/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019, 2022-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_IRTC_H_
#define FSL_IRTC_H_

#include "fsl_common.h"

/*!
 * @addtogroup irtc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_IRTC_DRIVER_VERSION (MAKE_VERSION(2, 2, 4)) /*!< Version. */
/*@}*/

#if defined(FSL_FEATURE_RTC_HAS_CLOCK_SELECT) && FSL_FEATURE_RTC_HAS_CLOCK_SELECT
/*! @brief IRTC clock select. */
typedef enum _irtc_clock_select
{
    kIRTC_Clk16K = 0x0U, /*!< 16.384 kHz clock is selected.*/
    kIRTC_Clk32K = 0x1U, /*!< 32.768 kHz clock is selected.*/
} irtc_clock_select_t;
#endif

#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
/*! @brief IRTC filter clock source options. */
typedef enum _irtc_filter_clock_source
{
    kIRTC_32K = 0x0U, /*!< Use 32 kHz clock source for the tamper filter.*/
    kIRTC_512 = 0x1U, /*!< Use 512 Hz clock source for the tamper filter.*/
    kIRTC_128 = 0x2U, /*!< Use 128 Hz clock source for the tamper filter.*/
    kIRTC_64  = 0x3U, /*!< Use 64 Hz clock source for the tamper filter.*/
    kIRTC_16  = 0x4U, /*!< Use 16 Hz clock source for the tamper filter.*/
    kIRTC_8   = 0x5U, /*!< Use 8 Hz clock source for the tamper filter.*/
    kIRTC_4   = 0x6U, /*!< Use 4 Hz clock source for the tamper filter.*/
    kIRTC_2   = 0x7U  /*!< Use 2 Hz clock source for the tamper filter.*/
} irtc_filter_clock_source_t;

/*! @brief IRTC Tamper pins. */
typedef enum _irtc_tamper_pins
{
    kIRTC_Tamper_0 = 0U, /*!< External Tamper 0 */
    kIRTC_Tamper_1,      /*!< External Tamper 1 */
    kIRTC_Tamper_2,      /*!< External Tamper 2 */
    kIRTC_Tamper_3       /*!< Internal tamper, does not have filter configuration */
} irtc_tamper_pins_t;
#endif

/*! @brief List of IRTC interrupts */
typedef enum _irtc_interrupt_enable
{
#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
    kIRTC_TamperInterruptEnable = RTC_IER_TAMPER_IE_MASK, /*!< Tamper Interrupt Enable */
#endif
    kIRTC_AlarmInterruptEnable = RTC_IER_ALM_IE_MASK,   /*!< Alarm Interrupt Enable */
    kIRTC_DayInterruptEnable   = RTC_IER_DAY_IE_MASK,   /*!< Days Interrupt Enable */
    kIRTC_HourInterruptEnable  = RTC_IER_HOUR_IE_MASK,  /*!< Hours Interrupt Enable */
    kIRTC_MinInterruptEnable   = RTC_IER_MIN_IE_MASK,   /*!< Minutes Interrupt Enable */
    kIRTC_1hzInterruptEnable   = RTC_IER_IE_1HZ_MASK,   /*!< 1 Hz interval Interrupt Enable */
    kIRTC_2hzInterruptEnable   = RTC_IER_IE_2HZ_MASK,   /*!< 2 Hz interval Interrupt Enable */
    kIRTC_4hzInterruptEnable   = RTC_IER_IE_4HZ_MASK,   /*!< 4 Hz interval Interrupt Enable */
    kIRTC_8hzInterruptEnable   = RTC_IER_IE_8HZ_MASK,   /*!< 8 Hz interval Interrupt Enable */
    kIRTC_16hzInterruptEnable  = RTC_IER_IE_16HZ_MASK,  /*!< 16 Hz interval Interrupt Enable */
    kIRTC_32hzInterruptEnable  = RTC_IER_IE_32HZ_MASK,  /*!< 32 Hz interval Interrupt Enable */
    kIRTC_64hzInterruptEnable  = RTC_IER_IE_64HZ_MASK,  /*!< 64 Hz interval Interrupt Enable */
    kIRTC_128hzInterruptEnable = RTC_IER_IE_128HZ_MASK, /*!< 128 Hz interval Interrupt Enable */
    kIRTC_256hzInterruptEnable = RTC_IER_IE_256HZ_MASK, /*!< 256 Hz interval Interrupt Enable */
    kIRTC_512hzInterruptEnable = RTC_IER_IE_512HZ_MASK, /*!< 512 Hz interval Interrupt Enable */
#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
    kIRTC_WakeTimerInterruptEnable = (RTC_WAKE_TIMER_CTRL_INTR_EN_MASK << 16U), /*!< Wake timer Interrupt Enable */
#endif
#if defined(FSL_FEATURE_RTC_HAS_TAMPER_QUEUE) && FSL_FEATURE_RTC_HAS_TAMPER_QUEUE
    kIRTC_TamperQueueFullInterruptEnable =
        (RTC_TAMPER_QSCR_Q_FULL_INT_EN_MASK << 24U), /*!< Tamper queue full Interrupt Enable */
#endif
} irtc_interrupt_enable_t;

/*! @brief List of IRTC flags */
typedef enum _irtc_status_flags
{
#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
    kIRTC_TamperFlag = RTC_ISR_TAMPER_IS_MASK, /*!< Tamper Status flag*/
#endif
    kIRTC_AlarmFlag     = RTC_ISR_ALM_IS_MASK,                    /*!< Alarm Status flag */
    kIRTC_DayFlag       = RTC_ISR_DAY_IS_MASK,                    /*!< Days Status flag */
    kIRTC_HourFlag      = RTC_ISR_HOUR_IS_MASK,                   /*!< Hour Status flag */
    kIRTC_MinFlag       = RTC_ISR_MIN_IS_MASK,                    /*!< Minutes Status flag */
    kIRTC_1hzFlag       = RTC_ISR_IS_1HZ_MASK,                    /*!< 1 Hz interval status flag */
    kIRTC_2hzFlag       = RTC_ISR_IS_2HZ_MASK,                    /*!< 2 Hz interval status flag*/
    kIRTC_4hzFlag       = RTC_ISR_IS_4HZ_MASK,                    /*!< 4 Hz interval status flag*/
    kIRTC_8hzFlag       = RTC_ISR_IS_8HZ_MASK,                    /*!< 8 Hz interval status flag*/
    kIRTC_16hzFlag      = RTC_ISR_IS_16HZ_MASK,                   /*!< 16 Hz interval status flag*/
    kIRTC_32hzFlag      = RTC_ISR_IS_32HZ_MASK,                   /*!< 32 Hz interval status flag*/
    kIRTC_64hzFlag      = RTC_ISR_IS_64HZ_MASK,                   /*!< 64 Hz interval status flag*/
    kIRTC_128hzFlag     = RTC_ISR_IS_128HZ_MASK,                  /*!< 128 Hz interval status flag*/
    kIRTC_256hzFlag     = RTC_ISR_IS_256HZ_MASK,                  /*!< 256 Hz interval status flag*/
    kIRTC_512hzFlag     = RTC_ISR_IS_512HZ_MASK,                  /*!< 512 Hz interval status flag*/
    kIRTC_InvalidFlag   = (RTC_STATUS_INVAL_BIT_MASK << 16U),     /*!< Indicates if time/date counters are invalid */
    kIRTC_WriteProtFlag = (RTC_STATUS_WRITE_PROT_EN_MASK << 16U), /*!< Write protect enable status flag */
#if !defined(FSL_FEATURE_RTC_HAS_NO_CPU_LOW_VOLT_FLAG) || (!FSL_FEATURE_RTC_HAS_NO_CPU_LOW_VOLT_FLAG)
    kIRTC_CpuLowVoltFlag = (RTC_STATUS_CPU_LOW_VOLT_MASK << 16U), /*!< CPU low voltage warning flag */
#endif
#if !defined(FSL_FEATURE_RTC_HAS_NO_RST_SRC_FLAG) || (!FSL_FEATURE_RTC_HAS_NO_RST_SRC_FLAG)
    kIRTC_ResetSrcFlag = (RTC_STATUS_RST_SRC_MASK << 16U), /*!< Reset source flag */
#endif
    kIRTC_CmpIntFlag  = (RTC_STATUS_CMP_INT_MASK << 16U),  /*!< Compensation interval status flag */
    kIRTC_BusErrFlag  = (RTC_STATUS_BUS_ERR_MASK << 16U),  /*!< Bus error flag */
    kIRTC_CmpDoneFlag = (RTC_STATUS_CMP_DONE_MASK << 16U), /*!< Compensation done flag */
#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
    kIRTC_WakeTimerFlag = (RTC_WAKE_TIMER_CTRL_WAKE_FLAG_MASK << 28U) /*!< Wake timer status flag */
#endif
} irtc_status_flags_t;

