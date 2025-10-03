/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rtc.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RTC_MASK_MSB                       (0x0F)
#define RTC_MASK_LSB                       (0xF0)

#define RTC_FIRST_DAY_OF_A_MONTH           (1)

/* Day of week : valid range between 0 to 6. */
#define RTC_DAYS_IN_A_WEEK                 (6)

/* Month : valid range between 0 to 11.*/
#define RTC_MONTHS_IN_A_YEAR               (11)
#define RTC_LAST_DAY_OF_LEAP_FEB_MONTH     (29)
#define RTC_LAST_DAY_OF_A_MONTH            (31)
#define RTC_YEAR_VALUE_MIN                 (100)
#define RTC_YEAR_VALUE_MAX                 (199)

/* Seconds : valid range between 0 to 59.*/
#define RTC_SECONDS_IN_A_MINUTE            (59)

/* Minute : valid range between 0 to 59. */
#define RTC_MINUTES_IN_A_HOUR              (59)

/* Hours : valid range between 0 to 23. */
#define RTC_HOURS_IN_A_DAY                 (23)

/* In Zeller algorithm value of (-[Y/100] + [Y/400]) is 15 for Y = 2000 to Y = 2099) */
#define RTC_ZELLER_ALGM_CONST_FIFTEEN      (15)

/* Macro definitions for February and March months */
#define RTC_FEBRUARY_MONTH                 (2U)
#define RTC_MARCH_MONTH                    (3U)

#define RTC_TIME_H_MONTH_OFFSET            (1)

/*The RTC has a 100 year calendar to match the starting year 2000, year offset(1900) is added like 117 + 1900 = 2017 */
#define RTC_TIME_H_YEAR_OFFSET             (1900)

/** "RTC" in ASCII, used to determine if device is open. */
#define RTC_OPEN                           (0x00525443ULL)

#if BSP_FEATURE_RTC_HAS_RADJ_ADJ6
 #define RTC_MAX_ERROR_ADJUSTMENT_VALUE    (0x7FU)
 #define RTC_MAX_ADJ_VALUE                 (0x3FU)
 #define RTC_ADJ6_ADJUSTMENT_VALUE         (0x40U)
#else
 #define RTC_MAX_ERROR_ADJUSTMENT_VALUE    (0x3FU)
#endif

#define RTC_RHRCNT_HOUR_MASK               (0x3f)
#define RTC_COMPARE_ENB_BIT                (7U)
#define RTC_MASK_8TH_BIT                   (0x7F)

/* As per HW manual, value of Year is between 0 to 99, the RTC has a 100 year calendar from 2000 to 2099.
 * But as per C standards, tm_year is years since 1900.*/
#define RTC_C_TIME_OFFSET                  (100)

/* See section 26.2.20 Frequency Register (RFRH/RFRL)" of the RA6M3 manual R01UH0886EJ0100) */
#define RTC_RFRL_MIN_VALUE_LOCO            (0x7U)
#define RTC_RFRL_MAX_VALUE_LOCO            (0x1FFU)

#define RTC_ALARM_REG_SIZE                 (0x20)

#define BSP_DELAY_US_PER_SECOND            (1000000)
#define NOISE_FILTER_SET_NUMBER_DELAY      (3)
#define NOISE_FILTER_CLOCK_DIVIDE_1        (1)
#define NOISE_FILTER_CLOCK_DIVIDE_32       (32)
#define NOISE_FILTER_CLOCK_DIVIDE_4096     (4096)
#define NOISE_FILTER_CLOCK_DIVIDE_8192     (8192)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * rtc_prv_ns_callback)(rtc_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile rtc_prv_ns_callback)(rtc_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static uint8_t rtc_dec_to_bcd(uint8_t to_convert);
static uint8_t rtc_bcd_to_dec(uint8_t to_convert);
void           rtc_alarm_periodic_isr(void);
void           rtc_carry_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** RTC Implementation of Real Time Clock  */
const rtc_api_t g_rtc_on_rtc =
{
    .open               = R_RTC_Open,
    .close              = R_RTC_Close,
    .clockSourceSet     = R_RTC_ClockSourceSet,
    .calendarTimeGet    = R_RTC_CalendarTimeGet,
    .calendarTimeSet    = R_RTC_CalendarTimeSet,
    .calendarAlarmGet   = R_RTC_CalendarAlarmGet,
    .calendarAlarmSet   = R_RTC_CalendarAlarmSet,
    .periodicIrqRateSet = R_RTC_PeriodicIrqRateSet,
    .infoGet            = R_RTC_InfoGet,
    .errorAdjustmentSet = R_RTC_ErrorAdjustmentSet,
    .callbackSet        = R_RTC_CallbackSet,
    .timeCaptureSet     = R_RTC_TimeCaptureSet,
    .timeCaptureGet     = R_RTC_TimeCaptureGet,
};

#if RTC_CFG_PARAM_CHECKING_ENABLE

/* Number of days in each months start from January to December */
static const uint8_t days_in_months[12] = {31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};
#endif

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

static void r_rtc_set_clock_source(rtc_instance_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg);

static void r_rtc_start_bit_update(uint8_t value);

static void r_rtc_software_reset(void);

static void r_rtc_config_rtc_interrupts(rtc_instance_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg);

static void r_rtc_irq_set(bool irq_enable_flag, uint8_t mask);

static void r_rtc_call_callback(rtc_instance_ctrl_t * p_ctrl, rtc_event_t event);

#if RTC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_rtc_rfrl_validate(uint32_t value);

static fsp_err_t r_rtc_err_adjustment_parameter_check(rtc_error_adjustment_cfg_t const * const err_adj_cfg);

static fsp_err_t r_rtc_time_and_date_validate(rtc_time_t * const p_time);

static fsp_err_t r_rtc_time_validate(rtc_time_t * const p_time);

static fsp_err_t r_rtc_date_validate(rtc_time_t * const p_time);

static fsp_err_t r_rtc_alarm_time_and_date_validate(rtc_alarm_time_t * const p_time);

static fsp_err_t r_rtc_alarm_time_validate(rtc_alarm_time_t * const p_time);

static fsp_err_t r_rtc_alarm_month_and_year_validate(rtc_alarm_time_t * const p_time);

static fsp_err_t r_rtc_alarm_dayofmonth_and_dayofweek_validate(rtc_alarm_time_t * const p_time);

#endif

static void r_rtc_error_adjustment_set(rtc_error_adjustment_cfg_t const * const err_adj_cfg);

/*******************************************************************************************************************//**
 * @addtogroup RTC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens and configures the RTC driver module. Implements @ref rtc_api_t::open.
 * Configuration includes clock source, and interrupt callback function.
 *
 * Example:
 * @snippet r_rtc_example.c R_RTC_Open
 *
 * @retval FSP_SUCCESS              Initialization was successful and RTC has started.
 * @retval FSP_ERR_ASSERTION        Invalid p_ctrl or p_cfg pointer.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid time parameter field.
 **********************************************************************************************************************/
