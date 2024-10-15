/*
 * Copyright (c) 2022, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aic_core.h>
#include <aic_hal.h>
#include <hal_syscfg.h>
#include "usbh_core.h"
#include "usb_hc_ehci.h"

extern void USBH_IRQHandler(uint8_t busid);

static void aic_ehci_isr(int vector, void *arg)
{
    struct usbh_bus *bus = (struct usbh_bus *)arg;
    extern void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(bus->hcd.hcd_id);
}

static void aic_ohci_isr(int vector, void *arg)
{
    struct usbh_bus *bus = (struct usbh_bus *)arg;
    extern void OHCI_IRQHandler(uint8_t busid);
    OHCI_IRQHandler(bus->hcd.hcd_id);
}

typedef struct aic_ehci_config {
    uint32_t base_addr;
    uint32_t clk_id;
    uint32_t rst_id;
    uint32_t phy_clk_id;
    uint32_t phy_rst_id;
    uint32_t irq_num;
}aic_ehci_config_t;

aic_ehci_config_t config[] = {
#ifdef AIC_USING_USB0_HOST
    {
        USB_HOST0_BASE,
        CLK_USBH0,
        RESET_USBH0,
        CLK_USB_PHY0,
        RESET_USBPHY0,
        USB_HOST0_EHCI_IRQn
    },
#else
    {
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF
    },
#endif
#ifdef AIC_USING_USB1_HOST
    {
        USB_HOST1_BASE,
        CLK_USBH1,
        RESET_USBH1,
        CLK_USB_PHY1,
        RESET_USBPHY1,
        USB_HOST1_EHCI_IRQn
    }
#endif
};

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    uint32_t val;
    int i = 0;

    for (i=0; i<sizeof(config)/sizeof(aic_ehci_config_t); i++) {
        if (bus->hcd.reg_base == config[i].base_addr)
            break;
    }

    if (i == sizeof(config)/sizeof(aic_ehci_config_t))
        return;

    /* set usb0 phy switch: Host/Device */
    if (i == 0)
        syscfg_usb_phy0_sw_host(1);

    /* enable clock */
    hal_clk_enable(config[i].phy_clk_id);
    hal_clk_enable(config[i].clk_id);
    aicos_udelay(300);
    hal_reset_assert(config[i].phy_rst_id);
    hal_reset_assert(config[i].rst_id);
    aicos_udelay(300);
    hal_reset_deassert(config[i].phy_rst_id);
    hal_reset_deassert(config[i].rst_id);
    aicos_udelay(300);

    /* set phy type: UTMI/ULPI */
    val = readl((volatile void *)(unsigned long)(config[i].base_addr+0x800));
#ifdef FPGA_BOARD_ARTINCHIP
    /* fpga phy type = ULPI */
    writel((val  & ~0x1U), (volatile void *)(unsigned long)(config[i].base_addr+0x800));
#else
    /* board phy type = UTMI */
    writel((val | 0x1), (volatile void *)(unsigned long)(config[i].base_addr+0x800));
#endif

    /* Set AHB2STBUS_INSREG01
        Set EHCI packet buffer IN/OUT threshold (in DWORDs)
        Must increase the OUT threshold to avoid underrun. (FIFO size - 4)
    */
    writel((32 | (127 << 16)), (volatile void *)(unsigned long)(config[i].base_addr+0x94));

    /* register interrupt callback */
    aicos_request_irq(config[i].irq_num, (irq_handler_t)aic_ehci_isr,
                      0, "usb_host_ehci", bus);
    aicos_request_irq(config[i].irq_num + 1, (irq_handler_t)aic_ohci_isr,
                      0, "usb_host_ohci", bus);
    aicos_irq_enable(config[i].irq_num);
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    /* Defined by individual manufacturers */
    uint32_t regval;

    regval = EHCI_HCOR->portsc[port-1];
    if ((regval & EHCI_PORTSC_LSTATUS_MASK) == EHCI_PORTSC_LSTATUS_KSTATE)
        return USB_SPEED_LOW;

    if (regval & EHCI_PORTSC_PE)
        return USB_SPEED_HIGH;
    else
        return USB_SPEED_FULL;
}

void usb_ehci_dcache_clean(uintptr_t addr, uint32_t len)
{
    aicos_dcache_clean_range((size_t *)addr, len);
}

void usb_ehci_dcache_invalidate(uintptr_t addr, uint32_t len)
{
    aicos_dcache_invalid_range((size_t *)addr, len);
}

void usb_ehci_dcache_clean_invalidate(uintptr_t addr, uint32_t len)
{
    aicos_dcache_clean_invalid_range((size_t *)addr, len);
}

int usbh_init(void)
{
#if defined(AIC_USING_USB0_HOST) || defined(AIC_USING_USB1_HOST)
    int bus_id = 0;
#endif

#ifdef AIC_USING_USB0_HOST
    usbh_initialize(bus_id, USB_HOST0_BASE);
    bus_id++;
#endif

#ifdef AIC_USING_USB1_HOST
    usbh_initialize(bus_id, USB_HOST1_BASE);
    bus_id++;
#endif
    return 0;
}

#if defined(KERNEL_RTTHREAD)
#include <rtthread.h>
#include <rtdevice.h>

INIT_ENV_EXPORT(usbh_init);

#if defined (RT_USING_FINSH)
#include <finsh.h>

MSH_CMD_EXPORT_ALIAS(lsusb, lsusb, list usb device);
#endif
#endif