/*! @brief IRTC alarm match options */
typedef enum _irtc_alarm_match
{
    kRTC_MatchSecMinHr          = 0U, /*!< Only match second, minute and hour */
    kRTC_MatchSecMinHrDay       = 1U, /*!< Only match second, minute, hour and day */
    kRTC_MatchSecMinHrDayMnth   = 2U, /*!< Only match second, minute, hour, day and month */
    kRTC_MatchSecMinHrDayMnthYr = 3U  /*!< Only match second, minute, hour, day, month and year */
} irtc_alarm_match_t;

#if !defined(FSL_FEATURE_RTC_HAS_NO_GP_DATA_REG) || (!FSL_FEATURE_RTC_HAS_NO_GP_DATA_REG)
/*! @brief List of RTC Oscillator capacitor load settings */
typedef enum _irtc_osc_cap_load
{
    kIRTC_Capacitor2p  = (1U << 1U), /*!< 2pF capacitor load */
    kIRTC_Capacitor4p  = (1U << 2U), /*!< 4pF capacitor load */
    kIRTC_Capacitor8p  = (1U << 3U), /*!< 8pF capacitor load */
    kIRTC_Capacitor16p = (1U << 4U)  /*!< 16pF capacitor load */
} irtc_osc_cap_load_t;
#endif

/*! @brief IRTC clockout select. */
typedef enum _irtc_clockout_sel
{
    kIRTC_ClkoutNo = 0U,  /*!< No clock out */
    kIRTC_ClkoutFine1Hz,  /*!< clock out fine 1Hz */
    kIRTC_Clkout32kHz,    /*!< clock out 32.768kHz */
    kIRTC_ClkoutCoarse1Hz /*!< clock out coarse 1Hz */
} irtc_clockout_sel_t;

/*! @brief Structure is used to hold the date and time */
typedef struct _irtc_datetime
{
    uint16_t year;   /*!< Range from 1984 to 2239.*/
    uint8_t month;   /*!< Range from 1 to 12.*/
    uint8_t day;     /*!< Range from 1 to 31 (depending on month).*/
    uint8_t weekDay; /*!< Range from 0(Sunday) to 6(Saturday). */
    uint8_t hour;    /*!< Range from 0 to 23.*/
    uint8_t minute;  /*!< Range from 0 to 59.*/
    uint8_t second;  /*!< Range from 0 to 59.*/
} irtc_datetime_t;

/*! @brief Structure is used to hold the daylight saving time */
typedef struct _irtc_daylight_time
{
    uint8_t startMonth; /*!< Range from 1 to 12 */
    uint8_t endMonth;   /*!< Range from 1 to 12 */
    uint8_t startDay;   /*!< Range from 1 to 31 (depending on month) */
    uint8_t endDay;     /*!< Range from 1 to 31 (depending on month) */
    uint8_t startHour;  /*!< Range from 0 to 23 */
    uint8_t endHour;    /*!< Range from 0 to 23 */
} irtc_daylight_time_t;

#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
/*! @brief Structure is used to define the parameters to configure a RTC tamper event. */
typedef struct _irtc_tamper_config
{
#if FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION
    bool activePassive; /*!< true: configure tamper as active; false: passive tamper */
    bool direction;     /*!< true: configure tamper direction as output; false: configure as input;
                             this is only used if a tamper pin is defined as active */
#endif
    bool pinPolarity;                     /*!< true: tamper has active low polarity;
                                               false: active high polarity */
    irtc_filter_clock_source_t filterClk; /*!< Clock source for the tamper filter */
    uint8_t filterDuration;               /*!< Tamper filter duration.*/
} irtc_tamper_config_t;
#endif

/*!
 * @brief RTC config structure
 *
 * This structure holds the configuration settings for the RTC peripheral. To initialize this
 * structure to reasonable defaults, call the IRTC_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _irtc_config
{
#if !defined(FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE) || (!FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE)
    bool wakeupSelect; /*!< true: Tamper pin 0 is used to wakeup the chip;
                            false: Tamper pin 0 is used as the tamper pin */
#endif
#if !defined(FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK) || (!FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK)
    bool timerStdMask; /*!< true: Sampling clocks gated in standby mode;
                            false: Sampling clocks not gated */
#endif
    irtc_alarm_match_t alrmMatch; /*!< Pick one option from enumeration :: irtc_alarm_match_t */
#if defined(FSL_FEATURE_RTC_HAS_CLOCK_SELECT) && FSL_FEATURE_RTC_HAS_CLOCK_SELECT
    irtc_clock_select_t clockSelect; /*!< Pick one option from enumeration :: irtc_clock_select_t */
#endif
#if defined(FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE) && FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE
    bool disableClockOutput; /*!< true: The selected clock is not output to other peripherals;
                                  false: The selected clock is output to other peripherals */
#endif
} irtc_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the IRTC clock and configures the peripheral for basic operation.
 *
 * This function initiates a soft-reset of the IRTC module, this has not effect on DST,
 * calendaring, standby time and tamper detect registers.
 *
 * @note This API should be called at the beginning of the application using the IRTC driver.
 *
 * @param base   IRTC peripheral base address
 * @param config Pointer to user's IRTC config structure.
 *
 * @return kStatus_Fail if we cannot disable register write protection
 */
status_t IRTC_Init(RTC_Type *base, const irtc_config_t *config);

/*!
 * @brief Gate the IRTC clock
 *
 * @param base IRTC peripheral base address
 */
