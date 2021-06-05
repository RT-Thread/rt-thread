/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps_hw.h
* @addtogroup emacps_v3_11
* @{
*
* This header file contains identifiers and low-level driver functions (or
* macros) that can be used to access the PS Ethernet MAC (XEmacPs) device.
* High-level driver functions are defined in xemacps.h.
*
* @note
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a wsy  01/10/10 First release.
* 1.02a asa  11/05/12 Added hash defines for DMACR burst length configuration.
* 1.05a kpc  28/06/13 Added XEmacPs_ResetHw function prototype
* 1.06a asa  11/02/13 Changed the value for XEMACPS_RXBUF_LEN_MASK from 0x3fff
*                      to 0x1fff. This fixes the CR#744902.
* 2.1   srt  07/15/14 Add support for Zynq Ultrascale Mp GEM specification.
* 3.0   kvn  12/16/14 Changed name of XEMACPS_NWCFG_LENGTHERRDSCRD_MASK to
*                      XEMACPS_NWCFG_LENERRDSCRD_MASK as it exceeds 31 characters.
* 3.0  kpc   1/23/15  Corrected the extended descriptor macro values.
* 3.0  kvn   02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.0  hk   03/18/15 Added support for jumbo frames.
*                    Remove "used bit set" from TX error interrupt masks.
* 3.1  hk   08/10/15 Update upper 32 bit tx and rx queue ptr register offsets.
* 3.2   hk   02/22/16 Added SGMII support for Zynq Ultrascale+ MPSoC.
* 3.8  hk   09/17/18 Fix PTP interrupt masks.
* 3.9  hk   01/23/19 Add RX watermark support
* 3.10 hk   05/16/19 Clear status registers properly in reset
* </pre>
*
******************************************************************************/

#ifndef XEMACPS_HW_H        /* prevent circular inclusions */
#define XEMACPS_HW_H        /* by using protection macros */

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xil_assert.h"
#include "xil_io.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/

#define XEMACPS_MAX_MAC_ADDR     4U   /**< Maxmum number of mac address
                                           supported */
#define XEMACPS_MAX_TYPE_ID      4U   /**< Maxmum number of type id supported */

#ifdef __aarch64__
#define XEMACPS_BD_ALIGNMENT     64U   /**< Minimum buffer descriptor alignment
                                           on the local bus */
#else

#define XEMACPS_BD_ALIGNMENT     4U   /**< Minimum buffer descriptor alignment
                                           on the local bus */
#endif
#define XEMACPS_RX_BUF_ALIGNMENT 4U   /**< Minimum buffer alignment when using
                                           options that impose alignment
                                           restrictions on the buffer data on
                                           the local bus */

/** @name Direction identifiers
 *
 *  These are used by several functions and callbacks that need
 *  to specify whether an operation specifies a send or receive channel.
 * @{
 */
#define XEMACPS_SEND        1U          /**< send direction */
#define XEMACPS_RECV        2U          /**< receive direction */
/*@}*/

/**  @name MDC clock division
 *  currently supporting 8, 16, 32, 48, 64, 96, 128, 224.
 * @{
 */
typedef enum { MDC_DIV_8 = 0U, MDC_DIV_16, MDC_DIV_32, MDC_DIV_48,
    MDC_DIV_64, MDC_DIV_96, MDC_DIV_128, MDC_DIV_224
} XEmacPs_MdcDiv;

/*@}*/

#define XEMACPS_RX_BUF_SIZE 1536U /**< Specify the receive buffer size in
                                       bytes, 64, 128, ... 10240 */
#define XEMACPS_RX_BUF_SIZE_JUMBO 10240U

#define XEMACPS_RX_BUF_UNIT   64U /**< Number of receive buffer bytes as a
                                       unit, this is HW setup */

#define XEMACPS_MAX_RXBD     128U /**< Size of RX buffer descriptor queues */
#define XEMACPS_MAX_TXBD     128U /**< Size of TX buffer descriptor queues */

#define XEMACPS_MAX_HASH_BITS 64U /**< Maximum value for hash bits. 2**6 */

/* Register offset definitions. Unless otherwise noted, register access is
 * 32 bit. Names are self explained here.
 */

#define XEMACPS_NWCTRL_OFFSET        0x00000000U /**< Network Control reg */
#define XEMACPS_NWCFG_OFFSET         0x00000004U /**< Network Config reg */
#define XEMACPS_NWSR_OFFSET          0x00000008U /**< Network Status reg */

#define XEMACPS_DMACR_OFFSET         0x00000010U /**< DMA Control reg */
#define XEMACPS_TXSR_OFFSET          0x00000014U /**< TX Status reg */
#define XEMACPS_RXQBASE_OFFSET       0x00000018U /**< RX Q Base address reg */
#define XEMACPS_TXQBASE_OFFSET       0x0000001CU /**< TX Q Base address reg */
#define XEMACPS_RXSR_OFFSET          0x00000020U /**< RX Status reg */

#define XEMACPS_ISR_OFFSET           0x00000024U /**< Interrupt Status reg */
#define XEMACPS_IER_OFFSET           0x00000028U /**< Interrupt Enable reg */
#define XEMACPS_IDR_OFFSET           0x0000002CU /**< Interrupt Disable reg */
#define XEMACPS_IMR_OFFSET           0x00000030U /**< Interrupt Mask reg */

#define XEMACPS_PHYMNTNC_OFFSET      0x00000034U /**< Phy Maintaince reg */
#define XEMACPS_RXPAUSE_OFFSET       0x00000038U /**< RX Pause Time reg */
#define XEMACPS_TXPAUSE_OFFSET       0x0000003CU /**< TX Pause Time reg */

#define XEMACPS_JUMBOMAXLEN_OFFSET   0x00000048U /**< Jumbo max length reg */

#define XEMACPS_RXWATERMARK_OFFSET   0x0000007CU /**< RX watermark reg */

#define XEMACPS_HASHL_OFFSET         0x00000080U /**< Hash Low address reg */
#define XEMACPS_HASHH_OFFSET         0x00000084U /**< Hash High address reg */

#define XEMACPS_LADDR1L_OFFSET       0x00000088U /**< Specific1 addr low reg */
#define XEMACPS_LADDR1H_OFFSET       0x0000008CU /**< Specific1 addr high reg */
#define XEMACPS_LADDR2L_OFFSET       0x00000090U /**< Specific2 addr low reg */
#define XEMACPS_LADDR2H_OFFSET       0x00000094U /**< Specific2 addr high reg */
#define XEMACPS_LADDR3L_OFFSET       0x00000098U /**< Specific3 addr low reg */
#define XEMACPS_LADDR3H_OFFSET       0x0000009CU /**< Specific3 addr high reg */
#define XEMACPS_LADDR4L_OFFSET       0x000000A0U /**< Specific4 addr low reg */
#define XEMACPS_LADDR4H_OFFSET       0x000000A4U /**< Specific4 addr high reg */

#define XEMACPS_MATCH1_OFFSET        0x000000A8U /**< Type ID1 Match reg */
#define XEMACPS_MATCH2_OFFSET        0x000000ACU /**< Type ID2 Match reg */
#define XEMACPS_MATCH3_OFFSET        0x000000B0U /**< Type ID3 Match reg */
#define XEMACPS_MATCH4_OFFSET        0x000000B4U /**< Type ID4 Match reg */

#define XEMACPS_STRETCH_OFFSET       0x000000BCU /**< IPG Stretch reg */

#define XEMACPS_OCTTXL_OFFSET        0x00000100U /**< Octects transmitted Low
                                                      reg */
#define XEMACPS_OCTTXH_OFFSET        0x00000104U /**< Octects transmitted High
                                                      reg */

#define XEMACPS_TXCNT_OFFSET         0x00000108U /**< Error-free Frmaes
                                                      transmitted counter */
#define XEMACPS_TXBCCNT_OFFSET       0x0000010CU /**< Error-free Broadcast
                                                      Frames counter*/
#define XEMACPS_TXMCCNT_OFFSET       0x00000110U /**< Error-free Multicast
                                                      Frame counter */
#define XEMACPS_TXPAUSECNT_OFFSET    0x00000114U /**< Pause Frames Transmitted
                                                      Counter */
#define XEMACPS_TX64CNT_OFFSET       0x00000118U /**< Error-free 64 byte Frames
                                                      Transmitted counter */
#define XEMACPS_TX65CNT_OFFSET       0x0000011CU /**< Error-free 65-127 byte
                                                      Frames Transmitted
                                                      counter */
#define XEMACPS_TX128CNT_OFFSET      0x00000120U /**< Error-free 128-255 byte
                                                      Frames Transmitted
                                                      counter*/
#define XEMACPS_TX256CNT_OFFSET      0x00000124U /**< Error-free 256-511 byte
                                                      Frames transmitted
                                                      counter */
#define XEMACPS_TX512CNT_OFFSET      0x00000128U /**< Error-free 512-1023 byte
                                                      Frames transmitted
                                                      counter */
#define XEMACPS_TX1024CNT_OFFSET     0x0000012CU /**< Error-free 1024-1518 byte
                                                      Frames transmitted
                                                      counter */
#define XEMACPS_TX1519CNT_OFFSET     0x00000130U /**< Error-free larger than
                                                      1519 byte Frames
                                                      transmitted counter */
#define XEMACPS_TXURUNCNT_OFFSET     0x00000134U /**< TX under run error
                                                      counter */

#define XEMACPS_SNGLCOLLCNT_OFFSET   0x00000138U /**< Single Collision Frame
                                                      Counter */
#define XEMACPS_MULTICOLLCNT_OFFSET  0x0000013CU /**< Multiple Collision Frame
                                                      Counter */
#define XEMACPS_EXCESSCOLLCNT_OFFSET 0x00000140U /**< Excessive Collision Frame
                                                      Counter */
#define XEMACPS_LATECOLLCNT_OFFSET   0x00000144U /**< Late Collision Frame
                                                      Counter */
#define XEMACPS_TXDEFERCNT_OFFSET    0x00000148U /**< Deferred Transmission
                                                      Frame Counter */
#define XEMACPS_TXCSENSECNT_OFFSET   0x0000014CU /**< Transmit Carrier Sense
                                                      Error Counter */

#define XEMACPS_OCTRXL_OFFSET        0x00000150U /**< Octects Received register
                                                      Low */
#define XEMACPS_OCTRXH_OFFSET        0x00000154U /**< Octects Received register
                                                      High */

#define XEMACPS_RXCNT_OFFSET         0x00000158U /**< Error-free Frames
                                                      Received Counter */
#define XEMACPS_RXBROADCNT_OFFSET    0x0000015CU /**< Error-free Broadcast
                                                      Frames Received Counter */
#define XEMACPS_RXMULTICNT_OFFSET    0x00000160U /**< Error-free Multicast
                                                      Frames Received Counter */
#define XEMACPS_RXPAUSECNT_OFFSET    0x00000164U /**< Pause Frames
                                                      Received Counter */
#define XEMACPS_RX64CNT_OFFSET       0x00000168U /**< Error-free 64 byte Frames
                                                      Received Counter */
#define XEMACPS_RX65CNT_OFFSET       0x0000016CU /**< Error-free 65-127 byte
                                                      Frames Received Counter */
#define XEMACPS_RX128CNT_OFFSET      0x00000170U /**< Error-free 128-255 byte
                                                      Frames Received Counter */
#define XEMACPS_RX256CNT_OFFSET      0x00000174U /**< Error-free 256-512 byte
                                                      Frames Received Counter */
#define XEMACPS_RX512CNT_OFFSET      0x00000178U /**< Error-free 512-1023 byte
                                                      Frames Received Counter */
#define XEMACPS_RX1024CNT_OFFSET     0x0000017CU /**< Error-free 1024-1518 byte
                                                      Frames Received Counter */
#define XEMACPS_RX1519CNT_OFFSET     0x00000180U /**< Error-free 1519-max byte
                                                      Frames Received Counter */
#define XEMACPS_RXUNDRCNT_OFFSET     0x00000184U /**< Undersize Frames Received
                                                      Counter */
#define XEMACPS_RXOVRCNT_OFFSET      0x00000188U /**< Oversize Frames Received
                                                      Counter */
#define XEMACPS_RXJABCNT_OFFSET      0x0000018CU /**< Jabbers Received
                                                      Counter */
#define XEMACPS_RXFCSCNT_OFFSET      0x00000190U /**< Frame Check Sequence
                                                      Error Counter */
#define XEMACPS_RXLENGTHCNT_OFFSET   0x00000194U /**< Length Field Error
                                                      Counter */
#define XEMACPS_RXSYMBCNT_OFFSET     0x00000198U /**< Symbol Error Counter */
#define XEMACPS_RXALIGNCNT_OFFSET    0x0000019CU /**< Alignment Error Counter */
#define XEMACPS_RXRESERRCNT_OFFSET   0x000001A0U /**< Receive Resource Error
                                                      Counter */
#define XEMACPS_RXORCNT_OFFSET       0x000001A4U /**< Receive Overrun Counter */
#define XEMACPS_RXIPCCNT_OFFSET      0x000001A8U /**< IP header Checksum Error
                                                      Counter */
#define XEMACPS_RXTCPCCNT_OFFSET     0x000001ACU /**< TCP Checksum Error
                                                      Counter */
#define XEMACPS_RXUDPCCNT_OFFSET     0x000001B0U /**< UDP Checksum Error
                                                      Counter */
#define XEMACPS_LAST_OFFSET          0x000001B4U /**< Last statistic counter
                              offset, for clearing */

#define XEMACPS_1588_SEC_OFFSET      0x000001D0U /**< 1588 second counter */
#define XEMACPS_1588_NANOSEC_OFFSET  0x000001D4U /**< 1588 nanosecond counter */
#define XEMACPS_1588_ADJ_OFFSET      0x000001D8U /**< 1588 nanosecond
                              adjustment counter */
#define XEMACPS_1588_INC_OFFSET      0x000001DCU /**< 1588 nanosecond
                              increment counter */
#define XEMACPS_PTP_TXSEC_OFFSET     0x000001E0U /**< 1588 PTP transmit second
                              counter */
#define XEMACPS_PTP_TXNANOSEC_OFFSET 0x000001E4U /**< 1588 PTP transmit
                              nanosecond counter */
#define XEMACPS_PTP_RXSEC_OFFSET     0x000001E8U /**< 1588 PTP receive second
                              counter */
#define XEMACPS_PTP_RXNANOSEC_OFFSET 0x000001ECU /**< 1588 PTP receive
                              nanosecond counter */
#define XEMACPS_PTPP_TXSEC_OFFSET    0x000001F0U /**< 1588 PTP peer transmit
                              second counter */
#define XEMACPS_PTPP_TXNANOSEC_OFFSET 0x000001F4U /**< 1588 PTP peer transmit
                              nanosecond counter */
#define XEMACPS_PTPP_RXSEC_OFFSET    0x000001F8U /**< 1588 PTP peer receive
                              second counter */
#define XEMACPS_PTPP_RXNANOSEC_OFFSET 0x000001FCU /**< 1588 PTP peer receive
                              nanosecond counter */

#define XEMACPS_INTQ1_STS_OFFSET     0x00000400U /**< Interrupt Q1 Status
                            reg */
#define XEMACPS_TXQ1BASE_OFFSET         0x00000440U /**< TX Q1 Base address
                            reg */
#define XEMACPS_RXQ1BASE_OFFSET         0x00000480U /**< RX Q1 Base address
                            reg */
#define XEMACPS_MSBBUF_TXQBASE_OFFSET  0x000004C8U /**< MSB Buffer TX Q Base
                            reg */
#define XEMACPS_MSBBUF_RXQBASE_OFFSET  0x000004D4U /**< MSB Buffer RX Q Base
                            reg */
#define XEMACPS_INTQ1_IER_OFFSET     0x00000600U /**< Interrupt Q1 Enable
                            reg */
#define XEMACPS_INTQ1_IDR_OFFSET     0x00000620U /**< Interrupt Q1 Disable
                            reg */
#define XEMACPS_INTQ1_IMR_OFFSET     0x00000640U /**< Interrupt Q1 Mask
                            reg */

/* Define some bit positions for registers. */

/** @name network control register bit definitions
 * @{
 */
#define XEMACPS_NWCTRL_FLUSH_DPRAM_MASK    0x00040000U /**< Flush a packet from
                            Rx SRAM */
#define XEMACPS_NWCTRL_ZEROPAUSETX_MASK 0x00000800U /**< Transmit zero quantum
                                                         pause frame */
#define XEMACPS_NWCTRL_PAUSETX_MASK     0x00000800U /**< Transmit pause frame */
#define XEMACPS_NWCTRL_HALTTX_MASK      0x00000400U /**< Halt transmission
                                                         after current frame */
#define XEMACPS_NWCTRL_STARTTX_MASK     0x00000200U /**< Start tx (tx_go) */

#define XEMACPS_NWCTRL_STATWEN_MASK     0x00000080U /**< Enable writing to
                                                         stat counters */
#define XEMACPS_NWCTRL_STATINC_MASK     0x00000040U /**< Increment statistic
                                                         registers */
#define XEMACPS_NWCTRL_STATCLR_MASK     0x00000020U /**< Clear statistic
                                                         registers */
#define XEMACPS_NWCTRL_MDEN_MASK        0x00000010U /**< Enable MDIO port */
#define XEMACPS_NWCTRL_TXEN_MASK        0x00000008U /**< Enable transmit */
#define XEMACPS_NWCTRL_RXEN_MASK        0x00000004U /**< Enable receive */
#define XEMACPS_NWCTRL_LOOPEN_MASK      0x00000002U /**< local loopback */
/*@}*/

/** @name network configuration register bit definitions
 * @{
 */
#define XEMACPS_NWCFG_BADPREAMBEN_MASK 0x20000000U /**< disable rejection of
                                                        non-standard preamble */
#define XEMACPS_NWCFG_IPDSTRETCH_MASK  0x10000000U /**< enable transmit IPG */
#define XEMACPS_NWCFG_SGMIIEN_MASK     0x08000000U /**< SGMII Enable */
#define XEMACPS_NWCFG_FCSIGNORE_MASK   0x04000000U /**< disable rejection of
                                                        FCS error */
#define XEMACPS_NWCFG_HDRXEN_MASK      0x02000000U /**< RX half duplex */
#define XEMACPS_NWCFG_RXCHKSUMEN_MASK  0x01000000U /**< enable RX checksum
                                                        offload */
#define XEMACPS_NWCFG_PAUSECOPYDI_MASK 0x00800000U /**< Do not copy pause
                                                        Frames to memory */
#define XEMACPS_NWCFG_DWIDTH_64_MASK   0x00200000U /**< 64 bit Data bus width */
#define XEMACPS_NWCFG_MDC_SHIFT_MASK   18U       /**< shift bits for MDC */
#define XEMACPS_NWCFG_MDCCLKDIV_MASK   0x001C0000U /**< MDC Mask PCLK divisor */
#define XEMACPS_NWCFG_FCSREM_MASK      0x00020000U /**< Discard FCS from
                                                        received frames */
#define XEMACPS_NWCFG_LENERRDSCRD_MASK 0x00010000U
/**< RX length error discard */
#define XEMACPS_NWCFG_RXOFFS_MASK      0x0000C000U /**< RX buffer offset */
#define XEMACPS_NWCFG_PAUSEEN_MASK     0x00002000U /**< Enable pause RX */
#define XEMACPS_NWCFG_RETRYTESTEN_MASK 0x00001000U /**< Retry test */
#define XEMACPS_NWCFG_XTADDMACHEN_MASK 0x00000200U
/**< External address match enable */
#define XEMACPS_NWCFG_PCSSEL_MASK      0x00000800U /**< PCS Select */
#define XEMACPS_NWCFG_1000_MASK        0x00000400U /**< 1000 Mbps */
#define XEMACPS_NWCFG_1536RXEN_MASK    0x00000100U /**< Enable 1536 byte
                                                        frames reception */
#define XEMACPS_NWCFG_UCASTHASHEN_MASK 0x00000080U /**< Receive unicast hash
                                                        frames */
#define XEMACPS_NWCFG_MCASTHASHEN_MASK 0x00000040U /**< Receive multicast hash
                                                        frames */
#define XEMACPS_NWCFG_BCASTDI_MASK     0x00000020U /**< Do not receive
                                                        broadcast frames */
#define XEMACPS_NWCFG_COPYALLEN_MASK   0x00000010U /**< Copy all frames */
#define XEMACPS_NWCFG_JUMBO_MASK       0x00000008U /**< Jumbo frames */
#define XEMACPS_NWCFG_NVLANDISC_MASK   0x00000004U /**< Receive only VLAN
                                                        frames */
#define XEMACPS_NWCFG_FDEN_MASK        0x00000002U/**< full duplex */
#define XEMACPS_NWCFG_100_MASK         0x00000001U /**< 100 Mbps */
#define XEMACPS_NWCFG_RESET_MASK       0x00080000U/**< reset value */
/*@}*/

/** @name network status register bit definitaions
 * @{
 */
#define XEMACPS_NWSR_MDIOIDLE_MASK     0x00000004U /**< PHY management idle */
#define XEMACPS_NWSR_MDIO_MASK         0x00000002U /**< Status of mdio_in */
/*@}*/


/** @name MAC address register word 1 mask
 * @{
 */
#define XEMACPS_LADDR_MACH_MASK        0x0000FFFFU /**< Address bits[47:32]
                                                      bit[31:0] are in BOTTOM */
/*@}*/


/** @name DMA control register bit definitions
 * @{
 */
#define XEMACPS_DMACR_ADDR_WIDTH_64        0x40000000U /**< 64 bit address bus */
#define XEMACPS_DMACR_TXEXTEND_MASK        0x20000000U /**< Tx Extended desc mode */
#define XEMACPS_DMACR_RXEXTEND_MASK        0x10000000U /**< Rx Extended desc mode */
#define XEMACPS_DMACR_RXBUF_MASK        0x00FF0000U /**< Mask bit for RX buffer
                                                    size */
#define XEMACPS_DMACR_RXBUF_SHIFT         16U    /**< Shift bit for RX buffer
                                                size */
#define XEMACPS_DMACR_TCPCKSUM_MASK        0x00000800U /**< enable/disable TX
                                                        checksum offload */
#define XEMACPS_DMACR_TXSIZE_MASK        0x00000400U /**< TX buffer memory size */
#define XEMACPS_DMACR_RXSIZE_MASK        0x00000300U /**< RX buffer memory size */
#define XEMACPS_DMACR_ENDIAN_MASK        0x00000080U /**< endian configuration */
#define XEMACPS_DMACR_BLENGTH_MASK        0x0000001FU /**< buffer burst length */
#define XEMACPS_DMACR_SINGLE_AHB_BURST    0x00000001U /**< single AHB bursts */
#define XEMACPS_DMACR_INCR4_AHB_BURST    0x00000004U /**< 4 bytes AHB bursts */
#define XEMACPS_DMACR_INCR8_AHB_BURST    0x00000008U /**< 8 bytes AHB bursts */
#define XEMACPS_DMACR_INCR16_AHB_BURST    0x00000010U /**< 16 bytes AHB bursts */
/*@}*/

/** @name transmit status register bit definitions
 * @{
 */
#define XEMACPS_TXSR_HRESPNOK_MASK    0x00000100U /**< Transmit hresp not OK */
#define XEMACPS_TXSR_URUN_MASK        0x00000040U /**< Transmit underrun */
#define XEMACPS_TXSR_TXCOMPL_MASK     0x00000020U /**< Transmit completed OK */
#define XEMACPS_TXSR_BUFEXH_MASK      0x00000010U /**< Transmit buffs exhausted
                                                       mid frame */
#define XEMACPS_TXSR_TXGO_MASK        0x00000008U /**< Status of go flag */
#define XEMACPS_TXSR_RXOVR_MASK       0x00000004U /**< Retry limit exceeded */
#define XEMACPS_TXSR_FRAMERX_MASK     0x00000002U /**< Collision tx frame */
#define XEMACPS_TXSR_USEDREAD_MASK    0x00000001U /**< TX buffer used bit set */

#define XEMACPS_TXSR_ERROR_MASK      ((u32)XEMACPS_TXSR_HRESPNOK_MASK | \
                                       (u32)XEMACPS_TXSR_URUN_MASK | \
                                       (u32)XEMACPS_TXSR_BUFEXH_MASK | \
                                       (u32)XEMACPS_TXSR_RXOVR_MASK | \
                                       (u32)XEMACPS_TXSR_FRAMERX_MASK | \
                                       (u32)XEMACPS_TXSR_USEDREAD_MASK)
