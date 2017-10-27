/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "usart.h"

/* ARM PLL configuration for RUN mode */
const clock_arm_pll_config_t armPllConfig = { .loopDivider = 100U };

/* SYS PLL configuration for RUN mode */
const clock_sys_pll_config_t sysPllConfig = { .loopDivider = 1U };

/* USB1 PLL configuration for RUN mode */
const clock_usb_pll_config_t usb1PllConfig = { .loopDivider = 0U };

static void BOARD_BootClockGate(void)
{
    /* Disable all unused peripheral clock */
    CCM->CCGR0 = 0x00C0000FU;
    CCM->CCGR1 = 0x30000000U;
    CCM->CCGR2 = 0x003F0030U;
    CCM->CCGR3 = 0xF0000330U;
    CCM->CCGR4 = 0x0000FF3CU;
    CCM->CCGR5 = 0xF000330FU;
    CCM->CCGR6 = 0x00FC0300U;
}

static void BOARD_BootClockRUN(void)
{
    /* Boot ROM did initialize the XTAL, here we only sets external XTAL OSC freq */
    CLOCK_SetXtalFreq(24000000U);
    CLOCK_SetRtcXtalFreq(32768U);
    
    CLOCK_SetMux(kCLOCK_PeriphClk2Mux, 0x1); /* Set PERIPH_CLK2 MUX to OSC */
    CLOCK_SetMux(kCLOCK_PeriphMux, 0x1); /* Set PERIPH_CLK MUX to PERIPH_CLK2 */   
    
    /* Setting the VDD_SOC to 1.5V. It is necessary to config AHB to 600Mhz */
    DCDC->REG3 = (DCDC->REG3 & (~DCDC_REG3_TRG_MASK)) | DCDC_REG3_TRG(0x12);
    
    CLOCK_InitArmPll(&armPllConfig); /* Configure ARM PLL to 1200M */
#ifndef SKIP_SYSCLK_INIT
    CLOCK_InitSysPll(&sysPllConfig); /* Configure SYS PLL to 528M */
#endif
#ifndef SKIP_USB_PLL_INIT    
    CLOCK_InitUsb1Pll(&usb1PllConfig); /* Configure USB1 PLL to 480M */
#endif    
    CLOCK_SetDiv(kCLOCK_ArmDiv, 0x1); /* Set ARM PODF to 0, divide by 2 */
    CLOCK_SetDiv(kCLOCK_AhbDiv, 0x0); /* Set AHB PODF to 0, divide by 1 */ 
    CLOCK_SetDiv(kCLOCK_IpgDiv, 0x3); /* Set IPG PODF to 3, divede by 4 */ 
    
    CLOCK_SetMux(kCLOCK_PrePeriphMux, 0x3); /* Set PRE_PERIPH_CLK to PLL1, 1200M */    
    CLOCK_SetMux(kCLOCK_PeriphMux, 0x0); /* Set PERIPH_CLK MUX to PRE_PERIPH_CLK */       
    
    /* Disable unused clock */
    BOARD_BootClockGate();    
    
    /* Power down all unused PLL */    
    CLOCK_DeinitAudioPll();
    CLOCK_DeinitVideoPll();
    CLOCK_DeinitEnetPll();
    CLOCK_DeinitUsb2Pll();

    /* Configure UART divider to default */
    CLOCK_SetMux(kCLOCK_UartMux, 0); /* Set UART source to PLL3 80M */
    CLOCK_SetDiv(kCLOCK_UartDiv, 0); /* Set UART divider to 1 */    
    
    /* Update core clock */
    SystemCoreClockUpdate();
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

/**
 * This function will initial LPC8XX board.
 */
void rt_hw_board_init()
{
    BOARD_BootClockRUN();
    
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    extern int imxrt_hw_usart_init(void);
    imxrt_hw_usart_init();
    
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    
#ifdef RT_USING_HEAP
    rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
#endif
}

/*@}*/
