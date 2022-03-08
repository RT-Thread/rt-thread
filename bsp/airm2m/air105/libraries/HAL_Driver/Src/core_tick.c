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

#include "bl_inc.h"
volatile static uint64_t PowerOnTickCnt;
volatile static uint64_t prvPeriod;
//
static void SystemTickIrqHandler( int32_t Line, void *pData)
{
    volatile uint32_t clr;
    clr = TIMM0->TIM[CORE_TICK_TIM].EOI;
    PowerOnTickCnt += prvPeriod;
}

uint64_t GetSysTick(void)
{
    volatile uint32_t clr;
    volatile uint64_t PowerOnTick;
    ISR_OnOff(CORE_TICK_IRQ, 0);
    PowerOnTick = PowerOnTickCnt + prvPeriod - TIMM0->TIM[CORE_TICK_TIM].CurrentValue;
    if (TIMM0->TIM[CORE_TICK_TIM].IntStatus)
    {
        ISR_OnOff(CORE_TICK_IRQ, 1);
        while(TIMM0->TIM[CORE_TICK_TIM].IntStatus){;}
        PowerOnTick = PowerOnTickCnt + prvPeriod - TIMM0->TIM[CORE_TICK_TIM].CurrentValue;
    }
    ISR_OnOff(CORE_TICK_IRQ, 1);
    return PowerOnTick;
}

uint64_t GetSysTickUS(void)
{
    return GetSysTick()/CORE_TICK_1US;
}

uint64_t GetSysTickMS(void)
{
    return GetSysTick()/CORE_TICK_1MS;
}


void SysTickDelay(uint32_t Tick)
{
    uint64_t Tick1 = GetSysTick();
    uint64_t Tick2 = Tick1 + Tick;
    while(Tick2 > GetSysTick()){;}
    return;
}

void SysTickDelayUntil(uint64_t StartTick, uint32_t Tick)
{
    uint64_t Tick1 = StartTick + Tick;
    while(Tick1 > GetSysTick()){;}
    return;
}

uint8_t SysTickCheckTimeout(uint64_t StartTick, uint32_t Tick)
{
    uint64_t Tick1 = StartTick + Tick;
    if (Tick1 > GetSysTick())
    {
        return 0;
    }
    return 1;
}

void CoreTick_Init(void)
{
    prvPeriod = SystemCoreClock;
    TIMM0->TIM[CORE_TICK_TIM].ControlReg = 0;
    TIMM0->TIM[CORE_TICK_TIM].LoadCount = prvPeriod - 1;
    TIMM0->TIM[CORE_TICK_TIM].ControlReg = TIMER_CONTROL_REG_TIMER_ENABLE|TIMER_CONTROL_REG_TIMER_MODE;
    ISR_OnOff(CORE_TICK_IRQ, 0);
    ISR_SetHandler(CORE_TICK_IRQ, SystemTickIrqHandler, NULL);
    ISR_SetPriority(CORE_TICK_IRQ, CORE_TICK_IRQ_LEVEL);
    ISR_OnOff(CORE_TICK_IRQ, 1);
}
