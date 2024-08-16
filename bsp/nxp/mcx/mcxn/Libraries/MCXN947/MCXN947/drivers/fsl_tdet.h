/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_TDET_H_
#define FSL_TDET_H_

#include "fsl_common.h"

/*!
 * @addtogroup TDET
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Defines TDET driver version 2.1.0.
 *
 * Change log:
 * - Version 2.1.0
 *   - Added setting of disabling prescaler on tamper event into TDET_SetConfig() and TDET_GetDefaultConfig functions.
 * - Version 2.0.0
 *   - Initial version
 */
#define FSL_TDET_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*! @} */

/*!
 * @brief TDET Update Mode.
 *
 * These constants allow TDET interrupts to be cleared if no tampering has been detected, while still preventing
 * the TDET Tamper Flag (SR[DTF]) from being cleared once it is set.
 */
typedef enum _tdet_update_mode
{
    kTDET_StatusLockNormal = 0U,     /*!< TDET Status Register cannot be written when the Status Register Lock bit
                                          within the Lock Register (LR[SRL]) is clear */
    kTDET_StatusLockWithTamper = 1U, /*!< TDET Status Register cannot be written when the Status Register Lock bit
                                          within the Lock Register (LR[SRL]) is clear and TDET Tamper Flag (SR[DTF])
                                          is set*/
} tdet_update_mode_t;

/*!
 * @brief TDET Active Tamper Clock Source.
 *
 * These constants define the clock source for Active Tamper Shift Register to configure in a TDET base.
 */
typedef enum _tdet_active_tamper_clock
{
    kTDET_ClockType1Hz  = 0U, /*!< clocked by 1 Hz prescaler clock  */
    kTDET_ClockType64Hz = 1U, /*!< clocked by 614 Hz prescaler clock */
} tdet_active_tamper_clock_t;

/*!
 * @brief TDET Control Register.
 *
 * This structure defines values for TDET Control Register.
 */
typedef struct _tdet_config
{
    bool innerClockAndPrescalerEnable; /*!< Enable/disable 32768 Hz clock within TDET and the TDET prescaler that
                                          generates 512 Hz, 64Hz and 1 Hz prescaler clocks  */
    bool tamperForceSystemResetEnable; /*!< Enable/disable assertion of chip reset when tampering is detected */
    enum _tdet_update_mode updateMode; /*!< Selects update mode for TDET Status Register */
    enum _tdet_active_tamper_clock
        clockSourceActiveTamper0; /*!< Selects clock source for Active Tamper Shift Register 0 */
    enum _tdet_active_tamper_clock
        clockSourceActiveTamper1;     /*!< Selects clock source for Active Tamper Shift Register 1 */
    bool disablePrescalerAfterTamper; /*!< Allows the 32-KHz clock and prescaler to be automatically disabled after
                                         tamper detection and until the system acknowledges the tamper. Disabling the
                                         prescaler after detecting a tamper event conserves power and freezes the state
                                         of the active tamper outputs and glitch filters. To ensure a clean transition,
                                         the prescaler is disabled at the end of a 1 Hz period.  */
    uint32_t prescaler;               /*!< Initial value for the TDET prescaler 15-bit value. */
} tdet_config_t;

/*!
 * @brief TDET Tamper Pin Polarity.
 *
 * These constants define tamper pin polarity to configure in a TDET base.
 */
typedef enum _tdet_pin_polarity
{
    kTDET_TamperPinPolarityExpectNormal   = 0U, /*!< Tamper pin expected value is not inverted  */
    kTDET_TamperPinPolarityExpectInverted = 1U, /*!< Tamper pin expected value is inverted */
} tdet_pin_polarity_t;

/*!
 * @brief TDET Tamper Pin Direction.
 *
 * These constants define tamper pin direction to configure in a TDET base.
 */
typedef enum _tdet_pin_direction
{
    kTDET_TamperPinDirectionIn  = 0U, /*!< Tamper pins configured as input  */
    kTDET_TamperPinDirectionOut = 1U, /*!< Tamper pins configured as output, drives inverse of expected value */
} tdet_pin_direction_t;

/*!
 * @brief TDET Glitch Filter Tamper Pin Sample Frequency.
 *
 * These constants define tamper pin glitch filter sample frequency to configure in a TDET base.
 */
