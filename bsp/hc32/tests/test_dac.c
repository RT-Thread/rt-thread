/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单： DAC 设备使用例程
 * 例程导出了 dac_vol_sample 命令到控制终端
 * 命令调用格式：dac_vol_sample  参数1：dac1 | dac2  参数2：DAC配置值 （可选，范围0-4095），默认1365≈1.1V
 * 程序功能：通过 DAC 设备将数字值转换为模拟量，并输出电压值。将示波器通道连接到输出引脚，观察输出电压值
 *          示例代码参考电压为3.3V,转换位数为12位。
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

#ifdef BSP_USING_DAC

#define REFER_VOLTAGE                   330     /* 参考电压 3.3V,数据精度乘以100保留2位小数*/
#define DAC_MAX_OUTPUT_VALUE            4095

static int dac_vol_sample(int argc, char *argv[])
{
    char dac_device_name[] = "dac1";
    rt_uint8_t channel = 1;
    rt_dac_device_t dac_dev;
    rt_uint32_t value = 1365; /* 默认1.1V */
    rt_uint32_t convertBits;
    rt_uint32_t vol;
    rt_err_t ret = RT_EOK;

    /* 参数无输入或者输入错误按照默认值处理 */
    if (argc >= 2)
    {
        if (0 == rt_strcmp(argv[1], "dac1"))
        {
            rt_strcpy(dac_device_name, "dac1");
        }
#if defined (HC32F4A0) || defined (HC32F472)
        else if (0 == rt_strcmp(argv[1], "dac2"))
        {
            rt_strcpy(dac_device_name, "dac2");
        }
#endif
#if defined (HC32F472)
        else if (0 == rt_strcmp(argv[1], "dac3"))
        {
            rt_strcpy(dac_device_name, "dac3");
        }
        else if (0 == rt_strcmp(argv[1], "dac4"))
        {
            rt_strcpy(dac_device_name, "dac4");
        }
#endif
        else
        {
            rt_kprintf("The chip hasn't the dac unit!\r\n");
            return -RT_ERROR;
        }
    }

    /* 查找设备 */
    dac_dev = (rt_dac_device_t)rt_device_find(dac_device_name);
    if (dac_dev == RT_NULL)
    {
        rt_kprintf("dac sample run failed! can't find %s device!\n", dac_device_name);
        return -RT_ERROR;
    }

    if (RT_EOK != rt_device_control(&dac_dev->parent, RT_DAC_CMD_GET_RESOLUTION, &convertBits))
    {
        rt_kprintf("dac sample can't read resolution!\n");
        return -RT_ERROR;
    }
    convertBits = (1 << (rt_uint8_t)convertBits);
    for (channel = 1; channel < 3; channel++)
    {
        /* 打开通道 */
        ret = rt_dac_enable(dac_dev, channel);
        /* 设置输出值 */
        if (argc >= 3)
        {
            value = atoi(argv[2]);
            if (value > DAC_MAX_OUTPUT_VALUE)
            {
                rt_kprintf("invalid dac value!!! \n");
                return -RT_ERROR;
            }
        }
        rt_dac_write(dac_dev, channel, value);
        rt_kprintf("%s CH%d Value is :%d \n", dac_device_name, channel, value);
        /* 转换为对应电压值 */
        vol = value * REFER_VOLTAGE / convertBits;
        rt_kprintf("%s CH%d Voltage is :%d.%02dV \n", dac_device_name, channel, vol / 100, vol % 100);
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(dac_vol_sample, dac voltage convert sample < dac1 | dac2  value >);
#endif
