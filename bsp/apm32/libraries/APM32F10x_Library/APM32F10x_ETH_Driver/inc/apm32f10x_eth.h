/*!
 * @file        apm32f10x_eth.c
 *
 * @brief       This file provides all the ETH firmware functions
 *
 * @version     V1.0.3
 *
 * @date        2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F10x_ETH_H
#define __APM32F10x_ETH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f10x.h"

/** @addtogroup APM32F10x_ETHDriver
  @{
*/

/** @addtogroup ETH_Driver
  @{
*/

/** @defgroup ETH_Enumerations
  @{
*/

/**
 * @brief    ETH AutoNegotiation
 */
typedef enum
{
    ETH_AUTONEGOTIATION_DISABLE,    /*!< Disable negotiation */
    ETH_AUTONEGOTIATION_ENABLE      /*!< Enable negotiation */
} ETH_AUTONEGOTIATION_T;

/**
 * @brief    ETH Watchdog
 */
typedef enum
{
    ETH_WATCHDOG_ENABLE,    /*!< Enable watch dog */
    ETH_WATCHDOG_DISABLE    /*!< Disable watch dog */
} ETH_WATCHDOG_T;

/**
 * @brief    ETH Jabber
 */
typedef enum
{
    ETH_JABBER_ENABLE,  /*!< Enable jabber */
    ETH_JABBER_DISABLE  /*!< Disable jabber */
} ETH_JABBER_T;

/**
 * @brief    ETH Inter Frame Gap
 */
typedef enum
{
    ETH_INTERFRAMEGAP_96BIT = 0x00, /*!< Inter-Frame gap = 96-bit */
    ETH_INTERFRAMEGAP_88BIT = 0x01, /*!< Inter-Frame gap = 88-bit */
    ETH_INTERFRAMEGAP_80BIT = 0x02, /*!< Inter-Frame gap = 80-bit */
    ETH_INTERFRAMEGAP_72BIT = 0x03, /*!< Inter-Frame gap = 72-bit */
    ETH_INTERFRAMEGAP_64BIT = 0x04, /*!< Inter-Frame gap = 64-bit */
    ETH_INTERFRAMEGAP_56BIT = 0x05, /*!< Inter-Frame gap = 56-bit */
    ETH_INTERFRAMEGAP_48BIT = 0x06, /*!< Inter-Frame gap = 48-bit */
    ETH_INTERFRAMEGAP_40BIT = 0x07  /*!< Inter-Frame gap = 40-bit */
} ETH_INTERFRAMEGAP_T;

/**
 * @brief    ETH Carrier Sense
 */
typedef enum
{
    ETH_CARRIERSENCE_ENABLE,    /*!< Disable carrier sense during transmission */
    ETH_CARRIERSENCE_DISABLE    /*!< Ignore MII CRS signal */
} ETH_CARRIERSENCE_T;

/**
 * @brief    ETH Speed
 */
typedef enum
{
    ETH_SPEED_10M,  /*!< 10M speed */
    ETH_SPEED_100M  /*!< 100M speed */
} ETH_SPEED_T;

/**
 * @brief    ETH Receive Own
 */
typedef enum
{
    ETH_RECEIVEOWN_ENABLE,  /*!< Enable receive own */
    ETH_RECEIVEOWN_DISABLE  /*!< Disable receive own */
} ETH_RECEIVEOWN_T;

/**
 * @brief    ETH Loop Back Mode
 */
typedef enum
{
    ETH_LOOPBACKMODE_DISABLE,   /*!< Disable loopback mode */
    ETH_LOOPBACKMODE_ENABLE     /*!< Enable loopback mode */
} ETH_LOOPBACKMODE_T;

/**
 * @brief    ETH Duplex Mode
 */
typedef enum
{
    ETH_MODE_HALFDUPLEX,    /*!< Half-Duplex */
    ETH_MODE_FULLDUPLEX     /*!< Full-Duplex */
} ETH_MODE_T;

/**
 * @brief    ETH Checksum Offload
 */
typedef enum
{
    ETH_CHECKSUMOFFLAOD_DISABLE,    /*!< Disable IPv4 checksum offload */
    ETH_CHECKSUMOFFLAOD_ENABLE      /*!< Enable Ipv4 checksum offload */
} ETH_CHECKSUMOFFLAOD_T;

/**
 * @brief    ETH Retry Transmission
 */
typedef enum
{
    ETH_RETRYTRANSMISSION_ENABLE,   /*!< Enable retry */
    ETH_RETRYTRANSMISSION_DISABLE   /*!< Disable retry */
} ETH_RETRYTRANSMISSION_T;

/**
 * @brief    ETH Automatic Pad CRC Strip
 */
typedef enum
{
    ETH_AUTOMATICPADCRCSTRIP_DISABLE,   /*!< Disable automatic pad or CRC stripping */
    ETH_AUTOMATICPADCRCSTRIP_ENABLE     /*!< Enable automatic pad or CRC stripping */
} ETH_AUTOMATICPADCRCSTRIP_T;

/**
 * @brief    ETH Back Off Limit
 */
typedef enum
{
    ETH_BACKOFFLIMIT_10,    /*!< Set back off limit to 10 */
    ETH_BACKOFFLIMIT_8,     /*!< Set back off limit to 18 */
    ETH_BACKOFFLIMIT_4,     /*!< Set back off limit to 4 */
    ETH_BACKOFFLIMIT_1      /*!< Set back off limit to 1 */
} ETH_BACKOFFLIMIT_T;

/**
 * @brief    ETH Deferral Check
 */
typedef enum
{
    ETH_DEFFERRALCHECK_DISABLE, /*!< Disable deferral check */
    ETH_DEFFERRALCHECK_ENABLE   /*!< Enable deferral check */
} ETH_DEFFERRALCHECK_T;

/**
 * @brief    ETH Receive All
 */
typedef enum
{
    ETH_RECEIVEAll_DISABLE, /*!< Disable receive all */
    ETH_RECEIVEALL_ENABLE   /*!< Enable receive all */
} ETH_RECEIVEAll_T;

/**
 * @brief    ETH Source Addr Filter
 */
typedef enum
{
    ETH_SOURCEADDRFILTER_DISABLE,                       /*!< Disable source address filter */
    ETH_SOURCEADDRFILTER_NORMAL_ENABLE = BIT9,          /*!< Enable normal source address filter */
    ETH_SOURCEADDRFILTER_INVERSE_ENABLE = BIT8 | BIT9,  /*!< Enable inverse source address filter */
} ETH_SOURCEADDRFILTER_T;

/**
 * @brief    ETH Pass Control Frames
 */
typedef enum
{
    ETH_PASSCONTROLFRAMES_BLOCKALL = 1,             /*!< Even if all control frames except pause frames fail the
                                                        address filter, MAC forwards them to the application */
    ETH_PASSCONTROLFRAMES_FORWARDALL,               /*!< MAC forwards control frames to the application even if
                                                        they do not pass the address filter */
    ETH_PASSCONTROLFRAMES_FORWARDPASSEDADDRFILTER   /*!< MAC forwards control frames that pass through the address filter */
} ETH_PASSCONTROLFRAMES_T;

/**
 * @brief    ETH Broadcast Frames Reception
 */
typedef enum
{
    ETH_BROADCASTFRAMESRECEPTION_ENABLE,    /*!< Enable broadcast frames */
    ETH_BROADCASTFRAMESRECEPTION_DISABLE    /*!< Disable broadcast frames */
} ETH_BROADCASTFRAMESRECEPTION_T;

/**
 * @brief    ETH Destination Addr Filter
 */
typedef enum
{
    ETH_DESTINATIONADDRFILTER_NORMAL,   /*!< Normal destination address filter */
    ETH_DESTINATIONADDRFILTER_INVERSE   /*!< Inverse destination address filter */
} ETH_DESTINATIONADDRFILTER_T;

/**
 * @brief    ETH Destination Addr Filter
 */
typedef enum
{
    ETH_PROMISCUOUS_MODE_DISABLE,   /*!< Disable promiscuous mode */
    ETH_PROMISCUOUS_MODE_ENABLE     /*!< Enable promiscuous mode */
} ETH_PROMISCUOUS_MODE_T;

/**
 * @brief    ETH Multicast Frames Filter
 */
typedef enum
{
    ETH_MULTICASTFRAMESFILTER_PERFECT,                      /*!< Multicast perfect filter */
    ETH_MULTICASTFRAMESFILTER_NONE = BIT4,                  /*!< Multicast pass all multicast */
    ETH_MULTICASTFRAMESFILTER_HASHTABLE = BIT2,             /*!< Multicast hash multicast */
    ETH_MULTICASTFRAMESFILTER_PERFECTHASHTABLE = BIT2 | BIT10 /*!< Multicast perfect hash table */
} ETH_MULTICASTFRAMESFILTER_T;

/**
 * @brief    ETH Unicast Frames Filter
 */
typedef enum
{
    ETH_UNICASTFRAMESFILTER_PERFECT,                        /*!< Unicast perfect filter */
    ETH_UNICASTFRAMESFILTER_HASHTABLE = BIT1,               /*!< Unicast hash table */
    ETH_UNICASTFRAMESFILTER_PERFECTHASHTABLE = BIT1 | BIT10 /*!< Unicast perfect hash table */
} ETH_UNICASTFRAMESFILTER_T;

/**
 * @brief    ETH Zero Quanta Pause
 */
typedef enum
{
    ETH_ZEROQUANTAPAUSE_ENABLE,     /*!< Enable zero-quanta pause */
    ETH_ZEROQUANTAPAUSE_DISABLE     /*!< Disable zero-quanta pause */
} ETH_ZEROQUANTAPAUSE_T;

/**
 * @brief    ETH Pause Low Threshold
 */
typedef enum
{
    ETH_PAUSELOWTHRESHOLD_MINUS4,   /*!< Minus 4 slot-time */
    ETH_PAUSELOWTHRESHOLD_MINUS28,  /*!< Minus 28 slot-time */
    ETH_PAUSELOWTHRESHOLD_MINUS144, /*!< Minus 144 slot-time */
    ETH_PAUSELOWTHRESHOLD_MINUS256  /*!< Minus 256 slot-time */
} ETH_PAUSELOWTHRESHOLD_T;

/**
 * @brief    ETH Unicast Pause Frame Detect
 */
