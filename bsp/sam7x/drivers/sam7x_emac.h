#ifndef __SAM7X_EMAC_H__
#define __SAM7X_EMAC_H__

//#define DM9161
#define RTL8201 

#ifdef 	 DM9161
   #define AT91C_PHY_ADDR	31
#else
#define AT91C_PHY_ADDR      0x01
#endif

#define MII_DM9161_ID       0x0181b8a0
#define MII_RTL8201_ID      0x82010000

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

/* Basic mode control register. */
#define BMCR_RESV               0x007f  /* Unused...                   */
#define BMCR_CTST               0x0080  /* Collision test              */
#define BMCR_FULLDPLX           0x0100  /* Full duplex                 */
#define BMCR_ANRESTART          0x0200  /* Auto negotiation restart    */
#define BMCR_ISOLATE            0x0400  /* Disconnect DP83840 from MII */
#define BMCR_PDOWN              0x0800  /* Powerdown the DP83840       */
#define BMCR_ANENABLE           0x1000  /* Enable auto negotiation     */
#define BMCR_SPEED100           0x2000  /* Select 100Mbps              */
#define BMCR_LOOPBACK           0x4000  /* TXD loopback bits           */
#define BMCR_RESET              0x8000  /* Reset the DP83840           */

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

//----dm9161 define----
#define DM9161_RESET             (1 << 15) // 1= Software Reset; 0=Normal Operation
#define DM9161_LOOPBACK          (1 << 14) // 1=loopback Enabled; 0=Normal Operation
#define DM9161_SPEED_SELECT      (1 << 13) // 1=100Mbps; 0=10Mbps
#define DM9161_AUTONEG           (1 << 12) // Auto-negotiation Enable
#define DM9161_POWER_DOWN        (1 << 11) // 1=Power down 0=Normal operation
#define DM9161_ISOLATE           (1 << 10) // 1 = Isolates 0 = Normal operation
#define DM9161_RESTART_AUTONEG   (1 << 9)  // 1 = Restart auto-negotiation 0 = Normal operation
#define DM9161_DUPLEX_MODE       (1 << 8)  // 1 = Full duplex operation 0 = Normal operation
#define DM9161_COLLISION_TEST    (1 << 7)  // 1 = Collision test enabled 0 = Normal operation

#define DM9161_NP               (1 << 15) // Next page Indication
#define DM9161_ACK              (1 << 14) // Acknowledge
#define DM9161_RF               (1 << 13) // Remote Fault
//      Reserved                12 to 11  // Write as 0, ignore on read
#define DM9161_FCS              (1 << 10) // Flow Control Support
#define DM9161_T4               (1 << 9)  // 100BASE-T4 Support
#define DM9161_TX_FDX           (1 << 8)  // 100BASE-TX Full Duplex Support
#define DM9161_TX_HDX           (1 << 7)  // 100BASE-TX Support
#define DM9161_10_FDX           (1 << 6)  // 10BASE-T Full Duplex Support
#define DM9161_10_HDX           (1 << 5)  // 10BASE-T Support
//      Selector                 4 to 0   // Protocol Selection Bits
#define DM9161_AN_IEEE_802_3      0x0001

int sam7xether_register(char *name);

#endif
