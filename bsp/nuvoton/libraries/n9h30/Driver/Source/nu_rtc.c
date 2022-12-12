/**************************************************************************//**
* @file     RTC.c
* @brief    N9H30 RTC driver source file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "N9H30.h"
#include "nu_sys.h"
#include "nu_rtc.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_RTC_Driver RTC Driver
  @{
*/

/** @addtogroup N9H30_RTC_EXPORTED_FUNCTIONS RTC Exported Functions
  @{
*/

/// @cond HIDDEN_SYMBOLS

static CHAR g_chHourMode = 0;
static BOOL volatile g_bIsEnableTickInt  = FALSE;
static BOOL volatile g_bIsEnableAlarmInt = FALSE;

static UINT32 volatile g_u32Reg, g_u32Reg1, g_u32hiYear, g_u32loYear, g_u32hiMonth, g_u32loMonth, g_u32hiDay, g_u32loDay;
static UINT32 volatile g_u32hiHour, g_u32loHour, g_u32hiMin, g_u32loMin, g_u32hiSec, g_u32loSec;
UINT32 volatile i, Wait;

VOID RTC_Check(void)
{
    i = 0;

    Wait = inp32(REG_RTC_INTSTS) & RTC_INTSTS_REGWRBUSY_Msk;

    while (Wait == RTC_INTSTS_REGWRBUSY_Msk)
    {

        Wait = inp32(REG_RTC_INTSTS) & RTC_INTSTS_REGWRBUSY_Msk;

        i++;

        if (i > RTC_WAIT_COUNT)
        {
            break;
        }
    }
}

/// @endcond HIDDEN_SYMBOLS

/**
  * @brief      Set 32k Frequency Compensation Data
  *
  * @param[in]  i32FrequencyX100    Specify the RTC clock X100, ex: 3277365 means 32773.65.
  *
  * @return     E_RTC_ERR_FCR_VALUE   Wrong Compensation VALUE
  *             E_RTC_SUCCESS         Success
  *
  * @details    This API is used to compensate the 32 kHz frequency by current LXT frequency for RTC application.
  */
UINT32 RTC_DoFrequencyCompensation(INT32 i32FrequencyX100)
{
    INT32 i32RegInt, i32RegFra;
    UINT32 u32Reg;

    /* Compute integer and fraction for RTC FCR register */
    i32RegInt = (i32FrequencyX100 / 100) - RTC_FCR_REFERENCE;
    i32RegFra = (((i32FrequencyX100 % 100)) * 60) / 100;

    /* Judge Integer part is reasonable */
    if ((i32RegInt < 0) | (i32RegInt > 15))
    {
        return E_RTC_ERR_FCR_VALUE;
    }

    u32Reg = (uint32_t)((i32RegInt << 8) | i32RegFra);

    RTC_WriteEnable(1);
    outp32(REG_RTC_FREQADJ, u32Reg);
    RTC_Check();

    return E_RTC_SUCCESS;
}

/**
  * @brief      RTC access register enable
  *
  * @param[in]  bEnable    1: Enable access register
  *                        0: Disable access register
  *
  * @retval     E_RTC_ERR_EIO   Time-out error
  * @retval     E_RTC_SUCCESS   Success
  *
  */
UINT32 RTC_WriteEnable(BOOL bEnable)
{
    INT32 volatile i32i;

    RTC_Check();

    if (bEnable)
    {
        outp32(REG_RTC_RWEN, RTC_WRITE_KEY);
        RTC_Check();

        for (i32i = 0 ; i32i < RTC_WAIT_COUNT ; i32i++)
        {
            /*-------------------------------------------------------------------------------------------------*/
            /* check RTC_RWEN[16] to find out RTC write enable                                                  */
            /*-------------------------------------------------------------------------------------------------*/
            if (inp32(REG_RTC_RWEN) & 0x10000)
            {
                break;
            }
        }

        if (i32i == RTC_WAIT_COUNT)
        {
            //sysprintf ("\nRTC: 3, set write enable FAILED!\n");

            return E_RTC_ERR_EIO;
        }
    }
    else
    {
        for (i32i = 0 ; i32i < RTC_WAIT_COUNT ; i32i++)
        {
            if (inp32(REG_RTC_RWEN) == 0)
            {
                break;
            }
        }
    }

    return E_RTC_SUCCESS;
}

/**
  * @brief      Initial RTC and install ISR
  * @retval     E_RTC_ERR_EIO   Initial RTC time-out
  * @retval     E_RTC_SUCCESS   Success
  *
  */
