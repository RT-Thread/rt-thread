/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_ADC_B_H
#define R_ADC_B_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "bsp_api.h"
#include "r_adc_api.h"
#include "r_adc_b_cfg.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup ADC_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ADC_B_CHANNEL_VALID_FOR_UNIT(channel_mask, unit_id)    ((ADC_B_UNIT_ID_0 == unit_id) ?             \
                                                                (channel_mask &                            \
                                                                 BSP_FEATURE_ADC_B_UNIT_0_CHANNELS_MASK) : \
                                                                (channel_mask & BSP_FEATURE_ADC_B_UNIT_1_CHANNELS_MASK))

#define R_ADC_B0_ADUGTR_UGAIN_INTEGER_Pos       (22)
#define R_ADC_B0_ADUGTR_UGAIN_INTEGER_Msk       (0xC00000)
#define R_ADC_B0_ADUGTR_UGAIN_FRACTIONAL_Pos    (0)
#define R_ADC_B0_ADUGTR_UGAIN_FRACTIONAL_Msk    (0x3FFFFF)

/***********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

/** ADC clock divider selection */
typedef enum e_adc_b_clock_divider
{
    ADC_B_CLOCK_DIV_1 = 0,             ///< ADC Clock Division 1/1
    ADC_B_CLOCK_DIV_2 = 1,             ///< ADC Clock Division 1/2
    ADC_B_CLOCK_DIV_3 = 2,             ///< ADC Clock Division 1/3
    ADC_B_CLOCK_DIV_4 = 3,             ///< ADC Clock Division 1/4
    ADC_B_CLOCK_DIV_5 = 4,             ///< ADC Clock Division 1/5
    ADC_B_CLOCK_DIV_6 = 5,             ///< ADC Clock Division 1/6
    ADC_B_CLOCK_DIV_7 = 6,             ///< ADC Clock Division 1/7
    ADC_B_CLOCK_DIV_8 = 7              ///< ADC Clock Division 1/8
} adc_b_clock_divider_t;

/** ADC_B Conversion Mode */
typedef enum e_adc_b_converter_mode
{
    ADC_B_CONVERTER_MODE_SINGLE_SCAN     = 0x0, ///< Single scan mode
    ADC_B_CONVERTER_MODE_CONTINUOUS_SCAN = 0x1, ///< Continuous scan mode
    ADC_B_CONVERTER_MODE_BACKGROUND_SCAN = 0x2, ///< Background continuous scan mode (Valid for Hybrid mode only)
} adc_b_converter_mode_t;

/** ADC_B Conversion Method */
typedef enum e_adc_b_conversion_method
{
    ADC_B_CONVERSION_METHOD_SAR        = 0x0, ///< SAR conversion method
    ADC_B_CONVERSION_METHOD_OVERSAMPLE = 0x1, ///< Oversampling conversion method
    ADC_B_CONVERSION_METHOD_HYBRID     = 0x2, ///< Hybrid conversion method
} adc_b_conversion_method_t;

/** ADC_B data data format definitions */
typedef enum e_adc_b_data_format
{
    ADC_B_DATA_FORMAT_16_BIT = 0,      ///< 16 bit adc_b data format
    ADC_B_DATA_FORMAT_14_BIT = 1,      ///< 14 bit adc_b data format
    ADC_B_DATA_FORMAT_12_BIT = 2,      ///< 12 bit adc_b data format
    ADC_B_DATA_FORMAT_10_BIT = 3,      ///< 10 bit adc_b data format
} adc_b_data_format_t;

/** ADC limiter clipping table id selection options */
typedef enum e_adc_b_limit_clip_table_id
{
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_NONE = 0, ///< Limiter Clip Disabled
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_0    = 1, ///< Limiter Clip Table 0
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_1    = 2, ///< Limiter Clip Table 1
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_2    = 3, ///< Limiter Clip Table 2
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_3    = 4, ///< Limiter Clip Table 3
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_4    = 5, ///< Limiter Clip Table 4
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_5    = 6, ///< Limiter Clip Table 5
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_6    = 7, ///< Limiter Clip Table 6
    ADC_B_LIMIT_CLIP_TABLE_SELECTION_7    = 8, ///< Limiter Clip Table 7
} adc_b_limit_clip_table_id_t;

/** ADC unit selection options */
typedef enum e_adc_b_unit_id
{
    ADC_B_UNIT_ID_0 = 0,               ///< ADC Unit ID 0
    ADC_B_UNIT_ID_1 = 1,               ///< ADC Unit ID 1
} adc_b_unit_id_t;

/** ADC unit selection options */
typedef enum e_adc_b_unit_mask
{
    ADC_B_UNIT_MASK_0         = 0x01,  ///< ADC Unit Mask 0
    ADC_B_UNIT_MASK_1         = 0x02,  ///< ADC Unit Mask 1
    ADC_B_UNIT_MASK_UNDEFINED = 0xFF,  ///< ADC Unit Mask Unknown
} adc_b_unit_mask_t;

