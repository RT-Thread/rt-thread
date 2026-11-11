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
 * Test Case Name: UART Non-Blocking Receive Echo Test
 *
 * Test Objectives:
 * - Demonstrate non-blocking receive behavior paired with blocking transmit output
 * - Verify APIs: rt_device_find, rt_device_open with RT_DEVICE_FLAG_RX_NON_BLOCKING,
 *   rt_device_read (non-blocking), rt_device_write, rt_device_close
 *
 * Test Scenarios:
 * - **Scenario 1 (Interactive Echo / uart_test_nonblocking_rx):**
 *   1. Restart UART in RX non-blocking / TX blocking mode.
 *   2. Prompt user (or loopback peer) to send data while issuing countdown markers to MSH.
 *   3. Perform successive non-blocking reads of varying sizes (256/128 bytes), echoing captured data back and logging totals.
 *
 * Verification Metrics:
 * - Each read returns immediately with available data (may be zero); totals accumulate without overflow.
 * - Function returns RT_TRUE after final log, indicating no failures during sequence.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` with loopback or user-provided input on `RT_SERIAL_TC_DEVICE_NAME`.
 * - UART driver must support non-blocking reads and reversible open/close.
 *
 * Expected Results:
 * - No assertions triggered; terminal displays countdown prompts and mirrored input.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_nonblocking_rx)`.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_SERIAL_V2

static rt_bool_t nonblock_read(rt_device_t uart_dev)
{
    rt_size_t total_length, recv_length;
    char      uart_read_buffer[1024], log_buffer[64];

    /* make sure device is closed and reopen it */
    while (rt_device_close(uart_dev) != -RT_ERROR);
    rt_device_open(uart_dev, RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING);

    rt_sprintf(log_buffer, "\nNONBLOCKING READ BEGIN, PLEASE SEND SOME DATAS\n");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    total_length = 0;
    rt_device_write(uart_dev, 0, "5\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    rt_device_write(uart_dev, 0, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read, total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "4\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    rt_device_write(uart_dev, 0, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "3\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    rt_device_write(uart_dev, 0, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read, total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "2\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 128);
    rt_device_write(uart_dev, 0, uart_read_buffer, 128);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "1\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 128);
    rt_device_write(uart_dev, 0, uart_read_buffer, 128);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_sprintf(log_buffer, "BLOCKING READ END");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    return RT_TRUE;
}

static void uart_test_nonblocking_rx(void)
{
    rt_device_t uart_dev;
    uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    uassert_not_null(uart_dev);

    uassert_true(nonblock_read(uart_dev));
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
    UTEST_UNIT_RUN(uart_test_nonblocking_rx);
}
UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_nonblocking_rx", utest_tc_init, utest_tc_cleanup, 10);

#endif
