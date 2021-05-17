/**************************************************************************//**
 * @file     rtc.c
 * @version  V1.00
 * $Revision: 4 $
 * $Date: 18/04/25 11:43a $
 * @brief    M031 series Real Time Clock(RTC) driver source file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M031Series.h"


/** @cond HIDDEN_SYMBOLS */

/*---------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_GLOBALS

/*---------------------------------------------------------------------------------------------------------*/
/* Global file scope (static) variables                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
static volatile uint32_t g_u32HiYear, g_u32LoYear, g_u32HiMonth, g_u32LoMonth, g_u32HiDay, g_u32LoDay;
static volatile uint32_t g_u32HiHour, g_u32LoHour, g_u32HiMin, g_u32LoMin, g_u32HiSec, g_u32LoSec;

/** @endcond HIDDEN_SYMBOLS */


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup RTC_Driver RTC Driver
  @{
*/

/** @addtogroup RTC_EXPORTED_FUNCTIONS RTC Exported Functions
  @{
*/

/**
  * @brief      Initialize RTC module and start counting
  *
  * @param[in]  psPt    Specify the time property and current date and time. It includes:           \n
  *                     u32Year: Year value, range between 2000 ~ 2099.                             \n
  *                     u32Month: Month value, range between 1 ~ 12.                                \n
  *                     u32Day: Day value, range between 1 ~ 31.                                    \n
  *                     u32DayOfWeek: Day of the week. [RTC_SUNDAY / RTC_MONDAY / RTC_TUESDAY /
  *                                                     RTC_WEDNESDAY / RTC_THURSDAY / RTC_FRIDAY /
  *                                                     RTC_SATURDAY]                               \n
  *                     u32Hour: Hour value, range between 0 ~ 23.                                  \n
  *                     u32Minute: Minute value, range between 0 ~ 59.                              \n
  *                     u32Second: Second value, range between 0 ~ 59.                              \n
  *                     u32TimeScale: [RTC_CLOCK_12 / RTC_CLOCK_24]                                 \n
  *                     u8AmPm: [RTC_AM / RTC_PM]                                                   \n
  *
  * @return     None
  *
  * @details    This function is used to: \n
  *                 1. Write initial key to let RTC start count.  \n
  *                 2. Input parameter indicates start date/time. \n
  *                 3. User has to make sure that parameters of RTC date/time are reasonable. \n
  * @note       Null pointer for using default starting date/time.
  */
void RTC_Open(S_RTC_TIME_DATA_T *psPt)
{
    RTC->INIT = RTC_INIT_KEY;

    if (RTC->INIT != RTC_INIT_ACTIVE_Msk)
    {
        RTC->INIT = RTC_INIT_KEY;

        while (RTC->INIT != RTC_INIT_ACTIVE_Msk)
        {
        }
    }

    if (psPt == NULL)
    {
        /* No RTC date/time data */
    }
    else
    {
        /* Set RTC date and time */
        RTC_SetDateAndTime(psPt);
    }
}

/**
  * @brief      Disable RTC Clock
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This API will disable RTC peripheral clock and stops RTC counting.
  */
void RTC_Close(void)
{
    CLK->APBCLK0 &= ~CLK_APBCLK0_RTCCKEN_Msk;
}

/**
 *  @brief    Set Frequency Compensation Data
  *
 *  @param[in]    i32FrequencyX10000    Specify the RTC clock X 10000, ex: 327736512 means 32773.6512.
  *
  * @return     None
  *
  */
void RTC_32KCalibration(int32_t i32FrequencyX10000)
{

    /*
              Frequency counter measurement : 32773.6512 Hz
    */
    uint32_t u32Index;
    uint32_t u32Compensate;

    /* 327736512 %10000 = 6512  */
    u32Compensate = (uint32_t)(i32FrequencyX10000 % 10000);
    /*Fraction Part: (6512 X 64)/10000 = 41.6768(0x2A) => RTC_FREQADJ[5:0]=0x2A*/
    u32Compensate = ((u32Compensate * 64) / 10000);
    u32Compensate &= 0x3F;
    /*
         Formula for 32K compensation is
           FREQADJ = 0~0x00001F00 (Frequency range : 32752Hz ~ 32783Hz)
    */

    if (i32FrequencyX10000 >= (uint32_t)327840000)
    {
        u32Compensate = 0x1F3F;
    }
    else if (i32FrequencyX10000 < (uint32_t)327520000)
    {
        u32Compensate = 0x0;
    }
    else
    {
        /*  Integer Part: 32773 => RTC_FREQADJ[12:8] = 0x15 */
        for (u32Index = 0; u32Index < 0x20 ; u32Index++)
        {
            if ((i32FrequencyX10000 >= 327520000 + (u32Index * 10000)) && (i32FrequencyX10000 < 327520000 + ((u32Index + 1) * 10000)))
            {
                u32Compensate += (u32Index << RTC_FREQADJ_INTEGER_Pos);
                break;
            }
        }
    }


    RTC->FREQADJ = (uint32_t)u32Compensate;
}

/**
  * @brief      Get Current RTC Date and Time
  *
  * @param[out] psPt    The returned pointer is specified the current RTC value. It includes: \n
  *                     u32Year: Year value                                                   \n
  *                     u32Month: Month value                                                 \n
  *                     u32Day: Day value                                                     \n
  *                     u32DayOfWeek: Day of week                                             \n
  *                     u32Hour: Hour value                                                   \n
  *                     u32Minute: Minute value                                               \n
  *                     u32Second: Second value                                               \n
  *                     u32TimeScale: [RTC_CLOCK_12 / RTC_CLOCK_24]                           \n
  *                     u8AmPm: [RTC_AM / RTC_PM]                                             \n
  *
  * @return     None
  *
  * @details    This API is used to get the current RTC date and time value.
  */
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *psPt)
{
    uint32_t u32Tmp;

    psPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;     /* 12/24-hour */
    psPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk; /* Day of the week */

    /* Get [Date digit] data */
    g_u32HiYear  = (RTC->CAL & RTC_CAL_TENYEAR_Msk) >> RTC_CAL_TENYEAR_Pos;
    g_u32LoYear  = (RTC->CAL & RTC_CAL_YEAR_Msk) >> RTC_CAL_YEAR_Pos;
    g_u32HiMonth = (RTC->CAL & RTC_CAL_TENMON_Msk) >> RTC_CAL_TENMON_Pos;
    g_u32LoMonth = (RTC->CAL & RTC_CAL_MON_Msk) >> RTC_CAL_MON_Pos;
    g_u32HiDay   = (RTC->CAL & RTC_CAL_TENDAY_Msk) >> RTC_CAL_TENDAY_Pos;
    g_u32LoDay   = (RTC->CAL & RTC_CAL_DAY_Msk) >> RTC_CAL_DAY_Pos;

    /* Get [Time digit] data */
    g_u32HiHour = (RTC->TIME & RTC_TIME_TENHR_Msk) >> RTC_TIME_TENHR_Pos;
    g_u32LoHour = (RTC->TIME & RTC_TIME_HR_Msk) >> RTC_TIME_HR_Pos;
    g_u32HiMin  = (RTC->TIME & RTC_TIME_TENMIN_Msk) >> RTC_TIME_TENMIN_Pos;
    g_u32LoMin  = (RTC->TIME & RTC_TIME_MIN_Msk) >> RTC_TIME_MIN_Pos;
    g_u32HiSec  = (RTC->TIME & RTC_TIME_TENSEC_Msk) >> RTC_TIME_TENSEC_Pos;
    g_u32LoSec  = (RTC->TIME & RTC_TIME_SEC_Msk) >> RTC_TIME_SEC_Pos;

    /* Compute to 20XX year */
    u32Tmp  = (g_u32HiYear * 10ul);
    u32Tmp += g_u32LoYear;
    psPt->u32Year = u32Tmp + RTC_YEAR2000;

    /* Compute 0~12 month */
    u32Tmp = (g_u32HiMonth * 10ul);
    psPt->u32Month = u32Tmp + g_u32LoMonth;

    /* Compute 0~31 day */
    u32Tmp = (g_u32HiDay * 10ul);
    psPt->u32Day =  u32Tmp  + g_u32LoDay;

    /* Compute 12/24 hour */
    if (psPt->u32TimeScale == RTC_CLOCK_12)
    {
        u32Tmp = (g_u32HiHour * 10ul);
        u32Tmp += g_u32LoHour;
        psPt->u32Hour = u32Tmp;          /* AM: 1~12. PM: 21~32. */

        if (psPt->u32Hour >= 21ul)
        {
            psPt->u32AmPm  = RTC_PM;
            psPt->u32Hour -= 20ul;
        }
        else
        {
            psPt->u32AmPm = RTC_AM;
        }

        u32Tmp  = (g_u32HiMin  * 10ul);
        u32Tmp += g_u32LoMin;
        psPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32HiSec  * 10ul);
        u32Tmp += g_u32LoSec;
        psPt->u32Second = u32Tmp;
    }
    else
    {
        u32Tmp  = (g_u32HiHour * 10ul);
        u32Tmp += g_u32LoHour;
        psPt->u32Hour = u32Tmp;

        u32Tmp  = (g_u32HiMin * 10ul);
        u32Tmp +=  g_u32LoMin;
        psPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32HiSec * 10ul);
        u32Tmp += g_u32LoSec;
        psPt->u32Second = u32Tmp;
    }
}

