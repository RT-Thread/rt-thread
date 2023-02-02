#include <rthw.h>
#include <rtthread.h>

#define ISR_NUMBER    32 
static struct rt_irq_desc rv32irq_table[ISR_NUMBER];
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
    int irq_id = (mcause & 0x1F);
    int exception = !(mcause & 0x80000000);
    if(exception)
    {
        rt_kprintf("Trigger exception mcause = %d\r\n",mcause);
    }
    else
    {
        rv32irq_table[irq_id].handler(irq_id, rv32irq_table[irq_id].param);
    }

}
