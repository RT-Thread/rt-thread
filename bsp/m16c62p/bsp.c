/*
 * File      : bsp.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-09     fify      the first version
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
*/

#include "iom16c62p.h"
#include "bsp.h"
#include "rtconfig.h"

void led_init(void)
{
    pu37 = 1;
    pd11_0 = 1;

    led_off();
}

void led_on(void)
{
    p11_0 = 1;
}

void led_off(void)
{
    p11_0 = 0;
}

static void mcu_init(void)
{
	volatile  rt_uint32_t  count;
	                                                            /* Configure clock for divide by 1 mode                     */
	prcr           |= 0x01;                                     /* Enable access to clock registers           PRCR.PRC0 = 1 */
	cm1             = 0x20;                                     /* Set CM16, CM17 divide ratio to 1:                        */
									                            /*  ... main clock on in high drive no PLL                  */
	cm0            &= ~0x40;                                    /* Set divide ratio to 1                      CM0.CM06  = 0 */			

                                                                /* Configure main PLL                                       */
	prcr           |= 0x02;                                     /* Allow writing to processor mode register   PRCR.PRC0 = 1 */
	pm2            |= 0x01;                                     /* Set SFR access to 2 wait, which is required for          */
   									                            /*  ... operation greater than 16 MHz         PM2.PM20  = 1 */
	prcr           &= ~0x02;                                    /* Protect processor mode register            PRCR.PRC0 = 0 */
	plc0            = 0x91;                                     /* Enable and turn on PLL                                   */

    count           = 20000;                                    /* Delay while PLL stabilizes                               */
	while (count > 0) {
        count--;
    }

    cm1            |= 0x02;                                     /* Switch to PLL                              CM1.CM11  = 1 */
    prcr           &= ~0x01;                                    /* Protect clock control register             PRCR.PRC0 = 0 */
	
	prcr           |= 0x02;                                     /* Allow writing to processor mode register   PRCR.PRC0 = 1 */
	pm1            |= 0x01;                                     /* Enable data flash area                     PM1.PM10  = 1 */
	prcr           &= ~0x02;                                    /* Protect processor mode register            PRCR.PRC0 = 0 */
}

/*
*********************************************************************************************************
*                                         TICKER INITIALIZATION
*
* Description : This function is called to initialize rt-thread's tick source (typically a timer generating
*               interrupts every 1 to 100 mS).
*
*               We decided to use Timer #B0 as the tick interrupt source.
*
* Arguments   : none
*
* Returns     :
*
* Notes       : (1) Timer B channel 0 is setup as a periodic timer, generating an interrupt
*                   OS_TICKS_PER_SEC times per second.  The timer counts down and generates an interrupt
*                   when it underflows.
*
*               (2) The timer ISR handler, rt_hw_timer_handler(), is placed into the vector table in vectors.s34.
*********************************************************************************************************
*/

static void timer_tick_init(void)
{
	                                                            /* Set timer to timer mode                                  */
                                                                /* Set count source as PLL clock / 8 (f8)                   */
	tb0mr                   = 0x40;
                                                                /* Assign timer value and reload value                      */
	tb0                     = (CPU_CLK_FREQ / 8) / RT_TICK_PER_SECOND;
	                                                            /* Set timer B channel 0 interrupt level = 7                */
	                                                            /* Clear interrupt request                                  */
    tb0ic                   = 0x07;
	tabsr                  |= 0x20;                             /* Start timer                                              */
}

void system_init(void)
{
    mcu_init();
    led_init();                                                 /* Initialize the I/Os for the LED controls                 */
    timer_tick_init();                                          /* Initialize the rt-thread tick interrupt                   */
}
