/**************************************************************************//**
 * @file     rtc.c
 * @version  V3.00
 * @brief    Real Time Clock(RTC) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @cond HIDDEN_SYMBOLS */
/*---------------------------------------------------------------------------------------------------------*/
/* Global file scope (static) variables                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
static volatile uint32_t g_u32hiYear, g_u32loYear, g_u32hiMonth, g_u32loMonth, g_u32hiDay, g_u32loDay;
static volatile uint32_t g_u32hiHour, g_u32loHour, g_u32hiMin, g_u32loMin, g_u32hiSec, g_u32loSec;

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
  * @param[in]  sPt     Specify the time property and current date and time. It includes:           \n
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
  *                 4. Enable frequency dynamic compensation function. \n
  * @note       Null pointer for using default starting date/time.
  */
void RTC_Open(S_RTC_TIME_DATA_T *sPt)
{
    RTC->INIT = RTC_INIT_KEY;

    if(RTC->INIT != RTC_INIT_ACTIVE_Msk)
    {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk) {}
    }

    if(sPt != 0)
    {
        /* Enable frequency dynamic compensation function */
        RTC->CLKFMT |= RTC_CLKFMT_DCOMPEN_Msk;

        /* Set RTC date and time */
        RTC_SetDateAndTime(sPt);
    }
}

/**
  * @brief      Disable RTC Clock
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This API will disable RTC peripheral clock.
  */
void RTC_Close(void)
{
    if((__PC()&NS_OFFSET) != NS_OFFSET)
    {
        /* Only available in Secure code */
        CLK->APBCLK0 &= ~CLK_APBCLK0_RTCCKEN_Msk;
    }
}

/**
  * @brief      Set 32K Frequency Compensation Data
  *
  * @param[in]  i32FrequencyX10000  Specify the RTC clock X10000, ex: 327736512 means 32773.6512.
  *
  * @return     None
  *
  * @details    This API is used to compensate the 32 kHz frequency by current LXT frequency for RTC application.
  */
void RTC_32KCalibration(int32_t i32FrequencyX10000)
{
    int32_t i32RegInt, i32RegFra;

    /* Compute integer and fraction for RTC FCR register */
    i32RegInt = (i32FrequencyX10000 / 10000) - RTC_FCR_REFERENCE;
    i32RegFra = ((((i32FrequencyX10000 % 10000)) * 64) + 5000) / 10000;

    if(i32RegFra >= 0x40)
    {
        i32RegFra = 0x0;
        i32RegInt++;
    }

    /* Judge Integer part is reasonable */
    if((i32RegInt >= 0) && (i32RegInt <= 31))
    {
        while((RTC->FREQADJ & RTC_FREQADJ_FCRBUSY_Msk) == RTC_FREQADJ_FCRBUSY_Msk) {}
        RTC->FREQADJ = (uint32_t)((i32RegInt << 8) | i32RegFra);
        while((RTC->FREQADJ & RTC_FREQADJ_FCRBUSY_Msk) == RTC_FREQADJ_FCRBUSY_Msk) {}
    }
}

