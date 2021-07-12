/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-16     KyleChan     the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>

#define TC_UART_DEVICE_NAME "uart2"
#define TC_UART_SEND_TIMES 100


#ifdef UTEST_SERIAL_TC

#define TEST_UART_NAME            TC_UART_DEVICE_NAME

static struct rt_serial_device *serial;
static rt_sem_t tx_sem;
static rt_sem_t rx_sem;
static rt_uint8_t uart_over_flag;
static rt_bool_t uart_result = RT_TRUE;

static rt_err_t uart_find(void)
{
    serial = (struct rt_serial_device *)rt_device_find(TEST_UART_NAME);

    if (serial == RT_NULL)
    {
        LOG_E("find %s device failed!\n", TEST_UART_NAME);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t uart_tx_completion(rt_device_t device, void *buffer)
{
    rt_sem_release(tx_sem);
    return RT_EOK;
}

static rt_err_t uart_rx_indicate(rt_device_t device, rt_size_t size)
{
    rt_sem_release(rx_sem);
    return RT_EOK;
}

static void uart_send_entry(void *parameter)
{
    rt_uint8_t *uart_write_buffer;
    rt_uint16_t send_len, len = 0;
    rt_err_t result;

    rt_uint32_t i = 0;
    send_len = *(rt_uint16_t *)parameter;
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
    while (send_len - len)
    {
        len += rt_device_write(&serial->parent, 0, uart_write_buffer + len, send_len - len);
        result = rt_sem_take(tx_sem, RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            LOG_E("take sem err in send.");
        }
    }
    rt_free(uart_write_buffer);

}

static void uart_rec_entry(void *parameter)
{
    rt_uint16_t rev_len;

    rev_len = *(rt_uint16_t *)parameter;
    rt_uint8_t *ch;
    ch = (rt_uint8_t *)rt_calloc(1, sizeof(rt_uint8_t) * (rev_len + 1));
    rt_int32_t cnt, i;
    rt_uint8_t last_old_data;
    rt_bool_t fisrt_flag = RT_TRUE;
    rt_uint32_t all_receive_length = 0;

    while (1)
    {
        rt_err_t result;

        result = rt_sem_take(rx_sem, RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            LOG_E("take sem err in recv.");
        }

        cnt = rt_device_read(&serial->parent, 0, (void *)ch, rev_len);
        if (cnt == 0)
        {
            continue;
        }

        if (fisrt_flag != RT_TRUE)
        {
            if ((rt_uint8_t)(last_old_data + 1) != ch[0])
            {
                LOG_E("_Read Different data -> former data: %x, current data: %x.", last_old_data, ch[0]);
                uart_result = RT_FALSE;
                rt_free(ch);
                return;
            }
        }
        else
        {
            fisrt_flag = RT_FALSE;
        }

        for (i = 0; i < cnt - 1; i++)
        {
            if ((rt_uint8_t)(ch[i] + 1) != ch[i + 1])
            {
                LOG_E("Read Different data -> former data: %x, current data: %x.", ch[i], ch[i + 1]);

                uart_result = RT_FALSE;
                rt_free(ch);
                return;
            }
        }
        all_receive_length += cnt;
        if (all_receive_length >= rev_len)
            break;
        else
            last_old_data = ch[cnt - 1];
    }
    rt_free(ch);
    uart_over_flag = RT_TRUE;
}

static rt_err_t uart_api(rt_uint16_t test_buf)
{
    rt_thread_t thread_send = RT_NULL;
    rt_thread_t thread_recv = RT_NULL;
    rt_err_t result = RT_EOK;
    uart_over_flag = RT_FALSE;

    result = uart_find();
    if (result != RT_EOK)
    {
        return -RT_ERROR;
    }

    rx_sem = rt_sem_create("rx_sem", 0, RT_IPC_FLAG_PRIO);
    if (rx_sem == RT_NULL)
    {
        LOG_E("Init rx_sem failed.");
        uart_result = RT_FALSE;
        return -RT_ERROR;
    }

    tx_sem = rt_sem_create("tx_sem", 0, RT_IPC_FLAG_PRIO);
    if (tx_sem == RT_NULL)
    {
        LOG_E("Init tx_sem failed.");
        uart_result = RT_FALSE;
        return -RT_ERROR;
    }

    /* reinitialize */
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;
    config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING);

    if (result != RT_EOK)
    {
        LOG_E("Open uart device failed.");
        uart_result = RT_FALSE;
        return -RT_ERROR;
    }

    /* set receive callback function */
    result = rt_device_set_tx_complete(&serial->parent, uart_tx_completion);
    if (result != RT_EOK)
    {
        goto __exit;
    }

    result = rt_device_set_rx_indicate(&serial->parent, uart_rx_indicate);
    if (result != RT_EOK)
    {
        goto __exit;
    }

    thread_recv = rt_thread_create("uart_recv", uart_rec_entry, &test_buf, 1024, RT_THREAD_PRIORITY_MAX - 5, 10);
    thread_send = rt_thread_create("uart_send", uart_send_entry, &test_buf, 1024, RT_THREAD_PRIORITY_MAX - 4, 10);

    if (thread_send != RT_NULL && thread_recv != RT_NULL)
    {
        rt_thread_startup(thread_recv);
        rt_thread_startup(thread_send);
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
    if (tx_sem)
        rt_sem_delete(tx_sem);

    if (rx_sem)
        rt_sem_delete(rx_sem);

    rt_device_close(&serial->parent);
    return result;
}

static void tc_uart_api(void)
{
    rt_uint32_t times = 0;
    rt_uint16_t num = 0;
    while (TC_UART_SEND_TIMES - times)
    {
        num = (rand() % 1000) + 1;
        if(uart_api(num) == RT_EOK)
           LOG_I("data_lens [%3d], it is correct to read and write data. [%d] times testing.", num, ++times);
        else
        {
            LOG_E("uart test error");
            break;
        }
    }
    uassert_true(uart_over_flag == RT_TRUE);
}

static rt_err_t utest_tc_init(void)
{
    LOG_I("UART TEST: Please connect Tx and Rx directly for self testing.");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    tx_sem = RT_NULL;
    uart_result = RT_TRUE;
    uart_over_flag = RT_FALSE;

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "testcases.drivers.uart_rxnb_txnb", utest_tc_init, utest_tc_cleanup, 30);

#endif
