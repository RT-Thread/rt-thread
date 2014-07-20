/*
 *  serial.c UART driver
 *
 * COPYRIGHT (C) 2013, Shanghai Real-Thread Technology Co., Ltd
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */

#include <rthw.h>
#include <rtdevice.h>

#include "board.h"

#include "gic.h"
#include "cp15.h"

#include "uart_hw.h"

#define Zynq7000_UART_INT_DISABLE(UART)       \
    (UART->IER &= ~(UART_IXR_RXOVR | UART_IXR_RXFULL))
#define Zynq7000_UART_INT_ENABLE(UART)        \
    (UART->IER |= (UART_IXR_RXOVR | UART_IXR_RXFULL))

#define Zynq7000_UART_SENDCHAR(UART, ch)          \
    do {                                     \
        while ((UART->SR) & UART_SR_TXFULL); \
        UART->FIFO = ch;                     \
    } while(0)

#define Zynq7000_UART_GETCHAR(UART, ch)                          \
    do {                                                    \
        if (UART->ISR & UART_SR_RXOVR)                      \
        {                                                   \
            ch = UART->FIFO & 0xff;                         \
            UART->ISR = (UART_IXR_RXOVR | UART_IXR_RXFULL); \
        }                                                   \
    } while(0)

static void UartEnable(UART_Registers* uart)
{
	uint32_t tmp = uart->CR;
	tmp &= ~UART_CR_EN_DIS_MASK;
	tmp |= (UART_CR_TX_EN | UART_CR_RX_EN);

	uart->CR = tmp;
}

static void UartDisable(UART_Registers* uart)
{
	uint32_t tmp = uart->CR;
	tmp &= ~UART_CR_EN_DIS_MASK;
	tmp |= (UART_CR_TX_DIS | UART_CR_RX_DIS);
	uart->CR = tmp;
}

static void UartResetTXRXLogic(UART_Registers* uart)
{
	uart->CR |= 0x03;
    while (uart->CR & 0x03)
        ;
}

/*                        PULLUP       | LVCMOS18     | Fast CMOS     | UART  */
#define RX_MIO_PIN_MODE ((0x1UL << 12) | (0x1UL << 9) | (0x01UL << 8) | (0x7UL << 5))
#define TX_MIO_PIN_MODE (                (0x1UL << 9) | (0x01UL << 8) | (0x7UL << 5))

struct hw_uart_device
{
    UART_Registers * uart;
    rt_uint32_t irqno;

    /* MIO pin mode address */
    rt_uint32_t *rxmio;
    rt_uint32_t *txmio;
};

