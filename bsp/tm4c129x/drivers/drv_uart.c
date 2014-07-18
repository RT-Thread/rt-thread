/*
 * File      : drv_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009-2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-18     Bernard      The first version for LPC40xx
 * 2014-07-18     ArdaFu       Port to TM4C129X
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
//#include <components.h>

#include "sysctl.h"
#include "gpio.h"
#include "uart.h"
#include "hw_memmap.h"
#include "pin_map.h"
#include "interrupt.h"
#include "rom.h"
#include "rom_map.h"
typedef struct hw_uart_device
{
    uint32_t hw_base; // base address
}hw_uart_t;

#define GetHwUartPtr(serial) ((hw_uart_t*)(serial->parent.user_data))

static rt_err_t hw_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{	
	hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = GetHwUartPtr(serial);
	MAP_UARTDisable(uart->hw_base);
    /* Initialize UART Configuration parameter structure to default state:
     * Baudrate = 115200 bps
     * 8 data bit
     * 1 Stop bit
     * None parity
     */
    // Initialize UART0 peripheral with given to corresponding parameter
    MAP_UARTConfigSetExpClk(uart->hw_base, SysClock, cfg->baud_rate,
													(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
		MAP_UARTFIFOEnable(uart->hw_base);

  //
	// Enable the UART.
	//
	MAP_UARTEnable(uart->hw_base);
    return RT_EOK;
}

static rt_err_t hw_control(struct rt_serial_device *serial, int cmd, void *arg)
{
	hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = GetHwUartPtr(serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        MAP_UARTIntDisable(uart->hw_base, UART_INT_RX | UART_INT_RT);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        MAP_UARTIntEnable(uart->hw_base, UART_INT_RX | UART_INT_RT);
        break;
    }

    return RT_EOK;
}

static int hw_putc(struct rt_serial_device *serial, char c)
{
	hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = GetHwUartPtr(serial);
	
    MAP_UARTCharPut(uart->hw_base, *((uint8_t *)&c));
    return 1;
}

static int hw_getc(struct rt_serial_device *serial)
{
	hw_uart_t* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = GetHwUartPtr(serial);
	
	return MAP_UARTCharGetNonBlocking(uart->hw_base);
}

static const struct rt_uart_ops hw_uart_ops =
{
    hw_configure,
    hw_control,
    hw_putc,
    hw_getc,
};

#if defined(RT_USING_UART0)
/* UART0 device driver structure */
struct rt_serial_device serial0;
struct serial_ringbuffer uart0_int_rx_buf;
hw_uart_t uart0 =
{
    UART0_BASE,
};

void UART0_IRQHandler(void)
{
	  uint32_t intsrc;
    hw_uart_t *uart = &uart0;

    /* enter interrupt */
    rt_interrupt_enter();

    /* Determine the interrupt source */
    intsrc = UARTIntStatus(uart->hw_base, true);

    // Receive Data Available or Character time-out
    if (intsrc & (UART_INT_RX | UART_INT_RT))
    {
						UARTIntClear(UART0_BASE, intsrc);
        rt_hw_serial_isr(&serial0);

    }
		
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

int rt_hw_uart_init(void)
{
    hw_uart_t* uart;
    struct serial_configure config;
	
#ifdef RT_USING_UART0
    uart = &uart0;
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;

    serial0.ops    = &hw_uart_ops;
    serial0.int_rx = &uart0_int_rx_buf;
    serial0.config = config;

    //
    // Enable the peripherals used by this example.
    // The UART itself needs to be enabled, as well as the GPIO port
    // containing the pins that will be used.
    //

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the GPIO pin muxing for the UART function.
    // This is only necessary if your part supports GPIO pin function muxing.
    // Study the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using
    //
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Since GPIO A0 and A1 are used for the UART function, they must be
    // configured for use as a peripheral function (instead of GPIO).
    // TODO: change this to match the port/pin you are using
    //
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* preemption = 1, sub-priority = 1 */
    //IntPrioritySet(INT_UART0, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for UART channel */
	UARTIntRegister(uart->hw_base, UART0_IRQHandler);
	MAP_IntEnable(INT_UART0);
	MAP_UARTEnable(uart->hw_base);

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);
#endif
	return 0;
}
//INIT_BOARD_EXPORT(rt_hw_uart_init);
