/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_tim_w.h"
#include "r_tim_w_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "TIMW" in ASCII, used to determine if channel is open. */
#define TIM_W_OPEN                        (0x54494D57ULL)
#define TIM_W_PRV_ONESHOT_WAIT            (0x0)
#define TIM_W_PRV_GPIO_TRIGGER_OFFSET     (0x1U)
#define TIM_W_PRV_DELAY_CYCLES            (0x3U)

#if TIMER_TIMER_SETTINGS_REG_TIM_RELOAD2_Msk
 #define TIM_W_THRESHOLD_REG              TIMER_SETTINGS_REG
 #define TIM_W_PULSE_CNT_GPIO_REG         TIMER_PULSE_GPIO_SEL_REG
 #define TIM_W_PULSE_CNT_THRESHOLD_REG    TIMER_PULSE_CNT_CTRL_REG
 #define TIM_W_PRESCALER                  TIMER_PRE_SETTINGS_REG
#else
 #define TIM_W_THRESHOLD_REG              TIMER_THRESHOLD_REG
 #define TIM_W_PULSE_CNT_GPIO_REG         TIMER_PULSE_CNT_CTRL_REG
 #define TIM_W_PULSE_CNT_THRESHOLD_REG    TIMER_PULSE_CNT_THRESHOLD_REG
 #define TIM_W_PRESCALER                  TIMER_SETTINGS_REG
#endif

#if BSP_FEATURE_CGC_HAS_LP_CLOCK                  //! TIN_TODO: Remove when TIN lp clocks are added
 #define TIM_W_PRV_SYNC_DELAY_US(clk_cycles)    (((clk_cycles) * (1000000)) / (g_bsp_lp_clock) + 1)
#else
 #define TIM_W_PRV_LP_CLK_HZ             (32768U) //! TIN_TODO: Remove when TIN lp clocks are added
 #define TIM_W_PRV_SYNC_DELAY_US(clk_cycles)    (((clk_cycles) * (1000000)) / (TIM_W_PRV_LP_CLK_HZ) +1)
#endif
#if BSP_MCU_GROUP_RA6W1
 #define TIM_W_PWM_SYNC_TIMER_ALL        (0b00111)
 #define TIM_W_ONESHOT_TRIGGER_ALL       (0x2U)
 #define TIM_W_SLAVE_CCM_CHANNEL_SIZE    (0x2U)

 #define TIM_W_EVENT_GPIO1               (0x0U)
 #define TIM_W_EVENT_GPIO2               (0x1U)
 #define TIM_W_EVENT_GPIO3               (0x2U)
 #define TIM_W_EVENT_GPIO4               (0x3U)

#else
 #define TIM_W_ONESHOT_TRIGGER_ALL       (0x4U)
#endif

#define TIM_W_TIMEOUT                    (UINT16_MAX)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * tim_w_prv_ns_callback)(timer_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile tim_w_prv_ns_callback)(timer_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_tim_w_hardware_initialize(tim_w_instance_ctrl_t * const p_instance_ctrl,
                                        timer_cfg_t const * const     p_cfg);
static void     r_tim_w_common_open(tim_w_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);
static uint32_t r_tim_w_clock_frequency_get(tim_w_instance_ctrl_t * const p_instance_ctrl);
static void     r_tim_w_hardware_events_disable(tim_w_instance_ctrl_t * p_instance_ctrl);
static void     r_tim_w_disable_irq(IRQn_Type irq);
static void     r_tim_w_call_callback(tim_w_instance_ctrl_t * p_ctrl, uint8_t event, uint32_t capture);
static void     r_tim_w_freeze(tim_w_instance_ctrl_t * const p_instance_ctrl);
static void     r_tim_w_unfreeze(tim_w_instance_ctrl_t * const p_instance_ctrl);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void r_tim_w_generic_isr(void);

#if BSP_FEATURE_TIM_W_SUPPORTS_OVERFLOW_UNDERFLOW
void r_tim_w_counter_overflow_isr(void);
void r_tim_w_counter_underflow_isr(void);

