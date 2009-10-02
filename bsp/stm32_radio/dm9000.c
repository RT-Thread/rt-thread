#include <rtthread.h>
#include "dm9000.h"

#include <netif/ethernetif.h>
#include "lwipopts.h"

/*
 * DM9000 interrupt line is connected to PF7
 */
//--------------------------------------------------------
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

struct dm9000_rxhdr
{
    rt_uint8_t      RxPktReady;
    rt_uint8_t      RxStatus;
    rt_uint16_t     RxLen;
} __attribute__((__packed__));

struct rt_dm9000_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

    enum DM9000_TYPE type;
    rt_uint8_t imr_all;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/
};
static struct rt_dm9000_eth dm9000_device;

void delay_ms(rt_uint32_t dt)
{
}

/* Read a byte from I/O port */
rt_inline rt_uint8_t dm9000_io_read(rt_uint16_t reg)
{
    ETH_ADDR = reg;
    return (rt_uint8_t) ETH_DATA;
}

/* Write a byte to I/O port */
rt_inline void dm9000_io_write(rt_uint16_t reg, rt_uint16_t value)
{
    ETH_ADDR = reg;
    ETH_DATA = data;
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
    rt_uint32_t int_status;

    /* Disable all interrupts */
    dm9000_io_write(DM9000_IMR, IMR_PAR);

    /* Got DM9000 interrupt status */
    int_status = ior(DM9000_ISR);               /* Got ISR */
    dm9000_io_write(DM9000_ISR, int_status);    /* Clear ISR status */

    /* Received the coming packet */
    if (int_status & ISR_PRS)
    {
        rt_err_t result;

        /* a frame has been received */
        result = eth_device_ready(&(dm9000_device.parent));
        RT_ASSERT(result == RT_EOK);
    }

    /* Transmit Interrupt check */
    if (int_status & ISR_PTS)
    {
        /* transmit done */
        int tx_status = dm9000_io_read(DM9000_NSR);    /* Got TX status */

        if (tx_status & (NSR_TX2END | NSR_TX1END))
        {
            /* One packet sent complete */
        }
    }

    /* Re-enable interrupt mask */
    dm9000_io_write(DM9000_IMR, db->imr_all);
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
        return -RT_ERROR;
    }

	/* GPIO0 on pre-activate PHY */
	dm9000_io_write(DM9000_GPR, 0x00);	            /*REG_1F bit0 activate phyxcer */
	dm9000_io_write(DM9000_GPCR, GPCR_GEP_CNTL);    /* Let GPIO0 output */
    dm9000_io_write(DM9000_GPR, 0);                 /* Enable PHY */

	/* Set PHY */
	phy_mode_set(DM9000_AUTO);

	/* Program operating register */
	dm9000_io_write(DM9000_NCR, 0x0);	/* only intern phy supported by now */
	dm9000_io_write(DM9000_TCR, 0);	    /* TX Polling clear */
	dm9000_io_write(DM9000_BPTR, 0x3f);	/* Less 3Kb, 200us */
	dm9000_io_write(DM9000_FCTR, FCTR_HWOT(3) | FCTR_LWOT(8));	/* Flow Control : High/Low Water */
	dm9000_io_write(DM9000_FCR, 0x0);	/* SH FIXME: This looks strange! Flow Control */
	dm9000_io_write(DM9000_SMCR, 0);	/* Special Mode */
	dm9000_io_write(DM9000_NSR, NSR_WAKEST | NSR_TX2END | NSR_TX1END);	/* clear TX status */
	dm9000_io_write(DM9000_ISR, 0x0f);	/* Clear interrupt status */

	/* set mac address */
	for (i = 0, oft = 0x10; i < 6; i++, oft++)
		dm9000_io_write(oft, dm9000_device->dev_addr[i]);
	for (i = 0, oft = 0x16; i < 8; i++, oft++)
		dm9000_io_write(oft, 0xff);

	/* Activate DM9000 */
	dm9000_io_write(DM9000_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN);	/* RX enable */

	i = 0;
	while (!(phy_read(1) & 0x20))
	{
        /* autonegation complete bit */
		delay_ms(1000);
		i++;
		if (i == 10000)
		{
			rt_kprintf("could not establish link\n");
			return 0;
		}
	}

	/* see what we've got */
	lnk = phy_read(17) >> 12;
	rt_kprintf("operating at ");
	switch (lnk) {
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

	dm9000_io_write(DM9000_IMR, dm9000_device.imr_all);	/* Enable TX/RX interrupt mask */

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

static rt_size_t rt_dm9000_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_dm9000_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_dm9000_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch(cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if(args) rt_memcpy(args, dm9000_device.dev_addr, 6);
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
	struct pbuf* q;
	rt_uint32_t len;
	rt_uint16_t* ptr;

    /* Move data to DM9000 TX RAM */
    dm9000_io_write(DM9000_MWCMD, DM9000_IO);

	for (q = p; q != NULL; q = q->next)
	{
		len = q->len;
		ptr = q->payload;

        /* use 16bit mode to write data to DM9000 RAM */
        while (len)
        {
            dm9000_io_write(*ptr, DM9000_DATA);
            ptr ++; len -= 2;
        }
	}

    if (p->tot_len < 64) /* add pading */
    {
    }

    /* Set TX length to DM9000 */
    dm9000_io_write(DM9000_TXPLL, p->tot_len & 0xff);
    dm9000_io_write(DM9000_TXPLH, (p->tot_len >> 8) & 0xff);

	return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_dm9000_rx(rt_device_t dev)
{
    struct pbuf* p;
	rt_uint32_t len;

    /* init p pointer */
    p = RT_NULL;

	/* Check packet ready or not */
	dm9000_io_read(DM9000_MRCMDX);	    /* Dummy read */
	len = dm9000_io_read(DM9000_DATA);	/* Got most updated data */
	if (len)
    {
        rt_uint16_t rx_status, rx_len;
        rt_uint16_t* data;

		dm9000_io_write(DM9000_RCR, 0x00);	/* Stop Device */
		dm9000_io_write(DM9000_ISR, 0x80);	/* Stop INT request */

        /* A packet ready now  & Get status/length */
        DM9000_outb(DM9000_MRCMD, DM9000_IO);

        rx_status = dm9000_io_write(DM9000_DATA);
        rx_len = dm9000_io_write(DM9000_DATA);

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, rx_len, PBUF_RAM);
        if (p != RT_NULL)
        {
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                data = (rt_uint16_t*)q->payload;
                len = q->len;

                while (len)
                {
                    *data = dm9000_io_write(DM9000_DATA);
                    data ++; len -= 2;
                }
            }
        }
        else
        {
            rt_uint16_t dummy;

            /* no pbuf, discard data from DM9000 */
            data = &dummy;
            while (rx_len)
            {
                *data = dm9000_io_write(DM9000_DATA);
                rx_len -= 2;
            }
        }

        if ((rx_status & 0xbf00) || (rx_len < 0x40)
            || (rx_len > DM9000_PKT_MAX))
        {
            if (rx_status & 0x100)
            {
                rt_printf("rx fifo error\n");
            }
            if (rx_status & 0x200) {
                rt_printf("rx crc error\n");
            }
            if (rx_status & 0x8000)
            {
                rt_printf("rx length error\n");
            }
            if (rx_len > DM9000_PKT_MAX)
            {
                rt_printf("rx length too big\n");
                dm9000_reset();
            }

            /* it issues an error, release pbuf */
            pbuf_free(p);
            p = RT_NULL;
        }
    }
    else
    {
        /* restore interrupt */
        dm9000_io_write(DM9000_IMR, dm9000_device.imr_all);
    }

    return p;
}
{
	u8 rxbyte, *rdptr = (u8 *) NetRxPackets[0];
	u16 RxStatus, RxLen = 0;
	u32 tmplen, i;


	/* Status check: this byte must be 0 or 1 */
	if (rxbyte > 1) {
		DM9000_iow(DM9000_RCR, 0x00);	/* Stop Device */
		DM9000_iow(DM9000_ISR, 0x80);	/* Stop INT request */
		DM9000_DBG("rx status check: %d\n", rxbyte);
	}

	/* A packet ready now  & Get status/length */
	DM9000_outb(DM9000_MRCMD, DM9000_IO);

	RxStatus = DM9000_inw(DM9000_DATA);
	RxLen = DM9000_inw(DM9000_DATA);

	/* Read received packet from RX SRAM */
	tmplen = (RxLen + 1) / 2;
	for (i = 0; i < tmplen; i++)
		((u16 *) rdptr)[i] = DM9000_inw(DM9000_DATA);

	if ((RxStatus & 0xbf00) || (RxLen < 0x40)
	    || (RxLen > DM9000_PKT_MAX))
    {
		if (RxStatus & 0x100)
        {
			rt_printf("rx fifo error\n");
		}
		if (RxStatus & 0x200) {
			rt_printf("rx crc error\n");
		}
		if (RxStatus & 0x8000)
		{
			rt_printf("rx length error\n");
		}
		if (RxLen > DM9000_PKT_MAX)
        {
			rt_printf("rx length too big\n");
			dm9000_reset();
		}
	}
    else
    {
		/* Pass to upper layer */
		DM9000_DBG("passing packet to upper layer\n");
		NetReceive(NetRxPackets[0], RxLen);

		return RxLen;
	}
}