static inline void IRTC_Deinit(RTC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_Rtc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * @brief Fill in the IRTC config struct with the default settings
 *
 * The default values are:
 * @code
 *    config->wakeupSelect = true;
 *    config->timerStdMask = false;
 *    config->alrmMatch = kRTC_MatchSecMinHr;
 * @endcode
 * @param config Pointer to user's IRTC config structure.
 */
void IRTC_GetDefaultConfig(irtc_config_t *config);

/*! @}*/

/*!
 * @name Current Time & Alarm
 * @{
 */

/*!
 * @brief Sets the IRTC date and time according to the given time structure.
 *
 * The IRTC counter is started after the time is set.
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to structure where the date and time details to set are stored
 *
 * @return kStatus_Success: success in setting the time and starting the IRTC
 *         kStatus_InvalidArgument: failure. An error occurs because the datetime format is incorrect.
 */
status_t IRTC_SetDatetime(RTC_Type *base, const irtc_datetime_t *datetime);

/*!
 * @brief Gets the IRTC time and stores it in the given time structure.
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to structure where the date and time details are stored.
 */
void IRTC_GetDatetime(RTC_Type *base, irtc_datetime_t *datetime);

/*!
 * @brief Sets the IRTC alarm time
 *
 * @param base      RTC peripheral base address
 * @param alarmTime Pointer to structure where the alarm time is stored.
 *
 * @note weekDay field of alarmTime is not used during alarm match and should be set to 0
 *
 * @return kStatus_Success: success in setting the alarm
 *         kStatus_InvalidArgument: error in setting the alarm. Error occurs because the alarm
 *                                  datetime format is incorrect.
 */
status_t IRTC_SetAlarm(RTC_Type *base, const irtc_datetime_t *alarmTime);

/*!
 * @brief Returns the IRTC alarm time.
 *
 * @param base     RTC peripheral base address
 * @param datetime Pointer to structure where the alarm date and time details are stored.
 */
void IRTC_GetAlarm(RTC_Type *base, irtc_datetime_t *datetime);
/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected IRTC interrupts.
 *
 * @param base IRTC peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::irtc_interrupt_enable_t
 */
static inline void IRTC_EnableInterrupts(RTC_Type *base, uint32_t mask)
{
    base->IER |= (uint16_t)mask;
#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
    if (0U != (mask & (uint32_t)kIRTC_WakeTimerInterruptEnable))
    {
        base->WAKE_TIMER_CTRL |= RTC_WAKE_TIMER_CTRL_INTR_EN_MASK;
    }
#endif
#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
#if defined(FSL_FEATURE_RTC_HAS_TAMPER_QUEUE) && (FSL_FEATURE_RTC_HAS_TAMPER_QUEUE)
    if (0U != (mask & (uint32_t)kIRTC_TamperQueueFullInterruptEnable))
    {
        base->TAMPER_QSCR |= RTC_TAMPER_QSCR_Q_FULL_INT_EN_MASK;
    }
#endif
#endif
}

/*!
 * @brief Disables the selected IRTC interrupts.
 *
 * @param base IRTC peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::irtc_interrupt_enable_t
 */
static inline void IRTC_DisableInterrupts(RTC_Type *base, uint32_t mask)
{
    base->IER &= ~(uint16_t)mask;
#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
    if (0U != (mask & (uint32_t)kIRTC_WakeTimerInterruptEnable))
    {
        base->WAKE_TIMER_CTRL &= ~(uint16_t)RTC_WAKE_TIMER_CTRL_INTR_EN_MASK;
    }
#endif
#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
#if defined(FSL_FEATURE_RTC_HAS_TAMPER_QUEUE) && (FSL_FEATURE_RTC_HAS_TAMPER_QUEUE)
    if (0U != (mask & (uint32_t)kIRTC_TamperQueueFullInterruptEnable))
    {
        base->TAMPER_QSCR &= ~(uint16_t)RTC_TAMPER_QSCR_Q_FULL_INT_EN_MASK;
    }
#endif
#endif
}

/*!
 * @brief Gets the enabled IRTC interrupts.
 *
 * @param base IRTC peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::irtc_interrupt_enable_t
 */
static inline uint32_t IRTC_GetEnabledInterrupts(RTC_Type *base)
{
    uint32_t intsEnabled = base->IER;
#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
    intsEnabled |= (base->WAKE_TIMER_CTRL & (uint32_t)RTC_WAKE_TIMER_CTRL_INTR_EN_MASK) << 16U;
#endif
#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
#if defined(FSL_FEATURE_RTC_HAS_TAMPER_QUEUE) && (FSL_FEATURE_RTC_HAS_TAMPER_QUEUE)
    intsEnabled |= (base->TAMPER_QSCR & (uint32_t)RTC_TAMPER_QSCR_Q_FULL_INT_EN_MASK) << 24U;
#endif
#endif

    return intsEnabled;
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the IRTC status flags
 *
 * @param base IRTC peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::irtc_status_flags_t
 */
static inline uint32_t IRTC_GetStatusFlags(RTC_Type *base)
{
#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
    return (base->ISR | ((uint32_t)base->STATUS << 16U) | ((uint32_t)base->WAKE_TIMER_CTRL << 28U));
#else
    return (base->ISR | ((uint32_t)base->STATUS << 16U));
#endif
}

/*!
 * @brief Clears the IRTC status flags.
 *
 * @param base IRTC peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::irtc_status_flags_t
 */
static inline void IRTC_ClearStatusFlags(RTC_Type *base, uint32_t mask)
{
    base->ISR    = (uint16_t)mask;
    base->STATUS = (base->STATUS & ~((uint16_t)RTC_STATUS_BUS_ERR_MASK | (uint16_t)RTC_STATUS_CMP_DONE_MASK)) |
                   ((uint16_t)(mask >> 16U));
#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
    /* TAMPER flag need clear TAMPER_SCR[TMPR_STS] filed */
    if (0U != (mask & (uint32_t)kIRTC_TamperFlag))
    {
        base->TAMPER_SCR |= RTC_TAMPER_SCR_TMPR_STS_MASK;
    }
#endif
#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
    if (0U != (mask & (uint32_t)kIRTC_WakeTimerFlag))
    {
        base->WAKE_TIMER_CTRL |= RTC_WAKE_TIMER_CTRL_WAKE_FLAG_MASK;
    }
#endif
}

/*! @}*/

#if !defined(FSL_FEATURE_RTC_HAS_NO_GP_DATA_REG) || (!FSL_FEATURE_RTC_HAS_NO_GP_DATA_REG)

/*!
 * @brief This function sets the specified capacitor configuration for the RTC oscillator.
 *
 * @param base    IRTC peripheral base address
 * @param capLoad Oscillator loads to enable. This is a logical OR of members of the
 *                enumeration ::irtc_osc_cap_load_t
 */
static inline void IRTC_SetOscCapLoad(RTC_Type *base, uint16_t capLoad)
{
    uint16_t reg = base->GP_DATA_REG;

    reg &= ~((uint16_t)kIRTC_Capacitor2p | (uint16_t)kIRTC_Capacitor4p | (uint16_t)kIRTC_Capacitor8p |
             (uint16_t)kIRTC_Capacitor16p);
    reg |= capLoad;

    base->GP_DATA_REG = reg;
}

#endif

/*!
 * @brief Locks or unlocks IRTC registers for write access.
 *
 * @note When the registers are unlocked, they remain in unlocked state for
 * 2 seconds, after which they are locked automatically. After
 * power-on-reset, the registers come out unlocked and they are locked
 * automatically 15 seconds after power on.
 *
 * @param base IRTC peripheral base address
 * @param lock true: Lock IRTC registers; false: Unlock IRTC registers.
 *
 * @return kStatus_Success: if lock or unlock operation is successful
 *         kStatus_Fail: if lock or unlock operation fails even after multiple retry attempts
 */
status_t IRTC_SetWriteProtection(RTC_Type *base, bool lock);

/*!
 * @brief Performs a software reset on the IRTC module.
 *
 * Clears contents of alarm, interrupt (status and enable except tamper interrupt enable bit)
 * registers, STATUS[CMP_DONE] and STATUS[BUS_ERR]. This has no effect on DST, calendaring, standby time
 * and tamper detect registers.
 *
 * @param base IRTC peripheral base address
 */
static inline void IRTC_Reset(RTC_Type *base)
{
    base->CTRL |= RTC_CTRL_SWR_MASK;
}

#if !defined(FSL_FEATURE_RTC_HAS_NO_GP_DATA_REG) || (!FSL_FEATURE_RTC_HAS_NO_GP_DATA_REG)

/*!
 * @brief Enable/disable 32 kHz RTC OSC clock during RTC register write
 *
 * @param base IRTC peripheral base address
 * @param enable Enable/disable 32 kHz RTC OSC clock.
 *               - true: Enables the oscillator.
 *               - false: Disables the oscillator.
 *
 */
static inline void IRTC_Enable32kClkDuringRegisterWrite(RTC_Type *base, bool enable)
{
    uint16_t mask = RTC_GP_DATA_REG_CFG0_MASK;
    if (enable)
    {
        base->GP_DATA_REG &= ~mask;
    }
    else
    {
        base->GP_DATA_REG |= mask;
    }
}

#endif

/*!
 * @brief Select which clock to output from RTC.
 *
 * Select which clock to output from RTC for other modules to use inside SoC, for example,
 * RTC subsystem needs RTC to output 1HZ clock for sub-second counter.
 *
 * @param base IRTC peripheral base address
 * @param cloOut select clock to use for output,
 */
void IRTC_ConfigClockOut(RTC_Type *base, irtc_clockout_sel_t clkOut);

#if defined(FSL_FEATURE_RTC_HAS_CLOCK_SELECT) && FSL_FEATURE_RTC_HAS_CLOCK_SELECT

/*!
 * @brief Select which clock is used by RTC.
 *
 * Select which clock is used by RTC to output to the peripheral
 * and divided to generate a 512 Hz clock and a 1 Hz clock.
 *
 * @param base IRTC peripheral base address
 * @param clkSelect select clock used by RTC
 */
void IRTC_ConfigClockSelect(RTC_Type *base, irtc_clock_select_t clkSelect);

#endif /* FSL_FEATURE_RTC_HAS_CLOCK_SELECT */

#if defined(FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE) && FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE

/*!
 * @brief Determines whether the selected clock is output to other peripherals.
 *
 * Determines whether the selected clock is output to other peripherals.
 *
 * @param base IRTC peripheral base address
 * @param enable determine whether the selected clock is output to other peripherals
 */
static inline void IRTC_EnableClockOutputToPeripheral(RTC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL &= ~(uint16_t)RTC_CTRL_CLKO_DIS_MASK;
    }
    else
    {
        base->CTRL |= RTC_CTRL_CLKO_DIS_MASK;
    }
}

#endif /* FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE */

#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)

/*!
 * @brief Gets the IRTC Tamper status flags
 *
 * @param base IRTC peripheral base address
 *
 * @return The Tamper status value.
 */
static inline uint8_t IRTC_GetTamperStatusFlag(RTC_Type *base)
{
    return (uint8_t)((base->TAMPER_SCR & RTC_TAMPER_SCR_TMPR_STS_MASK) >> RTC_TAMPER_SCR_TMPR_STS_SHIFT);
}

/*!
 * @brief Gets the IRTC Tamper status flags
 *
 * @param base IRTC peripheral base address
 *
 */
static inline void IRTC_ClearTamperStatusFlag(RTC_Type *base)
{
    /* Writing '1' to this field clears the tamper status.*/
    base->TAMPER_SCR |= RTC_TAMPER_SCR_TMPR_STS_MASK;
}

/*!
 * @brief Set tamper configuration over
 *
 * Note that this API is neeeded after call IRTC_SetTamperParams to configure tamper events to
 * notify IRTC module that tamper configuration process is over.
 *
 * @param base IRTC peripheral base address
 *
 */
static inline void IRTC_SetTamperConfigurationOver(RTC_Type *base)
{
    /* Set tamper configuration over.*/
    base->CTRL2 |= RTC_CTRL2_TAMP_CFG_OVER_MASK;
}

#endif

/*!
 * @name Daylight Savings Interface
 * @{
 */

/*!
 * @brief Sets the IRTC daylight savings start and stop date and time.
 *
 * It also enables the daylight saving bit in the IRTC control register
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_SetDaylightTime(RTC_Type *base, const irtc_daylight_time_t *datetime);

/*!
 * @brief Gets the IRTC daylight savings time and stores it in the given time structure.
 *
 * @param base     IRTC peripheral base address
 * @param datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_GetDaylightTime(RTC_Type *base, irtc_daylight_time_t *datetime);

/*! @}*/

/*!
 * @name Time Compensation Interface
 * @{
 */

/*!
 * @brief Enables the coarse compensation and sets the value in the IRTC compensation register.
 *
 * @param base                 IRTC peripheral base address
 * @param compensationValue    Compensation value is a 2's complement value.
 * @param compensationInterval Compensation interval.
 */
void IRTC_SetCoarseCompensation(RTC_Type *base, uint8_t compensationValue, uint8_t compensationInterval);

/*!
 * @brief Enables the fine compensation and sets the value in the IRTC compensation register.
 *
 * @param base                 The IRTC peripheral base address
 * @param integralValue        Compensation integral value; twos complement value of the integer part
 * @param fractionValue        Compensation fraction value expressed as number of clock cycles of a
 *                             fixed 4.194304Mhz clock that have to be added.
 * @param accumulateFractional Flag indicating if we want to add to previous fractional part;
 *                             true: Add to previously accumulated fractional part,
 *                             false: Start afresh and overwrite current value
 */
void IRTC_SetFineCompensation(RTC_Type *base, uint8_t integralValue, uint8_t fractionValue, bool accumulateFractional);

/*! @}*/

#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)

/*!
 * @name Tamper Interface
 * @{
 */

/*!
 * @brief This function allows configuring the four tamper inputs.
 *
 * The function configures the filter properties for the three external tampers.
 * It also sets up active/passive and direction of the tamper bits, which are not available
 * on all platforms.
 * @note This function programs the tamper filter parameters. The user must gate the 32K clock to
 * the RTC before calling this function. It is assumed that the time and date are set after this
 * and the tamper parameters do not require to be changed again later.
 *
 * @param base         The IRTC peripheral base address
 * @param tamperNumber The IRTC tamper input to configure
 * @param tamperConfig The IRTC tamper properties
 */
void IRTC_SetTamperParams(RTC_Type *base, irtc_tamper_pins_t tamperNumber, const irtc_tamper_config_t *tamperConfig);

#if defined(FSL_FEATURE_RTC_HAS_TAMPER_QUEUE) && (FSL_FEATURE_RTC_HAS_TAMPER_QUEUE)

/*!
 * @brief This function reads the tamper timestamp and returns the associated tamper pin.
 *
 * The tamper timestamp has month, day, hour, minutes, and seconds. Ignore the year field as this
 * information is not available in the tamper queue. The user should look at the RTC_YEARMON register
 * for this because the expectation is that the queue is read at least once a year.
 * Return the tamper pin number associated with the timestamp.
 *
 * @param base             The IRTC peripheral base address
 * @param tamperTimestamp  The tamper timestamp
 *
 * @return The tamper pin number
 */
uint8_t IRTC_ReadTamperQueue(RTC_Type *base, irtc_datetime_t *tamperTimestamp);

/*!
 * @brief Gets the IRTC Tamper queue full status
 *
 * @param base IRTC peripheral base address
 *
 * @retval true Tamper queue is full.
 * @retval false Tamper queue is not full.
 */
static inline bool IRTC_GetTamperQueueFullStatus(RTC_Type *base)
{
    return ((0U != (base->TAMPER_SCR & RTC_TAMPER_QSCR_Q_FULL_MASK)) ? true : false);
}

/*!
 * @brief Clear the IRTC Tamper queue full status
 *
 * @param base IRTC peripheral base address
 *
 */
static inline void IRTC_ClearTamperQueueFullStatus(RTC_Type *base)
{
    base->TAMPER_QSCR |= RTC_TAMPER_QSCR_Q_CLEAR_MASK;
}
#endif /* FSL_FEATURE_RTC_HAS_TAMPER_QUEUE */

/*! @}*/

#endif

#if defined(FSL_FEATURE_RTC_HAS_SUBSYSTEM) && FSL_FEATURE_RTC_HAS_SUBSYSTEM
/*!
 * @name RTC subsystem Interface
 * @{
 */

/*!
 * @brief Enable the RTC wake-up timer.
 *
 * 1HZ clock out selected via call to API IRTC_ConfigClockOut in order for the subsecond
 * counter to synchronize with the RTC_SECONDS counter.
 *
 * @param base   RTC peripheral base address
 * @param enable Use/Un-use the sub-second counter.
 *               - true: Use RTC wake-up timer at the same time.
 *               - false: Un-use RTC wake-up timer, RTC only use the normal seconds timer by default.
 */
static inline void IRTC_EnableSubsecondCounter(RTC_Type *base, bool enable)
{
    if (enable)
    {
        base->SUBSECOND_CTRL |= RTC_SUBSECOND_CTRL_SUB_SECOND_CNT_EN_MASK;
    }
    else
    {
        base->SUBSECOND_CTRL &= ~RTC_SUBSECOND_CTRL_SUB_SECOND_CNT_EN_MASK;
    }
}

/*!
 * @brief Read the actual RTC sub-second COUNT value.
 *
 * @param base  RTC peripheral base address
 *
 * @return The actual RTC sub-second COUNT value.
 */
static inline uint32_t IRTC_GetSubsecondCount(RTC_Type *base)
{
    uint32_t a, b;

    /* Follow the RF document to read the RTC default seconds timer (1HZ) counter value. */
    do
    {
        a = base->SUBSECOND_CNT;
        b = base->SUBSECOND_CNT;
    } while (a != b);

    return b;
}
/*!
 * @brief Set countdown value to the RTC wake timer counter register.
 *
 * @param base        RTC peripheral base address
 * @param enable1kHzClk   Enable 1kHz clock source for the wake timer, else use the 32kHz clock.
 * @param wakeupValue The value to be loaded into the WAKE register in wake timer counter.
 */
static inline void IRTC_SetWakeupCount(RTC_Type *base, bool enable1kHzClk, uint32_t wakeupValue)
{
    /* Config whether enable the wakeup counter */
    uint32_t writeVal;
    writeVal              = base->WAKE_TIMER_CTRL;
    base->WAKE_TIMER_CTRL = RTC_WAKE_TIMER_CTRL_CLR_WAKE_TIMER_MASK;

    if (enable1kHzClk)
    {
        writeVal |= RTC_WAKE_TIMER_CTRL_OSC_DIV_ENA_MASK;
    }
    else
    {
        writeVal &= ~RTC_WAKE_TIMER_CTRL_OSC_DIV_ENA_MASK;
    }

    base->WAKE_TIMER_CTRL = writeVal;
    /* Set the start countdown value into the RTC WAKE register */
    base->WAKE_TIMER_CNT = wakeupValue;
}

/*!
 * @brief Read the actual value from the WAKE register value in RTC wake timer.
 *
 * @param base        RTC peripheral base address
 *
 * @return The actual value of the WAKE register value in wake timer counter.
 */
static inline uint32_t IRTC_GetWakeupCount(RTC_Type *base)
{
    /* Read current wake-up countdown value */
    return base->WAKE_TIMER_CNT;
}

/*! @}*/
#endif

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_IRTC_H_ */