typedef enum
{
    ETH_UNICASTPAUSEFRAMEDETECT_DISABLE,    /*!< Disable unicast pause frame detect */
    ETH_UNICASTPAUSEFRAMEDETECT_ENABLE      /*!< Enable unicast pause frame detect */
} ETH_UNICASTPAUSEFRAMEDETECT_T;

/**
 * @brief    ETH Receive Flow Control
 */
typedef enum
{
    ETH_RECEIVEFLOWCONTROL_DISABLE, /*!< Disable receive flow control */
    ETH_RECEIVEFLOWCONTROL_ENABLE   /*!< Enable receive flow control */
} ETH_RECEIVEFLOWCONTROL_T;

/**
 * @brief    ETH Transmit Flow Control
 */
typedef enum
{
    ETH_TRANSMITFLOWCONTROL_DISABLE,    /*!< Disable transmit flow control */
    ETH_TRANSMITFLOWCONTROL_ENABLE      /*!< Enable transmit flow control */
} ETH_TRANSMITFLOWCONTROL_T;

/**
 * @brief    ETH VLAN Tag Comparison
 */
typedef enum
{
    ETH_VLANTAGCOMPARISON_16BIT,    /*!< 16-bit VLAN tag comparison */
    ETH_VLANTAGCOMPARISON_12BIT     /*!< 12-bit VLAN tag comparison */
} ETH_VLANTAGCOMPARISON_T;

/**
 * @brief    ETH MAC Flags
 */
typedef enum
{
    ETH_MAC_FLAG_TST  = 0x00000200, /*!< Time stamp trigger flag */
    ETH_MAC_FLAG_MMCT = 0x00000040, /*!< MMC transmit flag */
    ETH_MAC_FLAG_MMCR = 0x00000020, /*!< MMC receive flag */
    ETH_MAC_FLAG_MMC  = 0x00000010, /*!< MMC flag */
    ETH_MAC_FLAG_PMT  = 0x00000008  /*!< PMT flag */
} ETH_MAC_FLAG_T;

/**
 * @brief    ETH MAC Interrupts
 */
typedef enum
{
    ETH_MAC_INT_TST  = 0x00000200,  /*!< Time stamp trigger interrupt */
    ETH_MAC_INT_MMCT = 0x00000040,  /*!< MMC transmit interrupt */
    ETH_MAC_INT_MMCR = 0x00000020,  /*!< MMC receive interrupt */
    ETH_MAC_INT_MMC  = 0x00000010,  /*!< MMC interrupt */
    ETH_MAC_INT_PMT  = 0x00000008   /*!< PMT interrupt */
} ETH_MAC_INT_T;

/**
 * @brief    ETH MAC Interrupts
 */
typedef enum
{
    ETH_MAC_ADDRESS0 = 0x00000000,  /*!< MAC Address0 */
    ETH_MAC_ADDRESS1 = 0x00000008,  /*!< MAC Address1 */
    ETH_MAC_ADDRESS2 = 0x00000010,  /*!< MAC Address2 */
    ETH_MAC_ADDRESS3 = 0x00000018   /*!< MAC Address3 */
} ETH_MAC_ADDRESS_T;

/**
 * @brief    ETH MAC addresses filter SA/DA
 */
typedef enum
{
    ETH_MAC_ADDRESSFILTER_SA,           /*!< MAC Address is used to compare with the
                                            SA fields of the received frame */
    ETH_MAC_ADDRESSFILTER_DA = BIT30    /*!< MAC Address is used to compare with the
                                            DA fields of the received frame */
} ETH_MAC_ADDRESSFILTER_T;

/**
 * @brief    ETH MAC addresses filter Mask bytes
 */
typedef enum
{
    ETH_MAC_ADDRESSMASK_BYTE6 = 0x20000000,  /*!< Mask MAC Address high reg bits [15:8] */
    ETH_MAC_ADDRESSMASK_BYTE5 = 0x10000000,  /*!< Mask MAC Address high reg bits [7:0] */
    ETH_MAC_ADDRESSMASK_BYTE4 = 0x08000000,  /*!< Mask MAC Address low reg bits [31:24] */
    ETH_MAC_ADDRESSMASK_BYTE3 = 0x04000000,  /*!< Mask MAC Address low reg bits [23:16] */
    ETH_MAC_ADDRESSMASK_BYTE2 = 0x02000000,  /*!< Mask MAC Address low reg bits [15:8] */
    ETH_MAC_ADDRESSMASK_BYTE1 = 0x01000000   /*!< Mask MAC Address low reg bits [70] */
} ETH_MAC_ADDRESSMASK_T;

/**
 * @brief    DMA Tx descriptor flags
 */
typedef enum
{
    ETH_DMATXDESC_OWN      = (int)0x80000000,   /*!< Descriptor is owned by DMA engine */
    ETH_DMATXDESC_INTC     = 0x40000000,        /*!< Interrupt on completion */
    ETH_DMATXDESC_LS       = 0x20000000,        /*!< Last Segment */
    ETH_DMATXDESC_FS       = 0x10000000,        /*!< First Segment */
    ETH_DMATXDESC_DISC     = 0x08000000,        /*!< Disable CRC */
    ETH_DMATXDESC_DISP     = 0x04000000,        /*!< Disable Pad */
    ETH_DMATXDESC_TXTSEN   = 0x02000000,        /*!< Transmit Time Stamp Enable */
    ETH_DMATXDESC_TXENDR   = 0x00200000,        /*!< Transmit End of Ring */
    ETH_DMATXDESC_TXCH     = 0x00100000,        /*!< Second Address Chained */
    ETH_DMATXDESC_TXTSS    = 0x00020000,        /*!< Tx Time Stamp Status */
    ETH_DMATXDESC_IHERR    = 0x00010000,        /*!< IP Header Error */
    ETH_DMATXDESC_ERRS     = 0x00008000,        /*!< Error summary */
    ETH_DMATXDESC_JTO      = 0x00004000,        /*!< Jabber Timeout */
    ETH_DMATXDESC_FF       = 0x00002000,        /*!< Frame Flushed: DMA/MTL flushed the frame due to SW flush */
    ETH_DMATXDESC_IPERR    = 0x00001000,        /*!< Payload Checksum Error */
    ETH_DMATXDESC_LSC      = 0x00000800,        /*!< Loss of Carrier: carrier lost during transmission */
    ETH_DMATXDESC_NC       = 0x00000400,        /*!< No Carrier: no carrier signal from the transceiver */
    ETH_DMATXDESC_LC       = 0x00000200,        /*!< Late Collision: transmission aborted due to collision */
    ETH_DMATXDESC_EC       = 0x00000100,        /*!< Excessive Collision: transmission aborted after 16 collisions */
    ETH_DMATXDESC_VLANF    = 0x00000080,        /*!< VLAN Frame */
    ETH_DMATXDESC_CCNT     = 0x00000078,        /*!< Collision Count */
    ETH_DMATXDESC_EDEF     = 0x00000004,        /*!< Excessive Deferral */
    ETH_DMATXDESC_UFERR    = 0x00000002,        /*!< Underflow Error: late data arrival from the memory */
    ETH_DMATXDESC_DEF      = 0x00000001         /*!< Deferred Bit */
} ETH_DMATXDESC_FLAG_T;

/**
 * @brief    ETH DMA Tx descriptor segment
 */
typedef enum
{
    ETH_DMATXDESC_LASTSEGMENTS = BIT30, /*!< Actual Tx desc contain last segment */
    ETH_DMATXDESC_FIRSTSEGMENT = BIT29  /*!< Actual Tx desc contain first segment */
} ETH_DMATXDESC_SEGMENTS_T;

/**
 * @brief    ETH DMA Tx descriptor Checksum Insertion Control
 */
typedef enum
{
    ETH_DMATXDESC_CHECKSUMBYPASS,                       /*!< Checksum bypass */
    ETH_DMATXDESC_CHECKSUMIPV4HEADER = BIT22,           /*!< IPv4 header checksum */
    ETH_DMATXDESC_CHECKSUMTCPUDPICMPSEGMENT = BIT23,    /*!< TCP/UDP/ICMP checksum. Pseudo header
                                                            checksum is assumed to be present */
    ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL = BIT22 | BIT23  /*!< TCP/UDP/ICMP checksum fully in hardware
                                                            including pseudo header */
} ETH_DMATXDESC_CHECKSUMB_T;

/**
 * @brief    DMA Rx descriptor status
 */
typedef enum
{
    ETH_DMARXDESC_OWN      = (int)0x80000000U,  /*!< Descriptor is owned by DMA engine */
    ETH_DMARXDESC_ADDRF    =  0x40000000,       /*!< DA Filter Fail for the rx frame */
    ETH_DMARXDESC_ERRS     =  0x00008000,       /*!< Error summary */
    ETH_DMARXDESC_DESERR   =  0x00004000,       /*!< Descriptor error: no more descriptors for receive frame */
    ETH_DMARXDESC_SADDRF   =  0x00002000,       /*!< SA Filter Fail for the received frame */
    ETH_DMARXDESC_LERR     =  0x00001000,       /*!< Frame size not matching with length field */
    ETH_DMARXDESC_OFERR    =  0x00000800,       /*!< Overflow Error: Frame was damaged due to buffer overflow */
    ETH_DMARXDESC_VLANF    =  0x00000400,       /*!< VLAN Tag: received frame is a VLAN frame */
    ETH_DMARXDESC_FDES     =  0x00000200,       /*!< First descriptor of the frame */
    ETH_DMARXDESC_LDES     =  0x00000100,       /*!< Last descriptor of the frame */
    ETH_DMARXDESC_IPV4HCE  =  0x00000080,       /*!< IPC Checksum Error/Giant Frame: Rx Ipv4 header checksum error */
    ETH_DMARXDESC_LC       =  0x00000040,       /*!< Late collision occurred during reception */
    ETH_DMARXDESC_FT       =  0x00000020,       /*!< Frame type - Ethernet, otherwise 802.3 */
    ETH_DMARXDESC_RXWDTTO  =  0x00000010,       /*!< Receive Watchdog Timeout: watchdog timer expired during reception */
    ETH_DMARXDESC_RERR     =  0x00000008,       /*!< Receive error: error reported by MII interface */
    ETH_DMARXDESC_DERR     =  0x00000004,       /*!< Dribble bit error: frame contains non int multiple of 8 bits */
    ETH_DMARXDESC_CERR     =  0x00000002,       /*!< CRC error */
    ETH_DMARXDESC_MAMPCE   =  0x00000001        /*!< Rx MAC Address/Payload Checksum Error:
                                                    Rx MAC address matched/ Rx Payload Checksum Error */
} ETH_DMARXDESC_FLAG_T;