/** ADC data sample addition and averaging options */
typedef enum e_adc_b_add_avg_mode
{
    ADC_B_ADD_AVERAGE_OFF             = 0x00, ///< Add/Average turned off for channels/sensors
    ADC_B_ADD_AVERAGE_ADDITION_ENABLE = 0x01, ///< Addition Mode Enabled
    ADC_B_ADD_AVERAGE_AVERAGE_ENABLE  = 0x02, ///< Average Mode Enabled
} adc_b_add_avg_mode_t;

/** ADC data sample addition and averaging options */
typedef enum e_adc_b_add_avg_count
{
    ADC_B_ADD_AVERAGE_1    = 0x00,     ///< Addition turned off for channels/sensors
    ADC_B_ADD_AVERAGE_2    = 0x01,     ///< Add/Average 2 samples
    ADC_B_ADD_AVERAGE_4    = 0x03,     ///< Add/Average 4 samples
    ADC_B_ADD_AVERAGE_8    = 0x04,     ///< Add/Average 8 samples
    ADC_B_ADD_AVERAGE_16   = 0x05,     ///< Add/Average 16 samples
    ADC_B_ADD_AVERAGE_32   = 0x06,     ///< Add/Average 32 samples
    ADC_B_ADD_AVERAGE_64   = 0x07,     ///< Add/Average 64 samples
    ADC_B_ADD_AVERAGE_128  = 0x08,     ///< Add/Average 128 samples
    ADC_B_ADD_AVERAGE_256  = 0x09,     ///< Add/Average 256 samples
    ADC_B_ADD_AVERAGE_512  = 0x0A,     ///< Add/Average 512 samples
    ADC_B_ADD_AVERAGE_1024 = 0x0B,     ///< Add/Average 1024 samples
} adc_b_add_avg_count_t;

/** ADC GPT Trigger options */
typedef enum e_adc_b_gpt_trigger
{
    ADC_B_GPT_TRIGGER_NONE = 0x00000000, ///< GPT Trigger Disabled
    ADC_B_GPT_TRIGGER_A0   = 0x00000001, ///< GPT Trigger A0
    ADC_B_GPT_TRIGGER_A1   = 0x00000002, ///< GPT Trigger A1
    ADC_B_GPT_TRIGGER_A2   = 0x00000004, ///< GPT Trigger A2
    ADC_B_GPT_TRIGGER_A3   = 0x00000008, ///< GPT Trigger A3
    ADC_B_GPT_TRIGGER_A4   = 0x00000010, ///< GPT Trigger A4
    ADC_B_GPT_TRIGGER_A5   = 0x00000020, ///< GPT Trigger A5
    ADC_B_GPT_TRIGGER_A6   = 0x00000040, ///< GPT Trigger A6
    ADC_B_GPT_TRIGGER_A7   = 0x00000080, ///< GPT Trigger A7
    ADC_B_GPT_TRIGGER_A8   = 0x00000100, ///< GPT Trigger A8
    ADC_B_GPT_TRIGGER_A9   = 0x00000200, ///< GPT Trigger A9
    ADC_B_GPT_TRIGGER_A10  = 0x00000400, ///< GPT Trigger A10
    ADC_B_GPT_TRIGGER_A11  = 0x00000800, ///< GPT Trigger A11
    ADC_B_GPT_TRIGGER_A12  = 0x00001000, ///< GPT Trigger A12
    ADC_B_GPT_TRIGGER_A13  = 0x00002000, ///< GPT Trigger A13
    ADC_B_GPT_TRIGGER_B0   = 0x00010000, ///< GPT Trigger B0
    ADC_B_GPT_TRIGGER_B1   = 0X00020000, ///< GPT Trigger B1
    ADC_B_GPT_TRIGGER_B2   = 0X00040000, ///< GPT Trigger B2
    ADC_B_GPT_TRIGGER_B3   = 0X00080000, ///< GPT Trigger B3
    ADC_B_GPT_TRIGGER_B4   = 0X00100000, ///< GPT Trigger B4
    ADC_B_GPT_TRIGGER_B5   = 0X00200000, ///< GPT Trigger B5
    ADC_B_GPT_TRIGGER_B6   = 0X00400000, ///< GPT Trigger B6
    ADC_B_GPT_TRIGGER_B7   = 0X00800000, ///< GPT Trigger B7
    ADC_B_GPT_TRIGGER_B8   = 0X01000000, ///< GPT Trigger B8
    ADC_B_GPT_TRIGGER_B9   = 0X02000000, ///< GPT Trigger B9
    ADC_B_GPT_TRIGGER_B10  = 0X04000000, ///< GPT Trigger B10
    ADC_B_GPT_TRIGGER_B11  = 0X08000000, ///< GPT Trigger B11
    ADC_B_GPT_TRIGGER_B12  = 0X10000000, ///< GPT Trigger B12
    ADC_B_GPT_TRIGGER_B13  = 0X20000000, ///< GPT Trigger B13
} adc_b_gpt_trigger_t;

