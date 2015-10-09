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

#ifndef __FSL_ENET_HAL_H__
#define __FSL_ENET_HAL_H__
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "core_cmInstr.h"
#if FSL_FEATURE_SOC_ENET_COUNT

/*!
 * @addtogroup enet_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the system endian type.*/

/*! @brief Defines the alignment operation.*/
#define ENET_ALIGN(x,align)        ((unsigned int)((x) + ((align)-1)) & (unsigned int)(~(unsigned int)((align)- 1)))
/*! @brief Defines the macro used for byte order change on Buffer descriptor*/
#if FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY 
#define BD_SHORTSWAP(n)                     __REV16(n)
#define BD_LONGSWAP(n)                      __REV(n)
#else
#define BD_SHORTSWAP(n)                      (n)
#define BD_LONGSWAP(n)                       (n)
#endif

/*! @brief Defines the Status return codes.*/
typedef enum _enet_status
{
    kStatus_ENET_Success = 0U,
    kStatus_ENET_InvalidInput,       /*!< Invalid ENET input parameter */
    kStatus_ENET_InvalidDevice,      /*!< Invalid ENET device*/
    kStatus_ENET_InitTimeout,        /*!< ENET initialize timeout*/
    kStatus_ENET_MemoryAllocateFail, /*!< Memory allocate failure*/
    kStatus_ENET_GetClockFreqFail,   /*!< Get clock frequency failure*/
    kStatus_ENET_Initialized,        /*!< ENET device already initialized*/
    kStatus_ENET_Open,       /*!< Open ENET device*/
    kStatus_ENET_Close,     /*!< Close ENET device*/
    kStatus_ENET_Layer2UnInitialized,    /*!< Layer2 PTP buffer queue uninitialized*/
    kStatus_ENET_Layer2OverLarge,    /*!< Layer2 packet length over large*/
    kStatus_ENET_Layer2BufferFull,   /*!< Layer2 packet buffer full*/
    kStatus_ENET_Layer2TypeError,  /*!< Layer2 packet error type*/
    kStatus_ENET_PtpringBufferFull,  /*!< PTP ring buffer full*/
    kStatus_ENET_PtpringBufferEmpty, /*!< PTP ring buffer empty*/
    kStatus_ENET_SMIUninitialized,   /*!< SMI uninitialized*/
    kStatus_ENET_SMIVisitTimeout,    /*!< SMI visit timeout*/
    kStatus_ENET_RxbdInvalid,        /*!< Receive buffer descriptor invalid*/
    kStatus_ENET_RxbdEmpty,          /*!< Receive buffer descriptor empty*/
    kStatus_ENET_RxbdTrunc,          /*!< Receive buffer descriptor truncate*/
    kStatus_ENET_RxbdError,          /*!< Receive buffer descriptor error*/
    kStatus_ENET_RxBdFull,           /*!< Receive buffer descriptor full*/
    kStatus_ENET_SmallRxBuffSize,    /*!< Receive buffer size is so small*/
    kStatus_ENET_NoEnoughRxBuffers,  /*!< Small receive buffer size*/
    kStatus_ENET_LargeBufferFull,    /*!< Receive large buffer full*/
    kStatus_ENET_TxLarge,            /*!< Transmit large packet*/
    kStatus_ENET_TxbdFull,           /*!< Transmit buffer descriptor full*/
    kStatus_ENET_TxbdNull,           /*!< Transmit buffer descriptor Null*/
    kStatus_ENET_TxBufferNull,       /*!< Transmit data buffer Null*/
    kStatus_ENET_NoRxBufferLeft,       /*!< No more receive buffer left*/
    kStatus_ENET_UnknownCommand,     /*!< Invalid ENET PTP IOCTL command*/
    kStatus_ENET_TimeOut,            /*!< ENET timeout*/
    kStatus_ENET_MulticastPointerNull, /*!< Null multicast group pointer*/
    kStatus_ENET_NoMulticastAddr,   /*!< No multicast group address*/
    kStatus_ENET_AlreadyAddedMulticast, /*!< Already added to multicast group*/
    kStatus_ENET_PHYAutoDiscoverFail /*!< Failed to automatically discover PHY*/
} enet_status_t;

#if FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY 
/*! @brief Defines the control and status regions of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_status
{
    kEnetRxBdBroadCast       = 0x8000U,    /*!< Broadcast */
    kEnetRxBdMultiCast       = 0x4000U,    /*!< Multicast*/
    kEnetRxBdLengthViolation = 0x2000U,    /*!< Receive length violation*/
    kEnetRxBdNoOctet         = 0x1000U,    /*!< Receive non-octet aligned frame*/
    kEnetRxBdCrc             = 0x0400U,    /*!< Receive CRC error*/
    kEnetRxBdOverRun         = 0x0200U,    /*!< Receive FIFO overrun*/
    kEnetRxBdTrunc           = 0x0100U,    /*!< Frame is truncated */
    kEnetRxBdEmpty           = 0x0080U,    /*!< Empty bit*/
    kEnetRxBdRxSoftOwner1    = 0x0040U,    /*!< Receive software owner*/
    kEnetRxBdWrap            = 0x0020U,    /*!< Update buffer descriptor*/
    kEnetRxBdRxSoftOwner2    = 0x0010U,    /*!< Receive software owner*/
    kEnetRxBdLast            = 0x0008U,    /*!< Last BD in the frame*/
    kEnetRxBdMiss            = 0x0001U     /*!< Receive for promiscuous mode*/
} enet_rx_bd_control_status_t;

/*! @brief Defines the control extended region1 of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_extend0
{  
    kEnetRxBdIpv4                = 0x0100U,  /*!< IPv4 frame*/
    kEnetRxBdIpv6                = 0x0200U,  /*!< IPv6 frame*/
    kEnetRxBdVlan                = 0x0400U,  /*!< VLAN*/
    kEnetRxBdProtocolChecksumErr = 0x1000U,  /*!< Protocol checksum error*/
    kEnetRxBdIpHeaderChecksumErr = 0x2000U,  /*!< IP header checksum error*/
} enet_rx_bd_control_extend0_t;

/*! @brief Defines the control extended region2 of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_extend1
{  
    kEnetRxBdUnicast   = 0x0001U,              /*!< Unicast frame*/
    kEnetRxBdCollision = 0x0002U,              /*!< BD collision*/
    kEnetRxBdPhyErr    = 0x0004U,              /*!< PHY error*/
    kEnetRxBdMacErr    = 0x0080U,              /*!< Mac error*/
    kEnetRxBdIntrrupt  = 0x8000U               /*!< BD interrupt*/
} enet_rx_bd_control_extend1_t;

/*! @brief Defines the control status region of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_status
{
    kEnetTxBdReady        = 0x0080U,         /*!<  Ready bit*/
    kEnetTxBdTxSoftOwner1 = 0x0040U,         /*!<  Transmit software owner*/
    kEnetTxBdWrap         = 0x0020U,         /*!<  Wrap buffer descriptor*/
    kEnetTxBdTxSoftOwner2 = 0x0010U,         /*!<  Transmit software owner*/
    kEnetTxBdLast         = 0x0008U,         /*!<  Last BD in the frame*/
    kEnetTxBdTransmitCrc  = 0x0004U          /*!<  Receive for transmit CRC*/
} enet_tx_bd_control_status_t;

