/*
 * Copyright (c) 2022 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"
#include "usbh_cdc_acm.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_cdc_acm"
#include "usb_log.h"

struct usbh_cdc_acm {
    struct usb_endpoint_descriptor *intin;
    struct usbh_urb intin_urb;
    struct usb_osal_timer *modem_timer;
    uint16_t modem_status;
};

static int usbh_cdc_acm_attach(struct usbh_serial *serial)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;

    struct usbh_cdc_acm *cdc_acm_class = usb_osal_malloc(sizeof(struct usbh_cdc_acm));
    if (!cdc_acm_class) {
        USB_LOG_ERR("No memory for cdc_acm_class\r\n");
        return -USB_ERR_NOMEM;
    }
    memset(cdc_acm_class, 0, sizeof(struct usbh_cdc_acm));
    serial->priv = cdc_acm_class;

    for (uint8_t i = 0; i < serial->hport->config.intf[serial->intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &serial->hport->config.intf[serial->intf].altsetting[0].ep[i].ep_desc;

        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(cdc_acm_class->intin, ep_desc);
                break;
            } else {
            }
        }
    }

    if (!cdc_acm_class->intin) {
        USB_LOG_ERR("Failed to find interrupt endpoint\r\n");
        ret = -USB_ERR_NODEV;
        goto errout;
    }
    return 0;
errout:
    serial->priv = NULL;
    usb_osal_free(cdc_acm_class);
    return ret;
}

static void usbh_cdc_acm_detach(struct usbh_serial *serial)
{
    struct usbh_cdc_acm *cdc_acm_class;

    if (!serial || !serial->priv) {
        return;
    }

    cdc_acm_class = (struct usbh_cdc_acm *)serial->priv;
    if (cdc_acm_class->intin) {
        usbh_kill_urb(&cdc_acm_class->intin_urb);
    }
    serial->priv = NULL;
    usb_osal_free(cdc_acm_class);
}

static int usbh_cdc_acm_set_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
{
    struct usb_setup_packet *setup;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SET_LINE_CODING;
    setup->wValue = 0;
    setup->wIndex = serial->intf;
    setup->wLength = 7;

    memcpy(serial->iobuffer, line_coding, sizeof(struct cdc_line_coding));

    return usbh_control_transfer(serial->hport, setup, serial->iobuffer);
}

static int usbh_cdc_acm_get_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_GET_LINE_CODING;
    setup->wValue = 0;
    setup->wIndex = serial->intf;
    setup->wLength = 7;

    ret = usbh_control_transfer(serial->hport, setup, serial->iobuffer);
    if (ret < 0) {
        return ret;
    }
    memcpy(line_coding, serial->iobuffer, sizeof(struct cdc_line_coding));
    return ret;
}

static int usbh_cdc_acm_set_line_state(struct usbh_serial *serial, bool dtr, bool rts)
{
    struct usb_setup_packet *setup;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SET_CONTROL_LINE_STATE;
    setup->wValue = (dtr << 0) | (rts << 1);
    setup->wIndex = serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_cdc_acm_get_modem_status(struct usbh_serial *serial)
{
    struct usbh_cdc_acm *cdc_acm_class;
    uintptr_t flags;
    uint16_t status;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    flags = usb_osal_enter_critical_section();

    cdc_acm_class = (struct usbh_cdc_acm *)serial->priv;

    status = (cdc_acm_class->modem_status & CDC_SERIAL_STATE_DSR ? USBH_SERIAL_TIOCM_DSR : 0) |
             (cdc_acm_class->modem_status & CDC_SERIAL_STATE_RING ? USBH_SERIAL_TIOCM_RI : 0) |
             (cdc_acm_class->modem_status & CDC_SERIAL_STATE_DCD ? USBH_SERIAL_TIOCM_CD : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_DTR ? USBH_SERIAL_TIOCM_DTR : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_RTS ? USBH_SERIAL_TIOCM_RTS : 0);

    usb_osal_leave_critical_section(flags);

    return status;
}

#ifdef CONFIG_USBH_SERIAL_GET_MODEM_STATUS
static int __usbh_cdc_acm_get_modem_status(struct usbh_serial *serial)
{
    struct usbh_cdc_acm *cdc_acm_class;
    struct cdc_acm_notification *notification;
    uint16_t difference;
    uintptr_t flags;
    int ret;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }
    cdc_acm_class = (struct usbh_cdc_acm *)serial->priv;

    usbh_int_urb_fill(&cdc_acm_class->intin_urb, serial->hport, cdc_acm_class->intin, &serial->iobuffer[USBH_SERIAL_INT_NOCACHE_OFFSET], cdc_acm_class->intin->wMaxPacketSize, 0xffffffff, NULL, NULL);
    ret = usbh_submit_urb(&cdc_acm_class->intin_urb);
    if (ret < 0) {
        return ret;
    }

    if (cdc_acm_class->intin_urb.actual_length < sizeof(struct cdc_acm_notification)) {
        return -USB_ERR_INVAL;
    }

    notification = (struct cdc_acm_notification *)&serial->iobuffer[USBH_SERIAL_INT_NOCACHE_OFFSET];
    if (notification->bNotificationType != CDC_NOTIFICATION_SERIAL_STATE) {
        return -USB_ERR_INVAL;
    }

    flags = usb_osal_enter_critical_section();

    difference = cdc_acm_class->modem_status ^ notification->data;
    cdc_acm_class->modem_status = notification->data;

    if (difference & CDC_SERIAL_STATE_DSR)
        serial->iocount.dsr++;
    if (difference & CDC_SERIAL_STATE_DCD)
        serial->iocount.dcd++;
    if (notification->data & CDC_SERIAL_STATE_BREAK)
        serial->iocount.brk++;
    if (notification->data & CDC_SERIAL_STATE_FRAMING)
        serial->iocount.frame++;
    if (notification->data & CDC_SERIAL_STATE_PARITY)
        serial->iocount.parity++;
    if (notification->data & CDC_SERIAL_STATE_OVERRUN)
        serial->iocount.overrun++;

    usb_osal_leave_critical_section(flags);

    return ret;
}
#endif

static const struct usbh_serial_driver cdc_acm_driver = {
    .driver_name = "cdc_acm",

    .ignore_rx_header = 0,
    .ignore_tx_header = 0,

    .attach = usbh_cdc_acm_attach,
    .detach = usbh_cdc_acm_detach,
    .set_flow_control = NULL,
    .set_line_coding = usbh_cdc_acm_set_line_coding,
    .get_line_coding = usbh_cdc_acm_get_line_coding,
    .set_line_state = usbh_cdc_acm_set_line_state,
    .get_modem_status = usbh_cdc_acm_get_modem_status,
};

static int usbh_cdc_acm_connect(struct usbh_hubport *hport, uint8_t intf)
{
    return usbh_serial_probe(hport, intf, &cdc_acm_driver) ? 0 : -USB_ERR_NOMEM;
}

static int usbh_cdc_acm_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usbh_serial *serial = (struct usbh_serial *)hport->config.intf[intf].priv;

    if (serial) {
        usbh_serial_remove(serial);
    }
    return 0;
}

const struct usbh_class_driver cdc_acm_class_driver = {
    .driver_name = "cdc_acm",
    .connect = usbh_cdc_acm_connect,
    .disconnect = usbh_cdc_acm_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info cdc_acm_none_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .bInterfaceClass = USB_DEVICE_CLASS_CDC,
    .bInterfaceSubClass = CDC_ABSTRACT_CONTROL_MODEL,
    .bInterfaceProtocol = CDC_COMMON_PROTOCOL_NONE,
    .id_table = NULL,
    .class_driver = &cdc_acm_class_driver
};

CLASS_INFO_DEFINE const struct usbh_class_info cdc_acm_at_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .bInterfaceClass = USB_DEVICE_CLASS_CDC,
    .bInterfaceSubClass = CDC_ABSTRACT_CONTROL_MODEL,
    .bInterfaceProtocol = CDC_COMMON_PROTOCOL_AT_COMMANDS,
    .id_table = NULL,
    .class_driver = &cdc_acm_class_driver
};
