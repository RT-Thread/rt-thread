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
 * @addtogroup nrf_i2s I2S HAL and driver
 * @ingroup    nrf_drivers
 * @brief      @tagAPI52 Inter-IC Sound (I2S) interface APIs.
 *
 * @defgroup   nrf_drv_i2s I2S driver
 * @{
 * @ingroup    nrf_i2s
 * @brief      @tagAPI52 Inter-IC Sound (I2S) interface driver.
 */


#ifndef NRF_DRV_I2S_H__
#define NRF_DRV_I2S_H__

#include "nordic_common.h"
#include "sdk_config.h"
#include "nrf_i2s.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief This value can be provided instead of a pin number for the signals
 *        SDOUT, SDIN, and MCK to specify that a given signal is not used
 *        and therefore does not need to be connected to a pin.
 */
#define NRF_DRV_I2S_PIN_NOT_USED  0xFF

/**
 * @brief Flag indicating that calls to the data handler for RX and TX should
 *        be synchronized, thus always combined into one call.
 *
 * Use this flag when calling @ref nrf_drv_i2s_start to force a common call
 * to the @ref nrf_drv_i2s_data_handler_t "data handler" for RX and TX data.
 * This is useful, for example, when received data should be processed and
 * then be sent back. Obviously, this flag is only applicable when both
 * directions (RX and TX) are enabled.
 */
#define NRF_DRV_I2S_FLAG_SYNCHRONIZED_MODE  0x01

/**
 * @brief I2S driver configuration structure.
 */
typedef struct
{
    uint8_t sck_pin;      ///< SCK pin number.
    uint8_t lrck_pin;     ///< LRCK pin number.
    uint8_t mck_pin;      ///< MCK pin number.
                          /**< Optional. Use @ref NRF_DRV_I2S_PIN_NOT_USED
                           *   if this signal is not needed. */
    uint8_t sdout_pin;    ///< SDOUT pin number.
                          /**< Optional. Use @ref NRF_DRV_I2S_PIN_NOT_USED
                           *   if this signal is not needed. */
    uint8_t sdin_pin;     ///< SDIN pin number.
                          /**< Optional. Use @ref NRF_DRV_I2S_PIN_NOT_USED
                           *   if this signal is not needed. */
    uint8_t irq_priority; ///< Interrupt priority.

    nrf_i2s_mode_t     mode;         ///< Mode of operation.
    nrf_i2s_format_t   format;       ///< Frame format.
    nrf_i2s_align_t    alignment;    ///< Alignment of sample within a frame.
    nrf_i2s_swidth_t   sample_width; ///< Sample width.
    nrf_i2s_channels_t channels;     ///< Enabled channels.
    nrf_i2s_mck_t      mck_setup;    ///< Master clock setup.
    nrf_i2s_ratio_t    ratio;        ///< MCK/LRCK ratio.
} nrf_drv_i2s_config_t;

/**
 * @brief I2S driver default configuration.
 */
#define NRF_DRV_I2S_DEFAULT_CONFIG           \
{                                            \
    .sck_pin      = I2S_CONFIG_SCK_PIN,      \
    .lrck_pin     = I2S_CONFIG_LRCK_PIN,     \
    .mck_pin      = I2S_CONFIG_MCK_PIN,      \
    .sdout_pin    = I2S_CONFIG_SDOUT_PIN,    \
    .sdin_pin     = I2S_CONFIG_SDIN_PIN,     \
    .irq_priority = I2S_CONFIG_IRQ_PRIORITY, \
    .mode         = (nrf_i2s_mode_t)I2S_CONFIG_MASTER,       \
    .format       = (nrf_i2s_format_t)I2S_CONFIG_FORMAT,       \
    .alignment    = (nrf_i2s_align_t)I2S_CONFIG_ALIGN,        \
    .sample_width = (nrf_i2s_swidth_t)I2S_CONFIG_SWIDTH,       \
    .channels     = (nrf_i2s_channels_t)I2S_CONFIG_CHANNELS,     \
    .mck_setup    = (nrf_i2s_mck_t)I2S_CONFIG_MCK_SETUP,    \
    .ratio        = (nrf_i2s_ratio_t)I2S_CONFIG_RATIO,        \
}

/**
 * @brief I2S driver data handler type.
 *
 * A data handling function of this type must be specified during initialization
 * of the driver. The driver will call this function when a new portion of data
 * is received or a new portion of data should be prepared for transmission.
 * The first case is indicated by a non-NULL value in the @p p_data_received
 * parameter (which points to the memory containing the received data).
 * Similarly, the second case is indicated by a non-NULL value in the
 * @p p_data_to_send parameter (which points to where the data to be transmitted
 * should be placed).
 *
 * @note The two cases mentioned above may be indicated separately or combined
 *       into one call (depending on the environment in which the driver is
 *       used). Therefore, both parameters should be checked and handled
 *       properly in every call. @ref NRF_DRV_I2S_FLAG_SYNCHRONIZED_MODE
 *       "Synchronized mode" can be used to always combine these indications.
 *
 * @param[in]  p_data_received Pointer to the buffer with received data,
 *                             or NULL if the handler is called to prepare
 *                             transmission only.
 * @param[out] p_data_to_send  Pointer to the buffer where data to be sent
 *                             should be written, or NULL if the handler is
 *                             called for received data only.
 * @param[in]  number_of_words Length of data received and/or to be written
 *                             (in 32-bit words). This value is always equal to
 *                             half the size of the buffers set by the call
 *                             to the @ref nrf_drv_i2s_start function.
 */
typedef void (* nrf_drv_i2s_data_handler_t)(uint32_t const * p_data_received,
                                            uint32_t       * p_data_to_send,
                                            uint16_t         number_of_words);


/**
 * @brief Function for initializing the I2S driver.
 *
 * @param[in] p_config Pointer to the structure with initial configuration.
 *                     If NULL, the default configuration is used.
 * @param[in] handler  Data handler provided by the user. Must not be NULL.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver was already initialized.
 * @retval NRF_ERROR_INVALID_PARAM If the requested combination of configuration
 *                                 options is not allowed by the I2S peripheral.
 */
ret_code_t nrf_drv_i2s_init(nrf_drv_i2s_config_t const * p_config,
                            nrf_drv_i2s_data_handler_t   handler);

/**
 * @brief Function for uninitializing the I2S driver.
 */
void       nrf_drv_i2s_uninit(void);

/**
 * @brief Function for starting the continuous I2S transfer.
 *
 * The I2S data transfer can be performed in one of three modes: RX (reception)
 * only, TX (transmission) only, or in both directions simultaneously.
 * The mode is selected by specifying a proper buffer for a given direction
 * in the call to this function or by passing NULL instead if this direction
 * should be disabled.
 *
 * The length of the buffer (which is a common value for RX and TX if both
 * directions are enabled) is specified in 32-bit words. One 32-bit memory
 * word can either contain four 8-bit samples, two 16-bit samples, or one
 * right-aligned 24-bit sample sign-extended to a 32-bit value.
 * For a detailed memory mapping for different supported configurations,
 * see the @linkProductSpecification52.
 *
 * The provided buffers are logically divided into two parts of equal size.
 * One of them is in use by the peripheral (for storing received data or for
 * getting data to be transmitted, respectively). The other part is provided
 * to the application via a call to the defined @ref nrf_drv_i2s_data_handler_t
 * "data handling function", so that the application can process the received
 * data or prepare the next portion of data to be sent. The two parts are
 * swapped every time @p buffer_size/2 data words are received or transmitted.
 *
 * Additional options are provided using the @p flags parameter:
 * - @ref NRF_DRV_I2S_FLAG_SYNCHRONIZED_MODE - the calls to data handler should
 *   be done in a synchronized manner (one common call for TX and RX).
 *   Applicable only when both RX and TX are enabled.
 *
 * @attention All data exchange is done in the data handler only. In particular,
 *            no data should be written to the transmit buffer before calling
 *            this function (a proper call to the data handler to get the first
 *            portion of data to be sent will be done before the actual transfer
 *            starts).
 *
 * @note Peripherals using EasyDMA (like I2S) require the transfer buffers
 *       to be placed in the Data RAM region. If this condition is not met,
 *       this function will fail with the error code NRF_ERROR_INVALID_ADDR.
 *
 * @param[in] p_rx_buffer Pointer to the receive buffer.
 *                        Pass NULL if reception is not required.
 * @param[in] p_tx_buffer Pointer to the transmit buffer.
 *                        Pass NULL if transmission is not required.
 * @param[in] buffer_size Size of the buffers (in 32-bit words).
 *                        The size must be an even number greater than 0.
 * @param[in] flags       Transfer options (0 for default settings).
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_INVALID_STATE If a transfer was already started or
 *                                 the driver has not been initialized.
 * @retval NRF_ERROR_INVALID_ADDR  If the provided buffers are not placed
 *                                 in the Data RAM region.
 */
ret_code_t nrf_drv_i2s_start(uint32_t * p_rx_buffer,
                             uint32_t * p_tx_buffer,
                             uint16_t   buffer_size,
                             uint8_t    flags);

/**
 * @brief Function for stopping the I2S transfer.
 */
void       nrf_drv_i2s_stop(void);


#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_I2S_H__

/** @} */
