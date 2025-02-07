/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_PWM_H_
#define FSL_PWM_H_

#include "fsl_common.h"

/*!
 * @addtogroup pwm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
#define FSL_PWM_DRIVER_VERSION (MAKE_VERSION(2, 8, 4)) /*!< Version 2.8.4 */
/*! @} */

/*! Number of bits per submodule for software output control */
#define PWM_SUBMODULE_SWCONTROL_WIDTH 2
/*! Because setting the pwm duty cycle doesn't support PWMX, getting the pwm duty cycle also doesn't support PWMX. */
#define PWM_SUBMODULE_CHANNEL 2

/*! @brief List of PWM submodules */
typedef enum _pwm_submodule
{
    kPWM_Module_0 = 0U, /*!< Submodule 0 */
    kPWM_Module_1,      /*!< Submodule 1 */
    kPWM_Module_2,      /*!< Submodule 2 */
#if defined(FSL_FEATURE_PWM_SUBMODULE_COUNT) && (FSL_FEATURE_PWM_SUBMODULE_COUNT > 3U)
    kPWM_Module_3       /*!< Submodule 3 */
#endif /* FSL_FEATURE_PWM_SUBMODULE_COUNT */
} pwm_submodule_t;

/*! @brief List of PWM channels in each module */
typedef enum _pwm_channels
{
    kPWM_PwmB = 0U,
    kPWM_PwmA,
    kPWM_PwmX
} pwm_channels_t;

/*! @brief List of PWM value registers */
typedef enum _pwm_value_register
{
    kPWM_ValueRegister_0 = 0U, /*!< PWM Value0 register */
    kPWM_ValueRegister_1,      /*!< PWM Value1 register */
    kPWM_ValueRegister_2,      /*!< PWM Value2 register */
    kPWM_ValueRegister_3,      /*!< PWM Value3 register */
    kPWM_ValueRegister_4,      /*!< PWM Value4 register */
    kPWM_ValueRegister_5       /*!< PWM Value5 register */
} pwm_value_register_t;

/*! @brief List of PWM value registers mask */
enum _pwm_value_register_mask
{
    kPWM_ValueRegisterMask_0 = (1U << 0), /*!< PWM Value0 register mask */
    kPWM_ValueRegisterMask_1 = (1U << 1), /*!< PWM Value1 register mask */
    kPWM_ValueRegisterMask_2 = (1U << 2), /*!< PWM Value2 register mask */
    kPWM_ValueRegisterMask_3 = (1U << 3), /*!< PWM Value3 register mask */
    kPWM_ValueRegisterMask_4 = (1U << 4), /*!< PWM Value4 register mask */
    kPWM_ValueRegisterMask_5 = (1U << 5)  /*!< PWM Value5 register mask */
};

/*! @brief PWM clock source selection.*/
typedef enum _pwm_clock_source
{
    kPWM_BusClock = 0U,  /*!< The IPBus clock is used as the clock */
    kPWM_ExternalClock,  /*!< EXT_CLK is used as the clock */
    kPWM_Submodule0Clock /*!< Clock of the submodule 0 (AUX_CLK) is used as the source clock */
} pwm_clock_source_t;

/*! @brief PWM prescaler factor selection for clock source*/
typedef enum _pwm_clock_prescale
{
    kPWM_Prescale_Divide_1 = 0U, /*!< PWM clock frequency = fclk/1 */
    kPWM_Prescale_Divide_2,      /*!< PWM clock frequency = fclk/2 */
    kPWM_Prescale_Divide_4,      /*!< PWM clock frequency = fclk/4 */
    kPWM_Prescale_Divide_8,      /*!< PWM clock frequency = fclk/8 */
    kPWM_Prescale_Divide_16,     /*!< PWM clock frequency = fclk/16 */
    kPWM_Prescale_Divide_32,     /*!< PWM clock frequency = fclk/32 */
    kPWM_Prescale_Divide_64,     /*!< PWM clock frequency = fclk/64 */
    kPWM_Prescale_Divide_128     /*!< PWM clock frequency = fclk/128 */
} pwm_clock_prescale_t;

/*! @brief Options that can trigger a PWM FORCE_OUT */
typedef enum _pwm_force_output_trigger
{
    kPWM_Force_Local = 0U,   /*!< The local force signal, CTRL2[FORCE], from the submodule is used to force updates */
    kPWM_Force_Master,       /*!< The master force signal from submodule 0 is used to force updates */
    kPWM_Force_LocalReload,  /*!< The local reload signal from this submodule is used to force updates without regard to
                                the state of LDOK */
    kPWM_Force_MasterReload, /*!< The master reload signal from submodule 0 is used to force updates if LDOK is set */
    kPWM_Force_LocalSync,    /*!< The local sync signal from this submodule is used to force updates */
    kPWM_Force_MasterSync,   /*!< The master sync signal from submodule0 is used to force updates */
    kPWM_Force_External,     /*!< The external force signal, EXT_FORCE, from outside the PWM module causes updates */
    kPWM_Force_ExternalSync  /*!< The external sync signal, EXT_SYNC, from outside the PWM module causes updates */
} pwm_force_output_trigger_t;

/*! @brief PWM channel output status */
typedef enum _pwm_output_state
{
    kPWM_HighState = 0, /*!< The output state of PWM channel is high */
    kPWM_LowState,      /*!< The output state of PWM channel is low */
    kPWM_NormalState,   /*!< The output state of PWM channel is normal */
    kPWM_InvertState,   /*!< The output state of PWM channel is invert */
    kPWM_MaskState      /*!< The output state of PWM channel is mask */
} pwm_output_state_t;

/*! @brief PWM counter initialization options */
typedef enum _pwm_init_source
{
    kPWM_Initialize_LocalSync = 0U, /*!< Local sync causes initialization */
    kPWM_Initialize_MasterReload,   /*!< Master reload from submodule 0 causes initialization */
    kPWM_Initialize_MasterSync,     /*!< Master sync from submodule 0 causes initialization */
    kPWM_Initialize_ExtSync         /*!< EXT_SYNC causes initialization */
} pwm_init_source_t;

/*! @brief PWM load frequency selection */
typedef enum _pwm_load_frequency
{
    kPWM_LoadEveryOportunity = 0U, /*!< Every PWM opportunity */
    kPWM_LoadEvery2Oportunity,     /*!< Every 2 PWM opportunities */
    kPWM_LoadEvery3Oportunity,     /*!< Every 3 PWM opportunities */
    kPWM_LoadEvery4Oportunity,     /*!< Every 4 PWM opportunities */
    kPWM_LoadEvery5Oportunity,     /*!< Every 5 PWM opportunities */
    kPWM_LoadEvery6Oportunity,     /*!< Every 6 PWM opportunities */
    kPWM_LoadEvery7Oportunity,     /*!< Every 7 PWM opportunities */
    kPWM_LoadEvery8Oportunity,     /*!< Every 8 PWM opportunities */
    kPWM_LoadEvery9Oportunity,     /*!< Every 9 PWM opportunities */
    kPWM_LoadEvery10Oportunity,    /*!< Every 10 PWM opportunities */
    kPWM_LoadEvery11Oportunity,    /*!< Every 11 PWM opportunities */
    kPWM_LoadEvery12Oportunity,    /*!< Every 12 PWM opportunities */
    kPWM_LoadEvery13Oportunity,    /*!< Every 13 PWM opportunities */
    kPWM_LoadEvery14Oportunity,    /*!< Every 14 PWM opportunities */
    kPWM_LoadEvery15Oportunity,    /*!< Every 15 PWM opportunities */
    kPWM_LoadEvery16Oportunity     /*!< Every 16 PWM opportunities */
} pwm_load_frequency_t;

