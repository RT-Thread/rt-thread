/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021, 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_TPM_H_
#define FSL_TPM_H_

#include "fsl_common.h"

/*
 * $Coverage Justification Reference$
 *
 * $Justification tpm_h_ref_1$
 * Hardware limitations make this code impossible to implement.
 *
 */

/*!
 * @addtogroup tpm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief TPM driver version 2.3.1. */
#define FSL_TPM_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*! @} */

/*! @brief Help macro to get the max counter value */
#define TPM_MAX_COUNTER_VALUE(x) ((1U != (uint8_t)FSL_FEATURE_TPM_HAS_32BIT_COUNTERn(x)) ? 0xFFFFU : 0xFFFFFFFFU)

/*!
 * @brief List of TPM channels.
 * @note Actual number of available channels is SoC dependent
 */
typedef enum _tpm_chnl
{
    kTPM_Chnl_0 = 0U, /*!< TPM channel number 0*/
    kTPM_Chnl_1,      /*!< TPM channel number 1 */
    kTPM_Chnl_2,      /*!< TPM channel number 2 */
    kTPM_Chnl_3,      /*!< TPM channel number 3 */
    kTPM_Chnl_4,      /*!< TPM channel number 4 */
    kTPM_Chnl_5,      /*!< TPM channel number 5 */
    kTPM_Chnl_6,      /*!< TPM channel number 6 */
    kTPM_Chnl_7       /*!< TPM channel number 7 */
} tpm_chnl_t;

/*! @brief TPM PWM operation modes */
typedef enum _tpm_pwm_mode
{
    kTPM_EdgeAlignedPwm = 0U, /*!< Edge aligned PWM */
    kTPM_CenterAlignedPwm,    /*!< Center aligned PWM */
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    kTPM_CombinedPwm /*!< Combined PWM (Edge-aligned, center-aligned, or asymmetrical PWMs can be obtained in combined
                        mode using different software configurations) */
#endif
} tpm_pwm_mode_t;

/*!
 * @brief TPM PWM output pulse mode: high-true, low-true or no output
 *
 * @note When the TPM has PWM pause level select feature, the PWM output cannot be turned off by selecting the output
 *       level. In this case, the channel must be closed to close the PWM output.
 */
typedef enum _tpm_pwm_level_select
{
#if !(defined(FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT) && FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT)
    kTPM_NoPwmSignal = 0U, /*!< No PWM output on pin */
    kTPM_LowTrue,          /*!< Low true pulses */
    kTPM_HighTrue          /*!< High true pulses */
#else
    kTPM_HighTrue = 0U, /*!< High true pulses */
    kTPM_LowTrue        /*!< Low true pulses */
#endif
} tpm_pwm_level_select_t;

#if (defined(FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT) && FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT)
/*! @brief TPM PWM output when first enabled or paused: set or clear */
typedef enum _tpm_pwm_pause_level_select
{
    kTPM_ClearOnPause = 0U, /*!< Clear Output when counter first enabled or paused. */
    kTPM_SetOnPause         /*!< Set Output when counter first enabled or paused. */
} tpm_pwm_pause_level_select_t;
#endif

/*! @brief List of TPM channel modes and level control bit mask */
typedef enum _tpm_chnl_control_bit_mask
{
    kTPM_ChnlELSnAMask = TPM_CnSC_ELSA_MASK, /*!< Channel ELSA bit mask.*/
    kTPM_ChnlELSnBMask = TPM_CnSC_ELSB_MASK, /*!< Channel ELSB bit mask.*/
    kTPM_ChnlMSAMask   = TPM_CnSC_MSA_MASK,  /*!< Channel MSA bit mask.*/
    kTPM_ChnlMSBMask   = TPM_CnSC_MSB_MASK,  /*!< Channel MSB bit mask.*/
} tpm_chnl_control_bit_mask_t;

