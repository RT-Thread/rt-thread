/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include "NuMicro.h"
#include "rtthread.h"
#include "drv_gpio.h"

#define NU_MFP_POS(PIN)   ((PIN % 4) * 8)
#define NU_MFP_MSK(PIN)   (0x1ful << NU_MFP_POS(PIN))

#define STR2(x) #x
#define STR(x) STR2(x)
#define INCBIN(name, file) \
    __asm__(".section .rodata\n" \
            ".global incbin_" STR(name) "_start\n" \
            ".balign 16\n" \
            "incbin_" STR(name) "_start:\n" \
            ".incbin \"" file "\"\n" \
            \
            ".global incbin_" STR(name) "_end\n" \
            ".balign 1\n" \
            "incbin_" STR(name) "_end:\n" \
            ".byte 0\n" \
    ); \
    extern const __attribute__((aligned(32))) void* incbin_ ## name ## _start; \
    extern const void* incbin_ ## name ## _end;

void nu_pin_func(rt_base_t pin, int data);

#endif /* __DRV_COMMON_H__ */