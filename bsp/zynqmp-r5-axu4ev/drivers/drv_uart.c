/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19     WangHuachen  the first version
 */

#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "gic.h"

#include "drv_uart.h"

#define IOU_SLCR_BASE_ADDR   XPAR_PSU_IOUSLCR_0_S_AXI_BASEADDR
#define ZynqMP_IOU_SLCR_MIO_PIN(x)     (IOU_SLCR_BASE_ADDR + 0x04 * x)

#define XUARTPS_MAX_RATE    921600U
#define XUARTPS_MIN_RATE    110U
#define XUARTPS_MAX_BAUD_ERROR_RATE     3U	/* max % error allowed */

#define ZynqMP_UART_INT_DISABLE(UART)       \
    (UART->IER &= ~(UART_IXR_RXOVR | UART_IXR_RXFULL))
#define ZynqMP_UART_INT_ENABLE(UART)        \
    (UART->IER |= (UART_IXR_RXOVR | UART_IXR_RXFULL))

#define ZynqMP_UART_SENDCHAR(UART, ch)          \
    do {                                     \
        while ((UART->SR) & UART_SR_TXFULL); \
        UART->FIFO = ch;                     \
    } while(0)

#define ZynqMP_UART_GETCHAR(UART, ch)                          \
    do {                                                    \
        if (UART->ISR & UART_IXR_RXOVR)                      \
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
    uart->CR |= (UART_CR_TXRST | UART_CR_RXRST);
    while (uart->CR & (UART_CR_TXRST | UART_CR_RXRST));
}

/*                     UART TxD/RxD |   L3 Mux   |   L2 Mux    |  L1 Mux  */
#define RX_MIO_PIN_MODE ((0x6 << 5) | (0x0 << 3) | (0x0 << 2) | (0x0 << 1))
#define TX_MIO_PIN_MODE ((0x6 << 5) | (0x0 << 3) | (0x0 << 2) | (0x0 << 1))

struct hw_uart_device
{
    UART_Registers * uart;
    rt_uint32_t irqno;
    rt_uint32_t inputClockHz;

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

static rt_err_t XUartPsSetBandRate(struct hw_uart_device *pdev, rt_uint32_t targetBandRate)
{
    rt_uint32_t IterBAUDDIV;	/* Iterator for available baud divisor values */
    rt_uint32_t BRGR_Value;		/* Calculated value for baud rate generator */
    rt_uint32_t CalcBaudRate;	/* Calculated baud rate */
    rt_uint32_t BaudError;		/* Diff between calculated and requested baud rate */
    rt_uint32_t Best_BRGR = 0U;	/* Best value for baud rate generator */
    rt_uint8_t Best_BAUDDIV = 0U;	/* Best value for baud divisor */
    rt_uint32_t Best_Error = 0xFFFFFFFFU;
    rt_uint32_t PercentError;
    rt_uint32_t ModeReg;
    rt_uint32_t InputClk;

    if ((targetBandRate > (rt_uint32_t)XUARTPS_MAX_RATE) ||
        (targetBandRate < (rt_uint32_t)XUARTPS_MIN_RATE))
        return -RT_EINVAL;
    /*
     * Make sure the baud rate is not impossilby large.
     * Fastest possible baud rate is Input Clock / 2.
     */
    if ((targetBandRate * 2) > pdev->inputClockHz)
        return -RT_EINVAL;

    /* Check whether the input clock is divided by 8 */
    ModeReg = pdev->uart->MR;
    InputClk = pdev->inputClockHz;
    if(ModeReg & UART_MR_CLKSEL)
        InputClk = pdev->inputClockHz / 8;

    /*
     * Determine the Baud divider. It can be 4to 254.
     * Loop through all possible combinations
     */
    for (IterBAUDDIV = 4; IterBAUDDIV < 255; IterBAUDDIV++)
    {
        /* Calculate the value for BRGR register */
        BRGR_Value = InputClk / (targetBandRate * (IterBAUDDIV + 1));

        /* Calculate the baud rate from the BRGR value */
        CalcBaudRate = InputClk / (BRGR_Value * (IterBAUDDIV + 1));

        /* Avoid unsigned integer underflow */
        if (targetBandRate > CalcBaudRate)
            BaudError = targetBandRate - CalcBaudRate;
        else
            BaudError = CalcBaudRate - targetBandRate;

        /* Find the calculated baud rate closest to requested baud rate. */
        if (Best_Error > BaudError)
        {
            Best_BRGR = BRGR_Value;
            Best_BAUDDIV = IterBAUDDIV;
            Best_Error = BaudError;
        }
    }

    /* Make sure the best error is not too large. */
    PercentError = (Best_Error * 100) / targetBandRate;
    if (XUARTPS_MAX_BAUD_ERROR_RATE < PercentError)
        return -RT_ERROR;

    pdev->uart->BAUDGEN = Best_BRGR;
    pdev->uart->BAUDDIV = Best_BAUDDIV;
    return RT_EOK;
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    uint32_t mr;
    struct hw_uart_device *pdev = serial->parent.user_data;
    UART_Registers *uart = pdev->uart;

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
        return -RT_EINVAL;

    if (cfg->parity == PARITY_EVEN)
        mr |= UART_MR_PARITY_EVEN;
    else if (cfg->parity == PARITY_ODD)
        mr |= UART_MR_PARITY_ODD;
    else if (cfg->parity == PARITY_NONE)
        mr |= UART_MR_PARITY_NONE;
    else
        return -RT_EINVAL;

    if (cfg->data_bits == DATA_BITS_8)
        mr |= UART_MR_CHARLEN_8_BIT;
    else if (cfg->data_bits == DATA_BITS_7)
        mr |= UART_MR_CHARLEN_7_BIT;
    else if (cfg->data_bits == DATA_BITS_6)
        mr |= UART_MR_CHARLEN_6_BIT;
    else
        return -RT_EINVAL;

    uart->MR = mr;

    uart->TXWM = 8;
    uart->RXWM = 1;

    if (XUartPsSetBandRate(pdev, cfg->baud_rate) != RT_EOK)
    {
        rt_kprintf("baudrate %d not implemented yet\n", cfg->baud_rate);
        return -RT_EINVAL;
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
        ZynqMP_UART_INT_DISABLE(pdev->uart);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        ZynqMP_UART_INT_ENABLE(pdev->uart);
        rt_hw_interrupt_install(pdev->irqno, rt_hw_uart_isr, serial, serial->parent.parent.name);
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

    ZynqMP_UART_SENDCHAR(dev->uart, c);

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *dev;

    RT_ASSERT(serial != RT_NULL);
    dev = (struct hw_uart_device *)serial->parent.user_data;

    ch = -1;
    ZynqMP_UART_GETCHAR(dev->uart, ch);

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
#ifdef BSP_USING_UART0
static struct hw_uart_device _uart_device0 =
{
    .uart  = (UART_Registers*)XPAR_PSU_UART_0_BASEADDR,
    .irqno = XPAR_PSU_UART_0_INTR,
    .inputClockHz = XPAR_PSU_UART_0_UART_CLK_FREQ_HZ,

    .rxmio = (rt_uint32_t*)ZynqMP_IOU_SLCR_MIO_PIN(42), /* MIO42 */
    .txmio = (rt_uint32_t*)ZynqMP_IOU_SLCR_MIO_PIN(43), /* MIO43 */
};
static struct rt_serial_device _serial0;
#endif

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

    /* register uart device */
#ifdef BSP_USING_UART0
    _serial0.ops    = &_uart_ops;
    _serial0.config = config;
    rt_hw_serial_register(&_serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_uart_device0);
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);