UINT32 RTC_Init(void)
{
    INT32 i32i;

    /*-----------------------------------------------------------------------------------------------------*/
    /* When RTC is power on, write 0xa5eb1357 to RTC_INIR to reset all logic.                              */
    /*-----------------------------------------------------------------------------------------------------*/

    outp32(REG_RTC_INIT, RTC_INIT_KEY);
    RTC_Check();

    for (i32i = 0 ; i32i < RTC_WAIT_COUNT ; i32i++)
    {
        if (inp32(REG_RTC_INIT) & 0x01)
        {
            /* Check RTC_INIR[0] to find out RTC reset signal */
            break;
        }
    }

    if (i32i == RTC_WAIT_COUNT)
    {
        return E_RTC_ERR_EIO;
    }

    /*-----------------------------------------------------------------------------------------------------*/
    /* Install RTC ISR                                                                                     */
    /*-----------------------------------------------------------------------------------------------------*/

    outp32(REG_RTC_RWEN, RTC_WRITE_KEY);
    RTC_Check();

    for (i32i = 0 ; i32i < RTC_WAIT_COUNT ; i32i++)
    {
        /*-------------------------------------------------------------------------------------------------*/
        /* check RTC_RWEN[16] to find out RTC write enable                                                 */
        /*-------------------------------------------------------------------------------------------------*/
        if (inp32(REG_RTC_RWEN) & 0x10000)
        {
            break;
        }
    }

    if (i32i == RTC_WAIT_COUNT)
    {
        return E_RTC_ERR_EIO;
    }

    return E_RTC_SUCCESS;
}

/**
  * @brief      Set Current Timer
  *
  * @param[in]  *sPt    Specify the time property and current time. It includes:
  *                  -   u8cClockDisplay: \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24
  *                  -   u8cAmPm: \ref RTC_AM / \ref RTC_PM
  *                  -   u32cSecond: Second value
  *                  -   u32cMinute: Minute value
  *                  -   u32cHour: Hour value
  *                  -   u32cDayOfWeek: Day of week
  *                  -   u32cDay: Day value
  *                  -   u32cMonth: Month value
  *                  -   u32Year: Year value
  *                  -   u32AlarmMaskSecond: Mask second alarm
  *                  -   u32AlarmMaskMinute: Mask minute alarm
  *                  -   u32AlarmMaskHour: Mask hour alarm
  *                  -   *pfnAlarmCallBack: Call back function
  *
  * @retval     E_RTC_ERR_EIO   Initial RTC time-out
  * @retval     E_RTC_SUCCESS   Success
  *
  */
UINT32 RTC_Open(S_RTC_TIME_DATA_T *sPt)
{
    UINT32 volatile u32Reg;

    /*-----------------------------------------------------------------------------------------------------*/
    /* DO BASIC JUDGEMENT TO Check RTC time data value is reasonable or not.                               */
    /*-----------------------------------------------------------------------------------------------------*/
    if (((sPt->u32Year - RTC_YEAR2000) > 99) |
            ((sPt->u32cMonth == 0) || (sPt->u32cMonth > 12)) |
            ((sPt->u32cDay   == 0) || (sPt->u32cDay   > 31)))
    {
        return E_RTC_ERR_CALENDAR_VALUE;
    }

    if (sPt->u8cClockDisplay == RTC_CLOCK_12)
    {
        if ((sPt->u32cHour == 0) || (sPt->u32cHour > 12))
        {
            return E_RTC_ERR_TIMESACLE_VALUE ;
        }
    }
    else if (sPt->u8cClockDisplay == RTC_CLOCK_24)
    {
        if (sPt->u32cHour > 23)
        {
            return E_RTC_ERR_TIMESACLE_VALUE ;
        }
    }
    else
    {
        return E_RTC_ERR_TIMESACLE_VALUE ;
    }

    if ((sPt->u32cMinute > 59) |
            (sPt->u32cSecond > 59) |
            (sPt->u32cSecond > 59))
    {
        return E_RTC_ERR_TIME_VALUE ;
    }
    if (sPt->u32cDayOfWeek > 6)
    {
        return E_RTC_ERR_DWR_VALUE ;
    }

    /*-----------------------------------------------------------------------------------------------------*/
    /* Second, set RTC time data.                                                                          */
    /*-----------------------------------------------------------------------------------------------------*/
    if (sPt->u8cClockDisplay == RTC_CLOCK_12)
    {
        g_chHourMode = RTC_CLOCK_12;

        RTC_WriteEnable(1);
        outp32(REG_RTC_TIMEFMT, RTC_CLOCK_12);
        RTC_Check();

        /*-------------------------------------------------------------------------------------------------*/
        /* important, range of 12-hour PM mode is 21 upto 32                                               */
        /*-------------------------------------------------------------------------------------------------*/
        if (sPt->u8cAmPm == RTC_PM)
            sPt->u32cHour += 20;
    }
    else                                                                               /* RTC_CLOCK_24 */
    {
        g_chHourMode = RTC_CLOCK_24;

        RTC_WriteEnable(1);
        outp32(REG_RTC_TIMEFMT, RTC_CLOCK_24);
        RTC_Check();
    }


    g_u32hiHour  = sPt->u32cHour / 10;
    g_u32loHour  = sPt->u32cHour % 10;
    g_u32hiMin   = sPt->u32cMinute / 10;
    g_u32loMin   = sPt->u32cMinute % 10;
    g_u32hiSec   = sPt->u32cSecond / 10;
    g_u32loSec   = sPt->u32cSecond % 10;
    u32Reg     = (g_u32hiHour << 20);
    u32Reg    |= (g_u32loHour << 16);
    u32Reg    |= (g_u32hiMin << 12);
    u32Reg    |= (g_u32loMin << 8);
    u32Reg    |= (g_u32hiSec << 4);
    u32Reg    |= g_u32loSec;
    g_u32Reg = u32Reg;

    RTC_WriteEnable(1);
    outp32(REG_RTC_TIME, (UINT32)g_u32Reg);
    RTC_Check();

    if (sPt->u8cClockDisplay == RTC_CLOCK_12)
    {
        if (sPt->u8cAmPm == RTC_PM)
            sPt->u32cHour -= 20;
    }

    g_u32hiYear  = (sPt->u32Year - RTC_YEAR2000) / 10;
    g_u32loYear  = (sPt->u32Year - RTC_YEAR2000) % 10;
    g_u32hiMonth =  sPt->u32cMonth              / 10;
    g_u32loMonth =  sPt->u32cMonth              % 10;
    g_u32hiDay   =  sPt->u32cDay                / 10;
    g_u32loDay   =  sPt->u32cDay                % 10;
    u32Reg    = (g_u32hiYear << 20);
    u32Reg    |= (g_u32loYear << 16);
    u32Reg    |= (g_u32hiMonth << 12);
    u32Reg    |= (g_u32loMonth << 8);
    u32Reg    |= (g_u32hiDay << 4);
    u32Reg    |= g_u32loDay;
    g_u32Reg = u32Reg;

    RTC_WriteEnable(1);
    outp32(REG_RTC_CAL, (UINT32)g_u32Reg);
    RTC_Check();

    RTC_WriteEnable(1);
    outp32(REG_RTC_WEEKDAY, (UINT32)sPt->u32cDayOfWeek);
    RTC_Check();

    return E_RTC_SUCCESS;
}


