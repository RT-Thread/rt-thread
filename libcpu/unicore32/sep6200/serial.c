/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-16       Peng Fan     Modified from sep4020
 */
#include <rtthread.h>
#include <rthw.h>
#include "serial.h"

/**
 * @addtogroup sep6200
 */
/*@{*/

/* RT-Thread Device Interface */
/**
 * This function initializes serial
 */
static rt_err_t rt_serial_init (rt_device_t dev)
{
    struct serial_device* uart = (struct serial_device*) dev->user_data;

    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {

        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            rt_memset(uart->int_rx->rx_buffer, 0,
                sizeof(uart->int_rx->rx_buffer));
            uart->int_rx->read_index = uart->int_rx->save_index = 0;
        }

        if (dev->flag & RT_DEVICE_FLAG_INT_TX)
        {
            rt_memset(uart->int_tx->tx_buffer, 0,
                sizeof(uart->int_tx->tx_buffer));
            uart->int_tx->write_index = uart->int_tx->save_index = 0;
        }

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }

    return RT_EOK;
}

/* save a char to serial buffer */
static void rt_serial_savechar(struct serial_device* uart, char ch)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    uart->int_rx->rx_buffer[uart->int_rx->save_index] = ch;
    uart->int_rx->save_index ++;
    if (uart->int_rx->save_index >= UART_RX_BUFFER_SIZE)
        uart->int_rx->save_index = 0;

    /* if the next position is read index, discard this 'read char' */
    if (uart->int_rx->save_index == uart->int_rx->read_index)
    {
        uart->int_rx->read_index ++;
        if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
            uart->int_rx->read_index = 0;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);
    return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    return RT_EOK;
}

static rt_size_t rt_serial_read (rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    rt_err_t err_code;
    struct serial_device* uart;

    ptr = buffer;
    err_code = RT_EOK;
    uart = (struct serial_device*)dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        rt_base_t level;

        /* interrupt mode Rx */
        while (size)
        {
            if (uart->int_rx->read_index != uart->int_rx->save_index)
            {
                *ptr++ = uart->int_rx->rx_buffer[uart->int_rx->read_index];
                size --;

                /* disable interrupt */
                level = rt_hw_interrupt_disable();

                uart->int_rx->read_index ++;
                if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
                    uart->int_rx->read_index = 0;

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
            }
            else
            {
                /* set error code */
                err_code = -RT_EEMPTY;
                break;
            }
        }
    }
    else
    {
        /* polling mode */
        while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
        {
            while (uart->uart_device->lsr & USTAT_RCV_READY)
            {
                *ptr = uart->uart_device->dlbl_fifo.txfifo & 0xff;
                ptr ++;
            }
        }
    }

    /* set error code */
    rt_set_errno(err_code);
    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_size_t rt_serial_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    rt_err_t err_code;
    struct serial_device* uart;

    err_code = RT_EOK;
    ptr = (rt_uint8_t*)buffer;
    uart = (struct serial_device*)dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* interrupt mode Tx */
        while (uart->int_tx->save_index != uart->int_tx->write_index)
        {
            /* save on tx buffer */
            uart->int_tx->tx_buffer[uart->int_tx->save_index] = *ptr++;

            -- size;

            /* move to next position */
            uart->int_tx->save_index ++;

            /* wrap save index */
            if (uart->int_tx->save_index >= UART_TX_BUFFER_SIZE)
                uart->int_tx->save_index = 0;
        }

        /* set error code */
        if (size > 0)
            err_code = -RT_EFULL;
    }
    else
    {
        /* polling mode */
        while (size)
        {
            /*
             * to be polite with serial console add a line feed
             * to the carriage return character
             */
            if (*ptr == '\n' && (dev->flag & RT_DEVICE_FLAG_STREAM))
            {
                while (!(uart->uart_device->lsr & USTAT_TXB_EMPTY));
                uart->uart_device->dlbl_fifo.txfifo = '\r';
            }

            while (!(uart->uart_device->lsr & USTAT_TXB_EMPTY));
            uart->uart_device->dlbl_fifo.txfifo = (*ptr & 0x1FF);

            ++ptr; --size;
        }
    }

    /* set error code */
    rt_set_errno(err_code);

    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_serial_control (rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        break;
    }

    return RT_EOK;
}

/*
 * serial register
 */
rt_err_t rt_hw_serial_register(rt_device_t device, const char* name, rt_uint32_t flag, struct serial_device *serial)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_serial_init;
    device->open        = rt_serial_open;
    device->close       = rt_serial_close;
    device->read        = rt_serial_read;
    device->write       = rt_serial_write;
    device->control     = rt_serial_control;
    device->user_data   = serial;

    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/* ISR for serial interrupt */
void rt_hw_serial_isr(rt_device_t device)
{
    struct serial_device* uart = (struct serial_device*) device->user_data;

    /* interrupt mode receive */
    RT_ASSERT(device->flag & RT_DEVICE_FLAG_INT_RX);

    /* save on rx buffer */
    while (uart->uart_device->lsr & USTAT_RCV_READY)
    {
        rt_serial_savechar(uart, uart->uart_device->dlbl_fifo.rxfifo & 0xff);
    }

    /* invoke callback */
    if (device->rx_indicate != RT_NULL)
    {
        rt_size_t rx_length;

        /* get rx length */
        rx_length = uart->int_rx->read_index > uart->int_rx->save_index ?
            UART_RX_BUFFER_SIZE - uart->int_rx->read_index + uart->int_rx->save_index :
            uart->int_rx->save_index - uart->int_rx->read_index;

        device->rx_indicate(device, rx_length);
    }
}

/*@}*/
