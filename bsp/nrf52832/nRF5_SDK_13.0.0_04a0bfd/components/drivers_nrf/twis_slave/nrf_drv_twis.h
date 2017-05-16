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
#ifndef NRF_DRV_TWIS_H__
#define NRF_DRV_TWIS_H__

#include "sdk_config.h"
#include "nrf_drv_common.h"
#include "nrf_gpio.h"
#include "sdk_errors.h"
#include "nrf_twis.h"
#include <stdint.h>
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif
/**@file
 * @addtogroup nrf_twis Two Wire slave interface (TWIS)
 * @ingroup    nrf_drivers
 * @brief      Two Wire slave interface (TWIS) APIs.
 *
 *
 * @defgroup nrf_drv_twis TWIS driver
 * @{
 * @ingroup    nrf_twis
 * @brief      TWI slave APIs.
 */

/**
 * @brief Event callback function event definitions.
 */
typedef enum
{
    TWIS_EVT_READ_REQ,     ///< Read request detected
                           /**< If there is no buffer prepared, buf_req flag in the even will be set.
                                Call then @ref nrf_drv_twis_tx_prepare to give parameters for buffer.
                                */
    TWIS_EVT_READ_DONE,    ///< Read request has finished - free any data
    TWIS_EVT_READ_ERROR,   ///< Read request finished with error
    TWIS_EVT_WRITE_REQ,    ///< Write request detected
                           /**< If there is no buffer prepared, buf_req flag in the even will be set.
                                Call then @ref nrf_drv_twis_rx_prepare to give parameters for buffer.
                                */
    TWIS_EVT_WRITE_DONE,   ///< Write request has finished - process data
    TWIS_EVT_WRITE_ERROR,  ///< Write request finished with error
    TWIS_EVT_GENERAL_ERROR ///< Error that happens not inside WRITE or READ transaction
} nrf_drv_twis_evt_type_t;

/**
 * @brief TWIS driver instance structure
 *
 * @note We only need instance number here so we could really use just a number
 * that would be send to every driver function.
 * But for compatibility reason this number is inserted into the structure.
 */
typedef struct
{
    uint8_t instNr; /**< Instance number */
}nrf_drv_twis_t;

/**
 * @brief TWIS driver event structure
 */
typedef struct
{
    nrf_drv_twis_evt_type_t type; ///< Event type
    union
    {
        bool buf_req;       ///< Flag for @ref TWIS_EVT_READ_REQ and @ref TWIS_EVT_WRITE_REQ
                            /**< Information if transmission buffer requires to be prepared */
        uint32_t tx_amount; ///< Data for @ref TWIS_EVT_READ_DONE
        uint32_t rx_amount; ///< Data for @ref TWIS_EVT_WRITE_DONE
        uint32_t error;     ///< Data for @ref TWIS_EVT_GENERAL_ERROR
    }data;
}nrf_drv_twis_evt_t;

/**
 * @brief TWI slave event callback function type.
 *
 * @param[in] p_event Event information structure.
 */
typedef void (*nrf_drv_twis_event_handler_t)(nrf_drv_twis_evt_t const * const p_event);

/**
 * @brief Structure for TWIS configuration
 */
typedef struct
{
    uint32_t addr[2];               //!< Set addresses that this slave should respond. Set 0 to disable.
    uint32_t scl;                   //!< SCL pin number
    nrf_gpio_pin_pull_t scl_pull;   //!< SCL pin pull
    uint32_t sda;                   //!< SDA pin number
    nrf_gpio_pin_pull_t sda_pull;   //!< SDA pin pull
    uint8_t  interrupt_priority;    //!< The priority of interrupt for the module to set
}nrf_drv_twis_config_t;

/**
 * @brief Possible error sources
 *
 * This is flag enum - values from this enum can be connected using logical or operator.
 * @note
 * We could use directly @ref nrf_twis_error_t. Error type enum is redefined here becouse
 * of possible future extension (eg. supporting timeouts and synchronous mode).
 */
