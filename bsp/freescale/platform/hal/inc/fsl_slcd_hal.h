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
#ifndef __FSL_SLCD_HAL_H__
#define __FSL_SLCD_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup slcd_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief SLCD to handle different LCD glass capacitance. */
typedef enum _slcd_load_adjust
{
    kSLCDLowLoadOrFastestClkSrc       = 0U,  /*!< Adjust the resistor bias network in low load or selects fastest clock for charge pump. @internal gui name="Low load, fastest clock source" */
    kSLCDLowLoadOrIntermediateClkSrc  = 1U,  /*!< Adjust the resistor bias network in low load or selects intermediate clock for charge pump. @internal gui name="Low load, intermediate clock source" */
    kSLCDHighLoadOrIntermediateClkSrc = 2U,  /*!< Adjust the resistor bias network in high load or selects intermediate clock for charge pump. @internal gui name="High load, intermediate clock source" */
    kSLCDHighLoadOrSlowestClkSrc      = 3U   /*!< Adjust the resistor bias network in high load or selects slowest clock for charge pump. @internal gui name="High load, slowest clock source" */
}slcd_load_adjust_t;

/*! @breif adjust the regulated voltage to meet the desired contrast */
typedef enum _slcd_regulated_voltage_trim
{
    kSLCDRegulatedVolatgeTrim00 = 0U,  /*!< Increase the voltage to 0.91 V @internal gui name="0.91 V" */
    kSLCDRegulatedVolatgeTrim01 = 1U,  /*!< Increase the voltage to 1.01 V @internal gui name="1.01 V" */
    kSLCDRegulatedVolatgeTrim02 = 2U,  /*!< Increase the voltage to 0.96 V @internal gui name="0.96 V" */
    kSLCDRegulatedVolatgeTrim03 = 3U,  /*!< Increase the voltage to 1.06 V @internal gui name="1.06 V" */
    kSLCDRegulatedVolatgeTrim04 = 4U,  /*!< Increase the voltage to 0.93 V @internal gui name="0.93 V" */
    kSLCDRegulatedVolatgeTrim05 = 5U,  /*!< Increase the voltage to 1.02 V @internal gui name="1.02 V" */
    kSLCDRegulatedVolatgeTrim06 = 6U,  /*!< Increase the voltage to 0.98 V @internal gui name="0.98 V" */
    kSLCDRegulatedVolatgeTrim07 = 7U,  /*!< Increase the voltage to 1.08 V @internal gui name="1.08 V" */
    kSLCDRegulatedVolatgeTrim08 = 8U,  /*!< Increase the voltage to 0.92 V @internal gui name="0.92 V" */
    kSLCDRegulatedVolatgeTrim09 = 9U,  /*!< Increase the voltage to 1.02 V @internal gui name="1.02 V" */
    kSLCDRegulatedVolatgeTrim10 = 10U, /*!< Increase the voltage to 0.97 V @internal gui name="0.97 V" */
    kSLCDRegulatedVolatgeTrim11 = 11U, /*!< Increase the voltage to 1.07 V @internal gui name="1.07 V" */
    kSLCDRegulatedVolatgeTrim12 = 12U, /*!< Increase the voltage to 0.94 V @internal gui name="0.94 V" */
    kSLCDRegulatedVolatgeTrim13 = 13U, /*!< Increase the voltage to 1.05 V @internal gui name="1.05 V" */
    kSLCDRegulatedVolatgeTrim14 = 14U, /*!< Increase the voltage to 0.99 V @internal gui name="0.99 V" */
    kSLCDRegulatedVolatgeTrim15 = 15U  /*!< Increase the voltage to 1.09 V @internal gui name="1.09 V" */
}slcd_regulated_voltage_trim_t;


/*! @brief SLCD alternate clock divider */
typedef enum _slcd_alt_clk_div
{
    kSLCDAltClkDivFactor1   = 0U,   /*!< No divide for alternate clock. @internal gui name="1" */
    kSLCDAltClkDivFactor64  = 1U,   /*!< Divide alternate clock with factor 64. @internal gui name="64" */
    kSLCDAltClkDivFactor256 = 2U,   /*!< Divide alternate clock with factor 256. @internal gui name="256" */
    kSLCDAltClkDivFactor512 = 3U    /*!< Divide alternate clock with factor 512. @internal gui name="512" */
}slcd_alt_clk_div_t;

