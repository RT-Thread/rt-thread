/*
 * Copyright (c) 2018, Freescale Semiconductor, Inc.
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PDM_H_
#define _FSL_PDM_H_

#include "fsl_common.h"

/*!
 * @addtogroup pdm_driver PDM Driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_PDM_DRIVER_VERSION (MAKE_VERSION(2, 8, 0)) /*!< Version 2.8.0 */
/*@}*/

/*! @brief PDM XFER QUEUE SIZE */
#define PDM_XFER_QUEUE_SIZE (4U)

/*! @brief PDM return status*/
enum
{
    kStatus_PDM_Busy = MAKE_STATUS(kStatusGroup_PDM, 0), /*!< PDM is busy. */
#if (defined(FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ) && (FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ == 1U))
    kStatus_PDM_CLK_LOW = MAKE_STATUS(kStatusGroup_PDM, 1), /*!< PDM clock frequency low */
#endif
    kStatus_PDM_FIFO_ERROR           = MAKE_STATUS(kStatusGroup_PDM, 2), /*!< PDM FIFO underrun or overflow */
    kStatus_PDM_QueueFull            = MAKE_STATUS(kStatusGroup_PDM, 3), /*!< PDM FIFO underrun or overflow */
    kStatus_PDM_Idle                 = MAKE_STATUS(kStatusGroup_PDM, 4), /*!< PDM is idle */
    kStatus_PDM_Output_ERROR         = MAKE_STATUS(kStatusGroup_PDM, 5), /*!< PDM is output error */
    kStatus_PDM_ChannelConfig_Failed = MAKE_STATUS(kStatusGroup_PDM, 6), /*!< PDM channel config failed */
#if !(defined(FSL_FEATURE_PDM_HAS_NO_HWVAD) && FSL_FEATURE_PDM_HAS_NO_HWVAD)
    kStatus_PDM_HWVAD_VoiceDetected = MAKE_STATUS(kStatusGroup_PDM, 7), /*!< PDM hwvad voice detected */
    kStatus_PDM_HWVAD_Error         = MAKE_STATUS(kStatusGroup_PDM, 8), /*!< PDM hwvad error */
#endif
};

/*! @brief The PDM interrupt enable flag */
enum _pdm_interrupt_enable
{
    kPDM_ErrorInterruptEnable = PDM_CTRL_1_ERREN_MASK, /*!< PDM channel error interrupt enable. */
    kPDM_FIFOInterruptEnable  = PDM_CTRL_1_DISEL(2U),  /*!< PDM channel FIFO interrupt */
};

/*! @brief The PDM status */
enum _pdm_internal_status
{
    kPDM_StatusDfBusyFlag = (int)PDM_STAT_BSY_FIL_MASK, /*!< Decimation filter is busy processing data */
#if !(defined(FSL_FEATURE_PDM_HAS_NO_FIR_RDY) && FSL_FEATURE_PDM_HAS_NO_FIR_RDY)
    kPDM_StatusFIRFilterReady = PDM_STAT_FIR_RDY_MASK, /*!< FIR filter data is ready */
#endif
#if (defined(FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ) && (FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ == 1U))
    kPDM_StatusFrequencyLow = PDM_STAT_LOWFREQF_MASK, /*!< Mic app clock frequency not high enough */
#endif
    kPDM_StatusCh0FifoDataAvaliable = PDM_STAT_CH0F_MASK, /*!< channel 0 fifo data reached watermark level */
    kPDM_StatusCh1FifoDataAvaliable = PDM_STAT_CH1F_MASK, /*!< channel 1 fifo data reached watermark level */
    kPDM_StatusCh2FifoDataAvaliable = PDM_STAT_CH2F_MASK, /*!< channel 2 fifo data reached watermark level */
    kPDM_StatusCh3FifoDataAvaliable = PDM_STAT_CH3F_MASK, /*!< channel 3 fifo data reached watermark level */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_StatusCh4FifoDataAvaliable = PDM_STAT_CH4F_MASK, /*!< channel 4 fifo data reached watermark level */
    kPDM_StatusCh5FifoDataAvaliable = PDM_STAT_CH5F_MASK, /*!< channel 5 fifo data reached watermark level */
    kPDM_StatusCh6FifoDataAvaliable = PDM_STAT_CH6F_MASK, /*!< channel 6 fifo data reached watermark level */
    kPDM_StatusCh7FifoDataAvaliable = PDM_STAT_CH7F_MASK, /*!< channel 7 fifo data reached watermark level */
#endif
};

/*! @brief PDM channel enable mask */
enum _pdm_channel_enable_mask
{
    kPDM_EnableChannel0 = PDM_STAT_CH0F_MASK, /*!< channgel 0 enable mask */
    kPDM_EnableChannel1 = PDM_STAT_CH1F_MASK, /*!< channgel 1 enable mask */
    kPDM_EnableChannel2 = PDM_STAT_CH2F_MASK, /*!< channgel 2 enable mask */
    kPDM_EnableChannel3 = PDM_STAT_CH3F_MASK, /*!< channgel 3 enable mask */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_EnableChannel4 = PDM_STAT_CH4F_MASK, /*!< channgel 4 enable mask */
    kPDM_EnableChannel5 = PDM_STAT_CH5F_MASK, /*!< channgel 5 enable mask */
    kPDM_EnableChannel6 = PDM_STAT_CH6F_MASK, /*!< channgel 6 enable mask */
    kPDM_EnableChannel7 = PDM_STAT_CH7F_MASK, /*!< channgel 7 enable mask */

    kPDM_EnableChannelAll = kPDM_EnableChannel0 | kPDM_EnableChannel1 | kPDM_EnableChannel2 | kPDM_EnableChannel3 |
                            kPDM_EnableChannel4 | kPDM_EnableChannel5 | kPDM_EnableChannel6 | kPDM_EnableChannel7,
#else
    kPDM_EnableChannelAll = kPDM_EnableChannel0 | kPDM_EnableChannel1 | kPDM_EnableChannel2 | kPDM_EnableChannel3,
#endif
};

