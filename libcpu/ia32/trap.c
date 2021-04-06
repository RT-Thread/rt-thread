/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtthread.h>

#include <bsp.h>

/* Interrupt descriptor table.  (Must be built at run time because
 * shifted function addresses can't be represented in relocation records.)
 */
struct Gatedesc idt[256] = { {0}, };
struct Pseudodesc idt_pd =
{
    0, sizeof(idt) - 1, (unsigned long) idt,
};

/* exception and interrupt handler table */
extern rt_isr_handler_t isr_table[];
extern rt_isr_handler_t trap_func[];
extern rt_isr_handler_t hdinterrupt_func[];
extern void rt_hw_interrupt_handle(int vector, void* param);

/**
 * @addtogroup I386
 */
/*@{*/

/**
 * this function initializes the interrupt descript table
 *
 */
void rt_hw_idt_init(void)
{
    extern void Xdefault(void);
    int i, j, func;

    // install a default handler
    for (i = 0; i < sizeof(idt)/sizeof(idt[0]); i++)
        SETGATE(idt[i], 0, GD_KT, &Xdefault, 0);

    /*install trap handler*/
    for(i = 0; i < 16; i++)
    {
        func = (int)trap_func[i];
        SETGATE(idt[i], 0, GD_KT, func, 0);
    }

    func = (int)trap_func[3];
    SETGATE(idt[3], 0, GD_KT, func, 3);

    i = 0;

    /*install exteral interrupt handler*/
    for(j = IRQ_OFFSET; j < IRQ_OFFSET + MAX_HANDLERS; j++)
    {
        func = (int)hdinterrupt_func[i];
        SETGATE(idt[j], 0, GD_KT, func, 0);
        i++;
    }

    // Load the IDT
    asm volatile("lidt idt_pd + 2");
}

/**
 * this function will deal with all kinds of kernel trap
 *
 *@param trapno the trap number
 *
 */
void rt_hw_trap_irq(int trapno)
{
    switch(trapno)
    {
        case T_DIVIDE:
            rt_kprintf("Divide error interrupt\n");
            RT_ASSERT(0);
        case T_PGFLT:
            rt_kprintf("Page fault interrupt\n");
            RT_ASSERT(0);
        case T_GPFLT:
            rt_kprintf("General protection interrupt\n");
            RT_ASSERT(0);
        case T_DEFAULT:
            rt_hw_interrupt_handle(T_DEFAULT, RT_NULL);
            return;
    }

    /*kernel bug if run here*/
    RT_ASSERT(0);
}

/*@}*/