/*! @brief List of PWM fault selections */
typedef enum _pwm_fault_input
{
    kPWM_Fault_0 = 0U, /*!< Fault 0 input pin */
    kPWM_Fault_1,      /*!< Fault 1 input pin */
    kPWM_Fault_2,      /*!< Fault 2 input pin */
    kPWM_Fault_3       /*!< Fault 3 input pin */
} pwm_fault_input_t;

/*! @brief List of PWM fault disable mapping selections */
typedef enum _pwm_fault_disable
{
    kPWM_FaultDisable_0 = (1U << 0), /*!< Fault 0 disable mapping */
    kPWM_FaultDisable_1 = (1U << 1), /*!< Fault 1 disable mapping */
    kPWM_FaultDisable_2 = (1U << 2), /*!< Fault 2 disable mapping */
    kPWM_FaultDisable_3 = (1U << 3)  /*!< Fault 3 disable mapping */
} pwm_fault_disable_t;

/*! @brief List of PWM fault channels */
typedef enum _pwm_fault_channels
{
    kPWM_faultchannel_0 = 0U,
    kPWM_faultchannel_1
} pwm_fault_channels_t;

/*! @brief PWM capture edge select */
typedef enum _pwm_input_capture_edge
{
    kPWM_Disable = 0U,   /*!< Disabled */
    kPWM_FallingEdge,    /*!< Capture on falling edge only */
    kPWM_RisingEdge,     /*!< Capture on rising edge only */
    kPWM_RiseAndFallEdge /*!< Capture on rising or falling edge */
} pwm_input_capture_edge_t;

/*! @brief PWM output options when a FORCE_OUT signal is asserted */
typedef enum _pwm_force_signal
{
    kPWM_UsePwm = 0U,     /*!< Generated PWM signal is used by the deadtime logic.*/
    kPWM_InvertedPwm,     /*!< Inverted PWM signal is used by the deadtime logic.*/
    kPWM_SoftwareControl, /*!< Software controlled value is used by the deadtime logic. */
    kPWM_UseExternal      /*!< PWM_EXTA signal is used by the deadtime logic. */
} pwm_force_signal_t;

/*! @brief Options available for the PWM A & B pair operation */
typedef enum _pwm_chnl_pair_operation
{
    kPWM_Independent = 0U,  /*!< PWM A & PWM B operate as 2 independent channels */
    kPWM_ComplementaryPwmA, /*!< PWM A & PWM B are complementary channels, PWM A generates the signal */
    kPWM_ComplementaryPwmB  /*!< PWM A & PWM B are complementary channels, PWM B generates the signal */
} pwm_chnl_pair_operation_t;

/*! @brief Options available on how to load the buffered-registers with new values */
typedef enum _pwm_register_reload
{
    kPWM_ReloadImmediate = 0U,     /*!< Buffered-registers get loaded with new values as soon as LDOK bit is set */
    kPWM_ReloadPwmHalfCycle,       /*!< Registers loaded on a PWM half cycle */
    kPWM_ReloadPwmFullCycle,       /*!< Registers loaded on a PWM full cycle */
    kPWM_ReloadPwmHalfAndFullCycle /*!< Registers loaded on a PWM half & full cycle */
} pwm_register_reload_t;

/*! @brief Options available on how to re-enable the PWM output when recovering from a fault */
typedef enum _pwm_fault_recovery_mode
{
    kPWM_NoRecovery = 0U,        /*!< PWM output will stay inactive */
    kPWM_RecoverHalfCycle,       /*!< PWM output re-enabled at the first half cycle */
    kPWM_RecoverFullCycle,       /*!< PWM output re-enabled at the first full cycle */
    kPWM_RecoverHalfAndFullCycle /*!< PWM output re-enabled at the first half or full cycle */
} pwm_fault_recovery_mode_t;

/*! @brief List of PWM interrupt options */
typedef enum _pwm_interrupt_enable
{
    kPWM_CompareVal0InterruptEnable = (1U << 0),  /*!< PWM VAL0 compare interrupt */
    kPWM_CompareVal1InterruptEnable = (1U << 1),  /*!< PWM VAL1 compare interrupt */
    kPWM_CompareVal2InterruptEnable = (1U << 2),  /*!< PWM VAL2 compare interrupt */
    kPWM_CompareVal3InterruptEnable = (1U << 3),  /*!< PWM VAL3 compare interrupt */
    kPWM_CompareVal4InterruptEnable = (1U << 4),  /*!< PWM VAL4 compare interrupt */
    kPWM_CompareVal5InterruptEnable = (1U << 5),  /*!< PWM VAL5 compare interrupt */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX
    kPWM_CaptureX0InterruptEnable   = (1U << 6),  /*!< PWM capture X0 interrupt */
    kPWM_CaptureX1InterruptEnable   = (1U << 7),  /*!< PWM capture X1 interrupt */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB
    kPWM_CaptureB0InterruptEnable   = (1U << 8),  /*!< PWM capture B0 interrupt */
    kPWM_CaptureB1InterruptEnable   = (1U << 9),  /*!< PWM capture B1 interrupt */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA
    kPWM_CaptureA0InterruptEnable   = (1U << 10), /*!< PWM capture A0 interrupt */
    kPWM_CaptureA1InterruptEnable   = (1U << 11), /*!< PWM capture A1 interrupt */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA */
    kPWM_ReloadInterruptEnable      = (1U << 12), /*!< PWM reload interrupt */
    kPWM_ReloadErrorInterruptEnable = (1U << 13), /*!< PWM reload error interrupt */
    kPWM_Fault0InterruptEnable      = (1U << 16), /*!< PWM fault 0 interrupt */
    kPWM_Fault1InterruptEnable      = (1U << 17), /*!< PWM fault 1 interrupt */
    kPWM_Fault2InterruptEnable      = (1U << 18), /*!< PWM fault 2 interrupt */
    kPWM_Fault3InterruptEnable      = (1U << 19)  /*!< PWM fault 3 interrupt */
} pwm_interrupt_enable_t;

/*! @brief List of PWM status flags */
typedef enum _pwm_status_flags
{
    kPWM_CompareVal0Flag = (1U << 0),  /*!< PWM VAL0 compare flag */
    kPWM_CompareVal1Flag = (1U << 1),  /*!< PWM VAL1 compare flag */
    kPWM_CompareVal2Flag = (1U << 2),  /*!< PWM VAL2 compare flag */
    kPWM_CompareVal3Flag = (1U << 3),  /*!< PWM VAL3 compare flag */
    kPWM_CompareVal4Flag = (1U << 4),  /*!< PWM VAL4 compare flag */
    kPWM_CompareVal5Flag = (1U << 5),  /*!< PWM VAL5 compare flag */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX
    kPWM_CaptureX0Flag   = (1U << 6),  /*!< PWM capture X0 flag */
    kPWM_CaptureX1Flag   = (1U << 7),  /*!< PWM capture X1 flag */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB
    kPWM_CaptureB0Flag   = (1U << 8),  /*!< PWM capture B0 flag */
    kPWM_CaptureB1Flag   = (1U << 9),  /*!< PWM capture B1 flag */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA
    kPWM_CaptureA0Flag   = (1U << 10), /*!< PWM capture A0 flag */
    kPWM_CaptureA1Flag   = (1U << 11), /*!< PWM capture A1 flag */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA */
    kPWM_ReloadFlag      = (1U << 12), /*!< PWM reload flag */
    kPWM_ReloadErrorFlag = (1U << 13), /*!< PWM reload error flag */
    kPWM_RegUpdatedFlag  = (1U << 14), /*!< PWM registers updated flag */
    kPWM_Fault0Flag      = (1U << 16), /*!< PWM fault 0 flag */
    kPWM_Fault1Flag      = (1U << 17), /*!< PWM fault 1 flag */
    kPWM_Fault2Flag      = (1U << 18), /*!< PWM fault 2 flag */
    kPWM_Fault3Flag      = (1U << 19)  /*!< PWM fault 3 flag */
} pwm_status_flags_t;

