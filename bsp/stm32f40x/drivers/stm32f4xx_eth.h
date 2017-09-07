/**
  ******************************************************************************
  * @file    stm32f2xx_eth.h
  * @author  MCD Application Team
  * @version V0.0.1
  * @date    10/21/2010
  * @brief   This file contains all the functions prototypes for the Ethernet
  *          firmware library.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F2XX_ETH_H
#define __STM32F2XX_ETH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Uncomment this line when using time stamping and/or IPv4 checksum offload */
#define USE_ENHANCED_DMA_DESCRIPTORS

/**
 * @brief Uncomment the line below if you want to use user defined Delay function
 *        (for precise timing), otherwise default _eth_delay_ function defined within
 *        this driver is used (less precise timing).
 */
/* #define USE_Delay */

#ifdef USE_Delay
#include "main.h"
  #define _eth_delay_    Delay     /*!< User can provide more timing precise _eth_delay_ function */
#else
  #define _eth_delay_    ETH_Delay /*!< Default _eth_delay_ function with less precise timing */
#endif

/** @addtogroup STM32F2XX_ETH_Driver
  * @{
  */

/** @defgroup ETH_Exported_Types
  * @{
  */

/**
  * @brief  ETH MAC Init structure definition
  * @note   The user should not configure all the ETH_InitTypeDef structure's fields.
  *   By calling the ETH_StructInit function the structure’s fields are set to their default values.
  *   Only the parameters that will be set to a non-default value should be configured.
  */
typedef struct {
/**
  * @brief / * MAC
  */
  uint32_t             ETH_AutoNegotiation;           /*!< Selects or not the AutoNegotiation mode for the external PHY
                                                           The AutoNegotiation allows an automatic setting of the Speed (10/100Mbps)
                                                           and the mode (half/full-duplex).
                                                           This parameter can be a value of @ref ETH_AutoNegotiation */

  uint32_t             ETH_Watchdog;                  /*!< Selects or not the Watchdog timer
                                                           When enabled, the MAC allows no more then 2048 bytes to be received.
                                                           When disabled, the MAC can receive up to 16384 bytes.
                                                           This parameter can be a value of @ref ETH_watchdog */

  uint32_t             ETH_Jabber;                    /*!< Selects or not Jabber timer
                                                           When enabled, the MAC allows no more then 2048 bytes to be sent.
                                                           When disabled, the MAC can send up to 16384 bytes.
                                                           This parameter can be a value of @ref ETH_Jabber */

  uint32_t             ETH_InterFrameGap;             /*!< Selects the minimum IFG between frames during transmission
                                                           This parameter can be a value of @ref ETH_Inter_Frame_Gap */

  uint32_t             ETH_CarrierSense;              /*!< Selects or not the Carrier Sense
                                                           This parameter can be a value of @ref ETH_Carrier_Sense */

  uint32_t             ETH_Speed;                     /*!< Sets the Ethernet speed: 10/100 Mbps
                                                           This parameter can be a value of @ref ETH_Speed */

  uint32_t             ETH_ReceiveOwn;                /*!< Selects or not the ReceiveOwn
                                                           ReceiveOwn allows the reception of frames when the TX_EN signal is asserted
                                                           in Half-Duplex mode
                                                           This parameter can be a value of @ref ETH_Receive_Own */

  uint32_t             ETH_LoopbackMode;              /*!< Selects or not the internal MAC MII Loopback mode
                                                           This parameter can be a value of @ref ETH_Loop_Back_Mode */

  uint32_t             ETH_Mode;                      /*!< Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode
                                                           This parameter can be a value of @ref ETH_Duplex_Mode */

  uint32_t             ETH_ChecksumOffload;           /*!< Selects or not the IPv4 checksum checking for received frame payloads' TCP/UDP/ICMP headers.
                                                           This parameter can be a value of @ref ETH_Checksum_Offload */

  uint32_t             ETH_RetryTransmission;         /*!< Selects or not the MAC attempt retries transmission, based on the settings of BL,
                                                           when a colision occurs (Half-Duplex mode)
                                                           This parameter can be a value of @ref ETH_Retry_Transmission */

  uint32_t             ETH_AutomaticPadCRCStrip;      /*!< Selects or not the Automatic MAC Pad/CRC Stripping
                                                           This parameter can be a value of @ref ETH_Automatic_Pad_CRC_Strip */

  uint32_t             ETH_BackOffLimit;              /*!< Selects the BackOff limit value
                                                           This parameter can be a value of @ref ETH_Back_Off_Limit */

  uint32_t             ETH_DeferralCheck;             /*!< Selects or not the deferral check function (Half-Duplex mode)
                                                           This parameter can be a value of @ref ETH_Deferral_Check */

  uint32_t             ETH_ReceiveAll;                /*!< Selects or not all frames reception by the MAC (No fitering)
                                                           This parameter can be a value of @ref ETH_Receive_All */

  uint32_t             ETH_SourceAddrFilter;          /*!< Selects the Source Address Filter mode
                                                           This parameter can be a value of @ref ETH_Source_Addr_Filter */

  uint32_t             ETH_PassControlFrames;         /*!< Sets the forwarding mode of the control frames (including unicast and multicast PAUSE frames)
                                                           This parameter can be a value of @ref ETH_Pass_Control_Frames */

  uint32_t             ETH_BroadcastFramesReception;  /*!< Selects or not the reception of Broadcast Frames
                                                           This parameter can be a value of @ref ETH_Broadcast_Frames_Reception */

  uint32_t             ETH_DestinationAddrFilter;     /*!< Sets the destination filter mode for both unicast and multicast frames
                                                           This parameter can be a value of @ref ETH_Destination_Addr_Filter */

  uint32_t             ETH_PromiscuousMode;           /*!< Selects or not the Promiscuous Mode
                                                           This parameter can be a value of @ref ETH_Promiscuous_Mode */

  uint32_t             ETH_MulticastFramesFilter;     /*!< Selects the Multicast Frames filter mode: None/HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                                           This parameter can be a value of @ref ETH_Multicast_Frames_Filter */

  uint32_t             ETH_UnicastFramesFilter;       /*!< Selects the Unicast Frames filter mode: HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                                           This parameter can be a value of @ref ETH_Unicast_Frames_Filter */

  uint32_t             ETH_HashTableHigh;             /*!< This field holds the higher 32 bits of Hash table.  */

  uint32_t             ETH_HashTableLow;              /*!< This field holds the lower 32 bits of Hash table.  */

  uint32_t             ETH_PauseTime;                 /*!< This field holds the value to be used in the Pause Time field in the
                                                           transmit control frame */

  uint32_t             ETH_ZeroQuantaPause;           /*!< Selects or not the automatic generation of Zero-Quanta Pause Control frames
                                                           This parameter can be a value of @ref ETH_Zero_Quanta_Pause */

  uint32_t             ETH_PauseLowThreshold;         /*!< This field configures the threshold of the PAUSE to be checked for
                                                           automatic retransmission of PAUSE Frame
                                                           This parameter can be a value of @ref ETH_Pause_Low_Threshold */

  uint32_t             ETH_UnicastPauseFrameDetect;   /*!< Selects or not the MAC detection of the Pause frames (with MAC Address0
                                                           unicast address and unique multicast address)
                                                           This parameter can be a value of @ref ETH_Unicast_Pause_Frame_Detect */

  uint32_t             ETH_ReceiveFlowControl;        /*!< Enables or disables the MAC to decode the received Pause frame and
                                                           disable its transmitter for a specified time (Pause Time)
                                                           This parameter can be a value of @ref ETH_Receive_Flow_Control */

  uint32_t             ETH_TransmitFlowControl;       /*!< Enables or disables the MAC to transmit Pause frames (Full-Duplex mode)
                                                           or the MAC back-pressure operation (Half-Duplex mode)
                                                           This parameter can be a value of @ref ETH_Transmit_Flow_Control */

  uint32_t             ETH_VLANTagComparison;         /*!< Selects the 12-bit VLAN identifier or the complete 16-bit VLAN tag for
                                                           comparison and filtering
                                                           This parameter can be a value of @ref ETH_VLAN_Tag_Comparison */

  uint32_t             ETH_VLANTagIdentifier;         /*!< Holds the VLAN tag identifier for receive frames */

/**
  * @brief / * DMA
  */

  uint32_t             ETH_DropTCPIPChecksumErrorFrame; /*!< Selects or not the Dropping of TCP/IP Checksum Error Frames
                                                             This parameter can be a value of @ref ETH_Drop_TCP_IP_Checksum_Error_Frame */

  uint32_t             ETH_ReceiveStoreForward;         /*!< Enables or disables the Receive store and forward mode
                                                             This parameter can be a value of @ref ETH_Receive_Store_Forward */

  uint32_t             ETH_FlushReceivedFrame;          /*!< Enables or disables the flushing of received frames
                                                             This parameter can be a value of @ref ETH_Flush_Received_Frame */

  uint32_t             ETH_TransmitStoreForward;        /*!< Enables or disables Transmit store and forward mode
                                                             This parameter can be a value of @ref ETH_Transmit_Store_Forward */

  uint32_t             ETH_TransmitThresholdControl;    /*!< Selects or not the Transmit Threshold Control
                                                             This parameter can be a value of @ref ETH_Transmit_Threshold_Control */

  uint32_t             ETH_ForwardErrorFrames;          /*!< Selects or not the forward to the DMA of erroneous frames
                                                             This parameter can be a value of @ref ETH_Forward_Error_Frames */

  uint32_t             ETH_ForwardUndersizedGoodFrames; /*!< Enables or disables the Rx FIFO to forward Undersized frames (frames with no Error
                                                             and length less than 64 bytes) including pad-bytes and CRC)
                                                             This parameter can be a value of @ref ETH_Forward_Undersized_Good_Frames */

  uint32_t             ETH_ReceiveThresholdControl;     /*!< Selects the threshold level of the Receive FIFO
                                                             This parameter can be a value of @ref ETH_Receive_Threshold_Control */

  uint32_t             ETH_SecondFrameOperate;          /*!< Selects or not the Operate on second frame mode, which allows the DMA to process a second
                                                             frame of Transmit data even before obtaining the status for the first frame.
                                                             This parameter can be a value of @ref ETH_Second_Frame_Operate */

  uint32_t             ETH_AddressAlignedBeats;         /*!< Enables or disables the Address Aligned Beats
                                                             This parameter can be a value of @ref ETH_Address_Aligned_Beats */

  uint32_t             ETH_FixedBurst;                  /*!< Enables or disables the AHB Master interface fixed burst transfers
                                                             This parameter can be a value of @ref ETH_Fixed_Burst */

  uint32_t             ETH_RxDMABurstLength;            /*!< Indicates the maximum number of beats to be transferred in one Rx DMA transaction
                                                             This parameter can be a value of @ref ETH_Rx_DMA_Burst_Length */

  uint32_t             ETH_TxDMABurstLength;            /*!< Indicates sthe maximum number of beats to be transferred in one Tx DMA transaction
                                                             This parameter can be a value of @ref ETH_Tx_DMA_Burst_Length */

  uint32_t             ETH_DescriptorSkipLength;        /*!< Specifies the number of word to skip between two unchained descriptors (Ring mode) */

  uint32_t             ETH_DMAArbitration;              /*!< Selects the DMA Tx/Rx arbitration
                                                             This parameter can be a value of @ref ETH_DMA_Arbitration */
}ETH_InitTypeDef;

/**--------------------------------------------------------------------------**/
/**
  * @brief                           DMA descriptors types
  */
/**--------------------------------------------------------------------------**/

/**
  * @brief  ETH DMA Desciptors data structure definition
  */
typedef struct  {
  uint32_t   Status;                /*!< Status */
  uint32_t   ControlBufferSize;     /*!< Control and Buffer1, Buffer2 lengths */
  uint32_t   Buffer1Addr;           /*!< Buffer1 address pointer */
  uint32_t   Buffer2NextDescAddr;   /*!< Buffer2 or next descriptor address pointer */
/* Enhanced ETHERNET DMA PTP Desciptors */
#ifdef USE_ENHANCED_DMA_DESCRIPTORS
  uint32_t   ExtendedStatus;        /* Extended status for PTP receive descriptor */
  uint32_t   Reserved1;             /* Reserved */
  uint32_t   TimeStampLow;          /* Time Stamp Low value for transmit and receive */
  uint32_t   TimeStampHigh;         /* Time Stamp High value for transmit and receive */
#endif /* USE_ENHANCED_DMA_DESCRIPTORS */
} ETH_DMADESCTypeDef;


/**
  * @}
  */

/** @defgroup ETH_Exported_Constants
  * @{
  */

/**--------------------------------------------------------------------------**/
/**
  * @brief                          ETH Frames defines
  */
/**--------------------------------------------------------------------------**/

/** @defgroup ENET_Buffers_setting
  * @{
  */
#define ETH_MAX_PACKET_SIZE    1520    /*!< ETH_HEADER + ETH_EXTRA + MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_HEADER               14    /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC                   4    /*!< Ethernet CRC */
#define ETH_EXTRA                 2    /*!< Extra bytes in some cases */
#define VLAN_TAG                  4    /*!< optional 802.1q VLAN Tag */
#define MIN_ETH_PAYLOAD          46    /*!< Minimum Ethernet payload size */
#define MAX_ETH_PAYLOAD        1500    /*!< Maximum Ethernet payload size */
#define JUMBO_FRAME_PAYLOAD    9000    /*!< Jumbo frame payload size */

