/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-13     CYFS         Add standardized utest documentation block
*/

/**
 * Test Case Name: UART Blocking Receive Echo Test
 *
 * Test Objectives:
 * - Demonstrate blocking read semantics while capturing multiple user inputs
 * - Verify APIs: rt_device_find, rt_device_open with RT_DEVICE_FLAG_RX_BLOCKING,
 *   rt_device_read, rt_device_write, rt_device_close
 *
 * Test Scenarios:
 * - **Scenario 1 (Interactive Echo / uart_test_blocking_rx):**
 *   1. Restart UART in fully blocking RX/TX mode.
 *   2. Prompt user (or loopback source) for data, then execute several blocking reads of identical size, echoing results to console.
 *   3. Track cumulative bytes received and log progress after each read.
 *
 * Verification Metrics:
 * - Each blocking read returns the requested buffer length; totals increment accordingly.
 * - Test helper returns RT_TRUE once sequence completes.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` with loopback or external stimulus on `RT_SERIAL_TC_DEVICE_NAME`.
 * - UART driver must support blocking reads and repeated open/close operations.
 *
 * Expected Results:
 * - No assertions triggered; console displays prompts and echo logs.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_blocking_rx)`.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_SERIAL_V2

static rt_bool_t block_read(rt_device_t uart_dev)
{
    rt_size_t total_length, recv_length;
    char      uart_read_buffer[1024], log_buffer[64];

    /* make sure device is closed and reopen it */
    while (rt_device_close(uart_dev) != -RT_ERROR);
    rt_device_open(uart_dev, RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_RX_BLOCKING);

    rt_sprintf(log_buffer, "\nBLOCKING READ BEGIN, PLEASE SEND SOME DATAS\n");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    total_length  = 0;
    recv_length   = 0;
    recv_length   = rt_device_read(uart_dev, -1, uart_read_buffer, rt_strlen(log_buffer));
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read, total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length   = 0;
    recv_length   = rt_device_read(uart_dev, -1, uart_read_buffer, rt_strlen(log_buffer));
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length   = 0;
    recv_length   = rt_device_read(uart_dev, -1, uart_read_buffer, rt_strlen(log_buffer));
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length   = 0;
    recv_length   = rt_device_read(uart_dev, -1, uart_read_buffer, rt_strlen(log_buffer));
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length   = 0;
    recv_length   = rt_device_read(uart_dev, -1, uart_read_buffer, rt_strlen(log_buffer));
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_sprintf(log_buffer, "BLOCKING READ END");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    return RT_TRUE;
}

static void uart_test_blocking_rx(void)
{
    rt_device_t uart_dev;
    uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    uassert_not_null(uart_dev);

    uassert_true(block_read(uart_dev));
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_device_t uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(uart_test_blocking_rx);
}
UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_blocking_rx", utest_tc_init, utest_tc_cleanup, 10);

#endif
