/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 * 2026-06-09     li.mengmeng      port for N32H7xx
 * 2026-08-28     FUNMSAN          add N32H47_48x and N32H49x support
 */

#include <board.h>
#include <rtthread.h>

#if defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2) ||                                                                 \
    (defined(SOC_SERIES_N32H47x_48x) && (defined(BSP_USING_DAC3) || defined(BSP_USING_DAC4) ||                            \
                                         defined(BSP_USING_DAC5) || defined(BSP_USING_DAC6) || defined(BSP_USING_DAC7) || \
                                         defined(BSP_USING_DAC8)))

#if defined(SOC_SERIES_N32H7xx)
#include "n32h7xx_rcc.h"
#include "n32h7xx_dac.h"
#elif defined(SOC_SERIES_N32H47x_48x)
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_dac.h"
#elif defined(SOC_SERIES_N32H49x)
#include "n32h49x_rcc.h"
#include "n32h49x_dac.h"
#endif

#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG "drv.dac"
#include <drv_log.h>

typedef struct
{
    DACX DACx;
    DAC_Module *DAC_Module;
    uint32_t periph_clk;
    void (*EnablePeriphClk)(uint32_t periph, FunctionalState cmd);
    uint32_t DAC_clk_pres;

    GPIO_Module *GPIOx;
    uint16_t GPIO_Pin;
    uint32_t GPIO_RCC;

    DAC_InitType Init;
} DAC_InitInfo_t;

static DAC_InitInfo_t dac_config[] = {
#ifdef BSP_USING_DAC1
    DAC1_CONFIG,
#endif

#ifdef BSP_USING_DAC2
    DAC2_CONFIG,
#endif

#if defined(SOC_SERIES_N32H47x_48x)
#ifdef BSP_USING_DAC3
    DAC3_CONFIG,
#endif

#ifdef BSP_USING_DAC4
    DAC4_CONFIG,
#endif

#ifdef BSP_USING_DAC5
    DAC5_CONFIG,
#endif

#ifdef BSP_USING_DAC6
    DAC6_CONFIG,
#endif

#ifdef BSP_USING_DAC7
    DAC7_CONFIG,
#endif

#ifdef BSP_USING_DAC8
    DAC8_CONFIG,
#endif
#endif /* SOC_SERIES_N32H47x_48x */
};

struct n32_dac
{
    DAC_InitInfo_t DAC_Info;
    struct rt_dac_device n32_dac_device;
};

static struct n32_dac n32_dac_obj[sizeof(dac_config) / sizeof(dac_config[0])];

static rt_err_t n32_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    DAC_InitInfo_t *n32_dac_info;

    RT_ASSERT(device != RT_NULL);
    n32_dac_info = device->parent.user_data;

    /* Enable DAC */
    DAC_Enable(n32_dac_info->DACx, ENABLE);

    return RT_EOK;
}

static rt_err_t n32_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    DAC_InitInfo_t *n32_dac_info;

    RT_ASSERT(device != RT_NULL);
    n32_dac_info = device->parent.user_data;

    /* Disable DAC */
    DAC_Enable(n32_dac_info->DACx, DISABLE);

    return RT_EOK;
}

static rt_uint8_t n32_dac_get_resolution(struct rt_dac_device *device)
{
    RT_ASSERT(device != RT_NULL);

    /* N32H7xx and N32H47x/48x DACs support 12-bit resolution */
    return 12;
}

static rt_err_t n32_set_dac_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_uint16_t set_value;
    DAC_InitInfo_t *n32_dac_info;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    n32_dac_info = device->parent.user_data;

    set_value = (rt_uint16_t)(*value);
    if (set_value > 4095)
    {
        set_value = 4095;
    }

    /* Set DAC output data (12-bit right-aligned) */
    DAC_SetData(n32_dac_info->DACx, DAC_ALIGN_R_12BIT, set_value);

    /* Trigger software conversion */
    DAC_SoftTrgEnable(n32_dac_info->DACx, ENABLE);

    return RT_EOK;
}

static const struct rt_dac_ops n32_dac_ops = {
    .disabled = n32_dac_disabled,
    .enabled = n32_dac_enabled,
    .convert = n32_set_dac_value,
    .get_resolution = n32_dac_get_resolution,
};

static int n32_dac_init(void)
{
    int result = RT_EOK;
    char name_buf[5] = { 'd', 'a', 'c', '0', 0 };
    int i = 0;

    for (i = 0; i < sizeof(dac_config) / sizeof(dac_config[0]); i++)
    {
        n32_dac_obj[i].DAC_Info = dac_config[i];

        /* Set device name */
        name_buf[3] = '0';
        if (n32_dac_obj[i].DAC_Info.DACx == DAC1)
        {
            name_buf[3] = '1';
        }
        else if (n32_dac_obj[i].DAC_Info.DACx == DAC2)
        {
            name_buf[3] = '2';
        }
#if defined(SOC_SERIES_N32H47x_48x)
        else if (n32_dac_obj[i].DAC_Info.DACx == DAC3)
        {
            name_buf[3] = '3';
        }
        else if (n32_dac_obj[i].DAC_Info.DACx == DAC4)
        {
            name_buf[3] = '4';
        }
        else if (n32_dac_obj[i].DAC_Info.DACx == DAC5)
        {
            name_buf[3] = '5';
        }
        else if (n32_dac_obj[i].DAC_Info.DACx == DAC6)
        {
            name_buf[3] = '6';
        }
        else if (n32_dac_obj[i].DAC_Info.DACx == DAC7)
        {
            name_buf[3] = '7';
        }
        else if (n32_dac_obj[i].DAC_Info.DACx == DAC8)
        {
            name_buf[3] = '8';
        }
#endif /* SOC_SERIES_N32H47x_48x */

        /* Enable DAC peripheral clock */
        n32_dac_obj[i].DAC_Info.EnablePeriphClk(n32_dac_obj[i].DAC_Info.periph_clk, ENABLE);
        /* Config DAC12 prescaler factor,DAC_CLK = 1M*/
        DAC_ConfigClkPrescaler(n32_dac_obj[i].DAC_Info.DAC_Module, n32_dac_obj[i].DAC_Info.DAC_clk_pres);

#if defined(SOC_SERIES_N32H7xx) || defined(SOC_SERIES_N32H49x)
        DAC_SetHighFrequencyMode(n32_dac_obj[i].DAC_Info.DAC_Module, DAC_HIGH_FREQ_MODE_BELOW_160M);
#elif defined(SOC_SERIES_N32H47x_48x)
        /* The high-frequency mode field is only available for DAC1~DAC4. */
        if ((n32_dac_obj[i].DAC_Info.DAC_Module == DAC12) ||
            (n32_dac_obj[i].DAC_Info.DAC_Module == DAC34))
        {
            DAC_SetHighFrequencyMode(n32_dac_obj[i].DAC_Info.DAC_Module, DAC_HIGH_FREQ_MODE_BELOW_160M);
        }
#endif
        /* Initialize DAC */
        DAC_Init(n32_dac_obj[i].DAC_Info.DACx, &n32_dac_obj[i].DAC_Info.Init);

        /* Register DAC device */
        if (rt_hw_dac_register(&n32_dac_obj[i].n32_dac_device, name_buf, &n32_dac_ops, &n32_dac_obj[i].DAC_Info) == RT_EOK)
        {
            LOG_D("%s init success", name_buf);
        }
        else
        {
            LOG_E("%s register failed", name_buf);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(n32_dac_init);

#endif /* BSP_USING_DACx */

