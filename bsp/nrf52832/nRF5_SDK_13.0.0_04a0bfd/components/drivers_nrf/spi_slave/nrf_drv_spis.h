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
/**@file
 * @addtogroup nrf_spis SPIS HAL and driver
 * @ingroup    nrf_drivers
 * @brief      SPIS APIs.
 *
 */

#ifndef SPI_SLAVE_H__
#define SPI_SLAVE_H__

#include <stdint.h>
#include "nrf.h"
#include "nrf_error.h"
#include "sdk_config.h"
#include "nrf_spis.h"
#include "nrf_gpio.h"
#include "sdk_common.h"
#include "app_util_platform.h"
#include "nrf_peripherals.h"

#ifdef __cplusplus
extern "C" {
#endif


    #define SPIS0_IRQ            SPI0_TWI0_IRQn
    #define SPIS0_IRQ_HANDLER    SPI0_TWI0_IRQHandler
    #define SPIS1_IRQ            SPI1_TWI1_IRQn
    #define SPIS1_IRQ_HANDLER    SPI1_TWI1_IRQHandler

#if SPIS_COUNT > 2
    #define SPIS2_IRQ            SPIM2_SPIS2_SPI2_IRQn
    #define SPIS2_IRQ_HANDLER    SPIM2_SPIS2_SPI2_IRQHandler
#endif

/**
 * @defgroup nrf_drv_spis SPI slave driver
 * @{
 * @ingroup  nrf_spis
 * @brief    Multi-instance SPI slave driver.
 */

#define NRF_DRV_SPIS_DEFAULT_CSN_PULLUP NRF_GPIO_PIN_NOPULL /**< Default pull-up configuration of the SPI CS. */
#define NRF_DRV_SPIS_DEFAULT_MISO_DRIVE NRF_GPIO_PIN_S0S1   /**< Default drive configuration of the SPI MISO. */

/**
* @brief This value can be provided instead of a pin number for the signals MOSI
*        and MISO to specify that the given signal is not used and therefore
*        does not need to be connected to a pin.
*/
#define NRF_DRV_SPIS_PIN_NOT_USED       0xFF

/** @brief SPIS transaction bit order definitions. */
typedef enum
{
    NRF_DRV_SPIS_BIT_ORDER_LSB_FIRST = NRF_SPIS_BIT_ORDER_LSB_FIRST, /**< Least significant bit shifted out first. */
    NRF_DRV_SPIS_BIT_ORDER_MSB_FIRST = NRF_SPIS_BIT_ORDER_MSB_FIRST  /**< Most significant bit shifted out first. */
} nrf_drv_spis_endian_t;

/** @brief SPIS mode definitions for clock polarity and phase. */
typedef enum
{
    NRF_DRV_SPIS_MODE_0 = NRF_SPIS_MODE_0,       /**< (CPOL = 0, CPHA = 0). */
    NRF_DRV_SPIS_MODE_1 = NRF_SPIS_MODE_1,       /**< (CPOL = 0, CPHA = 1). */
    NRF_DRV_SPIS_MODE_2 = NRF_SPIS_MODE_2,       /**< (CPOL = 1, CPHA = 0). */
    NRF_DRV_SPIS_MODE_3 = NRF_SPIS_MODE_3        /**< (CPOL = 1, CPHA = 1). */
} nrf_drv_spis_mode_t;

/** @brief Event callback function event definitions. */
typedef enum
{
    NRF_DRV_SPIS_BUFFERS_SET_DONE,          /**< Memory buffer set event. Memory buffers have been set successfully to the SPI slave device, and SPI transactions can be done. */
    NRF_DRV_SPIS_XFER_DONE,                 /**< SPI transaction event. SPI transaction has been completed. */
    NRF_DRV_SPIS_EVT_TYPE_MAX                    /**< Enumeration upper bound. */
} nrf_drv_spis_event_type_t;

/** @brief Structure containing the event context from the SPI slave driver. */
typedef struct
{
    nrf_drv_spis_event_type_t evt_type;     //!< Type of event.
    uint32_t                  rx_amount;    //!< Number of bytes received in last transaction. This parameter is only valid for @ref NRF_DRV_SPIS_XFER_DONE events.
    uint32_t                  tx_amount;    //!< Number of bytes transmitted in last transaction. This parameter is only valid for @ref NRF_DRV_SPIS_XFER_DONE events.
} nrf_drv_spis_event_t;

/** @brief SPI slave driver instance data structure. */
typedef struct
{
    NRF_SPIS_Type * p_reg;          //!< SPIS instance register.
    uint8_t         instance_id;    //!< SPIS instance ID.
    IRQn_Type       irq;            //!< IRQ of the specific instance.
} nrf_drv_spis_t;

#define SPIS0_INSTANCE_INDEX 0
#define SPIS1_INSTANCE_INDEX SPIS0_INSTANCE_INDEX+SPIS0_ENABLED
#define SPIS2_INSTANCE_INDEX SPIS1_INSTANCE_INDEX+SPIS1_ENABLED

/** @brief Macro for creating an SPI slave driver instance. */
#define NRF_DRV_SPIS_INSTANCE(id)                        \
{                                                        \
    .p_reg        = CONCAT_2(NRF_SPIS, id),              \
    .irq          = CONCAT_3(SPIS, id, _IRQ),            \
    .instance_id  = CONCAT_3(SPIS, id, _INSTANCE_INDEX), \
}

/** @brief SPI slave instance default configuration. */
#define NRF_DRV_SPIS_DEFAULT_CONFIG                                \
{                                                                  \
    .sck_pin      = NRF_DRV_SPIS_PIN_NOT_USED,                     \
    .mosi_pin     = NRF_DRV_SPIS_PIN_NOT_USED,                     \
    .miso_pin     = NRF_DRV_SPIS_PIN_NOT_USED,                     \
    .csn_pin      = NRF_DRV_SPIS_PIN_NOT_USED,                     \
    .miso_drive   = NRF_DRV_SPIS_DEFAULT_MISO_DRIVE,               \
    .csn_pullup   = NRF_DRV_SPIS_DEFAULT_CSN_PULLUP,               \
    .orc          = SPIS_DEFAULT_ORC,                              \
    .def          = SPIS_DEFAULT_DEF,                              \
    .mode         = (nrf_drv_spis_mode_t)SPIS_DEFAULT_MODE,        \
    .bit_order    = (nrf_drv_spis_endian_t)SPIS_DEFAULT_BIT_ORDER, \
    .irq_priority = SPIS_DEFAULT_CONFIG_IRQ_PRIORITY,              \
}

/** @brief SPI peripheral device configuration data. */
typedef struct
{
    uint32_t              miso_pin;            //!< SPI MISO pin (optional).
                                               /**< Set @ref NRF_DRV_SPIS_PIN_NOT_USED
                                                *   if this signal is not needed. */
    uint32_t              mosi_pin;            //!< SPI MOSI pin (optional).
                                               /**< Set @ref NRF_DRV_SPIS_PIN_NOT_USED
                                                *   if this signal is not needed. */
    uint32_t              sck_pin;             //!< SPI SCK pin.
    uint32_t              csn_pin;             //!< SPI CSN pin.
    nrf_drv_spis_mode_t   mode;                //!< SPI mode.
    nrf_drv_spis_endian_t bit_order;           //!< SPI transaction bit order.
    nrf_gpio_pin_pull_t   csn_pullup;          //!< CSN pin pull-up configuration.
    nrf_gpio_pin_drive_t  miso_drive;          //!< MISO pin drive configuration.
    uint8_t               def;                 //!< Character clocked out in case of an ignored transaction.
    uint8_t               orc;                 //!< Character clocked out after an over-read of the transmit buffer.
    uint8_t               irq_priority;        //!< Interrupt priority.
} nrf_drv_spis_config_t;


/** @brief SPI slave event callback function type.
 *
 * @param[in] event                 SPI slave driver event.
 */
typedef void (*nrf_drv_spis_event_handler_t)(nrf_drv_spis_event_t event);

/** @brief Function for initializing the SPI slave driver instance.
 *
 * @note When the nRF52 Anomaly 109 workaround for SPIS is enabled, this function
 *       initializes the GPIOTE driver as well, and uses one of GPIOTE channels
 *       to detect falling edges on CSN pin.
 *
 * @param[in] p_instance    Pointer to the driver instance structure.
 * @param[in] p_config      Pointer to the structure with the initial configuration.
 *                          If NULL, the default configuration will be used.
 * @param[in] event_handler Function to be called by the SPI slave driver upon event.
 *
 * @retval NRF_SUCCESS             If the initialization was successful.
 * @retval NRF_ERROR_INVALID_PARAM If an invalid parameter is supplied.
 * @retval NRF_ERROR_BUSY          If some other peripheral with the same
 *                                 instance ID is already in use. This is
 *                                 possible only if PERIPHERAL_RESOURCE_SHARING_ENABLED
 *                                 is set to a value other than zero.
 * @retval NRF_ERROR_INTERNAL      GPIOTE channel for detecting falling edges
 *                                 on CSN pin cannot be initialized. Possible
 *                                 only when using nRF52 Anomaly 109 workaround.
 */
ret_code_t nrf_drv_spis_init(nrf_drv_spis_t const * const  p_instance,
                             nrf_drv_spis_config_t const * p_config,
                             nrf_drv_spis_event_handler_t  event_handler);

/**
 * @brief Function for uninitializing the SPI slave driver instance.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void nrf_drv_spis_uninit(nrf_drv_spis_t const * const p_instance);

/** @brief Function for preparing the SPI slave instance for a single SPI transaction.
 *
 * This function prepares the SPI slave device to be ready for a single SPI transaction. It configures
 * the SPI slave device to use the memory supplied with the function call in SPI transactions.
 *
 * When either the memory buffer configuration or the SPI transaction has been
 * completed, the event callback function will be called with the appropriate event
 * @ref nrf_drv_spis_event_type_t. Note that the callback function can be called before returning from
 * this function, because it is called from the SPI slave interrupt context.
 *
 * @note This function can be called from the callback function context.
 *
 * @note Client applications must call this function after every @ref NRF_DRV_SPIS_XFER_DONE event if
 * the SPI slave driver should be prepared for a possible new SPI transaction.
 *
 * @note Peripherals that are using EasyDMA (for example, SPIS) require the transfer buffers
 * to be placed in the Data RAM region. Otherwise, this function will fail
 * with the error code NRF_ERROR_INVALID_ADDR.
 *
 * @param[in] p_instance            Pointer to the driver instance structure.
 * @param[in] p_tx_buffer           Pointer to the TX buffer.
 * @param[in] p_rx_buffer           Pointer to the RX buffer.
 * @param[in] tx_buffer_length      Length of the TX buffer in bytes.
 * @param[in] rx_buffer_length      Length of the RX buffer in bytes.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NULL           If the operation failed because a NULL pointer was supplied.
 * @retval NRF_ERROR_INVALID_STATE  If the operation failed because the SPI slave device is in an incorrect state.
 * @retval NRF_ERROR_INVALID_ADDR   If the provided buffers are not placed in the Data
 *                                  RAM region.
 * @retval NRF_ERROR_INTERNAL       If the operation failed because of an internal error.
 */
ret_code_t nrf_drv_spis_buffers_set(nrf_drv_spis_t const * const  p_instance,
                                    const uint8_t * p_tx_buffer,
                                    uint8_t   tx_buffer_length,
                                    uint8_t * p_rx_buffer,
                                    uint8_t   rx_buffer_length);


#ifdef __cplusplus
}
#endif

#endif // SPI_SLAVE_H__

/** @} */
