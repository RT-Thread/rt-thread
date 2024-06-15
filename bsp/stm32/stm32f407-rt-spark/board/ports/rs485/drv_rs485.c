/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-10-24     thread-liu        first version
 * 2023-05-05     yuanjie           add test method
 */

#include <rtdevice.h>
#include <board.h>
#include <drv_gpio.h>
#include "drv_rs485.h"

#ifdef BSP_USING_RS485

#define RS485_OUT       rt_pin_write(BSP_RS485_RTS_PIN, PIN_HIGH)
#define RS485_IN        rt_pin_write(BSP_RS485_RTS_PIN, PIN_LOW)

rt_device_t rs485_serial = {0};
struct rt_semaphore rs485_rx_sem = {0};

/* uart send data callback function */
static rt_err_t rs485_output(rt_device_t dev, void * buffer)
{
    return RT_EOK;
}

/* uart receive data callback function */
static rt_err_t rs485_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rs485_rx_sem);

    return RT_EOK;
}

/* send string */
int rs485_send_data(char *tbuf, rt_uint16_t t_len)
{
    /* change rs485 mode */
    RS485_OUT;

    /* send data */
    rt_device_write(rs485_serial, 0, tbuf, t_len);

    /* change rs485 mode */
    RS485_IN;

    rt_kprintf("\nsend:");
    for(int i =0;i<t_len;i++)
    {
        rt_kprintf("%d:%x ",i,tbuf[i]);
    }
    return RT_EOK;
}

#ifndef BSP_USING_LED_MATRIX_RS485_DEMO
static void rs485_thread_entry(void *parameter)
{
    char ch;

    while (1)
    {
        /* A byte of data is read from a rs485_serial port, and if it is not read, it waits for the received semaphore */
        while (rt_device_read(rs485_serial, -1, &ch, 1) != 1)
        {
            rt_sem_take(&rs485_rx_sem, RT_WAITING_FOREVER);
        }
        // rt_kprintf("%c",ch);
    }
}
#endif

/* rs485 rts pin init */
int rs485_init(void)
{
    /* find uart device */
    rs485_serial = rt_device_find(RS485_UART_DEVICE_NAME);
    if (!rs485_serial)
    {
        rt_kprintf("find %s failed!\n", RS485_UART_DEVICE_NAME);
        return -RT_ERROR;
    }

    rt_device_open(rs485_serial, RT_DEVICE_FLAG_INT_RX);

    /* set receive data callback function */
    rt_device_set_rx_indicate(rs485_serial, rs485_input);

    /* set the send completion callback function */
    rt_device_set_tx_complete(rs485_serial, rs485_output);

    rt_pin_mode(BSP_RS485_RTS_PIN, PIN_MODE_OUTPUT);

    RS485_IN;

    rt_sem_init(&rs485_rx_sem, "rs485_rx_sem", 0, RT_IPC_FLAG_FIFO);
#ifndef BSP_USING_LED_MATRIX_RS485_DEMO
    /* create rs485 receive thread */
     rt_thread_t thread = rt_thread_create("rs485", rs485_thread_entry, RT_NULL, 1024, 25, 10);
#else
    extern void led_matrix_receieve_task(void *parameter);
    rt_thread_t thread = rt_thread_create("rs485", led_matrix_receieve_task, RT_NULL, 1024, 20, 10);
#endif

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
// INIT_DEVICE_EXPORT(rs485_init);

void rs485_test(int argc, void **argv)
{
    char *str;
    if (argc == 1)
    {
        rt_kprintf("-t  --Enter any keys to send.\n");
    }
    else if (argc == 3)
    {
        if (rt_strcmp(argv[1], "-t") == 0)
        {
            str = argv[2];
            rs485_send_data(str, rt_strnlen(str, 32));
        }
    }
}
MSH_CMD_EXPORT(rs485_test, test rs485 transmission);

#endif /* BSP_USING_RS485 */