#endif
void r_tim_w_ccm_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* TIM_W implementation of timer interface  */
const timer_api_t g_timer_on_tim_w =
{
    .open            = R_TIM_W_Open,
    .stop            = R_TIM_W_Stop,
    .start           = R_TIM_W_Start,
    .reset           = R_TIM_W_Reset,
    .enable          = R_TIM_W_Enable,
    .disable         = R_TIM_W_Disable,
    .periodSet       = R_TIM_W_PeriodSet,
    .dutyCycleSet    = R_TIM_W_DutyCycleSet,
    .compareMatchSet = R_TIM_W_CompareMatchSet,
    .infoGet         = R_TIM_W_InfoGet,
    .statusGet       = R_TIM_W_StatusGet,
    .callbackSet     = R_TIM_W_CallbackSet,
    .close           = R_TIM_W_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup TIM_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the timer module and applies configurations. Implements @ref timer_api_t::open.
 *
 * @note TIM_W hardware does not support one-shot interrupt on cycle_end. When using one-shot mode, the timer will be switched
 * to periodic in order to generate the cycle_end irq, then switch back to one-shot inside the ISR.
 *
 * The TIM_W implementation of the general timer can accept a tim_w_extended_cfg_t extension parameter.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL or the source divider is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       timer_cfg_t::p_callback is not NULL, but ISR is not enabled.
 * @retval FSP_ERR_INVALID_MODE           PWM mode cant be accessed without TIM_W_CFG_OUTPUT_SUPPORT_ENABLE == 1
 * @retval FSP_ERR_INVALID_CHANNEL        PWM sync supports only TIM as master.
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid argument passed for one-shot mode, capture/compare as well as count down
 *                                        are not supported.
 *                                        Capture/compare channel size is out of limit.
 *                                        PWM period or duty cycle values are not within valid limits.
 *                                        PWM sync can not be set without the PWM mode active.
 *                                        CCM Channel configuration is empty while channel size is not zero.
 *                                        Elc_channel exceeds the CCM channel size.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg) // NOLINT(readability-function-cognitive-complexity)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_instance_ctrl);

    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_cfg->p_extend;

    /* Check power domains before setting any hardware registers */
 #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
    if (TIM_W_TIM8 == p_cfg->channel)
    {
        FSP_ASSERT(bsp_pd_is_up_check(BSP_PD_COM));
    }
    else
    {
        FSP_ASSERT(bsp_pd_is_up_check(BSP_PD_TMR));
    }
 #endif

    /* Check the source divider is within valid range */
    FSP_ASSERT(p_cfg->source_div <= TIM_W_SOURCE_DIV_MAX);
    FSP_ERROR_RETURN(TIM_W_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    uint32_t channel_mask = 1U << (p_cfg->channel + TIM_W_CHANNEL_OFFSET); // Channel bitmask

    /* Ensure channel selected is valid/Available */
    FSP_ERROR_RETURN(0 != (channel_mask & BSP_FEATURE_TIM_W_VALID_CHANNEL_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* If callback is not null make sure the general IRQ is enabled. */
    if (p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    if (TIMER_MODE_ONE_SHOT == p_cfg->mode)
    {
        /* One-shot does not support count down */
        FSP_ERROR_RETURN(p_extend->direction == TIMER_DIRECTION_UP, FSP_ERR_INVALID_ARGUMENT);
    }

 #if BSP_MCU_GROUP_RA6W1               //! Add PC test
    if (p_extend->oneshot_switch_to_periodic)
    {
        /* Oneshot_switch_to_periodic is supported only by channels TIM_W_TIM1 and TIM_W_TIM5 */
        FSP_ERROR_RETURN((TIM_W_TIM1 == p_cfg->channel) || (TIM_W_TIM5 == p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
    }
 #endif

    if (NULL != p_extend->p_ccm_cfg)
    {
 #if BSP_MCU_GROUP_RA6W1               //! Add PC test
        if (p_extend->p_ccm_cfg->single_capture_mode)
        {
            /* Feature supported only by channels TIM_W_TIM1 and TIM_W_TIM5 */
            FSP_ERROR_RETURN((TIM_W_TIM1 == p_cfg->channel) || (TIM_W_TIM5 == p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
        }
 #endif

        /* One-shot mode does not support any capture/compare operations. */
        FSP_ERROR_RETURN(TIMER_MODE_ONE_SHOT != p_cfg->mode, FSP_ERR_INVALID_ARGUMENT);

 #if BSP_MCU_GROUP_RA6W1               //! Add PC test
        if ((TIM_W_TIM1 == p_cfg->channel) || (TIM_W_TIM5 == p_cfg->channel))
        {
            FSP_ERROR_RETURN(BSP_FEATURE_TIM_W_NUM_OF_CCM_CHANNELS >=
                             p_extend->p_ccm_cfg->ccm_channel_size,
                             FSP_ERR_INVALID_ARGUMENT);
        }
        else
        {
            FSP_ERROR_RETURN(TIM_W_SLAVE_CCM_CHANNEL_SIZE >= //! Modify for RA6W1
                             p_extend->p_ccm_cfg->ccm_channel_size,
                             FSP_ERR_INVALID_ARGUMENT);
        }

 #else
        FSP_ERROR_RETURN(BSP_FEATURE_TIM_W_NUM_OF_CCM_CHANNELS >= //! Modify for RA6W1
                         p_extend->p_ccm_cfg->ccm_channel_size,
                         FSP_ERR_INVALID_ARGUMENT);
 #endif

 #if !BSP_FEATURE_ELC_MISSING
        if (TIM_W_ELC_CAPTURE == p_extend->elc_task)
        {
            FSP_ERROR_RETURN(p_extend->p_ccm_cfg->elc_channel <=
                             p_extend->p_ccm_cfg->ccm_channel_size,
                             FSP_ERR_INVALID_ARGUMENT);
        }
 #endif
        if (0U < p_extend->p_ccm_cfg->ccm_channel_size)
        {
            FSP_ERROR_RETURN(NULL != p_extend->p_ccm_cfg->p_ccm_channel_cfg, FSP_ERR_INVALID_ARGUMENT);
        }
    }

 #if TIM_W_CFG_OUTPUT_SUPPORT_ENABLE
    if (TIMER_MODE_PWM == p_cfg->mode)
    {
        /* Ensure PWM period does not exceed max value */
        FSP_ERROR_RETURN(p_cfg->period_counts <= TIM_W_PWM_MAX, FSP_ERR_INVALID_ARGUMENT);

        /* Ensure Duty Cycle does not exceed Period value */
        FSP_ERROR_RETURN(p_cfg->duty_cycle_counts <= p_cfg->period_counts, FSP_ERR_INVALID_ARGUMENT);
    }

    if (0U != p_extend->pwm_sync_map)
    {
        /* Ensure PWM sync is not activated without pwm mode */
        FSP_ERROR_RETURN(TIMER_MODE_PWM == p_cfg->mode, FSP_ERR_INVALID_ARGUMENT);

  #if BSP_MCU_GROUP_RA6W3

        /* Ensure the master channel on pwm sync is TIM_W_TIM1 or TIM_W_TIM8 */
        FSP_ERROR_RETURN((TIM_W_TIM1 == p_cfg->channel) || (TIM_W_TIM8 == p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
  #elif BSP_MCU_GROUP_RA6W1

        /* Ensure the master channel on pwm sync is TIM_W_TIM1 or TIM_W_TIM5 */
        FSP_ERROR_RETURN((TIM_W_TIM1 == p_cfg->channel) || (TIM_W_TIM5 == p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
  #else

        /* Ensure the master channel on pwm sync is TIM */
        FSP_ERROR_RETURN(TIM_W_TIM1 == p_cfg->channel, FSP_ERR_INVALID_CHANNEL);
  #endif
    }

 #else
    FSP_ERROR_RETURN(TIMER_MODE_PWM != p_cfg->mode, FSP_ERR_INVALID_MODE);
 #endif
#endif

    /* Initialize control structure based on configurations. */
    r_tim_w_common_open(p_instance_ctrl, p_cfg);
    r_tim_w_hardware_initialize(p_instance_ctrl, p_cfg);

    p_instance_ctrl->open = TIM_W_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops timer. Implements @ref timer_api_t::stop.
 *
 * @note In case the timer runs on low power clock, a max of 2 lp_clk sync cycles are required for the TIM_PAUSE bit
 * to be effective.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_Stop
 *
 * @retval FSP_SUCCESS                 Timer successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Stop (timer_ctrl_t * const p_ctrl)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if TIM_W_CFG_OUTPUT_SUPPORT_ENABLE

    /* Pause does not affect the timer's behaviour for synced channels when on PWM mode. */
    if (0U != p_extend->pwm_sync_map)
    {
        /* Stop pwm on synced channels */
        p_instance_ctrl->p_reg->TIMER_PWM_SYNC_REG_b.PWM_START = 0U;
        if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
        {
            R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
        }
    }
#endif

    /* Edge detect needs to be disabled to stop counting edges for edge detect mode. */
    if (TIMER_MODE_EDGE_DETECT == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EDGE_DET_CNT_EN = 0U;
    }

    /* Pause timer */
    r_tim_w_freeze(p_instance_ctrl);

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer. Implements @ref timer_api_t::start.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_Start
 *
 * @retval FSP_SUCCESS                 Timer successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Start (timer_ctrl_t * const p_ctrl)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if TIM_W_CFG_OUTPUT_SUPPORT_ENABLE
    if (0U != p_extend->pwm_sync_map)
    {
        /* Start pwm_sync */
        p_instance_ctrl->p_reg->TIMER_PWM_SYNC_REG_b.PWM_START = 1U;
    }
#endif

    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN = 1U;
        FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY, 0U);
        p_instance_ctrl->p_reg->TIMER_ONESHOT_TRIGGER_REG = 1U;
    }
    else if (TIMER_MODE_EDGE_DETECT == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EDGE_DET_CNT_EN = 1U;
    }
    else
    {
        p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN = 1U;
    }

    /* Resume Counter */
    r_tim_w_unfreeze(p_instance_ctrl);

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter to the initial value. Implements @ref timer_api_t::reset.
 *
 * @retval FSP_SUCCESS                 Counter value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Reset (timer_ctrl_t * const p_ctrl)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Keep track of the timer state */
    timer_state_t timer_pause_state = TIMER_STATE_COUNTING;
    timer_state_t timer_en_state    = TIMER_STATE_COUNTING;

#if !BSP_FEATURE_TIM_W_SUPPORTS_PAUSE_NATIVELY

    /* Calculate the freeze bit corresponding to the channel.
     * The range of SET_FREEZE_REG_b.FRZ_SWTIM..FRZ_SWTIM8 is [1..8]. The channel range is [0..7]. */
    uint8_t freeze_bit = p_instance_ctrl->p_cfg->channel + 1;

    /* Check if the timer is frozen */
    timer_pause_state = CRG_TOP->SET_FREEZE_REG & (1 << (freeze_bit)) ? TIMER_STATE_STOPPED : TIMER_STATE_COUNTING;
#else
    timer_pause_state =
        p_instance_ctrl->p_reg->TIMER_PAUSE_REG_b.TIM_PAUSE ? TIMER_STATE_STOPPED : TIMER_STATE_COUNTING;
#endif

    if (TIMER_STATE_STOPPED == timer_pause_state)
    {
        r_tim_w_unfreeze(p_instance_ctrl);

        if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
        {
            R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
        }
    }

    if (0U == p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN)
    {
        timer_en_state = TIMER_STATE_STOPPED;
    }
    else
    {
        /* Clear timer counter. */
        p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN = 0U;
        FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY, 0U);
    }

    if (TIMER_STATE_STOPPED == timer_pause_state)
    {
        r_tim_w_freeze(p_instance_ctrl);
    }

    if (TIMER_STATE_COUNTING == timer_en_state)
    {
        p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN = 1U;
    }

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables external event triggers that capture the counter and sets the elc task. Implements @ref timer_api_t::enable.
 *
 * @note The timer could be running before R_TIM_W_Enable(). To ensure it is stopped, call R_TIM_W_Stop().
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_Enable
 *
 * @retval FSP_SUCCESS                  External events successfully enabled.
 * @retval FSP_ERR_ASSERTION            p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN             The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Enable (timer_ctrl_t * const p_ctrl) // NOLINT(readability-function-cognitive-complexity)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
    tim_w_extended_cfg_t  * p_extend;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint32_t tim_w_input_event_fall_en_lut[BSP_FEATURE_TIM_W_NUM_OF_CCM_CHANNELS] =
    {
        TIMER_TIMER_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_IN3_EVENT_FALL_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_IN4_EVENT_FALL_EN_Pos,
#if !BSP_MCU_GROUP_RA6W1
        TIMER_TIMER_CTRL_REG_TIM_IN5_EVENT_FALL_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_IN6_EVENT_FALL_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_IN7_EVENT_FALL_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_IN8_EVENT_FALL_EN_Pos,
#endif
    };

    uint32_t tim_w_cap_event_irq_en_lut[BSP_FEATURE_TIM_W_NUM_OF_CCM_CHANNELS] =
    {
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Pos,
#if !BSP_MCU_GROUP_RA6W1
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO5_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO6_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO7_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO8_IRQ_EN_Pos,
#endif
    };

    uint32_t          actual_pin;
    bsp_io_port_pin_t pin_id;
    bsp_io_port_t     port_id;

    uint32_t ctrl_reg = p_instance_ctrl->p_reg->TIMER_CTRL_REG;

    switch (p_instance_ctrl->p_cfg->mode)
    {
        case TIMER_MODE_PERIODIC:
        {
            if ((NULL == p_extend->p_ccm_cfg) || (NULL == p_extend->p_ccm_cfg->p_ccm_channel_cfg))
            {
                break;
            }

#if BSP_MCU_GROUP_RA6W1
            ctrl_reg &=
                ~((TIMER_TIMER_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN3_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN4_EVENT_FALL_EN_Msk)
                  );

            ctrl_reg &=
                ~((TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Msk)
                  );
#else
            ctrl_reg &=
                ~((TIMER_TIMER_CTRL_REG_TIM_IN1_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN2_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN3_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN4_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN5_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN6_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN7_EVENT_FALL_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_IN8_EVENT_FALL_EN_Msk)
                  );

            ctrl_reg &=
                ~((TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO5_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO6_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO7_IRQ_EN_Msk) |
                  (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO8_IRQ_EN_Msk)
                  );
#endif

            for (uint8_t index = 0; index < p_extend->p_ccm_cfg->ccm_channel_size; index++)
            {
#if BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH
                if ((TIM_W_CCM_OPERATION_CAPTURE != p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].operation) ||
                    (TIM_W_GPIO_TRIGGER_DISABLED == p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].capture_trigger))
#else
                if (TIM_W_GPIO_TRIGGER_DISABLED == p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].capture_trigger)
#endif
                {
                    continue;
                }

                pin_id =
                    (bsp_io_port_pin_t) (BSP_IO_PIN_BITS &
                                         (uint16_t) p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].capture_source);
                port_id =
                    (bsp_io_port_t) ((BSP_IO_PORT_BITS &
                                      (uint16_t) p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].capture_source) >>
                                     BSP_IO_PORT_OFFSET);

                actual_pin = (port_id == 0U) ? pin_id + 1U :
                             (port_id == 1U) ? pin_id + 1U + BSP_FEATURE_IO_PORT0_GPIO_COUNT :
                             pin_id + 1U + BSP_FEATURE_IO_PORT1_GPIO_COUNT + BSP_FEATURE_IO_PORT0_GPIO_COUNT;

                ctrl_reg |=
                    (p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].capture_trigger - TIM_W_PRV_GPIO_TRIGGER_OFFSET) <<
                        tim_w_input_event_fall_en_lut[index];
                ctrl_reg |= 1U << tim_w_cap_event_irq_en_lut[index];

#if BSP_MCU_GROUP_RA6W1
                if (TIM_W_EVENT_GPIO1 == index)
                {
                    p_instance_ctrl->p_reg->TIMER_GPIO1_CONF_REG = actual_pin;
                }
                else if (TIM_W_EVENT_GPIO2 == index)
                {
                    p_instance_ctrl->p_reg->TIMER_GPIO2_CONF_REG = actual_pin;
                }
                else if (TIM_W_EVENT_GPIO3 == index)
                {
                    p_instance_ctrl->p_reg->TIMER_GPIO3_CONF_REG = actual_pin;
                }
                else if (TIM_W_EVENT_GPIO4 == index)
                {
                    p_instance_ctrl->p_reg->TIMER_GPIO4_CONF_REG = actual_pin;
                }

#else
                p_instance_ctrl->p_reg->TIMER_GPIO_CONF_REG[index] = actual_pin;
#endif
            }

            break;
        }

        case TIMER_MODE_EDGE_DETECT:
        {
            FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_EDGE_DET_CNT_EN, ctrl_reg, 1U);

            if (TIM_W_GPIO_TRIGGER_DISABLED == p_extend->gpio_trigger)
            {
                break;
            }

            /* Calculate the actual tim_w gpio configure register value */
            pin_id  = (bsp_io_port_pin_t) (BSP_IO_PIN_BITS & (uint16_t) p_extend->gpio_source);
            port_id = (bsp_io_port_t) ((BSP_IO_PORT_BITS & (uint16_t) p_extend->gpio_source) >> BSP_IO_PORT_OFFSET);

            actual_pin = (port_id == 0U) ? pin_id + 1U :
                         (port_id == 1U) ? pin_id + 1U + BSP_FEATURE_IO_PORT0_GPIO_COUNT :
                         pin_id + 1U + BSP_FEATURE_IO_PORT1_GPIO_COUNT + BSP_FEATURE_IO_PORT0_GPIO_COUNT;

            p_instance_ctrl->p_reg->TIM_W_PULSE_CNT_GPIO_REG = actual_pin;

            FSP_REG_VAR_FIELD_SET(TIMER,
                                  TIMER_CTRL_REG,
                                  TIM_EDGE_DET_CNT_FALL_EN,
                                  ctrl_reg,
                                  p_extend->gpio_trigger - TIM_W_PRV_GPIO_TRIGGER_OFFSET);

            break;
        }

        case TIMER_MODE_ONE_SHOT:
        {
            /* TIM_EN bit does not trigger the one-shot pulse operation in one-shot mode,
             * but we need to set it before the trigger takes place
             */
            FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_EN, ctrl_reg, 1U);

            if (TIM_W_GPIO_TRIGGER_DISABLED == p_extend->gpio_trigger)
            {
                break;
            }

            /* Calculate the actual tim_w gpio configure register value */
            pin_id  = (bsp_io_port_pin_t) (BSP_IO_PIN_BITS & (uint16_t) p_extend->gpio_source);
            port_id = (bsp_io_port_t) ((BSP_IO_PORT_BITS & (uint16_t) p_extend->gpio_source) >> BSP_IO_PORT_OFFSET);

            actual_pin = (port_id == 0U) ? pin_id + 1U :
                         (port_id == 1U) ? pin_id + 1U + BSP_FEATURE_IO_PORT0_GPIO_COUNT :
                         pin_id + 1U + BSP_FEATURE_IO_PORT1_GPIO_COUNT + BSP_FEATURE_IO_PORT0_GPIO_COUNT;

#if BSP_MCU_GROUP_RA6W1
            p_instance_ctrl->p_reg->TIMER_GPIO1_CONF_REG = actual_pin;
#else
            p_instance_ctrl->p_reg->TIMER_GPIO_CONF_REG[0U] = actual_pin;
#endif
            FSP_REG_VAR_FIELD_SET(TIMER,
                                  TIMER_CTRL_REG,
                                  TIM_IN1_EVENT_FALL_EN,
                                  ctrl_reg,
                                  p_extend->gpio_trigger - TIM_W_PRV_GPIO_TRIGGER_OFFSET);

            break;
        }

        case TIMER_MODE_PWM:
        {
            /* global SYNC_ENABLE signal is set here for TIMER_MODE_PWM mode */
            if (p_extend->pwm_sync_map != 0U)
            {
                p_instance_ctrl->p_reg->TIMER_PWM_SYNC_REG_b.SYNC_ENABLE = 1U;
            }
        }

        default:
        {
            break;
        }
    }

#if !BSP_FEATURE_ELC_MISSING
    if ((TIM_W_ELC_CAPTURE == p_extend->elc_task) &&
        (p_extend->p_ccm_cfg->p_ccm_channel_cfg[p_extend->p_ccm_cfg->elc_channel].ccm_operation_irq >=
         (IRQn_Type) 0U))
    {
        ctrl_reg |= 1U << tim_w_cap_event_irq_en_lut[p_extend->p_ccm_cfg->elc_channel];
    }

    /* Set timer elc task */
    p_instance_ctrl->p_reg->TIMER_ELC_TASK_REG =
        ((p_extend->elc_task << TIMER_TIMER_ELC_TASK_REG_TIM_ELC_TASK_Pos) &
         TIMER_TIMER_ELC_TASK_REG_TIM_ELC_TASK_Msk) |
        ((p_extend->p_ccm_cfg->elc_channel <<
            TIMER_TIMER_ELC_TASK_REG_TIM_ELC_TASK_CAPTURE_Pos) &
         TIMER_TIMER_ELC_TASK_REG_TIM_ELC_TASK_CAPTURE_Msk);
#endif

    p_instance_ctrl->p_reg->TIMER_CTRL_REG = ctrl_reg;

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables external event triggers that start, stop, capture or compare.
 * Implements @ref timer_api_t::disable.
 *
 * @note The timer could be running after R_TIM_W_Disable(). To ensure it is stopped, call R_TIM_W_Stop().
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_Disable
 *
 * @retval FSP_SUCCESS                 External events successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Disable (timer_ctrl_t * const p_ctrl)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    r_tim_w_hardware_events_disable(p_instance_ctrl);

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets period value provided.
 *
 * Implements @ref timer_api_t::periodSet.
 *
 * @warning Period will be updated immediately regardless of the timer's state.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL, or selected value exceeds HW specifications.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    Selected value exceeds the maximum register value.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    timer_cfg_t * p_cfg = (timer_cfg_t *) p_instance_ctrl->p_cfg;
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    if (TIMER_MODE_PWM == p_cfg->mode)
    {
        /* in TIMER_MODE_PWM, period_counts value does not exceed max pwm_freq register value */
        FSP_ERROR_RETURN(period_counts <= TIM_W_PWM_MAX, FSP_ERR_INVALID_ARGUMENT);
    }
#endif

    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->TIM_W_THRESHOLD_REG = period_counts;
    }
    else if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        if (p_extend->oneshot_switch_to_periodic)
        {
            p_instance_ctrl->p_reg->TIM_W_THRESHOLD_REG = period_counts;
        }
        else
        {
            p_instance_ctrl->p_reg->TIMER_SHOTWIDTH_REG = period_counts;
        }
    }
    else if (TIMER_MODE_EDGE_DETECT == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->TIM_W_PULSE_CNT_THRESHOLD_REG = period_counts;
    }