/*@}*/

/**
 * @name receive status register bit definitions
 * @{
 */
#define XEMACPS_RXSR_HRESPNOK_MASK    0x00000008U /**< Receive hresp not OK */
#define XEMACPS_RXSR_RXOVR_MASK       0x00000004U /**< Receive overrun */
#define XEMACPS_RXSR_FRAMERX_MASK     0x00000002U /**< Frame received OK */
#define XEMACPS_RXSR_BUFFNA_MASK      0x00000001U /**< RX buffer used bit set */

#define XEMACPS_RXSR_ERROR_MASK      ((u32)XEMACPS_RXSR_HRESPNOK_MASK | \
                                       (u32)XEMACPS_RXSR_RXOVR_MASK | \
                                       (u32)XEMACPS_RXSR_BUFFNA_MASK)

#define XEMACPS_SR_ALL_MASK    0xFFFFFFFFU /**< Mask for full register */

/*@}*/

/**
 * @name Interrupt Q1 status register bit definitions
 * @{
 */
#define XEMACPS_INTQ1SR_TXCOMPL_MASK    0x00000080U /**< Transmit completed OK */
#define XEMACPS_INTQ1SR_TXERR_MASK    0x00000040U /**< Transmit AMBA Error */

#define XEMACPS_INTQ1_IXR_ALL_MASK    ((u32)XEMACPS_INTQ1SR_TXCOMPL_MASK | \
                     (u32)XEMACPS_INTQ1SR_TXERR_MASK)

