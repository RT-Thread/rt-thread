/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019, 2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SLCD_H_
#define FSL_SLCD_H_

#include "fsl_common.h"

/*!
 * @addtogroup slcd
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief SLCD driver version. */
#define FSL_SLCD_DRIVER_VERSION (MAKE_VERSION(2, 0, 4))
/*! @} */

/*! @brief SLCD power supply option. */
typedef enum _slcd_power_supply_option
{
    kSLCD_InternalVll3UseChargePump =
        2U, /*!< VLL3 connected to VDD internally, charge pump is used to generate VLL1 and VLL2. */
    kSLCD_ExternalVll3UseResistorBiasNetwork =
        4U, /*!< VLL3 is driven externally and resistor bias network is used to generate VLL1 and VLL2. */
    kSLCD_ExteranlVll3UseChargePump =
        6U, /*!< VLL3 is driven externally and charge pump is used to generate VLL1 and VLL2. */
    kSLCD_InternalVll1UseChargePump =
        7U /*!< VIREG is connected to VLL1 internally and charge pump is used to generate VLL2 and VLL3. */
} slcd_power_supply_option_t;

/*! @brief SLCD regulated voltage trim parameter, be used to meet the desired contrast. */
typedef enum _slcd_regulated_voltage_trim
{
    kSLCD_RegulatedVolatgeTrim00 = 0U, /*!< Increase the voltage to 0.91 V. */
    kSLCD_RegulatedVolatgeTrim01,      /*!< Increase the voltage to 1.01 V. */
    kSLCD_RegulatedVolatgeTrim02,      /*!< Increase the voltage to 0.96 V. */
    kSLCD_RegulatedVolatgeTrim03,      /*!< Increase the voltage to 1.06 V. */
    kSLCD_RegulatedVolatgeTrim04,      /*!< Increase the voltage to 0.93 V. */
    kSLCD_RegulatedVolatgeTrim05,      /*!< Increase the voltage to 1.02 V. */
    kSLCD_RegulatedVolatgeTrim06,      /*!< Increase the voltage to 0.98 V. */
    kSLCD_RegulatedVolatgeTrim07,      /*!< Increase the voltage to 1.08 V. */
    kSLCD_RegulatedVolatgeTrim08,      /*!< Increase the voltage to 0.92 V. */
    kSLCD_RegulatedVolatgeTrim09,      /*!< Increase the voltage to 1.02 V. */
    kSLCD_RegulatedVolatgeTrim10,      /*!< Increase the voltage to 0.97 V. */
    kSLCD_RegulatedVolatgeTrim11,      /*!< Increase the voltage to 1.07 V. */
    kSLCD_RegulatedVolatgeTrim12,      /*!< Increase the voltage to 0.94 V. */
    kSLCD_RegulatedVolatgeTrim13,      /*!< Increase the voltage to 1.05 V. */
    kSLCD_RegulatedVolatgeTrim14,      /*!< Increase the voltage to 0.99 V. */
    kSLCD_RegulatedVolatgeTrim15       /*!< Increase the voltage to 1.09 V. */
} slcd_regulated_voltage_trim_t;

/*! @brief SLCD load adjust to handle different LCD glass capacitance or
 *  configure the LCD charge pump clock source.
 *  Adjust the LCD glass capacitance if resistor bias network is enabled:
 *  kSLCD_LowLoadOrFastestClkSrc - Low load (LCD glass capacitance 2000pF or lower.
 *                 LCD or GPIO function can be used on VLL1,VLL2,Vcap1 and Vcap2 pins)
 *  kSLCD_LowLoadOrIntermediateClkSrc - low load (LCD glass capacitance 2000pF or lower.
 *                 LCD or GPIO function can be used on VLL1,VLL2,Vcap1 and Vcap2 pins)
 *  kSLCD_HighLoadOrIntermediateClkSrc - high load (LCD glass capacitance 8000pF or lower.
 *                 LCD or GPIO function can be used on Vcap1 and Vcap2 pins)
 *  kSLCD_HighLoadOrSlowestClkSrc - high load (LCD glass capacitance 8000pF or lower
 *                 LCD or GPIO function can be used on Vcap1 and Vcap2 pins)
 *  Adjust clock for charge pump if charge pump is enabled:
 *  kSLCD_LowLoadOrFastestClkSrc - Fasten clock source (LCD glass capacitance
 *                 8000pF or 4000pF or lower if Fast Frame Rate is set)
 *  kSLCD_LowLoadOrIntermediateClkSrc - Intermediate clock source (LCD glass
 *                 capacitance 4000pF or 2000pF or lower if Fast Frame Rate is set)
 *  kSLCD_HighLoadOrIntermediateClkSrc - Intermediate clock source (LCD glass
 *                 capacitance 2000pF or 1000pF or lower if Fast Frame Rate is set)
 *  kSLCD_HighLoadOrSlowestClkSrc - slowest clock source (LCD glass capacitance
 *                 1000pF or 500pF or lower if Fast Frame Rate is set)
 */
