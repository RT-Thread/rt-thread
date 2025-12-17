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
 * Test Case Name: UART Non-Blocking Transmit Throughput Test
 *
 * Test Objectives:
 * - Measure and validate non-blocking transmit behavior across varying burst sizes
 * - Verify APIs: rt_device_find, rt_device_open with RT_DEVICE_FLAG_TX_NON_BLOCKING,
 *   rt_device_write, rt_device_close, rt_tick_get
 *
 * Test Scenarios:
 * - **Scenario 1 (Burst Size Sweep / uart_test_nonblocking_tx):**
 *   1. Re-open the UART in fully non-blocking mode after ensuring it is closed.
 *   2. Issue sequential write loops for payloads of 8, 32, 128, 512, and 1024 bytes, plus 100 iterations of 1024 bytes,
 *      collecting total bytes written and elapsed ticks.
 *   3. Log throughput metrics for each run to detect stalls or partial transfers.
 *
 * Verification Metrics:
 * - Each loop writes the exact number of requested bytes; cumulative counters match expectations.
 * - Measured tick deltas are captured for post-run performance analysis; function returns RT_TRUE.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` with loopback wiring for `RT_SERIAL_TC_DEVICE_NAME`.
 * - UART driver must support non-blocking write semantics and allow repeated open/close.
 *
 * Expected Results:
 * - Test completes without assertion failures; logs show per-size throughput data.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_nonblocking_tx)`.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#define UART_SEND_TIMES  100
#define UART_TEST_NUMBER 6


#ifdef RT_UTEST_SERIAL_V2

static rt_bool_t nonblock_write(rt_device_t uart_dev)
{
    rt_size_t  wr_sz = 0, tmp = 0, i, write_num_array[UART_TEST_NUMBER], total_write_num[UART_TEST_NUMBER], index;
    rt_tick_t  tick1, tick2, tick_array[UART_TEST_NUMBER];
    rt_uint8_t uart_write_buffer[1024];

    for (i = 0; i < 1024; i++)
        uart_write_buffer[i] = '0' + (i % 50);

    /* make sure device is closed and reopen it */
    while (rt_device_close(uart_dev) != -RT_ERROR);
    uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    rt_device_open(uart_dev, RT_DEVICE_FLAG_TX_NON_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING);

    LOG_D("\nNONBLOCKING WRITE BEGIN\n");

    index = 0;
    tmp   = 0;
    tick1 = rt_tick_get();
    for (i = 0; i < UART_SEND_TIMES; i++)
    {
        wr_sz = 0;
        while (wr_sz < 1024)
            wr_sz += rt_device_write(uart_dev, 0, &uart_write_buffer[wr_sz], 1024 - wr_sz);
        tmp += wr_sz;
    }
    tick2                    = rt_tick_get();
    total_write_num[index]   = UART_SEND_TIMES * 1024;
    tick_array[index]        = tick2 - tick1;
    write_num_array[index++] = tmp;

    wr_sz = 0;
    tick1 = rt_tick_get();
    while (wr_sz < 8)
        wr_sz += rt_device_write(uart_dev, 0, &uart_write_buffer[wr_sz], 8 - wr_sz);
    tick2                    = rt_tick_get();
    total_write_num[index]   = 8;
    tick_array[index]        = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    while (wr_sz < 32)
        wr_sz += rt_device_write(uart_dev, 0, &uart_write_buffer[wr_sz], 32 - wr_sz);
    tick2                    = rt_tick_get();
    total_write_num[index]   = 32;
    tick_array[index]        = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    while (wr_sz < 128)
        wr_sz += rt_device_write(uart_dev, 0, &uart_write_buffer[wr_sz], 128 - wr_sz);
    tick2                    = rt_tick_get();
    total_write_num[index]   = 128;
    tick_array[index]        = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    while (wr_sz < 512)
        wr_sz += rt_device_write(uart_dev, 0, &uart_write_buffer[wr_sz], 512 - wr_sz);
    tick2                    = rt_tick_get();
    total_write_num[index]   = 512;
    tick_array[index]        = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    while (wr_sz < 1024)
        wr_sz += rt_device_write(uart_dev, 0, &uart_write_buffer[wr_sz], 1024 - wr_sz);
    tick2                    = rt_tick_get();
    total_write_num[index]   = 1024;
    tick_array[index]        = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    LOG_D("\nNONBLOCKING_TX END\n");
    for (i = 0; i < index; i++)
    {
        LOG_D("\nNONBLOCKING_MODE : write %d / %d bytes in %d ticks\n", write_num_array[i], total_write_num[i], tick_array[i]);
        rt_thread_mdelay(10);
    }

    return RT_TRUE;
}

static void uart_test_nonblocking_tx(void)
{
    rt_device_t uart_dev;
    uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    uassert_not_null(uart_dev);

    uassert_true(nonblock_write(uart_dev));
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
    UTEST_UNIT_RUN(uart_test_nonblocking_tx);
}
UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_nonblocking_tx", utest_tc_init, utest_tc_cleanup, 10);

#endif