/*! @brief List of PWM DMA options */
typedef enum _pwm_dma_enable
{
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX
    kPWM_CaptureX0DMAEnable = (1U << 0), /*!< PWM capture X0 DMA */
    kPWM_CaptureX1DMAEnable = (1U << 1), /*!< PWM capture X1 DMA */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX */    
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB    
    kPWM_CaptureB0DMAEnable = (1U << 2), /*!< PWM capture B0 DMA */
    kPWM_CaptureB1DMAEnable = (1U << 3), /*!< PWM capture B1 DMA */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA
    kPWM_CaptureA0DMAEnable = (1U << 4), /*!< PWM capture A0 DMA */
    kPWM_CaptureA1DMAEnable = (1U << 5)  /*!< PWM capture A1 DMA */
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA */
} pwm_dma_enable_t;

/*! @brief List of PWM capture DMA enable source select */
typedef enum _pwm_dma_source_select
{
    kPWM_DMARequestDisable = 0U, /*!< Read DMA requests disabled */
    kPWM_DMAWatermarksEnable,    /*!< Exceeding a FIFO watermark sets the DMA read request */
    kPWM_DMALocalSync,           /*!< A local sync (VAL1 matches counter) sets the read DMA request */
    kPWM_DMALocalReload          /*!< A local reload (STS[RF] being set) sets the read DMA request */
} pwm_dma_source_select_t;

/*! @brief PWM FIFO Watermark AND Control */
typedef enum _pwm_watermark_control
{
    kPWM_FIFOWatermarksOR = 0U, /*!< Selected FIFO watermarks are OR'ed together */
    kPWM_FIFOWatermarksAND      /*!< Selected FIFO watermarks are AND'ed together */
} pwm_watermark_control_t;

/*! @brief PWM operation mode */
typedef enum _pwm_mode
{
    kPWM_SignedCenterAligned = 0U, /*!< Signed center-aligned */
    kPWM_CenterAligned,            /*!< Unsigned cente-aligned */
    kPWM_SignedEdgeAligned,        /*!< Signed edge-aligned */
    kPWM_EdgeAligned               /*!< Unsigned edge-aligned */
} pwm_mode_t;

/*! @brief PWM output pulse mode, high-true or low-true */
typedef enum _pwm_level_select
{
    kPWM_HighTrue = 0U, /*!< High level represents "on" or "active" state */
    kPWM_LowTrue        /*!< Low level represents "on" or "active" state */
} pwm_level_select_t;

/*! @brief PWM output fault status */
typedef enum _pwm_fault_state
{
    kPWM_PwmFaultState0 =
        0U,              /*!< Output is forced to logic 0 state prior to consideration of output polarity control. */
    kPWM_PwmFaultState1, /*!< Output is forced to logic 1 state prior to consideration of output polarity control. */
    kPWM_PwmFaultState2, /*!< Output is tristated. */
    kPWM_PwmFaultState3  /*!< Output is tristated. */
} pwm_fault_state_t;

/*! @brief PWM reload source select */
typedef enum _pwm_reload_source_select
{
    kPWM_LocalReload = 0U, /*!< The local reload signal is used to reload registers */
    kPWM_MasterReload      /*!< The master reload signal (from submodule 0) is used to reload */
} pwm_reload_source_select_t;

/*! @brief PWM fault clearing options */
typedef enum _pwm_fault_clear
{
    kPWM_Automatic = 0U, /*!< Automatic fault clearing  */
    kPWM_ManualNormal,   /*!< Manual fault clearing with no fault safety mode */
    kPWM_ManualSafety    /*!< Manual fault clearing with fault safety mode */
} pwm_fault_clear_t;

/*! @brief Options for submodule master control operation */
typedef enum _pwm_module_control
{
    kPWM_Control_Module_0 = (1U << 0), /*!< Control submodule 0's start/stop,buffer reload operation */
    kPWM_Control_Module_1 = (1U << 1), /*!< Control submodule 1's start/stop,buffer reload operation */
    kPWM_Control_Module_2 = (1U << 2), /*!< Control submodule 2's start/stop,buffer reload operation */
    kPWM_Control_Module_3 = (1U << 3)  /*!< Control submodule 3's start/stop,buffer reload operation */
} pwm_module_control_t;

/*! @brief Structure for the user to define the PWM signal characteristics */
typedef struct _pwm_signal_param
{
    pwm_channels_t pwmChannel; /*!< PWM channel being configured; PWM A or PWM B */
    uint8_t dutyCyclePercent;  /*!< PWM pulse width, value should be between 0 to 100
                                    0=inactive signal(0% duty cycle)...
                                    100=always active signal (100% duty cycle)*/
    pwm_level_select_t level;  /*!< PWM output active level select */
    uint16_t deadtimeValue;    /*!< The deadtime value; only used if channel pair is operating in complementary mode */
    pwm_fault_state_t faultState; /*!< PWM output fault status */
    bool pwmchannelenable;        /*!< Enable PWM output */
} pwm_signal_param_t;

/*!
 * @brief PWM config structure
 *
 * This structure holds the configuration settings for the PWM peripheral. To initialize this
 * structure to reasonable defaults, call the PWM_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _pwm_config
{
    bool enableDebugMode; /*!< true: PWM continues to run in debug mode;
                               false: PWM is paused in debug mode */
#if !defined(FSL_FEATURE_PWM_HAS_NO_WAITEN) || (!FSL_FEATURE_PWM_HAS_NO_WAITEN)
    bool enableWait;                         /*!< true: PWM continues to run in WAIT mode;
                                                  false: PWM is paused in WAIT mode */
#endif                                       /* FSL_FEATURE_PWM_HAS_NO_WAITEN */
    pwm_init_source_t initializationControl; /*!< Option to initialize the counter */
    pwm_clock_source_t clockSource;          /*!< Clock source for the counter */
    pwm_clock_prescale_t prescale;           /*!< Pre-scaler to divide down the clock */
    pwm_chnl_pair_operation_t pairOperation; /*!< Channel pair in indepedent or complementary mode */
    pwm_register_reload_t reloadLogic;       /*!< PWM Reload logic setup */
    pwm_reload_source_select_t reloadSelect; /*!< Reload source select */
    pwm_load_frequency_t reloadFrequency;    /*!< Specifies when to reload, used when user's choice
                                                  is not immediate reload */
    pwm_force_output_trigger_t forceTrigger; /*!< Specify which signal will trigger a FORCE_OUT */
} pwm_config_t;

