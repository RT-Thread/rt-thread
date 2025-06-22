/* Copyright 2020 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>
#include "../interdrv/adc/drv_adc.h"
#include "utest.h"

/*
 * 测试 ADC 驱动的读操作
 * 1. 查找 ADC 设备。
 * 2. 启用 ADC 设备。
 * 3. 启用每个 ADC 通道并读取其值。
 * 4. 验证读取的值在预期范围内。
 * 5. 禁用每个 ADC 通道并验证读取值为 0。
 *
 * 本测试基于 01Studio 开发板，该开发板自带排针，并引出 SoC 的以下 4 个 ADC 通道
 * 板级排针编号 | SoC 的 ADC 通道编号 | 输入电压范围
 * -------------+---------------------+-------------
 * 32           | ADC0                | (0 ~ 3.6V)
 * 36           | ADC1                | (0 ~ 3.6V)
 * 38           | ADC2                | (0 ~ 1.8V)
 * 40           | ADC3                | (0 ~ 1.8V)
 * SoC 的 ADC 通道默认只支持最大 1.8V 的输入电压，对于 ADC0 和 ADC1 通道，开发板
 * 通过增加功放将最大支持电压提升到 3.6V（而且同样采用了分压机制，导致实际 ADC
 * 通道的输入电压只有板级排针电压的一半）。
 *
 * 测试时注意连接输入的最大电压不要超过额定值，否则可能会损坏 ADC 通道。
 *
 * 另外注意这个adc 只有 12bit，所以读取的值范围是 0 ~ 4095
 *
 * 具体测试最大 1.8V 的 ADC 通道（譬如 38/40）时，可以自己通过两个 10K 欧姆的电
 * 阻将模拟输入从 3.3V 分压（将可调电阻调制最大时万用表实测 A 点电压为 1.69V 左右）：
 *          +----------+    +---------------+
 * 3.3V ----| 10K 欧姆 |----| 可调 10K 欧姆 |---- 接地
 *          +----------+    +---------------+
 *                                  A
 *                                  |
 *                              ADC2/ADC3
 *
 * 具体测试最大 3.6V 的 ADC 通道（譬如 32/36）时，可以直接引入 3.3V。
 *                          +---------------+
 * 3.3V --------------------| 可调 10K 欧姆 |---- 接地
 *                          +---------------+
 *                                  A
 *                                  |
 *                              ADC0/ADC1
 */
static void test_read(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    rt_uint32_t value, vol;
    rt_adc_device_t adc_dev;

    adc_dev = (rt_adc_device_t)rt_device_find(K230_ADC_NAME);
    uassert_not_null(adc_dev);

    ret = rt_adc_enable(adc_dev, 0);
    uassert_int_equal(ret, RT_EOK);

    for (i = 0; i < 4; i++)
    {
        ret = rt_adc_enable(adc_dev, i);
        uassert_int_equal(ret, RT_EOK);

        value = rt_adc_read(adc_dev, i);
        /* 转换为对应电压值,对应 12 位 ADC 最大值 4095, 内部基准最大电压值 1.8V，数据精度乘以 100 保留 2 位小数 */
        vol = value * 180 / 4095;
        if (i == 0 || i == 1)
            vol = vol * 2; /* ADC0/ADC1 分压后实际电压是输入电压的二分之一 */

        LOG_I("ADC chan[%d] read value: %d, calculated voltage is: %d.%02dV\n",
              i, value, vol / 100, vol % 100);
    }

    for (i = 0; i < ADC_MAX_CHANNEL; i++)
    {
        ret = rt_adc_disable(adc_dev, i);
        uassert_int_equal(ret, RT_EOK);

        value = rt_adc_read(adc_dev, i);
        uassert_int_equal(value, 0);
    }

    return;
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
    UTEST_UNIT_RUN(test_read);
}
UTEST_TC_EXPORT(testcase, "adc", utest_tc_init, utest_tc_cleanup, 100);