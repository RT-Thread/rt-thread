/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 */


#define UNUSED 1

#ifndef SYNOP_GMAC_DEV_H
#define SYNOP_GMAC_DEV_H 1

/*******************************************************************/
#define SYNOP_LOOPBACK_MODE 0
#define SYNOP_LOOPBACK_DEBUG 0
#define SYNOP_PHY_LOOPBACK 0

#define SYNOP_TX_TEST 0
#define SYNOP_RX_TEST 0

#define SYNOP_TOP_DEBUG 0
#define SYNOP_REG_DEBUG 0
#define SYNOP_RX_DEBUG 0
#define SYNOP_TX_DEBUG 0
/*******************************************************************/

#include "synopGMAC_plat.h"
#include "synopGMAC_types.h"

//sw:   typedef are included in synopGMAC_plat.h
//  it is strange that we should add it here again!!

/*SynopGMAC can support up to 32 phys*/
#define GMAC_PHY_BASE 1
#ifdef GMAC_PHY_BASE
#define DEFAULT_PHY_BASE GMAC_PHY_BASE
#else
#define DEFAULT_PHY_BASE PHY16      //We use First Phy
#endif
#define MACBASE 0x0000          // The Mac Base address offset is 0x0000
#define DMABASE 0x1000          // Dma base address starts with an offset 0x1000


enum GMACPhyBase
{
    PHY0  = 0,          //The device can support 32 phys, but we use first phy only
    PHY1  = 1,
    PHY16 = 16,
    PHY31 = 31,
};


//#define TRANSMIT_DESC_SIZE  256       //Tx Descriptors needed in the Descriptor pool/queue
//#define RECEIVE_DESC_SIZE   256   //Rx Descriptors needed in the Descriptor pool/queue
//#define TRANSMIT_DESC_SIZE  13//256   //Tx Descriptors needed in the Descriptor pool/queue
#define TRANSMIT_DESC_SIZE  36 //48 //Tx Descriptors needed in the Descriptor pool/queue
#define RECEIVE_DESC_SIZE   72 //96 //Rx Descriptors needed in the Descriptor pool/queue

#define ETHERNET_HEADER             14  //6 byte Dest addr, 6 byte Src addr, 2 byte length/type
#define ETHERNET_CRC                 4  //Ethernet CRC
#define ETHERNET_EXTRA           2  //Only God knows about this?????
#define ETHERNET_PACKET_COPY       250  // Maximum length when received data is copied on to a new skb
#define ETHERNET_PACKET_EXTRA       18  // Preallocated length for the rx packets is MTU + ETHERNET_PACKET_EXTRA
#define VLAN_TAG             4  //optional 802.1q VLAN Tag
#define MIN_ETHERNET_PAYLOAD        46  //Minimum Ethernet payload size
#define MAX_ETHERNET_PAYLOAD      1500  //Maximum Ethernet payload size
#define JUMBO_FRAME_PAYLOAD       9000  //Jumbo frame payload size

#define TX_BUF_SIZE        ETHERNET_HEADER + ETHERNET_CRC + MAX_ETHERNET_PAYLOAD + VLAN_TAG
#define RX_BUF_SIZE        ETHERNET_HEADER + ETHERNET_CRC + MAX_ETHERNET_PAYLOAD + VLAN_TAG


// This is the IP's phy address. This is unique address for every MAC in the universe
#define DEFAULT_MAC_ADDRESS {0x00, 0x55, 0x7B, 0xB5, 0x7D, 0xF7}

/*
DMA Descriptor Structure
The structure is common for both receive and transmit descriptors
The descriptor is of 4 words, but our structrue contains 6 words where
last two words are to hold the virtual address of the network buffer pointers
for driver's use
From the GMAC core release 3.50a onwards, the Enhanced Descriptor structure got changed.
The descriptor (both transmit and receive) are of 8 words each rather the 4 words of normal
descriptor structure.
Whenever IEEE 1588 Timestamping is enabled TX/RX DESC6 provides the lower 32 bits of Timestamp value and
                                           TX/RX DESC7 provides the upper 32 bits of Timestamp value
In addition to this whenever extended status bit is set (RX DESC0 bit 0), RX DESC4 contains the extended status information
*/

#define MODULO_INTERRUPT   1 // if it is set to 1, interrupt is available for all the descriptors or else interrupt is available only for
                 // descriptor whose index%MODULO_INTERRUPT is zero
#ifdef ENH_DESC_8W
typedef struct DmaDescStruct
{
  u32   status;         /* Status                                   */
  u32   length;         /* Buffer 1  and Buffer 2 length                        */
  u32   buffer1;        /* Network Buffer 1 pointer (Dma-able)                          */
  u32   buffer2;        /* Network Buffer 2 pointer or next descriptor pointer (Dma-able)in chain structure     */
            /* This data below is used only by driver                   */
  u32   extstatus;      /* Extended status of a Rx Descriptor                                           */
  u32   reserved1;      /* Reserved word                                                                */
  u32   timestamplow;   /* Lower 32 bits of the 64 bit timestamp value                                  */
  u32   timestamphigh;  /* Higher 32 bits of the 64 bit timestamp value                                  */
  u32   data1;          /* This holds virtual address of buffer1, not used by DMA           */
  u32   data2;          /* This holds virtual address of buffer2, not used by DMA           */
} DmaDesc;
#else
typedef struct DmaDescStruct
{
  u32   status;         /* Status                                   */
  u32   length;         /* Buffer 1  and Buffer 2 length                        */
  u32   buffer1;        /* Network Buffer 1 pointer (Dma-able)                          */
  u32   buffer2;        /* Network Buffer 2 pointer or next descriptor pointer (Dma-able)in chain structure     */
            /* This data below is used only by driver                   */
  u32   data1;          /* This holds virtual address of buffer1, not used by DMA           */
  u32   data2;          /* This holds virtual address of buffer2, not used by DMA           */

  u32   dummy1;     //sw: for addr align
  u32   dummy2;     //

} DmaDesc;
#endif

enum DescMode
{
    RINGMODE    = 0x00000001,
    CHAINMODE   = 0x00000002,
};

enum BufferMode
{
    SINGLEBUF   = 0x00000001,
    DUALBUF     = 0x00000002,
};

/* synopGMAC device data */

typedef struct synopGMACDeviceStruct
{
  u32 MacBase;               /* base address of MAC registers         */
  u32 DmaBase;               /* base address of DMA registers         */
  u32 PhyBase;               /* PHY device address on MII interface   */
  u32 Version;                   /* Gmac Revision version             */


  dma_addr_t TxDescDma;      /* Dma-able address of first tx descriptor either in ring or chain mode, this is used by the GMAC device*/
  dma_addr_t RxDescDma;      /* Dma-albe address of first rx descriptor either in ring or chain mode, this is used by the GMAC device*/
  DmaDesc *TxDesc;               /* start address of TX descriptors ring or chain, this is used by the driver  */
  DmaDesc *RxDesc;               /* start address of RX descriptors ring or chain, this is used by the driver  */

  u32 BusyTxDesc;        /* Number of Tx Descriptors owned by DMA at any given time*/
  u32 BusyRxDesc;        /* Number of Rx Descriptors owned by DMA at any given time*/

  u32  RxDescCount;              /* number of rx descriptors in the tx descriptor queue/pool */
  u32  TxDescCount;              /* number of tx descriptors in the rx descriptor queue/pool */

  u32  TxBusy;                   /* index of the tx descriptor owned by DMA, is obtained by synopGMAC_get_tx_qptr()                */
  u32  TxNext;                   /* index of the tx descriptor next available with driver, given to DMA by synopGMAC_set_tx_qptr() */
  u32  RxBusy;                   /* index of the rx descriptor owned by DMA, obtained by synopGMAC_get_rx_qptr()                   */
  u32  RxNext;                   /* index of the rx descriptor next available with driver, given to DMA by synopGMAC_set_rx_qptr() */

  DmaDesc * TxBusyDesc;          /* Tx Descriptor address corresponding to the index TxBusy */
  DmaDesc * TxNextDesc;          /* Tx Descriptor address corresponding to the index TxNext */
  DmaDesc * RxBusyDesc;          /* Rx Descriptor address corresponding to the index TxBusy */
  DmaDesc * RxNextDesc;          /* Rx Descriptor address corresponding to the index RxNext */

  /*Phy related stuff*/
  u32 ClockDivMdc;      /* Clock divider value programmed in the hardware           */
  /* The status of the link */
  u32 LinkState0;       /* Link status as reported by the Marvel Phy                */
  u32 LinkState;        /* Link status as reported by the Marvel Phy                */
  u32 DuplexMode;               /* Duplex mode of the Phy                   */
  u32 Speed;            /* Speed of the Phy                     */
  u32 LoopBackMode;         /* Loopback status of the Phy                   */

//  void * FirstTxDesc;
//  void * FirstRxDesc;
//  u32 skb_array[RECEIVE_DESC_SIZE];
} synopGMACdevice;



/* Below is "88E1011/88E1011S Integrated 10/100/1000 Gigabit Ethernet Transceiver"
 * Register and their layouts. This Phy has been used in the Dot Aster GMAC Phy daughter.
 * Since the Phy register map is standard, this map hardly changes to a different Ppy
 */

enum MiiRegisters
{
  PHY_CONTROL_REG           = 0x0000,       /*Control Register*/
  PHY_STATUS_REG            = 0x0001,       /*Status Register */
  PHY_ID_HI_REG             = 0x0002,       /*PHY Identifier High Register*/
  PHY_ID_LOW_REG            = 0x0003,       /*PHY Identifier High Register*/
  PHY_AN_ADV_REG            = 0x0004,       /*Auto-Negotiation Advertisement Register*/
  PHY_LNK_PART_ABl_REG      = 0x0005,       /*Link Partner Ability Register (Base Page)*/
  PHY_AN_EXP_REG            = 0x0006,       /*Auto-Negotiation Expansion Register*/
  PHY_AN_NXT_PAGE_TX_REG    = 0x0007,       /*Next Page Transmit Register*/
  PHY_LNK_PART_NXT_PAGE_REG = 0x0008,       /*Link Partner Next Page Register*/
  PHY_1000BT_CTRL_REG       = 0x0009,       /*1000BASE-T Control Register*/
  PHY_1000BT_STATUS_REG     = 0x000a,       /*1000BASE-T Status Register*/
  PHY_SPECIFIC_CTRL_REG     = 0x0010,       /*Phy specific control register*/
  PHY_SPECIFIC_STATUS_REG   = 0x0011,       /*Phy specific status register*/
  PHY_INTERRUPT_ENABLE_REG  = 0x0012,       /*Phy interrupt enable register*/
  PHY_INTERRUPT_STATUS_REG  = 0x0013,       /*Phy interrupt status register*/
  PHY_EXT_PHY_SPC_CTRL      = 0x0014,       /*Extended Phy specific control*/
  PHY_RX_ERR_COUNTER        = 0x0015,       /*Receive Error Counter*/
  PHY_EXT_ADDR_CBL_DIAG     = 0x0016,       /*Extended address for cable diagnostic register*/
  PHY_LED_CONTROL       = 0x0018,       /*LED Control*/
  PHY_MAN_LED_OVERIDE       = 0x0019,       /*Manual LED override register*/
  PHY_EXT_PHY_SPC_CTRL2     = 0x001a,       /*Extended Phy specific control 2*/
  PHY_EXT_PHY_SPC_STATUS    = 0x001b,       /*Extended Phy specific status*/
  PHY_CBL_DIAG_REG      = 0x001c,       /*Cable diagnostic registers*/
};


/* This is Control register layout. Control register is of 16 bit wide.
*/

enum Mii_GEN_CTRL
{                             /*    Description                bits        R/W  default value  */
    Mii_reset        = 0x8000,
    Mii_Speed_10         = 0x0000,   /* 10   Mbps                    6:13           RW                      */
    Mii_Speed_100        = 0x2000,   /* 100  Mbps                    6:13           RW                      */
    Mii_Speed_1000       = 0x0040,   /* 1000 Mbit/s                  6:13           RW                      */

    Mii_Duplex           = 0x0100,   /* Full Duplex mode             8                  RW                      */

    Mii_Manual_Master_Config = 0x0800,   /* Manual Master Config         11                 RW          */

    Mii_Loopback         = 0x4000,   /* Enable Loop back             14                 RW                      */
    Mii_NoLoopback       = 0x0000,   /* Enable Loop back             14                 RW                      */
};

enum Mii_Phy_Status
{
    Mii_phy_status_speed_10     = 0x0000,
    Mii_phy_status_speed_100    = 0x4000,
    Mii_phy_status_speed_1000   = 0x8000,

    Mii_phy_status_full_duplex  = 0x2000,
    Mii_phy_status_half_duplex  = 0x0000,

    Mii_phy_status_link_up      = 0x0400,   //lyf:rtl 8211 phy
//  Mii_phy_status_link_up      = 0x0100,   //sw: broadcom BCM5461 PHY
};
/* This is Status register layout. Status register is of 16 bit wide.
*/
enum Mii_GEN_STATUS
{
    Mii_AutoNegCmplt     = 0x0020,   /* Autonegotiation completed      5              RW                   */
    Mii_Link             = 0x0004,   /* Link status                    2              RW                   */
};

enum Mii_Link_Status
{
    LINKDOWN    = 0,
    LINKUP      = 1,
};

enum Mii_Duplex_Mode
{
    HALFDUPLEX = 1,
    FULLDUPLEX = 2,
};
enum Mii_Link_Speed
{
    SPEED10     = 1,
    SPEED100    = 2,
    SPEED1000   = 3,
};

enum Mii_Loop_Back
{
    NOLOOPBACK  = 0,
    LOOPBACK    = 1,
};



/**********************************************************
 * GMAC registers Map
 * For Pci based system address is BARx + GmacRegisterBase
 * For any other system translation is done accordingly
 **********************************************************/
enum GmacRegisters
{
  GmacConfig          = 0x0000,    /* Mac config Register                       */
  GmacFrameFilter     = 0x0004,    /* Mac frame filtering controls              */
  GmacHashHigh        = 0x0008,    /* Multi-cast hash table high                */
  GmacHashLow         = 0x000C,    /* Multi-cast hash table low                 */
  GmacGmiiAddr        = 0x0010,    /* GMII address Register(ext. Phy)           */
  GmacGmiiData        = 0x0014,    /* GMII data Register(ext. Phy)              */
  GmacFlowControl     = 0x0018,    /* Flow control Register                     */
  GmacVlan            = 0x001C,    /* VLAN tag Register (IEEE 802.1Q)           */

  GmacVersion         = 0x0020,    /* GMAC Core Version Register                */
  GmacWakeupAddr      = 0x0028,    /* GMAC wake-up frame filter adrress reg     */
  GmacPmtCtrlStatus       = 0x002C,    /* PMT control and status register           */

  GmacInterruptStatus     = 0x0038,    /* Mac Interrupt ststus register        */
  GmacInterruptMask       = 0x003C,    /* Mac Interrupt Mask register          */