typedef enum _slcd_load_adjust
{
    kSLCD_LowLoadOrFastestClkSrc = 0U,  /*!< Adjust in low load or selects fastest clock. */
    kSLCD_LowLoadOrIntermediateClkSrc,  /*!< Adjust in low load or selects intermediate clock. */
    kSLCD_HighLoadOrIntermediateClkSrc, /*!< Adjust in high load or selects intermediate clock. */
    kSLCD_HighLoadOrSlowestClkSrc       /*!< Adjust in high load or selects slowest clock. */
} slcd_load_adjust_t;

/*! @brief SLCD clock source. */
typedef enum _slcd_clock_src
{
    kSLCD_DefaultClk    = 0U, /*!< Select default clock ERCLK32K. */
    kSLCD_AlternateClk1 = 1U, /*!< Select alternate clock source 1 : MCGIRCLK. */
#if FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE
    kSLCD_AlternateClk2 = 3U /*!< Select alternate clock source 2 : OSCERCLK. */
#endif                       /* FSL_FEATURE_SLCD_HAS_MULTI_ALTERNATE_CLOCK_SOURCE */
} slcd_clock_src_t;

/*! @brief SLCD alternate clock divider. */
typedef enum _slcd_alt_clock_div
{
    kSLCD_AltClkDivFactor1 = 0U, /*!< No divide for alternate clock. */
    kSLCD_AltClkDivFactor64,     /*!< Divide alternate clock with factor 64. */
    kSLCD_AltClkDivFactor256,    /*!< Divide alternate clock with factor 256. */
    kSLCD_AltClkDivFactor512     /*!< Divide alternate clock with factor 512. */
} slcd_alt_clock_div_t;

/*! @brief SLCD clock prescaler to generate frame frequency. */
typedef enum _slcd_clock_prescaler
{
    kSLCD_ClkPrescaler00 = 0U, /*!< Prescaler 0. */
    kSLCD_ClkPrescaler01,      /*!< Prescaler 1. */
    kSLCD_ClkPrescaler02,      /*!< Prescaler 2. */
    kSLCD_ClkPrescaler03,      /*!< Prescaler 3. */
    kSLCD_ClkPrescaler04,      /*!< Prescaler 4. */
    kSLCD_ClkPrescaler05,      /*!< Prescaler 5. */
    kSLCD_ClkPrescaler06,      /*!< Prescaler 6. */
    kSLCD_ClkPrescaler07       /*!< Prescaler 7. */
} slcd_clock_prescaler_t;

/*! @brief SLCD duty cycle. */
typedef enum _slcd_duty_cycle
{
    kSLCD_1Div1DutyCycle = 0U, /*!< LCD use 1 BP 1/1 duty cycle. */
    kSLCD_1Div2DutyCycle,      /*!< LCD use 2 BP 1/2 duty cycle. */
    kSLCD_1Div3DutyCycle,      /*!< LCD use 3 BP 1/3 duty cycle. */
    kSLCD_1Div4DutyCycle,      /*!< LCD use 4 BP 1/4 duty cycle. */
    kSLCD_1Div5DutyCycle,      /*!< LCD use 5 BP 1/5 duty cycle. */
    kSLCD_1Div6DutyCycle,      /*!< LCD use 6 BP 1/6 duty cycle. */
    kSLCD_1Div7DutyCycle,      /*!< LCD use 7 BP 1/7 duty cycle. */
    kSLCD_1Div8DutyCycle       /*!< LCD use 8 BP 1/8 duty cycle. */
} slcd_duty_cycle_t;

