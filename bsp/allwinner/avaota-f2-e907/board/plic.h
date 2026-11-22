/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal PLIC (RISC-V platform-level interrupt controller) for the V861 C907
 * M-mode firmware. S-mode/SMART is not used by this BSP, so only the M-mode
 * context 0 registers (0x2000/0x200000 offsets) are touched.
 */

#ifndef V861_PLIC_H__
#define V861_PLIC_H__

#include <stdint.h>
#include <rtthread.h>

#define V861_PLIC_BASE    0x10000000U
#define V861_PLIC_IRQ_NUM 128

void v861_plic_init(void);
void v861_plic_enable_irq(int irq);
void v861_plic_disable_irq(int irq);
void v861_plic_handle_irq(void);

/* Register an ISR for a PLIC source number (same numbering as the DTS
 * "interrupts" property). Returns the previous handler, RT_NULL if none. */
rt_isr_handler_t v861_plic_install_irq(int irq, rt_isr_handler_t handler, void *param);

#endif /* V861_PLIC_H__ */