/*! @brief SLCD clock source */
typedef enum _slcd_clk_src
{
    kSLCDDefaultClk   = 0U,   /*!< Select default clock as lcd clock source. @internal gui name="Default" */
    kSLCDAlternateClk = 1U    /*!< Select alternate clock as lcd clock source. @internal gui name="Alternate" */
}slcd_clk_src_t;

/*! @brief SLCD alternate clock source */
typedef enum _slcd_alt_clk_src
{
    kSLCDAltClkSrc1 = 0U,   /*!< Select default alternate clock. @internal gui name="Clock source 1" */
    kSLCDAltClkSrc2 = 1U    /*!< Select alternate clock source 2. @internal gui name="Clock source 2" */
}slcd_alt_clk_src_t;

/*! @brief SLCD clock prescaler to generate frame frequency */
typedef enum _slcd_clk_prescaler
{
    kSLCDClkPrescaler00 = 0U, /*!< Prescaler 0. @internal gui name="0" */
    kSLCDClkPrescaler01 = 1U, /*!< Prescaler 1. @internal gui name="1" */
    kSLCDClkPrescaler02 = 2U, /*!< Prescaler 2. @internal gui name="2" */
    kSLCDClkPrescaler03 = 3U, /*!< Prescaler 3. @internal gui name="3" */
    kSLCDClkPrescaler04 = 4U, /*!< Prescaler 4. @internal gui name="4" */
    kSLCDClkPrescaler05 = 5U, /*!< Prescaler 5. @internal gui name="5" */
    kSLCDClkPrescaler06 = 6U, /*!< Prescaler 6. @internal gui name="6" */
    kSLCDClkPrescaler07 = 7U  /*!< Prescaler 7.  @internal gui name="7" */
}slcd_clk_prescaler_t;

/*! @brief SLCD duty cycle */
typedef enum _slcd_duty_cyc
{
    kSLCD1DutyCyc     = 0U,  /*!< LCD use 1/1 duty cycle @internal gui name="1/1" */
    kSLCD1Div2DutyCyc = 1U,  /*!< LCD use 1/2 duty cycle @internal gui name="1/2" */
    kSLCD1Div3DutyCyc = 2U,  /*!< LCD use 1/3 duty cycle @internal gui name="1/3" */
    kSLCD1Div4DutyCyc = 3U,  /*!< LCD use 1/4 duty cycle @internal gui name="1/4" */
    kSLCD1Div5DutyCyc = 4U,  /*!< LCD use 1/5 duty cycle @internal gui name="1/5" */
    kSLCD1Div6DutyCyc = 5U,  /*!< LCD use 1/6 duty cycle @internal gui name="1/6" */
    kSLCD1Div7DutyCyc = 6U,  /*!< LCD use 1/7 duty cycle @internal gui name="1/7" */
    kSLCD1Div8DutyCyc = 7U   /*!< LCD use 1/8 duty cycle @internal gui name="1/8" */
}slcd_duty_cyc_t;

/*! @brief SLCD segement index */
typedef enum _slcd_phase_index
{
    kSLCDPhaseA = 0U,  /*!< LCD waveform phase A */
    kSLCDPhaseB = 1U,  /*!< LCD waveform phase B */
    kSLCDPhaseC = 2U,  /*!< LCD waveform phase C */
    kSLCDPhaseD = 3U,  /*!< LCD waveform phase D */
    kSLCDPhaseE = 4U,  /*!< LCD waveform phase E */
    kSLCDPhaseF = 5U,  /*!< LCD waveform phase F */
    kSLCDPhaseG = 6U,  /*!< LCD waveform phase G */
    kSLCDPhaseH = 7U   /*!< LCD waveform phase H */
}slcd_phase_index_t;

/*! @brief SLCD blink mode */
typedef enum _slcd_blink_mode
{
    kSLCDBlankDisplay = 0U,   /*!< Display blank during the blink period.                                           */
    kSLCDAltDisplay   = 1U    /*!< Display alternate display during the blink period if duty cycle is lower than 5. */
}slcd_blink_mode_t;

