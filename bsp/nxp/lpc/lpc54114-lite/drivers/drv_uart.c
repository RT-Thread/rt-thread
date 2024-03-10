/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-18     Bernard      The first version for LPC40xx
 * 2014-12-16     RT_learning  The first version for LPC5410x
 * 2017-08-01     XiaoYang     The first version for LPC546xx
 * 2018-11-30     yangjie      The first version for LPC54114
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "fsl_usart.h"
#include "fsl_common.h"
#include "fsl_iocon.h"

struct lpc_uart
{
    USART_Type *UART;
    IRQn_Type UART_IRQn;
};

static rt_err_t lpc_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct lpc_uart *uart;
    usart_config_t u0_config;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct lpc_uart *)serial->parent.user_data;

    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUSART_ParityDisabled;
     * config.stopBitCount = kUSART_OneStopBit;
     * config.loopback = false;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    USART_GetDefaultConfig(&u0_config);

    u0_config.baudRate_Bps = cfg->baud_rate;
    u0_config.parityMode = kUSART_ParityDisabled,
    u0_config.stopBitCount = kUSART_OneStopBit,
    u0_config.bitCountPerChar = kUSART_8BitsPerChar,
    u0_config.loopback = false,
    u0_config.txWatermark = kUSART_TxFifo0,
    u0_config.rxWatermark = kUSART_RxFifo1,
    u0_config.enableTx = true;
    u0_config.enableRx = true;

    USART_Init(uart->UART, &u0_config, CLOCK_GetFreq(kCLOCK_Flexcomm0));

    return RT_EOK;
}

static rt_err_t lpc_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct lpc_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct lpc_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        USART_DisableInterrupts(uart->UART, kUSART_RxLevelInterruptEnable);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        USART_EnableInterrupts(uart->UART, kUSART_RxLevelInterruptEnable);
        break;
    }

    return RT_EOK;
}

static int lpc_putc(struct rt_serial_device *serial, char c)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;

    while (!(kUSART_TxFifoNotFullFlag & USART_GetStatusFlags(uart->UART)));

    USART_WriteByte(uart->UART, c);

    return 1;
}

static int lpc_getc(struct rt_serial_device *serial)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;
    if (kUSART_RxFifoNotEmptyFlag & USART_GetStatusFlags(uart->UART))
    {
        return USART_ReadByte(uart->UART);
    }
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

#define PORT0_IDX                        0u   /*!< Port index */
#define PIN0_IDX                         0u   /*!< Pin number for pin 0 */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 */

/* UART0 device driver structure */
struct lpc_uart uart0 =
{
    USART0,
    FLEXCOMM0_IRQn,
};
struct rt_serial_device serial0;

void FLEXCOMM0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);

    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_uart_init(void)
{
    struct lpc_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0

    uart = &uart0;

    serial0.ops    = &lpc_uart_ops;
    serial0.config = config;
    serial0.parent.user_data = uart;

    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

    /* reset FLEXCOMM for USART */
    RESET_PeripheralReset(kFC0_RST_SHIFT_RSTn);

    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    const uint32_t port0_pin0_config = ((IOCON->PIO[PORT0_IDX][PIN0_IDX] &
                                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))    /* Mask bits to zero which are setting */
                                        | IOCON_PIO_FUNC(1)                   /* Selects pin function: PORT00 (pin 31) is configured as FC0_RXD_SDA_MOSI. */
                                        | IOCON_PIO_DIGIMODE(1));             /* Select Analog/Digital mode : Digital mode. */

    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN0_IDX, port0_pin0_config);           /* PORT0 PIN0 (coords: 31) is configured as FC0_RXD_SDA_MOSI */

    const uint32_t port0_pin1_config = ((IOCON->PIO[PORT0_IDX][PIN1_IDX] &
                                        (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))    /* Mask bits to zero which are setting */
                                        | IOCON_PIO_FUNC(1)                   /* Selects pin function: PORT01 (pin 32) is configured as FC0_TXD_SCL_MISO. */
                                        | IOCON_PIO_DIGIMODE(1));             /* Select Analog/Digital mode : Digital mode. */

    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN1_IDX, port0_pin1_config);           /* PORT0 PIN1 (coords: 32) is configured as FC0_TXD_SCL_MISO */

    /* Enable RX interrupt. */
    USART_EnableInterrupts(uart->UART, kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable);
    EnableIRQ(uart->UART_IRQn);

    CLOCK_DisableClock(kCLOCK_Iocon);

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);

#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
