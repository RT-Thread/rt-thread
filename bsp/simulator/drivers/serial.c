/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-02-05     Bernard      first version
 * 2009-10-25     Bernard      fix rt_serial_read bug when there is no data
 *                             in the buffer.
 * 2010-03-29     Bernard      cleanup code.
 * 2013-02-7      prife        rewrite for simulator
 */

#include <rthw.h>

#include "serial.h"
#include <stdio.h>

#if 0
static FILE *fp = RT_NULL;
#endif

/*@{*/
int seial_save_byte(unsigned char ch, struct serial_device * serial)
{
    /* save on rx buffer */
    rt_base_t level;
    struct rt_device * dev = RT_DEVICE(serial);
    /* disable interrupt */
    //暂时关闭中断，因为要操作uart数据结构
    level = rt_hw_interrupt_disable();

    /* save character */
    serial->serial_rx.rx_buffer[serial->serial_rx.save_index] = ch;
    serial->serial_rx.save_index ++;
    //下面的代码检查save_index是否已经到到缓冲区尾部，如果是则回转到头部，称为一个环形缓冲区
    if (serial->serial_rx.save_index >= SERIAL_RX_BUFFER_SIZE)
        serial->serial_rx.save_index = 0;

    //这种情况表示反转后的save_index追上了read_index，则增大read_index，丢弃一个旧的数据
    /* if the next position is read index, discard this 'read char' */
    if (serial->serial_rx.save_index == serial->serial_rx.read_index)
    {
        serial->serial_rx.read_index ++;
        if (serial->serial_rx.read_index >= SERIAL_RX_BUFFER_SIZE)
            serial->serial_rx.read_index = 0;
    }

    /* enable interrupt */
    //uart数据结构已经操作完成，重新使能中断
    rt_hw_interrupt_enable(level);

    /* invoke callback */
    if (dev->rx_indicate != RT_NULL)
    {
        rt_size_t rx_length;

        /* get rx length */
        rx_length = serial->serial_rx.read_index > serial->serial_rx.save_index ?
            SERIAL_RX_BUFFER_SIZE - serial->serial_rx.read_index + serial->serial_rx.save_index :
        serial->serial_rx.save_index - serial->serial_rx.read_index;

        dev->rx_indicate(dev, rx_length);
    }
    return 0;
}

/* RT-Thread Device Interface */
/**
 * This function initializes serial
 */
static rt_err_t rt_serial_init(rt_device_t dev)
{
    struct serial_device * serial = SERIAL_DEVICE(dev);
    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            rt_memset(serial->serial_rx.rx_buffer, 0,
                      sizeof(serial->serial_rx.rx_buffer));
            serial->serial_rx.read_index = 0;
            serial->serial_rx.save_index = 0;
        }

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }
    return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
    return RT_EOK;
}
static rt_size_t rt_serial_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint8_t *ptr;
    rt_err_t err_code;
    struct serial_device * serial = SERIAL_DEVICE(dev);

    ptr = buffer;
    err_code = RT_EOK;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* interrupt mode Rx */
        while (size)
        {
            rt_base_t level;

            /* disable interrupt */
            level = rt_hw_interrupt_disable();

            if (serial->serial_rx.read_index != serial->serial_rx.save_index)
            {
                /* read a character */
                *ptr++ = serial->serial_rx.rx_buffer[serial->serial_rx.read_index];
                size--;

                /* move to next position */
                serial->serial_rx.read_index ++;
                if (serial->serial_rx.read_index >= SERIAL_RX_BUFFER_SIZE)
                    serial->serial_rx.read_index = 0;
            }
            else
            {
                /* set error code */
                err_code = -RT_EEMPTY;

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
                break;
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);
        }
    }


    /* set error code */
    rt_set_errno(err_code);
    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_size_t rt_serial_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    int level;
#if 0
    if (fp == NULL)
        fp = fopen("log.txt", "wb+");

    if (fp != NULL)
        fwrite(buffer, size, 1, fp);
#endif

    level = rt_hw_interrupt_disable();
    fwrite(buffer, size, 1, stdout);
	fflush(stdout);
    rt_hw_interrupt_enable(level);
    return size;
}

static rt_err_t rt_serial_control(rt_device_t dev, rt_uint8_t cmd, void *args)
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
rt_err_t rt_hw_serial_register(rt_device_t device, const char *name, rt_uint32_t flag)
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
    device->user_data       = RT_NULL;

    /* register a character device */
    return rt_device_register(device, name, (rt_uint16_t)(RT_DEVICE_FLAG_RDWR | flag));
}

rt_err_t rt_hw_serial_init(struct serial_device * serial, char * name)
{
    return rt_hw_serial_register(RT_DEVICE(serial), name,
                                 RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
}
