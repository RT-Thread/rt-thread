/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     Mr.Tiger     first version
 */

#include "drv_config.h"
#ifdef RT_USING_ADC

#define DRV_DEBUG
#define DBG_TAG              "drv.adc"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

struct ra_adc_map ra_adc[] =
{
#ifdef BSP_USING_ADC0
    {
      .device_name = "adc0",
      .g_cfg = &g_adc0_cfg,
      .g_ctrl = &g_adc0_ctrl,
      .g_channel_cfg = &g_adc0_channel_cfg,
    },
#endif
#ifdef BSP_USING_ADC1
    {
      .device_name = "adc1",
      .g_cfg = &g_adc1_cfg,
      .g_ctrl = &g_adc1_ctrl,
      .g_channel_cfg = &g_adc1_channel_cfg,
    },
#endif
};

static struct rt_adc_dev adc_obj[sizeof(ra_adc) / sizeof(ra_adc[0])] = {0};

static rt_err_t ra_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_adc_map *adc = (struct ra_adc_map *)device->parent.user_data;
    /**< start adc*/
    if (enabled)
    {
        if (FSP_SUCCESS != R_ADC_ScanStart((adc_ctrl_t *)adc->g_ctrl))
        {
            LOG_E("start %s failed.", adc->device_name);
            return -RT_ERROR;
        }
    }
    else
    {
        /**< stop adc*/
        if (FSP_SUCCESS != R_ADC_ScanStop((adc_ctrl_t *)adc->g_ctrl))
        {
            LOG_E("stop %s failed.", adc->device_name);
            return -RT_ERROR;
        }
    }
    return RT_EOK;
}

rt_err_t ra_adc_close(struct rt_adc_device *device)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_adc_map *adc = (struct ra_adc_map *)device->parent.user_data;
    if (FSP_SUCCESS != R_ADC_Close((adc_ctrl_t *)adc->g_ctrl))
    {
        LOG_E("close %s failed.", adc->device_name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t ra_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_adc_map *adc = (struct ra_adc_map *)device->parent.user_data;
    if (RT_EOK != R_ADC_Read32((adc_ctrl_t *)adc->g_ctrl, channel, value))
    {
        LOG_E("get adc value failed.\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static const struct rt_adc_ops ra_adc_ops =
{
    .enabled = ra_adc_enabled,
    .convert = ra_get_adc_value,
};

static int ra_adc_init(void)
{
    rt_err_t result = 0;
    rt_size_t obj_num = sizeof(adc_obj) / sizeof(struct rt_adc_dev);

    for (int i = 0; i < obj_num; i++)
    {
        /* init ADC object */
        result = R_ADC_Open((adc_ctrl_t *)ra_adc[i].g_ctrl, ra_adc[i].g_cfg);

        result = R_ADC_ScanCfg((adc_ctrl_t *)ra_adc[i].g_ctrl, ra_adc[i].g_channel_cfg);

        /* register ADC device */
        if(rt_hw_adc_register(&adc_obj[i].adc_device,
                                       ra_adc[i].device_name,
                                       &ra_adc_ops,
                                       &ra_adc[i]) == RT_EOK)
        {
            LOG_D("%s init success", ra_adc[i].device_name);
        }
        else
        {
            LOG_E("%s register failed", ra_adc[i].device_name);
            result = -RT_ERROR;
        }
        RT_ASSERT(result == RT_EOK);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(ra_adc_init);
#endif