typedef enum _tdet_glitch_filter_sample_freq
{
    kTDET_GlitchFilterSamplingEveryCycle8   = 0U, /*!<  Sample once every 8 cycles */
    kTDET_GlitchFilterSamplingEveryCycle32  = 1U, /*!<  Sample once every 32 cycles */
    kTDET_GlitchFilterSamplingEveryCycle128 = 2U, /*!<  Sample once every 128 cycles */
    kTDET_GlitchFilterSamplingEveryCycle512 = 3U, /*!<  Sample once every 512 cycles */
} tdet_glitch_filter_sample_freq_t;
/*!
 * @brief TDET Glitch Filter Tamper Pin Sample Width.
 *
 * These constants define tamper pin glitch filter sample width to configure in a TDET base.
 */
typedef enum _tdet_glitch_filter_sample_width
{
    kTDET_GlitchFilterSampleDisable = 0U, /*!<  Sampling disabled */
    kTDET_GlitchFilterSampleCycle2  = 1U, /*!<  Sample width pull enable/input buffer enable=2 cycles/1 cycle */
    kTDET_GlitchFilterSampleCycle4  = 2U, /*!<  Sample width pull enable/input buffer enable=4 cycles/2 cycles */
    kTDET_GlitchFilterSampleCycle8  = 3U, /*!<  Sample width pull enable/input buffer enable=8 cycles/4 cycles */
} tdet_glitch_filter_sample_width_t;

/*!
 * @brief TDET Glitch Filter Tamper Pin Clock Source.
 *
 * These constants define tamper pin glitch filter clock source to configure in a TDET base.
 */
typedef enum _tdet_glitch_filter_prescaler
{
    kTDET_GlitchFilterClock512Hz   = 0U, /*!< Glitch Filter on tamper pin is clocked by the 512 Hz prescaler clock */
    kTDET_GlitchFilterClock32768Hz = 1U, /*!< Glitch Filter on tamper pin is clocked by the 32768 Hz prescaler clock */
} tdet_glitch_filter_prescaler_t;

/*!
 * @brief TDET Glitch Filter Tamper Pin Expected Value.
 *
 * These constants define tamper pin glitch filter expected value to configure in a TDET base.
 */
typedef enum _tdet_glitch_filter_expected
{
    kTDET_GlitchFilterExpectedLogicZero     = 0U, /*!<  Expected value is logic zero */
    kTDET_GlitchFilterExpectedActTamperOut0 = 1U, /*!<  Expected value is active tamper 0 output */
    kTDET_GlitchFilterExpectedActTamperOut1 = 2U, /*!<  Expected value is active tamper 1 output */
    kTDET_GlitchFilterExpectedActTamperOutXOR =
        3U, /*!<  Expected value is active tamper 0 output XORed with active tamper 1 output */
} tdet_glitch_filter_expected_t;

/*!
 * @brief TDET Glitch Filter Tamper Pull Select.
 *
 * These constants define tamper pin glitch filter pull direction to configure in a TDET base.
 */
typedef enum _tdet_glitch_filter_pull
{
    kTDET_GlitchFilterPullTypeAssert = 0U, /*!< Tamper pin pull direction always asserts the tamper pin. */
    kTDET_GlitchFilterPullTypeNegate = 1U, /*!< Tamper pin pull direction always negates the tamper pin. */
} tdet_glitch_filter_pull_t;

/*!
 * @brief TDET Tamper Pin configuration registers.
 *
 * This structure defines values for TDET Pin Direction, Pin Polarity, and Glitch Filter registers.
 */
typedef struct _tdet_pin_config
{
    enum _tdet_pin_polarity pinPolarity;   /*!< Selects tamper pin expected value */
    enum _tdet_pin_direction pinDirection; /*!< Selects tamper pin direction */
    bool tamperPullEnable;                 /*!< Enable/disable pull resistor on the tamper pin */
    enum _tdet_glitch_filter_sample_freq tamperPinSampleFrequency; /*!< Selects tamper pin sample frequency */
    enum _tdet_glitch_filter_sample_width tamperPinSampleWidth;    /*!< Selects tamper pin sample width */
    bool glitchFilterEnable; /*!< Enable/disable glitch filter on the tamper pin */
    enum _tdet_glitch_filter_prescaler
        glitchFilterPrescaler; /*!< Selects the prescaler for the glitch filter on tamper pin */

    uint8_t glitchFilterWidth; /*!< 6-bit value to configure number of clock edges the input must remain stable for to
                                  be passed through the glitch filter for the tamper pin */

    enum _tdet_glitch_filter_expected tamperPinExpected; /*!< Selects tamper pin expected value */
    enum _tdet_glitch_filter_pull tamperPullSelect;      /*!< Selects the direction of the tamper pin pull resistor */
} tdet_pin_config_t;

/*! @brief List of TDET external tampers */
typedef enum _tdet_external_tamper_pin
{
    kTDET_ExternalTamper0 = 1U << 0,
    kTDET_ExternalTamper1 = 1U << 1,
    kTDET_ExternalTamper2 = 1U << 2,
    kTDET_ExternalTamper3 = 1U << 3,
    kTDET_ExternalTamper4 = 1U << 4,
    kTDET_ExternalTamper5 = 1U << 5,
    kTDET_ExternalTamper6 = 1U << 6,
    kTDET_ExternalTamper7 = 1U << 7
} tdet_external_tamper_pin_t;

/*!
 * @brief TDET Active Tamper Register Select.
 *
 * These constants are used to define activeTamperRegisterSelect argument to be used with
 * TDET_ActiveTamperConfigure().
 */
typedef enum _tdet_active_tamper_register
{
    kTDET_ActiveTamperRegister0 = 1u << 0,
    kTDET_ActiveTamperRegister1 = 1u << 1,
} tdet_active_tamper_register_t;

/*!
 * @brief TDET Active Tamper registers.
 *
 * This structure defines values for TDET Active Tamper Registers.
 */
typedef struct _tdet_active_tamper_config
{
    uint32_t activeTamperShift;      /*!< Active tamper shift register. initialize to non-zero value. */
    uint32_t activeTamperPolynomial; /*!< Polynomial of the active tamper shift register. */
} tdet_active_tamper_config_t;

/*!
 * @brief TDET Status Register flags.
 *
 * This provides constants for the TDET Status Register.
 */
typedef enum _tdet_status_flag
{
    kTDET_StatusTamperFlag            = 1U << DIGTMP_SR_DTF_SHIFT,    /*!< TDET  Digital Tamper Flag */
    kTDET_StatusTamperAcknowledgeFlag = 1U << DIGTMP_SR_TAF_SHIFT,    /*!< TDET Tamper Acknowledge Flag */
    kTDET_StatusClockTamper           = 1U << DIGTMP_IER_TIIE0_SHIFT, /*!< TDET Clock Tamper detected */
    kTDET_StatusConfigurationTamper   = 1U << DIGTMP_IER_TIIE1_SHIFT, /*!< TDET Configuration Tamper detected */
    kTDET_StatusVoltageTamper         = 1U << DIGTMP_IER_TIIE2_SHIFT, /*!< TDET Voltage Tamper detected */
    kTDET_StatusTemperatureTamper     = 1U << DIGTMP_IER_TIIE3_SHIFT, /*!< TDET Temperature Tamper detected */
    kTDET_StatusRamZeroizeTamper      = 1U << DIGTMP_IER_TIIE6_SHIFT, /*!< TDET RAM Zeroize Tamper detected */
    kTDET_StatusTamperPinTamper0      = 1U << DIGTMP_IER_TPIE0_SHIFT, /*!< TDET Tamper Pin 0 Tamper detected */
    kTDET_StatusTamperPinTamper1      = 1U << DIGTMP_IER_TPIE1_SHIFT, /*!< TDET Tamper Pin 1 Tamper detected */
    kTDET_StatusTamperPinTamper2      = 1U << DIGTMP_IER_TPIE2_SHIFT, /*!< TDET Tamper Pin 2 Tamper detected */
    kTDET_StatusTamperPinTamper3      = 1U << DIGTMP_IER_TPIE3_SHIFT, /*!< TDET Tamper Pin 3 Tamper detected */
    kTDET_StatusTamperPinTamper4      = 1U << DIGTMP_IER_TPIE4_SHIFT, /*!< TDET Tamper Pin 4 Tamper detected */
    kTDET_StatusTamperPinTamper5      = 1U << DIGTMP_IER_TPIE5_SHIFT, /*!< TDET Tamper Pin 5 Tamper detected */
    kTDET_StatusTamperPinTamper6      = 1U << DIGTMP_IER_TPIE6_SHIFT, /*!< TDET Tamper Pin 6 Tamper detected */
    kTDET_StatusTamperPinTamper7      = 1U << DIGTMP_IER_TPIE7_SHIFT, /*!< TDET Tamper Pin 7 Tamper detected */
    kTDET_StatusAll = DIGTMP_SR_DTF_MASK | DIGTMP_SR_TAF_MASK | DIGTMP_IER_TIIE0_MASK | DIGTMP_IER_TIIE1_MASK |
                      DIGTMP_IER_TIIE2_MASK | DIGTMP_IER_TIIE3_MASK | DIGTMP_IER_TIIE6_MASK | DIGTMP_IER_TPIE0_MASK |
                      DIGTMP_IER_TPIE1_MASK | DIGTMP_IER_TPIE2_MASK | DIGTMP_IER_TPIE3_MASK | DIGTMP_IER_TPIE4_MASK |
                      DIGTMP_IER_TPIE5_MASK | DIGTMP_IER_TPIE6_MASK |
                      DIGTMP_IER_TPIE7_MASK, /*!< Mask for all of the TDET Status Register bits */
} tdet_status_flag_t;

