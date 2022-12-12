/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     Mr.Tiger     first version
 */

#include <rtthread.h>
#include "drv_config.h"
#ifdef RT_USING_DAC

//#define DRV_DEBUG
#define DBG_TAG              "drv.dac"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

struct ra_dac_map ra_dac[] =
{
#ifdef BSP_USING_DAC0
    {'0', &g_dac0_cfg, &g_dac0_ctrl},
#endif
#ifdef BSP_USING_DAC1
    {'1', &g_dac1_cfg, &g_dac1_ctrl},
#endif
};

#ifdef BSP_USING_DAC0
struct rt_dac_device dac0_device;
struct ra_dac_dev _ra_dac0_device = {.ra_dac_device_t = &dac0_device, .ra_dac_map_dev = &ra_dac[0]};
#endif

#ifdef BSP_USING_DAC1
struct rt_dac_device dac1_device;
struct ra_dac_dev _ra_dac1_device = {.ra_dac_device_t = &dac1_device, .ra_dac_map_dev = &ra_dac[1]};
#endif

rt_err_t ra_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_dac_map *dac = (struct ra_dac_map *)device->parent.user_data;
    if (FSP_SUCCESS != R_DAC_Stop((dac_ctrl_t *)dac->g_ctrl))
    {
        LOG_E("dac%c stop failed.", dac->name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

rt_err_t ra_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_dac_map *dac = (struct ra_dac_map *)device->parent.user_data;
    if (FSP_SUCCESS != R_DAC_Start((dac_ctrl_t *)dac->g_ctrl))
    {
        LOG_E("dac%c start failed.", dac->name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

rt_err_t ra_dac_write(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    struct ra_dac_map *dac = (struct ra_dac_map *)device->parent.user_data;
    if (FSP_SUCCESS != R_DAC_Write((dac_ctrl_t *)dac->g_ctrl, *value))
    {
        LOG_E("dac%c set value failed.", dac->name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

struct rt_dac_ops ra_dac_ops =
{
    .disabled = ra_dac_disabled,
    .enabled  = ra_dac_enabled,
    .convert  = ra_dac_write,
};

static int ra_dac_init(void)
{
#ifdef BSP_USING_DAC0
    _ra_dac0_device.ra_dac_device_t->ops = &ra_dac_ops;
    R_DAC_Open((dac_ctrl_t *)_ra_dac0_device.ra_dac_map_dev->g_ctrl, (dac_cfg_t const *)_ra_dac0_device.ra_dac_map_dev->g_cfg);
    if (FSP_SUCCESS != rt_hw_dac_register(_ra_dac0_device.ra_dac_device_t, "dac0", &ra_dac_ops, (void *)_ra_dac0_device.ra_dac_map_dev))
    {
        LOG_E("dac0 register failed");
        return -RT_ERROR;
    }
#endif

#ifdef BSP_USING_DAC1
    _ra_dac1_device.ra_dac_device_t->ops = &ra_dac_ops;
    R_DAC_Open((dac_ctrl_t *)_ra_dac1_device.ra_dac_map_dev->g_ctrl, (dac_cfg_t const *) _ra_dac1_device.ra_dac_map_dev->g_cfg);
    if (FSP_SUCCESS != rt_hw_dac_register(_ra_dac1_device.ra_dac_device_t, "dac1", &ra_dac_ops, (void *)_ra_dac1_device.ra_dac_map_dev))
    {
        LOG_E("dac1 register failed");
        return -RT_ERROR;
    }
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(ra_dac_init);

#endif
