/*
 * Copyright (c) 2025, sakumisu
 * Copyright (c) 2025, MDLZCOOL
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_serial"
#include "usb_log.h"

#define DEV_FORMAT_VENDOR  "/dev/ttyUSB%d"
#define DEV_FORMAT_CDC_ACM "/dev/ttyACM%d"

#define CONFIG_USBHOST_MAX_SERIAL_CLASS 4

static struct usbh_serial g_serial_class[CONFIG_USBHOST_MAX_SERIAL_CLASS];

static uint32_t g_devinuse = 0;
static uint32_t g_cdcacm_devinuse = 0;

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_serial_iobuffer[CONFIG_USBHOST_MAX_SERIAL_CLASS][USB_ALIGN_UP((USBH_SERIAL_RX2_NOCACHE_OFFSET + USBH_SERIAL_RX2_NOCACHE_SIZE), CONFIG_USB_ALIGN_SIZE)];

/* refer to cherryrb */
static int usbh_serial_ringbuffer_init(usbh_serial_ringbuf_t *rb, void *pool, uint32_t size)
{
    if (NULL == rb) {
        return -1;
    }

    if (NULL == pool) {
        return -1;
    }

    if ((size < 2) || (size & (size - 1))) {
        return -1;
    }

    rb->in = 0;
    rb->out = 0;
    rb->mask = size - 1;
    rb->pool = pool;

    return 0;
}

static void usbh_serial_ringbuffer_reset(usbh_serial_ringbuf_t *rb)
{
    rb->in = 0;
    rb->out = 0;
}

static uint32_t usbh_serial_ringbuffer_get_used(usbh_serial_ringbuf_t *rb)
{
    return rb->in - rb->out;
}

static uint32_t usbh_serial_ringbuffer_write(usbh_serial_ringbuf_t *rb, void *data, uint32_t size)
{
    uint32_t unused;
    uint32_t offset;
    uint32_t remain;

    unused = (rb->mask + 1) - (rb->in - rb->out);

    if (size > unused) {
        size = unused;
    }

    offset = rb->in & rb->mask;

    remain = rb->mask + 1 - offset;
    remain = remain > size ? size : remain;

    memcpy(((uint8_t *)(rb->pool)) + offset, data, remain);
    memcpy(rb->pool, (uint8_t *)data + remain, size - remain);

    rb->in += size;

    return size;
}

static uint32_t usbh_serial_ringbuffer_peek(usbh_serial_ringbuf_t *rb, void *data, uint32_t size)
{
    uint32_t used;
    uint32_t offset;
    uint32_t remain;

    used = rb->in - rb->out;
    if (size > used) {
        size = used;
    }

    offset = rb->out & rb->mask;

    remain = rb->mask + 1 - offset;
    remain = remain > size ? size : remain;

    memcpy(data, ((uint8_t *)(rb->pool)) + offset, remain);
    memcpy((uint8_t *)data + remain, rb->pool, size - remain);

    return size;
}

static uint32_t usbh_serial_ringbuffer_read(usbh_serial_ringbuf_t *rb, void *data, uint32_t size)
{
    size = usbh_serial_ringbuffer_peek(rb, data, size);
    rb->out += size;
    return size;
}

static struct usbh_serial *usbh_serial_alloc(bool is_cdcacm)
{
    uint8_t devno;
    uint8_t devno2;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_SERIAL_CLASS; devno++) {
        if ((g_devinuse & (1U << devno)) == 0) {
            g_devinuse |= (1U << devno);
            memset(&g_serial_class[devno], 0, sizeof(struct usbh_serial));
            g_serial_class[devno].minor = devno;
            g_serial_class[devno].cdc_minor = -1;
            g_serial_class[devno].iobuffer = g_serial_iobuffer[devno];
            g_serial_class[devno].rx_complete_sem = usb_osal_sem_create(0);

            if (is_cdcacm) {
                for (devno2 = 0; devno2 < CONFIG_USBHOST_MAX_SERIAL_CLASS; devno2++) {
                    if ((g_cdcacm_devinuse & (1U << devno2)) == 0) {
                        g_cdcacm_devinuse |= (1U << devno2);
                        g_serial_class[devno].cdc_minor = devno2;
                        return &g_serial_class[devno];
                    }
                }

                g_devinuse &= ~(1U << devno);
                return NULL;
            } else {
                return &g_serial_class[devno];
            }
        }
    }
    return NULL;
}

