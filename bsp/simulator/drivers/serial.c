/*
******************************************************************************
* By   : parai
* email:parai@foxmail.com
* virtual serial driver
******************************************************************************
*/

#include <rthw.h>
#include <rtthread.h>

#define _DEBUG_SERIAL 0
#include "serial.h"
#include <stdio.h>
struct rt_device serial_device;
extern struct serial_int_rx serial_rx;
static FILE *fp = RT_NULL;

/*@{*/

/* RT-Thread Device Interface */
/**
 * This function initializes serial
 */
static rt_err_t rt_serial_init(rt_device_t dev)
{
    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            rt_memset(serial_rx.rx_buffer, 0,
                      sizeof(serial_rx.rx_buffer));
            serial_rx.read_index = 0;
            serial_rx.save_index = 0;
        }

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }
    return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
#if _DEBUG_SERIAL==1
    printf("in rt_serial_open()\n");
#endif
    return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
#if _DEBUG_SERIAL==1
    printf("in rt_serial_close()\n");
#endif
    return RT_EOK;
}
static rt_size_t rt_serial_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint8_t *ptr;
    rt_err_t err_code;

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

            if (serial_rx.read_index != serial_rx.save_index)
            {
                /* read a character */
                *ptr++ = serial_rx.rx_buffer[serial_rx.read_index];
                size--;

                /* move to next position */
                serial_rx.read_index ++;
                if (serial_rx.read_index >= SERIAL_RX_BUFFER_SIZE)
                    serial_rx.read_index = 0;
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
#if _DEBUG_SERIAL==1
    printf("in rt_serial_write()\n");
#endif
    if (fp == NULL)
        fp = fopen("log.txt", "wb+");

    if (fp != NULL)
        fwrite(buffer, size, 1, fp);

    printf("%s", (char *)buffer);
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
static rt_err_t rt_hw_serial_register(rt_device_t device, const char *name, rt_uint32_t flag)
{
    RT_ASSERT(device != RT_NULL);
#if _DEBUG_SERIAL==1
    printf("in rt_serial_register()\n");
#endif
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

rt_err_t rt_hw_serial_init(void)
{
    return rt_hw_serial_register(&serial_device, RT_CONSOLE_DEVICE_NAME,
                                 RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
}
