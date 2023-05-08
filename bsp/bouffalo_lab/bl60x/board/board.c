/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/03/15     flyingcys    first version
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

static void system_clock_init(void)
{
    GLB_Set_System_CLK(GLB_PLL_XTAL_40M, GLB_SYS_CLK_PLL192M);
    GLB_Set_MTimer_CLK(1, GLB_MTIMER_CLK_BCLK, 95);
}

static void peripheral_clock_init(void)
{
    PERIPHERAL_CLOCK_ADC_DAC_ENABLE();
    PERIPHERAL_CLOCK_SEC_ENABLE();
    PERIPHERAL_CLOCK_DMA0_ENABLE();
    PERIPHERAL_CLOCK_UART0_ENABLE();
    PERIPHERAL_CLOCK_UART1_ENABLE();
    PERIPHERAL_CLOCK_SPI0_ENABLE();
    PERIPHERAL_CLOCK_I2C0_ENABLE();
    PERIPHERAL_CLOCK_PWM0_ENABLE();
    PERIPHERAL_CLOCK_TIMER0_1_WDG_ENABLE();

    GLB_Set_UART_CLK(ENABLE, HBN_UART_CLK_160M, 0);
    GLB_Set_SPI_CLK(ENABLE, 0);
    GLB_Set_I2C_CLK(ENABLE, 0);

    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_XCLK, 1);
    GLB_Set_DAC_CLK(ENABLE, GLB_DAC_CLK_XCLK, 0x3E);
}

/* This is the timer interrupt service routine. */
static void systick_isr(void)
{
    rt_tick_increase();
}

void rt_hw_board_init(void)
{
    bflb_flash_init();

    system_clock_init();
    peripheral_clock_init();
    bflb_irq_initialize();

    bflb_mtimer_config(HW_MTIMER_CLOCK / RT_TICK_PER_SECOND, systick_isr);

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("RT_HW_HEAP_BEGIN:%x RT_HW_HEAP_END:%x\r\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void rt_hw_cpu_reset(void)
{
    GLB_SW_POR_Reset();
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
