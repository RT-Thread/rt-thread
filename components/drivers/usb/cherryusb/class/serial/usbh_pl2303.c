/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 * Copyright (c) 2024, Derek Konigsberg
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"
#include "usbh_pl2303.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_pl2303"
#include "usb_log.h"

#define UART_STATE_INDEX          8
#define UART_STATE_MSR_MASK       0x8b
#define UART_STATE_TRANSIENT_MASK 0x74
#define UART_DCD                  0x01
#define UART_DSR                  0x02
#define UART_BREAK_ERROR          0x04
#define UART_RING                 0x08
#define UART_FRAME_ERROR          0x10
#define UART_PARITY_ERROR         0x20
#define UART_OVERRUN_ERROR        0x40
#define UART_CTS                  0x80

struct pl2303_type_data {
    const char *name;
    uint32_t max_baud_rate;
    unsigned long quirks;
    unsigned int no_autoxonxoff : 1;
    unsigned int no_divisors    : 1;
    unsigned int alt_divisors   : 1;
};

enum pl2303_type {
    TYPE_H,
    TYPE_HX,
    TYPE_TA,
    TYPE_TB,
    TYPE_HXD,
    TYPE_HXN,
    TYPE_COUNT
};

struct usbh_pl2303 {
    enum pl2303_type chip_type;
    uint32_t quirks;
    struct usb_endpoint_descriptor *intin;
    struct usbh_urb intin_urb;
    struct usb_osal_timer *modem_timer;
    uint16_t modem_status;
};

static const struct pl2303_type_data pl2303_type_data[TYPE_COUNT] = {
    [TYPE_H] = {
        .name = "PL2303H",
        .max_baud_rate = 1228800,
        .quirks = PL2303_QUIRK_LEGACY,
        .no_autoxonxoff = true,
    },
    [TYPE_HX] = {
        .name = "PL2303HX",
        .max_baud_rate = 6000000,
    },
    [TYPE_TA] = {
        .name = "PL2303TA",
        .max_baud_rate = 6000000,
        .alt_divisors = true,
    },
    [TYPE_TB] = {
        .name = "PL2303TB",
        .max_baud_rate = 12000000,
        .alt_divisors = true,
    },
    [TYPE_HXD] = {
        .name = "PL2303HXD",
        .max_baud_rate = 12000000,
    },
    [TYPE_HXN] = {
        .name = "PL2303G",
        .max_baud_rate = 12000000,
        .no_divisors = true,
    },
};

/*
 * Returns the nearest supported baud rate that can be set directly without
 * using divisors.
 */
static uint32_t pl2303_get_supported_baud_rate(uint32_t baud)
{
    static const uint32_t baud_sup[] = {
        75, 150, 300, 600, 1200, 1800, 2400, 3600, 4800, 7200, 9600,
        14400, 19200, 28800, 38400, 57600, 115200, 230400, 460800,
        614400, 921600, 1228800, 2457600, 3000000, 6000000
    };

    unsigned i;

    for (i = 0; i < ARRAY_SIZE(baud_sup); ++i) {
        if (baud_sup[i] > baud)
            break;
    }

    if (i == ARRAY_SIZE(baud_sup))
        baud = baud_sup[i - 1];
    else if (i > 0 && (baud_sup[i] - baud) > (baud - baud_sup[i - 1]))
        baud = baud_sup[i - 1];
    else
        baud = baud_sup[i];

    return baud;
}

/*
 * NOTE: If unsupported baud rates are set directly, the PL2303 seems to
 *       use 9600 baud.
 */
static uint32_t pl2303_encode_baud_rate_direct(unsigned char buf[4],
                                               uint32_t baud)
{
    memcpy(buf, &baud, 4);

    return baud;
}

static uint32_t pl2303_encode_baud_rate_divisor_alt(unsigned char buf[4],
                                                    uint32_t baud)
{
    unsigned int baseline, mantissa, exponent;

    /*
     * Apparently, for the TA version the formula is:
     *   baudrate = 12M * 32 / (mantissa * 2^exponent)
     * where
     *   mantissa = buf[10:0]
     *   exponent = buf[15:13 16]
     */
    baseline = 12000000 * 32;
    mantissa = baseline / baud;
    if (mantissa == 0)
        mantissa = 1; /* Avoid dividing by zero if baud > 32*12M. */
    exponent = 0;
    while (mantissa >= 2048) {
        if (exponent < 15) {
            mantissa >>= 1; /* divide by 2 */
            exponent++;
        } else {
            /* Exponent is maxed. Trim mantissa and leave. */
            mantissa = 2047;
            break;
        }
    }

    buf[3] = 0x80;
    buf[2] = exponent & 0x01;
    buf[1] = (exponent & ~0x01) << 4 | mantissa >> 8;
    buf[0] = mantissa & 0xff;

    /* Calculate and return the exact baud rate. */
    baud = (baseline / mantissa) >> exponent;

    return baud;
}

static uint32_t pl2303_encode_baud_rate_divisor(unsigned char buf[4],
                                                uint32_t baud)
{
    unsigned int baseline, mantissa, exponent;

    /*
    * Apparently the formula is:
    *   baudrate = 12M * 32 / (mantissa * 4^exponent)
    * where
    *   mantissa = buf[8:0]
    *   exponent = buf[11:9]
    */
    baseline = 12000000 * 32;
    mantissa = baseline / baud;
    if (mantissa == 0)
        mantissa = 1; /* Avoid dividing by zero if baud > 32*12M. */
    exponent = 0;
    while (mantissa >= 512) {
        if (exponent < 7) {
            mantissa >>= 2; /* divide by 4 */
            exponent++;
        } else {
            /* Exponent is maxed. Trim mantissa and leave. */
            mantissa = 511;
            break;
        }
    }

    buf[3] = 0x80;
    buf[2] = 0;
    buf[1] = exponent << 1 | mantissa >> 8;
    buf[0] = mantissa & 0xff;

    /* Calculate and return the exact baud rate. */
    baud = (baseline / mantissa) >> (exponent << 1);

    return baud;
}

static int pl2303_vendor_write(struct usbh_serial *serial, uint16_t wValue, uint16_t wIndex)
{
    struct usb_setup_packet *setup;
    struct usbh_pl2303 *pl2303_class;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;
    pl2303_class = (struct usbh_pl2303 *)serial->priv;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = pl2303_class->chip_type == TYPE_HXN ? PL2303_VENDOR_WRITE_NREQUEST : PL2303_VENDOR_WRITE_REQUEST;
    setup->wValue = wValue;
    setup->wIndex = wIndex;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int pl2303_vendor_read(struct usbh_serial *serial, uint16_t wValue, uint8_t *data)
{
    struct usb_setup_packet *setup;
    struct usbh_pl2303 *pl2303_class;
    int ret;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;
    pl2303_class = (struct usbh_pl2303 *)serial->priv;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = pl2303_class->chip_type == TYPE_HXN ? PL2303_VENDOR_READ_NREQUEST : PL2303_VENDOR_READ_REQUEST;
    setup->wValue = wValue;
    setup->wIndex = 0;
    setup->wLength = 1;

    ret = usbh_control_transfer(serial->hport, setup, serial->iobuffer);
    if (ret < 0) {
        return ret;
    }
    memcpy(data, serial->iobuffer, 1);

    return ret;
}

static bool pl2303_supports_hx_status(struct usbh_serial *serial)
{
    int ret;
    uint8_t buf;

    ret = pl2303_vendor_read(serial, PL2303_READ_TYPE_HX_STATUS, &buf);
    if (ret < 0) {
        return false;
    }

    return true;
}

static bool pl2303_is_hxd_clone(struct usbh_serial *serial)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = CDC_REQUEST_GET_LINE_CODING;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 7;

    ret = usbh_control_transfer(serial->hport, setup, serial->iobuffer);
    if (ret < 0) {
        return false;
    }
    return true;
}

static int pl2303_update_reg(struct usbh_serial *serial, uint8_t reg, uint8_t mask, uint8_t val)
{
    int ret;
    uint8_t buf[1];
    struct usbh_pl2303 *pl2303_class;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    pl2303_class = (struct usbh_pl2303 *)serial->priv;

    if (pl2303_class->chip_type == TYPE_HXN)
        ret = pl2303_vendor_read(serial, reg, buf);
    else
        ret = pl2303_vendor_read(serial, reg | 0x80, buf);

    if (ret < 0) {
        return ret;
    }

    *buf &= ~mask;
    *buf |= val & mask;

    return pl2303_vendor_write(serial, reg, *buf);
}