/**
 * @brief    DMA Rx descriptor extended flags
 */
typedef enum
{
    ETH_DMAPTPRXDESC_PTPV   =  0x00002000,  /*!< PTP version */
    ETH_DMAPTPRXDESC_PTPFT  =  0x00001000,  /*!< PTP frame type */
    ETH_DMAPTPRXDESC_PTPMT  =  0x00000F00,  /*!< PTP message type */
    ETH_DMAPTPRXDESC_IPV6P  =  0x00000080,  /*!< IPv6 packet received */
    ETH_DMAPTPRXDESC_IPV4P  =  0x00000040,  /*!< IPv4 packet received */
    ETH_DMAPTPRXDESC_IPCBP  =  0x00000020,  /*!< IP checksum bypassed */
    ETH_DMAPTPRXDESC_IPPERR =  0x00000010,  /*!< IP payload error */
    ETH_DMAPTPRXDESC_IPHERR =  0x00000008,  /*!< IP header error */
    ETH_DMAPTPRXDESC_IPPT   =  0x00000007   /*!< IP payload type */
} ETH_DMAPTPRXDESC_FLAG_T;

/**
 * @brief    ETH DMA Rx descriptor buffers
 */
typedef enum
{
    ETH_DMARXDESC_BUFFER1,  /*!< DMA Rx Desc Buffer1 */
    ETH_DMARXDESC_BUFFER2   /*!< DMA Rx Desc Buffer2 */
} ETH_DMARXDESC_BUFFER_T;

/**
 * @brief    ETH Drop TCP IP Checksum Error Frame
 */
typedef enum
{
    ETH_DROPTCPIPCHECKSUMERRORFRAME_ENABLE,     /*!< Enable dropping of TCP/IP checksum error frame */
    ETH_DROPTCPIPCHECKSUMERRORFRAME_DISABLE     /*!< Disable dropping of TCP/IP checksum error frame */
} ETH_DROPTCPIPCHECKSUMERRORFRAME_T;

/**
 * @brief    ETH Receive Store Forward
 */
typedef enum
{
    ETH_RECEIVESTOREFORWARD_DISABLE,    /*!< Disable receive store and forward */
    ETH_RECEIVESTOREFORWARD_ENABLE      /*!< Enable receive store and forward */
} ETH_RECEIVESTOREFORWARD_T;

/**
 * @brief    ETH Flush Received Frame
 */
typedef enum
{
    ETH_FLUSHRECEIVEDFRAME_ENABLE,  /*!< Enable flushing of received frames */
    ETH_FLUSHRECEIVEDFRAME_DISABLE  /*!< Disable flushing of received frames */
} ETH_FLUSHRECEIVEDFRAME_T;

/**
 * @brief    ETH Transmit Store Forward
 */
typedef enum
{
    ETH_TRANSMITSTOREFORWARD_DISABLE,   /*!< Disable transmit store and forward */
    ETH_TRANSMITSTOREFORWARD_ENABLE     /*!< Enable transmit store and forward */
} ETH_TRANSMITSTOREFORWARD_T;

/**
 * @brief    ETH Transmit Threshold Control
 */
typedef enum
{
    ETH_TRANSMITTHRESHOLDCONTROL_64BYTES,   /*!< Select 64 bytes transmit threshild level */
    ETH_TRANSMITTHRESHOLDCONTROL_128BYTES,  /*!< Select 128 bytes transmit threshild level */
    ETH_TRANSMITTHRESHOLDCONTROL_192BYTES,  /*!< Select 192 bytes transmit threshild level */
    ETH_TRANSMITTHRESHOLDCONTROL_256BYTES,  /*!< Select 256 bytes transmit threshild level */
    ETH_TRANSMITTHRESHOLDCONTROL_40BYTES,   /*!< Select 40 bytes transmit threshild level */
    ETH_TRANSMITTHRESHOLDCONTROL_32BYTES,   /*!< Select 32 bytes transmit threshild level */
    ETH_TRANSMITTHRESHOLDCONTROL_24BYTES,   /*!< Select 24 bytes transmit threshild level */
    ETH_TRANSMITTHRESHOLDCONTROL_16BYTES    /*!< Select 16 bytes transmit threshild level */
} ETH_TRANSMITTHRESHOLDCONTROL_T;

/**
 * @brief    ETH Forward Error Frames
 */
typedef enum
{
    ETH_FORWARDERRORFRAMES_DISABLE, /*!< Disable forward error frames */
    ETH_FORWARDERRORFRAMES_ENABLE   /*!< Enable forward error frames */
} ETH_FORWARDERRORFRAMES_T;

/**
 * @brief    ETH Forward Undersized Good Frames
 */
typedef enum
{
    ETH_FORWARDUNDERSIZEDGOODFRAMES_DISABLE,    /*!< Disable forward undersized good frames */
    ETH_FORWARDUNDERSIZEDGOODFRAMES_ENABLE      /*!< Enable forward undersized good frames */
} ETH_FORWARDUNDERSIZEDGOODFRAMES_T;

/**
 * @brief    ETH Receive Threshold Control
 */
typedef enum
{
    ETH_RECEIVEDTHRESHOLDCONTROL_64BYTES,   /*!< Select 64 bytes receive threshold level */
    ETH_RECEIVEDTHRESHOLDCONTROL_32BYTES,   /*!< Select 32 bytes receive threshold level */
    ETH_RECEIVEDTHRESHOLDCONTROL_96BYTES,   /*!< Select 96 bytes receive threshold level */
    ETH_RECEIVEDTHRESHOLDCONTROL_128BYTES   /*!< Select 128 bytes receive threshold level */
} ETH_RECEIVEDTHRESHOLDCONTROL_T;

/**
 * @brief    ETH Second Frame Operate
 */
typedef enum
{
    ETH_SECONDFRAMEOPERARTE_DISABLE,    /*!< Disable second frame operate */
    ETH_SECONDFRAMEOPERARTE_ENABLE      /*!< Enable second frame operate */
} ETH_SECONDFRAMEOPERARTE_T;

/**
 * @brief    ETH Address Aligned Beats
 */
typedef enum
{
    ETH_ADDRESSALIGNEDBEATS_DISABLE,    /*!< Disable address aligned beats */
    ETH_ADDRESSALIGNEDBEATS_ENABLE      /*!< Enable address aligned beats */
} ETH_ADDRESSALIGNEDBEATS_T;

/**
 * @brief    ETH Fixed Burst
 */
typedef enum
{
    ETH_FIXEDBURST_DISABLE, /*!< Disable fixed burst */
    ETH_FIXEDBURST_ENABLE   /*!< Enable fixed burst */
} ETH_FIXEDBURST_T;

/**
 * @brief    ETH Rx DMA Burst Length
 */
typedef enum
{
    ETH_RXDMABURSTLENGTH_1BEAT        = BIT17,          /*!< Maxnum number of Rx DMA transaction = 1 beat */
    ETH_RXDMABURSTLENGTH_2BEAT        = BIT18,          /*!< Maxnum number of Rx DMA transaction = 2 beat */
    ETH_RXDMABURSTLENGTH_4BEAT        = BIT19,          /*!< Maxnum number of Rx DMA transaction = 4 beat */
    ETH_RXDMABURSTLENGTH_8BEAT        = BIT20,          /*!< Maxnum number of Rx DMA transaction = 8 beat */
    ETH_RXDMABURSTLENGTH_16BEAT       = BIT21,          /*!< Maxnum number of Rx DMA transaction = 16 beat */
    ETH_RXDMABURSTLENGTH_32BEAT       = BIT22,          /*!< Maxnum number of Rx DMA transaction = 32 beat */
    ETH_RXDMABURSTLENGTH_4XPBL_4BEAT  = BIT17 | BIT24,  /*!< Maxnum number of Rx DMA transaction = 4 beat */
    ETH_RXDMABURSTLENGTH_4XPBL_8BEAT  = BIT18 | BIT24,  /*!< Maxnum number of Rx DMA transaction = 8 beat */
    ETH_RXDMABURSTLENGTH_4XPBL_16BEAT = BIT19 | BIT24,  /*!< Maxnum number of Rx DMA transaction = 16 beat */
    ETH_RXDMABURSTLENGTH_4XPBL_32BEAT = BIT20 | BIT24,  /*!< Maxnum number of Rx DMA transaction = 32 beat */
    ETH_RXDMABURSTLENGTH_4XPBL_64BEAT = BIT21 | BIT24,  /*!< Maxnum number of Rx DMA transaction = 64 beat */
    ETH_RXDMABURSTLENGTH_4XPBL_128BEAT = BIT22 | BIT24  /*!< Maxnum number of Rx DMA transaction = 128 beat */
} ETH_RXDMABURSTLENGTH_T;

/**
 * @brief    ETH Tx DMA Burst Length
 */
typedef enum
{
    ETH_TXDMABURSTLENGTH_1BEAT        = BIT8,           /*!< Maxnum number of Tx DMA transaction = 1 beat */
    ETH_TXDMABURSTLENGTH_2BEAT        = BIT9,           /*!< Maxnum number of Tx DMA transaction = 2 beat */
    ETH_TXDMABURSTLENGTH_4BEAT        = BIT10,          /*!< Maxnum number of Tx DMA transaction = 4 beat */
    ETH_TXDMABURSTLENGTH_8BEAT        = BIT11,          /*!< Maxnum number of Tx DMA transaction = 8 beat */
    ETH_TXDMABURSTLENGTH_16BEAT       = BIT12,          /*!< Maxnum number of Tx DMA transaction = 16 beat */
    ETH_TXDMABURSTLENGTH_32BEAT       = BIT13,          /*!< Maxnum number of Tx DMA transaction = 32 beat */
    ETH_TXDMABURSTLENGTH_4XPBL_4BEAT  = BIT8 | BIT24,   /*!< Maxnum number of Tx DMA transaction = 4 beat */
    ETH_TXDMABURSTLENGTH_4XPBL_8BEAT  = BIT9 | BIT24,   /*!< Maxnum number of Tx DMA transaction = 8 beat */
    ETH_TXDMABURSTLENGTH_4XPBL_16BEAT = BIT10 | BIT24,  /*!< Maxnum number of Tx DMA transaction = 16 beat */
    ETH_TXDMABURSTLENGTH_4XPBL_32BEAT = BIT11 | BIT24,  /*!< Maxnum number of Tx DMA transaction = 32 beat */
    ETH_TXDMABURSTLENGTH_4XPBL_64BEAT = BIT12 | BIT24,  /*!< Maxnum number of Tx DMA transaction = 64 beat */
    ETH_TXDMABURSTLENGTH_4XPBL_128BEAT = BIT13 | BIT24  /*!< Maxnum number of Tx DMA transaction = 128 beat */
} ETH_TXDMABURSTLENGTH_T;

