/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_ENET_DRIVER_H__
#define __FSL_ENET_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_enet_hal.h"
#include "fsl_os_abstraction.h"
#if FSL_FEATURE_SOC_ENET_COUNT
/*! 
 * @addtogroup enet_driver
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Array for ENET module register base address. */
extern ENET_Type * const g_enetBase[];

/*! @brief Two-dimensional array for the ENET interrupt vector number. */
extern const IRQn_Type g_enetTxIrqId[];
extern const IRQn_Type g_enetRxIrqId[];
extern const IRQn_Type g_enetTsIrqId[];
extern const IRQn_Type g_enetErrIrqId[];

/*******************************************************************************
 * Definitions

 ******************************************************************************/
/*! @brief Defines the approach: ENET interrupt handler receive */
#ifndef ENET_RECEIVE_ALL_INTERRUPT
#define ENET_RECEIVE_ALL_INTERRUPT  1
#endif

/*! @brief Defines the statistic enable macro.*/
#ifndef ENET_ENABLE_DETAIL_STATS
#define ENET_ENABLE_DETAIL_STATS    0
#endif

/*! brief Defines the macro for converting constants from host byte order to network byte order*/
#define ENET_HTONS(n)                      __REV16(n)
#define ENET_HTONL(n)                      __REV(n)
#define ENET_NTOHS(n)                      __REV16(n)
#define ENET_NTOHL(n)                      __REV(n)

/*! @brief Defines the CRC-32 calculation constant. */
#define  ENET_ORIGINAL_CRC32   0xFFFFFFFFU      /*!< CRC-32 Original data*/
#define  ENET_CRC32_POLYNOMIC  0xEDB88320U     /*!< CRC-32 Polynomic*/

#if FSL_FEATURE_ENET_SUPPORT_PTP
/*! @brief Defines the PTP IOCTL macro.*/
typedef enum _enet_ptp_ioctl
{
    kEnetPtpGetRxTimestamp = 0,    /*!< ENET PTP gets receive timestamp*/
    kEnetPtpGetTxTimestamp,        /*!< ENET PTP gets transmit timestamp*/
    kEnetPtpGetCurrentTime,        /*!< ENET PTP gets current time*/
    kEnetPtpSetCurrentTime,        /*!< ENET PTP sets current time*/
    kEnetPtpFlushTimestamp,        /*!< ENET PTP flushes timestamp*/
    kEnetPtpCorrectTime,           /*!< ENET PTP time correction*/
    kEnetPtpSendEthernetPtpV2,     /*!< ENET PTPv2 sends Ethernet frame*/
    kEnetPtpReceiveEthernetPtpV2   /*!< ENET PTPv2 receives with Ethernet frame*/
} enet_ptp_ioctl_t;


/*! @brief Defines the ENET PTP message related constant.*/
typedef enum _enet_ptp_event_type
{
     kEnetPtpSourcePortIdLen = 10,     /*!< PTP message sequence id length*/
     kEnetPtpEventMsgType    = 3,      /*!< PTP event message type*/
     kEnetPtpEventPort       = 319,    /*!< PTP event port number*/
     kEnetPtpGnrlPort        = 320     /*!< PTP general port number*/
} enet_ptp_event_type_t;

/*! @brief Defines all ENET PTP content offsets in the IPv4 PTP UDP/IP multicast message.*/
typedef enum _enet_ipv4_ptp_content_offset
{
    kEnetPtpIpVersionOffset       = 0xe,   /*!< IPv4 PTP message IP version offset*/
    kEnetPtpIpv4UdpProtocolOffset = 0x17,  /*!< IPv4 PTP message UDP protocol offset*/
    kEnetPtpIpv4UdpPortOffset     = 0x24,  /*!< IPv4 PTP message UDP port offset*/
    kEnetPtpIpv4UdpMsgTypeOffset  = 0x2a,  /*!< IPv4 PTP message UDP message type offset*/
    kEnetPtpIpv4UdpVersionoffset  = 0x2b,  /*!< IPv4 PTP message UDP version offset*/
    kEnetPtpIpv4UdpClockIdOffset  = 0x3e,  /*!< IPv4 PTP message UDP clock id offset*/
    kEnetPtpIpv4UdpSequenIdOffset = 0x48,  /*!< IPv4 PTP message UDP sequence id offset*/
    kEnetPtpIpv4UdpCtlOffset      = 0x4a   /*!< IPv4 PTP message UDP control offset*/
} enet_ipv4_ptp_content_offset_t;

