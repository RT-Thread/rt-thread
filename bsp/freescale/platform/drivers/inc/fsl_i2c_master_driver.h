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
#ifndef __FSL_I2C_MASTER_DRIVER_H__
#define __FSL_I2C_MASTER_DRIVER_H__

#include <stdlib.h>
#include <stdbool.h>
#include "fsl_i2c_hal.h"
#include "fsl_os_abstraction.h"

/*!
 * @addtogroup i2c_master
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for I2C instances. */
extern I2C_Type * const g_i2cBase[I2C_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! 
 * @brief Information necessary to communicate with an I2C slave device.
 * @internal gui name="Master configuration" id="i2cMasterCfg"
 */
typedef struct I2CDevice 
{
    uint16_t address;        /*!< Slave's 7-bit or 10-bit address. If 10-bit address,
                                  the first 6 bits must be 011110 in binary. @internal gui name="Address" id="Address" */
    uint32_t baudRate_kbps; /*!< The baud rate in kbps to use by current slave device. @internal gui name="Baudrate" id="BaudRate" */
} i2c_device_t;

/*!
 * @brief Internal driver state information.
 *
 * @note The contents of this structure are internal to the driver and should not be
 *      modified by users. Also, contents of the structure are subject to change in
 *      future releases.
 */
typedef struct I2CMasterState {
    uint8_t * rxBuff;
    volatile uint32_t rxSize;
    const uint8_t * txBuff;
    volatile uint32_t txSize;
    volatile i2c_status_t status;
    volatile bool i2cIdle;
    bool isBlocking;
    bool isRequesting;
    uint32_t lastBaudRate_kbps;
    semaphore_t irqSync;
} i2c_master_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name I2C Master
 * @{
 */

/*!
 * @brief Initializes the I2C master mode driver.
 *
 * @param instance The I2C peripheral instance number.
 * @param master   The pointer to the I2C master driver state structure.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_MasterInit(uint32_t instance, i2c_master_state_t * master);

/*!
 * @brief Shuts down the driver.
 *
 * @param instance The I2C peripheral instance number.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_MasterDeinit(uint32_t instance);

/*!
 * @brief Configures the I2C bus to access a device.
 *
 * @param instance The I2C peripheral instance number.
 * @param device   The pointer to the I2C device information structure.
 */
void I2C_DRV_MasterSetBaudRate(uint32_t instance, const i2c_device_t * device);

/*!
 * @brief Performs a blocking send transaction on the I2C bus.
 *
 * Both cmdBuff and txBuff are byte aligned, user needs to prepare these buffers
 * according to related protocol if slave devices data are not byte-aligned. 
 *
 * @param instance    The I2C peripheral instance number.
 * @param device      The pointer to the I2C device information structure.
 * @param cmdBuff     The pointer to the commands to be transferred, could be NULL.
 * @param cmdSize     The length in bytes of the commands to be transferred, could be 0.
 * @param txBuff      The pointer to the data to be transferred, cannot be NULL.
 * @param txSize      The length in bytes of the data to be transferred, cannot be 0.
 * @param timeout_ms  A timeout for the transfer in microseconds.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_MasterSendDataBlocking(uint32_t instance,
                                            const i2c_device_t * device,
                                            const uint8_t * cmdBuff,
                                            uint32_t cmdSize,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            uint32_t timeout_ms);

/*!
 * @brief Performs a non-blocking send transaction on the I2C bus.
 *
 * This function returns immediately when set buffer pointer and length to transfer buffer and
 * transfer Size. The user must check the status of I2C to know the whether transmission
 * is finished or not.
 * Both cmdBuff and txBuff are byte aligned, user needs to prepare these buffers
 * according to related protocol if slave devices data are not byte-aligned. 
 *
 * @param instance    The I2C peripheral instance number.
 * @param device      The pointer to the I2C device information structure.
 * @param cmdBuff     The pointer to the commands to be transferred,could be NULL.
 * @param cmdSize     The length in bytes of the commands to be transferred, could be 0.
 * @param txBuff      The pointer to the data to be transferred, cannot be NULL.
 * @param txSize      The length in bytes of the data to be transferred, cannot be 0.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_MasterSendData(uint32_t instance,
                                    const i2c_device_t * device,
                                    const uint8_t * cmdBuff,
                                    uint32_t cmdSize,
                                    const uint8_t * txBuff,
                                    uint32_t txSize);

/*!
 * @brief Gets the current status of the I2C master transmit.
 *
 * This function gets the current I2C status of the non-blocking transmit.
 *
 * @param instance Instance number of the I2C module.
 * @param bytesRemaining  The number of remaining bytes in the active I2C transmits.
 * @return Current status of I2C transmission: in progress (busy) or complete (success).
 */
i2c_status_t I2C_DRV_MasterGetSendStatus(uint32_t instance, uint32_t *bytesRemaining);

/*!
 * @brief Terminates a non-blocking I2C Master transmission early.
 *
 * @param instance Instance number of the I2C module.
 * @return Whether the aborting is success or not.
 */
i2c_status_t I2C_DRV_MasterAbortSendData(uint32_t instance);

/*!
 * @brief Performs a blocking receive transaction on the I2C bus.
 *
 * Both cmdBuff and rxBuff are byte aligned, user needs to prepare these buffers
 * according to related protocol if slave devices data are not byte-aligned. 
 *
 * @param instance    The I2C peripheral instance number.
 * @param device      The pointer to the I2C device information structure.
 * @param cmdBuff     The pointer to the commands to be transferred, could be NULL.
 * @param cmdSize     The length in bytes of the commands to be transferred, could be 0.
 * @param rxBuff      The pointer to the data to be transferred, cannot be NULL.
 * @param rxSize      The length in bytes of the data to be transferred, cannot be 0.
 * @param timeout_ms  A timeout for the transfer in microseconds.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_MasterReceiveDataBlocking(uint32_t instance,
                                               const i2c_device_t * device,
                                               const uint8_t * cmdBuff,
                                               uint32_t cmdSize,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize,
                                               uint32_t timeout_ms);

/*!
 * @brief Performs a non-blocking receive transaction on the I2C bus.
 *
 * This function returns immediately after set buffer pointer and length to the receive buffer and
 * the receive size. The user must check the status of I2C to know the whether the receiving
 * is finished or not.
 * Both cmdBuff and rxBuff are byte aligned, user needs to prepare these buffers
 * according to related protocol if slave devices data are not byte-aligned. 
 *
 * @param instance    The I2C peripheral instance number.
 * @param device      The pointer to the I2C device information structure.
 * @param cmdBuff     The pointer to the commands to be transferred, could be NULL.
 * @param cmdSize     The length in bytes of the commands to be transferred, could be 0.
 * @param rxBuff      The pointer to the data to be transferred, cannot be NULL.
 * @param rxSize      The length in bytes of the data to be transferred, cannot be 0.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_MasterReceiveData(uint32_t  instance,
                                       const i2c_device_t * device,
                                       const uint8_t * cmdBuff,
                                       uint32_t cmdSize,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize);

/*!
 * @brief Gets the current status of the I2C master receive.
 *
 * This function is designed to get the current I2C status of a non-blocking receive.
 *
 * @param instance Instance number of the I2C module.
 * @param bytesRemaining  The number of remaining bytes in the active I2C transmits.
 * @return Current status of I2C receive: in progress (busy) or complete (success).
 */
i2c_status_t I2C_DRV_MasterGetReceiveStatus(uint32_t instance,
                                            uint32_t *bytesRemaining);

/*!
 * @brief Performs a polling receive transaction on the I2C bus.
 *
 * Both cmdBuff and rxBuff are byte aligned. The user needs to prepare these buffers
 * according to the related protocol if the slave device data is not byte-aligned. 
 *
 * @param instance  Instance number of the I2C module.
 * @param slaveAddr The slave address to communicate.
 * @param cmdBuff   The pointer to the commands to be transferred, could be NULL.
 * @param cmdSize   The length in bytes of the commands to be transferred, could be 0.
 * @param rxBuff    The pointer to the data to be transferred, cannot be NULL.
 * @param rxSize    The length in bytes of the data to be transferred, cannot be 0.
 * @return Error or success status returned by API.
 */
static inline i2c_status_t I2C_DRV_MasterReceiveDataPolling(uint32_t instance,
                                                            uint16_t slaveAddr,
                                                            const uint8_t * cmdBuff,
                                                            uint32_t cmdSize,
                                                            uint8_t * rxBuff,
                                                            uint32_t rxSize)
{

    return I2C_HAL_MasterReceiveDataPolling(g_i2cBase[instance], slaveAddr,
                                            cmdBuff, cmdSize, rxBuff, rxSize);
}

/*!
 * @brief Performs a polling send transaction on the I2C bus.
 *
 * Both cmdBuff and txBuff are byte aligned. The user needs to prepare these buffers
 * according to the related protocol if the slave device data is not byte-aligned. 
 *
 * @param instance  Instance number of the I2C module.
 * @param slaveAddr The slave address to communicate.
 * @param cmdBuff   The pointer to the commands to be transferred, could be NULL.
 * @param cmdSize   The length in bytes of the commands to be transferred, could be 0.
 * @param txBuff    The pointer to the data to be transferred, cannot be NULL.
 * @param txSize    The length in bytes of the data to be transferred, cannot be 0.
 * @return Error or success status returned by API.
 */
static inline i2c_status_t I2C_DRV_MasterSendDataPolling(uint32_t instance,
                                                         uint16_t slaveAddr,
                                                         const uint8_t * cmdBuff,
                                                         uint32_t cmdSize,
                                                         const uint8_t * txBuff,
                                                         uint32_t txSize)
{
    return I2C_HAL_MasterSendDataPolling(g_i2cBase[instance], slaveAddr,
                                         cmdBuff, cmdSize, txBuff, txSize);

}

/*!
 * @brief The interrupt handler for I2C master mode
 *
 * @param instance  Instance number of the I2C module.
 */
void I2C_DRV_MasterIRQHandler(uint32_t instance);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_I2C_MASTER_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

