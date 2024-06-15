/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_ch34x.h"

#define DEV_FORMAT "/dev/ttyUSB%d"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_ch34x_buf[64];

#define CONFIG_USBHOST_MAX_CP210X_CLASS 1

static struct usbh_ch34x g_ch34x_class[CONFIG_USBHOST_MAX_CP210X_CLASS];
static uint32_t g_devinuse = 0;

static struct usbh_ch34x *usbh_ch34x_class_alloc(void)
{
    int devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_CP210X_CLASS; devno++) {
        if ((g_devinuse & (1 << devno)) == 0) {
            g_devinuse |= (1 << devno);
            memset(&g_ch34x_class[devno], 0, sizeof(struct usbh_ch34x));
            g_ch34x_class[devno].minor = devno;
            return &g_ch34x_class[devno];
        }
    }
    return NULL;
}

static void usbh_ch34x_class_free(struct usbh_ch34x *ch34x_class)
{
    int devno = ch34x_class->minor;

    if (devno >= 0 && devno < 32) {
        g_devinuse &= ~(1 << devno);
    }
    memset(ch34x_class, 0, sizeof(struct usbh_ch34x));
}

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

static int usbh_ch34x_get_version(struct usbh_ch34x *ch34x_class)
{
    struct usb_setup_packet *setup = ch34x_class->hport->setup;
    int ret;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = CH34X_READ_VERSION;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 2;

    ret = usbh_control_transfer(ch34x_class->hport, setup, g_ch34x_buf);
    if (ret < 0) {
        return ret;
    }

    USB_LOG_INFO("Ch34x chip version %02x:%02x\r\n", g_ch34x_buf[0], g_ch34x_buf[1]);
    return ret;
}

static int usbh_ch34x_flow_ctrl(struct usbh_ch34x *ch34x_class)
{
    struct usb_setup_packet *setup = ch34x_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = CH34X_WRITE_REG;
    setup->wValue = 0x2727;
    setup->wIndex = 0;
    setup->wLength = 0;

    return usbh_control_transfer(ch34x_class->hport, setup, NULL);
}

int usbh_ch34x_set_line_coding(struct usbh_ch34x *ch34x_class, struct cdc_line_coding *line_coding)
{
    struct usb_setup_packet *setup = ch34x_class->hport->setup;
    uint16_t reg_value = 0;
    uint16_t value = 0;
    uint8_t factor = 0;
    uint8_t divisor = 0;

    memcpy((uint8_t *)&ch34x_class->line_coding, line_coding, sizeof(struct cdc_line_coding));

    /* refer to https://github.com/WCHSoftGroup/ch341ser_linux/blob/main/driver/ch341.c */

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

    reg_value |= 0xC0;

    value |= 0x9c;
    value |= reg_value << 8;

    usbh_ch34x_get_baudrate_div(line_coding->dwDTERate, &factor, &divisor);

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = CH34X_SERIAL_INIT;
    setup->wValue = value;
    setup->wIndex = (factor << 8) | 0x80 | divisor;
    setup->wLength = 0;

    return usbh_control_transfer(ch34x_class->hport, setup, NULL);
}

int usbh_ch34x_get_line_coding(struct usbh_ch34x *ch34x_class, struct cdc_line_coding *line_coding)
{
    memcpy(line_coding, (uint8_t *)&ch34x_class->line_coding, sizeof(struct cdc_line_coding));
    return 0;
}

int usbh_ch34x_set_line_state(struct usbh_ch34x *ch34x_class, bool dtr, bool rts)
{
    struct usb_setup_packet *setup = ch34x_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = CH34X_MODEM_CTRL;
    setup->wValue = 0x0f | (dtr << 5) | (rts << 6);
    setup->wIndex = 0;
    setup->wLength = 0;

    return usbh_control_transfer(ch34x_class->hport, setup, NULL);
}

static int usbh_ch34x_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret = 0;

    struct usbh_ch34x *ch34x_class = usbh_ch34x_class_alloc();
    if (ch34x_class == NULL) {
        USB_LOG_ERR("Fail to alloc ch34x_class\r\n");
        return -USB_ERR_NOMEM;
    }

    ch34x_class->hport = hport;
    ch34x_class->intf = intf;

    hport->config.intf[intf].priv = ch34x_class;

    usbh_ch34x_get_version(ch34x_class);
    usbh_ch34x_flow_ctrl(ch34x_class);

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;
        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            continue;
        } else {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(ch34x_class->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(ch34x_class->bulkout, ep_desc);
            }
        }
    }

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, ch34x_class->minor);

    USB_LOG_INFO("Register CH34X Class:%s\r\n", hport->config.intf[intf].devname);

#if 0
    USB_LOG_INFO("Test ch34x rx and tx and rx for 5 times, baudrate is 115200\r\n");

    struct cdc_line_coding linecoding;
    uint8_t count = 5;

    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_ch34x_set_line_coding(ch34x_class, &linecoding);
    usbh_ch34x_set_line_state(ch34x_class, true, false);

    memset(g_ch34x_buf, 'a', sizeof(g_ch34x_buf));
    ret = usbh_ch34x_bulk_out_transfer(ch34x_class, g_ch34x_buf, sizeof(g_ch34x_buf), 0xfffffff);
    USB_LOG_RAW("out ret:%d\r\n", ret);
    while (count--) {
        ret = usbh_ch34x_bulk_in_transfer(ch34x_class, g_ch34x_buf, sizeof(g_ch34x_buf), 0xfffffff);
        USB_LOG_RAW("in ret:%d\r\n", ret);
        if (ret > 0) {
            for (uint32_t i = 0; i < ret; i++) {
                USB_LOG_RAW("%02x ", g_ch34x_buf[i]);
            }
            USB_LOG_RAW("\r\n");
        }
    }
#endif
    usbh_ch34x_run(ch34x_class);
    return ret;
}

static int usbh_ch34x_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_ch34x *ch34x_class = (struct usbh_ch34x *)hport->config.intf[intf].priv;

    if (ch34x_class) {
        if (ch34x_class->bulkin) {
            usbh_kill_urb(&ch34x_class->bulkin_urb);
        }

        if (ch34x_class->bulkout) {
            usbh_kill_urb(&ch34x_class->bulkout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister CH34X Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_ch34x_stop(ch34x_class);
        }

        usbh_ch34x_class_free(ch34x_class);
    }

    return ret;
}

int usbh_ch34x_bulk_in_transfer(struct usbh_ch34x *ch34x_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &ch34x_class->bulkin_urb;

    usbh_bulk_urb_fill(urb, ch34x_class->hport, ch34x_class->bulkin, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

int usbh_ch34x_bulk_out_transfer(struct usbh_ch34x *ch34x_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &ch34x_class->bulkout_urb;

    usbh_bulk_urb_fill(urb, ch34x_class->hport, ch34x_class->bulkout, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

__WEAK void usbh_ch34x_run(struct usbh_ch34x *ch34x_class)
{
}

__WEAK void usbh_ch34x_stop(struct usbh_ch34x *ch34x_class)
{
}

static const uint16_t ch34x_id_table[][2] = {
    { 0x1A86, 0x7523 },
    { 0, 0 },
};

const struct usbh_class_driver ch34x_class_driver = {
    .driver_name = "ch34x",
    .connect = usbh_ch34x_connect,
    .disconnect = usbh_ch34x_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info ch34x_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .class = 0xff,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = ch34x_id_table,
    .class_driver = &ch34x_class_driver
};