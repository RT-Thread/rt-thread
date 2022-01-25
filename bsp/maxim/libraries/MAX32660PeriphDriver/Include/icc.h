/**
 * @file    icc.h
 * @brief   Instruction Controller Cache(ICC) function prototypes and data types.
 */

/* ****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 *************************************************************************** */

/* Define to prevent redundant inclusion */
#ifndef _ICC_H_
#define _ICC_H_

/* **** Includes **** */
#include <stdint.h>
#include "icc_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup icc Internal Cache Controller (ICC)
 * @ingroup periphlibs
 * @{
 */ 

/**
 * @brief Enumeration type for the Cache ID Register
 */
typedef enum {
    ICC_CACHE_ID_RELNUM,	// Identifies the RTL release version
    ICC_CACHE_ID_PARTNUM,	// Specifies the value of C_ID Port Number
    ICC_CACHE_ID_CCHID		// Specifies the value of Cache ID
} icc_cache_id_t;

/**
 * @brief	Reads the data from the Cache Id Register.
 * @param	cid	Enumeration type for Cache Id Register.
 * @retval	Returns the contents of Cache Id Register. 
 */
int ICC_ID(icc_cache_id_t cid);

/**
 * @brief	Enable the instruction cache controller.
 */
void ICC_Enable(void);

/**
 * @brief	Disable the instruction cache controller.
 */
void ICC_Disable(void);

/**
 * @brief	Flush the instruction cache controller.
 */
void ICC_Flush(void);

/**@} end of group icc */

#ifdef __cplusplus
}
#endif

#endif /* _ICC_H_ */
