/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2022, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_snvs_lp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.snvs_lp"
#endif

#define SECONDS_IN_A_DAY    (86400U)
#define SECONDS_IN_A_HOUR   (3600U)
#define SECONDS_IN_A_MINUTE (60U)
#define DAYS_IN_A_YEAR      (365U)
#define YEAR_RANGE_START    (1970U)
#define YEAR_RANGE_END      (2099U)

#define SNVS_DEFAULT_PGD_VALUE (0x41736166U)

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
static bool SNVS_LP_CheckDatetimeFormat(const snvs_lp_srtc_datetime_t *datetime);

/*!
 * @brief Converts time data from datetime to seconds
 *
 * @param datetime Pointer to datetime structure where the date and time details are stored
 *
 * @return The result of the conversion in seconds
 */
static uint32_t SNVS_LP_ConvertDatetimeToSeconds(const snvs_lp_srtc_datetime_t *datetime);

/*!
 * @brief Converts time data from seconds to a datetime structure
 *
 * @param seconds  Seconds value that needs to be converted to datetime format
 * @param datetime Pointer to the datetime structure where the result of the conversion is stored
 */
static void SNVS_LP_ConvertSecondsToDatetime(uint32_t seconds, snvs_lp_srtc_datetime_t *datetime);

/*!
 * @brief Returns SRTC time in seconds.
 *
 * This function is used internally to get actual SRTC time in seconds.
 *
 * @param base SNVS peripheral base address
 *
 * @return SRTC time in seconds
 */
static uint32_t SNVS_LP_SRTC_GetSeconds(SNVS_Type *base);

#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && \
     defined(SNVS_LP_CLOCKS))
/*!
 * @brief Get the SNVS instance from peripheral base address.
 *
 * @param base SNVS peripheral base address.
 *
 * @return SNVS instance.
 */
static uint32_t SNVS_LP_GetInstance(SNVS_Type *base);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && \
     defined(SNVS_LP_CLOCKS))
