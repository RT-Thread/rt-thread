/**
  ******************************************************************************
  * @brief   ETH header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_ETH_H
#define __GD32F10X_ETH_H
#define IF_USE_EXTERNPHY_LIB        0

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"
#if (1 == IF_USE_EXTERNPHY_LIB)
#include "phy.h"
#endif

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup ETH
  * @{
  */

/** @defgroup ETH_Exported_Types
  * @{
  */

/**
  * @brief  ETH MAC Initial Parameters
  */
typedef struct {
    /**
      * @brief / * MAC
      */
    uint32_t             ETH_MAC_AutoNegotiation;             /*!< Enable or disable external PHY's AutoNegotiation function
                                                                 detailed in @ref ETH_AutoNegotiation */

    uint32_t             ETH_MAC_Watchdog;                    /*!< Enable or disable the Watchdog timer
                                                                 detailed in @ref ETH_watchdog */

    uint32_t             ETH_MAC_Jabber;                      /*!< Enable or disable Jabber timer
                                                                 detailed in @ref ETH_Jabber */

    uint32_t             ETH_MAC_InterFrameGap;               /*!< Set the gap of two frames when transmission
                                                                 detailed in @ref ETH_Inter_Frame_Gap */

    uint32_t             ETH_MAC_CarrierSense;                /*!< Enable or disable the Carrier Sense
                                                                 detailed in @ref ETH_Carrier_Sense */

    uint32_t             ETH_MAC_Speed;                       /*!< Set the Ethernet speed, detailed in @ref ETH_Speed */


    uint32_t             ETH_MAC_ReceiveOwn;                  /*!< Enable or disable the ReceiveOwn mode
                                                                 detailed in @ref ETH_Receive_Own */

    uint32_t             ETH_MAC_LoopbackMode;                /*!< Enable or disable the MAC Loopback mode
                                                                 detailed in @ref ETH_Loop_Back_Mode */

    uint32_t             ETH_MAC_Mode;                        /*!< Set the MAC duplex mode, detailed in @ref ETH_Duplex_Mode */

    uint32_t             ETH_MAC_ChecksumOffload;             /*!< Enable or disable the IPv4(TCP/UDP/ICMP headers) checksum checking when reception
                                                                 detailed in @ref ETH_Checksum_Offload */

    uint32_t             ETH_MAC_RetryTransmission;           /*!< Enable or disable the MAC attempt retries transmission in Half-Duplex mode when a colision occurs
                                                                 detailed in @ref ETH_Retry_Transmission */

    uint32_t             ETH_MAC_AutomaticPadCRCDrop;         /*!< Enable or disable the Automatic Pad/CRC Drop
                                                                 detailed in @ref ETH_Automatic_Pad_CRC_Drop */

    uint32_t             ETH_MAC_BackOffLimit;                /*!< Set the BackOff limit value, detailed in @ref ETH_Back_Off_Limit */

    uint32_t             ETH_MAC_DeferralCheck;               /*!< Enable or disable the deferral check function only in Half-Duplex mode
                                                                 detailed in @ref ETH_Deferral_Check */

    uint32_t             ETH_MAC_FilterDisable;               /*!< Enable or disable the MAC filter, detailed in @ref ETH_Filter_Disable */

    uint32_t             ETH_MAC_SourceAddrFilter;            /*!< Set the SA Filter mode, detailed in @ref ETH_Source_Addr_Filter */

    uint32_t             ETH_MAC_PassControlFrames;           /*!< Set the mode of the control frames (including unicast and multicast PAUSE frames)
                                                                 detailed in @ref ETH_Pass_Control_Frames */

    uint32_t             ETH_MAC_BroadcastFramesReception;    /*!< Enable or disable the reception of Broadcast Frames
                                                                 detailed in @ref ETH_Broadcast_Frames_Reception */

    uint32_t             ETH_MAC_DestinationAddrFilter;       /*!< Set the DA filter mode, detailed in @ref ETH_Destination_Addr_Filter */

    uint32_t             ETH_MAC_PromiscuousMode;             /*!< Enable or disable the Promiscuous Mode
                                                                 detailed in @ref ETH_Promiscuous_Mode */

    uint32_t             ETH_MAC_MulticastFramesFilter;       /*!< Set the Multicast Frames filter mode
                                                                 detailed in @ref ETH_Multicast_Frames_Filter */

    uint32_t             ETH_MAC_UnicastFramesFilter;         /*!< Set the Unicast Frames filter mode
                                                                 detailed in @ref ETH_Unicast_Frames_Filter */

    uint32_t             ETH_MAC_HashListHigh;                /*!< Hash list higher 32 bits */

    uint32_t             ETH_MAC_HashListLow;                 /*!< Hash list lower 32 bits */

    uint32_t             ETH_MAC_PauseTime;                   /*!< Set the Pause Time field value in the transmit control frame */

    uint32_t             ETH_MAC_ZeroQuantaPause;             /*!< Enable or disable the automatic generation of Zero-Quanta Pause Control frames
                                                                 detailed in @ref ETH_Zero_Quanta_Pause */

    uint32_t             ETH_MAC_PauseLowThreshold;           /*!< Set the threshold of the PAUSE to be checked for
                                                                 automatic retransmission of PAUSE Frame
                                                                 detailed in @ref ETH_Pause_Low_Threshold */

    uint32_t             ETH_MAC_FlowControlDeactiveThreshold;/*!< Set the threshold of the deactive flow control
                                                                 detailed in @ref ETH_RFD_Threshold  */

    uint32_t             ETH_MAC_FlowControlActiveThreshold;  /*!< Set the threshold of the active flow control
                                                                 detailed in @ref ETH_RFA_Threshold  */

    uint32_t             ETH_MAC_UnicastPauseFrameDetect;     /*!< Enable or disable the unicast Pause frames detection
                                                                 detailed in @ref ETH_Unicast_Pause_Frame_Detect */

    uint32_t             ETH_MAC_ReceiveFlowControl;          /*!< Enable or disable the MAC to received Pause frame
                                                                 detailed in @ref ETH_Receive_Flow_Control */

    uint32_t             ETH_MAC_TransmitFlowControl;         /*!< Enable or disable the MAC to transmit Pause frames in Full-Duplex mode
                                                                 or back-pressure operation in Half-Duplex mode
                                                                 detailed in @ref ETH_Transmit_Flow_Control */

    uint32_t             ETH_MAC_VLANTagComparison;           /*!< Set VLAN tag comparison and filtering mode
                                                                 detailed in @ref ETH_VLAN_Tag_Comparison */

    uint32_t             ETH_MAC_VLANTagIdentifier;           /*!< Set VLAN tag identifier for receive frames */

    /**
      * @brief / * DMA
      */

    uint32_t             ETH_DMA_DropTCPIPChecksumErrorFrame; /*!< Enable or disable the TCP/IP Checksum Error Frames drop
                                                                 detailed in @ref ETH_Drop_TCP_IP_Checksum_Error_Frame */

    uint32_t             ETH_DMA_ReceiveStoreForward;         /*!< Set the Rx FIFO operation mode
                                                                 detailed in @ref ETH_Receive_Store_Forward */

    uint32_t             ETH_DMA_FlushReceivedFrame;          /*!< Enable or disable the flushing Receive FIFO
                                                                 detailed in @ref ETH_Flush_Received_Frame */

    uint32_t             ETH_DMA_TransmitStoreForward;        /*!< Enable or disable Tx FIFO operation mode
                                                                 detailed in @ref ETH_Transmit_Store_Forward */

    uint32_t             ETH_DMA_TransmitThresholdControl;    /*!< Enable or disable the Transmit Threshold Control and set the level
                                                                 detailed in @ref ETH_Transmit_Threshold_Control */

    uint32_t             ETH_DMA_ForwardErrorFrames;          /*!< Enable or disable receive the erroneous frames to the DMA
                                                                 detailed in @ref ETH_Forward_Error_Frames */

    uint32_t             ETH_DMA_ForwardUndersizedGoodFrames; /*!< Enable or disable receive the Undersized frames with no Error
                                                                 and length less than 64 bytes including pad-bytes and CRC to the DMA
                                                                 detailed in @ref ETH_Forward_Undersized_Good_Frames */

    uint32_t             ETH_DMA_ReceiveThresholdControl;     /*!< Enable or disable the Receive Threshold Control and set the level
                                                                 detailed in @ref ETH_Receive_Threshold_Control */

    uint32_t             ETH_DMA_SecondFrameOperate;          /*!< Enable or disable the Operate on second frame mode
                                                                 detailed in @ref ETH_Second_Frame_Operate */

    uint32_t             ETH_DMA_AddressAligned;              /*!< Enable or disable the Address Aligned
                                                                 detailed in @ref ETH_Address_Aligned */

    uint32_t             ETH_DMA_FixedBurst;                  /*!< Enable or disable the AHB Master interface fixed burst transfers
                                                                 detailed in @ref ETH_Fixed_Burst */

    uint32_t             ETH_DMA_RxDMABurstLength;            /*!< Set the maximum number of beats to be transferred in one Rx DMA transaction
                                                                 detailed in @ref ETH_Rx_DMA_Burst_Length */

    uint32_t             ETH_DMA_TxDMABurstLength;            /*!< Set the maximum number of beats to be transferred in one Tx DMA transaction
                                                                 detailed in @ref ETH_Tx_DMA_Burst_Length */

    uint32_t             ETH_DMA_DescriptorSkipLength;        /*!< Set the number of word to skip between two descriptors only in Ring mode */

    uint32_t             ETH_DMA_Arbitration;                 /*!< Set the DMA Tx/Rx priority ratio
                                                                 detailed in @ref ETH_DMA_Arbitration */
} ETH_InitPara;