/**
  * @brief      Get RTC Alarm Date and Time
  *
  * @param[out] psPt    The returned pointer is specified the RTC alarm value. It includes: \n
  *                     u32Year: Year value                                                 \n
  *                     u32Month: Month value                                               \n
  *                     u32Day: Day value                                                   \n
  *                     u32DayOfWeek: Day of week                                           \n
  *                     u32Hour: Hour value                                                 \n
  *                     u32Minute: Minute value                                             \n
  *                     u32Second: Second value                                             \n
  *                     u32TimeScale: [RTC_CLOCK_12 / RTC_CLOCK_24]                         \n
  *                     u8AmPm: [RTC_AM / RTC_PM]                                           \n
  *
  * @return     None
  *
  * @details    This API is used to get the RTC alarm date and time setting.
  */
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *psPt)
{
    uint32_t u32Tmp;

    psPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;     /* 12/24-hour */
    psPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk; /* Day of the week */

    /* Get alarm [Date digit] data */
    g_u32HiYear  = (RTC->CALM & RTC_CALM_TENYEAR_Msk) >> RTC_CALM_TENYEAR_Pos;
    g_u32LoYear  = (RTC->CALM & RTC_CALM_YEAR_Msk) >> RTC_CALM_YEAR_Pos;
    g_u32HiMonth = (RTC->CALM & RTC_CALM_TENMON_Msk) >> RTC_CALM_TENMON_Pos;
    g_u32LoMonth = (RTC->CALM & RTC_CALM_MON_Msk) >> RTC_CALM_MON_Pos;
    g_u32HiDay   = (RTC->CALM & RTC_CALM_TENDAY_Msk) >> RTC_CALM_TENDAY_Pos;
    g_u32LoDay   = (RTC->CALM & RTC_CALM_DAY_Msk) >> RTC_CALM_DAY_Pos;

    /* Get alarm [Time digit] data */
    g_u32HiHour = (RTC->TALM & RTC_TALM_TENHR_Msk) >> RTC_TALM_TENHR_Pos;
    g_u32LoHour = (RTC->TALM & RTC_TALM_HR_Msk) >> RTC_TALM_HR_Pos;
    g_u32HiMin  = (RTC->TALM & RTC_TALM_TENMIN_Msk) >> RTC_TALM_TENMIN_Pos;
    g_u32LoMin  = (RTC->TALM & RTC_TALM_MIN_Msk) >> RTC_TALM_MIN_Pos;
    g_u32HiSec  = (RTC->TALM & RTC_TALM_TENSEC_Msk) >> RTC_TALM_TENSEC_Pos;
    g_u32LoSec  = (RTC->TALM & RTC_TALM_SEC_Msk) >> RTC_TALM_SEC_Pos;

    /* Compute to 20XX year */
    u32Tmp  = (g_u32HiYear * 10ul);
    u32Tmp += g_u32LoYear;
    psPt->u32Year = u32Tmp + RTC_YEAR2000;

    /* Compute 0~12 month */
    u32Tmp = (g_u32HiMonth * 10ul);
    psPt->u32Month = u32Tmp + g_u32LoMonth;

    /* Compute 0~31 day */
    u32Tmp = (g_u32HiDay * 10ul);
    psPt->u32Day = u32Tmp + g_u32LoDay;

    /* Compute 12/24 hour */
    if (psPt->u32TimeScale == RTC_CLOCK_12)
    {
        u32Tmp  = (g_u32HiHour * 10ul);
        u32Tmp += g_u32LoHour;
        psPt->u32Hour = u32Tmp;          /* AM: 1~12. PM: 21~32. */

        if (psPt->u32Hour >= 21ul)
        {
            psPt->u32AmPm  = RTC_PM;
            psPt->u32Hour -= 20ul;
        }
        else
        {
            psPt->u32AmPm = RTC_AM;
        }

        u32Tmp  = (g_u32HiMin * 10ul);
        u32Tmp += g_u32LoMin;
        psPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32HiSec * 10ul);
        u32Tmp += g_u32LoSec;
        psPt->u32Second = u32Tmp;

    }
    else
    {
        u32Tmp  = (g_u32HiHour * 10ul);
        u32Tmp +=  g_u32LoHour;
        psPt->u32Hour = u32Tmp;

        u32Tmp  = (g_u32HiMin * 10ul);
        u32Tmp += g_u32LoMin;
        psPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32HiSec * 10ul);
        u32Tmp += g_u32LoSec;
        psPt->u32Second = u32Tmp;
    }
}