/** ADC External Trigger options */
typedef enum e_adc_b_external_trigger
{
    ADC_B_EXTERNAL_TRIGGER_NONE   = 0x00, ///< External Trigger Disabled
    ADC_B_EXTERNAL_TRIGGER_ADTRG0 = 0X01, ///< External Trigger ADTRG0 Selection
    ADC_B_EXTERNAL_TRIGGER_ADTRG1 = 0X02, ///< External Trigger ADTRG1 Selection
} adc_b_external_trigger_t;

/** ADC Self-Diagnosis mode options */
typedef enum e_adc_b_self_diagnosis_mode
{
    ADC_B_SELF_DIAGNOSIS_DISABLED = 0, ///< Self-Diagnosis Disabled
    ADC_B_SELF_DIAGNOSIS_MODE_1   = 4, ///< Self-Diagnosis Mode 1
    ADC_B_SELF_DIAGNOSIS_MODE_2   = 5, ///< Self-Diagnosis Mode 2
    ADC_B_SELF_DIAGNOSIS_MODE_3   = 6, ///< Self-Diagnosis Mode 3
} adc_b_self_diagnosis_mode_t;

/** ADC Sample-and-Hold unit enable mask */
typedef enum e_adc_b_sample_and_hold_mask
{
    ADC_B_SAMPLE_AND_HOLD_MASK_NONE   = 0x00, ///< Sample-and-Hold Disabled
    ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_0 = 0x01, ///< Sample-and-Hold Unit 0
    ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_1 = 0x02, ///< Sample-and-Hold Unit 1
    ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_2 = 0x04, ///< Sample-and-Hold Unit 2
    ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_4 = 0x10, ///< Sample-and-Hold Unit 3
    ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_5 = 0x20, ///< Sample-and-Hold Unit 4
    ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_6 = 0x40, ///< Sample-and-Hold Unit 5
} adc_b_sample_and_hold_mask_t;

/** ADC PGA Gain */
typedef enum e_adc_b_pga_gain
{
    ADC_B_PGA_GAIN_DISABLED            = 0x00010000, ///< PGA Gain Disabled
    ADC_B_PGA_GAIN_DIFFERENTIAL_1_500  = 0x0101000E, ///< PGA Gain Setting 1.500
    ADC_B_PGA_GAIN_DIFFERENTIAL_2_333  = 0x0511000E, ///< PGA Gain Setting 2.333
    ADC_B_PGA_GAIN_DIFFERENTIAL_4_000  = 0x0921000E, ///< PGA Gain Setting 4.000
    ADC_B_PGA_GAIN_DIFFERENTIAL_5_667  = 0x0B31000E, ///< PGA Gain Setting 5.667
    ADC_B_PGA_GAIN_SINGLE_ENDED_2_500  = 0x0101000C, ///< PGA Gain Setting 2.500
    ADC_B_PGA_GAIN_SINGLE_ENDED_2_667  = 0x0201000C, ///< PGA Gain Setting 2.667
    ADC_B_PGA_GAIN_SINGLE_ENDED_2_857  = 0x0301000C, ///< PGA Gain Setting 2.857
    ADC_B_PGA_GAIN_SINGLE_ENDED_3_077  = 0x0401000C, ///< PGA Gain Setting 3.077
    ADC_B_PGA_GAIN_SINGLE_ENDED_3_333  = 0x0501000C, ///< PGA Gain Setting 3.333
    ADC_B_PGA_GAIN_SINGLE_ENDED_3_636  = 0x0601000C, ///< PGA Gain Setting 3.636
    ADC_B_PGA_GAIN_SINGLE_ENDED_4_000  = 0x0701000C, ///< PGA Gain Setting 4.000
    ADC_B_PGA_GAIN_SINGLE_ENDED_4_444  = 0x0801000C, ///< PGA Gain Setting 4.444
    ADC_B_PGA_GAIN_SINGLE_ENDED_5_000  = 0x0901000C, ///< PGA Gain Setting 5.000
    ADC_B_PGA_GAIN_SINGLE_ENDED_5_714  = 0x0A01000C, ///< PGA Gain Setting 5.714
    ADC_B_PGA_GAIN_SINGLE_ENDED_6_667  = 0x0B01000C, ///< PGA Gain Setting 6.667
    ADC_B_PGA_GAIN_SINGLE_ENDED_8_000  = 0x0C01000C, ///< PGA Gain Setting 8.000
    ADC_B_PGA_GAIN_SINGLE_ENDED_10_000 = 0x0D01000C, ///< PGA Gain Setting 10.000
    ADC_B_PGA_GAIN_SINGLE_ENDED_13_333 = 0x0E01000C, ///< PGA Gain Setting 13.333
} adc_b_pga_gain_t;

/** ADC Digital Filter Selection */
typedef enum e_adc_b_digital_filter_selection
{
    ADC_B_DIGITAL_FILTER_MODE_SINC3 = 0x1, ///< Digital filter Sinc3 filter (Oversampling Rate = 8)
    ADC_B_DIGITAL_FILTER_MODE_PHASE = 0x2, ///< Digital filter Minimum phase filter (Group delay < 2)
} adc_b_digital_filter_selection_t;

