/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
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
#include "fsl_smartcard_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
smartcard_driver_interface_t smartcardDrvInterface = {NULL};

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static smartcard_status_t SMARTCARD_DRV_InterfaceInit(uint32_t interfaceInsatance, 
                               smartcard_state_t * smartcardStatePtr,
                               smartcard_interface_config_t * interfaceUserConfig);
static void SMARTCARD_DRV_InterfaceDeInit(uint32_t instance);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_Init
 * Description   : This function initializes a SMARTCARD instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the SMARTCARD module, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the core, initialize DMA, 
 * interface/PHY specific initialization, and enable the SMARTCARD module 
 * transmitter and receiver.
 * The following is an example of how to set up the uart_state_t and the
 * uart_user_config_t parameters and how to call the SMARTCARD_DRV_Init function by
 * passing in these parameters:
 *    edma_user_config_t edmaUserConfig;
 *    edmaUserConfig.chnArbitration = kEDMAChnArbitrationRoundrobin;
 *    edmaUserConfig.notHaltOnError = false;
 *   
 *    smartcard_user_config_t smartcardConfig;
 *    smartcardConfig.interfaceConfig.sCClock = 5000000;
 *    smartcardConfig.interfaceConfig.interfaceInsatance = 0;
 *    smartcardConfig.interfaceConfig.cardSoltNo = 0;
 *    smartcardConfig.vcc = kSmartcardVoltageClassB3_3V;
 *    smartcardConfig.xferMode = kSmartcardCPUXferMode;
 *    smartcardConfig.clockModuleInstance = HW_SMARTCARD_FTM_INSTANCE;
 *    smartcardConfig.clockModuleChannel = HW_SMARTCARD_FTM_CHANNEL;
 *    smartcardConfig.controlPortInstance = HW_SMARTCARD_I2C_INSTANCE;
 *    SMARTCARD_DRV_Init(instance, &smartcardState, &smartcardConfig);
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_Init(uint32_t instance, smartcard_state_t * smartcardStatePtr,
                            const smartcard_user_config_t * smartcardUserConfig)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    assert(smartcardStatePtr && smartcardUserConfig);
    
    smartcard_status_t smartcardStatus;
    
    /* Install Peripheral driver functions */
    SMARTCARD_DRV_InstallDriverFunctions(&smartcardDrvInterface);
    
    /* Install PHY/Interface driver functions */
    SMARTCARD_DRV_InstallInterfaceFunctions(&smartcardDrvInterface);
    
    /* Invoke smartcard IP driver specific peripheral driver initialization */
    smartcardStatus = smartcardDrvInterface.smartcardDrvInit(instance, smartcardStatePtr, smartcardUserConfig);
    
    if(smartcardStatus != kStatus_SMARTCARD_Success)
    {
        return smartcardStatus;
    }
    
    /* Invoke interface/PHY driver specific peripheral driver initialization */
    smartcardStatus = SMARTCARD_DRV_InterfaceInit(smartcardStatePtr->interfaceConfig.interfaceInstance, smartcardStatePtr, &smartcardStatePtr->interfaceConfig);
    
    return smartcardStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_Deinit
 * Description   : This function shuts down the SMARTCARD driver by invoking module 
 *                 IP and interface/PHY specific de-init functions.
 *
 *END**************************************************************************/
