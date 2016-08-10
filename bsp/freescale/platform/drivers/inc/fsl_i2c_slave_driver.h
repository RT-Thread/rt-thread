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
#ifndef __FSL_I2C_SLAVE_H__
#define __FSL_I2C_SLAVE_H__

#include <stdint.h>
#include "fsl_i2c_hal.h"
#include "fsl_os_abstraction.h"


/*!
 * @addtogroup i2c_slave
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Table of base addresses for I2C instances. */
extern I2C_Type * const g_i2cBase[I2C_INSTANCE_COUNT];
extern void * g_i2cStatePtr[I2C_INSTANCE_COUNT];
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Internal driver state information.
 *
 * @note The contents of this structure are internal to the driver and should not be
 *      modified by users. Also, contents of the structure are subject to change in
 *      future releases.
 */

/*!
 * @brief Defines the type of flags for callback function
 */
typedef enum _i2c_slave_event
{
#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    kI2CSlaveStartDetect  = 0x01u,   /*!< The slave I2C detecting START signal event. */
#endif
    kI2CSlaveTxReq   = 0x02u,        /*!< The slave I2C Transmitting Request event. */
    kI2CSlaveRxReq   = 0x04u,        /*!< The slave I2C Receiving Request event. */
    kI2CSlaveTxNAK   = 0x08u,        /*!< The slave I2C Transmitting NAK event. */
    kI2CSlaveTxEmpty = 0x10u,        /*!< The slave I2C Transmitting Buffer Empty event. */
    kI2CSlaveRxFull  = 0x20u,        /*!< The slave I2C Receiving Buffer Full event. */
    kI2CSlaveAbort   = 0x40u,        /*!< The slave I2C Slave abort transaction event.*/
#if (FSL_FEATURE_I2C_HAS_START_STOP_DETECT || FSL_FEATURE_I2C_HAS_STOP_DETECT)
    kI2CSlaveStopDetect = 0x80u,     /*!< The slave I2C detecting STOP signal event.*/
#endif
} i2c_slave_event_t;

/*! @brief I2C slave callback function */
typedef void (*i2c_slave_callback_t)(uint8_t instance,i2c_slave_event_t slaveEvent,void *userData);

/*!
 * @brief Runtime state of the I2C Slave driver.
 *
 * This structure holds data used by the I2C Slave Peripheral driver to
 * communicate between the transfer function and the interrupt handler. The
 * interrupt handler also uses this information to keep track of its progress.
 */
typedef struct I2CSlaveState
{
    i2c_status_t status;                 /*!< The slave I2C status. */
    volatile uint32_t txSize;            /*!< Size of the TX buffer.*/
    volatile uint32_t rxSize;            /*!< Size of the RX buffer.*/
    const uint8_t *txBuff;               /*!< Pointer to Tx Buffer.*/
    uint8_t *rxBuff;                     /*!< Pointer to Rx Buffer.*/
    bool isTxBusy;                       /*!< True if the driver is sending data.*/
    bool isRxBusy;                       /*!< True if the driver is receiving data.*/
    bool isTxBlocking;                   /*!< True if transmit is blocking transaction. */
    bool isRxBlocking;                   /*!< True if receive is blocking transaction. */
    event_t irqEvent;                    /*!< Use to wait for ISR to complete its Tx, Rx business */
    bool slaveListening;                 /*!< True if slave is in listening mode. */
    i2c_slave_callback_t slaveCallback;  /*!< Pointer to user callback function. */
    void *callbackParam;                 /*!< Pointer to user callback param. */
} i2c_slave_state_t;

/*!
 * @brief Defines the structure to initialize the I2C Slave module.
 *
 * @note once slaveListening mode is selected, all send/receive
 * blocking/non-blocking functions will be invalid.
 * @internal gui name="Slave configuration" id="i2cSlaveCfg"
 */