  GmacAddr0High       = 0x0040,    /* Mac address0 high Register                */
  GmacAddr0Low        = 0x0044,    /* Mac address0 low Register                 */
  GmacAddr1High       = 0x0048,    /* Mac address1 high Register                */
  GmacAddr1Low        = 0x004C,    /* Mac address1 low Register                 */
  GmacAddr2High       = 0x0050,    /* Mac address2 high Register                */
  GmacAddr2Low        = 0x0054,    /* Mac address2 low Register                 */
  GmacAddr3High       = 0x0058,    /* Mac address3 high Register                */
  GmacAddr3Low        = 0x005C,    /* Mac address3 low Register                 */
  GmacAddr4High       = 0x0060,    /* Mac address4 high Register                */
  GmacAddr4Low        = 0x0064,    /* Mac address4 low Register                 */
  GmacAddr5High       = 0x0068,    /* Mac address5 high Register                */
  GmacAddr5Low        = 0x006C,    /* Mac address5 low Register                 */
  GmacAddr6High       = 0x0070,    /* Mac address6 high Register                */
  GmacAddr6Low        = 0x0074,    /* Mac address6 low Register                 */
  GmacAddr7High       = 0x0078,    /* Mac address7 high Register                */
  GmacAddr7Low        = 0x007C,    /* Mac address7 low Register                 */
  GmacAddr8High       = 0x0080,    /* Mac address8 high Register                */
  GmacAddr8Low        = 0x0084,    /* Mac address8 low Register                 */
  GmacAddr9High       = 0x0088,    /* Mac address9 high Register                */
  GmacAddr9Low            = 0x008C,    /* Mac address9 low Register                 */
  GmacAddr10High          = 0x0090,    /* Mac address10 high Register               */
  GmacAddr10Low       = 0x0094,    /* Mac address10 low Register                */
  GmacAddr11High      = 0x0098,    /* Mac address11 high Register               */
  GmacAddr11Low       = 0x009C,    /* Mac address11 low Register                */
  GmacAddr12High      = 0x00A0,    /* Mac address12 high Register               */
  GmacAddr12Low           = 0x00A4,    /* Mac address12 low Register                */
  GmacAddr13High      = 0x00A8,    /* Mac address13 high Register               */
  GmacAddr13Low       = 0x00AC,    /* Mac address13 low Register                */
  GmacAddr14High      = 0x00B0,    /* Mac address14 high Register               */
  GmacAddr14Low           = 0x00B4,    /* Mac address14 low Register                */
  GmacAddr15High          = 0x00B8,    /* Mac address15 high Register               */
  GmacAddr15Low       = 0x00BC,    /* Mac address15 low Register                */
  GmacStatus          = 0x00d8,    /*MAC status*/

  /*Time Stamp Register Map*/
  GmacTSControl           = 0x0700,  /* Controls the Timestamp update logic                         : only when IEEE 1588 time stamping is enabled in corekit            */

  GmacTSSubSecIncr        = 0x0704,  /* 8 bit value by which sub second register is incremented     : only when IEEE 1588 time stamping without external timestamp input */

  GmacTSHigh              = 0x0708,  /* 32 bit seconds(MS)                                          : only when IEEE 1588 time stamping without external timestamp input */
  GmacTSLow               = 0x070C,  /* 32 bit nano seconds(MS)                                     : only when IEEE 1588 time stamping without external timestamp input */

  GmacTSHighUpdate        = 0x0710,  /* 32 bit seconds(MS) to be written/added/subtracted           : only when IEEE 1588 time stamping without external timestamp input */
  GmacTSLowUpdate         = 0x0714,  /* 32 bit nano seconds(MS) to be writeen/added/subtracted      : only when IEEE 1588 time stamping without external timestamp input */

  GmacTSAddend            = 0x0718,  /* Used by Software to readjust the clock frequency linearly   : only when IEEE 1588 time stamping without external timestamp input */

  GmacTSTargetTimeHigh    = 0x071C,  /* 32 bit seconds(MS) to be compared with system time          : only when IEEE 1588 time stamping without external timestamp input */
  GmacTSTargetTimeLow     = 0x0720,  /* 32 bit nano seconds(MS) to be compared with system time     : only when IEEE 1588 time stamping without external timestamp input */

  GmacTSHighWord          = 0x0724,  /* Time Stamp Higher Word Register (Version 2 only); only lower 16 bits are valid                                                   */
  //GmacTSHighWordUpdate    = 0x072C,  /* Time Stamp Higher Word Update Register (Version 2 only); only lower 16 bits are valid                                            */

  GmacTSStatus            = 0x0728,  /* Time Stamp Status Register                                                                                                       */
};

/**********************************************************
 * GMAC Network interface registers
 * This explains the Register's Layout

 * FES is Read only by default and is enabled only when Tx
 * Config Parameter is enabled for RGMII/SGMII interface
 * during CoreKit Config.

 * DM is Read only with value 1'b1 in Full duplex only Config
 **********************************************************/

/* GmacConfig              = 0x0000,    Mac config Register  Layout */
enum GmacConfigReg
{
                                           /* Bit description                      Bits         R/W   Reset value  */
  GmacWatchdog         = 0x00800000,
  GmacWatchdogDisable      = 0x00800000,     /* (WD)Disable watchdog timer on Rx      23           RW                */
  GmacWatchdogEnable       = 0x00000000,     /* Enable watchdog timer                                        0       */

  GmacJabber           = 0x00400000,
  GmacJabberDisable        = 0x00400000,     /* (JD)Disable jabber timer on Tx        22           RW                */
  GmacJabberEnable         = 0x00000000,     /* Enable jabber timer                                          0       */

  GmacFrameBurst           = 0x00200000,
  GmacFrameBurstEnable     = 0x00200000,     /* (BE)Enable frame bursting during Tx   21           RW                */
  GmacFrameBurstDisable    = 0x00000000,     /* Disable frame bursting                                       0       */

  GmacJumboFrame           = 0x00100000,
  GmacJumboFrameEnable     = 0x00100000,     /* (JE)Enable jumbo frame for Tx         20           RW                */
  GmacJumboFrameDisable    = 0x00000000,     /* Disable jumbo frame                                          0       */

  GmacInterFrameGap7       = 0x000E0000,     /* (IFG) Config7 - 40 bit times          19:17        RW                */
  GmacInterFrameGap6       = 0x000C0000,     /* (IFG) Config6 - 48 bit times                                         */
  GmacInterFrameGap5       = 0x000A0000,     /* (IFG) Config5 - 56 bit times                                         */
  GmacInterFrameGap4       = 0x00080000,     /* (IFG) Config4 - 64 bit times                                         */
  GmacInterFrameGap3       = 0x00040000,     /* (IFG) Config3 - 72 bit times                                         */
  GmacInterFrameGap2       = 0x00020000,     /* (IFG) Config2 - 80 bit times                                         */
  GmacInterFrameGap1       = 0x00010000,     /* (IFG) Config1 - 88 bit times                                         */
  GmacInterFrameGap0       = 0x00000000,     /* (IFG) Config0 - 96 bit times                                 000     */

  GmacDisableCrs       = 0x00010000,
  GmacMiiGmii          = 0x00008000,
  GmacSelectMii            = 0x00008000,     /* (PS)Port Select-MII mode              15           RW                */
  GmacSelectGmii           = 0x00000000,     /* GMII mode                                                    0       */

  GmacFESpeed100           = 0x00004000,     /*(FES)Fast Ethernet speed 100Mbps       14           RW                */
  GmacFESpeed10            = 0x00000000,     /* 10Mbps                                                       0       */

  GmacRxOwn        = 0x00002000,
  GmacDisableRxOwn         = 0x00002000,     /* (DO)Disable receive own packets       13           RW                */
  GmacEnableRxOwn          = 0x00000000,     /* Enable receive own packets                                   0       */

  GmacLoopback         = 0x00001000,
  GmacLoopbackOn           = 0x00001000,     /* (LM)Loopback mode for GMII/MII        12           RW                */
  GmacLoopbackOff          = 0x00000000,     /* Normal mode                                                  0       */

  GmacDuplex           = 0x00000800,
  GmacFullDuplex           = 0x00000800,     /* (DM)Full duplex mode                  11           RW                */
  GmacHalfDuplex           = 0x00000000,     /* Half duplex mode                                             0       */

  GmacRxIpcOffload     = 0x00000400,     /*IPC checksum offload           10           RW        0       */

  GmacRetry        = 0x00000200,
  GmacRetryDisable         = 0x00000200,     /* (DR)Disable Retry                      9           RW                */
  GmacRetryEnable          = 0x00000000,     /* Enable retransmission as per BL                              0       */

  GmacLinkUp               = 0x00000100,     /* (LUD)Link UP                           8           RW                */
  GmacLinkDown             = 0x00000100,     /* Link Down                                                    0       */

  GmacPadCrcStrip      = 0x00000080,
  GmacPadCrcStripEnable    = 0x00000080,     /* (ACS) Automatic Pad/Crc strip enable   7           RW                */
  GmacPadCrcStripDisable   = 0x00000000,     /* Automatic Pad/Crc stripping disable                          0       */

  GmacBackoffLimit     = 0x00000060,
  GmacBackoffLimit3        = 0x00000060,     /* (BL)Back-off limit in HD mode          6:5         RW                */
  GmacBackoffLimit2        = 0x00000040,     /*                                                                      */
  GmacBackoffLimit1        = 0x00000020,     /*                                                                      */
  GmacBackoffLimit0        = 0x00000000,     /*                                                              00      */

  GmacDeferralCheck    = 0x00000010,
  GmacDeferralCheckEnable  = 0x00000010,     /* (DC)Deferral check enable in HD mode   4           RW                */
  GmacDeferralCheckDisable = 0x00000000,     /* Deferral check disable                                       0       */

  GmacTx           = 0x00000008,
  GmacTxEnable             = 0x00000008,     /* (TE)Transmitter enable                 3           RW                */
  GmacTxDisable            = 0x00000000,     /* Transmitter disable                                          0       */

  GmacRx           = 0x00000004,
  GmacRxEnable             = 0x00000004,     /* (RE)Receiver enable                    2           RW                */
  GmacRxDisable            = 0x00000000,     /* Receiver disable                                             0       */
};

/* GmacFrameFilter    = 0x0004,     Mac frame filtering controls Register Layout*/
enum GmacFrameFilterReg
{
  GmacFilter           = 0x80000000,
  GmacFilterOff            = 0x80000000,     /* (RA)Receive all incoming packets       31         RW                 */
  GmacFilterOn             = 0x00000000,     /* Receive filtered packets only                                0       */

  GmacHashPerfectFilter    = 0x00000400,     /*Hash or Perfect Filter enable           10         RW         0       */

  GmacSrcAddrFilter    = 0x00000200,
  GmacSrcAddrFilterEnable  = 0x00000200,     /* (SAF)Source Address Filter enable       9         RW                 */
  GmacSrcAddrFilterDisable = 0x00000000,     /*                                                              0       */

  GmacSrcInvaAddrFilter    = 0x00000100,
  GmacSrcInvAddrFilterEn   = 0x00000100,     /* (SAIF)Inv Src Addr Filter enable        8         RW                 */
  GmacSrcInvAddrFilterDis  = 0x00000000,     /*                                                              0       */

  GmacPassControl      = 0x000000C0,
  GmacPassControl3         = 0x000000C0,     /* (PCS)Forwards ctrl frms that pass AF    7:6       RW                 */
  GmacPassControl2         = 0x00000080,     /* Forwards all control frames                                          */
  GmacPassControl1         = 0x00000040,     /* Does not pass control frames                                         */
  GmacPassControl0         = 0x00000000,     /* Does not pass control frames                                 00      */

  GmacBroadcast        = 0x00000020,
  GmacBroadcastDisable     = 0x00000020,     /* (DBF)Disable Rx of broadcast frames     5         RW                 */
  GmacBroadcastEnable      = 0x00000000,     /* Enable broadcast frames                                      0       */

  GmacMulticastFilter      = 0x00000010,
  GmacMulticastFilterOff   = 0x00000010,     /* (PM) Pass all multicast packets         4         RW                 */
  GmacMulticastFilterOn    = 0x00000000,     /* Pass filtered multicast packets                              0       */

  GmacDestAddrFilter       = 0x00000008,
  GmacDestAddrFilterInv    = 0x00000008,     /* (DAIF)Inverse filtering for DA          3         RW                 */
  GmacDestAddrFilterNor    = 0x00000000,     /* Normal filtering for DA                                      0       */

  GmacMcastHashFilter      = 0x00000004,
  GmacMcastHashFilterOn    = 0x00000004,     /* (HMC)perfom multicast hash filtering    2         RW                 */
  GmacMcastHashFilterOff   = 0x00000000,     /* perfect filtering only                                       0       */

  GmacUcastHashFilter      = 0x00000002,
  GmacUcastHashFilterOn    = 0x00000002,     /* (HUC)Unicast Hash filtering only        1         RW                 */
  GmacUcastHashFilterOff   = 0x00000000,     /* perfect filtering only                                       0       */

  GmacPromiscuousMode      = 0x00000001,
  GmacPromiscuousModeOn    = 0x00000001,     /* Receive all frames                      0         RW                 */
  GmacPromiscuousModeOff   = 0x00000000,     /* Receive filtered packets only                                0       */
};


/*GmacGmiiAddr             = 0x0010,    GMII address Register(ext. Phy) Layout          */
enum GmacGmiiAddrReg
{
  GmiiDevMask              = 0x0000F800,     /* (PA)GMII device address                 15:11     RW         0x00    */
  GmiiDevShift             = 11,

  GmiiRegMask              = 0x000007C0,     /* (GR)GMII register in selected Phy       10:6      RW         0x00    */
  GmiiRegShift             = 6,

  GmiiCsrClkMask       = 0x0000001C,     /*CSR Clock bit Mask            4:2                 */
  GmiiCsrClk5              = 0x00000014,     /* (CR)CSR Clock Range     250-300 MHz      4:2      RW         000     */
  GmiiCsrClk4              = 0x00000010,     /*                         150-250 MHz                                  */
  GmiiCsrClk3              = 0x0000000C,     /*                         35-60 MHz                                    */
  GmiiCsrClk2              = 0x00000008,     /*                         20-35 MHz                                    */
  GmiiCsrClk1              = 0x00000004,     /*                         100-150 MHz                                  */
  GmiiCsrClk0              = 0x00000000,     /*                         60-100 MHz                                   */

  GmiiWrite                = 0x00000002,     /* (GW)Write to register                      1      RW                 */
  GmiiRead                 = 0x00000000,     /* Read from register                                            0      */

  GmiiBusy                 = 0x00000001,     /* (GB)GMII interface is busy                 0      RW          0      */
};

/* GmacGmiiData            = 0x0014,    GMII data Register(ext. Phy) Layout             */
enum GmacGmiiDataReg
{
  GmiiDataMask             = 0x0000FFFF,     /* (GD)GMII Data                             15:0    RW         0x0000  */
};


/*GmacFlowControl    = 0x0018,    Flow control Register   Layout                  */
enum GmacFlowControlReg
{
  GmacPauseTimeMask        = 0xFFFF0000,     /* (PT) PAUSE TIME field in the control frame  31:16   RW       0x0000  */
  GmacPauseTimeShift       = 16,

  GmacPauseLowThresh       = 0x00000030,
  GmacPauseLowThresh3      = 0x00000030,     /* (PLT)thresh for pause tmr 256 slot time      5:4    RW               */
  GmacPauseLowThresh2      = 0x00000020,     /*                           144 slot time                              */
  GmacPauseLowThresh1      = 0x00000010,     /*                            28 slot time                              */
  GmacPauseLowThresh0      = 0x00000000,     /*                             4 slot time                       000    */

  GmacUnicastPauseFrame    = 0x00000008,
  GmacUnicastPauseFrameOn  = 0x00000008,     /* (UP)Detect pause frame with unicast addr.     3    RW                */
  GmacUnicastPauseFrameOff = 0x00000000,     /* Detect only pause frame with multicast addr.                   0     */

