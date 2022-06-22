/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-01-14     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_uart.h"
#include "drv_gpio.h"
#include <ald_gpio.h>
#include "ald_dma.h"

/**
 * @addtogroup es32f3
 */

/*@{*/

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
}

/*******************************************************************************
 * Function Name  : SystemClock_Configuration
 * Description    : Configures the System Clock.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SystemClock_Config(void)
{

    SYSCFG_UNLOCK();
#if  ES_CMU_LRC_EN
    SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
#endif  /*ES_CMU_LRC_EN*/

#if ES_CMU_LOSC_EN
    SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
#endif  /*ES_CMU_LOSC_EN*/

#if ES_CMU_HRC_EN
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
#endif  /*ES_CMU_HRC_EN*/

#if ES_CMU_HOSC_EN
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
#endif  /*ES_CMU_HOSC_EN*/

    SYSCFG_LOCK();

#if  ES_CMU_PLL1_EN
    /*PLL的源必须是4M*/
    ald_cmu_pll1_config(ES_PLL1_REFER_CLK, ES_PLL1_OUT_CLK);

    #if ES_CMU_PLL1_SAFE_EN
        ald_cmu_pll_safe_config(ENABLE);
    #else
        ald_cmu_pll_safe_config(DISABLE);
    #endif

#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
#endif  /*ES_CMU_PLL1_EN*/

    ald_cmu_clock_config(ES_SYS_CLK_SOURSE, ES_SYS_CLK);

    ald_cmu_div_config(CMU_SYS,ES_CMU_SYS_DIV);
    ald_cmu_div_config(CMU_HCLK_1,ES_CMU_HCLK_1_DIV);
    ald_cmu_div_config(CMU_HCLK_2,ES_CMU_HCLK_2_DIV);
    ald_cmu_div_config(CMU_PCLK_1,ES_CMU_PCLK_1_DIV);
    ald_cmu_div_config(CMU_PCLK_2,ES_CMU_PCLK_2_DIV);

    ald_cmu_perh_clock_config(CMU_PERH_ALL, ENABLE);

/*低功耗时钟使能*/
#ifdef RT_USING_PM
        SYSCFG_UNLOCK();
        SET_BIT(CMU->LPENR, CMU_LPENR_LRCEN_MSK);
        SET_BIT(CMU->LPENR, CMU_LPENR_LOSCEN_MSK);
        SET_BIT(CMU->LPENR, CMU_LPENR_HRCEN_MSK);
        SET_BIT(CMU->LPENR, CMU_LPENR_HOSCEN_MSK);
        SYSCFG_LOCK();
#endif

}

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
    /* ticks = sysclk / RT_TICK_PER_SECOND */
    SysTick_Config(ald_cmu_get_sys_clock() / RT_TICK_PER_SECOND);

    __systick_interval = 1;
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    ald_inc_tick();
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This is the cmu interrupt service.
 *
 */
void CMU_Handler(void)
{
    ald_cmu_irq_handler();
}
/**
 * This is the DMA interrupt service.
 *
 */
void DMA_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    ald_dma_irq_handler();
    /* leave interrupt */
    rt_interrupt_leave();
}
/*@}*/
/**
 * This function will initial ES32F3 board.
 */
void rt_hw_board_init(void)
{
    /* NVIC Configuration */
    NVIC_Configuration();
    /*System Clock Configuration */
    SystemClock_Config();
    /* Configure the SysTick */
    SysTick_Configuration();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#ifdef BSP_USING_DMA0
    ald_cmu_perh_clock_config(CMU_PERH_DMA, ENABLE);
    ald_dma_init(DMA0);
#endif
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    unsigned int start, now, delta, reload, us_tick;
    start = SysTick->VAL;
    reload = SysTick->LOAD;
    us_tick = ald_cmu_get_sys_clock() / 1000000UL;
    do
    {
        now = SysTick->VAL;
        delta = start > now ? start - now : reload + start - now;
    }
    while (delta <  us_tick * us);
}
