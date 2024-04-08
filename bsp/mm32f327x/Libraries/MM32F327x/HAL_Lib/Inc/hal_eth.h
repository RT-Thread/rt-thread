////////////////////////////////////////////////////////////////////////////////
/// @file     HAL_eth.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE HAL_eth.h EXAMPLES.
/// ////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT  MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

#ifndef __HAL_ETH_H
#define __HAL_ETH_H

// Files includes
#include "types.h"
#include "mm32_device.h"
#include "hal_eth_conf.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ETH_HAL
/// @brief ETH HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ETH_Exported_Types
/// @{


////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ETH     | Header | Extra | VLAN tag | Payload   | CRC |
// Size    | 14     | 2     | 4        | 46 ~ 1500 | 4   |
#define ETH_MAX_PACKET_SIZE     1524
#define ETH_HEADER              14      ///< MAC Dest Addr 6 byte + MAC Src Addr 6 byte + Lenth/Type 2 byte
#define ETH_EXTRA               2
#define VLAN_TAG                4
#define ETH_PAYLOAD_MIN         46
#define ETH_PAYLOAD_MAX         1500
#define JUMBO_FRAME_PAYLOAD     9000

#ifndef ETH_RX_BUF_SIZE
#define ETH_RX_BUF_SIZE     ETH_MAX_PACKET_SIZE
#endif

#ifndef ETH_RX_BUF_NUM
#define ETH_RX_BUF_NUM      4
#endif

#ifndef ETH_TX_BUF_SIZE
#define ETH_TX_BUF_SIZE     ETH_MAX_PACKET_SIZE
#endif

#ifndef ETH_TX_BUF_NUM
#define ETH_TX_BUF_NUM      4
#endif

#define ETH_DMA_RDES_FL_Pos     16                                              ///< Ethernet DMA Received Frame Length Position

#define ETH_WAKEUP_REGISTER_LENGTH                          8                   ///< ETHERNET Remote Wake-up frame register length

#define ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT       17                  ///< ETHERNET Missed frames counter Shift

#define ETH_DMA_TDES_COLLISION_COUNTSHIFT                   3                   ///< ETHERNET DMA Tx descriptors Collision Count Shift
#define ETH_DMA_TDES_BUFFER2_SIZESHIFT                      11                  ///< ETHERNET DMA Tx descriptors Buffer2 Size Shift

#define ETH_DMA_RDES_FRAME_LENGTHSHIFT                      16                  ///< ETHERNET DMA Rx descriptors Frame Length Shift
#define ETH_DMA_RDES_BUFFER2_SIZESHIFT                      11                  ///< ETHERNET DMA Rx descriptors Buffer2 Size Shift

///< ETHERNET errors
#define  ETH_ERROR                                          ((u32)0)
#define  ETH_SUCCESS                                        ((u32)1)


#ifdef _HAL_ETH_C_
#define GLOBAL

#else
#define GLOBAL extern
#endif


////////////////////////////////////////////////////////////////////////////////
/// @brief ETH Init Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32    ETH_AutoNegotiation;
    __IO u32    ETH_Watchdog;
    __IO u32    ETH_Jabber;
    __IO u32    ETH_InterFrameGap;
    __IO u32    ETH_CarrierSense;
    __IO u32    ETH_Speed;
    __IO u32    ETH_ReceiveOwn;
    __IO u32    ETH_LoopbackMode;
    __IO u32    ETH_Mode;
    __IO u32    ETH_ChecksumOffload;
    __IO u32    ETH_RetryTransmission;
    __IO u32    ETH_AutomaticPadCRCStrip;
    __IO u32    ETH_BackOffLimit;
    __IO u32    ETH_DeferralCheck;
    __IO u32    ETH_ReceiveAll;
    __IO u32    ETH_SourceAddrFilter;
    __IO u32    ETH_PassControlFrames;
    __IO u32    ETH_BroadcastFramesReception;
    __IO u32    ETH_DestinationAddrFilter;
    __IO u32    ETH_PromiscuousMode;
    __IO u32    ETH_MulticastFramesFilter;
    __IO u32    ETH_UnicastFramesFilter;
    __IO u32    ETH_HashTableHigh;
    __IO u32    ETH_HashTableLow;
    __IO u32    ETH_PauseTime;
    __IO u32    ETH_ZeroQuantaPause;
    __IO u32    ETH_PauseLowThreshold;
    __IO u32    ETH_UnicastPauseFrameDetect;
    __IO u32    ETH_ReceiveFlowControl;
    __IO u32    ETH_TransmitFlowControl;
    __IO u32    ETH_VLANTagComparison;
    __IO u32    ETH_VLANTagIdentifier;
    __IO u32    ETH_DropTCPIPChecksumErrorFrame;
    __IO u32    ETH_ReceiveStoreForward;
    __IO u32    ETH_FlushReceivedFrame;
    __IO u32    ETH_TransmitStoreForward;
    __IO u32    ETH_TransmitThresholdControl;
    __IO u32    ETH_ForwardErrorFrames;
    __IO u32    ETH_ForwardUndersizedGoodFrames;
    __IO u32    ETH_ReceiveThresholdControl;
    __IO u32    ETH_SecondFrameOperate;
    __IO u32    ETH_AddressAlignedBeats;
    __IO u32    ETH_FixedBurst;
    __IO u32    ETH_RxDMABurstLength;
    __IO u32    ETH_TxDMABurstLength;
    __IO u32    ETH_DescriptorSkipLength;
    __IO u32    ETH_DMAArbitration;
} ETH_InitTypeDef;

typedef struct {
    __IO u32   CS;                                                              ///< Control and Status
    __IO u32   BL;                                                              ///< Buffer1, Buffer2 lengths
    __IO u32   BUF1ADDR;                                                        ///< Buffer1 address pointer
    __IO u32   BUF2NDADDR;                                                      ///< Buffer2 or next descriptor address pointer

#ifdef USE_ENHANCED_DMA_DESCRIPTORS                                             ///< Enhanced ETHERNET DMA PTP Descriptors
    __IO u32        ExtendedStatus;                                             ///< Extended status for PTP receive descriptor
    __IO u32        Reserved1;                                                  ///< Reserved
    __IO u32        TimeStampLow;                                               ///< Time Stamp Low value for transmit and receive
    __IO u32        TimeStampHigh;                                              ///< Time Stamp High value for transmit and receive
#endif
} ETH_DMADESCTypeDef;

typedef struct {
    __IO u32                         len;
    __IO u32                         buf;
    __IO ETH_DMADESCTypeDef*    ptrDesc;
} FrameTypeDef;

