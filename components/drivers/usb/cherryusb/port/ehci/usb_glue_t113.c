/*
 * Copyright (c) 2025, YC113
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usb_hc_ehci.h"
#include "usb_hc_ohci.h"

#include "interrupt.h"
#include "drv_reg_base.h"
#include "drv_clock.h"

#if !defined(CONFIG_USB_EHCI_WITH_OHCI)
#error "t113 must define CONFIG_USB_EHCI_WITH_OHCI for ls/fs device"
#endif

#if CONFIG_USBHOST_MAX_BUS != 2
#error "t113 has 2 usb host controller"
#endif

#if CONFIG_USB_OHCI_HCOR_OFFSET != 0x400
#error "t113 CONFIG_USB_OHCI_HCOR_OFFSET must be 0x400"
#endif

#if defined(CONFIG_USB_EHCI_HCOR_RESERVED_DISABLE)
#error "t113 usb ehci register need reserved"
#endif

#if !defined(CONFIG_USB_EHCI_CONFIGFLAG)
#error "t113 usb ehci has configflag register"
#endif

#if defined(CONFIG_USB_EHCI_ISO)
#error "t113 usb ehci no iso register"
#endif

void usb_select_phyTohci(void)
{
    *(volatile rt_uint32_t *)(USB0_OTG_BASE_ADDR + 0x420) &= ~(1 << 0);
}

void usb_gate_open(rt_uint8_t busid)
{
    rt_uint32_t addr;

    /* otg bus reset and gate open */
    if (busid == 0)
        usb_select_phyTohci();

    /* reset phy */
    addr = (rt_uint32_t)&CCU->usb0_clk + busid * 4;
    *(volatile rt_uint32_t *)addr &= ~(1 << 30);
    sdelay(10);
    *(volatile rt_uint32_t *)addr |= 1 << 30;
    sdelay(10);

    /* ehci bus reset */
    CCU->usb_bgr &= ~((1 << 20) << busid);
    sdelay(10);
    CCU->usb_bgr |= (1 << 20) << busid;
    sdelay(10);

    /* ehci gate open */
    CCU->usb_bgr |= (1 << 4) << busid;

    /* ohci bus reset */
    CCU->usb_bgr &= ~((1 << 16) << busid);
    sdelay(10);
    CCU->usb_bgr |= (1 << 16) << busid;
    sdelay(10);

    /* ohci gate open */
    CCU->usb_bgr |= 1 << busid;

    sdelay(10);

    /* clock enable */
    *(volatile rt_uint32_t *)addr &= ~(3 << 24);
    *(volatile rt_uint32_t *)addr |= (1 << 31) | (1 << 24);

    USB_LOG_DBG("usb%d gate : %X, clock : %X\n", busid, CCU->usb_bgr, *(volatile rt_uint32_t *)addr);
}

void usb_clean_siddp(struct usbh_bus *bus)
{
    *(volatile rt_uint32_t *)(bus->hcd.reg_base + 0x810) &= ~(1 << 3);
}

static void usb_new_phyx_tp_write(struct usbh_bus *bus, int addr, int data, int len)
{
    rt_uint32_t base = bus->hcd.reg_base;

    for (int i = 0; i < len; i++) {
        *(volatile rt_uint8_t *)(base + 0x810) |= 1 << 1;

        *(volatile rt_uint8_t *)(base + 0x810 + 1) = addr + i;

        *(volatile rt_uint8_t *)(base + 0x810) &= ~(1 << 0);

        *(volatile rt_uint8_t *)(base + 0x810) &= ~(1 << 7);
        *(volatile rt_uint8_t *)(base + 0x810) |= (data & 0x1) << 7;

        *(volatile rt_uint8_t *)(base + 0x810) |= 1 << 0;

        *(volatile rt_uint8_t *)(base + 0x810) &= ~(1 << 0);

        *(volatile rt_uint8_t *)(base + 0x810) &= ~(1 << 1);

        data >>= 1;
    }
}

void usb_new_phy_init(struct usbh_bus *bus)
{
    rt_int32_t value = 0;
    rt_uint32_t efuse_val = 0x1E5080F;

    usb_new_phyx_tp_write(bus, 0x1C, 0x0, 0x03);

    /* vref mode */
    usb_new_phyx_tp_write(bus, 0x60, 0x0, 0x01);

    value = (efuse_val & 0x3C0000) >> 18;
    usb_new_phyx_tp_write(bus, 0x44, value, 0x04);

    value = (efuse_val & 0x1C00000) >> 22;
    usb_new_phyx_tp_write(bus, 0x36, value, 0x03);
}

void usb_hci_set_passby(struct usbh_bus *bus)
{
    /* AHB Master interface INCR16 enable */
    /* AHB Master interface INCR8 enable */
    /* AHB Master interface burst type INCR4 enable */
    /* AHB Master interface INCRX align enable */
    /* ULPI bypass enable */
    *(volatile rt_uint32_t *)(bus->hcd.reg_base + 0x800) |= (1 << 11) | (1 << 10) | (1 << 9) | (1 << 8) | (1 << 0);
}

void t113_ehci_isr(int vector, void *arg)
{
    struct usbh_bus *bus = (struct usbh_bus *)arg;

    USB_LOG_DBG("t113_ehci_isr");

    extern void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(bus->hcd.hcd_id);
}

void t113_ohci_isr(int vector, void *arg)
{
    struct usbh_bus *bus = (struct usbh_bus *)arg;

    USB_LOG_DBG("t113_ohci_isr");

    extern void OHCI_IRQHandler(uint8_t busid);
    OHCI_IRQHandler(bus->hcd.hcd_id);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    int vector;
    RT_ASSERT(bus->busid <= 1);

    usb_gate_open(bus->busid);
    usb_clean_siddp(bus);
    usb_hci_set_passby(bus);

    /* register EHCI interrupt callback */
    vector = T113_IRQ_USB0_EHCI + (bus->busid > 0 ? 3 : 0);
    rt_hw_interrupt_install(vector, t113_ehci_isr, bus, RT_NULL);
    rt_hw_interrupt_umask(vector);

    /* register OHCI interrupt callback */
    rt_hw_interrupt_install(vector + 1, t113_ohci_isr, bus, RT_NULL);
    rt_hw_interrupt_umask(vector + 1);

    USB_LOG_DBG("usb%d vector : %d, phy : %X\n", bus->busid, vector, *(volatile rt_uint32_t *)(bus->hcd.reg_base + 0x810));
    USB_LOG_DBG("usb%d hc low level init success\n", bus->busid);
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    /* Defined by individual manufacturers */
    uint32_t regval;

    regval = EHCI_HCOR->portsc[port - 1];
    if ((regval & EHCI_PORTSC_LSTATUS_MASK) == EHCI_PORTSC_LSTATUS_KSTATE)
        return USB_SPEED_LOW;

    if (regval & EHCI_PORTSC_PE)
        return USB_SPEED_HIGH;
    else
        return USB_SPEED_FULL;
}

int __usbh_init(void)
{
#ifdef T113_USING_USB0_HOST
    /* USB0 MSC test OK */
    usbh_initialize(0, USB0_BASE_ADDR);
#endif

#ifdef T113_USING_USB1_HOST
    /* USB1 MSC test OK */
    usbh_initialize(1, USB1_BASE_ADDR);
#endif
    return 0;
}

#ifdef PKG_CHERRYUSB_HOST

#include <rtthread.h>
#include <rtdevice.h>

INIT_ENV_EXPORT(__usbh_init);

#endif
