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

/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef DRV_PWM_H__
#define DRV_PWM_H__
#include <stdint.h>

#define NSEC_PER_SEC    1000000000L
typedef struct
{
    volatile uint32_t pwmcfg;            /* 0x00 */
    volatile uint32_t reserved0;
    volatile uint32_t pwmcount;          /* 0x08 */
    volatile uint32_t reserved1;
    volatile uint32_t pwms;              /* 0x10 */
    volatile uint32_t reserved2;
    volatile uint32_t reserved3;
    volatile uint32_t reserved4;
    volatile uint32_t pwmcmp0;           /* 0x20 */
    volatile uint32_t pwmcmp1;           /* 0x24 */
    volatile uint32_t pwmcmp2;           /* 0x28 */
    volatile uint32_t pwmcmp3;           /* 0x2c */
} kd_pwm_t;

typedef struct
{
    uint32_t scale : 4;
    uint32_t reserve: 4;
    uint32_t sticky : 1;
    uint32_t zerocmp : 1;
    uint32_t deglitch : 1;
    uint32_t reserve1 : 1;
    uint32_t enalways : 1;
    uint32_t enoneshot : 1;
    uint32_t reserve2 : 2;
    uint32_t cmp0center : 1;
    uint32_t cmp1center : 1;
    uint32_t cmp2center : 1;
    uint32_t cmp3center : 1;
    uint32_t reserve3 : 4;
    uint32_t cmp0gang : 1;
    uint32_t cmp1gang : 1;
    uint32_t cmp2gang : 1;
    uint32_t cmp3gang : 1;
    uint32_t cmp0ip : 1;
    uint32_t cmp1ip : 1;
    uint32_t cmp2ip : 1;
    uint32_t cmp3ip : 1;
} pwm_cfg_t;

typedef struct
{
    pwm_cfg_t cfg;
    uint32_t  freq;
    uint32_t cmp0_val;
    double   cmp1_duty;
    double   cmp2_duty;
    double   cmp3_duty;
} pwm_param_t;

#endif