#if TIM_W_CFG_OUTPUT_SUPPORT_ENABLE
    if (TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode)
    {
        FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_PWM_BUSY, 0U);
        p_instance_ctrl->p_reg->TIMER_PWM_CTRL_REG =
            ((period_counts << TIMER_TIMER_PWM_CTRL_REG_TIM_PWM_FREQ_Pos) &
             TIMER_TIMER_PWM_CTRL_REG_TIM_PWM_FREQ_Msk) |
            (((period_counts >> 1) << TIMER_TIMER_PWM_CTRL_REG_TIM_PWM_DC_Pos) &
             TIMER_TIMER_PWM_CTRL_REG_TIM_PWM_DC_Msk);
    }
    else if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_PWM_BUSY, 0U);
        p_instance_ctrl->p_reg->TIMER_PWM_CTRL_REG_b.TIM_PWM_FREQ = (uint16_t) period_counts;
    }
#endif

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets period value provided.
 *
 * Implements @ref timer_api_t::periodSet.
 *
 * @warning Light version of periodSet, the new period will be applied without any checks.
 *
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_PeriodSet_light (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;

#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->p_reg->TIM_W_THRESHOLD_REG = period_counts;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets duty cycle. Implements @ref timer_api_t::dutyCycleSet.
 *
 * @warning Duty cycle will be updated immediately regardless of the timer's state.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_DutyCycleSet
 *
 * @param[in] p_ctrl                   Pointer to instance control block.
 * @param[in] duty_cycle_counts        Duty cycle to set in counts.
 * @param[in] pin                      Use tim_w_io_pin_t to select TIM_W_IO_PIN_GTIOCA or TIM_W_IO_PIN_GTIOCB
 *
 * @retval FSP_SUCCESS                 Duty cycle updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL or the pin is not one of tim_w_io_pin_t
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    Duty cycle is larger than period.
 * @retval FSP_ERR_INVALID_MODE        Duty cycle can only be configured in PWM mode.
 * @retval FSP_ERR_UNSUPPORTED         TIM_W_CFG_OUTPUT_SUPPORT_ENABLE is 0.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
    FSP_PARAMETER_NOT_USED(pin);
#if TIM_W_CFG_OUTPUT_SUPPORT_ENABLE
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
 #if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    timer_cfg_t * p_cfg = (timer_cfg_t *) p_instance_ctrl->p_cfg;
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Duty Cycle can be configured only in TIMER_MODE_PWM mode. */
    FSP_ERROR_RETURN(TIMER_MODE_PWM == p_cfg->mode, FSP_ERR_INVALID_MODE);

    /* DC value can not exceed period value */
    FSP_ERROR_RETURN(duty_cycle_counts <= p_cfg->period_counts, FSP_ERR_INVALID_ARGUMENT);
 #endif

    p_instance_ctrl->p_reg->TIMER_PWM_CTRL_REG_b.TIM_PWM_DC = (uint16_t) duty_cycle_counts;

    /* Wait until the updated values are effective */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_PWM_BUSY, 0U);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(duty_cycle_counts);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif
}