/*! @brief Defines the control extended region1 of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend0
{
    kEnetTxBdTxErr              = 0x0080U,      /*!<  Transmit error*/
    kEnetTxBdTxUnderFlowErr     = 0x0020U,      /*!<  Underflow error*/
    kEnetTxBdExcessCollisionErr = 0x0010U,      /*!<  Excess collision error*/
    kEnetTxBdTxFrameErr         = 0x0008U,      /*!<  Frame error*/
    kEnetTxBdLatecollisionErr   = 0x0004U,      /*!<  Late collision error*/
    kEnetTxBdOverFlowErr        = 0x0002U,      /*!<  Overflow error*/
    kEnetTxTimestampErr         = 0x0001U       /*!<  Timestamp error*/
} enet_tx_bd_control_extend0_t;

/*! @brief Defines the control extended region2 of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend1
{
    kEnetTxBdTxInterrupt = 0x0040U,   /*!< Transmit interrupt*/
    kEnetTxBdTimeStamp   = 0x0020U    /*!< Transmit timestamp flag */
} enet_tx_bd_control_extend1_t;
#else
/*! @brief Defines the control and status region of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_status
{
    kEnetRxBdEmpty           = 0x8000U,    /*!< Empty bit*/
    kEnetRxBdRxSoftOwner1    = 0x4000U,    /*!< Receive software owner*/
    kEnetRxBdWrap            = 0x2000U,    /*!< Update buffer descriptor*/
    kEnetRxBdRxSoftOwner2    = 0x1000U,    /*!< Receive software owner*/
    kEnetRxBdLast            = 0x0800U,    /*!< Last BD in the frame*/
    kEnetRxBdMiss            = 0x0100U,    /*!< Receive for promiscuous mode*/
    kEnetRxBdBroadCast       = 0x0080U,    /*!< Broadcast */
    kEnetRxBdMultiCast       = 0x0040U,    /*!< Multicast*/
    kEnetRxBdLengthViolation = 0x0020U,    /*!< Receive length violation*/
    kEnetRxBdNoOctet         = 0x0010U,    /*!< Receive non-octet aligned frame*/
    kEnetRxBdCrc             = 0x0004U,    /*!< Receive CRC error*/
    kEnetRxBdOverRun         = 0x0002U,    /*!< Receive FIFO overrun*/
    kEnetRxBdTrunc           = 0x0001U     /*!< Frame is truncated    */
} enet_rx_bd_control_status_t;

/*! @brief Defines the control extended region1 of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_extend0
{  
    kEnetRxBdIpv4                = 0x0001U,  /*!< Ipv4 frame*/
    kEnetRxBdIpv6                = 0x0002U,  /*!< Ipv6 frame*/
    kEnetRxBdVlan                = 0x0004U,  /*!< VLAN*/
    kEnetRxBdProtocolChecksumErr = 0x0010U,  /*!< Protocol checksum error*/
    kEnetRxBdIpHeaderChecksumErr = 0x0020U,  /*!< IP header checksum error*/
} enet_rx_bd_control_extend0_t;

/*! @brief Defines the control extended region2 of the receive buffer descriptor.*/
typedef enum _enet_rx_bd_control_extend1
{  
    kEnetRxBdIntrrupt  = 0x0080U,           /*!< BD interrupt*/
    kEnetRxBdUnicast   = 0x0100U,           /*!< Unicast frame*/
    kEnetRxBdCollision = 0x0200U,           /*!< BD collision*/
    kEnetRxBdPhyErr    = 0x0400U,           /*!< PHY error*/
    kEnetRxBdMacErr    = 0x8000U            /*!< Mac error */
} enet_rx_bd_control_extend1_t;

/*! @brief Defines the control status of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_status
{
    kEnetTxBdReady        = 0x8000U,  /*!<  Ready bit*/
    kEnetTxBdTxSoftOwner1 = 0x4000U,  /*!<  Transmit software owner*/
    kEnetTxBdWrap         = 0x2000U,  /*!<  Wrap buffer descriptor*/
    kEnetTxBdTxSoftOwner2 = 0x1000U,  /*!<  Transmit software owner*/
    kEnetTxBdLast         = 0x0800U,  /*!<  Last BD in the frame*/
    kEnetTxBdTransmitCrc  = 0x0400U   /*!<  Receive for transmit CRC   */
} enet_tx_bd_control_status_t;

/*! @brief Defines the control extended region1 of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend0
{
    kEnetTxBdTxErr              = 0x8000U,      /*!<  Transmit error*/
    kEnetTxBdTxUnderFlowErr     = 0x2000U,      /*!<  Underflow error*/
    kEnetTxBdExcessCollisionErr = 0x1000U,      /*!<  Excess collision error*/
    kEnetTxBdTxFrameErr         = 0x0800U,      /*!<  Frame error*/
    kEnetTxBdLatecollisionErr   = 0x0400U,      /*!<  Late collision error*/
    kEnetTxBdOverFlowErr        = 0x0200U,      /*!<  Overflow error*/
    kEnetTxTimestampErr         = 0x0100U       /*!<  Timestamp error*/
} enet_tx_bd_control_extend0_t;

/*! @brief Defines the control extended region2 of the transmit buffer descriptor.*/
typedef enum _enet_tx_bd_control_extend1
{
    kEnetTxBdTxInterrupt = 0x4000U,   /*!< Transmit interrupt*/
    kEnetTxBdTimeStamp   = 0x2000U    /*!< Transmit timestamp flag */
} enet_tx_bd_control_extend1_t;
#endif

/*! @brief Defines the macro to the different ENET constant value.*/
typedef enum _enet_constant_parameter
{
    kEnetMacAddrLen  = 6U,       /*!< ENET mac address length*/
    kEnetHashValMask = 0x1FU,    /*!< ENET hash value mask*/
    kEnetMinBuffSize = 256U,     /*!< ENET minimum buffer size*/
    kEnetMaxTimeout  = 0xFFFFU,  /*!< ENET timeout*/
    kEnetMdcFreq     = 2500000U  /*!< MDC frequency*/
} enet_constant_parameter_t;

/*! @brief Defines the normal FIFO configuration for ENET MAC.*/
typedef enum _enet_fifo_configure
{
    kEnetMinTxFifoAlmostFull     = 6U,   /*!< ENET minimum transmit FIFO almost full value*/
    kEnetMinFifoAlmostEmpty      = 4U,   /*!<  ENET minimum FIFO almost empty value*/
    kEnetDefaultTxFifoAlmostFull = 8U    /*!< ENET default transmit FIFO almost full value*/
} enet_fifo_configure_t;

/*! @brief Defines the normal operating mode and sleep mode for ENET MAC.*/
typedef enum _enet_mac_operate_mode
{
    kEnetMacNormalMode = 0U,   /*!< Normal operating mode for ENET MAC*/
    kEnetMacSleepMode  = 1U    /*!< Sleep mode for ENET MAC*/
} enet_mac_operate_mode_t;

/*! @brief Defines the RMII or MII mode for data interface between the MAC and the PHY.*/
typedef enum _enet_config_rmii_mode
{
    kEnetCfgMii  = 0U,   /*!< MII mode for data interface*/
    kEnetCfgRmii = 1U    /*!< RMII mode for data interface*/
} enet_config_rmii_mode_t;

/*! @brief Defines the 10 Mbps or 100 Mbps speed mode for the data transfer.*/
typedef enum _enet_config_speed
{
    kEnetCfgSpeed100M = 0U,   /*!< Speed 100 M mode*/
    kEnetCfgSpeed10M  = 1U    /*!< Speed 10 M mode*/
} enet_config_speed_t;

/*! @brief Defines the half or full duplex mode for the data transfer.*/
typedef enum _enet_config_duplex
{
    kEnetCfgHalfDuplex = 0U, /*!< Half duplex mode*/
    kEnetCfgFullDuplex = 1U  /*!< Full duplex mode*/
} enet_config_duplex_t;