/**
  * @brief      Read current date/time or alarm date/time from RTC
  *
  * @param[in]   eTime  \ref RTC_CURRENT_TIME / \ref RTC_ALARM_TIME
  * @param[out]  *sPt    Specify the time property and current time. It includes:
  *                  -   u8cClockDisplay: \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24
  *                  -   u8cAmPm: \ref RTC_AM / \ref RTC_PM
  *                  -   u32cSecond: Second value
  *                  -   u32cMinute: Minute value
  *                  -   u32cHour: Hour value
  *                  -   u32cDayOfWeek: Day of week
  *                  -   u32cDay: Day value
  *                  -   u32cMonth: Month value
  *                  -   u32Year: Year value
  *                  -   u32AlarmMaskSecond: Mask second alarm
  *                  -   u32AlarmMaskMinute: Mask minute alarm
  *                  -   u32AlarmMaskHour: Mask hour alarm
  *                  -   *pfnAlarmCallBack: Call back function
  *
  * @retval     E_RTC_ERR_ENOTTY   Wrong select time
  * @retval     E_RTC_SUCCESS   Success
  *
  */
UINT32 RTC_Read(E_RTC_TIME_SELECT eTime, S_RTC_TIME_DATA_T *sPt)
{
    UINT32 u32Tmp;

    sPt->u8cClockDisplay = inp32(REG_RTC_TIMEFMT);                               /* 12/24-hour */
    sPt->u32cDayOfWeek = inp32(REG_RTC_WEEKDAY);                                  /* Day of week */

    switch (eTime)
    {
    case RTC_CURRENT_TIME:
    {
        g_u32Reg   = inp32(REG_RTC_CAL);
        g_u32Reg1  = inp32(REG_RTC_TIME);
        break;
    }
    case RTC_ALARM_TIME:
    {
        g_u32Reg   = inp32(REG_RTC_CALM);
        g_u32Reg1  = inp32(REG_RTC_TALM);
        break;
    }
    default:
    {
        return E_RTC_ERR_ENOTTY;
    }
    }

    g_u32hiYear  = (g_u32Reg & 0xF00000) >> 20;
    g_u32loYear  = (g_u32Reg & 0xF0000) >> 16;
    g_u32hiMonth = (g_u32Reg & 0x1000) >> 12;
    g_u32loMonth = (g_u32Reg & 0xF00) >> 8;
    g_u32hiDay   = (g_u32Reg & 0x30) >> 4;
    g_u32loDay   =  g_u32Reg & 0xF;

    u32Tmp = (g_u32hiYear * 10);
    u32Tmp += g_u32loYear;
    sPt->u32Year   =   u32Tmp  + RTC_YEAR2000;

    u32Tmp = (g_u32hiMonth * 10);
    sPt->u32cMonth = u32Tmp + g_u32loMonth;

    u32Tmp = (g_u32hiDay * 10);
    sPt->u32cDay   =  u32Tmp  + g_u32loDay;

    g_u32hiHour = (g_u32Reg1 & 0x300000) >> 20;
    g_u32loHour = (g_u32Reg1 & 0xF0000) >> 16;
    g_u32hiMin  = (g_u32Reg1 & 0x7000) >> 12;
    g_u32loMin  = (g_u32Reg1 & 0xF00) >> 8;
    g_u32hiSec  = (g_u32Reg1 & 0x70) >> 4;
    g_u32loSec  =  g_u32Reg1 & 0xF;

    if (sPt->u8cClockDisplay == RTC_CLOCK_12)
    {
        u32Tmp = (g_u32hiHour * 10);
        u32Tmp += g_u32loHour;
        sPt->u32cHour = u32Tmp;                                /* AM: 1~12. PM: 21~32. */

        if (eTime == RTC_CURRENT_TIME)
        {
            if (sPt->u32cHour >= 21)
            {
                sPt->u8cAmPm = RTC_PM;
                sPt->u32cHour -= 20;
            }
            else
            {
                sPt->u8cAmPm = RTC_AM;
            }
        }
        else
        {
            if (sPt->u32cHour < 12)
            {
                if (sPt->u32cHour == 0)
                    sPt->u32cHour = 12;
                sPt->u8cAmPm = RTC_AM;
            }
            else
            {
                sPt->u32cHour -= 12;
                sPt->u8cAmPm = RTC_PM;
            }
        }

        u32Tmp = (g_u32hiMin  * 10);
        u32Tmp += g_u32loMin;
        sPt->u32cMinute = u32Tmp;

        u32Tmp = (g_u32hiSec  * 10);
        u32Tmp += g_u32loSec;
        sPt->u32cSecond = u32Tmp;

    }
    else
    {
        /* RTC_CLOCK_24 */
        u32Tmp = (g_u32hiHour * 10);
        u32Tmp += g_u32loHour;
        sPt->u32cHour   = u32Tmp;

        u32Tmp = (g_u32hiMin  * 10);
        u32Tmp += g_u32loMin;
        sPt->u32cMinute = u32Tmp;

        u32Tmp = (g_u32hiSec  * 10);
        u32Tmp += g_u32loSec;
        sPt->u32cSecond = u32Tmp;
    }

    return E_RTC_SUCCESS;

}


