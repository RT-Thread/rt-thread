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
 
#include <string.h>
#include "fsl_flexio_i2c_master_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT
/*******************************************************************************
 * Prototype
 ******************************************************************************/
static uint32_t isTx = 0;
/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static flexio_i2c_status_t FLEXIO_I2C_DRV_MasterStartSendData(flexio_i2c_state_t *i2cState,
                                                              uint16_t slaveAddr,
                                                              flexio_i2c_memrequest_t *memRequest,
                                                              uint8_t * txBuff,
                                                              uint32_t txSize);
static flexio_i2c_status_t FLEXIO_I2C_DRV_MasterStartReceiveData(flexio_i2c_state_t *i2cState,
                                                           uint16_t slaveAddr,
                                                           flexio_i2c_memrequest_t *memRequest,
                                                           uint8_t * rxBuff,
                                                           uint32_t rxSize);
static void FLEXIO_I2C_DRV_MasterCompleteTransferData(flexio_i2c_state_t *i2cState);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_Init
 * Description   : Initialize a I2C device for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers,initialize the module to user defined settings and 
 * default settings, configures underlying flexio Pin,shifter and timer.
 * The following is an example of how to set up the flexio_i2c_state_t and the
 * flexio_i2c_userconfig_t parameters and how to call the FLEXIO_I2C_DRV_Init function
 * by passing in these parameters:
 *    flexio_i2c_state_t i2cState;
      flexio_i2c_userconif_t i2cMasterConfig;
      i2cMasterConfig.baudRate = 100000;
      i2cMasterConfig.i2cHwConfig.sdaPinIdx = 0;
      i2cMasterConfig.i2cHwConfig.sclkPinIdx = 1;
      i2cMasterConfig.i2cHwConfig.shifterIdx = {0,1};
      i2cMasterConfig.i2cHwConfig.timerIdx = {0,1};
 *    FLEXIO_I2C_DRV_MasterInit(instance, &i2cState, &i2cMasterConfig);
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterInit(uint32_t instance, flexio_i2c_state_t *i2cState, 
                                        const flexio_i2c_userconfig_t *i2cMasterConfig)
{
    if((i2cState == NULL)||(i2cMasterConfig == NULL))
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }
    FLEXIO_Type* base = g_flexioBase[instance];
    /*Reset the i2cState structure*/
    memset(i2cState,0,sizeof(*i2cState));
    /*Create semaphore for xIrq*/
    OSA_SemaCreate(&i2cState->xIrqSync,0);
    /*Init FlexIO I2C resource*/
    i2cState->i2cDev.flexioBase = base;
    i2cState->i2cDev.sdaPinIdx = i2cMasterConfig->i2cHwConfig.sdaPinIdx;
    i2cState->i2cDev.sckPinIdx = i2cMasterConfig->i2cHwConfig.sclkPinIdx;
    i2cState->i2cDev.shifterIdx[0] = i2cMasterConfig->i2cHwConfig.shifterIdx[0];
    i2cState->i2cDev.shifterIdx[1] = i2cMasterConfig->i2cHwConfig.shifterIdx[1];
    i2cState->i2cDev.timerIdx[0] = i2cMasterConfig->i2cHwConfig.timerIdx[0];
    i2cState->i2cDev.timerIdx[1] = i2cMasterConfig->i2cHwConfig.timerIdx[1];
    flexio_i2c_master_config_t masterConfig;
    /*Get FlexIO clock frequency for baudrate calculation*/
    masterConfig.flexioBusClk = CLOCK_SYS_GetFlexioFreq(instance);
    masterConfig.baudrate = i2cMasterConfig->baudRate;
    FLEXIO_I2C_HAL_ConfigMaster(&(i2cState->i2cDev),&masterConfig);
    FLEXIO_DRV_RegisterCallback(instance,i2cState->i2cDev.shifterIdx[0],
                                FLEXIO_I2C_DRV_TX_IRQHandler,(void *)(i2cState));
    FLEXIO_DRV_RegisterCallback(instance,i2cState->i2cDev.shifterIdx[1],
                                FLEXIO_I2C_DRV_RX_IRQHandler,(void *)(i2cState));
    return kStatus_FlexIO_I2C_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_Deinit
 * Description   : Shutdown a FlexIO simulated I2C device.
 * This function destroy the semaphores
 *
 *END**************************************************************************/
