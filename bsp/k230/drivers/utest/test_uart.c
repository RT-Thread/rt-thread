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
 * 测试 UART3 在 DMA 模式下的数据发送功能
 *
 * 1. 查找名为 "uart3" 的串口设备；
 * 2. 打开设备，并配置为 DMA 发送（DMA_TX）+ 流式传输（STREAM）模式；
 * 3. 设置串口参数：
 *    - 波特率：115200；
 *    - 数据位：8 位；
 *    - 停止位：1 位；
 *    - 校验位：无；
 * 4. 动态分配一段 2024 字节的内存作为发送缓冲区：
 *    - 填充 2023 个字符 '['；
 *    - 最后添加 '\0' 作为字符串结尾；
 * 5. 调用 `rt_device_write` 接口，将缓冲区数据通过 UART3 DMA 方式发送出去；
 * 6. 发送完成后：
 *    - 关闭 UART3 设备；
 *    - 释放发送缓冲区内存。
 *
 * 硬件说明：
 * - 本测试基于 K230 平台；
 * - UART3 为开发板上的一个串口接口；
 * - 发送的数据为 2023 个 '[' 字符，可通过串口调试工具观察输出；
 * - 本测试仅验证 DMA 发送路径是否正常，不包含接收功能。
 *
 */

#define UART_DEV_NAME "uart3"

static void uart_tx_demo(void)
{
    rt_device_t uart_dev;
    char *msg = rt_malloc(2024);
    for (int i = 0; i < 2023; i++)
    {
        msg[i] = '[';
    }
    msg[2023]='\0';

    rt_err_t ret;

    uart_dev = rt_device_find(UART_DEV_NAME);
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

    struct rt_serial_device *serial;
    serial = rt_container_of(uart_dev, struct rt_serial_device, parent);
    uassert_not_null(serial);

    size_t len = 2024;
    ret = rt_device_write(serial,0,msg,len);
    uassert_int_equal(ret, len);

    ret = rt_device_close(uart_dev);
    uassert_int_equal(ret, RT_EOK);
    rt_free(msg);
}

static void uart_testcase(void)
{
    UTEST_UNIT_RUN(uart_tx_demo);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(uart_testcase, "uart_dma", utest_tc_init, utest_tc_cleanup, 10);