static void usbh_serial_free(struct usbh_serial *serial)
{
    uint8_t devno = serial->minor;
    if (devno < 32) {
        g_devinuse &= ~(1U << devno);
    }

    if (serial->cdc_minor >= 0) {
        g_cdcacm_devinuse &= ~(1U << serial->cdc_minor);
    }

    if (g_serial_class[devno].rx_complete_sem) {
        usb_osal_sem_delete(g_serial_class[devno].rx_complete_sem);
    }
}

static void usbh_serial_callback(void *arg, int nbytes)
{
    struct usbh_serial *serial = (struct usbh_serial *)arg;
    int ret;

    if (nbytes < 0) {
        if (nbytes != -USB_ERR_SHUTDOWN) {
            USB_LOG_ERR("serial transfer error: %d\n", nbytes);
        }
        serial->rx_errorcode = nbytes;
        usb_osal_sem_give(serial->rx_complete_sem);
        return;
    }

    if (nbytes < serial->driver->ignore_rx_header) {
        USB_LOG_ERR("serial rx short packet: %d\n", nbytes);
        serial->rx_errorcode = -USB_ERR_IO;
        usb_osal_sem_give(serial->rx_complete_sem);
        return;
    }

    if (nbytes >= serial->driver->ignore_rx_header) {
        /* resubmit the read urb */
        usbh_bulk_urb_fill(&serial->bulkin_urb, serial->hport, serial->bulkin, &serial->iobuffer[serial->rx_buf_index ? USBH_SERIAL_RX_NOCACHE_OFFSET : USBH_SERIAL_RX2_NOCACHE_OFFSET], serial->bulkin->wMaxPacketSize,
                           0, usbh_serial_callback, serial);
        ret = usbh_submit_urb(&serial->bulkin_urb);
        if (ret < 0) {
            USB_LOG_ERR("serial submit failed: %d\n", ret);
            serial->rx_errorcode = ret;
            usb_osal_sem_give(serial->rx_complete_sem);
            return;
        }

        usbh_serial_ringbuffer_write(&serial->rx_rb,
                                     &serial->iobuffer[(serial->rx_buf_index ? USBH_SERIAL_RX2_NOCACHE_OFFSET : USBH_SERIAL_RX_NOCACHE_OFFSET) + serial->driver->ignore_rx_header],
                                     (nbytes - serial->driver->ignore_rx_header));

        if (serial->rx_complete_callback) {
            serial->rx_complete_callback(serial, nbytes - serial->driver->ignore_rx_header);
        }
        serial->rx_buf_index ^= 1;
        serial->rx_errorcode = 0;
        usb_osal_sem_give(serial->rx_complete_sem);
    }
}

struct usbh_serial *usbh_serial_probe(struct usbh_hubport *hport, uint8_t intf,
                                      const struct usbh_serial_driver *driver)
{
    struct usb_endpoint_descriptor *ep_desc;
    struct usbh_serial *serial;
    bool is_cdcacm = false;
    int ret;

    if (strcmp(driver->driver_name, "cdc_acm") == 0) {
        is_cdcacm = true;
    }

    serial = usbh_serial_alloc(is_cdcacm);
    if (serial == NULL) {
        USB_LOG_ERR("Fail to alloc serial class\r\n");
        return NULL;
    }

    serial->hport = hport;
    serial->intf = intf;
    serial->driver = driver;

    if (driver->attach) {
        ret = driver->attach(serial);
        if (ret < 0) {
            USB_LOG_ERR("Serial attach failed: %d\r\n", ret);
            usbh_serial_free(serial);
            return NULL;
        }
    }

    if (is_cdcacm) {
        intf = intf + 1; /* data interface */
    }

    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;

        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_BULK) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(serial->bulkin, ep_desc);
            } else {
                USBH_EP_INIT(serial->bulkout, ep_desc);
            }
        }
    }

    if (is_cdcacm) {
        intf = intf - 1; /* data interface */
    }

    if (!serial->bulkin || !serial->bulkout) {
        USB_LOG_ERR("Serial bulk in/out endpoint not found\r\n");
        usbh_serial_free(serial);
        return NULL;
    }

    if (is_cdcacm) {
        snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT_CDC_ACM, serial->cdc_minor);
    } else {
        snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT_VENDOR, serial->minor);
    }

    hport->config.intf[intf].priv = serial;
    USB_LOG_INFO("Register Serial Class: %s (%s)\r\n", hport->config.intf[intf].devname, driver->driver_name);

    usbh_serial_run(serial);

    return serial;
}

