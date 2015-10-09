/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#include "fsl_interrupt_manager.h"
#include "fsl_smartcard_ncn8025_driver.h"
#if defined(FTM_INSTANCE_COUNT)
#include "fsl_ftm_driver.h"
#elif defined(TPM_INSTANCE_COUNT)
#include "fsl_tpm_driver.h"
#endif
#include "fsl_gpio_driver.h"
#include "fsl_port_hal.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
smartcard_interface_state_t gInterfaceState[HW_SMARTCARD_INTERFACE_COUNT];
smartcard_interface_slot_t gInterfaceSlot[HW_SMARTCARD_INTERFACE_COUNT][HW_SMARTCARD_INTERFACE_SLOT_COUNT];

extern smartcard_driver_interface_t smartcardDrvInterface;
#if defined(EMVSIM_INSTANCE_COUNT)
extern EMVSIM_Type * const g_emvsimBase[EMVSIM_INSTANCE_COUNT];
#else
extern UART_Type *const g_uartBase[UART_INSTANCE_COUNT];
#endif

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static uint16_t SMARTCARD_DRV_InterfaceClockInit(uint8_t clockModuleInstance,  uint8_t clockModuleChannel, uint32_t cardClk);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InstallInterfaceFunctions
 * Description   : This function Installs SMARTCARD PHY/Interface Driver functions
 *
 *END**************************************************************************/
void SMARTCARD_DRV_InstallInterfaceFunctions(smartcard_driver_interface_t *smartcardDrvInterfacePtr)
{
    smartcardDrvInterface.smartcardDrvInterfaceInit = SMARTCARD_DRV_NCN8025Init;
    smartcardDrvInterface.smartcardDrvInterfaceDeInit = SMARTCARD_DRV_NCN8025DeInit;
    smartcardDrvInterface.smartcardDrvInstallInterfaceCallback = SMARTCARD_DRV_NCN8025InstallCallback;
    smartcardDrvInterface.smartcardDrvInterfaceActivate =  SMARTCARD_DRV_NCN8025Activate;
    smartcardDrvInterface.smartcardDrvInterfaceDeactivate = SMARTCARD_DRV_NCN8025Deactivate;
    smartcardDrvInterface.smartcardDrvInterfaceControl =  SMARTCARD_DRV_NCN8025Control;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_NCN8025Init
 * Description   : This function iniitializes SMARTCARD PHY/Interface. The function will
 * initialize PHY speciic state, card/slot specific state, PHY's control interface 
 * parameters, initialize card clock etc.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_NCN8025Init(uint32_t interfaceInstance, 
                               smartcard_state_t * smartcardStatePtr,
                               const smartcard_interface_config_t * interfaceUserConfig)
{
#if defined(EMVSIM_INSTANCE_COUNT)
    uint32_t instance = interfaceUserConfig->clockModuleInstance;
    EMVSIM_Type * base = g_emvsimBase[instance];
#endif

    if (!g_smartcardInterfaceStatePtr[interfaceInstance])
    {
        /* Clear the state structure for this instance. */
        memset((void *)(&gInterfaceState[interfaceInstance]) , 0, sizeof(smartcard_interface_state_t));
        
        /* Save runtime structure pointer.*/
        g_smartcardInterfaceStatePtr[interfaceInstance] = &gInterfaceState[interfaceInstance];
    }

    /* Store interface IC state pointer */
    smartcardStatePtr->interfaceState = &gInterfaceState[interfaceInstance];

    /* Check if this slot already in use */
    if(smartcardStatePtr->interfaceState->slot[interfaceUserConfig->cardSoltNo])
    {
        return kStatus_SMARTCARD_PhyInitialized;
    }
    
    /* Store slot pointer */
    smartcardStatePtr->interfaceState->slot[interfaceUserConfig->cardSoltNo] = &gInterfaceSlot[interfaceUserConfig->interfaceInstance][interfaceUserConfig->cardSoltNo];
    
    /* Clear the state structure for this instance. */
    memset((void *)(smartcardStatePtr->interfaceState->slot[interfaceUserConfig->cardSoltNo]) , 0, sizeof(smartcard_interface_slot_t));
    
    /* Set Clock apply to Reset delay to EMV specific value */
    ((smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[interfaceUserConfig->cardSoltNo]))->clockToResetDelay = 42000;
    
    /*************** Initialize PHY/Interface interface ********************/
    /* Clock */
    SMARTCARD_DRV_InterfaceClockInit(smartcardStatePtr->interfaceConfig.clockModuleInstance,  smartcardStatePtr->interfaceConfig.clockModuleChannel, smartcardStatePtr->interfaceConfig.sCClock);
  
    /* Define gpio input pin config Interrupt structure.*/
    gpio_input_pin_user_config_t intPin[] = {
        {
             GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.irqPort, (uint32_t)smartcardStatePtr->interfaceConfig.irqPin),
             {
#if FSL_FEATURE_PORT_HAS_PULL_ENABLE
              false,
#endif
#if FSL_FEATURE_PORT_HAS_PULL_SELECTION
              kPortPullDown,
#endif
#if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER  
              false,
#endif
#if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
              false,
#endif
#if FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR
              kPortIntEitherEdge
#endif
             }
        },
        {
             GPIO_PINS_OUT_OF_RANGE,
             {
#if FSL_FEATURE_PORT_HAS_PULL_ENABLE
              false,
#endif
#if FSL_FEATURE_PORT_HAS_PULL_SELECTION
              kPortPullDown,
#endif
#if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
              false,
#endif
#if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
              false,
#endif
#if FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR
              kPortIntDisabled
#endif
             }
        }
    };

    gpio_output_pin_user_config_t controlPins[] = {

#if !defined(EMVSIM_INSTANCE_COUNT)
        /* Define gpio output pin CMDVCC config structure.*/
        {
            GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.controlPort, (uint32_t)smartcardStatePtr->interfaceConfig.controlPin),
            {
                1,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
                kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
                kPortHighDriveStrength,
#endif
#if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
                false
#endif
            }
        },
#endif
        /* Define gpio output pin VSEL0 config structure.*/
        {
            GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel0Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel0Pin),
            {
                0,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
                kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
                kPortHighDriveStrength,
#endif
#if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
                false
#endif
            }
        },
        /* Define gpio output pin VSEL1 config structure.*/
        {
            GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel1Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel1Pin),
            {
                0,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
                kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
                kPortHighDriveStrength,
#endif
#if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
                false
#endif
            }
        },