/*! @brief SLCD segment phase type. */
typedef enum _slcd_phase_type
{
    kSLCD_NoPhaseActivate = 0x00U, /*!< LCD wareform no phase activates. */
    kSLCD_PhaseAActivate  = 0x01U, /*!< LCD waveform phase A activates. */
    kSLCD_PhaseBActivate  = 0x02U, /*!< LCD waveform phase B activates. */
    kSLCD_PhaseCActivate  = 0x04U, /*!< LCD waveform phase C activates. */
    kSLCD_PhaseDActivate  = 0x08U, /*!< LCD waveform phase D activates. */
    kSLCD_PhaseEActivate  = 0x10U, /*!< LCD waveform phase E activates. */
    kSLCD_PhaseFActivate  = 0x20U, /*!< LCD waveform phase F activates. */
    kSLCD_PhaseGActivate  = 0x40U, /*!< LCD waveform phase G activates. */
    kSLCD_PhaseHActivate  = 0x80U  /*!< LCD waveform phase H activates. */
} slcd_phase_type_t;

/*! @brief SLCD segment phase bit index. */
typedef enum _slcd_phase_index
{
    kSLCD_PhaseAIndex = 0x0U, /*!< LCD phase A bit index. */
    kSLCD_PhaseBIndex = 0x1U, /*!< LCD phase B bit index. */
    kSLCD_PhaseCIndex = 0x2U, /*!< LCD phase C bit index. */
    kSLCD_PhaseDIndex = 0x3U, /*!< LCD phase D bit index. */
    kSLCD_PhaseEIndex = 0x4U, /*!< LCD phase E bit index. */
    kSLCD_PhaseFIndex = 0x5U, /*!< LCD phase F bit index. */
    kSLCD_PhaseGIndex = 0x6U, /*!< LCD phase G bit index. */
    kSLCD_PhaseHIndex = 0x7U  /*!< LCD phase H bit index. */
} slcd_phase_index_t;

/*! @brief SLCD display mode. */
typedef enum _slcd_display_mode
{
    kSLCD_NormalMode = 0U, /*!< LCD Normal display mode. */
    kSLCD_AlternateMode,   /*!< LCD Alternate display mode. For four back planes or less. */
    kSLCD_BlankMode        /*!< LCD Blank display mode. */
} slcd_display_mode_t;

/*! @brief SLCD blink mode. */
typedef enum _slcd_blink_mode
{
    kSLCD_BlankDisplayBlink = 0U, /*!< Display blank during the blink period. */
    kSLCD_AltDisplayBlink /*!< Display alternate display during the blink period if duty cycle is lower than 5. */
} slcd_blink_mode_t;

/*! @brief SLCD blink rate. */
typedef enum _slcd_blink_rate
{
    kSLCD_BlinkRate00 = 0U, /*!< SLCD blink rate is LCD clock/((2^12)). */
    kSLCD_BlinkRate01,      /*!< SLCD blink rate is LCD clock/((2^13)). */
    kSLCD_BlinkRate02,      /*!< SLCD blink rate is LCD clock/((2^14)). */
    kSLCD_BlinkRate03,      /*!< SLCD blink rate is LCD clock/((2^15)). */
    kSLCD_BlinkRate04,      /*!< SLCD blink rate is LCD clock/((2^16)). */
    kSLCD_BlinkRate05,      /*!< SLCD blink rate is LCD clock/((2^17)). */
    kSLCD_BlinkRate06,      /*!< SLCD blink rate is LCD clock/((2^18)). */
    kSLCD_BlinkRate07       /*!< SLCD blink rate is LCD clock/((2^19)). */
} slcd_blink_rate_t;

