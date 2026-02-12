/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_eth.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_78X_ETH_H__
#define __N32H76X_78X_ETH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "n32h76x_78x.h"
#include "n32h76x_78x_rcc.h"
#include "n32h76x_78x_gpio.h"


#define ETH_TX_DESC_NUMBER ((uint32_t)0x00000004U) /* Tx Descriptor Length: Minimum is 4, maximum is 1024 */
#define ETH_RX_DESC_NUMBER ((uint32_t)0x00000004U) /* Rx Descriptor Length: Minimum is 4, maximum is 1024 */


/*** ETH Structure Definition Start ***/

typedef enum
{
    ETH_MII_MODE   = ((uint32_t)0x00000000U),
    ETH_RMII_MODE  = ((uint32_t)0x00000001U),
    ETH_GMII_MODE  = ((uint32_t)0x00000002U)
} EthMediaInterfaceType;

typedef enum
{
    ETH_MDCCLK_NORMAL = ((uint32_t)0x00000000U), /* Frequency range: 1.0MHz ≤ MDC clock ≤ 2.5MHz */
    ETH_MDCCLK_FAST   = ((uint32_t)0x00000001U)  /* Frequency range: MDC clock > 2.5MHz */
} EthMdcClkType;

typedef enum
{
    ETH_SUCCESS       = ((uint32_t)0x00000000U), /* No error */
    ETH_ERROR_BUSY    = ((uint32_t)0x00000001U), /* Busy error */
    ETH_ERROR_PARAM   = ((uint32_t)0x00000002U), /* Parameter error */
    ETH_ERROR_TIMEOUT = ((uint32_t)0x00000004U), /* Timeout error */
    ETH_ERROR_DMA     = ((uint32_t)0x00000008U), /* DMA transfer error */
    ETH_ERROR_MAC     = ((uint32_t)0x00000010U), /* MAC transfer error */
    ETH_ERROR_RPHY    = ((uint32_t)0x00000020U), /* Read PHY register error */
    ETH_ERROR_WPHY    = ((uint32_t)0x00000040U), /* Write PHY register error */
    DESC_OWNED_BY_DMA = ((uint32_t)0x00000080U), /* Descriptor is owned by the DMA */
    NO_DESC_TO_BUILD  = ((uint32_t)0x00000100U), /* No descriptors to build */
    NO_DATA_TRANSFER  = ((uint32_t)0x00000200U), /* No data transfer */
    FATAL_BUS_ERROR   = ((uint32_t)0x00000400U), /* Fatal Bus Error */
    ETH_ERROR_MIF     = ((uint32_t)0x00000800U)  /* Media interface selection error */
} EthFuncStatusType;

typedef enum
{
    ETH_MAC_ADDR0_OFFSET = ((uint32_t)0x00000000U), /* MAC Address0 Offset */
    ETH_MAC_ADDR1_OFFSET = ((uint32_t)0x00000008U), /* MAC Address1 Offset */
    ETH_MAC_ADDR2_OFFSET = ((uint32_t)0x00000010U), /* MAC Address2 Offset */
    ETH_MAC_ADDR3_OFFSET = ((uint32_t)0x00000018U)  /* MAC Address3 Offset */
} EthMacAddr0123Type;

typedef enum
{
    ETH_MACADDR1_OFFSET = ((uint32_t)0x00000008U), /* MAC Address1 Offset */
    ETH_MACADDR2_OFFSET = ((uint32_t)0x00000010U), /* MAC Address2 Offset */
    ETH_MACADDR3_OFFSET = ((uint32_t)0x00000018U)  /* MAC Address3 Offset */
} EthMacAddr123Type;

typedef enum
{
    ETH_MMC_SCGP_OFFSET  = ((uint32_t)0x0000004CU), /* TX Single Collision Good Packets Counter register address Offset */
    ETH_MMC_MCGP_OFFSET  = ((uint32_t)0x00000050U), /* TX Multiple Collision Good Packets Counter register address Offset */
    ETH_MMC_PCG_OFFSET   = ((uint32_t)0x00000068U), /* TX Good Packets Counter register address Offset */
    ETH_MMC_BPG_OFFSET   = ((uint32_t)0x0000008CU), /* RX Good Broadcast Packets Counter register address Offset */
    ETH_MMC_MPG_OFFSET   = ((uint32_t)0x00000090U), /* RX Good Multicast Packets Counter register address Offset */
    ETH_MMC_CRCEP_OFFSET = ((uint32_t)0x00000094U), /* RX CRC Error Packets Counter register address Offset */
    ETH_MMC_AEP_OFFSET   = ((uint32_t)0x00000098U), /* RX Alignment Error Packets Counter register address Offset */
    ETH_MMC_UPG_OFFSET   = ((uint32_t)0x000000C4U)  /* RX Good Unicast Packets Counter register address Offset */
} EthMmcAddrType;

typedef enum
{
    ETH_MACTS_SSIR_OFFSET   = ((uint32_t)0x00000004U), /* Sub Second Increment register address Offset */
    ETH_MACTS_STSR_OFFSET   = ((uint32_t)0x00000008U), /* System Time Seconds register address Offset */
    ETH_MACTS_STNSR_OFFSET  = ((uint32_t)0x0000000CU), /* System Time Nanoseconds register address Offset */
    ETH_MACTS_STSUR_OFFSET  = ((uint32_t)0x00000010U), /* System Time Seconds Update register address Offset */
    ETH_MACTS_STNSUR_OFFSET = ((uint32_t)0x00000014U), /* System Time Nanoseconds Update register address Offset */
    ETH_MACTS_TAR_OFFSET    = ((uint32_t)0x00000018U), /* Timestamp Addend register address Offset */
    ETH_MACTS_TTSNSR_OFFSET = ((uint32_t)0x00000030U), /* Tx Timestamp Status Nanoseconds register address Offset */
    ETH_MACTS_TTSSR_OFFSET  = ((uint32_t)0x00000034U), /* Tx Timestamp Status Seconds register address Offset */
    ETH_MACTS_TICNSR_OFFSET = ((uint32_t)0x00000058U), /* Timestamp Ingress Correction Nanosecond register address Offset */
    ETH_MACTS_TECNSR_OFFSET = ((uint32_t)0x0000005CU), /* Timestamp Egress Correction Nanosecond register address Offset */
    ETH_MACTS_TILR_OFFSET   = ((uint32_t)0x00000068U), /* Timestamp Ingress Latency register address Offset */
    ETH_MACTS_TELR_OFFSET   = ((uint32_t)0x0000006CU), /* Timestamp Egress Latency register address Offset */
    ETH_MACTS_PTTSR_OFFSET  = ((uint32_t)0x00000080U), /* PPS Target Time Seconds register address Offset */
    ETH_MACTS_PTTNSR_OFFSET = ((uint32_t)0x00000084U)  /* PPS Target Time Nanosecond register address Offset */
} EthTsAddrType;

typedef enum
{
    ETH_TX_PACKETS_FEATURES_CSUM         = ((uint32_t)0x00000001U), /* Checksum Control */
    ETH_TX_PACKETS_FEATURES_SAIC         = ((uint32_t)0x00000002U), /* Source Address Insertion Control */
    ETH_TX_PACKETS_FEATURES_VLANTAG      = ((uint32_t)0x00000004U), /* VLAN Tag */
    ETH_TX_PACKETS_FEATURES_INNERVLANTAG = ((uint32_t)0x00000008U), /* Inner VLAN Tag */
    ETH_TX_PACKETS_FEATURES_TSO          = ((uint32_t)0x00000010U), /* TCP Segementation */
    ETH_TX_PACKETS_FEATURES_CRCPAD       = ((uint32_t)0x00000020U), /* CRC Pad Control */
    ETH_TX_PACKETS_FEATURES_OSTC         = ((uint32_t)0x00000040U)  /* One-Step Timestamp Correction */
} EthTxPackAttrType;

typedef enum
{
    ETH_MACADDR_FILTER_SA = ((uint32_t)0x00000000U),
    ETH_MACADDR_FILTER_DA = ((uint32_t)0x00000008U)
} EthMacAddrFilterType;

typedef enum
{
    ETH_PREAMBLE_LEN_7BYTES = ((uint32_t)0x00000000U),
    ETH_PREAMBLE_LEN_5BYTES = ((uint32_t)0x00000004U),
    ETH_PREAMBLE_LEN_3BYTES = ((uint32_t)0x00000008U)
} EthTxPreLenType;

typedef enum
{
    ETH_BACK_OFF_LIMIT_10 = ((uint32_t)0x00000000U),
    ETH_BACK_OFF_LIMIT_8  = ((uint32_t)0x00000020U),
    ETH_BACK_OFF_LIMIT_4  = ((uint32_t)0x00000040U),
    ETH_BACK_OFF_LIMIT_1  = ((uint32_t)0x00000060U)
} EthBacOffLimType;

typedef enum
{
    ETH_HALF_DUPLEX_MODE = ((uint32_t)0x00000000U),
    ETH_FULL_DUPLEX_MODE = ((uint32_t)0x00002000U)
} EthDuplexType;

typedef enum
{
    ETH_SPEED_1000M = ((uint32_t)0x00000000U),
    ETH_SPEED_10M   = ((uint32_t)0x00008000U),
    ETH_SPEED_100M  = ((uint32_t)0x0000C000U)
} EthSpeedType;

typedef enum
{
    ETH_INTER_PACKET_GAP_96BIT = ((uint32_t)0x00000000U),
    ETH_INTER_PACKET_GAP_88BIT = ((uint32_t)0x01000000U),
    ETH_INTER_PACKET_GAP_80BIT = ((uint32_t)0x02000000U),
    ETH_INTER_PACKET_GAP_72BIT = ((uint32_t)0x03000000U),
    ETH_INTER_PACKET_GAP_64BIT = ((uint32_t)0x04000000U),
    ETH_INTER_PACKET_GAP_56BIT = ((uint32_t)0x05000000U),
    ETH_INTER_PACKET_GAP_48BIT = ((uint32_t)0x06000000U),
    ETH_INTER_PACKET_GAP_40BIT = ((uint32_t)0x07000000U)
} EthIntPktGapType;

typedef enum
{
    ETH_SRC_ADDR_CTRL_INTERNAL_SIGNALS = ((uint32_t)0x00000000U), /* The generation of the source address field is controlled by internal signals */
    ETH_SRC_ADDR_CTRL_INSERT_MACAR0    = ((uint32_t)0x20000000U), /* The Source Address field is inserted by the contents of the MAC Address 0 register */
    ETH_SRC_ADDR_CTRL_REPLACE_MACAR0   = ((uint32_t)0x30000000U), /* The Source Address field is replaced by the contents of the MAC Address 0 register */
    ETH_SRC_ADDR_CTRL_INSERT_MACAR1    = ((uint32_t)0x60000000U), /* The Source Address field is inserted by the contents of the MAC Address 1 register */
    ETH_SRC_ADDR_CTRL_REPLACE_MACAR1   = ((uint32_t)0x70000000U), /* The Source Address field is replaced by the contents of the MAC Address 1 register */
} EthSrcAddrCtrlType;

typedef enum
{
    ETH_CTRL_PACKETS_FLTR_ALL    = ((uint32_t)0x00000000U), /* MAC filters all control packets from reaching the application */
    ETH_CTRL_PACKETS_FW_XCPT_PAU = ((uint32_t)0x00000040U), /* MAC forwards all control packets except Pause packets to the \
                                                               application even if they fail the Address filter */
    ETH_CTRL_PACKETS_FW_ALL      = ((uint32_t)0x00000080U), /* MAC forwards all control packets to the application even if  \
                                                               they fail the Address filter */
    ETH_CTRL_PACKETS_FW_PASS     = ((uint32_t)0x000000C0U)  /* MAC forwards the control packets that pass the Address filter */
} EthCtrlPktType;

typedef enum
{
    ETH_WDG_TIMEOUT_2KBYTES  = ((uint32_t)0x00000000U),
    ETH_WDG_TIMEOUT_3KBYTES  = ((uint32_t)0x00000001U),
    ETH_WDG_TIMEOUT_4KBYTES  = ((uint32_t)0x00000002U),
    ETH_WDG_TIMEOUT_5KBYTES  = ((uint32_t)0x00000003U),
    ETH_WDG_TIMEOUT_6KBYTES  = ((uint32_t)0x00000004U),
    ETH_WDG_TIMEOUT_7KBYTES  = ((uint32_t)0x00000005U),
    ETH_WDG_TIMEOUT_8KBYTES  = ((uint32_t)0x00000006U),
    ETH_WDG_TIMEOUT_9KBYTES  = ((uint32_t)0x00000007U),
    ETH_WDG_TIMEOUT_10KBYTES = ((uint32_t)0x00000008U),
    ETH_WDG_TIMEOUT_11KBYTES = ((uint32_t)0x00000009U),
    ETH_WDG_TIMEOUT_12KBYTES = ((uint32_t)0x0000000AU),
    ETH_WDG_TIMEOUT_13KBYTES = ((uint32_t)0x0000000BU),
    ETH_WDG_TIMEOUT_14KBYTES = ((uint32_t)0x0000000CU),
    ETH_WDG_TIMEOUT_15KBYTES = ((uint32_t)0x0000000DU),
    ETH_WDG_TIMEOUT_16KBYTES = ((uint32_t)0x0000000EU)
} EthWdgTimOutType;