/*!
 * @brief TDET Interrupt Enable Register.
 *
 * This provides constants for the TDET Interrupt Enable Register.
 */
typedef enum _tdet_interrupt
{
    kTDET_InterruptTamper              = 1U << DIGTMP_IER_DTIE_SHIFT,  /*!< TDET Digital Tamper Interrupt  */
    kTDET_InterruptClockTamper         = 1U << DIGTMP_IER_TIIE0_SHIFT, /*!< TDET Clock Tamper Interrupt */
    kTDET_InterruptConfigurationTamper = 1U << DIGTMP_IER_TIIE1_SHIFT, /*!< TDET Configuration error */
    kTDET_InterruptVoltageTamper       = 1U << DIGTMP_IER_TIIE2_SHIFT, /*!< TDET Voltage Tamper */
    kTDET_InterruptTemperatureTamper   = 1U << DIGTMP_IER_TIIE3_SHIFT, /*!< TDET Temperature Tamper Interrupt */
    kTDET_InterruptRamZeroizeTamper    = 1U << DIGTMP_IER_TIIE6_SHIFT, /*!< TDET RAM Zeroize Tamper Interrupt */
    kTDET_InterruptTamperPinTamper0    = 1U << DIGTMP_IER_TPIE0_SHIFT, /*!< TDET Tamper Pin Tamper 0 Interrupt */
    kTDET_InterruptTamperPinTamper1    = 1U << DIGTMP_IER_TPIE1_SHIFT, /*!< TDET Tamper Pin Tamper 1 Interrupt */
    kTDET_InterruptTamperPinTamper2    = 1U << DIGTMP_IER_TPIE2_SHIFT, /*!< TDET Tamper Pin Tamper 2 Interrupt */
    kTDET_InterruptTamperPinTamper3    = 1U << DIGTMP_IER_TPIE3_SHIFT, /*!< TDET Tamper Pin Tamper 3 Interrupt */
    kTDET_InterruptTamperPinTamper4    = 1U << DIGTMP_IER_TPIE4_SHIFT, /*!< TDET Tamper Pin Tamper 4 Interrupt */
    kTDET_InterruptTamperPinTamper5    = 1U << DIGTMP_IER_TPIE5_SHIFT, /*!< TDET Tamper Pin Tamper 5 Interrupt */
    kTDET_InterruptTamperPinTamper6    = 1U << DIGTMP_IER_TPIE6_SHIFT, /*!< TDET Tamper Pin Tamper 6 Interrupt */
    kTDET_InterruptTamperPinTamper7    = 1U << DIGTMP_IER_TPIE7_SHIFT, /*!< TDET Tamper Pin Tamper 7 Interrupt */
    kTDET_InterruptTamperPinTamper_All = DIGTMP_IER_TPIE0_MASK | DIGTMP_IER_TPIE1_MASK | DIGTMP_IER_TPIE2_MASK |
                                         DIGTMP_IER_TPIE3_MASK | DIGTMP_IER_TPIE4_MASK | DIGTMP_IER_TPIE5_MASK |
                                         DIGTMP_IER_TPIE6_MASK |
                                         DIGTMP_IER_TPIE7_MASK, /*!< TDET All Tamper Pins Interrupt */
    kTDET_InterruptAll = DIGTMP_IER_DTIE_MASK | DIGTMP_IER_TIIE0_MASK | DIGTMP_IER_TIIE1_MASK | DIGTMP_IER_TIIE2_MASK |
                         DIGTMP_IER_TIIE3_MASK | DIGTMP_IER_TIIE6_MASK | DIGTMP_IER_TPIE0_MASK | DIGTMP_IER_TPIE1_MASK |
                         DIGTMP_IER_TPIE2_MASK | DIGTMP_IER_TPIE3_MASK | DIGTMP_IER_TPIE4_MASK | DIGTMP_IER_TPIE5_MASK |
                         DIGTMP_IER_TPIE6_MASK |
                         DIGTMP_IER_TPIE7_MASK, /*!< Mask to select all TDET Interrupt Enable Register bits */
} tdet_interrupt_t;

/*!
 * @brief TDET Tamper Enable Register.
 *
 * This provides constants for the TDET Tamper Enable Register.
 */
typedef enum _tdet_tamper
{
    kTDET_TamperClock         = 1U << DIGTMP_TER_TIE0_SHIFT, /*!< Clock Tamper Enable */
    kTDET_TamperConfiguration = 1U << DIGTMP_TER_TIE1_SHIFT, /*!< Configuration error Tamper Enable */
    kTDET_TamperVoltage       = 1U << DIGTMP_TER_TIE2_SHIFT, /*!< Voltage Tamper Enable */
    kTDET_TamperTemperature   = 1U << DIGTMP_TER_TIE3_SHIFT, /*!< Temperature Tamper Enable */
    kTDET_TamperRamZeroize    = 1U << DIGTMP_TER_TIE6_SHIFT, /*!< RAM Zeroize Tamper Enable */
    kTDET_TamperTamperPin0    = 1U << DIGTMP_TER_TPE0_SHIFT, /*!< Tamper Pin 0 Tamper Enable */
    kTDET_TamperTamperPin1    = 1U << DIGTMP_TER_TPE1_SHIFT, /*!< Tamper Pin 1 Tamper Enable */
    kTDET_TamperTamperPin2    = 1U << DIGTMP_TER_TPE2_SHIFT, /*!< Tamper Pin 2 Tamper Enable */
    kTDET_TamperTamperPin3    = 1U << DIGTMP_TER_TPE3_SHIFT, /*!< Tamper Pin 3 Tamper Enable */
    kTDET_TamperTamperPin4    = 1U << DIGTMP_TER_TPE4_SHIFT, /*!< Tamper Pin 4 Tamper Enable */
    kTDET_TamperTamperPin5    = 1U << DIGTMP_TER_TPE5_SHIFT, /*!< Tamper Pin 5 Tamper Enable */
    kTDET_TamperTamperPin6    = 1U << DIGTMP_TER_TPE6_SHIFT, /*!< Tamper Pin 6 Tamper Enable */
    kTDET_TamperTamperPin7    = 1U << DIGTMP_TER_TPE7_SHIFT, /*!< Tamper Pin 7 Tamper Enable */
    kTDET_TamperTamperPinAll  = DIGTMP_TER_TPE0_MASK | DIGTMP_TER_TPE1_MASK | DIGTMP_TER_TPE2_MASK |
                               DIGTMP_TER_TPE3_MASK | DIGTMP_TER_TPE4_MASK | DIGTMP_TER_TPE5_MASK |
                               DIGTMP_TER_TPE6_MASK | DIGTMP_TER_TPE7_MASK, /*!< All Tamper Pin Tamper Enable */
    kTDET_TamperAll = DIGTMP_TER_TIE0_MASK | DIGTMP_TER_TIE1_MASK | DIGTMP_TER_TIE2_MASK | DIGTMP_TER_TIE3_MASK |
                      DIGTMP_TER_TIE6_MASK | DIGTMP_TER_TPE0_MASK | DIGTMP_TER_TPE1_MASK | DIGTMP_TER_TPE2_MASK |
                      DIGTMP_TER_TPE3_MASK | DIGTMP_TER_TPE4_MASK | DIGTMP_TER_TPE5_MASK | DIGTMP_TER_TPE6_MASK |
                      DIGTMP_TER_TPE7_MASK, /*!< Mask to select all Tamper Enable Register bits */
} tdet_tamper_t;

/*!
 * @brief TDET Registers.
 *
 * This provides constants to encode a mask for the TDET Registers.
 */
