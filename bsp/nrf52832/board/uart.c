#include "board.h"
#include "uart.h"

#include "nrf_drv_common.h"
#include "nrf_drv_uart.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"

#include <rtdevice.h>

static struct rt_serial_device _serial0_0;
#if USE_UART0_1
static struct rt_serial_device _serial0_1;
#endif

typedef struct
{
    struct rt_serial_device *serial;
    nrf_drv_uart_t uart;
    uint32_t rx_pin;
    uint32_t tx_pin;
} UART_CFG_T;

UART_CFG_T uart0 = {
    .uart = NRF_DRV_UART_INSTANCE(0),
#ifdef RT_USING_CONSOLE
    .rx_pin = 8,
    .tx_pin = 6
#else
    .rx_pin = 19,
    .tx_pin = 20
#endif
};

#if USE_UART0_1
UART_CFG_T uart1 = {
    .uart = NRF_DRV_UART_INSTANCE(0),
    .rx_pin = 3,
    .tx_pin = 4
};
#endif

UART_CFG_T *working_cfg = RT_NULL;

void UART0_IRQHandler(void)
{
    if (nrf_uart_int_enable_check(NRF_UART0, NRF_UART_INT_MASK_ERROR)
        && nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_ERROR))
    {
        nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);
    }

    if (nrf_uart_int_enable_check(NRF_UART0, NRF_UART_INT_MASK_RXDRDY)
        && nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXDRDY))
    {
        rt_hw_serial_isr(working_cfg->serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (nrf_uart_int_enable_check(NRF_UART0, NRF_UART_INT_MASK_TXDRDY)
        && nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_TXDRDY))
    {
        rt_hw_serial_isr(working_cfg->serial, RT_SERIAL_EVENT_TX_DONE);
    }

    if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXTO))
    {
        rt_hw_serial_isr(working_cfg->serial, RT_SERIAL_EVENT_RX_TIMEOUT);
    }
}

static rt_err_t _uart_cfg(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    nrf_drv_uart_config_t config = NRF_DRV_UART_DEFAULT_CONFIG;
    UART_CFG_T *instance = &uart0;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (UART_CFG_T*)serial->parent.user_data;
    }

    nrf_uart_disable(instance->uart.reg.p_uart);

    switch (cfg->baud_rate)
    {
    case 115200:
        config.baudrate = NRF_UART_BAUDRATE_115200;
        break;

    case 9600:
        config.baudrate = NRF_UART_BAUDRATE_9600;
        break;

    default:
        config.baudrate = NRF_UART_BAUDRATE_115200;
        break;
    }

    if (cfg->parity == PARITY_NONE)
    {
        config.parity = NRF_UART_PARITY_EXCLUDED;
    }
    else
    {
        config.parity = NRF_UART_PARITY_INCLUDED;
    }

    config.hwfc = NRF_UART_HWFC_DISABLED;
    config.interrupt_priority = APP_IRQ_PRIORITY_LOWEST;
    config.pselcts = 0;
    config.pselrts = 0;
    config.pselrxd = instance->rx_pin;
    config.pseltxd = instance->tx_pin;

    nrf_gpio_pin_set(config.pseltxd);
    nrf_gpio_cfg_output(config.pseltxd);
    nrf_gpio_pin_clear(config.pseltxd);
    nrf_gpio_cfg_input(config.pselrxd, NRF_GPIO_PIN_NOPULL);
    nrf_uart_baudrate_set(instance->uart.reg.p_uart, config.baudrate);
    nrf_uart_configure(instance->uart.reg.p_uart, config.parity, config.hwfc);
    nrf_uart_txrx_pins_set(instance->uart.reg.p_uart, config.pseltxd, config.pselrxd);

    if (config.hwfc == NRF_UART_HWFC_ENABLED)
    {
        nrf_uart_hwfc_pins_set(instance->uart.reg.p_uart, config.pselrts, config.pselcts);
    }

    nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_TXDRDY);
    nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_RXDRDY);
    nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_RXTO);
    nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_ERROR);

    nrf_uart_int_enable(instance->uart.reg.p_uart, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_RXTO | NRF_UART_INT_MASK_ERROR);
    nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *)instance->uart.reg.p_uart), config.interrupt_priority);
    nrf_uart_enable(instance->uart.reg.p_uart);
    // nrf_uart_task_trigger(instance->uart.reg.p_uart, NRF_UART_TASK_STARTRX);
    working_cfg = instance;
    return RT_EOK;
}