/**--------------------------------------------------------------------------**/
/**
  * @brief                 Ethernet DMA descriptors registers bits definition
  */
/**--------------------------------------------------------------------------**/

/**
@code
   DMA Tx Desciptor
  -----------------------------------------------------------------------------------------------
  TDES0 | OWN(31) | CTRL[30:26] | Reserved[25:24] | CTRL[23:20] | Reserved[19:17] | Status[16:0] |
  -----------------------------------------------------------------------------------------------
  TDES1 | Reserved[31:29] | Buffer2 ByteCount[28:16] | Reserved[15:13] | Buffer1 ByteCount[12:0] |
  -----------------------------------------------------------------------------------------------
  TDES2 |                         Buffer1 Address [31:0]                                         |
  -----------------------------------------------------------------------------------------------
  TDES3 |                   Buffer2 Address [31:0] / Next Desciptor Address [31:0]               |
  -----------------------------------------------------------------------------------------------
@endcode
*/

/**
  * @brief  Bit definition of TDES0 register: DMA Tx descriptor status register
  */
#define ETH_DMATxDesc_OWN                     ((uint32_t)0x80000000)  /*!< OWN bit: descriptor is owned by DMA engine */
#define ETH_DMATxDesc_IC                      ((uint32_t)0x40000000)  /*!< Interrupt on Completion */
#define ETH_DMATxDesc_LS                      ((uint32_t)0x20000000)  /*!< Last Segment */
#define ETH_DMATxDesc_FS                      ((uint32_t)0x10000000)  /*!< First Segment */
#define ETH_DMATxDesc_DC                      ((uint32_t)0x08000000)  /*!< Disable CRC */
#define ETH_DMATxDesc_DP                      ((uint32_t)0x04000000)  /*!< Disable Padding */
#define ETH_DMATxDesc_TTSE                    ((uint32_t)0x02000000)  /*!< Transmit Time Stamp Enable */
#define ETH_DMATxDesc_CIC                     ((uint32_t)0x00C00000)  /*!< Checksum Insertion Control: 4 cases */
#define ETH_DMATxDesc_CIC_ByPass              ((uint32_t)0x00000000)  /*!< Do Nothing: Checksum Engine is bypassed */
#define ETH_DMATxDesc_CIC_IPV4Header          ((uint32_t)0x00400000)  /*!< IPV4 header Checksum Insertion */
#define ETH_DMATxDesc_CIC_TCPUDPICMP_Segment  ((uint32_t)0x00800000)  /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define ETH_DMATxDesc_CIC_TCPUDPICMP_Full     ((uint32_t)0x00C00000)  /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */
#define ETH_DMATxDesc_TER                     ((uint32_t)0x00200000)  /*!< Transmit End of Ring */
#define ETH_DMATxDesc_TCH                     ((uint32_t)0x00100000)  /*!< Second Address Chained */
#define ETH_DMATxDesc_TTSS                    ((uint32_t)0x00020000)  /*!< Tx Time Stamp Status */
#define ETH_DMATxDesc_IHE                     ((uint32_t)0x00010000)  /*!< IP Header Error */
#define ETH_DMATxDesc_ES                      ((uint32_t)0x00008000)  /*!< Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF || JT */
#define ETH_DMATxDesc_JT                      ((uint32_t)0x00004000)  /*!< Jabber Timeout */
#define ETH_DMATxDesc_FF                      ((uint32_t)0x00002000)  /*!< Frame Flushed: DMA/MTL flushed the frame due to SW flush */
#define ETH_DMATxDesc_PCE                     ((uint32_t)0x00001000)  /*!< Payload Checksum Error */
#define ETH_DMATxDesc_LCA                     ((uint32_t)0x00000800)  /*!< Loss of Carrier: carrier lost during tramsmission */
#define ETH_DMATxDesc_NC                      ((uint32_t)0x00000400)  /*!< No Carrier: no carrier signal from the tranceiver */
#define ETH_DMATxDesc_LCO                     ((uint32_t)0x00000200)  /*!< Late Collision: transmission aborted due to collision */
#define ETH_DMATxDesc_EC                      ((uint32_t)0x00000100)  /*!< Excessive Collision: transmission aborted after 16 collisions */
#define ETH_DMATxDesc_VF                      ((uint32_t)0x00000080)  /*!< VLAN Frame */
#define ETH_DMATxDesc_CC                      ((uint32_t)0x00000078)  /*!< Collision Count */
#define ETH_DMATxDesc_ED                      ((uint32_t)0x00000004)  /*!< Excessive Deferral */
#define ETH_DMATxDesc_UF                      ((uint32_t)0x00000002)  /*!< Underflow Error: late data arrival from the memory */
#define ETH_DMATxDesc_DB                      ((uint32_t)0x00000001)  /*!< Deferred Bit */

/**
  * @brief  Bit definition of TDES1 register
  */
#define ETH_DMATxDesc_TBS2  ((uint32_t)0x1FFF0000)  /*!< Transmit Buffer2 Size */
#define ETH_DMATxDesc_TBS1  ((uint32_t)0x00001FFF)  /*!< Transmit Buffer1 Size */

/**
  * @brief  Bit definition of TDES2 register
  */
#define ETH_DMATxDesc_B1AP  ((uint32_t)0xFFFFFFFF)  /*!< Buffer1 Address Pointer */

/**
  * @brief  Bit definition of TDES3 register
  */
#define ETH_DMATxDesc_B2AP  ((uint32_t)0xFFFFFFFF)  /*!< Buffer2 Address Pointer */

  /*---------------------------------------------------------------------------------------------
  TDES6 |                         Transmit Time Stmap Low [31:0]                                 |
  -----------------------------------------------------------------------------------------------
  TDES7 |                         Transmit Time Stmap High [31:0]                                |
  ----------------------------------------------------------------------------------------------*/

/* Bit definition of TDES6 register */
 #define ETH_DMAPTPTxDesc_TTSL  ((uint32_t)0xFFFFFFFF)  /* Transmit Time Stmap Low */

/* Bit definition of TDES7 register */
 #define ETH_DMAPTPTxDesc_TTSH  ((uint32_t)0xFFFFFFFF)  /* Transmit Time Stmap High */

/**
  * @}
  */


/** @defgroup DMA_Rx_descriptor
  * @{
  */

/**
@code
  DMA Rx Desciptor
  --------------------------------------------------------------------------------------------------------------------
  RDES0 | OWN(31) |                                             Status [30:0]                                          |
  ---------------------------------------------------------------------------------------------------------------------
  RDES1 | CTRL(31) | Reserved[30:29] | Buffer2 ByteCount[28:16] | CTRL[15:14] | Reserved(13) | Buffer1 ByteCount[12:0] |
  ---------------------------------------------------------------------------------------------------------------------
  RDES2 |                                       Buffer1 Address [31:0]                                                 |
  ---------------------------------------------------------------------------------------------------------------------
  RDES3 |                          Buffer2 Address [31:0] / Next Desciptor Address [31:0]                              |
  ---------------------------------------------------------------------------------------------------------------------
@endcode
*/

/**
  * @brief  Bit definition of RDES0 register: DMA Rx descriptor status register
  */
#define ETH_DMARxDesc_OWN         ((uint32_t)0x80000000)  /*!< OWN bit: descriptor is owned by DMA engine  */
#define ETH_DMARxDesc_AFM         ((uint32_t)0x40000000)  /*!< DA Filter Fail for the rx frame  */
#define ETH_DMARxDesc_FL          ((uint32_t)0x3FFF0000)  /*!< Receive descriptor frame length  */
#define ETH_DMARxDesc_ES          ((uint32_t)0x00008000)  /*!< Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE */
#define ETH_DMARxDesc_DE          ((uint32_t)0x00004000)  /*!< Desciptor error: no more descriptors for receive frame  */
#define ETH_DMARxDesc_SAF         ((uint32_t)0x00002000)  /*!< SA Filter Fail for the received frame */
#define ETH_DMARxDesc_LE          ((uint32_t)0x00001000)  /*!< Frame size not matching with length field */
#define ETH_DMARxDesc_OE          ((uint32_t)0x00000800)  /*!< Overflow Error: Frame was damaged due to buffer overflow */
#define ETH_DMARxDesc_VLAN        ((uint32_t)0x00000400)  /*!< VLAN Tag: received frame is a VLAN frame */
#define ETH_DMARxDesc_FS          ((uint32_t)0x00000200)  /*!< First descriptor of the frame  */
#define ETH_DMARxDesc_LS          ((uint32_t)0x00000100)  /*!< Last descriptor of the frame  */
#define ETH_DMARxDesc_IPV4HCE     ((uint32_t)0x00000080)  /*!< IPC Checksum Error: Rx Ipv4 header checksum error   */
#define ETH_DMARxDesc_LC          ((uint32_t)0x00000040)  /*!< Late collision occurred during reception   */
#define ETH_DMARxDesc_FT          ((uint32_t)0x00000020)  /*!< Frame type - Ethernet, otherwise 802.3    */
#define ETH_DMARxDesc_RWT         ((uint32_t)0x00000010)  /*!< Receive Watchdog Timeout: watchdog timer expired during reception    */
#define ETH_DMARxDesc_RE          ((uint32_t)0x00000008)  /*!< Receive error: error reported by MII interface  */
#define ETH_DMARxDesc_DBE         ((uint32_t)0x00000004)  /*!< Dribble bit error: frame contains non int multiple of 8 bits  */
#define ETH_DMARxDesc_CE          ((uint32_t)0x00000002)  /*!< CRC error */
#define ETH_DMARxDesc_MAMPCE      ((uint32_t)0x00000001)  /*!< Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error */

/**
  * @brief  Bit definition of RDES1 register
  */
#define ETH_DMARxDesc_DIC   ((uint32_t)0x80000000)  /*!< Disable Interrupt on Completion */
#define ETH_DMARxDesc_RBS2  ((uint32_t)0x1FFF0000)  /*!< Receive Buffer2 Size */
#define ETH_DMARxDesc_RER   ((uint32_t)0x00008000)  /*!< Receive End of Ring */
#define ETH_DMARxDesc_RCH   ((uint32_t)0x00004000)  /*!< Second Address Chained */
#define ETH_DMARxDesc_RBS1  ((uint32_t)0x00001FFF)  /*!< Receive Buffer1 Size */

/**
  * @brief  Bit definition of RDES2 register
  */
#define ETH_DMARxDesc_B1AP  ((uint32_t)0xFFFFFFFF)  /*!< Buffer1 Address Pointer */

/**
  * @brief  Bit definition of RDES3 register
  */
#define ETH_DMARxDesc_B2AP  ((uint32_t)0xFFFFFFFF)  /*!< Buffer2 Address Pointer */

/*---------------------------------------------------------------------------------------------------------------------
  RDES4 |                   Reserved[31:15]              |             Extended Status [14:0]                          |
  ---------------------------------------------------------------------------------------------------------------------
  RDES5 |                                            Reserved[31:0]                                                    |
  ---------------------------------------------------------------------------------------------------------------------
  RDES6 |                                       Receive Time Stmap Low [31:0]                                          |
  ---------------------------------------------------------------------------------------------------------------------
  RDES7 |                                       Receive Time Stmap High [31:0]                                         |
  --------------------------------------------------------------------------------------------------------------------*/

/* Bit definition of RDES4 register */
#define ETH_DMAPTPRxDesc_PTPV     ((uint32_t)0x00002000)  /* PTP Version */
#define ETH_DMAPTPRxDesc_PTPFT    ((uint32_t)0x00001000)  /* PTP Frame Type */
#define ETH_DMAPTPRxDesc_PTPMT    ((uint32_t)0x00000F00)  /* PTP Message Type */
  #define ETH_DMAPTPRxDesc_PTPMT_Sync                      ((uint32_t)0x00000100)  /* SYNC message (all clock types) */
  #define ETH_DMAPTPRxDesc_PTPMT_FollowUp                  ((uint32_t)0x00000200)  /* FollowUp message (all clock types) */
  #define ETH_DMAPTPRxDesc_PTPMT_DelayReq                  ((uint32_t)0x00000300)  /* DelayReq message (all clock types) */
  #define ETH_DMAPTPRxDesc_PTPMT_DelayResp                 ((uint32_t)0x00000400)  /* DelayResp message (all clock types) */
  #define ETH_DMAPTPRxDesc_PTPMT_PdelayReq_Announce        ((uint32_t)0x00000500)  /* PdelayReq message (peer-to-peer transparent clock) or Announce message (Ordinary or Boundary clock) */
  #define ETH_DMAPTPRxDesc_PTPMT_PdelayResp_Manag          ((uint32_t)0x00000600)  /* PdelayResp message (peer-to-peer transparent clock) or Management message (Ordinary or Boundary clock)  */
  #define ETH_DMAPTPRxDesc_PTPMT_PdelayRespFollowUp_Signal ((uint32_t)0x00000700)  /* PdelayRespFollowUp message (peer-to-peer transparent clock) or Signaling message (Ordinary or Boundary clock) */
#define ETH_DMAPTPRxDesc_IPV6PR   ((uint32_t)0x00000080)  /* IPv6 Packet Received */
#define ETH_DMAPTPRxDesc_IPV4PR   ((uint32_t)0x00000040)  /* IPv4 Packet Received */
#define ETH_DMAPTPRxDesc_IPCB  ((uint32_t)0x00000020)  /* IP Checksum Bypassed */
#define ETH_DMAPTPRxDesc_IPPE  ((uint32_t)0x00000010)  /* IP Payload Error */
#define ETH_DMAPTPRxDesc_IPHE  ((uint32_t)0x00000008)  /* IP Header Error */
#define ETH_DMAPTPRxDesc_IPPT  ((uint32_t)0x00000007)  /* IP Payload Type */
  #define ETH_DMAPTPRxDesc_IPPT_UDP                 ((uint32_t)0x00000001)  /* UDP payload encapsulated in the IP datagram */
  #define ETH_DMAPTPRxDesc_IPPT_TCP                 ((uint32_t)0x00000002)  /* TCP payload encapsulated in the IP datagram */
  #define ETH_DMAPTPRxDesc_IPPT_ICMP                ((uint32_t)0x00000003)  /* ICMP payload encapsulated in the IP datagram */

/* Bit definition of RDES6 register */
#define ETH_DMAPTPRxDesc_RTSL  ((uint32_t)0xFFFFFFFF)  /* Receive Time Stmap Low */

/* Bit definition of RDES7 register */
#define ETH_DMAPTPRxDesc_RTSH  ((uint32_t)0xFFFFFFFF)  /* Receive Time Stmap High */


/**--------------------------------------------------------------------------**/
/**
  * @brief                     Desciption of common PHY registers
  */
/**--------------------------------------------------------------------------**/

/**
  * @}
  */

/** @defgroup PHY_Read_write_Timeouts
  * @{
  */
#define PHY_READ_TO                     ((uint32_t)0x0004FFFF)
#define PHY_WRITE_TO                    ((uint32_t)0x0004FFFF)

/**
  * @}
  */

/** @defgroup PHY_Reset_Delay
  * @{
  */
#define PHY_ResetDelay                  ((uint32_t)0x000FFFFF)

/**
  * @}
  */

/** @defgroup PHY_Config_Delay
  * @{
  */
#define PHY_ConfigDelay                 ((uint32_t)0x00FFFFFF)

/**
  * @}
  */

/** @defgroup PHY_Register_address
  * @{
  */
#define PHY_BCR                          0          /*!< Tranceiver Basic Control Register */
#define PHY_BSR                          1          /*!< Tranceiver Basic Status Register */

/**
  * @}
  */

/** @defgroup PHY_basic_Control_register
  * @{
  */
#define PHY_Reset                       ((uint16_t)0x8000)      /*!< PHY Reset */
#define PHY_Loopback                    ((uint16_t)0x4000)      /*!< Select loop-back mode */
#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100)      /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000)      /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100)      /*!< Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000)      /*!< Set the half-duplex mode at 10 Mb/s */
#define PHY_AutoNegotiation             ((uint16_t)0x1000)      /*!< Enable auto-negotiation function */
#define PHY_Restart_AutoNegotiation     ((uint16_t)0x0200)      /*!< Restart auto-negotiation function */
#define PHY_Powerdown                   ((uint16_t)0x0800)      /*!< Select the power down mode */
#define PHY_Isolate                     ((uint16_t)0x0400)      /*!< Isolate PHY from MII */

/**
  * @}
  */

/** @defgroup PHY_basic_status_register
  * @{
  */
#define PHY_AutoNego_Complete           ((uint16_t)0x0020)      /*!< Auto-Negotioation process completed */
#define PHY_Linked_Status               ((uint16_t)0x0004)      /*!< Valid link established */
#define PHY_Jabber_detection            ((uint16_t)0x0002)      /*!< Jabber condition detected */

/**
  * @}
  */

/** @defgroup PHY_status_register
  * @{
  */
/* The PHY status register value change from a PHY to another so the user have
   to update this value depending on the used external PHY */
/**
  * @brief  For LAN8700
  */
/*#define PHY_SR                           31 */        /*!< Tranceiver Status Register */

/**
  * @brief  For DP83848
  */
#define PHY_SR                           16     /*!< Tranceiver Status Register */

/* The Speed and Duplex mask values change from a PHY to another so the user have to update
   this value depending on the used external PHY */
/**
  * @brief  For LAN8700
  */
/*#define PHY_Speed_Status            ((uint16_t)0x0004)*/      /*!< Configured information of Speed: 10Mbps */
/*#define PHY_Duplex_Status           ((uint16_t)0x0010)*/      /*!< Configured information of Duplex: Full-duplex */

/**
  * @brief  For DP83848
  */
#define PHY_Speed_Status            ((uint16_t)0x0002)    /*!< Configured information of Speed: 10Mbps */
#define PHY_Duplex_Status           ((uint16_t)0x0004)    /*!< Configured information of Duplex: Full-duplex */
#define IS_ETH_PHY_ADDRESS(ADDRESS) ((ADDRESS) <= 0x20)
#define IS_ETH_PHY_REG(REG) ((REG) <= 0x1F)

/**--------------------------------------------------------------------------**/
/**
  * @brief                                  MAC defines
  */
/**--------------------------------------------------------------------------**/

/**
  * @}
  */

/** @defgroup ETH_AutoNegotiation
  * @{
  */
#define ETH_AutoNegotiation_Enable     ((uint32_t)0x00000001)
#define ETH_AutoNegotiation_Disable    ((uint32_t)0x00000000)
#define IS_ETH_AUTONEGOTIATION(CMD) (((CMD) == ETH_AutoNegotiation_Enable) || \
                                     ((CMD) == ETH_AutoNegotiation_Disable))

/**
  * @}
  */

/** @defgroup ETH_watchdog
  * @{
  */
#define ETH_Watchdog_Enable       ((uint32_t)0x00000000)
#define ETH_Watchdog_Disable      ((uint32_t)0x00800000)
#define IS_ETH_WATCHDOG(CMD) (((CMD) == ETH_Watchdog_Enable) || \
                              ((CMD) == ETH_Watchdog_Disable))

/**
  * @}
  */

/** @defgroup ETH_Jabber
  * @{
  */
#define ETH_Jabber_Enable    ((uint32_t)0x00000000)
#define ETH_Jabber_Disable   ((uint32_t)0x00400000)
#define IS_ETH_JABBER(CMD) (((CMD) == ETH_Jabber_Enable) || \
                            ((CMD) == ETH_Jabber_Disable))

/**
  * @}
  */

/** @defgroup ETH_Inter_Frame_Gap
  * @{
  */
#define ETH_InterFrameGap_96Bit   ((uint32_t)0x00000000)  /*!< minimum IFG between frames during transmission is 96Bit */
#define ETH_InterFrameGap_88Bit   ((uint32_t)0x00020000)  /*!< minimum IFG between frames during transmission is 88Bit */
#define ETH_InterFrameGap_80Bit   ((uint32_t)0x00040000)  /*!< minimum IFG between frames during transmission is 80Bit */
#define ETH_InterFrameGap_72Bit   ((uint32_t)0x00060000)  /*!< minimum IFG between frames during transmission is 72Bit */
#define ETH_InterFrameGap_64Bit   ((uint32_t)0x00080000)  /*!< minimum IFG between frames during transmission is 64Bit */
#define ETH_InterFrameGap_56Bit   ((uint32_t)0x000A0000)  /*!< minimum IFG between frames during transmission is 56Bit */
#define ETH_InterFrameGap_48Bit   ((uint32_t)0x000C0000)  /*!< minimum IFG between frames during transmission is 48Bit */
#define ETH_InterFrameGap_40Bit   ((uint32_t)0x000E0000)  /*!< minimum IFG between frames during transmission is 40Bit */
#define IS_ETH_INTER_FRAME_GAP(GAP) (((GAP) == ETH_InterFrameGap_96Bit) || \
                                     ((GAP) == ETH_InterFrameGap_88Bit) || \
                                     ((GAP) == ETH_InterFrameGap_80Bit) || \
                                     ((GAP) == ETH_InterFrameGap_72Bit) || \
                                     ((GAP) == ETH_InterFrameGap_64Bit) || \
                                     ((GAP) == ETH_InterFrameGap_56Bit) || \
                                     ((GAP) == ETH_InterFrameGap_48Bit) || \
                                     ((GAP) == ETH_InterFrameGap_40Bit))

/**
  * @}
  */

/** @defgroup ETH_Carrier_Sense
  * @{
  */
#define ETH_CarrierSense_Enable   ((uint32_t)0x00000000)
#define ETH_CarrierSense_Disable  ((uint32_t)0x00010000)
#define IS_ETH_CARRIER_SENSE(CMD) (((CMD) == ETH_CarrierSense_Enable) || \
                                   ((CMD) == ETH_CarrierSense_Disable))

/**
  * @}
  */

/** @defgroup ETH_Speed
  * @{
  */
#define ETH_Speed_10M        ((uint32_t)0x00000000)
#define ETH_Speed_100M       ((uint32_t)0x00004000)
#define IS_ETH_SPEED(SPEED) (((SPEED) == ETH_Speed_10M) || \
                             ((SPEED) == ETH_Speed_100M))

/**
  * @}
  */

/** @defgroup ETH_Receive_Own
  * @{
  */
#define ETH_ReceiveOwn_Enable     ((uint32_t)0x00000000)
#define ETH_ReceiveOwn_Disable    ((uint32_t)0x00002000)
#define IS_ETH_RECEIVE_OWN(CMD) (((CMD) == ETH_ReceiveOwn_Enable) || \
                                 ((CMD) == ETH_ReceiveOwn_Disable))

/**
  * @}
  */

/** @defgroup ETH_Loop_Back_Mode
  * @{
  */
#define ETH_LoopbackMode_Enable        ((uint32_t)0x00001000)
#define ETH_LoopbackMode_Disable       ((uint32_t)0x00000000)
#define IS_ETH_LOOPBACK_MODE(CMD) (((CMD) == ETH_LoopbackMode_Enable) || \
                                   ((CMD) == ETH_LoopbackMode_Disable))

/**
  * @}
  */

/** @defgroup ETH_Duplex_Mode
  * @{
  */
#define ETH_Mode_FullDuplex       ((uint32_t)0x00000800)
#define ETH_Mode_HalfDuplex       ((uint32_t)0x00000000)
#define IS_ETH_DUPLEX_MODE(MODE) (((MODE) == ETH_Mode_FullDuplex) || \
                                  ((MODE) == ETH_Mode_HalfDuplex))

/**
  * @}
  */

/** @defgroup ETH_Checksum_Offload
  * @{
  */
#define ETH_ChecksumOffload_Enable     ((uint32_t)0x00000400)
#define ETH_ChecksumOffload_Disable    ((uint32_t)0x00000000)
#define IS_ETH_CHECKSUM_OFFLOAD(CMD) (((CMD) == ETH_ChecksumOffload_Enable) || \
                                      ((CMD) == ETH_ChecksumOffload_Disable))

/**
  * @}
  */

/** @defgroup ETH_Retry_Transmission
  * @{
  */
#define ETH_RetryTransmission_Enable   ((uint32_t)0x00000000)
#define ETH_RetryTransmission_Disable  ((uint32_t)0x00000200)
#define IS_ETH_RETRY_TRANSMISSION(CMD) (((CMD) == ETH_RetryTransmission_Enable) || \
                                        ((CMD) == ETH_RetryTransmission_Disable))

/**
  * @}
  */

/** @defgroup ETH_Automatic_Pad_CRC_Strip
  * @{
  */
#define ETH_AutomaticPadCRCStrip_Enable     ((uint32_t)0x00000080)
#define ETH_AutomaticPadCRCStrip_Disable    ((uint32_t)0x00000000)
#define IS_ETH_AUTOMATIC_PADCRC_STRIP(CMD) (((CMD) == ETH_AutomaticPadCRCStrip_Enable) || \
                                            ((CMD) == ETH_AutomaticPadCRCStrip_Disable))

/**
  * @}
  */

/** @defgroup ETH_Back_Off_Limit
  * @{
  */
#define ETH_BackOffLimit_10  ((uint32_t)0x00000000)
#define ETH_BackOffLimit_8   ((uint32_t)0x00000020)
#define ETH_BackOffLimit_4   ((uint32_t)0x00000040)
#define ETH_BackOffLimit_1   ((uint32_t)0x00000060)
#define IS_ETH_BACKOFF_LIMIT(LIMIT) (((LIMIT) == ETH_BackOffLimit_10) || \
                                     ((LIMIT) == ETH_BackOffLimit_8) || \
                                     ((LIMIT) == ETH_BackOffLimit_4) || \
                                     ((LIMIT) == ETH_BackOffLimit_1))

/**
  * @}
  */

/** @defgroup ETH_Deferral_Check
  * @{
  */
#define ETH_DeferralCheck_Enable       ((uint32_t)0x00000010)
#define ETH_DeferralCheck_Disable      ((uint32_t)0x00000000)
#define IS_ETH_DEFERRAL_CHECK(CMD) (((CMD) == ETH_DeferralCheck_Enable) || \
                                    ((CMD) == ETH_DeferralCheck_Disable))

/**
  * @}
  */

/** @defgroup ETH_Receive_All
  * @{
  */
