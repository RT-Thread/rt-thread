/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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

#ifndef __FSL_FLEXIO_I2C_HAL_H__
#define __FSL_FLEXIO_I2C_HAL_H__

#include <stdint.h>
#include <stdbool.h>

#include "fsl_flexio_hal.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_i2c_hal
 * @{
 */

/*!
 * @brief Define structure of configuring the flexio i2c device. 
 */
typedef struct FlexioI2cDev
{
    FLEXIO_Type * flexioBase; /*!< FlexIO module base pointer. */
    
    uint32_t sdaPinIdx;       /*!< Pin index for I2C SDA in FlexIO. */
    uint32_t sckPinIdx;       /*!< Pin index for I2C SCK in FlexIO. */

    uint32_t shifterIdx[2];   /*!< Shifter index used for I2C in FlexIO. */
    uint32_t timerIdx[2];     /*!< Timer index used for I2C in FlexIO. */
} flexio_i2c_dev_t;

/*!
 * @brief Define structure of configuring the flexio i2c bus for master. 
 */
typedef struct FlexioI2cMasterConfig
{
    uint32_t flexioBusClk;  /*!< FlexIO bus clock frequency in Hz. */
    uint32_t baudrate;		/*!< I2C xfer bandrate in bps. */
    uint32_t xferWordCount; /*!< Word count for one transfer frame. */
} flexio_i2c_master_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*---------------------------------------------------------------------------
 * Configure.
 *-------------------------------------------------------------------------*/
/*!
 * @brief Configure the flexio working as i2c master device.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_I2C_HAL_ConfigMaster(flexio_i2c_dev_t *devPtr,  const flexio_i2c_master_config_t *configPtr);

/*!
 * @brief Configure the count of words for each frame.
 *
 * When using flexio_i2c_master, each frame's length should be configured
 * before sending any word. Of course, when calling the FLEXIO_I2C_HAL_ConfigMaster(),
 * user can set the "configPtr->xferWrodCount" to set word count. However, this
 * API could provide the light-weight setting without changing any other settings.
 *
 * @param devPtr Pointer to the device.
 * @param count Word count for each frame.
 * @return Execution status.
 */
flexio_status_t FLEXIO_I2C_HAL_ConfigXferWordCountOnce(flexio_i2c_dev_t *devPtr, uint32_t count);

/*---------------------------------------------------------------------------
 * Tx.
 *-------------------------------------------------------------------------*/
/*!
 * @brief Get the flag if the rx buffer is empty.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2C_HAL_GetTxBufferEmptyFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Clear the flag of tx buffer empty manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2C_HAL_ClearTxBufferEmptyFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for tx buffer is empty.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2C_HAL_SetTxBufferEmptyIntCmd(flexio_i2c_dev_t *devPtr, bool enable);

/*!
 * @brief Get the tx error flag.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2C_HAL_GetTxErrFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Clear the tx error flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2C_HAL_ClearTxErrFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for tx error.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2C_HAL_SetTxErrIntCmd(flexio_i2c_dev_t *devPtr, bool enable);

/*!
 * @brief Put data into tx buffer.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_I2C_HAL_PutData(flexio_i2c_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Put data into tx buffer when empty.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_I2C_HAL_PutDataPolling(flexio_i2c_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Switch on/off the tx DMA support.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2C_HAL_SetTxDmaCmd(flexio_i2c_dev_t *devPtr, bool enable);

/*!
 * @brief Get address of tx buffer when using DMA.
 *
 * @param devPtr Pointer to the device.
 * @return Address of tx buffer.
 */
uint32_t FLEXIO_I2C_HAL_GetTxBufferAddr(flexio_i2c_dev_t *devPtr);

/*---------------------------------------------------------------------------
 * Rx.
 *-------------------------------------------------------------------------*/
/*!
 * @brief Get the flag that rx buffer is full.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2C_HAL_GetRxBufferFullFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Clear the rx buffer empty flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2C_HAL_ClearRxBufferFullFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for rx buffer is full.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2C_HAL_SetRxBufferFullIntCmd(flexio_i2c_dev_t *devPtr, bool enable);

/*!
 * @brief Get the rx error flag.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2C_HAL_GetRxErrFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Clear the rx error flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2C_HAL_ClearRxErrFlag(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for rx error.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2C_HAL_SetRxErrIntCmd(flexio_i2c_dev_t *devPtr, bool enable);

/*!
 * @brief Get the data from tx buffer.
 *
 * @param devPtr Pointer to the device.
 * @return Data from rx buffer.
 */
uint32_t FLEXIO_I2C_HAL_GetData(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Get the data from tx buffer when full.
 *
 * @param devPtr Pointer to the device.
 * @return Data from rx buffer.
 */
uint32_t FLEXIO_I2C_HAL_GetDataPolling(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Switch on/off the rx DMA support.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2C_HAL_SetRxDmaCmd(flexio_i2c_dev_t *devPtr, bool enable);

/*!
 * @brief Get the address the of rx buffer.
 *
 * @param devPtr Pointer to the device.
 * @return Address of rx buffer.
 */
uint32_t FLEXIO_I2C_HAL_GetRxBufferAddr(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Configure the next sending would generate NACK condition.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2C_HAL_ConfigSendNAck(flexio_i2c_dev_t *devPtr);

/*!
 * @brief Configure the next sending would generate ACK condition.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2C_HAL_ConfigSendAck(flexio_i2c_dev_t *devPtr);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_FLEXIO_I2C_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

