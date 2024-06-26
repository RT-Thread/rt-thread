/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_LPADC_H_
#define FSL_LPADC_H_

#include "fsl_common.h"

/*!
 * @addtogroup lpadc
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief LPADC driver version 2.8.4. */
#define FSL_LPADC_DRIVER_VERSION (MAKE_VERSION(2, 8, 4))
/*! @} */

#if (defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) && (FSL_FEATURE_LPADC_OFSTRIM_COUNT == 1))
#define ADC_OFSTRIM_OFSTRIM_MAX  (ADC_OFSTRIM_OFSTRIM_MASK >> ADC_OFSTRIM_OFSTRIM_SHIFT)
#define ADC_OFSTRIM_OFSTRIM_SIGN ((ADC_OFSTRIM_OFSTRIM_MAX + 1U) >> 1U)

#elif (defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) && (FSL_FEATURE_LPADC_OFSTRIM_COUNT == 2))
#define ADC_OFSTRIM_OFSTRIM_A_MAX  (ADC_OFSTRIM_OFSTRIM_A_MASK >> ADC_OFSTRIM_OFSTRIM_A_SHIFT)
#define ADC_OFSTRIM_OFSTRIM_B_MAX  (ADC_OFSTRIM_OFSTRIM_B_MASK >> ADC_OFSTRIM_OFSTRIM_B_SHIFT)
#define ADC_OFSTRIM_OFSTRIM_A_SIGN ((ADC_OFSTRIM_OFSTRIM_A_MAX + 1U) >> 1U)
#define ADC_OFSTRIM_OFSTRIM_B_SIGN ((ADC_OFSTRIM_OFSTRIM_B_MAX + 1U) >> 1U)
#endif /* defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) */

/*!
 * @brief Define the MACRO function to get command status from status value.
 *
 * The statusVal is the return value from LPADC_GetStatusFlags().
 */
#define LPADC_GET_ACTIVE_COMMAND_STATUS(statusVal) ((statusVal & ADC_STAT_CMDACT_MASK) >> ADC_STAT_CMDACT_SHIFT)

/*!
 * @brief Define the MACRO function to get trigger status from status value.
 *
 * The statusVal is the return value from LPADC_GetStatusFlags().
 */
#define LPADC_GET_ACTIVE_TRIGGER_STATUE(statusVal) ((statusVal & ADC_STAT_TRGACT_MASK) >> ADC_STAT_TRGACT_SHIFT)

/* Map macros to the unified name. */
#if !defined(ADC_STAT_FOF0_MASK)
#ifdef ADC_STAT_FOF_MASK
#define ADC_STAT_FOF0_MASK ADC_STAT_FOF_MASK
#else
#error "ADC_STAT_FOF0_MASK not defined"
#endif /* ifdef(ADC_STAT_FOF_MASK) */
#endif /* !defined(ADC_STAT_FOF0_MASK) */

#if !defined(ADC_STAT_RDY0_MASK)
#ifdef ADC_STAT_RDY_MASK
#define ADC_STAT_RDY0_MASK ADC_STAT_RDY_MASK
#else
#error "ADC_STAT_RDY0_MASK not defined"
#endif /* ifdef ADC_STAT_RDY_MASK */
#endif /* !defined(ADC_STAT_RDY0_MASK) */

#if !defined(ADC_IE_FOFIE0_MASK)
#ifdef ADC_IE_FOFIE_MASK
#define ADC_IE_FOFIE0_MASK ADC_IE_FOFIE_MASK
#else
#error "ADC_IE_FOFIE0_MASK not defined"
#endif /* ifdef ADC_IE_FOFIE_MASK */
#endif /* !defined(ADC_IE_FOFIE0_MASK) */

#if !defined(ADC_IE_FWMIE0_MASK)
#ifdef ADC_IE_FWMIE_MASK
#define ADC_IE_FWMIE0_MASK ADC_IE_FWMIE_MASK
#else
#error "ADC_IE_FWMIE0_MASK not defined"
#endif /* ifdef ADC_IE_FWMIE_MASK */
#endif /* !defined(ADC_IE_FWMIE0_MASK) */

/*!
 * @brief Define hardware flags of the module.
 */
enum _lpadc_status_flags
{
    kLPADC_ResultFIFO0OverflowFlag = ADC_STAT_FOF0_MASK, /*!< Indicates that more data has been written to the Result
                                                               FIFO 0 than it can hold. */
    kLPADC_ResultFIFO0ReadyFlag = ADC_STAT_RDY0_MASK,    /*!< Indicates when the number of valid datawords in the result
                                                               FIFO 0 is greater than the setting watermark level. */

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    kLPADC_ResultFIFO1OverflowFlag = ADC_STAT_FOF1_MASK, /*!< Indicates that more data has been written to the Result
                                                              FIFO 1 than it can hold. */
    kLPADC_ResultFIFO1ReadyFlag = ADC_STAT_RDY1_MASK,    /*!< Indicates when the number of valid datawords in the result
                                                              FIFO 1 is greater than the setting watermark level. */
#endif /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U)) */

#if (defined(FSL_FEATURE_LPADC_HAS_STAT_TEXC_INT) && (FSL_FEATURE_LPADC_HAS_STAT_TEXC_INT == 1U))
    kLPADC_TriggerExceptionFlag = ADC_STAT_TEXC_INT_MASK, /*!< Indicates that a trigger exception event has occurred. */
#endif /* (defined(FSL_FEATURE_LPADC_HAS_STAT_TEXC_INT) && (FSL_FEATURE_LPADC_HAS_STAT_TEXC_INT == 1U)) */

#if (defined(FSL_FEATURE_LPADC_HAS_STAT_TCOMP_INT) && (FSL_FEATURE_LPADC_HAS_STAT_TCOMP_INT == 1U))
    kLPADC_TriggerCompletionFlag = ADC_STAT_TCOMP_INT_MASK, /*!< Indicates that a trigger completion event has occurred.
                                                             */
#endif /* (defined(FSL_FEATURE_LPADC_HAS_STAT_TCOMP_INT) && (FSL_FEATURE_LPADC_HAS_STAT_TCOMP_INT == 1U)) */

#if (defined(FSL_FEATURE_LPADC_HAS_STAT_CAL_RDY) && (FSL_FEATURE_LPADC_HAS_STAT_CAL_RDY == 1U))
    kLPADC_CalibrationReadyFlag = ADC_STAT_CAL_RDY_MASK, /*!< Indicates that the calibration process is done. */
#endif /* (defined(FSL_FEATURE_LPADC_HAS_STAT_CAL_RDY) && (FSL_FEATURE_LPADC_HAS_STAT_CAL_RDY == 1U)) */

#if (defined(FSL_FEATURE_LPADC_HAS_STAT_ADC_ACTIVE) && (FSL_FEATURE_LPADC_HAS_STAT_ADC_ACTIVE == 1U))
    kLPADC_ActiveFlag = ADC_STAT_ADC_ACTIVE_MASK, /*!< Indicates that the ADC is in active state. */
#endif /* (defined(FSL_FEATURE_LPADC_HAS_STAT_ADC_ACTIVE) && (FSL_FEATURE_LPADC_HAS_STAT_ADC_ACTIVE == 1U)) */

    kLPADC_ResultFIFOOverflowFlag = kLPADC_ResultFIFO0OverflowFlag, /*!< To compilitable with old version, do not
                                                                        recommend using this, please use @ref
                                                                        kLPADC_ResultFIFO0OverflowFlag as instead. */

    kLPADC_ResultFIFOReadyFlag = kLPADC_ResultFIFO0ReadyFlag,       /*!< To compilitable with old version, do not
                                                                        recommend using this, please use @ref
                                                                        kLPADC_ResultFIFO0ReadyFlag as instead. */
};

/*!
 * @brief Define interrupt switchers of the module.
 *
 * Note: LPADC of different chips supports different number of trigger sources,
 * please check the Reference Manual for details.
 */