#if !defined(EMVSIM_INSTANCE_COUNT)
        /* Define gpio output pin RESET config structure.*/
        {
            GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.resetPort, (uint32_t)smartcardStatePtr->interfaceConfig.resetPin),
            {
                0,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
                kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
                kPortHighDriveStrength,
#endif
#if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
                false
#endif
            }
        },
#endif
        {
            GPIO_PINS_OUT_OF_RANGE,
            {
                0,
#if FSL_FEATURE_PORT_HAS_SLEW_RATE
                kPortFastSlewRate,
#endif
#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
                kPortLowDriveStrength,
#endif
#if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
                false
#endif
            }
        }
    };

    /*Init Input pin, Output pin.*/
    GPIO_DRV_Init(intPin, controlPins);
#if defined(EMVSIM_INSTANCE_COUNT)
    /* Set CMD_VCC pin to logic level '1', to allow card detection interrupt from NCN8025 */
    EMVSIM_HAL_SetVCCEnable(base, true);
    EMVSIM_HAL_SetCardVCCEnablePolarity(base, kEmvsimVccEnIsHigh);
#endif
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_NCN8025DeInit
 * Description   : This function de-iniitializes SMARTCARD PHY/Interface. The function will
 * clear PHY speciic state, card/slot specific state, ungate card clock etc.
 *
 *END**************************************************************************/
void SMARTCARD_DRV_NCN8025DeInit(uint32_t instance)
{    
    uint8_t i;
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_smartcardStatePtr[instance];

    /* Check if smartcard driver is already deinitialized */
    if (smartcardStatePtr == NULL)
    {
        return;
    }
    /* De-initialize PHY/Interface interface */
    /* Invalidate slot state specific memory */  
    smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo] = NULL;
    
    for(i=0; i<HW_SMARTCARD_INTERFACE_SLOT_COUNT; i++)
    {
        if(smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo] != NULL)
        {
            break;
        }
    }
    
    /* Check if all card slot state data are invalidated */
    if(i == HW_SMARTCARD_INTERFACE_SLOT_COUNT)
    {
        /* Then invalidate PHY state also */
        g_smartcardInterfaceStatePtr[smartcardStatePtr->interfaceConfig.interfaceInstance] = NULL;
    }     
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_NCN8025InstallCallback
 * Description   : Install receive data callback function, pass in NULL pointer
 * as callback will unistall.
 *
 *END**************************************************************************/
