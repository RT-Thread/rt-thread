/**
 * \file IfxEth_regdef.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Eth Eth
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Eth_Bitfields Bitfields
 * \ingroup IfxLld_Eth
 * 
 * \defgroup IfxLld_Eth_union Union
 * \ingroup IfxLld_Eth
 * 
 * \defgroup IfxLld_Eth_struct Struct
 * \ingroup IfxLld_Eth
 * 
 */
#ifndef IFXETH_REGDEF_H
#define IFXETH_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Eth_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_ETH_ACCEN0_Bits
{
    unsigned int EN0:1;                     /**< \brief [0:0] Access Enable for Master TAG ID 0 (rw) */
    unsigned int EN1:1;                     /**< \brief [1:1] Access Enable for Master TAG ID 1 (rw) */
    unsigned int EN2:1;                     /**< \brief [2:2] Access Enable for Master TAG ID 2 (rw) */
    unsigned int EN3:1;                     /**< \brief [3:3] Access Enable for Master TAG ID 3 (rw) */
    unsigned int EN4:1;                     /**< \brief [4:4] Access Enable for Master TAG ID 4 (rw) */
    unsigned int EN5:1;                     /**< \brief [5:5] Access Enable for Master TAG ID 5 (rw) */
    unsigned int EN6:1;                     /**< \brief [6:6] Access Enable for Master TAG ID 6 (rw) */
    unsigned int EN7:1;                     /**< \brief [7:7] Access Enable for Master TAG ID 7 (rw) */
    unsigned int EN8:1;                     /**< \brief [8:8] Access Enable for Master TAG ID 8 (rw) */
    unsigned int EN9:1;                     /**< \brief [9:9] Access Enable for Master TAG ID 9 (rw) */
    unsigned int EN10:1;                    /**< \brief [10:10] Access Enable for Master TAG ID 10 (rw) */
    unsigned int EN11:1;                    /**< \brief [11:11] Access Enable for Master TAG ID 11 (rw) */
    unsigned int EN12:1;                    /**< \brief [12:12] Access Enable for Master TAG ID 12 (rw) */
    unsigned int EN13:1;                    /**< \brief [13:13] Access Enable for Master TAG ID 13 (rw) */
    unsigned int EN14:1;                    /**< \brief [14:14] Access Enable for Master TAG ID 14 (rw) */
    unsigned int EN15:1;                    /**< \brief [15:15] Access Enable for Master TAG ID 15 (rw) */
    unsigned int EN16:1;                    /**< \brief [16:16] Access Enable for Master TAG ID 16 (rw) */
    unsigned int EN17:1;                    /**< \brief [17:17] Access Enable for Master TAG ID 17 (rw) */
    unsigned int EN18:1;                    /**< \brief [18:18] Access Enable for Master TAG ID 18 (rw) */
    unsigned int EN19:1;                    /**< \brief [19:19] Access Enable for Master TAG ID 19 (rw) */
    unsigned int EN20:1;                    /**< \brief [20:20] Access Enable for Master TAG ID 20 (rw) */
    unsigned int EN21:1;                    /**< \brief [21:21] Access Enable for Master TAG ID 21 (rw) */
    unsigned int EN22:1;                    /**< \brief [22:22] Access Enable for Master TAG ID 22 (rw) */
    unsigned int EN23:1;                    /**< \brief [23:23] Access Enable for Master TAG ID 23 (rw) */
    unsigned int EN24:1;                    /**< \brief [24:24] Access Enable for Master TAG ID 24 (rw) */
    unsigned int EN25:1;                    /**< \brief [25:25] Access Enable for Master TAG ID 25 (rw) */
    unsigned int EN26:1;                    /**< \brief [26:26] Access Enable for Master TAG ID 26 (rw) */
    unsigned int EN27:1;                    /**< \brief [27:27] Access Enable for Master TAG ID 27 (rw) */
    unsigned int EN28:1;                    /**< \brief [28:28] Access Enable for Master TAG ID 28 (rw) */
    unsigned int EN29:1;                    /**< \brief [29:29] Access Enable for Master TAG ID 29 (rw) */
    unsigned int EN30:1;                    /**< \brief [30:30] Access Enable for Master TAG ID 30 (rw) */
    unsigned int EN31:1;                    /**< \brief [31:31] Access Enable for Master TAG ID 31 (rw) */
} Ifx_ETH_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_ETH_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_ETH_ACCEN1_Bits;