void FLEXIO_I2C_DRV_MasterDeinit(flexio_i2c_state_t *i2cState)
{
    /* Destroy transfer sema. */
    OSA_SemaDestroy(&i2cState->xIrqSync);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterInstallRxCallback
 * Description   : Install receive data callback function, pass in NULL pointer
 * as callback will uninstall.
 *
 *END**************************************************************************/
flexio_i2c_rx_callback_t FLEXIO_I2C_DRV_MasterInstallRxCallback(flexio_i2c_state_t *i2cState,
                                                           flexio_i2c_rx_callback_t function, 
                                                           void * callbackParam)
{
    flexio_i2c_rx_callback_t currentCallback = i2cState->rxCallback;
    i2cState->rxCallback = function;
    i2cState->rxCallbackParam = callbackParam;
    return currentCallback;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterSendDataBlocking
 * Description   : This function sends (transmits) data out through the FlexIO
 * simulated I2C module using a blocking method.
 * A blocking (also known as synchronous) function means that the function does
 * not return until the transmit is complete. This blocking function is used to
 * send data through the FlexIO simulated I2C port.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterSendDataBlocking(flexio_i2c_state_t *i2cState,
                                        uint16_t slaveAddr,
                                        flexio_i2c_memrequest_t *memRequest,
                                        uint8_t * txBuff,
                                        uint32_t txSize,
                                        uint32_t timeout)
{
    if((i2cState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }
    flexio_i2c_status_t retVal = kStatus_FlexIO_I2C_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    i2cState->isXBlocking = true;
    
    /* Start the transmission process */
    retVal = FLEXIO_I2C_DRV_MasterStartSendData(i2cState, slaveAddr, memRequest, txBuff, txSize);

    if (retVal == kStatus_FlexIO_I2C_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&i2cState->xIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable the transmitter data register empty interrupt */
            FLEXIO_I2C_HAL_SetTxBufferEmptyIntCmd(&(i2cState->i2cDev), false);
            /* Update the information of the module driver state */
            i2cState->isXBusy = false;

            retVal = kStatus_FlexIO_I2C_Timeout;
        }
    }
    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterSendData
 * Description   : This function sends (transmits) data through the FlexIO simulated
 * I2C module using a non-blocking method.
 * A non-blocking (also known as asynchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterSendData(flexio_i2c_state_t *i2cState,
                                            uint16_t slaveAddr,
                                            flexio_i2c_memrequest_t *memRequest,
                                            uint8_t * txBuff,
                                            uint32_t txSize)
{
    if((i2cState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }

    flexio_i2c_status_t retVal = kStatus_FlexIO_I2C_Success;

    /* Indicates current transaction is non-blocking */
    i2cState->isXBlocking = false;

    /* Start the transmission process */
    retVal = FLEXIO_I2C_DRV_MasterStartSendData(i2cState, slaveAddr, memRequest, txBuff, txSize);

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterGetTransmitStatus
 * Description   : This function returns whether the previous transmit has 
 * finished.
 * When performing an non-blocking transmit, the user can call this function to
 * ascertain the state of the current transmission: in progress (or busy) or
 * complete (success). In addition, if the transmission is still in progress,
 * the user can obtain the number of words that have been currently transferred.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterGetTransmitStatus(flexio_i2c_state_t *i2cState, uint32_t * bytesRemaining)
{
    if(i2cState == NULL)
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }

    flexio_i2c_status_t retVal = kStatus_FlexIO_I2C_Success;
    uint32_t txSize = i2cState->xSize;

    /* Fill in the bytes transferred. This may return that all bytes were
     * transmitted.*/
    if (bytesRemaining)
    {
        *bytesRemaining = txSize;
    }

    if (txSize)
    {
        retVal = kStatus_FlexIO_I2C_XBusy;
    }
    
    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterAbortSendingData
 * Description   : This function ends a non-blocking I2C transmission early.
 * During a non-blocking I2C transmission, the user has the option to terminate
 * the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterAbortSendingData(flexio_i2c_state_t *i2cState)
{
    if(i2cState == NULL)
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!i2cState->isXBusy)
    {
        return kStatus_FlexIO_I2C_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_I2C_DRV_MasterCompleteTransferData(i2cState);

    return kStatus_FlexIO_I2C_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterReceiveDataBlocking
 * Description   : This function gets (receives) data from the I2C module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the I2C port.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterReceiveDataBlocking(flexio_i2c_state_t *i2cState, 
                                                       uint16_t slaveAddr,
                                                       flexio_i2c_memrequest_t *memRequest,
                                                       uint8_t * rxBuff,
                                                       uint32_t rxSize, 
                                                       uint32_t timeout)
{
    if((i2cState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }

    flexio_i2c_status_t retVal = kStatus_FlexIO_I2C_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    i2cState->isXBlocking = true;

    retVal = FLEXIO_I2C_DRV_MasterStartReceiveData(i2cState, slaveAddr, memRequest, rxBuff, rxSize);

    if (retVal == kStatus_FlexIO_I2C_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&i2cState->xIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable receive data full and rx overrun interrupt */
            FLEXIO_I2C_HAL_SetRxBufferFullIntCmd(&(i2cState->i2cDev), false);
            /* Update the information of the module driver state */
            i2cState->isXBusy = false;

            retVal = kStatus_FlexIO_I2C_Timeout;
        }
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterReceiveData
 * Description   : This function gets (receives) data from the simulated I2C
 * module using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the
 * application must get the receive status to check if receive is completed or
 * not.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterReceiveData(flexio_i2c_state_t *i2cState,
                                               uint16_t slaveAddr,
                                               flexio_i2c_memrequest_t *memRequest,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize)
{
    if((i2cState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }

    flexio_i2c_status_t retVal = kStatus_FlexIO_I2C_Success;

    /* Indicates current transaction is non-blocking.*/
    i2cState->isXBlocking = false;

    retVal = FLEXIO_I2C_DRV_MasterStartReceiveData(i2cState, slaveAddr, memRequest, rxBuff, rxSize);

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterGetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 *                 completed.
 * When performing a non-blocking receive, the user can call this function to
 * ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress, the
 * user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterGetReceiveStatus(flexio_i2c_state_t *i2cState,
                                        uint32_t * bytesRemaining)
{
    if(i2cState == NULL)
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }
    flexio_i2c_status_t retVal = kStatus_FlexIO_I2C_Success;
    uint32_t rxSize = i2cState->xSize;

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = rxSize;
    }

    if (rxSize)
    {
        retVal = kStatus_FlexIO_I2C_XBusy;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterAbortReceivingData
 * Description   : This function aborts data receive.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_AbortReceivingData(flexio_i2c_state_t *i2cState)
{
    if(i2cState == NULL)
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!i2cState->isXBusy)
    {
        return kStatus_FlexIO_I2C_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_I2C_DRV_MasterCompleteTransferData(i2cState);

    return kStatus_FlexIO_I2C_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_TX_IRQHandler
 * Description   : Interrupt i2cState for SDO for FlexIO I2C device.
 * This i2cState uses the buffers stored in the flexio_i2c_state_t struct to send
 * data. This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXIO_I2C_DRV_TX_IRQHandler(void *param)
{
    flexio_i2c_state_t *i2cState = (flexio_i2c_state_t *)param;
    if(i2cState == NULL)
    {
        return;
    }

    /* Exit the ISR if no transfer is happening for this instance. */
    if (!i2cState->isXBusy)
    {
        return;
    }
    if(FLEXIO_I2C_HAL_GetRxErrFlag(&(i2cState->i2cDev)))
    {
        /*Receive NACK from slave, send stop*/
        FLEXIO_I2C_HAL_ClearRxErrFlag(&(i2cState->i2cDev));
        FLEXIO_WR_TIMCFG_TIMDIS(g_flexioBase[0],(i2cState->i2cDev).timerIdx[0],4);
        /* Send STOP condition. */
        FLEXIO_I2C_DRV_MasterCompleteTransferData(i2cState);
        return;
    }
    /*Read rx shifter to avoid overrun.*/
   FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
    /* Handle transmit data register empty interrupt */
    --i2cState->xSize;
    /* Check to see if there are any more bytes to send */
    if (i2cState->xSize)
    {
        /* Transmit data and update tx size/buff */
        ++i2cState->xBuff;
        FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), *(i2cState->xBuff));
    }
    else
    {
         /* Send STOP condition. */
        FLEXIO_I2C_HAL_ConfigXferWordCountOnce(&(i2cState->i2cDev),0);
        FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), 0x0);
        FLEXIO_I2C_DRV_MasterCompleteTransferData(i2cState);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_RX_IRQHandler
 * Description   : Interrupt i2cState for SDI for FlexIO I2C device.
 * This i2cState uses the buffers stored in the flexio_uart_state_t struct to transfer
 * data. This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXIO_I2C_DRV_RX_IRQHandler(void *param)
{
    flexio_i2c_state_t *i2cState = (flexio_i2c_state_t *)param;
    if(i2cState == NULL)
    {
        return;
    }

    /* Exit the ISR if no transfer is happening for this instance. */
    if (!(i2cState->isXBusy))
    {
        return;
    }
    if(isTx)
    {
      isTx = 0;
      FLEXIO_I2C_HAL_SetRxBufferFullIntCmd(&(i2cState->i2cDev), false);
      if(FLEXIO_I2C_HAL_GetRxErrFlag(&(i2cState->i2cDev)))
      {
          /*Receive NACK from slave, send stop*/
          FLEXIO_I2C_HAL_ClearRxErrFlag(&(i2cState->i2cDev));
          FLEXIO_WR_TIMCFG_TIMDIS(g_flexioBase[0],(i2cState->i2cDev).timerIdx[0],4);
          /* Send STOP condition. */
          FLEXIO_I2C_DRV_MasterCompleteTransferData(i2cState);    
      }
      return;
    }
    /* Handle transmit data register empty interrupt */
    uint32_t tmp = FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
    *(i2cState->xBuff) = tmp>>24;
    FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), 0xFFFFFFFF);
    ++i2cState->xBuff;
    --i2cState->xSize;
    if(i2cState->xSize == 1)
    {
        FLEXIO_I2C_HAL_ConfigSendNAck(&(i2cState->i2cDev));
    }
    if(i2cState->xSize == 0)
    {
         /* Send STOP condition. */
        FLEXIO_I2C_HAL_ConfigXferWordCountOnce(&(i2cState->i2cDev),0);
        FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), 0x0);
        FLEXIO_I2C_DRV_MasterCompleteTransferData(i2cState);
        if (i2cState->rxCallback != NULL)
        {
            i2cState->rxCallback(i2cState);
        }
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterSendAddress
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending slave address.
 *
 *END**************************************************************************/
flexio_i2c_status_t FLEXIO_I2C_DRV_MasterSendAddress(flexio_i2c_state_t *i2cState,
                                                     uint16_t slaveAddr,
                                                     flexio_i2c_direction_t direction,
                                                     flexio_i2c_memrequest_t *memRequest)
{
    uint8_t addrByte1, addrByte2, directionBit;
    bool is10bitAddr;
    /* Make sure the transmit data register is empty and ready for data */
    while(!FLEXIO_I2C_HAL_GetTxBufferEmptyFlag(&(i2cState->i2cDev))) { }
    
    /*--------------- Prepare Address Buffer ------------------*/
    /* Get r/w bit according to required direction.
     * read is 1, write is 0. */
    directionBit = (direction == kFlexIOI2CRead) ? 0x1U : 0x0U;

    /* Check to see if slave address is 10 bits or not. */
    is10bitAddr = ((slaveAddr >> 10U) == 0x1EU) ? true : false;

    /* Get address byte 1 and byte 2 according address bit number. */
    if (is10bitAddr)
    {
        addrByte1 = (uint8_t)(slaveAddr >> 8U);
        addrByte2 = (uint8_t)slaveAddr;
    }
    else
    {
        addrByte1 = (uint8_t)slaveAddr;
    }

    /* Get the device address with r/w direction. If we have a sub-address,
      then that is always done as a write transfer prior to transferring
      the actual data.*/
    addrByte1 = addrByte1 << 1U;

    /* First need to write if 10-bit address or has cmd buffer. */
    addrByte1 |= (uint8_t)((is10bitAddr || memRequest) ? 0U : directionBit);

    /* Put the slave address in shifter to start the transmission */
    FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), addrByte1);
    FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
    FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
    FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));

    if (is10bitAddr)
    {
        /* Put address byte 2 into shifter. */
        while(!FLEXIO_I2C_HAL_GetRxBufferFullFlag(&(i2cState->i2cDev))){}
        FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), addrByte2 );
        FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
    }
    /*If the operation is a memory operation, send the memory address*/
    if(memRequest)
    {
        for (uint8_t i = 0U; i < memRequest->memAddrSize; i++)
        {
            FLEXIO_I2C_HAL_PutDataPolling(&(i2cState->i2cDev), *(memRequest->memAddress+i));
            while(!FLEXIO_I2C_HAL_GetRxBufferFullFlag(&(i2cState->i2cDev))){}
            FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
        }
    }
    /* Send slave address again if receiving data from 10-bit address slave,
       OR conducting a memory read */
    if((direction == kFlexIOI2CRead)&&(memRequest||is10bitAddr))
    {
        /* Prepare for RESTART condition, no stop.*/
        FLEXIO_I2C_HAL_PutDataPolling(&(i2cState->i2cDev), 0xFFFFFFFF);
        FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
    }

    return kStatus_FlexIO_I2C_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_MasterStartSendData
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 *
 *END**************************************************************************/
static flexio_i2c_status_t FLEXIO_I2C_DRV_MasterStartSendData(flexio_i2c_state_t *i2cState,
                                                              uint16_t slaveAddr,
                                                              flexio_i2c_memrequest_t *memRequest,
                                                              uint8_t * txBuff,
                                                              uint32_t txSize)
{
    flexio_i2c_status_t result = kStatus_FlexIO_I2C_Success;
    /* Check that we're not busy already transmitting data from a previous
     * function call. */
    if (i2cState->isXBusy)
    {
        return kStatus_FlexIO_I2C_XBusy;
    }

    if (txSize == 0U)
    {
        return kStatus_FlexIO_I2C_NoDataToDeal;
    }
    /* Initialize the module driver state structure. */
    i2cState->xBuff = txBuff;
    i2cState->xSize = txSize;
    i2cState->isXBusy = true;
    /*Calculate total bytes in the I2C frame*/
    bool is10bitAddr = ((slaveAddr >> 10U) == 0x1EU) ? true : false;
    uint32_t byteCount = txSize + 1;
    if(is10bitAddr)
    {
        byteCount++;
    }
    else if(memRequest)
    {
        byteCount += memRequest->memAddrSize;
    }
    /*Config total bytes in the I2C frame*/
    if(FLEXIO_I2C_HAL_ConfigXferWordCountOnce(&(i2cState->i2cDev),byteCount) != kStatus_FLEXIO_Success)
    {
        return kStatus_FlexIO_I2C_InvalidParam;  
    }
    /*Send slave address and memory address(if a memory request)*/
    result = FLEXIO_I2C_DRV_MasterSendAddress(i2cState, slaveAddr, kFlexIOI2CWrite, memRequest);
    if(result != kStatus_FlexIO_I2C_Success)
    {
        return result;
    }
    /* Put the first data in shifter to start the transmission */
    FLEXIO_I2C_HAL_PutDataPolling(&(i2cState->i2cDev), *(txBuff));
    /* Enable interrupt generation for tx shifter.  */
    
    FLEXIO_I2C_HAL_SetTxBufferEmptyIntCmd(&(i2cState->i2cDev), true);
    isTx = 1;
    FLEXIO_I2C_HAL_SetRxBufferFullIntCmd(&(i2cState->i2cDev), true);
    return kStatus_FlexIO_I2C_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_StartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexio_i2c_status_t FLEXIO_I2C_DRV_MasterStartReceiveData(flexio_i2c_state_t *i2cState,
                                                           uint16_t slaveAddr,
                                                           flexio_i2c_memrequest_t *memRequest,
                                                           uint8_t * rxBuff,
                                                           uint32_t rxSize)
{
    flexio_i2c_status_t result = kStatus_FlexIO_I2C_Success;
    if(i2cState == NULL)
    {
        return kStatus_FlexIO_I2C_InvalidParam;
    }

    /* Check that we're not busy receiving data from a previous function call. */
    if (i2cState->isXBusy)
    {
        return kStatus_FlexIO_I2C_XBusy;
    }

    if (rxSize == 0U)
    {
        return kStatus_FlexIO_I2C_NoDataToDeal;
    }

    /* Initialize the module driver state structure to indicate transfer in progress
     * and with the buffer and byte count data */
    i2cState->xBuff = rxBuff;
    i2cState->xSize = rxSize;
    i2cState->isXBusy = true;
    /*Calculate total bytes in the I2C frame*/
    bool is10bitAddr = ((slaveAddr >> 10U) == 0x1EU) ? true : false;
    uint32_t byteCount = 1;
    if(is10bitAddr)
    {
        byteCount++;
    }
    else 
    {
    if(memRequest)
    {
        byteCount += memRequest->memAddrSize;
    }
    else
    {
        byteCount +=rxSize;
    }
     }
    /*Config total bytes in the I2C frame*/
    if(FLEXIO_I2C_HAL_ConfigXferWordCountOnce(&(i2cState->i2cDev),byteCount) != kStatus_FLEXIO_Success)
    {
        return kStatus_FlexIO_I2C_InvalidParam;  
    }

    /*Send slave address and memory address(if a memory request)*/
    result = FLEXIO_I2C_DRV_MasterSendAddress(i2cState, slaveAddr, kFlexIOI2CRead, memRequest);
    while(!FLEXIO_I2C_HAL_GetRxBufferFullFlag(&(i2cState->i2cDev))){}
    if(FLEXIO_I2C_HAL_GetRxErrFlag(&(i2cState->i2cDev)))
    {
      /*Receive NACK from slave, send stop*/
      FLEXIO_I2C_HAL_ClearRxErrFlag(&(i2cState->i2cDev));
      FLEXIO_WR_TIMCFG_TIMDIS(g_flexioBase[0],(i2cState->i2cDev).timerIdx[0],4);
      /* Send STOP condition. */
      FLEXIO_I2C_DRV_MasterCompleteTransferData(i2cState);    
      return result;
    }
    if(result != kStatus_FlexIO_I2C_Success)
    {
        return result;
    }
    /*if 10-bit slave read, needs a second I2C Frame, calculate the total byetes of second frame*/
    if(is10bitAddr || memRequest)
    {
        byteCount = rxSize + 1 ;
        /*Config total bytes in the second I2C frame*/
		if(FLEXIO_I2C_HAL_ConfigXferWordCountOnce(&(i2cState->i2cDev),byteCount) != kStatus_FLEXIO_Success)
		{
			return kStatus_FlexIO_I2C_InvalidParam;  
		}

        /* Send address byte 1 again. */
        if(is10bitAddr)
        {
             FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), (((slaveAddr >> 8)<<1) | 1U));
       
        }
        else
        {
            FLEXIO_I2C_HAL_PutData(&(i2cState->i2cDev), ((((uint32_t)slaveAddr) << 1)| 1U));
        }
        FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
        while(!FLEXIO_I2C_HAL_GetRxBufferFullFlag(&(i2cState->i2cDev))){}
    }
    /*if single byte read, config send NACK*/
    if(rxSize == 1)
    {
        FLEXIO_I2C_HAL_ConfigSendNAck(&(i2cState->i2cDev));
    }
    /*else config send ACK*/
    else
    {
        FLEXIO_I2C_HAL_ConfigSendAck(&(i2cState->i2cDev));
    }
    FLEXIO_I2C_HAL_PutDataPolling(&(i2cState->i2cDev),0xFFFFFFFF);
    FLEXIO_I2C_HAL_GetData(&(i2cState->i2cDev));
    /* Enable the receive data full interrupt */
    isTx = 0;
    FLEXIO_I2C_HAL_SetRxBufferFullIntCmd(&(i2cState->i2cDev), true);

    return kStatus_FlexIO_I2C_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2C_DRV_CompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_I2C_DRV_MasterCompleteTransferData(flexio_i2c_state_t *i2cState)
{
    if(i2cState == NULL)
    {
        return;
    }

    /* Disable the transmitter data register empty interrupt */
    FLEXIO_I2C_HAL_SetTxBufferEmptyIntCmd(&(i2cState->i2cDev), false);
    /* Disable receive data full interrupt */
    FLEXIO_I2C_HAL_SetRxBufferFullIntCmd(&(i2cState->i2cDev), false);
    /*Clear Tx/Rx overrun/underrun flag*/
    FLEXIO_I2C_HAL_ClearTxErrFlag(&(i2cState->i2cDev));
    FLEXIO_I2C_HAL_ClearRxErrFlag(&(i2cState->i2cDev));

    /* Signal the synchronous completion object. */
    if (i2cState->isXBlocking)
    {
        OSA_SemaPost(&i2cState->xIrqSync);
    }

    /* Update the information of the module driver state */
    i2cState->isXBusy = false;
}

#endif

