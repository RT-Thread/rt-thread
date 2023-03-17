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

#if defined(BSP_USING_DAC)

#include <rtdevice.h>
#include "NuMicro.h"

/* Private define ---------------------------------------------------------------*/
enum
{
    DAC_START = -1,
#if defined(BSP_USING_DAC0)
    DAC0_IDX,
#endif
#if defined(BSP_USING_DAC1)
    DAC1_IDX,
#endif
    DAC_CNT
};

/* Private Typedef --------------------------------------------------------------*/
struct nu_dac
{
    struct rt_dac_device dev;
    char      *name;
    DAC_T     *base;
    uint32_t  chn_msk;
    uint32_t  max_chn_num;
};
typedef struct nu_dac *nu_dac_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel);
static rt_err_t nu_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel);
static rt_err_t nu_dac_convert(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value);

/* Public functions ------------------------------------------------------------*/
int rt_hw_dac_init(void);

/* Private variables ------------------------------------------------------------*/

static struct nu_dac nu_dac_arr [] =
{
#if defined(BSP_USING_DAC0)
    {
        .name = "dac0", .base = DAC0, .chn_msk = 0, .max_chn_num = 1,
    },
#endif
#if defined(BSP_USING_DAC1)
    {
        .name = "dac1", .base = DAC1, .chn_msk = 0, .max_chn_num = 1,
    },
#endif
};

/* nu_dac_enabled - Enable DAC engine and wait for ready */
static rt_err_t nu_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    nu_dac_t psNuDAC = (nu_dac_t)device;

    RT_ASSERT(device);

    if (channel >= psNuDAC->max_chn_num)
        return -(RT_EINVAL);

    if (!(psNuDAC->chn_msk & (0x1 << channel)))
    {
        DAC_Open(psNuDAC->base, channel, DAC_SOFTWARE_TRIGGER);

        /* The DAC conversion settling time is 1us */
        DAC_SetDelayTime(psNuDAC->base, 1);

        DAC_ENABLE_RIGHT_ALIGN(psNuDAC->base);

        psNuDAC->chn_msk |= (0x1 << channel);
    }

    return RT_EOK;
}

static rt_err_t nu_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    nu_dac_t psNuDAC = (nu_dac_t)device;

    RT_ASSERT(device);

    if (channel >= psNuDAC->max_chn_num)
        return -(RT_EINVAL);

    if (psNuDAC->chn_msk & (0x1 << channel))
    {
        DAC_Close(psNuDAC->base, channel);

        psNuDAC->chn_msk &= ~(0x1 << channel);
    }

    return RT_EOK;
}

static rt_err_t nu_dac_convert(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    nu_dac_t psNuDAC = (nu_dac_t)device;
    rt_err_t ret = -RT_ERROR;

    RT_ASSERT(device);
    RT_ASSERT(value);

    if (channel >= psNuDAC->max_chn_num)
    {
        ret = -RT_EINVAL;
        goto exit_nu_dac_convert;
    }

    if (!(psNuDAC->chn_msk & (1 << channel)))
    {
        goto exit_nu_dac_convert;
    }

    /* Set DAC 12-bit holding data */
    DAC_WRITE_DATA(psNuDAC->base, 0, (uint16_t)*value);

    /* Start A/D conversion */
    DAC_START_CONV(psNuDAC->base);

    ret = RT_EOK;

exit_nu_dac_convert:

    return -(ret);
}

static const struct rt_dac_ops nu_dac_ops =
{
    .disabled = nu_dac_disabled,
    .enabled  = nu_dac_enabled,
    .convert  = nu_dac_convert,
};

int rt_hw_dac_init(void)
{
    int i;
    rt_err_t result;

    for (i = (DAC_START + 1); i < DAC_CNT; i++)
    {
        result = rt_hw_dac_register(&nu_dac_arr[i].dev, nu_dac_arr[i].name, &nu_dac_ops, NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_dac_init);

#endif //#if defined(BSP_USING_DAC)