/*! @brief Defines the write operation for the MII.*/
typedef enum _enet_mii_write
{
    kEnetWriteNoCompliant = 0U,  /*!< Write frame operation, but not MII compliant.*/
    kEnetWriteValidFrame  = 1U,  /*!< Write frame operation for a valid MII management frame*/
}enet_mii_write_t;

/*! @brief Defines the read operation for the MII.*/
typedef enum _enet_mii_read
{
    kEnetReadValidFrame  = 2U,   /*!< Read frame operation for a valid MII management frame.*/
    kEnetReadNoCompliant = 3U    /*!< Read frame operation, but not MII compliant*/
}enet_mii_read_t;

/*! @brief Defines the initialization, enables or disables the operation for a special address filter */
typedef enum _enet_special_address_filter
{
    kEnetSpecialAddressInit    = 0U,     /*!< Initializes the special address filter.*/
    kEnetSpecialAddressEnable  = 1U,  /*!< Enables the special address filter.*/
    kEnetSpecialAddressDisable = 2U  /*!< Disables the special address filter.*/
} enet_special_address_filter_t;

/*! @brief Defines the IEEE 1588 timer channel numbers.*/
typedef enum _enet_timer_channel
{
    kEnetTimerChannel1 = 0U,  /*!< IEEE 1588 timer Channel 1*/
    kEnetTimerChannel2 = 1U,  /*!< IEEE 1588 timer Channel 2*/
    kEnetTimerChannel3 = 2U,  /*!< IEEE 1588 timer Channel 3*/
    kEnetTimerChannel4 = 3U   /*!< IEEE 1588 timer Channel 4*/
} enet_timer_channel_t;

/*! @brief Defines the capture or compare mode for IEEE 1588 timer channels.*/
typedef enum _enet_timer_channel_mode
{
    kEnetChannelDisable                 = 0U,  /*!< Disable timer channel*/
    kEnetChannelRisingCapture           = 1U,  /*!< Input capture on rising edge*/
    kEnetChannelFallingCapture          = 2U,  /*!< Input capture on falling edge*/
    kEnetChannelBothCapture             = 3U,  /*!< Input capture on both edges*/
    kEnetChannelSoftCompare             = 4U,  /*!< Output compare software only*/
    kEnetChannelToggleCompare           = 5U,  /*!< Toggle output on compare*/
    kEnetChannelClearCompare            = 6U,  /*!< Clear output on compare*/
    kEnetChannelSetCompare              = 7U,  /*!< Set output on compare*/
    kEnetChannelClearCompareSetOverflow = 10U, /*!< Clear output on compare, set output on overflow*/
    kEnetChannelSetCompareClearOverflow = 11U, /*!< Set output on compare, clear output on overflow*/
    kEnetChannelPulseLowonCompare       = 14U, /*!< Pulse output low on compare for one IEEE 1588 clock cycle*/
    kEnetChannelPulseHighonCompare      = 15U  /*!< Pulse output high on compare for one IEEE 1588 clock cycle*/
} enet_timer_channel_mode_t;

/*! @brief Defines the RXFRAME/RXBYTE/TXFRAME/TXBYTE/MII/TSTIMER/TSAVAIL interrupt source for ENET.*/
typedef enum _enet_interrupt_request
{
    kEnetBabrInterrupt          = 0x40000000U,  /*!< Babbling receive error interrupt source*/
    kEnetBabtInterrupt          = 0x20000000U,  /*!< Babbling transmit error interrupt source*/
    kEnetGraceStopInterrupt     = 0x10000000U,  /*!< Graceful stop complete interrupt source*/
    kEnetTxFrameInterrupt       = 0x08000000U,  /*!< TX FRAME interrupt source */
    kEnetTxByteInterrupt        = 0x04000000U,  /*!< TX BYTE interrupt source*/
    kEnetRxFrameInterrupt       = 0x02000000U,  /*!< RX FRAME interrupt source */
    kEnetRxByteInterrupt        = 0x01000000U,  /*!< RX BYTE interrupt source */
    kEnetMiiInterrupt           = 0x00800000U,  /*!< MII interrupt source*/
    kEnetEBusERInterrupt        = 0x00400000U,  /*!< Ethernet bus error interrupt source*/
    kEnetLateCollisionInterrupt = 0x00200000U,  /*!< Late collision interrupt source*/
    kEnetRetryLimitInterrupt    = 0x00100000U,  /*!< Collision Retry Limit interrupt source*/
    kEnetUnderrunInterrupt      = 0x00080000U,  /*!< Transmit FIFO underrun interrupt source*/
    kEnetPayloadRxInterrupt     = 0x00040000U,  /*!< Payload Receive interrupt source*/
    kEnetWakeupInterrupt        = 0x00020000U,  /*!< WAKEUP interrupt source*/
    kEnetTsAvailInterrupt       = 0x00010000U,  /*!< TS AVAIL interrupt source*/
    kEnetTsTimerInterrupt       = 0x00008000U,  /*!< TS WRAP interrupt source*/
    kEnetAllInterrupt           = 0x7FFFFFFFU   /*!< All interrupt*/
} enet_interrupt_request_t;

/* Internal IRQ number*/
typedef enum _enet_irq_number
{
    kEnetTsTimerNumber  = 0,     /*!< ENET ts_timer IRQ number*/
    kEnetReceiveNumber  = 1,     /*!< ENET receive IRQ number*/
    kEnetTransmitNumber = 2,     /*!< ENET transmit IRQ number*/
    kEnetMiiErrorNumber = 3      /*!< ENET MII error IRQ number*/
} enet_irq_number_t;

/*! @brief Defines the ENET main constant.*/
typedef enum _enet_frame_max
{
    kEnetNsecOneSec          = 1000000000, /*!< NanoSecond in one second*/
    kEnetMaxFrameSize        = 1518,  /*!< Maximum frame size*/
    kEnetMaxFrameVlanSize    = 1522,  /*!< Maximum VLAN frame size*/
    kEnetMaxFrameDateSize    = 1500,  /*!< Maximum frame data size*/
    kEnetDefaultTruncLen     = 2047,  /*!< Default Truncate length*/
    kEnetDefaultIpg          = 12,    /*!< ENET default transmit inter packet gap*/
    kEnetMaxValidTxIpg       = 27,    /*!< Maximum valid transmit IPG*/
    kEnetMinValidTxIpg       = 8,     /*!< Minimum valid transmit IPG*/     
    kEnetMaxMdioHoldCycle    = 7,     /*!< Maximum hold time clock cycle on MDIO Output*/
    kEnetMaxFrameBdNumbers   = 6,     /*!< Maximum buffer descriptor numbers of a frame*/
    kEnetFrameFcsLen         = 4,     /*!< FCS length*/
    kEnetEthernetHeadLen     = 14,    /*!< Ethernet Frame header length*/
    kEnetEthernetVlanHeadLen = 18     /*!< Ethernet VLAN frame header length*/
} enet_frame_max_t;

/*! @brief Defines the transmit accelerator configuration*/
typedef enum _enet_txaccelerator_config
{
    kEnetTxAccelisShift16Enabled  = 0x01U,   /*!< Transmit FIFO shift-16*/
    kEnetTxAccelIpCheckEnabled    = 0x08U,   /*!< Insert IP header checksum */
    kEnetTxAccelProtoCheckEnabled = 0x10U    /*!< Insert protocol checksum*/
} enet_txaccelerator_config_t;

