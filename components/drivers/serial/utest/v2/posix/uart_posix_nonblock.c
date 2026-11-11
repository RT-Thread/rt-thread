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
 * Test Case Name: UART POSIX Non-Blocking Test
 *
 * Test Objectives:
 * - Validate POSIX-layer non-blocking serial operations using termios configuration
 * - Verify APIs: open/close, tcgetattr/tcsetattr, cfsetispeed/cfsetospeed, fcntl(O_NONBLOCK),
 *   read, write, rt_thread_mdelay
 *
 * Test Scenarios:
 * - **Scenario 1 (Non-Blocking Echo / tc_uart_api):**
 *   1. Open POSIX device `RT_SERIAL_POSIX_TC_DEVICE_NAME`, configure baud, frame format, and disable flow control.
 *   2. Enable O_NONBLOCK mode and allocate small TX/RX buffer.
 *   3. Loop `RT_SERIAL_TC_SEND_ITERATIONS` times, issuing fixed-size and random-length writes, followed by reads after short delays to confirm echo data availability.
 *
 * Verification Metrics:
 * - Each write/read pair returns the expected number of bytes.
 * - No system calls fail; routine returns RT_TRUE signalling success.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` with POSIX device exposure (`RT_SERIAL_POSIX_TC_DEVICE_NAME`) and loopback wiring.
 * - Operating environment must provide termios/fcntl APIs (e.g., RT-Thread POSIX layer or Linux host).
 *
 * Expected Results:
 * - Test executes without assertions; logs remain quiet unless errors occur.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_posix_nonblock)`.
 */

#include <rtthread.h>
#include "utest.h"
#include <rtdevice.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>


#ifdef RT_UTEST_SERIAL_V2

static int32_t serial_fd;

static rt_err_t uart_find(void)
{
    serial_fd = open(RT_SERIAL_POSIX_TC_DEVICE_NAME, O_RDWR);
    if (serial_fd == -1)
    {
        LOG_E("find %s device failed!\n", RT_SERIAL_TC_DEVICE_NAME);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t configureSerial(int fd, int baud)
{
    int32_t        result = 0;
    struct termios options;

    result = tcgetattr(fd, &options); // 获取当前端口的属性
    if (result == -1)
        return -RT_ERROR;

    // 设置波特率
    result = cfsetispeed(&options, baud); // 设置输入波特率
    if (result == -1)
        return -RT_ERROR;

    result = cfsetospeed(&options, baud); // 设置输出波特率
    if (result == -1)
        return -RT_ERROR;

    // 设置数据位
    options.c_cflag &= ~PARENB; // 清除校验位，无校验
    options.c_cflag &= ~CSTOPB; // 仅一个停止位
    options.c_cflag &= ~CSIZE;  // 清除掩码
    options.c_cflag |= CS8;     // 8位数据

    // 设置无流控
    options.c_cflag &= ~CRTSCTS;                // 不使用硬件流控制
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // 不使用软件流控制

    // 使能接收器和发送器
    options.c_cflag |= CLOCAL | CREAD;

    // 设置行终止符
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // 应用属性
    result = tcsetattr(fd, TCSANOW, &options);
    if (result == -1)
        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t uart_api()
{
    rt_err_t    result = RT_EOK;
    rt_uint8_t *uart_write_buffer;
    rt_int32_t  cnt, i, send_size;
    int         flags = 0;

    result = uart_find();
    if (result != RT_EOK)
    {
        return -RT_ERROR;
    }

    result = configureSerial(serial_fd, B115200);
    if (result == -1)
    {
        goto __exit;
    }

    flags = fcntl(serial_fd, F_GETFL, 0);
    if (flags == -1)
    {
        goto __exit;
    }

    result = fcntl(serial_fd, F_SETFL, flags | O_NONBLOCK);
    if (result == -1)
    {
        goto __exit;
    }

    uart_write_buffer = (rt_uint8_t *)rt_malloc(100);

    for (i = 0; i < RT_SERIAL_TC_SEND_ITERATIONS; i++)
    {
        send_size = 1;
        cnt       = write(serial_fd, uart_write_buffer, send_size);
        if (cnt != send_size)
        {
            result = -RT_ERROR;
            goto __exit;
        }

        rt_thread_mdelay(2);
        cnt = read(serial_fd, (void *)uart_write_buffer, send_size);
        if (cnt != send_size)
        {
            result = -RT_ERROR;
            goto __exit;
        }

        send_size = rand() % 30 + 1;
        cnt       = write(serial_fd, uart_write_buffer, send_size);
        if (cnt != send_size)
        {
            LOG_E("uart write failed %d %d", cnt, send_size);
            result = -RT_ERROR;
            goto __exit;
        }

        rt_thread_mdelay(send_size * 0.0868 + 5);
        cnt = read(serial_fd, (void *)uart_write_buffer, send_size + 1);
        if (cnt != send_size)
        {
            LOG_E("uart read failed %d %d", cnt, send_size);
            result = -RT_ERROR;
            goto __exit;
        }
    }

__exit:
    rt_thread_mdelay(5);
    if (uart_write_buffer)
        rt_free(uart_write_buffer);
    close(serial_fd);
    return result == RT_EOK ? RT_TRUE : RT_FALSE;
}

static void tc_uart_api(void)
{
    uassert_true(uart_api() == RT_TRUE);
}

static rt_err_t utest_tc_init(void)
{
    LOG_I("UART TEST: Please connect Tx and Rx directly for self testing.");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    close(serial_fd);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_posix_nonblock", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