#define ETH_ReceiveAll_Enable     ((uint32_t)0x80000000)
#define ETH_ReceiveAll_Disable    ((uint32_t)0x00000000)
#define IS_ETH_RECEIVE_ALL(CMD) (((CMD) == ETH_ReceiveAll_Enable) || \
                                 ((CMD) == ETH_ReceiveAll_Disable))

/**
  * @}
  */

/** @defgroup ETH_Source_Addr_Filter
  * @{
  */
#define ETH_SourceAddrFilter_Normal_Enable       ((uint32_t)0x00000200)
#define ETH_SourceAddrFilter_Inverse_Enable      ((uint32_t)0x00000300)
#define ETH_SourceAddrFilter_Disable             ((uint32_t)0x00000000)
#define IS_ETH_SOURCE_ADDR_FILTER(CMD) (((CMD) == ETH_SourceAddrFilter_Normal_Enable) || \
                                        ((CMD) == ETH_SourceAddrFilter_Inverse_Enable) || \
                                        ((CMD) == ETH_SourceAddrFilter_Disable))

/**
  * @}
  */

/** @defgroup ETH_Pass_Control_Frames
  * @{
  */
#define ETH_PassControlFrames_BlockAll                ((uint32_t)0x00000040)  /*!< MAC filters all control frames from reaching the application */
#define ETH_PassControlFrames_ForwardAll              ((uint32_t)0x00000080)  /*!< MAC forwards all control frames to application even if they fail the Address Filter */
#define ETH_PassControlFrames_ForwardPassedAddrFilter ((uint32_t)0x000000C0)  /*!< MAC forwards control frames that pass the Address Filter. */
#define IS_ETH_CONTROL_FRAMES(PASS) (((PASS) == ETH_PassControlFrames_BlockAll) || \
                                     ((PASS) == ETH_PassControlFrames_ForwardAll) || \
                                     ((PASS) == ETH_PassControlFrames_ForwardPassedAddrFilter))

/**
  * @}
  */

/** @defgroup ETH_Broadcast_Frames_Reception
  * @{
  */
#define ETH_BroadcastFramesReception_Enable      ((uint32_t)0x00000000)
#define ETH_BroadcastFramesReception_Disable     ((uint32_t)0x00000020)
#define IS_ETH_BROADCAST_FRAMES_RECEPTION(CMD) (((CMD) == ETH_BroadcastFramesReception_Enable) || \
                                                ((CMD) == ETH_BroadcastFramesReception_Disable))

/**
  * @}
  */

/** @defgroup ETH_Destination_Addr_Filter
  * @{
  */
#define ETH_DestinationAddrFilter_Normal    ((uint32_t)0x00000000)
#define ETH_DestinationAddrFilter_Inverse   ((uint32_t)0x00000008)
#define IS_ETH_DESTINATION_ADDR_FILTER(FILTER) (((FILTER) == ETH_DestinationAddrFilter_Normal) || \
                                                ((FILTER) == ETH_DestinationAddrFilter_Inverse))

/**
  * @}
  */

/** @defgroup ETH_Promiscuous_Mode
  * @{
  */
#define ETH_PromiscuousMode_Enable     ((uint32_t)0x00000001)
#define ETH_PromiscuousMode_Disable    ((uint32_t)0x00000000)
#define IS_ETH_PROMISCUOUS_MODE(CMD) (((CMD) == ETH_PromiscuousMode_Enable) || \
                                      ((CMD) == ETH_PromiscuousMode_Disable))

/**
  * @}
  */

/** @defgroup ETH_Multicast_Frames_Filter
  * @{
  */
#define ETH_MulticastFramesFilter_PerfectHashTable    ((uint32_t)0x00000404)
#define ETH_MulticastFramesFilter_HashTable           ((uint32_t)0x00000004)
#define ETH_MulticastFramesFilter_Perfect             ((uint32_t)0x00000000)
#define ETH_MulticastFramesFilter_None                ((uint32_t)0x00000010)
#define IS_ETH_MULTICAST_FRAMES_FILTER(FILTER) (((FILTER) == ETH_MulticastFramesFilter_PerfectHashTable) || \
                                                ((FILTER) == ETH_MulticastFramesFilter_HashTable) || \
                                                ((FILTER) == ETH_MulticastFramesFilter_Perfect) || \
                                                ((FILTER) == ETH_MulticastFramesFilter_None))


/**
  * @}
  */

/** @defgroup ETH_Unicast_Frames_Filter
  * @{
  */
#define ETH_UnicastFramesFilter_PerfectHashTable ((uint32_t)0x00000402)
#define ETH_UnicastFramesFilter_HashTable        ((uint32_t)0x00000002)
#define ETH_UnicastFramesFilter_Perfect          ((uint32_t)0x00000000)
#define IS_ETH_UNICAST_FRAMES_FILTER(FILTER) (((FILTER) == ETH_UnicastFramesFilter_PerfectHashTable) || \
                                              ((FILTER) == ETH_UnicastFramesFilter_HashTable) || \
                                              ((FILTER) == ETH_UnicastFramesFilter_Perfect))

/**
  * @}
  */

/** @defgroup ETH_Pause_Time
  * @{
  */
#define IS_ETH_PAUSE_TIME(TIME) ((TIME) <= 0xFFFF)

/**
  * @}
  */

/** @defgroup ETH_Zero_Quanta_Pause
  * @{
  */
#define ETH_ZeroQuantaPause_Enable     ((uint32_t)0x00000000)
#define ETH_ZeroQuantaPause_Disable    ((uint32_t)0x00000080)
#define IS_ETH_ZEROQUANTA_PAUSE(CMD)   (((CMD) == ETH_ZeroQuantaPause_Enable) || \
                                        ((CMD) == ETH_ZeroQuantaPause_Disable))
/**
  * @}
  */

/** @defgroup ETH_Pause_Low_Threshold
  * @{
  */
#define ETH_PauseLowThreshold_Minus4        ((uint32_t)0x00000000)  /*!< Pause time minus 4 slot times */
#define ETH_PauseLowThreshold_Minus28       ((uint32_t)0x00000010)  /*!< Pause time minus 28 slot times */
#define ETH_PauseLowThreshold_Minus144      ((uint32_t)0x00000020)  /*!< Pause time minus 144 slot times */
#define ETH_PauseLowThreshold_Minus256      ((uint32_t)0x00000030)  /*!< Pause time minus 256 slot times */
#define IS_ETH_PAUSE_LOW_THRESHOLD(THRESHOLD) (((THRESHOLD) == ETH_PauseLowThreshold_Minus4) || \
                                               ((THRESHOLD) == ETH_PauseLowThreshold_Minus28) || \
                                               ((THRESHOLD) == ETH_PauseLowThreshold_Minus144) || \
                                               ((THRESHOLD) == ETH_PauseLowThreshold_Minus256))

/**
  * @}
  */

/** @defgroup ETH_Unicast_Pause_Frame_Detect
  * @{
  */
#define ETH_UnicastPauseFrameDetect_Enable  ((uint32_t)0x00000008)
#define ETH_UnicastPauseFrameDetect_Disable ((uint32_t)0x00000000)
#define IS_ETH_UNICAST_PAUSE_FRAME_DETECT(CMD) (((CMD) == ETH_UnicastPauseFrameDetect_Enable) || \
                                                ((CMD) == ETH_UnicastPauseFrameDetect_Disable))

/**
  * @}
  */

/** @defgroup ETH_Receive_Flow_Control
  * @{
  */
#define ETH_ReceiveFlowControl_Enable       ((uint32_t)0x00000004)
#define ETH_ReceiveFlowControl_Disable      ((uint32_t)0x00000000)
#define IS_ETH_RECEIVE_FLOWCONTROL(CMD) (((CMD) == ETH_ReceiveFlowControl_Enable) || \
                                         ((CMD) == ETH_ReceiveFlowControl_Disable))

/**
  * @}
  */

/** @defgroup ETH_Transmit_Flow_Control
  * @{
  */
#define ETH_TransmitFlowControl_Enable      ((uint32_t)0x00000002)
#define ETH_TransmitFlowControl_Disable     ((uint32_t)0x00000000)
#define IS_ETH_TRANSMIT_FLOWCONTROL(CMD) (((CMD) == ETH_TransmitFlowControl_Enable) || \
                                          ((CMD) == ETH_TransmitFlowControl_Disable))

/**
  * @}
  */

/** @defgroup ETH_VLAN_Tag_Comparison
  * @{
  */
#define ETH_VLANTagComparison_12Bit    ((uint32_t)0x00010000)
#define ETH_VLANTagComparison_16Bit    ((uint32_t)0x00000000)
#define IS_ETH_VLAN_TAG_COMPARISON(COMPARISON) (((COMPARISON) == ETH_VLANTagComparison_12Bit) || \
                                                ((COMPARISON) == ETH_VLANTagComparison_16Bit))
#define IS_ETH_VLAN_TAG_IDENTIFIER(IDENTIFIER) ((IDENTIFIER) <= 0xFFFF)

/**
  * @}
  */

/** @defgroup ETH_MAC_Flags
  * @{
  */
#define ETH_MAC_FLAG_TST     ((uint32_t)0x00000200)  /*!< Time stamp trigger flag (on MAC) */
#define ETH_MAC_FLAG_MMCT    ((uint32_t)0x00000040)  /*!< MMC transmit flag  */
#define ETH_MAC_FLAG_MMCR    ((uint32_t)0x00000020)  /*!< MMC receive flag */
#define ETH_MAC_FLAG_MMC     ((uint32_t)0x00000010)  /*!< MMC flag (on MAC) */
#define ETH_MAC_FLAG_PMT     ((uint32_t)0x00000008)  /*!< PMT flag (on MAC) */
#define IS_ETH_MAC_GET_FLAG(FLAG) (((FLAG) == ETH_MAC_FLAG_TST) || ((FLAG) == ETH_MAC_FLAG_MMCT) || \
                                   ((FLAG) == ETH_MAC_FLAG_MMCR) || ((FLAG) == ETH_MAC_FLAG_MMC) || \
                                   ((FLAG) == ETH_MAC_FLAG_PMT))
/**
  * @}
  */

/** @defgroup ETH_MAC_Interrupts
  * @{
  */
#define ETH_MAC_IT_TST       ((uint32_t)0x00000200)  /*!< Time stamp trigger interrupt (on MAC) */
#define ETH_MAC_IT_MMCT      ((uint32_t)0x00000040)  /*!< MMC transmit interrupt */
#define ETH_MAC_IT_MMCR      ((uint32_t)0x00000020)  /*!< MMC receive interrupt */
#define ETH_MAC_IT_MMC       ((uint32_t)0x00000010)  /*!< MMC interrupt (on MAC) */
#define ETH_MAC_IT_PMT       ((uint32_t)0x00000008)  /*!< PMT interrupt (on MAC) */
#define IS_ETH_MAC_IT(IT) ((((IT) & (uint32_t)0xFFFFFDF7) == 0x00) && ((IT) != 0x00))
#define IS_ETH_MAC_GET_IT(IT) (((IT) == ETH_MAC_IT_TST) || ((IT) == ETH_MAC_IT_MMCT) || \
                               ((IT) == ETH_MAC_IT_MMCR) || ((IT) == ETH_MAC_IT_MMC) || \
                               ((IT) == ETH_MAC_IT_PMT))
/**
  * @}
  */

/** @defgroup ETH_MAC_addresses
  * @{
  */
#define ETH_MAC_Address0     ((uint32_t)0x00000000)
#define ETH_MAC_Address1     ((uint32_t)0x00000008)
#define ETH_MAC_Address2     ((uint32_t)0x00000010)
#define ETH_MAC_Address3     ((uint32_t)0x00000018)
#define IS_ETH_MAC_ADDRESS0123(ADDRESS) (((ADDRESS) == ETH_MAC_Address0) || \
                                         ((ADDRESS) == ETH_MAC_Address1) || \
                                         ((ADDRESS) == ETH_MAC_Address2) || \
                                         ((ADDRESS) == ETH_MAC_Address3))
#define IS_ETH_MAC_ADDRESS123(ADDRESS) (((ADDRESS) == ETH_MAC_Address1) || \
                                        ((ADDRESS) == ETH_MAC_Address2) || \
                                        ((ADDRESS) == ETH_MAC_Address3))
/**
  * @}
  */

/** @defgroup ETH_MAC_addresses_filter_SA_DA_filed_of_received_frames
  * @{
  */
#define ETH_MAC_AddressFilter_SA       ((uint32_t)0x00000000)
#define ETH_MAC_AddressFilter_DA       ((uint32_t)0x00000008)
#define IS_ETH_MAC_ADDRESS_FILTER(FILTER) (((FILTER) == ETH_MAC_AddressFilter_SA) || \
                                           ((FILTER) == ETH_MAC_AddressFilter_DA))
/**
  * @}
  */

/** @defgroup ETH_MAC_addresses_filter_Mask_bytes
  * @{
  */
#define ETH_MAC_AddressMask_Byte6      ((uint32_t)0x20000000)  /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MAC_AddressMask_Byte5      ((uint32_t)0x10000000)  /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MAC_AddressMask_Byte4      ((uint32_t)0x08000000)  /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MAC_AddressMask_Byte3      ((uint32_t)0x04000000)  /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MAC_AddressMask_Byte2      ((uint32_t)0x02000000)  /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MAC_AddressMask_Byte1      ((uint32_t)0x01000000)  /*!< Mask MAC Address low reg bits [70] */
#define IS_ETH_MAC_ADDRESS_MASK(MASK) (((MASK) == ETH_MAC_AddressMask_Byte6) || \
                                       ((MASK) == ETH_MAC_AddressMask_Byte5) || \
                                       ((MASK) == ETH_MAC_AddressMask_Byte4) || \
                                       ((MASK) == ETH_MAC_AddressMask_Byte3) || \
                                       ((MASK) == ETH_MAC_AddressMask_Byte2) || \
                                       ((MASK) == ETH_MAC_AddressMask_Byte1))

/**--------------------------------------------------------------------------**/
/**
  * @brief                      Ethernet DMA Desciptors defines
  */
/**--------------------------------------------------------------------------**/
/**
  * @}
  */

/** @defgroup ETH_DMA_Tx_descriptor_flags
  * @{
  */
#define IS_ETH_DMATxDESC_GET_FLAG(FLAG) (((FLAG) == ETH_DMATxDesc_OWN) || \
                                         ((FLAG) == ETH_DMATxDesc_IC) || \
                                         ((FLAG) == ETH_DMATxDesc_LS) || \
                                         ((FLAG) == ETH_DMATxDesc_FS) || \
                                         ((FLAG) == ETH_DMATxDesc_DC) || \
                                         ((FLAG) == ETH_DMATxDesc_DP) || \
                                         ((FLAG) == ETH_DMATxDesc_TTSE) || \
                                         ((FLAG) == ETH_DMATxDesc_TER) || \
                                         ((FLAG) == ETH_DMATxDesc_TCH) || \
                                         ((FLAG) == ETH_DMATxDesc_TTSS) || \
                                         ((FLAG) == ETH_DMATxDesc_IHE) || \
                                         ((FLAG) == ETH_DMATxDesc_ES) || \
                                         ((FLAG) == ETH_DMATxDesc_JT) || \
                                         ((FLAG) == ETH_DMATxDesc_FF) || \
                                         ((FLAG) == ETH_DMATxDesc_PCE) || \
                                         ((FLAG) == ETH_DMATxDesc_LCA) || \
                                         ((FLAG) == ETH_DMATxDesc_NC) || \
                                         ((FLAG) == ETH_DMATxDesc_LCO) || \
                                         ((FLAG) == ETH_DMATxDesc_EC) || \
                                         ((FLAG) == ETH_DMATxDesc_VF) || \
                                         ((FLAG) == ETH_DMATxDesc_CC) || \
                                         ((FLAG) == ETH_DMATxDesc_ED) || \
                                         ((FLAG) == ETH_DMATxDesc_UF) || \
                                         ((FLAG) == ETH_DMATxDesc_DB))

/**
  * @}
  */

/** @defgroup ETH_DMA_Tx_descriptor_segment
  * @{
  */
#define ETH_DMATxDesc_LastSegment      ((uint32_t)0x40000000)  /*!< Last Segment */
#define ETH_DMATxDesc_FirstSegment     ((uint32_t)0x20000000)  /*!< First Segment */
#define IS_ETH_DMA_TXDESC_SEGMENT(SEGMENT) (((SEGMENT) == ETH_DMATxDesc_LastSegment) || \
                                            ((SEGMENT) == ETH_DMATxDesc_FirstSegment))

/**
  * @}
  */

/** @defgroup ETH_DMA_Tx_descriptor_Checksum_Insertion_Control
  * @{
  */
#define ETH_DMATxDesc_ChecksumByPass             ((uint32_t)0x00000000)   /*!< Checksum engine bypass */
#define ETH_DMATxDesc_ChecksumIPV4Header         ((uint32_t)0x00400000)   /*!< IPv4 header checksum insertion  */
#define ETH_DMATxDesc_ChecksumTCPUDPICMPSegment  ((uint32_t)0x00800000)   /*!< TCP/UDP/ICMP checksum insertion. Pseudo header checksum is assumed to be present */
#define ETH_DMATxDesc_ChecksumTCPUDPICMPFull     ((uint32_t)0x00C00000)   /*!< TCP/UDP/ICMP checksum fully in hardware including pseudo header */
#define IS_ETH_DMA_TXDESC_CHECKSUM(CHECKSUM) (((CHECKSUM) == ETH_DMATxDesc_ChecksumByPass) || \
                                              ((CHECKSUM) == ETH_DMATxDesc_ChecksumIPV4Header) || \
                                              ((CHECKSUM) == ETH_DMATxDesc_ChecksumTCPUDPICMPSegment) || \
                                              ((CHECKSUM) == ETH_DMATxDesc_ChecksumTCPUDPICMPFull))
/**
  * @brief  ETH DMA Tx Desciptor buffer size
  */
#define IS_ETH_DMATxDESC_BUFFER_SIZE(SIZE) ((SIZE) <= 0x1FFF)

/**
  * @}
  */

/** @defgroup ETH_DMA_Rx_descriptor_flags
  * @{
  */
#define IS_ETH_DMARxDESC_GET_FLAG(FLAG) (((FLAG) == ETH_DMARxDesc_OWN) || \
                                         ((FLAG) == ETH_DMARxDesc_AFM) || \
                                         ((FLAG) == ETH_DMARxDesc_ES) || \
                                         ((FLAG) == ETH_DMARxDesc_DE) || \
                                         ((FLAG) == ETH_DMARxDesc_SAF) || \
                                         ((FLAG) == ETH_DMARxDesc_LE) || \
                                         ((FLAG) == ETH_DMARxDesc_OE) || \
                                         ((FLAG) == ETH_DMARxDesc_VLAN) || \
                                         ((FLAG) == ETH_DMARxDesc_FS) || \
                                         ((FLAG) == ETH_DMARxDesc_LS) || \
                                         ((FLAG) == ETH_DMARxDesc_IPV4HCE) || \
                                         ((FLAG) == ETH_DMARxDesc_LC) || \
                                         ((FLAG) == ETH_DMARxDesc_FT) || \
                                         ((FLAG) == ETH_DMARxDesc_RWT) || \
                                         ((FLAG) == ETH_DMARxDesc_RE) || \
                                         ((FLAG) == ETH_DMARxDesc_DBE) || \
                                         ((FLAG) == ETH_DMARxDesc_CE) || \
                                         ((FLAG) == ETH_DMARxDesc_MAMPCE))

/* ETHERNET DMA PTP Rx descriptor extended flags  --------------------------------*/
#define IS_ETH_DMAPTPRxDESC_GET_EXTENDED_FLAG(FLAG) (((FLAG) == ETH_DMAPTPRxDesc_PTPV) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_PTPFT) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_PTPMT) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_IPV6PR) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_IPV4PR) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_IPCB) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_IPPE) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_IPHE) || \
                                                     ((FLAG) == ETH_DMAPTPRxDesc_IPPT))

/**
  * @}
  */

/** @defgroup ETH_DMA_Rx_descriptor_buffers_
  * @{
  */
#define ETH_DMARxDesc_Buffer1     ((uint32_t)0x00000000)  /*!< DMA Rx Desc Buffer1 */
#define ETH_DMARxDesc_Buffer2     ((uint32_t)0x00000001)  /*!< DMA Rx Desc Buffer2 */
#define IS_ETH_DMA_RXDESC_BUFFER(BUFFER) (((BUFFER) == ETH_DMARxDesc_Buffer1) || \
                                          ((BUFFER) == ETH_DMARxDesc_Buffer2))

/**--------------------------------------------------------------------------**/
/**
  * @brief                           Ethernet DMA defines
  */
/**--------------------------------------------------------------------------**/
/**
  * @}
  */

/** @defgroup ETH_Drop_TCP_IP_Checksum_Error_Frame
  * @{
  */
#define ETH_DropTCPIPChecksumErrorFrame_Enable   ((uint32_t)0x00000000)
#define ETH_DropTCPIPChecksumErrorFrame_Disable  ((uint32_t)0x04000000)
#define IS_ETH_DROP_TCPIP_CHECKSUM_FRAME(CMD) (((CMD) == ETH_DropTCPIPChecksumErrorFrame_Enable) || \
                                               ((CMD) == ETH_DropTCPIPChecksumErrorFrame_Disable))
/**
  * @}
  */

/** @defgroup ETH_Receive_Store_Forward
  * @{
  */
#define ETH_ReceiveStoreForward_Enable      ((uint32_t)0x02000000)
#define ETH_ReceiveStoreForward_Disable     ((uint32_t)0x00000000)
#define IS_ETH_RECEIVE_STORE_FORWARD(CMD) (((CMD) == ETH_ReceiveStoreForward_Enable) || \
                                           ((CMD) == ETH_ReceiveStoreForward_Disable))
/**
  * @}
  */

/** @defgroup ETH_Flush_Received_Frame
  * @{
  */
#define ETH_FlushReceivedFrame_Enable       ((uint32_t)0x00000000)
#define ETH_FlushReceivedFrame_Disable      ((uint32_t)0x01000000)
#define IS_ETH_FLUSH_RECEIVE_FRAME(CMD) (((CMD) == ETH_FlushReceivedFrame_Enable) || \
                                         ((CMD) == ETH_FlushReceivedFrame_Disable))
/**
  * @}
  */

/** @defgroup ETH_Transmit_Store_Forward
  * @{
  */
#define ETH_TransmitStoreForward_Enable     ((uint32_t)0x00200000)
#define ETH_TransmitStoreForward_Disable    ((uint32_t)0x00000000)
#define IS_ETH_TRANSMIT_STORE_FORWARD(CMD) (((CMD) == ETH_TransmitStoreForward_Enable) || \
                                            ((CMD) == ETH_TransmitStoreForward_Disable))
/**
  * @}
  */

/** @defgroup ETH_Transmit_Threshold_Control
  * @{
  */
#define ETH_TransmitThresholdControl_64Bytes     ((uint32_t)0x00000000)  /*!< threshold level of the MTL Transmit FIFO is 64 Bytes */
#define ETH_TransmitThresholdControl_128Bytes    ((uint32_t)0x00004000)  /*!< threshold level of the MTL Transmit FIFO is 128 Bytes */
#define ETH_TransmitThresholdControl_192Bytes    ((uint32_t)0x00008000)  /*!< threshold level of the MTL Transmit FIFO is 192 Bytes */
#define ETH_TransmitThresholdControl_256Bytes    ((uint32_t)0x0000C000)  /*!< threshold level of the MTL Transmit FIFO is 256 Bytes */
#define ETH_TransmitThresholdControl_40Bytes     ((uint32_t)0x00010000)  /*!< threshold level of the MTL Transmit FIFO is 40 Bytes */
#define ETH_TransmitThresholdControl_32Bytes     ((uint32_t)0x00014000)  /*!< threshold level of the MTL Transmit FIFO is 32 Bytes */
#define ETH_TransmitThresholdControl_24Bytes     ((uint32_t)0x00018000)  /*!< threshold level of the MTL Transmit FIFO is 24 Bytes */
#define ETH_TransmitThresholdControl_16Bytes     ((uint32_t)0x0001C000)  /*!< threshold level of the MTL Transmit FIFO is 16 Bytes */
#define IS_ETH_TRANSMIT_THRESHOLD_CONTROL(THRESHOLD) (((THRESHOLD) == ETH_TransmitThresholdControl_64Bytes) || \
                                                      ((THRESHOLD) == ETH_TransmitThresholdControl_128Bytes) || \
                                                      ((THRESHOLD) == ETH_TransmitThresholdControl_192Bytes) || \
                                                      ((THRESHOLD) == ETH_TransmitThresholdControl_256Bytes) || \
                                                      ((THRESHOLD) == ETH_TransmitThresholdControl_40Bytes) || \
                                                      ((THRESHOLD) == ETH_TransmitThresholdControl_32Bytes) || \
                                                      ((THRESHOLD) == ETH_TransmitThresholdControl_24Bytes) || \
                                                      ((THRESHOLD) == ETH_TransmitThresholdControl_16Bytes))
/**
  * @}
  */

/** @defgroup ETH_Forward_Error_Frames
  * @{
  */
#define ETH_ForwardErrorFrames_Enable       ((uint32_t)0x00000080)
#define ETH_ForwardErrorFrames_Disable      ((uint32_t)0x00000000)
#define IS_ETH_FORWARD_ERROR_FRAMES(CMD) (((CMD) == ETH_ForwardErrorFrames_Enable) || \
                                          ((CMD) == ETH_ForwardErrorFrames_Disable))
/**
  * @}
  */

/** @defgroup ETH_Forward_Undersized_Good_Frames
  * @{
  */
#define ETH_ForwardUndersizedGoodFrames_Enable   ((uint32_t)0x00000040)
#define ETH_ForwardUndersizedGoodFrames_Disable  ((uint32_t)0x00000000)
#define IS_ETH_FORWARD_UNDERSIZED_GOOD_FRAMES(CMD) (((CMD) == ETH_ForwardUndersizedGoodFrames_Enable) || \
                                                    ((CMD) == ETH_ForwardUndersizedGoodFrames_Disable))

/**
  * @}
  */

/** @defgroup ETH_Receive_Threshold_Control
  * @{
  */
#define ETH_ReceiveThresholdControl_64Bytes      ((uint32_t)0x00000000)  /*!< threshold level of the MTL Receive FIFO is 64 Bytes */
#define ETH_ReceiveThresholdControl_32Bytes      ((uint32_t)0x00000008)  /*!< threshold level of the MTL Receive FIFO is 32 Bytes */
#define ETH_ReceiveThresholdControl_96Bytes      ((uint32_t)0x00000010)  /*!< threshold level of the MTL Receive FIFO is 96 Bytes */
#define ETH_ReceiveThresholdControl_128Bytes     ((uint32_t)0x00000018)  /*!< threshold level of the MTL Receive FIFO is 128 Bytes */
#define IS_ETH_RECEIVE_THRESHOLD_CONTROL(THRESHOLD) (((THRESHOLD) == ETH_ReceiveThresholdControl_64Bytes) || \
                                                     ((THRESHOLD) == ETH_ReceiveThresholdControl_32Bytes) || \
                                                     ((THRESHOLD) == ETH_ReceiveThresholdControl_96Bytes) || \
                                                     ((THRESHOLD) == ETH_ReceiveThresholdControl_128Bytes))
/**
  * @}
  */

/** @defgroup ETH_Second_Frame_Operate
  * @{
  */
#define ETH_SecondFrameOperate_Enable       ((uint32_t)0x00000004)
#define ETH_SecondFrameOperate_Disable      ((uint32_t)0x00000000)
#define IS_ETH_SECOND_FRAME_OPERATE(CMD) (((CMD) == ETH_SecondFrameOperate_Enable) || \
                                          ((CMD) == ETH_SecondFrameOperate_Disable))

/**
  * @}
  */

/** @defgroup ETH_Address_Aligned_Beats
  * @{
  */
#define ETH_AddressAlignedBeats_Enable      ((uint32_t)0x02000000)
#define ETH_AddressAlignedBeats_Disable     ((uint32_t)0x00000000)
#define IS_ETH_ADDRESS_ALIGNED_BEATS(CMD) (((CMD) == ETH_AddressAlignedBeats_Enable) || \
                                           ((CMD) == ETH_AddressAlignedBeats_Disable))

/**
  * @}
  */

/** @defgroup ETH_Fixed_Burst
  * @{
  */
#define ETH_FixedBurst_Enable     ((uint32_t)0x00010000)
#define ETH_FixedBurst_Disable    ((uint32_t)0x00000000)
#define IS_ETH_FIXED_BURST(CMD) (((CMD) == ETH_FixedBurst_Enable) || \
                                 ((CMD) == ETH_FixedBurst_Disable))

/**
  * @}
  */

/** @defgroup ETH_Rx_DMA_Burst_Length
  * @{
  */
#define ETH_RxDMABurstLength_1Beat          ((uint32_t)0x00020000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define ETH_RxDMABurstLength_2Beat          ((uint32_t)0x00040000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define ETH_RxDMABurstLength_4Beat          ((uint32_t)0x00080000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_RxDMABurstLength_8Beat          ((uint32_t)0x00100000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_RxDMABurstLength_16Beat         ((uint32_t)0x00200000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_RxDMABurstLength_32Beat         ((uint32_t)0x00400000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_RxDMABurstLength_4xPBL_4Beat    ((uint32_t)0x01020000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_RxDMABurstLength_4xPBL_8Beat    ((uint32_t)0x01040000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_RxDMABurstLength_4xPBL_16Beat   ((uint32_t)0x01080000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_RxDMABurstLength_4xPBL_32Beat   ((uint32_t)0x01100000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_RxDMABurstLength_4xPBL_64Beat   ((uint32_t)0x01200000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define ETH_RxDMABurstLength_4xPBL_128Beat  ((uint32_t)0x01400000)  /*!< maximum number of beats to be transferred in one RxDMA transaction is 128 */

#define IS_ETH_RXDMA_BURST_LENGTH(LENGTH) (((LENGTH) == ETH_RxDMABurstLength_1Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_2Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_4Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_8Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_16Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_32Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_4xPBL_4Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_4xPBL_8Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_4xPBL_16Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_4xPBL_32Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_4xPBL_64Beat) || \
                                           ((LENGTH) == ETH_RxDMABurstLength_4xPBL_128Beat))

/**
  * @}
  */

/** @defgroup ETH_Tx_DMA_Burst_Length
  * @{
  */
#define ETH_TxDMABurstLength_1Beat          ((uint32_t)0x00000100)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define ETH_TxDMABurstLength_2Beat          ((uint32_t)0x00000200)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define ETH_TxDMABurstLength_4Beat          ((uint32_t)0x00000400)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_TxDMABurstLength_8Beat          ((uint32_t)0x00000800)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_TxDMABurstLength_16Beat         ((uint32_t)0x00001000)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_TxDMABurstLength_32Beat         ((uint32_t)0x00002000)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_TxDMABurstLength_4xPBL_4Beat    ((uint32_t)0x01000100)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_TxDMABurstLength_4xPBL_8Beat    ((uint32_t)0x01000200)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_TxDMABurstLength_4xPBL_16Beat   ((uint32_t)0x01000400)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_TxDMABurstLength_4xPBL_32Beat   ((uint32_t)0x01000800)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_TxDMABurstLength_4xPBL_64Beat   ((uint32_t)0x01001000)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define ETH_TxDMABurstLength_4xPBL_128Beat  ((uint32_t)0x01002000)  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */

#define IS_ETH_TXDMA_BURST_LENGTH(LENGTH) (((LENGTH) == ETH_TxDMABurstLength_1Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_2Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_4Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_8Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_16Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_32Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_4xPBL_4Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_4xPBL_8Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_4xPBL_16Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_4xPBL_32Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_4xPBL_64Beat) || \
                                           ((LENGTH) == ETH_TxDMABurstLength_4xPBL_128Beat))
/**
  * @brief  ETH DMA Desciptor SkipLength
  */
#define IS_ETH_DMA_DESC_SKIP_LENGTH(LENGTH) ((LENGTH) <= 0x1F)

/**
  * @}
  */

/** @defgroup ETH_DMA_Arbitration
  * @{
  */
#define ETH_DMAArbitration_RoundRobin_RxTx_1_1   ((uint32_t)0x00000000)
#define ETH_DMAArbitration_RoundRobin_RxTx_2_1   ((uint32_t)0x00004000)
#define ETH_DMAArbitration_RoundRobin_RxTx_3_1   ((uint32_t)0x00008000)
#define ETH_DMAArbitration_RoundRobin_RxTx_4_1   ((uint32_t)0x0000C000)
#define ETH_DMAArbitration_RxPriorTx             ((uint32_t)0x00000002)
#define IS_ETH_DMA_ARBITRATION_ROUNDROBIN_RXTX(RATIO) (((RATIO) == ETH_DMAArbitration_RoundRobin_RxTx_1_1) || \
                                                       ((RATIO) == ETH_DMAArbitration_RoundRobin_RxTx_2_1) || \
                                                       ((RATIO) == ETH_DMAArbitration_RoundRobin_RxTx_3_1) || \
                                                       ((RATIO) == ETH_DMAArbitration_RoundRobin_RxTx_4_1) || \
                                                       ((RATIO) == ETH_DMAArbitration_RxPriorTx))
/**
  * @}
  */

/** @defgroup ETH_DMA_Flags
  * @{
  */
#define ETH_DMA_FLAG_TST               ((uint32_t)0x20000000)  /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_FLAG_PMT               ((uint32_t)0x10000000)  /*!< PMT interrupt (on DMA) */
#define ETH_DMA_FLAG_MMC               ((uint32_t)0x08000000)  /*!< MMC interrupt (on DMA) */
#define ETH_DMA_FLAG_DataTransferError ((uint32_t)0x00800000)  /*!< Error bits 0-Rx DMA, 1-Tx DMA */
#define ETH_DMA_FLAG_ReadWriteError    ((uint32_t)0x01000000)  /*!< Error bits 0-write trnsf, 1-read transfr */
#define ETH_DMA_FLAG_AccessError       ((uint32_t)0x02000000)  /*!< Error bits 0-data buffer, 1-desc. access */
#define ETH_DMA_FLAG_NIS               ((uint32_t)0x00010000)  /*!< Normal interrupt summary flag */
#define ETH_DMA_FLAG_AIS               ((uint32_t)0x00008000)  /*!< Abnormal interrupt summary flag */
#define ETH_DMA_FLAG_ER                ((uint32_t)0x00004000)  /*!< Early receive flag */
#define ETH_DMA_FLAG_FBE               ((uint32_t)0x00002000)  /*!< Fatal bus error flag */
#define ETH_DMA_FLAG_ET                ((uint32_t)0x00000400)  /*!< Early transmit flag */
#define ETH_DMA_FLAG_RWT               ((uint32_t)0x00000200)  /*!< Receive watchdog timeout flag */
#define ETH_DMA_FLAG_RPS               ((uint32_t)0x00000100)  /*!< Receive process stopped flag */
#define ETH_DMA_FLAG_RBU               ((uint32_t)0x00000080)  /*!< Receive buffer unavailable flag */
#define ETH_DMA_FLAG_R                 ((uint32_t)0x00000040)  /*!< Receive flag */
#define ETH_DMA_FLAG_TU                ((uint32_t)0x00000020)  /*!< Underflow flag */
#define ETH_DMA_FLAG_RO                ((uint32_t)0x00000010)  /*!< Overflow flag */
#define ETH_DMA_FLAG_TJT               ((uint32_t)0x00000008)  /*!< Transmit jabber timeout flag */
#define ETH_DMA_FLAG_TBU               ((uint32_t)0x00000004)  /*!< Transmit buffer unavailable flag */
#define ETH_DMA_FLAG_TPS               ((uint32_t)0x00000002)  /*!< Transmit process stopped flag */
#define ETH_DMA_FLAG_T                 ((uint32_t)0x00000001)  /*!< Transmit flag */

#define IS_ETH_DMA_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFE1800) == 0x00) && ((FLAG) != 0x00))
#define IS_ETH_DMA_GET_FLAG(FLAG) (((FLAG) == ETH_DMA_FLAG_TST) || ((FLAG) == ETH_DMA_FLAG_PMT) || \
                                   ((FLAG) == ETH_DMA_FLAG_MMC) || ((FLAG) == ETH_DMA_FLAG_DataTransferError) || \
                                   ((FLAG) == ETH_DMA_FLAG_ReadWriteError) || ((FLAG) == ETH_DMA_FLAG_AccessError) || \
                                   ((FLAG) == ETH_DMA_FLAG_NIS) || ((FLAG) == ETH_DMA_FLAG_AIS) || \
                                   ((FLAG) == ETH_DMA_FLAG_ER) || ((FLAG) == ETH_DMA_FLAG_FBE) || \
                                   ((FLAG) == ETH_DMA_FLAG_ET) || ((FLAG) == ETH_DMA_FLAG_RWT) || \
                                   ((FLAG) == ETH_DMA_FLAG_RPS) || ((FLAG) == ETH_DMA_FLAG_RBU) || \
                                   ((FLAG) == ETH_DMA_FLAG_R) || ((FLAG) == ETH_DMA_FLAG_TU) || \
                                   ((FLAG) == ETH_DMA_FLAG_RO) || ((FLAG) == ETH_DMA_FLAG_TJT) || \
                                   ((FLAG) == ETH_DMA_FLAG_TBU) || ((FLAG) == ETH_DMA_FLAG_TPS) || \
                                   ((FLAG) == ETH_DMA_FLAG_T))
/**
  * @}
  */

/** @defgroup ETH_DMA_Interrupts
  * @{
  */
#define ETH_DMA_IT_TST       ((uint32_t)0x20000000)  /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_IT_PMT       ((uint32_t)0x10000000)  /*!< PMT interrupt (on DMA) */
#define ETH_DMA_IT_MMC       ((uint32_t)0x08000000)  /*!< MMC interrupt (on DMA) */
#define ETH_DMA_IT_NIS       ((uint32_t)0x00010000)  /*!< Normal interrupt summary */
#define ETH_DMA_IT_AIS       ((uint32_t)0x00008000)  /*!< Abnormal interrupt summary */
#define ETH_DMA_IT_ER        ((uint32_t)0x00004000)  /*!< Early receive interrupt */
#define ETH_DMA_IT_FBE       ((uint32_t)0x00002000)  /*!< Fatal bus error interrupt */
#define ETH_DMA_IT_ET        ((uint32_t)0x00000400)  /*!< Early transmit interrupt */
#define ETH_DMA_IT_RWT       ((uint32_t)0x00000200)  /*!< Receive watchdog timeout interrupt */
#define ETH_DMA_IT_RPS       ((uint32_t)0x00000100)  /*!< Receive process stopped interrupt */
#define ETH_DMA_IT_RBU       ((uint32_t)0x00000080)  /*!< Receive buffer unavailable interrupt */
#define ETH_DMA_IT_R         ((uint32_t)0x00000040)  /*!< Receive interrupt */
#define ETH_DMA_IT_TU        ((uint32_t)0x00000020)  /*!< Underflow interrupt */
#define ETH_DMA_IT_RO        ((uint32_t)0x00000010)  /*!< Overflow interrupt */
#define ETH_DMA_IT_TJT       ((uint32_t)0x00000008)  /*!< Transmit jabber timeout interrupt */
#define ETH_DMA_IT_TBU       ((uint32_t)0x00000004)  /*!< Transmit buffer unavailable interrupt */
#define ETH_DMA_IT_TPS       ((uint32_t)0x00000002)  /*!< Transmit process stopped interrupt */
#define ETH_DMA_IT_T         ((uint32_t)0x00000001)  /*!< Transmit interrupt */

#define IS_ETH_DMA_IT(IT) ((((IT) & (uint32_t)0xFFFE1800) == 0x00) && ((IT) != 0x00))
#define IS_ETH_DMA_GET_IT(IT) (((IT) == ETH_DMA_IT_TST) || ((IT) == ETH_DMA_IT_PMT) || \
                               ((IT) == ETH_DMA_IT_MMC) || ((IT) == ETH_DMA_IT_NIS) || \
                               ((IT) == ETH_DMA_IT_AIS) || ((IT) == ETH_DMA_IT_ER) || \
                               ((IT) == ETH_DMA_IT_FBE) || ((IT) == ETH_DMA_IT_ET) || \
                               ((IT) == ETH_DMA_IT_RWT) || ((IT) == ETH_DMA_IT_RPS) || \
                               ((IT) == ETH_DMA_IT_RBU) || ((IT) == ETH_DMA_IT_R) || \
                               ((IT) == ETH_DMA_IT_TU) || ((IT) == ETH_DMA_IT_RO) || \
                               ((IT) == ETH_DMA_IT_TJT) || ((IT) == ETH_DMA_IT_TBU) || \
                               ((IT) == ETH_DMA_IT_TPS) || ((IT) == ETH_DMA_IT_T))

/**
  * @}
  */

/** @defgroup ETH_DMA_transmit_process_state_
  * @{
  */
#define ETH_DMA_TransmitProcess_Stopped     ((uint32_t)0x00000000)  /*!< Stopped - Reset or Stop Tx Command issued */
#define ETH_DMA_TransmitProcess_Fetching    ((uint32_t)0x00100000)  /*!< Running - fetching the Tx descriptor */
#define ETH_DMA_TransmitProcess_Waiting     ((uint32_t)0x00200000)  /*!< Running - waiting for status */
#define ETH_DMA_TransmitProcess_Reading     ((uint32_t)0x00300000)  /*!< Running - reading the data from host memory */
#define ETH_DMA_TransmitProcess_Suspended   ((uint32_t)0x00600000)  /*!< Suspended - Tx Desciptor unavailabe */
#define ETH_DMA_TransmitProcess_Closing     ((uint32_t)0x00700000)  /*!< Running - closing Rx descriptor */

/**
  * @}
  */


/** @defgroup ETH_DMA_receive_process_state_
  * @{
  */
#define ETH_DMA_ReceiveProcess_Stopped      ((uint32_t)0x00000000)  /*!< Stopped - Reset or Stop Rx Command issued */
#define ETH_DMA_ReceiveProcess_Fetching     ((uint32_t)0x00020000)  /*!< Running - fetching the Rx descriptor */
#define ETH_DMA_ReceiveProcess_Waiting      ((uint32_t)0x00060000)  /*!< Running - waiting for packet */
#define ETH_DMA_ReceiveProcess_Suspended    ((uint32_t)0x00080000)  /*!< Suspended - Rx Desciptor unavailable */
#define ETH_DMA_ReceiveProcess_Closing      ((uint32_t)0x000A0000)  /*!< Running - closing descriptor */
#define ETH_DMA_ReceiveProcess_Queuing      ((uint32_t)0x000E0000)  /*!< Running - queuing the recieve frame into host memory */

/**
  * @}
  */

/** @defgroup ETH_DMA_overflow_
  * @{
  */
#define ETH_DMA_Overflow_RxFIFOCounter      ((uint32_t)0x10000000)  /*!< Overflow bit for FIFO overflow counter */
#define ETH_DMA_Overflow_MissedFrameCounter ((uint32_t)0x00010000)  /*!< Overflow bit for missed frame counter */
#define IS_ETH_DMA_GET_OVERFLOW(OVERFLOW) (((OVERFLOW) == ETH_DMA_Overflow_RxFIFOCounter) || \
                                           ((OVERFLOW) == ETH_DMA_Overflow_MissedFrameCounter))

/**--------------------------------------------------------------------------**/
/**
  * @brief                           Ethernet PMT defines
  */
/**--------------------------------------------------------------------------**/
/**
  * @}
  */

/** @defgroup ETH_PMT_Flags
  * @{
  */
#define ETH_PMT_FLAG_WUFFRPR      ((uint32_t)0x80000000)  /*!< Wake-Up Frame Filter Register Poniter Reset */
#define ETH_PMT_FLAG_WUFR         ((uint32_t)0x00000040)  /*!< Wake-Up Frame Received */
#define ETH_PMT_FLAG_MPR          ((uint32_t)0x00000020)  /*!< Magic Packet Received */
#define IS_ETH_PMT_GET_FLAG(FLAG) (((FLAG) == ETH_PMT_FLAG_WUFR) || \
                                   ((FLAG) == ETH_PMT_FLAG_MPR))

/**--------------------------------------------------------------------------**/
/**
  * @brief                           Ethernet MMC defines
  */
/**--------------------------------------------------------------------------**/
/**
  * @}
  */

/** @defgroup ETH_MMC_Tx_Interrupts
  * @{
  */
#define ETH_MMC_IT_TGF       ((uint32_t)0x00200000)  /*!< When Tx good frame counter reaches half the maximum value */
#define ETH_MMC_IT_TGFMSC    ((uint32_t)0x00008000)  /*!< When Tx good multi col counter reaches half the maximum value */
#define ETH_MMC_IT_TGFSC     ((uint32_t)0x00004000)  /*!< When Tx good single col counter reaches half the maximum value */

/**
  * @}
  */

/** @defgroup ETH_MMC_Rx_Interrupts
  * @{
  */
#define ETH_MMC_IT_RGUF      ((uint32_t)0x10020000)  /*!< When Rx good unicast frames counter reaches half the maximum value */
#define ETH_MMC_IT_RFAE      ((uint32_t)0x10000040)  /*!< When Rx alignment error counter reaches half the maximum value */
#define ETH_MMC_IT_RFCE      ((uint32_t)0x10000020)  /*!< When Rx crc error counter reaches half the maximum value */
#define IS_ETH_MMC_IT(IT) (((((IT) & (uint32_t)0xFFDF3FFF) == 0x00) || (((IT) & (uint32_t)0xEFFDFF9F) == 0x00)) && \
                           ((IT) != 0x00))
#define IS_ETH_MMC_GET_IT(IT) (((IT) == ETH_MMC_IT_TGF) || ((IT) == ETH_MMC_IT_TGFMSC) || \
                               ((IT) == ETH_MMC_IT_TGFSC) || ((IT) == ETH_MMC_IT_RGUF) || \
                               ((IT) == ETH_MMC_IT_RFAE) || ((IT) == ETH_MMC_IT_RFCE))
/**
  * @}
  */

/** @defgroup ETH_MMC_Registers
  * @{
  */
#define ETH_MMCCR            ((uint32_t)0x00000100)  /*!< MMC CR register */
#define ETH_MMCRIR           ((uint32_t)0x00000104)  /*!< MMC RIR register */
#define ETH_MMCTIR           ((uint32_t)0x00000108)  /*!< MMC TIR register */
#define ETH_MMCRIMR          ((uint32_t)0x0000010C)  /*!< MMC RIMR register */
#define ETH_MMCTIMR          ((uint32_t)0x00000110)  /*!< MMC TIMR register */
#define ETH_MMCTGFSCCR       ((uint32_t)0x0000014C)  /*!< MMC TGFSCCR register */
#define ETH_MMCTGFMSCCR      ((uint32_t)0x00000150)  /*!< MMC TGFMSCCR register */
#define ETH_MMCTGFCR         ((uint32_t)0x00000168)  /*!< MMC TGFCR register */
#define ETH_MMCRFCECR        ((uint32_t)0x00000194)  /*!< MMC RFCECR register */
#define ETH_MMCRFAECR        ((uint32_t)0x00000198)  /*!< MMC RFAECR register */
#define ETH_MMCRGUFCR        ((uint32_t)0x000001C4)  /*!< MMC RGUFCR register */

/**
  * @brief  ETH MMC registers
  */
#define IS_ETH_MMC_REGISTER(REG) (((REG) == ETH_MMCCR)  || ((REG) == ETH_MMCRIR) || \
                                  ((REG) == ETH_MMCTIR)  || ((REG) == ETH_MMCRIMR) || \
                                  ((REG) == ETH_MMCTIMR) || ((REG) == ETH_MMCTGFSCCR) || \
                                  ((REG) == ETH_MMCTGFMSCCR) || ((REG) == ETH_MMCTGFCR) || \
                                  ((REG) == ETH_MMCRFCECR) || ((REG) == ETH_MMCRFAECR) || \
                                  ((REG) == ETH_MMCRGUFCR))

/**--------------------------------------------------------------------------**/
/**
  * @brief                           Ethernet PTP defines
  */
/**--------------------------------------------------------------------------**/
/**
  * @}
  */

/** @defgroup ETH_PTP_time_update_method
  * @{
  */
#define ETH_PTP_FineUpdate        ((uint32_t)0x00000001)  /*!< Fine Update method */
#define ETH_PTP_CoarseUpdate      ((uint32_t)0x00000000)  /*!< Coarse Update method */
#define IS_ETH_PTP_UPDATE(UPDATE) (((UPDATE) == ETH_PTP_FineUpdate) || \
                                   ((UPDATE) == ETH_PTP_CoarseUpdate))

/**
  * @}
  */


/** @defgroup ETH_PTP_Flags
  * @{
  */
#define ETH_PTP_FLAG_TSARU        ((uint32_t)0x00000020)  /*!< Addend Register Update */
#define ETH_PTP_FLAG_TSITE        ((uint32_t)0x00000010)  /*!< Time Stamp Interrupt Trigger */
#define ETH_PTP_FLAG_TSSTU        ((uint32_t)0x00000008)  /*!< Time Stamp Update */
#define ETH_PTP_FLAG_TSSTI        ((uint32_t)0x00000004)  /*!< Time Stamp Initialize */

#define ETH_PTP_FLAG_TSTTR        ((uint32_t)0x10000002)  /* Time stamp target time reached */
#define ETH_PTP_FLAG_TSSO         ((uint32_t)0x10000001)  /* Time stamp seconds overflow */

#define IS_ETH_PTP_GET_FLAG(FLAG) (((FLAG) == ETH_PTP_FLAG_TSARU) || \
                                    ((FLAG) == ETH_PTP_FLAG_TSITE) || \
                                    ((FLAG) == ETH_PTP_FLAG_TSSTU) || \
                                    ((FLAG) == ETH_PTP_FLAG_TSSTI) || \
                                    ((FLAG) == ETH_PTP_FLAG_TSTTR) || \
                                    ((FLAG) == ETH_PTP_FLAG_TSSO))

/**
  * @brief  ETH PTP subsecond increment
  */
#define IS_ETH_PTP_SUBSECOND_INCREMENT(SUBSECOND) ((SUBSECOND) <= 0xFF)

/**
  * @}
  */


/** @defgroup ETH_PTP_time_sign
  * @{
  */
#define ETH_PTP_PositiveTime      ((uint32_t)0x00000000)  /*!< Positive time value */
#define ETH_PTP_NegativeTime      ((uint32_t)0x80000000)  /*!< Negative time value */
#define IS_ETH_PTP_TIME_SIGN(SIGN) (((SIGN) == ETH_PTP_PositiveTime) || \
                                    ((SIGN) == ETH_PTP_NegativeTime))

/**
  * @brief  ETH PTP time stamp low update
  */
#define IS_ETH_PTP_TIME_STAMP_UPDATE_SUBSECOND(SUBSECOND) ((SUBSECOND) <= 0x7FFFFFFF)

/**
  * @brief  ETH PTP registers
  */
#define ETH_PTPTSCR     ((uint32_t)0x00000700)  /*!< PTP TSCR register */
#define ETH_PTPSSIR     ((uint32_t)0x00000704)  /*!< PTP SSIR register */
#define ETH_PTPTSHR     ((uint32_t)0x00000708)  /*!< PTP TSHR register */
#define ETH_PTPTSLR     ((uint32_t)0x0000070C)  /*!< PTP TSLR register */
#define ETH_PTPTSHUR    ((uint32_t)0x00000710)  /*!< PTP TSHUR register */
#define ETH_PTPTSLUR    ((uint32_t)0x00000714)  /*!< PTP TSLUR register */
#define ETH_PTPTSAR     ((uint32_t)0x00000718)  /*!< PTP TSAR register */
#define ETH_PTPTTHR     ((uint32_t)0x0000071C)  /*!< PTP TTHR register */
#define ETH_PTPTTLR     ((uint32_t)0x00000720)  /* PTP TTLR register */

#define ETH_PTPTSSR     ((uint32_t)0x00000728)  /* PTP TSSR register */

#define IS_ETH_PTP_REGISTER(REG) (((REG) == ETH_PTPTSCR) || ((REG) == ETH_PTPSSIR) || \
                                   ((REG) == ETH_PTPTSHR) || ((REG) == ETH_PTPTSLR) || \
                                   ((REG) == ETH_PTPTSHUR) || ((REG) == ETH_PTPTSLUR) || \
                                   ((REG) == ETH_PTPTSAR) || ((REG) == ETH_PTPTTHR) || \
                                   ((REG) == ETH_PTPTTLR) || ((REG) == ETH_PTPTSSR))

/**
  * @brief  ETHERNET PTP clock
  */
#define ETH_PTP_OrdinaryClock               ((uint32_t)0x00000000)  /* Ordinary Clock */
#define ETH_PTP_BoundaryClock               ((uint32_t)0x00010000)  /* Boundary Clock */
#define ETH_PTP_EndToEndTransparentClock    ((uint32_t)0x00020000)  /* End To End Transparent Clock */
#define ETH_PTP_PeerToPeerTransparentClock  ((uint32_t)0x00030000)  /* Peer To Peer Transparent Clock */

#define IS_ETH_PTP_TYPE_CLOCK(CLOCK) (((CLOCK) == ETH_PTP_OrdinaryClock) || \
                          ((CLOCK) == ETH_PTP_BoundaryClock) || \
                          ((CLOCK) == ETH_PTP_EndToEndTransparentClock) || \
                                      ((CLOCK) == ETH_PTP_PeerToPeerTransparentClock))
/**
  * @brief  ETHERNET snapshot
  */
#define ETH_PTP_SnapshotMasterMessage          ((uint32_t)0x00008000)  /* Time stamp snapshot for message relevant to master enable */
#define ETH_PTP_SnapshotEventMessage           ((uint32_t)0x00004000)  /* Time stamp snapshot for event message enable */
#define ETH_PTP_SnapshotIPV4Frames             ((uint32_t)0x00002000)  /* Time stamp snapshot for IPv4 frames enable */
#define ETH_PTP_SnapshotIPV6Frames             ((uint32_t)0x00001000)  /* Time stamp snapshot for IPv6 frames enable */
#define ETH_PTP_SnapshotPTPOverEthernetFrames  ((uint32_t)0x00000800)  /* Time stamp snapshot for PTP over ethernet frames enable */
#define ETH_PTP_SnapshotAllReceivedFrames      ((uint32_t)0x00000100)  /* Time stamp snapshot for all received frames enable */

#define IS_ETH_PTP_SNAPSHOT(SNAPSHOT) (((SNAPSHOT) == ETH_PTP_SnapshotMasterMessage) || \
                           ((SNAPSHOT) == ETH_PTP_SnapshotEventMessage) || \
                           ((SNAPSHOT) == ETH_PTP_SnapshotIPV4Frames) || \
                           ((SNAPSHOT) == ETH_PTP_SnapshotIPV6Frames) || \
                           ((SNAPSHOT) == ETH_PTP_SnapshotPTPOverEthernetFrames) || \
                           ((SNAPSHOT) == ETH_PTP_SnapshotAllReceivedFrames))

/**
  * @}
  */


/**
  * @}
  */

/** @defgroup ETH_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup ETH_Exported_Functions
  * @{
  */
void ETH_DeInit(void);
uint32_t ETH_Init(ETH_InitTypeDef* ETH_InitStruct);
void ETH_StructInit(ETH_InitTypeDef* ETH_InitStruct);
void ETH_SoftwareReset(void);
FlagStatus ETH_GetSoftwareResetStatus(void);
void  ETH_Start(void);
uint32_t ETH_HandleTxPkt(uint8_t *ppkt, uint16_t FrameLength);
uint32_t ETH_HandleRxPkt(uint8_t *ppkt);
uint32_t ETH_GetRxPktSize(void);
void ETH_DropRxPkt(void);

#ifdef USE_ENHANCED_DMA_DESCRIPTORS
 void ETH_EnhancedDescriptorCmd(FunctionalState NewState);
#endif /* USE_ENHANCED_DMA_DESCRIPTORS */

/**
  * @brief  PHY
  */
uint16_t ETH_ReadPHYRegister(uint16_t PHYAddress, uint16_t PHYReg);
uint32_t ETH_WritePHYRegister(uint16_t PHYAddress, uint16_t PHYReg, uint16_t PHYValue);
uint32_t ETH_PHYLoopBackCmd(uint16_t PHYAddress, FunctionalState NewState);

/**
  * @brief  MAC
  */
void ETH_MACTransmissionCmd(FunctionalState NewState);
void ETH_MACReceptionCmd(FunctionalState NewState);
FlagStatus ETH_GetFlowControlBusyStatus(void);
void ETH_InitiatePauseControlFrame(void);
void ETH_BackPressureActivationCmd(FunctionalState NewState);
FlagStatus ETH_GetMACFlagStatus(uint32_t ETH_MAC_FLAG);
ITStatus ETH_GetMACITStatus(uint32_t ETH_MAC_IT);
void ETH_MACITConfig(uint32_t ETH_MAC_IT, FunctionalState NewState);
void ETH_MACAddressConfig(uint32_t MacAddr, uint8_t *Addr);
void ETH_GetMACAddress(uint32_t MacAddr, uint8_t *Addr);
void ETH_MACAddressPerfectFilterCmd(uint32_t MacAddr, FunctionalState NewState);
void ETH_MACAddressFilterConfig(uint32_t MacAddr, uint32_t Filter);
void ETH_MACAddressMaskBytesFilterConfig(uint32_t MacAddr, uint32_t MaskByte);

/**
  * @brief  DMA Tx/Rx descriptors
  */
void ETH_DMATxDescChainInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t *TxBuff, uint32_t TxBuffCount);
void ETH_DMATxDescRingInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t *TxBuff1, uint8_t *TxBuff2, uint32_t TxBuffCount);
FlagStatus ETH_GetDMATxDescFlagStatus(ETH_DMADESCTypeDef *DMATxDesc, uint32_t ETH_DMATxDescFlag);
uint32_t ETH_GetDMATxDescCollisionCount(ETH_DMADESCTypeDef *DMATxDesc);
void ETH_SetDMATxDescOwnBit(ETH_DMADESCTypeDef *DMATxDesc);
void ETH_DMATxDescTransmitITConfig(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState);
void ETH_DMATxDescFrameSegmentConfig(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_FrameSegment);
void ETH_DMATxDescChecksumInsertionConfig(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_Checksum);
void ETH_DMATxDescCRCCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState);
void ETH_DMATxDescEndOfRingCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState);
void ETH_DMATxDescSecondAddressChainedCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState);
void ETH_DMATxDescShortFramePaddingCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState);
void ETH_DMATxDescTimeStampCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState);
void ETH_DMATxDescBufferSizeConfig(ETH_DMADESCTypeDef *DMATxDesc, uint32_t BufferSize1, uint32_t BufferSize2);
void ETH_DMARxDescChainInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *RxBuff, uint32_t RxBuffCount);
void ETH_DMARxDescRingInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *RxBuff1, uint8_t *RxBuff2, uint32_t RxBuffCount);
FlagStatus ETH_GetDMARxDescFlagStatus(ETH_DMADESCTypeDef *DMARxDesc, uint32_t ETH_DMARxDescFlag);
#ifdef USE_ENHANCED_DMA_DESCRIPTORS
 FlagStatus ETH_GetDMAPTPRxDescExtendedFlagStatus(ETH_DMADESCTypeDef *DMAPTPRxDesc, uint32_t ETH_DMAPTPRxDescExtendedFlag);
#endif /* USE_ENHANCED_DMA_DESCRIPTORS */
void ETH_SetDMARxDescOwnBit(ETH_DMADESCTypeDef *DMARxDesc);
uint32_t ETH_GetDMARxDescFrameLength(ETH_DMADESCTypeDef *DMARxDesc);
void ETH_DMARxDescReceiveITConfig(ETH_DMADESCTypeDef *DMARxDesc, FunctionalState NewState);
void ETH_DMARxDescEndOfRingCmd(ETH_DMADESCTypeDef *DMARxDesc, FunctionalState NewState);
void ETH_DMARxDescSecondAddressChainedCmd(ETH_DMADESCTypeDef *DMARxDesc, FunctionalState NewState);
uint32_t ETH_GetDMARxDescBufferSize(ETH_DMADESCTypeDef *DMARxDesc, uint32_t DMARxDesc_Buffer);

/**
  * @brief  DMA
  */
FlagStatus ETH_GetDMAFlagStatus(uint32_t ETH_DMA_FLAG);
void ETH_DMAClearFlag(uint32_t ETH_DMA_FLAG);
ITStatus ETH_GetDMAITStatus(uint32_t ETH_DMA_IT);
void ETH_DMAClearITPendingBit(uint32_t ETH_DMA_IT);
uint32_t ETH_GetTransmitProcessState(void);
uint32_t ETH_GetReceiveProcessState(void);
void ETH_FlushTransmitFIFO(void);
FlagStatus ETH_GetFlushTransmitFIFOStatus(void);
void ETH_DMATransmissionCmd(FunctionalState NewState);
void ETH_DMAReceptionCmd(FunctionalState NewState);
void ETH_DMAITConfig(uint32_t ETH_DMA_IT, FunctionalState NewState);
FlagStatus ETH_GetDMAOverflowStatus(uint32_t ETH_DMA_Overflow);
uint32_t ETH_GetRxOverflowMissedFrameCounter(void);
uint32_t ETH_GetBufferUnavailableMissedFrameCounter(void);
uint32_t ETH_GetCurrentTxDescStartAddress(void);
uint32_t ETH_GetCurrentRxDescStartAddress(void);
uint32_t ETH_GetCurrentTxBufferAddress(void);
uint32_t ETH_GetCurrentRxBufferAddress(void);
void ETH_ResumeDMATransmission(void);
void ETH_ResumeDMAReception(void);
void ETH_SetReceiveWatchdogTimer(uint8_t Value);


/**
  * @brief  PMT
  */
void ETH_ResetWakeUpFrameFilterRegisterPointer(void);
void ETH_SetWakeUpFrameFilterRegister(uint32_t *Buffer);
void ETH_GlobalUnicastWakeUpCmd(FunctionalState NewState);
FlagStatus ETH_GetPMTFlagStatus(uint32_t ETH_PMT_FLAG);
void ETH_WakeUpFrameDetectionCmd(FunctionalState NewState);
void ETH_MagicPacketDetectionCmd(FunctionalState NewState);
void ETH_PowerDownCmd(FunctionalState NewState);

/**
  * @brief  MMC
  */
void ETH_MMCCounterFullPreset(void);
void ETH_MMCCounterHalfPreset(void);
void ETH_MMCCounterFreezeCmd(FunctionalState NewState);
void ETH_MMCResetOnReadCmd(FunctionalState NewState);
void ETH_MMCCounterRolloverCmd(FunctionalState NewState);
void ETH_MMCCountersReset(void);
void ETH_MMCITConfig(uint32_t ETH_MMC_IT, FunctionalState NewState);
ITStatus ETH_GetMMCITStatus(uint32_t ETH_MMC_IT);
uint32_t ETH_GetMMCRegister(uint32_t ETH_MMCReg);

/**
  * @brief  PTP
  */
void ETH_PTPNodeClockTypeConfig(uint32_t ClockType);
void ETH_PTPSnapshotCmd(uint32_t SnapshotMethod, FunctionalState NewState);
void ETH_PTPPacketSnoopingV2FormatCmd(FunctionalState NewState);
void ETH_PTPSubSecondRolloverCmd(FunctionalState NewState);
uint32_t ETH_HandlePTPTxPkt(uint8_t *ppkt, uint16_t FrameLength, uint32_t *PTPTxTab);
uint32_t ETH_HandlePTPRxPkt(uint8_t *ppkt, uint32_t *PTPRxTab);
#ifdef USE_ENHANCED_DMA_DESCRIPTORS
 void ETH_DMAPTPTxDescChainInit(ETH_DMADESCTypeDef *DMAPTPTxDescTab, uint8_t *TxBuff, uint32_t TxBuffCount);
 void ETH_DMAPTPRxDescChainInit(ETH_DMADESCTypeDef *DMAPTPRxDescTab, uint8_t *RxBuff, uint32_t RxBuffCount);
#endif /* USE_ENHANCED_DMA_DESCRIPTORS */
void ETH_EnablePTPTimeStampAddend(void);
void ETH_EnablePTPTimeStampInterruptTrigger(void);
void ETH_EnablePTPTimeStampUpdate(void);
void ETH_InitializePTPTimeStamp(void);
void ETH_PTPUpdateMethodConfig(uint32_t UpdateMethod);
void ETH_PTPTimeStampCmd(FunctionalState NewState);
FlagStatus ETH_GetPTPFlagStatus(uint32_t ETH_PTP_FLAG);
void ETH_SetPTPSubSecondIncrement(uint32_t SubSecondValue);
void ETH_SetPTPTimeStampUpdate(uint32_t Sign, uint32_t SecondValue, uint32_t SubSecondValue);
void ETH_SetPTPTimeStampAddend(uint32_t Value);
void ETH_SetPTPTargetTime(uint32_t HighValue, uint32_t LowValue);
uint32_t ETH_GetPTPRegister(uint32_t ETH_PTPReg);

/* STM32 ETH HW initialization */
void rt_hw_stm32_eth_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F2XX_ETH_H */
/**
  * @}
  */


/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
