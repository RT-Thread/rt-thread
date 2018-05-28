/*
 * File      : nuc97x_ethernet.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */


#ifndef PLATFORM_NUC97X_ETHERNET_H_
#define PLATFORM_NUC97X_ETHERNET_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Generic MII registers. */
#define MII_BMCR            0x00        /* Basic mode control register */
#define MII_BMSR            0x01        /* Basic mode status register  */
#define MII_PHYSID1         0x02        /* PHYS ID 1                   */
#define MII_PHYSID2         0x03        /* PHYS ID 2                   */
#define MII_ADVERTISE       0x04        /* Advertisement control reg   */
#define MII_LPA             0x05        /* Link partner ability reg    */
#define MII_EXPANSION       0x06        /* Expansion register          */
#define MII_DCOUNTER        0x12        /* Disconnect counter          */
#define MII_FCSCOUNTER      0x13        /* False carrier counter       */
#define MII_NWAYTEST        0x14        /* N-way auto-neg test reg     */
#define MII_RERRCOUNTER     0x15        /* Receive error counter       */
#define MII_SREVISION       0x16        /* Silicon revision            */
#define MII_RESV1           0x17        /* Reserved...                 */
#define MII_LBRERROR        0x18        /* Lpback, rx, bypass error    */
#define MII_PHYADDR         0x19        /* PHY address                 */
#define MII_RESV2           0x1a        /* Reserved...                 */
#define MII_TPISTATUS       0x1b        /* TPI status for 10mbps       */
#define MII_NCONFIG         0x1c        /* Network interface config    */

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

/* Basic mode status register. */
#define BMSR_ERCAP              0x0001  /* Ext-reg capability          */
#define BMSR_JCD                0x0002  /* Jabber detected             */
#define BMSR_LSTATUS            0x0004  /* Link status                 */
#define BMSR_ANEGCAPABLE        0x0008  /* Able to do auto-negotiation */
#define BMSR_RFAULT             0x0010  /* Remote fault detected       */
#define BMSR_ANEGCOMPLETE       0x0020  /* Auto-negotiation complete   */
#define BMSR_RESV               0x07c0  /* Unused...                   */
#define BMSR_10HALF             0x0800  /* Can do 10mbps, half-duplex  */
#define BMSR_10FULL             0x1000  /* Can do 10mbps, full-duplex  */
#define BMSR_100HALF            0x2000  /* Can do 100mbps, half-duplex */
#define BMSR_100FULL            0x4000  /* Can do 100mbps, full-duplex */
#define BMSR_100BASE4           0x8000  /* Can do 100mbps, 4k packets  */

/* Advertisement control register. */
#define ADVERTISE_SLCT          0x001f  /* Selector bits               */
#define ADVERTISE_CSMA          0x0001  /* Only selector supported     */
#define ADVERTISE_10HALF        0x0020  /* Try for 10mbps half-duplex  */
#define ADVERTISE_10FULL        0x0040  /* Try for 10mbps full-duplex  */
#define ADVERTISE_100HALF       0x0080  /* Try for 100mbps half-duplex */
#define ADVERTISE_100FULL       0x0100  /* Try for 100mbps full-duplex */
#define ADVERTISE_100BASE4      0x0200  /* Try for 100mbps 4k packets  */
#define ADVERTISE_RESV          0x1c00  /* Unused...                   */
#define ADVERTISE_RFAULT        0x2000  /* Say we can detect faults    */
#define ADVERTISE_LPACK         0x4000  /* Ack link partners response  */
#define ADVERTISE_NPAGE         0x8000  /* Next page bit               */

/* mac controller bit */
#define MCMDR_RXON      0x01
#define MCMDR_ACP       (0x01 << 3)
#define MCMDR_SPCRC     (0x01 << 5)
#define MCMDR_MGPWAKE       (0x01 << 6)
#define MCMDR_TXON      (0x01 << 8)
#define MCMDR_FDUP      (0x01 << 18)
//#define MCMDR_ENMDC       (0x01 << 19)
#define MCMDR_OPMOD     (0x01 << 20)
#define MCMDR_SWR       (0x01 << 24)

/* cam command regiser */
#define CAMCMR_AUP      0x01
#define CAMCMR_AMP      (0x01 << 1)
#define CAMCMR_ABP      (0x01 << 2)
#define CAMCMR_CCAM     (0x01 << 3)
#define CAMCMR_ECMP     (0x01 << 4)
#define CAM0EN          0x01