/*! @brief Options to configure a TPM channel's PWM signal */
typedef struct _tpm_chnl_pwm_signal_param
{
    tpm_chnl_t chnlNumber; /*!< TPM channel to configure.
                                In combined mode (available in some SoC's), this represents the
                                channel pair number */
#if (defined(FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT) && FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT)
    tpm_pwm_pause_level_select_t pauseLevel; /*!< PWM output level when counter first enabled or paused */
#endif
    tpm_pwm_level_select_t level; /*!< PWM output active level select */
    uint8_t dutyCyclePercent;     /*!< PWM pulse width, value should be between 0 to 100
                                       0=inactive signal(0% duty cycle)...
                                       100=always active signal (100% duty cycle)*/
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    uint8_t firstEdgeDelayPercent; /*!< Used only in combined PWM mode to generate asymmetrical PWM.
                                        Specifies the delay to the first edge in a PWM period.
                                        If unsure, leave as 0. Should be specified as percentage
                                        of the PWM period, (dutyCyclePercent + firstEdgeDelayPercent) value
                                        should be not greate than 100. */
    bool enableComplementary;      /*!< Used only in combined PWM mode.
                                        true: The combined channels output complementary signals;
                                        false: The combined channels output same signals; */
#if (defined(FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT) && FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT)
    tpm_pwm_pause_level_select_t secPauseLevel; /*!< Used only in combined PWM mode. Define the second channel output
                                                   level when counter first enabled or paused */
#endif
    uint8_t deadTimeValue[2]; /*!< The dead time value for channel n and n+1 in combined complementary PWM mode.
                               Deadtime insertion is disabled when this value is zero, otherwise deadtime insertion for
                               channel n/n+1 is configured as (deadTimeValue * 4) clock cycles. deadTimeValue's
                               available range is 0 ~ 15. */
#endif
} tpm_chnl_pwm_signal_param_t;

#if !(defined(FSL_FEATURE_TPM_HAS_NO_CONF) && FSL_FEATURE_TPM_HAS_NO_CONF)
/*!
 * @brief Trigger sources available.
 *
 * This is used for both internal & external trigger sources (external trigger sources available in certain SoC's)
 *
 * @note The actual trigger sources available is SoC-specific.
 */
typedef enum _tpm_trigger_select
{
    kTPM_Trigger_Select_0 = 0U,
    kTPM_Trigger_Select_1,
    kTPM_Trigger_Select_2,
    kTPM_Trigger_Select_3,
    kTPM_Trigger_Select_4,
    kTPM_Trigger_Select_5,
    kTPM_Trigger_Select_6,
    kTPM_Trigger_Select_7,
    kTPM_Trigger_Select_8,
    kTPM_Trigger_Select_9,
    kTPM_Trigger_Select_10,
    kTPM_Trigger_Select_11,
    kTPM_Trigger_Select_12,
    kTPM_Trigger_Select_13,
    kTPM_Trigger_Select_14,
    kTPM_Trigger_Select_15
} tpm_trigger_select_t;

#if defined(FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION) && FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
/*!
 * @brief Trigger source options available
 *
 * @note This selection is available only on some SoC's. For SoC's without this selection, the only
 * trigger source available is internal triger.
 */
typedef enum _tpm_trigger_source
{
    kTPM_TriggerSource_External = 0U, /*!< Use external trigger input */
    kTPM_TriggerSource_Internal       /*!< Use internal trigger (channel pin input capture) */
} tpm_trigger_source_t;

/*!
 * @brief External trigger source polarity
 *
 * @note Selects the polarity of the external trigger source.
 */
typedef enum _tpm_ext_trigger_polarity
{
    kTPM_ExtTrigger_Active_High = 0U, /*!< External trigger input is active high */
    kTPM_ExtTrigger_Active_Low        /*!< External trigger input is active low */
} tpm_ext_trigger_polarity_t;
#endif
#endif

/*! @brief TPM output compare modes */
typedef enum _tpm_output_compare_mode
{
    kTPM_NoOutputSignal  = (1U << TPM_CnSC_MSA_SHIFT), /*!< No channel output when counter reaches CnV  */
    kTPM_ToggleOnMatch   = ((1U << TPM_CnSC_MSA_SHIFT) | (1U << TPM_CnSC_ELSA_SHIFT)), /*!< Toggle output */
    kTPM_ClearOnMatch    = ((1U << TPM_CnSC_MSA_SHIFT) | (2U << TPM_CnSC_ELSA_SHIFT)), /*!< Clear output */
    kTPM_SetOnMatch      = ((1U << TPM_CnSC_MSA_SHIFT) | (3U << TPM_CnSC_ELSA_SHIFT)), /*!< Set output */
    kTPM_HighPulseOutput = ((3U << TPM_CnSC_MSA_SHIFT) | (1U << TPM_CnSC_ELSA_SHIFT)), /*!< Pulse output high */
    kTPM_LowPulseOutput  = ((3U << TPM_CnSC_MSA_SHIFT) | (2U << TPM_CnSC_ELSA_SHIFT))  /*!< Pulse output low */
} tpm_output_compare_mode_t;

/*! @brief TPM input capture edge */
typedef enum _tpm_input_capture_edge
{
    kTPM_RisingEdge      = (1U << TPM_CnSC_ELSA_SHIFT), /*!< Capture on rising edge only */
    kTPM_FallingEdge     = (2U << TPM_CnSC_ELSA_SHIFT), /*!< Capture on falling edge only */
    kTPM_RiseAndFallEdge = (3U << TPM_CnSC_ELSA_SHIFT)  /*!< Capture on rising or falling edge */
} tpm_input_capture_edge_t;

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
/*!
 * @brief TPM dual edge capture parameters
 *
 * @note This mode is available only on some SoC's.
 */
