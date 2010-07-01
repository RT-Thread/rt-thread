/*
 * File      : porttimer.c
 * This file is part of freemodbus in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-04     yi.qiu      first version
 */

/* ----------------------- Platform includes --------------------------------*/
#include <rtthread.h>

#include <s3c24x0.h>
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR( void );
extern rt_uint32_t PCLK;

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit(USHORT usTim1Timerout50us)
{
	/* all are interrupt mode,set Timer 3 MUX 1/4 */
	TCFG1  &= 0xffff0fff;
	TCFG1  |= 0x00001000;

	TCNTB3 = (rt_int32_t)(usTim1Timerout50us*(PCLK/ (4 *16* 1000))) - 1;
	/* manual update */
	TCON = TCON & (~(0x0f<<16)) | (0x02<<16);
	/* install interrupt handler */
	rt_hw_interrupt_install(INTTIMER3, prvvTIMERExpiredISR, RT_NULL);
	rt_hw_interrupt_umask(INTTIMER3);

	/* start timer3, reload */
	TCON = TCON & (~(0x0f<<16)) | (0x09<<16);

	return TRUE;
}

void vMBPortTimersEnable(void)
{
	/* start timer4, reload */
	TCON = TCON & (~(0x0f<<16)) | (0x09<<16);
}

void vMBPortTimersDisable(void)
{
	TCON = TCON & (~(0x01<<16));
}

static void prvvTIMERExpiredISR( void )
{
	(void)pxMBPortCBTimerExpired();
}

