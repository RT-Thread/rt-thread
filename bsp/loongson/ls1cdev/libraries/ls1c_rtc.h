/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-06     sundm75       first version
 */

 #ifndef __OPENLOONGSON_RTC_H
#define __OPENLOONGSON_RTC_H


#define RTC               ( (RTC_TypeDef* )LS1C_RTC_BASE)

typedef struct
{
  unsigned char Year;     /*0 ~ 99 */
  unsigned char Month;    /*1 ~ 12 */
  unsigned char Date;     /*1 ~ 31 */
  unsigned char Hours;    /*0 ~ 23 */
  unsigned char Minutes;  /*0 ~ 59 */
  unsigned char Seconds;  /*0 ~ 59 */
}RTC_TimeTypeDef; 

typedef struct
{
   unsigned long SYS_TOYWRITE0;
   unsigned long SYS_TOYWRITE1;
   unsigned long SYS_TOYREAD0;
   unsigned long SYS_TOYREAD1;
} RTC_TypeDef;

int  RTC_SetTime(RTC_TypeDef *hrtc, RTC_TimeTypeDef *sTime);
int  RTC_GetTime(RTC_TypeDef *hrtc, RTC_TimeTypeDef *sTime);

unsigned char RTC_IsLeapYear(unsigned int nYear);
unsigned char RTC_WeekDayNum(unsigned long nYear, unsigned char nMonth, unsigned char nDay);

#endif