/*! @brief Defines all ENET PTP content offset in THE IPv6 PTP UDP/IP multicast message.*/
typedef enum _enet_ipv6_ptp_content_offset
{
    kEnetPtpIpv6UdpProtocolOffset   = 0x14,   /*!< IPv6 PTP message UDP protocol offset*/
    kEnetPtpIpv6UdpPortOffset       = 0x38,   /*!< IPv6 PTP message UDP port offset*/
    kEnetPtpIpv6UdpMsgTypeOffset    = 0x3e,   /*!< IPv6 PTP message UDP message type offset*/
    kEnetPtpIpv6UdpVersionOffset    = 0x3f,   /*!< IPv6 PTP message UDP version offset*/
    kEnetPtpIpv6UdpClockIdOffset    = 0x52,   /*!< IPv6 PTP message UDP clock id offset*/
    kEnetPtpIpv6UdpSequenceIdOffset = 0x5c,   /*!< IPv6 PTP message UDP sequence id offset*/
    kEnetPtpIpv6UdpCtlOffset        = 0x5e    /*!< IPv6 PTP message UDP control offset*/
} enet_ipv6_ptp_content_offset_t;

/*! @brief Defines all ENET PTP content offset in the PTP Layer2 Ethernet message.*/
typedef enum _enet_ethernetl2_ptpv2_content_offset
{
    kEnetPtpEtherL2PktTypeOffset    = 0x0c,   /*!< PTPv2 message Ethernet packet type offset*/
    kEnetPtpEtherL2MsgTypeOffset    = 0x0e,   /*!< PTPv2 message Ethernet message type offset*/
    kEnetPtpEtherL2VersionOffset    = 0x0f,   /*!< PTPv2 message Ethernet version type offset*/
    kEnetPtpEtherL2ClockIdOffset    = 0x22,   /*!< PTPv2 message Ethernet clock id offset*/
    kEnetPtpEtherL2SequenceIdOffset = 0x2c,   /*!< PTPv2 message Ethernet sequence id offset*/
    kEnetPtpEtherL2CtlOffset        = 0x2e    /*!< PTPv2 message Ethernet control offset*/
} enet_ethernetl2_ptpv2_content_offset_t;

/*! @brief Defines the 1588 timer parameters.*/
typedef enum _enet_ptp_timer_wrap_period
{
    kEnetPtpAtperValue    = 1000000000, /*!< PTP timer wrap around one second */
    kEnetBaseIncreaseUnit = 2           /*!< PTP timer adjusts clock and increases value to 2*/
} enet_ptp_timer_wrap_period_t;
#endif

/*! @brief Defines the CRC data for a hash value calculation.*/
typedef enum _enet_crc_parameter
{
    kEnetCrcOffset = 8,           /*!< CRC-32 offset2*/
    kEnetCrcMask1  = 0x3F         /*!< CRC-32 mask*/
} enet_crc_parameter_t;

/*! @brief Defines the ENET protocol type and main parameters.*/
typedef enum _enet_protocol_type
{
    kEnetProtocoll2ptpv2   = 0x88F7,     /*!< Packet type Ethernet ieee802.3*/
    kEnetProtocolIpv4      = 0x0800,     /*!< Packet type IPv4*/
    kEnetProtocolIpv6      = 0x86dd,     /*!< Packet type IPv6*/
    kEnetProtocol8021QVlan = 0x8100,     /*!< Packet type VLAN*/
    kEnetPacketUdpVersion  = 0x11,       /*!< UDP protocol type*/
    kEnetPacketIpv4Version = 0x4,        /*!< Packet IP version IPv4*/
    kEnetPacketIpv6Version = 0x6         /*!< Packet IP version IPv6*/
} enet_protocol_type_t;


#if FSL_FEATURE_ENET_SUPPORT_PTP
/*! @brief Defines the  ENET Mac PTP timestamp structure.*/
typedef struct ENETMacPtpTime
{
    uint64_t second;     /*!< Second*/
    uint32_t nanosecond; /*!< Nanosecond*/
} enet_mac_ptp_time_t;

/*! @brief Defines the ENET PTP timer drift structure.*/
typedef struct ENETPtpDrift
{
    int32_t drift;    /*!< Drift for the PTP timer to adjust*/
} enet_ptp_drift_t;

