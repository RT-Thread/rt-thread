/*
 * Copyright (c) 2024, sakumisu
 * Copyright (c) 2024, Derek Konigsberg
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_pl2303.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_pl2303"
#include "usb_log.h"

#define DEV_FORMAT "/dev/ttyUSB%d"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_pl2303_buf[64];

#define CONFIG_USBHOST_MAX_PL2303_CLASS 1

#define UT_WRITE_VENDOR_DEVICE   (USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE)
#define UT_READ_VENDOR_DEVICE    (USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE)

static struct usbh_pl2303 g_pl2303_class[CONFIG_USBHOST_MAX_PL2303_CLASS];
static uint32_t g_devinuse = 0;

static struct usbh_pl2303 *usbh_pl2303_class_alloc(void)
{
    uint8_t devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_PL2303_CLASS; devno++) {
        if ((g_devinuse & (1U << devno)) == 0) {
            g_devinuse |= (1U << devno);
            memset(&g_pl2303_class[devno], 0, sizeof(struct usbh_pl2303));
            g_pl2303_class[devno].minor = devno;
            return &g_pl2303_class[devno];
        }
    }
    return NULL;
}

static void usbh_pl2303_class_free(struct usbh_pl2303 *pl2303_class)
{
    uint8_t devno = pl2303_class->minor;

    if (devno < 32) {
        g_devinuse &= ~(1U << devno);
    }
    memset(pl2303_class, 0, sizeof(struct usbh_pl2303));
}

static int usbh_pl2303_get_chiptype(struct usbh_pl2303 *pl2303_class)
{
    int ret = 0;

    switch (pl2303_class->hport->device_desc.bcdDevice) {
        case 0x0300:
            pl2303_class->chiptype = USBH_PL2303_TYPE_PL2303HX;
            /* or TA, that is HX with external crystal */
            break;
        case 0x0400:
            pl2303_class->chiptype = USBH_PL2303_TYPE_PL2303HXD;
            /* or EA, that is HXD with ESD protection */
            /* or RA, that has internal voltage level converter that works only up to 1Mbaud (!) */
            break;
        case 0x0500:
            pl2303_class->chiptype = USBH_PL2303_TYPE_PL2303HXD;
            /* in fact it's TB, that is HXD with external crystal */
            break;
        default:
            /* NOTE: I have no info about the bcdDevice for the base PL2303 (up to 1.2Mbaud,
           only fixed rates) and for PL2303SA (8-pin chip, up to 115200 baud */
            /* Determine the chip type.  This algorithm is taken from Linux. */
            if (pl2303_class->hport->device_desc.bDeviceClass == 0x02) {
                pl2303_class->chiptype = USBH_PL2303_TYPE_PL2303;
            } else if (pl2303_class->hport->device_desc.bMaxPacketSize0 == 0x40) {
                pl2303_class->chiptype = USBH_PL2303_TYPE_PL2303HX;
            } else {
                pl2303_class->chiptype = USBH_PL2303_TYPE_PL2303;
            }
            break;
    }

    /*
     * The new chip revision PL2303HXN is only compatible with the new
     * PLCOM_SET_REQUEST_PL2303HXN command. Issuing the old command
     * PLCOM_SET_REQUEST to the new chip raises an error. Thus, PL2303HX
     * and PL2303HXN can be distinguished by issuing an old-style request
     * (on a status register) to the new chip and checking the error.
     */
    if (pl2303_class->chiptype == USBH_PL2303_TYPE_PL2303HX) {
        struct usb_setup_packet *setup = pl2303_class->hport->setup;

        setup->bmRequestType = UT_READ_VENDOR_DEVICE;
        setup->bRequest = PL2303_SET_REQUEST;
        setup->wValue = PL2303_STATUS_REG_PL2303HX;
        setup->wIndex = 0;
        setup->wLength = 1;

        ret = usbh_control_transfer(pl2303_class->hport, setup, g_pl2303_buf);
        if (ret == -USB_ERR_STALL) {
            pl2303_class->chiptype = USBH_PL2303_TYPE_PL2303HXN;
            ret = 0;
        } else if (ret < 0) {
            USB_LOG_WRN("Error checking chip type: %d\r\n", ret);
            return ret;
        }
    }

    switch (pl2303_class->chiptype) {
        case USBH_PL2303_TYPE_PL2303:
            USB_LOG_INFO("chiptype = 2303\r\n");
            break;
        case USBH_PL2303_TYPE_PL2303HX:
            USB_LOG_INFO("chiptype = 2303HX/TA\r\n");
            break;
        case USBH_PL2303_TYPE_PL2303HXN:
            USB_LOG_INFO("chiptype = 2303HXN\r\n");
            break;
        case USBH_PL2303_TYPE_PL2303HXD:
            USB_LOG_INFO("chiptype = 2303HXD/TB/RA/EA\r\n");
            break;
        default:
            USB_LOG_INFO("chiptype = [%d]\r\n", pl2303_class->chiptype);
            break;
    }

    return ret;
}