/*@}*/

/**
 * @name interrupts bit definitions
 * Bits definitions are same in XEMACPS_ISR_OFFSET,
 * XEMACPS_IER_OFFSET, XEMACPS_IDR_OFFSET, and XEMACPS_IMR_OFFSET
 * @{
 */
#define XEMACPS_IXR_PTPPSTX_MASK    0x02000000U /**< PTP Pdelay_resp TXed */
#define XEMACPS_IXR_PTPPDRTX_MASK    0x01000000U /**< PTP Pdelay_req TXed */
#define XEMACPS_IXR_PTPPSRX_MASK    0x00800000U /**< PTP Pdelay_resp RXed */
#define XEMACPS_IXR_PTPPDRRX_MASK    0x00400000U /**< PTP Pdelay_req RXed */

#define XEMACPS_IXR_PTPSTX_MASK        0x00200000U /**< PTP Sync TXed */
#define XEMACPS_IXR_PTPDRTX_MASK    0x00100000U /**< PTP Delay_req TXed */
#define XEMACPS_IXR_PTPSRX_MASK        0x00080000U /**< PTP Sync RXed */
#define XEMACPS_IXR_PTPDRRX_MASK    0x00040000U /**< PTP Delay_req RXed */

#define XEMACPS_IXR_PAUSETX_MASK    0x00004000U    /**< Pause frame transmitted */
#define XEMACPS_IXR_PAUSEZERO_MASK  0x00002000U    /**< Pause time has reached
                                                     zero */
#define XEMACPS_IXR_PAUSENZERO_MASK 0x00001000U    /**< Pause frame received */
#define XEMACPS_IXR_HRESPNOK_MASK   0x00000800U    /**< hresp not ok */
#define XEMACPS_IXR_RXOVR_MASK      0x00000400U    /**< Receive overrun occurred */
#define XEMACPS_IXR_TXCOMPL_MASK    0x00000080U    /**< Frame transmitted ok */
#define XEMACPS_IXR_TXEXH_MASK      0x00000040U    /**< Transmit err occurred or
                                                     no buffers*/
#define XEMACPS_IXR_RETRY_MASK      0x00000020U    /**< Retry limit exceeded */
#define XEMACPS_IXR_URUN_MASK       0x00000010U    /**< Transmit underrun */
#define XEMACPS_IXR_TXUSED_MASK     0x00000008U    /**< Tx buffer used bit read */
#define XEMACPS_IXR_RXUSED_MASK     0x00000004U    /**< Rx buffer used bit read */
#define XEMACPS_IXR_FRAMERX_MASK    0x00000002U    /**< Frame received ok */
#define XEMACPS_IXR_MGMNT_MASK      0x00000001U    /**< PHY management complete */
#define XEMACPS_IXR_ALL_MASK        0x00007FFFU    /**< Everything! */

