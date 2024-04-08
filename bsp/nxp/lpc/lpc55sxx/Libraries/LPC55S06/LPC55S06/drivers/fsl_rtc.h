/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_RTC_H_
#define _FSL_RTC_H_

#include "fsl_common.h"

/*!
 * @addtogroup rtc
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_RTC_DRIVER_VERSION (MAKE_VERSION(2, 1, 2)) /*!< Version 2.1.2 */
/*@}*/

/*! @brief List of RTC interrupts */
typedef enum _rtc_interrupt_enable
{
    kRTC_AlarmInterruptEnable  = RTC_CTRL_ALARMDPD_EN_MASK, /*!< Alarm interrupt.*/
    kRTC_WakeupInterruptEnable = RTC_CTRL_WAKEDPD_EN_MASK   /*!< Wake-up interrupt.*/
} rtc_interrupt_enable_t;

/*! @brief List of RTC flags */
typedef enum _rtc_status_flags
{
    kRTC_AlarmFlag  = RTC_CTRL_ALARM1HZ_MASK, /*!< Alarm flag*/
    kRTC_WakeupFlag = RTC_CTRL_WAKE1KHZ_MASK  /*!< 1kHz wake-up timer flag*/
} rtc_status_flags_t;

/*! @brief Structure is used to hold the date and time */
typedef struct _rtc_datetime
{
    uint16_t year;  /*!< Range from 1970 to 2099.*/
    uint8_t month;  /*!< Range from 1 to 12.*/
    uint8_t day;    /*!< Range from 1 to 31 (depending on month).*/
    uint8_t hour;   /*!< Range from 0 to 23.*/
    uint8_t minute; /*!< Range from 0 to 59.*/
    uint8_t second; /*!< Range from 0 to 59.*/
} rtc_datetime_t;

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
 * @brief Un-gate the RTC clock and enable the RTC oscillator.
 *
 * @note This API should be called at the beginning of the application using the RTC driver.
 *
 * @param base RTC peripheral base address
 */
void RTC_Init(RTC_Type *base);

/*!
 * @brief Stop the timer and gate the RTC clock
 *
 * @param base RTC peripheral base address
 */
static inline void RTC_Deinit(RTC_Type *base)
{
    /* Stop the RTC timer */
    base->CTRL &= ~RTC_CTRL_RTC_EN_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the module clock */
    CLOCK_DisableClock(kCLOCK_Rtc);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*! @}*/

/*!
 * @name Current Time & Alarm
 * @{
 */

/*!
 * @brief Set the RTC date and time according to the given time structure.
 *
 * The RTC counter must be stopped prior to calling this function as writes to the RTC
 * seconds register will fail if the RTC counter is running.
 *
 * @param base     RTC peripheral base address
 * @param datetime Pointer to structure where the date and time details to set are stored
 *
 * @return kStatus_Success: Success in setting the time and starting the RTC
 *         kStatus_InvalidArgument: Error because the datetime format is incorrect
 */
status_t RTC_SetDatetime(RTC_Type *base, const rtc_datetime_t *datetime);

/*!
 * @brief Get the RTC time and stores it in the given time structure.
 *
 * @param base     RTC peripheral base address
 * @param datetime Pointer to structure where the date and time details are stored.
 */
void RTC_GetDatetime(RTC_Type *base, rtc_datetime_t *datetime);

/*!
 * @brief Set the RTC alarm time
 *
 * The function checks whether the specified alarm time is greater than the present
 * time. If not, the function does not set the alarm and returns an error.
 *
 * @param base      RTC peripheral base address
 * @param alarmTime Pointer to structure where the alarm time is stored.
 *
 * @return kStatus_Success: success in setting the RTC alarm
 *         kStatus_InvalidArgument: Error because the alarm datetime format is incorrect
 *         kStatus_Fail: Error because the alarm time has already passed
 */
status_t RTC_SetAlarm(RTC_Type *base, const rtc_datetime_t *alarmTime);

/*!
 * @brief Return the RTC alarm time.
 *
 * @param base     RTC peripheral base address
 * @param datetime Pointer to structure where the alarm date and time details are stored.
 */
void RTC_GetAlarm(RTC_Type *base, rtc_datetime_t *datetime);

/*! @}*/

/*!
 * @name RTC wake-up timer (1KHZ) Enable
 * @{
 */

/*!
 * @brief Enable the RTC wake-up timer (1KHZ).
 *
 * After calling this function, the RTC driver will use/un-use the RTC wake-up (1KHZ) at the same time.
 *
 * @param base   RTC peripheral base address
 * @param enable Use/Un-use the RTC wake-up timer.
 *               - true: Use RTC wake-up timer at the same time.
 *               - false: Un-use RTC wake-up timer, RTC only use the normal seconds timer by default.
 */
static inline void RTC_EnableWakeupTimer(RTC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= RTC_CTRL_RTC1KHZ_EN_MASK;
    }
    else
    {
        base->CTRL &= ~RTC_CTRL_RTC1KHZ_EN_MASK;
    }
}

/*!
 * @brief Get the enabled status of the RTC wake-up timer (1KHZ).
 *

 * @param base RTC peripheral base address
 *
 * @return The enabled status of RTC wake-up timer (1KHZ).
 */
static inline uint32_t RTC_GetEnabledWakeupTimer(RTC_Type *base)
{
    return (base->CTRL & RTC_CTRL_RTC1KHZ_EN_MASK);
}

/*! @}*/

/*!
 * @brief Set the RTC seconds timer (1HZ) MATCH value.
 *
 * @param base        RTC peripheral base address
 * @param matchValue  The value to be set into the RTC MATCH register
 */
static inline void RTC_SetSecondsTimerMatch(RTC_Type *base, uint32_t matchValue)
{
    /* Set the start match value into the default RTC seconds timer (1HZ). */
    base->MATCH = matchValue;
}

/*!
 * @brief Read actual RTC seconds timer (1HZ) MATCH value.
 *
 * @param base        RTC peripheral base address
 *
 * @return The actual RTC seconds timer (1HZ) MATCH value.
 */
static inline uint32_t RTC_GetSecondsTimerMatch(RTC_Type *base)
{
    /* Read the RTC default seconds timer (1HZ) MATCH value. */
    return base->MATCH;
}

/*!
 * @brief Set the RTC seconds timer (1HZ) COUNT value.
 *
 * @param base        RTC peripheral base address
 * @param countValue  The value to be loaded into the RTC COUNT register
 */
static inline void RTC_SetSecondsTimerCount(RTC_Type *base, uint32_t countValue)
{
    /* Set the start count value into the default RTC seconds timer (1HZ). */
    base->COUNT = countValue;
}

/*!
 * @brief Read the actual RTC seconds timer (1HZ) COUNT value.
 *
 * @param base  RTC peripheral base address
 *
 * @return The actual RTC seconds timer (1HZ) COUNT value.
 */
static inline uint32_t RTC_GetSecondsTimerCount(RTC_Type *base)
{
    uint32_t a, b;

    /* Follow the RF document to read the RTC default seconds timer (1HZ) counter value. */
    do
    {
        a = base->COUNT;
        b = base->COUNT;
    } while (a != b);

    return b;
}

/*!
 * @brief Enable the RTC wake-up timer (1KHZ) and set countdown value to the RTC WAKE register.
 *
 * @param base        RTC peripheral base address
 * @param wakeupValue The value to be loaded into the WAKE register in RTC wake-up timer (1KHZ).
 */
static inline void RTC_SetWakeupCount(RTC_Type *base, uint16_t wakeupValue)
{
    /* Use the RTC wake-up timer (1KHZ) */
    base->CTRL |= RTC_CTRL_RTC1KHZ_EN_MASK;

    /* Set the start countdown value into the RTC WAKE register */
    base->WAKE = RTC_WAKE_VAL((uint32_t)wakeupValue);
}

/*!
 * @brief Read the actual value from the WAKE register value in RTC wake-up timer (1KHZ).
 *
 * @param base        RTC peripheral base address
 *
 * @return The actual value of the WAKE register value in RTC wake-up timer (1HZ).
 */
static inline uint16_t RTC_GetWakeupCount(RTC_Type *base)
{
    /* Read current wake-up countdown value */
    return (uint16_t)((base->WAKE & RTC_WAKE_VAL_MASK) >> RTC_WAKE_VAL_SHIFT);
}

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enable the wake-up timer interrupt from deep power down mode.
 *
 * @param base RTC peripheral base address
 * @param enable Enable/Disable wake-up timer interrupt from deep power down mode.
 *               - true: Enable wake-up timer interrupt from deep power down mode.
 *               - false: Disable wake-up timer interrupt from deep power down mode.
 */
static inline void RTC_EnableWakeUpTimerInterruptFromDPD(RTC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= RTC_CTRL_WAKEDPD_EN_MASK;
    }
    else
    {
        base->CTRL &= ~RTC_CTRL_WAKEDPD_EN_MASK;
    }
}

/*!
 * @brief Enable the alarm timer interrupt from deep power down mode.
 *
 * @param base RTC peripheral base address
 * @param enable Enable/Disable alarm timer interrupt from deep power down mode.
 *               - true: Enable alarm timer interrupt from deep power down mode.
 *               - false: Disable alarm timer interrupt from deep power down mode.
 */
static inline void RTC_EnableAlarmTimerInterruptFromDPD(RTC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= RTC_CTRL_ALARMDPD_EN_MASK;
    }
    else
    {
        base->CTRL &= ~RTC_CTRL_ALARMDPD_EN_MASK;
    }
}

/*!
 * @brief Enables the selected RTC interrupts.
 * @deprecated Do not use this function.  It has been superceded by @ref RTC_EnableAlarmTimerInterruptFromDPD
 *  and RTC_EnableWakeUpTimerInterruptFromDPD
 *
 * @param base RTC peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::rtc_interrupt_enable_t
 */
static inline void RTC_EnableInterrupts(RTC_Type *base, uint32_t mask)
{
    uint32_t reg = base->CTRL;

    /* Clear flag bits to prevent accidentally clearing anything when writing back */
    reg &= ~(RTC_CTRL_ALARM1HZ_MASK | RTC_CTRL_WAKE1KHZ_MASK);
    reg |= mask;

    base->CTRL = reg;
}

/*!
 * @brief Disables the selected RTC interrupts.
 * @deprecated Do not use this function.  It has been superceded by @ref RTC_EnableAlarmTimerInterruptFromDPD
 *  and RTC_EnableWakeUpTimerInterruptFromDPD
 *
 * @param base RTC peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::rtc_interrupt_enable_t
 */
static inline void RTC_DisableInterrupts(RTC_Type *base, uint32_t mask)
{
    uint32_t reg = base->CTRL;

    /* Clear flag bits to prevent accidentally clearing anything when writing back */
    reg &= ~(RTC_CTRL_ALARM1HZ_MASK | RTC_CTRL_WAKE1KHZ_MASK | mask);

    base->CTRL = reg;
}

/*!
 * @brief Get the enabled RTC interrupts.
 * @deprecated Do not use this function.  It will be deleted in next release version.
 *
 * @param base RTC peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::rtc_interrupt_enable_t
 */
static inline uint32_t RTC_GetEnabledInterrupts(RTC_Type *base)
{
    return (base->CTRL & (RTC_CTRL_ALARMDPD_EN_MASK | RTC_CTRL_WAKEDPD_EN_MASK));
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Get the RTC status flags
 *
 * @param base RTC peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::rtc_status_flags_t
 */
static inline uint32_t RTC_GetStatusFlags(RTC_Type *base)
{
    return (base->CTRL & (RTC_CTRL_ALARM1HZ_MASK | RTC_CTRL_WAKE1KHZ_MASK));
}

/*!
 * @brief  Clear the RTC status flags.
 *
 * @param base RTC peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::rtc_status_flags_t
 */
static inline void RTC_ClearStatusFlags(RTC_Type *base, uint32_t mask)
{
    uint32_t reg = base->CTRL;

    /* Clear flag bits to prevent accidentally clearing anything when writing back */
    reg &= ~(RTC_CTRL_ALARM1HZ_MASK | RTC_CTRL_WAKE1KHZ_MASK);

    /* Write 1 to the flags we wish to clear */
    reg |= mask;

    base->CTRL = reg;
}

/*! @}*/

/*!
 * @name Timer Enable
 * @{
 */

/*!
 * @brief Enable the RTC timer counter.
 *
 * After calling this function, the RTC inner counter increments once a second when only using the RTC seconds timer
 * (1hz), while the RTC inner wake-up timer countdown once a millisecond when using RTC wake-up timer (1KHZ) at the
 * same time. RTC timer contain two timers, one is the RTC normal seconds timer, the other one is the RTC wake-up timer,
 * the RTC enable bit is the master switch for the whole RTC timer, so user can use the RTC seconds (1HZ) timer
 * independly, but they can't use the RTC wake-up timer (1KHZ) independently.
 *
 * @param base RTC peripheral base address
 * @param enable Enable/Disable RTC Timer counter.
 *               - true: Enable RTC Timer counter.
 *               - false: Disable RTC Timer counter.
 */
static inline void RTC_EnableTimer(RTC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= RTC_CTRL_RTC_EN_MASK;
    }
    else
    {
        base->CTRL &= ~RTC_CTRL_RTC_EN_MASK;
    }
}

/*!
 * @brief Starts the RTC time counter.
 * @deprecated Do not use this function.  It has been superceded by @ref RTC_EnableTimer
 *
 * After calling this function, the timer counter increments once a second provided SR[TOF] or
 * SR[TIF] are not set.
 *
 * @param base RTC peripheral base address
 */
static inline void RTC_StartTimer(RTC_Type *base)
{
    base->CTRL |= RTC_CTRL_RTC_EN_MASK;
}

/*!
 * @brief Stops the RTC time counter.
 * @deprecated Do not use this function.  It has been superceded by @ref RTC_EnableTimer
 *
 * RTC's seconds register can be written to only when the timer is stopped.
 *
 * @param base RTC peripheral base address
 */
static inline void RTC_StopTimer(RTC_Type *base)
{
    base->CTRL &= ~RTC_CTRL_RTC_EN_MASK;
}

/*! @}*/

/*!
 * @brief Perform a software reset on the RTC module.
 *
 * This resets all RTC registers to their reset value. The bit is cleared by software explicitly clearing it.
 *
 * @param base RTC peripheral base address
 */
static inline void RTC_Reset(RTC_Type *base)
{
    base->CTRL |= RTC_CTRL_SWRESET_MASK;
    base->CTRL &= ~RTC_CTRL_SWRESET_MASK;
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_RTC_H_ */
