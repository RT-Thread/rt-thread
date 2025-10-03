/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_gpt.h"
#include "r_gpt_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "GPT" in ASCII, used to determine if channel is open. */
#define GPT_OPEN                                         (0x00475054ULL)

/* define in case unsupported */
#ifndef BSP_FEATURE_GPT_GPTEH_CHANNEL_MASK
 #define BSP_FEATURE_GPT_GPTEH_CHANNEL_MASK              (0)
#endif
#ifndef BSP_FEATURE_GPT_GPTE_CHANNEL_MASK
 #define BSP_FEATURE_GPT_GPTE_CHANNEL_MASK               (0)
#endif
#ifndef BSP_FEATURE_GPT_AD_DIRECT_START_CHANNEL_MASK
 #define BSP_FEATURE_GPT_AD_DIRECT_START_CHANNEL_MASK    (0)
#endif

#define GPT_PRV_GPTE_OR_GPTEH_SUPPORTED                  (BSP_FEATURE_GPT_GPTEH_SUPPORTED | \
                                                          BSP_FEATURE_GPT_GPTE_SUPPORTED)
#define GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK               (BSP_FEATURE_GPT_GPTEH_CHANNEL_MASK | \
                                                          BSP_FEATURE_GPT_GPTE_CHANNEL_MASK)
#define GPT_PRV_ADC_DIRECT_START_SUPPORTED               (BSP_FEATURE_GPT_AD_DIRECT_START_SUPPORTED)
#define GPT_PRV_ADC_DIRECT_START_CHANNEL_MASK            (BSP_FEATURE_GPT_AD_DIRECT_START_CHANNEL_MASK)
#define GPT_PRV_ADC_ELC_START_SUPPORTED                  (GPT_PRV_GPTE_OR_GPTEH_SUPPORTED && \
                                                          !GPT_PRV_ADC_DIRECT_START_SUPPORTED)      // ELC-start is 'default' and exists if direct-start is not present
#define GPT_PRV_ADC_ELC_START_CHANNEL_MASK               (GPT_PRV_ADC_DIRECT_START_SUPPORTED ? \
                                                          0x0 : GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK) // No ELC-start present if direct start is supported.

#define GPT_PRV_ODC_SUPPORTED                            (BSP_FEATURE_GPT_GPTEH_SUPPORTED)
#define GPT_PRV_ODC_CHANNEL_MASK                         (BSP_FEATURE_GPT_GPTEH_CHANNEL_MASK)
#define GPT_PRV_GTWP_RESET_VALUE                         (0xA500U)
#define GPT_PRV_GTWP_WRITE_PROTECT                       (0xA501U)

#define GPT_PRV_GTIOR_STOP_LEVEL_BIT                     (6)
#define GPT_PRV_GTIOR_INITIAL_LEVEL_BIT                  (4)

#define GPT_PRV_GTIO_HIGH_COMPARE_MATCH_LOW_CYCLE_END    (0x6U)
#define GPT_PRV_GTIO_LOW_COMPARE_MATCH_HIGH_CYCLE_END    (0x9U)

#define GPT_PRV_GTIO_TOGGLE_COMPARE_MATCH                (0x3U)

#define GPT_PRV_GTBER_BUFFER_ENABLE_FORCE_TRANSFER       (0x550000U)
#define GPT_PRV_GTBER_DISABLE_BUFFER_OP_GTCCRA_GTCCRB    (0x500000U)

#define GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE             (0x80000000U)

#define GPT_PRV_GTCCRA                                   (0U)
#define GPT_PRV_GTCCRB                                   (1U)
#define GPT_PRV_GTCCRC                                   (2U)
#define GPT_PRV_GTCCRE                                   (3U)
#define GPT_PRV_GTCCRD                                   (4U)
#define GPT_PRV_GTCCRF                                   (5U)

/* GPT_CFG_OUTPUT_SUPPORT_ENABLE is set to 2 to enable extra features. */
#define GPT_PRV_EXTRA_FEATURES_ENABLED                   (2U)

#define R_GPT0_GTINTAD_ADTRAUEN_Pos                      (16U)

#define GPT_PRV_COMPARE_MATCH_A_MASK                     (0x01)
#define GPT_PRV_COMPARE_MATCH_B_MASK                     (0x02)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Duty cycle mode. */
typedef enum e_gpt_duty_cycle_mode
{
    GPT_DUTY_CYCLE_MODE_REGISTER    = 0, // Duty cycle depends on compare match
    GPT_DUTY_CYCLE_MODE_0_PERCENT   = 2, // Output low
    GPT_DUTY_CYCLE_MODE_100_PERCENT = 3, // Output high
} gpt_duty_cycle_mode_t;

/* Count direction */
typedef enum e_gpt_dir
{
    GPT_DIR_COUNT_DOWN = 0,
    GPT_DIR_COUNT_UP   = 1
} gpt_dir_t;

typedef struct st_gpt_prv_duty_registers
{
    uint32_t gtccr_buffer;
    uint32_t omdty;
} gpt_prv_duty_registers_t;

