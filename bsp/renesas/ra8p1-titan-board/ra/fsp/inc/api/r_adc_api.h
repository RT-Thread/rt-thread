/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_ADC_API_H
#define R_ADC_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_ANALOG_INTERFACES
 * @defgroup ADC_API ADC Interface
 * @brief Interface for A/D Converters.
 *
 * @section ADC_API_SUMMARY Summary
 * The ADC interface provides standard ADC functionality including one-shot mode (single scan), continuous scan and
 * group scan. It also allows configuration of hardware and software triggers for starting scans. After each conversion
 * an interrupt can be triggered, and if a callback function is provided, the call back is invoked with the
 * appropriate event information.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#ifndef BSP_OVERRIDE_ADC_INCLUDE
 #include "r_elc_api.h"
#endif
#include "r_transfer_api.h"

#if __has_include("r_adc_device_types.h")
 #include "r_adc_device_types.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*****************************************************************************
 * Typedef definitions
 ******************************************************************************/
#ifndef BSP_OVERRIDE_ADC_MODE_T

/** ADC operation mode definitions  */
typedef enum e_adc_mode
{
    ADC_MODE_SINGLE_SCAN     = 0,      ///< Single scan - one or more channels
    ADC_MODE_GROUP_SCAN      = 1,      ///< Two trigger sources to trigger scan for two groups which contain one or more channels
    ADC_MODE_CONTINUOUS_SCAN = 2,      ///< Continuous scan - one or more channels
} adc_mode_t;

#endif

#ifndef BSP_OVERRIDE_ADC_RESOLUTION_T

/** ADC data resolution definitions */
typedef enum e_adc_resolution
{
    ADC_RESOLUTION_12_BIT = 0,         ///< 12 bit resolution
    ADC_RESOLUTION_10_BIT = 1,         ///< 10 bit resolution
    ADC_RESOLUTION_8_BIT  = 2,         ///< 8 bit resolution
    ADC_RESOLUTION_14_BIT = 3,         ///< 14 bit resolution
    ADC_RESOLUTION_16_BIT = 4,         ///< 16 bit resolution
    ADC_RESOLUTION_24_BIT = 5,         ///< 24 bit resolution
} adc_resolution_t;
#endif

/** ADC data alignment definitions  */
typedef enum e_adc_alignment
{
    ADC_ALIGNMENT_RIGHT = 0,           ///< Data alignment right
    ADC_ALIGNMENT_LEFT  = 1            ///< Data alignment left
} adc_alignment_t;

#ifndef BSP_OVERRIDE_ADC_TRIGGER_T

/** ADC trigger mode definitions */
typedef enum e_adc_trigger
{
    ADC_TRIGGER_SOFTWARE       = 0,    ///< Software trigger; not for group modes
    ADC_TRIGGER_SYNC_ELC       = 2,    ///< Synchronous trigger via ELC
    ADC_TRIGGER_ASYNC_EXTERNAL = 3,    ///< External asynchronous trigger; not for group modes
} adc_trigger_t;

#endif

#ifndef BSP_OVERRIDE_ADC_EVENT_T

/** ADC callback event definitions  */
typedef enum e_adc_event
{
    ADC_EVENT_SCAN_COMPLETE,           ///< Normal/Group A scan complete
    ADC_EVENT_SCAN_COMPLETE_GROUP_B,   ///< Group B scan complete
    ADC_EVENT_SCAN_COMPLETE_GROUP_C,   ///< Group C scan complete
    ADC_EVENT_CALIBRATION_COMPLETE,    ///< Calibration complete
    ADC_EVENT_CONVERSION_COMPLETE,     ///< Conversion complete
    ADC_EVENT_CALIBRATION_REQUEST,     ///< Calibration requested
    ADC_EVENT_CONVERSION_ERROR,        ///< Scan error
    ADC_EVENT_OVERFLOW,                ///< Overflow occurred
    ADC_EVENT_LIMIT_CLIP,              ///< Limiter clipping occurred
    ADC_EVENT_FIFO_READ_REQUEST,       ///< FIFO read requested
    ADC_EVENT_FIFO_OVERFLOW,           ///< FIFO overflow occurred
    ADC_EVENT_WINDOW_COMPARE_A,        ///< Window A comparison condition met
    ADC_EVENT_WINDOW_COMPARE_B,        ///< Window B comparison condition met
    ADC_EVENT_ZERO_CROSS_DETECTION,    ///< Zero-cross detection interrupt
    ADC_EVENT_CAPTURE_A,               ///< Capture A conversion complete
    ADC_EVENT_CAPTURE_B,               ///< Capture B conversion complete
} adc_event_t;

