/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <string.h>
#include <rtthread.h>
#include <locale.h>

extern void rt_hw_post_init(void);

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern uint32_t Image$$ARM_LIB_HEAP$$ZI$$Base;
extern uint32_t Image$$ARM_LIB_HEAP$$ZI$$Limit;

void rt_hw_post_init(void) {
#ifdef RT_USING_HEAP
    uint32_t* pBase = &Image$$ARM_LIB_HEAP$$ZI$$Base;
    uint32_t* pLimit = &Image$$ARM_LIB_HEAP$$ZI$$Limit;
    memset(pBase, 0, (pLimit - pBase) * sizeof(uint32_t));
    rt_system_heap_init(pBase, pLimit);
#endif
}

#elif defined(__GNUC__)
extern int __bss_end;
#define HEAP_BEGIN      ((uint32_t*)&__bss_end)
#define HEAP_END        (uint32_t*)0x90000000

void rt_hw_post_init(void) {
#ifdef RT_USING_HEAP
    uint32_t* pBase = HEAP_BEGIN;
    uint32_t* pLimit = HEAP_END;
    memset(pBase, 0, (pLimit - pBase) * sizeof(uint32_t));
    rt_system_heap_init(pBase, pLimit);
#endif
}
#endif