typedef enum e_gpt_prv_capture_event
{
    GPT_PRV_CAPTURE_EVENT_A,
    GPT_PRV_CAPTURE_EVENT_B,
} gpt_prv_capture_event_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * gpt_prv_ns_callback)(timer_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile gpt_prv_ns_callback)(timer_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void gpt_hardware_initialize(gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);

static void gpt_common_open(gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);

static uint32_t gpt_clock_frequency_get(gpt_instance_ctrl_t * const p_instance_ctrl);

static void gpt_hardware_events_disable(gpt_instance_ctrl_t * p_instance_ctrl);

static void r_gpt_disable_irq(IRQn_Type irq);

static inline void r_gpt_write_protect_enable(gpt_instance_ctrl_t * const p_instance_ctrl,
                                              uint32_t                    write_protect_setting);
static inline uint32_t r_gpt_write_protect_disable(gpt_instance_ctrl_t * const p_instance_ctrl);

/* Noinline attribute added to reduce code size for CM23 GCC build. */
static void r_gpt_enable_irq(IRQn_Type const irq, uint32_t priority, void * p_context) __attribute__((noinline));

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

static void gpt_calculate_duty_cycle(gpt_instance_ctrl_t * const p_instance_ctrl,
                                     uint32_t const              duty_cycle_counts,
                                     gpt_prv_duty_registers_t  * p_duty_reg,
                                     uint32_t                    pin);

static uint32_t gpt_gtior_calculate(timer_cfg_t const * const p_cfg, gpt_pin_level_t const stop_level);

#endif

static void r_gpt_call_callback(gpt_instance_ctrl_t * p_ctrl, timer_event_t event, uint32_t capture);

static void r_gpt_init_compare_match_channel(gpt_instance_ctrl_t * p_instance_ctrl);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void gpt_counter_overflow_isr(void);
void gpt_counter_underflow_isr(void);
void gpt_capture_compare_a_isr(void);
void gpt_capture_compare_b_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* GPT implementation of timer interface  */
const timer_api_t g_timer_on_gpt =
{
    .open            = R_GPT_Open,
    .stop            = R_GPT_Stop,
    .start           = R_GPT_Start,
    .reset           = R_GPT_Reset,
    .enable          = R_GPT_Enable,
    .disable         = R_GPT_Disable,
    .periodSet       = R_GPT_PeriodSet,
    .dutyCycleSet    = R_GPT_DutyCycleSet,
    .compareMatchSet = R_GPT_CompareMatchSet,
    .infoGet         = R_GPT_InfoGet,
    .statusGet       = R_GPT_StatusGet,
    .callbackSet     = R_GPT_CallbackSet,
    .close           = R_GPT_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup GPT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the timer module and applies configurations. Implements @ref timer_api_t::open.
 *
 * GPT hardware does not support one-shot functionality natively.  When using one-shot mode, the timer will be stopped
 * in an ISR after the requested period has elapsed.
 *
 * The GPT implementation of the general timer can accept a gpt_extended_cfg_t extension parameter.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL or the source divider is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       timer_cfg_t::mode is ::TIMER_MODE_ONE_SHOT or timer_cfg_t::p_callback is not
 *                                        NULL, but ISR is not enabled.  ISR must be enabled to use one-shot mode or
 *                                        callback.
 * @retval FSP_ERR_INVALID_MODE           Triangle wave PWM is only supported if GPT_CFG_OUTPUT_SUPPORT_ENABLE is 2.
 *                                        Selected channel does not support external count sources.
 *                                        External and event count sources not are available in this mode.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_instance_ctrl);

 #if (2U == BSP_FEATURE_GPT_CLOCK_DIVIDER_STEP_SIZE)
  #if (BSP_FEATURE_GPT_CLOCK_DIVIDER_VALUE_7_9_VALID)
    FSP_ASSERT(p_cfg->source_div <= 10U);
  #else
    FSP_ASSERT((p_cfg->source_div != 7U) && (p_cfg->source_div != 9U) && (p_cfg->source_div <= 10));
  #endif
 #else
    FSP_ASSERT((0U == (p_cfg->source_div % 2U)) && (p_cfg->source_div <= 10));
 #endif

 #if GPT_PRV_EXTRA_FEATURES_ENABLED != GPT_CFG_OUTPUT_SUPPORT_ENABLE
    FSP_ERROR_RETURN(p_cfg->mode <= TIMER_MODE_ONE_SHOT_PULSE, FSP_ERR_INVALID_MODE);
 #endif

    FSP_ERROR_RETURN(GPT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_instance_ctrl->channel_mask = 1U << p_cfg->channel;

#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN((p_instance_ctrl->channel_mask & BSP_PERIPHERAL_GPT_CHANNEL_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    if ((p_cfg->p_callback) || (TIMER_MODE_ONE_SHOT == p_cfg->mode))
    {
        FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_cfg->p_extend;
    FSP_ERROR_RETURN((!p_extend->count_up_source && !p_extend->count_down_source) ||
                     (BSP_FEATURE_GPT_EVENT_COUNT_CHANNEL_MASK & p_instance_ctrl->channel_mask),
                     FSP_ERR_INVALID_MODE);

 #if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Alternate count sources cannot be used in triangle PWM modes */
    FSP_ERROR_RETURN(!((p_cfg->mode >= TIMER_MODE_ONE_SHOT_PULSE) &&
                       (p_extend->count_up_source || p_extend->count_down_source)),
                     FSP_ERR_INVALID_MODE);

    /* Callback is required if underflow interrupt is enabled. */
    gpt_extended_pwm_cfg_t const * p_pwm_cfg = p_extend->p_pwm_cfg;

    if (NULL != p_pwm_cfg)
    {
        if (p_pwm_cfg->trough_irq >= 0)
        {
            FSP_ASSERT(NULL != p_cfg->p_callback);
        }
    }
 #endif
#endif

    /* Initialize control structure based on configurations. */
    gpt_common_open(p_instance_ctrl, p_cfg);

    gpt_hardware_initialize(p_instance_ctrl, p_cfg);

    p_instance_ctrl->open = GPT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops timer. Implements @ref timer_api_t::stop.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Stop
 *
 * @retval FSP_SUCCESS                 Timer successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Stop (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer. Implements @ref timer_api_t::start.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Start
 *
 * @retval FSP_SUCCESS                 Timer successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Start (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start timer */
    p_instance_ctrl->p_reg->GTSTR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to 0. Implements @ref timer_api_t::reset.
 *
 * @note This function also updates to the new period if no counter overflow has occurred since the last call to
 * R_GPT_PeriodSet().
 *
 * @retval FSP_SUCCESS                 Counter value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Reset (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear timer counter. */
    p_instance_ctrl->p_reg->GTCLR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::enable.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Enable
 *
 * @retval FSP_SUCCESS                 External events successfully enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Enable (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Enable use of GTSTR, GTSTP, and GTCLR for this channel. */
    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint32_t             gtssr    = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    uint32_t             gtpsr    = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    uint32_t             gtcsr    = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;

    /* OR with user settings. */
    gtssr |= p_extend->start_source;
    gtpsr |= p_extend->stop_source;
    gtcsr |= p_extend->clear_source;

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set the count sources. Ensure stop and clear sources are set before start source, and capture sources are set
     * after start source. */
    p_instance_ctrl->p_reg->GTPSR   = gtpsr;
    p_instance_ctrl->p_reg->GTCSR   = gtcsr;
    p_instance_ctrl->p_reg->GTSSR   = gtssr;
    p_instance_ctrl->p_reg->GTICASR = p_extend->capture_a_source;
    p_instance_ctrl->p_reg->GTICBSR = p_extend->capture_b_source;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::disable.
 *
 * @note The timer could be running after R_GPT_Disable(). To ensure it is stopped, call R_GPT_Stop().
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Disable
 *
 * @retval FSP_SUCCESS                 External events successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Disable (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    gpt_hardware_events_disable(p_instance_ctrl);

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets period value provided. If the timer is running, the period will be updated after the next counter overflow.
 * If the timer is stopped, this function resets the counter and updates the period.
 * Implements @ref timer_api_t::periodSet.
 *
 * @warning If periodic output is used, the duty cycle buffer registers are updated after the period buffer register.
 * If this function is called while the timer is running and a GPT overflow occurs during processing, the duty cycle
 * will not be the desired 50% duty cycle until the counter overflow after processing completes.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    /* Update period buffer register. The actual period is one cycle longer than the register value for saw waves
     * and twice the register value for triangle waves. Reference section 23.2.21 "General PWM Timer Cycle Setting
     * Register (GTPR)". The setting passed to the configuration is expected to be half the desired period for
     * triangle waves. */
    uint32_t new_gtpr = period_counts - 1U;
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (p_instance_ctrl->p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        new_gtpr = period_counts;
    }
#endif

    p_instance_ctrl->p_reg->GTPBR = new_gtpr;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Set a 50% duty cycle so the period of the waveform on the output pin matches the requested period. */
    if (TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode)
    {
        /* The  GTIOCA/GTIOCB pins transition 1 cycle after compare match when buffer operation is used. Reference
         * Figure 23.34 "Example setting for saw-wave PWM mode" in the RA6M3 manual R01UH0886EJ0100. To get a duty cycle
         * as close to 50% as possible, duty cycle (register) = (period (counts) / 2) - 1. */
        uint32_t duty_cycle_50_percent = (period_counts >> 1) - 1U;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRC] = duty_cycle_50_percent;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRE] = duty_cycle_50_percent;
    }
#endif

    /* If the counter is not counting, update period register and reset counter. */
    if (0U == p_instance_ctrl->p_reg->GTCR_b.CST)
    {
        p_instance_ctrl->p_reg->GTPR = new_gtpr;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE
        p_instance_ctrl->p_reg->GTBER = GPT_PRV_GTBER_BUFFER_ENABLE_FORCE_TRANSFER;
#endif

        p_instance_ctrl->p_reg->GTCLR = p_instance_ctrl->channel_mask;
    }

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets duty cycle on requested pin. Implements @ref timer_api_t::dutyCycleSet.
 *
 * Duty cycle is updated in the buffer register. The updated duty cycle is reflected after the next cycle end (counter
 * overflow).
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_DutyCycleSet
 *
 * @param[in] p_ctrl                   Pointer to instance control block.
 * @param[in] duty_cycle_counts        Duty cycle to set in counts.
 * @param[in] pin                      Use gpt_io_pin_t to select GPT_IO_PIN_GTIOCA or GPT_IO_PIN_GTIOCB
 *
 * @retval FSP_SUCCESS                 Duty cycle updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL or the pin is not one of gpt_io_pin_t
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    Duty cycle is larger than period.
 * @retval FSP_ERR_INVALID_MODE        GPT_IO_PIN_TROUGH, and GPT_IO_PIN_CREST settings are invalid in the this mode.
 * @retval FSP_ERR_UNSUPPORTED         GPT_CFG_OUTPUT_SUPPORT_ENABLE is 0.
 **********************************************************************************************************************/
fsp_err_t R_GPT_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
#if GPT_CFG_OUTPUT_SUPPORT_ENABLE
    uint32_t              tmp_pin         = pin & 3U;
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
 #if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(tmp_pin <= GPT_IO_PIN_GTIOCA_AND_GTIOCB);
    bool pwm_mode3_pin = 0 != (pin & (GPT_IO_PIN_CREST | GPT_IO_PIN_TROUGH));
    if (TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3 == p_instance_ctrl->p_cfg->mode)
    {
        /* In TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3, the duty cycle must be for either a trough or crest. */
        FSP_ERROR_RETURN(pwm_mode3_pin, FSP_ERR_INVALID_MODE);
    }
    else
    {
        FSP_ERROR_RETURN((!pwm_mode3_pin) || (TIMER_MODE_ONE_SHOT_PULSE == p_instance_ctrl->p_cfg->mode),
                         FSP_ERR_INVALID_MODE);
    }

    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(duty_cycle_counts <= (p_instance_ctrl->p_reg->GTPBR + 1), FSP_ERR_INVALID_ARGUMENT);
 #endif

    /* Set duty cycle. */
    gpt_prv_duty_registers_t duty_regs = {UINT32_MAX, 0};

    gpt_calculate_duty_cycle(p_instance_ctrl, duty_cycle_counts, &duty_regs, pin);

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    /* Read modify write bitfield access is used to update GTUDDTYC to make sure we don't clobber settings for the
     * other pin. */
    uint32_t gtuddtyc = p_instance_ctrl->p_reg->GTUDDTYC;

    /* Only update GTCCR if 0% or 100% duty is not requested */
    if (!duty_regs.omdty)
    {
        uint32_t reg_offset = 2U;
        if (0 != (pin & GPT_IO_PIN_CREST))
        {
            /*
             * In TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3, if this is a crest duty cycle, then update the crest
             * duty cycle register. Otherwise, update the trough duty cycle register.
             * Or in case of One-Shot pulse mode, buffer registers are either GTCCRC and GTCCRD for pulses on GTIOCnA pin
             * or GTCCRE and GTCCRF for pulses on GTIOCnB pin.
             * Hence update registers GTCCRD, GTCCRF for trailing edge dutycycle counts on GTIOCnA, GTIOCnB respectively, otherwise update
             * registers GTCCRC,GTCCRE for leading edge dutycycle counts on GTIOCnA, GTIOCnB respectively.
             */
            reg_offset = 4U;
        }

        if (0 != (pin & GPT_IO_PIN_GTIOCA_AND_GTIOCB))
        {
            p_instance_ctrl->p_reg->GTCCR[reg_offset]     = duty_regs.gtccr_buffer;
            p_instance_ctrl->p_reg->GTCCR[reg_offset + 1] = duty_regs.gtccr_buffer;
        }
        else
        {
            p_instance_ctrl->p_reg->GTCCR[tmp_pin + reg_offset] = duty_regs.gtccr_buffer;
        }
    }

    if (0 != (pin & GPT_BUFFER_FORCE_PUSH))
    {
        /* Enable the compare match buffer. */
        p_instance_ctrl->p_reg->GTBER |= 1U << R_GPT0_GTBER_CCRSWT_Pos;
    }

    if (GPT_IO_PIN_GTIOCB != tmp_pin)
    {
        /* GTIOCA or both GTIOCA and GTIOCB. */
        gtuddtyc &= ~R_GPT0_GTUDDTYC_OADTY_Msk;
        gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OADTY_Pos;
    }

    if ((GPT_IO_PIN_GTIOCA_AND_GTIOCB == pin) && duty_regs.omdty)
    {
        /* When setting both pins to 0%/100% duty recalculate OBDTY before setting */
        gpt_calculate_duty_cycle(p_instance_ctrl, duty_cycle_counts, &duty_regs, GPT_IO_PIN_GTIOCB);
    }

    if (GPT_IO_PIN_GTIOCA != tmp_pin)
    {
        /* GTIOCB or both GTIOCA and GTIOCB. */
        gtuddtyc &= ~R_GPT0_GTUDDTYC_OBDTY_Msk;
        gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OBDTY_Pos;
    }

    p_instance_ctrl->p_reg->GTUDDTYC = gtuddtyc;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(duty_cycle_counts);
    FSP_PARAMETER_NOT_USED(pin);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif
}

/*******************************************************************************************************************//**
 * Set value for compare match feature. Implements @ref timer_api_t::compareMatchSet.
 *
 * @note This API should be used when timer is stop counting. And shall not be used along with PWM operation.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_CompareMatchSet
 *
 * @retval FSP_SUCCESS              Set the compare match value successfully.
 * @retval FSP_ERR_ASSERTION        p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance is not opened.
 * @retval FSP_ERR_NOT_ENABLED      Requested compare channel is disabled.
 **********************************************************************************************************************/
fsp_err_t R_GPT_CompareMatchSet (timer_ctrl_t * const        p_ctrl,
                                 uint32_t const              compare_match_value,
                                 timer_compare_match_t const match_channel)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;

#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Confirm that requested compare match channel is enabled */
    FSP_ERROR_RETURN(1U == (1U & ((uint8_t) (p_extend->compare_match_status >> match_channel))), FSP_ERR_NOT_ENABLED);
#endif

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set compare match value. As the counter counts from 0 to (period - 1), the compare match value from user's input
     * should be minus one. */
    p_instance_ctrl->p_reg->GTCCR[match_channel] = compare_match_value - 1U;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get timer information and store it in provided pointer p_info. Implements @ref timer_api_t::infoGet.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, frequency, and ELC event written to caller's
 *                                     structure successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_info was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get and store period */
    uint32_t gtpr          = p_instance_ctrl->p_reg->GTPR;
    uint32_t period_counts = gtpr + 1;
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (p_instance_ctrl->p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        period_counts = gtpr;
    }
#endif
    p_info->period_counts = period_counts;

    /* Get and store clock frequency */
    p_info->clock_frequency = gpt_clock_frequency_get(p_instance_ctrl);

    /* Get and store clock counting direction. Read count direction setting */
    p_info->count_direction = TIMER_DIRECTION_UP;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current timer status and store it in provided pointer p_status. Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_StatusGet
 *
 * @retval FSP_SUCCESS                 Current timer state and counter value set successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get counter state. */
    p_status->state = (timer_state_t) p_instance_ctrl->p_reg->GTCR_b.CST;

    /* Get counter value */
    p_status->counter = p_instance_ctrl->p_reg->GTCNT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set counter value.
 *
 * @note Do not call this API while the counter is counting.  The counter value can only be updated while the counter
 * is stopped.
 *
 * @retval FSP_SUCCESS                 Counter value updated.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_IN_USE              The timer is running.  Stop the timer before calling this function.
 **********************************************************************************************************************/
fsp_err_t R_GPT_CounterSet (timer_ctrl_t * const p_ctrl, uint32_t counter)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0U == p_instance_ctrl->p_reg->GTCR_b.CST, FSP_ERR_IN_USE);
#endif

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set counter value */
    p_instance_ctrl->p_reg->GTCNT = counter;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable output for GTIOCA and/or GTIOCB.
 *
 * @retval FSP_SUCCESS                 Output is enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_OutputEnable (timer_ctrl_t * const p_ctrl, gpt_io_pin_t pin)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    uint32_t gtior = p_instance_ctrl->p_reg->GTIOR;
    if (GPT_IO_PIN_GTIOCB != pin)
    {
        /* GTIOCA or both GTIOCA and GTIOCB. */
        gtior |= R_GPT0_GTIOR_OAE_Msk;
    }

    if (GPT_IO_PIN_GTIOCA != pin)
    {
        /* GTIOCB or both GTIOCA and GTIOCB. */
        gtior |= R_GPT0_GTIOR_OBE_Msk;
    }

    p_instance_ctrl->p_reg->GTIOR = gtior;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable output for GTIOCA and/or GTIOCB.
 *
 * @retval FSP_SUCCESS                 Output is disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_OutputDisable (timer_ctrl_t * const p_ctrl, gpt_io_pin_t pin)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    uint32_t gtior = p_instance_ctrl->p_reg->GTIOR;
    if (GPT_IO_PIN_GTIOCB != pin)
    {
        /* GTIOCA or both GTIOCA and GTIOCB. */
        gtior &= ~R_GPT0_GTIOR_OAE_Msk;
    }

    if (GPT_IO_PIN_GTIOCA != pin)
    {
        /* GTIOCB or both GTIOCA and GTIOCB. */
        gtior &= ~R_GPT0_GTIOR_OBE_Msk;
    }

    p_instance_ctrl->p_reg->GTIOR = gtior;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set A/D converter start request compare match value.
 *
 * @retval FSP_SUCCESS                 Counter value updated.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_AdcTriggerSet (timer_ctrl_t * const    p_ctrl,
                               gpt_adc_compare_match_t which_compare_match,
                               uint32_t                compare_match_value)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set A/D converter start request compare match value. */
    volatile uint32_t * p_gtadtr = &p_instance_ctrl->p_reg->GTADTRA;
    p_gtadtr[which_compare_match] = compare_match_value;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the Output Delay setting for the PWM output pin.
 *
 * @retval FSP_SUCCESS                 The output delay was set.
 * @retval FSP_ERR_ASSERTION           An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_CHANNEL     The channel does not support this feature.
 * @retval FSP_ERR_NOT_INITIALIZED     The PWM Output Delay Circuit has not been initialized.
 * @retval FSP_ERR_INVALID_STATE       The PWM Output Delay setting cannot be updated in the current state.
 * @retval FSP_ERR_UNSUPPORTED         This feature is not supported on this MCU.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PwmOutputDelaySet (timer_ctrl_t * const           p_ctrl,
                                   gpt_pwm_output_delay_edge_t    edge,
                                   gpt_pwm_output_delay_setting_t delay_setting,
                                   uint32_t const                 pin)
{
#if 0U != GPT_PRV_ODC_SUPPORTED && GPT_CFG_OUTPUT_SUPPORT_ENABLE
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;

 #if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0U != (GPT_PRV_ODC_CHANNEL_MASK & p_instance_ctrl->channel_mask), FSP_ERR_INVALID_CHANNEL);
    FSP_ERROR_RETURN(0U != (R_GPT_ODC->GTDLYCR1 & R_GPT_ODC_GTDLYCR1_DLLEN_Msk), FSP_ERR_NOT_INITIALIZED);

    if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        /* In Saw-wave mode, do not change the settings for the delay while the compare-match value is greater than or
         * equal to GTPR - 2. */
        uint32_t gtpr          = p_instance_ctrl->p_reg->GTPR;
        uint32_t compare_match = p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRC + pin];
        FSP_ERROR_RETURN(gtpr - 2 > compare_match, FSP_ERR_INVALID_STATE);
    }
    else
    {
        uint32_t compare_match;
        if ((TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3 == p_instance_ctrl->p_cfg->mode) ||
            (TIMER_MODE_ONE_SHOT_PULSE == p_instance_ctrl->p_cfg->mode))
        {
            /* In TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3, the trough compare match value is set in
             * GTCCRD, and GTCCRF. */
            compare_match = p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRD + pin];
        }
        else
        {
            /* In TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM and TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM, the trough compare match value is
             * set in GTCCRC, and GTCCRE. */
            compare_match = p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRC + pin];
        }

        timer_direction_t count_direction = (timer_direction_t) p_instance_ctrl->p_reg->GTST_b.TUCF;

        /* In Triangle-wave mode, do not change the settings for the delay while the counter if going down and the compare-match
         * value is less than or equal to 2. */
        FSP_ERROR_RETURN(TIMER_DIRECTION_DOWN != count_direction || 2 < compare_match, FSP_ERR_INVALID_STATE);
    }
 #endif

    FSP_CRITICAL_SECTION_DEFINE;

    if (GPT_PWM_OUTPUT_DELAY_SETTING_BYPASS == delay_setting)
    {
        /* Enter a critical section in order to ensure that multiple GPT channels don't access the common
         * register simultaneously. */
        FSP_CRITICAL_SECTION_ENTER;

 #if GPT_CFG_WRITE_PROTECT_ENABLE

        /* GTDLYCR2 is protected by R_GPT::GTWP. */
        uint32_t wp = R_GPT0->GTWP;
        R_GPT0->GTWP = GPT_PRV_GTWP_RESET_VALUE;
        R_GPT0->GTWP;
 #endif

        /* Enable the Delay Generation Circuit bypass. */
        R_GPT_ODC->GTDLYCR2 &= (uint16_t) (~p_instance_ctrl->channel_mask & UINT16_MAX);

 #if GPT_CFG_WRITE_PROTECT_ENABLE

        /* Restore the previous value of GTWP. */
        R_GPT0->GTWP = wp | GPT_PRV_GTWP_RESET_VALUE;
 #endif

        FSP_CRITICAL_SECTION_EXIT;
    }
    else
    {
        /* Calculate the offset for the register than needs to be set. */
        uint32_t channel_offset = sizeof(uint32_t) * p_instance_ctrl->p_cfg->channel;
        uint32_t pin_offset     =
            (uint32_t) ((uint32_t) &R_GPT_ODC->GTDLYR[0].B - (uint32_t) &R_GPT_ODC->GTDLYR[0].A) * pin;
        uint32_t edge_offset =
            (uint32_t) ((uint32_t) &R_GPT_ODC->GTDLYF[0].A - (uint32_t) &R_GPT_ODC->GTDLYR[0].A) * edge;
        uint16_t * p_gtdlyfnx =
            (uint16_t *) ((uint32_t) &R_GPT_ODC->GTDLYR[0].A + channel_offset + pin_offset + edge_offset);

 #if BSP_FEATURE_GPT_ODC_128_RESOLUTION_SUPPORTED
        delay_setting *= 4;            // Delay count is out of 32, per the API. Convert provided 32-count resolution into 128-count register setting.
 #endif

        /* Unprotect the delay setting register. */
        uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

        /* Write the delay setting to the register. */
        *p_gtdlyfnx = (uint16_t) delay_setting;

        /* Restore the previous value of GTWP. */
        r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

        /* Check if the channel has already been enabled. */
        if (0U == (R_GPT_ODC->GTDLYCR2 & p_instance_ctrl->channel_mask))
        {
            /* Enter a critical section in order to ensure that multiple GPT channels don't access the common
             * register simultaneously. */
            FSP_CRITICAL_SECTION_ENTER;

 #if GPT_CFG_WRITE_PROTECT_ENABLE

            /* GTDLYCR2 is protected by R_GPT::GTWP. */
            wp           = R_GPT0->GTWP;
            R_GPT0->GTWP = GPT_PRV_GTWP_RESET_VALUE;
            R_GPT0->GTWP;
 #endif

            /* Disable the Delay Generation Circuit bypass. */
            R_GPT_ODC->GTDLYCR2 |= (uint16_t) p_instance_ctrl->channel_mask;

 #if GPT_CFG_WRITE_PROTECT_ENABLE

            /* Restore the previous value of GTWP. */
            R_GPT0->GTWP = wp | GPT_PRV_GTWP_RESET_VALUE;
 #endif

            FSP_CRITICAL_SECTION_EXIT;
        }
    }

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(edge);
    FSP_PARAMETER_NOT_USED(delay_setting);
    FSP_PARAMETER_NOT_USED(pin);

    return FSP_ERR_UNSUPPORTED;
#endif
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
fsp_err_t R_GPT_CallbackSet (timer_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(timer_callback_args_t *),
                             void * const                  p_context,
                             timer_callback_args_t * const p_callback_memory)
{
    gpt_instance_ctrl_t * p_ctrl = (gpt_instance_ctrl_t *) p_api_ctrl;

#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(GPT_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if GPT_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    timer_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                        CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(timer_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops counter, disables output pins, and clears internal driver data. Implements @ref timer_api_t::close.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Close (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;

#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable interrupts. */
    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    r_gpt_disable_irq(p_instance_ctrl->p_cfg->cycle_end_irq);
    r_gpt_disable_irq(p_extend->capture_a_irq);
    r_gpt_disable_irq(p_extend->capture_b_irq);
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    gpt_extended_pwm_cfg_t const * p_pwm_cfg = p_extend->p_pwm_cfg;
    if (NULL != p_pwm_cfg)
    {
        r_gpt_disable_irq(p_pwm_cfg->trough_irq);
    }
#endif

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

    /* Stop counter. */
    p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

    /* Disable output. */
    p_instance_ctrl->p_reg->GTIOR = 0U;

    r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

    return err;
}

/*******************************************************************************************************************//**
 * Initialize the PWM Delay Generation Circuit (PDG).
 * This function must be called before calling @ref R_GPT_PwmOutputDelaySet.
 *
 * @note This function will delay for 20 microseconds.
 *
 * @retval FSP_SUCCESS                 Initialization sequence completed successfully.
 * @retval FSP_ERR_INVALID_STATE       The source clock frequnecy is out of the required range for the PDG.
 * @retval FSP_ERR_UNSUPPORTED         This feature is not supported.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PwmOutputDelayInitialize ()
{
#if (BSP_FEATURE_GPT_GPTEH_SUPPORTED && GPT_CFG_OUTPUT_SUPPORT_ENABLE)
 #if ((BSP_FEATURE_GPT_ODC_FRANGE_FREQ_MIN > 0) || GPT_CFG_PARAM_CHECKING_ENABLE)
  #if (BSP_PERIPHERAL_GPT_GTCLK_PRESENT && (GPT_CFG_GPTCLK_BYPASS == 0))

    /* Calculate the GPTCK Divider. */
    uint8_t divider = R_SYSTEM->GPTCKDIVCR;

    if (0U == divider)
    {
        divider = 1U;
    }
    else
    {
        divider *= 2U;
    }

    /* Calculate the GPTCK Frequency. */
    uint32_t gpt_frequency = R_BSP_SourceClockHzGet((fsp_priv_source_clock_t) R_SYSTEM->GPTCKCR_b.GPTCKSEL) / divider;
  #else

    /* Calculate the PCLKD Frequency. */
    uint32_t gpt_frequency = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD);
  #endif
 #endif

 #if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(BSP_FEATURE_GPT_ODC_FREQ_MAX >= gpt_frequency, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(BSP_FEATURE_GPT_ODC_FREQ_MIN <= gpt_frequency, FSP_ERR_INVALID_STATE);
 #endif

    uint32_t gtdlycr1 = R_GPT_ODC_GTDLYCR1_DLYRST_Msk;

 #if BSP_FEATURE_GPT_ODC_FRANGE_FREQ_MIN > 0
    gtdlycr1 |= BSP_FEATURE_GPT_ODC_FRANGE_SET_BIT(gpt_frequency);
 #endif

 #if BSP_PERIPHERAL_GPT_GTCLK_PRESENT && GPT_CFG_GPTCLK_BYPASS

    /* Bypass the GPTCLK. GPT instances will use PCLKD as the GPT Core clock. */
    R_GPT_GTCLK->GTCLKCR = 1U;
 #endif

    /* Cancel the module-stop state for the PDG. */
    R_BSP_MODULE_START(FSP_IP_GPT_PDG, 0);

 #if GPT_CFG_WRITE_PROTECT_ENABLE

    /* Disable write protection for GPT registers if they are protected. */
    R_GPT0->GTWP = GPT_PRV_GTWP_RESET_VALUE;
    R_GPT0->GTWP;
 #endif

    /* Reset the PWM Delay Generation Circuit. */
    R_GPT_ODC->GTDLYCR1 = (uint16_t) gtdlycr1;
    R_GPT_ODC->GTDLYCR2 = 0;

    /* Enable the DLL. */
    R_GPT_ODC->GTDLYCR1 = (uint16_t) (gtdlycr1 | R_GPT_ODC_GTDLYCR1_DLLEN_Msk);

    /* Wait for the DLL to be enabled. */
    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MICROSECONDS);

    /* Release the PWM Delay Generation Circuit from reset. */
    R_GPT_ODC->GTDLYCR1 &= (uint16_t) ~R_GPT_ODC_GTDLYCR1_DLYRST_Msk;

 #if GPT_CFG_WRITE_PROTECT_ENABLE

    /* Re-enable write protection for GPT registers. */
    R_GPT0->GTWP = GPT_PRV_GTWP_WRITE_PROTECT;
 #endif

    return FSP_SUCCESS;