/*! @brief The PDM fifo status */
enum _pdm_fifo_status
{
    kPDM_FifoStatusUnderflowCh0 = PDM_FIFO_STAT_FIFOUND0_MASK, /*!< channel0 fifo status underflow */
    kPDM_FifoStatusUnderflowCh1 = PDM_FIFO_STAT_FIFOUND1_MASK, /*!< channel1 fifo status underflow */
    kPDM_FifoStatusUnderflowCh2 = PDM_FIFO_STAT_FIFOUND2_MASK, /*!< channel2 fifo status underflow */
    kPDM_FifoStatusUnderflowCh3 = PDM_FIFO_STAT_FIFOUND3_MASK, /*!< channel3 fifo status underflow */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_FifoStatusUnderflowCh4 = PDM_FIFO_STAT_FIFOUND4_MASK, /*!< channel4 fifo status underflow */
    kPDM_FifoStatusUnderflowCh5 = PDM_FIFO_STAT_FIFOUND5_MASK, /*!< channel5 fifo status underflow */
    kPDM_FifoStatusUnderflowCh6 = PDM_FIFO_STAT_FIFOUND6_MASK, /*!< channel6 fifo status underflow */
    kPDM_FifoStatusUnderflowCh7 = PDM_FIFO_STAT_FIFOUND6_MASK, /*!< channel7 fifo status underflow */
#endif

    kPDM_FifoStatusOverflowCh0 = PDM_FIFO_STAT_FIFOOVF0_MASK, /*!< channel0 fifo status overflow */
    kPDM_FifoStatusOverflowCh1 = PDM_FIFO_STAT_FIFOOVF1_MASK, /*!< channel1 fifo status overflow */
    kPDM_FifoStatusOverflowCh2 = PDM_FIFO_STAT_FIFOOVF2_MASK, /*!< channel2 fifo status overflow */
    kPDM_FifoStatusOverflowCh3 = PDM_FIFO_STAT_FIFOOVF3_MASK, /*!< channel3 fifo status overflow */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_FifoStatusOverflowCh4 = PDM_FIFO_STAT_FIFOOVF4_MASK, /*!< channel4 fifo status overflow */
    kPDM_FifoStatusOverflowCh5 = PDM_FIFO_STAT_FIFOOVF5_MASK, /*!< channel5 fifo status overflow */
    kPDM_FifoStatusOverflowCh6 = PDM_FIFO_STAT_FIFOOVF6_MASK, /*!< channel6 fifo status overflow */
    kPDM_FifoStatusOverflowCh7 = PDM_FIFO_STAT_FIFOOVF7_MASK, /*!< channel7 fifo status overflow */
#endif
};

#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
/*! @brief The PDM output status */
enum _pdm_range_status
{
    kPDM_RangeStatusUnderFlowCh0 = PDM_RANGE_STAT_RANGEUNF0_MASK, /*!< channel0 range status underflow */
    kPDM_RangeStatusUnderFlowCh1 = PDM_RANGE_STAT_RANGEUNF1_MASK, /*!< channel1 range status underflow */
    kPDM_RangeStatusUnderFlowCh2 = PDM_RANGE_STAT_RANGEUNF2_MASK, /*!< channel2 range status underflow */
    kPDM_RangeStatusUnderFlowCh3 = PDM_RANGE_STAT_RANGEUNF3_MASK, /*!< channel3 range status underflow */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_RangeStatusUnderFlowCh4 = PDM_RANGE_STAT_RANGEUNF4_MASK, /*!< channel4 range status underflow */
    kPDM_RangeStatusUnderFlowCh5 = PDM_RANGE_STAT_RANGEUNF5_MASK, /*!< channel5 range status underflow */
    kPDM_RangeStatusUnderFlowCh6 = PDM_RANGE_STAT_RANGEUNF6_MASK, /*!< channel6 range status underflow */
    kPDM_RangeStatusUnderFlowCh7 = PDM_RANGE_STAT_RANGEUNF7_MASK, /*!< channel7 range status underflow */
#endif
    kPDM_RangeStatusOverFlowCh0 = PDM_RANGE_STAT_RANGEOVF0_MASK, /*!< channel0 range status overflow */
    kPDM_RangeStatusOverFlowCh1 = PDM_RANGE_STAT_RANGEOVF1_MASK, /*!< channel1 range status overflow */
    kPDM_RangeStatusOverFlowCh2 = PDM_RANGE_STAT_RANGEOVF2_MASK, /*!< channel2 range status overflow */
    kPDM_RangeStatusOverFlowCh3 = PDM_RANGE_STAT_RANGEOVF3_MASK, /*!< channel3 range status overflow */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_RangeStatusOverFlowCh4 = PDM_RANGE_STAT_RANGEOVF4_MASK, /*!< channel4 range status overflow */
    kPDM_RangeStatusOverFlowCh5 = PDM_RANGE_STAT_RANGEOVF5_MASK, /*!< channel5 range status overflow */
    kPDM_RangeStatusOverFlowCh6 = PDM_RANGE_STAT_RANGEOVF6_MASK, /*!< channel6 range status overflow */
    kPDM_RangeStatusOverFlowCh7 = PDM_RANGE_STAT_RANGEOVF7_MASK, /*!< channel7 range status overflow */
#endif
};
#else
/*! @brief The PDM output status */
enum _pdm_output_status
{
    kPDM_OutputStatusUnderFlowCh0 = PDM_OUT_STAT_OUTUNF0_MASK, /*!< channel0 output status underflow */
    kPDM_OutputStatusUnderFlowCh1 = PDM_OUT_STAT_OUTUNF1_MASK, /*!< channel1 output status underflow */
    kPDM_OutputStatusUnderFlowCh2 = PDM_OUT_STAT_OUTUNF2_MASK, /*!< channel2 output status underflow */
    kPDM_OutputStatusUnderFlowCh3 = PDM_OUT_STAT_OUTUNF3_MASK, /*!< channel3 output status underflow */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_OutputStatusUnderFlowCh4 = PDM_OUT_STAT_OUTUNF4_MASK, /*!< channel4 output status underflow */
    kPDM_OutputStatusUnderFlowCh5 = PDM_OUT_STAT_OUTUNF5_MASK, /*!< channel5 output status underflow */
    kPDM_OutputStatusUnderFlowCh6 = PDM_OUT_STAT_OUTUNF6_MASK, /*!< channel6 output status underflow */
    kPDM_OutputStatusUnderFlowCh7 = PDM_OUT_STAT_OUTUNF7_MASK, /*!< channel7 output status underflow */
#endif
    kPDM_OutputStatusOverFlowCh0 = PDM_OUT_STAT_OUTOVF0_MASK,  /*!< channel0 output status overflow */
    kPDM_OutputStatusOverFlowCh1 = PDM_OUT_STAT_OUTOVF1_MASK,  /*!< channel1 output status overflow */
    kPDM_OutputStatusOverFlowCh2 = PDM_OUT_STAT_OUTOVF2_MASK,  /*!< channel2 output status overflow */
    kPDM_OutputStatusOverFlowCh3 = PDM_OUT_STAT_OUTOVF3_MASK,  /*!< channel3 output status overflow */
#if !defined(FSL_FEATURE_PDM_CHANNEL_NUM) || (FSL_FEATURE_PDM_CHANNEL_NUM == 8U)
    kPDM_OutputStatusOverFlowCh4 = PDM_OUT_STAT_OUTOVF4_MASK,  /*!< channel4 output status overflow */
    kPDM_OutputStatusOverFlowCh5 = PDM_OUT_STAT_OUTOVF5_MASK,  /*!< channel5 output status overflow */
    kPDM_OutputStatusOverFlowCh6 = PDM_OUT_STAT_OUTOVF6_MASK,  /*!< channel6 output status overflow */
    kPDM_OutputStatusOverFlowCh7 = PDM_OUT_STAT_OUTOVF7_MASK,  /*!< channel7 output status overflow */
#endif
};
#endif

