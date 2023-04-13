/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2010-03-08     Bernard          The first version for LPC17xx
 * 2010-06-29     lgnq             Modified for V850
*/

#include <rthw.h>
#include <rtthread.h>
#include "io70f3454.h"
#include "uart.h"

#if defined(RT_USING_UART0) && defined(RT_USING_DEVICE)

struct rt_uart_v850
{
    struct rt_device parent;

    /* buffer for reception */
    rt_uint8_t read_index, save_index;
    rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
}uart_device;

void  uarta1_receive_handler(void)
{
    rt_ubase_t level;
    rt_uint8_t c;

    struct rt_uart_v850 *uart = &uart_device;

//  while(ri_u0c1 == 0)
//      ;
    c = (char) UA1RX;

    /* Receive Data Available */
    uart->rx_buffer[uart->save_index] = c;

    level = rt_hw_interrupt_disable();
    uart->save_index ++;
    if (uart->save_index >= RT_UART_RX_BUFFER_SIZE)
        uart->save_index = 0;
    rt_hw_interrupt_enable(level);

    /* invoke callback */
    if (uart->parent.rx_indicate != RT_NULL)
    {
        rt_size_t length;
        if (uart->read_index > uart->save_index)
            length = RT_UART_RX_BUFFER_SIZE - uart->read_index + uart->save_index;
        else
            length = uart->save_index - uart->read_index;

        uart->parent.rx_indicate(&uart->parent, length);
    }
}

static rt_err_t rt_uart_init (rt_device_t dev)
{
    UA1TXE = 0U;    /* disable UARTA1 transmission operation */
    UA1RXE = 0U;    /* disable UARTA1 reception operation */
    UA1PWR = 0U;    /* disable UARTA1 operation */
    UA1TMK = 1U;    /* disable INTUA1T interrupt */
    UA1TIF = 0U;    /* clear INTUA1T interrupt flag */
    UA1RMK = 1U;    /* disable INTUA1R interrupt */
    UA1RIF = 0U;    /* clear INTUA1R interrupt flag */
    /* Set INTUA1T level low priority */
    UA1TIC |= 0x07U;
    /* Set INTUA1R level low priority */
    UA1RIC |= 0x07U;
    //BAUDRATE = 9600
    UA1CTL1 = _03_UARTA_BASECLK_FXX_16;
    UA1CTL2 = _11_UARTA1_BASECLK_DIVISION;
    UA1CTL0 = _10_UARTA_TRANSFDIR_LSB | _00_UARTA_PARITY_NONE | _02_UARTA_DATALENGTH_8BIT | _00_UARTA_STOPLENGTH_1BIT;
    UA1OPT0 = _14_UARTA_UAnOPT0_INITIALVALUE | _00_UARTA_TRAN_DATALEVEL_NORMAL | _00_UARTA_REC_DATALEVEL_NORMAL;
    UA1PWR  = 1U;    /* enable UARTA1 operation */
    /* Set TXDA1 pin */
    /* Set RXDA1 pin */
    PFC3_bit.no0  = 0;
    PFCE3_bit.no0 = 0;
    PMC3_bit.no0  = 1;

    PFC3_bit.no1  = 0;
    PFCE3_bit.no1 = 0;
    PMC3_bit.no1  = 1;

    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable the UART Interrupt */
        UA1TIF = 0U;    /* clear INTUA1T interrupt flag */
        UA1TMK = 1U;    /* disable INTUA1T interrupt */
        UA1RIF = 0U;    /* clear INTUA1R interrupt flag */
        UA1RMK = 0U;    /* enable INTUA1R interrupt */
        UA1TXE = 1U;    /* enable UARTA1 transmission operation */
        UA1RXE = 1U;    /* enable UARTA1 reception operation */
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Disable the UART Interrupt */
        UA1TXE = 0U;    /* disable UARTA1 transmission operation */
        UA1RXE = 0U;    /* disable UARTA1 reception operation */
        UA1TMK = 1U;    /* disable INTUA1T interrupt */
        UA1TIF = 0U;    /* clear INTUA1T interrupt flag */
        UA1RMK = 1U;    /* disable INTUA1R interrupt */
        UA1RIF = 0U;    /* clear INTUA1R interrupt flag */
    }

    return RT_EOK;
}

static rt_ssize_t rt_uart_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint8_t *ptr;
    struct rt_uart_v850 *uart = (struct rt_uart_v850 *)dev;
    RT_ASSERT(uart != RT_NULL);

    /* point to buffer */
    ptr = (rt_uint8_t *)buffer;
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        while (size)
        {
            /* interrupt receive */
            rt_base_t level;

            /* disable interrupt */
            level = rt_hw_interrupt_disable();
            if (uart->read_index != uart->save_index)
            {
                *ptr = uart->rx_buffer[uart->read_index];

                uart->read_index ++;
                if (uart->read_index >= RT_UART_RX_BUFFER_SIZE)
                    uart->read_index = 0;
            }
            else
            {
                /* no data in rx buffer */

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
                break;
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            ptr ++;
            size --;
        }

        return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    }

    return 0;
}

static rt_ssize_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    char *ptr;
    ptr = (char*)buffer;

    if (dev->flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                while (UA1TSF == 1U)
                    ;
                UA1TX = '\r';
            }

            /* THRE status, contain valid data */
            while (UA1TSF == 1U)
                ;
            UA1TX = *ptr;

            ptr ++;
            size --;
        }
    }
    else
    {
        while (size != 0)
        {
            /* THRE status, contain valid data */
            while (UA1TSF == 1U)
                ;
            UA1TX = *ptr;

            ptr ++;
            size --;
        }
    }

    return (rt_size_t)ptr - (rt_size_t)buffer;
}

void rt_hw_uart_init(void)
{
    struct rt_uart_v850 *uart;

    /* get uart device */
    uart = &uart_device;

    /* device initialization */
    uart->parent.type = RT_Device_Class_Char;
    rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));
    uart->read_index = uart->save_index = 0;

    /* device interface */
    uart->parent.init      = rt_uart_init;
    uart->parent.open      = rt_uart_open;
    uart->parent.close     = rt_uart_close;
    uart->parent.read      = rt_uart_read;
    uart->parent.write     = rt_uart_write;
    uart->parent.control   = RT_NULL;
    uart->parent.user_data = RT_NULL;

    rt_device_register(&uart->parent,
        "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
}
#endif /* end of UART */

/*@}*/
