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
 * Test Case Name: UART POSIX Blocking Echo Test
 *
 * Test Objectives:
 * - Validate POSIX blocking serial IO paths with multi-threaded send/receive verification
 * - Verify APIs: open/close, tcgetattr/tcsetattr, cfsetispeed/cfsetospeed, fcntl clearing O_NONBLOCK,
 *   read, write, rt_thread_create/startup
 *
 * Test Scenarios:
 * - **Scenario 1 (Length Sweep Echo / tc_uart_api):**
 *   1. Open POSIX serial device, configure canonical settings, and enforce blocking mode.
 *   2. Launch sender/receiver threads; sender streams sequential byte patterns while receiver checks ordering until quota met.
 *   3. Iterate through deterministic and random lengths, mirroring behavior of kernel-space blocking tests, and monitor global flags for errors.
 *
 * Verification Metrics:
 * - Received data remains sequential; `uart_result` stays RT_TRUE; `uart_over_flag` raised after completion.
 * - No termios or fcntl calls fail; thread creation succeeds.
 *
 * Dependencies:
 * - Requires `RT_UTEST_SERIAL_V2` with POSIX serial device `RT_SERIAL_POSIX_TC_DEVICE_NAME` looped back.
 * - Host environment must provide POSIX termios/fcntl APIs; adequate heap for buffers and thread stacks.
 *
 * Expected Results:
 * - Test completes without assertions; logs reflect pass counts for each payload length.
 * - Utest harness prints `[  PASSED  ] [ result   ] testcase (components.drivers.serial.v2.uart_posix_echo_block)`.
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

static int32_t    serial_fd;
static rt_uint8_t uart_over_flag;
static rt_bool_t  uart_result = RT_TRUE;

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

static void uart_send_entry(void *parameter)
{
    rt_uint8_t *uart_write_buffer;
    rt_uint16_t send_len;

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
    if (write(serial_fd, uart_write_buffer, send_len) != send_len)
    {
        LOG_E("device write failed\r\n");
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
        cnt = read(serial_fd, (void *)uart_write_buffer, rev_len);
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

static rt_err_t uart_api(rt_uint16_t length)
{
    rt_thread_t thread_send = RT_NULL;
    rt_thread_t thread_recv = RT_NULL;
    rt_err_t    result      = RT_EOK;
    int         flags       = 0;
    uart_over_flag          = RT_FALSE;

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

    result = fcntl(serial_fd, F_SETFL, flags & ~O_NONBLOCK);
    if (result == -1)
    {
        goto __exit;
    }


    thread_send = rt_thread_create("uart_send", uart_send_entry, &length, 1024, RT_THREAD_PRIORITY_MAX - 4, 10);
    thread_recv = rt_thread_create("uart_recv", uart_rec_entry, &length, 1024, RT_THREAD_PRIORITY_MAX - 5, 10);
    if ((thread_send != RT_NULL) && (thread_recv != RT_NULL))
    {
        rt_thread_startup(thread_send);
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
    rt_thread_mdelay(5);
    close(serial_fd);
    uart_over_flag = RT_FALSE;
    return result;
}

static void tc_uart_api(void)
{
    rt_uint32_t times = 0;
    rt_uint16_t num   = 0;
    rt_uint32_t i     = 0;

    while (RT_SERIAL_POSIX_TC_SEND_ITERATIONS - times)
    {
        num = (rand() % 1000) + 1;
        if (uart_api(num) == RT_EOK)
            LOG_I("data_lens [%4d], it is correct to read and write data. [%d] times testing.", num, ++times);
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
    uart_result    = RT_TRUE;
    uart_over_flag = RT_FALSE;
    close(serial_fd);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(tc_uart_api);
}

UTEST_TC_EXPORT(testcase, "components.drivers.serial.v2.uart_posix_echo_block", utest_tc_init, utest_tc_cleanup, 30);

#endif /* TC_UART_USING_TC */