typedef struct _tpm_dual_edge_capture_param
{
    bool enableSwap;                           /*!< true: Use channel n+1 input, channel n input is ignored;
                                                    false: Use channel n input, channel n+1 input is ignored */
    tpm_input_capture_edge_t currChanEdgeMode; /*!< Input capture edge select for channel n */
    tpm_input_capture_edge_t nextChanEdgeMode; /*!< Input capture edge select for channel n+1 */
} tpm_dual_edge_capture_param_t;
#endif

#if defined(FSL_FEATURE_TPM_HAS_QDCTRL) && FSL_FEATURE_TPM_HAS_QDCTRL
/*!
 * @brief TPM quadrature decode modes
 *
 * @note This mode is available only on some SoC's.
 */
typedef enum _tpm_quad_decode_mode
{
    kTPM_QuadPhaseEncode = 0U, /*!< Phase A and Phase B encoding mode */
    kTPM_QuadCountAndDir       /*!< Count and direction encoding mode */
} tpm_quad_decode_mode_t;

/*! @brief TPM quadrature phase polarities */
typedef enum _tpm_phase_polarity
{
    kTPM_QuadPhaseNormal = 0U, /*!< Phase input signal is not inverted */
    kTPM_QuadPhaseInvert       /*!< Phase input signal is inverted */
} tpm_phase_polarity_t;

/*! @brief TPM quadrature decode phase parameters */
typedef struct _tpm_phase_param
{
    uint32_t phaseFilterVal;            /*!< Filter value, filter is disabled when the value is zero */
    tpm_phase_polarity_t phasePolarity; /*!< Phase polarity */
} tpm_phase_params_t;
#endif

/*! @brief TPM clock source selection*/
typedef enum _tpm_clock_source
{
    kTPM_SystemClock = 1U, /*!< System clock */
#if defined(FSL_FEATURE_TPM_HAS_SC_CLKS) && FSL_FEATURE_TPM_HAS_SC_CLKS
    kTPM_FixedClock, /*!< Fixed frequency clock */
#endif
    kTPM_ExternalClock, /*!< External TPM_EXTCLK pin clock */
#if defined(FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION) && FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
    kTPM_ExternalInputTriggerClock /*!< Selected external input trigger clock */
#endif
} tpm_clock_source_t;

/*! @brief TPM prescale value selection for the clock source*/
typedef enum _tpm_clock_prescale
{
    kTPM_Prescale_Divide_1 = 0U, /*!< Divide by 1 */
    kTPM_Prescale_Divide_2,      /*!< Divide by 2 */
    kTPM_Prescale_Divide_4,      /*!< Divide by 4 */
    kTPM_Prescale_Divide_8,      /*!< Divide by 8 */
    kTPM_Prescale_Divide_16,     /*!< Divide by 16 */
    kTPM_Prescale_Divide_32,     /*!< Divide by 32 */
    kTPM_Prescale_Divide_64,     /*!< Divide by 64 */
    kTPM_Prescale_Divide_128     /*!< Divide by 128 */
} tpm_clock_prescale_t;

/*!
 * @brief TPM config structure
 *
 * This structure holds the configuration settings for the TPM peripheral. To initialize this
 * structure to reasonable defaults, call the TPM_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _tpm_config
{
    tpm_clock_prescale_t prescale; /*!< Select TPM clock prescale value */
#if !(defined(FSL_FEATURE_TPM_HAS_NO_CONF) && FSL_FEATURE_TPM_HAS_NO_CONF)
    bool useGlobalTimeBase;  /*!< true: The TPM channels use an external global time base (the local counter still use
                                for generate overflow interrupt and DMA request);
                                false: All TPM channels use the local counter as their timebase */
    bool syncGlobalTimeBase; /*!< true: The TPM counter is synchronized to the global time base;
                                 false: disabled */
    tpm_trigger_select_t triggerSelect; /*!< Input trigger to use for controlling the counter operation */
#if defined(FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION) && FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
    tpm_trigger_source_t triggerSource; /*!< Decides if we use external or internal trigger. */
    tpm_ext_trigger_polarity_t
        extTriggerPolarity; /*!< when using external trigger source, need selects the polarity of it. */
