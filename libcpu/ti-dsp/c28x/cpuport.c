/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-01     xuzhuoyi     the first version.
 */

#include <rtthread.h>

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
/* exception hook */
static rt_err_t (*rt_exception_hook)(void *context) = RT_NULL;

extern rt_uint16_t rt_hw_get_st0(void);
extern rt_uint16_t rt_hw_get_st1(void);

struct exception_stack_frame
{
    rt_uint32_t t_st0;
    rt_uint32_t acc;
    rt_uint32_t p;
    rt_uint32_t ar1_ar0;
    rt_uint32_t dp_st1;
    rt_uint32_t dbgstat_ier;
    rt_uint32_t return_address;
};

struct stack_frame
{
    struct exception_stack_frame exception_stack_frame;

    /* r4 ~ r11 register */
    rt_uint16_t ar0h;
    rt_uint16_t ar1h;
    rt_uint32_t xar2;
    rt_uint32_t xar3;
    rt_uint32_t xar4;
    rt_uint32_t xar5;
    rt_uint32_t xar6;
    rt_uint32_t xar7;
    rt_uint32_t xt;
    rt_uint32_t rpc;


};

rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    struct stack_frame *stack_frame;
    rt_uint8_t         *stk;
    unsigned long       i;

    stk  = stack_addr;
    stk  = (rt_uint8_t *)RT_ALIGN((rt_uint32_t)stk, 8);
    //stk -= sizeof(struct stack_frame);
    stk += 1;

    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.t_st0   = 0x11110000 | rt_hw_get_st0();
    stack_frame->exception_stack_frame.acc     = 0x33332222;
    stack_frame->exception_stack_frame.ar1_ar0 = 0x00001111 & (unsigned long)parameter; /* ar0 : argument */
    stack_frame->exception_stack_frame.p       = 0x55554444;                            /* p */
    stack_frame->exception_stack_frame.dp_st1  = (0x00000000) | rt_hw_get_st1();        /* dp_st1 */
    stack_frame->exception_stack_frame.dbgstat_ier    = 0;                              /* dbgstat_ier */
    stack_frame->exception_stack_frame.return_address = (unsigned long)tentry;          /* return_address */
    stack_frame->rpc = (unsigned long)texit;

    /* return task's current stack address */
    return stk + sizeof(struct stack_frame);
}

/**
 * This function set the hook, which is invoked on fault exception handling.
 *
 * @param exception_handle the exception handling hook function.
 */
void rt_hw_exception_install(rt_err_t (*exception_handle)(void *context))
{
    rt_exception_hook = exception_handle;
}


struct exception_info
{
    rt_uint32_t exc_return;
    struct stack_frame stack_frame;
};


/**
 * shutdown CPU
 */
void rt_hw_cpu_shutdown(void)
{
    rt_kprintf("shutdown...\n");

    RT_ASSERT(0);
}
