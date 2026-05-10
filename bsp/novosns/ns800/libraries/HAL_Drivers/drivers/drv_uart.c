/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     SummerGift   first version
 * 2020-03-16     SummerGift   add device close feature
 * 2020-03-20     SummerGift   fix bug caused by ORE
 * 2026-05-10     Codex        Reworked driver around BSP UART config tables
 */

#include "board.h"
#include "drv_uart.h"
#include "drv_config.h"

#ifdef RT_USING_SERIAL

#define DRV_DEBUG
#define LOG_TAG             "drv.uart"
#include <drv_log.h>

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4)
#error "Please define at least one BSP_USING_UARTx"
#endif

#ifndef BSP_NS800_UART_TX_TIMEOUT
#define BSP_NS800_UART_TX_TIMEOUT 6000
#endif

#ifdef RT_USING_SERIAL_V2
#define NS800_UART_BUF_CONFIG(_rxbuf, _txbuf)              \
    .rx_bufsz = (_rxbuf),                                  \
    .tx_bufsz = (_txbuf),
#define NS800_UART_DEFAULT_TX_TIMEOUT 0U
#else
#ifndef RT_SERIAL_RB_BUFSZ
#define RT_SERIAL_RB_BUFSZ 64
#endif

#define NS800_UART_BUF_CONFIG(_rxbuf, _txbuf)              \
    .rx_bufsz = RT_SERIAL_RB_BUFSZ,                        \
    .tx_bufsz = 0U,
#define NS800_UART_DEFAULT_TX_TIMEOUT BSP_NS800_UART_TX_TIMEOUT
#endif

enum
{
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
};

#ifdef BSP_USING_UART1
void UART1_IRQHandler(void);
#endif
#ifdef BSP_USING_UART2
void UART2_IRQHandler(void);
#endif
#ifdef BSP_USING_UART3
void UART3_IRQHandler(void);
#endif
#ifdef BSP_USING_UART4
void UART4_IRQHandler(void);
#endif

static struct ns800_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    {
        .name = "uart1",
        .Instance = UART1,
        .rx_irq_type = UART1_RX_IRQn,
        .tx_irq_type = UART1_TX_IRQn,
        .irq_handler = UART1_IRQHandler,
        .rx_port = GPIOA,
        .rx_pin = GPIO_PIN_13,
        .rx_mux = ALT6_FUNCTION,
        .rx_pad = GPIO_PIN_TYPE_PULLUP,
        .rx_direction = GPIO_DIR_MODE_IN,
        .rx_drive_max = RT_FALSE,
        .tx_port = GPIOA,
        .tx_pin = GPIO_PIN_12,
        .tx_mux = ALT6_FUNCTION,
        .tx_pad = GPIO_PIN_TYPE_STD,
        .tx_direction = GPIO_DIR_MODE_OUT,
        .tx_drive_max = RT_FALSE,
        .tx_block_timeout = NS800_UART_DEFAULT_TX_TIMEOUT,
        NS800_UART_BUF_CONFIG(BSP_UART1_RX_BUFSIZE, BSP_UART1_TX_BUFSIZE)
    },
#endif
#ifdef BSP_USING_UART2
    {
        .name = "uart2",
        .Instance = UART2,
        .rx_irq_type = UART2_RX_IRQn,
        .tx_irq_type = UART2_TX_IRQn,
        .irq_handler = UART2_IRQHandler,
        .rx_port = GPIOB,
        .rx_pin = GPIO_PIN_7,
        .rx_mux = ALT1_FUNCTION,
        .rx_pad = GPIO_PIN_TYPE_PULLUP,
        .rx_direction = GPIO_DIR_MODE_IN,
        .rx_drive_max = RT_FALSE,
        .tx_port = GPIOB,
        .tx_pin = GPIO_PIN_6,
        .tx_mux = ALT1_FUNCTION,
        .tx_pad = GPIO_PIN_TYPE_STD,
        .tx_direction = GPIO_DIR_MODE_OUT,
        .tx_drive_max = RT_TRUE,
        .tx_block_timeout = NS800_UART_DEFAULT_TX_TIMEOUT,
        NS800_UART_BUF_CONFIG(BSP_UART2_RX_BUFSIZE, BSP_UART2_TX_BUFSIZE)
    },