/*! @brief Pointer to snvs_lp clock. */
const clock_ip_name_t s_snvsLpClock[] = SNVS_LP_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static bool SNVS_LP_CheckDatetimeFormat(const snvs_lp_srtc_datetime_t *datetime)
{
    assert(datetime != NULL);

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

static uint32_t SNVS_LP_ConvertDatetimeToSeconds(const snvs_lp_srtc_datetime_t *datetime)
{
    assert(datetime != NULL);

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

    seconds = (seconds * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
              (datetime->minute * SECONDS_IN_A_MINUTE) + datetime->second;

    return seconds;
}

static void SNVS_LP_ConvertSecondsToDatetime(uint32_t seconds, snvs_lp_srtc_datetime_t *datetime)
{
    assert(datetime != NULL);

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
        if ((datetime->year & 3U) != 0U)
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

#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && \
     defined(SNVS_LP_CLOCKS))
static uint32_t SNVS_LP_GetInstance(SNVS_Type *base)
{
    return 0U;
}
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*!
 * brief Ungates the SNVS clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the SNVS driver.
 *
 * param base   SNVS peripheral base address
 * param config Pointer to the user's SNVS configuration structure.
 */
void SNVS_LP_Init(SNVS_Type *base)
{
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && \
     defined(SNVS_LP_CLOCKS))
    uint32_t instance = SNVS_LP_GetInstance(base);
    CLOCK_EnableClock(s_snvsLpClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Power glitch detector: set the PGD/LVD value and clear the previous status. */
#if defined(SNVS_LPPGDR_PGD)
    base->LPPGDR = SNVS_DEFAULT_PGD_VALUE;
    base->LPSR   = SNVS_LPSR_PGD_MASK;
#elif defined(SNVS_LPLVDR_LVD)
    base->LPLVDR = SNVS_DEFAULT_PGD_VALUE;
    base->LPSR   = SNVS_LPSR_LVD_MASK;
#else
#error "No power/voltage detector register defined"
#endif
}

/*!
 * brief Deinit the SNVS LP section.
 *
 * param base SNVS peripheral base address
 */
void SNVS_LP_Deinit(SNVS_Type *base)
{
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && \
     defined(SNVS_LP_CLOCKS))
    uint32_t instance = SNVS_LP_GetInstance(base);
    CLOCK_DisableClock(s_snvsLpClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Ungates the SNVS clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the SNVS driver.
 *
 * param base   SNVS peripheral base address
 * param config Pointer to the user's SNVS configuration structure.
 */
void SNVS_LP_SRTC_Init(SNVS_Type *base, const snvs_lp_srtc_config_t *config)
{
    assert(config != NULL);

    SNVS_LP_Init(base);

    if (config->srtcCalEnable)
    {
        base->LPCR = (base->LPCR & ~SNVS_LPCR_LPCALB_VAL_MASK) | SNVS_LPCR_LPCALB_VAL(config->srtcCalValue);
        base->LPCR |= SNVS_LPCR_LPCALB_EN_MASK;
    }

#if defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 0)

    int pin;

    for (pin = (int32_t)kSNVS_ExternalTamper1; pin <= (int32_t)SNVS_LP_MAX_TAMPER; pin++)
    {
        SNVS_LP_DisableExternalTamper(SNVS, (snvs_lp_external_tamper_t)pin);
        SNVS_LP_ClearExternalTamperStatus(SNVS, (snvs_lp_external_tamper_t)pin);
    }
#endif /* defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 0) */
}

/*!
 * brief Stops the SRTC timer.
 *
 * param base SNVS peripheral base address
 */
void SNVS_LP_SRTC_Deinit(SNVS_Type *base)
{
    base->LPCR &= ~SNVS_LPCR_SRTC_ENV_MASK;

    SNVS_LP_Deinit(base);
}

/*!
 * brief Fills in the SNVS_LP config struct with the default settings.
 *
 * The default values are as follows.
 * code
 *    config->srtccalenable = false;
 *    config->srtccalvalue = 0U;
 * endcode
 * param config Pointer to the user's SNVS configuration structure.
 */
void SNVS_LP_SRTC_GetDefaultConfig(snvs_lp_srtc_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->srtcCalEnable = false;
    config->srtcCalValue  = 0U;
}

static uint32_t SNVS_LP_SRTC_GetSeconds(SNVS_Type *base)
{
    uint32_t seconds = 0;
    uint32_t tmp     = 0;

    /* Do consecutive reads until value is correct */
    do
    {
        seconds = tmp;
        tmp     = (base->LPSRTCMR << 17U);
        tmp |= (base->LPSRTCLR >> 15U);
    } while (tmp != seconds);

    return seconds;
}

/*!
 * brief Sets the SNVS SRTC date and time according to the given time structure.
 *
 * param base     SNVS peripheral base address
 * param datetime Pointer to the structure where the date and time details are stored.
 *
 * return kStatus_Success: Success in setting the time and starting the SNVS SRTC
 *         kStatus_InvalidArgument: Error because the datetime format is incorrect
 */
status_t SNVS_LP_SRTC_SetDatetime(SNVS_Type *base, const snvs_lp_srtc_datetime_t *datetime)
{
    assert(datetime != NULL);

    uint32_t seconds = 0U;
    uint32_t tmp     = base->LPCR;

    /* disable RTC */
    SNVS_LP_SRTC_StopTimer(base);

    /* Return error if the time provided is not valid */
    if (!(SNVS_LP_CheckDatetimeFormat(datetime)))
    {
        return kStatus_InvalidArgument;
    }

    /* Set time in seconds */
    seconds = SNVS_LP_ConvertDatetimeToSeconds(datetime);

    base->LPSRTCMR = (uint32_t)(seconds >> 17U);
    base->LPSRTCLR = (uint32_t)(seconds << 15U);

    /* reenable SRTC in case that it was enabled before */
    if ((tmp & SNVS_LPCR_SRTC_ENV_MASK) != 0U)
    {
        SNVS_LP_SRTC_StartTimer(base);
    }

    return kStatus_Success;
}

/*!
 * brief Gets the SNVS SRTC time and stores it in the given time structure.
 *
 * param base     SNVS peripheral base address
 * param datetime Pointer to the structure where the date and time details are stored.
 */
void SNVS_LP_SRTC_GetDatetime(SNVS_Type *base, snvs_lp_srtc_datetime_t *datetime)
{
    assert(datetime != NULL);

    SNVS_LP_ConvertSecondsToDatetime(SNVS_LP_SRTC_GetSeconds(base), datetime);
}

/*!
 * brief Sets the SNVS SRTC alarm time.
 *
 * The function sets the SRTC alarm. It also checks whether the specified alarm
 * time is greater than the present time. If not, the function does not set the alarm
 * and returns an error.
 * Please note, that SRTC alarm has limited resolution because only 32 most
 * significant bits of SRTC counter are compared to SRTC Alarm register.
 * If the alarm time is beyond SRTC resolution, the function does not set the alarm
 * and returns an error.
 *
 * param base      SNVS peripheral base address
 * param alarmTime Pointer to the structure where the alarm time is stored.
 *
 * return kStatus_Success: success in setting the SNVS SRTC alarm
 *         kStatus_InvalidArgument: Error because the alarm datetime format is incorrect
 *         kStatus_Fail: Error because the alarm time has already passed or is beyond resolution
 */
status_t SNVS_LP_SRTC_SetAlarm(SNVS_Type *base, const snvs_lp_srtc_datetime_t *alarmTime)
{
    assert(alarmTime != NULL);

    uint32_t alarmSeconds = 0U;
    uint32_t currSeconds  = 0U;
    uint32_t tmp          = base->LPCR;

    /* Return error if the alarm time provided is not valid */
    if (!(SNVS_LP_CheckDatetimeFormat(alarmTime)))
    {
        return kStatus_InvalidArgument;
    }

    alarmSeconds = SNVS_LP_ConvertDatetimeToSeconds(alarmTime);
    currSeconds  = SNVS_LP_SRTC_GetSeconds(base);

    /* Return error if the alarm time has passed */
    if (alarmSeconds <= currSeconds)
    {
        return kStatus_Fail;
    }

    /* disable SRTC alarm interrupt */
    base->LPCR &= ~SNVS_LPCR_LPTA_EN_MASK;
    while ((base->LPCR & SNVS_LPCR_LPTA_EN_MASK) != 0U)
    {
    }

    /* Set alarm in seconds*/
    base->LPTAR = alarmSeconds;

    /* reenable SRTC alarm interrupt in case that it was enabled before */
    base->LPCR = tmp;

    return kStatus_Success;
}

/*!
 * brief Returns the SNVS SRTC alarm time.
 *
 * param base     SNVS peripheral base address
 * param datetime Pointer to the structure where the alarm date and time details are stored.
 */
void SNVS_LP_SRTC_GetAlarm(SNVS_Type *base, snvs_lp_srtc_datetime_t *datetime)
{
    assert(datetime != NULL);

    uint32_t alarmSeconds = 0U;

    /* Get alarm in seconds  */
    alarmSeconds = base->LPTAR;

    SNVS_LP_ConvertSecondsToDatetime(alarmSeconds, datetime);
}

/*!
 * brief Gets the SNVS status flags.
 *
 * param base SNVS peripheral base address
 *
 * return The status flags. This is the logical OR of members of the
 *         enumeration ::snvs_status_flags_t
 */
uint32_t SNVS_LP_SRTC_GetStatusFlags(SNVS_Type *base)
{
    uint32_t flags = 0U;

    if ((base->LPSR & SNVS_LPSR_LPTA_MASK) != 0U)
    {
        flags |= (uint32_t)kSNVS_SRTC_AlarmInterruptFlag;
    }

    return flags;
}

/*!
 * brief Gets the enabled SNVS interrupts.
 *
 * param base SNVS peripheral base address
 *
 * return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::snvs_interrupt_enable_t
 */
uint32_t SNVS_LP_SRTC_GetEnabledInterrupts(SNVS_Type *base)
{
    uint32_t val = 0U;

    if ((base->LPCR & SNVS_LPCR_LPTA_EN_MASK) != 0U)
    {
        val |= (uint32_t)kSNVS_SRTC_AlarmInterrupt;
    }

    return val;
}

/*!
 * brief Fills in the SNVS tamper pin config struct with the default settings.
 *
 * The default values are as follows.
 * code
 *  config->polarity        = 0U;
 *  config->filterenable    = 0U;
 *  config->filter          = 0U;
 * endcode
 * param config Pointer to the user's SNVS configuration structure.
 */
void SNVS_LP_PassiveTamperPin_GetDefaultConfig(snvs_lp_passive_tamper_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->polarity = 0U;
#if defined(FSL_FEATURE_SNVS_PASSIVE_TAMPER_FILTER) && (FSL_FEATURE_SNVS_PASSIVE_TAMPER_FILTER > 0)
    config->filterenable = 0U;
    config->filter       = 0U;
#endif /* FSL_FEATURE_SNVS_PASSIVE_TAMPER_FILTER */
}

#if defined(FSL_FEATURE_SNVS_HAS_ACTIVE_TAMPERS) && (FSL_FEATURE_SNVS_HAS_ACTIVE_TAMPERS > 0)
/*!
 * brief Fills in the SNVS tamper pin config struct with the default settings.
 *
 * The default values are as follows.
 * code
 *  config->clock       = kSNVS_ActiveTamper16HZ;
 *  config->seed        = 0U;
 *  config->polynomial  = 0U;
 * endcode
 * param config Pointer to the user's SNVS configuration structure.
 */
void SNVS_LP_TamperPinTx_GetDefaultConfig(tamper_active_tx_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->clock      = kSNVS_ActiveTamper16HZ;
    config->seed       = 0U;
    config->polynomial = 0U;
}

/*!
 * brief Fills in the SNVS tamper pin config struct with the default settings.
 *
 * The default values are as follows.
 * code
 *  config->filterenable    = 0U;
 *  config->filter          = 0U;
 *  config->tx              = kSNVS_ActiveTamper1;
 * endcode
 * param config Pointer to the user's SNVS configuration structure.
 */
void SNVS_LP_TamperPinRx_GetDefaultConfig(tamper_active_rx_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->filterenable = 0U;
    config->filter       = 0U;
    config->activeTamper = kSNVS_ActiveTamper1;
}
#endif /* FSL_FEATURE_SNVS_HAS_ACTIVE_TAMPERS */

#if defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 0)

/*!
 * brief Enables the specified SNVS external tamper.
 *
 * param base SNVS peripheral base address
 * param pin SNVS external tamper pin
 * param config Configuration structure of external passive tamper
 */
void SNVS_LP_EnablePassiveTamper(SNVS_Type *base, snvs_lp_external_tamper_t pin, snvs_lp_passive_tamper_t config)
{
    switch (pin)
    {
        case (kSNVS_ExternalTamper1):
            /* Set polarity */
            if (config.polarity != 0U)
            {
                SNVS->LPTDCR |= SNVS_LPTDCR_ET1P_MASK;
            }
            else
            {
                SNVS->LPTDCR &= ~SNVS_LPTDCR_ET1P_MASK;
            }
#if defined(FSL_FEATURE_SNVS_PASSIVE_TAMPER_FILTER) && (FSL_FEATURE_SNVS_PASSIVE_TAMPER_FILTER > 0)
            /* Enable filter and set it's value, dissable otherwise */
            if (config.filterenable != 0U)
            {
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF1_EN_MASK;
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF1(config.filter);
            }
            else
            {
                SNVS->LPTGFCR &= ~SNVS_LPTGFCR_ETGF1_EN_MASK;
            }
#endif /* FSL_FEATURE_SNVS_PASSIVE_TAMPER_FILTER */
            /* enable tamper pin */
            base->LPTDCR |= SNVS_LPTDCR_ET1_EN_MASK;
            break;
#if defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 1)
        case (kSNVS_ExternalTamper2):
            /* Set polarity */
            base->LPTDCR =
                (base->LPTDCR & ~(SNVS_LPTDCR_ET2P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDCR_ET2P_SHIFT);
            /* Enable filter and set it's value, dissable otherwise */
            if (config.filterenable != 0U)
            {
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF2_EN_MASK;
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF2(config.filter);
            }
            else
            {
                SNVS->LPTGFCR &= ~SNVS_LPTGFCR_ETGF2_EN_MASK;
            }

            /* enable tamper pin */
            SNVS->LPTDCR |= SNVS_LPTDCR_ET2_EN_MASK;

            break;
        case (kSNVS_ExternalTamper3):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET3P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET3P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF3(config.filter);
                /* Enable tamper 3 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF3_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET3_EN_MASK;
            break;
        case (kSNVS_ExternalTamper4):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET4P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET4P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF4(config.filter);
                /* Enable tamper 4 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF4_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET4_EN_MASK;
            break;
        case (kSNVS_ExternalTamper5):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET5P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET5P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF5(config.filter);
                /* Enable tamper 5 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF5_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET5_EN_MASK;
            break;
        case (kSNVS_ExternalTamper6):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET6P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET6P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF6(config.filter);
                /* Enable tamper 6 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF6_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET6_EN_MASK;
            break;
        case (kSNVS_ExternalTamper7):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET7P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET7P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF7(config.filter);
                /* Enable tamper 6 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF7_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET7_EN_MASK;
            break;
        case (kSNVS_ExternalTamper8):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET8P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET8P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF8(config.filter);
                /* Enable tamper 8 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF8_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET8_EN_MASK;
            break;
        case (kSNVS_ExternalTamper9):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET9P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET9P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF9(config.filter);
                /* Enable tamper 9 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF9_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET9_EN_MASK;
            break;
        case (kSNVS_ExternalTamper10):
            /* Set polarity */
            base->LPTDC2R =
                (base->LPTDC2R & ~(SNVS_LPTDC2R_ET10P_MASK)) | ((uint32_t)config.polarity << SNVS_LPTDC2R_ET10P_SHIFT);
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF10(config.filter);
                /* Enable tamper 10 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF10_EN(1U);
            }
            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET10_EN_MASK;
            break;
#endif
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
}

/*!
 * brief Disables the specified SNVS external tamper.
 *
 * param base SNVS peripheral base address
 * param pin SNVS external tamper pin
 */
void SNVS_LP_DisableExternalTamper(SNVS_Type *base, snvs_lp_external_tamper_t pin)
{
    switch (pin)
    {
        case (kSNVS_ExternalTamper1):
            base->LPTDCR &= ~SNVS_LPTDCR_ET1_EN_MASK;
            break;
#if defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 1)
        case (kSNVS_ExternalTamper2):
            base->LPTDCR &= ~SNVS_LPTDCR_ET2_EN_MASK;
            break;
        case (kSNVS_ExternalTamper3):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET3_EN_MASK;
            break;
        case (kSNVS_ExternalTamper4):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET4_EN_MASK;
            break;
        case (kSNVS_ExternalTamper5):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET5_EN_MASK;
            break;
        case (kSNVS_ExternalTamper6):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET6_EN_MASK;
            break;
        case (kSNVS_ExternalTamper7):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET7_EN_MASK;
            break;
        case (kSNVS_ExternalTamper8):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET8_EN_MASK;
            break;
        case (kSNVS_ExternalTamper9):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET9_EN_MASK;
            break;
        case (kSNVS_ExternalTamper10):
            base->LPTDC2R &= ~SNVS_LPTDC2R_ET10_EN_MASK;
            break;
#endif
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
}

/*!
 * brief Disable all external tamper.
 *
 * param base SNVS peripheral base address
 */
void SNVS_LP_DisableAllExternalTamper(SNVS_Type *base)
{
    for (int pin = (int8_t)kSNVS_ExternalTamper1; pin <= (int8_t)SNVS_LP_MAX_TAMPER; pin++)
    {
        SNVS_LP_DisableExternalTamper(SNVS, (snvs_lp_external_tamper_t)pin);
    }
}

/*!
 * brief Returns status of the specified external tamper.
 *
 * param base SNVS peripheral base address
 * param pin SNVS external tamper pin
 *
 * return The status flag. This is the enumeration ::snvs_external_tamper_status_t
 */
snvs_lp_external_tamper_status_t SNVS_LP_GetExternalTamperStatus(SNVS_Type *base, snvs_lp_external_tamper_t pin)
{
    snvs_lp_external_tamper_status_t status = kSNVS_TamperNotDetected;

    switch (pin)
    {
        case (kSNVS_ExternalTamper1):
            status = (bool)(base->LPSR & SNVS_LPSR_ET1D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
#if defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 1)
        case (kSNVS_ExternalTamper2):
            status = (bool)(base->LPSR & SNVS_LPSR_ET2D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper3):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET3D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper4):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET4D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper5):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET5D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper6):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET6D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper7):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET7D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper8):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET8D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper9):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET9D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
        case (kSNVS_ExternalTamper10):
            status = (bool)(base->LPTDSR & SNVS_LPTDSR_ET10D_MASK) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
            break;
#endif
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
    return status;
}

/*!
 * brief Clears status of the specified external tamper.
 *
 * param base SNVS peripheral base address
 * param pin SNVS external tamper pin
 */
void SNVS_LP_ClearExternalTamperStatus(SNVS_Type *base, snvs_lp_external_tamper_t pin)
{
    base->LPSR |= SNVS_LPSR_ET1D_MASK;

    switch (pin)
    {
        case (kSNVS_ExternalTamper1):
            base->LPSR |= SNVS_LPSR_ET1D_MASK;
            break;
#if defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 1)
        case (kSNVS_ExternalTamper2):
            base->LPSR |= SNVS_LPSR_ET2D_MASK;
            break;
        case (kSNVS_ExternalTamper3):
            base->LPTDSR |= SNVS_LPTDSR_ET3D_MASK;
            break;
        case (kSNVS_ExternalTamper4):
            base->LPTDSR |= SNVS_LPTDSR_ET4D_MASK;
            break;
        case (kSNVS_ExternalTamper5):
            base->LPTDSR |= SNVS_LPTDSR_ET5D_MASK;
            break;
        case (kSNVS_ExternalTamper6):
            base->LPTDSR |= SNVS_LPTDSR_ET6D_MASK;
            break;
        case (kSNVS_ExternalTamper7):
            base->LPTDSR |= SNVS_LPTDSR_ET7D_MASK;
            break;
        case (kSNVS_ExternalTamper8):
            base->LPTDSR |= SNVS_LPTDSR_ET8D_MASK;
            break;
        case (kSNVS_ExternalTamper9):
            base->LPTDSR |= SNVS_LPTDSR_ET9D_MASK;
            break;
        case (kSNVS_ExternalTamper10):
            base->LPTDSR |= SNVS_LPTDSR_ET10D_MASK;
            break;
#endif
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
}

/*!
 * brief Clears status of the all external tamper.
 *
 * param base SNVS peripheral base address
 */
void SNVS_LP_ClearAllExternalTamperStatus(SNVS_Type *base)
{
    for (int pin = (int8_t)kSNVS_ExternalTamper1; pin <= (int8_t)SNVS_LP_MAX_TAMPER; pin++)
    {
        SNVS_LP_ClearExternalTamperStatus(SNVS, (snvs_lp_external_tamper_t)pin);
    }
}

#endif /* (!(defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 0)) */

#if defined(FSL_FEATURE_SNVS_HAS_ACTIVE_TAMPERS) && (FSL_FEATURE_SNVS_HAS_ACTIVE_TAMPERS > 0)
/*!
 * brief Enable active tamper tx external pad
 *
 * param base SNVS peripheral base address
 * param pin SNVS external tamper pin
 */
status_t SNVS_LP_EnableTxActiveTamper(SNVS_Type *base, snvs_lp_active_tx_tamper_t pin, tamper_active_tx_config_t config)
{
    status_t status = kStatus_Success;

    switch (pin)
    {
        case (kSNVS_ActiveTamper1):
        {
            /* Enable active tamper tx external pad */
            base->LPATCTLR |= SNVS_LPATCTLR_AT1_PAD_EN_MASK;
            /* Set seed and polynomial */
            base->LPATCR[0] |= SNVS_LPATCR_Seed(config.seed) | SNVS_LPATCR_Polynomial(config.polynomial);
            /* Set clock */
            base->LPATCLKR |= SNVS_LPATCLKR_AT1_CLK_CTL(config.clock);
            /* Enable active tamper pin */
            base->LPATCTLR |= SNVS_LPATCTLR_AT1_EN_MASK;
            break;
        }
        case (kSNVS_ActiveTamper2):
        {
            base->LPATCTLR |= SNVS_LPATCTLR_AT2_PAD_EN_MASK;
            base->LPATCR[1] |= SNVS_LPATCR_Seed(config.seed) | SNVS_LPATCR_Polynomial(config.polynomial);
            base->LPATCLKR |= SNVS_LPATCLKR_AT2_CLK_CTL(config.clock);
            base->LPATCTLR |= SNVS_LPATCTLR_AT2_EN_MASK;
            break;
        }
        case (kSNVS_ActiveTamper3):
        {
            base->LPATCTLR |= SNVS_LPATCTLR_AT3_PAD_EN_MASK;
            base->LPATCR[2] |= SNVS_LPATCR_Seed(config.seed) | SNVS_LPATCR_Polynomial(config.polynomial);
            base->LPATCLKR |= SNVS_LPATCLKR_AT3_CLK_CTL(config.clock);
            base->LPATCTLR |= SNVS_LPATCTLR_AT3_EN_MASK;
            break;
        }
        case (kSNVS_ActiveTamper4):
        {
            base->LPATCTLR |= SNVS_LPATCTLR_AT4_PAD_EN_MASK;
            base->LPATCR[3] |= SNVS_LPATCR_Seed(config.seed) | SNVS_LPATCR_Polynomial(config.polynomial);
            base->LPATCLKR |= SNVS_LPATCLKR_AT4_CLK_CTL(config.clock);
            base->LPATCTLR |= SNVS_LPATCTLR_AT4_EN_MASK;
            break;
        }
        case (kSNVS_ActiveTamper5):
        {
            base->LPATCTLR |= SNVS_LPATCTLR_AT5_PAD_EN_MASK;
            base->LPATCR[4] |= SNVS_LPATCR_Seed(config.seed) | SNVS_LPATCR_Polynomial(config.polynomial);
            base->LPATCLKR |= SNVS_LPATCLKR_AT5_CLK_CTL(config.clock);
            base->LPATCTLR |= SNVS_LPATCTLR_AT5_EN_MASK;
            break;
        }
        default:
            status = kStatus_InvalidArgument;
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
    return status;
}

/*!
 * brief Enable active tamper rx external pad
 *
 * param base SNVS peripheral base address
 * param rx SNVS external RX tamper pin
 * param config SNVS RX tamper config structure
 */
status_t SNVS_LP_EnableRxActiveTamper(SNVS_Type *base, snvs_lp_external_tamper_t rx, tamper_active_rx_config_t config)
{
    status_t status = kStatus_Success;

    switch (rx)
    {
        case (kSNVS_ExternalTamper1):
            /* Enable filter and set it's value, dissable otherwise */
            if (config.filterenable != 0U)
            {
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF1_EN_MASK;
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF1(config.filter);
            }
            else
            {
                SNVS->LPTGFCR &= ~SNVS_LPTGFCR_ETGF1_EN_MASK;
            }

            /* Route TX to external tamper 1 */
            base->LPATRC1R = SNVS_LPATRC1R_ET1RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDCR |= SNVS_LPTDCR_ET1_EN_MASK;
            break;
#if defined(FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER) && (FSL_FEATURE_SNVS_HAS_MULTIPLE_TAMPER > 1)
        case (kSNVS_ExternalTamper2):
            /* Enable filter and set it's value, dissable otherwise */
            if (config.filterenable != 0U)
            {
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF2_EN_MASK;
                SNVS->LPTGFCR |= SNVS_LPTGFCR_ETGF2(config.filter);
            }
            else
            {
                SNVS->LPTGFCR &= ~SNVS_LPTGFCR_ETGF2_EN_MASK;
            }

            /* Route TX to external tamper 2 */
            base->LPATRC1R = SNVS_LPATRC1R_ET2RCTL(config.activeTamper);

            /* enable tamper pin */
            SNVS->LPTDCR |= SNVS_LPTDCR_ET2_EN_MASK;

            break;
        case (kSNVS_ExternalTamper3):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF3(config.filter);
                /* Enable tamper 3 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF3_EN(1U);
            }

            /* Route TX to external tamper 3 */
            base->LPATRC1R = SNVS_LPATRC1R_ET3RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET3_EN_MASK;
            break;
        case (kSNVS_ExternalTamper4):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF4(config.filter);
                /* Enable tamper 4 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF4_EN(1U);
            }

            /* Route TX to external tamper 4 */
            base->LPATRC1R = SNVS_LPATRC1R_ET4RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET4_EN_MASK;
            break;
        case (kSNVS_ExternalTamper5):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF5(config.filter);
                /* Enable tamper 5 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF5_EN(1U);
            }

            /* Route TX to external tamper 5 */
            base->LPATRC1R = SNVS_LPATRC1R_ET5RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET5_EN_MASK;
            break;
        case (kSNVS_ExternalTamper6):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF6(config.filter);
                /* Enable tamper 6 glitch filter */
                SNVS->LPTGF1CR |= SNVS_LPTGF1CR_ETGF6_EN(1U);
            }

            /* Route TX to external tamper 6 */
            base->LPATRC1R = SNVS_LPATRC1R_ET6RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET6_EN_MASK;
            break;
        case (kSNVS_ExternalTamper7):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF7(config.filter);
                /* Enable tamper 6 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF7_EN(1U);
            }

            /* Route TX to external tamper 7 */
            base->LPATRC1R = SNVS_LPATRC1R_ET7RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET7_EN_MASK;
            break;
        case (kSNVS_ExternalTamper8):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF8(config.filter);
                /* Enable tamper 8 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF8_EN(1U);
            }

            /* Route TX to external tamper 8 */
            base->LPATRC1R = SNVS_LPATRC1R_ET8RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET8_EN_MASK;
            break;
        case (kSNVS_ExternalTamper9):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF9(config.filter);
                /* Enable tamper 9 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF9_EN(1U);
            }

            /* Route TX to external tamper 9 */
            base->LPATRC1R = SNVS_LPATRC2R_ET9RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET9_EN_MASK;
            break;
        case (kSNVS_ExternalTamper10):
            /* Enable filter and set it's value if set */
            if (config.filterenable != 0U)
            {
                /* Set filter value */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF10(config.filter);
                /* Enable tamper 10 glitch filter */
                SNVS->LPTGF2CR |= SNVS_LPTGF2CR_ETGF10_EN(1U);
            }

            /* Route TX to external tamper 10 */
            base->LPATRC1R = SNVS_LPATRC2R_ET10RCTL(config.activeTamper);

            /* enable tamper pin */
            base->LPTDC2R |= SNVS_LPTDC2R_ET10_EN_MASK;
            break;
#endif
        default:
            status = kStatus_InvalidArgument;
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }

    return status;
}

/*!
 * brief Sets voltage tamper detect
 *
 * param base SNVS peripheral base address
 * param enable True if enable false if disable
 */
status_t SNVS_LP_SetVoltageTamper(SNVS_Type *base, bool enable)
{
    base->LPTDCR |= SNVS_LPTDCR_VT_EN(enable);

    return kStatus_Success;
}

/*!
 * brief Sets temperature tamper detect
 *
 * param base SNVS peripheral base address
 * param enable True if enable false if disable
 */
status_t SNVS_LP_SetTemperatureTamper(SNVS_Type *base, bool enable)
{
    SNVS->LPTDCR |= SNVS_LPTDCR_TT_EN(enable);

    return kStatus_Success;
}

/*!
 * brief Sets clock tamper detect
 *
 * param base SNVS peripheral base address
 * param enable True if enable false if disable
 */
status_t SNVS_LP_SetClockTamper(SNVS_Type *base, bool enable)
{
    SNVS->LPTDCR |= SNVS_LPTDCR_CT_EN(enable);

    return kStatus_Success;
}

/*!
 * brief Check voltage tamper
 *
 * param base SNVS peripheral base address
 */
snvs_lp_external_tamper_status_t SNVS_LP_CheckVoltageTamper(SNVS_Type *base)
{
    return ((SNVS->LPSR & SNVS_LPSR_VTD_MASK) != 0U) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
}

/*!
 * brief Check temperature tamper
 *
 * param base SNVS peripheral base address
 */
snvs_lp_external_tamper_status_t SNVS_LP_CheckTemperatureTamper(SNVS_Type *base)
{
    return ((SNVS->LPSR & SNVS_LPSR_TTD_MASK) != 0U) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
}

/*!
 * brief Check clock tamper
 *
 * param base SNVS peripheral base address
 */
snvs_lp_external_tamper_status_t SNVS_LP_CheckClockTamper(SNVS_Type *base)
{
    return ((SNVS->LPSR & SNVS_LPSR_CTD_MASK) != 0U) ? kSNVS_TamperDetected : kSNVS_TamperNotDetected;
}
#endif /* defined(FSL_FEATURE_SNVS_HAS_ACTIVE_TAMPERS) && (FSL_FEATURE_SNVS_HAS_ACTIVE_TAMPERS > 0) */

/*!
 * brief Get the current Monotonic Counter.
 *
 * param base SNVS peripheral base address
 * return Current Monotonic Counter value.
 */
uint64_t SNVS_LP_GetMonotonicCounter(SNVS_Type *base)
{
    uint32_t mc_lsb, mc_msb;

    mc_msb = base->LPSMCMR;
    mc_lsb = base->LPSMCLR;

    return ((uint64_t)mc_msb << 32UL) | (uint64_t)mc_lsb;
}

/*!
 * brief Write Zeroizable Master Key (ZMK) to the SNVS registers.
 *
 * param base SNVS peripheral base address
 * param ZMKey The ZMK write to the SNVS register.
 */
void SNVS_LP_WriteZeroizableMasterKey(SNVS_Type *base, uint32_t ZMKey[SNVS_ZMK_REG_COUNT])
{
    uint8_t i = 0;

    for (i = 0; i < SNVS_ZMK_REG_COUNT; i++)
    {
        base->LPZMKR[i] = ZMKey[i];
    }
}

#if defined(FSL_FEATURE_SNVS_HAS_STATE_TRANSITION) && (FSL_FEATURE_SNVS_HAS_STATE_TRANSITION > 0)
/*!
 * brief Transition SNVS SSM state to Trusted/Non-secure from Check state
 *
 * param base SNVS peripheral base address
 *
 * return kStatus_Success: Success in transitioning SSM State
 *        kStatus_Fail: SSM State transition failed
 */
status_t SNVS_LP_SSM_State_Transition(SNVS_Type *base)
{
    uint32_t curr_ssm_state = ((base->HPSR & SNVS_HPSR_SSM_STATE_MASK) >> SNVS_HPSR_SSM_STATE_SHIFT);
    uint32_t sec_config     = ((OCOTP_CTRL->HW_OCOTP_OTFAD_CFG3 & OCOTP_CTRL_HW_OCOTP_SEC_CONFIG1_MASK) >>
                           OCOTP_CTRL_HW_OCOTP_SEC_CONFIG1_SHIFT);

    /* Check if SSM State is Check state */
    if (curr_ssm_state == SNVS_SSM_STATE_CHECK)
    {
        if (sec_config == SEC_CONFIG_OPEN)
        {
            /* Transition to Non-secure state */
            base->HPCOMR |= SNVS_HPCOMR_SW_SV(1);
        }
        else
        {
            /* Transition to Trusted state */
            base->HPCOMR |= SNVS_HPCOMR_SSM_ST(1);
        }
    }

    uint32_t new_ssm_state = ((base->HPSR & SNVS_HPSR_SSM_STATE_MASK) >> SNVS_HPSR_SSM_STATE_SHIFT);

    if (new_ssm_state != SNVS_SSM_STATE_CHECK)
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}
#endif /* FSL_FEATURE_SNVS_HAS_STATE_TRANSITION */