/*! @brief SLCD blink rate */
typedef enum _slcd_blink_rate
{
    kSLCDBlinkRate00 = 0U,  /*!< SLCD blink rate is LCD clock/((2^12)) */ 
    kSLCDBlinkRate01 = 1U,  /*!< SLCD blink rate is LCD clock/((2^13)) */
    kSLCDBlinkRate02 = 2U,  /*!< SLCD blink rate is LCD clock/((2^14)) */
    kSLCDBlinkRate03 = 3U,  /*!< SLCD blink rate is LCD clock/((2^15)) */
    kSLCDBlinkRate04 = 4U,  /*!< SLCD blink rate is LCD clock/((2^16)) */
    kSLCDBlinkRate05 = 5U,  /*!< SLCD blink rate is LCD clock/((2^17)) */
    kSLCDBlinkRate06 = 6U,  /*!< SLCD blink rate is LCD clock/((2^18)) */
    kSLCDBlinkRate07 = 7U   /*!< SLCD blink rate is LCD clock/((2^19)) */
}slcd_blink_rate_t;

/*! 
 * @brief This structure describes SLCD blink configuration.
 */
typedef struct SlcdBlinkConfig
{
   slcd_blink_rate_t blinkRate;  /*!< SLCD blinking frequency configuration                */
   slcd_blink_mode_t blinkMode;  /*!< Selects the SLCD display mode during blinking period */
}slcd_blink_config_t;

/*! 
 * @brief This structure describes SLCD power supply configuration.
 */
typedef enum SlcdPowerSupplyOption
{
    kSLCDPowerReserved0                      = 0U,   /*!< Unused right now @internal gui name="" */
    kSLCDPowerReserved1                      = 1U,   /*!< Unused right now @internal gui name="" */
    kSLCDPowerInternalVll3AndChargePump      = 2U,   /*!< VLL3 connected to VDD internally and charge pump is used to generate VLL1 and VLL2 @internal gui name="VLL3 to VDD, charge pump" */
    kSLCDPowerReserved2                      = 3U,   /*!< Unused right now @internal gui name="" */
    kSLCDPowerExternalVll3AndResistorNetWork = 4U,   /*!< VLL3 is driven externally and resistor bias network is used to generate VLL1 and VLL2 @internal gui name="External VLL3, resistor network" */
    kSLCDPowerReserved3                      = 5U,   /*!< Unused right now @internal gui name="" */
    kSLCDPowerExternalVll3AndChargePump      = 6U,   /*!< VLL3 is driven externally and charge pump is used to generate VLL1 and VLL2 @internal gui name="External VLL3, charge pump" */
    kSLCDPowerVll1AndChargePump              = 7U,   /*!< VIREG is connected to VLL1 internally and charge pump is used to generate VLL2 and VLL3 @internal gui name="VLL1 to VIREG, charge pump" */
}slcd_power_supply_option_t;

/*! @brief SLCD fault detect clock prescaler */
typedef enum _slcd_fault_detect_clk_prescaler
{
    kSLCDFaultSampleFreq1BusClk       = 0U,  /*!< Fault detect sample clock frequency is 1/1 bus clock   */
    kSLCDFaultSampleFreq1Div2BusClk   = 1U,  /*!< Fault detect sample clock frequency is 1/2 bus clock   */
    kSLCDFaultSampleFreq1Div4BusClk   = 2U,  /*!< Fault detect sample clock frequency is 1/4 bus clock   */
    kSLCDFaultSampleFreq1Div8BusClk   = 3U,  /*!< Fault detect sample clock frequency is 1/8 bus clock   */
    kSLCDFaultSampleFreq1Div16BusClk  = 4U,  /*!< Fault detect sample clock frequency is 1/16 bus clock  */
    kSLCDFaultSampleFreq1Div32BusClk  = 5U,  /*!< Fault detect sample clock frequency is 1/32 bus clock  */
    kSLCDFaultSampleFreq1Div64BusClk  = 6U,  /*!< Fault detect sample clock frequency is 1/64 bus clock  */
    kSLCDFaultSampleFreq1Div128BusClk = 7U   /*!< Fault detect sample clock frequency is 1/128 bus clock */
}slcd_fault_detect_clk_prescaler_t;

