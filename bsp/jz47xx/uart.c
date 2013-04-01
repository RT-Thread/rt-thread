#include <rthw.h>
#include <rtthread.h>

#include <jz4755.h>

/**
 * @addtogroup Jz47xx
 */

/*@{*/
#if defined(RT_USING_UART) && defined(RT_USING_DEVICE)

#define UART_BAUDRATE   57600
#define DEV_CLK         12000000

/*
 * Define macros for UARTIER
 * UART Interrupt Enable Register
 */
#define UARTIER_RIE	    (1 << 0)	/* 0: receive fifo "full" interrupt disable */
#define UARTIER_TIE	    (1 << 1)	/* 0: transmit fifo "empty" interrupt disable */
#define UARTIER_RLIE	(1 << 2)	/* 0: receive line status interrupt disable */
#define UARTIER_MIE	    (1 << 3)	/* 0: modem status interrupt disable */
#define UARTIER_RTIE	(1 << 4)	/* 0: receive timeout interrupt disable */

/*
 * Define macros for UARTISR
 * UART Interrupt Status Register
 */
#define UARTISR_IP	        (1 << 0)	/* 0: interrupt is pending  1: no interrupt */
#define UARTISR_IID	        (7 << 1)	/* Source of Interrupt */
#define UARTISR_IID_MSI		(0 << 1)	/* Modem status interrupt */
#define UARTISR_IID_THRI	(1 << 1)	/* Transmitter holding register empty */
#define UARTISR_IID_RDI		(2 << 1)	/* Receiver data interrupt */
#define UARTISR_IID_RLSI	(3 << 1)	/* Receiver line status interrupt */
#define UARTISR_FFMS	    (3 << 6)	/* FIFO mode select, set when UARTFCR.FE is set to 1 */
#define UARTISR_FFMS_NO_FIFO	(0 << 6)
#define UARTISR_FFMS_FIFO_MODE	(3 << 6)

/*
 * Define macros for UARTFCR
 * UART FIFO Control Register
 */
#define UARTFCR_FE	    (1 << 0)	/* 0: non-FIFO mode  1: FIFO mode */
#define UARTFCR_RFLS	(1 << 1)	/* write 1 to flush receive FIFO */
#define UARTFCR_TFLS	(1 << 2)	/* write 1 to flush transmit FIFO */
#define UARTFCR_DMS	    (1 << 3)	/* 0: disable DMA mode */
#define UARTFCR_UUE	    (1 << 4)	/* 0: disable UART */
#define UARTFCR_RTRG	(3 << 6)	/* Receive FIFO Data Trigger */
#define UARTFCR_RTRG_1	(0 << 6)
#define UARTFCR_RTRG_4	(1 << 6)
#define UARTFCR_RTRG_8	(2 << 6)
#define UARTFCR_RTRG_15	(3 << 6)

/*
 * Define macros for UARTLCR
 * UART Line Control Register
 */
#define UARTLCR_WLEN	(3 << 0)	/* word length */
#define UARTLCR_WLEN_5	(0 << 0)
#define UARTLCR_WLEN_6	(1 << 0)
#define UARTLCR_WLEN_7	(2 << 0)
#define UARTLCR_WLEN_8	(3 << 0)
#define UARTLCR_STOP	(1 << 2)	/* 0: 1 stop bit when word length is 5,6,7,8
					   1: 1.5 stop bits when 5; 2 stop bits when 6,7,8 */
#define UARTLCR_PE	    (1 << 3)	/* 0: parity disable */
#define UARTLCR_PROE	(1 << 4)	/* 0: even parity  1: odd parity */
#define UARTLCR_SPAR	(1 << 5)	/* 0: sticky parity disable */
#define UARTLCR_SBRK	(1 << 6)	/* write 0 normal, write 1 send break */
#define UARTLCR_DLAB	(1 << 7)	/* 0: access UARTRDR/TDR/IER  1: access UARTDLLR/DLHR */

/*
 * Define macros for UARTLSR
 * UART Line Status Register
 */
