/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-15     flyingcys    1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "wm_io.h"
#include "wm_uart.h"
#include "wm_gpio_afsel.h"
#include "wm_type_def.h"
#include "wm_cpu.h"
#include "drv_uart.h"
#include "pin_map.h"

#define   WM600_UART0    (TLS_UART_REGS_T *) HR_UART0_BASE_ADDR
#define   WM600_UART1    (TLS_UART_REGS_T *) HR_UART1_BASE_ADDR
#define   WM600_UART2    (TLS_UART_REGS_T *) HR_UART2_BASE_ADDR

static void wm_uart_reg_init(TLS_UART_REGS_T *UARTx)
{
    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    if (UARTx == WM600_UART0)
    {
        /* disable auto flow control */
        tls_reg_write32(HR_UART0_FLOW_CTRL, 0);
        /* disable dma */
        tls_reg_write32(HR_UART0_DMA_CTRL, 0);
        /* one byte tx */
        tls_reg_write32(HR_UART0_FIFO_CTRL, 0);
        /* disable interrupt */
        tls_reg_write32(HR_UART0_INT_MASK, 0xFF);
        /* enable rx/timeout interrupt */
        tls_reg_write32(HR_UART0_INT_MASK, ~(3 << 2));
    }
    else if (UARTx == WM600_UART1)
    {
        /* 4 byte tx, 8 bytes rx */
        tls_reg_write32(HR_UART1_FIFO_CTRL, (0x01 << 2) | (0x02 << 4));
        /* enable rx timeout, disable rx dma, disable tx dma */
        tls_reg_write32(HR_UART1_DMA_CTRL, (8 << 3) | (1 << 2));
        /* enable rx/timeout interrupt */
        tls_reg_write32(HR_UART1_INT_MASK, ~(3 << 2));
    }
    else if (UARTx == WM600_UART2)
    {
        /* 4 byte tx, 8 bytes rx */
        tls_reg_write32(HR_UART2_FIFO_CTRL, (0x01 << 2) | (0x02 << 4));
        /* enable rx timeout, disable rx dma, disable tx dma */
        tls_reg_write32(HR_UART2_DMA_CTRL, (8 << 3) | (1 << 2));
        /* enable rx/timeout interrupt */
        tls_reg_write32(HR_UART2_INT_MASK, ~(3 << 2));
        UARTx->UR_LC &= ~(0x1000000);
    }
}

static void wm_uart_gpio_config(TLS_UART_REGS_T *UARTx)
{
#if defined(BSP_USING_UART1) || defined(BSP_USING_UART2)
    rt_int16_t gpio_pin;
#endif

    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    if (UARTx == WM600_UART0)
    {
        /* UART0_TX-PA04 UART0_RX-PA05 */
        wm_uart0_tx_config(WM_IO_PA_04);
        wm_uart0_rx_config(WM_IO_PA_05);
    }
#ifdef BSP_USING_UART1
    else if (UARTx == WM600_UART1)
    {

        gpio_pin = wm_get_pin(WM_UART1_RX_PIN);
        if (gpio_pin >= 0)
        {
            wm_uart1_rx_config((enum tls_io_name)gpio_pin);
        }
        gpio_pin = wm_get_pin(WM_UART1_TX_PIN);
        if (gpio_pin >= 0)
        {
            wm_uart1_tx_config((enum tls_io_name)gpio_pin);
        }
    }
#endif
#ifdef BSP_USING_UART2
    else if (UARTx == WM600_UART2)
    {
        gpio_pin = wm_get_pin(WM_UART2_RX_PIN);
        if (gpio_pin >= 0)
        {
            wm_uart2_rx_config((enum tls_io_name)gpio_pin);
        }
        gpio_pin = wm_get_pin(WM_UART2_TX_PIN);
        if (gpio_pin >= 0)
        {
            wm_uart2_tx_scio_config((enum tls_io_name)gpio_pin);
        }
    }
#endif
}

static void wm_uart_irq_config(TLS_UART_REGS_T *UARTx)
{
    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    /* config uart interrupt register */
    /* clear interrupt */
    UARTx->UR_INTS = 0xFFFFFFFF;
    /* enable interupt */
    UARTx->UR_INTM = 0x0;
    UARTx->UR_DMAC = (4UL << UDMA_RX_FIFO_TIMEOUT_SHIFT) | UDMA_RX_FIFO_TIMEOUT;

    /* config FIFO control */
    UARTx->UR_FIFOC = UFC_TX_FIFO_LVL_16_BYTE | UFC_RX_FIFO_LVL_16_BYTE | UFC_TX_FIFO_RESET | UFC_RX_FIFO_RESET;
    UARTx->UR_LC &= ~(ULCON_TX_EN | ULCON_RX_EN);
    UARTx->UR_LC |= ULCON_TX_EN | ULCON_RX_EN;
}