/**
  * @brief      Get Current RTC Date and Time
  *
  * @param[out] sPt     The returned pointer is specified the current RTC value. It includes: \n
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
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Tmp;

    sPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;     /* 12/24-hour */
    sPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk; /* Day of the week */

    /* Get [Date digit] data */
    g_u32hiYear  = (RTC->CAL & RTC_CAL_TENYEAR_Msk) >> RTC_CAL_TENYEAR_Pos;
    g_u32loYear  = (RTC->CAL & RTC_CAL_YEAR_Msk) >> RTC_CAL_YEAR_Pos;
    g_u32hiMonth = (RTC->CAL & RTC_CAL_TENMON_Msk) >> RTC_CAL_TENMON_Pos;
    g_u32loMonth = (RTC->CAL & RTC_CAL_MON_Msk) >> RTC_CAL_MON_Pos;
    g_u32hiDay   = (RTC->CAL & RTC_CAL_TENDAY_Msk) >> RTC_CAL_TENDAY_Pos;
    g_u32loDay   = (RTC->CAL & RTC_CAL_DAY_Msk) >> RTC_CAL_DAY_Pos;

    /* Get [Time digit] data */
    g_u32hiHour = (RTC->TIME & RTC_TIME_TENHR_Msk) >> RTC_TIME_TENHR_Pos;
    g_u32loHour = (RTC->TIME & RTC_TIME_HR_Msk) >> RTC_TIME_HR_Pos;
    g_u32hiMin  = (RTC->TIME & RTC_TIME_TENMIN_Msk) >> RTC_TIME_TENMIN_Pos;
    g_u32loMin  = (RTC->TIME & RTC_TIME_MIN_Msk) >> RTC_TIME_MIN_Pos;
    g_u32hiSec  = (RTC->TIME & RTC_TIME_TENSEC_Msk) >> RTC_TIME_TENSEC_Pos;
    g_u32loSec  = (RTC->TIME & RTC_TIME_SEC_Msk) >> RTC_TIME_SEC_Pos;

    /* Compute to 20XX year */
    u32Tmp  = (g_u32hiYear * 10UL);
    u32Tmp += g_u32loYear;
    sPt->u32Year = u32Tmp + (uint32_t)RTC_YEAR2000;

    /* Compute 0~12 month */
    u32Tmp = (g_u32hiMonth * 10UL);
    sPt->u32Month = u32Tmp + g_u32loMonth;

    /* Compute 0~31 day */
    u32Tmp = (g_u32hiDay * 10UL);
    sPt->u32Day = u32Tmp + g_u32loDay;

    /* Compute 12/24 hour */
    if(sPt->u32TimeScale == (uint32_t)RTC_CLOCK_12)
    {
        u32Tmp  = (g_u32hiHour * 10UL);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;          /* AM: 1~12. PM: 21~32. */

        if(sPt->u32Hour >= 21UL)
        {
            sPt->u32AmPm  = (uint32_t)RTC_PM;
            sPt->u32Hour -= 20UL;
        }
        else
        {
            sPt->u32AmPm = (uint32_t)RTC_AM;
        }

        u32Tmp  = (g_u32hiMin  * 10UL);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec  * 10UL);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }
    else
    {
        u32Tmp  = (g_u32hiHour * 10UL);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;

        u32Tmp  = (g_u32hiMin * 10UL);
        u32Tmp +=  g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10UL);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }
}

/**
  * @brief      Get RTC Alarm Date and Time
  *
  * @param[out] sPt     The returned pointer is specified the RTC alarm value. It includes: \n
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
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Tmp;

    sPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;     /* 12/24-hour */
    sPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk; /* Day of the week */

    /* Get alarm [Date digit] data */
    g_u32hiYear  = (RTC->CALM & RTC_CALM_TENYEAR_Msk) >> RTC_CALM_TENYEAR_Pos;
    g_u32loYear  = (RTC->CALM & RTC_CALM_YEAR_Msk) >> RTC_CALM_YEAR_Pos;
    g_u32hiMonth = (RTC->CALM & RTC_CALM_TENMON_Msk) >> RTC_CALM_TENMON_Pos;
    g_u32loMonth = (RTC->CALM & RTC_CALM_MON_Msk) >> RTC_CALM_MON_Pos;
    g_u32hiDay   = (RTC->CALM & RTC_CALM_TENDAY_Msk) >> RTC_CALM_TENDAY_Pos;
    g_u32loDay   = (RTC->CALM & RTC_CALM_DAY_Msk) >> RTC_CALM_DAY_Pos;

    /* Get alarm [Time digit] data */
    g_u32hiHour = (RTC->TALM & RTC_TALM_TENHR_Msk) >> RTC_TALM_TENHR_Pos;
    g_u32loHour = (RTC->TALM & RTC_TALM_HR_Msk) >> RTC_TALM_HR_Pos;
    g_u32hiMin  = (RTC->TALM & RTC_TALM_TENMIN_Msk) >> RTC_TALM_TENMIN_Pos;
    g_u32loMin  = (RTC->TALM & RTC_TALM_MIN_Msk) >> RTC_TALM_MIN_Pos;
    g_u32hiSec  = (RTC->TALM & RTC_TALM_TENSEC_Msk) >> RTC_TALM_TENSEC_Pos;
    g_u32loSec  = (RTC->TALM & RTC_TALM_SEC_Msk) >> RTC_TALM_SEC_Pos;

    /* Compute to 20XX year */
    u32Tmp  = (g_u32hiYear * 10UL);
    u32Tmp += g_u32loYear;
    sPt->u32Year = u32Tmp + (uint32_t)RTC_YEAR2000;

    /* Compute 0~12 month */
    u32Tmp = (g_u32hiMonth * 10UL);
    sPt->u32Month = u32Tmp + g_u32loMonth;

    /* Compute 0~31 day */
    u32Tmp = (g_u32hiDay * 10UL);
    sPt->u32Day = u32Tmp + g_u32loDay;

    /* Compute 12/24 hour */
    if(sPt->u32TimeScale == (uint32_t)RTC_CLOCK_12)
    {
        u32Tmp  = (g_u32hiHour * 10UL);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;          /* AM: 1~12. PM: 21~32. */

        if(sPt->u32Hour >= 21UL)
        {
            sPt->u32AmPm  = (uint32_t)RTC_PM;
            sPt->u32Hour -= 20UL;
        }
        else
        {
            sPt->u32AmPm = (uint32_t)RTC_AM;
        }

        u32Tmp  = (g_u32hiMin * 10UL);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10UL);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }
    else
    {
        u32Tmp  = (g_u32hiHour * 10UL);
        u32Tmp +=  g_u32loHour;
        sPt->u32Hour = u32Tmp;

        u32Tmp  = (g_u32hiMin * 10UL);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10UL);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }
}

