/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"
#include "usbh_cp210x.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_cp210x"
#include "usb_log.h"

struct usbh_cp210x {
    uint8_t partnum;
    uint32_t fw_version;
    uint32_t min_speed;
    uint32_t max_speed;
    bool use_actual_rate;
    bool no_flow_control;
    bool no_event_mode;
};

struct cp210x_rate {
    uint32_t rate;
    uint32_t high;
};

static const struct cp210x_rate cp210x_an205_table1[] = {
    { 300, 300 },
    { 600, 600 },
    { 1200, 1200 },
    { 1800, 1800 },
    { 2400, 2400 },
    { 4000, 4000 },
    { 4800, 4803 },
    { 7200, 7207 },
    { 9600, 9612 },
    { 14400, 14428 },
    { 16000, 16062 },
    { 19200, 19250 },
    { 28800, 28912 },
    { 38400, 38601 },
    { 51200, 51558 },
    { 56000, 56280 },
    { 57600, 58053 },
    { 64000, 64111 },
    { 76800, 77608 },
    { 115200, 117028 },
    { 128000, 129347 },
    { 153600, 156868 },
    { 230400, 237832 },
    { 250000, 254234 },
    { 256000, 273066 },
    { 460800, 491520 },
    { 500000, 567138 },
    { 576000, 670254 },
    { 921600, 0xffffffff }
};

/*
 * Quantises the baud rate as per AN205 Table 1
 */
static uint32_t cp210x_get_an205_rate(uint32_t baud)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(cp210x_an205_table1); ++i) {
        if (baud <= cp210x_an205_table1[i].high)
            break;
    }

    return cp210x_an205_table1[i].rate;
}

static uint32_t cp210x_get_actual_rate(uint32_t baud)
{
    unsigned int prescale = 1;
    unsigned int div;

    if (baud <= 365)
        prescale = 4;

    div = DIV_ROUND_CLOSEST(48000000, 2 * prescale * baud);
    baud = 48000000 / (2 * prescale * div);

    return baud;
}

static void usbh_cp210x_init_max_speed(struct usbh_serial *serial)
{
    struct usbh_cp210x *cp210x_class;

    if (!serial || !serial->hport || !serial->priv) {
        return;
    }

    cp210x_class = (struct usbh_cp210x *)serial->priv;

    bool use_actual_rate = false;
    uint32_t min = 300;
    uint32_t max;

    switch (cp210x_class->partnum) {
        case CP210X_PARTNUM_CP2101:
            max = 921600;
            break;
        case CP210X_PARTNUM_CP2102:
        case CP210X_PARTNUM_CP2103:
            max = 1000000;
            break;
        case CP210X_PARTNUM_CP2104:
            use_actual_rate = true;
            max = 2000000;
            break;
        case CP210X_PARTNUM_CP2108:
            max = 2000000;
            break;
        case CP210X_PARTNUM_CP2105:
            if (serial->intf == 0) {
                use_actual_rate = true;
                max = 2000000; /* ECI */
            } else {
                min = 2400;
                max = 921600; /* SCI */
            }
            break;
        case CP210X_PARTNUM_CP2102N_QFN28:
        case CP210X_PARTNUM_CP2102N_QFN24:
        case CP210X_PARTNUM_CP2102N_QFN20:
            use_actual_rate = true;
            max = 3000000;
            break;
        default:
            max = 2000000;
            break;
    }

    cp210x_class->min_speed = min;
    cp210x_class->max_speed = max;
    cp210x_class->use_actual_rate = use_actual_rate;
}

static int usbh_cp210x_control_out(struct usbh_serial *serial, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint8_t *data, uint16_t size)
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
    setup->wLength = size;

    if (data && size) {
        memcpy(serial->iobuffer, data, size);
        return usbh_control_transfer(serial->hport, setup, serial->iobuffer);
    } else {
        return usbh_control_transfer(serial->hport, setup, NULL);
    }
}