typedef struct  {
    __IO ETH_DMADESCTypeDef*    ptrFS_Rx_Desc;                                  ///< First Segment Rx Desc
    __IO ETH_DMADESCTypeDef*    ptrLS_Rx_Desc;                                  ///< Last Segment Rx Desc
    __IO u32               cnt;                                            ///< Segment count
} ETH_DMA_Rx_Frame_infos;



#define ETH_DMA_TDES_OWN                     ((u32)0x80000000)             ///< OWN bit: descriptor is owned by DMA engine
#define ETH_DMA_TDES_ES                      ((u32)0x00008000)             ///< Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF || JT
#define ETH_DMA_TDES_JT                      ((u32)0x00004000)             ///< Jabber Timeout
#define ETH_DMA_TDES_FF                      ((u32)0x00002000)             ///< Frame Flushed: DMA/MTL flushed the frame due to SW flush
#define ETH_DMA_TDES_LCA                     ((u32)0x00000800)             ///< Loss of Carrier: carrier lost during transmission
#define ETH_DMA_TDES_NC                      ((u32)0x00000400)             ///< No Carrier: no carrier signal from the transceiver
#define ETH_DMA_TDES_LCO                     ((u32)0x00000200)             ///< Late Collision: transmission aborted due to collision
#define ETH_DMA_TDES_EC                      ((u32)0x00000100)             ///< Excessive Collision: transmission aborted after 16 collisions
#define ETH_DMA_TDES_VF                      ((u32)0x00000080)             ///< VLAN Frame
#define ETH_DMA_TDES_CC                      ((u32)0x00000078)             ///< Collision Count
#define ETH_DMA_TDES_ED                      ((u32)0x00000004)             ///< Excessive Deferral
#define ETH_DMA_TDES_UF                      ((u32)0x00000002)             ///< Underflow Error: late data arrival from the memory
#define ETH_DMA_TDES_DB                      ((u32)0x00000001)             ///< Deferred Bit

#define ETH_DMA_TDES_IC                      ((u32)0x80000000)             ///< Interrupt on Completion
#define ETH_DMA_TDES_LS                      ((u32)0x40000000)             ///< Last Segment
#define ETH_DMA_TDES_FS                      ((u32)0x20000000)             ///< First Segment
#define ETH_DMA_TDES_DC                      ((u32)0x04000000)             ///< Disable CRC
#define ETH_DMA_TDES_TER                     ((u32)0x02000000)             ///< Transmit end of ring
#define ETH_DMA_TDES_TCH                     ((u32)0x01000000)             ///< Second Address Chained
#define ETH_DMA_TDES_DP                      ((u32)0x00800000)             ///< Disable Padding
#define ETH_DMA_TDES_TBS2                    ((u32)0x003FF800)             ///< Transmit Buffer 2 Size
#define ETH_DMA_TDES_TBS1                    ((u32)0x000007FF)             ///< Transmit Buffer 1 Size

#define ETH_DMA_TDES_B1AP                    ((u32)0xFFFFFFFF)             ///< Buffer 1 Address Pointer

#define ETH_DMA_TDES_B2AP                    ((u32)0xFFFFFFFF)             ///< Buffer 2 Address Pointer

#if defined(USE_ENHANCED_DMA_DESCRIPTORS)
#define ETH_DMA_PTP_TDES_TTSL                ((u32)0xFFFFFFFF)              ///< Transmit Time Stamp Low
#define ETH_DMA_PTP_TDES_TTSH                ((u32)0xFFFFFFFF)              ///< Transmit Time Stamp High
#endif

#define ETH_DMA_RDES_OWN                     ((u32)0x80000000)             ///< OWN bit: descriptor is owned by DMA engine
#define ETH_DMA_RDES_AFM                     ((u32)0x40000000)             ///< DA Filter Fail for the rx frame
#define ETH_DMA_RDES_FL                      ((u32)0x3FFF0000)             ///< Receive descriptor frame length
#define ETH_DMA_RDES_ES                      ((u32)0x00008000)             ///< Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE
#define ETH_DMA_RDES_DE                      ((u32)0x00004000)             ///< Descriptor error: no more descriptors for receive frame
#define ETH_DMA_RDES_SAF                     ((u32)0x00002000)             ///< SA Filter Fail for the received frame
#define ETH_DMA_RDES_LE                      ((u32)0x00001000)             ///< Frame size not matching with length field
#define ETH_DMA_RDES_OE                      ((u32)0x00000800)             ///< Overflow Error: Frame was damaged due to buffer overflow
#define ETH_DMA_RDES_VLAN                    ((u32)0x00000400)             ///< VLAN Tag: received frame is a VLAN frame
#define ETH_DMA_RDES_FS                      ((u32)0x00000200)             ///< First descriptor of the frame
#define ETH_DMA_RDES_LS                      ((u32)0x00000100)             ///< Last descriptor of the frame
#define ETH_DMA_RDES_IPV4HCE                 ((u32)0x00000080)             ///< IPC Checksum Error: Rx Ipv4 header checksum error
#define ETH_DMA_RDES_LC                      ((u32)0x00000040)             ///< Late collision occurred during reception
#define ETH_DMA_RDES_FT                      ((u32)0x00000020)             ///< Frame type - Ethernet, otherwise 802.3
#define ETH_DMA_RDES_RWT                     ((u32)0x00000010)             ///< Receive Watchdog Timeout: watchdog timer expired during reception
#define ETH_DMA_RDES_RE                      ((u32)0x00000008)             ///< Receive error: error reported by MII interface
#define ETH_DMA_RDES_DBE                     ((u32)0x00000004)             ///< Dribble bit error: frame contains non int multiple of 8 bits
#define ETH_DMA_RDES_CE                      ((u32)0x00000002)             ///< CRC error
#define ETH_DMA_RDES_MAMPCE                  ((u32)0x00000001)             ///< Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error

#define ETH_DMA_RDES_DIC                     ((u32)0x80000000)             ///< Disable Interrupt on Completion
#define ETH_DMA_RDES_RER                     ((u32)0x02000000)             ///< Receive End of Ring
#define ETH_DMA_RDES_RCH                     ((u32)0x01000000)             ///< Second Address Chained
#define ETH_DMA_RDES_RBS2                    ((u32)0x003FF800)             ///< Receive Buffer2 Size
#define ETH_DMA_RDES_RBS1                    ((u32)0x000007FF)             ///< Receive Buffer1 Size

#define ETH_DMA_RDES_B1AP                    ((u32)0xFFFFFFFF)             ///< Buffer 1 Address Pointer

#define ETH_DMA_RDES_B2AP                    ((u32)0xFFFFFFFF)             ///< Buffer 2 Address Pointer


