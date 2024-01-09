/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2023-05-12     CDT                  first version
 */
#include <board.h>

#if defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2)

#include <drivers/dac.h>
#include <drv_dac.h>
#include <drv_config.h>
#include "rtdevice.h"
#include "hc32_ll.h"
#include <drv_log.h>

#if defined(HC32F4A0)
    #define DAC_CHANNEL_ID_MAX              (DAC_CH2 + 1U)
    #define DAC_RESOLUTION                  (12)
    #define DAC_LEFT_ALIGNED_DATA_MASK      (0xFFF0U)
    #define DAC_RIGHT_ALIGNED_DATA_MASK     (0xFFFU)
#endif

typedef struct
{
    struct rt_dac_device rt_dac;
    CM_DAC_TypeDef *instance;
    struct dac_dev_init_params init;
} dac_device;

static dac_device _g_dac_dev_array[] =
{
#ifdef BSP_USING_DAC1
    {
        {0},
        CM_DAC1,
        DAC1_INIT_PARAMS,
    },
#endif
#ifdef BSP_USING_DAC2
    {
        {0},
        CM_DAC2,
        DAC2_INIT_PARAMS,
    },
#endif
};

static rt_uint16_t _dac_get_channel(rt_uint32_t channel)
{
    rt_uint16_t ll_channel = 0;

    switch (channel)
    {
    case  1:
        ll_channel = DAC_CH1;
        break;
    case  2:
        ll_channel = DAC_CH2;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    return ll_channel;
}

static rt_err_t _dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(channel <= DAC_CHANNEL_ID_MAX);

    CM_DAC_TypeDef *p_ll_instance = device->parent.user_data;
    uint16_t ll_channel = _dac_get_channel(channel);

    int32_t result = DAC_Start(p_ll_instance, ll_channel);

    return (result == LL_OK) ? RT_EOK : -RT_ERROR;
}

static rt_err_t _dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(channel <= DAC_CHANNEL_ID_MAX);

    CM_DAC_TypeDef *p_ll_instance = device->parent.user_data;
    uint16_t ll_channel = _dac_get_channel(channel);

    int32_t result = DAC_Stop(p_ll_instance, ll_channel);

    return (result == LL_OK) ? RT_EOK : -RT_ERROR;
}

static rt_uint8_t _dac_get_resolution(struct rt_dac_device *device)
{
    return DAC_RESOLUTION;
}

static rt_err_t _dac_set_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(channel <= DAC_CHANNEL_ID_MAX);
    CM_DAC_TypeDef *p_ll_instance = device->parent.user_data;

    if (READ_REG16_BIT(p_ll_instance->DACR, DAC_DACR_DPSEL) == DAC_DATA_ALIGN_LEFT)
    {
        RT_ASSERT(0U == (*value & ~DAC_LEFT_ALIGNED_DATA_MASK));
    }
    else
    {
        RT_ASSERT(0U == (*value & ~DAC_RIGHT_ALIGNED_DATA_MASK));
    }
    uint16_t ll_channel = _dac_get_channel(channel);
    DAC_SetChData(p_ll_instance, ll_channel, *value);

    return RT_EOK;
}

static const struct rt_dac_ops g_dac_ops =
{
    .disabled = _dac_disabled,
    .enabled  = _dac_enabled,
    .convert  = _dac_set_value,
    .get_resolution = _dac_get_resolution,
};

static void _dac_clock_enable(void)
{
#if defined(BSP_USING_DAC1)
    FCG_Fcg3PeriphClockCmd(PWC_FCG3_DAC1, ENABLE);
#endif
#if defined(BSP_USING_DAC2)
    FCG_Fcg3PeriphClockCmd(PWC_FCG3_DAC2, ENABLE);
#endif
}

extern rt_err_t rt_hw_board_dac_init(CM_DAC_TypeDef *DACx);
int rt_hw_dac_init(void)
{
    int result = RT_EOK;
    rt_err_t ret;
    int i = 0;

    _dac_clock_enable();
    uint32_t dev_cnt = sizeof(_g_dac_dev_array) / sizeof(_g_dac_dev_array[0]);
    for (; i < dev_cnt; i++)
    {

        DAC_DeInit(_g_dac_dev_array[i].instance);
        rt_hw_board_dac_init(_g_dac_dev_array[i].instance);

        ret = rt_hw_dac_register(&_g_dac_dev_array[i].rt_dac, \
                                 (const char *)_g_dac_dev_array[i].init.name, \
                                 &g_dac_ops, (void *)_g_dac_dev_array[i].instance);
        if (ret == RT_EOK)
        {
            LOG_D("%s init success", (const char *)_g_dac_dev_array[i].init.name);
        }
        else
        {
            LOG_E("%s register failed", (const char *)_g_dac_dev_array[i].init.name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_dac_init);

#endif /* BSP_USING_DAC */
