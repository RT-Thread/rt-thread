/*
 * File      : rtdebug.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 */
 
#ifndef __RTDEBUG_H__
#define __RTDEBUG_H__

#include <rtconfig.h>

/* Using this macro to control all kernel debug features. */
#ifdef RT_DEBUG

/* Turn on some of these (set to non-zero) to debug kernel */
#ifndef RT_DEBUG_MEM
#define RT_DEBUG_MEM        0
#endif

#ifndef RT_DEBUG_MEMHEAP
#define RT_DEBUG_MEMHEAP	0
#endif

#ifndef RT_DEBUG_MODULE
#define RT_DEBUG_MODULE     0
#endif

#ifndef RT_DEBUG_SCHEDULER
#define RT_DEBUG_SCHEDULER  0
#endif

#ifndef RT_DEBUG_SLAB
#define RT_DEBUG_SLAB       0
#endif

#ifndef RT_DEBUG_THREAD
#define RT_DEBUG_THREAD     0
#endif

#ifndef RT_DEBUG_TIMER
#define RT_DEBUG_TIMER      0
#endif

#ifndef RT_DEBUG_IRQ
#define RT_DEBUG_IRQ        0
#endif

#ifndef RT_DEBUG_IPC
#define RT_DEBUG_IPC        0
#endif

/* Turn on this to enable context check */
#ifndef RT_DEBUG_CONTEXT_CHECK
#define RT_DEBUG_CONTEXT_CHECK 1
#endif

#define RT_DEBUG_LOG(type,message)  do { if (type) rt_kprintf message;} while (0)

#define RT_ASSERT(EX)   if (!(EX)) {volatile char dummy = 0;\
                            rt_kprintf("(%s) assert failed at %s:%d \n", \
                            #EX, __FUNCTION__, __LINE__); while (dummy == 0);}

/* Macro to check current context */
#if RT_DEBUG_CONTEXT_CHECK
#define RT_DEBUG_NOT_IN_INTERRUPT do {\
        rt_base_t level;\
        level = rt_hw_interrupt_disable();\
        if (rt_interrupt_get_nest() != 0){\
            rt_kprintf("Function[%s] shall not used in ISR\n", __FUNCTION__);\
            RT_ASSERT(0)}\
        rt_hw_interrupt_enable(level);} while (0)
#endif
#else /* RT_DEBUG */

#define RT_ASSERT(EX)
#define RT_DEBUG_LOG(type,message)
#define RT_DEBUG_NOT_IN_INTERRUPT

#endif /* RT_DEBUG */

#endif /* __RTDEBUG_H__ */
