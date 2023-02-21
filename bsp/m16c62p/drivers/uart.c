/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-08     Bernard      The first version for LPC17xx
 * 2010-04-10     fify         Modified for M16C
 */

#include <rthw.h>
#include <rtthread.h>
#include "iom16c62p.h"
#include "bsp.h"
#include "uart.h"

#if defined(RT_USING_UART0) && defined(RT_USING_DEVICE)

struct rt_uart_m16c
{
    struct rt_device parent;

    /* buffer for reception */
    rt_uint8_t read_index, save_index;
    rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
}uart_device;

void u0rec_handler(void)
{
    rt_ubase_t level;
    rt_uint8_t c;

    struct rt_uart_m16c *uart = &uart_device;

    while (U0C1.BIT.RI == 0)
        ;
    c = U0RB.BYTE.U0RBL;

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
    rt_uint32_t level;
    /* set UART0 bit rate generator bit rate can be calculated by:
          bit rate = ((BRG count source / 16)/baud rate) - 1
          Baud rate is based on main crystal or PLL not CPU core clock */
    //pclk1 = 1;   /// seleck F1SIO
    U0BRG = (unsigned char)(((CPU_CLK_FREQ/16)/BAUD_RATE)-1);   //(N+1)

    /* UART Transmit/Receive Control Register 2 */
    UCON.BYTE = 0x00;
         /*   00000000
          b0    U0IRS       UART0 transmit irq cause select bit, 0 = transmit buffer empty
          b1    U1IRS       UART1 transmit irq cause select bit, 0 = transmit buffer empty
          b2    U0RRM       UART0 continuous receive mode enable bit, set to 0 in UART mode
          b3    U1RRM       UART1 continuous receive mode enable bit, set to 0 in UART mode
          b4    CLKMD0      CLK/CLKS select bit 0, set to 0 in UART mode
          b5    CLKMD1      CLK/CLKS select bit 1, set to 0 in UART mode
          b6    RCSP        Separate CTS/RTS bit,
          b7    Reserved, set to 0 */

    /* UART0 transmit/receive control register 0 */
    /* f1 count source, CTS/RTS disabled, CMOS output */
    U0C0.BYTE = 0x10;
         /* 00010000
          b1:b0 CLK01:CLK0  BRG count source select bits                        //01         F8SIO
          b2    CRS         CTS/RTS function select bit
          b3    TXEPT       Transmit register empty flag
          b4    CRD         CTS/RTS disable bit
          b5    NCH         Data output select bit
          b6    CKPOL       CLK polarity select bit,set to 0 in UART mode
          b7    UFORM       Transfer format select bit,set to 0 in UART mode */

    /* UART0 transmit/receive control register 1 */
    /*  disable transmit and receive, no error output pin, data not inverted */
    U0C1.BYTE = 0x00;
         /*  00000000
          b0    TE          Transmit enable bit
          b1    TI          Transmit buffer empty flag
          b2    RE          Receive enable bit
          b3    RI          Receive complete flag
          b5:b4             Reserved, set to 0
          b6    UOLCH       Data logic select bit
          b7    UOERE       Error signal output enable bit */

    /* UART0 transmit/receive mode register */
    /* 8-bit data,asynch mode, internal clock, 1 stop bit, no parity */
    U0MR.BYTE = 0x05;
         /*  00000101
          b2:b0 SMD12:SMD1  Serial I/O Mode select bits
          b3    CKDIR       Internal/External clock select bit, CKDIR
          b4    STPS        Stop bit length select bit, STPS
          b5    PRY         Odd/even parity select bit, PRY
          b6    PRYE        Parity enable bit, PRYE
          b7    IOPOL       TxD, RxD I/O polarity reverse bit */

    /* clear UART0 receive buffer by reading */
    U0TB.WORD = U0RB.WORD;
    /* clear UART0 transmit buffer */
    U0TB.WORD = 0;

    /* disable irqs before setting irq registers */
    level = rt_hw_interrupt_disable();
    /* Enable UART0 receive interrupt, priority level 4 */
    S0RIC.BYTE = 0x04;
    /* Enable all interrupts */
    rt_hw_interrupt_enable(level);

    /* UART0 transmit/receive control register 1 */
    /* enable transmit and receive */
    U0C1.BYTE = 0x05;
        /*  00000101    enable transmit and receive
        b0      TE          Transmit enable bit
        b1      TI          Transmit buffer empty flag
        b2      RE          Receive enable bit
        b3      RI          Receive complete flag
        b5:b4               Reserved, set to 0
        b6      UOLCH       Data logic select bit
        b7      UOERE       Error signal output enable bit */

    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable the UART Interrupt */
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Disable the UART Interrupt */
    }

    return RT_EOK;
}

static rt_ssize_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_uint8_t *ptr;
    struct rt_uart_m16c *uart = (struct rt_uart_m16c *)dev;
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

static rt_ssize_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    char *ptr;
    ptr = (char *)buffer;

    if (dev->flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                while (U0C1.BIT.TI == 0)
                    ;
                U0TB.BYTE.U0TBL = '\r';
            }

            /* THRE status, contain valid data */
            while (U0C1.BIT.TI == 0)
                ;
            U0TB.BYTE.U0TBL = *ptr;

            ptr ++;
            size --;
        }
    }
    else
    {
        while (size != 0)
        {
            /* THRE status, contain valid data */
            while (U0C1.BIT.TI == 0)
                ;
            U0TB.BYTE.U0TBL = *ptr;

            ptr ++;
            size --;
        }
    }

    return (rt_size_t)ptr - (rt_size_t)buffer;
}

void rt_hw_uart_init(void)
{
    struct rt_uart_m16c *uart;

    /* get uart device */
    uart = &uart_device;

    /* device initialization */
    uart->parent.type = RT_Device_Class_Char;
    rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));
    uart->read_index = uart->save_index = 0;

    /* device interface */
    uart->parent.init       = rt_uart_init;
    uart->parent.open       = rt_uart_open;
    uart->parent.close      = rt_uart_close;
    uart->parent.read       = rt_uart_read;
    uart->parent.write      = rt_uart_write;
    uart->parent.control    = RT_NULL;
    uart->parent.user_data  = RT_NULL;

    rt_device_register(&uart->parent,
        "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
}
#endif /* end of UART */

/*@}*/
