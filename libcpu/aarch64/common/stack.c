/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-12     RT-Thread    init
 * 2023-07-13     GuEe-GUI     append fpu: Q16 ~ Q31
 */
#include <board.h>
#include <rtthread.h>
#include <cpuport.h>

#include <armv8.h>

#define INITIAL_SPSR_EL1 (PSTATE_EL1 | SP_ELx)

#ifdef RT_USING_CPLUSPLUS
extern char __tdata_start, __tdata_end;
extern char __tbss_start, __tbss_end;

static rt_size_t rt_hw_thread_tls_size(void)
{
    /* Preserve any linker-inserted alignment gap between .tdata and .tbss. */
    rt_size_t size = &__tbss_end - &__tdata_start;

    return RT_ALIGN(size, 16);
}

static void rt_hw_thread_tls_init(void *tls)
{
    rt_size_t tdata_size = &__tdata_end - &__tdata_start;
    rt_size_t tls_size = rt_hw_thread_tls_size();

    rt_memcpy(tls, &__tdata_start, tdata_size);
    rt_memset((rt_uint8_t *)tls + tdata_size, 0, tls_size - tdata_size);
}

/*
 * rt_hw_stack_init() reserves TLS below the initial stack pointer.  Derive
 * the same aligned address from the TCB for every subsequent context switch.
 */
void *rt_hw_thread_tls_base(struct rt_thread *thread)
{
    rt_ubase_t top = (rt_ubase_t)thread->stack_addr + thread->stack_size -
                     sizeof(rt_ubase_t);

    return (void *)RT_ALIGN_DOWN(top - rt_hw_thread_tls_size(), 16);
}
#endif /* RT_USING_CPLUSPLUS */

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    rt_ubase_t *stk;

#ifdef RT_USING_CPLUSPLUS
    stack_addr = (rt_uint8_t *)RT_ALIGN_DOWN(
        (rt_ubase_t)stack_addr - rt_hw_thread_tls_size(), 16);
    rt_hw_thread_tls_init(stack_addr);
#endif

    /* The AAPCS64 requires 128-bit (16 byte) stack alignment */
    stk = (rt_ubase_t*)RT_ALIGN_DOWN((rt_ubase_t)stack_addr, 16);

    for (int i = 0; i < 32; ++i)
    {
        stk -= sizeof(rt_uint128_t) / sizeof(rt_ubase_t);

        *(rt_uint128_t *)stk = (rt_uint128_t) { 0 };
    }

    *(--stk) = (rt_ubase_t)texit;           /* X20, 2nd param */
    *(--stk) = (rt_ubase_t)tentry;          /* X19, 1st param */
    *(--stk) = (rt_ubase_t)22;              /* X22 */
    *(--stk) = (rt_ubase_t)parameter;       /* X21, 3rd param */
    *(--stk) = (rt_ubase_t)24;              /* X24 */
    *(--stk) = (rt_ubase_t)23;              /* X23 */
    *(--stk) = (rt_ubase_t)26;              /* X26 */
    *(--stk) = (rt_ubase_t)25;              /* X25 */
    *(--stk) = (rt_ubase_t)28;              /* X28 */
    *(--stk) = (rt_ubase_t)27;              /* X27 */
    *(--stk) = (rt_ubase_t)0;               /* sp_el0 */
    *(--stk) = (rt_ubase_t)0;               /* X29 - addr 0 as AAPCS64 specified */
    *(--stk) = (rt_ubase_t)0;               /* FPSR */
    *(--stk) = (rt_ubase_t)0;               /* FPCR */
    *(--stk) = INITIAL_SPSR_EL1;            /* Save Processor States */
    *(--stk) = (rt_ubase_t)_thread_start;   /* Exception return address. */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}
