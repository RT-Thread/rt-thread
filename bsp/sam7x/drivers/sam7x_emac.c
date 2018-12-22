#include <rthw.h>
#include <rtthread.h>
#include <netif/ethernetif.h>

#include "sam7x_emac.h"
#include "AT91SAM7X256.h"
#include "lwipopts.h"
#include "lwip/mem.h"

#define MAX_ADDR_LEN 6

#ifdef DM9161
#define EMAC_PIO_CFG	(AT91C_PB8_EMDC         | \
						 AT91C_PB9_EMDIO         | \
						 AT91C_PB2_ETX0          | \
						 AT91C_PB3_ETX1          | \
						 AT91C_PB10_ETX2         | \
						 AT91C_PB11_ETX3         | \
						 AT91C_PB1_ETXEN         | \
						 AT91C_PB0_ETXCK_EREFCK  | \
						 AT91C_PB15_ERXDV_ECRSDV | \
						 AT91C_PB5_ERX0			| \
						 AT91C_PB6_ERX1			| \
						 AT91C_PB12_ETXER        | \
						 AT91C_PB13_ERX2			| \
						 AT91C_PB14_ERX3			| \
						 AT91C_PB17_ERXCK		| \
						 AT91C_PB16_ECOL			| \
						 AT91C_PB4_ECRS			| \
						 AT91C_PB7_ERXER)
#else
#define EMAC_PIO_CFG	(AT91C_PB0_ETXCK_EREFCK | \
		AT91C_PB1_ETXEN        | \
		AT91C_PB2_ETX0         | \
		AT91C_PB3_ETX1         | \
		AT91C_PB4_ECRS         | \
		AT91C_PB5_ERX0         | \
		AT91C_PB6_ERX1         | \
		AT91C_PB7_ERXER        | \
		AT91C_PB8_EMDC         | \
		AT91C_PB9_EMDIO        | \
		AT91C_PB10_ETX2        | \
		AT91C_PB11_ETX3        | \
		AT91C_PB10_ETX2		   | \
		AT91C_PB13_ERX2        | \
		AT91C_PB14_ERX3        | \
		AT91C_PB15_ERXDV_ECRSDV| \
		AT91C_PB16_ECOL        | \
		AT91C_PB17_ERXCK)
#endif

#define RB_BUFFER_SIZE		8			/* max number of receive buffers */
#define ETH_RX_BUF_SIZE		128

#define TB_BUFFER_SIZE		4
#define ETH_TX_BUF_SIZE		(PBUF_POOL_BUFSIZE)

struct rbf_t
{
	rt_uint32_t addr;
	rt_uint32_t status;
};

static rt_uint32_t 	current_rb_index;						/* current receive buffer index */
static volatile struct rbf_t rb_descriptors[RB_BUFFER_SIZE];
static volatile struct rbf_t tb_descriptors[TB_BUFFER_SIZE];
static rt_uint8_t 	rx_buf[RB_BUFFER_SIZE][ETH_RX_BUF_SIZE] __attribute__ ((aligned (8)));
static rt_uint8_t 	tx_buf[TB_BUFFER_SIZE][ETH_TX_BUF_SIZE] __attribute__ ((aligned (8)));
static struct rt_semaphore tx_sem;

struct net_device
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/
};
static struct net_device  sam7x_dev_entry;
static struct net_device *sam7x_dev =&sam7x_dev_entry;
AT91PS_EMAC pEmac = AT91C_BASE_EMAC;

rt_inline void write_phy(rt_uint8_t addr, rt_uint32_t value)
{
	AT91C_BASE_EMAC->EMAC_MAN = ((0x01<<30) | (2 << 16) | (1 << 28) |
								 (AT91C_PHY_ADDR << 23) | (addr << 18))  | value;
	/* Wait until IDLE bit in Network Status register is cleared */
	while (!(AT91C_BASE_EMAC->EMAC_NSR & AT91C_EMAC_IDLE));
}

rt_inline rt_uint32_t read_phy(rt_uint8_t addr)
{
	AT91C_BASE_EMAC->EMAC_MAN = (0x01<<30) | (0x02 << 16) | (0x02 << 28) |
								(AT91C_PHY_ADDR << 23) | (addr << 18);

	/* Wait until IDLE bit in Network Status register is cleared */
	while (!(AT91C_BASE_EMAC->EMAC_NSR & AT91C_EMAC_IDLE));

	return (AT91C_BASE_EMAC->EMAC_MAN & 0x0000ffff);
}

rt_inline void sam7xether_reset_tx_desc(void)
{
	static rt_uint32_t index = 0;

	if(tb_descriptors[index].status & TxDESC_STATUS_USED)
	{
		while(!(tb_descriptors[index].status & TxDESC_STATUS_LAST_BUF))
		{
			index ++;
			if(index >= TB_BUFFER_SIZE)index = 0;

			tb_descriptors[index].status |= TxDESC_STATUS_USED;
		}

		index ++;
		if(index >= TB_BUFFER_SIZE)index = 0;
	}
}


/* interrupt service routing */
static void sam7xether_isr(int irq, void* param)
{
	/* Variable definitions can be made now. */
	volatile rt_uint32_t isr, rsr;
	
	/* get status */
	isr = AT91C_BASE_EMAC->EMAC_ISR;
	rsr = AT91C_BASE_EMAC->EMAC_RSR;

	if( ( isr & AT91C_EMAC_RCOMP ) || ( rsr & AT91C_EMAC_REC ) )
	{
		rt_err_t result;

		/* a frame has been received */
		result = eth_device_ready((struct eth_device*)&(sam7x_dev->parent));
		RT_ASSERT(result == RT_EOK);

		AT91C_BASE_EMAC->EMAC_RSR = AT91C_EMAC_REC;
	}

	if( isr & AT91C_EMAC_TCOMP )
	{
		/* A frame has been transmitted. Mark all the buffers as free */
		sam7xether_reset_tx_desc();

		AT91C_BASE_EMAC->EMAC_TSR = AT91C_EMAC_COMP;
	}
}

rt_inline void linksetup(void)
{
	rt_uint32_t value, tout, id1, id2;
#ifdef DM9161
	rt_uint32_t ulBMSR,ulBMCR,i;
#endif

#ifdef DM9161
  	//PHY has internal pull down : disable MII isolate
  	tout = read_phy(PHY_REG_BMCR);
  	tout = read_phy(PHY_REG_BMCR);
  	tout &= ~BMCR_ISOLATE;
  	write_phy(PHY_REG_BMCR, tout);

	/* Check if this is a RTL8201 or DM9161 PHY. */
	id1 = read_phy(PHY_REG_PHYID1);
	id2 = read_phy(PHY_REG_PHYID2);

	if (((id1 << 16) | (id2 & 0xfff0)) == MII_DM9161_ID)
	{
		rt_kprintf("read MII_DM9161_ID ok!\n");	

        tout = DM9161_NP | DM9161_TX_FDX | DM9161_TX_HDX |
               DM9161_10_FDX | DM9161_10_HDX | DM9161_AN_IEEE_802_3;
        write_phy(PHY_REG_ANAR, tout);
   	    // Wait for PHY auto negotiation completed
		i = 0;
  	    do {
    		ulBMSR = read_phy(PHY_REG_BMSR);
			ulBMSR = read_phy(PHY_REG_BMSR);
			i++;

			if(i >= 0xffff)
			   break;
  	    }while (!(ulBMSR & BMSR_ANEGCOMPLETE));

		if(i >= 0xffff)
		   rt_kprintf("PHY No Link!\n");
		else
		   rt_kprintf("PHY auto negotiation completed!\n");

		/* Update the MAC register NCFGR. */
		AT91C_BASE_EMAC->EMAC_NCFGR = 0;
		ulBMCR = read_phy(PHY_REG_BMCR);
			
	    if (ulBMCR & BMCR_ANENABLE)
	    {				
			/* AutoNegotiation is enabled. */
			if(!(ulBMSR & BMSR_ANEGCOMPLETE))
			{
			    /* Auto-negotitation in progress. */		
				rt_kprintf("Auto-negotitation in progress!\n");
			    return;			
			}		

	    	if (ulBMCR & BMCR_SPEED100) 
	    	{
		    	/* Speed 100Mbit is enabled. */
		    	AT91C_BASE_EMAC->EMAC_NCFGR |= AT91C_EMAC_SPD;
		    	    
	    	}
	    	if (ulBMCR & BMCR_FULLDPLX) 
	    	{
		    	/* Full duplex is enabled. */
		    	AT91C_BASE_EMAC->EMAC_NCFGR |= AT91C_EMAC_FD;		    
	    	}
       }
    }
#else
	/* Check if this is a RTL8201 or DM9161 PHY. */
	id1 = read_phy(PHY_REG_PHYID1);
	id2 = read_phy(PHY_REG_PHYID2);

	if (((id2 << 16) | (id1 & 0xfff0)) == MII_RTL8201_ID)
	{
	    rt_kprintf("read MII_RTL8201_ID ok!\n");	


		/* Configure the PHY device */
		/* Use autonegotiation about the link speed. */
		write_phy (PHY_REG_BMCR, PHY_AUTO_NEG);

		/* Wait to complete Auto_Negotiation. */
		for (tout = 0; tout < 0x100000; tout++)
		{
			value = read_phy (PHY_REG_BMSR);
			if (value & BMSR_ANEGCOMPLETE) break; /* autonegotiation finished. */
		}

		/* Check the link status. */
		for (tout = 0; tout < 0x10000; tout++)
		{
			value = read_phy (PHY_REG_BMSR);
			if (value & BMSR_LINKST) break; /* Link is on. */
		}
	}
	value = read_phy (PHY_REG_ANLPAR);

	/* Update the MAC register NCFGR. */
	AT91C_BASE_EMAC->EMAC_NCFGR &= ~(AT91C_EMAC_SPD | AT91C_EMAC_FD);

	/* set full duplex . */
	if (value & 0xA000) AT91C_BASE_EMAC->EMAC_NCFGR |= AT91C_EMAC_FD;
	/* set speed */
	if (value & 0xC000) AT91C_BASE_EMAC->EMAC_NCFGR |= AT91C_EMAC_SPD;
 #endif 
}

/*
 * Set the MAC address.
 */
rt_inline void update_mac_address(struct net_device* device)
{
	AT91C_BASE_EMAC->EMAC_SA1L = (device->dev_addr[3] << 24) |
								 (device->dev_addr[2] << 16) |
								 (device->dev_addr[1] << 8)  |
								 device->dev_addr[0];
	AT91C_BASE_EMAC->EMAC_SA1H = (device->dev_addr[5] << 8) |
								 device->dev_addr[4];
}

rt_inline void sam7xether_desc_init()
{
	rt_uint32_t i;

	/* Rx Buffer Descriptor initialization */
	current_rb_index = 0;
	for (i = 0; i < RB_BUFFER_SIZE; i++)
	{
		rb_descriptors[i].addr = (rt_uint32_t)&(rx_buf[i][0]);
		rb_descriptors[i].status = 0;
	}
	/* Set the WRAP bit at the end of the list descriptor. */
	rb_descriptors[RB_BUFFER_SIZE-1].addr |= 0x02;
	/* Set Rx Queue pointer to descriptor list. */
	AT91C_BASE_EMAC->EMAC_RBQP = (unsigned int)&(rb_descriptors[0]);

	/* Tx Buffer Descriptor initialization */
	for (i = 0; i < TB_BUFFER_SIZE; i++)
	{
		tb_descriptors[i].addr = (rt_uint32_t)&(tx_buf[i][0]);
		tb_descriptors[i].status = TxDESC_STATUS_USED;
	}
	/* Set the WRAP bit at the end of the list descriptor. */
	tb_descriptors[TB_BUFFER_SIZE-1].status |= TxDESC_STATUS_WRAP;
	/* Set Tx Queue pointer to descriptor list. */
	AT91C_BASE_EMAC->EMAC_TBQP = (unsigned int)&(tb_descriptors[0]);
}

/* RT-Thread Device Interface */

