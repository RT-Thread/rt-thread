#ifndef FM3_EMAC_H_INCLUDED
#define FM3_EMAC_H_INCLUDED

#include <stdint.h>
//#include <mb9bf618s.h>
#include <eth_driver.h>
#include "gd32f4xx_enet.h"

/******************************************************************************/
/*                Ethernet MAC Registers bits definitions                     */
/******************************************************************************/
		/* Bit definition for Ethernet MAC Control Register register */
#define EMAC_MACCR_WD      ((uint32_t)0x00800000)  /* Watchdog disable */
#define EMAC_MACCR_JD      ((uint32_t)0x00400000)  /* Jabber disable */
#define EMAC_MACCR_IFG     ((uint32_t)0x000E0000)  /* Inter-frame gap */
#define EMAC_MACCR_IFG_96Bit     ((uint32_t)0x00000000)  /* Minimum IFG between frames during transmission is 96Bit */
#define EMAC_MACCR_IFG_88Bit     ((uint32_t)0x00020000)  /* Minimum IFG between frames during transmission is 88Bit */
#define EMAC_MACCR_IFG_80Bit     ((uint32_t)0x00040000)  /* Minimum IFG between frames during transmission is 80Bit */
#define EMAC_MACCR_IFG_72Bit     ((uint32_t)0x00060000)  /* Minimum IFG between frames during transmission is 72Bit */
#define EMAC_MACCR_IFG_64Bit     ((uint32_t)0x00080000)  /* Minimum IFG between frames during transmission is 64Bit */
#define EMAC_MACCR_IFG_56Bit     ((uint32_t)0x000A0000)  /* Minimum IFG between frames during transmission is 56Bit */
#define EMAC_MACCR_IFG_48Bit     ((uint32_t)0x000C0000)  /* Minimum IFG between frames during transmission is 48Bit */
#define EMAC_MACCR_IFG_40Bit     ((uint32_t)0x000E0000)  /* Minimum IFG between frames during transmission is 40Bit */
#define EMAC_MACCR_CSD     ((uint32_t)0x00010000)  /* Carrier sense disable (during transmission) */
#define EMAC_MACCR_FES     ((uint32_t)0x00004000)  /* Fast ethernet speed */
#define EMAC_MACCR_ROD     ((uint32_t)0x00002000)  /* Receive own disable */
#define EMAC_MACCR_LM      ((uint32_t)0x00001000)  /* loopback mode */
#define EMAC_MACCR_DM      ((uint32_t)0x00000800)  /* Duplex mode */
#define EMAC_MACCR_IPCO    ((uint32_t)0x00000400)  /* IP Checksum offload */
#define EMAC_MACCR_RD      ((uint32_t)0x00000200)  /* Retry disable */
#define EMAC_MACCR_APCS    ((uint32_t)0x00000080)  /* Automatic Pad/CRC stripping */
#define EMAC_MACCR_BL      ((uint32_t)0x00000060)  /* Back-off limit: random integer number (r) of slot time delays before rescheduling
														a transmission attempt during retries after a collision: 0 =< r <2^k */
#define EMAC_MACCR_BL_10    ((uint32_t)0x00000000)  /* k = min (n, 10) */
#define EMAC_MACCR_BL_8     ((uint32_t)0x00000020)  /* k = min (n, 8) */
#define EMAC_MACCR_BL_4     ((uint32_t)0x00000040)  /* k = min (n, 4) */
#define EMAC_MACCR_BL_1     ((uint32_t)0x00000060)  /* k = min (n, 1) */
#define EMAC_MACCR_DC      ((uint32_t)0x00000010)  /* Defferal check */
#define EMAC_MACCR_TE      ((uint32_t)0x00000008)  /* Transmitter enable */
#define EMAC_MACCR_RE      ((uint32_t)0x00000004)  /* Receiver enable */

        /* Bit definition for Ethernet MAC Frame Filter Register */
#define EMAC_MACFFR_RA     ((uint32_t)0x80000000)  /* Receive all */
#define EMAC_MACFFR_HPF    ((uint32_t)0x00000400)  /* Hash or perfect filter */
#define EMAC_MACFFR_SAF    ((uint32_t)0x00000200)  /* Source address filter enable */
#define EMAC_MACFFR_SAIF   ((uint32_t)0x00000100)  /* SA inverse filtering */
#define EMAC_MACFFR_PCF    ((uint32_t)0x000000C0)  /* Pass control frames: 3 cases */
#define EMAC_MACFFR_PCF_BlockAll                ((uint32_t)0x00000040)  /* MAC filters all control frames from reaching the application */
#define EMAC_MACFFR_PCF_ForwardAll              ((uint32_t)0x00000080)  /* MAC forwards all control frames to application even if they fail the Address Filter */
#define EMAC_MACFFR_PCF_ForwardPassedAddrFilter ((uint32_t)0x000000C0)  /* MAC forwards control frames that pass the Address Filter. */
#define EMAC_MACFFR_BFD    ((uint32_t)0x00000020)  /* Broadcast frame disable */
#define EMAC_MACFFR_PAM 	  ((uint32_t)0x00000010)  /* Pass all mutlicast */
#define EMAC_MACFFR_DAIF   ((uint32_t)0x00000008)  /* DA Inverse filtering */
#define EMAC_MACFFR_HM     ((uint32_t)0x00000004)  /* Hash multicast */
#define EMAC_MACFFR_HU     ((uint32_t)0x00000002)  /* Hash unicast */
#define EMAC_MACFFR_PM     ((uint32_t)0x00000001)  /* Promiscuous mode */

        /* Bit definition for Ethernet MAC Hash Table High Register */
#define EMAC_MACHTHR_HTH   ((uint32_t)0xFFFFFFFF)  /* Hash table high */

        /* Bit definition for Ethernet MAC Hash Table Low Register */
#define EMAC_MACHTLR_HTL   ((uint32_t)0xFFFFFFFF)  /* Hash table low */

        /* Bit definition for Ethernet MAC MII Address Register */
#define EMAC_MACMIIAR_PA   ((uint32_t)0x0000F800)  /* Physical layer address */
#define EMAC_MACMIIAR_MR   ((uint32_t)0x000007C0)  /* MII register in the selected PHY */
#define EMAC_MACMIIAR_CR   ((uint32_t)0x0000001C)  /* CR clock range: 6 cases */
#define EMAC_MACMIIAR_CR_Div42   ((uint32_t)0x00000000)  /* HCLK:60-100 MHz; MDC clock= HCLK/42 */
#define EMAC_MACMIIAR_CR_Div62   ((uint32_t)0x00000004)  /* HCLK:100-150 MHz; MDC clock= HCLK/62 */
#define EMAC_MACMIIAR_CR_Div16   ((uint32_t)0x00000008)  /* HCLK:20-35 MHz; MDC clock= HCLK/16 */
#define EMAC_MACMIIAR_CR_Div26   ((uint32_t)0x0000000C)  /* HCLK:35-60 MHz; MDC clock= HCLK/26 */
#define EMAC_MACMIIAR_CR_Div102  ((uint32_t)0x00000010)  /* HCLK:150-250 MHz; MDC clock= HCLK/102 */
#define EMAC_MACMIIAR_CR_Div122  ((uint32_t)0x00000014)  /* HCLK:250-300 MHz; MDC clock= HCLK/122*/
#define EMAC_MACMIIAR_MW   ((uint32_t)0x00000002)  /* MII write */
#define EMAC_MACMIIAR_MB   ((uint32_t)0x00000001)  /* MII busy */

        /* Bit definition for Ethernet MAC MII Data Register */
#define EMAC_MACMIIDR_MD   ((uint32_t)0x0000FFFF)  /* MII data: read/write data from/to PHY */

        /* Bit definition for Ethernet MAC Flow Control Register */
#define EMAC_MACFCR_PT     ((uint32_t)0xFFFF0000)  /* Pause time */
#define EMAC_MACFCR_ZQPD   ((uint32_t)0x00000080)  /* Zero-quanta pause disable */
#define EMAC_MACFCR_PLT    ((uint32_t)0x00000030)  /* Pause low threshold: 4 cases */
#define EMAC_MACFCR_PLT_Minus4   ((uint32_t)0x00000000)  /* Pause time minus 4 slot times */
#define EMAC_MACFCR_PLT_Minus28  ((uint32_t)0x00000010)  /* Pause time minus 28 slot times */
#define EMAC_MACFCR_PLT_Minus144 ((uint32_t)0x00000020)  /* Pause time minus 144 slot times */
#define EMAC_MACFCR_PLT_Minus256 ((uint32_t)0x00000030)  /* Pause time minus 256 slot times */
#define EMAC_MACFCR_UPFD   ((uint32_t)0x00000008)  /* Unicast pause frame detect */
#define EMAC_MACFCR_RFCE   ((uint32_t)0x00000004)  /* Receive flow control enable */
#define EMAC_MACFCR_TFCE   ((uint32_t)0x00000002)  /* Transmit flow control enable */
#define EMAC_MACFCR_FCBBPA ((uint32_t)0x00000001)  /* Flow control busy/backpressure activate */

        /* Bit definition for Ethernet MAC VLAN Tag Register */
#define EMAC_MACVLANTR_VLANTC ((uint32_t)0x00010000)  /* 12-bit VLAN tag comparison */
#define EMAC_MACVLANTR_VLANTI ((uint32_t)0x0000FFFF)  /* VLAN tag identifier (for receive frames) */

        /* Bit definition for Ethernet MAC Remote Wake-UpFrame Filter Register */
#define EMAC_MACRWUFFR_D   ((uint32_t)0xFFFFFFFF)  /* Wake-up frame filter register data */
        /* Eight sequential Writes to this address (offset 0x28) will write all Wake-UpFrame Filter Registers.
           Eight sequential Reads from this address (offset 0x28) will read all Wake-UpFrame Filter Registers. */
        /* Wake-UpFrame Filter Reg0 : Filter 0 Byte Mask
           Wake-UpFrame Filter Reg1 : Filter 1 Byte Mask
           Wake-UpFrame Filter Reg2 : Filter 2 Byte Mask
           Wake-UpFrame Filter Reg3 : Filter 3 Byte Mask
           Wake-UpFrame Filter Reg4 : RSVD - Filter3 Command - RSVD - Filter2 Command -
                                      RSVD - Filter1 Command - RSVD - Filter0 Command
           Wake-UpFrame Filter Re5 : Filter3 Offset - Filter2 Offset - Filter1 Offset - Filter0 Offset
           Wake-UpFrame Filter Re6 : Filter1 CRC16 - Filter0 CRC16
           Wake-UpFrame Filter Re7 : Filter3 CRC16 - Filter2 CRC16 */

        /* Bit definition for Ethernet MAC PMT Control and Status Register */
#define EMAC_MACPMTCSR_WFFRPR ((uint32_t)0x80000000)  /* Wake-Up Frame Filter Register Pointer Reset */
#define EMAC_MACPMTCSR_GU     ((uint32_t)0x00000200)  /* Global Unicast */
#define EMAC_MACPMTCSR_WFR    ((uint32_t)0x00000040)  /* Wake-Up Frame Received */
#define EMAC_MACPMTCSR_MPR    ((uint32_t)0x00000020)  /* Magic Packet Received */
#define EMAC_MACPMTCSR_WFE    ((uint32_t)0x00000004)  /* Wake-Up Frame Enable */
#define EMAC_MACPMTCSR_MPE    ((uint32_t)0x00000002)  /* Magic Packet Enable */
#define EMAC_MACPMTCSR_PD     ((uint32_t)0x00000001)  /* Power Down */

        /* Bit definition for Ethernet MAC Status Register */