#if defined(USE_ENHANCED_DMA_DESCRIPTORS)
#define ETH_DMA_PTP_RDES_PTPV                            ((u32)0x00002000)  ///< PTP Version
#define ETH_DMA_PTP_RDES_PTPFT                           ((u32)0x00001000)  ///< PTP Frame Type
#define ETH_DMA_PTP_RDES_PTPMT                           ((u32)0x00000F00)  ///< PTP Message Type
#define ETH_DMA_PTP_RDES_PTPMT_Sync                      ((u32)0x00000100)  ///< SYNC message (all clock types)
#define ETH_DMA_PTP_RDES_PTPMT_FollowUp                  ((u32)0x00000200)  ///< FollowUp message (all clock types)
#define ETH_DMA_PTP_RDES_PTPMT_DelayReq                  ((u32)0x00000300)  ///< DelayReq message (all clock types)
#define ETH_DMA_PTP_RDES_PTPMT_DelayResp                 ((u32)0x00000400)  ///< DelayResp message (all clock types)
#define ETH_DMA_PTP_RDES_PTPMT_PdelayReq_Announce        ((u32)0x00000500)  ///< PdelayReq message (peer-to-peer transparent clock) or Announce message (Ordinary or Boundary clock)
#define ETH_DMA_PTP_RDES_PTPMT_PdelayResp_Manag          ((u32)0x00000600)  ///< PdelayResp message (peer-to-peer transparent clock) or Management message (Ordinary or Boundary clock)
#define ETH_DMA_PTP_RDES_PTPMT_PdelayRespFollowUp_Signal ((u32)0x00000700)  ///< PdelayRespFollowUp message (peer-to-peer transparent clock) or Signaling message (Ordinary or Boundary clock)
#define ETH_DMA_PTP_RDES_IPV6PR                          ((u32)0x00000080)  ///< IPv6 Packet Received
#define ETH_DMA_PTP_RDES_IPV4PR                          ((u32)0x00000040)  ///< IPv4 Packet Received
#define ETH_DMA_PTP_RDES_IPCB                            ((u32)0x00000020)  ///< IP Checksum Bypassed
#define ETH_DMA_PTP_RDES_IPPE                            ((u32)0x00000010)  ///< IP Payload Error
#define ETH_DMA_PTP_RDES_IPHE                            ((u32)0x00000008)  ///< IP Header Error
#define ETH_DMA_PTP_RDES_IPPT                            ((u32)0x00000007)  ///< IP Payload Type
#define ETH_DMA_PTP_RDES_IPPT_UDP                        ((u32)0x00000001)  ///< UDP payload encapsulated in the IP datagram
#define ETH_DMA_PTP_RDES_IPPT_TCP                        ((u32)0x00000002)  ///< TCP payload encapsulated in the IP datagram
#define ETH_DMA_PTP_RDES_IPPT_ICMP                       ((u32)0x00000003)  ///< ICMP payload encapsulated in the IP datagram



#define ETH_DMA_PTP_RDES_TTSL               ((u32)0xFFFFFFFF)              ///< Receive Time Stamp Low
#define ETH_DMA_PTP_RDES_TTSH               ((u32)0xFFFFFFFF)              ///< Receive Time Stamp High
#endif

////////////////////////////////////////////////////////////////////////////////
#define PHY_READ_TIMEOUT                    ((u32)0x0004FFFF)
#define PHY_WRITE_TIMEOUT                   ((u32)0x0004FFFF)

#define PHY_BCR                             0                                   ///< Transceiver Basic Control Register
#define PHY_BSR                             1                                   ///< Transceiver Basic Status Register

#define PHY_Reset                           ((u16)0x8000)                  ///< PHY Reset
#define PHY_Loopback                        ((u16)0x4000)                  ///< Select loop-back mode
#define PHY_FULLDUPLEX_100M                 ((u16)0x2100)                  ///< Set the full-duplex mode at 100 Mb/s
#define PHY_HALFDUPLEX_100M                 ((u16)0x2000)                  ///< Set the half-duplex mode at 100 Mb/s
#define PHY_FULLDUPLEX_10M                  ((u16)0x0100)                  ///< Set the full-duplex mode at 10 Mb/s
#define PHY_HALFDUPLEX_10M                  ((u16)0x0000)                  ///< Set the half-duplex mode at 10 Mb/s
#define PHY_AutoNegotiation                 ((u16)0x1000)                  ///< Enable auto-negotiation function
#define PHY_Restart_AutoNegotiation         ((u16)0x0200)                  ///< Restart auto-negotiation function
#define PHY_Powerdown                       ((u16)0x0800)                  ///< Select the power down mode
#define PHY_Isolate                         ((u16)0x0400)                  ///< Isolate PHY from MII

#define PHY_AutoNego_Complete               ((u16)0x0020)                  ///< Auto-Negotiation process completed
#define PHY_Linked_Status                   ((u16)0x0004)                  ///< Valid link established
#define PHY_Jabber_detection                ((u16)0x0002)                  ///< Jabber condition detected

////////////////////////////////////////////////////////////////////////////////
#define ETH_AutoNegotiation_Enable          ((u32)0x00000001)
#define ETH_AutoNegotiation_Disable         ((u32)0x00000000)

#define ETH_Watchdog_Enable                 ((u32)0x00000000)
#define ETH_Watchdog_Disable                ((u32)0x00800000)

#define ETH_Jabber_Enable                   ((u32)0x00000000)
#define ETH_Jabber_Disable                  ((u32)0x00400000)

#define ETH_InterFrameGap_96Bit             ((u32)0x00000000)              ///< minimum IFG between frames during transmission is 96Bit
#define ETH_InterFrameGap_88Bit             ((u32)0x00020000)              ///< minimum IFG between frames during transmission is 88Bit
#define ETH_InterFrameGap_80Bit             ((u32)0x00040000)              ///< minimum IFG between frames during transmission is 80Bit
#define ETH_InterFrameGap_72Bit             ((u32)0x00060000)              ///< minimum IFG between frames during transmission is 72Bit
#define ETH_InterFrameGap_64Bit             ((u32)0x00080000)              ///< minimum IFG between frames during transmission is 64Bit
#define ETH_InterFrameGap_56Bit             ((u32)0x000A0000)              ///< minimum IFG between frames during transmission is 56Bit
#define ETH_InterFrameGap_48Bit             ((u32)0x000C0000)              ///< minimum IFG between frames during transmission is 48Bit
#define ETH_InterFrameGap_40Bit             ((u32)0x000E0000)              ///< minimum IFG between frames during transmission is 40Bit

#define ETH_CarrierSense_Enable             ((u32)0x00000000)
#define ETH_CarrierSense_Disable            ((u32)0x00010000)

#define ETH_Speed_10M                       ((u32)0x00000000)
#define ETH_Speed_100M                      ((u32)0x00004000)

#define ETH_ReceiveOwn_Enable               ((u32)0x00000000)
#define ETH_ReceiveOwn_Disable              ((u32)0x00002000)

