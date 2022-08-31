/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_rtc.h"

/* Initialize RTC. */
void RTC_Init(void)
{
    /* Open access rights. */
    RCC->BDCR |= RCC_BDCR_DBP_MASK;

    /* Reset BKP. */
    RCC->BDCR |= RCC_BDCR_BDRST_MASK;
    RCC->BDCR &= ~RCC_BDCR_BDRST_MASK;

    /* Enable clock source. */
    RCC->BDCR |= RCC_BDCR_RTCSEL(1u);
    RCC->BDCR &= ~RCC_BDCR_LSEON_MASK;
    RCC->BDCR |= RCC_BDCR_LSEON_MASK;

    /* Clear register synchronization status. */
    RTC->CRL &= ~RTC_CRL_RSF_MASK;
}

/* Enable or disable access to RTC and backing registers. */
void RTC_EnableAccess(bool enable)
{
    if (enable)
    {
        RCC->BDCR |= RCC_BDCR_DBP_MASK;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_DBP_MASK;
    }
}

/* Enable backup domain software reset, the register of BKP is reset by the backup domain, not reset during power reset and system reset. */
void RTC_EnableReset(bool enable)
{
    if (enable)
    {
        RCC->BDCR |= RCC_BDCR_BDRST_MASK;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_BDRST_MASK;
    }
}

/* Get the current status flags of the RTC module. */
uint32_t RTC_GetStatus(void)
{
    return RTC->CRL;
}

/* Clear the status flag of the RTC module. */
void RTC_ClearStatus(uint32_t status)
{
    RTC->CRL &= ~status;
}

/* Get RTC clock source status. */
uint32_t RTC_GetClockStatus(void)
{
    return RCC->BDCR;
}

/* Enable RTC clock. */
void RTC_Enable(bool enable)
{
    if (enable)
    {
        RCC->BDCR |= RCC_BDCR_RTCEN_MASK;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_RTCEN_MASK;
    }
}

/* Enable or disable the configuration mode, enable to enter configuration mode, this is a precondition for registers to write data. */
void RTC_EnableConf(bool enable)
{
    if (enable)
    {
        RTC->CRL |= RTC_CRL_CNF_MASK;
    }
    else
    {
        RTC->CRL &= ~RTC_CRL_CNF_MASK;
    }
}

/* Setup prescaler register, open configration module before put data into RTC register. */
void RTC_PutPrescalerData(uint32_t div)
{
    RTC->CRL |= RTC_CRL_CNF_MASK;  /* Enable the configuration mode. */
    RTC->PRLH = div >> 16u;        /* Setup the upper 16-bit value of prescaler. */
    RTC->PRLL = div;               /* Setup the lower 16-bit value of prescaler. */
    RTC->CRL &= ~RTC_CRL_CNF_MASK; /* Disable the configuration mode. */
}

/* Setup counter register, open configration module before put data into RTC register. */
void RTC_PutCounterData(uint32_t cnt)
{
    RTC->CRL |= RTC_CRL_CNF_MASK;  /* Enable the configuration mode. */
    RTC->CNTH = cnt >> 16u;        /* Setup the upper 16-bit value of counter. */
    RTC->CNTL = cnt;               /* Setup the lower 16-bit value of counter. */
    RTC->CRL &= ~RTC_CRL_CNF_MASK; /* Disable the configuration mode. */
}

/* Setup alarm register, open configration module before put data into RTC register. */
void RTC_PutAlarmData(uint32_t alarm)
{
    RTC->CRL |= RTC_CRL_CNF_MASK;  /* Enable the configuration mode. */
    RTC->ALRH = alarm >> 16u;      /* Setup the upper 16-bit value of alarm counter. */
    RTC->ALRL = alarm;             /* Setup the lower 16-bit value of alarm counter. */
    RTC->CRL &= ~RTC_CRL_CNF_MASK; /* Disable the configuration mode. */
}

/* Get the data from counter of I2C module. */
uint32_t RTC_GetCounterData(void)
{
    return ( (RTC->CNTH << 16u) | RTC->CNTL );
}

/* Get alarm count value which is used to alarm interrupt. */
uint32_t RTC_GetAlarmData(void)
{
    return ( (RTC->ALRH << 16u) | RTC->ALRL);
}

/* Enable RTC interrupt of RTC module. */
void RTC_EnableInterrupts(uint32_t interrupts, bool enable)
{
    if (enable)
    {
        RTC->CRH |= interrupts;
    }
    else
    {
        RTC->CRH &= ~interrupts;
    }
}

/* Get the interrupts status flags of the RTC module. */
uint32_t RTC_GetInterruptStatus(void)
{
    return RTC->CRL;
}

/* Clear the status of RTC interrupt. */
void RTC_ClearInterruptStatus(uint32_t interrupts)
{
    RTC->CRL &= ~interrupts;
}

/* Get RTC interrupt enable status. */
uint32_t RTC_GetEnabledInterrupts(void)
{
    return RTC->CRH;
}

/* Judging whether the current year is a leap year, an ordinary leap year or a century leap year. */
bool RTC_JudgeLeapYear(uint16_t years)
{
    if (years % 4u == 0u)
    {
        if (years % 100u == 0u)
        {
            if (years % 400u == 0u)
            {
                return true;  /* Century leap year. */
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true; /* Ordinary leap year. */
        }
    }
    else
    {
        return false;
    }
}

/* Month correction table, used for calculation of month. */
const uint8_t month_table[12u] = {31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u};

/* Setup initialization time. */
bool RTC_SetTimeBlocking(RTC_Init_Type * init, RTC_Time_Type * time)
{
    RTC_PutPrescalerData(init->Div);  /* Setup prescaler. */
    while ( (0u == (RTC_GetStatus() & RTC_STATUS_OPERATION) ) && (0u != (time->WaitTime--) ) )  /* Wait for write operation finish, only after the end of the previous write operation can new write be performed. */
    {
    }

    /* Calculate the total number of seconds of the current configuration time. */
    uint32_t seccnt = 0u;
    if ( (init->Years < init->LYears) || (init->Years > init->HYears) )   /* Exceeding the specified year. */
    {
        return false;
    }
    /* Calculate the number of seconds from the lowest years to the current setup years. */
    for (uint16_t years = init->LYears; years < init->Years; years++)
    {
        if ( RTC_JudgeLeapYear(years) )
        {
            seccnt += 31622400u;  /* The number of seconds in leap year is 31622400. */
        }
        else
        {
            seccnt += 31536000u;  /* The number of seconds in normal year is 31622400. */
        }
    }

    /* Add up the seconds of the previous month. */
    init->Months -= 1u;  /* The month count starts from 0 instead of 1, so current months - 1. */
    for (uint16_t months = 0u; months < init->Months; months++)
    {
        seccnt += (uint32_t)month_table[months] * 86400u;  /* Calculate the number of seconds of months, the total number of seconds in a day is 86400. */
        if ( ( RTC_JudgeLeapYear(init->Years) ) && (months == 1u) )  /* The time is in a leap year and february, add the number of seconds in one day. */
        {
            seccnt += 86400u;  /* The number of seconds in day is 86400. */
        }
    }
    /* Add up the seconds of the previous date. */
    seccnt += (uint32_t)(init->Days - 1u) * 86400u;  /* The day set for initialization is less than 24 hours, which needs to be subtracted by one day. */
    seccnt += (uint32_t)(init->Hours) * 3600u;  /* There are 3600 seconds in a hour. */
    seccnt += (uint32_t)(init->Mins) * 60u;   /* There are 60 seconds in a minute. */
    seccnt += (init->Secs);


    while ( (0u == (RTC_GetStatus() & RTC_STATUS_OPERATION)) && (0u != (time->WaitTime--) ) )  /* Wait for write operation finish, only after the end of the previous write operation can new write be performed. */
    {
    }

    /* Configrate counter value. */
    RTC_PutCounterData(seccnt);  /* Put data into counter. */
    while ( ( 0u == (RTC_GetStatus() & RTC_STATUS_OPERATION) ) && (0u != (time->WaitTime--) ) )  /* Wait for write operation finish. */
    {
    }
    if (0u == time->WaitTime)   /* Timeout. */
    {
        return false;
    }

    return true;
}

/* Calculate and get current time. */
void RTC_CalcTimeBlocking(RTC_Init_Type * init, RTC_Time_Type * time)
{
    while ( 0u == (RTC_GetStatus() & RTC_STATUS_SYNC) && (0u != time->WaitTime) )  /* Wait for register synchronization, only register synchronization can read RTC register. */
    {
        time->WaitTime--;
    }
    uint32_t count = RTC_GetCounterData();  /* Get current seconds count. */

    /* Calculated in days. */
    uint16_t years = init->LYears;
    uint32_t days = count / 86400u;

    for (; days >= 365u; days -= 365u)
    {
        if ( RTC_JudgeLeapYear(years) )  /* Determine whether it is a leap year. */
        {
            if (days >= 366u)
            {
                days -= 1u;
            }
            else
            {
                break;
            }
        }
        years++;
    }
    init->Years = years;  /* Get current years. */

    uint16_t months = 0u;
    for (; days >= 28u; days -= 28u)
    {
        if ( ( true == RTC_JudgeLeapYear(init->Years) ) && (months == 1u) )  /* The time is February of leap year. */
        {
            if (days >= 29u)
            {
                days -= 1u;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (days >= month_table[months])  /* Reach the maximum number of days in the current month. */
            {
                days = days - month_table[months] + 28u;
            }
            else
            {
                break;
            }
        }
        months++;
    }
    init->Months = months + 1u;  /* Get current months. */
    init->Days   = days   + 1u;   /* Get current days. */
    init->Hours  = ( count % 86400u) / 3600u;  /* Get current hours. */
    init->Mins   = ((count % 86400u) % 3600u) / 60u;  /* Get current minutes. */
    init->Secs   = ((count % 86400u) % 3600u) % 60u;  /* Get current seconds. */
}

/* Setup the alarm response time. */
bool RTC_SetAlarmBlocking(RTC_Time_Type * time)
{
    RTC_EnableInterrupts(RTC_INT_ALARM, true);  /* Enable alarm interrupt. */
    while ( 0u == (RTC_GetStatus() & RTC_STATUS_SYNC) && (0u != time->WaitTime) )  /* Wait for register synchronization, only register synchronization can read RTC register. */
    {
        time->WaitTime--;
    }
    uint32_t value = RTC_GetCounterData();  /* Get the current total number of seconds. */
    RTC_PutAlarmData(value + time->AlarmTime);  /* Set alarm respond time. */
    while ( 0u == (RTC_GetStatus() & RTC_STATUS_OPERATION) && (0u != time->WaitTime) )  /* Wait for write operation finish. */
    {
        time->WaitTime--;
    }
    if (0u == time->WaitTime)
    {
        return false;
    }
    return true;
}

/* RTC interrupt request handler. */
void RTC_TimeHandler(RTC_Init_Type * init, RTC_Time_Type * time, uint32_t interrupts)
{
    /* Seconds interrupt. */
    if ( ( 0u == (interrupts & RTC_INT_ALARM) ) && ( 1u == (interrupts & RTC_INT_SEC) ) )
    {
        RTC_CalcTimeBlocking(init, time);  /* Get current time. */
        if (time->SecDoneCallback)
        {
            (*(time->SecDoneCallback))((void *)time);  /* Callback when seconds interrupt done. */
        }
    }

    /* Alarm interrupt. */
    if (0u != (interrupts & RTC_INT_ALARM) ) /* When the alarm count value is the same as the current count value, the alarm clock interrupt is generated. */
    {
        RTC_CalcTimeBlocking(init, time);  /* Get current time. */
        RTC_ClearInterruptStatus(RTC_INT_ALARM);  /* Clear alarm interrupt status flag. */
        if (time->AlarmDoneCallback)
        {
            (*(time->AlarmDoneCallback))((void *)time);  /* Callback when alarm interrupt done. */
        }
    }
    RTC_ClearInterruptStatus(RTC_INT_SEC | RTC_INT_OVERFLOW);  /* Clear seconds interrupt status flag and overflow status flag. */
}

/* EOF. */

