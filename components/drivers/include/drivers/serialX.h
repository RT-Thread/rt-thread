/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-10     THEWON       serialX first version
 * 2022-06-08     THEWON       add No TX Empty interrupt support
 * 2023-02-15     THEWON       add init ops
 */

#ifndef __SERIALX_H__
#define __SERIALX_H__

#include <rtthread.h>
#include <rtdevice.h>

#define BAUD_RATE_2400                  2400
#define BAUD_RATE_4800                  4800
#define BAUD_RATE_9600                  9600
#define BAUD_RATE_19200                 19200
#define BAUD_RATE_38400                 38400
#define BAUD_RATE_57600                 57600
#define BAUD_RATE_115200                115200
#define BAUD_RATE_230400                230400
#define BAUD_RATE_460800                460800
#define BAUD_RATE_921600                921600
#define BAUD_RATE_2000000               2000000
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

#ifndef RT_SERIAL_FIFO_BUFSZ
#define RT_SERIAL_FIFO_BUFSZ            128
#endif

#ifndef RT_SERIAL_DMA_BUFSZ
#define RT_SERIAL_DMA_BUFSZ             32
#endif

#if RT_SERIAL_DMA_BUFSZ < 32
#define RT_SERIAL_DMA_BUFSZ             32
#endif

#if RT_SERIAL_FIFO_BUFSZ < (RT_SERIAL_DMA_BUFSZ*2)
#define RT_SERIAL_FIFO_BUFSZ            RT_SERIAL_DMA_BUFSZ*2
#endif


#define RT_SERIAL_EVENT_RX_IND          0x01    /* Rx indication */
#define RT_SERIAL_EVENT_TX_DONE         0x02    /* Tx complete   */
#define RT_SERIAL_EVENT_RX_DMADONE      0x03    /* Rx DMA transfer done */
#define RT_SERIAL_EVENT_TX_DMADONE      0x04    /* Tx DMA transfer done */
#define RT_SERIAL_EVENT_RX_TIMEOUT      0x05    /* Rx timeout    */

#define RT_SERIAL_DMA_RX                0x01
#define RT_SERIAL_DMA_TX                0x02

#define RT_SERIAL_RX_INT                0x01
#define RT_SERIAL_TX_INT                0x02

#define RT_SERIAL_ERR_OVERRUN           0x01
#define RT_SERIAL_ERR_FRAMING           0x02
#define RT_SERIAL_ERR_PARITY            0x03

#define RT_SERIAL_TX_DATAQUEUE_SIZE     2048
#define RT_SERIAL_TX_DATAQUEUE_LWM      30

#define RT_SERIAL_FLOWCONTROL_CTSRTS     1
#define RT_SERIAL_FLOWCONTROL_NONE       0

/* Default config for serial_configure structure */
#define RT_SERIAL_CONFIG_DEFAULT           \
{                                          \
    BAUD_RATE_115200, /* 115200 bits/s */  \
    DATA_BITS_8,      /* 8 databits */     \
    STOP_BITS_1,      /* 1 stopbit */      \
    PARITY_NONE,      /* No parity  */     \
    BIT_ORDER_LSB,    /* LSB first sent */ \
    NRZ_NORMAL,       /* Normal mode */    \
    RT_SERIAL_FIFO_BUFSZ, /* Buffer size */  \
    RT_SERIAL_FLOWCONTROL_NONE, /* Off flowcontrol */ \
    0                                      \
}

#define RT_SERIAL_EVENT_TXDONE (1 << 0)
#define RT_SERIAL_EVENT_RXDONE (1 << 1)

//#define RT_SERIAL_USE_EVENT                 // Just for test, maybe using event in the future

struct rt_serial_device;

typedef int (*cb_serial_tx)(struct rt_serial_device *serial, const rt_uint8_t *data, int length);
typedef int (*cb_serial_rx)(struct rt_serial_device *serial, rt_uint8_t *data, int length);

struct serial_configure
{
    rt_uint32_t baud_rate;

    rt_uint32_t data_bits               :4;
    rt_uint32_t stop_bits               :2;
    rt_uint32_t parity                  :2;
    rt_uint32_t bit_order               :1;
    rt_uint32_t invert                  :1;
    rt_uint32_t bufsz                   :16;        // unused, move it to struct rt_serial_device
    rt_uint32_t flowcontrol             :1;
    rt_uint32_t reserved                :5;
};

/*
 * Serial FIFO mode
 */
struct rt_serial_fifo
{
    rt_uint32_t buf_sz;
    /* software fifo */
    rt_uint8_t *buffer;

    rt_uint16_t put_index, get_index;

    rt_bool_t is_full;
};

struct rt_serial_device
{
    struct rt_device          parent;

    const struct rt_uart_ops *ops;
    struct serial_configure   config;
    rt_uint32_t bufsz;

    void *serial_rx;
    void *serial_tx;

#ifdef RT_SERIAL_USING_DMA
    rt_size_t dma_idx_rx;
    rt_uint8_t serial_dma_rx[RT_SERIAL_DMA_BUFSZ];
    rt_uint8_t serial_dma_tx[RT_SERIAL_DMA_BUFSZ];
#endif

    cb_serial_rx _cb_rx;
    cb_serial_tx _cb_tx;
#ifndef RT_SERIAL_USE_EVENT
    struct rt_completion completion_rx;
    struct rt_completion completion_tx;
#else
    rt_event_t rx_done;
    rt_event_t tx_done;
#endif
};
typedef struct rt_serial_device rt_serial_t;

/**
 * uart operators
 */
struct rt_uart_ops
{
    int (*init)(struct rt_serial_device *serial);

    rt_err_t (*configure)(struct rt_serial_device *serial, struct serial_configure *cfg);
    rt_err_t (*control)(struct rt_serial_device *serial, int cmd, void *arg);

    int (*putc)(struct rt_serial_device *serial, char c);
    int (*getc)(struct rt_serial_device *serial);
    int (*flush)(struct rt_serial_device *serial);

#if defined (RT_SERIAL_NO_TXEIT)
    rt_bool_t (*is_int_txing)(struct rt_serial_device *serial);
    void (*start_tx)(struct rt_serial_device *serial, rt_uint8_t ch);
#else
    void (*start_tx)(struct rt_serial_device *serial);
#endif
    void (*stop_tx)(struct rt_serial_device *serial);

#ifdef RT_SERIAL_USING_DMA
    rt_bool_t (*is_dma_txing)(struct rt_serial_device *serial);
    void (*start_dma_tx)(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size);
    void (*stop_dma_tx)(struct rt_serial_device *serial);
#endif

    void (*enable_interrupt)(struct rt_serial_device *serial);
    void (*disable_interrupt)(struct rt_serial_device *serial);
};

void rt_hw_serial_isr(struct rt_serial_device *serial, int event);

rt_err_t rt_hw_serial_register(struct rt_serial_device *serial,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data);

#endif
