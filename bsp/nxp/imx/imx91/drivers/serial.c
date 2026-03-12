/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 * 2025-09-15     Siwei Xu     Fix LPUART driver
 */

#include <rthw.h>
#include <rtdevice.h>
#include <ioremap.h>
#include <drivers/misc.h>

#include "serial.h"

#include "MIMX9131.h"
#include "fsl_clock.h"
#include "fsl_lpuart.h"

struct hw_uart_device
{
    struct rt_serial_device serial;  /* Select serial device */
    const char *device_name; /* serial device name */

    LPUART_Type *uart_ptr;
    rt_base_t uart_base;
    int instance;
    int irqn;

    clock_root_t clock_root; /* clock root */
    clock_root_mux_source_t clock_mux; /* clock mux */
    clock_ip_name_t clock_ip_name; /* clock control gate */
};

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
static struct hw_uart_device _uart1_device = {
    .device_name = "uart1",
    .uart_ptr = RT_NULL,
    .uart_base = LPUART1_BASE,
    .instance = 1,
    .irqn = LPUART1_IRQn,
    .clock_root = kCLOCK_Root_Lpuart1,
    .clock_mux = kCLOCK_LPUART1_ClockRoot_MuxOsc24M,
    .clock_ip_name = kCLOCK_Lpuart1,
};
#endif

static struct hw_uart_device *hw_uart_devices[] = {
#ifdef BSP_USING_UART1
    &_uart1_device,
#endif
};

static void rt_hw_uart_isr(int irqn, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hw_uart_device *uart = RT_NULL;
    static lpuart_config_t config;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    LPUART_GetDefaultConfig(&config);

    // baud rate
    config.baudRate_Bps = cfg->baud_rate;

    // data bits
    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        config.dataBitsCount = kLPUART_EightDataBits;
        break;
    case DATA_BITS_7:
#if defined(FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT) && FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT
        config.dataBitsCount = kLPUART_SevenDataBits;
        break;
#endif
    default:
        config.dataBitsCount = kLPUART_EightDataBits;
        break;
    }

    // parity bit
    switch (cfg->parity)
    {
    case PARITY_NONE:
        config.parityMode = kLPUART_ParityDisabled;
        break;
    case PARITY_ODD:
        config.parityMode = kLPUART_ParityOdd;
        break;
    case PARITY_EVEN:
        config.parityMode = kLPUART_ParityEven;
        break;
    default:
        config.parityMode = kLPUART_ParityDisabled;
        break;
    }

    // stop bits
#if defined(FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        config.stopBitCount = kLPUART_OneStopBit;
        break;
    case STOP_BITS_2:
        config.stopBitCount = kLPUART_TwoStopBit;
        break;
    default:
        config.stopBitCount = kLPUART_OneStopBit;
        break;
    }
#endif

    // LSB/MSB
    if (cfg->bit_order == BIT_ORDER_LSB)
    {
        config.isMsb = false;
    }
    else
    {
        config.isMsb = true;
    }

    // hardware flow control
#if defined(FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT) && FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT
    if (cfg->flowcontrol == RT_SERIAL_FLOWCONTROL_NONE)
    {
        // disable hardware flow control
        config.enableRxRTS = false;
        config.enableTxCTS = false;
    }
    else
    {
        // enable hardware flow control
        config.enableRxRTS = true;
        config.enableTxCTS = true;
    }
#endif

    // enable TX and RX
    config.enableTx = serial->parent.flag & RT_DEVICE_FLAG_WRONLY;
    config.enableRx = serial->parent.flag & RT_DEVICE_FLAG_RDONLY;

    // Set UART clock source and clock divider
    CLOCK_SetRootClockMux(uart->clock_root, uart->clock_mux);
    CLOCK_SetRootClockDiv(uart->clock_root, 1U);

    // Initialize the LPUART module with the configuration structure and clock source
    LPUART_Init(uart->uart_ptr, &config, CLOCK_GetIpFreq(uart->clock_root));

    // Install interrupt handler
    rt_hw_interrupt_install(uart->irqn, rt_hw_uart_isr, serial, "uart");
    rt_hw_interrupt_mask(uart->irqn);

    // Enable RX interrupt
    LPUART_EnableInterrupts(uart->uart_ptr, kLPUART_RxDataRegFullInterruptEnable);
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        rt_hw_interrupt_mask(uart->irqn);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        rt_hw_interrupt_umask(uart->irqn);
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    while (!(LPUART_GetStatusFlags(uart->uart_ptr) & kLPUART_TxDataRegEmptyFlag))
    {
        __NOP();
    }

    LPUART_WriteByte(uart->uart_ptr, c);

    return 1;
}

