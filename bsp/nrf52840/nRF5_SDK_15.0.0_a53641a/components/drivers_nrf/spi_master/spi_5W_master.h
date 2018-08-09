/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#ifndef APP_SPI_MASTER_H
#define APP_SPI_MASTER_H

#include <stdint.h>
#include <stdlib.h>
#include "boards.h"

#ifdef __cplusplus
extern "C" {
#endif

#define _SPI_5W_

/**@brief Struct containing configuration parameters of the SPI master. */
typedef struct
{
    uint32_t SPI_Freq;      /**< SPI frequency. */
    uint32_t SPI_Pin_SCK;   /**< SCK pin number. */
    uint32_t SPI_Pin_MISO;  /**< MISO pin number. */
    uint32_t SPI_Pin_MOSI;  /**< MOSI pin number .*/
    uint32_t SPI_Pin_SS;    /**< Slave select pin number. */
    uint8_t SPI_ORDER;      /**< Bytes order MSBFIRST or LSBFIRST. */
    uint8_t SPI_CPOL;       /**< Serial clock polarity ACTIVEHIGH or ACTIVELOW. */
    uint8_t SPI_CPHA;       /**< Serial clock phase LEADING or TRAILING. */
 } spi_master_config_t;

/**@brief SPI master driver events types. */
typedef enum
{
    SPI_MASTER_EVT_TRANSFER_STARTED = 0, /**< An event indicating that transfer has been started */
    SPI_MASTER_EVT_TRANSFER_COMPLETED,   /**< An event indicating that transfer has been completed */
    SPI_MASTER_EVT_TRANSFER_ABORTED,   /**< An event indicating that transfer has been aborted */
    SPI_MASTER_EVT_TRANSFER_RESTARTED,   /**< An event indicating that transfer has been resumed */
    SPI_MASTER_EVT_FIRST_BYTE_RECEIVED,   /**< An event indicating end of one byte transfer  */
    SPI_MASTER_EVT_TYPE_MAX              /**< Enumeration upper bound. */
} spi_master_evt_type_t;

/**@brief Struct containing parameters of the SPI MASTER event */
 typedef struct
 {
   spi_master_evt_type_t type; /**< Type of an event */
   uint16_t data;                   /**< event data - context dependent */
 } spi_master_evt_t;

 /**@brief SPI MASTER internal states types. */
 typedef enum
 {
   SPI_MASTER_STATE_DISABLED, /**< A state indicating that SPI master is disabled. */
   SPI_MASTER_STATE_BUSY,     /**< A state indicating that SPI master is sending now. */
   SPI_MASTER_STATE_ABORTED,
   SPI_MASTER_STATE_IDLE      /**< A state indicating that SPI master is idle now. */
 } spi_master_state_t;

 /**@brief Instances of SPI master module. */
 typedef enum
 {
     #ifdef SPI_MASTER_0_ENABLE
        SPI_MASTER_0,   /**< A instance of SPI master 0. */
     #endif

     #ifdef SPI_MASTER_1_ENABLE
        SPI_MASTER_1,   /**< A instance of SPI master 1. */
     #endif

     SPI_MASTER_HW_ENABLED_COUNT    /**< A number of enabled instances of SPI master. */
 } spi_master_hw_instance_t;

/**@brief Type of generic callback function handler to be used by all SPI MASTER driver events.
 *
 * @param[in] spi_master_evt    SPI MASTER driver event.
 */
typedef void (*spi_master_event_handler_t) (spi_master_evt_t spi_master_evt);


/**@brief Function for opening and initializing a SPI master driver.
 *
 * @note  Function initializes SPI master hardware and internal module states, unregister events callback.
 *
 * @warning If the function has been already called, the function @ref spi_master_close has to be
 *          called before spi_master_open can be called again.
 *
 * @param[in] spi_master_hw_instance    Instance of SPI master module.
 * @param[in] p_spi_master_config       Pointer to configuration structure which will be used
 *                                      to initialize SPI MASTER hardware.
 *
 * @retval NRF_SUCCESS                Operation success.
 * @retval NRF_ERROR_INVALID_STATE    Operation failure. The function has been already called.
 *                                    To call it again the function @ref spi_master_close
 *                                    has to be called previously.
 * @retval NRF_ERROR_NULL             Operation failure. NULL pointer supplied.
 */
uint32_t spi_master_open(const spi_master_hw_instance_t spi_master_hw_instance,
                         spi_master_config_t const * const p_spi_master_config);


/**@brief Function for closing a SPI MASTER driver.
 *
 * @note  Function disable hardware, reset internal module states and unregister events callback
 *        function.
 *
 * @param[in] spi_master_hw_instance    A instance of SPI master.
 */
void spi_master_close(const spi_master_hw_instance_t spi_master_hw_instance);


/**@brief Function for transferring data between SPI master and SPI slave
 *
 * @note  Function registers buffers pointed by p_tx_buf and p_rx_buf parameters, after that starts transmission.
 *        Function generates an event of type @ref SPI_MASTER_EVT_TRANSFER_STARTED when transfer has been started
 *        and @ref SPI_MASTER_EVT_TRANSFER_COMPLETED when transfer has been completed.
 *
 * @param[in]  spi_master_hw_instance    Instance of SPI master module.
 * @param[in]  p_tx_buf                  Pointer to a transmit buffer.
 * @param[in]  tx_buf_len                Number of octets to the transfer.
 * @param[out] p_rx_buf                  Pointer to a receive buffer.
 * @param[in]  rx_buf_len                Number of octets to be received.
 *
 * @retval NRF_SUCCESS                Operation success. Packet was registered to the transmission
 *                                    and event will be send upon transmission completion.
 * @retval NRF_ERROR_BUSY             Operation failure. Transmitting of a data is in progress.
 */
 uint32_t spi_master_send_recv(const spi_master_hw_instance_t spi_master_hw_instance,
                               uint8_t * const p_tx_buf, const uint16_t tx_buf_len,
                               uint8_t * const p_rx_buf, const uint16_t rx_buf_len);


/**@brief Function for registration event handler.
*
* @note  Function registers a event handler to be used by SPI MASTER driver for sending events.
*        @ref SPI_MASTER_EVT_TRANSFER_STARTED and @ref SPI_MASTER_EVT_TRANSFER_COMPLETED.
*
* @param[in] spi_master_hw_instance    Instance of SPI master module.
* @param[in] event_handler             Generic callback function handler to be used
*                                      by all SPI master driver events.
*/
void spi_master_evt_handler_reg(const spi_master_hw_instance_t spi_master_hw_instance,
                                spi_master_event_handler_t event_handler);


/**@brief Function for getting current state of the SPI master driver.
 *
 * @note  Function gets current state of the SPI master driver.
 *
 * @param[in] spi_master_hw_instance   Instance of SPI master module.
 *
 * @retval SPI_MASTER_STATE_DISABLED   SPI MASTER is disabled.
 * @retval SPI_MASTER_STATE_BUSY       SPI_MASTER is sending now.
 * @retval SPI_MASTER_STATE_IDLE       SPI_MASTER is idle now.
 */
spi_master_state_t spi_master_get_state(const spi_master_hw_instance_t spi_master_hw_instance);

#ifdef _SPI_5W_

uint32_t spi_master_abort(const spi_master_hw_instance_t spi_master_hw_instance);

uint32_t spi_master_restart(const spi_master_hw_instance_t spi_master_hw_instance);

void spi_5W_master_evt_handler_reg(const spi_master_hw_instance_t spi_master_hw_instance,
                                         spi_master_event_handler_t event_handler);
#endif


#ifdef __cplusplus
}
#endif

#endif
