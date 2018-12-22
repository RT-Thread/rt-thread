/**
 * Copyright (c) 2017 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_SPI_MNGR_H__
#define NRF_SPI_MNGR_H__

#include <stdint.h>
#include "nrf_drv_spi.h"
#include "sdk_errors.h"
#include "nrf_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_spi_mngr SPI transaction manager
 * @{
 * @ingroup app_common
 *
 * @brief Module for scheduling SPI transactions.
 */


/**
 * @brief Macro for creating a simple SPI transfer.
 *
 * @param[in] _p_tx_data    Pointer to the data to be sent.
 * @param[in] _tx_length    Number of bytes to send.
 * @param[in] _p_rx_data    Pointer to a buffer for received data.
 * @param[in] _rx_length    Number of bytes to receive.
 */
#define NRF_SPI_MNGR_TRANSFER(_p_tx_data, _tx_length, _p_rx_data, _rx_length)   \
{                                               \
    .p_tx_data = (uint8_t const *)_p_tx_data,   \
    .tx_length = (uint8_t)        _tx_length,   \
    .p_rx_data = (uint8_t *)      _p_rx_data,   \
    .rx_length = (uint8_t)        _rx_length,   \
}


/**
 * @brief SPI transaction end callback prototype.
 *
 * @param     result      Result of operation (NRF_SUCCESS on success,
 *                        otherwise a relevant error code).
 * @param[in] p_user_data Pointer to user data defined in transaction
 *                        descriptor.
 */
typedef void (* nrf_spi_mngr_callback_end_t)(ret_code_t result, void * p_user_data);

/**
 * @brief SPI transaction begin callback prototype.
 *
 * @param[in] p_user_data Pointer to user data defined in transaction
 *                        descriptor.
 */
typedef void (* nrf_spi_mngr_callback_begin_t)(void * p_user_data);


/**
 * @brief SPI transfer descriptor.
 */
typedef struct
{
    uint8_t const * p_tx_data;  ///< Pointer to the data to be sent.
    uint8_t         tx_length;  ///< Number of bytes to send.
    uint8_t *       p_rx_data;  ///< Pointer to a buffer for received data.
    uint8_t         rx_length;  ///< Number of bytes to receive.
} nrf_spi_mngr_transfer_t;


/**
 * @brief SPI transaction descriptor.
 */
typedef struct
{
    nrf_spi_mngr_callback_begin_t   begin_callback;
    ///< User-specified function to be called before the transaction is started.

    nrf_spi_mngr_callback_end_t     end_callback;
    ///< User-specified function to be called after the transaction is finished.

    void *                          p_user_data;
    ///< Pointer to user data to be passed to the end_callback.

    nrf_spi_mngr_transfer_t const * p_transfers;
    ///< Pointer to the array of transfers that make up the transaction.

    uint8_t                         number_of_transfers;
    ///< Number of transfers that make up the transaction.

    nrf_drv_spi_config_t const *    p_required_spi_cfg;
    ///< Pointer to instance hardware configuration.
} nrf_spi_mngr_transaction_t;


/**
 * @brief SPI instance control block.
 */
typedef struct
{
    nrf_spi_mngr_transaction_t const * volatile p_current_transaction;
    ///< Currently realized transaction.

    nrf_drv_spi_config_t                        default_configuration;
    ///< Default hardware configuration.

    nrf_drv_spi_config_t const *                p_current_configuration;
    ///< Pointer to current hardware configuration.

    uint8_t volatile                            current_transfer_idx;
    ///< Index of currently performed transfer (within current transaction).

    bool volatile                               internal_transaction_in_progress;
    ///< Informs that an internal transaction is being performed (by nrf_spi_mngr_perform()).

    uint8_t volatile                            internal_transaction_result;
    ///< Used to pass the result of the internal transaction realized by nrf_spi_mngr_perform().
} nrf_spi_mngr_cb_t;


/**
 * @brief SPI transaction manager instance.
 */
typedef struct
{
    nrf_spi_mngr_cb_t * p_nrf_spi_mngr_cb;
    ///< Control block of instance.

    nrf_queue_t const * p_queue;
    ///< Transaction queue.

    nrf_drv_spi_t       spi;
    ///< Pointer to SPI master driver instance.
} nrf_spi_mngr_t;


/**
 * @brief Macro for simplifying the defining of an SPI transaction manager
 *        instance.
 *
 * This macro allocates a static buffer for the transaction queue.
 * Therefore, it should be used in only one place in the code for a given
 * instance.
 *
 * @note The queue size is the maximum number of pending transactions
 *       not counting the one that is currently realized. This means that
 *       for an empty queue with size of for example 4 elements, it is
 *       possible to schedule up to 5 transactions.
 *
 * @param[in]  _nrf_spi_mngr_name   Name of instance to be created.
 * @param[in]  _queue_size          Size of the transaction queue (maximum number
 *                                  of pending transactions).
 * @param[in]  _spi_idx             Index of hardware SPI instance to be used.
 */
