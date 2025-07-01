/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_ftdi.h"

#define DEV_FORMAT "/dev/ttyUSB%d"

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_ftdi_buf[USB_ALIGN_UP(64, CONFIG_USB_ALIGN_SIZE)];

#define CONFIG_USBHOST_MAX_FTDI_CLASS 1

static struct usbh_ftdi g_ftdi_class[CONFIG_USBHOST_MAX_FTDI_CLASS];
static uint32_t g_devinuse = 0;

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

static struct usbh_ftdi *usbh_ftdi_class_alloc(void)
{
    uint8_t devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_FTDI_CLASS; devno++) {
        if ((g_devinuse & (1U << devno)) == 0) {
            g_devinuse |= (1U << devno);
            memset(&g_ftdi_class[devno], 0, sizeof(struct usbh_ftdi));
            g_ftdi_class[devno].minor = devno;
            return &g_ftdi_class[devno];
        }
    }
    return NULL;
}

static void usbh_ftdi_class_free(struct usbh_ftdi *ftdi_class)
{
    uint8_t devno = ftdi_class->minor;

    if (devno < 32) {
        g_devinuse &= ~(1U << devno);
    }
    memset(ftdi_class, 0, sizeof(struct usbh_ftdi));
}

/*
 * Divide positive or negative dividend by positive or negative divisor
 * and round to closest integer. Result is undefined for negative
 * divisors if the dividend variable type is unsigned and for negative
 * dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor) (       \
    {                                         \
        typeof(x) __x = x;                    \
        typeof(divisor) __d = divisor;        \
        (((typeof(x))-1) > 0 ||               \
         ((typeof(divisor))-1) > 0 ||         \
         (((__x) > 0) == ((__d) > 0))) ?      \
            (((__x) + ((__d) / 2)) / (__d)) : \
            (((__x) - ((__d) / 2)) / (__d));  \
    })

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

int usbh_ftdi_reset(struct usbh_ftdi *ftdi_class)
{
    struct usb_setup_packet *setup;

    if (!ftdi_class || !ftdi_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = ftdi_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = SIO_RESET_REQUEST;
    setup->wValue = 0;
    setup->wIndex = ftdi_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(ftdi_class->hport, setup, NULL);
}

static int usbh_ftdi_set_modem(struct usbh_ftdi *ftdi_class, uint16_t value)
{
    struct usb_setup_packet *setup;

    if (!ftdi_class || !ftdi_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = ftdi_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = SIO_SET_MODEM_CTRL_REQUEST;
    setup->wValue = value;
    setup->wIndex = ftdi_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(ftdi_class->hport, setup, NULL);
}

static int usbh_ftdi_set_baudrate(struct usbh_ftdi *ftdi_class, uint32_t baudrate)
{
    struct usb_setup_packet *setup;
    uint32_t div_value;
    uint16_t value;
    uint8_t baudrate_high;

    if (!ftdi_class || !ftdi_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = ftdi_class->hport->setup;

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
            } else {
                return -USB_ERR_INVAL;
            }
            break;
    }

    value = div_value & 0xFFFF;
    baudrate_high = (div_value >> 16) & 0xff;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = SIO_SET_BAUDRATE_REQUEST;
    setup->wValue = value;
    setup->wIndex = (baudrate_high << 8) | ftdi_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(ftdi_class->hport, setup, NULL);
}

static int usbh_ftdi_set_data_format(struct usbh_ftdi *ftdi_class, uint8_t databits, uint8_t parity, uint8_t stopbits, uint8_t isbreak)
{
    /**
     * D0-D7 databits  BITS_7=7, BITS_8=8
     * D8-D10 parity  NONE=0, ODD=1, EVEN=2, MARK=3, SPACE=4
     * D11-D12 		STOP_BIT_1=0, STOP_BIT_15=1, STOP_BIT_2=2
     * D14  		BREAK_OFF=0, BREAK_ON=1
     **/
    struct usb_setup_packet *setup;
    uint16_t value;

    if (!ftdi_class || !ftdi_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = ftdi_class->hport->setup;

    value = ((isbreak & 0x01) << 14) | ((stopbits & 0x03) << 11) | ((parity & 0x0f) << 8) | (databits & 0x0f);

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = SIO_SET_DATA_REQUEST;
    setup->wValue = value;
    setup->wIndex = ftdi_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(ftdi_class->hport, setup, NULL);
}

