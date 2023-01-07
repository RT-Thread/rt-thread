/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BL_SYS_H__
#define __BL_SYS_H__

#include <stdint.h>

typedef enum {
    BL_RST_POWER_OFF = 0,
    BL_RST_HARDWARE_WATCHDOG,
    BL_RST_FATAL_EXCEPTION,
    BL_RST_SOFTWARE_WATCHDOG,
    BL_RST_SOFTWARE,
} BL_RST_REASON_E;

BL_RST_REASON_E bl_sys_rstinfo_get(void);
int bl_sys_rstinfo_set(BL_RST_REASON_E val);
int bl_sys_rstinfo_getsting(char *info);
void bl_sys_rstinfo_init(void);
int bl_sys_logall_enable(void);
int bl_sys_logall_disable(void);
void bl_sys_mfg_config(void);
int bl_sys_reset_por(void);
void bl_sys_reset_system(void);
int bl_sys_isxipaddr(uint32_t addr);
int bl_sys_early_init(void);
int bl_sys_init(void);
void bl_enable_cpu0(void);
void bl_boot_cpu0(uint32_t start_addr);
void bl_halt_cpu0(void);
void bl_release_cpu0(void);
void bl_sys_enabe_jtag(int cpuid);
void bl_sys_lowlevel_init(void);
#endif
