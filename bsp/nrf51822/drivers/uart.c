/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "uart.h"

#include <nrf_gpio.h>

#define UART_RX_BUFSZ 512
rt_uint8_t rx_buffer[UART_RX_BUFSZ];

struct nrf51822_uart
{
    struct rt_device parent;
    struct rt_ringbuffer rx_rb;
} uart_device;

void UART0_IRQHandler(void)
{
    rt_ubase_t level;
    struct nrf51822_uart* uart = &uart_device;

    level = rt_hw_interrupt_disable();

    // Wait for RXD data to be received
    while (NRF_UART0->EVENTS_RXDRDY != 1) ;
    NRF_UART0->EVENTS_RXDRDY = 0;

    rt_hw_interrupt_enable(level);
    /* [Handling the data received over UART] */
    rt_ringbuffer_putchar_force(&(uart->rx_rb), (rt_uint8_t)NRF_UART0->RXD);

    /* invoke callback */
    if(uart->parent.rx_indicate != RT_NULL)
    {
        uart->parent.rx_indicate(&uart->parent, rt_ringbuffer_data_len(&uart->rx_rb));
    }
}


static rt_err_t rt_uart_init (rt_device_t dev)
{
    /* UART Initialization and Enable */
    /** @snippet [Configure UART RX and TX pin] */
    nrf_gpio_cfg_output(TX_PIN_NUMBER);
    nrf_gpio_cfg_input(RX_PIN_NUMBER, NRF_GPIO_PIN_NOPULL);

    NRF_UART0->PSELTXD = TX_PIN_NUMBER;
    NRF_UART0->PSELRXD = RX_PIN_NUMBER;
    /** @snippet [Configure UART RX and TX pin] */
    if (HWFC)
    {
        nrf_gpio_cfg_output(RTS_PIN_NUMBER);
        nrf_gpio_cfg_input(CTS_PIN_NUMBER, NRF_GPIO_PIN_NOPULL);
        NRF_UART0->PSELCTS = CTS_PIN_NUMBER;
        NRF_UART0->PSELRTS = RTS_PIN_NUMBER;
        NRF_UART0->CONFIG  = (UART_CONFIG_HWFC_Enabled << UART_CONFIG_HWFC_Pos);
    }

    NRF_UART0->BAUDRATE      = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);
    NRF_UART0->ENABLE        = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
    NRF_UART0->TASKS_STARTTX = 1;
    NRF_UART0->TASKS_STARTRX = 1;
    NRF_UART0->EVENTS_RXDRDY = 0;

    NRF_UART0->INTENSET = (UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos);

    NVIC_EnableIRQ(UART0_IRQn);

    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable the UART Interrupt */
        NVIC_EnableIRQ(UART0_IRQn);
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Disable the UART Interrupt */
        NVIC_DisableIRQ(UART0_IRQn);
    }

    return RT_EOK;
}

static rt_size_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_size_t length;
    struct nrf51822_uart *uart = (struct nrf51822_uart*)dev;
    /* interrupt receive */
    rt_base_t level;

    RT_ASSERT(uart != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    length = rt_ringbuffer_get(&(uart->rx_rb), buffer, size);
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return length;
}

static rt_size_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    char *ptr;
    ptr = (char*) buffer;

    if (dev->open_flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                NRF_UART0->TXD = (uint8_t)'\r';

                // Wait for TXD data to be sent.
                while (NRF_UART0->EVENTS_TXDRDY != 1) ;

                NRF_UART0->EVENTS_TXDRDY = 0;
            }

            NRF_UART0->TXD = (uint8_t)(*ptr);

            // Wait for TXD data to be sent.
            while (NRF_UART0->EVENTS_TXDRDY != 1) ;

            NRF_UART0->EVENTS_TXDRDY = 0;

            ptr ++;
            size --;
        }
    }
    else
    {
        while ( size != 0 )
        {
            NRF_UART0->TXD = (uint8_t)(*ptr);

            // Wait for TXD data to be sent.
            while (NRF_UART0->EVENTS_TXDRDY != 1) ;

            NRF_UART0->EVENTS_TXDRDY = 0;

            ptr++;
            size--;
        }
    }

    return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_hw_uart_init(void)
{
    struct nrf51822_uart* uart;

    /* get uart device */
    uart = &uart_device;

    /* device initialization */
    uart->parent.type = RT_Device_Class_Char;
    rt_ringbuffer_init(&(uart->rx_rb), rx_buffer, sizeof(rx_buffer));

    /* device interface */
    uart->parent.init       = rt_uart_init;
    uart->parent.open       = rt_uart_open;
    uart->parent.close      = rt_uart_close;
    uart->parent.read       = rt_uart_read;
    uart->parent.write      = rt_uart_write;
    uart->parent.control    = RT_NULL;
    uart->parent.user_data  = RT_NULL;

    rt_device_register(&uart->parent, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
}