/*! @brief Structure for the user to configure the fault input filter. */
typedef struct _pwm_fault_input_filter_param
{
    uint8_t faultFilterCount;  /*!< Fault filter count */
    uint8_t faultFilterPeriod; /*!< Fault filter period;value of 0 will bypass the filter */
    bool faultGlitchStretch;   /*!< Fault Glitch Stretch Enable: A logic 1 means that input
                                    fault signals will be stretched to at least 2 IPBus clock cycles */
} pwm_fault_input_filter_param_t;

/*! @brief Structure is used to hold the parameters to configure a PWM fault */
typedef struct _pwm_fault_param
{
    pwm_fault_clear_t faultClearingMode;   /*!< Fault clearing mode to use */
    bool faultLevel;                       /*!< true: Logic 1 indicates fault;
                                                false: Logic 0 indicates fault */
    bool enableCombinationalPath;          /*!< true: Combinational Path from fault input is enabled;
                                                false: No combination path is available */
    pwm_fault_recovery_mode_t recoverMode; /*!< Specify when to re-enable the PWM output */
} pwm_fault_param_t;

/*!
 * @brief Structure is used to hold parameters to configure the capture capability of a signal pin
 */
typedef struct _pwm_input_capture_param
{
    bool captureInputSel;           /*!< true: Use the edge counter signal as source
                                         false: Use the raw input signal from the pin as source */
    uint8_t edgeCompareValue;       /*!< Compare value, used only if edge counter is used as source */
    pwm_input_capture_edge_t edge0; /*!< Specify which edge causes a capture for input circuitry 0 */
    pwm_input_capture_edge_t edge1; /*!< Specify which edge causes a capture for input circuitry 1 */
    bool enableOneShotCapture;      /*!< true: Use one-shot capture mode;
                                         false: Use free-running capture mode */
    uint8_t fifoWatermark;          /*!< Watermark level for capture FIFO. The capture flags in
                                         the status register will set if the word count in the FIFO
                                         is greater than this watermark level */
} pwm_input_capture_param_t;

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
 * @brief Ungates the PWM submodule clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the PWM driver.
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 * @param config    Pointer to user's PWM config structure.
 *
 * @return kStatus_Success means success; else failed.
 */
status_t PWM_Init(PWM_Type *base, pwm_submodule_t subModule, const pwm_config_t *config);

/*!
 * @brief Gate the PWM submodule clock
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to deinitialize
 */
void PWM_Deinit(PWM_Type *base, pwm_submodule_t subModule);

/*!
 * @brief  Fill in the PWM config struct with the default settings
 *
 * The default values are:
 * @code
 *   config->enableDebugMode = false;
 *   config->enableWait = false;
 *   config->reloadSelect = kPWM_LocalReload;
 *   config->clockSource = kPWM_BusClock;
 *   config->prescale = kPWM_Prescale_Divide_1;
 *   config->initializationControl = kPWM_Initialize_LocalSync;
 *   config->forceTrigger = kPWM_Force_Local;
 *   config->reloadFrequency = kPWM_LoadEveryOportunity;
 *   config->reloadLogic = kPWM_ReloadImmediate;
 *   config->pairOperation = kPWM_Independent;
 * @endcode
 * @param config Pointer to user's PWM config structure.
 */
void PWM_GetDefaultConfig(pwm_config_t *config);

/*! @}*/

/*!
 * @name Module PWM output
 * @{
 */
/*!
 * @brief Sets up the PWM signals for a PWM submodule.
 *
 * The function initializes the submodule according to the parameters passed in by the user. The function
 * also sets up the value compare registers to match the PWM signal requirements.
 * If the dead time insertion logic is enabled, the pulse period is reduced by the
 * dead time period specified by the user.
 *
 * @param base        PWM peripheral base address
 * @param subModule   PWM submodule to configure
 * @param chnlParams  Array of PWM channel parameters to configure the channel(s), PWMX submodule is not supported.
 * @param numOfChnls  Number of channels to configure, this should be the size of the array passed in.
 *                    Array size should not be more than 2 as each submodule has 2 pins to output PWM
 * @param mode        PWM operation mode, options available in enumeration ::pwm_mode_t
 * @param pwmFreq_Hz  PWM signal frequency in Hz
 * @param srcClock_Hz PWM source clock of correspond submodule in Hz. If source clock of submodule1,2,3 is from
 *                    submodule0 AUX_CLK, its source clock is submodule0 source clock divided with submodule0
 *                    prescaler value instead of submodule0 source clock.
 *
 * @return Returns kStatus_Fail if there was error setting up the signal; kStatus_Success otherwise
 */
status_t PWM_SetupPwm(PWM_Type *base,
                      pwm_submodule_t subModule,
                      const pwm_signal_param_t *chnlParams,
                      uint8_t numOfChnls,
                      pwm_mode_t mode,
                      uint32_t pwmFreq_Hz,
                      uint32_t srcClock_Hz);

/*!
 * @brief Set PWM phase shift for PWM channel running on channel PWM_A, PWM_B which with 50% duty cycle.
 *
 * @param base        PWM peripheral base address
 * @param subModule   PWM submodule to configure
 * @param pwmChannel  PWM channel to configure
 * @param pwmFreq_Hz  PWM signal frequency in Hz
 * @param srcClock_Hz PWM main counter clock in Hz.
 * @param shiftvalue  Phase shift value, range in 0 ~ 50
 * @param doSync      true: Set LDOK bit for the submodule list;
 *                    false: LDOK bit don't set, need to call PWM_SetPwmLdok to sync update.
 *
 * @return Returns kStatus_Fail if there was error setting up the signal; kStatus_Success otherwise
 */
status_t PWM_SetupPwmPhaseShift(PWM_Type *base,
                                pwm_submodule_t subModule,
                                pwm_channels_t pwmChannel,
                                uint32_t pwmFreq_Hz,
                                uint32_t srcClock_Hz,
                                uint8_t shiftvalue,
                                bool doSync);

/*!
 * @brief Updates the PWM signal's dutycycle.
 *
 * The function updates the PWM dutycyle to the new value that is passed in.
 * If the dead time insertion logic is enabled then the pulse period is reduced by the
 * dead time period specified by the user.
 *
 * @param base              PWM peripheral base address
 * @param subModule         PWM submodule to configure
 * @param pwmSignal         Signal (PWM A or PWM B) to update
 * @param currPwmMode       The current PWM mode set during PWM setup
 * @param dutyCyclePercent  New PWM pulse width, value should be between 0 to 100
 *                          0=inactive signal(0% duty cycle)...
 *                          100=active signal (100% duty cycle)
 */
void PWM_UpdatePwmDutycycle(PWM_Type *base,
                            pwm_submodule_t subModule,
                            pwm_channels_t pwmSignal,
                            pwm_mode_t currPwmMode,
                            uint8_t dutyCyclePercent);

/*!
 * @brief Updates the PWM signal's dutycycle with 16-bit accuracy.
 *
 * The function updates the PWM dutycyle to the new value that is passed in.
 * If the dead time insertion logic is enabled then the pulse period is reduced by the
 * dead time period specified by the user.
 *
 * @param base              PWM peripheral base address
 * @param subModule         PWM submodule to configure
 * @param pwmSignal         Signal (PWM A or PWM B) to update
 * @param currPwmMode       The current PWM mode set during PWM setup
 * @param dutyCycle         New PWM pulse width, value should be between 0 to 65535
 *                          0=inactive signal(0% duty cycle)...
 *                          65535=active signal (100% duty cycle)
 */