  GmacRxFlowControl    = 0x00000004,
  GmacRxFlowControlEnable  = 0x00000004,     /* (RFE)Enable Rx flow control                   2    RW                */
  GmacRxFlowControlDisable = 0x00000000,     /* Disable Rx flow control                                        0     */

  GmacTxFlowControl        = 0x00000002,
  GmacTxFlowControlEnable  = 0x00000002,     /* (TFE)Enable Tx flow control                   1    RW                */
  GmacTxFlowControlDisable = 0x00000000,     /* Disable flow control                                           0     */

  GmacFlowControlBackPressure= 0x00000001,
  GmacSendPauseFrame       = 0x00000001,     /* (FCB/PBA)send pause frm/Apply back pressure   0    RW          0     */
};

/*  GmacInterruptStatus   = 0x0038,     Mac Interrupt ststus register          */
enum GmacInterruptStatusBitDefinition
{
  GmacTSIntSts         = 0x00000200,    /* set if int generated due to TS (Read Time Stamp Status Register to know details)*/
  GmacMmcRxChksumOffload   = 0x00000080,    /* set if int generated in MMC RX CHECKSUM OFFLOAD int register                   */
  GmacMmcTxIntSts      = 0x00000040,    /* set if int generated in MMC TX Int register             */
  GmacMmcRxIntSts      = 0x00000020,    /* set if int generated in MMC RX Int register             */
  GmacMmcIntSts        = 0x00000010,    /* set if any of the above bit [7:5] is set            */
  GmacPmtIntSts        = 0x00000008,    /* set whenver magic pkt/wake-on-lan frame is received         */
  GmacPcsAnComplete    = 0x00000004,    /* set when AN is complete in TBI/RTBI/SGMIII phy interface        */
  GmacPcsLnkStsChange      = 0x00000002,    /* set if any lnk status change in TBI/RTBI/SGMII interface        */
  GmacRgmiiIntSts      = 0x00000001,    /* set if any change in lnk status of RGMII interface          */

};

/*  GmacInterruptMask       = 0x003C,     Mac Interrupt Mask register          */
enum GmacInterruptMaskBitDefinition
{
  GmacTSIntMask        = 0x00000200,    /* when set disables the time stamp interrupt generation            */
  GmacPmtIntMask       = 0x00000008,    /* when set Disables the assertion of PMT interrupt                 */
  GmacPcsAnIntMask     = 0x00000004,    /* When set disables the assertion of PCS AN complete interrupt         */
  GmacPcsLnkStsIntMask     = 0x00000002,    /* when set disables the assertion of PCS lnk status change interrupt   */
  GmacRgmiiIntMask     = 0x00000001,    /* when set disables the assertion of RGMII int             */
};

/**********************************************************
 * GMAC DMA registers
 * For Pci based system address is BARx + GmaDmaBase
 * For any other system translation is done accordingly
 **********************************************************/

enum DmaRegisters
{
  DmaBusMode        = 0x0000,    /* CSR0 - Bus Mode Register                          */
  DmaTxPollDemand   = 0x0004,    /* CSR1 - Transmit Poll Demand Register              */
  DmaRxPollDemand   = 0x0008,    /* CSR2 - Receive Poll Demand Register               */
  DmaRxBaseAddr     = 0x000C,    /* CSR3 - Receive Descriptor list base address       */
  DmaTxBaseAddr     = 0x0010,    /* CSR4 - Transmit Descriptor list base address      */
  DmaStatus         = 0x0014,    /* CSR5 - Dma status Register                        */
  DmaControl        = 0x0018,    /* CSR6 - Dma Operation Mode Register                */
  DmaInterrupt      = 0x001C,    /* CSR7 - Interrupt enable                           */
  DmaMissedFr       = 0x0020,    /* CSR8 - Missed Frame & Buffer overflow Counter     */
  DmaTxCurrDesc     = 0x0048,    /*      - Current host Tx Desc Register              */
  DmaRxCurrDesc     = 0x004C,    /*      - Current host Rx Desc Register              */
  DmaTxCurrAddr     = 0x0050,    /* CSR20 - Current host transmit buffer address      */
  DmaRxCurrAddr     = 0x0054,    /* CSR21 - Current host receive buffer address       */
};

/**********************************************************
 * DMA Engine registers Layout
 **********************************************************/

/*DmaBusMode               = 0x0000,    CSR0 - Bus Mode */
enum DmaBusModeReg
{                                         /* Bit description                                Bits     R/W   Reset value */
  DmaFixedBurstEnable     = 0x00010000,   /* (FB)Fixed Burst SINGLE, INCR4, INCR8 or INCR16   16     RW                */
  DmaFixedBurstDisable    = 0x00000000,   /*             SINGLE, INCR                                          0       */

  DmaTxPriorityRatio11    = 0x00000000,   /* (PR)TX:RX DMA priority ratio 1:1                15:14   RW        00      */
  DmaTxPriorityRatio21    = 0x00004000,   /* (PR)TX:RX DMA priority ratio 2:1                                          */
  DmaTxPriorityRatio31    = 0x00008000,   /* (PR)TX:RX DMA priority ratio 3:1                                          */
  DmaTxPriorityRatio41    = 0x0000C000,   /* (PR)TX:RX DMA priority ratio 4:1                                          */

  DmaBurstLengthx8        = 0x01000000,   /* When set mutiplies the PBL by 8                  24      RW        0      */

  DmaBurstLength256       = 0x01002000,   /*(DmaBurstLengthx8 | DmaBurstLength32) = 256      [24]:13:8                 */
  DmaBurstLength128       = 0x01001000,   /*(DmaBurstLengthx8 | DmaBurstLength16) = 128      [24]:13:8                 */
  DmaBurstLength64        = 0x01000800,   /*(DmaBurstLengthx8 | DmaBurstLength8) = 64        [24]:13:8                 */
  DmaBurstLength32        = 0x00002000,   /* (PBL) programmable Dma burst length = 32        13:8    RW                */
  DmaBurstLength16        = 0x00001000,   /* Dma burst length = 16                                                     */
  DmaBurstLength8         = 0x00000800,   /* Dma burst length = 8                                                      */
  DmaBurstLength4         = 0x00000400,   /* Dma burst length = 4                                                      */
  DmaBurstLength2         = 0x00000200,   /* Dma burst length = 2                                                      */
  DmaBurstLength1         = 0x00000100,   /* Dma burst length = 1                                                      */
  DmaBurstLength0         = 0x00000000,   /* Dma burst length = 0                                               0x00   */

  DmaDescriptor8Words     = 0x00000080,   /* Enh Descriptor works  1=> 8 word descriptor      7                  0    */
  DmaDescriptor4Words     = 0x00000000,   /* Enh Descriptor works  0=> 4 word descriptor      7                  0    */

  DmaDescriptorSkip16     = 0x00000040,   /* (DSL)Descriptor skip length (no.of dwords)       6:2     RW               */
  DmaDescriptorSkip8      = 0x00000020,   /* between two unchained descriptors                                         */
  DmaDescriptorSkip4      = 0x00000010,   /*                                                                           */
  DmaDescriptorSkip2      = 0x00000008,   /*                                                                           */
  DmaDescriptorSkip1      = 0x00000004,   /*                                                                           */
  DmaDescriptorSkip0      = 0x00000000,   /*                                                                    0x00   */

  DmaArbitRr              = 0x00000000,   /* (DA) DMA RR arbitration                            1     RW         0     */
  DmaArbitPr              = 0x00000002,   /* Rx has priority over Tx                                                   */

  DmaResetOn              = 0x00000001,   /* (SWR)Software Reset DMA engine                     0     RW               */
  DmaResetOff             = 0x00000000,   /*                                                                      0    */
};


/*DmaStatus         = 0x0014,    CSR5 - Dma status Register                        */
enum DmaStatusReg
{
  /*Bit 28 27 and 26 indicate whether the interrupt due to PMT GMACMMC or GMAC LINE Remaining bits are DMA interrupts*/
  GmacPmtIntr             = 0x10000000,   /* (GPI)Gmac subsystem interrupt                      28     RO       0       */
  GmacMmcIntr             = 0x08000000,   /* (GMI)Gmac MMC subsystem interrupt                  27     RO       0       */
  GmacLineIntfIntr        = 0x04000000,   /* Line interface interrupt                           26     RO       0       */

  DmaErrorBit2            = 0x02000000,   /* (EB)Error bits 0-data buffer, 1-desc. access       25     RO       0       */
  DmaErrorBit1            = 0x01000000,   /* (EB)Error bits 0-write trnsf, 1-read transfr       24     RO       0       */
  DmaErrorBit0            = 0x00800000,   /* (EB)Error bits 0-Rx DMA, 1-Tx DMA                  23     RO       0       */

  DmaTxState              = 0x00700000,   /* (TS)Transmit process state                         22:20  RO               */
  DmaTxStopped            = 0x00000000,   /* Stopped - Reset or Stop Tx Command issued                         000      */
  DmaTxFetching           = 0x00100000,   /* Running - fetching the Tx descriptor                                       */
  DmaTxWaiting            = 0x00200000,   /* Running - waiting for status                                               */
  DmaTxReading            = 0x00300000,   /* Running - reading the data from host memory                                */
  DmaTxSuspended          = 0x00600000,   /* Suspended - Tx Descriptor unavailabe                                       */
  DmaTxClosing            = 0x00700000,   /* Running - closing Rx descriptor                                            */

  DmaRxState              = 0x000E0000,   /* (RS)Receive process state                         19:17  RO                */
  DmaRxStopped            = 0x00000000,   /* Stopped - Reset or Stop Rx Command issued                         000      */
  DmaRxFetching           = 0x00020000,   /* Running - fetching the Rx descriptor                                       */
  DmaRxWaiting            = 0x00060000,   /* Running - waiting for packet                                               */
  DmaRxSuspended          = 0x00080000,   /* Suspended - Rx Descriptor unavailable                                      */
  DmaRxClosing            = 0x000A0000,   /* Running - closing descriptor                                               */
  DmaRxQueuing            = 0x000E0000,   /* Running - queuing the recieve frame into host memory                       */

  DmaIntNormal            = 0x00010000,   /* (NIS)Normal interrupt summary                     16     RW        0       */
  DmaIntAbnormal          = 0x00008000,   /* (AIS)Abnormal interrupt summary                   15     RW        0       */

  DmaIntEarlyRx           = 0x00004000,   /* Early receive interrupt (Normal)       RW        0       */
  DmaIntBusError          = 0x00002000,   /* Fatal bus error (Abnormal)             RW        0       */
  DmaIntEarlyTx           = 0x00000400,   /* Early transmit interrupt (Abnormal)    RW        0       */
  DmaIntRxWdogTO          = 0x00000200,   /* Receive Watchdog Timeout (Abnormal)    RW        0       */
  DmaIntRxStopped         = 0x00000100,   /* Receive process stopped (Abnormal)     RW        0       */
  DmaIntRxNoBuffer        = 0x00000080,   /* Receive buffer unavailable (Abnormal)  RW        0       */
  DmaIntRxCompleted       = 0x00000040,   /* Completion of frame reception (Normal) RW        0       */
  DmaIntTxUnderflow       = 0x00000020,   /* Transmit underflow (Abnormal)          RW        0       */
  DmaIntRcvOverflow       = 0x00000010,   /* Receive Buffer overflow interrupt      RW        0       */
  DmaIntTxJabberTO        = 0x00000008,   /* Transmit Jabber Timeout (Abnormal)     RW        0       */
  DmaIntTxNoBuffer        = 0x00000004,   /* Transmit buffer unavailable (Normal)   RW        0       */
  DmaIntTxStopped         = 0x00000002,   /* Transmit process stopped (Abnormal)    RW        0       */
  DmaIntTxCompleted       = 0x00000001,   /* Transmit completed (Normal)            RW        0       */
};

/*DmaControl        = 0x0018,     CSR6 - Dma Operation Mode Register                */
enum DmaControlReg
{
  DmaDisableDropTcpCs     = 0x04000000,   /* (DT) Dis. drop. of tcp/ip CS error frames        26      RW        0       */

  DmaStoreAndForward      = 0x02200000,   /* (SF)Store and forward                            21      RW        0       */
  DmaFlushTxFifo          = 0x00100000,   /* (FTF)Tx FIFO controller is reset to default      20      RW        0       */

  DmaTxThreshCtrl         = 0x0001C000,   /* (TTC)Controls thre Threh of MTL tx Fifo          16:14   RW                */
  DmaTxThreshCtrl16       = 0x0001C000,   /* (TTC)Controls thre Threh of MTL tx Fifo 16       16:14   RW                */
  DmaTxThreshCtrl24       = 0x00018000,   /* (TTC)Controls thre Threh of MTL tx Fifo 24       16:14   RW                */
  DmaTxThreshCtrl32       = 0x00014000,   /* (TTC)Controls thre Threh of MTL tx Fifo 32       16:14   RW                */
  DmaTxThreshCtrl40       = 0x00010000,   /* (TTC)Controls thre Threh of MTL tx Fifo 40       16:14   RW                */
  DmaTxThreshCtrl256      = 0x0000c000,   /* (TTC)Controls thre Threh of MTL tx Fifo 256      16:14   RW                */
  DmaTxThreshCtrl192      = 0x00008000,   /* (TTC)Controls thre Threh of MTL tx Fifo 192      16:14   RW                */
  DmaTxThreshCtrl128      = 0x00004000,   /* (TTC)Controls thre Threh of MTL tx Fifo 128      16:14   RW                */
  DmaTxThreshCtrl64       = 0x00000000,   /* (TTC)Controls thre Threh of MTL tx Fifo 64       16:14   RW        000     */

  DmaTxStart              = 0x00002000,   /* (ST)Start/Stop transmission                      13      RW        0       */

  DmaRxFlowCtrlDeact      = 0x00401800,   /* (RFD)Rx flow control deact. threhold             [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact1K    = 0x00000000,   /* (RFD)Rx flow control deact. threhold (1kbytes)   [22]:12:11   RW        00       */
  DmaRxFlowCtrlDeact2K    = 0x00000800,   /* (RFD)Rx flow control deact. threhold (2kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact3K    = 0x00001000,   /* (RFD)Rx flow control deact. threhold (3kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact4K    = 0x00001800,   /* (RFD)Rx flow control deact. threhold (4kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact5K    = 0x00400000,   /* (RFD)Rx flow control deact. threhold (4kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact6K    = 0x00400800,   /* (RFD)Rx flow control deact. threhold (4kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact7K    = 0x00401000,   /* (RFD)Rx flow control deact. threhold (4kbytes)   [22]:12:11   RW                 */

  DmaRxFlowCtrlAct        = 0x00800600,   /* (RFA)Rx flow control Act. threhold              [23]:10:09   RW                 */
  DmaRxFlowCtrlAct1K      = 0x00000000,   /* (RFA)Rx flow control Act. threhold (1kbytes)    [23]:10:09   RW        00       */
  DmaRxFlowCtrlAct2K      = 0x00000200,   /* (RFA)Rx flow control Act. threhold (2kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct3K      = 0x00000400,   /* (RFA)Rx flow control Act. threhold (3kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct4K      = 0x00000300,   /* (RFA)Rx flow control Act. threhold (4kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct5K      = 0x00800000,   /* (RFA)Rx flow control Act. threhold (5kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct6K      = 0x00800200,   /* (RFA)Rx flow control Act. threhold (6kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct7K      = 0x00800400,   /* (RFA)Rx flow control Act. threhold (7kbytes)    [23]:10:09   RW                 */

