/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_irtc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.irtc"
#endif

#define IRTC_BASE_YEAR   (2112U)
#define YEAR_RANGE_START (1984U) /* Valid values for year range from -128 to 127; 2112 - 128 */
#define YEAR_RANGE_END   (2239U) /* Valid values for year range from -128 to 127; 2112 + 127 */

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
static bool IRTC_CheckDatetimeFormat(const irtc_datetime_t *datetime);

/*******************************************************************************
 * Code
 ******************************************************************************/
static bool IRTC_CheckDatetimeFormat(const irtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    bool fgRet = true;

    /* Table of days in a month for a non leap year */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Check year, month, hour, minute, seconds */
    if ((datetime->year < YEAR_RANGE_START) || (datetime->year > YEAR_RANGE_END) || (datetime->month > 12U) ||
        (datetime->month < 1U) || (datetime->weekDay >= 7U) || (datetime->hour >= 24U) || (datetime->minute >= 60U) ||
        (datetime->second >= 60U))
    {
        /* If not correct then error*/
        fgRet = false;
    }
    else
    {
        /* Adjust the days in February for a leap year */
        if (((0U == (datetime->year & 3U)) && (0U != (datetime->year % 100U))) || (0U == (datetime->year % 400U)))
        {
            daysPerMonth[2] = 29U;
        }

        /* Check the validity of the day */
        if ((datetime->day > daysPerMonth[datetime->month]) || (datetime->day < 1U))
        {
            fgRet = false;
        }
    }
    return fgRet;
}

/*!
 * brief Ungates the IRTC clock and configures the peripheral for basic operation.
 *
 * This function initiates a soft-reset of the IRTC module, this has not effect on DST,
 * calendaring, standby time and tamper detect registers.
 *
 * note This API should be called at the beginning of the application using the IRTC driver.
 *
 * param base   IRTC peripheral base address
 * param config Pointer to user's IRTC config structure.
 *
 * return kStatus_Fail if we cannot disable register write protection
 */
status_t IRTC_Init(RTC_Type *base, const irtc_config_t *config)
{
    assert(NULL != config);

    uint16_t reg;
    status_t status = kStatus_Success;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Rtc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FSL_FEATURE_RTC_HAS_RESET) && FSL_FEATURE_RTC_HAS_RESET
    RESET_PeripheralReset(kRTC_RST_SHIFT_RSTn);
#endif

    /* Unlock to allow register write operation */
    if (kStatus_Success == IRTC_SetWriteProtection(base, false))
    {
        /* Issue a software reset */
        IRTC_Reset(base);

#if !defined(FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE) || (!FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE)
        /* Setup the wakeup pin select */
        if (config->wakeupSelect)
        {
            base->CTRL2 |= RTC_CTRL2_WAKEUP_MODE_MASK;
        }
        else
        {
            base->CTRL2 &= ~(uint16_t)RTC_CTRL2_WAKEUP_MODE_MASK;
        }
#endif
        /* Setup alarm match operation, sampling clock operation in standby mode, 16.384kHz RTC clock and selected clock outout to other peripherals */
        reg = base->CTRL;
        reg &= ~(
#if !defined(FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK) || (!FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK)
               (uint16_t)RTC_CTRL_TIMER_STB_MASK_MASK |
#endif
#if defined(FSL_FEATURE_RTC_HAS_CLOCK_SELECT) && FSL_FEATURE_RTC_HAS_CLOCK_SELECT
               (uint16_t)RTC_CTRL_CLK_SEL_MASK |
#endif
#if defined(FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE) && FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE
               (uint16_t)RTC_CTRL_CLKO_DIS_MASK |
#endif
               (uint16_t)RTC_CTRL_ALM_MATCH_MASK);
        reg |= (
#if !defined(FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK) || (!FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK)
               RTC_CTRL_TIMER_STB_MASK(config->timerStdMask) |
#endif
#if defined(FSL_FEATURE_RTC_HAS_CLOCK_SELECT) && FSL_FEATURE_RTC_HAS_CLOCK_SELECT
               RTC_CTRL_CLK_SEL(config->clockSelect) |
#endif
#if defined(FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE) && FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE
               RTC_CTRL_CLKO_DIS(config->disableClockOutput) |
#endif
               RTC_CTRL_ALM_MATCH(config->alrmMatch));
        base->CTRL = reg;
    }
    else
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Fill in the IRTC config struct with the default settings
 *
 * The default values are:
 * code
 *    config->wakeupSelect = true;
 *    config->timerStdMask = false;
 *    config->alrmMatch = kRTC_MatchSecMinHr;
 * endcode
 * param config Pointer to user's IRTC config structure.
 */
