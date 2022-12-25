/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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


struct device_uart
{
    struct rt_serial_device serial;
    uint8_t port;
    uint8_t tx_pin;
    uint8_t rx_pin;
};

static void _uart_rx_irq(void *param)
{
    struct device_uart *uart = (struct device_uart *)param;;

    struct rt_serial_device *serial = &uart->serial;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static int uart_signal_get(uint8_t pin)
{
    //TODO no magic number is allowed here
    if (pin >= 12 && pin <=23) {
        return (pin + 6) % 12;
    } else if (pin >= 36 && pin <=45) {
        return (pin + 6) % 12;
    }
    return (pin % 12);
}

static int uart_func_get(uint8_t id, GLB_UART_SIG_FUN_Type uartfunc)
{
    switch (id) {
        case 0:
            return uartfunc;
        case 1:
            return (GLB_UART_SIG_FUN_UART1_RTS - GLB_UART_SIG_FUN_UART0_RTS) * 1 + uartfunc;
        case 2:
            return (GLB_UART_SIG_FUN_UART1_RTS - GLB_UART_SIG_FUN_UART0_RTS) * 1 + uartfunc;
        default:
            /*empty here*/
            //TODO should assert here?
            return uartfunc;
    }
}
static void uart_gpio_demo(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin)
{
    GLB_GPIO_Cfg_Type gpio_cfg;
    uint8_t uart_func, uart_sig;

    //FIXME SWAP set is NOT put here
    GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, 1);
    GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45, 1);

    //common GPIO cfg
    gpio_cfg.drive = 0;
    gpio_cfg.smtCtrl = 1;
    gpio_cfg.gpioMode = GPIO_MODE_AF;
    gpio_cfg.pullType = GPIO_PULL_UP;
    gpio_cfg.gpioFun = GPIO_FUN_UART;

    //cfg for UART Tx
    gpio_cfg.gpioPin = GLB_GPIO_PIN_0 + tx_pin;
    uart_func = uart_func_get(id, GLB_UART_SIG_FUN_UART0_TXD);
    uart_sig = uart_signal_get(gpio_cfg.gpioPin);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig, (GLB_UART_SIG_FUN_Type)uart_func);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_func, (GLB_UART_SIG_FUN_Type)uart_sig);
    GLB_GPIO_Init(&gpio_cfg);

    //cfg for UART Rx
    gpio_cfg.gpioPin = GLB_GPIO_PIN_0 + rx_pin;
    uart_func = uart_func_get(id, GLB_UART_SIG_FUN_UART0_RXD);
    uart_sig = uart_signal_get(gpio_cfg.gpioPin);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig, (GLB_UART_SIG_FUN_Type)uart_func);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_func, (GLB_UART_SIG_FUN_Type)uart_sig);
    GLB_GPIO_Init(&gpio_cfg);

    //Enable UART clock
    GLB_Set_UART_CLK(1, 0, 0);
}

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct device_uart *uart;
    uint8_t id;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    id = uart->port;

    UART_CFG_Type uart_cfg = {
      80*1000*1000,     /*UART clock from XTAL*/
      2000000,          /* baudrate  */
      UART_DATABITS_8,  /* data bits  */
      UART_STOPBITS_1,  /* stop bits */
      UART_PARITY_NONE, /* parity  */
      DISABLE,          /* Disable auto flow control */
      DISABLE,          /* Disable rx input de-glitch function */
      DISABLE,          /* Disable RTS output SW control mode */
      DISABLE,          /* Disable tx output SW control mode */
      DISABLE,          /* Disable tx lin mode */
      DISABLE,          /* Disable rx lin mode */
      0,                /* Tx break bit count for lin mode */
      UART_LSB_FIRST,   /* UART each data byte is send out LSB-first */
    };

    UART_FifoCfg_Type fifoCfg = {
      16,      /* TX FIFO threshold */
      16,      /* RX FIFO threshold */
      DISABLE, /* Disable tx dma req/ack interface */
      DISABLE  /* Disable rx dma req/ack interface */
    };

    /* init debug uart gpio first */
    uart_gpio_demo(id, uart->tx_pin, uart->rx_pin, 0xff, 0xff);

    /* disable all interrupt */
    UART_IntMask(id, UART_INT_ALL, MASK);

    /* disable uart before config */
    UART_Disable(id, UART_TXRX);

    uart_cfg.baudRate = cfg->baud_rate;

    switch (cfg->data_bits)
    {
        case DATA_BITS_5:
            uart_cfg.dataBits = UART_DATABITS_5;
            break;

        case DATA_BITS_6:
            uart_cfg.dataBits = UART_DATABITS_6;
            break;

        case DATA_BITS_7:
            uart_cfg.dataBits = UART_DATABITS_7;
            break;

        case DATA_BITS_8:
            uart_cfg.dataBits = UART_DATABITS_8;
            break;

        default:
            uart_cfg.dataBits = UART_DATABITS_8;
            break;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_1:
            uart_cfg.stopBits = UART_STOPBITS_1;
            break;
        
        case STOP_BITS_2:
            uart_cfg.stopBits = UART_STOPBITS_2;
            break;

        default:
            uart_cfg.stopBits = UART_STOPBITS_1;
            break;
    }

    switch (cfg->parity)
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

    /* uart init with configuration */
    UART_Init(id, &uart_cfg);

    /* UART fifo configuration */
    UART_FifoConfig(id, &fifoCfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);

    /* Set rx time-out value */
    UART_SetRxTimeoutValue(id, UART_DEFAULT_RTO_TIMEOUT);

    /* enable uart */
    UART_AutoBaudDetection(id, 0);
    UART_Enable(id, UART_TXRX);    

    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
    	bl_uart_int_disable(uart->port);
        bl_uart_int_rx_notify_unregister(uart->port, _uart_rx_irq, uart);
        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        bl_uart_int_rx_notify_register(uart->port, _uart_rx_irq, uart);
        bl_uart_int_enable(uart->port);
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

    bl_uart_data_send(uart->port, c);

    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    ch = bl_uart_data_recv(uart->port);

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

#ifdef BSP_USING_UART0
    static struct device_uart uart0;

    serial  = &uart0.serial;
    uart    = &uart0;

    serial->ops              = &_uart_ops;
    serial->config           = config;
    serial->config.baud_rate = 2000000;

    uart->port = 0;
    uart->tx_pin = BSP_UART0_TXD_PIN;
    uart->rx_pin = BSP_UART0_RXD_PIN;

    /* register USART device */
    result = rt_hw_serial_register(serial,
                                    "uart0",
                                    RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, 
                                    uart);
    RT_ASSERT(result == RT_EOK);
#endif

    return 0;
}