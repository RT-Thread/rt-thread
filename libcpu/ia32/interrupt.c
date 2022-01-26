/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015/9/15      Bernard      Update to new interrupt framework.
 */

#include <rthw.h>
#include <rtthread.h>

#include <bsp.h>

extern void rt_hw_idt_init(void);

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS];

rt_uint16_t irq_mask_8259A = 0xFFFF;

void rt_hw_interrupt_handle(int vector, void* param);

/**
 * @addtogroup I386
 */
/*@{*/

/**
 * This function initializes 8259 interrupt controller
 */
void rt_hw_pic_init()
{
    outb(IO_PIC1, 0x11);
    outb(IO_PIC1+1, IRQ_OFFSET);
    outb(IO_PIC1+1, 1<<IRQ_SLAVE);
    outb(IO_PIC1+1, 0x3);
    outb(IO_PIC1+1, 0xff);
    outb(IO_PIC1, 0x68);
    outb(IO_PIC1, 0x0a);
    outb(IO_PIC2, 0x11);
    outb(IO_PIC2+1, IRQ_OFFSET + 8);
    outb(IO_PIC2+1, IRQ_SLAVE);
    outb(IO_PIC2+1, 0x3);
    outb(IO_PIC2+1, 0xff);
    outb(IO_PIC2, 0x68);
    outb(IO_PIC2, 0x0a);

    if (irq_mask_8259A != 0xFFFF)
    {
        outb(IO_PIC1+1, (char)irq_mask_8259A);
        outb(IO_PIC2+1, (char)(irq_mask_8259A >> 8));
    }
}

void rt_hw_interrupt_handle(int vector, void* param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

void rt_hw_isr(int vector)
{
    if (vector < MAX_HANDLERS)
    {
        irq_desc[vector].handler(vector, irq_desc[vector].param);
    }
}

/**
 * This function initializes interrupt descript table and 8259 interrupt controller
 *
 */
void rt_hw_interrupt_init(void)
{
    int idx;

    rt_hw_idt_init();
    rt_hw_pic_init();

    /* init exceptions table */
    for(idx=0; idx < MAX_HANDLERS; idx++)
    {
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif
    }
}

void rt_hw_interrupt_umask(int vector)
{
    irq_mask_8259A = irq_mask_8259A&~(1<<vector);
    outb(IO_PIC1+1, (char)irq_mask_8259A);
    outb(IO_PIC2+1, (char)(irq_mask_8259A >> 8));
}

void rt_hw_interrupt_mask(int vector)
{
    irq_mask_8259A = irq_mask_8259A | (1<<vector);
    outb(IO_PIC1+1, (char)irq_mask_8259A);
    outb(IO_PIC2+1, (char)(irq_mask_8259A >> 8));
}

rt_isr_handler_t rt_hw_interrupt_install(int              vector,
                                         rt_isr_handler_t handler,
                                         void            *param,
                                         const char      *name)
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

/*@}*/
