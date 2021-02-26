/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      source file for the interrupt server route
 */

#include <drv_common.h>
#include <csi_config.h>
#include "soc.h"

#ifndef CONFIG_SYSTICK_HZ
#define CONFIG_SYSTICK_HZ 100
#endif

extern volatile uint32_t rt_thread_switch_interrupt_flag;

extern void ck_usart_irqhandler(int32_t idx);
extern void dw_timer_irqhandler(int32_t idx);
extern void dw_gpio_irqhandler(int32_t idx);
extern void systick_handler(void);
extern void xPortSysTickHandler(void);
extern void OSTimeTick(void);

#define  ATTRIBUTE_ISR

#define readl(addr) \
    ({ unsigned int __v = (*(volatile unsigned int *) (addr)); __v; })


#if(CONFIG_KERNEL_RTTHREAD == 1)
#define  CSI_INTRPT_ENTER()  rt_interrupt_enter()
#define  CSI_INTRPT_EXIT()   rt_interrupt_leave()
#endif


void __attribute__((isr)) SysTick_Handler(void)
{
#if(CONFIG_KERNEL_RTTHREAD == 1)
    CSI_INTRPT_ENTER();
#endif

    csi_coret_config(drv_get_sys_freq() / CONFIG_SYSTICK_HZ, CORET_IRQn);
    
#if defined(CONFIG_KERNEL_RHINO)
    systick_handler();
#elif defined(CONFIG_KERNEL_FREERTOS)
    xPortSysTickHandler();
#elif defined(CONFIG_KERNEL_RTTHREAD)
    rt_tick_increase();
#elif defined(CONFIG_KERNEL_UCOS)
    OSTimeTick();
#endif

#if(CONFIG_KERNEL_RTTHREAD == 1)
    CSI_INTRPT_EXIT();
#endif
}

ATTRIBUTE_ISR void USART_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    ck_usart0_irqhandler();
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM0_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(0);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM1_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(1);
    CSI_INTRPT_EXIT();
}
ATTRIBUTE_ISR void TIM2_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(2);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM3_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(3);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM4_NMIHandler(void)
{
    dw_timer_irqhandler(4);
}

ATTRIBUTE_ISR void TIM6_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(6);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM7_IRQHandler(void)
{
    dw_timer_irqhandler(7);
}

ATTRIBUTE_ISR void TIM8_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(8);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM9_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(9);
    CSI_INTRPT_EXIT();
}
ATTRIBUTE_ISR void TIM10_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(10);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void TIM11_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_timer_irqhandler(11);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO0_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(0);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO1_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(1);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO2_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(2);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO3_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(3);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO4_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(4);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO5_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(5);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO6_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(6);
    CSI_INTRPT_EXIT();
}

ATTRIBUTE_ISR void GPIO7_IRQHandler(void)
{
    CSI_INTRPT_ENTER();
    dw_gpio_irqhandler(7);
    CSI_INTRPT_EXIT();
}