/** \brief  Register 11 - AHB or AXI Status Register */
typedef struct _Ifx_ETH_AHB_OR_AXI_STATUS_Bits
{
    unsigned int AXWHSTS:1;                 /**< \brief [0:0] AXI Master Write Channel or AHB Master Status (r) */
    unsigned int AXIRDSTS:1;                /**< \brief [1:1] AXI Master Read Channel Status (r) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_ETH_AHB_OR_AXI_STATUS_Bits;

/** \brief  Register 0 - Bus Mode Register */
typedef struct _Ifx_ETH_BUS_MODE_Bits
{
    unsigned int SWR:1;                     /**< \brief [0:0] Software Reset (rw) */
    unsigned int DA:1;                      /**< \brief [1:1] DMA Arbitration Scheme (rw) */
    unsigned int DSL:5;                     /**< \brief [6:2] Descriptor Skip Length (rw) */
    unsigned int ATDS:1;                    /**< \brief [7:7] Alternate Descriptor Size (rw) */
    unsigned int PBL:6;                     /**< \brief [13:8] Programmable Burst Length (rw) */
    unsigned int PR:2;                      /**< \brief [15:14] Priority Ratio (rw) */
    unsigned int FB:1;                      /**< \brief [16:16] Fixed Burst (rw) */
    unsigned int RPBL:6;                    /**< \brief [22:17] Rx DMA PBL (rw) */
    unsigned int USP:1;                     /**< \brief [23:23] Use Seperate PBL (rw) */
    unsigned int PBLx8:1;                   /**< \brief [24:24] PBLx8 Mode (rw) */
    unsigned int AAL:1;                     /**< \brief [25:25] Address Aligned Beats (rw) */
    unsigned int MB:1;                      /**< \brief [26:26] Mixed Burst (rw) */
    unsigned int TXPR:1;                    /**< \brief [27:27] Transmit Priority (rw) */
    unsigned int PRWG:2;                    /**< \brief [29:28] Channel Priority Weights (r) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ETH_BUS_MODE_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_ETH_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_ETH_CLC_Bits;

/** \brief  Register 21 - Current Host Receive Buffer Address Register */
typedef struct _Ifx_ETH_CURRENT_HOST_RECEIVE_BUFFER_ADDRESS_Bits
{
    unsigned int CURRBUFAPTR:32;            /**< \brief [31:0] Host Receive Buffer Address Pointer (r) */
} Ifx_ETH_CURRENT_HOST_RECEIVE_BUFFER_ADDRESS_Bits;

/** \brief  Register 19 - Current Host Receive Descriptor Register */
typedef struct _Ifx_ETH_CURRENT_HOST_RECEIVE_DESCRIPTOR_Bits
{
    unsigned int CURRDESAPTR:32;            /**< \brief [31:0] Host Receive Descriptor Address Pointer (r) */
} Ifx_ETH_CURRENT_HOST_RECEIVE_DESCRIPTOR_Bits;

/** \brief  Register 20 - Current Host Transmit Buffer Address Register */
typedef struct _Ifx_ETH_CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS_Bits
{
    unsigned int CURTBUFAPTR:32;            /**< \brief [31:0] Host Transmit Buffer Address Pointer (r) */
} Ifx_ETH_CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS_Bits;

/** \brief  Register 18 - Current Host Transmit Descriptor Register */
typedef struct _Ifx_ETH_CURRENT_HOST_TRANSMIT_DESCRIPTOR_Bits
{
    unsigned int CURTDESAPTR:32;            /**< \brief [31:0] Host Transmit Descriptor Address Pointer (r) */
} Ifx_ETH_CURRENT_HOST_TRANSMIT_DESCRIPTOR_Bits;

/** \brief  Register 9 - Debug Register */
typedef struct _Ifx_ETH_DEBUG_Bits
{
    unsigned int RPESTS:1;                  /**< \brief [0:0] MAC GMII or MII Receive Protocol Engine Status (r) */
    unsigned int RFCFCSTS:2;                /**< \brief [2:1] MAC Receive Frame Controller FIFO Status (r) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int RWCSTS:1;                  /**< \brief [4:4] MTL Rx FIFO Write Controller Active Status (r) */
    unsigned int RRCSTS:2;                  /**< \brief [6:5] MTL Rx FIFO Read Controller State (r) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int RXFSTS:2;                  /**< \brief [9:8] MTL Rx FIFO Fill-level Status (r) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int TPESTS:1;                  /**< \brief [16:16] MAC GMII or MII Transmit Protocol Engine Status (r) */
    unsigned int TFCSTS:2;                  /**< \brief [18:17] MAC Transmit Frame Controller Status (r) */
    unsigned int TXPAUSED:1;                /**< \brief [19:19] MAC transmitter in PAUSE (r) */
    unsigned int TRCSTS:2;                  /**< \brief [21:20] MTL Tx FIFO Read Controller Status (r) */
    unsigned int TWCSTS:1;                  /**< \brief [22:22] MTL Tx FIFO Write Controller Active Status (r) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int TXFSTS:1;                  /**< \brief [24:24] MTL Tx FIFO Not Empty Status (r) */
    unsigned int TXSTSFSTS:1;               /**< \brief [25:25] MTL TxStatus FIFO Full Status (r) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ETH_DEBUG_Bits;

/** \brief  Register 6 - Flow Control Register */
typedef struct _Ifx_ETH_FLOW_CONTROL_Bits
{
    unsigned int FCA_BPA:1;                 /**< \brief [0:0] Flow Control Busy or Backpressure Activate (rw) */
    unsigned int TFE:1;                     /**< \brief [1:1] Transmit Flow Control Enable (rw) */
    unsigned int RFE:1;                     /**< \brief [2:2] Receive Flow Control Enable (rw) */
    unsigned int UP:1;                      /**< \brief [3:3] Unicast Pause Frame Detect (rw) */
    unsigned int PLT:2;                     /**< \brief [5:4] Pause Low Threshold (rw) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int DZPQ:1;                    /**< \brief [7:7] Disable Zero-Quanta Pause (rw) */
    unsigned int reserved_8:8;              /**< \brief \internal Reserved */
    unsigned int PT:16;                     /**< \brief [31:16] Pause Time (rw) */
} Ifx_ETH_FLOW_CONTROL_Bits;

/** \brief  Register 4 - GMII Address Register */
typedef struct _Ifx_ETH_GMII_ADDRESS_Bits
{
    unsigned int GB:1;                      /**< \brief [0:0] GMII Busy (rw) */
    unsigned int GW:1;                      /**< \brief [1:1] GMII Write (rw) */
    unsigned int CR:4;                      /**< \brief [5:2] CSR Clock Range (rw) */
    unsigned int GR:5;                      /**< \brief [10:6] GMII Register (rw) */
    unsigned int PA:5;                      /**< \brief [15:11] Physical Layer Address (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ETH_GMII_ADDRESS_Bits;

/** \brief  Register 5 - GMII Data Register */
typedef struct _Ifx_ETH_GMII_DATA_Bits
{
    unsigned int GD:16;                     /**< \brief [15:0] GMII Data (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ETH_GMII_DATA_Bits;

/** \brief  Input and Output Control Register */
typedef struct _Ifx_ETH_GPCTL_Bits
{
    unsigned int ALTI0:2;                   /**< \brief [1:0] Alternate Input Select (rw) */
    unsigned int ALTI1:2;                   /**< \brief [3:2] Alternate Input Select (rw) */
    unsigned int ALTI2:2;                   /**< \brief [5:4] Alternate Input Select (rw) */
    unsigned int ALTI3:2;                   /**< \brief [7:6] Alternate Input Select (rw) */
    unsigned int ALTI4:2;                   /**< \brief [9:8] Alternate Input Select (rw) */
    unsigned int ALTI5:2;                   /**< \brief [11:10] Alternate Input Select (rw) */
    unsigned int ALTI6:2;                   /**< \brief [13:12] Alternate Input Select (rw) */
    unsigned int ALTI7:2;                   /**< \brief [15:14] Alternate Input Select (rw) */
    unsigned int ALTI8:2;                   /**< \brief [17:16] Alternate Input Select (rw) */
    unsigned int ALTI9:2;                   /**< \brief [19:18] Alternate Input Select (rw) */
    unsigned int ALTI10:2;                  /**< \brief [21:20] Alternate Input Select (rw) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int EPR:1;                     /**< \brief [24:24] External Phy Interface RMMI Mode Bit (rw) */
    unsigned int DIV:1;                     /**< \brief [25:25] Module Clock Divider Request Bit (rw) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ETH_GPCTL_Bits;

/** \brief  Register 2 - Hash Table High Register */
typedef struct _Ifx_ETH_HASH_TABLE_HIGH_Bits
{
    unsigned int HTH:32;                    /**< \brief [31:0] Hash Table High (rw) */
} Ifx_ETH_HASH_TABLE_HIGH_Bits;

/** \brief  Register 3 - Hash Table Low Register */
typedef struct _Ifx_ETH_HASH_TABLE_LOW_Bits
{
    unsigned int HTL:32;                    /**< \brief [31:0] Hash Table Low (rw) */
} Ifx_ETH_HASH_TABLE_LOW_Bits;

/** \brief  Register 22 - HW Feature Register */
typedef struct _Ifx_ETH_HW_FEATURE_Bits
{
    unsigned int MIISEL:1;                  /**< \brief [0:0] MIISEL (r) */
    unsigned int GMIISEL:1;                 /**< \brief [1:1] GMIISEL (r) */
    unsigned int HDSEL:1;                   /**< \brief [2:2] HDSEL (r) */
    unsigned int EXTHASHEN:1;               /**< \brief [3:3] EXTHASHEN (r) */
    unsigned int HASHSEL:1;                 /**< \brief [4:4] HASHSEL (r) */
    unsigned int ADDMACADRSEL:1;            /**< \brief [5:5] ADDMACADRSEL (r) */
    unsigned int PCSSEL:1;                  /**< \brief [6:6] PCSSEL (r) */
    unsigned int L3L4FLTREN:1;              /**< \brief [7:7] L3L4FLTREN (r) */
    unsigned int SMASEL:1;                  /**< \brief [8:8] SMASEL (r) */
    unsigned int RWKSEL:1;                  /**< \brief [9:9] RWKSEL (r) */
    unsigned int MGKSEL:1;                  /**< \brief [10:10] MGKSEL (r) */
    unsigned int MMCSEL:1;                  /**< \brief [11:11] MMCSEL (r) */
    unsigned int TSVER1SEL:1;               /**< \brief [12:12] TSVER1SEL (r) */
    unsigned int TSVER2SEL:1;               /**< \brief [13:13] TSVER2SEL (r) */
    unsigned int EEESEL:1;                  /**< \brief [14:14] EEESEL (r) */
    unsigned int AVSEL:1;                   /**< \brief [15:15] AVSEL (r) */
    unsigned int TXCOESEL:1;                /**< \brief [16:16] TXCOESEL (r) */
    unsigned int RXTYP1COE:1;               /**< \brief [17:17] RXTYP1COE (r) */
    unsigned int RXTYP2COE:1;               /**< \brief [18:18] RXTYP2COE (r) */
    unsigned int RXFIFOSIZE:1;              /**< \brief [19:19] RXFIFOSIZE (rw) */
    unsigned int RXCHCNT:2;                 /**< \brief [21:20] RXCHCNT (r) */
    unsigned int TXCHCNT:2;                 /**< \brief [23:22] TXCHCNT (r) */
    unsigned int ENHDESSEL:1;               /**< \brief [24:24] ENHDESSEL (r) */
    unsigned int INTTSEN:1;                 /**< \brief [25:25] INTTSEN (r) */
    unsigned int FLEXIPPSEN:1;              /**< \brief [26:26] FLEXIPPSEN (r) */
    unsigned int SAVLANINS:1;               /**< \brief [27:27] SAVLANINS (r) */
    unsigned int ACTPHYIF:3;                /**< \brief [30:28] Active or Selected PHY interface (r) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ETH_HW_FEATURE_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_ETH_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_ETH_ID_Bits;

/** \brief  Register 7 - Interrupt Enable Register */
typedef struct _Ifx_ETH_INTERRUPT_ENABLE_Bits
{
    unsigned int TIE:1;                     /**< \brief [0:0] Transmit Interrupt Enable (rw) */
    unsigned int TSE:1;                     /**< \brief [1:1] Transmit Stopped Enable (rw) */
    unsigned int TUE:1;                     /**< \brief [2:2] Transmit Buffer Unvailable Enable (rw) */
    unsigned int TJE:1;                     /**< \brief [3:3] Transmit Jabber Timeout Enable (rw) */
    unsigned int OVE:1;                     /**< \brief [4:4] Overflow Interrupt Enable (rw) */
    unsigned int UNE:1;                     /**< \brief [5:5] Underflow Interrupt Enable (rw) */
    unsigned int RIE:1;                     /**< \brief [6:6] Receive Interrupt Enable (rw) */
    unsigned int RUE:1;                     /**< \brief [7:7] Receive Buffer Unavailable Enable (rw) */
    unsigned int RSE:1;                     /**< \brief [8:8] Receive Stopped Enable (rw) */
    unsigned int RWE:1;                     /**< \brief [9:9] Receive Watchdog Timeout Enable (rw) */
    unsigned int ETE:1;                     /**< \brief [10:10] Early Transmit Interrupt Enable (rw) */
    unsigned int reserved_11:2;             /**< \brief \internal Reserved */
    unsigned int FBE:1;                     /**< \brief [13:13] Fatal Bus Error Enable (rw) */
    unsigned int ERE:1;                     /**< \brief [14:14] Early Receive Interrupt Enable (rw) */
    unsigned int AIE:1;                     /**< \brief [15:15] Abnormal Interrupt Summary Enable (rw) */
    unsigned int NIE:1;                     /**< \brief [16:16] Normal Interrupt Summary Enable (rw) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_ETH_INTERRUPT_ENABLE_Bits;

/** \brief  Register 15 - Interrupt Mask Register */
typedef struct _Ifx_ETH_INTERRUPT_MASK_Bits
{
    unsigned int RGSMIIIM:1;                /**< \brief [0:0] RGMII or SMII Interrupt Mask (r) */
    unsigned int PCSLCHGIM:1;               /**< \brief [1:1] PCS Link Status Interrupt Mask (r) */
    unsigned int PCSANCIM:1;                /**< \brief [2:2] PCS AN Completion Interrupt Mask (r) */
    unsigned int PMTIM:1;                   /**< \brief [3:3] PMT Interrupt Mask (rw) */
    unsigned int reserved_4:5;              /**< \brief \internal Reserved */
    unsigned int TSIM:1;                    /**< \brief [9:9] Timestamp Interrupt Mask (rw) */
    unsigned int LPIIM:1;                   /**< \brief [10:10] LPI Interrupt Mask (r) */
    unsigned int reserved_11:21;            /**< \brief \internal Reserved */
} Ifx_ETH_INTERRUPT_MASK_Bits;

/** \brief  Register 14 - Interrupt Register */
typedef struct _Ifx_ETH_INTERRUPT_STATUS_Bits
{
    unsigned int RGSMIIIS:1;                /**< \brief [0:0] RGMII or SMII Interrupt Status (r) */
    unsigned int PCSLCHGIS:1;               /**< \brief [1:1] PCS Link Status Changed (r) */
    unsigned int PCSANCIS:1;                /**< \brief [2:2] PCS Auto-Negotiation Complete (r) */
    unsigned int PMTIS:1;                   /**< \brief [3:3] PMT Interrupt Status (r) */
    unsigned int MMCIS:1;                   /**< \brief [4:4] MMC Interrupt Status (r) */
    unsigned int MMCRXIS:1;                 /**< \brief [5:5] MMC Receive Interrupt Status (r) */
    unsigned int MMCTXIS:1;                 /**< \brief [6:6] MMC Transmit Interrupt Status (r) */
    unsigned int MMCRXIPIS:1;               /**< \brief [7:7] MMC Receive Checksum Offload Interrupt Status (r) */
    unsigned int reserved_8:1;              /**< \brief \internal Reserved */
    unsigned int TSIS:1;                    /**< \brief [9:9] Timestamp Interrupt Status (r) */
    unsigned int LPIIS:1;                   /**< \brief [10:10] LPI Interrupt Status (r) */
    unsigned int reserved_11:21;            /**< \brief \internal Reserved */
} Ifx_ETH_INTERRUPT_STATUS_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_ETH_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_ETH_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_ETH_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_ETH_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_ETH_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_ETH_KRSTCLR_Bits;

/** \brief  MAC Address High Register */
typedef struct _Ifx_ETH_MAC_ADDRESS_HIGH_Bits
{
    unsigned int ADDRHI:16;                 /**< \brief [15:0]  (rw) */
    unsigned int reserved_16:8;             /**< \brief \internal Reserved */
    unsigned int MBC:6;                     /**< \brief [29:24]  (rw) */
    unsigned int SA:1;                      /**< \brief [30:30]  (rw) */
    unsigned int AE:1;                      /**< \brief [31:31]  (rw) */
} Ifx_ETH_MAC_ADDRESS_HIGH_Bits;

/** \brief  MAC Address Low Register */
typedef struct _Ifx_ETH_MAC_ADDRESS_LOW_Bits
{
    unsigned int ADDRLO:32;                 /**< \brief [31:0]  (rw) */
} Ifx_ETH_MAC_ADDRESS_LOW_Bits;

/** \brief  Register 0 - MAC Configuration Register */
typedef struct _Ifx_ETH_MAC_CONFIGURATION_Bits
{
    unsigned int PRELEN:2;                  /**< \brief [1:0] Preamble Length for Transmit Frames (rw) */
    unsigned int RE:1;                      /**< \brief [2:2] Receiver Enable (rw) */
    unsigned int TE:1;                      /**< \brief [3:3] Transmitter Enable (rw) */
    unsigned int DC:1;                      /**< \brief [4:4] Deferral Check (rw) */
    unsigned int BL:2;                      /**< \brief [6:5] Back-Off Limit (rw) */
    unsigned int ACS:1;                     /**< \brief [7:7] Automatic Pad or CRC Stripping (rw) */
    unsigned int LUD:1;                     /**< \brief [8:8] Link Up or Down (r) */
    unsigned int DR:1;                      /**< \brief [9:9] Disable Retry (rw) */
    unsigned int IPC:1;                     /**< \brief [10:10] Checksum Offload (rw) */
    unsigned int DM:1;                      /**< \brief [11:11] Duplex Mode (rw) */
    unsigned int LM:1;                      /**< \brief [12:12] Loopback Mode (rw) */
    unsigned int DO:1;                      /**< \brief [13:13] Disable Receive Own (rw) */
    unsigned int FES:1;                     /**< \brief [14:14] Speed (rw) */
    unsigned int PS:1;                      /**< \brief [15:15] Port Select (r) */
    unsigned int DCRS:1;                    /**< \brief [16:16] Disable Carrier Sense During Transmission (rw) */
    unsigned int IFG:3;                     /**< \brief [19:17] Inter-Frame Gap (rw) */
    unsigned int JE:1;                      /**< \brief [20:20] Jumbo Frame Enable (rw) */
    unsigned int BE:1;                      /**< \brief [21:21] Frame Burst Enable (r) */
    unsigned int JD:1;                      /**< \brief [22:22] Jabber Disable (rw) */
    unsigned int WD:1;                      /**< \brief [23:23] Watchdog Disable (rw) */
    unsigned int TC:1;                      /**< \brief [24:24] Transmit Configuration in RGMII, SGMII, or SMII (r) */
    unsigned int CST:1;                     /**< \brief [25:25] CRC Stripping of Type Frames (rw) */
    unsigned int SFTERR:1;                  /**< \brief [26:26] SMII Force Transmit Error (r) */
    unsigned int TWOKPE:1;                  /**< \brief [27:27] IEEE 802.3as support for 2K packets Enable (rw) */
    unsigned int SARC:3;                    /**< \brief [30:28] Source Address Insertion or Replacement Control (r) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ETH_MAC_CONFIGURATION_Bits;

/** \brief  Register 1 - MAC Frame Filter */
typedef struct _Ifx_ETH_MAC_FRAME_FILTER_Bits
{
    unsigned int PR:1;                      /**< \brief [0:0] Promiscuous Mode (rw) */
    unsigned int HUC:1;                     /**< \brief [1:1] Hash Unicast (rw) */
    unsigned int HMC:1;                     /**< \brief [2:2] Hash Multicast (rw) */
    unsigned int DAIF:1;                    /**< \brief [3:3] DA Inverse Filtering (rw) */
    unsigned int PM:1;                      /**< \brief [4:4] Pass All Multicast (rw) */
    unsigned int DBF:1;                     /**< \brief [5:5] Disable Broadcast Frames (rw) */
    unsigned int PCF:2;                     /**< \brief [7:6] Pass Control Frames (rw) */
    unsigned int SAIF:1;                    /**< \brief [8:8] SA Inverse Filtering (rw) */
    unsigned int SAF:1;                     /**< \brief [9:9] Source Address Filter Enable (rw) */
    unsigned int HPF:1;                     /**< \brief [10:10] Hash or Perfect Filter (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int VTFE:1;                    /**< \brief [16:16] VLAN Tag Filter Enable (rw) */
    unsigned int reserved_17:3;             /**< \brief \internal Reserved */
    unsigned int IPFE:1;                    /**< \brief [20:20] Layer 3 and Layer 4 Filter Enable (r) */
    unsigned int DNTU:1;                    /**< \brief [21:21] Drop non-TCP/UDP over IP Frames (r) */
    unsigned int reserved_22:9;             /**< \brief \internal Reserved */
    unsigned int RA:1;                      /**< \brief [31:31] Receive All (rw) */
} Ifx_ETH_MAC_FRAME_FILTER_Bits;

/** \brief  Register 8 - Missed Frame and Buffer Overflow Counter Register */
typedef struct _Ifx_ETH_MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER_Bits
{
    unsigned int MISFRMCNT:16;              /**< \brief [15:0] MISFRMCNT (r) */
    unsigned int MISCNTOVF:1;               /**< \brief [16:16] MISCNTOVF (r) */
    unsigned int OVFFRMCNT:11;              /**< \brief [27:17] OVFFRMCNT (r) */
    unsigned int OVFCNTOVF:1;               /**< \brief [28:28] OVFCNTOVF (r) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_ETH_MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER_Bits;

/** \brief  Register 64 - MMC Control Register */
typedef struct _Ifx_ETH_MMC_CONTROL_Bits
{
    unsigned int CNTRST:1;                  /**< \brief [0:0] Counters Reset (rw) */
    unsigned int CNTSTOPRO:1;               /**< \brief [1:1] Counters Stop Rollover (rw) */
    unsigned int RSTONRD:1;                 /**< \brief [2:2] Reset on Read (rw) */
    unsigned int CNTFREEZ:1;                /**< \brief [3:3] MMC Counter Freeze (rw) */
    unsigned int CNTPRST:1;                 /**< \brief [4:4] Counters Preset (rw) */
    unsigned int CNTPRSTLVL:1;              /**< \brief [5:5] Full-Half Preset (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int UCDBC:1;                   /**< \brief [8:8] Update MMC Counters for Dropped Broadcast Frames (rw) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_ETH_MMC_CONTROL_Bits;

/** \brief  Register 130 - MMC Receive Checksum Offload Interrupt Register */
typedef struct _Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_Bits
{
    unsigned int RXIPV4GFIS:1;              /**< \brief [0:0] MMC Receive IPV4 Good Frame Counter Interrupt Status (r) */
    unsigned int RXIPV4HERFIS:1;            /**< \brief [1:1] MMC Receive IPV4 Header Error Frame Counter Interrupt Status (r) */
    unsigned int RXIPV4NOPAYFIS:1;          /**< \brief [2:2] MMC Receive IPV4 No Payload Frame Counter Interrupt Status (r) */
    unsigned int RXIPV4FRAGFIS:1;           /**< \brief [3:3] MMC Receive IPV4 Fragmented Frame Counter Interrupt Status (r) */
    unsigned int RXIPV4UDSBLFIS:1;          /**< \brief [4:4] MMC Receive IPV4 UDP Checksum Disabled Frame Counter Interrupt Status (r) */
    unsigned int RXIPV6GFIS:1;              /**< \brief [5:5] MMC Receive IPV6 Good Frame Counter Interrupt Status (r) */
    unsigned int RXIPV6HERFIS:1;            /**< \brief [6:6] MMC Receive IPV6 Header Error Frame Counter Interrupt Status (r) */
    unsigned int RXIPV6NOPAYFIS:1;          /**< \brief [7:7] MMC Receive IPV6 No Payload Frame Counter Interrupt Status (r) */
    unsigned int RXUDPGFIS:1;               /**< \brief [8:8] MMC Receive UDP Good Frame Counter Interrupt Status (r) */
    unsigned int RXUDPERFIS:1;              /**< \brief [9:9] MMC Receive UDP Error Frame Counter Interrupt Status (r) */
    unsigned int RXTCPGFIS:1;               /**< \brief [10:10] MMC Receive TCP Good Frame Counter Interrupt Status (r) */
    unsigned int RXTCPERFIS:1;              /**< \brief [11:11] MMC Receive TCP Error Frame Counter Interrupt Status (r) */
    unsigned int RXICMPGFIS:1;              /**< \brief [12:12] MMC Receive ICMP Good Frame Counter Interrupt Status (r) */
    unsigned int RXICMPERFIS:1;             /**< \brief [13:13] MMC Receive ICMP Error Frame Counter Interrupt Status (r) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int RXIPV4GOIS:1;              /**< \brief [16:16] MMC Receive IPV4 Good Octet Counter Interrupt Status (r) */
    unsigned int RXIPV4HEROIS:1;            /**< \brief [17:17] MMC Receive IPV4 Header Error Octet Counter Interrupt Status (r) */
    unsigned int RXIPV4NOPAYOIS:1;          /**< \brief [18:18] MMC Receive IPV4 No Payload Octet Counter Interrupt Status (r) */
    unsigned int RXIPV4FRAGOIS:1;           /**< \brief [19:19] MMC Receive IPV4 Fragmented Octet Counter Interrupt Status (r) */
    unsigned int RXIPV4UDSBLOIS:1;          /**< \brief [20:20] MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Status (r) */
    unsigned int RXIPV6GOIS:1;              /**< \brief [21:21] MMC Receive IPV6 Good Octet Counter Interrupt Status (r) */
    unsigned int RXIPV6HEROIS:1;            /**< \brief [22:22] MMC Receive IPV6 Header Error Octet Counter Interrupt Status (r) */
    unsigned int RXIPV6NOPAYOIS:1;          /**< \brief [23:23] MMC Receive IPV6 No Payload Octet Counter Interrupt Status (r) */
    unsigned int RXUDPGOIS:1;               /**< \brief [24:24] MMC Receive UDP Good Octet Counter Interrupt Status (r) */
    unsigned int RXUDPEROIS:1;              /**< \brief [25:25] MMC Receive UDP Error Octet Counter Interrupt Status (r) */
    unsigned int RXTCPGOIS:1;               /**< \brief [26:26] MMC Receive TCP Good Octet Counter Interrupt Status (r) */
    unsigned int RXTCPEROIS:1;              /**< \brief [27:27] MMC Receive TCP Error Octet Counter Interrupt Status (r) */
    unsigned int RXICMPGOIS:1;              /**< \brief [28:28] MMC Receive ICMP Good Octet Counter Interrupt Status (r) */
    unsigned int RXICMPEROIS:1;             /**< \brief [29:29] MMC Receive ICMP Error Octet Counter Interrupt Status (r) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_Bits;

/** \brief  Register 128 - MMC Receive Checksum Offload Interrupt Mask Register */
typedef struct _Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_MASK_Bits
{
    unsigned int RXIPV4GFIM:1;              /**< \brief [0:0] MMC Receive IPV4 Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXIPV4HERFIM:1;            /**< \brief [1:1] MMC Receive IPV4 Header Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXIPV4NOPAYFIM:1;          /**< \brief [2:2] MMC Receive IPV4 No Payload Frame Counter Interrupt Mask (rw) */
    unsigned int RXIPV4FRAGFIM:1;           /**< \brief [3:3] MMC Receive IPV4 Fragmented Frame Counter Interrupt Mask (rw) */
    unsigned int RXIPV4UDSBLFIM:1;          /**< \brief [4:4] MMC Receive IPV4 UDP Checksum Disabled Frame Counter Interrupt Mask (rw) */
    unsigned int RXIPV6GFIM:1;              /**< \brief [5:5] MMC Receive IPV6 Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXIPV6HERFIM:1;            /**< \brief [6:6] MMC Receive IPV6 Header Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXIPV6NOPAYFIM:1;          /**< \brief [7:7] MMC Receive IPV6 No Payload Frame Counter Interrupt Mask (rw) */
    unsigned int RXUDPGFIM:1;               /**< \brief [8:8] MMC Receive UDP Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXUDPERFIM:1;              /**< \brief [9:9] MMC Receive UDP Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXTCPGFIM:1;               /**< \brief [10:10] MMC Receive TCP Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXTCPERFIM:1;              /**< \brief [11:11] MMC Receive TCP Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXICMPGFIM:1;              /**< \brief [12:12] MMC Receive ICMP Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXICMPERFIM:1;             /**< \brief [13:13] MMC Receive ICMP Error Frame Counter Interrupt Mask (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int RXIPV4GOIM:1;              /**< \brief [16:16] MMC Receive IPV4 Good Octet Counter Interrupt Mask (rw) */
    unsigned int RXIPV4HEROIM:1;            /**< \brief [17:17] MMC Receive IPV4 Header Error Octet Counter Interrupt Mask (rw) */
    unsigned int RXIPV4NOPAYOIM:1;          /**< \brief [18:18] MMC Receive IPV4 No Payload Octet Counter Interrupt Mask (rw) */
    unsigned int RXIPV4FRAGOIM:1;           /**< \brief [19:19] MMC Receive IPV4 Fragmented Octet Counter Interrupt Mask (rw) */
    unsigned int RXIPV4UDSBLOIM:1;          /**< \brief [20:20] MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Mask (rw) */
    unsigned int RXIPV6GOIM:1;              /**< \brief [21:21] MMC Receive IPV6 Good Octet Counter Interrupt Mask (rw) */
    unsigned int RXIPV6HEROIM:1;            /**< \brief [22:22] MMC Receive IPV6 Header Error Octet Counter Interrupt Mask (rw) */
    unsigned int RXIPV6NOPAYOIM:1;          /**< \brief [23:23] MMC Receive IPV6 No Payload Octet Counter Interrupt Mask (rw) */
    unsigned int RXUDPGOIM:1;               /**< \brief [24:24] MMC Receive UDP Good Octet Counter Interrupt Mask (rw) */
    unsigned int RXUDPEROIM:1;              /**< \brief [25:25] MMC Receive UDP Error Octet Counter Interrupt Mask (rw) */
    unsigned int RXTCPGOIM:1;               /**< \brief [26:26] MMC Receive TCP Good Octet Counter Interrupt Mask (rw) */
    unsigned int RXTCPEROIM:1;              /**< \brief [27:27] MMC Receive TCP Error Octet Counter Interrupt Mask (rw) */
    unsigned int RXICMPGOIM:1;              /**< \brief [28:28] MMC Receive ICMP Good Octet Counter Interrupt Mask (rw) */
    unsigned int RXICMPEROIM:1;             /**< \brief [29:29] MMC Receive ICMP Error Octet Counter Interrupt Mask (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_MASK_Bits;

/** \brief  Register 65 - MMC Receive Interrupt Register */
typedef struct _Ifx_ETH_MMC_RECEIVE_INTERRUPT_Bits
{
    unsigned int RXGBFRMIS:1;               /**< \brief [0:0] MMC Receive Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RXGBOCTIS:1;               /**< \brief [1:1] MMC Receive Good Bad Octet Counter Interrupt Status (r) */
    unsigned int RXGOCTIS:1;                /**< \brief [2:2] MMC Receive Good Octet Counter Interrupt Status. (r) */
    unsigned int RXBCGFIS:1;                /**< \brief [3:3] MMC Receive Broadcast Good Frame Counter Interrupt Status. (r) */
    unsigned int RXMCGFIS:1;                /**< \brief [4:4] MMC Receive Multicast Good Frame Counter Interrupt Status (r) */
    unsigned int RXCRCERFIS:1;              /**< \brief [5:5] MMC Receive CRC Error Frame Counter Interrupt Status (r) */
    unsigned int RXALGNERFIS:1;             /**< \brief [6:6] MMC Receive Alignment Error Frame Counter Interrupt Status (r) */
    unsigned int RXRUNTFIS:1;               /**< \brief [7:7] MMC Receive Runt Frame Counter Interrupt Status (r) */
    unsigned int RXJABERFIS:1;              /**< \brief [8:8] MMC Receive Jabber Error Frame Counter Interrupt Status (r) */
    unsigned int RXUSIZEGFIS:1;             /**< \brief [9:9] MMC Receive Undersize Good Frame Counter Interrupt Status (r) */
    unsigned int RXOSIZEGFIS:1;             /**< \brief [10:10] MMC Receive Oversize Good Frame Counter Interrupt Status (r) */
    unsigned int RX64OCTGBFIS:1;            /**< \brief [11:11] MMC Receive 64 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RX65T127OCTGBFIS:1;        /**< \brief [12:12] MMC Receive 65 to 127 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RX128T255OCTGBFIS:1;       /**< \brief [13:13] MMC Receive 128 to 255 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RX256T511OCTGBFIS:1;       /**< \brief [14:14] MMC Receive 256 to 511 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RX512T1023OCTGBFIS:1;      /**< \brief [15:15] MMC Receive 512 to 1023 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RX1024TMAXOCTGBFIS:1;      /**< \brief [16:16] MMC Receive 1024 to Maximum Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RXUCGFIS:1;                /**< \brief [17:17] MMC Receive Unicast Good Frame Counter Interrupt Status (r) */
    unsigned int RXLENERFIS:1;              /**< \brief [18:18] MMC Receive Length Error Frame Counter Interrupt Status (r) */
    unsigned int RXORANGEFIS:1;             /**< \brief [19:19] MMC Receive Out Of Range Error Frame Counter Interrupt Status (r) */
    unsigned int RXPAUSFIS:1;               /**< \brief [20:20] MMC Receive Pause Frame Counter Interrupt Status (r) */
    unsigned int RXFOVFIS:1;                /**< \brief [21:21] MMC Receive FIFO Overflow Frame Counter Interrupt Status (r) */
    unsigned int RXVLANGBFIS:1;             /**< \brief [22:22] MMC Receive VLAN Good Bad Frame Counter Interrupt Status (r) */
    unsigned int RXWDOGFIS:1;               /**< \brief [23:23] MMC Receive Watchdog Error Frame Counter Interrupt Status (r) */
    unsigned int RXRCVERRFIS:1;             /**< \brief [24:24] MMC Receive Error Frame Counter Interrupt Status (r) */
    unsigned int RXCTRLFIS:1;               /**< \brief [25:25] MMC Receive Control Frame Counter Interrupt Status (r) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ETH_MMC_RECEIVE_INTERRUPT_Bits;

/** \brief  - */
typedef struct _Ifx_ETH_MMC_RECEIVE_INTERRUPT_MASK_Bits
{
    unsigned int RXGBFRMIM:1;               /**< \brief [0:0] MMC Receive Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RXGBOCTIM:1;               /**< \brief [1:1] MMC Receive Good Bad Octet Counter Interrupt Mask (rw) */
    unsigned int RXGOCTIM:1;                /**< \brief [2:2] MMC Receive Good Octet Counter Interrupt Mask (rw) */
    unsigned int RXBCGFIM:1;                /**< \brief [3:3] MMC Receive Broadcast Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXMCGFIM:1;                /**< \brief [4:4] MMC Receive Multicast Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXCRCERFIM:1;              /**< \brief [5:5] MMC Receive CRC Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXALGNERFIM:1;             /**< \brief [6:6] MMC Receive Alignment Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXRUNTFIM:1;               /**< \brief [7:7] MMC Receive Runt Frame Counter Interrupt Mask (rw) */
    unsigned int RXJABERFIM:1;              /**< \brief [8:8] MMC Receive Jabber Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXUSIZEGFIM:1;             /**< \brief [9:9] MMC Receive Undersize Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXOSIZEGFIM:1;             /**< \brief [10:10] MMC Receive Oversize Good Frame Counter Interrupt Mask (rw) */
    unsigned int RX64OCTGBFIM:1;            /**< \brief [11:11] MMC Receive 64 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RX65T127OCTGBFIM:1;        /**< \brief [12:12] MMC Receive 65 to 127 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RX128T255OCTGBFIM:1;       /**< \brief [13:13] MMC Receive 128 to 255 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RX256T511OCTGBFIM:1;       /**< \brief [14:14] MMC Receive 256 to 511 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RX512T1023OCTGBFIM:1;      /**< \brief [15:15] MMC Receive 512 to 1023 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RX1024TMAXOCTGBFIM:1;      /**< \brief [16:16] MMC Receive 1024 to Maximum Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RXUCGFIM:1;                /**< \brief [17:17] MMC Receive Unicast Good Frame Counter Interrupt Mask (rw) */
    unsigned int RXLENERFIM:1;              /**< \brief [18:18] MMC Receive Length Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXORANGEFIM:1;             /**< \brief [19:19] MMC Receive Out Of Range Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXPAUSFIM:1;               /**< \brief [20:20] MMC Receive Pause Frame Counter Interrupt Mask (rw) */
    unsigned int RXFOVFIM:1;                /**< \brief [21:21] MMC Receive FIFO Overflow Frame Counter Interrupt Mask (rw) */
    unsigned int RXVLANGBFIM:1;             /**< \brief [22:22] MMC Receive VLAN Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int RXWDOGFIM:1;               /**< \brief [23:23] MMC Receive Watchdog Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXRCVERRFIM:1;             /**< \brief [24:24] MMC Receive Error Frame Counter Interrupt Mask (rw) */
    unsigned int RXCTRLFIM:1;               /**< \brief [25:25] MMC Receive Control Frame Counter Interrupt Mask (rw) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ETH_MMC_RECEIVE_INTERRUPT_MASK_Bits;

/** \brief  Register 66 - MMC Transmit Interrupt Register */
typedef struct _Ifx_ETH_MMC_TRANSMIT_INTERRUPT_Bits
{
    unsigned int TXGBOCTIS:1;               /**< \brief [0:0] MMC Transmit Good Bad Octet Counter Interrupt Status (r) */
    unsigned int TXGBFRMIS:1;               /**< \brief [1:1] MMC Transmit Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TXBCGFIS:1;                /**< \brief [2:2] MMC Transmit Broadcast Good Frame Counter Interrupt Status (r) */
    unsigned int TXMCGFIS:1;                /**< \brief [3:3] MMC Transmit Multicast Good Frame Counter Interrupt Status (r) */
    unsigned int TX64OCTGBFIS:1;            /**< \brief [4:4] MMC Transmit 64 Octet Good Bad Frame Counter Interrupt Status. (r) */
    unsigned int TX65T127OCTGBFIS:1;        /**< \brief [5:5] MMC Transmit 65 to 127 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TX128T255OCTGBFIS:1;       /**< \brief [6:6] MMC Transmit 128 to 255 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TX256T511OCTGBFIS:1;       /**< \brief [7:7] MMC Transmit 256 to 511 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TX512T1023OCTGBFIS:1;      /**< \brief [8:8] MMC Transmit 512 to 1023 Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TX1024TMAXOCTGBFIS:1;      /**< \brief [9:9] MMC Transmit 1024 to Maximum Octet Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TXUCGBFIS:1;               /**< \brief [10:10] MMC Transmit Unicast Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TXMCGBFIS:1;               /**< \brief [11:11] MMC Transmit Multicast Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TXBCGBFIS:1;               /**< \brief [12:12] MMC Transmit Broadcast Good Bad Frame Counter Interrupt Status (r) */
    unsigned int TXUFLOWERFIS:1;            /**< \brief [13:13] MMC Transmit Underflow Error Frame Counter Interrupt Status (r) */
    unsigned int TXSCOLGFIS:1;              /**< \brief [14:14] MMC Transmit Single Collision Good Frame Counter Interrupt Status (r) */
    unsigned int TXMCOLGFIS:1;              /**< \brief [15:15] MMC Transmit Multiple Collision Good Frame Counter Interrupt Status (r) */
    unsigned int TXDEFFIS:1;                /**< \brief [16:16] MMC Transmit Deferred Frame Counter Interrupt Status (r) */
    unsigned int TXLATCOLFIS:1;             /**< \brief [17:17] MMC Transmit Late Collision Frame Counter Interrupt Status (r) */
    unsigned int TXEXCOLFIS:1;              /**< \brief [18:18] MMC Transmit Excessive Collision Frame Counter Interrupt Status (r) */
    unsigned int TXCARERFIS:1;              /**< \brief [19:19] MMC Transmit Carrier Error Frame Counter Interrupt Status (r) */
    unsigned int TXGOCTIS:1;                /**< \brief [20:20] MMC Transmit Good Octet Counter Interrupt Status (r) */
    unsigned int TXGFRMIS:1;                /**< \brief [21:21] MMC Transmit Good Frame Counter Interrupt Status (r) */
    unsigned int TXEXDEFFIS:1;              /**< \brief [22:22] MMC Transmit Excessive Deferral Frame Counter Interrupt Status (r) */
    unsigned int TXPAUSFIS:1;               /**< \brief [23:23] MMC Transmit Pause Frame Counter Interrupt Status (r) */
    unsigned int TXVLANGFIS:1;              /**< \brief [24:24] MMC Transmit VLAN Good Frame Counter Interrupt Status (r) */
    unsigned int TXOSIZEGFIS:1;             /**< \brief [25:25] MMC Transmit Oversize Good Frame Counter Interrupt Status (r) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ETH_MMC_TRANSMIT_INTERRUPT_Bits;

/** \brief  Register 68 - MMC Transmit Interrupt Mask Register */
typedef struct _Ifx_ETH_MMC_TRANSMIT_INTERRUPT_MASK_Bits
{
    unsigned int TXGBOCTIM:1;               /**< \brief [0:0] MMC Transmit Good Bad Octet Counter Interrupt Mask (rw) */
    unsigned int TXGBFRMIM:1;               /**< \brief [1:1] MMC Transmit Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TXBCGFIM:1;                /**< \brief [2:2] MMC Transmit Broadcast Good Frame Counter Interrupt Mask (rw) */
    unsigned int TXMCGFIM:1;                /**< \brief [3:3] MMC Transmit Multicast Good Frame Counter Interrupt Mask (rw) */
    unsigned int TX64OCTGBFIM:1;            /**< \brief [4:4] MMC Transmit 64 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TX65T127OCTGBFIM:1;        /**< \brief [5:5] MMC Transmit 65 to 127 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TX128T255OCTGBFIM:1;       /**< \brief [6:6] MMC Transmit 128 to 255 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TX256T511OCTGBFIM:1;       /**< \brief [7:7] MMC Transmit 256 to 511 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TX512T1023OCTGBFIM:1;      /**< \brief [8:8] MMC Transmit 512 to 1023 Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TX1024TMAXOCTGBFIM:1;      /**< \brief [9:9] MMC Transmit 1024 to Maximum Octet Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TXUCGBFIM:1;               /**< \brief [10:10] MMC Transmit Unicast Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TXMCGBFIM:1;               /**< \brief [11:11] MMC Transmit Multicast Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TXBCGBFIM:1;               /**< \brief [12:12] MMC Transmit Broadcast Good Bad Frame Counter Interrupt Mask (rw) */
    unsigned int TXUFLOWERFIM:1;            /**< \brief [13:13] MMC Transmit Underflow Error Frame Counter Interrupt Mask (rw) */
    unsigned int TXSCOLGFIM:1;              /**< \brief [14:14] MMC Transmit Single Collision Good Frame Counter Interrupt Mask (rw) */
    unsigned int TXMCOLGFIM:1;              /**< \brief [15:15] MMC Transmit Multiple Collision Good Frame Counter Interrupt Mask (rw) */
    unsigned int TXDEFFIM:1;                /**< \brief [16:16] MMC Transmit Deferred Frame Counter Interrupt Mask (rw) */
    unsigned int TXLATCOLFIM:1;             /**< \brief [17:17] MMC Transmit Late Collision Frame Counter Interrupt Mask (rw) */
    unsigned int TXEXCOLFIM:1;              /**< \brief [18:18] MMC Transmit Excessive Collision Frame Counter Interrupt Mask (rw) */
    unsigned int TXCARERFIM:1;              /**< \brief [19:19] MMC Transmit Carrier Error Frame Counter Interrupt Mask (rw) */
    unsigned int TXGOCTIM:1;                /**< \brief [20:20] MMC Transmit Good Octet Counter Interrupt Mask (rw) */
    unsigned int TXGFRMIM:1;                /**< \brief [21:21] MMC Transmit Good Frame Counter Interrupt Mask (rw) */
    unsigned int TXEXDEFFIM:1;              /**< \brief [22:22] MMC Transmit Excessive Deferral Frame Counter Interrupt Mask (rw) */
    unsigned int TXPAUSFIM:1;               /**< \brief [23:23] MMC Transmit Pause Frame Counter Interrupt Mask (rw) */
    unsigned int TXVLANGFIM:1;              /**< \brief [24:24] MMC Transmit VLAN Good Frame Counter Interrupt Mask (rw) */
    unsigned int TXOSIZEGFIM:1;             /**< \brief [25:25] MMC Transmit Oversize Good Frame Counter Interrupt Mask (rw) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ETH_MMC_TRANSMIT_INTERRUPT_MASK_Bits;

/** \brief  Register 6 - Operation Mode Register */
typedef struct _Ifx_ETH_OPERATION_MODE_Bits
{
    unsigned int reserved_0:1;              /**< \brief \internal Reserved */
    unsigned int SR:1;                      /**< \brief [1:1] Start or Stop Receive (rw) */
    unsigned int OSF:1;                     /**< \brief [2:2] Operate on Second Frame (rw) */
    unsigned int RTC:2;                     /**< \brief [4:3] Receive Threshold Control (rw) */
    unsigned int reserved_5:1;              /**< \brief \internal Reserved */
    unsigned int FUF:1;                     /**< \brief [6:6] Forward Undersized Good Frames (rw) */
    unsigned int FEF:1;                     /**< \brief [7:7] Forward Error Frames (rw) */
    unsigned int EFC:1;                     /**< \brief [8:8] Enable HW Flow Control (rw) */
    unsigned int RFA:2;                     /**< \brief [10:9] Threshold for Activating Flow Control (in half-duplex and full-duplex) (rw) */
    unsigned int RFD:2;                     /**< \brief [12:11] Threshold for Deactivating Flow Control (in half-duplex and full-duplex) (rw) */
    unsigned int ST:1;                      /**< \brief [13:13] Start or Stop Transmission Command (rw) */
    unsigned int TTC:3;                     /**< \brief [16:14] Transmit Threshold Control (rw) */
    unsigned int reserved_17:3;             /**< \brief \internal Reserved */
    unsigned int FTF:1;                     /**< \brief [20:20] Flush Transmit FIFO (rw) */
    unsigned int TSF:1;                     /**< \brief [21:21] Transmit Store and Forward (rw) */
    unsigned int RFD_2:1;                   /**< \brief [22:22] MSB of Threshold for Deactivating Flow Control (r) */
    unsigned int RFA_2:1;                   /**< \brief [23:23] MSB of Threshold for Activating Flow Control (r) */
    unsigned int DFF:1;                     /**< \brief [24:24] Disable Flushing of Received Frames (rw) */
    unsigned int RSF:1;                     /**< \brief [25:25] Receive Store and Forward (rw) */
    unsigned int DT:1;                      /**< \brief [26:26] Disable Dropping of TCP/IP Checksum Error Frames (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ETH_OPERATION_MODE_Bits;

/** \brief  Register 11 - PMT Control and Status Register */
typedef struct _Ifx_ETH_PMT_CONTROL_STATUS_Bits
{
    unsigned int PWRDWN:1;                  /**< \brief [0:0] Power Down (rw) */
    unsigned int MGKPKTEN:1;                /**< \brief [1:1] Magic Packet Enable (rw) */
    unsigned int RWKPKTEN:1;                /**< \brief [2:2] Wake-Up Frame Enable (rw) */
    unsigned int reserved_3:2;              /**< \brief \internal Reserved */
    unsigned int MGKPRCVD:1;                /**< \brief [5:5] Magic Packet Received (r) */
    unsigned int RWKPRCVD:1;                /**< \brief [6:6] Wake-Up Frame Received (r) */
    unsigned int reserved_7:2;              /**< \brief \internal Reserved */
    unsigned int GLBLUCAST:1;               /**< \brief [9:9] Global Unicast (rw) */
    unsigned int reserved_10:21;            /**< \brief \internal Reserved */
    unsigned int RWKFILTRST:1;              /**< \brief [31:31] Wake-Up Frame Filter Register Pointer Reset (rw) */
} Ifx_ETH_PMT_CONTROL_STATUS_Bits;

/** \brief  Register 459 - PPS Control Register */
typedef struct _Ifx_ETH_PPS_CONTROL_Bits
{
    unsigned int PPSCTRL_PPSCMD:4;          /**< \brief [3:0] PPSCTRL0 or PPSCMD0 (rw) */
    unsigned int PPSEN0:1;                  /**< \brief [4:4] Flexible PPS Output Mode Enable (r) */
    unsigned int TRGTMODSEL0:2;             /**< \brief [6:5] Target Time Register Mode for PPS0 Output (r) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int PPSCMD1:3;                 /**< \brief [10:8] Flexible PPS1 Output Control (r) */
    unsigned int reserved_11:2;             /**< \brief \internal Reserved */
    unsigned int TRGTMODSEL1:2;             /**< \brief [14:13] Target Time Register Mode for PPS1 Output (r) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int PPSCMD2:3;                 /**< \brief [18:16] Flexible PPS2 Output Control (r) */
    unsigned int reserved_19:2;             /**< \brief \internal Reserved */
    unsigned int TRGTMODSEL2:2;             /**< \brief [22:21] Target Time Register Mode for PPS2 Output (r) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int PPSCMD3:3;                 /**< \brief [26:24] Flexible PPS3 Output Control (r) */
    unsigned int reserved_27:2;             /**< \brief \internal Reserved */
    unsigned int TRGTMODSEL3:2;             /**< \brief [30:29] Target Time Register Mode for PPS3 Output (r) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ETH_PPS_CONTROL_Bits;

/** \brief  Register 3 - Receive Descriptor List Address Register */
typedef struct _Ifx_ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int RDESLA:30;                 /**< \brief [31:2] Start of Receive List (rw) */
} Ifx_ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS_Bits;

/** \brief  Register 9 - Receive Interrupt Watchdog Timer Register */
typedef struct _Ifx_ETH_RECEIVE_INTERRUPT_WATCHDOG_TIMER_Bits
{
    unsigned int RIWT:8;                    /**< \brief [7:0] RI Watchdog Timer Count (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_ETH_RECEIVE_INTERRUPT_WATCHDOG_TIMER_Bits;

/** \brief  Register 2 - Receive Poll Demand Register */
typedef struct _Ifx_ETH_RECEIVE_POLL_DEMAND_Bits
{
    unsigned int RPD:32;                    /**< \brief [31:0] Receive Poll Demand (rw) */
} Ifx_ETH_RECEIVE_POLL_DEMAND_Bits;

/** \brief  Register 10 - Remote Wake-Up Frame Filter Register */
typedef struct _Ifx_ETH_REMOTE_WAKE_UP_FRAME_FILTER_Bits
{
    unsigned int WKUPFRMFTR:32;             /**< \brief [31:0] WKUPFRMFTR (rw) */
} Ifx_ETH_REMOTE_WAKE_UP_FRAME_FILTER_Bits;

/** \brief  Register 112 - Receive Frame Count for Good and Bad 1,024 to Maxsize
 * Bytes Frames */
typedef struct _Ifx_ETH_RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int RX1024_MAXOCTGB:32;        /**< \brief [31:0] RX1024_MAXOCTGB (r) */
} Ifx_ETH_RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 109 - Receive Frame Count for Good and Bad 128 to 255 Bytes
 * Frames */
typedef struct _Ifx_ETH_RX_128TO255OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int RX128_255OCTGB:32;         /**< \brief [31:0] RX128_255OCTGB (r) */
} Ifx_ETH_RX_128TO255OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 110 - Receive Frame Count for Good and Bad 256 to 511 Bytes
 * Frames */
typedef struct _Ifx_ETH_RX_256TO511OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int RX256_511OCTGB:32;         /**< \brief [31:0] RX256_511OCTGB (r) */
} Ifx_ETH_RX_256TO511OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 111 - Receive Frame Count for Good and Bad 512 to 1,023
 * Bytes Frames */
typedef struct _Ifx_ETH_RX_512TO1023OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int RX512_1023OCTGB:32;        /**< \brief [31:0] RX512_1023OCTGB (r) */
} Ifx_ETH_RX_512TO1023OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 107 - Receive Frame Count for Good and Bad 64 Byte Frames */
typedef struct _Ifx_ETH_RX_64OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int RX64OCTGB:32;              /**< \brief [31:0] RX64OCTGB (r) */
} Ifx_ETH_RX_64OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 108 - Receive Frame Count for Good and Bad 65 to 127 Bytes
 * Frames */
typedef struct _Ifx_ETH_RX_65TO127OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int RX65_127OCTGB:32;          /**< \brief [31:0] RX65_127OCTGB (r) */
} Ifx_ETH_RX_65TO127OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 102 - Receive Frame Count for Alignment Error Frames */
typedef struct _Ifx_ETH_RX_ALIGNMENT_ERROR_FRAMES_Bits
{
    unsigned int RXALGNERR:32;              /**< \brief [31:0] RXALGNERR (r) */
} Ifx_ETH_RX_ALIGNMENT_ERROR_FRAMES_Bits;

/** \brief  Register 99 - Receive Frame Count for Good Broadcast Frames */
typedef struct _Ifx_ETH_RX_BROADCAST_FRAMES_GOOD_Bits
{
    unsigned int RXBCASTG:32;               /**< \brief [31:0] RXBCASTG (r) */
} Ifx_ETH_RX_BROADCAST_FRAMES_GOOD_Bits;

/** \brief  Register 121 - Receive Frame Count for Good Control Frames Frames */
typedef struct _Ifx_ETH_RX_CONTROL_FRAMES_GOOD_Bits
{
    unsigned int RXCTRLG:32;                /**< \brief [31:0] RXCTRLG (r) */
} Ifx_ETH_RX_CONTROL_FRAMES_GOOD_Bits;

/** \brief  Register 101 - Receive Frame Count for CRC Error Frames */
typedef struct _Ifx_ETH_RX_CRC_ERROR_FRAMES_Bits
{
    unsigned int RXCRCERR:32;               /**< \brief [31:0] RXCRCERR (r) */
} Ifx_ETH_RX_CRC_ERROR_FRAMES_Bits;

/** \brief  Register 117 - Receive Frame Count for FIFO Overflow Frames */
typedef struct _Ifx_ETH_RX_FIFO_OVERFLOW_FRAMES_Bits
{
    unsigned int RXFIFOOVFL:32;             /**< \brief [31:0] RXFIFOOVFL (r) */
} Ifx_ETH_RX_FIFO_OVERFLOW_FRAMES_Bits;

/** \brief  Register 96 - Receive Frame Count for Good and Bad Frames */
typedef struct _Ifx_ETH_RX_FRAMES_COUNT_GOOD_BAD_Bits
{
    unsigned int RXFRMGB:32;                /**< \brief [31:0] RXFRMGB (r) */
} Ifx_ETH_RX_FRAMES_COUNT_GOOD_BAD_Bits;

/** \brief  Register 104 - Receive Frame Count for Jabber Error Frames */
typedef struct _Ifx_ETH_RX_JABBER_ERROR_FRAMES_Bits
{
    unsigned int RXJABERR:32;               /**< \brief [31:0] RXJABERR (r) */
} Ifx_ETH_RX_JABBER_ERROR_FRAMES_Bits;

/** \brief  Register 114 - Receive Frame Count for Length Error Frames */
typedef struct _Ifx_ETH_RX_LENGTH_ERROR_FRAMES_Bits
{
    unsigned int RXLENERR:32;               /**< \brief [31:0] RXLENERR (r) */
} Ifx_ETH_RX_LENGTH_ERROR_FRAMES_Bits;

/** \brief  Register 100 - Receive Frame Count for Good Multicast Frames */
typedef struct _Ifx_ETH_RX_MULTICAST_FRAMES_GOOD_Bits
{
    unsigned int RXMCASTG:32;               /**< \brief [31:0] RXMCASTG (r) */
} Ifx_ETH_RX_MULTICAST_FRAMES_GOOD_Bits;

/** \brief  Register 97 - Receive Octet Count for Good and Bad Frames */
typedef struct _Ifx_ETH_RX_OCTET_COUNT_GOOD_BAD_Bits
{
    unsigned int RXOCTGB:32;                /**< \brief [31:0] RXOCTGB (r) */
} Ifx_ETH_RX_OCTET_COUNT_GOOD_BAD_Bits;

/** \brief  Register 98 - Receive Octet Count for Good Frames */
typedef struct _Ifx_ETH_RX_OCTET_COUNT_GOOD_Bits
{
    unsigned int RXOCTG:32;                 /**< \brief [31:0] RXOCTG (r) */
} Ifx_ETH_RX_OCTET_COUNT_GOOD_Bits;

/** \brief  Register 115 - Receive Frame Count for Out of Range Frames */
typedef struct _Ifx_ETH_RX_OUT_OF_RANGE_TYPE_FRAMES_Bits
{
    unsigned int RXOUTOFRNG:32;             /**< \brief [31:0] RXOUTOFRNG (r) */
} Ifx_ETH_RX_OUT_OF_RANGE_TYPE_FRAMES_Bits;

/** \brief  Register 106 - Receive Frame Count for Oversize Frames */
typedef struct _Ifx_ETH_RX_OVERSIZE_FRAMES_GOOD_Bits
{
    unsigned int RXOVERSZG:32;              /**< \brief [31:0] RXOVERSZG (r) */
} Ifx_ETH_RX_OVERSIZE_FRAMES_GOOD_Bits;

/** \brief  Register 116 - Receive Frame Count for PAUSE Frames */
typedef struct _Ifx_ETH_RX_PAUSE_FRAMES_Bits
{
    unsigned int RXPAUSEFRM:32;             /**< \brief [31:0] RXPAUSEFRM (r) */
} Ifx_ETH_RX_PAUSE_FRAMES_Bits;

/** \brief  Register 120 - Receive Frame Count for Receive Error Frames */
typedef struct _Ifx_ETH_RX_RECEIVE_ERROR_FRAMES_Bits
{
    unsigned int RXRCVERR:32;               /**< \brief [31:0] RXRCVERR (r) */
} Ifx_ETH_RX_RECEIVE_ERROR_FRAMES_Bits;

/** \brief  Register 103 - Receive Frame Count for Runt Error Frames */
typedef struct _Ifx_ETH_RX_RUNT_ERROR_FRAMES_Bits
{
    unsigned int RXRUNTERR:32;              /**< \brief [31:0] RXRUNTERR (r) */
} Ifx_ETH_RX_RUNT_ERROR_FRAMES_Bits;

/** \brief  Register 105 - Receive Frame Count for Undersize Frames */
typedef struct _Ifx_ETH_RX_UNDERSIZE_FRAMES_GOOD_Bits
{
    unsigned int RXUNDERSZG:32;             /**< \brief [31:0] RXUNDERSZG (r) */
} Ifx_ETH_RX_UNDERSIZE_FRAMES_GOOD_Bits;

/** \brief  Register 113 - Receive Frame Count for Good Unicast Frames */
typedef struct _Ifx_ETH_RX_UNICAST_FRAMES_GOOD_Bits
{
    unsigned int RXUCASTG:32;               /**< \brief [31:0] RXUCASTG (r) */
} Ifx_ETH_RX_UNICAST_FRAMES_GOOD_Bits;

/** \brief  Register 118 - Receive Frame Count for Good and Bad VLAN Frames */
typedef struct _Ifx_ETH_RX_VLAN_FRAMES_GOOD_BAD_Bits
{
    unsigned int RXVLANFRGB:32;             /**< \brief [31:0] RXVLANFRGB (r) */
} Ifx_ETH_RX_VLAN_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 119 - Receive Frame Count for Watchdog Error Frames */
typedef struct _Ifx_ETH_RX_WATCHDOG_ERROR_FRAMES_Bits
{
    unsigned int RXWDGERR:32;               /**< \brief [31:0] RXWDGERR (r) */
} Ifx_ETH_RX_WATCHDOG_ERROR_FRAMES_Bits;

/** \brief  Register 145 - Receive ICMP Error Frame Counter Register */
typedef struct _Ifx_ETH_RXICMP_ERROR_FRAMES_Bits
{
    unsigned int RXICMPERRFRM:32;           /**< \brief [31:0] RXICMPERRFRM (r) */
} Ifx_ETH_RXICMP_ERROR_FRAMES_Bits;

/** \brief  Register 161 - Receive ICMP Error Octet Counter Register */
typedef struct _Ifx_ETH_RXICMP_ERROR_OCTETS_Bits
{
    unsigned int RXICMPERROCT:32;           /**< \brief [31:0] RXICMPERROCT (r) */
} Ifx_ETH_RXICMP_ERROR_OCTETS_Bits;

/** \brief  Register 144 - Receive ICMP Good Frame Counter Register */
typedef struct _Ifx_ETH_RXICMP_GOOD_FRAMES_Bits
{
    unsigned int RXICMPGDFRM:32;            /**< \brief [31:0] RXICMPGDFRM (r) */
} Ifx_ETH_RXICMP_GOOD_FRAMES_Bits;

/** \brief  Register 160 - Receive ICMP Good Octet Counter Register */
typedef struct _Ifx_ETH_RXICMP_GOOD_OCTETS_Bits
{
    unsigned int RXICMPGDOCT:32;            /**< \brief [31:0] RXICMPGDOCT (r) */
} Ifx_ETH_RXICMP_GOOD_OCTETS_Bits;

/** \brief  Register 135 - Receive IPV4 Fragmented Frame Counter Register */
typedef struct _Ifx_ETH_RXIPV4_FRAGMENTED_FRAMES_Bits
{
    unsigned int RXIPV4FRAGFRM:32;          /**< \brief [31:0] RXIPV4FRAGFRM (r) */
} Ifx_ETH_RXIPV4_FRAGMENTED_FRAMES_Bits;

/** \brief  Register 151 - Receive IPV4 Fragmented Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV4_FRAGMENTED_OCTETS_Bits
{
    unsigned int RXIPV4FRAGOCT:32;          /**< \brief [31:0] This field indicates the number of bytes received in fragmented IPv4 datagrams. The value in the IPv4 headers Length field is used to update this counter. (r) */
} Ifx_ETH_RXIPV4_FRAGMENTED_OCTETS_Bits;

/** \brief  Register 132 - Receive IPV4 Good Frame Counter Register */
typedef struct _Ifx_ETH_RXIPV4_GOOD_FRAMES_Bits
{
    unsigned int RXIPV4GDFRM:32;            /**< \brief [31:0] RXIPV4GDFRM (r) */
} Ifx_ETH_RXIPV4_GOOD_FRAMES_Bits;

/** \brief  Register 148 - Receive IPV4 Good Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV4_GOOD_OCTETS_Bits
{
    unsigned int RXIPV4GDOCT:32;            /**< \brief [31:0] This field indicates the number of bytes received in good IPv4 datagrams encapsulating TCP, UDP, or ICMP data. The Ethernet header, FCS, pad, or IP pad (r) */
} Ifx_ETH_RXIPV4_GOOD_OCTETS_Bits;

/** \brief  Register 133 - Receive IPV4 Header Error Frame Counter Register */
typedef struct _Ifx_ETH_RXIPV4_HEADER_ERROR_FRAMES_Bits
{
    unsigned int RXIPV4HDRERRFRM:32;        /**< \brief [31:0] RXIPV4HDRERRFRM (r) */
} Ifx_ETH_RXIPV4_HEADER_ERROR_FRAMES_Bits;

/** \brief  Register 149 - Receive IPV4 Header Error Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV4_HEADER_ERROR_OCTETS_Bits
{
    unsigned int RXIPV4HDRERROCT:32;        /**< \brief [31:0] This field indicates the number of bytes received in the IPv4 datagrams with header errors (checksum, length, or version mismatch). The value in the Length field of IPv4 header is used to update this counter. (r) */
} Ifx_ETH_RXIPV4_HEADER_ERROR_OCTETS_Bits;

/** \brief  Register 134 - Receive IPV4 No Payload Frame Counter Register */
typedef struct _Ifx_ETH_RXIPV4_NO_PAYLOAD_FRAMES_Bits
{
    unsigned int RXIPV4NOPAYFRM:32;         /**< \brief [31:0] RXIPV4NOPAYFRM (r) */
} Ifx_ETH_RXIPV4_NO_PAYLOAD_FRAMES_Bits;

/** \brief  Register 150 - Receive IPV4 No Payload Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV4_NO_PAYLOAD_OCTETS_Bits
{
    unsigned int RXIPV4NOPAYOCT:32;         /**< \brief [31:0] This field indicates the number of bytes received in IPv4 datagrams that did not have a TCP, UDP, or ICMP payload. The value in the IPv4 headers Length field is used to update this counter. (r) */
} Ifx_ETH_RXIPV4_NO_PAYLOAD_OCTETS_Bits;

/** \brief  Register 152 - Receive IPV4 Fragmented Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_Bits
{
    unsigned int RXIPV4UDSBLOCT:32;         /**< \brief [31:0] RXIPV4UDSBLOCT (r) */
} Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_Bits;

/** \brief  Register 136 - Receive IPV4 UDP Checksum Disabled Frame Counter
 * Register */
typedef struct _Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES_Bits
{
    unsigned int RXIPV4UDSBLFRM:32;         /**< \brief [31:0] RXIPV4UDSBLFRM (r) */
} Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES_Bits;

/** \brief  Register 137 - Receive IPV6 Good Frame Counter Register */
typedef struct _Ifx_ETH_RXIPV6_GOOD_FRAMES_Bits
{
    unsigned int RXIPV6GDFRM:32;            /**< \brief [31:0] RXIPV6GDFRM (r) */
} Ifx_ETH_RXIPV6_GOOD_FRAMES_Bits;

/** \brief  Register 153 - Receive IPV6 Good Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV6_GOOD_OCTETS_Bits
{
    unsigned int RXIPV6GDOCT:32;            /**< \brief [31:0] Thsi field indicates the number of bytes received in good IPv6 datagrams encapsulating TCP, UDP or ICMPv6 data. (r) */
} Ifx_ETH_RXIPV6_GOOD_OCTETS_Bits;

/** \brief  Register 138 - Receive IPV6 Header Error Frame Counter Register */
typedef struct _Ifx_ETH_RXIPV6_HEADER_ERROR_FRAMES_Bits
{
    unsigned int RXIPV6HDRERRFRM:32;        /**< \brief [31:0] RXIPV6HDRERRFRM (r) */
} Ifx_ETH_RXIPV6_HEADER_ERROR_FRAMES_Bits;

/** \brief  Register 154 - Receive IPV6 Header Error Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV6_HEADER_ERROR_OCTETS_Bits
{
    unsigned int RXIPV6HDRERROCT:32;        /**< \brief [31:0] This field indicates the number of bytes received in IPv6 datagrams with header errors (length or version mismatch). The value in the IPv6 headers Length field is used to update this counter. (r) */
} Ifx_ETH_RXIPV6_HEADER_ERROR_OCTETS_Bits;

/** \brief  Register 139 - Receive IPV6 No Payload Frame Counter Register */
typedef struct _Ifx_ETH_RXIPV6_NO_PAYLOAD_FRAMES_Bits
{
    unsigned int RXIPV6NOPAYFRM:32;         /**< \brief [31:0] RXIPV6NOPAYFRM (r) */
} Ifx_ETH_RXIPV6_NO_PAYLOAD_FRAMES_Bits;

/** \brief  Register 155 - Receive IPV6 No Payload Octet Counter Register */
typedef struct _Ifx_ETH_RXIPV6_NO_PAYLOAD_OCTETS_Bits
{
    unsigned int RXIPV6NOPAYOCT:32;         /**< \brief [31:0] This field indicates the number of bytes received in IPv6 datagrams that did not have a TCP, UDP, or ICMP payload. The value in the IPv6 headers Length field is used to update this counter. (r) */
} Ifx_ETH_RXIPV6_NO_PAYLOAD_OCTETS_Bits;

/** \brief  Register 143 - Receive TCP Error Frame Counter Register */
typedef struct _Ifx_ETH_RXTCP_ERROR_FRAMES_Bits
{
    unsigned int RXTCPERRFRM:32;            /**< \brief [31:0] RXTCPERRFRM (r) */
} Ifx_ETH_RXTCP_ERROR_FRAMES_Bits;

/** \brief  Register 159 - Receive TCP Error Octet Counter Register */
typedef struct _Ifx_ETH_RXTCP_ERROR_OCTETS_Bits
{
    unsigned int RXTCPERROCT:32;            /**< \brief [31:0] RXTCPERROCT (r) */
} Ifx_ETH_RXTCP_ERROR_OCTETS_Bits;

/** \brief  Register 142 - Receive TCP Good Frame Counter Register */
typedef struct _Ifx_ETH_RXTCP_GOOD_FRAMES_Bits
{
    unsigned int RXTCPGDFRM:32;             /**< \brief [31:0] RXTCPGDFRM (r) */
} Ifx_ETH_RXTCP_GOOD_FRAMES_Bits;

/** \brief  Register 158 - Receive TCP Good Octet Counter Register */
typedef struct _Ifx_ETH_RXTCP_GOOD_OCTETS_Bits
{
    unsigned int RXTCPGDOCT:32;             /**< \brief [31:0] RXTCPGDOCT (r) */
} Ifx_ETH_RXTCP_GOOD_OCTETS_Bits;

/** \brief  Register 141 - Receive UDP Error Frame Counter Register */
typedef struct _Ifx_ETH_RXUDP_ERROR_FRAMES_Bits
{
    unsigned int RXUDPERRFRM:32;            /**< \brief [31:0] RXUDPERRFRM (r) */
} Ifx_ETH_RXUDP_ERROR_FRAMES_Bits;

/** \brief  Register 157 - Receive UDP Error Octet Counter Register */
typedef struct _Ifx_ETH_RXUDP_ERROR_OCTETS_Bits
{
    unsigned int RXUDPERROCT:32;            /**< \brief [31:0] RXUDPERROCT (r) */
} Ifx_ETH_RXUDP_ERROR_OCTETS_Bits;

/** \brief  Register 140 - Receive UDP Good Frame Counter Register */
typedef struct _Ifx_ETH_RXUDP_GOOD_FRAMES_Bits
{
    unsigned int RXUDPGDFRM:32;             /**< \brief [31:0] RXUDPGDFRM (r) */
} Ifx_ETH_RXUDP_GOOD_FRAMES_Bits;

/** \brief  Register 156 - Receive UDP Good Octet Counter Register */
typedef struct _Ifx_ETH_RXUDP_GOOD_OCTETS_Bits
{
    unsigned int RXUDPGDOCT:32;             /**< \brief [31:0] RXUDPGDOCT (r) */
} Ifx_ETH_RXUDP_GOOD_OCTETS_Bits;

/** \brief  Register 5 - Status Register */
typedef struct _Ifx_ETH_STATUS_Bits
{
    unsigned int TI:1;                      /**< \brief [0:0] Transmit Interrupt (rw) */
    unsigned int TPS:1;                     /**< \brief [1:1] Transmit Process Stopped (rw) */
    unsigned int TU:1;                      /**< \brief [2:2] Transmit Buffer Unavailable (rw) */
    unsigned int TJT:1;                     /**< \brief [3:3] Transmit Jabber Timeout (rw) */
    unsigned int OVF:1;                     /**< \brief [4:4] Receive Overflow (rw) */
    unsigned int UNF:1;                     /**< \brief [5:5] Transmit Underflow (rw) */
    unsigned int RI:1;                      /**< \brief [6:6] Receive Interrupt (rw) */
    unsigned int RU:1;                      /**< \brief [7:7] Receive Buffer Unavailable (rw) */
    unsigned int RPS:1;                     /**< \brief [8:8] Receive Process Stopped (rw) */
    unsigned int RWT:1;                     /**< \brief [9:9] Receive Watchdog Timeout (rw) */
    unsigned int ETI:1;                     /**< \brief [10:10] Early Transmit Interrupt (rw) */
    unsigned int reserved_11:2;             /**< \brief \internal Reserved */
    unsigned int FBI:1;                     /**< \brief [13:13] Fatal Bus Error Interrupt (rw) */
    unsigned int ERI:1;                     /**< \brief [14:14] Early Receive Interrupt (rw) */
    unsigned int AIS:1;                     /**< \brief [15:15] Abnormal Interrupt Summary (rw) */
    unsigned int NIS:1;                     /**< \brief [16:16] Normal Interrupt Summary (rw) */
    unsigned int RS:3;                      /**< \brief [19:17] Received Process State (r) */
    unsigned int TS:3;                      /**< \brief [22:20] Transmit Process State (r) */
    unsigned int EB:3;                      /**< \brief [25:23] Error Bits (r) */
    unsigned int GLI:1;                     /**< \brief [26:26] GMAC Line interface Interrupt (r) */
    unsigned int GMI:1;                     /**< \brief [27:27] GMAC MMC Interrupt (r) */
    unsigned int GPI:1;                     /**< \brief [28:28] GMAC PMT Interrupt (r) */
    unsigned int TTI:1;                     /**< \brief [29:29] Timestamp Trigger Interrupt (r) */
    unsigned int GLPII:1;                   /**< \brief [30:30] GMAC LPI Interrupt (for Channel 0) (r) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ETH_STATUS_Bits;

/** \brief  Register 449 - Sub-Second Increment Register */
typedef struct _Ifx_ETH_SUB_SECOND_INCREMENT_Bits
{
    unsigned int SSINC:8;                   /**< \brief [7:0] Sub-second Increment Value (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_ETH_SUB_SECOND_INCREMENT_Bits;

/** \brief  Register 457 - System Time - Higher Word Seconds Register */
typedef struct _Ifx_ETH_SYSTEM_TIME_HIGHER_WORD_SECONDS_Bits
{
    unsigned int TSHWR:16;                  /**< \brief [15:0] Timestamp Higher Word Register (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ETH_SYSTEM_TIME_HIGHER_WORD_SECONDS_Bits;

/** \brief  Register 451 - System Time - Nanoseconds Register */
typedef struct _Ifx_ETH_SYSTEM_TIME_NANOSECONDS_Bits
{
    unsigned int TSSS:31;                   /**< \brief [30:0] Timestamp Sub Seconds (r) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ETH_SYSTEM_TIME_NANOSECONDS_Bits;

/** \brief  Register 453 - System Time - Nanoseconds Update Register */
typedef struct _Ifx_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE_Bits
{
    unsigned int TSSS:31;                   /**< \brief [30:0] Timestamp Sub Second (rw) */
    unsigned int ADDSUB:1;                  /**< \brief [31:31] Add or subtract time (rw) */
} Ifx_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE_Bits;

/** \brief  Register 450 - System Time - Seconds Register */
typedef struct _Ifx_ETH_SYSTEM_TIME_SECONDS_Bits
{
    unsigned int TSS:32;                    /**< \brief [31:0] Timestamp Second (r) */
} Ifx_ETH_SYSTEM_TIME_SECONDS_Bits;

/** \brief  Register 452 - System Time - Seconds Update Register */
typedef struct _Ifx_ETH_SYSTEM_TIME_SECONDS_UPDATE_Bits
{
    unsigned int TSS:32;                    /**< \brief [31:0] Timestamp Second (rw) */
} Ifx_ETH_SYSTEM_TIME_SECONDS_UPDATE_Bits;

/** \brief  Register 456 - Target Time Nanoseconds Register */
typedef struct _Ifx_ETH_TARGET_TIME_NANOSECONDS_Bits
{
    unsigned int TTSLO:31;                  /**< \brief [30:0] Target Timestamp Low Register (rw) */
    unsigned int TRGTBUSY:1;                /**< \brief [31:31] Target Time Register Busy (r) */
} Ifx_ETH_TARGET_TIME_NANOSECONDS_Bits;

/** \brief  Register 455 - Target Time Seconds Register */
typedef struct _Ifx_ETH_TARGET_TIME_SECONDS_Bits
{
    unsigned int TSTR:32;                   /**< \brief [31:0] Target Time Seconds Register (rw) */
} Ifx_ETH_TARGET_TIME_SECONDS_Bits;

/** \brief  Register 454 - Timestamp Addend Register */
typedef struct _Ifx_ETH_TIMESTAMP_ADDEND_Bits
{
    unsigned int TSAR:32;                   /**< \brief [31:0] Timestamp Addend Register (rw) */
} Ifx_ETH_TIMESTAMP_ADDEND_Bits;

/** \brief  Register 448 - Timestamp Control Register */
typedef struct _Ifx_ETH_TIMESTAMP_CONTROL_Bits
{
    unsigned int TSENA:1;                   /**< \brief [0:0] Timestamp Enable (rw) */
    unsigned int TSCFUPDT:1;                /**< \brief [1:1] Timestamp Fine or Coarse Update (rw) */
    unsigned int TSINIT:1;                  /**< \brief [2:2] Timestamp Initialize (rw) */
    unsigned int TSUPDT:1;                  /**< \brief [3:3] Timestamp Update (rw) */
    unsigned int TSTRIG:1;                  /**< \brief [4:4] Timestamp Interrupt Trigger Enable (rw) */
    unsigned int TSADDREG:1;                /**< \brief [5:5] Addend Reg Update (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int TSENALL:1;                 /**< \brief [8:8] Enable Timestamp for All Frames (rw) */
    unsigned int TSCTRLSSR:1;               /**< \brief [9:9] Timestamp Digital or Binary Rollover Control (rw) */
    unsigned int TSVER2ENA:1;               /**< \brief [10:10] Enable PTP packet Processing for Version 2 Format (rw) */
    unsigned int TSIPENA:1;                 /**< \brief [11:11] Enable Processing of PTP over Ethernet Frames (rw) */
    unsigned int TSIPV6ENA:1;               /**< \brief [12:12] Enable Processing of PTP Frames Sent Over IPv6-UDP (rw) */
    unsigned int TSIPV4ENA:1;               /**< \brief [13:13] Enable Processing of PTP Frames Sent over IPv4-UDP (rw) */
    unsigned int TSEVNTENA:1;               /**< \brief [14:14] Enable Timestamp Snapshot for Event Messages (rw) */
    unsigned int TSMSTRENA:1;               /**< \brief [15:15] Enable Snapshot for Messages Relevant to Master (rw) */
    unsigned int SNAPTYPSEL:2;              /**< \brief [17:16] Select PTP packets for Taking Snapshots (rw) */
    unsigned int TSENMACADDR:1;             /**< \brief [18:18] Enable MAC address for PTP Frame Filtering (rw) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int ATSFC:1;                   /**< \brief [24:24] Auxiliary Snapshot FIFO Clear (r) */
    unsigned int ATSEN0:1;                  /**< \brief [25:25] Auxiliary Snapshot 0 Enable (r) */
    unsigned int ATSEN1:1;                  /**< \brief [26:26] Auxiliary Snapshot 1 Enable (r) */
    unsigned int ATSEN2:1;                  /**< \brief [27:27] Auxiliary Snapshot 2 Enable (r) */
    unsigned int ATSEN3:1;                  /**< \brief [28:28] Auxiliary Snapshot 3 Enable (r) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_ETH_TIMESTAMP_CONTROL_Bits;

/** \brief  Register 458 - Timestamp Status Register */
typedef struct _Ifx_ETH_TIMESTAMP_STATUS_Bits
{
    unsigned int TSSOVF:1;                  /**< \brief [0:0] Timestamp Seconds Overflow (r) */
    unsigned int TSTARGT:1;                 /**< \brief [1:1] Timestamp Target Time Reached (r) */
    unsigned int AUXTSTRIG:1;               /**< \brief [2:2] Auxiliary Timestamp Trigger Snapshot (r) */
    unsigned int TSTRGTERR:1;               /**< \brief [3:3] Timestamp Target Time Error (r) */
    unsigned int TSTARGT1:1;                /**< \brief [4:4] Timestamp Target Time Reached for Target Time PPS1 (r) */
    unsigned int TSTRGTERR1:1;              /**< \brief [5:5] Timestamp Target Time Error (r) */
    unsigned int TSTARGT2:1;                /**< \brief [6:6] Timestamp Target Time Reached for Target Time PPS2 (r) */
    unsigned int TSTRGTERR2:1;              /**< \brief [7:7] Timestamp Target Time Error (r) */
    unsigned int TSTARGT3:1;                /**< \brief [8:8] Timestamp Target Time Reached for Target Time PPS3 (r) */
    unsigned int TSTRGTERR3:1;              /**< \brief [9:9] Timestamp Target Time Error (r) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int ATSSTN:4;                  /**< \brief [19:16] Auxiliary Timestamp Snapshot Trigger Identifier (r) */
    unsigned int reserved_20:4;             /**< \brief \internal Reserved */
    unsigned int ATSSTM:1;                  /**< \brief [24:24] Auxiliary Timestamp Snapshot Trigger Missed (r) */
    unsigned int ATSNS:5;                   /**< \brief [29:25] Number of Auxiliary Timestamp Snapshots (r) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ETH_TIMESTAMP_STATUS_Bits;

/** \brief  Register 4 - Transmit Descriptor List Address Register */
typedef struct _Ifx_ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int TDESLA:30;                 /**< \brief [31:2] Start of Transmit List (rw) */
} Ifx_ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS_Bits;

/** \brief  Register 1 - Transmit Poll Demand Register */
typedef struct _Ifx_ETH_TRANSMIT_POLL_DEMAND_Bits
{
    unsigned int TPD:32;                    /**< \brief [31:0] Transmit Poll Demand (rw) */
} Ifx_ETH_TRANSMIT_POLL_DEMAND_Bits;

/** \brief  Register 78 - Transmit Octet Count for Good and Bad 1024 to Maxsize
 * Bytes Frames */
typedef struct _Ifx_ETH_TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int TX1024_MAXOCTGB:32;        /**< \brief [31:0] TX1024_MAXOCTGB (r) */
} Ifx_ETH_TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 75 - Transmit Octet Count for Good and Bad 128 to 255 Bytes
 * Frames */
typedef struct _Ifx_ETH_TX_128TO255OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int TX128_255OCTGB:32;         /**< \brief [31:0] TX128_255OCTGB (r) */
} Ifx_ETH_TX_128TO255OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 76 - Transmit Octet Count for Good and Bad 256 to 511 Bytes
 * Frames */
typedef struct _Ifx_ETH_TX_256TO511OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int TX256_511OCTGB:32;         /**< \brief [31:0] TX256_511OCTGB (r) */
} Ifx_ETH_TX_256TO511OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 77 - Transmit Octet Count for Good and Bad 512 to 1023
 * Bytes Frames */
typedef struct _Ifx_ETH_TX_512TO1023OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int TX512_1023OCTGB:32;        /**< \brief [31:0] TX512_1023OCTGB (r) */
} Ifx_ETH_TX_512TO1023OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 73 - Transmit Octet Count for Good and Bad 64 Byte Frames */
typedef struct _Ifx_ETH_TX_64OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int TX64OCTGB:32;              /**< \brief [31:0] TX64OCTGB (r) */
} Ifx_ETH_TX_64OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 74 - Transmit Octet Count for Good and Bad 65 to 127 Bytes
 * Frames */
typedef struct _Ifx_ETH_TX_65TO127OCTETS_FRAMES_GOOD_BAD_Bits
{
    unsigned int TX65_127OCTGB:32;          /**< \brief [31:0] TX65_127OCTGB (r) */
} Ifx_ETH_TX_65TO127OCTETS_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 81 - Transmit Frame Count for Good and Bad Broadcast Frames */
typedef struct _Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_BAD_Bits
{
    unsigned int TXBCASTGB:32;              /**< \brief [31:0] TXBCASTGB (r) */
} Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 71 - Transmit Frame Count for Good Broadcast Frames */
typedef struct _Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_Bits
{
    unsigned int TXBCASTG:32;               /**< \brief [31:0] TXBCASTG (r) */
} Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_Bits;

/** \brief  Register 88 - Transmit Frame Count for Carrier Sense Error Frames */
typedef struct _Ifx_ETH_TX_CARRIER_ERROR_FRAMES_Bits
{
    unsigned int TXCARR:32;                 /**< \brief [31:0] TXCARR (r) */
} Ifx_ETH_TX_CARRIER_ERROR_FRAMES_Bits;

/** \brief  Register 85 - Transmit Frame Count for Deferred Frames */
typedef struct _Ifx_ETH_TX_DEFERRED_FRAMES_Bits
{
    unsigned int TXDEFRD:32;                /**< \brief [31:0] TXDEFRD (r) */
} Ifx_ETH_TX_DEFERRED_FRAMES_Bits;

/** \brief  Register 87 - Transmit Frame Count for Excessive Collision Error
 * Frames */
typedef struct _Ifx_ETH_TX_EXCESSIVE_COLLISION_FRAMES_Bits
{
    unsigned int TXEXSCOL:32;               /**< \brief [31:0] TXEXSCOL (r) */
} Ifx_ETH_TX_EXCESSIVE_COLLISION_FRAMES_Bits;

/** \brief  Register 91 - Transmit Frame Count for Excessive Deferral Error
 * Frames */
typedef struct _Ifx_ETH_TX_EXCESSIVE_DEFERRAL_ERROR_Bits
{
    unsigned int TXEXSDEF:32;               /**< \brief [31:0] TXEXSDEF (r) */
} Ifx_ETH_TX_EXCESSIVE_DEFERRAL_ERROR_Bits;

/** \brief  Register 70 - Transmit Frame Count for Good and Bad Frames */
typedef struct _Ifx_ETH_TX_FRAME_COUNT_GOOD_BAD_Bits
{
    unsigned int TXFRMGB:32;                /**< \brief [31:0] TXFRMGB (r) */
} Ifx_ETH_TX_FRAME_COUNT_GOOD_BAD_Bits;

/** \brief  Register 90 - Transmit Frame Count for Good Frames */
typedef struct _Ifx_ETH_TX_FRAME_COUNT_GOOD_Bits
{
    unsigned int TXFRMG:32;                 /**< \brief [31:0] TXFRMG (r) */
} Ifx_ETH_TX_FRAME_COUNT_GOOD_Bits;

/** \brief  Register 86 - Transmit Frame Count for Late Collision Error Frames */
typedef struct _Ifx_ETH_TX_LATE_COLLISION_FRAMES_Bits
{
    unsigned int TXLATECOL:32;              /**< \brief [31:0] TXLATECOL (r) */
} Ifx_ETH_TX_LATE_COLLISION_FRAMES_Bits;

/** \brief  Register 80 - Transmit Frame Count for Good and Bad Multicast Frames */
typedef struct _Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_BAD_Bits
{
    unsigned int TXMCASTGB:32;              /**< \brief [31:0] TXMCASTGB (r) */
} Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 72 - Transmit Frame Count for Good Multicast Frames */
typedef struct _Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_Bits
{
    unsigned int TXMCASTG:32;               /**< \brief [31:0] TXMCASTG (r) */
} Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_Bits;

/** \brief  Register 84 - Transmit Frame Count for Frames Transmitted after
 * Multiple Collision */
typedef struct _Ifx_ETH_TX_MULTIPLE_COLLISION_GOOD_FRAMES_Bits
{
    unsigned int TXMULTCOLG:32;             /**< \brief [31:0] TXMULTCOLG (r) */
} Ifx_ETH_TX_MULTIPLE_COLLISION_GOOD_FRAMES_Bits;

/** \brief  Register 69 - Transmit Octet Count for Good and Bad Frames */
typedef struct _Ifx_ETH_TX_OCTET_COUNT_GOOD_BAD_Bits
{
    unsigned int TXOCTGB:32;                /**< \brief [31:0] TXOCTGB (r) */
} Ifx_ETH_TX_OCTET_COUNT_GOOD_BAD_Bits;

/** \brief  Register 89 - Transmit Octet Count for Good Frames */
typedef struct _Ifx_ETH_TX_OCTET_COUNT_GOOD_Bits
{
    unsigned int TXOCTG:32;                 /**< \brief [31:0] TXOCTG (r) */
} Ifx_ETH_TX_OCTET_COUNT_GOOD_Bits;

/** \brief  Register 94 - Transmit Frame Count for Good Oversize Frames */
typedef struct _Ifx_ETH_TX_OSIZE_FRAMES_GOOD_Bits
{
    unsigned int TXOSIZG:32;                /**< \brief [31:0] TXOSIZG (r) */
} Ifx_ETH_TX_OSIZE_FRAMES_GOOD_Bits;

/** \brief  Register 92 - Transmit Frame Count for Good PAUSE Frames */
typedef struct _Ifx_ETH_TX_PAUSE_FRAMES_Bits
{
    unsigned int TXPAUSE:32;                /**< \brief [31:0] TXPAUSE (r) */
} Ifx_ETH_TX_PAUSE_FRAMES_Bits;

/** \brief  Register 83 - Transmit Frame Count for Frames Transmitted after
 * Single Collision */
typedef struct _Ifx_ETH_TX_SINGLE_COLLISION_GOOD_FRAMES_Bits
{
    unsigned int TXSNGLCOLG:32;             /**< \brief [31:0] TXSNGLCOLG (r) */
} Ifx_ETH_TX_SINGLE_COLLISION_GOOD_FRAMES_Bits;

/** \brief  Register 82 - Transmit Frame Count for Underflow Error Frames */
typedef struct _Ifx_ETH_TX_UNDERFLOW_ERROR_FRAMES_Bits
{
    unsigned int TXUNDRFLW:32;              /**< \brief [31:0] TXUNDRFLW (r) */
} Ifx_ETH_TX_UNDERFLOW_ERROR_FRAMES_Bits;

/** \brief  Register 79 - Transmit Frame Count for Good and Bad Unicast Frames */
typedef struct _Ifx_ETH_TX_UNICAST_FRAMES_GOOD_BAD_Bits
{
    unsigned int TXUCASTGB:32;              /**< \brief [31:0] TXUCASTGB (r) */
} Ifx_ETH_TX_UNICAST_FRAMES_GOOD_BAD_Bits;

/** \brief  Register 93 - Transmit Frame Count for Good VLAN Frames */
typedef struct _Ifx_ETH_TX_VLAN_FRAMES_GOOD_Bits
{
    unsigned int TXVLANG:32;                /**< \brief [31:0] TXVLANG (r) */
} Ifx_ETH_TX_VLAN_FRAMES_GOOD_Bits;

/** \brief  Register 8 - Version Register */
typedef struct _Ifx_ETH_VERSION_Bits
{
    unsigned int SNPSVER:8;                 /**< \brief [7:0] SNPSVER (r) */
    unsigned int USERVER:8;                 /**< \brief [15:8] USERVER (r) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ETH_VERSION_Bits;

/** \brief  Register 7 - VLAN Tag Register */
typedef struct _Ifx_ETH_VLAN_TAG_Bits
{
    unsigned int VL:16;                     /**< \brief [15:0] VLAN Tag Identifier for Receive Frames (rw) */
    unsigned int ETV:1;                     /**< \brief [16:16] Enable 12-Bit VLAN Tag Comparison (rw) */
    unsigned int VTIM:1;                    /**< \brief [17:17] VLAN Tag Inverse Match Enable (rw) */
    unsigned int ESVL:1;                    /**< \brief [18:18] Enable S-VLAN (rw) */
    unsigned int VTHM:1;                    /**< \brief [19:19] VLAN Tag Hash Table Match Enable (r) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_ETH_VLAN_TAG_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Eth_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_ETH_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ETH_ACCEN1;

/** \brief  Register 11 - AHB or AXI Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_AHB_OR_AXI_STATUS_Bits B;       /**< \brief Bitfield access */
} Ifx_ETH_AHB_OR_AXI_STATUS;

/** \brief  Register 0 - Bus Mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_BUS_MODE_Bits B;                /**< \brief Bitfield access */
} Ifx_ETH_BUS_MODE;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_ETH_CLC;

/** \brief  Register 21 - Current Host Receive Buffer Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_CURRENT_HOST_RECEIVE_BUFFER_ADDRESS_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_CURRENT_HOST_RECEIVE_BUFFER_ADDRESS;

/** \brief  Register 19 - Current Host Receive Descriptor Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_CURRENT_HOST_RECEIVE_DESCRIPTOR_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_CURRENT_HOST_RECEIVE_DESCRIPTOR;

/** \brief  Register 20 - Current Host Transmit Buffer Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS;

/** \brief  Register 18 - Current Host Transmit Descriptor Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_CURRENT_HOST_TRANSMIT_DESCRIPTOR_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_CURRENT_HOST_TRANSMIT_DESCRIPTOR;

/** \brief  Register 9 - Debug Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_DEBUG_Bits B;                   /**< \brief Bitfield access */
} Ifx_ETH_DEBUG;

/** \brief  Register 6 - Flow Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_FLOW_CONTROL_Bits B;            /**< \brief Bitfield access */
} Ifx_ETH_FLOW_CONTROL;

/** \brief  Register 4 - GMII Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_GMII_ADDRESS_Bits B;            /**< \brief Bitfield access */
} Ifx_ETH_GMII_ADDRESS;

/** \brief  Register 5 - GMII Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_GMII_DATA_Bits B;               /**< \brief Bitfield access */
} Ifx_ETH_GMII_DATA;

/** \brief  Input and Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_GPCTL_Bits B;                   /**< \brief Bitfield access */
} Ifx_ETH_GPCTL;

/** \brief  Register 2 - Hash Table High Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_HASH_TABLE_HIGH_Bits B;         /**< \brief Bitfield access */
} Ifx_ETH_HASH_TABLE_HIGH;

