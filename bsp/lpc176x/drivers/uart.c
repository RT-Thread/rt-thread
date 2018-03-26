/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-08     Bernard      The first version for LPC17xx
 * 2010-05-02     Aozima       update CMSIS to 130
 */

#include <rthw.h>
#include <rtthread.h>
#include "LPC17xx.h"

#define IER_RBR     0x01
#define IER_THRE    0x02
#define IER_RLS     0x04

#define IIR_PEND    0x01
#define IIR_RLS     0x03
#define IIR_RDA     0x02
#define IIR_CTI     0x06
#define IIR_THRE    0x01

#define LSR_RDR     0x01
#define LSR_OE      0x02
#define LSR_PE      0x04
#define LSR_FE      0x08
#define LSR_BI      0x10
#define LSR_THRE    0x20
#define LSR_TEMT    0x40
#define LSR_RXFE    0x80

/**
 * @addtogroup LPC176x
 */

/*@{*/
#if defined(RT_USING_UART0) && defined(RT_USING_DEVICE)

#define UART_BAUDRATE   115200
#define LPC_UART        LPC_UART0
#define UART_IRQn       UART0_IRQn

struct rt_uart_lpc
{
    struct rt_device parent;

    /* buffer for reception */
    //rt_uint8_t read_index, save_index;
	rt_uint16_t read_index, save_index;		//fix here 8bit length
    rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
} uart_device;

 //get the precise bps settings
void rt_uart_precise_baudset(rt_uint32_t uartclk, rt_uint32_t bps, rt_uint8_t *m_fdr, rt_uint32_t *m_fdiv)
{
	typedef struct
	{
		rt_uint8_t Div: 4; 
		rt_uint8_t Mul: 4; 
	} rt_uart_dcm_tbl;

	//1-[000-999]+\,
	rt_uart_dcm_tbl const tbl[] =
	{
		{ 0, 1 }, { 1, 15}, { 1, 14}, { 1, 13},
		{ 1, 12}, { 1, 11}, { 1, 10}, { 1, 9 },
		{ 1, 8 }, { 2, 15}, { 1, 7 }, { 2, 13},
		{ 1, 6 }, { 2, 11}, { 1, 5 }, { 3, 14},
		{ 2, 9 }, { 3, 13}, { 1, 4 }, { 4, 15},
		{ 3, 11}, { 2, 7 }, { 3, 10}, { 4, 13},
		{ 1, 3 }, { 5, 14}, { 4, 11}, { 3, 8 },
		{ 5, 13}, { 2, 5 }, { 5, 12}, { 3, 7 },
		{ 4, 9 }, { 5, 11}, { 6, 13}, { 7, 15},//-----------4*9
		{ 1, 2 }, { 8, 15}, { 7, 13}, { 6, 11},
		{ 5, 9 }, { 4, 7 }, { 7, 12}, { 3, 5 },
		{ 8, 13}, { 5, 8 }, { 7, 11}, { 9, 14},
		{ 2, 3 }, { 9, 13}, { 7, 10}, { 5, 7 },
		{ 8, 11}, { 11, 15}, { 3, 4 }, { 10, 13},
		{ 7, 9 }, { 11, 14}, { 4, 5 }, { 9, 11},
		{ 5, 6 }, { 11, 13}, { 6, 7 }, { 13, 15},
		{ 7, 8 }, { 8, 9 }, { 9, 10}, { 10, 11},
		{ 11, 12}, { 12, 13}, { 13, 14}, { 14, 15},
	};

	rt_uint8_t i = 0, k = 0, j = 0;
	rt_uint8_t m_err[72] = {0};

	rt_uint32_t fDiv, uDLest;
	rt_uint32_t uartClock = uartclk;//SystemCoreClock / 4; // get clk

	float fFRest = 1.5;// tFRest = 1.5, tAbs, min;


	if (uartClock % (16 * bps) == 0) // PCLK / (16*bps)
	{
		m_fdr[0] = 0x10;// shut down
		m_fdiv[0] = (uartClock >> 4) / ( bps );
		return;
	}

	k = 0xff;
	for(i = 0; i < 72; i++)				//
	{
		uDLest = (uint32_t)(uartClock * tbl[i].Mul / (16 * bps * (tbl[i].Mul + tbl[i].Div)));
		fFRest = (float)(uartClock * tbl[i].Mul) / (float)(16 * bps * uDLest * (tbl[i].Mul + tbl[i].Div));		//
		fDiv = (uint32_t)((fFRest - 1) * 10000);
		if(fDiv > 0xff)
		{
			m_err[i] = 0xff;
		}
		else
		{
			m_err[i] = fDiv;
		}

		if(m_err[i] < k)
		{
			k = m_err[i];		//
			j = i;
			m_fdr[0] = tbl[j].Div | (tbl[j].Mul << 4);
			m_fdiv[0] = uDLest;
		}
	}
}

