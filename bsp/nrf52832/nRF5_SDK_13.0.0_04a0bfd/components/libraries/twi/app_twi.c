/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(APP_TWI)
#include "app_twi.h"
#include "nrf_assert.h"
#include "app_util_platform.h"

static ret_code_t start_transfer(app_twi_t const * p_app_twi)
{
    ASSERT(p_app_twi != NULL);

    // [use a local variable to avoid using two volatile variables in one
    //  expression]
    uint8_t current_transfer_idx = p_app_twi->p_app_twi_cb->current_transfer_idx;
    app_twi_transfer_t const * p_transfer =
        &p_app_twi->p_app_twi_cb->p_current_transaction->p_transfers[current_transfer_idx];
    uint8_t address = APP_TWI_OP_ADDRESS(p_transfer->operation);

    nrf_drv_twi_xfer_desc_t xfer_desc;
    uint32_t                flags;

    xfer_desc.address       = address;
    xfer_desc.p_primary_buf = p_transfer->p_data;
    xfer_desc.primary_length = p_transfer->length;

    /* If it is possible try to bind two transfers together. They can be combined if:
     * - there is no stop condition after current transfer.
     * - current transfer is TX.
     * - there is at least one more transfer in the transaction.
     * - address of next trnasfer is the same as current transfer.
     */
    if ((p_transfer->flags & APP_TWI_NO_STOP) &&
        !APP_TWI_IS_READ_OP(p_transfer->operation) &&
        ((current_transfer_idx + 1)
            < p_app_twi->p_app_twi_cb->p_current_transaction->number_of_transfers) &&
        (APP_TWI_OP_ADDRESS(p_transfer->operation) ==
        APP_TWI_OP_ADDRESS(p_app_twi->p_app_twi_cb->p_current_transaction->
                            p_transfers[current_transfer_idx + 1].operation)))
    {
        app_twi_transfer_t const * p_second_transfer =
            &p_app_twi->p_app_twi_cb->p_current_transaction->p_transfers[current_transfer_idx + 1];
        xfer_desc.p_secondary_buf = p_second_transfer->p_data;
        xfer_desc.secondary_length = p_second_transfer->length;
        xfer_desc.type = APP_TWI_IS_READ_OP(p_second_transfer->operation) ? NRF_DRV_TWI_XFER_TXRX :
                                                                            NRF_DRV_TWI_XFER_TXTX;
        flags = (p_second_transfer->flags & APP_TWI_NO_STOP) ? NRF_DRV_TWI_FLAG_TX_NO_STOP : 0;
        p_app_twi->p_app_twi_cb->current_transfer_idx++;
    }
    else
    {
        xfer_desc.type = APP_TWI_IS_READ_OP(p_transfer->operation) ? NRF_DRV_TWI_XFER_RX :
                NRF_DRV_TWI_XFER_TX;
        xfer_desc.p_secondary_buf = NULL;
        xfer_desc.secondary_length = 0;
        flags = (p_transfer->flags & APP_TWI_NO_STOP) ? NRF_DRV_TWI_FLAG_TX_NO_STOP : 0;
    }

    return nrf_drv_twi_xfer(&p_app_twi->twi, &xfer_desc, flags);
}


static void transaction_end_signal(app_twi_t const * p_app_twi,
                                   ret_code_t        result)
{
    ASSERT(p_app_twi != NULL);

    if (p_app_twi->p_app_twi_cb->p_current_transaction->callback)
    {
        // [use a local variable to avoid using two volatile variables in one
        //  expression]
        void * p_user_data = p_app_twi->p_app_twi_cb->p_current_transaction->p_user_data;
        p_app_twi->p_app_twi_cb->p_current_transaction->callback(result, p_user_data);
    }
}

static void twi_event_handler(nrf_drv_twi_evt_t const * p_event,
                              void *                    p_context);

