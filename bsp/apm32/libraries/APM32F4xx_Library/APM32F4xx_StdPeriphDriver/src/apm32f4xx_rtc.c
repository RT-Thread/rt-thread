/*!
 * @file        apm32f4xx_rtc.c
 *
 * @brief       This file provides all the RTC firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx.h"
#include "apm32f4xx_rtc.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup RTC_Driver
  * @brief RTC driver modules
  @{
*/

/** @defgroup RTC_Macros Macros
  @{
*/

/* RTC timeout definition */
#define RTC_TIMEOUT_WAKE_UP        ((uint32_t)0x00010000)
#define RTC_TIMEOUT_INIT           ((uint32_t)0x00010000)
#define RTC_TIMEOUT_ALARM          ((uint32_t)0x00010000)
#define RTC_TIMEOUT_CALIB          ((uint32_t)0x00020000)
#define RTC_TIMEOUT_SYNCHRO        ((uint32_t)0x00020000)
#define RTC_TIMEOUT_SHIFT          ((uint32_t)0x00001000)

/**@} end of group RTC_Macros*/

/** @defgroup RTC_Functions
  @{
*/

static uint8_t RTC_ByteConBcd2(uint8_t val);
static uint8_t RTC_Bcd2ConByte(uint8_t val);

/*!
 * @brief     Reset the RTC registers to their default values.
 *
 * @param     None
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_Reset(void)
{
    __IO uint32_t timeout = 0x00;

    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();

        return ERROR;
    }
    else
    {
        /* Reset register */
        RTC->TIME  = (uint32_t)0x00000000;
        RTC->DATE  = (uint32_t)0x00002101;
        RTC->CTRL &= (uint32_t)0x00000007;

        /* Wait for wakeup timer write flag */
        while ((RTC->STS_B.WUTWFLG != BIT_SET) && (timeout != RTC_TIMEOUT_WAKE_UP))
        {
            timeout++;
        }

        if (RTC->STS_B.WUTWFLG == BIT_RESET)
        {
            RTC_EnableWriteProtection();

            return ERROR;
        }
        else
        {
            /* Reset register */
            RTC->CTRL = (uint32_t)0x00000000;
            RTC->AUTORLD = (uint32_t)0x0000FFFF;
            RTC->PSC = (uint32_t)0x007F00FF;
            RTC->DCAL = (uint32_t)0x00000000;
            RTC->ALRMA = (uint32_t)0x00000000;
            RTC->ALRMB = (uint32_t)0x00000000;
            RTC->SHIFT = (uint32_t)0x00000000;
            RTC->CAL = (uint32_t)0x00000000;
            RTC->ALRMASS = (uint32_t)0x00000000;
            RTC->ALRMBSS = (uint32_t)0x00000000;

            RTC->STS = (uint32_t)0x00000000;

            RTC->TACFG = (uint32_t)0x00000000;

            if (RTC_WaitForSynchro() == ERROR)
            {
                RTC_EnableWriteProtection();

                return ERROR;
            }
            else
            {
                RTC_EnableWriteProtection();

                return SUCCESS;
            }
        }
    }
}

/*!
 * @brief     Deinitializes the RTC registers to their default reset values
 *
 * @param     rtcConfig : pointer to a RTC_Config_T structure which will be initialized
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_Config(RTC_Config_T* rtcConfig)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();

        return ERROR;
    }
    else
    {
        RTC->CTRL_B.TIMEFCFG  = (rtcConfig->format);
        RTC->PSC_B.SPSC = (rtcConfig->synchPrediv);
        RTC->PSC_B.APSC = (rtcConfig->asynchPrediv);

        RTC_DisableInit();
        RTC_EnableWriteProtection();

        return SUCCESS;
    }
}

/*!
 * @brief     Fills each RTC_ConfigStruct member with its default value
 *
 * @param     rtcConfig : pointer to a RTC_Config_T structure which will be initialized
 *
 * @retval    None
 */
void RTC_ConfigStructInit(RTC_Config_T* rtcConfig)
{
    rtcConfig->format = RTC_HOURFORMAT_24;
    rtcConfig->asynchPrediv = (uint32_t)0x7F;
    rtcConfig->synchPrediv = (uint32_t)0xFF;
}

/*!
 * @brief     Enable the write protection for RTC registers
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableWriteProtection(void)
{
    RTC->WRPROT = 0xFF;
}

/*!
 * @brief     Disable the write protection for RTC registers
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableWriteProtection(void)
{
    RTC->WRPROT = 0xCA;
    RTC->WRPROT = 0x53;
}

/*!
 * @brief     Enable the RTC Initialization mode.
 *
 * @param     None
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_EnableInit(void)
{
    __IO uint32_t timeout = 0x00;

    if (RTC->STS_B.RINITFLG == BIT_RESET)
    {
        /* Enable initialization mode */
        RTC->STS_B.INITEN = BIT_SET;

        /* Wait for initialization flag */
        while ((RTC->STS_B.RINITFLG != BIT_SET) && (timeout != RTC_TIMEOUT_INIT))
        {
            timeout++;
        }

        if (RTC->STS_B.RINITFLG != BIT_SET)
        {
            return ERROR;
        }
    }

    return SUCCESS;
}

/*!
 * @brief     Disable the RTC Initialization mode.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableInit(void)
{
    RTC->STS_B.INITEN = BIT_RESET;
}

/*!
 * @brief     Waits until the RTC Time and Date registers are synchronized
 *            with RTC APB clock
 *
 * @param     None
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_WaitForSynchro(void)
{
    __IO uint32_t timeout = 0;

    RTC_DisableWriteProtection();

    RTC->STS &= (uint32_t)0xFFFFFF5F;

    /* Wait for synchrocnt flag */
    while ((RTC->STS_B.RSFLG != BIT_SET) && (timeout != RTC_TIMEOUT_SYNCHRO))
    {
        timeout++;
    }

    if (RTC->STS_B.RSFLG != BIT_RESET)
    {
        RTC_EnableWriteProtection();

        return SUCCESS;
    }
    else
    {
        RTC_EnableWriteProtection();

        return ERROR;
    }
}

