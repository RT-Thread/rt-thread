/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "LPC24xx.h"
#include "board.h"

/* serial hardware register */
#define REG8(d)         (*((volatile unsigned char *)(d)))
#define REG32(d)        (*((volatile unsigned long *)(d)))

#define UART_RBR(base)  REG8(base + 0x00)
#define UART_THR(base)  REG8(base + 0x00)
#define UART_IER(base)  REG32(base + 0x04)
#define UART_IIR(base)  REG32(base + 0x08)
#define UART_FCR(base)  REG8(base + 0x08)
#define UART_LCR(base)  REG8(base + 0x0C)
#define UART_MCR(base)  REG8(base + 0x10)
#define UART_LSR(base)  REG8(base + 0x14)
#define UART_MSR(base)  REG8(base + 0x18)
#define UART_SCR(base)  REG8(base + 0x1C)
#define UART_DLL(base)  REG8(base + 0x00)
#define UART_DLM(base)  REG8(base + 0x04)
#define UART_ACR(base)  REG32(base + 0x20)
#define UART_FDR(base)  REG32(base + 0x28)
#define UART_TER(base)  REG8(base + 0x30)

/* LPC serial device */
struct rt_lpcserial
{
    /* inherit from device */
    struct rt_device parent;

    rt_uint32_t hw_base;
    rt_uint32_t irqno;
    rt_uint32_t baudrate;

    /* reception field */
    rt_uint16_t save_index, read_index;
    rt_uint8_t  rx_buffer[RT_UART_RX_BUFFER_SIZE];
};

#ifdef RT_USING_UART1
struct rt_lpcserial serial1;
#endif
#ifdef RT_USING_UART2
struct rt_lpcserial serial2;
#endif

void rt_hw_serial_init(void);

#define U0PINS      0x00000005

void rt_hw_uart_isr(int irqno, void *param)
{
    RT_UNUSED rt_uint32_t iir;
    struct rt_lpcserial* lpc_serial = (struct rt_lpcserial*)param;

    RT_ASSERT(lpc_serial != RT_NULL)

    if (UART_LSR(lpc_serial->hw_base) & 0x01)
    {
        rt_base_t level;

        while (UART_LSR(lpc_serial->hw_base) & 0x01)
        {
            /* disable interrupt */
            level = rt_hw_interrupt_disable();

            /* read character */
            lpc_serial->rx_buffer[lpc_serial->save_index] =
                UART_RBR(lpc_serial->hw_base);
            lpc_serial->save_index ++;
            if (lpc_serial->save_index >= RT_UART_RX_BUFFER_SIZE)
                lpc_serial->save_index = 0;

            /* if the next position is read index, discard this 'read char' */
            if (lpc_serial->save_index == lpc_serial->read_index)
            {
                lpc_serial->read_index ++;
                if (lpc_serial->read_index >= RT_UART_RX_BUFFER_SIZE)
                    lpc_serial->read_index = 0;
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);
        }

        /* invoke callback */
        if(lpc_serial->parent.rx_indicate != RT_NULL)
        {
          lpc_serial->parent.rx_indicate(&lpc_serial->parent, 1);
        }
    }

    /* clear interrupt source */
    iir = UART_IIR(lpc_serial->hw_base);

    /* acknowledge Interrupt */
    VICVectAddr = 0;
}


/**
 * @addtogroup LPC214x
 */
/*@{*/

static rt_err_t rt_serial_init (rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_lpcserial* lpc_serial;
    lpc_serial = (struct rt_lpcserial*) dev;

    RT_ASSERT(lpc_serial != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* init UART rx interrupt */
        UART_IER(lpc_serial->hw_base) = 0x01;

        /* install ISR */
        rt_hw_interrupt_install(lpc_serial->irqno,
                                rt_hw_uart_isr, lpc_serial, RT_NULL);
        rt_hw_interrupt_umask(lpc_serial->irqno);
    }

    return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
    struct rt_lpcserial* lpc_serial;
    lpc_serial = (struct rt_lpcserial*) dev;

    RT_ASSERT(lpc_serial != RT_NULL);

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* disable UART rx interrupt */
        UART_IER(lpc_serial->hw_base) = 0x00;
    }

    return RT_EOK;
}

static rt_err_t rt_serial_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static rt_size_t rt_serial_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    struct rt_lpcserial *lpc_serial = (struct rt_lpcserial*)dev;
    RT_ASSERT(lpc_serial != RT_NULL);

    /* point to buffer */
    ptr = (rt_uint8_t*) buffer;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        while (size)
        {
            /* interrupt receive */
            rt_base_t level;

            /* disable interrupt */
            level = rt_hw_interrupt_disable();
            if (lpc_serial->read_index != lpc_serial->save_index)
            {
                *ptr = lpc_serial->rx_buffer[lpc_serial->read_index];

                lpc_serial->read_index ++;
                if (lpc_serial->read_index >= RT_UART_RX_BUFFER_SIZE)
                    lpc_serial->read_index = 0;
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

            ptr ++; size --;
        }

        return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    }
    else if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
    {
        /* not support right now */
        RT_ASSERT(0);
    }

    /* polling mode */
    while (size && (UART_LSR(lpc_serial->hw_base) & 0x01))
    {
        /* Read Character */
        *ptr = UART_RBR(lpc_serial->hw_base);

        ptr  ++;
        size --;
    }

    return (rt_size_t)ptr - (rt_size_t)buffer;
}

