/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-16     GuEe-GUI     first version
 */

#ifndef __SERIAL_8250_H__
#define __SERIAL_8250_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/serial_dm.h>

#include <ioremap.h>

#include "regs.h"

enum
{
    PORT_UNKNOWN,
    PORT_IO,
    PORT_MMIO,
    PORT_MMIO16,
    PORT_MMIO32,
    PORT_MMIO32BE,
};

struct serial8250
{
    struct rt_serial_device parent;
    struct rt_clk *clk;

    int irq;
    void *base;
    rt_size_t size;
    rt_uint32_t freq;       /* frequency */
    rt_uint32_t regshift;   /* reg offset shift */
    rt_uint8_t iotype;      /* io access style */

    struct rt_spinlock spinlock;

    rt_err_t (*serial_ios)(struct serial8250 *, struct serial_configure *ios);
    rt_uint32_t (*serial_in)(struct serial8250 *, int offset);
    void (*serial_out)(struct serial8250 *, int offset, int value);
    rt_err_t (*serial_dma_enable)(struct serial8250 *, rt_bool_t enabled);
    rt_ssize_t (*serial_dma_tx)(struct serial8250 *, const rt_uint8_t *buf, rt_size_t size);
    rt_ssize_t (*serial_dma_rx)(struct serial8250 *, rt_uint8_t *buf, rt_size_t size);
    rt_err_t (*handle_irq)(struct serial8250 *, int irq);

    /* Free all resource (and parent) by child */
    void (*remove)(struct serial8250 *);
    void *data;
};

#define serial8250_alloc(obj) rt_calloc(1, sizeof(typeof(*obj)))
#define raw_to_serial8250(raw_serial) rt_container_of(raw_serial, struct serial8250, parent)

rt_err_t serial8250_config(struct serial8250 *serial, const char *options);
rt_err_t serial8250_setup(struct serial8250 *serial);
rt_err_t serial8250_remove(struct serial8250 *serial);

rt_uint32_t serial8250_in(struct serial8250 *serial, int offset);
void serial8250_out(struct serial8250 *serial, int offset, int value);
void serial8250_dma_tx_done(struct serial8250 *serial);
void serial8250_dma_rx_done(struct serial8250 *serial, int recv_len);
rt_err_t serial8250_ios(struct serial8250 *serial, struct serial_configure *cfg);

rt_err_t serial8250_uart_configure(struct rt_serial_device *raw_serial, struct serial_configure *cfg);
rt_err_t serial8250_uart_control(struct rt_serial_device *raw_serial, int cmd, void *arg);
int serial8250_uart_putc(struct rt_serial_device *raw_serial, char c);
int serial8250_uart_getc(struct rt_serial_device *raw_serial);
rt_ssize_t serial8250_uart_dma_transmit(struct rt_serial_device *raw_serial,
        rt_uint8_t *buf, rt_size_t size, int direction);

int serial8250_early_putc(struct rt_serial_device *raw_serial, char c);
rt_err_t serial8250_early_fdt_setup(struct serial8250 *serial, struct rt_fdt_earlycon *con, const char *options);

extern struct serial8250 early_serial8250;
extern const struct rt_uart_ops serial8250_uart_ops;

#endif /* __SERIAL_8250_H__ */
