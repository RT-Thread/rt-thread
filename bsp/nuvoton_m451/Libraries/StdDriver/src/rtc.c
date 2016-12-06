/**************************************************************************//**
 * @file     rtc.c
 * @version  V3.00
 * $Revision: 7 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series RTC driver source file
 *
 * @note
 * Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M451Series.h"


/// @cond HIDDEN_SYMBOLS

/*---------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_GLOBALS

/*---------------------------------------------------------------------------------------------------------*/
/* Global file scope (static) variables                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
static volatile uint32_t g_u32hiYear, g_u32loYear, g_u32hiMonth, g_u32loMonth, g_u32hiDay, g_u32loDay;
static volatile uint32_t g_u32hiHour, g_u32loHour, g_u32hiMin, g_u32loMin, g_u32hiSec, g_u32loSec;

/// @endcond HIDDEN_SYMBOLS




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
  * @note       Null pointer for using default starting date/time.
  */
void RTC_Open(S_RTC_TIME_DATA_T *sPt)
{
    RTC->INIT = RTC_INIT_KEY;

    if(RTC->INIT != RTC_INIT_ACTIVE_Msk)
    {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk);
    }

    if(sPt == 0)
        return ;

    /* Set RTC date and time */
    RTC_SetDateAndTime(sPt);

    /* Waiting for RTC settings stable */
    while((RTC->RWEN & RTC_RWEN_RWENF_Msk) == RTC_RWEN_RWENF_Msk);
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
  * @brief      Set 32k Frequency Compensation Data
  *
  * @param[in]  i32FrequencyX100    Specify the RTC clock X100, ex: 3277365 means 32773.65.
  *
  * @return     None
  *
  * @details    This API is used to compensate the 32 kHz frequency by current LXT frequency for RTC application.
  */
