/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-3-16       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>
#include "NuMicro.h"

#if defined(BSP_USING_EADC)

/* Private define ---------------------------------------------------------------*/
enum
{
    EADC_START = -1,
#if defined(BSP_USING_EADC0)
    EADC0_IDX,
#endif
#if defined(BSP_USING_EADC1)
    EADC1_IDX,
#endif
#if defined(BSP_USING_EADC2)
    EADC2_IDX,
#endif
    EADC_CNT
};

/* Private Typedef --------------------------------------------------------------*/
struct nu_eadc
{
    struct rt_adc_device dev;
    char *name;
    EADC_T     *base;
    uint32_t    chn_msk;
    uint32_t    max_chn_num;
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
        .base = EADC0,
        .chn_msk = 0,
        .max_chn_num = 16,
    },
#endif
#if defined(BSP_USING_EADC1)
    {
        .name = "eadc1",
        .base = EADC1,
        .chn_msk = 0,
        .max_chn_num = 16,
    },
#endif
#if defined(BSP_USING_EADC2)
    {
        .name = "eadc2",
        .base = EADC2,
        .chn_msk = 0,
        .max_chn_num = 16,
    },
#endif
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
    nu_eadc_t psNuEADC = (nu_eadc_t)device;

    RT_ASSERT(device);

    if (channel >= psNuEADC->max_chn_num)
        return -(RT_EINVAL);

    if (enabled)
    {
        if (psNuEADC->chn_msk == 0)
        {
            EADC_Open(psNuEADC->base, EADC_CTL_DIFFEN_SINGLE_END);
        }

        psNuEADC->chn_msk |= (0x1 << channel);
    }
    else
    {
        psNuEADC->chn_msk &= ~(0x1 << channel);

        if (psNuEADC->chn_msk == 0)
        {
            EADC_Close(psNuEADC->base);
        }
    }

    return RT_EOK;
}

static rt_err_t nu_get_eadc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    nu_eadc_t psNuEADC = (nu_eadc_t)device;
    rt_err_t ret = -RT_ERROR;

    RT_ASSERT(device);
    RT_ASSERT(value);

    if (channel >= psNuEADC->max_chn_num)
    {
        *value = 0xFFFFFFFF;
        ret = -RT_EINVAL;
        goto exit_nu_get_eadc_value;
    }

    if ((psNuEADC->chn_msk & (1 << channel)) == 0)
    {
        *value = 0xFFFFFFFF;
        ret = -RT_EBUSY;
        goto exit_nu_get_eadc_value;
    }

    EADC_ConfigSampleModule(psNuEADC->base, 0, EADC_SOFTWARE_TRIGGER, channel);

    EADC_CLR_INT_FLAG(psNuEADC->base, EADC_STATUS2_ADIF0_Msk);

    EADC_ENABLE_INT(psNuEADC->base, BIT0);

    EADC_ENABLE_SAMPLE_MODULE_INT(psNuEADC->base, 0, BIT0);

    EADC_START_CONV(psNuEADC->base, BIT0);

    while (EADC_GET_INT_FLAG(psNuEADC->base, BIT0) == 0);

    EADC_DISABLE_INT(psNuEADC->base, BIT0);

    *value = EADC_GET_CONV_DATA(psNuEADC->base, 0);

    ret = RT_EOK;

exit_nu_get_eadc_value:

    return -(ret);
}

int rt_hw_eadc_init(void)
{
    int i;
    rt_err_t result;

    for (i = (EADC_START + 1); i < EADC_CNT; i++)
    {
        result = rt_hw_adc_register(&nu_eadc_arr[i].dev, nu_eadc_arr[i].name, &nu_adc_ops, NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_eadc_init);

#endif //#if defined(BSP_USING_EADC)
