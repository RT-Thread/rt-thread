#include <rthw.h>
#include <rtthread.h>
#include "CMSIS/CM0/NUC1xx.h"

/**
 * @addtogroup NUC1xx
 */

/*@{*/
#if defined(RT_USING_UART) && defined(RT_USING_DEVICE)

#define UART_BAUDRATE   115200
struct rt_uart_nuc
{
	struct rt_device parent;

	/* buffer for reception */
	rt_uint8_t read_index, save_index;
	rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
}uart_device;

void UART0_IRQHandler(void)
{
	rt_ubase_t level;
    struct rt_uart_nuc* uart = &uart_device;

	if (UART0->ISR.RDA_INT == 1)	    /* Receive Data Available */
	{
		while (UART0->ISR.RDA_IF == 1)
		{
			/* Receive Data Available */
			uart->rx_buffer[uart->save_index] = UART0->DATA;

			level = rt_hw_interrupt_disable();
			uart->save_index ++;
			if (uart->save_index >= RT_UART_RX_BUFFER_SIZE)
				uart->save_index = 0;
			rt_hw_interrupt_enable(level);
		}

		/* invoke callback */
		if(uart->parent.rx_indicate != RT_NULL)
		{
		    rt_size_t length;
		    if (uart->read_index > uart->save_index)
                length = RT_UART_RX_BUFFER_SIZE - uart->read_index + uart->save_index;
            else
                length = uart->save_index - uart->read_index;

            uart->parent.rx_indicate(&uart->parent, length);
		}
	}

	return;
}

static rt_err_t rt_uart_init (rt_device_t dev)
{
    /* Multi-Function Pin: Enable UART0:Tx Rx */
    SYS->GPBMFP.UART0_RX = 1;
    SYS->GPBMFP.UART0_TX = 1;

    /* Configure GCR to reset UART0 */
    SYS->IPRSTC2.UART0_RST = 1;
    SYS->IPRSTC2.UART0_RST = 0;

    /* Enable UART clock */
    SYSCLK->APBCLK.UART0_EN = 1;

    /* Select UART clock source */
    SYSCLK->CLKSEL1.UART_S = 0;

    /* Data format */
    UART0->LCR.WLS = 3;

    /* Configure the baud rate */
    *((__IO uint32_t *)&UART0->BAUD) = 0x3F000066; /* This setting is for 115200bsp with 12Mhz clock source */

	return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
	RT_ASSERT(dev != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* open receive data available interrupt */
		UART0->IER.RDA_IEN = 1;

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
	rt_uint8_t* ptr;
	struct rt_uart_nuc *uart = (struct rt_uart_nuc*)dev;
	RT_ASSERT(uart != RT_NULL);

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

static rt_size_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
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
				/* check whether UART is empty */
				while (UART0->FSR.TX_EMPTY !=1);
				/* write data */
				UART0->DATA = '\r';
			}

			/* check whether UART is empty */
			while (UART0->FSR.TX_EMPTY !=1);
			/* write data */
			UART0->DATA = *ptr;

			ptr ++;
			size --;
		}
	}
	else
	{
	while ( size != 0 )
	{
		/* check whether UART is empty */
		while (UART0->FSR.TX_EMPTY !=1);
		/* write data */
		UART0->DATA = *ptr;

		ptr++;
		size--;
	}
	}

	return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_hw_uart_init(void)
{
	struct rt_uart_nuc* uart;

	/* get uart device */
	uart = &uart_device;

	/* device initialization */
	uart->parent.type = RT_Device_Class_Char;
	rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));
	uart->read_index = uart->save_index = 0;

	/* device interface */
	uart->parent.init 	    = rt_uart_init;
	uart->parent.open 	    = rt_uart_open;
	uart->parent.close      = rt_uart_close;
	uart->parent.read 	    = rt_uart_read;
	uart->parent.write      = rt_uart_write;
	uart->parent.control    = RT_NULL;
	uart->parent.user_data  = RT_NULL;

	rt_device_register(&uart->parent,
		"uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
}
#endif /* end of UART */

/*@}*/
