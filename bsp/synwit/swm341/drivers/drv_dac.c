/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-10     lik          first version
 */

#include "drv_dac.h"

#ifdef BSP_USING_DAC

//#define DRV_DEBUG
#define LOG_TAG "drv.dac"
#include <drv_log.h>

static struct rt_dac_device swm_dac_device;

static rt_err_t swm_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);

    if (channel != 0)
    {
        LOG_E("dac channel must be 0.");
        return -RT_ERROR;
    }
    DAC_Open(DAC);

    return RT_EOK;
}

static rt_err_t swm_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);

    if (channel != 0)
    {
        LOG_E("dac channel must be 0.");
        return -RT_ERROR;
    }
    DAC_Close(DAC);

    return RT_EOK;
}

static rt_err_t swm_dac_convert(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    if (channel != 0)
    {
        LOG_E("dac channel must be 0.");
        return -RT_ERROR;
    }

    DAC->DHR = *value;
    while(DAC->SR & DAC_SR_DHRFULL_Msk) __NOP();

    return RT_EOK;
}

static const struct rt_dac_ops swm_dac_ops =
    {
        .disabled = swm_dac_disabled,
        .enabled = swm_dac_enabled,
        .convert = swm_dac_convert,
};

int swm_dac_init(void)
{
    int result = RT_EOK;

    PORT_Init(PORTD, PIN2, PORTD_PIN2_DAC_OUT, 0);

    DAC_Init(DAC, DAC_FORMAT_LSB12B);

    SYS->DACCR &= ~SYS_DACCR_VRADJ_Msk;
    SYS->DACCR |= (17 << SYS_DACCR_VRADJ_Pos);

    /* register dac device */
    result = rt_hw_dac_register(&swm_dac_device, "dac", &swm_dac_ops, RT_NULL);
    if(result != RT_EOK)
    {
        LOG_E("dac register fail.");
    }
    else
    {
        LOG_D("dac register success.");
    }

    return result;
}
INIT_DEVICE_EXPORT(swm_dac_init);

#endif /* BSP_USING_DAC */