static int usbh_cp210x_control_in(struct usbh_serial *serial, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint8_t *data, uint16_t size)
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

static int usbh_cp210x_get_partnum(struct usbh_serial *serial)
{
    uint8_t version[3];
    struct usbh_cp210x *cp210x_class;
    int ret;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    cp210x_class = (struct usbh_cp210x *)serial->priv;

    ret = usbh_cp210x_control_in(serial, CP210X_VENDOR_SPECIFIC, CP210X_GET_PARTNUM, serial->intf, (uint8_t *)&cp210x_class->partnum, 1);
    if (ret < 0) {
        return ret;
    }

    USB_LOG_INFO("chip partnum: 0x%02x\r\n", cp210x_class->partnum);

    switch (cp210x_class->partnum) {
        case CP210X_PARTNUM_CP2102:
            break;
        case CP210X_PARTNUM_CP2105:
        case CP210X_PARTNUM_CP2108:
            ret = usbh_cp210x_control_in(serial, CP210X_VENDOR_SPECIFIC, CP210X_GET_FW_VER_2N, serial->intf, version, 3);
            if (ret < 0) {
                return ret;
            }
            cp210x_class->fw_version = version[0] << 16 | version[1] << 8 | version[2];
            break;
        case CP210X_PARTNUM_CP2102N_QFN28:
        case CP210X_PARTNUM_CP2102N_QFN24:
        case CP210X_PARTNUM_CP2102N_QFN20:
            ret = usbh_cp210x_control_in(serial, CP210X_VENDOR_SPECIFIC, CP210X_GET_FW_VER_2N, serial->intf, version, 3);
            if (ret < 0) {
                return ret;
            }
            cp210x_class->fw_version = version[0] << 16 | version[1] << 8 | version[2];
            if (cp210x_class->fw_version <= 0x10004)
                cp210x_class->no_flow_control = true;
            break;
        default:
            break;
    }
    return ret;
}

static int usbh_cp210x_enable(struct usbh_serial *serial)
{
    return usbh_cp210x_control_out(serial, CP210X_IFC_ENABLE, 1, serial->intf, NULL, 0);
}

static int usbh_cp210x_set_chars(struct usbh_serial *serial)
{
    struct cp210x_special_chars chars = { 0 };

    return usbh_cp210x_control_out(serial, CP210X_SET_CHARS, 0, serial->intf, (uint8_t *)&chars, sizeof(struct cp210x_special_chars));
}

// static int usbh_cp210x_get_common_status(struct usbh_serial *serial, struct cp210x_comm_status *status)
// {
//     return usbh_cp210x_control_in(serial, CP210X_GET_COMM_STATUS, 0, serial->intf, (uint8_t *)status, sizeof(struct cp210x_comm_status));
// }

static int usbh_cp210x_set_baudrate(struct usbh_serial *serial, uint32_t baudrate)
{
    struct usb_setup_packet *setup;
    struct usbh_cp210x *cp210x_class;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;
    cp210x_class = (struct usbh_cp210x *)serial->priv;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_SET_BAUDRATE;
    setup->wValue = 0;
    setup->wIndex = serial->intf;
    setup->wLength = 4;

    if (cp210x_class->use_actual_rate)
        baudrate = cp210x_get_actual_rate(baudrate);
    else if (baudrate < 1000000)
        baudrate = cp210x_get_an205_rate(baudrate);

    memcpy(serial->iobuffer, (uint8_t *)&baudrate, 4);
    return usbh_control_transfer(serial->hport, setup, serial->iobuffer);
}

static int usbh_cp210x_set_data_format(struct usbh_serial *serial, uint8_t databits, uint8_t parity, uint8_t stopbits)
{
    struct usb_setup_packet *setup;
    uint16_t value;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }
    setup = serial->hport->setup;

    value = ((databits & 0x0F) << 8) | ((parity & 0x0f) << 4) | ((stopbits & 0x03) << 0);

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = CP210X_SET_LINE_CTL;
    setup->wValue = value;
    setup->wIndex = serial->intf;
    setup->wLength = 0;

    return usbh_control_transfer(serial->hport, setup, NULL);
}

