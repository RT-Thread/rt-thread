/**
 * \file   consoleUtils.h
 *
 * \brief  This file contains the prototypes of the generic Console
 *         utility functions defined in utils/consoleUtils.c which allow
 *         user to configure the console type and redirect the I/O
 *         operations to the selected console Type.
 *
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

#ifndef _CONSOLEUTILS_H_
#define _CONSOLEUTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

enum consoleUtilsType
{
    CONSOLE_UART = 0,
    CONSOLE_DEBUGGER,
    CONSOLE_MAXTYPE
};

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

extern void ConsoleUtilsInit();
extern void ConsoleUtilsSetType(enum consoleUtilsType consoleFlag);
extern void ConsoleUtilsPrintf(const char *string, ...);
extern int ConsoleUtilsScanf(const char *format, ...);
extern char*  ConsoleUtilsGets(char *rxBuffer, int size);
extern void ConsoleUtilsPuts(char *string, int size);
extern void ConsoleUtilsPutChar(unsigned char byte);
extern unsigned char ConsoleUtilsGetChar(void);

#ifdef __cplusplus
}
#endif
#endif