#define XEMACPS_IXR_TX_ERR_MASK    ((u32)XEMACPS_IXR_TXEXH_MASK |         \
                                     (u32)XEMACPS_IXR_RETRY_MASK |         \
                                     (u32)XEMACPS_IXR_URUN_MASK)


#define XEMACPS_IXR_RX_ERR_MASK    ((u32)XEMACPS_IXR_HRESPNOK_MASK |      \
                                     (u32)XEMACPS_IXR_RXUSED_MASK |        \
                                     (u32)XEMACPS_IXR_RXOVR_MASK)

/*@}*/

/** @name PHY Maintenance bit definitions
 * @{
 */
#define XEMACPS_PHYMNTNC_OP_MASK    0x40020000U    /**< operation mask bits */
#define XEMACPS_PHYMNTNC_OP_R_MASK  0x20000000U    /**< read operation */
#define XEMACPS_PHYMNTNC_OP_W_MASK  0x10000000U    /**< write operation */
#define XEMACPS_PHYMNTNC_ADDR_MASK  0x0F800000U    /**< Address bits */
#define XEMACPS_PHYMNTNC_REG_MASK   0x007C0000U    /**< register bits */
#define XEMACPS_PHYMNTNC_DATA_MASK  0x00000FFFU    /**< data bits */
#define XEMACPS_PHYMNTNC_PHAD_SHFT_MSK   23U    /**< Shift bits for PHYAD */
#define XEMACPS_PHYMNTNC_PREG_SHFT_MSK   18U    /**< Shift bits for PHREG */
/*@}*/

