/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
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
 */

#ifndef _KERNEL_OS_RTTHREAD_OS_COMMON_H_
#define _KERNEL_OS_RTTHREAD_OS_COMMON_H_

#include <stdint.h>
#include <stdio.h>
#include "rtthread.h"
#include "rthw.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum  {
    OS_PRIORITY_IDLE            = 31, //(RT_THREAD_PRIORITY_MAX - 1) - 0,   // 31
    OS_PRIORITY_LOW             = 30, //(RT_THREAD_PRIORITY_MAX - 1) - 1,   // 30
    OS_PRIORITY_BELOW_NORMAL    = 29, //(RT_THREAD_PRIORITY_MAX - 1) - 2,   // 29
    OS_PRIORITY_NORMAL          = 10, //(RT_THREAD_PRIORITY_MAX) / (3),     // 10
    OS_PRIORITY_ABOVE_NORMAL    =  9, //(RT_THREAD_PRIORITY_MAX + 4) / (4), // 9
    OS_PRIORITY_HIGH            =  8, //(RT_THREAD_PRIORITY_MAX) / (5),     // 6
    OS_PRIORITY_REAL_TIME       =  1                                        // 1
} OS_Priority;

/**
 * @brief OS status definition
 */
typedef enum {
    OS_OK           = 0,    /* success */
    OS_FAIL         = -1,   /* general failure */
    OS_E_NOMEM      = -2,   /* out of memory */
    OS_E_PARAM      = -3,   /* invalid parameter */
    OS_E_TIMEOUT    = -4,   /* operation timeout */
    OS_E_ISR        = -5,   /* not allowed in ISR context */
} OS_Status;

/** @brief Type definition of OS time */
typedef unsigned long OS_Time_t;

#define OS_WAIT_FOREVER         0xffffffffU /* Wait forever timeout value */
#define OS_SEMAPHORE_MAX_COUNT  0xffffffffU /* Maximum count value for semaphore */
#define OS_INVALID_HANDLE       NULL        /* OS invalid handle */

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_OS_RTTHREAD_OS_COMMON_H_ */