#define EMAC_MACSR_TSTS      ((uint32_t)0x00000200)  /* Time stamp trigger status */
#define EMAC_MACSR_MMCTS     ((uint32_t)0x00000040)  /* MMC transmit status */
#define EMAC_MACSR_MMMCRS    ((uint32_t)0x00000020)  /* MMC receive status */
#define EMAC_MACSR_MMCS      ((uint32_t)0x00000010)  /* MMC status */
#define EMAC_MACSR_PMTS      ((uint32_t)0x00000008)  /* PMT status */

        /* Bit definition for Ethernet MAC Interrupt Mask Register */
#define EMAC_MACIMR_TSTIM     ((uint32_t)0x00000200)  /* Time stamp trigger interrupt mask */
#define EMAC_MACIMR_PMTIM     ((uint32_t)0x00000008)  /* PMT interrupt mask */

        /* Bit definition for Ethernet MAC Address0 High Register */
#define EMAC_MACA0HR_MACA0H   ((uint32_t)0x0000FFFF)  /* MAC address0 high */

        /* Bit definition for Ethernet MAC Address0 Low Register */
#define EMAC_MACA0LR_MACA0L   ((uint32_t)0xFFFFFFFF)  /* MAC address0 low */

        /* Bit definition for Ethernet MAC Address1 High Register */
#define EMAC_MACA1HR_AE       ((uint32_t)0x80000000)  /* Address enable */
#define EMAC_MACA1HR_SA       ((uint32_t)0x40000000)  /* Source address */
#define EMAC_MACA1HR_MBC      ((uint32_t)0x3F000000)  /* Mask byte control: bits to mask for comparison of the MAC Address bytes */
#define EMAC_MACA1HR_MBC_HBits15_8    ((uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MACA1HR_MBC_HBits7_0     ((uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MACA1HR_MBC_LBits31_24   ((uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MACA1HR_MBC_LBits23_16   ((uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MACA1HR_MBC_LBits15_8    ((uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MACA1HR_MBC_LBits7_0     ((uint32_t)0x01000000)  /* Mask MAC Address low reg bits [7:0] */
#define EMAC_MACA1HR_MACA1H   ((uint32_t)0x0000FFFF)  /* MAC address1 high */

        /* Bit definition for Ethernet MAC Address1 Low Register */
#define EMAC_MACA1LR_MACA1L   ((uint32_t)0xFFFFFFFF)  /* MAC address1 low */

        /* Bit definition for Ethernet MAC Address2 High Register */
#define EMAC_MACA2HR_AE       ((uint32_t)0x80000000)  /* Address enable */
#define EMAC_MACA2HR_SA       ((uint32_t)0x40000000)  /* Source address */
#define EMAC_MACA2HR_MBC      ((uint32_t)0x3F000000)  /* Mask byte control */
#define EMAC_MACA2HR_MBC_HBits15_8    ((uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MACA2HR_MBC_HBits7_0     ((uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MACA2HR_MBC_LBits31_24   ((uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MACA2HR_MBC_LBits23_16   ((uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MACA2HR_MBC_LBits15_8    ((uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MACA2HR_MBC_LBits7_0     ((uint32_t)0x01000000)  /* Mask MAC Address low reg bits [70] */
#define EMAC_MACA2HR_MACA2H   ((uint32_t)0x0000FFFF)  /* MAC address1 high */

        /* Bit definition for Ethernet MAC Address2 Low Register */
#define EMAC_MACA2LR_MACA2L   ((uint32_t)0xFFFFFFFF)  /* MAC address2 low */

        /* Bit definition for Ethernet MAC Address3 High Register */
#define EMAC_MACA3HR_AE       ((uint32_t)0x80000000)  /* Address enable */
#define EMAC_MACA3HR_SA       ((uint32_t)0x40000000)  /* Source address */
#define EMAC_MACA3HR_MBC      ((uint32_t)0x3F000000)  /* Mask byte control */
#define EMAC_MACA3HR_MBC_HBits15_8    ((uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MACA3HR_MBC_HBits7_0     ((uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MACA3HR_MBC_LBits31_24   ((uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MACA3HR_MBC_LBits23_16   ((uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MACA3HR_MBC_LBits15_8    ((uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MACA3HR_MBC_LBits7_0     ((uint32_t)0x01000000)  /* Mask MAC Address low reg bits [70] */
#define EMAC_MACA3HR_MACA3H   ((uint32_t)0x0000FFFF)  /* MAC address3 high */

        /* Bit definition for Ethernet MAC Address3 Low Register */
#define EMAC_MACA3LR_MACA3L   ((uint32_t)0xFFFFFFFF)  /* MAC address3 low */

/******************************************************************************/
/*                Ethernet MMC Registers bits definition                      */
/******************************************************************************/

        /* Bit definition for Ethernet MMC Contol Register */
#define EMAC_MMCCR_MCF        ((uint32_t)0x00000008)  /* MMC Counter Freeze */
#define EMAC_MMCCR_ROR        ((uint32_t)0x00000004)  /* Reset on Read */
#define EMAC_MMCCR_CSR        ((uint32_t)0x00000002)  /* Counter Stop Rollover */
#define EMAC_MMCCR_CR         ((uint32_t)0x00000001)  /* Counters Reset */

        /* Bit definition for Ethernet MMC Receive Interrupt Register */
#define EMAC_MMCRIR_RGUFS     ((uint32_t)0x00020000)  /* Set when Rx good unicast frames counter reaches half the maximum value */
#define EMAC_MMCRIR_RFAES     ((uint32_t)0x00000040)  /* Set when Rx alignment error counter reaches half the maximum value */
#define EMAC_MMCRIR_RFCES     ((uint32_t)0x00000020)  /* Set when Rx crc error counter reaches half the maximum value */

        /* Bit definition for Ethernet MMC Transmit Interrupt Register */
#define EMAC_MMCTIR_TGFS      ((uint32_t)0x00200000)  /* Set when Tx good frame count counter reaches half the maximum value */
#define EMAC_MMCTIR_TGFMSCS   ((uint32_t)0x00008000)  /* Set when Tx good multi col counter reaches half the maximum value */
#define EMAC_MMCTIR_TGFSCS    ((uint32_t)0x00004000)  /* Set when Tx good single col counter reaches half the maximum value */

        /* Bit definition for Ethernet MMC Receive Interrupt Mask Register */
#define EMAC_MMCRIMR_RGUFM    ((uint32_t)0x00020000)  /* Mask the interrupt when Rx good unicast frames counter reaches half the maximum value */
#define EMAC_MMCRIMR_RFAEM    ((uint32_t)0x00000040)  /* Mask the interrupt when when Rx alignment error counter reaches half the maximum value */
#define EMAC_MMCRIMR_RFCEM    ((uint32_t)0x00000020)  /* Mask the interrupt when Rx crc error counter reaches half the maximum value */

        /* Bit definition for Ethernet MMC Transmit Interrupt Mask Register */
#define EMAC_MMCTIMR_TGFM     ((uint32_t)0x00200000)  /* Mask the interrupt when Tx good frame count counter reaches half the maximum value */
#define EMAC_MMCTIMR_TGFMSCM  ((uint32_t)0x00008000)  /* Mask the interrupt when Tx good multi col counter reaches half the maximum value */
#define EMAC_MMCTIMR_TGFSCM   ((uint32_t)0x00004000)  /* Mask the interrupt when Tx good single col counter reaches half the maximum value */

        /* Bit definition for Ethernet MMC Transmitted Good Frames after Single Collision Counter Register */
#define EMAC_MMCTGFSCCR_TGFSCC     ((uint32_t)0xFFFFFFFF)  /* Number of successfully transmitted frames after a single collision in Half-duplex mode. */

        /* Bit definition for Ethernet MMC Transmitted Good Frames after More than a Single Collision Counter Register */
#define EMAC_MMCTGFMSCCR_TGFMSCC   ((uint32_t)0xFFFFFFFF)  /* Number of successfully transmitted frames after more than a single collision in Half-duplex mode. */

        /* Bit definition for Ethernet MMC Transmitted Good Frames Counter Register */
#define EMAC_MMCTGFCR_TGFC    ((uint32_t)0xFFFFFFFF)  /* Number of good frames transmitted. */

        /* Bit definition for Ethernet MMC Received Frames with CRC Error Counter Register */
#define EMAC_MMCRFCECR_RFCEC  ((uint32_t)0xFFFFFFFF)  /* Number of frames received with CRC error. */

        /* Bit definition for Ethernet MMC Received Frames with Alignment Error Counter Register */
#define EMAC_MMCRFAECR_RFAEC  ((uint32_t)0xFFFFFFFF)  /* Number of frames received with alignment (dribble) error */

        /* Bit definition for Ethernet MMC Received Good Unicast Frames Counter Register */
#define EMAC_MMCRGUFCR_RGUFC  ((uint32_t)0xFFFFFFFF)  /* Number of good unicast frames received. */

/******************************************************************************/
/*               Ethernet PTP Registers bits definition                       */
/******************************************************************************/

        /* Bit definition for Ethernet PTP Time Stamp Control Register */
#define EMAC_PTPTSCR_TSARU    ((uint32_t)0x00000020)  /* Addend register update */
#define EMAC_PTPTSCR_TSITE    ((uint32_t)0x00000010)  /* Time stamp interrupt trigger enable */
#define EMAC_PTPTSCR_TSSTU    ((uint32_t)0x00000008)  /* Time stamp update */
#define EMAC_PTPTSCR_TSSTI    ((uint32_t)0x00000004)  /* Time stamp initialize */
#define EMAC_PTPTSCR_TSFCU    ((uint32_t)0x00000002)  /* Time stamp fine or coarse update */
#define EMAC_PTPTSCR_TSE      ((uint32_t)0x00000001)  /* Time stamp enable */

        /* Bit definition for Ethernet PTP Sub-Second Increment Register */
#define EMAC_PTPSSIR_STSSI    ((uint32_t)0x000000FF)  /* System time Sub-second increment value */

        /* Bit definition for Ethernet PTP Time Stamp High Register */
#define EMAC_PTPTSHR_STS      ((uint32_t)0xFFFFFFFF)  /* System Time second */

        /* Bit definition for Ethernet PTP Time Stamp Low Register */
#define EMAC_PTPTSLR_STPNS    ((uint32_t)0x80000000)  /* System Time Positive or negative time */
#define EMAC_PTPTSLR_STSS     ((uint32_t)0x7FFFFFFF)  /* System Time sub-seconds */

        /* Bit definition for Ethernet PTP Time Stamp High Update Register */
#define EMAC_PTPTSHUR_TSUS    ((uint32_t)0xFFFFFFFF)  /* Time stamp update seconds */

        /* Bit definition for Ethernet PTP Time Stamp Low Update Register */