static int usbh_pl2303_do(struct usbh_pl2303 *pl2303_class,
                          uint8_t req_type, uint8_t request, uint16_t value, uint16_t index,
                          uint16_t length)
{
    struct usb_setup_packet *setup;

    if (!pl2303_class || !pl2303_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = pl2303_class->hport->setup;

    setup->bmRequestType = req_type;
    setup->bRequest = request;
    setup->wValue = value;
    setup->wIndex = index;
    setup->wLength = length;

    return usbh_control_transfer(pl2303_class->hport, setup, g_pl2303_buf);
}

int usbh_pl2303_set_line_coding(struct usbh_pl2303 *pl2303_class, struct cdc_line_coding *line_coding)
{
    struct usb_setup_packet *setup;

    if (!pl2303_class || !pl2303_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = pl2303_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SET_LINE_CODING;
    setup->wValue = 0;
    setup->wIndex = pl2303_class->intf;
    setup->wLength = 7;

    memcpy(g_pl2303_buf, line_coding, sizeof(struct cdc_line_coding));

    return usbh_control_transfer(pl2303_class->hport, setup, g_pl2303_buf);
}

int usbh_pl2303_get_line_coding(struct usbh_pl2303 *pl2303_class, struct cdc_line_coding *line_coding)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!pl2303_class || !pl2303_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = pl2303_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_GET_LINE_CODING;
    setup->wValue = 0;
    setup->wIndex = pl2303_class->intf;
    setup->wLength = 7;

    ret = usbh_control_transfer(pl2303_class->hport, setup, g_pl2303_buf);
    if (ret < 0) {
        return ret;
    }
    memcpy(line_coding, g_pl2303_buf, sizeof(struct cdc_line_coding));
    return ret;
}

int usbh_pl2303_set_line_state(struct usbh_pl2303 *pl2303_class, bool dtr, bool rts)
{
    struct usb_setup_packet *setup;

    if (!pl2303_class || !pl2303_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = pl2303_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SET_CONTROL_LINE_STATE;
    setup->wValue = (dtr << 0) | (rts << 1);
    setup->wIndex = pl2303_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(pl2303_class->hport, setup, NULL);
}

static int usbh_pl2303_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret = 0;

    struct usbh_pl2303 *pl2303_class = usbh_pl2303_class_alloc();
    if (pl2303_class == NULL) {
        USB_LOG_ERR("Fail to alloc pl2303_class\r\n");
        return -USB_ERR_NOMEM;
    }

    pl2303_class->hport = hport;
    pl2303_class->intf = intf;

    hport->config.intf[intf].priv = pl2303_class;

    do {
        ret = usbh_pl2303_get_chiptype(pl2303_class);
        if (ret < 0) {
            break;
        }

        /* Startup reset sequence, if necessary for the chip type */
        if (pl2303_class->chiptype != USBH_PL2303_TYPE_PL2303HXN) {
            struct usb_setup_packet *setup = pl2303_class->hport->setup;

            setup->bmRequestType = UT_WRITE_VENDOR_DEVICE;
            setup->bRequest = PL2303_SET_REQUEST;
            setup->wValue = 0;
            setup->wIndex = pl2303_class->intf;
            setup->wLength = 0;

            ret = usbh_control_transfer(pl2303_class->hport, setup, g_pl2303_buf);
            if (ret < 0) {
                USB_LOG_WRN("Initialization reset failed: %d\r\n", ret);
                break;
            }
        }

        if (pl2303_class->chiptype == USBH_PL2303_TYPE_PL2303) {
            /* HX variants seem to lock up after a clear stall request. */
            /*
             * The FreeBSD code sets the stall flags on the in and out pipes
             * here. Have no idea exactly how to do this, or if it is necessary.
             * May just leave this code unwritten until test hardware is available.
             */
        } else if (pl2303_class->chiptype == USBH_PL2303_TYPE_PL2303HX || pl2303_class->chiptype == USBH_PL2303_TYPE_PL2303HXD) {
            /* Reset upstream data pipes */
            ret = usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 8, 0, 0);
            if (ret < 0) {
                USB_LOG_WRN("Could not reset upstream data pipes (8,0): %d\r\n", ret);
                break;
            }
            ret = usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 9, 0, 0);
            if (ret < 0) {
                USB_LOG_WRN("Could not reset upstream data pipes (9,0): %d\r\n", ret);
                break;
            }
        } else if (pl2303_class->chiptype == USBH_PL2303_TYPE_PL2303HXN) {
            /* Reset upstream data pipes */
            ret = usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST_PL2303HXN, 0x07, 0x03, 0);
            if (ret < 0) {
                USB_LOG_WRN("Could not reset upstream data pipes (7,3): %d\r\n", ret);
                break;
            }
        }

        /* Final device initialization, if necessary for the chip type */
        if (pl2303_class->chiptype != USBH_PL2303_TYPE_PL2303HXN) {
            if (usbh_pl2303_do(pl2303_class, UT_READ_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x8484, 0, 1) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x0404, 0, 0) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_READ_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x8484, 0, 1) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_READ_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x8383, 0, 1) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_READ_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x8484, 0, 1) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x0404, 1, 0) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_READ_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x8484, 0, 1) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_READ_VENDOR_DEVICE, PL2303_SET_REQUEST, 0x8383, 0, 1) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 0, 1, 0) < 0 ||
                usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 1, 0, 0) < 0) {
                USB_LOG_WRN("Could not complete init sequence\r\n");
                ret = -USB_ERR_INVAL;
                break;
            }

            if (pl2303_class->chiptype != USBH_PL2303_TYPE_PL2303) {
                ret = usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 2, 0x44, 0);
            } else {
                ret = usbh_pl2303_do(pl2303_class, UT_WRITE_VENDOR_DEVICE, PL2303_SET_REQUEST, 2, 0x24, 0);
            }
            if (ret < 0) {
                USB_LOG_WRN("Could not complete final init request: %d\r\n", ret);
                break;
            }
        }
    } while (0);

    if (ret < 0) {
        USB_LOG_ERR("Failed to initialize PL2303 device: %d\r\n", ret);
        return ret;
    }

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;
        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            continue;
        } else {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(pl2303_class->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(pl2303_class->bulkout, ep_desc);
            }
        }
    }

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, pl2303_class->minor);

    USB_LOG_INFO("Register PL2303 Class:%s\r\n", hport->config.intf[intf].devname);

