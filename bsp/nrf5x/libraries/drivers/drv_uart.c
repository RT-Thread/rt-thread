#include <rtdevice.h>
#include <nrfx_uart.h>
#include "drv_uart.h"

static struct rt_serial_device _serial0_0;
static void uart_event_hander(nrfx_uart_event_t const *p_event,void *p_context);

typedef struct
{
    struct rt_serial_device *serial;
    nrfx_uart_t uart;
    uint32_t rx_pin;
    uint32_t tx_pin;
    nrfx_uart_event_handler_t event_handler;
} UART_CFG_T;


UART_CFG_T uart0 = {
    .uart = NRFX_UART_INSTANCE(0),
#ifdef RT_USING_CONSOLE
    .rx_pin = 8,
    .tx_pin = 6,
    .event_handler = uart_event_hander,
#else
    .rx_pin = 19,
    .tx_pin = 20
#endif
};
UART_CFG_T *working_cfg = RT_NULL;

static void uart_event_hander(nrfx_uart_event_t const *p_event,void *p_context)
{
    
    if (p_event->type == NRFX_UART_EVT_RX_DONE)
    {
        rt_hw_serial_isr(working_cfg->serial, RT_SERIAL_EVENT_RX_IND);
    }
    if (p_event->type == NRFX_UART_EVT_TX_DONE)
    {
        
    }
}

static rt_err_t _uart_cfg(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    nrfx_uart_config_t config = NRFX_UART_DEFAULT_CONFIG(uart0.tx_pin,uart0.rx_pin);
    UART_CFG_T *instance = &uart0;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (UART_CFG_T*)serial->parent.user_data;
    }

    nrfx_uart_uninit(&(instance->uart));

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
        config.hal_cfg.parity = NRF_UART_PARITY_EXCLUDED;
    }
    else
    {
        config.hal_cfg.parity = NRF_UART_PARITY_INCLUDED;
    }

    config.hal_cfg.hwfc = NRF_UART_HWFC_DISABLED;
    config.pselrxd = instance->rx_pin;
    config.pseltxd = instance->tx_pin;

    nrfx_uart_init(&(instance->uart), &config, instance->event_handler);
    
    nrf_uart_int_enable(instance->uart.p_reg, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_RXTO | NRF_UART_INT_MASK_ERROR);
    nrf_uart_int_disable(instance->uart.p_reg, NRF_UART_INT_MASK_TXDRDY);
    
    nrfx_uart_rx_enable(&(instance->uart));
    
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
        break;

        /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        break;

    case RT_DEVICE_CTRL_CUSTOM:
        if ((rt_uint32_t)(arg) == UART_CONFIG_BAUD_RATE_9600)
        {
            instance->serial->config.baud_rate = 9600;
        }
        else if ((rt_uint32_t)(arg) == UART_CONFIG_BAUD_RATE_115200)
        {
            instance->serial->config.baud_rate = 115200;
        }
        _uart_cfg(instance->serial, &(instance->serial->config));
        break;

    case RT_DEVICE_CTRL_PIN:
        if (working_cfg != instance)
        {
            _uart_cfg(instance->serial, &(instance->serial->config));
        }
        break;

    case RT_DEVICE_POWERSAVE:
        nrfx_uart_uninit(&(instance->uart));
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
    int rtn = 1;
    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (UART_CFG_T*)serial->parent.user_data;
    }

    nrf_uart_event_clear(instance->uart.p_reg, NRF_UART_EVENT_TXDRDY);
    nrf_uart_task_trigger(instance->uart.p_reg, NRF_UART_TASK_STARTTX);
    nrf_uart_txd_set(instance->uart.p_reg, (uint8_t)c);
    while (!nrf_uart_event_check(instance->uart.p_reg, NRF_UART_EVENT_TXDRDY))
    {
        //wait for TXD send
    }    
    return rtn;
}

/* 
    @note: this function is invaild ,the cause of the problem is [nrfx_uart.c - line 340] 
*/
static int _uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    UART_CFG_T *instance = working_cfg;

    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (UART_CFG_T*)serial->parent.user_data;
    }
    
    ch = (int)(nrf_uart_rxd_get(instance->uart.p_reg));
    
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

    rt_hw_serial_register(&_serial0_0, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,  &uart0);
}