/**
  * @brief      Update Current RTC Date and Time
  *
  * @param[in]  sPt     Specify the time property and current date and time. It includes:           \n
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
void RTC_SetDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32RegCAL, u32RegTIME;

    if(sPt != 0)
    {
        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC 24/12 hour setting and Day of the Week                                                      */
        /*-----------------------------------------------------------------------------------------------------*/
        if(sPt->u32TimeScale == (uint32_t)RTC_CLOCK_12)
        {
            RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

            /*-------------------------------------------------------------------------------------------------*/
            /* Important, range of 12-hour PM mode is 21 up to 32                                               */
            /*-------------------------------------------------------------------------------------------------*/
            if(sPt->u32AmPm == (uint32_t)RTC_PM)
            {
                sPt->u32Hour += 20UL;
            }
        }
        else
        {
            RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        }

        /* Set Day of the Week */
        RTC->WEEKDAY = sPt->u32DayOfWeek;

        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC Current Date and Time                                                                       */
        /*-----------------------------------------------------------------------------------------------------*/
        u32RegCAL  = ((sPt->u32Year - (uint32_t)RTC_YEAR2000) / 10UL) << 20;
        u32RegCAL |= (((sPt->u32Year - (uint32_t)RTC_YEAR2000) % 10UL) << 16);
        u32RegCAL |= ((sPt->u32Month  / 10UL) << 12);
        u32RegCAL |= ((sPt->u32Month  % 10UL) << 8);
        u32RegCAL |= ((sPt->u32Day    / 10UL) << 4);
        u32RegCAL |= (sPt->u32Day     % 10UL);

        u32RegTIME  = ((sPt->u32Hour   / 10UL) << 20);
        u32RegTIME |= ((sPt->u32Hour   % 10UL) << 16);
        u32RegTIME |= ((sPt->u32Minute / 10UL) << 12);
        u32RegTIME |= ((sPt->u32Minute % 10UL) << 8);
        u32RegTIME |= ((sPt->u32Second / 10UL) << 4);
        u32RegTIME |= (sPt->u32Second % 10UL);

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
  * @param[in]  sPt     Specify the time property and alarm date and time. It includes:             \n
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
void RTC_SetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32RegCALM, u32RegTALM;

    if(sPt != 0)
    {
        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC 24/12 hour setting and Day of the Week                                                      */
        /*-----------------------------------------------------------------------------------------------------*/
        if(sPt->u32TimeScale == (uint32_t)RTC_CLOCK_12)
        {
            RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

            /*-------------------------------------------------------------------------------------------------*/
            /* Important, range of 12-hour PM mode is 21 up to 32                                               */
            /*-------------------------------------------------------------------------------------------------*/
            if(sPt->u32AmPm == (uint32_t)RTC_PM)
            {
                sPt->u32Hour += 20UL;
            }
        }
        else
        {
            RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        }

        /*-----------------------------------------------------------------------------------------------------*/
        /* Set RTC Alarm Date and Time                                                                         */
        /*-----------------------------------------------------------------------------------------------------*/
        u32RegCALM  = ((sPt->u32Year - (uint32_t)RTC_YEAR2000) / 10UL) << 20;
        u32RegCALM |= (((sPt->u32Year - (uint32_t)RTC_YEAR2000) % 10UL) << 16);
        u32RegCALM |= ((sPt->u32Month  / 10UL) << 12);
        u32RegCALM |= ((sPt->u32Month  % 10UL) << 8);
        u32RegCALM |= ((sPt->u32Day    / 10UL) << 4);
        u32RegCALM |= (sPt->u32Day    % 10UL);

        u32RegTALM  = ((sPt->u32Hour   / 10UL) << 20);
        u32RegTALM |= ((sPt->u32Hour   % 10UL) << 16);
        u32RegTALM |= ((sPt->u32Minute / 10UL) << 12);
        u32RegTALM |= ((sPt->u32Minute % 10UL) << 8);
        u32RegTALM |= ((sPt->u32Second / 10UL) << 4);
        u32RegTALM |= (sPt->u32Second % 10UL);

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

    u32RegCAL  = ((u32Year - (uint32_t)RTC_YEAR2000) / 10UL) << 20;
    u32RegCAL |= (((u32Year - (uint32_t)RTC_YEAR2000) % 10UL) << 16);
    u32RegCAL |= ((u32Month / 10UL) << 12);
    u32RegCAL |= ((u32Month % 10UL) << 8);
    u32RegCAL |= ((u32Day   / 10UL) << 4);
    u32RegCAL |= (u32Day   % 10UL);


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
    if((u32TimeMode == (uint32_t)RTC_CLOCK_12) && (u32AmPm == (uint32_t)RTC_PM))
    {
        u32Hour += 20UL;
    }

    u32RegTIME  = ((u32Hour   / 10UL) << 20);
    u32RegTIME |= ((u32Hour   % 10UL) << 16);
    u32RegTIME |= ((u32Minute / 10UL) << 12);
    u32RegTIME |= ((u32Minute % 10UL) << 8);
    u32RegTIME |= ((u32Second / 10UL) << 4);
    u32RegTIME |= (u32Second % 10UL);

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

    u32RegCALM  = ((u32Year - (uint32_t)RTC_YEAR2000) / 10UL) << 20;
    u32RegCALM |= (((u32Year - (uint32_t)RTC_YEAR2000) % 10UL) << 16);
    u32RegCALM |= ((u32Month / 10UL) << 12);
    u32RegCALM |= ((u32Month % 10UL) << 8);
    u32RegCALM |= ((u32Day   / 10UL) << 4);
    u32RegCALM |= (u32Day   % 10UL);


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
        u32Hour += 20UL;
    }

    u32RegTALM  = ((u32Hour   / 10UL) << 20);
    u32RegTALM |= ((u32Hour   % 10UL) << 16);
    u32RegTALM |= ((u32Minute / 10UL) << 12);
    u32RegTALM |= ((u32Minute % 10UL) << 8);
    u32RegTALM |= ((u32Second / 10UL) << 4);
    u32RegTALM |= (u32Second % 10UL);

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
  *                                     - \ref RTC_INTEN_TAMP0IEN_Msk : Tamper 0 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP1IEN_Msk : Tamper 1 or Pair 0 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP2IEN_Msk : Tamper 2 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP3IEN_Msk : Tamper 3 or Pair 1 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP4IEN_Msk : Tamper 4 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP5IEN_Msk : Tamper 5 or Pair 2 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_CLKFIEN_Msk  : LXT Clock Frequency Monitor Fail interrupt
  *                                     - \ref RTC_INTEN_CLKSTIEN_Msk : LXT Clock Frequency Monitor Stop interrupt
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
  *                                     - \ref RTC_INTEN_TAMP0IEN_Msk : Tamper 0 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP1IEN_Msk : Tamper 1 or Pair 0 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP2IEN_Msk : Tamper 2 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP3IEN_Msk : Tamper 3 or Pair 1 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP4IEN_Msk : Tamper 4 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_TAMP5IEN_Msk : Tamper 5 or Pair 2 Pin Event Detection interrupt
  *                                     - \ref RTC_INTEN_CLKFIEN_Msk  : LXT Clock Frequency Monitor Fail interrupt
  *                                     - \ref RTC_INTEN_CLKSTIEN_Msk : LXT Clock Frequency Monitor Stop interrupt
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