typedef enum
{
    ETH_PAUSE_LOW_THRESHOLD_PT4   = ((uint32_t)0x00000000U), /* Pause Time minus 4 Slot Times */
    ETH_PAUSE_LOW_THRESHOLD_PT28  = ((uint32_t)0x00000010U), /* Pause Time minus 28 Slot Times */
    ETH_PAUSE_LOW_THRESHOLD_PT36  = ((uint32_t)0x00000020U), /* Pause Time minus 36 Slot Times */
    ETH_PAUSE_LOW_THRESHOLD_PT144 = ((uint32_t)0x00000030U), /* Pause Time minus 144 Slot Times */
    ETH_PAUSE_LOW_THRESHOLD_PT256 = ((uint32_t)0x00000040U), /* Pause Time minus 256 Slot Times */
    ETH_PAUSE_LOW_THRESHOLD_PT512 = ((uint32_t)0x00000050U)  /* Pause Time minus 512 Slot Times */
} EthPauLowThdType;

typedef enum
{
    ETH_TXQUEUE_OPERATE_THRESHOLD_32  = ((uint32_t)0x00000000U), /* Threshold Mode, level: 32Bytes */
    ETH_TXQUEUE_OPERATE_STOREFORWARD  = ((uint32_t)0x00000002U), /* Store and Forward Mode */
    ETH_TXQUEUE_OPERATE_THRESHOLD_64  = ((uint32_t)0x00000010U), /* Threshold Mode, level: 64Bytes */
    ETH_TXQUEUE_OPERATE_THRESHOLD_96  = ((uint32_t)0x00000020U), /* Threshold Mode, level: 96Bytes */
    ETH_TXQUEUE_OPERATE_THRESHOLD_128 = ((uint32_t)0x00000030U), /* Threshold Mode, level: 128Bytes */
    ETH_TXQUEUE_OPERATE_THRESHOLD_192 = ((uint32_t)0x00000040U), /* Threshold Mode, level: 192Bytes */
    ETH_TXQUEUE_OPERATE_THRESHOLD_256 = ((uint32_t)0x00000050U), /* Threshold Mode, level: 256Bytes */
    ETH_TXQUEUE_OPERATE_THRESHOLD_384 = ((uint32_t)0x00000060U), /* Threshold Mode, level: 384Bytes */
    ETH_TXQUEUE_OPERATE_THRESHOLD_512 = ((uint32_t)0x00000070U)  /* Threshold Mode, level: 512Bytes */
} EthTxQOpeType;

typedef enum
{
    ETH_RXQUEUE_OPERATE_THRESHOLD_64  = ((uint32_t)0x00000000U), /* Threshold Mode, level: 64Bytes */
    ETH_RXQUEUE_OPERATE_THRESHOLD_32  = ((uint32_t)0x00000001U), /* Threshold Mode, level: 32Bytes */
    ETH_RXQUEUE_OPERATE_THRESHOLD_96  = ((uint32_t)0x00000002U), /* Threshold Mode, level: 96Bytes */
    ETH_RXQUEUE_OPERATE_THRESHOLD_128 = ((uint32_t)0x00000003U), /* Threshold Mode, level: 128Bytes */
    ETH_RXQUEUE_OPERATE_STOREFORWARD  = ((uint32_t)0x00000020U)  /* Store and Forward Mode */
} EthRxQOpeType;

