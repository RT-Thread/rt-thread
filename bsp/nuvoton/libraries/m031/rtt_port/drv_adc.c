/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-9-16       Philo        First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>
#include "NuMicro.h"

#ifdef BSP_USING_ADC

/* Private define ---------------------------------------------------------------*/

/* Private Typedef --------------------------------------------------------------*/
struct nu_adc
{
    struct rt_adc_device dev;
    char *name;
    ADC_T *adc_base;
    int adc_reg_tab;
    int adc_max_ch_num;

};
typedef struct nu_adc *nu_adc_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled);
static rt_err_t nu_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value);

/* Public functions ------------------------------------------------------------*/
int rt_hw_adc_init(void);

/* Private variables ------------------------------------------------------------*/

static struct nu_adc nu_adc_arr [] =
{
#if defined(BSP_USING_ADC0)
    {
        .name = "adc0",
        .adc_base = ADC,
        .adc_max_ch_num = 15,
    },
#endif

    {0}
};

static const struct rt_adc_ops nu_adc_ops =
{
    nu_adc_enabled,
    nu_get_adc_value,
};
typedef struct rt_adc_ops *rt_adc_ops_t;


/* nu_adc_enabled - Enable ADC clock and wait for ready */
static rt_err_t nu_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{

    ADC_T *adc_base = ((nu_adc_t)device)->adc_base;
    int *padc_reg_tab = &((nu_adc_t)device)->adc_reg_tab;
    RT_ASSERT(device != RT_NULL);

    if (channel >= ((nu_adc_t)device)->adc_max_ch_num)
        return -(RT_EINVAL);

    if (enabled)
    {
        ADC_POWER_ON(adc_base);

        if (*padc_reg_tab == 0)
        {
            ADC_Open(adc_base, ADC_ADCR_DIFFEN_SINGLE_END, ADC_ADCR_ADMD_SINGLE, (0x1 << channel));
        }

        *padc_reg_tab |= (0x1 << channel);
    }
    else
    {
        *padc_reg_tab &= ~(0x1 << channel);

        if (*padc_reg_tab == 0)
        {
            ADC_Close(adc_base);
        }

        ADC_POWER_DOWN(adc_base);
    }

    return RT_EOK;
}

static rt_err_t nu_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    ADC_T *adc_base = ((nu_adc_t)device)->adc_base;
    int *padc_reg_tab = &((nu_adc_t)device)->adc_reg_tab;

    if (channel >= ((nu_adc_t)device)->adc_max_ch_num)
    {
        *value = 0xFFFFFFFF;
        return -(RT_EINVAL);
    }

    if ((*padc_reg_tab & (0x1 << channel)) == 0)
    {
        *value = 0xFFFFFFFF;
        return -(RT_EBUSY);
    }

    ADC_SET_INPUT_CHANNEL(adc_base, (0x1<<channel));

    ADC_CLR_INT_FLAG(adc_base, ADC_ADF_INT);

    ADC_ENABLE_INT(adc_base, ADC_ADF_INT);

    ADC_START_CONV(adc_base);

    while (ADC_GET_INT_FLAG(adc_base, ADC_ADF_INT) == 0);

    *value = ADC_GET_CONVERSION_DATA(adc_base,channel);

    return RT_EOK;
}

int rt_hw_adc_init(void)
{
    rt_err_t result = -RT_ERROR;
    int nu_sel = 0;

    while (nu_adc_arr[nu_sel].name != 0)
    {
        nu_adc_arr[nu_sel].adc_reg_tab = 0;

        result = rt_hw_adc_register(&nu_adc_arr[nu_sel].dev, nu_adc_arr[nu_sel].name, &nu_adc_ops, NULL);
        RT_ASSERT(result == RT_EOK);
        nu_sel++;
    }

    return (int)result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);


#endif /* #if defined(BSP_USING_ADC) */
