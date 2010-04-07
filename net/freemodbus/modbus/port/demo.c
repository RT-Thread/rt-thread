/*
 * File      : demo.c
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
 * 2010-04-07     LiJin
 */
 
/* ----------------------- Platform includes --------------------------------*/
#include <rtthread.h>
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbconfig.h"
#include "mbframe.h"
#include "mbproto.h"
#include "mbfunc.h"


USHORT buf[256];


void rt_modbus_thread_entry(void* parameter)
{
	eMBErrorCode eStatus;
		
	eStatus = eMBInit( MB_RTU, 0x0A, 0, 115200, MB_PAR_EVEN );

	/* Enable the Modbus Protocol Stack. */
	eStatus = eMBEnable(  );
	rt_thread_delay(50);
	
	while(1)
	{

		/* request holding reg  */
		eMBMReadHoldingRegisters(0x0A, 0x1, 0x10, buf);
		rt_kprintf("stop\n");
		rt_thread_delay(100);
		/* request coils  */
		eMBMReadCoils(0x0A, 0x1, 128, buf);
		rt_thread_delay(100);

		//while(1);
	}
}

int modbus_demo_init(void)
{
	rt_thread_t modbus_thread;

	modbus_thread = rt_thread_create("modbus",
								rt_modbus_thread_entry, RT_NULL,
								2048, 20, 20);

	if (modbus_thread != RT_NULL)
		rt_thread_startup(modbus_thread);

	return 0;
}

eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	return MB_ENOREG;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
			eMBRegisterMode eMode )
{
	return MB_ENOREG;
}


eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
			eMBRegisterMode eMode )
{
	return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	return MB_ENOREG;
}