  DmaRxThreshCtrl         = 0x00000018,   /* (RTC)Controls thre Threh of MTL rx Fifo          4:3   RW                */
  DmaRxThreshCtrl64       = 0x00000000,   /* (RTC)Controls thre Threh of MTL tx Fifo 64       4:3   RW                */
  DmaRxThreshCtrl32       = 0x00000008,   /* (RTC)Controls thre Threh of MTL tx Fifo 32       4:3   RW                */
  DmaRxThreshCtrl96       = 0x00000010,   /* (RTC)Controls thre Threh of MTL tx Fifo 96       4:3   RW                */
  DmaRxThreshCtrl128      = 0x00000018,   /* (RTC)Controls thre Threh of MTL tx Fifo 128      4:3   RW                */

  DmaEnHwFlowCtrl         = 0x00000100,   /* (EFC)Enable HW flow control                      8       RW                 */
  DmaDisHwFlowCtrl        = 0x00000000,   /* Disable HW flow control                                            0        */

  DmaFwdErrorFrames       = 0x00000080,   /* (FEF)Forward error frames                        7       RW        0       */
  DmaFwdUnderSzFrames     = 0x00000040,   /* (FUF)Forward undersize frames                    6       RW        0       */
  DmaTxSecondFrame        = 0x00000004,   /* (OSF)Operate on second frame                     4       RW        0       */
  DmaRxStart              = 0x00000002,   /* (SR)Start/Stop reception                         1       RW        0       */
};


/*DmaInterrupt      = 0x001C,    CSR7 - Interrupt enable Register Layout     */
enum  DmaInterruptReg
{
  DmaIeNormal            = DmaIntNormal     ,   /* Normal interrupt enable                 RW        0       */
  DmaIeAbnormal          = DmaIntAbnormal   ,   /* Abnormal interrupt enable               RW        0       */

  DmaIeEarlyRx           = DmaIntEarlyRx    ,   /* Early receive interrupt enable          RW        0       */
  DmaIeBusError          = DmaIntBusError   ,   /* Fatal bus error enable                  RW        0       */
  DmaIeEarlyTx           = DmaIntEarlyTx    ,   /* Early transmit interrupt enable         RW        0       */
  DmaIeRxWdogTO          = DmaIntRxWdogTO   ,   /* Receive Watchdog Timeout enable         RW        0       */
  DmaIeRxStopped         = DmaIntRxStopped  ,   /* Receive process stopped enable          RW        0       */
  DmaIeRxNoBuffer        = DmaIntRxNoBuffer ,   /* Receive buffer unavailable enable       RW        0       */
  DmaIeRxCompleted       = DmaIntRxCompleted,   /* Completion of frame reception enable    RW        0       */
  DmaIeTxUnderflow       = DmaIntTxUnderflow,   /* Transmit underflow enable               RW        0       */

  DmaIeRxOverflow        = DmaIntRcvOverflow,   /* Receive Buffer overflow interrupt       RW        0       */
  DmaIeTxJabberTO        = DmaIntTxJabberTO ,   /* Transmit Jabber Timeout enable          RW        0       */
  DmaIeTxNoBuffer        = DmaIntTxNoBuffer ,   /* Transmit buffer unavailable enable      RW        0       */
  DmaIeTxStopped         = DmaIntTxStopped  ,   /* Transmit process stopped enable         RW        0       */
  DmaIeTxCompleted       = DmaIntTxCompleted,   /* Transmit completed enable               RW        0       */
};



/**********************************************************
 * DMA Engine descriptors
 **********************************************************/
#ifdef ENH_DESC
/*
**********Enhanced Descritpor structure to support 8K buffer per buffer ****************************

DmaRxBaseAddr     = 0x000C,   CSR3 - Receive Descriptor list base address
DmaRxBaseAddr is the pointer to the first Rx Descriptors. the Descriptor format in Little endian with a
32 bit Data bus is as shown below

Similarly
DmaTxBaseAddr     = 0x0010,  CSR4 - Transmit Descriptor list base address
DmaTxBaseAddr is the pointer to the first Rx Descriptors. the Descriptor format in Little endian with a
32 bit Data bus is as shown below
                  --------------------------------------------------------------------------
    RDES0     |OWN (31)| Status                                                        |
          --------------------------------------------------------------------------
    RDES1     | Ctrl | Res | Byte Count Buffer 2 | Ctrl | Res | Byte Count Buffer 1    |
          --------------------------------------------------------------------------
    RDES2     |  Buffer 1 Address                                                      |
          --------------------------------------------------------------------------
    RDES3     |  Buffer 2 Address / Next Descriptor Address                            |
          --------------------------------------------------------------------------

                  --------------------------------------------------------------------------
    TDES0     |OWN (31)| Ctrl | Res | Ctrl | Res | Status                              |
          --------------------------------------------------------------------------
    TDES1     | Res | Byte Count Buffer 2 | Res |         Byte Count Buffer 1          |
          --------------------------------------------------------------------------
    TDES2     |  Buffer 1 Address                                                      |
          --------------------------------------------------------------------------
    TDES3         |  Buffer 2 Address / Next Descriptor Address                            |
          --------------------------------------------------------------------------

*/

enum DmaDescriptorStatus    /* status word of DMA descriptor */
{
  DescOwnByDma          = 0x80000000,   /* (OWN)Descriptor is owned by DMA engine              31      RW                  */

  DescDAFilterFail      = 0x40000000,   /* (AFM)Rx - DA Filter Fail for the rx frame           30                          */

  DescFrameLengthMask   = 0x3FFF0000,   /* (FL)Receive descriptor frame length                 29:16                       */
  DescFrameLengthShift  = 16,

  DescError             = 0x00008000,   /* (ES)Error summary bit  - OR of the follo. bits:     15                          */
                    /*  DE || OE || IPC || LC || RWT || RE || CE */
  DescRxTruncated       = 0x00004000,   /* (DE)Rx - no more descriptors for receive frame      14                          */
  DescSAFilterFail      = 0x00002000,   /* (SAF)Rx - SA Filter Fail for the received frame     13                          */
  DescRxLengthError = 0x00001000,   /* (LE)Rx - frm size not matching with len field       12                          */
  DescRxDamaged         = 0x00000800,   /* (OE)Rx - frm was damaged due to buffer overflow     11                          */
  DescRxVLANTag         = 0x00000400,   /* (VLAN)Rx - received frame is a VLAN frame           10                          */
  DescRxFirst           = 0x00000200,   /* (FS)Rx - first descriptor of the frame              9                          */
  DescRxLast            = 0x00000100,   /* (LS)Rx - last descriptor of the frame               8                          */
  DescRxLongFrame       = 0x00000080,   /* (Giant Frame)Rx - frame is longer than 1518/1522    7                          */
  DescRxCollision       = 0x00000040,   /* (LC)Rx - late collision occurred during reception   6                          */
  DescRxFrameEther      = 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3     5                          */
  DescRxWatchdog        = 0x00000010,   /* (RWT)Rx - watchdog timer expired during reception   4                          */
  DescRxMiiError        = 0x00000008,   /* (RE)Rx - error reported by MII interface            3                          */
  DescRxDribbling       = 0x00000004,   /* (DE)Rx - frame contains non int multiple of 8 bits  2                          */
  DescRxCrc             = 0x00000002,   /* (CE)Rx - CRC error                                  1                          */
//  DescRxMacMatch        = 0x00000001,   /* (RX MAC Address) Rx mac address reg(1 to 15)match   0                          */

  DescRxEXTsts          = 0x00000001,   /* Extended Status Available (RDES4)                           0                          */

  DescTxIntEnable       = 0x40000000,   /* (IC)Tx - interrupt on completion                    30                       */
  DescTxLast            = 0x20000000,   /* (LS)Tx - Last segment of the frame                  29                       */
  DescTxFirst           = 0x10000000,   /* (FS)Tx - First segment of the frame                 28                       */
  DescTxDisableCrc      = 0x08000000,   /* (DC)Tx - Add CRC disabled (first segment only)      27                       */
  DescTxDisablePadd = 0x04000000,   /* (DP)disable padding, added by - reyaz               26                       */

  DescTxCisMask     = 0x00c00000,   /* Tx checksum offloading control mask             23:22            */
  DescTxCisBypass   = 0x00000000,   /* Checksum bypass                              */
  DescTxCisIpv4HdrCs    = 0x00400000,   /* IPv4 header checksum                             */
  DescTxCisTcpOnlyCs    = 0x00800000,   /* TCP/UDP/ICMP checksum. Pseudo header checksum is assumed to be present   */
  DescTxCisTcpPseudoCs  = 0x00c00000,   /* TCP/UDP/ICMP checksum fully in hardware including pseudo header      */

  TxDescEndOfRing       = 0x00200000,   /* (TER)End of descriptors ring                        21                       */
  TxDescChain           = 0x00100000,   /* (TCH)Second buffer address is chain address         20                       */

  DescRxChkBit0     = 0x00000001,   /*()  Rx - Rx Payload Checksum Error                   0                          */
  DescRxChkBit7     = 0x00000080,   /* (IPC CS ERROR)Rx - Ipv4 header checksum error       7                          */
  DescRxChkBit5     = 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3     5                          */

  DescRxTSavail         = 0x00000080,   /* Time stamp available                                7                          */
  DescRxFrameType   = 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3     5                          */

  DescTxIpv4ChkError    = 0x00010000,   /* (IHE) Tx Ip header error                            16                         */
  DescTxTimeout         = 0x00004000,   /* (JT)Tx - Transmit jabber timeout                    14                         */
  DescTxFrameFlushed    = 0x00002000,   /* (FF)Tx - DMA/MTL flushed the frame due to SW flush  13                         */
  DescTxPayChkError     = 0x00001000,   /* (PCE) Tx Payload checksum Error                     12                         */
  DescTxLostCarrier     = 0x00000800,   /* (LC)Tx - carrier lost during tramsmission           11                         */
  DescTxNoCarrier       = 0x00000400,   /* (NC)Tx - no carrier signal from the tranceiver      10                         */
  DescTxLateCollision   = 0x00000200,   /* (LC)Tx - transmission aborted due to collision      9                         */
  DescTxExcCollisions   = 0x00000100,   /* (EC)Tx - transmission aborted after 16 collisions   8                         */
  DescTxVLANFrame       = 0x00000080,   /* (VF)Tx - VLAN-type frame                            7                         */

  DescTxCollMask        = 0x00000078,   /* (CC)Tx - Collision count                            6:3                        */
  DescTxCollShift       = 3,

  DescTxExcDeferral     = 0x00000004,   /* (ED)Tx - excessive deferral                         2                        */
  DescTxUnderflow       = 0x00000002,   /* (UF)Tx - late data arrival from the memory          1                        */
  DescTxDeferred        = 0x00000001,   /* (DB)Tx - frame transmision deferred                 0                        */

    /*
    This explains the RDES1/TDES1 bits layout
              --------------------------------------------------------------------
        RDES1/TDES1  | Control Bits | Byte Count Buffer 2 | Byte Count Buffer 1          |
              --------------------------------------------------------------------

    */
// DmaDescriptorLength     length word of DMA descriptor


  RxDisIntCompl     = 0x80000000,   /* (Disable Rx int on completion)           31          */
  RxDescEndOfRing       = 0x00008000,   /* (TER)End of descriptors ring                         15                       */
  RxDescChain           = 0x00004000,   /* (TCH)Second buffer address is chain address          14                       */


  DescSize2Mask         = 0x1FFF0000,   /* (TBS2) Buffer 2 size                                28:16                    */
  DescSize2Shift        = 16,
  DescSize1Mask         = 0x00001FFF,   /* (TBS1) Buffer 1 size                                12:0                     */
  DescSize1Shift        = 0,


    /*
    This explains the RDES4 Extended Status bits layout
              --------------------------------------------------------------------
        RDES4        |                             Extended Status                        |
              --------------------------------------------------------------------
    */
  DescRxPtpAvail        = 0x00004000,    /* PTP snapshot available                              14                        */
  DescRxPtpVer          = 0x00002000,    /* When set indicates IEEE1584 Version 2 (else Ver1)   13                        */
  DescRxPtpFrameType    = 0x00001000,    /* PTP frame type Indicates PTP sent over ethernet     12                        */
  DescRxPtpMessageType  = 0x00000F00,    /* Message Type                                        11:8                      */
  DescRxPtpNo           = 0x00000000,    /* 0000 => No PTP message received                                               */
  DescRxPtpSync         = 0x00000100,    /* 0001 => Sync (all clock types) received                                       */
  DescRxPtpFollowUp     = 0x00000200,    /* 0010 => Follow_Up (all clock types) received                                  */
  DescRxPtpDelayReq     = 0x00000300,    /* 0011 => Delay_Req (all clock types) received                                  */
  DescRxPtpDelayResp    = 0x00000400,    /* 0100 => Delay_Resp (all clock types) received                                 */
  DescRxPtpPdelayReq    = 0x00000500,    /* 0101 => Pdelay_Req (in P to P tras clk)  or Announce in Ord and Bound clk     */
  DescRxPtpPdelayResp   = 0x00000600,    /* 0110 => Pdealy_Resp(in P to P trans clk) or Management in Ord and Bound clk   */
  DescRxPtpPdelayRespFP = 0x00000700,    /* 0111 => Pdealy_Resp_Follow_Up (in P to P trans clk) or Signaling in Ord and Bound clk   */
  DescRxPtpIPV6         = 0x00000080,    /* Received Packet is  in IPV6 Packet                  7                         */
  DescRxPtpIPV4         = 0x00000040,    /* Received Packet is  in IPV4 Packet                  6                         */

  DescRxChkSumBypass    = 0x00000020,    /* When set indicates checksum offload engine          5
                                            is bypassed                                                                   */
  DescRxIpPayloadError  = 0x00000010,    /* When set indicates 16bit IP payload CS is in error  4                         */
  DescRxIpHeaderError   = 0x00000008,    /* When set indicates 16bit IPV4 header CS is in       3
                                            error or IP datagram version is not consistent
                                            with Ethernet type value                                                      */
  DescRxIpPayloadType   = 0x00000007,     /* Indicate the type of payload encapsulated          2:0
                                             in IPdatagram processed by COE (Rx)                                          */
  DescRxIpPayloadUnknown= 0x00000000,     /* Unknown or didnot process IP payload                                         */
  DescRxIpPayloadUDP    = 0x00000001,     /* UDP                                                                          */
  DescRxIpPayloadTCP    = 0x00000002,     /* TCP                                                                          */
  DescRxIpPayloadICMP   = 0x00000003,     /* ICMP                                                                         */

};

#else
/*

********** Default Descritpor structure  ****************************
DmaRxBaseAddr     = 0x000C,   CSR3 - Receive Descriptor list base address
DmaRxBaseAddr is the pointer to the first Rx Descriptors. the Descriptor format in Little endian with a
32 bit Data bus is as shown below

Similarly
DmaTxBaseAddr     = 0x0010,  CSR4 - Transmit Descriptor list base address
DmaTxBaseAddr is the pointer to the first Rx Descriptors. the Descriptor format in Little endian with a
32 bit Data bus is as shown below
                  --------------------------------------------------------------------
    RDES0/TDES0  |OWN (31)| Status                                                   |
          --------------------------------------------------------------------
    RDES1/TDES1  | Control Bits | Byte Count Buffer 2 | Byte Count Buffer 1          |
          --------------------------------------------------------------------
    RDES2/TDES2  |  Buffer 1 Address                                                 |
          --------------------------------------------------------------------
    RDES3/TDES3  |  Buffer 2 Address / Next Descriptor Address                       |
          --------------------------------------------------------------------
*/
enum DmaDescriptorStatus    /* status word of DMA descriptor */
{
  DescOwnByDma          = 0x80000000,   /* (OWN)Descriptor is owned by DMA engine            31      RW                  */

