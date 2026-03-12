/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"
#include "usbh_ch34x.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_ch43x"
#include "usb_log.h"

struct usbh_ch34x {
    struct usb_endpoint_descriptor *intin;
    struct usbh_urb intin_urb;
    struct usb_osal_timer *modem_timer;
    uint16_t modem_status;
};

/* refer to https://github.com/WCHSoftGroup/ch341ser_linux/blob/main/driver/ch341.c */

static int usbh_ch34x_get_baudrate_div(uint32_t baudrate, uint8_t *factor, uint8_t *divisor)
{
    uint8_t a;
    uint8_t b;
    uint32_t c;

    switch (baudrate) {
        case 921600:
            a = 0xf3;
            b = 7;
            break;

        case 307200:
            a = 0xd9;
            b = 7;
            break;

        default:
            if (baudrate > 6000000 / 255) {
                b = 3;
                c = 6000000;
            } else if (baudrate > 750000 / 255) {
                b = 2;
                c = 750000;
            } else if (baudrate > 93750 / 255) {
                b = 1;
                c = 93750;
            } else {
                b = 0;
                c = 11719;
            }
            a = (uint8_t)(c / baudrate);
            if (a == 0 || a == 0xFF) {
                return -USB_ERR_INVAL;
            }
            if ((c / a - baudrate) > (baudrate - c / (a + 1))) {
                a++;
            }
            a = (uint8_t)(256 - a);
            break;
    }

    *factor = a;
    *divisor = b;

    return 0;
}

static int usbh_ch34x_control_out(struct usbh_serial *serial, uint8_t bRequest, uint16_t wValue, uint16_t wIndex)
{
    struct usb_setup_packet *setup;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = bRequest;
    setup->wValue = wValue;
    setup->wIndex = wIndex;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_ch34x_control_in(struct usbh_serial *serial, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint8_t *data, uint16_t size)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = bRequest;
    setup->wValue = wValue;
    setup->wIndex = wIndex;
    setup->wLength = size;

    ret = usbh_control_transfer(serial->hport, setup, serial->iobuffer);
    if (ret < 0) {
        return ret;
    }
    memcpy(data, serial->iobuffer, size);

    return ret;
}

static int usbh_ch34x_get_version(struct usbh_serial *serial)
{
    int ret;
    uint8_t buf[2];

    ret = usbh_ch34x_control_in(serial, CH34X_READ_VERSION, 0, 0, buf, 2);
    if (ret < 0) {
        return ret;
    }

    USB_LOG_INFO("chip version: 0x%02x\r\n", buf[0]);
    return ret;
}

static int usbh_ch34x_attach(struct usbh_serial *serial)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret;

    struct usbh_ch34x *ch34x_class = usb_osal_malloc(sizeof(struct usbh_ch34x));
    if (!ch34x_class) {
        USB_LOG_ERR("No memory for ch34x_class\r\n");
        return -USB_ERR_NOMEM;
    }
    memset(ch34x_class, 0, sizeof(struct usbh_ch34x));
    serial->priv = ch34x_class;

    for (uint8_t i = 0; i < serial->hport->config.intf[serial->intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &serial->hport->config.intf[serial->intf].altsetting[0].ep[i].ep_desc;

        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(ch34x_class->intin, ep_desc);
                break;
            } else {
            }
        }
    }

    if (!ch34x_class->intin) {
        USB_LOG_ERR("Failed to find interrupt endpoint\r\n");
        ret = -USB_ERR_NODEV;
        goto errout;
    }

    ret = usbh_ch34x_get_version(serial);
    ret |= usbh_ch34x_control_out(serial, CH34X_SERIAL_INIT, 0, 0);
    ret |= usbh_ch34x_control_out(serial, CH34X_WRITE_REG, 0x1312, 0xd982);
    ret |= usbh_ch34x_control_out(serial, CH34X_WRITE_REG, 0x0f2c, 0x0007);
    if (ret < 0) {
        goto errout;
    }

    return 0;
errout:
    serial->priv = NULL;
    usb_osal_free(ch34x_class);
    return ret;
}

static void usbh_ch34x_detach(struct usbh_serial *serial)
{
    struct usbh_ch34x *ch34x_class;

    if (!serial || !serial->priv) {
        return;
    }

    ch34x_class = (struct usbh_ch34x *)serial->priv;
    if (ch34x_class->intin) {
        usbh_kill_urb(&ch34x_class->intin_urb);
    }
    serial->priv = NULL;
    usb_osal_free(ch34x_class);
}

static int usbh_ch34x_set_flow_ctrl(struct usbh_serial *serial, bool hardctrl)
{
    return usbh_ch34x_control_out(serial, CH34X_WRITE_REG, 0x2727, hardctrl ? 0x0101 : 0x0000);
}

static int usbh_ch34x_set_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
{
    uint16_t reg_value = 0;
    uint16_t value = 0;
    uint16_t index = 0;
    uint8_t factor = 0;
    uint8_t divisor = 0;

    switch (line_coding->bParityType) {
        case 0:
            break;
        case 1:
            reg_value |= CH341_L_PO;
            break;
        case 2:
            reg_value |= CH341_L_PE;
            break;
        case 3:
            reg_value |= CH341_L_PM;
            break;
        case 4:
            reg_value |= CH341_L_PS;
            break;
        default:
            return -USB_ERR_INVAL;
    }

    switch (line_coding->bDataBits) {
        case 5:
            reg_value |= CH341_L_D5;
            break;
        case 6:
            reg_value |= CH341_L_D6;
            break;
        case 7:
            reg_value |= CH341_L_D7;
            break;
        case 8:
            reg_value |= CH341_L_D8;
            break;
        default:
            return -USB_ERR_INVAL;
    }

    if (line_coding->bCharFormat == 2) {
        reg_value |= CH341_L_SB;
    }

    usbh_ch34x_get_baudrate_div(line_coding->dwDTERate, &factor, &divisor);

    reg_value |= 0xC0;
    value |= 0x9c;
    value |= reg_value << 8;
    index |= 0x80 | divisor;
    index |= (uint16_t)factor << 8;

    return usbh_ch34x_control_out(serial, CH34X_SERIAL_INIT, value, index);
}

