/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        the first version
 */

#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>

static unsigned addr_6845;
static rt_uint16_t *crt_buf;
static rt_int16_t  crt_pos;

extern void init_keyboard();
extern void rt_keyboard_isr(void);
extern rt_bool_t rt_keyboard_getc(char* c);

extern void rt_serial_init(void);
extern char rt_serial_getc(void);
extern void rt_serial_putc(const char c);

void rt_console_putc(int c);

/**
 * @addtogroup QEMU
 */
/*@{*/

/**
 * This function initializes cga
 *
 */
void rt_cga_init(void)
{
    rt_uint16_t volatile *cp;
    rt_uint16_t was;
    rt_uint32_t pos;

    cp = (rt_uint16_t *) (CGA_BUF);
    was = *cp;
    *cp = (rt_uint16_t) 0xA55A;
    if (*cp != 0xA55A)
    {
        cp = (rt_uint16_t *) (MONO_BUF);
        addr_6845 = MONO_BASE;
    }
    else
    {
        *cp = was;
        addr_6845 = CGA_BASE;
    }

    /* Extract cursor location */
    outb(addr_6845, 14);
    pos = inb(addr_6845+1) << 8;
    outb(addr_6845, 15);
    pos |= inb(addr_6845+1);

    crt_buf = (rt_uint16_t *)cp;
    crt_pos = pos;
}

/**
 * This function will write a character to cga
 *
 * @param c the char to write
 */
static void rt_cga_putc(int c)
{
    /* if no attribute given, then use black on white */
    if (!(c & ~0xff)) c |= 0x0700;

    switch (c & 0xff)
    {
    case '\b':
        if (crt_pos > 0)
        {
            crt_pos--;
            crt_buf[crt_pos] = (c&~0xff) | ' ';
        }
        break;
    case '\n':
        crt_pos += CRT_COLS;
        /* cascade  */
    case '\r':
        crt_pos -= (crt_pos % CRT_COLS);
        break;
    case '\t':
        rt_console_putc(' ');
        rt_console_putc(' ');
        rt_console_putc(' ');
        rt_console_putc(' ');
        rt_console_putc(' ');
        break;
    default:
        crt_buf[crt_pos++] = c;     /* write the character */
        break;
    }

    if (crt_pos >= CRT_SIZE)
    {
        rt_int32_t i;
        rt_memcpy(crt_buf, crt_buf + CRT_COLS, (CRT_SIZE - CRT_COLS) << 1);
        for (i = CRT_SIZE - CRT_COLS; i < CRT_SIZE; i++)
            crt_buf[i] = 0x0700 | ' ';
        crt_pos -= CRT_COLS;
    }

    outb(addr_6845, 14);
    outb(addr_6845+1, crt_pos >> 8);
    outb(addr_6845, 15);
    outb(addr_6845+1, crt_pos);
}

/**
 * This function will write a character to serial an cga
 *
 * @param c the char to write
 */
void rt_console_putc(int c)
{
    rt_cga_putc(c);
    rt_serial_putc(c);
}

/* RT-Thread Device Interface */
#define CONSOLE_RX_BUFFER_SIZE    64
static struct rt_device    console_device;
static rt_uint8_t  rx_buffer[CONSOLE_RX_BUFFER_SIZE];
static rt_uint32_t read_index, save_index;

static rt_err_t rt_console_init (rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_console_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_console_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_console_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static rt_ssize_t rt_console_write(rt_device_t dev, rt_off_t pos, const void * buffer, rt_size_t size)
{
    rt_size_t i = size;
    const char* str = buffer;

    while(i--)
    {
        rt_console_putc(*str++);
    }

    return size;
}

static rt_ssize_t rt_console_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr = buffer;
    rt_err_t err_code = RT_EOK;

    /* interrupt mode Rx */
    while (size)
    {
        rt_base_t level;

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        if (read_index != save_index)
        {
            /* read a character */
            *ptr++ = rx_buffer[read_index];
            size--;

            /* move to next position */
            read_index ++;
            if (read_index >= CONSOLE_RX_BUFFER_SIZE)
                read_index = 0;
        }
        else
        {
            /* set error code */
            err_code = -RT_EEMPTY;

            /* enable interrupt */
            rt_hw_interrupt_enable(level);
            break;
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }

    /* set error code */
    rt_set_errno(err_code);
    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static void rt_console_isr(int vector, void* param)
{
    char c;
    rt_bool_t ret;
    rt_base_t level;

    if(INTUART0_RX == vector)
    {
        c = rt_serial_getc();
        ret = RT_TRUE;
    }
    else
    {
        rt_keyboard_isr();
        ret = rt_keyboard_getc(&c);
    }

    if(ret == RT_FALSE)
    {
        /* do nothing */
    }
    else
    {
        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* save character */
        rx_buffer[save_index] = c;
        save_index ++;
        if (save_index >= CONSOLE_RX_BUFFER_SIZE)
            save_index = 0;

        /* if the next position is read index, discard this 'read char' */
        if (save_index == read_index)
        {
            read_index ++;
            if (read_index >= CONSOLE_RX_BUFFER_SIZE)
                read_index = 0;
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }

    /* invoke callback */
    if (console_device.rx_indicate != RT_NULL)
    {
        rt_size_t rx_length;

        /* get rx length */
        rx_length = read_index > save_index ?
            CONSOLE_RX_BUFFER_SIZE - read_index + save_index :
            save_index - read_index;

        if(rx_length > 0)
        {
            console_device.rx_indicate(&console_device, rx_length);
        }
    }
}

/**
 * This function initializes console
 *
 */
int rt_hw_console_init(void)
{
    rt_cga_init();
    rt_serial_init();
    init_keyboard();

    /* install  keyboard isr */
    rt_hw_interrupt_install(INTKEYBOARD, rt_console_isr, RT_NULL, "kbd");
    rt_hw_interrupt_umask(INTKEYBOARD);

    rt_hw_interrupt_install(INTUART0_RX, rt_console_isr, RT_NULL, "COM1");
    rt_hw_interrupt_umask(INTUART0_RX);

    console_device.type         = RT_Device_Class_Char;
    console_device.rx_indicate  = RT_NULL;
    console_device.tx_complete  = RT_NULL;
    console_device.init         = rt_console_init;
    console_device.open         = rt_console_open;
    console_device.close        = rt_console_close;
    console_device.read         = rt_console_read;
    console_device.write        = rt_console_write;
    console_device.control      = rt_console_control;
    console_device.user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(&console_device,
                        "console",
                        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_console_init);

/**
 * This function is used to display a string on console, normally, it's
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 *
 * Modified:
 *  caoxl 2009-10-14
 *  the name is change to rt_hw_console_output in the v0.3.0
 *
 */
void rt_hw_console_output(const char* str)
{
    while (*str)
    {
        rt_console_putc (*str++);
    }
}

/*@}*/
