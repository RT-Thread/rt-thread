/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-01     Bernard      The first version
 * 2025-04-20     GuEe-GUI     Port for not DM
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <rthw.h>

#define IRQ_INTC(vector)    (vector)
#ifdef RT_USING_SMP
#define IPI_INTC(vector)    (ipi_intc_base + (vector))
#endif

#define IRQ_PLIC(vector)    (irq_plic_base + (vector))

#define IRQ_CLIC(vector)    (vector)
#ifdef RT_USING_SMP
#define IPI_CLIC(vector)    (ipi_clic_base + (vector))
#endif

#ifdef RT_USING_SMP
extern rt_uint32_t ipi_intc_base;
extern rt_uint32_t ipi_clic_base;
#endif
extern rt_uint32_t irq_plic_base;

void rt_hw_interrupt_handle(rt_ubase_t scause);

#ifdef RT_USING_SMP
void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);
#endif

#endif /* __INTERRUPT_H__ */