#endif
#ifdef BSP_USING_UART3
    {
        .name = "uart3",
        .Instance = UART3,
        .rx_irq_type = UART3_RX_IRQn,
        .tx_irq_type = UART3_TX_IRQn,
        .irq_handler = UART3_IRQHandler,
        .rx_port = GPIOB,
        .rx_pin = GPIO_PIN_25,
        .rx_mux = ALT11_FUNCTION,
        .rx_pad = GPIO_PIN_TYPE_PULLUP,
        .rx_direction = GPIO_DIR_MODE_IN,
        .rx_drive_max = RT_FALSE,
        .tx_port = GPIOB,
        .tx_pin = GPIO_PIN_24,
        .tx_mux = ALT11_FUNCTION,
        .tx_pad = GPIO_PIN_TYPE_STD,
        .tx_direction = GPIO_DIR_MODE_OUT,
        .tx_drive_max = RT_TRUE,
        .tx_block_timeout = NS800_UART_DEFAULT_TX_TIMEOUT,
        NS800_UART_BUF_CONFIG(BSP_UART3_RX_BUFSIZE, BSP_UART3_TX_BUFSIZE)
    },
#endif
#ifdef BSP_USING_UART4
    {
        .name = "uart4",
        .Instance = UART4,
        .rx_irq_type = UART4_RX_IRQn,
        .tx_irq_type = UART4_TX_IRQn,
        .irq_handler = UART4_IRQHandler,
        .rx_port = GPIOB,
        .rx_pin = GPIO_PIN_13,
        .rx_mux = ALT7_FUNCTION,
        .rx_pad = GPIO_PIN_TYPE_PULLUP,
        .rx_direction = GPIO_DIR_MODE_IN,
        .rx_drive_max = RT_FALSE,
        .tx_port = GPIOB,
        .tx_pin = GPIO_PIN_12,
        .tx_mux = ALT7_FUNCTION,
        .tx_pad = GPIO_PIN_TYPE_STD,
        .tx_direction = GPIO_DIR_MODE_OUT,
        .tx_drive_max = RT_TRUE,
        .tx_block_timeout = NS800_UART_DEFAULT_TX_TIMEOUT,
        NS800_UART_BUF_CONFIG(BSP_UART4_RX_BUFSIZE, BSP_UART4_TX_BUFSIZE)
    },
#endif
};

static struct ns800_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static void ns800_uart_gpio_init(const struct ns800_uart_config *config)
{
    RT_ASSERT(config != RT_NULL);

