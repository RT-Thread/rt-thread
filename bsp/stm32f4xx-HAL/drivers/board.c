/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */

#include <rtthread.h>
#include "board.h"

/**
 * @addtogroup STM32
 */

/*@{*/

static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
#ifdef RT_USING_RTC
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
#endif
    /**Configure the main internal regulator output voltage 
    */
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
#ifdef RT_USING_RTC
    RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
#endif
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE/1000000UL);//Get 1M clock
    RCC_OscInitStruct.PLL.PLLN = (HCLK_VALUE/1000000UL)*2;//Get 2*HCLK_VALUE
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;//Get HCLK_VALUE
    RCC_OscInitStruct.PLL.PLLQ = RCC_OscInitStruct.PLL.PLLN/48;//Get 48M Clock
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        while(1)
        {}
    }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;

#if (RT_HSE_HCLK <= 42000000UL)
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        while(1)
        {}
    }
#elif (RT_HSE_HCLK <= 84000000UL)
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        while(1)
        {}
    }
#elif (RT_HSE_HCLK <= 168000000UL)
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        while(1)
        {}
    }
#else
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
        while(1)
        {}
    }
#endif
#ifdef RT_USING_RTC
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        while(1)
        {}
    }
#endif
}
/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    /* tick for HAL Library */
    HAL_IncTick();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/* re-implementat tick interface for STM32 HAL */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    /*Configure the SysTick to have interrupt in 1ms time basis*/
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / RT_TICK_PER_SECOND);

    /*Configure the SysTick IRQ priority */
    HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority , 0);

    /* Return function status */
    return HAL_OK;
}

void HAL_Delay(__IO uint32_t Delay)
{
    rt_thread_delay(Delay);
}

void HAL_SuspendTick(void)
{
    /* we should not suspend tick */
}

void HAL_ResumeTick(void)
{
    /* we should not resume tick */
}
void HAL_MspInit(void)
{

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  /* BusFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  /* UsageFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  /* SVCall_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  /* DebugMonitor_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
    
    /* Configure the system clock @ 84 Mhz */
    SystemClock_Config();
	
    HAL_Init();
	
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



/*@}*/
