/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-03-01     wangyq        the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_uart.h"
#include "drv_gpio.h"
#include <ald_cmu.h>
#include <ald_gpio.h>

/**
 * @addtogroup es32f0
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
    /* hosc 12MHz, from hosc/3 pll to 48MHz */
    cmu_pll1_config(CMU_PLL1_INPUT_HOSC_3, CMU_PLL1_OUTPUT_48M);

    /*  MCLK 48MHz*/
    cmu_clock_config(CMU_CLOCK_PLL1, 48000000);
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
    rt_uint32_t _mclk;
    rt_uint32_t _sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);

    /* get hrc clock*/
    _mclk = cmu_get_clock();

    /* SYSCLK = MCLK/SYSDIV */
    SysTick_Config(_mclk / (RT_TICK_PER_SECOND << _sys_div));
}

/**
 * This is the timer interrupt service routine.
 *
 */
void systick_irq_cbk(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/*@}*/
/**
 * This function will initial ES32F0 board.
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
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
