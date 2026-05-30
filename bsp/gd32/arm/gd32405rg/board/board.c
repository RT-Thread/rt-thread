/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-08     ShiHongChao  first implementation
 */
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef RT_USING_SERIAL_V2
#include "drv_usart_v2.h"
#else
#include "drv_usart.h"
#endif


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    while (1)
    {
    }
    /* USER CODE END Error_Handler */
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, 0);
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

static void system_clock_8M_200M(void);

/**
 * This function will initial GD32 board.
 */
void rt_hw_board_init()
{
    /* config system clock HSE 8M to 200M */
    system_clock_8M_200M();

    /* NVIC Configuration */
#define NVIC_VTOR_MASK 0x3FFFFF80
#ifdef VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    SCB->VTOR = (0x08000000 & NVIC_VTOR_MASK);
#endif

    SystemClock_Config();

#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

#ifdef BSP_USING_SDRAM
    rt_system_heap_init((void *)EXT_SDRAM_BEGIN, (void *)EXT_SDRAM_END);
#else
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/**
 * @brief config system clock HSE 8M PLL to 200M
 * @param none
 */
static void system_clock_8M_200M(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* reset RCU */
    rcu_deinit();

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do
    {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while ((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if (0U == (RCU_CTL & RCU_CTL_HXTALSTB))
    {
        while (1)
        {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL |= PMU_CTL_LDOVS;

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 8, PLL_N = 400, PLL_P = 2, PLL_Q = 9 */
    RCU_PLL = (8U | (400U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL) | (9U << 24U));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while (0U == (RCU_CTL & RCU_CTL_PLLSTB))
    {
    }

    /* Enable the high-drive to extend the clock frequency to 200 Mhz */
    PMU_CTL |= PMU_CTL_HDEN;
    while (0U == (PMU_CS & PMU_CS_HDRF))
    {
    }

    /* select the high-drive mode */
    PMU_CTL |= PMU_CTL_HDS;
    while (0U == (PMU_CS & PMU_CS_HDSRF))
    {
    }

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLLP;

    /* wait until PLL is selected as system clock */
    while (0U == (RCU_CFG0 & RCU_SCSS_PLLP))
    {
    }

    /* Update SystemCoreClock variable */
    SystemCoreClock = 200000000U; // 200MHz
}

/*@}*/