#else

    return FSP_ERR_UNSUPPORTED;
#endif
}

/** @} (end addtogroup GPT) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enables write protection.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 * @param[in]  write_protect_setting   The value of GTWP prior to being cleared.
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_enable (gpt_instance_ctrl_t * const p_instance_ctrl,
                                               uint32_t                    write_protect_setting)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    p_instance_ctrl->p_reg->GTWP = write_protect_setting;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(write_protect_setting);
#endif
}

/*******************************************************************************************************************//**
 * Disables write protection.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 **********************************************************************************************************************/
static inline uint32_t r_gpt_write_protect_disable (gpt_instance_ctrl_t * const p_instance_ctrl)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    uint32_t write_protect_setting = p_instance_ctrl->p_reg->GTWP;
    p_instance_ctrl->p_reg->GTWP = GPT_PRV_GTWP_RESET_VALUE;

    return write_protect_setting;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);

    return 0U;
#endif
}

/*******************************************************************************************************************//**
 * Initializes control structure based on configuration.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 * @param[in]  p_cfg                   Pointer to timer configuration.
 **********************************************************************************************************************/
static void gpt_common_open (gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Initialize control structure.  */
    p_instance_ctrl->p_cfg = p_cfg;

    /* If callback is not null or timer mode is one shot, make sure the IRQ is enabled and store callback in the
     *  control block.
     *  @note The GPT hardware does not support one-shot mode natively.  To support one-shot mode, the timer will be
     *  stopped and cleared using software in the ISR. *//* Determine if this is a 32-bit or a 16-bit timer. */
    p_instance_ctrl->variant = TIMER_VARIANT_16_BIT;
    if (0U != (p_instance_ctrl->channel_mask & BSP_FEATURE_GPT_32BIT_CHANNEL_MASK))
    {
        p_instance_ctrl->variant = TIMER_VARIANT_32_BIT;
    }

    /* Save register base address. */
    uint32_t base_address = (uint32_t) R_GPT0 + (p_cfg->channel * ((uint32_t) R_GPT1 - (uint32_t) R_GPT0));
    p_instance_ctrl->p_reg = (R_GPT0_Type *) base_address;

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;
}

