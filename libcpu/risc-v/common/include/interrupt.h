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

#ifndef RT_USING_DM
#ifdef RT_USING_ADT_BITMAP
#include <bitmap.h>

#define RISCV_PLIC_QUIRK_EDGE_INTERRUPT RT_BIT(0)

#define RISCV_CLIC_QUIRK_MODE_FIXED     RT_BIT(0)
#define RISCV_CLIC_QUIRK_MINTTHRESH     RT_BIT(1)
#define RISCV_CLIC_QUIRK_SHV            RT_BIT(2)
#endif /* RT_USING_ADT_BITMAP */

#define INTC_TYPE_RISCV                 0
#define INTC_TYPE_ANDESTECH             1
#define INTC_TYPE_CLIC                  2

#define IRQ_INTC(vector)    (vector)
#ifdef RT_USING_SMP
#define IPI_INTC(vector)    (ipi_intc_base + (vector))
#endif

#define IRQ_PLIC(vector)    (irq_plic_base + (vector))

#define IRQ_CLIC(vector)    (vector)
#ifdef RT_USING_SMP
#define IPI_CLIC(vector)    (ipi_clic_base + (vector))
extern int ipi_intc_base;
extern int ipi_clic_base;
#endif
extern int irq_plic_base;

rt_ubase_t platform_get_plic_base(void);
rt_size_t platform_get_plic_size(void);
rt_ubase_t platform_get_plic_quirks(void);
rt_ubase_t platform_get_clic_base(void);
rt_size_t platform_get_clic_size(void);
rt_ubase_t platform_get_clic_quirks(void);

#ifdef ARCH_RISCV_M_MODE
rt_ubase_t platform_get_clint_base(void);
rt_size_t platform_get_clint_size(void);
#endif

#endif /* !RT_USING_DM */

#ifdef RT_USING_SMP
void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);
#endif

void rt_hw_interrupt_handle(rt_uint32_t vector, void *param);

#endif /* __INTERRUPT_H__ */