#endif
    bool enableDoze;            /*!< true: TPM counter is paused in doze mode;
                                     false: TPM counter continues in doze mode */
    bool enableDebugMode;       /*!< true: TPM counter continues in debug mode;
                                     false: TPM counter is paused in debug mode */
    bool enableReloadOnTrigger; /*!< true: TPM counter is reloaded on trigger;
                                     false: TPM counter not reloaded */
    bool enableStopOnOverflow;  /*!< true: TPM counter stops after overflow;
                                     false: TPM counter continues running after overflow */
    bool enableStartOnTrigger;  /*!< true: TPM counter only starts when a trigger is detected;
                                     false: TPM counter starts immediately */
#if defined(FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER) && FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER
    bool enablePauseOnTrigger; /*!< true: TPM counter will pause while trigger remains asserted;
                                    false: TPM counter continues running */
#endif
#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
    uint8_t chnlPolarity; /*!< Defines the input/output polarity of the channels in POL register */
#endif
#endif
} tpm_config_t;

/*! @brief List of TPM interrupts */
typedef enum _tpm_interrupt_enable
{
    kTPM_Chnl0InterruptEnable        = (1U << 0), /*!< Channel 0 interrupt.*/
    kTPM_Chnl1InterruptEnable        = (1U << 1), /*!< Channel 1 interrupt.*/
    kTPM_Chnl2InterruptEnable        = (1U << 2), /*!< Channel 2 interrupt.*/
    kTPM_Chnl3InterruptEnable        = (1U << 3), /*!< Channel 3 interrupt.*/
    kTPM_Chnl4InterruptEnable        = (1U << 4), /*!< Channel 4 interrupt.*/
    kTPM_Chnl5InterruptEnable        = (1U << 5), /*!< Channel 5 interrupt.*/
    kTPM_Chnl6InterruptEnable        = (1U << 6), /*!< Channel 6 interrupt.*/
    kTPM_Chnl7InterruptEnable        = (1U << 7), /*!< Channel 7 interrupt.*/
    kTPM_TimeOverflowInterruptEnable = (1U << 8)  /*!< Time overflow interrupt.*/
} tpm_interrupt_enable_t;

/*! @brief List of TPM flags */
typedef enum _tpm_status_flags
{
    kTPM_Chnl0Flag        = (1U << 0), /*!< Channel 0 flag */
    kTPM_Chnl1Flag        = (1U << 1), /*!< Channel 1 flag */
    kTPM_Chnl2Flag        = (1U << 2), /*!< Channel 2 flag */
    kTPM_Chnl3Flag        = (1U << 3), /*!< Channel 3 flag */
    kTPM_Chnl4Flag        = (1U << 4), /*!< Channel 4 flag */
    kTPM_Chnl5Flag        = (1U << 5), /*!< Channel 5 flag */
    kTPM_Chnl6Flag        = (1U << 6), /*!< Channel 6 flag */
    kTPM_Chnl7Flag        = (1U << 7), /*!< Channel 7 flag */
    kTPM_TimeOverflowFlag = (1U << 8)  /*!< Time overflow flag */
} tpm_status_flags_t;

/*!
 * @brief TPM callback function pointer
 *
 * @param base   TPM peripheral base address.
 */
typedef void (*tpm_callback_t)(TPM_Type *base);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Gets the instance from the base address
 *
 * @param base TPM peripheral base address
 * @return The TPM instance
 */
uint32_t TPM_GetInstance(TPM_Type *base);

/*!
 * @brief Ungates the TPM clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the TPM driver.
 *
 * @param base   TPM peripheral base address
 * @param config Pointer to user's TPM config structure.
 */
void TPM_Init(TPM_Type *base, const tpm_config_t *config);

/*!
 * @brief Stops the counter and gates the TPM clock
 *
 * @param base TPM peripheral base address
 */
void TPM_Deinit(TPM_Type *base);

/*!
 * @brief  Fill in the TPM config struct with the default settings
 *
 * The default values are:
 * @code
 *     config->prescale = kTPM_Prescale_Divide_1;
 *     config->useGlobalTimeBase = false;
 *     config->syncGlobalTimeBase = false;
 *     config->dozeEnable = false;
 *     config->dbgMode = false;
 *     config->enableReloadOnTrigger = false;
 *     config->enableStopOnOverflow = false;
 *     config->enableStartOnTrigger = false;
 *#if FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER
 *     config->enablePauseOnTrigger = false;
 *#endif
 *     config->triggerSelect = kTPM_Trigger_Select_0;
 *#if FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
 *     config->triggerSource = kTPM_TriggerSource_External;
 *     config->extTriggerPolarity = kTPM_ExtTrigger_Active_High;
 *#endif
 *#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
 *     config->chnlPolarity = 0U;
 *#endif
 * @endcode
 * @param config Pointer to user's TPM config structure.
 */
