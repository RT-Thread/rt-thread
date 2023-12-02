/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-7      SummerGift   first version
 */

#include "drv_common.h"
#include <board.h>

#ifdef RT_USING_PIN
#include <drv_gpio.h>
#endif

#ifdef RT_USING_SERIAL
#ifdef RT_USING_SERIAL_V2
#include <drv_usart_v2.h>
#else
#include <drv_usart.h>
#endif /* RT_USING_SERIAL */
#endif /* RT_USING_SERIAL_V2 */

#define DBG_TAG    "drv_common"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */

extern __IO uint32_t uwTick;
static uint32_t _systick_ms = 1;

/* SysTick configuration */
void rt_hw_systick_init(void)
{
    HAL_SYSTICK_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    NVIC_SetPriority(SysTick_IRQn, 0xFF);

    _systick_ms = 1000u / RT_TICK_PER_SECOND;
    if(_systick_ms == 0)
        _systick_ms = 1;
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        HAL_IncTick();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

uint32_t HAL_GetTick(void)
{
    if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        HAL_IncTick();

    return uwTick;
}

void HAL_IncTick(void)
{
    uwTick += _systick_ms;
}

void HAL_SuspendTick(void)
{
}

void HAL_ResumeTick(void)
{
}

void HAL_Delay(__IO uint32_t Delay)
{
    if (rt_thread_self())
    {
        rt_thread_mdelay(Delay);
    }
    else
    {
        for (rt_uint32_t count = 0; count < Delay; count++)
        {
            rt_hw_us_delay(1000);
        }
    }
}

/* re-implement tick interface for STM32 HAL */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
    rt_hw_systick_init();

    /* Return function status */
    return HAL_OK;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char *s, int num)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    LOG_E("Error_Handler at file:%s num:%d", s, num);
    while (1)
    {
    }
    /* USER CODE END Error_Handler */
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint64_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * (reload / (1000000 / RT_TICK_PER_SECOND));
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

/**
 * This function will initial STM32 board.
 */
rt_weak void rt_hw_board_init(void)
{
#ifdef BSP_SCB_ENABLE_I_CACHE
    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();
#endif

#ifdef BSP_SCB_ENABLE_D_CACHE
    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();
#endif

    /* HAL_Init() function is called at the beginning of the program */
    HAL_Init();

    /* System clock initialization */
    SystemClock_Config();

#if defined(RT_USING_HEAP)
    /* Heap initialization */
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_PIN
    rt_hw_pin_init();
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
