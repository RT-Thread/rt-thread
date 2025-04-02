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

#ifndef __SYSCTL_BOOT_H__
#define __SYSCTL_BOOT_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct pll {
    volatile uint32_t cfg0;
    volatile uint32_t cfg1;
    volatile uint32_t ctl;
    volatile uint32_t state;
} pll_t;

/*
 * pll related registers see TRM 2.2.4 Table 2-2-8
 * soc_glb_rst: see TRM 2.1.4 Table 2-2-1
 * Others: see TRM 2.3.4 Table 2-3-2
 */
typedef struct sysctl_boot {
    pll_t pll[4];
    volatile uint32_t soc_boot_ctl;         /* 0x40 */
    volatile uint32_t reserved0[7];         /* 0x44 0x48 0x4c 0x50 0x54 0x58 0x5c*/
    volatile uint32_t soc_glb_rst;          /* 0x60 */
    volatile uint32_t soc_rst_tim;          /* 0x64 */
    volatile uint32_t soc_slp_tim;          /* 0x68 */
    volatile uint32_t soc_slp_ctl;          /* 0x6c */
    volatile uint32_t clk_stable_tim;       /* 0x70 */
    volatile uint32_t cpu_wakeup_tim;       /* 0x74 */
    volatile uint32_t soc_wakeup_src;       /* 0x78 */
    volatile uint32_t cpu_wakeup_cfg;       /* 0x7c */
    volatile uint32_t timer_pause_ctl;      /* 0x80 */
    volatile uint32_t reserved1[3];         /* 0x84 0x88 0x8c */
    volatile uint32_t sysctl_int0_raw;      /* 0x90 */
    volatile uint32_t sysctl_int0_en;       /* 0x94 */
    volatile uint32_t sysctl_int0_state;    /* 0x98 */
    volatile uint32_t reserved2;            /* 0x9c */
    volatile uint32_t sysctl_int1_raw;      /* 0xa0 */
    volatile uint32_t sysctl_int1_en;       /* 0xa4 */
    volatile uint32_t sysctl_int1_state;    /* 0xa8 */
    volatile uint32_t reserved3;            /* 0xac */
    volatile uint32_t sysctl_int2_raw;      /* 0xb0 */
    volatile uint32_t sysctl_int2_en;       /* 0xb4 */
    volatile uint32_t sysctl_int2_state;    /* 0xb8 */
    volatile uint32_t reserved4[17];        /* 0xbc 0xc0-0xcc 0xd0-0xdc 0xe0-0xec 0xf0-0xfc*/
    volatile uint32_t cpu0_hart_rstvec;     /* 0x100 */
    volatile uint32_t cpu1_hart_rstvec;     /* 0x104 */
    volatile uint32_t reserved5[4];         /* 0x108 0x10c 0x110 0x114 */
    volatile uint32_t soc_sleep_mask;       /* 0x118 */
} sysctl_boot_t;


/* See TRM 1.4.1 Boot media Selection */
typedef enum
{
    SYSCTL_BOOT_NORFLASH    = 0,
    SYSCTL_BOOT_NANDFLASH   = 1,
    SYSCTL_BOOT_EMMC        = 2,
    SYSCTL_BOOT_SDCARD      = 3,
    SYSCTL_BOOT_MAX,
} sysctl_boot_mode_e;

sysctl_boot_mode_e sysctl_boot_get_boot_mode(void);
bool sysctl_boot_get_otp_bypass(void);
void sysctl_boot_set_pll_lock(void);
void sysctl_boot_set_spi2axi(void);
void sysctl_boot_reset_soc(void);

int sysctl_boot_read_is_boot_wakeup(void);
void sysctl_boot_soc_sleep_ctl(void);

#endif