/*******************************************************************************************************************//**
 * Performs hardware initialization of the GPT.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void gpt_hardware_initialize (gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Save pointer to extended configuration structure. */
    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_cfg->p_extend;

#if BSP_PERIPHERAL_GPT_GTCLK_PRESENT && GPT_CFG_GPTCLK_BYPASS

    /* Bypass the GPTCLK. GPT instances will use PCLKD as the GPT Core clock. */
    R_GPT_GTCLK->GTCLKCR = 1U;
#endif

    /* Power on GPT before setting any hardware registers. Make sure the counter is stopped before setting mode
     * register, PCLK divisor register, and counter register. */
    R_BSP_MODULE_START(FSP_IP_GPT, p_cfg->channel);

#if (GPT_CFG_OUTPUT_SUPPORT_ENABLE && BSP_FEATURE_GPT_GPTEH_SUPPORTED)
    if (0U != (BSP_FEATURE_GPT_GPTEH_CHANNEL_MASK & p_instance_ctrl->channel_mask))
    {
        /* Enter a critical section in order to ensure that multiple GPT channels don't access the common
         * register simultaneously. */
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

 #if GPT_CFG_WRITE_PROTECT_ENABLE

        /* Disable write protection for GPT registers if they are protected. */
        uint32_t wp = R_GPT0->GTWP;
        R_GPT0->GTWP = GPT_PRV_GTWP_RESET_VALUE;
        R_GPT0->GTWP;
 #endif

        /* Enable the Delay Generation Circuit bypass. */
        R_GPT_ODC->GTDLYCR2 &= (uint16_t) (~p_instance_ctrl->channel_mask & UINT16_MAX);

 #if GPT_CFG_WRITE_PROTECT_ENABLE
        R_GPT0->GTWP = wp | GPT_PRV_GTWP_RESET_VALUE;
 #endif

        FSP_CRITICAL_SECTION_EXIT;
    }
