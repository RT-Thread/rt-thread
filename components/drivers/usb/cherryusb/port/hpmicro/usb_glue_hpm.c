/*
 * Copyright (c) 2022-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_l1c_drv.h"
#include "hpm_usb_drv.h"
#include "usb_config.h"

void (*g_usb_hpm_irq[2])(uint8_t busid);
uint8_t g_usb_hpm_busid[2];

#ifndef CONFIG_CHERRYUSB_CUSTOM_IRQ_HANDLER
SDK_DECLARE_EXT_ISR_M(IRQn_USB0, hpm_isr_usb0)
#ifdef HPM_USB1_BASE
SDK_DECLARE_EXT_ISR_M(IRQn_USB1, hpm_isr_usb1)
#endif
#endif

#ifdef CONFIG_USB_OTG_ENABLE
#include "usbotg_core.h"
int usb_otg_init(uint8_t busid)
{
    (void)busid;

    return 0;
}

int usb_otg_deinit(uint8_t busid)
{
    (void)busid;

    return 0;
}

void hpm_isr_usb0(void)
{
    if (usb_otgsc_get_id_chg_flag(HPM_USB0)) {
        usb_otgsc_clear_id_chg_flag(HPM_USB0);
        usbotg_trigger_role_change(g_usb_hpm_busid[0], usb_otgsc_get_id_status(HPM_USB0) ? USBOTG_MODE_DEVICE : USBOTG_MODE_HOST);
    }

    USBOTG_IRQHandler(g_usb_hpm_busid[0]);
}

#ifdef HPM_USB1_BASE
void hpm_isr_usb1(void)
{
    if (usb_otgsc_get_id_chg_flag(HPM_USB1)) {
        usb_otgsc_clear_id_chg_flag(HPM_USB1);
        usbotg_trigger_role_change(g_usb_hpm_busid[1], usb_otgsc_get_id_status(HPM_USB1) ? USBOTG_MODE_DEVICE : USBOTG_MODE_HOST);
    }

    USBOTG_IRQHandler(g_usb_hpm_busid[1]);
}
#endif

#else

void hpm_isr_usb0(void)
{
    g_usb_hpm_irq[0](g_usb_hpm_busid[0]);
}

#ifdef HPM_USB1_BASE
void hpm_isr_usb1(void)
{
    g_usb_hpm_irq[1](g_usb_hpm_busid[1]);
}
#endif

#endif

ATTR_WEAK void hpm_usb_isr_enable(uint32_t base)
{
    if (base == HPM_USB0_BASE) {
        intc_m_enable_irq(IRQn_USB0);
    } else {
#ifdef HPM_USB1_BASE
        intc_m_enable_irq(IRQn_USB1);
#endif
    }
}

ATTR_WEAK void hpm_usb_isr_disable(uint32_t base)
{
    if (base == HPM_USB0_BASE) {
        intc_m_disable_irq(IRQn_USB0);
    } else {
#ifdef HPM_USB1_BASE
        intc_m_disable_irq(IRQn_USB1);
#endif
    }
}

#ifdef CONFIG_USB_DCACHE_ENABLE
void usb_dcache_clean(uintptr_t addr, size_t size)
{
    l1c_dc_writeback(addr, size);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    l1c_dc_invalidate(addr, size);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    l1c_dc_flush(addr, size);
}
#endif