smartcard_interface_callback_t SMARTCARD_DRV_NCN8025InstallCallback(uint32_t instance, 
                                              smartcard_interface_callback_t function, 
                                              void * callbackParam)
{
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_smartcardStatePtr[instance];
    
    /* Hold the pointer to current callback function */
    smartcard_interface_callback_t currentCallback = smartcardState->interfaceCallback;
    
    /* Store new callback function */
    smartcardState->interfaceCallback = function;
    
    /* Store pointer to callback parameter */ 
    smartcardState->interfaceCallbackParam = callbackParam;

    /* Return old callback function to the caller */
    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_NCN8025Activate
 * Description   : Activates the smartcard interface
 *
 *END**************************************************************************/
void SMARTCARD_DRV_NCN8025Activate(uint32_t instance, smartcard_reset_type_t resetType)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_smartcardStatePtr[instance];
    smartcard_interface_slot_t * interfaceSlotParams = (smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo]);
#if defined(EMVSIM_INSTANCE_COUNT)
    EMVSIM_Type * base = g_emvsimBase[instance];
#else
    uint32_t temp;
    UART_Type * base = g_uartBase[instance];
#endif

    smartcardStatePtr->timersState.initCharTimerExpired = false;
    smartcardStatePtr->resetType = resetType;

    /* Set data convention format into default direct mode */
#if defined(EMVSIM_INSTANCE_COUNT)
    smartcardStatePtr->cardParams.Fi = 372;
    smartcardStatePtr->cardParams.currentD = 1;
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlInverseConvention, false);
    EMVSIM_HAL_SetBaudrateDivisor(base, (smartcardStatePtr->cardParams.Fi / smartcardStatePtr->cardParams.currentD));
#else
    UART_BWR_S2_RXINV(base, 0);
    UART_BWR_S2_MSBF(base, 0);
    UART_BWR_C3_TXINV(base, 0);
#endif

    if(resetType == kSmartcardColdReset)
    {
		/* Ensure that RST is LOW and CMD is high here so that PHY goes in normal mode */
#if defined(EMVSIM_INSTANCE_COUNT)
        EMVSIM_HAL_SetVCCEnable(base, true);
        EMVSIM_HAL_SetCardVCCEnablePolarity(base, kEmvsimVccEnIsHigh);
        EMVSIM_HAL_ResetCard(base, kEmvsimResetAssert);
#else
        GPIO_DRV_ClearPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.resetPort, (uint32_t)smartcardStatePtr->interfaceConfig.resetPin));
        GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.controlPort, (uint32_t)smartcardStatePtr->interfaceConfig.controlPin));
#endif   
        if (smartcardStatePtr->cardParams.vcc == kSmartcardVoltageClassA5_0V)
        {
            /* vcc = 5v: vsel0=0,vsel1= 1 */
            GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel1Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel1Pin));
            GPIO_DRV_ClearPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel0Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel0Pin));
        }
        else if (smartcardStatePtr->cardParams.vcc == kSmartcardVoltageClassB3_3V)
        {
            /* vcc = 3.3v: vsel0=x,vsel1= 0 */
            GPIO_DRV_ClearPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel1Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel1Pin));
            GPIO_DRV_ClearPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel0Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel0Pin));     
        }
        else
        {
            /* vcc = 1.8v: vsel0=1,vsel1= 1 */
            GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel1Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel1Pin));
            GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.vsel0Port, (uint32_t)smartcardStatePtr->interfaceConfig.vsel0Pin)); 
        }
        
        /* Set PHY to start Activation sequence by pulling CMDVCC low */
#if defined(EMVSIM_INSTANCE_COUNT)
        EMVSIM_HAL_SetCardVCCEnablePolarity(base, kEmvsimVccEnIsLow);
