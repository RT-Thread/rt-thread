/**************************************************************************//**
 * @file     rtc.c
 * @version  V1.00
 * $Revision: 18 $
 * $Date: 15/11/26 10:43a $
 * @brief    NUC472/NUC442 RTC driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/


#include <stdio.h>
#include "NUC472_442.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Includes of local headers                                                                               */
/*---------------------------------------------------------------------------------------------------------*/



/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_RTC_Driver RTC Driver
  @{
*/
/// @cond HIDDEN_SYMBOLS

/*---------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_GLOBALS

/*---------------------------------------------------------------------------------------------------------*/
/* Global file scope (static) variables                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
static volatile uint32_t g_u32Reg, g_u32Reg1,g_u32hiYear,g_u32loYear,g_u32hiMonth,g_u32loMonth,g_u32hiDay,g_u32loDay;
static volatile uint32_t g_u32hiHour,g_u32loHour,g_u32hiMin,g_u32loMin,g_u32hiSec,g_u32loSec;

/// @endcond HIDDEN_SYMBOLS

/** @addtogroup NUC472_442_RTC_EXPORTED_FUNCTIONS RTC Exported Functions
  @{
*/


/**
 *  @brief    Set Frequency Compensation Data
 *
 *  @param[in]    i32FrequencyX100    Specify the RTC clock X100, ex: 3277365 means 32773.65.
 *
 *  @return   None
 *
 */
void RTC_32KCalibration(int32_t i32FrequencyX100)
{
    int32_t i32RegInt,i32RegFra ;

    /* Compute Integer and Fraction for RTC register*/
    i32RegInt = (i32FrequencyX100/100) - RTC_FCR_REFERENCE;
    i32RegFra = (((i32FrequencyX100%100)) * 60) / 100;

    /* Judge Integer part is reasonable */
    if ( (i32RegInt < 0) | (i32RegInt > 15) ) {
        return;
    }

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->FREQADJ = (uint32_t)((i32RegInt<<8) | i32RegFra);

}

/**
 *  @brief    This function is used to:
 *            1. Write initial key to let RTC start count.  \n
 *            2. Input parameter indicates start time.      \n
 *            Null pointer for using default starting time. \n
 *
 *  @param[in]    sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *  @return   None
 *
 */
void RTC_Open (S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Reg;

    volatile int32_t i32delay=1000;

    if(RTC->INIT != 0x1) {
        RTC->INIT = RTC_INIT_KEY;

        while(RTC->INIT != 0x1);
    }

    if(sPt == NULL)
        return;

    /*-----------------------------------------------------------------------------------------------------*/
    /* Second, set RTC 24/12 hour setting                                                                  */
    /*-----------------------------------------------------------------------------------------------------*/
    if (sPt->u32TimeScale == RTC_CLOCK_12) {
        RTC->RWEN = RTC_WRITE_KEY;
        while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

        /*-------------------------------------------------------------------------------------------------*/
        /* important, range of 12-hour PM mode is 21 up to 32                                               */
        /*-------------------------------------------------------------------------------------------------*/
        if (sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
    } else {                                                                           /* RTC_CLOCK_24 */
        RTC->RWEN = RTC_WRITE_KEY;
        while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC Calender Loading                                                                            */
    /*-----------------------------------------------------------------------------------------------------*/
    u32Reg     = ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg    |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg    |= ((sPt->u32Month  / 10) << 12);
    u32Reg    |= ((sPt->u32Month  % 10) << 8);
    u32Reg    |= ((sPt->u32Day    / 10) << 4);
    u32Reg    |= (sPt->u32Day     % 10);
    g_u32Reg = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->CAL = (uint32_t)g_u32Reg;

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC Time Loading                                                                                */
    /*-----------------------------------------------------------------------------------------------------*/
    u32Reg     = ((sPt->u32Hour / 10) << 20);
    u32Reg    |= ((sPt->u32Hour % 10) << 16);
    u32Reg    |= ((sPt->u32Minute / 10) << 12);
    u32Reg    |= ((sPt->u32Minute % 10) << 8);
    u32Reg    |= ((sPt->u32Second / 10) << 4);
    u32Reg    |= (sPt->u32Second % 10);
    g_u32Reg = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->TIME = (uint32_t)g_u32Reg;

    RTC->WEEKDAY = sPt->u32DayOfWeek;

    /* Waiting for RTC settings stable */
    while(i32delay--);

}

/**
 *  @brief    Read current date/time from RTC setting
 *
 *  @param[out]    sPt \n
 *                     Specify the time property and current time. It includes: \n
 *                     u32Year: Year value                                      \n
 *                     u32Month: Month value                                    \n
 *                     u32Day: Day value                                        \n
 *                     u32DayOfWeek: Day of week                                \n
 *                     u32Hour: Hour value                                      \n
 *                     u32Minute: Minute value                                  \n
 *                     u32Second: Second value                                  \n
 *                     u32TimeScale: \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24          \n
 *                     u8AmPm: \ref RTC_AM / \ref RTC_PM                            \n
 *
 *  @return   None
 *
 */
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Tmp;

    sPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;    /* 12/24-hour */
    sPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk;          /* Day of week */

    g_u32hiYear  = (RTC->CAL & RTC_CAL_TENYEAR_Msk) >> RTC_CAL_TENYEAR_Pos;
    g_u32loYear  = (RTC->CAL & RTC_CAL_YEAR_Msk)    >> RTC_CAL_YEAR_Pos;
    g_u32hiMonth = (RTC->CAL & RTC_CAL_TENMON_Msk)  >> RTC_CAL_TENMON_Pos;
    g_u32loMonth = (RTC->CAL & RTC_CAL_MON_Msk)     >> RTC_CAL_MON_Pos;
    g_u32hiDay   = (RTC->CAL & RTC_CAL_TENDAY_Msk)  >> RTC_CAL_TENDAY_Pos;
    g_u32loDay   = (RTC->CAL & RTC_CAL_DAY_Msk);

    g_u32hiHour =  (RTC->TIME & RTC_TIME_TENHR_Msk)  >> RTC_TIME_TENHR_Pos;
    g_u32loHour =  (RTC->TIME & RTC_TIME_HR_Msk)     >> RTC_TIME_HR_Pos;
    g_u32hiMin  =  (RTC->TIME & RTC_TIME_TENMIN_Msk) >> RTC_TIME_TENMIN_Pos;
    g_u32loMin  =  (RTC->TIME & RTC_TIME_MIN_Msk)    >> RTC_TIME_MIN_Pos;
    g_u32hiSec  =  (RTC->TIME & RTC_TIME_TENSEC_Msk) >> RTC_TIME_TENSEC_Pos;
    g_u32loSec  =  (RTC->TIME & RTC_TIME_SEC_Msk);

    u32Tmp  = (g_u32hiYear * 10);              /* Compute to 20XX year */
    u32Tmp += g_u32loYear;
    sPt->u32Year = u32Tmp + RTC_YEAR2000;

    u32Tmp = (g_u32hiMonth * 10);              /* Compute 0~12 month */
    sPt->u32Month = u32Tmp + g_u32loMonth;

    u32Tmp = (g_u32hiDay * 10);                /* Compute 0~31 day */
    sPt->u32Day   =  u32Tmp  + g_u32loDay;

    if (sPt->u32TimeScale == RTC_CLOCK_12) { /* Compute12/24 hour */
        u32Tmp = (g_u32hiHour * 10);
        u32Tmp+= g_u32loHour;
        sPt->u32Hour = u32Tmp;                 /* AM: 1~12. PM: 21~32. */

        if (sPt->u32Hour >= 21) {
            sPt->u32AmPm = RTC_PM;
            sPt->u32Hour -= 20;
        } else {
            sPt->u32AmPm = RTC_AM;
        }

        u32Tmp = (g_u32hiMin  * 10);
        u32Tmp+= g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp = (g_u32hiSec  * 10);
        u32Tmp+= g_u32loSec;
        sPt->u32Second = u32Tmp;

    } else {
        /* RTC_CLOCK_24 */
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
 *  @brief    Read alarm date/time from RTC setting
 *
 *  @param[out]    sPt \n
 *                     Specify the time property and current time. It includes: \n
 *                     u32Year: Year value                                      \n
 *                     u32Month: Month value                                    \n
 *                     u32Day: Day value                                        \n
 *                     u32DayOfWeek: Day of week                                \n
 *                     u32Hour: Hour value                                      \n
 *                     u32Minute: Minute value                                  \n
 *                     u32Second: Second value                                  \n
 *                     u32TimeScale: \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24          \n
 *                     u8AmPm: \ref RTC_AM / \ref RTC_PM                            \n
 *
 *  @return   None
 *
 */
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Tmp;

    sPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;  /* 12/24-hour */
    sPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk;        /* Day of week */

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    g_u32hiYear  = (RTC->CALM & RTC_CALM_TENYEAR_Msk) >> RTC_CALM_TENYEAR_Pos;
    g_u32loYear  = (RTC->CALM & RTC_CALM_YEAR_Msk)    >> RTC_CALM_YEAR_Pos;
    g_u32hiMonth = (RTC->CALM & RTC_CALM_TENMON_Msk)  >> RTC_CALM_TENMON_Pos;
    g_u32loMonth = (RTC->CALM & RTC_CALM_MON_Msk)     >> RTC_CALM_MON_Pos;
    g_u32hiDay   = (RTC->CALM & RTC_CALM_TENDAY_Msk)  >> RTC_CALM_TENDAY_Pos;
    g_u32loDay   = (RTC->CALM & RTC_CALM_DAY_Msk);

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    g_u32hiHour   =  (RTC->TALM & RTC_TALM_TENHR_Msk)  >> RTC_TALM_TENHR_Pos;
    g_u32loHour   =  (RTC->TALM & RTC_TALM_HR_Msk)     >> RTC_TALM_HR_Pos;
    g_u32hiMin    =  (RTC->TALM & RTC_TALM_TENMIN_Msk) >> RTC_TALM_TENMIN_Pos;
    g_u32loMin    =  (RTC->TALM & RTC_TALM_MIN_Msk)    >> RTC_TALM_MIN_Pos;
    g_u32hiSec    =  (RTC->TALM & RTC_TALM_TENSEC_Msk) >> RTC_TALM_TENSEC_Pos;
    g_u32loSec    =  (RTC->TALM & RTC_TALM_SEC_Msk);

    u32Tmp  = (g_u32hiYear * 10);                                    /* Compute to 20XX year */
    u32Tmp += g_u32loYear;
    sPt->u32Year = u32Tmp + RTC_YEAR2000;

    u32Tmp = (g_u32hiMonth * 10);                                    /* Compute 0~12 month */
    sPt->u32Month = u32Tmp + g_u32loMonth;

    u32Tmp = (g_u32hiDay * 10);                                        /* Compute 0~31 day */
    sPt->u32Day = u32Tmp + g_u32loDay;

    if (sPt->u32TimeScale == RTC_CLOCK_12) {                /* Compute12/24 hour */
        u32Tmp  = (g_u32hiHour * 10);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;                                        /* AM: 1~12. PM: 21~32. */

        if (sPt->u32Hour >= 21) {
            sPt->u32AmPm  = RTC_PM;
            sPt->u32Hour -= 20;
        } else {
            sPt->u32AmPm = RTC_AM;
        }

        u32Tmp  = (g_u32hiMin * 10);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;

    } else {
        /* RTC_CLOCK_24 */
        u32Tmp  = (g_u32hiHour * 10);
        u32Tmp +=  g_u32loHour;
        sPt->u32Hour = u32Tmp;

        u32Tmp = (g_u32hiMin * 10);
        u32Tmp+= g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }

}



/**
 *  @brief    This function is used to update date/time to RTC.
 *
 *  @param[in]    sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *
 *  @return   None
 *
 *
 */
void RTC_SetDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    if (sPt->u32TimeScale == RTC_CLOCK_12) {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

        /*-----------------------------------------------------------------------------------------*/
        /* important, range of 12-hour PM mode is 21 up to 32                                       */
        /*-----------------------------------------------------------------------------------------*/
        if (sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
    } else {                                                              /* RTC_CLOCK_24 */
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    RTC->WEEKDAY = sPt->u32DayOfWeek & RTC_WEEKDAY_WEEKDAY_Msk;

    u32Reg     = ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg    |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg    |= ((sPt->u32Month  / 10) << 12);
    u32Reg    |= ((sPt->u32Month  % 10) << 8);
    u32Reg    |= ((sPt->u32Day    / 10) << 4);
    u32Reg    |=  (sPt->u32Day    % 10);
    g_u32Reg = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->CAL = (uint32_t)g_u32Reg;

    u32Reg     = ((sPt->u32Hour   / 10) << 20);
    u32Reg    |= ((sPt->u32Hour   % 10) << 16);
    u32Reg    |= ((sPt->u32Minute / 10) << 12);
    u32Reg    |= ((sPt->u32Minute % 10) << 8);
    u32Reg    |= ((sPt->u32Second / 10) << 4);
    u32Reg    |=  (sPt->u32Second % 10);
    g_u32Reg = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->TIME = (uint32_t)g_u32Reg;

}

/**
 *  @brief    This function is used to set alarm date/time to RTC.
 *
 *  @param[in]    sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *  @return   None
 *
 */
void RTC_SetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    if (sPt->u32TimeScale == RTC_CLOCK_12) {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

        /*-----------------------------------------------------------------------------------------*/
        /* important, range of 12-hour PM mode is 21 up to 32                                       */
        /*-----------------------------------------------------------------------------------------*/
        if (sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
    } else {                                                              /* RTC_CLOCK_24 */
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    RTC->WEEKDAY = sPt->u32DayOfWeek & RTC_WEEKDAY_WEEKDAY_Msk;


    u32Reg     = ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg    |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg    |= ((sPt->u32Month  / 10) << 12);
    u32Reg    |= ((sPt->u32Month  % 10) << 8);
    u32Reg    |= ((sPt->u32Day     / 10) << 4);
    u32Reg    |=  (sPt->u32Day    % 10);
    g_u32Reg   = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->CALM = (uint32_t)g_u32Reg;

    u32Reg     = ((sPt->u32Hour   / 10) << 20);
    u32Reg    |= ((sPt->u32Hour   % 10) << 16);
    u32Reg    |= ((sPt->u32Minute / 10) << 12);
    u32Reg    |= ((sPt->u32Minute % 10) << 8);
    u32Reg    |= ((sPt->u32Second / 10) << 4);
    u32Reg    |=  (sPt->u32Second % 10);
    g_u32Reg = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->TALM = (uint32_t)g_u32Reg;

}


/**
 *  @brief    This function is used to update date to RTC
 *
 *  @param[in]    u32Year       The Year Calendar Digit of Alarm Setting
 *  @param[in]    u32Month      The Month Calendar Digit of Alarm Setting
 *  @param[in]    u32Day        The Day Calendar Digit of Alarm Setting
 *  @param[in]    u32DayOfWeek  The Day of Week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                 \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                 \ref RTC_SATURDAY]
 *
 *  @return   None
 *
 */
void RTC_SetDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day, uint32_t u32DayOfWeek)
{
    __IO uint32_t u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->WEEKDAY = u32DayOfWeek & RTC_WEEKDAY_WEEKDAY_Msk;

    u32Reg     = ((u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg    |= (((u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg    |= ((u32Month  / 10) << 12);
    u32Reg    |= ((u32Month  % 10) << 8);
    u32Reg    |= ((u32Day    / 10) << 4);
    u32Reg    |=  (u32Day    % 10);
    g_u32Reg   = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->CAL = (uint32_t)g_u32Reg;

}

/**
 *  @brief    This function is used to update time to RTC.
 *
 *  @param[in]    u32Hour     The Hour Time Digit of Alarm Setting.
 *  @param[in]    u32Minute   The Month Calendar Digit of Alarm Setting
 *  @param[in]    u32Second   The Day Calendar Digit of Alarm Setting
 *  @param[in]    u32TimeMode The 24-Hour / 12-Hour Time Scale Selection. [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]
 *  @param[in]    u32AmPm     12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [ \ref RTC_AM / \ref RTC_PM]
 *
 *  @return   None
 *
 */
void RTC_SetTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm)
{
    __IO uint32_t u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    if (u32TimeMode == RTC_CLOCK_12) {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

        if (u32AmPm == RTC_PM)    /* important, range of 12-hour PM mode is 21 up to 32 */
            u32Hour += 20;
    } else if(u32TimeMode == RTC_CLOCK_24) {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    u32Reg     = ((u32Hour   / 10) << 20);
    u32Reg    |= ((u32Hour   % 10) << 16);
    u32Reg    |= ((u32Minute / 10) << 12);
    u32Reg    |= ((u32Minute % 10) << 8);
    u32Reg    |= ((u32Second / 10) << 4);
    u32Reg    |=  (u32Second % 10);

    g_u32Reg = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->TIME = (uint32_t)g_u32Reg;

}

/**
 *  @brief    This function is used to set alarm date to RTC
 *
 *  @param[in]    u32Year    The Year Calendar Digit of Alarm Setting
 *  @param[in]    u32Month   The Month Calendar Digit of Alarm Setting
 *  @param[in]    u32Day     The Day Calendar Digit of Alarm Setting
 *
 *  @return   None
 *
 */
void RTC_SetAlarmDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day)
{
    __IO uint32_t u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    u32Reg       = ((u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg      |= (((u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg      |= ((u32Month  / 10) << 12);
    u32Reg      |= ((u32Month  % 10) << 8);
    u32Reg      |= ((u32Day    / 10) << 4);
    u32Reg      |=  (u32Day    % 10);
    g_u32Reg   = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->CALM = (uint32_t)g_u32Reg;

}

/**
 *  @brief    This function is used to set alarm date to RTC
 *
 *  @param[in]     u32Hour     The Hour Time Digit of Alarm Setting.
 *  @param[in]     u32Minute   The Minute Time Digit of Alarm Setting
 *  @param[in]     u32Second   The Second Time Digit of Alarm Setting
 *  @param[in]     u32TimeMode The 24-Hour / 12-Hour Time Scale Selection. [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]
 *  @param[in]     u32AmPm     12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [ \ref RTC_AM / \ref RTC_PM]
 *
 *  @return   None
 *
 */
void RTC_SetAlarmTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm)
{
    __IO uint32_t u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    if (u32TimeMode == RTC_CLOCK_12) {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;

        if (u32AmPm == RTC_PM)    /* important, range of 12-hour PM mode is 21 up to 32 */
            u32Hour += 20;
    } else if(u32TimeMode == RTC_CLOCK_24) {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
    }

    u32Reg     = ((u32Hour   / 10) << 20);
    u32Reg    |= ((u32Hour   % 10) << 16);
    u32Reg    |= ((u32Minute / 10) << 12);
    u32Reg    |= ((u32Minute % 10) <<  8);
    u32Reg    |= ((u32Second / 10) <<  4);
    u32Reg    |=  (u32Second % 10);

    g_u32Reg = u32Reg;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->TALM = (uint32_t)g_u32Reg;

}


/**
 *  @brief    The spare registers access enable
 *
 *  @return   None
 *
 */
void RTC_EnableSpareAccess(void)
{
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->SPRCTL |= RTC_SPRCTL_SPRRWEN_Msk;

    while(!(RTC->SPRCTL & RTC_SPRCTL_SPRRWRDY_Msk));
}


/**
 *  @brief    This function is used to:
 *            1. Enable tamper detection function.            \n
 *            2. Set tamper detect pin number.                \n
 *            3. Set tamper control register, interrupt.      \n
 *            4. Clear tamper status.                         \n
 *            5. Destroy Spare Register when tamper detected  \n
 *
 *  @param[in]    u32PinNumber    tamper detect pin number. [ \ref RTC_TAMPER_0 / \ref RTC_TAMPER_1]
 *  @param[in]    u32PinCondition set tamper detection condition: 1=High level detect, 0=Low level detect
 *  @param[in]    u32IntFlag Enable/Disable tamper interrupt: 1=Enable, 0=Disable
 *  @param[in]    u32ClearFlag Clear tamper status
 *  @param[in]    u32DestroyEn Enable/Disable Destroy Spare Register when tamper detected: 1=Enable, 0=Disable
 *
 *  @return   None
 *
 */
void RTC_EnableTamperDetection(uint32_t u32PinNumber, uint32_t u32PinCondition, uint32_t u32IntFlag, uint32_t u32ClearFlag, uint32_t u32DestroyEn)
{
    uint32_t u32Tmp;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    u32Tmp = RTC->TAMPCTL;

    if(u32PinNumber == RTC_TAMPER_0) {
        //if(u32ClearFlag)
        //    RTC->TAMPSTS = RTC_TAMPSTS_TAMPSTS0_Msk;

        if(u32PinCondition)
            u32Tmp |= RTC_TAMPCTL_TAMPLV0_Msk;
        else
            u32Tmp &= ~RTC_TAMPCTL_TAMPLV0_Msk;

        u32Tmp |= RTC_TAMPCTL_TAMPDBEN0_Msk;
        u32Tmp |= RTC_TAMPCTL_TAMPEN0_Msk;
    } else if(u32PinNumber == RTC_TAMPER_1) {
        //if(u32ClearFlag)
        //    RTC->TAMPSTS = RTC_TAMPSTS_TAMPSTS1_Msk;

        if(u32PinCondition)
            u32Tmp |= RTC_TAMPCTL_TAMPLV1_Msk;
        else
            u32Tmp &= ~RTC_TAMPCTL_TAMPLV1_Msk;

        u32Tmp |= RTC_TAMPCTL_TAMPDBEN1_Msk;
        u32Tmp |= RTC_TAMPCTL_TAMPEN1_Msk;
    }

    if(u32IntFlag)
        u32Tmp |= RTC_TAMPCTL_TIEN_Msk;
    else
        u32Tmp &= ~RTC_TAMPCTL_TIEN_Msk;

    if(u32DestroyEn)
        u32Tmp |= RTC_TAMPCTL_DESTROYEN_Msk;
    else
        u32Tmp &= ~RTC_TAMPCTL_DESTROYEN_Msk;

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->TAMPCTL = u32Tmp;

    while(RTC->RWEN & RTC_RWEN_RWENF_Msk);

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    if(u32PinNumber == RTC_TAMPER_0) {
        if(u32ClearFlag)
            RTC->TAMPSTS = RTC_TAMPSTS_TAMPSTS0_Msk;
    } else if(u32PinNumber == RTC_TAMPER_1) {
        if(u32ClearFlag)
            RTC->TAMPSTS = RTC_TAMPSTS_TAMPSTS1_Msk;
    }
}

/**
 *  @brief    This function is used to disable tamper detection function.
 *
 *  @param[in]    u32PinNumber    tamper detect pin number: \ref RTC_TAMPER_0, \ref RTC_TAMPER_1
 *
 *  @return   None
 *
 */
void RTC_DisableTamperDetection(uint32_t u32PinNumber)
{
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    if(u32PinNumber == RTC_TAMPER_0) {
        RTC->TAMPCTL &= ~RTC_TAMPCTL_TAMPEN0_Msk;
    } else if(u32PinNumber == RTC_TAMPER_1) {
        RTC->TAMPCTL &= ~RTC_TAMPCTL_TAMPEN1_Msk;
    }

}

/**
 *  @brief    This function is used to get day of week.
 *
 *  @param    None
 *
 *  @return   Day of week
 *
 */
uint32_t RTC_GetDayOfWeek(void)
{
    return (RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk);
}

/**
 *  @brief    The function is used to set time tick period for periodic time tick Interrupt.
 *
 *  @param[in]    u32TickSelection
 *                       It is used to set the RTC time tick period for Periodic Time Tick Interrupt request.
 *                       It consists of: \n
 *                       - \ref RTC_TICK_1_SEC : Time tick is 1 second        \n
 *                       - \ref RTC_TICK_1_2_SEC : Time tick is 1/2 second    \n
 *                       - \ref RTC_TICK_1_4_SEC : Time tick is 1/4 second    \n
 *                       - \ref RTC_TICK_1_8_SEC : Time tick is 1/8 second    \n
 *                       - \ref RTC_TICK_1_16_SEC : Time tick is 1/16 second  \n
 *                       - \ref RTC_TICK_1_32_SEC : Time tick is 1/32 second  \n
 *                       - \ref RTC_TICK_1_64_SEC : Time tick is 1/64 second  \n
 *                       - \ref RTC_TICK_1_128_SEC : Time tick is 1/128 second
 *
 *  @return   None
 *
 */
void RTC_SetTickPeriod(uint32_t u32TickSelection)
{
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->TICK = RTC->TICK & ~RTC_TICK_TICKSEL_Msk | u32TickSelection;
}

/**
 *  @brief    The function is used to enable specified interrupt.
 *
 *  @param[in]    u32IntFlagMask      The structure of interrupt source. It consists of: \n
 *                                \ref RTC_INTEN_ALMIEN_Msk : Alarm interrupt                  \n
 *                                \ref RTC_INTEN_TICKIEN_Msk : Tick interrupt                    \n
 *
 *  @return   None
 *
 */
void RTC_EnableInt(uint32_t u32IntFlagMask)
{
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    RTC->INTEN |= u32IntFlagMask;
}

/**
 *  @brief    The function is used to disable specified interrupt.
 *
 *  @param[in]    u32IntFlagMask      The structure of interrupt source. It consists of: \n
 *                                \ref RTC_INTEN_ALMIEN_Msk : Alarm interrupt                  \n
 *                                \ref RTC_INTEN_TICKIEN_Msk : Tick interrupt                    \n
 *
 *  @return  None
 *
 */
void RTC_DisableInt(uint32_t u32IntFlagMask)
{
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));

    if(u32IntFlagMask & RTC_INTEN_TICKIEN_Msk) {
        RTC->INTEN  &= ~RTC_INTEN_TICKIEN_Msk;
        RTC->INTSTS |= RTC_INTSTS_TICKIF_Msk;
    }

    if(u32IntFlagMask & RTC_INTEN_ALMIEN_Msk) {
        RTC->INTEN &= ~RTC_INTEN_ALMIEN_Msk;
        RTC->INTSTS |= RTC_INTSTS_ALMIF_Msk;
    }

}

/**
 *  @brief    Disable RTC clock.
 *
 *  @return   None
 *
 */
void RTC_Close (void)
{
    CLK->APBCLK0  &= ~CLK_APBCLK0_RTCCKEN_Msk;
}


/*@}*/ /* end of group NUC472_442_RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_RTC_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


