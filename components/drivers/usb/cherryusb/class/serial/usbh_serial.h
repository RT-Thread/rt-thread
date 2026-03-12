/*
 * Copyright (c) 2025, sakumisu
 * Copyright (c) 2025, MDLZCOOL
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_SERIAL_H
#define USBH_SERIAL_H

#include "usb_cdc.h"

#define USBH_SERIAL_CTRL_NOCACHE_OFFSET 0
#define USBH_SERIAL_CTRL_NOCACHE_SIZE   32
#define USBH_SERIAL_INT_NOCACHE_OFFSET  USB_ALIGN_UP(USBH_SERIAL_CTRL_NOCACHE_SIZE, CONFIG_USB_ALIGN_SIZE)
#define USBH_SERIAL_INT_NOCACHE_SIZE    32
#define USBH_SERIAL_RX_NOCACHE_OFFSET   USB_ALIGN_UP((USBH_SERIAL_INT_NOCACHE_OFFSET + USBH_SERIAL_INT_NOCACHE_SIZE), CONFIG_USB_ALIGN_SIZE)
#define USBH_SERIAL_RX_NOCACHE_SIZE     512
#define USBH_SERIAL_RX2_NOCACHE_OFFSET  USB_ALIGN_UP((USBH_SERIAL_RX_NOCACHE_OFFSET + USBH_SERIAL_RX_NOCACHE_SIZE), CONFIG_USB_ALIGN_SIZE)
#define USBH_SERIAL_RX2_NOCACHE_SIZE    512

#define USBH_SERIAL_DATABITS_5 5
#define USBH_SERIAL_DATABITS_6 6
#define USBH_SERIAL_DATABITS_7 7
#define USBH_SERIAL_DATABITS_8 8

#define USBH_SERIAL_PARITY_NONE  0
#define USBH_SERIAL_PARITY_ODD   1
#define USBH_SERIAL_PARITY_EVEN  2
#define USBH_SERIAL_PARITY_MARK  3
#define USBH_SERIAL_PARITY_SPACE 4

#define USBH_SERIAL_STOPBITS_1   0
#define USBH_SERIAL_STOPBITS_1_5 1
#define USBH_SERIAL_STOPBITS_2   2

/* modem lines */
#define USBH_SERIAL_TIOCM_LE   0x001 /* line enable */
#define USBH_SERIAL_TIOCM_DTR  0x002 /* data terminal ready */
#define USBH_SERIAL_TIOCM_RTS  0x004 /* request to send */
#define USBH_SERIAL_TIOCM_ST   0x010 /* secondary transmit */
#define USBH_SERIAL_TIOCM_SR   0x020 /* secondary receive */
#define USBH_SERIAL_TIOCM_CTS  0x040 /* clear to send */
#define USBH_SERIAL_TIOCM_CAR  0x100 /* carrier detect */
#define USBH_SERIAL_TIOCM_CD   USBH_SERIAL_TIOCM_CAR
#define USBH_SERIAL_TIOCM_RNG  0x200 /* ring */
#define USBH_SERIAL_TIOCM_RI   USBH_SERIAL_TIOCM_RNG
#define USBH_SERIAL_TIOCM_DSR  0x400 /* data set ready */
#define USBH_SERIAL_TIOCM_OUT1 0x2000
#define USBH_SERIAL_TIOCM_OUT2 0x4000
#define USBH_SERIAL_TIOCM_LOOP 0x8000

#define USBH_SERIAL_O_RDONLY 0x0000 /* open for reading only */
#define USBH_SERIAL_O_WRONLY 0x0001 /* open for writing only */
#define USBH_SERIAL_O_RDWR   0x0002 /* open for reading and writing */

#define USBH_SERIAL_O_ACCMODE  0x0003 /* mask for above modes, from 4.4BSD https://minnie.tuhs.org/cgi-bin/utree.pl?file=4.4BSD/usr/include/sys/fcntl.h */
#define USBH_SERIAL_O_NONBLOCK 0x0004 /* non-blocking I/O, from BSD apple https://opensource.apple.com/source/xnu/xnu-1228.0.2/bsd/sys/fcntl.h */

