/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "user.h"

static int32_t RTC_DummyCB(void *pData, void *pParam)
{
    DBG("!");
    return 0;
}

static CBFuncEx_t prvRTCCB;
static void *prvParam;

static void RTC_IrqHandler(int32_t Line, void *pData)
{
    RTC->RTC_INTCLR = 1;
    ISR_OnOff(RTC_IRQn, 0);
    prvRTCCB(pData, prvParam);
}

void RTC_GlobalInit(void)
{
    int8_t Buf[4][6];
    LongInt Tamp;
    char *strMon[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    int Day,Year,Mon,Hour,Min,Sec,i;
    CmdParam CP;
    Date_UserDataStruct BuildDate;
    Time_UserDataStruct BuildTime;
    prvRTCCB = RTC_DummyCB;
    if (!RTC->RTC_REF)
    {
        DBG("rtc lost power!");
        memset(&CP, 0, sizeof(CP));
        memset(Buf, 0, sizeof(Buf));
        CP.param_max_len = 6;
        CP.param_max_num = 4;
        CP.param_str = (int8_t *)Buf;
        CmdParseParam(__DATE__, &CP, ' ');
        Mon = 0;
        for (i = 0; i < 12; i++)
        {
            if (!strcmp(strMon[i], Buf[0]))
            {
                Mon = i + 1;
            }
        }

        if (Buf[1][0])
        {
            Day = strtol(Buf[1], NULL, 10);
            Year = strtol(Buf[2], NULL, 10);
        }
        else
        {
            Day = strtol(Buf[2], NULL, 10);
            Year = strtol(Buf[3], NULL, 10);
        }


        CP.param_num = 0;
        memset(Buf, 0, sizeof(Buf));

        CP.param_str = (int8_t *)Buf;
        CmdParseParam(__TIME__, &CP, ':');
        Hour = strtol(Buf[0], NULL, 10);
        Min = strtol(Buf[1], NULL, 10);
        Sec = strtol(Buf[2], NULL, 10);
        BuildDate.Year = Year;
        BuildDate.Mon = Mon;
        BuildDate.Day = Day;
        BuildTime.Hour = Hour;
        BuildTime.Min = Min;
        BuildTime.Sec = Sec;
        RTC_SetDateTime(&BuildDate, &BuildTime, 0);
    }
#ifdef __BUILD_OS__
    ISR_SetPriority(RTC_IRQn, IRQ_MAX_PRIORITY + 1);
#else
    ISR_SetPriority(RTC_IRQn, 3);
#endif
    ISR_SetHandler(RTC_IRQn, RTC_IrqHandler, NULL);
//  RTC_GetDateTime(&uBuildDate, &uBuildTime);
//  DBG("%04u-%02u-%02u %02u:%02u:%02u", uBuildDate.Date.Year, uBuildDate.Date.Mon,
//          uBuildDate.Date.Day, uBuildTime.Time.Hour, uBuildTime.Time.Min,
//          uBuildTime.Time.Sec);

}

void RTC_SetStamp(uint32_t Stamp)
{
    while (!(RTC->RTC_CS & RTC_CS_READY)) {;}
    RTC->RTC_CS |= RTC_CS_CLR;
    while (RTC->RTC_CS & RTC_CS_CLR) {;}
    RTC->RTC_REF = Stamp;
}

void RTC_SetDateTime(Date_UserDataStruct *pDate, Time_UserDataStruct *pTime, uint8_t isForce)
{
    uint64_t Tamp = UTC2Tamp(pDate, pTime);
    uint32_t curTime;
    uint32_t newTime = (uint32_t)Tamp;
    while (!(RTC->RTC_CS & RTC_CS_READY)) {;}
    if (isForce)
    {
        RTC->RTC_CS |= RTC_CS_CLR;
        while (RTC->RTC_CS & RTC_CS_CLR) {;}
        RTC->RTC_REF = newTime;
    }
    else
    {
        RTC->RTC_CS |= RTC_CS_LOCK_TIM;
        curTime = RTC->RTC_TIM;
        RTC->RTC_CS &= ~RTC_CS_LOCK_TIM;
        curTime += RTC->RTC_REF;
        if (newTime > curTime)
        {
            RTC->RTC_CS |= RTC_CS_CLR;
            while (RTC->RTC_CS & RTC_CS_CLR) {;}
            RTC->RTC_REF = newTime;
        }
    }
}

void RTC_GetDateTime(Date_UserDataStruct *pDate, Time_UserDataStruct *pTime)
{
    Tamp2UTC(RTC_GetUTC(), pDate, pTime, 0);
}

uint64_t RTC_GetUTC(void)
{
    uint64_t curTime;
    while (!(RTC->RTC_CS & RTC_CS_READY)) {;}
    RTC->RTC_CS |= RTC_CS_LOCK_TIM;
    curTime = RTC->RTC_TIM;
    RTC->RTC_CS &= ~RTC_CS_LOCK_TIM;
    curTime += RTC->RTC_REF;
    return curTime;
}

void RTC_SetAlarm(uint32_t TimeSecond, CBFuncEx_t CB, void *pParam)
{
    while (!(RTC->RTC_CS & RTC_CS_READY)) {;}
    RTC->RTC_INTCLR = 1;
    RTC->RTC_CS &= ~RTC_CS_ALARM_EN;
    RTC->RTC_CS |= RTC_CS_LOCK_TIM;
    RTC->RTC_ARM = RTC->RTC_TIM + TimeSecond;
    RTC->RTC_CS &= ~RTC_CS_LOCK_TIM;
    if (CB)
    {
        prvRTCCB = CB;
    }
    else
    {
        prvRTCCB = RTC_DummyCB;
    }
    prvParam = pParam;
    RTC->RTC_CS |= RTC_CS_ALARM_EN;
    ISR_OnOff(RTC_IRQn, 1);
}
