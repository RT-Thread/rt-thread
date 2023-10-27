/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-25     Shell        first version
 */

#ifndef __LWP_INTERNAL_H__
#define __LWP_INTERNAL_H__

#include "lwp.h"
#include "lwp_user_mm.h"

#include <rtthread.h>
#include "libc_musl.h"

struct rt_lwp;
rt_err_t lwp_mutex_take_safe(rt_mutex_t mtx, rt_int32_t timeout, rt_bool_t interruptable);
rt_err_t lwp_mutex_release_safe(rt_mutex_t mtx);

#ifdef RT_USING_SMP
    #define LOCAL_IRQ_MASK() rt_hw_local_irq_disable()
    #define LOCAL_IRQ_UNMASK(level) rt_hw_local_irq_enable(level)
#else
    #define LOCAL_IRQ_MASK() rt_hw_interrupt_disable()
    #define LOCAL_IRQ_UNMASK(level) rt_hw_interrupt_enable(level)
#endif

#ifndef LWP_USING_CPUS_LOCK
rt_err_t lwp_critical_enter(struct rt_lwp *lwp);
rt_err_t lwp_critical_exit(struct rt_lwp *lwp);

#define LWP_LOCK(lwp)                           \
    do {                                        \
        RT_DEBUG_SCHEDULER_AVAILABLE(1);        \
        if (lwp_critical_enter(lwp) != RT_EOK)  \
        {                                       \
            RT_ASSERT(0);                       \
        }                                       \
    } while (0)

#define LWP_UNLOCK(lwp)                         \
    do {                                        \
        if (lwp_critical_exit(lwp) != RT_EOK)   \
        {                                       \
            RT_ASSERT(0);                       \
        }                                       \
    } while (0)

#else

#define LWP_LOCK(lwp)           rt_base_t level = rt_hw_interrupt_disable()
#define LWP_UNLOCK(lwp)         rt_hw_interrupt_enable(level)

#endif /* LWP_USING_CPUS_LOCK */

/* cpus lock */
#ifdef LWP_OVERRIDE_CPUS_LOCK
#undef rt_hw_interrupt_disable
#undef rt_hw_interrupt_enable

#define rt_hw_interrupt_disable() ({                \
    rt_base_t irq = rt_hw_interrupt_is_disabled();  \
    if (irq)                                        \
    {                                               \
        LOG_W("Nested interrupt disable");          \
        rt_backtrace();                             \
        irq = 0xabadcafe;                           \
    } else {                                        \
        irq = rt_cpus_lock();                       \
    }                                               \
    irq;                                            \
})

#define rt_hw_interrupt_enable(level) do {  \
    if (level != 0xabadcafe)                \
        rt_cpus_unlock(level);              \
    } while (0)
#endif /* LWP_OVERRIDE_CPUS_LOCK */

/**
 * Brief: Return code with safety check
 * There tend to be chances where a return value is returned without correctly init
 */
#ifndef LWP_DEBUG
#define DEF_RETURN_CODE(name)   rt_err_t name
#define RETURN(name)            return name

#else
#define _LWP_UNINITIALIZED_RC   0xbeefcafe
#define DEF_RETURN_CODE(name)   rt_err_t name = _LWP_UNINITIALIZED_RC
#define RETURN(name)            {RT_ASSERT(name != _LWP_UNINITIALIZED_RC);return name;}
#endif /* LWP_DEBUG */

#endif /* __LWP_INTERNAL_H__ */