/** \brief  Register 3 - Hash Table Low Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_HASH_TABLE_LOW_Bits B;          /**< \brief Bitfield access */
} Ifx_ETH_HASH_TABLE_LOW;

/** \brief  Register 22 - HW Feature Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_HW_FEATURE_Bits B;              /**< \brief Bitfield access */
} Ifx_ETH_HW_FEATURE;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_ETH_ID;

/** \brief  Register 7 - Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_INTERRUPT_ENABLE_Bits B;        /**< \brief Bitfield access */
} Ifx_ETH_INTERRUPT_ENABLE;

/** \brief  Register 15 - Interrupt Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_INTERRUPT_MASK_Bits B;          /**< \brief Bitfield access */
} Ifx_ETH_INTERRUPT_MASK;

/** \brief  Register 14 - Interrupt Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_INTERRUPT_STATUS_Bits B;        /**< \brief Bitfield access */
} Ifx_ETH_INTERRUPT_STATUS;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_ETH_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_ETH_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_ETH_KRSTCLR;

/** \brief  MAC Address High Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MAC_ADDRESS_HIGH_Bits B;        /**< \brief Bitfield access */
} Ifx_ETH_MAC_ADDRESS_HIGH;

/** \brief  MAC Address Low Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MAC_ADDRESS_LOW_Bits B;         /**< \brief Bitfield access */
} Ifx_ETH_MAC_ADDRESS_LOW;

