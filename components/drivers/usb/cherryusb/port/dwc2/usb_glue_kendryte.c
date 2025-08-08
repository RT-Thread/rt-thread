/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtthread.h>
#include <rthw.h>
#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_dwc2_param.h"

#include <riscv_io.h>
#include "sysctl_rst.h"
#include "ioremap.h"
#include "mmu.h"
#include "cache.h"

extern rt_mmu_info mmu_info;

#if defined(ENABLE_CHERRY_USB) || defined(PKG_USING_CHERRYUSB) || defined(RT_USING_CHERRYUSB)
#define DEFAULT_USB_HCLK_FREQ_MHZ 200

uint32_t SystemCoreClock = (DEFAULT_USB_HCLK_FREQ_MHZ * 1000 * 1000);

const uintptr_t usb_dev_addr[2] = { 0x91500000UL, 0x91540000UL };

#define USB_IDPULLUP0   (1 << 4)
#define USB_DMPULLDOWN0 (1 << 8)
#define USB_DPPULLDOWN0 (1 << 9)

const struct dwc2_user_params param_common = {
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (3016 - 16 - 256 * 8),
    .device_tx_fifo_size = {
        [0] = 16,  // 64 byte
        [1] = 512, // 1024 byte, double buffer
        [2] = 256, // 1024 byte
        [3] = 512, // 1024 byte, double buffer
        [4] = 256, // 1024 byte
        [5] = 256, // 1024 byte
        [6] = 256, // 1024 byte
        [7] = 0,
        [8] = 0,
        [9] = 0,
        [10] = 0,
        [11] = 0,
        [12] = 0,
        [13] = 0,
        [14] = 0,
        [15] = 0 },

    .host_dma_desc_enable = false,
    .host_rx_fifo_size = 3016 - 128 * 2 - 256 * 2,
    .host_nperio_tx_fifo_size = 128 * 2, // 512 byte, double buffer
    .host_perio_tx_fifo_size = 256 * 2,  // 1024 byte, double buffer

    .device_gccfg = 0,
    .host_gccfg = 0
};

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM
void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
    memcpy(params, &param_common, sizeof(struct dwc2_user_params));
#ifdef CONFIG_USB_DWC2_CUSTOM_FIFO
    struct usb_dwc2_user_fifo_config s_dwc2_fifo_config;

    dwc2_get_user_fifo_config(reg_base, &s_dwc2_fifo_config);

    params->device_rx_fifo_size = s_dwc2_fifo_config.device_rx_fifo_size;
    for (uint8_t i = 0; i < MAX_EPS_CHANNELS; i++) {
        params->device_tx_fifo_size[i] = s_dwc2_fifo_config.device_tx_fifo_size[i];
    }
#endif
}
#endif

// USB Host
#if defined(ENABLE_CHERRY_USB_HOST) || defined(PKG_CHERRYUSB_HOST) || defined(RT_CHERRYUSB_HOST)
static void usb_hc_interrupt_cb(int irq, void *arg_pv)
{
    USBH_IRQHandler((uint8_t)(uintptr_t)arg_pv);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    uint32_t *hs_reg;
    uint32_t usb_ctl3;

    if ((uintptr_t)rt_hw_mmu_v2p(&mmu_info, (void *)bus->hcd.reg_base) == usb_dev_addr[0]) {
        if (!sysctl_reset(SYSCTL_RESET_USB0)) {
            USB_LOG_ERR("reset usb0 fail\n");
        }

        hs_reg = (uint32_t *)rt_ioremap((void *)(0x91585000 + 0x7C), 0x1000);
        usb_ctl3 = *hs_reg | USB_IDPULLUP0;

        *hs_reg = usb_ctl3 | (USB_DMPULLDOWN0 | USB_DPPULLDOWN0);

        rt_iounmap(hs_reg);

        rt_hw_interrupt_install(173, usb_hc_interrupt_cb, (void *)(uintptr_t)bus->hcd.hcd_id, "usbh0");
        rt_hw_interrupt_umask(173);

    } else {
        if (!sysctl_reset(SYSCTL_RESET_USB1)) {
            USB_LOG_ERR("reset usb1 fail\n");
        }

        hs_reg = (uint32_t *)rt_ioremap((void *)(0x91585000 + 0x9C), 0x1000);
        usb_ctl3 = *hs_reg | USB_IDPULLUP0;

        *hs_reg = usb_ctl3 | (USB_DMPULLDOWN0 | USB_DPPULLDOWN0);

        rt_iounmap(hs_reg);

        rt_hw_interrupt_install(174, usb_hc_interrupt_cb, (void *)(uintptr_t)bus->hcd.hcd_id, "usbh1");
        rt_hw_interrupt_umask(174);
    }
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    if ((uintptr_t)rt_hw_mmu_v2p(&mmu_info, (void *)bus->hcd.reg_base) == usb_dev_addr[0]) {
        rt_hw_interrupt_mask(173);
    } else {
        rt_hw_interrupt_mask(174);
    }
}
#endif // ENABLE_CHERRY_USB_HOST

// USB Device
#if defined(ENABLE_CHERRY_USB_DEVICE) || defined(PKG_CHERRYUSB_DEVICE) || defined(RT_CHERRYUSB_DEVICE)
static void usb_dc_interrupt_cb(int irq, void *arg_pv)
{
    USBD_IRQHandler((uint8_t)(uintptr_t)arg_pv);
}

void usb_dc_low_level_init(uint8_t busid)
{
    if ((uintptr_t)rt_hw_mmu_v2p(&mmu_info, (void *)g_usbdev_bus[busid].reg_base) == usb_dev_addr[0]) {
        if (!sysctl_reset(SYSCTL_RESET_USB0)) {
            USB_LOG_ERR("reset usb0 fail\n");
        }

        uint32_t *hs_reg = (uint32_t *)rt_ioremap((void *)(0x91585000 + 0x7C), 0x1000);
        *hs_reg = 0x37;
        rt_iounmap(hs_reg);

        rt_hw_interrupt_install(173, usb_dc_interrupt_cb, (void *)(uintptr_t)busid, "usbd0");
        rt_hw_interrupt_umask(173);
    } else {
        if (!sysctl_reset(SYSCTL_RESET_USB1)) {
            USB_LOG_ERR("reset usb1 fail\n");
        }

        uint32_t *hs_reg = (uint32_t *)rt_ioremap((void *)(0x91585000 + 0x9C), 0x1000);
        *hs_reg = 0x37;
        rt_iounmap(hs_reg);

        rt_hw_interrupt_install(174, usb_dc_interrupt_cb, (void *)(uintptr_t)busid, "usbd1");
        rt_hw_interrupt_umask(174);
    }
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    if ((uintptr_t)rt_hw_mmu_v2p(&mmu_info, (void *)g_usbdev_bus[busid].reg_base) == usb_dev_addr[0]) {
        rt_hw_interrupt_mask(173);
    } else {
        rt_hw_interrupt_mask(174);
    }
}
#endif // ENABLE_CHERRY_USB_DEVICE

void usbd_dwc2_delay_ms(uint8_t ms)
{
    rt_thread_mdelay(ms);
}

#ifdef CONFIG_USB_DCACHE_ENABLE
void usb_dcache_clean(uintptr_t addr, size_t size)
{
    rt_hw_cpu_dcache_clean((void *)addr, size);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    rt_hw_cpu_dcache_invalidate((void *)addr, size);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    rt_hw_cpu_dcache_clean_flush((void *)addr, size);
}
#endif

#endif // ENABLE_CHERRY_USB