/*! @brief Defines the receive accelerator configuration*/
typedef enum _enet_rxaccelerator_config
{
    kEnetRxAccelPadRemoveEnabled  =  0x01U,  /*!< Padding removal for short IP frames*/
    kEnetRxAccelIpCheckEnabled    =  0x02U,  /*!< Discard with wrong IP header checksum */
    kEnetRxAccelProtoCheckEnabled =  0x04U,  /*!< Discard with wrong protocol checksum*/
    kEnetRxAccelMacCheckEnabled   =  0x40U,  /*!< Discard with Mac layer errors*/
    kEnetRxAccelisShift16Enabled  =  0x80U   /*!< Receive FIFO shift-16*/
} enet_rxaccelerator_config_t;


/*! @brief Defines the ENET MAC control Configure*/
typedef enum _enet_mac_control_flag
{
    kEnetStopModeEnable           = 0x1U,  /*!< ENET Stop mode enable*/
    kEnetDebugModeEnable          = 0x2U, /*! Enable MAC to enter hardware freeze when enter debug mode*/
    kEnetPayloadlenCheckEnable    = 0x4U, /*!< ENET receive payload length check enable*/
    kEnetRxFlowControlEnable      = 0x8U, /*!< Enable ENET flow control*/
    kEnetRxCrcFwdEnable           = 0x10U, /*!< Received frame CRC is stripped from the frame*/
    kEnetRxPauseFwdEnable         = 0x20U,/*!< Pause frames are forwarded to the user application*/
    kEnetRxPadRemoveEnable        = 0x40U, /*!< Padding is removed from received frames*/
    kEnetRxBcRejectEnable         = 0x80U, /*!< Broadcast frame reject*/
    kEnetRxPromiscuousEnable      = 0x100U, /*!< Promiscuous mode enabled*/
    kEnetTxCrcFwdEnable           = 0x200U, /*!< Enable transmit frame with the CRC from application*/
    kEnetTxCrcBdEnable            = 0x400U,  /*!< When transmit CRC FWD disable, transmit buffer descriptor enable transmit CRC*/
    kEnetMacAddrInsert            = 0x800U, /*!< Enable MAC address insert*/
    kEnetTxAccelEnable            = 0x1000U, /*!< Transmit accelerator enable*/
    kEnetRxAccelEnable            = 0x2000U, /*!< Transmit accelerator enable*/
    kEnetStoreAndFwdEnable        = 0x4000U, /*!< Switcher to enable store and forward*/
    kEnetMacMibEnable             = 0x8000U,  /*!< Disable MIB module*/
    kEnetSMIPreambleDisable       = 0x10000U, /*!< Enable SMI preamble*/
    kEnetVlanTagEnabled           = 0x20000U,   /*!< Enable VLAN Tag*/
    kEnetMacEnhancedEnable        = 0x40000U /*!< Enable enhanced MAC feature (IEEE 1588 feature/enhanced buff descriptor)*/
} enet_mac_control_flag_t;

#if (!FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY) 
/*! @brief Defines the buffer descriptor structure for the little-endian system and endianness configurable IP.*/
typedef struct ENETBdStruct
{
    uint16_t  length;           /*!< Buffer descriptor data length*/
    uint16_t  control;          /*!< Buffer descriptor control*/
    uint8_t   *buffer;          /*!< Data buffer pointer*/
    uint16_t  controlExtend0;   /*!< Extend buffer descriptor control0*/
    uint16_t  controlExtend1;   /*!< Extend buffer descriptor control1*/
    uint16_t  payloadCheckSum;  /*!< Internal payload checksum*/
    uint8_t   headerLength;     /*!< Header length*/
    uint8_t   protocalTyte;     /*!< Protocol type*/
    uint16_t  reserved0;
    uint16_t  controlExtend2;   /*!< Extend buffer descriptor control2*/
    uint32_t  timestamp;        /*!< Timestamp */
    uint16_t  reserved1;
    uint16_t  reserved2;
    uint16_t  reserved3;
    uint16_t  reserved4;
} enet_bd_struct_t;

#else
/*! @brief Defines the buffer descriptors structure for the Big-endian system.*/
typedef struct ENETBdStruct
{
    uint16_t  control;          /*!< Buffer descriptor control   */
    uint16_t   length;          /*!< Buffer descriptor data length*/
    uint8_t   *buffer;          /*!< Data buffer pointer*/
    uint16_t  controlExtend1;   /*!< Extend buffer descriptor control1*/
    uint16_t  controlExtend0;   /*!< Extend buffer descriptor control0*/
    uint8_t   headerLength;     /*!< Header length*/
    uint8_t   protocalTyte;     /*!< Protocol type*/
    uint16_t  payloadCheckSum;  /*!< Internal payload checksum*/
    uint16_t  controlExtend2;   /*!< Extend buffer descriptor control2*/
    uint16_t  reserved0;  
    uint32_t  timestamp;        /*!< Timestamp pointer*/
    uint16_t  reserved1;
    uint16_t  reserved2;
    uint16_t  reserved3;
    uint16_t  reserved4;
} enet_bd_struct_t;
#endif

/*! @brief Defines the RMII/MII configuration structure*/
typedef struct ENETConfigRMII
{
    enet_config_rmii_mode_t mode;      /*!< RMII/MII mode*/
    enet_config_speed_t speed;    /*!< 100M/10M Speed*/
    enet_config_duplex_t duplex;  /*!< Full/Duplex mode*/
    bool isRxOnTxDisabled;        /*!< Disable receive and transmit*/
    bool isLoopEnabled;           /*!< MII loop mode*/
} enet_config_rmii_t;

/*! @brief Defines the configuration structure for the IEEE 1588 PTP timer.*/
typedef struct ENETConfigPtpTimer
{
    bool isSlaveEnabled;        /*!< Master or slave PTP timer*/
    uint32_t clockIncease;      /*!< Timer increase value each clock period*/
    uint32_t period;            /*!< Timer period for generate interrupt event  */
#if FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT_ERRATA_2579 
    /*!< If support for IEEE 1588 timestamp timer overflow interrupt, \
    set the channel for overflow interrupt */
    enet_timer_channel_t channel; 
#endif
} enet_config_ptp_timer_t;

/*! @brief Defines the transmit FIFO configuration.*/
typedef struct ENETConfigTxFifo
{
    bool isStoreForwardEnabled;   /*!< Transmit FIFO store and forward */
    uint8_t txFifoWrite; /*!< Transmit FIFO write. This should be set when isStoreForwardEnabled
                         is false. this field indicates the number of bytes in step of 64 bytes 
                         written to the transmit FiFO before transmission of a frame begins*/
    uint8_t txEmpty;        /*!< Transmit FIFO section empty threshold, default zero*/
    uint8_t txAlmostEmpty;  /*!< Transmit FIFO section almost empty threshold, The minimum value of 4 should be set*/
    uint8_t txAlmostFull;   /*!< Transmit FIFO section almost full threshold, The minimum value of 6 is required
                              a recommended value of at least 8 should be set*/
} enet_config_tx_fifo_t;

/*! @brief Defines the receive FIFO configuration.*/
typedef struct ENETConfigRxFifo
{
    uint8_t rxFull;           /*!< Receive FIFO section full threshold, default zero*/
    uint8_t rxAlmostFull;     /*!< Receive FIFO section almost full threshold, The minimum value of 4 should be set*/
    uint8_t rxEmpty;          /*!< Receive FIFO section empty threshold, default zero*/
    uint8_t rxAlmostEmpty;    /*!< Receive FIFO section almost empty threshold, The minimum value of 4 should be set*/
} enet_config_rx_fifo_t;

