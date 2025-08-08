/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_dwc2_param.h"

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM

#if __has_include("stm32f1xx_hal.h")
#include "stm32f1xx_hal.h"

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

    .device_gccfg = ((1 << 16) | (1 << 21)), // fs: USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS
    .total_fifo_size = 320                   // 1280 byte
};

const struct dwc2_user_params param_pb14_pb15 = { 0 }; // do not support
#if defined(HAL_HCD_MODULE_ENABLED)
#error "HAL_HCD_MODULE_ENABLED is not supported for STM32F1xx, please use HAL_PCD_MODULE_ENABLED"
#endif
#elif __has_include("stm32f2xx_hal.h")
#include "stm32f2xx_hal.h"

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

    .device_gccfg = ((1 << 16) | (1 << 21)), // fs: USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS
    .total_fifo_size = 320                   // 1280 byte
};

const struct dwc2_user_params param_pb14_pb15 = {
#ifdef CONFIG_USB_HS
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#else
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
#endif
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (1012 - 16 - 256 - 128 - 128 - 128 - 128),
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
    .host_rx_fifo_size = 628,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte

#ifdef CONFIG_USB_HS
    .device_gccfg = 0,
    .host_gccfg = 0,
#else
    .device_gccfg = ((1 << 16) | (1 << 21)), // fs: USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS hs:0
    .host_gccfg = ((1 << 16) | (1 << 21))    // fs: USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS hs:0
#endif
};
#elif __has_include("stm32f4xx_hal.h")
#include "stm32f4xx_hal.h"

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

#if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) ||                                                 \
    defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || \
    defined(STM32F423xx)
    .device_gccfg = (1 << 16), // fs: USB_OTG_GCCFG_PWRDWN
    .b_session_valid_override = true,
#else
    .device_gccfg = ((1 << 16) | (1 << 21)), // fs: USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS
#endif
    .total_fifo_size = 320 // 1280 byte
};

const struct dwc2_user_params param_pb14_pb15 = {
#ifdef CONFIG_USB_HS
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#else
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
#endif
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (1006 - 16 - 256 - 128 - 128 - 128 - 128), // 1006/1012
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
    .host_rx_fifo_size = 622,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte
#ifdef CONFIG_USB_HS
    .device_gccfg = 0,
    .host_gccfg = 0,
#else
#if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) ||                                                 \
    defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || \
    defined(STM32F423xx)
    .device_gccfg = (1 << 16), // fs: USB_OTG_GCCFG_PWRDWN
    .host_gccfg = (1 << 16),   // fs: USB_OTG_GCCFG_PWRDWN
    .b_session_valid_override = true,
#else
    .device_gccfg = ((1 << 16) | (1 << 21)), // fs: USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS hs:0
    .host_gccfg = ((1 << 16) | (1 << 21))    // fs: USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS hs:0
#endif
#endif
};
#elif __has_include("stm32f7xx_hal.h")
#include "stm32f7xx_hal.h"

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

    .device_gccfg = (1 << 16), // fs: USB_OTG_GCCFG_PWRDWN
    .host_gccfg = (1 << 16),   // fs: USB_OTG_GCCFG_PWRDWN

    .b_session_valid_override = true,
    .total_fifo_size = 320 // 1280 byte
};

const struct dwc2_user_params param_pb14_pb15 = {
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#else
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
#endif
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (1006 - 16 - 256 - 128 - 128 - 128 - 128),
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
    .host_rx_fifo_size = 622,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    .device_gccfg = (1 << 23),       // USB_OTG_GCCFG_PHYHSEN
    .host_gccfg = (1 << 23),         // USB_OTG_GCCFG_PHYHSEN
#else
#ifdef CONFIG_USB_HS
    .device_gccfg = 0,
    .host_gccfg = 0,
#else
    .device_gccfg = (1 << 16), // fs: USB_OTG_GCCFG_PWRDWN hs:0
    .host_gccfg = (1 << 16),   // fs: USB_OTG_GCCFG_PWRDWN hs:0
#endif
#endif
    .b_session_valid_override = true
};
#elif __has_include("stm32h7xx_hal.h")
#include "stm32h7xx_hal.h"

const struct dwc2_user_params param_pa11_pa12 = {
    .phy_type = DWC2_PHY_TYPE_PARAM_FS, // DWC2_PHY_TYPE_PARAM_UTMI
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (952 - 16 - 256 - 128 - 128 - 128 - 128),
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
    .host_rx_fifo_size = 568,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte

    .device_gccfg = (1 << 16), // fs: USB_OTG_GCCFG_PWRDWN hs:0
    .host_gccfg = (1 << 16),   // fs: USB_OTG_GCCFG_PWRDWN hs:0

    .b_session_valid_override = true
};