/*! @brief SLCD fault detect sample window width */
typedef enum _slcd_fault_detect_sample_win_width
{
    kSLCDFaultDetectWinWidth4SampleClk   = 0U,  /*!< Sample window width is 4 sample clock cycles   */
    kSLCDFaultDetectWinWidth8SampleClk   = 1U,  /*!< Sample window width is 8 sample clock cycles   */
    kSLCDFaultDetectWinWidth16SampleClk  = 2U,  /*!< Sample window width is 16 sample clock cycles  */
    kSLCDFaultDetectWinWidth32SampleClk  = 3U,  /*!< Sample window width is 32 sample clock cycles  */
    kSLCDFaultDetectWinWidth64SampleClk  = 4U,  /*!< Sample window width is 64 sample clock cycles  */
    kSLCDFaultDetectWinWidth128SampleClk = 5U,  /*!< Sample window width is 128 sample clock cycles */
    kSLCDFaultDetectWinWidth256SampleClk = 6U,  /*!< Sample window width is 256 sample clock cycles */
    kSLCDFaultDetectWinWidth512SampleClk = 7U   /*!< Sample window width is 512 sample clock cycles */
}slcd_fault_detect_sample_win_width_t;

/*! 
 * @brief This structure describes SLCD fault detection configuration.
 */
typedef struct SlcdFaultDetectionConfig
{
   bool                                 faultDetectCompleteIntEnabled;   /*!< Fault detect complete interrupt enabled or disabled                                   */
   bool                                 faultDetectBackPlaneEnabled;     /*!< True means the type of pin id that fault detected is back plane otherwise front plane */
   uint8_t                              faultDetectPinIndex;             /*!< Fault detected pin id  from 0 to 63                                                   */
   slcd_fault_detect_clk_prescaler_t    prescaler;                       /*!< Fault detected clock prescaler                                                        */
   slcd_fault_detect_sample_win_width_t winWidth;                        /*!< Fault detected sample window width                                                    */
}slcd_fault_detect_config_t;

/*! 
 * @brief This union structure describes SLCD work mode configuration.
 */
typedef struct _slcd_work_mode
{
    bool kSLCDEnableInDozeMode;  /*!< false means enabled in doze mode */
    bool kSLCDEnableInStopMode;  /*!< false means enabled in stop mode */
}slcd_work_mode_t;

/*! 
 * @brief This enum structure describes SLCD interrupt configuration.
 */
typedef enum _slcd_int_type
{
   kSLCDFrameFreqInt              = 1U,  /*!< SLCD frame frequency interrupt is enabled or disabled                            */
   kSLCDFaultDetectionCompleteInt = 2U,  /*!< SLCD fault detection complete interrupt is enabled or disabled                   */
   kSLCDEnableAllInt              = 3U   /*!< SLCD both frame frequency and fault detection interrupts are enabled or disabled */
}slcd_int_type_t;

/*! 
 * @brief This structure describes SLCD clock and frame configuration.
 * 
 */
typedef struct _slcd_clk_config
{
    slcd_clk_src_t       clkSrc; /*!< Clock source. @internal gui name="Clock source" */
#if FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE
    slcd_alt_clk_src_t   altClkSrc; /*!< Alternate clock source. @internal gui name="Alternate clock source" */
#endif
    slcd_alt_clk_div_t   altClkDiv; /*!< Functions as a clock divider to divide the alternate clock before it is selected as LCD clock source. @internal gui name="Alternate clock divider" */
    slcd_clk_prescaler_t clkPrescaler; /*!< Clock prescaler. @internal gui name="Clock prescaler" */
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE
    bool                 fastFrameRateEnable; /*!< Increases the Frame Clock Frequency from 23.3-73.1 Hz to 46.6-146.2 Hz. @internal gui name="Fast frame rate" */
#endif
}slcd_clk_config_t;

/*! @brief SLCD status return codes.*/
typedef enum _SLCD_status {
    kStatus_SLCD_Success      = 0x0U, /*!< Succeed          */
    kStatus_SLCD_NullArgument = 0x1U, /*!< Argument is NULL */
    kStatus_SLCD_Fail         = 0x2U  /*!< SLCD failed      */
 } slcd_status_t;

/*! @brief SLCD  */

