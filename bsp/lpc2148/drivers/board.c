/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "lpc214x.h"
#include "board.h"

/**
 * @addtogroup LPC2148
 */
/*@{*/

/**
 * This is the timer interrupt service routine.
 * @param vector the irq number for timer
 */
void rt_hw_timer_handler(int vector, void *param)
{
    rt_tick_increase();

    /* clear interrupt flag */
    T0IR |= 0x01;

    /* acknowledge Interrupt */
    VICVectAddr = 0;
}

/**
 * This function is used to display a string on console, normally, it's
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
    while (*str)
    {
        if (*str=='\n')
        {
            while (!(U0LSR & 0x20));
            U0THR = '\r';
        }

        while (!(U0LSR & 0x20));
        U0THR = *str;

        str ++;
    }
}

#define BAUD_RATE   115200
#define U0PINS      0x05
void rt_hw_console_init()
{
    /* Enable RxD and TxD pins */
    PINSEL0 = U0PINS;

    /* 8 bits, no Parity, 1 Stop bit */
    U0LCR = 0x83;

    /* Setup Baudrate */
    U0DLL = (PCLK/16/BAUD_RATE) & 0xFF;
    U0DLM = ((PCLK/16/BAUD_RATE) >> 8) & 0xFF;

    /* DLAB = 0 */
    U0LCR = 0x03;
}

/**
 * This function will initial sam7x256 board.
 */
void rt_hw_board_init(void)
{
    /* console init */
    rt_hw_console_init();

    /* prescaler = 0*/
    T0PR = 0;
    T0PC = 0;

    /* reset and enable MR0 interrupt */
    T0MCR = 0x3;
    T0MR0 = PCLK / RT_TICK_PER_SECOND;

    /* enable timer 0 */
    T0TCR = 1;

    /* install timer handler */
    rt_hw_interrupt_install(TIMER0_INT, rt_hw_timer_handler, RT_NULL, "TIMER0");
    rt_hw_interrupt_umask(TIMER0_INT);
}

/*@}*/