#define EMAC_PTPTSLUR_TSUPNS  ((uint32_t)0x80000000)  /* Time stamp update Positive or negative time */
#define EMAC_PTPTSLUR_TSUSS   ((uint32_t)0x7FFFFFFF)  /* Time stamp update sub-seconds */

        /* Bit definition for Ethernet PTP Time Stamp Addend Register */
#define EMAC_PTPTSAR_TSA      ((uint32_t)0xFFFFFFFF)  /* Time stamp addend */

        /* Bit definition for Ethernet PTP Target Time High Register */
#define EMAC_PTPTTHR_TTSH     ((uint32_t)0xFFFFFFFF)  /* Target time stamp high */

        /* Bit definition for Ethernet PTP Target Time Low Register */
#define EMAC_PTPTTLR_TTSL     ((uint32_t)0xFFFFFFFF)  /* Target time stamp low */

/******************************************************************************/
/*                 Ethernet DMA Registers bits definition                     */
/******************************************************************************/

        /* Bit definition for Ethernet DMA Bus Mode Register */
#define EMAC_DMABMR_AAB       ((uint32_t)0x02000000)  /* Address-Aligned beats */
#define EMAC_DMABMR_FPM        ((uint32_t)0x01000000)  /* 4xPBL mode */
#define EMAC_DMABMR_USP       ((uint32_t)0x00800000)  /* Use separate PBL */
#define EMAC_DMABMR_RDP       ((uint32_t)0x007E0000)  /* RxDMA PBL */
#define EMAC_DMABMR_RDP_1Beat    ((uint32_t)0x00020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define EMAC_DMABMR_RDP_2Beat    ((uint32_t)0x00040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define EMAC_DMABMR_RDP_4Beat    ((uint32_t)0x00080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_DMABMR_RDP_8Beat    ((uint32_t)0x00100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_DMABMR_RDP_16Beat   ((uint32_t)0x00200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_DMABMR_RDP_32Beat   ((uint32_t)0x00400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_DMABMR_RDP_4xPBL_4Beat   ((uint32_t)0x01020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_DMABMR_RDP_4xPBL_8Beat   ((uint32_t)0x01040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_DMABMR_RDP_4xPBL_16Beat  ((uint32_t)0x01080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_DMABMR_RDP_4xPBL_32Beat  ((uint32_t)0x01100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_DMABMR_RDP_4xPBL_64Beat  ((uint32_t)0x01200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define EMAC_DMABMR_RDP_4xPBL_128Beat ((uint32_t)0x01400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 128 */
#define EMAC_DMABMR_FB        ((uint32_t)0x00010000)  /* Fixed Burst */
#define EMAC_DMABMR_RTPR      ((uint32_t)0x0000C000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_1_1     ((uint32_t)0x00000000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_2_1     ((uint32_t)0x00004000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_3_1     ((uint32_t)0x00008000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_4_1     ((uint32_t)0x0000C000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_PBL    ((uint32_t)0x00003F00)  /* Programmable burst length */
#define EMAC_DMABMR_PBL_1Beat    ((uint32_t)0x00000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define EMAC_DMABMR_PBL_2Beat    ((uint32_t)0x00000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define EMAC_DMABMR_PBL_4Beat    ((uint32_t)0x00000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_DMABMR_PBL_8Beat    ((uint32_t)0x00000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_DMABMR_PBL_16Beat   ((uint32_t)0x00001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_DMABMR_PBL_32Beat   ((uint32_t)0x00002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_DMABMR_PBL_4xPBL_4Beat   ((uint32_t)0x01000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_DMABMR_PBL_4xPBL_8Beat   ((uint32_t)0x01000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_DMABMR_PBL_4xPBL_16Beat  ((uint32_t)0x01000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_DMABMR_PBL_4xPBL_32Beat  ((uint32_t)0x01000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_DMABMR_PBL_4xPBL_64Beat  ((uint32_t)0x01001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define EMAC_DMABMR_PBL_4xPBL_128Beat ((uint32_t)0x01002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */
#define EMAC_DMABMR_EDE       ((uint32_t)0x00000080)  /* Enhanced Descriptor Enable */
#define EMAC_DMABMR_DSL       ((uint32_t)0x0000007C)  /* Descriptor Skip Length */
#define EMAC_DMABMR_DA        ((uint32_t)0x00000002)  /* DMA arbitration scheme */
#define EMAC_DMABMR_SR        ((uint32_t)0x00000001)  /* Software reset */

        /* Bit definition for Ethernet DMA Transmit Poll Demand Register */
#define EMAC_DMATPDR_TPD      ((uint32_t)0xFFFFFFFF)  /* Transmit poll demand */

        /* Bit definition for Ethernet DMA Receive Poll Demand Register */
#define EMAC_DMARPDR_RPD      ((uint32_t)0xFFFFFFFF)  /* Receive poll demand  */

        /* Bit definition for Ethernet DMA Receive Descriptor List Address Register */
#define EMAC_DMARDLAR_SRL     ((uint32_t)0xFFFFFFFF)  /* Start of receive list */

        /* Bit definition for Ethernet DMA Transmit Descriptor List Address Register */
#define EMAC_DMATDLAR_STL     ((uint32_t)0xFFFFFFFF)  /* Start of transmit list */

        /* Bit definition for Ethernet DMA Status Register */
#define EMAC_DMASR_TSTS       ((uint32_t)0x20000000)  /* Time-stamp trigger status */
#define EMAC_DMASR_PMTS       ((uint32_t)0x10000000)  /* PMT status */
#define EMAC_DMASR_MMCS       ((uint32_t)0x08000000)  /* MMC status */
#define EMAC_DMASR_EBS        ((uint32_t)0x03800000)  /* Error bits status */
        /* combination with EBS[2:0] for GetFlagStatus function */
#define EMAC_DMASR_EBS_DescAccess      ((uint32_t)0x02000000)  /* Error bits 0-data buffer, 1-desc. access */
#define EMAC_DMASR_EBS_ReadTransf      ((uint32_t)0x01000000)  /* Error bits 0-write transfer, 1-read transfer */
#define EMAC_DMASR_EBS_DataTransfTx    ((uint32_t)0x00800000)  /* Error bits 0-Rx DMA, 1-Tx DMA */
#define EMAC_DMASR_TPS         ((uint32_t)0x00700000)  /* Transmit process state */
#define EMAC_DMASR_TPS_Stopped         ((uint32_t)0x00000000)  /* Stopped - Reset or Stop Tx Command issued  */
#define EMAC_DMASR_TPS_Fetching        ((uint32_t)0x00100000)  /* Running - fetching the Tx descriptor */
#define EMAC_DMASR_TPS_Waiting         ((uint32_t)0x00200000)  /* Running - waiting for status */
#define EMAC_DMASR_TPS_Reading         ((uint32_t)0x00300000)  /* Running - reading the data from host memory */
#define EMAC_DMASR_TPS_Suspended       ((uint32_t)0x00600000)  /* Suspended - Tx Descriptor unavailable */
#define EMAC_DMASR_TPS_Closing         ((uint32_t)0x00700000)  /* Running - closing Rx descriptor */
#define EMAC_DMASR_RPS         ((uint32_t)0x000E0000)  /* Receive process state */
#define EMAC_DMASR_RPS_Stopped         ((uint32_t)0x00000000)  /* Stopped - Reset or Stop Rx Command issued */
#define EMAC_DMASR_RPS_Fetching        ((uint32_t)0x00020000)  /* Running - fetching the Rx descriptor */
#define EMAC_DMASR_RPS_Waiting         ((uint32_t)0x00060000)  /* Running - waiting for packet */
#define EMAC_DMASR_RPS_Suspended       ((uint32_t)0x00080000)  /* Suspended - Rx Descriptor unavailable */
#define EMAC_DMASR_RPS_Closing         ((uint32_t)0x000A0000)  /* Running - closing descriptor */
#define EMAC_DMASR_RPS_Queuing         ((uint32_t)0x000E0000)  /* Running - queuing the receive frame into host memory */
#define EMAC_DMASR_NIS        ((uint32_t)0x00010000)  /* Normal interrupt summary */
#define EMAC_DMASR_AIS        ((uint32_t)0x00008000)  /* Abnormal interrupt summary */
#define EMAC_DMASR_ERS        ((uint32_t)0x00004000)  /* Early receive status */
#define EMAC_DMASR_FBES       ((uint32_t)0x00002000)  /* Fatal bus error status */
#define EMAC_DMASR_ETS        ((uint32_t)0x00000400)  /* Early transmit status */
#define EMAC_DMASR_RWTS       ((uint32_t)0x00000200)  /* Receive watchdog timeout status */
#define EMAC_DMASR_RPSS       ((uint32_t)0x00000100)  /* Receive process stopped status */
#define EMAC_DMASR_RBUS       ((uint32_t)0x00000080)  /* Receive buffer unavailable status */
#define EMAC_DMASR_RS         ((uint32_t)0x00000040)  /* Receive status */
#define EMAC_DMASR_TUS        ((uint32_t)0x00000020)  /* Transmit underflow status */
#define EMAC_DMASR_ROS        ((uint32_t)0x00000010)  /* Receive overflow status */
#define EMAC_DMASR_TJTS       ((uint32_t)0x00000008)  /* Transmit jabber timeout status */
#define EMAC_DMASR_TBUS       ((uint32_t)0x00000004)  /* Transmit buffer unavailable status */
#define EMAC_DMASR_TPSS       ((uint32_t)0x00000002)  /* Transmit process stopped status */
#define EMAC_DMASR_TS         ((uint32_t)0x00000001)  /* Transmit status */

        /* Bit definition for Ethernet DMA Operation Mode Register */
#define EMAC_DMAOMR_DTCEFD    ((uint32_t)0x04000000)  /* Disable Dropping of TCP/IP checksum error frames */
#define EMAC_DMAOMR_RSF       ((uint32_t)0x02000000)  /* Receive store and forward */
#define EMAC_DMAOMR_DFRF      ((uint32_t)0x01000000)  /* Disable flushing of received frames */
#define EMAC_DMAOMR_TSF       ((uint32_t)0x00200000)  /* Transmit store and forward */
#define EMAC_DMAOMR_FTF       ((uint32_t)0x00100000)  /* Flush transmit FIFO */
#define EMAC_DMAOMR_TTC       ((uint32_t)0x0001C000)  /* Transmit threshold control */
#define EMAC_DMAOMR_TTC_64Bytes       ((uint32_t)0x00000000)  /* threshold level of the MTL Transmit FIFO is 64 Bytes */
#define EMAC_DMAOMR_TTC_128Bytes      ((uint32_t)0x00004000)  /* threshold level of the MTL Transmit FIFO is 128 Bytes */
#define EMAC_DMAOMR_TTC_192Bytes      ((uint32_t)0x00008000)  /* threshold level of the MTL Transmit FIFO is 192 Bytes */
#define EMAC_DMAOMR_TTC_256Bytes      ((uint32_t)0x0000C000)  /* threshold level of the MTL Transmit FIFO is 256 Bytes */
#define EMAC_DMAOMR_TTC_40Bytes       ((uint32_t)0x00010000)  /* threshold level of the MTL Transmit FIFO is 40 Bytes */
#define EMAC_DMAOMR_TTC_32Bytes       ((uint32_t)0x00014000)  /* threshold level of the MTL Transmit FIFO is 32 Bytes */
#define EMAC_DMAOMR_TTC_24Bytes       ((uint32_t)0x00018000)  /* threshold level of the MTL Transmit FIFO is 24 Bytes */
#define EMAC_DMAOMR_TTC_16Bytes       ((uint32_t)0x0001C000)  /* threshold level of the MTL Transmit FIFO is 16 Bytes */
#define EMAC_DMAOMR_ST        ((uint32_t)0x00002000)  /* Start/stop transmission command */
#define EMAC_DMAOMR_FEF       ((uint32_t)0x00000080)  /* Forward error frames */
#define EMAC_DMAOMR_FUGF      ((uint32_t)0x00000040)  /* Forward undersized good frames */
#define EMAC_DMAOMR_RTC       ((uint32_t)0x00000018)  /* receive threshold control */
#define EMAC_DMAOMR_RTC_64Bytes       ((uint32_t)0x00000000)  /* threshold level of the MTL Receive FIFO is 64 Bytes */
#define EMAC_DMAOMR_RTC_32Bytes       ((uint32_t)0x00000008)  /* threshold level of the MTL Receive FIFO is 32 Bytes */
#define EMAC_DMAOMR_RTC_96Bytes       ((uint32_t)0x00000010)  /* threshold level of the MTL Receive FIFO is 96 Bytes */
#define EMAC_DMAOMR_RTC_128Bytes      ((uint32_t)0x00000018)  /* threshold level of the MTL Receive FIFO is 128 Bytes */
#define EMAC_DMAOMR_OSF       ((uint32_t)0x00000004)  /* operate on second frame */
#define EMAC_DMAOMR_SR        ((uint32_t)0x00000002)  /* Start/stop receive */

        /* Bit definition for Ethernet DMA Interrupt Enable Register */
