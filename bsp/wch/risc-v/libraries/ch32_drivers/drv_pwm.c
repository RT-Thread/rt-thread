/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-09-23     charlown          first version
 * 2022-10-14     hg0720            the first version which add from wch
 * 2022-10-20     MXH               add the remaining timers
 */

#include "drv_pwm.h"

#ifdef BSP_USING_PWM

#define LOG_TAG "drv.pwm"
#include <drv_log.h>

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

void ch32_tim_clock_init(TIM_TypeDef* timx)
{
#ifdef BSP_USING_TIM1_PWM
    if (timx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
#endif/* BSP_USING_TIM1_PWM */

#ifdef BSP_USING_TIM2_PWM
    if (timx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
#endif/* BSP_USING_TIM2_PWM */

#ifdef BSP_USING_TIM3_PWM
    if (timx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
#endif/* BSP_USING_TIM3_PWM */

#ifdef BSP_USING_TIM4_PWM
    if (timx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
#endif/* BSP_USING_TIM4_PWM */

#ifdef BSP_USING_TIM5_PWM
    if (timx == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
#endif/* BSP_USING_TIM5_PWM */

    /* TIM6 and TIM7 don't support PWM Mode. */

#ifdef BSP_USING_TIM8_PWM
    if (timx == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    }
#endif/* BSP_USING_TIM8_PWM */

#ifdef BSP_USING_TIM9_PWM
    if (timx == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    }
#endif/* BSP_USING_TIM9_PWM */

#ifdef BSP_USING_TIM10_PWM
    if (timx == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    }
#endif/* BSP_USING_TIM10_PWM */
}

rt_uint32_t ch32_tim_clock_get(TIM_TypeDef* timx)
{
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);

    /*tim1~10 all in HCLK*/
    return RCC_Clocks.HCLK_Frequency;
}

/*
 * NOTE:  some pwm pins of some timers are reused,
 *          please keep caution when using pwm
 */

void ch32_pwm_io_init(TIM_TypeDef* timx, rt_uint8_t channel)
{
    GPIO_InitTypeDef GPIO_InitStructure;

#ifdef BSP_USING_TIM1_PWM
    if (timx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

#ifdef BSP_USING_TIM1_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM1_PWM_CH1 */

#ifdef BSP_USING_TIM1_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM1_PWM_CH2 */

#ifdef BSP_USING_TIM1_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM1_PWM_CH3 */

#ifdef BSP_USING_TIM1_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM1_PWM_CH4 */
    }
#endif/* BSP_USING_TIM1_PWM */

#ifdef BSP_USING_TIM2_PWM
    if (timx == TIM2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

#ifdef BSP_USING_TIM2_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM2_PWM_CH1 */

#ifdef BSP_USING_TIM2_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM2_PWM_CH2 */

#ifdef BSP_USING_TIM2_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM2_PWM_CH3 */

#ifdef BSP_USING_TIM2_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM2_PWM_CH4 */
    }
#endif/* BSP_USING_TIM2_PWM */

#ifdef BSP_USING_TIM3_PWM
    if (timx == TIM3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

#ifdef BSP_USING_TIM3_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM3_PWM_CH1 */

#ifdef BSP_USING_TIM3_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM3_PWM_CH2 */

#ifdef BSP_USING_TIM3_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM3_PWM_CH3 */

#ifdef BSP_USING_TIM3_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM3_PWM_CH4 */
    }
#endif/* BSP_USING_TIM3_PWM */

#ifdef BSP_USING_TIM4_PWM
    if (timx == TIM4)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

#ifdef BSP_USING_TIM4_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM4_PWM_CH1 */

#ifdef BSP_USING_TIM4_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM4_PWM_CH2 */

#ifdef BSP_USING_TIM4_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM4_PWM_CH3 */

#ifdef BSP_USING_TIM4_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM4_PWM_CH4 */
    }
#endif/* BSP_USING_TIM4_PWM */

#ifdef BSP_USING_TIM5_PWM
    if (timx == TIM5)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

#ifdef BSP_USING_TIM5_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM5_PWM_CH1 */

#ifdef BSP_USING_TIM5_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM5_PWM_CH2 */

#ifdef BSP_USING_TIM5_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM5_PWM_CH3 */

#ifdef BSP_USING_TIM5_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM5_PWM_CH4 */
    }
#endif/* BSP_USING_TIM5_PWM */

    /* TIM6 and TIM7 don't support PWM Mode. */

#ifdef BSP_USING_TIM8_PWM
    if (timx == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

/* I don't test it, because there is a 10M-PHY ETH port on my board,
 * which uses the following four pins.
 * You can try it on a board without a 10M-PHY ETH port. */
#ifdef BSP_USING_TIM8_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM8_PWM_CH1 */

#ifdef BSP_USING_TIM8_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM8_PWM_CH2 */

#ifdef BSP_USING_TIM8_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM8_PWM_CH3 */

#ifdef BSP_USING_TIM8_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM8_PWM_CH4 */
    }
#endif/* BSP_USING_TIM8_PWM */

#ifdef BSP_USING_TIM9_PWM
    if (timx == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

#ifdef BSP_USING_TIM9_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM9_PWM_CH1 */

#ifdef BSP_USING_TIM9_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM9_PWM_CH2 */

#ifdef BSP_USING_TIM9_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM9_PWM_CH3 */

#ifdef BSP_USING_TIM9_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM9_PWM_CH4 */
    }
#endif/* BSP_USING_TIM9_PWM */

#ifdef BSP_USING_TIM10_PWM
    if (timx == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

#ifdef BSP_USING_TIM10_PWM_CH1
        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM10_PWM_CH1 */

#ifdef BSP_USING_TIM10_PWM_CH2
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM10_PWM_CH2 */

#ifdef BSP_USING_TIM10_PWM_CH3
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM10_PWM_CH3 */

#ifdef BSP_USING_TIM10_PWM_CH4
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
#endif/* BSP_USING_TIM10_PWM_CH4 */
    }
#endif/* BSP_USING_TIM10_PWM */
}

/*
 * channel = FLAG_NOT_INIT: the channel is not use.
 */
struct rtdevice_pwm_device pwm_device_list[] =
{
#ifdef BSP_USING_TIM1_PWM
    {
        .periph = TIM1,
        .name = "pwm1",
#ifdef BSP_USING_TIM1_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM1_PWM_CH1 */

#ifdef BSP_USING_TIM1_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM1_PWM_CH2 */

#ifdef BSP_USING_TIM1_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM1_PWM_CH3 */

#ifdef BSP_USING_TIM1_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM1_PWM_CH4 */
    },
#endif /* BSP_USING_TIM1_PWM */

#ifdef BSP_USING_TIM2_PWM
    {
        .periph = TIM2,
        .name = "pwm2",
#ifdef BSP_USING_TIM2_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM2_PWM_CH1 */

#ifdef BSP_USING_TIM2_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM2_PWM_CH2 */

#ifdef BSP_USING_TIM2_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM2_PWM_CH3 */

#ifdef BSP_USING_TIM2_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM2_PWM_CH4 */
    },
#endif /* BSP_USING_TIM2_PWM */

#ifdef BSP_USING_TIM3_PWM
    {
        .periph = TIM3,
        .name = "pwm3",
#ifdef BSP_USING_TIM3_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM3_PWM_CH1 */

#ifdef BSP_USING_TIM3_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM3_PWM_CH2 */

#ifdef BSP_USING_TIM3_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM3_PWM_CH3 */

#ifdef BSP_USING_TIM3_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM3_PWM_CH4 */
    },
#endif /* BSP_USING_TIM3_PWM */

#ifdef BSP_USING_TIM4_PWM
    {
        .periph = TIM4,
        .name = "pwm4",
#ifdef BSP_USING_TIM4_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM4_PWM_CH1 */

#ifdef BSP_USING_TIM4_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM4_PWM_CH2 */

#ifdef BSP_USING_TIM4_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM4_PWM_CH3 */

#ifdef BSP_USING_TIM4_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM4_PWM_CH4 */
    },
#endif /* BSP_USING_TIM4_PWM */

#ifdef BSP_USING_TIM5_PWM
    {
        .periph = TIM5,
        .name = "pwm5",
#ifdef BSP_USING_TIM5_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM5_PWM_CH1 */

#ifdef BSP_USING_TIM5_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM5_PWM_CH2 */

#ifdef BSP_USING_TIM5_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM5_PWM_CH3 */

#ifdef BSP_USING_TIM5_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM5_PWM_CH4 */
    },
#endif /* BSP_USING_TIM5_PWM */

#ifdef BSP_USING_TIM8_PWM
    {
        .periph = TIM8,
        .name = "pwm8",
#ifdef BSP_USING_TIM8_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM8_PWM_CH1 */

#ifdef BSP_USING_TIM8_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM8_PWM_CH2 */

#ifdef BSP_USING_TIM8_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM8_PWM_CH3 */

#ifdef BSP_USING_TIM8_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM8_PWM_CH4 */
    },
#endif /* BSP_USING_TIM8_PWM */

#ifdef BSP_USING_TIM9_PWM
    {
        .periph = TIM9,
        .name = "pwm9",
#ifdef BSP_USING_TIM9_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM9_PWM_CH1 */

#ifdef BSP_USING_TIM9_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM9_PWM_CH2 */

#ifdef BSP_USING_TIM9_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM9_PWM_CH3 */

#ifdef BSP_USING_TIM9_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM9_PWM_CH4 */
    },
#endif /* BSP_USING_TIM9_PWM */

#ifdef BSP_USING_TIM10_PWM
    {
        .periph = TIM10,
        .name = "pwm10",
#ifdef BSP_USING_TIM10_PWM_CH1
        .channel[0] = TIM_Channel_1,
#else
        .channel[0] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM10_PWM_CH1 */

#ifdef BSP_USING_TIM10_PWM_CH2
        .channel[1] = TIM_Channel_2,
#else
        .channel[1] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM10_PWM_CH2 */

#ifdef BSP_USING_TIM10_PWM_CH3
        .channel[2] = TIM_Channel_3,
#else
        .channel[2] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM10_PWM_CH3 */

#ifdef BSP_USING_TIM10_PWM_CH4
        .channel[3] = TIM_Channel_4,
#else
        .channel[3] = FLAG_NOT_INIT,
#endif/* BSP_USING_TIM10_PWM_CH4 */
    },
#endif /* BSP_USING_TIM10_PWM */
};

static rt_err_t ch32_pwm_device_enable(struct rt_device_pwm* device, struct rt_pwm_configuration* configuration, rt_bool_t enable)
{
    struct rtdevice_pwm_device* pwm_device;
    rt_uint32_t channel_index;
    rt_uint16_t ccx_state;

    pwm_device = (struct rtdevice_pwm_device*)device;
    channel_index = configuration->channel;

    if (enable == RT_TRUE)
    {
        ccx_state = TIM_CCx_Enable;
    }
    else
    {
        ccx_state = TIM_CCx_Disable;
    }

    if (channel_index <= 4 && channel_index > 0)
    {
        if (pwm_device->channel[channel_index - 1] == FLAG_NOT_INIT)
        {
            return -RT_EINVAL;
        }
        TIM_CCxCmd(pwm_device->periph, pwm_device->channel[channel_index - 1], ccx_state);
    }
    else
    {
        return -RT_EINVAL;
    }

    TIM_Cmd(pwm_device->periph, ENABLE);

    return RT_EOK;
}

static rt_err_t ch32_pwm_device_get(struct rt_device_pwm* device, struct rt_pwm_configuration* configuration)
{
    struct rtdevice_pwm_device* pwm_device;
    rt_uint32_t arr_counter, ccr_counter, prescaler, sample_freq;
    rt_uint32_t channel_index;
    rt_uint32_t tim_clock;

    pwm_device = (struct rtdevice_pwm_device*)device;
    tim_clock = ch32_tim_clock_get(pwm_device->periph);
    channel_index = configuration->channel;
    arr_counter = pwm_device->periph->ATRLR + 1;
    prescaler = pwm_device->periph->PSC + 1;
    sample_freq = (tim_clock / prescaler) / arr_counter;

    /* unit:ns */
    configuration->period = 1000000000 / sample_freq;

    if (channel_index == 1)
    {
        ccr_counter = pwm_device->periph->CH1CVR + 1;
        configuration->pulse = ((ccr_counter * 100) / arr_counter) * configuration->period / 100;
    }
    else if (channel_index == 2)
    {
        ccr_counter = pwm_device->periph->CH2CVR + 1;
        configuration->pulse = ((ccr_counter * 100) / arr_counter) * configuration->period / 100;
    }
    else if (channel_index == 3)
    {
        ccr_counter = pwm_device->periph->CH3CVR + 1;
        configuration->pulse = ((ccr_counter * 100) / arr_counter) * configuration->period / 100;
    }
    else if (channel_index == 4)
    {
        ccr_counter = pwm_device->periph->CH4CVR + 1;
        configuration->pulse = ((ccr_counter * 100) / arr_counter) * configuration->period / 100;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t ch32_pwm_device_set(struct rt_device_pwm* device, struct rt_pwm_configuration* configuration)
{
    struct rtdevice_pwm_device* pwm_device;
    rt_uint32_t arr_counter, ccr_counter, prescaler, sample_freq;
    rt_uint32_t channel_index;
    rt_uint32_t tim_clock;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitType;
    TIM_OCInitTypeDef TIM_OCInitType;

    pwm_device = (struct rtdevice_pwm_device*)device;
    tim_clock = ch32_tim_clock_get(pwm_device->periph);
    channel_index = configuration->channel;

    /* change to freq, unit:Hz */
    sample_freq = 1000000000 / configuration->period;

    /* counter = (tim_clk / prescaler) / sample_freq */
    /* normally, tim_clk is not need div, if arr_counter over 65536, need div. */
    prescaler = 1;
    arr_counter = (tim_clock / prescaler) / sample_freq;

    if (arr_counter > MAX_COUNTER)
    {
        /* need div tim_clock
         * and round up the prescaler value.
         * (tim_clock >> 16) = tim_clock / 65536
         */
        if ((tim_clock >> 16) % sample_freq == 0)
            prescaler = (tim_clock >> 16) / sample_freq;
        else
            prescaler = (tim_clock >> 16) / sample_freq + 1;

        /* counter = (tim_clk / prescaler) / sample_freq */
        arr_counter = (tim_clock / prescaler) / sample_freq;
    }
    /* ccr_counter = duty cycle * arr_counter */
    ccr_counter = (configuration->pulse * 100 / configuration->period) * arr_counter / 100;

    /* check arr_counter > 1, cxx_counter > 1 */
    if (arr_counter < MIN_COUNTER)
    {
        arr_counter = MIN_COUNTER;
    }
    if (ccr_counter < MIN_PULSE)
    {
        ccr_counter = MIN_PULSE;
    }

    /* TMRe base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitType);
    TIM_TimeBaseInitType.TIM_Period = arr_counter - 1;
    TIM_TimeBaseInitType.TIM_Prescaler = prescaler - 1;
    TIM_TimeBaseInitType.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitType.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(pwm_device->periph, &TIM_TimeBaseInitType);

    TIM_OCStructInit(&TIM_OCInitType);
    TIM_OCInitType.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitType.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitType.TIM_Pulse = ccr_counter - 1;
    TIM_OCInitType.TIM_OCPolarity = TIM_OCPolarity_High;

    if (channel_index == 1)
    {
        TIM_OC1Init(pwm_device->periph, &TIM_OCInitType);
        TIM_OC1PreloadConfig(pwm_device->periph, TIM_OCPreload_Disable);
    }
    else if (channel_index == 2)
    {
        TIM_OC2Init(pwm_device->periph, &TIM_OCInitType);
        TIM_OC2PreloadConfig(pwm_device->periph, TIM_OCPreload_Disable);
    }
    else if (channel_index == 3)
    {
        TIM_OC3Init(pwm_device->periph, &TIM_OCInitType);
        TIM_OC3PreloadConfig(pwm_device->periph, TIM_OCPreload_Disable);
    }
    else if (channel_index == 4)
    {
        TIM_OC4Init(pwm_device->periph, &TIM_OCInitType);
        TIM_OC4PreloadConfig(pwm_device->periph, TIM_OCPreload_Disable);
    }
    else
    {
        return -RT_EINVAL;
    }

    TIM_ARRPreloadConfig(pwm_device->periph, ENABLE);
    TIM_CtrlPWMOutputs(pwm_device->periph, ENABLE);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm* device, int cmd, void* arg)
{
    struct rt_pwm_configuration* configuration;

    configuration = (struct rt_pwm_configuration*)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return ch32_pwm_device_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return ch32_pwm_device_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return ch32_pwm_device_set(device, configuration);
    case PWM_CMD_GET:
        return ch32_pwm_device_get(device, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops pwm_ops =
{
    .control = drv_pwm_control
};

static int rt_hw_pwm_init(void)
{
    int result = RT_EOK;
    int index = 0;
    int channel_index;

    for (index = 0; index < ITEM_NUM(pwm_device_list); index++)
    {
        ch32_tim_clock_init(pwm_device_list[index].periph);
        for (channel_index = 0; channel_index < sizeof(pwm_device_list[index].channel); channel_index++)
        {
            if (pwm_device_list[index].channel[channel_index] != FLAG_NOT_INIT)
            {
                ch32_pwm_io_init(pwm_device_list[index].periph, pwm_device_list[index].channel[channel_index]);
            }
        }

        if (rt_device_pwm_register(&pwm_device_list[index].parent, pwm_device_list[index].name, &pwm_ops, RT_NULL) == RT_EOK)
        {
            LOG_D("%s register success", pwm_device_list[index].name);
        }
        else
        {
            LOG_D("%s register failed", pwm_device_list[index].name);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM */
