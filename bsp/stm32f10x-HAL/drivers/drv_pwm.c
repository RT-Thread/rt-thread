/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-07-15     ZYH          first version
 * 2018-10-19     XXXXzzzz000  transplant from stm32f4xx-HAL drv_pwm.c
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE 2

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
    {
        drv_pwm_control};

static rt_err_t drv_pwm_enable(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);
    if (!enable)
    {
        HAL_TIM_PWM_Stop(htim, channel);
    }
    else
    {
        HAL_TIM_PWM_Start(htim, channel);
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_get(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);
    rt_uint32_t tim_clock;

    tim_clock = SystemCoreClock;

    if (__HAL_TIM_GET_CLOCKDIVISION(htim) == TIM_CLOCKDIVISION_DIV2)
    {
        tim_clock = tim_clock / 2;
    }
    else if (__HAL_TIM_GET_CLOCKDIVISION(htim) == TIM_CLOCKDIVISION_DIV4)
    {
        tim_clock = tim_clock / 4;
    }
    tim_clock /= 1000000UL;
    configuration->period = (__HAL_TIM_GET_AUTORELOAD(htim) + 1) * (htim->Instance->PSC + 1) * 1000UL / tim_clock;
    configuration->pulse = (__HAL_TIM_GET_COMPARE(htim, channel) + 1) * (htim->Instance->PSC + 1) * 1000UL / tim_clock;
    return RT_EOK;
}

static rt_err_t drv_pwm_set(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint32_t tim_clock, psc;
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);

    tim_clock = SystemCoreClock;

    tim_clock /= 1000000UL;
    period = (unsigned long long)configuration->period * tim_clock / 1000ULL;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    __HAL_TIM_SET_PRESCALER(htim, psc - 1);
    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    __HAL_TIM_SET_AUTORELOAD(htim, period - 1);
    pulse = (unsigned long long)configuration->pulse * tim_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }
    __HAL_TIM_SET_COMPARE(htim, channel, pulse - 1);
    __HAL_TIM_SET_COUNTER(htim, 0);
    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(htim, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(htim, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(htim, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(htim, configuration);
    default:
        return RT_EINVAL;
    }
}

static void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle);

#ifdef BSP_USING_PWM1
TIM_HandleTypeDef htim1;
#endif
#ifdef BSP_USING_PWM2
TIM_HandleTypeDef htim2;
#endif
#ifdef BSP_USING_PWM3
TIM_HandleTypeDef htim3;
#endif
#ifdef BSP_USING_PWM4
TIM_HandleTypeDef htim4;
#endif
#ifdef BSP_USING_PWM5
TIM_HandleTypeDef htim5;
#endif
#ifdef BSP_USING_PWM8
TIM_HandleTypeDef htim8;
#endif

#ifdef BSP_USING_PWM1
static void MX_TIM1_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 0;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 0;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
    {
        RT_ASSERT(0);
    }
    if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

#ifdef BSP_USING_PWM1_CH1
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM1_CH1 */

#ifdef BSP_USING_PWM1_CH2
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM1_CH2 */
    sConfigOC.OCMode = TIM_OCMODE_TIMING;
#ifdef BSP_USING_PWM1_CH3
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM1_CH3 */

#ifdef BSP_USING_PWM1_CH4
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM1_CH4 */

    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;

    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }
    HAL_TIM_MspPostInit(&htim1);
}
#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2
static void MX_TIM2_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 0;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

#ifdef BSP_USING_PWM2_CH1
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM2_CH1 */

#ifdef BSP_USING_PWM2_CH2
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM2_CH2 */

#ifdef BSP_USING_PWM2_CH3
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM2_CH3 */

#ifdef BSP_USING_PWM2_CH4
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM2_CH3 */

    HAL_TIM_MspPostInit(&htim2);
}
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3
void MX_TIM3_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 0;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
#ifdef BSP_USING_PWM3_CH1
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM3_CH1 */

#ifdef BSP_USING_PWM3_CH2
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM3_CH2 */

#ifdef BSP_USING_PWM3_CH3
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM3_CH3 */

