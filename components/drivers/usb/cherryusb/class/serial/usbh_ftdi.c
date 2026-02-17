/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"
#include "usbh_ftdi.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_ftdi"
#include "usb_log.h"

enum ftdi_chip_type {
    SIO,
    FT232A,
    FT232B,
    FT2232C,
    FT232R,
    FT232H,
    FT2232H,
    FT4232H,
    FT4232HA,
    FT232HP,
    FT233HP,
    FT2232HP,
    FT2233HP,
    FT4232HP,
    FT4233HP,
    FTX,
};

static const char *ftdi_chip_name[] = {
    [SIO] = "SIO", /* the serial part of FT8U100AX */
    [FT232A] = "FT232A",
    [FT232B] = "FT232B",
    [FT2232C] = "FT2232C/D",
    [FT232R] = "FT232R",
    [FT232H] = "FT232H",
    [FT2232H] = "FT2232H",
    [FT4232H] = "FT4232H",
    [FT4232HA] = "FT4232HA",
    [FT232HP] = "FT232HP",
    [FT233HP] = "FT233HP",
    [FT2232HP] = "FT2232HP",
    [FT2233HP] = "FT2233HP",
    [FT4232HP] = "FT4232HP",
    [FT4233HP] = "FT4233HP",
    [FTX] = "FT-X",
};

struct usbh_ftdi {
    enum ftdi_chip_type chip_type;
};

static uint32_t ftdi_232bm_baud_base_to_divisor(uint32_t baud, int base)
{
    static const unsigned char divfrac[8] = { 0, 3, 2, 4, 1, 5, 6, 7 };
    uint32_t divisor;
    /* divisor shifted 3 bits to the left */
    int divisor3 = DIV_ROUND_CLOSEST(base, 2 * baud);
    divisor = divisor3 >> 3;
    divisor |= (uint32_t)divfrac[divisor3 & 0x7] << 14;
    /* Deal with special cases for highest baud rates. */
    if (divisor == 1) /* 1.0 */
        divisor = 0;
    else if (divisor == 0x4001) /* 1.5 */
        divisor = 1;
    return divisor;
}

static uint32_t ftdi_232bm_baud_to_divisor(uint32_t baud)
{
    return ftdi_232bm_baud_base_to_divisor(baud, 48000000);
}

static uint32_t ftdi_2232h_baud_base_to_divisor(uint32_t baud, int base)
{
    static const unsigned char divfrac[8] = { 0, 3, 2, 4, 1, 5, 6, 7 };
    uint32_t divisor;
    int divisor3;

    /* hi-speed baud rate is 10-bit sampling instead of 16-bit */
    divisor3 = DIV_ROUND_CLOSEST(8 * base, 10 * baud);

    divisor = divisor3 >> 3;
    divisor |= (uint32_t)divfrac[divisor3 & 0x7] << 14;
    /* Deal with special cases for highest baud rates. */
    if (divisor == 1) /* 1.0 */
        divisor = 0;
    else if (divisor == 0x4001) /* 1.5 */
        divisor = 1;
    /*
     * Set this bit to turn off a divide by 2.5 on baud rate generator
     * This enables baud rates up to 12Mbaud but cannot reach below 1200
     * baud with this bit set
     */
    divisor |= 0x00020000;
    return divisor;
}

static uint32_t ftdi_2232h_baud_to_divisor(uint32_t baud)
{
    return ftdi_2232h_baud_base_to_divisor(baud, 120000000);
}

int usbh_ftdi_reset(struct usbh_serial *serial)
{
    struct usb_setup_packet *setup;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = FTDI_SIO_RESET;
    setup->wValue = 0;
    setup->wIndex = serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_ftdi_set_baudrate(struct usbh_serial *serial, uint32_t baudrate)
{
    struct usb_setup_packet *setup;
    struct usbh_ftdi *ftdi_class;
    uint32_t div_value;
    uint16_t value;
    uint8_t baudrate_high;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;
    ftdi_class = (struct usbh_ftdi *)serial->priv;

    switch (ftdi_class->chip_type) {
        case FT232B:
        case FT2232C:
        case FT232R:
            if (baudrate > 3000000) {
                return -USB_ERR_INVAL;
            }
            div_value = ftdi_232bm_baud_to_divisor(baudrate);
            break;
        default:
            if ((baudrate <= 12000000) && (baudrate >= 1200)) {
                div_value = ftdi_2232h_baud_to_divisor(baudrate);
            } else if (baudrate < 1200) {
                div_value = ftdi_232bm_baud_to_divisor(baudrate);
            } else {
                return -USB_ERR_INVAL;
            }
            break;
    }

    value = div_value & 0xFFFF;
    baudrate_high = (div_value >> 16) & 0xff;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = FTDI_SIO_SET_BAUDRATE;
    setup->wValue = value;
    setup->wIndex = (baudrate_high << 8) | serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_ftdi_set_data_format(struct usbh_serial *serial, uint8_t databits, uint8_t parity, uint8_t stopbits, uint8_t isbreak)
{
    /**
     * D0-D7 databits  BITS_7=7, BITS_8=8
     * D8-D10 parity  NONE=0, ODD=1, EVEN=2, MARK=3, SPACE=4
     * D11-D12 		STOP_BIT_1=0, STOP_BIT_15=1, STOP_BIT_2=2
     * D14  		BREAK_OFF=0, BREAK_ON=1
     **/
    struct usb_setup_packet *setup;
    uint16_t value;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    value = ((isbreak & 0x01) << 14) | ((stopbits & 0x03) << 11) | ((parity & 0x0f) << 8) | (databits & 0x0f);

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = FTDI_SIO_SET_DATA;
    setup->wValue = value;
    setup->wIndex = serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_ftdi_set_latency_timer(struct usbh_serial *serial, uint16_t value)
{
    struct usb_setup_packet *setup;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = FTDI_SIO_SET_LATENCY_TIMER;
    setup->wValue = value;
    setup->wIndex = serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_ftdi_attach(struct usbh_serial *serial)
{
    uint16_t version;
    uint8_t chip_type;
    int ret;

    version = serial->hport->device_desc.bcdDevice;

    switch (version) {
        case 0x400:
            chip_type = FT232B;
            break;
        case 0x500:
            chip_type = FT2232C;
            break;
        case 0x600:
            chip_type = FT232R;
            break;
        case 0x700:
            chip_type = FT2232H;
            break;
        case 0x900:
            chip_type = FT232H;
            break;

        default:
            USB_LOG_ERR("Unsupported FTDI chip version: 0x%04x\r\n", version);
            return -USB_ERR_NOTSUPP;
    }

    USB_LOG_INFO("chip name: %s\r\n", ftdi_chip_name[chip_type]);

    struct usbh_ftdi *ftdi_class = usb_osal_malloc(sizeof(struct usbh_ftdi));
    if (!ftdi_class) {
        USB_LOG_ERR("No memory for ftdi_class\r\n");
        return -USB_ERR_NOMEM;
    }
    memset(ftdi_class, 0, sizeof(struct usbh_ftdi));
    serial->priv = ftdi_class;

    ftdi_class->chip_type = chip_type;
    ret = usbh_ftdi_set_latency_timer(serial, 0x10);
    if (ret < 0) {
        goto errout;
    }
    return 0;
errout:
    serial->priv = NULL;
    usb_osal_free(ftdi_class);
    return ret;
}

static void usbh_ftdi_detach(struct usbh_serial *serial)
{
    if (serial && serial->priv) {
        serial->priv = NULL;
        usb_osal_free(serial->priv);
    }
}

static int usbh_ftdi_set_flow_ctrl(struct usbh_serial *serial, bool hardctrl)
{
    struct usb_setup_packet *setup;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = FTDI_SIO_SET_FLOW_CTRL;
    setup->wValue = hardctrl ? FTDI_SIO_RTS_CTS_HS : FTDI_SIO_DISABLE_FLOW_CTRL;
    setup->wIndex = serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_ftdi_set_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
{
    int ret = usbh_ftdi_set_baudrate(serial, line_coding->dwDTERate);
    if (ret < 0) {
        return ret;
    }
    return usbh_ftdi_set_data_format(serial, line_coding->bDataBits, line_coding->bParityType, line_coding->bCharFormat, 0);
}

static int usbh_ftdi_set_line_state(struct usbh_serial *serial, bool dtr, bool rts)
{
    struct usb_setup_packet *setup;
    uint16_t value = 0;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    value = ((dtr ? FTDI_SIO_SET_DTR_HIGH : FTDI_SIO_SET_DTR_LOW) | (rts ? FTDI_SIO_SET_RTS_HIGH : FTDI_SIO_SET_RTS_LOW));

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = FTDI_SIO_SET_MODEM_CTRL;
    setup->wValue = value;
    setup->wIndex = serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_ftdi_get_modem_status(struct usbh_serial *serial)
{
    struct usb_setup_packet *setup;
    uint16_t status = 0;
    int ret;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }

    setup = serial->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = FTDI_SIO_GET_MODEM_STATUS;
    setup->wValue = 0x0000;
    setup->wIndex = serial->intf;
    setup->wLength = 2;

    ret = usbh_control_transfer(serial->hport, setup, serial->iobuffer);
    if (ret < 0) {
        return 0;
    }

    status = (serial->iobuffer[0] & FTDI_SIO_DSR_MASK ? USBH_SERIAL_TIOCM_DSR : 0) |
             (serial->iobuffer[0] & FTDI_SIO_CTS_MASK ? USBH_SERIAL_TIOCM_CTS : 0) |
             (serial->iobuffer[0] & FTDI_SIO_RI_MASK ? USBH_SERIAL_TIOCM_RI : 0) |
             (serial->iobuffer[0] & FTDI_SIO_RLSD_MASK ? USBH_SERIAL_TIOCM_CD : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_DTR ? USBH_SERIAL_TIOCM_DTR : 0) |
             (serial->line_state & USBH_SERIAL_TIOCM_RTS ? USBH_SERIAL_TIOCM_RTS : 0);

    return status;
}

static const struct usbh_serial_driver ftdi_driver = {
    .driver_name = "ftdi",

    .ignore_rx_header = 2,
    .ignore_tx_header = 0,

    .attach = usbh_ftdi_attach,
    .detach = usbh_ftdi_detach,
    .set_flow_control = usbh_ftdi_set_flow_ctrl,
    .set_line_coding = usbh_ftdi_set_line_coding,
    .get_line_coding = NULL,
    .set_line_state = usbh_ftdi_set_line_state,
    .get_modem_status = usbh_ftdi_get_modem_status,
};

static int usbh_ftdi_connect(struct usbh_hubport *hport, uint8_t intf)
{
    return usbh_serial_probe(hport, intf, &ftdi_driver) ? 0 : -USB_ERR_NOMEM;
}

static int usbh_ftdi_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usbh_serial *serial = (struct usbh_serial *)hport->config.intf[intf].priv;

    if (serial) {
        usbh_serial_remove(serial);
    }
    return 0;
}

static const uint16_t ftdi_id_table[][2] = {
    { 0x0403, 0x6001 },
    { 0x0403, 0x6010 },
    { 0x0403, 0x6014 },
    { 0, 0 },
};

const struct usbh_class_driver ftdi_class_driver = {
    .driver_name = "ftdi",
    .connect = usbh_ftdi_connect,
    .disconnect = usbh_ftdi_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info ftdi_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS,
    .bInterfaceClass = 0xff,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .id_table = ftdi_id_table,
    .class_driver = &ftdi_class_driver
};