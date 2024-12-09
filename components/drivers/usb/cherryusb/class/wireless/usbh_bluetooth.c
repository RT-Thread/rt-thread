/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_bluetooth.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_bluetooth"
#include "usb_log.h"

#define DEV_FORMAT "/dev/bluetooth"

static struct usbh_bluetooth g_bluetooth_class;

#ifdef CONFIG_USBHOST_BLUETOOTH_HCI_H4
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bluetooth_tx_buf[1 + CONFIG_USBHOST_BLUETOOTH_TX_SIZE];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bluetooth_rx_buf[1 + CONFIG_USBHOST_BLUETOOTH_RX_SIZE];
#else
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bluetooth_cmd_buf[1 + 256];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bluetooth_evt_buf[1 + 256];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bluetooth_tx_buf[1 + CONFIG_USBHOST_BLUETOOTH_TX_SIZE];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_bluetooth_rx_buf[1 + CONFIG_USBHOST_BLUETOOTH_RX_SIZE];
#endif

static int usbh_bluetooth_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret = 0;
#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
    uint8_t mult;
    uint16_t mps;
#endif

    struct usbh_bluetooth *bluetooth_class = &g_bluetooth_class;

#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
    if (intf != 0) {
        return 0;
    }
#endif

    memset(bluetooth_class, 0, sizeof(struct usbh_bluetooth));

    bluetooth_class->hport = hport;
    bluetooth_class->intf = intf;
#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
    bluetooth_class->num_of_intf_altsettings = hport->config.intf[intf + 1].altsetting_num;
#endif
    hport->config.intf[intf].priv = bluetooth_class;

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;
#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(bluetooth_class->intin, ep_desc);
            } else {
                return -USB_ERR_NOTSUPP;
            }
        } else {
#endif
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(bluetooth_class->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(bluetooth_class->bulkout, ep_desc);
            }
#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
        }
#endif
    }
#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
    USB_LOG_INFO("Num of altsettings:%u\r\n", bluetooth_class->num_of_intf_altsettings);

    for (uint8_t i = 0; i < bluetooth_class->num_of_intf_altsettings; i++) {
        USB_LOG_INFO("Altsetting:%u\r\n", i);
        for (uint8_t j = 0; j < hport->config.intf[intf + 1].altsetting[i].intf_desc.bNumEndpoints; j++) {
            ep_desc = &bluetooth_class->hport->config.intf[intf + 1].altsetting[i].ep[j].ep_desc;

            mult = USB_GET_MULT(ep_desc->wMaxPacketSize);
            mps = USB_GET_MAXPACKETSIZE(ep_desc->wMaxPacketSize);

            USB_LOG_INFO("\tEp=%02x Attr=%02u Mps=%d Interval=%02u Mult=%02u\r\n",
                         ep_desc->bEndpointAddress,
                         ep_desc->bmAttributes,
                         mps,
                         ep_desc->bInterval,
                         mult);
        }
    }

    ret = usbh_set_interface(hport, intf, 0);
    if (ret < 0) {
        return ret;
    }
    USB_LOG_INFO("Bluetooth select altsetting 0\r\n");
#endif
    strncpy(hport->config.intf[intf].devname, DEV_FORMAT, CONFIG_USBHOST_DEV_NAMELEN);
    USB_LOG_INFO("Register Bluetooth Class:%s\r\n", hport->config.intf[intf].devname);
    usbh_bluetooth_run(bluetooth_class);
    return ret;
}

static int usbh_bluetooth_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_bluetooth *bluetooth_class = (struct usbh_bluetooth *)hport->config.intf[intf].priv;

    if (hport->config.config_desc.bNumInterfaces == (intf + 1)) {
        return 0;
    }

    if (bluetooth_class) {
        if (bluetooth_class->bulkin) {
            usbh_kill_urb(&bluetooth_class->bulkin_urb);
        }

        if (bluetooth_class->bulkout) {
            usbh_kill_urb(&bluetooth_class->bulkout_urb);
        }
#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
        if (bluetooth_class->intin) {
            usbh_kill_urb(&bluetooth_class->intin_urb);
        }

        // if (bluetooth_class->isoin) {
        //     usbh_kill_urb(&bluetooth_class->isoin_urb);
        // }

        // if (bluetooth_class->isoin) {
        //     usbh_kill_urb(&bluetooth_class->isoinin_urb);
        // }
#endif
        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister Bluetooth Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_bluetooth_stop(bluetooth_class);
        }

        memset(bluetooth_class, 0, sizeof(struct usbh_bluetooth));
    }

    return ret;
}

