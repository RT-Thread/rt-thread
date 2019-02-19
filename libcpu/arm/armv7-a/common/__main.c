/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rtdef.h>
#include <stdint.h>
#include <string.h>
#include <rthw.h>
#include <mmu.h>

RT_WEAK void rt_hw_post_init(void)
{
}

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern void _platform_post_lib_init(void);
extern void $Super$$__cpp_initialize__aeabi_(void);

void $Sub$$__cpp_initialize__aeabi_(void)
{
    $Super$$__cpp_initialize__aeabi_();
}

void _platform_post_lib_init(void) 
{
    rt_hw_mmu_init();
    rt_hw_post_init();
}

#elif defined(__GNUC__)
extern int rtthread_startup(void);
extern uint32_t __bss_start;
extern uint32_t __bss_end;
extern uint32_t __ctors_start__;
extern uint32_t __ctors_end__;
void __main(void)
{
    uint32_t bytes = (uint32_t)&__bss_end - (uint32_t)&__bss_start;
    memset(&__bss_start, 0, bytes);

    /* call C++ constructors of global objects */
    uint32_t size = (uint32_t*)&__ctors_end__ - (uint32_t*)&__ctors_start__;
    for (uint32_t i = 0; i < size; i++) {
        uint32_t funcPtr = ((uint32_t*)&__ctors_start__)[i];
        ((void(*)(void))funcPtr)();
    }

    rt_hw_mmu_init();
    rt_hw_post_init();

    /* Corresponds to the armcc/armclang function: $Sub$$main */
    rt_hw_interrupt_disable();
    rtthread_startup();
}
#endif

int cplusplus_system_init(void)
{
    return 0;
}