#if 0
    USB_LOG_INFO("Test pl2303 rx and tx and rx for 5 times, baudrate is 115200\r\n");

    struct cdc_line_coding linecoding;
    uint8_t count = 5;

    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_pl2303_set_line_coding(pl2303_class, &linecoding);
    usbh_pl2303_set_line_state(pl2303_class, true, false);

    memset(g_pl2303_buf, 'a', sizeof(g_pl2303_buf));
    ret = usbh_pl2303_bulk_out_transfer(pl2303_class, g_pl2303_buf, sizeof(g_pl2303_buf), 0xfffffff);
    USB_LOG_RAW("out ret:%d\r\n", ret);
    while (count--) {
        ret = usbh_pl2303_bulk_in_transfer(pl2303_class, g_pl2303_buf, sizeof(g_pl2303_buf), 0xfffffff);
        USB_LOG_RAW("in ret:%d\r\n", ret);
        if (ret > 0) {
            for (uint32_t i = 0; i < ret; i++) {
                USB_LOG_RAW("%02x ", g_pl2303_buf[i]);
            }
        }
        USB_LOG_RAW("\r\n");
    }
#endif

    usbh_pl2303_run(pl2303_class);
    return ret;
}

static int usbh_pl2303_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_pl2303 *pl2303_class = (struct usbh_pl2303 *)hport->config.intf[intf].priv;

    if (pl2303_class) {
        if (pl2303_class->bulkin) {
            usbh_kill_urb(&pl2303_class->bulkin_urb);
        }

        if (pl2303_class->bulkout) {
            usbh_kill_urb(&pl2303_class->bulkout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister PL2303 Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_pl2303_stop(pl2303_class);
        }

        usbh_pl2303_class_free(pl2303_class);
    }

    return ret;
}

int usbh_pl2303_bulk_in_transfer(struct usbh_pl2303 *pl2303_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &pl2303_class->bulkin_urb;

    usbh_bulk_urb_fill(urb, pl2303_class->hport, pl2303_class->bulkin, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

int usbh_pl2303_bulk_out_transfer(struct usbh_pl2303 *pl2303_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &pl2303_class->bulkout_urb;

    usbh_bulk_urb_fill(urb, pl2303_class->hport, pl2303_class->bulkout, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

__WEAK void usbh_pl2303_run(struct usbh_pl2303 *pl2303_class)
{
    (void)pl2303_class;
}

__WEAK void usbh_pl2303_stop(struct usbh_pl2303 *pl2303_class)
{
    (void)pl2303_class;
}

static const uint16_t pl2303_id_table[][2] = {
    { 0x067B, 0x2303 }, // PL2303 Serial (ATEN/IOGEAR UC232A)
    { 0x067B, 0x23A3 }, // PL2303HXN Serial, type GC
    { 0x067B, 0x23B3 }, // PL2303HXN Serial, type GB
    { 0x067B, 0x23C3 }, // PL2303HXN Serial, type GT
    { 0x067B, 0x23D3 }, // PL2303HXN Serial, type GL
    { 0x067B, 0x23E3 }, // PL2303HXN Serial, type GE
    { 0x067B, 0x23F3 }, // PL2303HXN Serial, type GS
    { 0, 0 },
};

const struct usbh_class_driver pl2303_class_driver = {
    .driver_name = "pl2303",
    .connect = usbh_pl2303_connect,
    .disconnect = usbh_pl2303_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info pl2303_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .class = 0xff,
    .subclass = 0x00,
    .protocol = 0x00,
    .id_table = pl2303_id_table,
    .class_driver = &pl2303_class_driver
};