/** \brief  Register 0 - MAC Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MAC_CONFIGURATION_Bits B;       /**< \brief Bitfield access */
} Ifx_ETH_MAC_CONFIGURATION;

/** \brief  Register 1 - MAC Frame Filter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MAC_FRAME_FILTER_Bits B;        /**< \brief Bitfield access */
} Ifx_ETH_MAC_FRAME_FILTER;

/** \brief  Register 8 - Missed Frame and Buffer Overflow Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER;

/** \brief  Register 64 - MMC Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MMC_CONTROL_Bits B;             /**< \brief Bitfield access */
} Ifx_ETH_MMC_CONTROL;

/** \brief  Register 130 - MMC Receive Checksum Offload Interrupt Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT;

/** \brief  Register 128 - MMC Receive Checksum Offload Interrupt Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_MASK_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_MASK;

/** \brief  Register 65 - MMC Receive Interrupt Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MMC_RECEIVE_INTERRUPT_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_MMC_RECEIVE_INTERRUPT;

/** \brief  - */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MMC_RECEIVE_INTERRUPT_MASK_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_MMC_RECEIVE_INTERRUPT_MASK;

/** \brief  Register 66 - MMC Transmit Interrupt Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MMC_TRANSMIT_INTERRUPT_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_MMC_TRANSMIT_INTERRUPT;

/** \brief  Register 68 - MMC Transmit Interrupt Mask Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_MMC_TRANSMIT_INTERRUPT_MASK_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_MMC_TRANSMIT_INTERRUPT_MASK;

/** \brief  Register 6 - Operation Mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_OPERATION_MODE_Bits B;          /**< \brief Bitfield access */
} Ifx_ETH_OPERATION_MODE;