/*! @brief Defines the ENET Mac PTP time parameter.*/
typedef struct ENETMacPtpMasterTime
{
    uint8_t masterPtpInstance;/*!< PTP master timer instance*/
    uint64_t second;          /*!< PTP master timer second */
} enet_mac_ptp_master_time_t;

/*! @brief Defines the structure for the ENET PTP message data and timestamp data.*/
typedef struct ENETMacPtpTsData
{
    uint8_t version;              /*!< PTP version*/
    uint8_t sourcePortId[kEnetPtpSourcePortIdLen];/*!< PTP source port ID*/
    uint16_t sequenceId;          /*!< PTP sequence ID*/
    uint8_t messageType;          /*!< PTP message type*/
    enet_mac_ptp_time_t timeStamp;/*!< PTP timestamp*/
} enet_mac_ptp_ts_data_t;

/*! @brief Defines the ENET PTP ring buffer structure for the PTP message timestamp store.*/
typedef struct ENETMacPtpTsRing
{
    uint32_t front; /*!< The first index of the ring*/
    uint32_t end;   /*!< The end index of the ring*/
    uint32_t size;  /*!< The size of the ring*/
    enet_mac_ptp_ts_data_t *ptpTsDataPtr;/*!< PTP message data structure*/
} enet_mac_ptp_ts_ring_t;

/*! @brief Defines the ENET data buffers for the PTP version2 message using the layer2 Ethernet frame.*/
typedef struct ENETMacPtpL2buffer
{
    uint8_t packet[kEnetMaxFrameVlanSize]; /*!< Buffer for ptpv2 message*/
    uint16_t length;                       /*!< PTP message length*/
} enet_mac_ptp_l2buffer_t;

/*! @brief Defines the ENET PTPv2 packet queue using the layer2 Ethernet frame.*/
typedef struct ENETMacPtpL2bufferqueue
{
    enet_mac_ptp_l2buffer_t *l2bufferPtr;   /*!< PTP layer2 data buffers*/
    uint16_t l2bufferNum;    /*!< PTP Layer2 buffer Numbers*/
    uint16_t writeIdx;          /*!< Queue write index*/
    uint16_t readIdx;            /*!< Queue read index*/
} enet_mac_ptp_l2buffer_queue_t;

/*! @brief Defines the ENET PTP layer2 Ethernet frame structure.*/
typedef struct ENETMacPtpL2packet
{
    uint8_t *ptpMsg;     /*!< PTP message*/
    uint16_t length;     /*!< Length of the PTP message*/
    uint8_t hwAddr[kEnetMacAddrLen];  /*!< Destination hardware address*/
    uint16_t vlanId;     /* VLAN id*/
    uint8_t vlanPrior;   /* VLAN priority */
} enet_mac_ptp_l2_packet_t;

/*! @brief Defines the ENET PTP buffer structure for all 1588 data.*/
typedef struct ENETPrivatePtpBuffer
{
    enet_mac_ptp_ts_ring_t rxTimeStamp;/*!< Data structure for receive message*/
    enet_mac_ptp_ts_ring_t txTimeStamp;/*!< Data structure for transmit timestamp*/
    enet_mac_ptp_l2buffer_queue_t layer2Queue;/*!< Data structure for layer2 Ethernet queue*/
    uint64_t masterSecond;             /*!< PTP time second when it's master time*/
    bool firstflag;         /* First flag for multicast transmit buffer descriptors*/
    volatile enet_bd_struct_t *firstBdPtr; /* First buffer descriptor for timestamp store*/
} enet_private_ptp_buffer_t;
#endif


/*! @brief Defines the multicast group structure for the ENET device. */
typedef struct ENETMulticastGroup
{
    uint8_t groupAdddr[kEnetMacAddrLen];   /*!< Multicast group address*/
    uint32_t hash;                 /*!< Hash value of the multicast group address*/
    struct ENETMulticastGroup *next; /*!< Pointer of the next group structure*/
    struct ENETMulticastGroup *prv;  /*!< Pointer of the previous structure*/
} enet_multicast_group_t;

/*! @brief Defines the ENET header structure. */
typedef struct ENETEthernetHeader
{
    uint8_t destAddr[kEnetMacAddrLen];  /*!< Destination address */
    uint8_t sourceAddr[kEnetMacAddrLen];/*!< Source address*/
    uint16_t type;         /*!< Protocol type*/
} enet_ethernet_header_t;

/*! @brief Defines the ENET VLAN frame header structure. */
typedef struct ENET8021vlanHeader
{
    uint8_t destAddr[kEnetMacAddrLen];  /*!< Destination address */
    uint8_t sourceAddr[kEnetMacAddrLen];/*!< Source address*/
    uint16_t tpidtag;      /*!< ENET 8021tag header tag region*/
    uint16_t othertag;     /*!< ENET 8021tag header type region*/
    uint16_t type;         /*!< Protocol type*/
} enet_8021vlan_header_t;

/*! @brief Defines the structure for ENET buffer descriptors status.*/
typedef struct ENETBuffDescripContext
{
    volatile enet_bd_struct_t * rxBdBasePtr;   /*!< Receive buffer descriptor base address pointer*/
    volatile enet_bd_struct_t * rxBdCurPtr;    /*!< Current receive buffer descriptor pointer*/
    volatile enet_bd_struct_t * rxBdDirtyPtr;  /*!< Receive dirty buffer descriptor*/
    volatile enet_bd_struct_t * txBdBasePtr;   /*!< Transmit buffer descriptor base address pointer*/
    volatile enet_bd_struct_t * txBdCurPtr;    /*!< Current transmit buffer descriptor pointer*/
    volatile enet_bd_struct_t * txBdDirtyPtr;  /*!< Last cleaned transmit buffer descriptor pointer*/
    bool  isTxBdFull;         /*!< Transmit buffer descriptor full*/
    bool  isRxBdFull;         /*!< Receive buffer descriptor full*/
    uint32_t rxBuffSizeAlign;      /*!< Receive buffer size alignment*/
    uint32_t txBuffSizeAlign;    /*!< Transmit buffer size alignment */
    uint8_t *extRxBuffQue; /*!< Extended Rx data buffer queue to update the data buff
                                 in the receive buffer descriptor*/
    uint8_t extRxBuffNum;        /*!< extended data buffer number */
} enet_buff_descrip_context_t;

/*! @brief Defines the ENET packets statistic structure.*/
typedef struct ENETMacStats
{
    uint32_t statsRxTotal;   /*!< Total number of receive packets*/
    uint32_t statsTxTotal;   /*!< Total number of transmit packets*/
#if ENET_ENABLE_DETAIL_STATS
    uint32_t statsRxMissed;  /*!< Total number of receive packets*/
    uint32_t statsRxDiscard; /*!< Receive discarded with error */
    uint32_t statsRxError;   /*!< Receive discarded with error packets*/
    uint32_t statsTxMissed;  /*!< Transmit missed*/
    uint32_t statsTxDiscard; /*!< Transmit discarded with error */
    uint32_t statsTxError;   /*!< Transmit error*/
    uint32_t statsRxAlign;   /*!< Receive non-octet alignment*/
    uint32_t statsRxFcs;     /*!< Receive CRC error*/
    uint32_t statsRxTruncate;/*!< Receive truncate*/
    uint32_t statsRxLengthGreater;  /*!< Receive length greater than RCR[MAX_FL] */
    uint32_t statsRxCollision;      /*!< Receive collision*/
    uint32_t statsRxOverRun;        /*!< Receive over run*/
    uint32_t statsTxOverFlow;       /*!< Transmit overflow*/
    uint32_t statsTxLateCollision;  /*!< Transmit late collision*/
    uint32_t statsTxExcessCollision;/*!< Transmit excess collision*/
    uint32_t statsTxUnderFlow;      /*!< Transmit under flow*/
    uint32_t statsTxLarge;          /*!< Transmit large packet*/
    uint32_t statsTxSmall;          /*!< Transmit small packet*/
#endif
} enet_stats_t;

/*! @brief Defines the ENET MAC packet buffer structure.*/
typedef struct ENETMacPacketBuffer
{
    uint8_t *data;     /*!< Data buffer pointer*/
    uint16_t length;    /*!< Data length*/
    struct ENETMacPacketBuffer *next;  /*!< Next pointer*/
} enet_mac_packet_buffer_t;

#if ENET_RECEIVE_ALL_INTERRUPT
typedef uint32_t (* enet_netif_callback_t)(void *enetPtr, enet_mac_packet_buffer_t *packet);
#endif