// This function starts pending transaction if there is no current one or
// when 'switch_transaction' parameter is set to true. It is important to
// switch to new transaction without setting 'p_app_twi->p_current_transaction'
// to NULL in between, since this pointer is used to check idle status - see
// 'app_twi_is_idle()'.
static void start_pending_transaction(app_twi_t const * p_app_twi,
                                      bool              switch_transaction)
{
    ASSERT(p_app_twi != NULL);

    for (;;)
    {
        bool start_transaction = false;

        CRITICAL_REGION_ENTER();
        if (switch_transaction || app_twi_is_idle(p_app_twi))
        {
            if (nrf_queue_pop(p_app_twi->p_queue,
                (void *)(&p_app_twi->p_app_twi_cb->p_current_transaction))
                == NRF_SUCCESS)
            {
                start_transaction = true;
            }
            else
            {
                p_app_twi->p_app_twi_cb->p_current_transaction = NULL;
            }
        }
        CRITICAL_REGION_EXIT();

        if (!start_transaction)
        {
            return;
        }
        else
        {
            ret_code_t result;

            nrf_drv_twi_config_t const * p_instance_cfg =
                p_app_twi->p_app_twi_cb->p_current_transaction->p_required_twi_cfg == NULL ?
                &p_app_twi->p_app_twi_cb->default_configuration :
                p_app_twi->p_app_twi_cb->p_current_transaction->p_required_twi_cfg;

            if (memcmp(p_app_twi->p_app_twi_cb->p_current_configuration,
                        p_instance_cfg,
                        sizeof(*p_instance_cfg)) != 0)
            {
                ret_code_t err_code;
                nrf_drv_twi_uninit(&p_app_twi->twi);
                err_code = nrf_drv_twi_init(&p_app_twi->twi,
                        p_instance_cfg,
                        twi_event_handler,
                        (void *)p_app_twi);
                ASSERT(err_code == NRF_SUCCESS);
                nrf_drv_twi_enable(&p_app_twi->twi);

                p_app_twi->p_app_twi_cb->p_current_configuration = p_instance_cfg;
            }

            // Try to start first transfer for this new transaction.
            p_app_twi->p_app_twi_cb->current_transfer_idx = 0;
            result = start_transfer(p_app_twi);

            // If transaction started successfully there is nothing more to do here now.
            if (result == NRF_SUCCESS)
            {
                return;
            }

            // Transfer failed to start - notify user that this transaction
            // cannot be started and try with next one (in next iteration of
            // the loop).
            transaction_end_signal(p_app_twi, result);

            switch_transaction = true;
        }
    }
}


static void twi_event_handler(nrf_drv_twi_evt_t const * p_event,
                              void *                    p_context)
{
    ASSERT(p_event != NULL);

    app_twi_t * p_app_twi = (app_twi_t *)p_context;
    ret_code_t result;

    // This callback should be called only during transaction.
    ASSERT(p_app_twi->p_app_twi_cb->p_current_transaction != NULL);

    if (p_event->type == NRF_DRV_TWI_EVT_DONE)
    {
        result = NRF_SUCCESS;

        // Transfer finished successfully. If there is another one to be
        // performed in the current transaction, start it now.
        // [use a local variable to avoid using two volatile variables in one
        //  expression]
        uint8_t current_transfer_idx = p_app_twi->p_app_twi_cb->current_transfer_idx;
        ++current_transfer_idx;
        if (current_transfer_idx <
                p_app_twi->p_app_twi_cb->p_current_transaction->number_of_transfers)
        {
            p_app_twi->p_app_twi_cb->current_transfer_idx = current_transfer_idx;

            result = start_transfer(p_app_twi);

            if (result == NRF_SUCCESS)
            {
                // The current transaction goes on and we've successfully
                // started its next transfer -> there is nothing more to do.
                return;
            }

            // [if the next transfer could not be started due to some error
            //  we finish the transaction with this error code as the result]
        }
    }
    else
    {
        result = NRF_ERROR_INTERNAL;
    }

    // The current transaction has been completed or interrupted by some error.
    // Notify the user and start next one (if there is any).
    transaction_end_signal(p_app_twi, result);
    // [we switch transactions here ('p_app_twi->p_current_transaction' is set
    //  to NULL only if there is nothing more to do) in order to not generate
    //  spurious idle status (even for a moment)]
    start_pending_transaction(p_app_twi, true);
}