/*!
 * @brief     Enables the RTC reference clock detection.
 *
 * @param     None
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_EnableRefClock(void)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();

        return ERROR;
    }
    else
    {
        RTC->CTRL_B.RCLKDEN = BIT_SET;
        RTC_DisableInit();
        RTC_EnableWriteProtection();

        return SUCCESS;
    }
}

/*!
 * @brief     Disable the RTC reference clock detection
 *
 * @param     None
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_DisableRefClock(void)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();

        return ERROR;
    }
    else
    {
        RTC->CTRL_B.RCLKDEN = BIT_RESET;
        RTC_DisableInit();
        RTC_EnableWriteProtection();

        return SUCCESS;
    }
}

/*!
 * @brief     Enable the Bypass Shadow feature.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableBypassShadow(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.RCMCFG = BIT_SET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disable the Bypass Shadow feature.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableBypassShadow(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.RCMCFG = BIT_RESET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Config the RTC current time
 *
 * @param     format: specifies the format to write
 *                    This parameter can be one of the following values:
 *                    @arg RTC_FORMAT_BIN : Format in Bin
 *                    @arg RTC_FORMAT_BCD : Format in BCD
 *
 * @param     timeConfig: Pointer to a RTC_TimeConfig_T structure that
 *                        contains the configuration information for the RTC peripheral
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_ConfigTime(RTC_FORMAT_T format, RTC_TimeConfig_T* timeConfig)
{
    uint8_t state = ERROR;
    uint32_t temp = 0;

    if (RTC->CTRL_B.TIMEFCFG == BIT_RESET)
    {
        timeConfig->h12 = RTC_H12_AM;
    }

    /* Combine parameters of time */
    if (format != RTC_FORMAT_BIN)
    {
        temp = (((uint32_t)(timeConfig->hours) << 16) | \
                ((uint32_t)(timeConfig->minutes) << 8) | \
                ((uint32_t)(timeConfig->seconds))| \
                ((uint32_t)(timeConfig->h12) << 22));
    }
    else
    {
        temp = (uint32_t)(((uint32_t)RTC_ByteConBcd2(timeConfig->hours) << 16) | \
                          ((uint32_t)RTC_ByteConBcd2(timeConfig->minutes) << 8) | \
                          ((uint32_t)RTC_ByteConBcd2(timeConfig->seconds))| \
                          (((uint32_t)(timeConfig->h12) << 22)));
    }

    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        state = ERROR;
    }
    else
    {
        RTC->TIME = (uint32_t)(temp & 0x007F7F7F);

        RTC_DisableInit();

        if (RTC->CTRL_B.RCMCFG == RESET)
        {
            if (RTC_WaitForSynchro() == ERROR)
            {
                state = ERROR;
            }
            else
            {
                state = SUCCESS;
            }
        }
        else
        {
            state = SUCCESS;
        }
    }

    RTC_EnableWriteProtection();

    return state;
}

/*!
 * @brief     Fills each timeConfig member with its default value
 *
 * @param     timeConfig:  Pointer to a RTC_TimeConfig_T structure that
 *                         contains the configuration information for the RTC peripheral
 *
 * @retval    None
 */
void RTC_ConfigTimeStructInit(RTC_TimeConfig_T* timeConfig)
{
    timeConfig->hours = 0;
    timeConfig->minutes = 0;
    timeConfig->seconds = 0;
    timeConfig->h12 = RTC_H12_AM;
}

/*!
 * @brief     Read the RTC current Time
 *
 * @param     format: specifies the format to write
 *                    This parameter can be one of the following values:
 *                    @arg RTC_FORMAT_BIN : format in Bin
 *                    @arg RTC_FORMAT_BCD : format in BCD
 *
 * @param     time:  Pointer to a RTC_TimeConfig_T structure that
 *                   contains the configuration information for the RTC peripheral
 *
 * @retval    None
 */
void RTC_ReadTime(RTC_FORMAT_T format, RTC_TimeConfig_T* time)
{
    uint32_t temp = 0;

    temp = (uint32_t)((RTC->TIME) & 0x007F7F7F);

    time->h12 = (RTC_H12_T)((temp & 0x00400000) >> 22);
    time->hours   = (uint8_t)((temp & 0x003F0000) >> 16);
    time->minutes = (uint8_t)((temp & 0x00007F00) >>8);
    time->seconds = (uint8_t)(temp & 0x0000007F);

    if (format == RTC_FORMAT_BIN)
    {
        time->hours   = (uint8_t)RTC_Bcd2ConByte(time->hours);
        time->minutes = (uint8_t)RTC_Bcd2ConByte(time->minutes);
        time->seconds = (uint8_t)RTC_Bcd2ConByte(time->seconds);
    }
}

/*!
 * @brief     Read the RTC current Calendar Subseconds value
 *
 * @param     None
 *
 * @retval    RTC current Calendar Subseconds value
 */
uint32_t RTC_ReadSubSecond(void)
{
    uint32_t temp = 0;

    temp = (uint32_t)(RTC->SUBSEC);
    (void) (RTC->DATE);

    return temp;
}

/*!
 * @brief     Config the RTC current time
 *
 * @param     format: specifies the format to write
 *                    This parameter can be one of the following values:
 *                    @arg RTC_FORMAT_BIN : format in Bin
 *                    @arg RTC_FORMAT_BCD : format in BCD
 *
 * @param     dateConfig:  Pointer to a RTC_DateConfig_T structure that
 *                         contains the configuration DATE information for the RTC peripheral
 *
 * @retval    None
 */
uint8_t RTC_ConfigDate(RTC_FORMAT_T format, RTC_DateConfig_T* dateConfig)
{
    uint8_t state = ERROR;
    uint32_t temp = 0;

    if ((format == RTC_FORMAT_BIN) && ((dateConfig->month & 0x10) == 0x10))
    {
        dateConfig->month = (RTC_MONTH_T)((dateConfig->month & (uint32_t)~(0x10)) + 0x0A);
    }

    if (format != RTC_FORMAT_BIN)
    {
        temp = (((uint32_t)(dateConfig->year) << 16) | \
                ((uint32_t)(dateConfig->month) << 8) | \
                ((uint32_t)(dateConfig->date))| \
                ((uint32_t)(dateConfig->weekday) << 13));
    }
    else
    {
        temp = (((uint32_t)RTC_ByteConBcd2(dateConfig->year) << 16) | \
                ((uint32_t)RTC_ByteConBcd2(dateConfig->month) << 8) | \
                ((uint32_t)RTC_ByteConBcd2(dateConfig->date))| \
                ((uint32_t)(dateConfig->weekday) << 13));
    }

    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        state = ERROR;
    }
    else
    {
        RTC->DATE = (uint32_t)(temp & 0x00FFFF3F);
        RTC_DisableInit();

        if (RTC->CTRL_B.RCMCFG == RESET)
        {
            if (RTC_WaitForSynchro() == ERROR)
            {
                state = ERROR;
            }
            else
            {
                state = SUCCESS;
            }
        }
        else
        {
            state = SUCCESS;
        }
    }

    RTC_EnableWriteProtection();
    return state;
}

/*!
 * @brief     Fills each dateConfig member with its default value
 *
 * @param     dateConfig: Pointer to a RTC_DateConfig_T structure that contains
 *                        the configuration DATE information for the RTC peripheral
 *
 * @retval    None
 */
void RTC_ConfigDateStructInit(RTC_DateConfig_T* dateConfig)
{
    dateConfig->weekday = RTC_WEEKDAY_MONDAY;
    dateConfig->month = RTC_MONTH_JANUARY;
    dateConfig->date = 0x01;
    dateConfig->year = 0x00;
}

/*!
 * @brief     Read the RTC current date
 *
 * @param     format: specifies the format to write
 *                    This parameter can be one of the following values:
 *                    @arg RTC_FORMAT_BIN : format in Bin
 *                    @arg RTC_FORMAT_BCD : format in BCD
 *
 * @param     date: Pointer to a RTC_DateConfig_T structure that contains the
 *                  configuration DATE information for the RTC peripheral.
 *
 * @retval    None
 */