#define EMAC_DMAIER_NISE      ((uint32_t)0x00010000)  /* Normal interrupt summary enable */
#define EMAC_DMAIER_AISE      ((uint32_t)0x00008000)  /* Abnormal interrupt summary enable */
#define EMAC_DMAIER_ERIE      ((uint32_t)0x00004000)  /* Early receive interrupt enable */
#define EMAC_DMAIER_FBEIE     ((uint32_t)0x00002000)  /* Fatal bus error interrupt enable */
#define EMAC_DMAIER_ETIE      ((uint32_t)0x00000400)  /* Early transmit interrupt enable */
#define EMAC_DMAIER_RWTIE     ((uint32_t)0x00000200)  /* Receive watchdog timeout interrupt enable */
#define EMAC_DMAIER_RPSIE     ((uint32_t)0x00000100)  /* Receive process stopped interrupt enable */
#define EMAC_DMAIER_RBUIE     ((uint32_t)0x00000080)  /* Receive buffer unavailable interrupt enable */
#define EMAC_DMAIER_RIE       ((uint32_t)0x00000040)  /* Receive interrupt enable */
#define EMAC_DMAIER_TUIE      ((uint32_t)0x00000020)  /* Transmit Underflow interrupt enable */
#define EMAC_DMAIER_ROIE      ((uint32_t)0x00000010)  /* Receive Overflow interrupt enable */
#define EMAC_DMAIER_TJTIE     ((uint32_t)0x00000008)  /* Transmit jabber timeout interrupt enable */
#define EMAC_DMAIER_TBUIE     ((uint32_t)0x00000004)  /* Transmit buffer unavailable interrupt enable */
#define EMAC_DMAIER_TPSIE     ((uint32_t)0x00000002)  /* Transmit process stopped interrupt enable */
#define EMAC_DMAIER_TIE       ((uint32_t)0x00000001)  /* Transmit interrupt enable */

        /* Bit definition for Ethernet DMA Missed Frame and Buffer Overflow Counter Register */
#define EMAC_DMAMFBOCR_OFOC   ((uint32_t)0x10000000)  /* Overflow bit for FIFO overflow counter */
#define EMAC_DMAMFBOCR_MFA    ((uint32_t)0x0FFE0000)  /* Number of frames missed by the application */
#define EMAC_DMAMFBOCR_OMFC   ((uint32_t)0x00010000)  /* Overflow bit for missed frame counter */
#define EMAC_DMAMFBOCR_MFC    ((uint32_t)0x0000FFFF)  /* Number of frames missed by the controller */

        /* Bit definition for Ethernet DMA Current Host Transmit Descriptor Register */
#define EMAC_DMACHTDR_HTDAP   ((uint32_t)0xFFFFFFFF)  /* Host transmit descriptor address pointer */

        /* Bit definition for Ethernet DMA Current Host Receive Descriptor Register */
#define EMAC_DMACHRDR_HRDAP   ((uint32_t)0xFFFFFFFF)  /* Host receive descriptor address pointer */

        /* Bit definition for Ethernet DMA Current Host Transmit Buffer Address Register */
#define EMAC_DMACHTBAR_HTBAP  ((uint32_t)0xFFFFFFFF)  /* Host transmit buffer address pointer */

        /* Bit definition for Ethernet DMA Current Host Receive Buffer Address Register */
#define EMAC_DMACHRBAR_HRBAP  ((uint32_t)0xFFFFFFFF)  /* Host receive buffer address pointer */

//typedef enum {
//	RESET = 0, SET = !RESET
//} FlagStatus, ITStatus;
//typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

/**
  * ETH MAC Init structure definition
  */
typedef struct
{
    /**
     * MAC
     */
    uint32_t             EMAC_AutoNegotiation;           /* Selects or not the AutoNegotiation mode for the external PHY
                                                           The AutoNegotiation allows an automatic setting of the Speed (10/100Mbps)
                                                           and the mode (half/full-duplex).
                                                           This parameter can be a value of @ref EMAC_AutoNegotiation */

    uint32_t             EMAC_Watchdog;                  /* Selects or not the Watchdog timer
                                                           When enabled, the MAC allows no more then 2048 bytes to be received.
                                                           When disabled, the MAC can receive up to 16384 bytes.
                                                           This parameter can be a value of @ref EMAC_watchdog */

    uint32_t             EMAC_Jabber;                    /* Selects or not Jabber timer
                                                           When enabled, the MAC allows no more then 2048 bytes to be sent.
                                                           When disabled, the MAC can send up to 16384 bytes.
                                                           This parameter can be a value of @ref EMAC_Jabber */

    uint32_t             EMAC_InterFrameGap;             /* Selects the minimum IFG between frames during transmission
                                                           This parameter can be a value of @ref EMAC_Inter_Frame_Gap */

    uint32_t             EMAC_CarrierSense;              /* Selects or not the Carrier Sense
                                                           This parameter can be a value of @ref EMAC_Carrier_Sense */

    uint32_t             EMAC_Speed;                     /* Sets the Ethernet speed: 10/100 Mbps
                                                           This parameter can be a value of @ref EMAC_Speed */

    uint32_t             EMAC_ReceiveOwn;                /* Selects or not the ReceiveOwn
                                                           ReceiveOwn allows the reception of frames when the TX_EN signal is asserted
                                                           in Half-Duplex mode
                                                           This parameter can be a value of @ref EMAC_Receive_Own */

    uint32_t             EMAC_LoopbackMode;              /* Selects or not the internal MAC MII Loopback mode
                                                           This parameter can be a value of @ref EMAC_Loop_Back_Mode */

    uint32_t             EMAC_Mode;                      /* Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode
                                                           This parameter can be a value of @ref EMAC_Duplex_Mode */

    uint32_t             EMAC_ChecksumOffload;           /* Selects or not the IPv4 checksum checking for received frame payloads' TCP/UDP/ICMP headers.
                                                           This parameter can be a value of @ref EMAC_Checksum_Offload */

    uint32_t             EMAC_RetryTransmission;         /* Selects or not the MAC attempt retries transmission, based on the settings of BL,
                                                           when a colision occurs (Half-Duplex mode)
                                                           This parameter can be a value of @ref EMAC_Retry_Transmission */

    uint32_t             EMAC_AutomaticPadCRCStrip;      /* Selects or not the Automatic MAC Pad/CRC Stripping
                                                           This parameter can be a value of @ref EMAC_Automatic_Pad_CRC_Strip */

    uint32_t             EMAC_BackOffLimit;              /* Selects the BackOff limit value
                                                           This parameter can be a value of @ref EMAC_Back_Off_Limit */

    uint32_t             EMAC_DeferralCheck;             /* Selects or not the deferral check function (Half-Duplex mode)
                                                           This parameter can be a value of @ref EMAC_Deferral_Check */

    uint32_t             EMAC_ReceiveAll;                /* Selects or not all frames reception by the MAC (No fitering)
                                                           This parameter can be a value of @ref EMAC_Receive_All */

    uint32_t             EMAC_SourceAddrFilter;          /* Selects the Source Address Filter mode
                                                           This parameter can be a value of @ref EMAC_Source_Addr_Filter */

    uint32_t             EMAC_PassControlFrames;         /* Sets the forwarding mode of the control frames (including unicast and multicast PAUSE frames)
                                                           This parameter can be a value of @ref EMAC_Pass_Control_Frames */

    uint32_t             EMAC_BroadcastFramesReception;  /* Selects or not the reception of Broadcast Frames
                                                           This parameter can be a value of @ref EMAC_Broadcast_Frames_Reception */

    uint32_t             EMAC_DestinationAddrFilter;     /* Sets the destination filter mode for both unicast and multicast frames
                                                           This parameter can be a value of @ref EMAC_Destination_Addr_Filter */

    uint32_t             EMAC_PromiscuousMode;           /* Selects or not the Promiscuous Mode
                                                           This parameter can be a value of @ref EMAC_Promiscuous_Mode */

    uint32_t             EMAC_MulticastFramesFilter;     /* Selects the Multicast Frames filter mode: None/HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                                           This parameter can be a value of @ref EMAC_Multicast_Frames_Filter */

    uint32_t             EMAC_UnicastFramesFilter;       /* Selects the Unicast Frames filter mode: HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                                           This parameter can be a value of @ref EMAC_Unicast_Frames_Filter */

    uint32_t             EMAC_HashTableHigh;             /* This field holds the higher 32 bits of Hash table.  */

    uint32_t             EMAC_HashTableLow;              /* This field holds the lower 32 bits of Hash table.  */

    uint32_t             EMAC_PauseTime;                 /* This field holds the value to be used in the Pause Time field in the
                                                           transmit control frame */

    uint32_t             EMAC_ZeroQuantaPause;           /* Selects or not the automatic generation of Zero-Quanta Pause Control frames
                                                           This parameter can be a value of @ref EMAC_Zero_Quanta_Pause */

    uint32_t             EMAC_PauseLowThreshold;         /* This field configures the threshold of the PAUSE to be checked for
                                                           automatic retransmission of PAUSE Frame
                                                           This parameter can be a value of @ref EMAC_Pause_Low_Threshold */

    uint32_t             EMAC_UnicastPauseFrameDetect;   /* Selects or not the MAC detection of the Pause frames (with MAC Address0
                                                           unicast address and unique multicast address)
                                                           This parameter can be a value of @ref EMAC_Unicast_Pause_Frame_Detect */

    uint32_t             EMAC_ReceiveFlowControl;        /* Enables or disables the MAC to decode the received Pause frame and
                                                           disable its transmitter for a specified time (Pause Time)
                                                           This parameter can be a value of @ref EMAC_Receive_Flow_Control */

    uint32_t             EMAC_TransmitFlowControl;       /* Enables or disables the MAC to transmit Pause frames (Full-Duplex mode)
                                                           or the MAC back-pressure operation (Half-Duplex mode)
                                                           This parameter can be a value of @ref EMAC_Transmit_Flow_Control */

    uint32_t             EMAC_VLANTagComparison;         /* Selects the 12-bit VLAN identifier or the complete 16-bit VLAN tag for
                                                           comparison and filtering
                                                           This parameter can be a value of @ref EMAC_VLAN_Tag_Comparison */

    uint32_t             EMAC_VLANTagIdentifier;         /* Holds the VLAN tag identifier for receive frames */

    /**
     * DMA
     */

    uint32_t             EMAC_DropTCPIPChecksumErrorFrame; /* Selects or not the Dropping of TCP/IP Checksum Error Frames
                                                             This parameter can be a value of @ref EMAC_Drop_TCP_IP_Checksum_Error_Frame */

    uint32_t             EMAC_ReceiveStoreForward;         /* Enables or disables the Receive store and forward mode
                                                             This parameter can be a value of @ref EMAC_Receive_Store_Forward */

    uint32_t             EMAC_FlushReceivedFrame;          /* Enables or disables the flushing of received frames
                                                             This parameter can be a value of @ref EMAC_Flush_Received_Frame */

    uint32_t             EMAC_TransmitStoreForward;        /* Enables or disables Transmit store and forward mode
                                                             This parameter can be a value of @ref EMAC_Transmit_Store_Forward */

    uint32_t             EMAC_TransmitThresholdControl;    /* Selects or not the Transmit Threshold Control
                                                             This parameter can be a value of @ref EMAC_Transmit_Threshold_Control */

    uint32_t             EMAC_ForwardErrorFrames;          /* Selects or not the forward to the DMA of erroneous frames
                                                             This parameter can be a value of @ref EMAC_Forward_Error_Frames */

    uint32_t             EMAC_ForwardUndersizedGoodFrames; /* Enables or disables the Rx FIFO to forward Undersized frames (frames with no Error
                                                             and length less than 64 bytes) including pad-bytes and CRC)
                                                             This parameter can be a value of @ref EMAC_Forward_Undersized_Good_Frames */

    uint32_t             EMAC_ReceiveThresholdControl;     /* Selects the threshold level of the Receive FIFO
                                                             This parameter can be a value of @ref EMAC_Receive_Threshold_Control */

    uint32_t             EMAC_SecondFrameOperate;          /* Selects or not the Operate on second frame mode, which allows the DMA to process a second
                                                             frame of Transmit data even before obtaining the status for the first frame.
                                                             This parameter can be a value of @ref EMAC_Second_Frame_Operate */

    uint32_t             EMAC_AddressAlignedBeats;         /* Enables or disables the Address Aligned Beats
                                                             This parameter can be a value of @ref EMAC_Address_Aligned_Beats */

    uint32_t             EMAC_FixedBurst;                  /* Enables or disables the AHB Master interface fixed burst transfers
                                                             This parameter can be a value of @ref EMAC_Fixed_Burst */

    uint32_t             EMAC_RxDMABurstLength;            /* Indicates the maximum number of beats to be transferred in one Rx DMA transaction
                                                             This parameter can be a value of @ref EMAC_Rx_DMA_Burst_Length */

    uint32_t             EMAC_TxDMABurstLength;            /* Indicates sthe maximum number of beats to be transferred in one Tx DMA transaction
                                                             This parameter can be a value of @ref EMAC_Tx_DMA_Burst_Length */

    uint32_t             EMAC_DescriptorSkipLength;        /* Specifies the number of word to skip between two unchained int (Ring mode) */

    uint32_t             EMAC_DMAArbitration;              /* Selects the DMA Tx/Rx arbitration
                                                             This parameter can be a value of @ref EMAC_DMA_Arbitration */
} EMAC_InitTypeDef;

/**--------------------------------------------------------------------------**/
/**
  *                            DMA int types
  */
/**--------------------------------------------------------------------------**/

/**
  * ETH DMA Descriptors data structure definition
  */
typedef struct
{
    uint32_t   Status;                /* Status */
    uint32_t   ControlBufferSize;     /* Control and Buffer1, Buffer2 lengths */
    uint32_t   Buffer1Addr;           /* Buffer1 address pointer */
    uint32_t   Buffer2NextDescAddr;   /* Buffer2 or next descriptor address pointer */
} EMAC_DMADESCTypeDef;

/**--------------------------------------------------------------------------**/
/**
  *                           ETH Frames defines
  */
/**--------------------------------------------------------------------------**/

#define EMAC_MAX_PACKET_SIZE    	1520    /* EMAC_HEADER + EMAC_EXTRA + MAX_EMAC_PAYLOAD + EMAC_CRC */
#define EMAC_HEADER               	14    	/* 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define EMAC_CRC                   	4    	/* Ethernet CRC */
#define EMAC_EXTRA                 	2    	/* Extra bytes in some cases */
#define VLAN_TAG                  	4    	/* optional 802.1q VLAN Tag */
#define MIN_EMAC_PAYLOAD          	46    	/* Minimum Ethernet payload size */
#define MAX_EMAC_PAYLOAD        	1500    /* Maximum Ethernet payload size */
#define JUMBO_FRAME_PAYLOAD    		9000    /* Jumbo frame payload size */

/**--------------------------------------------------------------------------**/
/**
 *                  Ethernet DMA int registers bits definition
 */
/**--------------------------------------------------------------------------**/

#define EMAC_DMATxDesc_OWN                     ((uint32_t)0x80000000)  /* OWN bit: descriptor is owned by DMA engine */
#define EMAC_DMATxDesc_IC                      ((uint32_t)0x40000000)  /* Interrupt on Completion */
#define EMAC_DMATxDesc_LS                      ((uint32_t)0x20000000)  /* Last Segment */
#define EMAC_DMATxDesc_FS                      ((uint32_t)0x10000000)  /* First Segment */
#define EMAC_DMATxDesc_DC                      ((uint32_t)0x08000000)  /* Disable CRC */
#define EMAC_DMATxDesc_DP                      ((uint32_t)0x04000000)  /* Disable Padding */
#define EMAC_DMATxDesc_TTSE                    ((uint32_t)0x02000000)  /* Transmit Time Stamp Enable */
#define EMAC_DMATxDesc_CIC                     ((uint32_t)0x00C00000)  /* Checksum Insertion Control: 4 cases */
#define EMAC_DMATxDesc_CIC_ByPass              ((uint32_t)0x00000000)  /* Do Nothing: Checksum Engine is bypassed */
#define EMAC_DMATxDesc_CIC_IPV4Header          ((uint32_t)0x00400000)  /* IPV4 header Checksum Insertion */
#define EMAC_DMATxDesc_CIC_TCPUDPICMP_Segment  ((uint32_t)0x00800000)  /* TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define EMAC_DMATxDesc_CIC_TCPUDPICMP_Full     ((uint32_t)0x00C00000)  /* TCP/UDP/ICMP Checksum Insertion fully calculated */
#define EMAC_DMATxDesc_TER                     ((uint32_t)0x00200000)  /* Transmit End of Ring */
#define EMAC_DMATxDesc_TCH                     ((uint32_t)0x00100000)  /* Second Address Chained */
#define EMAC_DMATxDesc_TTSS                    ((uint32_t)0x00020000)  /* Tx Time Stamp Status */
#define EMAC_DMATxDesc_IHE                     ((uint32_t)0x00010000)  /* IP Header Error */
#define EMAC_DMATxDesc_ES                      ((uint32_t)0x00008000)  /* Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF || JT */
#define EMAC_DMATxDesc_JT                      ((uint32_t)0x00004000)  /* Jabber Timeout */
#define EMAC_DMATxDesc_FF                      ((uint32_t)0x00002000)  /* Frame Flushed: DMA/MTL flushed the frame due to SW flush */
#define EMAC_DMATxDesc_PCE                     ((uint32_t)0x00001000)  /* Payload Checksum Error */
#define EMAC_DMATxDesc_LCA                     ((uint32_t)0x00000800)  /* Loss of Carrier: carrier lost during transmission */
#define EMAC_DMATxDesc_NC                      ((uint32_t)0x00000400)  /* No Carrier: no carrier signal from the transceiver */
#define EMAC_DMATxDesc_LCO                     ((uint32_t)0x00000200)  /* Late Collision: transmission aborted due to collision */
#define EMAC_DMATxDesc_EC                      ((uint32_t)0x00000100)  /* Excessive Collision: transmission aborted after 16 collisions */
#define EMAC_DMATxDesc_VF                      ((uint32_t)0x00000080)  /* VLAN Frame */
#define EMAC_DMATxDesc_CC                      ((uint32_t)0x00000078)  /* Collision Count */
#define EMAC_DMATxDesc_ED                      ((uint32_t)0x00000004)  /* Excessive Deferral */
#define EMAC_DMATxDesc_UF                      ((uint32_t)0x00000002)  /* Underflow Error: late data arrival from the memory */
#define EMAC_DMATxDesc_DB                      ((uint32_t)0x00000001)  /* Deferred Bit */

#define EMAC_DMATxDesc_TBS2  ((uint32_t)0x1FFF0000)  /* Transmit Buffer2 Size */
#define EMAC_DMATxDesc_TBS1  ((uint32_t)0x00001FFF)  /* Transmit Buffer1 Size */

#define EMAC_DMATxDesc_B1AP  ((uint32_t)0xFFFFFFFF)  /* Buffer1 Address Pointer */

#define EMAC_DMATxDesc_B2AP  ((uint32_t)0xFFFFFFFF)  /* Buffer2 Address Pointer */

#define EMAC_DMARxDesc_OWN         ((uint32_t)0x80000000)  /* OWN bit: descriptor is owned by DMA engine  */
#define EMAC_DMARxDesc_AFM         ((uint32_t)0x40000000)  /* DA Filter Fail for the rx frame  */
#define EMAC_DMARxDesc_FL          ((uint32_t)0x3FFF0000)  /* Receive descriptor frame length  */
#define EMAC_DMARxDesc_ES          ((uint32_t)0x00008000)  /* Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE */
#define EMAC_DMARxDesc_DE          ((uint32_t)0x00004000)  /* Descriptor error: no more int for receive frame  */
#define EMAC_DMARxDesc_SAF         ((uint32_t)0x00002000)  /* SA Filter Fail for the received frame */
#define EMAC_DMARxDesc_LE          ((uint32_t)0x00001000)  /* Frame size not matching with length field */
#define EMAC_DMARxDesc_OE          ((uint32_t)0x00000800)  /* Overflow Error: Frame was damaged due to buffer overflow */
#define EMAC_DMARxDesc_VLAN        ((uint32_t)0x00000400)  /* VLAN Tag: received frame is a VLAN frame */
#define EMAC_DMARxDesc_FS          ((uint32_t)0x00000200)  /* First descriptor of the frame  */
#define EMAC_DMARxDesc_LS          ((uint32_t)0x00000100)  /* Last descriptor of the frame  */
#define EMAC_DMARxDesc_IPV4HCE     ((uint32_t)0x00000080)  /* IPC Checksum Error: Rx Ipv4 header checksum error   */
#define EMAC_DMARxDesc_LC          ((uint32_t)0x00000040)  /* Late collision occurred during reception   */
#define EMAC_DMARxDesc_FT          ((uint32_t)0x00000020)  /* Frame type - Ethernet, otherwise 802.3    */
#define EMAC_DMARxDesc_RWT         ((uint32_t)0x00000010)  /* Receive Watchdog Timeout: watchdog timer expired during reception    */
#define EMAC_DMARxDesc_RE          ((uint32_t)0x00000008)  /* Receive error: error reported by MII interface  */
#define EMAC_DMARxDesc_DBE         ((uint32_t)0x00000004)  /* Dribble bit error: frame contains non int multiple of 8 bits  */
#define EMAC_DMARxDesc_CE          ((uint32_t)0x00000002)  /* CRC error */
#define EMAC_DMARxDesc_MAMPCE      ((uint32_t)0x00000001)  /* Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error */