const struct dwc2_user_params param_pb14_pb15 = {
#ifdef CONFIG_USB_HS
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#else
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
#endif
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (952 - 16 - 256 - 128 - 128 - 128 - 128),
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
    .host_rx_fifo_size = 568,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte

#ifdef CONFIG_USB_HS
    .device_gccfg = 0,
    .host_gccfg = 0,
#else
    .device_gccfg = (1 << 16), // fs: USB_OTG_GCCFG_PWRDWN hs:0
    .host_gccfg = (1 << 16),   // fs: USB_OTG_GCCFG_PWRDWN hs:0
#endif
    .b_session_valid_override = true
};
#elif __has_include("stm32h7rsxx_hal.h")
#include "stm32h7rsxx_hal.h"

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

    .device_gccfg = (1 << 16), // fs: USB_OTG_GCCFG_PWRDWN
    .b_session_valid_override = true,
    .total_fifo_size = 320 // 1280 byte
};

const struct dwc2_user_params param_pb14_pb15 = {
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (952 - 16 - 256 - 128 - 128 - 128 - 128),
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
    .host_rx_fifo_size = 568,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte

    .device_gccfg = ((1 << 23) | (1 << 24)), // hs: USB_OTG_GCCFG_VBVALEXTOEN | USB_OTG_GCCFG_VBVALOVAL
    .host_gccfg = (1 << 25)                  // hs: USB_OTG_GCCFG_PULLDOWNEN
};
#elif __has_include("stm32l4xx_hal.h")
#include "stm32l4xx_hal.h"

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

    .device_gccfg = (1 << 16),
    .b_session_valid_override = true,
    .total_fifo_size = 320 // 1280 byte
};

const struct dwc2_user_params param_pb14_pb15 = { 0 }; // do not support
#if defined(HAL_HCD_MODULE_ENABLED)
#error "HAL_HCD_MODULE_ENABLED is not supported for STM32L4xx, please use HAL_PCD_MODULE_ENABLED"
#endif
#elif __has_include("stm32u5xx_hal.h")
#include "stm32u5xx_hal.h"

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

    .device_gccfg = (1 << 16),
    .b_session_valid_override = true,
    .total_fifo_size = 320 // 1280 byte
};

#if defined(STM32U595xx) || defined(STM32U5A5xx) || defined(STM32U599xx) || defined(STM32U5A9xx) || \
    defined(STM32U5F7xx) || defined(STM32U5G7xx) || defined(STM32U5F9xx) || defined(STM32U5G9xx)
const struct dwc2_user_params param_pb14_pb15 = {
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (952 - 16 - 256 - 128 - 128 - 128 - 128),
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
    .host_rx_fifo_size = 568,
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 256,  // 1024 byte

    .device_gccfg = ((1 << 23) | (1 << 24)), // hs: USB_OTG_GCCFG_VBVALEXTOEN | USB_OTG_GCCFG_VBVALOVAL
    .host_gccfg = (1 << 25)                  // hs: USB_OTG_GCCFG_PULLDOWNEN
};
#else
const struct dwc2_user_params param_pb14_pb15 = { 0 }; // do not support
#endif
#endif

#endif // CONFIG_USB_DWC2_CUSTOM_PARAM

#if !defined(HAL_HCD_MODULE_ENABLED) && !defined(HAL_PCD_MODULE_ENABLED)
#error please define HAL_HCD_MODULE_ENABLED or HAL_PCD_MODULE_ENABLED in stm32xxx_hal_conf.h
#endif

typedef void (*usb_dwc2_irq)(uint8_t busid);

struct dwc2_instance {
    USB_OTG_GlobalTypeDef *Instance;
};

static usb_dwc2_irq g_usb_dwc2_irq[2];
static uint8_t g_usb_dwc2_busid[2] = { 0, 0 };
static struct dwc2_instance g_dwc2_instance;

#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
/**
  * @brief  Enables control of a High Speed USB PHY
  *         Init the low level hardware : GPIO, CLOCK, NVIC...
  * @param  USBx  Selected device
  * @retval HAL status
  */
