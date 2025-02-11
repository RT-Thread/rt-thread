/*
 * Copyright (c) 2022-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-22     chasel   first version
 */

#include <rtthread.h>
#include "mm32_device.h"
#include "mm32_msp.h"

void mm32_msp_uart_init(void *instance)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_TypeDef *uart_x = (UART_TypeDef *)instance;

#ifdef BSP_USING_UART1
    if(UART1 == uart_x)
    {
        /* Enable UART clock */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

        /* Configure USART Rx/tx PIN */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_High;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
    }
#endif
#ifdef BSP_USING_UART2
    if(UART2 == uart_x)
    {
        /* Enable UART clock */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

        /* Configure USART Rx/tx PIN */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_High;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
    }
#endif
#ifdef BSP_USING_UART3
    if(UART3 == uart_x)
    {
        /* Enable UART clock */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

        GPIO_InitTypeDef GPIO_InitStructure;
        /* Configure USART Rx/tx PIN */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_High;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_7);
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_7);
    }
#endif
    /* add others */
}

#ifdef BSP_USING_ADC
void mm32_msp_adc_init(void *instance)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    ADC_TypeDef *adc_x = (ADC_TypeDef *)instance;

#ifdef BSP_USING_ADC1
    if(adc_x == ADC1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Enable ADC1 clock
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

        /* configure adc channel as analog input */
        GPIO_StructInit(&GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_High;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#endif

#ifdef BSP_USING_ADC2
    if(adc_x == ADC2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //Enable ADC2 clock
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

        /* configure adc channel as analog input */
        GPIO_StructInit(&GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_High;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#endif
}
#endif /* BSP_USING_ADC */

