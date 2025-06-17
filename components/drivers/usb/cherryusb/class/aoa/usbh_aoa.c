/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_aoa.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_aoa"
#include "usb_log.h"

#define DEV_FORMAT "/dev/aoa"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_aoa_buffer[USB_ALIGN_UP(128, CONFIG_USB_ALIGN_SIZE)];

static struct usbh_aoa g_aoa_class;

int usbh_aoa_switch(struct usbh_hubport *hport, struct aoa_string_info *info)
{
    struct usb_setup_packet *setup;
    int ret;

    setup = hport->setup;

    if (setup == NULL) {
        return -USB_ERR_INVAL;
    }

    USB_LOG_INFO("Try switch into aoa mode\r\n");

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_GET_PROTOCOL;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 2;

    ret = usbh_control_transfer(hport, setup, g_aoa_buffer);
    if (ret < 0) {
        return ret;
    }

    USB_LOG_INFO("AOA version: v%d.%d\r\n", g_aoa_buffer[0], g_aoa_buffer[1]);

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_SEND_STRING;
    setup->wValue = 0;
    setup->wIndex = AOA_ACCESSORY_STRING_MANUFACTURER;
    setup->wLength = strlen(info->acc_manufacturer) + 1;

    memcpy(g_aoa_buffer, info->acc_manufacturer, strlen(info->acc_manufacturer));
    ret = usbh_control_transfer(hport, setup, g_aoa_buffer);
    if (ret < 0) {
        return ret;
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_SEND_STRING;
    setup->wValue = 0;
    setup->wIndex = AOA_ACCESSORY_STRING_MODEL;
    setup->wLength = strlen(info->acc_model) + 1;

    memcpy(g_aoa_buffer, info->acc_model, strlen(info->acc_model));
    ret = usbh_control_transfer(hport, setup, g_aoa_buffer);
    if (ret < 0) {
        return ret;
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_SEND_STRING;
    setup->wValue = 0;
    setup->wIndex = AOA_ACCESSORY_STRING_DESCRIPTION;
    setup->wLength = strlen(info->acc_description) + 1;

    memcpy(g_aoa_buffer, info->acc_description, strlen(info->acc_description));
    ret = usbh_control_transfer(hport, setup, g_aoa_buffer);
    if (ret < 0) {
        return ret;
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_SEND_STRING;
    setup->wValue = 0;
    setup->wIndex = AOA_ACCESSORY_STRING_VERSION;
    setup->wLength = strlen(info->acc_version) + 1;

    memcpy(g_aoa_buffer, info->acc_version, strlen(info->acc_version));
    ret = usbh_control_transfer(hport, setup, g_aoa_buffer);
    if (ret < 0) {
        return ret;
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_SEND_STRING;
    setup->wValue = 0;
    setup->wIndex = AOA_ACCESSORY_STRING_URI;
    setup->wLength = strlen(info->acc_uri) + 1;

    memcpy(g_aoa_buffer, info->acc_uri, strlen(info->acc_uri));
    ret = usbh_control_transfer(hport, setup, g_aoa_buffer);
    if (ret < 0) {
        return ret;
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_SEND_STRING;
    setup->wValue = 0;
    setup->wIndex = AOA_ACCESSORY_STRING_SERIAL;
    setup->wLength = strlen(info->acc_serial) + 1;

    memcpy(g_aoa_buffer, info->acc_serial, strlen(info->acc_serial));
    ret = usbh_control_transfer(hport, setup, g_aoa_buffer);
    if (ret < 0) {
        return ret;
    }

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_START;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 0;

    ret = usbh_control_transfer(hport, setup, NULL);
    if (ret < 0) {
        return ret;
    }

    USB_LOG_INFO("Switch into aoa mode success, wait usb device restart...\r\n");
    return 0;
}

int usbh_aoa_register_hid(struct usbh_aoa *aoa_class, uint16_t id, uint8_t *report, uint32_t report_len)
{
    struct usb_setup_packet *setup;
    int ret;
    uint8_t len;
    uint32_t offset;

    if (!aoa_class || !aoa_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = aoa_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_REGISTER_HID;
    setup->wValue = id;
    setup->wIndex = report_len;
    setup->wLength = 0;

    ret = usbh_control_transfer(aoa_class->hport, setup, NULL);
    if (ret < 0) {
        return ret;
    }

    offset = 0;
    while (report_len > 0) {
        len = report_len > 64 ? 64 : report_len;

        setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
        setup->bRequest = AOA_ACCESSORY_SET_HID_REPORT_DESC;
        setup->wValue = id;
        setup->wIndex = offset;
        setup->wLength = len;

        memcpy(g_aoa_buffer, report + offset, len);
        ret = usbh_control_transfer(aoa_class->hport, setup, g_aoa_buffer);
        if (ret < 0) {
            return ret;
        }
        offset += len;
        report_len -= len;
    }
    return ret;
}

int usbh_aoa_send_hid_event(struct usbh_aoa *aoa_class, uint16_t id, uint8_t *event, uint32_t event_len)
{
    struct usb_setup_packet *setup;
    int ret;
    uint8_t len;
    uint32_t offset;

    if (!aoa_class || !aoa_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = aoa_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = AOA_ACCESSORY_SEND_HID_EVENT;
    setup->wValue = id;
    setup->wIndex = 0;
    setup->wLength = event_len;

    memcpy(g_aoa_buffer, event, event_len);
    return usbh_control_transfer(aoa_class->hport, setup, event);
}

static int usbh_aoa_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret = 0;

    struct usbh_aoa *aoa_class = &g_aoa_class;

    memset(aoa_class, 0, sizeof(struct usbh_aoa));

    aoa_class->hport = hport;
    aoa_class->intf = intf;

    hport->config.intf[intf].priv = aoa_class;

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;

        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(aoa_class->bulkin, ep_desc);
        } else {
            USBH_EP_INIT(aoa_class->bulkout, ep_desc);
        }
    }

    strncpy(hport->config.intf[intf].devname, DEV_FORMAT, CONFIG_USBHOST_DEV_NAMELEN);

    USB_LOG_INFO("Register AOA Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_aoa_run(aoa_class);
    return 0;
}

static int usbh_aoa_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_aoa *aoa_class = (struct usbh_aoa *)hport->config.intf[intf].priv;

    if (aoa_class) {
        if (aoa_class->bulkin) {
            usbh_kill_urb(&aoa_class->bulkin_urb);
        }

        if (aoa_class->bulkout) {
            usbh_kill_urb(&aoa_class->bulkout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister AOA Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_aoa_stop(aoa_class);
        }

        memset(aoa_class, 0, sizeof(struct usbh_aoa));
    }

    return ret;
}

__WEAK void usbh_aoa_run(struct usbh_aoa *aoa_class)
{
    (void)aoa_class;
}

__WEAK void usbh_aoa_stop(struct usbh_aoa *aoa_class)
{
    (void)aoa_class;
}

static const uint16_t aoa_id_table[][2] = {
    { AOA_ACCESSORY_VENDOR_ID, AOA_ACCESSORY_PRODUCT_ID },
    { AOA_ACCESSORY_VENDOR_ID, AOA_ACCESSORY_ADB_PRODUCT_ID },
    { AOA_ACCESSORY_VENDOR_ID, AOA_AUDIO_PRODUCT_ID },
    { AOA_ACCESSORY_VENDOR_ID, AOA_AUDIO_ADB_PRODUCT_ID },
    { AOA_ACCESSORY_VENDOR_ID, AOA_ACCESSORY_AUDIO_PRODUCT_ID },
    { AOA_ACCESSORY_VENDOR_ID, AOA_ACCESSORY_AUDIO_ADB_PRODUCT_ID },
    { 0, 0 },
};

const struct usbh_class_driver aoa_class_driver = {
    .driver_name = "aoa",
    .connect = usbh_aoa_connect,
    .disconnect = usbh_aoa_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info aoa_intf_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS,
    .bInterfaceClass = 0xff,
    .bInterfaceSubClass = 0xff,
    .bInterfaceProtocol = 0x00,
    .id_table = aoa_id_table,
    .class_driver = &aoa_class_driver
};