/*******************************************************************************************************************//**
 * Set value for compare match feature. Implements @ref timer_api_t::compareMatchSet.
 *
 * @note This API should be used when timer has stop counting and shall not be used along with PWM operation.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_CompareMatchSet
 *
 * @retval FSP_SUCCESS              Set the compare match value successfully.
 * @retval FSP_ERR_ASSERTION        p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance is not opened.
 * @retval FSP_ERR_NOT_ENABLED      Requested compare channel is disabled.
 *                                  CCM channel configuration is NULL.
 * @retval FSP_ERR_INVALID_MODE     Compare match operation is only available on periodic mode.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_CompareMatchSet (timer_ctrl_t * const        p_ctrl,
                                   uint32_t const              compare_match_value,
                                   timer_compare_match_t const match_channel)
{
#if BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;

 #if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);

    /* Confirm that requested compare match channel is enabled */
    FSP_ERROR_RETURN((NULL != p_extend->p_ccm_cfg) && (NULL != p_extend->p_ccm_cfg->p_ccm_channel_cfg),
                     FSP_ERR_NOT_ENABLED);
    FSP_ERROR_RETURN(
        TIM_W_CCM_OPERATION_COMPARE_MATCH == p_extend->p_ccm_cfg->p_ccm_channel_cfg[match_channel].operation,
        FSP_ERR_NOT_ENABLED);
 #else
    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
 #endif

    /* Set compare match value. */
    p_instance_ctrl->p_reg->TIMER_COMPARE_MATCH_REG[match_channel] = compare_match_value;

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(TIM_W_PRV_DELAY_CYCLES), BSP_DELAY_UNITS_MICROSECONDS);
    }

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(compare_match_value);
    FSP_PARAMETER_NOT_USED(match_channel);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif
}

