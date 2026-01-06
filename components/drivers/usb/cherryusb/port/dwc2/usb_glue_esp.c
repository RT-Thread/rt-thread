/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "sdkconfig.h"
#include "esp_idf_version.h"
#include "esp_intr_alloc.h"
#include "esp_private/usb_phy.h"
#include "soc/periph_defs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_dwc2_param.h"

#define  GET_USB_INDEX(reg_base)    0
#define GET_USB_INTR_SOURCE(reg_base)   ETS_USB_INTR_SOURCE
#define GET_USB_PHY_TARGET(reg_base)    USB_PHY_TARGET_INT
#define GET_USB_PHY_SPEED(reg_base)    USB_PHY_SPEED_UNDEFINED
#ifdef CONFIG_IDF_TARGET_ESP32S2
#define DEFAULT_CPU_FREQ_MHZ    CONFIG_ESP32S2_DEFAULT_CPU_FREQ_MHZ
#define DEFAULT_USB_INTR_SOURCE ETS_USB_INTR_SOURCE
#elif CONFIG_IDF_TARGET_ESP32S3
#define DEFAULT_CPU_FREQ_MHZ    CONFIG_ESP32S3_DEFAULT_CPU_FREQ_MHZ
#define DEFAULT_USB_INTR_SOURCE ETS_USB_INTR_SOURCE
#elif CONFIG_IDF_TARGET_ESP32P4
#undef GET_USB_INDEX
#define GET_USB_INDEX(reg_base)    ((reg_base) == (void*)ESP_USB_HS0_BASE ? 0 : 1)
#define DEFAULT_CPU_FREQ_MHZ    CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ
#define DEFAULT_USB_INTR_SOURCE ETS_USB_OTG_INTR_SOURCE
#define USB_FS_INTR_SOURCE      ETS_USB_OTG11_CH0_INTR_SOURCE
#undef GET_USB_INTR_SOURCE
#define GET_USB_INTR_SOURCE(reg_base) ((reg_base) == (void*)ESP_USB_HS0_BASE ? DEFAULT_USB_INTR_SOURCE : USB_FS_INTR_SOURCE)
#undef GET_USB_PHY_TARGET
#define GET_USB_PHY_TARGET(reg_base)    ((reg_base) == (void*)ESP_USB_HS0_BASE ? USB_PHY_TARGET_UTMI : USB_PHY_TARGET_INT)
#undef GET_USB_PHY_SPEED
#define GET_USB_PHY_SPEED(reg_base)    ((reg_base) == (void*)ESP_USB_HS0_BASE ? USB_PHY_SPEED_HIGH : USB_PHY_SPEED_FULL)
#else
#define DEFAULT_CPU_FREQ_MHZ 160
#endif

uint32_t SystemCoreClock = (DEFAULT_CPU_FREQ_MHZ * 1000 * 1000);
static usb_phy_handle_t s_phy_handle[SOC_USB_OTG_PERIPH_NUM] = {NULL};
static intr_handle_t s_interrupt_handle[SOC_USB_OTG_PERIPH_NUM] = {NULL};

