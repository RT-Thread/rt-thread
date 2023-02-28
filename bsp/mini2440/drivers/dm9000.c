#include <rtthread.h>
#include <netif/ethernetif.h>

#include "dm9000.h"
#include <s3c24x0.h>

/*
 * Davicom DM9000EP driver
 *
 * IRQ_LAN connects to EINT7(GPF7)
 * nLAN_CS connects to nGCS4
 */

/* #define DM9000_DEBUG		1 */
#if DM9000_DEBUG
#define DM9000_TRACE	rt_kprintf
#else
#define DM9000_TRACE(...)
#endif

/*
 * DM9000 interrupt line is connected to PF7
 */
//--------------------------------------------------------

#define DM9000_PHY		  0x40	/* PHY address 0x01 */

#define MAX_ADDR_LEN 6
enum DM9000_PHY_mode
{
	DM9000_10MHD = 0, DM9000_100MHD = 1,
	DM9000_10MFD = 4, DM9000_100MFD = 5,
	DM9000_AUTO  = 8, DM9000_1M_HPNA = 0x10
};

enum DM9000_TYPE
{
	TYPE_DM9000E,
	TYPE_DM9000A,
	TYPE_DM9000B
};

struct rt_dm9000_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

	enum DM9000_TYPE type;
	enum DM9000_PHY_mode mode;

	rt_uint8_t packet_cnt;				  /* packet I or II */
	rt_uint16_t queue_packet_len;		   /* queued packet (packet II) */

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];		/* hw address	*/
};
static struct rt_dm9000_eth dm9000_device;
static struct rt_semaphore sem_ack, sem_lock;

void rt_dm9000_isr(int irqno);

static void delay_ms(rt_uint32_t ms)
{
	rt_uint32_t len;
	for (;ms > 0; ms --)
		for (len = 0; len < 100; len++ );
}

/* Read a byte from I/O port */
rt_inline rt_uint8_t dm9000_io_read(rt_uint16_t reg)
{
	DM9000_IO = reg;
	return (rt_uint8_t) DM9000_DATA;
}

/* Write a byte to I/O port */
rt_inline void dm9000_io_write(rt_uint16_t reg, rt_uint16_t value)
{
	DM9000_IO = reg;
	DM9000_DATA = value;
}

/* Read a word from phyxcer */
rt_inline rt_uint16_t phy_read(rt_uint16_t reg)
{
	rt_uint16_t val;

	/* Fill the phyxcer register into REG_0C */
	dm9000_io_write(DM9000_EPAR, DM9000_PHY | reg);
	dm9000_io_write(DM9000_EPCR, 0xc);	/* Issue phyxcer read command */

	delay_ms(100);		/* Wait read complete */

	dm9000_io_write(DM9000_EPCR, 0x0);	/* Clear phyxcer read command */
	val = (dm9000_io_read(DM9000_EPDRH) << 8) | dm9000_io_read(DM9000_EPDRL);

	return val;
}

/* Write a word to phyxcer */
rt_inline void phy_write(rt_uint16_t reg, rt_uint16_t value)
{
	/* Fill the phyxcer register into REG_0C */
	dm9000_io_write(DM9000_EPAR, DM9000_PHY | reg);

	/* Fill the written data into REG_0D & REG_0E */
	dm9000_io_write(DM9000_EPDRL, (value & 0xff));
	dm9000_io_write(DM9000_EPDRH, ((value >> 8) & 0xff));
	dm9000_io_write(DM9000_EPCR, 0xa);	/* Issue phyxcer write command */

	delay_ms(500);		/* Wait write complete */

	dm9000_io_write(DM9000_EPCR, 0x0);	/* Clear phyxcer write command */
}

/* Set PHY operationg mode */
rt_inline void phy_mode_set(rt_uint32_t media_mode)
{
	rt_uint16_t phy_reg4 = 0x01e1, phy_reg0 = 0x1000;
	if (!(media_mode & DM9000_AUTO))
	{
		switch (media_mode)
		{
		case DM9000_10MHD:
			phy_reg4 = 0x21;
			phy_reg0 = 0x0000;
			break;
		case DM9000_10MFD:
			phy_reg4 = 0x41;
			phy_reg0 = 0x1100;
			break;
		case DM9000_100MHD:
			phy_reg4 = 0x81;
			phy_reg0 = 0x2000;
			break;
		case DM9000_100MFD:
			phy_reg4 = 0x101;
			phy_reg0 = 0x3100;
			break;
		}
		phy_write(4, phy_reg4);	/* Set PHY media mode */
		phy_write(0, phy_reg0);	/*  Tmp */
	}

	dm9000_io_write(DM9000_GPCR, 0x01);	/* Let GPIO0 output */
	dm9000_io_write(DM9000_GPR, 0x00);	/* Enable PHY */
}

