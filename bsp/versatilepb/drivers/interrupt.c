/*
 * Vectored Interrupt Controller
 * Marcos Medeiros
 */
#include <rtthread.h>
#include "rthw.h"
#include "interrupt.h"

#define __iobase	0x10140000
#define __sic_iobase	0x10003000


enum VICRegisters
{
	IRQ_STATUS		= 0x000,
	FIQ_STATUS		= 0x004,
	RAW_INTR		= 0x008,
	INT_SELECT		= 0x00c,
	INT_ENABLE		= 0x010,
	INT_CLEAR		= 0x014,
	SOFT_INT		= 0x018,
	SOFT_INT_CLEAR	= 0x01c,
	PROTECTION		= 0x020,
	VECT_ADDR		= 0x030,
	DEF_VECT_ADDR	= 0x034,
	VECT_ADDR_0		= 0x100,
	VECT_ADDR_1		= 0x104,
	VECT_ADDR_2		= 0x108,
	VECT_ADDR_3		= 0x10c,
	VECT_ADDR_4		= 0x110,
	VECT_ADDR_5		= 0x114,
	VECT_ADDR_6		= 0x118,
	VECT_ADDR_7		= 0x11c,
	VECT_ADDR_8		= 0x120,
	VECT_ADDR_9		= 0x124,
	VECT_ADDR_10	= 0x128,
	VECT_ADDR_11	= 0x12c,
	VECT_ADDR_12	= 0x130,
	VECT_ADDR_13	= 0x134,
	VECT_ADDR_14	= 0x138,
	VECT_ADDR_15	= 0x13c,
	VECT_CTRL_0		= 0x200,
	VECT_CTRL_1		= 0x204,
	VECT_CTRL_2		= 0x208,
	VECT_CTRL_3		= 0x20c,
	VECT_CTRL_4		= 0x210,
	VECT_CTRL_5		= 0x214,
	VECT_CTRL_6		= 0x218,
	VECT_CTRL_7		= 0x21c,
	VECT_CTRL_8		= 0x220,
	VECT_CTRL_9		= 0x224,
	VECT_CTRL_10	= 0x228,
	VECT_CTRL_11	= 0x22c,
	VECT_CTRL_12	= 0x230,
	VECT_CTRL_13	= 0x234,
	VECT_CTRL_14	= 0x238,
	VECT_CTRL_15	= 0x23c,
};

/* according to vpb_sic_read & vpb_sic_write qemu/hw/arm/versatilepb.c
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0224i/Cacgfedh.html */
enum SICRegisters
{
	SIC_STATUS		= 0x000,	/* Read Status of interrupt (after mask) */
	SIC_RAWSTAT		= 0x004,	/* Read Status of interrupt (before mask) */
	SIC_ENABLE		= 0x008,	/* Read Interrupt mask */
	SIC_ENSET		= 0x008,	/* Write Set bits HIGH to enable the corresponding interrupt signals */
	SIC_ENCLR		= 0x00c,	/* Write Set bits HIGH to mask the corresponding interrupt signals */
	SIC_SOFTINTSET	= 0x010,	/* Read/write Set software interrupt */
	SIC_SOFTINTCLR	= 0x014,	/* Write Clear software interrupt */
	SIC_PICENABLE	= 0x020,	/* Read Read status of pass-through mask (allows interrupt to pass directly to the primary interrupt controller) */
	SIC_PICENSET	= 0x020,	/* Write Set bits HIGH to set the corresponding interrupt pass-through mask bits */
	SIC_PICENCLR	= 0x024,	/* Write Set bits HIGH to clear the corresponding interrupt pass-through mask bits */
};

struct rt_irq_desc irq_desc[64];
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
extern rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq)
{
 	rt_uint32_t irqstatus = readl(__iobase + IRQ_STATUS);
	rt_uint32_t i = 0;
	for (i = 0; i < 32; i++) {
		if (irqstatus & 1) {
			return i;
		}
		irqstatus >>= 1;
	}

	irqstatus = readl(__sic_iobase + SIC_STATUS);
	for (i = 32; i < 64; i++) {
		if (irqstatus & 1) {
			return i;
		}
		irqstatus >>= 1;
	}

	return 0;
}

void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id)
{

}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_unmask(int num)
{
	if (num > 63)
		return;
	if(num < 32)
	{
		writel(__iobase + INT_ENABLE, (1 << num));
	}
	else
	{
		writel(__sic_iobase + SIC_ENSET, (1 << (num-32)));
	}
}
/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int num)
{
	if (num > 63)
		return;
	if(num < 32)
	{
		writel(__iobase + INT_CLEAR, (1 << num));
	}
	else
	{
		writel(__sic_iobase + SIC_ENCLR, (1 << (num-32)));
	}
}

void rt_hw_interrupt_init(void)
{

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

    if(vector < 64)
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
