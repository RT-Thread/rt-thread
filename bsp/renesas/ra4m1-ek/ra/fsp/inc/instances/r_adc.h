/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_ADC_H
#define R_ADC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>

/* Fixed width integer support. */
#include <stdint.h>

/* bool support */
#include <stdbool.h>
#include "bsp_api.h"
#include "r_adc_cfg.h"
#include "r_adc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup ADC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Typical values that can be used to modify the sample states.
 * The minimum sample state count value is either 6 or 7 depending on the clock ratios.
 * It is fixed to 7 based on the fact that at the lowest ADC conversion clock supported (1 MHz)
 * this extra state will lead to at worst a "1 microsecond" increase in conversion time.
 * At 60 MHz the extra sample state will add 16.7 ns to the conversion time.
 */
#define ADC_SAMPLE_STATE_COUNT_MIN             (7U)
#define ADC_SAMPLE_STATE_COUNT_MAX             (255U)

/* Typical values that can be used for the sample and hold counts for the channels 0-2*/
/* Minimum sample and hold states */
#define ADC_SAMPLE_STATE_HOLD_COUNT_MIN        (4U)

/* Default sample and hold states */
#define ADC_SAMPLE_STATE_HOLD_COUNT_DEFAULT    (24U)

/** For ADC Scan configuration adc_channel_cfg_t::scan_mask, adc_channel_cfg_t::scan_mask_group_b,
 *  adc_channel_cfg_t::add_mask and adc_channel_cfg_t::sample_hold_mask.
 *  Use bitwise OR to combine these masks for desired channels and sensors.    */
typedef enum e_adc_mask
{
    ADC_MASK_OFF         = (0U),                                   ///< No channels selected
    ADC_MASK_CHANNEL_0   = (1U << 0U),                             ///< Channel 0 mask
    ADC_MASK_CHANNEL_1   = (1U << 1U),                             ///< Channel 1 mask
    ADC_MASK_CHANNEL_2   = (1U << 2U),                             ///< Channel 2 mask
    ADC_MASK_CHANNEL_3   = (1U << 3U),                             ///< Channel 3 mask
    ADC_MASK_CHANNEL_4   = (1U << 4U),                             ///< Channel 4 mask
    ADC_MASK_CHANNEL_5   = (1U << 5U),                             ///< Channel 5 mask
    ADC_MASK_CHANNEL_6   = (1U << 6U),                             ///< Channel 6 mask
    ADC_MASK_CHANNEL_7   = (1U << 7U),                             ///< Channel 7 mask
    ADC_MASK_CHANNEL_8   = (1U << 8U),                             ///< Channel 8 mask
    ADC_MASK_CHANNEL_9   = (1U << 9U),                             ///< Channel 9 mask
    ADC_MASK_CHANNEL_10  = (1U << 10U),                            ///< Channel 10 mask
    ADC_MASK_CHANNEL_11  = (1U << 11U),                            ///< Channel 11 mask
    ADC_MASK_CHANNEL_12  = (1U << 12U),                            ///< Channel 12 mask
    ADC_MASK_CHANNEL_13  = (1U << 13U),                            ///< Channel 13 mask
    ADC_MASK_CHANNEL_14  = (1U << 14U),                            ///< Channel 14 mask
    ADC_MASK_CHANNEL_15  = (1U << 15U),                            ///< Channel 15 mask
    ADC_MASK_CHANNEL_16  = (1U << 16U),                            ///< Channel 16 mask
    ADC_MASK_CHANNEL_17  = (1U << 17U),                            ///< Channel 17 mask
    ADC_MASK_CHANNEL_18  = (1U << 18U),                            ///< Channel 18 mask
    ADC_MASK_CHANNEL_19  = (1U << 19U),                            ///< Channel 19 mask
    ADC_MASK_CHANNEL_20  = (1U << 20U),                            ///< Channel 20 mask
    ADC_MASK_CHANNEL_21  = (1U << 21U),                            ///< Channel 21 mask
    ADC_MASK_CHANNEL_22  = (1U << 22U),                            ///< Channel 22 mask
    ADC_MASK_CHANNEL_23  = (1U << 23U),                            ///< Channel 23 mask
    ADC_MASK_CHANNEL_24  = (1U << 24U),                            ///< Channel 24 mask
    ADC_MASK_CHANNEL_25  = (1U << 25U),                            ///< Channel 25 mask
    ADC_MASK_CHANNEL_26  = (1U << 26U),                            ///< Channel 26 mask
    ADC_MASK_CHANNEL_27  = (1U << 27U),                            ///< Channel 27 mask
    ADC_MASK_CHANNEL_28  = (1U << 28U),                            ///< Channel 28 mask
    ADC_MASK_TEMPERATURE = (1U << 29UL),                           ///< Temperature sensor channel mask
    ADC_MASK_VOLT        = (1U << 30UL),                           ///< Voltage reference channel mask
    ADC_MASK_SENSORS     = (ADC_MASK_TEMPERATURE | ADC_MASK_VOLT), ///< All sensor channel mask
} adc_mask_t;

