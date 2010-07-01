/*
 * File      : mbmaster.c
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
#include "rtthread.h"
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbconfig.h"
#include "mbframe.h"
#include "mbproto.h"
#include "mbfunc.h"

eMBErrorCode eMBMReadHoldingRegisters  (UCHAR ucSlaveAddress, USHORT usRegStartAddress, 
			UBYTE ubNRegs, UBYTE arusBufferOut[]) 
{
	static UCHAR ucMBFrame[5];
	eMBErrorCode eStatus = MB_ENOERR;
	eMBEventType eEvent;
	static UCHAR ucRcvAddress;
	static USHORT usLength;
	UCHAR *ucRcvFrame;

	/* make up request frame */	
	ucMBFrame[0] = MB_FUNC_READ_HOLDING_REGISTER;
	ucMBFrame[1] = (UCHAR)(usRegStartAddress >> 8);
	ucMBFrame[2] = (UCHAR)(usRegStartAddress);
	ucMBFrame[3] = (UCHAR)(ubNRegs >> 8);
	ucMBFrame[4] = (UCHAR)(ubNRegs);	
	 
	/* send request frame to slave device */
	eStatus = eMBRTUSend( ucSlaveAddress, ucMBFrame, 5 );

	/* wait on receive event */
	if( xMBPortEventGet( &eEvent ) == TRUE )
	{		
		eStatus = eMBRTUReceive( &ucRcvAddress, &ucRcvFrame, &usLength );

		if( eStatus == MB_ENOERR )
		{
			/* Check if the frame is for us. If not ignore the frame. */
			if( ( ucRcvAddress == ucSlaveAddress ) || ( ucRcvAddress == MB_ADDRESS_BROADCAST ) )
			{
				RT_ASSERT(ucRcvFrame[0] == MB_FUNC_READ_HOLDING_REGISTER);
				RT_ASSERT(ucRcvFrame[1] == 2*ubNRegs)

				rt_memcpy((UCHAR *)arusBufferOut, &ucRcvFrame[2], 2*ubNRegs);
			}
		}
	}
	else eStatus = MB_ETIMEDOUT;

	return eStatus;
}

/*! @fn eMBErrorCode eMBMReadCoils  (UCHAR ucSlaveAddress, USHORT usCoilStartAddress,
			UBYTE ubNCoils, USHORT arusBufferOut[])
** @brief  request coils
** @details
** @param     ucSlaveAddress slave station address :from 1 to 247(max)
** @param     usCoilStartAddress coils address
** @param     ubNCoils  request coils number
** @param     arusBufferOut  response packet buf
** @return    eMBErrorCode
** @author   LiJin
** @date     2010-04-07
** @note
*/
eMBErrorCode eMBMReadCoils  (UCHAR ucSlaveAddress, USHORT usCoilStartAddress,
			UBYTE ubNCoils, UBYTE arusBufferOut[])
{
	static UCHAR ucMBFrame[5];
	eMBErrorCode eStatus = MB_ENOERR;
	eMBEventType eEvent;
	static UCHAR ucRcvAddress;
	static USHORT usLength;
	UCHAR *ucRcvFrame;

	/* make up request frame */
	ucMBFrame[0] = MB_FUNC_READ_COILS;
	ucMBFrame[1] = (UCHAR)(usCoilStartAddress >> 8);
	ucMBFrame[2] = (UCHAR)(usCoilStartAddress);
	ucMBFrame[3] = (UCHAR)(ubNCoils >> 8);
	ucMBFrame[4] = (UCHAR)(ubNCoils);

	/* send request frame to slave device */
	eStatus = eMBRTUSend( ucSlaveAddress, ucMBFrame, 5 );

	/* wait on receive event */
	if( xMBPortEventGet( &eEvent ) == TRUE )
	{
		eStatus = eMBRTUReceive( &ucRcvAddress, &ucRcvFrame, &usLength );
		if( eStatus == MB_ENOERR )
		{
			/* Check if the frame is for us. If not ignore the frame. */
			if( ucRcvAddress == ucSlaveAddress )
			{
				RT_ASSERT(ucRcvFrame[0] == MB_FUNC_READ_COILS);

				rt_memcpy((UCHAR *)arusBufferOut, &ucRcvFrame[2], ucRcvFrame[1]);
			}
		}
	}
	else eStatus = MB_ETIMEDOUT;

	return eStatus;

}