static int usbh_cp210x_attach(struct usbh_serial *serial)
{
    int ret;

    struct usbh_cp210x *cp210x_class = usb_osal_malloc(sizeof(struct usbh_cp210x));
    if (!cp210x_class) {
        return -USB_ERR_NOMEM;
    }
    memset(cp210x_class, 0, sizeof(struct usbh_cp210x));
    serial->priv = cp210x_class;

    ret = usbh_cp210x_get_partnum(serial);
    usbh_cp210x_init_max_speed(serial);
    ret |= usbh_cp210x_enable(serial);
    ret |= usbh_cp210x_set_chars(serial);
    if (ret < 0) {
        goto errout;
    }
    return 0;
errout:
    serial->priv = NULL;
    usb_osal_free(cp210x_class);
    return ret;
}

static void usbh_cp210x_detach(struct usbh_serial *serial)
{
    if (serial && serial->priv) {
        serial->priv = NULL;
        usb_osal_free(serial->priv);
    }
}

int usbh_cp210x_set_flow_ctrl(struct usbh_serial *serial, bool enable)
{
    struct cp210x_flow_ctl flow_ctl = { 0 };
    uint32_t flow_repl;
    uint32_t ctl_hs;
    int ret;

    ret = usbh_cp210x_control_in(serial, CP210X_GET_FLOW, 0, serial->intf, (uint8_t *)&flow_ctl, sizeof(struct cp210x_flow_ctl));
    if (ret < 0) {
        return ret;
    }

    ctl_hs = flow_ctl.lControlHandshake;
    flow_repl = flow_ctl.lFlowReplace;

    ctl_hs &= ~CP210X_SERIAL_DSR_HANDSHAKE;
    ctl_hs &= ~CP210X_SERIAL_DCD_HANDSHAKE;
    ctl_hs &= ~CP210X_SERIAL_DSR_SENSITIVITY;
    ctl_hs &= ~CP210X_SERIAL_DTR_MASK;
    ctl_hs |= CP210X_SERIAL_DTR_INACTIVE;

    flow_repl &= ~CP210X_SERIAL_RTS_MASK;
    flow_repl &= ~CP210X_SERIAL_AUTO_RECEIVE;
    flow_repl &= ~CP210X_SERIAL_AUTO_TRANSMIT;
    flow_repl |= CP210X_SERIAL_RTS_INACTIVE;

    flow_repl &= ~CP210X_SERIAL_RTS_MASK;
    if (enable) {
        ctl_hs |= CP210X_SERIAL_CTS_HANDSHAKE;
    } else {
        ctl_hs &= ~CP210X_SERIAL_CTS_HANDSHAKE;
    }
    flow_ctl.lControlHandshake = ctl_hs;
    flow_ctl.lFlowReplace = flow_repl;

    return usbh_cp210x_control_out(serial, CP210X_SET_FLOW, 0, serial->intf, (uint8_t *)&flow_ctl, sizeof(struct cp210x_flow_ctl));
}

int usbh_cp210x_set_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
{
    int ret;

    ret = usbh_cp210x_set_baudrate(serial, line_coding->dwDTERate);
    if (ret < 0) {
        return ret;
    }
    return usbh_cp210x_set_data_format(serial, line_coding->bDataBits, line_coding->bParityType, line_coding->bCharFormat);
}

