/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-25     Shell        first version
 * 2023-11-25     Shell        Add pgrp, session lock API
 */

#ifndef __LWP_INTERNAL_H__
#define __LWP_INTERNAL_H__

#include "lwp.h"
#include "lwp_arch.h"
#include "lwp_user_mm.h"
#include "lwp_mm.h"

#include <rtthread.h>
#include "libc_musl.h"

struct rt_lwp;

#define LWP_MTX_FLAGS_INTR   0x1 /* interruptible waiting */
#define LWP_MTX_FALGS_NESTED 0x2 /* allow nested */
rt_err_t lwp_mutex_take_safe(rt_mutex_t mtx, rt_int32_t timeout, int flags);
rt_err_t lwp_mutex_release_safe(rt_mutex_t mtx);

rt_inline rt_bool_t lwp_in_user_space(const char *addr)
{
    return (addr >= (char *)USER_VADDR_START && addr < (char *)USER_VADDR_TOP);
}

#ifdef RT_USING_SMP
    #define LOCAL_IRQ_MASK() rt_hw_local_irq_disable()
    #define LOCAL_IRQ_UNMASK(level) rt_hw_local_irq_enable(level)
#else
    #define LOCAL_IRQ_MASK() rt_hw_interrupt_disable()
    #define LOCAL_IRQ_UNMASK(level) rt_hw_interrupt_enable(level)
#endif

#ifndef LWP_USING_CPUS_LOCK
rt_err_t lwp_sess_critical_enter(struct rt_session *sess, int flags);
rt_err_t lwp_sess_critical_exit(struct rt_session *sess);
rt_err_t lwp_pgrp_critical_enter(struct rt_processgroup *pgrp, int flags);
rt_err_t lwp_pgrp_critical_exit(struct rt_processgroup *pgrp);
rt_err_t lwp_critical_enter(struct rt_lwp *lwp, int flags);
rt_err_t lwp_critical_exit(struct rt_lwp *lwp);

#define LWP_ASSERT_LOCKED(proc) RT_ASSERT(rt_mutex_get_owner(&(proc)->lwp_lock) == rt_thread_self())
#define PGRP_ASSERT_LOCKED(pgrp) RT_ASSERT(rt_mutex_get_owner(&(pgrp)->mutex) == rt_thread_self())

#define LWP_LOCK(lwp)                             \
    do                                            \
    {                                             \
        RT_DEBUG_SCHEDULER_AVAILABLE(1);          \
        if (lwp_critical_enter(lwp, 0) != RT_EOK) \
        {                                         \
            RT_ASSERT(0);                         \
        }                                         \
    } while (0)

#define LWP_LOCK_NESTED(lwp)                                         \
    do                                                               \
    {                                                                \
        RT_DEBUG_SCHEDULER_AVAILABLE(1);                             \
        if (lwp_critical_enter(lwp, LWP_MTX_FALGS_NESTED) != RT_EOK) \
        {                                                            \
            RT_ASSERT(0);                                            \
        }                                                            \
    } while (0)

#define LWP_UNLOCK(lwp)                         \
    do {                                        \
        if (lwp_critical_exit(lwp) != RT_EOK)   \
        {                                       \
            RT_ASSERT(0);                       \
        }                                       \
    } while (0)

#define PGRP_LOCK(pgrp)                                 \
    do                                                  \
    {                                                   \
        RT_DEBUG_SCHEDULER_AVAILABLE(1);                \
        if (lwp_pgrp_critical_enter(pgrp, 0) != RT_EOK) \
        {                                               \
            RT_ASSERT(0);                               \
        }                                               \
    } while (0)

#define PGRP_LOCK_NESTED(pgrp)                                             \
    do                                                                     \
    {                                                                      \
        RT_DEBUG_SCHEDULER_AVAILABLE(1);                                   \
        if (lwp_pgrp_critical_enter(pgrp, LWP_MTX_FALGS_NESTED) != RT_EOK) \
        {                                                                  \
            RT_ASSERT(0);                                                  \
        }                                                                  \
    } while (0)

#define PGRP_UNLOCK(pgrp)                           \
    do                                              \
    {                                               \
        if (lwp_pgrp_critical_exit(pgrp) != RT_EOK) \
        {                                           \
            RT_ASSERT(0);                           \
        }                                           \
    } while (0)

#define SESS_LOCK(sess)                                 \
    do                                                  \
    {                                                   \
        RT_DEBUG_SCHEDULER_AVAILABLE(1);                \
        if (lwp_sess_critical_enter(sess, 0) != RT_EOK) \
        {                                               \
            RT_ASSERT(0);                               \
        }                                               \
    } while (0)

#define SESS_LOCK_NESTED(sess)                                             \
    do                                                                     \
    {                                                                      \
        RT_DEBUG_SCHEDULER_AVAILABLE(1);                                   \
        if (lwp_sess_critical_enter(sess, LWP_MTX_FALGS_NESTED) != RT_EOK) \
        {                                                                  \
            RT_ASSERT(0);                                                  \
        }                                                                  \
    } while (0)

#define SESS_UNLOCK(sess)                           \
    do                                              \
    {                                               \
        if (lwp_sess_critical_exit(sess) != RT_EOK) \
        {                                           \
            RT_ASSERT(0);                           \
        }                                           \
    } while (0)

#else

#define LWP_LOCK(lwp)           rt_base_t level = rt_hw_interrupt_disable()
#define LWP_UNLOCK(lwp)         rt_hw_interrupt_enable(level)
#define PGRP_LOCK(pgrp)         rt_base_t level = rt_hw_interrupt_disable()
#define PGRP_UNLOCK(pgrp)       rt_hw_interrupt_enable(level)
#define SESS_LOCK(sess)         rt_base_t level = rt_hw_interrupt_disable()
#define SESS_UNLOCK(sess)       rt_hw_interrupt_enable(level)

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
#define LWP_DEF_RETURN_CODE(name)   rt_err_t name;RT_UNUSED(name)
#define LWP_RETURN(name)            return name

#else
#define _LWP_UNINITIALIZED_RC   0xbeefcafe
#define LWP_DEF_RETURN_CODE(name)   rt_err_t name = _LWP_UNINITIALIZED_RC
#define LWP_RETURN(name)            {RT_ASSERT(name != _LWP_UNINITIALIZED_RC);return name;}
#endif /* LWP_DEBUG */

int load_ldso(struct rt_lwp *lwp, char *exec_name, char *const argv[], char *const envp[]);

#endif /* __LWP_INTERNAL_H__ */