/*******************************************************************************************************************//**
 * Get captured values for all configured capturing channels when sequential capturing is enabled.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_SequentialCapturesGet
 *
 * @param[in] p_ctrl                   Pointer to instance control block.
 * @param[in] p_captures               Pointer to the captured snapshot values.
 *
 * @note    p_captures length must be greater or equal than the number of sequential captures.
 *
 * @retval FSP_SUCCESS              Captured values stored successfully.
 * @retval FSP_ERR_ASSERTION        p_ctrl or p_captures was NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance is not opened.
 * @retval FSP_ERR_INVALID_MODE     Capture operation is only available on periodic mode.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_SequentialCapturesGet (timer_ctrl_t * const p_ctrl, uint32_t * const p_captures)
{
#if BSP_FEATURE_TIM_W_SUPPORTS_SEQ_CAPTURES
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;

 #if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_captures);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
 #endif
    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (NULL != p_extend->p_ccm_cfg)
    {
        for (uint8_t index = 0; index < p_extend->p_ccm_cfg->seq_captures; index++)
        {
            *(p_captures + index) = p_instance_ctrl->p_reg->TIMER_CAPTURE_GPIO_REG[index];
        }
    }

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_captures);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif
}

/*******************************************************************************************************************//**
 * Get timer information and store it in provided pointer p_info. Implements @ref timer_api_t::infoGet.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, frequency, and ELC event written to caller's
 *                                     structure successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_info was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;
#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    if (TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode)
    {
        p_info->period_counts = p_instance_ctrl->p_reg->TIM_W_THRESHOLD_REG;
    }
    else if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        p_info->period_counts = p_instance_ctrl->p_reg->TIMER_SHOTWIDTH_REG;
    }
    else if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        p_info->period_counts = p_instance_ctrl->p_reg->TIMER_PWM_CTRL_REG_b.TIM_PWM_FREQ;
    }

    /* Get and store clock frequency after prescaler */
    p_info->clock_frequency = r_tim_w_clock_frequency_get(p_instance_ctrl);

    /* Get and store clock counting direction. Read count direction setting */
    p_info->count_direction = (timer_direction_t) !(p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_COUNT_DOWN_EN);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current timer status and store it in provided pointer p_status. Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_tim_w_example.c R_TIM_W_StatusGet
 *
 * @retval FSP_SUCCESS                 Current timer state and counter value set successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;

#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if !BSP_FEATURE_TIM_W_SUPPORTS_PAUSE_NATIVELY

    /* Read the refreeze register */
    uint32_t freeze_reg = CRG_TOP->RESET_FREEZE_REG;

    /* Calculate the freeze bit corresponding to the channel.
     * The range of RESET_FREEZE_REG_b.FRZ_SWTIM..FRZ_SWTIM8 is [1..8]. The channel range is [0..7]. */
    uint32_t freeze_bit = p_instance_ctrl->p_cfg->channel + 1;
#endif

    /* Get counter value */
    if (TIMER_MODE_EDGE_DETECT == p_instance_ctrl->p_cfg->mode)
    {
        p_status->counter = 0U;
    }
    else
    {
        p_status->counter = p_instance_ctrl->p_reg->TIMER_TIMER_VAL_REG_b.TIM_TIMER_VALUE;
    }

    p_status->state = TIMER_STATE_COUNTING;

    /* Get counter state */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        /* The TIM_W state can not be determined with certainty in case ONESHOT_SWITCH is set. */
        if (1U == p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_ONESHOT_SWITCH)
        {
            p_status->state = TIMER_STATE_UNKNOWN;
        }
        else if (TIM_W_PRV_ONESHOT_WAIT == p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_ONESHOT_PHASE)
        {
            p_status->state = TIMER_STATE_STOPPED;
        }
    }

#if !BSP_FEATURE_TIM_W_SUPPORTS_PAUSE_NATIVELY
    if (freeze_reg & (1 << freeze_bit) || (0U == p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN))
#else
    if ((1U == p_instance_ctrl->p_reg->TIMER_PAUSE_REG) || (0U == p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN))
#endif
    {
        p_status->state = TIMER_STATE_STOPPED;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref timer_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_CallbackSet (timer_ctrl_t * const          p_api_ctrl,
                               void (                      * p_callback)(timer_callback_args_t *),
                               void * const                  p_context,
                               timer_callback_args_t * const p_callback_memory)
{
    tim_w_instance_ctrl_t * p_ctrl = (tim_w_instance_ctrl_t *) p_api_ctrl;

#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->p_callback        = p_callback;
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops counter, disables output pins, and clears internal driver data. Implements @ref timer_api_t::close.
 *
 * @note In case the timer runs on low power clock, a max of 2 lp_clk sync cycles are required for the TIM_EN bit
 * to be effective.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TIM_W_Close (timer_ctrl_t * const p_ctrl)
{
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) p_ctrl;

#if TIM_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIM_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Disables external events */
    r_tim_w_hardware_events_disable(p_instance_ctrl);

    r_tim_w_unfreeze(p_instance_ctrl);

#if BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH

    /* Set capture_compare mode to reset value (capture) and clear compare match irq reg */
    p_instance_ctrl->p_reg->TIMER_COMPARE_MATCH_ENABLE_REG = 0U;
    p_instance_ctrl->p_reg->TIMER_COMPARE_MATCH_IRQ_REG    = 0U;
#endif
    p_instance_ctrl->p_reg->TIMER_PWM_SYNC_REG = 0U;

    /* Disable interrupts. */
    r_tim_w_disable_irq(p_instance_ctrl->p_cfg->cycle_end_irq);

    if ((NULL != p_extend->p_ccm_cfg) && (NULL != p_extend->p_ccm_cfg->p_ccm_channel_cfg))
    {
        for (uint8_t index = 0; index < p_extend->p_ccm_cfg->ccm_channel_size; index++)
        {
            if (p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].ccm_operation_irq >= 0)
            {
                r_tim_w_disable_irq(p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].ccm_operation_irq);
            }
        }
    }

    /*
     * Reset the TIM_EN bit field before resetting the ctrl register.
     * This way we ensure that the TIM_W resets properly before closing.
     */
    p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_EN = 0U;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY, 0U);

    /* Stop timer clock. */
    p_instance_ctrl->p_reg->TIMER_CTRL_REG = 0U;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY, 0U);

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

#if BSP_MCU_GROUP_RA6W3
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
    if (TIM_W_TIM8 <= p_instance_ctrl->p_cfg->channel)
    {
        /* Disable the PD_SLP timer clock only if all TIM8–TIM10 are closed */
        if ((0 == TIMER8->TIMER8_CTRL_REG) &&
            (0 == TIMER9->TIMER9_CTRL_REG) &&
            (0 == TIMER10->TIMER10_CTRL_REG))
        {
            CRG_TOP->CLK_PD_SLP_REG_b.SLP_TIMER_ENABLE = 0;
        }
    }
    FSP_CRITICAL_SECTION_EXIT;
#endif

    return FSP_SUCCESS;
}

/** @} (end addtogroup TIM_W) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes control structure based on configuration.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 * @param[in]  p_cfg                   Pointer to timer configuration.
 **********************************************************************************************************************/
static void r_tim_w_common_open (tim_w_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Initialize control structure.  */
    p_instance_ctrl->p_cfg = p_cfg;

#if defined(TIMER9) && defined(TIMER10)

    /* Save register base address. */
 #if BSP_MCU_GROUP_RA6W3
    if (TIM_W_TIM8 > p_cfg->channel)
    {
        uint32_t base_address = (uint32_t) TIMER + (p_cfg->channel * ((uint32_t) TIMER2 - (uint32_t) TIMER));
        p_instance_ctrl->p_reg = (TIMER_Type *) base_address;
    }
    else
    {
        uint32_t base_address = (uint32_t) TIMER8 +
                                ((p_cfg->channel - TIM_W_TIM8) * ((uint32_t) TIMER9 - (uint32_t) TIMER8));
        p_instance_ctrl->p_reg = (TIMER_Type *) base_address;
    }
 #endif
#else
    if (TIM_W_TIM8 > p_cfg->channel)
    {
        uint32_t base_address = (uint32_t) TIMER + (p_cfg->channel * ((uint32_t) TIMER2 - (uint32_t) TIMER));
        p_instance_ctrl->p_reg = (TIMER_Type *) base_address;
    }
    else
    {
        p_instance_ctrl->p_reg = (TIMER_Type *) TIMER8;
    }
#endif

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;
}