/* RT-Thread UART interface */

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    uint32_t mr;
    struct hw_uart_device *pdev = serial->parent.user_data;
    UART_Registers *uart = pdev->uart;

    /* unlock SLCR */
    __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_UNLOCK) = 0xDF0D;

    /* no loopback */
    __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_MIO_LOOPBACK) &= ~(1 << 1);

    if (uart == (void*)Zynq7000_UART0_BASE)
    {
        /* enable the coresponding AMBA Peripheral Clock */
        __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_APER_CLK_CTRL) |= 1 << 20;
        /* enable uart clock. Divider 0x14 gives 50MHZ ref clock on IO PLL input. */
        __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_UART_CLK_CTRL) |= (0x14 << 8) | 0x01;
        /* deassert the AMBA clock and software reset */
        __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_UART_RST_CTRL) &= ~((0x01 << 2)|(0x01 << 0));
    }
    else if (uart == (void*)Zynq7000_UART1_BASE)
    {
        __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_APER_CLK_CTRL) |= 1 << 21;
        __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_UART_CLK_CTRL) |= (0x14 << 8) | 0x02;
        __REG32(Zynq7000_SLCR_BASE+Zynq7000_SLCR_UART_RST_CTRL) &= ~((0x01 << 3)|(0x01 << 1));
    }
    else
        return -RT_ERROR;

    UartDisable(uart);
    UartResetTXRXLogic(uart);
    UartEnable(uart);

    mr = uart->MR & ~(UART_MR_CHARLEN_MASK |
                      UART_MR_STOPMODE_MASK |
                      UART_MR_PARITY_MASK);

    if (cfg->stop_bits == STOP_BITS_2)
        mr |= UART_MR_STOPMODE_2_BIT;
    else if (cfg->stop_bits == STOP_BITS_1)
        mr |= UART_MR_STOPMODE_1_BIT;
    else
        return -RT_ERROR;

    if (cfg->parity == PARITY_EVEN)
        mr |= UART_MR_PARITY_EVEN;
    else if (cfg->parity == PARITY_ODD)
        mr |= UART_MR_PARITY_ODD;
    else if (cfg->parity == PARITY_NONE)
        mr |= UART_MR_PARITY_NONE;
    else
        return -1;

    if (cfg->data_bits == DATA_BITS_8)
        mr |= UART_MR_CHARLEN_8_BIT;
    else if (cfg->data_bits == DATA_BITS_7)
        mr |= UART_MR_CHARLEN_7_BIT;
    else if (cfg->data_bits == DATA_BITS_6)
        mr |= UART_MR_CHARLEN_6_BIT;
    else
        return -RT_ERROR;

	uart->MR = mr;

    uart->TXWM = 8;
    uart->RXWM = 1;

    if (cfg->baud_rate == BAUD_RATE_115200)
    {
        uart->BAUDGEN = UART_BAUDGEN_115200;
        uart->BAUDDIV = UART_BAUDDIV_115200;
    }
    else
    {
        rt_kprintf("baudrate %d not implemented yet\n", cfg->baud_rate);
    }

    /* disable all interrupts */
    uart->IDR = UART_IXR_MASK;

    /* configure the pin */
    *(pdev->txmio) = TX_MIO_PIN_MODE;
    *(pdev->rxmio) = RX_MIO_PIN_MODE;

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *pdev;

    RT_ASSERT(serial != RT_NULL);

    pdev = serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        Zynq7000_UART_INT_DISABLE(pdev->uart);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        Zynq7000_UART_INT_ENABLE(pdev->uart);
        rt_hw_interrupt_install(pdev->irqno, rt_hw_uart_isr, serial, "uart");
        /* set the interrupt to this cpu */
        arm_gic_set_cpu(0, pdev->irqno, 1 << rt_cpu_get_smp_id());
        rt_hw_interrupt_umask(pdev->irqno);
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *dev;

    RT_ASSERT(serial != RT_NULL);
    dev = (struct hw_uart_device *)serial->parent.user_data;

    Zynq7000_UART_SENDCHAR(dev->uart, c);

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *dev;

    RT_ASSERT(serial != RT_NULL);
    dev = (struct hw_uart_device *)serial->parent.user_data;

    ch = -1;
    Zynq7000_UART_GETCHAR(dev->uart, ch);

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

/* UART device driver structure */
static struct hw_uart_device _uart_device0 =
{
    .uart  = (UART_Registers*)Zynq7000_UART0_BASE,
    .irqno = IRQ_Zynq7000_UART0,
    .rxmio = (rt_uint32_t*)(Zynq7000_SLCR_BASE+0x0728), /* MIO10 */
    .txmio = (rt_uint32_t*)(Zynq7000_SLCR_BASE+0x072C), /* MIO11 */
};
static struct hw_uart_device _uart_device1 =
{
    .uart  = (UART_Registers*)Zynq7000_UART1_BASE,
    .irqno = IRQ_Zynq7000_UART1,
    .rxmio = (rt_uint32_t*)(Zynq7000_SLCR_BASE+0x07C4), /* MIO49 */
    .txmio = (rt_uint32_t*)(Zynq7000_SLCR_BASE+0x07C0), /* MIO48 */
};

static struct rt_serial_device _serial0;
static struct rt_serial_device _serial1;

int rt_hw_uart_init(void)
{
    struct serial_configure config;

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
	config.bufsz     = RT_SERIAL_RB_BUFSZ;

    _serial0.ops    = &_uart_ops;
    _serial0.config = config;

    _serial1.ops    = &_uart_ops;
    _serial1.config = config;

    /* register uart device */
    rt_hw_serial_register(&_serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_uart_device0);
    rt_hw_serial_register(&_serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_uart_device1);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