/*!@ brief Defines the receive statistics of MIB*/
typedef struct ENETMibRxStat
{
    uint16_t rxPackets;       /*!< Receive packets*/
    uint16_t rxBroadcastPackets; /*!< Receive broadcast packets*/
    uint16_t rxMulticastPackets;  /*!< Receive multicast packets*/
    uint16_t rxCrcAlignErrorPackets;  /*!< Receive packets with CRC/align error*/
    uint16_t rxUnderSizeGoodPackets;  /*!< Receive packets undersize and good CRC*/
    uint16_t rxUnderSizeBadPackets;  /*!< Receive packets undersize and bad CRC*/
    uint16_t rxOverSizeGoodPackets; /*!< Receive packets oversize and good CRC*/
    uint16_t rxOverSizeBadPackets;  /*!< Receive packets oversize and bad CRC*/
    uint16_t rxByte64Packets;       /*!< Receive packets 64-byte*/
    uint16_t rxByte65to127Packets;  /*!< Receive packets 65-byte to 127-byte*/
    uint16_t rxByte128to255Packets;  /*!< Receive packets 128-byte to 255-byte*/
    uint16_t rxByte256to511Packets;  /*!< Receive packets 256-byte to 511-byte */
    uint16_t rxByte512to1023Packets;  /*!< Receive packets 512-byte to 1023-byte*/
    uint16_t rxByte1024to2047Packets;  /*!< Receive packets 1024-byte to 2047-byte*/
    uint16_t rxByteOver2048Packets;  /*!< Receive packets over 2048-byte*/
    uint32_t rxOctets;              /*!< Receive octets*/
    uint32_t ieeeOctetsrxFrameOk;   /*!< Receive octets of received frames OK*/
    uint16_t ieeerxFrameDrop;     /*!< Receive frames dropped*/
    uint16_t ieeerxFrameOk;      /*!< Receive frames OK*/
    uint16_t ieeerxFrameCrcErr;    /*!< Receive frames with CRC error*/
    uint16_t ieeetxFrameAlignErr;  /*!< Receive frames with align error*/
    uint16_t ieeetxFrameMacErr;  /*!< Receive frames with Mac error*/
    uint16_t ieeetxFramePause;   /*!< Receive flow control pause frames*/
} enet_mib_rx_stat_t;

/*!@ brief Defines the transmit statistics of MIB*/
typedef struct ENETMibTxStat
{
    uint16_t txPackets;      /*!< Transmit packets*/
    uint16_t txBroadcastPackets;  /*!< Transmit broadcast packets*/
    uint16_t txMulticastPackets;  /*!< Transmit multicast packets*/
    uint16_t txCrcAlignErrorPackets;  /*!< Transmit packets with CRC/align error*/
    uint16_t txUnderSizeGoodPackets;  /*!< Transmit packets undersize and good CRC*/
    uint16_t txUnderSizeBadPackets;  /*!< Transmit packets undersize and bad CRC*/
    uint16_t txOverSizeGoodPackets;  /*!< Transmit packets oversize and good CRC*/
    uint16_t txOverSizeBadPackets;  /*!< Transmit packets oversize and bad CRC*/
    uint16_t txCollision;          /*!< Transmit packets with collision*/
    uint16_t txByte64Packets;     /*!< Transmit packets 64-byte*/
    uint16_t txByte65to127Packets;   /*!< Transmit packets 65-byte to 127-byte*/
    uint16_t txByte128to255Packets;   /*!< Transmit packets 128-byte to 255-byte*/
    uint16_t txByte256to511Packets;   /*!< Transmit packets 256-byte to 511-byte*/
    uint16_t txByte512to1023Packets;  /*!< Transmit packets 512-byte to 1023-byte*/
    uint16_t txByte1024to2047Packets;  /*!< Transmit packets 1024-byte to 2047-byte*/
    uint16_t txByteOver2048Packets;   /*!< Transmit packets over 2048-byte*/
    uint32_t txOctets;            /*!< Transmit octets*/
    uint32_t ieeeOctetstxFrameOk;  /*!< Transmit octets of transmitted frames OK*/
    uint16_t ieeetxFrameOk;          /*!< Transmit frames OK*/
    uint16_t ieeetxFrameOneCollision;  /*!< Transmit frames with single collision*/
    uint16_t ieeetxFrameMultiCollison;  /*!< Transmit frames with multicast collision*/
    uint16_t ieeetxFrameLateCollison;  /*!< Transmit frames with late collision*/ 
    uint16_t ieeetxFrmaeExcCollison;   /*!< Transmit frames with excessive collision*/
    uint16_t ieeetxFrameDelay;      /*!< Transmit frames after deferral delay*/
    uint16_t ieeetxFrameMacErr;     /*!< Transmit frames with MAC error*/
    uint16_t ieeetxFrameCarrSenseErr;  /*!< Transmit frames with carrier sense error*/
    uint16_t ieeetxFramePause; /*!< Transmit flow control Pause frame*/
} enet_mib_tx_stat_t;

/*! @brief Define the special configure for receive and transmit controller*/
typedef struct ENETSpecialMacConfig
{
    uint16_t rxMaxFrameLen; /*!< Receive maximum frame length*/
    uint16_t rxTruncLen;    /*!< Receive truncate length, must be greater than or equal to maximum frame length*/
    uint16_t txInterPacketGap; /*!< Transmit inter-packet-gap*/           
} enet_special_maccfg_t;

/*! @brief Defines the basic configuration structure for the ENET device.*/
typedef struct ENETMacConfig
{
    enet_mac_operate_mode_t macMode;  /*!< Mac Normal or sleep mode*/   
    uint8_t *macAddr;    /*!< MAC hardware address*/
    enet_config_rmii_t *rmiiCfgPtr;/*!< RMII configure mode*/    
    uint32_t macCtlConfigure;/*!< Mac control configure, it is recommended to use enet_mac_control_flag_t 
                      it is special control set for loop mode, sleep mode, CRC forward/terminate, and so on*/
    enet_config_rx_fifo_t *rxFifoPtr;    /*!< Receive FIFO configuration, if NULL default values will be used*/
    enet_config_tx_fifo_t *txFifoPtr;    /*!< Transmit FIFO configuration, if NULL default values will be used*/
    uint8_t rxAccelerCfg; /*!< Receive accelerator configure, should be set when kEnetTxAccelEnable is set*/
    uint8_t txAccelerCfg; /*!< Transmit accelerator configure, should be set when kEnetRxAccelEnable is set*/
    uint16_t pauseDuration;          /*!< Pause duration, should be set when kEnetRxFlowControlEnable is set*/
    enet_special_maccfg_t *macSpecialCfg;  /*!< special configure for MAC to instead of default configure*/
#if FSL_FEATURE_ENET_SUPPORT_PTP
    bool isSlaveMode;      /*!< PTP IEEE 1588 timer configuration*/
#endif
} enet_mac_config_t;

/*! @brief The configuration structure of buffer descriptor */
typedef struct ENETBdConfig
{
    volatile enet_bd_struct_t *txBds; /*!< The start address of ENET transmit buffer descriptors.    
                                   This address must always be evenly divisible by 16. */      
    uint8_t *txBuffer;/*!< The transmit data buffer start address. This address must 
                         always be evenly divisible by 16. */
    uint32_t txBdNumber;       /*!< The transmit buffer descriptor numbers. */
    uint32_t txBuffSizeAlign;  /*!< The aligned transmit buffer size. */    
    volatile enet_bd_struct_t *rxBds; /*!< The start address of ENET receive buffer descriptors.   
                                  This address must always be evenly divisible by 16. */
    uint8_t *rxBuffer;       /*!< The receive data buffer start address. This address must 
                             always be evenly divisible by 16. */  
    uint32_t rxBdNumber;       /*!<  The receive buffer descriptor numbers. */
    uint32_t rxBuffSizeAlign;  /*!< The aligned receive transmit buffer size. */
} enet_bd_config;

