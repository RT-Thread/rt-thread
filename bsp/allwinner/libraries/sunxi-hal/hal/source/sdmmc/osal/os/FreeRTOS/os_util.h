/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
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
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
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

#ifndef _OS_UTIL_H_
#define _OS_UTIL_H_

#include <string.h>
#include <stdlib.h>
#include "os_time.h"
#include "os_debug.h"
//#include "k_api.h"
//#include "freertos_to_aos.h"

//extern volatile uint32_t ulPortInterruptNesting;

extern volatile uint32_t ulPortInterruptNesting[];
//extern uint8_t g_intrpt_nested_level[];
//extern int cpu_cur_get(void);
/*  check if in ISR context or not */
static __always_inline int OS_IsISRContext(void)
{
      //return __get_IPSR();
      //  return ulPortInterruptNesting;
      //return (int)g_intrpt_nested_level[cpu_cur_get()];
      return ulPortInterruptNesting[cur_cpu_id()];
}


static __always_inline TickType_t OS_CalcWaitTicks(OS_Time_t msec)
{
    TickType_t tick;
    if (msec == OS_WAIT_FOREVER) {
        tick = portMAX_DELAY;
    } else if (msec != 0) {
        tick = OS_MSecsToTicks(msec);
        if (tick == 0)
            tick = 1;
    } else {
        tick = 0;
    }
    return tick;
}

/* memory */
#define OS_Malloc(l)        malloc(l)
#define OS_Free(p)          free(p)
#define OS_Memcpy(d, s, l)  memcpy(d, s, l)
#define OS_Memset(d, c, l)  memset(d, c, l)
#define OS_Memcmp(a, b, l)  memcmp(a, b, l)
#define OS_Memmove(d, s, n) memmove(d, s, n)


#endif /* _OS_UTIL_H_ */
