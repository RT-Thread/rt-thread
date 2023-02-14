#include <rthw.h>
#include <rtthread.h>
#include "riscv-ops.h" 
#include "rt_hw_stack_frame.h"

#define ISR_NUMBER    32 
static volatile rt_hw_stack_frame_t *s_stack_frame;
static struct rt_irq_desc rv32irq_table[ISR_NUMBER];
void rt_show_stack_frame(void);
/**
 * 预设中断入口函数
 * @param mcause 中断异常ID
 */
static rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t mcause)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", mcause);
    return RT_NULL;
}

/**
 * 中断函数表初始化 
 */
void rt_hw_interrupt_init(void) 
{
    int idx = 0; 

    for (idx = 0; idx < ISR_NUMBER; idx++)
    {
        rv32irq_table[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle; 
        rv32irq_table[idx].param = RT_NULL; 
    }
}

/**
 * 预装载中断入口函数
 * @param vector  中断号
 * @param handler 中断入口函数 
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, 
        void *param, const char *name) 
{
    void *user_param = param;
    char *user_name = name;
    if(vector < ISR_NUMBER) 
    {
        if (handler != RT_NULL) 
        {
            rv32irq_table[vector].handler = (rt_isr_handler_t)handler;
            rv32irq_table[vector].param = param;
        }
    }
}

/**
 * 统一中断入口函数 
 * @param mcause 中断异常ID
 */
rt_weak void rt_rv32_system_irq_handler(rt_uint32_t mcause)
{
    rt_uint32_t mscratch = read_csr(0x340);
    rt_uint32_t irq_id = (mcause & 0x1F);
    rt_uint32_t exception = !(mcause & 0x80000000);
    if(exception)
    {
        s_stack_frame = (rt_hw_stack_frame_t *)mscratch;
        rt_show_stack_frame();
    }
    else
    {
        rv32irq_table[irq_id].handler(irq_id, rv32irq_table[irq_id].param);
    }

}

rt_weak void rt_show_stack_frame(void)
{
    rt_kprintf("Stack frame:\r\n----------------------------------------\r\n");
    rt_kprintf("ra      : 0x%08x\r\n", s_stack_frame->ra);
    rt_kprintf("mstatus : 0x%08x\r\n", read_csr(0x300));//mstatus
    rt_kprintf("t0      : 0x%08x\r\n", s_stack_frame->t0);
    rt_kprintf("t1      : 0x%08x\r\n", s_stack_frame->t1);
    rt_kprintf("t2      : 0x%08x\r\n", s_stack_frame->t2);
    rt_kprintf("a0      : 0x%08x\r\n", s_stack_frame->a0);
    rt_kprintf("a1      : 0x%08x\r\n", s_stack_frame->a1);
    rt_kprintf("a2      : 0x%08x\r\n", s_stack_frame->a2);
    rt_kprintf("a3      : 0x%08x\r\n", s_stack_frame->a3);
    rt_kprintf("a4      : 0x%08x\r\n", s_stack_frame->a4);
    rt_kprintf("a5      : 0x%08x\r\n", s_stack_frame->a5);
    rt_kprintf("a6      : 0x%08x\r\n", s_stack_frame->a6);
    rt_kprintf("a7      : 0x%08x\r\n", s_stack_frame->a7);
    rt_kprintf("t3      : 0x%08x\r\n", s_stack_frame->t3);
    rt_kprintf("t4      : 0x%08x\r\n", s_stack_frame->t4);
    rt_kprintf("t5      : 0x%08x\r\n", s_stack_frame->t5);
    rt_kprintf("t6      : 0x%08x\r\n", s_stack_frame->t6);
}