typedef enum
{
    ETH_DMA_ARBITRA_WRR_RX1_TX1 = ((uint32_t)0x00000000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 1:1 */
    ETH_DMA_ARBITRA_FP_RX       = ((uint32_t)0x00000002U), /* Fixed Priority, Rx path has priority over Tx path */
    ETH_DMA_ARBITRA_WRR_TX1_RX1 = ((uint32_t)0x00000800U), /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 1:1 */
    ETH_DMA_ARBITRA_FP_TX       = ((uint32_t)0x00000802U), /* Fixed Priority, Tx path has priority over Rx path */
    ETH_DMA_ARBITRA_WRR_RX2_TX1 = ((uint32_t)0x00001000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 2:1 */
    ETH_DMA_ARBITRA_WRR_TX2_RX1 = ((uint32_t)0x00001800U), /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 2:1 */
    ETH_DMA_ARBITRA_WRR_RX3_TX1 = ((uint32_t)0x00002000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 3:1 */
    ETH_DMA_ARBITRA_WRR_TX3_RX1 = ((uint32_t)0x00002800U), /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 3:1 */
    ETH_DMA_ARBITRA_WRR_RX4_TX1 = ((uint32_t)0x00003000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 4:1 */
    ETH_DMA_ARBITRA_WRR_TX4_RX1 = ((uint32_t)0x00003800U), /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 4:1 */
    ETH_DMA_ARBITRA_WRR_RX5_TX1 = ((uint32_t)0x00004000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 5:1 */
    ETH_DMA_ARBITRA_WRR_TX5_RX1 = ((uint32_t)0x00004800U), /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 5:1 */
    ETH_DMA_ARBITRA_WRR_RX6_TX1 = ((uint32_t)0x00005000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 6:1 */
    ETH_DMA_ARBITRA_WRR_TX6_RX1 = ((uint32_t)0x00005800U), /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 6:1 */
    ETH_DMA_ARBITRA_WRR_RX7_TX1 = ((uint32_t)0x00006000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 7:1 */
    ETH_DMA_ARBITRA_WRR_TX7_RX1 = ((uint32_t)0x00006800U), /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 7:1 */
    ETH_DMA_ARBITRA_WRR_RX8_TX1 = ((uint32_t)0x00007000U), /* Weighted Round-Robin with Rx:Tx, Rx:Tx = 8:1 */
    ETH_DMA_ARBITRA_WRR_TX8_RX1 = ((uint32_t)0x00007800U)  /* Weighted Round-Robin with Tx:Rx, Tx:Rx = 8:1 */
} EthTxRxArbType;

typedef enum
{
    ETH_BURST_MODE_UNFIXED = ((uint32_t)0x00000000U), /* Unspecified length (INCR) or SINGLE transfers */
    ETH_BURST_MODE_FIXED   = ((uint32_t)0x00000001U), /* Specified length (INCRx or SINGLE) */
    ETH_BURST_MODE_MIXED   = ((uint32_t)0x00004000U)  /* Mixed Burst */
} EthBurstType;

typedef enum
{
    ETH_DESC_SKIP_LEN_0BIT   = ((uint32_t)0x00000000U),
    ETH_DESC_SKIP_LEN_32BIT  = ((uint32_t)0x00040000U),
    ETH_DESC_SKIP_LEN_64BIT  = ((uint32_t)0x00080000U),
    ETH_DESC_SKIP_LEN_96BIT  = ((uint32_t)0x000C0000U),
    ETH_DESC_SKIP_LEN_128BIT = ((uint32_t)0x00100000U),
    ETH_DESC_SKIP_LEN_160BIT = ((uint32_t)0x00140000U),
    ETH_DESC_SKIP_LEN_192BIT = ((uint32_t)0x00180000U),
    ETH_DESC_SKIP_LEN_224BIT = ((uint32_t)0x001C0000U)
} EthDesSkiLenType;

typedef enum
{
    ETH_TX_PROGRAM_BURST_LEN_1  = ((uint32_t)0x00010000U),
    ETH_TX_PROGRAM_BURST_LEN_2  = ((uint32_t)0x00020000U),
    ETH_TX_PROGRAM_BURST_LEN_4  = ((uint32_t)0x00040000U),
    ETH_TX_PROGRAM_BURST_LEN_8  = ((uint32_t)0x00080000U),
    ETH_TX_PROGRAM_BURST_LEN_16 = ((uint32_t)0x00100000U),
    ETH_TX_PROGRAM_BURST_LEN_32 = ((uint32_t)0x00200000U)
} EthTxBurLenType;

typedef enum
{
    ETH_RX_PROGRAM_BURST_LEN_1  = ((uint32_t)0x00010000U),
    ETH_RX_PROGRAM_BURST_LEN_2  = ((uint32_t)0x00020000U),
    ETH_RX_PROGRAM_BURST_LEN_4  = ((uint32_t)0x00040000U),
    ETH_RX_PROGRAM_BURST_LEN_8  = ((uint32_t)0x00080000U),
    ETH_RX_PROGRAM_BURST_LEN_16 = ((uint32_t)0x00100000U),
    ETH_RX_PROGRAM_BURST_LEN_32 = ((uint32_t)0x00200000U)
} EthRxBurLenType;

typedef enum
{
    ETH_VLANTAGRXSTRIPPING_NONE    = ((uint32_t)0x00000000U),
    ETH_VLANTAGRXSTRIPPING_IFPASS  = ((uint32_t)0x00200000U),
    ETH_VLANTAGRXSTRIPPING_IFFAILS = ((uint32_t)0x00400000U),
    ETH_VLANTAGRXSTRIPPING_ALWAYS  = ((uint32_t)0x00600000U)
} EthRxVlanStripType;

typedef enum
{
    ETH_VLANTYPECHECK_CVLAN   = ((uint32_t)0x00000000U),
    ETH_VLANTYPECHECK_SVLAN   = ((uint32_t)0x000C0000U),
    ETH_VLANTYPECHECK_DISABLE = ((uint32_t)0x00100000U)
} EthVlanCheckType;




/** ETH initialize configuration structure definition **/
typedef struct
{
    /******************* MAC Basic Configuration *******************/
    EthTxPreLenType    TxPreambleLen;             /* Configs the Preamble Length for Transmit packets */

    uint32_t           DeferralCheck;             /* Enables or Disable Deferral check function in the half-duplex mode */

    EthBacOffLimType   BackOffLimit;              /* Selects the Back-Off limit value in the half-duplex mode */

    uint32_t           DisTxRetry;                /* Enables or Disable MAC retry transmission, when a collision occurs in Half Duplex mode */

    uint32_t           DisCSDuringTransmit;       /* Enables or Disable Carrier Sense During Transmission in the half-duplex mode */

    uint32_t           DisRxOwn;                  /* Enables or Disable Receive Own in Half Duplex mode */

    uint32_t           CSBeforeTransmit;          /* Enables or Disable Carrier Sense Before Transmission in the full-duplex mode */

    uint32_t           Loopback;                  /* Enables or Disable Loopback Mode */

    EthDuplexType      Duplex;                    /* Selects the Half-duplex or Full-duplex mode */

    EthSpeedType       SpeedSelect;               /* Selects the speed mode: 10Mbps or 100Mbps or 1000Mbps, note ETH2 only 10Mbps or 100Mbps */

    uint32_t           JumboPacket;               /* Enables or Disable Jumbo Packet */

    uint32_t           DisTxJabber;               /* Enables or Disable Jabber timer on Tx path */

    uint32_t           PacketBurst;               /* Enables or Disable Packet Burst in GMII half-duplex mode, ETH2 is not supported */

    uint32_t           DisRxWatchdog;             /* Enables or Disable Watchdog timer on Rx path */

    uint32_t           AutoPadCRCStrip;           /* Enables or Disable Automatic Pad or CRC Stripping function */

    uint32_t           CRCStripTypePacket;        /* Enables or Disable CRC stripping for Type packets function */

    uint32_t           Support2KPacket;           /* Enables or Disable IEEE 802.3as Support for 2K Packets function */

    uint32_t           GiantPacketSizeLimitCtrl;  /* Enables or Disable Giant Packet Size Limit Control */

    EthIntPktGapType   InterPacketGapVal;         /* Configs the minimum Inter-Packet Gap between packets during transmission */

    uint32_t           ChecksumOffload;           /* Enables or Disable Checksum Offload function */

    EthSrcAddrCtrlType SrcAddrCtrl;               /* Selects the Source Address Insertion or Replacement Control */

    uint32_t           ARPOffload;                /* Enables or Disable ARP Offload function */

    /****************** MAC Extended Configuration ******************/
    uint32_t           GiantPacketSizeLimit;      /* Configs Giant Packet Size Limit value, If the received packet size is greater than the \
                                                   value programmed in this field in units of bytes, the MAC declares the received packet \
                                                   as Giant packet. This value must be ≥ 1518 bytes */

    uint32_t           DisRxPacketCRCCheck;       /* Enables or Disable CRC Checking for Rx Packets */

    uint32_t           SPDetect;                  /* Enables or Disable Slow Protocol Detection */

    uint32_t           USPPacketDetect;           /* Enables or Disable Unicast Slow Protocol Packet Detect */

    uint32_t           ExtInterPacketGap;         /* Enables or Disable Extended Inter-Packet Gap */

    uint32_t           ExtInterPacketGapVal;      /* Configs the minimum Inter-Packet Gap between packets during transmission */

    uint32_t           DropARPPacket;             /* Enables or Disable ARP Packet Drop function if IP Address Mismatch */

    /**************** MAC Packet Filter Configuration ***************/
    uint32_t           Promiscuous;               /* Enables or Disable Promiscuous Mode */

    uint32_t           HashUnicast;               /* Enables or Disable Hash Unicast Filtering Mode */

    uint32_t           HashMulticast;             /* Enables or Disable Hash Multicast Filtering Mode */

    uint32_t           DAInverseFiltering;        /* Enables or Disable DA Inverse Filtering Mode */

    uint32_t           PassAllMulticast;          /* Enables or Disable Pass All Multicast Mode */

    uint32_t           DisBroadcastPackets;       /* Enables or Disable Broadcast Packets */

    EthCtrlPktType     PassControlPackets;        /* Configs the forwarding of all control packets */

    uint32_t           SAInverseFiltering;        /* Enables or Disable SA Inverse Filtering Mode */

    uint32_t           SAFilter;                  /* Enables or Disable SA Filter */

    uint32_t           HashOrPerfectFilter;       /* Enables or Disable Hash or Perfect Filter */

    uint32_t           VLANTagFilter;             /* Enables or Disable VLAN Tag Filter */

    uint32_t           Layer3Layer4Filter;        /* Enables or Disable Layer 3 and Layer 4 Filter */

    uint32_t           DropNonTcpUdpPackets;      /* Enables or Disable Drop Non-TCP/UDP over IP Packets */

    uint32_t           ReceiveAll;                /* Enables or Disable Receive All mode */

    /************** MAC Watchdog Timeout Configuration **************/
    EthWdgTimOutType   WatchdogTimeout;           /* Configs watchdog timeout for a received packet, if the length of a received packet  \
                                                   exceeds the value of this field, such packet is terminated and declared as an error \
                                                   packet */
    
    uint32_t           ProgramWatchdog;           /* Enables or Disable Programmable Watchdog function */

    /**************** MAC Flow Control Configuration ****************/
    uint32_t           TxFlowControl;             /* Enables or Disable Transmit Flow Control function */

    EthPauLowThdType   PauseLowThreshold;         /* Configs the threshold of the Pause timer */

    uint32_t           DisZeroQuantaPause;        /* Enables or Disable Zero-Quanta Pause function */

    uint32_t           PauseTime;                 /* Configs the value to be used in the Pause Time field in the Tx control packet */

    uint32_t           RxFlowControl;             /* Enables or Disable Receive Flow Control function */

    uint32_t           UPPacketDetect;            /* Enables or Disable Unicast Pause Packet Detect */

    /*********** MAC Transaction Layer (MTL) Configuration **********/
    EthTxQOpeType      TxQueueOperateMode;        /* Config Tx Store and Forward Mode or Threshold Mode and threshold level */

    EthRxQOpeType      RxQueueOperateMode;        /* Configs Rx Store and Forward Mode or Threshold Mode and threshold level */

    uint32_t           ForwardUSGoodPacket;       /* Enables or Disable Forward Undersized Good Packets function */

    uint32_t           ForwardErrorPacket;        /* Enables or Disable Forward Error Packets function */

    uint32_t           DisDropTCPIPCSErrorPacket; /* Enables or Disable Dropping of TCP/IP Checksum Error Packets */

    /****************** DMA Bus Mode Configuration ******************/
    EthTxRxArbType     TxRxArbitration;           /* Configs the arbitration scheme between the Tx and Rx paths of DMA */

    uint32_t           DescriptorCache;           /* Enables or Disable Descriptor Cache function */

    /*************** DMA System Bus Mode Configuration **************/
    EthBurstType       BurstMode;                 /* Configs the AHB Master interface burst transfers */

    uint32_t           AddrAlignedBeats;          /* Enables or Disable AHB Master interface address-aligned burst transfers on Read   \
                                                   and Write channels */

    uint32_t           RebuildINCRxBurst;         /* Enables or Disable AHB Master to rebuild the pending beats of any initiated burst \
                                                   transfer with INCRx and SINGLE transfers */

    /******************* DMA Channel Configuration ******************/
    uint32_t           MaxSegmentSize;            /* Configs the maximum segment size that should be used while segmenting the packet  \
                                                   This parameter can be a value from 0x40 to 0x3FFF */

    uint32_t           PBLx8mode;                 /* Enables or Disable PBL multiplication by eight */

    EthDesSkiLenType   DescriptorSkipLen;         /* Configs the Word number to skip between two unchained descriptors */

    /************** DMA Channel Transmit Configuration **************/
    uint32_t           OperateSecondPacket;       /* Enables or Disable Operate on Second Packet mode, it instructs the DMA to process  \
                                                   the second packet of the Transmit data even before the status for the first packet \
                                                   is obtained */

    uint32_t           TCPSegment;                /* Enables or Disable TCP Segmentation function */

    EthTxBurLenType    TxBurstLength;             /* Configs the maximum number of beats to be transferred in one DMA block data transfer */

    uint32_t           EarlyTxInterruptCtrl;      /* Enables or Disable Early Transmit Interrupt function */

    /*************** DMA Channel Receive Configuration ***************/
    EthRxBurLenType    RxBurstLength;             /* Configs the maximum number of beats to be transferred in one DMA block data transfer */

    uint32_t           EarlyRxInterruptCtrl;      /* Enables or Disable Early Receive Interrupt function */

    uint32_t           RxPacketFlush;             /* Enables or Disable Rx Packet Flush function */

} ETH_InitType;

/** ETH Rx VLAN tag initialize configuration structure definition **/
typedef struct
{
    uint32_t           VLANTagHashTableMatch;   /* Enables or Disables VLAN Tag Hash Table Match */

    uint32_t           VLANTagInStatus;         /* Enables or Disables VLAN Tag in Rx status */

    EthRxVlanStripType StripVLANTag;            /* Sets the VLAN Tag Stripping on Receive */

    EthVlanCheckType   VLANTypeCheck;           /* Enables or Disables VLAN Type Check */

    uint32_t           VLANTagInverceMatch;     /* Enables or disables VLAN Tag Inverse Match */

    uint32_t           VLANTagComparison12Bit;  /* Enables or disables 12-Bit VLAN Tag Comparison */

} ETH_RxVLANTagInitType;

/** ETH DMA Descriptor structure definition **/
typedef struct
{
    __IO uint32_t DESC0;
    __IO uint32_t DESC1;
    __IO uint32_t DESC2;
    __IO uint32_t DESC3;
    __IO uint32_t Buf1Addr; /* Used to backup rx buffer 1 address */
    __IO uint32_t Buf2Addr; /* Used to backup rx buffer 2 address */
} ETH_DMADescType;

/** ETH DMA Tx Descriptor List structure definition **/
typedef struct
{
    uint32_t TxDesc[ETH_TX_DESC_NUMBER]; /* Tx DMA descriptors addresses */

    uint32_t CurTxDesc;                  /* Current Tx descriptor index for packet transmission */
} ETH_TxDescListType;

/** ETH DMA Rx Descriptor List structure definition **/
typedef struct
{
    uint32_t RxDesc[ETH_RX_DESC_NUMBER]; /* Rx DMA descriptors addresses */

    uint32_t CurRxDesc;                  /* Current Rx descriptor, ready for next reception */

    uint32_t FirstAppDesc;               /* First descriptor of last received packet */

    uint32_t AppDescNbr;                 /* Number of descriptors of last received packet */

    uint32_t AppContextDesc;             /* If 1 a context descriptor is present in last received packet
                                            If 0 no context descriptor is present in last received packet */

    uint32_t ItMode;                     /* If 1, DMA will generate the Rx complete interrupt
                                            If 0, DMA will not generate the Rx complete interrupt */ 
} ETH_RxDescListType;

/** ETH Buffers List structure definition **/
typedef struct __ETH_BufferType
{
    uint8_t* pBuf;                  /* buffer address */

    uint32_t Len;                   /* buffer length */

    struct __ETH_BufferType* pNext; /* Pointer to the next buffer in the list */
} ETH_BufferType;

/** ETH Transmit Packet structure definition **/
typedef struct
{
    uint32_t        Attributes;   /* Tx packet HW features capabilities
                                     This parameter can be a combination of EthTxPackAttrType */
    
    ETH_BufferType* pTxBuffer;    /* Tx buffers pointers */

    uint32_t        Length;       /* Total packet length */

    uint32_t        SAInsertCtrl; /* Source address insertion control */

    uint32_t        CRCPadCtrl;   /* Specifies the CRC and Pad insertion and replacement control */

    uint32_t        ChecksumCtrl; /* Specifies the checksum insertion control */

    uint32_t        VlanTag;      /* Sets VLAN Tag only when VLAN is enabled */
} ETH_TxPacketType;

/** ETH Received Packet structure definition **/
typedef struct
{
    uint32_t DescriptorCnt;   /* Number of Rx Descriptors */

    uint32_t VlanTag;         /* Vlan Tag value */

    uint32_t Checksum;        /* Rx Checksum status */

    uint32_t HeaderType;      /* IP header type */

    uint32_t PayloadType;     /* Payload type */

    uint32_t MACFilterStatus; /* MAC filter status */

    uint32_t ErrorCode;       /* Rx error code */
} ETH_RxPacketType;

/** Function prototype for phy get link status functions.
*\*\param  addr PHY port address
*\*\param  reg PHY register address
*\*\return Acquired PHY link state value containing speed core duplex mode
**/
typedef uint16_t (*phyGetLinkStatus_fn)(uint16_t addr, uint16_t reg);

/** ETH External PHY information definition **/
typedef struct
{
    uint16_t phyAddr;       /* PHY address, value 0~31 */

    uint16_t bcRegAddr;     /* PHY Basic Control Register */

    uint16_t bsRegAddr;     /* PHY Basic Status Register */

    uint16_t sdRegAddr;     /* Address of the status register indicating speed and duplex mode in auto-negotiation mode */

    uint16_t phyReset;      /* PHY Reset */

    // uint16_t phyLoopback;   /* Select PHY's loop-back mode */

    uint16_t phyMode;       /* Set PHY's duplex and speed mode */

    uint16_t phyAutoNeg;    /* Enable PHY's auto-negotiation function */

    uint16_t phyAutoNegOK;  /* Auto-negotiation completed */

    uint16_t phyLinkOK;     /* Valid link established */

    uint16_t phyDuplexMask; /* PHY Duplex mask */

    uint16_t phySpeedMask;  /* PHY Speed mask */
    
    phyGetLinkStatus_fn phyGetLinkStatus;
} ETH_PHYInfoType;

/** ETH module information definition **/
typedef struct
{
    EthMediaInterfaceType MediaInterface; /* Selects the interface where the MAC is connected to the PHY */

    FunctionalStatus      AutoNegCmd;     /* Enables or Disables the AutoNegotiation mode for the external PHY */

    FunctionalStatus      PPSOutCmd;      /* Enables or Disables the PPS out operations */

    FunctionalStatus      PMTCmd;         /* Enables or Disables the PMT (MAC Magic Packet/Remote Wake-Up Packet) */
    
    FunctionalStatus      LPICmd;         /* Enables or Disables the LPI (Low-power interface, EEE mode) */

    EthMdcClkType         MDCClockMode;   /* Selects the MDC clock range from 1.0M to 2.5M or greater than 2.5M */

    uint32_t              CSRClkDiv;      /* Provides the CSR clock division factor used to calculate the MDC clock.
                                             Available only when the MDC clock range is greater than 2.5M */

    uint8_t*              pMACAddr;       /* MAC Address of used Hardware: must be pointer on an array of 6 bytes */

    ETH_DMADescType*      pTxDesc;        /* Provides the address of the first DMA Tx descriptor in the list */

    ETH_DMADescType*      pRxDesc;        /* Provides the address of the first DMA Rx descriptor in the list */

    uint32_t              RxBuffLen;      /* Provides the length of Rx buffers size */

    ETH_TxDescListType    TxDescList;     /* Holds all Tx descriptors list addresses and current descriptor index */

    ETH_RxDescListType    RxDescList;     /* Holds all Rx descriptors list addresses and current descriptor index */

    ETH_PHYInfoType       PHYInfo;        /* Provides information related to PHY initialization and some status information */

} ETH_InfoType;


/*** ETH Structure Definition End ***/


/*** ETH Macro Definition Start ***/

/** ETH register bit field mask definition **/
#define ETH_REG_BIT_FIELD_MASK ((uint32_t)0x00000000U)

/** ETH Link speed duplex definition **/
#define ETH_LINK_10FULL        ((uint32_t)0x00000001U)
#define ETH_LINK_10HALF        ((uint32_t)0x00000002U)
#define ETH_LINK_100FULL       ((uint32_t)0x00000004U)
#define ETH_LINK_100HALF       ((uint32_t)0x00000008U)
#define ETH_LINK_1000FULL      ((uint32_t)0x00000010U)
#define ETH_LINK_1000HALF      ((uint32_t)0x00000020U)

/** ETH MAC Interrupt flag definition **/
#define ETH_MAC_INT_FLAG_PHY   ((uint32_t)(ETH_MACINTSTS_PHYIS))
#define ETH_MAC_INT_FLAG_PMT   ((uint32_t)(ETH_MACINTSTS_PMTIS))
#define ETH_MAC_INT_FLAG_MMCRX ((uint32_t)(ETH_MACINTSTS_MMCIS \
                                         | ETH_MACINTSTS_MMCRXIS))
#define ETH_MAC_INT_FLAG_MMCTX ((uint32_t)(ETH_MACINTSTS_MMCIS \
                                         | ETH_MACINTSTS_MMCTXIS))
#define ETH_MAC_INT_FLAG_TS    ((uint32_t)(ETH_MACINTSTS_TSIS))
#define ETH_MAC_INT_FLAG_TX    ((uint32_t)(ETH_MACINTSTS_TXSTSIS))
#define ETH_MAC_INT_FLAG_RX    ((uint32_t)(ETH_MACINTSTS_RXSTSIS))
#define ETH_MAC_INT_FLAG_MDIO  ((uint32_t)(ETH_MACINTSTS_MDIOIS))

/** ETH MAC Interrupt definition **/
#define ETH_MAC_INT_PHY   ((uint32_t)ETH_MACINTEN_PHYIE)
#define ETH_MAC_INT_PMT   ((uint32_t)ETH_MACINTEN_PMTIE)
#define ETH_MAC_INT_TS    ((uint32_t)ETH_MACINTEN_TSIE)
#define ETH_MAC_INT_TX    ((uint32_t)ETH_MACINTEN_TXSTSIE)
#define ETH_MAC_INT_RX    ((uint32_t)ETH_MACINTEN_RXSTSIE)
#define ETH_MAC_INT_MDIO  ((uint32_t)ETH_MACINTEN_MDIOIE)

/** ETH MAC TX-RX flag definition **/
#define ETH_MACTX_FLAG_TJT   ((uint32_t)ETH_MACRXTXSTS_TJT)
#define ETH_MACTX_FLAG_NCARR ((uint32_t)ETH_MACRXTXSTS_NCARR)
#define ETH_MACTX_FLAG_LCARR ((uint32_t)ETH_MACRXTXSTS_LCARR)
#define ETH_MACTX_FLAG_EXDEF ((uint32_t)ETH_MACRXTXSTS_EXDEF)
#define ETH_MACTX_FLAG_LCOL  ((uint32_t)ETH_MACRXTXSTS_LCOL)
#define ETH_MACTX_FLAG_EXCOL ((uint32_t)ETH_MACRXTXSTS_EXCOL)
#define ETH_MACRX_FLAG_RWT   ((uint32_t)ETH_MACRXTXSTS_RWT)

/** ETH PMT flag definition **/
#define ETH_PMT_FLAG_WUPFRPR ((uint32_t)ETH_MACPMTCTRLSTS_RWKFILTRST) /* Remote Wake-Up Packet Filter Register Pointer Reset */
#define ETH_PMT_FLAG_WUPR    ((uint32_t)ETH_MACPMTCTRLSTS_RWKPRCVD)   /* Remote Wake-Up Packet Received */
#define ETH_PMT_FLAG_MPR     ((uint32_t)ETH_MACPMTCTRLSTS_MGKPRCVD)   /* Magic Packet Received */

/** ETH MDC clock frequency definition **/
#define ETH_MACMDIOADDR_CR_MASK   ((uint32_t)(ETH_MACMDIOADDR_CR))
#define ETH_MDCNCLK_CRSCLK_DIV42  ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            & ETH_MACMDIOADDR_CR_1 \
                                            & ETH_MACMDIOADDR_CR_2 \
                                            & ETH_MACMDIOADDR_CR_3))
#define ETH_MDCNCLK_CRSCLK_DIV62  ((uint32_t)(ETH_MACMDIOADDR_CR_0))
#define ETH_MDCNCLK_CRSCLK_DIV16  ((uint32_t)(ETH_MACMDIOADDR_CR_1))
#define ETH_MDCNCLK_CRSCLK_DIV26  ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            | ETH_MACMDIOADDR_CR_1))
#define ETH_MDCNCLK_CRSCLK_DIV102 ((uint32_t)(ETH_MACMDIOADDR_CR_2))
#define ETH_MDCNCLK_CRSCLK_DIV124 ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            | ETH_MACMDIOADDR_CR_2))
#define ETH_MDCNCLK_CRSCLK_DIV204 ((uint32_t)(ETH_MACMDIOADDR_CR_1 \
                                            | ETH_MACMDIOADDR_CR_2))
#define ETH_MDCNCLK_CRSCLK_DIV324 ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            | ETH_MACMDIOADDR_CR_1 \
                                            | ETH_MACMDIOADDR_CR_2))

#define ETH_MDCFCLK_CRSCLK_DIV4   ((uint32_t)(ETH_MACMDIOADDR_CR_3))
#define ETH_MDCFCLK_CRSCLK_DIV6   ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            | ETH_MACMDIOADDR_CR_3))
#define ETH_MDCFCLK_CRSCLK_DIV8   ((uint32_t)(ETH_MACMDIOADDR_CR_1 \
                                            | ETH_MACMDIOADDR_CR_3))
#define ETH_MDCFCLK_CRSCLK_DIV10  ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            | ETH_MACMDIOADDR_CR_1 \
                                            | ETH_MACMDIOADDR_CR_3))
#define ETH_MDCFCLK_CRSCLK_DIV12  ((uint32_t)(ETH_MACMDIOADDR_CR_2 \
                                            | ETH_MACMDIOADDR_CR_3))
#define ETH_MDCFCLK_CRSCLK_DIV14  ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            | ETH_MACMDIOADDR_CR_2 \
                                            | ETH_MACMDIOADDR_CR_3))
#define ETH_MDCFCLK_CRSCLK_DIV16  ((uint32_t)(ETH_MACMDIOADDR_CR_1 \
                                            | ETH_MACMDIOADDR_CR_2 \
                                            | ETH_MACMDIOADDR_CR_3))
#define ETH_MDCFCLK_CRSCLK_DIV18  ((uint32_t)(ETH_MACMDIOADDR_CR_0 \
                                            | ETH_MACMDIOADDR_CR_1 \
                                            | ETH_MACMDIOADDR_CR_2 \
                                            | ETH_MACMDIOADDR_CR_3))

/** ETH MAC Address Filter Mask Bytes definition **/
#define ETH_MACADDR_MASK_MBC   ((uint32_t)ETH_MACADDR1H_MBC)
#define ETH_MACADDR_MASK_BYTE1 ((uint32_t)ETH_MACADDR1H_MBC_0) /* Mask MAC Address low reg bits [7:0] */
#define ETH_MACADDR_MASK_BYTE2 ((uint32_t)ETH_MACADDR1H_MBC_1) /* Mask MAC Address low reg bits [15:8] */
#define ETH_MACADDR_MASK_BYTE3 ((uint32_t)ETH_MACADDR1H_MBC_2) /* Mask MAC Address low reg bits [23:16] */
#define ETH_MACADDR_MASK_BYTE4 ((uint32_t)ETH_MACADDR1H_MBC_3) /* Mask MAC Address low reg bits [31:24] */
#define ETH_MACADDR_MASK_BYTE5 ((uint32_t)ETH_MACADDR1H_MBC_4) /* Mask MAC Address high reg bits [7:0] */
#define ETH_MACADDR_MASK_BYTE6 ((uint32_t)ETH_MACADDR1H_MBC_5) /* Mask MAC Address high reg bits [15:8] */

/** ETH MAC Timestamp update method definition **/
#define ETH_MACTS_FINE_UPDATE   ((uint32_t)ETH_MACTSCTRL_TSCFUPDT) /* Fine Update method */
#define ETH_MACTS_COARSE_UPDATE ((uint32_t)ETH_REG_BIT_FIELD_MASK) /* Coarse Update method */

/** ETH MAC PTP Packet Type definition **/
#define ETH_MACPTP_TYPE_VERSION2 ((uint32_t)ETH_MACTSCTRL_TSVER2ENA)
#define ETH_MACPTP_TYPE_ETHERNET ((uint32_t)ETH_MACTSCTRL_TSIPENA)
#define ETH_MACPTP_TYPE_IPV6UDP  ((uint32_t)ETH_MACTSCTRL_TSIPV6ENA)
#define ETH_MACPTP_TYPE_IPV4UDP  ((uint32_t)ETH_MACTSCTRL_TSIPV4ENA)

/** ETH MAC TimeStamp update calculation mode definition **/
#define ETH_MACTS_CALMODE_SUB ((uint32_t)ETH_MACSYSTNSUP_ADDSUB) /* Subtract Time */
#define ETH_MACTS_CALMODE_ADD ((uint32_t)ETH_REG_BIT_FIELD_MASK) /* Add Time */

/** ETH MAC PPS Frequency Control definition **/
#define ETH_MACPPS_FREQCTRL_B2D1         ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0)) /* Binary rollover is 2 Hz, Digital rollover is 1 Hz */
#define ETH_MACPPS_FREQCTRL_B4D2         ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_1)) /* Binary rollover is 4 Hz, Digital rollover is 2 Hz */
#define ETH_MACPPS_FREQCTRL_B8D4         ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_1)) /* Binary rollover is 8 Hz, Digital rollover is 4 Hz */
#define ETH_MACPPS_FREQCTRL_B16D8        ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_2)) /* Binary rollover is 16 Hz, Digital rollover is 8 Hz */
#define ETH_MACPPS_FREQCTRL_B32D16       ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_2)) /* Binary rollover is 32 Hz, Digital rollover is 16 Hz */
#define ETH_MACPPS_FREQCTRL_B64D32       ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_1 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_2)) /* Binary rollover is 64 Hz, Digital rollover is 32 Hz */
#define ETH_MACPPS_FREQCTRL_B128D64      ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_1 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_2)) /* Binary rollover is 128 Hz, Digital rollover is 64 Hz */
#define ETH_MACPPS_FREQCTRL_B256D128     ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 256 Hz, Digital rollover is 128 Hz */
#define ETH_MACPPS_FREQCTRL_B512D256     ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 512 Hz, Digital rollover is 256 Hz */
#define ETH_MACPPS_FREQCTRL_B1024D512    ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_1 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 1024 Hz, Digital rollover is 512 Hz */
#define ETH_MACPPS_FREQCTRL_B2048D1024   ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_1 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 2048 Hz, Digital rollover is 1024 Hz */
#define ETH_MACPPS_FREQCTRL_B4096D2048   ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_2 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 4096 Hz, Digital rollover is 2048 Hz */
#define ETH_MACPPS_FREQCTRL_B8192D4096   ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_2 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 8192 Hz, Digital rollover is 4096 Hz */
#define ETH_MACPPS_FREQCTRL_B16384D8192  ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_1 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_2 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 16384 Hz, Digital rollover is 8192 Hz */
#define ETH_MACPPS_FREQCTRL_B32768D16384 ((uint32_t)(ETH_MACPPSCTRL_PPSCTRL_0 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_1 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_2 \
                                                   | ETH_MACPPSCTRL_PPSCTRL_3)) /* Binary rollover is 32768 Hz, Digital rollover is 16384 Hz */


/** ETH MMC RX Interrupt flag definition **/
#define ETH_MMCRX_INT_FLAG_BCGPIS    ((uint32_t)ETH_MMCRXINT_RXBCGPIS)
#define ETH_MMCRX_INT_FLAG_MCGPIS    ((uint32_t)ETH_MMCRXINT_RXMCGPIS)
#define ETH_MMCRX_INT_FLAG_CRCERPIS  ((uint32_t)ETH_MMCRXINT_RXCRCERPIS)
#define ETH_MMCRX_INT_FLAG_ALGNERPIS ((uint32_t)ETH_MMCRXINT_RXALGNERPIS)
#define ETH_MMCRX_INT_FLAG_UCGPIS    ((uint32_t)ETH_MMCRXINT_RXUCGPIS)

/** ETH MMC TX Interrupt flag definition **/
#define ETH_MMCTX_INT_FLAG_SCOLGPIS ((uint32_t)ETH_MMCTXINT_TXSCOLGPIS)
#define ETH_MMCTX_INT_FLAG_MCOLGPIS ((uint32_t)ETH_MMCTXINT_TXMCOLGPIS)
#define ETH_MMCTX_INT_FLAG_GPKTIS   ((uint32_t)ETH_MMCTXINT_TXGPKTIS)

/** ETH MMC RX Interrupt definition **/
#define ETH_MMCRX_INT_BCGPIM    ((uint32_t)ETH_MMCRXINTMSK_RXBCGPIM)
#define ETH_MMCRX_INT_MCGPIM    ((uint32_t)ETH_MMCRXINTMSK_RXMCGPIM)
#define ETH_MMCRX_INT_CRCERPIM  ((uint32_t)ETH_MMCRXINTMSK_RXCRCERPIM)
#define ETH_MMCRX_INT_ALGNERPIM ((uint32_t)ETH_MMCRXINTMSK_RXALGNERPIM)
#define ETH_MMCRX_INT_UCGPIM    ((uint32_t)ETH_MMCRXINTMSK_RXUCGPIM)

/** ETH MMC TX Interrupt definition **/
#define ETH_MMCTX_INT_SCOLGPIM ((uint32_t)ETH_MMCTXINTMSK_TXSCOLGPIM)
#define ETH_MMCTX_INT_MCOLGPIM ((uint32_t)ETH_MMCTXINTMSK_TXMCOLGPIM)
#define ETH_MMCTX_INT_GPKTIM   ((uint32_t)ETH_MMCTXINTMSK_TXGPKTIM)

/** ETH MAC TimeStamp flag definition **/
#define ETH_MACTS_FLAG_SOVF     ((uint32_t)ETH_MACTSSTS_TSSOVF)     /* Seconds Overflow flag */
#define ETH_MACTS_FLAG_TARGT0   ((uint32_t)ETH_MACTSSTS_TSTARGT0)   /* Target Time Reached flag */
#define ETH_MACTS_FLAG_TRGTERR0 ((uint32_t)ETH_MACTSSTS_TSTRGTERR0) /* Target Time Error flag */
#define ETH_MACTS_FLAG_TXTSSIS  ((uint32_t)ETH_MACTSSTS_TXTSSIS)    /* Tx Timestamp Status Interrupt Status flag */



/** ETH MTL Interrupt flag definition **/
#define ETH_MTL_INT_FLAG_Q0IS ((uint32_t)ETH_MTLINTSTS_Q0IS)

/** ETH MTL Queue Interrupt definition **/
#define ETH_MTLTXQUEUE_INT_UIE   ((uint32_t)ETH_MTLQINTCTRLSTS_TXUIE) /* Transmit Queue Underflow Interrupt */
#define ETH_MTLRXQUEUE_INT_OIE   ((uint32_t)ETH_MTLQINTCTRLSTS_RXOIE) /* Receive Queue Overflow Interrupt */

/** ETH MTL Queue Interrupt flag definition **/
#define ETH_MTLTXQUEUE_INT_FLAG_UNFIS ((uint32_t)ETH_MTLQINTCTRLSTS_TXUNFIS) /* Transmit Queue Underflow Interrupt Flag */
#define ETH_MTLRXQUEUE_INT_FLAG_OVFIS ((uint32_t)ETH_MTLQINTCTRLSTS_RXOVFIS) /* Receive Queue Overflow Interrupt Flag */

/** ETH MTL Counter flag definition **/
#define ETH_MTLCOUNTER_FLAG_UFCNTOVF  ((uint32_t)ETH_MTLTXQUDF_UFCNTOVF)      /* Underflow Packet Counter Overflow Flag */
#define ETH_MTLCOUNTER_FLAG_OVFCNTOVF ((uint32_t)ETH_MTLRXQMPOFCNT_OVFCNTOVF) /* Overflow Packet Counter Overflow Flag */
#define ETH_MTLCOUNTER_FLAG_MISCNTOVF ((uint32_t)ETH_MTLRXQMPOFCNT_MISCNTOVF) /* Missed Packet Counter Overflow Flag */

/** ETH MTL Queue Status definition **/
#define ETH_TRCSTS_MASK         ((uint32_t)(ETH_MTLTXQDBG_TRCSTS))
#define ETH_MTLTXQSTS_IDLE      ((uint32_t)(ETH_MTLTXQDBG_TRCSTS_0 \
                                          & ETH_MTLTXQDBG_TRCSTS_1))
#define ETH_MTLTXQSTS_READ      ((uint32_t)(ETH_MTLTXQDBG_TRCSTS_0))
#define ETH_MTLTXQSTS_WAIT      ((uint32_t)(ETH_MTLTXQDBG_TRCSTS_1))
#define ETH_MTLTXQSTS_FLUSH     ((uint32_t)(ETH_MTLTXQDBG_TRCSTS_0 \
                                          | ETH_MTLTXQDBG_TRCSTS_1))
#define ETH_MTLTXQSTS_NOT_EMPTY ((uint32_t)(ETH_MTLTXQDBG_TXQSTS))

#define ETH_RRCSTS_MASK         ((uint32_t)(ETH_MTLRXQDBG_RRCSTS))
#define ETH_MTLRXQSTS_IDLE      ((uint32_t)(ETH_MTLRXQDBG_RRCSTS_0 \
                                          & ETH_MTLRXQDBG_RRCSTS_1))
#define ETH_MTLRXQSTS_READ_DATA ((uint32_t)(ETH_MTLRXQDBG_RRCSTS_0)) /* Reading packet data */
#define ETH_MTLRXQSTS_READ_STS  ((uint32_t)(ETH_MTLRXQDBG_RRCSTS_1)) /* Reading packet status (or timestamp) */
#define ETH_MTLRXQSTS_FLUSH     ((uint32_t)(ETH_MTLRXQDBG_RRCSTS_0 \
                                          | ETH_MTLRXQDBG_RRCSTS_1)) /* Flushing the packet data and status */

#define ETH_RXQSTS_MASK         ((uint32_t)(ETH_MTLRXQDBG_RXQSTS))
#define ETH_MTLRXQSTS_EMPTY     ((uint32_t)(ETH_MTLRXQDBG_RXQSTS_0 \
                                          & ETH_MTLRXQDBG_RXQSTS_1)) /* Rx Queue empty */
#define ETH_MTLRXQSTS_BLW_THR   ((uint32_t)(ETH_MTLRXQDBG_RXQSTS_0)) /* Rx Queue fill-level below flow-control deactivate threshold */
#define ETH_MTLRXQSTS_ABV_THR   ((uint32_t)(ETH_MTLRXQDBG_RXQSTS_1)) /* Rx Queue fill-level above flow-control activate threshold */
#define ETH_MTLRXQSTS_FULL      ((uint32_t)(ETH_MTLRXQDBG_RXQSTS_0 \
                                          | ETH_MTLRXQDBG_RXQSTS_1)) /* Rx Queue full */

#define ETH_MTLRXQSTS_PACK_NBR  ((uint32_t)(ETH_MTLRXQDBG_PRXQ))

/** ETH DMA Interrupt flag definition **/
#define ETH_DMA_INT_FLAG_DMACH0 ((uint32_t)ETH_DMAINTSTS_DC0IS)
#define ETH_DMA_INT_FLAG_MTL    ((uint32_t)ETH_DMAINTSTS_MTLIS)
#define ETH_DMA_INT_FLAG_MAC    ((uint32_t)ETH_DMAINTSTS_MACIS)

/** ETH DMA channel 0 transmit process flag definition **/
#define ETH_DMACH0_TXPRO_FLAG_STOP     ((uint32_t)(ETH_DMADBGSTS_TPS0_0 \
                                                 & ETH_DMADBGSTS_TPS0_1 \
                                                 & ETH_DMADBGSTS_TPS0_2 \
                                                 & ETH_DMADBGSTS_TPS0_3)) /* Stopped (Reset or Stop Transmit Command issued) */
#define ETH_DMACH0_TXPRO_FLAG_RUN_FTTD ((uint32_t)(ETH_DMADBGSTS_TPS0_0)) /* Running (Fetching Tx Transfer Descriptor) */
#define ETH_DMACH0_TXPRO_FLAG_RUN_WS   ((uint32_t)(ETH_DMADBGSTS_TPS0_1)) /* Running (Waiting for status) */
#define ETH_DMACH0_TXPRO_FLAG_RUN_RDS  ((uint32_t)(ETH_DMADBGSTS_TPS0_0 \
                                                 | ETH_DMADBGSTS_TPS0_1)) /* Running (Reading Data from system memory buffer and queuing it to the Tx buffer (Tx FIFO)) */
#define ETH_DMACH0_TXPRO_FLAG_TSTMP_WS ((uint32_t)(ETH_DMADBGSTS_TPS0_2)) /* Timestamp write status */
#define ETH_DMACH0_TXPRO_FLAG_SUSPND   ((uint32_t)(ETH_DMADBGSTS_TPS0_1 \
                                                 | ETH_DMADBGSTS_TPS0_2)) /* Suspended (Tx Descriptor Unavailable or Tx Buffer Underflow) */
#define ETH_DMACH0_TXPRO_FLAG_RUN_CTD  ((uint32_t)(ETH_DMADBGSTS_TPS0_0 \
                                                 | ETH_DMADBGSTS_TPS0_1 \
                                                 | ETH_DMADBGSTS_TPS0_2)) /* Running (Closing Tx Descriptor) */

/** ETH DMA channel 0 receive process flag definition **/
#define ETH_DMACH0_RXPRO_FLAG_STOP     ((uint32_t)(ETH_DMADBGSTS_RPS0_0 \
                                                 & ETH_DMADBGSTS_RPS0_1 \
                                                 & ETH_DMADBGSTS_RPS0_2 \
                                                 & ETH_DMADBGSTS_RPS0_3)) /* Stopped (Reset or Stop Receive Command issued) */
#define ETH_DMACH0_RXPRO_FLAG_RUN_FTTD ((uint32_t)(ETH_DMADBGSTS_RPS0_0)) /* Running (Fetching Rx Transfer Descriptor) */
#define ETH_DMACH0_RXPRO_FLAG_RUN_WRP  ((uint32_t)(ETH_DMADBGSTS_RPS0_0 \
                                                 | ETH_DMADBGSTS_RPS0_1)) /* Running (Waiting for Rx packet) */
#define ETH_DMACH0_RXPRO_FLAG_SUSPND   ((uint32_t)(ETH_DMADBGSTS_RPS0_2)) /* Suspended (Rx Descriptor Unavailable) */
#define ETH_DMACH0_RXPRO_FLAG_RUN_CRD  ((uint32_t)(ETH_DMADBGSTS_RPS0_0 \
                                                 | ETH_DMADBGSTS_RPS0_2)) /* Running (Closing the Rx Descriptor) */
#define ETH_DMACH0_RXPRO_FLAG_TSTMP    ((uint32_t)(ETH_DMADBGSTS_RPS0_1 \
                                                 | ETH_DMADBGSTS_RPS0_2)) /* Timestamp write status */
#define ETH_DMACH0_RXPRO_FLAG_RUN_TRP  ((uint32_t)(ETH_DMADBGSTS_RPS0_0 \
                                                 | ETH_DMADBGSTS_RPS0_1 \
                                                 | ETH_DMADBGSTS_RPS0_2)) /* Running (Transferring the received packet data from the Rx buffer to the system memory) */

/** ETH DMA channel 0 Interrupt definition **/
#define ETH_DMACH0_INT_TI  ((uint32_t)ETH_DMACH0INTEN_TIE)
#define ETH_DMACH0_INT_TPS ((uint32_t)ETH_DMACH0INTEN_TXSE)
#define ETH_DMACH0_INT_TBU ((uint32_t)ETH_DMACH0INTEN_TBUE)
#define ETH_DMACH0_INT_RI  ((uint32_t)ETH_DMACH0INTEN_RIE)
#define ETH_DMACH0_INT_RBU ((uint32_t)ETH_DMACH0INTEN_RBUE)
#define ETH_DMACH0_INT_RPS ((uint32_t)ETH_DMACH0INTEN_RSE)
#define ETH_DMACH0_INT_RWT ((uint32_t)ETH_DMACH0INTEN_RWTE)
#define ETH_DMACH0_INT_ETI ((uint32_t)ETH_DMACH0INTEN_ETIE)
#define ETH_DMACH0_INT_ERI ((uint32_t)ETH_DMACH0INTEN_ERIE)
#define ETH_DMACH0_INT_FBE ((uint32_t)ETH_DMACH0INTEN_FBEE)
#define ETH_DMACH0_INT_CDE ((uint32_t)ETH_DMACH0INTEN_CDEE)
#define ETH_DMACH0_INT_AIS ((uint32_t)ETH_DMACH0INTEN_AIE)
#define ETH_DMACH0_INT_NIS ((uint32_t)ETH_DMACH0INTEN_NIE)

/** ETH DMA channel 0 flag definition **/
#define ETH_DMACH0_FLAG_TI  ((uint32_t)ETH_DMACH0STS_TI)
#define ETH_DMACH0_FLAG_TPS ((uint32_t)ETH_DMACH0STS_TPS)
#define ETH_DMACH0_FLAG_TBU ((uint32_t)ETH_DMACH0STS_TBU)
#define ETH_DMACH0_FLAG_RI  ((uint32_t)ETH_DMACH0STS_RI)
#define ETH_DMACH0_FLAG_RBU ((uint32_t)ETH_DMACH0STS_RBU)
#define ETH_DMACH0_FLAG_RPS ((uint32_t)ETH_DMACH0STS_RPS)
#define ETH_DMACH0_FLAG_RWT ((uint32_t)ETH_DMACH0STS_RWT)
#define ETH_DMACH0_FLAG_ETI ((uint32_t)ETH_DMACH0STS_ETI)
#define ETH_DMACH0_FLAG_ERI ((uint32_t)ETH_DMACH0STS_ERI)
#define ETH_DMACH0_FLAG_FBE ((uint32_t)ETH_DMACH0STS_FBE)
#define ETH_DMACH0_FLAG_CDE ((uint32_t)ETH_DMACH0STS_CDE)
#define ETH_DMACH0_FLAG_AIS ((uint32_t)ETH_DMACH0STS_AIS)
#define ETH_DMACH0_FLAG_NIS ((uint32_t)ETH_DMACH0STS_NIS)

/** ETH DMA channel 0 Interrupt flag definition **/
#define ETH_DMACH0_INT_FLAG_TI  ((uint32_t)ETH_DMACH0STS_TI)
#define ETH_DMACH0_INT_FLAG_TPS ((uint32_t)ETH_DMACH0STS_TPS)
#define ETH_DMACH0_INT_FLAG_TBU ((uint32_t)ETH_DMACH0STS_TBU)
#define ETH_DMACH0_INT_FLAG_RI  ((uint32_t)ETH_DMACH0STS_RI)
#define ETH_DMACH0_INT_FLAG_RBU ((uint32_t)ETH_DMACH0STS_RBU)
#define ETH_DMACH0_INT_FLAG_RPS ((uint32_t)ETH_DMACH0STS_RPS)
#define ETH_DMACH0_INT_FLAG_RWT ((uint32_t)ETH_DMACH0STS_RWT)
#define ETH_DMACH0_INT_FLAG_ETI ((uint32_t)ETH_DMACH0STS_ETI)
#define ETH_DMACH0_INT_FLAG_ERI ((uint32_t)ETH_DMACH0STS_ERI)
#define ETH_DMACH0_INT_FLAG_FBE ((uint32_t)ETH_DMACH0STS_FBE)
#define ETH_DMACH0_INT_FLAG_CDE ((uint32_t)ETH_DMACH0STS_CDE)
#define ETH_DMACH0_INT_FLAG_AIS ((uint32_t)ETH_DMACH0STS_AIS)
#define ETH_DMACH0_INT_FLAG_NIS ((uint32_t)ETH_DMACH0STS_NIS)

/** ETH DMA Receive Interrupt Watchdog Timer Count Unit definition **/
#define ETH_DMARXINT_WDGTIM_CNTUNIT_256  ((uint32_t)(ETH_DMACH0RXINTWT_RWTU_0 \
                                                   & ETH_DMACH0RXINTWT_RWTU_1))
#define ETH_DMARXINT_WDGTIM_CNTUNIT_512  ((uint32_t)(ETH_DMACH0RXINTWT_RWTU_0))
#define ETH_DMARXINT_WDGTIM_CNTUNIT_1024 ((uint32_t)(ETH_DMACH0RXINTWT_RWTU_1))
#define ETH_DMARXINT_WDGTIM_CNTUNIT_2048 ((uint32_t)(ETH_DMACH0RXINTWT_RWTU_0 \
                                                   | ETH_DMACH0RXINTWT_RWTU_1))



/*** ETH Macro Definition End ***/


/*** ETH DMA Transmit Normal Descriptor (Read Format) Start ***/

/** Bit definition for ETH_DMATXND0RF register (TDES0) **/
#define ETH_DMATXND0RF_BUF1AP ((uint32_t)0xFFFFFFFF) /* Buffer 1 Address Pointer */
#define ETH_DMATXND0RF_TSOHAP ((uint32_t)0xFFFFFFFF) /* TSO Header Address Pointer */

/** Bit definition for ETH_DMATXND1RF register (TDES1) **/
#define ETH_DMATXND1RF_BUF2AP ((uint32_t)0xFFFFFFFF) /* Buffer 2 Address Pointer */

/** Bit definition for ETH_DMATXND2RF register (TDES2) **/
#define ETH_DMATXND2RF_B1L      ((uint32_t)0x00003FFF) /* Buffer 1 Length */
#define ETH_DMATXND2RF_HL       ((uint32_t)0x00003FFF) /* Header length when TCP segmentation is enabled */
#define ETH_DMATXND2RF_VTIR     ((uint32_t)0x0000C000) /* VTIR[1:0]: VLAN Tag Insertion or Replacement */
#define ETH_DMATXND2RF_VTIR_0   ((uint32_t)0x00004000) /* VTIR bit 0 */
#define ETH_DMATXND2RF_VTIR_1   ((uint32_t)0x00008000) /* VTIR bit 1 */
#define ETH_DMATXND2RF_B2L      ((uint32_t)0x3FFF0000) /* Buffer 2 Length */
#define ETH_DMATXND2RF_TTSE     ((uint32_t)0x40000000) /* Transmit Timestamp Enable */
#define ETH_DMATXND2RF_IOC      ((uint32_t)0x80000000) /* Interrupt on Completion */