/** @name RX watermark bit definitions
 * @{
 */
#define XEMACPS_RXWM_HIGH_MASK        0x0000FFFFU    /**< RXWM high mask */
#define XEMACPS_RXWM_LOW_MASK        0xFFFF0000U    /**< RXWM low mask */
#define XEMACPS_RXWM_LOW_SHFT_MSK    16U    /**< Shift for RXWM low */
/*@}*/

/* Transmit buffer descriptor status words offset
 * @{
 */
#define XEMACPS_BD_ADDR_OFFSET  0x00000000U /**< word 0/addr of BDs */
#define XEMACPS_BD_STAT_OFFSET  0x00000004U /**< word 1/status of BDs */
#define XEMACPS_BD_ADDR_HI_OFFSET  0x00000008U /**< word 2/addr of BDs */

/*
 * @}
 */

/* Transmit buffer descriptor status words bit positions.
 * Transmit buffer descriptor consists of two 32-bit registers,
 * the first - word0 contains a 32-bit address pointing to the location of
 * the transmit data.
 * The following register - word1, consists of various information to control
 * the XEmacPs transmit process.  After transmit, this is updated with status
 * information, whether the frame was transmitted OK or why it had failed.
 * @{
 */
#define XEMACPS_TXBUF_USED_MASK  0x80000000U /**< Used bit. */
#define XEMACPS_TXBUF_WRAP_MASK  0x40000000U /**< Wrap bit, last descriptor */
#define XEMACPS_TXBUF_RETRY_MASK 0x20000000U /**< Retry limit exceeded */
#define XEMACPS_TXBUF_URUN_MASK  0x10000000U /**< Transmit underrun occurred */
#define XEMACPS_TXBUF_EXH_MASK   0x08000000U /**< Buffers exhausted */
#define XEMACPS_TXBUF_TCP_MASK   0x04000000U /**< Late collision. */
#define XEMACPS_TXBUF_NOCRC_MASK 0x00010000U /**< No CRC */
#define XEMACPS_TXBUF_LAST_MASK  0x00008000U /**< Last buffer */
#define XEMACPS_TXBUF_LEN_MASK   0x00003FFFU /**< Mask for length field */
/*
 * @}
 */

