/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-12     Steven Liu   first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "hal_base.h"
#include "hal_bsp.h"
#include "drv_cache.h"
#include "drv_heap.h"

#ifdef RT_USING_CRU
#include "drv_clock.h"
#endif

#ifdef RT_USING_PIN
#include "iomux.h"
#endif

#ifdef RT_USING_UART
#include "drv_uart.h"
#endif

#ifdef RT_USING_MODULE
#define DATA_EXEC_FLAG   0U
#else
#define DATA_EXEC_FLAG   1U
#endif

#ifdef RT_USING_CRU
rt_weak const struct clk_init clk_inits[] =
{
    INIT_CLK("SCLK_SHRM", SCLK_SHRM, 10 * MHZ),
    INIT_CLK("PCLK_SHRM", PCLK_SHRM, 10 * MHZ),
    INIT_CLK("PCLK_ALIVE", PCLK_ALIVE, 10 * MHZ),
    INIT_CLK("HCLK_ALIVE", HCLK_ALIVE, 10 * MHZ),
    INIT_CLK("HCLK_M4", HCLK_M4, 10 * MHZ),
    INIT_CLK("ACLK_LOGIC", ACLK_LOGIC, 10 * MHZ),
    INIT_CLK("HCLK_LOGIC", HCLK_LOGIC, 10 * MHZ),
    INIT_CLK("PCLK_LOGIC", PCLK_LOGIC, 10 * MHZ),
    INIT_CLK("SCLK_SFC_SRC", SCLK_SFC_SRC, 5 * MHZ),
    INIT_CLK("SCLK_SFC1_SRC", SCLK_SFC1_SRC, 5 * MHZ),
    INIT_CLK("PLL_GPLL", PLL_GPLL, 1188 * MHZ),
    INIT_CLK("PLL_CPLL", PLL_CPLL, 1188 * MHZ),
    INIT_CLK("SCLK_SFC_SRC", SCLK_SFC_SRC, 50 * MHZ),
    INIT_CLK("HCLK_M4", HCLK_M4, 300 * MHZ),
    INIT_CLK("ACLK_DSP", ACLK_DSP, 400 * MHZ),
    INIT_CLK("ACLK_LOGIC", ACLK_LOGIC, 300 * MHZ),
    INIT_CLK("HCLK_LOGIC", HCLK_LOGIC, 150 * MHZ),
    INIT_CLK("PCLK_LOGIC", PCLK_LOGIC, 150 * MHZ),
    INIT_CLK("SCLK_SHRM", SCLK_SHRM, 300 * MHZ),
    INIT_CLK("PCLK_SHRM", PCLK_SHRM, 100 * MHZ),
    INIT_CLK("PCLK_ALIVE", PCLK_ALIVE, 100 * MHZ),
    INIT_CLK("HCLK_ALIVE", HCLK_ALIVE, 100 * MHZ),
    { /* sentinel */ },
};

rt_weak const struct clk_unused clks_unused[] =
{
    {0, 0, 0x00030003},
    {0, 5, 0x00ee00ee},
    {0, 6, 0x048d048d},
    {0, 7, 0x00110011},
    {0, 11, 0x40e040e0},
    {0, 12, 0x90709070},
    {0, 13, 0xe203e203},
    {0, 14, 0xa6e1a6e1},
    { /* sentinel */ },
};
#endif

#if defined(RT_USING_UART0)
rt_weak const struct uart_board g_uart0_board =
{
    .baud_rate = ROCKCHIP_UART_BAUD_RATE_DEFAULT,
    .dev_flag = ROCKCHIP_UART_SUPPORT_FLAG_DEFAULT,
    .bufer_size = RT_SERIAL_RB_BUFSZ,
    .name = "uart0",
};
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
rt_weak const struct uart_board g_uart1_board =
{
    .baud_rate = ROCKCHIP_UART_BAUD_RATE_DEFAULT,
    .dev_flag = ROCKCHIP_UART_SUPPORT_FLAG_DEFAULT,
    .bufer_size = RT_SERIAL_RB_BUFSZ,
    .name = "uart1",
};
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART2)
rt_weak const struct uart_board g_uart2_board =
{
    .baud_rate = ROCKCHIP_UART_BAUD_RATE_DEFAULT,
    .dev_flag = ROCKCHIP_UART_SUPPORT_FLAG_DEFAULT,
    .bufer_size = RT_SERIAL_RB_BUFSZ,
    .name = "uart2",
};
#endif /* RT_USING_UART2 */

extern void SysTick_Handler(void);
rt_weak void tick_isr(int vector, void *param)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_IncTick();
    rt_tick_increase();
#ifdef TICK_TIMER
    HAL_TIMER_ClrInt(TICK_TIMER);
#endif

    /* leave interrupt */
    rt_interrupt_leave();
}

void BSP_MPU_Init(void)
{
    static const ARM_MPU_Region_t table[] =
    {
        {
            .RBAR = ARM_MPU_RBAR(0U, 0x04000000U),
            .RASR = ARM_MPU_RASR(0U, ARM_MPU_AP_FULL, 0U, 0U, 1U, 0U, 0U, ARM_MPU_REGION_SIZE_1MB)
        },
        {
            .RBAR = ARM_MPU_RBAR(1U, 0x18000000U),
            .RASR = ARM_MPU_RASR(0U, ARM_MPU_AP_FULL, 0U, 0U, 1U, 0U, 0U, ARM_MPU_REGION_SIZE_32MB)
        },
        {
            .RBAR = ARM_MPU_RBAR(2U, 0x20000000U),
            .RASR = ARM_MPU_RASR(DATA_EXEC_FLAG, ARM_MPU_AP_FULL, 0U, 0U, 1U, 1U, 0U, ARM_MPU_REGION_SIZE_1MB)
        },
        {
            .RBAR = ARM_MPU_RBAR(3U, 0x40000000U),
            .RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 0U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_256MB)
        },
        {
            .RBAR = ARM_MPU_RBAR(4U, 0x60000000U),
            .RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 0U, 0U, 1U, 1U, 0U, ARM_MPU_REGION_SIZE_256MB)
        },
    };

    ARM_MPU_Load(&(table[0]), 5U);

#ifdef RT_USING_UNCACHE_HEAP
    ARM_MPU_Region_t uncache_region;

    uncache_region.RBAR = ARM_MPU_RBAR(5U, RK_UNCACHE_HEAP_START);
    uncache_region.RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 0U, 0U, 0U, 0U, 0U, RT_UNCACHE_HEAP_ORDER);
    ARM_MPU_SetRegionEx(5, uncache_region.RBAR, uncache_region.RASR);
#endif

    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);
}

/**
 *  Initialize the Hardware related stuffs. Called from rtthread_startup()
 *  after interrupt disabled.
 */
void rt_hw_board_init(void)
{
    /* HAL_Init */
    HAL_Init();

    /* hal bsp init */
    BSP_Init();

    /* tick init */
    HAL_SetTickFreq(1000 / RT_TICK_PER_SECOND);
    rt_hw_interrupt_install(TICK_IRQn, tick_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(TICK_IRQn);
    HAL_NVIC_SetPriority(TICK_IRQn, NVIC_PERIPH_PRIO_LOWEST, NVIC_PERIPH_SUB_PRIO_LOWEST);
#ifdef RT_USING_SYSTICK
    HAL_SYSTICK_CLKSourceConfig(HAL_SYSTICK_CLKSRC_EXT);
    HAL_SYSTICK_Config((PLL_INPUT_OSC_RATE / RT_TICK_PER_SECOND) - 1);
    HAL_SYSTICK_Enable();
#else
    HAL_TIMER_Init(TICK_TIMER, TIMER_FREE_RUNNING);
    HAL_TIMER_SetCount(TICK_TIMER, (PLL_INPUT_OSC_RATE / RT_TICK_PER_SECOND) - 1);
    HAL_TIMER_Start_IT(TICK_TIMER);
#endif

    rt_hw_cpu_cache_init();

#ifdef RT_USING_PIN
#ifdef RK_BSP_TEMP
    rt_hw_iomux_config();
#endif
#endif

#ifdef RT_USING_CRU
#ifdef RK_BSP_TEMP
    clk_init(clk_inits, false);

    /* disable some clks when init, and enabled by device when needed */
    clk_disable_unused(clks_unused);
    if (RT_CONSOLE_DEVICE_UART(0))
        CRU->CRU_CLKGATE_CON[2] = 0x08860886;
    else if (RT_CONSOLE_DEVICE_UART(1))
        CRU->CRU_CLKGATE_CON[2] = 0x080d080d;
    else if (RT_CONSOLE_DEVICE_UART(2))
        CRU->CRU_CLKGATE_CON[2] = 0x008b008b;
    else
        CRU->CRU_CLKGATE_CON[2] = 0x088f088f;
#endif
#endif

#ifdef RT_USING_UART
    rt_hw_usart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