/**
  * @brief      Enable Spare Registers Access
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This API is used to enable the spare registers 0~19 can be accessed.
  */
void RTC_EnableSpareAccess(void)
{
    RTC->SPRCTL |= RTC_SPRCTL_SPRRWEN_Msk;
}

/**
  * @brief      Disable Spare Register
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This API is used to disable the spare register 0~19 cannot be accessed.
  */
void RTC_DisableSpareRegister(void)
{
    RTC->SPRCTL &= ~RTC_SPRCTL_SPRRWEN_Msk;
}

/**
  * @brief      Static Tamper Detect
  *
  * @param[in]  u32TamperSelect     Tamper pin select. Possible options are
  *                                 - \ref RTC_TAMPER5_SELECT
  *                                 - \ref RTC_TAMPER4_SELECT
  *                                 - \ref RTC_TAMPER3_SELECT
  *                                 - \ref RTC_TAMPER2_SELECT
  *                                 - \ref RTC_TAMPER1_SELECT
  *                                 - \ref RTC_TAMPER0_SELECT
  *
  * @param[in]  u32DetecLevel       Tamper pin detection level select. Possible options are
  *                                 - \ref RTC_TAMPER_HIGH_LEVEL_DETECT
  *                                 - \ref RTC_TAMPER_LOW_LEVEL_DETECT
  *
  * @param[in]  u32DebounceEn       Tamper pin de-bounce enable
  *                                 - \ref RTC_TAMPER_DEBOUNCE_ENABLE
  *                                 - \ref RTC_TAMPER_DEBOUNCE_DISABLE
  *
  * @return     None
  *
  * @details    This API is used to enable the tamper pin detect function with specify trigger condition.
  *             User need disable dynamic tamper function before use this API.
  */
