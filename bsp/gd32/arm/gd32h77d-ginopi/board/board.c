/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-08     CYFS         configure boot vectors and display memory cache policy
 */
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef BSP_USING_LCD_MIPI
#include "gd32h77x_78x_misc.h"
#endif

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
extern void Reset_Handler(void);
extern uint32_t __initial_sp;

__attribute__((section(".ARM.__at_0x08000000"), used))
const uint32_t boot_fuction_table[] =
{
    (uint32_t)&__initial_sp,
    (uint32_t)&Reset_Handler,
};
#elif defined(__GNUC__)
extern void Reset_Handler(void);
extern uint32_t _sp;

__attribute__((section(".boot_fuction_table"), used))
const uint32_t boot_fuction_table[] =
{
    (uint32_t)&_sp,
    (uint32_t)&Reset_Handler,
};
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

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint64_t required_ticks;
    rt_uint32_t previous;
    rt_uint32_t current;
    rt_uint32_t elapsed = 0U;
    rt_uint32_t reload = SysTick->LOAD;

    required_ticks = (rt_uint64_t)us *
                     (reload / (1000000U / RT_TICK_PER_SECOND));
    previous = SysTick->VAL;
    while (elapsed < required_ticks)
    {
        current = SysTick->VAL;
        if (current != previous)
        {
            elapsed += (current < previous) ?
                       (previous - current) :
                       (reload - current + previous);
            previous = current;
        }
    }
}

/**
 * This function will initial GD32 board.
 */
void rt_hw_board_init()
{
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08010000 */
    SCB->VTOR  = (0x08010000 & NVIC_VTOR_MASK);
#endif

    /* Reset entry (or a bootloader handoff) must leave D-Cache disabled. */
    RT_ASSERT((SCB->CCR & SCB_CCR_DC_Msk) == 0U);

    /* Instruction caching does not change the SDRAM data attributes. */
    rt_hw_cpu_icache_enable();

    SystemClock_Config();

#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board drivers, including SDRAM, ran with uncached data accesses. */
    rt_hw_cpu_dcache_enable();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
}

/*@}*/
