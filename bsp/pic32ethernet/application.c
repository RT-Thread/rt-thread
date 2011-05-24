/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-23     aozima       first implementation for PIC32.
 */

// Adds support for PIC32 Peripheral library functions and macros
#include <plib.h>

static void delay(void)
{
    volatile unsigned long i;
    for(i=0;i<500000;i++);
}

int rt_application_init(void)
{
    PORTSetPinsDigitalOut(IOPORT_D, BIT_0);

   while(1)
   {
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       delay();
       PORTSetBits(IOPORT_D, BIT_0);
       delay();
       PORTClearBits(IOPORT_D, BIT_0);
   }

    return 0;
}