#endif

    /* Initialize all registers that may affect operation of this driver to reset values.  Skip these since they
     * affect all channels, and are initialized in GTCR and GTCNT: GTSTR, GTSTP, GTCLR. GTCR is set immediately after
     * clearing the module stop bit to ensure the timer is stopped before proceeding with configuration. */
    p_instance_ctrl->p_reg->GTWP  = GPT_PRV_GTWP_RESET_VALUE;
    p_instance_ctrl->p_reg->GTCR  = 0U;
    p_instance_ctrl->p_reg->GTST  = 0U;
    p_instance_ctrl->p_reg->GTCNT = 0U;

    /* GTPR, GTCCRn, GTIOR, GTSSR, GTPSR, GTCSR, GTUPSR, GTDNSR, GTPBR, and GTUDDTYC are set by this driver. */

    /* Initialization sets all register required for up counting as described in hardware manual (Figure 23.4 in the
     * RA6M3 manual R01UH0886EJ0100) and other registers required by the driver. */

    /* Dividers for GPT are half the enum value. */
    uint32_t gtcr_tpcs = p_cfg->source_div >> BSP_FEATURE_GPT_TPCS_SHIFT;
    uint32_t gtcr      = gtcr_tpcs << R_GPT0_GTCR_TPCS_Pos;

    /* Store period register setting. The actual period and is one cycle longer than the register value for saw waves
     * and twice the register value for triangle waves. Reference section 23.2.21 "General PWM Timer Cycle Setting
     * Register (GTPR)". The setting passed to the configuration is expected to be half the desired period for
     * triangle waves. */
    uint32_t gtpr = p_cfg->period_counts - 1U;

    /* Set GTCR.MD = 0x001 for TIMER_MODE_ONE_SHOT_PULSE mode. */
    if (TIMER_MODE_ONE_SHOT_PULSE == p_cfg->mode)
    {
        gtcr |= (1U << R_GPT0_GTCR_MD_Pos);
    }

