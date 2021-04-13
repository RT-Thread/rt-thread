/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-13     shelton      first version
 */

#include <at32f4xx.h>
#include <rtthread.h>
#include "at32_msp.h"

#ifdef BSP_USING_UART
void at32_msp_usart_init(void *Instance)
{
    GPIO_InitType GPIO_InitStruct;
    USART_Type *USARTx = (USART_Type *)Instance;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
#ifdef BSP_USING_UART1
    if(USART1 == USARTx)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_USART1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_9;
        GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_10;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#endif
#ifdef BSP_USING_UART2
    if(USART2 == USARTx)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_2;
        GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_3;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#endif
#ifdef BSP_USING_UART3
    if(USART3 == USARTx)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART3, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_10;
        GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_11;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SERIAL */

#ifdef BSP_USING_SPI
void at32_msp_spi_init(void *Instance)
{
    GPIO_InitType GPIO_InitStruct;
    SPI_Type *SPIx = (SPI_Type *)Instance;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
#ifdef BSP_USING_SPI1
    if(SPI1 == SPIx)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_SPI1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_4;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_5 | GPIO_Pins_7;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_6;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#endif
#ifdef BSP_USING_SPI2
    if(SPI2 == SPIx)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_SPI2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_12;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_13 | GPIO_Pins_15;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_14;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SPI */

#ifdef BSP_USING_SDIO
void at32_msp_sdio_init(void *Instance)
{
    GPIO_InitType GPIO_InitStructure;
    SDIO_Type *SDIOx = (SDIO_Type *)Instance;

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;

    if(SDIO1 == SDIOx)
    {
        /* if used dma ... */
        RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_DMA2, ENABLE);

        RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_SDIO1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOC | RCC_APB2PERIPH_GPIOD, ENABLE);
        GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8 | GPIO_Pins_9 | GPIO_Pins_10 | GPIO_Pins_11 | GPIO_Pins_12;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pins = GPIO_Pins_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }
}
#endif /* BSP_USING_SDIO */

#ifdef BSP_USING_PWM
void at32_msp_tmr_init(void *Instance)
{
    GPIO_InitType GPIO_InitStructure;
    TMR_Type *TMRx = (TMR_Type *)Instance;

    if(TMRx == TMR1)
    {
        /* TMR1 clock enable */
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_TMR1, ENABLE);
        /* GPIOA clock enable */
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);

        /* GPIOA Configuration:TMR1 Channel1 and Channel4 as alternate function push-pull */
        GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8 | GPIO_Pins_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;

        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }

    if(TMRx == TMR2)
    {
        /* TMR2 clock enable */
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR2, ENABLE);
        /* GPIOA clock enable */
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);

        /* GPIOA Configuration:TMR2 Channel1 and Channel2 as alternate function push-pull */
        GPIO_InitStructure.GPIO_Pins = GPIO_Pins_0 | GPIO_Pins_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;

        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    /* Add others */
}
#endif /* BSP_USING_PWM */

#ifdef BSP_USING_ADC
void at32_msp_adc_init(void *Instance)
{
    GPIO_InitType GPIO_InitStruct;
    ADC_Type *ADCx = (ADC_Type *)Instance;

#ifdef BSP_USING_ADC1
    if(ADCx == ADC1)
    {
        /* ADC1 & GPIO clock enable */
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_ADC1 | RCC_APB2PERIPH_GPIOA | RCC_APB2PERIPH_GPIOB | RCC_APB2PERIPH_GPIOC,ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_StructInit(&GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_0 | GPIO_Pins_1 | GPIO_Pins_2 | GPIO_Pins_3 | GPIO_Pins_4 | GPIO_Pins_5;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_ANALOG;
        GPIO_Init(GPIOC, &GPIO_InitStruct);

    }
#endif

#ifdef BSP_USING_ADC2
    if(ADCx == ADC2)
    {
        /* ADC2 & GPIO clock enable */
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_ADC2 | RCC_APB2PERIPH_GPIOA | RCC_APB2PERIPH_GPIOB | RCC_APB2PERIPH_GPIOC,ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_StructInit(&GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_0 | GPIO_Pins_1 | GPIO_Pins_2 | GPIO_Pins_3 | GPIO_Pins_4 | GPIO_Pins_5;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_ANALOG;
        GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
#endif
}
#endif /* BSP_USING_ADC */

#ifdef BSP_USING_HWTIMER
void at32_msp_hwtmr_init(void *Instance)
{
    TMR_Type *TMRx = (TMR_Type *)Instance;

#ifdef BSP_USING_HWTMR3
    if(TMRx == TMR3)
    {
        /* TMR3 clock enable */
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR3, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTMR4
    if(TMRx == TMR4)
    {
        /* TMR4 clock enable */
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR4, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTMR5
    if(TMRx == TMR5)
    {
        /* TMR5 clock enable */
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR5, ENABLE);
    }
#endif
}
#endif

#ifdef BSP_USING_CAN
void at32_msp_can_init(void *Instance)
{
    GPIO_InitType GPIO_InitStruct;
    CAN_Type *CANx = (CAN_Type *)Instance;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
#ifdef BSP_USING_CAN1
    if(CAN1 == CANx)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_CAN1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_12;
        GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_11;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#endif
#ifdef BSP_USING_CAN2
    if(CAN2 == CANx)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_CAN2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_AFIO, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);
        GPIO_PinsRemapConfig(AFIO_MAP6_CAN2_0001, ENABLE);
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_6;
        GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStruct.GPIO_Pins = GPIO_Pins_5;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
#endif
}
#endif /* BSP_USING_CAN */