/**
 * @brief    ETH DMA Arbitration
 */
typedef enum
{
    ETH_DMAARBITRATION_ROUNDROBIN_RXTX_1_1,                 /*!< Priority ratio RX : TX = 1 : 1 */
    ETH_DMAARBITRATION_ROUNDROBIN_RXTX_2_1 = BIT14,         /*!< Priority ratio RX : TX = 2 : 1 */
    ETH_DMAARBITRATION_ROUNDROBIN_RXTX_3_1 = BIT15,         /*!< Priority ratio RX : TX = 3 : 1 */
    ETH_DMAARBITRATION_ROUNDROBIN_RXTX_4_1 = BIT14 | BIT15, /*!< Priority ratio RX : TX = 4 : 1 */
    ETH_DMAARBITRATION_RXPRIORTX = BIT1                     /*!< Rx priority ratio higher than Tx */
} ETH_DMAARBITRATION_T;

/**
 * @brief    ETH DMA Flags
 */
typedef enum
{
    ETH_DMA_FLAG_TST               = 0x20000000,   /*!< Time-stamp trigger interrupt (on DMA) */
    ETH_DMA_FLAG_PMT               = 0x10000000,   /*!< PMT interrupt (on DMA) */
    ETH_DMA_FLAG_MMC               = 0x08000000,   /*!< MMC interrupt (on DMA) */
    ETH_DMA_FLAG_DATATRANSFERERROR = 0x00800000,   /*!< Error bits 0-Rx DMA, 1-Tx DMA */
    ETH_DMA_FLAG_READWRITEERROR    = 0x01000000,   /*!< Error bits 0-write transfer, 1-read transfer */
    ETH_DMA_FLAG_ACCESSERROR       = 0x02000000,   /*!< Error bits 0-data buffer, 1-desc. access */
    ETH_DMA_FLAG_NIS               = 0x00010000,   /*!< Normal interrupt summary flag */
    ETH_DMA_FLAG_AIS               = 0x00008000,   /*!< Abnormal interrupt summary flag */
    ETH_DMA_FLAG_ER                = 0x00004000,   /*!< Early receive flag */
    ETH_DMA_FLAG_FBE               = 0x00002000,   /*!< Fatal bus error flag */
    ETH_DMA_FLAG_ET                = 0x00000400,   /*!< Early transmit flag */
    ETH_DMA_FLAG_RWT               = 0x00000200,   /*!< Receive watchdog timeout flag */
    ETH_DMA_FLAG_RPS               = 0x00000100,   /*!< Receive process stopped flag */
    ETH_DMA_FLAG_RBU               = 0x00000080,   /*!< Receive buffer unavailable flag */
    ETH_DMA_FLAG_RX                = 0x00000040,   /*!< Receive flag */
    ETH_DMA_FLAG_TU                = 0x00000020,   /*!< Underflow flag */
    ETH_DMA_FLAG_RO                = 0x00000010,   /*!< Overflow flag */
    ETH_DMA_FLAG_TJT               = 0x00000008,   /*!< Transmit jabber timeout flag */
    ETH_DMA_FLAG_TBU               = 0x00000004,   /*!< Transmit buffer unavailable flag */
    ETH_DMA_FLAG_TPS               = 0x00000002,   /*!< Transmit process stopped flag */
    ETH_DMA_FLAG_TX                = 0x00000001    /*!< Transmit flag */
} ETH_DMA_FLAG_T;

/**
 * @brief    ETH DMA Interrupts
 */
typedef enum
{
    ETH_DMA_INT_TST   =   0x20000000,   /*!< Time-stamp trigger interrupt (on DMA) */
    ETH_DMA_INT_PMT   =   0x10000000,   /*!< PMT interrupt (on DMA) */
    ETH_DMA_INT_MMC   =   0x08000000,   /*!< MMC interrupt (on DMA) */
    ETH_DMA_INT_NIS   =   0x00010000,   /*!< Normal interrupt summary */
    ETH_DMA_INT_AIS   =   0x00008000,   /*!< Abnormal interrupt summary */
    ETH_DMA_INT_ER    =   0x00004000,   /*!< Early receive interrupt */
    ETH_DMA_INT_FBE   =   0x00002000,   /*!< Fatal bus error interrupt */
    ETH_DMA_INT_ET    =   0x00000400,   /*!< Early transmit interrupt */
    ETH_DMA_INT_RWT   =   0x00000200,   /*!< Receive watchdog timeout interrupt */
    ETH_DMA_INT_RPS   =   0x00000100,   /*!< Receive process stopped interrupt */
    ETH_DMA_INT_RBU   =   0x00000080,   /*!< Receive buffer unavailable interrupt */
    ETH_DMA_INT_RX    =   0x00000040,   /*!< Receive interrupt */
    ETH_DMA_INT_TU    =   0x00000020,   /*!< Underflow interrupt */
    ETH_DMA_INT_RO    =   0x00000010,   /*!< Overflow interrupt */
    ETH_DMA_INT_TJT   =   0x00000008,   /*!< Transmit jabber timeout interrupt */
    ETH_DMA_INT_TBU   =   0x00000004,   /*!< Transmit buffer unavailable interrupt */
    ETH_DMA_INT_TPS   =   0x00000002,   /*!< Transmit process stopped interrupt */
    ETH_DMA_INT_TX    =   0x00000001    /*!< Transmit interrupt */
} ETH_DMA_INT_T;

/**
 * @brief    ETH DMA transmit process state
 */
typedef enum
{
    ETH_DMA_TRANSMITPROCESS_STOPPED,            /*!< Stopped - Reset or Stop Tx Command issued */
    ETH_DMA_TRANSMITPROCESS_FETCHING,           /*!< Running - fetching the Tx descriptor */
    ETH_DMA_TRANSMITPROCESS_WAITING,            /*!< Running - waiting for status */
    ETH_DMA_TRANSMITPROCESS_READING,            /*!< Running - reading the data from host memory */
    ETH_DMA_TRANSMITPROCESS_SUSPENDED = 0x06,   /*!< Suspended - Tx Descriptor unavailable */
    ETH_DMA_TRANSMITPROCESS_CLOSING = 0x07,     /*!< Running - closing Rx descriptor */
} ETH_DMA_TRANSMITPROCESS_T;

/**
 * @brief    ETH DMA receive process state
 */
typedef enum
{
    ETH_DMA_RECEIVEPROCESS_STOPPED,             /*!< Stopped - Reset or Stop Rx Command issued */
    ETH_DMA_RECEIVEPROCESS_FETCHING  = 0x02,    /*!< Running - fetching the Rx descriptor */
    ETH_DMA_RECEIVEPROCESS_WAITING   = 0x06,    /*!< Running - waiting for packet */
    ETH_DMA_RECEIVEPROCESS_SUSPENDED = 0x08,    /*!< Suspended - Rx Descriptor unavailable */
    ETH_DMA_RECEIVEPROCESS_CLOSING   = 0x0A,    /*!< Running - closing descriptor */
    ETH_DMA_RECEIVEPROCESS_QUEUING   = 0x0E     /*!< Running - queuing the receive frame into host memory */
} ETH_DMA_RECEIVEPROCESS_T;

/**
 * @brief    ETH DMA overflow
 */
typedef enum
{
    ETH_DMA_OVERFLOW_RXFIFOCOUNTER = BIT28,     /*!< Overflow for FIFO Overflows Counter */
    ETH_DMA_OVERFLOW_MISSEDFRAMECOUNTER = BIT16 /*!< Overflow for Buffer Unavailable Missed Frame Counter */
} ETH_DMA_OVERFLOW_T;

/**
 * @brief    ETH PMT Flags
 */
typedef enum
{
    ETH_PMT_FLAG_WUFFRPR = (int)BIT31,  /*!< Wake-Up Frame Filter Register Pointer Reset */
    ETH_PMT_FLAG_WUFR = BIT6,           /*!< Wake-Up Frame Received */
    ETH_PMT_FLAG_MPR = BIT5             /*!< Magic Packet Received */
} ETH_PMT_FLAG_T;

/**
 * @brief    ETH MMC Tx/RX Interrupts
 */
typedef enum
{
    ETH_MMC_INT_TGF    = BIT21,         /*!< When Tx good frame counter reaches half the maximum value */
    ETH_MMC_INT_TGFMSC = BIT15,         /*!< When Tx good multi col counter reaches half the maximum value */
    ETH_MMC_INT_TGFSC  = BIT14,         /*!< When Tx good single col counter reaches half the maximum value */
    ETH_MMC_INT_RGUF   = BIT21 | BIT30, /*!< When Rx good unicast frames counter reaches half the maximum value */
    ETH_MMC_INT_RFAE   = BIT6 | BIT30,  /*!< When Rx alignment error counter reaches half the maximum value */
    ETH_MMC_INT_RFCE   = BIT5 | BIT30   /*!< When Rx crc error counter reaches half the maximum value */
} ETH_MMC_INT_T;

/**
 * @brief    ETH MMC Registers
 */