typedef enum _tdet_register
{
    kTDET_NoRegister      = 0U,                         /*!< No Register */
    kTDET_Control         = 1U << DIGTMP_LR_CRL_SHIFT,  /*!< Control Register */
    kTDET_Status          = 1U << DIGTMP_LR_SRL_SHIFT,  /*!< Status Register */
    kTDET_Lock            = 1U << DIGTMP_LR_LRL_SHIFT,  /*!< Lock Register */
    kTDET_InterruptEnable = 1U << DIGTMP_LR_IEL_SHIFT,  /*!< Interrupt Enable Register */
    kTDET_TamperSeconds   = 1U << DIGTMP_LR_TSL_SHIFT,  /*!< Tamper Seconds Register */
    kTDET_TamperEnable    = 1U << DIGTMP_LR_TEL_SHIFT,  /*!< Tamper Enable Register */
    kTDET_PinDirection    = 1U << DIGTMP_LR_PDL_SHIFT,  /*!< Pin Direction Register */
    kTDET_PinPolarity     = 1U << DIGTMP_LR_PPL_SHIFT,  /*!< Pin Polarity Register */
    kTDET_ActiveTamper0   = 1U << DIGTMP_LR_ATL0_SHIFT, /*!< Active Tamper Register 0 */
    kTDET_ActiveTamper1   = 1U << DIGTMP_LR_ATL1_SHIFT, /*!< Active Tamper Register 1 */
    kTDET_GlitchFilter0   = 1U << DIGTMP_LR_GFL0_SHIFT, /*!< Glitch Filter Register 0 */
    kTDET_GlitchFilter1   = 1U << DIGTMP_LR_GFL1_SHIFT, /*!< Glitch Filter Register 1 */
    kTDET_GlitchFilter2   = 1U << DIGTMP_LR_GFL2_SHIFT, /*!< Glitch Filter Register 2 */
    kTDET_GlitchFilter3   = 1U << DIGTMP_LR_GFL3_SHIFT, /*!< Glitch Filter Register 3 */
    kTDET_GlitchFilter4   = 1U << DIGTMP_LR_GFL4_SHIFT, /*!< Glitch Filter Register 4 */
    kTDET_GlitchFilter5   = 1U << DIGTMP_LR_GFL5_SHIFT, /*!< Glitch Filter Register 5 */
    kTDET_GlitchFilter6   = 1U << DIGTMP_LR_GFL6_SHIFT, /*!< Glitch Filter Register 6 */
    kTDET_GlitchFilter7   = 1U << DIGTMP_LR_GFL7_SHIFT, /*!< Glitch Filter Register 7 */
    kTDET_PinConfigurationRegisters =
        DIGTMP_LR_PDL_MASK | DIGTMP_LR_PPL_MASK | DIGTMP_LR_ATL0_MASK | DIGTMP_LR_ATL1_MASK | DIGTMP_LR_GFL0_MASK |
        DIGTMP_LR_GFL1_MASK | DIGTMP_LR_GFL2_MASK | DIGTMP_LR_GFL3_MASK | DIGTMP_LR_GFL4_MASK | DIGTMP_LR_GFL5_MASK |
        DIGTMP_LR_GFL6_MASK | DIGTMP_LR_GFL7_MASK, /*!< Mask to select all TDET Pin Configuration Registers */
    kTDET_AllRegisters = DIGTMP_LR_CRL_MASK | DIGTMP_LR_SRL_MASK | DIGTMP_LR_LRL_MASK | DIGTMP_LR_IEL_MASK |
                         DIGTMP_LR_TSL_MASK | DIGTMP_LR_TEL_MASK | DIGTMP_LR_PDL_MASK | DIGTMP_LR_PPL_MASK |
                         DIGTMP_LR_ATL0_MASK | DIGTMP_LR_ATL1_MASK | DIGTMP_LR_GFL0_MASK | DIGTMP_LR_GFL1_MASK |
                         DIGTMP_LR_GFL2_MASK | DIGTMP_LR_GFL3_MASK | DIGTMP_LR_GFL4_MASK | DIGTMP_LR_GFL5_MASK |
                         DIGTMP_LR_GFL6_MASK | DIGTMP_LR_GFL7_MASK, /*!< Mask to select all TDET Registers */
} tdet_register_t;

/*******************************************************************************
 * API
 *******************************************************************************/