/*! @brief SLCD fault detect clock prescaler. */
typedef enum _slcd_fault_detect_clock_prescaler
{
    kSLCD_FaultSampleFreqDivider1 = 0U, /*!< Fault detect sample clock frequency is 1/1 bus clock. */
    kSLCD_FaultSampleFreqDivider2,      /*!< Fault detect sample clock frequency is 1/2 bus clock. */
    kSLCD_FaultSampleFreqDivider4,      /*!< Fault detect sample clock frequency is 1/4 bus clock. */
    kSLCD_FaultSampleFreqDivider8,      /*!< Fault detect sample clock frequency is 1/8 bus clock. */
    kSLCD_FaultSampleFreqDivider16,     /*!< Fault detect sample clock frequency is 1/16 bus clock. */
    kSLCD_FaultSampleFreqDivider32,     /*!< Fault detect sample clock frequency is 1/32 bus clock. */
    kSLCD_FaultSampleFreqDivider64,     /*!< Fault detect sample clock frequency is 1/64 bus clock. */
    kSLCD_FaultSampleFreqDivider128     /*!< Fault detect sample clock frequency is 1/128 bus clock. */
} slcd_fault_detect_clock_prescaler_t;

/*! @brief SLCD fault detect sample window width. */
typedef enum _slcd_fault_detect_sample_window_width
{
    kSLCD_FaultDetectWindowWidth4SampleClk = 0U, /*!< Sample window width is 4 sample clock cycles. */
    kSLCD_FaultDetectWindowWidth8SampleClk,      /*!< Sample window width is 8 sample clock cycles. */
    kSLCD_FaultDetectWindowWidth16SampleClk,     /*!< Sample window width is 16 sample clock cycles. */
    kSLCD_FaultDetectWindowWidth32SampleClk,     /*!< Sample window width is 32 sample clock cycles. */
    kSLCD_FaultDetectWindowWidth64SampleClk,     /*!< Sample window width is 64 sample clock cycles. */
    kSLCD_FaultDetectWindowWidth128SampleClk,    /*!< Sample window width is 128 sample clock cycles. */
    kSLCD_FaultDetectWindowWidth256SampleClk,    /*!< Sample window width is 256 sample clock cycles. */
    kSLCD_FaultDetectWindowWidth512SampleClk     /*!< Sample window width is 512 sample clock cycles. */
} slcd_fault_detect_sample_window_width_t;

/*! @brief SLCD interrupt source. */
typedef enum _slcd_interrupt_enable
{
    kSLCD_FaultDetectCompleteInterrupt = 1U, /*!< SLCD fault detection complete interrupt source. */
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    kSLCD_FrameFreqInterrupt = 2U /*!< SLCD frame frequency interrupt source. Not available in all low-power modes. */
#endif                            /* FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT */
} slcd_interrupt_enable_t;

/*! @brief SLCD behavior in low power mode. */
typedef enum _slcd_lowpower_behavior
{
    kSLCD_EnabledInWaitStop = 0, /*!< SLCD works in wait and stop mode. */
    kSLCD_EnabledInWaitOnly,     /*!< SLCD works in wait mode and is disabled in stop mode. */
    kSLCD_EnabledInStopOnly,     /*!< SLCD works in stop mode and is disabled in wait mode. */
    kSLCD_DisabledInWaitStop     /*!< SLCD is disabled in stop mode and wait mode. */
} slcd_lowpower_behavior;

/*! @brief SLCD fault frame detection configuration structure. */
typedef struct _slcd_fault_detect_config
{
    bool faultDetectIntEnable;       /*!< Fault frame detection interrupt enable flag.*/
    bool faultDetectBackPlaneEnable; /*!< True means the pin id fault detected is back plane otherwise front plane. */
    uint8_t faultDetectPinIndex;     /*!< Fault detected pin id  from 0 to 63. */
    slcd_fault_detect_clock_prescaler_t faultPrescaler; /*!< Fault detect clock prescaler. */
    slcd_fault_detect_sample_window_width_t width;      /*!< Fault detect sample window width. */
} slcd_fault_detect_config_t;

