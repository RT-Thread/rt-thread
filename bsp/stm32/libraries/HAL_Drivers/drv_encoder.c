/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-09 15:25:34
 * @LastEditTime: 2019-08-09 17:29:27
 * @LastEditors: Please set LastEditors
 */
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-23     balanceTWK   first version
 */

#include "board.h"
#include "drv_config.h"
#ifdef RT_USING_ENCODER

//#define DRV_DEBUG
#define LOG_TAG             "drv.encoder"
#include <drv_log.h>

#if !defined(BSP_USING_ENCODER1) && !defined(BSP_USING_ENCODER2) && !defined(BSP_USING_ENCODER3) \
    && !defined(BSP_USING_ENCODER4) && !defined(BSP_USING_ENCODER5) && !defined(BSP_USING_ENCODER6) && !defined(BSP_USING_LPENCODER1)
    #error "Please define at least one BSP_USING_ENCODERx"
    /* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
#endif

enum
{
#ifdef BSP_USING_ENCODER1
    ENCODER1_INDEX,
#endif
#ifdef BSP_USING_ENCODER2
    ENCODER2_INDEX,
#endif
#ifdef BSP_USING_ENCODER3
    ENCODER3_INDEX,
#endif
#ifdef BSP_USING_ENCODER4
    ENCODER4_INDEX,
#endif
#ifdef BSP_USING_ENCODER5
    ENCODER5_INDEX,
#endif
#ifdef BSP_USING_ENCODER6
    ENCODER6_INDEX,
#endif
};

struct stm32_encoder_device
{
    struct rt_encoder_device encoder;
    TIM_HandleTypeDef tim_handler;
    char *name;
};

static struct stm32_encoder_device stm32_encoder_obj[] =
{
#ifdef BSP_USING_ENCODER1
    ENCODER1_CONFIG,
#endif
#ifdef BSP_USING_ENCODER2
    ENCODER2_CONFIG,
#endif
#ifdef BSP_USING_ENCODER3
    ENCODER3_CONFIG,
#endif
#ifdef BSP_USING_ENCODER4
    ENCODER4_CONFIG,
#endif
#ifdef BSP_USING_ENCODER5
    ENCODER5_CONFIG,
#endif
#ifdef BSP_USING_ENCODER6
    ENCODER6_CONFIG,
#endif
};

rt_err_t encoder_init(struct rt_encoder_device *encoder)
{
    TIM_Encoder_InitTypeDef sConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_HandleTypeDef *tim_handler = (TIM_HandleTypeDef *)encoder->parent.user_data;

    tim_handler->Init.Prescaler = 0;
    tim_handler->Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_handler->Init.Period = 0xffff;
    tim_handler->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
    sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
    sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC1Filter = 3;
    sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
    sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC2Filter = 3;

    if (HAL_TIM_Encoder_Init(tim_handler, &sConfig) != HAL_OK)
    {
        LOG_E("encoder init failed");
        return -RT_ERROR;
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    if (HAL_TIMEx_MasterConfigSynchronization(tim_handler, &sMasterConfig))
    {
        LOG_E("TIMx master config failed");
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_int32_t encoder_get_count(struct rt_encoder_device *encoder)
{
    TIM_HandleTypeDef *tim_handler = (TIM_HandleTypeDef *)encoder->parent.user_data;
    return (rt_int16_t)__HAL_TIM_GET_COUNTER(tim_handler);
}

rt_err_t encoder_control(struct rt_encoder_device *encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result;
    TIM_HandleTypeDef *tim_handler = (TIM_HandleTypeDef *)encoder->parent.user_data;

    result = RT_EOK;

    switch (cmd)
    {
    case ENCODER_CMD_ENABLE:
        HAL_TIM_Encoder_Start(tim_handler, TIM_CHANNEL_ALL);
        break;
    case ENCODER_CMD_DISABLE:
        HAL_TIM_Encoder_Stop(tim_handler, TIM_CHANNEL_ALL);
        break;
    case ENCODER_CMD_CLEAR_COUNT:
        __HAL_TIM_SET_COUNTER(tim_handler, 0);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static const struct rt_encoder_ops _ops =
{
    .init = encoder_init,
    .get_count = encoder_get_count,
    .control = encoder_control,
};

int hw_encoder_init(void)
{
    int i;
    int result;

    result = RT_EOK;
    for (i = 0; i < sizeof(stm32_encoder_obj) / sizeof(stm32_encoder_obj[0]); i++)
    {
        stm32_encoder_obj[i].encoder.type = AB_PHASE_ENCODER;
        stm32_encoder_obj[i].encoder.ops = &_ops;

        if (rt_device_encoder_register(&stm32_encoder_obj[i].encoder, stm32_encoder_obj[i].name, &stm32_encoder_obj[i].tim_handler) != RT_EOK)
        {
            LOG_E("%s register failed", stm32_encoder_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(hw_encoder_init);

#endif