void rt_hw_dm9000_init()
{
    dm9000_device.type    = TYPE_DM9000A;
    dm9000_device.imr_all = IMR_PAR | IMR_PTM | IMR_PRM;

	dm9000_device.parent.parent.init       = rt_dm9000_init;
	dm9000_device.parent.parent.open       = rt_dm9000_open;
	dm9000_device.parent.parent.close      = rt_dm9000_close;
	dm9000_device.parent.parent.read       = rt_dm9000_read;
	dm9000_device.parent.parent.write      = rt_dm9000_write;
	dm9000_device.parent.parent.control    = rt_dm9000_control;
	dm9000_device.parent.parent.private    = RT_NULL;

	dm9000_device.parent.eth_rx     = rt_dm9000_rx;
	dm9000_device.parent.eth_tx     = rt_dm9000_tx;

	rt_device_register((rt_device_t)&dm9000_device,
		"E0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void dm9000(void)
{
	rt_kprintf("\n");
	rt_kprintf("NCR   (0x00): %02x\n", dm9000_io_read(0));
	rt_kprintf("NSR   (0x01): %02x\n", dm9000_io_read(1));
	rt_kprintf("TCR   (0x02): %02x\n", dm9000_io_read(2));
	rt_kprintf("TSRI  (0x03): %02x\n", dm9000_io_read(3));
	rt_kprintf("TSRII (0x04): %02x\n", dm9000_io_read(4));
	rt_kprintf("RCR   (0x05): %02x\n", dm9000_io_read(5));
	rt_kprintf("RSR   (0x06): %02x\n", dm9000_io_read(6));
	rt_kprintf("ISR   (0xFE): %02x\n", dm9000_io_read(ISR));
	rt_kprintf("\n");
}

#endif
