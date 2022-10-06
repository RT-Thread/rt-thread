/**
 * \file   uartStdio.h
 *
 * \brief  This file contains the prototypes of the functions present in
 *         utils/src/uartStdio.c
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _UARTSTDIO_H_
#define _UARTSTDIO_H_

#include <stdarg.h>
#include "misc.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                    MACRO DEFINITIONS
****************************************************************************/

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

extern unsigned int UARTPuts(char *pTxBuffer, int numBytesToWrite);
extern char*  UARTGets(char *pRxBuffer, int numBytesToRead);
extern unsigned int UARTwrite(const char *pcBuf, unsigned int len);
extern void UARTPutc(unsigned char byteTx);
extern unsigned char UARTGetc(void);
extern void UARTStdioInit(void);
extern int UARTScanf(const char *format, va_list vaArg);
extern void UARTPrintf(const char *string, va_list vaArg);

/*****************************************************************************
**                      DEPRECATED API DECLARATIONS
******************************************************************************/
DEPRECATED(extern void UARTPutHexNum(unsigned int hexValue));
DEPRECATED(extern unsigned int UARTGetHexNum(void));
DEPRECATED(extern void UARTPutNum(int value));
DEPRECATED(extern int UARTGetNum(void));
DEPRECATED(extern void UARTprintf(const char *pcString, ...));

#ifdef __cplusplus
}
#endif
#endif
