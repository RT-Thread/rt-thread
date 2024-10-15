/*
 * Copyright : (C) 2024 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2024/6/26 first commit
 */
#include "rtthread.h"
#include "interrupt.h"

#include "fparameters.h"

void USBH_IRQHandler(uint8_t busid);

static void usb_hc_xhci_interrupt_handler(int irqno, void *param)
{
    if (irqno == FUSB3_0_IRQ_NUM) {
        USBH_IRQHandler(FUSB3_ID_0);
    } else if (irqno == FUSB3_1_IRQ_NUM) {
        USBH_IRQHandler(FUSB3_ID_1);
    }
}

void usb_hc_setup_xhci_interrupt(uint32_t id)
{
    uint32_t irq_num = (id == FUSB3_ID_0) ? FUSB3_0_IRQ_NUM : FUSB3_1_IRQ_NUM;
    rt_hw_interrupt_set_priority(irq_num, 0xd0);
    rt_hw_interrupt_install(irq_num, usb_hc_xhci_interrupt_handler, 
                            NULL, "xhci");
    rt_hw_interrupt_umask(irq_num);
}

void usb_hc_revoke_xhci_interrupt(uint32_t id)
{
    uint32_t irq_num = (id == FUSB3_ID_0) ? FUSB3_0_IRQ_NUM : FUSB3_1_IRQ_NUM;

    rt_hw_interrupt_mask(irq_num);
}

unsigned long usb_hc_get_register_base(uint32_t id)
{
    if (FUSB3_ID_0 == id)
        return FUSB3_0_BASE_ADDR + FUSB3_XHCI_OFFSET;
    else
        return FUSB3_1_BASE_ADDR + FUSB3_XHCI_OFFSET;
}