static int usbh_pl2303_get_chiptype(struct usbh_serial *serial)
{
    if (serial->hport->device_desc.bDeviceClass == 0x02) {
        return TYPE_H; /* variant 0 */
    }

    if (serial->hport->device_desc.bMaxPacketSize0 != 0x40) {
        if (serial->hport->device_desc.bDeviceClass == 0x00 || serial->hport->device_desc.bDeviceClass == 0xff)
            return TYPE_H; /* variant 1 */

        return TYPE_H; /* variant 0 */
    }

    switch (serial->hport->device_desc.bcdUSB) {
        case 0x101:
            /* USB 1.0.1? Let's assume they meant 1.1... */
        case 0x110:
            switch (serial->hport->device_desc.bcdDevice) {
                case 0x300:
                    return TYPE_HX;
                case 0x400:
                    return TYPE_HXD;
                default:
                    return TYPE_HX;
            }
            break;
        case 0x200:
            switch (serial->hport->device_desc.bcdDevice) {
                case 0x100: /* GC */
                case 0x105:
                    return TYPE_HXN;
                case 0x300: /* GT / TA */
                    if (pl2303_supports_hx_status(serial))
                        return TYPE_TA;
                    __attribute__((fallthrough));
                case 0x305:
                case 0x400: /* GL */
                case 0x405:
                    return TYPE_HXN;
                case 0x500: /* GE / TB */
                    if (pl2303_supports_hx_status(serial))
                        return TYPE_TB;
                    __attribute__((fallthrough));
                case 0x505:
                case 0x600: /* GS */
                case 0x605:
                case 0x700: /* GR */
                case 0x705:
                case 0x905:  /* GT-2AB */
                case 0x1005: /* GC-Q20 */
                    return TYPE_HXN;
            }
            break;
    }

    USB_LOG_ERR("Unsupported PL2303 Device\r\n");
    return -USB_ERR_NOTSUPP;
}

static int usbh_pl2303_attach(struct usbh_serial *serial)
{
    struct usbh_pl2303 *pl2303_class;
    struct usb_endpoint_descriptor *ep_desc;
    uint8_t type;
    int ret;

    ret = usbh_pl2303_get_chiptype(serial);
    if (ret < 0) {
        return ret;
    }

    pl2303_class = usb_osal_malloc(sizeof(struct usbh_pl2303));
    if (pl2303_class == NULL) {
        USB_LOG_ERR("Fail to alloc pl2303_class\r\n");
        return -USB_ERR_NOMEM;
    }
    memset(pl2303_class, 0, sizeof(struct usbh_pl2303));
    serial->priv = pl2303_class;

    for (uint8_t i = 0; i < serial->hport->config.intf[serial->intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &serial->hport->config.intf[serial->intf].altsetting[0].ep[i].ep_desc;

        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(pl2303_class->intin, ep_desc);
                break;
            } else {
            }
        }
    }

    if (!pl2303_class->intin) {
        USB_LOG_ERR("Failed to find interrupt endpoint\r\n");
        ret = -USB_ERR_NODEV;
        goto errout;
    }

    type = (uint8_t)ret;
    pl2303_class->chip_type = type;
    pl2303_class->quirks = pl2303_type_data[pl2303_class->chip_type].quirks;

    USB_LOG_INFO("chip type: %s\r\n", pl2303_type_data[pl2303_class->chip_type].name);

    if (type == TYPE_HXD && pl2303_is_hxd_clone(serial)) {
        pl2303_class->quirks |= PL2303_QUIRK_NO_BREAK_GETLINE;
    }

    if (type != TYPE_HXN) {
        uint8_t buf[1];
        ret = pl2303_vendor_read(serial, 0x8484, buf);
        ret |= pl2303_vendor_write(serial, 0x0404, 0);
        ret |= pl2303_vendor_read(serial, 0x8484, buf);
        ret |= pl2303_vendor_read(serial, 0x8383, buf);
        ret |= pl2303_vendor_read(serial, 0x8484, buf);
        ret |= pl2303_vendor_write(serial, 0x0404, 1);
        ret |= pl2303_vendor_read(serial, 0x8484, buf);
        ret |= pl2303_vendor_read(serial, 0x8383, buf);
        ret |= pl2303_vendor_write(serial, 0, 1);
        ret |= pl2303_vendor_write(serial, 1, 0);
        if (pl2303_class->quirks & PL2303_QUIRK_LEGACY)
            ret |= pl2303_vendor_write(serial, 2, 0x24);
        else
            ret |= pl2303_vendor_write(serial, 2, 0x44);
    } else {
        ret = 0;
    }

    if (ret < 0) {
        USB_LOG_ERR("pl2303 init failed\r\n");
        goto errout;
    }

    return 0;