#define USBH_SERIAL_CMD_SET_ATTR 0
#define USBH_SERIAL_CMD_GET_ATTR 1
#define USBH_SERIAL_CMD_IOCMBIS  2
#define USBH_SERIAL_CMD_IOCMBIC  3
#define USBH_SERIAL_CMD_TIOCMSET 4
#define USBH_SERIAL_CMD_TIOCMGET 5

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t in;   /*!< Define the write pointer.               */
    uint32_t out;  /*!< Define the read pointer.                */
    uint32_t mask; /*!< Define the write and read pointer mask. */
    void *pool;    /*!< Define the memory pointer.              */
} usbh_serial_ringbuf_t;

/*
 * Counters of the input lines (CTS, DSR, RI, CD) interrupts
 */

struct usbh_serial_async_icount {
    uint32_t cts, dsr, rng, dcd, tx, rx;
    uint32_t frame, parity, overrun, brk;
    uint32_t buf_overrun;
};

struct usbh_serial_termios {
    uint32_t baudrate;
    uint8_t databits;
    uint8_t parity;
    uint8_t stopbits;
    bool rtscts; /* hardware flow control */
    uint32_t rx_timeout;
};

struct usbh_serial;

typedef void (*usbh_serial_rx_complete_callback_t)(struct usbh_serial *serial, int nbytes);

/**
 * @brief Serial Driver Operations
 */
struct usbh_serial_driver {
    const char *driver_name;

    uint8_t ignore_tx_header;
    uint8_t ignore_rx_header;

    int (*attach)(struct usbh_serial *serial);
    void (*detach)(struct usbh_serial *serial);

    int (*open)(struct usbh_serial *serial);
    void (*close)(struct usbh_serial *serial);
    int (*set_flow_control)(struct usbh_serial *serial, bool enable);
    int (*set_line_coding)(struct usbh_serial *serial, struct cdc_line_coding *line_coding);
    int (*get_line_coding)(struct usbh_serial *serial, struct cdc_line_coding *line_coding);
    int (*set_line_state)(struct usbh_serial *serial, bool dtr, bool rts);
    int (*get_modem_status)(struct usbh_serial *serial);
};

/**
 * @brief Serial Instance
 */
struct usbh_serial {
    struct usbh_hubport *hport;
    uint8_t intf;      /* Interface Number */
    int minor;         /* Serial Port Number (/dev/ttyUSBx or /dev/ttyACMx) */
    int cdc_minor;     /* Serial Port Number (/dev/ttyACMx) */
    uint8_t *iobuffer; /* I/O buffer for serial transfers */
    uint8_t ref_count; /* Reference Count */
    uint32_t open_flags;
    uint32_t rx_timeout_ms;

    struct cdc_line_coding line_coding;
    uint16_t line_state;
    bool rtscts; /* hardware flow control */
    struct usbh_serial_async_icount iocount;

    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */
    struct usbh_urb bulkout_urb;
    struct usbh_urb bulkin_urb;

    const struct usbh_serial_driver *driver;

    usbh_serial_ringbuf_t rx_rb;
    uint8_t rx_rb_pool[CONFIG_USBHOST_SERIAL_RX_SIZE];
    usb_osal_sem_t rx_complete_sem;
    uint8_t rx_buf_index;
    int rx_errorcode;
    usbh_serial_rx_complete_callback_t rx_complete_callback;

    void *priv;      /* Private Data */
    void *user_data; /* User Data */
};

/* internal api */
struct usbh_serial *usbh_serial_probe(struct usbh_hubport *hport, uint8_t intf, const struct usbh_serial_driver *driver);
void usbh_serial_remove(struct usbh_serial *serial);

/* public api */
struct usbh_serial *usbh_serial_open(const char *devname, uint32_t open_flags);
int usbh_serial_close(struct usbh_serial *serial);
int usbh_serial_control(struct usbh_serial *serial, int cmd, void *arg);
int usbh_serial_write(struct usbh_serial *serial, const void *buffer, uint32_t buflen);
int usbh_serial_read(struct usbh_serial *serial, void *buffer, uint32_t buflen);

/* cdc only api */
int usbh_serial_cdc_write_async(struct usbh_serial *serial, uint8_t *buffer, uint32_t buflen, usbh_complete_callback_t complete, void *arg);
int usbh_serial_cdc_read_async(struct usbh_serial *serial, uint8_t *buffer, uint32_t buflen, usbh_complete_callback_t complete, void *arg);

/* public weak api */
void usbh_serial_run(struct usbh_serial *serial);
void usbh_serial_stop(struct usbh_serial *serial);

int usbh_serial(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* USBH_SERIAL_H */