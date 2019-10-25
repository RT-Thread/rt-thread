/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 */

#include <rtthread.h>
#include "drv_uart.h"

#include "fsl_usart.h"
#include "fsl_common.h"
#include "fsl_iocon.h"

#ifdef RT_USING_SERIAL

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

#if !defined(BSP_USING_UART0) && \
    !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && \
    !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"
#endif

#include <rtdevice.h>

/* lpc uart driver */
struct lpc_uart
{
    USART_Type *uart_base;
    IRQn_Type irqn;
    clock_name_t clock_src;
    
    struct rt_serial_device *serial;
    char *device_name;
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void FLEXCOMM0_IRQHandler(void)
{
    uart_isr(&serial0);
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;

void FLEXCOMM1_IRQHandler(void)
{
    uart_isr(&serial1);
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;

void FLEXCOMM2_IRQHandler(void)
{
    uart_isr(&serial2);
}

#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;

void FLEXCOMM3_IRQHandler(void)
{
    uart_isr(&serial3);
}

#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;

void FLEXCOMM4_IRQHandler(void)
{
    uart_isr(&serial4);
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;

void FLEXCOMM5_IRQHandler(void)
{
    uart_isr(&serial5);
}

#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
struct rt_serial_device serial6;

void FLEXCOMM6_IRQHandler(void)
{
    uart_isr(&serial6);
}

#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
struct rt_serial_device serial7;

void FLEXCOMM7_IRQHandler(void)
{
    uart_isr(&serial7);
}

#endif /* BSP_USING_UART7 */

static const struct lpc_uart uarts[] =
{
#ifdef BSP_USING_UART0
    {
        USART0,
        FLEXCOMM0_IRQn,
        kCLOCK_Flexcomm0,
        
        &serial0,
        "uart",
    },
#endif
#ifdef BSP_USING_UART1
    {
        USART1,
        FLEXCOMM1_IRQn,
        kCLOCK_Flexcomm1,
        
        &serial1,
        "uart1",
    },
#endif
#ifdef BSP_USING_UART2
    {
        USART2,
        FLEXCOMM2_IRQn,
        kCLOCK_Flexcomm2,
        
        &serial2,
        "uart2",
    },
#endif
#ifdef BSP_USING_UART3
    {
        USART3,
        FLEXCOMM3_IRQn,
        kCLOCK_Flexcomm3,
        
        &serial3,
        "uart3",
    },
#endif
#ifdef BSP_USING_UART4
    {
        USART4,
        FLEXCOMM4_IRQn,
        kCLOCK_Flexcomm4,
        
        &serial4,
        "uart4",
    },
#endif
#ifdef BSP_USING_UART5
    {
        USART5,
        FLEXCOMM5_IRQn,
        kCLOCK_Flexcomm5,
        
        &serial5,
        "uart5",
    },
#endif
#ifdef BSP_USING_UART6
    {
        USART6,
        FLEXCOMM6_IRQn,
        kCLOCK_Flexcomm6,
        
        &serial6,
        "uart6",
    },
#endif
#ifdef BSP_USING_UART7
    {
        USART7,
        FLEXCOMM7_IRQn,
        kCLOCK_Flexcomm7,
        
        &serial7,
        "uart7",
    },
#endif
};

/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void lpc_uart_gpio_init(struct lpc_uart *uart)
{
    if (uart->uart_base != RT_NULL)
    {
#ifdef BSP_USING_UART0
        /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);
#endif
#ifdef BSP_USING_UART1
        /* attach 12 MHz clock to FLEXCOMM1 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1);
#endif
#ifdef BSP_USING_UART2
        /* attach 12 MHz clock to FLEXCOMM2 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
#endif
#ifdef BSP_USING_UART3
        /* attach 12 MHz clock to FLEXCOMM3 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);
#endif
#ifdef BSP_USING_UART4
        /* attach 12 MHz clock to FLEXCOMM4 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);
#endif
#ifdef BSP_USING_UART5
        /* attach 12 MHz clock to FLEXCOMM5 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM5);
#endif
#ifdef BSP_USING_UART6
        /* attach 12 MHz clock to FLEXCOMM6 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM6);
#endif
#ifdef BSP_USING_UART7
        /* attach 12 MHz clock to FLEXCOMM7 (debug console) */
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);
#endif
    }
    else
    {
        RT_ASSERT(RT_NULL);
    }
}


static rt_err_t lpc_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct lpc_uart *uart;
    usart_config_t config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    
    uart = (struct lpc_uart *)serial->parent.user_data;

    lpc_uart_gpio_init(uart);
    
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUSART_ParityDisabled;
     * config.stopBitCount = kUSART_OneStopBit;
     * config.loopback = false;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    USART_GetDefaultConfig(&config);
    config.baudRate_Bps = cfg->baud_rate;
    
    switch (cfg->data_bits)
    {
        case DATA_BITS_7:
            config.bitCountPerChar = kUSART_7BitsPerChar;
            break;

        default:
            config.bitCountPerChar = kUSART_8BitsPerChar;
            break;
    }
    
    switch (cfg->stop_bits)
    {
        case STOP_BITS_2:
            config.stopBitCount = kUSART_TwoStopBit;
            break;
        default:
            config.stopBitCount = kUSART_OneStopBit;
            break;
    }
    
    switch (cfg->parity)
    {
        case PARITY_ODD:
            config.parityMode = kUSART_ParityOdd;
            break;
        case PARITY_EVEN:
            config.parityMode = kUSART_ParityEven;
            break;
        default:
            config.parityMode = kUSART_ParityDisabled;
            break;
    }
    
    config.enableTx = true;
    config.enableRx = true;

    USART_Init(uart->uart_base, &config, CLOCK_GetFreq(uart->clock_src));

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
        USART_DisableInterrupts(uart->uart_base, kUSART_RxLevelInterruptEnable);
        DisableIRQ(uart->irqn);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        USART_EnableInterrupts(uart->uart_base, kUSART_RxLevelInterruptEnable);
        EnableIRQ(uart->irqn);
        break;
    }

    return RT_EOK;
}

static int lpc_putc(struct rt_serial_device *serial, char ch)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;

    while (!(kUSART_TxFifoNotFullFlag & USART_GetStatusFlags(uart->uart_base)));

    USART_WriteByte(uart->uart_base, ch);

    return 1;
}

static int lpc_getc(struct rt_serial_device *serial)
{
    struct lpc_uart *uart;

    uart = (struct lpc_uart *)serial->parent.user_data;
    if (kUSART_RxFifoNotEmptyFlag & USART_GetStatusFlags(uart->uart_base))
    {
        return USART_ReadByte(uart->uart_base);
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
    struct lpc_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct lpc_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver -------------------------------------------------*/
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

static const struct rt_uart_ops lpc_uart_ops =
{
    lpc_configure,
    lpc_control,
    lpc_putc,
    lpc_getc,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;
    
    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &lpc_uart_ops;
        uarts[i].serial->config = config;

        /* register UART device */
        rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /*BSP_USING_SERIAL */
