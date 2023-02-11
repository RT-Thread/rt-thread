/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#include <stdio.h>
#include <string.h>
#include <rtthread.h>
#include <rtdevice.h>
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
    if (USART1 == USARTx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
#ifdef BSP_USING_UART1_PIN_RMP
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_USART1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_7;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#endif
    }

#endif /* BSP_USING_UART1 */
#ifdef BSP_USING_UART2

    if (USART2 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
#ifdef BSP_USING_UART2_PIN_RMP1
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_USART2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);

#elif defined (BSP_USING_UART2_PIN_RMP2)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMCP2_USART2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_8;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);

#elif defined (BSP_USING_UART2_PIN_RMP3)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_USART2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);

#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#endif
    }

#endif /* BSP_USING_UART2 */
#ifdef BSP_USING_UART3

    if (USART3 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
#if defined(BSP_USING_UART3_PIN_PART_RMP)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_PART_RMP_USART3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#elif defined(BSP_USING_UART3_PIN_ALL_RMP)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_ALL_RMP_USART3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_8;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#endif
    }

#endif /* BSP_USING_UART3 */
#ifdef BSP_USING_UART4

    if (UART4 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART4, ENABLE);
#if defined(BSP_USING_UART4_PIN_RMP1)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_UART4, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOE, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_7;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
#elif defined(BSP_USING_UART4_PIN_RMP2)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_UART4, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_13;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_14;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#elif defined(BSP_USING_UART4_PIN_RMP3)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART4, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#endif
    }

#endif /* BSP_USING_UART4 */
#ifdef BSP_USING_UART5

    if (UART5 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART5, ENABLE);
#if defined(BSP_USING_UART5_PIN_RMP1)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_UART5, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_13;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_14;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#elif defined(BSP_USING_UART5_PIN_RMP2)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_UART5, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_8;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
#elif defined(BSP_USING_UART5_PIN_RMP3)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART5, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_8;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
#endif
    }

#endif /* BSP_USING_UART5 */
#ifdef BSP_USING_UART6

    if (UART6 == USARTx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_UART6, ENABLE);
#if defined(BSP_USING_UART6_PIN_RMP2)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_UART6, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#elif defined(BSP_USING_UART6_PIN_RMP3)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART6, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#else /* BSP_USING_UART6_PIN_NORMP */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
#endif
    }

#endif /* BSP_USING_UART6 */
#ifdef BSP_USING_UART7

    if (UART7 == USARTx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_UART7, ENABLE);
#if defined(BSP_USING_UART7_PIN_RMP1)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_UART7, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#elif defined(BSP_USING_UART7_PIN_RMP3)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_UART7, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0;
        GPIO_InitPeripheral(GPIOG, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitPeripheral(GPIOG, &GPIO_InitCtlStruct);
#else /* BSP_USING_UART7_PIN_NORMP */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#endif
    }

#endif /* BSP_USING_UART7 */
    /* Add others */
}
#endif /* BSP_USING_SERIAL */

#ifdef BSP_USING_SPI
void n32_msp_deinit(void *Instance)
{
    SPI_Module *SPIx = (SPI_Module *)Instance;
    SPI_Enable(SPIx, DISABLE);
    SPI_I2S_DeInit(SPIx);
    if (SPI1 == SPIx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, DISABLE);
    }
    else if (SPI2 == SPIx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, DISABLE);
    }
    else if (SPI3 == SPIx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3, DISABLE);
    }
}

void n32_msp_spi_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    SPI_Module *SPIx = (SPI_Module *)Instance;

    n32_msp_deinit(SPIx);

    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_SPI1
    if (SPI1 == SPIx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE);
#if   defined (BSP_USING_SPI1_PIN_RMP1)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_SPI1, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_15;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3 | GPIO_PIN_5;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#elif defined (BSP_USING_SPI1_PIN_RMP2)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_SPI1, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);

#elif defined (BSP_USING_SPI1_PIN_RMP3)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_SPI1, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_7 | GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_8;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#endif

    }
#endif
#ifdef BSP_USING_SPI2
    if (SPI2 == SPIx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);
#if   defined (BSP_USING_SPI1_PIN_RMP1)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_SPI2, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_7 | GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_8;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#elif   defined (BSP_USING_SPI2_PIN_RMP2)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_SPI2, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11 | GPIO_PIN_13;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOE, &GPIO_InitCtlStruct);
#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_13 | GPIO_PIN_15;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_14;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#endif
    }
#endif
#ifdef BSP_USING_SPI3
    if (SPI3 == SPIx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3, ENABLE);
#if   defined (BSP_USING_SPI3_PIN_RMP1)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP1_SPI3, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
#endif
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10 | GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#elif   defined (BSP_USING_SPI3_PIN_RMP2)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP2_SPI3, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_8;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9 | GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStruct);
#elif   defined (BSP_USING_SPI3_PIN_RMP3)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP3_SPI3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#else
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
#if   defined (BSP_USING_SPI_NSS_PIN)
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_15;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#endif
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3 | GPIO_PIN_5;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#endif
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

    if (SDIO == SDIOx)
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
void n32_msp_tim_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStructure;
    GPIO_InitStruct(&GPIO_InitCtlStructure);
    TIM_Module *TIMx = (TIM_Module *)Instance;

    if (TIMx == TIM1)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
    }

    if (TIMx == TIM2)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
    }

    if (TIMx == TIM3)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitCtlStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
        GPIO_InitCtlStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStructure);
    }

    if (TIMx == TIM4)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitCtlStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStructure);
    }

    if (TIMx == TIM5)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
    }

    if (TIMx == TIM8)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitCtlStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStructure);
    }
}
#endif /* BSP_USING_PWM */

#ifdef BSP_USING_ADC
void n32_msp_adc_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    GPIO_InitStruct(&GPIO_InitCtlStruct);
    ADC_Module *ADCx = (ADC_Module *)Instance;

#ifdef BSP_USING_ADC1
    if (ADCx == ADC1)
    {
        /* ADC1 & GPIO clock enable */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);
        ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV8);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitCtlStruct.GPIO_Speed = GPIO_INPUT;
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
    }
#endif

#ifdef BSP_USING_ADC2
    if (ADCx == ADC2)
    {
        /* ADC2 & GPIO clock enable */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC2, ENABLE);
        ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV8);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitCtlStruct.GPIO_Speed = GPIO_INPUT;
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
    }
#endif
}
#endif /* BSP_USING_ADC */

#ifdef BSP_USING_HWTIMER
void n32_msp_hwtim_init(void *Instance)
{
    TIM_Module *TIMx = (TIM_Module *)Instance;

#ifdef BSP_USING_HWTIM3
    if (TIMx == TIM3)
    {
        /* TIM3 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM4
    if (TIMx == TIM4)
    {
        /* TIM4 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM5
    if (TIMx == TIM5)
    {
        /* TIM5 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM6
    if (TIMx == TIM6)
    {
        /* TIM6 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM7
    if (TIMx == TIM7)
    {
        /* TIM7 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM7, ENABLE);
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
    if (CAN1 == CANx)
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
    if (CAN2 == CANx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_13;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
}
#endif /* BSP_USING_CAN */

void n32_msp_jtag_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#if defined(BSP_RMP_SW_JTAG_NO_NJTRST)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_NO_NJTRST, ENABLE);
    /* Available pin: PB4 */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
#elif defined(BSP_RMP_SW_JTAG_SW_ENABLE)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE, ENABLE);
    /* Available pin: PB3, PB4, PA15 */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_15;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#elif defined(BSP_RMP_SW_JTAG_DISABLE)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_DISABLE, ENABLE);
    /* Available pin: PB3, PB4, PA13, PA14, PA15 */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IPU;
    GDPIO_InitCtlStruct.Pin = GPIO_PIN_4;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_13;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_14;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitCtlStruct.Pin = GPIO_PIN_15;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
#else
    return;
#endif
}


#ifdef RT_USING_FINSH
#include <finsh.h>
#if defined(BSP_USING_UART2) || defined(BSP_USING_UART3)
static void uart_test_rw(rt_device_t uartx, const char *name)
{
    if (uartx == NULL)
    {
        uartx = rt_device_find(name);
        rt_err_t err = rt_device_open(uartx, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX);
        RT_ASSERT(err == RT_EOK);
    }
    rt_device_write(uartx, 0, name, strlen(name));
    rt_device_write(uartx, 0, "\r\n", 2);
    uint8_t recv_buf[64] = {0x0};
    int ret = rt_device_read(uartx, 0, recv_buf, sizeof(recv_buf));
    if (ret != 0)
    {
        for (int i = 0; i < ret; ++i)
            rt_kprintf("[%02x]", recv_buf[i]);
    }
    rt_device_write(uartx, 0, "\r\n", 2);
}
static void uart_test(void)
{
#ifdef BSP_USING_UART2
    static rt_device_t u2 = NULL;
    uart_test_rw(u2, "uart2");
#endif
#ifdef BSP_USING_UART3
    static rt_device_t u3 = NULL;
    uart_test_rw(u3, "uart3");
#endif
}
MSH_CMD_EXPORT(uart_test, uart_test)
#endif

#ifdef BSP_USING_ADC
#ifdef BSP_USING_ADC1
    #define ADC_DEV_NAME        "adc1"
#else
    #define ADC_DEV_NAME        "adc2"
#endif
#define REFER_VOLTAGE       3300
#define CONVERT_BITS        (1 << 12)
static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    for (int i = 1; i <= 18; ++i)
    {
        ret = rt_adc_enable(adc_dev, i);
        value = rt_adc_read(adc_dev, i);
        rt_kprintf("ch=[%d] the value is :[%d] \n", i, value);
        vol = value * REFER_VOLTAGE / CONVERT_BITS;
        rt_kprintf("ch=[%d] the voltage is :[%d] \n", i, vol);
    }

    return ret;
}
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);
#endif

#ifdef BSP_USING_HWTIMER
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("timer name is :%s.\n", dev->parent.name);
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}
static int hwtimer_init(const char *name)
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;
    hw_dev = rt_device_find(name);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", name);
        return RT_ERROR;
    }
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", name);
        return ret;
    }
    rt_device_set_rx_indicate(hw_dev, timeout_cb);
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }
    timeout_s.sec = 5;
    timeout_s.usec = 0;
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    rt_thread_mdelay(3500);

    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}

static int hwtimer_sample(int argc, char *argv[])
{
#ifdef BSP_USING_HWTIM6
    hwtimer_init("timer6");
#endif
#ifdef BSP_USING_HWTIM7
    hwtimer_init("timer7");
#endif
    return RT_EOK;
}
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
#endif

#endif
