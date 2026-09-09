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

#define RISCV_PLIC_QUIRK_EDGE_INTERRUPT RT_BIT(0)

#define RISCV_CLIC_QUIRK_MODE_FIXED     RT_BIT(0)
#define RISCV_CLIC_QUIRK_MINTTHRESH     RT_BIT(1)
#define RISCV_CLIC_QUIRK_SHV            RT_BIT(2)

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC

#define IRQ_INTC(vector)    (vector)
#ifdef RT_USING_SMP
#define IPI_INTC(vector)    (ipi_intc_base + (vector))
#endif

#define IRQ_PLIC(vector)    (irq_plic_base + (vector))

#ifdef RT_USING_SMP
extern int ipi_intc_base;
#endif
extern int irq_plic_base;

rt_ubase_t platform_get_plic_base(void);
rt_size_t platform_get_plic_size(void);
rt_ubase_t platform_get_plic_quirks(void);

#else /* ARCH_RISCV_NON_DM_IRQ_CLIC */

#define IRQ_CLIC(vector)    (vector)
#ifdef RT_USING_SMP
#define IPI_CLIC(vector)    (ipi_clic_base + (vector))
extern int ipi_clic_base;
#endif

rt_ubase_t platform_get_clic_base(void);
rt_size_t platform_get_clic_size(void);
rt_ubase_t platform_get_clic_quirks(void);

#endif /* ARCH_RISCV_NON_DM_IRQ_PLIC */

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
