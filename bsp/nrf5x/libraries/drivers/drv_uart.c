/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-28     xckhmf       Modify for <nrfx>
 *
 */
#include <rtdevice.h>
#include <nrfx_uart.h>
#include "drv_uart.h"

#ifdef BSP_USING_UART

typedef struct
{
    struct rt_serial_device *serial;
    nrfx_uart_t uart;
    uint8_t rx_byte;
    uint16_t rx_length;
    uint32_t rx_pin;
    uint32_t tx_pin;
    nrfx_uart_event_handler_t event_handler;
} drv_uart_cfg_t;

#ifdef BSP_USING_UART0
static struct rt_serial_device _serial_0;
static void uart0_event_hander(nrfx_uart_event_t const *p_event,void *p_context);
drv_uart_cfg_t m_uart0_cfg = {
    .uart = NRFX_UART_INSTANCE(0),
    .rx_byte = 0,
    .rx_length = 0,
    .rx_pin = BSP_UART0_RX_PIN,
    .tx_pin = BSP_UART0_TX_PIN,
    .event_handler = uart0_event_hander
};
#endif  /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    #error <nrfx_uart> not support UART1. Use UART0 instead.
#endif  /* BSP_USING_UART1 */

#ifdef BSP_USING_UART0
static void uart0_event_hander(nrfx_uart_event_t const *p_event,void *p_context)
{   
    if (p_event->type == NRFX_UART_EVT_RX_DONE)
    {
        if(p_event->data.rxtx.bytes == 1)
        {
            m_uart0_cfg.rx_length = p_event->data.rxtx.bytes;
            
            /* rx_byte equal p_data  */
            //m_uart0_cfg.rx_byte = *(p_event->data.rxtx.p_data); 
            
            rt_hw_serial_isr(m_uart0_cfg.serial, RT_SERIAL_EVENT_RX_IND);
        }
        nrfx_uart_rx(&(m_uart0_cfg.uart),&m_uart0_cfg.rx_byte,1);
    }
    if (p_event->type == NRFX_UART_EVT_TX_DONE)
    {
        /* @TODO:[RT_DEVICE_FLAG_INT_TX]*/
    }
}
#endif  /* BSP_USING_UART0 */

static rt_err_t _uart_cfg(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    nrfx_uart_config_t config = NRFX_UART_DEFAULT_CONFIG(BSP_UART0_TX_PIN,BSP_UART0_RX_PIN);
    drv_uart_cfg_t *instance = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
  
    if (serial->parent.user_data == RT_NULL)
    {
        return -RT_ERROR;
    }
    instance = (drv_uart_cfg_t*)serial->parent.user_data;
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
    nrfx_uart_rx(&(instance->uart),&(instance->rx_byte),1);
    nrf_uart_int_disable(instance->uart.p_reg, NRF_UART_INT_MASK_TXDRDY);
    return RT_EOK;
}

static rt_err_t _uart_ctrl(struct rt_serial_device *serial, int cmd, void *arg)
{
    drv_uart_cfg_t *instance = NULL;
    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data == RT_NULL)
    {
        return -RT_ERROR;
    }
    instance = (drv_uart_cfg_t*)serial->parent.user_data;

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
        _uart_cfg(instance->serial, &(instance->serial->config));
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
RT_WEAK int uart_putc_hook(rt_uint8_t *ch)
{
    return -1;
}
static int _uart_putc(struct rt_serial_device *serial, char c)
{
    drv_uart_cfg_t *instance = NULL;
    int rtn = 1;
    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (drv_uart_cfg_t*)serial->parent.user_data;
    }

    nrf_uart_event_clear(instance->uart.p_reg, NRF_UART_EVENT_TXDRDY);
    nrf_uart_task_trigger(instance->uart.p_reg, NRF_UART_TASK_STARTTX);
    nrf_uart_txd_set(instance->uart.p_reg, (uint8_t)c);
    uart_putc_hook((rt_uint8_t *)&c);
    while (!nrf_uart_event_check(instance->uart.p_reg, NRF_UART_EVENT_TXDRDY))
    {
        //wait for TXD send
    }    
    return rtn;
}

RT_WEAK int uart_getc_hook(rt_uint8_t *ch)
{
    return -1;
};

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    drv_uart_cfg_t *instance = NULL;
    RT_ASSERT(serial != RT_NULL);

    if (serial->parent.user_data != RT_NULL)
    {
        instance = (drv_uart_cfg_t*)serial->parent.user_data;
    }  
    if(instance->rx_length)
    {
        ch = instance->rx_byte;
        instance->rx_length--;
    }

    if (-1 != ch)
    {
        return ch;
    }
    else
    {
        if (-1 == uart_getc_hook((rt_uint8_t *)&ch))
        {
            return -1;
        }
        else
        {
            return ch;
        }
    }
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

#ifdef BSP_USING_UART0
    _serial_0.config = config;
    _serial_0.ops = &_uart_ops;
    m_uart0_cfg.serial = &_serial_0;
    rt_hw_serial_register(&_serial_0, "uart0", \
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,  &m_uart0_cfg);
#endif  /* BSP_USING_UART0 */

}

#endif /* BSP_USING_UART */