/*! @brief Defines the receive buffer descriptor configure structure.*/
typedef struct ENETBuffConfig
{
    uint16_t rxBdNumber;    /*!< Receive buffer descriptor number*/
    uint16_t txBdNumber;    /*!< Transmit buffer descriptor number*/
    uint32_t rxBuffSizeAlign;    /*!< Aligned receive buffer size and must be larger than 256*/
    uint32_t txBuffSizeAlign;    /*!< Aligned transmit buffer size and must be larger than 256*/
    volatile enet_bd_struct_t  *rxBdPtrAlign; /*!< Aligned receive buffer descriptor pointer */
    uint8_t *rxBufferAlign;     /*!< Aligned receive data buffer pointer */
    volatile enet_bd_struct_t  *txBdPtrAlign; /*!< Aligned transmit buffer descriptor pointer*/
    uint8_t *txBufferAlign;     /*!< Aligned transmit buffer descriptor pointer*/
    uint8_t *extRxBuffQue;    /*!< Extended Rx data buffer queue to update the data buff
                                 in the receive buffer descriptor*/
    uint8_t extRxBuffNum;     /*!< extended data buffer number  */
#if FSL_FEATURE_ENET_SUPPORT_PTP
    uint32_t ptpTsRxBuffNum;      /*!< Receive 1588 timestamp buffer number*/
    uint32_t ptpTsTxBuffNum;     /*!< Transmit 1588 timestamp buffer number*/
    enet_mac_ptp_ts_data_t *ptpTsRxDataPtr; /*!< 1588 timestamp receive buffer pointer*/
    enet_mac_ptp_ts_data_t *ptpTsTxDataPtr; /*!< 1588 timestamp transmit buffer pointer*/
#endif
} enet_buff_config_t;


/*! @brief Defines the ENET device data structure for the ENET.*/
typedef struct ENETDevIf
{
    struct ENETDevIf *next; /*!< Next device structure address*/
    void *netIfPrivate;  /*!< For upper layer private structure*/  
    enet_multicast_group_t *multiGroupPtr; /*!< Multicast group chain*/
    uint32_t deviceNumber;    /*!< Device number*/
    uint8_t macAddr[kEnetMacAddrLen];        /*!< Mac address */
    uint8_t phyAddr;        /*!< PHY address connected to this device*/
    bool isInitialized;       /*!< Device initialized*/
    uint16_t maxFrameSize;  /*!< Mac maximum frame size*/
    bool isVlanTagEnabled;   /*!< ENET VLAN-TAG frames enabled*/
    bool isTxCrcEnable;         /*!< Transmit CRC enable in buffer descriptor*/
    bool isRxCrcFwdEnable;      /*!< Receive CRC forward*/
    enet_buff_descrip_context_t bdContext; /*!< Mac buffer descriptors context pointer*/
#if FSL_FEATURE_ENET_SUPPORT_PTP
    enet_private_ptp_buffer_t privatePtp;/*!< PTP private buffer*/
#endif
    enet_stats_t stats;                /*!< Packets statistic*/
#if ENET_RECEIVE_ALL_INTERRUPT
    enet_netif_callback_t  enetNetifcall;  /*!< Receive callback function to the upper layer*/
#else
    event_t enetReceiveSync;     /*!< Receive sync signal*/
#endif
    mutex_t enetContextSync;     /*!< Sync signal*/
} enet_dev_if_t;

/*! @brief Defines the ENET user configuration structure. */
typedef struct ENETUserConfig
{
    const enet_mac_config_t* macCfgPtr;   /*!< MAC configuration structure */
    const enet_buff_config_t* buffCfgPtr;   /*!< ENET buffer configuration structure */
} enet_user_config_t;


/*******************************************************************************
 * API 
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
  * @name ENET Driver
  * @{
  */


#if FSL_FEATURE_ENET_SUPPORT_PTP
/*!
 * @brief Initializes the ENET PTP context structure with the basic configuration.
 *
 * @param enetIfPtr The ENET context structure.
 * @param ptpTsRxDataPtr The PTP timestamp buffer pointer for received frames.
 * @param rxBuffNum The PTP timestamp buffer numbers for received frames.
 * @param ptpTsTxDataPtr The PTP timestamp buffer pointer for transmitted frames. 
 * @param txBuffNum The PTP timestamp buffer numbers for transmitted frames.
 * @param isSlaveEnabled The flag to enable or disable slave mode.
 * @return The execution status.
 */
enet_status_t ENET_DRV_1588Init(enet_dev_if_t *enetIfPtr, enet_mac_ptp_ts_data_t *ptpTsRxDataPtr,uint32_t rxBuffNum, 
            enet_mac_ptp_ts_data_t *ptpTsTxDataPtr, uint32_t txBuffNum, bool isSlaveEnabled);
  
