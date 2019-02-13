/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2017-10-20     ZYH          emmm...setup for HAL Libraries
 * 2017-11-15     ZYH            update to 3.0.0
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"

/**
 * @addtogroup STM32
 */

/*@{*/

void HAL_MspInit(void)
{
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    /* System interrupt init*/
    __HAL_RCC_AFIO_CLK_ENABLE();
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
    /**DISABLE: JTAG-DP Disabled and SW-DP Disabled**/
    __HAL_AFIO_REMAP_SWJ_NOJTAG();
}


void SystemClock_Config(void)
{
    rt_err_t ret = RT_EOK;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    
#if !defined(RT_USING_HSI)
    /* Initializes the CPU, AHB and APB busses clocks */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL9;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if(ret == HAL_TIMEOUT)
    {
        /* HSE timeout switch to HSI */
        rt_memset(&RCC_OscInitStruct, 0, sizeof(RCC_OscInitStruct));
        RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
        RCC_OscInitStruct.HSICalibrationValue = 16;
        RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI_DIV2;
        RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL16;
        ret = HAL_RCC_OscConfig(&RCC_OscInitStruct); 
        RT_ASSERT(ret == HAL_OK);
    }
    
    /* Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | 
                                       RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
    RT_ASSERT(ret == HAL_OK);
    
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / RT_TICK_PER_SECOND);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
#else
    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL16;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct); 
    RT_ASSERT(ret == HAL_OK);

    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK | 
                                       RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2); 
    RT_ASSERT(ret == HAL_OK);
    
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/RT_TICK_PER_SECOND);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
#endif
}

static void m3_m4_delay_us(rt_uint32_t us)
{
    __IO uint32_t Delay = us * (SystemCoreClock / 8U / 1000000U);
    do 
    {
        __NOP();
    } 
    while (Delay --);
}

void HAL_Delay(__IO uint32_t Delay)
{
    m3_m4_delay_us(Delay * 10);
}

extern __IO uint32_t uwTick;
uint32_t HAL_GetTick(void)
{
    HAL_Delay(1);
    uwTick ++;
    return uwTick;
}

void HAL_SuspendTick(void)
{
    /* we should not suspend tick */
}

void HAL_ResumeTick(void)
{
    /* we should not resume tick */
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_IncTick();
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init(void)
{
    HAL_Init();
    SystemClock_Config();
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
    us_tick = SystemCoreClock / 1000000UL;
    do{
        now = SysTick->VAL;
        delta = start > now ? start - now : reload + start - now;
    } while(delta <  us_tick * us);
}