#define UARTLSR_DR	    (1 << 0)	/* 0: receive FIFO is empty  1: receive data is ready */
#define UARTLSR_ORER	(1 << 1)	/* 0: no overrun error */
#define UARTLSR_PER	    (1 << 2)	/* 0: no parity error */
#define UARTLSR_FER	    (1 << 3)	/* 0; no framing error */
#define UARTLSR_BRK	    (1 << 4)	/* 0: no break detected  1: receive a break signal */
#define UARTLSR_TDRQ	(1 << 5)	/* 1: transmit FIFO half "empty" */
#define UARTLSR_TEMT	(1 << 6)	/* 1: transmit FIFO and shift registers empty */
#define UARTLSR_RFER	(1 << 7)	/* 0: no receive error  1: receive error in FIFO mode */

/*
 * Define macros for UARTMCR
 * UART Modem Control Register
 */
#define UARTMCR_DTR	    (1 << 0)	/* 0: DTR_ ouput high */
#define UARTMCR_RTS	    (1 << 1)	/* 0: RTS_ output high */
#define UARTMCR_OUT1	(1 << 2)	/* 0: UARTMSR.RI is set to 0 and RI_ input high */
#define UARTMCR_OUT2	(1 << 3)	/* 0: UARTMSR.DCD is set to 0 and DCD_ input high */
#define UARTMCR_LOOP	(1 << 4)	/* 0: normal  1: loopback mode */
#define UARTMCR_MCE	    (1 << 7)	/* 0: modem function is disable */

/*
 * Define macros for UARTMSR
 * UART Modem Status Register
 */
#define UARTMSR_DCTS	(1 << 0)	/* 0: no change on CTS_ pin since last read of UARTMSR */
#define UARTMSR_DDSR	(1 << 1)	/* 0: no change on DSR_ pin since last read of UARTMSR */
#define UARTMSR_DRI	    (1 << 2)	/* 0: no change on RI_ pin since last read of UARTMSR */
#define UARTMSR_DDCD	(1 << 3)	/* 0: no change on DCD_ pin since last read of UARTMSR */
#define UARTMSR_CTS	    (1 << 4)	/* 0: CTS_ pin is high */
#define UARTMSR_DSR	    (1 << 5)	/* 0: DSR_ pin is high */
#define UARTMSR_RI	    (1 << 6)	/* 0: RI_ pin is high */
#define UARTMSR_DCD	    (1 << 7)	/* 0: DCD_ pin is high */

/*
 * Define macros for SIRCR
 * Slow IrDA Control Register
 */
#define SIRCR_TSIRE	(1 << 0)	/* 0: transmitter is in UART mode  1: IrDA mode */
#define SIRCR_RSIRE	(1 << 1)	/* 0: receiver is in UART mode  1: IrDA mode */
#define SIRCR_TPWS	(1 << 2)	/* 0: transmit 0 pulse width is 3/16 of bit length
					   1: 0 pulse width is 1.6us for 115.2Kbps */
#define SIRCR_TXPL	(1 << 3)	/* 0: encoder generates a positive pulse for 0 */
#define SIRCR_RXPL	(1 << 4)	/* 0: decoder interprets positive pulse as 0 */

struct rt_uart_jz
{
	struct rt_device parent;

	rt_uint32_t hw_base;
	rt_uint32_t irq;

	/* buffer for reception */
	rt_uint8_t read_index, save_index;
	rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
}uart_device;