/* interrupt service routine */
void rt_dm9000_isr(int irqno)
{
	rt_uint16_t int_status;
	rt_uint16_t last_io;
	rt_uint32_t eint_pend;

	last_io = DM9000_IO;

	/* Disable all interrupts */
	dm9000_io_write(DM9000_IMR, IMR_PAR);

	/* Got DM9000 interrupt status */
	int_status = dm9000_io_read(DM9000_ISR);	/* Got ISR */
	dm9000_io_write(DM9000_ISR, int_status);	/* Clear ISR status */

	DM9000_TRACE("dm9000 isr: int status %04x\n", int_status);

	/* receive overflow */
	if (int_status & ISR_ROS)
	{
		rt_kprintf("overflow\n");
	}

	if (int_status & ISR_ROOS)
	{
		rt_kprintf("overflow counter overflow\n");
	}

	/* Received the coming packet */
	if (int_status & ISR_PRS)
	{
		/* a frame has been received */
		eth_device_ready(&(dm9000_device.parent));
	}

	/* Transmit Interrupt check */
	if (int_status & ISR_PTS)
	{
		/* transmit done */
		int tx_status = dm9000_io_read(DM9000_NSR);	/* Got TX status */

		if (tx_status & (NSR_TX2END | NSR_TX1END))
		{
			dm9000_device.packet_cnt --;
			if (dm9000_device.packet_cnt > 0)
			{
				DM9000_TRACE("dm9000 isr: tx second packet\n");

				/* transmit packet II */
				/* Set TX length to DM9000 */
				dm9000_io_write(DM9000_TXPLL, dm9000_device.queue_packet_len & 0xff);
				dm9000_io_write(DM9000_TXPLH, (dm9000_device.queue_packet_len >> 8) & 0xff);

				/* Issue TX polling command */
				dm9000_io_write(DM9000_TCR, TCR_TXREQ);	/* Cleared after TX complete */
			}

			/* One packet sent complete */
			rt_sem_release(&sem_ack);
		}
	}

	/* Re-enable interrupt mask */
	dm9000_io_write(DM9000_IMR, IMR_PAR | IMR_PTM | IMR_PRM);

	DM9000_IO = last_io;
}

/* RT-Thread Device Interface */
/* initialize the interface */
static rt_err_t rt_dm9000_init(rt_device_t dev)
{
	int i, oft, lnk;
	rt_uint32_t value;

	/* RESET device */
	dm9000_io_write(DM9000_NCR, NCR_RST);
	delay_ms(1000);		/* delay 1ms */

	/* identfy DM9000 */
	value  = dm9000_io_read(DM9000_VIDL);
	value |= dm9000_io_read(DM9000_VIDH) << 8;
	value |= dm9000_io_read(DM9000_PIDL) << 16;
	value |= dm9000_io_read(DM9000_PIDH) << 24;
	if (value == DM9000_ID)
	{
		rt_kprintf("dm9000 id: 0x%x\n", value);
	}
	else
	{
		rt_kprintf("dm9000 id: 0x%x\n", value);
		return -RT_ERROR;
	}

	/* GPIO0 on pre-activate PHY */
	dm9000_io_write(DM9000_GPR, 0x00);				/* REG_1F bit0 activate phyxcer */
	dm9000_io_write(DM9000_GPCR, GPCR_GEP_CNTL);	/* Let GPIO0 output */
	dm9000_io_write(DM9000_GPR, 0x00);				 /* Enable PHY */

	/* Set PHY */
	phy_mode_set(dm9000_device.mode);

	/* Program operating register */
	dm9000_io_write(DM9000_NCR, 0x0);	/* only intern phy supported by now */
	dm9000_io_write(DM9000_TCR, 0);		/* TX Polling clear */
	dm9000_io_write(DM9000_BPTR, 0x3f);	/* Less 3Kb, 200us */
	dm9000_io_write(DM9000_FCTR, FCTR_HWOT(3) | FCTR_LWOT(8));	/* Flow Control : High/Low Water */
	dm9000_io_write(DM9000_FCR, 0x0);	/* SH FIXME: This looks strange! Flow Control */
	dm9000_io_write(DM9000_SMCR, 0);	/* Special Mode */
	dm9000_io_write(DM9000_NSR, NSR_WAKEST | NSR_TX2END | NSR_TX1END);	/* clear TX status */
	dm9000_io_write(DM9000_ISR, 0x0f);	/* Clear interrupt status */
	dm9000_io_write(DM9000_TCR2, 0x80);	/* Switch LED to mode 1 */

	/* set mac address */
	for (i = 0, oft = 0x10; i < 6; i++, oft++)
		dm9000_io_write(oft, dm9000_device.dev_addr[i]);
	/* set multicast address */
	for (i = 0, oft = 0x16; i < 8; i++, oft++)
		dm9000_io_write(oft, 0xff);

	/* Activate DM9000 */
	dm9000_io_write(DM9000_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN);	/* RX enable */
	dm9000_io_write(DM9000_IMR, IMR_PAR);

	if (dm9000_device.mode == DM9000_AUTO)
	{
	    i = 0;
		while (!(phy_read(1) & 0x20))
		{
			/* autonegation complete bit */
			rt_thread_delay( RT_TICK_PER_SECOND/10 );
			i++;
			if (i > 30 ) /* wait 3s */
			{
				rt_kprintf("could not establish link\n");
				return 0;
			}
		}
	}

	/* send a notify */
	eth_device_linkchange(&dm9000_device.parent, RT_TRUE);

	/* see what we've got */
	lnk = phy_read(17) >> 12;
	rt_kprintf("operating at ");
	switch (lnk)
	{
	case 1:
		rt_kprintf("10M half duplex ");
		break;
	case 2:
		rt_kprintf("10M full duplex ");
		break;
	case 4:
		rt_kprintf("100M half duplex ");
		break;
	case 8:
		rt_kprintf("100M full duplex ");
		break;
	default:
		rt_kprintf("unknown: %d ", lnk);
		break;
	}
	rt_kprintf("mode\n");

	/* Enable TX/RX interrupt mask */
	dm9000_io_write(DM9000_IMR,IMR_PAR | IMR_PTM | IMR_PRM);

	return RT_EOK;
}

