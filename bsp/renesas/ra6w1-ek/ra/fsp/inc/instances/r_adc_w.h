/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_ADC_W_H
#define R_ADC_W_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "bsp_api.h"
#include "r_adc_api.h"
#include "r_adc_w_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup ADC_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ADC_CH0_DMAC_SRC_ADDR     (&AUXADC->FIFO0_DMA_DATA_REG)

/***********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

/** DMA enable */
typedef enum e_adc_w_dma_enable
{
    ADC_W_DMA_DISABLED = 0,            /**< DMA disabled */
    ADC_W_DMA_ENABLED  = 1,            /**< DMA enabled */
} adc_w_dma_enable_t;

/** ADC Interrupt Mode Threshold */
typedef enum e_adc_w_thd_interrupt_mode
{
    ADC_W_INTERRUPT_THD_NONE  = 0x000, /**< Threshold interrupt is disabled */
    ADC_W_INTERRUPT_THD_OVER  = 0x001, /**< An interrupt occurs when the conversion result exceeds the threshold. */
    ADC_W_INTERRUPT_THD_UNDER = 0x010, /**< An interrupt occurs when the conversion result is below the threshold. */
    ADC_W_INTERRUPT_THD_DIFF  = 0x100,
} adc_w_thd_interrupt_mode_t;

/** ADC Interrupt Mode FIFO */
typedef enum e_adc_w_fifo_interrupt_mode
{
    ADC_W_INTERRUPT_FIFO_NONE = 0x00,  /**< FIFO interrupt is disabled */
    ADC_W_INTERRUPT_FIFO_HALF = 0x01,  /**< An interrupt occurs when the FIFO is filled with four data. */
    ADC_W_INTERRUPT_FIFO_FULL = 0x10,
} adc_w_fifo_interrupt_mode_t;

/** ADC Sensor Wakeup Mode enable */
typedef enum e_adc_w_sensorwakeup_enable
{
    ADC_W_SENSOR_WAKEUP_DISABLED = 0,  /**< sensor wakeup disabled */
    ADC_W_SENSOR_WAKEUP_ENABLED  = 1,  /**< sensor wakeup enabled */
} adc_w_sensorwakeup_enable_t;

/** Threshold mode selection for sensor wakeup mode */
typedef enum e_adc_w_sensorwakeup_thd_mode
{
    ADC_W_SENSOR_WAKEUP_THD_OVER  = 0, /**< Over threshold */
    ADC_W_SENSOR_WAKEUP_THD_UNDER = 1, /**< Under threshold */
} adc_w_sensorwakeup_thd_mode_t;

/** Timer count clock source for sensor wakeup mode (base = 32.768KHz) */
typedef enum e_adc_w_timer_count_clock_source
{
    ADC_W_TIMER_COUNT_SOURCE_8 = 0,    /**< 7.81-msec period */
    ADC_W_TIMER_COUNT_SOURCE_31,       /**< 31.25-msec period */
    ADC_W_TIMER_COUNT_SOURCE_62,       /**< 62.5-msec period */
    ADC_W_TIMER_COUNT_SOURCE_250,      /**< 250-msec period */
    ADC_W_TIMER_COUNT_SOURCE_1000,     /**< 1000-msec period */
    ADC_W_TIMER_COUNT_SOURCE_4000,     /**< 4000-msec period */
    ADC_W_TIMER_COUNT_SOURCE_16000,    /**< 16000-msec period */
    ADC_W_TIMER_COUNT_SOURCE_64000,    /**< 64,000-msec period */
} adc_w_timer_count_clock_source_t;

/** Sample number for average in sensor wakeup mode */
typedef enum e_adc_w_sample_average
{
    ADC_W_SAMPLE_AVERAGE_4 = 0,        /**< 4-sample processing */
    ADC_W_SAMPLE_AVERAGE_8,            /**< 8-sample processing */
    ADC_W_SAMPLE_AVERAGE_16,           /**< 16-sample processing */
    ADC_W_SAMPLE_AVERAGE_32,           /**< 32-sample processing */
    ADC_W_SAMPLE_AVERAGE_64,           /**< 64-sample processing */
    ADC_W_SAMPLE_AVERAGE_128,          /**< 128-sample processing */
    ADC_W_SAMPLE_AVERAGE_256,          /**< 256-sample processing */
    ADC_W_SAMPLE_AVERAGE_512,          /**< 512-sample processing */
} adc_w_sample_average_t;

