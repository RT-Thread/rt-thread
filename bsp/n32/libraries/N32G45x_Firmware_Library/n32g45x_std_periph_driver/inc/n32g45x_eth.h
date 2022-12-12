/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @brief Ethernet functions.
 * @file n32g45x_eth.h
 * @author Nations
 * @version v1.0.0
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __N32G45X_ETH_H__
#define __N32G45X_ETH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup ETH
 * @{
 */

/** @addtogroup ETH_Exported_Types
 * @{
 */

/**
 * @brief  ETH MAC Init structure definition
 * @note   The user should not configure all the ETH_InitType structure's fields.
 *   By calling the ETH_InitStruct function the structures fields are set to their default values.
 *   Only the parameters that will be set to a non-default value should be configured.
 */
typedef struct
{
    uint32_t AutoNegotiation; /*!< Selects or not the AutoNegotiation mode for the external PHY
                                     The AutoNegotiation allows an automatic setting of the Speed (10/100Mbps)
                                     and the mode (half/full-duplex).
                                     This parameter can be a value of @ref AutoNegotiation */

    uint32_t Watchdog; /*!< Selects or not the Watchdog timer
                              When enabled, the MAC allows no more then 2048 bytes to be received.
                              When disabled, the MAC can receive up to 16384 bytes.
                              This parameter can be a value of @ref ETH_watchdog */

    uint32_t Jabber; /*!< Selects or not Jabber timer
                            When enabled, the MAC allows no more then 2048 bytes to be sent.
                            When disabled, the MAC can send up to 16384 bytes.
                            This parameter can be a value of @ref Jabber */

    uint32_t InterFrameGap; /*!< Selects the minimum IFG between frames during transmission
                                   This parameter can be a value of @ref ETH_Inter_Frame_Gap */

    uint32_t CarrierSense; /*!< Selects or not the Carrier Sense
                                  This parameter can be a value of @ref ETH_Carrier_Sense */

    uint32_t SpeedMode; /*!< Sets the Ethernet speed: 10/100 Mbps
                           This parameter can be a value of @ref SpeedMode */

    uint32_t RxOwn; /*!< Selects or not the ReceiveOwn
                                ReceiveOwn allows the reception of frames when the TX_EN signal is asserted
                                in Half-Duplex mode
                                This parameter can be a value of @ref ETH_Receive_Own */

    uint32_t LoopbackMode; /*!< Selects or not the internal MAC MII Loopback mode
                                  This parameter can be a value of @ref ETH_Loop_Back_Mode */

    uint32_t DuplexMode; /*!< Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode
                          This parameter can be a value of @ref ETH_Duplex_Mode */

    uint32_t ChecksumOffload; /*!< Selects or not the IPv4 checksum checking for received frame payloads' TCP/UDP/ICMP
                                 headers. This parameter can be a value of @ref ETH_Checksum_Offload */

    uint32_t RetryTransmission; /*!< Selects or not the MAC attempt retries transmission, based on the settings of BL,
                                       when a colision occurs (Half-Duplex mode)
                                       This parameter can be a value of @ref ETH_Retry_Transmission */

    uint32_t AutomaticPadCRCStrip; /*!< Selects or not the Automatic MAC Pad/CRC Stripping
                                          This parameter can be a value of @ref ETH_Automatic_Pad_CRC_Strip */

    uint32_t BackoffLimit; /*!< Selects the BackOff limit value
                                  This parameter can be a value of @ref ETH_Back_Off_Limit
                                  This parameer only valid in ETH_DUPLEX_MODE_HALF mode*/

    uint32_t DeferralCheck; /*!< Selects or not the deferral check function (Half-Duplex mode)
                                   This parameter can be a value of @ref ETH_Deferral_Check */

    uint32_t RxAll; /*!< Selects or not all frames reception by the MAC (No fitering)
                                This parameter can be a value of @ref ETH_Receive_All */

    uint32_t SrcAddrFilter; /*!< Selects the Source Address Filter mode
                                      This parameter can be a value of @ref ETH_Source_Addr_Filter */

    uint32_t PassCtrlFrames; /*!< Sets the forwarding mode of the control frames (including unicast and multicast Pause
                                frames) This parameter can be a value of @ref ETH_Pass_Control_Frames */

    uint32_t BroadcastFramesReception; /*!< Selects or not the reception of Broadcast Frames
                                              This parameter can be a value of @ref ETH_Broadcast_Frames_Reception */

    uint32_t DestAddrFilter; /*!< Sets the destination filter mode for both unicast and multicast frames
                                           This parameter can be a value of @ref ETH_Destination_Addr_Filter */

    uint32_t PromiscuousMode; /*!< Selects or not the Promiscuous Mode
                                     This parameter can be a value of @ref ETH_Promiscuous_Mode */

    uint32_t MulticastFramesFilter; /*!< Selects the Multicast Frames filter mode:
                                       None/HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                           This parameter can be a value of @ref ETH_Multicast_Frames_Filter */

    uint32_t UnicastFramesFilter; /*!< Selects the Unicast Frames filter mode:
                                     HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                         This parameter can be a value of @ref ETH_Unicast_Frames_Filter */

    uint32_t HashTableHigh; /*!< This field holds the higher 32 bits of Hash table.  */

    uint32_t HashTableLow; /*!< This field holds the lower 32 bits of Hash table.  */

    uint32_t PauseTime; /*!< This field holds the value to be used in the Pause Time field in the
                               transmit control frame */

    uint32_t ZeroQuantaPause; /*!< Selects or not the automatic generation of Zero-Quanta Pause Control frames
                                     This parameter can be a value of @ref ETH_Zero_Quanta_Pause */

    uint32_t PauseLowThreshold; /*!< This field configures the threshold of the Pause to be checked for
                                       automatic retransmission of Pause Frame
                                       This parameter can be a value of @ref ETH_Pause_Low_Threshold */

    uint32_t UnicastPauseFrameDetect; /*!< Selects or not the MAC detection of the Pause frames (with MAC Address0
                                             unicast address and unique multicast address)
                                             This parameter can be a value of @ref ETH_Unicast_Pause_Frame_Detect */

    uint32_t RxFlowCtrl; /*!< Enables or disables the MAC to decode the received Pause frame and
                                        disable its transmitter for a specified time (Pause Time)
                                        This parameter can be a value of @ref ETH_Receive_Flow_Control */

    uint32_t TxFlowCtrl; /*!< Enables or disables the MAC to transmit Pause frames (Full-Duplex mode)
                                         or the MAC back-pressure operation (Half-Duplex mode)
                                         This parameter can be a value of @ref ETH_Transmit_Flow_Control */

    uint32_t VLANTagComparison; /*!< Selects the 12-bit VLAN identifier or the complete 16-bit VLAN tag for
                                       comparison and filtering
                                       This parameter can be a value of @ref ETH_VLAN_Tag_Comparison */

    uint32_t VLANTagIdentifier; /*!< Holds the VLAN tag identifier for receive frames */

    uint32_t DropTCPIPChecksumErrorFrame; /*!< Selects or not the Dropping of TCP/IP Checksum Error Frames
                                                 This parameter can be a value of @ref
                                             ETH_Drop_TCP_IP_Checksum_Error_Frame */

    uint32_t RxStoreForward; /*!< Enables or disables the Receive store and forward mode
                                         This parameter can be a value of @ref ETH_Receive_Store_Forward */

    uint32_t FlushRxFrame; /*!< Enables or disables the flushing of received frames
                                        This parameter can be a value of @ref ETH_Flush_Received_Frame */

    uint32_t TxStoreForward; /*!< Enables or disables Transmit store and forward mode
                                          This parameter can be a value of @ref ETH_Transmit_Store_Forward */

    uint32_t TxThresholdCtrl; /*!< Selects or not the Transmit Threshold Control
                                              This parameter can be a value of @ref ETH_Transmit_Threshold_Control */

    uint32_t ForwardErrorFrames; /*!< Selects or not the forward to the DMA of erroneous frames
                                        This parameter can be a value of @ref ETH_Forward_Error_Frames */

    uint32_t ForwardUndersizedGoodFrames; /*!< Enables or disables the Rx DATFIFO to forward Undersized frames (frames
                                             with no Error and length less than 64 bytes) including pad-bytes and CRC)
                                                 This parameter can be a value of @ref
                                             ETH_Forward_Undersized_Good_Frames */

    uint32_t RxThresholdCtrl; /*!< Selects the threshold level of the Receive DATFIFO
                                             This parameter can be a value of @ref ETH_Receive_Threshold_Control */

    uint32_t SecondFrameOperate; /*!< Selects or not the Operate on second frame mode, which allows the DMA to process a
                                    second frame of Transmit data even before obtaining the status for the first frame.
                                        This parameter can be a value of @ref ETH_Second_Frame_Operate */

    uint32_t AddrAlignedBeats; /*!< Enables or disables the Address Aligned Beats
                                         This parameter can be a value of @ref ETH_Address_Aligned_Beats */

    uint32_t FixedBurst; /*!< Enables or disables the AHB Master interface fixed burst transfers
                                This parameter can be a value of @ref ETH_Fixed_Burst */

    uint32_t RxDMABurstLen; /*!< Indicates the maximum number of beats to be transferred in one Rx DMA transaction
                                      This parameter can be a value of @ref ETH_Rx_DMA_Burst_Length */

    uint32_t TxDMABurstLen; /*!< Indicates sthe maximum number of beats to be transferred in one Tx DMA transaction
                                      This parameter can be a value of @ref ETH_Tx_DMA_Burst_Length */

    uint32_t DescSkipLen; /*!< Specifies the number of word to skip between two unchained descriptors (Ring mode) */

    uint32_t DMAArbitration; /*!< Selects the DMA Tx/Rx arbitration
                                    This parameter can be a value of @ref ETH_DMA_Arbitration */
} ETH_InitType;

/**
 * @brief  ETH DMA Desciptors data structure definition
 */
typedef struct
{
    uint32_t Status;             /*!< Status */
    uint32_t CtrlOrBufSize;      /*!< Control and Buffer1, Buffer2 lengths */
    uint32_t Buf1Addr;           /*!< Buffer1 address pointer */
    uint32_t Buf2OrNextDescAddr; /*!< Buffer2 or next descriptor address pointer */
} ETH_DMADescType;

/**
 * @}
 */

/** @addtogroup ETH_Exported_Constants
 * @{
 */

/**
 * @addtogroup ETH_PHY_Registers
 * @{
 */
#define PHY_BCR 0 /*!< Tranceiver Basic Control Register */
#define PHY_BSR 1 /*!< Tranceiver Basic Status Register */

#define PHY_RESET            ((u16)0x8000) /*!< PHY Reset */
#define PHY_LOOPBACK         ((u16)0x4000) /*!< Select loop-back mode */
#define PHY_FULLDUPLEX_100M  ((u16)0x2100) /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M  ((u16)0x2000) /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M   ((u16)0x0100) /*!< Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M   ((u16)0x0000) /*!< Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGO         ((u16)0x1000) /*!< Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGO ((u16)0x0200) /*!< Restart auto-negotiation function */
#define PHY_POWERDOWN        ((u16)0x0800) /*!< Select the power down mode */
#define PHY_ISOLATE          ((u16)0x0400) /*!< Isolate PHY from MII */

#define PHY_AUTONEGO_COMPLETE ((u16)0x0020) /*!< Auto-Negotioation process completed */
#define PHY_LINKED_STATUS     ((u16)0x0004) /*!< Valid link established */
#define PHY_JABBER_DETECTION  ((u16)0x0002) /*!< Jabber condition detected */

#define PHY_READ_TO  ((uint32_t)0x0004FFFF)
#define PHY_WRITE_TO ((uint32_t)0x0004FFFF)

#define IS_ETH_PHY_ADDRESS(ADDRESS) ((ADDRESS) < 0x20)
#define IS_ETH_PHY_REG(REG)         ((REG) < 0x20)
/**
 * @}
 */

/** @addtogroup ENET_Buffers_setting
 * @{
 */
#define ETH_MAX_PACKET_SIZE     1520 /*!< ETH_HEADER + ETH_EXTRA + ETH_MAX_PAYLOAD + ETH_CRC */
#define ETH_HEADER              14   /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC                 4    /*!< Ethernet CRC */
#define ETH_EXTRA               2    /*!< Extra bytes in some cases */
#define ETH_VLAN_TAG            4    /*!< optional 802.1q VLAN Tag */
#define ETH_MIN_PAYLOAD         46   /*!< Minimum Ethernet payload size */
#define ETH_MAX_PAYLOAD         1500 /*!< Maximum Ethernet payload size */
#define ETH_JUMBO_FRAME_PAYLOAD 9000 /*!< Jumbo frame payload size */

/*
   DMA Tx Desciptor
  -----------------------------------------------------------------------------------------------
  TDES0 |       OWN(31)           |             Reserved[30:18]         |      Status[17:0]      |
  -----------------------------------------------------------------------------------------------
  TDES1 |   Ctrl[31:22]     |   Buffer2 ByteCount[21:11]    |   Buffer1 ByteCount[10:0]          |
  -----------------------------------------------------------------------------------------------
  TDES2 |                         Buffer1 Address [31:0]                                         |
  -----------------------------------------------------------------------------------------------
  TDES3 |                   Buffer2 Address [31:0] / Next Desciptor Address [31:0]               |
  -----------------------------------------------------------------------------------------------
*/

/*
 * Bit definition of TDES0 register: DMA Tx descriptor status register
 */
#define ETH_DMA_TX_DESC_OWN  ((uint32_t)0x80000000) /*!< OWN bit: descriptor is owned by DMA engine */
#define ETH_DMA_TX_DESC_TTSS ((uint32_t)0x00020000) /*!< Tx Time Stamp Status */
#define ETH_DMA_TX_DESC_IHE  ((uint32_t)0x00010000) /*!< IP Header Error */
#define ETH_DMA_TX_DESC_ES                                                                                             \
    ((uint32_t)0x00008000) /*!< Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF ||   \
                              JT */
#define ETH_DMA_TX_DESC_JT  ((uint32_t)0x00004000) /*!< Jabber Timeout */
#define ETH_DMA_TX_DESC_FF  ((uint32_t)0x00002000) /*!< Frame Flushed: DMA/MTL flushed the frame due to SW flush */
#define ETH_DMA_TX_DESC_PCE ((uint32_t)0x00001000) /*!< Payload Checksum Error */
#define ETH_DMA_TX_DESC_LOC ((uint32_t)0x00000800) /*!< Loss of Carrier: carrier lost during tramsmission */
#define ETH_DMA_TX_DESC_NC  ((uint32_t)0x00000400) /*!< No Carrier: no carrier signal from the tranceiver */
#define ETH_DMA_TX_DESC_LC  ((uint32_t)0x00000200) /*!< Late Collision: transmission aborted due to collision */
#define ETH_DMA_TX_DESC_EC  ((uint32_t)0x00000100) /*!< Excessive Collision: transmission aborted after 16 collisions  \
                                                    */
#define ETH_DMA_TX_DESC_VF ((uint32_t)0x00000080)  /*!< VLAN Frame */
#define ETH_DMA_TX_DESC_CC ((uint32_t)0x00000078)  /*!< Collision Count */
#define ETH_DMA_TX_DESC_ED ((uint32_t)0x00000004)  /*!< Excessive Deferral */
#define ETH_DMA_TX_DESC_UF ((uint32_t)0x00000002)  /*!< Underflow Error: late data arrival from the memory */
#define ETH_DMA_TX_DESC_DB ((uint32_t)0x00000001)  /*!< Deferred Bit */

/*
 * Bit definition of TDES1 register
 */
#define ETH_DMA_TX_DESC_IC ((uint32_t)0x80000000) /*!< Interrupt on Completion */
#define ETH_DMA_TX_DESC_LS ((uint32_t)0x40000000) /*!< Last Segment */
#define ETH_DMA_TX_DESC_FS ((uint32_t)0x20000000) /*!< First Segment */

#define ETH_DMA_TX_DESC_CIC             ((uint32_t)0x18000000) /*!< Checksum Insertion Control: 4 cases */
#define ETH_DMA_TX_DESC_CIC_BYPASS      ((uint32_t)0x00000000) /*!< Do Nothing: Checksum Engine is bypassed */
#define ETH_DMA_TX_DESC_CIC_IPV4_HEADER ((uint32_t)0x08000000) /*!< IPV4 header Checksum Insertion */
#define ETH_DMA_TX_DESC_CIC_TCPUDPICMP_SEGMENT                                                                         \
    ((uint32_t)0x10000000) /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define ETH_DMA_TX_DESC_CIC_TCPUDPICMP_FULL                                                                            \
    ((uint32_t)0x18000000) /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */

#define ETH_DMA_TX_DESC_DC   ((uint32_t)0x04000000) /*!< Disable CRC */
#define ETH_DMA_TX_DESC_TER  ((uint32_t)0x02000000) /*!< Transmit End of Ring */
#define ETH_DMA_TX_DESC_TCH  ((uint32_t)0x01000000) /*!< Second Address Chained */
#define ETH_DMA_TX_DESC_DP   ((uint32_t)0x00800000) /*!< Disable Padding */
#define ETH_DMA_TX_DESC_TTSE ((uint32_t)0x00400000) /*!< Transmit Time Stamp Enable */
#define ETH_DMA_TX_DESC_TBS2 ((uint32_t)0x003FF800) /*!< Transmit Buffer2 Size */
#define ETH_DMA_TX_DESC_TBS1 ((uint32_t)0x000007FF) /*!< Transmit Buffer1 Size */

/*
 * Bit definition of TDES2 register
 */
#define ETH_DMA_TX_DESC_B1ADDR ((uint32_t)0xFFFFFFFF) /*!< Buffer1 Address Pointer */

/*
 * Bit definition of TDES3 register
 */
#define ETH_DMA_TX_DESC_B2ADDR ((uint32_t)0xFFFFFFFF) /*!< Buffer2 Address Pointer */

/**
 * @}
 */

/** @addtogroup DMA_Rx_descriptor
 * @{
 */

/*
  DMA Rx Desciptor
  --------------------------------------------------------------------------------------------------------------------
  RDES0 | OWN(31) |                                             Status [30:0]                                          |
  ---------------------------------------------------------------------------------------------------------------------
  RDES1 | CTRL(31) | Reserved[30:26] | CTRL[25:24] | Reserved[23:22] | Buffer2 ByteCnt[21:11] | Buffer1 ByteCnt[10:0]  |
  ---------------------------------------------------------------------------------------------------------------------
  RDES2 |                                       Buffer1 Address [31:0]                                                 |
  ---------------------------------------------------------------------------------------------------------------------
  RDES3 |                          Buffer2 Address [31:0] / Next Desciptor Address [31:0]                              |
  ---------------------------------------------------------------------------------------------------------------------
*/

/*
 * Bit definition of RDES0 register: DMA Rx descriptor status register
 */
#define ETH_DMA_RX_DESC_OWN ((uint32_t)0x80000000) /*!< OWN bit: descriptor is owned by DMA engine  */
#define ETH_DMA_RX_DESC_AFM ((uint32_t)0x40000000) /*!< DA Filter Fail for the rx frame  */
#define ETH_DMA_RX_DESC_FL  ((uint32_t)0x3FFF0000) /*!< Receive descriptor frame length  */
#define ETH_DMA_RX_DESC_ES                                                                                             \
    ((uint32_t)0x00008000) /*!< Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE */
#define ETH_DMA_RX_DESC_DE      ((uint32_t)0x00004000) /*!< Desciptor error: no more descriptors for receive frame  */
#define ETH_DMA_RX_DESC_SAF     ((uint32_t)0x00002000) /*!< SA Filter Fail for the received frame */
#define ETH_DMA_RX_DESC_LE      ((uint32_t)0x00001000) /*!< Frame size not matching with length field */
#define ETH_DMA_RX_DESC_OE      ((uint32_t)0x00000800) /*!< Overflow Error: Frame was damaged due to buffer overflow */
#define ETH_DMA_RX_DESC_VLAN    ((uint32_t)0x00000400) /*!< VLAN Tag: received frame is a VLAN frame */
#define ETH_DMA_RX_DESC_FS      ((uint32_t)0x00000200) /*!< First descriptor of the frame  */
#define ETH_DMA_RX_DESC_LS      ((uint32_t)0x00000100) /*!< Last descriptor of the frame  */
#define ETH_DMA_RX_DESC_IPV4HCE ((uint32_t)0x00000080) /*!< IPC Checksum Error: Rx Ipv4 header checksum error   */
#define ETH_DMA_RX_DESC_LC      ((uint32_t)0x00000040) /*!< Late collision occurred during reception   */
#define ETH_DMA_RX_DESC_FT      ((uint32_t)0x00000020) /*!< Frame type - Ethernet, otherwise 802.3    */
#define ETH_DMA_RX_DESC_RWT                                                                                            \
    ((uint32_t)0x00000010) /*!< Receive Watchdog Timeout: watchdog timer expired during reception    */
#define ETH_DMA_RX_DESC_RE  ((uint32_t)0x00000008) /*!< Receive error: error reported by MII interface  */
#define ETH_DMA_RX_DESC_DBE ((uint32_t)0x00000004) /*!< Dribble bit error: frame contains non int multiple of 8 bits   \
                                                    */
#define ETH_DMA_RX_DESC_CE ((uint32_t)0x00000002)  /*!< CRC error */
#define ETH_DMA_RX_DESC_RMAPCE                                                                                         \
    ((uint32_t)0x00000001) /*!< Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum     \
                              Error */

/*
 * Bit definition of RDES1 register
 */
#define ETH_DMA_RX_DESC_DIC  ((uint32_t)0x80000000) /*!< Disable Interrupt on Completion */
#define ETH_DMA_RX_DESC_RBS2 ((uint32_t)0x003FF800) /*!< Receive Buffer2 Size */
#define ETH_DMA_RX_DESC_RER  ((uint32_t)0x02000000) /*!< Receive End of Ring */
#define ETH_DMA_RX_DESC_RCH  ((uint32_t)0x01000000) /*!< Second Address Chained */
#define ETH_DMA_RX_DESC_RBS1 ((uint32_t)0x000007FF) /*!< Receive Buffer1 Size */

/*
 * Bit definition of RDES2 register
 */
#define ETH_DMA_RX_DESC_B1ADDR ((uint32_t)0xFFFFFFFF) /*!< Buffer1 Address Pointer */

/*
 * Bit definition of RDES3 register
 */
#define ETH_DMA_RX_DESC_B2ADDR ((uint32_t)0xFFFFFFFF) /*!< Buffer2 Address Pointer */

/**
 * @}
 */

/** @addtogroup AutoNegotiation
 * @{
 */
#define ETH_AUTONEG_ENABLE      ((uint32_t)0x00000001)
#define ETH_AUTONEG_DISABLE     ((uint32_t)0x00000000)
#define IS_ETH_AUTONEG(CMDCTRL) (((CMDCTRL) == ETH_AUTONEG_ENABLE) || ((CMDCTRL) == ETH_AUTONEG_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_watchdog
 * @{
 */
#define ETH_WATCHDOG_ENABLE      ((uint32_t)0x00000000)
#define ETH_WATCHDOG_DISABLE     ((uint32_t)0x00800000)
#define IS_ETH_WATCHDOG(CMDCTRL) (((CMDCTRL) == ETH_WATCHDOG_ENABLE) || ((CMDCTRL) == ETH_WATCHDOG_DISABLE))

/**
 * @}
 */

/** @addtogroup Jabber
 * @{
 */
#define ETH_JABBER_ENABLE      ((uint32_t)0x00000000)
#define ETH_JABBER_DISABLE     ((uint32_t)0x00400000)
#define IS_ETH_JABBER(CMDCTRL) (((CMDCTRL) == ETH_JABBER_ENABLE) || ((CMDCTRL) == ETH_JABBER_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Inter_Frame_Gap
 * @{
 */
#define ETH_INTER_FRAME_GAP_96BIT ((uint32_t)0x00000000) /*!< minimum IFG between frames during transmission is 96Bit  \
                                                          */
#define ETH_INTER_FRAME_GAP_88BIT ((uint32_t)0x00020000) /*!< minimum IFG between frames during transmission is 88Bit  \
                                                          */
#define ETH_INTER_FRAME_GAP_80BIT ((uint32_t)0x00040000) /*!< minimum IFG between frames during transmission is 80Bit  \
                                                          */
#define ETH_INTER_FRAME_GAP_72BIT ((uint32_t)0x00060000) /*!< minimum IFG between frames during transmission is 72Bit  \
                                                          */
#define ETH_INTER_FRAME_GAP_64BIT ((uint32_t)0x00080000) /*!< minimum IFG between frames during transmission is 64Bit  \
                                                          */
#define ETH_INTER_FRAME_GAP_56BIT ((uint32_t)0x000A0000) /*!< minimum IFG between frames during transmission is 56Bit  \
                                                          */
#define ETH_INTER_FRAME_GAP_48BIT ((uint32_t)0x000C0000) /*!< minimum IFG between frames during transmission is 48Bit  \
                                                          */
#define ETH_INTER_FRAME_GAP_40BIT ((uint32_t)0x000E0000) /*!< minimum IFG between frames during transmission is 40Bit  \
                                                          */
#define IS_ETH_INTER_FRAME_GAP(GAP)                                                                                    \
    (((GAP) == ETH_INTER_FRAME_GAP_96BIT) || ((GAP) == ETH_INTER_FRAME_GAP_88BIT)                                      \
     || ((GAP) == ETH_INTER_FRAME_GAP_80BIT) || ((GAP) == ETH_INTER_FRAME_GAP_72BIT)                                   \
     || ((GAP) == ETH_INTER_FRAME_GAP_64BIT) || ((GAP) == ETH_INTER_FRAME_GAP_56BIT)                                   \
     || ((GAP) == ETH_INTER_FRAME_GAP_48BIT) || ((GAP) == ETH_INTER_FRAME_GAP_40BIT))

/**
 * @}
 */

/** @addtogroup ETH_Carrier_Sense
 * @{
 */
#define ETH_CARRIER_SENSE_ENABLE  ((uint32_t)0x00000000)
#define ETH_CARRIER_SENSE_DISABLE ((uint32_t)0x00010000)
#define IS_ETH_CARRIER_SENSE(CMDCTRL)                                                                                  \
    (((CMDCTRL) == ETH_CARRIER_SENSE_ENABLE) || ((CMDCTRL) == ETH_CARRIER_SENSE_DISABLE))

/**
 * @}
 */

/** @addtogroup SpeedMode
 * @{
 */
#define ETH_SPEED_MODE_10M       ((uint32_t)0x00000000)
#define ETH_SPEED_MODE_100M      ((uint32_t)0x00004000)
#define IS_ETH_SPEED_MODE(SPEED) (((SPEED) == ETH_SPEED_MODE_10M) || ((SPEED) == ETH_SPEED_MODE_100M))

/**
 * @}
 */

/** @addtogroup ETH_Receive_Own
 * @{
 */
#define ETH_RX_OWN_ENABLE      ((uint32_t)0x00000000)
#define ETH_RX_OWN_DISABLE     ((uint32_t)0x00002000)
#define IS_ETH_RX_OWN(CMDCTRL) (((CMDCTRL) == ETH_RX_OWN_ENABLE) || ((CMDCTRL) == ETH_RX_OWN_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Loop_Back_Mode
 * @{
 */
#define ETH_LOOPBACK_MODE_ENABLE  ((uint32_t)0x00001000)
#define ETH_LOOPBACK_MODE_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_LOOPBACK_MODE(CMDCTRL)                                                                                  \
    (((CMDCTRL) == ETH_LOOPBACK_MODE_ENABLE) || ((CMDCTRL) == ETH_LOOPBACK_MODE_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Duplex_Mode
 * @{
 */
#define ETH_DUPLEX_MODE_FULL     ((uint32_t)0x00000800)
#define ETH_DUPLEX_MODE_HALF     ((uint32_t)0x00000000)
#define IS_ETH_DUPLEX_MODE(MODE) (((MODE) == ETH_DUPLEX_MODE_FULL) || ((MODE) == ETH_DUPLEX_MODE_HALF))

/**
 * @}
 */

/** @addtogroup ETH_Checksum_Offload
 * @{
 */
#define ETH_CHECKSUM_OFFLOAD_ENABLE  ((uint32_t)0x00000400)
#define ETH_CHECKSUM_OFFLOAD_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_CHECKSUM_OFFLOAD(CMDCTRL)                                                                               \
    (((CMDCTRL) == ETH_CHECKSUM_OFFLOAD_ENABLE) || ((CMDCTRL) == ETH_CHECKSUM_OFFLOAD_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Retry_Transmission
 * @{
 */
#define ETH_RETRY_TRANSMISSION_ENABLE  ((uint32_t)0x00000000)
#define ETH_RETRY_TRANSMISSION_DISABLE ((uint32_t)0x00000200)
#define IS_ETH_RETRY_TRANSMISSION(CMDCTRL)                                                                             \
    (((CMDCTRL) == ETH_RETRY_TRANSMISSION_ENABLE) || ((CMDCTRL) == ETH_RETRY_TRANSMISSION_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Automatic_Pad_CRC_Strip
 * @{
 */
#define ETH_AUTO_PAD_CRC_STRIP_ENABLE  ((uint32_t)0x00000080)
#define ETH_AUTO_PAD_CRC_STRIP_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_AUTO_PAD_CRC_STRIP(CMDCTRL)                                                                             \
    (((CMDCTRL) == ETH_AUTO_PAD_CRC_STRIP_ENABLE) || ((CMDCTRL) == ETH_AUTO_PAD_CRC_STRIP_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Back_Off_Limit
 * @{
 */
#define ETH_BACKOFF_LIMIT_10 ((uint32_t)0x00000000)
#define ETH_BACKOFF_LIMIT_8  ((uint32_t)0x00000020)
#define ETH_BACKOFF_LIMIT_4  ((uint32_t)0x00000040)
#define ETH_BACKOFF_LIMIT_1  ((uint32_t)0x00000060)
#define IS_ETH_BACKOFF_LIMIT(LIMIT)                                                                                    \
    (((LIMIT) == ETH_BACKOFF_LIMIT_10) || ((LIMIT) == ETH_BACKOFF_LIMIT_8) || ((LIMIT) == ETH_BACKOFF_LIMIT_4)         \
     || ((LIMIT) == ETH_BACKOFF_LIMIT_1))

/**
 * @}
 */

/** @addtogroup ETH_Deferral_Check
 * @{
 */
#define ETH_DEFERRAL_CHECK_ENABLE  ((uint32_t)0x00000010)
#define ETH_DEFERRAL_CHECK_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_DEFERRAL_CHECK(CMDCTRL)                                                                                 \
    (((CMDCTRL) == ETH_DEFERRAL_CHECK_ENABLE) || ((CMDCTRL) == ETH_DEFERRAL_CHECK_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Receive_All
 * @{
 */
#define ETH_RX_ALL_ENABLE      ((uint32_t)0x80000000)
#define ETH_RX_ALL_DISABLE     ((uint32_t)0x00000000)
#define IS_ETH_RX_ALL(CMDCTRL) (((CMDCTRL) == ETH_RX_ALL_ENABLE) || ((CMDCTRL) == ETH_RX_ALL_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Source_Addr_Filter
 * @{
 */
#define ETH_SRC_ADDR_FILTER_NORMAL_ENABLE  ((uint32_t)0x00000200)
#define ETH_SRC_ADDR_FILTER_INVERSE_ENABLE ((uint32_t)0x00000300)
#define ETH_SRC_ADDR_FILTER_DISABLE        ((uint32_t)0x00000000)
#define IS_ETH_SRC_ADDR_FILTER(CMDCTRL)                                                                                \
    (((CMDCTRL) == ETH_SRC_ADDR_FILTER_NORMAL_ENABLE) || ((CMDCTRL) == ETH_SRC_ADDR_FILTER_INVERSE_ENABLE)             \
     || ((CMDCTRL) == ETH_SRC_ADDR_FILTER_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Pass_Control_Frames
 * @{
 */
#define ETH_PASS_CTRL_FRAMES_BLOCK_ALL                                                                                 \
    ((uint32_t)0x00000040) /*!< MAC filters all control frames from reaching the application */
#define ETH_PASS_CTRL_FRAMES_FORWARD_ALL                                                                               \
    ((uint32_t)0x00000080) /*!< MAC forwards all control frames to application even if they fail the Address Filter */
#define ETH_PASS_CTRL_FRAMES_FORWARD_PASSED_ADDR_FILTER                                                                \
    ((uint32_t)0x000000C0) /*!< MAC forwards control frames that pass the Address Filter. */
#define IS_ETH_PASS_CTRL_FRAMES(PASS)                                                                                  \
    (((PASS) == ETH_PASS_CTRL_FRAMES_BLOCK_ALL) || ((PASS) == ETH_PASS_CTRL_FRAMES_FORWARD_ALL)                        \
     || ((PASS) == ETH_PASS_CTRL_FRAMES_FORWARD_PASSED_ADDR_FILTER))

/**
 * @}
 */

/** @addtogroup ETH_Broadcast_Frames_Reception
 * @{
 */
#define ETH_BROADCAST_FRAMES_RECEPTION_ENABLE  ((uint32_t)0x00000000)
#define ETH_BROADCAST_FRAMES_RECEPTION_DISABLE ((uint32_t)0x00000020)
#define IS_ETH_BROADCAST_FRAMES_RECEPTION(CMDCTRL)                                                                     \
    (((CMDCTRL) == ETH_BROADCAST_FRAMES_RECEPTION_ENABLE) || ((CMDCTRL) == ETH_BROADCAST_FRAMES_RECEPTION_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Destination_Addr_Filter
 * @{
 */
#define ETH_DEST_ADDR_FILTER_NORMAL  ((uint32_t)0x00000000)
#define ETH_DEST_ADDR_FILTER_INVERSE ((uint32_t)0x00000008)
#define IS_ETH_DEST_ADDR_FILTER(FILTER)                                                                                \
    (((FILTER) == ETH_DEST_ADDR_FILTER_NORMAL) || ((FILTER) == ETH_DEST_ADDR_FILTER_INVERSE))

/**
 * @}
 */

/** @addtogroup ETH_Promiscuous_Mode
 * @{
 */
#define ETH_PROMISCUOUS_MODE_ENABLE  ((uint32_t)0x00000001)
#define ETH_PROMISCUOUS_MODE_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_PROMISCUOUS_MODE(CMDCTRL)                                                                               \
    (((CMDCTRL) == ETH_PROMISCUOUS_MODE_ENABLE) || ((CMDCTRL) == ETH_PROMISCUOUS_MODE_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Multicast_Frames_Filter
 * @{
 */
#define ETH_MULTICAST_FRAMES_FILTER_PERFECT_HASH_TABLE ((uint32_t)0x00000404)
#define ETH_MULTICAST_FRAMES_FILTER_HASH_TABLE         ((uint32_t)0x00000004)
#define ETH_MULTICAST_FRAMES_FILTER_PERFECT            ((uint32_t)0x00000000)
#define ETH_MULTICAST_FRAMES_FILTER_NONE               ((uint32_t)0x00000010)
#define IS_ETH_MULTICAST_FRAMES_FILTER(FILTER)                                                                         \
    (((FILTER) == ETH_MULTICAST_FRAMES_FILTER_PERFECT_HASH_TABLE)                                                      \
     || ((FILTER) == ETH_MULTICAST_FRAMES_FILTER_HASH_TABLE) || ((FILTER) == ETH_MULTICAST_FRAMES_FILTER_PERFECT)      \
     || ((FILTER) == ETH_MULTICAST_FRAMES_FILTER_NONE))

/**
 * @}
 */

/** @addtogroup ETH_Unicast_Frames_Filter
 * @{
 */
#define ETH_UNICAST_FRAMES_FILTER_PERFECTHASHTABLE ((uint32_t)0x00000402)
#define ETH_UNICAST_FRAMES_FILTER_HASHTABLE        ((uint32_t)0x00000002)
#define ETH_UNICAST_FRAMES_FILTER_PERFECT          ((uint32_t)0x00000000)
#define IS_ETH_UNICAST_FRAMES_FILTER(FILTER)                                                                           \
    (((FILTER) == ETH_UNICAST_FRAMES_FILTER_PERFECTHASHTABLE) || ((FILTER) == ETH_UNICAST_FRAMES_FILTER_HASHTABLE)     \
     || ((FILTER) == ETH_UNICAST_FRAMES_FILTER_PERFECT))

/**
 * @}
 */

/** @addtogroup ETH_Pause_Time
 * @{
 */
#define IS_ETH_PAUSE_TIME(TIME) ((TIME) <= 0xFFFF)

/**
 * @}
 */

/** @addtogroup ETH_Zero_Quanta_Pause
 * @{
 */
#define ETH_ZERO_QUANTA_PAUSE_ENABLE  ((uint32_t)0x00000000)
#define ETH_ZERO_QUANTA_PAUSE_DISABLE ((uint32_t)0x00000080)
#define IS_ETH_ZERO_QUANTA_PAUSE(CMDCTRL)                                                                              \
    (((CMDCTRL) == ETH_ZERO_QUANTA_PAUSE_ENABLE) || ((CMDCTRL) == ETH_ZERO_QUANTA_PAUSE_DISABLE))
/**
 * @}
 */

/** @addtogroup ETH_Pause_Low_Threshold
 * @{
 */
#define ETH_PAUSE_LOW_THRESHOLD_MINUS4   ((uint32_t)0x00000000) /*!< Pause time minus 4 slot times */
#define ETH_PAUSE_LOW_THRESHOLD_MINUS28  ((uint32_t)0x00000010) /*!< Pause time minus 28 slot times */
#define ETH_PAUSE_LOW_THRESHOLD_MINUS144 ((uint32_t)0x00000020) /*!< Pause time minus 144 slot times */
#define ETH_PAUSE_LOW_THRESHOLD_MINUS256 ((uint32_t)0x00000030) /*!< Pause time minus 256 slot times */
#define IS_ETH_PAUSE_LOW_THRESHOLD(THRESHOLD)                                                                          \
    (((THRESHOLD) == ETH_PAUSE_LOW_THRESHOLD_MINUS4) || ((THRESHOLD) == ETH_PAUSE_LOW_THRESHOLD_MINUS28)               \
     || ((THRESHOLD) == ETH_PAUSE_LOW_THRESHOLD_MINUS144) || ((THRESHOLD) == ETH_PAUSE_LOW_THRESHOLD_MINUS256))

/**
 * @}
 */

/** @addtogroup ETH_Unicast_Pause_Frame_Detect
 * @{
 */
#define ETH_UNICAST_PAUSE_FRAME_DETECT_ENABLE  ((uint32_t)0x00000008)
#define ETH_UNICAST_PAUSE_FRAME_DETECT_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_UNICAST_PAUSE_FRAME_DETECT(CMDCTRL)                                                                     \
    (((CMDCTRL) == ETH_UNICAST_PAUSE_FRAME_DETECT_ENABLE) || ((CMDCTRL) == ETH_UNICAST_PAUSE_FRAME_DETECT_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Receive_Flow_Control
 * @{
 */
#define ETH_RX_FLOW_CTRL_ENABLE      ((uint32_t)0x00000004)
#define ETH_RX_FLOW_CTRL_DISABLE     ((uint32_t)0x00000000)
#define IS_ETH_RX_FLOW_CTRL(CMDCTRL) (((CMDCTRL) == ETH_RX_FLOW_CTRL_ENABLE) || ((CMDCTRL) == ETH_RX_FLOW_CTRL_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Transmit_Flow_Control
 * @{
 */
#define ETH_TX_FLOW_CTRL_ENABLE      ((uint32_t)0x00000002)
#define ETH_TX_FLOW_CTRL_DISABLE     ((uint32_t)0x00000000)
#define IS_ETH_TX_FLOW_CTRL(CMDCTRL) (((CMDCTRL) == ETH_TX_FLOW_CTRL_ENABLE) || ((CMDCTRL) == ETH_TX_FLOW_CTRL_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_VLAN_Tag_Comparison
 * @{
 */
#define ETH_VLAN_TAG_COMPARISON_12BIT ((uint32_t)0x00010000)
#define ETH_VLAN_TAG_COMPARISON_16BIT ((uint32_t)0x00000000)
#define IS_ETH_VLAN_TAG_COMPARISON(COMPARISON)                                                                         \
    (((COMPARISON) == ETH_VLAN_TAG_COMPARISON_12BIT) || ((COMPARISON) == ETH_VLAN_TAG_COMPARISON_16BIT))
#define IS_ETH_VLAN_TAG_IDENTIFIER(IDENTIFIER) ((IDENTIFIER) <= 0xFFFF)

/**
 * @}
 */

/** @addtogroup ETH_MAC_Flags
 * @{
 */
#define ETH_MAC_FLAG_TST   ((uint32_t)0x00000200) /*!< Time stamp trigger flag (on MAC) */
#define ETH_MAC_FLAG_MMCTX ((uint32_t)0x00000040) /*!< MMC transmit flag  */
#define ETH_MAC_FLAG_MMCRX ((uint32_t)0x00000020) /*!< MMC receive flag */
#define ETH_MAC_FLAG_MMC   ((uint32_t)0x00000010) /*!< MMC flag (on MAC) */
#define ETH_MAC_FLAG_PMT   ((uint32_t)0x00000008) /*!< PMT flag (on MAC) */
#define IS_ETH_MAC_GET_FLAG(FLAG)                                                                                      \
    (((FLAG) == ETH_MAC_FLAG_TST) || ((FLAG) == ETH_MAC_FLAG_MMCTX) || ((FLAG) == ETH_MAC_FLAG_MMCRX)                  \
     || ((FLAG) == ETH_MAC_FLAG_MMC) || ((FLAG) == ETH_MAC_FLAG_PMT))
/**
 * @}
 */

/** @addtogroup ETH_MAC_Interrupts
 * @{
 */
#define ETH_MAC_INT_TST    ((uint32_t)0x00000200) /*!< Time stamp trigger interrupt (on MAC) */
#define ETH_MAC_INT_MMCTX  ((uint32_t)0x00000040) /*!< MMC transmit interrupt */
#define ETH_MAC_INT_MMCRX  ((uint32_t)0x00000020) /*!< MMC receive interrupt */
#define ETH_MAC_INT_MMC    ((uint32_t)0x00000010) /*!< MMC interrupt (on MAC) */
#define ETH_MAC_INT_PMT    ((uint32_t)0x00000008) /*!< PMT interrupt (on MAC) */
#define IS_ETH_MAC_INT(IT) ((((IT) & (uint32_t)0xFFFFFDF7) == 0x00) && ((IT) != 0x00))
#define IS_ETH_MAC_GET_INT(IT)                                                                                         \
    (((IT) == ETH_MAC_INT_TST) || ((IT) == ETH_MAC_INT_MMCTX) || ((IT) == ETH_MAC_INT_MMCRX)                           \
     || ((IT) == ETH_MAC_INT_MMC) || ((IT) == ETH_MAC_INT_PMT))
/**
 * @}
 */

/** @addtogroup ETH_MAC_addresses
 * @{
 */
#define ETH_MAC_ADDR0 ((uint32_t)0x00000000)
#define ETH_MAC_ADDR1 ((uint32_t)0x00000008)
#define ETH_MAC_ADDR2 ((uint32_t)0x00000010)
#define ETH_MAC_ADDR3 ((uint32_t)0x00000018)
#define IS_ETH_MAC_ADDR0123(ADDRESS)                                                                                   \
    (((ADDRESS) == ETH_MAC_ADDR0) || ((ADDRESS) == ETH_MAC_ADDR1) || ((ADDRESS) == ETH_MAC_ADDR2)                      \
     || ((ADDRESS) == ETH_MAC_ADDR3))
#define IS_ETH_MAC_ADDR123(ADDRESS)                                                                                    \
    (((ADDRESS) == ETH_MAC_ADDR1) || ((ADDRESS) == ETH_MAC_ADDR2) || ((ADDRESS) == ETH_MAC_ADDR3))
/**
 * @}
 */

/** @addtogroup ETH_MAC_addresses_filter_SA_DA_filed_of_received_frames
 * @{
 */
#define ETH_MAC_ADDR_FILTER_SA         ((uint32_t)0x00000000)
#define ETH_MAC_ADDR_FILTER_DA         ((uint32_t)0x00000008)
#define IS_ETH_MAC_ADDR_FILTER(FILTER) (((FILTER) == ETH_MAC_ADDR_FILTER_SA) || ((FILTER) == ETH_MAC_ADDR_FILTER_DA))
/**
 * @}
 */

/** @addtogroup ETH_MAC_addresses_filter_Mask_bytes
 * @{
 */
#define ETH_MAC_ADDR_MASK_BYTE6 ((uint32_t)0x20000000) /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MAC_ADDR_MASK_BYTE5 ((uint32_t)0x10000000) /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MAC_ADDR_MASK_BYTE4 ((uint32_t)0x08000000) /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MAC_ADDR_MASK_BYTE3 ((uint32_t)0x04000000) /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MAC_ADDR_MASK_BYTE2 ((uint32_t)0x02000000) /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MAC_ADDR_MASK_BYTE1 ((uint32_t)0x01000000) /*!< Mask MAC Address low reg bits [70] */
#define IS_ETH_MAC_ADDR_MASK(INTEN)                                                                                    \
    (((INTEN) == ETH_MAC_ADDR_MASK_BYTE6) || ((INTEN) == ETH_MAC_ADDR_MASK_BYTE5)                                      \
     || ((INTEN) == ETH_MAC_ADDR_MASK_BYTE4) || ((INTEN) == ETH_MAC_ADDR_MASK_BYTE3)                                   \
     || ((INTEN) == ETH_MAC_ADDR_MASK_BYTE2) || ((INTEN) == ETH_MAC_ADDR_MASK_BYTE1))

/**
 * @}
 */

/** @addtogroup ETH_DMA_Tx_descriptor_flags
 * @{
 */
#define IS_ETH_DMATXDESC_GET_FLAG(FLAG)                                                                                \
    (((FLAG) == ETH_DMA_TX_DESC_OWN) || ((FLAG) == ETH_DMA_TX_DESC_IC) || ((FLAG) == ETH_DMA_TX_DESC_LS)               \
     || ((FLAG) == ETH_DMA_TX_DESC_FS) || ((FLAG) == ETH_DMA_TX_DESC_DC) || ((FLAG) == ETH_DMA_TX_DESC_DP)             \
     || ((FLAG) == ETH_DMA_TX_DESC_TTSE) || ((FLAG) == ETH_DMA_TX_DESC_TER) || ((FLAG) == ETH_DMA_TX_DESC_TCH)         \
     || ((FLAG) == ETH_DMA_TX_DESC_TTSS) || ((FLAG) == ETH_DMA_TX_DESC_IHE) || ((FLAG) == ETH_DMA_TX_DESC_ES)          \
     || ((FLAG) == ETH_DMA_TX_DESC_JT) || ((FLAG) == ETH_DMA_TX_DESC_FF) || ((FLAG) == ETH_DMA_TX_DESC_PCE)            \
     || ((FLAG) == ETH_DMA_TX_DESC_LOC) || ((FLAG) == ETH_DMA_TX_DESC_NC) || ((FLAG) == ETH_DMA_TX_DESC_LC)            \
     || ((FLAG) == ETH_DMA_TX_DESC_EC) || ((FLAG) == ETH_DMA_TX_DESC_VF) || ((FLAG) == ETH_DMA_TX_DESC_CC)             \
     || ((FLAG) == ETH_DMA_TX_DESC_ED) || ((FLAG) == ETH_DMA_TX_DESC_UF) || ((FLAG) == ETH_DMA_TX_DESC_DB))

/**
 * @}
 */

/** @addtogroup ETH_DMA_Tx_descriptor_segment
 * @{
 */
#define ETH_DMA_TX_DESC_LAST_SEGMENT  ((uint32_t)0x40000000) /*!< Last Segment */
#define ETH_DMA_TX_DESC_FIRST_SEGMENT ((uint32_t)0x20000000) /*!< First Segment */
#define IS_ETH_DMA_TX_DESC_SEGMENT(SEGMENT)                                                                            \
    (((SEGMENT) == ETH_DMA_TX_DESC_LAST_SEGMENT) || ((SEGMENT) == ETH_DMA_TX_DESC_FIRST_SEGMENT))

/**
 * @}
 */

/** @addtogroup ETH_DMA_Tx_descriptor_Checksum_Insertion_Control
 * @{
 */
#define ETH_DMA_TX_DESC_CHECKSUM_BYPASS      ((uint32_t)0x00000000) /*!< Checksum engine bypass */
#define ETH_DMA_TX_DESC_CHECKSUM_IPV4_HEADER ((uint32_t)0x08000000) /*!< IPv4 header checksum insertion  */
#define ETH_DMA_TX_DESC_CHECKSUM_TCPUDPICMP_SEGMENT                                                                    \
    ((uint32_t)0x10000000) /*!< TCP/UDP/ICMP checksum insertion. Pseudo header checksum is assumed to be present */
#define ETH_DMA_TX_DESC_CHECKSUM_TCPUDPICMP_FULL                                                                       \
    ((uint32_t)0x18000000) /*!< TCP/UDP/ICMP checksum fully in hardware including pseudo header */
#define IS_ETH_DMA_TX_DESC_CHECKSUM(CHECKSUM)                                                                          \
    (((CHECKSUM) == ETH_DMA_TX_DESC_CHECKSUM_BYPASS) || ((CHECKSUM) == ETH_DMA_TX_DESC_CHECKSUM_IPV4_HEADER)           \
     || ((CHECKSUM) == ETH_DMA_TX_DESC_CHECKSUM_TCPUDPICMP_SEGMENT)                                                    \
     || ((CHECKSUM) == ETH_DMA_TX_DESC_CHECKSUM_TCPUDPICMP_FULL))

#define IS_ETH_DMA_TX_DESC_BUFFER_SIZE(SIZE) ((SIZE) <= 0x1FFF)

/**
 * @}
 */

/** @addtogroup ETH_DMA_Rx_descriptor_flags
 * @{
 */
#define IS_ETH_DMA_RX_DESC_GET_FLAG(FLAG)                                                                              \
    (((FLAG) == ETH_DMA_RX_DESC_OWN) || ((FLAG) == ETH_DMA_RX_DESC_AFM) || ((FLAG) == ETH_DMA_RX_DESC_ES)              \
     || ((FLAG) == ETH_DMA_RX_DESC_DE) || ((FLAG) == ETH_DMA_RX_DESC_SAF) || ((FLAG) == ETH_DMA_RX_DESC_LE)            \
     || ((FLAG) == ETH_DMA_RX_DESC_OE) || ((FLAG) == ETH_DMA_RX_DESC_VLAN) || ((FLAG) == ETH_DMA_RX_DESC_FS)           \
     || ((FLAG) == ETH_DMA_RX_DESC_LS) || ((FLAG) == ETH_DMA_RX_DESC_IPV4HCE) || ((FLAG) == ETH_DMA_RX_DESC_LC)        \
     || ((FLAG) == ETH_DMA_RX_DESC_FT) || ((FLAG) == ETH_DMA_RX_DESC_RWT) || ((FLAG) == ETH_DMA_RX_DESC_RE)            \
     || ((FLAG) == ETH_DMA_RX_DESC_DBE) || ((FLAG) == ETH_DMA_RX_DESC_CE) || ((FLAG) == ETH_DMA_RX_DESC_RMAPCE))

/**
 * @}
 */

/** @addtogroup ETH_DMA_Rx_descriptor_buffers_
 * @{
 */
#define ETH_DMA_RX_DESC_BUFFER1 ((uint32_t)0x00000000) /*!< DMA Rx Desc Buffer1 */
#define ETH_DMA_RX_DESC_BUFFER2 ((uint32_t)0x00000001) /*!< DMA Rx Desc Buffer2 */
#define IS_ETH_DMA_RXDESC_BUFFER(BUFFER)                                                                               \
    (((BUFFER) == ETH_DMA_RX_DESC_BUFFER1) || ((BUFFER) == ETH_DMA_RX_DESC_BUFFER2))

/**
 * @}
 */

/** @addtogroup ETH_Drop_TCP_IP_Checksum_Error_Frame
 * @{
 */
#define ETH_DROP_TCPIP_CHECKSUM_ERROR_FRAME_ENABLE  ((uint32_t)0x00000000)
#define ETH_DROP_TCPIP_CHECKSUM_ERROR_FRAME_DISABLE ((uint32_t)0x04000000)
#define IS_ETH_DROP_TCPIP_CHECKSUM_FRAME(CMDCTRL)                                                                      \
    (((CMDCTRL) == ETH_DROP_TCPIP_CHECKSUM_ERROR_FRAME_ENABLE)                                                         \
     || ((CMDCTRL) == ETH_DROP_TCPIP_CHECKSUM_ERROR_FRAME_DISABLE))
/**
 * @}
 */

/** @addtogroup ETH_Receive_Store_Forward
 * @{
 */
#define ETH_RX_STORE_FORWARD_ENABLE  ((uint32_t)0x02000000)
#define ETH_RX_STORE_FORWARD_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_RX_STORE_FORWARD(CMDCTRL)                                                                               \
    (((CMDCTRL) == ETH_RX_STORE_FORWARD_ENABLE) || ((CMDCTRL) == ETH_RX_STORE_FORWARD_DISABLE))
/**
 * @}
 */

/** @addtogroup ETH_Flush_Received_Frame
 * @{
 */
#define ETH_FLUSH_RX_FRAME_ENABLE  ((uint32_t)0x00000000)
#define ETH_FLUSH_RX_FRAME_DISABLE ((uint32_t)0x01000000)
#define IS_ETH_FLUSH_RX_FRAME(CMDCTRL)                                                                                 \
    (((CMDCTRL) == ETH_FLUSH_RX_FRAME_ENABLE) || ((CMDCTRL) == ETH_FLUSH_RX_FRAME_DISABLE))
/**
 * @}
 */

/** @addtogroup ETH_Transmit_Store_Forward
 * @{
 */
#define ETH_TX_STORE_FORWARD_ENABLE  ((uint32_t)0x00200000)
#define ETH_TX_STORE_FORWARD_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_TX_STORE_FORWARD(CMDCTRL)                                                                               \
    (((CMDCTRL) == ETH_TX_STORE_FORWARD_ENABLE) || ((CMDCTRL) == ETH_TX_STORE_FORWARD_DISABLE))
/**
 * @}
 */

/** @addtogroup ETH_Transmit_Threshold_Control
 * @{
 */
#define ETH_TX_THRESHOLD_CTRL_64BYTES                                                                                  \
    ((uint32_t)0x00000000) /*!< threshold level of the MTL Transmit DATFIFO is 64 Bytes */
#define ETH_TX_THRESHOLD_CTRL_128BYTES                                                                                 \
    ((uint32_t)0x00004000) /*!< threshold level of the MTL Transmit DATFIFO is 128 Bytes */
#define ETH_TX_THRESHOLD_CTRL_192BYTES                                                                                 \
    ((uint32_t)0x00008000) /*!< threshold level of the MTL Transmit DATFIFO is 192 Bytes */
#define ETH_TX_THRESHOLD_CTRL_256BYTES                                                                                 \
    ((uint32_t)0x0000C000) /*!< threshold level of the MTL Transmit DATFIFO is 256 Bytes */
#define ETH_TX_THRESHOLD_CTRL_40BYTES                                                                                  \
    ((uint32_t)0x00010000) /*!< threshold level of the MTL Transmit DATFIFO is 40 Bytes */
#define ETH_TX_THRESHOLD_CTRL_32BYTES                                                                                  \
    ((uint32_t)0x00014000) /*!< threshold level of the MTL Transmit DATFIFO is 32 Bytes */
#define ETH_TX_THRESHOLD_CTRL_24BYTES                                                                                  \
    ((uint32_t)0x00018000) /*!< threshold level of the MTL Transmit DATFIFO is 24 Bytes */
#define ETH_TX_THRESHOLD_CTRL_16BYTES                                                                                  \
    ((uint32_t)0x0001C000) /*!< threshold level of the MTL Transmit DATFIFO is 16 Bytes */
#define IS_ETH_TX_THRESHOLD_CTRL(THRESHOLD)                                                                            \
    (((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_64BYTES) || ((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_128BYTES)                 \
     || ((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_192BYTES) || ((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_256BYTES)             \
     || ((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_40BYTES) || ((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_32BYTES)               \
     || ((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_24BYTES) || ((THRESHOLD) == ETH_TX_THRESHOLD_CTRL_16BYTES))
/**
 * @}
 */

/** @addtogroup ETH_Forward_Error_Frames
 * @{
 */
#define ETH_FORWARD_ERROR_FRAMES_ENABLE  ((uint32_t)0x00000080)
#define ETH_FORWARD_ERROR_FRAMES_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_FORWARD_ERROR_FRAMES(CMDCTRL)                                                                           \
    (((CMDCTRL) == ETH_FORWARD_ERROR_FRAMES_ENABLE) || ((CMDCTRL) == ETH_FORWARD_ERROR_FRAMES_DISABLE))
/**
 * @}
 */

/** @addtogroup ETH_Forward_Undersized_Good_Frames
 * @{
 */
#define ETH_FORWARD_UNDERSIZED_GOOD_FRAMES_ENABLE  ((uint32_t)0x00000040)
#define ETH_FORWARD_UNDERSIZED_GOOD_FRAMES_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_FORWARD_UNDERSIZED_GOOD_FRAMES(CMDCTRL)                                                                 \
    (((CMDCTRL) == ETH_FORWARD_UNDERSIZED_GOOD_FRAMES_ENABLE)                                                          \
     || ((CMDCTRL) == ETH_FORWARD_UNDERSIZED_GOOD_FRAMES_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Receive_Threshold_Control
 * @{
 */
#define ETH_RX_THRESHOLD_CTRL_64BYTES                                                                                  \
    ((uint32_t)0x00000000) /*!< threshold level of the MTL Receive DATFIFO is 64 Bytes */
#define ETH_RX_THRESHOLD_CTRL_32BYTES                                                                                  \
    ((uint32_t)0x00000008) /*!< threshold level of the MTL Receive DATFIFO is 32 Bytes */
#define ETH_RX_THRESHOLD_CTRL_96BYTES                                                                                  \
    ((uint32_t)0x00000010) /*!< threshold level of the MTL Receive DATFIFO is 96 Bytes */
#define ETH_RX_THRESHOLD_CTRL_128BYTES                                                                                 \
    ((uint32_t)0x00000018) /*!< threshold level of the MTL Receive DATFIFO is 128 Bytes */
#define IS_ETH_RX_THRESHOLD_CTRL(THRESHOLD)                                                                            \
    (((THRESHOLD) == ETH_RX_THRESHOLD_CTRL_64BYTES) || ((THRESHOLD) == ETH_RX_THRESHOLD_CTRL_32BYTES)                  \
     || ((THRESHOLD) == ETH_RX_THRESHOLD_CTRL_96BYTES) || ((THRESHOLD) == ETH_RX_THRESHOLD_CTRL_128BYTES))
/**
 * @}
 */

/** @addtogroup ETH_Second_Frame_Operate
 * @{
 */
#define ETH_SECOND_FRAME_OPERATE_ENABLE  ((uint32_t)0x00000004)
#define ETH_SECOND_FRAME_OPERATE_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_SECOND_FRAME_OPERATE(CMDCTRL)                                                                           \
    (((CMDCTRL) == ETH_SECOND_FRAME_OPERATE_ENABLE) || ((CMDCTRL) == ETH_SECOND_FRAME_OPERATE_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Address_Aligned_Beats
 * @{
 */
#define ETH_ADDR_ALIGNED_BEATS_ENABLE  ((uint32_t)0x02000000)
#define ETH_ADDR_ALIGNED_BEATS_DISABLE ((uint32_t)0x00000000)
#define IS_ETH_ADDR_ALIGNED_BEATS(CMDCTRL)                                                                             \
    (((CMDCTRL) == ETH_ADDR_ALIGNED_BEATS_ENABLE) || ((CMDCTRL) == ETH_ADDR_ALIGNED_BEATS_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Fixed_Burst
 * @{
 */
#define ETH_FIXED_BURST_ENABLE      ((uint32_t)0x00010000)
#define ETH_FIXED_BURST_DISABLE     ((uint32_t)0x00000000)
#define IS_ETH_FIXED_BURST(CMDCTRL) (((CMDCTRL) == ETH_FIXED_BURST_ENABLE) || ((CMDCTRL) == ETH_FIXED_BURST_DISABLE))

/**
 * @}
 */

/** @addtogroup ETH_Rx_DMA_Burst_Length
 * @{
 */
#define ETH_RX_DMA_BURST_LEN_1BEAT                                                                                     \
    ((uint32_t)0x00020000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define ETH_RX_DMA_BURST_LEN_2BEAT                                                                                     \
    ((uint32_t)0x00040000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define ETH_RX_DMA_BURST_LEN_4BEAT                                                                                     \
    ((uint32_t)0x00080000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_RX_DMA_BURST_LEN_8BEAT                                                                                     \
    ((uint32_t)0x00100000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_RX_DMA_BURST_LEN_16BEAT                                                                                    \
    ((uint32_t)0x00200000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_RX_DMA_BURST_LEN_32BEAT                                                                                    \
    ((uint32_t)0x00400000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_RX_DMA_BURST_LEN_PBLX8_8BEAT                                                                               \
    ((uint32_t)0x01020000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_RX_DMA_BURST_LEN_PBLX8_16BEAT                                                                              \
    ((uint32_t)0x01040000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_RX_DMA_BURST_LEN_PBLX8_32BEAT                                                                              \
    ((uint32_t)0x01080000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_RX_DMA_BURST_LEN_PBLX8_64BEAT                                                                              \
    ((uint32_t)0x01100000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_RX_DMA_BURST_LEN_PBLX8_128BEAT                                                                             \
    ((uint32_t)0x01200000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define ETH_RX_DMA_BURST_LEN_PBLX8_256BEAT                                                                             \
    ((uint32_t)0x01400000) /*!< maximum number of beats to be transferred in one RxDMA transaction is 128 */
#define IS_ETH_RX_DMA_BURST_LEN(LENGTH)                                                                                \
    (((LENGTH) == ETH_RX_DMA_BURST_LEN_1BEAT) || ((LENGTH) == ETH_RX_DMA_BURST_LEN_2BEAT)                              \
     || ((LENGTH) == ETH_RX_DMA_BURST_LEN_4BEAT) || ((LENGTH) == ETH_RX_DMA_BURST_LEN_8BEAT)                           \
     || ((LENGTH) == ETH_RX_DMA_BURST_LEN_16BEAT) || ((LENGTH) == ETH_RX_DMA_BURST_LEN_32BEAT)                         \
     || ((LENGTH) == ETH_RX_DMA_BURST_LEN_PBLX8_8BEAT) || ((LENGTH) == ETH_RX_DMA_BURST_LEN_PBLX8_16BEAT)              \
     || ((LENGTH) == ETH_RX_DMA_BURST_LEN_PBLX8_32BEAT) || ((LENGTH) == ETH_RX_DMA_BURST_LEN_PBLX8_64BEAT)             \
     || ((LENGTH) == ETH_RX_DMA_BURST_LEN_PBLX8_128BEAT) || ((LENGTH) == ETH_RX_DMA_BURST_LEN_PBLX8_256BEAT))

/**
 * @}
 */

/** @addtogroup ETH_Tx_DMA_Burst_Length
 * @{
 */
#define ETH_TX_DMA_BURST_LEN_1BEAT                                                                                     \
    ((uint32_t)0x00000100) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define ETH_TX_DMA_BURST_LEN_2BEAT                                                                                     \
    ((uint32_t)0x00000200) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define ETH_TX_DMA_BURST_LEN_4BEAT                                                                                     \
    ((uint32_t)0x00000400) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_TX_DMA_BURST_LEN_8BEAT                                                                                     \
    ((uint32_t)0x00000800) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_TX_DMA_BURST_LEN_16BEAT                                                                                    \
    ((uint32_t)0x00001000) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_TX_DMA_BURST_LEN_32BEAT                                                                                    \
    ((uint32_t)0x00002000) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_TX_DMA_BURST_LEN_PBLX8_8BEAT                                                                               \
    ((uint32_t)0x01000100) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_TX_DMA_BURST_LEN_PBLX8_16BEAT                                                                              \
    ((uint32_t)0x01000200) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_TX_DMA_BURST_LEN_PBLX8_32BEAT                                                                              \
    ((uint32_t)0x01000400) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_TX_DMA_BURST_LEN_PBLX8_64BEAT                                                                              \
    ((uint32_t)0x01000800) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_TX_DMA_BURST_LEN_PBLX8_128BEAT                                                                             \
    ((uint32_t)0x01001000) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define ETH_TX_DMA_BURST_LEN_PBLX8_256BEAT                                                                             \
    ((uint32_t)0x01002000) /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */
#define IS_ETH_TX_DMA_BURST_LEN(LENGTH)                                                                                \
    (((LENGTH) == ETH_TX_DMA_BURST_LEN_1BEAT) || ((LENGTH) == ETH_TX_DMA_BURST_LEN_2BEAT)                              \
     || ((LENGTH) == ETH_TX_DMA_BURST_LEN_4BEAT) || ((LENGTH) == ETH_TX_DMA_BURST_LEN_8BEAT)                           \
     || ((LENGTH) == ETH_TX_DMA_BURST_LEN_16BEAT) || ((LENGTH) == ETH_TX_DMA_BURST_LEN_32BEAT)                         \
     || ((LENGTH) == ETH_TX_DMA_BURST_LEN_PBLX8_8BEAT) || ((LENGTH) == ETH_TX_DMA_BURST_LEN_PBLX8_16BEAT)              \
     || ((LENGTH) == ETH_TX_DMA_BURST_LEN_PBLX8_32BEAT) || ((LENGTH) == ETH_TX_DMA_BURST_LEN_PBLX8_64BEAT)             \
     || ((LENGTH) == ETH_TX_DMA_BURST_LEN_PBLX8_128BEAT) || ((LENGTH) == ETH_TX_DMA_BURST_LEN_PBLX8_256BEAT))

#define IS_ETH_DMA_DESC_SKIP_LEN(LENGTH) ((LENGTH) <= 0x1F)

/**
 * @}
 */

/** @addtogroup ETH_DMA_Arbitration
 * @{
 */
#define ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_1_1 ((uint32_t)0x00000000)
#define ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_2_1 ((uint32_t)0x00004000)
#define ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_3_1 ((uint32_t)0x00008000)
#define ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_4_1 ((uint32_t)0x0000C000)
#define ETH_DMA_ARBITRATION_RX_PRIOR_TX          ((uint32_t)0x00000002)
#define IS_ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX(RATIO)                                                                 \
    (((RATIO) == ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_1_1) || ((RATIO) == ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_2_1)    \
     || ((RATIO) == ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_3_1) || ((RATIO) == ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_4_1) \
     || ((RATIO) == ETH_DMA_ARBITRATION_RX_PRIOR_TX))
/**
 * @}
 */

/** @addtogroup ETH_DMA_Flags
 * @{
 */
#define ETH_DMA_FLAG_TST                 ((uint32_t)0x20000000) /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_FLAG_PMT                 ((uint32_t)0x10000000) /*!< PMT interrupt (on DMA) */
#define ETH_DMA_FLAG_MMC                 ((uint32_t)0x08000000) /*!< MMC interrupt (on DMA) */
#define ETH_DMA_FLAG_DATA_TRANSFER_ERROR ((uint32_t)0x00800000) /*!< Error bits 0-Rx DMA, 1-Tx DMA */
#define ETH_DMA_FLAG_READ_WRITE_ERROR    ((uint32_t)0x01000000) /*!< Error bits 0-write trnsf, 1-read transfr */
#define ETH_DMA_FLAG_ACCESS_ERROR        ((uint32_t)0x02000000) /*!< Error bits 0-data buffer, 1-desc. access */
#define ETH_DMA_FLAG_NIS                 ((uint32_t)0x00010000) /*!< Normal interrupt summary flag */
#define ETH_DMA_FLAG_AIS                 ((uint32_t)0x00008000) /*!< Abnormal interrupt summary flag */
#define ETH_DMA_FLAG_EARLY_RX            ((uint32_t)0x00004000) /*!< Early receive flag */
#define ETH_DMA_FLAG_FATAL_BUS_ERROR     ((uint32_t)0x00002000) /*!< Fatal bus error flag */
#define ETH_DMA_FLAG_EARLY_TX            ((uint32_t)0x00000400) /*!< Early transmit flag */
#define ETH_DMA_FLAG_RX_WDG_TIMEOUT      ((uint32_t)0x00000200) /*!< Receive watchdog timeout flag */
#define ETH_DMA_FLAG_RX_PROC_STOP        ((uint32_t)0x00000100) /*!< Receive process stopped flag */
#define ETH_DMA_FLAG_RX_BUF_UA           ((uint32_t)0x00000080) /*!< Receive buffer unavailable flag */
#define ETH_DMA_FLAG_RX                  ((uint32_t)0x00000040) /*!< Receive flag */
#define ETH_DMA_FLAG_TX_UNDERFLOW        ((uint32_t)0x00000020) /*!< Underflow flag */
#define ETH_DMA_FLAG_RX_OVERFLOW         ((uint32_t)0x00000010) /*!< Overflow flag */
#define ETH_DMA_FLAG_TX_JABBER_TIMEOUT   ((uint32_t)0x00000008) /*!< Transmit jabber timeout flag */
#define ETH_DMA_FLAG_TX_BUF_UA           ((uint32_t)0x00000004) /*!< Transmit buffer unavailable flag */
#define ETH_DMA_FLAG_TX_PROC_STOP        ((uint32_t)0x00000002) /*!< Transmit process stopped flag */
#define ETH_DMA_FLAG_TX                  ((uint32_t)0x00000001) /*!< Transmit flag */

#define IS_ETH_DMA_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFE1800) == 0x00) && ((FLAG) != 0x00))
#define IS_ETH_DMA_GET_FLAG(FLAG)                                                                                      \
    (((FLAG) == ETH_DMA_FLAG_TST) || ((FLAG) == ETH_DMA_FLAG_PMT) || ((FLAG) == ETH_DMA_FLAG_MMC)                      \
     || ((FLAG) == ETH_DMA_FLAG_DATA_TRANSFER_ERROR) || ((FLAG) == ETH_DMA_FLAG_READ_WRITE_ERROR)                      \
     || ((FLAG) == ETH_DMA_FLAG_ACCESS_ERROR) || ((FLAG) == ETH_DMA_FLAG_NIS) || ((FLAG) == ETH_DMA_FLAG_AIS)          \
     || ((FLAG) == ETH_DMA_FLAG_EARLY_RX) || ((FLAG) == ETH_DMA_FLAG_FATAL_BUS_ERROR)                                  \
     || ((FLAG) == ETH_DMA_FLAG_EARLY_TX) || ((FLAG) == ETH_DMA_FLAG_RX_WDG_TIMEOUT)                                   \
     || ((FLAG) == ETH_DMA_FLAG_RX_PROC_STOP) || ((FLAG) == ETH_DMA_FLAG_RX_BUF_UA) || ((FLAG) == ETH_DMA_FLAG_RX)     \
     || ((FLAG) == ETH_DMA_FLAG_TX_UNDERFLOW) || ((FLAG) == ETH_DMA_FLAG_RX_OVERFLOW)                                  \
     || ((FLAG) == ETH_DMA_FLAG_TX_JABBER_TIMEOUT) || ((FLAG) == ETH_DMA_FLAG_TX_BUF_UA)                               \
     || ((FLAG) == ETH_DMA_FLAG_TX_PROC_STOP) || ((FLAG) == ETH_DMA_FLAG_TX))
/**
 * @}
 */

/** @addtogroup ETH_DMA_Interrupts
 * @{
 */
#define ETH_DMA_INT_TST               ((uint32_t)0x20000000) /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_INT_PMT               ((uint32_t)0x10000000) /*!< PMT interrupt (on DMA) */
#define ETH_DMA_INT_MMC               ((uint32_t)0x08000000) /*!< MMC interrupt (on DMA) */
#define ETH_DMA_INT_NIS               ((uint32_t)0x00010000) /*!< Normal interrupt summary */
#define ETH_DMA_INT_AIS               ((uint32_t)0x00008000) /*!< Abnormal interrupt summary */
#define ETH_DMA_INT_EARLY_RX          ((uint32_t)0x00004000) /*!< Early receive interrupt */
#define ETH_DMA_INT_FATAL_BUS_ERROR   ((uint32_t)0x00002000) /*!< Fatal bus error interrupt */
#define ETH_DMA_INT_EARLY_TX          ((uint32_t)0x00000400) /*!< Early transmit interrupt */
#define ETH_DMA_INT_RX_WDG_TIMEOUT    ((uint32_t)0x00000200) /*!< Receive watchdog timeout interrupt */
#define ETH_DMA_INT_RX_PROC_STOP      ((uint32_t)0x00000100) /*!< Receive process stopped interrupt */
#define ETH_DMA_INT_RX_BUF_UA         ((uint32_t)0x00000080) /*!< Receive buffer unavailable interrupt */
#define ETH_DMA_INT_RX                ((uint32_t)0x00000040) /*!< Receive interrupt */
#define ETH_DMA_INT_TX_UNDERFLOW      ((uint32_t)0x00000020) /*!< Underflow interrupt */
#define ETH_DMA_INT_RX_OVERFLOW       ((uint32_t)0x00000010) /*!< Overflow interrupt */
#define ETH_DMA_INT_TX_JABBER_TIMEOUT ((uint32_t)0x00000008) /*!< Transmit jabber timeout interrupt */
#define ETH_DMA_INT_TX_BUF_UA         ((uint32_t)0x00000004) /*!< Transmit buffer unavailable interrupt */
#define ETH_DMA_INT_TX_PROC_STOP      ((uint32_t)0x00000002) /*!< Transmit process stopped interrupt */
#define ETH_DMA_INT_TX                ((uint32_t)0x00000001) /*!< Transmit interrupt */

#define IS_ETH_DMA_INT(IT) ((((IT) & (uint32_t)0xFFFE1800) == 0x00) && ((IT) != 0x00))
#define IS_ETH_DMA_GET_INT(IT)                                                                                         \
    (((IT) == ETH_DMA_INT_TST) || ((IT) == ETH_DMA_INT_PMT) || ((IT) == ETH_DMA_INT_MMC) || ((IT) == ETH_DMA_INT_NIS)  \
     || ((IT) == ETH_DMA_INT_AIS) || ((IT) == ETH_DMA_INT_EARLY_RX) || ((IT) == ETH_DMA_INT_FATAL_BUS_ERROR)           \
     || ((IT) == ETH_DMA_INT_EARLY_TX) || ((IT) == ETH_DMA_INT_RX_WDG_TIMEOUT) || ((IT) == ETH_DMA_INT_RX_PROC_STOP)   \
     || ((IT) == ETH_DMA_INT_RX_BUF_UA) || ((IT) == ETH_DMA_INT_RX) || ((IT) == ETH_DMA_INT_TX_UNDERFLOW)              \
     || ((IT) == ETH_DMA_INT_RX_OVERFLOW) || ((IT) == ETH_DMA_INT_TX_JABBER_TIMEOUT)                                   \
     || ((IT) == ETH_DMA_INT_TX_BUF_UA) || ((IT) == ETH_DMA_INT_TX_PROC_STOP) || ((IT) == ETH_DMA_INT_TX))

/**
 * @}
 */

/** @addtogroup ETH_DMA_transmit_process_state_
 * @{
 */
#define ETH_DMA_TX_PROC_STOPPED   ((uint32_t)0x00000000) /*!< Stopped - Reset or Stop Tx Command issued */
#define ETH_DMA_TX_PROC_FETCHING  ((uint32_t)0x00100000) /*!< Running - fetching the Tx descriptor */
#define ETH_DMA_TX_PROC_WAITING   ((uint32_t)0x00200000) /*!< Running - waiting for status */
#define ETH_DMA_TX_PROC_READING   ((uint32_t)0x00300000) /*!< Running - reading the data from host memory */
#define ETH_DMA_TX_PROC_SUSPENDED ((uint32_t)0x00600000) /*!< Suspended - Tx Desciptor unavailabe */
#define ETH_DMA_TX_PROC_CLOSING   ((uint32_t)0x00700000) /*!< Running - closing Rx descriptor */

/**
 * @}
 */

/** @addtogroup ETH_DMA_receive_process_state_
 * @{
 */
#define ETH_DMA_RX_PROC_STOPPED   ((uint32_t)0x00000000) /*!< Stopped - Reset or Stop Rx Command issued */
#define ETH_DMA_RX_PROC_FETCHING  ((uint32_t)0x00020000) /*!< Running - fetching the Rx descriptor */
#define ETH_DMA_RX_PROC_WAITING   ((uint32_t)0x00060000) /*!< Running - waiting for packet */
#define ETH_DMA_RX_PROC_SUSPENDED ((uint32_t)0x00080000) /*!< Suspended - Rx Desciptor unavailable */
#define ETH_DMA_RX_PROC_CLOSING   ((uint32_t)0x000A0000) /*!< Running - closing descriptor */
#define ETH_DMA_RX_PROC_QUEUING   ((uint32_t)0x000E0000) /*!< Running - queuing the recieve frame into host memory */

/**
 * @}
 */

/** @addtogroup ETH_DMA_overflow_
 * @{
 */
#define ETH_DMA_OVERFLOW_RX_FIFO_COUNTER      ((uint32_t)0x10000000) /*!< Overflow bit for DATFIFO overflow counter */
#define ETH_DMA_OVERFLOW_MISSED_FRAME_COUNTER ((uint32_t)0x00010000) /*!< Overflow bit for missed frame counter */
#define IS_ETH_DMA_GET_OVERFLOW(OVERFLOW)                                                                              \
    (((OVERFLOW) == ETH_DMA_OVERFLOW_RX_FIFO_COUNTER) || ((OVERFLOW) == ETH_DMA_OVERFLOW_MISSED_FRAME_COUNTER))

/**
 * @}
 */

/** @addtogroup ETH_PMT_Flags
 * @{
 */
#define ETH_PMT_FLAG_RWKUPFILTRST ((uint32_t)0x80000000) /*!< Wake-Up Frame Filter Register Poniter Reset */
#define ETH_PMT_FLAG_RWKPRCVD     ((uint32_t)0x00000040) /*!< Wake-Up Frame Received */
#define ETH_PMT_FLAG_MGKPRCVD     ((uint32_t)0x00000020) /*!< Magic Packet Received */
#define IS_ETH_PMT_GET_FLAG(FLAG) (((FLAG) == ETH_PMT_FLAG_RWKPRCVD) || ((FLAG) == ETH_PMT_FLAG_MGKPRCVD))

/**
 * @}
 */

/** @addtogroup ETH_MMC_Tx_Interrupts
 * @{
 */
#define ETH_MMC_INT_TXGFRMIS ((uint32_t)0x00200000) /*!< When Tx good frame counter reaches half the maximum value */
#define ETH_MMC_INT_TXMCOLGFIS                                                                                         \
    ((uint32_t)0x00008000) /*!< When Tx good multi col counter reaches half the maximum value */
#define ETH_MMC_INT_TXSCOLGFIS                                                                                         \
    ((uint32_t)0x00004000) /*!< When Tx good single col counter reaches half the maximum value */

/**
 * @}
 */

/** @addtogroup ETH_MMC_Rx_Interrupts
 * @{
 */
#define ETH_MMC_INT_RXUCGFIS                                                                                           \
    ((uint32_t)0x10020000) /*!< When Rx good unicast frames counter reaches half the maximum value */
#define ETH_MMC_INT_RXALGNERFIS                                                                                        \
    ((uint32_t)0x10000040) /*!< When Rx alignment error counter reaches half the maximum value */
#define ETH_MMC_INT_RXCRCERFIS ((uint32_t)0x10000020) /*!< When Rx crc error counter reaches half the maximum value */
#define IS_ETH_MMC_INT(IT)                                                                                             \
    (((((IT) & (uint32_t)0xFFDF3FFF) == 0x00) || (((IT) & (uint32_t)0xEFFDFF9F) == 0x00)) && ((IT) != 0x00))
#define IS_ETH_MMC_GET_INT(IT)                                                                                         \
    (((IT) == ETH_MMC_INT_TXGFRMIS) || ((IT) == ETH_MMC_INT_TXMCOLGFIS) || ((IT) == ETH_MMC_INT_TXSCOLGFIS)            \
     || ((IT) == ETH_MMC_INT_RXUCGFIS) || ((IT) == ETH_MMC_INT_RXALGNERFIS) || ((IT) == ETH_MMC_INT_RXCRCERFIS))
/**
 * @}
 */

/** @addtogroup ETH_MMC_Registers
 * @{
 */
#define ETH_MMCCTRL        ((uint32_t)0x00000100) /*!< MMC CTRL register */
#define ETH_MMCRXINT       ((uint32_t)0x00000104) /*!< MMC RIR register */
#define ETH_MMCTXINT       ((uint32_t)0x00000108) /*!< MMC TIR register */
#define ETH_MMCRXINTMSK    ((uint32_t)0x0000010C) /*!< MMC RIMR register */
#define ETH_MMCTXINTMSK    ((uint32_t)0x00000110) /*!< MMC TIMR register */
#define ETH_MMCTXGFASCCNT  ((uint32_t)0x0000014C) /*!< MMC TGFSCCR register */
#define ETH_MMCTXGFAMSCCNT ((uint32_t)0x00000150) /*!< MMC TGFMSCCR register */
#define ETH_MMCTXGFCNT     ((uint32_t)0x00000168) /*!< MMC TGFCR register */
#define ETH_MMCRXFCECNT    ((uint32_t)0x00000194) /*!< MMC RFCECR register */
#define ETH_MMCRXFAECNT    ((uint32_t)0x00000198) /*!< MMC RFAECR register */
#define ETH_MMCRXGUFCNT    ((uint32_t)0x000001C4) /*!< MMC RGUFCR register */

#define IS_ETH_MMC_REGISTER(REG)                                                                                       \
    (((REG) == ETH_MMCCTRL) || ((REG) == ETH_MMCRXINT) || ((REG) == ETH_MMCTXINT) || ((REG) == ETH_MMCRXINTMSK)        \
     || ((REG) == ETH_MMCTXINTMSK) || ((REG) == ETH_MMCTXGFASCCNT) || ((REG) == ETH_MMCTXGFAMSCCNT)                    \
     || ((REG) == ETH_MMCTXGFCNT) || ((REG) == ETH_MMCRXFCECNT) || ((REG) == ETH_MMCRXFAECNT)                          \
     || ((REG) == ETH_MMCRXGUFCNT))

/**
 * @}
 */

/** @addtogroup ETH_PTP_time_update_method
 * @{
 */
#define ETH_PTP_FINE_UPDATE       ((uint32_t)0x00000001) /*!< Fine Update method */
#define ETH_PTP_COARSE_UPDATE     ((uint32_t)0x00000000) /*!< Coarse Update method */
#define IS_ETH_PTP_UPDATE(UPDATE) (((UPDATE) == ETH_PTP_FINE_UPDATE) || ((UPDATE) == ETH_PTP_COARSE_UPDATE))

/**
 * @}
 */

/** @addtogroup ETH_PTP_Flags
 * @{
 */
#define ETH_PTP_FLAG_TSADDREG ((uint32_t)0x00000020) /*!< Addend Register Update */
#define ETH_PTP_FLAG_TSTRIG   ((uint32_t)0x00000010) /*!< Time Stamp Interrupt Trigger */
#define ETH_PTP_FLAG_TSUPDT   ((uint32_t)0x00000008) /*!< Time Stamp Update */
#define ETH_PTP_FLAG_TSINIT   ((uint32_t)0x00000004) /*!< Time Stamp Initialize */
#define IS_ETH_PTP_GET_FLAG(FLAG)                                                                                      \
    (((FLAG) == ETH_PTP_FLAG_TSADDREG) || ((FLAG) == ETH_PTP_FLAG_TSTRIG) || ((FLAG) == ETH_PTP_FLAG_TSUPDT)           \
     || ((FLAG) == ETH_PTP_FLAG_TSINIT))

#define IS_ETH_PTP_SUBSECOND_INCREMENT(SUBSECOND) ((SUBSECOND) <= 0xFF)

/**
 * @}
 */

/** @addtogroup ETH_PTP_time_sign
 * @{
 */
#define ETH_PTP_POSITIVE_TIME      ((uint32_t)0x00000000) /*!< Positive time value */
#define ETH_PTP_NEGATIVE_TIME      ((uint32_t)0x80000000) /*!< Negative time value */
#define IS_ETH_PTP_TIME_SIGN(SIGN) (((SIGN) == ETH_PTP_POSITIVE_TIME) || ((SIGN) == ETH_PTP_NEGATIVE_TIME))

#define IS_ETH_PTP_TIME_STAMP_UPDATE_SUBSECOND(SUBSECOND) ((SUBSECOND) <= 0x7FFFFFFF)

#define ETH_PTPTSCTRL ((uint32_t)0x00000700) /*!< PTP TSCR register */
#define ETH_PTPSSINC  ((uint32_t)0x00000704) /*!< PTP SSIR register */
#define ETH_PTPSEC    ((uint32_t)0x00000708) /*!< PTP TSHR register */
#define ETH_PTPNS     ((uint32_t)0x0000070C) /*!< PTP TSLR register */
#define ETH_PTPSECUP  ((uint32_t)0x00000710) /*!< PTP TSHUR register */
#define ETH_PTPNSUP   ((uint32_t)0x00000714) /*!< PTP TSLUR register */
#define ETH_PTPTSADD  ((uint32_t)0x00000718) /*!< PTP TSAR register */
#define ETH_PTPTTSEC  ((uint32_t)0x0000071C) /*!< PTP TTHR register */
#define ETH_PTPTTNS   ((uint32_t)0x00000720) /* PTP TTLR register */
#define IS_ETH_PTP_REGISTER(REG)                                                                                       \
    (((REG) == ETH_PTPTSCTRL) || ((REG) == ETH_PTPSSINC) || ((REG) == ETH_PTPSEC) || ((REG) == ETH_PTPNS)              \
     || ((REG) == ETH_PTPSECUP) || ((REG) == ETH_PTPNSUP) || ((REG) == ETH_PTPTSADD) || ((REG) == ETH_PTPTTSEC)        \
     || ((REG) == ETH_PTPTTNS))

/**
 * @}
 */

/**
 * @}
 */
/** @addtogroup ETH_Exported_Macros
 * @{
 */
/**
 * @}
 */

/* ETHERNET errors */
#define ETH_ERROR   ((uint32_t)0)
#define ETH_SUCCESS ((uint32_t)1)

/**
 * @brief the function prototype of initialize PHY.
 * @param ETH_InitStruct init struct of ETH MAC peripheral.
 * @return whether initialization succeed:
 *  - ETH_ERROR initialization fail
 *  - ETH_SUCCESS initialization succeed
 */
typedef uint32_t (*ETH_InitPHY)(ETH_InitType* ETH_InitStruct);

/** @addtogroup ETH_Exported_Functions
 * @{
 */
void ETH_DeInit(void);

uint32_t ETH_Init(ETH_InitType* ETH_InitStruct, ETH_InitPHY callable);
void ETH_InitStruct(ETH_InitType* ETH_InitStruct);
void ETH_SoftwareReset(void);
FlagStatus ETH_GetSoftwareResetStatus(void);
void ETH_EnableTxRx(void);
uint32_t ETH_TxPacket(u8* ppkt, u16 FrameLength);
uint32_t ETH_RxPacket(u8* ppkt, uint8_t checkErr);
uint32_t ETH_GetRxPacketSize(void);
void ETH_DropRxPacket(void);

#define ETH_INTERFACE_RMII 0
#define ETH_INTERFACE_MII  1

void ETH_ConfigGpio(uint8_t ETH_Interface, uint8_t remap);

/* PHY */
uint16_t ETH_ReadPhyRegister(u16 PHYAddress, u16 PHYReg);
uint32_t ETH_WritePhyRegister(u16 PHYAddress, u16 PHYReg, u16 PHYValue);
uint32_t ETH_EnablePhyLoopBack(u16 PHYAddress, FunctionalState Cmd);

/* MAC */
void ETH_EnableMacTx(FunctionalState Cmd);
void ETH_EnableMacRx(FunctionalState Cmd);
FlagStatus ETH_GetFlowCtrlBusyStatus(void);
void ETH_GeneratePauseCtrlFrame(void);
void ETH_EnableBackPressureActivation(FunctionalState Cmd);
FlagStatus ETH_GetMacFlagStatus(uint32_t ETH_MAC_FLAG);
INTStatus ETH_GetMacIntStatus(uint32_t ETH_MAC_IT);
void ETH_EnableMacInt(uint32_t ETH_MAC_IT, FunctionalState Cmd);
void ETH_SetMacAddr(uint32_t MacAddr, u8* Addr);
void ETH_GetMacAddr(uint32_t MacAddr, u8* Addr);
void ETH_EnableMacAddrPerfectFilter(uint32_t MacAddr, FunctionalState Cmd);
void ETH_ConfigMacAddrFilter(uint32_t MacAddr, uint32_t Filter);
void ETH_ConfigMacAddrMaskBytesFilter(uint32_t MacAddr, uint32_t MaskByte);

/* DMA Tx/Rx descriptors */
void ETH_ConfigDmaTxDescInChainMode(ETH_DMADescType* DMATxDescTab, u8* TxBuff, uint32_t BufSize, uint32_t TxBuffCount);
void ETH_ConfigDmaTxDescInRingMode(ETH_DMADescType* DMATxDescTab,
                                   u8* TxBuff1,
                                   u8* TxBuff2,
                                   uint32_t BufSize,
                                   uint32_t TxBuffCount);
FlagStatus ETH_GetDmaTxDescFlagStatus(ETH_DMADescType* DMATxDesc, uint32_t ETH_DMATxDescFlag);
uint32_t ETH_GetDmaTxDescCollisionCount(ETH_DMADescType* DMATxDesc);
void ETH_SetDmaTxDescOwn(ETH_DMADescType* DMATxDesc);
void ETH_EnableDmaTxDescTransmitInt(ETH_DMADescType* DMATxDesc, FunctionalState Cmd);
void ETH_ConfigDmaTxDescFrameSegment(ETH_DMADescType* DMATxDesc, uint32_t DMATxDesc_FrameSegment);
void ETH_ConfigDmaTxDescChecksumInsertion(ETH_DMADescType* DMATxDesc, uint32_t DMATxDesc_Checksum);
void ETH_EnableDmaTxDescCrc(ETH_DMADescType* DMATxDesc, FunctionalState Cmd);
void ETH_EnableDmaTxDescEndOfRing(ETH_DMADescType* DMATxDesc, FunctionalState Cmd);
void ETH_EnableDmaTxDescSecondAddrChained(ETH_DMADescType* DMATxDesc, FunctionalState Cmd);
void ETH_EnableDmaTxDescShortFramePadding(ETH_DMADescType* DMATxDesc, FunctionalState Cmd);
void ETH_EnableDmaTxDescTimeStamp(ETH_DMADescType* DMATxDesc, FunctionalState Cmd);
void ETH_ConfigDmaTxDescBufSize(ETH_DMADescType* DMATxDesc, uint32_t BufferSize1, uint32_t BufferSize2);
void ETH_ConfigDmaRxDescInChainMode(ETH_DMADescType* DMARxDescTab, u8* RxBuff, uint32_t BufSize, uint32_t RxBuffCount);
void ETH_ConfigDmaRxDescInRingMode(ETH_DMADescType* DMARxDescTab,
                                   u8* RxBuff1,
                                   u8* RxBuff2,
                                   uint32_t BuffSize,
                                   uint32_t RxBuffCount);
FlagStatus ETH_GetDmaRxDescFlagStatus(ETH_DMADescType* DMARxDesc, uint32_t ETH_DMARxDescFlag);
void ETH_SetDmaRxDescOwn(ETH_DMADescType* DMARxDesc);
uint32_t ETH_GetDmaRxDescFrameLen(__IO ETH_DMADescType* DMARxDesc);
void ETH_EnableDmaRxDescReceiveInt(ETH_DMADescType* DMARxDesc, FunctionalState Cmd);
void ETH_EnableDmaRxDescEndOfRing(ETH_DMADescType* DMARxDesc, FunctionalState Cmd);
void ETH_EnableDmaRxDescSecondAddrChained(ETH_DMADescType* DMARxDesc, FunctionalState Cmd);
uint32_t ETH_GetDmaRxDescBufSize(ETH_DMADescType* DMARxDesc, uint32_t DMARxDesc_Buffer);

/* DMA */
FlagStatus ETH_GetDmaFlagStatus(uint32_t ETH_DMA_FLAG);
void ETH_ClrDmaFlag(uint32_t ETH_DMA_FLAG);
INTStatus ETH_GetDmaIntStatus(uint32_t ETH_DMA_IT);
void ETH_ClrDmaIntPendingBit(uint32_t ETH_DMA_IT);
uint32_t ETH_GetTxProcState(void);
uint32_t ETH_GetRxProcState(void);
void ETH_FlushTxFifo(void);
FlagStatus ETH_GetFlushTxFifoStatus(void);
void ETH_EnableDmaTx(FunctionalState Cmd);
void ETH_EnableDmaRx(FunctionalState Cmd);
void ETH_EnableDmaInt(uint32_t ETH_DMA_IT, FunctionalState Cmd);
FlagStatus ETH_GetDmaOverflowStatus(uint32_t ETH_DMA_Overflow);
uint32_t ETH_GetRxOverflowMissedFrameCounter(void);
uint32_t ETH_GetBufUnavailableMissedFrameCounter(void);
uint32_t ETH_GetCurrentTxDescAddr(void);
uint32_t ETH_GetCurrentRxDescAddr(void);
uint32_t ETH_GetCurrentTxBufAddr(void);
uint32_t ETH_GetCurrentRxBufAddr(void);
void ETH_ResumeDmaTx(void);
void ETH_ResumeDmaRx(void);

/* PMT */
void ETH_ResetWakeUpFrameFilter(void);
void ETH_SetWakeUpFrameFilter(uint32_t* Buffer);
void ETH_EnableGlobalUnicastWakeUp(FunctionalState Cmd);
FlagStatus ETH_GetPmtFlagStatus(uint32_t ETH_PMT_FLAG);
void ETH_EnableWakeUpFrameDetection(FunctionalState Cmd);
void ETH_EnableMagicPacketDetection(FunctionalState Cmd);
void ETH_EnablePowerDown(FunctionalState Cmd);

/* MMC */
void ETH_EnableMmcCounterFreeze(FunctionalState Cmd);
void ETH_EnableMmcResetOnRead(FunctionalState Cmd);
void ETH_EnableMmcCounterRollover(FunctionalState Cmd);
void ETH_ResetMmcCounters(void);
void ETH_EnableMmcInt(uint32_t ETH_MMC_IT, FunctionalState Cmd);
INTStatus ETH_GetMmcIntStatus(uint32_t ETH_MMC_IT);
uint32_t ETH_GetMmcRegisterValue(uint32_t ETH_MMCReg);

/* PTP */
uint32_t ETH_TxPtpPacket(u8* ppkt, u16 FrameLength, uint32_t* PTPTxTab);
uint32_t ETH_RxPtpPacket(u8* ppkt, uint32_t* PTPRxTab);
void ETH_ConfigDmaPtpTxDescInChainMode(ETH_DMADescType* DMATxDescTab,
                                       ETH_DMADescType* DMAPTPTxDescTab,
                                       u8* TxBuff,
                                       uint32_t TxBuffCount);
void ETH_ConfigDmaPtpRxDescInChainMode(ETH_DMADescType* DMARxDescTab,
                                       ETH_DMADescType* DMAPTPRxDescTab,
                                       u8* RxBuff,
                                       uint32_t RxBuffCount);
void ETH_UpdatePtpTimeStampAddend(void);
void ETH_EnablePtpTimeStampIntTrigger(void);
void ETH_UpdatePtpTimeStamp(void);
void ETH_InitPtpTimeStamp(void);
void ETH_ConfigPtpUpdateMethod(uint32_t UpdateMethod);
void ETH_StartPTPTimeStamp(FunctionalState Cmd);
FlagStatus ETH_GetPtpFlagStatus(uint32_t ETH_PTP_FLAG);
void ETH_SetPtpSubSecondInc(uint32_t SubSecondValue);
void ETH_SetPtpTimeStampUpdate(uint32_t Sign, uint32_t SecondValue, uint32_t SubSecondValue);
void ETH_SetPtpTimeStampAddend(uint32_t Value);
void ETH_SetPtpTargetTime(uint32_t HighValue, uint32_t LowValue);
uint32_t ETH_GetPtpRegisterValue(uint32_t ETH_PTPReg);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __N32G45X_ETH_H__ */
/**
 * @}
 */

/**
 * @}
 */
