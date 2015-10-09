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
#include "fsl_smartcard_direct_driver.h"
#include "fsl_emvsim_hal.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
smartcard_interface_state_t gInterfaceState[HW_SMARTCARD_INTERFACE_COUNT];
smartcard_interface_slot_t gInterfaceSlot[HW_SMARTCARD_INTERFACE_COUNT][HW_SMARTCARD_INTERFACE_SLOT_COUNT];

extern smartcard_driver_interface_t smartcardDrvInterface;
extern EMVSIM_Type * const g_emvsimBase[EMVSIM_INSTANCE_COUNT];

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
    smartcardDrvInterface.smartcardDrvInterfaceInit = SMARTCARD_DRV_DirectInit;
    smartcardDrvInterface.smartcardDrvInterfaceDeInit = SMARTCARD_DRV_DirectDeInit;
    smartcardDrvInterface.smartcardDrvInstallInterfaceCallback = SMARTCARD_DRV_DirectInstallCallback;
    smartcardDrvInterface.smartcardDrvInterfaceActivate =  SMARTCARD_DRV_DirectActivate;
    smartcardDrvInterface.smartcardDrvInterfaceDeactivate = SMARTCARD_DRV_DirectDeactivate;
    smartcardDrvInterface.smartcardDrvInterfaceControl =  SMARTCARD_DRV_DirectControl;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_DirectInit
 * Description   : This function iniitializes SMARTCARD direct interface. The function will
 * initialize direct interface speciic state, card/slot specific state, interface's control 
 * parameters, initialize card clock etc.
 *
 *END**************************************************************************/
smartcard_status_t SMARTCARD_DRV_DirectInit(uint32_t interfaceInstance, 
                               smartcard_state_t * smartcardStatePtr,
                               const smartcard_interface_config_t * interfaceUserConfig)
{    
    EMVSIM_Type * base = g_emvsimBase[smartcardStatePtr->interfaceConfig.clockModuleInstance];
    
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
    ((smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[interfaceUserConfig->cardSoltNo]))->clockToResetDelay = 40000;
    
    /*************** Initialize PHY/Interface interface ********************/
    /* Clock */
    SMARTCARD_DRV_InterfaceClockInit(smartcardStatePtr->interfaceConfig.clockModuleInstance,  smartcardStatePtr->interfaceConfig.clockModuleChannel, smartcardStatePtr->interfaceConfig.sCClock);
    
    /* Configure EMVSIM direct interface driver interrupt function */
    EMVSIM_HAL_SetCardPresenceDetectEdge(base, kEmvsimPDOnFallingEdge);
    EMVSIM_HAL_SetIntMode(base, kEmvsimIntPresenceDetect, true);
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_DirectDeInit
 * Description   : This function de-iniitializes SMARTCARD direct interface. The function will
 * clear interface speciic state, card/slot specific state, ungate card clock etc.
 *
 *END**************************************************************************/
void SMARTCARD_DRV_DirectDeInit(uint32_t instance)
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
 * Function Name : SMARTCARD_DRV_DirectInstallCallback
 * Description   : Install receive data callback function, pass in NULL pointer
 * as callback will unistall.
 *
 *END**************************************************************************/
smartcard_interface_callback_t SMARTCARD_DRV_DirectInstallCallback(uint32_t instance, 
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
 * Function Name : SMARTCARD_DRV_DirectActivate
 * Description   : Activates the smartcard interface
 *
 *END**************************************************************************/
void SMARTCARD_DRV_DirectActivate(uint32_t instance, smartcard_reset_type_t resetType)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_smartcardStatePtr[instance];
    smartcard_interface_slot_t * interfaceSlotParams = (smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo]);
    EMVSIM_Type * base = g_emvsimBase[instance];
    
    assert(smartcardStatePtr->cardParams.vcc == kSmartcardVoltageClassB3_3V);
    
    smartcardStatePtr->timersState.initCharTimerExpired = false;
    smartcardStatePtr->resetType = resetType;
    
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlInverseConvention, false);
    
    smartcardStatePtr->cardParams.Fi = 372;
    smartcardStatePtr->cardParams.currentD = 1;
    EMVSIM_HAL_SetBaudrateDivisor(base, (smartcardStatePtr->cardParams.Fi/smartcardStatePtr->cardParams.currentD));
    
    if(resetType == kSmartcardColdReset)
    {
        /* Ensure that RST is LOW and CMD is high here so that PHY goes in normal mode */
        EMVSIM_HAL_SetVCCEnable(base, true);
        EMVSIM_HAL_ResetCard(base, kEmvsimResetAssert);
        
        /* Wait for sometime as specified by EMV before pulling RST High */        
        /* As per EMV delay <= 42000 Clock cycles
         * as per PHY delay >= 1us
         */
        
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
        
        /* Pull reset HIGH Now to mark the end of Activation sequence */
        EMVSIM_HAL_ResetCard(base, kEmvsimResetDeassert);
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
        EMVSIM_HAL_ResetCard(base, kEmvsimResetAssert);
        
        /* Wait for sometime as specified by EMV before pulling RST High */        
        /* As per EMV delay <= 42000 Clock cycles
         * as per PHY delay >= 1us
         */
        
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
        /* Pull reset HIGH to mark the end of Activation sequence*/
        EMVSIM_HAL_ResetCard(base, kEmvsimResetDeassert);
    }
    
    /* Down counter trigger, and clear any pending counter status flag */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
    EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT0Timeout);
    EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
    
    /* Set counter value */
    EMVSIM_HAL_SetGPCNTValue(base, 0, INIT_DELAY_CLOCK_CYCLES + INIT_DELAY_CLOCK_CYCLES_ADJUSTMENT);
    
    /* Pre-load counter value for ATR duration delay */
    EMVSIM_HAL_SetGPCNTValue(base, 1, EMV_ATR_DURATION_ETU + ATR_DURATION_ADJUSTMENT);
    
    /* Select the clock for GPCNT for both TS detection and early start of ATR duration counter */
    EMVSIM_HAL_SetGPCClockSelect(base, 0, kEmvsimGPCCardClock);
    EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCTxClock);
    
    /* Enable counter interrupt for TS detection */
    EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt0, true);
        
    /* Trigger the counter */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);
    
    /*  Here the card was activated */
    interfaceSlotParams->active = true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_DirectDeactivate
 * Description   : De-activates the smartcard interface
 *
 *END**************************************************************************/