static int usb_hsphy_init(uint32_t hse_value)
{
    __IO uint32_t count = 0U;

    /* Enable LDO */
    USB_HS_PHYC->USB_HS_PHYC_LDO |= USB_HS_PHYC_LDO_ENABLE;

    /* wait for LDO Ready */
    while ((USB_HS_PHYC->USB_HS_PHYC_LDO & USB_HS_PHYC_LDO_STATUS) == 0U) {
        count++;

        if (count > 200000U) {
            return -1;
        }
    }

    /* Controls PHY frequency operation selection */
    if (hse_value == 12000000U) /* HSE = 12MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x0U << 1);
    } else if (hse_value == 12500000U) /* HSE = 12.5MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x2U << 1);
    } else if (hse_value == 16000000U) /* HSE = 16MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x3U << 1);
    } else if (hse_value == 24000000U) /* HSE = 24MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x4U << 1);
    } else if (hse_value == 25000000U) /* HSE = 25MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x5U << 1);
    } else if (hse_value == 32000000U) /* HSE = 32MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x7U << 1);
    } else {
        /* ... */
    }

    /* Control the tuning interface of the High Speed PHY */
    USB_HS_PHYC->USB_HS_PHYC_TUNE |= USB_HS_PHYC_TUNE_VALUE;

    /* Enable PLL internal PHY */
    USB_HS_PHYC->USB_HS_PHYC_PLL |= USB_HS_PHYC_PLL_PLLEN;

    /* 2ms Delay required to get internal phy clock stable */
    HAL_Delay(2U);

    return 0;
}
#endif

#ifdef HAL_PCD_MODULE_ENABLED
void usb_dc_low_level_init(uint8_t busid)
{
    if (g_usbdev_bus[busid].reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = busid;
        g_usb_dwc2_irq[1] = USBD_IRQHandler;
    } else {
        g_usb_dwc2_busid[0] = busid;
        g_usb_dwc2_irq[0] = USBD_IRQHandler;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)g_usbdev_bus[busid].reg_base;
    HAL_PCD_MspInit((PCD_HandleTypeDef *)&g_dwc2_instance);

#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    usb_hsphy_init(25000000U);
#endif
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    if (g_usbdev_bus[busid].reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = 0;
        g_usb_dwc2_irq[1] = NULL;
    } else {
        g_usb_dwc2_busid[0] = 0;
        g_usb_dwc2_irq[0] = NULL;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)g_usbdev_bus[busid].reg_base;
    HAL_PCD_MspDeInit((PCD_HandleTypeDef *)&g_dwc2_instance);
}
#endif

#ifdef HAL_HCD_MODULE_ENABLED
void usb_hc_low_level_init(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = bus->hcd.hcd_id;
        g_usb_dwc2_irq[1] = USBH_IRQHandler;
    } else {
        g_usb_dwc2_busid[0] = bus->hcd.hcd_id;
        g_usb_dwc2_irq[0] = USBH_IRQHandler;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)bus->hcd.reg_base;
    HAL_HCD_MspInit((HCD_HandleTypeDef *)&g_dwc2_instance);

#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    usb_hsphy_init(25000000U);
#endif
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = 0;
        g_usb_dwc2_irq[1] = NULL;
    } else {
        g_usb_dwc2_busid[0] = 0;
        g_usb_dwc2_irq[0] = NULL;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)bus->hcd.reg_base;
    HAL_HCD_MspDeInit((HCD_HandleTypeDef *)&g_dwc2_instance);
}
#endif

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM
void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
    if (reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        memcpy(params, &param_pb14_pb15, sizeof(struct dwc2_user_params));
    } else {
        memcpy(params, &param_pa11_pa12, sizeof(struct dwc2_user_params));
    }
#ifdef CONFIG_USB_DWC2_CUSTOM_FIFO
    struct usb_dwc2_user_fifo_config s_dwc2_fifo_config;

    dwc2_get_user_fifo_config(reg_base, &s_dwc2_fifo_config);

    params->device_rx_fifo_size = s_dwc2_fifo_config.device_rx_fifo_size;
    for (uint8_t i = 0; i < MAX_EPS_CHANNELS; i++)
    {
        params->device_tx_fifo_size[i] = s_dwc2_fifo_config.device_tx_fifo_size[i];
    }
#endif
}
#endif

extern uint32_t SystemCoreClock;

void usbd_dwc2_delay_ms(uint8_t ms)
{
    uint32_t count = SystemCoreClock / 1000 * ms;
    while (count--) {
        __asm volatile("nop");
    }
}

void OTG_FS_IRQHandler(void)
{
    g_usb_dwc2_irq[0](g_usb_dwc2_busid[0]);
}

void OTG_HS_IRQHandler(void)
{
    g_usb_dwc2_irq[1](g_usb_dwc2_busid[1]);
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