/* initialize the interface */
rt_err_t sam7xether_init(rt_device_t dev)
{
	rt_uint32_t i;
	
	/* enable peripheral clock for EMAC and PIO B */
	AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_PIOB | 1 << AT91C_ID_EMAC;

	/* Disable pull up on RXDV => PHY normal mode (not in test mode), */
	/* and set MII mode. PHY has internal pull down.                  */
	AT91C_BASE_PIOB->PIO_PPUDR = (1<<16) | (1 << 15);

	/* Clear PB18 <=> PHY powerdown */
	AT91C_BASE_PIOB->PIO_PER 	= 1<<18;
	AT91C_BASE_PIOB->PIO_OER 	= 1<<18;
	AT91C_BASE_PIOB->PIO_CODR 	= 1<<18;

	/* EMAC IO init for EMAC-PHY communication. */
	AT91C_BASE_PIOB->PIO_ASR = EMAC_PIO_CFG;
	AT91C_BASE_PIOB->PIO_PDR = EMAC_PIO_CFG; // Set in Periph mode

	/* Enable communication between EMAC-PHY. */
	AT91C_BASE_EMAC->EMAC_NCR   |= AT91C_EMAC_MPE;
	/* MDC = MCK/32 */
	AT91C_BASE_EMAC->EMAC_NCFGR |= 2<<10;

	/* Reset PHY */
	AT91C_BASE_PIOB->PIO_PPUDR = AT91C_PB7_ERXER;

	AT91C_BASE_RSTC->RSTC_RMR = 0xA5000000 | (0x08 << 8) ;
	AT91C_BASE_RSTC->RSTC_RCR = 0xA5000000 | AT91C_RSTC_EXTRST;

	i = 0;
	while(!(AT91C_BASE_RSTC->RSTC_RSR & AT91C_RSTC_NRSTL))
	{
	   i++;
	   if(i >= 0xfffff)
	     break;
	}

    for(i=0; i<0xfffff; i++);//* 等待一段指定的时间，使PHY就绪

	linksetup();

	rt_kprintf("linksetup ok!\n");

	/* Disable management port in MAC control register. */
	AT91C_BASE_EMAC->EMAC_NCR &= ~AT91C_EMAC_MPE;

	/* Enable EMAC in MII mode, enable clock ERXCK and ETXCK */
	AT91C_BASE_EMAC->EMAC_USRIO= AT91C_EMAC_CLKEN;

	/* Transmit and Receive disable. */
	AT91C_BASE_EMAC->EMAC_NCR &= ~(AT91C_EMAC_RE | AT91C_EMAC_TE);

	/* init descriptor */
	sam7xether_desc_init();

	/* Clear receive and transmit status registers. */
	AT91C_BASE_EMAC->EMAC_RSR  = (AT91C_EMAC_OVR | AT91C_EMAC_REC | AT91C_EMAC_BNA);
	AT91C_BASE_EMAC->EMAC_TSR  = (AT91C_EMAC_UND | AT91C_EMAC_COMP| AT91C_EMAC_BEX |
								  AT91C_EMAC_RLES| AT91C_EMAC_COL | AT91C_EMAC_UBR);

	/* Configure EMAC operation mode. */
	//AT91C_BASE_EMAC->EMAC_NCFGR |= (AT91C_EMAC_BIG | AT91C_EMAC_DRFCS);
 	//                   复制所有有效帧到接收缓冲区   *不复制FCS字段       不接收广播帧    不接收1526字节长帧                 
	AT91C_BASE_EMAC->EMAC_NCFGR |= AT91C_EMAC_CAF |AT91C_EMAC_DRFCS | AT91C_EMAC_NBC | AT91C_EMAC_BIG;
	AT91C_BASE_EMAC->EMAC_NCR   |= (AT91C_EMAC_TE  | AT91C_EMAC_RE | AT91C_EMAC_WESTAT);

	/* update MAC address */
	update_mac_address(sam7x_dev);

	/* enable interrupt */
	AT91C_BASE_EMAC->EMAC_IDR = 0x3fff;
	AT91C_BASE_EMAC->EMAC_IER = AT91C_EMAC_RCOMP | AT91C_EMAC_TCOMP;

	/* setup interrupt */
	rt_hw_interrupt_install(AT91C_ID_EMAC, sam7xether_isr, RT_NULL, "emac");
	*(volatile unsigned int*)(0xFFFFF000 + AT91C_ID_EMAC * 4) = AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL | 5;
	// AT91C_AIC_SMR(AT91C_ID_EMAC) = AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL | 5;
	rt_hw_interrupt_umask(AT91C_ID_EMAC);

	return RT_EOK;
}