#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Saw-wave PWM mode is set in GTCR.MD for all modes except TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM and
     * TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM. */
    if (p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        gtcr |= ((uint32_t) p_cfg->mode << R_GPT0_GTCR_MD_Pos);
        gtpr  = p_cfg->period_counts;
    }
#endif

    /* Counter must be stopped to update TPCS. Reference section 23.2.12 "General PWM Timer Control Register (GTCR)"
     * in the RA6M3 manual R01UH0886EJ0100. */
    p_instance_ctrl->p_reg->GTCR = gtcr;

    gpt_hardware_events_disable(p_instance_ctrl);

    /* Configure the up/down count sources. These are not affected by enable/disable. */
    p_instance_ctrl->p_reg->GTUPSR = p_extend->count_up_source;
    p_instance_ctrl->p_reg->GTDNSR = p_extend->count_down_source;

    /* Set period. The actual period is one cycle longer than the register value. Reference section 23.2.21
     * "General PWM Timer Cycle Setting Register (GTPR)". */
    p_instance_ctrl->p_reg->GTPBR = gtpr;
    p_instance_ctrl->p_reg->GTPR  = gtpr;

    uint32_t gtuddtyc = 0U;
    uint32_t gtior    = p_extend->gtior_setting.gtior;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* For one shot mode, the compare match buffer register must be loaded with a value that exceeds the timer
     * cycle end value so that second compare match event would never occur and hence there will be only a
     * single pulse.  Writing to the upper bits is ignored for 16-bit timers. */
    gpt_prv_duty_registers_t duty_regs = {UINT32_MAX, 0};

    if (TIMER_MODE_PERIODIC == p_cfg->mode)
    {
        /* The  GTIOCA/GTIOCB pins transition 1 cycle after compare match when buffer operation is used. Reference
         * Figure 23.34 "Example setting for saw-wave PWM mode" in the RA6M3 manual R01UH0886EJ0100. To get a duty cycle
         * as close to 50% as possible, duty cycle (register) = (period (counts) / 2) - 1. */
        uint32_t duty_cycle_50_percent = (p_cfg->period_counts >> 1) - 1U;
        duty_regs.gtccr_buffer = duty_cycle_50_percent;
    }

    if (p_cfg->mode >= TIMER_MODE_PWM)
    {
        gpt_calculate_duty_cycle(p_instance_ctrl, p_cfg->duty_cycle_counts, &duty_regs, GPT_IO_PIN_GTIOCA);
    }

    /* Set the compare match and compare match buffer registers based on previously calculated values. */
    p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRC] = duty_regs.gtccr_buffer;
    p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRE] = duty_regs.gtccr_buffer;

    if (p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        /* Set the double buffer registers for triangle modes. */
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRD] = duty_regs.gtccr_buffer;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRF] = duty_regs.gtccr_buffer;
    }

    /* If the requested duty cycle is 0% or 100%, set this in the registers. */
    gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OADTY_Pos;
    gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OBDTY_Pos;

    /* Check if custom GTIOR settings are provided. */
    if (0 == p_extend->gtior_setting.gtior)
    {
        /* If custom GTIOR settings are not provided, calculate GTIOR. */
        if (p_extend->gtioca.output_enabled)
        {
            uint32_t gtioca_gtior = gpt_gtior_calculate(p_cfg, p_extend->gtioca.stop_level);
            gtior |= gtioca_gtior << R_GPT0_GTIOR_GTIOA_Pos;
        }

        if (p_extend->gtiocb.output_enabled)
        {
            uint32_t gtiocb_gtior = gpt_gtior_calculate(p_cfg, p_extend->gtiocb.stop_level);
            gtior |= gtiocb_gtior << R_GPT0_GTIOR_GTIOB_Pos;
        }
    }
#endif

    r_gpt_init_compare_match_channel(p_instance_ctrl);

#if GPT_PRV_GPTE_OR_GPTEH_SUPPORTED
    if ((1U << p_cfg->channel) & GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK)
    {
        /* This register is available on GPTE and GPTEH only. It must be cleared before setting. When modifying the
         * IVTT[2:0] bits, first set the IVTC[1:0] bits to 00b.  Reference section 23.2.18 "General PWM Timer Interrupt
         * and A/D Converter Start Request Skipping Setting Register (GTITC)"" of the RA6M3 manual R01UH0886EJ0100. */
        p_instance_ctrl->p_reg->GTITC = 0U;
    }
#endif

