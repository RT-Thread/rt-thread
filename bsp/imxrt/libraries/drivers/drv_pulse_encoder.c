/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-23     balanceTWK   first version
 * 2021-01-19     Leslie Lee   port to imxrt series
 */

#include <rtthread.h>
#include <rtdevice.h>
#ifdef BSP_USING_PULSE_ENCODER

#include "fsl_common.h"
#include "fsl_enc.h"

#define LOG_TAG             "drv.pulse_encoder"
#include <drv_log.h>

#if !defined(BSP_USING_PULSE_ENCODER1) && !defined(BSP_USING_PULSE_ENCODER2) && !defined(BSP_USING_PULSE_ENCODER3) \
    && !defined(BSP_USING_PULSE_ENCODER4)
    #error "Please define at least one BSP_USING_PULSE_ENCODERx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#elif (defined(BSP_USING_PULSE_ENCODER2) || defined(BSP_USING_PULSE_ENCODER3) || defined(BSP_USING_PULSE_ENCODER4)) || defined(SOC_IMXRT1015_SERIES)
    #error "IMXRT1015 had only one quadrature decoder module"
#elif (defined(BSP_USING_PULSE_ENCODER3) || defined(BSP_USING_PULSE_ENCODER4)) || defined(SOC_IMXRT1020_SERIES)
    #error "IMXRT1020 had only two quadrature decoder module"
#endif

enum
{
#ifdef BSP_USING_PULSE_ENCODER1
    PULSE_ENCODER1_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER2
    PULSE_ENCODER2_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER3
    PULSE_ENCODER3_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER4
    PULSE_ENCODER4_INDEX,
#endif
};

struct imxrt_pulse_encoder_device
{
    struct rt_pulse_encoder_device pulse_encoder;
    ENC_Type *base;
    char *name;
};
typedef struct imxrt_pulse_encoder_device imxrt_pulse_enccoder_device_t;

static imxrt_pulse_enccoder_device_t imxrt_pulse_encoder_obj[] =
{
#ifdef BSP_USING_PULSE_ENCODER1
    {
       .base            = ENC1,
       .name            = "pulse1"
    },
#endif
#ifdef BSP_USING_PULSE_ENCODER2
    {
       .base            = ENC2,
       .name            = "pulse2"
    },
#endif
#ifdef BSP_USING_PULSE_ENCODER3
    {
       .base            = ENC3,
       .name            = "pulse3"
    },
#endif
#ifdef BSP_USING_PULSE_ENCODER4
    {
       .base            = ENC4,
       .name            = "pulse4"
    },
#endif
};



rt_err_t pulse_encoder_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    ENC_Type *base = ((imxrt_pulse_enccoder_device_t *)(pulse_encoder->parent.user_data))->base;
    enc_config_t enc_config;
    ENC_GetDefaultConfig(&enc_config);
    ENC_Init(base, &enc_config);
    ENC_DoSoftwareLoadInitialPositionValue(base);  /* Update the position counter with initial value. */
    return RT_EOK;
}

rt_err_t pulse_encoder_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    ENC_SetInitialPositionValue(((imxrt_pulse_enccoder_device_t *)(pulse_encoder->parent.user_data))->base, 0);
    return RT_EOK;
}

rt_int32_t pulse_encoder_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    return (rt_int32_t)ENC_GetPositionValue(((imxrt_pulse_enccoder_device_t *)(pulse_encoder->parent.user_data))->base);
}

rt_err_t pulse_encoder_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result;

    result = RT_EOK;

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        result = pulse_encoder->ops->init(pulse_encoder);
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        ENC_Deinit(((imxrt_pulse_enccoder_device_t *)(pulse_encoder->parent.user_data))->base);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static const struct rt_pulse_encoder_ops _ops =
{
    .init = pulse_encoder_init,
    .get_count = pulse_encoder_get_count,
    .clear_count = pulse_encoder_clear_count,
    .control = pulse_encoder_control,
};

int rt_hw_pulse_encoder_init(void)
{
    int i;
    int result;

    result = RT_EOK;
    for (i = 0; i < sizeof(imxrt_pulse_encoder_obj) / sizeof(imxrt_pulse_encoder_obj[0]); i++)
    {
        imxrt_pulse_encoder_obj[i].pulse_encoder.type = AB_PHASE_PULSE_ENCODER;
        imxrt_pulse_encoder_obj[i].pulse_encoder.ops = &_ops;
        imxrt_pulse_encoder_obj[i].pulse_encoder.parent.user_data = &(imxrt_pulse_encoder_obj[i]);

        if (rt_device_pulse_encoder_register(&imxrt_pulse_encoder_obj[i].pulse_encoder, imxrt_pulse_encoder_obj[i].name, &imxrt_pulse_encoder_obj[i]) != RT_EOK)
        {
            LOG_E("%s register failed", imxrt_pulse_encoder_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_pulse_encoder_init);

#endif
