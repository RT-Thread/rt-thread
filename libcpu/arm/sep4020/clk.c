/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-20     zchong      first version
 */

#include <rtthread.h>
#include "sep4020.h"

#define	CLK_IN	        4000000		/* Fin = 4.00MHz  */
#define SYSCLK		    72000000	/* system clock we want */

#define CLK_ESRAM		0
#define CLK_LCDC		1
#define CLK_PWM			2
#define CLK_DMAC		3
#define CLK_EMI			4
#define CLK_MMCSD		5
#define CLK_SSI			7
#define CLK_UART0		8
#define CLK_UART1		9
#define CLK_UART2		10
#define CLK_UART3		11
#define CLK_USB			12
#define CLK_MAC			13
#define CLK_SMC			14
#define CLK_I2C			15
#define CLK_GPT			16

static void rt_hw_set_system_clock(void)
{
	rt_uint8_t pv;

	/* pv value*/
	pv  = SYSCLK/2/CLK_IN;
	/* go to normal mode*/
	*(RP)PMU_PMDR = 0x01;
	/* set the clock */
	*(RP)PMU_PMCR = 0x4000 | pv;
	/* trige configurate*/
	*(RP)PMU_PMCR = 0xc000 | pv;
}

static void rt_hw_set_usb_clock(void)
{
	/* set the clock */
	*(RP)PMU_PUCR = 0x000c;
	/* trige configurate*/
	*(RP)PMU_PMCR = 0x800c;

}

/**
 * @brief System Clock Configuration
 */
void rt_hw_clock_init(void)
{
	/* set system clock */
	rt_hw_set_system_clock();
	/* set usb clock */
	rt_hw_set_usb_clock();
}

/**
 * @brief Get system clock
 */
rt_uint32_t rt_hw_get_clock(void)
{
	rt_uint32_t val;
	rt_uint8_t pv, pd, npd;

	/* get PMCR value */
	val =*(RP) PMU_PMCR;
	/* get NPD */
	npd = (val >> 14) & 0x01;
	/* get PD  */
	pd  = (val >> 10) & 0x0f;
	/* get PV  */
	pv  = val & 0x7f;
	/* caculate the system clock */
	if(npd)
		val = 2 * CLK_IN * pv;
	else
		val = CLK_IN * pv / (pd + 1);

    return(val);
}

/**
 * @brief Enable module clock
 */
 void rt_hw_enable_module_clock(rt_uint8_t module)
 {

 }

/**
 * @brief Disable module clock
 */
  void rt_hw_disable_module_clock(rt_uint8_t module)
 {

 }