void usbh_serial_remove(struct usbh_serial *serial)
{
    if (!serial || !serial->hport)
        return;

    usbh_serial_close(serial);

    if (serial->driver && serial->driver->detach) {
        serial->driver->detach(serial);
    }

    if (serial->hport->config.intf[serial->intf].priv) {
        usb_osal_thread_schedule_other();
        USB_LOG_INFO("Unregister Serial Class: %s (%s)\r\n", serial->hport->config.intf[serial->intf].devname, serial->driver->driver_name);
        usbh_serial_stop(serial);
    }

    usbh_serial_free(serial);
}

struct usbh_serial *usbh_serial_open(const char *devname, uint32_t open_flags)
{
    struct usbh_serial *serial;
    int ret;

    serial = usbh_find_class_instance(devname);
    if (!serial) {
        return NULL;
    }

    if (serial->ref_count != 0) {
        USB_LOG_ERR("Device busy: %s\r\n", devname);
        return NULL;
    }

    if (serial && serial->driver && serial->driver->open) {
        ret = serial->driver->open(serial);
        if (ret < 0) {
            return NULL;
        }
    }

    usbh_serial_ringbuffer_init(&serial->rx_rb, serial->rx_rb_pool, CONFIG_USBHOST_SERIAL_RX_SIZE);

    serial->ref_count++;
    serial->open_flags = open_flags;

    return serial;
}

int usbh_serial_close(struct usbh_serial *serial)
{
    if (!serial || !serial->hport) {
        return -USB_ERR_INVAL;
    }

    if (serial->ref_count == 0) {
        return 0;
    }

    if (serial->bulkin) {
        usbh_kill_urb(&serial->bulkin_urb);
    }
    if (serial->bulkout) {
        usbh_kill_urb(&serial->bulkout_urb);
    }

    if (serial && serial->driver && serial->driver->set_flow_control && serial->rtscts) {
        serial->driver->set_flow_control(serial, false);
    }

    if (serial && serial->driver && serial->driver->close) {
        serial->driver->close(serial);
    }

    serial->ref_count--;
    serial->rtscts = false;

    return 0;
}

static int usbh_serial_tiocmset(struct usbh_serial *serial, uint32_t set, uint32_t clear)
{
    int ret;
    uint16_t line_state;
    bool dtr;
    bool rts;

    if (!serial || !serial->hport || !serial->hport->connected) {
        return -USB_ERR_INVAL;
    }

    if (serial->ref_count == 0) {
        return -USB_ERR_NODEV;
    }

    line_state = serial->line_state;
    clear &= ~set; /* 'set' takes precedence over 'clear' */

    if (set & USBH_SERIAL_TIOCM_DTR) {
        line_state |= USBH_SERIAL_TIOCM_DTR;
    }
    if (set & USBH_SERIAL_TIOCM_RTS) {
        line_state |= USBH_SERIAL_TIOCM_RTS;
    }
    if (clear & USBH_SERIAL_TIOCM_DTR) {
        line_state &= ~USBH_SERIAL_TIOCM_DTR;
    }
    if (clear & USBH_SERIAL_TIOCM_RTS) {
        line_state &= ~USBH_SERIAL_TIOCM_RTS;
    }

    dtr = (line_state & USBH_SERIAL_TIOCM_DTR) ? true : false;
    rts = (line_state & USBH_SERIAL_TIOCM_RTS) ? true : false;

    if (serial && serial->driver && serial->driver->set_line_state) {
        ret = serial->driver->set_line_state(serial, dtr, rts);
    } else {
        return -USB_ERR_NOTSUPP;
    }
    serial->line_state = line_state;

    return ret;
}

