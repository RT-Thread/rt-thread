/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     Bernard      first version
 * 2011-05-15     lgnq         modified according bernard's implementaion.
 */

#include <rtthread.h>

#include "serial.h"

/**
 * @addtogroup FM3 MB9B610
 */
/*@{*/

/* RT-Thread Device Interface */
/**
 * This function initializes serial
 */
static rt_err_t rt_serial_init (rt_device_t dev)
{
    struct serial_device* uart = (struct serial_device*) dev->user_data;

    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            rt_memset(uart->int_rx->rx_buffer, 0,
                      sizeof(uart->int_rx->rx_buffer));
            uart->int_rx->read_index = uart->int_rx->save_index = 0;
        }

        if (dev->flag & RT_DEVICE_FLAG_INT_TX)
        {
            rt_memset(uart->int_tx->tx_buffer, 0,
                      sizeof(uart->int_tx->tx_buffer));
            uart->int_tx->write_index = uart->int_tx->save_index = 0;
        }

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }

    return RT_EOK;
}

/* save a char to serial buffer */
static void rt_serial_savechar(struct serial_device* uart, char ch)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    uart->int_rx->rx_buffer[uart->int_rx->save_index] = ch;
    uart->int_rx->save_index ++;
    if (uart->int_rx->save_index >= UART_RX_BUFFER_SIZE)
        uart->int_rx->save_index = 0;

    /* if the next position is read index, discard this 'read char' */
    if (uart->int_rx->save_index == uart->int_rx->read_index)
    {
        uart->int_rx->read_index ++;
        if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
            uart->int_rx->read_index = 0;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct serial_device* uart;

    RT_ASSERT(dev != RT_NULL);
    uart = (struct serial_device*) dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* enable interrupt */
        UART_ENABLE_IRQ(uart->rx_irq);
    }

    return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
    struct serial_device* uart;

    RT_ASSERT(dev != RT_NULL);
    uart = (struct serial_device*) dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* disable interrupt */
        UART_DISABLE_IRQ(uart->rx_irq);
    }

    return RT_EOK;
}

static rt_ssize_t rt_serial_read (rt_device_t dev, rt_off_t pos, void* buffer,
                                 rt_size_t size)
{
    rt_uint8_t* ptr;
    rt_err_t err_code;
    struct serial_device* uart;

    ptr = buffer;
    err_code = RT_EOK;
    uart = (struct serial_device*)dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        rt_base_t level;

        /* interrupt mode Rx */
        while (size)
        {
            if (uart->int_rx->read_index != uart->int_rx->save_index)
            {
                *ptr++ = uart->int_rx->rx_buffer[uart->int_rx->read_index];
                size --;

                /* disable interrupt */
                level = rt_hw_interrupt_disable();

                uart->int_rx->read_index ++;
                if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
                    uart->int_rx->read_index = 0;

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
            }
            else
            {
                /* set error code */
                err_code = -RT_EEMPTY;
                break;
            }
        }
    }
    else
    {
        /* polling mode */
        while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
        {
            while (uart->uart_device->SSR & SSR_RDRF)
            {
                *ptr = uart->uart_device->RDR & 0xff;
                ptr ++;
            }
        }
    }

    /* set error code */
    rt_set_errno(err_code);
    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_ssize_t rt_serial_write (rt_device_t dev, rt_off_t pos,
                                  const void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    rt_err_t err_code;
    struct serial_device* uart;

    err_code = RT_EOK;
    ptr = (rt_uint8_t*)buffer;
    uart = (struct serial_device*)dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* interrupt mode Tx */
        while (uart->int_tx->save_index != uart->int_tx->write_index)
        {
            /* save on tx buffer */
            uart->int_tx->tx_buffer[uart->int_tx->save_index] = *ptr++;

            -- size;

            /* move to next position */
            uart->int_tx->save_index ++;

            /* wrap save index */
            if (uart->int_tx->save_index >= UART_TX_BUFFER_SIZE)
                uart->int_tx->save_index = 0;
        }

        /* set error code */
        if (size > 0)
            err_code = -RT_EFULL;
    }
    else
    {
        /* polling mode */
        while (size)
        {
            /*
             * to be polite with serial console add a line feed
             * to the carriage return character
             */
            if (*ptr == '\n' && (dev->flag & RT_DEVICE_FLAG_STREAM))
            {
                while (!(uart->uart_device->SSR & SSR_TDRE));
                uart->uart_device->TDR = '\r';
            }

            while (!(uart->uart_device->SSR & SSR_TDRE));
            uart->uart_device->TDR = (*ptr & 0x1FF);

            ++ptr;
            --size;
        }
    }

    /* set error code */
    rt_set_errno(err_code);

    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_serial_control (rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        break;
    }

    return RT_EOK;
}

/*
 * serial register
 */
rt_err_t rt_hw_serial_register(rt_device_t device, const char* name,
                               rt_uint32_t flag, struct serial_device *serial)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_serial_init;
    device->open        = rt_serial_open;
    device->close       = rt_serial_close;
    device->read        = rt_serial_read;
    device->write       = rt_serial_write;
    device->control     = rt_serial_control;
    device->user_data   = serial;

    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/* ISR for serial interrupt */
void rt_hw_serial_isr(rt_device_t device)
{
    struct serial_device* uart = (struct serial_device*) device->user_data;

    /* interrupt mode receive */
    RT_ASSERT(device->flag & RT_DEVICE_FLAG_INT_RX);

    /* save on rx buffer */
    while (uart->uart_device->SSR & SSR_RDRF)
    {
        rt_serial_savechar(uart, uart->uart_device->RDR & 0xff);
    }

    /* invoke callback */
    if (device->rx_indicate != RT_NULL)
    {
        rt_size_t rx_length;

        /* get rx length */
        rx_length = uart->int_rx->read_index > uart->int_rx->save_index ?
                    UART_RX_BUFFER_SIZE - uart->int_rx->read_index + uart->int_rx->save_index :
                    uart->int_rx->save_index - uart->int_rx->read_index;

        device->rx_indicate(device, rx_length);
    }
}

#ifdef RT_USING_UART0
/* UART0 device driver structure */
#define UART0   FM3_MFS0_UART
struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
    UART0,
    MFS0RX_IRQn,
    MFS0TX_IRQn,
    &uart0_int_rx,
    RT_NULL
};
struct rt_device uart0_device;

void MFS0RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&uart0_device);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /**< #ifdef RT_USING_UART0 */

#ifdef RT_USING_UART2
/* UART2 device driver structure */
#define UART2   FM3_MFS2_UART
struct serial_int_rx uart2_int_rx;
struct serial_device uart2 =
{
    UART2,
    MFS2RX_IRQn,
    MFS2TX_IRQn,
    &uart2_int_rx,
    RT_NULL
};
struct rt_device uart2_device;

void MFS2RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&uart2_device);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /**< #ifdef RT_USING_UART2 */

#ifdef RT_USING_UART4
/* UART4 device driver structure */
#define UART4   FM3_MFS4_UART
struct serial_int_rx uart4_int_rx;
struct serial_device uart4 =
{
    (FM3_MFS03_UART_TypeDef*)UART4,
    MFS4RX_IRQn,
    MFS4TX_IRQn,
    &uart4_int_rx,
    RT_NULL
};
struct rt_device uart4_device;

void MFS4RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_serial_isr(&uart4_device);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /**< #ifdef RT_USING_UART4 */

void rt_hw_serial_init(void)
{
    uint32_t APB2_clock = (SystemCoreClock >> (APBC2_PSR_Val & 0x03));

#ifdef RT_USING_UART0
    /* initialize UART0 */
    /* Set Uart Ch0 Port, SIN0_0:P21, SOT0_0:P22 */
    FM3_GPIO->ADE &= ~(1UL<<31); /* disable P22 AN31 function */
    FM3_GPIO->PFR2 = FM3_GPIO->PFR2 | (1<<1) | (1<<2);
    FM3_GPIO->EPFR07 = FM3_GPIO->EPFR07 & ~(3<<4 | 3<<6) | (1<<4) | (1<<6);

    uart0.uart_device->SMR = SMR_MD_UART | SMR_SOE;;
    uart0.uart_device->BGR = (APB2_clock + (BPS/2))/BPS - 1; /* round */
    uart0.uart_device->ESCR = ESCR_DATABITS_8;
    uart0.uart_device->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

    /* register UART0 device */
    rt_hw_serial_register(&uart0_device,
                          "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart0);
#endif /**< #ifdef RT_USING_UART0 */

#ifdef RT_USING_UART2
    /* initialize UART2 */
    /* Set Uart Ch2 Port, SIN2_2:P17, SOT2_2:P18 */
    FM3_GPIO->ADE &= ~(1<<7 | 1<<8); /* disable P17 AN07 and P18 AN08 function */
    FM3_GPIO->PFR1 = FM3_GPIO->PFR1 | (1<<7) | (1<<8) ;
    FM3_GPIO->EPFR07 = FM3_GPIO->EPFR07 | (3<<16) | (3<<18) ;

    uart2.uart_device->SMR = SMR_MD_UART | SMR_SOE;;
    uart2.uart_device->BGR = (APB2_clock + (BPS/2))/BPS - 1; /* round */
    uart2.uart_device->ESCR = ESCR_DATABITS_8;
    uart2.uart_device->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

    /* register UART2 device */
    rt_hw_serial_register(&uart2_device,
                          "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart2);
#endif /**< #ifdef RT_USING_UART2 */

#ifdef RT_USING_UART4
    /* initialize UART4 */
    /* Set Uart Ch4 Port, SIN4_2:P05, SOT4_2:P06 */
    FM3_GPIO->PFR0 = FM3_GPIO->PFR0 | (1<<5) | (1<<6);
    FM3_GPIO->EPFR08 = FM3_GPIO->EPFR08 | (3<<4) | (3<<6);

    uart4.uart_device->SMR = SMR_MD_UART | SMR_SOE;;
    uart4.uart_device->BGR = (APB2_clock + (BPS/2))/BPS - 1; /* round */
    uart4.uart_device->ESCR = ESCR_DATABITS_8;
    uart4.uart_device->SCR = SCR_RXE | SCR_TXE | SCR_RIE;

    /* register UART4 device */
    rt_hw_serial_register(&uart4_device,
                          "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart4);
#endif /**< #ifdef RT_USING_UART4 */
}

/*@}*/