static void rt_uart_irqhandler(int vector, void* param)
{
	rt_ubase_t level, isr;
    struct rt_uart_jz* uart = param;

    /* read interrupt status and clear it */
	isr = UART_ISR(uart->hw_base);

	if (isr & UARTISR_IID_RDI)	    /* Receive Data Available */
	{
		/* Receive Data Available */
		while (UART_LSR(uart->hw_base) & UARTLSR_DR)
		{
			uart->rx_buffer[uart->save_index] = UART_RDR(uart->hw_base);

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
	rt_uint32_t baud_div;
	struct rt_uart_jz *uart = (struct rt_uart_jz*)dev;

	RT_ASSERT(uart != RT_NULL);

	/* Init UART Hardware */
	UART_IER(uart->hw_base) = 0; /* clear interrupt */
	UART_FCR(uart->hw_base) = ~UARTFCR_UUE; /* disable UART unite */

	/* Enable UART clock */

	/* Set both receiver and transmitter in UART mode (not SIR) */
	UART_SIRCR(uart->hw_base) = ~(SIRCR_RSIRE | SIRCR_TSIRE);

	/* Set databits, stopbits and parity. (8-bit data, 1 stopbit, no parity) */
	UART_LCR(uart->hw_base) = UARTLCR_WLEN_8;

    /* set baudrate */
	baud_div = DEV_CLK / 16 / UART_BAUDRATE;
	UART_LCR(uart->hw_base) |= UARTLCR_DLAB;

	UART_DLHR(uart->hw_base) = (baud_div >> 8) & 0xff;
	UART_DLLR(uart->hw_base) = baud_div & 0xff;

	UART_LCR(uart->hw_base) &= ~UARTLCR_DLAB;

	/* Enable UART unit, enable and clear FIFO */
	UART_FCR(uart->hw_base) = UARTFCR_UUE | UARTFCR_FE | UARTFCR_TFLS | UARTFCR_RFLS;

	return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
	struct rt_uart_jz *uart = (struct rt_uart_jz*)dev;

	RT_ASSERT(uart != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Enable the UART Interrupt */
		UART_IER(uart->hw_base) |= (UARTIER_RIE | UARTIER_RTIE);

		/* install interrupt */
		rt_hw_interrupt_install(uart->irq, rt_uart_irqhandler, uart, "uart");
		rt_hw_interrupt_umask(uart->irq);
	}
	return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
	struct rt_uart_jz *uart = (struct rt_uart_jz*)dev;

	RT_ASSERT(uart != RT_NULL);
	if (dev->flag & RT_DEVICE_FLAG_INT_RX)
	{
		/* Disable the UART Interrupt */
		UART_IER(uart->hw_base) &= ~(UARTIER_RIE | UARTIER_RTIE);
	}

	return RT_EOK;
}

static rt_size_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t* ptr;
	struct rt_uart_jz *uart = (struct rt_uart_jz*)dev;

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
	struct rt_uart_jz *uart = (struct rt_uart_jz*)dev;

	RT_ASSERT(uart != RT_NULL);

	ptr = (char*)buffer;

	if (dev->flag & RT_DEVICE_FLAG_STREAM)
	{
		/* stream mode */
		while (size)
		{
			if (*ptr == '\n')
			{
				/* FIFO status, contain valid data */
				while (!((UART_LSR(uart->hw_base) & (UARTLSR_TDRQ | UARTLSR_TEMT)) == 0x60));
				/* write data */
				UART_TDR(uart->hw_base) = '\r';
			}

			/* FIFO status, contain valid data */
			while (!((UART_LSR(uart->hw_base) & (UARTLSR_TDRQ | UARTLSR_TEMT)) == 0x60));
			/* write data */
			UART_TDR(uart->hw_base) = *ptr;

			ptr ++;
			size --;
		}
	}
	else
	{
		while ( size != 0 )
		{
			/* FIFO status, contain valid data */
			while ( !(UART_LSR(uart->hw_base) & (UARTLSR_TDRQ | UARTLSR_TEMT) == 0x60) );

			/* write data */
			UART_TDR(uart->hw_base) = *ptr;

			ptr++;
			size--;
		}
	}

	return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_hw_uart_init(void)
{
	struct rt_uart_jz* uart;

	/* get uart device */
	uart = &uart_device;

	/* device initialization */
	uart->parent.type = RT_Device_Class_Char;
	rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));
	uart->read_index = uart->save_index = 0;
#if defined(RT_USING_UART0)
	uart->hw_base = UART0_BASE;
	uart->irq = IRQ_UART0;
#elif defined(RT_USING_UART1)
	uart->hw_base = UART1_BASE;
	uart->irq = IRQ_UART1;
#elif defined(RT_USING_UART2)
	uart->hw_base = UART2_BASE;
	uart->irq = IRQ_UART2;
#elif defined(RT_USING_UART3)
	uart->hw_base = UART3_BASE;
	uart->irq = IRQ_UART3;
#endif

	/* device interface */
	uart->parent.init 	    = rt_uart_init;
	uart->parent.open 	    = rt_uart_open;
	uart->parent.close      = rt_uart_close;
	uart->parent.read 	    = rt_uart_read;
	uart->parent.write      = rt_uart_write;
	uart->parent.control    = RT_NULL;
	uart->parent.user_data  = RT_NULL;

	rt_device_register(&uart->parent,
		"uart", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
}
#endif /* end of UART */

/*@}*/