#ifdef BSP_USING_EARLY_CONSOLE
LPUART_Type *earlycon_base = RT_NULL;

void rt_hw_earlycon_set(void *base)
{
    earlycon_base = (LPUART_Type *)base;
}

void rt_hw_earlycon_ioremap(void)
{
    earlycon_base = rt_ioremap_early((void *)LPUART1, LPUART1_SIZE);
}

void rt_hw_earlycon_putc(char c)
{
    LPUART_WriteByte(earlycon_base, c);
    while (!(LPUART_GetStatusFlags(earlycon_base) & kLPUART_TxDataRegEmptyFlag))
        ;
}

static void rt_hw_earlycon_print(const char *str, int print_newline)
{
    int has_cr = 0;
    int has_lf = 0;
    while (*str)
    {
        if (*str == '\r')
        {
            has_cr = 1;
        }
        else if (*str == '\n')
        {
            has_lf = 1;
        }
        rt_hw_earlycon_putc(*str++);
    }
    if (!has_cr && print_newline)
    {
        rt_hw_earlycon_putc('\r');
    }
    if (!has_lf && print_newline)
    {
        rt_hw_earlycon_putc('\n');
    }
}

void rt_hw_earlycon_puts(const char *str)
{
    rt_hw_earlycon_print(str, 1);
}

void rt_hw_earlycon_print_hex(const char *str, rt_base_t hex)
{
    rt_hw_earlycon_print(str, 0);
    rt_hw_earlycon_putc('0');
    rt_hw_earlycon_putc('x');
    for (int i = 60; i >= 0; i -= 4)
    {
        rt_base_t h = (hex >> i) & 0xF;
        rt_hw_earlycon_putc(h < 10 ? '0' + h : 'A' + h - 10);
    }
    rt_hw_earlycon_putc('\r');
    rt_hw_earlycon_putc('\n');
}
#endif

void rt_hw_console_putc(char c)
{
#if defined(BSP_USING_UART1)
    uart_putc(&_uart1_device.serial, c);
#endif
}

void rt_hw_console_output(const char *str)
{
#if defined(BSP_USING_UART1)
    int has_cr = 0;
    int has_lf = 0;
    while (*str)
    {
        if (*str == '\r')
        {
            has_cr = 1;
        }
        else if (*str == '\n')
        {
            has_lf = 1;
        }
        rt_hw_console_putc(*str++);
    }
    if (!has_cr)
    {
        rt_hw_console_putc('\r');
    }
    if (!has_lf)
    {
        rt_hw_console_putc('\n');
    }
#endif
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    uint32_t flags = LPUART_GetStatusFlags(uart->uart_ptr);
    if (flags & kLPUART_RxDataRegFullFlag)
    {
        ch = LPUART_ReadByte(uart->uart_ptr);
    }
    else
    {
        ch = -1;
    }

    return ch;
}

static const struct rt_uart_ops _uart_ops = {
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config;

    /* setup default serial configure */
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert = NRZ_NORMAL;
    config.bufsz = RT_SERIAL_RB_BUFSZ;

    /* Remap CCM controller to virtual address */
    CCM_CTRL = rt_ioremap((void *)CCM_CTRL_BASE, CCM_CTRL_SIZE);

    for (int i = 0; i < RT_ARRAY_SIZE(hw_uart_devices); i++)
    {
        if (hw_uart_devices[i] != RT_NULL)
        {
            hw_uart_devices[i]->serial.ops = &_uart_ops;
            hw_uart_devices[i]->serial.config = config;

            /* Remap LPUART instance to virtual address */
            hw_uart_devices[i]->uart_ptr = rt_ioremap((void *)hw_uart_devices[i]->uart_base, LPUART1_SIZE);

            /* Update LPUART instance */
            LPUART_SetInstance(hw_uart_devices[i]->instance, hw_uart_devices[i]->uart_ptr);

            rt_hw_serial_register(&hw_uart_devices[i]->serial, hw_uart_devices[i]->device_name,
                                  RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, hw_uart_devices[i]);
        }
    }

    return 0;
}
