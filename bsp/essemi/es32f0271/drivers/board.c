/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_uart.h"
#include "drv_gpio.h"
#include "md_gpio.h"

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
    /*-------------------------Clock Config-------------------------/
     * Config system clock to 48MHz of which the clock source
     * is PLL0.
     */
    
    //
    // Open PLL0/HRC then wait it ready.
    //
    SET_BIT(RCU->CON, RCU_CON_PLL0ON_MSK);
    SET_BIT(RCU->CON, RCU_CON_HRCON_MSK);

    /* Wait HRC clock steady. */
    while (!READ_BIT(RCU->CON, RCU_CON_HRCRDY_MSK));

    //
    // Change system clock source,PLL0,48MHz.
    //
    /* Chose PLL0 as system clock. */
    MODIFY_REG(RCU->CFG, RCU_CFG_SW_MSK, (0x4 << RCU_CFG_SW_POSS));
    /* Config mul of PLL0. */
    MODIFY_REG(RCU->CFG, RCU_CFG_PLLMUL_MSK, (11 << RCU_CFG_PLLMUL_POSS));

    //
    // Start to change system clock and wait it ready.
    //
    /* Config flash read wait time. */
    MODIFY_REG(FC->CON, FC_CON_WAIT_MSK, (0X2 << FC_CON_WAIT_POSS));
    /* Start to change. */
    SET_BIT(RCU->CFG, RCU_CFG_CKCFG_MSK);

    /* Wait system clock ready. */
    while (!READ_BIT(RCU->CON, RCU_CON_SWRDY_MSK));

    //
    // Remember the system clock.
    //
    SystemCoreClock = 48000000;
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
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
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

