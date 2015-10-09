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

#include <assert.h>
#include <string.h>
#include "fsl_i2c_hal.h"
#include "fsl_i2c_slave_driver.h"
#include "fsl_i2c_shared_function.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_I2C_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveInit
 * Description   : initializes the I2C module.
 * This function will save the application callback info, turn on the clock of
 * I2C instance, setup according to user configuration.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveInit(uint32_t instance,
                       const i2c_slave_user_config_t * userConfigPtr,
                       i2c_slave_state_t * slave)
{
    assert(slave);
    assert(instance < I2C_INSTANCE_COUNT);

    I2C_Type * base = g_i2cBase[instance];

    /* Exit if current instance is already initialized. */
    if (g_i2cStatePtr[instance])
    {
        return kStatus_I2C_Initialized;
    }

    /* Init driver instance structure */
    memset(slave, 0, sizeof(i2c_slave_state_t));
    slave->slaveListening = userConfigPtr->slaveListening;
    slave->slaveCallback = userConfigPtr->slaveCallback;
    slave->callbackParam = userConfigPtr->callbackParam;

    /* Enable clock for I2C.*/
    CLOCK_SYS_EnableI2cClock(instance);

    /* Init instance to known state. */
    I2C_HAL_Init(base);

    /* Set slave address.*/
    I2C_HAL_SetAddress7bit(base, userConfigPtr->address);

    /* Save runtime structure pointer.*/
    g_i2cStatePtr[instance] = slave;

    /* Create Event for irqSync */
    OSA_EventCreate(&slave->irqEvent, kEventAutoClear);

#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Enable I2C START&STOP signal detect interrupt in the peripheral.*/
    if(userConfigPtr->startStopDetect)
    {
        I2C_HAL_SetStartStopIntCmd(base,true);
    }
#endif
#if FSL_FEATURE_I2C_HAS_STOP_DETECT
    /* Enable STOP signal detect interrupt in the peripheral.*/
    if(userConfigPtr->stopDetect)
    {
        I2C_HAL_SetStopIntCmd(base,true);
    }
#endif

    /* Enable I2C interrupt as default if setup slave listening mode */
    I2C_HAL_SetIntCmd(base, slave->slaveListening);

    /* Enable I2C interrupt from NVIC */
    INT_SYS_EnableIRQ(g_i2cIrqId[instance]);

    /* Enable the peripheral operation.*/
    I2C_HAL_Enable(base);

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveDeinit
 * Description   : Shuts down the I2C slave driver.
 * This function will clear the control register and turn off the clock to the
 * module.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveDeinit(uint32_t instance)
{
    assert(instance < I2C_INSTANCE_COUNT);

    /* Exit if current instance is already de-initialized or is gated.*/
    if ((!g_i2cStatePtr[instance]) || (!CLOCK_SYS_GetI2cGateCmd(instance)))
    {
        return kStatus_I2C_Fail;
    }

    I2C_Type * base = g_i2cBase[instance];
    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /* Disable I2C START&STOP signal detect interrupt in the peripheral.*/
    I2C_HAL_SetStartStopIntCmd(base,false);
#endif
#if FSL_FEATURE_I2C_HAS_STOP_DETECT
    /* Disable STOP signal detect interrupt in the peripheral.*/
    I2C_HAL_SetStopIntCmd(base,false);
#endif

    /* Disable I2C interrupt. */
    I2C_HAL_SetIntCmd(base, false);

    /* Turn off I2C.*/
    I2C_HAL_Disable(base);

    /* Disable clock for I2C.*/
    CLOCK_SYS_DisableI2cClock(instance);

    /* Disable I2C NVIC interrupt */
    INT_SYS_DisableIRQ(g_i2cIrqId[instance]);

    /* Destroy sema. */
    OSA_EventDestroy(&i2cSlaveState->irqEvent);

    /* Clear runtime structure poniter.*/
    g_i2cStatePtr[instance] = NULL;

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveGetHandler
 * Description   : Get run-time handler to  I2C slave state structure.
 * This function will return the pointer to I2C slave state structure.
 *
 *END**************************************************************************/
i2c_slave_state_t * I2C_DRV_SlaveGetHandler(uint32_t instance)
{
    return (i2c_slave_state_t *)g_i2cStatePtr[instance];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveReceiveDataBlocking
 * Description   : Receive the data using a blocking method.
 * This function set buffer pointer and length to Rx buffer &Rx Size. Then wait
 * until the transmission is end (all data are received or STOP signal is
 * detected)
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveReceiveDataBlocking(uint32_t instance,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout_ms)
{
    assert(rxBuff);
    assert(instance < I2C_INSTANCE_COUNT);

    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

    if(!i2cSlaveState->slaveListening)
    {
        event_flags_t i2cIrqSetFlags;
        osa_status_t syncStatus;

        if (i2cSlaveState->isRxBusy)
        {
            return kStatus_I2C_Busy;
        }

        i2cSlaveState->rxBuff = rxBuff;
        i2cSlaveState->rxSize = rxSize;
        i2cSlaveState->isRxBusy = true;
        i2cSlaveState->isRxBlocking = true;
        i2cSlaveState->status = kStatus_I2C_Success;

        /* If IAAS event already comes, read dummy to release the bus.*/
        if(I2C_HAL_GetStatusFlag(g_i2cBase[instance], kI2CAddressAsSlave))
        {
            /* Switch to RX mode.*/
            I2C_HAL_SetDirMode(g_i2cBase[instance], kI2CReceive);
            I2C_HAL_ReadByte(g_i2cBase[instance]);
            I2C_HAL_ClearInt(g_i2cBase[instance]);
        }

        I2C_HAL_SetIntCmd(g_i2cBase[instance], true);

        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_EventWait(&i2cSlaveState->irqEvent,
                                       #if (FSL_FEATURE_I2C_HAS_START_STOP_DETECT || FSL_FEATURE_I2C_HAS_STOP_DETECT)
                                       kI2CSlaveStopDetect |
                                       #endif
                                       kI2CSlaveRxFull | kI2CSlaveAbort,
                                       false,
                                       timeout_ms,
                                       &i2cIrqSetFlags);
        } while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            I2C_HAL_SetIntCmd(g_i2cBase[instance], false);
            i2cSlaveState->isRxBusy = false;
            i2cSlaveState->status = kStatus_I2C_Timeout;
        }

        i2cSlaveState->isRxBlocking = false;

        return i2cSlaveState->status;
    }
    else /* i2cSlaveState->slaveListening */
    {
        return kStatus_I2C_Fail;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveReceiveData
 * Description   : Receive the data using a non-blocking method.
 * This function set buffer pointer and length to Rx buffer & Rx Size
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveReceiveData(uint32_t instance,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize)
{
    assert(rxBuff);
    assert(instance < I2C_INSTANCE_COUNT);

    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

    if(!i2cSlaveState->slaveListening)
    {
        if (i2cSlaveState->isRxBusy)
        {
            return kStatus_I2C_Busy;
        }

        i2cSlaveState->rxBuff = rxBuff;
        i2cSlaveState->rxSize = rxSize;
        i2cSlaveState->isRxBusy = true;
        i2cSlaveState->status = kStatus_I2C_Success;

        /* If IAAS event already comes, read dummy to release the bus.*/
        if(I2C_HAL_GetStatusFlag(g_i2cBase[instance], kI2CAddressAsSlave))
        {
             /* Switch to RX mode.*/
            I2C_HAL_SetDirMode(g_i2cBase[instance], kI2CReceive);
            I2C_HAL_ReadByte(g_i2cBase[instance]);
        }

        I2C_HAL_SetIntCmd(g_i2cBase[instance], true);

        return kStatus_I2C_Success;
    }
    else /* i2cSlaveState->slaveListening */
    {
        return kStatus_I2C_Fail;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveSendDataBlocking
 * Description   : Send the data using a blocking method.
 * This function set buffer pointer and length to Tx buffer & Tx Size.
 * Then wait until the transmission is end ( NAK is detected)
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveSendDataBlocking(uint32_t instance,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout_ms)
{
    assert(txBuff);
    assert(instance < I2C_INSTANCE_COUNT);

    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

    if(!i2cSlaveState->slaveListening)
    {
        event_flags_t i2cIrqSetFlags;
        osa_status_t syncStatus;

        if (i2cSlaveState->isTxBusy)
        {
            return kStatus_I2C_Busy;
        }

        /* Initialize the module driver state structure. */
        i2cSlaveState->txBuff = txBuff;
        i2cSlaveState->txSize = txSize;
        i2cSlaveState->isTxBusy = true;
        i2cSlaveState->isTxBlocking = true;
        i2cSlaveState->status = kStatus_I2C_Success;

        I2C_HAL_SetIntCmd(g_i2cBase[instance], true);

        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_EventWait(&i2cSlaveState->irqEvent,
                                       kI2CSlaveTxNAK | kI2CSlaveAbort,
                                       false,
                                       timeout_ms,
                                       &i2cIrqSetFlags);
        } while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            I2C_HAL_SetIntCmd(g_i2cBase[instance], false);
            i2cSlaveState->isTxBusy = false;			
            i2cSlaveState->status = kStatus_I2C_Timeout;
        }

        i2cSlaveState->isTxBlocking = false;

        return i2cSlaveState->status;
    }
    else /* i2cSlaveState->slaveListening */
    {
        return kStatus_I2C_Fail;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveSendData
 * Description   : Send the data using a non-blocking method.
 * This function set buffer pointer and length to Tx buffer & Tx Size
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveSendData(uint32_t instance,
                                   const uint8_t * txBuff,
                                   uint32_t txSize)
{
    assert(txBuff);
    assert(instance < I2C_INSTANCE_COUNT);

    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

    if(!i2cSlaveState->slaveListening)
    {
        if (i2cSlaveState->isTxBusy)
        {
            return kStatus_I2C_Busy;
        }

        /* Initialize the module driver state structure. */
        i2cSlaveState->txBuff = txBuff;
        i2cSlaveState->txSize = txSize;
        i2cSlaveState->isTxBusy = true;
        i2cSlaveState->status = kStatus_I2C_Success;

        I2C_HAL_SetIntCmd(g_i2cBase[instance], true);

        return kStatus_I2C_Success;
    }
    else /* i2cSlaveState->slaveListening */
    {
        return kStatus_I2C_Fail;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveGetTransmitStatus
 * Description   : Gets current status of I2C slave driver. This function returns
 * whether the previous I2C Slave Transmit has finished
 * When performing a non-blocking transmit, the user can call this function to
 * ascertain the state of the current transmission: in progress (or busy) or
 * complete (finished). The user can obtain the number of bytes that have been
 * currently transferred
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveGetTransmitStatus(uint32_t instance,
                                            uint32_t *bytesRemaining)
{
    assert(instance < I2C_INSTANCE_COUNT);

    /* Get current runtime structure */
    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];
    i2c_status_t retVal = kStatus_I2C_Success;
    uint32_t txSize = i2cSlaveState->txSize;

    if (bytesRemaining)
    {
        *bytesRemaining = txSize;
    }

    if (txSize)
    {
        retVal = kStatus_I2C_Busy;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveGetReceiveStatus
 * Description   : Gets current status of I2C slave driver. This function returns
 * whether the previous I2C Slave Receive has finished
 * When performing a non-blocking receiving, the user can call this function to
 * ascertain the state of the current receiving: in progress (or busy) or
 * complete (finished). The user can obtain the number of bytes that have been
 * currently transferred
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveGetReceiveStatus(uint32_t instance,
                                           uint32_t *bytesRemaining)
{
    assert(instance < I2C_INSTANCE_COUNT);

    /* Get current runtime structure */
    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];
    i2c_status_t retVal = kStatus_I2C_Success;
    uint32_t rxSize = i2cSlaveState->rxSize;

    if (bytesRemaining)
    {
        *bytesRemaining = rxSize;
    }

    if (rxSize)
    {
        retVal = kStatus_I2C_Busy;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveAbortReceiveData
 * Description   : This function is used to abort receiving of I2C slave
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveAbortReceiveData(uint32_t instance, uint32_t *rxSize)
{
    assert(instance < I2C_INSTANCE_COUNT);
    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

    *rxSize = i2cSlaveState->rxSize;

    /* Check if a transfer is running. */
    if (!i2cSlaveState->isRxBusy)
    {
        return kStatus_I2C_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    i2cSlaveState->isRxBusy = false;
    i2cSlaveState->rxBuff = NULL;
    i2cSlaveState->rxSize = 0;

    if(!i2cSlaveState->slaveListening)
    {
        /* Disable I2C interrupt in the peripheral.*/
        I2C_HAL_SetIntCmd(g_i2cBase[instance], false);

        if (i2cSlaveState->isRxBlocking)
        {
            /* Set kI2CSlaveRxFull event to notify that the receiving is done */
            OSA_EventSet(&i2cSlaveState->irqEvent, kI2CSlaveAbort);
        }
    }

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveAbortSendData
 * Description   : This function is used to abort sending of I2C slave
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_SlaveAbortSendData(uint32_t instance, uint32_t *txSize)
{
    assert(instance < I2C_INSTANCE_COUNT);
    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

    *txSize = i2cSlaveState->txSize;

    /* Check if a transfer is running. */
    if (!i2cSlaveState->isTxBusy)
    {
        return kStatus_I2C_NoSendInProgress;
    }

    /* Stop the running transfer. */
    i2cSlaveState->isTxBusy = false;
    i2cSlaveState->txBuff = NULL;
    i2cSlaveState->txSize = 0;

    if(!i2cSlaveState->slaveListening)
    {
        /* Disable I2C interrupt in the peripheral.*/
        I2C_HAL_SetIntCmd(g_i2cBase[instance], false);

        if (i2cSlaveState->isTxBlocking)
        {
            /* Set kI2CSlaveTxEmpty event to notify that the sending is done */
            OSA_EventSet(&i2cSlaveState->irqEvent, kI2CSlaveAbort);
        }
    }

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SlaveIRQHandler
 * Description   : I2C Slave Generic ISR.
 * ISR action be called inside I2C IRQ handler entry.
 *
 *END**************************************************************************/
void I2C_DRV_SlaveIRQHandler(uint32_t instance)
{
    assert(instance < I2C_INSTANCE_COUNT);

    I2C_Type * base = g_i2cBase[instance];
    uint8_t  i2cData  = 0x00;
    bool     doTransmit = false;
    bool     addressed = I2C_HAL_GetStatusFlag(base, kI2CAddressAsSlave);
    bool     stopIntEnabled = false;

#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    bool     startDetected = I2C_HAL_GetStartFlag(base);
    bool     startIntEnabled = I2C_HAL_GetStartStopIntCmd(base);
    bool     stopDetected = I2C_HAL_GetStopFlag(base);
    stopIntEnabled = startIntEnabled;
#endif

#if FSL_FEATURE_I2C_HAS_STOP_DETECT
    bool     stopDetected = I2C_HAL_GetStopFlag(base);
    stopIntEnabled = I2C_HAL_GetStopIntCmd(base);
#endif

    /* Get current runtime structure */
    i2c_slave_state_t * i2cSlaveState = (i2c_slave_state_t *)g_i2cStatePtr[instance];

    /* Get current slave transfer direction */
    i2c_direction_t direction = I2C_HAL_GetDirMode(base);

#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT
    /*--------------- Handle START ------------------*/
    if (startIntEnabled && startDetected)
    {
        I2C_HAL_ClearStartFlag(base);
        I2C_HAL_ClearInt(base);

        if(i2cSlaveState->slaveCallback != NULL)
        {
            /*Call callback to handle when the driver detect START signal*/
            i2cSlaveState->slaveCallback(instance,
                                         kI2CSlaveStartDetect,
                                         i2cSlaveState->callbackParam);
        }

        return;
    }
#endif

#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT || FSL_FEATURE_I2C_HAS_STOP_DETECT
    /*--------------- Handle STOP ------------------*/
    if (stopIntEnabled && stopDetected)
    {
        I2C_HAL_ClearStopFlag(base);
        I2C_HAL_ClearInt(base);

        if(!i2cSlaveState->slaveListening)
        {
            /* Disable I2C interrupt in the peripheral.*/
            I2C_HAL_SetIntCmd(base, false);
        }

        if(i2cSlaveState->slaveCallback != NULL)
        {
             /*Call callback to handle when the driver detect STOP signal*/
            i2cSlaveState->slaveCallback(instance,
                                         kI2CSlaveStopDetect,
                                         i2cSlaveState->callbackParam);
        }

        if (i2cSlaveState->isRxBlocking)
        {
            OSA_EventSet(&i2cSlaveState->irqEvent, kI2CSlaveStopDetect);
        }
        i2cSlaveState->isRxBusy = false;
        i2cSlaveState->isTxBusy = false;
        return;
    }
#endif

    /* Clear I2C IRQ.*/
    I2C_HAL_ClearInt(base);

    /*--------------- Handle Address ------------------*/
    /* Addressed only happens when receiving address. */
    if (addressed) /* Slave is addressed. */
    {
        /* Master read from Slave. Slave transmit.*/
        if (I2C_HAL_GetStatusFlag(base, kI2CSlaveTransmit))
        {
            /* Switch to TX mode*/
            I2C_HAL_SetDirMode(base, kI2CSend);

            if(i2cSlaveState->slaveCallback != NULL)
            {
                /*Call callback to handle when the driver get read request*/
                i2cSlaveState->slaveCallback(instance,
                                             kI2CSlaveTxReq,
                                             i2cSlaveState->callbackParam);
            }

            doTransmit = true;
        }
        else /* Master write to Slave. Slave receive.*/
        {
            /* Switch to RX mode.*/
            I2C_HAL_SetDirMode(base, kI2CReceive);

            if(i2cSlaveState->slaveCallback != NULL)
            {
                /*Call callback to handle when the driver get write request*/
                i2cSlaveState->slaveCallback(instance,
                                             kI2CSlaveRxReq,
                                             i2cSlaveState->callbackParam);
            }

            /* Read dummy character.*/
            I2C_HAL_ReadByte(base);
        }
    }
    /*--------------- Handle Transfer ------------------*/
    else
    {
        /* Handle transmit */
        if (direction == kI2CSend)
        {
            if (I2C_HAL_GetStatusFlag(base, kI2CReceivedNak))
            {
                /* Switch to RX mode.*/
                I2C_HAL_SetDirMode(base, kI2CReceive);
                /* Read dummy character to release bus */
                I2C_HAL_ReadByte(base);

                if ((!i2cSlaveState->slaveListening) && (!stopIntEnabled))
                {
                    /* Disable I2C interrupt in the peripheral.*/
                    I2C_HAL_SetIntCmd(base, false);
                }

                if(i2cSlaveState->slaveCallback != NULL)
                {
                     /* Receive TX NAK, mean transaction is finished, call callback to handle */
                    i2cSlaveState->slaveCallback(instance,
                                                 kI2CSlaveTxNAK,
                                                 i2cSlaveState->callbackParam);
                }

                if (i2cSlaveState->isTxBlocking)
                {
                    OSA_EventSet(&i2cSlaveState->irqEvent, kI2CSlaveTxNAK);
                }

                i2cSlaveState->txSize = 0;
                i2cSlaveState->txBuff = NULL;
                i2cSlaveState->isTxBusy = false;
            }
            else /* ACK from receiver.*/
            {
                doTransmit = true;
            }
        }
        /* Handle receive */
        else
        {
            /* Get byte from data register */
            i2cData = I2C_HAL_ReadByte(base);

            if (i2cSlaveState->rxSize)
            {
                *(i2cSlaveState->rxBuff) = i2cData;
                ++ i2cSlaveState->rxBuff;
                -- i2cSlaveState->rxSize;

                if (!i2cSlaveState->rxSize)
                {
                    if (!stopIntEnabled)
                    {
                        if(!i2cSlaveState->slaveListening)
                        {
                            /* Disable I2C interrupt in the peripheral.*/
                            I2C_HAL_SetIntCmd(base, false);
                        }

                        /* All bytes are received, so we're done with this transfer */
                        if (i2cSlaveState->isRxBlocking)
                        {
                            OSA_EventSet(&i2cSlaveState->irqEvent, kI2CSlaveRxFull);
                        }
                    }

                    i2cSlaveState->isRxBusy = false;
                    i2cSlaveState->rxBuff = NULL;

                    if(i2cSlaveState->slaveCallback != NULL)
                    {
                        /* Rx buffer is full, call callback to handle */
                        i2cSlaveState->slaveCallback(instance,
                                                     kI2CSlaveRxFull,
                                                     i2cSlaveState->callbackParam);
                    }
                }
            }
            else
            {
                /* The Rxbuff is full --> Set kStatus_I2C_SlaveRxOverrun*/
                i2cSlaveState->status = kStatus_I2C_SlaveRxOverrun;
            }
        }
    }

    /* DO TRANSMIT*/
    if (doTransmit)
    {
        /* Send byte to data register */
        if (i2cSlaveState->txSize)
        {
            i2cData = *(i2cSlaveState->txBuff);
            I2C_HAL_WriteByte(base, i2cData);
            ++ i2cSlaveState->txBuff;
            -- i2cSlaveState->txSize;
            if (!i2cSlaveState->txSize)
            {
                /* All bytes are received, so we're done with this transfer */
                i2cSlaveState->txBuff = NULL;
                i2cSlaveState->isTxBusy = false;

                if(i2cSlaveState->slaveCallback != NULL)
                {
                    /* Tx buffer is empty, finish transaction, call callback to handle */
                    i2cSlaveState->slaveCallback(instance,
                                                 kI2CSlaveTxEmpty,
                                                 i2cSlaveState->callbackParam);
                }

            }
        }
        else
        {
            /* The Txbuff is empty --> set kStatus_I2C_SlaveTxUnderrun*/
            i2cSlaveState->status = kStatus_I2C_SlaveTxUnderrun ;
        }
    }
}

#endif /* FSL_FEATURE_SOC_I2C_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/
