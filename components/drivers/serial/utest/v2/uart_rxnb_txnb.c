/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-16     KyleChan     the first version
 * 2025-11-13     CYFS         Add standardized utest documentation block
*/

/**
 * Test Case Name: UART Non-Blocking RX & TX Integration Test
 *
 * Test Objectives:
 * - Validate fully non-blocking UART workflow leveraging TX completion and RX indication callbacks
 * - Verify APIs: rt_device_find, rt_device_control(RT_DEVICE_CTRL_CONFIG / RT_SERIAL_CTRL_SET_RX_TIMEOUT),
 *   rt_device_open with RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING,
 *   rt_device_set_rx_indicate, rt_device_set_tx_complete, rt_device_read, rt_device_write, rt_sem APIs
 *
 * Test Scenarios:
 * - **Scenario 1 (Callback-Synchronized Duplex Transfer / tc_uart_api):**
 *   1. Configure UART buffers (optional DMA ping buffer) and create paired RX/TX semaphores.
 *   2. Register RX indication and TX completion callbacks to release semaphores on asynchronous events.
 *   3. Launch sender/receiver threads for deterministic and random payload sizes; sender fragments writes, waiting on TX semaphore, while receiver waits on RX semaphore before draining data.
 *   4. Verify data ordering continuously and stop once requested byte count satisfied per iteration.
 *
 * Verification Metrics:
 * - Received bytes maintain sequential increments; `uart_result` never flips to RT_FALSE.
 * - Semaphore waits succeed; non-blocking read/write calls progress without deadlock.
 * - UART handles close cleanly; semaphores deleted during cleanup.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2`, loopback on `RT_SERIAL_TC_DEVICE_NAME`, and callback-capable UART driver.
 * - Adequate heap for buffers, semaphores, and two 1 KB thread stacks.
 *
 * Expected Results:
 * - Unit test completes without assertions; logs reflect pass counts across length sweep.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_rxnb_txnb)`.
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdlib.h>


#ifdef RT_UTEST_SERIAL_V2

static struct rt_serial_device *serial;
static rt_sem_t                 tx_sem;
static rt_sem_t                 rx_sem;
static rt_uint8_t               uart_over_flag;
static rt_bool_t                uart_result = RT_TRUE;

static rt_err_t uart_find(void)
{
    serial = (struct rt_serial_device *)rt_device_find(RT_SERIAL_TC_DEVICE_NAME);

    if (serial == RT_NULL)
    {
        LOG_E("find %s device failed!\n", RT_SERIAL_TC_DEVICE_NAME);
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
    rt_err_t    result;

    rt_uint32_t i = 0;
    send_len      = *(rt_uint16_t *)parameter;
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
        len    += rt_device_write(&serial->parent, 0, uart_write_buffer + len, send_len - len);
        result  = rt_sem_take(tx_sem, RT_WAITING_FOREVER);
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
    rt_uint8_t *uart_write_buffer;
    uart_write_buffer = (rt_uint8_t *)rt_calloc(1, rev_len + 1);
    rt_int32_t  cnt, i;
    rt_uint8_t  last_old_data;
    rt_bool_t   fisrt_flag         = RT_TRUE;
    rt_uint32_t all_receive_length = 0;

    while (1)
    {
        rt_err_t result;

        result = rt_sem_take(rx_sem, RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            LOG_E("take sem err in recv.");
        }

        cnt = rt_device_read(&serial->parent, 0, (void *)uart_write_buffer, rev_len);
        if (cnt == 0)
        {
            continue;
        }

        if (fisrt_flag != RT_TRUE)
        {
            if ((rt_uint8_t)(last_old_data + 1) != uart_write_buffer[0])
            {
                LOG_E("_Read Different data -> former data: %x, current data: %x.", last_old_data, uart_write_buffer[0]);
                uart_result = RT_FALSE;
                rt_free(uart_write_buffer);
                return;
            }
        }
        else
        {
            fisrt_flag = RT_FALSE;
        }

        for (i = 0; i < cnt - 1; i++)
        {
            if ((rt_uint8_t)(uart_write_buffer[i] + 1) != uart_write_buffer[i + 1])
            {
                LOG_E("Read Different data -> former data: %x, current data: %x.", uart_write_buffer[i], uart_write_buffer[i + 1]);

                uart_result = RT_FALSE;
                rt_free(uart_write_buffer);
                return;
            }
        }
        all_receive_length += cnt;
        if (all_receive_length >= rev_len)
            break;
        else
            last_old_data = uart_write_buffer[cnt - 1];
    }
    rt_free(uart_write_buffer);
    uart_over_flag = RT_TRUE;
}

static rt_err_t uart_api(rt_uint16_t test_buf)
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
    config.baud_rate               = BAUD_RATE_115200;
    config.rx_bufsz                = RT_SERIAL_TC_RXBUF_SIZE;
    config.tx_bufsz                = RT_SERIAL_TC_TXBUF_SIZE;

#ifdef RT_SERIAL_USING_DMA
    config.dma_ping_bufsz = RT_SERIAL_TC_RXBUF_SIZE / 2;
#endif
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONFIG, &config);

    result = rt_device_open(&serial->parent, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING);
    if (result != RT_EOK)
    {
        LOG_E("Open uart device failed.");
        uart_result = RT_FALSE;
        return -RT_ERROR;
    }

    rt_int32_t timeout = 5000;
    rt_device_control(&serial->parent, RT_SERIAL_CTRL_SET_RX_TIMEOUT, (void *)&timeout);

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
    rt_thread_mdelay(5);
    uart_over_flag = RT_FALSE;
    return result;
}

static void tc_uart_api(void)
{
    rt_uint32_t count = 0;
    rt_uint16_t num   = 0;
    rt_uint32_t i     = 0;
    for (i = 1; i < 10; i++)
    {
        if (uart_api(RT_SERIAL_TC_TXBUF_SIZE * i + i % 2) == RT_EOK)
            LOG_I("data_lens [%4d], it is correct to read and write data. [%d] count testing.", RT_SERIAL_TC_TXBUF_SIZE * i + i % 2, ++count);
        else
        {
            LOG_E("uart test error");
            goto __exit;
        }
    }

    for (i = 1; i < 10; i++)
    {
        if (uart_api(RT_SERIAL_TC_RXBUF_SIZE * i + i % 2) == RT_EOK)
            LOG_I("data_lens [%4d], it is correct to read and write data. [%d] count testing.", RT_SERIAL_TC_RXBUF_SIZE * i + i % 2, ++count);
        else
        {
            LOG_E("uart test error");
            goto __exit;
        }
    }

    srand(rt_tick_get());
    while (RT_SERIAL_TC_SEND_ITERATIONS - count)
    {
        num = (rand() % 1000) + 1;
        if (uart_api(num) == RT_EOK)
            LOG_I("data_lens [%4d], it is correct to read and write data. [%d] count testing.", num, ++count);
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
    tx_sem               = RT_NULL;
    uart_result          = RT_TRUE;
    uart_over_flag       = RT_FALSE;
    rt_device_t uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_rxnb_txnb", utest_tc_init, utest_tc_cleanup, 30);

#endif