enum _lpadc_interrupt_enable
{
    kLPADC_ResultFIFO0OverflowInterruptEnable = ADC_IE_FOFIE0_MASK, /*!< Configures ADC to generate overflow interrupt
                                                                         requests when FOF0 flag is asserted. */
    kLPADC_FIFO0WatermarkInterruptEnable = ADC_IE_FWMIE0_MASK,      /*!< Configures ADC to generate watermark interrupt
                                                                         requests when RDY0 flag is asserted. */
    kLPADC_ResultFIFOOverflowInterruptEnable = kLPADC_ResultFIFO0OverflowInterruptEnable, /*!< To compilitable with old
                                                                            version, do not recommend using this,
                                                                            please use
                                                                            #kLPADC_ResultFIFO0OverflowInterruptEnable
                                                                            as instead. */
    kLPADC_FIFOWatermarkInterruptEnable = kLPADC_FIFO0WatermarkInterruptEnable, /*!< To compilitable with old version,
                                                                                   do not recommend using this, please
                                                                                   use
                                                                                   #kLPADC_FIFO0WatermarkInterruptEnable
                                                                                   as instead. */

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    kLPADC_ResultFIFO1OverflowInterruptEnable = ADC_IE_FOFIE1_MASK, /*!< Configures ADC to generate overflow interrupt
                                                                         requests when FOF1 flag is asserted. */
    kLPADC_FIFO1WatermarkInterruptEnable = ADC_IE_FWMIE1_MASK,      /*!< Configures ADC to generate watermark interrupt
                                                                         requests when RDY1 flag is asserted. */
#endif /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U)) */

#if (defined(FSL_FEATURE_LPADC_HAS_IE_TEXC_IE) && (FSL_FEATURE_LPADC_HAS_IE_TEXC_IE == 1U))
    kLPADC_TriggerExceptionInterruptEnable = ADC_IE_TEXC_IE_MASK, /*!< Configures ADC to generate trigger exception
                                                                      interrupt. */
#endif /* (defined(FSL_FEATURE_LPADC_HAS_IE_TEXC_IE) && (FSL_FEATURE_LPADC_HAS_IE_TEXC_IE == 1U)) */

#if (defined(FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE) && (FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE == 1U))
    kLPADC_Trigger0CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 0UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 0 completion. */
    kLPADC_Trigger1CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 1UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 1 completion. */
    kLPADC_Trigger2CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 2UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 2 completion. */
    kLPADC_Trigger3CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 3UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 3 completion. */
    kLPADC_Trigger4CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 4UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 4 completion. */
    kLPADC_Trigger5CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 5UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 5 completion. */
    kLPADC_Trigger6CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 6UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 6 completion. */
    kLPADC_Trigger7CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 7UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 7 completion. */
    kLPADC_Trigger8CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 8UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 8 completion. */
    kLPADC_Trigger9CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 9UL),   /*!< Configures ADC to generate interrupt
                                                                                when trigger 9 completion. */
    kLPADC_Trigger10CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 10UL), /*!< Configures ADC to generate interrupt
                                                                              when trigger 10 completion. */
    kLPADC_Trigger11CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 11UL), /*!< Configures ADC to generate interrupt
                                                                              when trigger 11 completion. */
    kLPADC_Trigger12CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 12UL), /*!< Configures ADC to generate interrupt
                                                                              when trigger 12 completion. */
    kLPADC_Trigger13CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 13UL), /*!< Configures ADC to generate interrupt
                                                                              when trigger 13 completion. */
    kLPADC_Trigger14CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 14UL), /*!< Configures ADC to generate interrupt
                                                                              when trigger 14 completion. */
    kLPADC_Trigger15CompletionInterruptEnable = ADC_IE_TCOMP_IE(1UL << 15UL), /*!< Configures ADC to generate interrupt
                                                                              when trigger 15 completion. */
#endif /* #if (defined(FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE) && (FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE == 1U)) */
};

#if (defined(FSL_FEATURE_LPADC_HAS_TSTAT) && (FSL_FEATURE_LPADC_HAS_TSTAT))
/*!
 * @brief The enumerator of lpadc trigger status flags, including interrupted flags and completed flags.
 *
 * Note: LPADC of different chips supports different number of trigger sources,
 * please check the Reference Manual for details.
 */
enum _lpadc_trigger_status_flags
{
    kLPADC_Trigger0InterruptedFlag  = 1UL << 0UL,  /*!< Trigger 0 is interrupted by a high priority exception. */
    kLPADC_Trigger1InterruptedFlag  = 1UL << 1UL,  /*!< Trigger 1 is interrupted by a high priority exception. */
    kLPADC_Trigger2InterruptedFlag  = 1UL << 2UL,  /*!< Trigger 2 is interrupted by a high priority exception. */
    kLPADC_Trigger3InterruptedFlag  = 1UL << 3UL,  /*!< Trigger 3 is interrupted by a high priority exception. */
    kLPADC_Trigger4InterruptedFlag  = 1UL << 4UL,  /*!< Trigger 4 is interrupted by a high priority exception. */
    kLPADC_Trigger5InterruptedFlag  = 1UL << 5UL,  /*!< Trigger 5 is interrupted by a high priority exception. */
    kLPADC_Trigger6InterruptedFlag  = 1UL << 6UL,  /*!< Trigger 6 is interrupted by a high priority exception. */
    kLPADC_Trigger7InterruptedFlag  = 1UL << 7UL,  /*!< Trigger 7 is interrupted by a high priority exception. */
    kLPADC_Trigger8InterruptedFlag  = 1UL << 8UL,  /*!< Trigger 8 is interrupted by a high priority exception. */
    kLPADC_Trigger9InterruptedFlag  = 1UL << 9UL,  /*!< Trigger 9 is interrupted by a high priority exception. */
    kLPADC_Trigger10InterruptedFlag = 1UL << 10UL, /*!< Trigger 10 is interrupted by a high priority exception. */
    kLPADC_Trigger11InterruptedFlag = 1UL << 11UL, /*!< Trigger 11 is interrupted by a high priority exception. */
    kLPADC_Trigger12InterruptedFlag = 1UL << 12UL, /*!< Trigger 12 is interrupted by a high priority exception. */
    kLPADC_Trigger13InterruptedFlag = 1UL << 13UL, /*!< Trigger 13 is interrupted by a high priority exception. */
    kLPADC_Trigger14InterruptedFlag = 1UL << 14UL, /*!< Trigger 14 is interrupted by a high priority exception. */
    kLPADC_Trigger15InterruptedFlag = 1UL << 15UL, /*!< Trigger 15 is interrupted by a high priority exception. */

    kLPADC_Trigger0CompletedFlag = 1UL << 16UL,    /*!< Trigger 0 is completed and
                                                       trigger 0 has enabled completion interrupts. */
    kLPADC_Trigger1CompletedFlag = 1UL << 17UL,    /*!< Trigger 1 is completed and
                                                       trigger 1 has enabled completion interrupts. */
    kLPADC_Trigger2CompletedFlag = 1UL << 18UL,    /*!< Trigger 2 is completed and
                                                       trigger 2 has enabled completion interrupts. */
    kLPADC_Trigger3CompletedFlag = 1UL << 19UL,    /*!< Trigger 3 is completed and
                                                       trigger 3 has enabled completion interrupts. */
    kLPADC_Trigger4CompletedFlag = 1UL << 20UL,    /*!< Trigger 4 is completed and
                                                       trigger 4 has enabled completion interrupts. */
    kLPADC_Trigger5CompletedFlag = 1UL << 21UL,    /*!< Trigger 5 is completed and
                                                       trigger 5 has enabled completion interrupts. */
    kLPADC_Trigger6CompletedFlag = 1UL << 22UL,    /*!< Trigger 6 is completed and
                                                       trigger 6 has enabled completion interrupts. */
    kLPADC_Trigger7CompletedFlag = 1UL << 23UL,    /*!< Trigger 7 is completed and
                                                       trigger 7 has enabled completion interrupts. */
    kLPADC_Trigger8CompletedFlag = 1UL << 24UL,    /*!< Trigger 8 is completed and
                                                       trigger 8 has enabled completion interrupts. */
    kLPADC_Trigger9CompletedFlag = 1UL << 25UL,    /*!< Trigger 9 is completed and
                                                       trigger 9 has enabled completion interrupts. */
    kLPADC_Trigger10CompletedFlag = 1UL << 26UL,   /*!< Trigger 10 is completed and
                                                      trigger 10 has enabled completion interrupts. */
    kLPADC_Trigger11CompletedFlag = 1UL << 27UL,   /*!< Trigger 11 is completed and
                                                      trigger 11 has enabled completion interrupts. */
    kLPADC_Trigger12CompletedFlag = 1UL << 28UL,   /*!< Trigger 12 is completed and
                                                      trigger 12 has enabled completion interrupts. */
    kLPADC_Trigger13CompletedFlag = 1UL << 29UL,   /*!< Trigger 13 is completed and
                                                      trigger 13 has enabled completion interrupts. */
    kLPADC_Trigger14CompletedFlag = 1UL << 30UL,   /*!< Trigger 14 is completed and
                                                      trigger 14 has enabled completion interrupts. */
    kLPADC_Trigger15CompletedFlag = 1UL << 31UL,   /*!< Trigger 15 is completed and
                                                      trigger 15 has enabled completion interrupts. */
};
#endif /* (defined(FSL_FEATURE_LPADC_HAS_TSTAT) && (FSL_FEATURE_LPADC_HAS_TSTAT)) */

/*!
 * @brief Define enumeration of sample scale mode.
 *
 * The sample scale mode is used to reduce the selected ADC analog channel input voltage level by a factor. The maximum
 * possible voltage on the ADC channel input should be considered when selecting a scale mode to ensure that the
 * reducing factor always results voltage level at or below the VREFH reference. This reducing capability allows
 * conversion of analog inputs higher than VREFH. A-side and B-side channel inputs are both scaled using the scale mode.
 */
typedef enum _lpadc_sample_scale_mode
{
    kLPADC_SamplePartScale = 0U, /*!< Use divided input voltage signal.
                                    (For scale select,please refer to the reference manual). */
    kLPADC_SampleFullScale = 1U, /*!< Full scale (Factor of 1). */
} lpadc_sample_scale_mode_t;

/*!
 * @brief Define enumeration of channel sample mode.
 *
 * The channel sample mode configures the channel with single-end/differential/dual-single-end, side A/B.
 */