  DescDAFilterFail      = 0x40000000,   /* (AFM)Rx - DA Filter Fail for the rx frame         30                          */

  DescFrameLengthMask   = 0x3FFF0000,   /* (FL)Receive descriptor frame length               29:16                       */
  DescFrameLengthShift  = 16,

  DescError             = 0x00008000,   /* (ES)Error summary bit  - OR of the follo. bits:   15                          */
                    /*  DE || OE || IPC || LC || RWT || RE || CE */
  DescRxTruncated       = 0x00004000,   /* (DE)Rx - no more descriptors for receive frame    14                          */
  DescSAFilterFail      = 0x00002000,   /* (SAF)Rx - SA Filter Fail for the received frame   13                          */
  DescRxLengthError = 0x00001000,   /* (LE)Rx - frm size not matching with len field     12                          */
  DescRxDamaged         = 0x00000800,   /* (OE)Rx - frm was damaged due to buffer overflow   11                          */
  DescRxVLANTag         = 0x00000400,   /* (VLAN)Rx - received frame is a VLAN frame         10                          */
  DescRxFirst           = 0x00000200,   /* (FS)Rx - first descriptor of the frame             9                          */
  DescRxLast            = 0x00000100,   /* (LS)Rx - last descriptor of the frame              8                          */
  DescRxLongFrame       = 0x00000080,   /* (Giant Frame)Rx - frame is longer than 1518/1522   7                          */
  DescRxCollision       = 0x00000040,   /* (LC)Rx - late collision occurred during reception  6                          */
  DescRxFrameEther      = 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3    5                          */
  DescRxWatchdog        = 0x00000010,   /* (RWT)Rx - watchdog timer expired during reception  4                          */
  DescRxMiiError        = 0x00000008,   /* (RE)Rx - error reported by MII interface           3                          */
  DescRxDribbling       = 0x00000004,   /* (DE)Rx - frame contains non int multiple of 8 bits 2                          */
  DescRxCrc             = 0x00000002,   /* (CE)Rx - CRC error                                 1                          */
  DescRxMacMatch        = 0x00000001,   /* (RX MAC Address) Rx mac address reg(1 to 15)match  0                          */

  //Rx Descriptor Checksum Offload engine (type 2) encoding
  //DescRxPayChkError     = 0x00000001,   /* ()  Rx - Rx Payload Checksum Error                 0                          */
  //DescRxIpv4ChkError    = 0x00000080,   /* (IPC CS ERROR)Rx - Ipv4 header checksum error      7                          */

  DescRxChkBit0     = 0x00000001,   /*()  Rx - Rx Payload Checksum Error                  0                          */
  DescRxChkBit7     = 0x00000080,   /* (IPC CS ERROR)Rx - Ipv4 header checksum error      7                          */
  DescRxChkBit5     = 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3    5                          */

  DescTxIpv4ChkError    = 0x00010000,   /* (IHE) Tx Ip header error                           16                         */
  DescTxTimeout         = 0x00004000,   /* (JT)Tx - Transmit jabber timeout                   14                         */
  DescTxFrameFlushed    = 0x00002000,   /* (FF)Tx - DMA/MTL flushed the frame due to SW flush 13                         */
  DescTxPayChkError     = 0x00001000,   /* (PCE) Tx Payload checksum Error                    12                         */
  DescTxLostCarrier     = 0x00000800,   /* (LC)Tx - carrier lost during tramsmission          11                         */
  DescTxNoCarrier       = 0x00000400,   /* (NC)Tx - no carrier signal from the tranceiver     10                         */
  DescTxLateCollision   = 0x00000200,   /* (LC)Tx - transmission aborted due to collision      9                         */
  DescTxExcCollisions   = 0x00000100,   /* (EC)Tx - transmission aborted after 16 collisions   8                         */
  DescTxVLANFrame       = 0x00000080,   /* (VF)Tx - VLAN-type frame                            7                         */

  DescTxCollMask        = 0x00000078,   /* (CC)Tx - Collision count                           6:3                        */
  DescTxCollShift       = 3,

  DescTxExcDeferral     = 0x00000004,   /* (ED)Tx - excessive deferral                          2                        */
  DescTxUnderflow       = 0x00000002,   /* (UF)Tx - late data arrival from the memory           1                        */
  DescTxDeferred        = 0x00000001,   /* (DB)Tx - frame transmision deferred                  0                        */

    /*
    This explains the RDES1/TDES1 bits layout
              --------------------------------------------------------------------
        RDES1/TDES1  | Control Bits | Byte Count Buffer 2 | Byte Count Buffer 1          |
              --------------------------------------------------------------------

    */
//DmaDescriptorLength     length word of DMA descriptor

  DescTxIntEnable       = 0x80000000,   /* (IC)Tx - interrupt on completion                    31                       */
  DescTxLast            = 0x40000000,   /* (LS)Tx - Last segment of the frame                  30                       */
  DescTxFirst           = 0x20000000,   /* (FS)Tx - First segment of the frame                 29                       */
  DescTxDisableCrc      = 0x04000000,   /* (DC)Tx - Add CRC disabled (first segment only)      26                       */

  RxDisIntCompl     = 0x80000000,   /* (Disable Rx int on completion)           31          */
  RxDescEndOfRing       = 0x02000000,   /* (TER)End of descriptors ring                                                 */
  RxDescChain           = 0x01000000,   /* (TCH)Second buffer address is chain address         24                       */

  DescTxDisablePadd = 0x00800000,   /* (DP)disable padding, added by - reyaz               23                       */

  TxDescEndOfRing       = 0x02000000,   /* (TER)End of descriptors ring                                                 */
  TxDescChain           = 0x01000000,   /* (TCH)Second buffer address is chain address         24                       */

  DescSize2Mask         = 0x003FF800,   /* (TBS2) Buffer 2 size                                21:11                    */
  DescSize2Shift        = 11,
  DescSize1Mask         = 0x000007FF,   /* (TBS1) Buffer 1 size                                10:0                     */
  DescSize1Shift        = 0,


  DescTxCisMask     = 0x18000000,   /* Tx checksum offloading control mask          28:27           */
  DescTxCisBypass   = 0x00000000,   /* Checksum bypass                              */
  DescTxCisIpv4HdrCs    = 0x08000000,   /* IPv4 header checksum                             */
  DescTxCisTcpOnlyCs    = 0x10000000,   /* TCP/UDP/ICMP checksum. Pseudo header checksum is assumed to be present   */
  DescTxCisTcpPseudoCs  = 0x18000000,   /* TCP/UDP/ICMP checksum fully in hardware including pseudo header      */
};
#endif

// Rx Descriptor COE type2 encoding
enum RxDescCOEEncode
{
  RxLenLT600            = 0,    /* Bit(5:7:0)=>0 IEEE 802.3 type frame Length field is Lessthan 0x0600          */
  RxIpHdrPayLoadChkBypass   = 1,    /* Bit(5:7:0)=>1 Payload & Ip header checksum bypassed (unsuppported payload)       */
  RxIpHdrPayLoadRes     = 2,    /* Bit(5:7:0)=>2 Reserved                               */
  RxChkBypass           = 3,    /* Bit(5:7:0)=>3 Neither IPv4 nor IPV6. So checksum bypassed                */
  RxNoChkError          = 4,    /* Bit(5:7:0)=>4 No IPv4/IPv6 Checksum error detected                   */
  RxPayLoadChkError     = 5,    /* Bit(5:7:0)=>5 Payload checksum error detected for Ipv4/Ipv6 frames           */
  RxIpHdrChkError       = 6,    /* Bit(5:7:0)=>6 Ip header checksum error detected for Ipv4 frames          */
  RxIpHdrPayLoadChkError    = 7,    /* Bit(5:7:0)=>7 Payload & Ip header checksum error detected for Ipv4/Ipv6 frames   */
};

/**********************************************************
 * DMA engine interrupt handling functions
 **********************************************************/

 enum synopGMACDmaIntEnum  /* Intrerrupt types */
{
  synopGMACDmaRxNormal   = 0x01,   /* normal receiver interrupt */
  synopGMACDmaRxAbnormal = 0x02,   /* abnormal receiver interrupt */
  synopGMACDmaRxStopped  = 0x04,   /* receiver stopped */
  synopGMACDmaTxNormal   = 0x08,   /* normal transmitter interrupt */
  synopGMACDmaTxAbnormal = 0x10,   /* abnormal transmitter interrupt */
  synopGMACDmaTxStopped  = 0x20,   /* transmitter stopped */
  synopGMACDmaError      = 0x80,   /* Dma engine error */
};


/**********************************************************
 * Initial register values
 **********************************************************/
enum InitialRegisters
{
   /* Full-duplex mode with perfect filter on */
  GmacConfigInitFdx1000   = GmacWatchdogEnable | GmacJabberEnable         | GmacFrameBurstEnable | GmacJumboFrameDisable
                          | GmacSelectGmii     | GmacEnableRxOwn          | GmacLoopbackOff
                          | GmacFullDuplex     | GmacRetryEnable          | GmacPadCrcStripDisable
                          | GmacBackoffLimit0  | GmacDeferralCheckDisable | GmacTxEnable          | GmacRxEnable,

  /* Full-duplex mode with perfect filter on */
  GmacConfigInitFdx110    = GmacWatchdogEnable | GmacJabberEnable         | GmacFrameBurstEnable  | GmacJumboFrameDisable
                          | GmacSelectMii      | GmacEnableRxOwn          | GmacLoopbackOff
                          | GmacFullDuplex     | GmacRetryEnable          | GmacPadCrcStripDisable
                          | GmacBackoffLimit0  | GmacDeferralCheckDisable | GmacTxEnable          | GmacRxEnable,

   /* Full-duplex mode */
   // CHANGED: Pass control config, dest addr filter normal, added source address filter, multicast & unicast
   // Hash filter.
   /*                        = GmacFilterOff         | GmacPassControlOff | GmacBroadcastEnable */
   GmacFrameFilterInitFdx = GmacFilterOn          | GmacPassControl0   | GmacBroadcastEnable |  GmacSrcAddrFilterDisable
                           | GmacMulticastFilterOn | GmacDestAddrFilterNor | GmacMcastHashFilterOff
                          | GmacPromiscuousModeOff | GmacUcastHashFilterOff,

   /* Full-duplex mode */
   GmacFlowControlInitFdx = GmacUnicastPauseFrameOff | GmacRxFlowControlEnable | GmacTxFlowControlEnable,

   /* Full-duplex mode */
   GmacGmiiAddrInitFdx    = GmiiCsrClk2,


   /* Half-duplex mode with perfect filter on */
   // CHANGED: Removed Endian configuration, added single bit config for PAD/CRC strip,
   /*| GmacSelectMii      | GmacLittleEndian         | GmacDisableRxOwn      | GmacLoopbackOff*/
   GmacConfigInitHdx1000  = GmacWatchdogEnable | GmacJabberEnable         | GmacFrameBurstEnable  | GmacJumboFrameDisable
                          | GmacSelectGmii     | GmacDisableRxOwn         | GmacLoopbackOff
                          | GmacHalfDuplex     | GmacRetryEnable          | GmacPadCrcStripDisable
                          | GmacBackoffLimit0  | GmacDeferralCheckDisable | GmacTxEnable          | GmacRxEnable,

   /* Half-duplex mode with perfect filter on */
   GmacConfigInitHdx110   = GmacWatchdogEnable | GmacJabberEnable         | GmacFrameBurstEnable  | GmacJumboFrameDisable
                          | GmacSelectMii      | GmacDisableRxOwn         | GmacLoopbackOff
                          | GmacHalfDuplex     | GmacRetryEnable          | GmacPadCrcStripDisable
                          | GmacBackoffLimit0  | GmacDeferralCheckDisable | GmacTxEnable          | GmacRxEnable,

   /* Half-duplex mode */
   GmacFrameFilterInitHdx = GmacFilterOn          | GmacPassControl0        | GmacBroadcastEnable | GmacSrcAddrFilterDisable
                          | GmacMulticastFilterOn | GmacDestAddrFilterNor   | GmacMcastHashFilterOff
                          | GmacUcastHashFilterOff| GmacPromiscuousModeOff,

   /* Half-duplex mode */
   GmacFlowControlInitHdx = GmacUnicastPauseFrameOff | GmacRxFlowControlDisable | GmacTxFlowControlDisable,

   /* Half-duplex mode */
   GmacGmiiAddrInitHdx    = GmiiCsrClk2,



   /**********************************************
   *DMA configurations
   **********************************************/

  DmaBusModeInit         = DmaFixedBurstEnable |   DmaBurstLength8   | DmaDescriptorSkip2       | DmaResetOff,
//   DmaBusModeInit         = DmaFixedBurstEnable |   DmaBurstLength8   | DmaDescriptorSkip4       | DmaResetOff,

   /* 1000 Mb/s mode */
   DmaControlInit1000     = DmaStoreAndForward,//       | DmaTxSecondFrame ,

   /* 100 Mb/s mode */
   DmaControlInit100      = DmaStoreAndForward,

   /* 10 Mb/s mode */
   DmaControlInit10       = DmaStoreAndForward,

  /* Interrupt groups */
  DmaIntErrorMask         = DmaIntBusError,           /* Error */
  DmaIntRxAbnMask         = DmaIntRxNoBuffer,         /* receiver abnormal interrupt */
  DmaIntRxNormMask        = DmaIntRxCompleted,        /* receiver normal interrupt   */
  DmaIntRxStoppedMask     = DmaIntRxStopped,          /* receiver stopped */
  DmaIntTxAbnMask         = DmaIntTxUnderflow,        /* transmitter abnormal interrupt */
  DmaIntTxNormMask        = DmaIntTxCompleted,        /* transmitter normal interrupt */
  DmaIntTxStoppedMask     = DmaIntTxStopped,          /* transmitter stopped */

  DmaIntEnable            = DmaIeNormal     | DmaIeAbnormal    | DmaIntErrorMask
//DmaIntEnable            = DmaIeNormal     | DmaIntErrorMask
                          | DmaIntRxAbnMask | DmaIntRxNormMask | DmaIntRxStoppedMask
//                          | DmaIntRxNormMask | DmaIntRxStoppedMask
                          | DmaIntTxAbnMask | DmaIntTxNormMask | DmaIntTxStoppedMask,
  DmaIntDisable           = 0,
};


/**********************************************************
 * Mac Management Counters (MMC)
 **********************************************************/

enum MMC_ENABLE
{
    GmacMmcCntrl            = 0x0100,   /* mmc control for operating mode of MMC                        */
    GmacMmcIntrRx           = 0x0104,   /* maintains interrupts generated by rx counters                    */
    GmacMmcIntrTx           = 0x0108,   /* maintains interrupts generated by tx counters                    */
    GmacMmcIntrMaskRx       = 0x010C,   /* mask for interrupts generated from rx counters                   */
    GmacMmcIntrMaskTx       = 0x0110,   /* mask for interrupts generated from tx counters                   */
};
enum MMC_TX
{
    GmacMmcTxOctetCountGb       = 0x0114,   /*Bytes Tx excl. of preamble and retried bytes     (Good or Bad)            */
    GmacMmcTxFrameCountGb       = 0x0118,   /*Frames Tx excl. of retried frames            (Good or Bad)            */
    GmacMmcTxBcFramesG      = 0x011C,   /*Broadcast Frames Tx                  (Good)               */
    GmacMmcTxMcFramesG      = 0x0120,   /*Multicast Frames Tx                  (Good)               */

