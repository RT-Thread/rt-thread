/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     Mr.Tiger     first version
 */

#include "drv_config.h"
#ifdef RT_USING_ADC

// #define DRV_DEBUG
#define DBG_TAG              "drv.adc"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

struct ra_adc_map ra_adc[] =
{
#if defined(BSP_USING_ADC0)
    {'0', &g_adc0_cfg, &g_adc0_ctrl, &g_adc0_channel_cfg},
#endif

#if defined(BSP_USING_ADC1)
    {'1', &g_adc1_cfg, &g_adc1_ctrl, &g_adc1_channel_cfg},
#endif
};

#if defined(BSP_USING_ADC0)
struct rt_adc_device adc0_device;
struct ra_dev _ra_adc0_device = {.ra_adc_device_t = &adc0_device, .ra_adc_dev = &ra_adc[0]};
#endif

#if defined(BSP_USING_ADC1)
struct rt_adc_device adc1_device;
struct ra_dev _ra_adc1_device = {.ra_adc_device_t = &adc1_device, .ra_adc_dev = &ra_adc[1]};
#endif

static rt_err_t ra_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_adc_map *adc = (struct ra_adc_map *)device->parent.user_data;
    /**< start adc*/
    if (enabled)
    {
        if (FSP_SUCCESS != R_ADC_ScanStart((adc_ctrl_t *)adc->g_ctrl))
        {
            LOG_E("start adc%c failed.", adc->name);
            return -RT_ERROR;
        }
    }
    else
    {
        /**< stop adc*/
        if (FSP_SUCCESS != R_ADC_ScanStop((adc_ctrl_t *)adc->g_ctrl))
        {
            LOG_E("stop adc%c failed.", adc->name);
            return -RT_ERROR;
        }
    }
    return RT_EOK;
}

rt_err_t ra_adc_close(struct rt_adc_device *device)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_adc_map *adc = (struct ra_adc_map *)(struct ra_adc_map *)device->parent.user_data;
    if (FSP_SUCCESS != R_ADC_Close((adc_ctrl_t *)adc->g_ctrl))
    {
        LOG_E("close adc%c failed.", adc->name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t ra_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
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
#if defined(BSP_USING_ADC0)
    R_ADC_Open((adc_ctrl_t *)_ra_adc0_device.ra_adc_dev->g_ctrl,
               (adc_cfg_t const * const)_ra_adc0_device.ra_adc_dev->g_cfg);

    R_ADC_ScanCfg((adc_ctrl_t *)_ra_adc0_device.ra_adc_dev->g_ctrl,
                  (adc_cfg_t const * const)_ra_adc0_device.ra_adc_dev->g_channel_cfg);

    if (RT_EOK != rt_hw_adc_register(_ra_adc0_device.ra_adc_device_t, "adc0", &ra_adc_ops, (void *)_ra_adc0_device.ra_adc_dev))
    {
        LOG_E("adc0 register failed");
        return -RT_ERROR;
    }
#endif

#if defined(BSP_USING_ADC1)
    R_ADC_Open((adc_ctrl_t *)_ra_adc1_device.ra_adc_dev->g_ctrl,
               (adc_cfg_t const * const)_ra_adc1_device.ra_adc_dev->g_cfg);

    R_ADC_ScanCfg((adc_ctrl_t *)_ra_adc1_device.ra_adc_dev->g_ctrl,
                  (adc_cfg_t const * const)_ra_adc1_device.ra_adc_dev->g_channel_cfg);

    if (RT_EOK != rt_hw_adc_register(_ra_adc1_device.ra_adc_device_t, "adc1", &ra_adc_ops, (void *)_ra_adc1_device.ra_adc_dev))
    {
        LOG_E("adc1 register failed");
        return -RT_ERROR;
    }
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(ra_adc_init);
#endif