/*! @brief SLCD clock configuration structure. */
typedef struct _slcd_clock_config
{
    slcd_clock_src_t clkSource; /*!< Clock source. "slcd_clock_src_t" is recommended to be used.
                                  The SLCD is optimized to operate using a 32.768kHz clock input. */
    slcd_alt_clock_div_t
        altClkDivider; /*!< The divider to divide the alternate clock used for alternate clock source. */
    slcd_clock_prescaler_t clkPrescaler; /*!< Clock prescaler. */
#if FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE
    bool fastFrameRateEnable; /*!< Fast frame rate enable flag. */
#endif                        /* FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE */
} slcd_clock_config_t;

/*! @brief SLCD configuration structure. */
typedef struct _slcd_config
{
    slcd_power_supply_option_t powerSupply;    /*!< Power supply option. */
    slcd_regulated_voltage_trim_t voltageTrim; /*!< Regulated voltage trim used for the internal regulator VIREG to
                                                  adjust to facilitate contrast control. */
    slcd_clock_config_t *clkConfig;            /*!< Clock configure. */
    slcd_display_mode_t displayMode;           /*!< SLCD display mode. */
    slcd_load_adjust_t loadAdjust;             /*!< Load adjust to handle glass capacitance. */
    slcd_duty_cycle_t dutyCycle;               /*!< Duty cycle. */
    slcd_lowpower_behavior lowPowerBehavior;   /*!< SLCD behavior in low power mode. */
#if FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT
    bool frameFreqIntEnable;    /*!< Frame frequency interrupt enable flag.*/
#endif                          /* FSL_FEATURE_SLCD_HAS_FAST_FRAME_RATE */
    uint32_t slcdLowPinEnabled; /*!< Setting enabled SLCD pin 0 ~ pin 31. Setting bit n to 1 means enable pin n. */
    uint32_t
        slcdHighPinEnabled; /*!< Setting enabled SLCD pin 32 ~ pin 63. Setting bit n to 1 means enable pin (n + 32). */
    uint32_t backPlaneLowPin;  /*!< Setting back plane pin 0 ~ pin 31. Setting bit n to 1 means setting pin n as back
                                  plane. It should never have the same bit setting as the frontPlane Pin. */
    uint32_t backPlaneHighPin; /*!< Setting back plane pin 32 ~ pin 63. Setting bit n to 1 means setting pin (n + 32) as
                                  back plane. It should never have the same bit setting as the frontPlane Pin. */
    slcd_fault_detect_config_t *faultConfig; /*!< Fault frame detection configure. If not requirement, set to NULL. */
} slcd_config_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the SLCD, ungates the module clock, initializes the power
 * setting, enables all used plane pins, and sets with interrupt and work mode
 * with the configuration.
 *
 * @param base  SLCD peripheral base address.
 * @param configure SLCD configuration pointer.
 *   For the configuration structure, many parameters have the default setting
 *   and the SLCD_Getdefaultconfig() is provided to get them. Use it
 *   verified for their applications.
 *   The others have no default settings, such as "clkConfig", and must be provided
 *   by the application before calling the SLCD_Init() API.
 */
void SLCD_Init(LCD_Type *base, slcd_config_t *configure);

/*!
 * @brief Deinitializes the SLCD module, gates the module clock, disables an interrupt,
 * and displays the SLCD.
 *
 * @param base  SLCD peripheral base address.
 */
void SLCD_Deinit(LCD_Type *base);

/*!
 * @brief Gets the SLCD default configuration structure. The
 * purpose of this API is to get default parameters of the configuration structure
 * for the SLCD_Init(). Use these initialized parameters unchanged in SLCD_Init()
 * or modify fields of the structure before the calling SLCD_Init().
 * All default parameters of the configure structuration are listed.
 * @code
   config.displayMode        = kSLCD_NormalMode;
   config.powerSupply        = kSLCD_InternalVll3UseChargePump;
   config.voltageTrim        = kSLCD_RegulatedVolatgeTrim00;
   config.lowPowerBehavior   = kSLCD_EnabledInWaitStop;
   config.interruptSrc       = 0;
   config.faultConfig        = NULL;
   config.frameFreqIntEnable =  false;
   @endcode
 * @param configure The SLCD configuration structure pointer.
 */
