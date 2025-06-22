/*
 * Copyright (c) 2022-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_USB_GLUE_HPM_H_
#define _HPM_USB_GLUE_HPM_H_

extern void (*g_usb_hpm_irq[2])(uint8_t busid);
extern uint8_t g_usb_hpm_busid[2];

void hpm_usb_isr_enable(uint32_t base);
void hpm_usb_isr_disable(uint32_t base);
void hpm_isr_usb0(void);
void hpm_isr_usb1(void);

#endif /* _HPM_USB_GLUE_HPM_H_ */