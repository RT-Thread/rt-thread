/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-07-22     kurisaw           first version
 */

#include <rtdevice.h>
#include <hal_data.h>
#include "drv_rs485.h"

#define DBG_TAG "drv.rs485"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#ifdef BSP_USING_RS485

#define RS485_OUT       rt_pin_write((rt_base_t)RS485_DE_PIN, PIN_HIGH)
#define RS485_IN        rt_pin_write((rt_base_t)RS485_DE_PIN, PIN_LOW)

static rt_device_t rs485_serial = RT_NULL;
static struct rt_semaphore rs485_rx_sem;
static struct rt_ringbuffer rs485_rx_rb;
static rt_uint8_t rs485_rx_buffer[RS485_RX_BUFFER_SIZE];

/* uart receive data callback function */
static rt_err_t rs485_input(rt_device_t dev, rt_size_t size)
{
    if (size > 0)
    {
        rt_uint8_t ch;
        while (rt_device_read(dev, 0, &ch, 1) == 1)
        {
            rt_ringbuffer_put_force(&rs485_rx_rb, &ch, 1);
        }
        rt_sem_release(&rs485_rx_sem);
    }
    return RT_EOK;
}

/* send data */
int rs485_send_data(const void *tbuf, rt_uint16_t t_len)
{
    RT_ASSERT(tbuf != RT_NULL);

    /* change rs485 mode to transmit */
    RS485_OUT;

    /* send data */
    rt_size_t sent = rt_device_write(rs485_serial, 0, tbuf, t_len);

    if (sent != t_len)
    {
        /* Transmission failed, switch back to receive mode */
        RS485_IN;
        return -RT_ERROR;
    }

    /* Note: We don't switch back to receive mode here -
       that will be done in the tx_complete callback (rs485_output) */

    LOG_I("send==>>");
    for (int i = 0; i < t_len; i++)
    {
        LOG_I("   %d:   %c ", i, ((rt_uint8_t *)tbuf)[i]);
    }
    RS485_IN;

    return RT_EOK;
}

#ifndef BSP_USING_LED_MATRIX_RS485_DEMO
static void rs485_thread_entry(void *parameter)
{
    rt_uint8_t ch;
    rt_size_t length;

    while (1)
    {
        /* Wait for data */
        rt_sem_take(&rs485_rx_sem, RT_WAITING_FOREVER);

        /* Process all available data in the ring buffer */
        while (length = rt_ringbuffer_get(&rs485_rx_rb, &ch, 1))
        {
            if (length == 1)
            {
                LOG_I("recv data:%c", ch);
            }
        }
    }
}
#endif

/* rs485 rts pin init */
int rs485_init(void)
{
    /* Initialize ring buffer */
    rt_ringbuffer_init(&rs485_rx_rb, rs485_rx_buffer, RS485_RX_BUFFER_SIZE);

    /* find uart device */
    rs485_serial = rt_device_find(RS485_UART_DEVICE_NAME);
    if (!rs485_serial)
    {
        LOG_E("find %s failed!", RS485_UART_DEVICE_NAME);
        return -RT_ERROR;
    }

    /* Open device in interrupt mode with DMA support if available */
    rt_device_open(rs485_serial, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX);

    /* set receive data callback function */
    rt_device_set_rx_indicate(rs485_serial, rs485_input);

    /* Initialize RTS pin */
    rt_pin_mode((rt_base_t)RS485_DE_PIN, PIN_MODE_OUTPUT);
    RS485_IN;

    /* Initialize semaphore */
    rt_sem_init(&rs485_rx_sem, "rs485_rx_sem", 0, RT_IPC_FLAG_FIFO);

    rt_thread_t thread = rt_thread_create("rs485", rs485_thread_entry, RT_NULL,
                                        1024, 25, 10);

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

void rs485_cmd(int argc, char **argv)
{
    if (argc == 1)
    {
        LOG_I("Usage:");
        LOG_I("rs485_cmd -t <message>  -- send message via RS485");
    }
    else if (argc == 3 && rt_strcmp(argv[1], "-t") == 0)
    {
        char *str = argv[2];
        rs485_send_data(str, rt_strnlen(str, 32));
    }

    return;
}
MSH_CMD_EXPORT(rs485_cmd, rs485 transmission cmd);

#endif /* BSP_USING_RS485 */