#define ETH_LoopbackMode_Enable             ((u32)0x00001000)
#define ETH_LoopbackMode_Disable            ((u32)0x00000000)

#define ETH_Mode_FullDuplex                 ((u32)0x00000800)
#define ETH_Mode_HalfDuplex                 ((u32)0x00000000)

#define ETH_ChecksumOffload_Enable          ((u32)0x00000400)
#define ETH_ChecksumOffload_Disable         ((u32)0x00000000)

#define ETH_RetryTransmission_Enable        ((u32)0x00000000)
#define ETH_RetryTransmission_Disable       ((u32)0x00000200)

#define ETH_AutomaticPadCRCStrip_Enable     ((u32)0x00000080)
#define ETH_AutomaticPadCRCStrip_Disable    ((u32)0x00000000)

#define ETH_BackOffLimit_10                 ((u32)0x00000000)
#define ETH_BackOffLimit_8                  ((u32)0x00000020)
#define ETH_BackOffLimit_4                  ((u32)0x00000040)
#define ETH_BackOffLimit_1                  ((u32)0x00000060)

#define ETH_DeferralCheck_Enable            ((u32)0x00000010)
#define ETH_DeferralCheck_Disable           ((u32)0x00000000)

#define ETH_ReceiveAll_Enable               ((u32)0x80000000)
#define ETH_ReceiveAll_Disable              ((u32)0x00000000)

#define ETH_SourceAddrFilter_Normal_Enable  ((u32)0x00000200)
#define ETH_SourceAddrFilter_Inverse_Enable ((u32)0x00000300)
#define ETH_SourceAddrFilter_Disable        ((u32)0x00000000)

#define ETH_PassControlFrames_BlockAll                  ((u32)0x00000040)  ///< MAC filters all control frames from reaching the application
#define ETH_PassControlFrames_ForwardAll                ((u32)0x00000080)  ///< MAC forwards all control frames to application even if they fail the Address Filter
#define ETH_PassControlFrames_ForwardPassedAddrFilter   ((u32)0x000000C0)  ///< MAC forwards control frames that pass the Address Filter.

#define ETH_BroadcastFramesReception_Enable             ((u32)0x00000000)
#define ETH_BroadcastFramesReception_Disable            ((u32)0x00000020)

#define ETH_DestinationAddrFilter_Normal                ((u32)0x00000000)
#define ETH_DestinationAddrFilter_Inverse               ((u32)0x00000008)

#define ETH_PromiscuousMode_Enable                      ((u32)0x00000001)
#define ETH_PromiscuousMode_Disable                     ((u32)0x00000000)

#define ETH_MulticastFramesFilter_PerfectHashTable      ((u32)0x00000404)
#define ETH_MulticastFramesFilter_HashTable             ((u32)0x00000004)
#define ETH_MulticastFramesFilter_Perfect               ((u32)0x00000000)
#define ETH_MulticastFramesFilter_None                  ((u32)0x00000010)

#define ETH_UnicastFramesFilter_PerfectHashTable        ((u32)0x00000402)
#define ETH_UnicastFramesFilter_HashTable               ((u32)0x00000002)
#define ETH_UnicastFramesFilter_Perfect                 ((u32)0x00000000)

#define ETH_ZeroQuantaPause_Enable                      ((u32)0x00000000)
#define ETH_ZeroQuantaPause_Disable                     ((u32)0x00000080)

#define ETH_PauseLowThreshold_Minus4                    ((u32)0x00000000)              ///< Pause time minus 4 slot times
#define ETH_PauseLowThreshold_Minus28                   ((u32)0x00000010)              ///< Pause time minus 28 slot times
#define ETH_PauseLowThreshold_Minus144                  ((u32)0x00000020)              ///< Pause time minus 144 slot times
#define ETH_PauseLowThreshold_Minus256                  ((u32)0x00000030)              ///< Pause time minus 256 slot times

#define ETH_UnicastPauseFrameDetect_Enable              ((u32)0x00000008)
#define ETH_UnicastPauseFrameDetect_Disable             ((u32)0x00000000)

#define ETH_ReceiveFlowControl_Enable                   ((u32)0x00000004)
#define ETH_ReceiveFlowControl_Disable                  ((u32)0x00000000)

#define ETH_TransmitFlowControl_Enable                  ((u32)0x00000002)
#define ETH_TransmitFlowControl_Disable                 ((u32)0x00000000)

#define ETH_VLANTagComparison_12Bit                     ((u32)0x00010000)
#define ETH_VLANTagComparison_16Bit                     ((u32)0x00000000)

#define ETH_MAC_FLAG_TST                                ((u32)0x00000200)              ///< Time stamp trigger flag (on MAC)
#define ETH_MAC_FLAG_MMCT                               ((u32)0x00000040)              ///< MMC transmit flag
#define ETH_MAC_FLAG_MMCR                               ((u32)0x00000020)              ///< MMC receive flag
#define ETH_MAC_FLAG_MMC                                ((u32)0x00000010)              ///< MMC flag (on MAC)
#define ETH_MAC_FLAG_PMT                                ((u32)0x00000008)              ///< PMT flag (on MAC)

#define ETH_MAC_IT_TST                                  ((u32)0x00000200)              ///< Time stamp trigger interrupt (on MAC)
#define ETH_MAC_IT_MMCT                                 ((u32)0x00000040)              ///< MMC transmit interrupt
#define ETH_MAC_IT_MMCR                                 ((u32)0x00000020)              ///< MMC receive interrupt
#define ETH_MAC_IT_MMC                                  ((u32)0x00000010)              ///< MMC interrupt (on MAC)
#define ETH_MAC_IT_PMT                                  ((u32)0x00000008)              ///< PMT interrupt (on MAC)

#define ETH_MAC_Address0                                ((u32)0x00000000)
#define ETH_MAC_Address1                                ((u32)0x00000008)
#define ETH_MAC_Address2                                ((u32)0x00000010)
#define ETH_MAC_Address3                                ((u32)0x00000018)

#define ETH_MAC_AddressFilter_SA                        ((u32)0x00000000)
#define ETH_MAC_AddressFilter_DA                        ((u32)0x00000008)

#define ETH_MAC_AddressMask_Byte6                       ((u32)0x20000000)              ///< Mask MAC Address high reg bits [15:8]
#define ETH_MAC_AddressMask_Byte5                       ((u32)0x10000000)              ///< Mask MAC Address high reg bits [7:0]
#define ETH_MAC_AddressMask_Byte4                       ((u32)0x08000000)              ///< Mask MAC Address low reg bits [31:24]
#define ETH_MAC_AddressMask_Byte3                       ((u32)0x04000000)              ///< Mask MAC Address low reg bits [23:16]
#define ETH_MAC_AddressMask_Byte2                       ((u32)0x02000000)              ///< Mask MAC Address low reg bits [15:8]
#define ETH_MAC_AddressMask_Byte1                       ((u32)0x01000000)              ///< Mask MAC Address low reg bits [70]

////////////////////////////////////////////////////////////////////////////////
#define ETH_DMA_TDES_LastSegment                        ((u32)0x40000000)              ///< Last Segment
#define ETH_DMA_TDES_FirstSegment                       ((u32)0x20000000)              ///< First Segment

#define ETH_DMA_TDES_ChecksumByPass                     ((u32)0x00000000)      ///< Checksum engine bypass
#define ETH_DMA_TDES_ChecksumIPV4Header                 ((u32)0x00400000)      ///< IPv4 header checksum insertion
#define ETH_DMA_TDES_ChecksumTCPUDPICMPSegment          ((u32)0x00800000)      ///< TCP/UDP/ICMP checksum insertion. Pseudo header checksum is assumed to be present
#define ETH_DMA_TDES_ChecksumTCPUDPICMPFull             ((u32)0x00C00000)      ///< TCP/UDP/ICMP checksum fully in hardware including pseudo header

#define ETH_DMA_RDES_Buffer1                            ((u32)0x00000000)              ///< DMA Rx Desc Buffer1
#define ETH_DMA_RDES_Buffer2                            ((u32)0x00000001)              ///< DMA Rx Desc Buffer2

#define ETH_DropTCPIPChecksumErrorFrame_Enable          ((u32)0x00000000)
#define ETH_DropTCPIPChecksumErrorFrame_Disable         ((u32)0x04000000)

#define ETH_ReceiveStoreForward_Enable                  ((u32)0x02000000)
#define ETH_ReceiveStoreForward_Disable                 ((u32)0x00000000)

#define ETH_FlushReceivedFrame_Enable                   ((u32)0x00000000)
#define ETH_FlushReceivedFrame_Disable                  ((u32)0x01000000)

#define ETH_TransmitStoreForward_Enable                 ((u32)0x00200000)
#define ETH_TransmitStoreForward_Disable                ((u32)0x00000000)

#define ETH_TransmitThresholdControl_64Bytes            ((u32)0x00000000)      ///< threshold level of the MTL Transmit FIFO is 64 Bytes
#define ETH_TransmitThresholdControl_128Bytes           ((u32)0x00004000)      ///< threshold level of the MTL Transmit FIFO is 128 Bytes
#define ETH_TransmitThresholdControl_192Bytes           ((u32)0x00008000)      ///< threshold level of the MTL Transmit FIFO is 192 Bytes
#define ETH_TransmitThresholdControl_256Bytes           ((u32)0x0000C000)      ///< threshold level of the MTL Transmit FIFO is 256 Bytes
#define ETH_TransmitThresholdControl_40Bytes            ((u32)0x00010000)      ///< threshold level of the MTL Transmit FIFO is 40 Bytes
#define ETH_TransmitThresholdControl_32Bytes            ((u32)0x00014000)      ///< threshold level of the MTL Transmit FIFO is 32 Bytes
#define ETH_TransmitThresholdControl_24Bytes            ((u32)0x00018000)      ///< threshold level of the MTL Transmit FIFO is 24 Bytes
#define ETH_TransmitThresholdControl_16Bytes            ((u32)0x0001C000)      ///< threshold level of the MTL Transmit FIFO is 16 Bytes

#define ETH_ForwardErrorFrames_Enable                   ((u32)0x00000080)
#define ETH_ForwardErrorFrames_Disable                  ((u32)0x00000000)

#define ETH_ForwardUndersizedGoodFrames_Enable          ((u32)0x00000040)
#define ETH_ForwardUndersizedGoodFrames_Disable         ((u32)0x00000000)

#define ETH_ReceiveThresholdControl_64Bytes             ((u32)0x00000000)      ///< threshold level of the MTL Receive FIFO is 64 Bytes
#define ETH_ReceiveThresholdControl_32Bytes             ((u32)0x00000008)      ///< threshold level of the MTL Receive FIFO is 32 Bytes
#define ETH_ReceiveThresholdControl_96Bytes             ((u32)0x00000010)      ///< threshold level of the MTL Receive FIFO is 96 Bytes
#define ETH_ReceiveThresholdControl_128Bytes            ((u32)0x00000018)      ///< threshold level of the MTL Receive FIFO is 128 Bytes

#define ETH_SecondFrameOperate_Enable       ((u32)0x00000004)
#define ETH_SecondFrameOperate_Disable      ((u32)0x00000000)

#define ETH_AddressAlignedBeats_Enable      ((u32)0x02000000)
#define ETH_AddressAlignedBeats_Disable     ((u32)0x00000000)

#define ETH_FixedBurst_Enable               ((u32)0x00010000)
#define ETH_FixedBurst_Disable              ((u32)0x00000000)

#define ETH_RxDMABurstLength_1Beat          ((u32)0x00020000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 1
#define ETH_RxDMABurstLength_2Beat          ((u32)0x00040000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 2
#define ETH_RxDMABurstLength_4Beat          ((u32)0x00080000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 4
#define ETH_RxDMABurstLength_8Beat          ((u32)0x00100000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 8
#define ETH_RxDMABurstLength_16Beat         ((u32)0x00200000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 16
#define ETH_RxDMABurstLength_32Beat         ((u32)0x00400000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 32
#define ETH_RxDMABurstLength_4xPBL_4Beat    ((u32)0x01020000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 4
#define ETH_RxDMABurstLength_4xPBL_8Beat    ((u32)0x01040000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 8
#define ETH_RxDMABurstLength_4xPBL_16Beat   ((u32)0x01080000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 16
#define ETH_RxDMABurstLength_4xPBL_32Beat   ((u32)0x01100000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 32
#define ETH_RxDMABurstLength_4xPBL_64Beat   ((u32)0x01200000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 64
#define ETH_RxDMABurstLength_4xPBL_128Beat  ((u32)0x01400000)              ///< maximum number of beats to be transferred in one RxDMA transaction is 128

#define ETH_TxDMABurstLength_1Beat          ((u32)0x00000100)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 1
#define ETH_TxDMABurstLength_2Beat          ((u32)0x00000200)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 2
#define ETH_TxDMABurstLength_4Beat          ((u32)0x00000400)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4
#define ETH_TxDMABurstLength_8Beat          ((u32)0x00000800)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8
#define ETH_TxDMABurstLength_16Beat         ((u32)0x00001000)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16
#define ETH_TxDMABurstLength_32Beat         ((u32)0x00002000)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32
#define ETH_TxDMABurstLength_4xPBL_4Beat    ((u32)0x01000100)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4
#define ETH_TxDMABurstLength_4xPBL_8Beat    ((u32)0x01000200)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8
#define ETH_TxDMABurstLength_4xPBL_16Beat   ((u32)0x01000400)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16
#define ETH_TxDMABurstLength_4xPBL_32Beat   ((u32)0x01000800)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32
#define ETH_TxDMABurstLength_4xPBL_64Beat   ((u32)0x01001000)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 64
#define ETH_TxDMABurstLength_4xPBL_128Beat  ((u32)0x01002000)              ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 128

