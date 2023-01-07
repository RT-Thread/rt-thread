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
#ifndef __HAL_SYS_H__
#define __HAL_SYS_H__

#include <stdint.h>

void hal_reboot();
void hal_sys_reset();
void hal_poweroff();

struct romapi_freertos_map
{
    void *vApplicationIdleHook;
    void *interrupt_entry_ptr;
    void *vApplicationGetIdleTaskMemory;
    void *vApplicationStackOverflowHook;
    void *vApplicationGetTimerTaskMemory;
    void *rtos_sprintf;
    void *vApplicationMallocFailedHook;
    void *rtos_memcpy_ptr;
    void *vAssertCalled;
    void *rtos_strlen_ptr;
    void *rtos_memset_ptr;
    void *rtos_clz;
    void *exception_entry_ptr;
    void *rtos_strcpy_ptr;
    void *xISRStackTop;
};
struct romapi_freertos_map* hal_sys_romapi_get(void);
void hal_sys_romapi_update(struct romapi_freertos_map *romapi);

void hal_sys_capcode_update(uint8_t capin, uint8_t capout);
uint8_t hal_sys_capcode_get(void);
void hal_sys_mtimer_div(void);
void hal_enable_cpu0(void);
void hal_boot_cpu0(uint32_t start_addr);
void hal_halt_cpu0(void);
void hal_release_cpu0(void);
#endif