/* mac mii controller bit */
#define MDCON           (0x01 << 19)
//#define PHYAD         (0x01 << 8)
#define PHYWR           (0x01 << 16)
#define PHYBUSY         (0x01 << 17)
#define CAM_ENTRY_SIZE      0x08

/* rx and tx status */
#define TXDS_TXCP       (0x01 << 19)
#define RXDS_CRCE       (0x01 << 17)
#define RXDS_PTLE       (0x01 << 19)
#define RXDS_RXGD       (0x01 << 20)
#define RXDS_ALIE       (0x01 << 21)
#define RXDS_RP         (0x01 << 22)

/* mac interrupt status*/
#define MISTA_EXDEF     (0x01 << 19)
#define MISTA_TXBERR    (0x01 << 24)
#define MISTA_TDU       (0x01 << 23)
#define MISTA_RDU       (0x01 << 10)
#define MISTA_RXBERR    (0x01 << 11)
#define MISTA_WOL       (0x01 << 15)
#define MISTA_RXGD      (0x01 << 4)

/* MIIDA Register Bits Define */
#define MIIDA_WRITE_MSK     (0x01 << 16)
#define MIIDA_BUSY_MSK      (0x01 << 17)
#define MIIDA_MDCON_MSK     (0x01 << 19)

/* MIEN Register Bits Define */
#define ENSTART         0x01
#define MIEN_RXIEN      (0x01 <<  0)
#define MIEN_CRCEIEN    (0x01 <<  1)
#define MIEN_RXOVIEN    (0x01 <<  2)
#define MIEN_LPIEN      (0x01 <<  3)
#define MIEN_RXGDIEN    (0x01 <<  4)
#define MIEN_ALIEIEN    (0x01 <<  5)
#define MIEN_RPIEN      (0x01 <<  6)
#define MIEN_MMPIEN     (0x01 <<  7)
#define MIEN_MFLEIEN    (0x01 <<  8)
#define MIEN_DENIEN     (0x01 <<  9)
#define MIEN_RDUIEN     (0x01 << 10)
#define MIEN_RXBEIEN    (0x01 << 11)
#define MIEN_CFRIEN     (0x01 << 14)
#define MIEN_WOLIEN     (0x01 << 15)
#define MIEN_TXIEN      (0x01 << 16)
#define MIEN_TXUDIEN    (0x01 << 17)
#define MIEN_TXCPIEN    (0x01 << 18)
#define MIEN_EXDEFIEN   (0x01 << 19)
#define MIEN_NCSIEN     (0x01 << 20)
#define MIEN_TXABTIEN   (0x01 << 21)
#define MIEN_LCIEN      (0x01 << 22)
#define MIEN_TDUIEN     (0x01 << 23)
#define MIEN_TXBEIEN    (0x01 << 24)
#define MIEN_TSALMIEN   (0x01 << 28)

/* rx and tx owner bit */
#define RX_OWEN_DMA     (0x01 << 31)
#define RX_OWEN_CPU     (~(0x03 << 30))
#define TX_OWEN_DMA     (0x01 << 31)
#define TX_OWEN_CPU     (~(0x01 << 31))

/* tx frame desc controller bit */
#define MACTXINTEN      0x04
#define CRCMODE         0x02
#define PADDINGMODE     0x01

/* fftcr controller bit */
#define TXTHD           (0x03 << 8)
#define BLENGTH         (0x01 << 20)


#define RX_DESCRIPTOR_NUM       4       // Max Number of Rx Frame Descriptors
#define TX_DESCRIPTOR_NUM       2       // Max number of Tx Frame Descriptors

#define PACKET_BUFFER_SIZE      0x600

#define CONFIG_PHY_ADDR         0


// Frame Descriptor's Owner bit
#define OWNERSHIP_EMAC 0x80000000  // 1 = EMAC
//#define OWNERSHIP_CPU 0x7fffffff  // 0 = CPU

typedef struct
{
    __IO UINT32 M;      /*!< CAMx Most Significant Word Register */
    __IO UINT32 L;      /*!< CAMx Least Significant Word Register */
}CAM_Typedef;