#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    gpt_extended_pwm_cfg_t const * p_pwm_cfg = p_extend->p_pwm_cfg;
    if (NULL != p_pwm_cfg)
    {
        uint32_t gtintad = ((uint32_t) p_pwm_cfg->output_disable << R_GPT0_GTINTAD_GRPDTE_Pos) |
                           ((uint32_t) p_pwm_cfg->poeg_link << R_GPT0_GTINTAD_GRP_Pos);

        /* Configure PWM Dead-time.
         * GTDVU is available on most timers, while GTDVD is only available on a subset of timers (GPTE/GPTEH) */
 #if BSP_FEATURE_GPT_GTDVU_SUPPORTED
        if ((1U << p_cfg->channel) & (BSP_FEATURE_GPT_GTDVU_CHANNEL_MASK | GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK))
        {
            /* Enable Dead-time nagative-phase waveform
             * Set GTDTCR.TDE only if one of the dead time values is non-zero. */
            p_instance_ctrl->p_reg->GTDTCR =
                ((p_pwm_cfg->dead_time_count_up > 0) || (p_pwm_cfg->dead_time_count_down > 0));

            /* Dead time value register GTDVU */
            p_instance_ctrl->p_reg->GTDVU = p_pwm_cfg->dead_time_count_up;
        }
 #endif

 #if (GPT_PRV_ADC_DIRECT_START_SUPPORTED || GPT_PRV_ADC_ELC_START_SUPPORTED)
        if ((1U << p_cfg->channel) & (GPT_PRV_ADC_DIRECT_START_CHANNEL_MASK |
                                      GPT_PRV_ADC_ELC_START_CHANNEL_MASK))
        {
  #if (GPT_PRV_GPTE_OR_GPTEH_SUPPORTED)

            /* Dead time value register GTDVD */
            p_instance_ctrl->p_reg->GTDVD = p_pwm_cfg->dead_time_count_down;

            /* GTITC is always present for GPTE and GPTEH timers */
            p_instance_ctrl->p_reg->GTITC = ((uint32_t) p_pwm_cfg->interrupt_skip_source << R_GPT0_GTITC_IVTC_Pos) |
                                            ((uint32_t) p_pwm_cfg->interrupt_skip_count << R_GPT0_GTITC_IVTT_Pos) |
                                            ((uint32_t) p_pwm_cfg->interrupt_skip_adc << R_GPT0_GTITC_ADTAL_Pos);
  #endif

            /* Configure AD Compare match behavior */
            gtintad |= ((uint32_t) p_pwm_cfg->adc_trigger << R_GPT0_GTINTAD_ADTRAUEN_Pos);
            p_instance_ctrl->p_reg->GTADTRA = p_pwm_cfg->adc_a_compare_match;
            p_instance_ctrl->p_reg->GTADTRB = p_pwm_cfg->adc_b_compare_match;
        }
 #endif

        p_instance_ctrl->p_reg->GTINTAD = gtintad;

        /* Check if custom GTIOR (Input/Output) settings are provided. */
        if (0 == p_extend->gtior_setting.gtior)
        {
            /* If custom GTIOR settings are not provided, set gtioca_disable_settings and gtiocb_disable_settings. */
            gtior |= (uint32_t) (p_pwm_cfg->gtioca_disable_setting << R_GPT0_GTIOR_OADF_Pos);
            gtior |= (uint32_t) (p_pwm_cfg->gtiocb_disable_setting << R_GPT0_GTIOR_OBDF_Pos);
        }
    }
    else
#endif

    {
        /* GTADTR* registers are unused if GTINTAD is cleared. */
        p_instance_ctrl->p_reg->GTINTAD = 0U;

        /* GTDVU, GTDVD, GTDBU, GTDBD, and GTSOTR are not used if GTDTCR is cleared. */
        p_instance_ctrl->p_reg->GTDTCR = 0U;
    }

    /* Check if custom GTIOR settings are provided. */
    if (0 == p_extend->gtior_setting.gtior)
    {
        /*
         * If custom GTIOR settings are not provided, configure the noise filter for
         * the GTIOC pins.
         */
        gtior |= (uint32_t) (p_extend->capture_filter_gtioca << R_GPT0_GTIOR_NFAEN_Pos);
        gtior |= (uint32_t) (p_extend->capture_filter_gtiocb << R_GPT0_GTIOR_NFBEN_Pos);
    }

    uint32_t gtber = GPT_PRV_GTBER_BUFFER_ENABLE_FORCE_TRANSFER;

    if (p_extend->compare_match_status)
    {
        /* If compare match being used, GTCCRA and GTCCRB will operate with no buffer. */
        gtber = GPT_PRV_GTBER_DISABLE_BUFFER_OP_GTCCRA_GTCCRB;
    }

    p_instance_ctrl->p_reg->GTBER = gtber;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (TIMER_MODE_ONE_SHOT == p_cfg->mode)
    {
        /* In one shot mode, the output pin toggles when counting starts, then again when the period expires.
         * The buffer is enabled to set the compare match to UINT32_MAX after the one shot pulse is output
         * so that the pin level will not change if the period expires again before the timer is stopped in
         * the interrupt.*/
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRA] = 0U;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRB] = 0U;
    }
#endif

    /* Set the I/O control register. */
    p_instance_ctrl->p_reg->GTIOR = gtior;

    /* Configure duty cycle and force timer to count up. GTUDDTYC must be set, then cleared to force the count
     * direction to be reflected when counting starts. Reference section 23.2.13 "General PWM Timer Count Direction
     * and Duty Setting Register (GTUDDTYC)" in the RA6M3 manual R01UH0886EJ0100. */
    p_instance_ctrl->p_reg->GTUDDTYC = gtuddtyc | 3U;
    p_instance_ctrl->p_reg->GTUDDTYC = gtuddtyc | 1U;

    /* Reset counter to 0. */
    p_instance_ctrl->p_reg->GTCLR = p_instance_ctrl->channel_mask;

    r_gpt_write_protect_enable(p_instance_ctrl, GPT_PRV_GTWP_WRITE_PROTECT);

    /* Enable CPU interrupts if callback is not null.  Also enable interrupts for one shot mode.
     *  @note The GPT hardware does not support one-shot mode natively. To support one-shot mode, the timer will be
     *  stopped and cleared using software in the ISR. */
    r_gpt_enable_irq(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);
    r_gpt_enable_irq(p_extend->capture_a_irq, p_extend->capture_a_ipl, p_instance_ctrl);
    r_gpt_enable_irq(p_extend->capture_b_irq, p_extend->capture_b_ipl, p_instance_ctrl);
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (NULL != p_pwm_cfg)
    {
        r_gpt_enable_irq(p_pwm_cfg->trough_irq, p_pwm_cfg->trough_ipl, p_instance_ctrl);
    }
#endif
}

/*******************************************************************************************************************//**
 * Disables hardware events that would cause the timer to start, stop, clear, or capture.
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static void gpt_hardware_events_disable (gpt_instance_ctrl_t * p_instance_ctrl)
{
    /* Enable use of GTSTR, GTSTP, and GTCLR for this channel. */
    p_instance_ctrl->p_reg->GTSSR   = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    p_instance_ctrl->p_reg->GTPSR   = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    p_instance_ctrl->p_reg->GTCSR   = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    p_instance_ctrl->p_reg->GTICASR = GPT_SOURCE_NONE;
    p_instance_ctrl->p_reg->GTICBSR = GPT_SOURCE_NONE;
}

/*******************************************************************************************************************//**
 * Disables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 **********************************************************************************************************************/
static void r_gpt_disable_irq (IRQn_Type irq)
{
    /* Disable interrupts. */
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Configures and enables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 * @param[in]  priority                NVIC priority of the interrupt
 * @param[in]  p_context               The interrupt context is a pointer to data required in the ISR.
 **********************************************************************************************************************/
static void r_gpt_enable_irq (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, priority, p_context);
    }
}

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Calculates duty cycle register values.  GTPR must be set before entering this function.
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 * @param[in]  duty_cycle_counts       Duty cycle to set
 * @param[out] p_duty_reg              Duty cycle register values
 **********************************************************************************************************************/