/**
  * @brief      Update Current RTC Date and Time
  *
  * @param[in]  psPt    Specify the time property and current date and time. It includes:           \n
  *                     u32Year: Year value, range between 2000 ~ 2099.                             \n
  *                     u32Month: Month value, range between 1 ~ 12.                                \n
  *                     u32Day: Day value, range between 1 ~ 31.                                    \n
  *                     u32DayOfWeek: Day of the week. [RTC_SUNDAY / RTC_MONDAY / RTC_TUESDAY /
  *                                                     RTC_WEDNESDAY / RTC_THURSDAY / RTC_FRIDAY /
  *                                                     RTC_SATURDAY]                               \n
  *                     u32Hour: Hour value, range between 0 ~ 23.                                  \n
  *                     u32Minute: Minute value, range between 0 ~ 59.                              \n
  *                     u32Second: Second value, range between 0 ~ 59.                              \n
  *                     u32TimeScale: [RTC_CLOCK_12 / RTC_CLOCK_24]                                 \n
  *                     u8AmPm: [RTC_AM / RTC_PM]                                                   \n
  *
  * @return     None
  *
  * @details    This API is used to update current date and time to RTC.
  */
void RTC_SetDateAndTime(S_RTC_TIME_DATA_T *psPt)
{
    uint32_t u32RegCAL, u32RegTIME;

    if (psPt == NULL)
    {
        /* No RTC date/time data */
    }
    else
    {
        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC 24/12 hour setting and Day of the Week                                                      */
        /*-----------------------------------------------------------------------------------------------------*/

        if (psPt->u32TimeScale == RTC_CLOCK_12)
        {
            RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

            /*-------------------------------------------------------------------------------------------------*/
            /* Important, range of 12-hour PM mode is 21 up to 32                                               */
            /*-------------------------------------------------------------------------------------------------*/
            if (psPt->u32AmPm == RTC_PM)
            {
                psPt->u32Hour += 20ul;
            }
        }
        else
        {
            RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        }

        /* Set Day of the Week */
        RTC->WEEKDAY = psPt->u32DayOfWeek;

        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC Current Date and Time                                                                       */
        /*-----------------------------------------------------------------------------------------------------*/
        u32RegCAL  = ((psPt->u32Year - RTC_YEAR2000) / 10ul) << 20;
        u32RegCAL |= (((psPt->u32Year - RTC_YEAR2000) % 10ul) << 16);
        u32RegCAL |= ((psPt->u32Month  / 10ul) << 12);
        u32RegCAL |= ((psPt->u32Month  % 10ul) << 8);
        u32RegCAL |= ((psPt->u32Day    / 10ul) << 4);
        u32RegCAL |= (psPt->u32Day     % 10ul);

        u32RegTIME  = ((psPt->u32Hour   / 10ul) << 20);
        u32RegTIME |= ((psPt->u32Hour   % 10ul) << 16);
        u32RegTIME |= ((psPt->u32Minute / 10ul) << 12);
        u32RegTIME |= ((psPt->u32Minute % 10ul) << 8);
        u32RegTIME |= ((psPt->u32Second / 10ul) << 4);
        u32RegTIME |= (psPt->u32Second % 10ul);

        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC Calender and Time Loading                                                                   */
        /*-----------------------------------------------------------------------------------------------------*/

        RTC->CAL  = (uint32_t)u32RegCAL;
        RTC->TIME = (uint32_t)u32RegTIME;
    }
}