/* The mask to get MIB receive static event counter */
#define ENET_GET_MIB_RX_STATIC_MASK           (1 << 0)
/* The mask to get MIB transmit static event counter */
#define ENET_GET_MIB_TX_STATIC_MASK           (1 << 1)
/* The mask to get transmit pause frame status */
#define ENET_GET_TX_PAUSE_MASK                (1 << 2)
/* The mask to get receive pause frame status */
#define ENET_GET_RX_PAUSE_MASK                (1 << 3)
/* The mask to get the SMI interface configuration status */
#define ENET_GET_SMI_CONFIG_MASK              (1 << 4)
/* The mask to get MIB updating status */
#define ENET_GET_MIB_UPDATE_MASK              (1 << 5)
/* The mask to get maximum frame length */
#define ENET_GET_MAX_FRAME_LEN_MASK           (1 << 6)

/* The status of the transmitted flow control frames
      - 1 if the MAC is transmitting a MAC control PAUSE frame.
      - 0 if No PAUSE frame transmit. */     
#define ENET_TX_PUASE_FLAG                 (1 << 0)   
/* The status of the received flow control frames
     - 1 if the flow control pause frame is received and the transmitter pauses
         for the duration defined in this pause frame.
     - 0 if there is no flow control frame received or the pause duration is complete.*/
#define ENET_RX_PAUSE_FLAG                 (1 << 1)
/* The MII configuration status.
     - 1 if the MII has been configured. 
     - 0 if the MII has not been configured. */ 
#define ENET_SMI_CONFIG_FLAG               (1 << 2)
/* The MIB updating status
     - 1 if MIB is idle and MIB is not updating. 
     - 0 if MIB is updating */
#define ENET_MIB_UPDATE_FLAG               (1 << 3)

/*! @brief The structure to save current status */
typedef struct ENETCurStatus
{
    enet_mib_rx_stat_t rxStatic; /*!< The receive static event counter */
    enet_mib_tx_stat_t txStatic; /*!< The transmit static event counter */
    uint16_t maxFrameLen;        /*!< The maximum frame length */
    uint32_t statusFlags;        /*!< The status flag */
}enet_cur_status_t;

/* Gets the control and the status region of the receive/transmit buffer descriptors. */   
#define ENET_BD_CTL_MASK                     (1 << 0)
/* Gets the extended control region of the transmit buffer descriptors. */
#define ENET_RX_BD_EXT_CTL_MASK              (1 << 1)
/* Gets the extended control region one of the receive buffer descriptor. */ 
#define ENET_RX_BD_EXT_CTL1_MASK             (1 << 2)
/* Gets the extended control region two of the receive buffer descriptor. */  
#define ENET_RX_BD_EXT_CTL2_MASK             (1 << 3)
/* Gets the data length of the buffer descriptors. */ 
#define ENET_BD_LEN_MASK                     (1 << 5)
/* Gets  the timestamp of the buffer descriptors. */  
#define ENET_BD_TIMESTAMP_MASK               (1 << 6)
/* Check if input buffer descriptor is the last one in the ring buffer */
#define ENET_RX_BD_WRAP_FLAG_MASK            (1 << 7)
/* Check if buffer descriptor empty flag is set. */  
#define ENET_RX_BD_EMPTY_FLAG_MASK           (1 << 8)
/* Check if buffer descriptor truncate flag is set. */    
#define ENET_RX_BD_TRUNC_FLAG_MASK           (1 << 9)
/* Check if buffer descriptor last flag is set. */  
#define ENET_RX_BD_LAST_FLAG_MASK            (1 << 10)   
/* Check if buffer descriptor ready flag is set. */ 
#define ENET_TX_BD_READY_FLAG_MASK           (1 << 11)
/* Check if buffer descriptor last flag is set. */  
#define ENET_TX_BD_LAST_FLAG_MASK            (1 << 12)
/* Check if buffer descriptor wrap flag is set. */ 
#define ENET_TX_BD_WRAP_FLAG_MASK            (1 << 13)
/* Check if buffer descriptor Receive over run flag is set. */  
#define ENET_RX_BD_OVERRUN_FLAG_MASK         (1 << 14)
/* Check if buffer descriptor Receive length violation flag is set. */ 
#define ENET_RX_BD_LEN_VIOLAT_FLAG_MASK      (1 << 15)
/* Check if buffer descriptor Receive non-octet aligned frame flag is set. */
#define ENET_RX_BD_NO_OCTET_FLAG_MASK        (1 << 16)
/* Check if buffer descriptor Receive CRC error flag is set. */
#define ENET_RX_BD_CRC_ERR_FLAG_MASK         (1 << 17)
/* Check if buffer descriptor late collision frame discard flag is set. */ 
#define ENET_RX_BD_COLLISION_FLAG_MASK       (1 << 18)
/* Check if buffer descriptor TxErr flag is set. */ 
#define ENET_TX_BD_TX_ERR_FLAG_MASK          (1 << 19)
/* Check if buffer descriptor Transmit excess collision flag is set. */ 
#define ENET_TX_BD_EXC_COL_FLAG_MASK         (1 << 20)
/* Check if buffer descriptor Transmit late collision flag is set. */ 
#define ENET_TX_BD_LATE_COL_FLAG_MASK        (1 << 21)
/* Check if buffer descriptor Transmit underflow flag is set. */ 
#define ENET_TX_BD_UNDERFLOW_FLAG_MASK       (1 << 22)
/* Check if buffer descriptor Transmit overflow flag is set. */ 
#define ENET_TX_BD_OVERFLOW_FLAG_MASK        (1 << 23)
/* Check if buffer descriptor Transmit timestamp flag is set. */
#define ENET_TX_BD_TIMESTAMP_FLAG_MASK       (1 << 24)

/* If input buffer descriptor is the last one, equals 1 */
#define ENET_RX_BD_WRAP_FLAG                   (1 << 0)
/* If buffer descriptor empty flag is set, equals 1 */
#define ENET_RX_BD_EMPTY_FLAG                  (1 << 1)
/* If buffer descriptor truncate flag is set, equals 1 */
#define ENET_RX_BD_TRUNC_FLAG                  (1 << 2)
/* If buffer descriptor last flag is set, equals 1 */
#define ENET_RX_BD_LAST_FLAG                   (1 << 3)
/* If buffer descriptor ready flag is set, equals 1 */
#define ENET_TX_BD_READY_FLAG                  (1 << 4)
/* If buffer descriptor last flag is set, equals 1 */
#define ENET_TX_BD_LAST_FLAG                   (1 << 5)
/* If buffer descriptor last flag is set, equals 1 */
#define ENET_TX_BD_WRAP_FLAG                   (1 << 6)
/* If buffer descriptor Receive over run flag is set, equals 1 */
#define ENET_RX_BD_OVERRUN_FLAG                (1 << 7)
/* If buffer descriptor Receive length violation flag is set, equals 1 */
#define ENET_RX_BD_LEN_VIOLAT_FLAG             (1 << 8)
/* If buffer descriptor Receive non-octet aligned frame flag is set, equals 1 */
#define ENET_RX_BD_NO_OCTET_FLAG               (1 << 9)
/* If buffer descriptor Receive crc error flag is set, equals 1 */
#define ENET_RX_BD_CRC_ERR_FLAG                (1 << 10)
/* If buffer descriptor late collision frame discard flag is set, equals 1 */
#define ENET_RX_BD_COLLISION_FLAG              (1 << 11)
/* If buffer descriptor TxRrr flag is set, equals 1 */
#define ENET_TX_BD_TX_ERR_FLAG                 (1 << 12)
/* If buffer descriptor Transmit excess collision flag is set, equals 1 */
#define ENET_TX_BD_EXC_COL_ERR_FLAG            (1 << 13)
/* If buffer descriptor Transmit late collision flag is set, equals 1 */
#define ENET_TX_BD_LATE_COL_ERR_FLAG           (1 << 14)
/* If buffer descriptor Transmit underflow flag is set, equals 1 */
#define ENET_TX_BD_UNDERFLOW_ERR_FLAG          (1 << 15)
/* If buffer descriptor Transmit overflow flag is set, equals 1 */
#define ENET_TX_BD_OVERFLOW_FLAG               (1 << 16)
/* If buffer descriptor Transmit timestamp flag is set, equals 1 */
#define ENET_TX_BD_TIMESTAMP_FLAG              (1 << 17)

