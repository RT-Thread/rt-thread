/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     bigmagic      The first version
 */

#ifndef INTERRUPT_H__
#define INTERRUPT_H__

#define IRQ_OFFSET 16
#ifndef IRQ_MAX_NR
#define IRQ_MAX_NR 200
#endif
#define INTERRUPTS_MAX (IRQ_OFFSET + IRQ_MAX_NR)

enum
{
    EP_INSTRUCTION_ADDRESS_MISALIGNED = 0,
    EP_INSTRUCTION_ACCESS_FAULT,
    EP_ILLEGAL_INSTRUCTION,
    EP_BREAKPOINT,
    EP_LOAD_ADDRESS_MISALIGNED,
    EP_LOAD_ACCESS_FAULT,
    EP_STORE_ADDRESS_MISALIGNED,
    EP_STORE_ACCESS_FAULT,
    EP_ENVIRONMENT_CALL_U_MODE,
    EP_ENVIRONMENT_CALL_S_MODE,
    EP_RESERVED10,
    EP_ENVIRONMENT_CALL_M_MODE,
    EP_INSTRUCTION_PAGE_FAULT, /* page attr */
    EP_LOAD_PAGE_FAULT,        /* read data */
    EP_RESERVED14,
    EP_STORE_PAGE_FAULT,       /* write data */
};

void rt_hw_interrupt_init(void);
void rt_hw_interrupt_mask(int vector);
void rt_hw_interrupt_umask(int vector);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, void *param, const char *name);

void plic_handle_irq(void);

#endif
