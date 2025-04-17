/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-18     Bernard      The first version for LPC40xx
 * 2019-05-05     jg1uaa       port to LPC1114
 */
#include <stddef.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "board.h"      // CPU_CLOCK
#include "drv_uart.h"

#ifdef BSP_USING_SERIAL

#define UART_BASE       0x40008000              // UART (only one)
#define UART_IRQ        21
#define UART_CLOCK      (CPU_CLOCK / 1)         // Hz

#define URBR            HWREG32(UART_BASE + 0x00)       // R-
#define UTHR            HWREG32(UART_BASE + 0x00)       // -W
#define UIER            HWREG32(UART_BASE + 0x04)       // RW
#define UIIR            HWREG32(UART_BASE + 0x08)       // R-
#define UFCR            HWREG32(UART_BASE + 0x08)       // -W
#define ULCR            HWREG32(UART_BASE + 0x0c)       // RW
#define UMCR            HWREG32(UART_BASE + 0x10)       // RW
#define ULSR            HWREG32(UART_BASE + 0x14)       // R-
#define UMSR            HWREG32(UART_BASE + 0x18)       // R-

#define UDLL            HWREG32(UART_BASE + 0x00)       // RW
#define UDLM            HWREG32(UART_BASE + 0x04)       // RW

#define IOCONFIG_BASE   0x40044000
#define IOCON_PIO1_6    HWREG32(IOCONFIG_BASE + 0xa4)
#define IOCON_PIO1_7    HWREG32(IOCONFIG_BASE + 0xa8)

#define SYSCON_BASE     0x40048000
#define AHBCLKCTRL      HWREG32(SYSCON_BASE + 0x80)
#define UARTCLKDIV      HWREG32(SYSCON_BASE + 0x98)

static rt_err_t lpc_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_uint32_t Fdiv = 0;

    RT_ASSERT(serial != RT_NULL);

    /* Initialize UART Configuration parameter structure to default state:
     * Baudrate = 115200 bps
     * 8 data bit
     * 1 Stop bit
     * None parity
     */
    /* set DLAB=1 */
    ULCR |= 0x80;
    /* config uart baudrate */
    Fdiv = UART_CLOCK / (cfg->baud_rate * 16);
    UDLM = Fdiv / 256;
    UDLL = Fdiv % 256;
    /* set DLAB=0 */
    ULCR &= ~0x80;
    /* config to 8 data bit,1 Stop bit,None parity */
    ULCR |= 0x03;

    /*enable and reset FIFO*/
    UFCR = 0x07;

    return RT_EOK;
}

static rt_err_t lpc_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    RT_ASSERT(serial != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UIER &= ~0x01;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UIER |= 0x01;
        break;
    }

    return RT_EOK;
}

static int lpc_putc(struct rt_serial_device *serial, char c)
{
    while (!(ULSR & 0x20));
    UTHR = c;

    return 1;
}

static int lpc_getc(struct rt_serial_device *serial)
{
    if (ULSR & 0x01)
        return URBR;
    else
        return -1;
}

static const struct rt_uart_ops lpc_uart_ops =
{
    lpc_configure,
    lpc_control,
    lpc_putc,
    lpc_getc,
};

struct rt_serial_device serial;

void UART_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    switch (UIIR & 0x0e)
    {
    case 0x04:
    case 0x0C:
        rt_hw_serial_isr(&serial, RT_SERIAL_EVENT_RX_IND);
        break;
    case 0x06:
        (void)ULSR;
        break;
    default:
        (void)ULSR;
        break;
    }
    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_uart_init(void)
{
    rt_err_t ret = RT_EOK;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    serial.ops    = &lpc_uart_ops;
    serial.config = config;
    serial.parent.user_data = NULL;

    /*
     * Initialize UART pin connect
     * P1.6: U0_RXD
     * P1.7: U0_TXD
     */
    IOCON_PIO1_6 = 0xc1;
    IOCON_PIO1_7 = 0xc1;

    /* setup the uart power and clock */
    UARTCLKDIV = 0x01;          // UART PCLK = system clock / 1
    AHBCLKCTRL |= (1 << 12);    // UART power-up

    /* priority = 1 */
    NVIC_SetPriority(UART_IRQ, 0x01 << 6);

    /* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(UART_IRQ);

    /* register UART device */
    ret = rt_hw_serial_register(&serial, "uart",
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                                NULL);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* BSP_USING_SERIAL */