#endif

#ifndef BSP_OVERRIDE_ADC_CHANNEL_T

/** ADC channels */
typedef enum e_adc_channel
{
    ADC_CHANNEL_0           = 0,       ///< ADC channel 0
    ADC_CHANNEL_1           = 1,       ///< ADC channel 1
    ADC_CHANNEL_2           = 2,       ///< ADC channel 2
    ADC_CHANNEL_3           = 3,       ///< ADC channel 3
    ADC_CHANNEL_4           = 4,       ///< ADC channel 4
    ADC_CHANNEL_5           = 5,       ///< ADC channel 5
    ADC_CHANNEL_6           = 6,       ///< ADC channel 6
    ADC_CHANNEL_7           = 7,       ///< ADC channel 7
    ADC_CHANNEL_8           = 8,       ///< ADC channel 8
    ADC_CHANNEL_9           = 9,       ///< ADC channel 9
    ADC_CHANNEL_10          = 10,      ///< ADC channel 10
    ADC_CHANNEL_11          = 11,      ///< ADC channel 11
    ADC_CHANNEL_12          = 12,      ///< ADC channel 12
    ADC_CHANNEL_13          = 13,      ///< ADC channel 13
    ADC_CHANNEL_14          = 14,      ///< ADC channel 14
    ADC_CHANNEL_15          = 15,      ///< ADC channel 15
    ADC_CHANNEL_16          = 16,      ///< ADC channel 16
    ADC_CHANNEL_17          = 17,      ///< ADC channel 17
    ADC_CHANNEL_18          = 18,      ///< ADC channel 18
    ADC_CHANNEL_19          = 19,      ///< ADC channel 19
    ADC_CHANNEL_20          = 20,      ///< ADC channel 20
    ADC_CHANNEL_21          = 21,      ///< ADC channel 21
    ADC_CHANNEL_22          = 22,      ///< ADC channel 22
    ADC_CHANNEL_23          = 23,      ///< ADC channel 23
    ADC_CHANNEL_24          = 24,      ///< ADC channel 24
    ADC_CHANNEL_25          = 25,      ///< ADC channel 25
    ADC_CHANNEL_26          = 26,      ///< ADC channel 26
    ADC_CHANNEL_27          = 27,      ///< ADC channel 27
    ADC_CHANNEL_28          = 28,      ///< ADC channel 28
    ADC_CHANNEL_DUPLEX_A    = 50,      ///< Data duplexing register A
    ADC_CHANNEL_DUPLEX_B    = 51,      ///< Data duplexing register B
    ADC_CHANNEL_DUPLEX      = -4,      ///< Data duplexing register
    ADC_CHANNEL_TEMPERATURE = -3,      ///< Temperature sensor output
    ADC_CHANNEL_VOLT        = -2,      ///< Internal reference voltage
} adc_channel_t;

#endif

typedef enum e_adc_group_id
{
    ADC_GROUP_ID_0 = 0,                ///< Group ID 0
    ADC_GROUP_ID_1 = 1,                ///< Group ID 1
    ADC_GROUP_ID_2 = 2,                ///< Group ID 2
    ADC_GROUP_ID_3 = 3,                ///< Group ID 3
    ADC_GROUP_ID_4 = 4,                ///< Group ID 4
    ADC_GROUP_ID_5 = 5,                ///< Group ID 5
    ADC_GROUP_ID_6 = 6,                ///< Group ID 6
    ADC_GROUP_ID_7 = 7,                ///< Group ID 7
    ADC_GROUP_ID_8 = 8,                ///< Group ID 8
} adc_group_id_t;

