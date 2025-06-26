/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-27     WangShun     the first version
 */

#include "board.h"
#include "rtthread.h"
#include <rtdevice.h>
#include <string.h>
#include <drv_usart.h>

#ifdef RT_USING_SERIAL
    #define DRV_DEBUG
    #define LOG_TAG              "drv.uart"

    #ifdef DRV_DEBUG
        #define DBG_LVL          DBG_LOG
    #else
        #define DBG_LVL          DBG_INFO
    #endif /* DRV_DEBUG */

    #include <rtdbg.h>

    #if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) \
        && !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
        #error "Please define at least one BSP_USING_UARTx"
        /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
    #endif

static void xuantie_uart0_rx_isr(csi_uart_t *uart_handler, csi_uart_event_t event, void *arg);

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
};

struct xuantie_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    {
        "uart0",
        0,
        xuantie_uart0_rx_isr
    }
#endif
};

struct xuantie_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t xuantie_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct xuantie_uart *uart = (struct xuantie_uart *)serial->parent.user_data;
    csi_error_t ret;

    ret = csi_uart_baud(&uart->uart, cfg->baud_rate);
    if (ret != CSI_OK)
    {
        return -RT_ERROR;
    }

    csi_uart_data_bits_t data_bits;
    csi_uart_parity_t parity;
    csi_uart_stop_bits_t stop_bits;

    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        data_bits = UART_DATA_BITS_5;
        break;
    case DATA_BITS_6:
        data_bits = UART_DATA_BITS_6;
        break;
    case DATA_BITS_7:
        data_bits = UART_DATA_BITS_7;
        break;
    case DATA_BITS_8:
        data_bits = UART_DATA_BITS_8;
        break;
    case DATA_BITS_9:
        data_bits = UART_DATA_BITS_9;
        break;
    default:
        data_bits = UART_DATA_BITS_8;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        parity = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        parity = UART_PARITY_EVEN;
        break;
    default:
        parity = UART_PARITY_NONE;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        stop_bits = UART_STOP_BITS_1;
        break;
    case STOP_BITS_2:
        stop_bits = UART_STOP_BITS_2;
        break;
    default:
        stop_bits = UART_STOP_BITS_1;
        break;
    }

    ret = csi_uart_format(&uart->uart, data_bits, parity, stop_bits);
    if (ret != CSI_OK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t xuantie_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CONFIG:
        return xuantie_configure(serial, (struct serial_configure *)arg);
    default:
        return -RT_ERROR;
    }
}

static int xuantie_putc(struct rt_serial_device *serial, char c)
{
    struct xuantie_uart *uart = (struct xuantie_uart *)serial->parent.user_data;
    int32_t ret;

    ret = csi_uart_send(&uart->uart, &c, 1, 50);
    if (ret == 1)
        return RT_EOK;

    return -RT_ERROR;
}

static int xuantie_getc(struct rt_serial_device *serial)
{
    int c = -1;
    struct xuantie_uart *uart = (struct xuantie_uart *)serial->parent.user_data;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE((&uart->uart));

    csi_uart_receive(&uart->uart, &c, 1, 0x5);
    dw_uart_enable_recv_irq(uart_base);
    return c;
}

static const struct rt_uart_ops xuantie_uart_ops =
{
    xuantie_configure,
    xuantie_control,
    xuantie_putc,
    xuantie_getc,
    RT_NULL,
};

static void xuantie_uart0_rx_isr(csi_uart_t *uart_handler, csi_uart_event_t event, void *arg)
{
    rt_interrupt_enter();
    rt_hw_serial_isr(&uart_obj[UART0_INDEX].serial, RT_SERIAL_EVENT_RX_IND);
    rt_interrupt_leave();
}

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct xuantie_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (int i = 0; i < obj_num; i++)
    {
        /* Initialize YOC UART */
        result = csi_uart_init(&uart_obj[i].uart, 0);
        if (result != CSI_OK)
        {
            LOG_E("Failed to initialize UART %d", uart_obj[i].config->idx);
            return -RT_ERROR;
        }

        /* Init UART object */
        uart_obj[i].config        = &uart_config[i];
        uart_obj[i].serial.ops    = &xuantie_uart_ops;
        uart_obj[i].serial.config = config;

        csi_uart_attach_callback(&uart_obj[i].uart, uart_obj[i].config->xuantie_uart_rx_isr, NULL);

        /* Register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                       &uart_obj[i]);
        if (result != RT_EOK)
        {
            LOG_E("Failed to register UART device %s", uart_obj[i].config->name);
            csi_uart_uninit(&uart_obj[i].uart);
            return -RT_ERROR;
        }
    }
    return result;
}

#endif /* RT_USING_SERIAL */