static int usbh_ftdi_set_latency_timer(struct usbh_ftdi *ftdi_class, uint16_t value)
{
    struct usb_setup_packet *setup;

    if (!ftdi_class || !ftdi_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = ftdi_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = SIO_SET_LATENCY_TIMER_REQUEST;
    setup->wValue = value;
    setup->wIndex = ftdi_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(ftdi_class->hport, setup, NULL);
}

static int usbh_ftdi_set_flow_ctrl(struct usbh_ftdi *ftdi_class, uint16_t value)
{
    struct usb_setup_packet *setup;

    if (!ftdi_class || !ftdi_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = ftdi_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = SIO_SET_FLOW_CTRL_REQUEST;
    setup->wValue = value;
    setup->wIndex = ftdi_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(ftdi_class->hport, setup, NULL);
}

static int usbh_ftdi_read_modem_status(struct usbh_ftdi *ftdi_class)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!ftdi_class || !ftdi_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = ftdi_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = SIO_POLL_MODEM_STATUS_REQUEST;
    setup->wValue = 0x0000;
    setup->wIndex = ftdi_class->intf;
    setup->wLength = 2;

    ret = usbh_control_transfer(ftdi_class->hport, setup, g_ftdi_buf);
    if (ret < 0) {
        return ret;
    }
    memcpy(ftdi_class->modem_status, g_ftdi_buf, 2);
    return ret;
}

int usbh_ftdi_set_line_coding(struct usbh_ftdi *ftdi_class, struct cdc_line_coding *line_coding)
{
    memcpy((uint8_t *)&ftdi_class->line_coding, line_coding, sizeof(struct cdc_line_coding));

    int ret = usbh_ftdi_set_baudrate(ftdi_class, line_coding->dwDTERate);
    if (ret < 0) {
        return ret;
    }
    return usbh_ftdi_set_data_format(ftdi_class, line_coding->bDataBits, line_coding->bParityType, line_coding->bCharFormat, 0);
}

int usbh_ftdi_get_line_coding(struct usbh_ftdi *ftdi_class, struct cdc_line_coding *line_coding)
{
    memcpy(line_coding, (uint8_t *)&ftdi_class->line_coding, sizeof(struct cdc_line_coding));
    return 0;
}

int usbh_ftdi_set_line_state(struct usbh_ftdi *ftdi_class, bool dtr, bool rts)
{
    int ret;

    if (dtr) {
        usbh_ftdi_set_modem(ftdi_class, SIO_SET_DTR_HIGH);
    } else {
        usbh_ftdi_set_modem(ftdi_class, SIO_SET_DTR_LOW);
    }

    if (rts) {
        ret = usbh_ftdi_set_modem(ftdi_class, SIO_SET_RTS_HIGH);
    } else {
        ret = usbh_ftdi_set_modem(ftdi_class, SIO_SET_RTS_LOW);
    }

    return ret;
}

static int usbh_ftdi_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    int ret = 0;
    uint16_t version;

    struct usbh_ftdi *ftdi_class = usbh_ftdi_class_alloc();
    if (ftdi_class == NULL) {
        USB_LOG_ERR("Fail to alloc ftdi_class\r\n");
        return -USB_ERR_NOMEM;
    }

    ftdi_class->hport = hport;
    ftdi_class->intf = intf;

    hport->config.intf[intf].priv = ftdi_class;

    version = hport->device_desc.bcdDevice;

    switch (version) {
        case 0x400:
            ftdi_class->chip_type = FT232B;
            break;
        case 0x500:
            ftdi_class->chip_type = FT2232C;
            break;
        case 0x600:
            ftdi_class->chip_type = FT232R;
            break;
        case 0x700:
            ftdi_class->chip_type = FT2232H;
            break;
        case 0x800:
            ftdi_class->chip_type = FT4232H;
            break;
        case 0x900:
            ftdi_class->chip_type = FT232H;
            break;

        default:
            USB_LOG_ERR("Unknown FTDI chip version:%04x\r\n", version);
            return -USB_ERR_NOTSUPP;
    }

    USB_LOG_INFO("FTDI chip name:%s\r\n", ftdi_chip_name[ftdi_class->chip_type]);

    usbh_ftdi_reset(ftdi_class);
    usbh_ftdi_set_flow_ctrl(ftdi_class, SIO_DISABLE_FLOW_CTRL);
    usbh_ftdi_set_latency_timer(ftdi_class, 0x10);
    usbh_ftdi_read_modem_status(ftdi_class);
    USB_LOG_INFO("modem status:%02x:%02x\r\n", ftdi_class->modem_status[0], ftdi_class->modem_status[1]);

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;

        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(ftdi_class->bulkin, ep_desc);
        } else {
            USBH_EP_INIT(ftdi_class->bulkout, ep_desc);
        }
    }

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, ftdi_class->minor);

    USB_LOG_INFO("Register FTDI Class:%s\r\n", hport->config.intf[intf].devname);

