/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rtc.h"

/*
 * $Coverage Justification Reference$
 *
 * $Justification rtc_c_ref_1$
 * Month is always under 13 and checked by assert.
 *
 * $Justification rtc_c_ref_2$
 * Can't simulate tamper in unit test environment.
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rtc"
#endif

#define SECONDS_IN_A_DAY    (86400U)
#define SECONDS_IN_A_HOUR   (3600U)
#define SECONDS_IN_A_MINUTE (60U)
#define DAYS_IN_A_YEAR      (365U)
#define YEAR_RANGE_START    (1970U)
#define YEAR_RANGE_END      (2099U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Checks whether the date and time passed in is valid
 *
 * @param datetime Pointer to structure where the date and time details are stored
 *
 * @return Returns false if the date & time details are out of range; true if in range
 */
static bool RTC_CheckDatetimeFormat(const rtc_datetime_t *datetime);

/*!
 * @brief Converts time data from datetime to seconds
 *
 * @param datetime Pointer to datetime structure where the date and time details are stored
 *
 * @return The result of the conversion in seconds
 */
static uint32_t RTC_ConvertDatetimeToSeconds(const rtc_datetime_t *datetime);

/*!
 * @brief Converts time data from seconds to a datetime structure
 *
 * @param seconds  Seconds value that needs to be converted to datetime format
 * @param datetime Pointer to the datetime structure where the result of the conversion is stored
 */
static void RTC_ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime);

/*******************************************************************************
 * Code
 ******************************************************************************/
static bool RTC_CheckDatetimeFormat(const rtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Check year, month, hour, minute, seconds */
    if ((datetime->year < YEAR_RANGE_START) || (datetime->year > YEAR_RANGE_END) || (datetime->month > 12U) ||
        (datetime->month < 1U) || (datetime->hour >= 24U) || (datetime->minute >= 60U) || (datetime->second >= 60U))
    {
        /* If not correct then error*/
        return false;
    }

    /* Adjust the days in February for a leap year */
    if ((((datetime->year & 3U) == 0U) && (datetime->year % 100U != 0U)) || (datetime->year % 400U == 0U))
    {
        daysPerMonth[2] = 29U;
    }

    /* Check the validity of the day */
    if ((datetime->day > daysPerMonth[datetime->month]) || (datetime->day < 1U))
    {
        return false;
    }

    return true;
}

static uint32_t RTC_ConvertDatetimeToSeconds(const rtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    /* Number of days from begin of the non Leap-year*/
    /* Number of days from begin of the non Leap-year*/
    uint16_t monthDays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};
    uint32_t seconds;

    /* Compute number of days from 1970 till given year*/
    seconds = ((uint32_t)datetime->year - 1970U) * DAYS_IN_A_YEAR;
    /* Add leap year days */
    seconds += (((uint32_t)datetime->year / 4U) - (1970U / 4U));
    /* Add number of days till given month*/
    seconds += monthDays[datetime->month];
    /* Add days in given month. We subtract the current day as it is
     * represented in the hours, minutes and seconds field*/
    seconds += ((uint32_t)datetime->day - 1U);
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if ((0U == (datetime->year & 3U)) && (datetime->month <= 2U))
    {
        seconds--;
    }

    seconds = (seconds * SECONDS_IN_A_DAY) + ((uint32_t)datetime->hour * SECONDS_IN_A_HOUR) +
              ((uint32_t)datetime->minute * SECONDS_IN_A_MINUTE) + datetime->second;

    return seconds;
}

static void RTC_ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    uint32_t x;
    uint32_t secondsRemaining, days;
    uint16_t daysInYear;
    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Start with the seconds value that is passed in to be converted to date time format */
    secondsRemaining = seconds;

    /* Calcuate the number of days, we add 1 for the current day which is represented in the
     * hours and seconds field
     */
    days = secondsRemaining / SECONDS_IN_A_DAY + 1U;

    /* Update seconds left*/
    secondsRemaining = secondsRemaining % SECONDS_IN_A_DAY;

    /* Calculate the datetime hour, minute and second fields */
    datetime->hour   = (uint8_t)(secondsRemaining / SECONDS_IN_A_HOUR);
    secondsRemaining = secondsRemaining % SECONDS_IN_A_HOUR;
    datetime->minute = (uint8_t)(secondsRemaining / 60U);
    datetime->second = (uint8_t)(secondsRemaining % SECONDS_IN_A_MINUTE);

    /* Calculate year */
    daysInYear     = DAYS_IN_A_YEAR;
    datetime->year = YEAR_RANGE_START;
    while (days > daysInYear)
    {
        /* Decrease day count by a year and increment year by 1 */
        days -= daysInYear;
        datetime->year++;

        /* Adjust the number of days for a leap year */
        if (0U != (datetime->year & 3U))
        {
            daysInYear = DAYS_IN_A_YEAR;
        }
        else
        {
            daysInYear = DAYS_IN_A_YEAR + 1U;
        }
    }

    /* Adjust the days in February for a leap year */
    if (0U == (datetime->year & 3U))
    {
        daysPerMonth[2] = 29U;
    }

    /*
     * $Branch Coverage Justification$
     * (x > 12U) not covered. $ref rtc_c_ref_1$.
     */
    for (x = 1U; x <= 12U; x++)
    {
        if (days <= daysPerMonth[x])
        {
            datetime->month = (uint8_t)x;
            break;
        }
        else
        {
            days -= daysPerMonth[x];
        }
    }

    datetime->day = (uint8_t)days;
}

/*!
 * brief Ungates the RTC clock and configures the peripheral for basic operation.
 *
 * This function issues a software reset if the timer invalid flag is set.
 *
 * note This API should be called at the beginning of the application using the RTC driver.
 *
 * param base   RTC peripheral base address
 * param config Pointer to the user's RTC configuration structure.
 */
void RTC_Init(RTC_Type *base, const rtc_config_t *config)
{
    assert(NULL != config);

    uint32_t reg;

#if defined(RTC_CLOCKS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Rtc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* RTC_CLOCKS */

    /* Issue a software reset if timer is invalid */
    if ((uint32_t)kRTC_TimeInvalidFlag == (RTC_GetStatusFlags(base) & (uint32_t)kRTC_TimeInvalidFlag))
    {
        RTC_Reset(base);
    }

    reg = base->CR;
/* Setup the update mode and supervisor access mode */
#if !(defined(FSL_FEATURE_RTC_HAS_NO_CR_OSCE) && FSL_FEATURE_RTC_HAS_NO_CR_OSCE)
    reg &= ~(RTC_CR_UM_MASK | RTC_CR_SUP_MASK);
    reg |= RTC_CR_UM(config->updateMode) | RTC_CR_SUP(config->supervisorAccess);
#else
    reg &= ~RTC_CR_UM_MASK;
    reg |= RTC_CR_UM(config->updateMode);
#endif

#if defined(FSL_FEATURE_RTC_HAS_WAKEUP_PIN_SELECTION) && FSL_FEATURE_RTC_HAS_WAKEUP_PIN_SELECTION
    /* Setup the wakeup pin select */
    reg &= ~(RTC_CR_WPS_MASK);
    reg |= RTC_CR_WPS(config->wakeupSelect);
#endif /* FSL_FEATURE_RTC_HAS_WAKEUP_PIN */
    base->CR = reg;

    /* Configure the RTC time compensation register */
    base->TCR = (RTC_TCR_CIR(config->compensationInterval) | RTC_TCR_TCR(config->compensationTime));

#if defined(FSL_FEATURE_RTC_HAS_TSIC) && FSL_FEATURE_RTC_HAS_TSIC
    /* Configure RTC timer seconds interrupt to be generated once per second */
    base->IER &= ~(RTC_IER_TSIC_MASK | RTC_IER_TSIE_MASK);
#endif
}

/*!
 * brief Fills in the RTC config struct with the default settings.
 *
 * The default values are as follows.
 * code
 *    config->wakeupSelect = false;
 *    config->updateMode = false;
 *    config->supervisorAccess = false;
 *    config->compensationInterval = 0;
 *    config->compensationTime = 0;
 * endcode
 * param config Pointer to the user's RTC configuration structure.
 */
void RTC_GetDefaultConfig(rtc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Wakeup pin will assert if the RTC interrupt asserts or if the wakeup pin is turned on */
    config->wakeupSelect = false;
    /* Registers cannot be written when locked */
    config->updateMode = false;
    /* Non-supervisor mode write accesses are not supported and will generate a bus error */
    config->supervisorAccess = false;
    /* Compensation interval used by the crystal compensation logic */
    config->compensationInterval = 0;
    /* Compensation time used by the crystal compensation logic */
    config->compensationTime = 0;
}

/*!
 * brief Sets the RTC date and time according to the given time structure.
 *
 * The RTC counter must be stopped prior to calling this function because writes to the RTC
 * seconds register fail if the RTC counter is running.
 *
 * param base     RTC peripheral base address
 * param datetime Pointer to the structure where the date and time details are stored.
 *
 * return kStatus_Success: Success in setting the time and starting the RTC
 *         kStatus_InvalidArgument: Error because the datetime format is incorrect
 */
status_t RTC_SetDatetime(RTC_Type *base, const rtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    /* Return error if the time provided is not valid */
    if (!(RTC_CheckDatetimeFormat(datetime)))
    {
        return kStatus_InvalidArgument;
    }

    /* Set time in seconds */
    base->TSR = RTC_ConvertDatetimeToSeconds(datetime);

    return kStatus_Success;
}

/*!
 * brief Gets the RTC time and stores it in the given time structure.
 *
 * param base     RTC peripheral base address
 * param datetime Pointer to the structure where the date and time details are stored.
 */
void RTC_GetDatetime(RTC_Type *base, rtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    uint32_t seconds = 0;

    seconds = base->TSR;
    RTC_ConvertSecondsToDatetime(seconds, datetime);
}

/*!
 * brief Sets the RTC alarm time.
 *
 * The function checks whether the specified alarm time is greater than the present
 * time. If not, the function does not set the alarm and returns an error.
 *
 * param base      RTC peripheral base address
 * param alarmTime Pointer to the structure where the alarm time is stored.
 *
 * return kStatus_Success: success in setting the RTC alarm
 *         kStatus_InvalidArgument: Error because the alarm datetime format is incorrect
 *         kStatus_Fail: Error because the alarm time has already passed
 */
status_t RTC_SetAlarm(RTC_Type *base, const rtc_datetime_t *alarmTime)
{
    assert(NULL != alarmTime);

    uint32_t alarmSeconds = 0;
    uint32_t currSeconds  = 0;

    /* Return error if the alarm time provided is not valid */
    if (!(RTC_CheckDatetimeFormat(alarmTime)))
    {
        return kStatus_InvalidArgument;
    }

    alarmSeconds = RTC_ConvertDatetimeToSeconds(alarmTime);

    /* Get the current time */
    currSeconds = base->TSR;

    /* Return error if the alarm time has passed */
    if (alarmSeconds < currSeconds)
    {
        return kStatus_Fail;
    }

    /* Set alarm in seconds*/
    base->TAR = alarmSeconds;

    return kStatus_Success;
}

/*!
 * brief Returns the RTC alarm time.
 *
 * param base     RTC peripheral base address
 * param datetime Pointer to the structure where the alarm date and time details are stored.
 */
void RTC_GetAlarm(RTC_Type *base, rtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    uint32_t alarmSeconds = 0;

    /* Get alarm in seconds  */
    alarmSeconds = base->TAR;

    RTC_ConvertSecondsToDatetime(alarmSeconds, datetime);
}

/*!
 * brief Enables the selected RTC interrupts.
 *
 * param base RTC peripheral base address
 * param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::rtc_interrupt_enable_t
 */