#define EMAC_DMARxDesc_DIC   ((uint32_t)0x80000000)  /* Disable Interrupt on Completion */
#define EMAC_DMARxDesc_RBS2  ((uint32_t)0x1FFF0000)  /* Receive Buffer2 Size */
#define EMAC_DMARxDesc_RER   ((uint32_t)0x00008000)  /* Receive End of Ring */
#define EMAC_DMARxDesc_RCH   ((uint32_t)0x00004000)  /* Second Address Chained */
#define EMAC_DMARxDesc_RBS1  ((uint32_t)0x00001FFF)  /* Receive Buffer1 Size */

#define EMAC_DMARxDesc_B1AP  ((uint32_t)0xFFFFFFFF)  /* Buffer1 Address Pointer */

#define EMAC_DMARxDesc_B2AP  ((uint32_t)0xFFFFFFFF)  /* Buffer2 Address Pointer */

#define PHY_READ_TO                     ((uint32_t)0x0004FFFF)
#define PHY_WRITE_TO                    ((uint32_t)0x0004FFFF)

#define PHY_ResetDelay                  ((uint32_t)0x000FFFFF)

#define PHY_ConfigDelay                 ((uint32_t)0x00FFFFFF)

#define PHY_BCR                          0          /* Tranceiver Basic Control Register */
#define PHY_BSR                          1          /* Tranceiver Basic Status Register */

#define PHY_Reset                       ((uint16_t)0x8000)      /* PHY Reset */
//#define PHY_Loopback                    ((uint16_t)0x4000)      /* Select loop-back mode */
//#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100)      /* Set the full-duplex mode at 100 Mb/s */
//#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000)      /* Set the half-duplex mode at 100 Mb/s */
//#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100)      /* Set the full-duplex mode at 10 Mb/s */
//#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000)      /* Set the half-duplex mode at 10 Mb/s */
//#define PHY_AutoNegotiation             ((uint16_t)0x1000)      /* Enable auto-negotiation function */
//#define PHY_Restart_AutoNegotiation     ((uint16_t)0x0200)      /* Restart auto-negotiation function */
//#define PHY_Powerdown                   ((uint16_t)0x0800)      /* Select the power down mode */
//#define PHY_Isolate                     ((uint16_t)0x0400)      /* Isolate PHY from MII */
//
//#define PHY_AutoNego_Complete           ((uint16_t)0x0020)      /* Auto-Negotiation process completed */
//#define PHY_Linked_Status               ((uint16_t)0x0004)      /* Valid link established */
//#define PHY_Jabber_detection            ((uint16_t)0x0002)      /* Jabber condition detected */
//
//#define PHY_SR                           16     /* Transceiver Status Register */
//
//#define PHY_Speed_Status            ((uint16_t)0x0002)    /* Configured information of Speed: 10Mbps */
//#define PHY_Duplex_Status           ((uint16_t)0x0004)    /* Configured information of Duplex: Full-duplex */

#define EMAC_AutoNegotiation_Enable     ((uint32_t)0x00000001)
#define EMAC_AutoNegotiation_Disable    ((uint32_t)0x00000000)

#define EMAC_Watchdog_Enable       ((uint32_t)0x00000000)
#define EMAC_Watchdog_Disable      ((uint32_t)0x00800000)

#define EMAC_Jabber_Enable    ((uint32_t)0x00000000)
#define EMAC_Jabber_Disable   ((uint32_t)0x00400000)

#define EMAC_InterFrameGap_96Bit   ((uint32_t)0x00000000)  /* minimum IFG between frames during transmission is 96Bit */
#define EMAC_InterFrameGap_88Bit   ((uint32_t)0x00020000)  /* minimum IFG between frames during transmission is 88Bit */
#define EMAC_InterFrameGap_80Bit   ((uint32_t)0x00040000)  /* minimum IFG between frames during transmission is 80Bit */
#define EMAC_InterFrameGap_72Bit   ((uint32_t)0x00060000)  /* minimum IFG between frames during transmission is 72Bit */
#define EMAC_InterFrameGap_64Bit   ((uint32_t)0x00080000)  /* minimum IFG between frames during transmission is 64Bit */
#define EMAC_InterFrameGap_56Bit   ((uint32_t)0x000A0000)  /* minimum IFG between frames during transmission is 56Bit */
#define EMAC_InterFrameGap_48Bit   ((uint32_t)0x000C0000)  /* minimum IFG between frames during transmission is 48Bit */
#define EMAC_InterFrameGap_40Bit   ((uint32_t)0x000E0000)  /* minimum IFG between frames during transmission is 40Bit */

#define EMAC_CarrierSense_Enable   ((uint32_t)0x00000000)
#define EMAC_CarrierSense_Disable  ((uint32_t)0x00010000)

#define EMAC_Speed_10M        ((uint32_t)0x00000000)
#define EMAC_Speed_100M       ((uint32_t)0x00004000)

#define EMAC_ReceiveOwn_Enable     ((uint32_t)0x00000000)
#define EMAC_ReceiveOwn_Disable    ((uint32_t)0x00002000)

#define EMAC_LoopbackMode_Enable        ((uint32_t)0x00001000)
#define EMAC_LoopbackMode_Disable       ((uint32_t)0x00000000)

#define EMAC_Mode_FullDuplex       ((uint32_t)0x00000800)
#define EMAC_Mode_HalfDuplex       ((uint32_t)0x00000000)

#define EMAC_ChecksumOffload_Enable     ((uint32_t)0x00000400)
#define EMAC_ChecksumOffload_Disable    ((uint32_t)0x00000000)

#define EMAC_RetryTransmission_Enable   ((uint32_t)0x00000000)
#define EMAC_RetryTransmission_Disable  ((uint32_t)0x00000200)

#define EMAC_AutomaticPadCRCStrip_Enable     ((uint32_t)0x00000080)
#define EMAC_AutomaticPadCRCStrip_Disable    ((uint32_t)0x00000000)

#define EMAC_BackOffLimit_10  ((uint32_t)0x00000000)
#define EMAC_BackOffLimit_8   ((uint32_t)0x00000020)
#define EMAC_BackOffLimit_4   ((uint32_t)0x00000040)
#define EMAC_BackOffLimit_1   ((uint32_t)0x00000060)

#define EMAC_DeferralCheck_Enable       ((uint32_t)0x00000010)
#define EMAC_DeferralCheck_Disable      ((uint32_t)0x00000000)

#define EMAC_ReceiveAll_Enable     ((uint32_t)0x80000000)
#define EMAC_ReceiveAll_Disable    ((uint32_t)0x00000000)

#define EMAC_SourceAddrFilter_Normal_Enable       ((uint32_t)0x00000200)
#define EMAC_SourceAddrFilter_Inverse_Enable      ((uint32_t)0x00000300)
#define EMAC_SourceAddrFilter_Disable             ((uint32_t)0x00000000)

#define EMAC_PassControlFrames_BlockAll                ((uint32_t)0x00000040)  /* MAC filters all control frames from reaching the application */
#define EMAC_PassControlFrames_ForwardAll              ((uint32_t)0x00000080)  /* MAC forwards all control frames to application even if they fail the Address Filter */
#define EMAC_PassControlFrames_ForwardPassedAddrFilter ((uint32_t)0x000000C0)  /* MAC forwards control frames that pass the Address Filter. */

#define EMAC_BroadcastFramesReception_Enable      ((uint32_t)0x00000000)
#define EMAC_BroadcastFramesReception_Disable     ((uint32_t)0x00000020)

#define EMAC_DestinationAddrFilter_Normal    ((uint32_t)0x00000000)
#define EMAC_DestinationAddrFilter_Inverse   ((uint32_t)0x00000008)

#define EMAC_PromiscuousMode_Enable     ((uint32_t)0x00000001)
#define EMAC_PromiscuousMode_Disable    ((uint32_t)0x00000000)

#define EMAC_MulticastFramesFilter_PerfectHashTable    ((uint32_t)0x00000404)
#define EMAC_MulticastFramesFilter_HashTable           ((uint32_t)0x00000004)
#define EMAC_MulticastFramesFilter_Perfect             ((uint32_t)0x00000000)
#define EMAC_MulticastFramesFilter_None                ((uint32_t)0x00000010)

#define EMAC_UnicastFramesFilter_PerfectHashTable ((uint32_t)0x00000402)
#define EMAC_UnicastFramesFilter_HashTable        ((uint32_t)0x00000002)
#define EMAC_UnicastFramesFilter_Perfect          ((uint32_t)0x00000000)

#define EMAC_ZeroQuantaPause_Enable     ((uint32_t)0x00000000)
#define EMAC_ZeroQuantaPause_Disable    ((uint32_t)0x00000080)

#define EMAC_PauseLowThreshold_Minus4        ((uint32_t)0x00000000)  /* Pause time minus 4 slot times */
#define EMAC_PauseLowThreshold_Minus28       ((uint32_t)0x00000010)  /* Pause time minus 28 slot times */
#define EMAC_PauseLowThreshold_Minus144      ((uint32_t)0x00000020)  /* Pause time minus 144 slot times */
#define EMAC_PauseLowThreshold_Minus256      ((uint32_t)0x00000030)  /* Pause time minus 256 slot times */

#define EMAC_UnicastPauseFrameDetect_Enable  ((uint32_t)0x00000008)
#define EMAC_UnicastPauseFrameDetect_Disable ((uint32_t)0x00000000)

#define EMAC_ReceiveFlowControl_Enable       ((uint32_t)0x00000004)
#define EMAC_ReceiveFlowControl_Disable      ((uint32_t)0x00000000)
#define EMAC_TransmitFlowControl_Enable      ((uint32_t)0x00000002)
#define EMAC_TransmitFlowControl_Disable     ((uint32_t)0x00000000)

#define EMAC_VLANTagComparison_12Bit    ((uint32_t)0x00010000)
#define EMAC_VLANTagComparison_16Bit    ((uint32_t)0x00000000)

#define EMAC_MAC_FLAG_TST     ((uint32_t)0x00000200)  /* Time stamp trigger flag (on MAC) */
#define EMAC_MAC_FLAG_MMCT    ((uint32_t)0x00000040)  /* MMC transmit flag  */
#define EMAC_MAC_FLAG_MMCR    ((uint32_t)0x00000020)  /* MMC receive flag */
#define EMAC_MAC_FLAG_MMC     ((uint32_t)0x00000010)  /* MMC flag (on MAC) */
#define EMAC_MAC_FLAG_PMT     ((uint32_t)0x00000008)  /* PMT flag (on MAC) */