typedef struct I2CSlaveUserConfig
{
    uint16_t address;                   /*!< Slave's 7-bit or 10-bit address. If 10-bit address,
                                             the first 6 bits must be 011110 in binary. @internal gui name="Address" id="SlaveAddress" */
    bool slaveListening;                /*!< The slave configuration mode. @internal gui name="Slave listening" id="SlaveListening" */
    i2c_slave_callback_t slaveCallback; /*!< The slave callback function. @internal gui name="Callback" id="SlaveCallback" */
    void *callbackParam;                /*!< The slave callback data. @internal gui name="Callback parameter" id="SlaveCallbackParam" */
#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    bool startStopDetect;               /*!< The slave startStop detect configuration @internal gui name="Start and Stop detect" id="SlaveStartStopDetect" */
#endif
#if FSL_FEATURE_I2C_HAS_STOP_DETECT
    bool stopDetect;                    /*!< The slave Stop detect configuration @internal gui name="Stop detect" id="SlaveStopDetect" */
#endif
}i2c_slave_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name I2C Slave
 * @{
 */

/*!
 * @brief Initializes the I2C module.
 *
 * Saves the application callback info, turns on the clock to the module,
 * enables the device, and enables interrupts. Sets the I2C to slave mode.
 * IOMUX should be handled in the init_hardware() function.
 *
 * @param instance       Instance number of the I2C module.
 * @param userConfigPtr  Pointer of the user configuration structure
 * @param slave          Pointer of the slave run-time structure.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_SlaveInit(uint32_t instance,
                               const i2c_slave_user_config_t * userConfigPtr,
                               i2c_slave_state_t * slave);

/*!
 * @brief Shuts down the I2C slave driver.
 *
 * Clears the control register and turns off the clock to the module.
 *
 * @param instance  Instance number of the I2C module.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_DRV_SlaveDeinit(uint32_t instance);

/*!
 * @brief Gets the I2C slave run-time state structure.
 *
 * This function gets the I2C slave run-time state structure.
 *
 * @param instance  Instance number of the I2C module.
 *
 * @return          Pointer to I2C slave run-time state structure.
 */
i2c_slave_state_t * I2C_DRV_SlaveGetHandler(uint32_t instance);

/*!
 * @brief Sends/transmits data by using a non-blocking method.
 *
 * This function returns immediately when the buffer pointer and length are set to the transfer buffer and
 * transfer size. The user should check the status of I2C slave to find out whether the transmission
 * is completed. The user can also wait the kI2CSlaveStop or the kI2CSlaveTxDone to ensure that
 * the transmission is ended.
 *
 * @param instance  Instance number of the I2C module.
 * @param txBuff    The pointer to sending the data buffer.
 * @param txSize    The number of bytes which the user wants to send.
 *
 * @return          success (if I2C slave status is not error) or error code in others.
 */
i2c_status_t I2C_DRV_SlaveSendData(uint32_t instance,
                                   const uint8_t * txBuff,
                                   uint32_t txSize);


/*!
 * @brief Sends (transmits) data by using a blocking method.
 *
 * This function sets the buffer pointer and length to the transfer buffer and the transfer size and waits until the
 * transmission is ended (NAK is detected).
 *
 * @param instance  Instance number of the I2C module.
 * @param txBuff    The pointer to sending the data buffer.
 * @param txSize    The number of bytes which the user wants to send.
 * @param timeout_ms   The maximum number of milliseconds to wait for transmit completed
 *
 * @return success (if I2C slave status is not error) or error code in others.
 */

i2c_status_t I2C_DRV_SlaveSendDataBlocking(uint32_t    instance,
                                           const uint8_t *  txBuff,
                                           uint32_t   txSize,
                                           uint32_t   timeout_ms);

/*!
 * @brief Receives the data by using a non-blocking method.
 *
 * This function returns immediately when the buffer pointer and length are set to the receive buffer and
 * the receive size. The user should check the status of the I2C slave to find out whether the transmission
 * is completed. The user can also wait the kI2CSlaveStop or the kI2CSlaveRxDone to ensure that
 * the transmission is ended.
 *
 * @param instance  Instance number of the I2C module.
 * @param rxBuff    The pointer to the received data buffer.
 * @param rxSize    The number of bytes which the user wants to receive.
 *
 * @return          success (if I2C slave status is not error) or error code in others.
 */
i2c_status_t I2C_DRV_SlaveReceiveData(uint32_t   instance,
                                       uint8_t * rxBuff,
                                       uint32_t  rxSize);

/*!
 * @brief Receives data by using a blocking method.
 *
 * This function sets the buffer pointer and length to the receive buffer and the receive size. Then, the function waits until the
 * transmission is ended (all data is received or a STOP signal is detected).
 *
 * @param instance  Instance number of the I2C module.
 * @param rxBuff    The pointer to the received data buffer.
 * @param rxSize    The number of bytes which the user wants to receive.
 * @param timeout_ms   The maximum number of milliseconds to wait for receive completed
 *
 * @return          success (if I2C slave status is not error) or error code in others.
 */
i2c_status_t I2C_DRV_SlaveReceiveDataBlocking(uint32_t instance,
                                       uint8_t  * rxBuff,
                                       uint32_t   rxSize,
                                       uint32_t   timeout_ms);

/*!
 * @brief Gets the current status of the I2C slave driver.
 *
 * @param instance        Instance number of the I2C module.
 * @param bytesRemaining  The number of remaining bytes that I2C transmits.
 * @return                The current status of I2C instance: in progress (busy),
 *                        complete (success) or idle (I2C bus is idle).
 */
i2c_status_t I2C_DRV_SlaveGetReceiveStatus(uint32_t instance,
                                            uint32_t *bytesRemaining);

/*!
 * @brief Gets the current status of the I2C slave driver.
 *
 * @param instance        Instance number of the I2C module.
 * @param bytesRemaining  The number of remaining bytes that I2C transmits.
 * @return                The current status of I2C instance: in progress (busy),
 *                        complete (success) or idle (I2C bus is idle).
 */
i2c_status_t I2C_DRV_SlaveGetTransmitStatus(uint32_t instance,
                                            uint32_t *bytesRemaining);

/*!
 * @brief Terminates a non-blocking receive of the I2C slave early.
 *
 * During an non-blocking receiving
 *
 * @param instance        Instance number of the I2C module.
 * @param rxSize          The number of remaining bytes in I2C Rx Buffer.
 * @return                kStatus_I2C_Success if success
 *                        kStatus_I2C_NoReceiveInProgress if none receiving is available.
 *
 */
i2c_status_t I2C_DRV_SlaveAbortReceiveData(uint32_t instance, uint32_t *rxSize);

/*!
 * @brief Terminates a non-blocking send of the I2C slave early.
 *
 * During an non-blocking receiving
 *
 * @param instance        Instance number of the I2C module.
 * @param txSize          The number of remaining bytes in I2C Tx Buffer.
 * @return                kStatus_I2C_Success if success
 *                        kStatus_I2C_NoReceiveInProgress if none receiving is available.
 *
 */
i2c_status_t I2C_DRV_SlaveAbortSendData(uint32_t instance, uint32_t *txSize);

/*!
 * @brief Gets the current status of the I2C slave bus.
 *
 * @param instance        Instance number of the I2C module.
 * @return                True if the bus is busy
 *                        False if the bus is idle
 *
 */
static inline bool I2C_DRV_SlaveIsBusBusy(uint32_t instance)
{
  return I2C_HAL_GetStatusFlag(g_i2cBase[instance], kI2CBusBusy);
}

/*!
* @brief Sends out multiple bytes of data using a polling method.
*
* @param  instance Instance number of the I2C module.
* @param  txBuff The buffer pointer which saves the data to be sent.
* @param  txSize Size of data to be sent in  bytes.
* @return Error or success status returned by API.
*/
static inline i2c_status_t I2C_DRV_SlaveSendDataPolling(uint32_t instance,
                                                        const uint8_t* txBuff,
                                                        uint32_t txSize)
{
    return I2C_HAL_SlaveSendDataPolling(g_i2cBase[instance], txBuff, txSize);
}

/*!
* @brief Receives multiple bytes of data using a polling method.
*
* @param  instance Instance number of the I2C module.
* @param  rxBuff The buffer pointer which saves the data to be received.
* @param  rxSize Size of data need to be received in bytes.
* @return Error or success status returned by the API.
*/
static inline i2c_status_t I2C_DRV_SlaveReceiveDataPolling(uint32_t instance,
                                                           uint8_t *rxBuff,
                                                           uint32_t rxSize)
{
    return I2C_HAL_SlaveReceiveDataPolling(g_i2cBase[instance], rxBuff, rxSize);
}

/*!
 * @brief The interrupt handler for I2C slave mode
 *
 * @param instance  Instance number of the I2C module.
 */
void I2C_DRV_SlaveIRQHandler(uint32_t instance);

/*@}*/
#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_I2C_SLAVE_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/