#define NRF_SPI_MNGR_DEF(_nrf_spi_mngr_name, _queue_size, _spi_idx) \
    NRF_QUEUE_DEF(nrf_spi_mngr_transaction_t const *,               \
                 _nrf_spi_mngr_name##_queue,                        \
                 (_queue_size),                                     \
                 NRF_QUEUE_MODE_NO_OVERFLOW);                       \
    static nrf_spi_mngr_cb_t CONCAT_2(_nrf_spi_mngr_name, _cb);     \
    static const nrf_spi_mngr_t _nrf_spi_mngr_name =                \
    {                                                               \
        .p_nrf_spi_mngr_cb = &CONCAT_2(_nrf_spi_mngr_name, _cb),    \
        .p_queue      = &_nrf_spi_mngr_name##_queue,                \
        .spi          = NRF_DRV_SPI_INSTANCE(_spi_idx)              \
    }


 /**
 * @brief Function for initializing an SPI transaction manager instance.
 *
 * @param[in] p_nrf_spi_mngr        Pointer to the instance to be initialized.
 * @param[in] p_default_spi_config  Pointer to the SPI driver configuration. This configuration
 *                                  will be used whenever the scheduled transaction will have
 *                                  p_spi_config set to NULL value.
 *
 * @return Values returned by the @ref nrf_drv_spi_init function.
 */
ret_code_t nrf_spi_mngr_init(nrf_spi_mngr_t const *         p_nrf_spi_mngr,
                             nrf_drv_spi_config_t const *   p_default_spi_config);


/**
 * @brief Function for uninitializing an SPI transaction manager instance.
 *
 * @param[in] p_nrf_spi_mngr Pointer to the instance to be uninitialized.
 */
void nrf_spi_mngr_uninit(nrf_spi_mngr_t const * p_nrf_spi_mngr);


/**
 * @brief Function for scheduling an SPI transaction.
 *
 * The transaction is enqueued and started as soon as the SPI bus is
 * available, thus when all previously scheduled transactions have been
 * finished (possibly immediately).
 *
 * @note If @ref nrf_spi_mngr_transaction_t::p_required_spi_cfg
 *       is set to a non-NULL value the module will compare it with
 *       @ref nrf_spi_mngr_cb_t::p_current_configuration and reinitialize hardware
 *       SPI instance with new parameters if any differences are found.
 *       If @ref nrf_spi_mngr_transaction_t::p_required_spi_cfg is set to NULL then
 *       it will treat it as it would be set to @ref nrf_spi_mngr_cb_t::default_configuration.
 *
 * @param[in] p_nrf_spi_mngr    Pointer to the SPI transaction manager instance.
 * @param[in] p_transaction     Pointer to the descriptor of the transaction to be
 *                              scheduled.
 *
 * @retval NRF_SUCCESS          If the transaction has been successfully scheduled.
 * @retval NRF_ERROR_NO_MEM     If the queue is full (Only if queue in
 *                              @ref NRF_QUEUE_MODE_NO_OVERFLOW).
 */
ret_code_t nrf_spi_mngr_schedule(nrf_spi_mngr_t const *             p_nrf_spi_mngr,
                                 nrf_spi_mngr_transaction_t const * p_transaction);


/**
 * @brief Function for scheduling a transaction and waiting until it is finished.
 *
 * This function schedules a transaction that consists of one or more transfers
 * and waits until it is finished.
 *
 * @param[in] p_nrf_spi_mngr        Pointer to the SPI transaction manager instance.
 * @param[in] p_transfers           Pointer to an array of transfers to be performed.
 * @param     number_of_transfers   Number of transfers to be performed.
 * @param     user_function         User-specified function to be called while
 *                                  waiting. NULL if such functionality
 *                                  is not needed.
 *
 * @retval NRF_SUCCESS              If the transfers have been successfully realized.
 * @retval NRF_ERROR_BUSY           If some transfers are already being performed.
 * @retval -                        Other error codes mean that the transaction has failed
 *                                  with the error reported by @ref nrf_drv_spi_transfer().
 */
ret_code_t nrf_spi_mngr_perform(nrf_spi_mngr_t const *          p_nrf_spi_mngr,
                                nrf_spi_mngr_transfer_t const * p_transfers,
                                uint8_t                         number_of_transfers,
                                void (* user_function)(void));


/**
 * @brief Function for getting the current state of an SPI transaction manager
 *        instance.
 *
 * @param[in] p_nrf_spi_mngr Pointer to the SPI transaction manager instance.
 *
 * @retval true  If all scheduled transactions have been finished.
 * @retval false Otherwise.
 */
__STATIC_INLINE bool nrf_spi_mngr_is_idle(nrf_spi_mngr_t const * p_nrf_spi_mngr)
{
    return (p_nrf_spi_mngr->p_nrf_spi_mngr_cb->p_current_transaction == NULL);
}

/**
 *@}
 **/
//typedef int p_current_transaction;

#ifdef __cplusplus
}
#endif

#endif // NRF_SPI_MNGR_H__