typedef enum
{
    ETH_MMC_CTRL       =  0x00000100,   /*!< MMC CTRL register */
    ETH_MMC_RXINT      =  0x00000104,   /*!< MMC RXINT register */
    ETH_MMC_TXINT      =  0x00000108,   /*!< MMC TXINT register */
    ETH_MMC_RXINTMASK  =  0x0000010C,   /*!< MMC RXINTMASK register */
    ETH_MMC_TXINTMASK  =  0x00000110,   /*!< MMC TXINTMASK register */
    ETH_MMC_TXGFSCCNT  =  0x0000014C,   /*!< MMC TXGFSCCNT register */
    ETH_MMC_TXGFMCCNT  =  0x00000150,   /*!< MMC TXGFMCCNT register */
    ETH_MMC_TXGFCNT    =  0x00000168,   /*!< MMC TXGFCNT register */
    ETH_MMC_RXFCECNT   =  0x00000194,   /*!< MMC RXFCECNT register */
    ETH_MMC_RXFAECNT   =  0x00000198,   /*!< MMC RXFAECNT register */
    ETH_MMC_RXGUNCNT   =  0x000001C4    /*!< MMC RXGUNCNT register */
} ETH_MMC_REG_T;

/**@} end of group ETH_Enumerations*/


/** @defgroup ETH_DMA_TX_Descriptor ETH DMA TX Descriptor
  * @{
  */

/**
*  DMA Tx Descriptor
*  -----------------------------------------------------------------------------------------------
*  TXDES0 | OWN(31) | CTRL[30:25] | Reserved(24) | CTRL[23:20] | Reserved[19:18] | Status[17:0]   |
*  -----------------------------------------------------------------------------------------------
*  TXDES1 | Reserved[31:29] | Buffer2 Size[28:16] | Reserved[15:13] | Buffer1 Size[12:0]          |
*  -----------------------------------------------------------------------------------------------
*  TXDES2 |                         Buffer1 Address [31:0]                                        |
*  -----------------------------------------------------------------------------------------------
*  TXDES3 |                   Buffer2 Address [31:0] / Next Descriptor Address [31:0]             |
*  -----------------------------------------------------------------------------------------------
*/

/**
  * @brief  Bit definition of TXDES0 register: DMA Tx descriptor status register
  */
#define ETH_DMATXDESC_OWN                     0x80000000U   /*!< OWN bit: descriptor is owned by DMA engine */
#define ETH_DMATXDESC_INTC                    0x40000000U   /*!< Interrupt on Completion */
#define ETH_DMATXDESC_LS                      0x20000000U   /*!< Last Segment */
#define ETH_DMATXDESC_FS                      0x10000000U   /*!< First Segment */
#define ETH_DMATXDESC_DISC                    0x08000000U   /*!< Disable CRC */
#define ETH_DMATXDESC_DISP                    0x04000000U   /*!< Disable Padding */
#define ETH_DMATXDESC_TXTSEN                  0x02000000U   /*!< Transmit Time Stamp Enable */
#define ETH_DMATXDESC_CIC                     0x00C00000U   /*!< Checksum Insertion Control: 4 cases */
#define ETH_DMATXDESC_CIC_BYPASS              0x00000000U   /*!< Do Nothing: Checksum Engine is bypassed */
#define ETH_DMATXDESC_CIC_IPV4HEADER          0x00400000U   /*!< IPV4 header Checksum Insertion */
#define ETH_DMATXDESC_CIC_TCPUDPICMP_SEGMENT  0x00800000U   /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define ETH_DMATXDESC_CIC_TCPUDPICMP_FULL     0x00C00000U   /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */
#define ETH_DMATXDESC_TXENDR                  0x00200000U   /*!< Transmit End of Ring */
#define ETH_DMATXDESC_TXCH                    0x00100000U   /*!< Second Address Chained */
#define ETH_DMATXDESC_TXTSS                   0x00020000U   /*!< Tx Time Stamp Status */
#define ETH_DMATXDESC_IHERR                   0x00010000U   /*!< IP Header Error */
#define ETH_DMATXDESC_ERRS                    0x00008000U   /*!< Error summary: OR of the following bits: UFERR || EDEF || EC || LC || NC || LSC || FF || JTO */
#define ETH_DMATXDESC_JTO                     0x00004000U   /*!< Jabber Timeout */
#define ETH_DMATXDESC_FF                      0x00002000U   /*!< Frame Flushed: DMA/MTL flushed the frame due to SW flush */
#define ETH_DMATXDESC_IPERR                   0x00001000U   /*!< Payload Checksum Error */
#define ETH_DMATXDESC_LSC                     0x00000800U   /*!< Loss of Carrier: carrier lost during transmission */
#define ETH_DMATXDESC_NC                      0x00000400U   /*!< No Carrier: no carrier signal from the transceiver */
#define ETH_DMATXDESC_LC                      0x00000200U   /*!< Late Collision: transmission aborted due to collision */
#define ETH_DMATXDESC_EC                      0x00000100U   /*!< Excessive Collision: transmission aborted after 16 collisions */
#define ETH_DMATXDESC_VLANF                   0x00000080U   /*!< VLAN Frame */
#define ETH_DMATXDESC_CCNT                    0x00000078U   /*!< Collision Count */
#define ETH_DMATXDESC_EDEF                    0x00000004U   /*!< Excessive Deferral */
#define ETH_DMATXDESC_UFERR                   0x00000002U   /*!< Underflow Error: late data arrival from the memory */
#define ETH_DMATXDESC_DEF                     0x00000001U   /*!< Deferred Bit */

/**
  * @brief  Bit definition of TXDES1 register
  */
#define ETH_DMATXDESC_TXBS2  0x1FFF0000U /*!< Transmit Buffer2 Size */
#define ETH_DMATXDESC_TXBS1  0x00001FFFU /*!< Transmit Buffer1 Size */

/**
  * @brief  Bit definition of TXDES2 register
  */
#define ETH_DMATXDESC_B1AP  0xFFFFFFFFU /*!< Buffer1 Address Pointer */

/**
  * @brief  Bit definition of TXDES3 register
  */
#define ETH_DMATXDESC_B2AP  0xFFFFFFFFU /*!< Buffer2 Address Pointer */

/**
*  ---------------------------------------------------------------------------------------------
*  TXDES6 |                         Transmit Time Stamp Low [31:0]                               |
*  ---------------------------------------------------------------------------------------------
*  TXDES7 |                         Transmit Time Stamp High [31:0]                              |
*  ----------------------------------------------------------------------------------------------
*/

/* Bit definition of TXDES6 register */
#define ETH_DMAPTPTXDESC_TXTSL  0xFFFFFFFFU  /*!< Transmit Time Stamp Low */

/* Bit definition of TXDES7 register */
#define ETH_DMAPTPTXDESC_TXTSH  0xFFFFFFFFU  /*!< Transmit Time Stamp High */

/**
  * @}
  */
/** @defgroup ETH_DMA_RX_Descriptor ETH DMA RX Descriptor
  * @{
  */

/**
  *DMA Rx Descriptor
  *--------------------------------------------------------------------------------------------------------------------
  *RXDES0 | OWN(31) |                                             Status [30:0]                                         |
  *---------------------------------------------------------------------------------------------------------------------
  *RXDES1 | CTRL(31) | Reserved[30:29] | Buffer2 Size[28:16] | CTRL[15:14] | Reserved(13) | Buffer1 Size[12:0]          |
  *---------------------------------------------------------------------------------------------------------------------
  *RXDES2 |                                       Buffer1 Address [31:0]                                                |
  *---------------------------------------------------------------------------------------------------------------------
  *RXDES3 |                          Buffer2 Address [31:0] / Next Descriptor Address [31:0]                            |
  *---------------------------------------------------------------------------------------------------------------------
*/

/**
  * @brief  Bit definition of RXDES0 register: DMA Rx descriptor status register
  */
#define ETH_DMARXDESC_OWN         0x80000000U   /*!< OWN bit: descriptor is owned by DMA engine */
#define ETH_DMARXDESC_ADDRF       0x40000000U   /*!< DA Filter Fail for the rx frame */
#define ETH_DMARXDESC_FL          0x3FFF0000U   /*!< Receive descriptor frame length */
#define ETH_DMARXDESC_ERRS        0x00008000U   /*!< Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE */
#define ETH_DMARXDESC_DESERR      0x00004000U   /*!< Descriptor error: no more descriptors for receive frame */
#define ETH_DMARXDESC_SADDRF      0x00002000U   /*!< SA Filter Fail for the received frame */
#define ETH_DMARXDESC_LERR        0x00001000U   /*!< Frame size not matching with length field */
#define ETH_DMARXDESC_OFERR       0x00000800U   /*!< Overflow Error: Frame was damaged due to buffer overflow */
#define ETH_DMARXDESC_VLANF       0x00000400U   /*!< VLAN Tag: received frame is a VLAN frame */
#define ETH_DMARXDESC_FDES        0x00000200U   /*!< First descriptor of the frame */
#define ETH_DMARXDESC_LDES        0x00000100U   /*!< Last descriptor of the frame */
#define ETH_DMARXDESC_IPV4HCE     0x00000080U   /*!< IPC Checksum Error: Rx Ipv4 header checksum error */
#define ETH_DMARXDESC_LC          0x00000040U   /*!< Late collision occurred during reception */
#define ETH_DMARXDESC_FT          0x00000020U   /*!< Frame type - Ethernet, otherwise 802.3 */
#define ETH_DMARXDESC_RXWWTTO     0x00000010U   /*!< Receive Watchdog Timeout: watchdog timer expired during reception */
#define ETH_DMARXDESC_RERR        0x00000008U   /*!< Receive error: error reported by MII interface */
#define ETH_DMARXDESC_DERR        0x00000004U   /*!< Dribble bit error: frame contains non int multiple of 8 bits */
#define ETH_DMARXDESC_CERR        0x00000002U   /*!< CRC error */
#define ETH_DMARXDESC_MAMPCE      0x00000001U   /*!< Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error */

/**
  * @brief  Bit definition of RXDES1 register
  */
#define ETH_DMARXDESC_DINTC  0x80000000U /*!< Disable Interrupt on Completion */
#define ETH_DMARXDESC_RXBS2  0x1FFF0000U /*!< Receive Buffer2 Size */
#define ETH_DMARXDESC_RXER   0x00008000U /*!< Receive End of Ring */
#define ETH_DMARXDESC_RXCH   0x00004000U /*!< Second Address Chained */
#define ETH_DMARXDESC_RXBS1  0x00001FFFU /*!< Receive Buffer1 Size */

/**
  * @brief  Bit definition of RXDES2 register
  */