/**
  * @brief  ETH DMA Desciptors structure def
  */
typedef struct {
    uint32_t   Status;                /*!< Status */
    uint32_t   ControlBufferSize;     /*!< Control and Buffer1, Buffer2 lengths */
    uint32_t   Buffer1Addr;           /*!< Buffer1 address pointer */
    uint32_t   Buffer2NextDescAddr;   /*!< Buffer2 or next descriptor address pointer */
} ETH_DMADESCTypeDef;

/**
  * @}
  */

/** @defgroup ETH_Exported_Constants
  * @{
  */

/** @defgroup ETH_delay_Def
  * @{
  */
/* #define USE_Delay */

#ifdef USE_Delay
#define _eth_delay_    Delay     /*!< User can provide more timing precise _eth_delay_ function */
#else
#define _eth_delay_    ETH_Delay /*!< Default _eth_delay_ function with less precise timing */
#endif

/**
  * @}
  */

/** @defgroup ETH_Buffer_Def
  * @{
  */
#define ETH_MAX_FRAME_SIZE                               1520    /*!< FRAME_HEADER + FRAME_EXTRA + MAX_FRAME_PAYLOAD + FRAME_CRC */
#define ETH_HEADER                                       14      /*!< 6 byte DA, 6 byte SA, 2 byte length/type */
#define ETH_CRC                                          4       /*!< 4 byte CRC */
#define ETH_EXTRA                                        2       /*!< Extra bytes in some cases */
#define VLAN_TAG                                         4       /*!< optional 802.1q VLAN Tag */
#define MIN_ETH_DATALENGTH                               46      /*!< Minimum Eth payload byte */
#define MAX_ETH_DATALENGTH                               1500    /*!< Maximum Eth payload byte */
#define JUMBO_FRAME_DATALENGTH                           9000    /*!< Jumbo frame payload byte */

/**
   DMA Tx Desciptor
  -----------------------------------------------------------------------------------------------
  TDES0 | BUSY(31) | CTRL[30:26] | Reserved[25:24] | CTRL[23:20] | Reserved[19:17] | Status[16:0] |
  -----------------------------------------------------------------------------------------------
  TDES1 | Reserved[31:29] | Buffer2 ByteCount[28:16] | Reserved[15:13] | Buffer1 ByteCount[12:0] |
  -----------------------------------------------------------------------------------------------
  TDES2 |                         Buffer1 Address [31:0]                                         |
  -----------------------------------------------------------------------------------------------
  TDES3 |                   Buffer2 Address [31:0] / Next Desciptor Address [31:0]               |
  -----------------------------------------------------------------------------------------------
*/

/**
  * @brief  DMA Tx descriptor TDES0 register Bit def
  */
#define ETH_DMATXDESC_BUSY                              ((uint32_t)0x80000000)  /*!< DMA or CPU control descriptor*/
#define ETH_DMATXDESC_INTC                              ((uint32_t)0x40000000)  /*!< Interrupt on Completion */
#define ETH_DMATXDESC_LSG                               ((uint32_t)0x20000000)  /*!< contains the last segment of the frame */
#define ETH_DMATXDESC_FSG                               ((uint32_t)0x10000000)  /*!< contains the first segment of the frame */
#define ETH_DMATXDESC_DCRC                              ((uint32_t)0x08000000)  /*!< Disable CRC */
#define ETH_DMATXDESC_DPAD                              ((uint32_t)0x04000000)  /*!< Disable Pad */
#define ETH_DMATXDESC_TTSEN                             ((uint32_t)0x02000000)  /*!< Transmit Time Stamp Enable */
#define ETH_DMATXDESC_CM                                ((uint32_t)0x00C00000)  /*!< Checksum Mode: 4 cases */
#define ETH_DMATXDESC_CM_DISABLE                        ((uint32_t)0x00000000)  /*!< Checksum Insertion disabled */
#define ETH_DMATXDESC_CM_IPV4HEADER                     ((uint32_t)0x00400000)  /*!< Only IP header checksum calculation and insertion are enabled */
#define ETH_DMATXDESC_CM_TCPUDPICMP_SEGMENT             ((uint32_t)0x00800000)  /*!< TCP/UDP/ICMP Checksum Insertion calculated but pseudo-header  */
#define ETH_DMATXDESC_CM_TCPUDPICMP_FULL                ((uint32_t)0x00C00000)  /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */
#define ETH_DMATXDESC_TERM                              ((uint32_t)0x00200000)  /*!< Transmit End of Ring Mode*/
#define ETH_DMATXDESC_TCHM                              ((uint32_t)0x00100000)  /*!< Transmit des Chained Mode*/
#define ETH_DMATXDESC_TTMSS                             ((uint32_t)0x00020000)  /*!< Tx Time Stamp Status */
#define ETH_DMATXDESC_IPHE                              ((uint32_t)0x00010000)  /*!< IP Header Error: IP4 or IP6*/
#define ETH_DMATXDESC_ES                                ((uint32_t)0x00008000)  /*!< Error summary */
#define ETH_DMATXDESC_JT                                ((uint32_t)0x00004000)  /*!< Jabber Timeout */
#define ETH_DMATXDESC_FRMF                              ((uint32_t)0x00002000)  /*!< clean FIFO */
#define ETH_DMATXDESC_IPPE                              ((uint32_t)0x00001000)  /*!< IP Payload Error */
#define ETH_DMATXDESC_LCA                               ((uint32_t)0x00000800)  /*!< Loss of Carrier */
#define ETH_DMATXDESC_NCA                               ((uint32_t)0x00000400)  /*!< No Carrier */
#define ETH_DMATXDESC_LCO                               ((uint32_t)0x00000200)  /*!< Late Collision */
#define ETH_DMATXDESC_ECO                               ((uint32_t)0x00000100)  /*!< abort transmission due to collision */
#define ETH_DMATXDESC_VFRM                              ((uint32_t)0x00000080)  /*!< VLAN Frame */
#define ETH_DMATXDESC_COCNT                             ((uint32_t)0x00000078)  /*!< Collision Count */
#define ETH_DMATXDESC_EXD                               ((uint32_t)0x00000004)  /*!< Excessive Deferral */
#define ETH_DMATXDESC_UFE                               ((uint32_t)0x00000002)  /*!< late data arrival from the memory */
#define ETH_DMATXDESC_DB                                ((uint32_t)0x00000001)  /*!< Deferred Bit */

/**
  * @brief  DMA Tx descriptor TDES1 register Bit def
  */
#define ETH_DMATXDESC_TB2S                              ((uint32_t)0x1FFF0000)  /*!< Transmit Buffer2 Size */
#define ETH_DMATXDESC_TB1S                              ((uint32_t)0x00001FFF)  /*!< Transmit Buffer1 Size */

/**
  * @brief  DMA Tx descriptor TDES2 register Bit def
  */
#define ETH_DMATXDESC_TB1AP                             ((uint32_t)0xFFFFFFFF)  /*!< Buffer1 Address Pointer */

/**
  * @brief  DMA Tx descriptor TDES3 register Bit def
  */
#define ETH_DMATXDESC_TB2AP                             ((uint32_t)0xFFFFFFFF)  /*!< Buffer2 Address Pointer */

/**
  * @}
  */


/** @defgroup DMA_Rx_descriptor
  * @{
  */