ret_code_t app_twi_init(app_twi_t const *               p_app_twi,
                        nrf_drv_twi_config_t const *    p_default_twi_config)
{
    ASSERT(p_app_twi != NULL);
    ASSERT(p_app_twi->p_queue != NULL);
    ASSERT(p_app_twi->p_queue->size > 0);
    ASSERT(p_default_twi_config != NULL);

    ret_code_t err_code;

    err_code = nrf_drv_twi_init(&p_app_twi->twi,
                                p_default_twi_config,
                                twi_event_handler,
                                (void *)p_app_twi);
    VERIFY_SUCCESS(err_code);

    nrf_drv_twi_enable(&p_app_twi->twi);

    p_app_twi->p_app_twi_cb->internal_transaction_in_progress = false;
    p_app_twi->p_app_twi_cb->p_current_transaction   = NULL;
    p_app_twi->p_app_twi_cb->default_configuration   = *p_default_twi_config;
    p_app_twi->p_app_twi_cb->p_current_configuration =
        &p_app_twi->p_app_twi_cb->default_configuration;

    return NRF_SUCCESS;
}


void app_twi_uninit(app_twi_t const * p_app_twi)
{
    ASSERT(p_app_twi != NULL);

    nrf_drv_twi_uninit(&p_app_twi->twi);

    p_app_twi->p_app_twi_cb->p_current_transaction = NULL;
}


ret_code_t app_twi_schedule(app_twi_t const *             p_app_twi,
                            app_twi_transaction_t const * p_transaction)
{
    ASSERT(p_app_twi != NULL);
    ASSERT(p_transaction != NULL);
    ASSERT(p_transaction->p_transfers != NULL);
    ASSERT(p_transaction->number_of_transfers != 0);

    ret_code_t result = NRF_SUCCESS;

    result = nrf_queue_push(p_app_twi->p_queue, (void *)(&p_transaction));
    if (result == NRF_SUCCESS)
    {
        // New transaction has been successfully added to queue,
        // so if we are currently idle it's time to start the job.
        start_pending_transaction(p_app_twi, false);
    }

    return result;
}


static void internal_transaction_cb(ret_code_t result, void * p_user_data)
{
    app_twi_t * p_app_twi = (app_twi_t *)p_user_data;

    p_app_twi->p_app_twi_cb->internal_transaction_result      = result;
    p_app_twi->p_app_twi_cb->internal_transaction_in_progress = false;
}


ret_code_t app_twi_perform(app_twi_t const *          p_app_twi,
                           app_twi_transfer_t const * p_transfers,
                           uint8_t                    number_of_transfers,
                           void (* user_function)(void))
{
    ASSERT(p_app_twi != NULL);
    ASSERT(p_transfers != NULL);
    ASSERT(number_of_transfers != 0);

    bool busy = false;

    CRITICAL_REGION_ENTER();
    if (p_app_twi->p_app_twi_cb->internal_transaction_in_progress)
    {
        busy = true;
    }
    else
    {
        p_app_twi->p_app_twi_cb->internal_transaction_in_progress = true;
    }
    CRITICAL_REGION_EXIT();

    if (busy)
    {
        return NRF_ERROR_BUSY;
    }
    else
    {
        app_twi_transaction_t internal_transaction =
        {
            .callback            = internal_transaction_cb,
            .p_user_data         = (void *)p_app_twi,
            .p_transfers         = p_transfers,
            .number_of_transfers = number_of_transfers,
        };
        ret_code_t result = app_twi_schedule(p_app_twi, &internal_transaction);
        VERIFY_SUCCESS(result);

        while (p_app_twi->p_app_twi_cb->internal_transaction_in_progress)
        {
            if (user_function)
            {
                user_function();
            }
        }

        return p_app_twi->p_app_twi_cb->internal_transaction_result;
    }
}
#endif //NRF_MODULE_ENABLED(APP_TWI)