void PWM_UpdatePwmDutycycleHighAccuracy(
    PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmSignal, pwm_mode_t currPwmMode, uint16_t dutyCycle);

/*!
 * @brief Update the PWM signal's period and dutycycle for a PWM submodule.
 *
 * The function updates PWM signal period generated by a specific submodule according to the parameters
 * passed in by the user. This function can also set dutycycle weather you want to keep original dutycycle
 * or update new dutycycle. Call this function in local sync control mode because PWM period is depended by  
 * INIT and VAL1 register of each submodule. In master sync initialization control mode, call this function 
 * to update INIT and VAL1 register of all submodule because PWM period is depended by INIT and VAL1 register
 * in submodule0. If the dead time insertion logic is enabled, the pulse period is reduced by the dead time 
 * period specified by the user. PWM signal will not be generated if its period is less than dead time duration.
 *
 * @param base        PWM peripheral base address
 * @param subModule   PWM submodule to configure
 * @param pwmSignal   Signal (PWM A or PWM B) to update
 * @param currPwmMode The current PWM mode set during PWM setup, options available in enumeration ::pwm_mode_t
 * @param pulseCnt    New PWM period, value should be between 0 to 65535
 *                    0=minimum PWM period...
 *                    65535=maximum PWM period
 * @param dutyCycle   New PWM pulse width of channel, value should be between 0 to 65535
 *                    0=inactive signal(0% duty cycle)...
 *                    65535=active signal (100% duty cycle)
 *                    You can keep original duty cycle or update new duty cycle
 */
void PWM_UpdatePwmPeriodAndDutycycle(PWM_Type *base,
                                         pwm_submodule_t subModule,
                                         pwm_channels_t pwmSignal,
                                         pwm_mode_t currPwmMode,
                                         uint16_t pulseCnt,
                                         uint16_t dutyCycle);

/*! @}*/

/*!
 * @brief Sets up the PWM input capture
 *
 * Each PWM submodule has 3 pins that can be configured for use as input capture pins. This function
 * sets up the capture parameters for each pin and enables the pin for input capture operation.
 *
 * @param base               PWM peripheral base address
 * @param subModule          PWM submodule to configure
 * @param pwmChannel         Channel in the submodule to setup
 * @param inputCaptureParams Parameters passed in to set up the input pin
 */
void PWM_SetupInputCapture(PWM_Type *base,
                           pwm_submodule_t subModule,
                           pwm_channels_t pwmChannel,
                           const pwm_input_capture_param_t *inputCaptureParams);

/*!
 * @brief Sets up the PWM fault input filter.
 *
 * @param base                   PWM peripheral base address
 * @param faultInputFilterParams Parameters passed in to set up the fault input filter.
 */
void PWM_SetupFaultInputFilter(PWM_Type *base, const pwm_fault_input_filter_param_t *faultInputFilterParams);

/*!
 * @brief Sets up the PWM fault protection.
 *
 * PWM has 4 fault inputs.
 *
 * @param base        PWM peripheral base address
 * @param faultNum    PWM fault to configure.
 * @param faultParams Pointer to the PWM fault config structure
 */
void PWM_SetupFaults(PWM_Type *base, pwm_fault_input_t faultNum, const pwm_fault_param_t *faultParams);

/*!
 * @brief  Fill in the PWM fault config struct with the default settings
 *
 * The default values are:
 * @code
 *   config->faultClearingMode = kPWM_Automatic;
 *   config->faultLevel = false;
 *   config->enableCombinationalPath = true;
 *   config->recoverMode = kPWM_NoRecovery;
 * @endcode
 * @param config Pointer to user's PWM fault config structure.
 */
void PWM_FaultDefaultConfig(pwm_fault_param_t *config);

/*!
 * @brief Selects the signal to output on a PWM pin when a FORCE_OUT signal is asserted.
 *
 * The user specifies which channel to configure by supplying the submodule number and whether
 * to modify PWM A or PWM B within that submodule.
 *
 * @param base       PWM peripheral base address
 * @param subModule  PWM submodule to configure
 * @param pwmChannel Channel to configure
 * @param mode       Signal to output when a FORCE_OUT is triggered
 */
void PWM_SetupForceSignal(PWM_Type *base,
                          pwm_submodule_t subModule,
                          pwm_channels_t pwmChannel,
                          pwm_force_signal_t mode);

/*!
 * @name Interrupts Interface
 * @{
 */

/*!
 * @brief Enables the selected PWM interrupts
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 * @param mask      The interrupts to enable. This is a logical OR of members of the
 *                  enumeration ::pwm_interrupt_enable_t
 */
void PWM_EnableInterrupts(PWM_Type *base, pwm_submodule_t subModule, uint32_t mask);

/*!
 * @brief Disables the selected PWM interrupts
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 * @param mask      The interrupts to enable. This is a logical OR of members of the
 *                  enumeration ::pwm_interrupt_enable_t
 */
void PWM_DisableInterrupts(PWM_Type *base, pwm_submodule_t subModule, uint32_t mask);

/*!
 * @brief Gets the enabled PWM interrupts
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::pwm_interrupt_enable_t
 */
uint32_t PWM_GetEnabledInterrupts(PWM_Type *base, pwm_submodule_t subModule);

/*! @}*/

/*!
 * @name DMA Interface
 * @{
 */

/*!
 * @brief Capture DMA Enable Source Select.
 *
 * @param base                  PWM peripheral base address
 * @param subModule             PWM submodule to configure
 * @param pwm_watermark_control PWM FIFO watermark and control
 */
static inline void PWM_DMAFIFOWatermarkControl(PWM_Type *base,
                                               pwm_submodule_t subModule,
                                               pwm_watermark_control_t pwm_watermark_control)
{
    uint16_t reg = base->SM[subModule].DMAEN;
    if (pwm_watermark_control == kPWM_FIFOWatermarksOR)
    {
        reg &= ~((uint16_t)PWM_DMAEN_FAND_MASK);
    }
    else
    {
        reg |= ((uint16_t)PWM_DMAEN_FAND_MASK);
    }
    base->SM[subModule].DMAEN = reg;
}

/*!
 * @brief Capture DMA Enable Source Select.
 *
 * @param base                  PWM peripheral base address
 * @param subModule             PWM submodule to configure
 * @param pwm_dma_source_select PWM capture DMA enable source select
 */
static inline void PWM_DMACaptureSourceSelect(PWM_Type *base,
                                              pwm_submodule_t subModule,
                                              pwm_dma_source_select_t pwm_dma_source_select)
{
    uint16_t reg = base->SM[subModule].DMAEN;

    reg &= ~((uint16_t)PWM_DMAEN_CAPTDE_MASK);
    reg |= (((uint16_t)pwm_dma_source_select << (uint16_t)PWM_DMAEN_CAPTDE_SHIFT) & (uint16_t)PWM_DMAEN_CAPTDE_MASK);

    base->SM[subModule].DMAEN = reg;
}

/*!
 * @brief Enables or disables the selected PWM DMA Capture read request.
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 * @param mask      The DMA to enable or disable. This is a logical OR of members of the
 *                  enumeration ::pwm_dma_enable_t
 * @param activate  true: Enable DMA read request; false: Disable DMA read request
 */
