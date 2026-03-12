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
#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include <utest.h>
#include "drv_spi.h"
#include <string.h>
#include "drv_pinctrl.h"
#include "drv_gpio.h"
/*
 * 测试 SPI0 在标准SPI模式下的数据发送功能
 *
 * 功能说明：
 *  - 查找名为 "spi0" 的SPI总线设备；
 *  - 挂载SPI设备到总线；
 *  - 配置SPI设备参数：
 *      - 模式：标准SPI模式0 (RT_SPI_MODE_0)
 *      - 数据位：8位
 *      - 最大频率：1MHz
 *      - 数据线宽度：1（标准SPI）
 *  - 准备测试数据（递增序列）；
 *  - 创建SPI消息并发送16字节数据；
 *  - 发送完成接收从机的16字节数据；
 *  - 发送完成后卸载SPI设备。
 *
 * 硬件说明：
 * - 本测试基于 K230 平台；
 * - 测试SPI0(OSPI)的标准SPI模式TX和RX功能,使用硬件CS；
 * - 对应的引脚配置为：
 *      - CS: GPIO14
 *      - CLK: GPIO15
 *      - D0: GPIO16
 *      - D1: GPIO17
 * - 需要连接SPI从设备（如SPI调试器等）来验证数据传输，本测试文件使用一块stm32制作的SPI调试器；
 * - 如果没有实际从设备，可以使用逻辑分析仪或示波器观察SPI波形(但是只能验证TX功能,接收到会是16bit的0xff)；
 */
#define SPI0_BUS_NAME     "spi0"
#define SPI0_DEV_NAME0     "spi00"
#define TEST_DATA_LENGTH  16
#define SPI0_CS_PIN      14
#define SPI0_CLK_PIN     15
#define SPI0_D0_PIN      16
#define SPI0_D1_PIN      17
#define SPI0_CS_PIN_AF  IOMUX_FUNC2
#define SPI0_CLK_PIN_AF  IOMUX_FUNC2
#define SPI0_D0_PIN_AF  IOMUX_FUNC2
#define SPI0_D1_PIN_AF  IOMUX_FUNC2

static void spi_gpio_init(void)
{
    LOG_I("SPI demo: initializing SPI0 GPIO...");
    k230_pinctrl_set_function(SPI0_CS_PIN, SPI0_CS_PIN_AF);
    k230_pinctrl_set_function(SPI0_CLK_PIN, SPI0_CLK_PIN_AF);
    k230_pinctrl_set_function(SPI0_D0_PIN, SPI0_D0_PIN_AF);
    k230_pinctrl_set_function(SPI0_D1_PIN, SPI0_D1_PIN_AF);

    k230_pinctrl_set_oe(SPI0_CS_PIN, 1);
    k230_pinctrl_set_oe(SPI0_CLK_PIN, 1);
    k230_pinctrl_set_oe(SPI0_D0_PIN, 1);
    k230_pinctrl_set_oe(SPI0_D1_PIN, 1);

    k230_pinctrl_set_ie(SPI0_CS_PIN, 1);
    k230_pinctrl_set_ie(SPI0_CLK_PIN, 1);
    k230_pinctrl_set_ie(SPI0_D0_PIN, 1);
    k230_pinctrl_set_ie(SPI0_D1_PIN, 1);
}

static void spi_device_demo(void)
{
    struct rt_qspi_device *qspi_dev;
    LOG_I("Using rt_qspi_device to transmit");
    rt_err_t ret;
    uint8_t tx_data[TEST_DATA_LENGTH];
    uint8_t rx_data[TEST_DATA_LENGTH];
    for (int i = 0; i < TEST_DATA_LENGTH; i++)
    {
        tx_data[i] = i;
    }
    rt_memset(rx_data, 0, sizeof(rx_data));

    /* Find QSPI Bus */
    struct rt_spi_bus *spi_bus = (struct rt_spi_bus *)rt_device_find(SPI0_BUS_NAME);
    if (!spi_bus)
    {
        LOG_E("Failed to find SPI bus: %s", SPI0_BUS_NAME);
        return;
    }
    LOG_I("Success to find SPI bus: %s", SPI0_BUS_NAME);

    qspi_dev = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (!qspi_dev)
    {
        LOG_E("Failed to allocate SPI device memory");
        return;
    }
    LOG_I("Success to allocate QSPI device memory");
    /* Attach SPI Device */
    ret = rt_spi_bus_attach_device(&(qspi_dev->parent), SPI0_DEV_NAME0, SPI0_BUS_NAME, RT_NULL);
    if (ret != RT_EOK)
    {
        LOG_E("Failed to attach SPI device: %d", ret);
        rt_free(qspi_dev);
        return;
    }
    LOG_I("SPI device attached successfully");
    /* SPI Device Config*/
    struct rt_qspi_configuration qspi_cfg;
    qspi_cfg.parent.mode = RT_SPI_MODE_0 | RT_SPI_MSB;
    qspi_cfg.parent.data_width = 8;
    qspi_cfg.parent.max_hz = 1000000;
    qspi_cfg.parent.reserved = 0;
    qspi_cfg.qspi_dl_width = 1;
    qspi_cfg.medium_size = 0;
    qspi_cfg.ddr_mode = 0;


    ret = rt_qspi_configure(qspi_dev, &qspi_cfg);
    if (ret != RT_EOK)
    {
        LOG_E("SPI configuration failed: %d", ret);
        rt_free(qspi_dev);
        return;
    }

    LOG_I("SPI configuration: Standard SPI, mode=0, data_width=8, max_hz=%d, data_lines=%d",
          qspi_cfg.parent.max_hz, qspi_cfg.qspi_dl_width);
    LOG_I("Sending test data (length=%d):", TEST_DATA_LENGTH);

    for (int i = 0; i < TEST_DATA_LENGTH; i++)
    {
        rt_kprintf("%02X ", tx_data[i]);
    }
    rt_kprintf("\n");

    /* Create SPI Message */
    struct rt_qspi_message msg;
    rt_memset(&msg, 0, sizeof(msg));
    /*Using Standard SPI*/
    msg.instruction.content = 0;
    msg.instruction.qspi_lines = 1;
    msg.address.content = 0;
    msg.address.size = 0;
    msg.address.qspi_lines = 1;
    msg.qspi_data_lines = 1;
    msg.dummy_cycles = 0;

    /* SPI Message Config */
    msg.parent.send_buf = tx_data;
    msg.parent.recv_buf = rx_data;
    msg.parent.length = TEST_DATA_LENGTH;
    msg.parent.cs_take = 1;
    msg.parent.cs_release = 1;
    msg.parent.next = RT_NULL;

    /* Transfer Data */
    ret = rt_qspi_transfer_message(qspi_dev, &msg);
    if (ret != TEST_DATA_LENGTH)
    {
        LOG_E("SPI transfer failed, returned: %d", ret);
    }
    uassert_int_equal(ret, TEST_DATA_LENGTH);

    LOG_I("SPI TX demo: sent %d bytes successfully", ret);
    LOG_I("Received data from slave (length=%d):", TEST_DATA_LENGTH);
    for (int i = 0; i < TEST_DATA_LENGTH; i++)
    {
        rt_kprintf("%02X ", rx_data[i]);
    }
    rt_kprintf("\n");
    /* Detach SPI Device */
    ret = rt_spi_bus_detach_device(&(qspi_dev->parent));
    uassert_int_equal(ret, RT_EOK);
    rt_free(qspi_dev);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(spi_gpio_init);
    UTEST_UNIT_RUN(spi_device_demo);
}

static rt_err_t utest_tc_init(void)
{
    LOG_I("SPI test case initialization");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    LOG_I("SPI test case cleanup");
    return RT_EOK;
}

UTEST_TC_EXPORT(testcase, "bsp.k230.drivers.spi", utest_tc_init, utest_tc_cleanup, 10);