fsp_err_t R_RTC_Open (rtc_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;

    /* Parameter checking */
#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(RTC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Save the configuration  */
    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

#if RTC_CFG_PARAM_CHECKING_ENABLE

    /* IRTC only use Subclock */
 #if BSP_FEATURE_RTC_IS_IRTC
    FSP_ERROR_RETURN(RTC_CLOCK_SOURCE_SUBCLK == p_cfg->clock_source, FSP_ERR_INVALID_ARGUMENT);
 #endif

    /* Verify the frequency comparison value for RFRL when using LOCO */
    if (RTC_CLOCK_SOURCE_LOCO == p_cfg->clock_source)
    {
        FSP_ERROR_RETURN(FSP_SUCCESS == r_rtc_rfrl_validate(p_cfg->freq_compare_value), FSP_ERR_INVALID_ARGUMENT);
    }
    /* Validate the error adjustment parameters when using SubClock */
    else
    {
        FSP_ERROR_RETURN(FSP_SUCCESS == r_rtc_err_adjustment_parameter_check(p_instance_ctrl->p_cfg->p_err_cfg),
                         FSP_ERR_INVALID_ARGUMENT);
    }
#endif

#if BSP_FEATURE_LPM_RTC_REGISTER_CLOCK_DISABLE

    /* Enable the RTC Register Read/Write clock if it was disabled in startup. */
    bsp_prv_rtc_register_clock_set(true);
#endif

    p_instance_ctrl->carry_isr_triggered = false;

#if RTC_CFG_OPEN_SET_CLOCK_SOURCE

    /* Set the clock source for RTC.
     * The count source must be selected only once before making the initial settings of the RTC registers
     * at power on. (see section 26.2.19 RTC Control Register 4 (RCR4) of the RA6M3 manual R01UH0886EJ0100)*/
    r_rtc_set_clock_source(p_instance_ctrl, p_cfg);
#endif

    r_rtc_config_rtc_interrupts(p_instance_ctrl, p_cfg);

    /** Mark driver as open by initializing it to "RTC" in its ASCII equivalent. */
    p_instance_ctrl->open = RTC_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Close the RTC driver.
 * Implements @ref rtc_api_t::close
 *
 * @retval FSP_SUCCESS          De-Initialization was successful and RTC driver closed.
 * @retval FSP_ERR_ASSERTION    Invalid p_ctrl.
 * @retval FSP_ERR_NOT_OPEN     Driver not open already for close.
 **********************************************************************************************************************/
fsp_err_t R_RTC_Close (rtc_ctrl_t * const p_ctrl)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear PIE, AIE, CIE*/
    R_RTC->RCR1 = 0U;

    /* When the RCR1 register is modified, check that all the bits are updated before proceeding
     * (see section 26.2.17 "RTC Control Register 1 (RCR1)" of the RA6M3 manual R01UH0886EJ0100)*/
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR1, 0);

    /* Set the START bit to 0 */
    r_rtc_start_bit_update(0U);

    if (p_instance_ctrl->p_cfg->periodic_irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->periodic_irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->periodic_irq, NULL);
    }

    if (p_instance_ctrl->p_cfg->alarm_irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->alarm_irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->alarm_irq, NULL);
    }