void RTC_StaticTamperEnable(uint32_t u32TamperSelect, uint32_t u32DetecLevel, uint32_t u32DebounceEn)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;

    u32Reg = RTC->TAMPCTL;

    u32TmpReg = (RTC_TAMPCTL_TAMP0EN_Msk | (u32DetecLevel << RTC_TAMPCTL_TAMP0LV_Pos) |
                 (u32DebounceEn << RTC_TAMPCTL_TAMP0DBEN_Pos));

    for(i = 0UL; i < (uint32_t)RTC_MAX_TAMPER_PIN_NUM; i++)
    {
        if(u32TamperSelect & (0x1UL << i))
        {
            u32Reg &= ~((RTC_TAMPCTL_TAMP0EN_Msk | RTC_TAMPCTL_TAMP0LV_Msk | RTC_TAMPCTL_TAMP0DBEN_Msk) << (i * 4UL));
            u32Reg |= (u32TmpReg << (i * 4UL));
        }
    }

    RTC->TAMPCTL = u32Reg;

}

/**
  * @brief      Static Tamper Disable
  *
  * @param[in]  u32TamperSelect     Tamper pin select. Possible options are
  *                                 - \ref RTC_TAMPER5_SELECT
  *                                 - \ref RTC_TAMPER4_SELECT
  *                                 - \ref RTC_TAMPER3_SELECT
  *                                 - \ref RTC_TAMPER2_SELECT
  *                                 - \ref RTC_TAMPER1_SELECT
  *                                 - \ref RTC_TAMPER0_SELECT
  *
  * @return     None
  *
  * @details    This API is used to disable the static tamper pin detect.
  */
void RTC_StaticTamperDisable(uint32_t u32TamperSelect)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;

    u32Reg = RTC->TAMPCTL;

    u32TmpReg = (RTC_TAMPCTL_TAMP0EN_Msk);

    for(i = 0UL; i < (uint32_t)RTC_MAX_TAMPER_PIN_NUM; i++)
    {
        if(u32TamperSelect & (0x1UL << i))
        {
            u32Reg &= ~(u32TmpReg << (i * 4UL));
        }
    }

    RTC->TAMPCTL = u32Reg;
}

/**
  * @brief      Dynamic Tamper Detect
  *
  * @param[in]  u32PairSel          Tamper pin detection enable. Possible options are
  *                                 - \ref RTC_PAIR0_SELECT
  *                                 - \ref RTC_PAIR1_SELECT
  *                                 - \ref RTC_PAIR2_SELECT
  *
  * @param[in]  u32DebounceEn       Tamper pin de-bounce enable
  *                                 - \ref RTC_TAMPER_DEBOUNCE_ENABLE
  *                                 - \ref RTC_TAMPER_DEBOUNCE_DISABLE
  *
  *  @param[in]  u32Pair1Source     Dynamic Pair 1 Input Source Select
  *                                 0: Pair 1 source select tamper 2
  *                                 1: Pair 1 source select tamper 0
  *
  *  @param[in]  u32Pair2Source     Dynamic Pair 2 Input Source Select
  *                                 0: Pair 2 source select tamper 4
  *                                 1: Pair 2 source select tamper 0
  *
  * @return     None
  *
  * @details    This API is used to enable the dynamic tamper.
  */