/**
  DMA Rx Desciptor
  --------------------------------------------------------------------------------------------------------------------
  RDES0 | BUSY(31) |                                             Status [30:0]                                          |
  ---------------------------------------------------------------------------------------------------------------------
  RDES1 | CTRL(31) | Reserved[30:29] | Buffer2 ByteCount[28:16] | CTRL[15:14] | Reserved(13) | Buffer1 ByteCount[12:0] |
  ---------------------------------------------------------------------------------------------------------------------
  RDES2 |                                       Buffer1 Address [31:0]                                                 |
  ---------------------------------------------------------------------------------------------------------------------
  RDES3 |                          Buffer2 Address [31:0] / Next Desciptor Address [31:0]                              |
  ---------------------------------------------------------------------------------------------------------------------
*/

/**
  * @brief  DMA Rx descriptor RDES0 register Bit def
  */
#define ETH_DMARXDESC_BUSY                              ((uint32_t)0x80000000)  /*!< DMA or CPU control descriptor */
#define ETH_DMARXDESC_DAFF                              ((uint32_t)0x40000000)  /*!< DA filter fail */
#define ETH_DMARXDESC_FRML                              ((uint32_t)0x3FFF0000)  /*!< Frame length  */
#define ETH_DMARXDESC_ERRS                              ((uint32_t)0x00008000)  /*!< Error summary */
#define ETH_DMARXDESC_DERR                              ((uint32_t)0x00004000)  /*!< no more descriptors for receive frame  */
#define ETH_DMARXDESC_SAFF                              ((uint32_t)0x00002000)  /*!< SA filter fail */
#define ETH_DMARXDESC_LERR                              ((uint32_t)0x00001000)  /*!< Frame size not matching with length field */
#define ETH_DMARXDESC_OERR                              ((uint32_t)0x00000800)  /*!< FIFO Overflow Error */
#define ETH_DMARXDESC_VTAG                              ((uint32_t)0x00000400)  /*!< VLAN Tag: a VLAN frame tag */
#define ETH_DMARXDESC_FDES                              ((uint32_t)0x00000200)  /*!< First descriptor of the frame */
#define ETH_DMARXDESC_LDES                              ((uint32_t)0x00000100)  /*!< Last descriptor of the frame */
#define ETH_DMARXDESC_IPHCERR                           ((uint32_t)0x00000080)  /*!< IPC Checksum Error: Rx Ipv4 or Ipv6 header checksum error */
#define ETH_DMARXDESC_LCO                               ((uint32_t)0x00000040)  /*!< Late collision occurred during reception */
#define ETH_DMARXDESC_FRMT                              ((uint32_t)0x00000020)  /*!< Frame type */
#define ETH_DMARXDESC_RWDT                              ((uint32_t)0x00000010)  /*!< Receive WD Timeout */
#define ETH_DMARXDESC_RERR                              ((uint32_t)0x00000008)  /*!< the RX_ERR signal is asserted while RX_DV is asserted during frame reception */
#define ETH_DMARXDESC_DBERR                             ((uint32_t)0x00000004)  /*!< received frame has a non int multiple of bytes */
#define ETH_DMARXDESC_CERR                              ((uint32_t)0x00000002)  /*!< CRC error */
#define ETH_DMARXDESC_PCERR                             ((uint32_t)0x00000001)  /*!< Receive MAC address matched/ Receive Payload Checksum Error */

/**
  * @brief  DMA Rx descriptor RDES1 register Bit def
  */
#define ETH_DMARXDESC_DINTC                             ((uint32_t)0x80000000)  /*!< Disable Interrupt on Completion */
#define ETH_DMARXDESC_RB2S                              ((uint32_t)0x1FFF0000)  /*!< Receive Buffer2 Size */
#define ETH_DMARXDESC_RERM                              ((uint32_t)0x00008000)  /*!< Receive End of Ring mode*/
#define ETH_DMARXDESC_RCHM                              ((uint32_t)0x00004000)  /*!< Receive des Chained mode */
#define ETH_DMARXDESC_RB1S                              ((uint32_t)0x00001FFF)  /*!< Receive Buffer1 Size */

/**
  * @brief  DMA Rx descriptor RDES2 register Bit def
  */
#define ETH_DMARXDESC_RB1AP                             ((uint32_t)0xFFFFFFFF)  /*!< Buffer1 Address Pointer */

/**
  * @brief  DMA Rx descriptor RDES3 register Bit def
  */
#define ETH_DMARXDESC_RB2AP                             ((uint32_t)0xFFFFFFFF)  /*!< Buffer2 Address Pointer */

#ifndef _PHY_H_
#define DP83848                                         0
#define LAN8700                                         1
#define PHY_TYPE                                        DP83848

/**
  * @}
  */

/** @defgroup PHY_Read_write_Timeouts
  * @{
  */
#define PHY_READ_TO                                     ((uint32_t)0x0004FFFF)
#define PHY_WRITE_TO                                    ((uint32_t)0x0004FFFF)

/**
  * @}
  */

/** @defgroup PHY_Reset_Delay
  * @{
  */
#define PHY_RESETDELAY                                  ((uint32_t)0x000FFFFF)

/**
  * @}
  */

/** @defgroup PHY_Config_Delay
  * @{
  */
#define PHY_CONFIGDELAY                                 ((uint32_t)0x00FFFFFF)

/**
  * @}
  */

/** @defgroup PHY_Register_address
  * @{
  */
#define PHY_BCR                                         0                  /*!< Tranceiver Basic Control Register */
#define PHY_BSR                                         1                  /*!< Tranceiver Basic Status Register */

/**
  * @}
  */

/** @defgroup PHY_basic_Control_register
  * @{
  */
#define PHY_RESET                                       ((u16)0x8000)      /*!< PHY Reset */
#define PHY_LOOPBACK                                    ((u16)0x4000)      /*!< Enable loop-back mode */
#define PHY_FULLDUPLEX_100M                             ((u16)0x2100)      /*!< Configure speed to 100 Mb/s and the full-duplex mode */
#define PHY_HALFDUPLEX_100M                             ((u16)0x2000)      /*!< Configure speed to 100 Mb/s and the half-duplex mode */
#define PHY_FULLDUPLEX_10M                              ((u16)0x0100)      /*!< Configure speed to 10 Mb/s and the full-duplex mode */
#define PHY_HALFDUPLEX_10M                              ((u16)0x0000)      /*!< Configure speed to 10 Mb/s and the half-duplex mode */
#define PHY_AUTONEGOTIATION                             ((u16)0x1000)      /*!< Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION                     ((u16)0x0200)      /*!< Restart auto-negotiation function */
#define PHY_POWERDOWN                                   ((u16)0x0800)      /*!< Enable the power down mode */
#define PHY_ISOLATE                                     ((u16)0x0400)      /*!< Isolate PHY from MII */

/**
  * @}
  */

/** @defgroup PHY_basic_status_register
  * @{
  */
#define PHY_AUTONEGO_COMPLETE                           ((u16)0x0020)      /*!< Auto-Negotioation process completed */
#define PHY_LINKED_STATUS                               ((u16)0x0004)      /*!< Valid link established */
#define PHY_JABBER_DETECTION                            ((u16)0x0002)      /*!< Jabber condition detected */

/**
  * @}
  */

/** @defgroup PHY_status_register
  * @{
  */
/* The PHY status register value change with PHY in different Manufacturer
   so the user can use external PHY lib to update this value if PHY types user selected not included in firmware */
#if(PHY_TYPE == LAN8700)
/**
  * @brief  For LAN8700
  */
#define PHY_SR                                          31                 /*!< Tranceiver Status Register */
/* The Speed and Duplex mask values change with PHY in different Manufacturer
   so the user can use external PHY lib to update this value if PHY types user selected not included in firmware */
#define PHY_Speed_Status                                ((u16)0x0004)      /*!< Configured information of Speed: 10Mbps */
#define PHY_DUPLEX_STATUS                               ((u16)0x0010)      /*!< Configured information of Duplex: Full-duplex */

#elif(PHY_TYPE == DP83848)
/**
  * @brief  For DP83848
  */
#define PHY_SR                                          16     /*!< Tranceiver Status Register */
/* The Speed and Duplex mask values change with PHY in different Manufacturer
   so the user can use external PHY lib to update this value if PHY types user selected not included in firmware */
#define PHY_SPEED_STATUS                                ((u16)0x0002)      /*!< Configured information of Speed: 10Mbps */
#define PHY_DUPLEX_STATUS                               ((u16)0x0004)      /*!< Configured information of Duplex: Full-duplex */