/** \brief  Register 11 - PMT Control and Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_PMT_CONTROL_STATUS_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_PMT_CONTROL_STATUS;

/** \brief  Register 459 - PPS Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_PPS_CONTROL_Bits B;             /**< \brief Bitfield access */
} Ifx_ETH_PPS_CONTROL;

/** \brief  Register 3 - Receive Descriptor List Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS;

/** \brief  Register 9 - Receive Interrupt Watchdog Timer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RECEIVE_INTERRUPT_WATCHDOG_TIMER_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RECEIVE_INTERRUPT_WATCHDOG_TIMER;

/** \brief  Register 2 - Receive Poll Demand Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RECEIVE_POLL_DEMAND_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_RECEIVE_POLL_DEMAND;

/** \brief  Register 10 - Remote Wake-Up Frame Filter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_REMOTE_WAKE_UP_FRAME_FILTER_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_REMOTE_WAKE_UP_FRAME_FILTER;

/** \brief  Register 112 - Receive Frame Count for Good and Bad 1,024 to Maxsize
 * Bytes Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 109 - Receive Frame Count for Good and Bad 128 to 255 Bytes
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_128TO255OCTETS_FRAMES_GOOD_BAD_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_RX_128TO255OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 110 - Receive Frame Count for Good and Bad 256 to 511 Bytes
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_256TO511OCTETS_FRAMES_GOOD_BAD_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_RX_256TO511OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 111 - Receive Frame Count for Good and Bad 512 to 1,023
 * Bytes Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_512TO1023OCTETS_FRAMES_GOOD_BAD_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RX_512TO1023OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 107 - Receive Frame Count for Good and Bad 64 Byte Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_64OCTETS_FRAMES_GOOD_BAD_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RX_64OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 108 - Receive Frame Count for Good and Bad 65 to 127 Bytes
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_65TO127OCTETS_FRAMES_GOOD_BAD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RX_65TO127OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 102 - Receive Frame Count for Alignment Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_ALIGNMENT_ERROR_FRAMES_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_RX_ALIGNMENT_ERROR_FRAMES;

/** \brief  Register 99 - Receive Frame Count for Good Broadcast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_BROADCAST_FRAMES_GOOD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RX_BROADCAST_FRAMES_GOOD;

/** \brief  Register 121 - Receive Frame Count for Good Control Frames Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_CONTROL_FRAMES_GOOD_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RX_CONTROL_FRAMES_GOOD;

/** \brief  Register 101 - Receive Frame Count for CRC Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_CRC_ERROR_FRAMES_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_RX_CRC_ERROR_FRAMES;

/** \brief  Register 117 - Receive Frame Count for FIFO Overflow Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_FIFO_OVERFLOW_FRAMES_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RX_FIFO_OVERFLOW_FRAMES;

/** \brief  Register 96 - Receive Frame Count for Good and Bad Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_FRAMES_COUNT_GOOD_BAD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RX_FRAMES_COUNT_GOOD_BAD;

/** \brief  Register 104 - Receive Frame Count for Jabber Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_JABBER_ERROR_FRAMES_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RX_JABBER_ERROR_FRAMES;

/** \brief  Register 114 - Receive Frame Count for Length Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_LENGTH_ERROR_FRAMES_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RX_LENGTH_ERROR_FRAMES;

/** \brief  Register 100 - Receive Frame Count for Good Multicast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_MULTICAST_FRAMES_GOOD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RX_MULTICAST_FRAMES_GOOD;

/** \brief  Register 98 - Receive Octet Count for Good Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_OCTET_COUNT_GOOD_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_RX_OCTET_COUNT_GOOD;

/** \brief  Register 97 - Receive Octet Count for Good and Bad Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_OCTET_COUNT_GOOD_BAD_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RX_OCTET_COUNT_GOOD_BAD;

/** \brief  Register 115 - Receive Frame Count for Out of Range Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_OUT_OF_RANGE_TYPE_FRAMES_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RX_OUT_OF_RANGE_TYPE_FRAMES;

/** \brief  Register 106 - Receive Frame Count for Oversize Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_OVERSIZE_FRAMES_GOOD_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RX_OVERSIZE_FRAMES_GOOD;

/** \brief  Register 116 - Receive Frame Count for PAUSE Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_PAUSE_FRAMES_Bits B;         /**< \brief Bitfield access */
} Ifx_ETH_RX_PAUSE_FRAMES;

