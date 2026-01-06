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
#include <utest.h>
#include <string.h>
#include "drv_i2c.h"
#include "drv_pinctrl.h"
#include "drv_gpio.h"

/*
 * 测试K230 I2C的主从机通信，在这里采用I2C0作为测试对象
 *
 * 硬件平台：
 * 测试的硬件平台为庐山派开发板，使用的I2C0引脚是GPIO048(SCL)
 * 和GPIO049(SDA)。
 *
 * 测试说明：
 * 1. 测试I2C0主机模式
 *     主机模式下，主机向从机发送16字节数据（不包括写读地址），
 *     然后再读取回来进行校验，共执行两次，分别是400kHz和1MHz速率。
 *     第一次写数据时，带一字节地址，总共写16字节数据，读取15字节数据，
 *     第二次写数据时，带一字节地址，总共写17字节数据，读取16字节数据。
 *     在两次写数据的过程中，如果开启dma功能，第一次会调用dma进行写，
 *     第二次会调用dma进行读。（前提是BSP_USING_I2C_DMA宏被定义，
 *     因为pdma要求地址与数据都要4字节对齐（地址的对齐问题会在驱动
 *     内部处理），若写/读数据大小非4字节对齐，即使启用了dma功能，
 *     实际也是调用的cpu轮询读写，这一点需要应用程序注意并处理）
 *     注：使用的从机为AT24C08 EEPROM，设备地址为0x50，
 *     page size 为 16 字节。
 */

#define I2C_NAME            "i2c0"
#define TARGET_ADDR         0x50

#define TEST_BUFFER_SIZE    16

#define I2C_SCL_PIN         48
#define I2C_SDA_PIN         49
#define I2C_SCL_PIN_AF      IOMUX_FUNC4
#define I2C_SDA_PIN_AF      IOMUX_FUNC4

static void test_i2c0_deinit_pin(void)
{
    k230_pinctrl_set_function(I2C_SCL_PIN, IOMUX_FUNC1);
    k230_pinctrl_set_function(I2C_SDA_PIN, IOMUX_FUNC1);
    k230_pinctrl_set_oe(I2C_SCL_PIN, 0);
    k230_pinctrl_set_oe(I2C_SDA_PIN, 0);
    k230_pinctrl_set_ie(I2C_SCL_PIN, 1);
    k230_pinctrl_set_ie(I2C_SDA_PIN, 1);

    kd_pin_mode(I2C_SCL_PIN, GPIO_DM_INPUT);
    kd_pin_mode(I2C_SDA_PIN, GPIO_DM_INPUT);
}

static void test_i2c0_init_pin(void)
{
    k230_pinctrl_set_function(I2C_SCL_PIN, I2C_SCL_PIN_AF); // I2C0_SCL
    k230_pinctrl_set_function(I2C_SDA_PIN, I2C_SDA_PIN_AF); // I2C0_SDA
    k230_pinctrl_set_oe(I2C_SCL_PIN, 1);
    k230_pinctrl_set_oe(I2C_SDA_PIN, 1);
    k230_pinctrl_set_ie(I2C_SCL_PIN, 1);
    k230_pinctrl_set_ie(I2C_SDA_PIN, 1);
}

static int test_i2c_check_pin(void)
{
    test_i2c0_deinit_pin();

    if (kd_pin_read(I2C_SCL_PIN) != 1 || kd_pin_read(I2C_SDA_PIN) != 1)
    {
        LOG_W("i2c bus is not idle, try to recover it.");
        k230_pinctrl_set_oe(I2C_SCL_PIN, 1);
        kd_pin_mode(I2C_SCL_PIN, GPIO_DM_OUTPUT);
        for (rt_uint8_t i = 0; i < 9; i++)
        {
            kd_pin_write(I2C_SCL_PIN, 0);
            rt_hw_us_delay(2);
            kd_pin_write(I2C_SCL_PIN, 1);
            rt_hw_us_delay(2);
        }
        k230_pinctrl_set_oe(I2C_SCL_PIN, 0);
        kd_pin_mode(I2C_SCL_PIN, GPIO_DM_INPUT);
    }

    if (kd_pin_read(I2C_SCL_PIN) != 1 || kd_pin_read(I2C_SDA_PIN) != 1)
    {
        LOG_E("i2c bus recover failed");
        return -RT_ERROR;
    }

    LOG_I("i2c bus(pin: %u, %u) is idle, init i2c bus pin", I2C_SCL_PIN, I2C_SDA_PIN);
    test_i2c0_init_pin();

    return RT_EOK;
}

