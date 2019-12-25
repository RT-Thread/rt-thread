/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_SPI_MNGR)
#include "nrf_spi_mngr.h"
#include "nrf_assert.h"
#include "app_util_platform.h"

typedef volatile struct
{
    bool    transaction_in_progress;
    uint8_t transaction_result;
} nrf_spi_mngr_cb_data_t;

static ret_code_t start_transfer(nrf_spi_mngr_t const * p_nrf_spi_mngr)
{
    ASSERT(p_nrf_spi_mngr != NULL);

    // use a local variable to avoid using two volatile variables in one
    // expression
    uint8_t curr_transfer_idx = p_nrf_spi_mngr->p_nrf_spi_mngr_cb->current_transfer_idx;
    nrf_spi_mngr_transfer_t const * p_transfer =
        &p_nrf_spi_mngr->p_nrf_spi_mngr_cb->p_current_transaction->p_transfers[curr_transfer_idx];

    return nrf_drv_spi_transfer(&p_nrf_spi_mngr->spi,
                                p_transfer->p_tx_data, p_transfer->tx_length,
                                p_transfer->p_rx_data, p_transfer->rx_length);
}


static void transaction_begin_signal(nrf_spi_mngr_t const * p_nrf_spi_mngr)
{
    ASSERT(p_nrf_spi_mngr != NULL);

    nrf_spi_mngr_transaction_t const * p_current_transaction =
        p_nrf_spi_mngr->p_nrf_spi_mngr_cb->p_current_transaction;


    if (p_current_transaction->begin_callback != NULL)
    {
        void * p_user_data = p_current_transaction->p_user_data;
        p_current_transaction->begin_callback(p_user_data);
    }
}


static void transaction_end_signal(nrf_spi_mngr_t const * p_nrf_spi_mngr,
                                   ret_code_t             result)
{
    ASSERT(p_nrf_spi_mngr != NULL);

    nrf_spi_mngr_transaction_t const * p_current_transaction =
        p_nrf_spi_mngr->p_nrf_spi_mngr_cb->p_current_transaction;

    if (p_current_transaction->end_callback != NULL)
    {
        void * p_user_data = p_current_transaction->p_user_data;
        p_current_transaction->end_callback(result, p_user_data);
    }
}


static void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                              void *                    p_context);


// This function starts pending transaction if there is no current one or
// when 'switch_transaction' parameter is set to true. It is important to
// switch to new transaction without setting 'p_nrf_spi_mngr->p_curr_transaction'
// to NULL in between, since this pointer is used to check idle status - see
// 'nrf_spi_mngr_is_idle()'.
static void start_pending_transaction(nrf_spi_mngr_t const * p_nrf_spi_mngr,
                                      bool                   switch_transaction)
{
    ASSERT(p_nrf_spi_mngr != NULL);

    while (1)
    {
        bool start_transaction = false;
        nrf_spi_mngr_cb_t * p_cb = p_nrf_spi_mngr->p_nrf_spi_mngr_cb;

        CRITICAL_REGION_ENTER();
        if (switch_transaction || nrf_spi_mngr_is_idle(p_nrf_spi_mngr))
        {
            if (nrf_queue_pop(p_nrf_spi_mngr->p_queue,
                              (void *)(&p_cb->p_current_transaction))
                == NRF_SUCCESS)
            {
                start_transaction = true;
            }
            else
            {
                p_cb->p_current_transaction = NULL;
            }
        }
        CRITICAL_REGION_EXIT();

        if (!start_transaction)
        {
            return;
        }

        nrf_drv_spi_config_t const * p_instance_cfg;
        if (p_cb->p_current_transaction->p_required_spi_cfg == NULL)
        {
            p_instance_cfg = &p_cb->default_configuration;
        }
        else
        {
            p_instance_cfg = p_cb->p_current_transaction->p_required_spi_cfg;
        }

        ret_code_t result;

        if (memcmp(p_cb->p_current_configuration, p_instance_cfg, sizeof(*p_instance_cfg)) != 0)
        {
            nrf_drv_spi_uninit(&p_nrf_spi_mngr->spi);
            result = nrf_drv_spi_init(&p_nrf_spi_mngr->spi,
                                      p_instance_cfg,
                                      spi_event_handler,
                                      (void *)p_nrf_spi_mngr);
            ASSERT(result == NRF_SUCCESS);
            p_cb->p_current_configuration = p_instance_cfg;
        }

        // Try to start first transfer for this new transaction.
        p_cb->current_transfer_idx = 0;

        // Execute user code if available before starting transaction
        transaction_begin_signal(p_nrf_spi_mngr);
        result = start_transfer(p_nrf_spi_mngr);

        // If transaction started successfully there is nothing more to do here now.
        if (result == NRF_SUCCESS)
        {
            return;
        }

        // Transfer failed to start - notify user that this transaction
        // cannot be started and try with next one (in next iteration of
        // the loop).
        transaction_end_signal(p_nrf_spi_mngr, result);

        switch_transaction = true;
    }
}


