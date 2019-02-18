/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>

#include "inc/arc/arc_exception.h"

/* enable interrupt and set interrupt priority mask */
#define ARC_INIT_STATUS (AUX_STATUS_MASK_IE | ((-1 - INT_PRI_MIN) << 1))


extern void start_r(void);


rt_uint32_t context_switch_reqflg;
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;

struct init_stack_frame {
	rt_uint32_t pc;
	rt_uint32_t blink;
	rt_uint32_t task;
	rt_uint32_t status32;
	rt_uint32_t r0;
};

/**
 * shutdown CPU
 */
void rt_hw_cpu_shutdown(void)
{

}

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