void TPM_GetDefaultConfig(tpm_config_t *config);

/*!
 * @brief Calculates the counter clock prescaler.
 *
 * This function calculates the values for SC[PS].
 *
 * @param base              TPM peripheral base address
 * @param counterPeriod_Hz  The desired frequency in Hz which corresponding to the time when the counter reaches the mod
 *                          value
 * @param srcClock_Hz       TPM counter clock in Hz
 *
 * return Calculated clock prescaler value.
 */
tpm_clock_prescale_t TPM_CalculateCounterClkDiv(TPM_Type *base, uint32_t counterPeriod_Hz, uint32_t srcClock_Hz);

/*! @}*/

/*!
 * @name Channel mode operations
 * @{
 */

/*!
 * @brief Configures the PWM signal parameters
 *
 * User calls this function to configure the PWM signals period, mode, dutycycle and edge. Use this
 * function to configure all the TPM channels that will be used to output a PWM signal
 *
 * @param base        TPM peripheral base address
 * @param chnlParams  Array of PWM channel parameters to configure the channel(s)
 * @param numOfChnls  Number of channels to configure, this should be the size of the array passed in
 * @param mode        PWM operation mode, options available in enumeration ::tpm_pwm_mode_t
 * @param pwmFreq_Hz  PWM signal frequency in Hz
 * @param srcClock_Hz TPM counter clock in Hz
 *
 * @return kStatus_Success if the PWM setup was successful,
 *         kStatus_Error on failure
 */
status_t TPM_SetupPwm(TPM_Type *base,
                      const tpm_chnl_pwm_signal_param_t *chnlParams,
                      uint8_t numOfChnls,
                      tpm_pwm_mode_t mode,
                      uint32_t pwmFreq_Hz,
                      uint32_t srcClock_Hz);

/*!
 * @brief Update the duty cycle of an active PWM signal
 *
 * @param base              TPM peripheral base address
 * @param chnlNumber        The channel number. In combined mode, this represents
 *                          the channel pair number
 * @param currentPwmMode    The current PWM mode set during PWM setup
 * @param dutyCyclePercent  New PWM pulse width, value should be between 0 to 100
 *                          0=inactive signal(0% duty cycle)...
 *                          100=active signal (100% duty cycle)
 * @return kStatus_Success if the PWM setup was successful,
 *         kStatus_Error on failure
 */
status_t TPM_UpdatePwmDutycycle(TPM_Type *base,
                                tpm_chnl_t chnlNumber,
                                tpm_pwm_mode_t currentPwmMode,
                                uint8_t dutyCyclePercent);

/*!
 * @brief Update the edge level selection for a channel
 *
 * @note When the TPM has PWM pause level select feature (FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT = 1), the PWM output
 *      cannot be turned off by selecting the output level. In this case, must use TPM_DisableChannel API to close the
 *      PWM output.
 *
 * @param base       TPM peripheral base address
 * @param chnlNumber The channel number
 * @param level      The level to be set to the ELSnB:ELSnA field; valid values are 00, 01, 10, 11.
 *                   See the appropriate SoC reference manual for details about this field.
 */
void TPM_UpdateChnlEdgeLevelSelect(TPM_Type *base, tpm_chnl_t chnlNumber, uint8_t level);

/*!
 * @brief Get the channel control bits value (mode, edge and level bit fileds).
 *
 * This function disable the channel by clear all mode and level control bits.
 *
 * @param base       TPM peripheral base address
 * @param chnlNumber The channel number
 * @return The contorl bits value. This is the logical OR of members of the
 *         enumeration @ref tpm_chnl_control_bit_mask_t.
 */
static inline uint8_t TPM_GetChannelContorlBits(TPM_Type *base, tpm_chnl_t chnlNumber)
{
    return (uint8_t)(base->CONTROLS[chnlNumber].CnSC &
                     (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK));
}

/*!
 * @brief Dsiable the channel.
 *
 * This function disable the channel by clear all mode and level control bits.
 *
 * @param base       TPM peripheral base address
 * @param chnlNumber The channel number
 */
static inline void TPM_DisableChannel(TPM_Type *base, tpm_chnl_t chnlNumber)
{
    do
    {
        /* Clear channel MSnB:MSnA and ELSnB:ELSnA to disable its output. */
        base->CONTROLS[chnlNumber].CnSC &=
            ~(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK);
        /* Wait till mode change to disable channel is acknowledged */
        /*
         * $Branch Coverage Justification$
         * (0U != (base->CONTROLS[chnlNumber].CnSC &
         *           (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)))
         * not covered.  $ref tpm_h_ref_1$.
         */

    } while (0U != (base->CONTROLS[chnlNumber].CnSC &
                    (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)));
}

