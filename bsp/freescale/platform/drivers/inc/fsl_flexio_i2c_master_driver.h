/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_FLEXIO_I2C_DRIVER_H
#define __FSL_FLEXIO_I2C_DRIVER_H

#include "fsl_flexio_i2c_hal.h"
#include "fsl_flexio_driver.h"
#include "fsl_os_abstraction.h"
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
#include "fsl_edma_driver.h"
#else
#include "fsl_dma_driver.h"
#endif

#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_i2c_master_driver
 * @{
 */
 
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Error codes for the FlexIO I2C driver. */
typedef enum flexio_i2c_status
{
    kStatus_FlexIO_I2C_Success                  = 0x00U, 
    kStatus_FlexIO_I2C_XBusy                    = 0x01U, 
    kStatus_FlexIO_I2C_NoTransmitInProgress     = 0x02U,
    kStatus_FlexIO_I2C_NoReceiveInProgress      = 0x03U, 
    kStatus_FlexIO_I2C_Timeout                  = 0x04U,
    kStatus_FlexIO_I2C_NoDataToDeal             = 0x05U,   
    kStatus_FlexIO_I2C_InvalidParam             = 0x06U,
    kStatus_FlexIO_I2C_DmaRequestFail           = 0x07U
} flexio_i2c_status_t;
/*! @brief Direction of master and slave transfers.*/
typedef enum flexio_i2c_direction {
    kFlexIOI2CWrite = 0U,   /*!< Master transmit, slave receive.*/
    kFlexIOI2CRead  = 1U    /*!< Master receive, slave transmit.*/
} flexio_i2c_direction_t;
/*! @brief I2C receive callback function type */
typedef void (* flexio_i2c_rx_callback_t)(void * i2cState);
/*! @brief Structure for write/read data from a specific memory address*/
typedef struct flexio_i2c_memrequest{
    const uint8_t * memAddress;
    uint32_t memAddrSize;
}flexio_i2c_memrequest_t;
/*!
 * @brief Runtime state structure for FlexIO I2C driver.
 */ 
typedef struct flexio_i2c_state {
    flexio_i2c_dev_t i2cDev;     /*!< FlexIO I2C Device configuration. */
    uint8_t *xBuff;              /*!< Transmit/receive buffer */
    volatile size_t xSize;       /*!< Transmit/receive size */
    volatile bool isXBusy;        /*!< True if there is an active transmit. */
    volatile bool isXBlocking;    /*!< True if transmit/receive is blocking transaction. */
    semaphore_t xIrqSync;      /*!< Used to wait for ISR to complete its transfer business. */
    flexio_i2c_rx_callback_t rxCallback; /*!< Callback to invoke after receiving byte.*/
    void * rxCallbackParam;        /*!< Receive callback parameter pointer.*/
    volatile bool isTxUseDma;    /*!< True if Tx DMA channel has already been configured. */
    volatile bool isRxUseDma;    /*!< True if Rx DMA channel has already been configured. */
}flexio_i2c_state_t;
/*!
 * @brief FlexIO I2C hardware resource configuration.
 *
 * These constants define the hardware resource used by FlexIO I2C master/slave device and include
 * the external pin and internal shifter and timer.
 * @internal gui name="I2C hardware configuration" id="i2cHwCfg"
 */
typedef struct flexio_i2c_hwconfig{
    uint32_t sdaPinIdx;      /*!< Data line. @internal gui name="SDA pin" id="SdaPin" */
    uint32_t sclkPinIdx;     /*!< Clock line. @internal gui name="SCL pin" id="SclPin" */
    uint32_t shifterIdx[2];  /*!< Shifter 0 is for transmit and shifter 1
                              * is for receive. @internal gui name="Shifter" id="i2cShifter" */
    uint32_t timerIdx[2]; /*!< Timer 0 is used to generate clock for clock line. 
                           * timer 1 is used to shift shifter @internal gui name="Timer" id="i2cTimer" */
}flexio_i2c_hwconfig_t;
/*!
 * @brief User configuration structure for the FlexIO I2C driver.
 *
 * Use an instance of this structure with the FLEXIO_I2C_DRV_Init()function. This enables configuration of the
 * settings of the FlexIO I2C peripheral with a single function call. Settings include:
 * I2C baud rate, data size, FlexIO I2C mode and FlexIO hardware resource
 * resource.
 * @internal gui name="I2C configuration" id="i2cCfg"
 */
typedef struct flexio_i2c_userconfig{
    uint32_t baudRate;    /*!< Baudrate configuration. @internal gui name="Baudrate" id="i2cBaudrate" */
    flexio_i2c_hwconfig_t i2cHwConfig;   /*!< FlexIO I2C Master Resource configuration. @internal gui name="Hardware configuration" */
}flexio_i2c_userconfig_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FlexIO I2C Driver
 * @{
 */

/*!
 * @brief Initializes a FlexIO-simulated I2C device.
 *
 * This function initializes the run-time state structure to keep track of
 * the on-going transfers and the module to user defined settings and 
 * default settings. It also configures the underlying FlexIO pin, shifter, and timer.
 * This is an example to set up the flexio_i2c_state_t and the
 * flexio_i2c_userconfig_t parameters and to call the FLEXIO_I2C_DRV_Init function
   @code
      flexio_i2c_userconif_t i2cMasterConfig;
      i2cMasterConfig.baudRate = 100000;
      i2cMasterConfig.i2cHwConfig.sdaPinIdx = 0;
      i2cMasterConfig.i2cHwConfig.sclkPinIdx = 1;
      i2cMasterConfig.i2cHwConfig.shifterIdx = {0,1};
      i2cMasterConfig.i2cHwConfig.timerIdx = {0,1};
   @endcode
 *
 * @param instance The FlexIO instance number.
 * @param i2cState A pointer to the global FlexIO I2C driver state structure memory. 
 *  The user passes in the memory for the run-time state structure. The FlexIO I2C driver
 *  populates the members. This run-time state structure keeps track of the
 *  current transfer in progress.
 * @param i2cMasterConfig The user configuration structure of type flexio_i2c_userconfig_t. 
 *  The user populates the members of this structure and passes the pointer of this structure
 *  to this function.
 * @return An error code or kStatus_FlexIO_I2C_Success.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterInit(uint32_t instance, flexio_i2c_state_t * i2cState,
                               const flexio_i2c_userconfig_t * i2cMasterConfig);
/*!
 * @brief Shuts down the FlexIO I2C.
 *
 * This function disables the FlexIO-simulated I2C trigger.
 *
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 */
void FLEXIO_I2C_DRV_MasterDeinit(flexio_i2c_state_t * i2cState);

/*!
 * @brief Sends (transmits) data out through the FlexIO-simulated I2C module using a 
 * blocking method.
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @param slaveAddr 7-bit or 10-bit slave address.
 * @param memRequest The memory request structure, including memory address and size,
 * if the operation is not a memory request, could pass NULL.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_I2C_Success.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterSendDataBlocking(flexio_i2c_state_t * i2cState,
                                                          uint16_t slaveAddr,
                                                          flexio_i2c_memrequest_t *memRequest,
                                                          uint8_t * txBuff,
                                                          uint32_t txSize,
                                                          uint32_t timeout);

/*!
 * @brief Sends (transmits) data through the FlexIO-simulated I2C module using a 
 * non-blocking method.
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @param slaveAddr 7-bit or 10-bit slave address.
 * @param memRequest The memory requests the structure, including memory address and size.
 * If the operation is not a memory request,  pass NULL.
 * @param txBuff A pointer to the source buffer containing 8-bit data chars to send.
 * @param txSize The number of bytes to send.
 * @return An error code or kStatus_FlexIO_I2C_Success.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterSendData(flexio_i2c_state_t * i2cState,
                                                  uint16_t slaveAddr,
                                                  flexio_i2c_memrequest_t *memRequest,
                                                  uint8_t * txBuff,
                                                  uint32_t txSize);
/*!
 * @brief Sends (transmits) slave address and register address(if a memory is requested) 
 * through the FlexIO-simulated I2C device.
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @param direction The direction of I2C operation, Read or Write.
 * @param slaveAddr 7-bit or 10-bit slave address.
 * @param memRequest The memory requests the structure, including memory address and size.
 * If the operation is not a memory request, pass NULL.
 * @return An error code or kStatus_FlexIO_I2C_Success.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterSendAddress(flexio_i2c_state_t *i2cState,
                                                     uint16_t slaveAddr,
						     flexio_i2c_direction_t direction,
                                                     flexio_i2c_memrequest_t *memRequest);
/*!
 * @brief Returns whether the previous FlexIO-simulated I2C transmit has finished.
 *
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes that
 *                       are remaining in the active transfer.
 * @return An error code or kStatus_FlexIO_I2C_Success.
 * @retval kStatus_FlexIO_I2C_Success The transmit has completed successfully.
 * @retval kStatus_FlexIO_I2C_TxBusy The transmit is still in progress. @a bytesTransmitted is
 *     filled with the number of bytes which are transmitted up to that point.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterGetTransmitStatus(flexio_i2c_state_t * i2cState, 
                                   uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated I2C transmission early.
 *
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @return An error code or kStatus_FlexIO_I2C_Success.
 * @retval kStatus_FlexIO_I2C_Success The transmit was successful.
 * @retval kStatus_FlexIO_I2C_NoTransmitInProgress No transmission is currently in progress.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterAbortSendingData(flexio_i2c_state_t * i2cState);

/*!
 * @brief Gets (receives) data from the FlexIO-simulated I2C module using a blocking method.
 *
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @param slaveAddr 7-bit or 10-bit slave address.
 * @param memRequest The memory requests the structure, including memory address and size.
 * If the operation is not a memory request, pass NULL.
 * @param rxBuff A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @param timeout A timeout value for RTOS abstraction sync control in milliseconds (ms).
 * @return An error code or kStatus_FlexIO_I2C_Success.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterReceiveDataBlocking(flexio_i2c_state_t * i2cState,
                                                             uint16_t slaveAddr,
                                                             flexio_i2c_memrequest_t *memRequest,
                                                             uint8_t * rxBuff,
                                                             uint32_t rxSize,
                                                             uint32_t timeout);
/*!
 * @brief Gets (receives) data from the FlexIO-simulated I2C module using a non-blocking method.
 *
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @param slaveAddr 7-bit or 10-bit slave address.
 * @param memRequest The memory requests the structure, including memory address and size.
 * If the operation is not a memory request, pass NULL.
 * @param rxBuff  A pointer to the buffer containing 8-bit read data chars received.
 * @param rxSize The number of bytes to receive.
 * @return An error code or kStatus_FlexIO_I2C_Success.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterReceiveData(flexio_i2c_state_t * i2cState,
                                                     uint16_t slaveAddr,
                                                     flexio_i2c_memrequest_t *memRequest,
                                                     uint8_t * rxBuff,
                                                     uint32_t rxSize);

/*!
 * @brief Returns whether the previous FlexIO-simulated I2C receive is complete.
 *
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @param bytesRemaining A pointer to a value that is populated with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return An error code or kStatus_FlexIO_I2C_Success.
 * @retval kStatus_FlexIO_I2C_Success The receive has completed successfully.
 * @retval kStatus_FlexIO_I2C_RxBusy The receive is still in progress. @a bytesReceived is
 *     filled with the number of bytes which are received up to that point.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterGetReceiveStatus(flexio_i2c_state_t * i2cState, 
                                  uint32_t * bytesRemaining);
/*!
 * @brief Terminates a non-blocking FlexIO-simulated I2C receive early.
 *
 * @param i2cState The run-time structure of FlexIO-simulated I2C.
 * @return An error code or kStatus_I2C_Success.
 * @retval kStatus_FlexIO_I2C_Success The receive was successful.
 * @retval kStatus_FlexIO_I2C_NoTransmitInProgress No receive is currently in progress.
 */
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterAbortReceivingData(flexio_i2c_state_t * i2cState);

/*!
 * @brief Interrupt handler for FlexIO-simulated I2C TX.
 * @param param The run-time structure of FlexIO simulated I2C.
 */
void FLEXIO_I2C_DRV_TX_IRQHandler(void *param);

/*!
 * @brief Interrupt handler for FlexIO-simulated I2C RX.
 * @param param The run-time structure of FlexIO simulated I2C.
 */
void FLEXIO_I2C_DRV_RX_IRQHandler(void *param);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif

#endif