void SLCD_GetDefaultConfig(slcd_config_t *configure);

/*! @} */

/*!
 * @name Plane Setting and Display Control
 * @{
 */

/*!
 * @brief Enables the SLCD controller, starts generation, and displays the front plane and back plane waveform.
 *
 * @param base  SLCD peripheral base address.
 */
static inline void SLCD_StartDisplay(LCD_Type *base)
{
    base->GCR |= LCD_GCR_LCDEN_MASK;
}

/*!
 * @brief Stops the SLCD controller. There is no waveform generator and all enabled pins
 * only output a low value.
 *
 * @param base  SLCD peripheral base address.
 */
static inline void SLCD_StopDisplay(LCD_Type *base)
{
    base->GCR &= ~LCD_GCR_LCDEN_MASK;
}

/*!
 * @brief Starts the SLCD blink mode.
 *
 * @param base  SLCD peripheral base address.
 * @param mode  SLCD blink mode.
 * @param rate  SLCD blink rate.
 */
void SLCD_StartBlinkMode(LCD_Type *base, slcd_blink_mode_t mode, slcd_blink_rate_t rate);

/*!
 * @brief Stops the SLCD blink mode.
 *
 * @param base  SLCD peripheral base address.
 */
static inline void SLCD_StopBlinkMode(LCD_Type *base)
{
    base->AR &= ~LCD_AR_BLINK_MASK;
}

/*!
 * @brief Sets the SLCD back plane pin phase.
 *
 * This function sets the SLCD back plane pin phase. "kSLCD_PhaseXActivate" setting
 * means the phase X is active for the back plane pin. "kSLCD_NoPhaseActivate" setting
 * means there is no phase active for the back plane pin.
 * For example, set the back plane pin 20 for phase A.
 * @code
 * SLCD_SetBackPlanePhase(LCD, 20, kSLCD_PhaseAActivate);
 * @endcode
 *
 * @param base    SLCD peripheral base address.
 * @param pinIndx SLCD back plane pin index. Range from 0 to 63.
 * @param phase   The phase activates for the back plane pin.
 */
static inline void SLCD_SetBackPlanePhase(LCD_Type *base, uint32_t pinIndx, slcd_phase_type_t phase)
{
    base->WF8B[pinIndx] = (uint8_t)phase;
}

/*!
 * @brief Sets the SLCD front plane segment operation for a front plane pin.
 *
 * This function sets the SLCD front plane segment on or off operation.
 * Each bit turns on or off the segments associated with the front plane pin in
 * the following pattern: HGFEDCBA (most significant bit controls segment H and
 * least significant bit controls segment A).
 * For example, turn on the front plane pin 20 for phase B and phase C.
 * @code
 * SLCD_SetFrontPlaneSegments(LCD, 20, (kSLCD_PhaseBActivate | kSLCD_PhaseCActivate));
 * @endcode
 *
 * @param base      SLCD peripheral base address.
 * @param pinIndx   SLCD back plane pin index. Range from 0 to 63.
 * @param operation The operation for the segment on the front plane pin.
 *                  This is a logical OR of the enumeration :: slcd_phase_type_t.
 */
static inline void SLCD_SetFrontPlaneSegments(LCD_Type *base, uint32_t pinIndx, uint8_t operation)
{
    base->WF8B[pinIndx] = operation;
}

/*!
 * @brief Sets one SLCD front plane pin for one phase.
 *
 * This function can be used to set one phase on or off for the front plane pin.
 * It can be call many times to set the plane pin for different phase indexes.
 * For example, turn on the front plane pin 20 for phase B and phase C.
 * @code
 * SLCD_SetFrontPlaneOnePhase(LCD, 20, kSLCD_PhaseBIndex, true);
 * SLCD_SetFrontPlaneOnePhase(LCD, 20, kSLCD_PhaseCIndex, true);
 * @endcode
 *
 * @param base      SLCD peripheral base address.
 * @param pinIndx   SLCD back plane pin index. Range from 0 to 63.
 * @param phaseIndx The phase bit index @ref slcd_phase_index_t.
 * @param enable    True to turn on the segment for phaseIndx phase
 *                  false to turn off the segment for phaseIndx phase.
 */