/** ADC data sample addition and averaging options */
typedef enum e_adc_add
{
    ADC_ADD_OFF             = 0,       ///< Addition turned off for channels/sensors
    ADC_ADD_TWO             = 1,       ///< Add two samples
    ADC_ADD_THREE           = 2,       ///< Add three samples
    ADC_ADD_FOUR            = 3,       ///< Add four samples
    ADC_ADD_SIXTEEN         = 5,       ///< Add sixteen samples
    ADC_ADD_AVERAGE_TWO     = 0x81,    ///< Average two samples
    ADC_ADD_AVERAGE_FOUR    = 0x83,    ///< Average four samples
    ADC_ADD_AVERAGE_EIGHT   = 0x84,    ///< Average eight samples
    ADC_ADD_AVERAGE_SIXTEEN = 0x85,    ///< Add sixteen samples
} adc_add_t;

/** ADC clear after read definitions */
typedef enum e_adc_clear
{
    ADC_CLEAR_AFTER_READ_OFF = 0,      ///< Clear after read off
    ADC_CLEAR_AFTER_READ_ON  = 1       ///< Clear after read on
} adc_clear_t;

/* VREF configuration options, not all options are available on all MCUs. If the MCU does not have VREFAMPCNT or
 * ADHVREFCNT. */
typedef enum e_adc_vref_control
{
    /* Available selections on MCUs with VREFAMPCNT.
     * Reference Table 32.12 "VREFADC output voltage control list" in the RA2A1 manual R01UH0888EJ0100.*/

    ADC_VREF_CONTROL_VREFH       = 0,      ///< VREFAMPCNT reset value. VREFADC Output voltage is Hi-Z
    ADC_VREF_CONTROL_1_5V_OUTPUT = 25,     ///< BGR turn ON. VREFADC Output voltage is 1.5 V
    ADC_VREF_CONTROL_2_0V_OUTPUT = 29,     ///< BGR turn ON. VREFADC Output voltage is 2.0 V
    ADC_VREF_CONTROL_2_5V_OUTPUT = 31,     ///< BGR turn ON. VREFADC Output voltage is 2.5 V

    /* Available selections on MCUs with ADHVREFCNT.
     * Reference Section 35.2.31 "A/D High-Potential/Low-Potential Reference Voltage Control Register (ADHVREFCNT)"
     * in the RA4M1 manual R01UH0887EJ0100.*/

    ADC_VREF_CONTROL_AVCC0_AVSS0  = 0x0,   ///< High potential is AVCC0, low potential is AVSS0
    ADC_VREF_CONTROL_VREFH0_AVSS0 = 0x1,   ///< High potential is VREFH0, low potential is AVSS0

    /** High potential is internal reference voltage, low potential is AVSS0. When the high potential is set to the
     * internal reference voltage, wait 5 us after R_ADC_Open() to start an ADC measurement. */
    ADC_VREF_CONTROL_IVREF_AVSS0   = 0x2,
    ADC_VREF_CONTROL_AVCC0_VREFL0  = 0x10, ///< High potential is AVCC0, low potential is VREFL0
    ADC_VREF_CONTROL_VREFH0_VREFL0 = 0x11, ///< High potential is VREFH0, low potential is VREFL0

    /** High potential is internal reference voltage, low potential is VREFL0. When the high potential is set to the
     * internal reference voltage, wait 5 us after R_ADC_Open() to start an ADC measurement. */
    ADC_VREF_CONTROL_IVREF_VREFL0 = 0x12,
} adc_vref_control_t;

