#ifndef __DM9000_H__
#define __DM9000_H__

#define DM9000_IO_BASE		0x20000300
#define DM9000_DATA_BASE	0x20000304

#define DM9000_IO 			(*((volatile rt_uint16_t *) DM9000_IO_BASE))    // CMD = 0
#define DM9000_DATA 		(*((volatile rt_uint16_t *) DM9000_DATA_BASE))  // CMD = 1

#define DM9000_inb(r) 		(*(volatile rt_uint8_t  *)r)
#define DM9000_outb(r, d) 	(*(volatile rt_uint8_t  *)r = d)
#define DM9000_inw(r) 		(*(volatile rt_uint16_t *)r)
#define DM9000_outw(r, d) 	(*(volatile rt_uint16_t *)r = d)

#define DM9000_ID		    0x90000A46  /* DM9000 ID */
#define DM9000_PKT_MAX		1536	    /* Received packet max size */
#define DM9000_PKT_RDY		0x01	    /* Packet ready to receive */

#define DM9000_NCR          0x00
#define DM9000_NSR          0x01
#define DM9000_TCR          0x02
#define DM9000_TSR1         0x03
#define DM9000_TSR2         0x04
#define DM9000_RCR          0x05
#define DM9000_RSR          0x06
#define DM9000_ROCR         0x07
#define DM9000_BPTR         0x08
#define DM9000_FCTR         0x09
#define DM9000_FCR          0x0A
#define DM9000_EPCR         0x0B
#define DM9000_EPAR         0x0C
#define DM9000_EPDRL        0x0D
#define DM9000_EPDRH        0x0E
#define DM9000_WCR          0x0F

#define DM9000_PAR          0x10
#define DM9000_MAR          0x16

#define DM9000_GPCR         0x1e
#define DM9000_GPR          0x1f
#define DM9000_TRPAL        0x22
#define DM9000_TRPAH        0x23
#define DM9000_RWPAL        0x24
#define DM9000_RWPAH        0x25

#define DM9000_VIDL         0x28
#define DM9000_VIDH         0x29
#define DM9000_PIDL         0x2A
#define DM9000_PIDH         0x2B

#define DM9000_CHIPR        0x2C
#define DM9000_TCR2			0x2D
#define DM9000_OTCR			0x2E
#define DM9000_SMCR         0x2F

#define DM9000_ETCR			0x30	/* early transmit control/status register */
#define DM9000_CSCR			0x31	/* check sum control register */
#define DM9000_RCSSR		0x32	/* receive check sum status register */

#define DM9000_MRCMDX       0xF0
#define DM9000_MRCMD        0xF2
#define DM9000_MRRL         0xF4
#define DM9000_MRRH         0xF5
#define DM9000_MWCMDX       0xF6
#define DM9000_MWCMD        0xF8
#define DM9000_MWRL         0xFA
#define DM9000_MWRH         0xFB
#define DM9000_TXPLL        0xFC
#define DM9000_TXPLH        0xFD
#define DM9000_ISR          0xFE
#define DM9000_IMR          0xFF

#define CHIPR_DM9000A       0x19
#define CHIPR_DM9000B       0x1B

#define NCR_EXT_PHY         (1<<7)
#define NCR_WAKEEN          (1<<6)
#define NCR_FCOL            (1<<4)
#define NCR_FDX             (1<<3)
#define NCR_LBK             (3<<1)
#define NCR_RST             (1<<0)

#define NSR_SPEED           (1<<7)
#define NSR_LINKST          (1<<6)
#define NSR_WAKEST          (1<<5)
#define NSR_TX2END          (1<<3)
#define NSR_TX1END          (1<<2)
#define NSR_RXOV            (1<<1)

#define TCR_TJDIS           (1<<6)
#define TCR_EXCECM          (1<<5)
#define TCR_PAD_DIS2        (1<<4)
#define TCR_CRC_DIS2        (1<<3)
#define TCR_PAD_DIS1        (1<<2)
#define TCR_CRC_DIS1        (1<<1)
#define TCR_TXREQ           (1<<0)

#define TSR_TJTO            (1<<7)
#define TSR_LC              (1<<6)
#define TSR_NC              (1<<5)
#define TSR_LCOL            (1<<4)
#define TSR_COL             (1<<3)
#define TSR_EC              (1<<2)

#define RCR_WTDIS           (1<<6)
#define RCR_DIS_LONG        (1<<5)
#define RCR_DIS_CRC         (1<<4)
#define RCR_ALL             (1<<3)
#define RCR_RUNT            (1<<2)
#define RCR_PRMSC           (1<<1)
#define RCR_RXEN            (1<<0)

#define RSR_RF              (1<<7)
#define RSR_MF              (1<<6)
#define RSR_LCS             (1<<5)
#define RSR_RWTO            (1<<4)
#define RSR_PLE             (1<<3)
#define RSR_AE              (1<<2)
#define RSR_CE              (1<<1)
#define RSR_FOE             (1<<0)

#define FCTR_HWOT(ot)       (( ot & 0xf ) << 4 )
#define FCTR_LWOT(ot)       ( ot & 0xf )

#define IMR_PAR             (1<<7)
#define IMR_ROOM            (1<<3)
#define IMR_ROM             (1<<2)
#define IMR_PTM             (1<<1)
#define IMR_PRM             (1<<0)

#define ISR_ROOS            (1<<3)
#define ISR_ROS             (1<<2)
#define ISR_PTS             (1<<1)
#define ISR_PRS             (1<<0)
#define ISR_CLR_STATUS      (ISR_ROOS | ISR_ROS | ISR_PTS | ISR_PRS)

#define EPCR_REEP           (1<<5)
#define EPCR_WEP            (1<<4)
#define EPCR_EPOS           (1<<3)
#define EPCR_ERPRR          (1<<2)
#define EPCR_ERPRW          (1<<1)
#define EPCR_ERRE           (1<<0)

#define GPCR_GEP_CNTL       (1<<0)

int rt_hw_dm9000_init(void);

#endif
