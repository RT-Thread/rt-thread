/**
 *******************************************************************************
 * @file    hc32f4a0_eth.h
 * @brief   This file contains all the Macro Definitions of the ETH driver
 *          library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
   2020-07-03       Yangjp          Optimize stc_eth_mac_init_t structure
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_ETH_H__
#define __HC32F4A0_ETH_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_ETH
 * @{
 */

#if (DDL_ETH_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ETH_Global_Types ETH Global Types
 * @{
 */

/**
 * @brief ETH Common Initialization Structure Definition
 */
typedef struct
{
    uint16_t u16AutoNegotiation;                /*!< Specifies the Auto Negotiation mode for the external PHY.
                                                     This parameter can be a value of @ref ETH_Auto_Negotiation */

    uint16_t u16PHYAddress;                     /*!< Specifies the Ethernet PHY address.
                                                     This parameter must be a number between Min_Data = 0 and Max_Data = 31 */

    uint8_t  au8MACAddr[6];                     /*!< Specifies the MAC Address of used Hardware */

    uint32_t u32MediaInterface;                 /*!< Specifies the media interface.
                                                     This parameter can be a value of @ref ETH_Media_Interface */

    uint32_t u32Speed;                          /*!< Specifies the Ethernet speed.
                                                     This parameter can be a value of @ref ETH_Speed */

    uint32_t u32DuplexMode;                     /*!< Specifies the MAC duplex mode.
                                                     This parameter can be a value of @ref ETH_Duplex_Mode */

    uint32_t u32ChecksumMode;                   /*!< Specifies the checksum check by hardware or by software.
                                                     This parameter can be a value of @ref ETH_Checksum_Mode */

    uint32_t u32RxMode;                         /*!< Specifies the Ethernet Rx mode.
                                                     This parameter can be a value of @ref ETH_Rx_Mode */
} stc_eth_comm_init_t;

/**
 * @brief ETH MAC Initialization Structure Definition
 */
typedef struct
{
    uint32_t u32TxClkPolarity;                  /*!< Specifies the Tx clock polarity.
                                                     This parameter can be a value of @ref ETH_TX_CLK_POLARITY */

    uint32_t u32RxRefClkPolarity;               /*!< Specifies the Rx/Ref clock polarity.
                                                     This parameter can be a value of @ref ETH_RX_REF_CLK_POLARITY */

    uint32_t u32SAInsertMode;                   /*!< Specifies the Source Address Insert or Replace Mode.
                                                     This parameter can be a value of @ref ETH_SA_Insert_Mode */

    uint32_t u32TypeFrameStripFCS;              /*!< Specifies the validity of stripping FCS for type frame.
                                                     This parameter can be a value of @ref ETH_TypeFrame_Strip_FCS */

    uint32_t u32Watchdog;                       /*!< Specifies the validity of the Watchdog timer.
                                                     This parameter can be a value of @ref ETH_Watchdog */

    uint32_t u32Jabber;                         /*!< Specifies the validity of the Jabber timer.
                                                     This parameter can be a value of @ref ETH_Jabber */

    uint32_t u32InterFrameGap;                  /*!< Specifies the minimum gap between frames during transmission.
                                                     This parameter can be a value of @ref ETH_Inter_Frame_Gap */

    uint32_t u32CarrierSense;                   /*!< Specifies the validity of the Carrier Sense (Half-Duplex mode).
                                                     This parameter can be a value of @ref ETH_Carrier_Sense */

    uint32_t u32ReceiveOwn;                     /*!< Specifies the validity of the Receive Own (Half-Duplex mode).
                                                     This parameter can be a value of @ref ETH_Receive_Own */

    uint32_t u32ChecksumOffload;                /*!< Specifies the validity of the IPv4 checksum Offload.
                                                     This parameter can be a value of @ref ETH_Checksum_Offload */

    uint32_t u32RetryTransmit;                  /*!< Specifies the validity of the MAC attempt to retry Transmit (Half-Duplex mode).
                                                     This parameter can be a value of @ref ETH_Retry_Transmit */

    uint32_t u32AutoStripPadFCS;                /*!< Specifies the validity of the Automatic Stripping Pad/FCS of MAC.
                                                     This parameter can be a value of @ref ETH_Auto_Strip_Pad_FCS */

    uint32_t u32BackOffLimit;                   /*!< Specifies the BackOff limit value (Half-Duplex mode).
                                                     This parameter can be a value of @ref ETH_Back_Off_Limit */

    uint32_t u32DeferralCheck;                  /*!< Specifies the validity of the deferral check (Half-Duplex mode).
                                                     This parameter can be a value of @ref ETH_Deferral_Check */

    uint16_t u16PauseTime;                      /*!< Specifies the Pause Time in the transmit control frame.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFF */

    uint32_t u32ZeroQuantaPause;                /*!< Specifies the validity of the automatic generation Zero-Quanta Pause Control frame.
                                                     This parameter can be a value of @ref ETH_Zero_Quanta_Pause */

    uint32_t u32PauseLowThreshold;              /*!< Specifies the PAUSE Frame threshold.
                                                     This parameter can be a value of @ref ETH_Pause_Low_Threshold */

    uint32_t u32UnicastPauseFrameDetect;        /*!< Specifies the validity of the detection unicast Pause frame.
                                                     This parameter can be a value of @ref ETH_Unicast_Pause_Frame_Detect */

    uint32_t u32ReceiveFlowControl;             /*!< Specifies the validity of the decoding function that receive Pause frame.
                                                     This parameter can be a value of @ref ETH_Receive_Flow_Control */

    uint32_t u32TransmitFlowControl;            /*!< Specifies the validity of the MAC transmit Pause frame (Full-Duplex mode) or the MAC back-pressure operation (Half-Duplex mode).
                                                     This parameter can be a value of @ref ETH_Transmit_Flow_Control */

    uint32_t u32ReceiveAll;                     /*!< Specifies the validity of the all frames reception by the MAC (No filtering).
                                                     This parameter can be a value of @ref ETH_Receive_All */

    uint32_t u32DropNotTcpUdp;                  /*!< Specifies the validity of Dropping all IP datagram without TCP/UDP field.
                                                     This parameter can be a value of @ref ETH_Drop_Not_TcpUdp */

    uint32_t u32VlanTagFilter;                  /*!< Specifies the validity of the VLAN Tag Filter.
                                                     This parameter can be a value of @ref ETH_VLAN_Tag_Filter */

    uint32_t u32SAFilter;                       /*!< Specifies the Source Address Filter mode.
                                                     This parameter can be a value of @ref ETH_Source_Addr_Filter */

    uint32_t u32PassControlFrame;               /*!< Specifies the forwarding mode of the control frame.
                                                     This parameter can be a value of @ref ETH_Pass_Control_Frame */

    uint32_t u32BroadcastFrameReception;        /*!< Specifies the validity of the reception Broadcast Frame.
                                                     This parameter can be a value of @ref ETH_Broadcast_Frame_Reception */

    uint32_t u32DAFilter;                       /*!< Specifies the destination filter mode for both unicast and multicast frame.
                                                     This parameter can be a value of @ref ETH_Destination_Addr_Filter */

    uint32_t u32MulticastFrameFilter;           /*!< Specifies the Multicast Frame filter mode.
                                                     This parameter can be a value of @ref ETH_Multicast_Frame_Filter */

    uint32_t u32UnicastFrameFilter;             /*!< Specifies the Unicast Frame filter mode.
                                                     This parameter can be a value of @ref ETH_Unicast_Frame_Filter */

    uint32_t u32PromiscuousMode;                /*!< Specifies the validity of the Promiscuous Mode.
                                                     This parameter can be a value of @ref ETH_Promiscuous_Mode */

    uint32_t u32HashTableHigh;                  /*!< Specifies the higher 32 bits of Hash table.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */

    uint32_t u32HashTableLow;                   /*!< Specifies the lower 32 bits of Hash table.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */

    uint32_t u32TxVlanInsertMode;               /*!< Specifies the VLAN insert mode in Transmit frame.
                                                     This parameter can be a value of @ref ETH_Tx_VLAN_Insert_Mode */

    uint16_t u16TxVlanTag;                      /*!< Specifies the VLAN tag value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFF */

    uint32_t u32RxVlanFilter;                   /*!< Specifies the VLAN filter mode in Receive frame.
                                                     This parameter can be a value of @ref ETH_Rx_VLAN_Filter */

    uint32_t u32RxVlanComparison;               /*!< Specifies the bits for comparison VLAN tag.
                                                     This parameter can be a value of @ref ETH_Rx_VLAN_Comparison */

    uint16_t u16RxVlanTag;                      /*!< Specifies the VLAN tag value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFF */

    uint16_t u16RxVlanHashTable;                /*!< Specifies the lower 16 bits of VLAN Hash table.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFF */
} stc_eth_mac_init_t;

/**
 * @brief ETH DMA Initialization Structure Definition
 */
typedef struct
{
    uint32_t u32BurstMode;                      /*!< Specifies the AHB Master interface burst transmission Mode.
                                                     This parameter can be a value of @ref ETH_Burst_Mode */

    uint32_t u32AddressAlign;                   /*!< Specifies the validity of the Address Align.
                                                     This parameter can be a value of @ref ETH_Address_Align */

    uint32_t u32RxDMABurstLength;               /*!< Specifies the maximum number of beats to be transferred in one Rx DMA transaction.
                                                     This parameter can be a value of @ref ETH_Rx_DMA_Burst_Length */

    uint32_t u32TxDMABurstLength;               /*!< Specifies the maximum number of beats to be transferred in one Tx DMA transaction.
                                                     This parameter can be a value of @ref ETH_Tx_DMA_Burst_Length */

    uint32_t u32EnhanceDescriptor;              /*!< Specifies the validity of the enhance descriptor format.
                                                     This parameter can be a value of @ref ETH_DMA_Enhance_Descriptor */

    uint32_t u32DescriptorSkipLength;           /*!< Specifies the number of word to skip between two unchain descriptors (Ring mode)
                                                     This parameter must be a number between Min_Data = 0 and Max_Data = 31 */

    uint32_t u32DMAArbitration;                 /*!< Specifies the DMA Tx/Rx arbitration.
                                                     This parameter can be a value of @ref ETH_DMA_Arbitration */

    uint32_t u32DropChecksumErrorFrame;         /*!< Specifies the validity of Dropping TCP/IP Checksum Error Frame.
                                                     This parameter can be a value of @ref ETH_Drop_TCPIP_Checksum_Error_Frame */

    uint32_t u32ReceiveStoreForward;            /*!< Specifies the validity of the Receive store and forward mode.
                                                     This parameter can be a value of @ref ETH_Receive_Store_Forward */

    uint32_t u32FlushReceiveFrame;              /*!< Specifies the validity of the flushing receive frame.
                                                     This parameter can be a value of @ref ETH_Flush_Receive_Frame */

    uint32_t u32TransmitStoreForward;           /*!< Specifies the validity of the Transmit store and forward mode.
                                                     This parameter can be a value of @ref ETH_Transmit_Store_Forward */

    uint32_t u32TransmitThreshold;              /*!< Specifies the Transmit Threshold.
                                                     This parameter can be a value of @ref ETH_Transmit_Threshold */

    uint32_t u32ForwardErrorFrame;              /*!< Specifies the validity of the forward erroneous frame.
                                                     This parameter can be a value of @ref ETH_Forward_Error_Frame */

    uint32_t u32ForwardUndersizeGoodFrame;     /*!< Specifies the validity of the Rx FIFO to forward Undersize frame.
                                                     This parameter can be a value of @ref ETH_Forward_Undersize_Good_Frame */

    uint32_t u32DropJumboFrame;                 /*!< Specifies the validity of Dropping jumbo Frame.
                                                     This parameter can be a value of @ref ETH_Drop_Jumbo_Frame */

    uint32_t u32ReceiveThreshold;               /*!< Specifies the threshold level of the Receive FIFO.
                                                     This parameter can be a value of @ref ETH_Receive_Threshold */

    uint32_t u32SecondFrameOperate;             /*!< Specifies the validity of the Operate on second frame mode.
                                                     This parameter can be a value of @ref ETH_Second_Frame_Operate */
} stc_eth_dma_init_t;

/**
 * @brief ETH MMC Initialization Structure Definition
 */
typedef struct
{
    uint32_t u32PresetMode;                     /*!< Specifies the MMC Counter preset mode.
                                                     This parameter can be a value of @ref ETH_MMC_Counter_Preset_Mode */

    uint32_t u32ReadReset;                      /*!< Specifies the validity of the MMC Reset on read.
                                                     This parameter can be a value of @ref ETH_MMC_Read_Reset */

    uint32_t u32ReloadMode;                     /*!< Specifies the validity of the MMC Counter reload.
                                                     This parameter can be a value of @ref ETH_MMC_Counter_Reload */
} stc_eth_mmc_init_t;

/**
 * @brief ETH PTP Initialization Structure Definition
 */
typedef struct
{
    uint32_t u32DAFilter;                       /*!< Specifies the validity of the DA filter for the PTP frame.
                                                     This parameter can be a value of @ref ETH_PTP_Frame_DA_Filter */

    uint32_t u32SnapDatagramType;               /*!< Specifies the PTP snapshot datagram type.
                                                     This parameter can be a value of @ref ETH_PTP_Snapshot_Datagram_Type */

    uint32_t u32SnapFrameType;                  /*!< Specifies the PTP snapshot frame type.
                                                     This parameter can be any combination of @ref ETH_PTP_Snapshot_Frame_Type */

    uint32_t u32DatagramVersion;                /*!< Specifies the PTP datagram version.
                                                     This parameter can be a value of @ref ETH_PTP_Datagram_Version */

    uint32_t u32SubSecScale;                    /*!< Specifies the PTP Time Stamp subsecond scale.
                                                     This parameter can be a value of @ref ETH_PTP_Subsecond_Scale */

    uint32_t u32CalibMode;                      /*!< Specifies the PTP Time Stamp calibration mode.
                                                     This parameter can be a value of @ref ETH_PTP_Calibration_Mode */

    uint32_t u32IncValueBasic;                  /*!< Specifies the PTP Time Stamp Basic increase value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */

    uint8_t  u8IncValueSubSec;                  /*!< Specifies the PTP Time Stamp Subsecond increase value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFF */

    uint32_t u32InitValueSec;                   /*!< Specifies the PTP Time Stamp Second Initial value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */

    uint32_t u32InitValueSubSec;                /*!< Specifies the PTP Time Stamp Subsecond Initial value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0x7FFFFFFF */
} stc_eth_ptp_init_t;

/**
 * @brief ETH PPS Configuration Structure Definition
 */
typedef struct
{
    uint32_t u32TargetTimeFunc;                 /*!< Specifies the arrival time trigger the function.
                                                     This parameter can be a value of @ref ETH_PPS_Target_Time_Function */

    uint32_t u32OutputMode;                     /*!< Specifies the PPS output mode.
                                                     This parameter can be a value of @ref ETH_PPS_Output_Mode */

    uint32_t u32OutputFreq;                     /*!< Specifies the PPS outout frequency.
                                                     This parameter can be any combination of @ref ETH_PPS_Output_Frequency */

    uint32_t u32TargetTimeSec;                  /*!< Specifies the PPS Target Time for Second.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */

    uint32_t u32TargetTimeSubSec;               /*!< Specifies the PPS Target Time for Subsecond.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0x7FFFFFFF */
} stc_eth_pps_config_t;

/**
 * @brief ETH DMA Descriptor Structure Definition
 */
typedef struct
{
    __IO uint32_t u32ControlStatus;             /*!< Control and Status */
    uint32_t      u32ControlBufferSize;         /*!< Control and Buffer1, Buffer2 lengths */
    uint32_t      u32Buffer1Addr;               /*!< Buffer1 address pointer */
    uint32_t      u32Buffer2NextDescAddr;       /*!< Buffer2 or next descriptor address pointer */
    /*!< Enhance Ethernet DMA Descriptors */
    __IO uint32_t u32ExtendStatus;              /*!< Extend status */
    uint32_t      Reserved;                     /*!< Reserved */
    uint32_t      u32TimeStampLow;              /*!< Time Stamp Low value for transmit and receive */
    uint32_t      u32TimeStampHigh;             /*!< Time Stamp High value for transmit and receive */
} stc_eth_dma_desc_t;

/**
 * @brief ETH DMA Received Frame Structure Definition
 */
typedef struct
{
    stc_eth_dma_desc_t *pstcFSDesc;             /*!< First Segment Rx Desc */
    stc_eth_dma_desc_t *pstcLSDesc;             /*!< Last Segment Rx Desc  */
    uint32_t           u32SegCount;             /*!< Segment count         */
    uint32_t           u32Length;               /*!< Frame length          */
    uint32_t           u32Buffer;               /*!< Frame buffer          */
} stc_eth_dma_rx_frame_t;

/**
 * @brief ETH Initialization Structure Definition
 */
typedef struct
{
    stc_eth_mac_init_t stcMacInit;              /*!< Ethernet MAC Initialization */
    stc_eth_dma_init_t stcDmaInit;              /*!< Ethernet DMA Initialization */
} stc_eth_init_t;

/**
 * @brief ETH Handle Structure Definition
 */
typedef struct
{
    stc_eth_comm_init_t     stcCommInit;        /*!< ETH Common Initialization */
    stc_eth_dma_desc_t      *stcRxDesc;         /*!< Rx descriptor to Get */
    stc_eth_dma_desc_t      *stcTxDesc;         /*!< Tx descriptor to Set */
    stc_eth_dma_rx_frame_t  stcRxFrame;         /*!< last Rx frame */
} stc_eth_handle_t;

/**
 * @brief ETH MAC Address Configuration Structure Definition
 */
typedef struct
{
    uint32_t u32MacAddrFilter;                  /*!< Specifies the MAC Address filter mode.
                                                     This parameter can be a value of @ref ETH_MAC_Address_Filter */

    uint32_t u32MacAddrMask;                    /*!< Specifies the MAC Address filter Mask.
                                                     This parameter can be a value of @ref ETH_MAC_Address_Filter_Mask */

    uint8_t  au8MACAddr[6];                     /*!< Specifies the MAC Address of used Hardware */
} stc_eth_mac_addr_config_t;

/**
 * @brief ETH L3L4 Filter Configuration Structure Definition
 */
typedef struct
{
    uint32_t u32L4DestPortFilter;               /*!< Specifies the L4 Destination port filter mode.
                                                     This parameter can be a value of @ref ETH_L4_Dest_Port_Filter */

    uint32_t u32L4SourcePortFilter;             /*!< Specifies the L4 Source port filter mode.
                                                     This parameter can be a value of @ref ETH_L4_Source_Port_Filter */

    uint32_t u32L4PortFilterProtocol;           /*!< Specifies the L4 protocol for port filter operation.
                                                     This parameter can be a value of @ref ETH_L4_Port_Filter_Protocol */

    uint32_t u32L3Ipv4DAFilterMask;             /*!< Specifies the L3 Destination Address filter mask in IPv4.
                                                     This parameter can be a value of @ref ETH_L3_Dest_Addr_Filter_Mask */

    uint32_t u32L3Ipv4SAFilterMask;             /*!< Specifies the L3 Source Address filter Mask in IPv4.
                                                     This parameter can be a value of @ref ETH_L3_Source_Addr_Filter_Mask */

    uint32_t u32L3Ipv6AddrFilterMask;           /*!< Specifies the L3 Destination/Source Address filter Mask in IPv6.
                                                     This parameter can be a value of @ref ETH_L3_DA_SA_Filter_Mask */

    uint32_t u32L3DAFilter;                     /*!< Specifies the L3 Destination Address filter mode.
                                                     This parameter can be a value of @ref ETH_L3_Dest_Addr_Filter */

    uint32_t u32L3SAFilter;                     /*!< Specifies the L3 Source Address filter mode.
                                                     This parameter can be a value of @ref ETH_L3_Source_Addr_Filter */

    uint32_t u32L3AddrFilterProtocol;           /*!< Specifies the L3 protocol for address filter operation.
                                                     This parameter can be a value of @ref ETH_L3_Addr_Filter_Protocol */

    uint16_t u16L4DestProtFilterValue;          /*!< Specifies the L4 Destination port filter value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFF */

    uint16_t u16L4SourceProtFilterValue;        /*!< Specifies the L4 Source port filter value.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFF */

    uint32_t u32L3Ipv4DAFilterValue;            /*!< Specifies the L3 Destination Address filter value in IPv4.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */

    uint32_t u32L3Ipv4SAFilterValue;            /*!< Specifies the L3 Source Address filter value in IPv4.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */

    uint32_t au32L3Ipv6AddrFilterValue[4];      /*!< Specifies the L3 Destination/Source Address filter value in IPv6.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFF */
} stc_eth_l3l4_filter_config_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ETH_Global_Macros ETH Global Macros
 * @{
 */

/**
 * @defgroup ETH_Buffer_Define ETH Buffer Define
 * @{
 */
#define ETH_PACKET_MAX_SIZE           (1524U)   /*!< ETH_HEADER + ETH_EXTRA + ETH_VLAN_TAG + ETH_MAX_PAYLOAD + ETH_CRC */
#define ETH_HEADER                    (14U)     /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC                       (4U)      /*!< Ethernet CRC */
#define ETH_EXTRA                     (2U)      /*!< Extra bytes in some cases */
#define ETH_VLAN_TAG                  (4U)      /*!< Optional 802.1Q VLAN Tag */
#define ETH_MIN_PAYLOAD               (46U)     /*!< Ethernet minimum payload size */
#define ETH_MAX_PAYLOAD               (1500U)   /*!< Ethernet maximum payload size */
#define ETH_JUMBO_FRAME_PAYLOAD       (9000U)   /*!< Jumbo frame payload size */

/* In below are defined the size of one Ethernet driver transmit buffer ETH_TXBUF_SIZE
   and the total count of the driver transmit buffers ETH_TXBUF_NUMBER.

   The configured value for ETH_TXBUF_SIZE and ETH_TXBUF_NUMBER are only provided as
   example, they can be reconfigured in the application layer to fit the application
   needs */

/* Configure the transmit buffer size for each Ethernet driver */
#ifndef ETH_TXBUF_SIZE
  #define ETH_TXBUF_SIZE              ETH_PACKET_MAX_SIZE
#endif

/* Configure the number of Ethernet driver transmit buffers (in a chained linked list)*/
#ifndef ETH_TXBUF_NUMBER
 #define ETH_TXBUF_NUMBER             (5U)      /* 5 Tx buffers of size ETH_TXBUF_SIZE */
#endif

/* In below are defined the size of one Ethernet driver receive buffer ETH_RXBUF_SIZE
   and the total count of the driver receive buffers ETH_RXBUF_NUMBER.

   The configured value for ETH_RXBUF_SIZE and ETH_RXBUF_NUMBER are only provided as
   example, they can be reconfigured in the application layer to fit the application
   needs */

/* Configure the receive buffer size for each Ethernet driver */
#ifndef ETH_RXBUF_SIZE
  #define ETH_RXBUF_SIZE              ETH_PACKET_MAX_SIZE
#endif

/* Configure the number of Ethernet drive receive buffers (in a chained linked list)*/
#ifndef ETH_RXBUF_NUMBER
  #define ETH_RXBUF_NUMBER            (5U)      /* 5 Rx buffers of size ETH_RXBUF_SIZE */
#endif

/**
 * @}
 */

/**
 * @defgroup ETH_DMA_TX_Descriptor ETH DMA TX Descriptor
 * @{
 */

/*
  Normal DMA Tx Descriptor
  -----------------------------------------------------------------------------------------------
  TDES0 | OWN(31)  |  CTRL[30:26]  |  TTSE(25)  |  CTRL[24:18]  |  TTSS(17)  |  Status[16:0]     |
  -----------------------------------------------------------------------------------------------
  TDES1 | CTRL[31:29] | Buffer2 ByteCount[28:16] | Reserved[15:13] | Buffer1 ByteCount[12:0]     |
  -----------------------------------------------------------------------------------------------
  TDES2 |                         Buffer1 Address [31:0]                                         |
  -----------------------------------------------------------------------------------------------
  TDES3 |                   Buffer2 Address [31:0] / Next Descriptor Address [31:0]              |
  -----------------------------------------------------------------------------------------------
 */

/**
 * @brief Bit definition of TDES0 register
 */
#define ETH_DMATXDESC_OWN                           (0x80000000UL)  /*!< OWN bit */
#define ETH_DMATXDESC_IOC                           (0x40000000UL)  /*!< Interrupt on Completion */
#define ETH_DMATXDESC_TLS                           (0x20000000UL)  /*!< Transmit Last Segment */
#define ETH_DMATXDESC_TFS                           (0x10000000UL)  /*!< Transmit First Segment */
#define ETH_DMATXDESC_DCRC                          (0x08000000UL)  /*!< Disable CRC */
#define ETH_DMATXDESC_DPAD                          (0x04000000UL)  /*!< Disable Padding */
#define ETH_DMATXDESC_TTSE                          (0x02000000UL)  /*!< Transmit Time Stamp Enable */
#define ETH_DMATXDESC_CRCR                          (0x01000000UL)  /*!< CRC Replace Control */
#define ETH_DMATXDESC_CIC                           (0x00C00000UL)  /*!< Checksum Insertion Control: 4 cases */
#define ETH_DMATXDESC_CIC_BYPASS                    (0x00000000UL)  /*!< Do Nothing: Checksum Engine is bypassed */
#define ETH_DMATXDESC_CIC_IPV4HEADER                (0x00400000UL)  /*!< IPV4 header Checksum Insertion */
#define ETH_DMATXDESC_CIC_TCPUDPICMP_SEGMENT        (0x00800000UL)  /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define ETH_DMATXDESC_CIC_TCPUDPICMP_FULL           (0x00C00000UL)  /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */
#define ETH_DMATXDESC_TER                           (0x00200000UL)  /*!< Transmit End of Ring */
#define ETH_DMATXDESC_TSAC                          (0x00100000UL)  /*!< Second Address Chained */
#define ETH_DMATXDESC_VLANC                         (0x000C0000UL)  /*!< VLAN Insertion Control: 4 cases */
#define ETH_DMATXDESC_VLANC_BYPASS                  (0x00000000UL)  /*!< Do Nothing: VLAN Insertion is bypassed */
#define ETH_DMATXDESC_VLANC_REMOVE_TAG              (0x00040000UL)  /*!< Remove Tag and Type fields in VLAN frame */
#define ETH_DMATXDESC_VLANC_INSERT_TAG              (0x00080000UL)  /*!< Insert VLAN Tag value in ETH_MAC_VTACTLR Register into transmit frame */
#define ETH_DMATXDESC_VLANC_REPLACE_TAG             (0x000C0000UL)  /*!< Replace VLAN tag value in transmit frame with VLAN tag value in ETH_MAC_VTACTLR register */
#define ETH_DMATXDESC_TTSS                          (0x00020000UL)  /*!< Tx Time Stamp Status */
#define ETH_DMATXDESC_IHE                           (0x00010000UL)  /*!< IP Header Error */
#define ETH_DMATXDESC_ETSUM                         (0x00008000UL)  /*!< Tx Error summary: OR of the following bits: IHE || JTE || FFF || TPCE || LOCE || NCE || TLCE || ECE || EDE || UDE */
#define ETH_DMATXDESC_JTE                           (0x00004000UL)  /*!< Jabber Timeout Error */
#define ETH_DMATXDESC_FFF                           (0x00002000UL)  /*!< Frame Flushed */
#define ETH_DMATXDESC_TPCE                          (0x00001000UL)  /*!< Payload Checksum Error */
#define ETH_DMATXDESC_LOCE                          (0x00000800UL)  /*!< Loss Carrier Error */
#define ETH_DMATXDESC_NCE                           (0x00000400UL)  /*!< No Carrier Error */
#define ETH_DMATXDESC_TLCE                          (0x00000200UL)  /*!< Late Collision Error */
#define ETH_DMATXDESC_ECE                           (0x00000100UL)  /*!< Excessive Collision Error */
#define ETH_DMATXDESC_VLF                           (0x00000080UL)  /*!< VLAN Frame */
#define ETH_DMATXDESC_COC                           (0x00000078UL)  /*!< Collision Count */
#define ETH_DMATXDESC_EDE                           (0x00000004UL)  /*!< Excessive Deferral Error */
#define ETH_DMATXDESC_UDE                           (0x00000002UL)  /*!< Underflow Error */
#define ETH_DMATXDESC_DEE                           (0x00000001UL)  /*!< Deferred Error */

/**
 * @brief Bit definition of TDES1 register
 */
#define ETH_DMATXDESC_SAIRC                         (0xE0000000UL)  /*!< Source Address Insertion or Replace Control: 5 cases */
#define ETH_DMATXDESC_SAIRC_BYPASS                  (0x00000000UL)  /*!< Do Nothing: Source Address Insertion or Replace Control is bypassed */
#define ETH_DMATXDESC_SAIRC_INSTER_MACADDR0         (0x20000000UL)  /*!< Insert address value in MAC address register 0 into transmit frame as SA address */
#define ETH_DMATXDESC_SAIRC_REPLACE_MACADDR0        (0x40000000UL)  /*!< Replace SA address in transmit frame with address value in MAC address register 0 */
#define ETH_DMATXDESC_SAIRC_INSTER_MACADDR1         (0xA0000000UL)  /*!< Insert address value in MAC address register 1 into transmit frame as SA address */
#define ETH_DMATXDESC_SAIRC_REPLACE_MACADDR1        (0xC0000000UL)  /*!< Replace SA address in transmit frame with address value in MAC address register 1 */
#define ETH_DMATXDESC_TBS2                          (0x1FFF0000UL)  /*!< Transmit Buffer2 Size */
#define ETH_DMATXDESC_TBS1                          (0x00001FFFUL)  /*!< Transmit Buffer1 Size */

/**
 * @brief Bit definition of TDES2 register
 */
#define ETH_DMATXDESC_TBAP1                         (0xFFFFFFFFUL)  /*!< Buffer1 Address Pointer */

/**
 * @brief Bit definition of TDES3 register
 */
#define ETH_DMATXDESC_TBAP2                         (0xFFFFFFFFUL)  /*!< Buffer2 Address Pointer */

/*
  Enhance DMA Tx Descriptor
  -----------------------------------------------------------------------------------------------
  TDES4 |                                Reserved[31:0]                                          |
  -----------------------------------------------------------------------------------------------
  TDES5 |                                Reserved[31:0]                                          |
  -----------------------------------------------------------------------------------------------
  TDES6 |                         Transmit Time Stamp Low [31:0]                                 |
  -----------------------------------------------------------------------------------------------
  TDES7 |                         Transmit Time Stamp High [31:0]                                |
  -----------------------------------------------------------------------------------------------
 */

/**
 * @brief Bit definition of TDES6 register
 */
 #define ETH_DMATXDESC_TTSL                         (0xFFFFFFFFUL)  /*!< Transmit Time Stamp Low */

/**
 * @brief Bit definition of TDES7 register
 */
 #define ETH_DMATXDESC_TTSH                         (0xFFFFFFFFUL)  /*!< Transmit Time Stamp High */

/**
 * @}
 */

/**
 * @defgroup ETH_DMA_RX_Descriptor ETH DMA RX Descriptor
 * @{
 */

/*
  Normal DMA Rx Descriptor
  --------------------------------------------------------------------------------------------------------------------
  RDES0 | OWN(31) |                                             Status [30:0]                                          |
  ---------------------------------------------------------------------------------------------------------------------
  RDES1 | CTRL(31) | Reserved[30:29] | Buffer2 ByteCount[28:16] | CTRL[15:14] | Reserved(13) | Buffer1 ByteCount[12:0] |
  ---------------------------------------------------------------------------------------------------------------------
  RDES2 |                                       Buffer1 Address [31:0]                                                 |
  ---------------------------------------------------------------------------------------------------------------------
  RDES3 |                          Buffer2 Address [31:0] / Next Descriptor Address [31:0]                             |
  ---------------------------------------------------------------------------------------------------------------------
*/

/**
 * @brief Bit definition of RDES0 register
 */
#define ETH_DMARXDESC_OWN                           (0x80000000UL)  /*!< OWN bit */
#define ETH_DMARXDESC_DAF                           (0x40000000UL)  /*!< DA Filter Fail for the received frame */
#define ETH_DMARXDESC_FRAL                          (0x3FFF0000UL)  /*!< Receive frame length */
#define ETH_DMARXDESC_ERSUM                         (0x00008000UL)  /*!< Rx Error summary: OR of the following bits: DPE || OVE || IPE_TSPA_GF || RLCE || WTE || REE || CRE in RDES0, or IPPE || IPHE in RDES4 */
#define ETH_DMARXDESC_DPE                           (0x00004000UL)  /*!< Descriptor Error: no more descriptors for receive frame */
#define ETH_DMARXDESC_SAF                           (0x00002000UL)  /*!< SA Filter Fail for the received frame */
#define ETH_DMARXDESC_LEE                           (0x00001000UL)  /*!< Length Error: Frame size not matching with length field */
#define ETH_DMARXDESC_OVE                           (0x00000800UL)  /*!< Overflow Error: Frame was damaged due to buffer overflow */
#define ETH_DMARXDESC_VLAT                          (0x00000400UL)  /*!< VLAN Tag: received frame is a VLAN frame */
#define ETH_DMARXDESC_RFS                           (0x00000200UL)  /*!< First descriptor */
#define ETH_DMARXDESC_RLS                           (0x00000100UL)  /*!< Last descriptor */
#define ETH_DMARXDESC_IPE_TSPA_GF                   (0x00000080UL)  /*!< COE Error or Time stamp valid or jumbo frame */
#define ETH_DMARXDESC_RLCE                          (0x00000040UL)  /*!< Late collision Error */
#define ETH_DMARXDESC_FRAT                          (0x00000020UL)  /*!< Frame type: Ethernet or PTP */
#define ETH_DMARXDESC_WTE                           (0x00000010UL)  /*!< Receive Watchdog Timeout */
#define ETH_DMARXDESC_REE                           (0x00000008UL)  /*!< Receive error: error reported by PHY RX_ER */
#define ETH_DMARXDESC_DBE                           (0x00000004UL)  /*!< Dribble bit error: frame contains non int multiple of 8 bits  */
#define ETH_DMARXDESC_CRE                           (0x00000002UL)  /*!< CRC error */
#define ETH_DMARXDESC_DAS_ESA                       (0x00000001UL)  /*!< MAC Address Filter/Status bit extension */

/**
 * @brief Bit definition of RDES1 register
 */
#define ETH_DMARXDESC_DIC                           (0x80000000UL)  /*!< Disable Interrupt on Completion */
#define ETH_DMARXDESC_RBS2                          (0x1FFF0000UL)  /*!< Receive Buffer2 Size */
#define ETH_DMARXDESC_RER                           (0x00008000UL)  /*!< Receive End of Ring */
#define ETH_DMARXDESC_RSAC                          (0x00004000UL)  /*!< Second Address Chained */
#define ETH_DMARXDESC_RBS1                          (0x00001FFFUL)  /*!< Receive Buffer1 Size */

/**
 * @brief Bit definition of RDES2 register
 */
#define ETH_DMARXDESC_RBAP1                         (0xFFFFFFFFUL)  /*!< Buffer1 Address Pointer */

/**
 * @brief Bit definition of RDES3 register
 */
#define ETH_DMARXDESC_RBAP2                         (0xFFFFFFFFUL)  /*!< Buffer2 Address Pointer */

/*
  Enhance DMA Rx Descriptor
  -----------------------------------------------------------------------------------------------
  RDES4 |    Reserved[31:26] | Extend Status [25:24] | Reserved[23:15] | Extend Status [14:0]    |
  -----------------------------------------------------------------------------------------------
  RDES5 |                                    Reserved[31:0]                                      |
  -----------------------------------------------------------------------------------------------
  RDES6 |                               Receive Time Stamp Low [31:0]                            |
  -----------------------------------------------------------------------------------------------
  RDES7 |                               Receive Time Stamp High [31:0]                           |
  -----------------------------------------------------------------------------------------------
*/

/**
 * @brief Bit definition of RDES4 register
 */
#define ETH_DMARXDESC_L4FMS                         (0x02000000UL)  /*!< L4 Port Filter Status */
#define ETH_DMARXDESC_L3FMS                         (0x01000000UL)  /*!< L3 Address Filter Status */
#define ETH_DMARXDESC_TSPD                          (0x00004000UL)  /*!< Discard Time Stamp */
#define ETH_DMARXDESC_PTPV                          (0x00002000UL)  /*!< PTP Version */
#define ETH_DMARXDESC_PTPFT                         (0x00001000UL)  /*!< PTP Frame Type */
#define ETH_DMARXDESC_MTP                           (0x00000F00UL)  /*!< PTP Datagram Type */
#define ETH_DMARXDESC_MTP_NONE                      (0x00000000UL)  /*!< No PTP messages */
#define ETH_DMARXDESC_MTP_SYNC                      (0x00000100UL)  /*!< SYNC message (all clock types) */
#define ETH_DMARXDESC_MTP_FOLLOWUP                  (0x00000200UL)  /*!< Follow_Up message (all clock types) */
#define ETH_DMARXDESC_MTP_DELAYREQ                  (0x00000300UL)  /*!< Delay_Req message (all clock types) */
#define ETH_DMARXDESC_MTP_DELAYRESP                 (0x00000400UL)  /*!< Delay_Resp message (all clock types) */
#define ETH_DMARXDESC_MTP_PDELAYREQ                 (0x00000500UL)  /*!< Pdelay_Req message (peer-to-peer transparent clock) */
#define ETH_DMARXDESC_MTP_PDELAYRESP                (0x00000600UL)  /*!< Pdelay_Resp message (peer-to-peer transparent clock) */
#define ETH_DMARXDESC_MTP_PDELAYRESP_FOLLOWUP       (0x00000700UL)  /*!< Pdelay_Resp_Follow_Up message (peer-to-peer transparent clock) */
#define ETH_DMARXDESC_MTP_ANNOUNCE                  (0x00000800UL)  /*!< Announce message (Ordinary or Boundary clock) */
#define ETH_DMARXDESC_MTP_MANAGEMENT                (0x00000900UL)  /*!< Management message (Ordinary or Boundary clock) */
#define ETH_DMARXDESC_MTP_SIGNALING                 (0x00000A00UL)  /*!< Signaling message (Ordinary or Boundary clock) */
#define ETH_DMARXDESC_MTP_DEFAULT                   (0x00000F00UL)  /*!< Default Datagram Type */
#define ETH_DMARXDESC_IPV6DR                        (0x00000080UL)  /*!< IPv6 Packet Received */
#define ETH_DMARXDESC_IPV4DR                        (0x00000040UL)  /*!< IPv4 Packet Received */
#define ETH_DMARXDESC_IPCB                          (0x00000020UL)  /*!< COE engine Bypassed */
#define ETH_DMARXDESC_IPPE                          (0x00000010UL)  /*!< IP Payload Error */
#define ETH_DMARXDESC_IPHE                          (0x00000008UL)  /*!< IP Header Error */
#define ETH_DMARXDESC_IPPT                          (0x00000007UL)  /*!< IP Payload Type: 4 cases */
#define ETH_DMARXDESC_IPPT_UNKNOWN                  (0x00000000UL)  /*!< Unknown */
#define ETH_DMARXDESC_IPPT_UDP                      (0x00000001UL)  /*!< UDP */
#define ETH_DMARXDESC_IPPT_TCP                      (0x00000002UL)  /*!< TCP */
#define ETH_DMARXDESC_IPPT_ICMP                     (0x00000003UL)  /*!< ICMP */

/**
 * @brief Bit definition of RDES6 register
 */
#define ETH_DMARXDESC_RTSL                          (0xFFFFFFFFUL)  /*!< Receive Time Stamp Low */

/**
 * @brief Bit definition of RDES7 register
 */
#define ETH_DMARXDESC_RTSH                          (0xFFFFFFFFUL)  /*!< Receive Time Stamp High */

/**
 * @}
 */

/**
 * @defgroup ETH_Auto_Negotiation ETH Auto Negotiation
 * @{
 */
#define ETH_AUTO_NEGOTIATION_DISABLE                (0x0000U)
#define ETH_AUTO_NEGOTIATION_ENABLE                 (0x0001U)
/**
 * @}
 */

/**
 * @defgroup ETH_Media_Interface ETH Media Interface
 * @{
 */
#define ETH_MAC_MEDIA_INTERFACE_MII                 (0UL)
#define ETH_MAC_MEDIA_INTERFACE_RMII                (ETH_MAC_IFCONFR_IFSEL)
/**
 * @}
 */

/**
 * @defgroup ETH_Speed ETH Speed
 * @{
 */
#define ETH_MAC_SPEED_10M                           (0UL)
#define ETH_MAC_SPEED_100M                          (ETH_MAC_CONFIGR_FES)
/**
 * @}
 */

/**
 * @defgroup ETH_Duplex_Mode ETH Duplex Mode
 * @{
 */
#define ETH_MAC_MODE_HALFDUPLEX                     (0UL)
#define ETH_MAC_MODE_FULLDUPLEX                     (ETH_MAC_CONFIGR_DM)
/**
 * @}
 */

/**
 * @defgroup ETH_Checksum_Mode ETH Checksum Mode
 * @{
 */
#define ETH_MAC_CHECKSUM_MODE_SOFTWARE              (0UL)
#define ETH_MAC_CHECKSUM_MODE_HARDWARE              (0x00000001UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Rx_Mode ETH Rx Mode
 * @{
 */
#define ETH_RX_MODE_POLLING                         (0UL)
#define ETH_RX_MODE_INTERRUPT                       (0x00000001UL)
/**
 * @}
 */

/**
 * @defgroup ETH_TX_CLK_POLARITY ETH TX Clock Polarity
 * @{
 */
#define ETH_MAC_TX_CLK_POLARITY_KEEP                (0UL)
#define ETH_MAC_TX_CLK_POLARITY_INVERSE             (ETH_MAC_IFCONFR_TCKINV)
/**
 * @}
 */

/**
 * @defgroup ETH_RX_REF_CLK_POLARITY ETH RX/REF Clock Polarity
 * @{
 */
#define ETH_MAC_RX_REF_CLK_POLARITY_KEEP            (0UL)
#define ETH_MAC_RX_REF_CLK_POLARITY_INVERSE         (ETH_MAC_IFCONFR_RCKINV)
/**
 * @}
 */

/**
 * @defgroup ETH_SA_Insert_Mode ETH SA Insert Mode
 * @{
 */
#define ETH_MAC_SA_MODE_BY_DMATXDESC                (0UL)                                                 /*!< Configure the Insert mode by Tx Descriptor of DMA */
#define ETH_MAC_SA_MODE_INSTER_MACADDR0             (ETH_MAC_CONFIGR_SAIRC_1)                             /*!< Insert address value in MAC address register 0 into transmit frame as SA address */
#define ETH_MAC_SA_MODE_REPLACE_MACADDR0            (ETH_MAC_CONFIGR_SAIRC_1 | ETH_MAC_CONFIGR_SAIRC_0)   /*!< Replace SA address in transmit frame with address value in MAC address register 0 */
#define ETH_MAC_SA_MODE_INSTER_MACADDR1             (ETH_MAC_CONFIGR_SAIRC_2 | ETH_MAC_CONFIGR_SAIRC_1)   /*!< Insert address value in MAC address register 1 into transmit frame as SA address */
#define ETH_MAC_SA_MODE_REPLACE_MACADDR1            (ETH_MAC_CONFIGR_SAIRC)                               /*!< Replace SA address in transmit frame with address value in MAC address register 1 */
/**
 * @}
 */

/**
 * @defgroup ETH_TypeFrame_Strip_FCS ETH Type Frame Strip FCS
 * @{
 */
#define ETH_MAC_TYPEFRAME_STRIP_FCS_DISABLE         (0UL)
#define ETH_MAC_TYPEFRAME_STRIP_FCS_ENABLE          (ETH_MAC_CONFIGR_CST)
/**
 * @}
 */

/**
 * @defgroup ETH_Watchdog ETH Watchdog
 * @{
 */
#define ETH_MAC_WATCHDOG_DISABLE                    (ETH_MAC_CONFIGR_MWD)
#define ETH_MAC_WATCHDOG_ENABLE                     (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Jabber ETH Jabber
 * @{
 */
#define ETH_MAC_JABBER_DISABLE                      (ETH_MAC_CONFIGR_MJB)
#define ETH_MAC_JABBER_ENABLE                       (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Inter_Frame_Gap ETH Inter Frame Gap
 * @{
 */
#define ETH_MAC_INTERFRAME_GAP_96BIT                (0UL)
#define ETH_MAC_INTERFRAME_GAP_88BIT                (ETH_MAC_CONFIGR_IFG_0)
#define ETH_MAC_INTERFRAME_GAP_80BIT                (ETH_MAC_CONFIGR_IFG_1)
#define ETH_MAC_INTERFRAME_GAP_72BIT                (ETH_MAC_CONFIGR_IFG_1 | ETH_MAC_CONFIGR_IFG_0)
#define ETH_MAC_INTERFRAME_GAP_64BIT                (ETH_MAC_CONFIGR_IFG_2)
#define ETH_MAC_INTERFRAME_GAP_56BIT                (ETH_MAC_CONFIGR_IFG_2 | ETH_MAC_CONFIGR_IFG_0)
#define ETH_MAC_INTERFRAME_GAP_48BIT                (ETH_MAC_CONFIGR_IFG_2 | ETH_MAC_CONFIGR_IFG_1)
#define ETH_MAC_INTERFRAME_GAP_40BIT                (ETH_MAC_CONFIGR_IFG)
/**
 * @}
 */

/**
 * @defgroup ETH_Carrier_Sense ETH Carrier Sense
 * @{
 */
#define ETH_MAC_CARRIER_SENCE_DISABLE               (ETH_MAC_CONFIGR_DCRS)
#define ETH_MAC_CARRIER_SENCE_ENABLE                (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Receive_Own ETH Receive Own
 * @{
 */
#define ETH_MAC_RECEIVE_OWN_DISABLE                 (ETH_MAC_CONFIGR_DO)
#define ETH_MAC_RECEIVE_OWN_ENABLE                  (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Checksum_Offload ETH Checksum Offload
 * @{
 */
#define ETH_MAC_CHECKSUM_OFFLAOD_DISABLE            (0UL)
#define ETH_MAC_CHECKSUM_OFFLAOD_ENABLE             (ETH_MAC_CONFIGR_IPCO)
/**
 * @}
 */

/**
 * @defgroup ETH_Retry_Transmit ETH Retry Transmit
 * @{
 */
#define ETH_MAC_RETRY_TRANSMIT_DISABLE              (ETH_MAC_CONFIGR_DRTY)
#define ETH_MAC_RETRY_TRANSMIT_ENABLE               (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Auto_Strip_Pad_FCS ETH Auto Strip Pad FCS
 * @{
 */
#define ETH_MAC_AUTO_STRIP_PAD_FCS_DISABLE          (0UL)
#define ETH_MAC_AUTO_STRIP_PAD_FCS_ENABLE           (ETH_MAC_CONFIGR_ACS)
/**
 * @}
 */

/**
 * @defgroup ETH_Back_Off_Limit ETH Back Off Limit
 * @{
 */
#define ETH_MAC_BACKOFF_LIMIT_10                    (0UL)
#define ETH_MAC_BACKOFF_LIMIT_8                     (ETH_MAC_CONFIGR_BL_0)
#define ETH_MAC_BACKOFF_LIMIT_4                     (ETH_MAC_CONFIGR_BL_1)
#define ETH_MAC_BACKOFF_LIMIT_1                     (ETH_MAC_CONFIGR_BL)
/**_
 * @}
 */

/**
 * @defgroup ETH_Deferral_Check ETH Deferral Check
 * @{
 */
#define ETH_MAC_DEFFERRAL_CHECK_DISABLE             (0UL)
#define ETH_MAC_DEFFERRAL_CHECK_ENABLE              (ETH_MAC_CONFIGR_DC)
/**
 * @}
 */

/**
 * @defgroup ETH_Zero_Quanta_Pause ETH Zero Quanta Pause
 * @{
 */
#define ETH_MAC_ZERO_QUANTA_PAUSE_DISABLE           (ETH_MAC_FLOCTLR_DZPQ)
#define ETH_MAC_ZERO_QUANTA_PAUSE_ENABLE            (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Pause_Low_Threshold ETH Pause Low Threshold
 * @{
 */
#define ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS4           (0UL)                     /*!< Pause time minus 4 slot times */
#define ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS28          (ETH_MAC_FLOCTLR_PLT_0)   /*!< Pause time minus 28 slot times */
#define ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS144         (ETH_MAC_FLOCTLR_PLT_1)   /*!< Pause time minus 144 slot times */
#define ETH_MAC_PAUSE_LOWTHRESHOLD_MINUS256         (ETH_MAC_FLOCTLR_PLT)     /*!< Pause time minus 256 slot times */
/**
 * @}
 */

/**
 * @defgroup ETH_Unicast_Pause_Frame_Detect ETH Unicast Pause Frame Detect
 * @{
 */
#define ETH_MAC_UNICAST_PAUSEFRAME_DETECT_DISABLE   (0UL)
#define ETH_MAC_UNICAST_PAUSEFRAME_DETECT_ENABLE    (ETH_MAC_FLOCTLR_UNP)
/**
 * @}
 */

/**
 * @defgroup ETH_Receive_Flow_Control ETH Receive Flow Control
 * @{
 */
#define ETH_MAC_RECEIVE_FLOWCONTROL_DISABLE         (0UL)
#define ETH_MAC_RECEIVE_FLOWCONTROL_ENABLE          (ETH_MAC_FLOCTLR_RFE)
/**
 * @}
 */

/**
 * @defgroup ETH_Transmit_Flow_Control ETH Transmit Flow Control
 * @{
 */
#define ETH_MAC_TRANSMIT_FLOWCONTROL_DISABLE        (0UL)
#define ETH_MAC_TRANSMIT_FLOWCONTROL_ENABLE         (ETH_MAC_FLOCTLR_TFE)
/**
 * @}
 */

/**
 * @defgroup ETH_Receive_All ETH Receive All
 * @{
 */
#define ETH_MAC_RECEIVE_All_DISABLE                 (0UL)
#define ETH_MAC_RECEIVE_ALL_ENABLE                  (ETH_MAC_FLTCTLR_RA)
/**
 * @}
 */

/**
 * @defgroup ETH_Drop_Not_TcpUdp ETH Drop Not TcpUdp
 * @{
 */
#define ETH_MAC_DROP_NOT_TCPUDP_DISABLE             (0UL)
#define ETH_MAC_DROP_NOT_TCPUDP_ENABLE              (ETH_MAC_FLTCTLR_DNTU)
/**
 * @}
 */

/**
 * @defgroup ETH_VLAN_Tag_Filter ETH VLAN Tag Filter
 * @{
 */
#define ETH_MAC_VLAN_TAG_FILTER_DISABLE             (0UL)
#define ETH_MAC_VLAN_TAG_FILTER_ENABLE              (ETH_MAC_FLTCTLR_VTFE)
/**
 * @}
 */

/**
 * @defgroup ETH_Source_Addr_Filter ETH Source Addr Filter
 * @{
 */
#define ETH_MAC_SOURCE_ADDR_FILTER_DISABLE          (0UL)
#define ETH_MAC_SOURCE_ADDR_FILTER_NORMAL           (ETH_MAC_FLTCTLR_SAF)
#define ETH_MAC_SOURCE_ADDR_FILTER_INVERSE          (ETH_MAC_FLTCTLR_SAF | ETH_MAC_FLTCTLR_SAIF)
/**
 * @}
 */

/**
 * @defgroup ETH_Pass_Control_Frame ETH Pass Control Frame
 * @{
 */
#define ETH_MAC_PASS_CTRLFRAME_BLOCK_ALL                    (0UL)                     /*!< MAC filter all control frame from reaching the application */
#define ETH_MAC_PASS_CTRLFRAME_FORWARD_NOTPAUSE_ALL         (ETH_MAC_FLTCTLR_PCF_0)   /*!< MAC forward all control frame except pause control frame to application even if they fail the address filter */
#define ETH_MAC_PASS_CTRLFRAME_FORWARD_ALL                  (ETH_MAC_FLTCTLR_PCF_1)   /*!< MAC forward all control frame to application even if they fail the address filter */
#define ETH_MAC_PASS_CTRLFRAME_FORWARD_PASSADDRFILTER       (ETH_MAC_FLTCTLR_PCF)     /*!< MAC forward control frame that pass the address filter. */
/**
 * @}
 */

/**
 * @defgroup ETH_Broadcast_Frame_Reception ETH Broadcast Frame Reception
 * @{
 */
#define ETH_MAC_BROADCASTFRAME_RECEPTION_DISABLE    (ETH_MAC_FLTCTLR_DBF)
#define ETH_MAC_BROADCASTFRAME_RECEPTION_ENABLE     (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Destination_Addr_Filter ETH Destination Addr Filter
 * @{
 */
#define ETH_MAC_DESTINATION_ADDR_FILTER_NORMAL      (0UL)
#define ETH_MAC_DESTINATION_ADDR_FILTER_INVERSE     (ETH_MAC_FLTCTLR_DAIF)
/**
 * @}
 */

/**
 * @defgroup ETH_Multicast_Frame_Filter ETH Multicast Frame Filter
 * @{
 */
#define ETH_MAC_MULTICASTFRAME_FILTER_NONE                  (ETH_MAC_FLTCTLR_PMF)
#define ETH_MAC_MULTICASTFRAME_FILTER_PERFECT               (0UL)
#define ETH_MAC_MULTICASTFRAME_FILTER_HASHTABLE             (ETH_MAC_FLTCTLR_HMC)
#define ETH_MAC_MULTICASTFRAME_FILTER_PERFECTHASHTABLE      (ETH_MAC_FLTCTLR_HPF | ETH_MAC_FLTCTLR_HMC)
/**
 * @}
 */

/**
 * @defgroup ETH_Unicast_Frame_Filter ETH Unicast Frame Filter
 * @{
 */
#define ETH_MAC_UNICASTFRAME_FILTER_PERFECT                 (0UL)
#define ETH_MAC_UNICASTFRAME_FILTER_HASHTABLE               (ETH_MAC_FLTCTLR_HUC)
#define ETH_MAC_UNICASTFRAME_FILTER_PERFECTHASHTABLE        (ETH_MAC_FLTCTLR_HPF | ETH_MAC_FLTCTLR_HUC)
/**
 * @}
 */

/**
 * @defgroup ETH_Promiscuous_Mode ETH Promiscuous Mode
 * @{
 */
#define ETH_MAC_PROMISCUOUS_MODE_DISABLE            (0UL)
#define ETH_MAC_PROMISCUOUS_MODE_ENABLE             (ETH_MAC_FLTCTLR_PR)
/**
 * @}
 */

/**
 * @defgroup ETH_Tx_VLAN_Insert_Mode ETH Tx VLAN Insert Mode
 * @{
 */
#define ETH_MAC_TXVLAN_MODE_BY_DMATXDESC            (0UL)                                               /*!< Configure the Tx VLAN mode by Tx Descriptor of DMA */
#define ETH_MAC_TXVLAN_MODE_BYPASS                  (ETH_MAC_VTACTLR_VLANS)                             /*!< Do Nothing: VLAN Insertion is bypassed */
#define ETH_MAC_TXVLAN_MODE_REMOVE_TAG              (ETH_MAC_VTACTLR_VLANS | ETH_MAC_VTACTLR_VLANC_0)   /*!< Remove Tag and Type fields in VLAN frame */
#define ETH_MAC_TXVLAN_MODE_INSERT_TAG              (ETH_MAC_VTACTLR_VLANS | ETH_MAC_VTACTLR_VLANC_1)   /*!< Insert VLAN Tag value in ETH_MAC_VTACTLR Register into transmit frame */
#define ETH_MAC_TXVLAN_MODE_REPLACE_TAG             (ETH_MAC_VTACTLR_VLANS | ETH_MAC_VTACTLR_VLANC)     /*!< Replace VLAN tag value in transmit frame with VLAN tag value in ETH_MAC_VTACTLR register */
/**
 * @}
 */

/**
 * @defgroup ETH_Rx_VLAN_Filter ETH Rx VLAN Filter
 * @{
 */
#define ETH_MAC_RXVLAN_FILTER_NORMAL                (0UL)
#define ETH_MAC_RXVLAN_FILTER_INVERSE               (ETH_MAC_VTAFLTR_VTIM)
#define ETH_MAC_RXVLAN_FILTER_NORMAL_HASHTABLE      (ETH_MAC_VTAFLTR_VTHM)
#define ETH_MAC_RXVLAN_FILTER_INVERSE_HASHTABLE     (ETH_MAC_VTAFLTR_VTHM | ETH_MAC_VTAFLTR_VTIM)
/**
 * @}
 */

/**
 * @defgroup ETH_Rx_VLAN_Comparison ETH Rx VLAN Comparison
 * @{
 */
#define ETH_MAC_RXVLAN_COMPARISON_16BIT             (0UL)
#define ETH_MAC_RXVLAN_COMPARISON_12BIT             (ETH_MAC_VTAFLTR_VTAL)
/**
 * @}
 */

/**
 * @defgroup ETH_L4_Dest_Port_Filter ETH L4 Dest Port Filter
 * @{
 */
#define ETH_MAC_L4_DESTPORT_FILTER_DISABLE          (0UL)
#define ETH_MAC_L4_DESTPORT_FILTER_NORMAL           (ETH_MAC_L34CTLR_L4DPM)
#define ETH_MAC_L4_DESTPORT_FILTER_INVERSE          (ETH_MAC_L34CTLR_L4DPIM | ETH_MAC_L34CTLR_L4DPM)
/**
 * @}
 */

/**
 * @defgroup ETH_L4_Source_Port_Filter ETH L4 Source Port Filter
 * @{
 */
#define ETH_MAC_L4_SOURCEPORT_FILTER_DISABLE        (0UL)
#define ETH_MAC_L4_SOURCEPORT_FILTER_NORMAL         (ETH_MAC_L34CTLR_L4SPM)
#define ETH_MAC_L4_SOURCEPORT_FILTER_INVERSE        (ETH_MAC_L34CTLR_L4SPIM | ETH_MAC_L34CTLR_L4SPM)
/**
 * @}
 */

/**
 * @defgroup ETH_L4_Port_Filter_Protocol ETH L4 Port Filter Protocol
 * @{
 */
#define ETH_MAC_L4_PORT_FILTER_PROTOCOL_TCP         (0UL)                     /*!< Port filter for TCP frame */
#define ETH_MAC_L4_PORT_FILTER_PROTOCOL_UDP         (ETH_MAC_L34CTLR_L4PEN)   /*!< Port filter for UDP frame */
/**
 * @}
 */

/**
 * @defgroup ETH_L3_Dest_Addr_Filter_Mask ETH L3 Destination Addr Filter Mask
 * @note The following definitions apply to IPv4
 * @{
 */
#define ETH_MAC_L3_DA_FILTER_MASK_NONE              (0x00000000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT0              (0x00000800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT1_0            (0x00001000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT2_0            (0x00001800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT3_0            (0x00002000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT4_0            (0x00002800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT5_0            (0x00003000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT6_0            (0x00003800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT7_0            (0x00004000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT8_0            (0x00004800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT9_0            (0x00005000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT10_0           (0x00005800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT11_0           (0x00006000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT12_0           (0x00006800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT13_0           (0x00007000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT14_0           (0x00007800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT15_0           (0x00008000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT16_0           (0x00008800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT17_0           (0x00009000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT18_0           (0x00009800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT19_0           (0x0000A000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT20_0           (0x0000A800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT21_0           (0x0000B000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT22_0           (0x0000B800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT23_0           (0x0000C000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT24_0           (0x0000C800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT25_0           (0x0000D000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT26_0           (0x0000D800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT27_0           (0x0000E000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT28_0           (0x0000E800UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT29_0           (0x0000F000UL)
#define ETH_MAC_L3_DA_FILTER_MASK_BIT30_0           (0x0000F800UL)
/**
 * @}
 */

/**
 * @defgroup ETH_L3_Source_Addr_Filter_Mask ETH L3 Source Addr Filter Mask
 * @note The following definitions apply to IPv4
 * @{
 */
#define ETH_MAC_L3_SA_FILTER_MASK_NONE              (0x00000000UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT0              (0x00000040UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT1_0            (0x00000080UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT2_0            (0x000000C0UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT3_0            (0x00000100UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT4_0            (0x00000140UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT5_0            (0x00000180UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT6_0            (0x000001C0UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT7_0            (0x00000200UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT8_0            (0x00000240UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT9_0            (0x00000280UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT10_0           (0x000002C0UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT11_0           (0x00000300UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT12_0           (0x00000340UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT13_0           (0x00000380UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT14_0           (0x000003C0UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT15_0           (0x00000400UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT16_0           (0x00000440UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT17_0           (0x00000480UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT18_0           (0x000004C0UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT19_0           (0x00000500UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT20_0           (0x00000540UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT21_0           (0x00000580UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT22_0           (0x000005C0UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT23_0           (0x00000600UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT24_0           (0x00000640UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT25_0           (0x00000680UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT26_0           (0x000006C0UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT27_0           (0x00000700UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT28_0           (0x00000740UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT29_0           (0x00000780UL)
#define ETH_MAC_L3_SA_FILTER_MASK_BIT30_0           (0x000007C0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_L3_DA_SA_Filter_Mask ETH L3 DA SA Filter Mask
 * @note The following definitions apply to IPv6.
 * @{
 */
#define ETH_MAC_L3_DA_SA_FILTER_MASK_NONE           (0x00000000UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT0           (0x00000040UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT1_0         (0x00000080UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT2_0         (0x000000C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT3_0         (0x00000100UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT4_0         (0x00000140UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT5_0         (0x00000180UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT6_0         (0x000001C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT7_0         (0x00000200UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT8_0         (0x00000240UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT9_0         (0x00000280UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT10_0        (0x000002C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT11_0        (0x00000300UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT12_0        (0x00000340UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT13_0        (0x00000380UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT14_0        (0x000003C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT15_0        (0x00000400UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT16_0        (0x00000440UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT17_0        (0x00000480UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT18_0        (0x000004C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT19_0        (0x00000500UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT20_0        (0x00000540UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT21_0        (0x00000580UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT22_0        (0x000005C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT23_0        (0x00000600UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT24_0        (0x00000640UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT25_0        (0x00000680UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT26_0        (0x000006C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT27_0        (0x00000700UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT28_0        (0x00000740UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT29_0        (0x00000780UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT30_0        (0x000007C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT31_0        (0x00000800UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT32_0        (0x00000840UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT33_0        (0x00000880UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT34_0        (0x000008C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT35_0        (0x00000900UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT36_0        (0x00000940UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT37_0        (0x00000980UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT38_0        (0x000009C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT39_0        (0x00000A00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT40_0        (0x00000A40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT41_0        (0x00000A80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT42_0        (0x00000AC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT43_0        (0x00000B00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT44_0        (0x00000B40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT45_0        (0x00000B80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT46_0        (0x00000BC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT47_0        (0x00000C00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT48_0        (0x00000C40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT49_0        (0x00000C80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT50_0        (0x00000CC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT51_0        (0x00000D00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT52_0        (0x00000D40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT53_0        (0x00000D80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT54_0        (0x00000DC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT55_0        (0x00000E00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT56_0        (0x00000E40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT57_0        (0x00000E80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT58_0        (0x00000EC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT59_0        (0x00000F00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT60_0        (0x00000F40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT61_0        (0x00000F80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT62_0        (0x00000FC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT63_0        (0x00001000UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT64_0        (0x00001040UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT65_0        (0x00001080UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT66_0        (0x000010C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT67_0        (0x00001100UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT68_0        (0x00001140UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT69_0        (0x00001180UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT70_0        (0x000011C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT71_0        (0x00001200UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT72_0        (0x00001240UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT73_0        (0x00001280UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT74_0        (0x000012C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT75_0        (0x00001300UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT76_0        (0x00001340UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT77_0        (0x00001380UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT78_0        (0x000013C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT79_0        (0x00001400UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT80_0        (0x00001440UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT81_0        (0x00001480UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT82_0        (0x000014C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT83_0        (0x00001500UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT84_0        (0x00001540UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT85_0        (0x00001580UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT86_0        (0x000015C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT87_0        (0x00001600UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT88_0        (0x00001640UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT89_0        (0x00001680UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT90_0        (0x000016C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT91_0        (0x00001700UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT92_0        (0x00001740UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT93_0        (0x00001780UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT94_0        (0x000017C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT95_0        (0x00001800UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT96_0        (0x00001840UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT97_0        (0x00001880UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT98_0        (0x000018C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT99_0        (0x00001900UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT100_0       (0x00001940UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT101_0       (0x00001980UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT102_0       (0x000019C0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT103_0       (0x00001A00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT104_0       (0x00001A40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT105_0       (0x00001A80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT106_0       (0x00001AC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT107_0       (0x00001B00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT108_0       (0x00001B40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT109_0       (0x00001B80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT110_0       (0x00001BC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT111_0       (0x00001C00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT112_0       (0x00001C40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT113_0       (0x00001C80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT114_0       (0x00001CC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT115_0       (0x00001D00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT116_0       (0x00001D40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT117_0       (0x00001D80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT118_0       (0x00001DC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT119_0       (0x00001E00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT120_0       (0x00001E40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT121_0       (0x00001E80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT122_0       (0x00001EC0UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT123_0       (0x00001F00UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT124_0       (0x00001F40UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT125_0       (0x00001F80UL)
#define ETH_MAC_L3_DA_SA_FILTER_MASK_BIT126_0       (0x00001FC0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_L3_Dest_Addr_Filter ETH L3 Destination Addr Filter
 * @{
 */
#define ETH_MAC_L3_DA_FILTER_DISABLE                (0UL)
#define ETH_MAC_L3_DA_FILTER_NORMAL                 (ETH_MAC_L34CTLR_L3DAM)
#define ETH_MAC_L3_DA_FILTER_INVERSE                (ETH_MAC_L34CTLR_L3DAIM | ETH_MAC_L34CTLR_L3DAM)
/**
 * @}
 */

/**
 * @defgroup ETH_L3_Source_Addr_Filter ETH L3 Source Addr Filter
 * @{
 */
#define ETH_MAC_L3_SA_FILTER_DISABLE                (0UL)
#define ETH_MAC_L3_SA_FILTER_NORMAL                 (ETH_MAC_L34CTLR_L3SAM)
#define ETH_MAC_L3_SA_FILTER_INVERSE                (ETH_MAC_L34CTLR_L3SAIM | ETH_MAC_L34CTLR_L3SAM)
/**
 * @}
 */

/**
 * @defgroup ETH_L3_Addr_Filter_Protocol ETH L3 Addr Filter Protocol
 * @{
 */
#define ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV4        (0UL)                     /*!< Ip Address filter for IPv4 */
#define ETH_MAC_L3_ADDR_FILTER_PROTOCOL_IPV6        (ETH_MAC_L34CTLR_L3PEN)   /*!< Ip Address filter for IPv6 */
/**
 * @}
 */

/**
 * @defgroup ETH_MAC_Address_Index ETH MAC Address Index
 * @{
 */
#define ETH_MAC_ADDRESS0                            (0x00000000UL)
#define ETH_MAC_ADDRESS1                            (0x00000008UL)
#define ETH_MAC_ADDRESS2                            (0x00000010UL)
#define ETH_MAC_ADDRESS3                            (0x00000018UL)
#define ETH_MAC_ADDRESS4                            (0x00000020UL)
/**
 * @}
 */

/**
 * @defgroup ETH_MAC_Address_Filter ETH MAC Address Filter
 * @note The parameter is invalid in ETH_MAC_ADDRESS0.
 * @{
 */
#define ETH_MAC_ADDRESS_FILTER_DISABLE              (0UL)                                           /*!< Disable perfect filter with MAC address. */
#define ETH_MAC_ADDRESS_FILTER_PERFECT_DA           (ETH_MAC_MACADHR1_AE1)                          /*!< Filter the DA address of the received frame with MAC address. */
#define ETH_MAC_ADDRESS_FILTER_PERFECT_SA           (ETH_MAC_MACADHR1_AE1 | ETH_MAC_MACADHR1_SA1)   /*!< Filter the SA address of the received frame with MAC address. */
/**
 * @}
 */

/**
 * @defgroup ETH_MAC_Address_Filter_Mask ETH MAC Address Filter Mask
 * @note The parameter is invalid in ETH_MAC_ADDRESS0.
 * @{
 */
#define ETH_MAC_ADDRESS_MASK_DISABLE                (0UL)                       /*!< Disable MAC Address Mask */
#define ETH_MAC_ADDRESS_MASK_BYTE6                  (ETH_MAC_MACADHR1_MBC1_5)   /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MAC_ADDRESS_MASK_BYTE5                  (ETH_MAC_MACADHR1_MBC1_4)   /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MAC_ADDRESS_MASK_BYTE4                  (ETH_MAC_MACADHR1_MBC1_3)   /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MAC_ADDRESS_MASK_BYTE3                  (ETH_MAC_MACADHR1_MBC1_2)   /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MAC_ADDRESS_MASK_BYTE2                  (ETH_MAC_MACADHR1_MBC1_1)   /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MAC_ADDRESS_MASK_BYTE1                  (ETH_MAC_MACADHR1_MBC1_0)   /*!< Mask MAC Address low reg bits [7:0] */
#define ETH_MAC_ADDRESS_MASK_ALL                    (ETH_MAC_MACADHR1_MBC1)     /*!< Mask MAC Address low reg bits [31:0] and low high bits [15:0] */
/**
 * @}
 */

/**
 * @defgroup ETH_MAC_INT_Flag ETH MAC Interrupt Flag
 * @{
 */
#define ETH_MAC_INT_FLAG_TSPIS                      (ETH_MAC_INTSTSR_TSPIS)     /*!< Time stamp trigger flag (on MAC) */
#define ETH_MAC_INT_FLAG_MMCTXIS                    (ETH_MAC_INTSTSR_MMCTXIS)   /*!< MMC transmit flag  */
#define ETH_MAC_INT_FLAG_MMCRXIS                    (ETH_MAC_INTSTSR_MMCRXIS)   /*!< MMC receive flag */
#define ETH_MAC_INT_FLAG_MMCIS                      (ETH_MAC_INTSTSR_MMCIS)     /*!< MMC flag (on MAC) */
#define ETH_MAC_INT_FLAG_PMTIS                      (ETH_MAC_INTSTSR_PMTIS)     /*!< PMT flag (on MAC) */
/**
 * @}
 */

/**
 * @defgroup ETH_MAC_Interrupt ETH MAC Interrupt
 * @{
 */
#define ETH_MAC_INT_TSPIM                           (ETH_MAC_INTMSKR_TSPIM)   /*!< Time stamp trigger interrupt (on MAC) */
#define ETH_MAC_INT_PMTIM                           (ETH_MAC_INTMSKR_PMTIM)   /*!< PMT interrupt (on MAC) */
/**
 * @}
 */

/**
 * @defgroup ETH_Burst_Mode ETH Burst Mode
 * @{
 */
#define ETH_DMA_BURST_MODE_NORMAL                   (0UL)                     /*!< DMA master interface only use SINGLE and INCR access type */
#define ETH_DMA_BURST_MODE_FIXED                    (ETH_DMA_BUSMODR_FBST)    /*!< DMA master interface use SINGLE and INCR, INCR8, INCR16 access type */
#define ETH_DMA_BURST_MODE_MIXED                    (ETH_DMA_BUSMODR_MBST)    /*!< DMA master interface will start all burst transmission with INCR length greater than 16 */
/**
 * @}
 */

/**
 * @defgroup ETH_Address_Align ETH Address Align
 * @{
 */
#define ETH_DMA_ADDRESS_ALIGN_DISABLE               (0UL)
#define ETH_DMA_ADDRESS_ALIGN_ENABLE                (ETH_DMA_BUSMODR_AAL)
/**
 * @}
 */

/**
 * @defgroup ETH_Rx_DMA_Burst_Length ETH Rx DMA Burst Length
 * @{
 */
#define ETH_DMA_RX_BURST_LENGTH_1BEAT               (ETH_DMA_BUSMODR_RPBL_0)                          /*!< Maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define ETH_DMA_RX_BURST_LENGTH_2BEAT               (ETH_DMA_BUSMODR_RPBL_1)                          /*!< Maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define ETH_DMA_RX_BURST_LENGTH_4BEAT               (ETH_DMA_BUSMODR_RPBL_2)                          /*!< Maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_DMA_RX_BURST_LENGTH_8BEAT               (ETH_DMA_BUSMODR_RPBL_3)                          /*!< Maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_DMA_RX_BURST_LENGTH_16BEAT              (ETH_DMA_BUSMODR_RPBL_4)                          /*!< Maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_DMA_RX_BURST_LENGTH_32BEAT              (ETH_DMA_BUSMODR_RPBL_5)                          /*!< Maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_DMA_RX_BURST_LENGTH_8XPBL_8BEAT         (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_RPBL_0)  /*!< Maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_DMA_RX_BURST_LENGTH_8XPBL_16BEAT        (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_RPBL_1)  /*!< Maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_DMA_RX_BURST_LENGTH_8XPBL_32BEAT        (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_RPBL_2)  /*!< Maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_DMA_RX_BURST_LENGTH_8XPBL_64BEAT        (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_RPBL_3)  /*!< Maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define ETH_DMA_RX_BURST_LENGTH_8XPBL_128BEAT       (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_RPBL_4)  /*!< Maximum number of beats to be transferred in one RxDMA transaction is 128 */
#define ETH_DMA_RX_BURST_LENGTH_8XPBL_256BEAT       (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_RPBL_5)  /*!< Maximum number of beats to be transferred in one RxDMA transaction is 256 */
/**
 * @}
 */

/**
 * @defgroup ETH_Tx_DMA_Burst_Length ETH Tx DMA Burst Length
 * @{
 */
#define ETH_DMA_TX_BURST_LENGTH_1BEAT               (ETH_DMA_BUSMODR_TPBL_0)                          /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define ETH_DMA_TX_BURST_LENGTH_2BEAT               (ETH_DMA_BUSMODR_TPBL_1)                          /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define ETH_DMA_TX_BURST_LENGTH_4BEAT               (ETH_DMA_BUSMODR_TPBL_2)                          /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_DMA_TX_BURST_LENGTH_8BEAT               (ETH_DMA_BUSMODR_TPBL_3)                          /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_DMA_TX_BURST_LENGTH_16BEAT              (ETH_DMA_BUSMODR_TPBL_4)                          /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_DMA_TX_BURST_LENGTH_32BEAT              (ETH_DMA_BUSMODR_TPBL_5)                          /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_DMA_TX_BURST_LENGTH_8XPBL_8BEAT         (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_TPBL_0)  /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_DMA_TX_BURST_LENGTH_8XPBL_16BEAT        (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_TPBL_1)  /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_DMA_TX_BURST_LENGTH_8XPBL_32BEAT        (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_TPBL_2)  /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_DMA_TX_BURST_LENGTH_8XPBL_64BEAT        (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_TPBL_3)  /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define ETH_DMA_TX_BURST_LENGTH_8XPBL_128BEAT       (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_TPBL_4)  /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */
#define ETH_DMA_TX_BURST_LENGTH_8XPBL_256BEAT       (ETH_DMA_BUSMODR_M8PBL | ETH_DMA_BUSMODR_TPBL_5)  /*!< Maximum number of beats to be transferred in one TxDMA (or both) transaction is 256 */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Enhance_Descriptor ETH DMA Enhance Descriptor
 * @{
 */
#define ETH_DMA_ENHANCE_DESCRIPTOR_DISABLE          (0UL)
#define ETH_DMA_ENHANCE_DESCRIPTOR_ENABLE           (ETH_DMA_BUSMODR_DSEN)
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Arbitration ETH DMA Arbitration
 * @{
 */
#define ETH_DMA_ARBITRATION_LOOP_RXTX_1_1           (0UL)
#define ETH_DMA_ARBITRATION_LOOP_RXTX_2_1           (ETH_DMA_BUSMODR_PRAT_0)
#define ETH_DMA_ARBITRATION_LOOP_RXTX_3_1           (ETH_DMA_BUSMODR_PRAT_1)
#define ETH_DMA_ARBITRATION_LOOP_RXTX_4_1           (ETH_DMA_BUSMODR_PRAT)
#define ETH_DMA_ARBITRATION_LOOP_TXRX_1_1           (ETH_DMA_BUSMODR_TXPR)
#define ETH_DMA_ARBITRATION_LOOP_TXRX_2_1           (ETH_DMA_BUSMODR_TXPR | ETH_DMA_BUSMODR_PRAT_0)
#define ETH_DMA_ARBITRATION_LOOP_TXRX_3_1           (ETH_DMA_BUSMODR_TXPR | ETH_DMA_BUSMODR_PRAT_1)
#define ETH_DMA_ARBITRATION_LOOP_TXRX_4_1           (ETH_DMA_BUSMODR_TXPR | ETH_DMA_BUSMODR_PRAT)
#define ETH_DMA_ARBITRATION_FIXED_RXPRIORTX         (ETH_DMA_BUSMODR_DMAA)
#define ETH_DMA_ARBITRATION_FIXED_TXPRIORRX         (ETH_DMA_BUSMODR_TXPR | ETH_DMA_BUSMODR_DMAA)
/**
 * @}
 */

/**
 * @defgroup ETH_Drop_TCPIP_Checksum_Error_Frame ETH Drop TCPIP Checksum Error Frame
 * @{
 */
#define ETH_DMA_DROP_CHECKSUM_ERRORFRAME_DISABLE    (ETH_DMA_OPRMODR_DTCOE)
#define ETH_DMA_DROP_CHECKSUM_ERRORFRAME_ENABLE     (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Receive_Store_Forward ETH Receive Store Forward
 * @{
 */
#define ETH_DMA_RECEIVE_STORE_FORWARD_DISABLE       (0UL)
#define ETH_DMA_RECEIVE_STORE_FORWARD_ENABLE        (ETH_DMA_OPRMODR_RSF)
/**
 * @}
 */

/**
 * @defgroup ETH_Flush_Receive_Frame ETH Flush Receive Frame
 * @{
 */
#define ETH_DMA_FLUSH_RECEIVEDFRAME_DISABLE         (ETH_DMA_OPRMODR_DFRF)
#define ETH_DMA_FLUSH_RECEIVEDFRAME_ENABLE          (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_Transmit_Store_Forward ETH Transmit Store Forward
 * @{
 */
#define ETH_DMA_TRANSMIT_STORE_FORWARD_DISABLE      (0UL)
#define ETH_DMA_TRANSMIT_STORE_FORWARD_ENABLE       (ETH_DMA_OPRMODR_TSF)
/**
 * @}
 */

/**
 * @defgroup ETH_Transmit_Threshold ETH Transmit Threshold
 * @{
 */
#define ETH_DMA_TRANSMIT_THRESHOLD_64BYTE           (0UL)                                             /*!< Threshold level of the Transmit FIFO is 64 Bytes */
#define ETH_DMA_TRANSMIT_THRESHOLD_128BYTE          (ETH_DMA_OPRMODR_TTC_0)                           /*!< Threshold level of the Transmit FIFO is 128 Bytes */
#define ETH_DMA_TRANSMIT_THRESHOLD_192BYTE          (ETH_DMA_OPRMODR_TTC_1)                           /*!< Threshold level of the Transmit FIFO is 192 Bytes */
#define ETH_DMA_TRANSMIT_THRESHOLD_256BYTE          (ETH_DMA_OPRMODR_TTC_1 | ETH_DMA_OPRMODR_TTC_0)   /*!< Threshold level of the Transmit FIFO is 256 Bytes */
#define ETH_DMA_TRANSMIT_THRESHOLD_40BYTE           (ETH_DMA_OPRMODR_TTC_2)                           /*!< Threshold level of the Transmit FIFO is 40 Bytes */
#define ETH_DMA_TRANSMIT_THRESHOLD_32BYTE           (ETH_DMA_OPRMODR_TTC_2 | ETH_DMA_OPRMODR_TTC_0)   /*!< Threshold level of the Transmit FIFO is 32 Bytes */
#define ETH_DMA_TRANSMIT_THRESHOLD_24BYTE           (ETH_DMA_OPRMODR_TTC_2 | ETH_DMA_OPRMODR_TTC_1)   /*!< Threshold level of the Transmit FIFO is 24 Bytes */
#define ETH_DMA_TRANSMIT_THRESHOLD_16BYTE           (ETH_DMA_OPRMODR_TTC)                             /*!< Threshold level of the Transmit FIFO is 16 Bytes */
/**
 * @}
 */

/**
 * @defgroup ETH_Forward_Error_Frame ETH Forward Error Frame
 * @{
 */
#define ETH_DMA_FORWARD_ERRORFRAME_DISABLE          (0UL)
#define ETH_DMA_FORWARD_ERRORFRAME_ENABLE           (ETH_DMA_OPRMODR_FEF)
/**
 * @}
 */

/**
 * @defgroup ETH_Forward_Undersize_Good_Frame ETH Forward Undersize Good Frame
 * @{
 */
#define ETH_DMA_FORWARD_UNDERSIZE_GOODFRAME_DISABLE (0UL)
#define ETH_DMA_FORWARD_UNDERSIZE_GOODFRAME_ENABLE  (ETH_DMA_OPRMODR_FUF)
/**
 * @}
 */

/**
 * @defgroup ETH_Drop_Jumbo_Frame ETH Drop Jumbo Frame
 * @{
 */
#define ETH_DMA_DROP_JUMBO_FRAME_DISABLE            (0UL)
#define ETH_DMA_DROP_JUMBO_FRAME_ENABLE             (ETH_DMA_OPRMODR_DGF)
/**
 * @}
 */

/**
 * @defgroup ETH_Receive_Threshold ETH Receive Threshold
 * @{
 */
#define ETH_DMA_RECEIVE_THRESHOLD_64BYTE            (0UL)                     /*!< Threshold level of the Receive FIFO is 64 Bytes */
#define ETH_DMA_RECEIVE_THRESHOLD_32BYTE            (ETH_DMA_OPRMODR_RTC_0)   /*!< Threshold level of the Receive FIFO is 32 Bytes */
#define ETH_DMA_RECEIVE_THRESHOLD_96BYTE            (ETH_DMA_OPRMODR_RTC_1)   /*!< Threshold level of the Receive FIFO is 96 Bytes */
#define ETH_DMA_RECEIVE_THRESHOLD_128BYTE           (ETH_DMA_OPRMODR_RTC)     /*!< Threshold level of the Receive FIFO is 128 Bytes */
/**
 * @}
 */

/**
 * @defgroup ETH_Second_Frame_Operate ETH Second Frame Operate
 * @{
 */
#define ETH_DMA_SECONDFRAME_OPERARTE_DISABLE        (0UL)
#define ETH_DMA_SECONDFRAME_OPERARTE_ENABLE         (ETH_DMA_OPRMODR_OSF)
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Flag ETH DMA Flag
 * @{
 */
#define ETH_DMA_FLAG_PTPS                           (ETH_DMA_DMASTSR_PTPS)  /*!< Time-stamp trigger status */
#define ETH_DMA_FLAG_PMTS                           (ETH_DMA_DMASTSR_PMTS)  /*!< PMT trigger status */
#define ETH_DMA_FLAG_MMCS                           (ETH_DMA_DMASTSR_MMCS)  /*!< MMC trigger status */
#define ETH_DMA_FLAG_EBUS                           (ETH_DMA_DMASTSR_EBUS)  /*!< Error state bits  */
#define ETH_DMA_FLAG_TSTS                           (ETH_DMA_DMASTSR_TSTS)  /*!< Transmit state */
#define ETH_DMA_FLAG_RSTS                           (ETH_DMA_DMASTSR_RSTS)  /*!< Receive state */
#define ETH_DMA_FLAG_NIS                            (ETH_DMA_DMASTSR_NIS)   /*!< Normal interrupt summary flag */
#define ETH_DMA_FLAG_AIS                            (ETH_DMA_DMASTSR_AIS)   /*!< Abnormal interrupt summary flag */
#define ETH_DMA_FLAG_ERS                            (ETH_DMA_DMASTSR_ERS)   /*!< Early receive flag */
#define ETH_DMA_FLAG_FBS                            (ETH_DMA_DMASTSR_FBS)   /*!< Fatal bus error flag */
#define ETH_DMA_FLAG_ETS                            (ETH_DMA_DMASTSR_ETS)   /*!< Early transmit flag */
#define ETH_DMA_FLAG_RWS                            (ETH_DMA_DMASTSR_RWS)   /*!< Receive watchdog timeout flag */
#define ETH_DMA_FLAG_RSS                            (ETH_DMA_DMASTSR_RSS)   /*!< Receive stopped flag */
#define ETH_DMA_FLAG_RUS                            (ETH_DMA_DMASTSR_RUS)   /*!< Receive buffer unavailable flag */
#define ETH_DMA_FLAG_RIS                            (ETH_DMA_DMASTSR_RIS)   /*!< Receive flag */
#define ETH_DMA_FLAG_UNS                            (ETH_DMA_DMASTSR_UNS)   /*!< Transmit Underflow flag */
#define ETH_DMA_FLAG_OVS                            (ETH_DMA_DMASTSR_OVS)   /*!< Receive Overflow flag */
#define ETH_DMA_FLAG_TJS                            (ETH_DMA_DMASTSR_TJS)   /*!< Transmit jabber timeout flag */
#define ETH_DMA_FLAG_TUS                            (ETH_DMA_DMASTSR_TUS)   /*!< Transmit buffer unavailable flag */
#define ETH_DMA_FLAG_TSS                            (ETH_DMA_DMASTSR_TSS)   /*!< Transmit stopped flag */
#define ETH_DMA_FLAG_TIS                            (ETH_DMA_DMASTSR_TIS)   /*!< Transmit interrupt flag */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Error_State ETH DMA Error State
 * @{
 */
#define ETH_DMA_ERRORSTATE_RX_WRITEDATA             (0UL)                                               /*!< RxDMA generates error while writing data */
#define ETH_DMA_ERRORSTATE_TX_READDATA              (ETH_DMA_DMASTSR_EBUS_1 | ETH_DMA_DMASTSR_EBUS_0)   /*!< TxDMA generates error while reading data */
#define ETH_DMA_ERRORSTATE_RX_WRITEDESC             (ETH_DMA_DMASTSR_EBUS_2)                            /*!< RxDMA generates error while writing descriptor */
#define ETH_DMA_ERRORSTATE_TX_WRITEDESC             (ETH_DMA_DMASTSR_EBUS_2 | ETH_DMA_DMASTSR_EBUS_0)   /*!< TxDMA generates error while writing descriptor */
#define ETH_DMA_ERRORSTATE_RX_READDESC              (ETH_DMA_DMASTSR_EBUS_2 | ETH_DMA_DMASTSR_EBUS_1)   /*!< RxDMA generates error while reading descriptor */
#define ETH_DMA_ERRORSTATE_TX_READDESC              (ETH_DMA_DMASTSR_EBUS)                              /*!< TxDMA generates error while reading descriptor */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Transmit_State ETH DMA Transmit State
 * @{
 */
#define ETH_DMA_TRANSMITSTATE_STOPPED               (0UL)                                               /*!< Stopped - Reset or Stop Tx Command issued */
#define ETH_DMA_TRANSMITSTATE_FETCHING              (ETH_DMA_DMASTSR_TSTS_0)                            /*!< Running - Fetching the Tx descriptor */
#define ETH_DMA_TRANSMITSTATE_WAITING               (ETH_DMA_DMASTSR_TSTS_1)                            /*!< Running - Waiting for status */
#define ETH_DMA_TRANSMITSTATE_READING               (ETH_DMA_DMASTSR_TSTS_1 | ETH_DMA_DMASTSR_TSTS_0)   /*!< Running - Reading the data from host memory */
#define ETH_DMA_TRANSMITSTATE_WRITING               (ETH_DMA_DMASTSR_TSTS_2)                            /*!< Running - Writing the time stamp */
#define ETH_DMA_TRANSMITSTATE_SUSPENDED             (ETH_DMA_DMASTSR_TSTS_2 | ETH_DMA_DMASTSR_TSTS_1)   /*!< Suspended - Tx Descriptor unavailable */
#define ETH_DMA_TRANSMITSTATE_CLOSING               (ETH_DMA_DMASTSR_TSTS)                              /*!< Running - Closing Rx descriptor */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Receive_State ETH DMA Receive State
 * @{
 */
#define ETH_DMA_RECEIVESTATE_STOPPED                (0UL)                                               /*!< Stopped - Reset or Stop Rx Command issued */
#define ETH_DMA_RECEIVESTATE_FETCHING               (ETH_DMA_DMASTSR_RSTS_0)                            /*!< Running - Fetching the Rx descriptor */
#define ETH_DMA_RECEIVESTATE_WAITING                (ETH_DMA_DMASTSR_RSTS_1 | ETH_DMA_DMASTSR_RSTS_0)   /*!< Running - Waiting for packet */
#define ETH_DMA_RECEIVESTATE_SUSPENDED              (ETH_DMA_DMASTSR_RSTS_2)                            /*!< Suspended - Rx Descriptor unavailable */
#define ETH_DMA_RECEIVESTATE_CLOSING                (ETH_DMA_DMASTSR_RSTS_2 | ETH_DMA_DMASTSR_RSTS_0)   /*!< Running - Closing descriptor */
#define ETH_DMA_RECEIVESTATE_WRITING                (ETH_DMA_DMASTSR_RSTS_2 | ETH_DMA_DMASTSR_RSTS_1)   /*!< Running - Writing the time stamp */
#define ETH_DMA_RECEIVESTATE_QUEUING                (ETH_DMA_DMASTSR_RSTS)                              /*!< Running - Queuing the receive frame into host memory */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Interrupt ETH DMA Interrupt
 * @{
 */
#define ETH_DMA_INT_NIE                             (ETH_DMA_INTENAR_NIE)   /*!< Normal interrupt summary */
#define ETH_DMA_INT_AIE                             (ETH_DMA_INTENAR_AIE)   /*!< Abnormal interrupt summary */
#define ETH_DMA_INT_ERE                             (ETH_DMA_INTENAR_ERE)   /*!< Early receive interrupt */
#define ETH_DMA_INT_FBE                             (ETH_DMA_INTENAR_FBE)   /*!< Fatal bus error interrupt */
#define ETH_DMA_INT_ETE                             (ETH_DMA_INTENAR_ETE)   /*!< Early transmit interrupt */
#define ETH_DMA_INT_RWE                             (ETH_DMA_INTENAR_RWE)   /*!< Receive watchdog timeout interrupt */
#define ETH_DMA_INT_RSE                             (ETH_DMA_INTENAR_RSE)   /*!< Receive process stopped interrupt */
#define ETH_DMA_INT_RUE                             (ETH_DMA_INTENAR_RUE)   /*!< Receive buffer unavailable interrupt */
#define ETH_DMA_INT_RIE                             (ETH_DMA_INTENAR_RIE)   /*!< Receive interrupt */
#define ETH_DMA_INT_UNE                             (ETH_DMA_INTENAR_UNE)   /*!< Transmit Underflow interrupt */
#define ETH_DMA_INT_OVE                             (ETH_DMA_INTENAR_OVE)   /*!< Receive Overflow interrupt */
#define ETH_DMA_INT_TJE                             (ETH_DMA_INTENAR_TJE)   /*!< Transmit jabber timeout interrupt */
#define ETH_DMA_INT_TUE                             (ETH_DMA_INTENAR_TUE)   /*!< Transmit buffer unavailable interrupt */
#define ETH_DMA_INT_TSE                             (ETH_DMA_INTENAR_TSE)   /*!< Transmit process stopped interrupt */
#define ETH_DMA_INT_TIE                             (ETH_DMA_INTENAR_TIE)   /*!< Transmit interrupt */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Overflow ETH DMA Overflow
 * @{
 */
#define ETH_DMA_OVERFLOW_RXFIFO_COUNTER             (ETH_DMA_RFRCNTR_OVFOVF)  /*!< Overflow bit for FIFO overflow counter */
#define ETH_DMA_OVERFLOW_MISSFRAME_COUNTER          (ETH_DMA_RFRCNTR_UNAOVF)  /*!< Overflow bit for miss frame counter */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Descriptor_Own ETH DMA Descriptor Own
 * @{
 */
#define ETH_DMADESC_OWN_CPU                         (0UL)                 /*!< The descriptor is owned by CPU */
#define ETH_DMADESC_OWN_DMA                         (ETH_DMATXDESC_OWN)   /*!< The descriptor is owned by DMA */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Descriptor_Buffer ETH DMA Descriptor Buffer
 * @{
 */
#define ETH_DMADESC_BUFFER1                         ((uint8_t)0x00UL)   /*!< DMA Desc Buffer1 */
#define ETH_DMADESC_BUFFER2                         ((uint8_t)0x01UL)   /*!< DMA Desc Buffer2 */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Tx_Descriptor_Checksum_Insertion_Control ETH DMA Tx Descriptor Checksum Insertion Control
 * @{
 */
#define ETH_DMATXDESC_CHECKSUM_BYPASS               (ETH_DMATXDESC_CIC_BYPASS)              /*!< Checksum Engine is bypassed */
#define ETH_DMATXDESC_CHECKSUM_IPV4HEADER           (ETH_DMATXDESC_CIC_IPV4HEADER)          /*!< IPv4 header checksum insertion  */
#define ETH_DMATXDESC_CHECKSUM_TCPUDPICMP_SEGMENT   (ETH_DMATXDESC_CIC_TCPUDPICMP_SEGMENT)  /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define ETH_DMATXDESC_CHECKSUM_TCPUDPICMP_FULL      (ETH_DMATXDESC_CIC_TCPUDPICMP_FULL)     /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Tx_Descriptor_VLAN_Insertion_Control ETH DMA Tx Descriptor VLAN Insertion Control
 * @{
 */
#define ETH_DMATXDESC_VLAN_BYPASS                   (ETH_DMATXDESC_VLANC_BYPASS)        /*!< VLAN Insertion is bypassed */
#define ETH_DMATXDESC_VLAN_REMOVE_TAG               (ETH_DMATXDESC_VLANC_REMOVE_TAG)    /*!< Remove Tag and Type fields in VLAN frame */
#define ETH_DMATXDESC_VLAN_INSERT_TAG               (ETH_DMATXDESC_VLANC_INSERT_TAG)    /*!< Insert VLAN Tag value in ETH_MAC_VTACTLR Register into transmit frame */
#define ETH_DMATXDESC_VLAN_REPLACE_TAG              (ETH_DMATXDESC_VLANC_REPLACE_TAG)   /*!< Replace VLAN tag value in transmit frame with VLAN tag value in ETH_MAC_VTACTLR register */
/**
 * @}
 */

/**
 * @defgroup ETH_DMA_Tx_Descriptor_SA_Insertion_Control ETH DMA Tx Descriptor SA Insertion Control
 * @{
 */
#define ETH_DMATXDESC_SA_BYPASS                     (ETH_DMATXDESC_SAIRC_BYPASS)            /*!< Source Address Insertion or Replace Control is bypassed */
#define ETH_DMATXDESC_SA_INSTER_MACADDR0            (ETH_DMATXDESC_SAIRC_INSTER_MACADDR0)   /*!< Insert address value in MAC address register 0 into transmit frame as SA address */
#define ETH_DMATXDESC_SA_REPLACE_MACADDR0           (ETH_DMATXDESC_SAIRC_REPLACE_MACADDR0)  /*!< Replace SA address in transmit frame with address value in MAC address register 0 */
#define ETH_DMATXDESC_SA_INSTER_MACADDR1            (ETH_DMATXDESC_SAIRC_INSTER_MACADDR1)   /*!< Insert address value in MAC address register 1 into transmit frame as SA address */
#define ETH_DMATXDESC_SA_REPLACE_MACADDR1           (ETH_DMATXDESC_SAIRC_REPLACE_MACADDR1)  /*!< Replace SA address in transmit frame with address value in MAC address register 1 */
/**
 * @}
 */

/**
 * @defgroup ETH_PMT_Flag ETH PMT Flag
 * @{
 */
#define ETH_PMT_FLAG_RTWKFR                         (ETH_MAC_PMTCTLR_RTWKFR)  /*!< Wake-Up Frame Filter Register Pointer Reset */
#define ETH_PMT_FLAG_WKFR                           (ETH_MAC_PMTCTLR_WKFR)    /*!< Wake-Up Frame Received */
#define ETH_PMT_FLAG_MPFR                           (ETH_MAC_PMTCTLR_MPFR)    /*!< Magic Packet Received */
/**
 * @}
 */

/**
 * @defgroup ETH_PMT_Wakeup_Source ETH PMT Wakeup Source
 * @{
 */
#define ETH_PMT_WAKEUP_GLOBAL_UNICAST               (ETH_MAC_PMTCTLR_GLUB)  /*!< Global unicast */
#define ETH_PMT_WAKEUP_WAKEUP_FRAME                 (ETH_MAC_PMTCTLR_WKEN)  /*!< Wake-Up Frame */
#define ETH_PMT_WAKEUP_MAGIC_PACKET                 (ETH_MAC_PMTCTLR_MPEN)  /*!< Magic Packet */
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Counter_Preset_Mode ETH MMC Counter Preset Mode
 * @{
 */
#define ETH_MMC_COUNTER_PRESETMODE_DISABLE          (0UL)                                               /*!< Disable preset */
#define ETH_MMC_COUNTER_PRESETMODE_HALFVALUE        (ETH_MMC_MMCCTLR_MCPSET)                            /*!< Half-Value preset: 0x7FF0 */
#define ETH_MMC_COUNTER_PRESETMODE_FULLVALUE        (ETH_MMC_MMCCTLR_MCPSEL | ETH_MMC_MMCCTLR_MCPSET)   /*!< Full-Value preset: 0xFFF0 */
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Read_Reset ETH MMC Read Reset
 * @{
 */
#define ETH_MMC_READ_RESET_DISABLE                  (0UL)
#define ETH_MMC_READ_RESET_ENABLE                   (ETH_MMC_MMCCTLR_ROR)
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Counter_Reload ETH MMC Counter Reload
 * @{
 */
#define ETH_MMC_COUNTER_RELOAD_DISABLE              (ETH_MMC_MMCCTLR_COS)
#define ETH_MMC_COUNTER_RELOAD_ENABLE               (0UL)
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Tx_Flag ETH MMC Tx Flag
 * @{
 */
#define ETH_MMC_FLAG_TXEDEIS                        (ETH_MMC_TRSSTSR_TXEDEIS)   /*!< When Tx excessive deferral error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_TXUGIS                         (ETH_MMC_TRSSTSR_TXUGIS)    /*!< When Tx unicast good frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_TXCAEIS                        (ETH_MMC_TRSSTSR_TXCAEIS)   /*!< When Tx carrier error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_TXECEIS                        (ETH_MMC_TRSSTSR_TXECEIS)   /*!< When Tx excessive collision error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_TXLCEIS                        (ETH_MMC_TRSSTSR_TXLCEIS)   /*!< When Tx deferral collision error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_TXDEEIS                        (ETH_MMC_TRSSTSR_TXDEEIS)   /*!< When Tx deferral error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_TXMGIS                         (ETH_MMC_TRSSTSR_TXMGIS)    /*!< When Tx multicast good frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_TXBGIS                         (ETH_MMC_TRSSTSR_TXBGIS)    /*!< When Tx broadcast good frame counter reaches half or all the maximum value */
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Rx_Flag ETH MMC Rx Flag
 * @{
 */
#define ETH_MMC_FLAG_RXOEIS                         (ETH_MMC_REVSTSR_RXOEIS)   /*!< When Rx out of scope error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_RXLEIS                         (ETH_MMC_REVSTSR_RXLEIS)   /*!< When Rx length error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_RXUGIS                         (ETH_MMC_REVSTSR_RXUGIS)   /*!< When Rx unicast good frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_RXREIS                         (ETH_MMC_REVSTSR_RXREIS)   /*!< When Rx short error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_RXAEIS                         (ETH_MMC_REVSTSR_RXAEIS)   /*!< When Rx alignment error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_RXCEIS                         (ETH_MMC_REVSTSR_RXCEIS)   /*!< When Rx crc error frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_RXMGIS                         (ETH_MMC_REVSTSR_RXMGIS)   /*!< When Rx multicast good frame counter reaches half or all the maximum value */
#define ETH_MMC_FLAG_RXBGIS                         (ETH_MMC_REVSTSR_RXBGIS)   /*!< When Rx broadcast good frame counter reaches half or all the maximum value */
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Tx_Interrupt ETH MMC Tx Interrupt
 * @{
 */
#define ETH_MMC_INT_TXEDEIM                         (ETH_MMC_TITCTLR_TXEDEIM)   /*!< Tx excessive deferral error frame interrupt */
#define ETH_MMC_INT_TXUGIM                          (ETH_MMC_TITCTLR_TXUGIM)    /*!< Tx unicast good frame interrupt */
#define ETH_MMC_INT_TXCAEIM                         (ETH_MMC_TITCTLR_TXCAEIM)   /*!< Tx carrier error frame interrupt */
#define ETH_MMC_INT_TXECEIM                         (ETH_MMC_TITCTLR_TXECEIM)   /*!< Tx excessive collision error frame interrupt */
#define ETH_MMC_INT_TXLCEIM                         (ETH_MMC_TITCTLR_TXLCEIM)   /*!< Tx deferral collision error frame interrupt */
#define ETH_MMC_INT_TXDEEIM                         (ETH_MMC_TITCTLR_TXDEEIM)   /*!< Tx deferral error frame interrupt */
#define ETH_MMC_INT_TXMGIM                          (ETH_MMC_TITCTLR_TXMGIM)    /*!< Tx multicast good frame interrupt */
#define ETH_MMC_INT_TXBGIM                          (ETH_MMC_TITCTLR_TXBGIM)    /*!< Tx broadcast good frame interrupt */
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Rx_Interrupt ETH MMC Rx Interrupt
 * @{
 */
#define ETH_MMC_INT_RXOEIM                          (ETH_MMC_RITCTLR_RXOEIM)   /*!< Rx out of scope error frame interrupt */
#define ETH_MMC_INT_RXLEIM                          (ETH_MMC_RITCTLR_RXLEIM)   /*!< Rx length error frame interrupt */
#define ETH_MMC_INT_RXUGIM                          (ETH_MMC_RITCTLR_RXUGIM)   /*!< Rx unicast good frame interrupt */
#define ETH_MMC_INT_RXREIM                          (ETH_MMC_RITCTLR_RXREIM)   /*!< Rx short error frame interrupt */
#define ETH_MMC_INT_RXAEIM                          (ETH_MMC_RITCTLR_RXAEIM)   /*!< Rx alignment error frame interrupt */
#define ETH_MMC_INT_RXCEIM                          (ETH_MMC_RITCTLR_RXCEIM)   /*!< Rx crc error frame interrupt */
#define ETH_MMC_INT_RXMGIM                          (ETH_MMC_RITCTLR_RXMGIM)   /*!< Rx multicast good frame interrupt */
#define ETH_MMC_INT_RXBGIM                          (ETH_MMC_RITCTLR_RXBGIM)   /*!< Rx broadcast good frame interrupt */
/**
 * @}
 */

/**
 * @defgroup ETH_MMC_Statistical_Register ETH MMC Statistical Register
 * @{
 */
#define ETH_MMC_REG_TXBRGFR                         (0x011CU)   /*!< Tx broadcast good frame Statistical Register */
#define ETH_MMC_REG_TXMUGFR                         (0x0120U)   /*!< Tx multicast good frame Statistical Register */
#define ETH_MMC_REG_TXDEEFR                         (0x0154U)   /*!< Tx deferral error frame Statistical Register */
#define ETH_MMC_REG_TXLCEFR                         (0x0158U)   /*!< Tx deferral collision error frame Statistical Register */
#define ETH_MMC_REG_TXECEFR                         (0x015CU)   /*!< Tx excessive collision error frame Statistical Register */
#define ETH_MMC_REG_TXCAEFR                         (0x0160U)   /*!< Tx carrier error frame Statistical Register */
#define ETH_MMC_REG_TXUNGFR                         (0x0168U)   /*!< Tx unicast good frame Statistical Register */
#define ETH_MMC_REG_TXEDEFR                         (0x016CU)   /*!< Tx excessive deferral error frame Statistical Register */
#define ETH_MMC_REG_RXBRGFR                         (0x018CU)   /*!< Rx broadcast good frame Statistical Register */
#define ETH_MMC_REG_RXMUGFR                         (0x0190U)   /*!< Rx multicast good frame Statistical Register */
#define ETH_MMC_REG_RXCREFR                         (0x0194U)   /*!< Rx crc error frame Statistical Register */
#define ETH_MMC_REG_RXALEFR                         (0x0198U)   /*!< Rx alignment error frame Statistical Register */
#define ETH_MMC_REG_RXRUEFR                         (0x019CU)   /*!< Rx short error frame Statistical Register */
#define ETH_MMC_REG_RXUNGFR                         (0x01C4U)   /*!< Rx unicast good frame Statistical Register */
#define ETH_MMC_REG_RXLEEFR                         (0x01C8U)   /*!< Rx length error frame Statistical Register */
#define ETH_MMC_REG_RXOREFR                         (0x01CCU)   /*!< Rx out of scope error frame Statistical Register */
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Frame_DA_Filter ETH PTP Frame DA Filter
 * @{
 */
#define ETH_PTP_FRAME_DA_FILTER_DISABLE             (0x00800000UL)
#define ETH_PTP_FRAME_DA_FILTER_ENABLE              (ETH_PTP_TSPCTLR_TSPADF)
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Snapshot_Datagram_Type ETH PTP Snapshot Datagram Type
 * @{
 */
#define ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY             (0UL)                                                                                   /*!< SYNC Follow_Up Delay_Req Delay_Resp */
#define ETH_PTP_DATAGRAM_TYPE_SYNC                          (ETH_PTP_TSPCTLR_TSPMTSEL_0)                                                            /*!< SYNC */
#define ETH_PTP_DATAGRAM_TYPE_DELAY                         (ETH_PTP_TSPCTLR_TSPMTSEL_1 | ETH_PTP_TSPCTLR_TSPMTSEL_0)                               /*!< Delay_Req */
#define ETH_PTP_DATAGRAM_TYPE_SYNC_FOLLOW_DELAY_PDELAY      (ETH_PTP_TSPCTLR_TSPMTSEL_2)                                                            /*!< SYNC Follow_Up Delay_Req Delay_Resp Pdelay_Req Pdelay_Resp Pdelay_Resp_Follow_Up */
#define ETH_PTP_DATAGRAM_TYPE_SYNC_PDELAY                   (ETH_PTP_TSPCTLR_TSPMTSEL_2 | ETH_PTP_TSPCTLR_TSPMTSEL_0)                               /*!< SYNC Pdelay_Req Pdelay_Resp */
#define ETH_PTP_DATAGRAM_TYPE_DELAY_PDEALY                  (ETH_PTP_TSPCTLR_TSPMTSEL_2 | ETH_PTP_TSPCTLR_TSPMTSEL_1 | ETH_PTP_TSPCTLR_TSPMTSEL_0)  /*!< Delay_Req Pdelay_Req Pdelay_Resp */
#define ETH_PTP_DATAGRAM_TYPE_SYNC_DELAY                    (ETH_PTP_TSPCTLR_TSPMTSEL_3)                                                            /*!< SYNC Delay_Req */
#define ETH_PTP_DATAGRAM_TYPE_PDELAY                        (ETH_PTP_TSPCTLR_TSPMTSEL_3 | ETH_PTP_TSPCTLR_TSPMTSEL_2)                               /*!< Pdelay_Req Pdelay_Resp */
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Snapshot_Frame_Type ETH PTP Snapshot Frame Type
 * @{
 */
#define ETH_PTP_FRAME_TYPE_IPV4FRAME                (ETH_PTP_TSPCTLR_TSPOVIPV4)   /*!< Time stamp snapshot for IPv4 frame */
#define ETH_PTP_FRAME_TYPE_IPV6FRAME                (ETH_PTP_TSPCTLR_TSPOVIPV6)   /*!< Time stamp snapshot for IPv6 frame */
#define ETH_PTP_FRAME_TYPE_ETHERNETFRAME            (ETH_PTP_TSPCTLR_TSPOVETH)    /*!< Time stamp snapshot for PTP over ethernet frame */
#define ETH_PTP_FRAME_TYPE_ALL_RECEIVEFRAME         (ETH_PTP_TSPCTLR_TSPEALL)     /*!< Time stamp snapshot for all received frame */
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Datagram_Version ETH PTP Datagram Version
 * @{
 */
#define ETH_PTP_DATAGRAM_VERSION_IEEE1588V1         (0UL)
#define ETH_PTP_DATAGRAM_VERSION_IEEE1588V2         (ETH_PTP_TSPCTLR_TSPVER)
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Subsecond_Scale ETH PTP Subsecond Scale
 * @{
 */
#define ETH_PTP_SUBSECOND_SCALE_HEX                 (0UL)                     /*!< The Second register increase 1 when SubSecond count to 0x7FFFFFFFH */
#define ETH_PTP_SUBSECOND_SCALE_DEC                 (ETH_PTP_TSPCTLR_TSPSSR)  /*!< The Second register increase 1 when SubSecond count to 0x3B9AC9FFH */
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Calibration_Mode ETH PTP Calibration Mode
 * @{
 */
#define ETH_PTP_CALIBRATION_MODE_COARSE             (0UL)                       /*!< Coarse calibration */
#define ETH_PTP_CALIBRATION_MODE_FINE               (ETH_PTP_TSPCTLR_TSPUPSEL)  /*!< Fine calibration */
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Time_Update_Sign ETH PTP Time Update Sign
 * @{
 */
#define ETH_PTP_TIME_UPDATE_SIGN_MINUS              (0UL)                       /*!< Minus for update register value */
#define ETH_PTP_TIME_UPDATE_SIGN_PLUS               (ETH_PTP_TMUNSER_TSPUPNS)   /*!< Plus for update register value */
/**
 * @}
 */

/**
 * @defgroup ETH_PTP_Flag ETH PTP Flag
 * @{
 */
#define ETH_PTP_FLAG_TSERR1                         (ETH_PTP_TSPSTSR_TSERR1)  /*!< Target time 1 error */
#define ETH_PTP_FLAG_TSTAR1                         (ETH_PTP_TSPSTSR_TSTAR1)  /*!< Target time 1 reached  */
#define ETH_PTP_FLAG_TSERR0                         (ETH_PTP_TSPSTSR_TSERR0)  /*!< Target time 0 error */
#define ETH_PTP_FLAG_TSTAR0                         (ETH_PTP_TSPSTSR_TSTAR0)  /*!< Target time 0 reached */
#define ETH_PTP_FLAG_TSOVF                          (ETH_PTP_TSPSTSR_TSOVF)   /*!< System time overflow */
/**
 * @}
 */

/**
 * @defgroup ETH_PPS_Target_Channel ETH PPS Target Channel
 * @{
 */
#define ETH_PPS_TARGET_CH0                          (0x00U)
#define ETH_PPS_TARGET_CH1                          (0x01U)
/**
 * @}
 */

/**
 * @defgroup ETH_PPS_Target_Time_Function ETH PPS Target Time Function
 * @{
 */
#define ETH_PPS_TARGET_TIME_FUNC_INT_EVENT          (0UL)                       /*!< The Target register is used only for interrupt output event */
#define ETH_PPS_TARGET_TIME_FUNC_INT_PPS_EVENT      (ETH_PTP_PPSCTLR_TT0SEL_1)  /*!< The Target register is used for interrupt out event and PPS single output event */
#define ETH_PPS_TARGET_TIME_FUNC_PPS_EVENT          (ETH_PTP_PPSCTLR_TT0SEL)    /*!< The Target register is used for PPS single output event */
/**
 * @}
 */

/**
 * @defgroup ETH_PPS_Output_Mode ETH PPS Output Mode
 * @note PPS1(ETH_PPS_TARGET_CH1) only supports single output mode(ETH_PPS_OUTPUT_MODE_SINGLE).
 * @{
 */
#define ETH_PPS_OUTPUT_MODE_CONTINUE                (0UL)                     /*!< Continuous output mode */
#define ETH_PPS_OUTPUT_MODE_SINGLE                  (ETH_PTP_PPSCTLR_PPSOMD)  /*!< Single output mode */
/**
 * @}
 */

/**
 * @defgroup ETH_PPS_Output_Frequency ETH PPS Output Frequency
 * @note PPS1(ETH_PPS_TARGET_CH1) only supports generate a pulse(ETH_PPS_OUTPUT_ONE_PULSE).
 * @{
 */
#define ETH_PPS_OUTPUT_FREQ_1HZ                     (0UL)                                                                                 /*!< Ouput pulse is 1HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_2HZ                     (ETH_PTP_PPSCTLR_PPSFRE0_0)                                                           /*!< Ouput pulse is 2HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_4HZ                     (ETH_PTP_PPSCTLR_PPSFRE0_1)                                                           /*!< Ouput pulse is 4HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_8HZ                     (ETH_PTP_PPSCTLR_PPSFRE0_1 | ETH_PTP_PPSCTLR_PPSFRE0_0)                               /*!< Ouput pulse is 8HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_16HZ                    (ETH_PTP_PPSCTLR_PPSFRE0_2)                                                           /*!< Ouput pulse is 16HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_32HZ                    (ETH_PTP_PPSCTLR_PPSFRE0_2 | ETH_PTP_PPSCTLR_PPSFRE0_0)                               /*!< Ouput pulse is 32HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_64HZ                    (ETH_PTP_PPSCTLR_PPSFRE0_2 | ETH_PTP_PPSCTLR_PPSFRE0_1)                               /*!< Ouput pulse is 64HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_128HZ                   (ETH_PTP_PPSCTLR_PPSFRE0_2 | ETH_PTP_PPSCTLR_PPSFRE0_1 | ETH_PTP_PPSCTLR_PPSFRE0_0)   /*!< Ouput pulse is 128HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_256HZ                   (ETH_PTP_PPSCTLR_PPSFRE0_3)                                                           /*!< Ouput pulse is 256HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_512HZ                   (ETH_PTP_PPSCTLR_PPSFRE0_3 | ETH_PTP_PPSCTLR_PPSFRE0_0)                               /*!< Ouput pulse is 512HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_1024HZ                  (ETH_PTP_PPSCTLR_PPSFRE0_3 | ETH_PTP_PPSCTLR_PPSFRE0_1)                               /*!< Ouput pulse is 1024HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_2048HZ                  (ETH_PTP_PPSCTLR_PPSFRE0_3 | ETH_PTP_PPSCTLR_PPSFRE0_1 | ETH_PTP_PPSCTLR_PPSFRE0_0)   /*!< Ouput pulse is 2048HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_4096HZ                  (ETH_PTP_PPSCTLR_PPSFRE0_3 | ETH_PTP_PPSCTLR_PPSFRE0_2)                               /*!< Ouput pulse is 4096HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_8192HZ                  (ETH_PTP_PPSCTLR_PPSFRE0_3 | ETH_PTP_PPSCTLR_PPSFRE0_2 | ETH_PTP_PPSCTLR_PPSFRE0_0)   /*!< Ouput pulse is 8192HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_16384HZ                 (ETH_PTP_PPSCTLR_PPSFRE0_3 | ETH_PTP_PPSCTLR_PPSFRE0_2 | ETH_PTP_PPSCTLR_PPSFRE0_1)   /*!< Ouput pulse is 16384HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_FREQ_32768HZ                 (ETH_PTP_PPSCTLR_PPSFRE0)                                                             /*!< Ouput pulse is 32768HZ in continuous ouput mode */
#define ETH_PPS_OUTPUT_ONE_PULSE                    (ETH_PTP_PPSCTLR_PPSFRE0_0)                                                           /*!< One pulse is generated in single ouput mode */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup ETH_Global_Functions
 * @{
 */

/**
 * @brief  Generate MAC pause control frame.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void ETH_MAC_GeneratePauseCtrlFrame(void)
{
    WRITE_REG32(bM4_ETH->MAC_FLOCTLR_b.FCA_BPA, Enable);
}

/**
 * @brief  Get MAC flow control status.
 * @param  None
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
__STATIC_INLINE en_flag_status_t ETH_MAC_GetFlowCtrlStatus(void)
{
    return ((en_flag_status_t)READ_REG32(bM4_ETH->MAC_FLOCTLR_b.FCA_BPA));
}

/**
 * @brief  Resume the DMA Transmit.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void ETH_DMA_ResumeTransmit(void)
{
    WRITE_REG32(M4_ETH->DMA_TXPOLLR, 0U);
}

/**
 * @brief  Resume the DMA Receive.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void ETH_DMA_ResumeReceive(void)
{
    WRITE_REG32(M4_ETH->DMA_RXPOLLR, 0U);
}

/**
 * @brief  Get DMA error status.
 * @param  None
 * @retval uint32_t                         The new DMA error status
 *         The error status may be one of the following values:
 *           - ETH_DMA_ERRORSTATE_RX_WRITEDATA:   TxDMA generates error while reading descriptor
 *           - ETH_DMA_ERRORSTATE_TX_READDATA:    TxDMA generates error while reading descriptor
 *           - ETH_DMA_ERRORSTATE_RX_WRITEDESC:   TxDMA generates error while reading descriptor
 *           - ETH_DMA_ERRORSTATE_TX_WRITEDESC:   TxDMA generates error while reading descriptor
 *           - ETH_DMA_ERRORSTATE_RX_READDESC:    TxDMA generates error while reading descriptor
 *           - ETH_DMA_ERRORSTATE_TX_READDESC:    TxDMA generates error while reading descriptor
 */
__STATIC_INLINE uint32_t ETH_DMA_GetErrorStatus(void)
{
    return (READ_REG32_BIT(M4_ETH->DMA_DMASTSR, ETH_DMA_DMASTSR_EBUS));
}

/**
 * @brief  Get DMA transmit status.
 * @param  None
 * @retval uint32_t                         The new DMA transmit status
 *           The transmit status may be one of the following values:
 *           - ETH_DMA_TRANSMITSTATE_STOPPED:     Stopped - Reset or Stop Tx Command issued
 *           - ETH_DMA_TRANSMITSTATE_FETCHING:    Running - Fetching the Tx descriptor
 *           - ETH_DMA_TRANSMITSTATE_WAITING:     Running - Waiting for status
 *           - ETH_DMA_TRANSMITSTATE_READING:     Running - Reading the data from host memory
 *           - ETH_DMA_TRANSMITSTATE_WRITING:     Running - Writing the time stamp
 *           - ETH_DMA_TRANSMITSTATE_SUSPENDED:   Suspended - Tx Descriptor unavailable
 *           - ETH_DMA_TRANSMITSTATE_CLOSING:     Running - Closing Rx descriptor
 */
__STATIC_INLINE uint32_t ETH_DMA_GetTransmitStatus(void)
{
    return (READ_REG32_BIT(M4_ETH->DMA_DMASTSR, ETH_DMA_DMASTSR_TSTS));
}

/**
 * @brief  Get DMA receive status.
 * @param  None
 * @retval uint32_t                         The new DMA receive status
 *           The receive status may be one of the following values:
 *           - ETH_DMA_RECEIVESTATE_STOPPED:      Stopped - Reset or Stop Rx Command issued
 *           - ETH_DMA_RECEIVESTATE_FETCHING:     Running - Fetching the Rx descriptor
 *           - ETH_DMA_RECEIVESTATE_WAITING:      Running - Waiting for packet
 *           - ETH_DMA_RECEIVESTATE_SUSPENDED:    Suspended - Rx Descriptor unavailable
 *           - ETH_DMA_RECEIVESTATE_CLOSING:      Running - Closing descriptor
 *           - ETH_DMA_RECEIVESTATE_WRITING:      Running - Writing the time stamp
 *           - ETH_DMA_RECEIVESTATE_QUEUING:      Running - Queuing the receive frame into host memory
 */
__STATIC_INLINE uint32_t ETH_DMA_GetReceiveStatus(void)
{
    return (READ_REG32_BIT(M4_ETH->DMA_DMASTSR, ETH_DMA_DMASTSR_RSTS));
}

/**
 * @brief  Get DMA Rx Overflow Missed Frame Counter value.
 * @param  None
 * @retval uint32_t                         Rx Overflow Missed Frame Counter value
 */
__STATIC_INLINE uint32_t ETH_DMA_GetRxOvfMissFrameCnt(void)
{
    return ((READ_REG32_BIT(M4_ETH->DMA_RFRCNTR, ETH_DMA_RFRCNTR_OVFCNT)) >> ETH_DMA_RFRCNTR_OVFCNT_POS);
}

/**
 * @brief  Get DMA Buffer Unavailable Missed Frame Counter value.
 * @param  None
 * @retval uint32_t                         Buffer Unavailable Missed Frame Counter value
 */
__STATIC_INLINE uint32_t ETH_DMA_GetBufferUnavaiMissFrameCnt(void)
{
    return (READ_REG32_BIT(M4_ETH->DMA_RFRCNTR, ETH_DMA_RFRCNTR_UNACNT));
}

/**
 * @brief  Get DMA current Tx descriptor start address.
 * @param  None
 * @retval uint32_t                         Transmit descriptor start address
 */
__STATIC_INLINE uint32_t ETH_DMA_GetCurTxDescAddr(void)
{
    return (READ_REG32(M4_ETH->DMA_CHTXDER));
}

/**
 * @brief  Get DMA current Rx descriptor start address.
 * @param  None
 * @retval uint32_t                         Receive descriptor start address
 */
__STATIC_INLINE uint32_t ETH_DMA_GetCurRxDescAddr(void)
{
    return (READ_REG32(M4_ETH->DMA_CHRXDER));
}

/**
 * @brief  Get DMA current Tx buffer address.
 * @param  None
 * @retval uint32_t                         Transmit buffer address
 */
__STATIC_INLINE uint32_t ETH_DMA_GetCurTxBufferAddr(void)
{
    return (READ_REG32(M4_ETH->DMA_CHTXBFR));
}

/**
 * @brief  Get DMA current Rx buffer address.
 * @param  None
 * @retval uint32_t                         Receive buffer address
 */
__STATIC_INLINE uint32_t ETH_DMA_GetCurRxBufferAddr(void)
{
    return (READ_REG32(M4_ETH->DMA_CHRXBFR));
}

/**
 * @brief  Get PMT wakeup frame filter register pointer index.
 * @param  None
 * @retval uint8_t                          Filter register pointer index.
 */
__STATIC_INLINE uint8_t ETH_PMT_GetWakeupFramePointerIndex(void)
{
    return ((uint8_t)(READ_REG32_BIT(M4_ETH->MAC_PMTCTLR, ETH_MAC_PMTCTLR_RTWKPT) >> ETH_MAC_PMTCTLR_RTWKPT_POS));
}

/**
 * @brief  Get PTP snapshot frame type.
 * @param  None
 * @retval uint32_t                         Receive frame type
 */
__STATIC_INLINE uint32_t ETH_PTP_GetSnapFrameType(void)
{
    return (READ_REG32_BIT(M4_ETH->PTP_TSPCTLR,
                           (ETH_PTP_TSPCTLR_TSPOVIPV4 | ETH_PTP_TSPCTLR_TSPOVIPV6 |
                            ETH_PTP_TSPCTLR_TSPOVETH  | ETH_PTP_TSPCTLR_TSPEALL)));
}

en_result_t ETH_DeInit(void);
en_result_t ETH_Init(stc_eth_handle_t *pstcEthHandle, stc_eth_init_t *pstcEthInit);
en_result_t ETH_CommStructInit(stc_eth_comm_init_t *pstcCommInit);
en_result_t ETH_StructInit(stc_eth_init_t *pstcEthInit);
en_result_t ETH_Start(void);
en_result_t ETH_Stop(void);

/* PHY Functions */
en_result_t ETH_PHY_WriteRegister(stc_eth_handle_t *pstcEthHandle, uint16_t u16Reg, uint16_t u16RegVal);
en_result_t ETH_PHY_ReadRegister(stc_eth_handle_t *pstcEthHandle, uint16_t u16Reg, uint16_t *pu16RegVal);
en_result_t ETH_PHY_LoopBackCmd(stc_eth_handle_t *pstcEthHandle, en_functional_state_t enNewSta);

/* MAC Functions */
void ETH_MAC_DeInit(void);
en_result_t ETH_MAC_Init(stc_eth_handle_t *pstcEthHandle, const stc_eth_mac_init_t *pstcMacInit);
en_result_t ETH_MAC_StructInit(stc_eth_mac_init_t *pstcMacInit);
void ETH_MAC_SetDuplexSpeed(uint32_t u32DuplexMode, uint32_t u32Speed);
void ETH_MAC_SetHashTable(uint32_t u32HashHigh, uint32_t u32HashLow);
void ETH_MAC_SetTxVlanTagVal(uint16_t u16TxTag);
void ETH_MAC_SetRxVlanTagVal(uint16_t u16RxTag);
void ETH_MAC_SetRxVlanHashTable(uint16_t u16HashVal);
void ETH_MAC_LoopBackCmd(en_functional_state_t enNewSta);
void ETH_MAC_GeneratePauseCtrlFrame(void);
void ETH_MAC_BackPressureCmd(en_functional_state_t enNewSta);
void ETH_MAC_TransmitCmd(en_functional_state_t enNewSta);
void ETH_MAC_ReceiveCmd(en_functional_state_t enNewSta);
void ETH_MAC_IntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta);
en_flag_status_t ETH_MAC_GetIntStatus(uint32_t u32Flag);
en_flag_status_t ETH_MAC_GetFlowCtrlStatus(void);

/* MAC Address Functions */
void ETH_MACADDR_DeInit(uint32_t u32Index);
en_result_t ETH_MACADDR_Init(uint32_t u32Index, const stc_eth_mac_addr_config_t *pstcMacAddrInit);
en_result_t ETH_MACADDR_StructInit(stc_eth_mac_addr_config_t *pstcMacAddrInit);
en_result_t ETH_MACADDR_SetAddress(uint32_t u32Index, uint8_t au8Addr[]);
en_result_t ETH_MACADDR_GetAddress(uint32_t u32Index, uint8_t au8Addr[]);
void ETH_MACADDR_SetFilterMode(uint32_t u32Index, uint32_t u32Mode);
void ETH_MACADDR_SetFilterMask(uint32_t u32Index, uint32_t u32Mask);

/* MAC L3L4 Filter Functions */
void ETH_MAC_L3L4FilterDeInit(void);
en_result_t ETH_MAC_L3L4FilterInit(const stc_eth_l3l4_filter_config_t *pstcL3L4FilterInit);
en_result_t ETH_MAC_L3L4FilterStructInit(stc_eth_l3l4_filter_config_t *pstcL3L4FilterInit);
void ETH_MAC_L3L4FilterCmd(en_functional_state_t enNewSta);
void ETH_MAC_SetPortFilterProtocol(uint32_t u32PortProtocol);
void ETH_MAC_SetDestPortFilterVal(uint16_t u16Port);
void ETH_MAC_SetSrcPortFilterVal(uint16_t u16Port);
void ETH_MAC_SetAddrFilterProtocol(uint32_t u32AddrProtocol);
void ETH_MAC_SetIpv4DestAddrFilterVal(uint32_t u32Addr);
void ETH_MAC_SetIpv4SrcAddrFilterVal(uint32_t u32Addr);
en_result_t ETH_MAC_SetIpv6AddrFilterVal(const uint32_t au32Addr[]);

/* DMA Functions */
void ETH_DMA_DeInit(void);
en_result_t ETH_DMA_Init(const stc_eth_dma_init_t *pstcDmaInit);
en_result_t ETH_DMA_StructInit(stc_eth_dma_init_t *pstcDmaInit);
en_result_t ETH_DMA_SoftwareReset(void);
void ETH_DMA_ResumeTransmit(void);
void ETH_DMA_ResumeReceive(void);
void ETH_DMA_SetTransPrioRatio(uint32_t u32PrioRatio);
void ETH_DMA_SetRxWatchdogCounter(uint8_t u8Value);
en_result_t ETH_DMA_FlushTransmitFIFO(void);
void ETH_DMA_TransmitCmd(en_functional_state_t enNewSta);
void ETH_DMA_ReceiveCmd(en_functional_state_t enNewSta);
void ETH_DMA_IntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta);
en_flag_status_t ETH_DMA_GetStatus(uint32_t u32Flag);
uint32_t ETH_DMA_GetErrorStatus(void);
uint32_t ETH_DMA_GetTransmitStatus(void);
uint32_t ETH_DMA_GetReceiveStatus(void);
en_flag_status_t ETH_DMA_GetOvfStatus(uint32_t u32Flag);
uint32_t ETH_DMA_GetRxOvfMissFrameCnt(void);
uint32_t ETH_DMA_GetBufferUnavaiMissFrameCnt(void);
uint32_t ETH_DMA_GetCurTxDescAddr(void);
uint32_t ETH_DMA_GetCurRxDescAddr(void);
uint32_t ETH_DMA_GetCurTxBufferAddr(void);
uint32_t ETH_DMA_GetCurRxBufferAddr(void);

/* DMA descriptor Functions */
en_result_t ETH_DMA_TxDescListInit(stc_eth_handle_t *pstcEthHandle, stc_eth_dma_desc_t astcTxDescTab[], const uint8_t au8TxBuffer[], uint32_t u32TxBufferCnt);
en_result_t ETH_DMA_RxDescListInit(stc_eth_handle_t *pstcEthHandle, stc_eth_dma_desc_t astcRxDescTab[], const uint8_t au8RxBuffer[], uint32_t u32RxBufferCnt);
en_result_t ETH_DMA_SetTransmitFrame(stc_eth_handle_t *pstcEthHandle, uint32_t u32FrameLength);
en_result_t ETH_DMA_GetReceiveFrame(stc_eth_handle_t *pstcEthHandle);
en_result_t ETH_DMA_GetReceiveFrame_Interrupt(stc_eth_handle_t *pstcEthHandle);
en_result_t ETH_DMA_SetTxDescOwn(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32Owner);
en_result_t ETH_DMA_SetTxDescBufferSize(stc_eth_dma_desc_t *pstcTxDesc, uint8_t u8BufferNum, uint32_t u32BufferSize);
en_result_t ETH_DMA_TxDescChecksumInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32ChecksumMode);
en_result_t ETH_DMA_TxDescVlanInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32VlanMode);
en_result_t ETH_DMA_TxDescSAInsertConfig(stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32SAMode);
en_result_t ETH_DMA_TxDescCRCCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta);
en_result_t ETH_DMA_TxDescPADCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta);
en_result_t ETH_DMA_TxDescTimestamp(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta);
en_result_t ETH_DMA_TxDescReplaceCRCCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta);
en_result_t ETH_DMA_TxDescIntCmd(stc_eth_dma_desc_t *pstcTxDesc, en_functional_state_t enNewSta);
en_flag_status_t ETH_DMA_GetTxDescStatus(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t u32Flag);
en_result_t ETH_DMA_GetTxDescCollisionCnt(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t *pu32ColliCnt);
en_result_t ETH_DMA_GetTxDescTimeStamp(const stc_eth_dma_desc_t *pstcTxDesc, uint32_t *pu32High, uint32_t *pu32Low);
en_result_t ETH_DMA_SetRxDescOwn(stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Owner);
en_result_t ETH_DMA_RxDescIntCmd(stc_eth_dma_desc_t *pstcRxDesc, en_functional_state_t enNewSta);
en_flag_status_t ETH_DMA_GetRxDescStatus(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Flag);
en_flag_status_t ETH_DMA_GetRxDescExtendStatus(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t u32Flag);
en_result_t ETH_DMA_GetRxDescPayloadType(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32PayloadType);
en_result_t ETH_DMA_GetRxDescDatagramType(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32DatagramType);
en_result_t ETH_DMA_GetRxDescFrameLength(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32FrameLength);
en_result_t ETH_DMA_GetRxDescBufferSize(const stc_eth_dma_desc_t *pstcRxDesc, uint8_t u8BufferNum, uint32_t *pu32BufferSize);
en_result_t ETH_DMA_GetRxDescTimeStamp(const stc_eth_dma_desc_t *pstcRxDesc, uint32_t *pu32High, uint32_t *pu32Low);

/* MAC PMT Functions */
en_result_t ETH_PMT_ResetWakeupFramePointer(void);
en_result_t ETH_PMT_WriteWakeupFrameRegister(const uint32_t au32RegBuffer[]);
void ETH_PMT_ForwardWakeupFrameCmd(en_functional_state_t enNewSta);
void ETH_PMT_WakeupSourceCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewSta);
en_result_t ETH_PMT_EnterPowerDown(void);
en_flag_status_t ETH_PMT_GetStatus(uint32_t u32Flag);
uint8_t ETH_PMT_GetWakeupFramePointerIndex(void);

/* MMC Functions */
en_result_t ETH_MMC_DeInit(void);
en_result_t ETH_MMC_Init(const stc_eth_mmc_init_t *pstcMmcInit);
en_result_t ETH_MMC_StructInit(stc_eth_mmc_init_t *pstcMmcInit);
en_result_t ETH_MMC_CounterReset(void);
void ETH_MMC_ResetAfterReadCmd(en_functional_state_t enNewSta);
void ETH_MMC_Cmd(en_functional_state_t enNewSta);
void ETH_MMC_TxIntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta);
void ETH_MMC_RxIntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta);
en_flag_status_t ETH_MMC_GetTxStatus(uint32_t u32Flag);
en_flag_status_t ETH_MMC_GetRxStatus(uint32_t u32Flag);
uint32_t ETH_MMC_GetRegister(uint32_t u32Reg);

/* PTP Functions */
void ETH_PTP_DeInit(void);
en_result_t ETH_PTP_Init(const stc_eth_ptp_init_t *pstcPtpInit);
en_result_t ETH_PTP_StructInit(stc_eth_ptp_init_t *pstcPtpInit);
void ETH_PTP_SetSnapDatagramType(uint32_t u32DatagramType);
void ETH_PTP_SetSnapFrameType(uint32_t u32FrameType);
uint32_t ETH_PTP_GetSnapFrameType(void);
void ETH_PTP_SetCalibMode(uint32_t u32CalibMode);
en_result_t ETH_PTP_UpdateBasicIncValue(void);
en_result_t ETH_PTP_UpdateSystemTime(void);
en_result_t ETH_PTP_SystemTimeInit(void);
en_result_t ETH_PTP_GetSystemTime(uint32_t *pu32Sec, uint32_t *pu32SubSec);
void ETH_PTP_SetIncValue(uint32_t u32BasicVal, uint8_t u8SubSecVal);
en_result_t ETH_PTP_GetIncValue(uint32_t *pu32BasicVal, uint8_t *pu8SubSecVal);
void ETH_PTP_SetUpdateTime(uint32_t u32Sign, uint32_t u32Sec, uint32_t u32SubSec);
void ETH_PTP_Cmd(en_functional_state_t enNewSta);
void ETH_PTP_IntCmd(en_functional_state_t enNewSta);
en_flag_status_t ETH_PTP_GetStatus(uint32_t u32Flag);

/* PTP PPS Functions */
void ETH_PPS_DeInit(uint8_t u8Ch);
en_result_t ETH_PPS_Init(uint8_t u8Ch, const stc_eth_pps_config_t *pstcPpsInit);
en_result_t ETH_PPS_StructInit(stc_eth_pps_config_t *pstcPpsInit);
void ETH_PPS_SetTargetTime(uint8_t u8Ch, uint32_t u32Sec, uint32_t u32SubSec);
void ETH_PPS_SetTargetTimeFunc(uint8_t u8Ch, uint32_t u32Func);
void ETH_PPS_SetPps0OutputMode(uint32_t u32OutputMode);
void ETH_PPS_SetPps0OutputFreq(uint32_t u32OutputFreq);

/**
 * @}
 */

#endif /* DDL_ETH_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_ETH_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
