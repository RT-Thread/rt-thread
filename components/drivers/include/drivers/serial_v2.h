/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2021-06-01     KyleChan     first version
 */

#ifndef __SERIAL_V2_H__
#define __SERIAL_V2_H__

#include <rtthread.h>

#define BAUD_RATE_2400                  2400
#define BAUD_RATE_4800                  4800
#define BAUD_RATE_9600                  9600
#define BAUD_RATE_19200                 19200
#define BAUD_RATE_38400                 38400
#define BAUD_RATE_57600                 57600
#define BAUD_RATE_115200                115200
#define BAUD_RATE_230400                230400
#define BAUD_RATE_460800                460800
#define BAUD_RATE_500000                500000
#define BAUD_RATE_921600                921600
#define BAUD_RATE_2000000               2000000
#define BAUD_RATE_2500000               2500000
#define BAUD_RATE_3000000               3000000

#define DATA_BITS_5                     5
#define DATA_BITS_6                     6
#define DATA_BITS_7                     7
#define DATA_BITS_8                     8
#define DATA_BITS_9                     9

#define STOP_BITS_1                     0
#define STOP_BITS_2                     1
#define STOP_BITS_3                     2
#define STOP_BITS_4                     3

#ifdef _WIN32
#include <windows.h>
#else
#define PARITY_NONE                     0
#define PARITY_ODD                      1
#define PARITY_EVEN                     2
#endif

#define BIT_ORDER_LSB                   0
#define BIT_ORDER_MSB                   1

#define NRZ_NORMAL                      0       /* Non Return to Zero : normal mode */
#define NRZ_INVERTED                    1       /* Non Return to Zero : inverted mode */

#define RT_DEVICE_FLAG_RX_BLOCKING      0x1000
#define RT_DEVICE_FLAG_RX_NON_BLOCKING  0x2000

#define RT_DEVICE_FLAG_TX_BLOCKING      0x4000
#define RT_DEVICE_FLAG_TX_NON_BLOCKING  0x8000

#define RT_SERIAL_RX_BLOCKING           RT_DEVICE_FLAG_RX_BLOCKING
#define RT_SERIAL_RX_NON_BLOCKING       RT_DEVICE_FLAG_RX_NON_BLOCKING
#define RT_SERIAL_TX_BLOCKING           RT_DEVICE_FLAG_TX_BLOCKING
#define RT_SERIAL_TX_NON_BLOCKING       RT_DEVICE_FLAG_TX_NON_BLOCKING

#define RT_DEVICE_CHECK_OPTMODE         0x20

#define RT_SERIAL_EVENT_RX_IND          0x01    /* Rx indication */
#define RT_SERIAL_EVENT_TX_DONE         0x02    /* Tx complete   */
#define RT_SERIAL_EVENT_RX_DMADONE      0x03    /* Rx DMA transfer done */
#define RT_SERIAL_EVENT_TX_DMADONE      0x04    /* Tx DMA transfer done */
#define RT_SERIAL_EVENT_RX_TIMEOUT      0x05    /* Rx timeout    */

#define RT_SERIAL_ERR_OVERRUN           0x01
#define RT_SERIAL_ERR_FRAMING           0x02
#define RT_SERIAL_ERR_PARITY            0x03

#define RT_SERIAL_TX_DATAQUEUE_SIZE     2048
#define RT_SERIAL_TX_DATAQUEUE_LWM      30

#define RT_SERIAL_RX_MINBUFSZ 64
#define RT_SERIAL_TX_MINBUFSZ 64

#define RT_SERIAL_TX_BLOCKING_BUFFER    1
#define RT_SERIAL_TX_BLOCKING_NO_BUFFER 0

#define RT_SERIAL_FLOWCONTROL_CTSRTS    1
#define RT_SERIAL_FLOWCONTROL_NONE      0

/* Default config for serial_configure structure */
#define RT_SERIAL_CONFIG_DEFAULT                      \
{                                                     \
    BAUD_RATE_115200,           /* 115200 bits/s */   \
    DATA_BITS_8,                /* 8 databits */      \
    STOP_BITS_1,                /* 1 stopbit */       \
    PARITY_NONE,                /* No parity  */      \
    BIT_ORDER_LSB,              /* LSB first sent */  \
    NRZ_NORMAL,                 /* Normal mode */     \
    RT_SERIAL_RX_MINBUFSZ,      /* rxBuf size */      \
    RT_SERIAL_TX_MINBUFSZ,      /* txBuf size */      \
    RT_SERIAL_FLOWCONTROL_NONE, /* Off flowcontrol */ \
    0                                                 \
}

/**
 * @brief Sets a hook function when RX indicate is called
 *
 * @param thread is the target thread that initializing
 */
typedef void (*rt_hw_serial_rxind_hookproto_t)(rt_device_t dev, rt_size_t size);
RT_OBJECT_HOOKLIST_DECLARE(rt_hw_serial_rxind_hookproto_t, rt_hw_serial_rxind);

struct serial_configure
{
    rt_uint32_t baud_rate;

    rt_uint32_t data_bits               :4;
    rt_uint32_t stop_bits               :2;
    rt_uint32_t parity                  :2;
    rt_uint32_t bit_order               :1;
    rt_uint32_t invert                  :1;
    rt_uint32_t rx_bufsz                :16;
    rt_uint32_t tx_bufsz                :16;
    rt_uint32_t flowcontrol             :1;
    rt_uint32_t reserved                :5;
};

/*
 * Serial Receive FIFO mode
 */
struct rt_serial_rx_fifo
{
    struct rt_ringbuffer rb;

    struct rt_completion rx_cpt;

    rt_uint16_t rx_cpt_index;

    /* software fifo */
    rt_uint8_t buffer[];
};

/*
 * Serial Transmit FIFO mode
 */
struct rt_serial_tx_fifo
{
    struct rt_ringbuffer rb;

    rt_size_t put_size;

    rt_bool_t activated;

    struct rt_completion tx_cpt;

    /* software fifo */
    rt_uint8_t buffer[];
};

struct rt_serial_device
{
    struct rt_device          parent;

    const struct rt_uart_ops *ops;
    struct serial_configure   config;

    void *serial_rx;
    void *serial_tx;

    struct rt_device_notify rx_notify;
};

/**
 * uart operators
 */
struct rt_uart_ops
{
    rt_err_t (*configure)(struct rt_serial_device       *serial,
                          struct serial_configure       *cfg);

    rt_err_t (*control)(struct rt_serial_device         *serial,
                                            int          cmd,
                                            void        *arg);

    int (*putc)(struct rt_serial_device *serial, char c);
    int (*getc)(struct rt_serial_device *serial);

    rt_ssize_t (*transmit)(struct rt_serial_device       *serial,
                                 rt_uint8_t             *buf,
                                 rt_size_t               size,
                                 rt_uint32_t             tx_flag);
};

void rt_hw_serial_isr(struct rt_serial_device *serial, int event);

rt_err_t rt_hw_serial_register(struct rt_serial_device      *serial,
                               const  char                  *name,
                                      rt_uint32_t            flag,
                                      void                  *data);

rt_err_t rt_hw_serial_register_tty(struct rt_serial_device *serial);
#endif