/**
  * @brief      Write current date/time or alarm date/time from RTC
  *
  * @param[in]   eTime  \ref RTC_CURRENT_TIME / \ref RTC_ALARM_TIME
  * @param[in]  *sPt     Specify the time property and current time. It includes:
  *                  -   u8cClockDisplay: \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24
  *                  -   u8cAmPm: \ref RTC_AM / \ref RTC_PM
  *                  -   u32cSecond: Second value
  *                  -   u32cMinute: Minute value
  *                  -   u32cHour: Hour value
  *                  -   u32cDayOfWeek: Day of week
  *                  -   u32cDay: Day value
  *                  -   u32cMonth: Month value
  *                  -   u32Year: Year value
  *                  -   u32AlarmMaskSecond: Mask second alarm
  *                  -   u32AlarmMaskMinute: Mask minute alarm
  *                  -   u32AlarmMaskHour: Mask hour alarm
  *                  -   *pfnAlarmCallBack: Call back function
  *
  * @retval     E_RTC_ERR_ENOTTY            Wrong select time
  * @retval     E_RTC_ERR_CALENDAR_VALUE    Wrong calender value
  * @retval     E_RTC_ERR_TIME_VALUE        Wrong time value
  * @retval     E_RTC_ERR_DWR_VALUE         Wrong day of week value
  * @retval     E_RTC_SUCCESS               Success
  *
  */
