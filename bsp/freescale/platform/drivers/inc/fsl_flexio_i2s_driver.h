/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_FLEXIO_I2S_DRIVER_H__
#define __FSL_FLEXIO_I2S_DRIVER_H__


#include "fsl_flexio_i2s_hal.h"
#include "fsl_os_abstraction.h"
#include "fsl_flexio_driver.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
#include "fsl_edma_driver.h"
#else
#include "fsl_dma_driver.h"
#endif

#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_i2s_driver
 * @{
 */
 
/*! @brief Callback function of I2S */
typedef void (* i2s_callback) (void * param);

/*! @brief FlexIO I2S status */
typedef enum _flexio_i2s_status
{
    kStatus_FlexioI2S_Success = 0x0,
    kStatus_FlexioI2S_DeviceBusy = 0x1,
    kStatus_FlexioI2S_InvalidParameter = 0x2,
    kStatus_FlexioI2S_Fail = 0x3
} flexio_i2s_status_t;

/*! @brief Master or slave enumeration */
typedef enum _flexio_i2s_master_slave
{
    kFlexioI2SMaster = 0U,/*!< As a I2S master. @internal gui name="Master" */
    kFlexioI2SSlave = 1U /*!< As a I2S slave. @internal gui name="Slave" */
} flexio_i2s_master_slave_t;

/*!
 * @brief Define the audio data format 
 * @internal gui name="I2S configuration" id="i2sCfg"
 */
typedef struct flexioI2SConfig
{
    uint32_t txPinIdx;  /*!< Transmit pin. Output for cases of both master and slave. @internal gui name="Tx pin" id="TxPin" */
    uint32_t rxPinIdx;  /*!< Receive pin. Input for cases of both master and slave. @internal gui name="Rx pin" id="RxPin" */
    uint32_t sckPinIdx; /*!< Clock pin. Output for master, input for slave. @internal gui name="Sck pin" id="SckPin" */
    uint32_t wsPinIdx;  /*!< Word select pin. Output for master, input for slave. @internal gui name="Word select pin" id="WsPin" */
    uint32_t shifterIdx[2]; /*!< Selects two shifters. @internal gui name="Shifter" id="i2sShifter" */
    uint32_t timerIdx[2]; /*!< Selects two timers. @internal gui name="Timer" id="i2sTimer" */
    flexio_i2s_master_slave_t master_slave; /*!< Acts as master or slave @internal gui name="Mode" */
    uint32_t sample_rate; /*!< Sample rate in Hz. @internal gui name="Sample rate" */
    uint32_t data_depth; /*!< Data depth, can be 8, 16, 24, or 32 bits @internal gui name="Bits" */
    dma_request_source_t baseSource; /*!< DMA request source number for FlexIO pin0.  @internal gui name="DmaSource" */
} flexio_i2s_config_t; 

/*! @brief Defines the operation handler */
typedef struct FlexioI2SHandler
{
    flexio_i2s_dev_t device; /*!< Configuration of the FlexIO resource */
    uint8_t * tx_buffer; /*!< Transmit data buffer address. */
    uint8_t * rx_buffer; /*!< Receive data buffer address. */
    uint32_t tx_length; /*!< Bytes to send. */
    uint32_t rx_length; /*!< Bytes to receive.  */
    uint32_t tx_finished_bytes; /*!< Transferred bytes. */
    uint32_t rx_finished_bytes; /*!< Received bytes  */
    uint32_t sample_rate; /*!< Audio sample rate.*/
    uint32_t bit_depth; /*!< Data depth. */
    semaphore_t tx_sem; /*!< Semaphore for the completion of data send.  */
    semaphore_t rx_sem; /*!< Semaphore for the completion of data receive.  */
    bool tx_active; /*!< Tx means sending data. */
    bool rx_active; /*!< Rx means receiving data. */
    i2s_callback tx_callback; /*!< Transmit callback function. */
    i2s_callback rx_callback; /*!< Receive callback function. */
    void *tx_callback_param; /*!< Transmit callback parameter. */
    void *rx_callback_param; /*!< Receive callback parameter. */
    bool tx_use_dma; /*!< Whether transmit uses DMA. */
    bool rx_use_dma; /*!< Whether receive uses DMA. */
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    edma_chn_state_t tx_edma_state;
    edma_chn_state_t rx_edma_state;
    edma_software_tcd_t tx_edma_tcd[2];
    edma_software_tcd_t rx_edma_tcd[2];
#else
    dma_channel_t tx_dma_chn; /*!< DMA transmit channel structure */
    dma_channel_t rx_dma_chn; /*!< DMA receive channel structure. */
#endif
    dma_request_source_t baseSource;
} flexio_i2s_handler_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FlexIO I2S Driver
 * @{
 */

/*! @brief Initializes the I2S transfer using the FlexIO.
 *
 * This interface transfers the FlexIO resource structure to a function which
 * configures the pin/timer/shifter to act as an I2S master/slave.
 *
 * @param instance FlexIO I2S instance.
 * @param handler FlexIO I2S handler; Transfer memory to the
 * driver and this memory is used until deinitialization function is called.
 * @param userConfig The user configuration structure of type flexio_i2c_userconfig_t. 
 *  The user populates the members of this structure and passes the pointer of this structure
 *  to this function.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_Init(uint32_t instance, flexio_i2s_handler_t *handler, 
        const flexio_i2s_config_t *userConfig);

/*! @brief De-initializes the FlexIO I2S.
 *
 * This function does not free  the FlexIO resource. It only clears the internal state.
 * @param handler FlexIO I2S handler.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_Deinit(flexio_i2s_handler_t *handler);

/*! @brief Starts the I2S transfer.
 *
 * @param handler FlexIO I2S handler.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_TxStart(flexio_i2s_handler_t *handler);

/*! @brief Starts the I2S receive.
 *
 * @param handler FlexIO I2S handler.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_RxStart(flexio_i2s_handler_t *handler);

/*! @brief Stops the I2S transfer.
 *
 * @param handler FlexIO I2S handler.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_TxStop(flexio_i2s_handler_t *handler);

/*! @brief Stops the I2S receive.
 *
 * @param handler FlexIO I2S handler.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_RxStop(flexio_i2s_handler_t *handler);

/*! @brief Sends data as an interrupt. 
 *
 * @param handler FlexIO I2S handler.
 * @param addr Start address of data to send.
 * @param len Bytes to send.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_SendDataInt(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len);

/*! @brief Receives data as an interrupt.
 *
 * @param handler FlexIO I2S handler.
 * @param addr Start address of data to receive.
 * @param len Bytes to receive.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_ReceiveDataInt(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len);

/*! @brief Sends data using the DMA. 
 *
 * @param handler FlexIO I2S handler.
 * @param addr Start address of data to transfer.
 * @param len Bytes to transfer.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_SendDataDma(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len);

/*! @brief Receives data using the DMA.
 * 
 * @param handler FlexIO I2S handler
 * @param addr Start address of data to receive.
 * @param len Bytes to receive.
 * @return An error code or kStatus_FlexioI2S_Success.
 */
flexio_i2s_status_t FLEXIO_I2S_DRV_ReceiveDataDma(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len);

/*! @brief Installs the callback function for complete data sending.
 *
 * The user-defined callback function is called by the transmit interrupt handler or the transfer DMA/eDMA
 * callback function.
 * @param handler FlexIO I2S handler.
 * @param callback User-defined callback function pointer.
 * @param param User-defined callback function parameter. It should be a void pointer.
 */
void FLEXIO_I2S_DRV_TxInstallCallback(flexio_i2s_handler_t *handler, i2s_callback callback,
    void *param);

/*! @brief Installs the callback function for complete data receiving.
 *
 * The user-defined callback function is called by the receive interrupt handler or the receive DMA/eDMA
 * callback function.
 * @param handler FlexIO I2S handler.
 * @param callback User-defined callback function pointer.
 * @param param User-defined callback function parameter. It should be a void pointer.
 */
void FLEXIO_I2S_DRV_RxInstallCallback(flexio_i2s_handler_t *handler, i2s_callback callback,
    void *param);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif

#endif /* __FSL_FLEXIO_I2S_DRIVER_H__ */

