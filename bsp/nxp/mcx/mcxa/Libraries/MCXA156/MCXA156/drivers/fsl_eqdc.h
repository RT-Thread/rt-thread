/*
 * Copyright 2022, 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_EQDC_H_
#define FSL_EQDC_H_

#include "fsl_common.h"

/*!
 * @addtogroup eqdc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FSL_EQDC_DRIVER_VERSION (MAKE_VERSION(2, 3, 0))

/*! @brief W1C bits in EQDC CTRL registers. */
#define EQDC_CTRL_W1C_FLAGS (EQDC_CTRL_HIRQ_MASK | EQDC_CTRL_XIRQ_MASK | EQDC_CTRL_WDIRQ_MASK)

/*! @brief W1C bits in EQDC INTCTRL registers. */
#define EQDC_INTCTRL_W1C_FLAGS                                                                                 \
    (EQDC_INTCTRL_SABIRQ_MASK | EQDC_INTCTRL_DIRIRQ_MASK | EQDC_INTCTRL_RUIRQ_MASK | EQDC_INTCTRL_ROIRQ_MASK | \
     EQDC_INTCTRL_CMP0IRQ_MASK | EQDC_INTCTRL_CMP1IRQ_MASK | EQDC_INTCTRL_CMP2IRQ_MASK | EQDC_INTCTRL_CMP3IRQ_MASK)

/*! @brief Interrupt enable bits in EQDC CTRL registers. */
#define EQDC_CTRL_INT_EN (EQDC_CTRL_HIE_MASK | EQDC_CTRL_XIE_MASK | EQDC_CTRL_WDIE_MASK)

/*! @brief Interrupt enable bits in EQDC INTCTRL registers. */
#if (defined(FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT) && FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT)
#define EQDC_INTCTRL_INT_EN                                                                                \
    (EQDC_INTCTRL_SABIE_MASK | EQDC_INTCTRL_DIRIE_MASK | EQDC_INTCTRL_RUIE_MASK | EQDC_INTCTRL_ROIE_MASK)
#else
#define EQDC_INTCTRL_INT_EN                                                                                \
    (EQDC_INTCTRL_SABIE_MASK | EQDC_INTCTRL_DIRIE_MASK | EQDC_INTCTRL_RUIE_MASK | EQDC_INTCTRL_ROIE_MASK | \
     EQDC_INTCTRL_CMP0IE_MASK | EQDC_INTCTRL_CMP1IE_MASK | EQDC_INTCTRL_CMP2IE_MASK | EQDC_INTCTRL_CMP3IE_MASK)
#endif

/*! @brief Interrupt flag bits in EQDC CTRL registers. */
#define EQDC_CTRL_INT_FLAGS (EQDC_CTRL_HIRQ_MASK | EQDC_CTRL_XIRQ_MASK | EQDC_CTRL_WDIRQ_MASK)

/*! @brief Interrupt flag bits in EQDC INTCTRL registers. */
#define EQDC_INTCTRL_INT_FLAGS                                                                                 \
    (EQDC_INTCTRL_SABIRQ_MASK | EQDC_INTCTRL_DIRIRQ_MASK | EQDC_INTCTRL_RUIRQ_MASK | EQDC_INTCTRL_ROIRQ_MASK | \
     EQDC_INTCTRL_CMP0IRQ_MASK | EQDC_INTCTRL_CMP1IRQ_MASK | EQDC_INTCTRL_CMP2IRQ_MASK | EQDC_INTCTRL_CMP3IRQ_MASK)

#if !(defined(FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT) && FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT)
#define kEQDC_PositionCompare0InerruptEnable kEQDC_PositionCompare0InterruptEnable
#define kEQDC_PositionCompare1InerruptEnable kEQDC_PositionCompare1InterruptEnable
#define kEQDC_PositionCompare2InerruptEnable kEQDC_PositionCompare2InterruptEnable
#define kEQDC_PositionCompare3InerruptEnable kEQDC_PositionCompare3InterruptEnable
#endif

/*!
 * @brief EQDC status flags, these flags indicate the counter's events.
 * @anchor _eqdc_status_flags
 */
enum _eqdc_status_flags
{
    kEQDC_HomeEnableTransitionFlag = EQDC_CTRL_HIRQ_MASK,  /*!< HOME/ENABLE signal transition occured. */
    kEQDC_IndexPresetPulseFlag     = EQDC_CTRL_XIRQ_MASK,  /*!< INDEX/PRESET  pulse occured. */
    kEQDC_WatchdogTimeoutFlag      = EQDC_CTRL_WDIRQ_MASK, /*!< Watchdog timeout occured. */

    kEQDC_SimultPhaseChangeFlag = (uint32_t)EQDC_INTCTRL_SABIRQ_MASK
                                  << 16U, /*!< Simultaneous change of PHASEA and PHASEB occured. */
    kEQDC_CountDirectionChangeFlag = (uint32_t)EQDC_INTCTRL_DIRIRQ_MASK
                                     << 16U, /*!< Count direction change interrupt enable. */
    kEQDC_PositionRollOverFlag = (uint32_t)EQDC_INTCTRL_ROIRQ_MASK
                                 << 16U, /*!< Position counter rolls over from 0xFFFFFFFF to 0, or
                                         from MOD value to INIT value. */
    kEQDC_PositionRollUnderFlag = (uint32_t)EQDC_INTCTRL_RUIRQ_MASK
                                  << 16U, /*!< Position register roll under from 0 to 0xFFFFFFFF, or
                                              from INIT value to MOD value. */

    kEQDC_PositionCompare0Flag = (uint32_t)EQDC_INTCTRL_CMP0IRQ_MASK
                                 << 16U, /*!< Position counter match the COMP0 value. */
    kEQDC_PositionCompare1Flag = (uint32_t)EQDC_INTCTRL_CMP1IRQ_MASK
                                 << 16U, /*!< Position counter match the COMP1 value. */
    kEQDC_PositionCompare2Flag = (uint32_t)EQDC_INTCTRL_CMP2IRQ_MASK
                                 << 16U, /*!< Position counter match the COMP2 value. */
    kEQDC_PositionCompare3Flag = (uint32_t)EQDC_INTCTRL_CMP3IRQ_MASK
                                 << 16U, /*!< Position counter match the COMP3 value. */

    kEQDC_StatusAllFlags = kEQDC_HomeEnableTransitionFlag | kEQDC_IndexPresetPulseFlag | kEQDC_WatchdogTimeoutFlag |
                           kEQDC_SimultPhaseChangeFlag | kEQDC_PositionRollOverFlag | kEQDC_PositionRollUnderFlag |
                           kEQDC_PositionCompare0Flag | kEQDC_PositionCompare1Flag | kEQDC_PositionCompare2Flag |
                           kEQDC_PositionCompare3Flag
};

/*!
 * @brief Signal status, these flags indicate the raw and filtered input signal status.
 * @anchor _eqdc_signal_status
 */
