/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>
#include <rtdbg.h>
#include <utest.h>
#include "drv_uart.h"
#include <string.h>

/*
 * 测试 UART0 在 DMA 模式下的数据发送功能，以及 UART0 在中断模式下的数据接收功能
 *
 * 功能说明：
 * 1. 发送测试（uart_tx_demo）：
 *    - 查找名为 "uart0" 的串口设备；
 *    - 打开设备，并配置为 DMA 发送（DMA_TX）+ 流式传输（STREAM）模式；
 *    - 设置串口参数：
 *        - 波特率：115200；
 *        - 数据位：8 位；
 *        - 停止位：1 位；
 *        - 校验位：无；
 *    - 动态分配一段 2000 字节的内存作为发送缓冲区：
 *        - 填充 1999 个字符 '['；
 *        - 最后添加 '\0' 作为字符串结尾；
 *    - 调用 `rt_device_write` 接口，将缓冲区数据通过 UART0 DMA 方式发送出去；
 *    - 发送完成后关闭 UART0 设备并释放发送缓冲区内存。
 *
 * 2. 接收测试（uart_rx_demo）：
 *    - 查找名为 "uart0" 的串口设备；
 *    - 打开设备，并配置为中断接收（INT_RX）+ 流式传输（STREAM）模式；
 *    - 设置串口参数（波特率 115200，8N1，无校验）；
 *    - 在 5 秒超时范围内循环读取 UART0 接收到的数据：
 *        - 如果有数据，则立即打印接收到的内容；
 *        - 如果没有数据，每隔 2.5 秒检查一次；
 *    - 超时或接收后关闭 UART0 设备。
 *
 * 硬件说明：
 * - 本测试基于 K230 平台；
 * - uart_tx_demo 用于发送测试，可在串口调试工具上观察 1999 个 '[' 输出；
 * - uart_rx_demo 用于接收测试，在 5 秒内通过外部串口助手发送数据，可在日志中看到接收结果；
 *
 */

#define UART0_DEV_NAME    "uart0"
#define TEXT_LENGTH        2000
#define TEXT_TIME          5
#define RX_TEXT_PERIOD     2500

static void uart_tx_demo(void)
{
    rt_device_t uart_dev;
    char *msg = rt_malloc(TEXT_LENGTH);
    for (int i = 0; i < TEXT_LENGTH - 1; i++)
    {
        msg[i] = '[';
    }
    msg[TEXT_LENGTH-1]='\0';

    rt_err_t ret;

    uart_dev = rt_device_find(UART0_DEV_NAME);
    uassert_not_null(uart_dev);

    ret = rt_device_open(uart_dev, RT_DEVICE_FLAG_DMA_TX | RT_DEVICE_FLAG_STREAM);
    uassert_int_equal(ret, RT_EOK);

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = 115200;
    config.data_bits = DATA_BITS_8;
    config.stop_bits = STOP_BITS_1;
    config.parity = PARITY_NONE;
    ret = rt_device_control(uart_dev, RT_DEVICE_CTRL_CONFIG, &config);
    uassert_int_equal(ret, RT_EOK);

    size_t len = TEXT_LENGTH;
    ret = rt_device_write(uart_dev, 0, msg, len);
    uassert_int_equal(ret, len);
    ret = rt_device_close(uart_dev);
    uassert_int_equal(ret, RT_EOK);
    rt_free(msg);
}

static void uart_rx_demo(void)
{
    rt_device_t uart_dev;
    char rx_buf[32];
    rt_size_t rx_len;

    uart_dev = rt_device_find(UART0_DEV_NAME);
    uassert_not_null(uart_dev);

    rt_err_t ret = rt_device_open(uart_dev, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
    uassert_int_equal(ret, RT_EOK);

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = 115200;
    config.data_bits = DATA_BITS_8;
    config.stop_bits = STOP_BITS_1;
    config.parity = PARITY_NONE;
    ret = rt_device_control(uart_dev, RT_DEVICE_CTRL_CONFIG, &config);
    uassert_int_equal(ret, RT_EOK);

    LOG_I("UART RX demo: please send data to uart0 within 5s...\n");

    rt_tick_t timeout = rt_tick_get() + RT_TICK_PER_SECOND * TEXT_TIME;
    while (rt_tick_get() < timeout)
    {
        rx_len = rt_device_read(uart_dev, 0, rx_buf, sizeof(rx_buf) - 1);
        if (rx_len > 0)
        {
            rx_buf[rx_len] = '\0';
            LOG_I("UART RX got %d bytes: %s\n", rx_len, rx_buf);
            break;
        }
        rt_thread_mdelay(RX_TEXT_PERIOD);
    }

    ret = rt_device_close(uart_dev);
    uassert_int_equal(ret, RT_EOK);
}

static void uart_testcase(void)
{
    UTEST_UNIT_RUN(uart_tx_demo);
    UTEST_UNIT_RUN(uart_rx_demo);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(uart_testcase, "uart", utest_tc_init, utest_tc_cleanup, 10);