int usbh_cp210x_set_line_state(struct usbh_serial *serial, bool dtr, bool rts)
{
    struct cp210x_flow_ctl flow_ctl = { 0 };
    uint32_t flow_repl;
    uint32_t ctl_hs;
    uint16_t control = 0;
    int ret;

    if (!serial || !serial->hport || !serial->priv) {
        return -USB_ERR_INVAL;
    }

    if (serial->rtscts) {
        ret = usbh_cp210x_control_in(serial, CP210X_GET_FLOW, 0, serial->intf, (uint8_t *)&flow_ctl, sizeof(struct cp210x_flow_ctl));
        if (ret < 0) {
            return ret;
        }
        ctl_hs = flow_ctl.lControlHandshake;
        flow_repl = flow_ctl.lFlowReplace;

        ctl_hs &= ~CP210X_SERIAL_DTR_MASK;
        if (dtr)
            ctl_hs |= CP210X_SERIAL_DTR_ACTIVE;
        else
            ctl_hs |= CP210X_SERIAL_DTR_INACTIVE;

        flow_repl &= ~CP210X_SERIAL_RTS_MASK;
        if (rts)
            flow_repl |= CP210X_SERIAL_RTS_FLOW_CTL;
        else
            flow_repl |= CP210X_SERIAL_RTS_INACTIVE;

        flow_ctl.lControlHandshake = ctl_hs;
        flow_ctl.lFlowReplace = flow_repl;

        return usbh_cp210x_control_out(serial, CP210X_SET_FLOW, 0, serial->intf, (uint8_t *)&flow_ctl, sizeof(struct cp210x_flow_ctl));
    } else {
        if (dtr) {
            control |= CP210X_CONTROL_DTR;
        }
        if (rts) {
            control |= CP210X_CONTROL_RTS;
        }
        control |= CP210X_CONTROL_WRITE_DTR;
        control |= CP210X_CONTROL_WRITE_RTS;
        return usbh_cp210x_control_out(serial, CP210X_SET_MHS, control, serial->intf, NULL, 0);
    }
}

static int usbh_cp210x_get_modem_status(struct usbh_serial *serial)
{
    int ret;
    uint8_t control;
    uint16_t status;

    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }

    ret = usbh_cp210x_control_in(serial, CP210X_GET_MDMSTS, 0, serial->intf, (uint8_t *)&control, 1);
    if (ret < 0) {
        return ret;
    }

    status = ((control & CP210X_CONTROL_DTR) ? USBH_SERIAL_TIOCM_DTR : 0) |
             ((control & CP210X_CONTROL_RTS) ? USBH_SERIAL_TIOCM_RTS : 0) |
             ((control & CP210X_CONTROL_CTS) ? USBH_SERIAL_TIOCM_CTS : 0) |
             ((control & CP210X_CONTROL_DSR) ? USBH_SERIAL_TIOCM_DSR : 0) |
             ((control & CP210X_CONTROL_RING) ? USBH_SERIAL_TIOCM_RI : 0) |
             ((control & CP210X_CONTROL_DCD) ? USBH_SERIAL_TIOCM_CD : 0);

    return status;
}

static const struct usbh_serial_driver cp210x_driver = {
    .driver_name = "cp210x",

    .ignore_rx_header = 0,
    .ignore_tx_header = 0,

    .attach = usbh_cp210x_attach,
    .detach = usbh_cp210x_detach,
    .set_flow_control = usbh_cp210x_set_flow_ctrl,
    .set_line_coding = usbh_cp210x_set_line_coding,
    .get_line_coding = NULL,
    .set_line_state = usbh_cp210x_set_line_state,
    .get_modem_status = usbh_cp210x_get_modem_status,
};

static int usbh_cp210x_connect(struct usbh_hubport *hport, uint8_t intf)
{
    return usbh_serial_probe(hport, intf, &cp210x_driver) ? 0 : -USB_ERR_NOMEM;
}

static int usbh_cp210x_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usbh_serial *serial = (struct usbh_serial *)hport->config.intf[intf].priv;

    if (serial) {
        usbh_serial_remove(serial);
    }
    return 0;
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
    .bInterfaceClass = 0xff,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .id_table = cp210x_id_table,
    .class_driver = &cp210x_class_driver
};