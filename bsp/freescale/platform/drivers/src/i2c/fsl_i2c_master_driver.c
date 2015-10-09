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
#include "fsl_i2c_master_driver.h"
#include "fsl_i2c_shared_function.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_I2C_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Default timeout time(ms) for sending of address and CMD buffer */
#define I2C_TIMEOUT_MS (30)

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

static i2c_status_t I2C_DRV_MasterWait(uint32_t instance, uint32_t timeout_ms);
static void I2C_DRV_CompleteTransfer(uint32_t instance);
static i2c_status_t I2C_DRV_SendAddress(uint32_t instance,
                                        const i2c_device_t * device,
                                        const uint8_t * cmdBuff,
                                        uint32_t cmdSize,
                                        i2c_direction_t direction,
                                        uint32_t timeout_ms);
static i2c_status_t I2C_DRV_MasterSend(uint32_t instance,
                                       const i2c_device_t * device,
                                       const uint8_t * cmdBuff,
                                       uint32_t cmdSize,
                                       const uint8_t * txBuff,
                                       uint32_t txSize,
                                       uint32_t timeout_ms,
                                       bool isBlocking);
static i2c_status_t I2C_DRV_MasterReceive(uint32_t instance,
                                          const i2c_device_t * device,
                                          const uint8_t * cmdBuff,
                                          uint32_t cmdSize,
                                          uint8_t * rxBuff,
                                          uint32_t rxSize,
                                          uint32_t timeout_ms,
                                          bool isBlocking);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterInit
 * Description   : initializes the I2C master mode driver.
 * This function will initialize the I2C master mode driver, enable I2C clock,
 * and enable I2C interrupt.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterInit(uint32_t instance, i2c_master_state_t * master)
{
    assert(master);
    assert(instance < I2C_INSTANCE_COUNT);

    I2C_Type * base = g_i2cBase[instance];

    /* Exit if current instance is already initialized */
    if (g_i2cStatePtr[instance])
    {
        return kStatus_I2C_Initialized;
    }

    /* Initialize driver instance struct */
    memset(master, 0, sizeof(i2c_master_state_t));

    /* Create sync object for transfer. */
    OSA_SemaCreate(&master->irqSync, 0);

    /* Enable clock for I2C.*/
    CLOCK_SYS_EnableI2cClock(instance);

    /* Initialize peripheral to known state.*/
    I2C_HAL_Init(base);

    /* Save runtime structure pointer */
    g_i2cStatePtr[instance] = master;

    /* Enable I2C interrupt in NVIC level.*/
    INT_SYS_EnableIRQ(g_i2cIrqId[instance]);

    /* Indicate I2C bus is idle. */
    master->i2cIdle = true;

    /* Enable module.*/
    I2C_HAL_Enable(base);

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterDeinit
 * Description   : Deinit the I2C master mode driver.
 * This function will deinit the I2C master mode driver, disable I2C clock,
 * and disable I2C interrupt.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterDeinit(uint32_t instance)
{
    assert(instance < I2C_INSTANCE_COUNT);

    /* Exit if current instance is already de-initialized or is gated.*/
    if ((!g_i2cStatePtr[instance]) || (!CLOCK_SYS_GetI2cGateCmd(instance)))
    {
        return kStatus_I2C_Fail;
    }

    I2C_Type * base = g_i2cBase[instance];
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    /* Disable module.*/
    I2C_HAL_Disable(base);

    /* Disable clock for I2C.*/
    CLOCK_SYS_DisableI2cClock(instance);

    /* Disable I2C NVIC interrupt*/
    INT_SYS_DisableIRQ(g_i2cIrqId[instance]);

    /* Destroy I2C sema. */
    OSA_SemaDestroy(&master->irqSync);

    /* Cleared state pointer. */
    g_i2cStatePtr[instance] = NULL;

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterSetBaudRate
 * Description   : configures the I2C bus to access a device.
 * This function will set baud rate.
 *
 *END**************************************************************************/
void I2C_DRV_MasterSetBaudRate(uint32_t instance, const i2c_device_t * device)
{
    assert(device);
    assert(instance < I2C_INSTANCE_COUNT);

    I2C_Type * base = g_i2cBase[instance];
    uint32_t i2cClockFreq;

    /* Get current runtime structure. */
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    /* Set baud rate if different.*/
    if (device->baudRate_kbps != master->lastBaudRate_kbps)
    {
        /* Get the current bus clock.*/
        i2cClockFreq = CLOCK_SYS_GetI2cFreq(instance);
        I2C_HAL_SetBaudRate(base, i2cClockFreq, device->baudRate_kbps, NULL);

        /* Record baud rate change */
        master->lastBaudRate_kbps = device->baudRate_kbps;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterSendDataBlocking
 * Description   : performs a blocking send transaction on the I2C bus.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterSendDataBlocking(uint32_t instance,
                                            const i2c_device_t * device,
                                            const uint8_t * cmdBuff,
                                            uint32_t cmdSize,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            uint32_t timeout_ms)
{
    return I2C_DRV_MasterSend(instance, device, cmdBuff, cmdSize, txBuff, txSize,
                              timeout_ms, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterSendData
 * Description   : Performs a non-blocking send transaction on the I2C bus.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterSendData(uint32_t instance,
                                    const i2c_device_t * device,
                                    const uint8_t * cmdBuff,
                                    uint32_t cmdSize,
                                    const uint8_t * txBuff,
                                    uint32_t txSize)
{
    return I2C_DRV_MasterSend(instance, device, cmdBuff, cmdSize, txBuff, txSize,
                              0, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterGetSendStatus
 * Description   : Gets current status of I2C master transmit.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterGetSendStatus(uint32_t instance,
                                         uint32_t *bytesRemaining)
{
    i2c_status_t retVal = kStatus_I2C_Success;
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];
    uint32_t txSize = master->txSize;

    if (bytesRemaining)
    {
        *bytesRemaining = txSize;
    }

    if (txSize)
    {
        retVal = kStatus_I2C_Busy;
    }

    if (master->status != kStatus_I2C_Success)
    {
        retVal = master->status;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterAbortSendData
 * Description   : Terminates a non-blocking I2C Master transmission early.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterAbortSendData(uint32_t instance)
{
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    if (master->i2cIdle)
    {
        return kStatus_I2C_Fail;
    }

    I2C_DRV_CompleteTransfer(instance);

    return kStatus_I2C_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterReceiveDataBlocking
 * Description   : Performs a blocking receive transaction on the I2C bus.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterReceiveDataBlocking(uint32_t instance,
                                               const i2c_device_t * device,
                                               const uint8_t * cmdBuff,
                                               uint32_t cmdSize,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize,
                                               uint32_t timeout_ms)
{
    return I2C_DRV_MasterReceive(instance, device, cmdBuff, cmdSize, rxBuff,
                                 rxSize, timeout_ms, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterReceiveData
 * Description   : Performs a non-blocking receive transaction on the I2C bus.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterReceiveData(uint32_t instance,
                                       const i2c_device_t * device,
                                       const uint8_t * cmdBuff,
                                       uint32_t cmdSize,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize)
{
    return I2C_DRV_MasterReceive(instance, device, cmdBuff, cmdSize, rxBuff,
                                 rxSize, 0, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterGetReceiveStatus
 * Description   : Gets current status of I2C master receive.
 *
 *END**************************************************************************/
i2c_status_t I2C_DRV_MasterGetReceiveStatus(uint32_t instance,
                                            uint32_t *bytesRemaining)
{
    i2c_status_t retVal = kStatus_I2C_Success;
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];
    uint32_t rxSize = master->rxSize;

    if (bytesRemaining)
    {
        *bytesRemaining = rxSize;
    }

    if (rxSize)
    {
        retVal = kStatus_I2C_Busy;
    }

    if (master->status != kStatus_I2C_Success)
    {
        retVal = master->status;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C master IRQ handler.
 * Description   : This handler uses the buffers stored in the
 * i2c_master_state_t structs to transfer data.
 * This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void I2C_DRV_MasterIRQHandler(uint32_t instance)
{
    assert(instance < I2C_INSTANCE_COUNT);

    I2C_Type * base = g_i2cBase[instance];

    /* Clear the interrupt flag*/
    I2C_HAL_ClearInt(base);

    /* Get current runtime structure */
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    /* Get current master transfer direction */
    i2c_direction_t direction = I2C_HAL_GetDirMode(base);
    bool     wasArbLost = I2C_HAL_GetStatusFlag(base, kI2CArbitrationLost);
    if (wasArbLost)
    {
        I2C_HAL_ClearArbitrationLost(base);
        master->status = kStatus_I2C_AribtrationLost;
        /* Disable I2C interrupt in the peripheral.*/
        I2C_HAL_SetIntCmd(base, false);
		if (master->isBlocking)
		{
			OSA_SemaPost(&master->irqSync);
		}

        return;
    }
    /* Exit immediately if there is no transfer in progress OR not in master mode */
    if ((!I2C_HAL_GetStatusFlag(base, kI2CBusBusy)) ||
        (!I2C_HAL_IsMaster(base)))
    {
        return;
    }

    /* Handle send */
    if (direction == kI2CSend)
    {
        /* Check whether we got an ACK or NAK from the former byte we sent */
        if (I2C_HAL_GetStatusFlag(base, kI2CReceivedNak))
        {
            /* Record that we got a NAK */
            master->status = kStatus_I2C_ReceivedNak;

            /* Got a NAK, so we're done with this transfer */
            I2C_DRV_CompleteTransfer(instance);
        }
        else
        {
            /* Continue send if still have data. TxSize/txBuff index need
             * increment first because one byte is already sent in order
             * to trigger interrupt */
            if (--master->txSize > 0)
            {
               /* Transmit next byte and update buffer index */
                I2C_HAL_WriteByte(base, *(++master->txBuff));
            }
            else
            {
                /* Finish send data, send STOP, disable interrupt */
                I2C_DRV_CompleteTransfer(instance);
            }
        }
    }
    else /* Handle receive */
    {
        switch (--master->rxSize)
        {
            case 0x0U:
                /* Finish receive data, send STOP, disable interrupt */
                I2C_DRV_CompleteTransfer(instance);
                break;
            case 0x1U:
                /* For the byte before last, we need to set NAK */
                I2C_HAL_SendNak(base);
                break;
            default :
                I2C_HAL_SendAck(base);
                break;
        }

        /* Read recently received byte into buffer and update buffer index */
        *(master->rxBuff++) = I2C_HAL_ReadByte(base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterWait
 * Description   : Wait transfer to finish.
 * This function is a static function which will be called by other data
 * transaction APIs.
 *
 *END**************************************************************************/
static i2c_status_t I2C_DRV_MasterWait(uint32_t instance, uint32_t timeout_ms)
{
    assert(instance < I2C_INSTANCE_COUNT);

    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];
    osa_status_t syncStatus;

    do
    {
        syncStatus = OSA_SemaWait(&master->irqSync, timeout_ms);
    }while(syncStatus == kStatus_OSA_Idle);

    if (syncStatus != kStatus_OSA_Success)
    {
        master->status = kStatus_I2C_Timeout;
    }

    return master->status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_CompleteTransfer
 * Description   : Send STOP and disable interrupt when error happens or finish
 * I2C transfers.
 * This function is a static function which will be called by other data
 * transaction APIs.
 *
 *END**************************************************************************/
static void I2C_DRV_CompleteTransfer(uint32_t instance)
{
    assert(instance < I2C_INSTANCE_COUNT);

    I2C_Type * base = g_i2cBase[instance];
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    if ((!master->isRequesting)
     || (master->status == kStatus_I2C_ReceivedNak)
     || (master->status == kStatus_I2C_Timeout))
    {
        /* Disable interrupt. */
        I2C_HAL_SetIntCmd(base, false);

        /* Generate stop signal. */
        I2C_HAL_SendStop(base);

        /* Indicate I2C bus is idle. */
        master->i2cIdle = true;
    }

    if (master->isBlocking)
    {
        OSA_SemaPost(&master->irqSync);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_SendAddress
 * Description   : Prepare and send out address buffer with interrupt.
 * This function is a static function which will be called by other data
 * transaction APIs.
 *
 *END**************************************************************************/
static i2c_status_t I2C_DRV_SendAddress(uint32_t instance,
                                        const i2c_device_t * device,
                                        const uint8_t * cmdBuff,
                                        uint32_t cmdSize,
                                        i2c_direction_t direction,
                                        uint32_t timeout_ms)
{
    assert(instance < I2C_INSTANCE_COUNT);

    I2C_Type * base = g_i2cBase[instance];
    /* Get current runtime structure. */
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    uint8_t addrByte1, addrByte2, directionBit;
    bool is10bitAddr;
    uint8_t addrBuff[2] = {0};
    uint8_t addrSize = 0;
    bool isMainXferBlocking = master->isBlocking;

    /* Send of address and CMD must be blocking without STOP */
    master->isRequesting = true;
    master->isBlocking = true;

    /*--------------- Prepare Address Buffer ------------------*/
    /* Get r/w bit according to required direction.
     * read is 1, write is 0. */
    directionBit = (direction == kI2CReceive) ? 0x1U : 0x0U;

    /* Check to see if slave address is 10 bits or not. */
    is10bitAddr = ((device->address >> 10U) == 0x1EU) ? true : false;

    /* Get address byte 1 and byte 2 according address bit number. */
    if (is10bitAddr)
    {
        addrByte1 = (uint8_t)(device->address >> 8U);
        addrByte2 = (uint8_t)device->address;
    }
    else
    {
        addrByte1 = (uint8_t)device->address;
    }

    /* Get the device address with r/w direction. If we have a sub-address,
      then that is always done as a write transfer prior to transferring
      the actual data.*/
    addrByte1 = addrByte1 << 1U;

    /* First need to write if 10-bit address or has cmd buffer. */
    addrByte1 |= (uint8_t)((is10bitAddr || cmdBuff) ? 0U : directionBit);

    /* Put slave address byte 1 into address buffer. */
    addrBuff[addrSize++] = addrByte1;

    if (is10bitAddr)
    {
        /* Put address byte 2 into address buffer. */
        addrBuff[addrSize++] = addrByte2;
    }

    /*--------------- Send Address Buffer ------------------*/
    master->txBuff = addrBuff;
    master->txSize = addrSize;

    /* Send first byte in address buffer to trigger interrupt.*/
    I2C_HAL_WriteByte(base, addrBuff[0]);

    /* Wait for the transfer to finish.*/
    I2C_DRV_MasterWait(instance, timeout_ms);

    /*--------------------- Send CMD -----------------------*/
    if ((master->status == kStatus_I2C_Success) && cmdBuff)
    {
        master->txBuff = cmdBuff;
        master->txSize = cmdSize;

        /* Send first byte in address buffer to trigger interrupt.*/
        I2C_HAL_WriteByte(base, *cmdBuff);

        /* Wait for the transfer to finish.*/
        I2C_DRV_MasterWait(instance, timeout_ms);
    }

    /*--------------- Send Address Again ------------------*/
    /* Send slave address again if receiving data from 10-bit address slave,
       OR conducting a cmd receive */
    if ((master->status == kStatus_I2C_Success) && (direction == kI2CReceive)
          && (is10bitAddr || cmdBuff))
    {
        /* Need to send slave address again. */
        master->txSize = 1U;
        master->txBuff = NULL;

        /* Need to generate a repeat start before changing to receive. */
        I2C_HAL_SendStart(base);

        /* Send address byte 1 again. */
        I2C_HAL_WriteByte(base, (uint8_t)(addrByte1 | 1U));

        /* Wait for the transfer to finish.*/
        I2C_DRV_MasterWait(instance, timeout_ms);
    }

    master->isRequesting = false;
    master->isBlocking = isMainXferBlocking ;

    return master->status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterSend
 * Description   : Private function to handle blocking/non-blocking send.
 * This function is a static function which will be called by other data
 * transaction APIs.
 *
 *END**************************************************************************/
static i2c_status_t I2C_DRV_MasterSend(uint32_t instance,
                                       const i2c_device_t * device,
                                       const uint8_t * cmdBuff,
                                       uint32_t cmdSize,
                                       const uint8_t * txBuff,
                                       uint32_t txSize,
                                       uint32_t timeout_ms,
                                       bool isBlocking)
{
    assert(instance < I2C_INSTANCE_COUNT);
    assert(txBuff);

    I2C_Type * base = g_i2cBase[instance];
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    /* Return if current instance is used */
    if (!master->i2cIdle)
    {
        return kStatus_I2C_Busy;
    }

    /* Need to assign a pre-defined timeout value for sending address and cmd */
    if (!isBlocking)
    {
        timeout_ms = I2C_TIMEOUT_MS;
    }

    master->txBuff = NULL;
    master->txSize = 0;
    master->rxBuff = NULL;
    master->rxBuff = 0;
    master->status = kStatus_I2C_Success;
    master->i2cIdle = false;
    master->isBlocking = isBlocking;

    I2C_DRV_MasterSetBaudRate(instance, device);

    /* Set direction to send for sending of address and data. */
    I2C_HAL_SetDirMode(base, kI2CSend);

    /* Enable i2c interrupt.*/
    I2C_HAL_ClearInt(base);
    I2C_HAL_SetIntCmd(base, true);

    /* Generate start signal. */
    I2C_HAL_SendStart(base);

    /* Send out slave address. */
    I2C_DRV_SendAddress(instance, device, cmdBuff, cmdSize, kI2CSend, timeout_ms);

    /* Send out data in transmit buffer. */
    if (master->status == kStatus_I2C_Success)
    {
        /* Fill tx buffer and size to run-time structure. */
        master->txBuff = txBuff;
        master->txSize = txSize;

        /* Send first byte in transmit buffer to trigger interrupt.*/
        I2C_HAL_WriteByte(base, master->txBuff[0]);

        if (isBlocking)
        {
            /* Wait for the transfer to finish.*/
            if(I2C_DRV_MasterWait(instance, timeout_ms) == kStatus_I2C_Timeout)
            {
               /* Disable interrupt. */
               I2C_HAL_SetIntCmd(base, false);

               if (I2C_HAL_GetStatusFlag(base, kI2CBusBusy))
               {
                 /* Generate stop signal. */
                 I2C_HAL_SendStop(base);
               }

               /* Indicate I2C bus is idle. */
               master->i2cIdle = true;                
            }

        }
    }
    else if (master->status == kStatus_I2C_Timeout)
    {
        /* Disable interrupt. */
        I2C_HAL_SetIntCmd(base, false);

        if (I2C_HAL_GetStatusFlag(base, kI2CBusBusy))
        {
            /* Generate stop signal. */
            I2C_HAL_SendStop(base);
        }

        /* Indicate I2C bus is idle. */
        master->i2cIdle = true;
    }

    return master->status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C_DRV_MasterReceive
 * Description   : Private function to handle blocking/non-blocking receive.
 * This function is a static function which will be called by other data
 * transaction APIs.
 *
 *END**************************************************************************/
static i2c_status_t I2C_DRV_MasterReceive(uint32_t instance,
                                          const i2c_device_t * device,
                                          const uint8_t * cmdBuff,
                                          uint32_t cmdSize,
                                          uint8_t * rxBuff,
                                          uint32_t rxSize,
                                          uint32_t timeout_ms,
                                          bool isBlocking)
{
    assert(instance < I2C_INSTANCE_COUNT);
    assert(rxBuff);

    I2C_Type * base = g_i2cBase[instance];
    i2c_master_state_t * master = (i2c_master_state_t *)g_i2cStatePtr[instance];

    /* Return if current instance is used */
    if (!master->i2cIdle)
    {
        return kStatus_I2C_Busy;
    }

    /* Need to assign a pre-defined timeout value for sending address and cmd */
    if (!isBlocking)
    {
        timeout_ms = I2C_TIMEOUT_MS;
    }

    master->rxBuff = rxBuff;
    master->rxSize = rxSize;
    master->txBuff = NULL;
    master->txSize = 0;
    master->status = kStatus_I2C_Success;
    master->i2cIdle = false;
    master->isBlocking = isBlocking;

    I2C_DRV_MasterSetBaudRate(instance, device);

    /* Set direction to send for sending of address. */
    I2C_HAL_SetDirMode(base, kI2CSend);

    /* Enable i2c interrupt.*/
    I2C_HAL_ClearInt(base);
    I2C_HAL_SetIntCmd(base, true);

    /* Generate start signal. */
    I2C_HAL_SendStart(base);

    /* Send out slave address. */
    I2C_DRV_SendAddress(instance, device, cmdBuff, cmdSize, kI2CReceive, timeout_ms);

    /* Start to receive data. */
    if (master->status == kStatus_I2C_Success)
    {
        /* Change direction to receive. */
        I2C_HAL_SetDirMode(base, kI2CReceive);

        /* Send NAK if only one byte to read. */
        if (rxSize == 0x1U)
        {
            I2C_HAL_SendNak(base);
        }
        else
        {
            I2C_HAL_SendAck(base);
        }

        /* Dummy read to trigger receive of next byte in interrupt. */
        I2C_HAL_ReadByte(base);

        if (isBlocking)
        {
            /* Wait for the transfer to finish.*/
            if(I2C_DRV_MasterWait(instance, timeout_ms) == kStatus_I2C_Timeout)
            {
               /* Disable interrupt. */
               I2C_HAL_SetIntCmd(base, false);

               if (I2C_HAL_GetStatusFlag(base, kI2CBusBusy))
               {
                 /* Generate stop signal. */
                 I2C_HAL_SendStop(base);
               }

               /* Indicate I2C bus is idle. */
               master->i2cIdle = true;                
            }

        }
    }
    else if (master->status == kStatus_I2C_Timeout)
    {
        /* Disable interrupt. */
        I2C_HAL_SetIntCmd(base, false);

        if (I2C_HAL_GetStatusFlag(base, kI2CBusBusy))
        {
            /* Generate stop signal. */
            I2C_HAL_SendStop(base);
        }

        /* Indicate I2C bus is idle. */
        master->i2cIdle = true;
    }

    return master->status;
}

#endif /* FSL_FEATURE_SOC_I2C_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