static int wm_uart_baudrate_set(TLS_UART_REGS_T *UARTx, u32 baudrate)
{
    u32 value;
    u32 apbclk;
    tls_sys_clk sysclk;

    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    tls_sys_clk_get(&sysclk);
    apbclk = sysclk.apbclk * 1000000;
    value = (apbclk / (16 * baudrate) - 1) |
            (((apbclk % (baudrate * 16)) * 16 / (baudrate * 16)) << 16);
    UARTx->UR_BD = value;

    return WM_SUCCESS;
}

static int wm_uart_parity_set(TLS_UART_REGS_T *UARTx, TLS_UART_PMODE_T paritytype)
{
    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    if (paritytype == TLS_UART_PMODE_DISABLED)
        UARTx->UR_LC &= ~ULCON_PMD_EN;
    else if (paritytype == TLS_UART_PMODE_EVEN)
    {
        UARTx->UR_LC &= ~ULCON_PMD_MASK;
        UARTx->UR_LC |= ULCON_PMD_EVEN;
    }
    else if (paritytype == TLS_UART_PMODE_ODD)
    {
        UARTx->UR_LC &= ~ULCON_PMD_MASK;
        UARTx->UR_LC |= ULCON_PMD_ODD;
    }
    else
        return WM_FAILED;

    return WM_SUCCESS;
}

static int wm_uart_stopbits_set(TLS_UART_REGS_T *UARTx, TLS_UART_STOPBITS_T stopbits)
{
    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    if (stopbits == TLS_UART_TWO_STOPBITS)
        UARTx->UR_LC |= ULCON_STOP_2;
    else
        UARTx->UR_LC &= ~ULCON_STOP_2;

    return WM_SUCCESS;
}

static int wm_uart_databits_set(TLS_UART_REGS_T *UARTx, TLS_UART_CHSIZE_T charlength)
{
    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    UARTx->UR_LC &= ~ULCON_WL_MASK;

    if (charlength == TLS_UART_CHSIZE_5BIT)
        UARTx->UR_LC |= ULCON_WL5;
    else if (charlength == TLS_UART_CHSIZE_6BIT)
        UARTx->UR_LC |= ULCON_WL6;
    else if (charlength == TLS_UART_CHSIZE_7BIT)
        UARTx->UR_LC |= ULCON_WL7;
    else if (charlength == TLS_UART_CHSIZE_8BIT)
        UARTx->UR_LC |= ULCON_WL8;
    else
        return WM_FAILED;

    return WM_SUCCESS;
}

static int wm_uart_flow_ctrl_set(TLS_UART_REGS_T *UARTx, TLS_UART_FLOW_CTRL_MODE_T flow_ctrl)
{
    RT_ASSERT(UARTx == WM600_UART0 || UARTx == WM600_UART1 || UARTx == WM600_UART2);

    switch (flow_ctrl)
    {
    case TLS_UART_FLOW_CTRL_NONE:
        UARTx->UR_FC = 0;
        break;

    case TLS_UART_FLOW_CTRL_HARDWARE:
        UARTx->UR_FC = (1UL << 0) | (6UL << 2);
        break;

    default:
        break;
    }

    return WM_SUCCESS;
}

struct device_uart
{
    TLS_UART_REGS_T volatile *uart_device;

    rt_uint32_t uart_irq_no;
};

static rt_err_t  drv_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  drv_uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       drv_uart_putc(struct rt_serial_device *serial, char c);
static int       drv_uart_getc(struct rt_serial_device *serial);
static rt_ssize_t drv_uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);

const struct rt_uart_ops _uart_ops =
{
    drv_uart_configure,
    drv_uart_control,
    drv_uart_putc,
    drv_uart_getc,
    drv_uart_dma_transmit
};

/*
 * UART interface
 */
static rt_err_t drv_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct device_uart *uart;
    u32 baud_rate;
    TLS_UART_PMODE_T parity;
    TLS_UART_STOPBITS_T stop_bits;
    TLS_UART_CHSIZE_T data_bits;

    RT_ASSERT(serial != RT_NULL && cfg != RT_NULL);
    serial->config = *cfg;

    uart = (struct device_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    switch (cfg->baud_rate)
    {
    case BAUD_RATE_2000000:
    case BAUD_RATE_921600:
    case BAUD_RATE_460800:
    case BAUD_RATE_230400:
    case BAUD_RATE_115200:
    case BAUD_RATE_57600:
    case BAUD_RATE_38400:
    case BAUD_RATE_19200:
    case BAUD_RATE_9600:
    case BAUD_RATE_4800:
    case BAUD_RATE_2400:
        baud_rate = cfg->baud_rate;
        break;

    default:
        rt_kprintf("baudrate set failed... default rate:115200\r\n");
        baud_rate = BAUD_RATE_115200;
        break;
    }
    wm_uart_baudrate_set((TLS_UART_REGS_T *)uart->uart_device, baud_rate);

    switch (cfg->parity)
    {
    case PARITY_ODD:
        parity = TLS_UART_PMODE_ODD;
        break;

    case PARITY_EVEN:
        parity = TLS_UART_PMODE_EVEN;
        break;

    case PARITY_NONE:
    default:
        parity = TLS_UART_PMODE_DISABLED;
        break;
    }
    wm_uart_parity_set((TLS_UART_REGS_T *)uart->uart_device, parity);

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        stop_bits = TLS_UART_TWO_STOPBITS;
        break;

    case STOP_BITS_1:
    default:
        stop_bits = TLS_UART_ONE_STOPBITS;
        break;
    }
    wm_uart_stopbits_set((TLS_UART_REGS_T *)uart->uart_device, stop_bits);

    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        data_bits = TLS_UART_CHSIZE_5BIT;
        break;

    case DATA_BITS_6:
        data_bits = TLS_UART_CHSIZE_6BIT;
        break;

    case DATA_BITS_7:
        data_bits = TLS_UART_CHSIZE_7BIT;
        break;

    case DATA_BITS_8:
    default:
        data_bits = TLS_UART_CHSIZE_8BIT;
        break;
    }
    wm_uart_databits_set((TLS_UART_REGS_T *)uart->uart_device, data_bits);
    wm_uart_flow_ctrl_set((TLS_UART_REGS_T *)uart->uart_device, TLS_UART_FLOW_CTRL_NONE);

    return (RT_EOK);
}

