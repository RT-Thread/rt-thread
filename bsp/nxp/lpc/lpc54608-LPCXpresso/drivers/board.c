/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-02-04     Magicoe      ported to LPC17xx
 * 2010-05-02     Aozima       update CMSIS to 130
 * 2017-08-02     XiaoYang     porting to LPC54608 bsp
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "clock_config.h"
#include "drv_uart.h"
#include "drv_sdram.h"

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

/**
 * This function will initial LPC54xx board.
 */
void rt_hw_board_init()
{
    /* Hardware Initialization */
    CLOCK_EnableClock(kCLOCK_InputMux);
    CLOCK_EnableClock(kCLOCK_Iocon);

    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x00000000 */
    SCB->VTOR  = (0x00000000 & NVIC_VTOR_MASK);
#endif

    BOARD_BootClockFROHF48M();
    /* init systick  1 systick = 1/(100M / 100) 100 systicks = 1s*/
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /* Heap initialization */
#ifdef RT_USING_HEAP
#ifdef BSP_DRV_SDRAM
    rt_kprintf("      heap: [0x%08x - 0x%08x]\n", LPC_EXT_SDRAM_BEGIN, LPC_EXT_SDRAM_END);
    rt_system_heap_init((void *)LPC_EXT_SDRAM_BEGIN, (void *)LPC_EXT_SDRAM_END);
    sram_init();
#else
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#endif

    /*init uart device*/
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef BSP_DRV_SDRAM
    lpc_sdram_hw_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization board with RT-Thread Components */
    rt_components_board_init();
#endif
}

#ifdef PKG_USING_GUIENGINE
#include <rtgui/driver.h>
#include "drv_lcd.h"

/* initialize for gui driver */
int rtgui_lcd_init(void)
{
    rt_device_t device;

    rt_hw_lcd_init();

    device = rt_device_find("lcd");
    /* set graphic device */
    rtgui_graphic_set_device(device);

    return 0;
}
INIT_DEVICE_EXPORT(rtgui_lcd_init);
#endif

void MemManage_Handler(void)
{
    extern void HardFault_Handler(void);

    rt_kprintf("Memory Fault!\n");
    HardFault_Handler();
}