/**
  * @brief      Update RTC Alarm Date and Time
  *
  * @param[in]  psPt    Specify the time property and alarm date and time. It includes:             \n
  *                     u32Year: Year value, range between 2000 ~ 2099.                             \n
  *                     u32Month: Month value, range between 1 ~ 12.                                \n
  *                     u32Day: Day value, range between 1 ~ 31.                                    \n
  *                     u32DayOfWeek: Day of the week. [RTC_SUNDAY / RTC_MONDAY / RTC_TUESDAY /
  *                                                     RTC_WEDNESDAY / RTC_THURSDAY / RTC_FRIDAY /
  *                                                     RTC_SATURDAY]                               \n
  *                     u32Hour: Hour value, range between 0 ~ 23.                                  \n
  *                     u32Minute: Minute value, range between 0 ~ 59.                              \n
  *                     u32Second: Second value, range between 0 ~ 59.                              \n
  *                     u32TimeScale: [RTC_CLOCK_12 / RTC_CLOCK_24]                                 \n
  *                     u8AmPm: [RTC_AM / RTC_PM]                                                   \n
  *
  * @return     None
  *
  * @details    This API is used to update alarm date and time setting to RTC.
  */
void RTC_SetAlarmDateAndTime(S_RTC_TIME_DATA_T *psPt)
{
    uint32_t u32RegCALM, u32RegTALM;

    if (psPt == NULL)
    {
        /* No RTC date/time data */
    }
    else
    {
        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC 24/12 hour setting and Day of the Week                                                      */
        /*-----------------------------------------------------------------------------------------------------*/

        if (psPt->u32TimeScale == RTC_CLOCK_12)
        {
            RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

            /*-------------------------------------------------------------------------------------------------*/
            /* Important, range of 12-hour PM mode is 21 up to 32                                               */
            /*-------------------------------------------------------------------------------------------------*/
            if (psPt->u32AmPm == RTC_PM)
            {
                psPt->u32Hour += 20ul;
            }
        }
        else
        {
            RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        }

        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC Alarm Date and Time                                                                         */
        /*-----------------------------------------------------------------------------------------------------*/
        u32RegCALM  = ((psPt->u32Year - RTC_YEAR2000) / 10ul) << 20;
        u32RegCALM |= (((psPt->u32Year - RTC_YEAR2000) % 10ul) << 16);
        u32RegCALM |= ((psPt->u32Month  / 10ul) << 12);
        u32RegCALM |= ((psPt->u32Month  % 10ul) << 8);
        u32RegCALM |= ((psPt->u32Day    / 10ul) << 4);
        u32RegCALM |= (psPt->u32Day    % 10ul);

        u32RegTALM  = ((psPt->u32Hour   / 10ul) << 20);
        u32RegTALM |= ((psPt->u32Hour   % 10ul) << 16);
        u32RegTALM |= ((psPt->u32Minute / 10ul) << 12);
        u32RegTALM |= ((psPt->u32Minute % 10ul) << 8);
        u32RegTALM |= ((psPt->u32Second / 10ul) << 4);
        u32RegTALM |= (psPt->u32Second % 10ul);


        RTC->CALM = (uint32_t)u32RegCALM;
        RTC->TALM = (uint32_t)u32RegTALM;
    }
}

