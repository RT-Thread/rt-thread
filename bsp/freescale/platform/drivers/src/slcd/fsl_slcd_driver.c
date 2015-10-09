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
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#include "fsl_slcd_driver.h"
/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_Init
 * Description   : initializes the SLCD driver.
 * This function will initialize the SLCD driver according to user configure
 * structure including clock source, power supply, contrast, frame frequency, 
 * the clock divider of generating frame frequency, duty cycle, fault detection and 
 * frame frequency interrupt status, lower power work mode.
 * Attention: Due to the register reset value depends on the reset type, so in order to avoid 
 * unexpected display, blank mode and SLCD pins are disabled in SLCD initialization.
 *
 *END**************************************************************************/
slcd_status_t SLCD_DRV_Init(uint32_t instance, const slcd_user_config_t* userConfigPtr)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    if (!userConfigPtr)
    {
        return kStatus_SLCD_NullArgument;
    }
    CLOCK_SYS_EnableSlcdClock(instance);                                                                                     /*!< Enable SLCD clock                                                             */
    SLCD_HAL_Init(base);                                                                                                     /*!< Register value depends on the reset type, so initializes SLCD to reset states */
    SLCD_HAL_ClockConfig(base, &userConfigPtr->clkConfig);                                                                   /*!< Configures SLCD clock                                                         */
    SLCD_HAL_VoltageAndPowerSupplyConfig(base, userConfigPtr->powerSupply, userConfigPtr->loadAdjust, userConfigPtr->trim);  /*!< Configures SLCD voltage power supply load just and contrast                   */
    SLCD_HAL_SetDutyCyc(base, userConfigPtr->dutyCyc);                                                                       /*!< Configures SLCD duty cycles                                                   */
    SLCD_HAL_SetLowPowerModeConfig(base, &userConfigPtr->workMode);
    if(userConfigPtr->slcdIntEnable)
    {
        INT_SYS_EnableIRQ(g_slcdIrqId[instance]);                                                                             /*!< Enable SLCD interrupt in NVIC                                                 */
    }
    
    return kStatus_SLCD_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_Deinit
 * Description   : Deinit the SLCD driver.
 * This function will deinit the SLCD driver with reset SLCD driver to reset state and
 * close SLCD clock.
 *
 *END**************************************************************************/
void SLCD_DRV_Deinit(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    INT_SYS_DisableIRQ(g_slcdIrqId[instance]);  /*!< Disables SLCD interrupt in NVIC   */
    SLCD_HAL_Init(base);                        /*!< Sets the SLCD to a workable state */
    CLOCK_SYS_DisableSlcdClock(instance);       /*!< Disables SLCD clock               */      
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_Start
 * Description   : Start SLCD counter
 * This function will enable SLCD after all configurations are finished.
 *
 *END**************************************************************************/
void SLCD_DRV_Start(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    SLCD_HAL_Enable(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_Stop
 * Description   : Stop SLCD counter
 * This function will disable SLCD driver.
 *
 *END**************************************************************************/
void SLCD_DRV_Stop(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    SLCD_HAL_Disable(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_Stop
 * Description   : Stop SLCD counter
 * This function will disable SLCD driver.
 *
 *END**************************************************************************/
void SLCD_DRV_SetIntCmd(uint32_t instance, slcd_int_type_t intType, bool enable)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    SLCD_HAL_SetIntCmd(base, intType, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_StartFaultDetection
 * Description   : This function starts SLCD fault detection.
 * Attention: This register is one-short, it clears after fault detection complete flag is set.
 * So this function should be called each time before your application wants to fault detection.
 *END**************************************************************************/
slcd_status_t SLCD_DRV_StartFaultDetection(uint32_t instance, const slcd_fault_detect_config_t *faultDetectConfigPtr)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    if (!faultDetectConfigPtr)
    {
        return kStatus_SLCD_NullArgument;
    }
    SLCD_HAL_FaultDetectionConfig(base, faultDetectConfigPtr); /*!< SLCD fault detection configuration                                                    */
    SLCD_HAL_SetFaultDetectCmd(base, true);                     /*!< Once this register is assert, test frame is inserted after a normal SLCD refresh frame */
    
    return kStatus_SLCD_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_CheckFaultDetectCompleteFlag
 * Description   : This function checks if SLCD fault detection is complete.
 * When fault detection is complete, the fault detection complete flag is set.
 *END**************************************************************************/
bool SLCD_DRV_CheckFaultDetectCompleteFlag(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    return SLCD_HAL_GetFaultDetectCompleteFlag(base);  /*!< Indicates that the fault detection is completed */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_ClearFaultDetectCompleteFlag
 * Description   : This function clears SLCD fault detection complete flag.
 * When fault detection complete interrupt is enabled and fault complete flag is set
 * then a SLCD interrupt request is assert, and write one to this register to clear interrupt request.
 *END**************************************************************************/
void SLCD_DRV_ClearFaultDetectCompleteFlag(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
	
    SLCD_HAL_ClearFaultDetectCompleteFlag(base);  /*!< clears SLCD fault detection complete flag */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_GetFaultDetectCounter
 * Description   : This function gets SLCD fault detection counter.
 *
 *END**************************************************************************/
uint8_t SLCD_DRV_GetFaultDetectCounter(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];

    return SLCD_HAL_GetFaultDetectCounter(base); /*!< Contains how many ¡°one/high¡± are sampled inside the fault detect sample window */
}
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_CheckFrameFrequencyIntFlag
 * Description   : when frame frequency interrupt is enabled this function checks a frame frequency interrupt condition has occurred or not.
 *
 *END**************************************************************************/
bool SLCD_DRV_CheckFrameFrequencyIntFlag(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
	
    return SLCD_HAL_GetFrameFrequencyIntFlag(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_ClearFrameFrequencyIntFlag
 * Description   : This function clears the frame frequency interrupt.
 *
 *END**************************************************************************/
void SLCD_DRV_ClearFrameFrequencyIntFlag(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];

    SLCD_HAL_ClearFrameFrequencyIntFlag(base);
}
#endif
/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_SetBlinkConfig
 * Description   : This function starts SLCD blinking mode.
 *
 *END**************************************************************************/
slcd_status_t SLCD_DRV_StartBlinkingMode(uint32_t instance, const slcd_blink_config_t *blinkConfigPtr)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    if (!blinkConfigPtr)
    {
        return kStatus_SLCD_NullArgument;
    }
    SLCD_HAL_BlinkingModeConfig(base, blinkConfigPtr);  /*!< Configures SLCD blinking mode */
    SLCD_HAL_SetBlinkCmd(base, 1U);                     /*!< Enables blinking display mode */
    
    return kStatus_SLCD_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_StopBlinkingMode
 * Description   : This function stops SLCD blinking mode.
 *
 *END**************************************************************************/
void SLCD_DRV_StopBlinkingMode(uint32_t instance)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];
    
    SLCD_HAL_SetBlinkCmd(base,  0U);  /*!< Disables blinking display mode */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_SetAltDisplayModeCmd
 * Description   : This function starts/stops SLCD alternating display mode.
 *
 *END**************************************************************************/
 void SLCD_DRV_SetAltDisplayModeCmd(uint32_t instance, bool enable)
 {
     assert(instance < LCD_INSTANCE_COUNT);
     LCD_Type * base = g_slcdBase[instance];
     
     SLCD_HAL_SetAltDisplayModeCmd(base, enable);
 }

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_SetBlankDisplayModeCmd
 * Description   : This function starts/stops SLCD blank display mode.
 *
 *END**************************************************************************/
void SLCD_DRV_SetBlankDisplayModeCmd(uint32_t instance, bool enable)
{
     assert(instance < LCD_INSTANCE_COUNT);
     LCD_Type * base = g_slcdBase[instance];
     
     SLCD_HAL_SetBlankDisplayModeCmd(base, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_SetAllPinsConfig
 * Description   : This function configures all SLCD pins.
 *
 *END**************************************************************************/

slcd_status_t SLCD_DRV_SetAllPinsConfig(uint32_t instance, const slcd_pins_config_t *pinsConfigPtr)
{
    assert(instance < LCD_INSTANCE_COUNT);
    LCD_Type * base = g_slcdBase[instance];

    if (!pinsConfigPtr)
    {
        return kStatus_SLCD_NullArgument;
    }
    SLCD_HAL_SetPinsEnableCmd(base, 0, pinsConfigPtr->slcdLowPinsEnabled);
    SLCD_HAL_SetPinsEnableCmd(base, 1, pinsConfigPtr->slcdHighPinsEnabled);
    SLCD_HAL_SetBackPlanePinsEnableCmd(base, 0, pinsConfigPtr->slcdBackPlaneLowPinsEnabled);
    SLCD_HAL_SetBackPlanePinsEnableCmd(base, 1, pinsConfigPtr->slcdBackPlaneHighPinsEnabled);
    
    return kStatus_SLCD_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_SetWaveForm
 * Description   : This function configures one SLCD pin wave form.
 *
 *END**************************************************************************/
 void SLCD_DRV_SetPinWaveForm(uint32_t instance, uint8_t pinIndex, uint8_t waveForm)
 {
     assert(instance < LCD_INSTANCE_COUNT);
     LCD_Type * base = g_slcdBase[instance];
     
     SLCD_HAL_SetPinWaveForm(base, pinIndex, waveForm);
 }
 
/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_SetBackPlanePhase
 * Description   : This function configures back plane phase.
 *
 *END**************************************************************************/
 void SLCD_DRV_SetBackPlanePhase(uint32_t instance, uint8_t pinIndex, slcd_phase_index_t phase)
 {
     assert(instance < LCD_INSTANCE_COUNT);
     LCD_Type * base = g_slcdBase[instance];
     
     SLCD_HAL_SetBackPlanePhase(base, pinIndex, phase);
 }
 
/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_DRV_SetSegementEnabledCmd
 * Description   : This function configures one SLCD segement enabled status.
 *
 *END**************************************************************************/
void SLCD_DRV_SetSegmentEnableCmd(uint32_t instance, uint8_t pinIndex, slcd_phase_index_t phaseIndex, bool enable)
{
     assert(instance < LCD_INSTANCE_COUNT);
     LCD_Type * base = g_slcdBase[instance];
     
     SLCD_HAL_SetPinWaveFormPhaseCmd(base, pinIndex, phaseIndex, enable);
}

/*******************************************************************************
 * EOF
 *******************************************************************************/