typedef enum _lpadc_sample_channel_mode
{
    kLPADC_SampleChannelSingleEndSideA = 0x0U, /*!< Single-end mode, only A-side channel is converted. */
#if !(defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 0U))
    kLPADC_SampleChannelSingleEndSideB = 0x1U, /*!< Single-end mode, only B-side channel is converted. */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_DIFF) && FSL_FEATURE_LPADC_HAS_CMDL_DIFF
    kLPADC_SampleChannelDiffBothSideAB = 0x2U, /*!< Differential mode, the ADC result is (CHnA-CHnB). */
    kLPADC_SampleChannelDiffBothSideBA = 0x3U, /*!< Differential mode, the ADC result is (CHnB-CHnA). */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CMDL_DIFF) && FSL_FEATURE_LPADC_HAS_CMDL_DIFF */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_CTYPE) && FSL_FEATURE_LPADC_HAS_CMDL_CTYPE
    kLPADC_SampleChannelDiffBothSide          = 0x02U, /*!< Differential mode, the ADC result is (CHnA-CHnB). */
    kLPADC_SampleChannelDualSingleEndBothSide = 0x03U, /*!< Dual-Single-Ended Mode. Both A side and B side
                                                            channels are converted independently. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CMDL_CTYPE) && FSL_FEATURE_LPADC_HAS_CMDL_CTYPE */
#endif /* !(defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 0U)) */
} lpadc_sample_channel_mode_t;

/*!
 * @brief Define enumeration of hardware average selection.
 *
 * It Selects how many ADC conversions are averaged to create the ADC result. An internal storage buffer is used to
 * capture temporary results while the averaging iterations are executed.
 *
 * @note Some enumerator values are not available on some devices, mainly depends on the size of AVGS field in CMDH
 * register.
 */
typedef enum _lpadc_hardware_average_mode
{
    kLPADC_HardwareAverageCount1   = 0U, /*!< Single conversion. */
    kLPADC_HardwareAverageCount2   = 1U, /*!< 2 conversions averaged. */
    kLPADC_HardwareAverageCount4   = 2U, /*!< 4 conversions averaged. */
    kLPADC_HardwareAverageCount8   = 3U, /*!< 8 conversions averaged. */
    kLPADC_HardwareAverageCount16  = 4U, /*!< 16 conversions averaged. */
    kLPADC_HardwareAverageCount32  = 5U, /*!< 32 conversions averaged. */
    kLPADC_HardwareAverageCount64  = 6U, /*!< 64 conversions averaged. */
    kLPADC_HardwareAverageCount128 = 7U, /*!< 128 conversions averaged. */
#if (defined(FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH) && \
     (FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH == 4U))
    kLPADC_HardwareAverageCount256  = 8U,  /*!< 256 conversions averaged. */
    kLPADC_HardwareAverageCount512  = 9U,  /*!< 512 conversions averaged. */
    kLPADC_HardwareAverageCount1024 = 10U, /*!< 1024 conversions averaged. */
#endif                                     /*  (defined(FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH) && \
                                               (FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH == 4U))*/
} lpadc_hardware_average_mode_t;

/*!
 * @brief Define enumeration of sample time selection.
 *
 * The shortest sample time maximizes conversion speed for lower impedance inputs. Extending sample time allows higher
 * impedance inputs to be accurately sampled. Longer sample times can also be used to lower overall power consumption
 * when command looping and sequencing is configured and high conversion rates are not required.
 */
typedef enum _lpadc_sample_time_mode
{
    kLPADC_SampleTimeADCK3   = 0U, /*!< 3 ADCK cycles total sample time. */
    kLPADC_SampleTimeADCK5   = 1U, /*!< 5 ADCK cycles total sample time. */
    kLPADC_SampleTimeADCK7   = 2U, /*!< 7 ADCK cycles total sample time. */
    kLPADC_SampleTimeADCK11  = 3U, /*!< 11 ADCK cycles total sample time. */
    kLPADC_SampleTimeADCK19  = 4U, /*!< 19 ADCK cycles total sample time. */
    kLPADC_SampleTimeADCK35  = 5U, /*!< 35 ADCK cycles total sample time. */
    kLPADC_SampleTimeADCK67  = 6U, /*!< 69 ADCK cycles total sample time. */
    kLPADC_SampleTimeADCK131 = 7U, /*!< 131 ADCK cycles total sample time. */
} lpadc_sample_time_mode_t;

/*!
 * @brief Define enumeration of hardware compare mode.
 *
 * After an ADC channel input is sampled and converted and any averaging iterations are performed, this mode setting
 * guides operation of the automatic compare function to optionally only store when the compare operation is true.
 * When compare is enabled, the conversion result is compared to the compare values.
 */
typedef enum _lpadc_hardware_compare_mode
{
    kLPADC_HardwareCompareDisabled        = 0U, /*!< Compare disabled. */
    kLPADC_HardwareCompareStoreOnTrue     = 2U, /*!< Compare enabled. Store on true. */
    kLPADC_HardwareCompareRepeatUntilTrue = 3U, /*!< Compare enabled. Repeat channel acquisition until true. */
} lpadc_hardware_compare_mode_t;

#if defined(FSL_FEATURE_LPADC_HAS_CMDL_MODE) && FSL_FEATURE_LPADC_HAS_CMDL_MODE
/*!
 * @brief Define enumeration of conversion resolution mode.
 *
 * Configure the resolution bit in specific conversion type. For detailed resolution accuracy, see to
 * #lpadc_sample_channel_mode_t
 */
typedef enum _lpadc_conversion_resolution_mode
{
    kLPADC_ConversionResolutionStandard = 0U, /*!< Standard resolution. Single-ended 12-bit conversion, Differential
                                                   13-bit conversion with 2's complement output. */
    kLPADC_ConversionResolutionHigh = 1U,     /*!< High resolution. Single-ended 16-bit conversion; Differential 16-bit
                                                   conversion with 2's complement output. */
} lpadc_conversion_resolution_mode_t;
#endif /* defined(FSL_FEATURE_LPADC_HAS_CMDL_MODE) && FSL_FEATURE_LPADC_HAS_CMDL_MODE */

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS
/*!
 * @brief Define enumeration of conversion averages mode.
 *
 * Configure the converion average number for auto-calibration.
 * @note Some enumerator values are not available on some devices, mainly depends on the size of CAL_AVGS field in CTRL
 * register.
 */
typedef enum _lpadc_conversion_average_mode
{
    kLPADC_ConversionAverage1   = 0U, /*!< Single conversion. */
    kLPADC_ConversionAverage2   = 1U, /*!< 2 conversions averaged. */
    kLPADC_ConversionAverage4   = 2U, /*!< 4 conversions averaged. */
    kLPADC_ConversionAverage8   = 3U, /*!< 8 conversions averaged. */
    kLPADC_ConversionAverage16  = 4U, /*!< 16 conversions averaged. */
    kLPADC_ConversionAverage32  = 5U, /*!< 32 conversions averaged. */
    kLPADC_ConversionAverage64  = 6U, /*!< 64 conversions averaged. */
    kLPADC_ConversionAverage128 = 7U, /*!< 128 conversions averaged. */
#if (defined(FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH) && \
     (FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH == 4U))
    kLPADC_ConversionAverage256  = 8U,  /*!< 256 conversions averaged. */
    kLPADC_ConversionAverage512  = 9U,  /*!< 512 conversions averaged. */
    kLPADC_ConversionAverage1024 = 10U, /*!< 1024 conversions averaged. */
#endif                                  /*  (defined(FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH) && \
                                            (FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH == 4U))*/
} lpadc_conversion_average_mode_t;
#endif /* defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS */

/*!
 * @brief Define enumeration of reference voltage source.
 *
 * For detail information, need to check the SoC's specification.
 */
typedef enum _lpadc_reference_voltage_mode
{
    kLPADC_ReferenceVoltageAlt1 = 0U, /*!< Option 1 setting. */
    kLPADC_ReferenceVoltageAlt2 = 1U, /*!< Option 2 setting. */
    kLPADC_ReferenceVoltageAlt3 = 2U, /*!< Option 3 setting. */
} lpadc_reference_voltage_source_t;

/*!
 * @brief Define enumeration of power configuration.
 *
 * Configures the ADC for power and performance. In the highest power setting the highest conversion rates will be
 * possible. Refer to the device data sheet for power and performance capabilities for each setting.
 */
typedef enum _lpadc_power_level_mode
{
    kLPADC_PowerLevelAlt1 = 0U, /*!< Lowest power setting. */
    kLPADC_PowerLevelAlt2 = 1U, /*!< Next lowest power setting. */
    kLPADC_PowerLevelAlt3 = 2U, /*!< ... */
    kLPADC_PowerLevelAlt4 = 3U, /*!< Highest power setting. */
} lpadc_power_level_mode_t;

#if (defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE)
/*!
 * @brief Define enumeration of offset calibration mode.
 *
 */
typedef enum _lpadc_offset_calibration_mode
{
    kLPADC_OffsetCalibration12bitMode = 0U, /*!< 12 bit offset calibration mode. */
    kLPADC_OffsetCalibration16bitMode = 1U, /*!< 16 bit offset calibration mode. */
} lpadc_offset_calibration_mode_t;
#endif                                      /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE */

/*!
 * @brief Define enumeration of trigger priority policy.
 *
 * This selection controls how higher priority triggers are handled.
 * @note \b kLPADC_TriggerPriorityPreemptSubsequently is not available on some devices, mainly depends on the size of
 * TPRICTRL field in CFG register.
 */
typedef enum _lpadc_trigger_priority_policy
{
    kLPADC_ConvPreemptImmediatelyNotAutoResumed = 0x0U, /*!< If a higher priority trigger is detected during command
                                                        processing, the current conversion is aborted and the new
                                                        command specified by the trigger is started, when higher
                                                        priority conversion finishes, the preempted conversion is not
                                                        automatically resumed or restarted. */
    kLPADC_ConvPreemptSoftlyNotAutoResumed = 0x1U,      /*!< If a higher priority trigger is received during command
                                                    processing, the current conversion is completed (including averaging
                                                    iterations and compare function if enabled) and stored to the result
                                                    FIFO before the higher priority trigger/command is initiated, when
                                                    higher priority conversion finishes, the preempted conversion is not
                                                    resumed or restarted. */

#if defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES
    kLPADC_ConvPreemptImmediatelyAutoRestarted = 0x4U, /*!< If a higher priority trigger is detected during command
                                                       processing, the current conversion is aborted and the new
                                                       command specified by the trigger is started, when higher
                                                       priority conversion finishes, the preempted conversion will
                                                       automatically be restarted. */
    kLPADC_ConvPreemptSoftlyAutoRestarted = 0x5U,      /*!< If a higher priority trigger is received during command
                                                       processing, the current conversion is completed (including averaging
                                                       iterations and compare function if enabled) and stored to the result
                                                       FIFO before the higher priority trigger/command is initiated, when
                                                       higher priority conversion finishes, the preempted conversion will
                                                       automatically be restarted. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES */

#if defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES
    kLPADC_ConvPreemptImmediatelyAutoResumed = 0xCU, /*!< If a higher priority trigger is detected during command
                                                     processing, the current conversion is aborted and the new
                                                     command specified by the trigger is started, when higher
                                                     priority conversion finishes, the preempted conversion will
                                                     automatically be resumed. */
    kLPADC_ConvPreemptSoftlyAutoResumed = 0xDU,      /*!< If a higher priority trigger is received during command
                                                      processing, the current conversion is completed (including averaging
                                                      iterations and compare function if enabled) and stored to the result
                                                      FIFO before the higher priority trigger/command is initiated, when
                                                      higher priority conversion finishes, the preempted conversion will
                                                      be automatically be resumed. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES */

    kLPADC_TriggerPriorityPreemptImmediately =
        kLPADC_ConvPreemptImmediatelyNotAutoResumed, /*!< Legacy support is not recommended as it only ensures
                                                        compatibility with older versions. */
    kLPADC_TriggerPriorityPreemptSoftly =
        kLPADC_ConvPreemptSoftlyNotAutoResumed, /*!< Legacy support is not recommended as it only ensures compatibility
                                                   with older versions. */

#if (defined(FSL_FEATURE_LPADC_CFG_TPRICTRL_BITFIELD_WIDTH) && (FSL_FEATURE_LPADC_CFG_TPRICTRL_BITFIELD_WIDTH == 2U))
    kLPADC_ConvPreemptSubsequentlyNotAutoResumed = 0x2U, /*!< If a higher priority trigger is received during command
                                                 processing, the current command will be completed (averaging,
                                                 looping, compare) before servicing the higher priority trigger, when
                                                 higher priority conversion finishes, the preempted conversion will
                                                 not automatically be restarted or resumed. */

#if defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES
    kLPADC_ConvPreemptSubsequentlyAutoRestarted = 0x6U, /*!< If a higher priority trigger is received during command
                                                processing, the current command will be completed (averaging,
                                                looping, compare) before servicing the higher priority trigger, when
                                                higher priority conversion finishes, the preempted conversion will
                                                be automatically restarted. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TRES) && FSL_FEATURE_LPADC_HAS_CFG_TRES */

#if defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES
    kLPADC_ConvPreemptSubsequentlyAutoResumed = 0xEU, /*!< If a higher priority trigger is received during command
                                              processing, the current command will be completed (averaging,
                                              looping, compare) before servicing the higher priority trigger, when
                                              higher priority conversion finishes, the preempted conversion will
                                              be automatically resumed. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_TCMDRES) && FSL_FEATURE_LPADC_HAS_CFG_TCMDRES */

    kLPADC_TriggerPriorityPreemptSubsequently =
        kLPADC_ConvPreemptSubsequentlyNotAutoResumed, /*!< Legacy support is not recommended as it only ensures
                                                         compatibility with older versions. */
#endif /* #if (defined(FSL_FEATURE_LPADC_CFG_TPRICTRL_BITFIELD_WIDTH) && \
          (FSL_FEATURE_LPADC_CFG_TPRICTRL_BITFIELD_WIDTH == 2U)) */

#if defined(FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI) && FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI
    kLPADC_TriggerPriorityExceptionDisabled = 0x10U, /*!<  High priority trigger exception disabled. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI) && FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI */
} lpadc_trigger_priority_policy_t;

#if ((defined(FSL_FEATURE_LPADC_HAS_CTRL_CALHS)) && FSL_FEATURE_LPADC_HAS_CTRL_CALHS)
/*!
 * @brief Define enumeration of tune value.
 */
typedef enum _lpadc_tune_value
{
    kLPADC_TuneValue0 = 0U, /*!< Tune value 0. */
    kLPADC_TuneValue1 = 1U, /*!< Tune value 1. */
    kLPADC_TuneValue2 = 2U, /*!< Tune value 2. */
    kLPADC_TuneValue3 = 3U, /*!< Tune value 3. */
} lpadc_tune_value_t;
#endif                      /* ((defined(FSL_FEATURE_LPADC_HAS_CTRL_CALHS)) && FSL_FEATURE_LPADC_HAS_CTRL_CALHS) */

/*!
 * @brief LPADC global configuration.
 *
 * This structure would used to keep the settings for initialization.
 */
typedef struct
{
#if defined(FSL_FEATURE_LPADC_HAS_CFG_ADCKEN) && FSL_FEATURE_LPADC_HAS_CFG_ADCKEN
    bool enableInternalClock;   /*!< Enables the internally generated clock source. The clock source is used in clock
                                     selection logic at the chip level and is optionally used for the ADC clock source. */
#endif                          /* FSL_FEATURE_LPADC_HAS_CFG_ADCKEN */
#if defined(FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG) && FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG
    bool enableVref1LowVoltage; /*!< If voltage reference option1 input is below 1.8V, it should be "true".
                                     If voltage reference option1 input is above 1.8V, it should be "false". */
#endif                          /* FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG */
    bool enableInDozeMode; /*!< Control system transition to Stop and Wait power modes while ADC is converting. When
                                enabled in Doze mode, immediate entries to Wait or Stop are allowed. When disabled, the
                                ADC will wait for the current averaging iteration/FIFO storage to complete before
                                acknowledging stop or wait mode entry. */
#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS
    lpadc_conversion_average_mode_t conversionAverageMode; /*!< Auto-Calibration Averages. */
#endif                                                     /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS */
    bool enableAnalogPreliminary; /*!< ADC analog circuits are pre-enabled and ready to execute conversions without
                                       startup delays(at the cost of higher DC current consumption). */
    uint32_t powerUpDelay; /*!< When the analog circuits are not pre-enabled, the ADC analog circuits are only powered
                                while the ADC is active and there is a counted delay defined by this field after an
                                initial trigger transitions the ADC from its Idle state to allow time for the analog
                                circuits to stabilize. The startup delay count of (powerUpDelay * 4) ADCK cycles must
                                result in a longer delay than the analog startup time. */
    lpadc_reference_voltage_source_t referenceVoltageSource; /*!< Selects the voltage reference high used for
                                                                  conversions.*/

#if defined(FSL_FEATURE_LPADC_HAS_CFG_PWRSEL) && (FSL_FEATURE_LPADC_HAS_CFG_PWRSEL == 1U)
    lpadc_power_level_mode_t powerLevelMode; /*!< Power Configuration Selection. */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_PWRSEL) && (FSL_FEATURE_LPADC_HAS_CFG_PWRSEL == 1U) */
    lpadc_trigger_priority_policy_t triggerPriorityPolicy; /*!< Control how higher priority triggers are handled, see to
                                                                lpadc_trigger_priority_policy_t. */
    bool enableConvPause; /*!< Enables the ADC pausing function. When enabled, a programmable delay is inserted during
                               command execution sequencing between LOOP iterations, between commands in a sequence, and
                               between conversions when command is executing in "Compare Until True" configuration. */
    uint32_t convPauseDelay; /*!< Controls the duration of pausing during command execution sequencing. The pause delay
                                  is a count of (convPauseDelay*4) ADCK cycles. Only available when ADC pausing
                                  function is enabled. The available value range is in 9-bit. */
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
    /* for FIFO0. */
    uint32_t FIFO0Watermark; /*!< FIFO0Watermark is a programmable threshold setting. When the number of datawords
                                stored in the ADC Result FIFO0 is greater than the value in this field, the ready flag
                                would be asserted to indicate stored data has reached the programmable threshold. */
    /* for FIFO1. */
    uint32_t FIFO1Watermark; /*!< FIFO1Watermark is a programmable threshold setting. When the number of datawords
                                stored in the ADC Result FIFO1 is greater than the value in this field, the ready flag
                                would be asserted to indicate stored data has reached the programmable threshold. */