    GPIO_setPinConfig(config->rx_port, config->rx_pin, config->rx_mux);
    GPIO_setAnalogMode(config->rx_port, config->rx_pin, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(config->rx_port, config->rx_pin, config->rx_pad);
    GPIO_setQualificationMode(config->rx_port, config->rx_pin, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(config->rx_port, config->rx_pin, config->rx_direction);
    if (config->rx_drive_max)
    {
        GPIO_setDriveLevel(config->rx_port, config->rx_pin, GPIO_DRV_MAX);
    }

    GPIO_setPinConfig(config->tx_port, config->tx_pin, config->tx_mux);
    GPIO_setAnalogMode(config->tx_port, config->tx_pin, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(config->tx_port, config->tx_pin, config->tx_pad);
    GPIO_setQualificationMode(config->tx_port, config->tx_pin, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(config->tx_port, config->tx_pin, config->tx_direction);
    if (config->tx_drive_max)
    {
        GPIO_setDriveLevel(config->tx_port, config->tx_pin, GPIO_DRV_MAX);
    }
}

static UART_BitCountPerChar ns800_uart_data_bits(rt_uint32_t data_bits)
{
    switch (data_bits)
    {
    case DATA_BITS_7:
        return UART_7_BITS_PER_CHAR;
    case DATA_BITS_9:
        return UART_9_BITS_PER_CHAR;
    case DATA_BITS_8:
    default:
        return UART_8_BITS_PER_CHAR;
    }
}

static void ns800_uart_apply_runtime_cfg(struct ns800_uart *uart, struct serial_configure *cfg)
{
    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart->handle.Instance = uart->config->Instance;
    uart->handle.baud_rate = cfg->baud_rate;
    uart->handle.data_bits = cfg->data_bits;
    uart->handle.stop_bits = cfg->stop_bits;
    uart->handle.parity = cfg->parity;
}

static void ns800_uart_clear_errors(UART_TypeDef *instance)
{
    UART_clearErrorFlags(instance,
                         UART_STAT_OR_M |
                         UART_STAT_NF_M |
                         UART_STAT_FE_M |
                         UART_STAT_PF_M);
}

static rt_err_t ns800_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ns800_uart *uart;
    UART_BitCountPerChar bit_count;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct ns800_uart, serial);

    ns800_uart_apply_runtime_cfg(uart, cfg);
    ns800_uart_gpio_init(uart->config);

    bit_count = ns800_uart_data_bits(cfg->data_bits);

    UART_resetModule(uart->handle.Instance);
    UART_setBaud(uart->handle.Instance, cfg->baud_rate);

    if (cfg->parity == PARITY_ODD)
    {
        UART_setBitCountPerChar(uart->handle.Instance, bit_count, true);
        UART_setParityMode(uart->handle.Instance, UART_PAR_ODD);
    }
    else if (cfg->parity == PARITY_EVEN)
    {
        UART_setBitCountPerChar(uart->handle.Instance, bit_count, true);
        UART_setParityMode(uart->handle.Instance, UART_PAR_EVEN);
    }
    else
    {
        UART_setBitCountPerChar(uart->handle.Instance, bit_count, false);
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        UART_setStopBitCount(uart->handle.Instance, UART_TWO_STOP_BIT);
        break;
    case STOP_BITS_1:
    default:
        UART_setStopBitCount(uart->handle.Instance, UART_ONE_STOP_BIT);
        break;
    }

    ns800_uart_clear_errors(uart->handle.Instance);

#ifdef RT_USING_SERIAL_V2
    UART_enableTxFifo(uart->handle.Instance);
    UART_resetTxFifo(uart->handle.Instance);
    UART_setTxFifoWatermark(uart->handle.Instance, UART_FIFO_TX6);

    UART_enableRxFifo(uart->handle.Instance);
    UART_resetRxFifo(uart->handle.Instance);
    UART_setRxFifoWatermark(uart->handle.Instance, UART_FIFO_RX1);
    UART_setRxIdleCharacter(uart->handle.Instance, UART_IDLE_CHARACTER_CNT0);
#else
    /*
     * RT-Thread serial v1 consumes RX data byte-by-byte from getc().
     * Keep the hardware in the simplest non-FIFO mode to avoid RDRF
     * reasserting on idle-partial FIFO conditions.
     */
    UART_disableTxFifo(uart->handle.Instance);
    UART_disableRxFifo(uart->handle.Instance);
    UART_setRxIdleCharacter(uart->handle.Instance, UART_IDLE_CHARACTER_CNT0);
#endif

    UART_enableTxModule(uart->handle.Instance);
    UART_enableRxModule(uart->handle.Instance);

    uart->tx_block_timeout = uart->config->tx_block_timeout;

    return RT_EOK;
}

static rt_err_t ns800_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ns800_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ns800_uart, serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
    {
        rt_uint32_t direction = (rt_uint32_t)arg;

        Interrupt_disable(uart->config->rx_irq_type);
        if (direction == RT_DEVICE_FLAG_INT_RX)
        {
            UART_disableInterrupt(uart->handle.Instance, UART_INT_RX_DATA_REG_FULL);
        }
        else if (direction == RT_DEVICE_FLAG_INT_TX)
        {
            UART_disableInterrupt(uart->handle.Instance, UART_INT_TX_COMPLETE);
            Interrupt_disable(uart->config->tx_irq_type);
        }
        break;
    }

    case RT_DEVICE_CTRL_SET_INT:
    {
        rt_uint32_t direction = (rt_uint32_t)arg;

        if (direction == RT_DEVICE_FLAG_INT_RX)
        {
            UART_enableInterrupt(uart->handle.Instance, UART_INT_RX_DATA_REG_FULL);
            Interrupt_register(uart->config->rx_irq_type, uart->config->irq_handler);
            Interrupt_enable(uart->config->rx_irq_type);
        }
        else if (direction == RT_DEVICE_FLAG_INT_TX)
        {
            UART_enableInterrupt(uart->handle.Instance, UART_INT_TX_COMPLETE);
            Interrupt_register(uart->config->tx_irq_type, uart->config->irq_handler);
            Interrupt_enable(uart->config->tx_irq_type);
        }
        break;
    }

    case RT_DEVICE_CTRL_CLOSE:
        UART_disableTxModule(uart->handle.Instance);
        UART_disableRxModule(uart->handle.Instance);
        break;

    case UART_CTRL_SET_BLOCK_TIMEOUT:
    {
        rt_uint32_t block_timeout = (rt_uint32_t)arg;

        if (block_timeout == 0U)
        {
            return -RT_ERROR;
        }

        uart->tx_block_timeout = block_timeout;
        break;
    }

    default:
        break;
    }