/* Receive buffer descriptor status words bit positions.
 * Receive buffer descriptor consists of two 32-bit registers,
 * the first - word0 contains a 32-bit word aligned address pointing to the
 * address of the buffer. The lower two bits make up the wrap bit indicating
 * the last descriptor and the ownership bit to indicate it has been used by
 * the XEmacPs.
 * The following register - word1, contains status information regarding why
 * the frame was received (the filter match condition) as well as other
 * useful info.
 * @{
 */
#define XEMACPS_RXBUF_BCAST_MASK     0x80000000U /**< Broadcast frame */
#define XEMACPS_RXBUF_MULTIHASH_MASK 0x40000000U /**< Multicast hashed frame */
#define XEMACPS_RXBUF_UNIHASH_MASK   0x20000000U /**< Unicast hashed frame */
#define XEMACPS_RXBUF_EXH_MASK       0x08000000U /**< buffer exhausted */
#define XEMACPS_RXBUF_AMATCH_MASK    0x06000000U /**< Specific address
                                                      matched */
#define XEMACPS_RXBUF_IDFOUND_MASK   0x01000000U /**< Type ID matched */
#define XEMACPS_RXBUF_IDMATCH_MASK   0x00C00000U /**< ID matched mask */
#define XEMACPS_RXBUF_VLAN_MASK      0x00200000U /**< VLAN tagged */
#define XEMACPS_RXBUF_PRI_MASK       0x00100000U /**< Priority tagged */
#define XEMACPS_RXBUF_VPRI_MASK      0x000E0000U /**< Vlan priority */
#define XEMACPS_RXBUF_CFI_MASK       0x00010000U /**< CFI frame */
#define XEMACPS_RXBUF_EOF_MASK       0x00008000U /**< End of frame. */
#define XEMACPS_RXBUF_SOF_MASK       0x00004000U /**< Start of frame. */
#define XEMACPS_RXBUF_LEN_MASK       0x00001FFFU /**< Mask for length field */
#define XEMACPS_RXBUF_LEN_JUMBO_MASK 0x00003FFFU /**< Mask for jumbo length */

