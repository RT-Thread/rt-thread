/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-01     xuzhuoyi     the first version.
 * 2019-07-03     zhaoxiaowei  add support for __rt_ffs.
 * 2019-12-05     xiaolifan    add support for hardware fpu32
 * 2022-10-17     guyunjie     add support for hardware fpu64 and vcrc
 */

#include <rthw.h>

#define DBG_TAG           "cpu.ti.c28x"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

extern volatile rt_uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
/* exception hook */
static rt_err_t (*rt_exception_hook)(void *context) = RT_NULL;

extern rt_uint16_t rt_hw_get_st0(void);
extern rt_uint16_t rt_hw_get_st1(void);
extern int rt_hw_calc_csb(int value);


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

#ifdef __TMS320C28XX_FPU32__
    rt_uint32_t rb;
    rt_uint32_t stf;
    rt_uint32_t r0h;
    rt_uint32_t r1h;
    rt_uint32_t r2h;
    rt_uint32_t r3h;
    rt_uint32_t r4h;
    rt_uint32_t r5h;
    rt_uint32_t r6h;
    rt_uint32_t r7h;
#endif

#ifdef __TMS320C28XX_FPU64__
    rt_uint32_t r0l;
    rt_uint32_t r1l;
    rt_uint32_t r2l;
    rt_uint32_t r3l;
    rt_uint32_t r4l;
    rt_uint32_t r5l;
    rt_uint32_t r6l;
    rt_uint32_t r7l;
#endif

#ifdef __TMS320C28XX_VCRC__
    rt_uint32_t vcrc;
    rt_uint32_t vstatus;
    rt_uint32_t vcrcpoly;
    rt_uint32_t vcrcsize;
#endif

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
    stk  = (rt_uint8_t *)RT_ALIGN((rt_uint32_t)stk, 2);
    stk += 1; /*to work around the stack alignment*/

    stack_frame = (struct stack_frame *)stk;

    /* zero all registers */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0;
    }

    /* configure special registers*/
    stack_frame->exception_stack_frame.dp_st1  = 0x00000A08;
    stack_frame->xar4 = (rt_uint32_t)parameter;
    stack_frame->exception_stack_frame.return_address = (rt_uint32_t)tentry;
    stack_frame->rpc = (rt_uint32_t)texit;

#ifdef __TMS320C28XX_FPU32__
    stack_frame->stf = 0x00000200;
    stack_frame->rb = 0;
#endif

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

#ifdef RT_USING_CPU_FFS
/*
 * This function called rt_hw_calc_csb to finds the first bit set in value.
 * rt_hw_calc_csb is a native assembly program that use "CSB" instruction in C28x.
 * When you use this function, remember that "int" is only 16-bit in C28x's C compiler.
 * If value is a number bigger that 0xFFFF, trouble may be caused.
 * Maybe change "int __rt_ffs(int value)" to "rt_int32_t __rt_ffs(rt_int32_t value)" will be better.
 */
int __rt_ffs(int value)
{
    return rt_hw_calc_csb(value);
}
#endif

void rt_interrupt_enter(void)
{
    rt_base_t level;

    __asm("  EINT");
    level = rt_hw_interrupt_disable();
    rt_interrupt_nest ++;
    RT_OBJECT_HOOK_CALL(rt_interrupt_enter_hook,());
    rt_hw_interrupt_enable(level);

    LOG_D("irq has come..., irq current nest:%d",
          (rt_int32_t)rt_interrupt_nest);
}

void rt_interrupt_leave(void)
{
    LOG_D("irq is going to leave, irq current nest:%d",
          (rt_int32_t)rt_interrupt_nest);

    rt_hw_interrupt_disable();
    RT_OBJECT_HOOK_CALL(rt_interrupt_leave_hook,());
    rt_interrupt_nest --;
    if(rt_thread_switch_interrupt_flag && !rt_interrupt_nest)
    {
        __asm("  OR IFR, #0x8000"); /* trigger rtos int */
    }
    /* rt_hw_interrupt_enable auto done by hardware on IRET */
}