#if (defined(FSL_FEATURE_PDM_HAS_DC_OUT_CTRL) && (FSL_FEATURE_PDM_HAS_DC_OUT_CTRL))
/*! @brief PDM DC remover configurations */
typedef enum _pdm_dc_remover
{
    kPDM_DcRemoverCutOff20Hz = 0U, /*!< DC remover cut off 20HZ */
    kPDM_DcRemoverCutOff13Hz = 1U, /*!< DC remover cut off 13.3HZ */
    kPDM_DcRemoverCutOff40Hz = 2U, /*!< DC remover cut off 40HZ */
    kPDM_DcRemoverBypass     = 3U, /*!< DC remover bypass */
} pdm_dc_remover_t;
#else
/*! @brief PDM DC remover configurations */
typedef enum _pdm_dc_remover
{
    kPDM_DcRemoverCutOff21Hz = 0U,  /*!< DC remover cut off 21HZ */
    kPDM_DcRemoverCutOff83Hz = 1U,  /*!< DC remover cut off 83HZ */
    kPDM_DcRemoverCutOff152Hz = 2U, /*!< DC remover cut off 152HZ */
    kPDM_DcRemoverBypass = 3U,      /*!< DC remover bypass */
} pdm_dc_remover_t;
#endif

/*! @brief PDM decimation filter quality mode */
typedef enum _pdm_df_quality_mode
{
    kPDM_QualityModeMedium   = 0U, /*!< quality mode memdium */
    kPDM_QualityModeHigh     = 1U, /*!< quality mode high */
    kPDM_QualityModeLow      = 7U, /*!< quality mode low */
    kPDM_QualityModeVeryLow0 = 6U, /*!< quality mode very low0 */
    kPDM_QualityModeVeryLow1 = 5U, /*!< quality mode very low1 */
    kPDM_QualityModeVeryLow2 = 4U, /*!< quality mode very low2 */
} pdm_df_quality_mode_t;

/*! @brief PDM  quality mode K factor */
enum _pdm_qulaity_mode_k_factor
{
    kPDM_QualityModeHighKFactor     = 1U, /*!< high quality mode K factor = 1 / 2 */
    kPDM_QualityModeMediumKFactor   = 2U, /*!< medium/very low0 quality mode K factor = 2 / 2 */
    kPDM_QualityModeLowKFactor      = 4U, /*!< low/very low1 quality mode K factor = 4 / 2 */
    kPDM_QualityModeVeryLow2KFactor = 8U, /*!< very low2 quality mode K factor = 8 / 2 */
};

/*! @brief PDM decimation filter output gain */
typedef enum _pdm_df_output_gain
{
    kPDM_DfOutputGain0  = 0U,   /*!< Decimation filter output gain 0 */
    kPDM_DfOutputGain1  = 1U,   /*!< Decimation filter output gain 1 */
    kPDM_DfOutputGain2  = 2U,   /*!< Decimation filter output gain 2 */
    kPDM_DfOutputGain3  = 3U,   /*!< Decimation filter output gain 3 */
    kPDM_DfOutputGain4  = 4U,   /*!< Decimation filter output gain 4 */
    kPDM_DfOutputGain5  = 5U,   /*!< Decimation filter output gain 5 */
    kPDM_DfOutputGain6  = 6U,   /*!< Decimation filter output gain 6 */
    kPDM_DfOutputGain7  = 7U,   /*!< Decimation filter output gain 7 */
    kPDM_DfOutputGain8  = 8U,   /*!< Decimation filter output gain 8 */
    kPDM_DfOutputGain9  = 9U,   /*!< Decimation filter output gain 9 */
    kPDM_DfOutputGain10 = 0xAU, /*!< Decimation filter output gain 10 */
    kPDM_DfOutputGain11 = 0xBU, /*!< Decimation filter output gain 11 */
    kPDM_DfOutputGain12 = 0xCU, /*!< Decimation filter output gain 12 */
    kPDM_DfOutputGain13 = 0xDU, /*!< Decimation filter output gain 13 */
    kPDM_DfOutputGain14 = 0xEU, /*!< Decimation filter output gain 14 */
    kPDM_DfOutputGain15 = 0xFU, /*!< Decimation filter output gain 15 */
} pdm_df_output_gain_t;

/*! @brief PDM data width */
enum _pdm_data_width
{
#if defined(FSL_FEATURE_PDM_FIFO_WIDTH) && (FSL_FEATURE_PDM_FIFO_WIDTH != 2U)
    kPDM_DataWwidth24 = 3U, /*!< PDM data width 24bit */
    kPDM_DataWwidth32 = 4U, /*!< PDM data width 32bit */
#else
    kPDM_DataWdith16 = 2U, /*!< PDM data width 16bit */
#endif
};

/*! @brief PDM channel configurations */
typedef struct _pdm_channel_config
{
#if (defined(FSL_FEATURE_PDM_HAS_DC_OUT_CTRL) && (FSL_FEATURE_PDM_HAS_DC_OUT_CTRL))
    pdm_dc_remover_t outputCutOffFreq; /*!< PDM output DC remover cut off frequency */
#endif

#if !(defined(FSL_FEATURE_PDM_DC_CTRL_VALUE_FIXED) && (FSL_FEATURE_PDM_DC_CTRL_VALUE_FIXED))
    pdm_dc_remover_t cutOffFreq; /*!< DC remover cut off frequency */
#endif

    pdm_df_output_gain_t gain; /*!< Decimation Filter Output Gain */
} pdm_channel_config_t;