/** ADC Sampling State table selection options */
typedef enum e_adc_b_sampling_state_table_id
{
    ADC_B_SAMPLING_STATE_TABLE_0  = 0,  ///< Sampling State Table 0
    ADC_B_SAMPLING_STATE_TABLE_1  = 1,  ///< Sampling State Table 1
    ADC_B_SAMPLING_STATE_TABLE_2  = 2,  ///< Sampling State Table 2
    ADC_B_SAMPLING_STATE_TABLE_3  = 3,  ///< Sampling State Table 3
    ADC_B_SAMPLING_STATE_TABLE_4  = 4,  ///< Sampling State Table 4
    ADC_B_SAMPLING_STATE_TABLE_5  = 5,  ///< Sampling State Table 5
    ADC_B_SAMPLING_STATE_TABLE_6  = 6,  ///< Sampling State Table 6
    ADC_B_SAMPLING_STATE_TABLE_7  = 7,  ///< Sampling State Table 7
    ADC_B_SAMPLING_STATE_TABLE_8  = 8,  ///< Sampling State Table 8
    ADC_B_SAMPLING_STATE_TABLE_9  = 9,  ///< Sampling State Table 9
    ADC_B_SAMPLING_STATE_TABLE_10 = 10, ///< Sampling State Table 10
    ADC_B_SAMPLING_STATE_TABLE_11 = 11, ///< Sampling State Table 12
    ADC_B_SAMPLING_STATE_TABLE_12 = 12, ///< Sampling State Table 13
    ADC_B_SAMPLING_STATE_TABLE_13 = 13, ///< Sampling State Table 14
    ADC_B_SAMPLING_STATE_TABLE_14 = 14, ///< Sampling State Table 15
    ADC_B_SAMPLING_STATE_TABLE_15 = 15, ///< Sampling State Table 16
} adc_b_sampling_state_table_id_t;

/** ADC User Gain table options */
typedef enum e_adc_b_user_gain_table_id
{
    ADC_B_USER_GAIN_TABLE_SELECTION_DISABLED = 0, ///< User Gain disabled
    ADC_B_USER_GAIN_TABLE_SELECTION_0        = 1, ///< User Gain table 0
    ADC_B_USER_GAIN_TABLE_SELECTION_1        = 2, ///< User Gain table 1
    ADC_B_USER_GAIN_TABLE_SELECTION_2        = 3, ///< User Gain table 2
    ADC_B_USER_GAIN_TABLE_SELECTION_3        = 4, ///< User Gain table 3
    ADC_B_USER_GAIN_TABLE_SELECTION_4        = 5, ///< User Gain table 4
    ADC_B_USER_GAIN_TABLE_SELECTION_5        = 6, ///< User Gain table 5
    ADC_B_USER_GAIN_TABLE_SELECTION_6        = 7, ///< User Gain table 6
    ADC_B_USER_GAIN_TABLE_SELECTION_7        = 8, ///< User Gain table 7
} adc_b_user_gain_table_id_t;

/** ADC User Offset table options */
typedef enum e_adc_b_user_offset_table_selection_id
{
    ADC_B_USER_OFFSET_TABLE_SELECTION_DISABLED = 0, ///< User Offset disabled
    ADC_B_USER_OFFSET_TABLE_SELECTION_0        = 1, ///< User Offset table 0
    ADC_B_USER_OFFSET_TABLE_SELECTION_1        = 2, ///< User Offset table 1
    ADC_B_USER_OFFSET_TABLE_SELECTION_2        = 3, ///< User Offset table 2
    ADC_B_USER_OFFSET_TABLE_SELECTION_3        = 4, ///< User Offset table 3
    ADC_B_USER_OFFSET_TABLE_SELECTION_4        = 5, ///< User Offset table 4
    ADC_B_USER_OFFSET_TABLE_SELECTION_5        = 6, ///< User Offset table 5
    ADC_B_USER_OFFSET_TABLE_SELECTION_6        = 7, ///< User Offset table 6
    ADC_B_USER_OFFSET_TABLE_SELECTION_7        = 8, ///< User Offset table 7
} adc_b_user_offset_table_selection_id_t;

/* ADC_B Calibration Status */
typedef enum e_adc_b_converter_state
{
    ADC_B_CONVERTER_STATE_NONE               = 0, // Converter state uninitialized
    ADC_B_CONVERTER_STATE_ADC_0_CALIBRATING  = 1, // ADC 0 Internal Circuit and Gain/Offset Calibration
    ADC_B_CONVERTER_STATE_ADC_1_CALIBRATING  = 2, // ADC 1 Internal Circuit and Gain/Offset Calibration
    ADC_B_CONVERTER_STATE_SH_0_2_CALIBRATING = 3, // ADC 0 Sample-and-Hold Calibration
    ADC_B_CONVERTER_STATE_SH_4_6_CALIBRATING = 4, // ADC 1 Sample-and-Hold Calibration
    ADC_B_CONVERTER_STATE_READY              = 5, // Calibration is complete / ADC 0,1 are ready
    ADC_B_CONVERTER_STATE_CALIBRATION_FAIL   = 6, // Calibration has failed
} adc_b_converter_state_t;

