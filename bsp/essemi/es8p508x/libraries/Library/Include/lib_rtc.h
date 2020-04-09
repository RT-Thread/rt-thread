/*********************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名:  lib_rtc.h
 *作  者:  WangMX
 *版  本:  V1.00
 *日  期:  2017/07/14
 *描  述:  RTC模块程序头文件
 *备  注:  适用于HRSDK-GDB-ES8P508x V1.1
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 **********************************************************/
#ifndef __LIBRTC_H__
#define __LIBRTC_H__

#include "ES8P508x.h"
#include "type.h"

/*RTC时钟源选择*/
typedef enum
{
    RTC_LOSC = 0x0,     //外部32768HZ时钟 RTC精确计时
    RTC_LRC  = 0x1,     //内部LRC时钟 RTC非精确计时
    RTC_PLCK_256 = 0x2, //PLCLK/256 RTC用作普通计数器
    RTC_PLCK = 0x3,     //PCLK RTC用作普通计数器
}RTC_TYPE_CLKS;

/*RTC时钟12/24小时制选择*/
typedef enum
{
    RTC_HOUR12 = 0x0, //12小时制
    RTC_HOUR24 = 0x1, //24小时制
}RTC_TYPE_TIME;

/* RTC中断源选择 */
typedef enum {
    RTC_Interrupt_Source_Second = 0x001,    // 秒中断
    RTC_Interrupt_Source_Minute = 0x002,    // 分中断
    RTC_Interrupt_Source_Hour = 0x004,      // 小时中断
    RTC_Interrupt_Source_Day = 0x008,       // 天中断
    RTC_Interrupt_Source_Month = 0x010,     // 月中断
    RTC_Interrupt_Source_DayALE = 0x100,    // 日闹钟中断
    RTC_Interrupt_Source_WeekALE = 0x200,   // 周闹钟中断
} RTC_Interrupt_Source;


/********************* RTC模块函数声明 *********************/
void RTC_Init(RTC_TYPE_CLKS CLKx,RTC_TYPE_TIME HOURx);
uint32_t RTC_ReadHourmode(void);
uint32_t RTC_ReadSecond(void);
uint32_t RTC_ReadMinute(void);
uint32_t RTC_ReadHour(uint32_t *meridiem);
uint32_t RTC_ReadDay(void);
uint32_t RTC_ReadMonth(void);
uint32_t RTC_ReadYear(void);
uint32_t RTC_ReadWeek(void);

ErrorStatus RTC_WriteSecond(uint32_t second);
ErrorStatus RTC_WriteMinute(uint32_t minute);
ErrorStatus RTC_WriteHour(uint32_t hour, uint32_t meridiem);
ErrorStatus RTC_WriteDay(uint32_t day);
ErrorStatus RTC_WriteMonth(uint32_t month);
ErrorStatus RTC_WriteYear(uint32_t year);
ErrorStatus RTC_WriteWeek(uint32_t week);

uint32_t RTC_ReadWeekAlarmMinute(void);
uint32_t RTC_ReadWeekAlarmHour(uint32_t *meridiem);
uint32_t RTC_ReadWeekAlarmWeek(void);
uint32_t RTC_ReadDayAlarmMinute(void);
uint32_t RTC_ReadDayAlarmHour(uint32_t *meridiem);

ErrorStatus RTC_WriteWeekAlarmMinute(uint32_t minute);
ErrorStatus RTC_WriteWeekAlarmHour(uint32_t hour, uint32_t meridiem);
ErrorStatus RTC_WriteWeekAlarmWeek(uint32_t week);
ErrorStatus RTC_WriteDayAlarmMinute(uint32_t minute);
ErrorStatus RTC_WriteDayAlarmHour(uint32_t hour, uint32_t meridiem);

void RTC_InterruptEnable(RTC_Interrupt_Source src);
void RTC_InterruptDisable(RTC_Interrupt_Source src);
ITStatus RTC_GetITStatus(RTC_Interrupt_Source src);
FlagStatus RTC_GetFlagStatus(RTC_Interrupt_Source src);
void RTC_ClearITPendingBit(RTC_Interrupt_Source src);

#endif

/*************************END OF FILE**********************/
