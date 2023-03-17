/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-10-24     thread-liu        first version
 */

#include <board.h>
#include "drv_rs485.h"

#ifdef BSP_USING_RS485

#define RS485_OUT       rt_pin_write(BSP_RS485_RTS_PIN, PIN_HIGH)
#define RS485_IN        rt_pin_write(BSP_RS485_RTS_PIN, PIN_LOW)

static rt_device_t serial = {0};
static struct rt_semaphore rx_sem = {0};

/* uart send data callback function */
static rt_err_t rs485_output(rt_device_t dev, void * buffer)
{
    return RT_EOK;
}

/* uart receive data callback function */
static rt_err_t rs485_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

/* send string */
int rs485_send_data(char *tbuf, rt_uint16_t t_len)
{
    /* change rs485 mode */
    RS485_OUT;

    /* send data */
    rt_device_write(serial, 0, tbuf, t_len);

    /* change rs485 mode */
    RS485_IN;

    return RT_EOK;
}

static void rs485_thread_entry(void *parameter)
{
    char ch;

    while (1)
    {
        /* A byte of data is read from a serial port, and if it is not read, it waits for the received semaphore */
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }

        /* The data read through the serial port output dislocation */
        ch = ch + 1;

        /* send char */
        rs485_send_data(&ch, 1);
    }
}

/* rs485 rts pin init */
static int rs485_init(void)
{
    /* find uart device */
    serial = rt_device_find(RS485_UART_DEVICE_NAME);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", RS485_UART_DEVICE_NAME);
        return -RT_ERROR;
    }

    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);

    /* set receive data callback function */
    rt_device_set_rx_indicate(serial, rs485_input);

    /* set the send completion callback function */
    rt_device_set_tx_complete(serial, rs485_output);

    rt_pin_mode(BSP_RS485_RTS_PIN, PIN_MODE_OUTPUT);

    RS485_IN;

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* create rs485 thread */
    rt_thread_t thread = rt_thread_create("rs485", rs485_thread_entry, RT_NULL, 1024, 25, 10);

    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rs485_init);

#endif /* bsp_using_RS485 */