/** ADC FIFO data type */
typedef struct st_adc_b_fifo_data
{
    uint32_t data                  : 16; ///< Conversion Data.
    uint32_t                       : 8;  // Reserved for future use.
    adc_channel_t physical_channel : 7;  ///< Channel number for data.
    uint32_t      err              : 1;  ///< Error bit.
} adc_b_fifo_data_t;

/** ADC FIFO Read data structure */
typedef struct st_adc_b_fifo_read
{
    uint8_t           count;           ///< Number of valid FIFO data read
    adc_b_fifo_data_t fifo_data[8];    ///< FIFO data
} adc_b_fifo_read_t;

/* ADC Virtual Channel configuration data */
typedef struct st_adc_b_virtual_channel_cfg
{
    /* State tracking data */
    adc_b_virtual_channel_t channel_id; ///< Channel ID

    /* Register data */
    union
    {
        uint32_t channel_cfg;             ///< Channel configuration register data
        struct
        {
            uint32_t group           : 5; ///< Scan group mask selection
            uint32_t                 : 3;
            uint32_t channel         : 7; ///< A/D conversion channel selection
            uint32_t differential    : 1; ///< Analog input mode selection (set to 1 if self-diagnosis is enabled)
            uint32_t sample_table_id : 4; ///< Sampling state table selection
            uint32_t                 : 12;
        } channel_cfg_bits;               ///< Channel configuration register bits
    };

    union
    {
        uint32_t channel_control_a;         ///< A/D conversion data operation control a
        struct
        {
            uint32_t digital_filter_id : 3; ///< Digital filter table index selection
            uint32_t                   : 13;
            uint32_t gain_table_id     : 4; ///< User gain table selection
            uint32_t                   : 4;
            uint32_t offset_table_id   : 4; ///< User offset table selection
            uint32_t                   : 4;
        } channel_control_a_bits;           ///< A/D conversion data operation control a bits
    };

    union
    {
        uint32_t channel_control_b;              ///< A/D conversion data operation control b
        struct
        {
            uint32_t addition_average_mode  : 2; ///< Addition/Averaging mode selection
            uint32_t                        : 6;
            uint32_t addition_average_count : 4; ///< Addition/Averaging times selection
            uint32_t                        : 4;
            uint32_t compare_match_enable   : 8; ///< Compare match enable
            uint32_t                        : 8;
        } channel_control_b_bits;                ///< A/D conversion data operation control b bits
    };

    union
    {
        uint32_t channel_control_c;             ///< A/D conversion data operation control c
        struct
        {
            uint32_t limiter_clip_table_id : 4; ///< Limiter clip table selection
            uint32_t                       : 12;
            uint32_t channel_data_format   : 2; ///< A/D conversion data format selection
            uint32_t                       : 2;
            uint32_t data_is_unsigned      : 1; ///< A/D conversion data sign selection (set to zero when self-diagnosis channel is selected)
            uint32_t                       : 11;
        } channel_control_c_bits;               ///< A/D conversion data operation control c bits
    };
} adc_b_virtual_channel_cfg_t;

/** ADC Group configuration data */
typedef struct st_adc_b_group_cfg
{
    /* State tracking data */
    adc_group_id_t  scan_group_id;                         ///< Scan Group ID
    adc_b_unit_id_t converter_selection;                   ///< Converter selection
    bool            scan_group_enable;                     ///< Scan Group enable state
    uint8_t         virtual_channel_count;                 ///< Virtual Channel count

    /* Register data */
    bool scan_end_interrupt_enable;                        ///< Scan End Interrupt enable
    adc_b_external_trigger_t external_trigger_enable_mask; ///< External Trigger mask
    elc_peripheral_t         elc_trigger_enable_mask;      ///< ELC Trigger mask
    adc_b_gpt_trigger_t      gpt_trigger_enable_mask;      ///< GPT Trigger mask
    uint8_t  conversion_start_delay;                       ///< Conversion start delay
    uint32_t self_diagnosis_mask;                          ///< Self-Diagnosis register data
    bool     limit_clip_interrupt_enable;                  ///< Limiter Clip interrupt enable
    adc_b_virtual_channel_cfg_t ** p_virtual_channels;     ///< Pointer to virtual channel configuration array of size virtual_channel_count
} adc_b_group_cfg_t;

/** ADC Scan Group configuration */
typedef struct st_adc_b_scan_cfg
{
/* The ADC operates on scan groups.
 * There may be up to eight scan groups configured at a time */
    uint8_t              group_count;  ///< Group Count
    adc_b_group_cfg_t ** p_adc_groups; ///< Pointer to ADC group configuration data
} adc_b_scan_cfg_t;