#ifdef CONFIG_USBHOST_BLUETOOTH_HCI_LOG
static void usbh_bluetooth_hci_dump(uint8_t *data, uint32_t len)
{
    uint32_t i = 0;

    for (i = 0; i < len; i++) {
        if (i % 16 == 0) {
            USB_LOG_RAW("\r\n");
        }

        USB_LOG_RAW("%02x ", data[i]);
    }

    USB_LOG_RAW("\r\n");
}
#else
#define usbh_bluetooth_hci_dump(data, len)
#endif

static int usbh_bluetooth_hci_bulk_out(uint8_t *buffer, uint32_t buflen)
{
    struct usbh_bluetooth *bluetooth_class = &g_bluetooth_class;
    struct usbh_urb *urb = &bluetooth_class->bulkout_urb;
    int ret;

    usbh_bulk_urb_fill(urb, bluetooth_class->hport, bluetooth_class->bulkout, buffer, buflen, USB_OSAL_WAITING_FOREVER, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

#ifdef CONFIG_USBHOST_BLUETOOTH_HCI_H4
int usbh_bluetooth_hci_write(uint8_t hci_type, uint8_t *buffer, uint32_t buflen)
{
    int ret;

    g_bluetooth_tx_buf[0] = hci_type;
    memcpy(&g_bluetooth_tx_buf[1], buffer, buflen);
    usbh_bluetooth_hci_dump(g_bluetooth_tx_buf, buflen + 1);
    ret = usbh_bluetooth_hci_bulk_out(g_bluetooth_tx_buf, buflen + 1);
    return ret;
}

void usbh_bluetooth_hci_rx_thread(void *argument)
{
    int ret;
    uint32_t ep_mps;
    uint8_t retry = 0;
    uint16_t actual_len = 0;

    ep_mps = USB_GET_MAXPACKETSIZE(g_bluetooth_class.bulkin->wMaxPacketSize);

    USB_LOG_INFO("Create hc rx thread\r\n");
    while (1) {
        usbh_bulk_urb_fill(&g_bluetooth_class.bulkin_urb, g_bluetooth_class.hport, g_bluetooth_class.bulkin, &g_bluetooth_rx_buf[actual_len], ep_mps, USB_OSAL_WAITING_FOREVER, NULL, NULL);
        ret = usbh_submit_urb(&g_bluetooth_class.bulkin_urb);
        if (ret < 0) {
            if (ret == -USB_ERR_SHUTDOWN) {
                goto delete;
            } else {
                retry++;
                if (retry == 3) {
                    retry = 0;
                    goto delete;
                }
                continue;
            }
        }
        actual_len += g_bluetooth_class.bulkin_urb.actual_length;
        if (g_bluetooth_class.bulkin_urb.actual_length != ep_mps) {
            usbh_bluetooth_hci_dump(g_bluetooth_rx_buf, actual_len);
            usbh_bluetooth_hci_read_callback(g_bluetooth_rx_buf, actual_len);
            actual_len = 0;
        } else {
            /* read continue util read short packet */
        }
    }
    // clang-format off
delete :
    USB_LOG_INFO("Delete hc acl rx thread\r\n");
    usb_osal_thread_delete(NULL);
    // clang-format on
}

#else
static int usbh_bluetooth_hci_cmd(uint8_t *buffer, uint32_t buflen)
{
    struct usbh_bluetooth *bluetooth_class = &g_bluetooth_class;
    struct usb_setup_packet *setup;

    if (!bluetooth_class || !bluetooth_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = bluetooth_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = 0x00;
    setup->wValue = 0;
    setup->wIndex = bluetooth_class->intf;
    setup->wLength = buflen;

    return usbh_control_transfer(bluetooth_class->hport, setup, buffer);
}

int usbh_bluetooth_hci_write(uint8_t hci_type, uint8_t *buffer, uint32_t buflen)
{
    int ret;

    if (hci_type == USB_BLUETOOTH_HCI_CMD) {
        g_bluetooth_cmd_buf[0] = USB_BLUETOOTH_HCI_CMD;
        memcpy(&g_bluetooth_cmd_buf[1], buffer, buflen);
        usbh_bluetooth_hci_dump(g_bluetooth_cmd_buf, buflen + 1);
        ret = usbh_bluetooth_hci_cmd(&g_bluetooth_cmd_buf[1], buflen);
    } else if (hci_type == USB_BLUETOOTH_HCI_ACL) {
        g_bluetooth_tx_buf[0] = USB_BLUETOOTH_HCI_ACL;
        memcpy(&g_bluetooth_tx_buf[1], buffer, buflen);
        usbh_bluetooth_hci_dump(g_bluetooth_tx_buf, buflen + 1);
        ret = usbh_bluetooth_hci_bulk_out(&g_bluetooth_tx_buf[1], buflen);
    } else {
        ret = -1;
    }

    return ret;
}

void usbh_bluetooth_hci_evt_rx_thread(void *argument)
{
    int ret;
    uint32_t ep_mps;
    uint32_t interval;
    uint8_t retry = 0;
    uint16_t actual_len = 0;

    ep_mps = USB_GET_MAXPACKETSIZE(g_bluetooth_class.intin->wMaxPacketSize);
    interval = g_bluetooth_class.intin->bInterval;

    USB_LOG_INFO("Create hc event rx thread\r\n");
    while (1) {
        usbh_int_urb_fill(&g_bluetooth_class.intin_urb, g_bluetooth_class.hport, g_bluetooth_class.intin, &g_bluetooth_evt_buf[1 + actual_len], ep_mps, USB_OSAL_WAITING_FOREVER, NULL, NULL);
        ret = usbh_submit_urb(&g_bluetooth_class.intin_urb);
        if (ret < 0) {
            if (ret == -USB_ERR_SHUTDOWN) {
                goto delete;
            } else if (ret == -USB_ERR_NAK) {
                usb_osal_msleep(interval);
                continue;
            } else {
                retry++;
                if (retry == 3) {
                    retry = 0;
                    goto delete;
                }
                usb_osal_msleep(interval);
                continue;
            }
        }
        actual_len += g_bluetooth_class.intin_urb.actual_length;
        if (g_bluetooth_class.intin_urb.actual_length != ep_mps) {
            g_bluetooth_evt_buf[0] = USB_BLUETOOTH_HCI_EVT;
            usbh_bluetooth_hci_dump(g_bluetooth_evt_buf, actual_len + 1);
            usbh_bluetooth_hci_read_callback(g_bluetooth_evt_buf, actual_len + 1);
            actual_len = 0;
        } else {
            /* read continue util read short packet */
        }
        usb_osal_msleep(interval);
    }
    // clang-format off
delete :
    USB_LOG_INFO("Delete hc event rx thread\r\n");
    usb_osal_thread_delete(NULL);
    // clang-format on
}

void usbh_bluetooth_hci_acl_rx_thread(void *argument)
{
    int ret;
    uint32_t ep_mps;
    uint8_t retry = 0;
    uint16_t actual_len = 0;

    ep_mps = USB_GET_MAXPACKETSIZE(g_bluetooth_class.bulkin->wMaxPacketSize);

    USB_LOG_INFO("Create hc acl rx thread\r\n");
    while (1) {
        usbh_bulk_urb_fill(&g_bluetooth_class.bulkin_urb, g_bluetooth_class.hport, g_bluetooth_class.bulkin, &g_bluetooth_rx_buf[1 + actual_len], ep_mps, USB_OSAL_WAITING_FOREVER, NULL, NULL);
        ret = usbh_submit_urb(&g_bluetooth_class.bulkin_urb);
        if (ret < 0) {
            if (ret == -USB_ERR_SHUTDOWN) {
                goto delete;
            } else {
                retry++;
                if (retry == 3) {
                    retry = 0;
                    goto delete;
                }
                continue;
            }
        }
        actual_len += g_bluetooth_class.bulkin_urb.actual_length;
        if (g_bluetooth_class.bulkin_urb.actual_length != ep_mps) {
            g_bluetooth_rx_buf[0] = USB_BLUETOOTH_HCI_ACL;
            usbh_bluetooth_hci_dump(g_bluetooth_rx_buf, actual_len + 1);
            usbh_bluetooth_hci_read_callback(g_bluetooth_rx_buf, actual_len + 1);
            actual_len = 0;
        } else {
            /* read continue util read short packet */
        }
    }
    // clang-format off
delete :
    USB_LOG_INFO("Delete hc acl rx thread\r\n");
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

__WEAK void usbh_bluetooth_hci_read_callback(uint8_t *data, uint32_t len)
{
    (void)data;
    (void)len;
}

__WEAK void usbh_bluetooth_run(struct usbh_bluetooth *bluetooth_class)
{
    (void)bluetooth_class;
}

__WEAK void usbh_bluetooth_stop(struct usbh_bluetooth *bluetooth_class)
{
    (void)bluetooth_class;
}

static const struct usbh_class_driver bluetooth_class_driver = {
    .driver_name = "bluetooth",
    .connect = usbh_bluetooth_connect,
    .disconnect = usbh_bluetooth_disconnect
};

#ifdef CONFIG_USBHOST_BLUETOOTH_HCI_H4
static const uint16_t bluetooth_id_table[][2] = {
    { 0x2fe3, 0x000c },
    { 0, 0 },
};

CLASS_INFO_DEFINE const struct usbh_class_info bluetooth_h4_nrf_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .class = 0xff,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = bluetooth_id_table,
    .class_driver = &bluetooth_class_driver
};
#else
CLASS_INFO_DEFINE const struct usbh_class_info bluetooth_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .class = USB_DEVICE_CLASS_WIRELESS,
    .subclass = 0x01,
    .protocol = 0x01,
    .id_table = NULL,
    .class_driver = &bluetooth_class_driver
};
#endif