void RTC_DynamicTamperEnable(uint32_t u32PairSel, uint32_t u32DebounceEn, uint32_t u32Pair1Source, uint32_t u32Pair2Source)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;
    uint32_t u32Tamper2Debounce, u32Tamper4Debounce;

    u32Reg = RTC->TAMPCTL;
    u32Reg &= ~(RTC_TAMPCTL_TAMP0EN_Msk | RTC_TAMPCTL_TAMP1EN_Msk | RTC_TAMPCTL_TAMP2EN_Msk |
                RTC_TAMPCTL_TAMP3EN_Msk | RTC_TAMPCTL_TAMP4EN_Msk | RTC_TAMPCTL_TAMP5EN_Msk);

    u32Tamper2Debounce = u32Reg & RTC_TAMPCTL_TAMP2DBEN_Msk;
    u32Tamper4Debounce = u32Reg & RTC_TAMPCTL_TAMP4DBEN_Msk;

    u32Reg &= ~(RTC_TAMPCTL_TAMP0EN_Msk | RTC_TAMPCTL_TAMP1EN_Msk | RTC_TAMPCTL_TAMP2EN_Msk |
                RTC_TAMPCTL_TAMP3EN_Msk | RTC_TAMPCTL_TAMP4EN_Msk | RTC_TAMPCTL_TAMP5EN_Msk);
    u32Reg &= ~(RTC_TAMPCTL_DYN1ISS_Msk | RTC_TAMPCTL_DYN2ISS_Msk);
    u32Reg |= ((u32Pair1Source & 0x1UL) << RTC_TAMPCTL_DYN1ISS_Pos) | ((u32Pair2Source & 0x1UL) << RTC_TAMPCTL_DYN2ISS_Pos);

    if(u32DebounceEn)
    {
        u32TmpReg = (RTC_TAMPCTL_TAMP0EN_Msk | RTC_TAMPCTL_TAMP1EN_Msk |
                     RTC_TAMPCTL_TAMP0DBEN_Msk | RTC_TAMPCTL_TAMP1DBEN_Msk | RTC_TAMPCTL_DYNPR0EN_Msk);
    }
    else
    {
        u32TmpReg = (RTC_TAMPCTL_TAMP0EN_Msk | RTC_TAMPCTL_TAMP1EN_Msk | RTC_TAMPCTL_DYNPR0EN_Msk);
    }

    for(i = 0UL; i < (uint32_t)RTC_MAX_PAIR_NUM; i++)
    {
        if(u32PairSel & (0x1UL << i))
        {
            u32Reg &= ~((RTC_TAMPCTL_TAMP0DBEN_Msk | RTC_TAMPCTL_TAMP1DBEN_Msk) << (i * 8UL));
            u32Reg |= (u32TmpReg << (i * 8UL));
        }
    }

    if((u32Pair1Source) && (u32PairSel & (uint32_t)RTC_PAIR1_SELECT))
    {
        u32Reg &= ~RTC_TAMPCTL_TAMP2EN_Msk;
        u32Reg |= u32Tamper2Debounce;
    }

    if((u32Pair2Source) && (u32PairSel & (uint32_t)RTC_PAIR2_SELECT))
    {
        u32Reg &= ~RTC_TAMPCTL_TAMP4EN_Msk;
        u32Reg |= u32Tamper4Debounce;
    }

    RTC->TAMPCTL = u32Reg;
}

/**
  * @brief      Dynamic Tamper Disable
  *
  * @param[in]  u32PairSel          Tamper pin detection enable. Possible options are
  *                                 - \ref RTC_PAIR0_SELECT
  *                                 - \ref RTC_PAIR1_SELECT
  *                                 - \ref RTC_PAIR2_SELECT
  *
  * @return     None
  *
  * @details    This API is used to disable the dynamic tamper.
  */
void RTC_DynamicTamperDisable(uint32_t u32PairSel)
{
    uint32_t i;
    uint32_t u32Reg;
    uint32_t u32TmpReg;
    uint32_t u32Tamper2En = 0UL, u32Tamper4En = 0UL;

    u32Reg = RTC->TAMPCTL;

    if((u32Reg & (uint32_t)RTC_TAMPCTL_DYN1ISS_Msk) && (u32PairSel & (uint32_t)RTC_PAIR1_SELECT))
    {
        u32Tamper2En = u32Reg & RTC_TAMPCTL_TAMP2EN_Msk;
    }

    if((u32Reg & (uint32_t)RTC_TAMPCTL_DYN2ISS_Msk) && (u32PairSel & (uint32_t)RTC_PAIR2_SELECT))
    {
        u32Tamper4En = u32Reg & RTC_TAMPCTL_TAMP4EN_Msk;
    }

    u32TmpReg = (RTC_TAMPCTL_TAMP0EN_Msk | RTC_TAMPCTL_TAMP1EN_Msk | RTC_TAMPCTL_DYNPR0EN_Msk);

    for(i = 0UL; i < (uint32_t)RTC_MAX_PAIR_NUM; i++)
    {
        if(u32PairSel & (0x1UL << i))
        {
            u32Reg &= ~(u32TmpReg << ((i * 8UL)));
        }
    }

    u32Reg |= (u32Tamper2En | u32Tamper4En);

    RTC->TAMPCTL = u32Reg;
}