void IRTC_GetDefaultConfig(irtc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

#if !defined(FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE) || (!FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE)
    /* Tamper pin 0 is used as a wakeup/hibernation pin */
    config->wakeupSelect = true;
#endif

#if !defined(FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK) || (!FSL_FEATURE_RTC_HAS_NO_TIMER_STB_MASK)
    /* Sampling clock are not gated when in standby mode */
    config->timerStdMask = false;
#endif

    /* Only seconds, minutes and hours are matched when generating an alarm */
    config->alrmMatch = kRTC_MatchSecMinHr;

#if defined(FSL_FEATURE_RTC_HAS_CLOCK_SELECT) && FSL_FEATURE_RTC_HAS_CLOCK_SELECT
    /* 16.384kHz clock is selected */
    config->clockSelect = kIRTC_Clk16K;
#endif

#if defined(FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE) && FSL_FEATURE_RTC_HAS_CLOCK_OUTPUT_DISABLE
    /* The selected clock is not output to other peripherals */
    config->disableClockOutput = true;
#endif
}

/*!
 * brief Sets the IRTC date and time according to the given time structure.
 *
 * The IRTC counter is started after the time is set.
 *
 * param base     IRTC peripheral base address
 * param datetime Pointer to structure where the date and time details to set are stored
 *
 * return kStatus_Success: success in setting the time and starting the IRTC
 *         kStatus_InvalidArgument: failure. An error occurs because the datetime format is incorrect.
 */
status_t IRTC_SetDatetime(RTC_Type *base, const irtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    status_t status = kStatus_Success;

    /* Return error if the time provided is not valid */
    if (IRTC_CheckDatetimeFormat(datetime))
    {
        /* The register stores the offset in years from the base year of 2112 */
        if (datetime->year < IRTC_BASE_YEAR)
        {
            /* Values for years less than the base year range from -128 to 1 */
            base->YEARMON =
                RTC_YEARMON_YROFST(0x100U + datetime->year - IRTC_BASE_YEAR) | RTC_YEARMON_MON_CNT(datetime->month);
        }
        else
        {
            /* Values for years greater or equal to the base year range from 0 to 127 */
            base->YEARMON = RTC_YEARMON_YROFST(datetime->year - IRTC_BASE_YEAR) | RTC_YEARMON_MON_CNT(datetime->month);
        }
        /* Update the Day Count and Day of the week field */
        base->DAYS = RTC_DAYS_DOW(datetime->weekDay) | RTC_DAYS_DAY_CNT(datetime->day);

        /* Update hour and minute field */
        base->HOURMIN = RTC_HOURMIN_HOUR_CNT(datetime->hour) | RTC_HOURMIN_MIN_CNT(datetime->minute);

        /* Update the seconds register */
        base->SECONDS = RTC_SECONDS_SEC_CNT(datetime->second);
    }
    else
    {
        status = kStatus_InvalidArgument;
    }

    return status;
}

/*!
 * brief Gets the IRTC time and stores it in the given time structure.
 *
 * param base     IRTC peripheral base address
 * param datetime Pointer to structure where the date and time details are stored.
 */
void IRTC_GetDatetime(RTC_Type *base, irtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    uint16_t temp = base->YEARMON;

    datetime->year =
        (uint16_t)IRTC_BASE_YEAR + (uint16_t)((int8_t)(uint8_t)((temp >> RTC_YEARMON_YROFST_SHIFT) & 0xFFU));
    datetime->month = (uint8_t)temp & RTC_YEARMON_MON_CNT_MASK;

    temp              = base->DAYS;
    datetime->weekDay = (uint8_t)((temp & RTC_DAYS_DOW_MASK) >> RTC_DAYS_DOW_SHIFT);
    datetime->day     = (uint8_t)temp & RTC_DAYS_DAY_CNT_MASK;

    temp             = base->HOURMIN;
    datetime->hour   = (uint8_t)((temp & RTC_HOURMIN_HOUR_CNT_MASK) >> RTC_HOURMIN_HOUR_CNT_SHIFT);
    datetime->minute = (uint8_t)temp & RTC_HOURMIN_MIN_CNT_MASK;

    datetime->second = (uint8_t)(base->SECONDS) & RTC_SECONDS_SEC_CNT_MASK;
}

