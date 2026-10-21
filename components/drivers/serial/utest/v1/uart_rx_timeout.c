/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-21     Yunlk        the first version
 */

/**
 * Test Case Name: Serial V1 RX Timeout Event Test (components.drivers.serial.v1.uart_rx_timeout)
 *
 * Test Objectives:
 * - Verify that RT_SERIAL_EVENT_RX_TIMEOUT is handled by the v1 recceive path
 *   instead of being silently dropped.
 * - Verify that the event behaves like a receive indication: the hardware FIFO is
 *   drained and the bytes buffered in the software FIFO are reported through
 *   rx_indicate.
 * - List specific functions or APIs to be tested:
 * - rt_hw_serial_register
 * - rt_device_open / rt_device_set_rx_indicate / rt_device_close
 * - rt_hw_serial_isr with RT_SERIAL_EVENT_RX_IND and RT_SERIAL_EVENT_RX_TIMEOUT
 *
 * Test Scenarios:
 * - A fake serial device is registered and opened with RT_DEVICE_FLAG_INT_RX, so
 * that the v1 framework allocates its software RX FIFO. The device's getc()
 * returns bytes from a scripted buffer, which stands in for the hardware FIFO.
 * 1. **Baseline (RX_IND):** four bytes are available, the RX indication event is
 *    raised and rx_indicate must be called once with a length of 4.
 * 2. **Timeout after partial frame (RX_TIMEOUT):** five more bytes are available,
 *    the timeout event is raised and rx_indicate must be called once with the
 *    total buffered length of 9.
 * 3. **Timeout with nothing buffered:** the software FIFO is emptied first, the
 *    timeout event is raised and rx_indicate must NOT be called, because there is
 *    nothing to report.
 *
 * Verification Metrics:
 * - Case 1: callback count 1, reported length 4.
 * - Case 2: callback count 1, reported length 9 (4 from case 1 + 5 new bytes).
 * - Case 3: callback count 0 when nothing is buffered.
 *
 * Dependencies:
 * - Software configuration
 * - `RT_USING_UTEST` and `RT_USING_UTESTCASES` must be enabled.
 * - `RT-Thread Utestcases` -> `Kernel Components` -> `Drivers` -> `Serial Test`
 *   -> `Serial V1 Test` must be enabled (`RT_UTEST_SERIAL_V1`).
 * - `RT_USING_SERIAL_V1` must be the selected serial framework.
 * - Hardware requirements
 * - None. The test registers its own fake serial device and never touches real
 *   hardware, so it runs on any BSP (verified on bsp/qemu-vexpress-a9).
 * - Run the test case from the msh prompt:
 * `utest_run components.drivers.serial.v1.uart_rx_timeout`
 *
 * Expected Results:
 * - The console prints the callback count and length for each scenario.
 * - Final Output: `[ PASSED ] [ result ] testcase (components.drivers.serial.v1.uart_rx_timeout)`
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_SERIAL_V1

#define TEST_DEV_NAME   "utest_uart"
#define TEST_RXBUF_SIZE 64
#define TEST_HW_DATA    "RT-THREAD"
#define TEST_HW_LEN     (sizeof(TEST_HW_DATA) - 1)

static struct rt_serial_device _test_serial;
static rt_bool_t _test_registered;

/* bytes the fake hardware "has already received", consumed by getc() */
static const char _hw_data[] = TEST_HW_DATA;
static rt_size_t _hw_pos;
static rt_size_t _hw_len;

static rt_size_t _ind_count;
static rt_size_t _ind_last_size;

static rt_err_t _rx_indicate(rt_device_t dev, rt_size_t size)
{
    _ind_count++;
    _ind_last_size = size;

    return RT_EOK;
}

static void _ind_reset(void)
{
    _ind_count = 0;
    _ind_last_size = 0;
}

/* ---------------- fake uart ops ---------------- */

static rt_err_t _fake_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t _fake_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    return RT_EOK;
}

static int _fake_putc(struct rt_serial_device *serial, char c)
{
    return 1;
}