/**
  * @brief      Config Dynamic Tamper
  *
  * @param[in]  u32ChangeRate       The dynamic tamper output change rate
  *                                 - \ref RTC_2POW10_CLK
  *                                 - \ref RTC_2POW11_CLK
  *                                 - \ref RTC_2POW12_CLK
  *                                 - \ref RTC_2POW13_CLK
  *                                 - \ref RTC_2POW14_CLK
  *                                 - \ref RTC_2POW15_CLK
  *                                 - \ref RTC_2POW16_CLK
  *                                 - \ref RTC_2POW17_CLK
  *
  * @param[in]  u32SeedReload       Reload new seed or not
  *                                 0: not reload new seed
  *                                 1: reload new seed
  *
  * @param[in]  u32RefPattern       Reference pattern
  *                                 - \ref RTC_REF_RANDOM_PATTERN
  *                                 - \ref RTC_REF_SEED_VALUE
  *
  * @param[in]  u32Seed             Seed Value (0x0 ~ 0xFFFFFFFF)
  *
  * @return     None
  *
  * @details    This API is used to config dynamic tamper setting.
  */
void RTC_DynamicTamperConfig(uint32_t u32ChangeRate, uint32_t u32SeedReload, uint32_t u32RefPattern, uint32_t u32Seed)
{
    uint32_t u32Reg;

    u32Reg = RTC->TAMPCTL;

    u32Reg &= ~(RTC_TAMPCTL_DYNSRC_Msk | RTC_TAMPCTL_SEEDRLD_Msk | RTC_TAMPCTL_DYNRATE_Msk);

    u32Reg |= (u32ChangeRate) | ((u32SeedReload & 0x1UL) << RTC_TAMPCTL_SEEDRLD_Pos) |
              (u32RefPattern << RTC_TAMPCTL_DYNSRC_Pos);

    RTC->TAMPSEED = u32Seed; /* need set seed value before re-loade seed */
    RTC->TAMPCTL = u32Reg;
}

/**
  * @brief      Set RTC Clock Source
  *
  * @param[in]  u32ClkSrc       u32ClkSrc is the RTC clock source. It could be
  *                             - \ref RTC_CLOCK_SOURCE_LXT
  *                             - \ref RTC_CLOCK_SOURCE_LIRC
  *                             - \ref RTC_CLOCK_SOURCE_LIRC32K
  *
  * @retval     RTC_CLOCK_SOURCE_LXT
  * @retval     RTC_CLOCK_SOURCE_LIRC
  * @retval     RTC_CLOCK_SOURCE_LIRC32K
  *
  * @details    This API is used to get the setting of RTC clock source.
  *             User must to enable the selected clock source by themselves executing perform this API.
  */
uint32_t RTC_SetClockSource(uint32_t u32ClkSrc)
{
    uint32_t u32TrimDefault = inpw(SYS_BASE + 0x14Cul);

    if(u32ClkSrc == RTC_CLOCK_SOURCE_LXT)
    {
        /* RTC clock source is external LXT */
        RTC->LXTCTL &= ~RTC_LXTCTL_RTCCKSEL_Msk;
        RTC->LXTCTL &= ~RTC_LXTCTL_C32KSEL_Msk;

        return RTC_CLOCK_SOURCE_LXT;
    }
    else if(u32ClkSrc == RTC_CLOCK_SOURCE_LIRC32K)
    {
        /* Load LIRC32 trim setting */
        RTC->LXTCTL = ((RTC->LXTCTL & ~(0x1FFul << 16)) | ((u32TrimDefault & 0x1FFul) << 16));

        /* RTC clock source is LIRC32K */
        RTC->LXTCTL |= RTC_LXTCTL_LIRC32KEN_Msk;
        RTC->LXTCTL &= ~RTC_LXTCTL_RTCCKSEL_Msk;
        RTC->LXTCTL |= RTC_LXTCTL_C32KSEL_Msk;

        return RTC_CLOCK_SOURCE_LIRC32K;
    }
    else if(u32ClkSrc == RTC_CLOCK_SOURCE_LIRC)
    {
        /* RTC clock source is LIRC */
        RTC->LXTCTL |= RTC_LXTCTL_RTCCKSEL_Msk;

        return RTC_CLOCK_SOURCE_LIRC;
    }
    else
    {
        /* Set the default RTC clock source is LIRC */
        RTC->LXTCTL |= RTC_LXTCTL_RTCCKSEL_Msk;

        return RTC_CLOCK_SOURCE_LIRC;
    }
}

