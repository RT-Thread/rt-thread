/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-23     aozima       first implementation for PIC32.
 */

// Adds support for PIC32 Peripheral library functions and macros
#include <plib.h>
#include <rtthread.h>

// Configuration Bits
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (PIC32 Starter Kit: use divide by 2 only)
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = XT            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = OFF           // Debugger Disabled for Starter Kit

//  The following is used by the main application
#define SYS_FREQ        (80000000UL)

#define PB_DIV              (1 << ((OSCCON&_OSCCON_PBDIV0_MASK)>>_OSCCON_PBDIV0_POSITION) )
#define PRESCALE            256
#define TOGGLES_PER_SEC     RT_TICK_PER_SECOND
#define T1_TICK             (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)

static void rt_hw_show_info(void)
{
    rt_kprintf("\r\n\r\n---------- board info ----------\r\n");
    rt_kprintf("DEVICE_FAMILY:    PIC32\r\n");
    rt_kprintf("CPU_ARCHITECTURE: MIPS\r\n");
    rt_kprintf("CPU_FREQ:         %uMHz\r\n",SYS_FREQ/1000000UL);
}

static void rt_hw_timer_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
* This function will initial board.
 */
void rt_hw_board_init()
{
    // Configure the device for maximum performance, but do not change the PBDIV clock divisor.
    // Given the options, this function will change the program Flash wait states,
    // RAM wait state and enable prefetch cache, but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above.
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    /* use DBPRINTF */
    /* rt_hw_console_init(); */

    rt_hw_usart_init();
    rt_console_set_device("uart1");

    rt_hw_show_info();

    // enable multi-vector interrupts
    INTEnableSystemMultiVectoredInt();
    rt_hw_interrupt_disable();

//    // STEP 2. configure the core timer
//    OpenCoreTimer(CORE_TICK_RATE);
//
//    // set up the core timer interrupt with a prioirty of 2 and zero sub-priority
//    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));

    // STEP 2. configure Timer 1 using internal clock, 1:256 prescale
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, T1_TICK);
    // set up the timer interrupt with a priority of 2
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2);

    /* Setup the software interrupt. */
    mConfigIntCoreSW0( CSW_INT_ON | CSW_INT_PRIOR_1 | CSW_INT_SUB_PRIOR_0 );
}

void __ISR(_TIMER_1_VECTOR, ipl2) Timer1Handler(void)
{
    // clear the interrupt flag
    mT1ClearIntFlag();

    // .. things to do
    rt_hw_timer_handler();
}

//void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void)
//{
//    // clear the interrupt flag
//    mCTClearIntFlag();
//
//    // .. things to do
//    rt_hw_timer_handler();
//
//    // update the period
//    UpdateCoreTimer(CORE_TICK_RATE);
//}


void __ISR(_CORE_SOFTWARE_0_VECTOR, ipl1) CoreSW0Handler(void);

