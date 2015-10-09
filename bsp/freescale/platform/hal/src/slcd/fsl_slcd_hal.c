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
#include "fsl_slcd_hal.h"
/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 *******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_HAL_ClockConfig
 * Description   : Initialize SLCD clock.
 *
 *END**************************************************************************/
void SLCD_HAL_ClockConfig(LCD_Type * base, const slcd_clk_config_t *clkConfigPtr)
{
    uint32_t value = 0;
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE && FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE
    value = LCD_GCR_SOURCE_MASK | LCD_GCR_ALTDIV_MASK | LCD_GCR_LCLK_MASK | LCD_GCR_FFR_MASK | LCD_GCR_ALTSOURCE_MASK;
#else
    value = LCD_GCR_SOURCE_MASK | LCD_GCR_ALTDIV_MASK | LCD_GCR_LCLK_MASK;
#endif
    value = LCD_RD_GCR(base) & (~value);
    LCD_WR_GCR(base, value); /*!< Clear the bit feild due to register reset value depends on the reset type */
    value = 0;
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE && FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE
    value = LCD_GCR_SOURCE(clkConfigPtr->clkSrc) | LCD_GCR_ALTDIV(clkConfigPtr->altClkDiv) | LCD_GCR_LCLK(clkConfigPtr->clkPrescaler) | 
            LCD_GCR_ALTSOURCE(clkConfigPtr->altClkSrc) | LCD_GCR_FFR(clkConfigPtr->fastFrameRateEnable);
#else
    value = LCD_GCR_SOURCE(clkConfigPtr->clkSrc) | LCD_GCR_ALTDIV(clkConfigPtr->altClkDiv) | LCD_GCR_LCLK(clkConfigPtr->clkPrescaler);
#endif
    value = LCD_RD_GCR(base) | value;
    LCD_WR_GCR(base, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_HAL_VoltageAndPowerSupplyConfig
 * Description   : Initialize SLCD voltage, power supply and contrast.
 *
 *END**************************************************************************/
void SLCD_HAL_VoltageAndPowerSupplyConfig(LCD_Type * base, slcd_power_supply_option_t powerSupply, slcd_load_adjust_t loadAdjust, slcd_regulated_voltage_trim_t trim)   
{
    uint32_t value = 0;
    value = LCD_GCR_RVEN_MASK | LCD_GCR_CPSEL_MASK | LCD_GCR_VSUPPLY_MASK | LCD_GCR_LADJ_MASK | LCD_GCR_RVTRIM_MASK;
    value = LCD_RD_GCR(base) & (~value);
    LCD_WR_GCR(base, value); /*!< Clear the bit feild due to register reset value depends on the reset type */    
    value = 0;
    value = LCD_GCR_RVEN(powerSupply&1U) | LCD_GCR_CPSEL(((uint32_t)powerSupply>>1U)&1U) | 
             LCD_GCR_VSUPPLY(((uint32_t)powerSupply>>2U)&1U) | LCD_GCR_LADJ(loadAdjust) | LCD_GCR_RVTRIM(trim);
    value = LCD_RD_GCR(base) | value;
    LCD_WR_GCR(base, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_HAL_BlinkingModeConfig
 * Description   : Configures SLCD blinking mode.
 *
 *END**************************************************************************/
void SLCD_HAL_BlinkingModeConfig(LCD_Type * base, const slcd_blink_config_t *blinkConfigPtr)
{
    uint32_t value = 0;
    assert(blinkConfigPtr);
    value = LCD_AR_BRATE_MASK | LCD_AR_BMODE_MASK;
    value = LCD_RD_AR(base) & (~value);
    LCD_WR_AR(base, value);   /*!< Clear the bit field due to register reset value depends on the reset type */   
    value = 0;
    value = LCD_AR_BRATE(blinkConfigPtr->blinkRate) | LCD_AR_BMODE(blinkConfigPtr->blinkMode);
    value = LCD_RD_AR(base) | value;
    LCD_WR_AR(base, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_HAL_SetWorkModeCmd
 * Description   : Configures SLCD work mode in stop/doze mode.
 *
 *END**************************************************************************/
void SLCD_HAL_SetLowPowerModeConfig(LCD_Type * base, const slcd_work_mode_t *workMode)
{
    uint32_t value = 0;
    value = LCD_GCR_LCDDOZE_MASK | LCD_GCR_LCDSTP_MASK;
    value = LCD_RD_GCR(base) &(~value);
    LCD_WR_GCR(base, value);           /*!< Clear the bit feild due to register reset value depends on the reset type */
    value = 0;
    value = LCD_GCR_LCDDOZE(workMode->kSLCDEnableInDozeMode) | LCD_GCR_LCDSTP(workMode->kSLCDEnableInStopMode);
    value = LCD_RD_GCR(base) | value;
    LCD_WR_GCR(base, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_HAL_SetIntCmd
 * Description   : Configures SLCD interrupt.
 *
 *END**************************************************************************/
void SLCD_HAL_SetIntCmd(LCD_Type * base, slcd_int_type_t intType, bool enable)
{
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    if(kSLCDFrameFreqInt | intType)
    {
        LCD_BWR_GCR_LCDIEN(base, enable);
    }
#endif
    if(kSLCDFaultDetectionCompleteInt | intType)
    {
        LCD_WR_GCR_FDCIEN(base, enable);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_HAL_FaultDetectionConfig
 * Description   : Configures SLCD fault detection.
 *
 *END**************************************************************************/
void SLCD_HAL_FaultDetectionConfig(LCD_Type * base, const slcd_fault_detect_config_t *faultDetectConfigPtr)
{
    uint32_t value = 0;
    assert(faultDetectConfigPtr);
    value = LCD_FDCR_FDPINID_MASK | LCD_FDCR_FDBPEN_MASK | LCD_FDCR_FDSWW_MASK | LCD_FDCR_FDPRS_MASK;
    value = LCD_RD_FDCR(base) & (~value);
    LCD_WR_FDCR(base, value);  /*!< Clear the bit feild due to register reset value depends on the reset type */ 
    value = 0;
    value = LCD_FDCR_FDPINID(faultDetectConfigPtr->faultDetectPinIndex) | LCD_FDCR_FDBPEN(faultDetectConfigPtr->faultDetectBackPlaneEnabled) |
            LCD_FDCR_FDSWW(faultDetectConfigPtr->winWidth) | LCD_FDCR_FDPRS(faultDetectConfigPtr->prescaler);
    value = LCD_RD_FDCR(base) | value;
    LCD_WR_FDCR(base, value);
    LCD_BWR_GCR_FDCIEN(base, faultDetectConfigPtr->faultDetectCompleteIntEnabled); /*!< Configures fault detection complete interrupt enabled or disabled */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SLCD_HAL_Init
 * Description   : Initialize SLCD module to workable state.
 *
 *END**************************************************************************/
void SLCD_HAL_Init(LCD_Type * base)
{
   uint8_t i;
   slcd_clk_config_t clkConfig;
   clkConfig.clkSrc              = kSLCDDefaultClk;
#if FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE
   clkConfig.altClkSrc           = kSLCDAltClkSrc1;
#endif
   clkConfig.altClkDiv           = kSLCDAltClkDivFactor1;
   clkConfig.clkPrescaler        = kSLCDClkPrescaler00;
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE
   clkConfig.fastFrameRateEnable = false;
#endif
   
   LCD_WR_AR(base, 0);
   LCD_WR_FDCR(base, 0);
   LCD_WR_FDSR(base, 0);
   LCD_WR_PEN(base, 0, 0);
   LCD_WR_PEN(base, 1, 0);
   LCD_WR_BPEN(base, 0, 0);
   LCD_WR_BPEN(base, 1, 0);
   SLCD_HAL_Disable(base);
   SLCD_HAL_ClockConfig(base, &clkConfig);
   SLCD_HAL_VoltageAndPowerSupplyConfig(base, kSLCDPowerInternalVll3AndChargePump, kSLCDHighLoadOrSlowestClkSrc, kSLCDRegulatedVolatgeTrim08);
   for(i = 0; i < FSL_FEATURE_SLCD_HAS_PIN_NUM; i++)
   {
      SLCD_HAL_SetPinWaveForm(base, i, (uint8_t)0x00);
   }
}

/*******************************************************************************
 * EOF
 *******************************************************************************/
