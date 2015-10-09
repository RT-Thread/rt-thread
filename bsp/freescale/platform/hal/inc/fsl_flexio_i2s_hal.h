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

#ifndef __FSL_FLEXIO_I2S_HAL_H__
#define __FSL_FLEXIO_I2S_HAL_H__

#include "fsl_flexio_hal.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_i2s_hal
 * @{
 */

/*!
 * @brief Define type of FlexIO I2S device.
 */
typedef struct FlexioI2sDev
{
    FLEXIO_Type * flexioBase; /*!< FlexIO module base address. */  
    /* User-defined pin for I2S. */
    uint32_t txPinIdx;  /*!< output for cases of both master and slave. */
    uint32_t rxPinIdx;  /*!< input for cases of both master and slave. */
    uint32_t sckPinIdx; /*!< output for master, input for slave. */
    uint32_t wsPinIdx;  /*!< output for master, input for slave. */
    /* Internal hardware resource. */
    uint32_t shifterIdx[2]; /*!< Shifter index used for I2S in FlexIO. */
    uint32_t timerIdx[2];   /*!< Timer index used for I2S in FlexIO. */
} flexio_i2s_dev_t;

/*!
 * @brief Define type of I2S master device configuration structure.
 */
typedef struct FlexioI2sMasterConfig
{
    uint32_t flexioBusClk;  /*!< Flexio bus clock in Hz. */
    uint32_t bitClk;        /*!< Bit clock in Hz. */
    uint32_t bitCount;      /*!< Bit count for each work. */
} flexio_i2s_master_config_t;

/*!
 * @brief Define type of I2S slave device configuration structure.
 */
typedef struct FlexioI2sSlaveConfig
{
    uint32_t bitCount;     /*!< Bit count for each work. */
} flexio_i2s_slave_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*---------------------------------------------------------------------------
 * Configure.
 *-------------------------------------------------------------------------*/
/*!
 * @brief Configure the flexio working as i2s master device.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_I2S_HAL_Configure_Master(
    flexio_i2s_dev_t *devPtr, const flexio_i2s_master_config_t *configPtr);

/*!
 * @brief Configure the flexio working as i2s slave device.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_I2S_HAL_Configure_Slave(
    flexio_i2s_dev_t *devPtr, const flexio_i2s_slave_config_t *configPtr);

/*---------------------------------------------------------------------------
 * Tx.
 *-------------------------------------------------------------------------*/
/* Status flag and interrupt. */
/*!
 * @brief Get the flag that tx buffer is empty.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2S_HAL_GetTxBufferEmptyFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Clear the tx buffer empty flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2S_HAL_ClearTxBufferEmptyFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for tx buffer empty.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2S_HAL_SetTxBufferEmptyIntCmd(flexio_i2s_dev_t *devPtr, bool enable);

/*!
 * @brief Get the current setting of interrupt switcher.
 *
 * @param devPtr Pointer to the device.
 * @return The setting of event.
 */
bool FLEXIO_I2S_HAL_GetTxBufferEmptyIntCmd(flexio_i2s_dev_t *devPtr);

/* Error flag and interrupt. */
/*!
 * @brief Get the rx error flag.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2S_HAL_GetTxErrFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Clear the tx error flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2S_HAL_ClearTxErrFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for tx error.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2S_HAL_SetTxErrIntCmd(flexio_i2s_dev_t *devPtr, bool enable);

/* Data buffer. */
/*!
 * @brief Put the data into tx buffer.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_I2S_HAL_PutData(flexio_i2s_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Put the data into tx buffer when empty.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_I2S_HAL_PutDataPolling(flexio_i2s_dev_t *devPtr, uint32_t dat);

/* DMA. */
/*!
 * @brief Switch on/off the tx DMA support.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2S_HAL_SetTxDmaCmd(flexio_i2s_dev_t *devPtr, bool enable);

/*!
 * @brief Get the address of tx buffer when using DMA. 
 *
 * @param devPtr Pointer to the device.
 * @return Address of tx buffer.
 */
uint32_t FLEXIO_I2S_HAL_GetTxBufferAddr(flexio_i2s_dev_t *devPtr);

/*---------------------------------------------------------------------------
 * Rx.
 *-------------------------------------------------------------------------*/
/* Status flag and interrupt. */
/*!
 * @brief Get the flag if the rx buffer is full.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2S_HAL_GetRxBufferFullFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Clear the rx buffer full flag.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2S_HAL_ClearRxBufferFullFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for rx buffer full.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2S_HAL_SetRxBufferFullIntCmd(flexio_i2s_dev_t *devPtr, bool enable);

/*!
 * @brief Get the current setting of tx buffer full interrupt.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of event.
 */
bool FLEXIO_I2S_HAL_GetRxBufferFullIntCmd(flexio_i2s_dev_t *devPtr);

/* Error flag and interrupt. */
/*!
 * @brief Get the flag if rx error.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_I2S_HAL_GetRxErrFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Clear the rx error flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_I2S_HAL_ClearRxErrFlag(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for rx error event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Swichter to the event.
 */
void FLEXIO_I2S_HAL_SetRxErrIntCmd(flexio_i2s_dev_t *devPtr, bool enable);

/* Data buffer. */
/*!
 * @brief Get the data from rx buffer.
 *
 * @param devPtr Pointer to the device.
 * @return Reading data.
 */
uint32_t FLEXIO_I2S_HAL_GetData(flexio_i2s_dev_t *devPtr);

/*!
 * @brief Get the data from rx buffer when full.
 *
 * @param devPtr Pointer to the device.
 * @return Reading data.
 */
uint32_t FLEXIO_I2S_HAL_GetDataPolling(flexio_i2s_dev_t *devPtr);

/* DMA. */
/*!
 * @brief Switch on/off the rx DMA support.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_I2S_HAL_SetRxDmaCmd(flexio_i2s_dev_t *devPtr, bool enable);

/*!
 * @brief Get the address of rx buffer when using DMA.
 *
 * @param devPtr Pointer to the device.
 * @return Address of rx buffer.
 */
uint32_t FLEXIO_I2S_HAL_GetRxBufferAddr(flexio_i2s_dev_t *devPtr);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_FLEXIO_I2S_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

