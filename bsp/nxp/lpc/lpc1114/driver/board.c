/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-05     jg1uaa       the first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include "drv_uart.h"

#define SYSCON_BASE     0x40048000
#define MEMMAP          HWREG32(SYSCON_BASE + 0x000)
#define SYSPLLCTRL      HWREG32(SYSCON_BASE + 0x008)
#define SYSPLLSTAT      HWREG32(SYSCON_BASE + 0x00c)
#define SYSPLLCLKSEL    HWREG32(SYSCON_BASE + 0x040)
#define SYSPLLCLKUEN    HWREG32(SYSCON_BASE + 0x044)
#define MAINCLKSEL      HWREG32(SYSCON_BASE + 0x070)
#define MAINCLKUEN      HWREG32(SYSCON_BASE + 0x074)
#define AHBCLKCTRL      HWREG32(SYSCON_BASE + 0x080)
#define PDRUNCFG        HWREG32(SYSCON_BASE + 0x238)

#define SCB_BASE        0xe000e000
#define SYST_CSR        HWREG32(SCB_BASE + 0x010)
#define SYST_RVR        HWREG32(SCB_BASE + 0x014)
#define NVIC_ISER       HWREG32(SCB_BASE + 0x100)
#define NVIC_ICER       HWREG32(SCB_BASE + 0x180)
#define NVIC_ISPR       HWREG32(SCB_BASE + 0x200)
#define NVIC_ICPR       HWREG32(SCB_BASE + 0x280)
#define NVIC_IPR(irqno) HWREG32(SCB_BASE + 0x400 + (((irqno) / 4) << 2))
#define SCB_SHPR3       HWREG32(SCB_BASE + 0xd20)

extern unsigned char __bss_end__[];
extern unsigned char _ram_end[];

/**
 * This is the timer interrupt service routine.
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

rt_weak void UART_IRQHandler(void)
{
    
};

void os_clock_init(void)
{
    /* bump up system clock 12MHz to 48MHz, using IRC (internal RC) osc. */

    MAINCLKSEL = 0;             // main clock: IRC @12MHz (default, for safety)
    MAINCLKUEN = 0;
    MAINCLKUEN = 1;

    PDRUNCFG &= ~0x80;           // power up System PLL

    SYSPLLCLKSEL = 0;           // PLL clock source: IRC osc
    SYSPLLCLKUEN = 0;
    SYSPLLCLKUEN = 1;

    SYSPLLCTRL = 0x23;          // Fcco = 2 x P x FCLKOUT
                                //  192MHz = 2 x 2 x 48MHz
                                // M = FCLKOUT / FCLKIN
                                //  4 = 48MHz / 12MHz

    while (!(SYSPLLSTAT & 1));  // wait for lock PLL

    MAINCLKSEL = 3;             // main clock: system PLL
    MAINCLKUEN = 0;
    MAINCLKUEN = 1;

    AHBCLKCTRL |= (1 << 16);    // power up IOCON
}

void SysTick_init(void)
{
    rt_uint32_t shpr3;

    /* set SysTick interrupt priority */
    shpr3 = SCB_SHPR3;
    shpr3 &= ~0xff000000;
    shpr3 |= 0x40 << 24;
    SCB_SHPR3 = shpr3;

    /* start SysTick */
    SYST_CSR = 0x06;    // Clock source:Core, SysTick Exception:enable
    SYST_RVR = (CPU_CLOCK / RT_TICK_PER_SECOND) - 1;
    SYST_CSR = 0x07;    // Counter:enable
}

/**
 * This function initializes LPC1114 SoC.
 */
void rt_hw_board_init(void)
{
    os_clock_init();

    /* init SysTick */
    SysTick_init();

#ifdef RT_USING_HEAP
    /* initialize system heap */
    rt_system_heap_init((void *)&__bss_end__, (void *)&_ram_end);
#endif
    /* initialize uart */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/**
 * Enable External Interrupt
 */
void NVIC_EnableIRQ(rt_int32_t irqno)
{
    NVIC_ISER = 1UL << (irqno & 0x1f);
}

/**
 * Disable External Interrupt
 */
void NVIC_DisableIRQ(rt_int32_t irqno)
{
    NVIC_ICER = 1UL << (irqno & 0x1f);
}

/**
 * Get Pending Interrupt
 *      Different from CMSIS implementation,
 *      returns zero/non-zero, not zero/one.
 */
rt_uint32_t NVIC_GetPendingIRQ(rt_int32_t irqno)
{
    return NVIC_ISPR & (1UL << (irqno & 0x1f));
}

/**
 * Set Pending Interrupt
 */
void NVIC_SetPendingIRQ(rt_int32_t irqno)
{
    NVIC_ISPR = 1UL << (irqno & 0x1f);
}

/**
 * Clear Pending Interrupt
 */
void NVIC_ClearPendingIRQ(rt_int32_t irqno)
{
    NVIC_ICPR = 1UL << (irqno & 0x1f);
}

/**
 * Set Interrupt Priority
 *      Different from CMSIS implementation,
 *      this code supports only external (device specific) interrupt.
 */
void NVIC_SetPriority(rt_int32_t irqno, rt_uint32_t priority)
{
    rt_uint32_t shift, ipr;

    shift = (irqno % 4) * 8;
    ipr = NVIC_IPR(irqno);
    ipr &= ~(0xffUL << shift);
    ipr |= (priority & 0xff) << shift;
    NVIC_IPR(irqno) = ipr;
}
