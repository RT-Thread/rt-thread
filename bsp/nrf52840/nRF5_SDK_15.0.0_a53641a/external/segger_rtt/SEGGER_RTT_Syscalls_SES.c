/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 2014 - 2017  SEGGER Microcontroller GmbH & Co. KG        *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT * Real Time Transfer for embedded targets         *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the RTT protocol and J-Link.                       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* o Redistributions in binary form must reproduce the above          *
*   copyright notice, this list of conditions and the following      *
*   disclaimer in the documentation and/or other materials provided  *
*   with the distribution.                                           *
*                                                                    *
* o Neither the name of SEGGER Microcontroller GmbH & Co. KG         *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       RTT version: 6.18a                                           *
*                                                                    *
**********************************************************************
---------------------------END-OF-HEADER------------------------------
File    : SEGGER_RTT_Syscalls_SES.c
Purpose : Reimplementation of printf, puts and __getchar using RTT 
          in SEGGER Embedded Studio.
          To use RTT for printf output, include this file in your 
          application.
Revision: $Rev: 4351 $
----------------------------------------------------------------------
*/
#include "sdk_config.h"
#if !defined(RETARGET_ENABLED) || RETARGET_ENABLED == 0
#if (defined __SES_ARM) || (defined __CROSSWORKS_ARM)
  
#include "SEGGER_RTT.h"
#include <stdarg.h>
#include <stdio.h>
#include "limits.h"
#include "__libc.h"
#include "__vfprintf.h"

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
//
// Select string formatting implementation.
//
// RTT printf formatting
//  - Configurable stack usage. (SEGGER_RTT_PRINTF_BUFFER_SIZE in SEGGER_RTT_Conf.h)
//  - No maximum string length.
//  - Limited conversion specifiers and flags. (See SEGGER_RTT_printf.c)
// Standard library printf formatting
//  - Configurable formatting capabilities.
//  - Full conversion specifier and flag support.
//  - Maximum string length has to be known or (slightly) slower character-wise output.
// 
// #define PRINTF_USE_SEGGER_RTT_FORMATTING    0 // Use standard library formatting
// #define PRINTF_USE_SEGGER_RTT_FORMATTING    1 // Use RTT formatting
//
#ifndef   PRINTF_USE_SEGGER_RTT_FORMATTING
  #define PRINTF_USE_SEGGER_RTT_FORMATTING    0
#endif
//
// If using standard library formatting, 
// select maximum output string buffer size or character-wise output.
//
// #define PRINTF_BUFFER_SIZE                  0 // Use character-wise output
// #define PRINTF_BUFFER_SIZE                128 // Default maximum string length
//
#ifndef   PRINTF_BUFFER_SIZE
  #define PRINTF_BUFFER_SIZE                128
#endif

#if PRINTF_USE_SEGGER_RTT_FORMATTING  // Use SEGGER RTT formatting implementation
/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/
int SEGGER_RTT_vprintf(unsigned BufferIndex, const char * sFormat, va_list * pParamList);

/*********************************************************************
*
*       Global functions, printf
*
**********************************************************************
*/
/********************************************************************* 
*
*       printf()
*
*  Function description
*    print a formatted string using RTT and SEGGER RTT formatting.
*/
int printf(const char *fmt,...) {
  int     n;
  va_list args;
  
  va_start (args, fmt);
  n = SEGGER_RTT_vprintf(0, fmt, &args);
  va_end(args);
  return n;
}

#elif PRINTF_BUFFER_SIZE == 0 // Use standard library formatting with character-wise output

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
static int _putchar(int x, __printf_tag_ptr ctx) {
  (void)ctx;
  SEGGER_RTT_Write(0, (char *)&x, 1);
  return x;
}

/*********************************************************************
*
*       Global functions, printf
*
**********************************************************************
*/
/********************************************************************* 
*
*       printf()
*
*  Function description
*    print a formatted string character-wise, using RTT and standard 
*    library formatting.
*/
int printf(const char *fmt, ...) {
  int         n;
  va_list     args;
  __printf_t  iod;
  
  va_start(args, fmt);
  iod.string    = 0;
  iod.maxchars  = INT_MAX;
  iod.output_fn = _putchar;
  SEGGER_RTT_LOCK();
  n = __vfprintf(&iod, fmt, args);
  SEGGER_RTT_UNLOCK();
  va_end(args);
  return n;
}

#else // Use standard library formatting with static buffer

/*********************************************************************
*
*       Global functions, printf
*
**********************************************************************
*/
/********************************************************************* 
*
*       printf()
*
*  Function description
*    print a formatted string using RTT and standard library formatting.
*/
int printf(const char *fmt,...) {
  int     n;
  char    aBuffer[PRINTF_BUFFER_SIZE];
  va_list args;
  
  va_start (args, fmt);
  n = vsnprintf(aBuffer, sizeof(aBuffer), fmt, args);
  if (n > (int)sizeof(aBuffer)) {
    SEGGER_RTT_Write(0, aBuffer, sizeof(aBuffer));
  } else if (n > 0) {
    SEGGER_RTT_Write(0, aBuffer, n);
  }
  va_end(args);
  return n;
}
#endif

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/
/********************************************************************* 
*
*       puts()
*
*  Function description
*    print a string using RTT.
*/
int puts(const char *s) {
  return SEGGER_RTT_WriteString(0, s);
}

/********************************************************************* 
*
*       __putchar()
*
*  Function description
*    Write one character via RTT.
*/
int __putchar(int x, __printf_tag_ptr ctx) {
  (void)ctx;
  SEGGER_RTT_Write(0, (char *)&x, 1);
  return x;
}

/********************************************************************* 
*
*       __getchar()
*
*  Function description
*    Wait for and get a character via RTT.
*/
int __getchar() {
  return SEGGER_RTT_WaitKey();
}

#endif
#endif
/****** End Of File *************************************************/