/*! @brief The buffer descriptor attribute */
typedef struct EnetBdAttr
{
    uint16_t bdCtl;           /*!< Buffer descriptor control field */
    uint16_t rxBdExtCtl;      /*!< Buffer descriptor extend control field  */
    uint16_t rxBdExtCtl1;     /*!< Buffer descriptor extend control field 1 */
    uint16_t rxBdExtCtl2;     /*!< Buffer descriptor extend control field 2 */
    uint16_t bdLen;           /*!< Buffer descriptor data length field */
    uint32_t bdTimestamp;     /*!< Buffer descriptor time stamp field */
    uint64_t flags;           /*!< The status flag in the buffer descriptor */
}enet_bd_attr_t;

/*! @brief The action of mac which should be enabled dynamically */
typedef enum EnetEnableDynamicalAct
{
    kEnGraceSendStop,     /*!< Enable/disable mac to stop the sending process gracefully */ 
    kEnSendPauseFrame,    /*!< Enable/disable mac to send the pause frame after current data frame is sent */ 
    kEnClearMibCounter,     /*!< Enable/disable mac to clear the MIB counter */
}enet_en_dynamical_act_t;
  
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API                              
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the ENET module to reset status.
 *
 * @param base The ENET peripheral base address.
 * @return The status of the initialize operation.
 *          - false initialize failure.
 *          - true initialize success.
 */
enet_status_t ENET_HAL_Init(ENET_Type * base);

/*!
 * @brief Configures the ENET.
 *
 * @param base The ENET peripheral base address.
 * @param macCfgPtr MAC controller related configuration.
 * @param sysClk The system clock
 * @param bdConfig buffer descriptor related configuration
 */
void ENET_HAL_Config(ENET_Type * base, const enet_mac_config_t *macCfgPtr, \
  const uint32_t sysClk, const enet_bd_config* bdConfig); 

/*!
 * @brief Gets the ENET status.
 *
 * @param base The ENET peripheral base address.
 * @param mask The mask represent which status user want to get.
 * @param curStatus The structure to save the status result
 */
void ENET_HAL_GetStatus(ENET_Type * base, const uint32_t mask, enet_cur_status_t* curStatus);

/*!
 * @brief Sets the hardware addressing filtering to a multicast group address.
 *
 * This interface is used to add the ENET device to a multicast group address.
 * After joining the group,  Mac  receives all frames with the group Mac address.
 *
 * @param base The ENET peripheral base address.
 * @param crcValue The CRC value of the multicast group address.
 * @param mode The operation for initialize/enable/disable the specified hardware address.
 */
void ENET_HAL_SetMulticastAddrHash(ENET_Type * base, uint32_t crcValue, enet_special_address_filter_t mode);

/*!
 * @brief Gets the attribute field value of buffer descriptor structure and flag
 * status in the control field.
 * 
 * @param curBd The ENET buffer descriptor address.
 * @param mask The attribute mask represent which field user want to get.
 * @param resultAttr the attribute value which is updated according to the mask value.
 */
void ENET_HAL_GetBufDescripAttr(volatile enet_bd_struct_t *curBd, const uint64_t mask, enet_bd_attr_t* resultAttr);
 
 /*!
 * @brief Gets the buffer address of the buffer descriptors.
 *
 * @param curBd The current buffer descriptor.
 * @return The buffer address of the buffer descriptor.
 */ 
uint8_t* ENET_HAL_GetBuffDescripData(volatile enet_bd_struct_t *curBd);

/*!
 * @brief Clears the receive buffer descriptor flag after it has been received or 
 * encountered some error in the receiving process.
 *
 * This interface mainly clears the status region and update the buffer pointer of 
 * the receive descriptor to a null buffer to ensure that the BD is  correctly available 
 * to receive data.
 *
 * @param rxBds The current receive buffer descriptor.
 * @param data The data buffer address. This address must be divided by 16
 *              if the isbufferUpdate is set.
 * @param isbufferUpdate The data buffer update flag. When you want to update 
 *        the data buffer of the buffer descriptor ensure that this flag
 *        is set.
 */
void ENET_HAL_ClrRxBdAfterHandled(volatile enet_bd_struct_t *rxBds, uint8_t *data, bool isbufferUpdate);

/*!
 * @brief Sets the transmit buffer descriptor flag before sending a frame.
 *
 * This interface mainly clears the status region of the transmit buffer descriptor to 
 * ensure tat the BD is correctly available to send.
 * Set the isTxtsCfged when the transmit timestamp feature is required. 
 *
 * @param txBds The current transmit buffer descriptor.
 * @param length The data length on buffer descriptor.
 * @param isTxtsCfged The timestamp configure flag. The timestamp is 
 *        added to the transmit buffer descriptor when this flag is set.
 * @param isTxCrcEnable The flag to transmit CRC sequence after the data byte.
 *        - True the transmit controller transmits the CRC sequence after the data byte.
 *        If the transmit CRC forward from application is disabled this flag should be set
 *        to add the CRC sequence.
 *        - False the transmit buffer descriptor does not transmit the CRC sequence after the data byte.
 * @param isLastOne The last BD flag in a frame.
 *        - True the last BD in a frame.
 *        - False not the last BD in a frame.
 */
void ENET_HAL_SetTxBdBeforeSend(volatile enet_bd_struct_t *txBds, uint16_t length, \
  bool isTxtsCfged, bool isTxCrcEnable, bool isLastOne);

/*!
 * @brief Clears the context in the transmit buffer descriptors.
 *
 * Clears the data, length, control, and status region of the transmit buffer descriptor.
 *
 * @param curBd The current buffer descriptor.
 */
static inline void ENET_HAL_ClrTxBdAfterSend(volatile enet_bd_struct_t *curBd)
{
    assert(curBd);

    curBd->length = 0;                /* Set data length*/
    curBd->control &= (kEnetTxBdWrap);/* Set control */
    curBd->controlExtend1 = 0;
}

/*!
 * @brief Activates the receive buffer descriptor.
 *
 * The buffer descriptor activation
 * should be done after the ENET module is enabled. Otherwise, the activation  fails.
 *
 * @param base The ENET peripheral base address.
 */
 static inline void ENET_HAL_SetRxBdActive(ENET_Type * base)
{
    ENET_SET_RDAR(base, ENET_RDAR_RDAR_MASK);
}

/*!
 * @brief Activates the transmit buffer descriptor.
 *
 * The  buffer descriptor activation should be done after the ENET module is
 * enabled. Otherwise, the activation  fails.
 * 
 * @param base The ENET peripheral base address.
 */
static inline void ENET_HAL_SetTxBdActive(ENET_Type * base)
{
    ENET_SET_TDAR(base, ENET_TDAR_TDAR_MASK);
}

/*!
 * @brief Configures the (R)MII data interface of ENET.
 *
 * @param base The ENET peripheral base address.
 * @param rmiiCfgPtr The RMII/MII configuration structure pointer.
 */
