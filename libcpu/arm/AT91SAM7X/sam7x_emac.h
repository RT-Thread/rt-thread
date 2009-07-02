#ifndef __SAM7X_EMAC_H__
#define __SAM7X_EMAC_H__

#define AT91C_PHY_ADDR      0x01
#define MII_RTL8201_ID		0x82010000

/* RTL8201 PHY registers. */
#define PHY_REG_BMCR        0x00        /* Basic mode control register       */
#define PHY_REG_BMSR        0x01        /* Basic mode status register        */
#define PHY_REG_PHYID1      0x02        /* PHY ID identifier #1              */
#define PHY_REG_PHYID2      0x03        /* PHY ID identifier #2              */
#define PHY_REG_ANAR        0x04        /* AutoNegotiation Advertisement reg.*/
#define PHY_REG_ANLPAR      0x05        /* AutoNeg.Link partner ability reg  */
#define PHY_REG_ANER        0x06        /* AutoNeg. Expansion register       */
#define PHY_REG_DSCR        0x10        /* DAVICOM Specified Config. reg     */
#define PHY_REG_DSCSR       0x11        /* DAVICOM Spec. Config/Status reg   */
#define PHY_REG_10BTCSR     0x12        /* 10BASET Configuration/Status reg  */
#define PHY_REG_PWDOR       0x13        /* Power Down Control Register       */
#define PHY_REG_SCR         0x14        /* Specified Config register         */
#define PHY_REG_INTR        0x15        /* Interrupt register                */
#define PHY_REG_RECR        0x16        /* Receive Error Counter register    */
#define PHY_REG_DISCR       0x17        /* Disconnect Counter register       */
#define PHY_REG_RLSR        0x18        /* Hardware Reset Latch State reg.   */

#define PHY_FULLD_100M      0x2100      /* Full Duplex 100Mbit               */
#define PHY_HALFD_100M      0x2000      /* Half Duplex 100Mbit               */
#define PHY_FULLD_10M       0x0100      /* Full Duplex 10Mbit                */
#define PHY_HALFD_10M       0x0000      /* Half Duplex 10MBit                */
#define PHY_AUTO_NEG        0x3000      /* Select Auto Negotiation           */

/* Basic mode status register. */
#define BMSR_ERCAP          0x0001      /* Ext-reg capability                */
#define BMSR_JCD            0x0002      /* Jabber detected                   */
#define BMSR_LINKST         0x0004      /* Link status                       */
#define BMSR_ANEGCAPABLE    0x0008      /* Able to do auto-negotiation       */
#define BMSR_RFAULT         0x0010      /* Remote fault detected             */
#define BMSR_ANEGCOMPLETE   0x0020      /* Auto-negotiation complete         */
#define BMSR_MIIPRESUP      0x0040      /* MII Frame Preamble Suppression    */
#define BMSR_RESV           0x0780      /* Unused...                         */
#define BMSR_10HALF         0x0800      /* Can do 10mbps, half-duplex        */
#define BMSR_10FULL         0x1000      /* Can do 10mbps, full-duplex        */
#define BMSR_100HALF        0x2000      /* Can do 100mbps, half-duplex       */
#define BMSR_100FULL        0x4000      /* Can do 100mbps, full-duplex       */
#define BMSR_100BASE4       0x8000      /* Can do 100mbps, 4k packets        */

#define RxDESC_FLAG_ADDR_MASK		0xfffffffc
#define	RxDESC_FLAG_WARP			0x00000002
#define	RxDESC_FLAG_OWNSHIP			0x00000001
#define RxDESC_STATUS_BUF_SIZE		(0x00000FFF)
#define RxDESC_STATUS_FRAME_START	(1U << 14)
#define RxDESC_STATUS_FRAME_END		(1U << 15)

#define TxDESC_STATUS_BUF_SIZE		(0x000007FF)
#define TxDESC_STATUS_LAST_BUF		(1U << 15)
#define	TxDESC_STATUS_NO_CRC		(1U << 16)
#define	TxDESC_STATUS_BUF_EXHAUSTED	(1U << 27)
#define	TxDESC_STATUS_Tx_UNDERRUN	(1U << 28)
#define	TxDESC_STATUS_Tx_ERROR		(1U << 29)
#define	TxDESC_STATUS_WRAP			(1U << 30)
#define	TxDESC_STATUS_USED			(1U << 31)

int sam7xether_register(char *name);

#endif