/**
  * @brief      Update RTC Current Date
  *
  * @param[in]  u32Year         The year calendar digit of current RTC setting.
  * @param[in]  u32Month        The month calendar digit of current RTC setting.
  * @param[in]  u32Day          The day calendar digit of current RTC setting.
  * @param[in]  u32DayOfWeek    The Day of the week. [RTC_SUNDAY / RTC_MONDAY / RTC_TUESDAY /
  *                                                   RTC_WEDNESDAY / RTC_THURSDAY / RTC_FRIDAY /
  *                                                   RTC_SATURDAY]
  *
  * @return     None
  *
  * @details    This API is used to update current date to RTC.
  */
void RTC_SetDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day, uint32_t u32DayOfWeek)
{
    uint32_t u32RegCAL;

    u32RegCAL  = ((u32Year - RTC_YEAR2000) / 10ul) << 20;
    u32RegCAL |= (((u32Year - RTC_YEAR2000) % 10ul) << 16);
    u32RegCAL |= ((u32Month / 10ul) << 12);
    u32RegCAL |= ((u32Month % 10ul) << 8);
    u32RegCAL |= ((u32Day   / 10ul) << 4);
    u32RegCAL |= (u32Day   % 10ul);

    /* Set Day of the Week */
    RTC->WEEKDAY = u32DayOfWeek & RTC_WEEKDAY_WEEKDAY_Msk;

    /* Set RTC Calender Loading */
    RTC->CAL = (uint32_t)u32RegCAL;
}