#if BSP_FEATURE_RTC_HAS_ALARM1
    if (((rtc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->alarm1_irq >= 0)
    {
        R_BSP_IrqDisable(((rtc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->alarm1_irq);
        R_FSP_IsrContextSet(((rtc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->alarm1_irq, NULL);
    }
#endif
    if (p_instance_ctrl->p_cfg->carry_irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->carry_irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->carry_irq, NULL);
    }

#if BSP_FEATURE_LPM_RTC_REGISTER_CLOCK_DISABLE

    /* Disable the RTC Register Read/Write clock. */
    bsp_prv_rtc_register_clock_set(false);
#endif

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the RTC clock source. Implements @ref rtc_api_t::clockSourceSet.
 *
 * Example:
 * @snippet r_rtc_example.c R_RTC_ClockSourceSet
 *
 * @retval FSP_SUCCESS              Initialization was successful and RTC has started.
 * @retval FSP_ERR_ASSERTION        Invalid p_ctrl or p_cfg pointer.
 * @retval FSP_ERR_NOT_OPEN         Driver is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid clock source.
 **********************************************************************************************************************/
fsp_err_t R_RTC_ClockSourceSet (rtc_ctrl_t * const p_ctrl)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #if BSP_FEATURE_RTC_IS_IRTC
    FSP_ERROR_RETURN(RTC_CLOCK_SOURCE_SUBCLK == p_instance_ctrl->p_cfg->clock_source, FSP_ERR_INVALID_ARGUMENT);
 #endif
#endif

    /* Set the clock source for RTC.
     * The count source must be selected only once before making the initial settings of the RTC registers
     * at power on. (see section 26.2.19 RTC Control Register 4 (RCR4) of the RA6M3 manual R01UH0886EJ0100)*/
    r_rtc_set_clock_source(p_instance_ctrl, p_instance_ctrl->p_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the calendar time.
 *
 * Implements @ref rtc_api_t::calendarTimeSet.
 *
 * @retval FSP_SUCCESS              Calendar time set operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid time parameter field.
 **********************************************************************************************************************/
fsp_err_t R_RTC_CalendarTimeSet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time)
{
    fsp_err_t             err             = FSP_SUCCESS;
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(p_time);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Verify the seconds, minutes, hours, year ,day of the week, day of the month, month and year are valid values */
    FSP_ERROR_RETURN(FSP_SUCCESS == r_rtc_time_and_date_validate(p_time), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* See section "26.3.3 Setting the Time" of the RA6M3 manual R01UH0886EJ0100 for steps to set the time and error
     * adjustment value */

    /* Set the START bit to 0 */
    r_rtc_start_bit_update(0U);

    /* Set the year, month, day of the week, ... */
    R_RTC->RSECCNT = rtc_dec_to_bcd((uint8_t) p_time->tm_sec);
    R_RTC->RMINCNT = rtc_dec_to_bcd((uint8_t) p_time->tm_min);
    R_RTC->RHRCNT  = rtc_dec_to_bcd((uint8_t) p_time->tm_hour) & RTC_RHRCNT_HOUR_MASK;
    R_RTC->RWKCNT  = rtc_dec_to_bcd((uint8_t) p_time->tm_wday);
    R_RTC->RDAYCNT = rtc_dec_to_bcd((uint8_t) p_time->tm_mday);

    /* Add one to match with HW register */
    R_RTC->RMONCNT = rtc_dec_to_bcd((uint8_t) (p_time->tm_mon + 1));

    /* Subtract 100 to match with HW register */
    R_RTC->RYRCNT = rtc_dec_to_bcd((uint8_t) (p_time->tm_year - RTC_C_TIME_OFFSET));

    if (RTC_CLOCK_SOURCE_SUBCLK == p_instance_ctrl->p_cfg->clock_source)
    {
        /* Set Error Adjustment values */
        r_rtc_error_adjustment_set(p_instance_ctrl->p_cfg->p_err_cfg);
    }

    /* Set the START bit to 1 */
    r_rtc_start_bit_update(1U);

    return err;
}

/*******************************************************************************************************************//**
 * Get the calendar time.
 * @warning Do not call this function from a critical section or from an interrupt with higher priority than the carry
 * interrupt, or the time returned may be inaccurate.
 *
 * Implements @ref rtc_api_t::calendarTimeGet
 *
 * @retval FSP_SUCCESS              Calendar time get operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 * @retval FSP_ERR_IRQ_BSP_DISABLED User IRQ parameter not valid
 **********************************************************************************************************************/
fsp_err_t R_RTC_CalendarTimeGet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(p_time);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->p_cfg->carry_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    fsp_err_t err = FSP_SUCCESS;

    uint32_t carry_irq_status = NVIC_GetEnableIRQ(p_instance_ctrl->p_cfg->carry_irq);

    if ((uint32_t) 0U == carry_irq_status)
    {
        r_rtc_irq_set(true, R_RTC_RCR1_CIE_Msk);
        R_BSP_IrqEnable(p_instance_ctrl->p_cfg->carry_irq);
    }

    /* If a carry occurs while the 64-Hz counter and time are being read, the correct time is not obtained,
     * therefore they must be read again. 26.3.5 "Reading 64-Hz Counter and Time" of the RA6M3 manual R01UH0886EJ0100)*/
    do
    {
        p_instance_ctrl->carry_isr_triggered = false; /** This flag will be set to 'true' in the carry ISR */
        p_time->tm_sec  = (int32_t) rtc_bcd_to_dec(R_RTC->RSECCNT);
        p_time->tm_min  = (int32_t) rtc_bcd_to_dec(R_RTC->RMINCNT);
        p_time->tm_hour = (int32_t) rtc_bcd_to_dec(R_RTC->RHRCNT & RTC_RHRCNT_HOUR_MASK);
        p_time->tm_wday = (int32_t) rtc_bcd_to_dec(R_RTC->RWKCNT);
        p_time->tm_mday = (int32_t) rtc_bcd_to_dec(R_RTC->RDAYCNT);

        /* Subtract one to match with C time.h standards */
        p_time->tm_mon = (int32_t) rtc_bcd_to_dec(R_RTC->RMONCNT) - 1;

        /* Add 100 to match with C time.h standards */
        p_time->tm_year = (int32_t) rtc_bcd_to_dec((uint8_t) R_RTC->RYRCNT) + RTC_C_TIME_OFFSET;
    } while (p_instance_ctrl->carry_isr_triggered);

    /** Restore the state of carry IRQ. */
    if ((uint32_t) 0U == carry_irq_status)
    {
        r_rtc_irq_set(false, R_RTC_RCR1_CIE_Msk);

        /* Disable this interrupt in the NVIC */
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->carry_irq);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Set the calendar alarm time.
 *
 * Implements @ref rtc_api_t::calendarAlarmSet.
 *
 * @pre The calendar counter must be running before the alarm can be set.
 *
 * @retval FSP_SUCCESS              Calendar alarm time set operation was successful.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid time parameter field.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 * @retval FSP_ERR_IRQ_BSP_DISABLED User IRQ parameter not valid
 **********************************************************************************************************************/
fsp_err_t R_RTC_CalendarAlarmSet (rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_alarm);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #if BSP_FEATURE_RTC_HAS_ALARM1
    FSP_ERROR_RETURN((p_alarm->channel == RTC_ALARM_CHANNEL_0 && p_instance_ctrl->p_cfg->alarm_irq >= 0) ||
                     (p_alarm->channel == RTC_ALARM_CHANNEL_1 &&
                      ((rtc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->alarm1_irq >= 0),
                     FSP_ERR_IRQ_BSP_DISABLED);
 #else
    FSP_ERROR_RETURN(p_instance_ctrl->p_cfg->alarm_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
 #endif

    /* Verify the seconds, minutes, hours, year ,day of the week, day of the month and month are valid values */
    FSP_ERROR_RETURN(FSP_SUCCESS == r_rtc_alarm_time_and_date_validate(p_alarm), FSP_ERR_INVALID_ARGUMENT);
#endif

    volatile uint8_t  * p_reg;
    volatile uint16_t * p_reg_ryrar;

    IRQn_Type           alarm_irq     = p_instance_ctrl->p_cfg->alarm_irq;
    rtc_alarm_channel_t alarm_channel = RTC_ALARM_CHANNEL_0;

#if BSP_FEATURE_RTC_HAS_ALARM1
    alarm_channel = p_alarm->channel;
    if (RTC_ALARM_CHANNEL_1 == alarm_channel)
    {
        alarm_irq = ((rtc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->alarm1_irq;
    }
#endif

    /* Disable the ICU alarm interrupt request */
    R_BSP_IrqDisable(alarm_irq);

    /* Set alarm time */
    volatile uint8_t field;
    if (p_alarm->sec_match)
    {
        field = rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_sec) | (uint8_t) (p_alarm->sec_match << RTC_COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }

    p_reg  = &R_RTC->RSECAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    *p_reg = field;

    if (p_alarm->min_match)
    {
        field = rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_min) | (uint8_t) (p_alarm->min_match << RTC_COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }

    p_reg    = &R_RTC->RMINAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    (*p_reg) = field;

    if (p_alarm->hour_match)
    {
        field = rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_hour) |
                (uint8_t) (p_alarm->hour_match << RTC_COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }

    p_reg    = &R_RTC->RHRAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    (*p_reg) = field;

    if (p_alarm->dayofweek_match)
    {
        field = (uint8_t) p_alarm->time.tm_wday | (uint8_t) (p_alarm->dayofweek_match << RTC_COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }

    p_reg    = &R_RTC->RWKAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    (*p_reg) = field;

    if (p_alarm->mday_match)
    {
        field = rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_mday) |
                (uint8_t) (p_alarm->mday_match << RTC_COMPARE_ENB_BIT);
    }
    else
    {
        field = 1U;
    }

    p_reg    = &R_RTC->RDAYAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    (*p_reg) = field;

    if (p_alarm->mon_match)
    {
        /* Add one to month to match with HW register */
        field = rtc_dec_to_bcd((uint8_t) (p_alarm->time.tm_mon + 1)) |
                (uint8_t) (p_alarm->mon_match << RTC_COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }

    p_reg    = &R_RTC->RMONAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    (*p_reg) = field;

    if (p_alarm->year_match)
    {
        field = rtc_dec_to_bcd((uint8_t) (p_alarm->time.tm_year - RTC_C_TIME_OFFSET));
    }
    else
    {
        field = 0U;
    }

    /*It is a pointer to uint16_t so the offset needs to be halved */
    p_reg_ryrar    = &R_RTC->RYRAR + (RTC_ALARM_REG_SIZE * alarm_channel) / 2;
    (*p_reg_ryrar) = field;

    p_reg    = &R_RTC->RYRAREN + (RTC_ALARM_REG_SIZE * alarm_channel);
    (*p_reg) = (uint8_t) (p_alarm->year_match << R_RTC_RYRAREN_ENB_Pos);

    /* Enable the alarm interrupt */
    r_rtc_irq_set(true, R_RTC_RCR1_AIE_Msk);

    R_BSP_IrqEnable(alarm_irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the calendar alarm time.
 *
 * Implements @ref rtc_api_t::calendarAlarmGet
 *
 * @retval FSP_SUCCESS           Calendar alarm time get operation was successful.
 * @retval FSP_ERR_ASSERTION     Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN      Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_CalendarAlarmGet (rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm)
{
#if RTC_CFG_PARAM_CHECKING_ENABLE
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_alarm);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    volatile uint8_t  * p_reg;
    volatile uint16_t * p_reg_ryrar;
    uint8_t             reg_val;
    uint16_t            reg_ryrar_val;

    rtc_alarm_channel_t alarm_channel = RTC_ALARM_CHANNEL_0;

#if BSP_FEATURE_RTC_HAS_ALARM1
    alarm_channel = p_alarm->channel;
#endif

    p_reg                = &R_RTC->RSECAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    reg_val              = *p_reg;
    p_alarm->time.tm_sec = rtc_bcd_to_dec(reg_val & RTC_MASK_8TH_BIT);
    p_alarm->sec_match   = (bool) (reg_val & R_RTC_RSECAR_ENB_Msk);

    p_reg                = &R_RTC->RMINAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    reg_val              = *p_reg;
    p_alarm->time.tm_min = rtc_bcd_to_dec(reg_val & RTC_MASK_8TH_BIT);
    p_alarm->min_match   = (bool) (reg_val & R_RTC_RMINAR_ENB_Msk);

    p_reg                 = &R_RTC->RHRAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    reg_val               = *p_reg;
    p_alarm->time.tm_hour = rtc_bcd_to_dec(reg_val & RTC_MASK_8TH_BIT);
    p_alarm->hour_match   = (bool) (reg_val & R_RTC_RHRAR_ENB_Msk);

    p_reg                    = &R_RTC->RWKAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    reg_val                  = *p_reg;
    p_alarm->time.tm_wday    = rtc_bcd_to_dec(reg_val & RTC_MASK_8TH_BIT);
    p_alarm->dayofweek_match = (bool) (reg_val & R_RTC_RWKAR_ENB_Msk);

    p_reg                 = &R_RTC->RDAYAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    reg_val               = *p_reg;
    p_alarm->time.tm_mday = rtc_bcd_to_dec(reg_val & RTC_MASK_8TH_BIT);
    p_alarm->mday_match   = (bool) (reg_val & R_RTC_RDAYAR_ENB_Msk);

    /* Subtract one from month to match with C time.h standards */
    p_reg                = &R_RTC->RMONAR + (RTC_ALARM_REG_SIZE * alarm_channel);
    reg_val              = *p_reg;
    p_alarm->time.tm_mon = rtc_bcd_to_dec(reg_val & RTC_MASK_8TH_BIT) - (uint8_t) 1;
    p_alarm->mon_match   = (bool) (reg_val & R_RTC_RMONAR_ENB_Msk);

    /*It is a pointer to uint16_t so the offset needs to be halved */
    p_reg_ryrar   = &R_RTC->RYRAR + (RTC_ALARM_REG_SIZE * alarm_channel) / 2;
    reg_ryrar_val = *p_reg_ryrar;

    /* Add 100 to the year to match with C time.h standards */
    p_alarm->time.tm_year = rtc_bcd_to_dec((uint8_t) reg_ryrar_val) + (uint8_t) RTC_C_TIME_OFFSET;

    p_reg               = &R_RTC->RYRAREN + (RTC_ALARM_REG_SIZE * alarm_channel);
    reg_val             = *p_reg;
    p_alarm->year_match = (bool) (reg_val & R_RTC_RYRAREN_ENB_Msk);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the periodic interrupt rate and enable periodic interrupt.
 *
 * Implements @ref rtc_api_t::periodicIrqRateSet
 *
 * @note To start the RTC @ref R_RTC_CalendarTimeSet must be called at least once.
 *
 * Example:
 * @snippet r_rtc_example.c R_RTC_PeriodicIrqRateSet
 *
 * @retval FSP_SUCCESS               The periodic interrupt rate was successfully set.
 * @retval FSP_ERR_ASSERTION         Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN          Driver not open already for operation.
 * @retval FSP_ERR_IRQ_BSP_DISABLED  User IRQ parameter not valid
 **********************************************************************************************************************/
fsp_err_t R_RTC_PeriodicIrqRateSet (rtc_ctrl_t * const p_ctrl, rtc_periodic_irq_select_t const rate)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->p_cfg->periodic_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
#endif
    fsp_err_t err = FSP_SUCCESS;

    uint8_t rcr1 = R_RTC->RCR1;
    rcr1       &= (uint8_t) ~R_RTC_RCR1_PES_Msk;
    R_RTC->RCR1 = (uint8_t) (rcr1 | (rate << R_RTC_RCR1_PES_Pos));

    /* When the RCR1 register is modified, check that all the bits are updated before proceeding
     * (see section 26.2.17 "RTC Control Register 1 (RCR1)" of the RA6M3 manual R01UH0886EJ0100)*/
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR1 >> R_RTC_RCR1_PES_Pos, rate);

    r_rtc_irq_set(true, R_RTC_RCR1_PIE_Msk);

    R_BSP_IrqEnable(p_instance_ctrl->p_cfg->periodic_irq);

    return err;
}

/*******************************************************************************************************************//**
 * Set RTC clock source and running status information ad store it in provided pointer p_rtc_info
 *
 * Implements @ref rtc_api_t::infoGet
 *
 * @retval FSP_SUCCESS          Get information Successful.
 * @retval FSP_ERR_ASSERTION    Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN     Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_InfoGet (rtc_ctrl_t * const p_ctrl, rtc_info_t * const p_rtc_info)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_rtc_info);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_rtc_info->clock_source = p_instance_ctrl->p_cfg->clock_source;
    p_rtc_info->status       = (rtc_status_t) R_RTC->RCR2_b.START;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function sets time error adjustment
 *
 * Implements @ref rtc_api_t::errorAdjustmentSet
 *
 * @retval FSP_SUCCESS                 Time error adjustment successful.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Driver not open for operation.
 * @retval FSP_ERR_UNSUPPORTED         The clock source is not sub-clock.
 * @retval FSP_ERR_INVALID_ARGUMENT    Invalid error adjustment value.
 **********************************************************************************************************************/
fsp_err_t R_RTC_ErrorAdjustmentSet (rtc_ctrl_t * const p_ctrl, rtc_error_adjustment_cfg_t const * const err_adj_cfg)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Error adjustment is supported only if clock source is sub-clock */
    if (p_instance_ctrl->p_cfg->clock_source != RTC_CLOCK_SOURCE_SUBCLK)
    {
        return FSP_ERR_UNSUPPORTED;
    }

    /* Verify the frequecy comparison valure for RFRL when using LOCO */
    FSP_ERROR_RETURN(FSP_SUCCESS == r_rtc_err_adjustment_parameter_check(err_adj_cfg), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Set Error Adjustment values */
    r_rtc_error_adjustment_set(err_adj_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements rtc_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to RTC control block is NULL or the RTC is not configured to use the
 *                                       internal clock.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_RTC_CallbackSet (rtc_ctrl_t * const          p_ctrl,
                             void (                    * p_callback)(rtc_callback_args_t *),
                             void * const                p_context,
                             rtc_callback_args_t * const p_callback_memory)
{
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;

#if (RTC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if RTC_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    rtc_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(rtc_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set time capture configuration for the provided channel.
 *
 * Implements @ref rtc_api_t::timeCaptureSet
 *
 * @note Updating capture settings requires significant software delay. Timing considerations should be carefully
 * considered when calling this function.
 *
 * @retval FSP_SUCCESS                 Setting for Time capture was successful.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Driver not open already for operation.
 * @retval FSP_ERR_INVALID_CHANNEL     Invalid input channel set.
 * @retval FSP_ERR_UNSUPPORTED         Hardware not support this feature.
 **********************************************************************************************************************/
fsp_err_t R_RTC_TimeCaptureSet (rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture)
{
#if BSP_FEATURE_RTC_HAS_ALARM1
 #if (RTC_CFG_PARAM_CHECKING_ENABLE)
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time_capture);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_RTC_RTCCR_CHANNELS > p_time_capture->channel, FSP_ERR_INVALID_CHANNEL);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Clear config, set TCEN bit before set other bit. */
    R_RTC->RTCCR[p_time_capture->channel].RTCCR = R_RTC_RTCCR_RTCCR_TCEN_Msk;

    /* When RTCCRn is modified, check that all the bits except the TCST bit are updated before continuing with
     * additional processing. (see section 23.2.27 "RTCCRn : Time Capture Control Register n (n = 0 to 2)" of the
     * manual R01UH1005EJ0100) */
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RTCCR[p_time_capture->channel].RTCCR, (uint8_t) R_RTC_RTCCR_RTCCR_TCEN_Msk);

    R_RTC->RTCCR[p_time_capture->channel].RTCCR |=
        (uint8_t) (p_time_capture->noise_filter << R_RTC_RTCCR_RTCCR_TCNF_Pos);

    /* When the noise filter is used, set the TCNF[2:0] bits,wait for 3 cycles of the specified sampling period (see
     * section 23.2.27 "RTCCRn : Time Capture Control Register n (n = 0 to 2)" of the  manual R01UH1005EJ0100) */
    uint32_t noise_filter_delay_us = 0;
    switch (p_time_capture->noise_filter)
    {
        case RTC_TIME_CAPTURE_NOISE_FILTER_ON_DIVIDER_32:
        {
            noise_filter_delay_us = BSP_DELAY_US_PER_SECOND * (NOISE_FILTER_CLOCK_DIVIDE_32 / BSP_SUBCLOCK_FREQ_HZ);
            break;
        }

        case RTC_TIME_CAPTURE_NOISE_FILTER_ON_DIVIDER_4096:
        {
            noise_filter_delay_us = BSP_DELAY_US_PER_SECOND * (NOISE_FILTER_CLOCK_DIVIDE_4096 / BSP_SUBCLOCK_FREQ_HZ);
            break;
        }

        case RTC_TIME_CAPTURE_NOISE_FILTER_ON_DIVIDER_8192:
        {
            noise_filter_delay_us = BSP_DELAY_US_PER_SECOND * (NOISE_FILTER_CLOCK_DIVIDE_8192 / BSP_SUBCLOCK_FREQ_HZ);
            break;
        }

        default:
        {
            noise_filter_delay_us = BSP_DELAY_US_PER_SECOND * (NOISE_FILTER_CLOCK_DIVIDE_1 / BSP_SUBCLOCK_FREQ_HZ);
            break;
        }
    }

    R_BSP_SoftwareDelay(NOISE_FILTER_SET_NUMBER_DELAY * noise_filter_delay_us, BSP_DELAY_UNITS_MICROSECONDS);

    /* When RTCCRn is modified, check that all the bits except the TCST bit are updated before continuing with
     * additional processing. (see section 23.2.27 "RTCCRn : Time Capture Control Register n (n = 0 to 2)" of the
     * manual R01UH1005EJ0100) */
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RTCCR[p_time_capture->channel].RTCCR_b.TCNF,
                               (uint8_t) p_time_capture->noise_filter);

    R_RTC->RTCCR[p_time_capture->channel].RTCCR |= (uint8_t) (p_time_capture->source << R_RTC_RTCCR_RTCCR_TCCT_Pos);

    /* When RTCCRn is modified, check that all the bits except the TCST bit are updated before continuing with
     * additional processing. (see section 23.2.27 "RTCCRn : Time Capture Control Register n (n = 0 to 2)" of the
     * manual R01UH1005EJ0100) */
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RTCCR[p_time_capture->channel].RTCCR_b.TCCT, (uint8_t) p_time_capture->source);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_time_capture);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Get time capture value of the provided channel.
 *
 * Implements @ref rtc_api_t::timeCaptureGet
 *
 * @retval FSP_SUCCESS                 Get time capture successful.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Driver not open already for operation.
 * @retval FSP_ERR_INVALID_CHANNEL     Invalid input channel get.
 * @retval FSP_ERR_INVALID_STATE       Invalid operation state.
 * @retval FSP_ERR_UNSUPPORTED         Hardware not support this feature.
 **********************************************************************************************************************/
fsp_err_t R_RTC_TimeCaptureGet (rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture)
{
#if BSP_FEATURE_RTC_HAS_ALARM1
 #if (RTC_CFG_PARAM_CHECKING_ENABLE)
    rtc_instance_ctrl_t * p_instance_ctrl = (rtc_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time_capture);
    FSP_ERROR_RETURN(RTC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_RTC_RTCCR_CHANNELS > p_time_capture->channel, FSP_ERR_INVALID_CHANNEL);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* The event is detected only during count operation (RCR2.START bit = 1). Before reading the capture register,
     * make sure that this bit is set to 1. */
    FSP_ERROR_RETURN(R_RTC->RCR2_b.START == 1U, FSP_ERR_INVALID_STATE);

    /* Capture event detected */
    FSP_ERROR_RETURN(R_RTC->RTCCR[p_time_capture->channel].RTCCR_b.TCST == 1U, FSP_ERR_INVALID_STATE);

    /* Get configuration of capture source and noise filter */
    p_time_capture->source       = (rtc_time_capture_source_t) R_RTC->RTCCR[p_time_capture->channel].RTCCR_b.TCCT;
    p_time_capture->noise_filter = (rtc_time_capture_noise_filter_t) R_RTC->RTCCR[p_time_capture->channel].RTCCR_b.TCNF;

    /* Before reading from this register, the time capture event detection should be stopped using the RTCCRn.TCCT[1:0]
     * bits.(see section 23.2.28 "RSECCPn : Second Capture Register n (n = 0 to 2) (in Calendar Count Mode)" of the
     *  manual r01uh1005ej0100 */
    uint8_t rtccr = R_RTC->RTCCR[p_time_capture->channel].RTCCR;
    R_RTC->RTCCR[p_time_capture->channel].RTCCR = rtccr & ((uint8_t) ~R_RTC_RTCCR_RTCCR_TCCT_Msk);

    /* When RTCCRn is modified, check that all the bits except the TCST bit are updated before continuing with
     * additional processing. (see section 23.2.27 "RTCCRn : Time Capture Control Register n (n = 0 to 2)" of the
     * manual R01UH1005EJ0100) */
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RTCCR[p_time_capture->channel].RTCCR,
                               (uint8_t) (rtccr & ((uint8_t) ~R_RTC_RTCCR_RTCCR_TCCT_Msk)));

    p_time_capture->time.tm_sec  = rtc_bcd_to_dec(R_RTC->CP[p_time_capture->channel].RSEC & RTC_MASK_8TH_BIT);
    p_time_capture->time.tm_min  = rtc_bcd_to_dec(R_RTC->CP[p_time_capture->channel].RMIN & RTC_MASK_8TH_BIT);
    p_time_capture->time.tm_hour = rtc_bcd_to_dec(R_RTC->CP[p_time_capture->channel].RHR & RTC_MASK_8TH_BIT);
    p_time_capture->time.tm_mday = rtc_bcd_to_dec(R_RTC->CP[p_time_capture->channel].RDAY & RTC_MASK_8TH_BIT);

    /* Subtract one from month to match with C time.h standards */
    p_time_capture->time.tm_mon = rtc_bcd_to_dec(R_RTC->CP[p_time_capture->channel].RMON & RTC_MASK_8TH_BIT) -
                                  (uint8_t) 1;

    /* Restore setting and clear Time capture status bit */
    R_RTC->RTCCR[p_time_capture->channel].RTCCR = rtccr & ((uint8_t) ~R_RTC_RTCCR_RTCCR_TCST_Msk);

    /* When RTCCRn is modified, check that all the bits except the TCST bit are updated before continuing with
     * additional processing. (see section 23.2.27 "RTCCRn : Time Capture Control Register n (n = 0 to 2)" of the
     * manual R01UH1005EJ0100) */
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RTCCR[p_time_capture->channel].RTCCR,
                               (uint8_t) (rtccr & ((uint8_t) ~R_RTC_RTCCR_RTCCR_TCST_Msk)));

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_time_capture);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @} (end addtpgroup RTC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Update the start bit
 *
 * @param[in]  value         Value to be updated
 **********************************************************************************************************************/
static void r_rtc_start_bit_update (uint8_t value)
{
    /* Set or Clear START bit in RCR2 register depending on the value */
    R_RTC->RCR2_b.START = value & 1U;

    /* The START bit is updated in synchronization with the next cycle of the count source. Check if the bit is updated
     * before proceeding (see section 26.2.18 "RTC Control Register 2 (RCR2)" of the RA6M3 manual R01UH0886EJ0100)*/
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2_b.START, value);
}

/*******************************************************************************************************************//**
 * Perform a software reset
 **********************************************************************************************************************/
static void r_rtc_software_reset (void)
{
    /* Set the RESET bit in the RCR2 register */
    R_RTC->RCR2_b.RESET = 1U;

    /* When 1 is written to this bit, initialization starts in synchronization with the count source. When the
     * initialization is completed, the RESET bit is automatically set to 0. Check that this bit is 0 before proceeding.
     * (see section 26.2.18 "RTC Control Register 2 (RCR2)" of the RA6M3 manual R01UH0886EJ0100)*/
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2_b.RESET, 0U);
}

/*******************************************************************************************************************//**
 * Set the RTC clock source
 *
 * @param[in]  p_ctrl                  Instance control block
 * @param[in]  p_cfg                   Pointer to rtc configuration.
 **********************************************************************************************************************/
static void r_rtc_set_clock_source (rtc_instance_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg)
{
    /* Select the count source (RCKSEL) */
    R_RTC->RCR4 = (uint8_t) p_ctrl->p_cfg->clock_source;

    /* Supply 6 clocks of the count source (LOCO/SOSC, 183us, 32kHZ).
     * See 26.3.2 "Clock and Count Mode Setting Procedure" of the RA6M3 manual R01UH0886EJ0100)*/
    R_BSP_SoftwareDelay(BSP_PRV_RTC_RESET_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);

    r_rtc_start_bit_update(0U);

    if (RTC_CLOCK_SOURCE_LOCO == p_ctrl->p_cfg->clock_source)
    {
        /* Write 0 before writing to the RFRL register after a cold start. (see section 26.2.20
         * Frequency Register (RFRH/RFRL)" of the RA6M3 manual R01UH0886EJ0100) */
        R_RTC->RFRH = 0;

        R_RTC->RFRL = (uint16_t) p_cfg->freq_compare_value;
    }

    R_RTC->RCR2 = 0;

    /* When setting the count mode, execute an RTC software reset and start again from the initial settings.
     * This bit is updated synchronously with the count source, and its value is fixed before the RTC software
     * reset is completed (see section 26.2.18 "RTC Control Register 2 (RCR2)" of the RA6M3 manual R01UH0886EJ0100)*/
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2_b.CNTMD, RTC_CALENDAR_MODE);

    r_rtc_software_reset();

    /* Disable RTC interrupts */
    R_RTC->RCR1 = 0;

    /* When the RCR1 register is modified, check that all the bits are updated before proceeding
     * (see section 26.2.17 "RTC Control Register 1 (RCR1)" of the RA6M3 manual R01UH0886EJ0100)*/
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR1, 0);

    /* Force RTC to 24 hour mode. Set HR24 bit in the RCR2 register */
    R_RTC->RCR2_b.HR24 = 1U;

    /*
     * See 23.6.5 "Notes on Writing to and Reading from Registers" of the RA6M5 manual R01UH0891EJ0120.
     * The value written is reflected when fourth read operations are performed after writing.
     */
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2_b.HR24, 1);

#if BSP_FEATURE_RTC_HAS_TCEN
    for (uint8_t index = 0U; index < BSP_FEATURE_RTC_RTCCR_CHANNELS; index++)
    {
        /* RTCCRn.TCEN must be cleared after reset. */
        R_RTC->RTCCR[index].RTCCR_b.TCEN = 0U;
        FSP_HARDWARE_REGISTER_WAIT(R_RTC->RTCCR[index].RTCCR_b.TCEN, 0);
    }
#endif
}

/*******************************************************************************************************************//**
 * Set IRQ priority and control info for IRQ handler .
 *
 * @param[in]  p_ctrl                  Instance control block
 * @param[in]  p_cfg                   Pointer to rtc configuration.
 **********************************************************************************************************************/
static void r_rtc_config_rtc_interrupts (rtc_instance_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg)
{
    if (p_cfg->periodic_irq >= 0)
    {
        R_BSP_IrqCfg(p_cfg->periodic_irq, p_cfg->periodic_ipl, p_ctrl);
    }

    if (p_cfg->alarm_irq >= 0)
    {
        R_BSP_IrqCfg(p_cfg->alarm_irq, p_cfg->alarm_ipl, p_ctrl);
    }

#if BSP_FEATURE_RTC_HAS_ALARM1
    if (((rtc_extended_cfg_t *) p_cfg->p_extend)->alarm1_irq >= 0)
    {
        R_BSP_IrqCfg(((rtc_extended_cfg_t *) p_cfg->p_extend)->alarm1_irq,
                     ((rtc_extended_cfg_t *) p_cfg->p_extend)->alarm1_ipl,
                     p_ctrl);
    }
#endif
    if (p_cfg->carry_irq >= 0)
    {
        R_BSP_IrqCfg(p_cfg->carry_irq, p_cfg->carry_ipl, p_ctrl);
    }
}

/*******************************************************************************************************************//**
 * Helper function to enable or disable the Alarm/ Periodic/ Carry interrupt
 *
 * @param[in]  irq_enable_flag         Interrupt enable
 * @param[in]  mask                    Mask for the corresponding interrupt enable bit in RCR1
 **********************************************************************************************************************/
static void r_rtc_irq_set (bool irq_enable_flag, uint8_t mask)
{
    /* Enable the RTC carry interrupt request */
    if (irq_enable_flag)
    {
        /* Set the Interrupt Enable in RCR1 */
        R_RTC->RCR1 |= mask;

        /* When the RCR1 register is modified, check that all the bits are updated before proceeding
         * (see section 26.2.17 "RTC Control Register 1 (RCR1)" of the RA6M3 manual R01UH0886EJ0100)*/
        FSP_HARDWARE_REGISTER_WAIT((R_RTC->RCR1 & mask), mask);
    }
    else
    {
        /* Clear the Interrupt Enable in RCR1 */
        R_RTC->RCR1 &= (uint8_t) ~mask;

        FSP_HARDWARE_REGISTER_WAIT((R_RTC->RCR1 & mask), 0U);
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to RTC instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_rtc_call_callback (rtc_instance_ctrl_t * p_ctrl, rtc_event_t event)
{
    rtc_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    rtc_callback_args_t * p_args = p_ctrl->p_callback_memory;
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
        rtc_prv_ns_callback p_callback = (rtc_prv_ns_callback) (p_ctrl->p_callback);
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

#if RTC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Validate RFRL value for LOCO
 *
 * @param[in]  value                      Frequency Comparison Value
 * @retval FSP_SUCCESS                    validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_rfrl_validate (uint32_t value)
{
    fsp_err_t err;
    err = FSP_SUCCESS;

    /* A value from 0007h through 01FFh can be specified as the frequency comparison value (see section 26.2.20
     * Frequency Register (RFRH/RFRL)" of the RA6M3 manual R01UH0886EJ0100) */
    if ((RTC_RFRL_MIN_VALUE_LOCO >= value) ||
        (RTC_RFRL_MAX_VALUE_LOCO <= value))
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Validate Error Adjustment configuration when using SubClock
 *
 * @param[in]  err_adj_cfg             Pointer to error adjustment config
 * @retval FSP_SUCCESS                 Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT    Invalid error configuration
 **********************************************************************************************************************/
static fsp_err_t r_rtc_err_adjustment_parameter_check (rtc_error_adjustment_cfg_t const * const err_adj_cfg)
{
    rtc_error_adjustment_mode_t   mode   = err_adj_cfg->adjustment_mode;
    rtc_error_adjustment_period_t period = err_adj_cfg->adjustment_period;
    uint32_t value = err_adj_cfg->adjustment_value;

    /* Validate adjustment mode and period */
    if (RTC_ERROR_ADJUSTMENT_MODE_AUTOMATIC == mode)
    {
        if (RTC_ERROR_ADJUSTMENT_PERIOD_NONE == period)
        {
            return FSP_ERR_INVALID_ARGUMENT;
        }
    }

    /* Validate adjustment value */
    if (value > RTC_MAX_ERROR_ADJUSTMENT_VALUE)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validate time and date fields of time parameter fields
 * Checking for seconds, minutes, hours are valid values by calling sub-function time validate.
 * Checking for year, month, day of the week and day of a month are valid values by calling sub-function
 * date validate.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_time_and_date_validate (rtc_time_t * const p_time)
{
    fsp_err_t err = FSP_SUCCESS;
    err = r_rtc_time_validate(p_time);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);
    err = r_rtc_date_validate(p_time);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validate time fields of time type parameter
 * Checking for the seconds, minutes, hours values for valid specified range.
 * Seconds 0 to 59.
 * Minutes 0 to 59.
 * Hours   0 to 23.
 *
 * @param[in]  p_time                      Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_time_validate (rtc_time_t * p_time)
{
    fsp_err_t err;
    err = FSP_SUCCESS;
    if ((p_time->tm_sec < 0) || (p_time->tm_sec > RTC_SECONDS_IN_A_MINUTE) ||
        (p_time->tm_min < 0) || (p_time->tm_min > RTC_MINUTES_IN_A_HOUR) ||
        (p_time->tm_hour < 0) || (p_time->tm_hour > RTC_HOURS_IN_A_DAY))
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Validate date fields of time type parameter
 * validating r_rtc date fields and setting day of a Week using Zeller's congruence.
 * Checking for year, month, day of the week and day of a month are valid values.
 * Leap year validation and Week of the day is calculated and updated in rtc time.
 * Day of week between 0 to 6
 * Day between 1 to 31
 * Month between 0 to 11 as per standard time.h, There's a mismatch between hardware configuration,
 * UM indicates that "A value from 01 through 12 (in BCD) can be specified" for Month Counter register in the RTC.
 * This difference will be taken care in the Set and Get functions.
 *
 * As per HW manual, value of Year is between 0 to 99, the RTC has a 100 year calendar from 2000 to 2099.
 * (see section 26.1 "Overview" of the RA6M3 manual R01UH0886EJ0100)
 * But as per C standards, tm_year is years since 1900.
 * A sample year set in an application would be like time.tm_year = 2019-1900; (to set year 2019)
 * Since RTC API follows the Date and time structure defined in C standard library <time.h>, the valid value of year is
 * between 100 and 199, which will be internally converted to HW required value.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_date_validate (rtc_time_t * const p_time)
{
    uint32_t day_of_week;
    uint32_t num_days_month;
    uint32_t day_of_a_month;
    uint32_t temp_month;
    uint32_t temp_year;

    day_of_a_month = (uint32_t) p_time->tm_mday;
    temp_month     = (uint32_t) (p_time->tm_mon + RTC_TIME_H_MONTH_OFFSET);

    /* The valid value of year is between 100 to 199, The RTC has a 100 year calendar from 2000 to 2099
     * to match the starting year 2000, a sample year offset(1900) is added like 117 + 1900 = 2017*/
    temp_year = (uint32_t) (p_time->tm_year + RTC_TIME_H_YEAR_OFFSET);

    /* Checking the error condition for year and months values, here valid value of year is between 100 to 199
     * and for month 0 to 11*/
    if ((p_time->tm_year < RTC_YEAR_VALUE_MIN) || (p_time->tm_year > RTC_YEAR_VALUE_MAX) ||
        (p_time->tm_mon < 0) || (p_time->tm_mon > RTC_MONTHS_IN_A_YEAR))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    /*For particular valid month, number of days in a month is updated */
    num_days_month = days_in_months[p_time->tm_mon];

    /* Checking for February month and Conditions for Leap year : Every fourth year is a leap year,
     * The RTC has a 100 year calendar from 2000 to 2099  */
    if ((RTC_FEBRUARY_MONTH == temp_month) && ((temp_year % 4U) == 0))
    {
        num_days_month = RTC_LAST_DAY_OF_LEAP_FEB_MONTH;
    }

    /* Checking for day of a month values for valid range */
    if ((p_time->tm_mday >= RTC_FIRST_DAY_OF_A_MONTH) && (day_of_a_month <= num_days_month))
    {
        /* Adjust month to run from 3 to 14 for March to February */
        if (temp_month < RTC_MARCH_MONTH)
        {
            temp_month = (temp_month + 12U);

            /* Adjust year if January or February*/
            --temp_year;
        }

        /*For the Gregorian calendar, Zeller's congruence formulas is
         * h = ( q + [13(m+1)/5] + Y + [Y/4] - [Y/100] + [Y/400])mod 7 (mod : modulo)
         * h is the day of the week , q is the day of the month,
         * m is the month (3 = March, 4 = April,..., 14 = February)
         * Y is year, which is Y - 1 during January and February */
        day_of_week = (uint32_t) p_time->tm_mday + ((13 * (temp_month + 1)) / 5) + temp_year + (temp_year / 4);
        day_of_week = (day_of_week - RTC_ZELLER_ALGM_CONST_FIFTEEN) % 7;

        /* Day of week between 0 to 6 :- Sunday to Saturday */
        /* d = (h + 6)mod 7 (mod : modulo) */
        p_time->tm_wday = (int16_t) ((day_of_week + 6U) % 7U);

        return FSP_SUCCESS;
    }

    return FSP_ERR_INVALID_ARGUMENT;
}

/*******************************************************************************************************************//**
 * Validate alarm time and date of Alarm time type parameter
 * Checking for alarm enable bit with the seconds, minutes, hours are valid values.
 * Checking for alarm enable bit with year, month, day of the week and day of a month are valid values.
 * If alarm enable bit is set for year, month, and day of a month for valid range, Week of the day is
 * calculated and updated in alarm time.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_alarm_time_and_date_validate (rtc_alarm_time_t * const p_time)
{
    fsp_err_t err = FSP_SUCCESS;
    err = r_rtc_alarm_time_validate(p_time);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);

    /* Checking for alarm enable bit for year, month, day of the month */
    if ((p_time->year_match) && (p_time->mon_match) && (p_time->mday_match))
    {
        err = r_rtc_date_validate(&p_time->time);
        FSP_ERROR_RETURN(err == FSP_SUCCESS, err);
    }
    else
    {
        err = r_rtc_alarm_month_and_year_validate(p_time);
        FSP_ERROR_RETURN(err == FSP_SUCCESS, err);
        err = r_rtc_alarm_dayofmonth_and_dayofweek_validate(p_time);
        FSP_ERROR_RETURN(err == FSP_SUCCESS, err);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validate alarm time fields of Alarm time type parameter
 * Checking for alarm enable bit with the seconds, minutes, hours value for valid specified range.
 * Seconds 0 to 59.
 * Minutes 0 to 59.
 * Hours   0 to 23.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_alarm_time_validate (rtc_alarm_time_t * const p_time)
{
    fsp_err_t err;
    err = FSP_SUCCESS;
    if (((p_time->sec_match) &&
         ((p_time->time.tm_sec < 0) || (p_time->time.tm_sec > RTC_SECONDS_IN_A_MINUTE))) ||
        ((p_time->min_match) &&
         ((p_time->time.tm_min < 0) || (p_time->time.tm_min > RTC_MINUTES_IN_A_HOUR))) ||
        ((p_time->hour_match) &&
         ((p_time->time.tm_hour < 0) || (p_time->time.tm_hour > RTC_HOURS_IN_A_DAY))))
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Validate alarm month and year of time type parameter
 * Checking for alarm enable bit with month and year value for valid specified range.
 * Month : 0 to 11.
 * Year  : 100 to 199.
 * Since RTC API follows the Date and time structure defined in C standard library <time.h>, the valid value of year is
 * between 100 to 199.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_alarm_month_and_year_validate (rtc_alarm_time_t * const p_time)
{
    fsp_err_t err;
    err = FSP_SUCCESS;
    if (((p_time->mon_match) &&
         ((p_time->time.tm_mon < 0) || (p_time->time.tm_mon > RTC_MONTHS_IN_A_YEAR))) ||
        ((p_time->year_match) &&
         ((p_time->time.tm_year < RTC_YEAR_VALUE_MIN) || (p_time->time.tm_year > RTC_YEAR_VALUE_MAX))))
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Validate alarm day of a month and day of the week of time type parameter
 * Checking for alarm enable bit with day of a month and day of the week values for valid specified range.
 * Day of a month  : 1 to 31.
 * Day of the week : 0 to 6.
 * If alarm enable bit is set for particular valid month, number of days in a month is updated from that particular
 * month, by default 31 days in a month and for February month days are considered as 29 days in a month.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_alarm_dayofmonth_and_dayofweek_validate (rtc_alarm_time_t * const p_time)
{
    fsp_err_t err;
    uint8_t   num_days_month;
    uint8_t   day_of_a_month;

    day_of_a_month = (uint8_t) p_time->time.tm_mday;
    err            = FSP_SUCCESS;

    /* checking for alarm enable bit of valid month */
    if (p_time->mon_match)
    {
        /* Checking condition for February month in time.h months start from 0 to 11, for February 1 */
        if ((RTC_FEBRUARY_MONTH - 1U) == p_time->time.tm_mon)
        {
            /*For February month, number of days can be 28 for regular year and 29 for leap year.
             * Hence consider 29 days for February.*/
            num_days_month = (uint8_t) RTC_LAST_DAY_OF_LEAP_FEB_MONTH;
        }
        else
        {
            /* For valid month, number of days in month is assigned*/
            num_days_month = days_in_months[p_time->time.tm_mon];
        }
    }
    else
    {
        /* default 31 days in a month*/
        num_days_month = (uint8_t) RTC_LAST_DAY_OF_A_MONTH;
    }

    if (((p_time->mday_match) &&
         ((p_time->time.tm_mday < RTC_FIRST_DAY_OF_A_MONTH) || (day_of_a_month > num_days_month))) ||
        ((p_time->dayofweek_match) &&
         ((p_time->time.tm_wday < 0) || (p_time->time.tm_wday > RTC_DAYS_IN_A_WEEK))))
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

#endif

/*******************************************************************************************************************//**
 * This function sets time error adjustment mode, period, type and value.
 *
 *@param[in] err_adj_cfg  Pointer to the Error Adjustment Configuration
 **********************************************************************************************************************/
static void r_rtc_error_adjustment_set (rtc_error_adjustment_cfg_t const * const err_adj_cfg)
{
    rtc_error_adjustment_mode_t   mode   = err_adj_cfg->adjustment_mode;
    rtc_error_adjustment_period_t period = err_adj_cfg->adjustment_period;
    rtc_error_adjustment_t        type   = err_adj_cfg->adjustment_type;
    uint32_t value = err_adj_cfg->adjustment_value;

    /* Check if mode change is required */
    if (mode != R_RTC->RCR2_b.AADJE)
    {
        /* Clear error adjustment before configuring the error adjustment mode
         * (see section "26.3.8.3 Procedure for changing the mode of adjustment" of the RA6M3 manual R01UH0886EJ0100) */
        R_RTC->RADJ = 0U;

        /* When RADJ is modified, check that all the bits are updated before continuing with more processing.
         * (see section 26.2.21 "Time Error Adjustment Register (RADJ)" of the RA6M3 manual R01UH0886EJ0100) */
        FSP_HARDWARE_REGISTER_WAIT(R_RTC->RADJ, 0U);

        /* Set the error adjustment enable, 1: Enable Automatic adjsutment 0: Disable Automatic adjsutment */
        R_RTC->RCR2_b.AADJE = (uint8_t) mode & 1U;
        FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2_b.AADJE, mode);
    }

    /* Set the period if mode is Automatic adjustment */
    if (RTC_ERROR_ADJUSTMENT_MODE_AUTOMATIC == mode)
    {
        /* Check if period change is required */
        if (period != R_RTC->RCR2_b.AADJP)
        {
            /* Set time error adjustment period */
            R_RTC->RCR2_b.AADJP = (uint8_t) (period & 1U);

            /* When RCR2 is modified, check that all the bits are updated before continuing with more processing.
             * (see section 26.2.18 "RTC Control Register 2 (RCR2) of the RA6M3 manual R01UH0886EJ0100) */
            FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2_b.AADJP, period);
        }
    }

#if BSP_FEATURE_RTC_HAS_RADJ_ADJ6
    uint16_t error_adjustment =
        (uint16_t) ((uint16_t) (((value & RTC_ADJ6_ADJUSTMENT_VALUE) > 0) << R_RTC_RADJ_ADJ6_Pos) |
                    ((uint8_t) (type << R_RTC_RADJ_PMADJ_Pos) |
                     (value & RTC_MAX_ADJ_VALUE)));
#else
    uint8_t error_adjustment = (uint8_t) ((uint8_t) (((uint8_t) type) << R_RTC_RADJ_PMADJ_Pos) |
                                          (RTC_MAX_ERROR_ADJUSTMENT_VALUE & value));
#endif

    R_RTC->RADJ = error_adjustment;

    /* When RADJ is modified, check that all the bits are updated before continuing with more processing.
     * (see section 26.2.21 "Time Error Adjustment Register (RADJ)" of the RA6M3 manual R01UH0886EJ0100) */
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RADJ, error_adjustment);
}

/*******************************************************************************************************************//**
 * RTC Callback ISR for alarm and periodic interrupt.
 *
 * Saves context if RTOS is used, stops the timer if one-shot mode, clears interrupts, calls callback if one was
 * provided in the open function, and restores context if RTOS is used.
 **********************************************************************************************************************/

void rtc_alarm_periodic_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

#if BSP_FEATURE_LPM_RTC_REGISTER_CLOCK_DISABLE

    /* Enable the RTC Register Read/Write clock if it was disabled prior to entering LPM. */
    bsp_prv_rtc_register_clock_set(true);
#endif

    /* Call the callback routine if one is available */
    if (NULL != p_ctrl->p_callback)
    {
        /* Set data to identify callback to user, then call user callback. */
        rtc_event_t event;
        if (irq == p_ctrl->p_cfg->alarm_irq)
        {
            event = RTC_EVENT_ALARM_IRQ;
        }

#if BSP_FEATURE_RTC_HAS_ALARM1
        else if (irq == ((rtc_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->alarm1_irq)
        {
            event = RTC_EVENT_ALARM1_IRQ;
        }
#endif
        else
        {
            event = RTC_EVENT_PERIODIC_IRQ;
        }

        /* Call callback */
        r_rtc_call_callback(p_ctrl, event);
    }

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * RTC Carry ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls callback if one was
 * provided in the open function, and restores context if RTOS is used.
 **********************************************************************************************************************/
void rtc_carry_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

#if BSP_FEATURE_LPM_RTC_REGISTER_CLOCK_DISABLE

    /* Enable the RTC Register Read/Write clock if it was disabled prior to entering LPM. */
    bsp_prv_rtc_register_clock_set(true);
#endif

    p_ctrl->carry_isr_triggered = true;

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Convert decimal to BCD
 *
 * @param[in] to_convert   Decimal Value to be converted
 **********************************************************************************************************************/
static uint8_t rtc_dec_to_bcd (uint8_t to_convert)
{
    return (uint8_t) ((((to_convert / (uint8_t) 10) << 4) & (uint8_t) RTC_MASK_LSB) | (to_convert % (uint8_t) 10));
}

/*******************************************************************************************************************//**
 * Convert  BCD to decimal
 *
 * @param[in] to_convert   BCD Value to be converted
 **********************************************************************************************************************/
static uint8_t rtc_bcd_to_dec (uint8_t to_convert)
{
    return (uint8_t) ((((to_convert & (uint8_t) RTC_MASK_LSB) >> 4) * (uint8_t) 10) +
                      (to_convert & (uint8_t) RTC_MASK_MSB));
}
