/*!
 * @file        apm32f0xx_rtc.c
 *
 * @brief       This file provides firmware functions to manage the following
 *              functionalities of the Real-Time Clock (RTC) peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f0xx_rtc.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup RTC_Driver RTC Driver
  @{
*/

/** @defgroup RTC_Macros Macros
  @{
*/

/**@} end of group RTC_Macros */

/** @defgroup RRTC_Enumerations Enumerations
  @{
*/

/**@} end of group RTC_Macros */

/** @defgroup RTC_Structures Structures
  @{
*/

/**@} end of group RTC_Structures */

/** @defgroup RTC_Variables Variables
  @{
*/

/**@} end of group RTC_Variables */

/** @defgroup RTC_Functions Functions
  @{
*/

static uint8_t RTC_ByteConBcd2(uint8_t val);
static uint8_t RTC_Bcd2ConByte(uint8_t val);

/*!
 * @brief       Deinitializes the RTC registers to their default reset values
 *
 * @param       None
 *
 * @retval      SUCCESS or ERROR
 */
uint8_t RTC_Reset(void)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();
        return ERROR;
    }
    else
    {
        RTC->TIME     = (uint32_t)0x00000000;
        RTC->AUTORLD  = (uint32_t)0x0000FFFF;
        RTC->DATE     = (uint32_t)0x00002101;
        RTC->CTRL    &= (uint32_t)0x00000000;
        RTC->PSC      = (uint32_t)0x007F00FF;
        RTC->ALRMA    = (uint32_t)0x00000000;
        RTC->SHIFT    = (uint32_t)0x00000000;
        RTC->CAL      = (uint32_t)0x00000000;
        RTC->ALRMASS  = (uint32_t)0x00000000;

        RTC->STS = (uint32_t)0x00000007;
        RTC->TACFG = 0x00000000;

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

/*!
 * @brief       Deinitializes the RTC registers to their default reset values
 *
 * @param       Struct : pointer to a RTC_Config_T structure which will be initialized
 *
 * @retval      SUCCESS or ERROR
 */
uint8_t RTC_Config(RTC_Config_T* Struct)
{
    RTC_DisableWriteProtection();

    if (RTC_EnableInit() == ERROR)
    {
        RTC_EnableWriteProtection();
        return ERROR;
    }
    else
    {
        RTC->CTRL_B.TIMEFCFG  = (Struct->format);
        RTC->PSC_B.SPSC = (Struct->SynchPrediv);
        RTC->PSC_B.APSC = (Struct->AsynchPrediv);

        RTC_DisableInit();
        RTC_EnableWriteProtection();
        return SUCCESS;
    }
}

/*!
 * @brief       Fills each RTC_ConfigStruct member with its default value
 *
 * @param       Struct : pointer to a RTC_Config_T structure which will be initialized
 *
 * @retval      None
 */
void RTC_ConfigStructInit(RTC_Config_T* Struct)
{
    Struct->format = RTC_HourFormat_24;
    Struct->AsynchPrediv = (uint32_t)0x7F;
    Struct->SynchPrediv = (uint32_t)0xFF;
}

/*!
 * @brief       Enable the write protection for RTC registers
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_EnableWriteProtection(void)
{
    RTC->WRPROT = 0xFF;
}

/*!
 * @brief       Disable the write protection for RTC registers
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_DisableWriteProtection(void)
{
    RTC->WRPROT = 0xCA;
    RTC->WRPROT = 0x53;
}

/*!
 * @brief       Enable the RTC Initialization mode.
 *
 * @param       None
 *
 * @retval      SUCCESS or ERROR
 */
uint8_t RTC_EnableInit(void)
{
    __IO uint32_t cnt = 0x00;
    uint32_t initstatus = 0x00;

    if (RTC->STS_B.RINITFLG == BIT_RESET)
    {
        RTC->STS = (uint32_t)0xFFFFFFFF;

        do
        {
            initstatus = RTC->STS_B.RINITFLG;
            cnt++;
        }
        while ((cnt != RTC_INITMODE_TIMEOUT) && (initstatus == 0x00));

        if (RTC->STS_B.RINITFLG != BIT_RESET)
        {
            return SUCCESS;
        }
        else
        {
            return ERROR;
        }
    }
    else
    {
        return SUCCESS;
    }
}

/*!
 * @brief       Disable the RTC Initialization mode.
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_DisableInit(void)
{
    RTC->STS_B.INITEN = BIT_RESET;
}

/*!
 * @brief       Waits until the RTC Time and Date registers (RTC_TIME and RTC_DATA) are
 *              synchronized with RTC APB clock
 * @param       None
 *
 * @retval      SUCCESS or ERROR
 */
uint8_t RTC_WaitForSynchro(void)
{
    __IO uint32_t cnt = 0x00;
    uint32_t synchrostatus = 0x00;

    if (RTC->CTRL_B.RCMCFG == BIT_RESET)
    {
        return SUCCESS;
    }
    else
    {
        RTC_DisableWriteProtection();
        RTC->STS &= (uint32_t)0xFFFFFF5F;

        do
        {
            synchrostatus = RTC->STS_B.RSFLG;
            cnt++;
        }
        while ((cnt != RTC_SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));

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
}

/*!
 * @brief       Enables the RTC reference clock detection
 *
 * @param       None
 *
 * @retval      SUCCESS or ERROR
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
 * @brief       Disable the RTC reference clock detection
 *
 * @param       None
 *
 * @retval      SUCCESS or ERROR
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
 * @brief       Enable the RTC reference clock detection
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_EnableBypassShadow(void)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.RCMCFG = BIT_SET;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Disable the RTC reference clock detection
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_DisableBypassShadow(void)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.RCMCFG = BIT_RESET;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Config the RTC current time
 *
 * @param       format: specifies the format to write
 *                      This parameter can be one of the following values:
 *                      @arg RTC_FORMAT_BIN: format in Bin
 *                      @arg RTC_FORMAT_BCD: format in BCD
 *
 * @param       timeStruct:  Pointer to a RTC_TIME_T structure that
 *                          contains the configuration information for the RTC peripheral
 *
 * @retval      None
 */
uint8_t RTC_ConfigTime(RTC_FORMAT_T format, RTC_TIME_T* timeStruct)
{
    uint8_t state = ERROR;
    uint32_t temp = 0;

    if (format == RTC_FORMAT_BIN)
    {
        if (RTC->CTRL_B.TIMEFCFG == BIT_RESET)
        {
            timeStruct->H12 = RTC_H12_AM;
        }
    }
    else
    {
        if (RTC->CTRL_B.TIMEFCFG == BIT_RESET)
        {
            timeStruct->H12 = RTC_H12_AM;
        }
        else
        {
            temp = RTC_Bcd2ConByte(timeStruct->hours);
        }
    }

    if (format != RTC_FORMAT_BIN)
    {
        temp = (((uint32_t)(timeStruct->hours) << 16) | \
                ((uint32_t)(timeStruct->minutes) << 8) | \
                ((uint32_t)(timeStruct->seconds)) | \
                ((uint32_t)(timeStruct->H12) << 22));
    }
    else
    {
        temp = (((uint32_t)RTC_ByteConBcd2(timeStruct->hours) << 16) | \
                ((uint32_t)RTC_ByteConBcd2(timeStruct->minutes) << 8) | \
                ((uint32_t)RTC_ByteConBcd2(timeStruct->seconds)) | \
                ((uint32_t)(timeStruct->H12) << 22));
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
 * @brief       Fills each timeStruct member with its default value
 *
 * @param       timeStruct:  Pointer to a RTC_TIME_T structure that
 *                           contains the configuration information for the RTC peripheral
 *
 * @retval      None
 */
void RTC_ConfigTimeStructInit(RTC_TIME_T* timeStruct)
{
    /** ALRMA Time Settings : Time = 00h:00mn:00sec */
    timeStruct->hours = 0;
    timeStruct->minutes = 0;
    timeStruct->seconds = 0;
    timeStruct->H12 = RTC_H12_AM;
}

/*!
 * @brief       Read the RTC current Time
 *
 * @param       format: specifies the format to write
 *                      This parameter can be one of the following values:
 *                      @arg RTC_FORMAT_BIN: format in Bin
 *                      @arg RTC_FORMAT_BCD: format in BCD
 *
 * @param       timeStruct:  Pointer to a RTC_TIME_T structure that
 *                           contains the configuration information for the RTC peripheral
 *
 * @retval      None
 */
void RTC_ReadTime(RTC_FORMAT_T format, RTC_TIME_T* timeStruct)
{
    uint32_t temp = 0;
    temp = (uint32_t)((RTC->TIME) & 0x007F7F7F);

    timeStruct->hours   = (uint8_t)((temp & 0x003F0000) >> 16);
    timeStruct->minutes = (uint8_t)((temp & 0x00007F00) >> 8);
    timeStruct->seconds = (uint8_t)(temp &  0x0000007F);
    timeStruct->H12 = (uint8_t)((temp & 0x00400000) >> 22);

    if (format == RTC_FORMAT_BIN)
    {
        timeStruct->hours   = (uint8_t)RTC_Bcd2ConByte(timeStruct->hours);
        timeStruct->minutes = (uint8_t)RTC_Bcd2ConByte(timeStruct->minutes);
        timeStruct->seconds = (uint8_t)RTC_Bcd2ConByte(timeStruct->seconds);
    }
}

/*!
 * @brief       Read the RTC current Calendar Subseconds value
 *
 * @param       None
 *
 * @retval      RTC current Calendar Subseconds value
 */
uint32_t RTC_ReadSubSecond(void)
{
    uint32_t temp = 0;
    temp = (uint32_t)(RTC->SUBSEC);
    (void)(RTC->DATE);
    return (temp);
}

/*!
 * @brief       Config the RTC current time
 *
 * @param       format: specifies the format to write
 *                      This parameter can be one of the following values:
 *                      @arg RTC_FORMAT_BIN: format in Bin
 *                      @arg RTC_FORMAT_BCD: format in BCD
 *
 * @param       dateStruct:  Pointer to a RTC_DATE_T structure that
 *                           contains the configuration DATE information for the RTC peripheral
 *
 * @retval      None
 */
uint8_t RTC_ConfigDate(RTC_FORMAT_T format, RTC_DATE_T* dateStruct)
{
    uint8_t state = ERROR;
    uint32_t temp = 0;

    if (format != RTC_FORMAT_BIN)
    {
        temp = RTC_Bcd2ConByte(dateStruct->month);
        temp = RTC_Bcd2ConByte(dateStruct->date);
    }

    if (format != RTC_FORMAT_BIN)
    {
        temp = (((uint32_t)(dateStruct->year) << 16) | \
                ((uint32_t)(dateStruct->month) << 8) | \
                ((uint32_t)(dateStruct->date)) | \
                ((uint32_t)(dateStruct->weekday) << 13));
    }
    else
    {
        temp = (((uint32_t)RTC_ByteConBcd2(dateStruct->year) << 16) | \
                ((uint32_t)RTC_ByteConBcd2(dateStruct->month) << 8) | \
                ((uint32_t)RTC_ByteConBcd2(dateStruct->date)) | \
                ((uint32_t)(dateStruct->weekday) << 13));

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
 * @brief       Fills each dateStruct member with its default value
 *
 * @param       dateStruct:  Pointer to a RTC_DATE_T structure that
 *                           contains the configuration DATE information for the RTC peripheral
 * @retval      None
 */
void RTC_ConfigDateStructInit(RTC_DATE_T* dateStruct)
{
    dateStruct->weekday = RTC_WEEKDAY_MONDAY;
    dateStruct->month = RTC_MONTH_JANUARY;
    dateStruct->date = 1;
    dateStruct->year = 0;
}

/*!
 * @brief       the RTC current date
 *
 * @param       format: specifies the format to write
 *                      This parameter can be one of the following values:
 *                      @arg RTC_FORMAT_BIN: format in Bin
 *                      @arg RTC_FORMAT_BCD: format in BCD
 *
 * @param       dateStruct:  Pointer to a RTC_DATE_T structure that
 *                           contains the configuration DATE information for the RTC peripheral
 *
 * @retval      None
 */
void RTC_ReadDate(RTC_FORMAT_T format, RTC_DATE_T* dateStruct)
{
    uint32_t temp = 0;
    temp = (uint32_t)((RTC->DATE) & 0x00FFFF3F);

    dateStruct->year  = (uint8_t)((temp & 0x00FF0000) >> 16);
    dateStruct->month = (uint8_t)((temp & 0x00001F00) >> 8);
    dateStruct->date  = (uint8_t)(temp &  0x0000003F);
    dateStruct->weekday = (uint8_t)((temp & 0x0000E000) >> 13);

    if (format == RTC_FORMAT_BIN)
    {
        dateStruct->year  = (uint8_t)RTC_Bcd2ConByte(dateStruct->year);
        dateStruct->month = (uint8_t)RTC_Bcd2ConByte(dateStruct->month);
        dateStruct->date  = (uint8_t)RTC_Bcd2ConByte(dateStruct->date);
        dateStruct->weekday = (uint8_t)(dateStruct->weekday);
    }
}

/*!
 * @brief       Config the specified RTC ALRMA
 *
 * @param       format: specifies the format to write
 *                      This parameter can be one of the following values:
 *                      @arg RTC_FORMAT_BIN: format in Bin
 *                      @arg RTC_FORMAT_BCD: format in BCD
 *
 * @param       alarmStruct: Pointer to a RTC_ALARM_T structure that
 *                           contains the configuration ALRMA information for the RTC peripheral
 *
 * @retval      None
 */
void RTC_ConfigAlarm(RTC_FORMAT_T format, RTC_ALARM_T* alarmStruct)
{
    uint32_t temp = 0;

    if (format != RTC_FORMAT_BCD)
    {
        if (RTC->CTRL_B.TIMEFCFG == BIT_RESET)
        {
            alarmStruct->time.H12 = 0x00;
        }
    }
    else
    {
        if (RTC->CTRL_B.TIMEFCFG == BIT_RESET)
        {
            alarmStruct->time.H12 = 0x00;
        }
        else
        {
            temp = RTC_Bcd2ConByte(alarmStruct->time.hours);
        }

        if (alarmStruct->AlarmDateWeekDaySel == RTC_WEEKDAY_SEL_DATE)
        {
            temp = RTC_ByteConBcd2(alarmStruct->AlarmDateWeekDay);
        }
        else
        {
            temp = RTC_ByteConBcd2(alarmStruct->AlarmDateWeekDay);
        }
    }

    if (format == RTC_FORMAT_BCD)
    {
        temp = (((uint32_t)(alarmStruct->time.hours) << 16) | \
                ((uint32_t)(alarmStruct->time.minutes) << 8) | \
                ((uint32_t)alarmStruct->time.seconds) | \
                ((uint32_t)(alarmStruct->time.H12) << 22) | \
                ((uint32_t)(alarmStruct->AlarmDateWeekDay) << 24) | \
                ((uint32_t)alarmStruct->AlarmDateWeekDaySel << 30) | \
                ((uint32_t)alarmStruct->AlarmMask));
    }
    else
    {
        temp = (((uint32_t)RTC_ByteConBcd2(alarmStruct->time.hours) << 16) | \
                ((uint32_t)RTC_ByteConBcd2(alarmStruct->time.minutes) << 8) | \
                ((uint32_t)RTC_ByteConBcd2(alarmStruct->time.seconds)) | \
                ((uint32_t)(alarmStruct->time.H12) << 22) | \
                ((uint32_t)RTC_ByteConBcd2(alarmStruct->AlarmDateWeekDay) << 24) | \
                ((uint32_t)alarmStruct->AlarmDateWeekDaySel << 30) | \
                ((uint32_t)alarmStruct->AlarmMask));
    }

    RTC_DisableWriteProtection();
    RTC->ALRMA = temp;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Fills each alarmStruct member with its default value
 *
 * @param       alarmStruct: Pointer to a RTC_ALARM_T structure that
 *                           contains the configuration ALRMA information for the RTC peripheral
 *
 * @retval      None
 */
void RTC_ConfigAlarmStructInit(RTC_ALARM_T* alarmStruct)
{
    alarmStruct->time.hours = 1;
    alarmStruct->time.minutes = 2;
    alarmStruct->time.seconds = 3;
    alarmStruct->time.H12 = RTC_H12_AM;
    alarmStruct->AlarmDateWeekDay = 1;
    alarmStruct->AlarmDateWeekDaySel = RTC_WEEKDAY_SEL_DATE;
    alarmStruct->AlarmMask = RTC_MASK_NONE;
}

/*!
 * @brief       Get the RTC ALRMA value and masks
 *
 * @param       format: specifies the format to write
 *                      This parameter can be one of the following values:
 *                      @arg RTC_FORMAT_BIN: format in Bin
 *                      @arg RTC_FORMAT_BCD: format in BCD
 *
 * @param       alarmStruct: Pointer to a RTC_ALARM_T structure that
 *                           contains the configuration ALRMA information for the RTC peripheral
 *
 * @retval      None
 */
void RTC_ReadAlarm(RTC_FORMAT_T format, RTC_ALARM_T* alarmStruct)
{
    uint8_t day_d, day_u, hours_d, hours_u, minutes_d, minutes_u, seconds_d, seconds_u;
    uint32_t day_mask, hours_mask, minutes_mask, seconds_mask;

    day_d = RTC->ALRMA_B.DAYT << 0x04;
    day_u = RTC->ALRMA_B.DAYU;
    hours_d = RTC->ALRMA_B.HRT << 0x04;
    hours_u = RTC->ALRMA_B.HRU;
    minutes_d = RTC->ALRMA_B.MINT << 0x04;
    minutes_u = RTC->ALRMA_B.MINU;
    seconds_d = RTC->ALRMA_B.SECT << 0x04;
    seconds_u = RTC->ALRMA_B.SECU;

    day_mask = RTC->ALRMA_B.DATEMEN << 8;
    hours_mask = RTC->ALRMA_B.HRMEN << 8;
    minutes_mask = RTC->ALRMA_B.MINMEN << 8;
    seconds_mask = RTC->ALRMA_B.SECMEN << 7;

    alarmStruct->time.hours   = (uint8_t)(hours_d | hours_u);
    alarmStruct->time.minutes = (uint8_t)(minutes_d | minutes_u);
    alarmStruct->time.seconds = (uint8_t)(seconds_d | seconds_u);
    alarmStruct->time.H12     = (uint8_t)(RTC->ALRMA_B.TIMEFCFG);
    alarmStruct->AlarmDateWeekDay = (uint8_t)(day_d | day_u);
    alarmStruct->AlarmDateWeekDaySel = (RTC_WEEKDAY_SEL_T)(RTC->ALRMA_B.WEEKSEL);
    alarmStruct->AlarmMask = (uint32_t)(day_mask | hours_mask | minutes_mask | seconds_mask);

    if (format == RTC_FORMAT_BIN)
    {
        alarmStruct->time.hours = (uint8_t)RTC_Bcd2ConByte(alarmStruct->time.hours);
        alarmStruct->time.minutes = (uint8_t)RTC_Bcd2ConByte(alarmStruct->time.minutes);
        alarmStruct->time.seconds = (uint8_t)RTC_Bcd2ConByte(alarmStruct->time.seconds);
        alarmStruct->AlarmDateWeekDay = (uint8_t)RTC_Bcd2ConByte(alarmStruct->AlarmDateWeekDay);
    }
}

/*!
 * @brief       Enable the RTC ALRMA.
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_EnableAlarm(void)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.ALREN = BIT_SET;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Disable the the RTC ALRMA.
 *
 * @param       None
 *
 * @retval      None
 */
uint8_t RTC_DisableAlarm(void)
{
    __IO uint32_t count = 0x00;
    RTC_DisableWriteProtection();
    RTC->CTRL_B.ALREN = BIT_RESET;

    while ((count != RTC_INITMODE_TIMEOUT) && ((RTC->STS_B.ALRWFLG) == BIT_RESET))
    {
        count++;
    }

    if ((RTC->STS_B.ALRWFLG) == BIT_RESET)
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
 * @brief       Read the RTC ALRMA Subseconds value
 *
 * @param       val: specifies the value for ALRMA Sub Second
 *                   this value must less than 0x00007FFF
 *
 * @param       mask: specifies the mask for ALRMA Sub Second
 *                   this value must less than 0x0f
 *
 * @retval      None
 */
void RTC_ConfigAlarmSubSecond(uint32_t val, uint8_t mask)
{
    RTC_DisableWriteProtection();
    RTC->ALRMASS_B.SUBSEC = val;
    RTC->ALRMASS_B.MASKSEL = mask;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Read the RTC ALRMA Subseconds value
 *
 * @param       None
 *
 * @retval      RTC ALRMA Subseconds value
 */
uint32_t RTC_ReadAlarmSubSecond(void)
{
    return (uint32_t)(RTC->ALRMASS_B.SUBSEC);
}

/*!
 * @brief       Configure the RTC Wakeup clock source.
 *
 * @param       wakeUpClock: Wakeup Clock source.
 *                    This parameter can be one of the following values:
 *                     @arg RTC_WAKEUP_CLOCK_RTCDIV16
 *                     @arg RTC_WAKEUP_CLOCK_RTCDIV8
 *                     @arg RTC_WAKEUP_CLOCK_RTCDIV4
 *                     @arg RTC_WAKEUP_CLOCK_RTCDIV2
 *                     @arg RTC_WAKEUP_CLOCK_CK_SPRE_16B
 *                     @arg RTC_WAKEUP_CLOCK_CK_SPRE_17B
 *
 * @retval      None
 *
 * @note        It's only for APM32F072 and APM32F091 devices
 */
void RTC_ConfigWakeUpClock(RTC_WAKEUP_CLOCK_T wakeUpClock)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.WUCLKSEL = wakeUpClock;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Configure the RTC Wakeup counter value.
 *
 * @param       wakeUpValue: Wakeup auto-reload value.
 *              This parameter can be a value from 0x0000 to 0xFFFF.
 *
 * @retval      None
 *
 * @note        The value from 0x0000 to 0xFFFF.
 */
void RTC_SetWakeUpValue(uint32_t wakeUpValue)
{
    RTC_DisableWriteProtection();
    RTC->AUTORLD = wakeUpValue;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Read the RTC Wakeup counter value.
 *
 * @param       None
 *
 * @retval      The RTC WakeUp Counter value.
 */
uint32_t RTC_ReadWakeUpValue(void)
{
    return ((uint32_t)(RTC->AUTORLD & 0x0000FFFF));
}

/*!
 * @brief       Enable the RTC WakeUp timer.
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_EnableWakeUp(void)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.WUTEN = BIT_SET;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Disable the RTC WakeUp timer.
 *
 * @param       None
 *
 * @retval      None
 */
uint8_t RTC_DisableWakeUp(void)
{
    __IO uint32_t count = 0x00;
    RTC_DisableWriteProtection();

    RTC->CTRL_B.WUTEN = BIT_RESET;

    while ((count != RTC_INITMODE_TIMEOUT) && ((RTC->STS_B.WUTWFLG) == BIT_RESET))
    {
        count++;
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
 * @brief       Adds or substract one hour from the current time
 *
 * @param       sav:   specifies the DayLightSaving
 *                     This parameter can be one of the following values:
 *                     @arg RTC_DLS_SUB1H
 *                     @arg RTC_DLS_ADD1H
 *
 * @param       bit:   specifies the DayLightSaving
 *                     This parameter can be one of the following values:
 *                     @arg RTC_SO_RESET
 *                     @arg RTC_SO_SET
 *
 * @retval      None
 */
void RTC_ConfigDayLightSaving(RTC_DAYLIGHT_SAVING_T sav, RTC_STORE_OPERATION_T bit)
{
    RTC_DisableWriteProtection();

    if (sav == RTC_DLS_ADD1H)
    {
        RTC->CTRL_B.STCCFG = (uint32_t)BIT_SET;
        RTC->CTRL_B.WTCCFG = (uint32_t)BIT_RESET;
    }
    else
    {
        RTC->CTRL_B.STCCFG = (uint32_t)BIT_RESET;
        RTC->CTRL_B.WTCCFG = (uint32_t)BIT_SET;
    }

    RTC->CTRL_B.BAKP = (uint32_t)bit;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Returns the RTC Day Light Saving stored operation
 *
 * @param       None
 *
 * @retval      RTC Day Light Saving stored operation
 */
uint32_t RTC_ReadStoreOperation(void)
{
    return (RTC->CTRL_B.BAKP);
}

/*!
 * @brief       Enables the RTC TimeStamp functionality with the
 *              specified time stamp pin stimulating edge
 *
 * @param       opsel: specifies RTC TimeStamp functionality
 *                     This parameter can be one of the following values:
 *                     @arg RTC_OPSEL_DISABLE
 *                     @arg RTC_OPSEL_ALARMA
*                      @arg RTC_OPSEL_WAKEUP: available only for APM32F072 and APM32F091 devices
 *
 * @param       opp:   specified time stamp pin stimulating edge
 *                     This parameter can be one of the following values:
 *                     @arg RTC_OPP_HIGH
 *                     @arg RTC_OPP_LOW
 *
 * @retval      None
 */
void RTC_ConfigOutput(RTC_OPSEL_T opsel, RTC_OPP_T opp)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.OUTSEL = (uint32_t)opsel;
    RTC->CTRL_B.POLCFG = (uint32_t)opp;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Enable the RTC clock to be output through the relative pin
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_EnableCalibOutput(void)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.CALOEN = BIT_SET;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Disable the RTC clock to be output through the relative pin
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_DisableCalibOutput(void)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.CALOEN = BIT_RESET;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Configure the Calibration Pinout Selection (1Hz or 512Hz).
 *
 * @param       calib:  Select the Calibration output Selection .
 *                      This parameter can be one of the following values:
 *                      @arg RTC_CALIBOUTPUT_512Hz
 *                      @arg RTC_CALIBOUTPUT_1Hz
 *
 * @retval      None
 */
void RTC_ConfigCalibOutput(RTC_CALIB_OUTPUT_T calib)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.CALOSEL = (uint32_t)calib;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Configures the Synchronization Shift Control Settings.
 *
 * @param       period: Select the Smooth Calibration period.
 *                      This parameter can be can be one of the following values:
 *                      @arg RTC_SCP_16SEC: The smooth calibration periode is 16.
 *                      @arg RTC_SCP_8SEC:  The smooth calibartion periode is 8s.
 *
 * @param       bit:    Select to Set or reset the CALP bit.
 *                      This parameter can be one of the following values:
 *                      @arg RTC_SCPP_RESET: Add one RTCCLK puls every 2**11 pulses.
 *                      @arg RTC_SCPP_SET:   No RTCCLK pulses are added.
 *
 * @param       value:  Select the value of CALM[8:0] bits.
 *                      This parameter can be one any value from 0 to 0x000001FF.
 *
 * @retval         SUCCESS or ERROR
 */
uint8_t RTC_ConfigSmoothCalib(RTC_SCP_T period, RTC_SCPP_T bit, uint32_t value)
{
    uint8_t state = ERROR;
    uint32_t count = 0;

    RTC_DisableWriteProtection();

    if (RTC->STS_B.RCALPFLG != BIT_RESET)
    {
        while ((RTC->STS_B.RCALPFLG != BIT_RESET) && (count != RTC_RECALPF_TIMEOUT))
        {
            count++;
        }
    }

    if (RTC->STS_B.RCALPFLG == BIT_RESET)
    {
        if (period == RTC_SCP_16SEC)
        {
            RTC->CAL = ((((uint32_t)bit << 15) | \
                         (uint32_t)BIT_SET << 13) | \
                        (uint32_t)value);
        }
        else
        {
            RTC->CAL = ((((uint32_t)bit << 15) | \
                         (uint32_t)BIT_SET << 14) | \
                        (uint32_t)value);
        }

        state = SUCCESS;
    }
    else
    {
        state = ERROR;
    }

    RTC_EnableWriteProtection();
    return (state);
}

/*!
 * @brief       Enables the RTC TimeStamp functionality with the
 *              specified time stamp pin stimulating edge
 *
 * @param       edge: Specifies the pin edge on which the TimeStamp is  activated.
 *                    This paramete can be one of the following:
 *                    @arg RTC_TIME_STAMPEDGE_RISING: the Time stamp event occurs on the rising
 *                                           edge of the related pin.
 *                    @arg RTC_TIME_STAMPEDGE_FALLING: the Time stamp event occurs on the
 *                                            falling edge of the related pin.
 * @retval      None
 */
void RTC_EnableTimeStamp(RTC_TIMESTAMP_EDGE_T edge)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.TSEN = BIT_SET;
    RTC->CTRL_B.TSETECFG = (uint32_t)edge;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Disables the RTC TimeStamp functionality with the
 *              specified time stamp pin stimulating edge
 *
 * @param       edge: Specifies the pin edge on which the TimeStamp is  activated.
 *                    This paramete can be one of the following:
 *                    @arg RTC_TIME_STAMPEDGE_RISING: the Time stamp event occurs on the rising
 *                                           edge of the related pin.
 *                    @arg RTC_TIME_STAMPEDGE_FALLING: the Time stamp event occurs on the
 *                                            falling edge of the related pin.
 *
 * @retval      None
 */
void RTC_DisableTimeStamp(RTC_TIMESTAMP_EDGE_T edge)
{
    RTC_DisableWriteProtection();
    RTC->CTRL_B.TSEN = BIT_RESET;
    RTC->CTRL_B.TSETECFG = (uint32_t)edge;
    RTC_EnableWriteProtection();
}

/*!
 * @brief       Read the RTC TimeStamp value and masks
 *
 * @param       format: specifies the format of the output parameters.
 *                      This parameter can be one of the following values:
 *                      @arg RTC_Format_BIN: data in Binary format
 *                      @arg RTC_Format_BCD: data in BCD    format
 *
 * @param       timeStruct: pointer to a RTC_TIME_T structure that will
 *                              contains the TimeStamp time values.
 *
 * @param       dateStruct: pointer to a RTC_DATE_T structure that will
 *                              contains the TimeStamp date values.
 *
 * @retval      None
 */
void RTC_ReadTimeDate(RTC_FORMAT_T format, RTC_TIME_T* timeStruct, RTC_DATE_T* dateStruct)
{
    uint32_t temptime = 0, tempdate = 0;
    temptime = (uint32_t)((RTC->TSTIME) & 0x007F7F7F);
    tempdate = (uint32_t)((RTC->TSDATE) & 0x00FFFF3F);

    timeStruct->hours   = (uint8_t)((temptime & 0x003F0000) >> 16);
    timeStruct->minutes = (uint8_t)((temptime & 0x00007F00) >> 8);
    timeStruct->seconds = (uint8_t)(temptime &  0x0000007F);
    timeStruct->H12 = (uint8_t)((temptime & 0x00400000) >> 22);

    dateStruct->year  =  0;
    dateStruct->month = (uint8_t)((tempdate & 0x00001F00) >> 8);
    dateStruct->date  = (uint8_t)(tempdate &  0x0000003F);
    dateStruct->weekday = (uint8_t)((tempdate & 0x0000E000) >> 13);

    if (format == RTC_FORMAT_BIN)
    {
        timeStruct->hours   = (uint8_t)RTC_Bcd2ConByte(timeStruct->hours);
        timeStruct->minutes = (uint8_t)RTC_Bcd2ConByte(timeStruct->minutes);
        timeStruct->seconds = (uint8_t)RTC_Bcd2ConByte(timeStruct->seconds);

        dateStruct->month = (uint8_t)RTC_Bcd2ConByte(dateStruct->month);
        dateStruct->date  = (uint8_t)RTC_Bcd2ConByte(dateStruct->date);
        dateStruct->weekday = (uint8_t)(dateStruct->weekday);
    }
}

/*!
 * @brief       Get the RTC timestamp Subseconds value
 *
 * @param       None
 *
 * @retval      RTC current timestamp Subseconds value
 */
uint32_t RTC_ReadTimeStampSubSecond(void)
{
    return (uint32_t)(RTC->TSSUBSEC);
}

/*!
 * @brief       Configures the select Tamper pin edge
 *
 * @param       tamper:  Selected tamper pin.
 *                       This parameter can be one of the following values:
 *                       @arg RTC_TAMPER_1: Select Tamper 1.
 *                       @arg RTC_TAMPER_2: Select Tamper 2.
 *                       @arg RTC_TAMPER_3: Select Tamper 3. (Only for APM32F072 and APM32F091 devices)
 *
 * @param       trigger: Specifies the trigger on the tamper pin that stimulates tamper event.
 *                       This parameter can be one of the following values:
 *                       @arg RTC_TAMPER_TRIGGER_RISINGEDGE: Rising Edge of the tamper pin causes tamper event.
 *                       @arg RTC_TAMPER_TRIGGER_FALLINGEDGE: Falling Edge of the tamper pin causes tamper event.
 *                       @arg RTC_TAMPER_TRIGGER_LOWLEVEL: Low Level of the tamper pin causes tamper event.
 *                       @arg RTC_TAMPER_TRIGGER_HIGHLEVEL: High Level of the tamper pin causes tamper event.
 *
 * @retval      None
 */
void RTC_ConfigTamperTrigger(RTC_TAMPER_T tamper, RTC_TAMPER_TRIGGER_T trigger)
{
    if (trigger == RTC_TAMPER_TRIGGER_RISINGEDGE)
    {
        if (tamper == RTC_TAMPER_1)
        {
            RTC->TACFG_B.TP1ALCFG = BIT_RESET;
        }
        if (tamper == RTC_TAMPER_2)
        {
            RTC->TACFG_B.TP2ALCFG = BIT_RESET;
        }
        if (tamper == RTC_TAMPER_3)
        {
            RTC->TACFG_B.TP3ALCFG = BIT_RESET;
        }
    }
    else
    {
        if (tamper == RTC_TAMPER_1)
        {
            RTC->TACFG_B.TP1ALCFG = BIT_SET;
        }
        if (tamper == RTC_TAMPER_2)
        {
            RTC->TACFG_B.TP2ALCFG = BIT_SET;
        }
        if (tamper == RTC_TAMPER_3)
        {
            RTC->TACFG_B.TP3ALCFG = BIT_SET;
        }
    }
}

/*!
 * @brief       Enables the Tamper detection
 *
 * @param       tamper: Selected tamper pin.
 *                      This parameter can be one of the following values:
 *                      @arg RTC_TAMPER_1: Select Tamper 1.
 *                      @arg RTC_TAMPER_2: Select Tamper 2.
 *                      @arg RTC_TAMPER_3: Select Tamper 3.(Only for APM32F072 and APM32F091 devices)
 *
 * @retval      None
 */
void RTC_EnableTamper(RTC_TAMPER_T tamper)
{
    if (tamper == RTC_TAMPER_1)
    {
        RTC->TACFG_B.TP1EN = BIT_SET;
    }
    if (tamper == RTC_TAMPER_2)
    {
        RTC->TACFG_B.TP2EN = BIT_SET;
    }
    if (tamper == RTC_TAMPER_3)
    {
        RTC->TACFG_B.TP3EN = BIT_SET;
    }

}

/*!
 * @brief       Disables the Tamper detection
 *
 * @param       tamper: Selected tamper pin.
 *                      This parameter can be any combination of the following values:
 *                      @arg RTC_TAMPER_1: Select Tamper 1.
 *                      @arg RTC_TAMPER_2: Select Tamper 2.
 *                      @arg RTC_TAMPER_3: Select Tamper 3.(Only for APM32F072 and APM32F091 devices)
 *
 * @retval      None
 */
void RTC_DisableTamper(RTC_TAMPER_T tamper)
{
    if (tamper == RTC_TAMPER_1)
    {
        RTC->TACFG_B.TP1EN = BIT_RESET;
    }
    if (tamper == RTC_TAMPER_2)
    {
        RTC->TACFG_B.TP2EN = BIT_RESET;
    }
    if (tamper == RTC_TAMPER_3)
    {
        RTC->TACFG_B.TP3EN = BIT_RESET;
    }
}

/*!
 * @brief       Configures the Tampers Filter
 *
  * @param      filter: Specifies the tampers filter.
  *                     This parameter can be one of the following values:
  *                     @arg RTC_TAMPER_FILTER_DISABLE: Tamper filter is disabled.
  *                     @arg RTC_TAMPER_FILTER_2SAMPLE: Tamper is activated after 2 consecutive samples at the active level
  *                     @arg RTC_TAMPER_FILTER_4SAMPLE: Tamper is activated after 4 consecutive samples at the active level
  *                     @arg RTC_TAMPER_FILTER_8SAMPLE: Tamper is activated after 8 consecutive samples at the active level
  *
 *
 * @retval      None
 */
void RTC_ConfigFilter(RTC_TAMPER_FILTER_T filter)
{
    RTC->TACFG_B.TPFCSEL = (uint32_t)filter;
}

/*!
 * @brief       Configures the Tampers Sampling Frequency
 *
 * @param       freq: Specifies the tampers Sampling Frequency.
 *                    This parameter can be one of the following values:
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768: Each of the tamper inputs are sampled
 *                                                         with a frequency =  RTCCLK / 32768
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384: Each of the tamper inputs are sampled
 *                                                         with a frequency =  RTCCLK / 16384
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192: Each of the tamper inputs are sampled
 *                                                      with a frequency =  RTCCLK / 8192
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096: Each of the tamper inputs are sampled
 *                                                        with a frequency =  RTCCLK / 4096
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048: Each of the tamper inputs are sampled
 *                                                        with a frequency =  RTCCLK / 2048
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024: Each of the tamper inputs are sampled
 *                                                        with a frequency =  RTCCLK / 1024
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512: Each of the tamper inputs are sampled
 *                                                       with a frequency =  RTCCLK / 512
 *                    @arg RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256: Each of the tamper inputs are sampled
 *                                                       with a frequency =  RTCCLK / 256
 *
 * @retval      None
 */
void RTC_ConfigSamplingFreq(RTC_TAMPER_SAMPLING_FREQ_T freq)
{
    RTC->TACFG_B.TPSFSEL = (uint32_t)freq;
}

/*!
 * @brief       Configures the Precharge Duration
 *
 * @param       duration: Specifies the Tampers Pins input  Precharge Duration.
 *                    This parameter can be one of the following values:
 *                    @arg RTC_PRECHARGEDURATION_1RTCCLK: Tamper pins are pre-charged before sampling during 1 RTCCLK cycle
 *                    @arg RTC_PRECHARGEDURATION_2RTCCLK: Tamper pins are pre-charged before sampling during 2 RTCCLK cycle
 *                    @arg RTC_PRECHARGEDURATION_4RTCCLK: Tamper pins are pre-charged before sampling during 4 RTCCLK cycle
 *                    @arg RTC_PRECHARGEDURATION_8RTCCLK: Tamper pins are pre-charged before sampling during 8 RTCCLK cycle
 *
 * @retval      None
 */
void RTC_PinsPrechargeDuration(RTC_PRECHARGE_DURATION_T duration)
{
    RTC->TACFG_B.TPPRDUSEL = (uint32_t)duration;
}

/*!
 * @brief       Enables the TimeStamp on Tamper Detection Event
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_EnableTDE(void)
{
    RTC->TACFG_B.TPTSEN = BIT_SET;
}

/*!
 * @brief       Disable the TimeStamp on Tamper Detection Event
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_DisableTDE(void)
{
    RTC->TACFG_B.TPTSEN = BIT_RESET;
}

/*!
 * @brief       Enable precharge of the selected Tamper pin
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_EnablePullUp(void)
{
    RTC->TACFG_B.TPPUDIS = BIT_SET;
}

/*!
 * @brief       Disable precharge of the selected Tamper pin
 *
 * @param       None
 *
 * @retval      None
 */
void RTC_DisablePullUp(void)
{
    RTC->TACFG_B.TPPUDIS = BIT_RESET;
}

/*!
 * @brief       Writes a data in RTC Backup data.
 *
 * @param       backup: RTC Backup data Register number.
 *                      This parameter can be one of the following values:
 *                      @arg RTC_BAKP_DATA0
 *                      @arg RTC_BAKP_DATA1
 *                      @arg RTC_BAKP_DATA2
 *                      @arg RTC_BAKP_DATA3
 *                      @arg RTC_BAKP_DATA4
 * @param       data: Data to be written in the specified RTC Backup data register.
 *
 * @retval      None
 */
void RTC_WriteBackup(RTC_BAKP_DATA_T backup, uint32_t data)
{
    switch (backup)
    {
        case 0:
            RTC->BAKP0 = data;
            break;

        case 1:
            RTC->BAKP1 = data;
            break;

        case 2:
            RTC->BAKP2 = data;
            break;

        case 3:
            RTC->BAKP3 = data;
            break;

        case 4:
            RTC->BAKP4 = data;
            break;

        default:
            break;
    }
}

/*!
 * @brief       Reads a data in RTC Backup data.
 *
 * @param       backup: RTC Backup data Register number.
 *                      This parameter can be one of the following values:
 *                      @arg RTC_BAKP_DATA0
 *                      @arg RTC_BAKP_DATA1
 *                      @arg RTC_BAKP_DATA2
 *                      @arg RTC_BAKP_DATA3
 *                      @arg RTC_BAKP_DATA4
 *
 * @retval      None
 */
uint32_t RTC_ReadBackup(RTC_BAKP_DATA_T backup)
{
    uint32_t data;

    switch (backup)
    {
        case 0:
            data = RTC->BAKP0;
            break;

        case 1:
            data = RTC->BAKP1;
            break;

        case 2:
            data = RTC->BAKP2;
            break;

        case 3:
            data = RTC->BAKP3;
            break;

        case 4:
            data = RTC->BAKP4;
            break;

        default:
            break;
    }

    return (data);
}

/*!
 * @brief       Configures the RTC Output Pin mode
 *
 * @param       output: specifies the RTC Output (PC13) pin mode.
 *                      This parameter can be one of the following values:
 *                      @arg RTC_OPENDRAIN: RTC Output (PC13) is configured in
 *                                    Open Drain mode.
 *                      @arg RTC_PUSHPULL:  RTC Output (PC13) is configured in
 *                                    Push Pull mode.
 *
 * @retval      None
 */
void RTC_ConfigOutputType(RTC_OUTPUT_T output)
{
    RTC->TACFG_B.PC13VAL = (uint32_t)output;
}

/*!
 * @brief       Configures the Synchronization Shift Control Settings.
 *
 * @param       add1S:  Select to add or not 1 second to the time Calendar.
 *                      This parameter can be one of the following values :
 *                      @arg RTC_SHIFTADD1S_SET: Add one second to the clock calendar.
 *                      @arg RTC_SHIFTADD1S_RESET:   No effect.
 *
 * @param       subFS:  Select the number of Second Fractions to Substitute.
 *                      This parameter can be one any value from 0 to 0x7FFF.
 *
 * @retval      SUCCESS or ERROR
 */
uint8_t RTC_ConfigSynchroShift(RTC_SHIFT_ADD1S_T add1S, uint32_t subFS)
{
    uint8_t state = ERROR;
    uint32_t shpfcount = 0;
    RTC_DisableWriteProtection();

    if (RTC->STS_B.SOPFLG != BIT_RESET)
    {
        while ((RTC->STS_B.SOPFLG != BIT_RESET) && (shpfcount != RTC_SHPF_TIMEOUT))
        {
            shpfcount++;
        }
    }

    if (RTC->STS_B.SOPFLG == BIT_RESET)
    {
        if (RTC->CTRL_B.RCLKDEN == BIT_RESET)
        {
            RTC->SHIFT_B.ADD1SECEN = add1S;
            RTC->SHIFT_B.SFSEC = subFS;

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
            state = ERROR;
        }
    }
    else
    {
        state = ERROR;
    }

    RTC_EnableWriteProtection();
    return (state);
}

/*!
 * @brief       Enable RTC interrupts.
 *
 * @param       interrupt: specifies the RTC interrupt sources to be enabled
 *                       This parameter can be any combination of the following values:
 *                        @arg RTC_INT_ALR:  ALRMA A interrupt mask
 *                        @arg RTC_INT_WT:  WakeUp Timer interrupt mask(only APM32F072 and APM32F091 devices)
 *                        @arg RTC_INT_TS:   Time Stamp interrupt mask
 *                        @arg RTC_INT_TAMP: Tamper event interrupt mask
 *
 * @retval      None
 */
void RTC_EnableInterrupt(uint32_t interrupt)
{
    RTC_DisableWriteProtection();
    RTC->CTRL |= (uint32_t)(interrupt & ~0x00000004);
    RTC->TACFG |= (uint32_t)(interrupt & 0x00000004);
    RTC_EnableWriteProtection();
}

/*!
 * @brief     Disable RTC interrupts.
 *
 * @param     interrupt: specifies the RTC interrupt sources to be disable
 *                       This parameter can be any combination of the following values:
 *                        @arg RTC_INT_ALR:  ALRMA A interrupt mask
 *                        @arg RTC_INT_WT:   WakeUp Timer interrupt mask(only APM32F072 and APM32F091 devices)
 *                        @arg RTC_INT_TS:   Time Stamp interrupt mask
 *                        @arg RTC_INT_TAMP: Tamper event interrupt mask
 *
 * @retval    None
 */
void RTC_DisableInterrupt(uint32_t interrupt)
{
    RTC_DisableWriteProtection();
    RTC->CTRL &= (uint32_t)~(interrupt & ~0x00000004);
    RTC->TACFG &= (uint32_t)~(interrupt & 0x00000004);
    RTC_EnableWriteProtection();
}

/*!
 * @brief     Read interrupt flag bit is set
 *
 * @param     flag: specifies the flag to read.
 *                  This parameter can be one of the following values:
 *                  @arg RTC_INT_FLAG_ALR: ALRMA interrupt
 *                  @arg RTC_INT_FLAG_TS: Time Stamp interrupt
 *                  @arg RTC_INT_FLAG_WT: WakeUp Timer interrupt (only APM32F072 and APM32F091 devices)
 *                  @arg RTC_INT_FLAG_TAMP1: Tamper1 event interrupt
 *                  @arg RTC_INT_FLAG_TAMP2: Tamper2 event interrupt
 *                  @arg RTC_INT_FLAG_TAMP3: Tamper3 event interrupt  (Only for APM32F072 and APM32F091 devices)
 * @retval    The new state of flag (SET or RESET).
 */
uint8_t RTC_ReadIntFlag(RTC_INT_FLAG_T flag)
{
    uint32_t intEnable;
    uint32_t intStatus;

    if (flag & 0x04)
    {
        intEnable = (uint32_t)RTC->TACFG_B.TPIEN;
        intStatus = (uint32_t)(RTC->STS & (flag >> 4));
    }
    else
    {
        intEnable = (uint32_t)RTC->CTRL;
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
 *                  @arg RTC_INT_FLAG_ALR: ALRMA interrupt
 *                  @arg RTC_INT_FLAG_TS: Time Stamp interrupt
 *                  @arg RTC_INT_FLAG_WT: WakeUp Timer interrupt (only APM32F072 and APM32F091 devices)
 *                  @arg RTC_INT_FLAG_TAMP1: Tamper1 event interrupt
 *                  @arg RTC_INT_FLAG_TAMP2: Tamper2 event interrupt
 *                  @arg RTC_INT_FLAG_TAMP3: Tamper3 event interrupt  (Only for APM32F072 and APM32F091 devices)
 * @retval    The new state of flag (SET or RESET).
 */
void RTC_ClearIntFlag(uint32_t flag)
{
    RTC->STS &= (uint32_t) ~(flag >> 4);
}

/*!
 * @brief     Checks whether the specified RTC flag is set or not.
 *
 * @param     flag: specifies the flag to check.
 *                  This parameter can be one of the following values:
 *                  @arg RTC_FLAG_ISF
 *                  @arg RTC_FLAG_RSF
 *                  @arg RTC_FLAG_INTF
 *                  @arg RTC_FLAG_ALRF
 *                  @arg RTC_FLAG_WTF  (only APM32F072 and APM32F091 devices)
 *                  @arg RTC_FLAG_TSF
 *                  @arg RTC_FLAG_TSOF
 *                  @arg RTC_FLAG_TP1F
 *                  @arg RTC_FLAG_TP2F
 *                  @arg RTC_FLAG_TP3F  (only APM32F072 and APM32F091 devices)
 *                  @arg RTC_FLAG_RPF
 * @retval    The new state of RTC_FLAG (SET or RESET).
 */
uint8_t RTC_ReadStatusFlag(RTC_FLAG_T flag)
{
    return (RTC->STS & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the RTC's status flags.
 * @param     flag: specifies the RTC flag to clear.
 *                  This parameter can be any combination of the following values:
 *                  @arg RTC_FLAG_TP3F: Tamper 3 event flag (only APM32F072 and APM32F091 devices)
 *                  @arg RTC_FLAG_TP2F: Tamper 2 event flag
 *                  @arg RTC_FLAG_TP1F: Tamper 1 event flag
 *                  @arg RTC_FLAG_TSOF: Time Stamp Overflow flag
 *                  @arg RTC_FLAG_TSF : Time Stamp event flag
 *                  @arg RTC_FLAG_WTF £ºWakeUp Timer flag  (only APM32F072 and APM32F091 devices)
 *                  @arg RTC_FLAG_ALRF: ALRMA A flag
 *                  @arg RTC_FLAG_RSF:  Registers Synchronized flag
 */
void RTC_ClearStatusFlag(uint32_t flag)
{
    RTC->STS &= (uint32_t)~flag;
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

    return ((uint8_t)(bcdhigh << 4) | val);
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

/**@} end of group RTC_Functions*/
/**@} end of group RTC_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver*/