#else
        GPIO_DRV_ClearPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.controlPort, (uint32_t)smartcardStatePtr->interfaceConfig.controlPin));
#endif
   
        /* Wait for sometime as specified by EMV before pulling RST High */        
        /* As per EMV delay <= 42000 Clock cycles
         * as per PHY delay >= 1us
         */
#if defined(EMVSIM_INSTANCE_COUNT)
        /* Down counter trigger, and clear any pending counter status flag */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
            
        /* Disable counter interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, false);
        
        /* Set counter value */
        EMVSIM_HAL_SetGPCNTValue(base, 1, interfaceSlotParams->clockToResetDelay);
        
        /* Select the clock for GPCNT */
        EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCCardClock);
        
        /* Trigger the counter */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);
        
        /* In polling mode */
        while(!EMVSIM_HAL_GetTransmitStatus(base, kEmvsimGPCNT1Timeout))
        {}
        
        /* Disable the counter */
        EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCClockDisable);
        
        /* Down counter trigger, and clear any pending counter status flag */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
#else
        temp = (uint32_t)((float)(1 + (float)(((float)(1000*interfaceSlotParams->clockToResetDelay)) / ((float)smartcardStatePtr->interfaceConfig.sCClock))));
        OSA_TimeDelay(temp);
#endif
        
        /* Pull reset HIGH Now to mark the end of Activation sequence */
#if defined(EMVSIM_INSTANCE_COUNT)
        EMVSIM_HAL_ResetCard(base, kEmvsimResetDeassert);
#else
        GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.resetPort, (uint32_t)smartcardStatePtr->interfaceConfig.resetPin));
#endif
    }
    else if(resetType == kSmartcardWarmReset)
    {
        /* Ensure that card is not already active */
        if(!interfaceSlotParams->active)
        {
            /* Card is not active;hence return */
            return;
        }
        /* Pull RESET low to start warm Activation sequence */
#if defined(EMVSIM_INSTANCE_COUNT)
        EMVSIM_HAL_ResetCard(base, kEmvsimResetAssert);
#else
        GPIO_DRV_ClearPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.resetPort, (uint32_t)smartcardStatePtr->interfaceConfig.resetPin));
#endif
        
        /* Wait for sometime as specified by EMV before pulling RST High */        
        /* As per EMV delay <= 42000 Clock cycles
         * as per PHY delay >= 1us
         */
#if defined(EMVSIM_INSTANCE_COUNT)   
        /* Down counter trigger, and clear any pending counter status flag */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
            
        /* Disable counter interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, false);
        
        /* Set counter value */
        EMVSIM_HAL_SetGPCNTValue(base, 1, interfaceSlotParams->clockToResetDelay);
        
        /* Select the clock for GPCNT */
        EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCCardClock);
        
        /* Trigger the counter */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);
        
        /* In polling mode */
        while(!EMVSIM_HAL_GetTransmitStatus(base, kEmvsimGPCNT1Timeout))
        {}
        
        /* Disable the counter */
        EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCClockDisable);
        
        /* Down counter trigger, and clear any pending counter status flag */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
#else
        temp = (uint32_t)((float)(1 + (float)(((float)(1000*interfaceSlotParams->clockToResetDelay)) / ((float)smartcardStatePtr->interfaceConfig.sCClock))));
        OSA_TimeDelay(temp);
#endif
        
        /* Pull reset HIGH to mark the end of Activation sequence*/
#if defined(EMVSIM_INSTANCE_COUNT)
        EMVSIM_HAL_ResetCard(base, kEmvsimResetDeassert);
#else
        GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.resetPort, (uint32_t)smartcardStatePtr->interfaceConfig.resetPin));
#endif
    }
    
#if defined(EMVSIM_INSTANCE_COUNT)
    /* Down counter trigger, and clear any pending counter status flag */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
    EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT0Timeout);
    EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
    
    /* Set counter value for TS detection delay */
    EMVSIM_HAL_SetGPCNTValue(base, 0, (INIT_DELAY_CLOCK_CYCLES + INIT_DELAY_CLOCK_CYCLES_ADJUSTMENT));
    
    /* Pre-load counter value for ATR duration delay */
    EMVSIM_HAL_SetGPCNTValue(base, 1, (EMV_ATR_DURATION_ETU + ATR_DURATION_ADJUSTMENT));
    
    /* Select the clock for GPCNT for both TS detection and early start of ATR duration counter */
    EMVSIM_HAL_SetGPCClockSelect(base, 0, kEmvsimGPCCardClock);
    EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCTxClock);
    
    /* Enable counter interrupt for TS detection */
    EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt0, true);
        
    /* Trigger the counter */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);