/*******************************************************************************************************************//**
 * Performs hardware initialization of the TIM_W.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void r_tim_w_hardware_initialize (tim_w_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg) // NOLINT(readability-function-cognitive-complexity)
{
    /* Save pointer to extended configuration structure. */
    tim_w_extended_cfg_t * p_extend = (tim_w_extended_cfg_t *) p_cfg->p_extend;

    uint32_t ctrl_reg      = 0U;
    uint32_t threshold_reg = 0U;

    uint32_t tim_w_cap_event_irq_en_lut[BSP_FEATURE_TIM_W_NUM_OF_CCM_CHANNELS] = //! Add bsp feature in TIN
    {
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Pos,
#if !BSP_MCU_GROUP_RA6W1
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO5_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO6_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO7_IRQ_EN_Pos,
        TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO8_IRQ_EN_Pos,
#endif
    };

#if BSP_MCU_GROUP_RA6W3
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if (TIM_W_TIM8 <= p_cfg->channel)
    {
        /* Enable the PD_SLP timer clock */
        CRG_TOP->CLK_PD_SLP_REG_b.SLP_TIMER_ENABLE = 1;
    }
#endif

    /* Check busy flag & set timer's clk prescaler ( 1/(2^N), N = 0 to 8 ). */
    uint32_t timeout = TIM_W_TIMEOUT;
    while ((1 == p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY) && --timeout)
    {
        ;
    }

    p_instance_ctrl->p_reg->TIM_W_PRESCALER = p_cfg->source_div;

    FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_SYS_CLK_EN, ctrl_reg, p_extend->count_source);
    FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_CLK_EN, ctrl_reg, 1U);
    FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_COUNT_DOWN_EN, ctrl_reg, !(p_extend->direction));
    FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_FREE_RUN_MODE_EN, ctrl_reg, p_extend->free_run);
    FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_IRQ_EN, ctrl_reg, 1U);

    if (TIMER_MODE_ONE_SHOT == p_cfg->mode)
    {
        /*
         * Set timer mode to one-shot
         * Configure one-shot trigger to access all sources available (GPIO, ELC, SW).
         */
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_ONESHOT_MODE_EN, ctrl_reg, 1U);
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_ONESHOT_TRIGGER, ctrl_reg, TIM_W_ONESHOT_TRIGGER_ALL);
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_ONESHOT_SWITCH, ctrl_reg,
                              p_extend->oneshot_switch_to_periodic);

        /*
         * When in one-shot mode, TIMER_THRESHOLD_REG value represents a delay
         * before the one-shot pulse.
         */
        threshold_reg = p_extend->oneshot_delay;

        /* Check busy flag & set shot fire duration. */
        timeout = TIM_W_TIMEOUT;
        while ((1 == p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY) && --timeout)
        {
            ;
        }

        p_instance_ctrl->p_reg->TIMER_SHOTWIDTH_REG = p_cfg->period_counts;
    }
    else if (TIMER_MODE_EDGE_DETECT == p_cfg->mode)
    {
        threshold_reg = UINT32_MAX;

        /* Set after how many pulses an interrupt is generated.
         * The first pulse shall be ignored by HW due to metastability issues.
         */
        p_instance_ctrl->p_reg->TIM_W_PULSE_CNT_THRESHOLD_REG = (p_cfg->period_counts) - 1U;
    }
    else if (TIMER_MODE_PERIODIC == p_cfg->mode)
    {
        threshold_reg = p_cfg->period_counts;

        if (NULL != p_extend->p_ccm_cfg)
        {
#if BSP_FEATURE_TIM_W_SUPPORTS_SEQ_CAPTURES
            if (p_extend->p_ccm_cfg->seq_captures > 0U)
            {
                /* Set sequential capturing to be triggered by both gpio and elc triggers */
                FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_SEQ_CAPTURING_MODE, ctrl_reg, 3U);

                /* Set the number of sequential captures needed for the capture IRQ to be triggered. */
                p_instance_ctrl->p_reg->TIMER_CONF_CAP_EVENTS_REG =
                    p_extend->p_ccm_cfg->seq_captures;
            }
#endif

            /* Configure CCM channels */
            if (NULL != p_extend->p_ccm_cfg->p_ccm_channel_cfg)
            {
                /*
                 * Fill the compare_match regs with desired value, enable compare mode
                 * and enable dedicated capture_compare irq lines
                 */
                for (uint8_t index = 0; index < p_extend->p_ccm_cfg->ccm_channel_size; index++)
                {
#if BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH
                    if (TIM_W_CCM_OPERATION_COMPARE_MATCH == p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].operation)
                    {
                        p_instance_ctrl->p_reg->TIMER_COMPARE_MATCH_REG[index] =
                            p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].compare_value;
                        p_instance_ctrl->p_reg->TIMER_COMPARE_MATCH_ENABLE_REG |= 1U << index;
                    }
#endif

                    if (p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].ccm_operation_irq >=
                        (IRQn_Type) 0U)
                    {
#if BSP_FEATURE_TIM_W_SUPPORTS_COMPARE_MATCH
                        if (TIM_W_CCM_OPERATION_COMPARE_MATCH ==
                            p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].operation)
                        {
                            p_instance_ctrl->p_reg->TIMER_COMPARE_MATCH_IRQ_REG |= 1U << index;
                        }
                        else
                        {
                            ctrl_reg |= 1U << tim_w_cap_event_irq_en_lut[index];
                        }

#else
                        ctrl_reg |= 1U << tim_w_cap_event_irq_en_lut[index];
#endif

                        //! Add PC test for timer5 only
#if BSP_FEATURE_TIM_W_HAS_IRQ_PER_CAPTURE_CHANNEL
                        R_BSP_IrqCfgEnable(p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].ccm_operation_irq,
                                           p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].ccm_operation_ipl,
                                           p_instance_ctrl);
#else
                        R_BSP_IrqCfgEnable(p_extend->p_ccm_cfg->p_ccm_channel_cfg[0].ccm_operation_irq,
                                           p_extend->p_ccm_cfg->p_ccm_channel_cfg[0].ccm_operation_ipl,
                                           p_instance_ctrl);
#endif
                    }
                }
            }
        }

        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CTRL_REG, TIM_SINGLE_EVENT_CAPTURE, ctrl_reg,
                              ((NULL != p_extend->p_ccm_cfg) ? p_extend->p_ccm_cfg->single_capture_mode : 0));
    }

    p_instance_ctrl->p_reg->TIMER_CTRL_REG = ctrl_reg;
#if BSP_MCU_GROUP_RA6W3
    FSP_CRITICAL_SECTION_EXIT;
#endif

#if TIM_W_CFG_OUTPUT_SUPPORT_ENABLE
    uint32_t pwm_reg = 0U;
    FSP_REG_VAR_FIELD_SET(TIMER, TIMER_PWM_CTRL_REG, TIM_PWM_FREQ, pwm_reg, p_cfg->period_counts);

    if (TIMER_MODE_PERIODIC == p_cfg->mode)
    {
        /* Periodic with output support generates a 50% duty cycle PWM along with timer functionality */
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_PWM_CTRL_REG, TIM_PWM_DC, pwm_reg, p_cfg->period_counts >> 1);
    }
    else if (TIMER_MODE_PWM == p_cfg->mode)
    {
        threshold_reg = UINT32_MAX;
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_PWM_CTRL_REG, TIM_PWM_DC, pwm_reg, p_cfg->duty_cycle_counts);

        if (p_extend->pwm_sync_map != 0U)
        {
            uint32_t pwm_sync_reg = 0;
 #if BSP_MCU_GROUP_RA6W1
            pwm_sync_reg = (p_extend->pwm_sync_map & TIM_W_PWM_SYNC_TIMER_ALL) <<
                           TIMER_TIMER_PWM_SYNC_REG_TIMER2_SYNC_Pos;
            FSP_REG_VAR_FIELD_SET(TIMER, TIMER_PWM_SYNC_REG, TIMER_SYNC, pwm_sync_reg, 1U);
 #else
            FSP_REG_VAR_FIELD_SET(TIMER, TIMER_PWM_SYNC_REG, TIMER_SLAVE_SYNC, pwm_sync_reg, p_extend->pwm_sync_map);
            FSP_REG_VAR_FIELD_SET(TIMER, TIMER_PWM_SYNC_REG, TIMER_MASTER_SYNC, pwm_sync_reg, 1U);
 #endif
            p_instance_ctrl->p_reg->TIMER_PWM_SYNC_REG = pwm_sync_reg;
        }
    }

    /* Check busy flag & set PWM register. */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_PWM_BUSY, 0U);
    p_instance_ctrl->p_reg->TIMER_PWM_CTRL_REG = pwm_reg;
