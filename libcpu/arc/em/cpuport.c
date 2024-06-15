/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>

#include "arc/arc_exception.h"

#if ARC_FEATURE_STACK_CHECK
#define ARC_INIT_STATUS ((1 << AUX_STATUS_BIT_SC) | AUX_STATUS_MASK_IE | ((-1 - INT_PRI_MIN) << 1) | STATUS32_RESET_VALUE)
#else
#define ARC_INIT_STATUS (AUX_STATUS_MASK_IE | ((-1 - INT_PRI_MIN) << 1) | STATUS32_RESET_VALUE)
#endif

extern void start_r(void);


rt_uint32_t rt_thread_switch_interrupt_flag;
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t exc_nest_count;

struct init_stack_frame {
    rt_uint32_t pc;
    rt_uint32_t blink;
    rt_uint32_t task;
    rt_uint32_t status32;
    rt_uint32_t r0;
};

rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    struct init_stack_frame *stack_frame;
    rt_uint8_t         *stk;

    stk  = stack_addr + sizeof(rt_uint32_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);
    stk -= sizeof(struct init_stack_frame);

    stack_frame = (struct init_stack_frame *)stk;

    stack_frame->pc = (rt_uint32_t)start_r;
    stack_frame->blink = (rt_uint32_t)texit;
    stack_frame->task = (rt_uint32_t)tentry;
    stack_frame->status32 = ARC_INIT_STATUS;
    stack_frame->r0 = (rt_uint32_t)parameter;

    return stk;
}


/**
 * This function set the hook, which is invoked on fault exception handling.
 *
 * @param exception_handle the exception handling hook function.
 */
void rt_hw_exception_install(rt_err_t (*exception_handle)(void *context))
{
    exception_handle = exception_handle;
}

void set_hw_stack_check(rt_uint32_t *from, rt_uint32_t *to)
{
    struct rt_thread *rt_thread_to;
    if (to != NULL) {
        rt_thread_to = rt_container_of(to, struct rt_thread, sp);
#if ARC_FEATURE_SEC_PRESENT
        arc_aux_write(AUX_S_KSTACK_TOP, (uint32_t)(rt_thread_to->stack_addr));
        arc_aux_write(AUX_S_KSTACK_BASE, (uint32_t)(rt_thread_to->stack_addr)+rt_thread_to->stack_size);
#else
        arc_aux_write(AUX_KSTACK_TOP, (uint32_t)(rt_thread_to->stack_addr));
        arc_aux_write(AUX_KSTACK_BASE, (uint32_t)(rt_thread_to->stack_addr)+rt_thread_to->stack_size);
#endif
    }
}