void RTC_ReadDate(RTC_FORMAT_T format, RTC_DateConfig_T* date)
{
    uint32_t temp = 0;
    temp = (uint32_t)((RTC->DATE) & 0x00FFFF3F);

    date->year  = (uint8_t)((temp & 0x00FF0000) >> 16);
    date->month = (RTC_MONTH_T)((temp & 0x00001F00) >>8);
    date->date  = (uint8_t)(temp &  0x0000003F);
    date->weekday =(RTC_WEEKDAY_T)((temp & 0x0000E000) >> 13);

    if (format == RTC_FORMAT_BIN)
    {
        date->year  = (uint8_t)RTC_Bcd2ConByte(date->year);
        date->month = (RTC_MONTH_T)RTC_Bcd2ConByte(date->month);
        date->date  = (uint8_t)RTC_Bcd2ConByte(date->date);
        date->weekday = (RTC_WEEKDAY_T)(date->weekday);
    }
}

/*!
 * @brief    Config the specified RTC alarm
 *
 * @param    format: specifies the format to write
 *                   This parameter can be one of the following values:
 *                   @arg RTC_FORMAT_BIN : format in Bin
 *                   @arg RTC_FORMAT_BCD : format in BCD
 *
 * @param    alarm: specifies the format to write
 *                  This parameter can be one of the following values:
 *                  @arg RTC_ALARM_A : to select Alarm A
 *                  @arg RTC_ALARM_B : to select Alarm B
 *
 * @param    alarmConfig: Pointer to a RTC_AlarmConfig_T structure that
 *                        contains the configuration ALRMA information for the RTC peripheral
 *
 * @retva    None
 */
void RTC_ConfigAlarm(RTC_FORMAT_T format, RTC_ALARM_T alarm, RTC_AlarmConfig_T* alarmConfig)
{
    uint32_t temp = 0;

    if (RTC->CTRL_B.TIMEFCFG == BIT_RESET)
    {
        alarmConfig->time.h12 = RTC_H12_AM;
    }

    if (format == RTC_FORMAT_BCD)
    {
        temp = (((uint32_t)(alarmConfig->time.hours) << 16) | \
                ((uint32_t)(alarmConfig->time.minutes) << 8) | \
                ((uint32_t)alarmConfig->time.seconds)| \
                ((uint32_t)(alarmConfig->time.h12) << 22) | \
                ((uint32_t)(alarmConfig->alarmDateWeekDay) << 24) | \
                ((uint32_t)alarmConfig->alarmDateWeekDaySel << 30) | \
                ((uint32_t)alarmConfig->alarmMask));
    }
    else
    {
        temp = (((uint32_t)RTC_ByteConBcd2(alarmConfig->time.hours) << 16) | \
                ((uint32_t)RTC_ByteConBcd2(alarmConfig->time.minutes) << 8) | \
                ((uint32_t)RTC_ByteConBcd2(alarmConfig->time.seconds))| \
                ((uint32_t)(alarmConfig->time.h12) << 22) | \
                ((uint32_t)RTC_ByteConBcd2(alarmConfig->alarmDateWeekDay) << 24) | \
                ((uint32_t)alarmConfig->alarmDateWeekDaySel << 30) | \
                ((uint32_t)alarmConfig->alarmMask));
    }

    RTC_DisableWriteProtection();

    if (alarm == RTC_ALARM_A)
    {
        RTC->ALRMA = temp;
    }
    else
    {
        RTC->ALRMB = temp;
    }

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Fills each alarmConfig member with its default value.
 *
 * @param     alarmConfig: Pointer to a RTC_AlarmConfig_T structure that
 *                         contains the configuration ALRMA information for the RTC peripheral
 *
 * @retval    None
 */
void RTC_ConfigAlarmStructInit(RTC_AlarmConfig_T* alarmConfig)
{
    alarmConfig->time.hours = 0;
    alarmConfig->time.minutes = 0;
    alarmConfig->time.seconds = 0;
    alarmConfig->time.h12 = RTC_H12_AM;
    alarmConfig->alarmDateWeekDay = 1;
    alarmConfig->alarmDateWeekDaySel = RTC_WEEKDAY_SEL_DATE;
    alarmConfig->alarmMask= RTC_MASK_NONE;
}

/*!
 * @brief     Read the RTC alarm value.
 *
 * @param     format: specifies the format to write
 *                    This parameter can be one of the following values:
 *                    @arg RTC_FORMAT_BIN : format in Bin
 *                    @arg RTC_FORMAT_BCD : format in BCD
 *
 * @param     alarm: specifies the format to write
 *                   This parameter can be one of the following values:
 *                   @arg RTC_ALARM_A : to select Alarm A
 *                   @arg RTC_ALARM_B : to select Alarm B
 *
 * @param     alarmConfig: Pointer to a RTC_AlarmConfig_T structure that contains
 *                         the configuration ALRMA information for the RTC peripheral
 *
 * @retval    None
 */
void RTC_ReadAlarm(RTC_FORMAT_T format, RTC_ALARM_T alarm, RTC_AlarmConfig_T* alarmConfig)
{
    uint8_t day_d,day_u,hours_d,hours_u,minutes_d,minutes_u,seconds_d,seconds_u;
    uint32_t day_mask,hours_mask,minutes_mask,seconds_mask;

    if (alarm == RTC_ALARM_A)
    {
        day_d = RTC->ALRMA_B.DAYT << 0x04;
        day_u = RTC->ALRMA_B.DAYU;
        hours_d = RTC->ALRMA_B.HRT << 0x04;
        hours_u = RTC->ALRMA_B.HRU;
        minutes_d = RTC->ALRMA_B.MINT << 0x04;
        minutes_u = RTC->ALRMA_B.MINU;
        seconds_d = RTC->ALRMA_B.SECT << 0x04;
        seconds_u = RTC->ALRMA_B.SECU;

        day_mask = RTC->ALRMA_B.DATEMEN<<8;
        hours_mask = RTC->ALRMA_B.HRMEN<<8;
        minutes_mask = RTC->ALRMA_B.MINMEN<<8;
        seconds_mask = RTC->ALRMA_B.SECMEN<<7;

        alarmConfig->time.hours   = (uint8_t)(hours_d | hours_u);
        alarmConfig->time.minutes = (uint8_t)(minutes_d | minutes_u);
        alarmConfig->time.seconds = (uint8_t)(seconds_d | seconds_u);
        alarmConfig->time.h12     = (RTC_H12_T)(RTC->ALRMA_B.TIMEFCFG);
        alarmConfig->alarmDateWeekDay = (uint8_t)(day_d | day_u);
        alarmConfig->alarmDateWeekDaySel = (RTC_WEEKDAY_SEL_T)(RTC->ALRMA_B.WEEKSEL);
        alarmConfig->alarmMask = (uint32_t)(day_mask | hours_mask | minutes_mask | seconds_mask);
    }
    else
    {
        day_d = RTC->ALRMB_B.DAYT << 0x04;
        day_u = RTC->ALRMB_B.DAYU;
        hours_d = RTC->ALRMB_B.HRT << 0x04;
        hours_u = RTC->ALRMB_B.HRU;
        minutes_d = RTC->ALRMB_B.MINT << 0x04;
        minutes_u = RTC->ALRMB_B.MINU;
        seconds_d = RTC->ALRMB_B.SECT << 0x04;
        seconds_u = RTC->ALRMB_B.SECU;

        day_mask = RTC->ALRMB_B.DATEMEN<<8;
        hours_mask = RTC->ALRMB_B.HRMEN<<8;
        minutes_mask = RTC->ALRMB_B.MINMEN<<8;
        seconds_mask = RTC->ALRMB_B.SECMEN<<7;

        alarmConfig->time.hours   = (uint8_t)(hours_d | hours_u);
        alarmConfig->time.minutes = (uint8_t)(minutes_d | minutes_u);
        alarmConfig->time.seconds = (uint8_t)(seconds_d | seconds_u);
        alarmConfig->time.h12     = (RTC_H12_T)(RTC->ALRMB_B.TIMEFCFG);
        alarmConfig->alarmDateWeekDay = (uint8_t)(day_d | day_u);
        alarmConfig->alarmDateWeekDaySel = (RTC_WEEKDAY_SEL_T)(RTC->ALRMB_B.WEEKSEL);
        alarmConfig->alarmMask = (uint32_t)(day_mask | hours_mask | minutes_mask | seconds_mask);
    }

    if (format == RTC_FORMAT_BIN)
    {
        alarmConfig->time.hours = (uint8_t)RTC_Bcd2ConByte(alarmConfig->time.hours);
        alarmConfig->time.minutes = (uint8_t)RTC_Bcd2ConByte(alarmConfig->time.minutes);
        alarmConfig->time.seconds = (uint8_t)RTC_Bcd2ConByte(alarmConfig->time.seconds);
        alarmConfig->alarmDateWeekDay = (uint8_t)RTC_Bcd2ConByte(alarmConfig->alarmDateWeekDay);
    }
}

/*!
 * @brief     Enable the RTC Alarm A.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableAlarmA(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.ALRAEN = BIT_SET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disable the the RTC Alarm A.
 *
 * @param     None
 *
 * @retval    None
 */
uint8_t RTC_DisableAlarmA(void)
{
    __IO uint32_t timeout = 0x00;

    RTC_DisableWriteProtection();
    RTC->CTRL_B.ALRAEN = BIT_RESET;

    /* wait for Alarm A write flag */
    while (((RTC->STS_B.ALRAWFLG) != BIT_SET) && (timeout != RTC_TIMEOUT_ALARM))
    {
        timeout++;
    }

    if ((RTC->STS_B.ALRAWFLG) == BIT_RESET)
    {
        RTC_EnableWriteProtection();
        return ERROR;
    }
    else
    {
        RTC_EnableWriteProtection();
        return SUCCESS;
    }
}

/*!
 * @brief     Enable the RTC Alarm B.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableAlarmB(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.ALRBEN = BIT_SET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disable the the RTC Alarm B.
 *
 * @param     None
 *
 * @retval    None
 */
uint8_t RTC_DisableAlarmB(void)
{
    __IO uint32_t timeout = 0x00;

    RTC_DisableWriteProtection();
    RTC->CTRL_B.ALRBEN = BIT_RESET;

    /* wait for Alarm B write flag */
    while (((RTC->STS_B.ALRBWFLG) != BIT_SET) && (timeout != RTC_TIMEOUT_ALARM))
    {
        timeout++;
    }

    if ((RTC->STS_B.ALRBWFLG) == BIT_RESET)
    {
        RTC_EnableWriteProtection();
        return ERROR;
    }
    else
    {
        RTC_EnableWriteProtection();
        return SUCCESS;
    }
}

/*!
 * @brief     Read the RTC ALRMA Subseconds value
 *
 * @param     val: specifies the value for ALRMA Sub Second
 *                 this value must less than 0x00007FFF
 *
 * @param     format: specifies the format to write
 *                    This parameter can be one of the following values:
 *                    @arg RTC_ALARM_A : to select Alarm A
 *                    @arg RTC_ALARM_B : to select Alarm B
 *
 * @param     mask: specifies the mask for ALRMA Sub Second.
 *                  This parameter can be one of the following values:
 *                  @arg RTC_ALARM_SUBSEC_MASK_ALL   : All Alarm SUBSEC fields are masked.
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_1  : Mask SUBSEC[14:1]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_2  : Mask SUBSEC[14:2]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_3  : Mask SUBSEC[14:3]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_4  : Mask SUBSEC[14:4]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_5  : Mask SUBSEC[14:5]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_6  : Mask SUBSEC[14:6]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_7  : Mask SUBSEC[14:7]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_8  : Mask SUBSEC[14:8]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_9  : Mask SUBSEC[14:9]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_10 : Mask SUBSEC[14:10]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_11 : Mask SUBSEC[14:11]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_12 : Mask SUBSEC[14:12]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14_13 : Mask SUBSEC[14:13]
 *                  @arg RTC_ALARM_SUBSEC_MASK_14    : Mask SUBSEC[14]
 *                  @arg RTC_ALARM_SUBSEC_MASK_NONE  : Alarm comparison is all the SUBSEC bit.
 *
 *                  this value must less than 0x0f
 *
 * @retval    None
 */
void RTC_ConfigAlarmSubSecond(RTC_ALARM_T alarm, uint32_t val, RTC_ALARM_SUBSEC_MASK_T mask)
{
    RTC_DisableWriteProtection();

    if (alarm == RTC_ALARM_A)
    {
        RTC->ALRMASS_B.SUBSEC  = val;
        RTC->ALRMASS_B.MASKSEL = mask;
    }
    else
    {
        RTC->ALRMBSS_B.SUBSEC  = val;
        RTC->ALRMBSS_B.MASKSEL = mask;
    }

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Read the RTC Alarm Subseconds value
 *
 * @param     format: specifies the format to write
 *                    This parameter can be one of the following values:
 *                    @arg RTC_ALARM_A : select Alarm A
 *                    @arg RTC_ALARM_B : select Alarm B
 *
 * @retval    RTC ALRM Subseconds value
 */
uint16_t RTC_ReadAlarmSubSecond(RTC_ALARM_T alarm)
{
    if (alarm == RTC_ALARM_A)
    {
        return (uint16_t)(RTC->ALRMASS_B.SUBSEC);
    }
    else
    {
        return (uint16_t)(RTC->ALRMBSS_B.SUBSEC);
    }
}

/*!
 * @brief     Configure the RTC Wakeup clock source.
 *
 * @param     wakeUpClock: specifies the Wakeup Clock source.
 *                         This parameter can be one of the following values:
 *                         @arg RTC_WAKEUP_CLOCK_RTC_DIV16   : Wakeup Clock Select to RTC/16
 *                         @arg RTC_WAKEUP_CLOCK_RTC_DIV8    : Wakeup Clock Select to RTC/8
 *                         @arg RTC_WAKEUP_CLOCK_RTC_DIV4    : Wakeup Clock Select to RTC/4
 *                         @arg RTC_WAKEUP_CLOCK_RTC_DIV2    : Wakeup Clock Select to RTC/2
 *                         @arg RTC_WAKEUP_CLOCK_CK_SPRE_16B : Wakeup Clock Select to clk_spre
 *                         @arg RTC_WAKEUP_CLOCK_CK_SPRE_17B : Wakeup Clock Select to clk_spre
 *
 * @retval    None
 */
void RTC_ConfigWakeUpClock(RTC_WAKEUP_CLOCK_T wakeUpClock)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.WUCLKSEL = wakeUpClock;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Configure the RTC Wakeup counter value.
 *
 * @param     wakeUpValue: a 16-bit Wakeup auto-reload value.
 *
 * @retval    None
 */
void RTC_ConfigWakeUpValue(uint16_t wakeUpValue)
{
    RTC_DisableWriteProtection();

    RTC->AUTORLD = (uint32_t)wakeUpValue;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Read the RTC Wakeup auto-reload value.
 *
 * @param     None
 *
 * @retval    The RTC WakeUp auto-reload value.
 */
uint16_t RTC_ReadWakeUpValue(void)
{
    return (uint16_t)RTC->AUTORLD;
}

/*!
 * @brief     Enable the RTC WakeUp timer.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableWakeUp(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.WUTEN = BIT_SET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disable the RTC WakeUp timer.
 *
 * @param     None
 *
 * @retval    None
 */
uint8_t RTC_DisableWakeUp(void)
{
    __IO uint32_t timeout = 0x00;
    RTC_DisableWriteProtection();

    RTC->CTRL_B.WUTEN = BIT_RESET;

    /* wait for wakeup timer write flag */
    while (((RTC->STS_B.WUTWFLG) == BIT_RESET) && (timeout != RTC_TIMEOUT_WAKE_UP))
    {
        timeout++;
    }

    if ((RTC->STS_B.WUTWFLG) == BIT_RESET)
    {
        RTC_EnableWriteProtection();
        return ERROR;
    }
    else
    {
        RTC_EnableWriteProtection();
        return SUCCESS;
    }
}

/*!
 * @brief     Adds or substract one hour from the current time
 *
 * @param     saving: specifies the DayLight Saving.
 *                 This parameter can be one of the following values:
 *                 @arg RTC_DLS_SUB_1H : Winter time change
 *                 @arg RTC_DLS_ADD_1H : Summer time change
 *
 * @param     bit: set the Backup Value.
 *                 This parameter can be one of the following values:
 *                 @arg RTC_BACKUP_RESET : Reset backup value
 *                 @arg RTC_BACKUP_SET   : Set backup value
 *
 * @retval    None
 */
void RTC_ConfigDayLightSaving(RTC_DLS_T saving, RTC_BACKUP_T bit)
{
    RTC_DisableWriteProtection();

    if (saving == RTC_DLS_ADD_1H)
    {
        RTC->CTRL_B.STCCFG = BIT_SET;
    }
    else
    {
        RTC->CTRL_B.WTCCFG = BIT_SET;
    }

    /* Backup Value Setup */
    RTC->CTRL_B.BAKP = bit;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Returns the RTC Day Light Saving stored operation
 *
 * @param     None
 *
 * @retval    RTC Day Light Saving backup stored operation
 */
uint8_t RTC_ReadStoreOperation(void)
{
    return (uint8_t)RTC->CTRL_B.BAKP;
}

/*!
 * @brief     Config the RTC alarm Output Way and output polarity.
 *
 * @param     outputSel: specifies RTC alarm Output Way.
 *                       This parameter can be one of the following values:
 *                       @arg RTC_OUT_SEL_DISABLE : Disable RTC output
 *                       @arg RTC_OUT_SEL_ALARM_A : Select alarm A as RTC output
 *                       @arg RTC_OUT_SEL_ALARM_B : Select alarm B as RTC output
 *                       @arg RTC_OUT_SEL_WAKEUP: : Select wake up as RTC output
 *
 * @param     polarity: specified the output polarity.
 *                      This parameter can be one of the following values:
 *                      @arg RTC_OUT_POLARITY_HIGH : The output polarity is high
 *                      @arg RTC_OUT_POLARITY_LOW  : The output polarity is low
 *
 * @retval    None
 */
void RTC_ConfigOutput(RTC_OUT_SEL_T outputSel, RTC_OUT_POLARITY_T polarity)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.OUTSEL = outputSel;
    RTC->CTRL_B.POLCFG = polarity;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Config RTC Coarse calibration.
 *
 * @param     calibSign: specifies the sign of the coarse calibration value.
 *                       This parameter can be  one of the following values:
 *                       @arg RTC_CALIB_SIGN_POSITIVE : The Calibration sign is positive
 *                       @arg RTC_CALIB_SIGN_NEGATIVE : The Calibration sign is negative
 *
 * @param     value: a 5-bit value of coarse calibration expressed in ppm.
 *
 * @note      For positive sign, the Calibration value could be between 0 and 126
 *            with a 4-ppm step.
 *
 * @note      For negative sign, the Calibration value could be between 0 and 63
 *            with a 2-ppm step.
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_ConfigCoarseCalib(RTC_CALIB_SIGN_T calibSign, uint32_t value)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();
        return ERROR;
    }
    else
    {
        RTC->DCAL_B.DCALCFG = calibSign;
        RTC->DCAL_B.DCAL    = value;

        RTC_DisableInit();
        RTC_EnableWriteProtection();

        return SUCCESS;
    }
}

/*!
 * @brief     Enables the Coarse calibration.
 *
 * @param     None
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_EnableCoarseCalib(void)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();

        return ERROR;
    }
    else
    {
        RTC->CTRL_B.DCALEN = BIT_SET;

        RTC_DisableInit();
        RTC_EnableWriteProtection();

        return SUCCESS;
    }
}

/*!
 * @brief     Disables the Coarse calibration.
 *
 * @param     None
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_DisableCoarseCalib(void)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();

        return ERROR;
    }
    else
    {
        RTC->CTRL_B.DCALEN = BIT_RESET;

        RTC_DisableInit();
        RTC_EnableWriteProtection();

        return SUCCESS;
    }
}

/*!
 * @brief     Enable the RTC clock Calibration Output.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableCalibOutput(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.CALOEN = BIT_SET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disable the RTC clock Calibration Output.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableCalibOutput(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.CALOEN = BIT_RESET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Config the Calibration output.
 *
 * @param     calib: Select the Calibration output.
 *                   This parameter can be one of the following values:
 *                   @arg RTC_CALIB_OUTPUT_512HZ : Calibration output is 512 Hz
 *                   @arg RTC_CALIB_OUTPUT_1HZ   : Calibration output is 1 Hz
 *
 * @retval    None
 */
void RTC_ConfigCalibOutput(RTC_CALIB_OUTPUT_T calib)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.CALOSEL = calib;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Config the Synchronization Shift Control Settings.
 *
 * @param     period: Select the Smooth Calibration period.
 *                    This parameter can be can be one of the following values:
 *                    @arg RTC_SCP_32SEC : The smooth calibration periode is 32s.
 *                    @arg RTC_SCP_16SEC : The smooth calibration periode is 16s.
 *                    @arg RTC_SCP_8SEC  : The smooth calibartion periode is 8s.
 *
 * @param     calibPulse: Select to Set or reset the CALP bit.
 *                        This parameter can be one of the following values:
 *                        @arg RTC_SCPP_RESET : Add one RTCCLK puls every 2**11 pulses.
 *                        @arg RTC_SCPP_SET   : No RTCCLK pulses are added.
 *
 * @param     value: a 9-bits value to Config RECALF[8:0].
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_ConfigSmoothCalib(RTC_SCP_T period, RTC_SCPP_T calibPulse, uint16_t value)
{
    uint8_t state = ERROR;
    uint32_t timeout = 0;

    RTC_DisableWriteProtection();

    /* wait for Recalibration flag to be cleared */
    while ((RTC->STS_B.RCALPFLG != BIT_RESET) && (timeout != RTC_TIMEOUT_CALIB))
    {
        timeout++;
    }

    if (RTC->STS_B.RCALPFLG != BIT_SET)
    {
        RTC->CAL = ((uint32_t)calibPulse << 15) | ((uint32_t)period << 13) |
                   (uint32_t)(value & 0x01FF);

        state = SUCCESS;
    }
    else
    {
        state = ERROR;
    }

    RTC_EnableWriteProtection();

    return state;
}

/*!
 * @brief     Enables the RTC TimeStamp functionality and config the Timestamp event
 *            active edge.
 *
 * @param     edge: Specifies the Timestamp event active edge.
 *                  This paramete can be one of the following:
 *                  @arg RTC_TIMESTAMP_EDGE_RISING  : Rising edge generates a timestamp event.
 *                  @arg RTC_TIMESTAMP_EDGE_FALLING : Falling edge generates a timestamp event
 *
 * @retval    None
 */
void RTC_EnableTimeStamp(RTC_TIMESTAMP_EDGE_T edge)
{
    RTC_DisableWriteProtection();

    /* Disable Timestamp when change the edge */
    RTC->CTRL_B.TSEN = BIT_RESET;

    RTC->CTRL_B.TSETECFG = edge;
    RTC->CTRL_B.TSEN = BIT_SET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disables the RTC TimeStamp functionality.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableTimeStamp(void)
{
    RTC_DisableWriteProtection();

    RTC->CTRL_B.TSEN = BIT_RESET;

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Read the RTC TimeStamp value and masks
 *
 * @param     format: specifies the format of the output parameters.
 *                    This parameter can be one of the following values:
 *                    @arg RTC_FORMAT_BIN : data in Binary format
 *                    @arg RTC_FORMAT_BCD : data in BCD format
 *
 * @param     time: pointer to a RTC_TimeConfig_T structure that will
 *                  contains the TimeStamp time values.
 *
 * @param     date: pointer to a RTC_DateConfig_T structure that will
 *                  contains the TimeStamp date values.
 *
 * @retval    None
 */
void RTC_ReadTimeDate(RTC_FORMAT_T format, RTC_TimeConfig_T* time, RTC_DateConfig_T* date)
{
    uint32_t temptime = 0, tempdate = 0;
    temptime = (uint32_t)((RTC->TSTIME) & 0x007F7F7F);
    tempdate = (uint32_t)((RTC->TSDATE) & 0x00FFFF3F);

    /* Read the time in BCD format */
    time->hours   = (uint8_t)((temptime & 0x003F0000 ) >> 16);
    time->minutes = (uint8_t)((temptime & 0x00007F00) >>8);
    time->seconds = (uint8_t)(temptime &  0x0000007F);
    time->h12 = (RTC_H12_T)((temptime & 0x00400000) >> 22);

    /* Read the date in BCD format */
    date->year  =  0;
    date->month = (RTC_MONTH_T)((tempdate & 0x00001F00) >>8);
    date->date  = (uint8_t)(tempdate &  0x0000003F);
    date->weekday =(RTC_WEEKDAY_T)((tempdate & 0x0000E000) >> 13);

    /* Binary format */
    if (format == RTC_FORMAT_BIN)
    {
        time->hours   = (uint8_t)RTC_Bcd2ConByte(time->hours);
        time->minutes = (uint8_t)RTC_Bcd2ConByte(time->minutes);
        time->seconds = (uint8_t)RTC_Bcd2ConByte(time->seconds);

        date->month = (RTC_MONTH_T)RTC_Bcd2ConByte(date->month);
        date->date  = (uint8_t)RTC_Bcd2ConByte(date->date);
        date->weekday = (RTC_WEEKDAY_T)(date->weekday);
    }
}

/*!
 * @brief     Get the RTC timestamp Subseconds value
 *
 * @param     None
 *
 * @retval    RTC current timestamp Subseconds value
 */
uint16_t RTC_ReadTimeStampSubSecond(void)
{
    return RTC->TSSUBSEC_B.SUBSEC;
}

/*!
 * @brief     Config the select Tamper pin edge
 *
 * @param     tamper:  Selected tamper pin.
 *                     This parameter can be one of the following values:
 *                     @arg RTC_TAMPER_1 : Select Tamper 1.
 *                     @arg RTC_TAMPER_2 : Select Tamper 2.
 *
 * @param     trigger: Specifies the trigger on the tamper pin that stimulates tamper event.
 *                     This parameter can be one of the following values:
 *                     @arg RTC_TAMPER_TRIGGER_EDGE_RISING  : Rising Edge of the tamper pin causes tamper event.
 *                     @arg RTC_TAMPER_TRIGGER_EDGE_FALLING : Falling Edge of the tamper pin causes tamper event.
 *                     @arg RTC_TAMPER_TRIGGER_LEVEL_LOW    : Low Level of the tamper pin causes tamper event.
 *                     @arg RTC_TAMPER_TRIGGER_LEVEL_HIGH   : High Level of the tamper pin causes tamper event.
 *
 * @retval    None
 */
void RTC_ConfigTamperTrigger(RTC_TAMPER_T tamper, RTC_TAMPER_TRIGGER_T trigger)
{
    if (tamper == RTC_TAMPER_1)
    {
        RTC->TACFG_B.TP1ALCFG = trigger;
    }
    else
    {
        RTC->TACFG_B.TP2ALCFG = trigger;
    }
}

/*!
 * @brief     Enables the Tamper detection
 *
 * @param     tamper: Selected tamper pin.
 *                    This parameter can be one of the following values:
 *                    @arg RTC_TAMPER_1 : Select Tamper 1.
 *                    @arg RTC_TAMPER_2 : Select Tamper 2.
 *
 * @retval    None
 */
void RTC_EnableTamper(RTC_TAMPER_T tamper)
{
    if (tamper == RTC_TAMPER_1)
    {
        RTC->TACFG_B.TP1EN = BIT_SET;
    }
    else
    {
        RTC->TACFG_B.TP2EN = BIT_SET;
    }
}

/*!
 * @brief     Disables the Tamper detection
 *
 * @param     tamper: Selected tamper pin.
 *                    This parameter can be any combination of the following values:
 *                    @arg RTC_TAMPER_1 : Select Tamper 1.
 *                    @arg RTC_TAMPER_2 : Select Tamper 2.
 *
 * @retval    None
 */
void RTC_DisableTamper(RTC_TAMPER_T tamper)
{
    if (tamper == RTC_TAMPER_1)
    {
        RTC->TACFG_B.TP1EN = BIT_RESET;
    }
    else
    {
        RTC->TACFG_B.TP2EN = BIT_RESET;
    }
}

/*!
 * @brief     Config the Tampers Filter
 *
 * @param    filter: Specifies the tampers filter.
 *                   This parameter can be one of the following values:
 *                   @arg RTC_TAMPER_FILTER_DISABLE : Tamper filter is disabled.
 *                   @arg RTC_TAMPER_FILTER_2SAMPLE : Tamper is activated after 2 consecutive samples at the active level
 *                   @arg RTC_TAMPER_FILTER_4SAMPLE : Tamper is activated after 4 consecutive samples at the active level
 *                   @arg RTC_TAMPER_FILTER_8SAMPLE : Tamper is activated after 8 consecutive samples at the active level
 *
 * @retval    None
 */
void RTC_ConfigFilter(RTC_TAMPER_FILTER_T filter)
{
    RTC->TACFG_B.TPFCSEL = filter;

}

/*!
 * @brief     Config the Tampers Sampling Frequency
 *
 * @param     freq: Specifies the tampers Sampling Frequency.
 *                  This parameter can be one of the following values:
 *                  @arg RTC_TSF_DIV_32768 : Tampers Sampling Frequency = RTC_CLK/32768
 *                  @arg RTC_TSF_DIV_16384 : Tampers Sampling Frequency = RTC_CLK/16384
 *                  @arg RTC_TSF_DIV_8192  : Tampers Sampling Frequency = RTC_CLK/8192
 *                  @arg RTC_TSF_DIV_4096  : Tampers Sampling Frequency = RTC_CLK/4096
 *                  @arg RTC_TSF_DIV_2048  : Tampers Sampling Frequency = RTC_CLK/2048
 *                  @arg RTC_TSF_DIV_1024  : Tampers Sampling Frequency = RTC_CLK/1024
 *                  @arg RTC_TSF_DIV_512   : Tampers Sampling Frequency = RTC_CLK/512
 *                  @arg RTC_TSF_DIV_256   : Tampers Sampling Frequency = RTC_CLK/256
 *
 * @retval    None
 */
void RTC_ConfigSamplingFreq(RTC_TSF_DIV_T freq)
{
    RTC->TACFG_B.TPSFSEL = freq;
}

/*!
 * @brief     Config the Precharge Duration.
 *
 * @param     duration: Specifies the Tampers Pins input  Precharge Duration.
 *                  This parameter can be one of the following values:
 *                  @arg RTC_TPD_RTCCLK_1 : Tamper pins are pre-charged before sampling during 1 RTCCLK cycle.
 *                  @arg RTC_TPD_RTCCLK_2 : Tamper pins are pre-charged before sampling during 2 RTCCLK cycle.
 *                  @arg RTC_TPD_RTCCLK_4 : Tamper pins are pre-charged before sampling during 4 RTCCLK cycle.
 *                  @arg RTC_TPD_RTCCLK_8 : Tamper pins are pre-charged before sampling during 8 RTCCLK cycle.
 *
 * @retval    None
 */
void RTC_PinsPrechargeDuration(RTC_TPD_RTCCLK_T duration)
{
    RTC->TACFG_B.TPPRDUSEL = duration;
}

/*!
 * @brief     Enables the TimeStamp on Tamper Detection Event
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableTDE(void)
{
    RTC->TACFG_B.TPTSEN = BIT_SET;
}

/*!
 * @brief     Disable the TimeStamp on Tamper Detection Event
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableTDE(void)
{
    RTC->TACFG_B.TPTSEN = BIT_RESET;
}

/*!
 * @brief     Enable pull-up resistors to precharge of the selected Tamper pin.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnablePullUp(void)
{
    /* Enable precharge */
    RTC->TACFG_B.TPPUDIS = BIT_RESET;
}

/*!
 * @brief     Disable pull-up resistors to precharge of the selected Tamper pin.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisablePullUp(void)
{
    /* Disable precharge */
    RTC->TACFG_B.TPPUDIS = BIT_SET;
}

/*!
 * @brief     Writes a data in RTC Backup data.
 *
 * @param     backup: RTC Backup data Register number.
 *                    This parameter can be RTC_BAKP_REG_x where x can be from 0 to 19.
 *
 * @param     data: Data to be written in the specified RTC Backup data register.
 *
 * @retval    None
 */
void RTC_WriteBackup(RTC_BAKP_REG_T backupReg, uint32_t data)
{
    RTC->BAKP[backupReg] = (uint32_t)data;
}

/*!
 * @brief     Reads a data in RTC Backup data.
 *
 * @param     backup: RTC Backup data Register number.
 *                    This parameter can be RTC_BAKP_REG_x where x can be from 0 to 19.
 *
 * @retval    None
 */
uint32_t RTC_ReadBackup(RTC_BAKP_REG_T backupReg)
{
    return RTC->BAKP[backupReg];
}

/*!
 * @brief     Config Tamper Pin.
 *
 * @param     tamperPin: specifies the RTC Tamper Pin.
 *                       This parameter can be one of the following values:
 *                       @arg RTC_TAMPER_PIN_AF1 : RTC_AF1(PC13) is used as RTC Tamper Pin.
 *                       @arg RTC_TAMPER_PIN_AF2 : RTC_AF2(PI8) is used as RTC Tamper Pin.
 *
 * @retval    None
 */
void RTC_ConfigTamperPin(RTC_TAMPER_PIN_T tamperPin)
{
    RTC->TACFG_B.TP1MSEL = tamperPin;
}

/*!
 * @brief     Config the RTC TimeStamp Pin.
 *
 * @param     timeStampPin: specifies the RTC TimeStamp Pin.
 *                          This parameter can be one of the following values:
 *                          @arg RTC_TIMESTAMP_PIN_AF1 : RTC_AF1(PC13) is used as RTC TimeStamp Pin.
 *                          @arg RTC_TIMESTAMP_PIN_AF2 : RTC_AF2(PI8) is used as RTC TimeStamp Pin.
 *
 * @retval    None
 */
void RTC_ConfigTimeStampPin(RTC_TIMESTAMP_PIN_T timeStampPin)
{
    RTC->TACFG_B.TSMSEL = timeStampPin;
}

/*!
 * @brief     Config the RTC Output Pin mode
 *
 * @param     outputType: specifies the RTC Output (PC13) pin mode.
 *                        This parameter can be one of the following values:
 *                        @arg RTC_OUTPUT_OD : RTC_ALARM(PC13) output Open-drain
 *                        @arg RTC_OUTPUT_PP : RTC_ALARM(PC13) output Push-pull
 *
 * @retval    None
 */
void RTC_ConfigOutputType(RTC_OUTPUT_T outputType)
{
    RTC->TACFG_B.ALRMOT = outputType;
}

/*!
 * @brief     Config the Synchronization Shift Control Settings.
 *
 * @param     add1S:  Select to add or not 1 second to the time Calendar.
 *                    This parameter can be one of the following values :
 *                    @arg RTC_SHIFT_ADD1S_RESET: No effect.
 *                    @arg RTC_SHIFT_ADD1S_SET  : Add one second to the clock calendar.
 *
 * @param     subFS:  Select the number of Second Fractions to Substitute.
 *                    This parameter can be one any value from 0 to 0x7FFF.
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t RTC_ConfigSynchroShift(RTC_SHIFT_ADD1S_T add1S, uint16_t subFS)
{
    uint32_t timeout = 0;

    RTC_DisableWriteProtection();

    /* wait for Shift operation flag to be cleared */
    while ((RTC->STS_B.SOPFLG != BIT_RESET) && (timeout != RTC_TIMEOUT_SHIFT))
    {
        timeout++;
    }

    /* check if Shift Operation flag is cleared and Reference Clock Detection is disabled */
    if ((RTC->STS_B.SOPFLG != BIT_SET) && (RTC->CTRL_B.RCLKDEN != BIT_SET))
    {
        RTC->SHIFT = ((uint32_t)add1S << 31) | (uint32_t)subFS;

        if (RTC_WaitForSynchro() != ERROR)
        {
            RTC_EnableWriteProtection();

            return SUCCESS;
        }
    }

    RTC_EnableWriteProtection();

    return ERROR;
}

/*!
 * @brief     Enable RTC interrupts.
 *
 * @param     interrupt: specifies the RTC interrupt sources to be enabled
 *                     This parameter can be any combination of the following values:
 *                      @arg RTC_INT_ALRA : Enable ALRMA A interrupt
 *                      @arg RTC_INT_ALRB : Enable ALRMA B interrupt
 *                      @arg RTC_INT_WT   : Enable WakeUp Timer interrupt
 *                      @arg RTC_INT_TS   : Enable Time Stamp interrupt
 *                      @arg RTC_INT_TAMP : Enable Tamper event interrupt
 *
 * @retval    None
 */
void RTC_EnableInterrupt(uint32_t interrupt)
{
    RTC_DisableWriteProtection();

    RTC->CTRL |= (uint32_t)(interrupt & ~RTC_INT_TAMP);
    RTC->TACFG |= (uint32_t)(interrupt & RTC_INT_TAMP);

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disable RTC interrupts.
 *
 * @param     interrupt: specifies the RTC interrupt sources to be disable
 *                       This parameter can be any combination of the following values:
 *                        @arg RTC_INT_ALRA : Disable ALRMA A interrupt
 *                        @arg RTC_INT_ALRB : Disable ALRMA B interrupt
 *                        @arg RTC_INT_WT   : Disable WakeUp Timer interrupt
 *                        @arg RTC_INT_TS   : Disable Time Stamp interrupt
 *                        @arg RTC_INT_TAMP : Disable Tamper event interrupt
 *
 * @retval    None
 */
void RTC_DisableInterrupt(uint32_t interrupt)
{
    RTC_DisableWriteProtection();

    RTC->CTRL &= (uint32_t)~(interrupt & ~RTC_INT_TAMP);
    RTC->TACFG &= (uint32_t)~(interrupt & RTC_INT_TAMP);

    RTC_EnableWriteProtection();
}

/*!
 * @brief     Read the specified RTC flag.
 *
 * @param     flag: specifies the flag to check.
 *                  This parameter can be one of the following values:
 *                  @arg RTC_FLAG_AAWF : Alarm A Write Flag
 *                  @arg RTC_FLAG_ABWF : Alarm B Write Flag
 *                  @arg RTC_FLAG_WTWF : Wakeup Timer Write Flag
 *                  @arg RTC_FLAG_SOPF : Shift Operation Pending Flag
 *                  @arg RTC_FLAG_ISF  : Initialization State Flag
 *                  @arg RTC_FLAG_RSF  : Registers Synchronization Flag
 *                  @arg RTC_FLAG_INTF : Register Initialization Flag
 *                  @arg RTC_FLAG_ALRAF: Alarm A Match Flag
 *                  @arg RTC_FLAG_ALRBF: Alarm B Match Flag
 *                  @arg RTC_FLAG_WTF  : Wakeup Timer Flag
 *                  @arg RTC_FLAG_TSF  : Time Stamp Flag
 *                  @arg RTC_FLAG_TSOF : Time Stamp Overflow Flag
 *                  @arg RTC_FLAG_TP1F : Tamper 1 event Detection Flag
 *                  @arg RTC_FLAG_TP2F : Tamper 2 event Detection Flag
 *                  @arg RTC_FLAG_RPF  : Recalibration Pending Flag
 *
 * @retval    SET or RESET.
 */
uint8_t RTC_ReadStatusFlag(RTC_FLAG_T flag)
{
    return  (RTC->STS & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the RTC's status flags.
 * @param     flag: specifies the RTC flag to clear.
 *                  This parameter can be any combination of the following values:
 *                  @arg RTC_FLAG_RSF   : Registers Synchronization Flag
 *                  @arg RTC_FLAG_ALRAF : Alarm A Match Flag
 *                  @arg RTC_FLAG_ALRBF : Alarm B Match Flag
 *                  @arg RTC_FLAG_WTF   : Wakeup Timer Flag
 *                  @arg RTC_FLAG_TSF   : Time Stamp Flag
 *                  @arg RTC_FLAG_TSOF  : Time Stamp Overflow Flag
 *                  @arg RTC_FLAG_TP1F  : Tamper 1 event Detection Flag
 *                  @arg RTC_FLAG_TP2F  : Tamper 2 event Detection Flag
 */
void RTC_ClearStatusFlag(uint32_t flag)
{
    RTC->STS &= (uint32_t)~flag;
}

/*!
 * @brief     Read interrupt flag bit is set
 *
 * @param     flag: specifies the flag to read.
 *                  This parameter can be one of the following values:
 *                  @arg RTC_INT_FLAG_ALRA  : Alarm A interrupt
 *                  @arg RTC_INT_FLAG_ALRB  : Alarm B interrupt
 *                  @arg RTC_INT_FLAG_WT    : WakeUp Timer interrupt
 *                  @arg RTC_INT_FLAG_TS    : Time Stamp interrupt
 *                  @arg RTC_INT_FLAG_TAMP1 : Tamper1 event interrupt
 *                  @arg RTC_INT_FLAG_TAMP2 : Tamper2 event interrupt
 *
 * @retval    The new state of flag (SET or RESET).
 */
uint8_t RTC_ReadIntFlag(RTC_INT_FLAG_T flag)
{
    uint8_t intEnable;
    uint32_t intStatus;

    if (flag & 0x01)
    {
        intEnable = RTC->TACFG_B.TPIEN;
        intStatus = (uint32_t)(RTC->STS & (flag >> 4));
    }
    else
    {
        intEnable = (RTC->CTRL & flag) ? SET : RESET;
        intStatus = (uint32_t)(RTC->STS & (flag >> 4));
    }

    if (intEnable && intStatus)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief     Clear RTC interrupt flag bit
 *
 * @param     flag: specifies the flag to clear.
 *                  This parameter can be any combination the following values:
 *                  @arg RTC_INT_FLAG_ALRA  : ALRMA interrupt
 *                  @arg RTC_INT_FLAG_ALRB  : ALRMB interrupt
 *                  @arg RTC_INT_FLAG_TS    : Time Stamp interrupt
 *                  @arg RTC_INT_FLAG_WT    : WakeUp Timer interrupt
 *                  @arg RTC_INT_FLAG_TAMP1 : Tamper1 event interrupt
 *                  @arg RTC_INT_FLAG_TAMP2 : Tamper2 event interrupt
 *
 * @retval    SET or RESET
 */
void RTC_ClearIntFlag(uint32_t flag)
{
    RTC->STS &= (uint32_t) ~(flag >> 4);
}

/*!
 * @brief     Converts a 2 digit decimal to BCD format
 *
 * @param     val: Byte to be converted
 *
 * @retval    Converted byte
 */
static uint8_t RTC_ByteConBcd2(uint8_t val)
{
    uint8_t bcdhigh = 0;

    while (val >= 10)
    {
        bcdhigh++;
        val -= 10;
    }

    return  ((uint8_t)(bcdhigh << 4) | val);
}

/*!
 * @brief     Convert from 2 digit BCD to Binary
 *
 * @param     val: BCD value to be converted
 *
 * @retval    Converted word
 */
static uint8_t RTC_Bcd2ConByte(uint8_t val)
{
    uint8_t tmp = 0;
    tmp = ((uint8_t)(val & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (val & (uint8_t)0x0F));
}

/**@} end of group RTC_Functions */
/**@} end of group RTC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