/*!
 * @brief Frees all ring buffers.
 *
 * @param enetIfPtr The basic Ethernet structure pointer.
 * @return The execution status.
 */
enet_status_t ENET_DRV_1588Deinit(enet_dev_if_t *enetIfPtr);

/*!
 * @brief Initializes the ENET PTP timer with the basic configuration.
 *
 * After the PTP starts, the 1588 timer also starts running. To make the 1588 timer
 * the slave, enable the isSlaveEnabled flag.
 *
 * @param instance The ENET instance number.
 * @param isSlaveEnabled The switch to enable or disable the PTP timer slave mode.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Start1588Timer(uint32_t instance, bool isSlaveEnabled);

/*!
 * @brief Stops the ENET PTP timer.
 *
 * @param instance The ENET instance number.
 */
void ENET_DRV_Stop1588Timer(uint32_t instance);

/*!
 * @brief Parses the ENET packet. 
 *
 * Parses the ENET message and checks if it is a PTP message. If it is a PTP message,
 * the message is stored in the PTP information structure. Message parsing 
 * decides whether timestamp processing is done after that.
 *
 * @param packet The ENET packet.
 * @param ptpTsPtr The pointer to the PTP data structure.
 * @param isPtpMsg The PTP message flag.
 * @param isFastEnabled The fast operation flag. If set, only check if it is a PTP message
 *        and doesn't store any PTP message.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Parse1588Packet(uint8_t *packet, enet_mac_ptp_ts_data_t *ptpTsPtr, 
                         bool *isPtpMsg, bool isFastEnabled);
/*!
 * @brief Gets the current value of the ENET PTP time.
 *
 * @param ptpTimerPtr The PTP timer structure.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Get1588timer(enet_mac_ptp_time_t *ptpTimerPtr);

/*!
 * @brief Sets the current value of the ENET PTP time.
 *
 * @param ptpTimerPtr The PTP timer structure.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Set1588timer(enet_mac_ptp_time_t *ptpTimerPtr);

/*!
 * @brief Adjusts the ENET PTP time.
 *
 * @param instance The ENET instance number.
 * @param drift The PTP timer drift value.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Adjust1588timer(uint32_t instance, int32_t drift);

/*!
 * @brief Stores the transmit timestamp.
 *
 * @param ptpBuffer The PTP buffer pointer.
 * @param firstBdPtr The first buffer descriptor of the current transmit frame.
 * @param lastBdPtr The last buffer descriptor of the current transmit frame.
 * @return The execution status.
 */	
enet_status_t ENET_DRV_GetTxTs(enet_private_ptp_buffer_t *ptpBuffer, volatile enet_bd_struct_t *firstBdPtr, volatile enet_bd_struct_t *lastBdPtr);

/*!
 * @brief Stores receive timestamp.
 *
 * @param ptpBuffer The PTP buffer pointer.
 * @param packet The current receive packet.
 * @param bdPtr The current receive buffer descriptor.
 * @return The execution status.
 */
enet_status_t ENET_DRV_GetRxTs(enet_private_ptp_buffer_t *ptpBuffer, uint8_t *packet, volatile enet_bd_struct_t *bdPtr);

/*!
 * @brief Initializes the buffer queue for the PTP layer2 Ethernet packets.
 *
 * @param enetIfPtr The ENET context structure.
 * @param ptpL2BufferPtr The PTP layer2 data buffer pointer, all allocated or distributed
 *        data buffers base address are stored here.
 * @param ptpL2BuffNum The PTP layer2 buffer numbers.
 * @return The execution status.
 */
enet_status_t ENET_DRV_1588l2queueInit(enet_dev_if_t *enetIfPtr, enet_mac_ptp_l2buffer_t *ptpL2BufferPtr,
                                       uint32_t ptpL2BuffNum);

/*!
 * @brief Adds the PTP layer2 Ethernet packet to the PTP Ethernet packet queue.
 *
 * @param enetIfPtr The ENET context structure.
 * @param packBuffer The packet buffer pointer.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Service_l2packet(enet_dev_if_t * enetIfPtr, enet_mac_packet_buffer_t *packBuffer);

/*!
 * @brief Sends the PTP layer2 Ethernet packet to the Net.
 *
 * @param enetIfPtr The ENET context structure.
 * @param paramPtr The buffer from upper layer. 
 * @return The execution status.
 */
