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
#include <string.h>

#include "bl_sys.h"
#include "hal_sys.h"

void hal_reboot()
{
    bl_sys_reset_por();
}

void hal_sys_reset()
{
    //bl_sys_reset_system();
}

void hal_poweroff()
{
    /*TODO empty now*/
}

#if 0
static uint32_t user_clz(uint32_t priorities)
{
    return __builtin_clz(priorities);
}

struct romapi_freertos_map* hal_sys_romapi_get(void)
{
    extern uint8_t __global_pointer_head$;
    uint32_t *gp_data_start = (uint32_t*)(&__global_pointer_head$);
    struct romapi_freertos_map* romapi_freertos;

    puts("  Configuring Version 1.0 ROM API...\r\n");

    /*clear bss/common section in GP aera*/
    memset(&__global_pointer_head$, 0, 0x498);
    romapi_freertos = (struct romapi_freertos_map*) (((uint8_t*)gp_data_start) + 0x45c);

    /* pTrapNetCounter */
    *(gp_data_start + 0) = (uint32_t)((uint8_t*)(gp_data_start) + 0x58);
    /* pullNextTime */
    *(gp_data_start + 1) = (uint32_t)((uint8_t*)(gp_data_start) + 0x60);
    /* system tick */
    *(gp_data_start + 2) = 32 * 1000 / 1000;//Use 32K

    return romapi_freertos;
}

void hal_sys_romapi_update(struct romapi_freertos_map *romapi_freertos)
{
    extern void interrupt_entry(uint32_t mcause);
    extern void exception_entry(uint32_t mcause, uint32_t mepc, uint32_t mtval);
    extern uint8_t __freertos_irq_stack_top;

    romapi_freertos->interrupt_entry_ptr = interrupt_entry;
    romapi_freertos->rtos_sprintf = sprintf;
    romapi_freertos->rtos_memcpy_ptr = memcpy;
    romapi_freertos->rtos_strlen_ptr = strlen;
    romapi_freertos->rtos_memset_ptr = memset;
    romapi_freertos->exception_entry_ptr = exception_entry;
    romapi_freertos->rtos_strcpy_ptr = strcpy;
    romapi_freertos->xISRStackTop = &__freertos_irq_stack_top;
    romapi_freertos->rtos_clz = user_clz;
}
#endif
void hal_sys_capcode_update(uint8_t capin, uint8_t capout)
{
    //TODO FPGA no capcode
#if 0
    static uint8_t capin_static, capout_static;

    if (255 != capin && 255 != capout) {
        RomDriver_AON_Set_Xtal_CapCode(capin, capout);
        capin_static = capin;
        capout_static = capout;
    } else {
        RomDriver_AON_Set_Xtal_CapCode(capin_static, capout_static);
    }
#endif
}

uint8_t hal_sys_capcode_get(void)
{
    return 0;
   // return AON_Get_Xtal_CapCode();
}

void hal_sys_mtimer_div(void)
{
    *(volatile uint32_t *)0x20009014 = 0x80000004;
}
void hal_enable_cpu0(void)
{
    bl_enable_cpu0();
}

void hal_boot_cpu0(uint32_t start_addr)
{
    bl_boot_cpu0(start_addr);
}

void hal_halt_cpu0(void)
{
    bl_halt_cpu0();
}

void hal_release_cpu0(void)
{
    bl_release_cpu0();
}