int usbh_serial_control(struct usbh_serial *serial, int cmd, void *arg)
{
    int ret;

    if (!serial || !serial->hport || !serial->hport->connected) {
        return -USB_ERR_INVAL;
    }

    if (serial->ref_count == 0) {
        return -USB_ERR_NODEV;
    }

    switch (cmd) {
        case USBH_SERIAL_CMD_SET_ATTR: {
            struct usbh_serial_termios *termios = (struct usbh_serial_termios *)arg;
            struct cdc_line_coding line_coding;

            line_coding.dwDTERate = termios->baudrate;
            line_coding.bCharFormat = termios->stopbits;
            line_coding.bParityType = termios->parity;
            line_coding.bDataBits = termios->databits;

            if (serial->bulkin) {
                usbh_kill_urb(&serial->bulkin_urb);
            }
            if (serial->bulkout) {
                usbh_kill_urb(&serial->bulkout_urb);
            }

            if (serial && serial->driver && serial->driver->set_line_coding) {
                ret = serial->driver->set_line_coding(serial, &line_coding);
                if (ret < 0) {
                    return ret;
                }
            } else {
                return -USB_ERR_NOTSUPP;
            }

            memcpy(&serial->line_coding, &line_coding, sizeof(struct cdc_line_coding));

            if (serial && serial->driver && serial->driver->set_flow_control) {
                ret = serial->driver->set_flow_control(serial, termios->rtscts);
            }

            serial->rtscts = termios->rtscts;
            serial->rx_timeout_ms = termios->rx_timeout;

            ret = usbh_serial_tiocmset(serial, USBH_SERIAL_TIOCM_DTR | USBH_SERIAL_TIOCM_RTS, 0);
            if (ret < 0) {
                return ret;
            }

            usbh_serial_ringbuffer_reset(&serial->rx_rb);
            usb_osal_sem_reset(serial->rx_complete_sem);
            serial->rx_buf_index = 0;
            usbh_bulk_urb_fill(&serial->bulkin_urb, serial->hport, serial->bulkin, &serial->iobuffer[serial->rx_buf_index ? USBH_SERIAL_RX2_NOCACHE_OFFSET : USBH_SERIAL_RX_NOCACHE_OFFSET], serial->bulkin->wMaxPacketSize,
                               0, usbh_serial_callback, serial);
            ret = usbh_submit_urb(&serial->bulkin_urb);

            return ret;
        } break;
        case USBH_SERIAL_CMD_GET_ATTR: {
            struct usbh_serial_termios *termios = (struct usbh_serial_termios *)arg;
            struct cdc_line_coding line_coding;

            if (serial && serial->driver && serial->driver->get_line_coding) {
                return serial->driver->get_line_coding(serial, &line_coding);
            } else {
                memcpy(&line_coding, &serial->line_coding, sizeof(struct cdc_line_coding));
            }

            termios->baudrate = line_coding.dwDTERate;
            termios->stopbits = line_coding.bCharFormat;
            termios->parity = line_coding.bParityType;
            termios->databits = line_coding.bDataBits;
            termios->rtscts = serial->rtscts;
            termios->rx_timeout = serial->rx_timeout_ms;
            return 0;
        } break;
        case USBH_SERIAL_CMD_IOCMBIS: {
            uint32_t flags = *(uint32_t *)arg;

            return usbh_serial_tiocmset(serial, flags, 0);
        } break;
        case USBH_SERIAL_CMD_IOCMBIC: {
            uint32_t flags = *(uint32_t *)arg;

            return usbh_serial_tiocmset(serial, 0, flags);
        } break;
        case USBH_SERIAL_CMD_TIOCMSET: {
            uint32_t flags = *(uint32_t *)arg;

            uint32_t set = 0;
            uint32_t clear = 0;

            set |= (flags & USBH_SERIAL_TIOCM_DTR) ? USBH_SERIAL_TIOCM_DTR : 0;
            set |= (flags & USBH_SERIAL_TIOCM_RTS) ? USBH_SERIAL_TIOCM_RTS : 0;
            clear |= !(flags & USBH_SERIAL_TIOCM_DTR) ? USBH_SERIAL_TIOCM_DTR : 0;
            clear |= !(flags & USBH_SERIAL_TIOCM_RTS) ? USBH_SERIAL_TIOCM_RTS : 0;

            return usbh_serial_tiocmset(serial, set, clear);
        } break;
        case USBH_SERIAL_CMD_TIOCMGET: {
            uint32_t *flags = (uint32_t *)arg;
            int status;

            if (serial && serial->driver && serial->driver->get_modem_status) {
                status = serial->driver->get_modem_status(serial);
                if (status < 0) {
                    return status;
                }
            } else {
                return -USB_ERR_NOTSUPP;
            }
            *flags = status;
        } break;
        default:
            break;
    }

    return -USB_ERR_NOTSUPP;
}