/* control the interface */
rt_err_t sam7xether_control(rt_device_t dev, int cmd, void *args)
{
	switch(cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if(args) rt_memcpy(args, sam7x_dev_entry.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

/* Open the ethernet interface */
rt_err_t sam7xether_open(rt_device_t dev, rt_uint16_t oflags)
{
	return RT_EOK;
}

/* Close the interface */
rt_err_t sam7xether_close(rt_device_t dev)
{
	return RT_EOK;
}

/* Read */
rt_size_t sam7xether_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

/* Write */
rt_size_t sam7xether_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

/* See the header file for descriptions of public functions. */
void sam7xether_write_frame(rt_uint8_t *ptr, rt_uint32_t length, rt_bool_t eof)
{
	rt_uint8_t *buf_ptr;
	static rt_uint32_t current_tb_index = 0;
	rt_uint32_t is_last, tx_offset = 0, remain, pdu_length;

	while(tx_offset < length)
	{
		/* check whether buffer is available */
		while(!(tb_descriptors[current_tb_index].status & TxDESC_STATUS_USED))
		{
			/* no buffer */
			rt_thread_delay(5);
		}

		/* Get the address of the buffer from the descriptor, then copy
		the data into the buffer. */
		buf_ptr = (rt_uint8_t *)tb_descriptors[current_tb_index].addr;

		/* How much can we write to the buffer? */
		remain = length - tx_offset;
		pdu_length = (remain <= ETH_TX_BUF_SIZE)? remain : ETH_TX_BUF_SIZE;

		/* Copy the data into the buffer. */
		rt_memcpy(buf_ptr, &ptr[tx_offset], pdu_length );
		tx_offset += pdu_length;

		/* Is this the last data for the frame? */
		if((eof == RT_TRUE) && ( tx_offset >= length )) is_last = TxDESC_STATUS_LAST_BUF;
		else is_last = 0;

		/* Fill out the necessary in the descriptor to get the data sent,
		then move to the next descriptor, wrapping if necessary. */
		if(current_tb_index >= (TB_BUFFER_SIZE - 1))
		{
			tb_descriptors[current_tb_index].status = ( pdu_length & TxDESC_STATUS_BUF_SIZE )
					| is_last
					| TxDESC_STATUS_WRAP;
			current_tb_index = 0;
		}
		else
		{
			tb_descriptors[current_tb_index].status = ( pdu_length & TxDESC_STATUS_BUF_SIZE )
					| is_last;
			current_tb_index++;
		}

		/* If this is the last buffer to be sent for this frame we can
		start the transmission. */
		if(is_last)
		{
			AT91C_BASE_EMAC->EMAC_NCR |= AT91C_EMAC_TSTART;
		}
	}
}

/* ethernet device interface */
/*
 * Transmit packet.
 */
rt_err_t sam7xether_tx( rt_device_t dev, struct pbuf* p)
{
	struct pbuf* q;

	/* lock tx operation */
	rt_sem_take(&tx_sem, RT_WAITING_FOREVER);
	
	for (q = p; q != NULL; q = q->next)
	{
		if (q->next == RT_NULL) sam7xether_write_frame(q->payload, q->len, RT_TRUE);
		else sam7xether_write_frame(q->payload, q->len, RT_FALSE);
	}

	rt_sem_release(&tx_sem);

	return 0;
}

void sam7xether_read_frame(rt_uint8_t* ptr, rt_uint32_t section_length, rt_uint32_t total)
{
	static rt_uint8_t* src_ptr;
	register rt_uint32_t buf_remain, section_remain;
	static rt_uint32_t section_read = 0, buf_offset = 0, frame_read = 0;

	if(ptr == RT_NULL)
	{
		/* Reset our state variables ready for the next read from this buffer. */
		src_ptr = (rt_uint8_t *)(rb_descriptors[current_rb_index].addr & RxDESC_FLAG_ADDR_MASK);
		frame_read = (rt_uint32_t)0;
		buf_offset = (rt_uint32_t)0;
	}
	else
	{
		/* Loop until we have obtained the required amount of data. */
		section_read = 0;
		while( section_read < section_length )
		{
			buf_remain = (ETH_RX_BUF_SIZE - buf_offset);
			section_remain = section_length - section_read;

			if( section_remain > buf_remain )
			{
				/* more data on section than buffer size */
				rt_memcpy(&ptr[ section_read ], &src_ptr[buf_offset], buf_remain);
				section_read += buf_remain;
				frame_read += buf_remain;

				/* free buffer */
				rb_descriptors[current_rb_index].addr &= ~RxDESC_FLAG_OWNSHIP;

				/* move to the next frame. */
				current_rb_index++;
				if(current_rb_index >= RB_BUFFER_SIZE) current_rb_index = 0;

				/* Reset the variables for the new buffer. */
				src_ptr = (rt_uint8_t *)(rb_descriptors[current_rb_index].addr & RxDESC_FLAG_ADDR_MASK);
				buf_offset = 0;
			}
			else
			{
				/* more data on buffer than section size */
				rt_memcpy(&ptr[section_read], &src_ptr[buf_offset], section_remain);
				buf_offset += section_remain;
				section_read += section_remain;
				frame_read += section_remain;

				/* finish this read */
				if((buf_offset >= ETH_RX_BUF_SIZE) || (frame_read >= total))
				{
					/* free buffer */
					rb_descriptors[current_rb_index].addr &= ~(RxDESC_FLAG_OWNSHIP);

					/* move to the next frame. */
					current_rb_index++;
					if( current_rb_index >= RB_BUFFER_SIZE ) current_rb_index = 0;

					src_ptr = (rt_uint8_t*)(rb_descriptors[current_rb_index].addr & RxDESC_FLAG_ADDR_MASK);
					buf_offset = 0;
				}
			}
		}
	}
}

struct pbuf *sam7xether_rx(rt_device_t dev)
{
	struct pbuf *p = RT_NULL;

	/* skip fragment frame */
	while((rb_descriptors[current_rb_index].addr & RxDESC_FLAG_OWNSHIP)
			&& !(rb_descriptors[current_rb_index].status & RxDESC_STATUS_FRAME_START))
	{
		rb_descriptors[current_rb_index].addr &= (~RxDESC_FLAG_OWNSHIP);

		current_rb_index++;
		if(current_rb_index >= RB_BUFFER_SIZE) current_rb_index = 0;
	}

	if ((rb_descriptors[current_rb_index].addr & RxDESC_FLAG_OWNSHIP))
	{
		struct pbuf* q;
		rt_uint32_t index, pkt_len = 0;

		/* first of all, find the frame length */
		index = current_rb_index;
		while (rb_descriptors[index].addr & RxDESC_FLAG_OWNSHIP)
		{
			pkt_len = rb_descriptors[index].status & RxDESC_STATUS_BUF_SIZE;
			if (pkt_len > 0) break;

			index ++;
			if (index >= RB_BUFFER_SIZE) index = 0;
		}

		if (pkt_len)
		{
			//p = pbuf_alloc(PBUF_LINK, pkt_len, PBUF_RAM);
			p = pbuf_alloc(PBUF_RAW, pkt_len, PBUF_POOL);
			if(p != RT_NULL)
			{
				sam7xether_read_frame(RT_NULL, 0, pkt_len);
				for(q = p; q != RT_NULL; q= q->next)
					sam7xether_read_frame(q->payload, q->len, pkt_len);
			}
			else
			{
				rt_kprintf("no memory in pbuf\n");
			}
		}
	}

	/* enable interrupt */
	AT91C_BASE_EMAC->EMAC_IER = AT91C_EMAC_RCOMP;

	return p;
}

int sam7xether_register(char *name)
{
	rt_err_t result;

	/* init rt-thread device interface */
	sam7x_dev_entry.parent.parent.init		= sam7xether_init;
	sam7x_dev_entry.parent.parent.open		= sam7xether_open;
	sam7x_dev_entry.parent.parent.close		= sam7xether_close;
	sam7x_dev_entry.parent.parent.read		= sam7xether_read;
	sam7x_dev_entry.parent.parent.write		= sam7xether_write;
	sam7x_dev_entry.parent.parent.control	= sam7xether_control;
	sam7x_dev_entry.parent.eth_rx			= sam7xether_rx;
	sam7x_dev_entry.parent.eth_tx			= sam7xether_tx;

	/* Update MAC address */
	sam7x_dev_entry.dev_addr[0] = 0x1e;
	sam7x_dev_entry.dev_addr[1] = 0x30;
	sam7x_dev_entry.dev_addr[2] = 0x6c;
	sam7x_dev_entry.dev_addr[3] = 0xa2;
	sam7x_dev_entry.dev_addr[4] = 0x45;
	sam7x_dev_entry.dev_addr[5] = 0x5e;
	/* update mac address */
	update_mac_address(sam7x_dev);

	rt_sem_init(&tx_sem, "emac", 1, RT_IPC_FLAG_FIFO);
	
	result = eth_device_init(&(sam7x_dev->parent), (char*)name);
	RT_ASSERT(result == RT_EOK);

	return RT_EOK;
}