/* returns the next scripted byte, -1 when the hardware FIFO is empty */
static int _fake_getc(struct rt_serial_device *serial)
{
    if (_hw_pos < _hw_len)
    {
        return (int)(rt_uint8_t)_hw_data[_hw_pos++];
    }

    return -1;
}

static const struct rt_uart_ops _fake_ops = {
    .configure = _fake_configure,
    .control = _fake_control,
    .putc = _fake_putc,
    .getc = _fake_getc,
    .dma_transmit = RT_NULL,
};

/* ---------------- test cases ---------------- */

/* a hardware idle-line timeout after a partial frame must report the buffered bytes */
static void uart_v1_rx_timeout(void)
{
    rt_device_t dev;
    struct serial_configure cfg = RT_SERIAL_CONFIG_DEFAULT;
    struct rt_serial_rx_fifo *rx_fifo;

    cfg.bufsz = TEST_RXBUF_SIZE;

    if (!_test_registered)
    {
        _test_serial.ops = &_fake_ops;
        _test_serial.config = cfg;
        uassert_int_equal(rt_hw_serial_register(&_test_serial, TEST_DEV_NAME,
                                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                                RT_NULL),
                          RT_EOK);
        _test_registered = RT_TRUE;
    }

    dev = rt_device_find(TEST_DEV_NAME);
    uassert_not_null(dev);
    uassert_int_equal(rt_device_open(dev, RT_DEVICE_FLAG_INT_RX), RT_EOK);
    rt_device_set_rx_indicate(dev, _rx_indicate);

    rx_fifo = (struct rt_serial_rx_fifo *)_test_serial.serial_rx;
    uassert_not_null(rx_fifo);

    /* ---- case 1: baseline, a plain RX_IND with 4 bytes ---- */
    _hw_pos = 0;
    _hw_len = 4;
    _ind_reset();

    rt_hw_serial_isr(&_test_serial, RT_SERIAL_EVENT_RX_IND);
    LOG_I("RX_IND   -> callbacks=%d, last_size=%d (expect 1 / 4)",
          (int)_ind_count, (int)_ind_last_size);
    uassert_int_equal(_ind_count, 1);
    uassert_int_equal(_ind_last_size, 4);

    /* ---- case 2: the event under test, 5 more bytes arrive, then timeout ---- */
    _hw_pos = 4;
    _hw_len = TEST_HW_LEN;
    _ind_reset();

    rt_hw_serial_isr(&_test_serial, RT_SERIAL_EVENT_RX_TIMEOUT);
    LOG_I("RX_TIMEOUT -> callbacks=%d, last_size=%d (expect 1 / %d)",
          (int)_ind_count, (int)_ind_last_size, (int)TEST_HW_LEN);
    uassert_int_equal(_ind_count, 1);
    uassert_int_equal(_ind_last_size, TEST_HW_LEN);

    /* ---- case 3: boundary, timeout with an empty buffer must stay silent ---- */
    rx_fifo->get_index = rx_fifo->put_index;
    rx_fifo->is_full = RT_FALSE;
    _hw_pos = 0;
    _hw_len = 0;
    _ind_reset();

    rt_hw_serial_isr(&_test_serial, RT_SERIAL_EVENT_RX_TIMEOUT);
    LOG_I("RX_TIMEOUT (empty) -> callbacks=%d (expect 0)", (int)_ind_count);
    uassert_int_equal(_ind_count, 0);

    rt_device_close(dev);
}

static rt_err_t utest_tc_init(void)
{
    _test_registered = RT_FALSE;
    _ind_reset();
    _hw_pos = 0;
    _hw_len = 0;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_device_t dev = rt_device_find(TEST_DEV_NAME);

    if (dev != RT_NULL)
    {
        rt_device_close(dev);
    }

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(uart_v1_rx_timeout);
}
UTEST_TC_EXPORT(testcase, "components.drivers.serial.v1.uart_rx_timeout",
                utest_tc_init, utest_tc_cleanup, 10);

#endif /* RT_UTEST_SERIAL_V1 */