/*!
 * @brief Enable the channel according to mode and level configs.
 *
 * This function enable the channel output according to input mode/level config parameters.
 *
 * @param base       TPM peripheral base address
 * @param chnlNumber The channel number
 * @param control     The contorl bits value. This is the logical OR of members of the
 *                    enumeration @ref tpm_chnl_control_bit_mask_t.
 */
static inline void TPM_EnableChannel(TPM_Type *base, tpm_chnl_t chnlNumber, uint8_t control)
{
#if defined(FSL_FEATURE_TPM_CnSC_CHF_WRITE_0_CLEAR) && FSL_FEATURE_TPM_CnSC_CHF_WRITE_0_CLEAR
    control |= TPM_CnSC_CHF_MASK;
#endif

    do
    {
        /* Set channel MSB:MSA and ELSB:ELSA bits. */
        base->CONTROLS[chnlNumber].CnSC =
            (base->CONTROLS[chnlNumber].CnSC &
             ~(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)) |
            (control & (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK));
        /* Wait till mode change is acknowledged */
        /*
         * $Branch Coverage Justification$
         * ((control & (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)) !=
         *    (uint8_t)(base->CONTROLS[chnlNumber].CnSC &
         *              (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)))
         * not covered. $ref tpm_h_ref_1$.
         */
    } while ((control & (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)) !=
             (uint8_t)(base->CONTROLS[chnlNumber].CnSC &
                       (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)));
}

/*!
 * @brief Enables capturing an input signal on the channel using the function parameters.
 *
 * When the edge specified in the captureMode argument occurs on the channel, the TPM counter is captured into
 * the CnV register. The user has to read the CnV register separately to get this value.
 *
 * @param base        TPM peripheral base address
 * @param chnlNumber  The channel number
 * @param captureMode Specifies which edge to capture
 */
void TPM_SetupInputCapture(TPM_Type *base, tpm_chnl_t chnlNumber, tpm_input_capture_edge_t captureMode);

/*!
 * @brief Configures the TPM to generate timed pulses.
 *
 * When the TPM counter matches the value of compareVal argument (this is written into CnV reg), the channel
 * output is changed based on what is specified in the compareMode argument.
 *
 * @param base         TPM peripheral base address
 * @param chnlNumber   The channel number
 * @param compareMode  Action to take on the channel output when the compare condition is met
 * @param compareValue Value to be programmed in the CnV register.
 */
void TPM_SetupOutputCompare(TPM_Type *base,
                            tpm_chnl_t chnlNumber,
                            tpm_output_compare_mode_t compareMode,
                            uint32_t compareValue);

#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
/*!
 * @brief Configures the dual edge capture mode of the TPM.
 *
 * This function allows to measure a pulse width of the signal on the input of channel of a
 * channel pair. The filter function is disabled if the filterVal argument passed is zero.
 *
 * @param base           TPM peripheral base address
 * @param chnlPairNumber The TPM channel pair number; options are 0, 1, 2, 3
 * @param edgeParam      Sets up the dual edge capture function
 * @param filterValue    Filter value, specify 0 to disable filter.
 */
void TPM_SetupDualEdgeCapture(TPM_Type *base,
                              tpm_chnl_t chnlPairNumber,
                              const tpm_dual_edge_capture_param_t *edgeParam,
                              uint32_t filterValue);
#endif

#if defined(FSL_FEATURE_TPM_HAS_QDCTRL) && FSL_FEATURE_TPM_HAS_QDCTRL
/*!
 * @brief Configures the parameters and activates the quadrature decode mode.
 *
 * @param base         TPM peripheral base address
 * @param phaseAParams Phase A configuration parameters
 * @param phaseBParams Phase B configuration parameters
 * @param quadMode     Selects encoding mode used in quadrature decoder mode
 */
void TPM_SetupQuadDecode(TPM_Type *base,
                         const tpm_phase_params_t *phaseAParams,
                         const tpm_phase_params_t *phaseBParams,
                         tpm_quad_decode_mode_t quadMode);
#endif

#if defined(FSL_FEATURE_TPM_HAS_POL) && FSL_FEATURE_TPM_HAS_POL
/*!
 * @brief Set the input and output polarity of each of the channels.
 *
 * @param base       TPM peripheral base address
 * @param chnlNumber The channel number
 * @param enable     true: Set the channel polarity to active high;
 *                   false: Set the channel polarity to active low;
 */
