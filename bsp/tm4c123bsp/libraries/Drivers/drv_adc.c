/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#include "drv_adc.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"

#ifdef  RT_USING_ADC
#include "adc_config.h"
#include "tm4c123_config.h"
#include <string.h>

#define LOG_TAG             "drv.adc"
#include <drv_log.h>

static struct tm4c123_adc_config adc_config[] =
{
#ifdef BSP_USING_ADC0
    ADC0_CONFIG,
#endif
#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif
};

struct tm4c123_adc
{
    struct tm4c123_adc_config *config;
    struct rt_adc_device adc_device;
};

static struct tm4c123_adc   adc_obj[sizeof(adc_config) / sizeof(adc_config[0])] = {0};

static rt_err_t tm4c123_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    RT_ASSERT(device != RT_NULL);
    struct tm4c123_adc_config   *config = (struct tm4c123_adc_config *)device->parent.user_data;

    if (enabled)
    {
        ADCSequenceEnable(config->adcbase, config->sequence);
        ADCIntClear(config->adcbase, config->sequence);
    }
    else
    {
        ADCSequenceDisable(config->adcbase, config->sequence);
    }
    return RT_EOK;
}

static rt_err_t tm4c123_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    uint32_t    pui32ADC0Value[4] = {0};
    struct tm4c123_adc_config   *config = (struct tm4c123_adc_config *)device->parent.user_data;

    /* Trigger the ADC conversion. */
    ADCProcessorTrigger(config->adcbase, config->sequence);

    while (!ADCIntStatus(config->adcbase, config->sequence, false))
    {
    }

    /* Clear the ADC interrupt flag. */
    ADCIntClear(config->adcbase, config->sequence);

    /* Read ADC Value. */
    ADCSequenceDataGet(config->adcbase, config->sequence, pui32ADC0Value);

    /* get ADC value */
    *value = (rt_uint32_t)pui32ADC0Value[channel];

    return RT_EOK;
}

static const struct rt_adc_ops tm4c123_adc_ops =
{
    .enabled = tm4c123_adc_enabled,
    .convert = tm4c123_get_adc_value,
};


static rt_err_t tm4c123_hw_adc_init(struct tm4c123_adc *device)
{

    uint32_t  adcbase = device->config->adcbase;
    uint32_t  sequencenum = device->config->sequence;

    ADCSequenceConfigure(adcbase, sequencenum,
                         device->config->trigermode, 0);

    ADCSequenceStepConfigure(adcbase, sequencenum, 0, ADC_CTL_CH7);
    ADCSequenceStepConfigure(adcbase, sequencenum, 1, ADC_CTL_CH6 | ADC_CTL_IE);
    ADCSequenceStepConfigure(adcbase, sequencenum, 2, ADC_CTL_CH5);
    /*Tell the ADC logic
      that this is the last conversion on sequence 3 (ADC_CTL_END). */
    ADCSequenceStepConfigure(adcbase, sequencenum, 3, ADC_CTL_CH4 | ADC_CTL_IE |
                             ADC_CTL_END);
    return RT_EOK;
}


static int tm4c123_adc_init(void)
{
    int i = 0;
    rt_size_t obj_num = sizeof(adc_obj) / sizeof(struct tm4c123_adc);
    rt_err_t result = RT_EOK;

    adc_hw_config();

    for (i = 0; i < obj_num; i++)
    {
        /* ADC init */
        adc_obj[i].config = &adc_config[i];


        if (tm4c123_hw_adc_init(&adc_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", adc_obj[i].config->name);
            result = -RT_ERROR;
            return result;
        }
        else
        {
            LOG_D("%s init success", adc_obj[i].config->name);

            /* register adc device */
            if (rt_hw_adc_register(&adc_obj[i].adc_device, adc_obj[i].config->name, &tm4c123_adc_ops, &adc_config[i]) == RT_EOK)
            {
                LOG_D("%s register success", adc_obj[i].config->name);
            }
            else
            {
                LOG_E("%s register failed", adc_obj[i].config->name);
                result = -RT_ERROR;
            }
        }
    }

    return result;
}
INIT_APP_EXPORT(tm4c123_adc_init);

#endif  /*RT_UING_ADC*/

/************************** end of file ******************/