#define EMAC_MAC_IT_TST       ((uint32_t)0x00000200)  /* Time stamp trigger interrupt (on MAC) */
#define EMAC_MAC_IT_MMCT      ((uint32_t)0x00000040)  /* MMC transmit interrupt */
#define EMAC_MAC_IT_MMCR      ((uint32_t)0x00000020)  /* MMC receive interrupt */
#define EMAC_MAC_IT_MMC       ((uint32_t)0x00000010)  /* MMC interrupt (on MAC) */
#define EMAC_MAC_IT_PMT       ((uint32_t)0x00000008)  /* PMT interrupt (on MAC) */

#define EMAC_MAC_Address0     ((uint32_t)0x00000000)
#define EMAC_MAC_Address1     ((uint32_t)0x00000008)
#define EMAC_MAC_Address2     ((uint32_t)0x00000010)
#define EMAC_MAC_Address3     ((uint32_t)0x00000018)

#define EMAC_MAC_AddressFilter_SA       ((uint32_t)0x00000000)
#define EMAC_MAC_AddressFilter_DA       ((uint32_t)0x00000008)

#define EMAC_MAC_AddressMask_Byte6      ((uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MAC_AddressMask_Byte5      ((uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MAC_AddressMask_Byte4      ((uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MAC_AddressMask_Byte3      ((uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MAC_AddressMask_Byte2      ((uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MAC_AddressMask_Byte1      ((uint32_t)0x01000000)  /* Mask MAC Address low reg bits [70] */

#define EMAC_DMATxDesc_LastSegment      ((uint32_t)0x40000000)  /* Last Segment */
#define EMAC_DMATxDesc_FirstSegment     ((uint32_t)0x20000000)  /* First Segment */

#define EMAC_DMATxDesc_ChecksumByPass             ((uint32_t)0x00000000)   /* Checksum engine bypass */
#define EMAC_DMATxDesc_ChecksumIPV4Header         ((uint32_t)0x00400000)   /* IPv4 header checksum insertion  */
#define EMAC_DMATxDesc_ChecksumTCPUDPICMPSegment  ((uint32_t)0x00800000)   /* TCP/UDP/ICMP checksum insertion. Pseudo header checksum is assumed to be present */
#define EMAC_DMATxDesc_ChecksumTCPUDPICMPFull     ((uint32_t)0x00C00000)   /* TCP/UDP/ICMP checksum fully in hardware including pseudo header */

#define EMAC_DMARxDesc_Buffer1     ((uint32_t)0x00000000)  /* DMA Rx Desc Buffer1 */
#define EMAC_DMARxDesc_Buffer2     ((uint32_t)0x00000001)  /* DMA Rx Desc Buffer2 */

#define EMAC_DropTCPIPChecksumErrorFrame_Enable   ((uint32_t)0x00000000)
#define EMAC_DropTCPIPChecksumErrorFrame_Disable  ((uint32_t)0x04000000)

#define EMAC_ReceiveStoreForward_Enable      ((uint32_t)0x02000000)
#define EMAC_ReceiveStoreForward_Disable     ((uint32_t)0x00000000)

#define EMAC_FlushReceivedFrame_Enable       ((uint32_t)0x00000000)
#define EMAC_FlushReceivedFrame_Disable      ((uint32_t)0x01000000)

#define EMAC_TransmitStoreForward_Enable     ((uint32_t)0x00200000)
#define EMAC_TransmitStoreForward_Disable    ((uint32_t)0x00000000)

#define EMAC_TransmitThresholdControl_64Bytes     ((uint32_t)0x00000000)  /* threshold level of the MTL Transmit FIFO is 64 Bytes */
#define EMAC_TransmitThresholdControl_128Bytes    ((uint32_t)0x00004000)  /* threshold level of the MTL Transmit FIFO is 128 Bytes */
#define EMAC_TransmitThresholdControl_192Bytes    ((uint32_t)0x00008000)  /* threshold level of the MTL Transmit FIFO is 192 Bytes */
#define EMAC_TransmitThresholdControl_256Bytes    ((uint32_t)0x0000C000)  /* threshold level of the MTL Transmit FIFO is 256 Bytes */
#define EMAC_TransmitThresholdControl_40Bytes     ((uint32_t)0x00010000)  /* threshold level of the MTL Transmit FIFO is 40 Bytes */
#define EMAC_TransmitThresholdControl_32Bytes     ((uint32_t)0x00014000)  /* threshold level of the MTL Transmit FIFO is 32 Bytes */
#define EMAC_TransmitThresholdControl_24Bytes     ((uint32_t)0x00018000)  /* threshold level of the MTL Transmit FIFO is 24 Bytes */
#define EMAC_TransmitThresholdControl_16Bytes     ((uint32_t)0x0001C000)  /* threshold level of the MTL Transmit FIFO is 16 Bytes */

#define EMAC_ForwardErrorFrames_Enable       ((uint32_t)0x00000080)
#define EMAC_ForwardErrorFrames_Disable      ((uint32_t)0x00000000)

#define EMAC_ForwardUndersizedGoodFrames_Enable   ((uint32_t)0x00000040)
#define EMAC_ForwardUndersizedGoodFrames_Disable  ((uint32_t)0x00000000)

#define EMAC_ReceiveThresholdControl_64Bytes      ((uint32_t)0x00000000)  /* threshold level of the MTL Receive FIFO is 64 Bytes */
#define EMAC_ReceiveThresholdControl_32Bytes      ((uint32_t)0x00000008)  /* threshold level of the MTL Receive FIFO is 32 Bytes */
#define EMAC_ReceiveThresholdControl_96Bytes      ((uint32_t)0x00000010)  /* threshold level of the MTL Receive FIFO is 96 Bytes */
#define EMAC_ReceiveThresholdControl_128Bytes     ((uint32_t)0x00000018)  /* threshold level of the MTL Receive FIFO is 128 Bytes */

#define EMAC_SecondFrameOperate_Enable       ((uint32_t)0x00000004)
#define EMAC_SecondFrameOperate_Disable      ((uint32_t)0x00000000)

#define EMAC_AddressAlignedBeats_Enable      ((uint32_t)0x02000000)
#define EMAC_AddressAlignedBeats_Disable     ((uint32_t)0x00000000)

#define EMAC_FixedBurst_Enable     ((uint32_t)0x00010000)
#define EMAC_FixedBurst_Disable    ((uint32_t)0x00000000)

#define EMAC_RxDMABurstLength_1Beat          ((uint32_t)0x00020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define EMAC_RxDMABurstLength_2Beat          ((uint32_t)0x00040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define EMAC_RxDMABurstLength_4Beat          ((uint32_t)0x00080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_RxDMABurstLength_8Beat          ((uint32_t)0x00100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_RxDMABurstLength_16Beat         ((uint32_t)0x00200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_RxDMABurstLength_32Beat         ((uint32_t)0x00400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_RxDMABurstLength_4xPBL_4Beat    ((uint32_t)0x01020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_RxDMABurstLength_4xPBL_8Beat    ((uint32_t)0x01040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_RxDMABurstLength_4xPBL_16Beat   ((uint32_t)0x01080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_RxDMABurstLength_4xPBL_32Beat   ((uint32_t)0x01100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_RxDMABurstLength_4xPBL_64Beat   ((uint32_t)0x01200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define EMAC_RxDMABurstLength_4xPBL_128Beat  ((uint32_t)0x01400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 128 */

#define EMAC_TxDMABurstLength_1Beat          ((uint32_t)0x00000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define EMAC_TxDMABurstLength_2Beat          ((uint32_t)0x00000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define EMAC_TxDMABurstLength_4Beat          ((uint32_t)0x00000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_TxDMABurstLength_8Beat          ((uint32_t)0x00000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_TxDMABurstLength_16Beat         ((uint32_t)0x00001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_TxDMABurstLength_32Beat         ((uint32_t)0x00002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_TxDMABurstLength_4xPBL_4Beat    ((uint32_t)0x01000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_TxDMABurstLength_4xPBL_8Beat    ((uint32_t)0x01000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_TxDMABurstLength_4xPBL_16Beat   ((uint32_t)0x01000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_TxDMABurstLength_4xPBL_32Beat   ((uint32_t)0x01000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_TxDMABurstLength_4xPBL_64Beat   ((uint32_t)0x01001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define EMAC_TxDMABurstLength_4xPBL_128Beat  ((uint32_t)0x01002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */

#define EMAC_DMAArbitration_RoundRobin_RxTx_1_1   ((uint32_t)0x00000000)
#define EMAC_DMAArbitration_RoundRobin_RxTx_2_1   ((uint32_t)0x00004000)
#define EMAC_DMAArbitration_RoundRobin_RxTx_3_1   ((uint32_t)0x00008000)
#define EMAC_DMAArbitration_RoundRobin_RxTx_4_1   ((uint32_t)0x0000C000)
#define EMAC_DMAArbitration_RxPriorTx             ((uint32_t)0x00000002)

#define EMAC_DMA_FLAG_TST               ((uint32_t)0x20000000)  /* Time-stamp trigger interrupt (on DMA) */
#define EMAC_DMA_FLAG_PMT               ((uint32_t)0x10000000)  /* PMT interrupt (on DMA) */
#define EMAC_DMA_FLAG_MMC               ((uint32_t)0x08000000)  /* MMC interrupt (on DMA) */
#define EMAC_DMA_FLAG_DataTransferError ((uint32_t)0x00800000)  /* Error bits 0-Rx DMA, 1-Tx DMA */
#define EMAC_DMA_FLAG_ReadWriteError    ((uint32_t)0x01000000)  /* Error bits 0-write transfer, 1-read transfer */
#define EMAC_DMA_FLAG_AccessError       ((uint32_t)0x02000000)  /* Error bits 0-data buffer, 1-desc. access */
#define EMAC_DMA_FLAG_NIS               ((uint32_t)0x00010000)  /* Normal interrupt summary flag */
#define EMAC_DMA_FLAG_AIS               ((uint32_t)0x00008000)  /* Abnormal interrupt summary flag */
#define EMAC_DMA_FLAG_ER                ((uint32_t)0x00004000)  /* Early receive flag */
#define EMAC_DMA_FLAG_FBE               ((uint32_t)0x00002000)  /* Fatal bus error flag */
#define EMAC_DMA_FLAG_ET                ((uint32_t)0x00000400)  /* Early transmit flag */
#define EMAC_DMA_FLAG_RWT               ((uint32_t)0x00000200)  /* Receive watchdog timeout flag */
#define EMAC_DMA_FLAG_RPS               ((uint32_t)0x00000100)  /* Receive process stopped flag */
#define EMAC_DMA_FLAG_RBU               ((uint32_t)0x00000080)  /* Receive buffer unavailable flag */
#define EMAC_DMA_FLAG_R                 ((uint32_t)0x00000040)  /* Receive flag */
#define EMAC_DMA_FLAG_TU                ((uint32_t)0x00000020)  /* Underflow flag */
#define EMAC_DMA_FLAG_RO                ((uint32_t)0x00000010)  /* Overflow flag */
#define EMAC_DMA_FLAG_TJT               ((uint32_t)0x00000008)  /* Transmit jabber timeout flag */
#define EMAC_DMA_FLAG_TBU               ((uint32_t)0x00000004)  /* Transmit buffer unavailable flag */
#define EMAC_DMA_FLAG_TPS               ((uint32_t)0x00000002)  /* Transmit process stopped flag */
#define EMAC_DMA_FLAG_T                 ((uint32_t)0x00000001)  /* Transmit flag */