UINT32 RTC_Write(E_RTC_TIME_SELECT eTime, S_RTC_TIME_DATA_T *sPt)
{
    UINT32 u32Reg;

    /*-----------------------------------------------------------------------------------------------------*/
    /* Check RTC time data value is reasonable or not.                                                     */
    /*-----------------------------------------------------------------------------------------------------*/
    if (((sPt->u32Year - RTC_YEAR2000) > 99) |
            ((sPt->u32cMonth == 0) || (sPt->u32cMonth > 12)) |
            ((sPt->u32cDay   == 0) || (sPt->u32cDay   > 31)))
    {
        return E_RTC_ERR_CALENDAR_VALUE;
    }

    if ((sPt->u32Year - RTC_YEAR2000) > 99)
    {
        return E_RTC_ERR_CALENDAR_VALUE;
    }

    if ((sPt->u32cMonth == 0) || (sPt->u32cMonth > 12))
    {
        return E_RTC_ERR_CALENDAR_VALUE;
    }

    if ((sPt->u32cDay == 0) || (sPt->u32cDay > 31))
    {
        return E_RTC_ERR_CALENDAR_VALUE;
    }

    if (sPt->u8cClockDisplay == RTC_CLOCK_12)
    {
        if ((sPt->u32cHour == 0) || (sPt->u32cHour > 12))
        {
            return E_RTC_ERR_TIME_VALUE;
        }
    }
    else if (sPt->u8cClockDisplay == RTC_CLOCK_24)
    {
        if (sPt->u32cHour > 23)
        {
            return E_RTC_ERR_TIME_VALUE;
        }
    }
    else
    {
        return E_RTC_ERR_TIME_VALUE;
    }

    if (sPt->u32cMinute > 59)
    {
        return E_RTC_ERR_TIME_VALUE;
    }

    if (sPt->u32cSecond > 59)
    {
        return E_RTC_ERR_TIME_VALUE;
    }

    if (sPt->u32cDayOfWeek > 6)
    {
        return E_RTC_ERR_DWR_VALUE;
    }

    switch (eTime)
    {

    case RTC_CURRENT_TIME:
    {
        /*---------------------------------------------------------------------------------------------*/
        /* Second, set RTC time data.                                                                  */
        /*---------------------------------------------------------------------------------------------*/

        if (sPt->u8cClockDisplay == RTC_CLOCK_12)
        {
            g_chHourMode = RTC_CLOCK_12;

            RTC_WriteEnable(1);
            outp32(REG_RTC_TIMEFMT, RTC_CLOCK_12);
            RTC_Check();

            /*-----------------------------------------------------------------------------------------*/
            /* important, range of 12-hour PM mode is 21 upto 32                                       */
            /*-----------------------------------------------------------------------------------------*/
            if (sPt->u8cAmPm == RTC_PM)
            {
                sPt->u32cHour += 20;
            }
        }
        else                                                                  /* RTC_CLOCK_24 */
        {
            g_chHourMode = RTC_CLOCK_24;

            RTC_WriteEnable(1);
            outp32(REG_RTC_TIMEFMT, RTC_CLOCK_24);
            RTC_Check();

        }

        g_u32hiHour  = sPt->u32cHour / 10;
        g_u32loHour  = sPt->u32cHour % 10;
        g_u32hiMin   = sPt->u32cMinute / 10;
        g_u32loMin   = sPt->u32cMinute % 10;
        g_u32hiSec   = sPt->u32cSecond / 10;
        g_u32loSec   = sPt->u32cSecond % 10;

        u32Reg = (g_u32hiHour << 20);
        u32Reg |= (g_u32loHour << 16);
        u32Reg |= (g_u32hiMin << 12);
        u32Reg |= (g_u32loMin << 8);
        u32Reg |= (g_u32hiSec << 4);
        u32Reg |= g_u32loSec;
        g_u32Reg = u32Reg;

        RTC_WriteEnable(1);
        outp32(REG_RTC_TIME, (UINT32)g_u32Reg);
        RTC_Check();

        g_u32hiYear  = (sPt->u32Year - RTC_YEAR2000) / 10;
        g_u32loYear  = (sPt->u32Year - RTC_YEAR2000) % 10;
        g_u32hiMonth = sPt->u32cMonth / 10;
        g_u32loMonth = sPt->u32cMonth % 10;
        g_u32hiDay   = sPt->u32cDay / 10;
        g_u32loDay   = sPt->u32cDay % 10;

        u32Reg = (g_u32hiYear << 20);
        u32Reg |= (g_u32loYear << 16);
        u32Reg |= (g_u32hiMonth << 12);
        u32Reg |= (g_u32loMonth << 8);
        u32Reg |= (g_u32hiDay << 4);
        u32Reg |= g_u32loDay;
        g_u32Reg = u32Reg;

        RTC_WriteEnable(1);
        outp32(REG_RTC_CAL, (UINT32)g_u32Reg);
        RTC_Check();

        RTC_WriteEnable(1);
        outp32(REG_RTC_WEEKDAY, (UINT32) sPt->u32cDayOfWeek);
        RTC_Check();

        if (sPt->u8cClockDisplay == RTC_CLOCK_12)
        {
            if (sPt->u8cAmPm == RTC_PM)
            {
                sPt->u32cHour -= 20;
            }
        }

        return E_RTC_SUCCESS;

    }
    case RTC_ALARM_TIME:
    {
        RTC_WriteEnable(1);
        outp32(REG_RTC_PWRCTL, inp32(REG_RTC_PWRCTL) & ~RTC_PWRCTL_ALARM_EN_Msk);
        RTC_Check();

        /*---------------------------------------------------------------------------------------------*/
        /* Second, set alarm time data.                                                                */
        /*---------------------------------------------------------------------------------------------*/
        g_u32hiYear = (sPt->u32Year - RTC_YEAR2000) / 10;
        g_u32loYear = (sPt->u32Year - RTC_YEAR2000) % 10;
        g_u32hiMonth = sPt->u32cMonth / 10;
        g_u32loMonth = sPt->u32cMonth % 10;
        g_u32hiDay = sPt->u32cDay / 10;
        g_u32loDay = sPt->u32cDay % 10;

        //u32Reg = ((sPt->u32AlarmMaskDayOfWeek & 0x1) << 31);
        u32Reg = ((sPt->u32cDayOfWeek & 0x7) << 24);
        //u32Reg|= ((sPt->u32AlarmMaskYear & 0x1) << 30);
        u32Reg |= (g_u32hiYear << 20);
        u32Reg |= (g_u32loYear << 16);
        //u32Reg|= ((sPt->u32AlarmMaskMonth & 0x1) << 29);
        u32Reg |= (g_u32hiMonth << 12);
        u32Reg |= (g_u32loMonth << 8);
        //u32Reg|= ((sPt->u32AlarmMaskDay & 0x1) << 28);
        u32Reg |= (g_u32hiDay << 4);
        u32Reg |= g_u32loDay;

        g_u32Reg = u32Reg;

        RTC_WriteEnable(1);
        outp32(REG_RTC_CALM, (UINT32)g_u32Reg);
        RTC_Check();


        if (g_chHourMode == RTC_CLOCK_12)
        {
            if (sPt->u8cAmPm == RTC_PM)       /* important, range of 12-hour PM mode is 21 upto 32 */
            {
                sPt->u32cHour += 20;
            }
        }
        g_u32hiHour   = sPt->u32cHour / 10;
        g_u32loHour   = sPt->u32cHour % 10;
        g_u32hiMin  = sPt->u32cMinute / 10;
        g_u32loMin  = sPt->u32cMinute % 10;
        g_u32hiSec  = sPt->u32cSecond / 10;
        g_u32loSec  = sPt->u32cSecond % 10;

        u32Reg = ((sPt->u32AlarmMaskHour & 0x1) << 30);
        u32Reg |= (g_u32hiHour << 20);
        u32Reg |= (g_u32loHour << 16);
        u32Reg |= ((sPt->u32AlarmMaskMinute & 0x1) << 29);
        u32Reg |= (g_u32hiMin << 12);
        u32Reg |= (g_u32loMin << 8);
        u32Reg |= ((sPt->u32AlarmMaskSecond & 0x1) << 28);
        u32Reg |= (g_u32hiSec << 4);
        u32Reg |= g_u32loSec;

        g_u32Reg = u32Reg;

        RTC_WriteEnable(1);
        outp32(REG_RTC_TALM, (UINT32)g_u32Reg);
        RTC_Check();

        if (sPt->u8cClockDisplay == RTC_CLOCK_12)
        {
            if (sPt->u8cAmPm == RTC_PM)
            {
                sPt->u32cHour -= 20;
            }
        }
        /*---------------------------------------------------------------------------------------------*/
        /* Finally, enable alarm interrupt.                                                            */
        /*---------------------------------------------------------------------------------------------*/

        RTC_Ioctl(0, RTC_IOC_ENABLE_INT, RTC_ALARM_INT, 0);

        RTC_WriteEnable(1);
        outp32(REG_RTC_PWRCTL, inp32(REG_RTC_PWRCTL) | RTC_PWRCTL_ALARM_EN_Msk);
        RTC_Check();

        return E_RTC_SUCCESS;
    }
    default:
    {
        return E_RTC_ERR_ENOTTY;
    }
    }

}


/**
  * @brief      Support some commands for application.
  *
  * @param[in]   i32Num     Interface number.   always set 0
  * @param[in]   eCmd       Command
  * @param[in]   u32Arg0    Arguments for the command
  * @param[in]   u32Arg1    Arguments for the command.
  *
  * @retval     E_RTC_ERR_ENOTTY            Wrong command or argument
  * @retval     E_RTC_ERR_ENODEV            Interface number incorrect
  * @retval     E_RTC_SUCCESS               Success
  *
  */
UINT32 RTC_Ioctl(INT32 i32Num, E_RTC_CMD eCmd, UINT32 u32Arg0, UINT32 u32Arg1)
{
    INT32 i32Ret;
    UINT32 u32Reg;
    RTC_TICK_T *ptick;
    UINT32 u32Tmp;

    if (i32Num != 0)
        return E_RTC_ERR_ENODEV;

    switch (eCmd)
    {

    case RTC_IOC_IDENTIFY_LEAP_YEAR:
    {
        u32Reg = inp32(REG_RTC_LEAPYEAR);
        if (u32Reg & 0x01)
        {
            *(PUINT32)u32Arg0 = RTC_LEAP_YEAR;
        }
        else
        {
            *(PUINT32)u32Arg0 = 0;
        }
        break;
    }
    case RTC_IOC_SET_TICK_MODE:
    {
        ptick = (RTC_TICK_T *) u32Arg0;

        if (g_bIsEnableTickInt == TRUE)
        {
            RTC_Ioctl(0, RTC_IOC_DISABLE_INT, RTC_TICK_INT, 0);
            g_bIsEnableTickInt = TRUE;
        }

        if (ptick->ucMode > RTC_TICK_1_128_SEC)                            /*Tick mode 0 to 7 */
        {
            return E_RTC_ERR_ENOTTY ;
        }

        RTC_WriteEnable(1);
        outp32(REG_RTC_TICK, ptick->ucMode);
        RTC_Check();

        /*---------------------------------------------------------------------------------------------*/
        /* Reset tick interrupt status if program enable tick interrupt before.                        */
        /*---------------------------------------------------------------------------------------------*/
        if (g_bIsEnableTickInt == TRUE)
        {

            RTC_Ioctl(0, RTC_IOC_ENABLE_INT, RTC_TICK_INT, 0);

            return E_RTC_SUCCESS;
        }
        break;
    }

    case RTC_IOC_GET_TICK:
    {
        break;
    }

    case RTC_IOC_RESTORE_TICK:
    {
        break;
    }

    case RTC_IOC_ENABLE_INT:
    {

        switch ((RTC_INT_SOURCE)u32Arg0)
        {

        case RTC_TICK_INT:
        {
            g_bIsEnableTickInt   = TRUE;
            u32Tmp = inp32(REG_RTC_INTEN) | RTC_TICK_INT;
            break;
        }
        case RTC_ALARM_INT:
        {
            g_bIsEnableAlarmInt  = TRUE;

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_PWRCTL) | RTC_PWRCTL_ALARM_EN_Msk;

            outp32(REG_RTC_PWRCTL, u32Tmp);
            outp32(REG_RTC_INTEN, inp32(REG_RTC_INTEN) | RTC_INTEN_ALMIEN_Msk);

            RTC_Check();

            u32Tmp = inp32(REG_RTC_INTEN) | RTC_ALARM_INT;

            break;
        }
        case RTC_RELATIVE_ALARM_INT:
        {
            g_bIsEnableAlarmInt  = TRUE;

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_PWRCTL) | RTC_PWRCTL_REL_ALARM_EN_Msk;

            outp32(REG_RTC_PWRCTL, u32Tmp);
            RTC_Check();

            u32Tmp = inp32(REG_RTC_INTEN) | RTC_RELATIVE_ALARM_INT;
            break;
        }
        case RTC_PSWI_INT:
        {
            g_bIsEnableAlarmInt  = TRUE;
            u32Tmp = inp32(REG_RTC_INTEN) | RTC_PSWI_INT;
            break;
        }
        default:
        {
            return E_RTC_ERR_ENOTTY;

        }
        }

        RTC_WriteEnable(1);
        outp32(REG_RTC_INTEN, u32Tmp);
        RTC_Check();

        break;
    }
    case RTC_IOC_DISABLE_INT:
    {

        switch ((RTC_INT_SOURCE)u32Arg0)
        {
        case RTC_TICK_INT:
        {
            g_bIsEnableTickInt   = FALSE;

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_INTEN) & (~RTC_TICK_INT);

            outp32(REG_RTC_INTEN, u32Tmp);

            outp32(REG_RTC_INTSTS, RTC_TICK_INT);
            RTC_Check();

            break;
        }
        case RTC_ALARM_INT:
        {
            g_bIsEnableAlarmInt  = FALSE;

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_INTEN) & (~RTC_ALARM_INT);

            outp32(REG_RTC_INTEN, u32Tmp);
            RTC_Check();

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_PWRCTL) & ~RTC_PWRCTL_ALARM_EN_Msk;

            outp32(REG_RTC_PWRCTL, u32Tmp);
            RTC_Check();

            outp32(REG_RTC_INTSTS, RTC_ALARM_INT);

            break;
        }
        case RTC_RELATIVE_ALARM_INT:
        {
            g_bIsEnableAlarmInt  = FALSE;

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_INTEN) & (~RTC_RELATIVE_ALARM_INT);

            outp32(REG_RTC_INTEN, u32Tmp);
            RTC_Check();

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_PWRCTL) & ~RTC_PWRCTL_REL_ALARM_EN_Msk;

            outp32(REG_RTC_PWRCTL, u32Tmp);
            RTC_Check();

            outp32(REG_RTC_INTSTS, RTC_RELATIVE_ALARM_INT);

            break;
        }
        case RTC_PSWI_INT:
        {
            g_bIsEnableAlarmInt  = FALSE;

            RTC_WriteEnable(1);
            u32Tmp = inp32(REG_RTC_INTEN) & (~RTC_PSWI_INT);

            outp32(REG_RTC_INTEN, u32Tmp);
            RTC_Check();

            outp32(REG_RTC_INTSTS, RTC_PSWI_INT);

            break;
        }

        case RTC_ALL_INT:
        {
            g_bIsEnableTickInt   = FALSE;
            g_bIsEnableAlarmInt  = FALSE;

            RTC_WriteEnable(1);
            outp32(REG_RTC_INTEN, 0);
            outp32(REG_RTC_INTSTS, RTC_ALL_INT);
            RTC_Check();

            break;
        }
        default:
        {
            return E_RTC_ERR_ENOTTY;
        }
        }


        break;
    }

    case RTC_IOC_SET_FREQUENCY:
    {
        i32Ret = RTC_DoFrequencyCompensation(u32Arg0) ;
        if (i32Ret != 0)
        {
            return E_RTC_ERR_ENOTTY;
        }
        break;
    }
    case RTC_IOC_SET_POWER_ON:
    {
        RTC_WriteEnable(1);
        u32Tmp = inp32(REG_RTC_PWRCTL) | 0x01;

        outp32(REG_RTC_PWRCTL, u32Tmp);
        RTC_Check();

        while ((inp32(REG_RTC_PWRCTL) & 0x01) != 0x1);

        break;
    }
    case RTC_IOC_SET_POWER_OFF:
    {
        RTC_WriteEnable(1);
        outp32(REG_RTC_PWRCTL, (inp32(REG_RTC_PWRCTL) & ~0x01) | 2);
        RTC_Check();

        while (1);

        //break;
    }
    case RTC_IOC_SET_POWER_OFF_PERIOD:
    {
        if (u32Arg0 < 4) u32Arg0 = 4;

        u32Arg0 = u32Arg0 - 4;

        RTC_WriteEnable(1);
        outp32(REG_RTC_PWRCTL, (inp32(REG_RTC_PWRCTL) & ~0xF000) | ((u32Arg0 & 0xF) << 12));
        RTC_Check();

        break;
    }
    case RTC_IOC_ENABLE_HW_POWEROFF:
    {
        RTC_WriteEnable(1);
        outp32(REG_RTC_PWRCTL, (inp32(REG_RTC_PWRCTL) | 0x04));
        RTC_Check();

        break;
    }
    case RTC_IOC_DISABLE_HW_POWEROFF:
    {
        RTC_WriteEnable(1);
        outp32(REG_RTC_PWRCTL, (inp32(REG_RTC_PWRCTL) & ~0x04));
        RTC_Check();

        break;
    }
    case RTC_IOC_SET_PSWI_CALLBACK:
    {

        RTC_Ioctl(0, RTC_IOC_ENABLE_INT, RTC_PSWI_INT, 0);

        break;
    }
    case RTC_IOC_GET_POWERKEY_STATUS:
    {
        RTC_WriteEnable(1);
        if (inp32(REG_RTC_PWRCTL) & 0x80)
            *(PUINT32)u32Arg0 = 1;
        else
            *(PUINT32)u32Arg0 = 0;

        break;
    }
    case RTC_IOC_SET_RELEATIVE_ALARM:
    {
        g_bIsEnableAlarmInt  = TRUE;

        RTC_WriteEnable(1);
        outp32(REG_RTC_PWRCTL, (inp32(REG_RTC_PWRCTL) & ~0xFFF0010));
        RTC_Check();

        RTC_WriteEnable(1);
        u32Tmp = (inp32(REG_RTC_PWRCTL) & ~0xFFF0000) | ((u32Arg0 & 0xFFF) << 16) | RTC_PWRCTL_REL_ALARM_EN_Msk;

        outp32(REG_RTC_PWRCTL, u32Tmp);
        RTC_Check();

        g_bIsEnableAlarmInt  = TRUE;

        RTC_WriteEnable(1);
        u32Tmp = inp32(REG_RTC_INTEN) | RTC_RELATIVE_ALARM_INT;

        outp32(REG_RTC_INTEN, u32Tmp);
        RTC_Check();

        break;

    }

    default:
    {
        return E_RTC_ERR_ENOTTY;
    }
    }

    return E_RTC_SUCCESS;
}

/**
  * @brief      Disable AIC channel of RTC and both tick and alarm interrupt.
  *
  * @param[in]  None
  *
  * @retval     E_RTC_SUCCESS               Success
  *
  */
UINT32 RTC_Close(void)
{

    g_bIsEnableTickInt = FALSE;

    sysDisableInterrupt(RTC_IRQn);


    RTC_Ioctl(0, RTC_IOC_DISABLE_INT, RTC_ALL_INT, 0);


    return E_RTC_SUCCESS;
}

/**
  * @brief      Enable RTC clock.
  *
  * @param[in]  bEnable  1: Enable \n
  *                      2: Disable
  *
  * @return     None
  *
  */
void RTC_EnableClock(BOOL bEnable)
{
    if (bEnable)
        outp32(REG_CLK_PCLKEN0, inp32(REG_CLK_PCLKEN0) | (1 << 2));
    else
        outp32(REG_CLK_PCLKEN0, inp32(REG_CLK_PCLKEN0) & ~(1 << 2));

}



/*@}*/ /* end of group N9H30_RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_RTC_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */


/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