typedef struct
{
    __IO UINT32 CAMCMR      ;   /*!< (EMCx_BA+0x000)  CAM Command Register */
    __IO UINT32 CAMEN       ;   /*!< (EMCx_BA+0x004) CAM Enable Register */
#if 1
    __IO UINT32 CAM0M;          /*!< (EMCx_BA+0x008) */
    __IO UINT32 CAM0L;          /*!< (EMCx_BA+0x00C) */
    __IO UINT32 CAM1M;          /*!< (EMCx_BA+0x010) */
    __IO UINT32 CAM1L;          /*!< (EMCx_BA+0x014) */
    __IO UINT32 CAM2M;          /*!< (EMCx_BA+0x018) */
    __IO UINT32 CAM2L;          /*!< (EMCx_BA+0x01C) */
    __IO UINT32 CAM3M;          /*!< (EMCx_BA+0x020) */
    __IO UINT32 CAM3L;          /*!< (EMCx_BA+0x024) */
    __IO UINT32 CAM4M;          /*!< (EMCx_BA+0x028) */
    __IO UINT32 CAM4L;          /*!< (EMCx_BA+0x02C) */
    __IO UINT32 CAM5M;          /*!< (EMCx_BA+0x030) */
    __IO UINT32 CAM5L;          /*!< (EMCx_BA+0x034) */
    __IO UINT32 CAM6M;          /*!< (EMCx_BA+0x038) */
    __IO UINT32 CAM6L;          /*!< (EMCx_BA+0x03C) */
    __IO UINT32 CAM7M;          /*!< (EMCx_BA+0x040) */
    __IO UINT32 CAM7L;          /*!< (EMCx_BA+0x044) */
    __IO UINT32 CAM8M;          /*!< (EMCx_BA+0x048) */
    __IO UINT32 CAM8L;          /*!< (EMCx_BA+0x04C) */
    __IO UINT32 CAM9M;          /*!< (EMCx_BA+0x050) */
    __IO UINT32 CAM9L;          /*!< (EMCx_BA+0x054) */
    __IO UINT32 CAM10M;         /*!< (EMCx_BA+0x058) */
    __IO UINT32 CAM10L;         /*!< (EMCx_BA+0x05C) */
    __IO UINT32 CAM11M;         /*!< (EMCx_BA+0x060) */
    __IO UINT32 CAM11L;         /*!< (EMCx_BA+0x064) */
    __IO UINT32 CAM12M;         /*!< (EMCx_BA+0x068) */
    __IO UINT32 CAM12L;         /*!< (EMCx_BA+0x06C) */
    __IO UINT32 CAM13M;         /*!< (EMCx_BA+0x070) */
    __IO UINT32 CAM13L;         /*!< (EMCx_BA+0x074) */
    __IO UINT32 CAM14M;         /*!< (EMCx_BA+0x078) */
    __IO UINT32 CAM14L;         /*!< (EMCx_BA+0x07C) */
    __IO UINT32 CAM15M;         /*!< (EMCx_BA+0x080) */
    __IO UINT32 CAM15L;         /*!< (EMCx_BA+0x084) */
#else
    CAM_Typedef CAMx[16];
#endif
    __IO UINT32 TXDLSA      ;   /*!< (EMCx_BA+0x088)  Transmit Descriptor Link List Start Address Register */
    __IO UINT32 RXDLSA      ;   /*!< (EMCx_BA+0x08C)  Receive Descriptor Link List Start Address Register */
    __IO UINT32 MCMDR       ;   /*!< (EMCx_BA+0x090)  MAC Command Register */
    __IO UINT32 MIID        ;   /*!< (EMCx_BA+0x094)  MII Management Data Register */
    __IO UINT32 MIIDA       ;   /*!< (EMCx_BA+0x098)  MII Management Control and Address Register */
    __IO UINT32 FFTCR       ;   /*!< (EMCx_BA+0x09C)  FIFO Threshold Control Register */
    __IO UINT32 TSDR        ;   /*!< (EMCx_BA+0x0a0)  Transmit Start Demand Register */
    __IO UINT32 RSDR        ;   /*!< (EMCx_BA+0x0a4)  Receive Start Demand Register */
    __IO UINT32 DMARFC      ;   /*!< (EMCx_BA+0x0a8)  Maximum Receive Frame Control Register */
    __IO UINT32 MIEN        ;   /*!< (EMCx_BA+0x0ac)  MAC Interrupt Enable Register */
    __IO UINT32 MISTA       ;   /*!< (EMCx_BA+0x0b0)  MAC Interrupt Status Register */
    __IO UINT32 MGSTA       ;   /*!< (EMCx_BA+0x0b4)  MAC General Status Register */
    __IO UINT32 MPCNT       ;   /*!< (EMCx_BA+0x0b8)  Missed Packet Count Register */
    __IO UINT32 MRPC        ;   /*!< (EMCx_BA+0x0bc)  MAC Receive Pause Count Register */
    __IO UINT32 RSV0[2];
    __IO UINT32 DMARFS      ;   /*!< (EMCx_BA+0x0c8)  DMA Receive Frame Status Register */
    __IO UINT32 CTXDSA      ;   /*!< (EMCx_BA+0x0cc)  Current Transmit Descriptor Start Address Register */
    __IO UINT32 CTXBSA      ;   /*!< (EMCx_BA+0x0d0)  Current Transmit Buffer Start Address Register */
    __IO UINT32 CRXDSA      ;   /*!< (EMCx_BA+0x0d4)  Current Receive Descriptor Start Address Register */
    __IO UINT32 CRXBSA      ;   /*!< (EMCx_BA+0x0d8)  Current Receive Buffer Start Address Register */
    __IO UINT32 RSV1[9];
    __IO UINT32 TSCTL       ;   /*!< (EMCx_BA+0x100)  Time Stamp Control Register */
    __IO UINT32 RSV2[3];
    __IO UINT32 TSSEC       ;   /*!< (EMCx_BA+0x110)  Time Stamp Counter Second Register */
    __IO UINT32 TSSUBSEC    ;   /*!< (EMCx_BA+0x114)  Time Stamp Counter Sub Second Register */
    __IO UINT32 TSINC       ;   /*!< (EMCx_BA+0x118)  Time Stamp Increment Register  */
    __IO UINT32 TSADDEN     ;   /*!< (EMCx_BA+0x11c)  Time Stamp Addend Register */
    __IO UINT32 TSUPDSEC    ;   /*!< (EMCx_BA+0x120)  Time Stamp Update Second Register */
    __IO UINT32 TSUPDSUBSEC ;   /*!< (EMCx_BA+0x124)  Time Stamp Update Sub Second Register */
    __IO UINT32 TSALMSEC    ;   /*!< (EMCx_BA+0x128)  Time Stamp Alarm Second Register */
    __IO UINT32 TSALMSUBSEC ;   /*!< (EMCx_BA+0x12c)  Time Stamp Alarm Sub Second Register */
}EMAC_Typedef;