/** ADC ISR configuration structure */
typedef struct st_adc_b_isr_cfg
{
    uint8_t   calibration_end_ipl_adc_0;  ///< Calibration end IPL for A/D converter unit 0
    uint8_t   calibration_end_ipl_adc_1;  ///< Calibration end IPL for A/D converter unit 1
    uint8_t   conversion_error_ipl_adc_0; ///< Conversion error IPL for A/D converter unit 0
    uint8_t   conversion_error_ipl_adc_1; ///< Conversion error IPL for A/D converter unit 1
    uint8_t   fifo_overflow_ipl;          ///< FIFO Overflow IPL
    uint8_t   fifo_read_ipl_group_0;      ///< FIFO Read threshold request IPL for Group 0
    uint8_t   fifo_read_ipl_group_1;      ///< FIFO Read threshold request IPL for Group 1
    uint8_t   fifo_read_ipl_group_2;      ///< FIFO Read threshold request IPL for Group 2
    uint8_t   fifo_read_ipl_group_3;      ///< FIFO Read threshold request IPL for Group 3
    uint8_t   fifo_read_ipl_group_4;      ///< FIFO Read threshold request IPL for Group 4
    uint8_t   fifo_read_ipl_group_5;      ///< FIFO Read threshold request IPL for Group 5 (available on some MCUs)
    uint8_t   fifo_read_ipl_group_6;      ///< FIFO Read threshold request IPL for Group 6 (available on some MCUs)
    uint8_t   fifo_read_ipl_group_7;      ///< FIFO Read threshold request IPL for Group 7 (available on some MCUs)
    uint8_t   fifo_read_ipl_group_8;      ///< FIFO Read threshold request IPL for Group 8 (available on some MCUs)
    uint8_t   fifo_read_ipl_group_5678;   ///< FIFO Read threshold request IPL for Groups 5, 6, 7, and 8 (available on some MCUs)
    uint8_t   limit_clip_ipl;             ///< Limiter Clip IPL
    uint8_t   overflow_error_ipl_adc_0;   ///< Overflow error IPL for A/D converter unit 0
    uint8_t   overflow_error_ipl_adc_1;   ///< Overflow error IPL for A/D converter unit 1
    uint8_t   scan_end_ipl_group_0;       ///< Scan End IPL for A/D Group 0
    uint8_t   scan_end_ipl_group_1;       ///< Scan End IPL for A/D Group 1
    uint8_t   scan_end_ipl_group_2;       ///< Scan End IPL for A/D Group 2
    uint8_t   scan_end_ipl_group_3;       ///< Scan End IPL for A/D Group 3
    uint8_t   scan_end_ipl_group_4;       ///< Scan End IPL for A/D Group 4
    uint8_t   scan_end_ipl_group_5;       ///< Scan End IPL for A/D Group 5 (available on some MCUs)
    uint8_t   scan_end_ipl_group_6;       ///< Scan End IPL for A/D Group 6 (available on some MCUs)
    uint8_t   scan_end_ipl_group_7;       ///< Scan End IPL for A/D Group 7 (available on some MCUs)
    uint8_t   scan_end_ipl_group_8;       ///< Scan End IPL for A/D Group 8 (available on some MCUs)
    uint8_t   scan_end_ipl_group_5678;    ///< Scan End IRQ for A/D Groups 5, 6, 7, and 8 (available on some MCUs)
    IRQn_Type calibration_end_irq_adc_0;  ///< Calibration end IRQ for A/D converter unit 0
    IRQn_Type calibration_end_irq_adc_1;  ///< Calibration end IRQ for A/D converter unit 1
    IRQn_Type conversion_error_irq_adc_0; ///< Conversion error IRQ for A/D converter unit 0
    IRQn_Type conversion_error_irq_adc_1; ///< Conversion error IRQ for A/D converter unit 1
    IRQn_Type fifo_overflow_irq;          ///< FIFO Overflow IRQ
    IRQn_Type fifo_read_irq_group_0;      ///< FIFO Read threshold request IRQ for Group 0
    IRQn_Type fifo_read_irq_group_1;      ///< FIFO Read threshold request IRQ for Group 1
    IRQn_Type fifo_read_irq_group_2;      ///< FIFO Read threshold request IRQ for Group 2
    IRQn_Type fifo_read_irq_group_3;      ///< FIFO Read threshold request IRQ for Group 3
    IRQn_Type fifo_read_irq_group_4;      ///< FIFO Read threshold request IRQ for Group 4
    IRQn_Type fifo_read_irq_group_5;      ///< FIFO Read threshold request IRQ for Group 5
    IRQn_Type fifo_read_irq_group_6;      ///< FIFO Read threshold request IRQ for Group 6
    IRQn_Type fifo_read_irq_group_7;      ///< FIFO Read threshold request IRQ for Group 7
    IRQn_Type fifo_read_irq_group_8;      ///< FIFO Read threshold request IRQ for Group 8
    IRQn_Type fifo_read_irq_group_5678;   ///< FIFO Read threshold request IRQ for Groups 5, 6, 7, and 8
    IRQn_Type limit_clip_irq;             ///< Limiter Clip IRQ
    IRQn_Type overflow_error_irq_adc_0;   ///< Overflow error IRQ for A/D converter unit 0
    IRQn_Type overflow_error_irq_adc_1;   ///< Overflow error IRQ for A/D converter unit 1
    IRQn_Type scan_end_irq_group_0;       ///< Scan End IRQ for A/D Group 0
    IRQn_Type scan_end_irq_group_1;       ///< Scan End IRQ for A/D Group 1
    IRQn_Type scan_end_irq_group_2;       ///< Scan End IRQ for A/D Group 2
    IRQn_Type scan_end_irq_group_3;       ///< Scan End IRQ for A/D Group 3
    IRQn_Type scan_end_irq_group_4;       ///< Scan End IRQ for A/D Group 4
    IRQn_Type scan_end_irq_group_5;       ///< Scan End IRQ for A/D Group 5
    IRQn_Type scan_end_irq_group_6;       ///< Scan End IRQ for A/D Group 6
    IRQn_Type scan_end_irq_group_7;       ///< Scan End IRQ for A/D Group 7
    IRQn_Type scan_end_irq_group_8;       ///< Scan End IRQ for A/D Group 8
    IRQn_Type scan_end_irq_group_5678;    ///< Scan End IRQ for A/D Groups 5, 6, 7, and 8
} adc_b_isr_cfg_t;