static int usbh_ch34x_set_line_state(struct usbh_serial *serial, bool dtr, bool rts)
{
    uint16_t value = 0;
    uint8_t control = 0;

    control = (dtr << 5) | (rts << 6);
    value = (uint8_t)~control;

    return usbh_ch34x_control_out(serial, CH34X_MODEM_CTRL, value, 0x0000);
}

static int usbh_ch34x_get_modem_status(struct usbh_serial *serial)
{
    struct usbh_ch34x *ch34x_class;
    uintptr_t flags;
    uint16_t status;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    flags = usb_osal_enter_critical_section();

    ch34x_class = (struct usbh_ch34x *)serial->priv;

    status = (ch34x_class->modem_status & CH341_CTI_DS ? USBH_SERIAL_TIOCM_DSR : 0) |
             (ch34x_class->modem_status & CH341_CTI_C ? USBH_SERIAL_TIOCM_CTS : 0) |
             (ch34x_class->modem_status & CH341_CTRL_RI ? USBH_SERIAL_TIOCM_RI : 0) |
             (ch34x_class->modem_status & CH341_CTI_DC ? USBH_SERIAL_TIOCM_CD : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_DTR ? USBH_SERIAL_TIOCM_DTR : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_RTS ? USBH_SERIAL_TIOCM_RTS : 0);

    usb_osal_leave_critical_section(flags);

    return status;
}

#ifdef CONFIG_USBH_SERIAL_GET_MODEM_STATUS
static int __usbh_ch34x_get_modem_status(struct usbh_serial *serial, uint16_t *status)
{
    struct usbh_ch34x *ch34x_class;
    uint8_t type = 0;
    uint8_t data = 0;
    uint16_t difference;
    uintptr_t flags;
    int ret;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }
    ch34x_class = (struct usbh_ch34x *)serial->priv;

    usbh_int_urb_fill(&ch34x_class->intin_urb, serial->hport, ch34x_class->intin, &serial->iobuffer[USBH_SERIAL_INT_NOCACHE_OFFSET], ch34x_class->intin->wMaxPacketSize, 0xffffffff, NULL, NULL);
    ret = usbh_submit_urb(&ch34x_class->intin_urb);
    if (ret < 0) {
        return ret;
    }

    if (ret < 4) {
        return -USB_ERR_INVAL;
    }

    flags = usb_osal_enter_critical_section();

    type = serial->iobuffer[USBH_SERIAL_INT_NOCACHE_OFFSET];
    if (type & CH341_CTT_M) {
        data = ~serial->iobuffer[USBH_SERIAL_INT_NOCACHE_OFFSET + 2] & CH341_CTI_ST;
        difference = data ^ (ch34x_class->modem_status & CH341_CTI_ST);
        ch34x_class->modem_status = data;

        if (difference) {
            if (difference & CH341_CTI_C) {
                serial->iocount.cts++;
            }
            if (difference & CH341_CTI_DS) {
                serial->iocount.dsr++;
            }
            if (difference & CH341_CTRL_RI) {
                serial->iocount.rng++;
            }
            if (difference & CH341_CTI_DC) {
                serial->iocount.dcd++;
            }
        }
    }

    if (type & CH341_CTT_O) {
        serial->iocount.overrun++;
    }
    if ((type & CH341_CTT_F) == CH341_CTT_F) {
        serial->iocount.frame++;
    }
    if (type & CH341_CTT_P) {
        serial->iocount.parity++;
    }

    usb_osal_leave_critical_section(flags);

    return ret;
}
#endif

static const struct usbh_serial_driver ch34x_driver = {
    .driver_name = "ch34x",

    .ignore_rx_header = 0,
    .ignore_tx_header = 0,

    .attach = usbh_ch34x_attach,
    .detach = usbh_ch34x_detach,
    .set_flow_control = usbh_ch34x_set_flow_ctrl,
    .set_line_coding = usbh_ch34x_set_line_coding,
    .get_line_coding = NULL,
    .set_line_state = usbh_ch34x_set_line_state,
    .get_modem_status = usbh_ch34x_get_modem_status,
};

static int usbh_ch34x_connect(struct usbh_hubport *hport, uint8_t intf)
{
    return usbh_serial_probe(hport, intf, &ch34x_driver) ? 0 : -USB_ERR_NOMEM;
}

static int usbh_ch34x_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usbh_serial *serial = (struct usbh_serial *)hport->config.intf[intf].priv;

    if (serial) {
        usbh_serial_remove(serial);
    }

    return 0;
}

static const uint16_t ch34x_id_table[][2] = {
    { 0x1A86, 0x7523 }, /* ch340 chip */
    { 0x1A86, 0x7522 }, /* ch340k chip */
    { 0x1A86, 0x5523 }, /* ch341 chip */
    { 0x1A86, 0xe523 }, /* ch330 chip */
    { 0x4348, 0x5523 }, /* ch340 custom chip */
    { 0, 0 },
};

const struct usbh_class_driver ch34x_class_driver = {
    .driver_name = "ch34x",
    .connect = usbh_ch34x_connect,
    .disconnect = usbh_ch34x_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info ch34x_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .bInterfaceClass = 0xff,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .id_table = ch34x_id_table,
    .class_driver = &ch34x_class_driver
};