// This function shall be called to handle SPI events. It shall be mainly used by SPI IRQ for
// finished tranfer.
static void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                              void *                    p_context)
{
    ASSERT(p_event != NULL);
    ASSERT(p_context != NULL);

    ret_code_t result;
    nrf_spi_mngr_cb_t * p_cb = ((nrf_spi_mngr_t const *)p_context)->p_nrf_spi_mngr_cb;

    // This callback should be called only during transaction.
    ASSERT(p_cb->p_current_transaction != NULL);

    if (p_event->type == NRF_DRV_SPI_EVENT_DONE)
    {
        result = NRF_SUCCESS;

        // Transfer finished successfully. If there is another one to be
        // performed in the current transaction, start it now.
        // use a local variable to avoid using two volatile variables in one
        // expression
        uint8_t curr_transfer_idx = p_cb->current_transfer_idx;
        ++curr_transfer_idx;
        if (curr_transfer_idx < p_cb->p_current_transaction->number_of_transfers)
        {
            p_cb->current_transfer_idx = curr_transfer_idx;

            result = start_transfer(((nrf_spi_mngr_t const *)p_context));

            if (result == NRF_SUCCESS)
            {
                // The current transaction is running and its next transfer
                // has been successfully started. There is nothing more to do.
                return;
            }
            // if the next transfer could not be started due to some error
            // we finish the transaction with this error code as the result
        }
    }
    else
    {
        result = NRF_ERROR_INTERNAL;
    }

    // The current transaction has been completed or interrupted by some error.
    // Notify the user and start next one (if there is any).
    transaction_end_signal(((nrf_spi_mngr_t const *)p_context), result);
    // we switch transactions here ('p_nrf_spi_mngr->p_current_transaction' is set
    // to NULL only if there is nothing more to do) in order to not generate
    // spurious idle status (even for a moment)
    start_pending_transaction(((nrf_spi_mngr_t const *)p_context), true);
}


ret_code_t nrf_spi_mngr_init(nrf_spi_mngr_t const *       p_nrf_spi_mngr,
                             nrf_drv_spi_config_t const * p_default_spi_config)
{
    ASSERT(p_nrf_spi_mngr != NULL);
    ASSERT(p_nrf_spi_mngr->p_queue != NULL);
    ASSERT(p_nrf_spi_mngr->p_queue->size > 0);
    ASSERT(p_default_spi_config != NULL);

    ret_code_t err_code;

    err_code = nrf_drv_spi_init(&p_nrf_spi_mngr->spi,
                                p_default_spi_config,
                                spi_event_handler,
                                (void *)p_nrf_spi_mngr);

    if (err_code == NRF_SUCCESS)
    {
        nrf_spi_mngr_cb_t * p_cb = p_nrf_spi_mngr->p_nrf_spi_mngr_cb;

        p_cb->p_current_transaction = NULL;
        p_cb->default_configuration = *p_default_spi_config;
        p_cb->p_current_configuration = &p_cb->default_configuration;
    }

    return err_code;
}


void nrf_spi_mngr_uninit(nrf_spi_mngr_t const * p_nrf_spi_mngr)
{
    ASSERT(p_nrf_spi_mngr != NULL);

    nrf_drv_spi_uninit(&p_nrf_spi_mngr->spi);

    p_nrf_spi_mngr->p_nrf_spi_mngr_cb->p_current_transaction = NULL;
}


ret_code_t nrf_spi_mngr_schedule(nrf_spi_mngr_t const *             p_nrf_spi_mngr,
                                 nrf_spi_mngr_transaction_t const * p_transaction)
{
    ASSERT(p_nrf_spi_mngr != NULL);
    ASSERT(p_transaction != NULL);
    ASSERT(p_transaction->p_transfers != NULL);
    ASSERT(p_transaction->number_of_transfers != 0);

    ret_code_t result = nrf_queue_push(p_nrf_spi_mngr->p_queue, (void *)(&p_transaction));
    if (result == NRF_SUCCESS)
    {
        // New transaction has been successfully added to queue,
        // so if we are currently idle it's time to start the job.
        start_pending_transaction(p_nrf_spi_mngr, false);
    }

    return result;
}


static void spi_internal_transaction_cb(ret_code_t result, void * p_user_data)
{
    nrf_spi_mngr_cb_data_t * p_cb_data = (nrf_spi_mngr_cb_data_t *)p_user_data;

    p_cb_data->transaction_result      = result;
    p_cb_data->transaction_in_progress = false;
}

ret_code_t nrf_spi_mngr_perform(nrf_spi_mngr_t const *          p_nrf_spi_mngr,
                                nrf_drv_spi_config_t const *    p_config,
                                nrf_spi_mngr_transfer_t const * p_transfers,
                                uint8_t                         number_of_transfers,
                                void                            (* user_function)(void))
{
    ASSERT(p_nrf_spi_mngr != NULL);
    ASSERT(p_transfers != NULL);
    ASSERT(number_of_transfers != 0);

    nrf_spi_mngr_cb_data_t cb_data =
    {
        .transaction_in_progress = true
    };

    nrf_spi_mngr_transaction_t internal_transaction =
    {
        .begin_callback      = NULL,
        .end_callback        = spi_internal_transaction_cb,
        .p_user_data         = (void *)&cb_data,
        .p_transfers         = p_transfers,
        .number_of_transfers = number_of_transfers,
        .p_required_spi_cfg  = p_config
    };

    ret_code_t result = nrf_spi_mngr_schedule(p_nrf_spi_mngr, &internal_transaction);
    VERIFY_SUCCESS(result);

    while (cb_data.transaction_in_progress)
    {
        if (user_function)
        {
            user_function();
        }
    }

    return cb_data.transaction_result;
}

#endif //NRF_MODULE_ENABLED(NRF_SPI_MNGR)