enet_status_t ENET_DRV_Send_l2packet(enet_dev_if_t * enetIfPtr, enet_mac_ptp_l2_packet_t *paramPtr);

/*!
 * @brief Receives the PTP layer2 Ethernet packet from the Net.
 *
 * @param enetIfPtr The ENET context structure.
 * @param paramPtr The buffer receive from net and will send to upper layer. 
 * @return The execution status.
 */
enet_status_t ENET_DRV_Receive_l2packet(enet_dev_if_t * enetIfPtr, enet_mac_ptp_l2_packet_t *paramPtr);

/*!
 * @brief Provides the handler for the 1588 stack for the PTP IOCTL.
 *
 * @param enetIfPtr The ENET context structure.
 * @param commandId The command ID.
 * @param inOutPtr The data buffer. 
 * @return The execution status.
 */
enet_status_t ENET_DRV_1588Ioctl(enet_dev_if_t * enetIfPtr, uint32_t commandId, void * inOutPtr);


/*!
 * @brief Checks whether the PTP ring buffer is full.
 *
 * @param ptpTsRingPtr The ENET PTP timestamp ring.
 * @return True if the PTP ring buffer is full. Otherwise, false.
 */
bool ENET_DRV_Is1588TsBuffFull(enet_mac_ptp_ts_ring_t *ptpTsRingPtr);

/*!
 * @brief Updates the latest ring buffers.
 *
 * Adds the PTP message data to the PTP ring buffers and increases the 
 * PTP ring buffer index.
 *
 * @param ptpTsRingPtr The ENET PTP timestamp ring.
 * @param data The PTP data buffer.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Update1588TsBuff(enet_mac_ptp_ts_ring_t *ptpTsRingPtr, enet_mac_ptp_ts_data_t *data);

/*!
 * @brief Searches the element in ring buffers with the message ID and Clock ID.
 *
 * @param ptpTsRingPtr The ENET PTP timestamp ring.
 * @param data The PTP data buffer.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Search1588TsBuff(enet_mac_ptp_ts_ring_t *ptpTsRingPtr, enet_mac_ptp_ts_data_t *data);

/*!
 * @brief Calculates the ENET PTP 1588 timestamp ring buffer index.
 *
 * @param size The ring size.
 * @param curIdx The current ring index.
 * @param offset The offset index.
 * @return The execution status.
 */
static inline uint32_t ENET_DRV_Incr1588TsBuffRing(uint32_t size, uint32_t curIdx, uint32_t offset)
{
    return ((curIdx + offset) % size);
}

/*!
 * @brief The ENET PTP time interrupt handler.
 *
 * @param instance The ENET instance number.
 */
void ENET_DRV_TsIRQHandler(uint32_t instance);
#endif

/*!
 * @brief Initializes the ENET with the basic configuration.
 *
 * @param enetIfPtr The pointer to the basic Ethernet structure.
 * @param userConfig The ENET user configuration structure pointer.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Init(enet_dev_if_t * enetIfPtr, const enet_user_config_t* userConfig);


/*!
 * @brief De-initializes the ENET device.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
enet_status_t ENET_DRV_Deinit(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Updates the receive buffer descriptor.
 *
 * This function updates the used receive buffer descriptor ring to
 * ensure that the used BDS is correctly used. It  cleans 
 * the status region and sets the control region of the used receive buffer 
 * descriptor. If the isBufferUpdate flag is set, the data buffer in the
 * buffer descriptor is updated.
 *
 * @param enetIfPtr The ENET context structure.
 * @param isBuffUpdate The data buffer update flag.
 * @return The execution status.
 */
enet_status_t ENET_DRV_UpdateRxBuffDescrip(enet_dev_if_t * enetIfPtr, bool isBuffUpdate);

/*!
 * @brief ENET transmit buffer descriptor cleanup.
 *
 * First, store the transmit frame error statistic and PTP timestamp of the transmitted packets. 
 * Second, clean up the used transmit buffer descriptors.
 * If the PTP 1588 feature is open, this interface  captures the 1588 timestamp. 
 * It is called by the transmit interrupt handler.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
enet_status_t ENET_DRV_CleanupTxBuffDescrip(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Increases the receive buffer descriptor to the next one.
 *
 * @param enetIfPtr The ENET context structure.
 * @param curBd The current buffer descriptor pointer.
 * @return the increased received buffer descriptor.
 */