/** ADC sample state registers */
typedef enum e_adc_sample_state_reg
{
    ADC_SAMPLE_STATE_CHANNEL_0 = 0,         ///< Sample state register channel 0
    ADC_SAMPLE_STATE_CHANNEL_1,             ///< Sample state register channel 1
    ADC_SAMPLE_STATE_CHANNEL_2,             ///< Sample state register channel 2
    ADC_SAMPLE_STATE_CHANNEL_3,             ///< Sample state register channel 3
    ADC_SAMPLE_STATE_CHANNEL_4,             ///< Sample state register channel 4
    ADC_SAMPLE_STATE_CHANNEL_5,             ///< Sample state register channel 5
    ADC_SAMPLE_STATE_CHANNEL_6,             ///< Sample state register channel 6
    ADC_SAMPLE_STATE_CHANNEL_7,             ///< Sample state register channel 7
    ADC_SAMPLE_STATE_CHANNEL_8,             ///< Sample state register channel 8
    ADC_SAMPLE_STATE_CHANNEL_9,             ///< Sample state register channel 9
    ADC_SAMPLE_STATE_CHANNEL_10,            ///< Sample state register channel 10
    ADC_SAMPLE_STATE_CHANNEL_11,            ///< Sample state register channel 11
    ADC_SAMPLE_STATE_CHANNEL_12,            ///< Sample state register channel 12
    ADC_SAMPLE_STATE_CHANNEL_13,            ///< Sample state register channel 13
    ADC_SAMPLE_STATE_CHANNEL_14,            ///< Sample state register channel 14
    ADC_SAMPLE_STATE_CHANNEL_15,            ///< Sample state register channel 15
    ADC_SAMPLE_STATE_CHANNEL_16_TO_31 = -3, ///< Sample state register channel 16 to 31
} adc_sample_state_reg_t;

/** ADC comparison settings */
typedef enum e_adc_compare_cfg
{
    ADC_COMPARE_CFG_EVENT_OUTPUT_OR  = 0,
    ADC_COMPARE_CFG_EVENT_OUTPUT_XOR = 1,
    ADC_COMPARE_CFG_EVENT_OUTPUT_AND = 2,
    ADC_COMPARE_CFG_A_ENABLE         = R_ADC0_ADCMPCR_CMPAE_Msk | R_ADC0_ADCMPCR_CMPAIE_Msk,
    ADC_COMPARE_CFG_B_ENABLE         = R_ADC0_ADCMPCR_CMPBE_Msk | R_ADC0_ADCMPCR_CMPBIE_Msk,
    ADC_COMPARE_CFG_WINDOW_ENABLE    = R_ADC0_ADCMPCR_WCMPE_Msk,
} adc_compare_cfg_t;

/** ADC Window B channel */
typedef enum e_adc_window_b_channel
{
    ADC_WINDOW_B_CHANNEL_0 = 0,
    ADC_WINDOW_B_CHANNEL_1,
    ADC_WINDOW_B_CHANNEL_2,
    ADC_WINDOW_B_CHANNEL_3,
    ADC_WINDOW_B_CHANNEL_4,
    ADC_WINDOW_B_CHANNEL_5,
    ADC_WINDOW_B_CHANNEL_6,
    ADC_WINDOW_B_CHANNEL_7,
    ADC_WINDOW_B_CHANNEL_8,
    ADC_WINDOW_B_CHANNEL_9,
    ADC_WINDOW_B_CHANNEL_10,
    ADC_WINDOW_B_CHANNEL_11,
    ADC_WINDOW_B_CHANNEL_12,
    ADC_WINDOW_B_CHANNEL_13,
    ADC_WINDOW_B_CHANNEL_14,
    ADC_WINDOW_B_CHANNEL_15,
    ADC_WINDOW_B_CHANNEL_16,
    ADC_WINDOW_B_CHANNEL_17,
    ADC_WINDOW_B_CHANNEL_18,
    ADC_WINDOW_B_CHANNEL_19,
    ADC_WINDOW_B_CHANNEL_20,
    ADC_WINDOW_B_CHANNEL_21,
    ADC_WINDOW_B_CHANNEL_22,
    ADC_WINDOW_B_CHANNEL_23,
    ADC_WINDOW_B_CHANNEL_24,
    ADC_WINDOW_B_CHANNEL_25,
    ADC_WINDOW_B_CHANNEL_26,
    ADC_WINDOW_B_CHANNEL_27,
    ADC_WINDOW_B_CHANNEL_28,
    ADC_WINDOW_B_CHANNEL_TEMPERATURE = 32,
    ADC_WINDOW_B_CHANNEL_VOLT        = 33,
    ADC_WINDOW_B_CHANNEL_NONE        = 63,
} adc_window_b_channel_t;

/** ADC Window B comparison mode */
typedef enum e_adc_window_b_mode
{
    ADC_WINDOW_B_MODE_LESS_THAN_OR_OUTSIDE   = 0,
    ADC_WINDOW_B_MODE_GREATER_THAN_OR_INSIDE = R_ADC0_ADCMPBNSR_CMPLB_Msk,
} adc_window_b_mode_t;