/** \brief  Register 120 - Receive Frame Count for Receive Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_RECEIVE_ERROR_FRAMES_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RX_RECEIVE_ERROR_FRAMES;

/** \brief  Register 103 - Receive Frame Count for Runt Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_RUNT_ERROR_FRAMES_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RX_RUNT_ERROR_FRAMES;

/** \brief  Register 105 - Receive Frame Count for Undersize Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_UNDERSIZE_FRAMES_GOOD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RX_UNDERSIZE_FRAMES_GOOD;

/** \brief  Register 113 - Receive Frame Count for Good Unicast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_UNICAST_FRAMES_GOOD_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RX_UNICAST_FRAMES_GOOD;

/** \brief  Register 118 - Receive Frame Count for Good and Bad VLAN Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_VLAN_FRAMES_GOOD_BAD_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RX_VLAN_FRAMES_GOOD_BAD;

/** \brief  Register 119 - Receive Frame Count for Watchdog Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RX_WATCHDOG_ERROR_FRAMES_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RX_WATCHDOG_ERROR_FRAMES;

/** \brief  Register 145 - Receive ICMP Error Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXICMP_ERROR_FRAMES_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_RXICMP_ERROR_FRAMES;

/** \brief  Register 161 - Receive ICMP Error Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXICMP_ERROR_OCTETS_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_RXICMP_ERROR_OCTETS;

/** \brief  Register 144 - Receive ICMP Good Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXICMP_GOOD_FRAMES_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXICMP_GOOD_FRAMES;

/** \brief  Register 160 - Receive ICMP Good Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXICMP_GOOD_OCTETS_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXICMP_GOOD_OCTETS;

/** \brief  Register 135 - Receive IPV4 Fragmented Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_FRAGMENTED_FRAMES_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_FRAGMENTED_FRAMES;

/** \brief  Register 151 - Receive IPV4 Fragmented Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_FRAGMENTED_OCTETS_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_FRAGMENTED_OCTETS;

/** \brief  Register 132 - Receive IPV4 Good Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_GOOD_FRAMES_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_GOOD_FRAMES;

/** \brief  Register 148 - Receive IPV4 Good Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_GOOD_OCTETS_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_GOOD_OCTETS;

/** \brief  Register 133 - Receive IPV4 Header Error Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_HEADER_ERROR_FRAMES_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_HEADER_ERROR_FRAMES;

/** \brief  Register 149 - Receive IPV4 Header Error Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_HEADER_ERROR_OCTETS_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_HEADER_ERROR_OCTETS;

/** \brief  Register 134 - Receive IPV4 No Payload Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_NO_PAYLOAD_FRAMES_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_NO_PAYLOAD_FRAMES;

/** \brief  Register 150 - Receive IPV4 No Payload Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_NO_PAYLOAD_OCTETS_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_NO_PAYLOAD_OCTETS;

/** \brief  Register 152 - Receive IPV4 Fragmented Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS;

/** \brief  Register 136 - Receive IPV4 UDP Checksum Disabled Frame Counter
 * Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES;

/** \brief  Register 137 - Receive IPV6 Good Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV6_GOOD_FRAMES_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXIPV6_GOOD_FRAMES;

/** \brief  Register 153 - Receive IPV6 Good Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV6_GOOD_OCTETS_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXIPV6_GOOD_OCTETS;

/** \brief  Register 138 - Receive IPV6 Header Error Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV6_HEADER_ERROR_FRAMES_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RXIPV6_HEADER_ERROR_FRAMES;

/** \brief  Register 154 - Receive IPV6 Header Error Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV6_HEADER_ERROR_OCTETS_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_RXIPV6_HEADER_ERROR_OCTETS;

/** \brief  Register 139 - Receive IPV6 No Payload Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV6_NO_PAYLOAD_FRAMES_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RXIPV6_NO_PAYLOAD_FRAMES;

/** \brief  Register 155 - Receive IPV6 No Payload Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXIPV6_NO_PAYLOAD_OCTETS_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_RXIPV6_NO_PAYLOAD_OCTETS;

/** \brief  Register 143 - Receive TCP Error Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXTCP_ERROR_FRAMES_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXTCP_ERROR_FRAMES;

/** \brief  Register 159 - Receive TCP Error Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXTCP_ERROR_OCTETS_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXTCP_ERROR_OCTETS;

/** \brief  Register 142 - Receive TCP Good Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXTCP_GOOD_FRAMES_Bits B;       /**< \brief Bitfield access */
} Ifx_ETH_RXTCP_GOOD_FRAMES;

/** \brief  Register 158 - Receive TCP Good Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXTCP_GOOD_OCTETS_Bits B;       /**< \brief Bitfield access */
} Ifx_ETH_RXTCP_GOOD_OCTETS;

/** \brief  Register 141 - Receive UDP Error Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXUDP_ERROR_FRAMES_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXUDP_ERROR_FRAMES;

/** \brief  Register 157 - Receive UDP Error Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXUDP_ERROR_OCTETS_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_RXUDP_ERROR_OCTETS;

/** \brief  Register 140 - Receive UDP Good Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXUDP_GOOD_FRAMES_Bits B;       /**< \brief Bitfield access */
} Ifx_ETH_RXUDP_GOOD_FRAMES;