/** ADC_W active channel configuration */
typedef struct st_adc_w_scan_cfg
{
    uint32_t scan_mask;                ///< Channels/bits: bit 0 is ch0; bit 3 is ch3.
} adc_w_scan_cfg_t;

/** ADC chennel config structure */
typedef struct st_adc_w_channel_cfg
{
    adc_w_fifo_interrupt_mode_t interrupt_mode_fifo; ///< FIFO interrupt settings(four data/none)
    adc_w_thd_interrupt_mode_t  interrupt_mode_thd;  ///< Threshold interrupt setting(none/over/under)
    adc_w_dma_enable_t          dma_en;              ///< Enable/disable DMA support
    adc_w_sensorwakeup_enable_t sensorwakeup_en;     ///< Enable/disable sensor wakeup mode
    uint16_t thd_value;                              ///< Threshold Level for the channel
    adc_w_sensorwakeup_thd_mode_t threshold_mode;    ///< Use threshold as upper or lower limit
} adc_w_channel_cfg_t;

/** ADC extended configuration data */
typedef struct st_adc_w_extended_cfg
{
    uint16_t conversion_clockdiv;                                                        ///< Divider for conversion clock (fAD) setting
    uint16_t upper_bound_limit;                                                          ///< Setting upper limit conversion value
    uint16_t lower_bound_limit;                                                          ///< Setting lower limit conversion value
    adc_w_channel_cfg_t const      * p_channel_cfgs[BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS]; ///< Configuration for each channel, set to NULL if unused
    adc_w_timer_count_clock_source_t timer_count_clock_source;                           ///< Setting lower limit conversion value
    uint16_t               timer_value;                                                  ///< Timer count clock source for sensor wakeup mode (base = 32.768KHz)
    adc_w_sample_average_t sample_average;                                               ///< Sample number for average in sensor wakeup mode
} adc_w_extended_cfg_t;

/** ADC instance control block. DO NOT INITIALIZE.  Initialized in @ref adc_api_t::open(). */
typedef struct st_adc_w_instance_ctrl
{
    adc_cfg_t const * p_cfg;                    ///< Boolean to verify that the Unit has been initialized
    void (* p_callback)(adc_callback_args_t *); ///< Pointer to callback that is called when an adc_w_event_t occurs.
    void   * p_context;                         ///< User defined context passed into callback function.
    uint32_t initialized;                       ///< Initialized status of ADC_W.
    uint32_t opened;                            ///< Open status of ADC_W.
    uint32_t scan_mask;                         ///< Scan mask of enabled channels.
    uint32_t scan_cfg_mask;                     ///< Scan mask of configured channels.
} adc_w_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_adc_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_ADC_W_ScanCfg(adc_ctrl_t * p_ctrl, void const * const p_scan_cfg);
fsp_err_t R_ADC_W_InfoGet(adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info);
fsp_err_t R_ADC_W_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_W_ScanGroupStart(adc_ctrl_t * p_ctrl, adc_group_mask_t group_mask);
fsp_err_t R_ADC_W_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_W_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_ADC_W_Read(adc_ctrl_t * p_ctrl, adc_channel_t const channel_id, uint16_t * const p_data);
fsp_err_t R_ADC_W_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const channel_id, uint32_t * const p_data);
fsp_err_t R_ADC_W_Close(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_W_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset);
fsp_err_t R_ADC_W_Calibrate(adc_ctrl_t * const p_ctrl, void const * p_extend);
fsp_err_t R_ADC_W_CallbackSet(adc_ctrl_t * const          p_api_ctrl,
                              void (                    * p_callback)(adc_callback_args_t *),
                              void * const                p_context,
                              adc_callback_args_t * const p_callback_memory);

fsp_err_t R_ADC_W_SensorWakeupcfg(adc_ctrl_t * const p_ctrl);
fsp_err_t R_ADC_W_FifoRead(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);

/*******************************************************************************************************************//**
 * @} (end defgroup ADC_W)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