#endif

    /*  Here the card was activated */
    interfaceSlotParams->active = true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_NCN8025Deactivate
 * Description   : De-activates the smartcard interface
 *
 *END**************************************************************************/
void SMARTCARD_DRV_NCN8025Deactivate(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_smartcardStatePtr[instance];
    smartcard_interface_slot_t * interfaceSlotParams = (smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo]);
#if defined(EMVSIM_INSTANCE_COUNT)
    EMVSIM_Type * base = g_emvsimBase[instance];
#endif
   
    /*Tell PHY to start Deactivation sequence by pulling CMD high*/
#if defined(EMVSIM_INSTANCE_COUNT)
    EMVSIM_HAL_ResetCard(base, kEmvsimResetAssert);
    EMVSIM_HAL_SetVCCEnable(base, true);
    EMVSIM_HAL_SetCardVCCEnablePolarity(base, kEmvsimVccEnIsHigh);
#else
    GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.controlPort, (uint32_t)smartcardStatePtr->interfaceConfig.controlPin));
    GPIO_DRV_ClearPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.resetPort, (uint32_t)smartcardStatePtr->interfaceConfig.resetPin));
#endif
    
    /*  here the card was deactivated */
    interfaceSlotParams->active = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_NCN8025Control
 * Description   : This function is used to differnet control interface/slot specific parameters
 *
 *END**************************************************************************/
void SMARTCARD_DRV_NCN8025Control(uint32_t instance, void *interfaceControl, void *param)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    assert(interfaceControl);
    assert(param);
    
    smartcard_interface_control_t *interfaceControlPtr = (smartcard_interface_control_t *)interfaceControl;
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_smartcardStatePtr[instance];
    smartcard_interface_slot_t * interfaceSlotParams = (smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo]);
    smartcard_card_voltage_class_t *vcc;
    uint32_t *clockToResetDelay;
    smartcard_interface_slot_t *statusParams;
#if defined(EMVSIM_INSTANCE_COUNT)
    EMVSIM_Type * base = g_emvsimBase[smartcardStatePtr->interfaceConfig.clockModuleInstance];