/** \brief  Register 156 - Receive UDP Good Octet Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_RXUDP_GOOD_OCTETS_Bits B;       /**< \brief Bitfield access */
} Ifx_ETH_RXUDP_GOOD_OCTETS;

/** \brief  Register 5 - Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_STATUS_Bits B;                  /**< \brief Bitfield access */
} Ifx_ETH_STATUS;

/** \brief  Register 449 - Sub-Second Increment Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_SUB_SECOND_INCREMENT_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_SUB_SECOND_INCREMENT;

/** \brief  Register 457 - System Time - Higher Word Seconds Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_SYSTEM_TIME_HIGHER_WORD_SECONDS_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_SYSTEM_TIME_HIGHER_WORD_SECONDS;

/** \brief  Register 451 - System Time - Nanoseconds Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_SYSTEM_TIME_NANOSECONDS_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_SYSTEM_TIME_NANOSECONDS;

/** \brief  Register 453 - System Time - Nanoseconds Update Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE;

/** \brief  Register 450 - System Time - Seconds Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_SYSTEM_TIME_SECONDS_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_SYSTEM_TIME_SECONDS;

/** \brief  Register 452 - System Time - Seconds Update Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_SYSTEM_TIME_SECONDS_UPDATE_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_SYSTEM_TIME_SECONDS_UPDATE;

/** \brief  Register 456 - Target Time Nanoseconds Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TARGET_TIME_NANOSECONDS_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_TARGET_TIME_NANOSECONDS;

/** \brief  Register 455 - Target Time Seconds Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TARGET_TIME_SECONDS_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_TARGET_TIME_SECONDS;

/** \brief  Register 454 - Timestamp Addend Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TIMESTAMP_ADDEND_Bits B;        /**< \brief Bitfield access */
} Ifx_ETH_TIMESTAMP_ADDEND;

/** \brief  Register 448 - Timestamp Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TIMESTAMP_CONTROL_Bits B;       /**< \brief Bitfield access */
} Ifx_ETH_TIMESTAMP_CONTROL;

/** \brief  Register 458 - Timestamp Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TIMESTAMP_STATUS_Bits B;        /**< \brief Bitfield access */
} Ifx_ETH_TIMESTAMP_STATUS;

/** \brief  Register 4 - Transmit Descriptor List Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS;

/** \brief  Register 1 - Transmit Poll Demand Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TRANSMIT_POLL_DEMAND_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TRANSMIT_POLL_DEMAND;

/** \brief  Register 78 - Transmit Octet Count for Good and Bad 1024 to Maxsize
 * Bytes Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 75 - Transmit Octet Count for Good and Bad 128 to 255 Bytes
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_128TO255OCTETS_FRAMES_GOOD_BAD_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_TX_128TO255OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 76 - Transmit Octet Count for Good and Bad 256 to 511 Bytes
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_256TO511OCTETS_FRAMES_GOOD_BAD_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_TX_256TO511OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 77 - Transmit Octet Count for Good and Bad 512 to 1023
 * Bytes Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_512TO1023OCTETS_FRAMES_GOOD_BAD_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_TX_512TO1023OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 73 - Transmit Octet Count for Good and Bad 64 Byte Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_64OCTETS_FRAMES_GOOD_BAD_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_TX_64OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 74 - Transmit Octet Count for Good and Bad 65 to 127 Bytes
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_65TO127OCTETS_FRAMES_GOOD_BAD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TX_65TO127OCTETS_FRAMES_GOOD_BAD;

/** \brief  Register 71 - Transmit Frame Count for Good Broadcast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TX_BROADCAST_FRAMES_GOOD;

/** \brief  Register 81 - Transmit Frame Count for Good and Bad Broadcast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_BAD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_BAD;

/** \brief  Register 88 - Transmit Frame Count for Carrier Sense Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_CARRIER_ERROR_FRAMES_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_TX_CARRIER_ERROR_FRAMES;

/** \brief  Register 85 - Transmit Frame Count for Deferred Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_DEFERRED_FRAMES_Bits B;      /**< \brief Bitfield access */
} Ifx_ETH_TX_DEFERRED_FRAMES;

/** \brief  Register 87 - Transmit Frame Count for Excessive Collision Error
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_EXCESSIVE_COLLISION_FRAMES_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_TX_EXCESSIVE_COLLISION_FRAMES;

/** \brief  Register 91 - Transmit Frame Count for Excessive Deferral Error
 * Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_EXCESSIVE_DEFERRAL_ERROR_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_TX_EXCESSIVE_DEFERRAL_ERROR;

/** \brief  Register 90 - Transmit Frame Count for Good Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_FRAME_COUNT_GOOD_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_TX_FRAME_COUNT_GOOD;

/** \brief  Register 70 - Transmit Frame Count for Good and Bad Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_FRAME_COUNT_GOOD_BAD_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_TX_FRAME_COUNT_GOOD_BAD;

/** \brief  Register 86 - Transmit Frame Count for Late Collision Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_LATE_COLLISION_FRAMES_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TX_LATE_COLLISION_FRAMES;

/** \brief  Register 72 - Transmit Frame Count for Good Multicast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TX_MULTICAST_FRAMES_GOOD;

/** \brief  Register 80 - Transmit Frame Count for Good and Bad Multicast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_BAD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_BAD;

/** \brief  Register 84 - Transmit Frame Count for Frames Transmitted after
 * Multiple Collision */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_MULTIPLE_COLLISION_GOOD_FRAMES_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_TX_MULTIPLE_COLLISION_GOOD_FRAMES;

/** \brief  Register 89 - Transmit Octet Count for Good Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_OCTET_COUNT_GOOD_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_TX_OCTET_COUNT_GOOD;

/** \brief  Register 69 - Transmit Octet Count for Good and Bad Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_OCTET_COUNT_GOOD_BAD_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_TX_OCTET_COUNT_GOOD_BAD;

/** \brief  Register 94 - Transmit Frame Count for Good Oversize Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_OSIZE_FRAMES_GOOD_Bits B;    /**< \brief Bitfield access */
} Ifx_ETH_TX_OSIZE_FRAMES_GOOD;

/** \brief  Register 92 - Transmit Frame Count for Good PAUSE Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_PAUSE_FRAMES_Bits B;         /**< \brief Bitfield access */
} Ifx_ETH_TX_PAUSE_FRAMES;

/** \brief  Register 83 - Transmit Frame Count for Frames Transmitted after
 * Single Collision */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_SINGLE_COLLISION_GOOD_FRAMES_Bits B; /**< \brief Bitfield access */
} Ifx_ETH_TX_SINGLE_COLLISION_GOOD_FRAMES;

/** \brief  Register 82 - Transmit Frame Count for Underflow Error Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_UNDERFLOW_ERROR_FRAMES_Bits B;   /**< \brief Bitfield access */
} Ifx_ETH_TX_UNDERFLOW_ERROR_FRAMES;

/** \brief  Register 79 - Transmit Frame Count for Good and Bad Unicast Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_UNICAST_FRAMES_GOOD_BAD_Bits B;  /**< \brief Bitfield access */
} Ifx_ETH_TX_UNICAST_FRAMES_GOOD_BAD;

/** \brief  Register 93 - Transmit Frame Count for Good VLAN Frames */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_TX_VLAN_FRAMES_GOOD_Bits B;     /**< \brief Bitfield access */
} Ifx_ETH_TX_VLAN_FRAMES_GOOD;

/** \brief  Register 8 - Version Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_VERSION_Bits B;                 /**< \brief Bitfield access */
} Ifx_ETH_VERSION;

