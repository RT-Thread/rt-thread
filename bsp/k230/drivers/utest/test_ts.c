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
#include <rtdef.h>
#include <stdlib.h>
#include "utest.h"
#include <math.h>
#include "drv_ts.h"
#include <page.h>

/*
 * 测试温度传感器驱动的读取功能
 *
 * 1. 查找名为 "ts" 的温度传感器设备。
 * 2. 打开设备，并确保设备成功初始化。
 * 3. 通过 rt_device_read 接口读取温度数据：
 *    - 每次读取的数据类型为 double；
 *    - 读取操作执行 5 次，以连续获取温度值；
 *    - 每次读取后打印温度值，格式为 "Temperature = XX.XX C"。
 * 4. 读取完成后，关闭设备并释放申请的内存。
 *
 * 硬件说明：
 * - 本测试基于 K230-01studio 开发板；
 * - 温度传感器为板载设备；
 * - 驱动已将硬件寄存器读取的原始 ADC 值转换为摄氏度的 double 值；
 * - 测试过程中，可在串口终端实时观察温度变化。
 */

#define TS_DEV_NAME               "ts"
rt_device_t ts_dev = RT_NULL;

static void test_ts_read(void)
{
    rt_uint32_t reval;
    rt_uint32_t cnt;
    rt_err_t ret = RT_EOK;
    double temp = 0;
    ts_dev = (rt_device_t)rt_device_find(TS_DEV_NAME);
    uassert_not_null(ts_dev);
    ret = rt_device_open(ts_dev, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(ret, RT_EOK);

    for(cnt = 0; cnt < 5; cnt++)
    {
        reval = rt_device_read(ts_dev, 0, &temp, sizeof(double));
        uassert_true(reval > 0);
        LOG_I("Temperature = %.2f C\n", temp);
        rt_thread_mdelay(1000);
    }
    rt_device_close(ts_dev);
}

static void test_ts_control(void)
{
    rt_err_t ret = RT_EOK;
    uint8_t val;

    ts_dev = (rt_device_t)rt_device_find(TS_DEV_NAME);
    uassert_not_null(ts_dev);
    ret = rt_device_open(ts_dev, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(ret, RT_EOK);

    /* SET_MODE */
    val = 1;
    ret = rt_device_control(ts_dev, RT_DEVICE_TS_CTRL_SET_MODE, &val);
    uassert_int_equal(ret, RT_EOK);

    /* GET_MODE */
    val = 0xFF;
    ret = rt_device_control(ts_dev, RT_DEVICE_TS_CTRL_GET_MODE, &val);
    uassert_int_equal(ret, RT_EOK);
    LOG_I("Current MODE = %d\n", val);

    /* SET_TRIM */
    val = 2;
    ret = rt_device_control(ts_dev, RT_DEVICE_TS_CTRL_SET_TRIM, &val);
    uassert_int_equal(ret, RT_EOK);

    /* GET_TRIM */
    val = 0xFF;
    ret = rt_device_control(ts_dev, RT_DEVICE_TS_CTRL_GET_TRIM, &val);
    uassert_int_equal(ret, RT_EOK);
    LOG_I("Current TRIM = %d\n", val);

    rt_device_close(ts_dev);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_ts_read);
    UTEST_UNIT_RUN(test_ts_control);
}
UTEST_TC_EXPORT(testcase, "ts", utest_tc_init, utest_tc_cleanup, 100);