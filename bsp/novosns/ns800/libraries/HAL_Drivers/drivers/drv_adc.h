/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-30     NinoC137     add NS800 ADC driver
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>

#ifdef __ADC_H__
    #undef __ADC_H__
#endif
#include "adc.h"
#ifdef __ADC_H__
    #undef __ADC_H__
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
    ADC外设相关配置
    该芯片单个ADC单元支持32个通道与SoC
    同时，共有4个Int模块与4个PPB模块
*/
#define NS800_ADC_CHANNEL_MAX       32U
#define NS800_ADC_SOC_MAX           32U
#define NS800_ADC_INT_MAX           4U
#define NS800_ADC_PPB_MAX           4U

/*
    ADC Int模块的序列号掩码
*/
#define NS800_ADC_INT1              0U
#define NS800_ADC_INT2              1U
#define NS800_ADC_INT3              2U
#define NS800_ADC_INT4              3U

/*
    ADC PPB模块的序列号掩码
*/
#define NS800_ADC_PPB1              0U
#define NS800_ADC_PPB2              1U
#define NS800_ADC_PPB3              2U
#define NS800_ADC_PPB4              3U

/*
    ADC PPB模块的功能配置
    PPB模块支持：
    1. 超上限检测
    2. 超下限检测
    3. 过零检测
    4. oversampling
*/
#define NS800_ADC_PPB_EVT_TRIPHI    0x0001U
#define NS800_ADC_PPB_EVT_TRIPLO    0x0002U
#define NS800_ADC_PPB_EVT_ZERO      0x0004U
#define NS800_ADC_PPB_EVT_ALL       (NS800_ADC_PPB_EVT_TRIPHI | NS800_ADC_PPB_EVT_TRIPLO | NS800_ADC_PPB_EVT_ZERO)

/*
    ADC的控制指令
 */
#define NS800_ADC_CMD_DISABLE_EXT   (RT_DEVICE_CTRL_BASE(ADC) + 0x10)
#define NS800_ADC_CMD_ENABLE_PPB    (RT_DEVICE_CTRL_BASE(ADC) + 0x11)
#define NS800_ADC_CMD_ENABLE_IRQ    (RT_DEVICE_CTRL_BASE(ADC) + 0x12)
#define NS800_ADC_CMD_SET_CALLBACK  (RT_DEVICE_CTRL_BASE(ADC) + 0x13)

/* 注意：务必确保在调用adc中断之前已正确初始化全局中断向量表 */
typedef void (*ns800_adc_irq_callback_t)(void *user_data);

struct ns800_adc_callback
{
    ns800_adc_irq_callback_t callback;
    void *user_data;
};

int rt_hw_adc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_ADC_H__ */