static inline void SLCD_SetFrontPlaneOnePhase(LCD_Type *base,
                                              uint32_t pinIndx,
                                              slcd_phase_index_t phaseIndx,
                                              bool enable)
{
    uint8_t reg = base->WF8B[pinIndx];

    if (enable)
    {
        base->WF8B[pinIndx] = (reg | (1U << (uint32_t)phaseIndx));
    }
    else
    {
        base->WF8B[pinIndx] = (reg & ~(1U << (uint32_t)phaseIndx));
    }
}

#if FSL_FEATURE_SLCD_HAS_PAD_SAFE
/*!
 * @brief Enables/disables the SLCD pad safe state.
 *
 * Forces the safe state on the LCD pad controls. All LCD front plane
 * and backplane functions are disabled.
 *
 * @param base  SLCD peripheral base address.
 * @param enable True enable, false disable.
 */
static inline void SLCD_EnablePadSafeState(LCD_Type *base, bool enable)
{
    if (enable)
    { /* Enable. */
        base->GCR |= LCD_GCR_PADSAFE_MASK;
    }
    else
    { /* Disable. */
        base->GCR &= ~LCD_GCR_PADSAFE_MASK;
    }
}
#endif /* FSL_FEATURE_SLCD_HAS_PAD_SAFE */

/*!
 * @brief Gets the SLCD fault detect counter.
 *
 * This function gets the number of samples inside the
 * fault detection sample window.
 *
 * @param base  SLCD peripheral base address.
 * @return The fault detect counter. The maximum return value is 255.
 * If the maximum 255 returns, the overflow may happen.
 * Reconfigure the fault detect sample window and fault detect clock prescaler
 * for proper sampling.
 */
static inline uint32_t SLCD_GetFaultDetectCounter(LCD_Type *base)
{
    return base->FDSR & LCD_FDSR_FDCNT_MASK;
}

/*! @} */

/*!
 * @name Interrupts.
 * @{
 */

/*!
 * @brief Enables the SLCD interrupt.
 * For example, to enable fault detect complete interrupt and frame frequency interrupt,
 * for FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT enabled case, do the following.
 * @code
 *     SLCD_EnableInterrupts(LCD,kSLCD_FaultDetectCompleteInterrupt | kSLCD_FrameFreqInterrupt);
 * @endcode
 *
 * @param base  SLCD peripheral base address.
 * @param mask  SLCD interrupts to enable. This is a logical OR of the
 *             enumeration :: slcd_interrupt_enable_t.
 */
void SLCD_EnableInterrupts(LCD_Type *base, uint32_t mask);

/*!
 * @brief Disables the SLCD interrupt.
 * For example, to disable fault detect complete interrupt and frame frequency interrupt,
 * for FSL_FEATURE_SLCD_HAS_FRAME_FREQUENCY_INTERRUPT enabled case, do the following.
 * @code
 *     SLCD_DisableInterrupts(LCD,kSLCD_FaultDetectCompleteInterrupt | kSLCD_FrameFreqInterrupt);
 * @endcode
 *
 * @param base  SLCD peripheral base address.
 * @param mask  SLCD interrupts to disable. This is a logical OR of the
 *             enumeration :: slcd_interrupt_enable_t.
 */
void SLCD_DisableInterrupts(LCD_Type *base, uint32_t mask);

/*!
 * @brief Gets the SLCD interrupt status flag.
 *
 * @param base  SLCD peripheral base address.
 * @return The event status of the interrupt source. This is the logical OR of members
 *         of the enumeration :: slcd_interrupt_enable_t.
 */
uint32_t SLCD_GetInterruptStatus(LCD_Type *base);

/*!
 * @brief Clears the SLCD interrupt events status flag.
 *
 * @param base  SLCD peripheral base address.
 * @param mask  SLCD interrupt source to be cleared.
 * This is the logical OR of members of the enumeration :: slcd_interrupt_enable_t.
 */
void SLCD_ClearInterruptStatus(LCD_Type *base, uint32_t mask);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* FSL_SLCD_H_*/
