/*
 * Copyright (c) 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_dwc2_param.h"
#include "rtthread.h"
#include "cybsp.h"
#include "cy_device.h"

#if defined (COMPONENT_CM55)

#if !defined(CONFIG_USB_DCACHE_ENABLE)
#error "Please enable CONFIG_USB_DCACHE_ENABLE and put USB_NOCACHE_RAM_SECTION to section ".cy_socmem_data" for CM55"
#endif

#else
#define CONFIG_USB_DWC2_DMA_ENABLE
#endif

const struct dwc2_user_params param_common = {
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = 0x21F,
    .device_tx_fifo_size = {
        [0] = 16,    // 64 byte
        [1] = 0x300, // 1024 byte, tripple buffer
        [2] = 0x300, // 1024 byte, tripple buffer
        [3] = 0x300, // 1024 byte, tripple buffer
        [4] = 0x300, // 1024 byte, tripple buffer
        [5] = 0x300, // 1024 byte, tripple buffer
        [6] = 0x300, // 1024 byte, tripple buffer
        [7] = 0x300, // 1024 byte, tripple buffer
        [8] = 0x300, // 1024 byte, tripple buffer
        [9] = 0,
        [10] = 0,
        [11] = 0,
        [12] = 0,
        [13] = 0,
        [14] = 0,
        [15] = 0 },

    .host_dma_desc_enable = false,
    .host_rx_fifo_size = 0x21F,
    .host_nperio_tx_fifo_size = 0x100, // 512 byte, double buffer
    .host_perio_tx_fifo_size = 0x400,  // 1024 byte, four buffer

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

void USBHS_DEVICE_IRQHandler(void)
{
    USBD_IRQHandler(0);
}

void usb_dc_low_level_init(uint8_t busid)
{
    USBHS_SS->SUBSYSTEM_CTL = (1 << USBHS_SS_SUBSYSTEM_CTL_AHB_MASTER_SYNC_Pos) | USBHS_SS_SUBSYSTEM_CTL_SS_ENABLE_Msk;
    USBHS_SS->PHY_FUNC_CTL_1 |= (7 << USBHS_SS_PHY_FUNC_CTL_1_PLL_FSEL_Pos);
    USBHS_SS->PHY_FUNC_CTL_2 |= (USBHS_SS_PHY_FUNC_CTL_2_RES_TUNING_SEL_Msk | USBHS_SS_PHY_FUNC_CTL_2_EFUSE_SEL_Msk);

    rt_thread_mdelay(200); /* Wait for PHY stable */

    cy_stc_sysint_t usb_int_cfg = {
        .intrSrc = usbhs_interrupt_usbhsctrl_IRQn,
        .intrPriority = 3
    };

    /* Install the interrupt service routine */
    Cy_SysInt_Init(&usb_int_cfg, USBHS_DEVICE_IRQHandler);

    NVIC_EnableIRQ(usbhs_interrupt_usbhsctrl_IRQn);
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    NVIC_DisableIRQ(usbhs_interrupt_usbhsctrl_IRQn);
}

void usbd_dwc2_delay_ms(uint8_t ms)
{
    rt_thread_mdelay(ms);
}

uint32_t usbd_dwc2_get_system_clock(void)
{
    return SystemCoreClock;
}

void USBHS_HOST_IRQHandler(void)
{
    USBH_IRQHandler(0);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    USBHS_SS->SUBSYSTEM_CTL = (1 << USBHS_SS_SUBSYSTEM_CTL_AHB_MASTER_SYNC_Pos) | USBHS_SS_SUBSYSTEM_CTL_USB_MODE_Msk | USBHS_SS_SUBSYSTEM_CTL_SS_ENABLE_Msk;
    USBHS_SS->PHY_FUNC_CTL_1 |= (7 << USBHS_SS_PHY_FUNC_CTL_1_PLL_FSEL_Pos);
    USBHS_SS->PHY_FUNC_CTL_2 |= (USBHS_SS_PHY_FUNC_CTL_2_RES_TUNING_SEL_Msk | USBHS_SS_PHY_FUNC_CTL_2_EFUSE_SEL_Msk);

    rt_thread_mdelay(200); /* Wait for PHY stable */

    cy_stc_sysint_t usb_int_cfg = {
        .intrSrc = usbhs_interrupt_usbhsctrl_IRQn,
        .intrPriority = 3
    };

    /* Install the interrupt service routine */
    Cy_SysInt_Init(&usb_int_cfg, USBHS_HOST_IRQHandler);

    NVIC_EnableIRQ(usbhs_interrupt_usbhsctrl_IRQn);
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    NVIC_DisableIRQ(usbhs_interrupt_usbhsctrl_IRQn);
}

#ifdef CONFIG_USB_DCACHE_ENABLE
void usb_dcache_clean(uintptr_t addr, size_t size)
{
    SCB_CleanDCache_by_Addr((void *)addr, size);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    SCB_InvalidateDCache_by_Addr((void *)addr, size);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    SCB_CleanInvalidateDCache_by_Addr((void *)addr, size);
}
#endif
