/*
 * Copyright (c) 2022-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "usbh_core.h"
#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_usb_drv.h"
#include "usb_glue_hpm.h"

#if !defined(CONFIG_USB_EHCI_HPMICRO) || !CONFIG_USB_EHCI_HPMICRO
#error "hpm ehci must set CONFIG_USB_EHCI_HPMICRO=1"
#endif

#if !defined(CONFIG_USB_EHCI_HCCR_OFFSET) || CONFIG_USB_EHCI_HCCR_OFFSET != 0x100
#error "hpm ehci must config CONFIG_USB_EHCI_HCCR_OFFSET to 0x100"
#endif

extern void (*g_usb_hpm_irq[2])(uint8_t busid);
extern uint8_t g_usb_hpm_busid[2];

static void usb_host_mode_init(USB_Type *ptr)
{
    /* Set mode to host, must be set immediately after reset */
    ptr->USBMODE &= ~USB_USBMODE_CM_MASK;
    ptr->USBMODE |= USB_USBMODE_CM_SET(3);

    /* Set the endian */
    ptr->USBMODE &= ~USB_USBMODE_ES_MASK;

    /* Set parallel interface signal */
    ptr->PORTSC1 &= ~USB_PORTSC1_STS_MASK;

    /* Set parallel transceiver width */
    ptr->PORTSC1 &= ~USB_PORTSC1_PTW_MASK;

#ifdef CONFIG_USB_HOST_FORCE_FULL_SPEED
    /* Set usb forced to full speed mode */
    ptr->PORTSC1 |= USB_PORTSC1_PFSC_MASK;
#endif

    /* Not use interrupt threshold. */
    ptr->USBCMD &= ~USB_USBCMD_ITC_MASK;
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    usb_phy_init((USB_Type *)(bus->hcd.reg_base), true);
}

void usb_hc_low_level2_init(struct usbh_bus *bus)
{
    usb_host_mode_init((USB_Type *)(bus->hcd.reg_base));

    if (bus->hcd.reg_base == HPM_USB0_BASE) {
        g_usb_hpm_busid[0] = bus->hcd.hcd_id;
        g_usb_hpm_irq[0] = USBH_IRQHandler;

        hpm_usb_isr_enable(HPM_USB0_BASE);
    } else {
#ifdef HPM_USB1_BASE
        g_usb_hpm_busid[1] = bus->hcd.hcd_id;
        g_usb_hpm_irq[1] = USBH_IRQHandler;

        hpm_usb_isr_enable(HPM_USB1_BASE);
#endif
    }
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    usb_phy_deinit((USB_Type *)(bus->hcd.reg_base));

    if (bus->hcd.reg_base == HPM_USB0_BASE) {
        hpm_usb_isr_disable(HPM_USB0_BASE);

        g_usb_hpm_busid[0] = 0;
        g_usb_hpm_irq[0] = NULL;
    } else {
#ifdef HPM_USB1_BASE
        hpm_usb_isr_disable(HPM_USB1_BASE);

        g_usb_hpm_busid[1] = 0;
        g_usb_hpm_irq[1] = NULL;
#endif
    }
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    (void)port;
    uint8_t speed;

    speed = usb_get_port_speed((USB_Type *)(bus->hcd.reg_base));

    if (speed == 0x00) {
        return USB_SPEED_FULL;
    }
    if (speed == 0x01) {
        return USB_SPEED_LOW;
    }
    if (speed == 0x02) {
        return USB_SPEED_HIGH;
    }

    return 0;
}