    GmacMmcTx64OctetsGb     = 0x0124,   /*Tx with len 64 bytes excl. of pre and retried    (Good or Bad)            */
    GmacMmcTx65To127OctetsGb    = 0x0128,   /*Tx with len >64 bytes <=127 excl. of pre and retried    (Good or Bad)         */
    GmacMmcTx128To255OctetsGb   = 0x012C,   /*Tx with len >128 bytes <=255 excl. of pre and retried   (Good or Bad)         */
    GmacMmcTx256To511OctetsGb   = 0x0130,   /*Tx with len >256 bytes <=511 excl. of pre and retried   (Good or Bad)         */
    GmacMmcTx512To1023OctetsGb  = 0x0134,   /*Tx with len >512 bytes <=1023 excl. of pre and retried  (Good or Bad)         */
    GmacMmcTx1024ToMaxOctetsGb  = 0x0138,   /*Tx with len >1024 bytes <=MaxSize excl. of pre and retried (Good or Bad)      */

    GmacMmcTxUcFramesGb     = 0x013C,   /*Unicast Frames Tx                      (Good or Bad)          */
    GmacMmcTxMcFramesGb     = 0x0140,   /*Multicast Frames Tx                  (Good and Bad)           */
    GmacMmcTxBcFramesGb     = 0x0144,   /*Broadcast Frames Tx                  (Good and Bad)           */
    GmacMmcTxUnderFlowError     = 0x0148,   /*Frames aborted due to Underflow error                         */
    GmacMmcTxSingleColG     = 0x014C,   /*Successfully Tx Frames after singel collision in Half duplex mode         */
    GmacMmcTxMultiColG      = 0x0150,   /*Successfully Tx Frames after more than singel collision in Half duplex mode       */
    GmacMmcTxDeferred       = 0x0154,   /*Successfully Tx Frames after a deferral in Half duplex mode               */
    GmacMmcTxLateCol        = 0x0158,   /*Frames aborted due to late collision error                        */
    GmacMmcTxExessCol       = 0x015C,   /*Frames aborted due to excessive (16) collision errors                 */
    GmacMmcTxCarrierError       = 0x0160,   /*Frames aborted due to carrier sense error (No carrier or Loss of carrier)     */
    GmacMmcTxOctetCountG        = 0x0164,   /*Bytes Tx excl. of preamble and retried bytes     (Good)               */
    GmacMmcTxFrameCountG        = 0x0168,   /*Frames Tx                            (Good)               */
    GmacMmcTxExessDef       = 0x016C,   /*Frames aborted due to excessive deferral errors (deferred for more than 2 max-sized frame times)*/

    GmacMmcTxPauseFrames        = 0x0170,   /*Number of good pause frames Tx.                           */
    GmacMmcTxVlanFramesG        = 0x0174,   /*Number of good Vlan frames Tx excl. retried frames                    */
};
enum MMC_RX
{
    GmacMmcRxFrameCountGb       = 0x0180,   /*Frames Rx                            (Good or Bad)            */
    GmacMmcRxOctetCountGb       = 0x0184,   /*Bytes Rx excl. of preamble and retried bytes     (Good or Bad)            */
    GmacMmcRxOctetCountG        = 0x0188,   /*Bytes Rx excl. of preamble and retried bytes     (Good)               */
    GmacMmcRxBcFramesG      = 0x018C,   /*Broadcast Frames Rx                  (Good)               */
    GmacMmcRxMcFramesG      = 0x0190,   /*Multicast Frames Rx                  (Good)               */

    GmacMmcRxCrcError       = 0x0194,   /*Number of frames received with CRC error                      */
    GmacMmcRxAlignError     = 0x0198,   /*Number of frames received with alignment (dribble) error. Only in 10/100mode      */
    GmacMmcRxRuntError      = 0x019C,   /*Number of frames received with runt (<64 bytes and CRC error) error           */
    GmacMmcRxJabberError        = 0x01A0,   /*Number of frames rx with jabber (>1518/1522 or >9018/9022 and CRC)            */
    GmacMmcRxUnderSizeG     = 0x01A4,   /*Number of frames received with <64 bytes without any error                */
    GmacMmcRxOverSizeG      = 0x01A8,   /*Number of frames received with >1518/1522 bytes without any error         */

    GmacMmcRx64OctetsGb     = 0x01AC,   /*Rx with len 64 bytes excl. of pre and retried    (Good or Bad)            */
    GmacMmcRx65To127OctetsGb    = 0x01B0,   /*Rx with len >64 bytes <=127 excl. of pre and retried    (Good or Bad)         */
    GmacMmcRx128To255OctetsGb   = 0x01B4,   /*Rx with len >128 bytes <=255 excl. of pre and retried   (Good or Bad)         */
    GmacMmcRx256To511OctetsGb   = 0x01B8,   /*Rx with len >256 bytes <=511 excl. of pre and retried   (Good or Bad)         */
    GmacMmcRx512To1023OctetsGb  = 0x01BC,   /*Rx with len >512 bytes <=1023 excl. of pre and retried  (Good or Bad)         */
    GmacMmcRx1024ToMaxOctetsGb  = 0x01C0,   /*Rx with len >1024 bytes <=MaxSize excl. of pre and retried (Good or Bad)      */

    GmacMmcRxUcFramesG      = 0x01C4,   /*Unicast Frames Rx                      (Good)             */
    GmacMmcRxLengthError        = 0x01C8,   /*Number of frames received with Length type field != frame size            */
    GmacMmcRxOutOfRangeType     = 0x01CC,   /*Number of frames received with length field != valid frame size           */

    GmacMmcRxPauseFrames        = 0x01D0,   /*Number of good pause frames Rx.                           */
    GmacMmcRxFifoOverFlow       = 0x01D4,   /*Number of missed rx frames due to FIFO overflow                   */
    GmacMmcRxVlanFramesGb       = 0x01D8,   /*Number of good Vlan frames Rx                             */

    GmacMmcRxWatchdobError      = 0x01DC,   /*Number of frames rx with error due to watchdog timeout error              */
};
enum MMC_IP_RELATED
{
    GmacMmcRxIpcIntrMask        = 0x0200,   /*Maintains the mask for interrupt generated from rx IPC statistic counters         */
    GmacMmcRxIpcIntr        = 0x0208,   /*Maintains the interrupt that rx IPC statistic counters generate           */

    GmacMmcRxIpV4FramesG        = 0x0210,   /*Good IPV4 datagrams received                              */
    GmacMmcRxIpV4HdrErrFrames   = 0x0214,   /*Number of IPV4 datagrams received with header errors                  */
    GmacMmcRxIpV4NoPayFrames    = 0x0218,   /*Number of IPV4 datagrams received which didnot have TCP/UDP/ICMP payload      */
    GmacMmcRxIpV4FragFrames     = 0x021C,   /*Number of IPV4 datagrams received with fragmentation                  */
    GmacMmcRxIpV4UdpChkDsblFrames   = 0x0220,   /*Number of IPV4 datagrams received that had a UDP payload checksum disabled        */

    GmacMmcRxIpV6FramesG        = 0x0224,   /*Good IPV6 datagrams received                              */
    GmacMmcRxIpV6HdrErrFrames   = 0x0228,   /*Number of IPV6 datagrams received with header errors                  */
    GmacMmcRxIpV6NoPayFrames    = 0x022C,   /*Number of IPV6 datagrams received which didnot have TCP/UDP/ICMP payload      */

    GmacMmcRxUdpFramesG     = 0x0230,   /*Number of good IP datagrams with good UDP payload                 */
    GmacMmcRxUdpErrorFrames     = 0x0234,   /*Number of good IP datagrams with UDP payload having checksum error            */

    GmacMmcRxTcpFramesG     = 0x0238,   /*Number of good IP datagrams with good TDP payload                 */
    GmacMmcRxTcpErrorFrames     = 0x023C,   /*Number of good IP datagrams with TCP payload having checksum error            */

    GmacMmcRxIcmpFramesG        = 0x0240,   /*Number of good IP datagrams with good Icmp payload                    */
    GmacMmcRxIcmpErrorFrames    = 0x0244,   /*Number of good IP datagrams with Icmp payload having checksum error           */

    GmacMmcRxIpV4OctetsG        = 0x0250,   /*Good IPV4 datagrams received excl. Ethernet hdr,FCS,Pad,Ip Pad bytes          */
    GmacMmcRxIpV4HdrErrorOctets = 0x0254,   /*Number of bytes in IPV4 datagram with header errors                   */
    GmacMmcRxIpV4NoPayOctets    = 0x0258,   /*Number of bytes in IPV4 datagram with no TCP/UDP/ICMP payload             */
    GmacMmcRxIpV4FragOctets     = 0x025C,   /*Number of bytes received in fragmented IPV4 datagrams                 */
    GmacMmcRxIpV4UdpChkDsblOctets   = 0x0260,   /*Number of bytes received in UDP segment that had UDP checksum disabled        */

    GmacMmcRxIpV6OctetsG        = 0x0264,   /*Good IPV6 datagrams received excl. Ethernet hdr,FCS,Pad,Ip Pad bytes          */
    GmacMmcRxIpV6HdrErrorOctets = 0x0268,   /*Number of bytes in IPV6 datagram with header errors                   */
    GmacMmcRxIpV6NoPayOctets    = 0x026C,   /*Number of bytes in IPV6 datagram with no TCP/UDP/ICMP payload             */

    GmacMmcRxUdpOctetsG     = 0x0270,   /*Number of bytes in IP datagrams with good UDP payload                 */
    GmacMmcRxUdpErrorOctets     = 0x0274,   /*Number of bytes in IP datagrams with UDP payload having checksum error        */

    GmacMmcRxTcpOctetsG     = 0x0278,   /*Number of bytes in IP datagrams with good TDP payload                 */
    GmacMmcRxTcpErrorOctets     = 0x027C,   /*Number of bytes in IP datagrams with TCP payload having checksum error        */

    GmacMmcRxIcmpOctetsG        = 0x0280,   /*Number of bytes in IP datagrams with good Icmp payload                */
    GmacMmcRxIcmpErrorOctets    = 0x0284,   /*Number of bytes in IP datagrams with Icmp payload having checksum error       */
};


enum MMC_CNTRL_REG_BIT_DESCRIPTIONS
{
    GmacMmcCounterFreeze        = 0x00000008,       /* when set MMC counters freeze to current value                */
    GmacMmcCounterResetOnRead   = 0x00000004,       /* when set MMC counters will be reset to 0 after read              */
    GmacMmcCounterStopRollover  = 0x00000002,       /* when set counters will not rollover after max value              */
    GmacMmcCounterReset     = 0x00000001,       /* when set all counters wil be reset (automatically cleared after 1 clk)   */

};

enum MMC_RX_INTR_MASK_AND_STATUS_BIT_DESCRIPTIONS
{
    GmacMmcRxWDInt          = 0x00800000,       /* set when rxwatchdog error reaches half of max value              */
    GmacMmcRxVlanInt        = 0x00400000,       /* set when GmacMmcRxVlanFramesGb counter reaches half of max value     */
    GmacMmcRxFifoOverFlowInt    = 0x00200000,       /* set when GmacMmcRxFifoOverFlow counter reaches half of max value     */
    GmacMmcRxPauseFrameInt      = 0x00100000,       /* set when GmacMmcRxPauseFrames counter reaches half of max value      */
    GmacMmcRxOutOfRangeInt      = 0x00080000,       /* set when GmacMmcRxOutOfRangeType counter reaches half of max value       */
    GmacMmcRxLengthErrorInt     = 0x00040000,       /* set when GmacMmcRxLengthError counter reaches half of max value      */
    GmacMmcRxUcFramesInt        = 0x00020000,       /* set when GmacMmcRxUcFramesG counter reaches half of max value        */
    GmacMmcRx1024OctInt     = 0x00010000,       /* set when GmacMmcRx1024ToMaxOctetsGb counter reaches half of max value    */
    GmacMmcRx512OctInt      = 0x00008000,       /* set when GmacMmcRx512To1023OctetsGb counter reaches half of max value    */
    GmacMmcRx256OctInt      = 0x00004000,       /* set when GmacMmcRx256To511OctetsGb counter reaches half of max value     */
    GmacMmcRx128OctInt      = 0x00002000,       /* set when GmacMmcRx128To255OctetsGb counter reaches half of max value     */
    GmacMmcRx65OctInt       = 0x00001000,       /* set when GmacMmcRx65To127OctetsG counter reaches half of max value       */
    GmacMmcRx64OctInt       = 0x00000800,       /* set when GmacMmcRx64OctetsGb counter reaches half of max value       */
    GmacMmcRxOverSizeInt        = 0x00000400,       /* set when GmacMmcRxOverSizeG counter reaches half of max value        */
    GmacMmcRxUnderSizeInt       = 0x00000200,       /* set when GmacMmcRxUnderSizeG counter reaches half of max value       */
    GmacMmcRxJabberErrorInt     = 0x00000100,       /* set when GmacMmcRxJabberError counter reaches half of max value      */
    GmacMmcRxRuntErrorInt       = 0x00000080,       /* set when GmacMmcRxRuntError counter reaches half of max value        */
    GmacMmcRxAlignErrorInt      = 0x00000040,       /* set when GmacMmcRxAlignError counter reaches half of max value       */
    GmacMmcRxCrcErrorInt        = 0x00000020,       /* set when GmacMmcRxCrcError counter reaches half of max value         */
    GmacMmcRxMcFramesInt        = 0x00000010,       /* set when GmacMmcRxMcFramesG counter reaches half of max value        */
    GmacMmcRxBcFramesInt        = 0x00000008,       /* set when GmacMmcRxBcFramesG counter reaches half of max value        */
    GmacMmcRxOctetGInt      = 0x00000004,       /* set when GmacMmcRxOctetCountG counter reaches half of max value      */
    GmacMmcRxOctetGbInt     = 0x00000002,       /* set when GmacMmcRxOctetCountGb counter reaches half of max value     */
    GmacMmcRxFrameInt       = 0x00000001,       /* set when GmacMmcRxFrameCountGb counter reaches half of max value     */
};

enum MMC_TX_INTR_MASK_AND_STATUS_BIT_DESCRIPTIONS
{