    return RT_EOK;
}

static int ns800_putc(struct rt_serial_device *serial, char c)
{
    struct ns800_uart *uart;
    rt_uint32_t block_timeout;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct ns800_uart, serial);
    block_timeout = uart->tx_block_timeout;

    while (!UART_isSpaceAvailable(uart->handle.Instance))
    {
        if (block_timeout-- == 0U)
        {
            return -1;
        }
    }

    UART_writeChar(uart->handle.Instance, (rt_uint8_t)c);

    while ((uart->handle.Instance->STAT.BIT.TC == false) && (--block_timeout != 0U))
    {
    }

    return (block_timeout != 0U) ? 1 : -1;
}

static int ns800_getc(struct rt_serial_device *serial)
{
    struct ns800_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ns800_uart, serial);

    if (UART_isDataAvailable(uart->handle.Instance))
    {
        return (int)UART_readChar(uart->handle.Instance);
    }

    return -1;
}

static void uart_isr(struct rt_serial_device *serial)
{
    struct ns800_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ns800_uart, serial);

    if (UART_getStatusFlag(uart->handle.Instance, UART_RX_OVERRUN) ||
        UART_getStatusFlag(uart->handle.Instance, UART_NOISE_DETECT) ||
        UART_getStatusFlag(uart->handle.Instance, UART_FRAME_ERR) ||
        UART_getStatusFlag(uart->handle.Instance, UART_PARITY_ERR))
    {
        ns800_uart_clear_errors(uart->handle.Instance);
    }

    if (UART_getStatusFlag(uart->handle.Instance, UART_RX_DATA_REG_FULL))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else if (UART_getStatusFlag(uart->handle.Instance, UART_TX_COMPLETE))
    {
        UART_disableInterrupt(uart->handle.Instance, UART_INT_TX_COMPLETE);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }
}

#ifdef BSP_USING_UART1
void UART1_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uart_obj[UART1_INDEX].serial);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART2
void UART2_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uart_obj[UART2_INDEX].serial);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART3
void UART3_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uart_obj[UART3_INDEX].serial);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART4
void UART4_IRQHandler(void)
{
    rt_interrupt_enter();
    uart_isr(&uart_obj[UART4_INDEX].serial);
    rt_interrupt_leave();
}
#endif

static void ns800_uart_fill_default_config(struct serial_configure *config,
                                           const struct ns800_uart_config *hw)
{
    RT_ASSERT(config != RT_NULL);
    RT_ASSERT(hw != RT_NULL);

    *config = (struct serial_configure)RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_SERIAL_V2
    config->rx_bufsz = hw->rx_bufsz;
    config->tx_bufsz = hw->tx_bufsz;
#else
    config->bufsz = hw->rx_bufsz;
#endif
}

static const struct rt_uart_ops ns800_uart_ops =
{
    .configure = ns800_configure,
    .control = ns800_control,
    .putc = ns800_putc,
    .getc = ns800_getc,
};

int rt_hw_uart_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t i;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops = &ns800_uart_ops;
        ns800_uart_fill_default_config(&uart_obj[i].serial.config, uart_obj[i].config);
        uart_obj[i].tx_block_timeout = uart_obj[i].config->tx_block_timeout;

        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR |
                                       RT_DEVICE_FLAG_INT_RX |
                                       RT_DEVICE_FLAG_INT_TX,
                                       RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */

