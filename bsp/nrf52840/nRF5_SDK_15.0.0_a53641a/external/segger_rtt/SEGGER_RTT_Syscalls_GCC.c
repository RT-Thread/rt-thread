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
File    : SEGGER_RTT_Syscalls_GCC.c
Purpose : Low-level functions for using printf() via RTT in GCC.
          To use RTT for printf output, include this file in your 
          application.
Revision: $Rev: 4351 $
----------------------------------------------------------------------
*/
#include "sdk_config.h"
#if !defined(RETARGET_ENABLED) || RETARGET_ENABLED == 0
#if defined(NRF_LOG_USES_RTT) && NRF_LOG_USES_RTT == 1
#if (defined __GNUC__) && !(defined __SES_ARM) && !(defined __CROSSWORKS_ARM)

#include <reent.h>  // required for _write_r
#include "SEGGER_RTT.h"


/*********************************************************************
*
*       Types
*
**********************************************************************
*/
//
// If necessary define the _reent struct 
// to match the one passed by the used standard library.
//
struct _reent;

/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/
int _write(int file, char *ptr, int len);
_ssize_t _write_r _PARAMS ((struct _reent *, int, const void *, size_t));

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _write()
*
* Function description
*   Low-level write function.
*   libc subroutines will use this system routine for output to all files,
*   including stdout.
*   Write data via RTT.
*/
int _write(int file, char *ptr, int len) {
  (void) file;  /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}

/*********************************************************************
*
*       _write_r()
*
* Function description
*   Low-level reentrant write function.
*   libc subroutines will use this system routine for output to all files,
*   including stdout.
*   Write data via RTT.
*/
_ssize_t _write_r _PARAMS((struct _reent *r, int file, const void *ptr, size_t len)) {
  (void) file;  /* Not used, avoid warning */
  (void) r;     /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}

#endif // #if (defined __GNUC__) && !(defined __SES_ARM) && !(defined __CROSSWORKS_ARM)
#endif // defined(NRF_LOG_USES_RTT) && NRF_LOG_USES_RTT == 1
#endif // !defined(RETARGET_ENABLED) || RETARGET_ENABLED == 0
/****** End Of File *************************************************/