enum _eqdc_signal_status
{
    kEQDC_SignalStatusRawHomeEnable       = EQDC_IMR_HOME_ENABLE_MASK,  /*!< Raw HOME/ENABLE input. */
    kEQDC_SignalStatusRawIndexPreset      = EQDC_IMR_INDEX_PRESET_MASK, /*!< Raw INDEX/PRESET input. */
    kEQDC_SignalStatusRawPhaseB           = EQDC_IMR_PHB_MASK,          /*!< Raw PHASEB input. */
    kEQDC_SignalStatusRawPhaseA           = EQDC_IMR_PHA_MASK,          /*!< Raw PHASEA input. */
    kEQDC_SignalStatusFilteredHomeEnable  = EQDC_IMR_FHOM_ENA_MASK,     /*!< The filtered HOME/ENABLE input. */
    kEQDC_SignalStatusFilteredIndexPreset = EQDC_IMR_FIND_PRE_MASK,     /*!< The filtered INDEX/PRESET input. */
    kEQDC_SignalStatusFilteredPhaseB      = EQDC_IMR_FPHB_MASK,         /*!< The filtered PHASEB input. */
    kEQDC_SignalStatusFilteredPhaseA      = EQDC_IMR_FPHA_MASK,         /*!< The filtered PHASEA input. */

    kEQDC_SignalStatusPositionCompare0Flag   = EQDC_IMR_CMPF0_MASK, /*!< Position Compare 0 Flag Output. */
    kEQDC_SignalStatusPositionCompare1Flag   = EQDC_IMR_CMP1F_MASK, /*!< Position Compare 1 Flag Output. */
    kEQDC_SignalStatusPositionCompare2Flag   = EQDC_IMR_CMP2F_MASK, /*!< Position Compare 2 Flag Output. */
    kEQDC_SignalStatusPositionCompare3Flag   = EQDC_IMR_CMP3F_MASK, /*!< Position Compare 3 Flag Output. */
    kEQDC_SignalStatusCountDirectionFlagHold = EQDC_IMR_DIRH_MASK,  /*!< Count Direction Flag Hold. */
    kEQDC_SignalStatusCountDirectionFlag     = EQDC_IMR_DIR_MASK,   /*!< Count Direction Flag Output. */

    kEQDC_SignalStatusAllFlags = kEQDC_SignalStatusRawHomeEnable | kEQDC_SignalStatusRawIndexPreset |
                                 kEQDC_SignalStatusRawPhaseB | kEQDC_SignalStatusRawPhaseA |
                                 kEQDC_SignalStatusFilteredHomeEnable | kEQDC_SignalStatusFilteredIndexPreset |
                                 kEQDC_SignalStatusFilteredPhaseB | kEQDC_SignalStatusFilteredPhaseA |
                                 kEQDC_SignalStatusPositionCompare0Flag | kEQDC_SignalStatusPositionCompare1Flag |
                                 kEQDC_SignalStatusPositionCompare2Flag | kEQDC_SignalStatusPositionCompare3Flag |
                                 kEQDC_SignalStatusCountDirectionFlagHold | kEQDC_SignalStatusCountDirectionFlag
};

/*!
 * @brief Interrupt enable/disable mask.
 * @anchor _eqdc_interrupt_enable
 */
enum _eqdc_interrupt_enable
{
    kEQDC_HomeEnableTransitionInterruptEnable =
        EQDC_CTRL_HIE_MASK,                                      /*!< HOME/ENABLE signal transition interrupt enable. */
    kEQDC_IndexPresetPulseInterruptEnable = EQDC_CTRL_XIE_MASK,  /*!< INDEX/PRESET pulse interrupt enable. */
    kEQDC_WatchdogTimeoutInterruptEnable  = EQDC_CTRL_WDIE_MASK, /*!< Watchdog timeout interrupt enable. */

    kEQDC_SimultPhaseChangeInterruptEnable = (uint32_t)EQDC_INTCTRL_SABIE_MASK
                                             << 16U, /*!< Simultaneous PHASEA and PHASEB change interrupt enable. */
    kEQDC_CountDirectionChangeInterruptEnable = (uint32_t)EQDC_INTCTRL_DIRIE_MASK
                                             << 16U, /*!< Count direction change interrupt enable. */
    kEQDC_PositionRollOverInterruptEnable = (uint32_t)EQDC_INTCTRL_ROIE_MASK << 16U, /*!< Roll-over interrupt enable. */
    kEQDC_PositionRollUnderInterruptEnable = (uint32_t)EQDC_INTCTRL_RUIE_MASK
                                             << 16U, /*!< Roll-under interrupt enable. */

#if !(defined(FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT) && FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT)
    kEQDC_PositionCompare0InterruptEnable = (uint32_t)EQDC_INTCTRL_CMP0IE_MASK
                                           << 16U, /*!< Position compare 0 interrupt enable. */
    kEQDC_PositionCompare1InterruptEnable = (uint32_t)EQDC_INTCTRL_CMP1IE_MASK
                                           << 16U, /*!< Position compare 1 interrupt enable. */
    kEQDC_PositionCompare2InterruptEnable = (uint32_t)EQDC_INTCTRL_CMP2IE_MASK
                                           << 16U, /*!< Position compare 2 interrupt enable. */
    kEQDC_PositionCompare3InterruptEnable = (uint32_t)EQDC_INTCTRL_CMP3IE_MASK
                                           << 16U, /*!< Position compare 3 interrupt enable. */
#endif

#if (defined(FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT) && FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT)
    kEQDC_AllInterruptEnable = kEQDC_HomeEnableTransitionInterruptEnable | kEQDC_IndexPresetPulseInterruptEnable |
                               kEQDC_WatchdogTimeoutInterruptEnable | kEQDC_SimultPhaseChangeInterruptEnable |
                               kEQDC_CountDirectionChangeInterruptEnable | kEQDC_PositionRollOverInterruptEnable |
                               kEQDC_PositionRollUnderInterruptEnable
#else
    kEQDC_AllInterruptEnable = kEQDC_HomeEnableTransitionInterruptEnable | kEQDC_IndexPresetPulseInterruptEnable |
                               kEQDC_WatchdogTimeoutInterruptEnable | kEQDC_SimultPhaseChangeInterruptEnable |
                               kEQDC_CountDirectionChangeInterruptEnable | kEQDC_PositionRollOverInterruptEnable |
                               kEQDC_PositionRollUnderInterruptEnable | kEQDC_PositionCompare0InterruptEnable |
                               kEQDC_PositionCompare1InterruptEnable | kEQDC_PositionCompare2InterruptEnable |
                               kEQDC_PositionCompare3InterruptEnable
#endif
};

/*!
 * @brief Define HOME/ENABLE signal's trigger mode.
 */
typedef enum _eqdc_home_enable_init_pos_counter_mode
{
    /*! Don't use HOME/ENABLE signal to initialize the position counter. */
    kEQDC_HomeInitPosCounterDisabled = 0U,

    /*! Use positive going edge to trigger initialization of position counters. */
    kEQDC_HomeInitPosCounterOnRisingEdge = EQDC_CTRL_HIP_MASK,

    /*! Use negative going edge to trigger initialization of position counters. */
    kEQDC_HomeInitPosCounterOnFallingEdge = EQDC_CTRL_HIP_MASK | EQDC_CTRL_HNE_MASK,
} eqdc_home_enable_init_pos_counter_mode_t;

/*!
 * @brief Define INDEX/PRESET signal's trigger mode.
 */
typedef enum _eqdc_index_preset_init_pos_counter_mode
{
    /*! INDEX/PRESET pulse does not initialize the position counter. */
    kEQDC_IndexInitPosCounterDisabled = 0U,

    /*! Use INDEX/PRESET pulse rising edge to initialize position counter. */
    kEQDC_IndexInitPosCounterOnRisingEdge = EQDC_CTRL_XIP_MASK,

    /*! Use INDEX/PRESET pulse falling edge to initialize position counter. */
    kEQDC_IndexInitPosCounterOnFallingEdge = EQDC_CTRL_XIP_MASK | EQDC_CTRL_XNE_MASK,
} eqdc_index_preset_init_pos_counter_mode_t;

