/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    first version
 */

#include <rtthread.h>
#include <rthw.h>

#include <LPC24xx.h>
#include "board.h"

/* #define BOARD_DEBUG */

#define DATA_COUNT 14400000/RT_TICK_PER_SECOND	/* T0MR0 = delayInMs * (Fpclk / 1000); */

/**
 * @addtogroup LPC2478
 */
/*@{*/

void rt_timer_handler(int vector)
{
#ifdef BOARD_DEBUG
	rt_kprintf("timer handler, increase a tick\n");
#endif

	T0IR |= 0x01;			/* clear interrupt flag */
	rt_tick_increase();
	VICVectAddr = 0;		/* Acknowledge Interrupt */
}

/**
 * This function will init LPC2478 board
 */
void rt_hw_board_init()
{
	extern void rt_serial_init(void);
	/* init hardware serial */
	rt_serial_init();

	T0IR 	= 0xff; 
	T0TC 	= 0;
	T0MCR 	= 0x03; 
	T0MR0 	= (DATA_COUNT);

	rt_hw_interrupt_install(TIMER0_INT, rt_timer_handler, RT_NULL);	
	rt_hw_interrupt_umask(TIMER0_INT);

	T0TCR = 0x01; //enable timer0 counter
}

/******************************************************************************
** Function name:		TargetInit
**
** Descriptions:		Initialize the target board; it is called in a necessary 
**						place, change it as needed
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetInit(void)
{
	/* Add your codes here */
	return;
}

/******************************************************************************
** Function name:		GPIOResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**				function; User may change it as needed, but may not 
**				deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void GPIOResetInit( void )
{
	return;        
}

/******************************************************************************
** Function name:		ConfigurePLL
**
** Descriptions:		Configure PLL switching to main OSC instead of IRC
**						at power up and wake up from power down. 
**						This routine is used in TargetResetInit() and those
**						examples using power down and wake up such as
**						USB suspend to resume, ethernet WOL, and power management
**						example
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ConfigurePLL ( void )
{
  unsigned long MValue, NValue;

  if ( PLLSTAT & (1 << 25) )
  {
	PLLCON = 1;			/* Enable PLL, disconnected */
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
  }

  PLLCON = 0;				/* Disable PLL, disconnected */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;

  SCS |= 0x20;			/* Enable main OSC */
  while( !(SCS & 0x40) );	/* Wait until main OSC is usable */

  CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

  PLLCFG = PLL_MValue | (PLL_NValue << 16);
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
      
  PLLCON = 1;				/* Enable PLL, disconnected */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;

  CCLKCFG = CCLKDivValue;	/* Set clock divider */
#if USE_USB
  USBCLKCFG = USBCLKDivValue;		/* usbclk = 288 MHz/6 = 48 MHz */
#endif

  while ( ((PLLSTAT & (1 << 26)) == 0) );	/* Check lock bit status */
    
  MValue = PLLSTAT & 0x00007FFF;
  NValue = (PLLSTAT & 0x00FF0000) >> 16;
  while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );

  PLLCON = 3;				/* enable and connect */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
  while ( ((PLLSTAT & (1 << 25)) == 0) );	/* Check connect bit status */
  return;
}

/******************************************************************************
** Function name:		TargetResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**						function; User may change it as needed, but may not 
**						deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetResetInit(void)
{
	MEMMAP = 0x1;			/* remap to internal flash */

#if USE_USB
	PCONP |= 0x80000000;		/* Turn On USB PCLK */
#endif
	/* Configure PLL, switch from IRC to Main OSC */
	ConfigurePLL();

	/* Set system timers for each component */
#if (Fpclk / (Fcclk / 4)) == 1
	PCLKSEL0 = 0x00000000;	/* PCLK is 1/4 CCLK */
	PCLKSEL1 = 0x00000000;
#endif
#if (Fpclk / (Fcclk / 4)) == 2
	PCLKSEL0 = 0xAAAAAAAA;	/* PCLK is 1/2 CCLK */
	PCLKSEL1 = 0xAAAAAAAA;	 
#endif
#if (Fpclk / (Fcclk / 4)) == 4
	PCLKSEL0 = 0x55555555;	/* PCLK is the same as CCLK */
	PCLKSEL1 = 0x55555555;	
#endif

	/* Set memory accelerater module*/
	MAMCR = 0;
#if Fcclk < 20000000
	MAMTIM = 1;
#else
#if Fcclk < 40000000
	MAMTIM = 2;
#else
	MAMTIM = 3;
#endif
#endif
	MAMCR = 2;

	GPIOResetInit();

	return;
}

/*@}*/