typedef enum
{
    NRF_DRV_TWIS_ERROR_OVERFLOW         = NRF_TWIS_ERROR_OVERFLOW,  /**< RX buffer overflow detected, and prevented */
    NRF_DRV_TWIS_ERROR_DATA_NACK        = NRF_TWIS_ERROR_DATA_NACK, /**< NACK sent after receiving a data byte */
    NRF_DRV_TWIS_ERROR_OVERREAD         = NRF_TWIS_ERROR_OVERREAD,  /**< TX buffer over-read detected, and prevented */
    NRF_DRV_TWIS_ERROR_UNEXPECTED_EVENT = 1 << 8                    /**< Unexpected event detected by state machine */
}nrf_drv_twis_error_t;

/**
 * @internal
 * @brief Internal macro for creating TWIS driver instance
 *
 * Second level of indirection in creating the instance.
 * Do not use this macro directly.
 * Use @ref NRF_DRV_TWIS_INSTANCE instead.
 */
#define NRF_DRV_TWIS_INSTANCE_x(id) \
    { \
        TWIS##id##_INSTANCE_INDEX \
    }

/**
 * @brief Macro for creating TWIS driver instance
 *
 * @param[in] id Instance index. Use 0 for TWIS0 and 1 for TWIS1
 */
#define NRF_DRV_TWIS_INSTANCE(id) NRF_DRV_TWIS_INSTANCE_x(id)

#define TWIS0_INSTANCE_INDEX 0
#define TWIS1_INSTANCE_INDEX TWIS0_INSTANCE_INDEX+TWIS0_ENABLED

/**
 * @brief Generate default configuration for TWIS driver instance
 */
#define NRF_DRV_TWIS_DEFAULT_CONFIG \
{ \
    .addr               = { TWIS_DEFAULT_CONFIG_ADDR0, TWIS_DEFAULT_CONFIG_ADDR1 }, \
    .scl                = 31, \
    .scl_pull           = (nrf_gpio_pin_pull_t)TWIS_DEFAULT_CONFIG_SCL_PULL, \
    .sda                = 31, \
    .sda_pull           = (nrf_gpio_pin_pull_t)TWIS_DEFAULT_CONFIG_SDA_PULL, \
    .interrupt_priority = TWIS_DEFAULT_CONFIG_IRQ_PRIORITY \
}

/**
 * @brief Function for initializing the TWIS driver instance.
 *
 * Function initializes and enables TWIS driver.
 * @attention After driver initialization enable it by @ref nrf_drv_twis_enable
 *
 * @param[in] p_instance      Pointer to the driver instance structure.
 * @attention                 @em p_instance has to be global object.
 *                            It would be used by interrupts so make it sure that object
 *                            would not be destroyed when function is leaving.
 * @param[in] p_config        Initial configuration.
 * @param[in] event_handler   Event handler provided by the user.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver is already initialized.
 * @retval NRF_ERROR_BUSY          If some other peripheral with the same
 *                                 instance ID is already in use. This is
 *                                 possible only if PERIPHERAL_RESOURCE_SHARING_ENABLED
 *                                 is set to a value other than zero.
 */
ret_code_t nrf_drv_twis_init(
        nrf_drv_twis_t          const * const p_instance,
        nrf_drv_twis_config_t   const * p_config,
        nrf_drv_twis_event_handler_t    const event_handler);

/**
 * @brief Function for uninitializing the TWIS driver instance.
 *
 * Function initializes the peripheral and resets all registers to default values.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @note
 * It is safe to call nrf_drv_twis_uninit even before initialization.
 * Actually @ref nrf_drv_twis_init function calls this function to
 * make sure that TWIS state is known.
 * @note
 * If TWIS driver was in uninitialized state before calling this function,
 * selected pins would not be reset to default configuration.
 */