/**
  * @brief      Update RTC Current Time
  *
  * @param[in]  u32Hour         The hour time digit of current RTC setting.
  * @param[in]  u32Minute       The minute time digit of current RTC setting.
  * @param[in]  u32Second       The second time digit of current RTC setting.
  * @param[in]  u32TimeMode     The 24-Hour / 12-Hour Time Scale Selection. [RTC_CLOCK_12 / RTC_CLOCK_24]
  * @param[in]  u32AmPm         12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [RTC_AM / RTC_PM]
  *
  * @return     None
  *
  * @details    This API is used to update current time to RTC.
  */
void RTC_SetTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm)
{
    uint32_t u32RegTIME;

    /* Important, range of 12-hour PM mode is 21 up to 32 */
    if ((u32TimeMode == RTC_CLOCK_12) && (u32AmPm == RTC_PM))
    {
        u32Hour += 20ul;
    }

    u32RegTIME  = ((u32Hour   / 10ul) << 20);
    u32RegTIME |= ((u32Hour   % 10ul) << 16);
    u32RegTIME |= ((u32Minute / 10ul) << 12);
    u32RegTIME |= ((u32Minute % 10ul) << 8);
    u32RegTIME |= ((u32Second / 10ul) << 4);
    u32RegTIME |= (u32Second % 10ul);

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC 24/12 hour setting and Day of the Week                                                      */
    /*-----------------------------------------------------------------------------------------------------*/
    if (u32TimeMode == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;
    }
    else
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    RTC->TIME = (uint32_t)u32RegTIME;
}

/**
  * @brief      Update RTC Alarm Date
  *
  * @param[in]  u32Year         The year calendar digit of RTC alarm setting.
  * @param[in]  u32Month        The month calendar digit of RTC alarm setting.
  * @param[in]  u32Day          The day calendar digit of RTC alarm setting.
  *
  * @return     None
  *
  * @details    This API is used to update alarm date setting to RTC.
  */
void RTC_SetAlarmDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day)
{
    uint32_t u32RegCALM;

    u32RegCALM  = ((u32Year - RTC_YEAR2000) / 10ul) << 20;
    u32RegCALM |= (((u32Year - RTC_YEAR2000) % 10ul) << 16);
    u32RegCALM |= ((u32Month / 10ul) << 12);
    u32RegCALM |= ((u32Month % 10ul) << 8);
    u32RegCALM |= ((u32Day   / 10ul) << 4);
    u32RegCALM |= (u32Day   % 10ul);

    /* Set RTC Alarm Date */
    RTC->CALM = (uint32_t)u32RegCALM;
}