/*! @brief PDM user configuration structure */
typedef struct _pdm_config
{
    bool
        enableDoze; /*!< This module will enter disable/low leakage mode if DOZEN is active with ipg_doze is asserted */
    uint8_t fifoWatermark;             /*!< Watermark value for FIFO */
    pdm_df_quality_mode_t qualityMode; /*!< Quality mode */
    uint8_t cicOverSampleRate;         /*!< CIC filter over sampling rate */
} pdm_config_t;

#if !(defined(FSL_FEATURE_PDM_HAS_NO_HWVAD) && FSL_FEATURE_PDM_HAS_NO_HWVAD)
/*! @brief PDM voice activity detector interrupt type */
enum _pdm_hwvad_interrupt_enable
{
    kPDM_HwvadErrorInterruptEnable = PDM_VAD0_CTRL_1_VADERIE_MASK, /*!< PDM channel HWVAD error interrupt enable. */
    kPDM_HwvadInterruptEnable      = PDM_VAD0_CTRL_1_VADIE_MASK,   /*!< PDM channel HWVAD interrupt */
};

/*! @brief The PDM hwvad interrupt status flag */
enum _pdm_hwvad_int_status
{
    kPDM_HwvadStatusInputSaturation = PDM_VAD0_STAT_VADINSATF_MASK, /*!< HWVAD saturation condition */
    kPDM_HwvadStatusVoiceDetectFlag = PDM_VAD0_STAT_VADIF_MASK,     /*!< HWVAD voice detect interrupt triggered */
};

/*! @brief High pass filter configure cut-off frequency*/
typedef enum _pdm_hwvad_hpf_config
{
    kPDM_HwvadHpfBypassed         = 0x0U, /*!< High-pass filter bypass */
    kPDM_HwvadHpfCutOffFreq1750Hz = 0x1U, /*!< High-pass filter cut off frequency 1750HZ */
    kPDM_HwvadHpfCutOffFreq215Hz  = 0x2U, /*!< High-pass filter cut off frequency 215HZ */
    kPDM_HwvadHpfCutOffFreq102Hz  = 0x3U, /*!< High-pass filter cut off frequency 102HZ */
} pdm_hwvad_hpf_config_t;

/*! @brief HWVAD internal filter status */
typedef enum _pdm_hwvad_filter_status
{
    kPDM_HwvadInternalFilterNormalOperation = 0U, /*!< internal filter ready for normal operation */
    kPDM_HwvadInternalFilterInitial         = PDM_VAD0_CTRL_1_VADST10_MASK, /*!< interla filter are initial */
} pdm_hwvad_filter_status_t;

/*! @brief PDM voice activity detector user configuration structure */
typedef struct _pdm_hwvad_config
{
    uint8_t channel;           /*!< Which channel uses voice activity detector */
    uint8_t initializeTime;    /*!< Number of frames or samples to initialize voice activity detector. */
    uint8_t cicOverSampleRate; /*!< CIC filter over sampling rate */

    uint8_t inputGain;                 /*!< Voice activity detector input gain */
    uint32_t frameTime;                /*!< Voice activity frame time */
    pdm_hwvad_hpf_config_t cutOffFreq; /*!< High pass filter cut off frequency */
    bool enableFrameEnergy;            /*!< If frame energy enabled, true means enable */
    bool enablePreFilter;              /*!< If pre-filter enabled */
} pdm_hwvad_config_t;

/*! @brief PDM voice activity detector noise filter user configuration structure */
typedef struct _pdm_hwvad_noise_filter
{
    bool enableAutoNoiseFilter;     /*!< If noise fileter automatically activated, true means enable */
    bool enableNoiseMin;            /*!< If Noise minimum block enabled, true means enabled */
    bool enableNoiseDecimation;     /*!< If enable noise input decimation */
    bool enableNoiseDetectOR;       /*!< Enables a OR logic in the output of minimum noise estimator block */
    uint32_t noiseFilterAdjustment; /*!< The adjustment value of the noise filter */
    uint32_t noiseGain;             /*!< Gain value for the noise energy or envelope estimated */
} pdm_hwvad_noise_filter_t;

/*! @brief PDM voice activity detector zero cross detector result */
typedef enum _pdm_hwvad_zcd_result
{
    kPDM_HwvadResultOREnergyBasedDetection =
        0U, /*!< zero cross detector result will be OR with energy based detection */
    kPDM_HwvadResultANDEnergyBasedDetection =
        1U, /*!< zero cross detector result will be AND with energy based detection */
} pdm_hwvad_zcd_result_t;

/*! @brief PDM voice activity detector zero cross detector configuration structure */
typedef struct _pdm_hwvad_zero_cross_detector
{
    bool enableAutoThreshold;      /*!< If ZCD auto-threshold enabled, true means enabled. */
    pdm_hwvad_zcd_result_t zcdAnd; /*!< Is ZCD result is AND'ed with energy-based detection, false means OR'ed */
    uint32_t threshold;            /*!< The adjustment value of the noise filter */
    uint32_t adjustmentThreshold;  /*!< Gain value for the noise energy or envelope estimated */
} pdm_hwvad_zero_cross_detector_t;
#endif

/*! @brief PDM SDMA transfer structure */
typedef struct _pdm_transfer
{
    volatile uint8_t *data;   /*!< Data start address to transfer. */
    volatile size_t dataSize; /*!< Total Transfer bytes size. */
} pdm_transfer_t;

/*! @brief PDM handle */
typedef struct _pdm_handle pdm_handle_t;

/*! @brief PDM transfer callback prototype */
typedef void (*pdm_transfer_callback_t)(PDM_Type *base, pdm_handle_t *handle, status_t status, void *userData);

#if !(defined(FSL_FEATURE_PDM_HAS_NO_HWVAD) && FSL_FEATURE_PDM_HAS_NO_HWVAD)
/*! @brief PDM HWVAD callback prototype */
typedef void (*pdm_hwvad_callback_t)(status_t status, void *userData);
/*! @brief PDM HWVAD notification structure */
typedef struct _pdm_hwvad_notification
{
    pdm_hwvad_callback_t callback;
    void *userData;
} pdm_hwvad_notification_t;
#endif

/*! @brief PDM handle structure */
struct _pdm_handle
{
    uint32_t state;                   /*!< Transfer status */
    pdm_transfer_callback_t callback; /*!< Callback function called at transfer event*/
    void *userData;                   /*!< Callback parameter passed to callback function*/

