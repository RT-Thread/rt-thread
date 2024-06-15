/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_cp210x.h"

#define DEV_FORMAT "/dev/ttyUSB%d"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_cp210x_buf[64];

#define CONFIG_USBHOST_MAX_CP210X_CLASS 4

static struct usbh_cp210x g_cp210x_class[CONFIG_USBHOST_MAX_CP210X_CLASS];
static uint32_t g_devinuse = 0;

static struct usbh_cp210x *usbh_cp210x_class_alloc(void)
{
    int devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_CP210X_CLASS; devno++) {
        if ((g_devinuse & (1 << devno)) == 0) {
            g_devinuse |= (1 << devno);
            memset(&g_cp210x_class[devno], 0, sizeof(struct usbh_cp210x));
            g_cp210x_class[devno].minor = devno;
            return &g_cp210x_class[devno];
        }
    }
    return NULL;
}

static void usbh_cp210x_class_free(struct usbh_cp210x *cp210x_class)
{
    int devno = cp210x_class->minor;

    if (devno >= 0 && devno < 32) {
        g_devinuse &= ~(1 << devno);
    }
    memset(cp210x_class, 0, sizeof(struct usbh_cp210x));
}

static int usbh_cp210x_enable(struct usbh_cp210x *cp210x_class)
{
    struct usb_setup_packet *setup = cp210x_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_IFC_ENABLE;
    setup->wValue = 1;
    setup->wIndex = cp210x_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(cp210x_class->hport, setup, NULL);
}

static int usbh_cp210x_set_flow(struct usbh_cp210x *cp210x_class)
{
    struct usb_setup_packet *setup = cp210x_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_SET_FLOW;
    setup->wValue = 0;
    setup->wIndex = cp210x_class->intf;
    setup->wLength = 16;

    memset(g_cp210x_buf, 0, 16);
    g_cp210x_buf[13] = 0x20;
    return usbh_control_transfer(cp210x_class->hport, setup, g_cp210x_buf);
}

static int usbh_cp210x_set_chars(struct usbh_cp210x *cp210x_class)
{
    struct usb_setup_packet *setup = cp210x_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_SET_CHARS;
    setup->wValue = 0;
    setup->wIndex = cp210x_class->intf;
    setup->wLength = 6;

    memset(g_cp210x_buf, 0, 6);
    g_cp210x_buf[0] = 0x80;
    g_cp210x_buf[4] = 0x88;
    g_cp210x_buf[5] = 0x28;
    return usbh_control_transfer(cp210x_class->hport, setup, g_cp210x_buf);
}

static int usbh_cp210x_set_baudrate(struct usbh_cp210x *cp210x_class, uint32_t baudrate)
{
    struct usb_setup_packet *setup = cp210x_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_SET_BAUDRATE;
    setup->wValue = 0;
    setup->wIndex = cp210x_class->intf;
    setup->wLength = 4;

    memcpy(g_cp210x_buf, (uint8_t *)&baudrate, 4);
    return usbh_control_transfer(cp210x_class->hport, setup, g_cp210x_buf);
}

static int usbh_cp210x_set_data_format(struct usbh_cp210x *cp210x_class, uint8_t databits, uint8_t parity, uint8_t stopbits)
{
    struct usb_setup_packet *setup = cp210x_class->hport->setup;
    uint16_t value;

    value = ((databits & 0x0F) << 8) | ((parity & 0x0f) << 4) | ((stopbits & 0x03) << 0);

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_SET_LINE_CTL;
    setup->wValue = value;
    setup->wIndex = cp210x_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(cp210x_class->hport, setup, NULL);
}

static int usbh_cp210x_set_mhs(struct usbh_cp210x *cp210x_class, uint8_t dtr, uint8_t rts, uint8_t dtr_mask, uint8_t rts_mask)
{
    struct usb_setup_packet *setup = cp210x_class->hport->setup;
    uint16_t value;

    value = ((dtr & 0x01) << 0) | ((rts & 0x01) << 1) | ((dtr_mask & 0x01) << 8) | ((rts_mask & 0x01) << 9);

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_SET_MHS;
    setup->wValue = value;
    setup->wIndex = cp210x_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(cp210x_class->hport, setup, NULL);
}

int usbh_cp210x_set_line_coding(struct usbh_cp210x *cp210x_class, struct cdc_line_coding *line_coding)
{
    memcpy((uint8_t *)&cp210x_class->line_coding, line_coding, sizeof(struct cdc_line_coding));
    usbh_cp210x_set_baudrate(cp210x_class, line_coding->dwDTERate);
    return usbh_cp210x_set_data_format(cp210x_class, line_coding->bDataBits, line_coding->bParityType, line_coding->bCharFormat);
}

