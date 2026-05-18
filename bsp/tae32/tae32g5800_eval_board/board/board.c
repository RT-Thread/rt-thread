/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-12     yeml    first version
 */

 #include "board.h"

 void SystemClock_Config(void)
 {
     LL_StatusETypeDef ret;
     RCU_SysclkUserCfgTypeDef sysclk_cfg;
 
     //SYSCLK Clock Config
     sysclk_cfg.sysclk_src  = SYSCLK_SRC_PLL0DivClk;
     sysclk_cfg.sysclk_freq = 180000000UL;
     sysclk_cfg.pll0clk_src = PLLCLK_SRC_HSE;
     sysclk_cfg.pll0clk_src_freq = HSE_VALUE;
     sysclk_cfg.apb0_clk_div = RCU_CLK_DIV_2;
     sysclk_cfg.apb1_clk_div = RCU_CLK_DIV_2;
     sysclk_cfg.ahb_clk_div  = RCU_CLK_DIV_1;
     ret = LL_RCU_SysclkInit(RCU, &sysclk_cfg);
 
     if (ret == LL_OK) {
         SystemCoreClockUpdate(sysclk_cfg.sysclk_freq);
     }
 
     if (ret == LL_OK) {
         LL_RCU_USB_ClkCfg(RCU_CLK_SRC_PLL0, RCU_CLK_DIV_6);
     }
     if (ret == LL_OK) {
        LL_RCU_CAN_ClkCfg(RCU_CLK_SRC_PLL0, RCU_CLK_DIV_6);
    }
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
 
     LL_IncTick();
     /* leave interrupt */
     rt_interrupt_leave();
 }
 
 /**
  * This function will initial TAE32 board.
  */
void rt_hw_board_init()
{
     /* System Clock Update */
     SystemClock_Config();

     /* System Tick Configuration */
     LL_Init();
     
 #if defined(RT_USING_HEAP)
     /* Heap initialization */
     rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
 #endif
 
 #ifdef RT_USING_SERIAL
     rt_hw_usart_init();
 #endif
 
 #if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
     /* Set the shell console output device */
     rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
 #endif
 
 #if defined(RT_USING_CONSOLE) && defined(RT_USING_NANO)
     extern void rt_hw_console_init(void);
     rt_hw_console_init();
 #endif

 #ifdef RT_USING_COMPONENTS_INIT
     /* Board underlying hardware initialization */
     rt_components_board_init();
 #endif
 }