/*!
 * brief Sets the IRTC alarm time
 *
 * param base      RTC peripheral base address
 * param alarmTime Pointer to structure where the alarm time is stored.
 *
 * note weekDay field of alarmTime is not used during alarm match and should be set to 0
 *
 * return kStatus_Success: success in setting the alarm
 *         kStatus_InvalidArgument: error in setting the alarm. Error occurs because the alarm
 *                                  datetime format is incorrect.
 */
status_t IRTC_SetAlarm(RTC_Type *base, const irtc_datetime_t *alarmTime)
{
    assert(NULL != alarmTime);

    status_t status = kStatus_Success;

    /* Return error if the alarm time provided is not valid */
    if (IRTC_CheckDatetimeFormat(alarmTime))
    {
        /* Set the alarm year */
        if (alarmTime->year < IRTC_BASE_YEAR)
        {
            base->ALM_YEARMON = RTC_ALM_YEARMON_ALM_YEAR(0x100U + alarmTime->year - IRTC_BASE_YEAR) |
                                RTC_ALM_YEARMON_ALM_MON(alarmTime->month);
        }
        else
        {
            base->ALM_YEARMON =
                RTC_ALM_YEARMON_ALM_YEAR(alarmTime->year - IRTC_BASE_YEAR) | RTC_ALM_YEARMON_ALM_MON(alarmTime->month);
        }

        /* Set the alarm day */
        base->ALM_DAYS = RTC_ALM_DAYS_ALM_DAY(alarmTime->day);

        /* Set the alarm hour and minute */
        base->ALM_HOURMIN = RTC_ALM_HOURMIN_ALM_HOUR(alarmTime->hour) | RTC_ALM_HOURMIN_ALM_MIN(alarmTime->minute);

        /* Set the alarm seconds */
        base->ALM_SECONDS = RTC_ALM_SECONDS_ALM_SEC(alarmTime->second);
    }
    else
    {
        status = kStatus_InvalidArgument;
    }

    return status;
}

/*!
 * brief Returns the IRTC alarm time.
 *
 * param base     RTC peripheral base address
 * param datetime Pointer to structure where the alarm date and time details are stored.
 */
void IRTC_GetAlarm(RTC_Type *base, irtc_datetime_t *datetime)
{
    assert(NULL != datetime);

    uint16_t temp = base->ALM_YEARMON;

    datetime->year =
        (uint16_t)IRTC_BASE_YEAR + (uint16_t)((int8_t)(uint8_t)((temp >> RTC_ALM_YEARMON_ALM_YEAR_SHIFT) & 0xFFU));
    datetime->month = (uint8_t)temp & RTC_ALM_YEARMON_ALM_MON_MASK;

    datetime->day = (uint8_t)(base->ALM_DAYS) & RTC_ALM_DAYS_ALM_DAY_MASK;

    temp             = base->ALM_HOURMIN;
    datetime->hour   = (uint8_t)((temp & RTC_ALM_HOURMIN_ALM_HOUR_MASK) >> RTC_ALM_HOURMIN_ALM_HOUR_SHIFT);
    datetime->minute = (uint8_t)temp & RTC_ALM_HOURMIN_ALM_MIN_MASK;

    datetime->second = (uint8_t)(base->ALM_SECONDS) & RTC_ALM_SECONDS_ALM_SEC_MASK;
}

/*!
 * brief Locks or unlocks IRTC registers for write access.
 *
 * note When the registers are unlocked, they remain in unlocked state for
 * 2 seconds, after which they are locked automatically. After
 * power-on-reset, the registers come out unlocked and they are locked
 * automatically 15 seconds after power on.
 *
 * param base IRTC peripheral base address
 * param lock true: Lock IRTC registers; false: Unlock IRTC registers.
 *
 * return kStatus_Success: if lock or unlock operation is successful
 *         kStatus_Fail: if lock or unlock operation fails even after multiple retry attempts
 */
