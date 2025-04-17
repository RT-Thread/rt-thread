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
 * 2006-08-23     Bernard      first implementation
 *
 * 2011-12-17     nl1031       for MacroBlaze
 *
 */

#include <rtthread.h>
#include <rthw.h>

#include "xbasic_types.h"
#include "board.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xuartlite.h"
#include "xtmrctr.h"
#include "xintc.h"
#include "xstatus.h"
#include "xuartlite_l.h"
#include "xintc_l.h"

#ifdef RT_USING_UART1
#include "drivers/dev_serial.h"
#endif

#define  TIMER_CNTR_0		0
#define  PIV  				(XPAR_PROC_BUS_0_FREQ_HZ / RT_TICK_PER_SECOND)
#define  LEDS_DEVICE_ID    	XPAR_LEDS_4BITS_DEVICE_ID
#define  RS232_DEVICE_ID   	XPAR_USB_UART_DEVICE_ID

#ifdef   RT_USING_UART1
#define  USB_UART_BASE		((struct uartport *)XPAR_USB_UART_BASEADDR)
#endif

/* Global Variables: */
XTmrCtr 	timer; 			/* The instance of the timer */
XGpio 		gpio_output; 	/* The driver instance for GPIO Device configured as O/P */
XUartLite 	uart_lite; 		/* Instance of the UartLite device */
XIntc 		int_ctl; 		/* The instance of the Interrupt Controller */
static		rt_uint32_t led_data;
static int cnt;



static void rt_hw_board_led_init(void);

/** 
 * This function will init led on the board
 */
static void rt_hw_board_led_init()
{
	rt_uint32_t status;
	led_data = 0;
	cnt = 0;
	status = XGpio_Initialize(&gpio_output, LEDS_DEVICE_ID);
	if (status != XST_SUCCESS)
	{
		return;
	}

	/*
	 * Set the direction for all signals to be outputs
	 */
	XGpio_SetDataDirection(&gpio_output, 1, 0x0);
	/*
	 * Set the GPIO outputs to high
	 */
	XGpio_DiscreteWrite(&gpio_output, 1, 3);
}

/** 
 * This function will take the led on board on.
 *
 * @param n the number nth led
 */
void rt_hw_board_led_on(rt_uint32_t led)
{
	led_data |= led;
	XGpio_DiscreteWrite(&gpio_output, 1, led_data);
}

/** 
 * This function will take the led on board off.
 *
 * @param n the number nth led
 */
void rt_hw_board_led_off(rt_uint32_t led)
{
	led_data &= ~led;
	XGpio_DiscreteWrite(&gpio_output, 1, led_data);
}


void rt_hw_led_flash(void)
{
	volatile rt_uint32_t i;

	rt_hw_board_led_off(1);
	for (i = 0; i < 20000; i ++);

	rt_hw_board_led_on(1);
	for (i = 0; i < 20000; i ++);
}


#ifdef RT_USING_CONSOLE

/*
 * RT-Thread Console Interface, used by rt_kprintf
 */
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

		/* Transmit Character */

		XUartLite_SendByte(STDOUT_BASEADDRESS, *str);
		if (*str == '\n')
			XUartLite_SendByte(STDOUT_BASEADDRESS, '\r');
		str++;
	}
}

static void rt_hw_console_init()
{
	rt_uint32_t status;

	/*
	* Initialize the UartLite driver so that it is ready to use.
	*/
	status = XUartLite_Initialize(&uart_lite, RS232_DEVICE_ID);
	if (status != XST_SUCCESS)
	{
		return;
	}

}
#endif


void rt_hw_timer_handler(void)
{
	rt_uint32_t csr;
	csr = XTmrCtr_ReadReg(timer.BaseAddress, TIMER_CNTR_0, XTC_TCSR_OFFSET);
	/*
	 * Check if timer expired and interrupt occured
	 */
	if (csr & XTC_CSR_INT_OCCURED_MASK)
	{
		rt_tick_increase();
		XTmrCtr_WriteReg(timer.BaseAddress, TIMER_CNTR_0, XTC_TCSR_OFFSET, csr | XTC_CSR_INT_OCCURED_MASK);
	}

}


/*
*********************************************************************************************************
*                                           rt_intc_init()
*
* Description: This function intializes the interrupt controller by registering the appropriate handler
*              functions and enabling interrupts.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  rt_intc_init (void)
{
    XStatus  status;

    XIntc_MasterDisable(XPAR_INTC_0_BASEADDR);

    status = XIntc_Initialize(&int_ctl, XPAR_INTC_0_DEVICE_ID);

	/* install interrupt handler */
    rt_hw_interrupt_install(XPAR_INTC_0_TMRCTR_0_VEC_ID, (rt_isr_handler_t)rt_hw_timer_handler, RT_NULL);
	rt_hw_interrupt_umask(XPAR_INTC_0_TMRCTR_0_VEC_ID);

	XIntc_Start(&int_ctl, XIN_REAL_MODE);

}


void  rt_tmr_init (void)
{
	rt_uint32_t ctl;
    XStatus  	status;

    status = XTmrCtr_Initialize(&timer,XPAR_AXI_TIMER_0_DEVICE_ID);
	XTmrCtr_WriteReg(timer.BaseAddress, TIMER_CNTR_0, XTC_TLR_OFFSET, PIV);
    ctl = XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_ENABLE_INT_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_DOWN_COUNT_MASK;
	XTmrCtr_WriteReg(timer.BaseAddress, TIMER_CNTR_0, XTC_TCSR_OFFSET, ctl);
}



/**
 * This function will initial SPARTAN 6 LX9 board.
 */
void rt_hw_board_init()
{
	microblaze_disable_icache();
	microblaze_disable_dcache();
	/* init hardware console */
	rt_hw_console_init();

	/* init led */
	rt_hw_board_led_init();

	/* init intc */
    rt_intc_init();

    /* timer init */
    rt_tmr_init();


}
