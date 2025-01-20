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
 * 程序清单： ADC 设备使用例程
 * 例程导出了 adc_vol_sample 命令到控制终端
 * 命令调用格式：adc_vol_sample    参数选择：adc1 | adc2 | adc3
 * 程序功能：通过 ADC 设备采样电压值并转换为数值。
 *          示例代码参考电压为3.3V,转换位数为12位。
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "board_config.h"
#include "drv_adc.h"

#ifdef BSP_USING_ADC

#define REFER_VOLTAGE                   3300        /* 参考电压 3.3V,单位mv */
#define CONVERT_BITS                    (1 << 12)   /* 转换位数为12位       */

/* ADC Channel Max */
#if defined (HC32F460)
    #define ADC1_CH_MAX                 (16U)
    #define ADC2_CH_MAX                 (8U)
#elif defined (HC32F472)
    #define ADC1_CH_MAX                 (21U)
    #define ADC2_CH_MAX                 (21U)
    #define ADC3_CH_MAX                 (22U)
#elif defined (HC32F4A0)
    #define ADC1_CH_MAX                 (16U)
    #define ADC2_CH_MAX                 (16U)
    #define ADC3_CH_MAX                 (20U)
#elif defined (HC32F448)
    #define ADC1_CH_MAX                 (16U)
    #define ADC2_CH_MAX                 (8U)
    #define ADC3_CH_MAX                 (12U)
#endif


#if defined(BSP_ADC1_USING_DMA) || defined(BSP_ADC2_USING_DMA) || defined(BSP_ADC3_USING_DMA)

static struct adc_dev_priv_params adc_priv;
static struct adc_dev_dma_priv_ops priv_ops;

/* Timer的配置需与文件 “adc_config.h”中的 ADC1_EOCA_DMA_CONFIG 对应 */
/* 这里使用Timer01 B通道作为ADC的触发源 */
rt_err_t adc_dma_trig_config(void)
{
    stc_tmr0_init_t stcTmr0Init;

#if defined(HC32F460) || defined(HC32F4A0) || defined(HC32F472) || defined(HC32F448)
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR0_1, ENABLE);
#endif
    (void)TMR0_StructInit(&stcTmr0Init);
    (void)TMR0_Init(CM_TMR0_1, TMR0_CH_B, &stcTmr0Init);
    return 0;
}

rt_err_t adc_dma_trig_start(void)
{
    TMR0_SetCountValue(CM_TMR0_1, TMR0_CH_B, 0x0);
    TMR0_SetCompareValue(CM_TMR0_1, TMR0_CH_B, 0x7FFF);
    TMR0_Start(CM_TMR0_1, TMR0_CH_B);
    return 0;
}

rt_err_t adc_dma_trig_stop(void)
{
    TMR0_Stop(CM_TMR0_1, TMR0_CH_B);
    TMR0_ClearStatus(CM_TMR0_1, TMR0_FLAG_CMP_B);
    return 0;
}
#endif

static int adc_vol_sample(int argc, char **argv)
{
    rt_adc_device_t adc_dev;            /* ADC 设备句柄 */
    rt_uint32_t value;
    rt_uint32_t vol;
    rt_uint8_t adc_channel;
    char adc_device[] = "adc1";
    rt_uint8_t adc_max_channel = ADC1_CH_MAX;

    /* 参数无输入或者输入错误按照默认值处理 */
    if (argc == 2)
    {
        if (0 == rt_strcmp(argv[1], "adc1"))
        {
            rt_strcpy(adc_device, "adc1");
            adc_max_channel = ADC1_CH_MAX;
        }
        else if (0 == rt_strcmp(argv[1], "adc2"))
        {
            rt_strcpy(adc_device, "adc2");
            adc_max_channel = ADC2_CH_MAX;
        }
#if defined (HC32F472) || defined (HC32F4A0) || defined (HC32F448)
        else if (0 == rt_strcmp(argv[1], "adc3"))
        {
            rt_strcpy(adc_device, "adc3");
            adc_max_channel = ADC3_CH_MAX;
        }
#endif
        else
        {
            rt_kprintf("The chip hasn't the adc unit!\r\n");
            return -RT_ERROR;
        }
    }

    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(adc_device);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\r\n", adc_device);
        return -RT_ERROR;
    }

#if defined(BSP_ADC1_USING_DMA) || defined(BSP_ADC2_USING_DMA) || defined(BSP_ADC3_USING_DMA)
    /* DMA配置 */
    adc_priv.flag = ADC_USING_EOCA_DMA_FLAG;
    priv_ops.dma_trig_config = &adc_dma_trig_config;
    priv_ops.dma_trig_start  = &adc_dma_trig_start;
    priv_ops.dma_trig_stop   = &adc_dma_trig_stop;
    adc_priv.ops = &priv_ops;
    adc_dev->parent.user_data = &adc_priv;
#endif

    /* 遍历所有通道 */
    for (adc_channel = 0; adc_channel < adc_max_channel; adc_channel++)
    {
        /* 使能设备 */
        rt_adc_enable(adc_dev, adc_channel);
        /* 读取采样值 */
        value = rt_adc_read(adc_dev, adc_channel);
        rt_kprintf("Channel: %d, value is :%d   0x%x\r\n", adc_channel, value, value);
        /* 转换为对应电压值 */
        vol = value * REFER_VOLTAGE / CONVERT_BITS;
        rt_kprintf("Simulate voltage is :%d mv\r\n", vol);
        vol =  rt_adc_voltage(adc_dev, adc_channel);
        rt_kprintf("Read voltage is :%d mv\r\n", vol);
        rt_kprintf("*********************\r\n");
    }
    rt_kprintf("*******The %s all channel have be tested**********\r\n", adc_device);
    return RT_EOK;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(adc_vol_sample, adc convert sample: select < adc1 | adc2 | adc3 >);
#endif