int usbh_serial_write(struct usbh_serial *serial, const void *buffer, uint32_t buflen)
{
    int ret;
    struct usbh_urb *urb;

    if (!serial || !serial->hport || !serial->hport->connected || !serial->bulkout) {
        return -USB_ERR_INVAL;
    }

    if (serial->ref_count == 0) {
        return -USB_ERR_NODEV;
    }

    urb = &serial->bulkout_urb;

    usbh_bulk_urb_fill(urb, serial->hport, serial->bulkout, (uint8_t *)buffer, buflen, 0xffffffff, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }
    return ret;
}

int usbh_serial_read(struct usbh_serial *serial, void *buffer, uint32_t buflen)
{
    int ret;

    if (!serial || !serial->hport || !serial->hport->connected || !serial->bulkin || !serial->line_coding.dwDTERate) {
        return -USB_ERR_INVAL;
    }

    if (serial->ref_count == 0) {
        return -USB_ERR_NODEV;
    }

    if (serial->open_flags & USBH_SERIAL_O_NONBLOCK) {
        return usbh_serial_ringbuffer_read(&serial->rx_rb, buffer, buflen);
    } else {
        if (usbh_serial_ringbuffer_get_used(&serial->rx_rb) == 0) {
            ret = usb_osal_sem_take(serial->rx_complete_sem, serial->rx_timeout_ms == 0 ? USB_OSAL_WAITING_FOREVER : serial->rx_timeout_ms);
            if (ret < 0) {
                return ret;
            }
            if (serial->rx_errorcode < 0) {
                return serial->rx_errorcode;
            }
        }
        return usbh_serial_ringbuffer_read(&serial->rx_rb, buffer, buflen);
    }
}

int usbh_serial_cdc_write_async(struct usbh_serial *serial, uint8_t *buffer, uint32_t buflen, usbh_complete_callback_t complete, void *arg)
{
    struct usbh_urb *urb;

    if (!serial || !serial->hport || !serial->hport->connected || !serial->bulkout || !complete || serial->line_coding.dwDTERate) {
        return -USB_ERR_INVAL;
    }

    if (serial->ref_count == 0) {
        return -USB_ERR_NODEV;
    }

    urb = &serial->bulkout_urb;

    usbh_bulk_urb_fill(urb, serial->hport, serial->bulkout, buffer, buflen,
                       0, complete, serial);
    return usbh_submit_urb(urb);
}

int usbh_serial_cdc_read_async(struct usbh_serial *serial, uint8_t *buffer, uint32_t buflen, usbh_complete_callback_t complete, void *arg)
{
    struct usbh_urb *urb;

    if (!serial || !serial->hport || !serial->hport->connected || !serial->bulkin || !complete || serial->line_coding.dwDTERate) {
        return -USB_ERR_INVAL;
    }

    if (serial->ref_count == 0) {
        return -USB_ERR_NODEV;
    }

    if (buflen % serial->bulkin->wMaxPacketSize) {
        return -USB_ERR_INVAL;
    }

    urb = &serial->bulkin_urb;

    usbh_bulk_urb_fill(urb, serial->hport, serial->bulkin, buffer, MIN(buflen, serial->bulkin->wMaxPacketSize),
                       0, complete, serial);
    return usbh_submit_urb(urb);
}

