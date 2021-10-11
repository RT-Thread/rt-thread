/*
File Name    : yc_systick.c
Author       : Yichip
Version      : V1.0
Date         : 2018/03/27
Description  : systick encapsulation.
*/

#include "yc_systick.h"

tick SystickCount;

void Systick_Dealy_Ms(uint32_t MS)
{
	uint32_t ReloadValue;

	ReloadValue = MS * 9600;

	*SYSTICK_CSR &= ~(((uint32_t)1) << SYSTICK_CSR_ENABLE);
	*SYSTICK_RVR = ReloadValue; //Set the reload value
	*SYSTICK_CVR = 0;			//clear the current value
	*SYSTICK_CSR |= ((SYSTICK_SYSCLOCK << SYSTICK_CSR_CLKSOURCE) | (1 << SYSTICK_CSR_ENABLE));

	while (!(*SYSTICK_CVR == 0));
	*SYSTICK_RVR = 0;
}

uint32_t SysTick_Config(uint32_t ReloadValue)
{
	ReloadValue -= 1;
	if (!IS_RELOAD_VALUE(ReloadValue))
		return 1;

	*SYSTICK_CSR &= ~(((uint32_t)1) << SYSTICK_CSR_ENABLE);

	*SYSTICK_RVR = ReloadValue; //Set the reload value
	*SYSTICK_CVR = 0;			//clear the current value
	SystickCount = 0;			// Reset the overflow counter
	*SYSTICK_CSR |=
		((SYSTICK_SYSCLOCK << SYSTICK_CSR_CLKSOURCE) |
		 (1 << SYSTICK_CSR_ENABLE) |
		 (1 << SYSTICK_CSR_TICKINT));
	return 0;
}

tick SysTick_GetTick()
{
	return SystickCount;
}

Boolean SysTick_IsTimeOut(tick start_tick, int interval)
{
	start_tick = SysTick_GetTick() - start_tick;
	if (start_tick < 0)
		start_tick += TICK_MAX_VALUE;
	if (((start_tick * (*SYSTICK_RVR)) / (CPU_MHZ / 1000)) >= interval)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint32_t SysTick_GetRelativeTime(tick start_tick)
{
	start_tick = SysTick_GetTick() - start_tick;
	if (start_tick < 0)
		start_tick += TICK_MAX_VALUE;
	return ((start_tick * (*SYSTICK_RVR)) / (CPU_MHZ / 1000));
}