#endif

    /* Check busy flag & set counter threshold. */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY, 0U);

    p_instance_ctrl->p_reg->TIM_W_THRESHOLD_REG = threshold_reg;

    /* Enable CPU interrupts if callback is not null.  Also enable interrupts for one shot mode.
     *  @note The TIM_W hardware does not support one-shot mode natively. To support one-shot mode, the timer will be
     *  stopped and cleared using software in the ISR.
     */
    if (p_cfg->cycle_end_irq >= (IRQn_Type) 0U)
    {
        R_BSP_IrqCfgEnable(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);
    }

#if BSP_FEATURE_TIM_W_SUPPORTS_OVERFLOW_UNDERFLOW
    if (p_extend->overflow_irq >= (IRQn_Type) 0U)
    {
        R_BSP_IrqCfgEnable(p_extend->overflow_irq, p_extend->overflow_ipl, p_instance_ctrl);
    }

    if (p_extend->underflow_irq >= (IRQn_Type) 0U)
    {
        R_BSP_IrqCfgEnable(p_extend->underflow_irq, p_extend->underflow_ipl, p_instance_ctrl);
    }
#endif

    /* Wait until the configuration values are effective */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_TIMER_BUSY, 0U);
#if TIM_W_CFG_OUTPUT_SUPPORT_ENABLE
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_PWM_BUSY, 0U);
#endif

    /* Wait 3 lp clock cycles for register changes to be effective */
    if (TIM_W_CLOCK_LP_CLK == p_extend->count_source)
    {
        R_BSP_SoftwareDelay(TIM_W_PRV_SYNC_DELAY_US(1), BSP_DELAY_UNITS_MICROSECONDS);
    }
}

/*******************************************************************************************************************//**
 * Disables hardware events that would cause the timer to start, stop, clear, or capture.
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static void r_tim_w_hardware_events_disable (tim_w_instance_ctrl_t * p_instance_ctrl)
{
#if BSP_MCU_GROUP_RA6W1
    p_instance_ctrl->p_reg->TIMER_GPIO1_CONF_REG = TIM_W_GPIO_TRIGGER_DISABLED;
    p_instance_ctrl->p_reg->TIMER_GPIO2_CONF_REG = TIM_W_GPIO_TRIGGER_DISABLED;
    if ((TIM_W_TIM1 == p_instance_ctrl->p_cfg->channel) ||
        (TIM_W_TIM5 == p_instance_ctrl->p_cfg->channel)) ///< ! only TIM_W_TIM1 and TIM_W_TIM5 supports 4 capture events
    {
        p_instance_ctrl->p_reg->TIMER_GPIO3_CONF_REG = TIM_W_GPIO_TRIGGER_DISABLED;
        p_instance_ctrl->p_reg->TIMER_GPIO4_CONF_REG = TIM_W_GPIO_TRIGGER_DISABLED;

        uint32_t tmp = p_instance_ctrl->p_reg->TIMER_CLEAR_GPIO_EVENT_REG;
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CLEAR_GPIO_EVENT_REG, TIM_CLEAR_GPIO1_EVENT, tmp, true);
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CLEAR_GPIO_EVENT_REG, TIM_CLEAR_GPIO2_EVENT, tmp, true);
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CLEAR_GPIO_EVENT_REG, TIM_CLEAR_GPIO3_EVENT, tmp, true);
        FSP_REG_VAR_FIELD_SET(TIMER, TIMER_CLEAR_GPIO_EVENT_REG, TIM_CLEAR_GPIO4_EVENT, tmp, true);
        p_instance_ctrl->p_reg->TIMER_CLEAR_GPIO_EVENT_REG = tmp;
    }

    p_instance_ctrl->p_reg->TIMER_CTRL_REG &=
        ~((TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Msk)
          );
#else
    p_instance_ctrl->p_reg->TIMER_CTRL_REG &=
        ~((TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO1_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO2_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO3_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO4_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO5_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO6_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO7_IRQ_EN_Msk) |
          (TIMER_TIMER_CTRL_REG_TIM_CAP_GPIO8_IRQ_EN_Msk)
          );

    for (uint8_t index = 0U; index < BSP_FEATURE_TIM_W_NUM_OF_CCM_CHANNELS; index++)
    {
        p_instance_ctrl->p_reg->TIMER_GPIO_CONF_REG[index] = TIM_W_GPIO_TRIGGER_DISABLED;
    }
#endif
    if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->TIMER_PWM_SYNC_REG_b.SYNC_ENABLE = 0U;
    }
    else if (TIMER_MODE_EDGE_DETECT == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->TIM_W_PULSE_CNT_GPIO_REG = 0U;
    }

#if !BSP_FEATURE_ELC_MISSING
    p_instance_ctrl->p_reg->TIMER_ELC_TASK_REG = 0U;
#endif
}

/*******************************************************************************************************************//**
 * Disables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 **********************************************************************************************************************/
static void r_tim_w_disable_irq (IRQn_Type irq)
{
    /* Disable interrupts. */
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Calculates clock frequency of TIM_W counter.  Divides TIM_W clock by TIM_W clock divisor.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 * ********************************************************************************************************/
static uint32_t r_tim_w_clock_frequency_get (tim_w_instance_ctrl_t * const p_instance_ctrl)
{
    /* Frequency = Timer clock frequency / 2^N, where N = 0 to 8 */
    uint32_t prescaler_val = 0;

    tim_w_clock_t src = (tim_w_clock_t) p_instance_ctrl->p_reg->TIMER_CTRL_REG_b.TIM_SYS_CLK_EN;

    prescaler_val = p_instance_ctrl->p_reg->TIM_W_PRESCALER;

    uint32_t timer_clk_freq = 0;

    if (src == TIM_W_CLOCK_DIVN)
    {
#if BSP_MCU_GROUP_RA6W1
        timer_clk_freq = BSP_CFG_XTALM_HZ;
#else
        timer_clk_freq = BSP_DIVN_FREQ_HZ;
#endif
    }
    else if (src == TIM_W_CLOCK_LP_CLK)
    {
#if BSP_FEATURE_CGC_HAS_LP_CLOCK       //! TIN_TODO: Remove when TIN lp clocks are added

        /* Get the LP clock Hz */
        timer_clk_freq = R_BSP_LPClockHzGet();
#else //! TIN_TODO: Remove when TIN lp clocks are added
        timer_clk_freq = TIM_W_PRV_LP_CLK_HZ;
#endif
    }

    /* Calculate the timer's frequency after the prescaler */
    return timer_clk_freq / (1 << prescaler_val);
}

/*******************************************************************************************************************//**
 * Freeze selected timer
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static void r_tim_w_freeze (tim_w_instance_ctrl_t * const p_instance_ctrl)
{
#if BSP_FEATURE_TIM_W_SUPPORTS_PAUSE_NATIVELY
    p_instance_ctrl->p_reg->TIMER_PAUSE_REG = 1U;
#else

    /* Calculate the freeze bit corresponding to the channel.
     * The range of SET_FREEZE_REG_b.FRZ_SWTIM..FRZ_SWTIM8 is [1..8]. The channel range is [0..7].
     */
    uint32_t freeze_bit = p_instance_ctrl->p_cfg->channel + 1;
    CRG_TOP->SET_FREEZE_REG = (1 << freeze_bit);
#endif
}