#ifdef BSP_USING_PWM3_CH4
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM3_CH4 */

    HAL_TIM_MspPostInit(&htim3);
}
#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4
void MX_TIM4_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 0;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 0;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
#ifdef BSP_USING_PWM4_CH1
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM4_CH1 */

#ifdef BSP_USING_PWM4_CH2
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM4_CH2 */

#ifdef BSP_USING_PWM4_CH3
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM4_CH3 */

#ifdef BSP_USING_PWM4_CH4
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM4_CH4 */

    HAL_TIM_MspPostInit(&htim4);
}
#endif /* BSP_USING_PWM4 */

#ifdef BSP_USING_PWM5
void MX_TIM5_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 0;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 0;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
#ifdef BSP_USING_PWM5_CH1
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM5_CH1 */

#ifdef BSP_USING_PWM5_CH2
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM5_CH2 */

#ifdef BSP_USING_PWM5_CH3
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM5_CH3 */

#ifdef BSP_USING_PWM5_CH4
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM5_CH3 */

    HAL_TIM_MspPostInit(&htim5);
}
#endif /* BSP_USING_PWM5 */

#ifdef BSP_USING_PWM8
static void MX_TIM8_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

    htim8.Instance = TIM8;
    htim8.Init.Prescaler = 0;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 0;
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.RepetitionCounter = 0;
    if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

#ifdef BSP_USING_PWM8_CH1
    if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM8_CH1 */

#ifdef BSP_USING_PWM8_CH2
    if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM8_CH2 */

#ifdef BSP_USING_PWM8_CH3
    if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM8_CH3 */

#ifdef BSP_USING_PWM8_CH4
    if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        RT_ASSERT(0);
    }
#endif /* BSP_USING_PWM8_CH4 */

    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;

    if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
    {
        RT_ASSERT(0);
    }
    HAL_TIM_MspPostInit(&htim8);
}
#endif /* BSP_USING_PWM8 */

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *tim_pwmHandle)
{
    if (tim_pwmHandle->Instance == TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();
    }
    else if (tim_pwmHandle->Instance == TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
    }
    else if (tim_pwmHandle->Instance == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
    }
    else if (tim_pwmHandle->Instance == TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
    }
    else if (tim_pwmHandle->Instance == TIM5)
    {
        __HAL_RCC_TIM5_CLK_ENABLE();
    }
    else if (tim_pwmHandle->Instance == TIM8)
    {
        __HAL_RCC_TIM8_CLK_ENABLE();
    }
}

static void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (timHandle->Instance == TIM1)
    {
        /**TIM1 GPIO Configuration    
    PE9     ------> TIM1_CH1
    PE11     ------> TIM1_CH2
    PE13     ------> TIM1_CH3
    PE14     ------> TIM1_CH4 
    */
#if defined(BSP_USING_PWM1_CH1) || defined(BSP_USING_PWM1_CH2) || defined(BSP_USING_PWM1_CH3) || defined(BSP_USING_PWM1_CH4)
        __HAL_RCC_GPIOE_CLK_ENABLE();

        GPIO_InitStruct.Pin = 0x00;

#ifdef BSP_USING_PWM1_CH1
        GPIO_InitStruct.Pin |= GPIO_PIN_9;
#endif
#ifdef BSP_USING_PWM1_CH2
        GPIO_InitStruct.Pin |= GPIO_PIN_11;
#endif
        /* FIXME:通道3,4无输出
#ifdef BSP_USING_PWM1_CH3
        GPIO_InitStruct.Pin |= GPIO_PIN_13;
#endif
#ifdef BSP_USING_PWM1_CH4
        GPIO_InitStruct.Pin |= GPIO_PIN_14;
#endif
*/
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
        __HAL_AFIO_REMAP_TIM1_ENABLE();
#endif
    }
    else if (timHandle->Instance == TIM2)
    {
        /**TIM2 GPIO Configuration    
    PB10     ------> TIM2_CH3
    PB11     ------> TIM2_CH4
    PA15     ------> TIM2_CH1
    PB3     ------> TIM2_CH2 
    */
#if defined(BSP_USING_PWM2_CH1) || defined(BSP_USING_PWM2_CH2) || defined(BSP_USING_PWM2_CH4)

        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitStruct.Pin = 0x00;
#ifdef BSP_USING_PWM2_CH1
        GPIO_InitStruct.Pin |= GPIO_PIN_10;
#endif
#ifdef BSP_USING_PWM2_CH2
        GPIO_InitStruct.Pin |= GPIO_PIN_11;
#endif
#ifdef BSP_USING_PWM2_CH4
        GPIO_InitStruct.Pin |= GPIO_PIN_3;
#endif
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif

#if defined(BSP_USING_PWM2_CH3)
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = 0x00;
#ifdef BSP_USING_PWM2_CH3
        GPIO_InitStruct.Pin |= GPIO_PIN_15;
#endif
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        __HAL_AFIO_REMAP_TIM2_ENABLE();
#endif
    }
    else if (timHandle->Instance == TIM3)
    {
        /**TIM3 GPIO Configuration    
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    PB0     ------> TIM3_CH3
    PB1     ------> TIM3_CH4 
    */
#if defined(BSP_USING_PWM3_CH1) || defined(BSP_USING_PWM3_CH2)
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = 0x00;
#ifdef BSP_USING_PWM3_CH1
        GPIO_InitStruct.Pin |= GPIO_PIN_6;
#endif
#ifdef BSP_USING_PWM3_CH2
        GPIO_InitStruct.Pin |= GPIO_PIN_7;
#endif
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = 0x00;
#endif

#if defined(BSP_USING_PWM3_CH3) || defined(BSP_USING_PWM3_CH4)
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitStruct.Pin = 0x00;
#ifdef BSP_USING_PWM3_CH3
        GPIO_InitStruct.Pin |= GPIO_PIN_0;
#endif
#ifdef BSP_USING_PWM3_CH4
        GPIO_InitStruct.Pin |= GPIO_PIN_1;
#endif
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
    }
    else if (timHandle->Instance == TIM4)
    {
        /**TIM4 GPIO Configuration    
    PD12     ------> TIM4_CH1
    PD13     ------> TIM4_CH2
    PD14     ------> TIM4_CH3
    PD15     ------> TIM4_CH4 
    */
#if defined(BSP_USING_PWM4_CH1) || defined(BSP_USING_PWM4_CH2) || defined(BSP_USING_PWM4_CH3) || defined(BSP_USING_PWM4_CH4)
        __HAL_RCC_GPIOD_CLK_ENABLE();

        GPIO_InitStruct.Pin = 0x00;
#ifdef BSP_USING_PWM4_CH1
        GPIO_InitStruct.Pin |= GPIO_PIN_12;
#endif
#ifdef BSP_USING_PWM4_CH2
        GPIO_InitStruct.Pin |= GPIO_PIN_13;
#endif
#ifdef BSP_USING_PWM4_CH3
        GPIO_InitStruct.Pin |= GPIO_PIN_14;
#endif
#ifdef BSP_USING_PWM4_CH4
        GPIO_InitStruct.Pin |= GPIO_PIN_15;
#endif
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        __HAL_AFIO_REMAP_TIM4_ENABLE();
#endif
    }
    else if (timHandle->Instance == TIM5)
    {
        /**TIM5 GPIO Configuration    
    PA0-WKUP     ------> TIM5_CH1
    PA1     ------> TIM5_CH2
    PA2     ------> TIM5_CH3
    PA3     ------> TIM5_CH4 
    */
#if defined(BSP_USING_PWM5_CH1) || defined(BSP_USING_PWM5_CH2) || defined(BSP_USING_PWM5_CH3) || defined(BSP_USING_PWM5_CH4)
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = 0x00;
#ifdef BSP_USING_PWM5_CH1
        GPIO_InitStruct.Pin |= GPIO_PIN_0;
#endif
#ifdef BSP_USING_PWM5_CH2
        GPIO_InitStruct.Pin |= GPIO_PIN_1;
#endif
#ifdef BSP_USING_PWM5_CH3
        GPIO_InitStruct.Pin |= GPIO_PIN_2;
#endif
#ifdef BSP_USING_PWM5_CH4
        GPIO_InitStruct.Pin |= GPIO_PIN_3;
#endif
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
    }
    else if (timHandle->Instance == TIM8)
    {
        /**TIM8 GPIO Configuration    
    PC6     ------> TIM8_CH1
    PC7     ------> TIM8_CH2
    PC8     ------> TIM8_CH3
    PC9     ------> TIM8_CH4 
    */
#if defined(BSP_USING_PWM8_CH1) || defined(BSP_USING_PWM8_CH2) || defined(BSP_USING_PWM8_CH3) || defined(BSP_USING_PWM8_CH4)
        __HAL_RCC_GPIOC_CLK_ENABLE();

        GPIO_InitStruct.Pin = 0x00;
#ifdef BSP_USING_PWM8_CH1
        GPIO_InitStruct.Pin |= GPIO_PIN_6;
#endif
#ifdef BSP_USING_PWM8_CH2
        GPIO_InitStruct.Pin |= GPIO_PIN_7;
#endif
#ifdef BSP_USING_PWM8_CH3
        GPIO_InitStruct.Pin |= GPIO_PIN_8;
#endif
#ifdef BSP_USING_PWM8_CH4
        GPIO_InitStruct.Pin |= GPIO_PIN_9;
#endif
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
#endif
    }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *tim_pwmHandle)
{
    if (tim_pwmHandle->Instance == TIM1)
    {
        __HAL_RCC_TIM1_CLK_DISABLE();
    }
    else if (tim_pwmHandle->Instance == TIM2)
    {
        __HAL_RCC_TIM2_CLK_DISABLE();
    }
    else if (tim_pwmHandle->Instance == TIM3)
    {
        __HAL_RCC_TIM3_CLK_DISABLE();
    }
    else if (tim_pwmHandle->Instance == TIM4)
    {
        __HAL_RCC_TIM4_CLK_DISABLE();
    }
    else if (tim_pwmHandle->Instance == TIM5)
    {
        __HAL_RCC_TIM5_CLK_DISABLE();
    }
    else if (tim_pwmHandle->Instance == TIM8)
    {
        __HAL_RCC_TIM8_CLK_DISABLE();
    }
}
int drv_pwm_init(void)
{
#ifdef BSP_USING_PWM1
    MX_TIM1_Init();
    rt_device_pwm_register(rt_calloc(1, sizeof(struct rt_device_pwm)), "pwm1", &drv_ops, &htim1);
#endif

#ifdef BSP_USING_PWM2
    MX_TIM2_Init();
    rt_device_pwm_register(rt_calloc(1, sizeof(struct rt_device_pwm)), "pwm2", &drv_ops, &htim2);
#endif

#ifdef BSP_USING_PWM3
    MX_TIM3_Init();
    rt_device_pwm_register(rt_calloc(1, sizeof(struct rt_device_pwm)), "pwm3", &drv_ops, &htim3);
#endif

#ifdef BSP_USING_PWM4
    MX_TIM4_Init();
    rt_device_pwm_register(rt_calloc(1, sizeof(struct rt_device_pwm)), "pwm4", &drv_ops, &htim4);
#endif

#ifdef BSP_USING_PWM5
    MX_TIM5_Init();
    rt_device_pwm_register(rt_calloc(1, sizeof(struct rt_device_pwm)), "pwm5", &drv_ops, &htim5);
#endif
#ifdef BSP_USING_PWM8
    MX_TIM8_Init();
    rt_device_pwm_register(rt_calloc(1, sizeof(struct rt_device_pwm)), "pwm8", &drv_ops, &htim8);
#endif
    return 0;
}
INIT_DEVICE_EXPORT(drv_pwm_init);

/* pwm test cmd */
static int pwm_test(int argc, char **argv)
{
    char *pwmc = argv[1];
    rt_device_t pwmd = rt_device_find(argv[1]);
    struct rt_pwm_configuration cfg =
        {
            .channel = 0,  /* 0-n */
            .period = 100, /* unit:ns 1ns~4.29s:1Ghz~0.23hz */
            .pulse = 50    /* unit:ns (pulse<=period) */
        };
    for (int i = 1; i < 5; i++)
    {
        cfg.channel = i;
        rt_device_control(pwmd, PWM_CMD_SET, &cfg);
        rt_device_control(pwmd, PWM_CMD_ENABLE, &cfg);
    }
}
MSH_CMD_EXPORT(pwm_test, pwm_test pwm1);