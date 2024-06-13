/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "usbh_core.h"
#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_usb_drv.h"

#if !defined(CONFIG_USB_EHCI_HPMICRO) || !CONFIG_USB_EHCI_HPMICRO
#error "hpm ehci must set CONFIG_USB_EHCI_HPMICRO=1"
#endif

#if !defined(CONFIG_USB_EHCI_HCCR_OFFSET) || CONFIG_USB_EHCI_HCCR_OFFSET != 0x100
#error "hpm ehci must config CONFIG_USB_EHCI_HCCR_OFFSET to 0x100"
#endif

static uint32_t _hcd_irqnum[CONFIG_USBHOST_MAX_BUS];
static uint8_t _hcd_busid[CONFIG_USBHOST_MAX_BUS];

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

    /* Not use interrupt threshold. */
    ptr->USBCMD &= ~USB_USBCMD_ITC_MASK;
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == HPM_USB0_BASE) {
        _hcd_irqnum[bus->hcd.hcd_id] = IRQn_USB0;
        _hcd_busid[0] = bus->hcd.hcd_id;
    } else {
#ifdef HPM_USB1_BASE
        if (bus->hcd.reg_base == HPM_USB1_BASE) {
            _hcd_irqnum[bus->hcd.hcd_id] = IRQn_USB1;
            _hcd_busid[1] = bus->hcd.hcd_id;
        }
#endif
    }

    usb_phy_init((USB_Type *)(bus->hcd.reg_base));
    intc_m_enable_irq(_hcd_irqnum[bus->hcd.hcd_id]);
}

void usb_hc_low_level2_init(struct usbh_bus *bus)
{
    usb_host_mode_init((USB_Type *)(bus->hcd.reg_base));
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

extern void USBH_IRQHandler(uint8_t busid);

void isr_usbh0(void)
{
    USBH_IRQHandler(_hcd_busid[0]);
}
SDK_DECLARE_EXT_ISR_M(IRQn_USB0, isr_usbh0)

#ifdef HPM_USB1_BASE
void isr_usbh1(void)
{
    USBH_IRQHandler(_hcd_busid[1]);
}
SDK_DECLARE_EXT_ISR_M(IRQn_USB1, isr_usbh1)
#endif