/*******************************************************************************************************************//**
 * Unfreeze selected timer
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static void r_tim_w_unfreeze (tim_w_instance_ctrl_t * const p_instance_ctrl)
{
#if BSP_FEATURE_TIM_W_SUPPORTS_PAUSE_NATIVELY
    p_instance_ctrl->p_reg->TIMER_PAUSE_REG = 0U;
#else

    /* Calculate the freeze bit corresponding to the channel.
     * The range of RESET_FREEZE_REG_b.FRZ_SWTIM..FRZ_SWTIM8 is [1..8]. The channel range is [0..7].
     */
    uint32_t freeze_bit = p_instance_ctrl->p_cfg->channel + 1;
    CRG_TOP->RESET_FREEZE_REG = (1 << freeze_bit);
#endif
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to TIM_W instance control block
 * @param[in]     event      Event code
 * @param[in]     capture    Event capture counts (if applicable)
 **********************************************************************************************************************/
static void r_tim_w_call_callback (tim_w_instance_ctrl_t * p_ctrl, uint8_t event, uint32_t capture)
{
    timer_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    timer_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->event     = (timer_event_t) event;
    p_args->capture   = capture;
    p_args->p_context = p_ctrl->p_context;
    p_ctrl->p_callback(p_args);

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Stops the timer if one-shot mode, clears interrupts, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void r_tim_w_ccm_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint32_t      capture_val    = 0U;
    timer_event_t callback_event = (timer_event_t) 0U;

#if BSP_FEATURE_TIM_W_HAS_IRQ_PER_CAPTURE_CHANNEL
    tim_w_extended_cfg_t * p_extend   = (tim_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    timer_event_t          event_base = TIMER_EVENT_COMPARE_A;

    for (uint8_t index = 0; index < p_extend->p_ccm_cfg->ccm_channel_size; index++)
    {
        if (p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].ccm_operation_irq == irq)
        {
            if (TIM_W_CCM_OPERATION_CAPTURE == p_extend->p_ccm_cfg->p_ccm_channel_cfg[index].operation)
            {
                event_base = TIMER_EVENT_CAPTURE_A;
            }

            callback_event = (timer_event_t) ((uint32_t) event_base + (uint32_t) index);

            /* Get the corresponding captured snapshot */
            capture_val = p_instance_ctrl->p_reg->TIMER_CAPTURE_GPIO_REG[index];

            /*
             * Since this isr is called for one ccm event at a time,
             * we can break and exit the loop on the first irq we find that triggered
             * the ISR.
             */
            break;
        }
    }

#else

    /* Get captured value. */
    if (true == p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_GPIO1_EVENT_PENDING)
    {
        callback_event = TIMER_EVENT_CAPTURE_A;
        capture_val    = p_instance_ctrl->p_reg->TIMER_CAPTURE_GPIO1_REG;
        p_instance_ctrl->p_reg->TIMER_CLEAR_GPIO_EVENT_REG_b.TIM_CLEAR_GPIO1_EVENT = true;
    }
    else if (true == p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_GPIO2_EVENT_PENDING)
    {
        callback_event = TIMER_EVENT_CAPTURE_B;
        capture_val    = p_instance_ctrl->p_reg->TIMER_CAPTURE_GPIO2_REG;
        p_instance_ctrl->p_reg->TIMER_CLEAR_GPIO_EVENT_REG_b.TIM_CLEAR_GPIO2_EVENT = true;
    }
    else if (true == p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_GPIO3_EVENT_PENDING)
    {
        callback_event = TIMER_EVENT_CAPTURE_C;
        capture_val    = p_instance_ctrl->p_reg->TIMER_CAPTURE_GPIO3_REG;
        p_instance_ctrl->p_reg->TIMER_CLEAR_GPIO_EVENT_REG_b.TIM_CLEAR_GPIO3_EVENT = true;
    }
    else if (true == p_instance_ctrl->p_reg->TIMER_STATUS_REG_b.TIM_GPIO4_EVENT_PENDING)
    {
        callback_event = TIMER_EVENT_CAPTURE_D;
        capture_val    = p_instance_ctrl->p_reg->TIMER_CAPTURE_GPIO4_REG;
        p_instance_ctrl->p_reg->TIMER_CLEAR_GPIO_EVENT_REG_b.TIM_CLEAR_GPIO4_EVENT = true;
    }

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    p_instance_ctrl->p_reg->TIMER_CLEAR_IRQ_REG = 0;
#endif
    if (NULL != p_instance_ctrl->p_callback)
    {
        r_tim_w_call_callback(p_instance_ctrl, callback_event, capture_val);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Stops the timer if one-shot mode, clears interrupts, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void r_tim_w_generic_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    timer_event_t event;
    uint32_t      timer_status = p_instance_ctrl->p_reg->TIMER_STATUS_REG;

    /* Store the event that caused the generic irq
     * and clear the equivalent status register
     */
    if (timer_status & TIMER_TIMER_STATUS_REG_TIM_IRQ_PULSE_STATUS_Msk)
    {
        event = TIMER_EVENT_PULSE_CNT_CYCLE_END;
#if BSP_MCU_GROUP_RA6W1
        p_instance_ctrl->p_reg->TIMER_CLEAR_IRQ_PULSE_REG_b.TIM_CLEAR_PULSE_IRQ = 1U;
#else
        p_instance_ctrl->p_reg->TIMER_CLEAR_REG = TIMER_TIMER_CLEAR_REG_TIM_CLEAR_IRQ_PULSE_STATUS_Msk;
#endif
    }

#if BSP_FEATURE_TIM_W_SUPPORTS_SEQ_CAPTURES
    else if (timer_status & TIMER_TIMER_STATUS_REG_TIM_IRQ_SEQ_STATUS_Msk) //!
    {
        event = TIMER_EVENT_SEQUENTIAL_CAPTURE_CYCLE_END;
        p_instance_ctrl->p_reg->TIMER_CLEAR_REG = TIMER_TIMER_CLEAR_REG_TIM_CLEAR_IRQ_SEQ_STATUS_Msk;
    }
#endif
    else                               /* Counter has wrapped around */
    {
        event = TIMER_EVENT_CYCLE_END;
#if BSP_MCU_GROUP_RA6W1
        p_instance_ctrl->p_reg->TIMER_CLEAR_IRQ_REG = 1U;
#else
        p_instance_ctrl->p_reg->TIMER_CLEAR_REG = TIMER_TIMER_CLEAR_REG_TIM_CLEAR_IRQ_STATUS_Msk;
#endif
    }

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqClearPending(irq);

    if (NULL != p_instance_ctrl->p_callback)
    {
        r_tim_w_call_callback(p_instance_ctrl, event, 0);
    }

    /* Clear pending IRQ a second time after callback to account for repeated interrupts from 0 period setting. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        R_BSP_IrqClearPending(irq);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#if BSP_FEATURE_TIM_W_SUPPORTS_OVERFLOW_UNDERFLOW

/*******************************************************************************************************************//**
 * Stops the timer if one-shot mode, clears interrupts, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void r_tim_w_counter_overflow_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear irq status bit */
    p_instance_ctrl->p_reg->TIMER_CLEAR_REG = TIMER_TIMER_CLEAR_REG_TIM_CLEAR_IRQ_STATUS_Msk;

    /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
    R_BSP_IrqClearPending(irq);

    if (NULL != p_instance_ctrl->p_callback)
    {
        r_tim_w_call_callback(p_instance_ctrl, TIMER_EVENT_OVERFLOW, 0);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Clears interrupts, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void r_tim_w_counter_underflow_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    tim_w_instance_ctrl_t * p_instance_ctrl = (tim_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
    R_BSP_IrqClearPending(irq);

    /* Clear irq status bit */
    p_instance_ctrl->p_reg->TIMER_CLEAR_REG = TIMER_TIMER_CLEAR_REG_TIM_CLEAR_IRQ_STATUS_Msk;

    if (NULL != p_instance_ctrl->p_callback)
    {
        r_tim_w_call_callback(p_instance_ctrl, TIMER_EVENT_UNDERFLOW, 0);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif
