 /*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       						Notes
 * 2025-12-02     Car12(1085582540@qq.com)       	first version

 */
#include <rtthread.h>


#define DBG_TAG "PWM"
#define DBG_LEVEL         DBG_LOG
#include <rtdbg.h>
#include "board.h"
/**
 * @brief enable gpio rcc
 * 
 * @param  gpio_grp         
 */
void n32_gpio_rcc_enable(GPIO_Module *gpio_grp)
{
    assert_param(IS_GPIO_ALL_PERIPH(gpio_grp));
    if (GPIOA == gpio_grp)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
         LOG_D("enable gpio rcc GPIOA");
    }
    else if (GPIOB == gpio_grp)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        LOG_D("enable gpio rcc GPIOB");
    }
    else if (GPIOC == gpio_grp)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
         LOG_D("enable gpio rcc GPIOC");
    }
    else if (GPIOD == gpio_grp)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
         LOG_D("enable gpio rcc GPIOD");
    }
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    else if (GPIOE == gpio_grp)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
    }
#if defined(SOC_N32G45X) 
    else if (GPIOF == gpio_grp)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
    }
    else if (GPIOG == gpio_grp)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
    }
#endif
#endif
}

/**
 * @brief 
 * 
 * @param  gpio_grp         
 * @param  pin              
 * 
 * The pin of Timer 2 involves the debug pin of SWD-JTAG. When reusing, it is necessary to first set the reuse of jSWD-JTAG
               JTMS/SWDIO 		PA13-----------swd
               JTCK/SWCLK 		A14------------swd
               JTDI 			PA15
               JTDO 			PB3
               NJTRST 			PB4

            * GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE,ENABLE);
 */
void gpio_remap_JTAGOFF_SWDON(GPIO_Module *gpio_grp, uint16_t pin)
{
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)

    if ((GPIOA == gpio_grp && GPIO_PIN_15) ||
        (GPIOB == gpio_grp && GPIO_PIN_3) ||
        (GPIOB == gpio_grp && GPIO_PIN_4))
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE, ENABLE);
    }
#endif
}

/**
 * @brief  enable time rcc
 */
void n32_time_rcc_config(TIM_Module *htim)
{
    RT_ASSERT(TIM1 == htim || TIM2 == htim || TIM3 == htim || TIM4 == htim || TIM5 == htim || TIM8 == htim
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    );
#else
              || TIM9 == htim);
#endif

    if (TIM1 == htim)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
    }
    else if (TIM2 == htim)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
    }
    else if (TIM3 == htim)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
    }
    else if (TIM4 == htim)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
    }
    else if (TIM5 == htim)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
    }
    else if (TIM8 == htim)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
    }
#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    else if (TIM9 == htim)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM9, ENABLE);
    }
#endif
}