/** Bit definition for ETH_DMATXND3RF register (TDES3) **/
#define ETH_DMATXND3RF_FL     ((uint32_t)0x00007FFF) /* Frame Length */
#define ETH_DMATXND3RF_TPL    ((uint32_t)0x0003FFFF) /* TCP Payload Length */
#define ETH_DMATXND3RF_CIC    ((uint32_t)0x00030000) /* CIC[1:0]: Checksum Insertion Control */
#define ETH_DMATXND3RF_CIC_0  ((uint32_t)0x00010000) /* CIC bit 0 */
#define ETH_DMATXND3RF_CIC_1  ((uint32_t)0x00020000) /* CIC bit 1 */
#define ETH_DMATXND3RF_TSE    ((uint32_t)0x00040000) /* TCP Segmentation Enable */
#define ETH_DMATXND3RF_THL    ((uint32_t)0x00780000) /* TCP/UDP Header Length */
#define ETH_DMATXND3RF_SAIC   ((uint32_t)0x00380000) /* SAIC[2:0]: SA Insertion Control */
#define ETH_DMATXND3RF_SAIC_0 ((uint32_t)0x00080000) /* SAIC bit 0 */
#define ETH_DMATXND3RF_SAIC_1 ((uint32_t)0x00100000) /* SAIC bit 1 */
#define ETH_DMATXND3RF_SAIC_2 ((uint32_t)0x00200000) /* SAIC bit 2 */
#define ETH_DMATXND3RF_CPC    ((uint32_t)0x0C000000) /* CPC[1:0]: CRC Pad Control */
#define ETH_DMATXND3RF_CPC_0  ((uint32_t)0x04000000) /* CPC bit 0 */
#define ETH_DMATXND3RF_CPC_1  ((uint32_t)0x08000000) /* CPC bit 1 */
#define ETH_DMATXND3RF_LD     ((uint32_t)0x10000000) /* Last Descriptor */
#define ETH_DMATXND3RF_FD     ((uint32_t)0x20000000) /* First Descriptor */
#define ETH_DMATXND3RF_CTXT   ((uint32_t)0x40000000) /* Context Type */
#define ETH_DMATXND3RF_OWN    ((uint32_t)0x80000000) /* Own Bit */

#define ETH_CHECKSUM_INSERT_DISABIE                 ((uint32_t)(ETH_DMATXND3RF_CIC_0 \
                                                              & ETH_DMATXND3RF_CIC_1))
#define ETH_CHECKSUM_INSERT_ONLY_IPHDR              ((uint32_t)(ETH_DMATXND3RF_CIC_0))
#define ETH_CHECKSUM_INSERT_IPHDR_PAYLOAD           ((uint32_t)(ETH_DMATXND3RF_CIC_1))
#define ETH_CHECKSUM_INSERT_IPHDR_PAYLOAD_PHDR_CALC ((uint32_t)(ETH_DMATXND3RF_CIC_0 \
                                                              | ETH_DMATXND3RF_CIC_1))

#define ETH_CRC_PAD_INSERT     ((uint32_t)(ETH_DMATXND3RF_CPC_0 \
                                         & ETH_DMATXND3RF_CPC_1))
#define ETH_CRC_INSERT         ((uint32_t)(ETH_DMATXND3RF_CPC_0))
#define ETH_CRC_INSERT_DISABIE ((uint32_t)(ETH_DMATXND3RF_CPC_1))
#define ETH_CRC_REPLACEMENT    ((uint32_t)(ETH_DMATXND3RF_CPC_0 \
                                         | ETH_DMATXND3RF_CPC_1))

/*** ETH DMA Transmit Normal Descriptor (Read Format) End ***/


/*** ETH DMA Transmit Normal Descriptor (Write-Back Format) Start ***/

/** Bit definition for ETH_DMATXND0WBF register (TDES0) **/
#define ETH_DMATXND0WBF_TTSL ((uint32_t)0xFFFFFFFF) /* Transmit Packet Timestamp Low */

/** Bit definition for ETH_DMATXND1WBF register (TDES1) **/
#define ETH_DMATXND1WBF_TTSH ((uint32_t)0xFFFFFFFF) /* Transmit Packet Timestamp High */

/** Bit definition for ETH_DMATXND3WBF register (TDES3) **/
#define ETH_DMATXND3WBF_IHE  ((uint32_t)0x00000001) /* IP Header Error */
#define ETH_DMATXND3WBF_DB   ((uint32_t)0x00000002) /* Deferred Bit */
#define ETH_DMATXND3WBF_UF   ((uint32_t)0x00000004) /* Underflow Error */
#define ETH_DMATXND3WBF_ED   ((uint32_t)0x00000004) /* Excessive Deferral */
#define ETH_DMATXND3WBF_CC   ((uint32_t)0x000000F0) /* Collision Count */
#define ETH_DMATXND3WBF_EC   ((uint32_t)0x00000100) /* Excessive Collision */
#define ETH_DMATXND3WBF_LC   ((uint32_t)0x00000200) /* Late Collision */
#define ETH_DMATXND3WBF_NC   ((uint32_t)0x00000400) /* No Carrier */
#define ETH_DMATXND3WBF_LOC  ((uint32_t)0x00000800) /* Loss of Carrier */
#define ETH_DMATXND3WBF_PCE  ((uint32_t)0x00001000) /* Payload Checksum Error */
#define ETH_DMATXND3WBF_PF   ((uint32_t)0x00002000) /* Packet Flushed */
#define ETH_DMATXND3WBF_JT   ((uint32_t)0x00004000) /* Jabber Timeout */
#define ETH_DMATXND3WBF_ES   ((uint32_t)0x00008000) /* Error Summary */
#define ETH_DMATXND3WBF_EUE  ((uint32_t)0x00010000) /* ECC Uncorrectable Error Status in TSO memory */
#define ETH_DMATXND3WBF_TTSS ((uint32_t)0x00020000) /* Tx Timestamp Status */
#define ETH_DMATXND3WBF_DE   ((uint32_t)0x00800000) /* Descriptor Error */
#define ETH_DMATXND3WBF_LD   ((uint32_t)0x10000000) /* Last Descriptor */
#define ETH_DMATXND3WBF_FD   ((uint32_t)0x20000000) /* First Descriptor */
#define ETH_DMATXND3WBF_CTXT ((uint32_t)0x40000000) /* Context Type */
#define ETH_DMATXND3WBF_OWN  ((uint32_t)0x80000000) /* Own Bit */

/** ETH DMA Tx Descriptor flag definition **/
#define ETH_DMATXDESC_FLAG_IHE  ((uint32_t)ETH_DMATXND3WBF_IHE)
#define ETH_DMATXDESC_FLAG_DB   ((uint32_t)ETH_DMATXND3WBF_DB)
#define ETH_DMATXDESC_FLAG_UF   ((uint32_t)ETH_DMATXND3WBF_UF)
#define ETH_DMATXDESC_FLAG_ED   ((uint32_t)ETH_DMATXND3WBF_ED)
#define ETH_DMATXDESC_FLAG_CC   ((uint32_t)ETH_DMATXND3WBF_CC)
#define ETH_DMATXDESC_FLAG_EC   ((uint32_t)ETH_DMATXND3WBF_EC)
#define ETH_DMATXDESC_FLAG_LC   ((uint32_t)ETH_DMATXND3WBF_LC)
#define ETH_DMATXDESC_FLAG_NC   ((uint32_t)ETH_DMATXND3WBF_NC)
#define ETH_DMATXDESC_FLAG_LOC  ((uint32_t)ETH_DMATXND3WBF_LOC)
#define ETH_DMATXDESC_FLAG_PCE  ((uint32_t)ETH_DMATXND3WBF_PCE)
#define ETH_DMATXDESC_FLAG_PF   ((uint32_t)ETH_DMATXND3WBF_PF)
#define ETH_DMATXDESC_FLAG_JT   ((uint32_t)ETH_DMATXND3WBF_JT)
#define ETH_DMATXDESC_FLAG_ES   ((uint32_t)ETH_DMATXND3WBF_ES)
#define ETH_DMATXDESC_FLAG_TTSS ((uint32_t)ETH_DMATXND3WBF_TTSS)
#define ETH_DMATXDESC_FLAG_DE   ((uint32_t)ETH_DMATXND3WBF_DE)
#define ETH_DMATXDESC_FLAG_LD   ((uint32_t)ETH_DMATXND3WBF_LD)
#define ETH_DMATXDESC_FLAG_FD   ((uint32_t)ETH_DMATXND3WBF_FD)

/*** ETH DMA Transmit Normal Descriptor (Write-Back Format) End ***/


/*** ETH DMA Transmit Context Descriptor Start ***/

/** Bit definition for ETH_DMATXCD0 register (TDES0) **/
#define ETH_DMATXCD0_TTSL ((uint32_t)0xFFFFFFFF) /* Transmit Packet Timestamp Low */

/** Bit definition for ETH_DMATXCD1 register (TDES1) **/
#define ETH_DMATXCD1_TTSH ((uint32_t)0xFFFFFFFF) /* Transmit Packet Timestamp High */

/** Bit definition for ETH_DMATXCD2 register (TDES2) **/
#define ETH_DMATXCD2_MSS  ((uint32_t)0x00003FFF) /* Maximum Segment Size */
#define ETH_DMATXCD2_IVT  ((uint32_t)0xFFFF0000) /* Inner VLAN Tag */

/** Bit definition for ETH_DMATXCD3 register (TDES3) **/
#define ETH_DMATXCD3_VT      ((uint32_t)0x0000FFFF) /* VLAN Tag */
#define ETH_DMATXCD3_VLTV    ((uint32_t)0x00010000) /* VLAN Tag Valid */
#define ETH_DMATXCD3_IVLTV   ((uint32_t)0x00020000) /* VLAN Tag Valid */
#define ETH_DMATXCD3_IVTIR   ((uint32_t)0x000C0000) /* IVTIR[1:0]: Inner VLAN Tag Insert or Replace */
#define ETH_DMATXCD3_IVTIR_0 ((uint32_t)0x00040000) /* IVTIR bit 0 */
#define ETH_DMATXCD3_IVTIR_1 ((uint32_t)0x00080000) /* IVTIR bit 1 */
#define ETH_DMATXCD3_CDE     ((uint32_t)0x00800000) /* Context Descriptor Error */
#define ETH_DMATXCD3_TCMSSV  ((uint32_t)0x04000000) /* One-Step Timestamp Correction Input */
#define ETH_DMATXCD3_OSTC    ((uint32_t)0x08000000) /* One-Step Timestamp Correction Enable */
#define ETH_DMATXCD3_CTXT    ((uint32_t)0x40000000) /* Context Type */
#define ETH_DMATXCD3_OWN     ((uint32_t)0x80000000) /* Own Bit */


/*** ETH DMA Transmit Context Descriptor End ***/


/*** ETH DMA Receive Normal Descriptor (Read Format) Start ***/

/** Bit definition for ETH_DMARXND0RF register (RDES0) **/
#define ETH_DMARXND0RF_BUF1AP ((uint32_t)0xFFFFFFFF) /* Buffer 1 Address Pointer */

/** Bit definition for ETH_DMARXND2RF register (RDES2) **/
#define ETH_DMARXND2RF_BUF2AP ((uint32_t)0xFFFFFFFF) /* Buffer 2 Address Pointer */

/** Bit definition for ETH_DMARXND3RF register (RDES3) **/
#define ETH_DMARXND3RF_BUF1V ((uint32_t)0x01000000) /* Buffer 1 Address Valid */
#define ETH_DMARXND3RF_BUF2V ((uint32_t)0x02000000) /* Buffer 2 Address Valid */
#define ETH_DMARXND3RF_IOC   ((uint32_t)0x40000000) /* Interrupt Enabled on Completion */
#define ETH_DMARXND3RF_OWN   ((uint32_t)0x80000000) /* Own Bit */

/*** ETH DMA Receive Normal Descriptor (Read Format) End ***/


/*** ETH DMA Receive Normal Descriptor (Write-Back Format) Start ***/

/** Bit definition for ETH_DMARXND0WBF register (RDES0) **/
#define ETH_DMARXND0WBF_OVT ((uint32_t)0x0000FFFF) /* Outer VLAN Tag */
#define ETH_DMARXND0WBF_IVT ((uint32_t)0xFFFF0000) /* Inner VLAN Tag */

