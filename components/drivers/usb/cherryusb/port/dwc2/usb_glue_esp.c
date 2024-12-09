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
#include "usbd_core.h"
#include "usbh_core.h"

#ifdef CONFIG_IDF_TARGET_ESP32S2
#define DEFAULT_CPU_FREQ_MHZ CONFIG_ESP32S2_DEFAULT_CPU_FREQ_MHZ
#define DEFAULT_USB_INTR_SOURCE ETS_USB_INTR_SOURCE
#elif CONFIG_IDF_TARGET_ESP32S3
#define DEFAULT_CPU_FREQ_MHZ CONFIG_ESP32S3_DEFAULT_CPU_FREQ_MHZ
#define DEFAULT_USB_INTR_SOURCE ETS_USB_INTR_SOURCE
#elif CONFIG_IDF_TARGET_ESP32P4
#define DEFAULT_CPU_FREQ_MHZ CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ
#define DEFAULT_USB_INTR_SOURCE ETS_USB_OTG_INTR_SOURCE
#else
#define DEFAULT_CPU_FREQ_MHZ 160
#endif

uint32_t SystemCoreClock = (DEFAULT_CPU_FREQ_MHZ * 1000 * 1000);
static usb_phy_handle_t s_phy_handle = NULL;
static intr_handle_t s_interrupt_handle = NULL;

static void usb_dc_interrupt_cb(void *arg_pv)
{
    extern void USBD_IRQHandler(uint8_t busid);
    USBD_IRQHandler(0);
}

void usb_dc_low_level_init(uint8_t busid)
{
    usb_phy_config_t phy_config = {
        .controller = USB_PHY_CTRL_OTG,
        .otg_mode = USB_OTG_MODE_DEVICE,
        .target = USB_PHY_TARGET_INT,
    };

    esp_err_t ret = usb_new_phy(&phy_config, &s_phy_handle);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Phy Init Failed!\r\n");
        return;
    }

    // TODO: Check when to enable interrupt
    ret = esp_intr_alloc(DEFAULT_USB_INTR_SOURCE, ESP_INTR_FLAG_LOWMED, usb_dc_interrupt_cb, 0, &s_interrupt_handle);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Interrupt Init Failed!\r\n");
        return;
    }
    USB_LOG_INFO("cherryusb, version: "CHERRYUSB_VERSION_STR"\r\n");
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    if (s_interrupt_handle) {
        esp_intr_free(s_interrupt_handle);
        s_interrupt_handle = NULL;
    }
    if (s_phy_handle) {
        usb_del_phy(s_phy_handle);
        s_phy_handle = NULL;
    }
}

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

static void usb_hc_interrupt_cb(void *arg_pv)
{
    extern void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(0);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    // Host Library defaults to internal PHY
    usb_phy_config_t phy_config = {
        .controller = USB_PHY_CTRL_OTG,
        .target = USB_PHY_TARGET_INT,
        .otg_mode = USB_OTG_MODE_HOST,
        .otg_speed = USB_PHY_SPEED_UNDEFINED, // In Host mode, the speed is determined by the connected device
        .ext_io_conf = NULL,
        .otg_io_conf = NULL,
    };

    esp_err_t ret = usb_new_phy(&phy_config, &s_phy_handle);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Phy Init Failed!\r\n");
        return;
    }

    // TODO: Check when to enable interrupt
    ret = esp_intr_alloc(DEFAULT_USB_INTR_SOURCE, ESP_INTR_FLAG_LOWMED, usb_hc_interrupt_cb, 0, &s_interrupt_handle);
    if (ret != ESP_OK) {
        USB_LOG_ERR("USB Interrupt Init Failed!\r\n");
        return;
    }
    USB_LOG_INFO("cherryusb, version: "CHERRYUSB_VERSION_STR"\r\n");
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    if (s_interrupt_handle) {
        esp_intr_free(s_interrupt_handle);
        s_interrupt_handle = NULL;
    }
    if (s_phy_handle) {
        usb_del_phy(s_phy_handle);
        s_phy_handle = NULL;
    }
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

void usbd_dwc2_delay_ms(uint8_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}