void RTC_32KCalibration(int32_t i32FrequencyX100)
{
    int32_t i32RegInt, i32RegFra;

    /* Compute integer and fraction for RTC FCR register */
    i32RegInt = (i32FrequencyX100 / 100) - RTC_FCR_REFERENCE;
    i32RegFra = (((i32FrequencyX100 % 100)) * 60) / 100;

    /* Judge Integer part is reasonable */
    if((i32RegInt < 0) | (i32RegInt > 15))
    {
        return ;
    }

    RTC_WaitAccessEnable();
    RTC->FREQADJ = (uint32_t)((i32RegInt << 8) | i32RegFra);
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
    u32Tmp  = (g_u32hiYear * 10);
    u32Tmp += g_u32loYear;
    sPt->u32Year = u32Tmp + RTC_YEAR2000;

    /* Compute 0~12 month */
    u32Tmp = (g_u32hiMonth * 10);
    sPt->u32Month = u32Tmp + g_u32loMonth;

    /* Compute 0~31 day */
    u32Tmp = (g_u32hiDay * 10);
    sPt->u32Day =  u32Tmp  + g_u32loDay;

    /* Compute 12/24 hour */
    if(sPt->u32TimeScale == RTC_CLOCK_12)
    {
        u32Tmp = (g_u32hiHour * 10);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;          /* AM: 1~12. PM: 21~32. */

        if(sPt->u32Hour >= 21)
        {
            sPt->u32AmPm  = RTC_PM;
            sPt->u32Hour -= 20;
        }
        else
        {
            sPt->u32AmPm = RTC_AM;
        }

        u32Tmp  = (g_u32hiMin  * 10);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec  * 10);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }
    else
    {
        u32Tmp  = (g_u32hiHour * 10);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;

        u32Tmp  = (g_u32hiMin * 10);
        u32Tmp +=  g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10);
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
    RTC_WaitAccessEnable();
    g_u32hiYear  = (RTC->CALM & RTC_CALM_TENYEAR_Msk) >> RTC_CALM_TENYEAR_Pos;
    g_u32loYear  = (RTC->CALM & RTC_CALM_YEAR_Msk) >> RTC_CALM_YEAR_Pos;
    g_u32hiMonth = (RTC->CALM & RTC_CALM_TENMON_Msk) >> RTC_CALM_TENMON_Pos;
    g_u32loMonth = (RTC->CALM & RTC_CALM_MON_Msk) >> RTC_CALM_MON_Pos;
    g_u32hiDay   = (RTC->CALM & RTC_CALM_TENDAY_Msk) >> RTC_CALM_TENDAY_Pos;
    g_u32loDay   = (RTC->CALM & RTC_CALM_DAY_Msk) >> RTC_CALM_DAY_Pos;

    /* Get alarm [Time digit] data */
    RTC_WaitAccessEnable();
    g_u32hiHour = (RTC->TALM & RTC_TALM_TENHR_Msk) >> RTC_TALM_TENHR_Pos;
    g_u32loHour = (RTC->TALM & RTC_TALM_HR_Msk) >> RTC_TALM_HR_Pos;
    g_u32hiMin  = (RTC->TALM & RTC_TALM_TENMIN_Msk) >> RTC_TALM_TENMIN_Pos;
    g_u32loMin  = (RTC->TALM & RTC_TALM_MIN_Msk) >> RTC_TALM_MIN_Pos;
    g_u32hiSec  = (RTC->TALM & RTC_TALM_TENSEC_Msk) >> RTC_TALM_TENSEC_Pos;
    g_u32loSec  = (RTC->TALM & RTC_TALM_SEC_Msk) >> RTC_TALM_SEC_Pos;

    /* Compute to 20XX year */
    u32Tmp  = (g_u32hiYear * 10);
    u32Tmp += g_u32loYear;
    sPt->u32Year = u32Tmp + RTC_YEAR2000;

    /* Compute 0~12 month */
    u32Tmp = (g_u32hiMonth * 10);
    sPt->u32Month = u32Tmp + g_u32loMonth;

    /* Compute 0~31 day */
    u32Tmp = (g_u32hiDay * 10);
    sPt->u32Day = u32Tmp + g_u32loDay;

    /* Compute 12/24 hour */
    if(sPt->u32TimeScale == RTC_CLOCK_12)
    {
        u32Tmp  = (g_u32hiHour * 10);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;          /* AM: 1~12. PM: 21~32. */

        if(sPt->u32Hour >= 21)
        {
            sPt->u32AmPm  = RTC_PM;
            sPt->u32Hour -= 20;
        }
        else
        {
            sPt->u32AmPm = RTC_AM;
        }

        u32Tmp  = (g_u32hiMin * 10);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;

    }
    else
    {
        u32Tmp  = (g_u32hiHour * 10);
        u32Tmp +=  g_u32loHour;
        sPt->u32Hour = u32Tmp;

        u32Tmp  = (g_u32hiMin * 10);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10);
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

    if(sPt == 0)
        return ;

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC 24/12 hour setting and Day of the Week                                                      */
    /*-----------------------------------------------------------------------------------------------------*/
    RTC_WaitAccessEnable();
    if(sPt->u32TimeScale == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

        /*-------------------------------------------------------------------------------------------------*/
        /* Important, range of 12-hour PM mode is 21 up to 32                                               */
        /*-------------------------------------------------------------------------------------------------*/
        if(sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
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
    u32RegCAL  = ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
    u32RegCAL |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    u32RegCAL |= ((sPt->u32Month  / 10) << 12);
    u32RegCAL |= ((sPt->u32Month  % 10) << 8);
    u32RegCAL |= ((sPt->u32Day    / 10) << 4);
    u32RegCAL |= (sPt->u32Day     % 10);

    u32RegTIME  = ((sPt->u32Hour   / 10) << 20);
    u32RegTIME |= ((sPt->u32Hour   % 10) << 16);
    u32RegTIME |= ((sPt->u32Minute / 10) << 12);
    u32RegTIME |= ((sPt->u32Minute % 10) << 8);
    u32RegTIME |= ((sPt->u32Second / 10) << 4);
    u32RegTIME |= (sPt->u32Second % 10);

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC Calender and Time Loading                                                                   */
    /*-----------------------------------------------------------------------------------------------------*/
    RTC_WaitAccessEnable();
    RTC->CAL  = (uint32_t)u32RegCAL;
    RTC->TIME = (uint32_t)u32RegTIME;
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

    if(sPt == 0)
        return ;

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC 24/12 hour setting and Day of the Week                                                      */
    /*-----------------------------------------------------------------------------------------------------*/
    RTC_WaitAccessEnable();
    if(sPt->u32TimeScale == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

        /*-------------------------------------------------------------------------------------------------*/
        /* Important, range of 12-hour PM mode is 21 up to 32                                               */
        /*-------------------------------------------------------------------------------------------------*/
        if(sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
    }
    else
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    /* Set Day of the Week */
    RTC->WEEKDAY = sPt->u32DayOfWeek;

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC Alarm Date and Time                                                                         */
    /*-----------------------------------------------------------------------------------------------------*/
    u32RegCALM  = ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
    u32RegCALM |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    u32RegCALM |= ((sPt->u32Month  / 10) << 12);
    u32RegCALM |= ((sPt->u32Month  % 10) << 8);
    u32RegCALM |= ((sPt->u32Day    / 10) << 4);
    u32RegCALM |= (sPt->u32Day    % 10);

    u32RegTALM  = ((sPt->u32Hour   / 10) << 20);
    u32RegTALM |= ((sPt->u32Hour   % 10) << 16);
    u32RegTALM |= ((sPt->u32Minute / 10) << 12);
    u32RegTALM |= ((sPt->u32Minute % 10) << 8);
    u32RegTALM |= ((sPt->u32Second / 10) << 4);
    u32RegTALM |= (sPt->u32Second % 10);

    RTC_WaitAccessEnable();
    RTC->CALM = (uint32_t)u32RegCALM;
    RTC->TALM = (uint32_t)u32RegTALM;
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

    u32RegCAL  = ((u32Year - RTC_YEAR2000) / 10) << 20;
    u32RegCAL |= (((u32Year - RTC_YEAR2000) % 10) << 16);
    u32RegCAL |= ((u32Month / 10) << 12);
    u32RegCAL |= ((u32Month % 10) << 8);
    u32RegCAL |= ((u32Day   / 10) << 4);
    u32RegCAL |= (u32Day   % 10);

    RTC_WaitAccessEnable();

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
    if((u32TimeMode == RTC_CLOCK_12) && (u32AmPm == RTC_PM))
        u32Hour += 20;

    u32RegTIME  = ((u32Hour   / 10) << 20);
    u32RegTIME |= ((u32Hour   % 10) << 16);
    u32RegTIME |= ((u32Minute / 10) << 12);
    u32RegTIME |= ((u32Minute % 10) << 8);
    u32RegTIME |= ((u32Second / 10) << 4);
    u32RegTIME |= (u32Second % 10);

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC 24/12 hour setting and Day of the Week                                                      */
    /*-----------------------------------------------------------------------------------------------------*/
    RTC_WaitAccessEnable();
    if(u32TimeMode == RTC_CLOCK_12)
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

    u32RegCALM  = ((u32Year - RTC_YEAR2000) / 10) << 20;
    u32RegCALM |= (((u32Year - RTC_YEAR2000) % 10) << 16);
    u32RegCALM |= ((u32Month / 10) << 12);
    u32RegCALM |= ((u32Month % 10) << 8);
    u32RegCALM |= ((u32Day   / 10) << 4);
    u32RegCALM |= (u32Day   % 10);

    RTC_WaitAccessEnable();

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
    if((u32TimeMode == RTC_CLOCK_12) && (u32AmPm == RTC_PM))
        u32Hour += 20;

    u32RegTALM  = ((u32Hour   / 10) << 20);
    u32RegTALM |= ((u32Hour   % 10) << 16);
    u32RegTALM |= ((u32Minute / 10) << 12);
    u32RegTALM |= ((u32Minute % 10) << 8);
    u32RegTALM |= ((u32Second / 10) << 4);
    u32RegTALM |= (u32Second % 10);

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC 24/12 hour setting and Day of the Week                                                      */
    /*-----------------------------------------------------------------------------------------------------*/
    RTC_WaitAccessEnable();
    if(u32TimeMode == RTC_CLOCK_12)
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
  *                                 It consists of:                                     \n
  *                                     RTC_TICK_1_SEC: Time tick is 1 second           \n
  *                                     RTC_TICK_1_2_SEC: Time tick is 1/2 second       \n
  *                                     RTC_TICK_1_4_SEC: Time tick is 1/4 second       \n
  *                                     RTC_TICK_1_8_SEC: Time tick is 1/8 second       \n
  *                                     RTC_TICK_1_16_SEC: Time tick is 1/16 second     \n
  *                                     RTC_TICK_1_32_SEC: Time tick is 1/32 second     \n
  *                                     RTC_TICK_1_64_SEC: Time tick is 1/64 second     \n
  *                                     RTC_TICK_1_128_SEC: Time tick is 1/128 second
  *
  * @return     None
  *
  * @details    This API is used to set RTC tick period time for each tick interrupt.
  */
void RTC_SetTickPeriod(uint32_t u32TickSelection)
{
    RTC_WaitAccessEnable();

    RTC->TICK = (RTC->TICK & ~RTC_TICK_TICK_Msk) | u32TickSelection;
}

/**
  * @brief      Enable RTC Interrupt
  *
  * @param[in]  u32IntFlagMask      Specify the interrupt source. It consists of:                    \n
  *                                     RTC_INTEN_ALMIEN_Msk: Alarm interrupt                        \n
  *                                     RTC_INTEN_TICKIEN_Msk: Tick interrupt                        \n
  *                                     RTC_INTEN_SNPDIEN_Msk: Snooper Pin Event Detection interrupt \n
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
  * @param[in]  u32IntFlagMask      Specify the interrupt source. It consists of:                    \n
  *                                     RTC_INTEN_ALMIEN_Msk: Alarm interrupt                        \n
  *                                     RTC_INTEN_TICKIEN_Msk: Tick interrupt                        \n
  *                                     RTC_INTEN_SNPDIEN_Msk: Snooper Pin Event Detection interrupt \n
  *
  * @return     None
  *
  * @details    This API is used to disable the specify RTC interrupt function.
  */
void RTC_DisableInt(uint32_t u32IntFlagMask)
{
    if(u32IntFlagMask & RTC_INTEN_ALMIEN_Msk)
    {
        RTC->INTEN  &= ~RTC_INTEN_ALMIEN_Msk;
        RTC->INTSTS = RTC_INTSTS_ALMIF_Msk;
    }

    if(u32IntFlagMask & RTC_INTEN_TICKIEN_Msk)
    {
        RTC->INTEN  &= ~RTC_INTEN_TICKIEN_Msk;
        RTC->INTSTS = RTC_INTSTS_TICKIF_Msk;
    }

    if(u32IntFlagMask & RTC_INTEN_SNPDIEN_Msk)
    {
        RTC->INTEN  &= ~RTC_INTEN_SNPDIEN_Msk;
        RTC->INTSTS = RTC_INTSTS_SNPDIF_Msk;
    }
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
    RTC_WaitAccessEnable();

    RTC->SPRCTL |= RTC_SPRCTL_SPRRWEN_Msk;

    while(!(RTC->SPRCTL & RTC_SPRCTL_SPRRWRDY_Msk));
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
    RTC_WaitAccessEnable();

    RTC->SPRCTL &= ~RTC_SPRCTL_SPRRWEN_Msk;
}

/**
  * @brief      Enable Snooper Pin Detect
  *
  * @param[in]  u32PinCondition     Snooper pin trigger condition. Possible options are
  *                                 - \ref RTC_SNOOPER_LOW_LEVEL
  *                                 - \ref RTC_SNOOPER_HIGH_LEVEL
  *                                 - \ref RTC_SNOOPER_FALLING_EDGE
  *                                 - \ref RTC_SNOOPER_RISING_EDGE
  *
  * @return     None
  *
  * @details    This API is used to enable the snooper pin detect function with specify trigger condition.
  */
void RTC_EnableSnooperDetection(uint32_t u32PinCondition)
{
    RTC_WaitAccessEnable();

    RTC->SPRCTL = ((RTC->SPRCTL & ~RTC_SNOOPER_DETECT_Msk) | u32PinCondition) | RTC_SPRCTL_SNPDEN_Msk;
}

/**
  * @brief      Disable Snooper Pin Detect
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This API is used to disable the snooper pin detect function.
  */
void RTC_DisableSnooperDetection(void)
{
    RTC_WaitAccessEnable();

    RTC->SPRCTL &= ~RTC_SPRCTL_SNPDEN_Msk;
}

/*@}*/ /* end of group RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group RTC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2013~2015 Nuvoton Technology Corp. ***/