/** Bit definition for ETH_DMARXND1WBF register (RDES1) **/
#define ETH_DMARXND1WBF_PT    ((uint32_t)0x00000007) /* PT[2:0]: Payload Type */
#define ETH_DMARXND1WBF_PT_0  ((uint32_t)0x00000001) /* PT bit 0 */
#define ETH_DMARXND1WBF_PT_1  ((uint32_t)0x00000002) /* PT bit 1 */
#define ETH_DMARXND1WBF_PT_2  ((uint32_t)0x00000004) /* PT bit 2 */
#define ETH_DMARXND1WBF_IPHE  ((uint32_t)0x00000008) /* IP Header Error */
#define ETH_DMARXND1WBF_IPV4  ((uint32_t)0x00000010) /* IPV4 Header Present */
#define ETH_DMARXND1WBF_IPV6  ((uint32_t)0x00000020) /* IPV6 Header Present */
#define ETH_DMARXND1WBF_IPCB  ((uint32_t)0x00000040) /* IP Checksum Bypassed */
#define ETH_DMARXND1WBF_IPCE  ((uint32_t)0x00000080) /* IP Payload Error */
#define ETH_DMARXND1WBF_PMT   ((uint32_t)0x00000F00) /* PMT[3:0]: PTP Message Type */
#define ETH_DMARXND1WBF_PMT_0 ((uint32_t)0x00000100) /* PMT bit 0 */
#define ETH_DMARXND1WBF_PMT_1 ((uint32_t)0x00000200) /* PMT bit 1 */
#define ETH_DMARXND1WBF_PMT_2 ((uint32_t)0x00000400) /* PMT bit 2 */
#define ETH_DMARXND1WBF_PMT_3 ((uint32_t)0x00000800) /* PMT bit 3 */
#define ETH_DMARXND1WBF_PFT   ((uint32_t)0x00001000) /* PTP Packet Type */
#define ETH_DMARXND1WBF_PV    ((uint32_t)0x00002000) /* PTP Version */
#define ETH_DMARXND1WBF_TSA   ((uint32_t)0x00004000) /* Timestamp Available */
#define ETH_DMARXND1WBF_TD    ((uint32_t)0x00008000) /* Timestamp Dropped */
#define ETH_DMARXND1WBF_OPC   ((uint32_t)0xFFFF0000) /* OAM Sub-Type Code, or MAC Control Packet opcode */

/** ETH DMA Rx Descriptor Extended flag definition **/
#define ETH_DMARXDESC_EXTFLAG_PT_NONE    ((uint32_t)(ETH_DMARXND1WBF_PT_0 \
                                                   & ETH_DMARXND1WBF_PT_1 \
                                                   & ETH_DMARXND1WBF_PT_2)) /* Payload Type: Unknown */
#define ETH_DMARXDESC_EXTFLAG_PT_NUDP    ((uint32_t)(ETH_DMARXND1WBF_PT_0)) /* Payload Type: UDP */
#define ETH_DMARXDESC_EXTFLAG_PT_TCP     ((uint32_t)(ETH_DMARXND1WBF_PT_1)) /* Payload Type: TCP */
#define ETH_DMARXDESC_EXTFLAG_PT_ICNP    ((uint32_t)(ETH_DMARXND1WBF_PT_0 \
                                                   | ETH_DMARXND1WBF_PT_1)) /* Payload Type: ICMP */
#define ETH_DMARXDESC_EXTFLAG_IPHE       ((uint32_t)(ETH_DMARXND1WBF_IPHE))
#define ETH_DMARXDESC_EXTFLAG_IPV4       ((uint32_t)(ETH_DMARXND1WBF_IPV4))
#define ETH_DMARXDESC_EXTFLAG_IPV6       ((uint32_t)(ETH_DMARXND1WBF_IPV6))
#define ETH_DMARXDESC_EXTFLAG_IPCB       ((uint32_t)(ETH_DMARXND1WBF_IPCB))
#define ETH_DMARXDESC_EXTFLAG_IPCE       ((uint32_t)(ETH_DMARXND1WBF_IPCE))
#define ETH_DMARXDESC_EXTFLAG_PMT_NONE   ((uint32_t)(ETH_DMARXND1WBF_PMT_0 \
                                                   & ETH_DMARXND1WBF_PMT_1 \
                                                   & ETH_DMARXND1WBF_PMT_2 \
                                                   & ETH_DMARXND1WBF_PMT_3)) /* No PTP message received */
#define ETH_DMARXDESC_EXTFLAG_PMT_SYNC   ((uint32_t)(ETH_DMARXND1WBF_PMT_0)) /* PTP Message Type: SYNC */
#define ETH_DMARXDESC_EXTFLAG_PMT_FU     ((uint32_t)(ETH_DMARXND1WBF_PMT_1)) /* PTP Message Type: Follow_Up */
#define ETH_DMARXDESC_EXTFLAG_PMT_DREQ   ((uint32_t)(ETH_DMARXND1WBF_PMT_0 \
                                                   | ETH_DMARXND1WBF_PMT_1)) /* PTP Message Type: Delay_Req */
#define ETH_DMARXDESC_EXTFLAG_PMT_DRESP  ((uint32_t)(ETH_DMARXND1WBF_PMT_2)) /* PTP Message Type: Delay_Resp */
#define ETH_DMARXDESC_EXTFLAG_PMT_PDREQ  ((uint32_t)(ETH_DMARXND1WBF_PMT_0 \
                                                   | ETH_DMARXND1WBF_PMT_2)) /* PTP Message Type: Pdelay_Req */
#define ETH_DMARXDESC_EXTFLAG_PMT_PDRESP ((uint32_t)(ETH_DMARXND1WBF_PMT_1 \
                                                   | ETH_DMARXND1WBF_PMT_2)) /* PTP Message Type: Pdelay_Resp */
#define ETH_DMARXDESC_EXTFLAG_PMT_PRFU   ((uint32_t)(ETH_DMARXND1WBF_PMT_0 \
                                                   | ETH_DMARXND1WBF_PMT_1 \
                                                   | ETH_DMARXND1WBF_PMT_2)) /* PTP Message Type: Pdelay_Resp_Follow_Up */
#define ETH_DMARXDESC_EXTFLAG_PMT_ANN    ((uint32_t)(ETH_DMARXND1WBF_PMT_3)) /* PTP Message Type: Announce */
#define ETH_DMARXDESC_EXTFLAG_PMT_MAN    ((uint32_t)(ETH_DMARXND1WBF_PMT_0 \
                                                   | ETH_DMARXND1WBF_PMT_3)) /* PTP Message Type: Management */
#define ETH_DMARXDESC_EXTFLAG_PMT_SIG    ((uint32_t)(ETH_DMARXND1WBF_PMT_1 \
                                                   | ETH_DMARXND1WBF_PMT_3)) /* PTP Message Type: Signaling */
#define ETH_DMARXDESC_EXTFLAG_PMT_PRT    ((uint32_t)(ETH_DMARXND1WBF_PMT_0 \
                                                   | ETH_DMARXND1WBF_PMT_1 \
                                                   | ETH_DMARXND1WBF_PMT_2 \
                                                   | ETH_DMARXND1WBF_PMT_3)) /* PTP packet with Reserved message Type */
#define ETH_DMARXDESC_EXTFLAG_PFT        ((uint32_t)(ETH_DMARXND1WBF_PFT))
#define ETH_DMARXDESC_EXTFLAG_PV         ((uint32_t)(ETH_DMARXND1WBF_PV))
#define ETH_DMARXDESC_EXTFLAG_TSA        ((uint32_t)(ETH_DMARXND1WBF_TSA))
#define ETH_DMARXDESC_EXTFLAG_TD         ((uint32_t)(ETH_DMARXND1WBF_TD))


/** Bit definition for ETH_DMARXND2WBF register (RDES2) **/
#define ETH_DMARXND2WBF_ARPNR    ((uint32_t)0x00000400) /* ARP Reply Not Generated */
#define ETH_DMARXND2WBF_VFS      ((uint32_t)0x00008000) /* VLAN Filter Status */
#define ETH_DMARXND2WBF_SAF      ((uint32_t)0x00010000) /* SA Address Filter Fail */
#define ETH_DMARXND2WBF_DAF      ((uint32_t)0x00020000) /* DA Address Filter Fail */
#define ETH_DMARXND2WBF_HF       ((uint32_t)0x00040000) /* Hash Filter Status */
#define ETH_DMARXND2WBF_MADRM    ((uint32_t)0x07F80000) /* MAC Address Match */
#define ETH_DMARXND2WBF_HV       ((uint32_t)0x07F80000) /* Hash Value */
#define ETH_DMARXND2WBF_L3FM     ((uint32_t)0x08000000) /* Layer 3 Filter Match */
#define ETH_DMARXND2WBF_L4FM     ((uint32_t)0x10000000) /* Layer 4 Filter Match */
#define ETH_DMARXND2WBF_L3L4FM   ((uint32_t)0xE0000000) /* L3L4FM[2:0]: Layer 3 and Layer 4 Filter Number Matched */
#define ETH_DMARXND2WBF_L3L4FM_0 ((uint32_t)0x20000000) /* L3L4FM bit 0 */
#define ETH_DMARXND2WBF_L3L4FM_1 ((uint32_t)0x40000000) /* L3L4FM bit 1 */
#define ETH_DMARXND2WBF_L3L4FM_2 ((uint32_t)0x80000000) /* L3L4FM bit 2 */

/** ETH DMA Rx Descriptor Filter flag definition **/
#define ETH_DMARXDESC_FLTFLAG_VFS ((uint32_t)(ETH_DMARXND2WBF_VFS))
#define ETH_DMARXDESC_FLTFLAG_SAF ((uint32_t)(ETH_DMARXND2WBF_SAF))
#define ETH_DMARXDESC_FLTFLAG_DAF ((uint32_t)(ETH_DMARXND2WBF_DAF))
#define ETH_DMARXDESC_FLTFLAG_HF  ((uint32_t)(ETH_DMARXND2WBF_HF))


/** Bit definition for ETH_DMARXND3WBF register (RDES3) **/
#define ETH_DMARXND3WBF_PL   ((uint32_t)0x00007FFF) /* Packet Length */
#define ETH_DMARXND3WBF_ES   ((uint32_t)0x00008000) /* Error Summary */
#define ETH_DMARXND3WBF_LT   ((uint32_t)0x00070000) /* LT[2:0]: Length/Type Field */
#define ETH_DMARXND3WBF_LT_0 ((uint32_t)0x00010000) /* LT bit 0 */
#define ETH_DMARXND3WBF_LT_1 ((uint32_t)0x00020000) /* LT bit 1 */
#define ETH_DMARXND3WBF_LT_2 ((uint32_t)0x00040000) /* LT bit 2 */
#define ETH_DMARXND3WBF_DE   ((uint32_t)0x00080000) /* Dribble Bit Error */
#define ETH_DMARXND3WBF_RE   ((uint32_t)0x00100000) /* Receive Error */
#define ETH_DMARXND3WBF_OE   ((uint32_t)0x00200000) /* Overflow Error */
#define ETH_DMARXND3WBF_RWT  ((uint32_t)0x00400000) /* Receive Watchdog Timeout */
#define ETH_DMARXND3WBF_GP   ((uint32_t)0x00800000) /* Giant Packet */
#define ETH_DMARXND3WBF_CE   ((uint32_t)0x01000000) /* CRC Error */
#define ETH_DMARXND3WBF_RS0V ((uint32_t)0x02000000) /* Receive Status RDES0 Valid */
#define ETH_DMARXND3WBF_RS1V ((uint32_t)0x04000000) /* Receive Status RDES1 Valid */
#define ETH_DMARXND3WBF_RS2V ((uint32_t)0x08000000) /* Receive Status RDES2 Valid */
#define ETH_DMARXND3WBF_LD   ((uint32_t)0x10000000) /* Last Descriptor */
#define ETH_DMARXND3WBF_FD   ((uint32_t)0x20000000) /* First Descriptor */
#define ETH_DMARXND3WBF_CTXT ((uint32_t)0x40000000) /* Receive Context Descriptor */
#define ETH_DMARXND3WBF_OWN  ((uint32_t)0x80000000) /* Own Bit */

#define ETH_DMARXND3WBF_LT_LP    ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                           & ETH_DMARXND3WBF_LT_1 \
                                           & ETH_DMARXND3WBF_LT_2)) /* length packet */
#define ETH_DMARXND3WBF_LT_TP    ((uint32_t)(ETH_DMARXND3WBF_LT_0)) /* type packet */
#define ETH_DMARXND3WBF_LT_ARP   ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                           | ETH_DMARXND3WBF_LT_1)) /* ARP Request packet type */
#define ETH_DMARXND3WBF_LT_VLAN  ((uint32_t)(ETH_DMARXND3WBF_LT_2)) /* Type packet with VLAN Tag */
#define ETH_DMARXND3WBF_LT_DVLAN ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                           | ETH_DMARXND3WBF_LT_2)) /* Type packet with Double VLAN Tag */
#define ETH_DMARXND3WBF_LT_MAC   ((uint32_t)(ETH_DMARXND3WBF_LT_1 \
                                           | ETH_DMARXND3WBF_LT_2)) /* MAC Control packet type */
#define ETH_DMARXND3WBF_LT_OAM   ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                           | ETH_DMARXND3WBF_LT_1 \
                                           | ETH_DMARXND3WBF_LT_2)) /* OAM packet type */

/** ETH DMA Rx Descriptor flag definition **/
#define ETH_DMARXDESC_FLAG_ES       ((uint32_t)(ETH_DMATXND3WBF_IHE))
#define ETH_DMARXDESC_FLAG_LT_LP    ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                              & ETH_DMARXND3WBF_LT_1 \
                                              & ETH_DMARXND3WBF_LT_2)) /* length packet */
#define ETH_DMARXDESC_FLAG_LT_TP    ((uint32_t)(ETH_DMARXND3WBF_LT_0)) /* type packet */
#define ETH_DMARXDESC_FLAG_LT_ARP   ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                              | ETH_DMARXND3WBF_LT_1)) /* ARP Request packet type */
#define ETH_DMARXDESC_FLAG_LT_VLAN  ((uint32_t)(ETH_DMARXND3WBF_LT_2)) /* Type packet with VLAN Tag */
#define ETH_DMARXDESC_FLAG_LT_DVLAN ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                              | ETH_DMARXND3WBF_LT_2)) /* Type packet with Double VLAN Tag */
#define ETH_DMARXDESC_FLAG_LT_MAC   ((uint32_t)(ETH_DMARXND3WBF_LT_1 \
                                              | ETH_DMARXND3WBF_LT_2)) /* MAC Control packet type */
#define ETH_DMARXDESC_FLAG_LT_OAM   ((uint32_t)(ETH_DMARXND3WBF_LT_0 \
                                              | ETH_DMARXND3WBF_LT_1 \
                                              | ETH_DMARXND3WBF_LT_2)) /* OAM packet type */