/**
  * @brief      Update RTC Alarm Time
  *
  * @param[in]  u32Hour         The hour time digit of RTC alarm setting.
  * @param[in]  u32Minute       The minute time digit of RTC alarm setting.
  * @param[in]  u32Second       The second time digit of RTC alarm setting.
  * @param[in]  u32TimeMode     The 24-Hour / 12-Hour Time Scale Selection. [RTC_CLOCK_12 / RTC_CLOCK_24]
  * @param[in]  u32AmPm         12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [RTC_AM / RTC_PM]
  *
  * @return     None
  *
  * @details    This API is used to update alarm time setting to RTC.
  */
void RTC_SetAlarmTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm)
{
    uint32_t u32RegTALM;

    /* Important, range of 12-hour PM mode is 21 up to 32 */
    if((u32TimeMode == (uint32_t)RTC_CLOCK_12) && (u32AmPm == (uint32_t)RTC_PM))
    {
        u32Hour += 20ul;
    }

    u32RegTALM  = ((u32Hour   / 10ul) << 20);
    u32RegTALM |= ((u32Hour   % 10ul) << 16);
    u32RegTALM |= ((u32Minute / 10ul) << 12);
    u32RegTALM |= ((u32Minute % 10ul) << 8);
    u32RegTALM |= ((u32Second / 10ul) << 4);
    u32RegTALM |= (u32Second % 10ul);

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC 24/12 hour setting and Day of the Week                                                      */
    /*-----------------------------------------------------------------------------------------------------*/
    if(u32TimeMode == (uint32_t)RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;
    }
    else
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    /* Set RTC Alarm Time */
    RTC->TALM = (uint32_t)u32RegTALM;
}

/**
  * @brief      Set RTC Alarm Date Mask Function
  *
  * @param[in]  u8IsTenYMsk     1: enable 10-Year digit alarm mask; 0: disabled.
  * @param[in]  u8IsYMsk        1: enable 1-Year digit alarm mask; 0: disabled.
  * @param[in]  u8IsTenMMsk     1: enable 10-Mon digit alarm mask; 0: disabled.
  * @param[in]  u8IsMMsk        1: enable 1-Mon digit alarm mask; 0: disabled.
  * @param[in]  u8IsTenDMsk     1: enable 10-Day digit alarm mask; 0: disabled.
  * @param[in]  u8IsDMsk        1: enable 1-Day digit alarm mask; 0: disabled.
  *
  * @return     None
  *
  * @details    This API is used to enable or disable RTC alarm date mask function.
  */
void RTC_SetAlarmDateMask(uint8_t u8IsTenYMsk, uint8_t u8IsYMsk, uint8_t u8IsTenMMsk, uint8_t u8IsMMsk, uint8_t u8IsTenDMsk, uint8_t u8IsDMsk)
{
    RTC->CAMSK = ((uint32_t)u8IsTenYMsk << RTC_CAMSK_MTENYEAR_Pos) |
                 ((uint32_t)u8IsYMsk    << RTC_CAMSK_MYEAR_Pos) |
                 ((uint32_t)u8IsTenMMsk << RTC_CAMSK_MTENMON_Pos) |
                 ((uint32_t)u8IsMMsk    << RTC_CAMSK_MMON_Pos) |
                 ((uint32_t)u8IsTenDMsk << RTC_CAMSK_MTENDAY_Pos) |
                 ((uint32_t)u8IsDMsk    << RTC_CAMSK_MDAY_Pos);
}

/**
  * @brief      Set RTC Alarm Time Mask Function
  *
  * @param[in]  u8IsTenHMsk     1: enable 10-Hour digit alarm mask; 0: disabled.
  * @param[in]  u8IsHMsk        1: enable 1-Hour digit alarm mask; 0: disabled.
  * @param[in]  u8IsTenMMsk     1: enable 10-Min digit alarm mask; 0: disabled.
  * @param[in]  u8IsMMsk        1: enable 1-Min digit alarm mask; 0: disabled.
  * @param[in]  u8IsTenSMsk     1: enable 10-Sec digit alarm mask; 0: disabled.
  * @param[in]  u8IsSMsk        1: enable 1-Sec digit alarm mask; 0: disabled.
  *
  * @return     None
  *
  * @details    This API is used to enable or disable RTC alarm time mask function.
  */