/** ADC action for group A interrupts group B scan.
 * This enumeration is used to specify the priority between Group A and B in group mode.  */
typedef enum e_adc_group_a
{
    ADC_GROUP_A_PRIORITY_OFF             = 0,      ///< Group A ignored and does not interrupt ongoing group B scan
    ADC_GROUP_A_GROUP_B_WAIT_FOR_TRIGGER = 1,      ///< Group A interrupts Group B(single scan) which restarts at next Group B trigger
    ADC_GROUP_A_GROUP_B_RESTART_SCAN     = 3,      ///< Group A interrupts Group B(single scan) which restarts immediately after Group A scan is complete
    ADC_GROUP_A_GROUP_B_CONTINUOUS_SCAN  = 0x8001, ///< Group A interrupts Group B(continuous scan) which continues scanning without a new Group B trigger
} adc_group_a_t;

/** ADC double-trigger mode definitions */
typedef enum e_adc_double_trigger
{
    ADC_DOUBLE_TRIGGER_DISABLED         = 0, ///< Double-triggering disabled
    ADC_DOUBLE_TRIGGER_ENABLED          = 1, ///< Double-triggering enabled
    ADC_DOUBLE_TRIGGER_ENABLED_EXTENDED = 2, ///< Double-triggering enabled on both ADC ELC events
} adc_double_trigger_t;

/** ADC Trigger synchronous start source
 * Note: not all sources are available for all MCUs or channels. See User Manual for more information. */
typedef enum
{
    ADC_START_SOURCE_DISABLED       = 0x3F, ///< ELC/GPT Start source disabled (For use with software start)
    ADC_START_SOURCE_ASYNC_EXTERNAL = 0x00, ///< External Trigger Input
    ADC_START_SOURCE_ELC_AD0        = 0x09, ///< ELC_AD0 (Converter 0 and Converter 1)
    ADC_START_SOURCE_ELC_AD1        = 0x0A, ///< ELC_AD1 (Converter 0 and Converter 1)
    ADC_START_SOURCE_ELC_AD01       = 0x0B, ///< ELC_AD0 and ELC_AD1 (Converter 0) also ELC_AD0 and ELC_AD1 (Converter 1)
    ADC_START_SOURCE_GPT_A0_A4      = 0x11, ///< GTADTRA0 (Converter 0) and GTADTRA4 (Converter 1)
    ADC_START_SOURCE_GPT_B0_B4      = 0x12, ///< GTADTRB0 (Converter 0) and GTADTRB4 (Converter 1)
    ADC_START_SOURCE_GPT_A1_A5      = 0x13, ///< GTADTRA1 (Converter 0) and GTADTRB5 (Converter 1)
    ADC_START_SOURCE_GPT_B1_B5      = 0x14, ///< GTADTRB1 (Converter 0) and GTADTRB5 (Converter 1)
    ADC_START_SOURCE_GPT_A2_A6      = 0x15, ///< GTADTRA2 (Converter 0) and GTADTRA6 (Converter 1)
    ADC_START_SOURCE_GPT_B2_B6      = 0x16, ///< GTADTRB2 (Converter 0) and GTADTRB6 (Converter 1)
    ADC_START_SOURCE_GPT_A3_A7      = 0x17, ///< GTADTRA3 (Converter 0) and GTADTRA7 (Converter 1)
    ADC_START_SOURCE_GPT_B3_B7      = 0x18, ///< GTADTRB3 (Converter 0) and GTADTRB7 (Converter 1)
    ADC_START_SOURCE_GPT_AB0_AB4    = 0x19, ///< GTADTRA/B0 (Converter 0) and GTADTRA/B4 (Converter 1)
    ADC_START_SOURCE_GPT_AB1_AB5    = 0x1A, ///< GTADTRA/B1 (Converter 0) and GTADTRA/B5 (Converter 1)
    ADC_START_SOURCE_GPT_AB2_AB6    = 0x1B, ///< GTADTRA/B2 (Converter 0) and GTADTRA/B6 (Converter 1)
    ADC_START_SOURCE_GPT_AB3_AB7    = 0x1C, ///< GTADTRA/B3 (Converter 0) and GTADTRA/B7 (Converter 1)
} adc_start_source_t;

/** ADC sample state configuration */
typedef struct st_adc_sample_state
{
    adc_sample_state_reg_t reg_id;     ///< Sample state register ID
    uint8_t                num_states; ///< Number of sampling states for conversion. Ch16-20/21 use the same value.
} adc_sample_state_t;

