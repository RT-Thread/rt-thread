/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2017.03
 * \date 2014-12-26
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup EMBARC_DEBUG
 * \brief necessary definitions of debug
 */

#ifndef _EMBARC_DEBUG_H_
#define _EMBARC_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EMBARC_PRINTF
	#include "common/xprintf.h"
	#define EMBARC_PRINTF xprintf
#endif

/*
 * if you want to use DBG or dbg_printf,
 * please define DEBUG or DBG_LESS or DBG_MORE before include embARC_debug.h
 * DEBUG: enable debug print
 * DBG_LESS: enable less debug msg
 * DBG_MORE: enable more debug msg
 **/

#if defined(DEBUG)
#if defined(DEBUG_HOSTLINK)
#include <stdio.h>
#define DBG(fmt, ...)	printf(fmt, ##__VA_ARGS__)
#else
#define DBG(fmt, ...)	EMBARC_PRINTF(fmt, ##__VA_ARGS__)
#endif
#else
#define DBG(fmt, ...)
#endif

#define DBG_LESS_INFO	0x01    /* less debug  messages */
#define DBG_MORE_INFO	0x02    /* more debug  messages */


#if defined (DBG_LESS)
#define DBG_TYPE		(DBG_LESS_INFO)
#elif defined (DBG_MORE)
#define DBG_TYPE		((DBG_LESS_INFO) | (DBG_MORE_INFO))
#else
#define DBG_TYPE 		0
#endif

#if DBG_TYPE > 0
#define dbg_printf(type, fmt, ...) \
		if (((type) & DBG_TYPE))  { EMBARC_PRINTF(fmt, ##__VA_ARGS__); }
#else
#define dbg_printf(type, fmt, ...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H_ */