void RTC_EnableInterrupts(RTC_Type *base, uint32_t mask)
{
    uint32_t tmp32 = 0U;

    /* RTC_IER */
    if (0U != ((uint32_t)kRTC_TimeInvalidInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TIIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_TimeOverflowInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TOIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_AlarmInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TAIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_SecondsInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TSIE_MASK;
    }
#if defined(FSL_FEATURE_RTC_HAS_MONOTONIC) && (FSL_FEATURE_RTC_HAS_MONOTONIC)
    if (0U != ((uint32_t)kRTC_MonotonicOverflowInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_MOIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_MONOTONIC */
    base->IER |= tmp32;

#if (defined(FSL_FEATURE_RTC_HAS_TIR) && FSL_FEATURE_RTC_HAS_TIR)
    tmp32 = 0U;

    /* RTC_TIR */
    if (0U != ((uint32_t)kRTC_TestModeInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_TMIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_FlashSecurityInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_FSIE_MASK;
    }
#if (defined(FSL_FEATURE_RTC_HAS_TIR_TPIE) && FSL_FEATURE_RTC_HAS_TIR_TPIE)
    if (0U != ((uint32_t)kRTC_TamperPinInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_TPIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_TPIE */
#if (defined(FSL_FEATURE_RTC_HAS_TIR_SIE) && FSL_FEATURE_RTC_HAS_TIR_SIE)
    if (0U != ((uint32_t)kRTC_SecurityModuleInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_SIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_SIE */
#if (defined(FSL_FEATURE_RTC_HAS_TIR_LCIE) && FSL_FEATURE_RTC_HAS_TIR_LCIE)
    if (0U != ((uint32_t)kRTC_LossOfClockInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_LCIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_LCIE */
    base->TIR |= tmp32;
#endif /* FSL_FEATURE_RTC_HAS_TIR */
}

/*!
 * brief Disables the selected RTC interrupts.
 *
 * param base RTC peripheral base address
 * param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::rtc_interrupt_enable_t
 */
void RTC_DisableInterrupts(RTC_Type *base, uint32_t mask)
{
    uint32_t tmp32 = 0U;

    /* RTC_IER */
    if (0U != ((uint32_t)kRTC_TimeInvalidInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TIIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_TimeOverflowInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TOIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_AlarmInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TAIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_SecondsInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_TSIE_MASK;
    }
#if defined(FSL_FEATURE_RTC_HAS_MONOTONIC) && (FSL_FEATURE_RTC_HAS_MONOTONIC)
    if (0U != ((uint32_t)kRTC_MonotonicOverflowInterruptEnable & mask))
    {
        tmp32 |= RTC_IER_MOIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_MONOTONIC */
    base->IER &= (uint32_t)(~tmp32);

#if (defined(FSL_FEATURE_RTC_HAS_TIR) && FSL_FEATURE_RTC_HAS_TIR)
    tmp32 = 0U;

    /* RTC_TIR */
    if (0U != ((uint32_t)kRTC_TestModeInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_TMIE_MASK;
    }
    if (0U != ((uint32_t)kRTC_FlashSecurityInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_FSIE_MASK;
    }
#if (defined(FSL_FEATURE_RTC_HAS_TIR_TPIE) && FSL_FEATURE_RTC_HAS_TIR_TPIE)
    if (0U != ((uint32_t)kRTC_TamperPinInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_TPIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_TPIE */
#if (defined(FSL_FEATURE_RTC_HAS_TIR_SIE) && FSL_FEATURE_RTC_HAS_TIR_SIE)
    if (0U != ((uint32_t)kRTC_SecurityModuleInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_SIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_SIE */
#if (defined(FSL_FEATURE_RTC_HAS_TIR_LCIE) && FSL_FEATURE_RTC_HAS_TIR_LCIE)
    if (0U != ((uint32_t)kRTC_LossOfClockInterruptEnable & mask))
    {
        tmp32 |= RTC_TIR_LCIE_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_LCIE */
    base->TIR &= (uint32_t)(~tmp32);
#endif /* FSL_FEATURE_RTC_HAS_TIR */
}

/*!
 * brief Gets the enabled RTC interrupts.
 *
 * param base RTC peripheral base address
 *
 * return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::rtc_interrupt_enable_t
 */
uint32_t RTC_GetEnabledInterrupts(RTC_Type *base)
{
    uint32_t tmp32 = 0U;

    /* RTC_IER */
    if (0U != (RTC_IER_TIIE_MASK & base->IER))
    {
        tmp32 |= (uint32_t)kRTC_TimeInvalidInterruptEnable;
    }
    if (0U != (RTC_IER_TOIE_MASK & base->IER))
    {
        tmp32 |= (uint32_t)kRTC_TimeOverflowInterruptEnable;
    }
    if (0U != (RTC_IER_TAIE_MASK & base->IER))
    {
        tmp32 |= (uint32_t)kRTC_AlarmInterruptEnable;
    }
    if (0U != (RTC_IER_TSIE_MASK & base->IER))
    {
        tmp32 |= (uint32_t)kRTC_SecondsInterruptEnable;
    }
#if defined(FSL_FEATURE_RTC_HAS_MONOTONIC) && (FSL_FEATURE_RTC_HAS_MONOTONIC)
    if (0U != (RTC_IER_MOIE_MASK & base->IER))
    {
        tmp32 |= (uint32_t)kRTC_MonotonicOverflowInterruptEnable;
    }
#endif /* FSL_FEATURE_RTC_HAS_MONOTONIC */

#if (defined(FSL_FEATURE_RTC_HAS_TIR) && FSL_FEATURE_RTC_HAS_TIR)
    /* RTC_TIR */
    if (0U != (RTC_TIR_TMIE_MASK & base->TIR))
    {
        tmp32 |= (uint32_t)kRTC_TestModeInterruptEnable;
    }
    if (0U != (RTC_TIR_FSIE_MASK & base->TIR))
    {
        tmp32 |= (uint32_t)kRTC_FlashSecurityInterruptEnable;
    }
#if (defined(FSL_FEATURE_RTC_HAS_TIR_TPIE) && FSL_FEATURE_RTC_HAS_TIR_TPIE)
    if (0U != (RTC_TIR_TPIE_MASK & base->TIR))
    {
        tmp32 |= (uint32_t)kRTC_TamperPinInterruptEnable;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_TPIE */
#if (defined(FSL_FEATURE_RTC_HAS_TIR_SIE) && FSL_FEATURE_RTC_HAS_TIR_SIE)
    if (0U != (RTC_TIR_SIE_MASK & base->TIR))
    {
        tmp32 |= (uint32_t)kRTC_SecurityModuleInterruptEnable;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_SIE */
#if (defined(FSL_FEATURE_RTC_HAS_TIR_LCIE) && FSL_FEATURE_RTC_HAS_TIR_LCIE)
    if (0U != (RTC_TIR_LCIE_MASK & base->TIR))
    {
        tmp32 |= (uint32_t)kRTC_LossOfClockInterruptEnable;
    }
#endif /* FSL_FEATURE_RTC_HAS_TIR_LCIE */
#endif /* FSL_FEATURE_RTC_HAS_TIR */

    return tmp32;
}

/*!
 * brief Gets the RTC status flags.
 *
 * param base RTC peripheral base address
 *
 * return The status flags. This is the logical OR of members of the
 *         enumeration ::rtc_status_flags_t
 */
uint32_t RTC_GetStatusFlags(RTC_Type *base)
{
    uint32_t tmp32 = 0U;

    /* RTC_SR */
    if (0U != (RTC_SR_TIF_MASK & base->SR))
    {
        tmp32 |= (uint32_t)kRTC_TimeInvalidFlag;
    }
    if (0U != (RTC_SR_TOF_MASK & base->SR))
    {
        tmp32 |= (uint32_t)kRTC_TimeOverflowFlag;
    }
    if (0U != (RTC_SR_TAF_MASK & base->SR))
    {
        tmp32 |= (uint32_t)kRTC_AlarmFlag;
    }
#if defined(FSL_FEATURE_RTC_HAS_MONOTONIC) && (FSL_FEATURE_RTC_HAS_MONOTONIC)
    if (0U != (RTC_SR_MOF_MASK & base->SR))
    {
        tmp32 |= (uint32_t)kRTC_MonotonicOverflowFlag;
    }
#endif /* FSL_FEATURE_RTC_HAS_MONOTONIC */
#if (defined(FSL_FEATURE_RTC_HAS_SR_TIDF) && FSL_FEATURE_RTC_HAS_SR_TIDF)
    /*
     * $Branch Coverage Justification$
     * (0U != (RTC_SR_TIDF_MASK & base->SR)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != (RTC_SR_TIDF_MASK & base->SR))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        tmp32 |= (uint32_t)kRTC_TamperInterruptDetectFlag;
    }
#endif /* FSL_FEATURE_RTC_HAS_SR_TIDF */

#if (defined(FSL_FEATURE_RTC_HAS_TDR) && FSL_FEATURE_RTC_HAS_TDR)
    /* RTC_TDR */
    /*
     * $Branch Coverage Justification$
     * (0U != (RTC_TDR_TMF_MASK & base->TDR)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != (RTC_TDR_TMF_MASK & base->TDR))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        tmp32 |= (uint32_t)kRTC_TestModeFlag;
    }
    if (0U != (RTC_TDR_FSF_MASK & base->TDR))
    {
        tmp32 |= (uint32_t)kRTC_FlashSecurityFlag;
    }
#if (defined(FSL_FEATURE_RTC_HAS_TDR_TPF) && FSL_FEATURE_RTC_HAS_TDR_TPF)
    /*
     * $Branch Coverage Justification$
     * (0U != (RTC_TDR_TPF_MASK & base->TDR)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != (RTC_TDR_TPF_MASK & base->TDR))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        tmp32 |= (uint32_t)kRTC_TamperPinFlag;
    }
#endif /* FSL_FEATURE_RTC_HAS_TDR_TPF */
#if (defined(FSL_FEATURE_RTC_HAS_TDR_STF) && FSL_FEATURE_RTC_HAS_TDR_STF)
    /*
     * $Branch Coverage Justification$
     * (0U != (RTC_TDR_STF_MASK & base->TDR)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != (RTC_TDR_STF_MASK & base->TDR))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        tmp32 |= (uint32_t)kRTC_SecurityTamperFlag;
    }
#endif /* FSL_FEATURE_RTC_HAS_TDR_STF */
#if (defined(FSL_FEATURE_RTC_HAS_TDR_LCTF) && FSL_FEATURE_RTC_HAS_TDR_LCTF)
    /*
     * $Branch Coverage Justification$
     * (0U != (RTC_TDR_LCTF_MASK & base->TDR)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != (RTC_TDR_LCTF_MASK & base->TDR))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        tmp32 |= (uint32_t)kRTC_LossOfClockTamperFlag;
    }
#endif /* FSL_FEATURE_RTC_HAS_TDR_LCTF */
#endif /* FSL_FEATURE_RTC_HAS_TDR */

    return tmp32;
}

/*!
 * brief  Clears the RTC status flags.
 *
 * param base RTC peripheral base address
 * param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::rtc_status_flags_t
 */
void RTC_ClearStatusFlags(RTC_Type *base, uint32_t mask)
{
    /* The alarm flag is cleared by writing to the TAR register */
    if (0U != (mask & (uint32_t)kRTC_AlarmFlag))
    {
        base->TAR = 0U;
    }

    /* The timer overflow flag is cleared by initializing the TSR register.
     * The time counter should be disabled for this write to be successful
     */
    if (0U != (mask & (uint32_t)kRTC_TimeOverflowFlag))
    {
        base->TSR = 1U;
    }

    /* The timer overflow flag is cleared by initializing the TSR register.
     * The time counter should be disabled for this write to be successful
     */
    if (0U != (mask & (uint32_t)kRTC_TimeInvalidFlag))
    {
        base->TSR = 1U;
    }

#if (defined(FSL_FEATURE_RTC_HAS_TDR) && FSL_FEATURE_RTC_HAS_TDR)
    /* To clear, write logic one to this flag after exiting from all test modes */
    /*
     * $Branch Coverage Justification$
     * (0U != ((uint32_t)kRTC_TestModeFlag & mask)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != ((uint32_t)kRTC_TestModeFlag & mask))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        base->TDR = RTC_TDR_TMF_MASK;
    }
    /* To clear, write logic one to this flag after flash security is enabled */
    /*
     * $Branch Coverage Justification$
     * (0U != ((uint32_t)kRTC_FlashSecurityFlag & mask)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != ((uint32_t)kRTC_FlashSecurityFlag & mask))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        base->TDR = RTC_TDR_FSF_MASK;
    }
#if (defined(FSL_FEATURE_RTC_HAS_TDR_TPF) && FSL_FEATURE_RTC_HAS_TDR_TPF)
    /* To clear, write logic one to the corresponding flag after that tamper pin negates */
    /*
     * $Branch Coverage Justification$
     * (0U != ((uint32_t)kRTC_TamperPinFlag & mask)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != ((uint32_t)kRTC_TamperPinFlag & mask))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        base->TDR = RTC_TDR_TPF_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TDR_TPF */
#if (defined(FSL_FEATURE_RTC_HAS_TDR_STF) && FSL_FEATURE_RTC_HAS_TDR_STF)
    /* To clear, write logic one to this flag after security module has negated its tamper detect */
    /*
     * $Branch Coverage Justification$
     * (0U != ((uint32_t)kRTC_SecurityTamperFlag & mask)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != ((uint32_t)kRTC_SecurityTamperFlag & mask))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        base->TDR = RTC_TDR_STF_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TDR_STF */
#if (defined(FSL_FEATURE_RTC_HAS_TDR_LCTF) && FSL_FEATURE_RTC_HAS_TDR_LCTF)
    /* To clear, write logic one to this flag after loss of clock negates */
    /*
     * $Branch Coverage Justification$
     * (0U != ((uint32_t)kRTC_LossOfClockTamperFlag & mask)) not covered. $ref rtc_c_ref_2$.
     */
    if (0U != ((uint32_t)kRTC_LossOfClockTamperFlag & mask))
    {
        /*
        * $Line Coverage Justification$
        * $ref rtc_c_ref_2$.
        */
        base->TDR = RTC_TDR_LCTF_MASK;
    }
#endif /* FSL_FEATURE_RTC_HAS_TDR_LCTF */
#endif /* FSL_FEATURE_RTC_HAS_TDR */
}

#if defined(FSL_FEATURE_RTC_HAS_MONOTONIC) && (FSL_FEATURE_RTC_HAS_MONOTONIC)

/*!
 * brief Reads the values of the Monotonic Counter High and Monotonic Counter Low and returns
 *        them as a single value.
 *
 * param base    RTC peripheral base address
 * param counter Pointer to variable where the value is stored.
 */
void RTC_GetMonotonicCounter(RTC_Type *base, uint64_t *counter)
{
    uint64_t u64temp;

    assert(NULL != counter);

    u64temp  = (uint64_t)base->MCLR;
    *counter = (((uint64_t)base->MCHR << 32U) | u64temp);
}

/*!
 * brief Writes values Monotonic Counter High and Monotonic Counter Low by decomposing
 *        the given single value. The Monotonic Overflow Flag in RTC_SR is cleared due to the API.
 *
 * param base    RTC peripheral base address
 * param counter Counter value
 */
void RTC_SetMonotonicCounter(RTC_Type *base, uint64_t counter)
{
    /* Prepare to initialize the register with the new value written */
    base->MER &= ~RTC_MER_MCE_MASK;

    base->MCHR = (uint32_t)((counter) >> 32);
    base->MCLR = (uint32_t)(counter);
}

/*!
 * brief Increments the Monotonic Counter by one.
 *
 * Increments the Monotonic Counter (registers RTC_MCLR and RTC_MCHR accordingly) by setting
 * the monotonic counter enable (MER[MCE]) and then writing to the RTC_MCLR register. A write to the
 * monotonic counter low that causes it to overflow also increments the monotonic counter high.
 *
 * param base RTC peripheral base address
 *
 * return kStatus_Success: success
 *         kStatus_Fail: error occurred, either time invalid or monotonic overflow flag was found
 */
status_t RTC_IncrementMonotonicCounter(RTC_Type *base)
{
    if (0U != (base->SR & (RTC_SR_MOF_MASK | RTC_SR_TIF_MASK)))
    {
        return kStatus_Fail;
    }

    /* Prepare to switch to increment mode */
    base->MER |= RTC_MER_MCE_MASK;
    /* Write anything so the counter increments*/
    base->MCLR = 1U;

    return kStatus_Success;
}

#endif /* FSL_FEATURE_RTC_HAS_MONOTONIC */