typedef enum e_adc_group_mask
{
    ADC_GROUP_MASK_NONE = 0x000,       ///< Group Mask Unknown or None
    ADC_GROUP_MASK_0    = 0x001,       ///< Group Mask 0
    ADC_GROUP_MASK_1    = 0x002,       ///< Group Mask 1
    ADC_GROUP_MASK_2    = 0x004,       ///< Group Mask 2
    ADC_GROUP_MASK_3    = 0x008,       ///< Group Mask 3
    ADC_GROUP_MASK_4    = 0x010,       ///< Group Mask 4
    ADC_GROUP_MASK_5    = 0x020,       ///< Group Mask 5
    ADC_GROUP_MASK_6    = 0x040,       ///< Group Mask 6
    ADC_GROUP_MASK_7    = 0x080,       ///< Group Mask 7
    ADC_GROUP_MASK_8    = 0x100,       ///< Group Mask 8
    ADC_GROUP_MASK_ALL  = 0x1FF,       ///< All Groups
} adc_group_mask_t;

/** ADC states. */
typedef enum e_adc_state
{
    ADC_STATE_IDLE                    = 0, ///< ADC is idle
    ADC_STATE_SCAN_IN_PROGRESS        = 1, ///< ADC scan in progress
    ADC_STATE_CALIBRATION_IN_PROGRESS = 2, ///< ADC calibration in progress - Not used by all ADC instances
} adc_state_t;

/** ADC status. */
typedef struct st_adc_status
{
    adc_state_t state;                 ///< Current state
} adc_status_t;

/** ADC callback arguments definitions  */
typedef struct st_adc_callback_args
{
    uint16_t         unit;             ///< ADC device in use
    adc_event_t      event;            ///< ADC callback event
    void           * p_context;        ///< Placeholder for user data
    adc_channel_t    channel;          ///< Channel of conversion result
    uint64_t         channel_mask;     ///< Channel mask for conversion result. Only valid for r_adc_b and r_sdadc_b
    adc_group_mask_t group_mask;       ///< Group Mask
} adc_callback_args_t;

#ifndef BSP_OVERRIDE_ADC_INFO_T

/** ADC Information Structure for Transfer Interface */
typedef struct st_adc_info
{
    __I void * p_address;                   ///< The address to start reading the data from
    uint32_t   length;                      ///< The total number of transfers to read

    transfer_size_t  transfer_size;         ///< The size of each transfer
    elc_peripheral_t elc_peripheral;        ///< Name of the peripheral in the ELC list
    elc_event_t      elc_event;             ///< Name of the ELC event for the peripheral
    uint32_t         calibration_data;      ///< Temperature sensor calibration data (0xFFFFFFFF if unsupported) for reference voltage
    uint16_t         room_calibration_data; ///< Room temperature sensor calibration data (0xFFFFFFFF if unsupported) for reference voltage
    uint16_t         low_calibration_data;  ///< Low temperature sensor calibration data (0xFFFFFFFF if unsupported) for reference voltage
    int16_t          slope_microvolts;      ///< Temperature sensor slope in microvolts/degrees C
} adc_info_t;

#endif

/** ADC general configuration  */
typedef struct st_adc_cfg
{
    uint16_t         unit;                             ///< ADC unit to be used
    adc_mode_t       mode;                             ///< ADC operation mode
    adc_resolution_t resolution;                       ///< ADC resolution
    adc_alignment_t  alignment;                        ///< Specify left or right alignment; ignored if addition used
    adc_trigger_t    trigger;                          ///< Default and Group A trigger source
    IRQn_Type        scan_end_irq;                     ///< Scan end IRQ number
    IRQn_Type        scan_end_b_irq;                   ///< Scan end group B IRQ number
    IRQn_Type        scan_end_c_irq;                   ///< Scan end group C IRQ number
    uint8_t          scan_end_ipl;                     ///< Scan end interrupt priority
    uint8_t          scan_end_b_ipl;                   ///< Scan end group B interrupt priority
    uint8_t          scan_end_c_ipl;                   ///< Scan end group C interrupt priority
    void (* p_callback)(adc_callback_args_t * p_args); ///< Callback function; set to NULL for none
    void       * p_context;                            ///< Placeholder for user data. Passed to the user callback in @ref adc_callback_args_t.
    void const * p_extend;                             ///< Extension parameter for hardware specific settings
} adc_cfg_t;

/** ADC control block. Allocate using driver instance control structure from driver instance header file. */
typedef void adc_ctrl_t;