static rt_err_t rt_dm9000_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_dm9000_close(rt_device_t dev)
{
	/* RESET devie */
	phy_write(0, 0x8000);	/* PHY RESET */
	dm9000_io_write(DM9000_GPR, 0x01);	/* Power-Down PHY */
	dm9000_io_write(DM9000_IMR, 0x80);	/* Disable all interrupt */
	dm9000_io_write(DM9000_RCR, 0x00);	/* Disable RX */

	return RT_EOK;
}

static rt_ssize_t rt_dm9000_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_ssize_t rt_dm9000_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_dm9000_control(rt_device_t dev, int cmd, void *args)
{
	switch (cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if (args) rt_memcpy(args, dm9000_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_dm9000_tx( rt_device_t dev, struct pbuf* p)
{
	DM9000_TRACE("dm9000 tx: %d\n", p->tot_len);

	/* lock DM9000 device */
	rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

	/* disable dm9000a interrupt */
	dm9000_io_write(DM9000_IMR, IMR_PAR);

	/* Move data to DM9000 TX RAM */
	DM9000_outb(DM9000_IO_BASE, DM9000_MWCMD);

	{
		/* q traverses through linked list of pbuf's
		 * This list MUST consist of a single packet ONLY */
		struct pbuf *q;
		rt_uint16_t pbuf_index = 0;
		rt_uint8_t word[2], word_index = 0;

		q = p;
		/* Write data into dm9000a, two bytes at a time
		 * Handling pbuf's with odd number of bytes correctly
		 * No attempt to optimize for speed has been made */
		while (q)
		{
			if (pbuf_index < q->len)
			{
				word[word_index++] = ((u8_t*)q->payload)[pbuf_index++];
				if (word_index == 2)
				{
					DM9000_outw(DM9000_DATA_BASE, (word[1] << 8) | word[0]);
					word_index = 0;
				}
			}
			else
			{
				q = q->next;
				pbuf_index = 0;
			}
		}
		/* One byte could still be unsent */
		if (word_index == 1)
		{
			DM9000_outw(DM9000_DATA_BASE, word[0]);
		}
	}

	if (dm9000_device.packet_cnt == 0)
	{
		DM9000_TRACE("dm9000 tx: first packet\n");

		dm9000_device.packet_cnt ++;
		/* Set TX length to DM9000 */
		dm9000_io_write(DM9000_TXPLL, p->tot_len & 0xff);
		dm9000_io_write(DM9000_TXPLH, (p->tot_len >> 8) & 0xff);

		/* Issue TX polling command */
		dm9000_io_write(DM9000_TCR, TCR_TXREQ);	/* Cleared after TX complete */
	}
	else
	{
		DM9000_TRACE("dm9000 tx: second packet\n");

		dm9000_device.packet_cnt ++;
		dm9000_device.queue_packet_len = p->tot_len;
	}

	/* enable dm9000a interrupt */
	dm9000_io_write(DM9000_IMR, IMR_PAR | IMR_PTM | IMR_PRM);

	/* unlock DM9000 device */
	rt_sem_release(&sem_lock);

	/* wait ack */
	rt_sem_take(&sem_ack, RT_WAITING_FOREVER);

	DM9000_TRACE("dm9000 tx done\n");

	return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_dm9000_rx(rt_device_t dev)
{
	struct pbuf* p;
	rt_uint32_t rxbyte;
	rt_uint16_t rx_status, rx_len;
	rt_uint16_t* data;

	/* init p pointer */
	p = RT_NULL;

	/* lock DM9000 device */
	rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

__error_retry:
	/* Check packet ready or not */
	dm9000_io_read(DM9000_MRCMDX);				/* Dummy read */
	rxbyte = DM9000_inb(DM9000_DATA_BASE);		/* Got most updated data */
	if (rxbyte)
	{
		if (rxbyte > 1)
		{
			DM9000_TRACE("dm9000 rx: rx error, stop device\n");

			dm9000_io_write(DM9000_RCR, 0x00);	/* Stop Device */
			dm9000_io_write(DM9000_ISR, 0x80);	/* Stop INT request */
		}

		/* A packet ready now  & Get status/length */
		DM9000_outb(DM9000_IO_BASE, DM9000_MRCMD);

		rx_status = DM9000_inw(DM9000_DATA_BASE);
		rx_len = DM9000_inw(DM9000_DATA_BASE);

		DM9000_TRACE("dm9000 rx: status %04x len %d\n", rx_status, rx_len);

		/* allocate buffer */
		p = pbuf_alloc(PBUF_LINK, rx_len, PBUF_RAM);
		if (p != RT_NULL)
		{
			struct pbuf* q;
			rt_int32_t len;

			for (q = p; q != RT_NULL; q= q->next)
			{
				data = (rt_uint16_t*)q->payload;
				len = q->len;

				while (len > 0)
				{
					*data = DM9000_inw(DM9000_DATA_BASE);
					data ++;
					len -= 2;
				}
			}
		}
		else
		{
			rt_uint16_t dummy;

			rt_kprintf("dm9000 rx: no pbuf\n");

			/* no pbuf, discard data from DM9000 */
			data = &dummy;
			while (rx_len)
			{
				*data = DM9000_inw(DM9000_DATA_BASE);
				rx_len -= 2;
			}
		}

		if ((rx_status & 0xbf00) || (rx_len < 0x40)
				|| (rx_len > DM9000_PKT_MAX))
		{
			rt_kprintf("rx error: status %04x, rx_len: %d\n", rx_status, rx_len);

			if (rx_status & 0x100)
			{
				rt_kprintf("rx fifo error\n");
			}
			if (rx_status & 0x200)
			{
				rt_kprintf("rx crc error\n");
			}
			if (rx_status & 0x8000)
			{
				rt_kprintf("rx length error\n");
			}
			if (rx_len > DM9000_PKT_MAX)
			{
				rt_kprintf("rx length too big\n");

				/* RESET device */
				dm9000_io_write(DM9000_NCR, NCR_RST);
				rt_thread_delay(1); /* delay 5ms */
			}

			/* it issues an error, release pbuf */
			if (p != RT_NULL) pbuf_free(p);
			p = RT_NULL;

			goto __error_retry;
		}
	}
	else
	{
		/* clear packet received latch status */
		dm9000_io_write(DM9000_ISR, ISR_PTS);

		/* restore receive interrupt */
		dm9000_io_write(DM9000_IMR, IMR_PAR | IMR_PTM | IMR_PRM);
	}

	/* unlock DM9000 device */
	rt_sem_release(&sem_lock);

	return p;
}

#define B4_Tacs				 0x0
#define B4_Tcos				 0x0
#define B4_Tacc				 0x7
#define B4_Tcoh				 0x0
#define B4_Tah				  0x0
#define B4_Tacp				 0x0
#define B4_PMC				  0x0

void INTEINT4_7_handler(int irqno, void *param)
{
    rt_uint32_t eint_pend;

    eint_pend = EINTPEND;

    /* EINT7 : DM9000AEP */
    if( eint_pend & (1<<7) )
    {
        rt_dm9000_isr(0);
    }

	/* clear EINT pending bit */
	EINTPEND = eint_pend;
}

int rt_hw_dm9000_init()
{
	/* Set GPF7 as EINT7 */
	GPFCON = GPFCON & (~(3 << 14)) | (2 << 14);
	GPFUP = GPFUP | (1 << 7);
	/* EINT7 High level interrupt */
	EXTINT0 = (EXTINT0 & (~(0x7 << 28))) | (0x1 << 28);
	/* Enable EINT7 */
	EINTMASK = EINTMASK & (~(1<<7));
	/* Set GPA15 as nGCS4 */
	GPACON |= 1 << 15;
	/* DM9000 width 16, wait enable */
	BWSCON = BWSCON & (~(0x7<<16)) | (0x5<<16);
	BANKCON4 = (1<<13) | (1<<11) | (0x6<<8) | (1<<6) | (1<<4) | (0<<2) | (0);

	rt_sem_init(&sem_ack, "tx_ack", 1, RT_IPC_FLAG_FIFO);
	rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

	dm9000_device.type  = TYPE_DM9000A;
	dm9000_device.mode	= DM9000_AUTO;
	dm9000_device.packet_cnt = 0;
	dm9000_device.queue_packet_len = 0;

	/*
	 * SRAM Tx/Rx pointer automatically return to start address,
	 * Packet Transmitted, Packet Received
	 */

	dm9000_device.dev_addr[0] = 0x00;
	dm9000_device.dev_addr[1] = 0x60;
	dm9000_device.dev_addr[2] = 0x6E;
	dm9000_device.dev_addr[3] = 0x11;
	dm9000_device.dev_addr[4] = 0x02;
	dm9000_device.dev_addr[5] = 0x0F;

	dm9000_device.parent.parent.init	   = rt_dm9000_init;
	dm9000_device.parent.parent.open	   = rt_dm9000_open;
	dm9000_device.parent.parent.close	   = rt_dm9000_close;
	dm9000_device.parent.parent.read	   = rt_dm9000_read;
	dm9000_device.parent.parent.write	   = rt_dm9000_write;
	dm9000_device.parent.parent.control	= rt_dm9000_control;
	dm9000_device.parent.parent.user_data  = RT_NULL;

	dm9000_device.parent.eth_rx	 = rt_dm9000_rx;
	dm9000_device.parent.eth_tx	 = rt_dm9000_tx;

	eth_device_init(&(dm9000_device.parent), "e0");

	/* instal interrupt */
	rt_hw_interrupt_install(INTEINT4_7, INTEINT4_7_handler, RT_NULL, "EINT4_7");
	rt_hw_interrupt_umask(INTEINT4_7);

	return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_dm9000_init);

void dm9000a(void)
{
	rt_kprintf("\n");
	rt_kprintf("NCR   (%02X): %02x\n", DM9000_NCR,   dm9000_io_read(DM9000_NCR));
	rt_kprintf("NSR   (%02X): %02x\n", DM9000_NSR,   dm9000_io_read(DM9000_NSR));
	rt_kprintf("TCR   (%02X): %02x\n", DM9000_TCR,   dm9000_io_read(DM9000_TCR));
	rt_kprintf("TSRI  (%02X): %02x\n", DM9000_TSR1,  dm9000_io_read(DM9000_TSR1));
	rt_kprintf("TSRII (%02X): %02x\n", DM9000_TSR2,  dm9000_io_read(DM9000_TSR2));
	rt_kprintf("RCR   (%02X): %02x\n", DM9000_RCR,   dm9000_io_read(DM9000_RCR));
	rt_kprintf("RSR   (%02X): %02x\n", DM9000_RSR,   dm9000_io_read(DM9000_RSR));
	rt_kprintf("ORCR  (%02X): %02x\n", DM9000_ROCR,  dm9000_io_read(DM9000_ROCR));
	rt_kprintf("CRR   (%02X): %02x\n", DM9000_CHIPR, dm9000_io_read(DM9000_CHIPR));
	rt_kprintf("CSCR  (%02X): %02x\n", DM9000_CSCR,  dm9000_io_read(DM9000_CSCR));
	rt_kprintf("RCSSR (%02X): %02x\n", DM9000_RCSSR, dm9000_io_read(DM9000_RCSSR));
	rt_kprintf("ISR   (%02X): %02x\n", DM9000_ISR,   dm9000_io_read(DM9000_ISR));
	rt_kprintf("IMR   (%02X): %02x\n", DM9000_IMR,   dm9000_io_read(DM9000_IMR));
	rt_kprintf("\n");
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(dm9000a, dm9000a register dump);
#endif