#else
    /* for FIFO. */
    uint32_t FIFOWatermark; /*!< FIFOWatermark is a programmable threshold setting. When the number of datawords stored
                                 in the ADC Result FIFO is greater than the value in this field, the ready flag would be
                                 asserted to indicate stored data has reached the programmable threshold. */
#endif                       /* FSL_FEATURE_LPADC_FIFO_COUNT */
#if (defined(FSL_FEATURE_LPADC_HAS_TSTAT) && (FSL_FEATURE_LPADC_HAS_TSTAT))

#endif /* FSL_FEATURE_LPADC_HAS_TSTAT */
} lpadc_config_t;

/*!
 * @brief Define structure to keep the configuration for conversion command.
 */
typedef struct
{
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_CSCALE) && FSL_FEATURE_LPADC_HAS_CMDL_CSCALE
    lpadc_sample_scale_mode_t sampleScaleMode;     /*!< Sample scale mode. */
#endif                                             /* FSL_FEATURE_LPADC_HAS_CMDL_CSCALE */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE) && FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE
    lpadc_sample_scale_mode_t channelBScaleMode;   /*!< Alternate channe B Scale mode. */
#endif                                             /* FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE */
    lpadc_sample_channel_mode_t sampleChannelMode; /*!< Channel sample mode. */
    uint32_t channelNumber;                        /*!< Channel number, select the channel or channel pair. */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH) && FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH
    uint32_t channelBNumber;                       /*!< Alternate Channel B number, select the channel. */
#endif
    uint32_t chainedNextCommandNumber; /*!< Selects the next command to be executed after this command completes.
                                            1-15 is available, 0 is to terminate the chain after this command. */
    bool enableAutoChannelIncrement;   /*!< Loop with increment: when disabled, the "loopCount" field selects the number
                                            of times the selected channel is converted consecutively; when enabled, the
                                            "loopCount" field defines how many consecutive channels are converted as part
                                            of the command execution. */
    uint32_t loopCount; /*!< Selects how many times this command executes before finish and transition to the next
                             command or Idle state. Command executes LOOP+1 times.  0-15 is available. */
    lpadc_hardware_average_mode_t hardwareAverageMode; /*!< Hardware average selection. */
    lpadc_sample_time_mode_t sampleTimeMode;           /*!< Sample time selection. */

    lpadc_hardware_compare_mode_t hardwareCompareMode; /*!< Hardware compare selection. */
    uint32_t hardwareCompareValueHigh; /*!< Compare Value High. The available value range is in 16-bit. */
    uint32_t hardwareCompareValueLow;  /*!< Compare Value Low. The available value range is in 16-bit. */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_MODE) && FSL_FEATURE_LPADC_HAS_CMDL_MODE
    lpadc_conversion_resolution_mode_t conversionResolutionMode; /*!< Conversion resolution mode. */
#endif                                                           /* FSL_FEATURE_LPADC_HAS_CMDL_MODE */
#if defined(FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG) && FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG
    bool enableWaitTrigger; /*!< Wait for trigger assertion before execution: when disabled, this command will be
                                 automatically executed; when enabled, the active trigger must be asserted again before
                                 executing this command. */
#endif                      /* FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG */
#if defined(FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN) && FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN
    bool enableChannelB;    /*! Enable alternate Channel B */
#endif                      /* FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN */
} lpadc_conv_command_config_t;

/*!
 * @brief Define structure to keep the configuration for conversion trigger.
 */
typedef struct
{
    uint32_t targetCommandId; /*!< Select the command from command buffer to execute upon detect of the associated
                                   trigger event. */
    uint32_t delayPower;      /*!< Select the trigger delay duration to wait at the start of servicing a trigger event.
                                   When this field is clear, then no delay is incurred. When this field is set to a non-zero
                                   value, the duration for the delay is 2^delayPower ADCK cycles. The available value range
                                   is 4-bit. */
    uint32_t priority; /*!< Sets the priority of the associated trigger source. If two or more triggers have the same
                            priority level setting, the lower order trigger event has the higher priority. The lower
                            value for this field is for the higher priority, the available value range is 1-bit. */
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
    uint8_t channelAFIFOSelect; /* SAR Result Destination For Channel A. */
    uint8_t channelBFIFOSelect; /* SAR Result Destination For Channel B. */
#endif                          /* FSL_FEATURE_LPADC_FIFO_COUNT */
    bool enableHardwareTrigger; /*!< Enable hardware trigger source to initiate conversion on the rising edge of the
                                     input trigger source or not. THe software trigger is always available. */
} lpadc_conv_trigger_config_t;

/*!
 * @brief Define the structure to keep the conversion result.
 */
typedef struct
{
    uint32_t commandIdSource; /*!< Indicate the command buffer being executed that generated this result. */
    uint32_t loopCountIndex;  /*!< Indicate the loop count value during command execution that generated this result. */
    uint32_t triggerIdSource; /*!< Indicate the trigger source that initiated a conversion and generated this result. */
    uint16_t convValue;       /*!< Data result. */
} lpadc_conv_result_t;

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFS) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFS
/*!
 * @brief A structure of calibration value.
 */
typedef struct _lpadc_calibration_value
{
    /* gain calibration result. */
    uint16_t gainCalibrationResultA;
#if !(defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 0U))
    uint16_t gainCalibrationResultB;
#endif /* !(defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 0U)) */
#if (defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ)
    /* general calibration value. */
    uint16_t generalCalibrationValueA[33U];
#if !(defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 0U))
    uint16_t generalCalibrationValueB[33U];
#endif /* !(defined(FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS) && (FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS == 0U)) */
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */
} lpadc_calibration_value_t;
#endif /* FSL_FEATURE_LPADC_HAS_CTRL_CALOFS */

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name Initialization & de-initialization.
 * @{
 */

/*!
 * @brief Initializes the LPADC module.
 *
 * @param base   LPADC peripheral base address.
 * @param config Pointer to configuration structure. See "lpadc_config_t".
 */
void LPADC_Init(ADC_Type *base, const lpadc_config_t *config);

/*!
 * @brief Gets an available pre-defined settings for initial configuration.
 *
 * This function initializes the converter configuration structure with an available settings. The default values are:
 * @code
 *   config->enableInDozeMode        = true;
 *   config->enableAnalogPreliminary = false;
 *   config->powerUpDelay            = 0x80;
 *   config->referenceVoltageSource  = kLPADC_ReferenceVoltageAlt1;
 *   config->powerLevelMode          = kLPADC_PowerLevelAlt1;
 *   config->triggerPriorityPolicy   = kLPADC_TriggerPriorityPreemptImmediately;
 *   config->enableConvPause         = false;
 *   config->convPauseDelay          = 0U;
 *   config->FIFOWatermark           = 0U;
 * @endcode
 * @param config Pointer to configuration structure.
 */
void LPADC_GetDefaultConfig(lpadc_config_t *config);

/*!
 * @brief De-initializes the LPADC module.
 *
 * @param base LPADC peripheral base address.
 */
void LPADC_Deinit(ADC_Type *base);

/*!
 * @brief Switch on/off the LPADC module.
 *
 * @param base LPADC peripheral base address.
 * @param enable switcher to the module.
 */
static inline void LPADC_Enable(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= ADC_CTRL_ADCEN_MASK;
    }
    else
    {
        base->CTRL &= ~ADC_CTRL_ADCEN_MASK;
    }
}

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
/*!
 * @brief Do reset the conversion FIFO0.
 *
 * @param base LPADC peripheral base address.
 */
static inline void LPADC_DoResetFIFO0(ADC_Type *base)
{
    base->CTRL |= ADC_CTRL_RSTFIFO0_MASK;
}

/*!
 * @brief Do reset the conversion FIFO1.
 *
 * @param base LPADC peripheral base address.
 */
static inline void LPADC_DoResetFIFO1(ADC_Type *base)
{
    base->CTRL |= ADC_CTRL_RSTFIFO1_MASK;
}
#else

#if defined(ADC_CTRL_RSTFIFO0_MASK)
#define ADC_CTRL_RSTFIFO_MASK ADC_CTRL_RSTFIFO0_MASK
#endif /* defined(ADC_CTRL_RSTFIFO0_MASK) */
/*!
 * @brief Do reset the conversion FIFO.
 *
 * @param base LPADC peripheral base address.
 */
static inline void LPADC_DoResetFIFO(ADC_Type *base)
{
    base->CTRL |= ADC_CTRL_RSTFIFO_MASK;
}
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */

/*!
 * @brief Do reset the module's configuration.
 *
 * Reset all ADC internal logic and registers, except the Control Register (ADCx_CTRL).
 *
 * @param base LPADC peripheral base address.
 */
static inline void LPADC_DoResetConfig(ADC_Type *base)
{
    base->CTRL |= ADC_CTRL_RST_MASK;
    base->CTRL &= ~ADC_CTRL_RST_MASK;
}

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Get status flags.
 *
 * @param base LPADC peripheral base address.
 * @return status flags' mask. See to #_lpadc_status_flags.
 */