status_t IRTC_SetWriteProtection(RTC_Type *base, bool lock)
{
    /* Retry before giving up */
    uint8_t repeatProtectSequence = 0xFFU;
    status_t status               = kStatus_Success;

    if (!lock)
    {
        /* Unlock IRTC registers */
        while ((0U != (base->STATUS & (uint16_t)RTC_STATUS_WRITE_PROT_EN_MASK)) && (0U != repeatProtectSequence))
        {
            /* Access in 8-bit mode while storing the value */
            *(__IO uint8_t *)(&base->STATUS) = 0U;
            *(__IO uint8_t *)(&base->STATUS) = 0x40U;
            *(__IO uint8_t *)(&base->STATUS) = 0xC0U;
            *(__IO uint8_t *)(&base->STATUS) = 0x80U;
            repeatProtectSequence--;
        }
    }
    else
    {
        /* Lock IRTC registers */
        while ((0U == ((base->STATUS & (uint16_t)RTC_STATUS_WRITE_PROT_EN_MASK) >> RTC_STATUS_WRITE_PROT_EN_SHIFT)) &&
               (0U != repeatProtectSequence))
        {
            *(__IO uint8_t *)(&base->STATUS) = 0x80U;
            repeatProtectSequence--;
        }
    }

    /* Lock/unlock was not successful even after trying 256 times */
    if (0U == repeatProtectSequence)
    {
        status = kStatus_Fail;
    }

    return status;
}

/*!
 * brief Sets the IRTC daylight savings start and stop date and time.
 *
 * It also enables the daylight saving bit in the IRTC control register
 *
 * param base     IRTC peripheral base address
 * param datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_SetDaylightTime(RTC_Type *base, const irtc_daylight_time_t *datetime)
{
    assert(NULL != datetime);

    /* Disable daylight saving time */
    base->CTRL &= ~(uint16_t)RTC_CTRL_DST_EN_MASK;

    /* Set the daylight saving time start month and end month value */
    base->DST_MONTH =
        RTC_DST_MONTH_DST_START_MONTH(datetime->startMonth) | RTC_DST_MONTH_DST_END_MONTH(datetime->endMonth);

    /* Set the daylight saving time start day and end day value */
    base->DST_DAY = RTC_DST_DAY_DST_START_DAY(datetime->startDay) | RTC_DST_DAY_DST_END_DAY(datetime->endDay);

    /* Set the daylight saving time start hour and end hour value */
    base->DST_HOUR = RTC_DST_HOUR_DST_START_HOUR(datetime->startHour) | RTC_DST_HOUR_DST_END_HOUR(datetime->endHour);

    /* Enable daylight saving time */
    base->CTRL |= RTC_CTRL_DST_EN_MASK;
}

/*!
 * brief Gets the IRTC daylight savings time and stores it in the given time structure.
 *
 * param base     IRTC peripheral base address
 * param datetime Pointer to a structure where the date and time details are stored.
 */
void IRTC_GetDaylightTime(RTC_Type *base, irtc_daylight_time_t *datetime)
{
    assert(NULL != datetime);

    uint16_t temp = base->DST_MONTH;

    /* Get the daylight savings time start and end month value */
    datetime->startMonth =
        (uint8_t)((temp & RTC_DST_MONTH_DST_START_MONTH_MASK) >> RTC_DST_MONTH_DST_START_MONTH_SHIFT);
    datetime->endMonth = (uint8_t)((temp & RTC_DST_MONTH_DST_END_MONTH_MASK) >> RTC_DST_MONTH_DST_END_MONTH_SHIFT);

    /* Get the daylight savings time start and end day value */
    temp               = base->DST_DAY;
    datetime->startDay = (uint8_t)((temp & RTC_DST_DAY_DST_START_DAY_MASK) >> RTC_DST_DAY_DST_START_DAY_SHIFT);
    datetime->endDay   = (uint8_t)((temp & RTC_DST_DAY_DST_END_DAY_MASK) >> RTC_DST_DAY_DST_END_DAY_SHIFT);

    /* Get the daylight savings time start and end hour value */
    temp                = base->DST_HOUR;
    datetime->startHour = (uint8_t)((temp & RTC_DST_HOUR_DST_START_HOUR_MASK) >> RTC_DST_HOUR_DST_START_HOUR_SHIFT);
    datetime->endHour   = (uint8_t)((temp & RTC_DST_HOUR_DST_END_HOUR_MASK) >> RTC_DST_HOUR_DST_END_HOUR_SHIFT);
}

