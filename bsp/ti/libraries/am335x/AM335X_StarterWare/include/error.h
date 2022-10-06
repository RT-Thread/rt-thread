/**
 * \file   error.h
 *
 * \brief  This files contains the macros for commonly used error code in
 *         StarterWare. These error codes are not specific to any module.
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


#ifndef ERROR_H__
#define ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "consoleUtils.h"

/* Successful completion of the functionality   */
#define S_PASS                  (0)
/* Generic failure code                         */
#define E_FAIL                  (-1)
/* Invalid parameter                            */
#define E_INVALID_PARAM         (-2)
/* Invalid operation                            */
#define E_INVALID_OPERATION     (-3)
/* Invalid index                                */
#define E_INVALID_INDEX         (-4)
/* Interrupt number not supported               */
#define E_INTR_NOT_SUPP         (-5)
/* Instance number not supported                */
#define E_INST_NOT_SUPP         (-6)
/* Invalid address                              */
#define E_INVALID_ADDR          (-7)
/* Invalid profile                              */
#define E_INVALID_PROFILE       (-8)
/* Invalid Chip Select                          */
#define E_INVALID_CHIP_SEL      (-9)

/*
** The input to the below macro are the macros which are defined above.
** For e.g. usage of PRINT_STATUS() will be PRINT_STATUS(E_FAIL) or
** PRINT_STATUS(S_PASS)
*/
/* Print the status */
#define PRINT_STATUS(x) (x >= 0) ? \
          ConsoleUtilsPrintf("\r\nSuccess! Passed with status code " #x "\n") \
          : ConsoleUtilsPrintf("\r\nError! Failed with status code " #x "\n")

#ifdef __cplusplus
}
#endif

#endif
