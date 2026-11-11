/*
 * Copyright (c) 2026, HakumenJean
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-06     HakumenJean  first version
 */

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "usbh_core.h"
#include "usb_hc_ehci.h"
#ifdef CONFIG_USB_EHCI_WITH_OHCI
#include "usb_hc_ohci.h"
#endif

#include "hal_clk.h"
#include "hal_reset.h"
#include "interrupt.h"

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

#define USB0_OTG_BASE_ADDR              (0x04100000U)
#define USB0_PHY_BASE_ADDR              (0x04100400U)
#define USB0_EHCI_BASE_ADDR             (0x04101000U)

#define USB1_EHCI_BASE_ADDR             (0x04200000U)
#define USB1_PHY_BASE_ADDR              (0x04200800U)

void usb_select_phyTohci(void)
{
    *(volatile rt_uint32_t *)(USB0_OTG_BASE_ADDR + 0x420) &= ~(1 << 0);
}

void usb_gate_open(rt_uint8_t busid)
{
    if (busid == 0) {
        /* otg gate open*/
        hal_clock_enable(hal_clock_get(HAL_SUNXI_CCU, CLK_BUS_OTG));

        /* otg bus reset */
        hal_reset_control_reset(hal_reset_control_get(HAL_SUNXI_RESET, RST_BUS_OTG));

        /* ehci gate open */
        hal_clock_enable(hal_clock_get(HAL_SUNXI_CCU, CLK_BUS_EHCI0));

        /* ehci bus reset */
        hal_reset_control_reset(hal_reset_control_get(HAL_SUNXI_RESET, RST_BUS_EHCI0));

        /* ohci gate open */
        hal_clock_enable(hal_clock_get(HAL_SUNXI_CCU, CLK_BUS_OHCI0));

        /* ohci bus reset */
        hal_reset_control_reset(hal_reset_control_get(HAL_SUNXI_RESET, RST_BUS_OHCI0));

        /* clock enable */
        hal_clock_enable(hal_clock_get(HAL_SUNXI_CCU, CLK_USB_OHCI0));

        /* reset phy */
        hal_reset_control_reset(hal_reset_control_get(HAL_SUNXI_RESET, RST_USB_PHY0));

        /* otg phy select */
        usb_select_phyTohci();
    } else {
        /* ehci gate open */
        hal_clock_enable(hal_clock_get(HAL_SUNXI_CCU, CLK_BUS_EHCI1));

        /* ehci bus reset */
        hal_reset_control_reset(hal_reset_control_get(HAL_SUNXI_RESET, RST_BUS_EHCI1));

        /* ohci gate open */
        hal_clock_enable(hal_clock_get(HAL_SUNXI_CCU, CLK_BUS_OHCI1));

        /* ohci bus reset */
        hal_reset_control_reset(hal_reset_control_get(HAL_SUNXI_RESET, RST_BUS_OHCI1));

        /* clock enable */
        hal_clock_enable(hal_clock_get(HAL_SUNXI_CCU, CLK_USB_OHCI1));

        /* reset phy */
        hal_reset_control_reset(hal_reset_control_get(HAL_SUNXI_RESET, RST_USB_PHY1));
    }
}

void usb_clean_siddp(struct usbh_bus *bus)
{
    *(volatile rt_uint32_t *)(bus->hcd.reg_base + 0x810) &= ~(1 << 3);
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

    rt_interrupt_enter();

    USB_LOG_DBG("t113_ehci_isr");

    extern void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(bus->hcd.hcd_id);

    rt_interrupt_leave();
}

#ifdef CONFIG_USB_EHCI_WITH_OHCI

void t113_ohci_isr(int vector, void *arg)
{
    struct usbh_bus *bus = (struct usbh_bus *)arg;

    rt_interrupt_enter();

    USB_LOG_DBG("t113_ohci_isr");

    extern void OHCI_IRQHandler(uint8_t busid);
    OHCI_IRQHandler(bus->hcd.hcd_id);

    rt_interrupt_leave();
}

#endif

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    int vector;
    RT_ASSERT(bus->busid <= 1);

    usb_gate_open(bus->busid);
    usb_clean_siddp(bus);
    usb_hci_set_passby(bus);

    /* register EHCI interrupt callback */
    vector = SUNXI_IRQ_USB0_EHCI + (bus->busid > 0 ? 3 : 0);
    rt_hw_interrupt_install(vector, t113_ehci_isr, bus, RT_NULL);
    rt_hw_interrupt_set_priority(vector, 11 << 4);
    rt_hw_interrupt_umask(vector);

    /* register OHCI interrupt callback */
#ifdef CONFIG_USB_EHCI_WITH_OHCI
    rt_hw_interrupt_install(vector + 1, t113_ohci_isr, bus, RT_NULL);
    rt_hw_interrupt_set_priority(vector, 11 << 4);
    rt_hw_interrupt_umask(vector + 1);
#endif

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
    usbh_initialize(0, USB0_EHCI_BASE_ADDR, NULL);
#endif

#ifdef T113_USING_USB1_HOST
    /* USB1 MSC test OK */
    usbh_initialize(1, USB1_EHCI_BASE_ADDR, NULL);
#endif
    return 0;
}

#ifdef PKG_CHERRYUSB_HOST

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

INIT_ENV_EXPORT(__usbh_init);

#ifdef CONFIG_USB_DCACHE_ENABLE
void usb_dcache_clean(uintptr_t addr, size_t size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)addr, size);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)addr, size);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)addr, size);
}
#endif

#endif