/** \brief  Register 7 - VLAN Tag Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ETH_VLAN_TAG_Bits B;                /**< \brief Bitfield access */
} Ifx_ETH_VLAN_TAG;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Eth_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  MAC Address */
typedef volatile struct _Ifx_ETH_MAC_ADDRESS
{
    Ifx_ETH_MAC_ADDRESS_HIGH HIGH;          /**< \brief 0, MAC Address High Register */
    Ifx_ETH_MAC_ADDRESS_LOW LOW;            /**< \brief 4, MAC Address Low Register */
} Ifx_ETH_MAC_ADDRESS;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Eth_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  ETH object */
typedef volatile struct _Ifx_ETH
{
    Ifx_ETH_CLC CLC;                        /**< \brief 0, Clock Control Register */
    Ifx_ETH_ID ID;                          /**< \brief 4, Module Identification Register */
    Ifx_ETH_GPCTL GPCTL;                    /**< \brief 8, Input and Output Control Register */
    Ifx_ETH_ACCEN0 ACCEN0;                  /**< \brief C, Access Enable Register 0 */
    Ifx_ETH_ACCEN1 ACCEN1;                  /**< \brief 10, Access Enable Register 1 */
    Ifx_ETH_KRST0 KRST0;                    /**< \brief 14, Kernel Reset Register 0 */
    Ifx_ETH_KRST1 KRST1;                    /**< \brief 18, Kernel Reset Register 1 */
    Ifx_ETH_KRSTCLR KRSTCLR;                /**< \brief 1C, Kernel Reset Status Clear Register */
    unsigned char reserved_20[4064];        /**< \brief 20, \internal Reserved */
    Ifx_ETH_MAC_CONFIGURATION MAC_CONFIGURATION;    /**< \brief 1000, Register 0 - MAC Configuration Register */
    Ifx_ETH_MAC_FRAME_FILTER MAC_FRAME_FILTER;  /**< \brief 1004, Register 1 - MAC Frame Filter */
    Ifx_ETH_HASH_TABLE_HIGH HASH_TABLE_HIGH;    /**< \brief 1008, Register 2 - Hash Table High Register */
    Ifx_ETH_HASH_TABLE_LOW HASH_TABLE_LOW;  /**< \brief 100C, Register 3 - Hash Table Low Register */
    Ifx_ETH_GMII_ADDRESS GMII_ADDRESS;      /**< \brief 1010, Register 4 - GMII Address Register */
    Ifx_ETH_GMII_DATA GMII_DATA;            /**< \brief 1014, Register 5 - GMII Data Register */
    Ifx_ETH_FLOW_CONTROL FLOW_CONTROL;      /**< \brief 1018, Register 6 - Flow Control Register */
    Ifx_ETH_VLAN_TAG VLAN_TAG;              /**< \brief 101C, Register 7 - VLAN Tag Register */
    Ifx_ETH_VERSION VERSION;                /**< \brief 1020, Register 8 - Version Register */
    Ifx_ETH_DEBUG DEBUG;                    /**< \brief 1024, Register 9 - Debug Register */
    Ifx_ETH_REMOTE_WAKE_UP_FRAME_FILTER REMOTE_WAKE_UP_FRAME_FILTER;    /**< \brief 1028, Register 10 - Remote Wake-Up Frame Filter Register */
    Ifx_ETH_PMT_CONTROL_STATUS PMT_CONTROL_STATUS;  /**< \brief 102C, Register 11 - PMT Control and Status Register */
    unsigned char reserved_1030[8];         /**< \brief 1030, \internal Reserved */
    Ifx_ETH_INTERRUPT_STATUS INTERRUPT_STATUS;  /**< \brief 1038, Register 14 - Interrupt Register */
    Ifx_ETH_INTERRUPT_MASK INTERRUPT_MASK;  /**< \brief 103C, Register 15 - Interrupt Mask Register */
    Ifx_ETH_MAC_ADDRESS MAC_ADDRESS_G0[16]; /**< \brief 1040, MAC Address */
    unsigned char reserved_10C0[64];        /**< \brief 10C0, \internal Reserved */
    Ifx_ETH_MMC_CONTROL MMC_CONTROL;        /**< \brief 1100, Register 64 - MMC Control Register */
    Ifx_ETH_MMC_RECEIVE_INTERRUPT MMC_RECEIVE_INTERRUPT;    /**< \brief 1104, Register 65 - MMC Receive Interrupt Register */
    Ifx_ETH_MMC_TRANSMIT_INTERRUPT MMC_TRANSMIT_INTERRUPT;  /**< \brief 1108, Register 66 - MMC Transmit Interrupt Register */
    Ifx_ETH_MMC_RECEIVE_INTERRUPT_MASK MMC_RECEIVE_INTERRUPT_MASK;  /**< \brief 110C, - */
    Ifx_ETH_MMC_TRANSMIT_INTERRUPT_MASK MMC_TRANSMIT_INTERRUPT_MASK;    /**< \brief 1110, Register 68 - MMC Transmit Interrupt Mask Register */
    Ifx_ETH_TX_OCTET_COUNT_GOOD_BAD TX_OCTET_COUNT_GOOD_BAD;    /**< \brief 1114, Register 69 - Transmit Octet Count for Good and Bad Frames */
    Ifx_ETH_TX_FRAME_COUNT_GOOD_BAD TX_FRAME_COUNT_GOOD_BAD;    /**< \brief 1118, Register 70 - Transmit Frame Count for Good and Bad Frames */
    Ifx_ETH_TX_BROADCAST_FRAMES_GOOD TX_BROADCAST_FRAMES_GOOD;  /**< \brief 111C, Register 71 - Transmit Frame Count for Good Broadcast Frames */
    Ifx_ETH_TX_MULTICAST_FRAMES_GOOD TX_MULTICAST_FRAMES_GOOD;  /**< \brief 1120, Register 72 - Transmit Frame Count for Good Multicast Frames */
    Ifx_ETH_TX_64OCTETS_FRAMES_GOOD_BAD TX_64OCTETS_FRAMES_GOOD_BAD;    /**< \brief 1124, Register 73 - Transmit Octet Count for Good and Bad 64 Byte Frames */
    Ifx_ETH_TX_65TO127OCTETS_FRAMES_GOOD_BAD TX_65TO127OCTETS_FRAMES_GOOD_BAD;  /**< \brief 1128, Register 74 - Transmit Octet Count for Good and Bad 65 to 127 Bytes Frames */
    Ifx_ETH_TX_128TO255OCTETS_FRAMES_GOOD_BAD TX_128TO255OCTETS_FRAMES_GOOD_BAD;    /**< \brief 112C, Register 75 - Transmit Octet Count for Good and Bad 128 to 255 Bytes Frames */
    Ifx_ETH_TX_256TO511OCTETS_FRAMES_GOOD_BAD TX_256TO511OCTETS_FRAMES_GOOD_BAD;    /**< \brief 1130, Register 76 - Transmit Octet Count for Good and Bad 256 to 511 Bytes Frames */
    Ifx_ETH_TX_512TO1023OCTETS_FRAMES_GOOD_BAD TX_512TO1023OCTETS_FRAMES_GOOD_BAD;  /**< \brief 1134, Register 77 - Transmit Octet Count for Good and Bad 512 to 1023 Bytes Frames */
    Ifx_ETH_TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD TX_1024TOMAXOCTETS_FRAMES_GOOD_BAD;  /**< \brief 1138, Register 78 - Transmit Octet Count for Good and Bad 1024 to Maxsize Bytes Frames */
    Ifx_ETH_TX_UNICAST_FRAMES_GOOD_BAD TX_UNICAST_FRAMES_GOOD_BAD;  /**< \brief 113C, Register 79 - Transmit Frame Count for Good and Bad Unicast Frames */
    Ifx_ETH_TX_MULTICAST_FRAMES_GOOD_BAD TX_MULTICAST_FRAMES_GOOD_BAD;  /**< \brief 1140, Register 80 - Transmit Frame Count for Good and Bad Multicast Frames */
    Ifx_ETH_TX_BROADCAST_FRAMES_GOOD_BAD TX_BROADCAST_FRAMES_GOOD_BAD;  /**< \brief 1144, Register 81 - Transmit Frame Count for Good and Bad Broadcast Frames */
    Ifx_ETH_TX_UNDERFLOW_ERROR_FRAMES TX_UNDERFLOW_ERROR_FRAMES;    /**< \brief 1148, Register 82 - Transmit Frame Count for Underflow Error Frames */
    Ifx_ETH_TX_SINGLE_COLLISION_GOOD_FRAMES TX_SINGLE_COLLISION_GOOD_FRAMES;    /**< \brief 114C, Register 83 - Transmit Frame Count for Frames Transmitted after Single Collision */
    Ifx_ETH_TX_MULTIPLE_COLLISION_GOOD_FRAMES TX_MULTIPLE_COLLISION_GOOD_FRAMES;    /**< \brief 1150, Register 84 - Transmit Frame Count for Frames Transmitted after Multiple Collision */
    Ifx_ETH_TX_DEFERRED_FRAMES TX_DEFERRED_FRAMES;  /**< \brief 1154, Register 85 - Transmit Frame Count for Deferred Frames */
    Ifx_ETH_TX_LATE_COLLISION_FRAMES TX_LATE_COLLISION_FRAMES;  /**< \brief 1158, Register 86 - Transmit Frame Count for Late Collision Error Frames */
    Ifx_ETH_TX_EXCESSIVE_COLLISION_FRAMES TX_EXCESSIVE_COLLISION_FRAMES;    /**< \brief 115C, Register 87 - Transmit Frame Count for Excessive Collision Error Frames */
    Ifx_ETH_TX_CARRIER_ERROR_FRAMES TX_CARRIER_ERROR_FRAMES;    /**< \brief 1160, Register 88 - Transmit Frame Count for Carrier Sense Error Frames */
    Ifx_ETH_TX_OCTET_COUNT_GOOD TX_OCTET_COUNT_GOOD;    /**< \brief 1164, Register 89 - Transmit Octet Count for Good Frames */
    Ifx_ETH_TX_FRAME_COUNT_GOOD TX_FRAME_COUNT_GOOD;    /**< \brief 1168, Register 90 - Transmit Frame Count for Good Frames */
    Ifx_ETH_TX_EXCESSIVE_DEFERRAL_ERROR TX_EXCESSIVE_DEFERRAL_ERROR;    /**< \brief 116C, Register 91 - Transmit Frame Count for Excessive Deferral Error Frames */
    Ifx_ETH_TX_PAUSE_FRAMES TX_PAUSE_FRAMES;    /**< \brief 1170, Register 92 - Transmit Frame Count for Good PAUSE Frames */
    Ifx_ETH_TX_VLAN_FRAMES_GOOD TX_VLAN_FRAMES_GOOD;    /**< \brief 1174, Register 93 - Transmit Frame Count for Good VLAN Frames */
    Ifx_ETH_TX_OSIZE_FRAMES_GOOD TX_OSIZE_FRAMES_GOOD;  /**< \brief 1178, Register 94 - Transmit Frame Count for Good Oversize Frames */
    unsigned char reserved_117C[4];         /**< \brief 117C, \internal Reserved */
    Ifx_ETH_RX_FRAMES_COUNT_GOOD_BAD RX_FRAMES_COUNT_GOOD_BAD;  /**< \brief 1180, Register 96 - Receive Frame Count for Good and Bad Frames */
    Ifx_ETH_RX_OCTET_COUNT_GOOD_BAD RX_OCTET_COUNT_GOOD_BAD;    /**< \brief 1184, Register 97 - Receive Octet Count for Good and Bad Frames */
    Ifx_ETH_RX_OCTET_COUNT_GOOD RX_OCTET_COUNT_GOOD;    /**< \brief 1188, Register 98 - Receive Octet Count for Good Frames */
    Ifx_ETH_RX_BROADCAST_FRAMES_GOOD RX_BROADCAST_FRAMES_GOOD;  /**< \brief 118C, Register 99 - Receive Frame Count for Good Broadcast Frames */
    Ifx_ETH_RX_MULTICAST_FRAMES_GOOD RX_MULTICAST_FRAMES_GOOD;  /**< \brief 1190, Register 100 - Receive Frame Count for Good Multicast Frames */
    Ifx_ETH_RX_CRC_ERROR_FRAMES RX_CRC_ERROR_FRAMES;    /**< \brief 1194, Register 101 - Receive Frame Count for CRC Error Frames */
    Ifx_ETH_RX_ALIGNMENT_ERROR_FRAMES RX_ALIGNMENT_ERROR_FRAMES;    /**< \brief 1198, Register 102 - Receive Frame Count for Alignment Error Frames */
    Ifx_ETH_RX_RUNT_ERROR_FRAMES RX_RUNT_ERROR_FRAMES;  /**< \brief 119C, Register 103 - Receive Frame Count for Runt Error Frames */
    Ifx_ETH_RX_JABBER_ERROR_FRAMES RX_JABBER_ERROR_FRAMES;  /**< \brief 11A0, Register 104 - Receive Frame Count for Jabber Error Frames */
    Ifx_ETH_RX_UNDERSIZE_FRAMES_GOOD RX_UNDERSIZE_FRAMES_GOOD;  /**< \brief 11A4, Register 105 - Receive Frame Count for Undersize Frames */
    Ifx_ETH_RX_OVERSIZE_FRAMES_GOOD RX_OVERSIZE_FRAMES_GOOD;    /**< \brief 11A8, Register 106 - Receive Frame Count for Oversize Frames */
    Ifx_ETH_RX_64OCTETS_FRAMES_GOOD_BAD RX_64OCTETS_FRAMES_GOOD_BAD;    /**< \brief 11AC, Register 107 - Receive Frame Count for Good and Bad 64 Byte Frames */
    Ifx_ETH_RX_65TO127OCTETS_FRAMES_GOOD_BAD RX_65TO127OCTETS_FRAMES_GOOD_BAD;  /**< \brief 11B0, Register 108 - Receive Frame Count for Good and Bad 65 to 127 Bytes Frames */
    Ifx_ETH_RX_128TO255OCTETS_FRAMES_GOOD_BAD RX_128TO255OCTETS_FRAMES_GOOD_BAD;    /**< \brief 11B4, Register 109 - Receive Frame Count for Good and Bad 128 to 255 Bytes Frames */
    Ifx_ETH_RX_256TO511OCTETS_FRAMES_GOOD_BAD RX_256TO511OCTETS_FRAMES_GOOD_BAD;    /**< \brief 11B8, Register 110 - Receive Frame Count for Good and Bad 256 to 511 Bytes Frames */
    Ifx_ETH_RX_512TO1023OCTETS_FRAMES_GOOD_BAD RX_512TO1023OCTETS_FRAMES_GOOD_BAD;  /**< \brief 11BC, Register 111 - Receive Frame Count for Good and Bad 512 to 1,023 Bytes Frames */
    Ifx_ETH_RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD RX_1024TOMAXOCTETS_FRAMES_GOOD_BAD;  /**< \brief 11C0, Register 112 - Receive Frame Count for Good and Bad 1,024 to Maxsize Bytes Frames */
    Ifx_ETH_RX_UNICAST_FRAMES_GOOD RX_UNICAST_FRAMES_GOOD;  /**< \brief 11C4, Register 113 - Receive Frame Count for Good Unicast Frames */
    Ifx_ETH_RX_LENGTH_ERROR_FRAMES RX_LENGTH_ERROR_FRAMES;  /**< \brief 11C8, Register 114 - Receive Frame Count for Length Error Frames */
    Ifx_ETH_RX_OUT_OF_RANGE_TYPE_FRAMES RX_OUT_OF_RANGE_TYPE_FRAMES;    /**< \brief 11CC, Register 115 - Receive Frame Count for Out of Range Frames */
    Ifx_ETH_RX_PAUSE_FRAMES RX_PAUSE_FRAMES;    /**< \brief 11D0, Register 116 - Receive Frame Count for PAUSE Frames */
    Ifx_ETH_RX_FIFO_OVERFLOW_FRAMES RX_FIFO_OVERFLOW_FRAMES;    /**< \brief 11D4, Register 117 - Receive Frame Count for FIFO Overflow Frames */
    Ifx_ETH_RX_VLAN_FRAMES_GOOD_BAD RX_VLAN_FRAMES_GOOD_BAD;    /**< \brief 11D8, Register 118 - Receive Frame Count for Good and Bad VLAN Frames */
    Ifx_ETH_RX_WATCHDOG_ERROR_FRAMES RX_WATCHDOG_ERROR_FRAMES;  /**< \brief 11DC, Register 119 - Receive Frame Count for Watchdog Error Frames */
    Ifx_ETH_RX_RECEIVE_ERROR_FRAMES RX_RECEIVE_ERROR_FRAMES;    /**< \brief 11E0, Register 120 - Receive Frame Count for Receive Error Frames */
    Ifx_ETH_RX_CONTROL_FRAMES_GOOD RX_CONTROL_FRAMES_GOOD;  /**< \brief 11E4, Register 121 - Receive Frame Count for Good Control Frames Frames */
    unsigned char reserved_11E8[24];        /**< \brief 11E8, \internal Reserved */
    Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT_MASK MMC_IPC_RECEIVE_INTERRUPT_MASK;  /**< \brief 1200, Register 128 - MMC Receive Checksum Offload Interrupt Mask Register */
    unsigned char reserved_1204[4];         /**< \brief 1204, \internal Reserved */
    Ifx_ETH_MMC_IPC_RECEIVE_INTERRUPT MMC_IPC_RECEIVE_INTERRUPT;    /**< \brief 1208, Register 130 - MMC Receive Checksum Offload Interrupt Register */
    unsigned char reserved_120C[4];         /**< \brief 120C, \internal Reserved */
    Ifx_ETH_RXIPV4_GOOD_FRAMES RXIPV4_GOOD_FRAMES;  /**< \brief 1210, Register 132 - Receive IPV4 Good Frame Counter Register */
    Ifx_ETH_RXIPV4_HEADER_ERROR_FRAMES RXIPV4_HEADER_ERROR_FRAMES;  /**< \brief 1214, Register 133 - Receive IPV4 Header Error Frame Counter Register */
    Ifx_ETH_RXIPV4_NO_PAYLOAD_FRAMES RXIPV4_NO_PAYLOAD_FRAMES;  /**< \brief 1218, Register 134 - Receive IPV4 No Payload Frame Counter Register */
    Ifx_ETH_RXIPV4_FRAGMENTED_FRAMES RXIPV4_FRAGMENTED_FRAMES;  /**< \brief 121C, Register 135 - Receive IPV4 Fragmented Frame Counter Register */
    Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES RXIPV4_UDP_CHECKSUM_DISABLED_FRAMES;    /**< \brief 1220, Register 136 - Receive IPV4 UDP Checksum Disabled Frame Counter Register */
    Ifx_ETH_RXIPV6_GOOD_FRAMES RXIPV6_GOOD_FRAMES;  /**< \brief 1224, Register 137 - Receive IPV6 Good Frame Counter Register */
    Ifx_ETH_RXIPV6_HEADER_ERROR_FRAMES RXIPV6_HEADER_ERROR_FRAMES;  /**< \brief 1228, Register 138 - Receive IPV6 Header Error Frame Counter Register */
    Ifx_ETH_RXIPV6_NO_PAYLOAD_FRAMES RXIPV6_NO_PAYLOAD_FRAMES;  /**< \brief 122C, Register 139 - Receive IPV6 No Payload Frame Counter Register */
    Ifx_ETH_RXUDP_GOOD_FRAMES RXUDP_GOOD_FRAMES;    /**< \brief 1230, Register 140 - Receive UDP Good Frame Counter Register */
    Ifx_ETH_RXUDP_ERROR_FRAMES RXUDP_ERROR_FRAMES;  /**< \brief 1234, Register 141 - Receive UDP Error Frame Counter Register */
    Ifx_ETH_RXTCP_GOOD_FRAMES RXTCP_GOOD_FRAMES;    /**< \brief 1238, Register 142 - Receive TCP Good Frame Counter Register */
    Ifx_ETH_RXTCP_ERROR_FRAMES RXTCP_ERROR_FRAMES;  /**< \brief 123C, Register 143 - Receive TCP Error Frame Counter Register */
    Ifx_ETH_RXICMP_GOOD_FRAMES RXICMP_GOOD_FRAMES;  /**< \brief 1240, Register 144 - Receive ICMP Good Frame Counter Register */
    Ifx_ETH_RXICMP_ERROR_FRAMES RXICMP_ERROR_FRAMES;    /**< \brief 1244, Register 145 - Receive ICMP Error Frame Counter Register */
    unsigned char reserved_1248[8];         /**< \brief 1248, \internal Reserved */
    Ifx_ETH_RXIPV4_GOOD_OCTETS RXIPV4_GOOD_OCTETS;  /**< \brief 1250, Register 148 - Receive IPV4 Good Octet Counter Register */
    Ifx_ETH_RXIPV4_HEADER_ERROR_OCTETS RXIPV4_HEADER_ERROR_OCTETS;  /**< \brief 1254, Register 149 - Receive IPV4 Header Error Octet Counter Register */
    Ifx_ETH_RXIPV4_NO_PAYLOAD_OCTETS RXIPV4_NO_PAYLOAD_OCTETS;  /**< \brief 1258, Register 150 - Receive IPV4 No Payload Octet Counter Register */
    Ifx_ETH_RXIPV4_FRAGMENTED_OCTETS RXIPV4_FRAGMENTED_OCTETS;  /**< \brief 125C, Register 151 - Receive IPV4 Fragmented Octet Counter Register */
    Ifx_ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS;  /**< \brief 1260, Register 152 - Receive IPV4 Fragmented Octet Counter Register */
    Ifx_ETH_RXIPV6_GOOD_OCTETS RXIPV6_GOOD_OCTETS;  /**< \brief 1264, Register 153 - Receive IPV6 Good Octet Counter Register */
    Ifx_ETH_RXIPV6_HEADER_ERROR_OCTETS RXIPV6_HEADER_ERROR_OCTETS;  /**< \brief 1268, Register 154 - Receive IPV6 Header Error Octet Counter Register */
    Ifx_ETH_RXIPV6_NO_PAYLOAD_OCTETS RXIPV6_NO_PAYLOAD_OCTETS;  /**< \brief 126C, Register 155 - Receive IPV6 No Payload Octet Counter Register */
    Ifx_ETH_RXUDP_GOOD_OCTETS RXUDP_GOOD_OCTETS;    /**< \brief 1270, Register 156 - Receive UDP Good Octet Counter Register */
    Ifx_ETH_RXUDP_ERROR_OCTETS RXUDP_ERROR_OCTETS;  /**< \brief 1274, Register 157 - Receive UDP Error Octet Counter Register */
    Ifx_ETH_RXTCP_GOOD_OCTETS RXTCP_GOOD_OCTETS;    /**< \brief 1278, Register 158 - Receive TCP Good Octet Counter Register */
    Ifx_ETH_RXTCP_ERROR_OCTETS RXTCP_ERROR_OCTETS;  /**< \brief 127C, Register 159 - Receive TCP Error Octet Counter Register */
    Ifx_ETH_RXICMP_GOOD_OCTETS RXICMP_GOOD_OCTETS;  /**< \brief 1280, Register 160 - Receive ICMP Good Octet Counter Register */
    Ifx_ETH_RXICMP_ERROR_OCTETS RXICMP_ERROR_OCTETS;    /**< \brief 1284, Register 161 - Receive ICMP Error Octet Counter Register */
    unsigned char reserved_1288[1144];      /**< \brief 1288, \internal Reserved */
    Ifx_ETH_TIMESTAMP_CONTROL TIMESTAMP_CONTROL;    /**< \brief 1700, Register 448 - Timestamp Control Register */
    Ifx_ETH_SUB_SECOND_INCREMENT SUB_SECOND_INCREMENT;  /**< \brief 1704, Register 449 - Sub-Second Increment Register */
    Ifx_ETH_SYSTEM_TIME_SECONDS SYSTEM_TIME_SECONDS;    /**< \brief 1708, Register 450 - System Time - Seconds Register */
    Ifx_ETH_SYSTEM_TIME_NANOSECONDS SYSTEM_TIME_NANOSECONDS;    /**< \brief 170C, Register 451 - System Time - Nanoseconds Register */
    Ifx_ETH_SYSTEM_TIME_SECONDS_UPDATE SYSTEM_TIME_SECONDS_UPDATE;  /**< \brief 1710, Register 452 - System Time - Seconds Update Register */
    Ifx_ETH_SYSTEM_TIME_NANOSECONDS_UPDATE SYSTEM_TIME_NANOSECONDS_UPDATE;  /**< \brief 1714, Register 453 - System Time - Nanoseconds Update Register */
    Ifx_ETH_TIMESTAMP_ADDEND TIMESTAMP_ADDEND;  /**< \brief 1718, Register 454 - Timestamp Addend Register */
    Ifx_ETH_TARGET_TIME_SECONDS TARGET_TIME_SECONDS;    /**< \brief 171C, Register 455 - Target Time Seconds Register */
    Ifx_ETH_TARGET_TIME_NANOSECONDS TARGET_TIME_NANOSECONDS;    /**< \brief 1720, Register 456 - Target Time Nanoseconds Register */
    Ifx_ETH_SYSTEM_TIME_HIGHER_WORD_SECONDS SYSTEM_TIME_HIGHER_WORD_SECONDS;    /**< \brief 1724, Register 457 - System Time - Higher Word Seconds Register */
    Ifx_ETH_TIMESTAMP_STATUS TIMESTAMP_STATUS;  /**< \brief 1728, Register 458 - Timestamp Status Register */
    Ifx_ETH_PPS_CONTROL PPS_CONTROL;        /**< \brief 172C, Register 459 - PPS Control Register */
    unsigned char reserved_1730[208];       /**< \brief 1730, \internal Reserved */
    Ifx_ETH_MAC_ADDRESS MAC_ADDRESS_G1[16]; /**< \brief 1800, MAC Address \note Array index shifted by 16. Example: defined register MAC_ADDRESS_G1[0]/MAC_ADDRESS_G10 corresponds to user manual MAC_ADDRESS_G116, ... */
    unsigned char reserved_1880[1920];      /**< \brief 1880, \internal Reserved */
    Ifx_ETH_BUS_MODE BUS_MODE;              /**< \brief 2000, Register 0 - Bus Mode Register */
    Ifx_ETH_TRANSMIT_POLL_DEMAND TRANSMIT_POLL_DEMAND;  /**< \brief 2004, Register 1 - Transmit Poll Demand Register */
    Ifx_ETH_RECEIVE_POLL_DEMAND RECEIVE_POLL_DEMAND;    /**< \brief 2008, Register 2 - Receive Poll Demand Register */
    Ifx_ETH_RECEIVE_DESCRIPTOR_LIST_ADDRESS RECEIVE_DESCRIPTOR_LIST_ADDRESS;    /**< \brief 200C, Register 3 - Receive Descriptor List Address Register */
    Ifx_ETH_TRANSMIT_DESCRIPTOR_LIST_ADDRESS TRANSMIT_DESCRIPTOR_LIST_ADDRESS;  /**< \brief 2010, Register 4 - Transmit Descriptor List Address Register */
    Ifx_ETH_STATUS STATUS;                  /**< \brief 2014, Register 5 - Status Register */
    Ifx_ETH_OPERATION_MODE OPERATION_MODE;  /**< \brief 2018, Register 6 - Operation Mode Register */
    Ifx_ETH_INTERRUPT_ENABLE INTERRUPT_ENABLE;  /**< \brief 201C, Register 7 - Interrupt Enable Register */
    Ifx_ETH_MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER MISSED_FRAME_AND_BUFFER_OVERFLOW_COUNTER;  /**< \brief 2020, Register 8 - Missed Frame and Buffer Overflow Counter Register */
    Ifx_ETH_RECEIVE_INTERRUPT_WATCHDOG_TIMER RECEIVE_INTERRUPT_WATCHDOG_TIMER;  /**< \brief 2024, Register 9 - Receive Interrupt Watchdog Timer Register */
    unsigned char reserved_2028[4];         /**< \brief 2028, \internal Reserved */
    Ifx_ETH_AHB_OR_AXI_STATUS AHB_OR_AXI_STATUS;    /**< \brief 202C, Register 11 - AHB or AXI Status Register */
    unsigned char reserved_2030[24];        /**< \brief 2030, \internal Reserved */
    Ifx_ETH_CURRENT_HOST_TRANSMIT_DESCRIPTOR CURRENT_HOST_TRANSMIT_DESCRIPTOR;  /**< \brief 2048, Register 18 - Current Host Transmit Descriptor Register */
    Ifx_ETH_CURRENT_HOST_RECEIVE_DESCRIPTOR CURRENT_HOST_RECEIVE_DESCRIPTOR;    /**< \brief 204C, Register 19 - Current Host Receive Descriptor Register */
    Ifx_ETH_CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS CURRENT_HOST_TRANSMIT_BUFFER_ADDRESS;  /**< \brief 2050, Register 20 - Current Host Transmit Buffer Address Register */
    Ifx_ETH_CURRENT_HOST_RECEIVE_BUFFER_ADDRESS CURRENT_HOST_RECEIVE_BUFFER_ADDRESS;    /**< \brief 2054, Register 21 - Current Host Receive Buffer Address Register */
    Ifx_ETH_HW_FEATURE HW_FEATURE;          /**< \brief 2058, Register 22 - HW Feature Register */
    unsigned char reserved_205C[164];       /**< \brief 205C, \internal Reserved */
} Ifx_ETH;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXETH_REGDEF_H */
