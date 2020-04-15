/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     isr.c
 * @brief    source file for the interrupt server route
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <drv_common.h>
#include "config.h"
#include "soc.h"

extern void dw_usart_irqhandler(int32_t idx);
extern void dw_timer_irqhandler(int32_t idx);
extern void dw_gpio_irqhandler(int32_t idx);
extern void dw_iic_irqhandler(int32_t idx);
extern void ck_rtc_irqhandler(int32_t idx);
extern void dw_spi_irqhandler(int32_t idx);
extern void dw_wdt_irqhandler(int32_t idx);
extern void ck_dma_irqhandler(int32_t idx);
extern void ck_aes_irqhandler(int32_t idx);
extern void ck_sha_irqhandler(int32_t idx);
#ifdef CONFIG_KERNEL_FREERTOS
extern void CKTimer1Isr(void);
extern void CKPendSVIsr(void);
#endif

#define readl(addr) \
    ({ unsigned int __v = (*(volatile unsigned int *) (addr)); __v; })

__attribute__((isr)) void CORET_IRQHandler(void)
{
    readl(0xE000E010);
}

#if defined(CONFIG_USART)
/*
__attribute__((isr)) void USART0_IRQHandler(void)
{
    dw_usart_irqhandler(0);
}


__attribute__((isr)) void USART1_IRQHandler(void)
{
    dw_usart_irqhandler(1);
}


__attribute__((isr)) void USART2_IRQHandler(void)
{
    dw_usart_irqhandler(2);
}

__attribute__((isr)) void USART3_IRQHandler(void)
{
    dw_usart_irqhandler(3);
}
*/
#endif

#if defined(CONFIG_TIMER)
__attribute__((isr)) void TIMA0_IRQHandler(void)
{
    dw_timer_irqhandler(0);
}

__attribute__((isr)) void TIMA1_IRQHandler(void)
{
    dw_timer_irqhandler(1);
}
__attribute__((isr)) void TIMB0_IRQHandler(void)
{
    dw_timer_irqhandler(2);
}

__attribute__((isr)) void TIMB1_IRQHandler(void)
{
    dw_timer_irqhandler(3);
}

#endif

#if defined(CONFIG_GPIO)

__attribute__((isr)) void GPIOA_IRQHandler(void)
{
    dw_gpio_irqhandler(0);
}

__attribute__((isr)) void GPIOB_IRQHandler(void)
{
    dw_gpio_irqhandler(1);
}
#endif

#if defined(CONFIG_IIC)
__attribute__((isr)) void I2C0_IRQHandler(void)
{
    dw_iic_irqhandler(0);
}

__attribute__((isr)) void I2C1_IRQHandler(void)
{
    dw_iic_irqhandler(1);
}
#endif

#if defined(CONFIG_RTC)

__attribute__((isr)) void RTC_IRQHandler(void)
{
    ck_rtc_irqhandler(0);
}

#endif

#if defined(CONFIG_AES)

__attribute__((isr)) void AES_IRQHandler(void)
{
    ck_aes_irqhandler(0);
}

#endif

#if defined(CONFIG_SHA)

__attribute__((isr)) void SHA_IRQHandler(void)
{
    ck_sha_irqhandler(0);
}

#endif

#if defined(CONFIG_SPI) && defined(CONFIG_GPIO)
__attribute__((isr)) void SPI0_IRQHandler(void)
{
    dw_spi_irqhandler(0);
}

__attribute__((isr)) void SPI1_IRQHandler(void)
{
    dw_spi_irqhandler(1);
}
#endif

#if defined(CONFIG_WDT)
__attribute__((isr)) void WDT_IRQHandler(void)
{
    dw_wdt_irqhandler(0);
}
#endif

#if defined(CONFIG_DMAC)
__attribute__((isr)) void DMAC_IRQHandler(void)
{
    ck_dma_irqhandler(0);
}
#endif