extern void VBAT0_DriverIRQHandler(void);

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name TDET Functional Operation
 * @{
 */

/*!
 * @brief Initialize TDET
 *
 * This function initializes TDET.
 *
 * @param base TDET peripheral base address
 * @return Status of the init operation
 */
status_t TDET_Init(DIGTMP_Type *base);

/*!
 * @brief Deinitialize TDET
 *
 * This function disables glitch filters and active tampers
 * This function disables the TDET clock and prescaler in TDET Control Register.
 * @param base TDET peripheral base address
 */
void TDET_Deinit(DIGTMP_Type *base);

/*!
 * @brief Gets default values for the TDET Control Register.
 *
 * This function fills the given structure with default values for the TDET Control Register.
 * The default values are:
 * @code
 *     defaultConfig->innerClockAndPrescalerEnable = true
 *     defaultConfig->tamperForceSystemResetEnable = false
 *     defaultConfig->updateMode = kTDET_StatusLockWithTamper
 *     defaultConfig->clockSourceActiveTamper0 = kTDET_ClockType1Hz
 *     defaultConfig->clockSourceActiveTamper1 = kTDET_ClockType1Hz
 *     defaultConfig->prescaler = 0
 * @endcode
 * @param base TDET peripheral base address
 * @param[out] defaultConfig Pointer to structure to be filled with default parameters
 */
void TDET_GetDefaultConfig(DIGTMP_Type *base, tdet_config_t *defaultConfig);

/*!
 * @brief Writes to the TDET Control Register.
 *
 * This function writes the given structure to the TDET Control Register.
 * @param base TDET peripheral base address
 * @param config Pointer to structure with TDET peripheral configuration parameters
 * @return kStatus_Fail when writing to TDET Control Register is not allowed
 * @return kStatus_Success when operation completes successfully
 */
status_t TDET_SetConfig(DIGTMP_Type *base, const tdet_config_t *config);

/*!
 * @brief Software reset.
 *
 * This function resets all TDET registers. The CR[SWR] itself is not affected;
 * it is reset by VBAT POR only.
 *
 * @param base TDET peripheral base address
 * @return kStatus_Fail when writing to TDET Control Register is not allowed
 * @return kStatus_Success when operation completes successfully
 */
status_t TDET_SoftwareReset(DIGTMP_Type *base);

/*!
 * @brief Writes to the active tamper register(s).
 *
 * This function writes per active tamper register parameters to active tamper register(s).
 *
 * @param base TDET peripheral base address
 * @param activeTamperConfig Pointer to structure with active tamper register parameters
 * @param activeTamperRegisterSelect Bit mask for active tamper registers to be configured. The passed value is
 *                                   combination of tdet_active_tamper_register_t values (OR'ed).
 * @return kStatus_Fail when writing to TDET Active Tamper Register(s) is not allowed
 * @return kStatus_Success when operation completes successfully
 */
status_t TDET_ActiveTamperSetConfig(DIGTMP_Type *base,
                                    const tdet_active_tamper_config_t *activeTamperConfig,
                                    uint32_t activeTamperRegisterSelect);

/*!
 * @brief Gets default values for tamper pin configuration.
 *
 * This function fills the give structure with default values for the tamper pin and glitch filter configuration.
 * The default values are:
 * code
 *     pinConfig->pinPolarity = kTDET_TamperPinPolarityExpectNormal;
 *     pinConfig->pinDirection = kTDET_TamperPinDirectionIn;
 *     pinConfig->tamperPullEnable = false;
 *     pinConfig->tamperPinSampleFrequency = kTDET_GlitchFilterSamplingEveryCycle8;
 *     pinConfig->tamperPinSampleWidth = kTDET_GlitchFilterSampleDisable;
 *     pinConfig->glitchFilterEnable = false;
 *     pinConfig->glitchFilterPrescaler = kTDET_GlitchFilterClock512Hz;
 *     pinConfig->glitchFilterWidth = 0;
 *     pinConfig->tamperPinExpected = kTDET_GlitchFilterExpectedLogicZero;
 *     pinConfig->tamperPullSelect = kTDET_GlitchFilterPullTypeAssert;
 * endcode
 *
 * @param base TDET peripheral base address
 * @param[out] pinConfig Pointer to structure to be filled with tamper pins default parameters
 */

void TDET_PinGetDefaultConfig(DIGTMP_Type *base, tdet_pin_config_t *pinConfig);

/*!
 * @brief Writes the tamper pin configuration.
 *
 * This function writes per pin parameters to tamper pin and glitch filter configuration registers.
 *
 * @param base TDET peripheral base address
 * @param pinConfig Pointer to structure with tamper pin and glitch filter configuration parameters
 * @param pinSelect Bit mask for tamper pins to be configured. The passed value is combination of
 *                  enum _tdet_tamper_pin (tdet_tamper_pin_t) values (OR'ed).
 * @return kStatus_Fail when writing to TDET Pin Direction, Pin Polarity or Glitch Filter Register(s) is not allowed
 * @return kStatus_Success when operation completes successfully
 */
status_t TDET_PinSetConfig(DIGTMP_Type *base, const tdet_pin_config_t *pinConfig, uint32_t pinSelect);

/*!
 * @brief Reads the Status Register.
 *
 * This function reads flag bits from TDET Status Register.
 *
 * @param base TDET peripheral base address
 * @param[out] result Pointer to uint32_t where to write Status Register read value. Use tdet_status_flag_t to decode
 *                    individual flags.
 * @return kStatus_Fail when Status Register reading is not allowed
 * @return kStatus_Success when result is written with the Status Register read value
 */
status_t TDET_GetStatusFlags(DIGTMP_Type *base, uint32_t *result);

/*!
 * @brief Writes to the Status Register.
 *
 * This function clears specified flag bits in TDET Status Register.
 *
 * @param base TDET peripheral base address
 * @param mask Bit mask for the flag bits to be cleared. Use tdet_status_flag_t to encode flags.
 * @return kStatus_Fail when Status Register writing is not allowed
 * @return kStatus_Success when mask is written to the Status Register
 */
status_t TDET_ClearStatusFlags(DIGTMP_Type *base, uint32_t mask);

/*!
 * @brief Writes to the Interrupt Enable Register.
 *
 * This function sets specified interrupt enable bits in TDET Interrupt Enable Register.
 *
 * @param base TDET peripheral base address
 * @param mask Bit mask for the interrupt enable bits to be set.
 * @return kStatus_Fail when Interrupt Enable Register writing is not allowed
 * @return kStatus_Success when mask is written to the Interrupt Enable Register
 */
status_t TDET_EnableInterrupts(DIGTMP_Type *base, uint32_t mask);

/*!
 * @brief Writes to the Interrupt Enable Register.
 *
 * This function clears specified interrupt enable bits in TDET Interrupt Enable Register.
 *
 * @param base TDET peripheral base address
 * @param mask Bit mask for the interrupt enable bits to be cleared.
 * @return kStatus_Fail when Interrupt Enable Register writing is not allowed
 * @return kStatus_Success when specified bits are cleared in the Interrupt Enable Register
 */
status_t TDET_DisableInterrupts(DIGTMP_Type *base, uint32_t mask);

/*!
 * @brief Writes to the Tamper Enable Register.
 *
 * This function sets specified tamper enable bits in TDET Tamper Enable Register.
 *
 * @param base TDET peripheral base address
 * @param mask Bit mask for the tamper enable bits to be set.
 * @return kStatus_Fail when Tamper Enable Register writing is not allowed
 * @return kStatus_Success when mask is written to the Tamper Enable Register
 */
status_t TDET_EnableTampers(DIGTMP_Type *base, uint32_t mask);

/*!
 * @brief Writes to the Tamper Enable Register.
 *
 * This function clears specified tamper enable bits in TDET Tamper Enable Register.
 *
 * @param base TDET peripheral base address
 * @param mask Bit mask for the tamper enable bits to be cleared.
 * @return kStatus_Fail when Tamper Enable Register writing is not allowed
 * @return kStatus_Success when specified bits are cleared in the Tamper Enable Register
 */
status_t TDET_DisableTampers(DIGTMP_Type *base, uint32_t mask);

/*!
 * @brief Writes to the Tamper Seconds Register.
 *
 * This function writes to TDET Tamper Seconds Register. This causes Status Register DTF flag to be set (TDET
 * tampering detected).
 *
 * @param base TDET peripheral base address
 * @return kStatus_Fail when Tamper Seconds Register writing is not allowed
 * @return kStatus_Success when Tamper Seconds Register is written
 */
status_t TDET_ForceTamper(DIGTMP_Type *base);

/*!
 * @brief Reads the Tamper Seconds Register.
 *
 * This function reads TDET Tamper Seconds Register. The read value returns the time in seconds at which the Status
 * Register DTF flag was set.
 *
 * @param base TDET peripheral base address
 * @param tamperTimeSeconds Time in seconds at which the tamper detection SR[DTF] flag was set.
 * @return kStatus_Fail when Tamper Seconds Register reading is not allowed
 * @return kStatus_Success when Tamper Seconds Register is read
 */
status_t TDET_GetTamperTimeSeconds(DIGTMP_Type *base, uint32_t *tamperTimeSeconds);

/*!
 * @brief Writes to the TDET Lock Register.
 *
 * This function clears specified lock bits in the TDET Lock Register.
 * When a lock bit is clear, a write to corresponding TDET Register is ignored.
 * Once cleared, these bits can only be set by VBAT POR or software reset.
 *
 * @param base TDET peripheral base address
 * @param mask Bit mask for the lock bits to be cleared. Use tdet_register_t values to encode (OR'ed) which TDET
 * Registers shall be locked.
 */
void TDET_LockRegisters(DIGTMP_Type *base, uint32_t mask);

/*! @}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/ /* end of group tdet */

#endif /* FSL_TDET_H_ */
