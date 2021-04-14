/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-23     Urey         first implementation
 */

#include <rtthread.h>

#ifdef RT_USING_CONSOLE

#include <rthw.h>
#include <rtdevice.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "board.h"
#include "soc.h"
#include "dw_usart.h"
#include "drv_usart.h"
#include "pin_name.h"
#include "pinmux.h"

#if CONFIG_USART
struct
{
    uint32_t base;
    uint32_t irq;
} const sg_usart_config[CONFIG_USART_NUM] =
{
    { CSKY_UART0_BASE, UART0_IRQn },
    { CSKY_UART1_BASE, UART1_IRQn },
    { CSKY_UART2_BASE, UART2_IRQn },
    { CSKY_UART3_BASE, UART3_IRQn }
};

typedef struct
{
    pin_t    tx;
    pin_t    rx;
    uint16_t cfg_idx;    //idx of sg_usart_config[]
    uint16_t function;
} usart_pin_map_t;
const static usart_pin_map_t s_usart_pin_map[] =
{
    {
        PA0_TXD0_PWM0_XX_SIROUT0,
        PA1_RXD0_PWM1_XX_SIRIN0,
        0,
        0
    },
    {
        PA10_TXD1_PWM1_XX_SIROUT1,
        PA11_RXD1_PWM2_XX_SIRIN1,
        1,
        0
    },
    {
        PA23_TXD2_PWM5_XX_SIROUT2,
        PA22_RXD2_PWM4_XX_SIRIN2,
        2,
        0
    },
    {
        PA26_TXD3_PWMFAULT_XX_SIROUT3,
        PA27_RXD3_PWM0_XX_SIRIN3,
        3,
        0
    }
};

int32_t target_usart_init(pin_t tx, pin_t rx, uint32_t *base, uint32_t *irq)
{
    uint32_t idx;

    for (idx = 0; idx < sizeof(s_usart_pin_map) / sizeof(usart_pin_map_t); idx++)
    {
        if (s_usart_pin_map[idx].tx == tx && s_usart_pin_map[idx].rx == rx)
        {
            *base = sg_usart_config[s_usart_pin_map[idx].cfg_idx].base;
            *irq = sg_usart_config[s_usart_pin_map[idx].cfg_idx].irq;

            /*pinmux*/
            pin_mux(s_usart_pin_map[idx].tx, s_usart_pin_map[idx].function);
            pin_mux(s_usart_pin_map[idx].rx, s_usart_pin_map[idx].function);
            return s_usart_pin_map[idx].cfg_idx;
        }
    }
    return -1;
}
#endif

#ifdef RT_USING_UART1
#define UART_TXD1     PA10_TXD1_PWM1_XX_SIROUT1
#define UART_RXD1     PA11_RXD1_PWM2_XX_SIRIN1

static  usart_handle_t uart1_handle;
static struct rt_serial_device  serial1;
/*
static void usart1_event_cb(uint32_t event, void *cb_arg)
{
    switch (event)
    {
    case USART_EVENT_SEND_COMPLETE:
        rt_hw_serial_isr(&serial1,RT_SERIAL_EVENT_TX_DONE);
        break;

    case USART_EVENT_RECEIVED:
        rt_hw_serial_isr(&serial1,RT_SERIAL_EVENT_RX_IND);
        break;

    default:
        break;
    }
}
*/

__attribute__((isr)) void USART1_IRQHandler(void)
{
    rt_hw_serial_isr(&serial1,RT_SERIAL_EVENT_RX_IND);
}
#endif

/*
 * UART interface
 */
static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    int ret;
    usart_handle_t uart;

    uint32_t bauds;
    usart_mode_e mode;
    usart_parity_e parity;
    usart_stop_bits_e stopbits;
    usart_data_bits_e databits;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* set baudrate parity...*/
    bauds = cfg->baud_rate;
    mode = USART_MODE_ASYNCHRONOUS;

    if (cfg->parity == PARITY_EVEN)
        parity = USART_PARITY_EVEN;
    else if (cfg->parity == PARITY_ODD)
        parity = USART_PARITY_ODD;
    else
        parity = USART_PARITY_NONE;

    stopbits = USART_STOP_BITS_1 ;
    databits = USART_DATA_BITS_8;

    ret = csi_usart_config(uart, SYSTEM_CLOCK, bauds, USART_MODE_ASYNCHRONOUS, parity, stopbits, databits);

    if (ret < 0)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    usart_handle_t uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        dw_usart_clr_int_flag(uart,IER_RDA_INT_ENABLE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* Enable the UART Interrupt */
        dw_usart_set_int_flag(uart,IER_RDA_INT_ENABLE);
        break;
    }

    return (RT_EOK);
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    usart_handle_t uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    dw_usart_putchar(uart,c);

    return (1);
}

static int uart_getc(struct rt_serial_device *serial)
{
    uint8_t ch;
    usart_handle_t uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (usart_handle_t)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    if (!dw_usart_getchar_no_poll(uart, &ch))
    {
        return (int)(ch);
    }
    else
    {
        return -1;
    }
}

const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};


int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART1
    serial1.ops                 = & _uart_ops;
    serial1.config              = config;
    serial1.config.bufsz        = 2048;
    serial1.config.baud_rate    = 115200;

    uart1_handle = csi_usart_initialize(UART_TXD1, UART_RXD1, NULL/*usart1_event_cb*/,
                                        (void *) 0);

    rt_hw_serial_register(&serial1,
                          "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart1_handle);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);
#endif