/** ADC extended configuration data */
typedef struct st_adc_b_extended_cfg
{
    /* Data used to calculate register settings */
    adc_b_pga_gain_t pga_gain[4];       ///< PGA Gain selection
    union
    {
        uint8_t pga_debug_monitor_mask; // PGA monitor mode mask bits
        __PACKED_STRUCT
        {
            /* For debug only! Prolonged use of PGA Monitor function may deteriorate PGA characteristics. See user manual for more information.*/
            uint8_t unit_0 : 1;         // PGA monitor mode unit 0 bit - FOR DEBUG USE ONLY! DO NOT USE IN PRODUCTION!
            uint8_t unit_1 : 1;         // PGA monitor mode unit 1 bit - FOR DEBUG USE ONLY! DO NOT USE IN PRODUCTION!
            uint8_t unit_2 : 1;         // PGA monitor mode unit 2 bit - FOR DEBUG USE ONLY! DO NOT USE IN PRODUCTION!
            uint8_t unit_3 : 1;         // PGA monitor mode unit 3 bit - FOR DEBUG USE ONLY! DO NOT USE IN PRODUCTION!
            uint8_t        : 4;
        } pga_debug_monitor_mask_b;     ///< PGA monitor mode bitfield
    };

    /* Register Data */
    union
    {
        uint32_t bits;                                  // Digital filter slection mask bits
        __PACKED_STRUCT
        {
            adc_b_digital_filter_selection_t idx_0 : 2; // Digital filter selection 0
            uint32_t                               : 6;
            adc_b_digital_filter_selection_t idx_1 : 2; // Digital filter selection 1
            uint32_t                               : 6;
            adc_b_digital_filter_selection_t idx_2 : 2; // Digital filter selection 2
            uint32_t                               : 6;
            adc_b_digital_filter_selection_t idx_3 : 2; // Digital filter selection 3
            uint32_t                               : 6;
        } settings;
    } adc_filter_selection[2];

    union
    {
        uint32_t clock_control_data;       ///< Clock control register data
        __PACKED_STRUCT
        {
            uint32_t source_selection : 2; ///< ADC_B clock source selection
            uint32_t                  : 14;
            uint32_t divider          : 3; ///< ADC_B clock divider selection
            uint32_t                  : 13;
        } clock_control_bits;
    };
    union
    {
        uint32_t sync_operation_control; ///< Synchronous Operation Control register data
        __PACKED_STRUCT
        {
            uint32_t period_cycle       : 11;
            uint32_t                    : 5;
            uint32_t adc_0_disable_sync : 1;
            uint32_t adc_1_disable_sync : 1;
            uint32_t                    : 14;
        } sync_operation_control_bits;
    };
    union
    {
        uint32_t adc_b_mode;                      /// ADC_B converter mode register data
        __PACKED_STRUCT
        {
            adc_b_converter_mode_t    mode   : 2; ///< ADC_B converter mode
            adc_b_conversion_method_t method : 2; ///< ADC_B converter method
            uint8_t                          : 4;
        } adc_b_converter_mode[2];
    };
    uint32_t scan_group_enable;                   ///< Scan Group enable register data
    union
    {
        __PACKED_STRUCT
        {
            uint32_t converter_selection_0; ///< Converter Selection register data for groups 0,1,2,3
            uint32_t converter_selection_1; ///< Converter Selection register data for groups 4,5,6,7
            uint32_t converter_selection_2; ///< Converter Selection register data for group 8
        };
        uint8_t converter_selection[9];
    };
    union
    {
        uint16_t fifo_enable_mask;       ///< FIFO enable register data
        __PACKED_STRUCT
        {
            uint16_t fifo_0 : 1;         ///< FIFO enable for group 0
            uint16_t fifo_1 : 1;         ///< FIFO enable for group 1
            uint16_t fifo_2 : 1;         ///< FIFO enable for group 2
            uint16_t fifo_3 : 1;         ///< FIFO enable for group 3
            uint16_t fifo_4 : 1;         ///< FIFO enable for group 4
            uint16_t fifo_5 : 1;         ///< FIFO enable for group 5
            uint16_t fifo_6 : 1;         ///< FIFO enable for group 6
            uint16_t fifo_7 : 1;         ///< FIFO enable for group 7
            uint16_t fifo_8 : 1;         ///< FIFO enable for group 8
            uint32_t        : 7;
        } fifo_enable_mask_bits;
    };
    uint16_t fifo_interrupt_enable_mask; ///< FIFO interrupt enable register data
    union
    {
        __PACKED_STRUCT
        {
            uint32_t fifo_interrupt_level0; ///< FIFO data threshold interrupt level register data for Group 0 and 1
            uint32_t fifo_interrupt_level1; ///< FIFO data threshold interrupt level register data for Group 2 and 3
            uint32_t fifo_interrupt_level2; ///< FIFO data threshold interrupt level register data for Group 4 and 5
            uint32_t fifo_interrupt_level3; ///< FIFO data threshold interrupt level register data for Group 6 and 7
            uint32_t fifo_interrupt_level4; ///< FIFO data threshold interrupt level register data for Group 8
        };
        uint16_t fifo_interrupt_level[9];   ///< FIFO data threshold interrupt level
    };
    union
    {
        uint16_t start_trigger_delay_table[9];
        __PACKED_STRUCT
        {
            uint32_t start_trigger_delay_0;              ///< Start trigger delay register data for group 0 and 1
            uint32_t start_trigger_delay_1;              ///< Start trigger delay register data for group 2 and 3
            uint32_t start_trigger_delay_2;              ///< Start trigger delay register data for group 4 and 5
            uint32_t start_trigger_delay_3;              ///< Start trigger delay register data for group 6 and 7
            uint32_t start_trigger_delay_4;              ///< Start trigger delay register data for group 8
        };
    };
    uint32_t                calibration_adc_state;       ///< Calibration State register data
    uint32_t                calibration_sample_and_hold; ///< Calibration Sample and Hold register data
    const adc_b_isr_cfg_t * p_isr_cfg;                   ///< Pointer to ISR configuration
    union
    {
        uint32_t sampling_state_tables[8];               /// Sampling State Table register data
        uint16_t sampling_state_table[15];               ///< Sampling State Tables
    };
    uint8_t  sample_and_hold_enable_mask;                ///< Sample and Hold enable register data
    uint32_t sample_and_hold_config_012;                 ///< Sample and Hold configuration register data
    uint32_t sample_and_hold_config_456;                 ///< Sample and Hold configuration register data
    uint32_t conversion_state;                           ///< ADC 0/1 Successive Approximation Time Configuration
    int32_t  user_offset_tables[8];                      ///< User Offset Table register data
    uint32_t user_gain_tables[8];                        ///< User Gain Table register data
    uint32_t limiter_clip_interrupt_enable_mask;         ///< Limiter clip interrupt enable register data
    uint32_t limiter_clip_tables[8];                     ///< Limiter clip Table register data
} adc_b_extended_cfg_t;

/** ADC instance control block. DO NOT INITIALIZE.  Initialized in @ref adc_api_t::open(). */
typedef struct st_adc_b_instance_ctrl
{
    adc_b_converter_state_t adc_state;                   ///< ADC 0 converter State
    uint32_t                cached_adtrgenr;             ///< Cached conversion peripheral trigger bits, used when starting and stopping scans.
    uint32_t                cached_adsystr;              ///< Cached conversion software start bits, used when starting and stopping scans.
    uint32_t                trigger_disable_wait_cycles; ///< ADC clock cycles required to wait after disabling trigger input

    adc_cfg_t const * p_cfg;                             ///< Boolean to verify that the Unit has been initialized
    void (* p_callback)(adc_callback_args_t *);          ///< Pointer to callback that is called when an adc_b_event_t occurs.
    adc_callback_args_t * p_callback_memory;             ///< Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void                * p_context;                     ///< User defined context passed into callback function.
    uint32_t              initialized;                   ///< Initialized status of ADC_B.
    uint32_t              opened;                        ///< Open status of ADC_B.
} adc_b_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_adc_b;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_ADC_B_ScanCfg(adc_ctrl_t * p_ctrl, void const * const p_scan_cfg);
fsp_err_t R_ADC_B_InfoGet(adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info);
fsp_err_t R_ADC_B_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_B_ScanGroupStart(adc_ctrl_t * p_ctrl, adc_group_mask_t group_mask);
fsp_err_t R_ADC_B_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_B_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_ADC_B_Read(adc_ctrl_t * p_ctrl, adc_channel_t const channel_id, uint16_t * const p_data);
fsp_err_t R_ADC_B_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const channel_id, uint32_t * const p_data);
fsp_err_t R_ADC_B_FifoRead(adc_ctrl_t * p_ctrl, adc_group_mask_t const group_mask, adc_b_fifo_read_t * const p_data);
fsp_err_t R_ADC_B_Close(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_B_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset);
fsp_err_t R_ADC_B_Calibrate(adc_ctrl_t * const p_ctrl, void const * p_extend);
fsp_err_t R_ADC_B_CallbackSet(adc_ctrl_t * const          p_api_ctrl,
                              void (                    * p_callback)(adc_callback_args_t *),
                              void * const                p_context,
                              adc_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end defgroup ADC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