#endif
    
    switch(*interfaceControlPtr)
    {
    case kSmartcardInterfaceSetVcc:
        /* Set card parameter to VCC level set by caller */
        vcc = (smartcard_card_voltage_class_t *)param;
        smartcardStatePtr->cardParams.vcc = *vcc;
        interfaceSlotParams->vcc = *vcc;
        break;
    case kSmartcardInterfaceSetClockToResetDelay:
        /* Set interface clock to Reset delay set by caller */
        clockToResetDelay = (uint32_t *)param;
        interfaceSlotParams->clockToResetDelay = *clockToResetDelay;
        break;
    case kSmartcardInterfaceReadStatus:
        /* Read interface/card status */
        statusParams = (smartcard_interface_slot_t *)param;

#if defined(EMVSIM_INSTANCE_COUNT)
        /* Expecting active low present detect */
        statusParams->present = (EMVSIM_HAL_GetCardPresenceDetectPinStatus(base) == kEmvsimPDPinIsLow);
#else		
        if(GPIO_DRV_ReadPinInput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.controlPort, (uint32_t)smartcardStatePtr->interfaceConfig.controlPin)))
        {
            if(GPIO_DRV_ReadPinInput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.irqPort, (uint32_t)smartcardStatePtr->interfaceConfig.irqPin)))
            {
                /* CMDVCC is high => session is inactive and INT is high => card is present */
                statusParams->present = true;
                statusParams->active = false;
                statusParams->faulty = false;
                statusParams->status = MASK_NCN8025_STATUS_PRES;
            }
            else
            {
                /* CMDVCC is high => session is inactive and INT is low => card is absent */
                statusParams->present = false;
                statusParams->active = false;
                statusParams->faulty = false;
                statusParams->status = 0;
            }
        }
        else
        {
            if(GPIO_DRV_ReadPinInput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.irqPort, (uint32_t)smartcardStatePtr->interfaceConfig.irqPin)))
            {
                /* CMDVCC is low => session is active and INT is high => card is present */
                statusParams->present = true;
                statusParams->active = true;
                statusParams->faulty = false;
                statusParams->status = MASK_NCN8025_STATUS_PRES | MASK_NCN8025_STATUS_ACTIVE ;
            }
            else
            {
                /* CMDVCC is low => session is active and INT is low => card is absent/deactivated due to some fault */
                /* A fault has been detected (card has been deactivated) but The cause of the deactivation is not yet known.
                 * Lets determine the cause of fault by pulling CMD high 
                 */
                GPIO_DRV_SetPinOutput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.controlPort, (uint32_t)smartcardStatePtr->interfaceConfig.controlPin));
                
                if(GPIO_DRV_ReadPinInput(GPIO_MAKE_PIN((uint32_t)smartcardStatePtr->interfaceConfig.irqPort, (uint32_t)smartcardStatePtr->interfaceConfig.irqPin)))
                {
                    /* The fault detected was not a card removal (card is still present) */
                    /* If INT follows CMDVCCN, the fault is due to a supply voltage drop, a VCC over-current detection or overheating. */
                    statusParams->present = true;
                    statusParams->active = false;
                    statusParams->faulty = true;
                    statusParams->status = MASK_NCN8025_STATUS_PRES | MASK_NCN8025_STATUS_FAULTY | MASK_NCN8025_STATUS_CARD_DEACTIVATED ;
                }
                else
                {
                    /* The fault detected was the card removal
                     * Setting CMDVCCN allows checking if the deactivation is due to card removal.
                     * In this case the INT pin will stay low after CMDVCCN is high.
                     */
                    statusParams->present = false;
                    statusParams->active = false;
                    statusParams->faulty = false;
                    statusParams->status = MASK_NCN8025_STATUS_CARD_REMOVED | MASK_NCN8025_STATUS_CARD_DEACTIVATED ;
                }
            }
        }
#endif

        /* Copying results back to caller buffer structure */
        interfaceSlotParams->present = statusParams->present;
        interfaceSlotParams->active = statusParams->active;
        interfaceSlotParams->faulty = statusParams->faulty;
        interfaceSlotParams->status = statusParams->status;
        break;
    default:
        break;
    }    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_NCN8025IRQHandler
 * Description   : Interrupt handler for interface PHY IRQ.
 * This handler reads interface/card status, and stores in smartcard_state_t
 *
 *END**************************************************************************/
void SMARTCARD_DRV_NCN8025IRQHandler(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    smartcard_interface_slot_t * interfaceSlotParams;
    smartcard_interface_control_t interfaceControl;
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_smartcardStatePtr[instance];

    interfaceSlotParams  = (smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo]);
    
    /* Read interface/card status */
    interfaceControl = kSmartcardInterfaceReadStatus;
    SMARTCARD_DRV_NCN8025Control(instance,&interfaceControl,interfaceSlotParams);
    
    /* Invoke callback if there is one */
    if (smartcardStatePtr->interfaceCallback != NULL)
    {
      smartcardStatePtr->interfaceCallback(instance, smartcardStatePtr->interfaceCallbackParam);
    }       
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_InterfaceClockInit
 * Description   : This function initializes clock module used for card clock generation
 *
 *END**************************************************************************/
