/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        the first version
 */
#include <rtthread.h>
#include "usart.h"

#include "fsl_common.h"
#include "fsl_lpuart.h"
#include "fsl_iomuxc.h"

#ifdef RT_USING_UART

#if !defined(RT_USING_UART0) && !defined(RT_USING_UART1) && \
    !defined(RT_USING_UART2) && !defined(RT_USING_UART3) && \
    !defined(RT_USING_UART4) && !defined(RT_USING_UART5) && \
    !defined(RT_USING_UART6) && !defined(RT_USING_UART7)
#error "Please define at least one UARTx"

#endif
        
#include <rtdevice.h>

/* imxrt uart driver */
struct imxrt_uart
{
    LPUART_Type * uart_base;
    IRQn_Type irqn;

    struct rt_serial_device * serial;
    char *device_name;
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(RT_USING_UART1)
struct rt_serial_device serial1;

void LPUART1_IRQHandler(void)
{
    uart_isr(&serial1);
}

#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART2)
struct rt_serial_device serial2;

void USART2_IRQHandler(void)
{
    uart_isr(&serial2);
}

#endif /* RT_USING_UART2 */

#if defined(RT_USING_UART3)
struct rt_serial_device serial3;

void UART3_IRQHandler(void)
{
    uart_isr(&serial3);
}

#endif /* RT_USING_UART3 */

#if defined(RT_USING_UART4)
struct rt_serial_device serial4;

void UART4_IRQHandler(void)
{
    uart_isr(&serial4);
}
#endif /* RT_USING_UART4 */

#if defined(RT_USING_UART5)
struct rt_serial_device serial5;

void USART5_IRQHandler(void)
{
    uart_isr(&serial5);
}

#endif /* RT_USING_UART5 */

#if defined(RT_USING_UART6)
struct rt_serial_device serial6;

void UART6_IRQHandler(void)
{
    uart_isr(&serial6);
}

#endif /* RT_USING_UART6 */

#if defined(RT_USING_UART7)
struct rt_serial_device serial7;

void UART7_IRQHandler(void)
{
    uart_isr(&serial7);
}

#endif /* RT_USING_UART7 */

#if defined(RT_USING_UART8)
struct rt_serial_device serial8;

void UART7_IRQHandler(void)
{
    uart_isr(&serial8);
}

#endif /* RT_USING_UART8 */

static const struct imxrt_uart uarts[] = {
    #ifdef RT_USING_UART1
    {
        LPUART1,
        LPUART1_IRQn,
        &serial1,
        "uart1",
    },
    #endif
  
};

/* Get debug console frequency. */
uint32_t BOARD_DebugConsoleSrcFreq(void)
{
    uint32_t freq;

    /* To make it simple, we assume default PLL and divider settings, and the only variable
       from application is use PLL3 source or OSC source */
    if (CLOCK_GetMux(kCLOCK_UartMux) == 0) /* PLL3 div6 80M */
    {
        freq = (CLOCK_GetPllFreq(kCLOCK_PllUsb1) / 6U) / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }
    else
    {
        freq = CLOCK_GetOscFreq() / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }

    return freq;
}


/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void imxrt_uart_gpio_init(struct imxrt_uart *uart)
{
    if (uart->uart_base == LPUART1)
    {
        CLOCK_EnableClock(kCLOCK_Iomuxc);          /* iomuxc clock (iomuxc_clk_enable): 0x03u */

        IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_12_LPUART1_TX,        /* GPIO_AD_B0_12 is configured as LPUART1_TX */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
        IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_13_LPUART1_RX,        /* GPIO_AD_B0_13 is configured as LPUART1_RX */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
        IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_12_LPUART1_TX,        /* GPIO_AD_B0_12 PAD functional properties : */
          0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                     Drive Strength Field: R0/6
                                                     Speed Field: medium(100MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Keeper
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                     Hyst. Enable Field: Hysteresis Disabled */
        IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_13_LPUART1_RX,        /* GPIO_AD_B0_13 PAD functional properties : */
          0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                     Drive Strength Field: R0/6
                                                     Speed Field: medium(100MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Keeper
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                     Hyst. Enable Field: Hysteresis Disabled */
    }
    else
    {
        RT_ASSERT(RT_NULL);
    }
}

static rt_err_t imxrt_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct imxrt_uart *uart;
    lpuart_config_t config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct imxrt_uart *)serial->parent.user_data;
    
    imxrt_uart_gpio_init(uart);
    
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

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        config.stopBitCount = kLPUART_OneStopBit;
        break;
    default:
        config.stopBitCount = kLPUART_TwoStopBit;
        break;
    }

    switch (cfg->parity)
    {
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
    
    config.enableTx = true;
    config.enableRx = true;
    
    LPUART_Init(uart->uart_base, &config, BOARD_DebugConsoleSrcFreq());
    
    
    return RT_EOK;
}

static rt_err_t imxrt_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct imxrt_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
        LPUART_DisableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        /* disable rx irq */
        DisableIRQ(uart->irqn);
        
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable interrupt */
        LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        /* enable rx irq */
        EnableIRQ(uart->irqn);
        break;
    }

    return RT_EOK;
}

static int imxrt_putc(struct rt_serial_device *serial, char ch)
{
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct imxrt_uart *)serial->parent.user_data;

    LPUART_WriteByte(uart->uart_base, ch);
    while(!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag));
    
    return 1;
}

static int imxrt_getc(struct rt_serial_device *serial)
{
    int ch;
    struct imxrt_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct imxrt_uart *)serial->parent.user_data;

    ch = -1;
    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
        ch = LPUART_ReadByte(uart->uart_base);
    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct imxrt_uart *uart = (struct imxrt_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);
    
    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver -------------------------------------------------*/
    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    
    /* leave interrupt */
    rt_interrupt_leave();
}

static const struct rt_uart_ops imxrt_uart_ops =
{
    imxrt_configure,
    imxrt_control,
    imxrt_putc,
    imxrt_getc,
};

int imxrt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

    
    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &imxrt_uart_ops;
        uarts[i].serial->config = config;

        /* register UART1 device */
        rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}
INIT_BOARD_EXPORT(imxrt_hw_usart_init);

#endif /*RT_USING_UART*/
