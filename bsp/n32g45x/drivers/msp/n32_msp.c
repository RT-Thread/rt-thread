/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

#include <n32g45x.h>
#include <rtthread.h>
#include "n32_msp.h"

#ifdef BSP_USING_SERIAL
void n32_msp_usart_init(void *Instance)
{
    GPIO_InitType GPIO_InitStructs;
    USART_Module *USARTx = (USART_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitStructs);
    GPIO_InitStructs.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_UART1
    if(USART1 == USARTx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitStructs.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructs.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructs);

        GPIO_InitStructs.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructs.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructs);
    }
#endif
#ifdef BSP_USING_UART2
    if(USART2 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitStructs.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructs.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructs);

        GPIO_InitStructs.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructs.Pin = GPIO_PIN_3;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructs);
    }
#endif
#ifdef BSP_USING_UART3
    if(USART3 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitStructs.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructs.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructs);

        GPIO_InitStructs.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructs.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructs);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SERIAL */







