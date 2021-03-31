/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "uart.h"
#include <stdint.h>
#include <stdbool.h>
#include "r_pdl_cgc.h"
/* General RPDL function definitions */
#include "r_pdl_definitions.h"
#include "intrinsics.h"
#include "iorx62n.h"



/**
 * This is the timer interrupt service routine.
 *
 */
#pragma vector = VECT_CMT0_CMI0
__interrupt
void SysTick_Handler(void)
{
   // __enable_interrupt();
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}


void  rt_hw_systick_init(void)
{
    /* Enable compare match timer 0. */
    MSTP( CMT0 ) = 0;

    /* Interrupt on compare match. */
    CMT0.CMCR.BIT.CMIE = 1;

    /* Set the compare match value. */
    CMT0.CMCOR = ( unsigned short ) (((XTAL_FREQUENCY * PCLK_MUL) / RT_TICK_PER_SECOND)/8 -1);

    /* Divide the PCLK by 128. */
    CMT0.CMCR.BIT.CKS = 0;

    /* Enable the interrupt... */
    _IEN( _CMT0_CMI0 ) = 1;

    /* ...and set its priority to the application defined kernel priority. */
    _IPR( _CMT0_CMI0 ) = 4;

    /* Start the timer. */
    CMT.CMSTR0.BIT.STR0 = 1;
}

void rt_hw_system_freq_init(void)
{
   /* Declare error flag */
  bool err = true;

  /* Modify the MCU clocks, all are based off Epson 12 MHz clock */
  err &=     R_CGC_Set
    (
    12E6,
    96E6,
    48E6,
    24E6,
    PDL_NO_DATA
    );
  /*
  Clock Description              Frequency
  ----------------------------------------
  Input Clock Frequency..............12MHz
  Internal Clock Frequency...........96MHz
  Peripheral Clock Frequency.........48MHz
  External Bus Clock Frequency.......24MHz */

  /* Halt in while loop when RPDL errors detected */
  while (!err);
}

/**
 * This function will initial rx62n board
 */
void rt_hw_board_init()
{

    rt_hw_system_freq_init();
    rt_hw_systick_init();
    rt_hw_uart_init();
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
