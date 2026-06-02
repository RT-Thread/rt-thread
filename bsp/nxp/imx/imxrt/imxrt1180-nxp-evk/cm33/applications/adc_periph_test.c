/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     tyustli      first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>
#include <fsl_rgpio.h>
#include <stdlib.h>
#include "fsl_lpadc.h"


static int adc_periph(int argc, char *argv[])
{
	int para=0;
	
	para = strtol(argv[1], NULL, 0);
	
	switch(para)
	{
		case 1: LPADC_Enable(ADC1, true); rt_kprintf("ADC1 is enabled\r\n"); break;
		
		case 2: 
		{
			LPADC_DoSoftwareTrigger(ADC1, 1U);  /* 1U is trigger0 mask. */
			rt_kprintf("ADC1 DoSoftwareTrigger0\r\n");
		}
		break;
		case 3: 
		{
			uint32_t cnt = LPADC_GetConvResultCount(ADC1, 0);
			rt_kprintf("ADC1 FIFO0 CovResultCount: %d\r\n", cnt);
		}break;
		case 4:
		{
			lpadc_conv_result_t ret;
			
			LPADC_GetConvResult(ADC1, &ret, 0);
			rt_kprintf("ADC1 index 0 commandIdSource: %x\r\n", ret.commandIdSource);
			rt_kprintf("ADC1 index 0 loopCountIndex: %x\r\n", ret.loopCountIndex);
			rt_kprintf("ADC1 index 0 triggerIdSource: %x\r\n", ret.triggerIdSource);
			rt_kprintf("ADC1 index 0 CovResult: %x\r\n", ret.convValue);
			
		}
		break;
		
		case 5: LPADC_Enable(ADC1, false); rt_kprintf("ADC1 is disabled\r\n");break;
		case 6:
		{
			uint32_t cnt = LPADC_GetConvResultCount(ADC1, 1);
			rt_kprintf("ADC1 FIFO1 CovResultCount: %d\r\n", cnt);
		} break;
		case 7:
		{
			lpadc_conv_result_t ret;
			while( !LPADC_GetConvResult(ADC1, &ret, 1) ) {
				
			}
			rt_kprintf("ADC1 index 1 commandIdSource: %x\r\n", ret.commandIdSource);
			rt_kprintf("ADC1 index 1 loopCountIndex: %x\r\n", ret.loopCountIndex);
			rt_kprintf("ADC1 index 1 triggerIdSource: %x\r\n", ret.triggerIdSource);
			rt_kprintf("ADC1 index 1 CovResult: %x\r\n", ret.convValue);
		} break;
	}
	
	return 0;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(adc_periph, adc peripheral test);

#if 0
/* ADC1_IRQn interrupt handler */
void ADC1_IRQHandler(void) {
  uint32_t trigger_status_flag;
  uint32_t status_flag;
	lpadc_conv_result_t ret;
	
	    /* enter interrupt */
    rt_interrupt_enter();
	rt_kprintf("this is in ADC1_IRQHandler.\r\n");
  /* Trigger interrupt flags */
  trigger_status_flag = LPADC_GetTriggerStatusFlags(ADC1);
	rt_kprintf("trigger_status_flag:%x.\r\n", trigger_status_flag);
  /* Interrupt flags */
  status_flag = LPADC_GetStatusFlags(ADC1);
	rt_kprintf("status_flag:%x.\r\n", status_flag);
  /* Clears trigger interrupt flags */
  LPADC_ClearTriggerStatusFlags(ADC1, trigger_status_flag);
  /* Clears interrupt flags */
  LPADC_ClearStatusFlags(ADC1, status_flag);

  /* Place your code here */
	rt_kprintf("---------------------------------------\r\n");
//	while( !LPADC_GetConvResult(ADC1, &ret, 0) ) {
//		
//	}
	LPADC_GetConvResult(ADC1, &ret, 0);
	rt_kprintf("ADC1 index 0 commandIdSource: %x\r\n", ret.commandIdSource);
	rt_kprintf("ADC1 index 0 loopCountIndex: %x\r\n", ret.loopCountIndex);
	rt_kprintf("ADC1 index 0 triggerIdSource: %x\r\n", ret.triggerIdSource);
	rt_kprintf("ADC1 index 0 CovResult: %x\r\n", ret.convValue);
	rt_kprintf("---------------------------------------\r\n");
  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
	
	/* leave interrupt */
    rt_interrupt_leave();
}
#endif