#define ETH_DMAArbitration_RoundRobin_RxTx_1_1      ((u32)0x00000000)
#define ETH_DMAArbitration_RoundRobin_RxTx_2_1      ((u32)0x00004000)
#define ETH_DMAArbitration_RoundRobin_RxTx_3_1      ((u32)0x00008000)
#define ETH_DMAArbitration_RoundRobin_RxTx_4_1      ((u32)0x0000C000)
#define ETH_DMAArbitration_RxPriorTx                ((u32)0x00000002)

#define ETH_DMA_FLAG_TST                    ((u32)0x20000000)              ///< Time-stamp trigger interrupt (on DMA)
#define ETH_DMA_FLAG_PMT                    ((u32)0x10000000)              ///< PMT interrupt (on DMA)
#define ETH_DMA_FLAG_MMC                    ((u32)0x08000000)              ///< MMC interrupt (on DMA)
#define ETH_DMA_FLAG_DataTransferError      ((u32)0x00800000)              ///< Error bits 0-Rx DMA, 1-Tx DMA
#define ETH_DMA_FLAG_ReadWriteError         ((u32)0x01000000)              ///< Error bits 0-write trnsf, 1-read transfr
#define ETH_DMA_FLAG_AccessError            ((u32)0x02000000)              ///< Error bits 0-data buffer, 1-desc. access
#define ETH_DMA_FLAG_NIS                    ((u32)0x00010000)              ///< Normal interrupt summary flag
#define ETH_DMA_FLAG_AIS                    ((u32)0x00008000)              ///< Abnormal interrupt summary flag
#define ETH_DMA_FLAG_ER                     ((u32)0x00004000)              ///< Early receive flag
#define ETH_DMA_FLAG_FBE                    ((u32)0x00002000)              ///< Fatal bus error flag
#define ETH_DMA_FLAG_ET                     ((u32)0x00000400)              ///< Early transmit flag
#define ETH_DMA_FLAG_RWT                    ((u32)0x00000200)              ///< Receive watchdog timeout flag
#define ETH_DMA_FLAG_RPS                    ((u32)0x00000100)              ///< Receive process stopped flag
#define ETH_DMA_FLAG_RBU                    ((u32)0x00000080)              ///< Receive buffer unavailable flag
#define ETH_DMA_FLAG_R                      ((u32)0x00000040)              ///< Receive flag
#define ETH_DMA_FLAG_TU                     ((u32)0x00000020)              ///< Underflow flag
#define ETH_DMA_FLAG_RO                     ((u32)0x00000010)              ///< Overflow flag
#define ETH_DMA_FLAG_TJT                    ((u32)0x00000008)              ///< Transmit jabber timeout flag
#define ETH_DMA_FLAG_TBU                    ((u32)0x00000004)              ///< Transmit buffer unavailable flag
#define ETH_DMA_FLAG_TPS                    ((u32)0x00000002)              ///< Transmit process stopped flag
#define ETH_DMA_FLAG_T                      ((u32)0x00000001)              ///< Transmit flag

#define ETH_DMA_IT_TST                      ((u32)0x20000000)              ///< Time-stamp trigger interrupt (on DMA)
#define ETH_DMA_IT_PMT                      ((u32)0x10000000)              ///< PMT interrupt (on DMA)
#define ETH_DMA_IT_MMC                      ((u32)0x08000000)              ///< MMC interrupt (on DMA)
#define ETH_DMA_IT_NIS                      ((u32)0x00010000)              ///< Normal interrupt summary
#define ETH_DMA_IT_AIS                      ((u32)0x00008000)              ///< Abnormal interrupt summary
#define ETH_DMA_IT_ER                       ((u32)0x00004000)              ///< Early receive interrupt
#define ETH_DMA_IT_FBE                      ((u32)0x00002000)              ///< Fatal bus error interrupt
#define ETH_DMA_IT_ET                       ((u32)0x00000400)              ///< Early transmit interrupt
#define ETH_DMA_IT_RWT                      ((u32)0x00000200)              ///< Receive watchdog timeout interrupt
#define ETH_DMA_IT_RPS                      ((u32)0x00000100)              ///< Receive process stopped interrupt
#define ETH_DMA_IT_RBU                      ((u32)0x00000080)              ///< Receive buffer unavailable interrupt
#define ETH_DMA_IT_R                        ((u32)0x00000040)              ///< Receive interrupt
#define ETH_DMA_IT_TU                       ((u32)0x00000020)              ///< Underflow interrupt
#define ETH_DMA_IT_RO                       ((u32)0x00000010)              ///< Overflow interrupt
#define ETH_DMA_IT_TJT                      ((u32)0x00000008)              ///< Transmit jabber timeout interrupt
#define ETH_DMA_IT_TBU                      ((u32)0x00000004)              ///< Transmit buffer unavailable interrupt
#define ETH_DMA_IT_TPS                      ((u32)0x00000002)              ///< Transmit process stopped interrupt
#define ETH_DMA_IT_T                        ((u32)0x00000001)              ///< Transmit interrupt

#define ETH_DMA_TransmitProcess_Stopped     ((u32)0x00000000)              ///< Stopped - Reset or Stop Tx Command issued
#define ETH_DMA_TransmitProcess_Fetching    ((u32)0x00100000)              ///< Running - fetching the Tx descriptor
#define ETH_DMA_TransmitProcess_Waiting     ((u32)0x00200000)              ///< Running - waiting for status
#define ETH_DMA_TransmitProcess_Reading     ((u32)0x00300000)              ///< Running - reading the data from host memory
#define ETH_DMA_TransmitProcess_Suspended   ((u32)0x00600000)              ///< Suspended - Tx Descriptor unavailable
#define ETH_DMA_TransmitProcess_Closing     ((u32)0x00700000)              ///< Running - closing Rx descriptor

#define ETH_DMA_ReceiveProcess_Stopped      ((u32)0x00000000)              ///< Stopped - Reset or Stop Rx Command issued
#define ETH_DMA_ReceiveProcess_Fetching     ((u32)0x00020000)              ///< Running - fetching the Rx descriptor
#define ETH_DMA_ReceiveProcess_Waiting      ((u32)0x00060000)              ///< Running - waiting for packet
#define ETH_DMA_ReceiveProcess_Suspended    ((u32)0x00080000)              ///< Suspended - Rx Descriptor unavailable
#define ETH_DMA_ReceiveProcess_Closing      ((u32)0x000A0000)              ///< Running - closing descriptor
#define ETH_DMA_ReceiveProcess_Queuing      ((u32)0x000E0000)              ///< Running - queuing the receive frame into host memory

#define ETH_DMA_Overflow_RxFIFOCounter      ((u32)0x10000000)              ///< Overflow bit for FIFO overflow counter
#define ETH_DMA_Overflow_MissedFrameCounter ((u32)0x00010000)              ///< Overflow bit for missed frame counter

////////////////////////////////////////////////////////////////////////////////
#define ETH_PMT_FLAG_WUFFRPR                ((u32)0x80000000)              ///< Wake-Up Frame Filter Register Pointer Reset
#define ETH_PMT_FLAG_WUFR                   ((u32)0x00000040)              ///< Wake-Up Frame Received
#define ETH_PMT_FLAG_MPR                    ((u32)0x00000020)              ///< Magic Packet Received

////////////////////////////////////////////////////////////////////////////////
#define ETH_MMC_IT_TGF                      ((u32)0x00200000)              ///< When Tx good frame counter reaches half the maximum value
#define ETH_MMC_IT_TGFMSC                   ((u32)0x00008000)              ///< When Tx good multi col counter reaches half the maximum value
#define ETH_MMC_IT_TGFSC                    ((u32)0x00004000)              ///< When Tx good single col counter reaches half the maximum value

#define ETH_MMC_IT_RGUF                     ((u32)0x10020000)              ///< When Rx good unicast frames counter reaches half the maximum value
#define ETH_MMC_IT_RFAE                     ((u32)0x10000040)              ///< When Rx alignment error counter reaches half the maximum value
#define ETH_MMC_IT_RFCE                     ((u32)0x10000020)              ///< When Rx crc error counter reaches half the maximum value

#define ETH_MMCCR                           ((u32)0x00000100)              ///< MMC CR register
#define ETH_MMCRIR                          ((u32)0x00000104)              ///< MMC RIR register
#define ETH_MMCTIR                          ((u32)0x00000108)              ///< MMC TIR register
#define ETH_MMCRIMR                         ((u32)0x0000010C)              ///< MMC RIMR register
#define ETH_MMCTIMR                         ((u32)0x00000110)              ///< MMC TIMR register
#define ETH_MMCTGFSCCR                      ((u32)0x0000014C)              ///< MMC TGFSCCR register
#define ETH_MMCTGFMSCCR                     ((u32)0x00000150)              ///< MMC TGFMSCCR register
#define ETH_MMCTGFCR                        ((u32)0x00000168)              ///< MMC TGFCR register
#define ETH_MMCRFCECR                       ((u32)0x00000194)              ///< MMC RFCECR register
#define ETH_MMCRFAECR                       ((u32)0x00000198)              ///< MMC RFAECR register
#define ETH_MMCRGUFCR                       ((u32)0x000001C4)              ///< MMC RGUFCR register

////////////////////////////////////////////////////////////////////////////////
#define ETH_PTP_FineUpdate                  ((u32)0x00000001)              ///< Fine Update method
#define ETH_PTP_CoarseUpdate                ((u32)0x00000000)              ///< Coarse Update method

#define ETH_PTP_FLAG_TSARU                  ((u32)0x00000020)              ///< Addend Register Update
#define ETH_PTP_FLAG_TSITE                  ((u32)0x00000010)              ///< Time Stamp Interrupt Trigger
#define ETH_PTP_FLAG_TSSTU                  ((u32)0x00000008)              ///< Time Stamp Update
#define ETH_PTP_FLAG_TSSTI                  ((u32)0x00000004)              ///< Time Stamp Initialize

#define ETH_PTP_FLAG_TSTTR                  ((u32)0x10000002)              ///< Time stamp target time reached
#define ETH_PTP_FLAG_TSSO                   ((u32)0x10000001)              ///< Time stamp seconds overflow

#define ETH_PTP_PositiveTime                ((u32)0x00000000)              ///< Positive time value
#define ETH_PTP_NegativeTime                ((u32)0x80000000)              ///< Negative time value

#define ETH_PTPTSCR                         ((u32)0x00000700)              ///< PTP TSCR register
#define ETH_PTPSSIR                         ((u32)0x00000704)              ///< PTP SSIR register
#define ETH_PTPTSHR                         ((u32)0x00000708)              ///< PTP TSHR register
#define ETH_PTPTSLR                         ((u32)0x0000070C)              ///< PTP TSLR register
#define ETH_PTPTSHUR                        ((u32)0x00000710)              ///< PTP TSHUR register
#define ETH_PTPTSLUR                        ((u32)0x00000714)              ///< PTP TSLUR register
#define ETH_PTPTSAR                         ((u32)0x00000718)              ///< PTP TSAR register
#define ETH_PTPTTHR                         ((u32)0x0000071C)              ///< PTP TTHR register
#define ETH_PTPTTLR                         ((u32)0x00000720)              ///< PTP TTLR register

#define ETH_PTPTSSR                         ((u32)0x00000728)              ///< PTP TSSR register

#define ETH_PTP_OrdinaryClock               ((u32)0x00000000)              ///< Ordinary Clock
#define ETH_PTP_BoundaryClock               ((u32)0x00010000)              ///< Boundary Clock
#define ETH_PTP_EndToEndTransparentClock    ((u32)0x00020000)              ///< End To End Transparent Clock
#define ETH_PTP_PeerToPeerTransparentClock  ((u32)0x00030000)              ///< Peer To Peer Transparent Clock

#define ETH_PTP_SnapshotMasterMessage               ((u32)0x00008000)      ///< Time stamp snapshot for message relevant to master enable
#define ETH_PTP_SnapshotEventMessage                ((u32)0x00004000)      ///< Time stamp snapshot for event message enable
#define ETH_PTP_SnapshotIPV4Frames                  ((u32)0x00002000)      ///< Time stamp snapshot for IPv4 frames enable
#define ETH_PTP_SnapshotIPV6Frames                  ((u32)0x00001000)      ///< Time stamp snapshot for IPv6 frames enable
#define ETH_PTP_SnapshotPTPOverEthernetFrames       ((u32)0x00000800)      ///< Time stamp snapshot for PTP over ethernet frames enable
#define ETH_PTP_SnapshotAllReceivedFrames           ((u32)0x00000100)      ///< Time stamp snapshot for all received frames enable

#define ETH_MAC_ADDR_HBASE      (ETH_BASE + 0x40)                               ///< ETHERNET MAC address high offset
#define ETH_MAC_ADDR_LBASE      (ETH_BASE + 0x44)                               ///< ETHERNET MAC address low offset

#define MACMIIAR_CR_MASK    ((u32)0xFFFFFFE3)

