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

#include "os_debug.h"
#include "param.h"

#if OS_RESOURCE_TRACE

extern int g_r_msgqueue_cnt;
extern int g_r_mutex_cnt;
extern int g_r_semaphore_cnt;
extern int g_r_thread_cnt;
extern int g_r_timer_cnt;

void r_os_resource_info(void)
{
/*
    OS_LOG(1, "<<< r os resource info >>>\n");
    OS_LOG(1, "g_r_msgqueue_cnt  %d\n", g_r_msgqueue_cnt);
    OS_LOG(1, "g_r_mutex_cnt     %d\n", g_r_mutex_cnt);
    OS_LOG(1, "g_r_semaphore_cnt %d\n", g_r_semaphore_cnt);
    OS_LOG(1, "g_r_thread_cnt    %d\n", g_r_thread_cnt);
    OS_LOG(1, "g_r_timer_cnt     %d\n", g_r_timer_cnt);
*/
}

#endif /* OS_RESOURCE_TRACE */

void print_hex_dump_words(const void *addr, unsigned int len)
{
    unsigned int i;
    const unsigned int *p = addr;

    if ((unsigned int)p & 0x03) {
        OS_SYSLOG("addr should be align 4B!\n");
        p =  (const void *)(((unsigned int)p) & ~0x03);
        return ;
    }
    len = DIV_ROUND_UP(len, 4);

    for (i = 0; i < len; i++) {
        if ((i & 0x03) == 0x0)
            OS_SYSLOG("\n[%p]: ", p);
        OS_SYSLOG("0x%08x ", *p++);
    }
    OS_SYSLOG("\n");
}

void print_hex_dump_bytes(const void *addr, unsigned int len)
{
    unsigned int i;
    const unsigned char *p = addr;
    len++;

    for (i = 1; i < len; ++i) {
        OS_SYSLOG("%02x ", *p++);
        if (i % 16 == 0) {
            OS_SYSLOG("\n");
        }
    }
    OS_SYSLOG("\n");
}