static rt_err_t _uart_ctrl(struct rt_serial_device *serial, int cmd, void *arg)
{
    UART_CFG_T *instance = working_cfg;

    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (UART_CFG_T*)serial->parent.user_data;
    }

    switch (cmd)
    {
        /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        nrf_uart_task_trigger(instance->uart.reg.p_uart, NRF_UART_TASK_STOPRX);
        nrf_uart_int_disable(instance->uart.reg.p_uart, NRF_UART_INT_MASK_RXDRDY
                                                | NRF_UART_INT_MASK_RXTO
                                                | NRF_UART_INT_MASK_ERROR);
        nrf_drv_common_irq_disable(nrf_drv_get_IRQn((void *)instance->uart.reg.p_uart));
        break;

        /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_RXDRDY);
        nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_RXTO);
        nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_ERROR);
        /* Enable RX interrupt. */
        nrf_uart_int_enable(instance->uart.reg.p_uart, NRF_UART_INT_MASK_RXDRDY
                                                | NRF_UART_INT_MASK_RXTO
                                                | NRF_UART_INT_MASK_ERROR);
        nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *)instance->uart.reg.p_uart), APP_IRQ_PRIORITY_LOWEST);
        nrf_uart_task_trigger(instance->uart.reg.p_uart, NRF_UART_TASK_STARTRX);
        break;

    case RT_DEVICE_CTRL_CUSTOM:
        if ((rt_uint32_t)(arg) == UART_CONFIG_BAUD_RATE_9600)
        {
            instance->serial->config.baud_rate = 9600;
            nrf_uart_baudrate_set(instance->uart.reg.p_uart, NRF_UART_BAUDRATE_9600);
        }
        else if ((rt_uint32_t)(arg) == UART_CONFIG_BAUD_RATE_115200)
        {
            instance->serial->config.baud_rate = 115200;
            nrf_uart_baudrate_set(instance->uart.reg.p_uart, NRF_UART_BAUDRATE_115200);
        }

        // _uart_cfg(instance->serial, &(instance->serial->config));
        // nrf_uart_task_trigger(instance->uart.reg.p_uart, NRF_UART_TASK_STARTRX);
        break;

    case RT_DEVICE_CTRL_PIN:
        if (working_cfg != instance)
        {
            _uart_cfg(instance->serial, &(instance->serial->config));
        }
        break;

    case RT_DEVICE_POWERSAVE:
        nrf_uart_disable(instance->uart.reg.p_uart);
        nrf_uart_txrx_pins_disconnect(instance->uart.reg.p_uart);
        nrf_gpio_pin_clear(instance->rx_pin);
        nrf_gpio_cfg_output(instance->rx_pin);
        nrf_gpio_pin_clear(instance->tx_pin);
        nrf_gpio_cfg_output(instance->tx_pin);
        break;

    case RT_DEVICE_WAKEUP:
        _uart_cfg(instance->serial, &(instance->serial->config));
        break;

    default:
        return RT_ERROR;
    }

    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    UART_CFG_T *instance = working_cfg;

    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (UART_CFG_T*)serial->parent.user_data;
    }

    nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_TXDRDY);
    nrf_uart_task_trigger(instance->uart.reg.p_uart, NRF_UART_TASK_STARTTX);
    nrf_uart_txd_set(instance->uart.reg.p_uart, (uint8_t)c);
    while (!nrf_uart_event_check(instance->uart.reg.p_uart, NRF_UART_EVENT_TXDRDY))
    {
    }

    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    UART_CFG_T *instance = working_cfg;

    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (UART_CFG_T*)serial->parent.user_data;
    }

    if (nrf_uart_event_check(instance->uart.reg.p_uart, NRF_UART_EVENT_RXDRDY))
    {
        nrf_uart_event_clear(instance->uart.reg.p_uart, NRF_UART_EVENT_RXDRDY);
        ch = (int)(nrf_uart_rxd_get(instance->uart.reg.p_uart));
    }

    return ch;
}

static struct rt_uart_ops _uart_ops = {
    _uart_cfg,
    _uart_ctrl,
    _uart_putc,
    _uart_getc
};

void rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    config.bufsz = RT_SERIAL_RB_BUFSZ;
    _serial0_0.config = config;
    _serial0_0.ops = &_uart_ops;
    uart0.serial = &_serial0_0;

    rt_hw_serial_register(&_serial0_0, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &uart0);

#if USE_UART0_1
    config.bufsz = UART0_RB_SIZE;
    _serial0_1.config = config;
    _serial0_1.ops = &_uart_ops;
    uart1.serial = &_serial0_1;
    rt_hw_serial_register(&_serial0_1, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &uart1);
#endif
}