    pdm_transfer_t pdmQueue[PDM_XFER_QUEUE_SIZE]; /*!< Transfer queue storing queued transfer */
    size_t transferSize[PDM_XFER_QUEUE_SIZE];     /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                   /*!< Index for user to queue transfer */
    volatile uint8_t queueDriver;                 /*!< Index for driver to get the transfer data and size */

    uint32_t format;      /*!< data format */
    uint8_t watermark;    /*!< Watermark value */
    uint8_t startChannel; /*!< end channel */
    uint8_t channelNums;  /*!< Enabled channel number */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus*/

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the PDM peripheral.
 *
 * Ungates the PDM clock, resets the module, and configures PDM with a configuration structure.
 * The configuration structure can be custom filled or set with default values by
 * PDM_GetDefaultConfig().
 *
 * @note  This API should be called at the beginning of the application to use
 * the PDM driver. Otherwise, accessing the PDM module can cause a hard fault
 * because the clock is not enabled.
 *
 * @param base PDM base pointer
 * @param config PDM configuration structure.
 */
void PDM_Init(PDM_Type *base, const pdm_config_t *config);

/*!
 * @brief De-initializes the PDM peripheral.
 *
 * This API gates the PDM clock. The PDM module can't operate unless PDM_Init
 * is called to enable the clock.
 *
 * @param base PDM base pointer
 */
void PDM_Deinit(PDM_Type *base);

/*!
 * @brief Resets the PDM module.
 *
 * @param base PDM base pointer
 */
static inline void PDM_Reset(PDM_Type *base)
{
    base->CTRL_1 |= PDM_CTRL_1_SRES_MASK;
}

/*!
 * @brief Enables/disables PDM interface.
 *
 * @param base PDM base pointer
 * @param enable True means PDM interface is enabled, false means PDM interface is disabled.
 */
static inline void PDM_Enable(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_1 |= PDM_CTRL_1_PDMIEN_MASK;
    }
    else
    {
        base->CTRL_1 &= ~PDM_CTRL_1_PDMIEN_MASK;
    }
}

/*!
 * @brief Enables/disables DOZE.
 *
 * @param base PDM base pointer
 * @param enable True means the module will enter Disable/Low Leakage mode when ipg_doze is asserted, false means the
 * module will not enter Disable/Low Leakage mode when ipg_doze is asserted.
 */
static inline void PDM_EnableDoze(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_1 |= PDM_CTRL_1_DOZEN_MASK;
    }
    else
    {
        base->CTRL_1 &= ~PDM_CTRL_1_DOZEN_MASK;
    }
}

/*!
 * @brief Enables/disables debug mode for PDM.
 * The PDM interface cannot enter debug mode once in Disable/Low Leakage or Low Power mode.
 * @param base PDM base pointer
 * @param enable True means PDM interface enter debug mode, false means PDM interface in normal mode.
 */
static inline void PDM_EnableDebugMode(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_1 |= PDM_CTRL_1_DBG_MASK;
    }
    else
    {
        base->CTRL_1 &= ~PDM_CTRL_1_DBG_MASK;
    }
}

/*!
 * @brief Enables/disables PDM interface in debug mode.
 *
 * @param base PDM base pointer
 * @param enable True means PDM interface is enabled debug mode, false means PDM interface is disabled after
 * after completing the current frame in debug mode.
 */
static inline void PDM_EnableInDebugMode(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_1 |= PDM_CTRL_1_DBGE_MASK;
    }
    else
    {
        base->CTRL_1 &= ~PDM_CTRL_1_DBGE_MASK;
    }
}

/*!
 * @brief Enables/disables PDM interface disable/Low Leakage mode.
 *
 * @param base PDM base pointer
 * @param enable True means PDM interface is in disable/low leakage mode, False means PDM interface is in normal mode.
 */
static inline void PDM_EnterLowLeakageMode(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_1 |= PDM_CTRL_1_MDIS_MASK;
    }
    else
    {
        base->CTRL_1 &= ~PDM_CTRL_1_MDIS_MASK;
    }
}

/*!
 * @brief Enables/disables the PDM channel.
 *
 * @param base PDM base pointer
 * @param channel PDM channel number need to enable or disable.
 * @param enable True means enable PDM channel, false means disable.
 */
static inline void PDM_EnableChannel(PDM_Type *base, uint8_t channel, bool enable)
{
    if (enable)
    {
        base->CTRL_1 |= (1UL << channel);
    }
    else
    {
        base->CTRL_1 &= ~(1UL << channel);
    }
}

/*!
 * @brief PDM one channel configurations.
 *
 * @param base PDM base pointer
 * @param config PDM channel configurations.
 * @param channel channel number.
 * after completing the current frame in debug mode.
 */
void PDM_SetChannelConfig(PDM_Type *base, uint32_t channel, const pdm_channel_config_t *config);

/*!
 * @brief PDM set sample rate.
 *
 * @note This function is depend on the configuration of the PDM and PDM channel, so the correct call sequence is
 * @code
 * PDM_Init(base, pdmConfig)
 * PDM_SetChannelConfig(base, channel, &channelConfig)
 * PDM_SetSampleRateConfig(base, source, sampleRate)
 * @endcode
 * @param base PDM base pointer
 * @param sourceClock_HZ PDM source clock frequency.
 * @param sampleRate_HZ PDM sample rate.
 */
status_t PDM_SetSampleRateConfig(PDM_Type *base, uint32_t sourceClock_HZ, uint32_t sampleRate_HZ);

/*!
 * @brief PDM set sample rate.
 *
 * @deprecated Do not use this function.  It has been superceded by @ref PDM_SetSampleRateConfig
 * @param base PDM base pointer
 * @param enableChannelMask PDM channel enable mask.
 * @param qualityMode quality mode.
 * @param osr cic oversample rate
 * @param clkDiv clock divider
 */
status_t PDM_SetSampleRate(
    PDM_Type *base, uint32_t enableChannelMask, pdm_df_quality_mode_t qualityMode, uint8_t osr, uint32_t clkDiv);

/*!
 * @brief Get the instance number for PDM.
 *
 * @param base PDM base pointer.
 */
uint32_t PDM_GetInstance(PDM_Type *base);
/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the PDM internal status flag.
 * Use the Status Mask in _pdm_internal_status to get the status value needed
 * @param base PDM base pointer
 * @return PDM status flag value.
 */
static inline uint32_t PDM_GetStatus(PDM_Type *base)
{
    return base->STAT;
}

/*!
 * @brief Gets the PDM FIFO status flag.
 * Use the Status Mask in _pdm_fifo_status to get the status value needed
 * @param base PDM base pointer
 * @return FIFO status.
 */
static inline uint32_t PDM_GetFifoStatus(PDM_Type *base)
{
    return base->FIFO_STAT;
}

#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
/*!
 * @brief Gets the PDM Range status flag.
 * Use the Status Mask in _pdm_range_status to get the status value needed
 * @param base PDM base pointer
 * @return output status.
 */
static inline uint32_t PDM_GetRangeStatus(PDM_Type *base)
{
    return base->RANGE_STAT;
}
#else
/*!
 * @brief Gets the PDM output status flag.
 * Use the Status Mask in _pdm_output_status to get the status value needed
 * @param base PDM base pointer
 * @return output status.
 */
static inline uint32_t PDM_GetOutputStatus(PDM_Type *base)
{
    return base->OUT_STAT;
}
#endif

/*!
 * @brief Clears the PDM Tx status.
 *
 * @param base PDM base pointer
 * @param mask State mask. It can be a combination of the status between kPDM_StatusFrequencyLow and
 * kPDM_StatusCh7FifoDataAvaliable.
 */
static inline void PDM_ClearStatus(PDM_Type *base, uint32_t mask)
{
    base->STAT = mask;
}

/*!
 * @brief Clears the PDM Tx status.
 *
 * @param base PDM base pointer
 * @param mask State mask.It can be a combination of the status in _pdm_fifo_status.
 */
static inline void PDM_ClearFIFOStatus(PDM_Type *base, uint32_t mask)
{
    base->FIFO_STAT = mask;
}

#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
/*!
 * @brief Clears the PDM range status.
 *
 * @param base PDM base pointer
 * @param mask State mask. It can be a combination of the status in _pdm_range_status.
 */
static inline void PDM_ClearRangeStatus(PDM_Type *base, uint32_t mask)
{
    base->RANGE_STAT = mask;
}
#else
/*!
 * @brief Clears the PDM output status.
 *
 * @param base PDM base pointer
 * @param mask State mask. It can be a combination of the status in _pdm_output_status.
 */
static inline void PDM_ClearOutputStatus(PDM_Type *base, uint32_t mask)
{
    base->OUT_STAT = mask;
}
#endif

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables the PDM interrupt requests.
 *
 * @param base PDM base pointer
 * @param mask interrupt source
 *     The parameter can be a combination of the following sources if defined.
 *     @arg kPDM_ErrorInterruptEnable
 *     @arg kPDM_FIFOInterruptEnable
 */
void PDM_EnableInterrupts(PDM_Type *base, uint32_t mask);

/*!
 * @brief Disables the PDM interrupt requests.
 *
 * @param base PDM base pointer
 * @param mask interrupt source
 *     The parameter can be a combination of the following sources if defined.
 *     @arg kPDM_ErrorInterruptEnable
 *     @arg kPDM_FIFOInterruptEnable
 */
static inline void PDM_DisableInterrupts(PDM_Type *base, uint32_t mask)
{
    base->CTRL_1 &= ~mask;
}

/*! @} */

/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Enables/disables the PDM DMA requests.
 *
 * @param base PDM base pointer
 * @param enable True means enable DMA, false means disable DMA.
 */
static inline void PDM_EnableDMA(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_1 = (base->CTRL_1 & (~PDM_CTRL_1_DISEL_MASK)) | PDM_CTRL_1_DISEL(0x1U);
    }
    else
    {
        base->CTRL_1 &= ~PDM_CTRL_1_DISEL_MASK;
    }
}

/*!
 * @brief  Gets the PDM data register address.
 *
 * This API is used to provide a transfer address for the PDM DMA transfer configuration.
 *
 * @param base PDM base pointer.
 * @param channel Which data channel used.
 * @return data register address.
 */
static inline uint32_t PDM_GetDataRegisterAddress(PDM_Type *base, uint32_t channel)
{
    return (uint32_t)(&(base->DATACH)[channel]);
}

/*! @} */

/*!
 * @name Bus Operations
 * @{
 */
#if defined(FSL_FEATURE_PDM_FIFO_WIDTH) && (FSL_FEATURE_PDM_FIFO_WIDTH == 2U)
/*!
 * @brief Reads data from the PDM FIFO.
 *
 * @param base PDM base pointer.
 * @param channel Data channel used.
 * @return Data in PDM FIFO.
 */
static inline int16_t PDM_ReadData(PDM_Type *base, uint32_t channel)
{
    return (int16_t)(base->DATACH[channel]);
}

/*!
 * @brief PDM read data non blocking.
 * So the actually read data byte size in this function is (size * 2 * channelNums).
 * @param base PDM base pointer.
 * @param startChannel start channel number.
 * @param channelNums total enabled channelnums.
 * @param buffer received buffer address.
 * @param size number of 16bit data to read.
 */
void PDM_ReadNonBlocking(PDM_Type *base, uint32_t startChannel, uint32_t channelNums, int16_t *buffer, size_t size);
#endif

/*!
 * @brief PDM read fifo.
 * @note: This function support 16 bit only for IP version that only supports 16bit.
 *
 * @param base PDM base pointer.
 * @param startChannel start channel number.
 * @param channelNums total enabled channelnums.
 * @param buffer received buffer address.
 * @param size number of samples to read.
 * @param dataWidth sample width.
 */
void PDM_ReadFifo(
    PDM_Type *base, uint32_t startChannel, uint32_t channelNums, void *buffer, size_t size, uint32_t dataWidth);

#if defined(FSL_FEATURE_PDM_FIFO_WIDTH) && (FSL_FEATURE_PDM_FIFO_WIDTH == 4U)
/*!
 * @brief Reads data from the PDM FIFO.
 *
 * @param base PDM base pointer.
 * @param channel Data channel used.
 * @return Data in PDM FIFO.
 */
static inline uint32_t PDM_ReadData(PDM_Type *base, uint32_t channel)
{
    return base->DATACH[channel];
}
#endif

/*!
 * @brief Set the PDM channel gain.
 *
 * Please note for different quality mode, the valid gain value is different, reference RM for detail.
 * @param base PDM base pointer.
 * @param channel PDM channel index.
 * @param gain channel gain, the register gain value range is 0 - 15.
 */
void PDM_SetChannelGain(PDM_Type *base, uint32_t channel, pdm_df_output_gain_t gain);

#if !(defined(FSL_FEATURE_PDM_HAS_NO_HWVAD) && FSL_FEATURE_PDM_HAS_NO_HWVAD)
/*! @} */

/*!
 * @name Voice Activity Detector
 * @{
 */

/*!
 * @brief Configure voice activity detector.
 *
 * @param base PDM base pointer
 * @param config Voice activity detector configure structure pointer .
 */
void PDM_SetHwvadConfig(PDM_Type *base, const pdm_hwvad_config_t *config);

/*!
 * @brief PDM hwvad force output disable.
 *
 * @param base PDM base pointer
 * @param enable true is output force disable, false is output not force.
 */
static inline void PDM_ForceHwvadOutputDisable(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->VAD0_CTRL_2 &= ~PDM_VAD0_CTRL_2_VADFOUTDIS_MASK;
    }
    else
    {
        base->VAD0_CTRL_2 |= PDM_VAD0_CTRL_2_VADFOUTDIS_MASK;
    }
}

/*!
 * @brief PDM hwvad reset.
 * It will reset VADNDATA register and will clean all internal buffers, should be called when the PDM isn't running.
 *
 * @param base PDM base pointer
 */
static inline void PDM_ResetHwvad(PDM_Type *base)
{
    base->VAD0_CTRL_1 |= PDM_VAD0_CTRL_1_VADRST_MASK;
}
/*!
 * @brief Enable/Disable Voice activity detector.
 * Should be called when the PDM isn't running.
 * @param base PDM base pointer.
 * @param enable True means enable voice activity detector, false means disable.
 */
static inline void PDM_EnableHwvad(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->VAD0_CTRL_1 |= PDM_VAD0_CTRL_1_VADEN_MASK;
    }
    else
    {
        base->VAD0_CTRL_1 &= ~PDM_VAD0_CTRL_1_VADEN_MASK;
    }
}

/*!
 * @brief Enables the PDM Voice Detector interrupt requests.
 *
 * @param base PDM base pointer
 * @param mask interrupt source
 *     The parameter can be a combination of the following sources if defined.
 *     @arg kPDM_HWVADErrorInterruptEnable
 *     @arg kPDM_HWVADInterruptEnable
 */
static inline void PDM_EnableHwvadInterrupts(PDM_Type *base, uint32_t mask)
{
    base->VAD0_CTRL_1 |= mask;
}

/*!
 * @brief Disables the PDM Voice Detector interrupt requests.
 *
 * @param base PDM base pointer
 * @param mask interrupt source
 *     The parameter can be a combination of the following sources if defined.
 *     @arg kPDM_HWVADErrorInterruptEnable
 *     @arg kPDM_HWVADInterruptEnable
 */
static inline void PDM_DisableHwvadInterrupts(PDM_Type *base, uint32_t mask)
{
    base->VAD0_CTRL_1 &= ~mask;
}

/*!
 * @brief Clears the PDM voice activity detector status flags.
 *
 * @param base PDM base pointer
 * @param mask State mask,reference _pdm_hwvad_int_status.
 */
static inline void PDM_ClearHwvadInterruptStatusFlags(PDM_Type *base, uint32_t mask)
{
    base->VAD0_STAT = mask;
}

/*!
 * @brief Clears the PDM voice activity detector status flags.
 *
 * @param base PDM base pointer
 * @return status, reference _pdm_hwvad_int_status
 */
static inline uint32_t PDM_GetHwvadInterruptStatusFlags(PDM_Type *base)
{
    return base->VAD0_STAT & (PDM_VAD0_STAT_VADIF_MASK | PDM_VAD0_STAT_VADINSATF_MASK);
}

/*!
 * @brief Get the PDM voice activity detector initial flags.
 *
 * @param base PDM base pointer
 * @return initial flag.
 */
static inline uint32_t PDM_GetHwvadInitialFlag(PDM_Type *base)
{
    return base->VAD0_STAT & PDM_VAD0_STAT_VADINITF_MASK;
}

#if !(defined(FSL_FEATURE_PDM_HAS_NO_VADEF) && (FSL_FEATURE_PDM_HAS_NO_VADEF))
/*!
 * @brief Get the PDM voice activity detector voice detected flags.
 * NOte: this flag is auto cleared when voice gone.
 * @param base PDM base pointer
 * @return voice detected flag.
 */
static inline uint32_t PDM_GetHwvadVoiceDetectedFlag(PDM_Type *base)
{
    return base->VAD0_STAT & PDM_VAD0_STAT_VADEF_MASK;
}
#endif

/*!
 * @brief Enables/disables voice activity detector signal filter.
 *
 * @param base PDM base pointer
 * @param enable True means enable signal filter, false means disable.
 */
static inline void PDM_EnableHwvadSignalFilter(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->VAD0_SCONFIG |= PDM_VAD0_SCONFIG_VADSFILEN_MASK;
    }
    else
    {
        base->VAD0_SCONFIG &= ~PDM_VAD0_SCONFIG_VADSFILEN_MASK;
    }
}

/*!
 * @brief Configure voice activity detector signal filter.
 *
 * @param base PDM base pointer
 * @param enableMaxBlock If signal maximum block enabled.
 * @param signalGain Gain value for the signal energy.
 */
void PDM_SetHwvadSignalFilterConfig(PDM_Type *base, bool enableMaxBlock, uint32_t signalGain);

/*!
 * @brief Configure voice activity detector noise filter.
 *
 * @param base PDM base pointer
 * @param config Voice activity detector noise filter configure structure pointer .
 */
void PDM_SetHwvadNoiseFilterConfig(PDM_Type *base, const pdm_hwvad_noise_filter_t *config);

/*!
 * @brief Enables/disables voice activity detector zero cross detector.
 *
 * @param base PDM base pointer
 * @param enable True means enable zero cross detector, false means disable.
 */
static inline void PDM_EnableHwvadZeroCrossDetector(PDM_Type *base, bool enable)
{
    if (enable)
    {
        base->VAD0_ZCD |= PDM_VAD0_ZCD_VADZCDEN_MASK;
    }
    else
    {
        base->VAD0_ZCD &= ~PDM_VAD0_ZCD_VADZCDEN_MASK;
    }
}

/*!
 * @brief Configure voice activity detector zero cross detector.
 *
 * @param base PDM base pointer
 * @param config Voice activity detector zero cross detector configure structure pointer .
 */
void PDM_SetHwvadZeroCrossDetectorConfig(PDM_Type *base, const pdm_hwvad_zero_cross_detector_t *config);

/*!
 * @brief Reads noise data.
 *
 * @param base PDM base pointer.
 * @return Data in PDM noise data register.
 */
static inline uint16_t PDM_GetNoiseData(PDM_Type *base)
{
    return (uint16_t)base->VAD0_NDATA;
}