static rt_size_t rt_serial_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    struct rt_lpcserial* lpc_serial;
    char *ptr;

    lpc_serial = (struct rt_lpcserial*) dev;
    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* not support */
        RT_ASSERT(0);
    }
    else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
    {
        /* not support */
        RT_ASSERT(0);
    }

    /* polling write */
    ptr = (char *)buffer;

    if (dev->flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                while (!(UART_LSR(lpc_serial->hw_base) & 0x20));
                UART_THR(lpc_serial->hw_base) = '\r';
            }

            while (!(UART_LSR(lpc_serial->hw_base) & 0x20));
            UART_THR(lpc_serial->hw_base) = *ptr;

            ptr ++;
            size --;
        }
    }
    else
    {
        while (size)
        {
            while (!(UART_LSR(lpc_serial->hw_base) & 0x20));
            UART_THR(lpc_serial->hw_base) = *ptr;

            ptr ++;
            size --;
        }
    }

    return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_hw_serial_init(void)
{
    struct rt_lpcserial* lpc_serial;

#ifdef RT_USING_UART1
    lpc_serial = &serial1;

    lpc_serial->parent.type = RT_Device_Class_Char;

    lpc_serial->hw_base = 0xE000C000;
    lpc_serial->baudrate = 115200;
    lpc_serial->irqno = UART0_INT;

    rt_memset(lpc_serial->rx_buffer, 0, sizeof(lpc_serial->rx_buffer));
    lpc_serial->read_index = lpc_serial->save_index = 0;

    /* Enable UART0 RxD and TxD pins */
    PINSEL0 |= 0x50;

    /* 8 bits, no Parity, 1 Stop bit */
    UART_LCR(lpc_serial->hw_base) = 0x83;

    /* Setup Baudrate */
    UART_DLL(lpc_serial->hw_base) = (PCLK/16/lpc_serial->baudrate) & 0xFF;
    UART_DLM(lpc_serial->hw_base) = ((PCLK/16/lpc_serial->baudrate) >> 8) & 0xFF;

    /* DLAB = 0 */
    UART_LCR(lpc_serial->hw_base) = 0x03;

    lpc_serial->parent.type     = RT_Device_Class_Char;
    lpc_serial->parent.init     = rt_serial_init;
    lpc_serial->parent.open     = rt_serial_open;
    lpc_serial->parent.close    = rt_serial_close;
    lpc_serial->parent.read     = rt_serial_read;
    lpc_serial->parent.write    = rt_serial_write;
    lpc_serial->parent.control  = rt_serial_control;
    lpc_serial->parent.user_data  = RT_NULL;

    rt_device_register(&lpc_serial->parent,
        "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
#endif

#ifdef RT_USING_UART2
    lpc_serial = &serial2;

    lpc_serial->parent.type = RT_Device_Class_Char;

    lpc_serial->hw_base = 0xE0010000;
    lpc_serial->baudrate = 115200;
    lpc_serial->irqno = UART1_INT;

    rt_memset(lpc_serial->rx_buffer, 0, sizeof(lpc_serial->rx_buffer));
    lpc_serial->read_index = lpc_serial->save_index = 0;

    /* Enable UART1 RxD and TxD pins */
    PINSEL0 |= 0x05 << 16;

    /* 8 bits, no Parity, 1 Stop bit */
    UART_LCR(lpc_serial->hw_base) = 0x83;

    /* Setup Baudrate */
    UART_DLL(lpc_serial->hw_base) = (PCLK/16/lpc_serial->baudrate) & 0xFF;
    UART_DLM(lpc_serial->hw_base) = ((PCLK/16/lpc_serial->baudrate) >> 8) & 0xFF;

    /* DLAB = 0 */
    UART_LCR(lpc_serial->hw_base) = 0x03;

    lpc_serial->parent.type     = RT_Device_Class_Char;
    lpc_serial->parent.init     = rt_serial_init;
    lpc_serial->parent.open     = rt_serial_open;
    lpc_serial->parent.close    = rt_serial_close;
    lpc_serial->parent.read     = rt_serial_read;
    lpc_serial->parent.write    = rt_serial_write;
    lpc_serial->parent.control  = rt_serial_control;
    lpc_serial->parent.user_data  = RT_NULL;

    rt_device_register(&lpc_serial->parent,
        "uart2", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
#endif
}

/*@}*/
