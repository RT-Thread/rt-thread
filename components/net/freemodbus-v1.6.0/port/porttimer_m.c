/*
 * FreeModbus Libary: STM32 Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer_m.c,v 1.60 2013/08/13 15:07:05 Armink add Master Functions$
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"

#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED
/* ----------------------- Variables ----------------------------------------*/
static USHORT usT35TimeOut50us;
static USHORT usPrescalerValue = 0;

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR(void);

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBMasterPortTimersInit(USHORT usTimeOut50us)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//====================================时钟初始化===========================
	//使能定时器2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//====================================定时器初始化===========================
	//定时器时间基配置说明
	//HCLK为72MHz，APB1经过2分频为36MHz
	//TIM2的时钟倍频后为72MHz（硬件自动倍频,达到最大）
	//TIM2的分频系数为3599，时间基频率为72 / (1 + Prescaler) = 20KHz,基准为50us
	//TIM最大计数值为usTim1Timerout50u	
	usPrescalerValue = (uint16_t) (SystemCoreClock / 20000) - 1;
	//保存T35定时器计数值
	usT35TimeOut50us = usTimeOut50us; 

	//预装载使能
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	//====================================中断初始化===========================
	//设置NVIC优先级分组为Group2：0-3抢占式优先级，0-3的响应式优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//清除溢出中断标志位
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	//定时器3溢出中断关闭
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	//定时器3禁能
	TIM_Cmd(TIM2, DISABLE);
	return TRUE;
}

void vMBMasterPortTimersT35Enable()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Set current timer mode,don't change it.*/
	vMBMasterSetCurTimerMode(MB_TMODE_T35);

	TIM_TimeBaseStructure.TIM_Prescaler = usPrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = (uint16_t) usT35TimeOut50us;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}

void vMBMasterPortTimersConvertDelayEnable()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Set current timer mode,don't change it.*/
	vMBMasterSetCurTimerMode(MB_TMODE_CONVERT_DELAY);

	TIM_TimeBaseStructure.TIM_Prescaler = usPrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(MB_MASTER_DELAY_MS_CONVERT * 1000 / 50);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}

void vMBMasterPortTimersRespondTimeoutEnable()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Set current timer mode,don't change it.*/
	vMBMasterSetCurTimerMode(MB_TMODE_RESPOND_TIMEOUT);

	TIM_TimeBaseStructure.TIM_Prescaler = usPrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(MB_MASTER_TIMEOUT_MS_RESPOND * 1000 / 50);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}

void vMBMasterPortTimersDisable()
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, DISABLE);
}

void prvvTIMERExpiredISR(void)
{
	(void) pxMBMasterPortCBTimerExpired();
}

void TIM2_IRQHandler(void)
{
	rt_interrupt_enter();
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);	     //清中断标记
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	 //清除定时器TIM2溢出中断标志位
		prvvTIMERExpiredISR();
	}
	rt_interrupt_leave();
}

#endif