static uint16_t SMARTCARD_DRV_InterfaceClockInit(uint8_t clockModuleInstance,  uint8_t clockModuleChannel, uint32_t cardClk)
{
#if defined(EMVSIM_INSTANCE_COUNT)
    assert(clockModuleInstance < EMVSIM_INSTANCE_COUNT);
    
    EMVSIM_Type * base = g_emvsimBase[clockModuleInstance];
    uint32_t emvsimClkMhz = 0;
    uint8_t emvsimPRSCValue;
    
    /* Retrieve EMV SIM clock */
    emvsimClkMhz = CLOCK_SYS_GetEmvsimFreq(clockModuleInstance)/1000000;
    
    /* Calculate MOD value */
    emvsimPRSCValue = (emvsimClkMhz*1000)/(cardClk/1000);
    
    /* Set clock prescaler */
    EMVSIM_HAL_SetClockPrescaler(base, emvsimPRSCValue);
    
    /* Enable smart card clock */
    EMVSIM_HAL_EnableCardClock(base);
    
    return cardClk;
	
#elif defined(FTM_INSTANCE_COUNT)
    assert(clockModuleInstance < FTM_INSTANCE_COUNT);
    
    
    ftm_user_config_t ftmInfo;    
    uint32_t periph_clk_mhz = 0;
    uint16_t ftmModValue;
    FTM_Type * ftmBase = g_ftmBase[clockModuleInstance];
    uint32_t chnlPairnum = FTM_HAL_GetChnPairIndex(clockModuleChannel);
    
    /* Retrieve FTM system clock */
    periph_clk_mhz = CLOCK_SYS_GetBusClockFreq()/1000000;
    
    /* Calculate MOD value */
    ftmModValue = ((periph_clk_mhz*1000/2)/(cardClk/1000)) -1;
    
    /* Clear FTM driver user configuration */
    memset(&ftmInfo, 0, sizeof(ftmInfo));
    
    ftmInfo.BDMMode = kFtmBdmMode_11;
    ftmInfo.syncMethod = kFtmUseSoftwareTrig;
    
    /* Initialize FTM driver */
    FTM_DRV_Init(clockModuleInstance, &ftmInfo);
    
    /* Reset FTM prescaler to 'Divide by 1', i.e., to be same clock as peripheral clock  */
    FTM_HAL_SetClockPs(ftmBase, kFtmDividedBy1);
    
    /* Disable FTM counter firstly */
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);

    /* Set initial counter value */
    FTM_HAL_SetCounterInitVal(ftmBase, 0);
    
    /* Set MOD value */
    FTM_HAL_SetMod(ftmBase, ftmModValue);
    
    /*  Other initializations to defaults */
    FTM_HAL_SetCpwms(ftmBase, 0);
    FTM_HAL_SetDualChnCombineCmd(ftmBase, chnlPairnum, false);
    FTM_HAL_SetDualEdgeCaptureCmd(ftmBase, chnlPairnum, false);
    
    /* Configure mode to output compare, tougle output on match */
    FTM_HAL_SetChnEdgeLevel(ftmBase, clockModuleChannel, kFtmToggleOnMatch);
    FTM_HAL_SetChnMSnBAMode(ftmBase, clockModuleChannel, 1);
    
    /* Configure a match value to toggle output at */
    FTM_HAL_SetChnCountVal(ftmBase, clockModuleChannel, 1);

    /* Set clock source to start the counter */
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_SystemClk);
    
    /* Re-calculate the actually configured smartcard clock and return to caller */
    return (uint32_t)(((periph_clk_mhz*1000/2)/(FTM_HAL_GetMod(ftmBase)+1))*1000);
#elif defined(TPM_INSTANCE_COUNT)
    assert(clockModuleInstance < TPM_INSTANCE_COUNT);
    assert(clockModuleChannel < FSL_FEATURE_TPM_CHANNEL_COUNTn(clockModuleInstance));
    
    /* Initialize TPM driver parameter */
    tpm_pwm_param_t param = {
        kTpmCenterAlignedPWM,   /* mode */
        kTpmHighTrue,           /* edgeMode */
        cardClk,                /* uFrequencyHZ */
        50                      /* uDutyCyclePercent */
    };
    
    /* Initialize TPM driver */
    tpm_general_config_t driverInfo;
    memset(&driverInfo, 0, sizeof(driverInfo));
    
    driverInfo.isDBGMode = true;
    TPM_DRV_Init(clockModuleInstance, &driverInfo);
    
    /* Set TPM clock source, the user will have to call the Clocking API's to set the 
     * TPM module clock before calling this function */
    TPM_DRV_SetClock(clockModuleInstance, kTpmClockSourceModuleClk, kTpmDividedBy1);
    
    /* Start TPM in PWM mode to generate smart card clock */
    TPM_DRV_PwmStart(clockModuleInstance, &param, clockModuleChannel);
    
    return cardClk;
#else
    return 0;
#endif
}
/*******************************************************************************
 * EOF
 ******************************************************************************/

