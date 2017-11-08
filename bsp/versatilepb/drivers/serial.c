/* VersatilePB uart0 serial
 * Marcos Medeiros
 */
#include <rtthread.h>
#include "interrupt.h"
#include "rthw.h"
#define __iobase		0x101f1000
#define IRQ_UART_NUM	12
#define UARTDR			0x00
#define UARTFR			0x18
#define UARTCR			0x30
#define UARTIMSC		0x38
#define UARTICR			0x44

static inline void serial_enable_rxe(rt_uint32_t v)
{
	rt_uint32_t curr = readl(__iobase + UARTCR);
	if (v)
		writel(__iobase + UARTCR, curr | (1 << 9));
	else
		writel(__iobase + UARTCR, curr & ~(1 << 9));
}

static inline void  serial_enable_txe(rt_uint32_t v)
{
	rt_uint32_t curr = readl(__iobase + UARTCR);
	if (v)
		writel(__iobase + UARTCR, curr | (1 << 8));
	else
		writel(__iobase + UARTCR, curr & ~(1 << 8));
}

static inline void  enable_txe_irq(rt_uint32_t v)
{
	rt_uint32_t curr = readl(__iobase + UARTIMSC);
	if (v)
		writel(__iobase + UARTIMSC, curr | (1 << 5));
	else
		writel(__iobase + UARTIMSC, curr & ~(1 << 5));
}

static inline void  enable_rxe_irq(rt_uint32_t v)
{
	rt_uint32_t curr = readl(__iobase + UARTIMSC);
	if (v)
		writel(__iobase + UARTIMSC, curr | (1 << 4));
	else
		writel(__iobase + UARTIMSC, curr & ~(1 << 4));
}

static inline void  clear_txe_irq()
{
	writel(__iobase + UARTICR, (1 << 5));
}

static inline void  clear_rxe_irq()
{
	writel(__iobase + UARTICR, (1 << 6));
}

static inline void  serial_wait()
{
	do {
		(void) 0;
	} while (readl(__iobase + UARTFR) & (1 << 5));
}

static void serial_init()
{
	/* enable receive irq and disable transmit */
	enable_rxe_irq(1);
	enable_txe_irq(0);
}

/**
 * This function will write a character to serial an cga
 *
 * @param c the char to write
 */
void rt_console_putc(int c)
{
	serial_wait();
	writeb(__iobase + UARTDR, c & 0xff);
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

static rt_size_t rt_console_write(rt_device_t dev, rt_off_t pos, const void * buffer, rt_size_t size)
{
    rt_size_t i = size;
    const char* str = buffer;

    while(i--)
    {
        rt_console_putc(*str++);
    }

    return size;
}

static rt_size_t rt_console_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
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
    rt_base_t level;

	if((readl(__iobase + UARTFR)&(1 << 6)) != 0)
	{
		/* disable interrupt */
		level = rt_hw_interrupt_disable();
		c = (readl(__iobase + UARTDR)&0xFF);
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

		clear_rxe_irq();
		/* enable interrupt */
		rt_hw_interrupt_enable(level);

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
		else
		{

		}
	}
}

/**
 * This function initializes console
 *
 */
void rt_hw_console_init(void)
{

	serial_init();

	/* install interrupt service routine */
	rt_hw_interrupt_install(IRQ_UART_NUM, rt_console_isr, RT_NULL, "serial");
	rt_hw_interrupt_unmask(IRQ_UART_NUM);

    console_device.type 		= RT_Device_Class_Char;
    console_device.rx_indicate  = RT_NULL;
    console_device.tx_complete  = RT_NULL;
    console_device.init 		= rt_console_init;
    console_device.open		    = rt_console_open;
    console_device.close		= rt_console_close;
    console_device.read 		= rt_console_read;
    console_device.write 	    = rt_console_write;
    console_device.control      = rt_console_control;
    console_device.user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(&console_device,
                              "console",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
}

/**
 * This function is used to display a string on console, normally, it's
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 *
 * Modified:
 *	caoxl 2009-10-14
 *	the name is change to rt_hw_console_output in the v0.3.0
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