static inline uint32_t LPADC_GetStatusFlags(ADC_Type *base)
{
    return base->STAT;
}

/*!
 * @brief Clear status flags.
 *
 * Only the flags can be cleared by writing ADCx_STATUS register would be cleared by this API.
 *
 * @param base LPADC peripheral base address.
 * @param mask Mask value for flags to be cleared. See to #_lpadc_status_flags.
 */
static inline void LPADC_ClearStatusFlags(ADC_Type *base, uint32_t mask)
{
    base->STAT = mask;
}

#if (defined(FSL_FEATURE_LPADC_HAS_TSTAT) && FSL_FEATURE_LPADC_HAS_TSTAT)
/*!
 * @brief Get trigger status flags to indicate which trigger sequences have been completed or interrupted by a high
 * priority trigger exception.
 *
 * @param base LPADC peripheral base address.
 * @return The OR'ed value of @ref _lpadc_trigger_status_flags.
 */
static inline uint32_t LPADC_GetTriggerStatusFlags(ADC_Type *base)
{
    return base->TSTAT;
}

/*!
 * @brief Clear trigger status flags.
 *
 * @param base LPADC peripheral base address.
 * @param mask The mask of trigger status flags to be cleared, should be the
 *              OR'ed value of @ref _lpadc_trigger_status_flags.
 */
static inline void LPADC_ClearTriggerStatusFlags(ADC_Type *base, uint32_t mask)
{
    /* This assert used to avoid user use doesn't supported trigger sources. */
    assert(((mask & 0xFFFFU) == (mask & ADC_TSTAT_TEXC_NUM_MASK)) &&
           ((mask & 0xFFFF0000U) == (mask & ADC_TSTAT_TCOMP_FLAG_MASK)));
    base->TSTAT = mask;
}
#endif /* (defined(FSL_FEATURE_LPADC_HAS_TSTAT) && FSL_FEATURE_LPADC_HAS_TSTAT) */

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enable interrupts.
 *
 * @param base LPADC peripheral base address.
 * @param mask Mask value for interrupt events. See to #_lpadc_interrupt_enable.
 */
static inline void LPADC_EnableInterrupts(ADC_Type *base, uint32_t mask)
{
#if (defined(FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE) && (FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE == 1U))
    /* This assert used to avoid user use doesn't supported trigger sources. */
    assert((mask <= 0xFFFFU) || ((mask & 0xFFFF0000U) == (mask & ADC_IE_TCOMP_IE_MASK)));
#endif /* #if (defined(FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE) && (FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE == 1U)) */
    base->IE |= mask;
}

/*!
 * @brief Disable interrupts.
 *
 * @param base LPADC peripheral base address.
 * @param mask Mask value for interrupt events. See to #_lpadc_interrupt_enable.
 */
static inline void LPADC_DisableInterrupts(ADC_Type *base, uint32_t mask)
{
#if (defined(FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE) && (FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE == 1U))
    /* This assert used to avoid user use doesn't supported trigger sources. */
    assert((mask <= 0xFFFFU) || ((mask & 0xFFFF0000U) == (mask & ADC_IE_TCOMP_IE_MASK)));
#endif /* #if (defined(FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE) && (FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE == 1U)) */
    base->IE &= ~mask;
}

/*!
 * @name DMA Control
 * @{
 */

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
/*!
 * @brief Switch on/off the DMA trigger for FIFO0 watermark event.
 *
 * @param base LPADC peripheral base address.
 * @param enable Switcher to the event.
 */
static inline void LPADC_EnableFIFO0WatermarkDMA(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->DE |= ADC_DE_FWMDE0_MASK;
    }
    else
    {
        base->DE &= ~ADC_DE_FWMDE0_MASK;
    }
}

/*!
 * @brief Switch on/off the DMA trigger for FIFO1 watermark event.
 *
 * @param base LPADC peripheral base address.
 * @param enable Switcher to the event.
 */
static inline void LPADC_EnableFIFO1WatermarkDMA(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->DE |= ADC_DE_FWMDE1_MASK;
    }
    else
    {
        base->DE &= ~ADC_DE_FWMDE1_MASK;
    }
}
#else
#if defined(ADC_DE_FWMDE0_MASK)
#define ADC_DE_FWMDE_MASK ADC_DE_FWMDE0_MASK
#endif /* defined(ADC_DE_FWMDE0_MASK) */
/*!
 * @brief Switch on/off the DMA trigger for FIFO watermark event.
 *
 * @param base LPADC peripheral base address.
 * @param enable Switcher to the event.
 */
static inline void LPADC_EnableFIFOWatermarkDMA(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->DE |= ADC_DE_FWMDE_MASK;
    }
    else
    {
        base->DE &= ~ADC_DE_FWMDE_MASK;
    }
}
#endif /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2)) */
/* @} */

/*!
 * @name Trigger and conversion with FIFO.
 * @{
 */

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2))
/*!
 * @brief Get the count of result kept in conversion FIFOn.
 *
 * @param base LPADC peripheral base address.
 * @param index Result FIFO index.
 * @return The count of result kept in conversion FIFOn.
 */
static inline uint32_t LPADC_GetConvResultCount(ADC_Type *base, uint8_t index)
{
    return (ADC_FCTRL_FCOUNT_MASK & base->FCTRL[index]) >> ADC_FCTRL_FCOUNT_SHIFT;
}

/*!
 * @brief Get the result in conversion FIFOn.
 *
 * @param base LPADC peripheral base address.
 * @param result Pointer to structure variable that keeps the conversion result in conversion FIFOn.
 * @param index Result FIFO index.
 *
 * @return Status whether FIFOn entry is valid.
 */
bool LPADC_GetConvResult(ADC_Type *base, lpadc_conv_result_t *result, uint8_t index);

/*!
 * @brief Get the result in conversion FIFOn using blocking method.
 *
 * @param base LPADC peripheral base address.
 * @param result Pointer to structure variable that keeps the conversion result in conversion FIFOn.
 * @param index Result FIFO index.
 */
void LPADC_GetConvResultBlocking(ADC_Type *base, lpadc_conv_result_t *result, uint8_t index);
#else  /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 1)) */
/*!
 * @brief Get the count of result kept in conversion FIFO.
 *
 * @param base LPADC peripheral base address.
 * @return The count of result kept in conversion FIFO.
 */
static inline uint32_t LPADC_GetConvResultCount(ADC_Type *base)
{
    return (ADC_FCTRL_FCOUNT_MASK & base->FCTRL) >> ADC_FCTRL_FCOUNT_SHIFT;
}

/*!
 * @brief Get the result in conversion FIFO.
 *
 * @param base LPADC peripheral base address.
 * @param result Pointer to structure variable that keeps the conversion result in conversion FIFO.
 *
 * @return Status whether FIFO entry is valid.
 */
bool LPADC_GetConvResult(ADC_Type *base, lpadc_conv_result_t *result);

/*!
 * @brief Get the result in conversion FIFO using blocking method.
 *
 * @param base LPADC peripheral base address.
 * @param result Pointer to structure variable that keeps the conversion result in conversion FIFO.
 */
void LPADC_GetConvResultBlocking(ADC_Type *base, lpadc_conv_result_t *result);
#endif /* (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2)) */

/*!
 * @brief Configure the conversion trigger source.
 *
 * Each programmable trigger can launch the conversion command in command buffer.
 *
 * @param base LPADC peripheral base address.
 * @param triggerId ID for each trigger. Typically, the available value range is from 0.
 * @param config Pointer to configuration structure. See to #lpadc_conv_trigger_config_t.
 */
void LPADC_SetConvTriggerConfig(ADC_Type *base, uint32_t triggerId, const lpadc_conv_trigger_config_t *config);

/*!
 * @brief Gets an available pre-defined settings for trigger's configuration.
 *
 * This function initializes the trigger's configuration structure with an available settings. The default values are:
 * @code
 *   config->targetCommandId        = 0U;
 *   config->delayPower             = 0U;
 *   config->priority               = 0U;
 *   config->channelAFIFOSelect     = 0U;
 *   config->channelBFIFOSelect     = 0U;
 *   config->enableHardwareTrigger  = false;
 * @endcode
 * @param config Pointer to configuration structure.
 */
void LPADC_GetDefaultConvTriggerConfig(lpadc_conv_trigger_config_t *config);

/*!
 * @brief Do software trigger to conversion command.
 *
 * @param base LPADC peripheral base address.
 * @param triggerIdMask Mask value for software trigger indexes, which count from zero.
 */
static inline void LPADC_DoSoftwareTrigger(ADC_Type *base, uint32_t triggerIdMask)
{
    /* Writes to ADCx_SWTRIG register are ignored while ADCx_CTRL[ADCEN] is clear. */
    base->SWTRIG = triggerIdMask;
}

#if defined(FSL_FEATURE_LPADC_HAS_TCTRL_CMD_SEL) && FSL_FEATURE_LPADC_HAS_TCTRL_CMD_SEL
/*!
 * @brief Enable hardware trigger command selection.
 *
 * This function will use the hardware trigger command from ADC_ETC.The trigger command is then defined
 * by ADC hardware trigger command selection field in ADC_ETC- >TRIGx_CHAINy_z_n[CSEL].
 *
 * @param base LPADC peripheral base address.
 * @param triggerId ID for each trigger. Typically, the available value range is from 0.
 * @param enable  True to enable or flase to disable.
 */