/*!
 * @brief Define type for decoder opertion mode.
 *
 * The Quadrature Decoder operates in following 4 operation modes:
 *   1.Quadrature Decode(QDC) Operation Mode (CTRL[PH1] = 0,CTRL2[OPMODE] = 0)
 *   In QDC operation mode, Module uses PHASEA, PHASEB, INDEX, HOME, TRIGGER
 *   and ICAP[3:1] to decode the PHASEA and PHASEB signals from Speed/Position sensor.
 *   2.Quadrature Count(QCT) Operation Mode (CTRL[PH1] = 0,CTRL2[OPMODE] = 1)
 *   In QCT operation mode, Module uses PHASEA, PHASEB, PRESET, ENABLE,
 *   TRIGGER and ICAP[3:1] to count the PHASEA and PHASEB signals from Speed/Position sensor.
 *   3.Single Phase Decode(PH1DC) Operation Mode (CTRL[PH1] = 1,CTRL2[OPMODE] = 0)
 *   In PH1DC operation mode, the module uses PHASEA, PHASEB, INDEX, HOME,
 *   TRIGGER and ICAP[3:1] to decode the PHASEA and PHASEB signals from Speed/Position sensor.
 *   4.Single Phase Count(PH1CT) Operation Mode (CTRL[PH1] = 1,CTRL2[OPMODE] = 1)
 *   In PH1CT operation mode, the module uses PHASEA, PHASEB, PRESET, ENABLE,
 *   TRIGGER and ICAP[3:1] to count the PHASEA and PHASEB signals from Speed/Position sensor.
 */
typedef enum _eqdc_operate_mode
{
    kEQDC_QuadratureDecodeOperationMode = 0U, /*!< Use standard quadrature decoder with PHASEA/PHASEB, INDEX/HOME. */
    kEQDC_QuadratureCountOperationMode,   /*!< Use quadrature count operation mode with PHASEA/PHASEB, PRESET/ENABLE. */
    kEQDC_SinglePhaseDecodeOperationMode, /*!< Use single phase quadrature decoder with PHASEA/PHASEB, INDEX/HOME. */
    kEQDC_SinglePhaseCountOperationMode,  /*!< Use single phase count decoder with PHASEA/PHASEB, PRESET/ENABLE. */
} eqdc_operate_mode_t;

/*!
 * @brief Define type for decoder count mode.
 *
 * In decode mode, it uses the standard quadrature decoder with PHASEA and PHASEB,
 * PHASEA = 0 and PHASEB = 0 mean reverse direction.
 *      - If PHASEA leads PHASEB, then motion is in the positive direction.
 *      - If PHASEA trails PHASEB,then motion is in the negative direction.
 * In single phase mode, there are three count modes:
 *      - In Signed Count mode (Single Edge). Both position counter (POS) and position difference counter (POSD) count
 *      on the input PHASEA rising edge while the input PHASEB provides the selected position counter direction
 * (up/down). If CTRL[REV] is 1, then the position counter will count in the opposite direction.
 *      - In Signed Count mode (double edge), both position counter (POS) and
 *      position difference counter (POSD) count the input PHASEA on both rising edge and falling edge while the input
 * PHASEB provides the selected position counter direction (up/down).
 *      - In UP/DOWN Pulse Count mode. Both position counter (POS) and position difference counter (POSD) count in the
 * up direction when input PHASEA rising edge occurs. Both counters count in the down direction when input PHASEB rising
 * edge occurs. If CTRL[REV] is 1, then the position counter will count in the opposite direction.
 */
typedef enum _eqdc_count_mode
{
    kEQDC_QuadratureX4 = 0U, /*!< Active on kEQDC_QuadratureDecodeOperationMode/kEQDC_QuadratureCountOperationMode. */
    kEQDC_QuadratureX2 = 1U, /*!< Active on kEQDC_QuadratureDecodeOperationMode/kEQDC_QuadratureCountOperationMode. */
    kEQDC_QuadratureX1 = 2U, /*!< Active on kEQDC_QuadratureDecodeOperationMode/kEQDC_QuadratureCountOperationMode. */
    kEQDC_UpDownPulseCount =
        0U, /*!< Active on kEQDC_SinglePhaseDecodeOperationMode/kEQDC_SinglePhaseCountOperationMode. */
    kEQDC_SignedCountDoubleEdge =
        1U, /*!< Active on kEQDC_SinglePhaseDecodeOperationMode/kEQDC_SinglePhaseCountOperationMode. */
    kEQDC_SignedCountSingleEdge =
        2U, /*!< Active on kEQDC_SinglePhaseDecodeOperationMode/kEQDC_SinglePhaseCountOperationMode. */
} eqdc_count_mode_t;

/*!
 * @brief Define type for the condition of POSMATCH pulses.
 */
typedef enum _eqdc_output_pulse_mode
{
    kEQDC_OutputPulseOnCounterEqualCompare = 0U, /*!< POSMATCH pulses when a match occurs between the position counters
                                                    (POS) and the compare value (UCOMPx/LCOMPx)(x range is 0-3). */
    kEQDC_OutputPulseOnReadingPositionCounter,   /*!< POSMATCH pulses when reading position counter(POS and LPOS),
                                                    revolution   counter(REV), position difference counter(POSD). */
} eqdc_output_pulse_mode_t;

/*!
 * @brief Define type for determining how the revolution counter (REV) is incremented/decremented.
 */
typedef enum _eqdc_revolution_count_condition
{
    kEQDC_RevolutionCountOnIndexPulse = 0U, /*!< Use INDEX pulse to increment/decrement revolution counter. */
    kEQDC_RevolutionCountOnRollOverModulus, /*!< Use modulus counting roll-over/under to increment/decrement revolution
                                              counter. */
} eqdc_revolution_count_condition_t;

/*!
 * @brief Input Filter Sample Count
 *
 * The Input Filter Sample Count represents the number of consecutive samples
 * that must agree, before the input filter accepts an input transition
 */
typedef enum _eqdc_filter_sample_count
{
    kEQDC_Filter3Samples  = 0U, /*!< 3  samples. */
    kEQDC_Filter4Samples  = 1U, /*!< 4  samples. */
    kEQDC_Filter5Samples  = 2U, /*!< 5  samples. */
    kEQDC_Filter6Samples  = 3U, /*!< 6  samples. */
    kEQDC_Filter7Samples  = 4U, /*!< 7  samples. */
    kEQDC_Filter8Samples  = 5U, /*!< 8  samples. */
    kEQDC_Filter9Samples  = 6U, /*!< 9  samples. */
    kEQDC_Filter10Samples = 7U, /*!< 10 samples. */
} eqdc_filter_sample_count_t;

/*!
 * @brief Count direction.
 */
typedef enum _eqdc_count_direction_flag
{
    kEQDC_CountDirectionDown = 0U, /*!< Last count was in down direction. */
    kEQDC_CountDirectionUp,        /*!< Last count was in up direction. */
} eqdc_count_direction_flag_t;

/*!
 * @brief Prescaler used by Last Edge Time (LASTEDGE) and
 * Position Difference Period Counter (POSDPER).
 */
typedef enum _eqdc_prescaler
{
    kEQDC_Prescaler1     = 0U,  /*!< Prescaler value 1. */
    kEQDC_Prescaler2     = 1U,  /*!< Prescaler value 2. */
    kEQDC_Prescaler4     = 2U,  /*!< Prescaler value 4. */
    kEQDC_Prescaler8     = 3U,  /*!< Prescaler value 8. */
    kEQDC_Prescaler16    = 4U,  /*!< Prescaler value 16. */
    kEQDC_Prescaler32    = 5U,  /*!< Prescaler value 32. */
    kEQDC_Prescaler64    = 6U,  /*!< Prescaler value 64. */
    kEQDC_Prescaler128   = 7U,  /*!< Prescaler value 128. */
    kEQDC_Prescaler256   = 8U,  /*!< Prescaler value 256. */
    kEQDC_Prescaler512   = 9U,  /*!< Prescaler value 512. */
    kEQDC_Prescaler1024  = 10U, /*!< Prescaler value 1024. */
    kEQDC_Prescaler2048  = 11U, /*!< Prescaler value 2048. */
    kEQDC_Prescaler4096  = 12U, /*!< Prescaler value 4096. */
    kEQDC_Prescaler8192  = 13U, /*!< Prescaler value 8192. */
    kEQDC_Prescaler16384 = 14U, /*!< Prescaler value 16384. */
    kEQDC_Prescaler32768 = 15U, /*!< Prescaler value 32768. */
} eqdc_prescaler_t;

/*!
 * @brief Define user configuration structure for EQDC module.
 */
typedef struct _eqdc_config
{
    /* Basic counter. */
    bool enableReverseDirection; /*!< Enable reverse direction counting. */
    bool countOnce;              /*!< Selects modulo loop or one shot counting mode.  */

    bool enableDma;                /*!< Enable DMA for new written buffer values of COMPx/INIT/MOD(x range is 0-3) */
    bool bufferedRegisterLoadMode; /*!<selects the loading time point of the buffered compare registers UCOMPx/LCOMPx,
                                       x=0~3, initial register (UINIT/LINIT), and modulus register (UMOD/LMOD). */

    bool enableTriggerInitPositionCounter;    /*!< Initialize position counter with initial register(UINIT, LINIT) value
                                               on TRIGGER's rising edge. */

#if (defined(FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD) && FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD)
 /*!
 * Enables the feature that the position counter to be initialized by Index Event Edge Mark.
 *
 * This option works together with @ref _eqdc_index_preset_init_pos_counter_mode and @ref enableReverseDirection;
 * If enabled, the behavior is like this:
 *
 * When PHA leads PHB (Clockwise):
 *   If @ref _eqdc_index_preset_init_pos_counter_mode is @ref kEQDC_IndexInitPosCounterOnRisingEdge,
 *   then INDEX rising edge reset position counter.
 *   If @ref _eqdc_index_preset_init_pos_counter_mode is @ref kEQDC_IndexInitPosCounterOnFallingEdge,
 *   then INDEX falling edge reset position counter.
 *   If @ref enableReverseDirection is false, then Reset position counter to initial value.
 *   If @ref enableReverseDirection is true, then reset position counter to modulus value.
 *
 * When PHA lags PHB (Counter Clockwise):
 *   If @ref _eqdc_index_preset_init_pos_counter_mode is @ref kEQDC_IndexInitPosCounterOnRisingEdge,
 *   then INDEX falling edge reset position counter.
 *   If @ref _eqdc_index_preset_init_pos_counter_mode is @ref kEQDC_IndexInitPosCounterOnFallingEdge,
 *   then INDEX rising edge reset position counter.
 *   If @ref enableReverseDirection is false, then Reset position counter to modulus value.
 *   If @ref enableReverseDirection is true, then reset position counter to initial value.
 */
    bool enableIndexInitPositionCounter;
#endif /* FSL_FEATURE_EQDC_CTRL2_HAS_EMIP_BIT_FIELD */

    bool enableTriggerClearPositionRegisters; /*!< Clear position counter(POS), revolution counter(REV), position
                                                difference counter (POSD) on TRIGGER's rising edge. */
    bool enableTriggerHoldPositionRegisters;  /*!< Load position counter(POS), revolution counter(REV), position
                                                difference counter (POSD) values to hold registers  on TRIGGER's rising
                                                edge. */

    bool filterPhaseA; /*!< Filter operation on PHASEA input, when write 1, it means filter for PHASEA input is
                           bypassed. */
    bool filterPhaseB; /*!< Filter operation on PHASEB input, when write 1, it means filter for PHASEB input is
                           bypassed. */
    bool filterIndPre; /*!< Filter operation on INDEX/PRESET input, when write 1, it means filter for INDEX/PRESET
                           input is bypassed. */
    bool filterHomEna; /*!< Filter operation on HOME/ENABLE input, when write 1, it means filter for  HOME/ENABLE input
                           is bypassed. */

    /* Watchdog. */
    bool enableWatchdog;           /*!< Enable the watchdog to detect if the target is moving or not. */
    uint16_t watchdogTimeoutValue; /*!< Watchdog timeout count value. It stores the timeout count for the quadrature
                                        decoder module watchdog timer. */

    /* Filter for input signals: PHASEA, PHASEB, INDEX and HOME. */
    eqdc_prescaler_t prescaler;                   /*!< Prescaler. */
    bool filterClockSourceselection;              /*!< Filter Clock Source selection. */
    eqdc_filter_sample_count_t filterSampleCount; /*!< Input Filter Sample Count. This value should be chosen to reduce
                               the probability of noisy samples causing an incorrect transition to be recognized. The
                               value represent the number of consecutive samples that must agree prior to the input
                               filter accepting an input transition. */
    uint8_t filterSamplePeriod; /*!< Input Filter Sample Period. This value should be set such that the sampling
                                     period is larger than the period of the expected noise. This value represents the
                                      sampling period (in IPBus clock cycles) of the decoder input signals.
                                      The available range is 0 - 255. */

    /* Operate mode. */
    eqdc_operate_mode_t operateMode; /*!< Selects operation mode. */
    eqdc_count_mode_t countMode;     /*!< Selects count mode. */

    /* Signal detection. */
    eqdc_home_enable_init_pos_counter_mode_t homeEnableInitPosCounterMode;   /*!< Select how HOME/Enable signal used to
                                                                  initialize position counters. */
    eqdc_index_preset_init_pos_counter_mode_t indexPresetInitPosCounterMode; /*!< Select how INDEX/Preset signal used
                                                                  to initialize position counters. */

    /* Position compare. */
    eqdc_output_pulse_mode_t outputPulseMode; /*!< The condition of POSMATCH pulses. */
    uint32_t positionCompareValue[4]; /*!< Position compare 0 ~ 3 value. The available value is a 32-bit number.*/

    /* Modulus counting. */
    eqdc_revolution_count_condition_t revolutionCountCondition; /*!< Revolution Counter Modulus Enable. */
    uint32_t positionModulusValue; /*!< Position modulus value. The available value is a 32-bit number. */
    uint32_t positionInitialValue; /*!< Position initial value. The available value is a 32-bit number. */
    uint32_t positionCounterValue; /*!< Position counter value. When Modulo mode enabled, the positionCounterValue
                                           should be in the range of @ref positionInitialValue and
                                           @ref positionModulusValue. */

    /* Period measurement. */
    bool enablePeriodMeasurement; /*!< Enable period measurement. When enabled, the position difference hold register
                                      (POSDH) is only updated when position difference register (POSD) is read. */

    /* Interrupts. */
    uint16_t enabledInterruptsMask; /*!< Mask of interrupts to be enabled, should be OR'ed value of @ref
                                          _eqdc_interrupt_enable. */
} eqdc_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization and deinitialization Interfaces
 * @{
 */

/*!
 * @brief Initializes the EQDC module.
 *
 * This function initializes the EQDC by enabling the IP bus clock (optional).
 *
 * @param base   EQDC peripheral base address.
 * @param psConfig Pointer to configuration structure.
 */
void EQDC_Init(EQDC_Type *base, const eqdc_config_t *psConfig);

/*!
 * @brief Gets an available pre-defined configuration.
 *
 * The default value are:
 * @code
    psConfig->enableReverseDirection              = false;
    psConfig->countOnce                           = false;
    psConfig->operateMode                         = kEQDC_QuadratureDecodeOperationMode;
    psConfig->countMode                           = kEQDC_QuadratureX4;
    psConfig->homeEnableInitPosCounterMode        = kEQDC_HomeInitPosCounterDisabled;
    psConfig->indexPresetInitPosCounterMode       = kEQDC_IndexInitPosCounterDisabled;
    psConfig->enableIndexInitPositionCounter      = false;
    psConfig->enableDma                           = false;
    psConfig->bufferedRegisterLoadMode            = false;
    psConfig->enableTriggerInitPositionCounter    = false;
    psConfig->enableTriggerClearPositionRegisters = false;
    psConfig->enableTriggerHoldPositionRegisters  = false;
    psConfig->enableWatchdog                      = false;
    psConfig->watchdogTimeoutValue                = 0xFFFFU;
    psConfig->filterPhaseA                        = 0U;
    psConfig->filterPhaseB                        = 0U;
    psConfig->filterIndPre                        = 0U;
    psConfig->filterHomEna                        = 0U;
    psConfig->filterClockSourceselection          = false;
    psConfig->filterSampleCount                   = kEQDC_Filter3Samples;
    psConfig->filterSamplePeriod                  = 0U;
    psConfig->outputPulseMode                     = kEQDC_OutputPulseOnCounterEqualCompare;
    psConfig->positionCompareValue[0]  	          = 0xFFFFFFFFU;
    psConfig->positionCompareValue[1]             = 0xFFFFFFFFU;
    psConfig->positionCompareValue[2]             = 0xFFFFFFFFU;
    psConfig->positionCompareValue[3]             = 0xFFFFFFFFU;
    psConfig->revolutionCountCondition            = kEQDC_RevolutionCountOnIndexPulse;
    psConfig->positionModulusValue                = 0U;
    psConfig->positionInitialValue                = 0U;
    psConfig->positionCounterValue                = 0U;
    psConfig->enablePeriodMeasurement             = false;
    psConfig->prescaler                           = kEQDC_Prescaler1;
    psConfig->enabledInterruptsMask               = 0U;
   @endcode
 *
 * @param psConfig Pointer to configuration structure.
 */
void EQDC_GetDefaultConfig(eqdc_config_t *psConfig);

/*!
 * @brief De-initializes the EQDC module.
 *
 * This function deinitializes the EQDC by disabling the IP bus clock (optional).
 *
 * @param base EQDC peripheral base address.
 */
void EQDC_Deinit(EQDC_Type *base);

/*!
 * @brief Initializes the mode of operation.
 *
 * This function initializes mode of operation by enabling the IP bus clock (optional).
 *
 * @param base   EQDC peripheral base address.
 * @param operateMode Select operation mode.
 */
void EQDC_SetOperateMode(EQDC_Type *base, eqdc_operate_mode_t operateMode);

/*!
 * @brief Initializes the mode of count.
 *
 * These bits control the basic counting and behavior of Position Counter and Position Difference Counter.
 * Setting CTRL[REV] to 1 can reverse the counting direction.
 * 1.In quadrature Mode (CTRL[PH1] = 0):
 *    00b - CM0: Normal/Reverse Quadrature X4
 *    01b - CM1: Normal/Reverse Quadrature X2
 *    10b - CM2: Normal/Reverse Quadrature X1
 *    11b - CM3: Reserved
 * 2.In Single Phase Mode (CTRL[PH1] = 1):
 *    00b - CM0: UP/DOWN Pulse Count Mode
 *    01b - CM1: Signed Mode, count PHASEA rising/falling edge, position counter counts up when PHASEB
 *    is low and counts down when PHASEB is high
 *    10b - CM2: Signed Count Mode,count PHASEA rising edge only, position counter counts up when
 *    PHASEB is low and counts down when PHASEB is high
 *    11b - CM3: Reserved
 *
 * @param base   EQDC peripheral base address.
 * @param countMode Select count mode.
 */
static inline void EQDC_SetCountMode(EQDC_Type *base, eqdc_count_mode_t countMode)
{
    base->CTRL2 = (base->CTRL2 & (uint16_t)(~EQDC_CTRL2_CMODE_MASK)) | EQDC_CTRL2_CMODE(countMode);
}

/*! @} */

/*!
 * @name Watchdog
 * @{
 */

/*!
 * @brief Enable watchdog for EQDC module.
 *
 * @param base EQDC peripheral base address
 * @param bEnable Enables or disables the watchdog
 */
static inline void EQDC_EnableWatchdog(EQDC_Type *base, bool bEnable)
{
    if (bEnable)
    {
        base->CTRL = (base->CTRL & (~EQDC_CTRL_W1C_FLAGS)) | EQDC_CTRL_WDE_MASK;
    }
    else
    {
        base->CTRL = (base->CTRL & (~(EQDC_CTRL_W1C_FLAGS | EQDC_CTRL_WDE_MASK)));
    }
}

/*!
 * @brief Set watchdog timeout value.
 *
 * @param base EQDC peripheral base address
 * @param u16Timeout Number of clock cycles, plus one clock cycle that the
 * watchdog timer counts before timing out
 */
static inline void EQDC_SetWatchdogTimeout(EQDC_Type *base, uint16_t u16Timeout)
{
    base->WTR = u16Timeout;
}

/*! @} */

/*!
 * @name DMA
 * @{
 */

/*!
 * @brief Enable DMA for EQDC module.
 *
 * @param base EQDC peripheral base address
 * @param bEnable Enables or disables the DMA
 */
static inline void EQDC_EnableDMA(EQDC_Type *base, bool bEnable)
{
    if (bEnable)
    {
        base->CTRL |= EQDC_CTRL_DMAEN_MASK;
    }
    else
    {
#if (defined(FSL_FEATURE_EQDC_HAS_ERRATA_051383) && FSL_FEATURE_EQDC_HAS_ERRATA_051383)
        /* Quadrature decoder CTRL[DMAEN] bit can not be cleared except do EQDC reset*/
        assert(false);
#else
        base->CTRL &= ~EQDC_CTRL_DMAEN_MASK;
#endif
    }
}

/*! @} */

/*!
 * @name Double-set Registers Loading Operation
 * @{
 */

/*!
 * @brief Set Buffered Register Load (Update) Mode.
 *
 * This bit selects the loading time point of the buffered compare registers UCOMPx/LCOMPx, x=0~3,
 * initial register (UINIT/LINIT), and modulus register (UMOD/LMOD).
 * Buffered registers are loaded and take effect at the next roll-over or roll-under if CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 */
static inline void EQDC_SetBufferedRegisterLoadUpdateMode(EQDC_Type *base)
{
    base->CTRL2 |= EQDC_CTRL2_LDMOD_MASK;
}

/*!
 * @brief Clear Buffered Register Load (Update) Mode.
 *
 * Buffered Register Load (Update) Mode bit selects the loading time point of the buffered compare registers
 * UCOMPx/LCOMPx, x=0~3, initial register (UINIT/LINIT), and modulus register (UMOD/LMOD). Buffered registers are loaded
 * and take effect immediately upon CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 */
static inline void EQDC_ClearBufferedRegisterLoadUpdateMode(EQDC_Type *base)
{
    base->CTRL2 &= ~EQDC_CTRL2_LDMOD_MASK;
}

/*!
 * @brief Set load okay.
 *
 * Load okay enables that the outer-set values of buffered compare registers (UCOMPx/LCOMPx, x=0~3),
 * initial register(UINIT/LINIT) and modulus register(UMOD/LMOD) can be loaded into their inner-sets and
 * take effect.
 * When LDOK is set, this loading action occurs at the next position counter roll-over or roll-under if
 * CTRL2[LDMOD] is set, or it occurs immediately if CTRL2[LDMOD] is cleared. LDOK is automatically
 * cleared after the values in outer-set is loaded into the inner-set.
 *
 * @param base EQDC peripheral base address.
 */
static inline void EQDC_SetEqdcLdok(EQDC_Type *base)
{
    base->CTRL |= EQDC_CTRL_LDOK_MASK;
}

/*!
 * @brief Get load okay.
 *
 * @param base EQDC peripheral base address.
 */
static inline uint8_t EQDC_GetEqdcLdok(EQDC_Type *base)
{
    return base->CTRL & EQDC_CTRL_LDOK_MASK;
}

/*!
 * @brief Clear load okay.
 *
 * @param base EQDC peripheral base address.
 */
static inline void EQDC_ClearEqdcLdok(EQDC_Type *base)
{
    base->CTRL &= ~EQDC_CTRL_LDOK_MASK;
}

/*! @} */

/*!
 * @name Status
 * @{
 */
/*!
 * @brief  Get the status flags.
 *
 * @param  base EQDC peripheral base address.
 *
 * @return  Logical OR'ed value of the status flags, @ref _eqdc_status_flags.
 */
static inline uint32_t EQDC_GetStatusFlags(EQDC_Type *base)
{
    uint32_t u32Flags = 0U;

    u32Flags = (uint32_t)(base->CTRL) & EQDC_CTRL_INT_FLAGS;

    u32Flags |= ((uint32_t)(base->INTCTRL) & EQDC_INTCTRL_INT_FLAGS) << 16;
    return u32Flags;
}

/*!
 * @brief Clear the status flags.
 *
 * @param base EQDC peripheral base address.
 * @param u32Flags Logical OR'ed value of the flags to clear, @ref _eqdc_status_flags.
 */
static inline void EQDC_ClearStatusFlags(EQDC_Type *base, uint32_t u32Flags)
{
    if (0U != (u32Flags & EQDC_CTRL_INT_FLAGS))
    {
        base->CTRL = (base->CTRL & (~EQDC_CTRL_W1C_FLAGS)) | (u32Flags & EQDC_CTRL_INT_FLAGS);
    }

    if (0U != ((u32Flags >> 16) & EQDC_INTCTRL_INT_FLAGS))
    {
        base->INTCTRL = (base->INTCTRL & (~EQDC_INTCTRL_W1C_FLAGS)) | ((u32Flags >> 16) & EQDC_INTCTRL_INT_FLAGS);
    }
}

/*!
 * @brief  Get the signals' real-time status.
 *
 * @param  base EQDC peripheral base address.
 * @return Logical OR'ed value of the real-time signal status, @ref _eqdc_signal_status.
 */
static inline uint16_t EQDC_GetSignalStatusFlags(EQDC_Type *base)
{
    return base->IMR;
}

/*!
 * @brief Get the direction of the last count.
 *
 * @param  base EQDC peripheral base address.
 * @return Direction of the last count.
 */
static inline eqdc_count_direction_flag_t EQDC_GetLastCountDirection(EQDC_Type *base)
{
    return ((0U != (base->IMR & EQDC_IMR_DIR_MASK)) ? kEQDC_CountDirectionUp : kEQDC_CountDirectionDown);
}
/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enable the interrupts.
 *
 * @param base EQDC peripheral base address.
 * @param u32Interrupts Logical OR'ed value of the interrupts, @ref _eqdc_interrupt_enable.
 */
static inline void EQDC_EnableInterrupts(EQDC_Type *base, uint32_t u32Interrupts)
{
    if (0U != (u32Interrupts & EQDC_CTRL_INT_EN))
    {
        base->CTRL = (base->CTRL & (~EQDC_CTRL_W1C_FLAGS)) | (u32Interrupts & EQDC_CTRL_INT_EN);
    }

    if (0U != ((u32Interrupts >> 16) & EQDC_INTCTRL_INT_EN))
    {
        base->INTCTRL = (base->INTCTRL & (~EQDC_INTCTRL_W1C_FLAGS)) | ((u32Interrupts >> 16) & EQDC_INTCTRL_INT_EN);
    }
}

/*!
 * @brief Disable the interrupts.
 *
 * @param base EQDC peripheral base address.
 * @param u32Interrupts Logical OR'ed value of the interrupts, @ref _eqdc_interrupt_enable.
 */
static inline void EQDC_DisableInterrupts(EQDC_Type *base, uint32_t u32Interrupts)
{
    if (0U != (u32Interrupts & EQDC_CTRL_INT_EN))
    {
        base->CTRL = (base->CTRL & (~EQDC_CTRL_W1C_FLAGS)) & (~(u32Interrupts & EQDC_CTRL_INT_EN));
    }

    if (0U != ((u32Interrupts >> 16) & EQDC_INTCTRL_INT_EN))
    {
        base->INTCTRL = (base->INTCTRL & (~EQDC_INTCTRL_W1C_FLAGS)) & (~((u32Interrupts >> 16) & EQDC_INTCTRL_INT_EN));
    }
}

/*! @} */

/*!
 * @name Counter Operation
 * @{
 */

/*!
 * @brief Load the initial position value to position counter.
 *
 * Software trigger to load the initial position value (UINIT and LINIT) contents
 * to position counter (UPOS and LPOS), so that to provide the consistent
 * operation the position counter registers.
 *
 * @param base EQDC peripheral base address.
 */
static inline void EQDC_DoSoftwareLoadInitialPositionValue(EQDC_Type *base)
{
    base->CTRL = (base->CTRL & (~EQDC_CTRL_W1C_FLAGS)) | EQDC_CTRL_SWIP_MASK;
}

/*!
 * @brief Set initial position value for EQDC module.
 *
 * Set the position counter initial value (UINIT, LINIT).
 * After writing values to the UINIT and LINIT registers, the values are "buffered" into outer-set
 * registers temporarily. Values will be loaded into inner-set registers and take effect using
 * the following two methods:
 * 1. If CTRL2[LDMODE] is 1, "buffered" values are loaded into inner-set and take effect
 * at the next roll-over or roll-under if CTRL[LDOK] is set.
 * 2. If CTRL2[LDMODE] is 0, "buffered" values are loaded into inner-set and take effect
 * immediately when CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 * @param u32PositionInitValue Position initial value
 */
static inline void EQDC_SetInitialPositionValue(EQDC_Type *base, uint32_t u32PositionInitValue)
{
    base->UINIT = (uint16_t)(u32PositionInitValue >> 16U);
    base->LINIT = (uint16_t)(u32PositionInitValue);
}

/*!
 * @brief Set position counter value.
 *
 * Set the position counter value (POS or UPOS, LPOS).
 *
 * @param base EQDC peripheral base address
 * @param positionCounterValue Position counter value
 */
static inline void EQDC_SetPositionCounterValue(EQDC_Type *base, uint32_t positionCounterValue)
{
    base->UPOS = (uint16_t)(positionCounterValue >> 16U);
    base->LPOS = (uint16_t)(positionCounterValue);
}

/*!
 * @brief Set position counter modulus value.
 *
 * Set the position counter modulus value (UMOD, LMOD).
 * After writing values to the UMOD and LMOD registers, the values are "buffered" into outer-set
 * registers temporarily. Values will be loaded into inner-set registers and take effect using
 * the following two methods:
 * 1. If CTRL2[LDMODE] is 1, "buffered" values are loaded into inner-set and take effect
 * at the next roll-over or roll-under if CTRL[LDOK] is set.
 * 2. If CTRL2[LDMODE] is 0, "buffered" values are loaded into inner-set and take effect
 * immediately when CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 * @param positionModulusValue Position modulus value
 */
static inline void EQDC_SetPositionModulusValue(EQDC_Type *base, uint32_t positionModulusValue)
{
    base->UMOD = (uint16_t)(positionModulusValue >> 16U);
    base->LMOD = (uint16_t)(positionModulusValue);
}

/*!
 * @brief Set position counter compare 0 value.
 *
 * Set the position counter compare 0 value (UCOMP0, LCOMP0).
 * After writing values to the UCOMP0 and LCOMP0 registers, the values are "buffered" into outer-set
 * registers temporarily. Values will be loaded into inner-set registers and take effect using
 * the following two methods:
 * 1. If CTRL2[LDMODE] is 1, "buffered" values are loaded into inner-set and take effect
 * at the next roll-over or roll-under if CTRL[LDOK] is set.
 * 2. If CTRL2[LDMODE] is 0, "buffered" values are loaded into inner-set and take effect
 * immediately when CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 * @param u32PositionComp0Value Position modulus value
 */
static inline void EQDC_SetPositionCompare0Value(EQDC_Type *base, uint32_t u32PositionComp0Value)
{
    base->UCOMP0 = (uint16_t)(u32PositionComp0Value >> 16U);
    base->LCOMP0 = (uint16_t)(u32PositionComp0Value);
}

/*!
 * @brief Set position counter compare 1 value.
 *
 * Set the position counter compare 1 value (UCOMP1, LCOMP1).
 * After writing values to the UCOMP1 and LCOMP1 registers, the values are "buffered" into outer-set
 * registers temporarily. Values will be loaded into inner-set registers and take effect using
 * the following two methods:
 * 1. If CTRL2[LDMODE] is 1, "buffered" values are loaded into inner-set and take effect
 * at the next roll-over or roll-under if CTRL[LDOK] is set.
 * 2. If CTRL2[LDMODE] is 0, "buffered" values are loaded into inner-set and take effect
 * immediately when CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 * @param u32PositionComp1Value Position modulus value
 */
static inline void EQDC_SetPositionCompare1Value(EQDC_Type *base, uint32_t u32PositionComp1Value)
{
    base->UCOMP1 = (uint16_t)(u32PositionComp1Value >> 16U);
    base->LCOMP1 = (uint16_t)(u32PositionComp1Value);
}

/*!
 * @brief Set position counter compare 2 value.
 *
 * Set the position counter compare 2 value (UCOMP2, LCOMP2).
 * After writing values to the UCOMP2 and LCOMP2 registers, the values are "buffered" into outer-set
 * registers temporarily. Values will be loaded into inner-set registers and take effect using
 * the following two methods:
 * 1. If CTRL2[LDMODE] is 1, "buffered" values are loaded into inner-set and take effect
 * at the next roll-over or roll-under if CTRL[LDOK] is set.
 * 2. If CTRL2[LDMODE] is 0, "buffered" values are loaded into inner-set and take effect
 * immediately when CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 * @param u32PositionComp2Value Position modulus value
 */
static inline void EQDC_SetPositionCompare2Value(EQDC_Type *base, uint32_t u32PositionComp2Value)
{
    base->UCOMP2 = (uint16_t)(u32PositionComp2Value >> 16U);
    base->LCOMP2 = (uint16_t)(u32PositionComp2Value);
}

/*!
 * @brief Set position counter compare 3 value.
 *
 * Set the position counter compare 3 value (UCOMP3, LCOMP3).
 * After writing values to the UCOMP3 and LCOMP3 registers, the values are "buffered" into outer-set
 * registers temporarily. Values will be loaded into inner-set registers and take effect using
 * the following two methods:
 * 1. If CTRL2[LDMODE] is 1, "buffered" values are loaded into inner-set and take effect
 * at the next roll-over or roll-under if CTRL[LDOK] is set.
 * 2. If CTRL2[LDMODE] is 0, "buffered" values are loaded into inner-set and take effect
 * immediately when CTRL[LDOK] is set.
 *
 * @param base EQDC peripheral base address
 * @param u32PositionComp3Value Position modulus value
 */
static inline void EQDC_SetPositionCompare3Value(EQDC_Type *base, uint32_t u32PositionComp3Value)
{
    base->UCOMP3 = (uint16_t)(u32PositionComp3Value >> 16U);
    base->LCOMP3 = (uint16_t)(u32PositionComp3Value);
}

/*!
 * @brief  Get the current position counter's value.
 *
 * @param  base EQDC peripheral base address.
 *
 * @return Current position counter's value.
 */
static inline uint32_t EQDC_GetPosition(EQDC_Type *base)
{
    uint32_t u32Pos;

    u32Pos = base->UPOS; /* Get upper 16 bits and make a snapshot. */
    u32Pos <<= 16U;
    u32Pos |= base->LPOSH; /* Get lower 16 bits from hold register. */

    return u32Pos;
}

/*!
 * @brief  Get the hold position counter's value.
 *
 * The position counter (POS or UPOS, LPOS) value is loaded to hold position (POSH or UPOSH, LPOSH)
 * when:
 *   1. Position register (POS or UPOS, LPOS), or position difference register (POSD),
 *   or revolution register (REV) is read.
 *   2. TRIGGER happens and TRIGGER is enabled to update the hold registers.
 *
 * @param  base EQDC peripheral base address.
 * @return Hold position counter's value.
 */
static inline uint32_t EQDC_GetHoldPosition(EQDC_Type *base)
{
    uint32_t u32Pos;

    u32Pos = base->UPOSH; /* Get upper 16 bits from hold register. */
    u32Pos <<= 16U;
    u32Pos |= base->LPOSH; /* Get lower 16 bits from hold register. */

    return u32Pos;
}

/*!
 * @brief  Get the hold position counter1's value.
 *
 * The Upper Position Counter Hold Register 1(UPOSH1) shares the same address with UCOMP1.
 * When read, this register means the value of UPOSH1, which is the upper 16 bits of POSH1.
 * The Lower Position Counter Hold Register 1(LPOSH1) shares the same address with LCOMP1.
 * When read, this register means the value of LPOSH1, which is the lower 16 bits of POSH1.
 * Position counter is captured into POSH1 on the rising edge of ICAP[1].
 *
 * @param  base EQDC peripheral base address.
 * @return  Hold position counter1's value.
 */
static inline uint32_t EQDC_GetHoldPosition1(EQDC_Type *base)
{
    uint32_t u32Pos;

    u32Pos = base->UPOSH1; /* Get upper 16 bits from hold register. */
    u32Pos <<= 16U;
    u32Pos |= base->LPOSH1; /* Get lower 16 bits from hold register. */

    return u32Pos;
}

/*!
 * @brief  Get the hold position counter2's value.
 *
 * The Upper Position Counter Hold Register 2(UPOSH2) shares the same address with UCOMP2.
 * When read,this register means the value of UPOSH2, which is the upper 16 bits of POSH2.
 * The Lower Position Counter Hold Register 2(LPOSH2) shares the same address with LCOMP2.
 * When read, this register means the value of LPOSH2, which is the lower 16 bits of POSH2.
 * Position counter is captured into POSH2 on the rising edge of ICAP[2].
 *
 * @param  base EQDC peripheral base address.
 * @return  Hold position counter2's value.
 */
static inline uint32_t EQDC_GetHoldPosition2(EQDC_Type *base)
{
    uint32_t u32Pos;

    u32Pos = base->UPOSH2; /* Get upper 16 bits from hold register. */
    u32Pos <<= 16U;
    u32Pos |= base->LPOSH2; /* Get lower 16 bits from hold register. */

    return u32Pos;
}

/*!
 * @brief  Get the hold position counter3's value.
 *
 * The Upper Position Counter Hold Register 3(UPOSH3) shares the same address with UCOMP3.
 * When read,this register means the value of UPOSH3, which is the upper 16 bits of POSH3.
 * The Lower Position Counter Hold Register 3(LPOSH3) shares the same address with LCOMP3.
 * When read, this register means the value of LPOSH3, which is the lower 16 bits of POSH3.
 * Position counter is captured into POSH3 on the rising edge of ICAP[3].
 *
 * @param  base EQDC peripheral base address.
 * @return  Hold position counter3's value.
 */
static inline uint32_t EQDC_GetHoldPosition3(EQDC_Type *base)
{
    uint32_t u32Pos;

    u32Pos = base->UPOSH3; /* Get upper 16 bits from hold register. */
    u32Pos <<= 16U;
    u32Pos |= base->LPOSH3; /* Get lower 16 bits from hold register. */

    return u32Pos;
}

/*!
 * @brief  Get the position difference counter's value.
 *
 * @param  base EQDC peripheral base address.
 * @return The position difference counter's value.
 */
static inline uint16_t EQDC_GetPositionDifference(EQDC_Type *base)
{
    return base->POSD;
}

/*!
 * @brief  Get the hold position difference counter's value.
 *
 * The position difference (POSD) value is loaded to hold position difference (POSDH)
 * when:
 * 1. Position register (POS or UPOS, LPOS), or position difference register (POSD),
 * or revolution register (REV) is read. When Period Measurement is enabled (CTRL3[PMEN] = 1),
 * POSDH will only be udpated when reading POSD.
 * 2. TRIGGER happens and TRIGGER is enabled to update the hold registers.
 *
 * @param  base EQDC peripheral base address.
 * @return  Hold position difference counter's value.
 */
static inline uint16_t EQDC_GetHoldPositionDifference(EQDC_Type *base)
{
    return base->POSDH;
}

/*!
 * @brief  Get the revolution counter's value.
 *
 * Get the revolution counter (REV) value.
 *
 * @param  base EQDC peripheral base address.
 * @return  The revolution counter's value.
 */
static inline uint16_t EQDC_GetRevolution(EQDC_Type *base)
{
    return base->REV;
}

/*!
 * @brief  Get the hold revolution counter's value.
 *
 * The revolution counter (REV) value is loaded to hold revolution (REVH)
 * when:
 * 1. Position register (POS or UPOS, LPOS), or position difference register (POSD),
 * or revolution register (REV) is read.
 * 2. TRIGGER happens and TRIGGER is enabled to update the hold registers.
 *
 * @param  base EQDC peripheral base address.
 * @return Hold position revolution counter's value.
 */
static inline uint16_t EQDC_GetHoldRevolution(EQDC_Type *base)
{
    return base->REVH;
}

/*!
 * @brief  Get the last edge time.
 *
 * Last edge time (LASTEDGE) is the time since the last edge occurred on PHASEA or PHASEB.
 * The last edge time register counts up using the peripheral clock after prescaler.
 * Any edge on PHASEA or PHASEB will reset this register to 0 and start counting.
 * If the last edge timer count reaches 0xffff, the counting will stop in order to
 * prevent an overflow.Counting will continue when an edge occurs on
 * PHASEA or PHASEB.
 *
 * @param  base EQDC peripheral base address.
 *
 * @return The last edge time.
 */
static inline uint16_t EQDC_GetLastEdgeTime(EQDC_Type *base)
{
    return base->LASTEDGE;
}

/*!
 * @brief  Get the hold last edge time.
 *
 * The hold of last edge time(LASTEDGEH) is update to last edge time(LASTEDGE)
 * when the position difference register register (POSD) is read.
 *
 * @param  base EQDC peripheral base address.
 * @return Hold of last edge time.
 */
static inline uint16_t EQDC_GetHoldLastEdgeTime(EQDC_Type *base)
{
    return base->LASTEDGEH;
}

/*!
 * @brief Get the Position Difference Period counter value
 *
 * The Position Difference Period counter (POSDPER) counts up using the
 * prescaled peripheral clock.  When reading the position difference register(POSD),
 * the last edge time (LASTEDGE) will be loaded to position difference period counter(POSDPER).
 * If the POSDPER count reaches 0xffff, the counting will stop in order to prevent an
 * overflow. Counting will continue when an edge occurs on PHASEA or PHASEB.
 *
 * @param  base EQDC peripheral base address.
 * @return The position difference period counter value.
 */
static inline uint16_t EQDC_GetPositionDifferencePeriod(EQDC_Type *base)
{
    return base->POSDPER;
}

/*!
 * @brief Get buffered Position Difference Period counter value
 *
 * The Bufferd Position Difference Period (POSDPERBFR) value is updated with
 * the position difference period counter(POSDPER) when any edge occurs
 * on PHASEA or PHASEB.
 *
 * @param  base EQDC peripheral base address.
 * @return The buffered position difference period counter value.
 */
static inline uint16_t EQDC_GetBufferedPositionDifferencePeriod(EQDC_Type *base)
{
    return base->POSDPERBFR;
}

/*!
 * @brief Get Hold Position Difference Period counter value
 *
 * The hold position difference period(POSDPERH) is updated with the value of
 * buffered position difference period(POSDPERBFR) when the
 * position difference(POSD) register is read.
 *
 * @param  base EQDC peripheral base address.
 * @return The hold position difference period counter value.
 */
static inline uint16_t EQDC_GetHoldPositionDifferencePeriod(EQDC_Type *base)
{
    return base->POSDPERH;
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_EQDC_H_ */