void SMARTCARD_DRV_Deinit(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke smartcard interface/PHY specific peripheral driver de-initialization */
    SMARTCARD_DRV_InterfaceDeInit(instance);
    
    /* Invoke smartcard IP specific peripheral driver de-initialization */
    smartcardDrvInterface.smartcardDrvDeinit(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_SendDataBlocking
 * Description   : This function sends (transmits) data out through the SMARTCARD 
 * module using a blocking method.
 * A blocking (also known as synchronous) function means that the function does
 * not return until the transmit is complete. This blocking function is used to
 * send data through the SMARTCARD port.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_SendDataBlocking(uint32_t instance,
                                        const uint8_t * txBuff,
                                        uint32_t txSize,
                                        uint32_t timeout)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    assert(txBuff);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvSendDataBlocking(instance, txBuff, txSize, timeout);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_SendData
 * Description   : This function sends (transmits) data through the SMARTCARD module
 * using a non-blocking method.
 * A non-blocking (also known as asynchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not. The asynchronous method of transmitting and receiving allows the SMARTCARD
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_SendData(uint32_t instance,
                                const uint8_t * txBuff,
                                uint32_t txSize)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    assert(txBuff);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvSendData(instance, txBuff, txSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_GetTransmitStatus
 * Description   : This function returns whether the previous SMARTCARD transmit has
 * finished.
 * When performing an async transmit, the user can call this function to
 * ascertain the state of the current transmission: in progress (or busy) or
 * complete (success). In addition, if the transmission is still in progress,
 * the user can obtain the number of words that have been currently transferred.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_GetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvGetTransmitStatus(instance, bytesRemaining);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_AbortSendingData
 * Description   : This function ends a non-blocking MARTCARD transmission early.
 * During a non-blocking MARTCARD transmission, the user has the option to terminate
 * the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_AbortSendingData(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvAbortSendingData(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_ReceiveDataBlocking
 * Description   : This function gets (receives) data from the MARTCARD module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the UART port.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_ReceiveDataBlocking(uint32_t instance, uint8_t * rxBuff,
                                           uint32_t rxSize, uint32_t *rcvdSize, uint32_t timeout)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    assert(rxBuff);
    assert(rcvdSize);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvReceiveDataBlocking(instance, rxBuff, rxSize, rcvdSize, timeout);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_ReceiveData
 * Description   : This function gets (receives) data from the SMARTCARD module using
 * a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the 
 * application must get the receive status to check if receive is completed or
 * not. The asynchronous method of transmitting and receiving allows the SMARTCARD
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_ReceiveData(uint32_t instance,
                                   uint8_t * rxBuff,
                                   uint32_t rxSize)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    assert(rxBuff);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvReceiveData(instance, rxBuff, rxSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_GetReceiveStatus
 * Description   : This function returns whether the previous SMARTCARD receive is
 *                 completed.
 * When performing a non-blocking receive, the user can call this function to
 * ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress, the
 * user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_GetReceiveStatus(uint32_t instance,
                                        uint32_t * bytesRemaining)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvGetReceiveStatus(instance, bytesRemaining);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_AbortReceivingData
 * Description   : This function shuts down the SMARTCARD by disabling interrupts and
 *                 the transmitter/receiver.
 * This function disables the SMARTCARD interrupts, disables the transmitter and
 * receiver, and flushes the FIFOs (for modules that support FIFOs).
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_AbortReceivingData(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvAbortReceivingData(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_Control
 * Description   : This function does different control functions for the SMARTCARD driver.
 * Control functions are as per smartcard_control_t structure.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_Control(uint32_t instance, smartcard_control_t control, void *controlBuff)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke SMARTCARD IP specific function */
    return smartcardDrvInterface.smartcardDrvControl(instance, control, controlBuff);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InstallInterfaceCallback
 * Description   : This function installs a user callback function to be called 
 * after any interface interrupt is serviced.
 *
 *END**************************************************************************/
smartcard_interface_callback_t SMARTCARD_DRV_InstallInterfaceCallback(uint32_t instance, 
                                              smartcard_interface_callback_t function, 
                                              void * callbackParam)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    if(smartcardDrvInterface.smartcardDrvInstallInterfaceCallback)
    {
        /* Invoke SMARTCARD IP specific function */
        return smartcardDrvInterface.smartcardDrvInstallInterfaceCallback(instance, function, callbackParam);
    }
    else
    {
        return NULL;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InstallInterfaceCallback
 * Description   : This function resets the SMARTCARD interface/card slot for 
 * the given reset type.
 *
 *END**************************************************************************/
void SMARTCARD_DRV_Reset(uint32_t instance, smartcard_reset_type_t resetType)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Enable Initial character detectio first */
    smartcardDrvInterface.smartcardDrvControl(instance, kSmartcardEnableInitDetect, NULL);
    
    /* Invoke SMARTCARD IP specific function to activate the card */
    smartcardDrvInterface.smartcardDrvInterfaceActivate(instance, resetType);
    
    /* Invoke SMARTCARD IP specific function to enable reception */
    smartcardDrvInterface.smartcardDrvControl(instance, kSmartcardEnableReceiverMode, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InstallInterfaceCallback
 * Description   : This function de-activates the SMARTCARD interface/card slot.
 *
 *END**************************************************************************/
void SMARTCARD_DRV_Deactivate(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke SMARTCARD IP specific function to deactivate the card */
    smartcardDrvInterface.smartcardDrvInterfaceDeactivate(instance);
    
    /*Wait for 100 ms*/
    OSA_TimeDelay(100);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InterfaceInit
 * Description   : This function invokes interface initilization routine
 *
 *END**************************************************************************/
static smartcard_status_t SMARTCARD_DRV_InterfaceInit(uint32_t interfaceInsatance, 
                               smartcard_state_t * smartcardStatePtr,
                               smartcard_interface_config_t * interfaceUserConfig)
{
    /* Invoke interface/PHY specific initialization function */
    return smartcardDrvInterface.smartcardDrvInterfaceInit(interfaceInsatance, 
                               smartcardStatePtr,
                               interfaceUserConfig);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InterfaceDeInit
 * Description   : This function invokes interface de-initilization routine
 *
 *END**************************************************************************/
static void SMARTCARD_DRV_InterfaceDeInit(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    /* Invoke interface/PHY specific de-initialization function */
    smartcardDrvInterface.smartcardDrvInterfaceDeInit(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InterfaceControl
 * Description   : This function invokes interface control function
 *
 *END**************************************************************************/
void SMARTCARD_DRV_InterfaceControl(uint32_t instance, void *interfaceControl, void *param)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    assert(interfaceControl);
    
    /* Invoke interface/PHY specific control function */
    smartcardDrvInterface.smartcardDrvInterfaceControl(instance, interfaceControl, param);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