void nrf_drv_twis_uninit(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Enable TWIS instance
 *
 * This function enables TWIS instance.
 * Function defined if there is needs for dynamically enabling and disabling the peripheral.
 * Use @ref nrf_drv_twis_enable and @ref nrf_drv_twis_disable functions.
 * They do not change any configuration registers.
 *
 * @param p_instance Pointer to the driver instance structure.
 */
void nrf_drv_twis_enable(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Disable TWIS instance
 *
 * Disabling TWIS instance gives possibility to turn off the TWIS while
 * holding configuration done by @ref nrf_drv_twis_init
 *
 * @param p_instance Pointer to the driver instance structure.
 */
void nrf_drv_twis_disable(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Get and clear last error flags
 *
 * Function gets information about errors.
 * This is also the only possibility to exit from error substate of the internal state machine.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @return Error flags defined in @ref nrf_drv_twis_error_t
 * @attention
 * This function clears error state and flags.
 */
uint32_t nrf_drv_twis_error_get_and_clear(nrf_drv_twis_t const * const p_instance);


/**
 * @brief Prepare data for sending
 *
 * This function should be used in response for @ref TWIS_EVT_READ_REQ event.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_buf      Transmission buffer
 * @attention            Transmission buffer has to be placed in RAM.
 * @param     size       Maximum number of bytes that master may read from buffer given.
 *
 * @retval NRF_SUCCESS              Preparation finished properly
 * @retval NRF_ERROR_INVALID_ADDR   Given @em p_buf is not placed inside the RAM
 * @retval NRF_ERROR_INVALID_LENGTH Wrong value in @em size parameter
 * @retval NRF_ERROR_INVALID_STATE  Module not initialized or not enabled
 */
ret_code_t nrf_drv_twis_tx_prepare(
        nrf_drv_twis_t const * const p_instance,
        void const * const p_buf,
        size_t size);

/**
 * @brief Get number of transmitted bytes
 *
 * Function returns number of bytes sent.
 * This function may be called after @ref TWIS_EVT_READ_DONE or @ref TWIS_EVT_READ_ERROR events.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @return Number of bytes sent.
 */
size_t nrf_drv_twis_tx_amount(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Prepare data for receiving
 *
 * This function should be used in response for @ref TWIS_EVT_WRITE_REQ event.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_buf      Buffer that would be filled with received data
 * @attention            Receiving buffer has to be placed in RAM.
 * @param     size       Size of the buffer (maximum amount of data to receive)
 *
 * @retval NRF_SUCCESS              Preparation finished properly
 * @retval NRF_ERROR_INVALID_ADDR   Given @em p_buf is not placed inside the RAM
 * @retval NRF_ERROR_INVALID_LENGTH Wrong value in @em size parameter
 * @retval NRF_ERROR_INVALID_STATE  Module not initialized or not enabled
 */
ret_code_t nrf_drv_twis_rx_prepare(
        nrf_drv_twis_t const * const p_instance,
        void * const p_buf,
        size_t size);

/**
 * @brief Get number of received bytes
 *
 * Function returns number of bytes received.
 * This function may be called after @ref TWIS_EVT_WRITE_DONE or @ref TWIS_EVT_WRITE_ERROR events.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @return Number of bytes received.
 */
size_t nrf_drv_twis_rx_amount(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Function checks if driver is busy right now
 *
 * Actual driver substate is tested.
 * If driver is in any other state than IDLE or ERROR this function returns true.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true  Driver is in state other than ERROR or IDLE
 * @retval false There is no transmission pending.
 */
bool nrf_drv_twis_is_busy(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Function checks if driver is waiting for tx buffer
 *
 * If this function returns true, it means that driver is stalled expecting
 * of the @ref nrf_drv_twis_tx_prepare function call.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true Driver waits for @ref nrf_drv_twis_tx_prepare
 * @retval false Driver is not in the state where it waits for preparing tx buffer.
 */
bool nrf_drv_twis_is_waiting_tx_buff(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Function checks if driver is waiting for rx buffer
 *
 * If this function returns true, it means that driver is staled expecting
 * of the @ref nrf_drv_twis_rx_prepare function call.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true Driver waits for @ref nrf_drv_twis_rx_prepare
 * @retval false Driver is not in the state where it waits for preparing rx buffer.
 */
bool nrf_drv_twis_is_waiting_rx_buff(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Check if driver is sending data
 *
 * If this function returns true, it means that there is ongoing output transmission.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true There is ongoing output transmission.
 * @retval false Driver is in other state.
 */
bool nrf_drv_twis_is_pending_tx(nrf_drv_twis_t const * const p_instance);

/**
 * @brief Check if driver is receiving data
 *
 * If this function returns true, it means that there is ongoing input transmission.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true There is ongoing input transmission.
 * @retval false Driver is in other state.
 */
bool nrf_drv_twis_is_pending_rx(nrf_drv_twis_t const * const p_instance);

/** @} */ /* End of lib_twis_drv group */

#ifdef __cplusplus
}
#endif

#endif /* NRF_DRV_TWIS_H__ */