errout:
    serial->priv = NULL;
    usb_osal_free(pl2303_class);
    return ret;
}

static void usbh_pl2303_detach(struct usbh_serial *serial)
{
    struct usbh_pl2303 *pl2303_class;

    if (!serial || !serial->priv) {
        return;
    }

    pl2303_class = (struct usbh_pl2303 *)serial->priv;
    if (pl2303_class->intin) {
        usbh_kill_urb(&pl2303_class->intin_urb);
    }
    serial->priv = NULL;
    usb_osal_free(pl2303_class);
}

static int usbh_pl2303_set_flow_ctrl(struct usbh_serial *serial, bool hardctrl)
{
    struct usbh_pl2303 *pl2303_class;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    pl2303_class = (struct usbh_pl2303 *)serial->priv;

    if (hardctrl) {
        if (pl2303_class->quirks & PL2303_QUIRK_LEGACY) {
            return pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0x40);
        } else if (pl2303_class->chip_type == TYPE_HXN) {
            return pl2303_update_reg(serial, PL2303_HXN_FLOWCTRL_REG,
                                     PL2303_HXN_FLOWCTRL_MASK,
                                     PL2303_HXN_FLOWCTRL_RTS_CTS);
        } else {
            return pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0x60);
        }
    } else {
        if (pl2303_class->chip_type == TYPE_HXN) {
            return pl2303_update_reg(serial, PL2303_HXN_FLOWCTRL_REG,
                                     PL2303_HXN_FLOWCTRL_MASK,
                                     PL2303_HXN_FLOWCTRL_NONE);
        } else {
            return pl2303_update_reg(serial, 0, PL2303_FLOWCTRL_MASK, 0);
        }
    }
}

static int usbh_pl2303_set_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
{
    struct usb_setup_packet *setup;
    struct usbh_pl2303 *pl2303_class;
    uint32_t baud;
    uint32_t baud_sup;
    uint8_t buf[7];

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    setup = serial->hport->setup;
    pl2303_class = (struct usbh_pl2303 *)serial->priv;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CDC_REQUEST_SET_LINE_CODING;
    setup->wValue = 0;
    setup->wIndex = serial->intf;
    setup->wLength = 7;

    baud = line_coding->dwDTERate;
    if (pl2303_type_data[pl2303_class->chip_type].max_baud_rate) {
        baud = MIN(baud, pl2303_type_data[pl2303_class->chip_type].max_baud_rate);
    }
    /*
     * Use direct method for supported baud rates, otherwise use divisors.
     * Newer chip types do not support divisor encoding.
     */
    if (pl2303_type_data[pl2303_class->chip_type].no_divisors)
        baud_sup = baud;
    else
        baud_sup = pl2303_get_supported_baud_rate(baud);

    if (baud == baud_sup)
        baud = pl2303_encode_baud_rate_direct(buf, baud);
    else if (pl2303_type_data[pl2303_class->chip_type].alt_divisors)
        baud = pl2303_encode_baud_rate_divisor_alt(buf, baud);
    else
        baud = pl2303_encode_baud_rate_divisor(buf, baud);

    buf[4] = line_coding->bCharFormat;
    buf[5] = line_coding->bParityType;
    buf[6] = line_coding->bDataBits;

    memcpy(serial->iobuffer, buf, sizeof(struct cdc_line_coding));

    return usbh_control_transfer(serial->hport, setup, serial->iobuffer);
}