    GmacMmcTxVlanInt        = 0x01000000,       /* set when GmacMmcTxVlanFramesG counter reaches half of max value      */
    GmacMmcTxPauseFrameInt      = 0x00800000,       /* set when GmacMmcTxPauseFrames counter reaches half of max value      */
    GmacMmcTxExessDefInt        = 0x00400000,       /* set when GmacMmcTxExessDef counter reaches half of max value         */
    GmacMmcTxFrameInt       = 0x00200000,       /* set when GmacMmcTxFrameCount counter reaches half of max value       */
    GmacMmcTxOctetInt       = 0x00100000,       /* set when GmacMmcTxOctetCountG counter reaches half of max value      */
    GmacMmcTxCarrierErrorInt    = 0x00080000,       /* set when GmacMmcTxCarrierError counter reaches half of max value     */
    GmacMmcTxExessColInt        = 0x00040000,       /* set when GmacMmcTxExessCol counter reaches half of max value         */
    GmacMmcTxLateColInt     = 0x00020000,       /* set when GmacMmcTxLateCol counter reaches half of max value          */
    GmacMmcTxDeferredInt        = 0x00010000,       /* set when GmacMmcTxDeferred counter reaches half of max value         */
    GmacMmcTxMultiColInt        = 0x00008000,       /* set when GmacMmcTxMultiColG counter reaches half of max value        */
    GmacMmcTxSingleCol      = 0x00004000,       /* set when GmacMmcTxSingleColG counter reaches half of max value       */
    GmacMmcTxUnderFlowErrorInt  = 0x00002000,       /* set when GmacMmcTxUnderFlowError counter reaches half of max value       */
    GmacMmcTxBcFramesGbInt      = 0x00001000,       /* set when GmacMmcTxBcFramesGb counter reaches half of max value       */
    GmacMmcTxMcFramesGbInt      = 0x00000800,       /* set when GmacMmcTxMcFramesGb counter reaches half of max value       */
    GmacMmcTxUcFramesInt        = 0x00000400,       /* set when GmacMmcTxUcFramesGb counter reaches half of max value       */
    GmacMmcTx1024OctInt         = 0x00000200,       /* set when GmacMmcTx1024ToMaxOctetsGb counter reaches half of max value    */
    GmacMmcTx512OctInt      = 0x00000100,       /* set when GmacMmcTx512To1023OctetsGb counter reaches half of max value    */
    GmacMmcTx256OctInt      = 0x00000080,       /* set when GmacMmcTx256To511OctetsGb counter reaches half of max value     */
    GmacMmcTx128OctInt      = 0x00000040,       /* set when GmacMmcTx128To255OctetsGb counter reaches half of max value     */
    GmacMmcTx65OctInt       = 0x00000020,       /* set when GmacMmcTx65To127OctetsGb counter reaches half of max value      */
    GmacMmcTx64OctInt       = 0x00000010,       /* set when GmacMmcTx64OctetsGb counter reaches half of max value       */
    GmacMmcTxMcFramesInt        = 0x00000008,       /* set when GmacMmcTxMcFramesG counter reaches half of max value        */
    GmacMmcTxBcFramesInt        = 0x00000004,       /* set when GmacMmcTxBcFramesG counter reaches half of max value        */
    GmacMmcTxFrameGbInt         = 0x00000002,       /* set when GmacMmcTxFrameCountGb counter reaches half of max value     */
    GmacMmcTxOctetGbInt         = 0x00000001,       /* set when GmacMmcTxOctetCountGb counter reaches half of max value     */

};


/**********************************************************
 * Power Management (PMT) Block
 **********************************************************/

/**
  * PMT supports the reception of network (remote) wake-up frames and Magic packet frames.
  * It generates interrupts for wake-up frames and Magic packets received by GMAC.
  * PMT sits in Rx path and is enabled with remote wake-up frame enable and Magic packet enable.
  * These enable are in PMT control and Status register and are programmed by apllication.
  *
  * When power down mode is enabled in PMT, all rx frames are dropped by the core. Core comes
  * out of power down mode only when either Magic packe tor a Remote wake-up frame is received
  * and the corresponding detection is enabled.
  *
  * Driver need not be modified to support this feature. Only Api to put the device in to power
  * down mode is sufficient
  */

#define WAKEUP_REG_LENGTH   8               /*This is the reg length for wake up register configuration*/

enum GmacPmtCtrlStatusBitDefinition
{
    GmacPmtFrmFilterPtrReset    = 0x80000000,       /* when set remote wake-up frame filter register pointer to 3'b000 */
    GmacPmtGlobalUnicast        = 0x00000200,       /* When set enables any unicast packet to be a wake-up frame       */
    GmacPmtWakeupFrameReceived  = 0x00000040,       /* Wake up frame received                      */
    GmacPmtMagicPktReceived     = 0x00000020,       /* Magic Packet received                       */
    GmacPmtWakeupFrameEnable    = 0x00000004,       /* Wake-up frame enable                        */
    GmacPmtMagicPktEnable       = 0x00000002,       /* Magic packet enable                         */
    GmacPmtPowerDown        = 0x00000001,       /* Power Down                              */
};




/**********************************************************
 * IEEE 1588-2008 Precision Time Protocol (PTP) Support
 **********************************************************/
enum PTPMessageType
{
    SYNC               = 0x0,
    Delay_Req          = 0x1,
    Pdelay_Req             = 0x2,
    Pdelay_Resp            = 0x3,
    Follow_up              = 0x8,
    Delay_Resp             = 0x9,
    Pdelay_Resp_Follow_Up  = 0xA,
    Announce               = 0xB,
    Signaling              = 0xC,
    Management             = 0xD,
};



typedef struct TimeStampStruct
{
  u32   TSversion;      /* PTP Version 1 or PTP version2                                                                          */
  u32   TSmessagetype;  /* Message type associated with this time stamp                                                           */

  u16   TShighest16;    /* Highest 16 bit time stamp value, Valid onley when ADV_TIME_HIGH_WORD configured in corekit         */
  u32   TSupper32;      /* Most significant 32 bit time stamp value                               */
  u32   TSlower32;      /* Least Significat 32 bit time stamp value                               */

} TimeStamp;


/**
  * IEEE 1588-2008 is the optional module to support Ethernet frame time stamping.
  * Sixty four (+16) bit time stamps are given in each frames transmit and receive status.
  * The driver assumes the following
  *  1. "IEEE 1588 Time Stamping" "TIME_STAMPING"is ENABLED in corekit
  *  2. "IEEE 1588 External Time Stamp Input Enable" "EXT_TIME_STAMPING" is DISABLED in corekit
  *  3. "IEEE 1588 Advanced Time Stamp support" "ADV_TIME_STAMPING" is ENABLED in corekit
  *  4. "IEEE 1588 Higher Word Register Enable" "ADV_TIME_HIGH_WORD" is ENABLED in corekit
  */

/* GmacTSControl  = 0x0700,   Controls the Timestamp update logic  : only when IEEE 1588 time stamping is enabled in corekit         */
enum GmacTSControlReg
{
  GmacTSENMACADDR     = 0x00040000,     /* Enable Mac Addr for PTP filtering     18            RW         0     */

  GmacTSCLKTYPE       = 0x00030000,     /* Select the type of clock node         17:16         RW         00    */
  /*
      TSCLKTYPE        TSMSTRENA      TSEVNTENA         Messages for wihich TS snapshot is taken
       00/01                X             0              SYNC, FOLLOW_UP, DELAY_REQ, DELAY_RESP
       00/01                1             0              DELAY_REQ
       00/01                0             1              SYNC
        10                  NA            0              SYNC, FOLLOW_UP, DELAY_REQ, DELAY_RESP
        10                  NA            1              SYNC, FOLLOW_UP
        11                  NA            0              SYNC, FOLLOW_UP, DELAY_REQ, DELAY_RESP, PDELAY_REQ, PDELAY_RESP
        11                  NA            1              SYNC, PDELAY_REQ, PDELAY_RESP
  */
  GmacTSOrdClk        = 0x00000000,     /* 00=> Ordinary clock*/
  GmacTSBouClk        = 0x00010000,     /* 01=> Boundary clock*/
  GmacTSEtoEClk       = 0x00020000,     /* 10=> End-to-End transparent clock*/
  GmacTSPtoPClk       = 0x00030000,     /* 11=> P-to-P transparent clock*/

  GmacTSMSTRENA       = 0x00008000,     /* Ena TS Snapshot for Master Messages   15            RW         0     */
  GmacTSEVNTENA       = 0x00004000,     /* Ena TS Snapshot for Event Messages    14            RW         0     */
  GmacTSIPV4ENA       = 0x00002000,     /* Ena TS snapshot for IPv4              13            RW         1     */
  GmacTSIPV6ENA       = 0x00001000,     /* Ena TS snapshot for IPv6              12            RW         0     */
  GmacTSIPENA         = 0x00000800,     /* Ena TS snapshot for PTP over E'net    11            RW         0     */
  GmacTSVER2ENA       = 0x00000400,     /* Ena PTP snooping for version 2        10            RW         0     */

  GmacTSCTRLSSR           = 0x00000200,      /* Digital or Binary Rollover           9             RW         0     */

  GmacTSENALL             = 0x00000100,      /* Enable TS fro all frames (Ver2 only) 8             RW         0     */

  GmacTSADDREG        = 0x00000020,      /* Addend Register Update           5             RW_SC      0     */
  GmacTSUPDT          = 0x00000008,      /* Time Stamp Update            3             RW_SC      0     */
  GmacTSINT       = 0x00000004,      /* Time Atamp Initialize            2             RW_SC      0     */

  GmacTSTRIG          = 0x00000010,      /* Time stamp interrupt Trigger Enable  4             RW_SC      0     */

  GmacTSCFUPDT        = 0x00000002,      /* Time Stamp Fine/Coarse           1             RW         0     */
  GmacTSCUPDTCoarse   = 0x00000000,      /* 0=> Time Stamp update method is coarse                      */
  GmacTSCUPDTFine     = 0x00000002,      /* 1=> Time Stamp update method is fine                    */

  GmacTSENA       = 0x00000001,      /* Time Stamp Enable                    0             RW         0     */
};


/*  GmacTSSubSecIncr          = 0x0704,   8 bit value by which sub second register is incremented     : only when IEEE 1588 time stamping without external timestamp input */
enum GmacTSSubSecIncrReg
{
  GmacSSINCMsk            = 0x000000FF,       /* Only Lower 8 bits are valid bits     7:0           RW         00    */
};

/*  GmacTSLow         = 0x070C,   Indicates whether the timestamp low count is positive or negative; for Adv timestamp it is always zero */
enum GmacTSSign
{
  GmacTSSign              = 0x80000000,      /* PSNT                                  31            RW          0    */
  GmacTSPositive          = 0x00000000,
  GmacTSNegative          = 0x80000000,
};

/*GmacTargetTimeLow       = 0x0718,   32 bit nano seconds(MS) to be compared with system time     : only when IEEE 1588 time stamping without external timestamp input */
enum GmacTSLowReg
{
  GmacTSDecThr            = 0x3B9AC9FF,      /*when TSCTRLSSR is set the max value for GmacTargetTimeLowReg and GmacTimeStampLow register is 0x3B9AC9FF at 1ns precision       */
};

/* GmacTSHighWord          = 0x0724,   Time Stamp Higher Word Register (Version 2 only); only lower 16 bits are valid                                                   */
enum GmacTSHighWordReg
{
  GmacTSHighWordMask      = 0x0000FFFF,     /* Time Stamp Higher work register has only lower 16 bits valid         */
};
/*GmacTSStatus            = 0x0728,   Time Stamp Status Register                                                                                                       */
enum GmacTSStatusReg
{
  GmacTSTargTimeReached   = 0x00000002,     /* Time Stamp Target Time Reached          1             RO          0    */
  GmacTSSecondsOverflow   = 0x00000001,     /* Time Stamp Seconds Overflow             0             RO          0    */
};


/**********************************************************
 * Time stamp related functions
 **********************************************************/
void synopGMAC_TS_enable(synopGMACdevice *gmacdev);
void synopGMAC_TS_disable(synopGMACdevice *gmacdev);

void synopGMAC_TS_int_enable(synopGMACdevice *gmacdev);
void synopGMAC_TS_int_disable(synopGMACdevice *gmacdev);

void synopGMAC_TS_mac_addr_filt_enable(synopGMACdevice *gmacdev);
void synopGMAC_TS_mac_addr_filt_disable(synopGMACdevice *gmacdev);
void synopGMAC_TS_set_clk_type(synopGMACdevice *gmacdev, u32 clk_type);
void synopGMAC_TS_master_enable(synopGMACdevice *gmacdev);          // Only for Ordinary clock and Boundary clock and "Advanced Time Stamp"
void synopGMAC_TS_master_disable(synopGMACdevice *gmacdev);         // Only for Ordinary clock and Boundary clock and "Advanced Time Stamp"
void synopGMAC_TS_event_enable(synopGMACdevice *gmacdev);           // Only for "Advanced Time Stamp"
void synopGMAC_TS_event_disable(synopGMACdevice *gmacdev);                   // Only for "Advanced Time Stamp"
void synopGMAC_TS_IPV4_enable(synopGMACdevice *gmacdev);                     // Only for "Advanced Time Stamp"
void synopGMAC_TS_IPV4_disable(synopGMACdevice *gmacdev);                    // Only for "Advanced Time Stamp"
void synopGMAC_TS_IPV6_enable(synopGMACdevice *gmacdev);                     // Only for "Advanced Time Stamp"
void synopGMAC_TS_IPV6_disable(synopGMACdevice *gmacdev);                    // Only for "Advanced Time Stamp"
void synopGMAC_TS_ptp_over_ethernet_enable(synopGMACdevice *gmacdev);        // Only for "Advanced Time Stamp"
void synopGMAC_TS_ptp_over_ethernet_disable(synopGMACdevice *gmacdev);       // Only for "Advanced Time Stamp"
void synopGMAC_TS_pkt_snoop_ver2(synopGMACdevice *gmacdev);                  // Only for "Advanced Time Stamp"
void synopGMAC_TS_pkt_snoop_ver1(synopGMACdevice *gmacdev);                  // Only for "Advanced Time Stamp"

void synopGMAC_TS_digital_rollover_enable(synopGMACdevice *gmacdev);
void synopGMAC_TS_binary_rollover_enable(synopGMACdevice *gmacdev);
void synopGMAC_TS_all_frames_enable(synopGMACdevice *gmacdev);               // Only for "Advanced Time Stamp"
void synopGMAC_TS_all_frames_disable(synopGMACdevice *gmacdev);              // Only for "Advanced Time Stamp"

s32 synopGMAC_TS_addend_update(synopGMACdevice *gmacdev, u32 addend_value);
s32 synopGMAC_TS_timestamp_update(synopGMACdevice *gmacdev, u32 high_value, u32 low_value);
s32 synopGMAC_TS_timestamp_init(synopGMACdevice *gmacdev, u32 high_value, u32 low_value);

void synopGMAC_TS_coarse_update(synopGMACdevice *gmacdev);          // Only if "fine correction" enabled
void synopGMAC_TS_fine_update(synopGMACdevice *gmacdev);            // Only if "fine correction" enabled

void synopGMAC_TS_subsecond_init(synopGMACdevice *gmacdev, u32 sub_sec_inc_val); // Update should happen making use of subsecond mask
void synopGMAC_TS_read_timestamp(synopGMACdevice *gmacdev, u16 * higher_sec_val,
                           u32 * sec_val, u32 *  sub_sec_val);                   // Reads the timestamp low,high and higher(Ver2) registers in the the struct pointer; readonly contents
void synopGMAC_TS_load_target_timestamp(synopGMACdevice *gmacdev, u32 sec_val, u32 sub_sec_val); //Loads the timestamp target register with the values provided

void synopGMAC_TS_load_timestamp_higher_val(synopGMACdevice *gmacdev, u32 higher_sec_val);
void synopGMAC_TS_read_timestamp_higher_val(synopGMACdevice *gmacdev, u16 * higher_sec_val);
void synopGMAC_TS_read_target_timestamp(synopGMACdevice *gmacdev, u32 * sec_val, u32 * sub_sec_val); //Read the target time stamp register contents


/**********************************************************
 * Common functions
 **********************************************************/