#define XEMACPS_RXBUF_WRAP_MASK      0x00000002U /**< Wrap bit, last BD */
#define XEMACPS_RXBUF_NEW_MASK       0x00000001U /**< Used bit.. */
#define XEMACPS_RXBUF_ADD_MASK       0xFFFFFFFCU /**< Mask for address */
/*
 * @}
 */

/*
 * Define appropriate I/O access method to memory mapped I/O or other
 * interface if necessary.
 */

#define XEmacPs_In32  Xil_In32
#define XEmacPs_Out32 Xil_Out32


/****************************************************************************/
/**
*
* Read the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XEmacPs_ReadReg(u32 BaseAddress, u32 RegOffset)
*
*****************************************************************************/
#define XEmacPs_ReadReg(BaseAddress, RegOffset) \
    XEmacPs_In32((BaseAddress) + (u32)(RegOffset))


/****************************************************************************/
/**
*
* Write the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XEmacPs_WriteReg(u32 BaseAddress, u32 RegOffset,
*         u32 Data)
*
*****************************************************************************/
#define XEmacPs_WriteReg(BaseAddress, RegOffset, Data) \
    XEmacPs_Out32((BaseAddress) + (u32)(RegOffset), (u32)(Data))

/************************** Function Prototypes *****************************/
/*
 * Perform reset operation to the emacps interface
 */
void XEmacPs_ResetHw(u32 BaseAddr);

#ifdef __cplusplus
  }
#endif

#endif /* end of protection macro */
/** @} */