static int usbh_pl2303_get_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
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

static int usbh_pl2303_set_line_state(struct usbh_serial *serial, bool dtr, bool rts)
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

static int usbh_pl2303_get_modem_status(struct usbh_serial *serial)
{
    struct usbh_pl2303 *pl2303_class;
    uintptr_t flags;
    uint16_t status;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    flags = usb_osal_enter_critical_section();
    pl2303_class = (struct usbh_pl2303 *)serial->priv;

    status = (pl2303_class->modem_status & UART_DSR ? USBH_SERIAL_TIOCM_DSR : 0) |
             (pl2303_class->modem_status & UART_CTS ? USBH_SERIAL_TIOCM_CTS : 0) |
             (pl2303_class->modem_status & UART_RING ? USBH_SERIAL_TIOCM_RI : 0) |
             (pl2303_class->modem_status & UART_DCD ? USBH_SERIAL_TIOCM_CD : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_DTR ? USBH_SERIAL_TIOCM_DTR : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_RTS ? USBH_SERIAL_TIOCM_RTS : 0);

    usb_osal_leave_critical_section(flags);

    return status;
}

#ifdef CONFIG_USBH_SERIAL_GET_MODEM_STATUS
static int __usbh_pl2303_get_modem_status(struct usbh_serial *serial)
{
    struct usbh_pl2303 *pl2303_class;
    uint8_t status = 0;
    uint16_t difference;
    uintptr_t flags;
    int ret;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }
    pl2303_class = (struct usbh_pl2303 *)serial->priv;

    usbh_int_urb_fill(&pl2303_class->intin_urb, serial->hport, pl2303_class->intin, &serial->iobuffer[USBH_SERIAL_INT_NOCACHE_OFFSET], pl2303_class->intin->wMaxPacketSize, 0xffffffff, NULL, NULL);
    ret = usbh_submit_urb(&pl2303_class->intin_urb);
    if (ret < 0) {
        return ret;
    }

    if (ret < 1) {
        return -USB_ERR_INVAL;
    }

    flags = usb_osal_enter_critical_section();

    status = serial->iobuffer[USBH_SERIAL_INT_NOCACHE_OFFSET];
    difference = pl2303_class->modem_status ^ status;
    pl2303_class->modem_status = status;

    if (status & UART_BREAK_ERROR)
        serial->iocount.brk++;

    if (difference & UART_STATE_MSR_MASK) {
        if (difference & UART_CTS)
            serial->iocount.cts++;
        if (difference & UART_DSR)
            serial->iocount.dsr++;
        if (difference & UART_RING)
            serial->iocount.rng++;
        if (difference & UART_DCD) {
            serial->iocount.dcd++;
        }
    }

    usb_osal_leave_critical_section(flags);

    return ret;
}
#endif

static const struct usbh_serial_driver pl2303_driver = {
    .driver_name = "pl2303",

    .ignore_rx_header = 0,
    .ignore_tx_header = 0,

    .attach = usbh_pl2303_attach,
    .detach = usbh_pl2303_detach,
    .set_flow_control = usbh_pl2303_set_flow_ctrl,
    .set_line_coding = usbh_pl2303_set_line_coding,
    .get_line_coding = usbh_pl2303_get_line_coding,
    .set_line_state = usbh_pl2303_set_line_state,
    .get_modem_status = usbh_pl2303_get_modem_status,
};

static int usbh_pl2303_connect(struct usbh_hubport *hport, uint8_t intf)
{
    return usbh_serial_probe(hport, intf, &pl2303_driver) ? 0 : -USB_ERR_NOMEM;
}

static int usbh_pl2303_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usbh_serial *serial = (struct usbh_serial *)hport->config.intf[intf].priv;

    if (serial) {
        usbh_serial_remove(serial);
    }

    return 0;
}

static const uint16_t pl2303_id_table[][2] = {
    { 0x067B, 0x2303 }, // PL2303 Serial (ATEN/IOGEAR UC232A)
    { 0x067B, 0x2304 }, // PL2303HXN Serial, type TB
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
    .bInterfaceClass = 0xff,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .id_table = pl2303_id_table,
    .class_driver = &pl2303_class_driver
};