s32 synopGMAC_set_mdc_clk_div(synopGMACdevice *gmacdev,u32 clk_div_val );
u32 synopGMAC_get_mdc_clk_div(synopGMACdevice *gmacdev);
s32 synopGMAC_read_phy_reg(u32 RegBase,u32 PhyBase, u32 RegOffset, u16 * data);
s32 synopGMAC_write_phy_reg(u32 RegBase, u32 PhyBase, u32 RegOffset, u16 data);
s32 synopGMAC_phy_loopback(synopGMACdevice *gmacdev, bool loopback);
s32 synopGMAC_read_version (synopGMACdevice * gmacdev) ;
s32 synopGMAC_reset (synopGMACdevice * gmacdev );
s32 synopGMAC_dma_bus_mode_init(synopGMACdevice * gmacdev, u32 init_value );
s32 synopGMAC_dma_control_init(synopGMACdevice * gmacdev, u32 init_value );
void synopGMAC_wd_enable(synopGMACdevice * gmacdev);
void synopGMAC_wd_disable(synopGMACdevice * gmacdev);
void synopGMAC_jab_enable(synopGMACdevice * gmacdev);
void synopGMAC_jab_disable(synopGMACdevice * gmacdev);
void synopGMAC_frame_burst_enable(synopGMACdevice * gmacdev);
void synopGMAC_frame_burst_disable(synopGMACdevice * gmacdev);
void synopGMAC_jumbo_frame_enable(synopGMACdevice * gmacdev);
void synopGMAC_jumbo_frame_disable(synopGMACdevice * gmacdev);
void synopGMAC_select_gmii(synopGMACdevice * gmacdev);
void synopGMAC_select_mii(synopGMACdevice * gmacdev);
void synopGMAC_rx_own_enable(synopGMACdevice * gmacdev);
void synopGMAC_rx_own_disable(synopGMACdevice * gmacdev);
void synopGMAC_loopback_on(synopGMACdevice * gmacdev);
void synopGMAC_loopback_off(synopGMACdevice * gmacdev);
void synopGMAC_set_full_duplex(synopGMACdevice * gmacdev);
void synopGMAC_set_half_duplex(synopGMACdevice * gmacdev);
void synopGMAC_retry_enable(synopGMACdevice * gmacdev);
void synopGMAC_retry_disable(synopGMACdevice * gmacdev);
void synopGMAC_pad_crc_strip_enable(synopGMACdevice * gmacdev);
void synopGMAC_pad_crc_strip_disable(synopGMACdevice * gmacdev);
void synopGMAC_back_off_limit(synopGMACdevice * gmacdev, u32 value);
void synopGMAC_deferral_check_enable(synopGMACdevice * gmacdev);
void synopGMAC_deferral_check_disable(synopGMACdevice * gmacdev);
void synopGMAC_rx_enable(synopGMACdevice * gmacdev);
void synopGMAC_rx_disable(synopGMACdevice * gmacdev);
void synopGMAC_tx_enable(synopGMACdevice * gmacdev);
void synopGMAC_tx_disable(synopGMACdevice * gmacdev);
void synopGMAC_frame_filter_enable(synopGMACdevice * gmacdev);
void synopGMAC_frame_filter_disable(synopGMACdevice * gmacdev);
void synopGMAC_write_hash_table_high(synopGMACdevice * gmacdev, u32 data);
void synopGMAC_write_hash_table_low(synopGMACdevice * gmacdev, u32 data);
void synopGMAC_hash_perfect_filter_enable(synopGMACdevice * gmacdev);
void synopGMAC_Hash_filter_only_enable(synopGMACdevice * gmacdev);
void synopGMAC_src_addr_filter_enable(synopGMACdevice * gmacdev);
void synopGMAC_src_addr_filter_disable(synopGMACdevice * gmacdev);
void synopGMAC_dst_addr_filter_inverse(synopGMACdevice * gmacdev);
void synopGMAC_dst_addr_filter_normal(synopGMACdevice * gmacdev);
void synopGMAC_set_pass_control(synopGMACdevice * gmacdev,u32 passcontrol);
void synopGMAC_broadcast_enable(synopGMACdevice * gmacdev);
void synopGMAC_broadcast_disable(synopGMACdevice * gmacdev);
void synopGMAC_multicast_enable(synopGMACdevice * gmacdev);
void synopGMAC_multicast_disable(synopGMACdevice * gmacdev);
void synopGMAC_multicast_hash_filter_enable(synopGMACdevice * gmacdev);
void synopGMAC_multicast_hash_filter_disable(synopGMACdevice * gmacdev);
void synopGMAC_promisc_enable(synopGMACdevice * gmacdev);
void synopGMAC_promisc_disable(synopGMACdevice * gmacdev);
void synopGMAC_unicast_hash_filter_enable(synopGMACdevice * gmacdev);
void synopGMAC_unicast_hash_filter_disable(synopGMACdevice * gmacdev);
void synopGMAC_unicast_pause_frame_detect_enable(synopGMACdevice * gmacdev);
void synopGMAC_unicast_pause_frame_detect_disable(synopGMACdevice * gmacdev);
void synopGMAC_rx_flow_control_enable(synopGMACdevice * gmacdev);
void synopGMAC_rx_flow_control_disable(synopGMACdevice * gmacdev);
void synopGMAC_tx_flow_control_enable(synopGMACdevice * gmacdev);
void synopGMAC_tx_flow_control_disable(synopGMACdevice * gmacdev);
void synopGMAC_tx_activate_flow_control(synopGMACdevice * gmacdev);
void synopGMAC_tx_deactivate_flow_control(synopGMACdevice * gmacdev);
void synopGMAC_pause_control(synopGMACdevice *gmacdev);
s32 synopGMAC_mac_init(synopGMACdevice * gmacdev);
s32 synopGMAC_set_mac_addr(synopGMACdevice *gmacdev, u32 MacHigh, u32 MacLow, u8 *MacAddr );
s32 synopGMAC_get_mac_addr(synopGMACdevice *gmacdev, u32 MacHigh, u32 MacLow, u8 *MacAddr );
s32 synopGMAC_attach (synopGMACdevice * gmacdev, u32 macBase, u32 dmaBase, u32 phyBase,u8 *mac_addr);
void synopGMAC_rx_desc_init_ring(DmaDesc *desc, bool last_ring_desc);
void synopGMAC_tx_desc_init_ring(DmaDesc *desc, bool last_ring_desc);
void synopGMAC_rx_desc_init_chain(DmaDesc * desc);
void synopGMAC_tx_desc_init_chain(DmaDesc * desc);
s32 synopGMAC_init_tx_rx_desc_queue(synopGMACdevice *gmacdev);
void synopGMAC_init_rx_desc_base(synopGMACdevice *gmacdev);
void synopGMAC_init_tx_desc_base(synopGMACdevice *gmacdev);
void synopGMAC_set_owner_dma(DmaDesc *desc);
void synopGMAC_set_desc_sof(DmaDesc *desc);
void synopGMAC_set_desc_eof(DmaDesc *desc);
bool synopGMAC_is_sof_in_rx_desc(DmaDesc *desc);
bool synopGMAC_is_eof_in_rx_desc(DmaDesc *desc);
bool synopGMAC_is_da_filter_failed(DmaDesc *desc);
bool synopGMAC_is_sa_filter_failed(DmaDesc *desc);
bool synopGMAC_is_desc_owned_by_dma(DmaDesc *desc);
u32 synopGMAC_get_rx_desc_frame_length(u32 status);
bool synopGMAC_is_desc_valid(u32 status);
bool synopGMAC_is_desc_empty(DmaDesc *desc);
bool synopGMAC_is_rx_desc_valid(u32 status);
bool synopGMAC_is_tx_aborted(u32 status);
bool synopGMAC_is_tx_carrier_error(u32 status);
u32 synopGMAC_get_tx_collision_count(u32 status);
u32 synopGMAC_is_exc_tx_collisions(u32 status);
bool synopGMAC_is_rx_frame_damaged(u32 status);
bool synopGMAC_is_rx_frame_collision(u32 status);
bool synopGMAC_is_rx_crc(u32 status);
bool synopGMAC_is_frame_dribbling_errors(u32 status);
bool synopGMAC_is_rx_frame_length_errors(u32 status);
bool synopGMAC_is_last_rx_desc(synopGMACdevice * gmacdev,DmaDesc *desc);
bool synopGMAC_is_last_tx_desc(synopGMACdevice * gmacdev,DmaDesc *desc);
bool synopGMAC_is_rx_desc_chained(DmaDesc * desc);
bool synopGMAC_is_tx_desc_chained(DmaDesc * desc);
void synopGMAC_get_desc_data(DmaDesc * desc, u32 * Status, u32 * Buffer1, u32 * Length1, u32 * Data1, u32 * Buffer2, u32 * Length2, u32 * Data2);
#ifdef ENH_DESC_8W
s32 synopGMAC_get_tx_qptr(synopGMACdevice * gmacdev, u32 * Status, u32 * Buffer1, u32 * Length1, u32 * Data1, u32 * Buffer2, u32 * Length2, u32 * Data2,
              u32 * Ext_Status, u32 * Time_Stamp_High, u32 * Time_Stamp_low);
#else
s32 synopGMAC_get_tx_qptr(synopGMACdevice * gmacdev, u32 * Status, u32 * Buffer1, u32 * Length1, u32 * Data1, u32 * Buffer2, u32 * Length2, u32 * Data2 );
#endif
s32 synopGMAC_set_tx_qptr(synopGMACdevice * gmacdev, u32 Buffer1, u32 Length1, u32 Data1, u32 Buffer2, u32 Length2, u32 Data2,u32 offload_needed,u32 * index,DmaDesc *Dpr);
s32 synopGMAC_set_rx_qptr(synopGMACdevice * gmacdev, u32 Buffer1, u32 Length1, u32 Data1, u32 Buffer2, u32 Length2, u32 Data2);
#ifdef ENH_DESC_8W
s32 synopGMAC_get_rx_qptr(synopGMACdevice * gmacdev, u32 * Status, u32 * Buffer1, u32 * Length1, u32 * Data1, u32 * Buffer2, u32 * Length2, u32 * Data2,
                           u32 * Ext_Status, u32 * Time_Stamp_High, u32 * Time_Stamp_low);
#else
s32 synopGMAC_get_rx_qptr(synopGMACdevice * gmacdev, u32 * Status, u32 * Buffer1, u32 * Length1, u32 * Data1, u32 * Buffer2, u32 * Length2, u32 * Data2);
#endif
void synopGMAC_clear_interrupt(synopGMACdevice *gmacdev);
u32 synopGMAC_get_interrupt_type(synopGMACdevice *gmacdev);
u32 synopGMAC_get_interrupt_mask(synopGMACdevice *gmacdev);
void synopGMAC_enable_interrupt(synopGMACdevice *gmacdev, u32 interrupts);
void synopGMAC_disable_interrupt_all(synopGMACdevice *gmacdev);
void synopGMAC_disable_interrupt(synopGMACdevice *gmacdev, u32 interrupts);
void synopGMAC_enable_dma_rx(synopGMACdevice * gmacdev);
void synopGMAC_enable_dma_tx(synopGMACdevice * gmacdev);
void synopGMAC_resume_dma_tx(synopGMACdevice * gmacdev);
void synopGMAC_resume_dma_rx(synopGMACdevice * gmacdev);
void synopGMAC_take_desc_ownership(DmaDesc * desc);
void synopGMAC_take_desc_ownership_rx(synopGMACdevice * gmacdev);
void synopGMAC_take_desc_ownership_tx(synopGMACdevice * gmacdev);
void synopGMAC_disable_dma_tx(synopGMACdevice * gmacdev);
void synopGMAC_disable_dma_rx(synopGMACdevice * gmacdev);
/******Following APIs are valid only for Enhanced Descriptor from 3.50a release onwards*******/
bool synopGMAC_is_ext_status(synopGMACdevice *gmacdev,u32 status);
bool synopGMAC_ES_is_IP_header_error(synopGMACdevice *gmacdev,u32 ext_status);
bool synopGMAC_ES_is_rx_checksum_bypassed(synopGMACdevice *gmacdev,u32 ext_status);
bool synopGMAC_ES_is_IP_payload_error(synopGMACdevice *gmacdev,u32 ext_status);
/*******************PMT APIs***************************************/
void synopGMAC_pmt_int_enable(synopGMACdevice *gmacdev);
void synopGMAC_pmt_int_disable(synopGMACdevice *gmacdev);
void synopGMAC_power_down_enable(synopGMACdevice *gmacdev);
void synopGMAC_power_down_disable(synopGMACdevice *gmacdev);
void synopGMAC_enable_pmt_interrupt(synopGMACdevice *gmacdev);
void synopGMAC_disable_pmt_interrupt(synopGMACdevice *gmacdev);
void synopGMAC_magic_packet_enable(synopGMACdevice *gmacdev);
void synopGMAC_wakeup_frame_enable(synopGMACdevice *gmacdev);
void synopGMAC_pmt_unicast_enable(synopGMACdevice *gmacdev);
bool synopGMAC_is_magic_packet_received(synopGMACdevice *gmacdev);
bool synopGMAC_is_wakeup_frame_received(synopGMACdevice *gmacdev);
void synopGMAC_write_wakeup_frame_register(synopGMACdevice *gmacdev, u32 * filter_contents);
/*******************MMC APIs***************************************/
void synopGMAC_mmc_counters_stop(synopGMACdevice *gmacdev);
void synopGMAC_mmc_counters_resume(synopGMACdevice *gmacdev);
void synopGMAC_mmc_counters_set_selfclear(synopGMACdevice *gmacdev);
void synopGMAC_mmc_counters_reset_selfclear(synopGMACdevice *gmacdev);
void synopGMAC_mmc_counters_disable_rollover(synopGMACdevice *gmacdev);
void synopGMAC_mmc_counters_enable_rollover(synopGMACdevice *gmacdev);
u32 synopGMAC_read_mmc_counter(synopGMACdevice *gmacdev, u32 counter);
u32 synopGMAC_read_mmc_rx_int_status(synopGMACdevice *gmacdev);
u32 synopGMAC_read_mmc_tx_int_status(synopGMACdevice *gmacdev);
void synopGMAC_disable_mmc_tx_interrupt(synopGMACdevice *gmacdev, u32 mask);
void synopGMAC_enable_mmc_tx_interrupt(synopGMACdevice *gmacdev, u32 mask);
void synopGMAC_disable_mmc_rx_interrupt(synopGMACdevice *gmacdev, u32 mask);
void synopGMAC_enable_mmc_rx_interrupt(synopGMACdevice *gmacdev, u32 mask);
void synopGMAC_enable_mmc_ipc_rx_interrupt(synopGMACdevice *gmacdev, u32 mask);
void synopGMAC_disable_mmc_ipc_rx_interrupt(synopGMACdevice *gmacdev, u32 mask);
/*******************Ip checksum offloading APIs***************************************/
void synopGMAC_enable_rx_chksum_offload(synopGMACdevice *gmacdev);
void synopGMAC_disable_rx_Ipchecksum_offload(synopGMACdevice *gmacdev);
void synopGMAC_rx_tcpip_chksum_drop_enable(synopGMACdevice *gmacdev);
void synopGMAC_rx_tcpip_chksum_drop_disable(synopGMACdevice *gmacdev);
u32  synopGMAC_is_rx_checksum_error(synopGMACdevice *gmacdev, u32 status);
bool synopGMAC_is_tx_ipv4header_checksum_error(synopGMACdevice *gmacdev, u32 status);
bool synopGMAC_is_tx_payload_checksum_error(synopGMACdevice *gmacdev, u32 status);
void synopGMAC_tx_checksum_offload_bypass(synopGMACdevice *gmacdev, DmaDesc *desc);
void synopGMAC_tx_checksum_offload_ipv4hdr(synopGMACdevice *gmacdev, DmaDesc *desc);
void synopGMAC_tx_checksum_offload_tcponly(synopGMACdevice *gmacdev, DmaDesc *desc);
void synopGMAC_tx_checksum_offload_tcp_pseudo(synopGMACdevice *gmacdev, DmaDesc *desc);

#endif /* End of file */