static rt_err_t drv_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct device_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        tls_irq_disable(uart->uart_irq_no);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* Enable the UART Interrupt */
        tls_irq_enable(uart->uart_irq_no);
        break;
    }

    return (RT_EOK);
}

static int drv_uart_putc(struct rt_serial_device *serial, char c)
{
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct device_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    while (uart->uart_device->UR_FIFOS & 0x3F); /* wait THR is empty */
    uart->uart_device->UR_TXW = (char)c;

    return (1);
}

static int drv_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct device_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    ch = -1;

    if (uart->uart_device->UR_FIFOS & UFS_RX_FIFO_CNT_MASK)
        ch = (int)uart->uart_device->UR_RXW;

    return ch;
}

static rt_ssize_t drv_uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return (0);
}

static void drv_uart_irq_handler(struct rt_serial_device *serial)
{
    u32 intr_src;
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct device_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* check interrupt status */
    intr_src = uart->uart_device->UR_INTS;
    uart->uart_device->UR_INTS = intr_src;

    if ((intr_src & UART_RX_INT_FLAG) && (0 == (uart->uart_device->UR_INTM & UIS_RX_FIFO)))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (intr_src & UART_TX_INT_FLAG)
    {

    }

    if (intr_src & UIS_CTS_CHNG)
    {

    }
}

#ifdef BSP_USING_UART0
static struct rt_serial_device  serial0;
static struct device_uart       uart0 =
{
    WM600_UART0,
    UART0_INT,
};

void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    drv_uart_irq_handler(&serial0);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART1
static struct rt_serial_device  serial1;
static struct device_uart       uart1 =
{
    WM600_UART1,
    UART1_INT,
};

void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    drv_uart_irq_handler(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();

}
#endif

#ifdef BSP_USING_UART2
static struct rt_serial_device  serial2;
static struct device_uart       uart2 =
{
    WM600_UART2,
    UART2_INT,
};

void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    drv_uart_irq_handler(&serial2);

    /* leave interrupt */
    rt_interrupt_leave();

}
#endif
/*
 * UART Initiation
 */
int wm_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    struct device_uart      *uart;

#ifdef BSP_USING_UART0
    {
        serial  = &serial0;
        uart    = &uart0;

        /* Init UART Hardware */
        wm_uart_gpio_config((TLS_UART_REGS_T *)uart->uart_device);
        wm_uart_reg_init((TLS_UART_REGS_T *)uart->uart_device);
        wm_uart_irq_config((TLS_UART_REGS_T *)uart->uart_device);

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        rt_hw_serial_register(serial,
                              "uart0",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    {
        serial  = &serial1;
        uart    = &uart1;

        /* Init UART Hardware */
        wm_uart_gpio_config((TLS_UART_REGS_T *)uart->uart_device);
        wm_uart_reg_init((TLS_UART_REGS_T *)uart->uart_device);
        wm_uart_irq_config((TLS_UART_REGS_T *)uart->uart_device);

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = WM_UART1_BAUDRATE;

        rt_hw_serial_register(serial,
                              "uart1",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif /* BSP_USING_UART1 */
#ifdef BSP_USING_UART2
    {
        serial  = &serial2;
        uart    = &uart2;

        /* Init UART Hardware */
        wm_uart_gpio_config((TLS_UART_REGS_T *)uart->uart_device);
        wm_uart_reg_init((TLS_UART_REGS_T *)uart->uart_device);
        wm_uart_irq_config((TLS_UART_REGS_T *)uart->uart_device);

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = WM_UART2_BAUDRATE;

        rt_hw_serial_register(serial,
                              "uart2",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif /* BSP_USING_UART2 */
    return 0;
}
INIT_BOARD_EXPORT(wm_hw_uart_init);
