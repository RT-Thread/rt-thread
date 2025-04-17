/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2012-02-13   mojingxian  first version
 */

#include "board.h"
#include "rtconfig.h"
#include "rtdef.h"
#include "rthw.h"
#include "drivers/dev_serial.h"

#include <signal.h>
#include <sys/platform.h>
#include <ccblkfn.h>
#include <sysreg.h>
#include <string.h>
#include <sys\exception.h>
#include <stdio.h>

#define IVG_CLR(index)     (index > 0 ? ((0xFFFFFFF0 << (index * 0x04)) | \
                           (0xFFFFFFF0 >> ((0x08 - index) * 0x04))):0xFFFFFFF0)
#define IVG_SET(index,ivg) ((((ivg) - 0x07) & 0x0F) << (index * 0x04))

#define UART0   ((struct uartport *)pUART_THR)
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
    UART0,
    &uart0_int_rx,
    RT_NULL
};
struct rt_device uart0_device;

/**
 * This function is to set the EBIU(EXTERNAL BUS INTERFACE UNIT).
 */
static void rt_hw_ebiu_init(void)
{
    *pEBIU_AMBCTL0  = 0xffc2ffc2;

    *pEBIU_AMBCTL1  = 0xffc2ffc3;

    *pEBIU_AMGCTL   = 0x010f;
}

/**
 * This is the timer interrupt service routine.
 */
EX_INTERRUPT_HANDLER(rt_hw_timer_handler)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function is called to initialize system tick source (typically a
 * timer generating interrupts every 1 to 100 mS).
 * We decided to use Core Timer as the tick interrupt source.
 */
void rt_hw_core_timer_init(void)
{
    *pTCNTL   = 1;     // Turn on timer, TMPWR
    *pTSCALE  = 0x00;
    *pTCOUNT  = CCLKSPEED / RT_TICK_PER_SECOND;
    *pTPERIOD = CCLKSPEED / RT_TICK_PER_SECOND;
    register_handler(ik_timer,rt_hw_timer_handler);
    *pTCNTL    = 0x07; // Start Timer and set Auto-reload
}

void rt_hw_interrupt_init(void)
{
    extern rt_uint32_t rt_interrupt_from_thread;
    extern rt_uint32_t rt_interrupt_to_thread;
    extern rt_uint32_t rt_thread_switch_interrupt_flag;
    extern rt_uint8_t  rt_interrupt_nest;
    extern void interrupt_thread_switch(void);

    register_handler(ik_ivg14,interrupt_thread_switch); //context_vdsp.S

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;
}

static void rt_hw_pll_init(void)
{
    unsigned long imask;

    sysreg_write(reg_SYSCFG, 0x32);

    *pSIC_IWR = 0x01;

    *pPLL_CTL = SET_MSEL(SPEED_MULTIPLE);

    // PLL Re-programming Sequence.
    // Core is idle'ed to allow the PPL to re-lock.
    imask = cli();
    idle();
    sti(imask);
    *pVR_CTL = 0x00FB;

    // PLL Re-programming Sequence.
    // Core is idle'ed to allow the PPL to re-lock.
    imask = cli();
    idle();
    sti(imask);

    *pPLL_DIV = BUS_DIVISOR;
}

/**
 * This function is called to initialize external sdram.
 */
static void rt_hw_exdram_init(void)
{
    // Initalize EBIU control registers to enable all banks
    *pEBIU_AMBCTL1 = 0xFFFFFF02;
    ssync();

    *pEBIU_AMGCTL = 0x00FF;
    ssync();

    // Check if already enabled
    if (SDRS != ((*pEBIU_SDSTAT) & SDRS))
    {
        return;
    }

    //SDRAM Refresh Rate Control Register
    *pEBIU_SDRRC = 0x01A0;

    //SDRAM Memory Bank Control Register
    *pEBIU_SDBCTL = 0x0025; //1.7   64 MB

    //SDRAM Memory Global Control Register
    *pEBIU_SDGCTL = 0x0091998D;//0x998D0491

    ssync();
}

short uart_set_bitrate(unsigned long bit_rate)
{
    unsigned short int divisor;

    switch (bit_rate)
    {
        case 1200:
        case 2400:
        case 4800:
        case 9600:
        case 19200:
        case 28800:
        case 38400:
        case 57600:
        case 115200:
        case 125000:
            divisor = (unsigned short int) ((float) SCLKSPEED / ((float) bit_rate * 16.0f) + 0.5f);

            *(pUART_LCR) |= DLAB;            // Enable access to DLL and DLH registers
            *(pUART_DLL) = divisor & 0xFF;
            *(pUART_DLH) = divisor >> 8;
            *(pUART_LCR) &= ~DLAB;           // clear DLAB bit

            break;

        default: // baud rate not supported
            break;
    }

    return 0;
}

void rt_hw_uart_init(void)
{
    // Apply UART configuration 8 bit data, No parity, 1 stop bit
    *pUART_LCR = 0x0000; // Reset value
    *pUART_LCR = WLS(8);

     // Ensure that Loopback mode is disabled by clearing LOOP_ENA bit
    *pUART_MCR = 0x0000; //Reset value

    uart_set_bitrate(19200);// Set communication baudrate 115200

    *pUART_IER = ERBFI;

    // Enable UART clock
    *pUART_GCTL = UCEN;
}

int uart_put_char(const char c)
{
    while (!(*pUART_LSR & THRE))
    {
        /* wait */
    }

    *pUART_THR = c;

    return c;
}

void rt_hw_console_output(const char *str)
{
    while (*str != '\0')
    {
        if (*str == '\n')
            uart_put_char('\r');
        uart_put_char(*str++);
    }
}

EX_INTERRUPT_HANDLER(uart_rx_isr)
{
    rt_interrupt_enter();

    rt_hw_serial_isr(&uart0_device);

    rt_interrupt_leave();
}

void rt_hw_isr_install(void)
{
    *pSIC_IWR   = 0xFFFFFFFF;
    *pSIC_IMASK = 0x00000000;

    *pSIC_IAR1 &= IVG_CLR(IAR1_DMA6_UARTRX_IVG);
    *pSIC_IAR1 |= IVG_SET(IAR1_DMA6_UARTRX_IVG,ik_ivg9);
    register_handler(ik_ivg9,uart_rx_isr);
    *pSIC_IMASK |= DMA6_UART_RX_INT_MASK;/*  开中断      */
}

void rt_hw_board_init(void)
{
    rt_hw_pll_init();

    rt_hw_ebiu_init();

    rt_hw_exdram_init();

    rt_hw_uart_init();
}