volatile enet_bd_struct_t * ENET_DRV_IncrRxBuffDescripIndex(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd);

/*!
 * @brief Increases the transmit buffer descriptor to the next one.
 *
 * @param enetIfPtr The ENET context structure.
 * @param curBd The current buffer descriptor pointer.
 * @return the increased transmit buffer descriptor.
 */
volatile enet_bd_struct_t * ENET_DRV_IncrTxBuffDescripIndex(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd);

/*!
 * @brief Processes the ENET receive frame error statistics.
 *
 * This interface gets the error statistics of the received frame.
 * Because the error information is in the last BD of a frame, this interface
 * should be called when processing the last BD of a frame.
 *
 * @param enetIfPtr The ENET context structure.
 * @param curBd The current buffer descriptor.
 * @return The frame error status.
 *         - True if the frame has an error. 
 *         - False if the frame does not have an error.
 */
bool ENET_DRV_RxErrorStats(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd);

/*!
 * @brief Processes the ENET transmit frame statistics.
 *
 * This interface gets the error statistics of the transmit frame.
 * Because the error information is in the last BD of a frame, this interface
 * should be called when processing the last BD of a frame.
 *
 * @param enetIfPtr The ENET context structure.
 * @param curBd The current buffer descriptor.
 */
void ENET_DRV_TxErrorStats(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd);

#if !ENET_RECEIVE_ALL_INTERRUPT
/*!
 * @brief Receives ENET packets.
 *
 * @param enetIfPtr The ENET context structure.
 * @param packBuffer The received data buffer.
 * @return The execution status.
 */
enet_status_t ENET_DRV_ReceiveData(enet_dev_if_t * enetIfPtr, enet_mac_packet_buffer_t *packBuffer);
#else
/*!
 * @brief Receives ENET packets.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
enet_status_t ENET_DRV_ReceiveData(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Installs ENET TCP/IP stack net interface callback function.
 *
 * @param enetIfPtr The ENET context structure.
 * @param function The ENET TCP/IP stack net interface callback function.
 * @return The execution status.
 */
enet_status_t ENET_DRV_InstallNetIfCall(enet_dev_if_t * enetIfPtr, enet_netif_callback_t function);
#endif


/*!
 * @brief Transmits ENET packets.
 *
 * @param enetIfPtr The ENET context structure.
 * @param dataLen The frame data length to be transmitted.
 * @param bdNumUsed The buffer descriptor need to be used.
 * @return The execution status.
 */
enet_status_t ENET_DRV_SendData(enet_dev_if_t * enetIfPtr, uint32_t dataLen, uint32_t bdNumUsed);

/*!
 * @brief The ENET receive interrupt handler.
 *
 * @param instance The ENET instance number.
 */
void ENET_DRV_RxIRQHandler(uint32_t instance);

/*!
 * @brief The ENET transmit interrupt handler.
 *
 * @param instance The ENET instance number.
 */
void ENET_DRV_TxIRQHandler(uint32_t instance);

/*!
 * @brief Calculates the CRC hash value.
 *
 * @param address The ENET Mac hardware address.
 * @param crcValue The calculated CRC value of the Mac address.
 */
void ENET_DRV_CalculateCrc32(uint8_t *address, uint32_t *crcValue);

/*!
 * @brief Adds the ENET device to a multicast group.
 *
 * @param instance The ENET instance number.
 * @param address The multicast group address.
 * @param hash The hash value of the multicast group address.
 * @return The execution status.
 */
enet_status_t ENET_DRV_AddMulticastGroup(uint32_t instance, uint8_t *address, uint32_t *hash);

/*!
 * @brief Moves the ENET device from a multicast group.
 *
 * @param instance The ENET instance number.
 * @param address The multicast group address.
 * @return The execution status.
 */
enet_status_t ENET_DRV_LeaveMulticastGroup(uint32_t instance, uint8_t *address);

/*!
 * @brief ENET buffer enqueue.
 *
 * @param queue The buffer queue address.
 * @param buffer The buffer will add to the buffer queue.
 */
void enet_mac_enqueue_buffer( void **queue, void *buffer);

/*!
 * @brief ENET buffer dequeue.
 *
 * @param queue The buffer queue address.
 * @return The buffer will be dequeued from the buffer queue.
 */
void *enet_mac_dequeue_buffer( void **queue);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_ENET_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/


