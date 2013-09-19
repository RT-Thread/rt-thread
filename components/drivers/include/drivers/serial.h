/*
 * File      : serial.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-05-15     lgnq         first version.
 * 2012-05-28     bernard      change interfaces
 * 2013-02-20     bernard      use RT_SERIAL_RB_BUFSZ to define
 *                             the size of ring buffer.
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <rtthread.h>

#define BAUD_RATE_4800                  4800
#define BAUD_RATE_9600                  9600
#define BAUD_RATE_115200                115200

#define DATA_BITS_5                     5
#define DATA_BITS_6                     6
#define DATA_BITS_7                     7
#define DATA_BITS_8                     8
#define DATA_BITS_9                     9

#define STOP_BITS_1                     0
#define STOP_BITS_2                     1
#define STOP_BITS_3                     2
#define STOP_BITS_4                     3

#define PARITY_NONE                     0
#define PARITY_ODD                      1
#define PARITY_EVEN                     2

#define BIT_ORDER_LSB                   0
#define BIT_ORDER_MSB                   1

#define NRZ_NORMAL                      0       /* Non Return to Zero : normal mode */
#define NRZ_INVERTED                    1       /* Non Return to Zero : inverted mode */

#ifndef RT_SERIAL_RB_BUFSZ
#define RT_SERIAL_RB_BUFSZ              64
#endif

#define RT_DEVICE_CTRL_CONFIG           0x03    /* configure device */
#define RT_DEVICE_CTRL_SET_INT          0x10    /* enable receive irq */
#define RT_DEVICE_CTRL_CLR_INT          0x11    /* disable receive irq */
#define RT_DEVICE_CTRL_GET_INT          0x12

#define RT_SERIAL_RX_INT                0x01
#define RT_SERIAL_TX_INT                0x02

#define RT_SERIAL_ERR_OVERRUN           0x01
#define RT_SERIAL_ERR_FRAMING           0x02
#define RT_SERIAL_ERR_PARITY            0x03

#define RT_SERIAL_TX_DATAQUEUE_SIZE     2048
#define RT_SERIAL_TX_DATAQUEUE_LWM      30

/* Default config for serial_configure structure */
#define RT_SERIAL_CONFIG_DEFAULT           \
{                                          \
    BAUD_RATE_115200, /* 115200 bits/s */  \
    DATA_BITS_8,      /* 8 databits */     \
    STOP_BITS_1,      /* 1 stopbit */      \
    PARITY_NONE,      /* No parity  */     \
    BIT_ORDER_LSB,    /* LSB first sent */ \
    NRZ_NORMAL,       /* Normal mode */    \
    0                                      \
}

struct serial_ringbuffer
{
    rt_uint8_t  buffer[RT_SERIAL_RB_BUFSZ];
    rt_uint16_t put_index, get_index;
};

struct serial_configure
{
    rt_uint32_t baud_rate;
    rt_uint32_t data_bits               :4;
    rt_uint32_t stop_bits               :2;
    rt_uint32_t parity                  :2;
    rt_uint32_t bit_order               :1;
    rt_uint32_t invert                  :1;
    rt_uint32_t reserved                :20;
};

struct rt_serial_device
{
    struct rt_device          parent;

    const struct rt_uart_ops *ops;
    struct serial_configure   config;

    /* rx structure */
    struct serial_ringbuffer *int_rx;
    /* tx structure */
    struct serial_ringbuffer *int_tx;

    struct rt_data_queue      tx_dq;              /* tx dataqueue */
    
    volatile rt_bool_t        dma_flag;           /* dma transfer flag */
};
typedef struct rt_serial_device rt_serial_t;

/**
 * uart operators
 */
struct rt_uart_ops
{
    rt_err_t (*configure)(struct rt_serial_device *serial, struct serial_configure *cfg);
    rt_err_t (*control)(struct rt_serial_device *serial, int cmd, void *arg);

    int (*putc)(struct rt_serial_device *serial, char c);
    int (*getc)(struct rt_serial_device *serial);

    rt_size_t (*dma_transmit)(struct rt_serial_device *serial, const char *buf, rt_size_t size);
};

void rt_hw_serial_isr(struct rt_serial_device *serial);
void rt_hw_serial_dma_tx_isr(struct rt_serial_device *serial);
rt_err_t rt_hw_serial_register(struct rt_serial_device *serial,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data);

#endif