#define ETH_DMARXDESC_B1AP  0xFFFFFFFFU /*!< Buffer1 Address Pointer */

/**
  * @brief  Bit definition of RXDES3 register
  */
#define ETH_DMARXDESC_B2AP  0xFFFFFFFFU /*!< Buffer2 Address Pointer */

/**
  *---------------------------------------------------------------------------------------------------------------------
  *RXDES4 |                   Reserved[31:14]              |             Extended Status [13:0]                         |
  *---------------------------------------------------------------------------------------------------------------------
  *RXDES5 |                                            Reserved[31:0]                                                   |
  *---------------------------------------------------------------------------------------------------------------------
  *RXDES6 |                                       Receive Time Stamp Low [31:0]                                         |
  *---------------------------------------------------------------------------------------------------------------------
  *RXDES7 |                                       Receive Time Stamp High [31:0]                                        |
  *---------------------------------------------------------------------------------------------------------------------
*/

/* Bit definition of RXDES4 register */
#define ETH_DMAPTPRXDESC_PTPV     0x00002000U                           /*!< PTP Version */
#define ETH_DMAPTPRXDESC_PTPFT    0x00001000U                           /*!< PTP Frame Type */
#define ETH_DMAPTPRXDESC_PTPMT    0x00000F00U                           /*!< PTP Message Type */
#define ETH_DMAPTPRXDESC_PTPMT_SYNC                      0x00000100U    /*!< SYNC message (all clock types) */
#define ETH_DMAPTPRXDESC_PTPMT_FOLLOWUP                  0x00000200U    /*!< FollowUp message (all clock types) */
#define ETH_DMAPTPRXDESC_PTPMT_DELAYREQ                  0x00000300U    /*!< DelayReq message (all clock types) */
#define ETH_DMAPTPRXDESC_PTPMT_DELAYRESP                 0x00000400U    /*!< DelayResp message (all clock types) */
#define ETH_DMAPTPRXDESC_PTPMT_PDELAYREQ_ANNOUNCE        0x00000500U    /*!< PdelayReq message (peer-to-peer transparent clock) or Announce message (Ordinary or Boundary clock) */
#define ETH_DMAPTPRXDESC_PTPMT_PDELAYRESP_MANAG          0x00000600U    /*!< PdelayResp message (peer-to-peer transparent clock) or Management message (Ordinary or Boundary clock) */
#define ETH_DMAPTPRXDESC_PTPMT_PDELAYRESPFOLLOWUP_SIGNAL 0x00000700U    /*!< PdelayRespFollowUp message (peer-to-peer transparent clock) or Signaling message (Ordinary or Boundary clock) */
#define ETH_DMAPTPRXDESC_IPV6P    0x00000080U                           /*!< IPv6 Packet Received */
#define ETH_DMAPTPRXDESC_IPV4P    0x00000040U                           /*!< IPv4 Packet Received */
#define ETH_DMAPTPRXDESC_IPCBP    0x00000020U                           /*!< IP Checksum Bypassed */
#define ETH_DMAPTPRXDESC_IPPERR   0x00000010U                           /*!< IP Payload Error */
#define ETH_DMAPTPRXDESC_IPHERR   0x00000008U                           /*!< IP Header Error */
#define ETH_DMAPTPRXDESC_IPPT     0x00000007U                           /*!< IP Payload Type */
#define ETH_DMAPTPRXDESC_IPPT_UDP                 0x00000001U           /*!< UDP payload encapsulated in the IP datagram */
#define ETH_DMAPTPRXDESC_IPPT_TCP                 0x00000002U           /*!< TCP payload encapsulated in the IP datagram */
#define ETH_DMAPTPRXDESC_IPPT_ICMP                0x00000003U           /*!< ICMP payload encapsulated in the IP datagram */

/* Bit definition of RXDES6 register */
#define ETH_DMAPTPRXDESC_RXTSL  0xFFFFFFFFU  /*!< Receive Time Stamp Low */

/* Bit definition of RXDES7 register */
#define ETH_DMAPTPRXDESC_RXTSH  0xFFFFFFFFU  /*!< Receive Time Stamp High */
/**
  * @}
  */


/** @addtogroup ETH_Macros Macros
  *@{
  */

/* ETH Frames defines */

/* Definition of the Ethernet driver buffers size and count */
#define ETH_RX_BUF_SIZE                ETH_MAX_PACKET_SIZE  /*!< buffer size for receive */
#define ETH_TX_BUF_SIZE                ETH_MAX_PACKET_SIZE  /*!< buffer size for transmit */
#define ETH_RXBUFNB                    (5U)                /*!< 5 Rx buffers of size ETH_RX_BUF_SIZE */
#define ETH_TXBUFNB                    (5U)                /*!< 5 Tx buffers of size ETH_TX_BUF_SIZE */

/* ETH_Buffers_setting ETH Buffers setting */
#define ETH_MAX_PACKET_SIZE       1524U /*!< ETH_HEADER + ETH_EXTRA + ETH_VLAN_TAG + ETH_MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_HEADER                14U   /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC                   4U    /*!< Ethernet CRC */
#define ETH_EXTRA                 2U    /*!< Extra bytes in some cases */
#define ETH_VLAN_TAG              4U    /*!< optional 802.1q VLAN Tag */
#define ETH_MIN_ETH_PAYLOAD       46U   /*!< Minimum Ethernet payload size */
#define ETH_MAX_ETH_PAYLOAD       1500U /*!< Maximum Ethernet payload size */
#define ETH_JUMBO_FRAME_PAYLOAD   9000U /*!< Jumbo frame payload size */

/**
*  Ethernet driver receive buffers are organized in a chained linked-list, when
*  an ethernet packet is received, the Rx-DMA will transfer the packet from RxFIFO
*  to the driver receive buffers memory.
*
*  Depending on the size of the received ethernet packet and the size of
*  each ethernet driver receive buffer, the received packet can take one or more
*  ethernet driver receive buffer.
*
*  In below are defined the size of one ethernet driver receive buffer ETH_RX_BUF_SIZE
*  and the total count of the driver receive buffers ETH_RXBUFNB.
*
*  The configured value for ETH_RX_BUF_SIZE and ETH_RXBUFNB are only provided as
*  example, they can be reconfigured in the application layer to fit the application
*  needs
*/

/** Here we configure each Ethernet driver receive buffer to fit the Max size Ethernet
*   packet
*/
#ifndef ETH_RX_BUF_SIZE
#define ETH_RX_BUF_SIZE         ETH_MAX_PACKET_SIZE
#endif

/* 5 Ethernet driver receive buffers are used (in a chained linked list)*/
#ifndef ETH_RXBUFNB
#define ETH_RXBUFNB             5U  /*!< 5 Rx buffers of size ETH_RX_BUF_SIZE */
#endif

/**
*  Ethernet driver transmit buffers are organized in a chained linked-list, when
*  an ethernet packet is transmitted, Tx-DMA will transfer the packet from the
*  driver transmit buffers memory to the TxFIFO.
*
*  Depending on the size of the Ethernet packet to be transmitted and the size of
*  each ethernet driver transmit buffer, the packet to be transmitted can take
*  one or more ethernet driver transmit buffer.
*
*  In below are defined the size of one ethernet driver transmit buffer ETH_TX_BUF_SIZE
*  and the total count of the driver transmit buffers ETH_TXBUFNB.
*
*  The configured value for ETH_TX_BUF_SIZE and ETH_TXBUFNB are only provided as
*  example, they can be reconfigured in the application layer to fit the application
*  needs
*/

/** Here we configure each Ethernet driver transmit buffer to fit the Max size Ethernet
*   packet
*/
#ifndef ETH_TX_BUF_SIZE
#define ETH_TX_BUF_SIZE         ETH_MAX_PACKET_SIZE
#endif

/* 5 ethernet driver transmit buffers are used (in a chained linked list)*/
#ifndef ETH_TXBUFNB
#define ETH_TXBUFNB             5U  /*!< 5  Tx buffers of size ETH_TX_BUF_SIZE */
#endif

/* ETHERNET MAC address offsets */
#define ETH_MAC_ADDR_HBASE   (ETH_MAC_BASE + 0x40)      /*!< ETHERNET MAC address high offset */
#define ETH_MAC_ADDR_LBASE    (ETH_MAC_BASE + 0x44)     /*!< ETHERNET MAC address low offset */

/* ETHERNET Errors */
#define  ETH_SUCCESS            1U
#define  ETH_ERROR              0U

/* ETHERNET DMA Tx descriptors Collision Count Shift */
#define  ETH_DMATXDESC_COLLISION_COUNTSHIFT        3U

/* ETHERNET DMA Tx descriptors Buffer2 Size Shift */
#define  ETH_DMATXDESC_BUFFER2_SIZESHIFT           16U

/* ETHERNET DMA Rx descriptors Frame Length Shift */
#define  ETH_DMARXDESC_FRAME_LENGTHSHIFT           16U

/* ETHERNET DMA Rx descriptors Buffer2 Size Shift */
#define  ETH_DMARXDESC_BUFFER2_SIZESHIFT           16U

/* ETHERNET DMA Rx descriptors Frame length Shift */
#define  ETH_DMARXDESC_FRAMELENGTHSHIFT            16U

/* ETHERNET MACMIIAR register Mask */
#define ETH_MACMIIAR_CR_MASK    0xFFFFFFE3U

/* ETHERNET MACCR register Mask */
#define ETH_MACCR_CLEAR_MASK    0xFF20010FU

/* ETHERNET MACFCR register Mask */
#define ETH_MACFCR_CLEAR_MASK   0x0000FF41U

/* ETHERNET DMAOMR register Mask */
#define ETH_DMAOMR_CLEAR_MASK   0xF8DE3F23U

/* ETHERNET Remote Wake-up frame register length */
#define ETH_WAKEUP_REGISTER_LENGTH      8U

/* ETHERNET Missed frames counter Shift */
#define  ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT     17U

/* PHY registers defines */

/* PHY Read write Timeouts */
#define PHY_READ_TIMEOUT                ((uint32_t)0x0004FFFF)
#define PHY_WRITE_TIMEOUT               ((uint32_t)0x0004FFFF)

/* PHY Register address */
#define PHY_BCR                                      0         /*!< Transceiver Basic Control Register */
#define PHY_BSR                                      1         /*!< Transceiver Basic Status Register */
#define PHY_SR                                       16        /*!< Transceiver Status Register for dp83848 */

/* PHY Status Register (PHYSTS), address 0x10 */
#define PHY_DUPLEX_STATUS               ((uint16_t)0x0004)     /*!< for dp83848 ((uint16_t)0x0010) */
#define PHY_SPEED_STATUS                ((uint16_t)0x0002)     /*!< for dp83848 ((uint16_t)0x0004) */

/* PHY basic status register */
#define PHY_AUTONEGO_COMPLETE           ((uint16_t)0x0020)     /*!< Auto-Negotiation process completed */
#define PHY_LINKED_STATUS               ((uint16_t)0x0004)     /*!< Valid link established */
#define PHY_JABBER_DETECTION            ((uint16_t)0x0002)     /*!< Jabber condition detected */

/* PHY basic Control register */
#define PHY_RESET                       ((uint16_t)0x8000)     /*!< PHY Reset */
#define PHY_LOOPBACK                    ((uint16_t)0x4000)     /*!< Select loop-back mode */
#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100)     /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000)     /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100)     /*!< Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000)     /*!< Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGOTIATION             ((uint16_t)0x1000)     /*!< Enable auto-negotiation function */
#define PHY_RESTAET_AUTONEGOTIATION     ((uint16_t)0x0200)     /*!< Restart auto-negotiation function */
#define PHY_POWERDOWN                   ((uint16_t)0x0800)     /*!< Select the power down mode */
#define PHY_ISOLATE                     ((uint16_t)0x0400)     /*!< Isolate PHY from MII */

/* PHY Delay */
#define PHY_RESET_DELAY                 ((uint32_t)0x000FFFFF) /*!< PHY reset delay */
#define PHY_CONFIG_DELAY                ((uint32_t)0x00FFFFFF) /*!< PHY configuration delay */
/* Delay to wait when writing to some Ethernet registers */
#define ETH_REG_WRITE_DELAY             ((uint32_t)0x0000FFFF)

/* Ethernet MAC MII Address Clock Range*/
#define ETH_MACMIIAR_CR_DIV42   ((uint8_t)0x00)                 /*!< HCLK:60-100 MHz; MDC clock = HCLK/42 */
#define ETH_MACMIIAR_CR_DIV62   ((uint8_t)0x01)                 /*!< HCLK:100-150 MHz; MDC clock = HCLK/62 */
#define ETH_MACMIIAR_CR_DIV16   ((uint8_t)0x02)                 /*!< HCLK:20-35 MHz; MDC clock = HCLK/16 */
#define ETH_MACMIIAR_CR_DIV26   ((uint8_t)0x03)                 /*!< HCLK:35-60 MHz; MDC clock = HCLK/26 */
#define ETH_MACMIIAR_CR_DIV102  ((uint8_t)0x04)                 /*!< HCLK:150-168 MHz; MDC clock = HCLK/102 */

/**@} end of group ETH_Macros */


/** @addtogroup ETH_Structure Data Structure
  @{
*/

/**
 * @brief    ETH MAC Config structure types
 */
typedef struct
{
    /* MAC Configuration */
    ETH_AUTONEGOTIATION_T           autoNegotiation;            /*!< Selects or not the AutoNegotiation mode for the external PHY
                                                                    The AutoNegotiation allows an automatic setting of the Speed (10/100Mbps)
                                                                    and the mode (half/full-duplex) */

    ETH_WATCHDOG_T                  watchDog;                   /*!< Selects or not the Watchdog timer
                                                                    When enabled, the MAC allows no more then 2048 bytes to be received.
                                                                    When disabled, the MAC can receive up to 16384 bytes. */

    ETH_JABBER_T                    jabber;                     /*!< Selects or not Jabber timer
                                                                    When enabled, the MAC allows no more then 2048 bytes to be sent.
                                                                    When disabled, the MAC can send up to 16384 bytes. */
    ETH_INTERFRAMEGAP_T             interFrameGap;              /*!< Selects the minimum IFG between frames during transmission */

    ETH_CARRIERSENCE_T              carrierSense;               /*!< Selects or not the Carrier Sense */

    ETH_SPEED_T                     speed;                      /*!< Sets the Ethernet speed: 10/100 Mbps */

    ETH_RECEIVEOWN_T                receiveOwn;                 /*!< Selects or not the ReceiveOwn
                                                                    ReceiveOwn allows the reception of frames when the TX_EN signal is asserted
                                                                    in Half-Duplex mode */

    ETH_LOOPBACKMODE_T              loopbackMode;               /*!< Selects or not the internal MAC MII Loopback mode */

    ETH_MODE_T                      mode;                       /*!< Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode */

    ETH_CHECKSUMOFFLAOD_T           checksumOffload;            /*!< Selects or not the IPv4 checksum checking for received frame payloads' TCP/UDP/ICMP headers. */

    ETH_RETRYTRANSMISSION_T         retryTransmission;          /*!< Selects or not the MAC attempt retries transmission, based on the settings of BL,
                                                                    when a collision occurs (Half-Duplex mode) */

    ETH_AUTOMATICPADCRCSTRIP_T      automaticPadCRCStrip;       /*!< Selects or not the Automatic MAC Pad/CRC Stripping */

    ETH_BACKOFFLIMIT_T              backOffLimit;               /*!< Selects the BackOff limit value */

    ETH_DEFFERRALCHECK_T            deferralCheck;              /*!< Selects or not the deferral check function (Half-Duplex mode) */

    ETH_RECEIVEAll_T                receiveAll;                 /*!< Selects or not all frames reception by the MAC (No filtering) */

    ETH_SOURCEADDRFILTER_T          sourceAddrFilter;           /*!< Selects the Source Address Filter mode */

    ETH_PASSCONTROLFRAMES_T         passControlFrames;          /*!< Sets the forwarding mode of the control frames (including unicast and multicast PAUSE frames) */

    ETH_BROADCASTFRAMESRECEPTION_T  broadcastFramesReception;   /*!< Selects or not the reception of Broadcast Frames */

    ETH_DESTINATIONADDRFILTER_T     destinationAddrFilter;      /*!< Sets the destination filter mode for both unicast and multicast frames */

    ETH_PROMISCUOUS_MODE_T          promiscuousMode;            /*!< Selects or not the Promiscuous Mode */

    ETH_MULTICASTFRAMESFILTER_T     multicastFramesFilter;      /*!< Selects the Multicast Frames filter mode */

    ETH_UNICASTFRAMESFILTER_T       unicastFramesFilter;        /*!< Selects the Unicast Frames filter mode */


    uint32_t                        hashTableHigh;              /*!< This field holds the higher 32 bits of Hash table. */

    uint32_t                        hashTableLow;               /*!< This field holds the lower 32 bits of Hash table. */

    uint32_t                        pauseTime;                  /*!< This field holds the (value<=0xFFFF) to be used in the Pause Time */

    ETH_ZEROQUANTAPAUSE_T           zeroQuantaPause;            /*!< Selects or not the automatic generation of Zero-Quanta Pause Control frames */

    ETH_PAUSELOWTHRESHOLD_T         pauseLowThreshold;          /*!< This field configures the threshold of the PAUSE to be checked for
                                                                    automatic retransmission of PAUSE Frame */

    ETH_UNICASTPAUSEFRAMEDETECT_T   unicastPauseFrameDetect;    /*!< Selects or not the MAC detection of the Pause frames (with MAC Address0
                                                                    unicast address and unique multicast address) */

    ETH_RECEIVEFLOWCONTROL_T        receiveFlowControl;         /*!< Enables or disables the MAC to decode the received Pause frame and
                                                                    disable its transmitter for a specified time (Pause Time) */

    ETH_TRANSMITFLOWCONTROL_T       transmitFlowControl;        /*!< Enables or disables the MAC to transmit Pause frames (Full-Duplex mode)
                                                                    or the MAC back-pressure operation (Half-Duplex mode) */

    ETH_VLANTAGCOMPARISON_T         VLANTagComparison;          /*!< Selects the 12-bit VLAN identifier or the complete 16-bit VLAN tag for
                                                                    comparison and filtering */

    uint32_t                        VLANTagIdentifier;          /*!< Holds the (value <=0xFFFF) VLAN tag identifier for receive frames */

    /* DMA Configuration */
    ETH_DROPTCPIPCHECKSUMERRORFRAME_T   dropTCPIPChecksumErrorFrame; /*!< Selects or not the Dropping of TCP/IP Checksum Error Frames */

    ETH_RECEIVESTOREFORWARD_T           receiveStoreForward;         /*!< Enables or disables the Receive store and forward mode */

    ETH_FLUSHRECEIVEDFRAME_T            flushReceivedFrame;          /*!< Enables or disables the flushing of received frames */

    ETH_TRANSMITSTOREFORWARD_T          transmitStoreForward;        /*!< Enables or disables Transmit store and forward mode */

    ETH_TRANSMITTHRESHOLDCONTROL_T      transmitThresholdControl;    /*!< Selects or not the Transmit Threshold Control */

    ETH_FORWARDERRORFRAMES_T            forwardErrorFrames;          /*!< Selects or not the forward to the DMA of erroneous frames */

    ETH_FORWARDUNDERSIZEDGOODFRAMES_T   forwardUndersizedGoodFrames; /*!< Enables or disables the Rx FIFO to forward Undersized frames (frames with no Error
                                                                        and length less than 64 bytes) including pad-bytes and CRC) */

    ETH_RECEIVEDTHRESHOLDCONTROL_T      receiveThresholdControl;     /*!< Selects the threshold level of the Receive FIFO */

    ETH_SECONDFRAMEOPERARTE_T           secondFrameOperate;          /*!< Selects or not the Operate on second frame mode, which allows the DMA to process a second
                                                                        frame of Transmit data even before obtaining the status for the first frame. */

    ETH_ADDRESSALIGNEDBEATS_T           addressAlignedBeats;         /*!< Enables or disables the Address Aligned Beats */

    ETH_FIXEDBURST_T                    fixedBurst;                  /*!< Enables or disables the AHB Master interface fixed burst transfers */

    ETH_RXDMABURSTLENGTH_T              rxDMABurstLength;            /*!< Indicates the maximum number of beats to be transferred in one Rx DMA transaction */

    ETH_TXDMABURSTLENGTH_T              txDMABurstLength;            /*!< Indicates the maximum number of beats to be transferred in one Tx DMA transaction */

    uint32_t                            descriptorSkipLength;        /*!< Specifies the number of word to skip between two unchained descriptors (Ring mode) (value <= 0x1F) */

    ETH_DMAARBITRATION_T                DMAArbitration;              /*!< Selects the DMA Tx/Rx arbitration */
} ETH_Config_T;

/**
  * @brief  ETH DMA Descriptors data structure types
  */
typedef struct
{
    __IO uint32_t   Status;                            /*!< Status */
    uint32_t        ControlBufferSize;                 /*!< Control and Buffer1, Buffer2 lengths */
    uint32_t        Buffer1Addr;                       /*!< Buffer1 address pointer */
    uint32_t        Buffer2NextDescAddr;               /*!< Buffer2 or next descriptor address pointer */
    /* Enhanced ETHERNET DMA PTP Descriptors */
} ETH_DMADescConfig_T;

/**
  * @brief  ETH DMA Descriptors data structure types
  */
typedef struct
{
    uint32_t        length;                 /*!< Data length */
    uint32_t        buffer;                 /*!< Data buffer */
    __IO ETH_DMADescConfig_T* descriptor;   /*!< DMA descriptor */
} ETH_Frame_T;

/**
  * @brief  ETH DMA Descriptors Received Frame Informations structure types
  */
typedef struct
{
    __IO ETH_DMADescConfig_T*   FS_RxDesc;              /*!< First Segment Rx Desc */
    __IO ETH_DMADescConfig_T*   LS_RxDesc;              /*!< Last Segment Rx Desc */
    __IO uint32_t               segCount;               /*!< Segment count */
} ETH_DMARxFrameInformations;

/**@} end of group ETH_Structure*/

/** @defgroup ETH_Functions
  @{
*/

/* ETH Configuration */
void ETH_Reset(void);
void ETH_ConfigStructInit(ETH_Config_T* ethConfig);
uint32_t ETH_Config(ETH_Config_T* ethConfig, uint16_t addr);
void ETH_SoftwareReset(void);
uint8_t ETH_ReadSoftwareReset(void);
void ETH_Start(void);
void ETH_Stop(void);
uint32_t ETH_ReadRxPacketSize(ETH_DMADescConfig_T* DMARxDesc);

/* PHY */
uint16_t ETH_ReadPHYRegister(uint16_t addr, uint16_t reg);
uint32_t ETH_WritePHYRegister(uint16_t addr, uint16_t reg, uint16_t data);
uint32_t ETH_EnablePHYLoopBack(uint16_t addr);
uint32_t ETH_DisablePHYLoopBack(uint16_t addr);

/* MAC */
void ETH_EnableMACTransmission(void);
void ETH_DisableMACTransmission(void);
void ETH_EnableMACReceiver(void);
void ETH_DisableMACReceiver(void);
uint8_t ETH_ReadFlowControlBusyStatus(void);
void ETH_SetPauseControlFrame(void);
void ETH_EnableBackPressureActivation(void);
void ETH_DisableBackPressureActivation(void);
uint8_t ETH_ReadMACFlagStatus(ETH_MAC_FLAG_T flag);
void ETH_EnableMACInterrupt(uint32_t interrupt);
void ETH_DisableMACInterrupt(uint32_t interrupt);
void ETH_ConfigMACAddress(ETH_MAC_ADDRESS_T macAddr, uint8_t* addr);
void ETH_ReadMACAddress(ETH_MAC_ADDRESS_T macAddr, uint8_t* addr);
void ETH_EnableMACAddressPerfectFilter(ETH_MAC_ADDRESS_T macAddr);
void ETH_DisableMACAddressPerfectFilter(ETH_MAC_ADDRESS_T macAddr);
void ETH_ConfigMACAddressFilter(ETH_MAC_ADDRESS_T macAddr, ETH_MAC_ADDRESSFILTER_T filter);
void ETH_ConfigMACAddressMaskBytesFilter(ETH_MAC_ADDRESS_T macAddr, uint32_t maskByte);

/* DMA descriptors */
void ETH_ConfigDMARxDescChain(ETH_DMADescConfig_T* DMARxDescTab, uint8_t* rxBuff, uint32_t rxBuffcount);
void ETH_ConfigDMATxDescChain(ETH_DMADescConfig_T* DMATxDescTab, uint8_t* txBuff, uint32_t txBuffcount);
uint32_t ETH_CheckReceivedFrame(void);
uint32_t ETH_Transmit_Descriptors(u16 frameLength);
ETH_Frame_T ETH_ReadReceivedFrame(void);
uint8_t ETH_ReadDMATxDescFlagStatus(ETH_DMADescConfig_T* DMATxDesc, ETH_DMATXDESC_FLAG_T flag);
uint32_t ETH_ReadDMATxDescCollisionCount(ETH_DMADescConfig_T* DMATxDesc);
void ETH_ConfigDMATxDescOwnBit(ETH_DMADescConfig_T* DMATxDesc);
void ETH_EnableDMATxDescTransmitInterrupt(ETH_DMADescConfig_T* DMATxDesc);
void ETH_DisableDMATxDescTransmitInterrupt(ETH_DMADescConfig_T* DMATxDesc);
void ETH_ConfigDMATxDescFrameSegment(ETH_DMADescConfig_T* DMATxDesc, ETH_DMATXDESC_SEGMENTS_T frameSegment);
void ETH_ConfigDMATxDescChecksumInsertion(ETH_DMADescConfig_T* DMATxDesc, ETH_DMATXDESC_CHECKSUMB_T checksum);
void ETH_EnableDMATxDescCRC(ETH_DMADescConfig_T* DMATxDesc);
void ETH_DisableDMATxDescCRC(ETH_DMADescConfig_T* DMATxDesc);
void ETH_EnableDMATxDescSecondAddressChained(ETH_DMADescConfig_T* DMATxDesc);
void ETH_DisableDMATxDescSecondAddressChained(ETH_DMADescConfig_T* DMATxDesc);
void ETH_EnableDMATxDescShortFramePadding(ETH_DMADescConfig_T* DMATxDesc);
void ETH_DisableDMATxDescShortFramePadding(ETH_DMADescConfig_T* DMATxDesc);
void ETH_ConfigDMATxDescBufferSize(ETH_DMADescConfig_T* DMATxDesc, uint32_t bufferSize1, uint32_t bufferSize2);
uint8_t ETH_ReadDMARxDescFlagStatus(ETH_DMADescConfig_T* DMARxDesc, ETH_DMARXDESC_FLAG_T flag);

void ETH_ConfigDMARxDescOwnBit(ETH_DMADescConfig_T* DMARxDesc);
uint32_t ETH_ReadDMARxDescFrameLength(ETH_DMADescConfig_T* DMARxDesc);
void ETH_EnableDMARxDescReceiveInterrupt(ETH_DMADescConfig_T* DMARxDesc);
void ETH_DisableDMARxDescReceiveInterrupt(ETH_DMADescConfig_T* DMATxDesc);
uint32_t ETH_ReadDMARxDescBufferSize(ETH_DMADescConfig_T* DMARxDesc, ETH_DMARXDESC_BUFFER_T buffer);
ETH_Frame_T ETH_ReadReceivedFrameInterrupt(void);

/* DMA */
uint8_t ETH_ReadDMAFlagStatus(ETH_DMA_FLAG_T flag);
void ETH_ClearDMAFlag(uint32_t flag);
uint8_t ETH_ReadDMAIntFlag(ETH_DMA_INT_T flag);
void ETH_ClearDMAIntFlag(uint32_t flag);
uint32_t ETH_ReadTransmitProcessState(void);
uint32_t ETH_ReadReceiveProcessState(void);
void ETH_FlushTransmitFIFO(void);
uint8_t ETH_ReadFlushTransmitFIFOStatus(void);
void ETH_EnableDMATransmission(void);
void ETH_DisableDMATransmission(void);
void ETH_EnableDMAReceiver(void);
void ETH_DisableDMAReceiver(void);
void ETH_EnableDMAInterrupt(uint32_t interrupt);
void ETH_DisableDMAInterrupt(uint32_t interrupt);
uint8_t ETH_ReadDMAOverflowStatus(ETH_DMA_OVERFLOW_T overflow);
uint32_t ETH_ReadRxOverflowMissedFrameCounter(void);
uint32_t ETH_ReadBufferUnavailableMissedFrameCounter(void);
uint32_t ETH_ReadCurrentTxDescStartAddress(void);
uint32_t ETH_ReadCurrentRxDescStartAddress(void);
uint32_t ETH_ReadCurrentTxBufferAddress(void);
uint32_t ETH_ReadCurrentRxBufferAddress(void);
void ETH_ResetDMATransmission(void);
void ETH_ResetDMAReception(void);

/* PMT */
void ETH_ResetWakeUpFrameFilterRegisterPointer(void);
void ETH_EnableGlobalUnicastWakeUp(void);
void ETH_DisableGlobalUnicastWakeUp(void);
uint8_t ETH_ReadPMTFlagStatus(ETH_PMT_FLAG_T flag);
void ETH_EnableWakeUpFrameDetection(void);
void ETH_DisableWakeUpFrameDetection(void);
void ETH_EnableMagicPacketDetection(void);
void ETH_DisableMagicPacketDetection(void);
void ETH_EnablePowerDown(void);
void ETH_DisablePowerDown(void);

/* MMC */
void ETH_EnableMMCCounterFreeze(void);
void ETH_DisableMMCCounterFreeze(void);
void ETH_EnableMMCResetOnRead(void);
void ETH_DisableMMCResetOnRead(void);
void ETH_EnableMMCCounterRollover(void);
void ETH_DisableMMCCounterRollover(void);
void ETH_ResetMMCCounters(void);
void ETH_EnableMMCInterrupt(uint32_t interrupt);
void ETH_DisableMMCInterrupt(uint32_t interrupt);
uint8_t ETH_ReadMMCIntFlag(uint32_t flag);
uint32_t ETH_ReadMMCRegister(ETH_MMC_REG_T MMCReg);

/**@} end of group ETH_Functions */
/**@} end of group ETH_Driver */
/**@} end of group APM32F10x_ETHDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10x_ETH_H */