/*!
 * @brief set hwvad internal filter status .
 * Note: filter initial status should be asserted for two more cycles, then set it to normal operation.
 * @param base PDM base pointer.
 * @param status internal filter status.
 */
static inline void PDM_SetHwvadInternalFilterStatus(PDM_Type *base, pdm_hwvad_filter_status_t status)
{
    base->VAD0_CTRL_1 = (base->VAD0_CTRL_1 & (~PDM_VAD0_CTRL_1_VADST10_MASK)) | (uint32_t)status;
}

/*!
 * @brief set HWVAD in envelope based mode .
 * Recommand configurations,
 * @code
 * static const pdm_hwvad_config_t hwvadConfig = {
 *   .channel           = 0,
 *   .initializeTime    = 10U,
 *   .cicOverSampleRate = 0U,
 *   .inputGain         = 0U,
 *   .frameTime         = 10U,
 *   .cutOffFreq        = kPDM_HwvadHpfBypassed,
 *   .enableFrameEnergy = false,
 *   .enablePreFilter   = true,
};

 * static const pdm_hwvad_noise_filter_t noiseFilterConfig = {
 *   .enableAutoNoiseFilter = false,
 *   .enableNoiseMin        = true,
 *   .enableNoiseDecimation = true,
 *   .noiseFilterAdjustment = 0U,
 *   .noiseGain             = 7U,
 *   .enableNoiseDetectOR   = true,
 * };
 * @endcode
 * @param base PDM base pointer.
 * @param hwvadConfig internal filter status.
 * @param noiseConfig Voice activity detector noise filter configure structure pointer.
 * @param zcdConfig Voice activity detector zero cross detector configure structure pointer .
 * @param signalGain signal gain value.
 */
void PDM_SetHwvadInEnvelopeBasedMode(PDM_Type *base,
                                     const pdm_hwvad_config_t *hwvadConfig,
                                     const pdm_hwvad_noise_filter_t *noiseConfig,
                                     const pdm_hwvad_zero_cross_detector_t *zcdConfig,
                                     uint32_t signalGain);

/*!
 * brief set HWVAD in energy based mode .
 * Recommand configurations,
 * code
 * static const pdm_hwvad_config_t hwvadConfig = {
 *   .channel           = 0,
 *   .initializeTime    = 10U,
 *   .cicOverSampleRate = 0U,
 *   .inputGain         = 0U,
 *   .frameTime         = 10U,
 *   .cutOffFreq        = kPDM_HwvadHpfBypassed,
 *   .enableFrameEnergy = true,
 *   .enablePreFilter   = true,
};

 * static const pdm_hwvad_noise_filter_t noiseFilterConfig = {
 *   .enableAutoNoiseFilter = true,
 *   .enableNoiseMin        = false,
 *   .enableNoiseDecimation = false,
 *   .noiseFilterAdjustment = 0U,
 *   .noiseGain             = 7U,
 *   .enableNoiseDetectOR   = false,
 * };
 * code
 * param base PDM base pointer.
 * param hwvadConfig internal filter status.
 * param noiseConfig Voice activity detector noise filter configure structure pointer.
 * param zcdConfig Voice activity detector zero cross detector configure structure pointer .
 * param signalGain signal gain value, signal gain value should be properly according to application.
 */
void PDM_SetHwvadInEnergyBasedMode(PDM_Type *base,
                                   const pdm_hwvad_config_t *hwvadConfig,
                                   const pdm_hwvad_noise_filter_t *noiseConfig,
                                   const pdm_hwvad_zero_cross_detector_t *zcdConfig,
                                   uint32_t signalGain);

/*!
 * @brief   Enable/Disable  hwvad callback.

 * This function enable/disable the hwvad interrupt for the selected PDM peripheral.
 *
 * @param base Base address of the PDM peripheral.
 * @param vadCallback callback Pointer to store callback function, should be NULL when disable.
 * @param userData user data.
 * @param enable true is enable, false is disable.
 * @retval None.
 */
void PDM_EnableHwvadInterruptCallback(PDM_Type *base, pdm_hwvad_callback_t vadCallback, void *userData, bool enable);
/*! @} */
#endif

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Initializes the PDM handle.
 *
 * This function initializes the handle for the PDM transactional APIs. Call
 * this function once to get the handle initialized.
 *
 * @param base PDM base pointer.
 * @param handle PDM handle pointer.
 * @param callback Pointer to the user callback function.
 * @param userData User parameter passed to the callback function.
 */
void PDM_TransferCreateHandle(PDM_Type *base, pdm_handle_t *handle, pdm_transfer_callback_t callback, void *userData);

/*!
 * @brief PDM set channel transfer config.
 *
 * @param base PDM base pointer.
 * @param handle PDM handle pointer.
 * @param channel PDM channel.
 * @param config channel config.
 * @param format data format, support data width configurations,_pdm_data_width.
 * @retval kStatus_PDM_ChannelConfig_Failed or kStatus_Success.
 */
status_t PDM_TransferSetChannelConfig(
    PDM_Type *base, pdm_handle_t *handle, uint32_t channel, const pdm_channel_config_t *config, uint32_t format);

/*!
 * @brief Performs an interrupt non-blocking receive transfer on PDM.
 *
 * @note This API returns immediately after the transfer initiates.
 * Call the PDM_RxGetTransferStatusIRQ to poll the transfer status and check whether
 * the transfer is finished. If the return status is not kStatus_PDM_Busy, the transfer
 * is finished.
 *
 * @param base PDM base pointer
 * @param handle Pointer to the pdm_handle_t structure which stores the transfer state.
 * @param xfer Pointer to the pdm_transfer_t structure.
 * @retval kStatus_Success Successfully started the data receive.
 * @retval kStatus_PDM_Busy Previous receive still not finished.
 */
status_t PDM_TransferReceiveNonBlocking(PDM_Type *base, pdm_handle_t *handle, pdm_transfer_t *xfer);

/*!
 * @brief Aborts the current IRQ receive.
 *
 * @note This API can be called when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param base PDM base pointer
 * @param handle Pointer to the pdm_handle_t structure which stores the transfer state.
 */
void PDM_TransferAbortReceive(PDM_Type *base, pdm_handle_t *handle);

/*!
 * @brief Tx interrupt handler.
 *
 * @param base PDM base pointer.
 * @param handle Pointer to the pdm_handle_t structure.
 */
void PDM_TransferHandleIRQ(PDM_Type *base, pdm_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif /*_cplusplus*/

/*! @} */

#endif /* _FSL_PDM_H_ */