#define PHY_Reset                                       PHY_RESETDELAY
#define PHY_ResetDelay                                  PHY_RESETDELAY
#define PHY_Speed_Status                                PHY_SPEED_STATUS

#endif

#endif


/**
  * @}
  */

/** @defgroup ETH_AutoNegotiation
  * @{
  */
#define ETH_AUTONEGOTIATION_ENABLE                      ((uint32_t)0x00000001)
#define ETH_AUTONEGOTIATION_DISABLE                     ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_watchdog
  * @{
  */
#define ETH_WATCHDOG_ENABLE                             ((uint32_t)0x00000000)
#define ETH_WATCHDOG_DISABLE                            ((uint32_t)0x00800000)

/**
  * @}
  */

/** @defgroup ETH_Jabber
  * @{
  */
#define ETH_JABBER_ENABLE                               ((uint32_t)0x00000000)
#define ETH_JABBER_DISABLE                              ((uint32_t)0x00400000)

/**
  * @}
  */

/** @defgroup ETH_Inter_Frame_Gap
  * @{
  */
#define ETH_INTERFRAMEGAP_96BIT                         ((uint32_t)0x00000000)
#define ETH_INTERFRAMEGAP_88BIT                         ((uint32_t)0x00020000)
#define ETH_INTERFRAMEGAP_80BIT                         ((uint32_t)0x00040000)
#define ETH_INTERFRAMEGAP_72BIT                         ((uint32_t)0x00060000)
#define ETH_INTERFRAMEGAP_64BIT                         ((uint32_t)0x00080000)
#define ETH_INTERFRAMEGAP_56BIT                         ((uint32_t)0x000A0000)
#define ETH_INTERFRAMEGAP_48BIT                         ((uint32_t)0x000C0000)
#define ETH_INTERFRAMEGAP_40BIT                         ((uint32_t)0x000E0000)


/**
  * @}
  */

/** @defgroup ETH_Carrier_Sense
  * @{
  */
#define ETH_CARRIERSENSE_ENABLE                         ((uint32_t)0x00000000)
#define ETH_CARRIERSENSE_DISABLE                        ((uint32_t)0x00010000)

/**
  * @}
  */

/** @defgroup ETH_Speed
  * @{
  */
#define ETH_SPEEDMODE_10M                               ((uint32_t)0x00000000)
#define ETH_SPEEDMODE_100M                              ((uint32_t)0x00004000)

/**
  * @}
  */

/** @defgroup ETH_Receive_Own
  * @{
  */
#define ETH_RECEIVEOWN_ENABLE                           ((uint32_t)0x00000000)
#define ETH_RECEIVEOWN_DISABLE                          ((uint32_t)0x00002000)


/**
  * @}
  */

/** @defgroup ETH_Loop_Back_Mode
  * @{
  */
#define ETH_LOOPBACKMODE_ENABLE                         ((uint32_t)0x00001000)
#define ETH_LOOPBACKMODE_DISABLE                        ((uint32_t)0x00000000)


/**
  * @}
  */

/** @defgroup ETH_Duplex_Mode
  * @{
  */
#define ETH_MODE_FULLDUPLEX                             ((uint32_t)0x00000800)
#define ETH_MODE_HALFDUPLEX                             ((uint32_t)0x00000000)


/**
  * @}
  */

/** @defgroup ETH_Checksum_Offload
  * @{
  */
#define ETH_CHECKSUMOFFLOAD_ENABLE                      ((uint32_t)0x00000400)
#define ETH_CHECKSUMOFFLOAD_DISABLE                     ((uint32_t)0x00000000)


/**
  * @}
  */

/** @defgroup ETH_Retry_Transmission
  * @{
  */
#define ETH_RETRYTRANSMISSION_ENABLE                    ((uint32_t)0x00000000)
#define ETH_RETRYTRANSMISSION_DISABLE                   ((uint32_t)0x00000200)


/**
  * @}
  */

/** @defgroup ETH_Automatic_Pad_CRC_Drop
  * @{
  */
#define ETH_AUTOMATICPADCRCDROP_ENABLE                  ((uint32_t)0x00000080)
#define ETH_AUTOMATICPADCRCDROP_DISABLE                 ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Back_Off_Limit
  * @{
  */
#define ETH_BACKOFFLIMIT_10                             ((uint32_t)0x00000000)
#define ETH_BACKOFFLIMIT_8                              ((uint32_t)0x00000020)
#define ETH_BACKOFFLIMIT_4                              ((uint32_t)0x00000040)
#define ETH_BACKOFFLIMIT_1                              ((uint32_t)0x00000060)

/**
  * @}
  */

/** @defgroup ETH_Deferral_Check
  * @{
  */
#define ETH_DEFERRALCHECK_ENABLE                        ((uint32_t)0x00000010)
#define ETH_DEFERRALCHECK_DISABLE                       ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Filter_Disable
  * @{
  */
#define ETH_FILTERDISABLE_ENABLE                        ((uint32_t)0x80000000)
#define ETH_FILTERDISABLE_DISABLE                       ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Source_Addr_Filter
  * @{
  */
#define ETH_SOURCEADDRFILTER_NORMAL_ENABLE              ((uint32_t)0x00000200)
#define ETH_SOURCEADDRFILTER_INVERSE_ENABLE             ((uint32_t)0x00000300)
#define ETH_SOURCEADDRFILTER_DISABLE                    ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Pass_Control_Frames
  * @{
  */
#define ETH_PASSCONTROLFRAMES_BLOCKALL                  ((uint32_t)0x00000040)
#define ETH_PASSCONTROLFRAMES_FORWARDALL                ((uint32_t)0x00000080)
#define ETH_PASSCONTROLFRAMES_FORWARDPASSEDADDRFILTER   ((uint32_t)0x000000C0)

/**
  * @}
  */

/** @defgroup ETH_Broadcast_Frames_Reception
  * @{
  */
#define ETH_BROADCASTFRAMESRECEPTION_ENABLE             ((uint32_t)0x00000000)
#define ETH_BROADCASTFRAMESRECEPTION_DISABLE            ((uint32_t)0x00000020)

/**
  * @}
  */

/** @defgroup ETH_Destination_Addr_Filter
  * @{
  */
#define ETH_DESTINATIONADDRFILTER_NORMAL                ((uint32_t)0x00000000)
#define ETH_DESTINATIONADDRFILTER_INVERSE               ((uint32_t)0x00000008)

/**
  * @}
  */

/** @defgroup ETH_Promiscuous_Mode
  * @{
  */
#define ETH_PROMISCUOUSMODE_ENABLE                      ((uint32_t)0x00000001)
#define ETH_PROMISCUOUSMODE_DISABLE                     ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Multicast_Frames_Filter
  * @{
  */
#define ETH_MULTICASTFRAMESFILTER_PERFECTHASHTABLE      ((uint32_t)0x00000404)
#define ETH_MULTICASTFRAMESFILTER_HASHTABLE             ((uint32_t)0x00000004)
#define ETH_MULTICASTFRAMESFILTER_PERFECT               ((uint32_t)0x00000000)
#define ETH_MULTICASTFRAMESFILTER_NONE                  ((uint32_t)0x00000010)


/**
  * @}
  */

/** @defgroup ETH_Unicast_Frames_Filter
  * @{
  */
#define ETH_UNICASTFRAMESFILTER_PERFECTHASHTABLE        ((uint32_t)0x00000402)
#define ETH_UNICASTFRAMESFILTER_HASHTABLE               ((uint32_t)0x00000002)
#define ETH_UNICASTFRAMESFILTER_PERFECT                 ((uint32_t)0x00000000)

/**
  * @}
  */


/** @defgroup ETH_Zero_Quanta_Pause
  * @{
  */
#define ETH_ZEROQUANTAPAUSE_ENABLE                      ((uint32_t)0x00000000)
#define ETH_ZEROQUANTAPAUSE_DISABLE                     ((uint32_t)0x00000080)
/**
  * @}
  */

/** @defgroup ETH_Pause_Low_Threshold
  * @{
  */
#define ETH_PAUSELOWTHRESHOLD_MINUS4                    ((uint32_t)0x00000000)
#define ETH_PAUSELOWTHRESHOLD_MINUS28                   ((uint32_t)0x00000010)
#define ETH_PAUSELOWTHRESHOLD_MINUS144                  ((uint32_t)0x00000020)
#define ETH_PAUSELOWTHRESHOLD_MINUS256                  ((uint32_t)0x00000030)

/**
  * @}
  */

/** @defgroup ETH_RFD_Threshold
  * @{
  */
#define ETH_RFD_256BYTES                                ((uint32_t)0x00000000)
#define ETH_RFD_512BYTES                                ((uint32_t)0x00000010)
#define ETH_RFD_768BYTES                                ((uint32_t)0x00000020)
#define ETH_RFD_1024BYTES                               ((uint32_t)0x00000030)
#define ETH_RFD_1280BYTES                               ((uint32_t)0x00000040)
#define ETH_RFD_1536BYTES                               ((uint32_t)0x00000050)
#define ETH_RFD_1792BYTES                               ((uint32_t)0x00000060)

/**
  * @}
  */

/** @defgroup ETH_RFA_Threshold
  * @{
  */
#define ETH_RFA_256BYTES                                ((uint32_t)0x00000000)
#define ETH_RFA_512BYTES                                ((uint32_t)0x00000001)
#define ETH_RFA_768BYTES                                ((uint32_t)0x00000002)
#define ETH_RFA_1024BYTES                               ((uint32_t)0x00000003)
#define ETH_RFA_1280BYTES                               ((uint32_t)0x00000004)
#define ETH_RFA_1536BYTES                               ((uint32_t)0x00000005)
#define ETH_RFA_1792BYTES                               ((uint32_t)0x00000006)

/**
  * @}
  */

/** @defgroup ETH_Unicast_Pause_Frame_Detect
  * @{
  */
#define ETH_UNICASTPAUSEFRAMEDETECT_ENABLE              ((uint32_t)0x00000008)
#define ETH_UNICASTPAUSEFRAMEDETECT_DISABLE             ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Receive_Flow_Control
  * @{
  */
#define ETH_RECEIVEFLOWCONTROL_ENABLE                   ((uint32_t)0x00000004)
#define ETH_RECEIVEFLOWCONTROL_DISABLE                  ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Transmit_Flow_Control
  * @{
  */
#define ETH_TRANSMITFLOWCONTROL_ENABLE                  ((uint32_t)0x00000002)
#define ETH_TRANSMITFLOWCONTROL_DISABLE                 ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_VLAN_Tag_Comparison
  * @{
  */
#define ETH_VLANTAGCOMPARISON_12BIT                     ((uint32_t)0x00010000)
#define ETH_VLANTAGCOMPARISON_16BIT                     ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_MAC_Flags
  * @{
  */
#define ETH_MAC_FLAG_TST                                ((uint32_t)0x00000200)  /*!< Time stamp trigger flag (on MAC) */
#define ETH_MAC_FLAG_MSCT                               ((uint32_t)0x00000040)  /*!< MSC transmit flag  */
#define ETH_MAC_FLAG_MSCR                               ((uint32_t)0x00000020)  /*!< MSC receive flag */
#define ETH_MAC_FLAG_MSC                                ((uint32_t)0x00000010)
#define ETH_MAC_FLAG_WUM                                ((uint32_t)0x00000008)
/**
  * @}
  */

/** @defgroup ETH_MAC_Interrupts
  * @{
  */
#define ETH_MAC_INT_TST                                  ((uint32_t)0x00000200)  /*!< Time stamp trigger interrupt (on MAC) */
#define ETH_MAC_INT_MSCT                                 ((uint32_t)0x00000040)  /*!< MSC transmit interrupt */
#define ETH_MAC_INT_MSCR                                 ((uint32_t)0x00000020)  /*!< MSC receive interrupt */
#define ETH_MAC_INT_MSC                                  ((uint32_t)0x00000010)
#define ETH_MAC_INT_WUM                                  ((uint32_t)0x00000008)
/**
  * @}
  */

/** @defgroup ETH_MAC_addresses
  * @{
  */
#define ETH_MAC_ADDRESS0                                ((uint32_t)0x00000000)
#define ETH_MAC_ADDRESS1                                ((uint32_t)0x00000008)
#define ETH_MAC_ADDRESS2                                ((uint32_t)0x00000010)
#define ETH_MAC_ADDRESS3                                ((uint32_t)0x00000018)
/**
  * @}
  */

/** @defgroup ETH_MAC_addresses_filter_SA_DA_filed_of_received_frames
  * @{
  */
#define ETH_MAC_ADDRESSFILTER_SA                        ((uint32_t)0x00000000)
#define ETH_MAC_ADDRESSFILTER_DA                        ((uint32_t)0x00000008)
/**
  * @}
  */

/** @defgroup ETH_MAC_addresses_filter_Mask_bytes
  * @{
  */
#define ETH_MAC_ADDRESSMASK_BYTE6                       ((uint32_t)0x20000000)  /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MAC_ADDRESSMASK_BYTE5                       ((uint32_t)0x10000000)  /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MAC_ADDRESSMASK_BYTE4                       ((uint32_t)0x08000000)  /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MAC_ADDRESSMASK_BYTE3                       ((uint32_t)0x04000000)  /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MAC_ADDRESSMASK_BYTE2                       ((uint32_t)0x02000000)  /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MAC_ADDRESSMASK_BYTE1                       ((uint32_t)0x01000000)  /*!< Mask MAC Address low reg bits [7:0] */

/**
  * @}
  */


/** @defgroup ETH_DMA_Tx_descriptor_segment
  * @{
  */
#define ETH_DMATXDESC_LASTSEGMENT                       ((uint32_t)0x40000000)
#define ETH_DMATXDESC_FIRSTSEGMENT                      ((uint32_t)0x20000000)

/**
  * @}
  */

/** @defgroup ETH_DMA_Tx_descriptor_Checksum_Insertion_Control
  * @{
  */
#define ETH_DMATXDESC_CHECKSUMDISABLE                   ((uint32_t)0x00000000)
#define ETH_DMATXDESC_CHECKSUMIPV4HEADER                ((uint32_t)0x00400000)
#define ETH_DMATXDESC_CHECKSUMTCPUDPICMPSEGMENT         ((uint32_t)0x00800000)
#define ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL            ((uint32_t)0x00C00000)


/**
  * @}
  */

/** @defgroup ETH_DMA_Rx_descriptor_buffers_
  * @{
  */
#define ETH_DMARXDESC_BUFFER1                           ((uint32_t)0x00000000)
#define ETH_DMARXDESC_BUFFER2                           ((uint32_t)0x00000001)

/**
  * @}
  */

/** @defgroup ETH_Drop_TCP_IP_Checksum_Error_Frame
  * @{
  */
#define ETH_DROPTCPIPCHECKSUMERRORFRAME_ENABLE          ((uint32_t)0x00000000)
#define ETH_DROPTCPIPCHECKSUMERRORFRAME_DISABLE         ((uint32_t)0x04000000)
/**
  * @}
  */

/** @defgroup ETH_Receive_Store_Forward
  * @{
  */
#define ETH_RECEIVESTOREFORWARD_ENABLE                  ((uint32_t)0x02000000)
#define ETH_RECEIVESTOREFORWARD_DISABLE                 ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup ETH_Flush_Received_Frame
  * @{
  */
#define ETH_FLUSHRECEIVEDFRAME_ENABLE                   ((uint32_t)0x00000000)
#define ETH_FLUSHRECEIVEDFRAME_DISABLE                  ((uint32_t)0x01000000)
/**
  * @}
  */

/** @defgroup ETH_Transmit_Store_Forward
  * @{
  */
#define ETH_TRANSMITSTOREFORWARD_ENABLE                 ((uint32_t)0x00200000)
#define ETH_TRANSMITSTOREFORWARD_DISABLE                ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup ETH_Transmit_Threshold_Control
  * @{
  */
#define ETH_TRANSMITTHRESHOLDCONTROL_64BYTES            ((uint32_t)0x00000000)
#define ETH_TRANSMITTHRESHOLDCONTROL_128BYTES           ((uint32_t)0x00004000)
#define ETH_TRANSMITTHRESHOLDCONTROL_192BYTES           ((uint32_t)0x00008000)
#define ETH_TRANSMITTHRESHOLDCONTROL_256BYTES           ((uint32_t)0x0000C000)
#define ETH_TRANSMITTHRESHOLDCONTROL_40BYTES            ((uint32_t)0x00010000)
#define ETH_TRANSMITTHRESHOLDCONTROL_32BYTES            ((uint32_t)0x00014000)
#define ETH_TRANSMITTHRESHOLDCONTROL_24BYTES            ((uint32_t)0x00018000)
#define ETH_TRANSMITTHRESHOLDCONTROL_16BYTES            ((uint32_t)0x0001C000)
/**
  * @}
  */

/** @defgroup ETH_Forward_Error_Frames
  * @{
  */
#define ETH_FORWARDERRORFRAMES_ENABLE                   ((uint32_t)0x00000080)
#define ETH_FORWARDERRORFRAMES_DISABLE                  ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup ETH_Forward_Undersized_Good_Frames
  * @{
  */
#define ETH_FORWARDUNDERSIZEDGOODFRAMES_ENABLE          ((uint32_t)0x00000040)
#define ETH_FORWARDUNDERSIZEDGOODFRAMES_DISABLE         ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Receive_Threshold_Control
  * @{
  */
#define ETH_RECEIVETHRESHOLDCONTROL_64BYTES             ((uint32_t)0x00000000)
#define ETH_RECEIVETHRESHOLDCONTROL_32BYTES             ((uint32_t)0x00000008)
#define ETH_RECEIVETHRESHOLDCONTROL_96BYTES             ((uint32_t)0x00000010)
#define ETH_RECEIVETHRESHOLDCONTROL_128BYTES            ((uint32_t)0x00000018)
/**
  * @}
  */

/** @defgroup ETH_Second_Frame_Operate
  * @{
  */
#define ETH_SECONDFRAMEOPERATE_ENABLE                   ((uint32_t)0x00000004)
#define ETH_SECONDFRAMEOPERATE_DISABLE                  ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Address_Aligned
  * @{
  */
#define ETH_ADDRESSALIGNED_ENABLE                       ((uint32_t)0x02000000)
#define ETH_ADDRESSALIGNED_DISABLE                      ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Fixed_Burst
  * @{
  */
#define ETH_FIXEDBURST_ENABLE                           ((uint32_t)0x00010000)
#define ETH_FIXEDBURST_DISABLE                          ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup ETH_Rx_DMA_Burst_Length
  * @{
  */
#define ETH_RXDMABURSTLENGTH_1BEAT                      ((uint32_t)0x00020000)
#define ETH_RXDMABURSTLENGTH_2BEAT                      ((uint32_t)0x00040000)
#define ETH_RXDMABURSTLENGTH_4BEAT                      ((uint32_t)0x00080000)
#define ETH_RXDMABURSTLENGTH_8BEAT                      ((uint32_t)0x00100000)
#define ETH_RXDMABURSTLENGTH_16BEAT                     ((uint32_t)0x00200000)
#define ETH_RXDMABURSTLENGTH_32BEAT                     ((uint32_t)0x00400000)
#define ETH_RXDMABURSTLENGTH_4XPBL_4BEAT                ((uint32_t)0x01020000)
#define ETH_RXDMABURSTLENGTH_4XPBL_8BEAT                ((uint32_t)0x01040000)
#define ETH_RXDMABURSTLENGTH_4XPBL_16BEAT               ((uint32_t)0x01080000)
#define ETH_RXDMABURSTLENGTH_4XPBL_32BEAT               ((uint32_t)0x01100000)
#define ETH_RXDMABURSTLENGTH_4XPBL_64BEAT               ((uint32_t)0x01200000)
#define ETH_RXDMABURSTLENGTH_4XPBL_128BEAT              ((uint32_t)0x01400000)
/**
  * @}
  */

/** @defgroup ETH_Tx_DMA_Burst_Length
  * @{
  */
#define ETH_TXDMABURSTLENGTH_1BEAT                      ((uint32_t)0x00000100)
#define ETH_TXDMABURSTLENGTH_2BEAT                      ((uint32_t)0x00000200)
#define ETH_TXDMABURSTLENGTH_4BEAT                      ((uint32_t)0x00000400)
#define ETH_TXDMABURSTLENGTH_8BEAT                      ((uint32_t)0x00000800)
#define ETH_TXDMABURSTLENGTH_16BEAT                     ((uint32_t)0x00001000)
#define ETH_TXDMABURSTLENGTH_32BEAT                     ((uint32_t)0x00002000)
#define ETH_TXDMABURSTLENGTH_4XPBL_4BEAT                ((uint32_t)0x01000100)
#define ETH_TXDMABURSTLENGTH_4XPBL_8BEAT                ((uint32_t)0x01000200)
#define ETH_TXDMABURSTLENGTH_4XPBL_16BEAT               ((uint32_t)0x01000400)
#define ETH_TXDMABURSTLENGTH_4XPBL_32BEAT               ((uint32_t)0x01000800)
#define ETH_TXDMABURSTLENGTH_4XPBL_64BEAT               ((uint32_t)0x01001000)
#define ETH_TXDMABURSTLENGTH_4XPBL_128BEAT              ((uint32_t)0x01002000)

/**
  * @}
  */

/** @defgroup ETH_DMA_Arbitration
  * @{
  */
#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_1_1          ((uint32_t)0x00000000)
#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_2_1          ((uint32_t)0x00004000)
#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_3_1          ((uint32_t)0x00008000)
#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_4_1          ((uint32_t)0x0000C000)
#define ETH_DMAARBITRATION_RXPRIORTX                    ((uint32_t)0x00000002)

/**
  * @}
  */

/** @defgroup ETH_DMA_Flags
  * @{
  */
#define ETH_DMA_FLAG_TST                                ((uint32_t)0x20000000)  /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_FLAG_WUM                                ((uint32_t)0x10000000)  /*!< WUM interrupt (on DMA) */
#define ETH_DMA_FLAG_MSC                                ((uint32_t)0x08000000)  /*!< MSC interrupt (on DMA) */
#define ETH_DMA_FLAG_DATATRANSFERERROR                  ((uint32_t)0x00800000)      /*!< Error bits 0-Rx DMA, 1-Tx DMA */
#define ETH_DMA_FLAG_READWRITEERROR                     ((uint32_t)0x01000000)      /*!< Error bits 0-write trnsf, 1-read transfr */
#define ETH_DMA_FLAG_ACCESSERROR                        ((uint32_t)0x02000000)      /*!< Error bits 0-data buffer, 1-desc. access */
#define ETH_DMA_FLAG_NIS                                ((uint32_t)0x00010000)  /*!< Normal interrupt summary flag */
#define ETH_DMA_FLAG_AIS                                ((uint32_t)0x00008000)  /*!< Abnormal interrupt summary flag */
#define ETH_DMA_FLAG_ER                                 ((uint32_t)0x00004000)  /*!< Early receive flag */
#define ETH_DMA_FLAG_FBE                                ((uint32_t)0x00002000)  /*!< Fatal bus error flag */
#define ETH_DMA_FLAG_ET                                 ((uint32_t)0x00000400)  /*!< Early transmit flag */
#define ETH_DMA_FLAG_RWT                                ((uint32_t)0x00000200)  /*!< Receive watchdog timeout flag */
#define ETH_DMA_FLAG_RPS                                ((uint32_t)0x00000100)  /*!< Receive process stopped flag */
#define ETH_DMA_FLAG_RBU                                ((uint32_t)0x00000080)  /*!< Receive buffer unavailable flag */
#define ETH_DMA_FLAG_R                                  ((uint32_t)0x00000040)  /*!< Receive flag */
#define ETH_DMA_FLAG_TU                                 ((uint32_t)0x00000020)  /*!< Transmit Underflow flag */
#define ETH_DMA_FLAG_RO                                 ((uint32_t)0x00000010)  /*!< Receive Overflow flag */
#define ETH_DMA_FLAG_TJT                                ((uint32_t)0x00000008)  /*!< Transmit jabber timeout flag */
#define ETH_DMA_FLAG_TBU                                ((uint32_t)0x00000004)  /*!< Transmit buffer unavailable flag */
#define ETH_DMA_FLAG_TPS                                ((uint32_t)0x00000002)  /*!< Transmit process stopped flag */
#define ETH_DMA_FLAG_T                                  ((uint32_t)0x00000001)  /*!< Transmit flag */

/**
  * @}
  */

/** @defgroup ETH_DMA_Interrupts
  * @{
  */
#define ETH_DMA_INT_TST                                  ((uint32_t)0x20000000)  /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_INT_WUM                                  ((uint32_t)0x10000000)  /*!< WUM interrupt (on DMA) */
#define ETH_DMA_INT_MSC                                  ((uint32_t)0x08000000)  /*!< MSC interrupt (on DMA) */
#define ETH_DMA_INT_NIS                                  ((uint32_t)0x00010000)  /*!< Normal interrupt summary */
#define ETH_DMA_INT_AIS                                  ((uint32_t)0x00008000)  /*!< Abnormal interrupt summary */
#define ETH_DMA_INT_ER                                   ((uint32_t)0x00004000)  /*!< Early receive interrupt */
#define ETH_DMA_INT_FBE                                  ((uint32_t)0x00002000)  /*!< Fatal bus error interrupt */
#define ETH_DMA_INT_ET                                   ((uint32_t)0x00000400)  /*!< Early transmit interrupt */
#define ETH_DMA_INT_RWT                                  ((uint32_t)0x00000200)  /*!< Receive watchdog timeout interrupt */
#define ETH_DMA_INT_RPS                                  ((uint32_t)0x00000100)  /*!< Receive process stopped interrupt */
#define ETH_DMA_INT_RBU                                  ((uint32_t)0x00000080)  /*!< Receive buffer unavailable interrupt */
#define ETH_DMA_INT_R                                    ((uint32_t)0x00000040)  /*!< Receive interrupt */
#define ETH_DMA_INT_TU                                   ((uint32_t)0x00000020)  /*!< Transmit Underflow interrupt */
#define ETH_DMA_INT_RO                                   ((uint32_t)0x00000010)  /*!< Receive Overflow interrupt */
#define ETH_DMA_INT_TJT                                  ((uint32_t)0x00000008)  /*!< Transmit jabber timeout interrupt */
#define ETH_DMA_INT_TBU                                  ((uint32_t)0x00000004)  /*!< Transmit buffer unavailable interrupt */
#define ETH_DMA_INT_TPS                                  ((uint32_t)0x00000002)  /*!< Transmit process stopped interrupt */
#define ETH_DMA_INT_T                                    ((uint32_t)0x00000001)  /*!< Transmit interrupt */


/**
  * @}
  */

/** @defgroup ETH_DMA_transmit_process_state_
  * @{
  */
#define ETH_DMA_TRANSMITPROCESS_STOPPED                 ((uint32_t)0x00000000)
#define ETH_DMA_TRANSMITPROCESS_FETCHING                ((uint32_t)0x00100000)
#define ETH_DMA_TRANSMITPROCESS_WAITING                 ((uint32_t)0x00200000)
#define ETH_DMA_TRANSMITPROCESS_READING                 ((uint32_t)0x00300000)
#define ETH_DMA_TRANSMITPROCESS_SUSPENDED               ((uint32_t)0x00600000)
#define ETH_DMA_TRANSMITPROCESS_CLOSING                 ((uint32_t)0x00700000)

/**
  * @}
  */


/** @defgroup ETH_DMA_receive_process_state_
  * @{
  */
#define ETH_DMA_RECEIVEPROCESS_STOPPED                  ((uint32_t)0x00000000)
#define ETH_DMA_RECEIVEPROCESS_FETCHING                 ((uint32_t)0x00020000)
#define ETH_DMA_RECEIVEPROCESS_WAITING                  ((uint32_t)0x00060000)
#define ETH_DMA_RECEIVEPROCESS_SUSPENDED                ((uint32_t)0x00080000)
#define ETH_DMA_RECEIVEPROCESS_CLOSING                  ((uint32_t)0x000A0000)
#define ETH_DMA_RECEIVEPROCESS_QUEUING                  ((uint32_t)0x000E0000)

/**
  * @}
  */

/** @defgroup ETH_DMA_overflow_
  * @{
  */
#define ETH_DMA_OVERFLOW_RXFIFOCOUNTER                  ((uint32_t)0x10000000)
#define ETH_DMA_OVERFLOW_MISSEDFRAMECOUNTER             ((uint32_t)0x00010000)

/**
  * @}
  */

/** @defgroup ETH_WUM_Flags
  * @{
  */
#define ETH_WUM_FLAG_WUFFRPR                            ((uint32_t)0x80000000)  /*!< Wake-Up Frame Filter Register Poniter Reset */
#define ETH_WUM_FLAG_WUFR                               ((uint32_t)0x00000040)  /*!< Wake-Up Frame Received */
#define ETH_WUM_FLAG_MPKR                               ((uint32_t)0x00000020)  /*!< Magic Packet Received */

/**
  * @}
  */

/** @defgroup ETH_MSC_Tx_Interrupts
  * @{
  */
#define ETH_MSC_INT_TGF                                  ((uint32_t)0x00200000)  /*!< When Tx good frame counter reaches half the maximum value */
#define ETH_MSC_INT_TGFMSC                               ((uint32_t)0x00008000)  /*!< When Tx good multi col counter reaches half the maximum value */
#define ETH_MSC_INT_TGFSC                                ((uint32_t)0x00004000)  /*!< When Tx good single col counter reaches half the maximum value */

/**
  * @}
  */

/** @defgroup ETH_MSC_Rx_Interrupts
  * @{
  */
#define ETH_MSC_INT_RGUF                                 ((uint32_t)0x10020000)  /*!< When Rx good unicast frames counter reaches half the maximum value */
#define ETH_MSC_INT_RFAE                                 ((uint32_t)0x10000040)  /*!< When Rx alignment error counter reaches half the maximum value */
#define ETH_MSC_INT_RFCE                                 ((uint32_t)0x10000020)  /*!< When Rx crc error counter reaches half the maximum value */
/**
  * @}
  */

/** @defgroup ETH_MSC_Registers
  * @{
  */
#define ETH_MSC_CTLR                                    ((uint32_t)0x00000100)
#define ETH_MSC_RISR                                    ((uint32_t)0x00000104)
#define ETH_MSC_TISR                                    ((uint32_t)0x00000108)
#define ETH_MSC_RIMR                                    ((uint32_t)0x0000010C)
#define ETH_MSC_TIMR                                    ((uint32_t)0x00000110)
#define ETH_MSC_SCCNT                                   ((uint32_t)0x0000014C)
#define ETH_MSC_MSCCNT                                  ((uint32_t)0x00000150)
#define ETH_MSC_TGFCNT                                  ((uint32_t)0x00000168)
#define ETH_MSC_RFCECNT                                 ((uint32_t)0x00000194)
#define ETH_MSC_RFAECNT                                 ((uint32_t)0x00000198)
#define ETH_MSC_RGUFCNT                                 ((uint32_t)0x000001C4)


/**
  * @}
  */

/** @defgroup ETH_PTP_time_update_mode
  * @{
  */
#define ETH_PTP_FINEMODE                                ((uint32_t)0x00000001)
#define ETH_PTP_COARSEMODE                              ((uint32_t)0x00000000)

/**
  * @}
  */


/** @defgroup ETH_PTP_Flags
  * @{
  */
#define ETH_PTP_FLAG_TMSARU                             ((uint32_t)0x00000020)  /*!< Addend Register Update */
#define ETH_PTP_FLAG_TMSITEN                            ((uint32_t)0x00000010)  /*!< Time Stamp Interrupt Trigger Enable */
#define ETH_PTP_FLAG_TMSSTU                             ((uint32_t)0x00000008)  /*!< Time Stamp Update */
#define ETH_PTP_FLAG_TMSSTI                             ((uint32_t)0x00000004)  /*!< Time Stamp Initialize */

/**
  * @}
  */

/** @defgroup ETH_PTP_time_sign
  * @{
  */
#define ETH_PTP_POSITIVETIME                            ((uint32_t)0x00000000)
#define ETH_PTP_NEGATIVETIME                            ((uint32_t)0x80000000)

/**
  * @brief  ETH PTP registers
  */
#define ETH_PTP_TSCTLR                                  ((uint32_t)0x00000700)
#define ETH_PTP_SSINCR                                  ((uint32_t)0x00000704)
#define ETH_PTP_TMSHR                                   ((uint32_t)0x00000708)
#define ETH_PTP_TMSLR                                   ((uint32_t)0x0000070C)
#define ETH_PTP_TMSHUR                                  ((uint32_t)0x00000710)
#define ETH_PTP_TMSLUR                                  ((uint32_t)0x00000714)
#define ETH_PTP_TSACNT                                  ((uint32_t)0x00000718)
#define ETH_PTP_ETHR                                    ((uint32_t)0x0000071C)
#define ETH_PTP_ETLR                                    ((uint32_t)0x00000720)

/**
  * @}
  */


/**
  * @}
  */


/** @defgroup ETH_Exported_Functions
  * @{
  */
void ETH_DeInit(void);
void ETH_MDIOInit(void);
uint32_t ETH_Init(ETH_InitPara *ETH_InitParaStruct, u16 PHYAddress);
void ETH_ParaInit(ETH_InitPara *ETH_InitParaStruct);
void ETH_SoftReset(void);
TypeState ETH_GetSoftResetStatus(void);
void ETH_Enable(TypeState NewValue);
uint32_t ETH_HandleTxPkt(uint8_t *pbuf, uint16_t size);
uint32_t ETH_HandleRxPkt(uint8_t *pbuf);
uint32_t ETH_GetRxPktSize(void);
void ETH_DropRxPkt(void);
/**
  * @brief  PHY
  */
uint16_t ETH_GetPHYRegisterValue(uint16_t PHYAddr, uint16_t PHYReg);
uint32_t ETH_SetPHYRegisterValue(uint16_t PHYAddr, uint16_t PHYReg, uint16_t PHYValue);
uint32_t ETH_PHYLoopBack_Enable(uint16_t PHYAddr, TypeState NewValue);

/**
  * @brief  MAC
  */
void ETH_MACTransmission_Enable(TypeState NewValue);
void ETH_MACReception_Enable(TypeState NewValue);
TypeState ETH_GetFlowControlBusyBitState(void);
void ETH_PauseFrameInit(void)  ;
void ETH_BackPressureActivation_Enable(TypeState NewValue);
TypeState ETH_GetMACBitState(uint32_t ETH_MAC_FLAG);
TypeState ETH_GetMACIntBitState(uint32_t ETH_MAC_IT);
void ETH_MACINTConfig(uint32_t ETH_MAC_IT, TypeState NewValue);
void ETH_SetMACAddress(uint32_t addr, uint8_t *buf);
void ETH_GetMACAddress(uint32_t addr, uint8_t *buf);
void ETH_MACAddressPerfectFilter_Enable(uint32_t addr, TypeState NewValue);
void ETH_MACAddressFilterConfig(uint32_t addr, uint32_t Filterfield);
void ETH_MACAddressFilterMaskBytesConfig(uint32_t addr, uint32_t addrmask);

/**
  * @brief  DMA Tx/Rx descriptors
  */
void ETH_DMATxDescChainModeInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t *pTxBuff, uint32_t TxBuffCnt);
void ETH_DMATxDescRingModeInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t *pTxBuff1, uint8_t *pTxBuff2, uint32_t TxBuffCnt);
TypeState ETH_GetDMATxDescBitState(ETH_DMADESCTypeDef *DMATxDesc, uint32_t ETH_DMATxDescFlag);
uint32_t ETH_GetDMATxDescCollisionCount(ETH_DMADESCTypeDef *DMATxDesc);
void ETH_SetDMATxDescBusyBit(ETH_DMADESCTypeDef *DMATxDesc);
void ETH_DMATxDescTransmitINTConfig(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue);
void ETH_SetDMATxDescFrameSegment(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_Segment);
void ETH_SetDMATxDescChecksumInsertion(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_Checksum);
void ETH_DMATxDescCRC_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue);
void ETH_DMATxDescEndOfRing_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue);
void ETH_DMATxDescSecondAddressChained_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue);
void ETH_DMATxDescShortFramePadding_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue);
void ETH_DMATxDescTimeStamp_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue);
void ETH_SetDMATxDescBufferSize(ETH_DMADESCTypeDef *DMATxDesc, uint32_t Buffer1Size, uint32_t Buffer2Size);
void ETH_DMARxDescChainModeInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *pRxBuff, uint32_t RxBuffCnt);
void ETH_DMARxDescRingModeInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *pRxBuff1, uint8_t *pRxBuff2, uint32_t RxBuffCnt);
TypeState ETH_GetDMARxDescBitState(ETH_DMADESCTypeDef *DMARxDesc, uint32_t ETH_DMARxDescFlag);
void ETH_SetDMARxDescBusyBit(ETH_DMADESCTypeDef *DMARxDesc);
uint32_t ETH_GetDMARxDescFrameLength(ETH_DMADESCTypeDef *DMARxDesc);
void ETH_DMARxDescReceiveINTConfig(ETH_DMADESCTypeDef *DMARxDesc, TypeState NewValue);
void ETH_DMARxDescEndOfRing_Enable(ETH_DMADESCTypeDef *DMARxDesc, TypeState NewValue);
void ETH_DMARxDescSecondAddressChained_Enable(ETH_DMADESCTypeDef *DMARxDesc, TypeState NewValue);
uint32_t ETH_GetDMARxDescBufferSize(ETH_DMADESCTypeDef *DMARxDesc, uint32_t DMARxDesc_Buffer);

/**
  * @brief  DMA
  */
TypeState ETH_GetDMABitState(uint32_t ETH_DMA_FLAG);
void ETH_DMAClearBitState(uint32_t ETH_DMA_FLAG);
TypeState ETH_GetDMAIntBitState(uint32_t ETH_DMA_IT);
void ETH_DMAClearIntBitState(uint32_t ETH_DMA_IT);
uint32_t ETH_GetTransmitProcessState(void);
uint32_t ETH_GetReceiveProcessState(void);
void ETH_CleanTransmitFIFO(void);
TypeState ETH_GetFlushTransmitFIFOStatus(void);
void ETH_DMATransmission_Enable(TypeState NewValue);
void ETH_DMAReception_Enable(TypeState NewValue);
void ETH_DMAINTConfig(uint32_t ETH_DMA_IT, TypeState NewValue);
TypeState ETH_GetDMAOverflowStatus(uint32_t ETH_DMA_Overflow);
uint32_t ETH_GetRxOverflowMissedFrameCounter(void);
uint32_t ETH_GetBufferUnavailableMissedFrameCounter(void);
uint32_t ETH_GetCurrentTxDescStartAddress(void);
uint32_t ETH_GetCurrentRxDescStartAddress(void);
uint32_t ETH_GetCurrentTxBufferAddress(void);
uint32_t ETH_GetCurrentRxBufferAddress(void);
void ETH_ResumeDMATransmission(void);
void ETH_ResumeDMAReception(void);

/**
  * @brief  WUM
  */
void ETH_ResetWakeUpFrameFilterRegister(void);
void ETH_SetWakeUpFrameFilterRegister(uint32_t *pBuffer);
void ETH_GlobalUnicastWakeUp_Enable(TypeState NewValue);
TypeState ETH_GetWUMBitState(uint32_t ETH_WUM_FLAG);
void ETH_WakeUpFrameDetection_Enable(TypeState NewValue);
void ETH_MagicPacketDetection_Enable(TypeState NewValue);
void ETH_PowerDown_Enable(TypeState NewValue);

/**
  * @brief  MSC
  */
void ETH_MSCCounterFreeze_Enable(TypeState NewValue);
void ETH_MSCResetOnRead_Enable(TypeState NewValue);
void ETH_MSCCounterRollover_Enable(TypeState NewValue);
void ETH_ResetMSCCounters(void);
void ETH_MSCINTConfig(uint32_t ETH_MSC_IT, TypeState NewValue);
TypeState ETH_GetMSCINTStatus(uint32_t ETH_MSC_IT);
uint32_t ETH_GetMSCRegister(uint32_t ETH_MSC_Register);

/**
  * @brief  PTP
  */
void ETH_PTPTimeStampAddendUpdate(void);
void ETH_PTPTimeStampIntTrigger_Enable(TypeState NewValue);
void ETH_PTPTimeStampUpdate_Enable(TypeState NewValue);
void ETH_PTPTimeStampInit(void);
void ETH_PTPUpdateModeConfig(uint32_t UpdateMode);
void ETH_PTPTimeStamp_Enable(TypeState NewValue);
TypeState ETH_GetPTPBitState(uint32_t ETH_PTP_FLAG);
void ETH_SetPTPSubSecondIncrement(uint32_t SubSecond);
void ETH_SetPTPUpdateTimeValue(uint32_t Sign, uint32_t SecondValue, uint32_t SubSecondValue);
void ETH_SetPTPTimeStampAddend(uint32_t add);
void ETH_SetPTPTargetTime(uint32_t HighReg_Value, uint32_t LowReg_Value);
uint32_t ETH_GetPTPRegister(uint32_t ETH_PTPRegister);
void ETH_DMAPTPTxDescChainModeInit(ETH_DMADESCTypeDef *DMATxDescTab, ETH_DMADESCTypeDef *DMAPTPTxDescTab,
                                   uint8_t *pTxBuff, uint32_t TxBuffCnt);
void ETH_DMAPTPRxDescChainModeInit(ETH_DMADESCTypeDef *DMARxDescTab, ETH_DMADESCTypeDef *DMAPTPRxDescTab,
                                   uint8_t *pRxBuff, uint32_t RxBuffCnt);
uint32_t ETH_HandlePTPTxPkt(uint8_t *pbuf, uint16_t size, uint32_t *PTPTxTab);
uint32_t ETH_HandlePTPRxPkt(uint8_t *pbuf, uint32_t *PTPRxTab);


#ifdef __cplusplus
}
#endif

#endif /* __GD32F10X_ETH_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