#if 0
    USB_LOG_INFO("Test ftdi rx and tx and rx for 5 times, baudrate is 115200\r\n");

    struct cdc_line_coding linecoding;
    uint8_t count = 5;

    linecoding.dwDTERate = 115200;
    linecoding.bDataBits = 8;
    linecoding.bParityType = 0;
    linecoding.bCharFormat = 0;
    usbh_ftdi_set_line_coding(ftdi_class, &linecoding);
    usbh_ftdi_set_line_state(ftdi_class, true, false);

    memset(g_ftdi_buf, 'a', sizeof(g_ftdi_buf));
    ret = usbh_ftdi_bulk_out_transfer(ftdi_class, g_ftdi_buf, sizeof(g_ftdi_buf), 0xfffffff);
    USB_LOG_RAW("out ret:%d\r\n", ret);
    while (count--) {
        ret = usbh_ftdi_bulk_in_transfer(ftdi_class, g_ftdi_buf, sizeof(g_ftdi_buf), 0xfffffff);
        USB_LOG_RAW("in ret:%d\r\n", ret);
        if (ret > 0) {
            for (uint32_t i = 0; i < ret; i++) {
                USB_LOG_RAW("%02x ", g_ftdi_buf[i]);
            }
        }
        USB_LOG_RAW("\r\n");
    }
#endif
    usbh_ftdi_run(ftdi_class);
    return ret;
}

static int usbh_ftdi_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_ftdi *ftdi_class = (struct usbh_ftdi *)hport->config.intf[intf].priv;

    if (ftdi_class) {
        if (ftdi_class->bulkin) {
            usbh_kill_urb(&ftdi_class->bulkin_urb);
        }

        if (ftdi_class->bulkout) {
            usbh_kill_urb(&ftdi_class->bulkout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            usb_osal_thread_schedule_other();
            USB_LOG_INFO("Unregister FTDI Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_ftdi_stop(ftdi_class);
        }

        usbh_ftdi_class_free(ftdi_class);
    }

    return ret;
}

int usbh_ftdi_bulk_in_transfer(struct usbh_ftdi *ftdi_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &ftdi_class->bulkin_urb;

    usbh_bulk_urb_fill(urb, ftdi_class->hport, ftdi_class->bulkin, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

int usbh_ftdi_bulk_out_transfer(struct usbh_ftdi *ftdi_class, uint8_t *buffer, uint32_t buflen, uint32_t timeout)
{
    int ret;
    struct usbh_urb *urb = &ftdi_class->bulkout_urb;

    usbh_bulk_urb_fill(urb, ftdi_class->hport, ftdi_class->bulkout, buffer, buflen, timeout, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

__WEAK void usbh_ftdi_run(struct usbh_ftdi *ftdi_class)
{
    (void)ftdi_class;
}

__WEAK void usbh_ftdi_stop(struct usbh_ftdi *ftdi_class)
{
    (void)ftdi_class;
}

static const uint16_t ftdi_id_table[][2] = {
    { 0x0403, 0x6001 },
    { 0x0403, 0x6010 },
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