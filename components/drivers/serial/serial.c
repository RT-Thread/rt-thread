/*
 * File      : serial.c
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
 * 2006-03-13     bernard      first version
 * 2012-05-15     lgnq         modified according bernard's implementation.
 * 2012-05-28     bernard      code cleanup
 * 2012-11-23     bernard      fix compiler warning.
 * 2013-02-20     bernard      use RT_SERIAL_RB_BUFSZ to define
 *                             the size of ring buffer.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

rt_inline void serial_ringbuffer_init(struct serial_ringbuffer *rbuffer)
{
    rt_memset(rbuffer->buffer, 0, sizeof(rbuffer->buffer));
    rbuffer->put_index = 0;
    rbuffer->get_index = 0;
}

rt_inline void serial_ringbuffer_putc(struct serial_ringbuffer *rbuffer,
                                      char                      ch)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rbuffer->buffer[rbuffer->put_index] = ch;
    rbuffer->put_index = (rbuffer->put_index + 1) & (RT_SERIAL_RB_BUFSZ - 1);

    /* if the next position is read index, discard this 'read char' */
    if (rbuffer->put_index == rbuffer->get_index)
    {
        rbuffer->get_index = (rbuffer->get_index + 1) & (RT_SERIAL_RB_BUFSZ - 1);
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

rt_inline int serial_ringbuffer_putchar(struct serial_ringbuffer *rbuffer,
                                        char                      ch)
{
    rt_base_t level;
    rt_uint16_t next_index;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    next_index = (rbuffer->put_index + 1) & (RT_SERIAL_RB_BUFSZ - 1);
    if (next_index != rbuffer->get_index)
    {
        rbuffer->buffer[rbuffer->put_index] = ch;
        rbuffer->put_index = next_index;
    }
    else
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        return -1;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return 1;
}

rt_inline int serial_ringbuffer_getc(struct serial_ringbuffer *rbuffer)
{
    int ch;
    rt_base_t level;

    ch = -1;
    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    if (rbuffer->get_index != rbuffer->put_index)
    {
        ch = rbuffer->buffer[rbuffer->get_index];
        rbuffer->get_index = (rbuffer->get_index + 1) & (RT_SERIAL_RB_BUFSZ - 1);
    }
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return ch;
}

rt_inline rt_uint32_t serial_ringbuffer_size(struct serial_ringbuffer *rbuffer)
{
    rt_uint32_t size;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    size = (rbuffer->put_index - rbuffer->get_index) & (RT_SERIAL_RB_BUFSZ - 1);
    rt_hw_interrupt_enable(level);

    return size;
}

/* RT-Thread Device Interface */

/*
 * This function initializes serial
 */
static rt_err_t rt_serial_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        /* apply configuration */
        if (serial->ops->configure)
            result = serial->ops->configure(serial, &serial->config);

        if (result != RT_EOK)
            return result;

        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
            serial_ringbuffer_init(serial->int_rx);

        if (dev->flag & RT_DEVICE_FLAG_INT_TX)
        {
			/* not supported yet */
			/*
            serial->ops->control(serial, RT_DEVICE_CTRL_SET_INT, (void *)RT_NULL);
            serial_ringbuffer_init(serial->int_tx);
            serial->int_sending_flag = RT_FALSE;
			*/
        }

        if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
        {
            serial->dma_flag = RT_FALSE;
            
            /* init data queue */
            rt_data_queue_init(&(serial->tx_dq), RT_SERIAL_TX_DATAQUEUE_SIZE,
                               RT_SERIAL_TX_DATAQUEUE_LWM, RT_NULL);
        }

        /* set activated */
        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }

    return result;
}

static rt_err_t rt_serial_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct rt_serial_device *serial;
    rt_uint32_t int_flags = 0;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        int_flags = RT_SERIAL_RX_INT;
    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
        int_flags |= RT_SERIAL_TX_INT;

    if (int_flags)
    {
        serial->ops->control(serial, RT_DEVICE_CTRL_SET_INT, (void *)int_flags);
    }

    return RT_EOK;
}

static rt_err_t rt_serial_close(struct rt_device *dev)
{
    struct rt_serial_device *serial;
    rt_uint32_t int_flags = 0;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        int_flags = RT_SERIAL_RX_INT;
    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
        int_flags |= RT_SERIAL_TX_INT;

    if (int_flags)
    {
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void *)int_flags);
    }

    return RT_EOK;
}

static rt_size_t rt_serial_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)
{
    rt_uint8_t *ptr;
    rt_uint32_t read_nbytes;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);

    if (size == 0)
        return 0;

    serial = (struct rt_serial_device *)dev;

    ptr = (rt_uint8_t *)buffer;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* interrupt mode Rx */
        while (size)
        {
            int ch;

            ch = serial_ringbuffer_getc(serial->int_rx);
            if (ch == -1)
                break;

            *ptr = ch & 0xff;
            ptr ++;
            size --;
        }
    }
    else
    {
        /* polling mode */
        while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
        {
            *ptr = serial->ops->getc(serial);
            ptr ++;
        }
    }

    read_nbytes = (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    /* set error code */
    if (read_nbytes == 0)
    {
        rt_set_errno(-RT_EEMPTY);
    }

    return read_nbytes;
}

static rt_size_t rt_serial_write(struct rt_device *dev,
                                 rt_off_t          pos,
                                 const void       *buffer,
                                 rt_size_t         size)
{
    rt_uint8_t *ptr;
    rt_size_t write_nbytes = 0;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);

    if (size == 0)
        return 0;

    serial = (struct rt_serial_device *)dev;

    ptr = (rt_uint8_t*)buffer;

    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* warning: data will be discarded if buffer is full */
        while (size)
        {
            if (serial_ringbuffer_putchar(serial->int_tx, *ptr) != -1)
            {
                ptr ++;
                size --;
            }
            else
                break;
        }
    }
    else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
    {
        rt_base_t level;
        rt_err_t result;
        
        RT_ASSERT(0 == (dev->flag & RT_DEVICE_FLAG_STREAM));

        result = rt_data_queue_push(&(serial->tx_dq), buffer, size, 20); 
        if (result == RT_EOK)
        {
            level = rt_hw_interrupt_disable();
            if (serial->dma_flag == RT_FALSE)
            {
                serial->dma_flag = RT_TRUE;
                rt_hw_interrupt_enable(level);
                serial->ops->dma_transmit(serial, buffer, size);
            }
            else
                rt_hw_interrupt_enable(level);

            return size;
        }
        else
        {
            rt_set_errno(result);

            return 0;
        }
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
                serial->ops->putc(serial, '\r');
            }

            serial->ops->putc(serial, *ptr);

            ++ ptr;
            -- size;
        }
    }

    write_nbytes = (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    if (write_nbytes == 0)
    {
        rt_set_errno(-RT_EFULL);
    }

    return write_nbytes;
}

static rt_err_t rt_serial_control(struct rt_device *dev,
                                  rt_uint8_t        cmd,
                                  void             *args)
{
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

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

    case RT_DEVICE_CTRL_CONFIG:
        /* configure device */
        serial->ops->configure(serial, (struct serial_configure *)args);
        break;
    }

    return RT_EOK;
}

/*
 * serial register
 */
rt_err_t rt_hw_serial_register(struct rt_serial_device *serial,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    struct rt_device *device;
    RT_ASSERT(serial != RT_NULL);

    device = &(serial->parent);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_serial_init;
    device->open        = rt_serial_open;
    device->close       = rt_serial_close;
    device->read        = rt_serial_read;
    device->write       = rt_serial_write;
    device->control     = rt_serial_control;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

/* ISR for serial interrupt */
void rt_hw_serial_isr(struct rt_serial_device *serial)
{
    int ch = -1;

    /* interrupt mode receive */
    RT_ASSERT(serial->parent.flag & RT_DEVICE_FLAG_INT_RX);

    while (1)
    {
        ch = serial->ops->getc(serial);
        if (ch == -1)
            break;

        serial_ringbuffer_putc(serial->int_rx, ch);
    }

    /* invoke callback */
    if (serial->parent.rx_indicate != RT_NULL)
    {
        rt_size_t rx_length;

        /* get rx length */
        rx_length = serial_ringbuffer_size(serial->int_rx);
        serial->parent.rx_indicate(&serial->parent, rx_length);
    }
}

/*
 * ISR for DMA mode Tx
 */
void rt_hw_serial_dma_tx_isr(struct rt_serial_device *serial)
{
    const void *data_ptr;
    rt_size_t data_size;
    const void *last_data_ptr;

    rt_data_queue_pop(&(serial->tx_dq), &last_data_ptr, &data_size, 0);
    if (RT_EOK == rt_data_queue_peak(&(serial->tx_dq), &data_ptr, &data_size))
    {
        /* transmit next data node */
         serial->ops->dma_transmit(serial, data_ptr, data_size);
    }
    else
    {
        serial->dma_flag = RT_FALSE;
    }

    /* invoke callback */
    if (serial->parent.tx_complete != RT_NULL)
    {
        serial->parent.tx_complete(&serial->parent, (void*)last_data_ptr);
    }
}