#define MACCR_CLEAR_MASK    ((u32)0xFF20810F)
#define MACFCR_CLEAR_MASK   ((u32)0x0000FF41)
#define DMAOMR_CLEAR_MASK   ((u32)0xF8DE3F23)



GLOBAL __IO ETH_DMADESCTypeDef*  DMATxDescToSet;
GLOBAL __IO ETH_DMADESCTypeDef*  DMARxDescToGet;

GLOBAL ETH_DMA_Rx_Frame_infos RX_Frame_Descriptor;
GLOBAL __IO ETH_DMA_Rx_Frame_infos* DMA_RX_FRAME_infos;
GLOBAL __IO u32 Frame_Rx_index;

#undef GLOBAL

void ETH_DeInit(void);
void ETH_StructInit(ETH_InitTypeDef* ptr);
u32 ETH_Init(ETH_InitTypeDef* ptr, u16 phy_addr);
void ETH_Start(void);
void ETH_Stop(void);
void ETH_MACTransmissionCmd(FunctionalState sta);
void ETH_MACReceptionCmd(FunctionalState sta);
FlagStatus ETH_GetFlowControlBusyStatus(void);
void ETH_InitiatePauseControlFrame(void);
void ETH_BackPressureActivationCmd(FunctionalState sta);
void ETH_MACAddressConfig(u32 reg_addr, u8* mac_addr);
void ETH_GetMACAddress(u32 reg_addr, u8* mac_addr);
void ETH_MACAddressPerfectFilterCmd(u32 reg_addr, FunctionalState sta);
void ETH_MACAddressFilterConfig(u32 reg_addr, u32 sta);
void ETH_MACAddressMaskBytesFilterConfig(u32 reg_addr, u32 mask_byte);
FrameTypeDef ETH_Get_Received_Frame(void);
FrameTypeDef ETH_Get_Received_Frame_interrupt(void);
u32 ETH_Prepare_Transmit_Descriptors(u16 len);
void ETH_DMARxDescChainInit(ETH_DMADESCTypeDef* ptr_desc, u8* buf, u32 cnt);
u32 ETH_CheckFrameReceived(void);
void ETH_DMATxDescChainInit(ETH_DMADESCTypeDef* ptr_desc, u8* buf, u32 cnt);
FlagStatus ETH_GetDMATxDescFlagStatus(ETH_DMADESCTypeDef* ptr_desc, u32 flag);
u32 ETH_GetDMATxDescCollisionCount(ETH_DMADESCTypeDef* ptr_desc);
void ETH_SetDMATxDescOwnBit(ETH_DMADESCTypeDef* ptr_desc);
void ETH_DMATxDescTransmitITConfig(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta);
void ETH_DMATxDescFrameSegmentConfig(ETH_DMADESCTypeDef* ptr_desc, u32 val);
void ETH_DMATxDescChecksumInsertionConfig(ETH_DMADESCTypeDef* ptr_desc, u32 val);
void ETH_DMATxDescCRCCmd(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta);
void ETH_DMATxDescSecondAddressChainedCmd(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta);
void ETH_DMATxDescShortFramePaddingCmd(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta);
void ETH_DMATxDescBufferSizeConfig(ETH_DMADESCTypeDef* ptr_desc, u32 buf1_size, u32 buf2_size);
FlagStatus ETH_GetDMARxDescFlagStatus(ETH_DMADESCTypeDef* ptr_desc, u32 flag);
void ETH_SetDMARxDescOwnBit(ETH_DMADESCTypeDef* ptr_desc);
u32 ETH_GetDMARxDescFrameLength(ETH_DMADESCTypeDef* ptr_desc);
void ETH_DMARxDescReceiveITConfig(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta);
u32 ETH_GetDMARxDescBufferSize(ETH_DMADESCTypeDef* ptr_desc, u32 buf);
u32 ETH_GetRxPktSize(ETH_DMADESCTypeDef* ptr_desc);
void ETH_SoftwareReset(void);
FlagStatus ETH_GetSoftwareResetStatus(void);
FlagStatus ETH_GetDMAFlagStatus(u32 flag);
void ETH_DMAClearFlag(u32 flag);
void ETH_DMAITConfig(u32 it, FunctionalState sta);
ITStatus ETH_GetDMAITStatus(u32 it);
void ETH_DMAClearITPendingBit(u32 it);
u32 ETH_GetTransmitProcessState(void);
u32 ETH_GetReceiveProcessState(void);
void ETH_FlushTransmitFIFO(void);
FlagStatus ETH_GetFlushTransmitFIFOStatus(void);
void ETH_DMATransmissionCmd(FunctionalState sta);
void ETH_DMAReceptionCmd(FunctionalState sta);
FlagStatus ETH_GetDMAOverflowStatus(u32 val);
u32 ETH_GetRxOverflowMissedFrameCounter(void);
u32 ETH_GetBufferUnavailableMissedFrameCounter(void);
u32 ETH_GetCurrentTxDescStartAddress(void);
u32 ETH_GetCurrentRxDescStartAddress(void);
u32 ETH_GetCurrentTxBufferAddress(void);
u32 ETH_GetCurrentRxBufferAddress(void);
void ETH_ResumeDMATransmission(void);
void ETH_ResumeDMAReception(void);
void ETH_SetReceiveWatchdogTimer(u8 val);
u16 ETH_ReadPHYRegister(u16 addr, u16 reg);
u16 ETH_WritePHYRegister(u16 addr, u16 reg, u16 val);
u32 ETH_PHYLoopBackCmd(u16 addr, FunctionalState sta);
void ETH_ResetWakeUpFrameFilterRegisterPointer(void);
void ETH_SetWakeUpFrameFilterRegister(u32* buf);
void ETH_GlobalUnicastWakeUpCmd(FunctionalState sta);
FlagStatus ETH_GetPMTFlagStatus(u32 flag);
void ETH_WakeUpFrameDetectionCmd(FunctionalState sta);
void ETH_MagicPacketDetectionCmd(FunctionalState sta);
void ETH_PowerDownCmd(FunctionalState sta);
void ETH_MMCCounterFullPreset(void);
void ETH_MMCCounterHalfPreset(void);
void ETH_MMCCounterFreezeCmd(FunctionalState sta);
void ETH_MMCResetOnReadCmd(FunctionalState sta);
void ETH_MMCCounterRolloverCmd(FunctionalState sta);
void ETH_MMCCountersReset(void);
void ETH_MMCITConfig(u32 it, FunctionalState sta);
ITStatus ETH_GetMMCITStatus(u32 it);
u32 ETH_GetMMCRegister(u32 reg);

/// @}

/// @}

/// @}
////////////////////////////////////////////////////////////////////////////////
#endif //__HAL_ETH_H
////////////////////////////////////////////////////////////////////////////////
