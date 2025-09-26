/*
 * COPYRIGHT (C) 2015, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-12     BruceOu      The first version
 * 2025-08-10     Siwei Xu     Fix compile errors
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

    LPUART_Type* uart_base;
    int irqn;

    clock_root_t clock_root; /* clock root */
    clock_root_mux_source_t clock_mux; /* clock mux */
    clock_ip_name_t clock_ip_name; /* clock control gate */
};

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
static struct hw_uart_device _uart1_device =
{
    .device_name = "uart1",
    .uart_base = LPUART1,
    .irqn = LPUART1_IRQn,
    .clock_root = kCLOCK_Root_Lpuart1,
    .clock_mux = kCLOCK_LPUART1_ClockRoot_MuxOsc24M,
    .clock_ip_name = kCLOCK_Lpuart1,
};
#endif

static struct hw_uart_device* hw_uart_devices[] =
{
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
    // struct hw_uart_device *uart;
    // uint32_t baudrate;
    // uint8_t parity, stopbits, datasize, flowcontrol;

    // RT_ASSERT(serial != RT_NULL);
    // uart = (struct hw_uart_device *)serial->parent.user_data;

    // baudrate = cfg->baud_rate;
    // switch (cfg->data_bits)
    // {
    // case DATA_BITS_8:
    //     datasize = EIGHTBITS;
    //     break;
    // case DATA_BITS_7:
    //     datasize = SEVENBITS;
    //     break;
    // }
    // if (cfg->stop_bits == STOP_BITS_1) stopbits = STOPBITS_ONE;
    // else if (cfg->stop_bits == STOP_BITS_2) stopbits = STOPBITS_TWO;

    // parity = PARITY_NONE;
    // flowcontrol = FLOWCTRL_OFF;

    // /* Initialize UART */
    // uart_init(uart->uart_base, baudrate, parity, stopbits, datasize, flowcontrol);

    // rt_hw_interrupt_install(uart->irqn, rt_hw_uart_isr, serial, "uart");
    // rt_hw_interrupt_mask(uart->irqn);

    // /* Set the IRQ mode for the Rx FIFO */
    // uart_set_FIFO_mode(uart->uart_base, RX_FIFO, 1, IRQ_MODE);

    struct hw_uart_device *uart = RT_NULL;
    static lpuart_config_t config;

    rt_hw_console_output("uart_configure start ...\n");
    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    rt_hw_console_output("uart_configure LPUART_GetDefaultConfig ...\n");
    LPUART_GetDefaultConfig(&config);
    rt_hw_console_output("uart_configure LPUART_GetDefaultConfig done!\n");

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
    if (cfg->bit_order == BIT_ORDER_LSB) {
        config.isMsb = false;
    } else {
        config.isMsb = true;
    }

    // hardware flow control
#if defined(FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT) && FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT
    if (cfg->flowcontrol == RT_SERIAL_FLOWCONTROL_NONE) {
        // disable hardware flow control
        config.enableRxRTS = false;
        config.enableTxCTS = false;
    } else {
        // enable hardware flow control
        config.enableRxRTS = true;
        config.enableTxCTS = true;
    }
#endif

    // enable TX and RX
    config.enableTx = serial->parent.flag & RT_DEVICE_FLAG_WRONLY;
    config.enableRx = serial->parent.flag & RT_DEVICE_FLAG_RDONLY;

    // Set UART clock source and clock divider
    // CLOCK_SetRootClockMux(uart->clock_root, uart->clock_mux);
    // CLOCK_SetRootClockDiv(uart->clock_root, 1U);

    // Initialize the LPUART module with the configuration structure and clock source
    rt_hw_console_output("uart_configure LPUART_Init ...\n");
    LPUART_Init(uart->uart_base, &config, CLOCK_GetIpFreq(uart->clock_root));

    // Install interrupt handler
    rt_hw_console_output("uart_configure rt_hw_interrupt_install ...\n");   
    rt_hw_interrupt_install(uart->irqn, rt_hw_uart_isr, serial, "uart");
    rt_hw_interrupt_mask(uart->irqn);

    // Enable RX interrupt
    rt_hw_console_output("uart_configure LPUART_EnableInterrupts ...\n");
    LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
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

    while (!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag)) {
        __NOP();
    }

    LPUART_WriteByte(uart->uart_base, c);

    return 1;
}

void imx_uart1_putc(char c)
{
    LPUART_WriteByte(LPUART1, c);
    while (!(LPUART_GetStatusFlags(LPUART1) & kLPUART_TxDataRegEmptyFlag));
}

void imx_uart1_puts(const char *str)
{
    int has_cr = 0;
    while (*str) {
        if (*str == '\r') {
            has_cr = 1;
        } else if (*str == '\n') {
            if (!has_cr) {
                imx_uart1_putc('\r');
            }
        }
        imx_uart1_putc(*str++);
    }
}

void imx_uart1_print_hex(const char *str, rt_base_t hex)
{
    imx_uart1_puts(str);
    imx_uart1_putc('0');
    imx_uart1_putc('x');
    for (int i = 60; i >= 0; i -= 4) {
        rt_base_t h = (hex >> i) & 0xF;
        imx_uart1_putc(h < 10 ? '0' + h : 'A' + h - 10);
    }
    imx_uart1_putc('\r');
    imx_uart1_putc('\n');
}

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
    while (*str) {
        if (*str == '\r') {
            has_cr = 1;
        } else if (*str == '\n') {
            if (!has_cr) {
                rt_hw_console_putc('\r');
            }
        }
        rt_hw_console_putc(*str++);
    }
#endif
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    uint32_t flags = LPUART_GetStatusFlags(uart->uart_base);
    if (flags & kLPUART_RxDataRegFullFlag) {
        ch = LPUART_ReadByte(uart->uart_base);
    } else {
        ch = -1;
    }

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config;
    /* set serial configure */
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    for (int i = 0; i < RT_ARRAY_SIZE(hw_uart_devices); i++)
    {
        if (hw_uart_devices[i] != RT_NULL)
        {
            hw_uart_devices[i]->serial.ops = &_uart_ops;
            hw_uart_devices[i]->serial.config = config;
            // hw_uart_devices[i]->uart_base = rt_ioremap((void *)hw_uart_devices[i]->uart_base, sizeof(LPUART_Type));

            rt_hw_serial_register(&hw_uart_devices[i]->serial, hw_uart_devices[i]->device_name,
                                  RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, hw_uart_devices[i]);
        }
    }

    return 0;
}
// INIT_BOARD_EXPORT(rt_hw_uart_init);