static inline void TPM_SetChannelPolarity(TPM_Type *base, tpm_chnl_t chnlNumber, bool enable)
{
    assert(1U == (uint8_t)FSL_FEATURE_TPM_POL_HAS_EFFECTn(base));
    if (enable)
    {
        base->POL &= ~((uint32_t)TPM_POL_POL0_MASK << (uint8_t)chnlNumber);
    }
    else
    {
        base->POL |= (uint32_t)TPM_POL_POL0_MASK << (uint8_t)chnlNumber;
    }
}
#endif
#if defined(FSL_FEATURE_TPM_HAS_TRIG) && FSL_FEATURE_TPM_HAS_TRIG
/*!
 * @brief Enable external trigger input to be used by channel.
 *
 * In input capture mode, configures the trigger input that is used by the channel to capture the
 * counter value. In output compare or PWM mode, configures the trigger input used to modulate
 * the channel output. When modulating the output, the output is forced to the channel initial
 * value whenever the trigger is not asserted.
 *
 * @note No matter how many external trigger sources there are, only input trigger 0 and 1 are used. The even numbered
 *      channels share the input trigger 0 and the odd numbered channels share the second input trigger 1.
 *
 * @param base       TPM peripheral base address
 * @param chnlNumber The channel number
 * @param enable     true: Configures trigger input 0 or 1 to be used by channel;
 *                   false: Trigger input has no effect on the channel
 */
static inline void TPM_EnableChannelExtTrigger(TPM_Type *base, tpm_chnl_t chnlNumber, bool enable)
{
    assert(1U == (uint8_t)FSL_FEATURE_TPM_TRIG_HAS_EFFECTn(base));
    if (enable)
    {
        base->TRIG |= (uint32_t)TPM_TRIG_TRIG0_MASK << (uint8_t)chnlNumber;
    }
    else
    {
        base->TRIG &= ~((uint32_t)TPM_TRIG_TRIG0_MASK << (uint8_t)chnlNumber);
    }
}
#endif
/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected TPM interrupts.
 *
 * @param base TPM peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::tpm_interrupt_enable_t
 */
void TPM_EnableInterrupts(TPM_Type *base, uint32_t mask);

/*!
 * @brief Disables the selected TPM interrupts.
 *
 * @param base TPM peripheral base address
 * @param mask The interrupts to disable. This is a logical OR of members of the
 *             enumeration ::tpm_interrupt_enable_t
 */
void TPM_DisableInterrupts(TPM_Type *base, uint32_t mask);

/*!
 * @brief Gets the enabled TPM interrupts.
 *
 * @param base TPM peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::tpm_interrupt_enable_t
 */
uint32_t TPM_GetEnabledInterrupts(TPM_Type *base);

/*!
 * @brief Register callback.
 *
 * If channel or overflow interrupt is enabled by the user, then a callback can be registered
 * which will be invoked when the interrupt is triggered.
 *
 * @param base       TPM peripheral base address
 * @param callback   Callback function
 */
void TPM_RegisterCallBack(TPM_Type *base, tpm_callback_t callback);

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */
/*!
 * @brief Gets the TPM channel value
 *
 * @note  The TPM channel value contain the captured TPM counter value for the input modes or the match value for the
 *        output modes.
 *
 * @param base       TPM peripheral base address
 * @param chnlNumber The channel number
 * @return The channle CnV regisyer value.
 */
static inline uint32_t TPM_GetChannelValue(TPM_Type *base, tpm_chnl_t chnlNumber)
{
    return base->CONTROLS[chnlNumber].CnV;
}

/*!
 * @brief Gets the TPM status flags
 *
 * @param base TPM peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::tpm_status_flags_t
 */
static inline uint32_t TPM_GetStatusFlags(TPM_Type *base)
{
    uint32_t statusFlags = 0;

#if defined(FSL_FEATURE_TPM_HAS_NO_STATUS) && FSL_FEATURE_TPM_HAS_NO_STATUS
    uint8_t chanlNumber = 0;

    /* Check the timer flag */
    if (0U != (base->SC & TPM_SC_TOF_MASK))
    {
        statusFlags |= (uint32_t)kTPM_TimeOverflowFlag;
    }

    for (chanlNumber = 0; (int8_t)chanlNumber < FSL_FEATURE_TPM_CHANNEL_COUNTn(base); chanlNumber++)
    {
        /* Check the channel flag */
        if (0U != (base->CONTROLS[chanlNumber].CnSC & TPM_CnSC_CHF_MASK))
        {
            statusFlags |= (1UL << chanlNumber);
        }
    }
#else
    statusFlags = base->STATUS;
#endif

    return statusFlags;
}

/*!
 * @brief Clears the TPM status flags
 *
 * @param base TPM peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::tpm_status_flags_t
 */