static void gpt_calculate_duty_cycle (gpt_instance_ctrl_t * const p_instance_ctrl,
                                      uint32_t const              duty_cycle_counts,
                                      gpt_prv_duty_registers_t  * p_duty_reg,
                                      uint32_t                    pin)
{
    /* Determine the current period. The actual period is one cycle longer than the register value for saw waves
     * and twice the register value for triangle waves. Reference section 23.2.21 "General PWM Timer Cycle Setting
     * Register (GTPBR)". The setting passed to the configuration is expected to be half the desired duty cycle for
     * triangle waves. */
    uint32_t current_period = p_instance_ctrl->p_reg->GTPBR;
 #if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (p_instance_ctrl->p_cfg->mode < TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
 #endif
    {
        current_period++;
    }

    bool duty_zero = (0U == duty_cycle_counts);
    bool duty_high = (duty_cycle_counts >= current_period);

    if (duty_zero || duty_high)
    {
        uint32_t gtior;

        if (!(GPT_IO_PIN_GTIOCB & pin))
        {
            gtior = p_instance_ctrl->p_reg->GTIOR_b.GTIOA;
        }
        else
        {
            gtior = p_instance_ctrl->p_reg->GTIOR_b.GTIOB;
        }

        bool first_level_low;

        if (p_instance_ctrl->p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
        {
            /* In triangle PWM modes use the initial pin level to determine 0%/100% setting. */
            first_level_low = !(gtior & 0x10);
        }
        else
        {
            /* In normal PWM mode use the cycle end setting to determine 0%/100% setting */
            first_level_low = (gtior & 0xC) == 0x4;
        }

        if ((duty_zero && !first_level_low) || (duty_high && first_level_low))
        {
            p_duty_reg->omdty = GPT_DUTY_CYCLE_MODE_0_PERCENT;
        }
        else
        {
            p_duty_reg->omdty = GPT_DUTY_CYCLE_MODE_100_PERCENT;
        }
    }
    else
    {
        uint32_t temp_duty_cycle = duty_cycle_counts;

 #if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
        if (p_instance_ctrl->p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
        {
            p_duty_reg->gtccr_buffer = temp_duty_cycle;
        }
        else
 #endif
        {
            /* The GTIOCA/GTIOCB pins transition 1 cycle after compare match when buffer operation is used. Reference
             * Figure 23.34 "Example setting for saw-wave PWM mode" in the RA6M3 manual R01UH0886EJ0100. */
            temp_duty_cycle--;
            p_duty_reg->gtccr_buffer = temp_duty_cycle;
        }
    }
}

#endif

/*******************************************************************************************************************//**
 * Calculates clock frequency of GPT counter.  Divides GPT clock by GPT clock divisor.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 *
 * @return     Clock frequency of the GPT counter.
 **********************************************************************************************************************/
static uint32_t gpt_clock_frequency_get (gpt_instance_ctrl_t * const p_instance_ctrl)
{
    /* Look up PCLKD frequency and divide it by GPT PCLKD divider. */
    timer_source_div_t pclk_divisor =
        (timer_source_div_t) (p_instance_ctrl->p_reg->GTCR_b.TPCS << BSP_FEATURE_GPT_TPCS_SHIFT);
    uint32_t pclk_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD);

    return pclk_freq_hz >> pclk_divisor;
}

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Calculates GTIOR settings for given mode and stop level.
 *
 * @param[in]  p_instance_ctrl         Instance control block
 * @param[in]  p_cfg                   Timer configuration
 * @param[in]  level                   Output level after timer stops
 **********************************************************************************************************************/
static uint32_t gpt_gtior_calculate (timer_cfg_t const * const p_cfg, gpt_pin_level_t const stop_level)
{
    /* The stop level is used as both the initial level and the stop level. */
    uint32_t gtior = R_GPT0_GTIOR_OAE_Msk | ((uint32_t) stop_level << R_GPT0_GTIOR_OADFLT_Pos) |
                     ((uint32_t) stop_level << GPT_PRV_GTIOR_INITIAL_LEVEL_BIT);

    uint32_t gtion = GPT_PRV_GTIO_LOW_COMPARE_MATCH_HIGH_CYCLE_END;

    if (TIMER_MODE_PWM == p_cfg->mode)
    {
        /* Use default: GTIOn is high at cycle end, then low at compare match. */
    }

 #if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    else if (p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        gtion = GPT_PRV_GTIO_TOGGLE_COMPARE_MATCH;
    }
 #endif
    else if (TIMER_MODE_ONE_SHOT_PULSE == p_cfg->mode)
    {
        gtion = GPT_PRV_GTIO_TOGGLE_COMPARE_MATCH;
    }
    else
    {
        /* In one-shot mode, the output pin goes high after the first compare match (one cycle after the timer starts counting). */
        if (GPT_PIN_LEVEL_LOW == stop_level)
        {
            gtion = GPT_PRV_GTIO_HIGH_COMPARE_MATCH_LOW_CYCLE_END;
        }
    }

    gtior |= gtion;

    return gtior;
}

#endif

/*******************************************************************************************************************//**
 * Set compare match value from configure instance into corresponding compare match channel.
 **********************************************************************************************************************/
static void r_gpt_init_compare_match_channel (gpt_instance_ctrl_t * p_instance_ctrl)
{
    /* Save pointer to extended configuration structure. */
    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Set commpare match value for GTCCRAn if this channel is enabled. */
    if (GPT_PRV_COMPARE_MATCH_A_MASK & p_extend->compare_match_status)
    {
        /* As the counter counts from 0 to (period - 1), the compare match value from user's input should be minus
         * one. */
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRA] = p_extend->compare_match_value[0] - 1U;
    }

    /* Set commpare match value for GTCCRBn if this channel is enabled. */
    if (GPT_PRV_COMPARE_MATCH_B_MASK & p_extend->compare_match_status)
    {
        /* As the counter counts from 0 to (period - 1), the compare match value from user's input should be minus
         * one. */
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRB] = p_extend->compare_match_value[1] - 1U;
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to GPT instance control block
 * @param[in]     event      Event code
 * @param[in]     capture    Event capture counts (if applicable)
 **********************************************************************************************************************/
static void r_gpt_call_callback (gpt_instance_ctrl_t * p_ctrl, timer_event_t event, uint32_t capture)
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

    p_args->event     = event;
    p_args->capture   = capture;
    p_args->p_context = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        gpt_prv_ns_callback p_callback = (gpt_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Common processing for input capture interrupt.
 *
 * @param[in]  event  Which input capture event occurred
 **********************************************************************************************************************/
static void r_gpt_ccmp_common_isr (gpt_prv_capture_event_t event)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    gpt_extended_cfg_t  * p_extend        = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint32_t      counter    = 0U;
    timer_event_t event_base = TIMER_EVENT_COMPARE_A;

    /* Identify whether capture or compare match is in use */
    if (!p_extend->compare_match_status)
    {
        /* If both compare match equal to 0 which mean capture operation is in use. Update the captured value and send
         * back to user. */
        counter    = p_instance_ctrl->p_reg->GTCCR[event];
        event_base = TIMER_EVENT_CAPTURE_A;
    }

    timer_event_t callback_event = (timer_event_t) ((uint32_t) event_base + (uint32_t) event);

    /* If we captured a one-shot pulse, then disable future captures. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        /* Disable captures. */
        gpt_hardware_events_disable(p_instance_ctrl);

        /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
        R_BSP_IrqClearPending(irq);
    }

    /* If a callback is provided, then call it with the captured counter value. */
    if (NULL != p_instance_ctrl->p_callback)
    {
        r_gpt_call_callback(p_instance_ctrl, callback_event, counter);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Stops the timer if one-shot mode, clears interrupts, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void gpt_counter_overflow_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* If one-shot mode is selected, stop the timer since period has expired. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        uint32_t wp = r_gpt_write_protect_disable(p_instance_ctrl);

        p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

        /* Clear the GPT counter and the overflow flag after the one shot pulse has being generated */
        p_instance_ctrl->p_reg->GTCNT                 = 0;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRA] = 0;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRB] = 0;

        r_gpt_write_protect_enable(p_instance_ctrl, wp | GPT_PRV_GTWP_RESET_VALUE);

        /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
        R_BSP_IrqClearPending(irq);
    }

    if (NULL != p_instance_ctrl->p_callback)
    {
        r_gpt_call_callback(p_instance_ctrl, TIMER_EVENT_CYCLE_END, 0);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Only supported for asymmetric triangle-wave PWM. Notifies application of trough event.
 **********************************************************************************************************************/
void gpt_counter_underflow_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Call user callback. */
    r_gpt_call_callback(p_instance_ctrl, TIMER_EVENT_TROUGH, 0);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture A source.
 *
 * Clears interrupt, disables captures if one-shot mode, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void gpt_capture_compare_a_isr (void)
{
    r_gpt_ccmp_common_isr(GPT_PRV_CAPTURE_EVENT_A);
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture B source.
 *
 * Clears interrupt, disables captures if one-shot mode, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void gpt_capture_compare_b_isr (void)
{
    r_gpt_ccmp_common_isr(GPT_PRV_CAPTURE_EVENT_B);
}