/*!
 * brief Enables the coarse compensation and sets the value in the IRTC compensation register.
 *
 * param base                 IRTC peripheral base address
 * param compensationValue    Compensation value is a 2's complement value.
 * param compensationInterval Compensation interval.
 */
void IRTC_SetCoarseCompensation(RTC_Type *base, uint8_t compensationValue, uint8_t compensationInterval)
{
    uint16_t reg;

    /* Set the compensation value and interval */
    base->COMPEN = (uint16_t)compensationValue | ((uint16_t)compensationInterval << 8U);

    /* Disable fine and enable coarse compensation */
    reg = base->CTRL;
    reg &= ~(uint16_t)RTC_CTRL_FINEEN_MASK;
    reg |= RTC_CTRL_COMP_EN_MASK;
    base->CTRL = reg;
}

/*!
 * brief Enables the fine compensation and sets the value in the IRTC compensation register.
 *
 * param base                 The IRTC peripheral base address
 * param integralValue        Compensation integral value; twos complement value of the integer part
 * param fractionValue        Compensation fraction value expressed as number of clock cycles of a
 *                             fixed 4.194304Mhz clock that have to be added.
 * param accumulateFractional Flag indicating if we want to add to previous fractional part;
 *                             true: Add to previously accumulated fractional part,
 *                             false: Start afresh and overwrite current value
 */
void IRTC_SetFineCompensation(RTC_Type *base, uint8_t integralValue, uint8_t fractionValue, bool accumulateFractional)
{
    if (!accumulateFractional)
    {
        /* Disable compensation to clear previous accumulated fractional part */
        base->CTRL &= ~(((uint16_t)1U << RTC_CTRL_COMP_EN_SHIFT) | ((uint16_t)1U << RTC_CTRL_FINEEN_SHIFT));
    }

    /* Set the compensation fractional and integral parts */
    base->COMPEN = ((uint16_t)fractionValue & 0x7FU) | (((uint16_t)integralValue & 0xFU) << 12U);
    /* Enable fine compensation */
    base->CTRL |= (RTC_CTRL_COMP_EN_MASK | RTC_CTRL_FINEEN_MASK);
}

#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)

/*!
 * brief This function allows configuring the four tamper inputs.
 *
 * The function configures the filter properties for the three external tampers.
 * It also sets up active/passive and direction of the tamper bits, which are not available
 * on all platforms.
 * note This function programs the tamper filter parameters. The user must gate the 32K clock to
 * the RTC before calling this function. It is assumed that the time and date are set after this
 * and the tamper parameters do not require to be changed again later.
 *
 * param base         The IRTC peripheral base address
 * param tamperNumber The IRTC tamper input to configure
 * param tamperConfig The IRTC tamper properties
 */
