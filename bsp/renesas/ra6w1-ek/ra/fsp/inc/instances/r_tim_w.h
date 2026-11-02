/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_TIM_W_H
#define R_TIM_W_H

/*******************************************************************************************************************//**
 * @addtogroup TIM_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define TIM_W_PWM_MAX              (0xFFFFUL)
#define TIM_W_COUNTER_MAX_VALUE    (0xFFFFFFFFU)

#define TIM_W_TIM1                 (0U)
#define TIM_W_TIM2                 (1U)
#define TIM_W_TIM3                 (2U)
#define TIM_W_TIM4                 (3U)
#define TIM_W_TIM5                 (4U)
#define TIM_W_TIM6                 (5U)
#define TIM_W_TIM7                 (6U)
#define TIM_W_TIM8                 (7U)

#define TIM_W_PWM_SYNC_TIMER2      (0b00000001)
#define TIM_W_PWM_SYNC_TIMER3      (0b00000010)
#define TIM_W_PWM_SYNC_TIMER4      (0b00000100)

#if BSP_MCU_GROUP_RA6W3
 #define TIM_W_TIM9                (8U)
 #define TIM_W_TIM10               (9U)

 #define TIM_W_CHANNEL_MAX         (TIM_W_TIM10)

 #define TIM_W_PWM_SYNC_TIMER5     (0b00001000)
 #define TIM_W_PWM_SYNC_TIMER6     (0b00010000)
 #define TIM_W_PWM_SYNC_TIMER7     (0b00100000)
 #define TIM_W_PWM_SYNC_TIMER8     (0b01000000)
 #define TIM_W_PWM_SYNC_TIMER9     (0b10000000)
#elif defined(BSP_MCU_GROUP_RA6B1) || defined(BSP_MCU_GROUP_RA6U1)
 #define TIM_W_PWM_SYNC_TIMER5     (0b00001000)
 #define TIM_W_PWM_SYNC_TIMER6     (0b00010000)
 #define TIM_W_PWM_SYNC_TIMER7     (0b00100000)

 #define TIM_W_CHANNEL_MAX         (TIM_W_TIM8)
#else
 #define TIM_W_CHANNEL_MAX         (TIM_W_TIM8)
#endif

#if BSP_FEATURE_TIM_W_LINEAR_SRC_DIV_STEP
 #define TIM_W_SOURCE_DIV_MAX      (TIMER_SOURCE_DIV_32)
#else
 #define TIM_W_SOURCE_DIV_MAX      (TIMER_SOURCE_DIV_256)
#endif

/** Offset to make the TIM_W HW channels 0-based for the r_tim_w driver. */
#if (BSP_FEATURE_TIM_W_VALID_CHANNEL_MASK & 0x1U)
 #define TIM_W_CHANNEL_OFFSET      (0U)
#elif (BSP_FEATURE_TIM_W_VALID_CHANNEL_MASK & 0x2U)
 #define TIM_W_CHANNEL_OFFSET      (1U)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Count source clock */
typedef enum e_tim_w_clock
{
    TIM_W_CLOCK_LP_CLK = 0,            ///< Select LP Clk to supply timer
    TIM_W_CLOCK_DIVN   = 1,            ///< Select Divn_clk clk to supply timer
} tim_w_clock_t;

/** Trigger edge for pulse period measurement mode and event counting mode. */
typedef enum e_tim_w_gpio_trigger
{
    TIM_W_GPIO_TRIGGER_DISABLED     = 0, ///< Disable external trigger events
    TIM_W_GPIO_TRIGGER_EDGE_RISING  = 1, ///< Measurement starts or events are counted on rising edge
    TIM_W_GPIO_TRIGGER_EDGE_FALLING = 2, ///< Measurement starts or events are counted on falling edge
} tim_w_gpio_trigger_t;

#if !BSP_FEATURE_ELC_MISSING

/** Tasks available for elc */
typedef enum e_tim_w_elc_task
{
    TIM_W_ELC_DISABLED = 0U,           ///< TIM_CLK_EN = 0
    TIM_W_ELC_START,                   ///< TIM_EN = 1
    TIM_W_ELC_STOP,                    ///< TIM_EN = 0
    TIM_W_ELC_COUNT_UP,                ///< PULSE_CNT += 1, edge counter mode only
    TIM_W_ELC_CLEAR,                   ///< TIM_TIMER_VALUE = initial count up/down value
    TIM_W_ELC_ONESHOT_TRIGGER,         ///< Trigger one-shot
    TIM_W_ELC_CAPTURE,                 ///< Trigger a capture operation
    TIM_W_ELC_PAUSE_RESUME,            ///< Toggle TIM_PAUSE
} tim_w_elc_task_t;
#endif

#if BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH

/** Channel available operations */
typedef enum e_tim_w_ccm_operation
{
    TIM_W_CCM_OPERATION_CAPTURE       = 0,
    TIM_W_CCM_OPERATION_COMPARE_MATCH = 1,
} tim_w_ccm_operation_t;
#endif

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref timer_api_t::open is called. */
typedef struct st_tim_w_instance_ctrl
{
    uint32_t            open;                     ///< Whether or not channel is open
    const timer_cfg_t * p_cfg;                    ///< Pointer to initial configurations
    TIMER_Type        * p_reg;                    ///< Base register for this channel

    void (* p_callback)(timer_callback_args_t *); ///< Pointer to callback
    timer_callback_args_t * p_callback_memory;    ///< Pointer to optional callback argument memory
    void * p_context;                             ///< Pointer to context to be passed into callback function
} tim_w_instance_ctrl_t;

/** Configuration structure for non-periodic Capture/CompareMatch channels. */
typedef struct st_tim_w_operation_channel_cfg
{
#if BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH
    tim_w_ccm_operation_t operation;     ///< Operation channel will be used as capture or compare match
    uint32_t              compare_value; ///< Select the operation channel's compare match value
#endif
    bsp_io_port_pin_t    capture_source; ///< Configuration for GPIOs used as a source for capture operation.
    tim_w_gpio_trigger_t capture_trigger;
    uint8_t              ccm_operation_ipl;
    IRQn_Type            ccm_operation_irq;
} tim_w_operation_channel_cfg;

/** Extended Configuration for Capture/Compare-Match Operations. */
typedef struct st_tim_w_extended_ccm_cfg
{
    /** When set, first capture value is persistant,
     * next captures on the same register will not overwrite the first value.
     */
    bool single_capture_mode;

#if BSP_FEATURE_TIM_W_SUPPORTS_SEQ_CAPTURES

    /** When set, sequential capturing is activated.
     *  When the number of capture triggers reaches this number,
     *  a generic irq will activate. Both gpio and elc can
     *  trigger sequential captures.
     */
    uint8_t seq_captures;
#endif

#if !BSP_FEATURE_ELC_MISSING
    uint8_t elc_channel;                             ///< Channel used for ELC Capture.
#endif

    tim_w_operation_channel_cfg * p_ccm_channel_cfg; ///< Configuration Array of Operation Channels
    uint8_t ccm_channel_size;                        ///< Number of Operation Channels used for Capture or Compare-Match operations.
} tim_w_extended_ccm_cfg;

/** TIM_W extension configures the output pins for TIM_W. */
typedef struct st_tim_w_extended_cfg
{
    bool              free_run;        ///< Free-running mode (up-count only)
    tim_w_clock_t     count_source;    ///< Clock source supplied to timer
    timer_direction_t direction;       ///< Counter direction

#if BSP_FEATURE_TIM_W_SUPPORTS_OVERFLOW_UNDERFLOW
    uint8_t   overflow_ipl;
    IRQn_Type overflow_irq;
    uint8_t   underflow_ipl;
    IRQn_Type underflow_irq;
#endif

    /* PWM Configuration Options */
    uint16_t pwm_sync_map;             ///< Channels to be synchronously started with TIM on PWM mode

#if !BSP_FEATURE_ELC_MISSING

    /* ELC Configuration Options */
    tim_w_elc_task_t elc_task;
#endif

    /* External GPIO used in One-Shot or Edge Detect Modes. */
    bsp_io_port_pin_t gpio_source;

    tim_w_gpio_trigger_t gpio_trigger;

    bool oneshot_switch_to_periodic;   ///< Enable auto mode switch from oneshot to periodic when oneshot elapses

    /* Delay before oneshot pulse begins.
     * If oneshot_switch_to_periodic is set, this delay also represents the period in periodic mode.
     */
    uint32_t oneshot_delay;

    /* Configuration of advanced Capture/Compare-Match Operations */
    tim_w_extended_ccm_cfg * p_ccm_cfg;
} tim_w_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_tim_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_TIM_W_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TIM_W_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TIM_W_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TIM_W_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TIM_W_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TIM_W_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_TIM_W_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_TIM_W_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_TIM_W_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_TIM_W_CallbackSet(timer_ctrl_t * const          p_api_ctrl,
                              void (                      * p_callback)(timer_callback_args_t *),
                              void * const                  p_context,
                              timer_callback_args_t * const p_callback_memory);
fsp_err_t R_TIM_W_Close(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TIM_W_CompareMatchSet(timer_ctrl_t * const        p_ctrl,
                                  uint32_t const              compare_match_value,
                                  timer_compare_match_t const match_channel);
fsp_err_t R_TIM_W_SequentialCapturesGet(timer_ctrl_t * const p_ctrl, uint32_t * const p_captures);

fsp_err_t R_TIM_W_PeriodSet_light(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);

/*******************************************************************************************************************//**
 * @} (end defgroup TIM_W)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