static inline void TPM_ClearStatusFlags(TPM_Type *base, uint32_t mask)
{
#if defined(FSL_FEATURE_TPM_HAS_NO_STATUS) && FSL_FEATURE_TPM_HAS_NO_STATUS
    uint32_t chnlStatusFlags = (mask & 0xFFU);
    uint8_t chnlNumber       = 0;

    /* Clear the timer overflow flag by writing a 0 to the bit while it is set */
    if (0U != (mask & (uint32_t)kTPM_TimeOverflowFlag))
    {
        base->SC &= ~TPM_SC_TOF_MASK;
    }
    /* Clear the channel flag */
    while (0U != chnlStatusFlags)
    {
        if (0U != (chnlStatusFlags & 0x1U))
        {
            base->CONTROLS[chnlNumber].CnSC &= ~TPM_CnSC_CHF_MASK;
        }
        chnlNumber++;
        chnlStatusFlags = chnlStatusFlags >> 1U;
    }
#else
    /* Clear the status flags */
    base->STATUS = mask;
#endif
}

/*! @}*/

/*!
 * @name Read and write the timer period
 * @{
 */

/*!
 * @brief Sets the timer period in units of ticks.
 *
 * Timers counts from 0 until it equals the count value set here. The count value is written to
 * the MOD register.
 *
 * @note
 * 1. This API allows the user to use the TPM module as a timer. Do not mix usage
 *    of this API with TPM's PWM setup API's.
 * 2. Call the utility macros provided in the fsl_common.h to convert usec or msec to ticks.
 *
 * @param base TPM peripheral base address
 * @param ticks A timer period in units of ticks, which should be equal or greater than 1.
 */
static inline void TPM_SetTimerPeriod(TPM_Type *base, uint32_t ticks)
{
    if (1U != (uint8_t)FSL_FEATURE_TPM_HAS_32BIT_COUNTERn(base))
    {
        assert(ticks <= 0xFFFFU);
    }
    base->MOD = ticks;
}

/*!
 * @brief Reads the current timer counting value.
 *
 * This function returns the real-time timer counting value in a range from 0 to a
 * timer period.
 *
 * @note Call the utility macros provided in the fsl_common.h to convert ticks to usec or msec.
 *
 * @param base TPM peripheral base address
 *
 * @return The current counter value in ticks
 */
static inline uint32_t TPM_GetCurrentTimerCount(TPM_Type *base)
{
    return (uint32_t)((base->CNT & TPM_CNT_COUNT_MASK) >> TPM_CNT_COUNT_SHIFT);
}

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the TPM counter.
 *
 * @param base        TPM peripheral base address
 * @param clockSource TPM clock source; once clock source is set the counter will start running
 */
static inline void TPM_StartTimer(TPM_Type *base, tpm_clock_source_t clockSource)
{
    uint32_t reg = base->SC;
#if defined(FSL_FEATURE_TPM_HAS_SC_CLKS) && FSL_FEATURE_TPM_HAS_SC_CLKS
    reg &= ~(TPM_SC_CLKS_MASK);
    reg |= TPM_SC_CLKS(clockSource);
#else
    reg &= ~(TPM_SC_CMOD_MASK);
    reg |= TPM_SC_CMOD(clockSource);
#endif
    base->SC = reg;
}

/*!
 * @brief Stops the TPM counter.
 *
 * @param base TPM peripheral base address
 */
static inline void TPM_StopTimer(TPM_Type *base)
{
#if defined(FSL_FEATURE_TPM_HAS_SC_CLKS) && FSL_FEATURE_TPM_HAS_SC_CLKS
    /* Set clock source to none to disable counter */
    base->SC &= ~(TPM_SC_CLKS_MASK);

    /* Wait till this reads as zero acknowledging the counter is disabled */
    while (0U != (base->SC & TPM_SC_CLKS_MASK))
    {
    }
#else
    /* Set clock source to none to disable counter */
    base->SC &= ~(TPM_SC_CMOD_MASK);

    /* Wait till this reads as zero acknowledging the counter is disabled */
    while (0U != (base->SC & TPM_SC_CMOD_MASK))
    {
    }
#endif
}

/*! @}*/

#if defined(FSL_FEATURE_TPM_HAS_GLOBAL) && FSL_FEATURE_TPM_HAS_GLOBAL
/*!
 * @brief Performs a software reset on the TPM module.
 *
 * Reset all internal logic and registers, except the Global Register. Remains set until cleared by software.
 *
 * @note TPM software reset is available on certain SoC's only
 *
 * @param base TPM peripheral base address
 */
static inline void TPM_Reset(TPM_Type *base)
{
    base->GLOBAL |= TPM_GLOBAL_RST_MASK;
    base->GLOBAL &= ~TPM_GLOBAL_RST_MASK;
}
#endif

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_TPM_H_ */