/**
 * @brief       Set RTC GPIO Operation Mode
 *
 * @param[in]   u32Pin          The single pin of GPIO-F port.
 *                              It could be 4~11, which means PF.4~PF.11.
 * @param[in]   u32Mode         Operation mode. It could be
 *                              - \ref RTC_IO_MODE_INPUT
 *                              - \ref RTC_IO_MODE_OUTPUT
 *                              - \ref RTC_IO_MODE_OPEN_DRAIN
 *                              - \ref RTC_IO_MODE_QUASI
 * @param[in]   u32DigitalCtl   The digital input path control of specified pin. It could be
 *                              - \ref RTC_IO_DIGITAL_ENABLE
 *                              - \ref RTC_IO_DIGITAL_DISABLE
 * @param[in]   u32PullCtl      The pull-up or pull-down control of specified pin. It could be
 *                              - \ref RTC_IO_PULL_UP_DOWN_DISABLE
 *                              - \ref RTC_IO_PULL_UP_ENABLE
 *                              - \ref RTC_IO_PULL_DOWN_ENABLE
 * @param[in]   u32OutputLevel  The I/O output level. 0: output low; 1: output high.
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO operation mode controlled by RTC module.
 */
void RTC_SetGPIOMode(uint32_t u32PFPin, uint32_t u32Mode, uint32_t u32DigitalCtl, uint32_t u32PullCtl, uint32_t u32OutputLevel)
{
    uint32_t u32Offset;

    if((u32PFPin == 4) || (u32PFPin == 5) || (u32PFPin == 6) || (u32PFPin == 7))
    {
        u32Offset = u32PFPin - 4;

        RTC_SET_IOCTL_BY_RTC(RTC);

        RTC->GPIOCTL0 = (RTC->GPIOCTL0 & ~(0x3FUL << (u32Offset * 8))) |
                        (u32Mode << (u32Offset * 8)) |
                        (u32OutputLevel << ((u32Offset * 8) + 2)) |
                        (u32DigitalCtl << ((u32Offset * 8) + 3)) |
                        (u32PullCtl << ((u32Offset * 8) + 4));
    }

    if((u32PFPin == 8) || (u32PFPin == 9) || (u32PFPin == 10) || (u32PFPin == 11))
    {
        u32Offset = u32PFPin - 8;

        RTC_SET_IOCTL_BY_RTC(RTC);

        RTC->GPIOCTL1 = (RTC->GPIOCTL1 & ~(0x3FUL << (u32Offset * 8))) |
                        (u32Mode << (u32Offset * 8)) |
                        (u32OutputLevel << ((u32Offset * 8) + 2)) |
                        (u32DigitalCtl << ((u32Offset * 8) + 3)) |
                        (u32PullCtl << ((u32Offset * 8) + 4));
    }
}

/**
 * @brief       Set RTC GPIO Output Level
 *
 * @param[in]   u32Pin          The single pin of GPIO-F port.
 *                              It could be 4~11, which means PF.4~PF.11.
 * @param[in]   u32OutputLevel  The I/O output level. 0: output low; 1: output high.
 *
 * @return      None
 *
 * @details     This function is used to set GPIO output level by RTC module.
 */
void RTC_SetGPIOLevel(uint32_t u32PFPin, uint32_t u32OutputLevel)
{
    uint32_t u32Offset;

    if((u32PFPin == 4) || (u32PFPin == 5) || (u32PFPin == 6) || (u32PFPin == 7))
    {
        u32Offset = u32PFPin - 4;

        RTC->GPIOCTL0 = (RTC->GPIOCTL0 & ~(0x4UL << (u32Offset * 8))) |
                        (u32OutputLevel << ((u32Offset * 8) + 2));
    }

    if((u32PFPin == 8) || (u32PFPin == 9) || (u32PFPin == 10) || (u32PFPin == 11))
    {
        u32Offset = u32PFPin - 8;

        RTC->GPIOCTL1 = (RTC->GPIOCTL1 & ~(0x4UL << (u32Offset * 8))) |
                        (u32OutputLevel << ((u32Offset * 8) + 2));
    }
}

/**@}*/ /* end of group RTC_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group RTC_Driver */

/**@}*/ /* end of group Standard_Driver */