#define ETH_DMARXDESC_FLAG_DE       ((uint32_t)(ETH_DMARXND3WBF_DE))
#define ETH_DMARXDESC_FLAG_RE       ((uint32_t)(ETH_DMARXND3WBF_RE))
#define ETH_DMARXDESC_FLAG_OE       ((uint32_t)(ETH_DMARXND3WBF_OE))
#define ETH_DMARXDESC_FLAG_RWT      ((uint32_t)(ETH_DMARXND3WBF_RWT))
#define ETH_DMARXDESC_FLAG_GP       ((uint32_t)(ETH_DMARXND3WBF_GP))
#define ETH_DMARXDESC_FLAG_CE       ((uint32_t)(ETH_DMARXND3WBF_CE))
#define ETH_DMARXDESC_FLAG_RS0V     ((uint32_t)(ETH_DMARXND3WBF_RS0V))
#define ETH_DMARXDESC_FLAG_RS1V     ((uint32_t)(ETH_DMARXND3WBF_RS1V))
#define ETH_DMARXDESC_FLAG_RS2V     ((uint32_t)(ETH_DMARXND3WBF_RS2V))
#define ETH_DMARXDESC_FLAG_LD       ((uint32_t)(ETH_DMARXND3WBF_LD))
#define ETH_DMARXDESC_FLAG_FD       ((uint32_t)(ETH_DMARXND3WBF_FD))


/*** ETH DMA Receive Normal Descriptor (Write-Back Format) End ***/


/*** ETH DMA Receive Context Descriptor Start ***/

/** Bit definition for ETH_DMARXCD0 register (RDES0) **/
#define ETH_DMARXCD0_RTSL ((uint32_t)0xFFFFFFFF) /* Receive Packet Timestamp Low */

/** Bit definition for ETH_DMARXCD1 register (RDES1) **/
#define ETH_DMARXCD1_RTSH ((uint32_t)0xFFFFFFFF) /* Receive Packet Timestamp High */

/** Bit definition for ETH_DMARXCD3 register (RDES3) **/
#define ETH_DMARXCD3_DE   ((uint32_t)0x20000000) /* Descriptor Error */
#define ETH_DMARXCD3_CTXT ((uint32_t)0x40000000) /* Receive Context Descriptor */
#define ETH_DMARXCD3_OWN  ((uint32_t)0x80000000) /* Own Bit */

/*** ETH DMA Receive Context Descriptor End ***/


/*** ETH Driving Functions Declaration ***/
void ETH_DeInit(ETH_Module* ETHx);
void ETH_StructInit(ETH_Module* ETHx, ETH_InitType* ETH_InitParam);
void ETH_DMATxDescListInit(ETH_Module* ETHx, ETH_InfoType* pInfo);
void ETH_DMARxDescListInit(ETH_Module* ETHx, ETH_InfoType* pInfo);
void ETH_ConfigMDCNormalClock(ETH_Module* ETHx, RCC_ClocksTypeDef* pClk);
void ETH_ConfigMDCFastClock(ETH_Module* ETHx, uint32_t DivValue);
uint32_t ETH_ReadPHYRegister(ETH_Module* ETHx, uint32_t PHYAddr, uint32_t PHYReg, uint32_t* pRegValue);
uint32_t ETH_WritePHYRegister(ETH_Module* ETHx, uint32_t PHYAddr, uint32_t PHYReg, uint32_t PHYRegValue);
EthFuncStatusType ETH_ExternalPHYInit(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_InitType* ETH_InitParam);
EthFuncStatusType ETH_Init(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_InitType* ETH_InitParam);
void ETH_TxMACCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_RxMACCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_SetHashTable(ETH_Module* ETHx, uint32_t *pHashTable);
void ETH_RxVLANTagStructInit(ETH_RxVLANTagInitType* ETH_RxVTInitParam);
void ETH_RxVLANTagInit(ETH_Module* ETHx, ETH_RxVLANTagInitType* ETH_RxVTInitParam);
void ETH_SetVLANHashTable(ETH_Module* ETHx, uint16_t HashTable);
void ETH_SetRxVLANIdentifier(ETH_Module* ETHx, uint32_t VLANIdentifier);
void ETH_InitiatePauseControlPacket(ETH_Module* ETHx);
void ETH_ActivateBackpressure(ETH_Module* ETHx);
void ETH_PowerDownCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_MagicPacketDetectionCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_WakeUpPacketDetectionCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_GlobalUnicastWakeUpCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_ResetWakeUpPacketFilterRegPointer(ETH_Module* ETHx);
void ETH_SetWakeUpPacketFilterRegister(ETH_Module* ETHx, uint32_t *pBuffer);
void ETH_CSRRegisterWrite1ClearCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_SetMACAddress(ETH_Module* ETHx, EthMacAddr0123Type Offset, uint8_t* pAddr);
void ETH_GetMACAddress(ETH_Module* ETHx, EthMacAddr0123Type Offset, uint8_t* pAddr);
void ETH_MACAddressPerfectFilterCmd(ETH_Module* ETHx, EthMacAddr123Type Offset, FunctionalStatus Cmd);
void ETH_SetMACAddressFilter(ETH_Module* ETHx, EthMacAddr123Type Offset, EthMacAddrFilterType Filter);
void ETH_SetMACAddressFilterMaskBytes(ETH_Module* ETHx, EthMacAddr123Type Offset, uint32_t MaskByte);
void ETH_MMCCountersReset(ETH_Module* ETHx);
void ETH_MMCCounterStopRolloverCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_MMCResetOnReadCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_MMCCounterFreezeCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_MMCCounterHalfPreset(ETH_Module* ETHx);
void ETH_MMCCounterFullPreset(ETH_Module* ETHx);
void ETH_MMCCounterUpdateForDropBCPacketCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
uint32_t ETH_GetMMCCounterValue(ETH_Module* ETHx, EthMmcAddrType Offset);
void ETH_MACTimeStampCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_SetTimeStampUpdateMethod(ETH_Module* ETHx, uint32_t Method);
void ETH_MACTimeStampInit(ETH_Module* ETHx);
void ETH_MACTimeStampUpdate(ETH_Module* ETHx);
// void ETH_EnableTimeStampIntTrigger(ETH_Module* ETHx);
void ETH_MACTimeStampAddendRegUpdate(ETH_Module* ETHx);
void ETH_MACTimeStampAllPacketsCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_MACTimeStampDigBinRolloverCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_PTPTypePacketProcesCmd(ETH_Module* ETHx, uint32_t PacketType, FunctionalStatus Cmd);
void ETH_MACAddrPTPPacketFilterCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_MACTxTimeStampStatusModeCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_SetSubSecondIncrementValue(ETH_Module* ETHx, uint8_t IncValue);
void ETH_SetTimeStampUpdateValue(ETH_Module* ETHx, uint32_t CalMode, uint32_t SecondValue, uint32_t SubSecondValue);
void ETH_SetTimeStampAddendValue(ETH_Module* ETHx, uint32_t AddValue);
uint32_t ETH_GetTimeStampRegValue(ETH_Module* ETHx, EthTsAddrType Offset);
void ETH_ConfigPPSOutput(ETH_Module* ETHx, uint32_t OutputFreq);
void ETH_SetPPSTargetTimeValue(ETH_Module* ETHx, uint32_t SecondValue, uint32_t SubSecondValue);

void ETH_MTLDropTxStatusCmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_MTLCounterPreset(ETH_Module* ETHx);
void ETH_MTLCounterReset(ETH_Module* ETHx);
void ETH_FlushTransmitQueue(ETH_Module* ETHx);
uint16_t ETH_GetMTLUnderflowPacketCounter(ETH_Module* ETHx);
uint16_t ETH_GetMTLOverflowPacketCounter(ETH_Module* ETHx);
uint16_t ETH_GetMTLMissedPacketCounter(ETH_Module* ETHx);

void ETH_SoftwareReset(ETH_Module* ETHx);
void ETH_TxDMACmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_RxDMACmd(ETH_Module* ETHx, FunctionalStatus Cmd);
void ETH_ResumeDMATransmission(ETH_Module* ETHx);
void ETH_ResumeDMAReception(ETH_Module* ETHx);
void ETH_SetRxInterruptWatchdogTimer(ETH_Module* ETHx, uint32_t CntUnit, uint32_t CntValue);
uint32_t ETH_GetCurrentTxDescriptorAddress(ETH_Module* ETHx);
uint32_t ETH_GetCurrentRxDescriptorAddress(ETH_Module* ETHx);
uint32_t ETH_GetCurrentTxBufferAddress(ETH_Module* ETHx);
uint32_t ETH_GetCurrentRxBufferAddress(ETH_Module* ETHx);
uint8_t ETH_GetTxDMAErrorType(ETH_Module* ETHx);
uint8_t ETH_GetRxDMAErrorType(ETH_Module* ETHx);
uint16_t ETH_GetDMACh0DroppedPacketCounter(ETH_Module* ETHx);
uint16_t ETH_GetDMACh0ERICounter(ETH_Module* ETHx);

EthFuncStatusType ETH_RxDescAssignMemory(ETH_InfoType* pInfo, uint32_t Index, uint8_t* pBuffer1, uint8_t* pBuffer2);
EthFuncStatusType ETH_BuildRxDescriptors(ETH_Module* ETHx, ETH_InfoType* pInfo);
EthFuncStatusType ETH_PrepareTxDescriptors(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_TxPacketType* pTxPacket, uint32_t ItMode);
EthFuncStatusType ETH_Transmit(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_TxPacketType* pTxPacket, uint32_t Timeout);
EthFuncStatusType ETH_TransmitIT(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_TxPacketType* pTxPacket);
uint8_t ETH_IsRxDataAvailable(ETH_InfoType* pInfo);
EthFuncStatusType ETH_GetRxDataBuffer(ETH_InfoType* pInfo, ETH_BufferType* pRxBuffer);
uint32_t ETH_GetRxDataLength(ETH_InfoType* pInfo);
EthFuncStatusType ETH_GetRxPacketInfo(ETH_InfoType* pInfo, ETH_RxPacketType* pRxPacket);
void ETH_Start(ETH_Module* ETHx);
void ETH_StartIT(ETH_Module* ETHx, ETH_InfoType* pInfo);
void ETH_Stop(ETH_Module* ETHx);
void ETH_StopIT(ETH_Module* ETHx, ETH_InfoType* pInfo);

FlagStatus ETH_GetTxDescFlagStatus(ETH_DMADescType* pTxDescriptor, uint32_t Flag);
FlagStatus ETH_GetRxDescExtendedFlagStatus(ETH_DMADescType* pRxDescriptor, uint32_t Flag);
FlagStatus ETH_GetRxDescFilterFlagStatus(ETH_DMADescType* pRxDescriptor, uint32_t Flag);
FlagStatus ETH_GetRxDescFlagStatus(ETH_DMADescType* pRxDescriptor, uint32_t Flag);
FlagStatus ETH_GetFlowControlBusyStatus(ETH_Module* ETHx);
INTStatus ETH_GetMACInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag);
FlagStatus ETH_GetMACTxRxFlagStatus(ETH_Module* ETHx, uint32_t Flag);
FlagStatus ETH_GetPMTFlagStatus(ETH_Module* ETHx, uint32_t Flag);
INTStatus ETH_GetMMCRxInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag);
INTStatus ETH_GetMMCTxInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag);
FlagStatus ETH_GetMACTimeStampFlagStatus(ETH_Module* ETHx, uint32_t Flag);
FlagStatus ETH_GetFlushTransmitQueueStatus(ETH_Module* ETHx);
INTStatus ETH_GetMTLInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag);
INTStatus ETH_GetMTLQueueInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag);
FlagStatus ETH_GetMTLCounterFlagStatus(ETH_Module* ETHx, uint32_t Flag);
FlagStatus ETH_GetSoftwareResetStatus(ETH_Module* ETHx);
INTStatus ETH_GetDMAInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag);
uint32_t ETH_GetDMACh0TxProcessStatus(ETH_Module* ETHx);
uint32_t ETH_GetDMACh0RxProcessStatus(ETH_Module* ETHx);
FlagStatus ETH_GetDMACh0FlagStatus(ETH_Module* ETHx, uint32_t Flag);
INTStatus ETH_GetDMACh0InterruptStatus(ETH_Module* ETHx, uint32_t IntFlag);

void ETH_ClearMACPHYInterruptFlag(ETH_Module* ETHx);
void ETH_ClearPMTFlag(ETH_Module* ETHx, uint32_t Flag);
void ETH_ClearMMCRxInterruptFlag(ETH_Module* ETHx, uint32_t IntFlag);
void ETH_ClearMMCTxInterruptFlag(ETH_Module* ETHx, uint32_t IntFlag);
void ETH_ClearMACTimeStampFlag(ETH_Module* ETHx, uint32_t Flag);
void ETH_ClearMACTxRxFlag(ETH_Module* ETHx, uint32_t Flag);
void ETH_ClearMACMDIOInterruptFlag(ETH_Module* ETHx);
void ETH_ClearMTLQueueInterruptFlag(ETH_Module* ETHx, uint32_t IntFlag);
void ETH_ClearDMACh0Flag(ETH_Module* ETHx, uint32_t Flag);
void ETH_ClearDMACh0InterruptFlag(ETH_Module* ETHx, uint32_t IntFlag);

void ETH_ConfigMACInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd);
void ETH_ConfigMMCRxInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd);
void ETH_ConfigMMCTxInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd);
void ETH_ConfigMTLQueueInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd);
void ETH_ConfigDMACh0Interrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd);

/*** ETH Driving Functions Declaration End ***/


#ifdef __cplusplus
}
#endif


#endif /* __N32H76X_78X_ETH_H__ */

