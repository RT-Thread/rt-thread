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

#ifndef __CORE_TIMER_H__
#define __CORE_TIMER_H__

typedef enum
{
    TIMER_SN_START = 0,
    TIMER_SN_MAX,
}STATIC_TIMER_ENUM;

typedef struct Timer_InfoStruct Timer_t;

/*********************************TimerList*****************************************/

void Timer_Init(void);
//void Timer_Task(void *Param);
//void Timer_Run(void);
Timer_t * Timer_Create(CBFuncEx_t CB, void *Param, void *NotifyTask);
Timer_t * Timer_GetStatic(uint32_t Sn, CBFuncEx_t CB, void *Param, void *NotifyTask);
int Timer_Start(Timer_t *Timer, uint64_t Tick, uint8_t IsRepeat);
int Timer_StartMS(Timer_t *Timer, uint32_t MS, uint8_t IsRepeat);
int Timer_StartUS(Timer_t *Timer, uint32_t US, uint8_t IsRepeat);
void Timer_Stop(Timer_t *Timer);
void Timer_Release(Timer_t *Timer);
uint32_t Timer_NextToRest(void);
uint8_t Timer_IsRunning(Timer_t *Timer);
void Timer_PrintAll(void);
#endif