void IRTC_SetTamperParams(RTC_Type *base, irtc_tamper_pins_t tamperNumber, const irtc_tamper_config_t *tamperConfig)
{
    assert(NULL != tamperConfig);

    uint16_t reg = 0;

#if defined(FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION) && (FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION)
    reg = base->TAMPER_DIRECTION;
    /* Set whether tamper pin is active or passive */
    if (tamperConfig->activePassive)
    {
        /* In case of active tamper, set the direction */
        reg |= (1U << tamperNumber);
        if (tamperConfig->direction)
        {
            /* Tamper direction is output */
            reg |= (1U << (RTC_TAMPER_DIRECTION_I_O_TAMP_SHIFT + tamperNumber));
        }
        else
        {
            /* Tamper direction is input */
            reg &= ~(1U << (RTC_TAMPER_DIRECTION_I_O_TAMP_SHIFT + tamperNumber));
        }
    }
    else
    {
        /* Passive tampers are input only and the direction bit is read only in this case */
        reg &= ~(1U << tamperNumber);
    }
    base->TAMPER_DIRECTION = reg;
#endif /* FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION */

    /* Set the filter properties for the external tamper pins */
    switch (tamperNumber)
    {
        case kIRTC_Tamper_0:
            /* Set the pin for Tamper 0 */
#if !defined(FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE) || (!FSL_FEATURE_RTC_HAS_NO_CTRL2_WAKEUP_MODE)
            base->CTRL2 &= ~(uint16_t)RTC_CTRL2_WAKEUP_MODE_MASK;
#endif
            reg = base->FILTER01_CFG;
            reg &= ~((uint16_t)RTC_FILTER01_CFG_POL0_MASK | (uint16_t)RTC_FILTER01_CFG_FIL_DUR0_MASK |
                     (uint16_t)RTC_FILTER01_CFG_CLK_SEL0_MASK);
            reg |= (RTC_FILTER01_CFG_POL0(tamperConfig->pinPolarity) |
                    RTC_FILTER01_CFG_FIL_DUR0(tamperConfig->filterDuration) |
                    RTC_FILTER01_CFG_CLK_SEL0(tamperConfig->filterClk));
            base->FILTER01_CFG = reg;
            break;
        case kIRTC_Tamper_1:
            reg = base->FILTER01_CFG;
            reg &= ~((uint16_t)RTC_FILTER01_CFG_POL1_MASK | (uint16_t)RTC_FILTER01_CFG_FIL_DUR1_MASK |
                     (uint16_t)RTC_FILTER01_CFG_CLK_SEL1_MASK);
            reg |= (RTC_FILTER01_CFG_POL1(tamperConfig->pinPolarity) |
                    RTC_FILTER01_CFG_FIL_DUR1(tamperConfig->filterDuration) |
                    RTC_FILTER01_CFG_CLK_SEL1(tamperConfig->filterClk));
            base->FILTER01_CFG = reg;
            break;
#if defined(FSL_FEATURE_RTC_HAS_FILTER23_CFG) && FSL_FEATURE_RTC_HAS_FILTER23_CFG
        case kIRTC_Tamper_2:
            reg = base->FILTER23_CFG;
            reg &= ~((uint16_t)RTC_FILTER23_CFG_POL2_MASK | (uint16_t)RTC_FILTER23_CFG_FIL_DUR2_MASK |
                     (uint16_t)RTC_FILTER23_CFG_CLK_SEL2_MASK);
            reg |= (RTC_FILTER23_CFG_POL2(tamperConfig->pinPolarity) |
                    RTC_FILTER23_CFG_FIL_DUR2(tamperConfig->filterDuration) |
                    RTC_FILTER23_CFG_CLK_SEL2(tamperConfig->filterClk));
            base->FILTER23_CFG = reg;
            break;
        case kIRTC_Tamper_3:
            reg = base->FILTER23_CFG;
            reg &= ~((uint16_t)RTC_FILTER23_CFG_POL3_MASK | (uint16_t)RTC_FILTER23_CFG_FIL_DUR3_MASK |
                     (uint16_t)RTC_FILTER23_CFG_CLK_SEL3_MASK);
            reg |= (RTC_FILTER23_CFG_POL3(tamperConfig->pinPolarity) |
                    RTC_FILTER23_CFG_FIL_DUR3(tamperConfig->filterDuration) |
                    RTC_FILTER23_CFG_CLK_SEL3(tamperConfig->filterClk));
            base->FILTER23_CFG = reg;
            break;
#else
        case kIRTC_Tamper_2:
            reg = base->FILTER2_CFG;
            reg &= ~((uint16_t)RTC_FILTER2_CFG_POL2_MASK | (uint16_t)RTC_FILTER2_CFG_FIL_DUR2_MASK |
                     (uint16_t)RTC_FILTER2_CFG_CLK_SEL2_MASK);
            reg |= (RTC_FILTER2_CFG_POL2(tamperConfig->pinPolarity) |
                    RTC_FILTER2_CFG_FIL_DUR2(tamperConfig->filterDuration) |
                    RTC_FILTER2_CFG_CLK_SEL2(tamperConfig->filterClk));
            base->FILTER2_CFG = reg;
            break;
#endif

        default:
            /* Internal tamper, does not have filter configuration. */
            break;
    }
}

#endif

#if !defined(FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE) || (!FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE)
#if defined(FSL_FEATURE_RTC_HAS_TAMPER_QUEUE) && (FSL_FEATURE_RTC_HAS_TAMPER_QUEUE)