void usbh_serial_help(void)
{
    USB_LOG_RAW("USB host serial test\r\n"
                "Usage: usbh_serial <ttypath> [options]...\r\n"
                "\r\n"
                "-b <baud>             set serial baudrate\r\n"
                "-t <dtr> <rts>        set rts and dtr\r\n"
                "-w string             write string\r\n"
                "-r                    read data and dump\r\n"
                "-x                    close serial device\r\n"
                "\r\n");
}

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_serial_testbuffer[512];

int usbh_serial(int argc, char **argv)
{
    static struct usbh_serial *serial;
    int ret;

    if (argc < 3) {
        usbh_serial_help();
        return 0;
    }

    if (serial) {
        if (!serial->hport || !serial->hport->connected) {
            serial = NULL;
        }
    }

    if (!serial) {
        serial = usbh_serial_open(argv[1], USBH_SERIAL_O_RDWR | USBH_SERIAL_O_NONBLOCK);
        if (!serial) {
            USB_LOG_ERR("Fail to open serial device: %s\r\n", argv[1]);
            return -USB_ERR_INVAL;
        }
    }

    if (strncmp(argv[2], "-b", 2) == 0 && argc >= 4) {
        struct usbh_serial_termios termios;

        memset(&termios, 0, sizeof(termios));
        termios.baudrate = atoi(argv[3]);
        termios.stopbits = 0;
        termios.parity = 0;
        termios.databits = 8;
        termios.rtscts = false;
        termios.rx_timeout = 0;
        usbh_serial_control(serial, USBH_SERIAL_CMD_SET_ATTR, &termios);
    } else if (strncmp(argv[2], "-t", 2) == 0 && argc >= 5) {
        uint32_t flags;

        flags = atoi(argv[3]) ? USBH_SERIAL_TIOCM_DTR : 0;
        flags |= atoi(argv[4]) ? USBH_SERIAL_TIOCM_RTS : 0;

        usbh_serial_control(serial, USBH_SERIAL_CMD_TIOCMSET, &flags);
        USB_LOG_INFO("Set DTR: %d, RTS: %d\r\n", atoi(argv[3]), atoi(argv[4]));
    } else if (strncmp(argv[2], "-w", 2) == 0 && argc >= 4) {
        memcpy(g_serial_testbuffer, argv[3], MIN(strlen(argv[3]), sizeof(g_serial_testbuffer)));
        uint32_t len = snprintf((char *)g_serial_testbuffer, sizeof(g_serial_testbuffer), "%s\r\n", argv[3]);
        ret = usbh_serial_write(serial, g_serial_testbuffer, len);
        if (ret >= 0) {
            USB_LOG_INFO("Write %d bytes\r\n", ret);
        } else {
            USB_LOG_ERR("Write failed: %d\r\n", ret);
        }
    } else if (strncmp(argv[2], "-r", 2) == 0) {
        ret = usbh_serial_read(serial, g_serial_testbuffer, sizeof(g_serial_testbuffer));
        if (ret >= 0) {
            usb_hexdump(g_serial_testbuffer, ret);
            USB_LOG_INFO("Read %d bytes\r\n", ret);
        } else {
            USB_LOG_ERR("Read failed: %d\r\n", ret);
        }
    } else if (strncmp(argv[2], "-x", 2) == 0) {
        usbh_serial_close(serial);
        serial = NULL;
    } else {
        usbh_serial_help();
    }

    return 0;
}

__WEAK void usbh_serial_run(struct usbh_serial *serial)
{
    (void)serial;
}

__WEAK void usbh_serial_stop(struct usbh_serial *serial)
{
    (void)serial;
}

static int usbh_cdc_data_connect(struct usbh_hubport *hport, uint8_t intf)
{
    (void)hport;
    (void)intf;
    return 0;
}

static int usbh_cdc_data_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    (void)hport;
    (void)intf;
    return 0;
}

const struct usbh_class_driver cdc_data_class_driver = {
    .driver_name = "cdc_data",
    .connect = usbh_cdc_data_connect,
    .disconnect = usbh_cdc_data_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info cdc_data_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS,
    .bInterfaceClass = USB_DEVICE_CLASS_CDC_DATA,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .id_table = NULL,
    .class_driver = &cdc_data_class_driver
};