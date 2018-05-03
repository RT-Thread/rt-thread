#include <rthw.h>
#include "plic_driver.h"
#include "platform.h"

#define MAX_HANDLERS    PLIC_NUM_INTERRUPTS
extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS];

rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
volatile plic_instance_t g_plic;
/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int irq)
{
	PLIC_disable_interrupt(&g_plic, irq);
	return;
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_unmask(int irq)
{
	PLIC_enable_interrupt(&g_plic, irq);
	PLIC_set_priority(&g_plic, irq, 1);
	return;
}
rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", vector);
    return RT_NULL;
}
void rt_hw_interrupt_init(void)
{
	int idx;
/*	config interrupt vector*/
	asm volatile(
		"la t0, trap_entry\n"
		"csrw mtvec, t0"
	);
/*	enable global interrupt*/
	PLIC_init(&g_plic,
			PLIC_CTRL_ADDR,
			PLIC_NUM_INTERRUPTS,
			PLIC_NUM_PRIORITIES);

	/* init exceptions table */
	for(idx=0; idx < MAX_HANDLERS; idx++)
	{
		rt_hw_interrupt_mask(idx);
		irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
		irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
		rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
		irq_desc[idx].counter = 0;
#endif
	}
	/* init interrupt nest, and context in thread sp */
	rt_interrupt_nest = 0;
	rt_interrupt_from_thread = 0;
	rt_interrupt_to_thread = 0;
	rt_thread_switch_interrupt_flag = 0;
}
rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq)
{
	//volatile rt_uint32_t irqstat;
	rt_uint32_t id = PLIC_claim_interrupt(&g_plic);
	return id;
}
void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id)
{
	PLIC_complete_interrupt(&g_plic, id);
	return;
}
/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the interrupt service function parameter
 * @param name the interrupt name
 * @return old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[vector].handler;
        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[vector].counter = 0;
#endif
        }
    }

    return old_handler;
}
