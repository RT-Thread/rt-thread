/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-2-11       FYChou       First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>
#include <NuMicro.h>

#ifdef BSP_USING_EADC

/* Private define ---------------------------------------------------------------*/

/* Private Typedef --------------------------------------------------------------*/
struct nu_eadc
{
    struct rt_adc_device dev;
    char *name;
    EADC_T *eadc_base;
    int eadc_reg_tab;
    int eadc_max_ch_num;

};
typedef struct nu_eadc *nu_eadc_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_eadc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled);
static rt_err_t nu_get_eadc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value);
static rt_err_t nu_get_eadc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value);


/* Public functions ------------------------------------------------------------*/
int rt_hw_eadc_init(void);

/* Private variables ------------------------------------------------------------*/

static struct nu_eadc nu_eadc_arr [] =
{
#if defined(BSP_USING_EADC0)
    {
        .name = "eadc0",
        .eadc_base = EADC0,
        .eadc_max_ch_num = 19,
    },
#endif

#if defined(BSP_USING_EADC1)
    {
        .name = "eadc1",
        .eadc_base = EADC1,
        .eadc_max_ch_num = 19,
    },
#endif

    {0}
};

static const struct rt_adc_ops nu_adc_ops =
{
    nu_eadc_enabled,
    nu_get_eadc_value,
};
typedef struct rt_adc_ops *rt_adc_ops_t;


/* nu_adc_enabled - Enable ADC clock and wait for ready */
static rt_err_t nu_eadc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{

    EADC_T *eadc_base = ((nu_eadc_t)device)->eadc_base;
    int *peadc_reg_tab = &((nu_eadc_t)device)->eadc_reg_tab;
    RT_ASSERT(device != RT_NULL);

    if (channel >= ((nu_eadc_t)device)->eadc_max_ch_num)
        return -(RT_EINVAL);

    if (enabled)
    {
        if (*peadc_reg_tab == 0)
        {
            EADC_Open(eadc_base, EADC_CTL_DIFFEN_SINGLE_END);
        }

        *peadc_reg_tab |= (0x1 << channel);
    }
    else
    {
        *peadc_reg_tab &= ~(0x1 << channel);

        if (*peadc_reg_tab == 0)
        {
            EADC_Close(eadc_base);
        }
    }

    return RT_EOK;
}

static rt_err_t nu_get_eadc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    EADC_T *eadc_base = ((nu_eadc_t)device)->eadc_base;
    int *peadc_reg_tab = &((nu_eadc_t)device)->eadc_reg_tab;

    if (channel >= ((nu_eadc_t)device)->eadc_max_ch_num)
    {
        *value = 0xFFFFFFFF;
        return -(RT_EINVAL);
    }

    if ((*peadc_reg_tab & (1 << channel)) == 0)
    {
        *value = 0xFFFFFFFF;
        return -(RT_EBUSY);
    }

    EADC_ConfigSampleModule(eadc_base, 0, EADC_SOFTWARE_TRIGGER, channel);

    EADC_CLR_INT_FLAG(eadc_base, EADC_STATUS2_ADIF0_Msk);

    EADC_ENABLE_INT(eadc_base, BIT0);

    EADC_ENABLE_SAMPLE_MODULE_INT(eadc_base, 0, BIT0);

    EADC_START_CONV(eadc_base, BIT0);

    while (EADC_GET_INT_FLAG(eadc_base, BIT0) == 0);

    *value = EADC_GET_CONV_DATA(eadc_base, 0);

    return RT_EOK;
}

int rt_hw_eadc_init(void)
{
    rt_err_t result = RT_ERROR;
    int nu_sel = 0;

    while (nu_eadc_arr[nu_sel].name != 0)
    {
        nu_eadc_arr[nu_sel].eadc_reg_tab = 0;

        result = rt_hw_adc_register(&nu_eadc_arr[nu_sel].dev, nu_eadc_arr[nu_sel].name, &nu_adc_ops, NULL);
        RT_ASSERT(result == RT_EOK);
        nu_sel++;
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_eadc_init);


#endif //#if defined(BSP_USING_EADC)