void RTC_SetAlarmTimeMask(uint8_t u8IsTenHMsk, uint8_t u8IsHMsk, uint8_t u8IsTenMMsk, uint8_t u8IsMMsk, uint8_t u8IsTenSMsk, uint8_t u8IsSMsk)
{
    RTC->TAMSK = ((uint32_t)u8IsTenHMsk << RTC_TAMSK_MTENHR_Pos) |
                 ((uint32_t)u8IsHMsk    << RTC_TAMSK_MHR_Pos) |
                 ((uint32_t)u8IsTenMMsk << RTC_TAMSK_MTENMIN_Pos) |
                 ((uint32_t)u8IsMMsk    << RTC_TAMSK_MMIN_Pos) |
                 ((uint32_t)u8IsTenSMsk << RTC_TAMSK_MTENSEC_Pos) |
                 ((uint32_t)u8IsSMsk    << RTC_TAMSK_MSEC_Pos);
}

/**
  * @brief      Get Day of the Week
  *
  * @param      None
  *
  * @retval     0   Sunday
  * @retval     1   Monday
  * @retval     2   Tuesday
  * @retval     3   Wednesday
  * @retval     4   Thursday
  * @retval     5   Friday
  * @retval     6   Saturday
  *
  * @details    This API is used to get day of the week of current RTC date.
  */
uint32_t RTC_GetDayOfWeek(void)
{
    return (RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk);
}

/**
  * @brief      Set RTC Tick Period Time
  *
  * @param[in]  u32TickSelection    It is used to set the RTC tick period time for Periodic Time Tick request. \n
  *                                 It consists of:
  *                                     - \ref RTC_TICK_1_SEC     : Time tick is 1 second
  *                                     - \ref RTC_TICK_1_2_SEC   : Time tick is 1/2 second
  *                                     - \ref RTC_TICK_1_4_SEC   : Time tick is 1/4 second
  *                                     - \ref RTC_TICK_1_8_SEC   : Time tick is 1/8 second
  *                                     - \ref RTC_TICK_1_16_SEC  : Time tick is 1/16 second
  *                                     - \ref RTC_TICK_1_32_SEC  : Time tick is 1/32 second
  *                                     - \ref RTC_TICK_1_64_SEC  : Time tick is 1/64 second
  *                                     - \ref RTC_TICK_1_128_SEC : Time tick is 1/128 second
  *
  * @return     None
  *
  * @details    This API is used to set RTC tick period time for each tick interrupt.
  */
void RTC_SetTickPeriod(uint32_t u32TickSelection)
{
    RTC->TICK = (RTC->TICK & ~RTC_TICK_TICK_Msk) | u32TickSelection;
}

/**
  * @brief      Enable RTC Interrupt
  *
  * @param[in]  u32IntFlagMask      Specify the interrupt source. It consists of:
  *                                     - \ref RTC_INTEN_ALMIEN_Msk   : Alarm interrupt
  *                                     - \ref RTC_INTEN_TICKIEN_Msk  : Tick interrupt
  *
  * @return     None
  *
  * @details    This API is used to enable the specify RTC interrupt function.
  */
void RTC_EnableInt(uint32_t u32IntFlagMask)
{
    RTC->INTEN |= u32IntFlagMask;
}

/**
  * @brief      Disable RTC Interrupt
  *
  * @param[in]  u32IntFlagMask      Specify the interrupt source. It consists of:
  *                                     - \ref RTC_INTEN_ALMIEN_Msk   : Alarm interrupt
  *                                     - \ref RTC_INTEN_TICKIEN_Msk  : Tick interrupt
  *
  * @return     None
  *
  * @details    This API is used to disable the specify RTC interrupt function.
  */
void RTC_DisableInt(uint32_t u32IntFlagMask)
{
    RTC->INTEN  &= ~u32IntFlagMask;
    RTC->INTSTS = u32IntFlagMask;
}

/*@}*/ /* end of group RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group RTC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

