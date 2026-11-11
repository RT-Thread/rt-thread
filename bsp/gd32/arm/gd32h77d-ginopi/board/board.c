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

#ifdef BSP_USING_LCD_MIPI
#ifndef BSP_USING_SDRAM
#error "MIPI LCD requires SDRAM"
#endif

#define BOARD_DMA_MPU_SUBREGION_SIZE    (512U * 1024U)
#ifdef BSP_USING_OV7670
#define BOARD_DMA_MPU_SIZE              EXT_SDRAM_LCD_SCANOUT_SIZE
#else
#define BOARD_DMA_MPU_SIZE              EXT_SDRAM_LCD_RESERVED_SIZE
#endif
#define BOARD_EXT_GUARD_ATTR            ARM_MPU_RASR(1U, ARM_MPU_AP_NONE, 0U, \
                                                     1U, 0U, 0U, 0x87U, \
                                                     ARM_MPU_REGION_SIZE_4GB)

/* SDRAM board initialization must finish before its windows become cacheable. */
static void board_mpu_config(void)
{
    mpu_region_init_struct mpu_config;
    rt_base_t level;

    RT_ASSERT((SCB->CCR & SCB_CCR_DC_Msk) == 0U);
    RT_ASSERT(EXT_SDRAM_LCD_RESERVED_SIZE <= 8U * BOARD_DMA_MPU_SUBREGION_SIZE);
    RT_ASSERT((EXT_SDRAM_LCD_RESERVED_SIZE % BOARD_DMA_MPU_SUBREGION_SIZE) == 0U);
    RT_ASSERT((BOARD_DMA_MPU_SIZE > 0U) &&
              (BOARD_DMA_MPU_SIZE <= EXT_SDRAM_LCD_RESERVED_SIZE));
    RT_ASSERT((BOARD_DMA_MPU_SIZE % BOARD_DMA_MPU_SUBREGION_SIZE) == 0U);

    level = rt_hw_interrupt_disable();
    __DSB();
    ARM_MPU_Disable();

    mpu_region_struct_para_init(&mpu_config);
    /* Match the reference project's AXI-SRAM write-through attributes. */
    mpu_config.region_base_address = 0x24000000U;
    mpu_config.region_size = MPU_REGION_SIZE_1MB;
    mpu_config.access_permission = MPU_AP_FULL_ACCESS;
    mpu_config.access_bufferable = MPU_ACCESS_NON_BUFFERABLE;
    mpu_config.access_cacheable = MPU_ACCESS_CACHEABLE;
    mpu_config.access_shareable = MPU_ACCESS_NON_SHAREABLE;
    mpu_config.region_number = MPU_REGION_NUMBER1;
    mpu_config.subregion_disable = MPU_SUBREGION_ENABLE;
    mpu_config.instruction_exec = MPU_INSTRUCTION_EXEC_PERMIT;
    mpu_config.tex_type = MPU_TEX_TYPE0;
    mpu_region_config(&mpu_config);
    mpu_region_enable();

    if (rt_hw_sdram_is_ready())
    {
        /* CPU-rendered layers can spill out of AXI SRAM into the SDRAM heap. */
        mpu_config.region_base_address = EXT_SDRAM_BEGIN;
        mpu_config.region_size = MPU_REGION_SIZE_32MB;
        mpu_config.access_permission = MPU_AP_FULL_ACCESS;
        mpu_config.access_bufferable = MPU_ACCESS_BUFFERABLE;
        mpu_config.access_cacheable = MPU_ACCESS_CACHEABLE;
        mpu_config.access_shareable = MPU_ACCESS_NON_SHAREABLE;
        mpu_config.region_number = MPU_REGION_NUMBER5;
        mpu_config.subregion_disable = MPU_SUBREGION_ENABLE;
        mpu_config.instruction_exec = MPU_INSTRUCTION_EXEC_NOT_PERMIT;
        mpu_config.tex_type = MPU_TEX_TYPE1;
        mpu_region_config(&mpu_config);
        mpu_region_enable();

        /* Keep scanout/IPA buffers write-through. Camera and LVGL draw buffers
         * reside in AXI SRAM; the SDRAM heap retains its write-back policy.
         * Preserve the existing 3 MiB reservation and heap addresses. */
        mpu_config.region_size = MPU_REGION_SIZE_4MB;
        mpu_config.access_bufferable = MPU_ACCESS_NON_BUFFERABLE;
        mpu_config.region_number = MPU_REGION_NUMBER6;
        mpu_config.subregion_disable = (rt_uint8_t)(0xFFU <<
            (BOARD_DMA_MPU_SIZE / BOARD_DMA_MPU_SUBREGION_SIZE));
        mpu_config.tex_type = MPU_TEX_TYPE0;
        mpu_region_config(&mpu_config);
        mpu_region_enable();
    }

#if !defined(BSP_USING_OSPI1)
    /* Block speculative accesses to unused external windows (0x60000000..
     * 0xDFFFFFFF). Regions 5/6 override this guard for valid SDRAM.
     * The OSPI0 Flash driver uses indirect transfers, not the mapped window.
     * Mapped OSPI needs its own accessible MPU regions before using this guard. */
    MPU->RNR = MPU_REGION_NUMBER0;
    if ((MPU->RASR & MPU_RASR_ENABLE_Msk) == 0U)
    {
        ARM_MPU_SetRegionEx(MPU_REGION_NUMBER0, 0U, BOARD_EXT_GUARD_ATTR);
    }
#endif

    ARM_MPU_Enable(MPU_MODE_PRIV_DEFAULT);
    __DSB();
    __ISB();
    rt_hw_interrupt_enable(level);
}
#endif /* BSP_USING_LCD_MIPI */

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

#ifdef BSP_USING_LCD_MIPI
    board_mpu_config();
#endif
    /* Board drivers, including SDRAM, ran with uncached data accesses. */
    rt_hw_cpu_dcache_enable();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
}

/*@}*/
