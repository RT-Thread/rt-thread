/*
 * File      : portevent.c
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

/* ----------------------- Modbus includes ----------------------------------*/
#include <rtthread.h>

#include "mb.h"
#include "mbport.h"

/* ----------------------- Variables ----------------------------------------*/
static struct rt_event event;

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortEventInit( void )
{
	rt_event_init(&event, "modbus", RT_IPC_FLAG_FIFO);

	return TRUE;
}

BOOL xMBPortEventPost( eMBEventType eEvent )
{
	/* only care abot EV_FRAME_RECEIVED event */
	if(eEvent == EV_FRAME_RECEIVED)
	{	
		rt_event_send(&event, 1<<eEvent);
	}
	return TRUE;
}

BOOL xMBPortEventGet( eMBEventType * eEvent )
{
	rt_uint32_t e;
	rt_int32_t time_out = 3000/(1000/RT_TICK_PER_SECOND);
		
	if(rt_event_recv(&event, (1<<EV_FRAME_RECEIVED),
			RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
			time_out, &e) == RT_EOK)
	{
		*eEvent = EV_FRAME_RECEIVED;
		return TRUE;
	}		
	else 
	{
		rt_kprintf("get event timeout\n");

		return FALSE;
	}	
}

