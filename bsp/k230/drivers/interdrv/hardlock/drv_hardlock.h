/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DRV_HARDLOCK_H__
#define DRV_HARDLOCK_H__
#include <rtdef.h>

typedef enum k230_hardlock_type
{
    HARDLOCK_GPIO = 0,
    HARDLOCK_KPU = 1,
    HARDLOCK_TS = 2,
    HARDLOCK_DISP = 3,
    HARDLOCK_DISP_CPU0 = 4,
    HARDLOCK_DISP_CPU1 = 5,
    HARDLOCK_HASH = 6,
    HARDLOCK_AES = 7,
    HARDLOCK_SM4 = 8,
    HARDLOCK_PDMA = 9,
    HARDLOCK_MAX = 128
} hardlock_type;

#ifdef BSP_USING_HARDLOCK
extern int kd_hardlock_lock(hardlock_type num);
extern void kd_hardlock_unlock(hardlock_type num);
extern int kd_request_lock(hardlock_type num);
#else
rt_inline int kd_hardlock_lock(hardlock_type num)
{ return 0; }
rt_inline void kd_hardlock_unlock(hardlock_type num)
{}
rt_inline int kd_request_lock(hardlock_type num)
{ return num; }
#endif

#endif