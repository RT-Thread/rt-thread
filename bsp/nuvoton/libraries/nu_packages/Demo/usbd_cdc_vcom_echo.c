/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-1-10       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(RT_USB_DEVICE_CDC) && (defined(BSP_USING_USBD) || defined(BSP_USING_HSUSBD))

static struct rt_semaphore rx_sem;

static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_err_t result = 0;

    result = rt_sem_release(&rx_sem);
    RT_ASSERT(result == RT_EOK);

    return RT_EOK;
}

static void serial_thread_entry(void *parameter)
{
    rt_device_t serial = (rt_device_t)parameter;
    char ch;
    char szStr[64];
    while (1)
    {
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            if (rt_sem_take(&rx_sem, 3 * RT_TICK_PER_SECOND) == -RT_ETIMEOUT)
            {
                /* output current tick */
                rt_snprintf(szStr, sizeof(szStr), "%d\n", rt_tick_get());
                rt_device_write(serial, 0, &szStr[0], rt_strlen(szStr));
                continue;
            }
        }
        rt_device_write(serial, 0, &ch, 1);
    }
}

static int vcom_echo_init(void)
{
    rt_err_t result = 0;
    rt_thread_t thread;
    rt_device_t serial;

    serial = rt_device_find("vcom");
    if (!serial)
    {
        rt_kprintf("find failed!\n");
        return RT_ERROR;
    }
    result = rt_device_init(serial);
    if (result)
    {
        rt_kprintf("init failed!\n");
        return -1;
    }
    result = rt_device_open(serial, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX/* | RT_DEVICE_FLAG_DMA_TX */);
    if (result)
    {
        rt_kprintf("open failed!\n");
        return -1;
    }

    result = rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(result == RT_EOK);

    result = rt_device_set_rx_indicate(serial, uart_input);
    RT_ASSERT(result == RT_EOK);

    thread = rt_thread_create("serial", serial_thread_entry, (void *)serial, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        result = rt_thread_startup(thread);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_APP_EXPORT(vcom_echo_init);

#endif
