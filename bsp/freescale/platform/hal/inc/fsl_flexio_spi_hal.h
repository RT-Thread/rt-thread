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

#ifndef __FSL_FLEXIO_SPI_HAL_H__
#define __FSL_FLEXIO_SPI_HAL_H__

#include "fsl_flexio_hal.h"

/*!
 * @addtogroup flexio_spi_hal
 * @{
 */

/*!
 * @brief Define structure of configuring the flexio spi device. 
 */
typedef struct
{
    FLEXIO_Type * flexioBase; /*!< FlexIO module base address. */
    /* User-defined pin for SPI master. */
    uint32_t txPinIdx;   /*!< Output pin index. */
    uint32_t rxPinIdx;   /*!< Input pin index. */
    uint32_t sclkPinIdx; /*!< Clock line, output for master, input for slave. */
    uint32_t csnPinIdx;  /*!< Chip select line, output for master, input for slave. */
    /* Internal hardware resource. */
    uint32_t shifterIdx[2]; /*!< Shifter index. */
    uint32_t timerIdx[2]; /*!< Timer index.
                           * timer 0 is available for both master and slave. 
                           * timer 1 would be only available for master 
                           * and not used in slave mode. */
} flexio_spi_dev_t;

/*!
 * @brief Define structure of configuring the flexio spi bus when master. 
 */
typedef struct 
{
    uint32_t flexioBusClk; /*!< Clock frequency of flexio bus. */
    uint32_t baudrate;     /*!< Baudrate for spi bus. */
    uint32_t bitCount;     /*!< Bit count for each word. */
    bool cphaOneEnable;    /*!< The phase of spi. */
} flexio_spi_master_config_t;

/*!
 * @brief Define structure of configuring the flexio spi bus when slave. 
 */
typedef struct 
{
    uint32_t bitCount;      /*!< Bit count for each word. */
    bool cphaOneEnable;     /*!< The phase of spi. */
} flexio_spi_slave_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*---------------------------------------------------------------------------
 * Configure.
 *-------------------------------------------------------------------------*/
/*!
 * @brief Configure the flexio working as spi master.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to the configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_SPI_HAL_ConfigMaster(flexio_spi_dev_t *devPtr, const flexio_spi_master_config_t *configPtr);

/*!
 * @brief Configure the flexio working as spi slave.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to the configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_SPI_HAL_ConfigSlave(flexio_spi_dev_t *devPtr, const flexio_spi_slave_config_t *configPtr);

/*---------------------------------------------------------------------------
 * Tx.
 *-------------------------------------------------------------------------*/
/*!
 * @brief Get the flag if the tx buffer is empty.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_SPI_HAL_GetTxBufferEmptyFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Clear the flag that tx buffer is empty.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_SPI_HAL_ClearTxBufferEmptyFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for event of tx buffer empty.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(flexio_spi_dev_t *devPtr, bool enable);

/*!
 * @brief Get the flag of tx error.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of the event.
 */
bool FLEXIO_SPI_HAL_GetTxErrFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Clear the flag of tx error manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_SPI_HAL_ClearTxErrFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt for tx error event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_SPI_HAL_SetTxErrIntCmd(flexio_spi_dev_t *devPtr, bool enable);

/*!
 * @brief Put the data to tx buffer as MSB transfer.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_SPI_HAL_PutDataMSB(flexio_spi_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Put the data to tx buffer as MSB transfer when empty.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_SPI_HAL_PutDataMSBPolling(flexio_spi_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Put the data to tx buffer as LSB transfer.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_SPI_HAL_PutDataLSB(flexio_spi_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Put the data to tx buffer as LSB transfer when empty.
 *
 * @param devPtr Pointer to the device.
 * @param dat Sending data.
 */
void FLEXIO_SPI_HAL_PutDataLSBPolling(flexio_spi_dev_t *devPtr, uint32_t dat);

/*!
 * @brief Switch on/off the DMA support for tx event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_SPI_HAL_SetTxDmaCmd(flexio_spi_dev_t *devPtr, bool enable);

/*!
 * @brief Get the tx MSB buffer's register for DMA use.
 *
 * @param devPtr Pointer to the device.
 * @return Address of tx MSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetTxBufferMSBAddr(flexio_spi_dev_t *devPtr);

/*!
 * @brief Get the tx LSB buffer's register for DMA use.
 *
 * @param devPtr Pointer to the device.
 * @return Address of tx LSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetTxBufferLSBAddr(flexio_spi_dev_t *devPtr);

/*---------------------------------------------------------------------------
 * Rx.
 *-------------------------------------------------------------------------*/

/*!
 * @brief Get the flag if the rx buffer is full.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of event.
 */
bool FLEXIO_SPI_HAL_GetRxBufferFullFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Clear the flag of rx buffer full manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_SPI_HAL_ClearRxBufferFullFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt of rx buffer full event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(flexio_spi_dev_t *devPtr, bool enable);

/*!
 * @brief Get the flag of rx error.
 *
 * @param devPtr Pointer to the device.
 * @return Assertion of event.
 */
bool FLEXIO_SPI_HAL_GetRxErrFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Clear the flag of rx error manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_SPI_HAL_ClearRxErrFlag(flexio_spi_dev_t *devPtr);

/*!
 * @brief Switch on/off the interrupt of the rx error event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_SPI_HAL_SetRxErrIntCmd(flexio_spi_dev_t *devPtr, bool enable);

/*!
 * @brief Get the data from rx MSB buffer. 
 *
 * @param devPtr Pointer to the device.
 * @return Data from rx MSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetDataMSB(flexio_spi_dev_t *devPtr);

/*!
 * @brief Get the data from rx MSB buffer when full.
 *
 * @param devPtr Pointer to the device.
 * @return Data from rx MSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetDataMSBPolling(flexio_spi_dev_t *devPtr);

/*!
 * @brief Get the data from rx LSB buffer.
 *
 * @param devPtr Pointer to the device.
 * @return Data from rx LSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetDataLSB(flexio_spi_dev_t *devPtr);

/*!
 * @brief Get the data from rx LSB buffer when full.
 *
 * @param devPtr Pointer to the device.
 * @return Data from rx LSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetDataLSBPolling(flexio_spi_dev_t *devPtr);

/*!
 * @brief Swtich on/off the DMA for rx event.
 *
 * @param devPtr Pointer to the device.
 * @param enable Switcher to the event.
 */
void FLEXIO_SPI_HAL_SetRxDmaCmd(flexio_spi_dev_t *devPtr, bool enable);

/*!
 * @brief Get the address of rx MSB buffer.
 *
 * @param devPtr Pointer to the device.
 * @return Address of rx MSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetRxBufferMSBAddr(flexio_spi_dev_t *devPtr);

/*!
 * @brief Get the address of rx LSB buffer.
 *
 * @param devPtr Pointer to the device.
 * @return Address of rx MSB buffer.
 */
uint32_t FLEXIO_SPI_HAL_GetRxBufferLSBAddr(flexio_spi_dev_t *devPtr);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __FSL_FLEXIO_SPI_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

