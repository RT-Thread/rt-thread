/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_irtc_hal.h"
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_RTC_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_Init
 * Description   : Resets the IRTC module.
 * This function initiates a soft-reset of the IRTC module to reset
 * the IRTC registers.
 *
 *END**************************************************************************/
void IRTC_HAL_Init(RTC_Type *base)
{
    /* Unlock IRTC registers. */
    IRTC_HAL_SetLockRegisterCmd(base, false);

    /* Issue a software reset */
    IRTC_HAL_SoftwareReset(base);

    /* Lock IRTC registers. */
    IRTC_HAL_SetLockRegisterCmd(base, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_SetLockRegisterCmd
 * Description   : Lock or unlock IRTC registers for write access.
 *
 *END**************************************************************************/
void IRTC_HAL_SetLockRegisterCmd(RTC_Type *base, bool lock)
{
    if (!lock)
    {
        while (RTC_BRD_STATUS_WRITE_PROT_EN(base))
        {
            RTC_WRITE_ENABLE(base, 0x00U);
            RTC_WRITE_ENABLE(base, 0x40U);
            RTC_WRITE_ENABLE(base, 0xC0U);
            RTC_WRITE_ENABLE(base, 0x80U);
        }
    }
    else
    {
        while (!RTC_BRD_STATUS_WRITE_PROT_EN(base))
        {
            RTC_WRITE_ENABLE(base, 0x80U);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_SetDatetime
 * Description   : Sets the IRTC date and time according to the given structure.
 *
 *END**************************************************************************/
void IRTC_HAL_SetDatetime(RTC_Type *base, const irtc_datetime_t * datetime)
{
    /* Wait for validate CPU write/read */
    while(IRTC_HAL_GetStatusFlag(base, kIRTCInvalidate)){ }

    IRTC_HAL_SetYearMonth(base, datetime->year, datetime->month);
    IRTC_HAL_SetDayWeek(base, datetime->day, datetime->weekDay);
    IRTC_HAL_SetHourMin(base, datetime->hour, datetime->minute);
    IRTC_HAL_SetSec(base, datetime->second);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetDatetime
 * Description   : Gets the IRTC time and stores it in the given time structure.
 *
 *END**************************************************************************/
void IRTC_HAL_GetDatetime(RTC_Type *base, irtc_datetime_t * datetime)
{
    /* Wait for validate CPU write/read */
    while(IRTC_HAL_GetStatusFlag(base, kIRTCInvalidate)){ }

    IRTC_HAL_GetYearMonth(base, &datetime->year, &datetime->month);
    IRTC_HAL_GetDayWeek(base, &datetime->day, &datetime->weekDay);
    IRTC_HAL_GetHourMin(base, &datetime->hour, &datetime->minute);
    IRTC_HAL_GetSec(base, &datetime->second);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_SetYearMonth
 * Description   : Sets the IRTC year and month.
 *
 *END**************************************************************************/
void IRTC_HAL_SetYearMonth(RTC_Type * base, uint16_t year, uint16_t month)
{
    if (year < IRTC_BASE_YEAR)
    {
        RTC_WR_YEARMON(base, RTC_YEARMON_YROFST(0x100+year-IRTC_BASE_YEAR) |
                             RTC_YEARMON_MON_CNT(month));
    }
    else
    {
        RTC_WR_YEARMON(base, RTC_YEARMON_YROFST(year-IRTC_BASE_YEAR) |
                             RTC_YEARMON_MON_CNT(month));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetYearMonth
 * Description   : Gets the IRTC current year and month.
 *
 *END**************************************************************************/
void IRTC_HAL_GetYearMonth(RTC_Type * base, uint16_t * year, uint16_t * month)
{
    uint16_t temp = RTC_RD_YEARMON(base);

    *year = IRTC_BASE_YEAR + (int8_t)(temp >> RTC_YEARMON_YROFST_SHIFT);
    *month = temp & RTC_YEARMON_MON_CNT_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetDayWeek
 * Description   : Gets the IRTC current day and day of week.
 *
 *END**************************************************************************/
void IRTC_HAL_GetDayWeek(RTC_Type * base, uint16_t * day, uint16_t * weekDay)
{
    uint16_t temp = RTC_RD_DAYS(base);

    *weekDay = temp >> RTC_DAYS_DOW_SHIFT;
    *day = temp & RTC_DAYS_DAY_CNT_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetHourMin
 * Description   : Gets the IRTC current hour and minute.
 *
 *END**************************************************************************/
void IRTC_HAL_GetHourMin(RTC_Type * base, uint16_t * hour, uint16_t * min)
{
    uint16_t temp = RTC_RD_HOURMIN(base);

    *hour = temp >> RTC_HOURMIN_HOUR_CNT_SHIFT;
    *min = temp & RTC_HOURMIN_MIN_CNT_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_SetAlarm
 * Description   : Sets the IRTC alarm time and date.
 *
 *END**************************************************************************/
void IRTC_HAL_SetAlarm(RTC_Type *base, const irtc_datetime_t * datetime)
{
    if (datetime->year < IRTC_BASE_YEAR)
    {
        RTC_WR_ALM_YEARMON(base, RTC_ALM_YEARMON_ALM_YEAR(0x100 + datetime->year - IRTC_BASE_YEAR) |
                           RTC_ALM_YEARMON_ALM_MON(datetime->month));
    }
    else
    {
        RTC_WR_ALM_YEARMON(base, RTC_ALM_YEARMON_ALM_YEAR(datetime->year - IRTC_BASE_YEAR) |
                           RTC_ALM_YEARMON_ALM_MON(datetime->month));
    }

    RTC_WR_ALM_DAYS(base, datetime->day);
    RTC_WR_ALM_HOURMIN(base, RTC_ALM_HOURMIN_ALM_HOUR(datetime->hour) |
                             RTC_ALM_HOURMIN_ALM_MIN(datetime->minute));
    RTC_WR_ALM_SECONDS(base, RTC_ALM_SECONDS_ALM_SEC(datetime->second));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetAlarm
 * Description   : Reads the value of the time alarm.
 *
 *END**************************************************************************/
void IRTC_HAL_GetAlarm(RTC_Type *base, irtc_datetime_t * datetime)
{
    uint16_t temp = RTC_RD_ALM_YEARMON(base);

    datetime->year = IRTC_BASE_YEAR + (int8_t)(temp >> RTC_ALM_YEARMON_ALM_YEAR_SHIFT);
    datetime->month = temp & RTC_ALM_YEARMON_ALM_MON_MASK;

    datetime->day = RTC_RD_ALM_DAYS(base);

    temp = RTC_RD_ALM_HOURMIN(base);
    datetime->hour = temp >> RTC_ALM_HOURMIN_ALM_HOUR_SHIFT;
    datetime->minute = temp & RTC_ALM_HOURMIN_ALM_MIN_MASK;

    datetime->second = RTC_RD_ALM_SECONDS(base) & RTC_ALM_SECONDS_ALM_SEC_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_SetDaylightTime
 * Description   : Sets the IRTC date and time according to the given structure.
 *
 *END**************************************************************************/
void IRTC_HAL_SetDaylightTime(RTC_Type *base, const irtc_daylight_time_t  * datetime)
{
    /* Disable daylight saving time in order to modify. */
    RTC_BWR_CTRL_DST_EN(base, 0U);

    IRTC_HAL_SetDaylightMonth(base, datetime->startMonth, datetime->endMonth);
    IRTC_HAL_SetDaylightDay(base, datetime->startDay, datetime->endDay);
    IRTC_HAL_SetDaylightHour(base, datetime->startHour, datetime->endHour);

    /* Enable daylight saving time */
    RTC_BWR_CTRL_DST_EN(base, 1U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetDaylightTime
 * Description   : Gets the IRTC time and stores it in the given time structure.
 *
 *END**************************************************************************/
void IRTC_HAL_GetDaylightTime(RTC_Type *base, irtc_daylight_time_t * datetime)
{
    IRTC_HAL_GetDaylightMonth(base, &datetime->startMonth, &datetime->endMonth);
    IRTC_HAL_GetDaylightDay(base, &datetime->startDay, &datetime->endDay);
    IRTC_HAL_GetDaylightHour(base, &datetime->startHour, &datetime->endHour);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetDaylightMonth
 * Description   : Gets the IRTC current daylight saving start and end month.
 *
 *END**************************************************************************/
void IRTC_HAL_GetDaylightMonth(RTC_Type * base, uint16_t * startMonth, uint16_t * endMonth)
{
    uint16_t temp = RTC_RD_DST_MONTH(base);

    *startMonth = temp >> RTC_DST_MONTH_DST_START_MONTH_SHIFT;
    *endMonth = ((temp & RTC_DST_MONTH_DST_END_MONTH_MASK) >> RTC_DST_MONTH_DST_END_MONTH_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetDaylightDay
 * Description   : Gets the IRTC current daylight saving start and end day.
 *
 *END**************************************************************************/
void IRTC_HAL_GetDaylightDay(RTC_Type * base, uint16_t * startDay, uint16_t * endDay)
{
    uint16_t temp = RTC_RD_DST_DAY(base);

    *startDay = temp >> RTC_DST_DAY_DST_START_DAY_SHIFT;
    *endDay = ((temp & RTC_DST_DAY_DST_END_DAY_MASK) >> RTC_DST_DAY_DST_END_DAY_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_GetDaylightHour
 * Description   : Gets the IRTC current daylight saving start and end hour.
 *
 *END**************************************************************************/
void IRTC_HAL_GetDaylightHour(RTC_Type * base, uint16_t * startHour, uint16_t * endHour)
{
    uint16_t temp = RTC_RD_DST_HOUR(base);

    *startHour = temp >> RTC_DST_HOUR_DST_START_HOUR_SHIFT;
    *endHour = ((temp & RTC_DST_HOUR_DST_END_HOUR_MASK) >> RTC_DST_HOUR_DST_END_HOUR_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_SetCoarseCompensation
 * Description   : Enables coarse compensation and sets the value to the IRTC compensation register.
 *
 *END**************************************************************************/
void IRTC_HAL_SetCoarseCompensation(RTC_Type *base, uint8_t compVal, uint8_t compInterval)
{
    /* Set the compensation value and interval */
    RTC_WR_COMPEN(base, (compVal & 0xFFu) | ((compInterval & 0xFFu) << 8U));

    /* Disable fine and enable coarse compensation */
    RTC_BWR_CTRL_FINEEN(base, 0U);
    RTC_BWR_CTRL_COMP_EN(base, 1U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_SetFineCompensation
 * Description   : Enables fine compensation and set the value to the IRTC compensation register.
 *
 *END**************************************************************************/
void IRTC_HAL_SetFineCompensation(RTC_Type *base, uint8_t integralVal, uint8_t fracVal,
                                           bool accumulateFrac)
{
    if (!accumulateFrac)
    {
        /* Disable compensation to clear previous accumulated fractional part */
        RTC_CLR_CTRL(base, (1U << RTC_CTRL_COMP_EN_SHIFT) | (1U << RTC_CTRL_FINEEN_SHIFT));
    }

    /* Set the compensation fractional and integral parts */
    RTC_WR_COMPEN(base, (fracVal & 0x7Fu) | ((integralVal & 0xFu) << 12U));
    /* Enable fine compensation */
    RTC_SET_CTRL(base, (1U << RTC_CTRL_COMP_EN_SHIFT) | (1U << RTC_CTRL_FINEEN_SHIFT));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_ConfigTamperParams
 * Description   : There are 4 tamper inputs available, this function allows configuring
 * these tamper inputs. The function configures the filter properties for the 3 external tampers
 * i.e 0,1,2. It also sets up active/passive and direction of the tamper bits, these are not available
 * on all platforms.
 *
 * NOTE: This function programs the tamper filter paramters, the user of this function must
 * gate the 32K clock to RTC before calling this function. It is assumed that the time and date
 * will be set after this and the tamper parameters will not require to be changed again later
 *
 *END**************************************************************************/
void IRTC_HAL_ConfigTamperParams(RTC_Type *base, irtc_tamper_pins_t tamperNum,
                                           irtc_tamper_config_t * tamperConfig)
{
#if FSL_FEATURE_RTC_HAS_TAMPER_DIRECTION
    /* Set whether tamper pin is active or passive */
    if (tamperConfig->activePassive)
    {
        /* In case of active tamper, set the direction */
        RTC_SET_TAMPER_DIRECTION(base, (1U << tamperNum));
        if (tamperConfig->direction)
        {
            RTC_SET_TAMPER_DIRECTION(base, (1U << (RTC_TAMPER_DIRECTION_I_O_TAMP_SHIFT + tamperNum)));
        }
        else
        {
            RTC_CLR_TAMPER_DIRECTION(base, (1U << (RTC_TAMPER_DIRECTION_I_O_TAMP_SHIFT + tamperNum)));
        }

    }
    else
    {
        /* Passive tampers are input only and the direction bit is read only in this case */
        RTC_CLR_TAMPER_DIRECTION(base, (1U << tamperNum));
    }
#endif

    /* Set the filter properties for the external tamper pins */
    switch(tamperNum)
    {
        case kIRTCTamper0:
            /* Set the pin for Tamper 0 */
            RTC_BWR_CTRL2_WAKEUP_MODE(base, 0U);
            RTC_BWR_FILTER01_CFG_POL0(base, tamperConfig->pinPolarity);
            RTC_BWR_FILTER01_CFG_FIL_DUR0(base, tamperConfig->filterDuration);
            RTC_BWR_FILTER01_CFG_CLK_SEL0(base, tamperConfig->filterClk);
            break;
        case kIRTCTamper1:
            RTC_BWR_FILTER01_CFG_POL1(base, tamperConfig->pinPolarity);
            RTC_BWR_FILTER01_CFG_FIL_DUR1(base, tamperConfig->filterDuration);
            RTC_BWR_FILTER01_CFG_CLK_SEL1(base, tamperConfig->filterClk);
            break;
        case kIRTCTamper2:
            RTC_BWR_FILTER2_CFG_POL2(base, tamperConfig->pinPolarity);
            RTC_BWR_FILTER2_CFG_FIL_DUR2(base, tamperConfig->filterDuration);
            RTC_BWR_FILTER2_CFG_CLK_SEL2(base, tamperConfig->filterClk);
            break;
        default:
            break;
    }
}

#if FSL_FEATURE_RTC_HAS_TAMPER_QUEUE
/*FUNCTION**********************************************************************
 *
 * Function Name : IRTC_HAL_ReadTamperQueue
 * Description   : This function will read the tamper timestamp and return the
 * tamper pin associated with this entry.
 *
 *END**************************************************************************/
uint8_t IRTC_HAL_ReadTamperQueue(RTC_Type *base, irtc_datetime_t * tamperTimestamp)
{
    /* Read the register 2 times to get a entry*/
    uint16_t temp1 = RTC_RD_TAMPER_QUEUE(base);
    uint16_t temp2 = RTC_RD_TAMPER_QUEUE(base);
    uint8_t tamperNum;

    /*
     * Tamper queue does not store the year field as this value can be read from RTC_YEARMON.
     * It is expected that the queue will be read at least once in a year.
     */
    tamperTimestamp->year = 0;
    tamperTimestamp->hour = temp1 & 0x1Fu;
    tamperTimestamp->day = (temp1 >> 5U) & 0x1Fu;
    tamperTimestamp->month = (temp1 >> 10U) & 0xFu;

    tamperTimestamp->second = temp2 & 0x3Fu;
    tamperTimestamp->minute = (temp2 >> 6U) & 0x3Fu;

    tamperNum = (temp2 >> 12U) & 0x7u;

    return tamperNum;
}
#endif

#endif /* FSL_FEATURE_SOC_RTC_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/
