/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_dwc2_param.h"

extern unsigned int system_core_clock;

uint32_t SystemCoreClock;

const struct dwc2_user_params param_pa11_pa12 = {
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
    .device_dma_enable = false,
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (320 - 16 - 16 - 16 - 16),
    .device_tx_fifo_size = {
        [0] = 16, // 64 byte
        [1] = 16, // 64 byte
        [2] = 16, // 64 byte
        [3] = 16, // 64 byte
        [4] = 0,
        [5] = 0,
        [6] = 0,
        [7] = 0,
        [8] = 0,
        [9] = 0,
        [10] = 0,
        [11] = 0,
        [12] = 0,
        [13] = 0,
        [14] = 0,
        [15] = 0 },
#ifdef AT32F415xx
    .device_gccfg = ((1 << 16) | (1 << 18) | (1 << 19) | (1 << 21)),
#else
    .device_gccfg = ((1 << 16) | (1 << 21)),
#endif
    .total_fifo_size = 320 // 1280 byte
};

#if __has_include("at32f402_405.h")
#include "at32f402_405.h"

const struct dwc2_user_params param_pb14_pb15 = {
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
    .device_dma_enable = true,
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (1008 - 16 - 256 - 128 - 128 - 128 - 128),
    .device_tx_fifo_size = {
        [0] = 16,  // 64 byte
        [1] = 256, // 1024 byte
        [2] = 128, // 512 byte
        [3] = 128, // 512 byte
        [4] = 128, // 512 byte
        [5] = 128, // 512 byte
        [6] = 0,
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
    .host_rx_fifo_size = 624,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte

    .device_gccfg = ((1 << 16) | (1 << 21)),
    .host_gccfg = ((1 << 16) | (1 << 21))
};
#endif

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM
void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
    SystemCoreClock = system_core_clock;

#if __has_include("at32f402_405.h")
    if (reg_base == OTGHS_BASE) {
        memcpy(params, &param_pb14_pb15, sizeof(struct dwc2_user_params));
    } else {
        memcpy(params, &param_pa11_pa12, sizeof(struct dwc2_user_params));
    }
#else
    memcpy(params, &param_pa11_pa12, sizeof(struct dwc2_user_params));
#endif
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

void usbd_dwc2_delay_ms(uint8_t ms)
{
    uint32_t count = SystemCoreClock / 1000 * ms;
    while (count--) {
        __asm volatile("nop");
    }
}