void ENET_HAL_SetRMIIMode(ENET_Type * base, enet_config_rmii_t *rmiiCfgPtr);

/*!
 * @brief Reads data from PHY. 
 *
 * @param base The ENET peripheral base address.
 * @return The data read from PHY
 */
static inline uint32_t ENET_HAL_GetSMIData(ENET_Type * base)
{
    return (uint32_t)ENET_BRD_MMFR_DATA(base);
}

/*!
 * @brief Sets the Serial Management interface (SMI) read command.
 *
 * @param base The ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param operation The read operation.
 */
void ENET_HAL_SetSMIRead(ENET_Type * base, uint32_t phyAddr, uint32_t phyReg, enet_mii_read_t operation);

/*!
 * @brief Sets the SMI write command.
 *
 * @param base The ENET peripheral base address.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param operation The write operation.
 * @param data The data written to PHY.
 */
void ENET_HAL_SetSMIWrite(ENET_Type * base, uint32_t phyAddr, uint32_t phyReg, enet_mii_write_t operation, uint32_t data);

/*!
 * @brief Enables/disables the Mac dynamical action.
 *
 * @param base The ENET peripheral base address.
 * @param action The action which will be enabled/disabled.
 * @param enable The switch to enable/disable the action of the Mac.
 */
void ENET_HAL_EnDynamicalAct(ENET_Type * base, enet_en_dynamical_act_t action, bool enable);

/*!
 * @brief Enables the ENET module.
 *
 * @param base The ENET peripheral base address.
 */
static inline void ENET_HAL_Enable(ENET_Type * base)
{    
    ENET_SET_ECR(base, ENET_ECR_ETHEREN_MASK); /* Enable Ethernet module*/

#if (!FSL_FEATURE_ENET_DMA_BIG_ENDIAN_ONLY)
    ENET_BWR_ECR_DBSWP(base,1);    /* buffer descriptor byte swapping for little-endian system and endianness configurable IP*/
#endif
}

/*!
 * @brief Disables the ENET module.
 *
 * @param base The ENET peripheral base address.
 */
static inline void ENET_HAL_Disable(ENET_Type * base)
{    
    ENET_CLR_ECR(base, ENET_ECR_ETHEREN_MASK); /* Disable Ethernet module*/
}

/*!
 * @brief Enables/disables the ENET interrupt.
 *
 * @param base The ENET peripheral base address.
 * @param source The interrupt sources.
 * @param enable The interrupt enable switch.
 */
void ENET_HAL_SetIntMode(ENET_Type * base, enet_interrupt_request_t source, bool enable);

/*!
 * @brief Clears ENET interrupt events. 
 *
 * @param base The ENET peripheral base address.
 * @param source The interrupt source to be cleared. enet_interrupt_request_t 
 *        enum types is recommended as the interrupt source.
 */
static inline void ENET_HAL_ClearIntStatusFlag(ENET_Type * base, enet_interrupt_request_t source)
{ 
    ENET_WR_EIR(base,source);    
}

/*!
 * @brief Gets the ENET interrupt status.
 *
 * @param base The ENET peripheral base address.
 * @param source The interrupt sources. enet_interrupt_request_t 
 *        enum types is recommended as the interrupt source.
 * @return The event status of the interrupt source
 *         - true if the interrupt event happened. 
 *         - false if the interrupt event has not happened.
 */
static inline bool ENET_HAL_GetIntStatusFlag(ENET_Type * base, enet_interrupt_request_t source)
{
    return ((ENET_RD_EIR(base) & (uint32_t)source) != 0);  
}

/*!
 * @brief Configures the IEEE 1588 timer and runs the IEEE 1588 timer.
 *
 * This interface configures the IEEE 1588 timer and starts the IEEE 1588 timer.
 * After the timer starts, the IEEE 1588 timer starts incrementing.
 *
 * @param base The ENET peripheral base address.
 * @param ptpCfgPtr The IEEE 1588 timer configuration structure pointer.
 */
void ENET_HAL_Start1588Timer(ENET_Type * base, enet_config_ptp_timer_t * ptpCfgPtr);

/*!
 * @brief Stops the IEEE 1588 timer.
 *
 * This interface stops the IEEE 1588 timer and clears its count value.
 *
 * @param base The ENET peripheral base address.
 */
void ENET_HAL_Stop1588Timer(ENET_Type * base);

/*!
 * @brief Adjusts the IEEE 1588 timer.
 *
 * Adjusts the IEEE 1588 timer according to the increase and correction period
 * of the configured correction.
 *
 * @param base The ENET peripheral base address.
 * @param increaseCorrection The increase correction for IEEE 1588 timer.
 * @param periodCorrection The period correction for IEEE 1588 timer.
 */
static inline void ENET_HAL_Adjust1588Timer(ENET_Type * base, uint32_t increaseCorrection, uint32_t periodCorrection)
{
    assert(increaseCorrection <= ENET_ATINC_INC_MASK);
    assert(periodCorrection <= ENET_ATCOR_COR_MASK);
    /* Set correction for PTP timer increment*/     
    ENET_BWR_ATINC_INC_CORR(base, increaseCorrection);
    /* Set correction for PTP timer period*/
    ENET_BWR_ATCOR_COR(base, periodCorrection);
}

/*!
 * @brief Sets the IEEE 1588 timer.
 *
 * @param base The ENET peripheral base address.
 * @param nanSecond The nanosecond set to IEEE 1588 timer.
 */
static inline void ENET_HAL_Set1588TimerNewTime(ENET_Type * base, uint32_t nanSecond)
{
    ENET_WR_ATVR(base,nanSecond);
}

/*!
 * @brief Gets the time from the IEEE 1588 timer.
 *
 * Sets the capture command to the IEEE 1588 timer before reading the current
 * time register. After set timer capture, wait for about 1 µs before reading
 * the captured timer.
 * @param base The ENET peripheral base address.
 * @return the current time from IEEE 1588 timer.
 */
static inline uint32_t ENET_HAL_Get1588TimerCurrentTime(ENET_Type * base)
{
    ENET_SET_ATCR(base, ENET_ATCR_CAPTURE_MASK);
    /*Bug of IC need repeat*/
    ENET_SET_ATCR(base, ENET_ATCR_CAPTURE_MASK);
    return ENET_RD_ATVR(base);   
}

/*!
 * @brief Gets the IEEE 1588 timer channel status.
 *
 * @param base The ENET peripheral base address.
 * @param channel The IEEE 1588 timer channel number.
 * @return Compare or capture operation status
 *         - True if the compare or capture has occurred.
 *         - False if the compare or capture has not occurred. 
 */
static inline bool ENET_HAL_Get1588TimerChnStatus(ENET_Type * base, enet_timer_channel_t channel)
{
    return ENET_BRD_TCSR_TF(base,channel);  
}

/*!
 * @brief Resets the IEEE 1588 timer compare value and clears the IEEE 1588 timer channel interrupt flag.
 *
 * @param base The ENET peripheral base address.
 * @param channel The IEEE 1588 timer channel number.
 * @param compareValue Compare value for IEEE 1588 timer channel.
 */
static inline void ENET_HAL_Rst1588TimerCmpValAndClrFlag(ENET_Type * base, enet_timer_channel_t channel, uint32_t compareValue)
{           
    ENET_WR_TCCR(base, channel, compareValue);   
    ENET_SET_TCSR(base, channel, ENET_TCSR_TF_MASK);/* clears interrupt flag*/
    ENET_WR_TGSR(base,(1U << channel));            /* clears channel flag*/
}

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/
#endif
#endif /*!< __FSL_ENET_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