static inline void LPADC_EnableHardwareTriggerCommandSelection(ADC_Type *base, uint32_t triggerId, bool enable)
{
    if (enable)
    {
        base->TCTRL[triggerId] |= ADC_TCTRL_CMD_SEL_MASK;
    }
    else
    {
        base->TCTRL[triggerId] &= ~ADC_TCTRL_CMD_SEL_MASK;
    }
}
#endif /* defined(FSL_FEATURE_LPADC_HAS_TCTRL_CMD_SEL) && FSL_FEATURE_LPADC_HAS_TCTRL_CMD_SEL*/

/*!
 * @brief Configure conversion command.

 * @note The number of compare value register on different chips is different, that is mean in some chips, some
 * command buffers do not have the compare functionality.
 *
 * @param base LPADC peripheral base address.
 * @param commandId ID for command in command buffer. Typically, the available value range is 1 - 15.
 * @param config Pointer to configuration structure. See to #lpadc_conv_command_config_t.
 */
void LPADC_SetConvCommandConfig(ADC_Type *base, uint32_t commandId, const lpadc_conv_command_config_t *config);

/*!
 * @brief Gets an available pre-defined settings for conversion command's configuration.
 *
 * This function initializes the conversion command's configuration structure with an available settings. The default
 * values are:
 * @code
 *   config->sampleScaleMode            = kLPADC_SampleFullScale;
 *   config->channelBScaleMode          = kLPADC_SampleFullScale;
 *   config->sampleChannelMode          = kLPADC_SampleChannelSingleEndSideA;
 *   config->channelNumber              = 0U;
 *   config->channelBNumber             = 0U;
 *   config->chainedNextCommandNumber   = 0U;
 *   config->enableAutoChannelIncrement = false;
 *   config->loopCount                  = 0U;
 *   config->hardwareAverageMode        = kLPADC_HardwareAverageCount1;
 *   config->sampleTimeMode             = kLPADC_SampleTimeADCK3;
 *   config->hardwareCompareMode        = kLPADC_HardwareCompareDisabled;
 *   config->hardwareCompareValueHigh   = 0U;
 *   config->hardwareCompareValueLow    = 0U;
 *   config->conversionResolutionMode   = kLPADC_ConversionResolutionStandard;
 *   config->enableWaitTrigger          = false;
 *   config->enableChannelB             = false;
 * @endcode
 * @param config Pointer to configuration structure.
 */
void LPADC_GetDefaultConvCommandConfig(lpadc_conv_command_config_t *config);

#if defined(FSL_FEATURE_LPADC_HAS_CFG_CALOFS) && FSL_FEATURE_LPADC_HAS_CFG_CALOFS
/*!
 * @brief Enable the calibration function.
 *
 * When CALOFS is set, the ADC is configured to perform a calibration function anytime the ADC executes
 * a conversion. Any channel selected is ignored and the value returned in the RESFIFO is a signed value
 * between -31 and 31. -32 is not a valid and is never a returned value. Software should copy the lower 6-
 * bits of the conversion result stored in the RESFIFO after a completed calibration conversion to the
 * OFSTRIM field. The OFSTRIM field is used in normal operation for offset correction.
 *
 * @param base LPADC peripheral base address.
 * @param enable switcher to the calibration function.
 */
void LPADC_EnableCalibration(ADC_Type *base, bool enable);
#if defined(FSL_FEATURE_LPADC_HAS_OFSTRIM) && FSL_FEATURE_LPADC_HAS_OFSTRIM
/*!
 * @brief Set proper offset value to trim ADC.
 *
 * To minimize the offset during normal operation, software should read the conversion result from
 * the RESFIFO calibration operation and write the lower 6 bits to the OFSTRIM register.
 *
 * @param base  LPADC peripheral base address.
 * @param value Setting offset value.
 */
static inline void LPADC_SetOffsetValue(ADC_Type *base, uint32_t value)
{
    base->OFSTRIM = (value & ADC_OFSTRIM_OFSTRIM_MASK) >> ADC_OFSTRIM_OFSTRIM_SHIFT;
}

/*!
 * @brief Do auto calibration.
 *
 * Calibration function should be executed before using converter in application. It used the software trigger and a
 * dummy conversion, get the offset and write them into the OFSTRIM register. It called some of functional API
 * including: -LPADC_EnableCalibration(...) -LPADC_LPADC_SetOffsetValue(...) -LPADC_SetConvCommandConfig(...)
 *   -LPADC_SetConvTriggerConfig(...)
 *
 * @param base  LPADC peripheral base address.
 */
void LPADC_DoAutoCalibration(ADC_Type *base);
#endif /* defined(FSL_FEATURE_LPADC_HAS_OFSTRIM) && FSL_FEATURE_LPADC_HAS_OFSTRIM */
#endif /* defined(FSL_FEATURE_LPADC_HAS_CFG_CALOFS) && FSL_FEATURE_LPADC_HAS_CFG_CALOFS */

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFS) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFS
#if defined(FSL_FEATURE_LPADC_HAS_OFSTRIM) && FSL_FEATURE_LPADC_HAS_OFSTRIM
#if defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) && (FSL_FEATURE_LPADC_OFSTRIM_COUNT == 1U)
/*!
 * @brief Set trim value for offset.
 *
 * @note For 16-bit conversions, each increment is 1/2 LSB resulting in a programmable offset range of -256 LSB to 255.5
 * LSB; For 12-bit conversions, each increment is 1/32 LSB resulting in a programmable offset range of -16 LSB to
 * 15.96875 LSB.
 *
 * @param base LPADC peripheral base address.
 * @param value Offset trim value, is a 10-bit signed value between -512 and 511.
 */
static inline void LPADC_SetOffsetValue(ADC_Type *base, int16_t value)
{
    base->OFSTRIM = ADC_OFSTRIM_OFSTRIM(value);
}

/*!
 * @brief Get trim value of offset.
 *
 * @param base LPADC peripheral base address.
 * @param pValue Pointer to the variable in type of int16_t to store offset value.
 */
static inline void LPADC_GetOffsetValue(ADC_Type *base, int16_t *pValue)
{
    assert(pValue != NULL);

    uint16_t ofstrim = (uint16_t)((base->OFSTRIM & (ADC_OFSTRIM_OFSTRIM_MASK)) >> ADC_OFSTRIM_OFSTRIM_SHIFT);

    if ((ofstrim & ADC_OFSTRIM_OFSTRIM_SIGN) != 0U)
    {
        /* If the sign bit is set, then set the other MSB. */
        ofstrim |= (uint16_t)(~ADC_OFSTRIM_OFSTRIM_MAX);
    }

    *pValue = (int16_t)ofstrim;
}
#elif (defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) && (FSL_FEATURE_LPADC_OFSTRIM_COUNT == 2U))
/*!
 * @brief Set proper offset value to trim ADC.
 *
 * Set the offset trim value for offset calibration manually.
 *
 * @param base  LPADC peripheral base address.
 * @param valueA Setting offset value A.
 * @param valueB Setting offset value B.
 * @note In normal adc sequence, the values are automatically calculated by LPADC_EnableOffsetCalibration.
 */
static inline void LPADC_SetOffsetValue(ADC_Type *base, int32_t valueA, int32_t valueB)
{
    base->OFSTRIM = ADC_OFSTRIM_OFSTRIM_A(valueA) | ADC_OFSTRIM_OFSTRIM_B(valueB);
}

/*!
 * @brief Get trim value of offset.
 *
 * @param base LPADC peripheral base address.
 * @param pValueA Pointer to the variable in type of int32_t to store offset A value.
 * @param pValueB Pointer to the variable in type of int32_t to store offset B value.
 */
static inline void LPADC_GetOffsetValue(ADC_Type *base, int32_t *pValueA, int32_t *pValueB)
{
    assert(pValueA != NULL);
    assert(pValueB != NULL);

    uint32_t ofstrimA = (base->OFSTRIM & (ADC_OFSTRIM_OFSTRIM_A_MASK)) >> ADC_OFSTRIM_OFSTRIM_A_SHIFT;
    uint32_t ofstrimB = (base->OFSTRIM & (ADC_OFSTRIM_OFSTRIM_B_MASK)) >> ADC_OFSTRIM_OFSTRIM_B_SHIFT;

    if ((ofstrimA & ADC_OFSTRIM_OFSTRIM_A_SIGN) != 0U)
    {
        /* If the sign bit is set, then set the other MSB. */
        ofstrimA |= (~ADC_OFSTRIM_OFSTRIM_A_MAX);
    }
    if ((ofstrimB & ADC_OFSTRIM_OFSTRIM_B_SIGN) != 0U)
    {
        /* If the sign bit is set, then set the other MSB. */
        ofstrimB |= (~ADC_OFSTRIM_OFSTRIM_B_MAX);
    }

    *pValueA = (int32_t)ofstrimA;
    *pValueB = (int32_t)ofstrimB;
}
#endif /* defined(FSL_FEATURE_LPADC_OFSTRIM_COUNT) */
#else  /* !(defined(FSL_FEATURE_LPADC_HAS_OFSTRIM) && FSL_FEATURE_LPADC_HAS_OFSTRIM) */
/*!
 * @brief Set proper offset value to trim 12 bit ADC conversion.
 *
 * Set the offset trim value for offset calibration manually.
 *
 * @param base  LPADC peripheral base address.
 * @param valueA Setting offset value A.
 * @param valueB Setting offset value B.
 * @note In normal adc sequence, the values are automatically calculated by LPADC_EnableOffsetCalibration.
 */