void UART0_IRQHandler(void)
{
    rt_ubase_t level, iir;
    struct rt_uart_lpc *uart = &uart_device;
	/* enter interrupt */ 
 	rt_interrupt_enter();
    /* read IIR and clear it */
    iir = LPC_UART->IIR;

    iir >>= 1;              /* skip pending bit in IIR */
    iir &= 0x07;            /* check bit 1~3, interrupt identification */

    if (iir == IIR_RDA)     /* Receive Data Available */
    {
        /* Receive Data Available */
        uart->rx_buffer[uart->save_index] = LPC_UART->RBR;

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
    else if (iir == IIR_RLS)
    {
        iir = LPC_UART->LSR;    //oe pe fe oe read for clear interrupt
    }
	/* leave interrupt */ 
 	rt_interrupt_leave();
    return;
}

static rt_err_t rt_uart_init(rt_device_t dev)
{
    rt_uint32_t Fdiv;
    rt_uint32_t pclkdiv, pclk;
	rt_uint8_t  m_fd = 0;

    /* Init UART Hardware */
    if (LPC_UART == LPC_UART0)
    {
        LPC_PINCON->PINSEL0 &= ~0x000000F0;
        LPC_PINCON->PINSEL0 |= 0x00000050;  /* RxD0 is P0.3 and TxD0 is P0.2 */
        /* By default, the PCLKSELx value is zero, thus, the PCLK for
        all the peripherals is 1/4 of the SystemFrequency. */
        /* Bit 6~7 is for UART0 */
        pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
        switch (pclkdiv)
        {
        case 0x00:
        default:
            pclk = SystemCoreClock / 4;
            break;
        case 0x01:
            pclk = SystemCoreClock;
            break;
        case 0x02:
            pclk = SystemCoreClock / 2;
            break;
        case 0x03:
            pclk = SystemCoreClock / 8;
            break;
        }
		
		rt_uart_precise_baudset(pclk, UART_BAUDRATE, &m_fd, &Fdiv); //get the precise bps settings
		LPC_UART0->LCR    = 0x83;							/* 8 bits, no Parity, 1 Stop bit */

		LPC_UART0->DLL    = Fdiv % 256;                   /*baud rate */
		LPC_UART0->FDR    = m_fd;						//add here
		LPC_UART0->DLM    = Fdiv / 256;

		LPC_UART0->LCR  = 0x03;/* DLAB = 0 */
		LPC_UART0->FCR  = 0x07;/* Enable and reset TX and RX FIFO. */

    }
    else if ((LPC_UART1_TypeDef *)LPC_UART == LPC_UART1)
    {
        LPC_PINCON->PINSEL4 &= ~0x0000000F;
        LPC_PINCON->PINSEL4 |= 0x0000000A;  /* Enable RxD1 P2.1, TxD1 P2.0 */

        /* By default, the PCLKSELx value is zero, thus, the PCLK for
        all the peripherals is 1/4 of the SystemFrequency. */
        /* Bit 8,9 are for UART1 */
        pclkdiv = (LPC_SC->PCLKSEL0 >> 8) & 0x03;
        switch (pclkdiv)
        {
        case 0x00:
        default:
            pclk = SystemCoreClock / 4;
            break;
        case 0x01:
            pclk = SystemCoreClock;
            break;
        case 0x02:
            pclk = SystemCoreClock / 2;
            break;
        case 0x03:
            pclk = SystemCoreClock / 8;
            break;
        }

		rt_uart_precise_baudset(pclk, UART_BAUDRATE, &m_fd, &Fdiv); //get the precise bps settings
		LPC_UART1->LCR    = 0x83;							/* 8 bits, no Parity, 1 Stop bit */
		LPC_UART1->DLL    = Fdiv % 256;                   /*baud rate */
		LPC_UART1->FDR    = m_fd;						//add here
		LPC_UART1->DLM    = Fdiv / 256;
		LPC_UART1->LCR  = 0x03;/* DLAB = 0 */
		LPC_UART1->FCR  = 0x07;/* Enable and reset TX and RX FIFO. */
    }

    /* Ensure a clean start, no data in either TX or RX FIFO. */
    while ((LPC_UART->LSR & (LSR_THRE | LSR_TEMT)) != (LSR_THRE | LSR_TEMT));
    while (LPC_UART->LSR & LSR_RDR)
    {
        Fdiv = LPC_UART->RBR;   /* Dump data from RX FIFO */
    }
    LPC_UART->IER = IER_RBR | IER_THRE | IER_RLS;   /* Enable UART interrupt */

    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable the UART Interrupt */
        NVIC_EnableIRQ(UART_IRQn);
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Disable the UART Interrupt */
        NVIC_DisableIRQ(UART_IRQn);
    }

    return RT_EOK;
}

static rt_size_t rt_uart_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint8_t *ptr;
    struct rt_uart_lpc *uart = (struct rt_uart_lpc *)dev;
    RT_ASSERT(uart != RT_NULL);

    /* point to buffer */
    ptr = (rt_uint8_t *) buffer;
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

static rt_size_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
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
                /* THRE status, contain valid data */
                while (!(LPC_UART->LSR & LSR_THRE));
                /* write data */
                LPC_UART->THR = '\r';
            }

            /* THRE status, contain valid data */
            while (!(LPC_UART->LSR & LSR_THRE));
            /* write data */
            LPC_UART->THR = *ptr;

            ptr ++;
            size --;
        }
    }
    else
    {
        while (size != 0)
        {
            /* THRE status, contain valid data */
            while (!(LPC_UART->LSR & LSR_THRE));

            /* write data */
            LPC_UART->THR = *ptr;

            ptr++;
            size--;
        }
    }

    return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_hw_uart_init(void)
{
    struct rt_uart_lpc *uart;

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
