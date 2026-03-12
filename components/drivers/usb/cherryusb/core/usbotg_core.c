/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbotg_core.h"

#ifdef CONFIG_USB_OTG_ENABLE
#undef USB_DBG_TAG
#define USB_DBG_TAG "usbotg_core"
#include "usb_log.h"

#define CONFIG_USB_OTG_MAX_BUS CONFIG_USBHOST_MAX_BUS

struct usbotg_core_priv {
    uint8_t busid;
    uint32_t reg_base;
    bool usbh_initialized;
    bool usbd_initialized;
    usbd_event_handler_t device_event_callback;
    usbh_event_handler_t host_event_callback;
    uint8_t request_mode;
    usb_osal_sem_t change_sem;
    usb_osal_thread_t change_thread;
} g_usbotg_core[CONFIG_USB_OTG_MAX_BUS];

static void usbotg_host_initialize(uint8_t busid)
{
    if (g_usbotg_core[busid].usbh_initialized) {
        return;
    }

    if (g_usbotg_core[busid].usbd_initialized) {
        usbd_deinitialize(busid);
        g_usbotg_core[busid].usbd_initialized = false;
    }

    USB_LOG_INFO("Switch to HOST mode\r\n");

    g_usbotg_core[busid].usbh_initialized = true;
    usbh_initialize(busid, g_usbotg_core[busid].reg_base);
}

static void usbotg_device_initialize(uint8_t busid)
{
    if (g_usbotg_core[busid].usbd_initialized) {
        return;
    }

    if (g_usbotg_core[busid].usbh_initialized) {
        usbh_deinitialize(busid);
        g_usbotg_core[busid].usbh_initialized = false;
    }

    USB_LOG_INFO("Switch to DEVICE mode\r\n");

    g_usbotg_core[busid].usbd_initialized = true;
    usbd_initialize(g_usbotg_core[busid].busid, g_usbotg_core[busid].reg_base, g_usbotg_core[busid].device_event_callback);
}

static void usbotg_rolechange_thread(void *argument)
{
    uint8_t busid = (uint8_t)(uintptr_t)argument;

    usb_otg_init(busid);

    while (1) {
        if (usb_osal_sem_take(g_usbotg_core[busid].change_sem, USB_OSAL_WAITING_FOREVER) == 0) {
            if (g_usbotg_core[busid].request_mode == USBOTG_MODE_HOST) {
                usbotg_host_initialize(busid);
            } else if (g_usbotg_core[busid].request_mode == USBOTG_MODE_DEVICE) {
                usbotg_device_initialize(busid);
            }
        }
    }
}

int usbotg_initialize(uint8_t busid, uint32_t reg_base, usbd_event_handler_t device_event_callback, usbh_event_handler_t host_event_callback, uint8_t default_role)
{
    char thread_name[32] = { 0 };

    USB_ASSERT_MSG(busid < CONFIG_USB_OTG_MAX_BUS, "bus overflow\r\n");

    g_usbotg_core[busid].busid = busid;
    g_usbotg_core[busid].reg_base = reg_base;
    g_usbotg_core[busid].device_event_callback = device_event_callback;
    g_usbotg_core[busid].host_event_callback = host_event_callback;

    g_usbotg_core[busid].change_sem = usb_osal_sem_create(0);
    if (g_usbotg_core[busid].change_sem == NULL) {
        USB_LOG_ERR("Failed to create change_sem\r\n");
        while (1) {
        }
    }

    snprintf(thread_name, 32, "usbotg%u", busid);
    g_usbotg_core[busid].change_thread = usb_osal_thread_create(thread_name, 2048, 10, usbotg_rolechange_thread, (void *)(uintptr_t)busid);
    if (g_usbotg_core[busid].change_thread == NULL) {
        USB_LOG_ERR("Failed to create usbotg thread\r\n");
        while (1) {
        }
    }

    usbotg_trigger_role_change(busid, default_role);
    return 0;
}

int usbotg_deinitialize(uint8_t busid)
{
    USB_ASSERT_MSG(busid < CONFIG_USB_OTG_MAX_BUS, "bus overflow\r\n");

    if (g_usbotg_core[busid].usbd_initialized) {
        usbd_deinitialize(busid);
        g_usbotg_core[busid].usbd_initialized = false;
    }

    if (g_usbotg_core[busid].usbh_initialized) {
        usbh_deinitialize(busid);
        g_usbotg_core[busid].usbh_initialized = false;
    }

    if (g_usbotg_core[busid].change_thread) {
        usb_osal_thread_delete(g_usbotg_core[busid].change_thread);
    }

    if (g_usbotg_core[busid].change_sem) {
        usb_otg_deinit(busid);
        usb_osal_sem_delete(g_usbotg_core[busid].change_sem);
    }

    return 0;
}

void usbotg_trigger_role_change(uint8_t busid, uint8_t mode)
{
    USB_ASSERT_MSG(busid < CONFIG_USB_OTG_MAX_BUS, "bus overflow\r\n");

    g_usbotg_core[busid].request_mode = mode;

    if (g_usbotg_core[busid].change_sem) {
        usb_osal_sem_give(g_usbotg_core[busid].change_sem);
    }
}

void USBOTG_IRQHandler(uint8_t busid)
{
    USB_ASSERT_MSG(busid < CONFIG_USB_OTG_MAX_BUS, "bus overflow\r\n");

    if (g_usbotg_core[busid].usbh_initialized) {
        USBH_IRQHandler(busid);
    } else if (g_usbotg_core[busid].usbd_initialized) {
        USBD_IRQHandler(busid);
    }
}
#endif /* CONFIG_USB_OTG_ENABLE */