static inline void LPADC_SetOffset12BitValue(ADC_Type *base, uint32_t valueA, uint32_t valueB)
{
    base->OFSTRIM12 = ADC_OFSTRIM12_OFSTRIM_A(valueA) | ADC_OFSTRIM12_OFSTRIM_A(valueB);
}

/*!
 * @brief Set proper offset value to trim 16 bit ADC conversion.
 *
 * Set the offset trim value for offset calibration manually.
 *
 * @param base  LPADC peripheral base address.
 * @param valueA Setting offset value A.
 * @param valueB Setting offset value B.
 * @note In normal adc sequence, the values are automatically calculated by LPADC_EnableOffsetCalibration.
 */
static inline void LPADC_SetOffset16BitValue(ADC_Type *base, uint32_t valueA, uint32_t valueB)
{
    base->OFSTRIM16 = ADC_OFSTRIM16_OFSTRIM_A(valueA) | ADC_OFSTRIM16_OFSTRIM_B(valueB);
}
#endif /* FSL_FEATURE_LPADC_HAS_OFSTRIM */

/*!
 * @brief Enable the offset calibration function.
 *
 * @param base LPADC peripheral base address.
 * @param enable switcher to the calibration function.
 */
static inline void LPADC_EnableOffsetCalibration(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= ADC_CTRL_CALOFS_MASK;
    }
    else
    {
        base->CTRL &= ~ADC_CTRL_CALOFS_MASK;
    }
}
#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE
/*!
 * @brief Set offset calibration mode.
 *
 * @param base LPADC peripheral base address.
 * @param mode set offset calibration mode.see to #lpadc_offset_calibration_mode_t .
 */
static inline void LPADC_SetOffsetCalibrationMode(ADC_Type *base, lpadc_offset_calibration_mode_t mode)
{
    base->CTRL = (base->CTRL & ~ADC_CTRL_CALOFSMODE_MASK) | ADC_CTRL_CALOFSMODE(mode);
}

#endif /* defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE */

/*!
 * @brief Do offset calibration.
 *
 * @param base LPADC peripheral base address.
 */
void LPADC_DoOffsetCalibration(ADC_Type *base);

#if defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ
/*!
 * @brief Do auto calibration.
 *
 * @param base  LPADC peripheral base address.
 */
void LPADC_DoAutoCalibration(ADC_Type *base);

/*!
 * @brief Prepare auto calibration, LPADC_FinishAutoCalibration has to be called before using the LPADC.
 * LPADC_DoAutoCalibration has been split in two API to avoid to be stuck too long in the function.
 *
 * @param base  LPADC peripheral base address.
 */
void LPADC_PrepareAutoCalibration(ADC_Type *base);

/*!
 * @brief Finish auto calibration start with LPADC_PrepareAutoCalibration.
 *
 * @param base  LPADC peripheral base address.
 */
void LPADC_FinishAutoCalibration(ADC_Type *base);

#endif /* defined(FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ) && FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ */

/*!
 * @brief Get calibration value into the memory which is defined by invoker.
 *
 * @note Please note the ADC will be disabled temporary.
 * @note This function should be used after finish calibration.
 *
 * @param base LPADC peripheral base address.
 * @param ptrCalibrationValue Pointer to @ref lpadc_calibration_value_t structure, this memory block should be always
 * powered on even in low power modes.
 */
void LPADC_GetCalibrationValue(ADC_Type *base, lpadc_calibration_value_t *ptrCalibrationValue);

/*!
 * @brief Set calibration value into ADC calibration registers.
 *
 * @note Please note the ADC will be disabled temporary.
 *
 * @param base LPADC peripheral base address.
 * @param ptrCalibrationValue Pointer to @ref lpadc_calibration_value_t structure which contains ADC's calibration
 * value.
 */
void LPADC_SetCalibrationValue(ADC_Type *base, const lpadc_calibration_value_t *ptrCalibrationValue);

#endif /* defined(FSL_FEATURE_LPADC_HAS_CTRL_CALOFS) && FSL_FEATURE_LPADC_HAS_CTRL_CALOFS */

#if ((defined(FSL_FEATURE_LPADC_HAS_CTRL_CALHS)) && FSL_FEATURE_LPADC_HAS_CTRL_CALHS)
/*!
 * @brief Request high speed mode trim calculation.
 *
 * @param base LPADC peripheral base address.
 */
static inline void LPADC_RequestHighSpeedModeTrim(ADC_Type *base)
{
    base->CTRL |= ADC_CTRL_CALHS_MASK;
}

/*!
 * @brief Get high speed mode trim value, the result is a 5-bit signed value between -16 and 15.
 *
 * @note The high speed mode trim value is used to minimize offset for high speed conversion.
 *
 * @param base LPADC peripheral base address.
 * @return The calculated high speed mode trim value.
 */
static inline int8_t LPADC_GetHighSpeedTrimValue(ADC_Type *base)
{
    return (int8_t)(base->HSTRIM);
}

/*!
 * @brief Set high speed mode trim value.
 *
 * @note If is possible to set the trim value manually, but it is recommended to use the LPADC_RequestHighSpeedModeTrim.
 *
 * @param base LPADC peripheral base address.
 * @param trimValue The trim value to be set.
 */
static inline void LPADC_SetHighSpeedTrimValue(ADC_Type *base, int8_t trimValue)
{
    base->HSTRIM = ADC_HSTRIM_HSTRIM(trimValue);
}

/*!
 * @brief Enable/disable high speed conversion mode, if enabled conversions complete 2 or 3 ADCK cycles sooner compared
 * to conversion cycle counts when high speed mode is disabled.
 *
 * @param base LPADC peripheral base address.
 * @param enable Used to enable/disable high speed conversion mode:
 *     - \b true Enable high speed conversion mode;
 *     - \b false Disable high speed conversion mode.
 */
static inline void LPADC_EnableHighSpeedConversionMode(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->CFG2 |= ADC_CFG2_HS_MASK;
    }
    else
    {
        base->CFG2 &= ~ADC_CFG2_HS_MASK;
    }
}

/*!
 * @brief Enable/disable an additional ADCK cycle to conversion.
 *
 * @param base LPADC peripheral base address.
 * @param enable Used to enable/disable an additional ADCK cycle to conversion:
 *          - \b true Enable an additional ADCK cycle to conversion;
 *          - \b false Disable an additional ADCK cycle to conversion.
 */
static inline void LPADC_EnableExtraCycle(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->CFG2 |= ADC_CFG2_HSEXTRA_MASK;
    }
    else
    {
        base->CFG2 &= ~ADC_CFG2_HSEXTRA_MASK;
    }
}

/*!
 * @brief Set tune value which provides some variability in how many cycles are needed to complete a conversion.
 *
 * @param base LPADC peripheral base address.
 * @param tuneValue The tune value to be set, please refer to @ref lpadc_tune_value_t.
 */
static inline void LPADC_SetTuneValue(ADC_Type *base, lpadc_tune_value_t tuneValue)
{
    base->CFG2 = (base->CFG2 & ~ADC_CFG2_TUNE_MASK) | ADC_CFG2_TUNE(tuneValue);
}

/*!
 * @brief Get tune value which provides some variability in how many cycles are needed to complete a conversion.
 *
 * @param base LPADC peripheral base address.
 * @return The tune value, please refer to @ref lpadc_tune_value_t.
 */
static inline lpadc_tune_value_t LPADC_GetTuneValue(ADC_Type *base)
{
    return (lpadc_tune_value_t)((base->CFG2 & ADC_CFG2_TUNE_MASK) >> ADC_CFG2_TUNE_SHIFT);
}
#endif /* ((defined(FSL_FEATURE_LPADC_HAS_CTRL_CALHS)) && FSL_FEATURE_LPADC_HAS_CTRL_CALHS) */

#if (defined(FSL_FEATURE_LPADC_HAS_CFG2_JLEFT) && FSL_FEATURE_LPADC_HAS_CFG2_JLEFT)
/*!
 * @brief Enable/disable left-justify format in 12-bit single-end mode.
 *
 * @param base LPADC peripheral base address.
 * @param enable Used to enable/disable left-justify format in 12-bit single-end mode:
 *          - \b true Enable left-justify format in 12-bit single-end mode;
 *          - \b false Disable left-justify format in 12-bit single-end mode.
 */
static inline void LPADC_EnableJustifiedLeft(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->CFG2 |= ADC_CFG2_JLEFT_MASK;
    }
    else
    {
        base->CFG2 &= ~ADC_CFG2_JLEFT_MASK;
    }
}
#endif /* (defined(FSL_FEATURE_LPADC_HAS_CFG2_JLEFT) && FSL_FEATURE_LPADC_HAS_CFG2_JLEFT) */

/* @} */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* FSL_LPADC_H_ */
