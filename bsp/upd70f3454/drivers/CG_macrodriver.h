/*
*******************************************************************************
* Copyright(C) NEC Electronics Corporation 2010
* All rights reserved by NEC Electronics Corporation.
* This program should be used on your own responsibility.
* NEC Electronics Corporation assumes no responsibility for any losses
* incurred by customers or third parties arising from the use of this file.
*
* This device driver was created by Applilet3 for V850ES/Jx3
* 32-Bit Single-Chip Microcontrollers
* Filename:	CG_macrodriver.h
* Abstract:	This file implements general head file.
* APIlib:	Applilet3 for V850ES/Jx3 V2.01 [20 Apr 2010]
* Device:	uPD70F3746
* Compiler:	IAR Systems ICCV850
* Creation date:	6/26/2010
*******************************************************************************
*/

#ifndef _MDSTATUS_
#define _MDSTATUS_
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include <intrinsics.h>
#include "io70f3454.h"
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	DI	__disable_interrupt
#define	EI	__enable_interrupt
#define	NOP	__no_operation
#define	HALT	__halt

/* Data type defintion */
typedef	unsigned long	ULONG;
typedef	signed long	SLONG;

typedef	unsigned int	UINT;
typedef	signed int	SINT;

typedef	unsigned short	USHORT;
typedef	signed short	SHORT;

typedef	unsigned char	UCHAR;
typedef	signed char	SCHAR;

typedef	unsigned char	BOOL;
typedef	unsigned short	MD_STATUS;

#define	MD_ON		1U
#define	MD_OFF		0U

#define	MD_TRUE		1U
#define	MD_FALSE	0U

#define MD_SET		1U
#define MD_CLEAR	0U

/* Status list definition */
#define	MD_STATUSBASE		0x00U
#define	MD_OK			(MD_STATUSBASE + 0x00U)	/* register setting OK */
#define	MD_RESET		(MD_STATUSBASE + 0x01U)	/* reset input */
#define	MD_SENDCOMPLETE		(MD_STATUSBASE + 0x02U)	/* send data complete */
#define	MD_ADDRESSMATCH		(MD_STATUSBASE + 0x03U)	/* IIC slave address match */
#define	MD_OVF			(MD_STATUSBASE + 0x04U)	/* timer count overflow */
#define	MD_SPT			(MD_STATUSBASE + 0x07U)	/* IIC stop */
#define	MD_NACK			(MD_STATUSBASE + 0x08U)	/* IIC no ACK */
#define	MD_SLAVE_SEND_END	(MD_STATUSBASE + 0x09U)	/* IIC slave send end */
#define	MD_SLAVE_RCV_END	(MD_STATUSBASE + 0x0AU)	/* IIC slave receive end */
#define	MD_MASTER_SEND_END	(MD_STATUSBASE + 0x0BU)	/* IIC master send end */
#define	MD_MASTER_RCV_END	(MD_STATUSBASE + 0x0CU)	/* IIC master receive end */
#define	MD_UNDEREXEC		(MD_STATUSBASE + 0x0DU)	/* DMA transfer under execute */
#define	MD_COMPLETED		(MD_STATUSBASE + 0x0EU)	/* DMA transfer completed */
#define MD_BUSY1		(MD_STATUSBASE + 0x0FU)	/* busy 1 */
#define MD_BUSY2		(MD_STATUSBASE + 0x10U)	/* busy 2 */

/* Error list definition */
#define	MD_ERRORBASE		0x80U
#define	MD_ERROR		(MD_ERRORBASE + 0x00U)	/* error */
#define	MD_RESOURCEERROR	(MD_ERRORBASE + 0x01U)	/* no resource available */
#define	MD_PARITYERROR		(MD_ERRORBASE + 0x02U)	/* UARTn parity error n=0,1,2 */
#define	MD_OVERRUNERROR		(MD_ERRORBASE + 0x03U)	/* UARTn overrun error n=0,1,2 */
#define	MD_FRAMEERROR		(MD_ERRORBASE + 0x04U)	/* UARTn frame error n=0,1,2 */
#define	MD_ARGERROR		(MD_ERRORBASE + 0x05U)	/* Error agrument input error */
#define	MD_TIMINGERROR		(MD_ERRORBASE + 0x06U)	/* Error timing operation error */
#define	MD_SETPROHIBITED	(MD_ERRORBASE + 0x07U)	/* setting prohibited */
#define	MD_ODDBUF		(MD_ERRORBASE + 0x08U)	/* in 16bit transfer mode,buffer size should be even */
#define	MD_DATAEXISTS		(MD_ERRORBASE + 0x09U)	/* Data to be transferred next exists in TXBn register */
#define	MD_STSERROR		(MD_ERRORBASE + 0x0AU)	/* CAN status error */
#define	MD_ALRDYSTART		(MD_ERRORBASE + 0x0BU)	/* CAN-controller is already started error */
#define	MD_NOMSG		(MD_ERRORBASE + 0x0CU)	/* CAN message not received */
#define	MD_ERROR1		(MD_ERRORBASE + 0x0DU)	/* error 1 */
#define	MD_ERROR2		(MD_ERRORBASE + 0x0EU)	/* error 2 */
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/

#endif
