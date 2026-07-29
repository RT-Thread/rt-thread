/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     yandld      The first version for MCXN
 */

#include <rtthread.h>
#include "drv_uart.h"

#include "fsl_lpuart.h"
#include "fsl_common.h"

#ifdef RT_USING_SERIAL



#include <rtdevice.h>

/* lpc uart driver */
struct mcx_uart
{
    struct rt_serial_device     *serial;  /* Select serial device */
    LPUART_Type                 *uart_base; /* serial base */
    IRQn_Type                   irqn; /* serial interrupt */
    clock_name_t                clock_src; /* serial RTC */
    clock_attach_id_t           clock_attach_id; /* RTC ID */
    clock_ip_name_t             clock_ip_name; /* serial clock name */
    clock_div_name_t            clock_div_name; /* serial clock div */
    char *device_name; /* serial device name */
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;

void LP_FLEXCOMM2_IRQHandler(void)
{
    uart_isr(&serial2); /* Serial interrupt handling function */
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;

void LP_FLEXCOMM4_IRQHandler(void)
{
    uart_isr(&serial4); /* Serial interrupt handling function */
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;

void LP_FLEXCOMM5_IRQHandler(void)
{
    uart_isr(&serial5); /* Serial interrupt handling function */
}
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6) /* same UART4 */
struct rt_serial_device serial6;

void LP_FLEXCOMM6_IRQHandler(void)
{
    uart_isr(&serial6);
}
#endif /* BSP_USING_UART6 */

static const struct mcx_uart uarts[] = /* Initializes the above structure */
{
#ifdef BSP_USING_UART2
    {
        &serial2,
        LPUART2,
        LP_FLEXCOMM2_IRQn,
        kCLOCK_Fro12M,
        kFRO12M_to_FLEXCOMM2,
        kCLOCK_LPFlexComm2,
        kCLOCK_DivFlexcom2Clk,
        "uart2",
    },
#endif
#ifdef BSP_USING_UART4
    {
        &serial4,
        LPUART4,
        LP_FLEXCOMM4_IRQn,
        kCLOCK_Fro12M,
        kFRO12M_to_FLEXCOMM4,
        kCLOCK_LPFlexComm4,
        kCLOCK_DivFlexcom4Clk,
        "uart4",
    },
#endif
#ifdef BSP_USING_UART5
    {
        &serial5,
        LPUART5,
        LP_FLEXCOMM5_IRQn,
        kCLOCK_Fro12M,
        kFRO12M_to_FLEXCOMM5,
        kCLOCK_LPFlexComm5,
        kCLOCK_DivFlexcom5Clk,
        "uart5",
    },
#endif
#ifdef BSP_USING_UART6
    {
        &serial6,
        LPUART6,
        LP_FLEXCOMM6_IRQn,
        kCLOCK_Fro12M,
        kFRO12M_to_FLEXCOMM6,
        kCLOCK_LPFlexComm6,
        kCLOCK_DivFlexcom6Clk,
        "uart6",
    },
#endif
};

/**
 * Configuring the serial port Module.
 *
 * @param serial device
 * @param Configure the serial port configuration structure to set the TX RX features
 */
static rt_err_t mcx_configure(struct rt_serial_device *serial, struct serial_configure *cfg) /* Configuring the serial port Module */
{
    struct mcx_uart *uart; /* Serial port hardware structure, calling the structure initialized above */
    lpuart_config_t config;/* It contains basic configuration parameters of the serial port, such as baud rate, data bit, stop bit, and parity check */

    RT_ASSERT(serial != RT_NULL); /* assert */
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct mcx_uart *)serial->parent.user_data;

    CLOCK_SetClkDiv(uart->clock_div_name, 1u);
    CLOCK_AttachClk(uart->clock_attach_id);
    CLOCK_EnableClock(uart->clock_ip_name);

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = cfg->baud_rate;

    switch (cfg->data_bits)
    {
        case DATA_BITS_7:
            config.dataBitsCount = kLPUART_SevenDataBits;
            break;

        default:
            config.dataBitsCount = kLPUART_EightDataBits;
            break;
    }

    config.enableTx     = true;
    config.enableRx     = true;

    LPUART_Init(uart->uart_base, &config, CLOCK_GetFreq(uart->clock_src));

    return RT_EOK;
}

/**
 * Serial Control Function.
 *
 * @param serial device struct
 * @param control Cmd
 * @param Parameters passed to the control command
 */
static rt_err_t mcx_control(struct rt_serial_device *serial, int cmd, void *arg)/* serial control */
{
    struct mcx_uart *uart = (struct mcx_uart *)serial->parent.user_data; /* Convert the type to struct mcx_uart */

    RT_ASSERT(uart != RT_NULL); /* Assert */

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        LPUART_DisableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        DisableIRQ(uart->irqn);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        EnableIRQ(uart->irqn);
        break;
    }


    return RT_EOK;
}

/**
 * Sends a single character function to a serial device.
 *
 * @param serial device struct
 * @param The serial port character you want to send
 */
static int mcx_putc(struct rt_serial_device *serial, char ch)
{
    struct mcx_uart *uart = (struct mcx_uart *)serial->parent.user_data;

    while(!(kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(uart->uart_base)));
    LPUART_WriteByte(uart->uart_base, ch);

    return 1;
}

static int mcx_getc(struct rt_serial_device *serial)
{
    struct mcx_uart *uart = (struct mcx_uart *)serial->parent.user_data;

    if (kLPUART_RxDataRegFullInterruptEnable & LPUART_GetStatusFlags(uart->uart_base))
/* Check whether the receive cache is full and read the status flag bit of the status register
   This flag is read, indicating that there is data in the cache and can be read */
    {
        return LPUART_ReadByte(uart->uart_base);
    }
    else
    {
        return -1;
    }
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct mcx_uart *uart; /* Create a serial port hardware structure variable */

    RT_ASSERT(serial != RT_NULL);

    uart = (struct mcx_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver -------------------------------------------------*/
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);

    /* leave interrupt */
    rt_interrupt_leave();
}

static const struct rt_uart_ops mcx_uart_ops =
{
    mcx_configure,
    mcx_control,
    mcx_putc,
    mcx_getc,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT; /* initial struct [115200,8,1,NONE] */
    int i;
/* Registers loops for multiple serial devices */
    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++) /* sizeof(uarts) / sizeof(uarts[0] : Calculate the number of struct mcx_uart serial ports */
    {
        uarts[i].serial->ops    = &mcx_uart_ops;
        uarts[i].serial->config = config;

/**
 * register UART device.
 *
 * @param Indicates the structure of the serial port device to be registered
 * @param device name
 * @param Flag bit mask
 * @param A pointer to the current device that is used as user private data at registration
 */
        rt_hw_serial_register(uarts[i].serial, uarts[i].device_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, (void *)&uarts[i]);
    }

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_uart_init); /* RT-Thread Automatic initialization mechanism */

#endif /*BSP_USING_SERIAL */