void SMARTCARD_DRV_DirectDeactivate(uint32_t instance)
{
    assert(instance < HW_SMARTCARD_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_smartcardStatePtr[instance];
    smartcard_interface_slot_t * interfaceSlotParams = (smartcard_interface_slot_t *)(smartcardStatePtr->interfaceState->slot[smartcardStatePtr->interfaceConfig.cardSoltNo]);
    EMVSIM_Type * base = g_emvsimBase[instance];
   
    /*Tell PHY to start Deactivation sequence by pulling CMD high*/
    EMVSIM_HAL_ResetCard(base, kEmvsimResetAssert);
    EMVSIM_HAL_SetVCCEnable(base, true);
    EMVSIM_HAL_SetCardVCCEnablePolarity(base, kEmvsimVccEnIsHigh);
    
    /*  here the card was deactivated */
    interfaceSlotParams->active = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMARTCARD_DRV_DirectControl
 * Description   : This function is used to differnet control interface/slot specific parameters
 *
 *END**************************************************************************/
void SMARTCARD_DRV_DirectControl(uint32_t instance, void *interfaceControl, void *param)
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
    EMVSIM_Type * base = g_emvsimBase[smartcardStatePtr->interfaceConfig.clockModuleInstance];
    
    switch(*interfaceControlPtr)
    {
    case kSmartcardInterfaceSetVcc:
        /* Set card parameter to VCC level set by caller */
        vcc = (smartcard_card_voltage_class_t *)param;
        
        /* Only 3.3V interface supported by the direct interface */
        assert(*vcc != kSmartcardVoltageClassB3_3V);
        
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
        
        /* Expecting active low present detect */
        statusParams->present = (EMVSIM_HAL_GetCardPresenceDetectPinStatus(base) == kEmvsimPDPinIsLow);
        
        /* Copying results back to caller buffer structure */
        interfaceSlotParams->present = statusParams->present;
        interfaceSlotParams->active = statusParams->active;

        break;
    default:
        break;
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
}
/*******************************************************************************
 * EOF
 ******************************************************************************/