/** ADC functions implemented at the HAL layer will follow this API. */
typedef struct st_adc_api
{
    /** Initialize ADC Unit;  apply power, set the operational mode, trigger sources, interrupt priority,
     * and configurations common to all channels and sensors.
     *
     * @pre Configure peripheral clocks, ADC pins and IRQs prior to calling this function.
     * @param[in]  p_ctrl  Pointer to control handle structure
     * @param[in]  p_cfg   Pointer to configuration structure
     */
    fsp_err_t (* open)(adc_ctrl_t * const p_ctrl, adc_cfg_t const * const p_cfg);

    /** Configure the scan including the channels, groups, and scan triggers to be used for the unit that
     * was initialized in the open call.  Some configurations are not supported for all implementations.
     * See implementation for details.
     *
     * @param[in]  p_ctrl     Pointer to control handle structure
     * @param[in]  p_extend   See implementation for details
     */
    fsp_err_t (* scanCfg)(adc_ctrl_t * const p_ctrl, void const * const p_extend);

    /** Start the scan (in case of a software trigger), or enable the hardware trigger.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* scanStart)(adc_ctrl_t * const p_ctrl);

    /** Start the scan group (in case of a software trigger), or enable the hardware trigger.
     *
     * @param[in]  p_ctrl     Pointer to control handle structure
     * @param[in]  group_mask Mask of groups to start
     */
    fsp_err_t (* scanGroupStart)(adc_ctrl_t * p_ctrl, adc_group_mask_t group_mask);

    /** Stop the ADC scan (in case of a software trigger), or disable the hardware trigger.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* scanStop)(adc_ctrl_t * const p_ctrl);

    /** Check scan status.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     * @param[out] p_status Pointer to store current status in
     */
    fsp_err_t (* scanStatusGet)(adc_ctrl_t * const p_ctrl, adc_status_t * p_status);

    /** Read ADC conversion result.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     * @param[in]  reg_id   ADC channel to read (see enumeration adc_channel_t)
     * @param[in]  p_data   Pointer to variable to load value into.
     */
    fsp_err_t (* read)(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);

    /** Read ADC conversion result into a 32-bit word.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     * @param[in]  reg_id   ADC channel to read (see enumeration adc_channel_t)
     * @param[in]  p_data   Pointer to variable to load value into.
     */
    fsp_err_t (* read32)(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);

    /** Calibrate ADC or associated PGA (programmable gain amplifier).  The driver may require implementation specific
     * arguments to the p_extend input. Not supported for all implementations. See implementation for details.
     *
     * @param[in]  p_ctrl    Pointer to control handle structure
     * @param[in]  p_extend  Pointer to implementation specific arguments
     */
    fsp_err_t (* calibrate)(adc_ctrl_t * const p_ctrl, void const * p_extend);

    /** Set offset for input PGA configured for differential input. Not supported for all implementations.
     *  See implementation for details.
     *
     * @param[in]  p_ctrl    Pointer to control handle structure
     * @param[in]  reg_id    ADC channel to read (see enumeration adc_channel_t)
     * @param[in]  offset    See implementation for details.
     */
    fsp_err_t (* offsetSet)(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t const offset);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the ADC control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(adc_ctrl_t * const p_ctrl, void (* p_callback)(adc_callback_args_t *),
                              void * const p_context, adc_callback_args_t * const p_callback_memory);

    /** Close the specified ADC unit by ending any scan in progress, disabling interrupts, and removing power to the
     * specified A/D unit.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* close)(adc_ctrl_t * const p_ctrl);

    /** Return the ADC data register address of the first (lowest number) channel and the total number of bytes
     * to be read in order for the DTC/DMAC to read the conversion results of all configured channels.
     * Return the temperature sensor calibration and slope data.
     *
     * @param[in]   p_ctrl       Pointer to control handle structure
     * @param[out]  p_adc_info   Pointer to ADC information structure
     */
    fsp_err_t (* infoGet)(adc_ctrl_t * const p_ctrl, adc_info_t * const p_adc_info);
} adc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_adc_instance
{
    adc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    adc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    void const      * p_channel_cfg;   ///< Pointer to the channel configuration structure for this instance
    adc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} adc_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup ADC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