static inline void PWM_EnableDMACapture(PWM_Type *base, pwm_submodule_t subModule, uint16_t mask, bool activate)
{
    uint16_t reg = base->SM[subModule].DMAEN;
    if (activate)
    {
        reg |= (uint16_t)(mask);
    }
    else
    {
        reg &= ~((uint16_t)(mask));
    }
    base->SM[subModule].DMAEN = reg;
}

/*!
 * @brief Enables or disables the PWM DMA write request.
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 * @param activate  true: Enable DMA write request; false: Disable DMA write request
 */
static inline void PWM_EnableDMAWrite(PWM_Type *base, pwm_submodule_t subModule, bool activate)
{
    uint16_t reg = base->SM[subModule].DMAEN;
    if (activate)
    {
        reg |= ((uint16_t)PWM_DMAEN_VALDE_MASK);
    }
    else
    {
        reg &= ~((uint16_t)PWM_DMAEN_VALDE_MASK);
    }
    base->SM[subModule].DMAEN = reg;
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the PWM status flags
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::pwm_status_flags_t
 */
uint32_t PWM_GetStatusFlags(PWM_Type *base, pwm_submodule_t subModule);

/*!
 * @brief Clears the PWM status flags
 *
 * @param base      PWM peripheral base address
 * @param subModule PWM submodule to configure
 * @param mask      The status flags to clear. This is a logical OR of members of the
 *                  enumeration ::pwm_status_flags_t
 */
void PWM_ClearStatusFlags(PWM_Type *base, pwm_submodule_t subModule, uint32_t mask);

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the PWM counter for a single or multiple submodules.
 *
 * Sets the Run bit which enables the clocks to the PWM submodule. This function can start multiple
 * submodules at the same time.
 *
 * @param base              PWM peripheral base address
 * @param subModulesToStart PWM submodules to start. This is a logical OR of members of the
 *                          enumeration ::pwm_module_control_t
 */
static inline void PWM_StartTimer(PWM_Type *base, uint8_t subModulesToStart)
{
    base->MCTRL |= PWM_MCTRL_RUN(subModulesToStart);
}

/*!
 * @brief Stops the PWM counter for a single or multiple submodules.
 *
 * Clears the Run bit which resets the submodule's counter. This function can stop multiple
 * submodules at the same time.
 *
 * @param base             PWM peripheral base address
 * @param subModulesToStop PWM submodules to stop. This is a logical OR of members of the
 *                         enumeration ::pwm_module_control_t
 */
static inline void PWM_StopTimer(PWM_Type *base, uint8_t subModulesToStop)
{
    base->MCTRL &= ~(PWM_MCTRL_RUN(subModulesToStop));
}

/*! @}*/

/*!
 * @brief Set the PWM VALx registers.
 *
 * This function allows the user to write value into VAL registers directly. And it will destroying the PWM clock period
 * set by the PWM_SetupPwm()/PWM_SetupPwmPhaseShift() functions.
 * Due to VALx registers are bufferd, the new value will not active uless call PWM_SetPwmLdok() and the reload point is
 * reached.
 *
 * @param base          PWM peripheral base address
 * @param subModule     PWM submodule to configure
 * @param valueRegister VALx register that will be writen new value
 * @param value         Value that will been write into VALx register
 */
static inline void PWM_SetVALxValue(PWM_Type *base,
                                    pwm_submodule_t subModule,
                                    pwm_value_register_t valueRegister,
                                    uint16_t value)
{
    switch (valueRegister)
    {
        case kPWM_ValueRegister_0:
            base->SM[subModule].VAL0 = value;
            break;
        case kPWM_ValueRegister_1:
            base->SM[subModule].VAL1 = value;
            break;
        case kPWM_ValueRegister_2:
            base->SM[subModule].VAL2 = value;
            break;
        case kPWM_ValueRegister_3:
            base->SM[subModule].VAL3 = value;
            break;
        case kPWM_ValueRegister_4:
            base->SM[subModule].VAL4 = value;
            break;
        case kPWM_ValueRegister_5:
            base->SM[subModule].VAL5 = value;
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * @brief Get the PWM VALx registers.
 *
 * @param base          PWM peripheral base address
 * @param subModule     PWM submodule to configure
 * @param valueRegister VALx register that will be read value
 * @return The VALx register value
 */
static inline uint16_t PWM_GetVALxValue(PWM_Type *base, pwm_submodule_t subModule, pwm_value_register_t valueRegister)
{
    uint16_t temp = 0U;

    switch (valueRegister)
    {
        case kPWM_ValueRegister_0:
            temp = base->SM[subModule].VAL0;
            break;
        case kPWM_ValueRegister_1:
            temp = base->SM[subModule].VAL1;
            break;
        case kPWM_ValueRegister_2:
            temp = base->SM[subModule].VAL2;
            break;
        case kPWM_ValueRegister_3:
            temp = base->SM[subModule].VAL3;
            break;
        case kPWM_ValueRegister_4:
            temp = base->SM[subModule].VAL4;
            break;
        case kPWM_ValueRegister_5:
            temp = base->SM[subModule].VAL5;
            break;
        default:
            assert(false);
            break;
    }

    return temp;
}

/*!
 * @brief Enables or disables the PWM output trigger.
 *
 * This function allows the user to enable or disable the PWM trigger. The PWM has 2 triggers. Trigger 0
 * is activated when the counter matches VAL 0, VAL 2, or VAL 4 register. Trigger 1 is activated
 * when the counter matches VAL 1, VAL 3, or VAL 5 register.
 *
 * @param base          PWM peripheral base address
 * @param subModule     PWM submodule to configure
 * @param valueRegister Value register that will activate the trigger
 * @param activate      true: Enable the trigger; false: Disable the trigger
 */
static inline void PWM_OutputTriggerEnable(PWM_Type *base,
                                           pwm_submodule_t subModule,
                                           pwm_value_register_t valueRegister,
                                           bool activate)
{
    if (activate)
    {
        base->SM[subModule].TCTRL |= ((uint16_t)1U << (uint16_t)valueRegister);
    }
    else
    {
        base->SM[subModule].TCTRL &= ~((uint16_t)1U << (uint16_t)valueRegister);
    }
}

/*!
 * @brief Enables the PWM output trigger.
 *
 * This function allows the user to enable one or more (VAL0-5) PWM trigger.
 *
 * @param base              PWM peripheral base address
 * @param subModule         PWM submodule to configure
 * @param valueRegisterMask Value register mask that will activate one or more (VAL0-5) trigger
 *                          enumeration ::_pwm_value_register_mask
 */
static inline void PWM_ActivateOutputTrigger(PWM_Type *base, pwm_submodule_t subModule, uint16_t valueRegisterMask)
{
    base->SM[subModule].TCTRL |= (PWM_TCTRL_OUT_TRIG_EN_MASK & (valueRegisterMask));
}

/*!
 * @brief Disables the PWM output trigger.
 *
 * This function allows the user to disables one or more (VAL0-5) PWM trigger.
 *
 * @param base              PWM peripheral base address
 * @param subModule         PWM submodule to configure
 * @param valueRegisterMask Value register mask that will Deactivate one or more (VAL0-5) trigger
 *                          enumeration ::_pwm_value_register_mask
 */
static inline void PWM_DeactivateOutputTrigger(PWM_Type *base, pwm_submodule_t subModule, uint16_t valueRegisterMask)
{
    base->SM[subModule].TCTRL &= ~(PWM_TCTRL_OUT_TRIG_EN_MASK & (valueRegisterMask));
}

/*!
 * @brief Sets the software control output for a pin to high or low.
 *
 * The user specifies which channel to modify by supplying the submodule number and whether
 * to modify PWM A or PWM B within that submodule.
 *
 * @param base       PWM peripheral base address
 * @param subModule  PWM submodule to configure
 * @param pwmChannel Channel to configure
 * @param value      true: Supply a logic 1, false: Supply a logic 0.
 */
static inline void PWM_SetupSwCtrlOut(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmChannel, bool value)
{
    if (value)
    {
        base->SWCOUT |=
            ((uint16_t)1U << (((uint16_t)subModule * (uint16_t)PWM_SUBMODULE_SWCONTROL_WIDTH) + (uint16_t)pwmChannel));
    }
    else
    {
        base->SWCOUT &=
            ~((uint16_t)1U << (((uint16_t)subModule * (uint16_t)PWM_SUBMODULE_SWCONTROL_WIDTH) + (uint16_t)pwmChannel));
    }
}

/*!
 * @brief Sets or clears the PWM LDOK bit on a single or multiple submodules
 *
 * Set LDOK bit to load buffered values into CTRL[PRSC] and the INIT, FRACVAL and VAL registers. The
 * values are loaded immediately if kPWM_ReloadImmediate option was choosen during config. Else the
 * values are loaded at the next PWM reload point.
 * This function can issue the load command to multiple submodules at the same time.
 *
 * @param base               PWM peripheral base address
 * @param subModulesToUpdate PWM submodules to update with buffered values. This is a logical OR of
 *                           members of the enumeration ::pwm_module_control_t
 * @param value              true: Set LDOK bit for the submodule list; false: Clear LDOK bit
 */
static inline void PWM_SetPwmLdok(PWM_Type *base, uint8_t subModulesToUpdate, bool value)
{
    if (value)
    {
        base->MCTRL |= PWM_MCTRL_LDOK(subModulesToUpdate);
    }
    else
    {
        base->MCTRL |= PWM_MCTRL_CLDOK(subModulesToUpdate);
    }
}

/*!
 * @brief Set PWM output fault status
 *
 * These bits determine the fault state for the PWM_A output in fault conditions
 * and STOP mode. It may also define the output state in WAIT and DEBUG modes
 * depending on the settings of CTRL2[WAITEN] and CTRL2[DBGEN].
 * This function can update PWM output fault status.
 *
 * @param base       PWM peripheral base address
 * @param subModule  PWM submodule to configure
 * @param pwmChannel Channel to configure
 * @param faultState PWM output fault status
 */
static inline void PWM_SetPwmFaultState(PWM_Type *base,
                                        pwm_submodule_t subModule,
                                        pwm_channels_t pwmChannel,
                                        pwm_fault_state_t faultState)
{
    uint16_t reg = base->SM[subModule].OCTRL;
    switch (pwmChannel)
    {
        case kPWM_PwmA:
            reg &= ~((uint16_t)PWM_OCTRL_PWMAFS_MASK);
            reg |= (((uint16_t)faultState << (uint16_t)PWM_OCTRL_PWMAFS_SHIFT) & (uint16_t)PWM_OCTRL_PWMAFS_MASK);
            break;
        case kPWM_PwmB:
            reg &= ~((uint16_t)PWM_OCTRL_PWMBFS_MASK);
            reg |= (((uint16_t)faultState << (uint16_t)PWM_OCTRL_PWMBFS_SHIFT) & (uint16_t)PWM_OCTRL_PWMBFS_MASK);
            break;
        case kPWM_PwmX:
            reg &= ~((uint16_t)PWM_OCTRL_PWMXFS_MASK);
            reg |= (((uint16_t)faultState << (uint16_t)PWM_OCTRL_PWMXFS_SHIFT) & (uint16_t)PWM_OCTRL_PWMXFS_MASK);
            break;
        default:
            assert(false);
            break;
    }
    base->SM[subModule].OCTRL = reg;
}

/*!
 * @brief Set PWM fault disable mapping
 *
 * Each of the four bits of this read/write field is one-to-one associated
 * with the four FAULTx inputs of fault channel 0/1. The PWM output will be turned
 * off if there is a logic 1 on an FAULTx input and a 1 in the corresponding
 * bit of this field. A reset sets all bits in this field.
 *
 * @param base               PWM peripheral base address
 * @param subModule          PWM submodule to configure
 * @param pwmChannel         PWM channel to configure
 * @param pwm_fault_channels PWM fault channel to configure
 * @param value              Fault disable mapping mask value
 *                           enumeration ::pwm_fault_disable_t
 */
static inline void PWM_SetupFaultDisableMap(PWM_Type *base,
                                            pwm_submodule_t subModule,
                                            pwm_channels_t pwmChannel,
                                            pwm_fault_channels_t pwm_fault_channels,
                                            uint16_t value)
{
    uint16_t reg = base->SM[subModule].DISMAP[pwm_fault_channels];
    switch (pwmChannel)
    {
        case kPWM_PwmA:
            reg &= ~((uint16_t)PWM_DISMAP_DIS0A_MASK);
            reg |= (((uint16_t)(value) << (uint16_t)PWM_DISMAP_DIS0A_SHIFT) & (uint16_t)PWM_DISMAP_DIS0A_MASK);
            break;
        case kPWM_PwmB:
            reg &= ~((uint16_t)PWM_DISMAP_DIS0B_MASK);
            reg |= (((uint16_t)(value) << (uint16_t)PWM_DISMAP_DIS0B_SHIFT) & (uint16_t)PWM_DISMAP_DIS0B_MASK);
            break;
        case kPWM_PwmX:
            reg &= ~((uint16_t)PWM_DISMAP_DIS0X_MASK);
            reg |= (((uint16_t)(value) << (uint16_t)PWM_DISMAP_DIS0X_SHIFT) & (uint16_t)PWM_DISMAP_DIS0X_MASK);
            break;
        default:
            assert(false);
            break;
    }
    base->SM[subModule].DISMAP[pwm_fault_channels] = reg;
}

/*!
 * @brief Set PWM output enable
 *
 * This feature allows the user to enable the PWM Output.
 *
 * @param base               PWM peripheral base address
 * @param pwmChannel         PWM channel to configure
 * @param subModule          PWM submodule to configure
 */
static inline void PWM_OutputEnable(PWM_Type *base, pwm_channels_t pwmChannel, pwm_submodule_t subModule)
{
    /* Set PWM output */
    switch (pwmChannel)
    {
        case kPWM_PwmA:
            base->OUTEN |= ((uint16_t)1U << ((uint16_t)PWM_OUTEN_PWMA_EN_SHIFT + (uint16_t)subModule));
            break;
        case kPWM_PwmB:
            base->OUTEN |= ((uint16_t)1U << ((uint16_t)PWM_OUTEN_PWMB_EN_SHIFT + (uint16_t)subModule));
            break;
        case kPWM_PwmX:
            base->OUTEN |= ((uint16_t)1U << ((uint16_t)PWM_OUTEN_PWMX_EN_SHIFT + (uint16_t)subModule));
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * @brief Set PWM output disable
 *
 *This feature allows the user to disable the PWM output.
 *
 * @param base               PWM peripheral base address
 * @param pwmChannel         PWM channel to configure
 * @param subModule          PWM submodule to configure
 */
static inline void PWM_OutputDisable(PWM_Type *base, pwm_channels_t pwmChannel, pwm_submodule_t subModule)
{
    switch (pwmChannel)
    {
        case kPWM_PwmA:
            base->OUTEN &= ~((uint16_t)1U << ((uint16_t)PWM_OUTEN_PWMA_EN_SHIFT + (uint16_t)subModule));
            break;
        case kPWM_PwmB:
            base->OUTEN &= ~((uint16_t)1U << ((uint16_t)PWM_OUTEN_PWMB_EN_SHIFT + (uint16_t)subModule));
            break;
        case kPWM_PwmX:
            base->OUTEN &= ~((uint16_t)1U << ((uint16_t)PWM_OUTEN_PWMX_EN_SHIFT + (uint16_t)subModule));
            break;
        default:
            assert(false);
            break;
    }
}

/*!
 * @brief Get the dutycycle value.
 *
 * @param base        PWM peripheral base address
 * @param subModule   PWM submodule to configure
 * @param pwmChannel  PWM channel to configure
 *
 * @return Current channel dutycycle value.
 */
uint8_t PWM_GetPwmChannelState(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmChannel);

/*!
 * @brief Set PWM output in idle status (high or low).
 *
 * @note This API should call after PWM_SetupPwm() APIs, and PWMX submodule is not supported.
 *
 * @param base               PWM peripheral base address
 * @param pwmChannel         PWM channel to configure
 * @param subModule          PWM submodule to configure
 * @param idleStatus         True: PWM output is high in idle status; false: PWM output is low in idle status.
 *
 * @return kStatus_Fail if there was error setting up the signal; kStatus_Success if set output idle success
 */
status_t PWM_SetOutputToIdle(PWM_Type *base, pwm_channels_t pwmChannel, pwm_submodule_t subModule, bool idleStatus);

/*!
 * @brief Set the pwm submodule prescaler.
 *
 * @param base               PWM peripheral base address
 * @param subModule          PWM submodule to configure
 * @param prescaler          Set prescaler value
 */
void PWM_SetClockMode(PWM_Type *base, pwm_submodule_t subModule, pwm_clock_prescale_t prescaler);

/*!
 * @brief This function enables-disables the forcing of the output of a given eFlexPwm channel to logic 0.
 *
 * @param base               PWM peripheral base address
 * @param pwmChannel         PWM channel to configure
 * @param subModule          PWM submodule to configure
 * @param forcetozero        True: Enable the pwm force output to zero; False: Disable the pwm output resumes normal
 *                           function.
 */
void PWM_SetPwmForceOutputToZero(PWM_Type *base,
                                 pwm_submodule_t subModule,
                                 pwm_channels_t pwmChannel,
                                 bool forcetozero);

/*!
 * @brief This function set the output state of the PWM pin as requested for the current cycle.
 *
 * @param base               PWM peripheral base address
 * @param subModule          PWM submodule to configure
 * @param pwmChannel         PWM channel to configure
 * @param outputstate        Set pwm output state, see @ref pwm_output_state_t.
 */
void PWM_SetChannelOutput(PWM_Type *base,
                          pwm_submodule_t subModule,
                          pwm_channels_t pwmChannel,
                          pwm_output_state_t outputstate);

#if defined(FSL_FEATURE_PWM_HAS_PHASE_DELAY) && FSL_FEATURE_PWM_HAS_PHASE_DELAY
/*!
 * @brief This function set the phase delay from the master sync signal of submodule 0.
 *
 * @param base               PWM peripheral base address
 * @param subModule          PWM submodule to configure
 * @param pwmChannel         PWM channel to configure
 * @param delayCycles        Number of cycles delayed from submodule 0.
 *
 * @return kStatus_Fail if the number of delay cycles is set larger than the period defined in submodule 0;
 *        kStatus_Success if set phase delay success
 */
status_t PWM_SetPhaseDelay(PWM_Type *base, pwm_channels_t pwmChannel, pwm_submodule_t subModule, uint16_t delayCycles);
#endif

#if defined(FSL_FEATURE_PWM_HAS_INPUT_FILTER_CAPTURE) && FSL_FEATURE_PWM_HAS_INPUT_FILTER_CAPTURE
/*!
 * @brief This function set the number of consecutive samples that must agree prior to the input filter.
 *
 * @param base               PWM peripheral base address
 * @param subModule          PWM submodule to configure
 * @param pwmChannel         PWM channel to configure
 * @param filterSampleCount  Number of consecutive samples.
 */
static inline void PWM_SetFilterSampleCount(PWM_Type *base,
                                             pwm_channels_t pwmChannel,
                                             pwm_submodule_t subModule,
                                             uint8_t filterSampleCount)
{
    switch(pwmChannel)
    {
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA
        case kPWM_PwmA:
            base->SM[subModule].CAPTFILTA &= ~((uint16_t)PWM_CAPTFILTA_CAPTA_FILT_CNT_MASK);
            base->SM[subModule].CAPTFILTA |= PWM_CAPTFILTA_CAPTA_FILT_CNT(filterSampleCount);
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB
        case kPWM_PwmB:
            base->SM[subModule].CAPTFILTB &= ~((uint16_t)PWM_CAPTFILTB_CAPTB_FILT_CNT_MASK);
            base->SM[subModule].CAPTFILTB |= PWM_CAPTFILTB_CAPTB_FILT_CNT(filterSampleCount);
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX
        case kPWM_PwmX:
            base->SM[subModule].CAPTFILTX &= ~((uint16_t)PWM_CAPTFILTX_CAPTX_FILT_CNT_MASK);
            base->SM[subModule].CAPTFILTX |= PWM_CAPTFILTX_CAPTX_FILT_CNT(filterSampleCount);
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX */
        default:
            assert(false);
            break;
    }
}

/*!
 * @brief This function set the sampling period of the fault pin input filter.
 *
 * @param base                 PWM peripheral base address
 * @param subModule            PWM submodule to configure
 * @param pwmChannel           PWM channel to configure
 * @param filterSamplePeriod   Sampling period of input filter.
 */
static inline void PWM_SetFilterSamplePeriod(PWM_Type *base,
                                             pwm_channels_t pwmChannel,
                                             pwm_submodule_t subModule,
                                             uint8_t filterSamplePeriod)
{
    switch(pwmChannel)
    {
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA
        case kPWM_PwmA:
            base->SM[subModule].CAPTFILTA &= ~((uint16_t)PWM_CAPTFILTA_CAPTA_FILT_PER_MASK);
            base->SM[subModule].CAPTFILTA |= PWM_CAPTFILTA_CAPTA_FILT_PER(filterSamplePeriod);
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB
        case kPWM_PwmB:
            base->SM[subModule].CAPTFILTB &= ~((uint16_t)PWM_CAPTFILTB_CAPTB_FILT_PER_MASK);
            base->SM[subModule].CAPTFILTB |= PWM_CAPTFILTB_CAPTB_FILT_PER(filterSamplePeriod);
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB */
#if defined(FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX) && FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX
        case kPWM_PwmX:
            base->SM[subModule].CAPTFILTX &= ~((uint16_t)PWM_CAPTFILTX_CAPTX_FILT_PER_MASK);
            base->SM[subModule].CAPTFILTX |= PWM_CAPTFILTX_CAPTX_FILT_PER(filterSamplePeriod);
            break;
#endif /* FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX */
        default:
            assert(false);
            break;
    }
}
#endif

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_PWM_H_ */
