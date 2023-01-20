/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                 Notes
 * 2022-07-28     rtthread qiu       first version
 */
#include "drv_dac.h"
#include "drv_common.h"
#include <rtthread.h>

#if defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2)

#define LOG_TAG "drv.dac"
#include <drv_log.h>

struct cyp_dac
{
    cy_stc_csdidac_config_t cyhal_dac_device;
    struct rt_dac_device cyp_dac_device;
    char *name;
};

static struct cyp_dac dac_config[] =
    {
#ifdef BSP_USING_DAC1
        DAC1_CONFIG,
#endif
#ifdef BSP_USING_DAC2
        DAC2_CONFIG,
#endif

};

/*get dac channel*/
static rt_uint32_t cyp_dac_get_channel(rt_uint32_t channel)
{
    rt_uint32_t cyp_dac_channel = 0;

    switch (channel)
    {
    case 1:
        cyp_dac_channel = CY_CSDIDAC_A;
        break;
    case 2:
        cyp_dac_channel = CY_CSDIDAC_B;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    return cyp_dac_channel;
}

struct cyp_dac cyp_adc_obj[sizeof(dac_config) / sizeof(dac_config[0])];

cy_stc_csdidac_context_t csdidac_context;

/*dac device enable*/
static rt_err_t cyp_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    cy_rslt_t result;

    rt_uint32_t cyp_channel;

    RT_ASSERT(device != RT_NULL);

    cyhal_dac_t *dac_device;

    dac_device = device->parent.user_data;

    /* get current dac channel*/
    cyp_channel = cyp_dac_get_channel(channel);

    /*DAC device init*/
    result = Cy_CSDIDAC_Init(&CSDIDAC_csdidac_config, &csdidac_context);

    if (result != RT_EOK)
    {
        LOG_E("Cy_CSDIDAC_Init fail = %d\n", result);
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

/*dac device disable*/
static rt_err_t cyp_dac_disable(struct rt_dac_device *device, rt_uint32_t channel)
{
    rt_uint32_t cyp_channel;

    cy_rslt_t result;

    RT_ASSERT(device != RT_NULL);

    cyhal_dac_t *dac_device;

    dac_device = device->parent.user_data;

    cyp_channel = cyp_dac_get_channel(channel);

    /*DAC free device*/
    result = Cy_CSDIDAC_OutputDisable(cyp_channel, &csdidac_context);
    if (result != RT_EOK)
    {
        LOG_E("DAC Outputdisable failed. Error: %d\n", result);
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

/*set dac output value*/
static rt_err_t cyp_adc_convert(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);

    cy_rslt_t result;

    rt_uint32_t cyp_channel;

    cyp_channel = cyp_dac_get_channel(channel);

    result = Cy_CSDIDAC_OutputEnable(cyp_channel, *value, &csdidac_context);
    if (result != RT_EOK)
    {
        LOG_E("DAC  channel initialization failed. Error: %d\n", result);
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static const struct rt_dac_ops cyp_dac_ops =
{
    .disabled = cyp_dac_disable,
    .enabled = cyp_dac_enabled,
    .convert = cyp_adc_convert,
};

/*dac device init*/
static int rt_hw_dac_init(void)
{
    int result = RT_EOK;

    /* save dac name */
    char name_buf[5] = {'d', 'a', 'c', '0', 0};

    int i = 0;

    i = sizeof(dac_config) / sizeof(dac_config[0]);

    for (i = 0; i < sizeof(dac_config) / sizeof(dac_config[0]); i++)
    {

#ifdef BSP_USING_DAC1
        name_buf[3] = '1';
#endif

#ifdef BSP_USING_DAC2
        name_buf[3] = '2';
#endif
        /* register DAC device */
        if (rt_hw_dac_register(&cyp_adc_obj[i].cyp_dac_device, name_buf, &cyp_dac_ops, RT_NULL) == RT_EOK)
        {
            LOG_E("dac device register success\n");
        }
        else
        {
            LOG_E("dac device register fail\n");
            result = -RT_ERROR;
        }
    }
    return result;
}

INIT_BOARD_EXPORT(rt_hw_dac_init);

#endif /* BSP_USING_DAC1 /BSP_USING_DAC2 */
