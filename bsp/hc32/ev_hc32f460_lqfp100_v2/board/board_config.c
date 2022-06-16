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

#if defined(RT_USING_CAN)
void CanPhyEnable(void)
{
    GPIO_ResetPins(CAN_STB_PORT, CAN_STB_PIN);
    GPIO_OutputCmd(CAN_STB_PORT, CAN_STB_PIN, ENABLE);
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
    #ifdef BSP_USING_ADC1_IN0
        (void)GPIO_Init(ADC1_IN0_PORT, ADC1_IN0_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC1_IN1
        (void)GPIO_Init(ADC1_IN1_PORT, ADC1_IN1_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC1_IN2
        (void)GPIO_Init(ADC1_IN2_PORT, ADC1_IN2_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC1_IN3
        (void)GPIO_Init(ADC1_IN3_PORT, ADC1_IN3_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN4
        (void)GPIO_Init(ADC12_IN4_PORT, ADC12_IN4_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN5
        (void)GPIO_Init(ADC12_IN5_PORT, ADC12_IN5_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN6
        (void)GPIO_Init(ADC12_IN6_PORT, ADC12_IN6_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN7
        (void)GPIO_Init(ADC12_IN7_PORT, ADC12_IN7_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN8
        (void)GPIO_Init(ADC12_IN8_PORT, ADC12_IN8_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN9
        (void)GPIO_Init(ADC12_IN9_PORT, ADC12_IN9_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN10
        (void)GPIO_Init(ADC12_IN10_PORT, ADC12_IN10_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN11
        (void)GPIO_Init(ADC12_IN11_PORT, ADC12_IN11_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC1_IN12
        (void)GPIO_Init(ADC1_IN12_PORT, ADC1_IN12_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC1_IN13
        (void)GPIO_Init(ADC1_IN13_PORT, ADC1_IN13_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC1_IN14
        (void)GPIO_Init(ADC1_IN14_PORT, ADC1_IN14_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC1_IN15
        (void)GPIO_Init(ADC1_IN15_PORT, ADC1_IN15_PIN, &stcGpioInit);
    #endif
        break;
#endif
#if defined(BSP_USING_ADC2)
    case (rt_uint32_t)CM_ADC2:
    #ifdef BSP_USING_ADC12_IN4
        (void)GPIO_Init(ADC12_IN4_PORT, ADC12_IN4_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN5
        (void)GPIO_Init(ADC12_IN5_PORT, ADC12_IN5_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN6
        (void)GPIO_Init(ADC12_IN6_PORT, ADC12_IN6_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN7
        (void)GPIO_Init(ADC12_IN7_PORT, ADC12_IN7_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN8
        (void)GPIO_Init(ADC12_IN8_PORT, ADC12_IN8_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN9
        (void)GPIO_Init(ADC12_IN9_PORT, ADC12_IN9_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN10
        (void)GPIO_Init(ADC12_IN10_PORT, ADC12_IN10_PIN, &stcGpioInit);
    #endif
    #ifdef BSP_USING_ADC12_IN11
        (void)GPIO_Init(ADC12_IN11_PORT, ADC12_IN11_PIN, &stcGpioInit);
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
