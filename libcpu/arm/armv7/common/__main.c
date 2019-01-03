/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rtdef.h>
#include <stdint.h>
#include <string.h>

#if defined(__CC_ARM) || defined(__CLANG_ARM)
#elif defined(__GNUC__)
extern uint32_t __bss_start;
extern uint32_t __bss_end;
extern uint32_t __ctors_start__;
extern uint32_t __ctors_end__;
void __main(void)
{
    uint32_t bytes = (uint32_t)&__bss_end - (uint32_t)&__bss_start;
    memset(&__bss_start, 0, bytes);

    // call C++ constructors of global objects
    uint32_t size = (uint32_t*)&__ctors_end__ - (uint32_t*)&__ctors_start__;
    for (uint32_t i = 0; i < size; i++) {
        uint32_t funcPtr = ((uint32_t*)&__bss_start)[i];
        ((void(*)(void))funcPtr)();
    }
}
#endif