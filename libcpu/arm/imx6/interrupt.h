/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h>
#include <stdbool.h>

// [ref]IMX6DQRM.pdf: 12.5.3.1 Interrupt Controller Features
#define MAX_HANDLERS	(32 + 128)  // ID0-ID15: SGI. ID16-ID31: PPI. ID32-ID159: SPI

#define INT_IRQ     0x00
#define INT_FIQ     0x01

#ifdef __cplusplus
extern "C" {
#endif

void rt_hw_interrupt_control(int32_t vector, int32_t priority, int32_t route);
int32_t rt_hw_interrupt_get_active(int32_t fiq_irq);
void rt_hw_interrupt_ack(int32_t fiq_irq);
void rt_hw_interrupt_trigger(int32_t vector);
void rt_hw_interrupt_clear(int32_t vector);

#ifdef __cplusplus
}
#endif

#endif
