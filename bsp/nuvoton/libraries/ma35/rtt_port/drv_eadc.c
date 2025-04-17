/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-9-23       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_EADC)

#include <rtdevice.h>
#include "NuMicro.h"

/* Private define --------------------------------------------------------------- */
#define DEF_EADC_MAX_CHANNEL_NUM     8

enum
{
    EADC_START = -1,
#if defined(BSP_USING_EADC0)
    EADC0_IDX,
#endif
    EADC_CNT
};

/* Private Typedef -------------------------------------------------------------- */
struct nu_eadc
{
    struct rt_adc_device parent;
    char                 *name;
    EADC_T               *base;
    uint32_t              rstidx;
    uint32_t              modid;
    uint32_t              chnmask;
};
typedef struct nu_eadc *nu_eadc_t;

/* Private functions ------------------------------------------------------------ */
static rt_err_t nu_eadc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled);
static rt_err_t nu_get_eadc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value);

/* Public functions ------------------------------------------------------------ */
int rt_hw_eadc_init(void);

/* Private variables ------------------------------------------------------------ */

static struct nu_eadc nu_eadc_arr [] =
{
#if defined(BSP_USING_EADC0)
    { .name = "eadc0", .base = EADC0, .rstidx = EADC0_RST, .modid = EADC0_MODULE, .chnmask = 0 },
#endif
};

static const struct rt_adc_ops nu_adc_ops =
{
    nu_eadc_enabled,
    nu_get_eadc_value,
};
typedef struct rt_adc_ops *rt_adc_ops_t;


/* nu_adc_enabled - Enable ADC clock and wait for ready */
static rt_err_t nu_eadc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    nu_eadc_t psNuEadc = (nu_eadc_t)device;
    RT_ASSERT(device != RT_NULL);

    if (channel >= DEF_EADC_MAX_CHANNEL_NUM)
        return -(RT_EINVAL);

    if (enabled)
    {
        if (psNuEadc->chnmask == 0)
        {
            /* Invoke Open function at first call. */
            EADC_Open(psNuEadc->base, EADC_CTL_DIFFEN_SINGLE_END);
        }
        psNuEadc->chnmask |= (1 << channel);
    }
    else
    {
        psNuEadc->chnmask &= ~(1 << channel);

        if (psNuEadc->chnmask == 0)
        {
            /* Invoke Open function at last call. */
            EADC_Close(psNuEadc->base);
        }
    }

    return RT_EOK;
}

static rt_err_t nu_get_eadc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    nu_eadc_t psNuEadc = (nu_eadc_t)device;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    if (channel >= DEF_EADC_MAX_CHANNEL_NUM)
    {
        *value = 0xFFFFFFFF;
        return -(RT_EINVAL);
    }

    if ((psNuEadc->chnmask & (1 << channel)) == 0)
    {
        *value = 0xFFFFFFFF;
        return -(RT_EBUSY);
    }

    EADC_ConfigSampleModule(psNuEadc->base, 0, EADC_SOFTWARE_TRIGGER, channel);

    EADC_CLR_INT_FLAG(psNuEadc->base, EADC_STATUS2_ADIF0_Msk);

    EADC_ENABLE_INT(psNuEadc->base, BIT0);

    EADC_ENABLE_SAMPLE_MODULE_INT(psNuEadc->base, 0, BIT0);

    EADC_START_CONV(psNuEadc->base, BIT0);

    while (EADC_GET_INT_FLAG(psNuEadc->base, BIT0) == 0);

    *value = EADC_GET_CONV_DATA(psNuEadc->base, 0);

    return RT_EOK;
}

int rt_hw_eadc_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (EADC_START + 1); i < EADC_CNT; i++)
    {
        CLK_EnableModuleClock(nu_eadc_arr[i].modid);
        SYS_ResetModule(nu_eadc_arr[i].rstidx);

        ret = rt_hw_adc_register(&nu_eadc_arr[i].parent, nu_eadc_arr[i].name, &nu_adc_ops, &nu_eadc_arr[i]);
        RT_ASSERT(ret == RT_EOK);
    }

    return (int)ret;
}
INIT_BOARD_EXPORT(rt_hw_eadc_init);

#endif /* #if defined(BSP_USING_EADC) */