/** ADC Window Compare configuration */
typedef struct st_adc_window_cfg
{
    uint32_t               compare_mask;       ///< Channel mask to compare with Window A
    uint32_t               compare_mode_mask;  ///< Per-channel condition mask for Window A
    adc_compare_cfg_t      compare_cfg;        ///< Window Compare configuration
    uint16_t               compare_ref_low;    ///< Window A lower reference value
    uint16_t               compare_ref_high;   ///< Window A upper reference value
    uint16_t               compare_b_ref_low;  ///< Window B lower reference value
    uint16_t               compare_b_ref_high; ///< Window A upper reference value
    adc_window_b_channel_t compare_b_channel;  ///< Window B channel
    adc_window_b_mode_t    compare_b_mode;     ///< Window B condition setting
} adc_window_cfg_t;

/** Extended configuration structure for ADC. */
typedef struct st_adc_extended_cfg
{
    adc_add_t            add_average_count;   ///< Add or average samples
    adc_clear_t          clearing;            ///< Clear after read
    adc_start_source_t   trigger;             ///< Trigger source for ADC
    adc_start_source_t   trigger_group_b;     ///< Trigger source for ADC group B; valid only for group mode
    adc_double_trigger_t double_trigger_mode; ///< Double-trigger mode setting
    adc_vref_control_t   adc_vref_control;    ///< VREFADC output voltage control
    uint8_t              enable_adbuf;        ///< Enable ADC Ring Buffer, Valid only to use along with DMAC transfer
    IRQn_Type            window_a_irq;        ///< IRQ number for Window Compare A interrupts
    IRQn_Type            window_b_irq;        ///< IRQ number for Window Compare B interrupts
    uint8_t              window_a_ipl;        ///< Priority for Window Compare A interrupts
    uint8_t              window_b_ipl;        ///< Priority for Window Compare B interrupts
} adc_extended_cfg_t;

/** ADC channel(s) configuration       */
typedef struct st_adc_channel_cfg
{
    uint32_t           scan_mask;          ///< Channels/bits: bit 0 is ch0; bit 15 is ch15.
    uint32_t           scan_mask_group_b;  ///< Valid for group modes.
    uint32_t           add_mask;           ///< Valid if add enabled in Open().
    adc_window_cfg_t * p_window_cfg;       ///< Pointer to Window Compare configuration
    adc_group_a_t      priority_group_a;   ///< Valid for group modes.
    uint8_t            sample_hold_mask;   ///< Channels/bits 0-2.
    uint8_t            sample_hold_states; ///< Number of states to be used for sample and hold. Affects channels 0-2.
} adc_channel_cfg_t;

/* Sample and hold Channel mask. Sample and hold is only available for channel 0,1,2*/
#define ADC_SAMPLE_HOLD_CHANNELS    (0x07U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** ADC instance control block. DO NOT INITIALIZE.  Initialized in @ref adc_api_t::open(). */
typedef struct
{
    R_ADC0_Type     * p_reg;                    // Base register for this unit
    adc_cfg_t const * p_cfg;
    uint32_t          opened;                   // Boolean to verify that the Unit has been initialized
    uint32_t          initialized;              // Initialized status of ADC
    uint32_t          scan_mask;                // Scan mask used for Normal scan
    uint16_t          scan_start_adcsr;

    void (* p_callback)(adc_callback_args_t *); // Pointer to callback that is called when an adc_event_t occurs.
    adc_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.

    /* Pointer to context to be passed into callback function */
    void * p_context;
} adc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_adc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ADC_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_ADC_ScanCfg(adc_ctrl_t * p_ctrl, void const * const p_channel_cfg);
fsp_err_t R_ADC_InfoGet(adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info);
fsp_err_t R_ADC_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_ScanGroupStart(adc_ctrl_t * p_ctrl, adc_group_mask_t group_id);
fsp_err_t R_ADC_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_ADC_Read(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);
fsp_err_t R_ADC_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);
fsp_err_t R_ADC_SampleStateCountSet(adc_ctrl_t * p_ctrl, adc_sample_state_t * p_sample);
fsp_err_t R_ADC_Close(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset);
fsp_err_t R_ADC_Calibrate(adc_ctrl_t * const p_ctrl, void const * p_extend);
fsp_err_t R_ADC_CallbackSet(adc_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(adc_callback_args_t *),
                            void * const                p_context,
                            adc_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end defgroup ADC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