int usbh_cp210x_get_line_coding(struct usbh_cp210x *cp210x_class, struct cdc_line_coding *line_coding)
{
    memcpy(line_coding, (uint8_t *)&cp210x_class->line_coding, sizeof(struct cdc_line_coding));
    return 0;
}

int usbh_cp210x_set_line_state(struct usbh_cp210x *cp210x_class, bool dtr, bool rts)
{
    return usbh_cp210x_set_mhs(cp210x_class, dtr, rts, 1, 1);
}

static int usbh_cp210x_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret = 0;

    struct usbh_cp210x *cp210x_class = usbh_cp210x_class_alloc();
    if (cp210x_class == NULL) {
        USB_LOG_ERR("Fail to alloc cp210x_class\r\n");
        return -USB_ERR_NOMEM;
    }

    cp210x_class->hport = hport;
    cp210x_class->intf = intf;

    hport->config.intf[intf].priv = cp210x_class;

    usbh_cp210x_enable(cp210x_class);
    usbh_cp210x_set_flow(cp210x_class);
    usbh_cp210x_set_chars(cp210x_class);

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;

        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(cp210x_class->bulkin, ep_desc);
        } else {
            USBH_EP_INIT(cp210x_class->bulkout, ep_desc);
        }
    }

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, cp210x_class->minor);

    USB_LOG_INFO("Register CP210X Class:%s\r\n", hport->config.intf[intf].devname);

#if 0
    USB_LOG_INFO("Test cp2102 rx and tx and rx for 5 times, baudrate is 115200\r\n");

    struct cdc_line_coding linecoding;
    uint8_t count = 5;

    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_cp210x_set_line_coding(cp210x_class, &linecoding);
    usbh_cp210x_set_line_state(cp210x_class, true, false);

    memset(g_cp210x_buf, 'a', sizeof(g_cp210x_buf));
    ret = usbh_cp210x_bulk_out_transfer(cp210x_class, g_cp210x_buf, sizeof(g_cp210x_buf), 0xfffffff);
    USB_LOG_RAW("out ret:%d\r\n", ret);
    while (count--) {
        ret = usbh_cp210x_bulk_in_transfer(cp210x_class, g_cp210x_buf, sizeof(g_cp210x_buf), 0xfffffff);
        USB_LOG_RAW("in ret:%d\r\n", ret);
        if (ret > 0) {
            for (uint32_t i = 0; i < ret; i++) {
                USB_LOG_RAW("%02x ", g_cp210x_buf[i]);
            }
            USB_LOG_RAW("\r\n");
        }
    }
#endif
    usbh_cp210x_run(cp210x_class);
    return ret;
}

static int usbh_cp210x_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_cp210x *cp210x_class = (struct usbh_cp210x *)hport->config.intf[intf].priv;

    if (cp210x_class) {
        if (cp210x_class->bulkin) {
            usbh_kill_urb(&cp210x_class->bulkin_urb);
        }

        if (cp210x_class->bulkout) {
            usbh_kill_urb(&cp210x_class->bulkout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister CP210X Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_cp210x_stop(cp210x_class);
        }

        usbh_cp210x_class_free(cp210x_class);
    }

    return ret;
}

int usbh_cp210x_bulk_in_transfer(struct usbh_cp210x *cp210x_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &cp210x_class->bulkin_urb;

    usbh_bulk_urb_fill(urb, cp210x_class->hport, cp210x_class->bulkin, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

int usbh_cp210x_bulk_out_transfer(struct usbh_cp210x *cp210x_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &cp210x_class->bulkout_urb;

    usbh_bulk_urb_fill(urb, cp210x_class->hport, cp210x_class->bulkout, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

__WEAK void usbh_cp210x_run(struct usbh_cp210x *cp210x_class)
{
}

__WEAK void usbh_cp210x_stop(struct usbh_cp210x *cp210x_class)
{
}

static const uint16_t cp210x_id_table[][2] = {
    { 0x10C4, 0xEA60 },
    { 0, 0 },
};

const struct usbh_class_driver cp210x_class_driver = {
    .driver_name = "cp210x",
    .connect = usbh_cp210x_connect,
    .disconnect = usbh_cp210x_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info cp210x_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .class = 0xff,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = cp210x_id_table,
    .class_driver = &cp210x_class_driver
};