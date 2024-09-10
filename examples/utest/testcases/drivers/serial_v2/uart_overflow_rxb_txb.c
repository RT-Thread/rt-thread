/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>

#define DBG_LVL DBG_LOG

#define TC_UART_DEVICE_NAME "uart2"
#define TC_UART_SEND_TIMES  100


#ifdef UTEST_SERIAL_TC

static struct rt_serial_device *serial;
static rt_uint8_t               uart_over_flag = RT_FALSE;
static rt_bool_t                uart_result    = RT_TRUE;

static rt_err_t uart_find(void)
{
    serial = (struct rt_serial_device *)rt_device_find(TC_UART_DEVICE_NAME);

    if (serial == RT_NULL)
    {
        LOG_E("find %s device failed!\n", TC_UART_DEVICE_NAME);
        return -RT_ERROR;
    }

    return RT_EOK;
}


static void uart_send_entry(void *parameter)
{
    rt_uint16_t send_len;
    rt_uint8_t *uart_write_buffer = RT_NULL;
    rt_uint32_t i                 = 0;
    send_len                      = *(rt_uint16_t *)parameter;

    /* assign send buffer */
    uart_write_buffer = (rt_uint8_t *)rt_malloc(send_len);
    if (uart_write_buffer == RT_NULL)
    {
        LOG_E("Without spare memory for uart dma!");
        uart_result = RT_FALSE;
        return;
    }

    rt_memset(uart_write_buffer, 0, send_len);

    for (i = 0; i < send_len; i++)
    {
        uart_write_buffer[i] = (rt_uint8_t)i;
    }
    /* send buffer */
    if (rt_device_write(&serial->parent, 0, uart_write_buffer, send_len) != send_len)
    {
        LOG_E("device write failed\r\n");
    }
    rt_free(uart_write_buffer);
}

static void uart_rec_entry(void *parameter)
{
    rt_uint16_t rev_len;
    rt_uint8_t *ch;
    rt_int32_t  cnt, i;
    rev_len = *(rt_uint16_t *)parameter;
    ch      = (rt_uint8_t *)rt_malloc(sizeof(rt_uint8_t) * (rev_len + 1));

    while (1)
    {
        cnt = rt_device_read(&serial->parent, 0, (void *)ch, BSP_UART2_RX_BUFSIZE);
        if (cnt != BSP_UART2_RX_BUFSIZE)
        {
            uart_result = RT_FALSE;
            rt_free(ch);
            return;
        }

        for (i = cnt - 1; i >= 0; i--)
        {
            if (ch[i] != ((rev_len - (cnt - i)) % 256))
            {
                LOG_E("Read Different data2 -> former data: %x, current data: %x.", ch[i], (rev_len - (cnt - i)) % 256);
                uart_result = RT_FALSE;
                rt_free(ch);
                return;
            }
        }

        break;
    }
    rt_free(ch);
    uart_over_flag = RT_TRUE;
}

static rt_err_t uart_api(rt_uint16_t length)
{
    rt_thread_t thread_send = RT_NULL;
    rt_thread_t thread_recv = RT_NULL;
    rt_err_t    result      = RT_EOK;
    uart_over_flag          = RT_FALSE;

    result = uart_find();
    if (result != RT_EOK)
    {
        return -RT_ERROR;
    }

    /* Reinitialize */
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate               = BAUD_RATE_115200;
    config.rx_bufsz                = BSP_UART2_RX_BUFSIZE;
    config.tx_bufsz                = BSP_UART2_TX_BUFSIZE;
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);

    if (result != RT_EOK)
    {
        LOG_E("Open uart device failed.");
        uart_result = RT_FALSE;
        return -RT_ERROR;
    }

    thread_send = rt_thread_create("uart_send", uart_send_entry, &length, 2048, RT_THREAD_PRIORITY_MAX - 4, 10);
    thread_recv = rt_thread_create("uart_recv", uart_rec_entry, &length, 2048, RT_THREAD_PRIORITY_MAX - 5, 10);

    if ((thread_send != RT_NULL) && (thread_recv != RT_NULL))
    {
        rt_thread_startup(thread_send);
        rt_thread_mdelay(length / 11 + 10);
        rt_thread_startup(thread_recv);
    }
    else
    {
        result = -RT_ERROR;
        goto __exit;
    }

    while (1)
    {
        if (uart_result != RT_TRUE)
        {
            LOG_E("The test for uart dma is failure.");
            result = -RT_ERROR;
            goto __exit;
        }
        if (uart_over_flag == RT_TRUE)
        {
            goto __exit;
        }
        /* waiting for test over */
        rt_thread_mdelay(5);
    }
__exit:
    rt_device_close(&serial->parent);
    return result;
}

static void tc_uart_api(void)
{
    rt_uint32_t times = 0;
    rt_uint16_t num   = 0;
    rt_uint32_t i     = 0;
    for (i = 1; i < 10; i++)
    {
        if (uart_api(BSP_UART2_TX_BUFSIZE * i + i % 2) == RT_EOK)
            LOG_I("data_lens [%4d], it is correct to read and write data. [%d] times testing.", BSP_UART2_TX_BUFSIZE * i + i % 2, ++times);
        else
        {
            LOG_E("uart test error");
            goto __exit;
        }
    }

    for (i = 1; i < 10; i++)
    {
        if (uart_api(BSP_UART2_RX_BUFSIZE * i + i % 2) == RT_EOK)
            LOG_I("data_lens [%4d], it is correct to read and write data. [%d] times testing.", BSP_UART2_RX_BUFSIZE * i + i % 2, ++times);
        else
        {
            LOG_E("uart test error");
            goto __exit;
        }
    }

    while (TC_UART_SEND_TIMES - times)
    {
        num = (rand() % BSP_UART2_RX_BUFSIZE) + 1;
        if (uart_api(num + BSP_UART2_RX_BUFSIZE) == RT_EOK)
            LOG_I("data_lens [%3d], it is correct to read and write data. [%d] times testing.", num, ++times);
        else
        {
            LOG_E("uart test error");
            break;
        }
    }

__exit:
    uassert_true(uart_result == RT_TRUE);
}

static rt_err_t utest_tc_init(void)
{
    LOG_I("UART TEST: Please connect Tx and Rx directly for self testing.");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    uart_result          = RT_TRUE;
    uart_over_flag       = RT_FALSE;
    rt_device_t uart_dev = rt_device_find(TC_UART_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "testcases.drivers.uart_overflow_rxb_txb", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