#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
const struct dwc2_user_params param_fs = {
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
    .device_dma_enable = true,
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (200 - 16 * 7),
    .device_tx_fifo_size = {
        [0] = 16, // 64 byte
        [1] = 16, // 64 byte
        [2] = 16, // 64 byte
        [3] = 16, // 64 byte
        [4] = 16, // 64 byte
        [5] = 16, // 64 byte
        [6] = 16, // 64 byte
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
    .host_rx_fifo_size = 80,
    .host_nperio_tx_fifo_size = 60, // 240 byte
    .host_perio_tx_fifo_size = 60,  // 240 byte
};
#elif CONFIG_IDF_TARGET_ESP32P4
const struct dwc2_user_params param_fs = {
    .phy_type = DWC2_PHY_TYPE_PARAM_FS,
    .device_dma_enable = true,
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (200 - 16 * 7),
    .device_tx_fifo_size = {
        [0] = 16, // 64 byte
        [1] = 16, // 64 byte
        [2] = 16, // 64 byte
        [3] = 16, // 64 byte
        [4] = 16, // 64 byte
        [5] = 16, // 64 byte
        [6] = 16, // 64 byte
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
    .host_rx_fifo_size = (200 - 60 - 60),
    .host_nperio_tx_fifo_size = 60, // 240 byte
    .host_perio_tx_fifo_size = 60,  // 240 byte
};

const struct dwc2_user_params param_hs = {
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,
    .device_dma_enable = true,
    .device_dma_desc_enable = false,
    .device_rx_fifo_size = (896 - 16 - 128 - 128 - 128 - 128 - 16 - 16),
    .device_tx_fifo_size = {
        [0] = 16,  // 64 byte
        [1] = 128, // 512 byte
        [2] = 128, // 512 byte
        [3] = 128, // 512 byte
        [4] = 128, // 512 byte
        [5] = 16,  // 64 byte
        [6] = 16,  // 64 byte
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
    .host_rx_fifo_size = (896 - 128 - 128),
    .host_nperio_tx_fifo_size = 128, // 512 byte
    .host_perio_tx_fifo_size = 128,  // 512 byte
};
#endif

static void usb_dc_interrupt_cb(void *arg_pv)
{
    extern void USBD_IRQHandler(uint8_t busid);
    uint8_t busid = (uintptr_t)arg_pv;
    USBD_IRQHandler(busid);
}

void usb_dc_low_level_init(uint8_t busid)
{
    esp_err_t ret;
    void *reg_base = (void*)g_usbdev_bus[busid].reg_base;
    (void)reg_base;
    usb_phy_config_t phy_config = {
        .controller = USB_PHY_CTRL_OTG,
        .otg_mode = USB_OTG_MODE_DEVICE,
    };
    phy_config.target = GET_USB_PHY_TARGET(reg_base);
    phy_config.otg_speed = GET_USB_PHY_SPEED(reg_base);
    
    ret = usb_new_phy(&phy_config, &s_phy_handle[GET_USB_INDEX(reg_base)]);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Phy Init Failed!\r\n");
        return;
    }

    uintptr_t arg = busid;
    // TODO: Check when to enable interrupt
    ret = esp_intr_alloc(GET_USB_INTR_SOURCE(reg_base), ESP_INTR_FLAG_LOWMED, usb_dc_interrupt_cb, (void *)arg, &s_interrupt_handle[GET_USB_INDEX(reg_base)]);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Interrupt Init Failed!\r\n");
        return;
    }
    USB_LOG_INFO("cherryusb, version: " CHERRYUSB_VERSION_STR "\r\n");
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    void *reg_base = (void*)g_usbdev_bus[busid].reg_base;
    (void)reg_base;
    if (s_interrupt_handle[GET_USB_INDEX(reg_base)]) {
        esp_intr_free(s_interrupt_handle[GET_USB_INDEX(reg_base)]);
        s_interrupt_handle[GET_USB_INDEX(reg_base)] = NULL;
    }
    if (s_phy_handle[GET_USB_INDEX(reg_base)]) {
        usb_del_phy(s_phy_handle[GET_USB_INDEX(reg_base)]);
        s_phy_handle[GET_USB_INDEX(reg_base)] = NULL;
    }
}

static void usb_hc_interrupt_cb(void *arg_pv)
{
    extern void USBH_IRQHandler(uint8_t busid);
    uint8_t busid = (uintptr_t)arg_pv;
    USBH_IRQHandler(busid);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    void *reg_base = (void*)bus->hcd.reg_base;
    (void)reg_base;
    // Host Library defaults to internal PHY
    usb_phy_config_t phy_config = {
        .controller = USB_PHY_CTRL_OTG,
        .otg_mode = USB_OTG_MODE_HOST,
        .otg_speed = USB_PHY_SPEED_UNDEFINED, // In Host mode, the speed is determined by the connected device
        .ext_io_conf = NULL,
        .otg_io_conf = NULL,
    };
    phy_config.target = GET_USB_PHY_TARGET(reg_base);

    esp_err_t ret = usb_new_phy(&phy_config, &s_phy_handle[GET_USB_INDEX(reg_base)]);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Phy Init Failed!\r\n");
        return;
    }

    uintptr_t arg = bus->busid;
    // TODO: Check when to enable interrupt
    ret = esp_intr_alloc(GET_USB_INTR_SOURCE(reg_base), ESP_INTR_FLAG_LOWMED, usb_hc_interrupt_cb, (void*)(arg), &s_interrupt_handle[GET_USB_INDEX(reg_base)]);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Interrupt Init Failed!\r\n");
        return;
    }
    USB_LOG_INFO("cherryusb, version: " CHERRYUSB_VERSION_STR "\r\n");
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    void *reg_base = (void*)bus->hcd.reg_base;
    (void)reg_base;
    if (s_interrupt_handle[GET_USB_INDEX(reg_base)]) {
        esp_intr_free(s_interrupt_handle[GET_USB_INDEX(reg_base)]);
        s_interrupt_handle[GET_USB_INDEX(reg_base)] = NULL;
    }
    if (s_phy_handle[GET_USB_INDEX(reg_base)]) {
        usb_del_phy(s_phy_handle[GET_USB_INDEX(reg_base)]);
        s_phy_handle[GET_USB_INDEX(reg_base)] = NULL;
    }
}

void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
    memcpy(params, &param_fs, sizeof(struct dwc2_user_params));
#elif CONFIG_IDF_TARGET_ESP32P4
    if (reg_base == ESP_USB_HS0_BASE) {
        memcpy(params, &param_hs, sizeof(struct dwc2_user_params));
    } else {
        memcpy(params, &param_fs, sizeof(struct dwc2_user_params));
    }
#endif
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

void usbd_dwc2_delay_ms(uint8_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

#ifdef CONFIG_USB_DCACHE_ENABLE
#include "esp_cache.h"

void usb_dcache_clean(uintptr_t addr, size_t size)
{
    if (size == 0)
        return;

    esp_cache_msync((void *)addr, size, ESP_CACHE_MSYNC_FLAG_TYPE_DATA | ESP_CACHE_MSYNC_FLAG_DIR_C2M);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    if (size == 0)
        return;

    esp_cache_msync((void *)addr, size, ESP_CACHE_MSYNC_FLAG_TYPE_DATA | ESP_CACHE_MSYNC_FLAG_DIR_M2C);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    if (size == 0)
        return;

    esp_cache_msync((void *)addr, size, ESP_CACHE_MSYNC_FLAG_TYPE_DATA | ESP_CACHE_MSYNC_FLAG_DIR_C2M | ESP_CACHE_MSYNC_FLAG_DIR_M2C);
}
#endif