/*!
 * brief This function reads the tamper timestamp and returns the associated tamper pin.
 *
 * The tamper timestamp has month, day, hour, minutes, and seconds. Ignore the year field as this
 * information is not available in the tamper queue. The user should look at the RTC_YEARMON register
 * for this because the expectation is that the queue is read at least once a year.
 * Return the tamper pin number associated with the timestamp.
 *
 * param base             The IRTC peripheral base address
 * param tamperTimestamp  The tamper timestamp
 *
 * return The tamper pin number
 */
uint8_t IRTC_ReadTamperQueue(RTC_Type *base, irtc_datetime_t *tamperTimestamp)
{
    assert(NULL != tamperTimestamp);

    /* Read the register 2 times to get a entry*/
    uint16_t temp1 = base->TAMPER_QUEUE;
    uint16_t temp2 = base->TAMPER_QUEUE;
    uint8_t tamperNum;

    /*
     * Tamper queue does not store the year field as this value can be read from RTC_YEARMON.
     * It is expected that the queue will be read at least once in a year.
     */
    tamperTimestamp->year = 0;
    /* From the first read; TAMPER_DATA[4:0] is the hour field */
    tamperTimestamp->hour = (uint8_t)temp1 & 0x1FU;
    /* From the first read; TAMPER_DATA[9:5] is the day field */
    tamperTimestamp->day = (uint8_t)(temp1 >> 5U) & 0x1FU;
    /* From the first read; TAMPER_DATA[13:10] is the month field */
    tamperTimestamp->month = (uint8_t)(temp1 >> 10U) & 0xFU;

    /* From the second read; TAMPER_DATA[5:0] is the seconds field */
    tamperTimestamp->second = (uint8_t)temp2 & 0x3FU;
    /* From the second read; TAMPER_DATA[11:6] is the minutes field */
    tamperTimestamp->minute = (uint8_t)(temp2 >> 6U) & 0x3FU;
    /* From the second read; TAMPER_DATA[14:12] is the tamper index */
    tamperNum = (uint8_t)(temp2 >> 12U) & 0x7U;

    return tamperNum;
}

#endif /* FSL_FEATURE_RTC_HAS_TAMPER_QUEUE */
#endif /* FSL_FEATURE_RTC_HAS_NO_TAMPER_FEATURE */

/*!
 * brief Select which clock to output from RTC.
 *
 * Select which clock to output from RTC for other modules to use inside SoC, for example,
 * RTC subsystem needs RTC to output 1HZ clock for sub-second counter.
 *
 * param base IRTC peripheral base address
 * param cloOut select clock to use for output
 */
void IRTC_ConfigClockOut(RTC_Type *base, irtc_clockout_sel_t clkOut)
{
    uint16_t ctrlVal = base->CTRL;

    ctrlVal &= (uint16_t)(~RTC_CTRL_CLKOUT_MASK);

    ctrlVal |= RTC_CTRL_CLKOUT((uint16_t)clkOut);
    if (clkOut == kIRTC_ClkoutCoarse1Hz)
    {
        ctrlVal |= RTC_CTRL_COMP_EN_MASK;
    }
    else if (clkOut == kIRTC_ClkoutFine1Hz)
    {
        ctrlVal |= RTC_CTRL_FINEEN_MASK;
    }
    else
    {
        /* empty else */
    }

    base->CTRL = ctrlVal;
}

#if defined(FSL_FEATURE_RTC_HAS_CLOCK_SELECT) && FSL_FEATURE_RTC_HAS_CLOCK_SELECT

/*!
 * brief Select which clock is used by RTC.
 *
 * Select which clock is used by RTC to output to the peripheral
 * and divided to generate a 512 Hz clock and a 1 Hz clock.
 *
 * param base IRTC peripheral base address
 * param clkSelect select clock used by RTC
 */
void IRTC_ConfigClockSelect(RTC_Type *base, irtc_clock_select_t clkSelect)
{
    uint16_t ctrlVal = base->CTRL;

    ctrlVal &= (uint16_t)(~RTC_CTRL_CLK_SEL_MASK);

    ctrlVal |= RTC_CTRL_CLK_SEL((uint16_t)clkSelect);

    base->CTRL = ctrlVal;
}

#endif /* FSL_FEATURE_RTC_HAS_CLOCK_SELECT */
