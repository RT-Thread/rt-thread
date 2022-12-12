/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 * 2022-06-16     lianghongquan     use macro definition config adc pin.
 * 2022-06-28     lianghongquan     add function rt_hw_board_pwm_tmra_init().
 */

#include <rtdevice.h>
#include "board_config.h"

/**
 * The below functions will initialize HC32 board.
 */

#if defined RT_USING_SERIAL
rt_err_t rt_hw_board_uart_init(CM_USART_TypeDef *USARTx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)USARTx)
    {
#if defined(BSP_USING_UART1)
    case (rt_uint32_t)CM_USART1:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART1_RX_PORT, USART1_RX_PIN, GPIO_FUNC_33);
        GPIO_SetFunc(USART1_TX_PORT, USART1_TX_PIN, GPIO_FUNC_32);
        break;
#endif
#if defined(BSP_USING_UART2)
    case (rt_uint32_t)CM_USART2:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART2_RX_PORT, USART2_RX_PIN, GPIO_FUNC_37);
        GPIO_SetFunc(USART2_TX_PORT, USART2_TX_PIN, GPIO_FUNC_36);
        break;
#endif
#if defined(BSP_USING_UART3)
    case (rt_uint32_t)CM_USART3:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART3_RX_PORT, USART3_RX_PIN, GPIO_FUNC_33);
        GPIO_SetFunc(USART3_TX_PORT, USART3_TX_PIN, GPIO_FUNC_32);
        break;
#endif
#if defined(BSP_USING_UART4)
    case (rt_uint32_t)CM_USART4:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART4_RX_PORT, USART4_RX_PIN, GPIO_FUNC_37);
        GPIO_SetFunc(USART4_TX_PORT, USART4_TX_PIN, GPIO_FUNC_36);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined(BSP_USING_CAN)
void CanPhyEnable(void)
{
#if defined(BSP_USING_CAN1)
#ifdef CAN1_STB_FUNC_ENABLE
    GPIO_ResetPins(CAN_STB_PORT, CAN_STB_PIN);
    GPIO_OutputCmd(CAN_STB_PORT, CAN_STB_PIN, ENABLE);
#endif
#endif
}
rt_err_t rt_hw_board_can_init(CM_CAN_TypeDef *CANx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)CANx)
    {
#if defined(BSP_USING_CAN1)
case (rt_uint32_t)CM_CAN:
    GPIO_SetFunc(CAN1_TX_PORT, CAN1_TX_PIN, CAN1_TX_PIN_FUNC);
    GPIO_SetFunc(CAN1_RX_PORT, CAN1_RX_PIN, CAN1_RX_PIN_FUNC);
    break;
#endif
default:
    result = -RT_ERROR;
    break;
    }

    return result;
}
#endif