#define EMAC0       ((EMAC_Typedef *) EMC0_BA)     /*!< EMC0  channel  */
#define EMAC1       ((EMAC_Typedef *) EMC1_BA)     /*!< EMC1  channel  */

#define ETH_TRIGGER_RX(EMCx)       (EMCx->RSDR = ENSTART)
#define ETH_TRIGGER_TX(EMCx)       (EMCx->TSDR = ENSTART)
#define ETH_ENABLE_RX(EMCx)        (EMCx->MCMDR |= MCMDR_RXON)
#define ETH_ENABLE_TX(EMCx)        (EMCx->MCMDR |= MCMDR_TXON)
#define ETH_DISABLE_RX(EMCx)       (EMCx->MCMDR &= ~MCMDR_RXON)
#define ETH_DISABLE_TX(EMCx)       (EMCx->MCMDR &= ~MCMDR_TXON)

#pragma pack(4)
// Tx/Rx buffer descriptor structure
struct eth_tx_descriptor
{
    unsigned int mode;
    unsigned int buffer;
    unsigned int sl;
    struct eth_tx_descriptor *next;
};
struct eth_rx_descriptor
{
    unsigned int sl;
    unsigned int buffer;
    unsigned int reserved;
    struct eth_rx_descriptor *next;
};

typedef struct
{
    EMAC_Typedef *EMACx;

    struct eth_rx_descriptor rx_desc [RX_DESCRIPTOR_NUM] ;
    struct eth_tx_descriptor tx_desc [TX_DESCRIPTOR_NUM] ;

    struct eth_rx_descriptor volatile *cur_rx_desc_ptr;
    struct eth_tx_descriptor volatile *cur_tx_desc_ptr, *fin_tx_desc_ptr;

    uint8_t rx_buf[RX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];
    uint8_t tx_buf[TX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];

    int plugged;
    int tx_vector,rx_vector;
}ETH_Typedef;
#pragma pack()
/*
 * functions
 */
void ETH_halt(ETH_Typedef *ETHx);
void ETH_chk_link(ETH_Typedef *ETHx);
void ETH_init(ETH_Typedef *ETHx, uint8_t *mac_addr);
uint8_t *ETH_get_tx_buf(ETH_Typedef *ETHx);
void ETH_start_tx(ETH_Typedef *ETHx,uint8_t * buffer,uint16_t length);
void ETH_start_rx(ETH_Typedef *ETHx);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_NUC97X_ETHERNET_H_ */