/*******************************************************************************
 ** Variables
 *******************************************************************************/

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SLCD HAL.
 * @{
 */

/*!
 * @brief Enables the SLCD module operation.
 *
 * @param base Base address of SLCD peripheral instance.
 */
static inline void SLCD_HAL_Enable(LCD_Type * base)
{
    LCD_BWR_GCR_LCDEN(base, 1U);
}

/*!
 * @brief Disables the SLCD module operation.
 *
 * @param base Base address of SLCD peripheral instance.
 */
static inline void SLCD_HAL_Disable(LCD_Type * base)
{
    LCD_BWR_GCR_LCDEN(base, 0U);
}

/*!
 * @brief Configures the SLCD duty cycle.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param dutyCyc LCD duty cycle.
 */
static inline void SLCD_HAL_SetDutyCyc(LCD_Type * base, slcd_duty_cyc_t dutyCyc)
{
    LCD_BWR_GCR_DUTY(base, dutyCyc);
}

#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
/*!
 * @brief Checks the SLCD frame frequency interrupt flag.
 *
 * @param base Base address of SLCD peripheral instance.
 * @return the status to indicate if start of SLCD frame has occurred
 *         - true: start of SLCD frame has occurred
 *         - false: frame frequency interrupt condition has not occurred
 */
static inline bool SLCD_HAL_GetFrameFrequencyIntFlag(LCD_Type * base)
{
    return (bool)LCD_BRD_AR_LCDIF(base);
}

/*!
 * @brief Clears the SLCD frame frequency interrupt flag with write 1 to this bit.
 *
 * @param base Base address of SLCD peripheral instance.
 */
static inline void SLCD_HAL_ClearFrameFrequencyIntFlag(LCD_Type * base)
{
    LCD_BWR_AR_LCDIF(base, 1U);
}
#endif

/*!
 * @brief Configures the SLCD blink command.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param enable Enable/Disable SLCD blinking mode.
 */
static inline void SLCD_HAL_SetBlinkCmd(LCD_Type * base, bool enable)
{
    LCD_BWR_AR_BLINK(base, enable);
}

/*!
 * @brief Configures the SLCD display mode.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param enable Enable/Disable SLCD alternate display mode.
 */
static inline void SLCD_HAL_SetAltDisplayModeCmd(LCD_Type * base, bool enable)
{
    LCD_BWR_AR_ALT(base, enable);
}

/*!
 * @brief Configures the SLCD blank mode.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param enable Enable/Disable SLCD blank mode.
 */
static inline void SLCD_HAL_SetBlankDisplayModeCmd(LCD_Type * base, bool enable)
{
    LCD_BWR_AR_BLANK(base, enable);
}

#if FSL_FEATURE_SLCD_HAS_PAD_SAFE
/*!
 * @brief Configures the SLCD pad safe state.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param enable Enable/Disable SLCD blank mode.
 */
static inline void SLCD_HAL_SetPadSafeStateEnableCmd(LCD_Type * base, bool enable)
{
    LCD_BWR_GCR_PADSAFE(base, enable);
}
#endif

/*!
 * @brief Configures the SLCD fault detection enable.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param enable Enable/Disable SLCD blank mode.
 */
static inline void SLCD_HAL_SetFaultDetectCmd(LCD_Type *base, bool enable)
{
    LCD_WR_FDCR_FDEN(base, enable);
}

/*!
 * @brief Returns the SLCD fault detect complete flag.
 *
 * This function indicates that the fault detection is completed.
 *
 * @param base Base address of SLCD peripheral instance.
 * @return Fault detect complete flag state.
 */
static inline bool SLCD_HAL_GetFaultDetectCompleteFlag(LCD_Type * base)
{
    return (bool)LCD_BRD_FDSR_FDCF(base);
}

/*!
 * @brief Clears the SLCD fault detect complete flag.
 *
 * This function clear fault detect complete flag.
 *
 * @param base Base address of SLCD peripheral instance.
 */
static inline void SLCD_HAL_ClearFaultDetectCompleteFlag(LCD_Type * base)
{
    LCD_BWR_FDSR_FDCF(base, 1U);
}

/*!
 * @brief Returns the SLCD fault detect counter.
 *
 * @param base Base address of SLCD peripheral instance.
 * @return Counter value.
 */
static inline uint32_t SLCD_HAL_GetFaultDetectCounter(LCD_Type * base)
{
    return LCD_BRD_FDSR_FDCNT(base);
}

/*!
 * @brief Configures all SLCD pins enabled states.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param highReg 0 means low pin register, 1 means high pin register.
 * @param data SLCD pins enabled status.
 */
static inline void SLCD_HAL_SetPinsEnableCmd(LCD_Type * base, uint8_t highReg, uint32_t data)
{
    LCD_WR_PEN(base, highReg, data);
}

/*!
 * @brief Configures all SLCD pins type in high back plane register.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param highReg 0 means low pin back panel register, 1 means high pin back panel register.
 * @param data ALL SLCD back plane enabled status.
 */
static inline void SLCD_HAL_SetBackPlanePinsEnableCmd(LCD_Type * base, uint8_t highReg, uint32_t data)
{
    LCD_WR_BPEN(base, highReg, data);
}

/*!
 * @brief Configures the SLCD pin waveform phase.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param pinIndex SLCD waveform number[0 63].
 * @param waveForm SLCD pin phase.
 */
static inline void SLCD_HAL_SetPinWaveForm(LCD_Type * base, uint8_t pinIndex, uint8_t waveForm)
{
    assert(pinIndex < FSL_FEATURE_SLCD_HAS_PIN_NUM);
    
    LCD_WR_WF8B(base, pinIndex, waveForm);
}

/*!
 * @brief Configures the SLCD pin waveform phase.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param pinIndex SLCD waveform number[0 63].
 * @param phase Configures SLCD back plane valid phase.
 */
static inline void SLCD_HAL_SetBackPlanePhase(LCD_Type * base, uint8_t pinIndex, slcd_phase_index_t phase)
{
    assert(pinIndex < FSL_FEATURE_SLCD_HAS_PIN_NUM);
    
    LCD_WR_WF8B(base, pinIndex, (uint8_t)(1<<(uint32_t)phase));
}

/*!
 * @brief Configures the SLCD pin waveform one phase.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param pinIndex SLCD waveform number[0 63].
 * @param phaseIndex SLCD pin phase.
 * @param enable Enable/Disable the specific phase for a pin.
 */
static inline void SLCD_HAL_SetPinWaveFormPhaseCmd(LCD_Type * base, uint8_t pinIndex, slcd_phase_index_t phaseIndex, bool enable)
{
    assert(pinIndex < FSL_FEATURE_SLCD_HAS_PIN_NUM && phaseIndex < FSL_FEATURE_SLCD_HAS_PHASE_NUM);
    
    LCD_BWR_WF8B_BPLCD(base, pinIndex, phaseIndex, enable);
}

/*!
 * @brief Configures the SLCD voltage and power supply.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param powerSupply SLCD power supply configuration.
 * @param loadAdjust SLCD load adjust configuration.
 * @param trim the regulated voltage value.
 */
void SLCD_HAL_VoltageAndPowerSupplyConfig(LCD_Type * base, slcd_power_supply_option_t powerSupply, slcd_load_adjust_t loadAdjust, slcd_regulated_voltage_trim_t trim);

/*!
 * @brief Configures the SLCD clock.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param clkConfigPtr  SLCD clock and frame configuration.
 */
void SLCD_HAL_ClockConfig(LCD_Type * base, const slcd_clk_config_t *clkConfigPtr);

/*!
 * @brief Configures the SLCD blinking mode.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param blinkConfigPtr Pointer of configuring SLCD blinking mode. 
 */
void SLCD_HAL_BlinkingModeConfig(LCD_Type * base, const slcd_blink_config_t *blinkConfigPtr);

/*!
 * @brief Configures the SLCD fault detection.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param faultDetectConfigPtr SLCD fault detection configuration.
 */
void SLCD_HAL_FaultDetectionConfig(LCD_Type * base, const slcd_fault_detect_config_t *faultDetectConfigPtr);

/*!
 * @brief Configures the SLCD running status in doze mode.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param workMode Configure SLCD work mode in doze/stop mode.
 */
void SLCD_HAL_SetLowPowerModeConfig(LCD_Type * base, const slcd_work_mode_t *workMode);

/*!
 * @brief Configures the SLCD frame frequency interrupt.
 *
 * @param base Base address of SLCD peripheral instance.
 * @param intType SLCD interrupt Configuration.
 * @param enable Enable or Disable interrupt.
 */
void SLCD_HAL_SetIntCmd(LCD_Type * base, slcd_int_type_t intType, bool enable);

/*!
 * @brief Configures the SLCD to a workable state.
 *
 * @param base Base address of SLCD peripheral instance.
 */
void SLCD_HAL_Init(LCD_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_SLCD_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/