#if defined(RT_USING_ADC)
rt_err_t rt_hw_board_adc_init(CM_ADC_TypeDef *ADCx)
{
    rt_err_t result = RT_EOK;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    switch ((rt_uint32_t)ADCx)
    {
#if defined(BSP_USING_ADC1)
    case (rt_uint32_t)CM_ADC1:
        (void)GPIO_Init(ADC1_CH10_PORT, ADC1_CH10_PIN, &stcGpioInit);
        (void)GPIO_Init(ADC1_CH12_PORT, ADC1_CH12_PIN, &stcGpioInit);
        (void)GPIO_Init(ADC1_CH13_PORT, ADC1_CH13_PIN, &stcGpioInit);
        break;
#endif
#if defined(BSP_USING_ADC2)
    case (rt_uint32_t)CM_ADC2:
        (void)GPIO_Init(ADC2_CH7_PORT, ADC2_CH7_PIN, &stcGpioInit);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined(RT_USING_PWM)
rt_err_t rt_hw_board_pwm_tmra_init(CM_TMRA_TypeDef *TMRAx)
{
    rt_err_t result = RT_EOK;
    switch ((rt_uint32_t)TMRAx)
    {
#if defined(BSP_USING_PWM_TMRA_1)
    case (rt_uint32_t)CM_TMRA_1:
    #ifdef BSP_USING_PWM_TMRA_1_CH1
        GPIO_SetFunc(PWM_TMRA_1_CH1_PORT, PWM_TMRA_1_CH1_PIN, PWM_TMRA_1_CH1_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH2
        GPIO_SetFunc(PWM_TMRA_1_CH2_PORT, PWM_TMRA_1_CH2_PIN, PWM_TMRA_1_CH2_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH3
        GPIO_SetFunc(PWM_TMRA_1_CH3_PORT, PWM_TMRA_1_CH3_PIN, PWM_TMRA_1_CH3_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH4
        GPIO_SetFunc(PWM_TMRA_1_CH4_PORT, PWM_TMRA_1_CH4_PIN, PWM_TMRA_1_CH4_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH5
        GPIO_SetFunc(PWM_TMRA_1_CH5_PORT, PWM_TMRA_1_CH5_PIN, PWM_TMRA_1_CH5_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH6
        GPIO_SetFunc(PWM_TMRA_1_CH6_PORT, PWM_TMRA_1_CH6_PIN, PWM_TMRA_1_CH6_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH7
        GPIO_SetFunc(PWM_TMRA_1_CH7_PORT, PWM_TMRA_1_CH7_PIN, PWM_TMRA_1_CH7_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH8
        GPIO_SetFunc(PWM_TMRA_1_CH8_PORT, PWM_TMRA_1_CH8_PIN, PWM_TMRA_1_CH8_PIN_FUNC);
    #endif
        break;
#endif
#if defined(BSP_USING_PWM_TMRA_2)
    case (rt_uint32_t)CM_TMRA_2:
    #ifdef BSP_USING_PWM_TMRA_2_CH1
        GPIO_SetFunc(PWM_TMRA_2_CH1_PORT, PWM_TMRA_2_CH1_PIN, PWM_TMRA_2_CH1_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH2
        GPIO_SetFunc(PWM_TMRA_2_CH2_PORT, PWM_TMRA_2_CH2_PIN, PWM_TMRA_2_CH2_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH3
        GPIO_SetFunc(PWM_TMRA_2_CH3_PORT, PWM_TMRA_2_CH3_PIN, PWM_TMRA_2_CH3_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH4
        GPIO_SetFunc(PWM_TMRA_2_CH4_PORT, PWM_TMRA_2_CH4_PIN, PWM_TMRA_2_CH4_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH5
        GPIO_SetFunc(PWM_TMRA_2_CH5_PORT, PWM_TMRA_2_CH5_PIN, PWM_TMRA_2_CH5_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH6
        GPIO_SetFunc(PWM_TMRA_2_CH6_PORT, PWM_TMRA_2_CH6_PIN, PWM_TMRA_2_CH6_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH7
        GPIO_SetFunc(PWM_TMRA_2_CH7_PORT, PWM_TMRA_2_CH7_PIN, PWM_TMRA_2_CH7_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH8
        GPIO_SetFunc(PWM_TMRA_2_CH8_PORT, PWM_TMRA_2_CH8_PIN, PWM_TMRA_2_CH8_PIN_FUNC);
    #endif
        break;
#endif
#if defined(BSP_USING_PWM_TMRA_3)
    case (rt_uint32_t)CM_TMRA_3:
    #ifdef BSP_USING_PWM_TMRA_3_CH1
        GPIO_SetFunc(PWM_TMRA_3_CH1_PORT, PWM_TMRA_3_CH1_PIN, PWM_TMRA_3_CH1_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH2
        GPIO_SetFunc(PWM_TMRA_3_CH2_PORT, PWM_TMRA_3_CH2_PIN, PWM_TMRA_3_CH2_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH3
        GPIO_SetFunc(PWM_TMRA_3_CH3_PORT, PWM_TMRA_3_CH3_PIN, PWM_TMRA_3_CH3_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH4
        GPIO_SetFunc(PWM_TMRA_3_CH4_PORT, PWM_TMRA_3_CH4_PIN, PWM_TMRA_3_CH4_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH5
        GPIO_SetFunc(PWM_TMRA_3_CH5_PORT, PWM_TMRA_3_CH5_PIN, PWM_TMRA_3_CH5_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH6
        GPIO_SetFunc(PWM_TMRA_3_CH6_PORT, PWM_TMRA_3_CH6_PIN, PWM_TMRA_3_CH6_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH7
        GPIO_SetFunc(PWM_TMRA_3_CH7_PORT, PWM_TMRA_3_CH7_PIN, PWM_TMRA_3_CH7_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH8
        GPIO_SetFunc(PWM_TMRA_3_CH8_PORT, PWM_TMRA_3_CH8_PIN, PWM_TMRA_3_CH8_PIN_FUNC);
    #endif
        break;
#endif
#if defined(BSP_USING_PWM_TMRA_4)
    case (rt_uint32_t)CM_TMRA_4:
    #ifdef BSP_USING_PWM_TMRA_4_CH1
        GPIO_SetFunc(PWM_TMRA_4_CH1_PORT, PWM_TMRA_4_CH1_PIN, PWM_TMRA_4_CH1_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH2
        GPIO_SetFunc(PWM_TMRA_4_CH2_PORT, PWM_TMRA_4_CH2_PIN, PWM_TMRA_4_CH2_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH3
        GPIO_SetFunc(PWM_TMRA_4_CH3_PORT, PWM_TMRA_4_CH3_PIN, PWM_TMRA_4_CH3_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH4
        GPIO_SetFunc(PWM_TMRA_4_CH4_PORT, PWM_TMRA_4_CH4_PIN, PWM_TMRA_4_CH4_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH5
        GPIO_SetFunc(PWM_TMRA_4_CH5_PORT, PWM_TMRA_4_CH5_PIN, PWM_TMRA_4_CH5_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH6
        GPIO_SetFunc(PWM_TMRA_4_CH6_PORT, PWM_TMRA_4_CH6_PIN, PWM_TMRA_4_CH6_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH7
        GPIO_SetFunc(PWM_TMRA_4_CH7_PORT, PWM_TMRA_4_CH7_PIN, PWM_TMRA_4_CH7_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH8
        GPIO_SetFunc(PWM_TMRA_4_CH8_PORT, PWM_TMRA_4_CH8_PIN, PWM_TMRA_4_CH8_PIN_FUNC);
    #endif
        break;
#endif
#if defined(BSP_USING_PWM_TMRA_5)
    case (rt_uint32_t)CM_TMRA_5:
    #ifdef BSP_USING_PWM_TMRA_5_CH1
        GPIO_SetFunc(PWM_TMRA_5_CH1_PORT, PWM_TMRA_5_CH1_PIN, PWM_TMRA_5_CH1_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH2
        GPIO_SetFunc(PWM_TMRA_5_CH2_PORT, PWM_TMRA_5_CH2_PIN, PWM_TMRA_5_CH2_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH3
        GPIO_SetFunc(PWM_TMRA_5_CH3_PORT, PWM_TMRA_5_CH3_PIN, PWM_TMRA_5_CH3_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH4
        GPIO_SetFunc(PWM_TMRA_5_CH4_PORT, PWM_TMRA_5_CH4_PIN, PWM_TMRA_5_CH4_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH5
        GPIO_SetFunc(PWM_TMRA_5_CH5_PORT, PWM_TMRA_5_CH5_PIN, PWM_TMRA_5_CH5_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH6
        GPIO_SetFunc(PWM_TMRA_5_CH6_PORT, PWM_TMRA_5_CH6_PIN, PWM_TMRA_5_CH6_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH7
        GPIO_SetFunc(PWM_TMRA_5_CH7_PORT, PWM_TMRA_5_CH7_PIN, PWM_TMRA_5_CH7_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH8
        GPIO_SetFunc(PWM_TMRA_5_CH8_PORT, PWM_TMRA_5_CH8_PIN, PWM_TMRA_5_CH8_PIN_FUNC);
    #endif
        break;
#endif
#if defined(BSP_USING_PWM_TMRA_6)
    case (rt_uint32_t)CM_TMRA_6:
    #ifdef BSP_USING_PWM_TMRA_6_CH1
        GPIO_SetFunc(PWM_TMRA_6_CH1_PORT, PWM_TMRA_6_CH1_PIN, PWM_TMRA_6_CH1_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH2
        GPIO_SetFunc(PWM_TMRA_6_CH2_PORT, PWM_TMRA_6_CH2_PIN, PWM_TMRA_6_CH2_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH3
        GPIO_SetFunc(PWM_TMRA_6_CH3_PORT, PWM_TMRA_6_CH3_PIN, PWM_TMRA_6_CH3_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH4
        GPIO_SetFunc(PWM_TMRA_6_CH4_PORT, PWM_TMRA_6_CH4_PIN, PWM_TMRA_6_CH4_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH5
        GPIO_SetFunc(PWM_TMRA_6_CH5_PORT, PWM_TMRA_6_CH5_PIN, PWM_TMRA_6_CH5_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH6
        GPIO_SetFunc(PWM_TMRA_6_CH6_PORT, PWM_TMRA_6_CH6_PIN, PWM_TMRA_6_CH6_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH7
        GPIO_SetFunc(PWM_TMRA_6_CH7_PORT, PWM_TMRA_6_CH7_PIN, PWM_TMRA_6_CH7_PIN_FUNC);
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH8
        GPIO_SetFunc(PWM_TMRA_6_CH8_PORT, PWM_TMRA_6_CH8_PIN, PWM_TMRA_6_CH8_PIN_FUNC);
    #endif
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif
