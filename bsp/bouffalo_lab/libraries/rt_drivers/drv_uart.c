/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
* 2022/12/25     flyingcys    first version
*/

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#define DBG_TAG "DRV.UART"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#define UART_DEFAULT_BAUDRATE 2000000

// uart0
#ifdef UART0_TX_USING_GPIO14
#define UART0_GPIO_TX           GPIO_PIN_14
#elif defined(UART0_TX_USING_GPIO16)
#define UART0_GPIO_TX           GPIO_PIN_16
#elif defined(UART0_TX_USING_GPIO21)
#define UART0_GPIO_TX           GPIO_PIN_21
#endif

#ifdef UART0_RX_USING_GPIO7
#define UART0_GPIO_RX           GPIO_PIN_7
#elif defined(UART0_RX_USING_GPIO15)
#define UART0_GPIO_RX           GPIO_PIN_15
#elif defined(UART0_RX_USING_GPIO22)
#define UART0_GPIO_RX           GPIO_PIN_22
#elif defined(UART0_RX_USING_GPIO23)
#define UART0_GPIO_RX           GPIO_PIN_23
#endif

// uart1
#ifdef UART1_TX_USING_GPIO4
#define UART1_GPIO_TX           GPIO_PIN_4
#elif defined(UART1_TX_USING_GPIO16)
#define UART1_GPIO_TX           GPIO_PIN_16
#elif defined(UART1_TX_USING_GPIO18)
#define UART1_GPIO_TX           GPIO_PIN_18
#elif defined(UART1_TX_USING_GPIO26)
#define UART1_GPIO_TX           GPIO_PIN_26
#endif

#ifdef UART1_RX_USING_GPIO3
#define UART1_GPIO_RX           GPIO_PIN_3
#elif defined(UART1_RX_USING_GPIO5)
#define UART1_GPIO_RX           GPIO_PIN_5
#elif defined(UART1_RX_USING_GPIO17)
#define UART1_GPIO_RX           GPIO_PIN_17
#elif defined(UART1_RX_USING_GPIO19)
#define UART1_GPIO_RX           GPIO_PIN_19
#elif defined(UART1_RX_USING_GPIO27)
#define UART1_GPIO_RX           GPIO_PIN_27
#endif

static struct bflb_device_s    *gpio;

struct device_uart
{
    struct rt_serial_device serial;
    struct bflb_device_s    *bflb_device;
};

static void _uart_rx_irq(int irq, void *arg)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)arg;
    RT_ASSERT(serial != RT_NULL);

    struct device_uart *uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(uart->bflb_device != RT_NULL);

    uint32_t intstatus = bflb_uart_get_intstatus(uart->bflb_device);
    if (intstatus & UART_INTSTS_RX_FIFO)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (intstatus & UART_INTSTS_RTO)
    {
        bflb_uart_int_clear(uart->bflb_device, UART_INTCLR_RTO);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *serial_cfg)
{
    struct device_uart *uart = RT_NULL;
    struct bflb_uart_config_s uart_cfg;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(serial_cfg != RT_NULL);

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(uart->bflb_device != RT_NULL);

    uart_cfg.baudrate = UART_DEFAULT_BAUDRATE;
    uart_cfg.data_bits = UART_DATA_BITS_8;
    uart_cfg.stop_bits = UART_STOP_BITS_1;
    uart_cfg.parity = UART_PARITY_NONE;
    uart_cfg.flow_ctrl = 0;
    uart_cfg.tx_fifo_threshold = 7;
    uart_cfg.rx_fifo_threshold = 7;

    uart_cfg.baudrate = serial_cfg->baud_rate;

    switch (serial_cfg->data_bits)
    {
        case DATA_BITS_5:
            uart_cfg.data_bits = UART_DATA_BITS_5;
            break;

        case DATA_BITS_6:
            uart_cfg.data_bits = UART_DATA_BITS_6;
            break;

        case DATA_BITS_7:
            uart_cfg.data_bits = UART_DATA_BITS_7;
            break;

        case DATA_BITS_8:
            uart_cfg.data_bits = UART_DATA_BITS_8;
            break;

        default:
            uart_cfg.data_bits = UART_DATA_BITS_8;
            break;
    }

    switch (serial_cfg->stop_bits)
    {
        case STOP_BITS_1:
            uart_cfg.stop_bits = UART_STOP_BITS_1;
            break;

        case STOP_BITS_2:
            uart_cfg.stop_bits = UART_STOP_BITS_2;
            break;

        default:
            uart_cfg.stop_bits = UART_STOP_BITS_1;
            break;
    }

    switch (serial_cfg->parity)
    {
        case PARITY_NONE:
            uart_cfg.parity = UART_PARITY_NONE;
            break;

        case PARITY_ODD:
            uart_cfg.parity = UART_PARITY_ODD;
            break;

        case PARITY_EVEN:
            uart_cfg.parity = UART_PARITY_EVEN;
            break;

        default:
            uart_cfg.parity = UART_PARITY_NONE;
            break;
    }

    bflb_uart_init(uart->bflb_device, &uart_cfg);

    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(uart->bflb_device != RT_NULL);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        bflb_irq_disable(uart->bflb_device->irq_num);
        bflb_irq_attach(uart->bflb_device->irq_num, NULL, NULL);
        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        bflb_uart_rxint_mask(uart->bflb_device, false);
        bflb_irq_attach(uart->bflb_device->irq_num, _uart_rx_irq, serial);
        bflb_irq_enable(uart->bflb_device->irq_num);
        break;
    }
    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(uart->bflb_device != RT_NULL);

    bflb_uart_putchar(uart->bflb_device, c);

    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(uart->bflb_device != RT_NULL);

    ch = bflb_uart_getchar(uart->bflb_device);

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    .configure = _uart_configure,
    .control = _uart_control,
    .putc = _uart_putc,
    .getc = _uart_getc,
    .dma_transmit = RT_NULL
};

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    rt_err_t result = 0;

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    struct rt_serial_device *serial;
    struct device_uart      *uart;

    gpio = bflb_device_get_by_name("gpio");

#ifdef BSP_USING_UART0
    static struct device_uart bl_uart0;

    serial  = &bl_uart0.serial;
    uart    = &bl_uart0;

    serial->ops              = &_uart_ops;
    serial->config           = config;
    serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

    uart->bflb_device = bflb_device_get_by_name("uart0");

    bflb_gpio_uart_init(gpio, UART0_GPIO_TX, GPIO_UART_FUNC_UART0_TX);
    bflb_gpio_uart_init(gpio, UART0_GPIO_RX, GPIO_UART_FUNC_UART0_RX);

    /* register USART device */
    result = rt_hw_serial_register(serial,
                                    "uart0",
                                    RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                    uart);
    RT_ASSERT(result == RT_EOK);
#endif

#ifdef BSP_USING_UART1
    static struct device_uart bl_uart1;

    serial  = &bl_uart1.serial;
    uart    = &bl_uart1;

    serial->ops              = &_uart_ops;
    serial->config           = config;
    serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

    uart->bflb_device = bflb_device_get_by_name("uart1");
    bflb_gpio_uart_init(gpio, UART1_GPIO_TX, GPIO_UART_FUNC_UART1_TX);
    bflb_gpio_uart_init(gpio, UART1_GPIO_RX, GPIO_UART_FUNC_UART1_RX);

    /* register USART device */
    result = rt_hw_serial_register(serial,
                                    "uart1",
                                    RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                    uart);
    RT_ASSERT(result == RT_EOK);
#endif
    return 0;
}
