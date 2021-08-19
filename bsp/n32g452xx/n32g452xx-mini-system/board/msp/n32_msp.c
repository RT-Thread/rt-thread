/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-13     shelton      first version
 */


#include <rtthread.h>
#include "n32g45x.h"
#include "n32_msp.h"

#ifdef BSP_USING_UART
void n32_msp_usart_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    USART_Module *USARTx = (USART_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_UART1
    if(USART1 == USARTx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_UART2
    if(USART2 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_UART3
    if(USART3 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SERIAL */

#ifdef BSP_USING_SPI
void n32_msp_spi_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    SPI_Module *SPIx = (SPI_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_SPI1
    if(SPI1 == SPIx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_SPI2
    if(SPI2 == SPIx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_13 | GPIO_PIN_15;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_14;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SPI */

#ifdef BSP_USING_SDIO
void n32_msp_sdio_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStructure;
    SDIO_Module *SDIOx = (SDIO_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStructure);
    GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if(SDIO == SDIOx)
    {
        /* if used dma ... */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);

        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_SDIO, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStructure);

        GPIO_InitCtlStructure.Pin = GPIO_PIN_2;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStructure);
    }
}
#endif /* BSP_USING_SDIO */

#ifdef BSP_USING_PWM
void n32_msp_tmr_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStructure;
    GPIO_InitStruct(&GPIO_InitCtlStructure);
    TIM_Module *TIMx = (TIM_Module *)Instance;

    if(TIMx == TIM1)
    {
        /* TIM1 clock enable */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
        /* GPIOA clock enable */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

        /* GPIOA Configuration:TIM1 Channel1 and Channel4 as alternate function push-pull */
        GPIO_InitCtlStructure.Pin = GPIO_PIN_8 | GPIO_PIN_11;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
    }

    if(TIMx == TIM2)
    {
        /* TIM2 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
        /* GPIOA clock enable */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

        /* GPIOA Configuration:TIM2 Channel1 and Channel2 as alternate function push-pull */
        GPIO_InitCtlStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
    }
    /* Add others */
}
#endif /* BSP_USING_PWM */

#ifdef BSP_USING_ADC
void n32_msp_adc_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    GPIO_InitStruct(&GPIO_InitCtlStruct);
    ADC_Module *ADCx = (ADC_Module *)Instance;

#ifdef BSP_USING_ADC1
    if(ADCx == ADC1)
    {
        /* ADC1 & GPIO clock enable */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);
        ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV8);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0;
        GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
    }
#endif

#ifdef BSP_USING_ADC2
    if(ADCx == ADC2)
    {
        /* ADC2 & GPIO clock enable */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC2, ENABLE);
        ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV8);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
    }
#endif
}
#endif /* BSP_USING_ADC */

#ifdef BSP_USING_HWTIMER
void n32_msp_hwtmr_init(void *Instance)
{
    TIM_Module *TIMx = (TIM_Module *)Instance;

#ifdef BSP_USING_HWTIM3
    if(TIMx == TIM3)
    {
        /* TIM3 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM4
    if(TIMx == TIM4)
    {
        /* TIM4 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM5
    if(TIMx == TIM5)
    {
        /* TIM5 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
    }
#endif
}
#endif

#ifdef BSP_USING_CAN
void n32_msp_can_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    CAN_Module *CANx = (CAN_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_CAN1
    if(CAN1 == CANx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_CAN2
    if(CAN2 == CANx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
//        GPIO_PinsRemapConfig(AFIO_MAP6_CAN2_0001, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
}
#endif /* BSP_USING_CAN */