static void _test_i2c0_master(rt_uint8_t *buffer_w, rt_uint8_t *buffer_r, rt_uint32_t size, rt_uint32_t speed)
{
    rt_err_t ret = RT_EOK;
    struct rt_i2c_bus_device *dev;
    struct rt_i2c_msg msgs[2];

    dev = rt_i2c_bus_device_find(I2C_NAME);
    uassert_not_null(dev);
    rt_i2c_control(dev, RT_I2C_DEV_CTRL_CLK, (void *)&speed);

    msgs[0].addr  = TARGET_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = buffer_w;
    msgs[0].len   = size + 1;

    if (rt_i2c_transfer(dev, msgs, 1) != 1)
    {
        LOG_E("i2c transfer failed");
        uassert_true(0);
    }

    rt_thread_mdelay(10);

    msgs[0].addr  = TARGET_ADDR;
    msgs[0].flags = RT_I2C_WR | RT_I2C_NO_STOP;
    msgs[0].buf   = &buffer_r[0];
    msgs[0].len   = 1;

    msgs[1].addr  = TARGET_ADDR;
    msgs[1].flags = RT_I2C_RD | RT_I2C_NO_START;
    msgs[1].buf   = &buffer_r[1];
    msgs[1].len   = size;

    if (rt_i2c_transfer(dev, msgs, 2) != 2)
    {
        LOG_E("i2c transfer failed");
        uassert_true(0);
    }

    LOG_I("Read data:\n");
    for (rt_uint8_t i = 1; i < size + 1; i++)
    {
        LOG_I("0x%02X ", buffer_r[i]);
    }

    uassert_buf_equal(buffer_w + 1, buffer_r + 1, size);
}

static void test_i2c0_master(void)
{
    rt_uint8_t buffer_w[TEST_BUFFER_SIZE + 1];
    rt_uint8_t buffer_r[TEST_BUFFER_SIZE + 1];
    rt_uint32_t size = TEST_BUFFER_SIZE;
    rt_uint32_t speed = 400000; // 400kHz

    memset(buffer_w + 1, 0xAA, TEST_BUFFER_SIZE);
    buffer_w[0] = 0x00; // memory address
    memset(buffer_r, 0x00, TEST_BUFFER_SIZE + 1);

    /* if BSP_USING_I2C_DMA is enabled, test i2c write with dma */
    _test_i2c0_master(buffer_w, buffer_r, size - 1, speed);

    speed = 1000000; // 1MHz
    memset(buffer_w + 1, 0x55, TEST_BUFFER_SIZE);
    buffer_w[0] = 0x00; // memory address
    memset(buffer_r, 0x00, TEST_BUFFER_SIZE + 1);

    /* if BSP_USING_I2C_DMA is enabled, test i2c read with dma */
    _test_i2c0_master(buffer_w, buffer_r, size, speed);
}

static void testcase(void)
{
    LOG_I("This is a i2c test case.\n");
    UTEST_UNIT_RUN(test_i2c0_master);
}

static rt_err_t utest_tc_init(void)
{
    return test_i2c_check_pin();
}

static rt_err_t utest_tc_cleanup(void)
{
    LOG_I("i2c bus pin deinit.\n");
    test_i2c0_deinit_pin();
    return RT_EOK;
}
UTEST_TC_EXPORT(testcase, "bsp.k230.drivers.i2c", utest_tc_init, utest_tc_cleanup, 100);