#define EMAC_DMA_INT_GLPII     ((uint32_t)(1UL<<30))  /* GMAC LPI Interrupt. */
#define EMAC_DMA_INT_TTI       ((uint32_t)(1UL<<29))  /* Time-Stamp Trigger Interrupt. */
#define EMAC_DMA_INT_GPI       ((uint32_t)(1UL<<28))  /* GMAC PMT Interrupt. */
#define EMAC_DMA_INT_GMI       ((uint32_t)(1UL<<27))  /* GMAC MMC Interrupt. */
#define EMAC_DMA_INT_GLI       ((uint32_t)(1UL<<26))  /* GMAC Line interface Interrupt. */
#define EMAC_DMA_INT_NIS       ((uint32_t)(1UL<<16))  /* Normal interrupt summary. */
#define EMAC_DMA_INT_AIS       ((uint32_t)(1UL<<15))  /* Abnormal interrupt summary. */
#define EMAC_DMA_INT_ER        ((uint32_t)0x00004000)  /* Early receive interrupt */
#define EMAC_DMA_INT_FBE       ((uint32_t)0x00002000)  /* Fatal bus error interrupt */
#define EMAC_DMA_INT_ET        ((uint32_t)0x00000400)  /* Early transmit interrupt */
#define EMAC_DMA_INT_RWT       ((uint32_t)0x00000200)  /* Receive watchdog timeout interrupt */
#define EMAC_DMA_INT_RPS       ((uint32_t)0x00000100)  /* Receive process stopped interrupt */
#define EMAC_DMA_INT_RBU       ((uint32_t)0x00000080)  /* Receive buffer unavailable interrupt */
#define EMAC_DMA_INT_R         ((uint32_t)0x00000040)  /* Receive interrupt */
#define EMAC_DMA_INT_TU        ((uint32_t)0x00000020)  /* Underflow interrupt */
#define EMAC_DMA_INT_RO        ((uint32_t)0x00000010)  /* Overflow interrupt */
#define EMAC_DMA_INT_TJT       ((uint32_t)0x00000008)  /* Transmit jabber timeout interrupt */
#define EMAC_DMA_INT_TBU       ((uint32_t)0x00000004)  /* Transmit buffer unavailable interrupt */
#define EMAC_DMA_INT_TPS       ((uint32_t)0x00000002)  /* Transmit process stopped interrupt */
#define EMAC_DMA_INT_T         ((uint32_t)0x00000001)  /* Transmit interrupt */

#define EMAC_DMA_TransmitProcess_Stopped     ((uint32_t)0x00000000)  /* Stopped - Reset or Stop Tx Command issued */
#define EMAC_DMA_TransmitProcess_Fetching    ((uint32_t)0x00100000)  /* Running - fetching the Tx descriptor */
#define EMAC_DMA_TransmitProcess_Waiting     ((uint32_t)0x00200000)  /* Running - waiting for status */
#define EMAC_DMA_TransmitProcess_Reading     ((uint32_t)0x00300000)  /* Running - reading the data from host memory */
#define EMAC_DMA_TransmitProcess_Suspended   ((uint32_t)0x00600000)  /* Suspended - Tx Descriptor unavailable */
#define EMAC_DMA_TransmitProcess_Closing     ((uint32_t)0x00700000)  /* Running - closing Rx descriptor */

#define EMAC_DMA_ReceiveProcess_Stopped      ((uint32_t)0x00000000)  /* Stopped - Reset or Stop Rx Command issued */
#define EMAC_DMA_ReceiveProcess_Fetching     ((uint32_t)0x00020000)  /* Running - fetching the Rx descriptor */
#define EMAC_DMA_ReceiveProcess_Waiting      ((uint32_t)0x00060000)  /* Running - waiting for packet */
#define EMAC_DMA_ReceiveProcess_Suspended    ((uint32_t)0x00080000)  /* Suspended - Rx Descriptor unavailable */
#define EMAC_DMA_ReceiveProcess_Closing      ((uint32_t)0x000A0000)  /* Running - closing descriptor */
#define EMAC_DMA_ReceiveProcess_Queuing      ((uint32_t)0x000E0000)  /* Running - queuing the receive frame into host memory */

#define EMAC_DMA_Overflow_RxFIFOCounter      ((uint32_t)0x10000000)  /* Overflow bit for FIFO overflow counter */
#define EMAC_DMA_Overflow_MissedFrameCounter ((uint32_t)0x00010000)  /* Overflow bit for missed frame counter */

#define EMAC_PMT_FLAG_WUFFRPR      ((uint32_t)0x80000000)  /* Wake-Up Frame Filter Register Pointer Reset */
#define EMAC_PMT_FLAG_WUFR         ((uint32_t)0x00000040)  /* Wake-Up Frame Received */
#define EMAC_PMT_FLAG_MPR          ((uint32_t)0x00000020)  /* Magic Packet Received */

#define EMAC_MMC_IT_TGF       ((uint32_t)0x00200000)  /* When Tx good frame counter reaches half the maximum value */
#define EMAC_MMC_IT_TGFMSC    ((uint32_t)0x00008000)  /* When Tx good multi col counter reaches half the maximum value */
#define EMAC_MMC_IT_TGFSC     ((uint32_t)0x00004000)  /* When Tx good single col counter reaches half the maximum value */
#define EMAC_MMC_IT_RGUF      ((uint32_t)0x10020000)  /* When Rx good unicast frames counter reaches half the maximum value */
#define EMAC_MMC_IT_RFAE      ((uint32_t)0x10000040)  /* When Rx alignment error counter reaches half the maximum value */
#define EMAC_MMC_IT_RFCE      ((uint32_t)0x10000020)  /* When Rx crc error counter reaches half the maximum value */

#define EMAC_MMCCR            ((uint32_t)0x00000100)  /* MMC CR register */
#define EMAC_MMCRIR           ((uint32_t)0x00000104)  /* MMC RIR register */
#define EMAC_MMCTIR           ((uint32_t)0x00000108)  /* MMC TIR register */
#define EMAC_MMCRIMR          ((uint32_t)0x0000010C)  /* MMC RIMR register */
#define EMAC_MMCTIMR          ((uint32_t)0x00000110)  /* MMC TIMR register */
#define EMAC_MMCTGFSCCR       ((uint32_t)0x0000014C)  /* MMC TGFSCCR register */
#define EMAC_MMCTGFMSCCR      ((uint32_t)0x00000150)  /* MMC TGFMSCCR register */
#define EMAC_MMCTGFCR         ((uint32_t)0x00000168)  /* MMC TGFCR register */
#define EMAC_MMCRFCECR        ((uint32_t)0x00000194)  /* MMC RFCECR register */
#define EMAC_MMCRFAECR        ((uint32_t)0x00000198)  /* MMC RFAECR register */
#define EMAC_MMCRGUFCR        ((uint32_t)0x000001C4)  /* MMC RGUFCR register */

#define EMAC_PTP_FineUpdate        ((uint32_t)0x00000001)  /* Fine Update method */
#define EMAC_PTP_CoarseUpdate      ((uint32_t)0x00000000)  /* Coarse Update method */

#define EMAC_PTP_FLAG_TSARU        ((uint32_t)0x00000020)  /* Addend Register Update */
#define EMAC_PTP_FLAG_TSITE        ((uint32_t)0x00000010)  /* Time Stamp Interrupt Trigger */
#define EMAC_PTP_FLAG_TSSTU        ((uint32_t)0x00000008)  /* Time Stamp Update */
#define EMAC_PTP_FLAG_TSSTI        ((uint32_t)0x00000004)  /* Time Stamp Initialize */

#define EMAC_PTP_PositiveTime      ((uint32_t)0x00000000)  /* Positive time value */
#define EMAC_PTP_NegativeTime      ((uint32_t)0x80000000)  /* Negative time value */

#define EMAC_PTPTSCR     ((uint32_t)0x00000700)  /* PTP TSCR register */
#define EMAC_PTPSSIR     ((uint32_t)0x00000704)  /* PTP SSIR register */
#define EMAC_PTPTSHR     ((uint32_t)0x00000708)  /* PTP TSHR register */
#define EMAC_PTPTSLR     ((uint32_t)0x0000070C)  /* PTP TSLR register */
#define EMAC_PTPTSHUR    ((uint32_t)0x00000710)  /* PTP TSHUR register */
#define EMAC_PTPTSLUR    ((uint32_t)0x00000714)  /* PTP TSLUR register */
#define EMAC_PTPTSAR     ((uint32_t)0x00000718)  /* PTP TSAR register */
#define EMAC_PTPTTHR     ((uint32_t)0x0000071C)  /* PTP TTHR register */
#define EMAC_PTPTTLR     ((uint32_t)0x00000720)  /* PTP TTLR register */

/* ETHERNET MAC address offsets */
#define EMAC_MAC_ADDR_HBASE    (FM3_ETHERNET_MAC0_BASE + 0x40)  /* ETHERNET MAC address high offset */
#define EMAC_MAC_ADDR_LBASE    (FM3_ETHERNET_MAC0_BASE + 0x44)  /* ETHERNET MAC address low offset */

/* ETHERNET MACMIIAR register Mask */
#define MACMIIAR_CR_MASK    ((uint32_t)0xFFFFFFE3)

/* ETHERNET MACCR register Mask */
#define MACCR_CLEAR_MASK    ((uint32_t)0xFF20810F)

/* ETHERNET MACFCR register Mask */
#define MACFCR_CLEAR_MASK   ((uint32_t)0x0000FF41)

/* ETHERNET DMAOMR register Mask */
#define DMAOMR_CLEAR_MASK   ((uint32_t)0xF8DE3F23)

/* ETHERNET errors */
#define  EMAC_ERROR              ((uint32_t)0)
#define  EMAC_SUCCESS            ((uint32_t)1)

/* ETHERNET DMA Rx descriptors Frame Length Shift */
#define  EMAC_DMARXDESC_FRAME_LENGTHSHIFT           16

uint32_t EMAC_init(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC);

void  EMAC_start(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC);
void set_ethernet_e_cout_clock(int is_rmii);

uint16_t EMAC_PHY_read(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC, uint16_t PHYAddress, uint16_t PHYReg);
uint32_t EMAC_PHY_write(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC, uint16_t PHYAddress, uint16_t PHYReg, uint16_t PHYValue);

void EMAC_MAC_Addr_config(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC, uint32_t MacAddr, uint8_t *Addr);
void EMAC_clear_pending(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC, uint32_t EMAC_DMA_IT);

void EMAC_INT_config(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC, uint32_t EMAC_DMA_IT, FlagStatus NewState);
void EMAC_resume_transmission(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC);
void EMAC_resume_reception(FM3_ETHERNET_MAC_TypeDef * FM3_ETHERNET_MAC);

#endif // FM3_EMAC_H_INCLUDED
