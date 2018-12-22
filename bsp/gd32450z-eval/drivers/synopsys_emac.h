/*
 * File      : rtdef.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __SYNOPSYS_EMAC_H__
#define __SYNOPSYS_EMAC_H__

#include <rtthread.h>
     

/******************************************************************************/
/*                Ethernet MAC Registers bits definitions                     */
/******************************************************************************/
/* Bit definition for Ethernet MAC Control Register register */
#define EMAC_MACCR_WD           ((rt_uint32_t)0x00800000)  /* Watchdog disable */
#define EMAC_MACCR_JD           ((rt_uint32_t)0x00400000)  /* Jabber disable */
#define EMAC_MACCR_IFG          ((rt_uint32_t)0x000E0000)  /* Inter-frame gap */
#define EMAC_MACCR_IFG_96Bit    ((rt_uint32_t)0x00000000)  /* Minimum IFG between frames during transmission is 96Bit */
#define EMAC_MACCR_IFG_88Bit    ((rt_uint32_t)0x00020000)  /* Minimum IFG between frames during transmission is 88Bit */
#define EMAC_MACCR_IFG_80Bit    ((rt_uint32_t)0x00040000)  /* Minimum IFG between frames during transmission is 80Bit */
#define EMAC_MACCR_IFG_72Bit    ((rt_uint32_t)0x00060000)  /* Minimum IFG between frames during transmission is 72Bit */
#define EMAC_MACCR_IFG_64Bit    ((rt_uint32_t)0x00080000)  /* Minimum IFG between frames during transmission is 64Bit */
#define EMAC_MACCR_IFG_56Bit    ((rt_uint32_t)0x000A0000)  /* Minimum IFG between frames during transmission is 56Bit */
#define EMAC_MACCR_IFG_48Bit    ((rt_uint32_t)0x000C0000)  /* Minimum IFG between frames during transmission is 48Bit */
#define EMAC_MACCR_IFG_40Bit    ((rt_uint32_t)0x000E0000)  /* Minimum IFG between frames during transmission is 40Bit */
#define EMAC_MACCR_CSD          ((rt_uint32_t)0x00010000)  /* Carrier sense disable (during transmission) */
#define EMAC_MACCR_FES          ((rt_uint32_t)0x00004000)  /* Fast ethernet speed */
#define EMAC_MACCR_ROD          ((rt_uint32_t)0x00002000)  /* Receive own disable */
#define EMAC_MACCR_LM           ((rt_uint32_t)0x00001000)  /* loopback mode */
#define EMAC_MACCR_DM           ((rt_uint32_t)0x00000800)  /* Duplex mode */
#define EMAC_MACCR_IPCO         ((rt_uint32_t)0x00000400)  /* IP Checksum offload */
#define EMAC_MACCR_RD           ((rt_uint32_t)0x00000200)  /* Retry disable */
#define EMAC_MACCR_APCS         ((rt_uint32_t)0x00000080)  /* Automatic Pad/CRC stripping */
#define EMAC_MACCR_BL           ((rt_uint32_t)0x00000060)  /* Back-off limit: random integer number (r) of slot time delays before rescheduling
															a transmission attempt during retries after a collision: 0 =< r <2^k */
#define EMAC_MACCR_BL_10     	((rt_uint32_t)0x00000000)  /* k = min (n, 10) */
#define EMAC_MACCR_BL_8         ((rt_uint32_t)0x00000020)  /* k = min (n, 8) */
#define EMAC_MACCR_BL_4         ((rt_uint32_t)0x00000040)  /* k = min (n, 4) */
#define EMAC_MACCR_BL_1         ((rt_uint32_t)0x00000060)  /* k = min (n, 1) */
#define EMAC_MACCR_DC           ((rt_uint32_t)0x00000010)  /* Defferal check */
#define EMAC_MACCR_TE           ((rt_uint32_t)0x00000008)  /* Transmitter enable */
#define EMAC_MACCR_RE           ((rt_uint32_t)0x00000004)  /* Receiver enable */

/* Bit definition for Ethernet MAC Frame Filter Register */
#define EMAC_MACFFR_RA          ((rt_uint32_t)0x80000000)  /* Receive all */
#define EMAC_MACFFR_HPF         ((rt_uint32_t)0x00000400)  /* Hash or perfect filter */
#define EMAC_MACFFR_SAF      	((rt_uint32_t)0x00000200)  /* Source address filter enable */
#define EMAC_MACFFR_SAIF        ((rt_uint32_t)0x00000100)  /* SA inverse filtering */
#define EMAC_MACFFR_PCF         ((rt_uint32_t)0x000000C0)  /* Pass control frames: 3 cases */
#define EMAC_MACFFR_PCF_BlockAll                ((rt_uint32_t)0x00000040)  /* MAC filters all control frames from reaching the application */
#define EMAC_MACFFR_PCF_ForwardAll              ((rt_uint32_t)0x00000080)  /* MAC forwards all control frames to application even if they fail the Address Filter */
#define EMAC_MACFFR_PCF_ForwardPassedAddrFilter ((rt_uint32_t)0x000000C0)  /* MAC forwards control frames that pass the Address Filter. */
#define EMAC_MACFFR_BFD         ((rt_uint32_t)0x00000020)  /* Broadcast frame disable */
#define EMAC_MACFFR_PAM       	((rt_uint32_t)0x00000010)  /* Pass all mutlicast */
#define EMAC_MACFFR_DAIF        ((rt_uint32_t)0x00000008)  /* DA Inverse filtering */
#define EMAC_MACFFR_HM     	    ((rt_uint32_t)0x00000004)  /* Hash multicast */
#define EMAC_MACFFR_HU     	    ((rt_uint32_t)0x00000002)  /* Hash unicast */
#define EMAC_MACFFR_PM     	    ((rt_uint32_t)0x00000001)  /* Promiscuous mode */

/* Bit definition for Ethernet MAC Hash Table High Register */
#define EMAC_MACHTHR_HTH   	    ((rt_uint32_t)0xFFFFFFFF)  /* Hash table high */

/* Bit definition for Ethernet MAC Hash Table Low Register */
#define EMAC_MACHTLR_HTL  	    ((rt_uint32_t)0xFFFFFFFF)  /* Hash table low */

/* Bit definition for Ethernet MAC MII Address Register */
#define EMAC_MACMIIAR_PA  	    ((rt_uint32_t)0x0000F800)  /* Physical layer address */
#define EMAC_MACMIIAR_MR 	   	((rt_uint32_t)0x000007C0)  /* MII register in the selected PHY */
#define EMAC_MACMIIAR_CR 	    ((rt_uint32_t)0x0000001C)  /* CR clock range: 6 cases */
#define EMAC_MACMIIAR_CR_Div42  ((rt_uint32_t)0x00000000)  /* HCLK:60-100 MHz; MDC clock= HCLK/42 */
#define EMAC_MACMIIAR_CR_Div62  ((rt_uint32_t)0x00000004)  /* HCLK:100-150 MHz; MDC clock= HCLK/62 */
#define EMAC_MACMIIAR_CR_Div16  ((rt_uint32_t)0x00000008)  /* HCLK:20-35 MHz; MDC clock= HCLK/16 */
#define EMAC_MACMIIAR_CR_Div26  ((rt_uint32_t)0x0000000C)  /* HCLK:35-60 MHz; MDC clock= HCLK/26 */
#define EMAC_MACMIIAR_CR_Div102 ((rt_uint32_t)0x00000010)  /* HCLK:150-250 MHz; MDC clock= HCLK/102 */
#define EMAC_MACMIIAR_CR_Div122 ((rt_uint32_t)0x00000014)  /* HCLK:250-300 MHz; MDC clock= HCLK/122*/
#define EMAC_MACMIIAR_MW   	  	((rt_uint32_t)0x00000002)  /* MII write */
#define EMAC_MACMIIAR_MB   		((rt_uint32_t)0x00000001)  /* MII busy */

/* Bit definition for Ethernet MAC MII Data Register */
#define EMAC_MACMIIDR_MD  	 	((rt_uint32_t)0x0000FFFF)  /* MII data: read/write data from/to PHY */

/* Bit definition for Ethernet MAC Flow Control Register */
#define EMAC_MACFCR_PT    		((rt_uint32_t)0xFFFF0000)  /* Pause time */
#define EMAC_MACFCR_ZQPD   		((rt_uint32_t)0x00000080)  /* Zero-quanta pause disable */
#define EMAC_MACFCR_PLT    		((rt_uint32_t)0x00000030)  /* Pause low threshold: 4 cases */
#define EMAC_MACFCR_PLT_Minus4   ((rt_uint32_t)0x00000000)  /* Pause time minus 4 slot times */
#define EMAC_MACFCR_PLT_Minus28  ((rt_uint32_t)0x00000010)  /* Pause time minus 28 slot times */
#define EMAC_MACFCR_PLT_Minus144 ((rt_uint32_t)0x00000020)  /* Pause time minus 144 slot times */
#define EMAC_MACFCR_PLT_Minus256 ((rt_uint32_t)0x00000030)  /* Pause time minus 256 slot times */
#define EMAC_MACFCR_UPFD   ((rt_uint32_t)0x00000008)  /* Unicast pause frame detect */
#define EMAC_MACFCR_RFCE   ((rt_uint32_t)0x00000004)  /* Receive flow control enable */
#define EMAC_MACFCR_TFCE   ((rt_uint32_t)0x00000002)  /* Transmit flow control enable */
#define EMAC_MACFCR_FCBBPA ((rt_uint32_t)0x00000001)  /* Flow control busy/backpressure activate */

/* Bit definition for Ethernet MAC VLAN Tag Register */
#define EMAC_MACVLANTR_VLANTC ((rt_uint32_t)0x00010000)  /* 12-bit VLAN tag comparison */
#define EMAC_MACVLANTR_VLANTI ((rt_uint32_t)0x0000FFFF)  /* VLAN tag identifier (for receive frames) */

/* Bit definition for Ethernet MAC Remote Wake-UpFrame Filter Register */
#define EMAC_MACRWUFFR_D   ((rt_uint32_t)0xFFFFFFFF)  /* Wake-up frame filter register data */
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
#define EMAC_MACPMTCSR_WFFRPR ((rt_uint32_t)0x80000000)  /* Wake-Up Frame Filter Register Pointer Reset */
#define EMAC_MACPMTCSR_GU     ((rt_uint32_t)0x00000200)  /* Global Unicast */
#define EMAC_MACPMTCSR_WFR    ((rt_uint32_t)0x00000040)  /* Wake-Up Frame Received */
#define EMAC_MACPMTCSR_MPR    ((rt_uint32_t)0x00000020)  /* Magic Packet Received */
#define EMAC_MACPMTCSR_WFE    ((rt_uint32_t)0x00000004)  /* Wake-Up Frame Enable */
#define EMAC_MACPMTCSR_MPE    ((rt_uint32_t)0x00000002)  /* Magic Packet Enable */
#define EMAC_MACPMTCSR_PD     ((rt_uint32_t)0x00000001)  /* Power Down */

/* Bit definition for Ethernet MAC Status Register */
#define EMAC_MACSR_TSTS      ((rt_uint32_t)0x00000200)  /* Time stamp trigger status */
#define EMAC_MACSR_MMCTS     ((rt_uint32_t)0x00000040)  /* MMC transmit status */
#define EMAC_MACSR_MMMCRS    ((rt_uint32_t)0x00000020)  /* MMC receive status */
#define EMAC_MACSR_MMCS      ((rt_uint32_t)0x00000010)  /* MMC status */
#define EMAC_MACSR_PMTS      ((rt_uint32_t)0x00000008)  /* PMT status */

/* Bit definition for Ethernet MAC Interrupt Mask Register */
#define EMAC_MACIMR_TSTIM     ((rt_uint32_t)0x00000200)  /* Time stamp trigger interrupt mask */
#define EMAC_MACIMR_PMTIM     ((rt_uint32_t)0x00000008)  /* PMT interrupt mask */

/* Bit definition for Ethernet MAC Address0 High Register */
#define EMAC_MACA0HR_MACA0H   ((rt_uint32_t)0x0000FFFF)  /* MAC address0 high */

/* Bit definition for Ethernet MAC Address0 Low Register */
#define EMAC_MACA0LR_MACA0L   ((rt_uint32_t)0xFFFFFFFF)  /* MAC address0 low */

/* Bit definition for Ethernet MAC Address1 High Register */
#define EMAC_MACA1HR_AE       ((rt_uint32_t)0x80000000)  /* Address enable */
#define EMAC_MACA1HR_SA       ((rt_uint32_t)0x40000000)  /* Source address */
#define EMAC_MACA1HR_MBC      ((rt_uint32_t)0x3F000000)  /* Mask byte control: bits to mask for comparison of the MAC Address bytes */
#define EMAC_MACA1HR_MBC_HBits15_8    ((rt_uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MACA1HR_MBC_HBits7_0     ((rt_uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MACA1HR_MBC_LBits31_24   ((rt_uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MACA1HR_MBC_LBits23_16   ((rt_uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MACA1HR_MBC_LBits15_8    ((rt_uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MACA1HR_MBC_LBits7_0     ((rt_uint32_t)0x01000000)  /* Mask MAC Address low reg bits [7:0] */
#define EMAC_MACA1HR_MACA1H   ((rt_uint32_t)0x0000FFFF)  /* MAC address1 high */

/* Bit definition for Ethernet MAC Address1 Low Register */
#define EMAC_MACA1LR_MACA1L   ((rt_uint32_t)0xFFFFFFFF)  /* MAC address1 low */

/* Bit definition for Ethernet MAC Address2 High Register */
#define EMAC_MACA2HR_AE       ((rt_uint32_t)0x80000000)  /* Address enable */
#define EMAC_MACA2HR_SA       ((rt_uint32_t)0x40000000)  /* Source address */
#define EMAC_MACA2HR_MBC      ((rt_uint32_t)0x3F000000)  /* Mask byte control */
#define EMAC_MACA2HR_MBC_HBits15_8    ((rt_uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MACA2HR_MBC_HBits7_0     ((rt_uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MACA2HR_MBC_LBits31_24   ((rt_uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MACA2HR_MBC_LBits23_16   ((rt_uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MACA2HR_MBC_LBits15_8    ((rt_uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MACA2HR_MBC_LBits7_0     ((rt_uint32_t)0x01000000)  /* Mask MAC Address low reg bits [70] */
#define EMAC_MACA2HR_MACA2H   ((rt_uint32_t)0x0000FFFF)  /* MAC address1 high */

/* Bit definition for Ethernet MAC Address2 Low Register */
#define EMAC_MACA2LR_MACA2L   ((rt_uint32_t)0xFFFFFFFF)  /* MAC address2 low */

/* Bit definition for Ethernet MAC Address3 High Register */
#define EMAC_MACA3HR_AE       ((rt_uint32_t)0x80000000)  /* Address enable */
#define EMAC_MACA3HR_SA       ((rt_uint32_t)0x40000000)  /* Source address */
#define EMAC_MACA3HR_MBC      ((rt_uint32_t)0x3F000000)  /* Mask byte control */
#define EMAC_MACA3HR_MBC_HBits15_8    ((rt_uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MACA3HR_MBC_HBits7_0     ((rt_uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MACA3HR_MBC_LBits31_24   ((rt_uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MACA3HR_MBC_LBits23_16   ((rt_uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MACA3HR_MBC_LBits15_8    ((rt_uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MACA3HR_MBC_LBits7_0     ((rt_uint32_t)0x01000000)  /* Mask MAC Address low reg bits [70] */
#define EMAC_MACA3HR_MACA3H   ((rt_uint32_t)0x0000FFFF)  /* MAC address3 high */

/* Bit definition for Ethernet MAC Address3 Low Register */
#define EMAC_MACA3LR_MACA3L   ((rt_uint32_t)0xFFFFFFFF)  /* MAC address3 low */

/******************************************************************************/
/*                Ethernet MMC Registers bits definition                      */
/******************************************************************************/

/* Bit definition for Ethernet MMC Contol Register */
#define EMAC_MMCCR_MCF        ((rt_uint32_t)0x00000008)  /* MMC Counter Freeze */
#define EMAC_MMCCR_ROR        ((rt_uint32_t)0x00000004)  /* Reset on Read */
#define EMAC_MMCCR_CSR        ((rt_uint32_t)0x00000002)  /* Counter Stop Rollover */
#define EMAC_MMCCR_CR         ((rt_uint32_t)0x00000001)  /* Counters Reset */

/* Bit definition for Ethernet MMC Receive Interrupt Register */
#define EMAC_MMCRIR_RGUFS     ((rt_uint32_t)0x00020000)  /* Set when Rx good unicast frames counter reaches half the maximum value */
#define EMAC_MMCRIR_RFAES     ((rt_uint32_t)0x00000040)  /* Set when Rx alignment error counter reaches half the maximum value */
#define EMAC_MMCRIR_RFCES     ((rt_uint32_t)0x00000020)  /* Set when Rx crc error counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Transmit Interrupt Register */
#define EMAC_MMCTIR_TGFS      ((rt_uint32_t)0x00200000)  /* Set when Tx good frame count counter reaches half the maximum value */
#define EMAC_MMCTIR_TGFMSCS   ((rt_uint32_t)0x00008000)  /* Set when Tx good multi col counter reaches half the maximum value */
#define EMAC_MMCTIR_TGFSCS    ((rt_uint32_t)0x00004000)  /* Set when Tx good single col counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Receive Interrupt Mask Register */
#define EMAC_MMCRIMR_RGUFM    ((rt_uint32_t)0x00020000)  /* Mask the interrupt when Rx good unicast frames counter reaches half the maximum value */
#define EMAC_MMCRIMR_RFAEM    ((rt_uint32_t)0x00000040)  /* Mask the interrupt when when Rx alignment error counter reaches half the maximum value */
#define EMAC_MMCRIMR_RFCEM    ((rt_uint32_t)0x00000020)  /* Mask the interrupt when Rx crc error counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Transmit Interrupt Mask Register */
#define EMAC_MMCTIMR_TGFM     ((rt_uint32_t)0x00200000)  /* Mask the interrupt when Tx good frame count counter reaches half the maximum value */
#define EMAC_MMCTIMR_TGFMSCM  ((rt_uint32_t)0x00008000)  /* Mask the interrupt when Tx good multi col counter reaches half the maximum value */
#define EMAC_MMCTIMR_TGFSCM   ((rt_uint32_t)0x00004000)  /* Mask the interrupt when Tx good single col counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Transmitted Good Frames after Single Collision Counter Register */
#define EMAC_MMCTGFSCCR_TGFSCC     ((rt_uint32_t)0xFFFFFFFF)  /* Number of successfully transmitted frames after a single collision in Half-duplex mode. */

/* Bit definition for Ethernet MMC Transmitted Good Frames after More than a Single Collision Counter Register */
#define EMAC_MMCTGFMSCCR_TGFMSCC   ((rt_uint32_t)0xFFFFFFFF)  /* Number of successfully transmitted frames after more than a single collision in Half-duplex mode. */

/* Bit definition for Ethernet MMC Transmitted Good Frames Counter Register */
#define EMAC_MMCTGFCR_TGFC    ((rt_uint32_t)0xFFFFFFFF)  /* Number of good frames transmitted. */

/* Bit definition for Ethernet MMC Received Frames with CRC Error Counter Register */
#define EMAC_MMCRFCECR_RFCEC  ((rt_uint32_t)0xFFFFFFFF)  /* Number of frames received with CRC error. */

/* Bit definition for Ethernet MMC Received Frames with Alignment Error Counter Register */
#define EMAC_MMCRFAECR_RFAEC  ((rt_uint32_t)0xFFFFFFFF)  /* Number of frames received with alignment (dribble) error */

/* Bit definition for Ethernet MMC Received Good Unicast Frames Counter Register */
#define EMAC_MMCRGUFCR_RGUFC  ((rt_uint32_t)0xFFFFFFFF)  /* Number of good unicast frames received. */

/******************************************************************************/
/*               Ethernet PTP Registers bits definition                       */
/******************************************************************************/

/* Bit definition for Ethernet PTP Time Stamp Control Register */
#define EMAC_PTPTSCR_TSARU    ((rt_uint32_t)0x00000020)  /* Addend register update */
#define EMAC_PTPTSCR_TSITE    ((rt_uint32_t)0x00000010)  /* Time stamp interrupt trigger enable */
#define EMAC_PTPTSCR_TSSTU    ((rt_uint32_t)0x00000008)  /* Time stamp update */
#define EMAC_PTPTSCR_TSSTI    ((rt_uint32_t)0x00000004)  /* Time stamp initialize */
#define EMAC_PTPTSCR_TSFCU    ((rt_uint32_t)0x00000002)  /* Time stamp fine or coarse update */
#define EMAC_PTPTSCR_TSE      ((rt_uint32_t)0x00000001)  /* Time stamp enable */

/* Bit definition for Ethernet PTP Sub-Second Increment Register */
#define EMAC_PTPSSIR_STSSI    ((rt_uint32_t)0x000000FF)  /* System time Sub-second increment value */

/* Bit definition for Ethernet PTP Time Stamp High Register */
#define EMAC_PTPTSHR_STS      ((rt_uint32_t)0xFFFFFFFF)  /* System Time second */

/* Bit definition for Ethernet PTP Time Stamp Low Register */
#define EMAC_PTPTSLR_STPNS    ((rt_uint32_t)0x80000000)  /* System Time Positive or negative time */
#define EMAC_PTPTSLR_STSS     ((rt_uint32_t)0x7FFFFFFF)  /* System Time sub-seconds */

/* Bit definition for Ethernet PTP Time Stamp High Update Register */
#define EMAC_PTPTSHUR_TSUS    ((rt_uint32_t)0xFFFFFFFF)  /* Time stamp update seconds */

/* Bit definition for Ethernet PTP Time Stamp Low Update Register */
#define EMAC_PTPTSLUR_TSUPNS  ((rt_uint32_t)0x80000000)  /* Time stamp update Positive or negative time */
#define EMAC_PTPTSLUR_TSUSS   ((rt_uint32_t)0x7FFFFFFF)  /* Time stamp update sub-seconds */

/* Bit definition for Ethernet PTP Time Stamp Addend Register */
#define EMAC_PTPTSAR_TSA      ((rt_uint32_t)0xFFFFFFFF)  /* Time stamp addend */

/* Bit definition for Ethernet PTP Target Time High Register */
#define EMAC_PTPTTHR_TTSH     ((rt_uint32_t)0xFFFFFFFF)  /* Target time stamp high */

/* Bit definition for Ethernet PTP Target Time Low Register */
#define EMAC_PTPTTLR_TTSL     ((rt_uint32_t)0xFFFFFFFF)  /* Target time stamp low */

/******************************************************************************/
/*                 Ethernet DMA Registers bits definition                     */
/******************************************************************************/

/* Bit definition for Ethernet DMA Bus Mode Register */
#define EMAC_DMABMR_AAB       ((rt_uint32_t)0x02000000)  /* Address-Aligned beats */
#define EMAC_DMABMR_FPM        ((rt_uint32_t)0x01000000)  /* 4xPBL mode */
#define EMAC_DMABMR_USP       ((rt_uint32_t)0x00800000)  /* Use separate PBL */
#define EMAC_DMABMR_RDP       ((rt_uint32_t)0x007E0000)  /* RxDMA PBL */
#define EMAC_DMABMR_RDP_1Beat    ((rt_uint32_t)0x00020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define EMAC_DMABMR_RDP_2Beat    ((rt_uint32_t)0x00040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define EMAC_DMABMR_RDP_4Beat    ((rt_uint32_t)0x00080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_DMABMR_RDP_8Beat    ((rt_uint32_t)0x00100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_DMABMR_RDP_16Beat   ((rt_uint32_t)0x00200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_DMABMR_RDP_32Beat   ((rt_uint32_t)0x00400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_DMABMR_RDP_4xPBL_4Beat   ((rt_uint32_t)0x01020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_DMABMR_RDP_4xPBL_8Beat   ((rt_uint32_t)0x01040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_DMABMR_RDP_4xPBL_16Beat  ((rt_uint32_t)0x01080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_DMABMR_RDP_4xPBL_32Beat  ((rt_uint32_t)0x01100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_DMABMR_RDP_4xPBL_64Beat  ((rt_uint32_t)0x01200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define EMAC_DMABMR_RDP_4xPBL_128Beat ((rt_uint32_t)0x01400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 128 */
#define EMAC_DMABMR_FB        ((rt_uint32_t)0x00010000)  /* Fixed Burst */
#define EMAC_DMABMR_RTPR      ((rt_uint32_t)0x0000C000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_1_1     ((rt_uint32_t)0x00000000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_2_1     ((rt_uint32_t)0x00004000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_3_1     ((rt_uint32_t)0x00008000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_RTPR_4_1     ((rt_uint32_t)0x0000C000)  /* Rx Tx priority ratio */
#define EMAC_DMABMR_PBL    ((rt_uint32_t)0x00003F00)  /* Programmable burst length */
#define EMAC_DMABMR_PBL_1Beat    ((rt_uint32_t)0x00000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define EMAC_DMABMR_PBL_2Beat    ((rt_uint32_t)0x00000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define EMAC_DMABMR_PBL_4Beat    ((rt_uint32_t)0x00000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_DMABMR_PBL_8Beat    ((rt_uint32_t)0x00000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_DMABMR_PBL_16Beat   ((rt_uint32_t)0x00001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_DMABMR_PBL_32Beat   ((rt_uint32_t)0x00002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_DMABMR_PBL_4xPBL_4Beat   ((rt_uint32_t)0x01000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_DMABMR_PBL_4xPBL_8Beat   ((rt_uint32_t)0x01000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_DMABMR_PBL_4xPBL_16Beat  ((rt_uint32_t)0x01000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_DMABMR_PBL_4xPBL_32Beat  ((rt_uint32_t)0x01000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_DMABMR_PBL_4xPBL_64Beat  ((rt_uint32_t)0x01001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define EMAC_DMABMR_PBL_4xPBL_128Beat ((rt_uint32_t)0x01002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */
#define EMAC_DMABMR_EDE       ((rt_uint32_t)0x00000080)  /* Enhanced Descriptor Enable */
#define EMAC_DMABMR_DSL       ((rt_uint32_t)0x0000007C)  /* Descriptor Skip Length */
#define EMAC_DMABMR_DA        ((rt_uint32_t)0x00000002)  /* DMA arbitration scheme */
#define EMAC_DMABMR_SR        ((rt_uint32_t)0x00000001)  /* Software reset */

/* Bit definition for Ethernet DMA Transmit Poll Demand Register */
#define EMAC_DMATPDR_TPD      ((rt_uint32_t)0xFFFFFFFF)  /* Transmit poll demand */

/* Bit definition for Ethernet DMA Receive Poll Demand Register */
#define EMAC_DMARPDR_RPD      ((rt_uint32_t)0xFFFFFFFF)  /* Receive poll demand  */

/* Bit definition for Ethernet DMA Receive Descriptor List Address Register */
#define EMAC_DMARDLAR_SRL     ((rt_uint32_t)0xFFFFFFFF)  /* Start of receive list */

/* Bit definition for Ethernet DMA Transmit Descriptor List Address Register */
#define EMAC_DMATDLAR_STL     ((rt_uint32_t)0xFFFFFFFF)  /* Start of transmit list */

/* Bit definition for Ethernet DMA Status Register */
#define EMAC_DMASR_TSTS       ((rt_uint32_t)0x20000000)  /* Time-stamp trigger status */
#define EMAC_DMASR_PMTS       ((rt_uint32_t)0x10000000)  /* PMT status */
#define EMAC_DMASR_MMCS       ((rt_uint32_t)0x08000000)  /* MMC status */
#define EMAC_DMASR_EBS        ((rt_uint32_t)0x03800000)  /* Error bits status */
/* combination with EBS[2:0] for GetFlagStatus function */
#define EMAC_DMASR_EBS_DescAccess      ((rt_uint32_t)0x02000000)  /* Error bits 0-data buffer, 1-desc. access */
#define EMAC_DMASR_EBS_ReadTransf      ((rt_uint32_t)0x01000000)  /* Error bits 0-write transfer, 1-read transfer */
#define EMAC_DMASR_EBS_DataTransfTx    ((rt_uint32_t)0x00800000)  /* Error bits 0-Rx DMA, 1-Tx DMA */
#define EMAC_DMASR_TPS         ((rt_uint32_t)0x00700000)  /* Transmit process state */
#define EMAC_DMASR_TPS_Stopped         ((rt_uint32_t)0x00000000)  /* Stopped - Reset or Stop Tx Command issued  */
#define EMAC_DMASR_TPS_Fetching        ((rt_uint32_t)0x00100000)  /* Running - fetching the Tx descriptor */
#define EMAC_DMASR_TPS_Waiting         ((rt_uint32_t)0x00200000)  /* Running - waiting for status */
#define EMAC_DMASR_TPS_Reading         ((rt_uint32_t)0x00300000)  /* Running - reading the data from host memory */
#define EMAC_DMASR_TPS_Suspended       ((rt_uint32_t)0x00600000)  /* Suspended - Tx Descriptor unavailable */
#define EMAC_DMASR_TPS_Closing         ((rt_uint32_t)0x00700000)  /* Running - closing Rx descriptor */
#define EMAC_DMASR_RPS         ((rt_uint32_t)0x000E0000)  /* Receive process state */
#define EMAC_DMASR_RPS_Stopped         ((rt_uint32_t)0x00000000)  /* Stopped - Reset or Stop Rx Command issued */
#define EMAC_DMASR_RPS_Fetching        ((rt_uint32_t)0x00020000)  /* Running - fetching the Rx descriptor */
#define EMAC_DMASR_RPS_Waiting         ((rt_uint32_t)0x00060000)  /* Running - waiting for packet */
#define EMAC_DMASR_RPS_Suspended       ((rt_uint32_t)0x00080000)  /* Suspended - Rx Descriptor unavailable */
#define EMAC_DMASR_RPS_Closing         ((rt_uint32_t)0x000A0000)  /* Running - closing descriptor */
#define EMAC_DMASR_RPS_Queuing         ((rt_uint32_t)0x000E0000)  /* Running - queuing the receive frame into host memory */
#define EMAC_DMASR_NIS        ((rt_uint32_t)0x00010000)  /* Normal interrupt summary */
#define EMAC_DMASR_AIS        ((rt_uint32_t)0x00008000)  /* Abnormal interrupt summary */
#define EMAC_DMASR_ERS        ((rt_uint32_t)0x00004000)  /* Early receive status */
#define EMAC_DMASR_FBES       ((rt_uint32_t)0x00002000)  /* Fatal bus error status */
#define EMAC_DMASR_ETS        ((rt_uint32_t)0x00000400)  /* Early transmit status */
#define EMAC_DMASR_RWTS       ((rt_uint32_t)0x00000200)  /* Receive watchdog timeout status */
#define EMAC_DMASR_RPSS       ((rt_uint32_t)0x00000100)  /* Receive process stopped status */
#define EMAC_DMASR_RBUS       ((rt_uint32_t)0x00000080)  /* Receive buffer unavailable status */
#define EMAC_DMASR_RS         ((rt_uint32_t)0x00000040)  /* Receive status */
#define EMAC_DMASR_TUS        ((rt_uint32_t)0x00000020)  /* Transmit underflow status */
#define EMAC_DMASR_ROS        ((rt_uint32_t)0x00000010)  /* Receive overflow status */
#define EMAC_DMASR_TJTS       ((rt_uint32_t)0x00000008)  /* Transmit jabber timeout status */
#define EMAC_DMASR_TBUS       ((rt_uint32_t)0x00000004)  /* Transmit buffer unavailable status */
#define EMAC_DMASR_TPSS       ((rt_uint32_t)0x00000002)  /* Transmit process stopped status */
#define EMAC_DMASR_TS         ((rt_uint32_t)0x00000001)  /* Transmit status */

/* Bit definition for Ethernet DMA Operation Mode Register */
#define EMAC_DMAOMR_DTCEFD    ((rt_uint32_t)0x04000000)  /* Disable Dropping of TCP/IP checksum error frames */
#define EMAC_DMAOMR_RSF       ((rt_uint32_t)0x02000000)  /* Receive store and forward */
#define EMAC_DMAOMR_DFRF      ((rt_uint32_t)0x01000000)  /* Disable flushing of received frames */
#define EMAC_DMAOMR_TSF       ((rt_uint32_t)0x00200000)  /* Transmit store and forward */
#define EMAC_DMAOMR_FTF       ((rt_uint32_t)0x00100000)  /* Flush transmit FIFO */
#define EMAC_DMAOMR_TTC       ((rt_uint32_t)0x0001C000)  /* Transmit threshold control */
#define EMAC_DMAOMR_TTC_64Bytes       ((rt_uint32_t)0x00000000)  /* threshold level of the MTL Transmit FIFO is 64 Bytes */
#define EMAC_DMAOMR_TTC_128Bytes      ((rt_uint32_t)0x00004000)  /* threshold level of the MTL Transmit FIFO is 128 Bytes */
#define EMAC_DMAOMR_TTC_192Bytes      ((rt_uint32_t)0x00008000)  /* threshold level of the MTL Transmit FIFO is 192 Bytes */
#define EMAC_DMAOMR_TTC_256Bytes      ((rt_uint32_t)0x0000C000)  /* threshold level of the MTL Transmit FIFO is 256 Bytes */
#define EMAC_DMAOMR_TTC_40Bytes       ((rt_uint32_t)0x00010000)  /* threshold level of the MTL Transmit FIFO is 40 Bytes */
#define EMAC_DMAOMR_TTC_32Bytes       ((rt_uint32_t)0x00014000)  /* threshold level of the MTL Transmit FIFO is 32 Bytes */
#define EMAC_DMAOMR_TTC_24Bytes       ((rt_uint32_t)0x00018000)  /* threshold level of the MTL Transmit FIFO is 24 Bytes */
#define EMAC_DMAOMR_TTC_16Bytes       ((rt_uint32_t)0x0001C000)  /* threshold level of the MTL Transmit FIFO is 16 Bytes */
#define EMAC_DMAOMR_ST        ((rt_uint32_t)0x00002000)  /* Start/stop transmission command */
#define EMAC_DMAOMR_FEF       ((rt_uint32_t)0x00000080)  /* Forward error frames */
#define EMAC_DMAOMR_FUGF      ((rt_uint32_t)0x00000040)  /* Forward undersized good frames */
#define EMAC_DMAOMR_RTC       ((rt_uint32_t)0x00000018)  /* receive threshold control */
#define EMAC_DMAOMR_RTC_64Bytes       ((rt_uint32_t)0x00000000)  /* threshold level of the MTL Receive FIFO is 64 Bytes */
#define EMAC_DMAOMR_RTC_32Bytes       ((rt_uint32_t)0x00000008)  /* threshold level of the MTL Receive FIFO is 32 Bytes */
#define EMAC_DMAOMR_RTC_96Bytes       ((rt_uint32_t)0x00000010)  /* threshold level of the MTL Receive FIFO is 96 Bytes */
#define EMAC_DMAOMR_RTC_128Bytes      ((rt_uint32_t)0x00000018)  /* threshold level of the MTL Receive FIFO is 128 Bytes */
#define EMAC_DMAOMR_OSF       ((rt_uint32_t)0x00000004)  /* operate on second frame */
#define EMAC_DMAOMR_SR        ((rt_uint32_t)0x00000002)  /* Start/stop receive */

/* Bit definition for Ethernet DMA Interrupt Enable Register */
#define EMAC_DMAIER_NISE      ((rt_uint32_t)0x00010000)  /* Normal interrupt summary enable */
#define EMAC_DMAIER_AISE      ((rt_uint32_t)0x00008000)  /* Abnormal interrupt summary enable */
#define EMAC_DMAIER_ERIE      ((rt_uint32_t)0x00004000)  /* Early receive interrupt enable */
#define EMAC_DMAIER_FBEIE     ((rt_uint32_t)0x00002000)  /* Fatal bus error interrupt enable */
#define EMAC_DMAIER_ETIE      ((rt_uint32_t)0x00000400)  /* Early transmit interrupt enable */
#define EMAC_DMAIER_RWTIE     ((rt_uint32_t)0x00000200)  /* Receive watchdog timeout interrupt enable */
#define EMAC_DMAIER_RPSIE     ((rt_uint32_t)0x00000100)  /* Receive process stopped interrupt enable */
#define EMAC_DMAIER_RBUIE     ((rt_uint32_t)0x00000080)  /* Receive buffer unavailable interrupt enable */
#define EMAC_DMAIER_RIE       ((rt_uint32_t)0x00000040)  /* Receive interrupt enable */
#define EMAC_DMAIER_TUIE      ((rt_uint32_t)0x00000020)  /* Transmit Underflow interrupt enable */
#define EMAC_DMAIER_ROIE      ((rt_uint32_t)0x00000010)  /* Receive Overflow interrupt enable */
#define EMAC_DMAIER_TJTIE     ((rt_uint32_t)0x00000008)  /* Transmit jabber timeout interrupt enable */
#define EMAC_DMAIER_TBUIE     ((rt_uint32_t)0x00000004)  /* Transmit buffer unavailable interrupt enable */
#define EMAC_DMAIER_TPSIE     ((rt_uint32_t)0x00000002)  /* Transmit process stopped interrupt enable */
#define EMAC_DMAIER_TIE       ((rt_uint32_t)0x00000001)  /* Transmit interrupt enable */

/* Bit definition for Ethernet DMA Missed Frame and Buffer Overflow Counter Register */
#define EMAC_DMAMFBOCR_OFOC   ((rt_uint32_t)0x10000000)  /* Overflow bit for FIFO overflow counter */
#define EMAC_DMAMFBOCR_MFA    ((rt_uint32_t)0x0FFE0000)  /* Number of frames missed by the application */
#define EMAC_DMAMFBOCR_OMFC   ((rt_uint32_t)0x00010000)  /* Overflow bit for missed frame counter */
#define EMAC_DMAMFBOCR_MFC    ((rt_uint32_t)0x0000FFFF)  /* Number of frames missed by the controller */

/* Bit definition for Ethernet DMA Current Host Transmit Descriptor Register */
#define EMAC_DMACHTDR_HTDAP   ((rt_uint32_t)0xFFFFFFFF)  /* Host transmit descriptor address pointer */

/* Bit definition for Ethernet DMA Current Host Receive Descriptor Register */
#define EMAC_DMACHRDR_HRDAP   ((rt_uint32_t)0xFFFFFFFF)  /* Host receive descriptor address pointer */

/* Bit definition for Ethernet DMA Current Host Transmit Buffer Address Register */
#define EMAC_DMACHTBAR_HTBAP  ((rt_uint32_t)0xFFFFFFFF)  /* Host transmit buffer address pointer */

/* Bit definition for Ethernet DMA Current Host Receive Buffer Address Register */
#define EMAC_DMACHRBAR_HRBAP  ((rt_uint32_t)0xFFFFFFFF)  /* Host receive buffer address pointer */

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
	rt_uint32_t             EMAC_AutoNegotiation;           /* Selects or not the AutoNegotiation mode for the external PHY
															The AutoNegotiation allows an automatic setting of the Speed (10/100Mbps)
															and the mode (half/full-duplex).
															This parameter can be a value of @ref EMAC_AutoNegotiation */

	rt_uint32_t             EMAC_Watchdog;                  /* Selects or not the Watchdog timer
															When enabled, the MAC allows no more then 2048 bytes to be received.
															When disabled, the MAC can receive up to 16384 bytes.
															This parameter can be a value of @ref EMAC_watchdog */

	rt_uint32_t             EMAC_Jabber;                    /* Selects or not Jabber timer
															When enabled, the MAC allows no more then 2048 bytes to be sent.
															When disabled, the MAC can send up to 16384 bytes.
															This parameter can be a value of @ref EMAC_Jabber */

	rt_uint32_t             EMAC_InterFrameGap;             /* Selects the minimum IFG between frames during transmission
															This parameter can be a value of @ref EMAC_Inter_Frame_Gap */

	rt_uint32_t             EMAC_CarrierSense;              /* Selects or not the Carrier Sense
															This parameter can be a value of @ref EMAC_Carrier_Sense */

	rt_uint32_t             EMAC_Speed;                     /* Sets the Ethernet speed: 10/100 Mbps
															This parameter can be a value of @ref EMAC_Speed */

	rt_uint32_t             EMAC_ReceiveOwn;                /* Selects or not the ReceiveOwn
															ReceiveOwn allows the reception of frames when the TX_EN signal is asserted
															in Half-Duplex mode
															This parameter can be a value of @ref EMAC_Receive_Own */

	rt_uint32_t             EMAC_LoopbackMode;              /* Selects or not the internal MAC MII Loopback mode
															This parameter can be a value of @ref EMAC_Loop_Back_Mode */

	rt_uint32_t             EMAC_Mode;                      /* Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode
															This parameter can be a value of @ref EMAC_Duplex_Mode */

	rt_uint32_t             EMAC_ChecksumOffload;           /* Selects or not the IPv4 checksum checking for received frame payloads' TCP/UDP/ICMP headers.
															This parameter can be a value of @ref EMAC_Checksum_Offload */

	rt_uint32_t             EMAC_RetryTransmission;         /* Selects or not the MAC attempt retries transmission, based on the settings of BL,
															when a colision occurs (Half-Duplex mode)
															This parameter can be a value of @ref EMAC_Retry_Transmission */

	rt_uint32_t             EMAC_AutomaticPadCRCStrip;      /* Selects or not the Automatic MAC Pad/CRC Stripping
															This parameter can be a value of @ref EMAC_Automatic_Pad_CRC_Strip */

	rt_uint32_t             EMAC_BackOffLimit;              /* Selects the BackOff limit value
															This parameter can be a value of @ref EMAC_Back_Off_Limit */

	rt_uint32_t             EMAC_DeferralCheck;             /* Selects or not the deferral check function (Half-Duplex mode)
															This parameter can be a value of @ref EMAC_Deferral_Check */

	rt_uint32_t             EMAC_ReceiveAll;                /* Selects or not all frames reception by the MAC (No fitering)
															This parameter can be a value of @ref EMAC_Receive_All */

	rt_uint32_t             EMAC_SourceAddrFilter;          /* Selects the Source Address Filter mode
															This parameter can be a value of @ref EMAC_Source_Addr_Filter */

	rt_uint32_t             EMAC_PassControlFrames;         /* Sets the forwarding mode of the control frames (including unicast and multicast PAUSE frames)
															This parameter can be a value of @ref EMAC_Pass_Control_Frames */

	rt_uint32_t             EMAC_BroadcastFramesReception;  /* Selects or not the reception of Broadcast Frames
															This parameter can be a value of @ref EMAC_Broadcast_Frames_Reception */

	rt_uint32_t             EMAC_DestinationAddrFilter;     /* Sets the destination filter mode for both unicast and multicast frames
															This parameter can be a value of @ref EMAC_Destination_Addr_Filter */

	rt_uint32_t             EMAC_PromiscuousMode;           /* Selects or not the Promiscuous Mode
															This parameter can be a value of @ref EMAC_Promiscuous_Mode */

	rt_uint32_t             EMAC_MulticastFramesFilter;     /* Selects the Multicast Frames filter mode: None/HashTableFilter/PerfectFilter/PerfectHashTableFilter
															This parameter can be a value of @ref EMAC_Multicast_Frames_Filter */

	rt_uint32_t             EMAC_UnicastFramesFilter;       /* Selects the Unicast Frames filter mode: HashTableFilter/PerfectFilter/PerfectHashTableFilter
															This parameter can be a value of @ref EMAC_Unicast_Frames_Filter */

	rt_uint32_t             EMAC_HashTableHigh;             /* This field holds the higher 32 bits of Hash table.  */

	rt_uint32_t             EMAC_HashTableLow;              /* This field holds the lower 32 bits of Hash table.  */

	rt_uint32_t             EMAC_PauseTime;                 /* This field holds the value to be used in the Pause Time field in the
															transmit control frame */

	rt_uint32_t             EMAC_ZeroQuantaPause;           /* Selects or not the automatic generation of Zero-Quanta Pause Control frames
															This parameter can be a value of @ref EMAC_Zero_Quanta_Pause */

	rt_uint32_t             EMAC_PauseLowThreshold;         /* This field configures the threshold of the PAUSE to be checked for
															automatic retransmission of PAUSE Frame
															This parameter can be a value of @ref EMAC_Pause_Low_Threshold */

	rt_uint32_t             EMAC_UnicastPauseFrameDetect;   /* Selects or not the MAC detection of the Pause frames (with MAC Address0
															unicast address and unique multicast address)
															This parameter can be a value of @ref EMAC_Unicast_Pause_Frame_Detect */

	rt_uint32_t             EMAC_ReceiveFlowControl;        /* Enables or disables the MAC to decode the received Pause frame and
															disable its transmitter for a specified time (Pause Time)
															This parameter can be a value of @ref EMAC_Receive_Flow_Control */

	rt_uint32_t             EMAC_TransmitFlowControl;       /* Enables or disables the MAC to transmit Pause frames (Full-Duplex mode)
															or the MAC back-pressure operation (Half-Duplex mode)
															This parameter can be a value of @ref EMAC_Transmit_Flow_Control */

	rt_uint32_t             EMAC_VLANTagComparison;         /* Selects the 12-bit VLAN identifier or the complete 16-bit VLAN tag for
															comparison and filtering
															This parameter can be a value of @ref EMAC_VLAN_Tag_Comparison */

	rt_uint32_t             EMAC_VLANTagIdentifier;         /* Holds the VLAN tag identifier for receive frames */

	/**
	 * DMA
	 */

	rt_uint32_t             EMAC_DropTCPIPChecksumErrorFrame; /* Selects or not the Dropping of TCP/IP Checksum Error Frames
															  This parameter can be a value of @ref EMAC_Drop_TCP_IP_Checksum_Error_Frame */

	rt_uint32_t             EMAC_ReceiveStoreForward;         /* Enables or disables the Receive store and forward mode
															  This parameter can be a value of @ref EMAC_Receive_Store_Forward */

	rt_uint32_t             EMAC_FlushReceivedFrame;          /* Enables or disables the flushing of received frames
															  This parameter can be a value of @ref EMAC_Flush_Received_Frame */

	rt_uint32_t             EMAC_TransmitStoreForward;        /* Enables or disables Transmit store and forward mode
															  This parameter can be a value of @ref EMAC_Transmit_Store_Forward */

	rt_uint32_t             EMAC_TransmitThresholdControl;    /* Selects or not the Transmit Threshold Control
															  This parameter can be a value of @ref EMAC_Transmit_Threshold_Control */

	rt_uint32_t             EMAC_ForwardErrorFrames;          /* Selects or not the forward to the DMA of erroneous frames
															  This parameter can be a value of @ref EMAC_Forward_Error_Frames */

	rt_uint32_t             EMAC_ForwardUndersizedGoodFrames; /* Enables or disables the Rx FIFO to forward Undersized frames (frames with no Error
															  and length less than 64 bytes) including pad-bytes and CRC)
															  This parameter can be a value of @ref EMAC_Forward_Undersized_Good_Frames */

	rt_uint32_t             EMAC_ReceiveThresholdControl;     /* Selects the threshold level of the Receive FIFO
															  This parameter can be a value of @ref EMAC_Receive_Threshold_Control */

	rt_uint32_t             EMAC_SecondFrameOperate;          /* Selects or not the Operate on second frame mode, which allows the DMA to process a second
															  frame of Transmit data even before obtaining the status for the first frame.
															  This parameter can be a value of @ref EMAC_Second_Frame_Operate */

	rt_uint32_t             EMAC_AddressAlignedBeats;         /* Enables or disables the Address Aligned Beats
															  This parameter can be a value of @ref EMAC_Address_Aligned_Beats */

	rt_uint32_t             EMAC_FixedBurst;                  /* Enables or disables the AHB Master interface fixed burst transfers
															  This parameter can be a value of @ref EMAC_Fixed_Burst */

	rt_uint32_t             EMAC_RxDMABurstLength;            /* Indicates the maximum number of beats to be transferred in one Rx DMA transaction
															  This parameter can be a value of @ref EMAC_Rx_DMA_Burst_Length */

	rt_uint32_t             EMAC_TxDMABurstLength;            /* Indicates sthe maximum number of beats to be transferred in one Tx DMA transaction
															  This parameter can be a value of @ref EMAC_Tx_DMA_Burst_Length */

	rt_uint32_t             EMAC_DescriptorSkipLength;        /* Specifies the number of word to skip between two unchained int (Ring mode) */

	rt_uint32_t             EMAC_DMAArbitration;              /* Selects the DMA Tx/Rx arbitration
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
	rt_uint32_t   Status;                /* Status */
	rt_uint32_t   ControlBufferSize;     /* Control and Buffer1, Buffer2 lengths */
	rt_uint32_t   Buffer1Addr;           /* Buffer1 address pointer */
	rt_uint32_t   Buffer2NextDescAddr;   /* Buffer2 or next descriptor address pointer */
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

#define EMAC_DMATxDesc_OWN                     ((rt_uint32_t)0x80000000)  /* OWN bit: descriptor is owned by DMA engine */
#define EMAC_DMATxDesc_IC                      ((rt_uint32_t)0x40000000)  /* Interrupt on Completion */
#define EMAC_DMATxDesc_LS                      ((rt_uint32_t)0x20000000)  /* Last Segment */
#define EMAC_DMATxDesc_FS                      ((rt_uint32_t)0x10000000)  /* First Segment */
#define EMAC_DMATxDesc_DC                      ((rt_uint32_t)0x08000000)  /* Disable CRC */
#define EMAC_DMATxDesc_DP                      ((rt_uint32_t)0x04000000)  /* Disable Padding */
#define EMAC_DMATxDesc_TTSE                    ((rt_uint32_t)0x02000000)  /* Transmit Time Stamp Enable */
#define EMAC_DMATxDesc_CIC                     ((rt_uint32_t)0x00C00000)  /* Checksum Insertion Control: 4 cases */
#define EMAC_DMATxDesc_CIC_ByPass              ((rt_uint32_t)0x00000000)  /* Do Nothing: Checksum Engine is bypassed */
#define EMAC_DMATxDesc_CIC_IPV4Header          ((rt_uint32_t)0x00400000)  /* IPV4 header Checksum Insertion */
#define EMAC_DMATxDesc_CIC_TCPUDPICMP_Segment  ((rt_uint32_t)0x00800000)  /* TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define EMAC_DMATxDesc_CIC_TCPUDPICMP_Full     ((rt_uint32_t)0x00C00000)  /* TCP/UDP/ICMP Checksum Insertion fully calculated */
#define EMAC_DMATxDesc_TER                     ((rt_uint32_t)0x00200000)  /* Transmit End of Ring */
#define EMAC_DMATxDesc_TCH                     ((rt_uint32_t)0x00100000)  /* Second Address Chained */
#define EMAC_DMATxDesc_TTSS                    ((rt_uint32_t)0x00020000)  /* Tx Time Stamp Status */
#define EMAC_DMATxDesc_IHE                     ((rt_uint32_t)0x00010000)  /* IP Header Error */
#define EMAC_DMATxDesc_ES                      ((rt_uint32_t)0x00008000)  /* Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF || JT */
#define EMAC_DMATxDesc_JT                      ((rt_uint32_t)0x00004000)  /* Jabber Timeout */
#define EMAC_DMATxDesc_FF                      ((rt_uint32_t)0x00002000)  /* Frame Flushed: DMA/MTL flushed the frame due to SW flush */
#define EMAC_DMATxDesc_PCE                     ((rt_uint32_t)0x00001000)  /* Payload Checksum Error */
#define EMAC_DMATxDesc_LCA                     ((rt_uint32_t)0x00000800)  /* Loss of Carrier: carrier lost during transmission */
#define EMAC_DMATxDesc_NC                      ((rt_uint32_t)0x00000400)  /* No Carrier: no carrier signal from the transceiver */
#define EMAC_DMATxDesc_LCO                     ((rt_uint32_t)0x00000200)  /* Late Collision: transmission aborted due to collision */
#define EMAC_DMATxDesc_EC                      ((rt_uint32_t)0x00000100)  /* Excessive Collision: transmission aborted after 16 collisions */
#define EMAC_DMATxDesc_VF                      ((rt_uint32_t)0x00000080)  /* VLAN Frame */
#define EMAC_DMATxDesc_CC                      ((rt_uint32_t)0x00000078)  /* Collision Count */
#define EMAC_DMATxDesc_ED                      ((rt_uint32_t)0x00000004)  /* Excessive Deferral */
#define EMAC_DMATxDesc_UF                      ((rt_uint32_t)0x00000002)  /* Underflow Error: late data arrival from the memory */
#define EMAC_DMATxDesc_DB                      ((rt_uint32_t)0x00000001)  /* Deferred Bit */

#define EMAC_DMATxDesc_TBS2  ((rt_uint32_t)0x1FFF0000)  /* Transmit Buffer2 Size */
#define EMAC_DMATxDesc_TBS1  ((rt_uint32_t)0x00001FFF)  /* Transmit Buffer1 Size */

#define EMAC_DMATxDesc_B1AP  ((rt_uint32_t)0xFFFFFFFF)  /* Buffer1 Address Pointer */

#define EMAC_DMATxDesc_B2AP  ((rt_uint32_t)0xFFFFFFFF)  /* Buffer2 Address Pointer */

#define EMAC_DMARxDesc_OWN         ((rt_uint32_t)0x80000000)  /* OWN bit: descriptor is owned by DMA engine  */
#define EMAC_DMARxDesc_AFM         ((rt_uint32_t)0x40000000)  /* DA Filter Fail for the rx frame  */
#define EMAC_DMARxDesc_FL          ((rt_uint32_t)0x3FFF0000)  /* Receive descriptor frame length  */
#define EMAC_DMARxDesc_ES          ((rt_uint32_t)0x00008000)  /* Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE */
#define EMAC_DMARxDesc_DE          ((rt_uint32_t)0x00004000)  /* Descriptor error: no more int for receive frame  */
#define EMAC_DMARxDesc_SAF         ((rt_uint32_t)0x00002000)  /* SA Filter Fail for the received frame */
#define EMAC_DMARxDesc_LE          ((rt_uint32_t)0x00001000)  /* Frame size not matching with length field */
#define EMAC_DMARxDesc_OE          ((rt_uint32_t)0x00000800)  /* Overflow Error: Frame was damaged due to buffer overflow */
#define EMAC_DMARxDesc_VLAN        ((rt_uint32_t)0x00000400)  /* VLAN Tag: received frame is a VLAN frame */
#define EMAC_DMARxDesc_FS          ((rt_uint32_t)0x00000200)  /* First descriptor of the frame  */
#define EMAC_DMARxDesc_LS          ((rt_uint32_t)0x00000100)  /* Last descriptor of the frame  */
#define EMAC_DMARxDesc_IPV4HCE     ((rt_uint32_t)0x00000080)  /* IPC Checksum Error: Rx Ipv4 header checksum error   */
#define EMAC_DMARxDesc_LC          ((rt_uint32_t)0x00000040)  /* Late collision occurred during reception   */
#define EMAC_DMARxDesc_FT          ((rt_uint32_t)0x00000020)  /* Frame type - Ethernet, otherwise 802.3    */
#define EMAC_DMARxDesc_RWT         ((rt_uint32_t)0x00000010)  /* Receive Watchdog Timeout: watchdog timer expired during reception    */
#define EMAC_DMARxDesc_RE          ((rt_uint32_t)0x00000008)  /* Receive error: error reported by MII interface  */
#define EMAC_DMARxDesc_DBE         ((rt_uint32_t)0x00000004)  /* Dribble bit error: frame contains non int multiple of 8 bits  */
#define EMAC_DMARxDesc_CE          ((rt_uint32_t)0x00000002)  /* CRC error */
#define EMAC_DMARxDesc_MAMPCE      ((rt_uint32_t)0x00000001)  /* Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error */

#define EMAC_DMARxDesc_DIC   ((rt_uint32_t)0x80000000)  /* Disable Interrupt on Completion */
#define EMAC_DMARxDesc_RBS2  ((rt_uint32_t)0x1FFF0000)  /* Receive Buffer2 Size */
#define EMAC_DMARxDesc_RER   ((rt_uint32_t)0x00008000)  /* Receive End of Ring */
#define EMAC_DMARxDesc_RCH   ((rt_uint32_t)0x00004000)  /* Second Address Chained */
#define EMAC_DMARxDesc_RBS1  ((rt_uint32_t)0x00001FFF)  /* Receive Buffer1 Size */

#define EMAC_DMARxDesc_B1AP  ((rt_uint32_t)0xFFFFFFFF)  /* Buffer1 Address Pointer */

#define EMAC_DMARxDesc_B2AP  ((rt_uint32_t)0xFFFFFFFF)  /* Buffer2 Address Pointer */

#define PHY_READ_TO                     ((rt_uint32_t)0x0004FFFF)
#define PHY_WRITE_TO                    ((rt_uint32_t)0x0004FFFF)

#define PHY_ResetDelay                  ((rt_uint32_t)0x000FFFFF)

#define PHY_ConfigDelay                 ((rt_uint32_t)0x00FFFFFF)

#define PHY_BCR                          0          /* Tranceiver Basic Control Register */
#define PHY_BSR                          1          /* Tranceiver Basic Status Register */

#define PHY_Reset                       ((rt_uint16_t)0x8000)      /* PHY Reset */
//#define PHY_Loopback                    ((rt_uint16_t)0x4000)      /* Select loop-back mode */
//#define PHY_FULLDUPLEX_100M             ((rt_uint16_t)0x2100)      /* Set the full-duplex mode at 100 Mb/s */
//#define PHY_HALFDUPLEX_100M             ((rt_uint16_t)0x2000)      /* Set the half-duplex mode at 100 Mb/s */
//#define PHY_FULLDUPLEX_10M              ((rt_uint16_t)0x0100)      /* Set the full-duplex mode at 10 Mb/s */
//#define PHY_HALFDUPLEX_10M              ((rt_uint16_t)0x0000)      /* Set the half-duplex mode at 10 Mb/s */
//#define PHY_AutoNegotiation             ((rt_uint16_t)0x1000)      /* Enable auto-negotiation function */
//#define PHY_Restart_AutoNegotiation     ((rt_uint16_t)0x0200)      /* Restart auto-negotiation function */
//#define PHY_Powerdown                   ((rt_uint16_t)0x0800)      /* Select the power down mode */
//#define PHY_Isolate                     ((rt_uint16_t)0x0400)      /* Isolate PHY from MII */
//
//#define PHY_AutoNego_Complete           ((rt_uint16_t)0x0020)      /* Auto-Negotiation process completed */
//#define PHY_Linked_Status               ((rt_uint16_t)0x0004)      /* Valid link established */
//#define PHY_Jabber_detection            ((rt_uint16_t)0x0002)      /* Jabber condition detected */
//
//#define PHY_SR                           16     /* Transceiver Status Register */
//
//#define PHY_Speed_Status            ((rt_uint16_t)0x0002)    /* Configured information of Speed: 10Mbps */
//#define PHY_Duplex_Status           ((rt_uint16_t)0x0004)    /* Configured information of Duplex: Full-duplex */

#define EMAC_AutoNegotiation_Enable     ((rt_uint32_t)0x00000001)
#define EMAC_AutoNegotiation_Disable    ((rt_uint32_t)0x00000000)

#define EMAC_Watchdog_Enable       ((rt_uint32_t)0x00000000)
#define EMAC_Watchdog_Disable      ((rt_uint32_t)0x00800000)

#define EMAC_Jabber_Enable    ((rt_uint32_t)0x00000000)
#define EMAC_Jabber_Disable   ((rt_uint32_t)0x00400000)

#define EMAC_InterFrameGap_96Bit   ((rt_uint32_t)0x00000000)  /* minimum IFG between frames during transmission is 96Bit */
#define EMAC_InterFrameGap_88Bit   ((rt_uint32_t)0x00020000)  /* minimum IFG between frames during transmission is 88Bit */
#define EMAC_InterFrameGap_80Bit   ((rt_uint32_t)0x00040000)  /* minimum IFG between frames during transmission is 80Bit */
#define EMAC_InterFrameGap_72Bit   ((rt_uint32_t)0x00060000)  /* minimum IFG between frames during transmission is 72Bit */
#define EMAC_InterFrameGap_64Bit   ((rt_uint32_t)0x00080000)  /* minimum IFG between frames during transmission is 64Bit */
#define EMAC_InterFrameGap_56Bit   ((rt_uint32_t)0x000A0000)  /* minimum IFG between frames during transmission is 56Bit */
#define EMAC_InterFrameGap_48Bit   ((rt_uint32_t)0x000C0000)  /* minimum IFG between frames during transmission is 48Bit */
#define EMAC_InterFrameGap_40Bit   ((rt_uint32_t)0x000E0000)  /* minimum IFG between frames during transmission is 40Bit */

#define EMAC_CarrierSense_Enable   ((rt_uint32_t)0x00000000)
#define EMAC_CarrierSense_Disable  ((rt_uint32_t)0x00010000)

#define EMAC_Speed_10M        ((rt_uint32_t)0x00000000)
#define EMAC_Speed_100M       ((rt_uint32_t)0x00004000)

#define EMAC_ReceiveOwn_Enable     ((rt_uint32_t)0x00000000)
#define EMAC_ReceiveOwn_Disable    ((rt_uint32_t)0x00002000)

#define EMAC_LoopbackMode_Enable        ((rt_uint32_t)0x00001000)
#define EMAC_LoopbackMode_Disable       ((rt_uint32_t)0x00000000)

#define EMAC_Mode_FullDuplex       ((rt_uint32_t)0x00000800)
#define EMAC_Mode_HalfDuplex       ((rt_uint32_t)0x00000000)

#define EMAC_ChecksumOffload_Enable     ((rt_uint32_t)0x00000400)
#define EMAC_ChecksumOffload_Disable    ((rt_uint32_t)0x00000000)

#define EMAC_RetryTransmission_Enable   ((rt_uint32_t)0x00000000)
#define EMAC_RetryTransmission_Disable  ((rt_uint32_t)0x00000200)

#define EMAC_AutomaticPadCRCStrip_Enable     ((rt_uint32_t)0x00000080)
#define EMAC_AutomaticPadCRCStrip_Disable    ((rt_uint32_t)0x00000000)

#define EMAC_BackOffLimit_10  ((rt_uint32_t)0x00000000)
#define EMAC_BackOffLimit_8   ((rt_uint32_t)0x00000020)
#define EMAC_BackOffLimit_4   ((rt_uint32_t)0x00000040)
#define EMAC_BackOffLimit_1   ((rt_uint32_t)0x00000060)

#define EMAC_DeferralCheck_Enable       ((rt_uint32_t)0x00000010)
#define EMAC_DeferralCheck_Disable      ((rt_uint32_t)0x00000000)

#define EMAC_ReceiveAll_Enable     ((rt_uint32_t)0x80000000)
#define EMAC_ReceiveAll_Disable    ((rt_uint32_t)0x00000000)

#define EMAC_SourceAddrFilter_Normal_Enable       ((rt_uint32_t)0x00000200)
#define EMAC_SourceAddrFilter_Inverse_Enable      ((rt_uint32_t)0x00000300)
#define EMAC_SourceAddrFilter_Disable             ((rt_uint32_t)0x00000000)

#define EMAC_PassControlFrames_BlockAll                ((rt_uint32_t)0x00000040)  /* MAC filters all control frames from reaching the application */
#define EMAC_PassControlFrames_ForwardAll              ((rt_uint32_t)0x00000080)  /* MAC forwards all control frames to application even if they fail the Address Filter */
#define EMAC_PassControlFrames_ForwardPassedAddrFilter ((rt_uint32_t)0x000000C0)  /* MAC forwards control frames that pass the Address Filter. */

#define EMAC_BroadcastFramesReception_Enable      ((rt_uint32_t)0x00000000)
#define EMAC_BroadcastFramesReception_Disable     ((rt_uint32_t)0x00000020)

#define EMAC_DestinationAddrFilter_Normal    ((rt_uint32_t)0x00000000)
#define EMAC_DestinationAddrFilter_Inverse   ((rt_uint32_t)0x00000008)

#define EMAC_PromiscuousMode_Enable     ((rt_uint32_t)0x00000001)
#define EMAC_PromiscuousMode_Disable    ((rt_uint32_t)0x00000000)

#define EMAC_MulticastFramesFilter_PerfectHashTable    ((rt_uint32_t)0x00000404)
#define EMAC_MulticastFramesFilter_HashTable           ((rt_uint32_t)0x00000004)
#define EMAC_MulticastFramesFilter_Perfect             ((rt_uint32_t)0x00000000)
#define EMAC_MulticastFramesFilter_None                ((rt_uint32_t)0x00000010)

#define EMAC_UnicastFramesFilter_PerfectHashTable ((rt_uint32_t)0x00000402)
#define EMAC_UnicastFramesFilter_HashTable        ((rt_uint32_t)0x00000002)
#define EMAC_UnicastFramesFilter_Perfect          ((rt_uint32_t)0x00000000)

#define EMAC_ZeroQuantaPause_Enable     ((rt_uint32_t)0x00000000)
#define EMAC_ZeroQuantaPause_Disable    ((rt_uint32_t)0x00000080)

#define EMAC_PauseLowThreshold_Minus4        ((rt_uint32_t)0x00000000)  /* Pause time minus 4 slot times */
#define EMAC_PauseLowThreshold_Minus28       ((rt_uint32_t)0x00000010)  /* Pause time minus 28 slot times */
#define EMAC_PauseLowThreshold_Minus144      ((rt_uint32_t)0x00000020)  /* Pause time minus 144 slot times */
#define EMAC_PauseLowThreshold_Minus256      ((rt_uint32_t)0x00000030)  /* Pause time minus 256 slot times */

#define EMAC_UnicastPauseFrameDetect_Enable  ((rt_uint32_t)0x00000008)
#define EMAC_UnicastPauseFrameDetect_Disable ((rt_uint32_t)0x00000000)

#define EMAC_ReceiveFlowControl_Enable       ((rt_uint32_t)0x00000004)
#define EMAC_ReceiveFlowControl_Disable      ((rt_uint32_t)0x00000000)
#define EMAC_TransmitFlowControl_Enable      ((rt_uint32_t)0x00000002)
#define EMAC_TransmitFlowControl_Disable     ((rt_uint32_t)0x00000000)

#define EMAC_VLANTagComparison_12Bit    ((rt_uint32_t)0x00010000)
#define EMAC_VLANTagComparison_16Bit    ((rt_uint32_t)0x00000000)

#define EMAC_MAC_FLAG_TST     ((rt_uint32_t)0x00000200)  /* Time stamp trigger flag (on MAC) */
#define EMAC_MAC_FLAG_MMCT    ((rt_uint32_t)0x00000040)  /* MMC transmit flag  */
#define EMAC_MAC_FLAG_MMCR    ((rt_uint32_t)0x00000020)  /* MMC receive flag */
#define EMAC_MAC_FLAG_MMC     ((rt_uint32_t)0x00000010)  /* MMC flag (on MAC) */
#define EMAC_MAC_FLAG_PMT     ((rt_uint32_t)0x00000008)  /* PMT flag (on MAC) */

#define EMAC_MAC_IT_TST       ((rt_uint32_t)0x00000200)  /* Time stamp trigger interrupt (on MAC) */
#define EMAC_MAC_IT_MMCT      ((rt_uint32_t)0x00000040)  /* MMC transmit interrupt */
#define EMAC_MAC_IT_MMCR      ((rt_uint32_t)0x00000020)  /* MMC receive interrupt */
#define EMAC_MAC_IT_MMC       ((rt_uint32_t)0x00000010)  /* MMC interrupt (on MAC) */
#define EMAC_MAC_IT_PMT       ((rt_uint32_t)0x00000008)  /* PMT interrupt (on MAC) */

#define EMAC_MAC_Address0     ((rt_uint32_t)0x00000000)
#define EMAC_MAC_Address1     ((rt_uint32_t)0x00000008)
#define EMAC_MAC_Address2     ((rt_uint32_t)0x00000010)
#define EMAC_MAC_Address3     ((rt_uint32_t)0x00000018)

#define EMAC_MAC_AddressFilter_SA       ((rt_uint32_t)0x00000000)
#define EMAC_MAC_AddressFilter_DA       ((rt_uint32_t)0x00000008)

#define EMAC_MAC_AddressMask_Byte6      ((rt_uint32_t)0x20000000)  /* Mask MAC Address high reg bits [15:8] */
#define EMAC_MAC_AddressMask_Byte5      ((rt_uint32_t)0x10000000)  /* Mask MAC Address high reg bits [7:0] */
#define EMAC_MAC_AddressMask_Byte4      ((rt_uint32_t)0x08000000)  /* Mask MAC Address low reg bits [31:24] */
#define EMAC_MAC_AddressMask_Byte3      ((rt_uint32_t)0x04000000)  /* Mask MAC Address low reg bits [23:16] */
#define EMAC_MAC_AddressMask_Byte2      ((rt_uint32_t)0x02000000)  /* Mask MAC Address low reg bits [15:8] */
#define EMAC_MAC_AddressMask_Byte1      ((rt_uint32_t)0x01000000)  /* Mask MAC Address low reg bits [70] */

#define EMAC_DMATxDesc_LastSegment      ((rt_uint32_t)0x40000000)  /* Last Segment */
#define EMAC_DMATxDesc_FirstSegment     ((rt_uint32_t)0x20000000)  /* First Segment */

#define EMAC_DMATxDesc_ChecksumByPass             ((rt_uint32_t)0x00000000)   /* Checksum engine bypass */
#define EMAC_DMATxDesc_ChecksumIPV4Header         ((rt_uint32_t)0x00400000)   /* IPv4 header checksum insertion  */
#define EMAC_DMATxDesc_ChecksumTCPUDPICMPSegment  ((rt_uint32_t)0x00800000)   /* TCP/UDP/ICMP checksum insertion. Pseudo header checksum is assumed to be present */
#define EMAC_DMATxDesc_ChecksumTCPUDPICMPFull     ((rt_uint32_t)0x00C00000)   /* TCP/UDP/ICMP checksum fully in hardware including pseudo header */

#define EMAC_DMARxDesc_Buffer1     ((rt_uint32_t)0x00000000)  /* DMA Rx Desc Buffer1 */
#define EMAC_DMARxDesc_Buffer2     ((rt_uint32_t)0x00000001)  /* DMA Rx Desc Buffer2 */

#define EMAC_DropTCPIPChecksumErrorFrame_Enable   ((rt_uint32_t)0x00000000)
#define EMAC_DropTCPIPChecksumErrorFrame_Disable  ((rt_uint32_t)0x04000000)

#define EMAC_ReceiveStoreForward_Enable      ((rt_uint32_t)0x02000000)
#define EMAC_ReceiveStoreForward_Disable     ((rt_uint32_t)0x00000000)

#define EMAC_FlushReceivedFrame_Enable       ((rt_uint32_t)0x00000000)
#define EMAC_FlushReceivedFrame_Disable      ((rt_uint32_t)0x01000000)

#define EMAC_TransmitStoreForward_Enable     ((rt_uint32_t)0x00200000)
#define EMAC_TransmitStoreForward_Disable    ((rt_uint32_t)0x00000000)

#define EMAC_TransmitThresholdControl_64Bytes     ((rt_uint32_t)0x00000000)  /* threshold level of the MTL Transmit FIFO is 64 Bytes */
#define EMAC_TransmitThresholdControl_128Bytes    ((rt_uint32_t)0x00004000)  /* threshold level of the MTL Transmit FIFO is 128 Bytes */
#define EMAC_TransmitThresholdControl_192Bytes    ((rt_uint32_t)0x00008000)  /* threshold level of the MTL Transmit FIFO is 192 Bytes */
#define EMAC_TransmitThresholdControl_256Bytes    ((rt_uint32_t)0x0000C000)  /* threshold level of the MTL Transmit FIFO is 256 Bytes */
#define EMAC_TransmitThresholdControl_40Bytes     ((rt_uint32_t)0x00010000)  /* threshold level of the MTL Transmit FIFO is 40 Bytes */
#define EMAC_TransmitThresholdControl_32Bytes     ((rt_uint32_t)0x00014000)  /* threshold level of the MTL Transmit FIFO is 32 Bytes */
#define EMAC_TransmitThresholdControl_24Bytes     ((rt_uint32_t)0x00018000)  /* threshold level of the MTL Transmit FIFO is 24 Bytes */
#define EMAC_TransmitThresholdControl_16Bytes     ((rt_uint32_t)0x0001C000)  /* threshold level of the MTL Transmit FIFO is 16 Bytes */

#define EMAC_ForwardErrorFrames_Enable       ((rt_uint32_t)0x00000080)
#define EMAC_ForwardErrorFrames_Disable      ((rt_uint32_t)0x00000000)

#define EMAC_ForwardUndersizedGoodFrames_Enable   ((rt_uint32_t)0x00000040)
#define EMAC_ForwardUndersizedGoodFrames_Disable  ((rt_uint32_t)0x00000000)

#define EMAC_ReceiveThresholdControl_64Bytes      ((rt_uint32_t)0x00000000)  /* threshold level of the MTL Receive FIFO is 64 Bytes */
#define EMAC_ReceiveThresholdControl_32Bytes      ((rt_uint32_t)0x00000008)  /* threshold level of the MTL Receive FIFO is 32 Bytes */
#define EMAC_ReceiveThresholdControl_96Bytes      ((rt_uint32_t)0x00000010)  /* threshold level of the MTL Receive FIFO is 96 Bytes */
#define EMAC_ReceiveThresholdControl_128Bytes     ((rt_uint32_t)0x00000018)  /* threshold level of the MTL Receive FIFO is 128 Bytes */

#define EMAC_SecondFrameOperate_Enable       ((rt_uint32_t)0x00000004)
#define EMAC_SecondFrameOperate_Disable      ((rt_uint32_t)0x00000000)

#define EMAC_AddressAlignedBeats_Enable      ((rt_uint32_t)0x02000000)
#define EMAC_AddressAlignedBeats_Disable     ((rt_uint32_t)0x00000000)

#define EMAC_FixedBurst_Enable     ((rt_uint32_t)0x00010000)
#define EMAC_FixedBurst_Disable    ((rt_uint32_t)0x00000000)

#define EMAC_RxDMABurstLength_1Beat          ((rt_uint32_t)0x00020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define EMAC_RxDMABurstLength_2Beat          ((rt_uint32_t)0x00040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define EMAC_RxDMABurstLength_4Beat          ((rt_uint32_t)0x00080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_RxDMABurstLength_8Beat          ((rt_uint32_t)0x00100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_RxDMABurstLength_16Beat         ((rt_uint32_t)0x00200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_RxDMABurstLength_32Beat         ((rt_uint32_t)0x00400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_RxDMABurstLength_4xPBL_4Beat    ((rt_uint32_t)0x01020000)  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define EMAC_RxDMABurstLength_4xPBL_8Beat    ((rt_uint32_t)0x01040000)  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define EMAC_RxDMABurstLength_4xPBL_16Beat   ((rt_uint32_t)0x01080000)  /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define EMAC_RxDMABurstLength_4xPBL_32Beat   ((rt_uint32_t)0x01100000)  /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define EMAC_RxDMABurstLength_4xPBL_64Beat   ((rt_uint32_t)0x01200000)  /* maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define EMAC_RxDMABurstLength_4xPBL_128Beat  ((rt_uint32_t)0x01400000)  /* maximum number of beats to be transferred in one RxDMA transaction is 128 */

#define EMAC_TxDMABurstLength_1Beat          ((rt_uint32_t)0x00000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define EMAC_TxDMABurstLength_2Beat          ((rt_uint32_t)0x00000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define EMAC_TxDMABurstLength_4Beat          ((rt_uint32_t)0x00000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_TxDMABurstLength_8Beat          ((rt_uint32_t)0x00000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_TxDMABurstLength_16Beat         ((rt_uint32_t)0x00001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_TxDMABurstLength_32Beat         ((rt_uint32_t)0x00002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_TxDMABurstLength_4xPBL_4Beat    ((rt_uint32_t)0x01000100)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define EMAC_TxDMABurstLength_4xPBL_8Beat    ((rt_uint32_t)0x01000200)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define EMAC_TxDMABurstLength_4xPBL_16Beat   ((rt_uint32_t)0x01000400)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define EMAC_TxDMABurstLength_4xPBL_32Beat   ((rt_uint32_t)0x01000800)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define EMAC_TxDMABurstLength_4xPBL_64Beat   ((rt_uint32_t)0x01001000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define EMAC_TxDMABurstLength_4xPBL_128Beat  ((rt_uint32_t)0x01002000)  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */

#define EMAC_DMAArbitration_RoundRobin_RxTx_1_1   ((rt_uint32_t)0x00000000)
#define EMAC_DMAArbitration_RoundRobin_RxTx_2_1   ((rt_uint32_t)0x00004000)
#define EMAC_DMAArbitration_RoundRobin_RxTx_3_1   ((rt_uint32_t)0x00008000)
#define EMAC_DMAArbitration_RoundRobin_RxTx_4_1   ((rt_uint32_t)0x0000C000)
#define EMAC_DMAArbitration_RxPriorTx             ((rt_uint32_t)0x00000002)

#define EMAC_DMA_FLAG_TST               ((rt_uint32_t)0x20000000)  /* Time-stamp trigger interrupt (on DMA) */
#define EMAC_DMA_FLAG_PMT               ((rt_uint32_t)0x10000000)  /* PMT interrupt (on DMA) */
#define EMAC_DMA_FLAG_MMC               ((rt_uint32_t)0x08000000)  /* MMC interrupt (on DMA) */
#define EMAC_DMA_FLAG_DataTransferError ((rt_uint32_t)0x00800000)  /* Error bits 0-Rx DMA, 1-Tx DMA */
#define EMAC_DMA_FLAG_ReadWriteError    ((rt_uint32_t)0x01000000)  /* Error bits 0-write transfer, 1-read transfer */
#define EMAC_DMA_FLAG_AccessError       ((rt_uint32_t)0x02000000)  /* Error bits 0-data buffer, 1-desc. access */
#define EMAC_DMA_FLAG_NIS               ((rt_uint32_t)0x00010000)  /* Normal interrupt summary flag */
#define EMAC_DMA_FLAG_AIS               ((rt_uint32_t)0x00008000)  /* Abnormal interrupt summary flag */
#define EMAC_DMA_FLAG_ER                ((rt_uint32_t)0x00004000)  /* Early receive flag */
#define EMAC_DMA_FLAG_FBE               ((rt_uint32_t)0x00002000)  /* Fatal bus error flag */
#define EMAC_DMA_FLAG_ET                ((rt_uint32_t)0x00000400)  /* Early transmit flag */
#define EMAC_DMA_FLAG_RWT               ((rt_uint32_t)0x00000200)  /* Receive watchdog timeout flag */
#define EMAC_DMA_FLAG_RPS               ((rt_uint32_t)0x00000100)  /* Receive process stopped flag */
#define EMAC_DMA_FLAG_RBU               ((rt_uint32_t)0x00000080)  /* Receive buffer unavailable flag */
#define EMAC_DMA_FLAG_R                 ((rt_uint32_t)0x00000040)  /* Receive flag */
#define EMAC_DMA_FLAG_TU                ((rt_uint32_t)0x00000020)  /* Underflow flag */
#define EMAC_DMA_FLAG_RO                ((rt_uint32_t)0x00000010)  /* Overflow flag */
#define EMAC_DMA_FLAG_TJT               ((rt_uint32_t)0x00000008)  /* Transmit jabber timeout flag */
#define EMAC_DMA_FLAG_TBU               ((rt_uint32_t)0x00000004)  /* Transmit buffer unavailable flag */
#define EMAC_DMA_FLAG_TPS               ((rt_uint32_t)0x00000002)  /* Transmit process stopped flag */
#define EMAC_DMA_FLAG_T                 ((rt_uint32_t)0x00000001)  /* Transmit flag */

#define EMAC_DMA_INT_GLPII     ((rt_uint32_t)(1UL<<30))  /* GMAC LPI Interrupt. */
#define EMAC_DMA_INT_TTI       ((rt_uint32_t)(1UL<<29))  /* Time-Stamp Trigger Interrupt. */
#define EMAC_DMA_INT_GPI       ((rt_uint32_t)(1UL<<28))  /* GMAC PMT Interrupt. */
#define EMAC_DMA_INT_GMI       ((rt_uint32_t)(1UL<<27))  /* GMAC MMC Interrupt. */
#define EMAC_DMA_INT_GLI       ((rt_uint32_t)(1UL<<26))  /* GMAC Line interface Interrupt. */
#define EMAC_DMA_INT_NIS       ((rt_uint32_t)(1UL<<16))  /* Normal interrupt summary. */
#define EMAC_DMA_INT_AIS       ((rt_uint32_t)(1UL<<15))  /* Abnormal interrupt summary. */
#define EMAC_DMA_INT_ER        ((rt_uint32_t)0x00004000)  /* Early receive interrupt */
#define EMAC_DMA_INT_FBE       ((rt_uint32_t)0x00002000)  /* Fatal bus error interrupt */
#define EMAC_DMA_INT_ET        ((rt_uint32_t)0x00000400)  /* Early transmit interrupt */
#define EMAC_DMA_INT_RWT       ((rt_uint32_t)0x00000200)  /* Receive watchdog timeout interrupt */
#define EMAC_DMA_INT_RPS       ((rt_uint32_t)0x00000100)  /* Receive process stopped interrupt */
#define EMAC_DMA_INT_RBU       ((rt_uint32_t)0x00000080)  /* Receive buffer unavailable interrupt */
#define EMAC_DMA_INT_R         ((rt_uint32_t)0x00000040)  /* Receive interrupt */
#define EMAC_DMA_INT_TU        ((rt_uint32_t)0x00000020)  /* Underflow interrupt */
#define EMAC_DMA_INT_RO        ((rt_uint32_t)0x00000010)  /* Overflow interrupt */
#define EMAC_DMA_INT_TJT       ((rt_uint32_t)0x00000008)  /* Transmit jabber timeout interrupt */
#define EMAC_DMA_INT_TBU       ((rt_uint32_t)0x00000004)  /* Transmit buffer unavailable interrupt */
#define EMAC_DMA_INT_TPS       ((rt_uint32_t)0x00000002)  /* Transmit process stopped interrupt */
#define EMAC_DMA_INT_T         ((rt_uint32_t)0x00000001)  /* Transmit interrupt */

#define EMAC_DMA_TransmitProcess_Stopped     ((rt_uint32_t)0x00000000)  /* Stopped - Reset or Stop Tx Command issued */
#define EMAC_DMA_TransmitProcess_Fetching    ((rt_uint32_t)0x00100000)  /* Running - fetching the Tx descriptor */
#define EMAC_DMA_TransmitProcess_Waiting     ((rt_uint32_t)0x00200000)  /* Running - waiting for status */
#define EMAC_DMA_TransmitProcess_Reading     ((rt_uint32_t)0x00300000)  /* Running - reading the data from host memory */
#define EMAC_DMA_TransmitProcess_Suspended   ((rt_uint32_t)0x00600000)  /* Suspended - Tx Descriptor unavailable */
#define EMAC_DMA_TransmitProcess_Closing     ((rt_uint32_t)0x00700000)  /* Running - closing Rx descriptor */

#define EMAC_DMA_ReceiveProcess_Stopped      ((rt_uint32_t)0x00000000)  /* Stopped - Reset or Stop Rx Command issued */
#define EMAC_DMA_ReceiveProcess_Fetching     ((rt_uint32_t)0x00020000)  /* Running - fetching the Rx descriptor */
#define EMAC_DMA_ReceiveProcess_Waiting      ((rt_uint32_t)0x00060000)  /* Running - waiting for packet */
#define EMAC_DMA_ReceiveProcess_Suspended    ((rt_uint32_t)0x00080000)  /* Suspended - Rx Descriptor unavailable */
#define EMAC_DMA_ReceiveProcess_Closing      ((rt_uint32_t)0x000A0000)  /* Running - closing descriptor */
#define EMAC_DMA_ReceiveProcess_Queuing      ((rt_uint32_t)0x000E0000)  /* Running - queuing the receive frame into host memory */

#define EMAC_DMA_Overflow_RxFIFOCounter      ((rt_uint32_t)0x10000000)  /* Overflow bit for FIFO overflow counter */
#define EMAC_DMA_Overflow_MissedFrameCounter ((rt_uint32_t)0x00010000)  /* Overflow bit for missed frame counter */

#define EMAC_PMT_FLAG_WUFFRPR      ((rt_uint32_t)0x80000000)  /* Wake-Up Frame Filter Register Pointer Reset */
#define EMAC_PMT_FLAG_WUFR         ((rt_uint32_t)0x00000040)  /* Wake-Up Frame Received */
#define EMAC_PMT_FLAG_MPR          ((rt_uint32_t)0x00000020)  /* Magic Packet Received */

#define EMAC_MMC_IT_TGF       ((rt_uint32_t)0x00200000)  /* When Tx good frame counter reaches half the maximum value */
#define EMAC_MMC_IT_TGFMSC    ((rt_uint32_t)0x00008000)  /* When Tx good multi col counter reaches half the maximum value */
#define EMAC_MMC_IT_TGFSC     ((rt_uint32_t)0x00004000)  /* When Tx good single col counter reaches half the maximum value */
#define EMAC_MMC_IT_RGUF      ((rt_uint32_t)0x10020000)  /* When Rx good unicast frames counter reaches half the maximum value */
#define EMAC_MMC_IT_RFAE      ((rt_uint32_t)0x10000040)  /* When Rx alignment error counter reaches half the maximum value */
#define EMAC_MMC_IT_RFCE      ((rt_uint32_t)0x10000020)  /* When Rx crc error counter reaches half the maximum value */

#define EMAC_MMCCR            ((rt_uint32_t)0x00000100)  /* MMC CR register */
#define EMAC_MMCRIR           ((rt_uint32_t)0x00000104)  /* MMC RIR register */
#define EMAC_MMCTIR           ((rt_uint32_t)0x00000108)  /* MMC TIR register */
#define EMAC_MMCRIMR          ((rt_uint32_t)0x0000010C)  /* MMC RIMR register */
#define EMAC_MMCTIMR          ((rt_uint32_t)0x00000110)  /* MMC TIMR register */
#define EMAC_MMCTGFSCCR       ((rt_uint32_t)0x0000014C)  /* MMC TGFSCCR register */
#define EMAC_MMCTGFMSCCR      ((rt_uint32_t)0x00000150)  /* MMC TGFMSCCR register */
#define EMAC_MMCTGFCR         ((rt_uint32_t)0x00000168)  /* MMC TGFCR register */
#define EMAC_MMCRFCECR        ((rt_uint32_t)0x00000194)  /* MMC RFCECR register */
#define EMAC_MMCRFAECR        ((rt_uint32_t)0x00000198)  /* MMC RFAECR register */
#define EMAC_MMCRGUFCR        ((rt_uint32_t)0x000001C4)  /* MMC RGUFCR register */

#define EMAC_PTP_FineUpdate        ((rt_uint32_t)0x00000001)  /* Fine Update method */
#define EMAC_PTP_CoarseUpdate      ((rt_uint32_t)0x00000000)  /* Coarse Update method */

#define EMAC_PTP_FLAG_TSARU        ((rt_uint32_t)0x00000020)  /* Addend Register Update */
#define EMAC_PTP_FLAG_TSITE        ((rt_uint32_t)0x00000010)  /* Time Stamp Interrupt Trigger */
#define EMAC_PTP_FLAG_TSSTU        ((rt_uint32_t)0x00000008)  /* Time Stamp Update */
#define EMAC_PTP_FLAG_TSSTI        ((rt_uint32_t)0x00000004)  /* Time Stamp Initialize */

#define EMAC_PTP_PositiveTime      ((rt_uint32_t)0x00000000)  /* Positive time value */
#define EMAC_PTP_NegativeTime      ((rt_uint32_t)0x80000000)  /* Negative time value */

#define EMAC_PTPTSCR     ((rt_uint32_t)0x00000700)  /* PTP TSCR register */
#define EMAC_PTPSSIR     ((rt_uint32_t)0x00000704)  /* PTP SSIR register */
#define EMAC_PTPTSHR     ((rt_uint32_t)0x00000708)  /* PTP TSHR register */
#define EMAC_PTPTSLR     ((rt_uint32_t)0x0000070C)  /* PTP TSLR register */
#define EMAC_PTPTSHUR    ((rt_uint32_t)0x00000710)  /* PTP TSHUR register */
#define EMAC_PTPTSLUR    ((rt_uint32_t)0x00000714)  /* PTP TSLUR register */
#define EMAC_PTPTSAR     ((rt_uint32_t)0x00000718)  /* PTP TSAR register */
#define EMAC_PTPTTHR     ((rt_uint32_t)0x0000071C)  /* PTP TTHR register */
#define EMAC_PTPTTLR     ((rt_uint32_t)0x00000720)  /* PTP TTLR register */

/* ETHERNET MAC address offsets */
#define EMAC_MAC_ADDR_HBASE    (ETHERNET_MAC0_BASE + 0x40)  /* ETHERNET MAC address high offset */
#define EMAC_MAC_ADDR_LBASE    (ETHERNET_MAC0_BASE + 0x44)  /* ETHERNET MAC address low offset */

/* ETHERNET MACMIIAR register Mask */
#define MACMIIAR_CR_MASK    ((rt_uint32_t)0xFFFFFFE3)

/* ETHERNET MACCR register Mask */
#define MACCR_CLEAR_MASK    ((rt_uint32_t)0xFF20810F)

/* ETHERNET MACFCR register Mask */
#define MACFCR_CLEAR_MASK   ((rt_uint32_t)0x0000FF41)

/* ETHERNET DMAOMR register Mask */
#define DMAOMR_CLEAR_MASK   ((rt_uint32_t)0xF8DE3F23)

/* ETHERNET errors */
#define  EMAC_ERROR              ((rt_uint32_t)0)
#define  EMAC_SUCCESS            ((rt_uint32_t)1)

/* ETHERNET DMA Rx descriptors Frame Length Shift */
#define  EMAC_DMARXDESC_FRAME_LENGTHSHIFT           16




/* ETHERNET-MAC registers */
/* ETHERNET-MAC registers */
struct rt_synopsys_eth
{
    volatile rt_uint32_t MCR;
    volatile rt_uint32_t MFFR;
    volatile rt_uint32_t MHTRH;
    volatile rt_uint32_t MHTRL;
    volatile rt_uint32_t GAR;
    volatile rt_uint32_t GDR;
    volatile rt_uint32_t FCR;
    volatile rt_uint32_t VTR;
               rt_uint8_t RESERVED0[8];
    
    volatile rt_uint32_t RWFFR;
    volatile rt_uint32_t PMTR;
    volatile rt_uint32_t LPICSR;
    volatile rt_uint32_t LPITCR;
    volatile rt_uint32_t ISR;
    volatile rt_uint32_t IMR;

    struct MARS
    {
        volatile rt_uint32_t MARH;
        volatile rt_uint32_t MARL;
    } MARs[16];

               rt_uint8_t RESERVED1[24];
    volatile rt_uint32_t RGSR;
               rt_uint8_t RESERVED2[36];
    volatile rt_uint32_t mmc_cntl;
    volatile rt_uint32_t mmc_intr_rx;
    volatile rt_uint32_t mmc_intr_tx;
    volatile rt_uint32_t mmc_intr_mask_rx;
    volatile rt_uint32_t mmc_intr_mask_tx;
    volatile rt_uint32_t txoctetcount_gb;
    volatile rt_uint32_t txframecount_gb;
    volatile rt_uint32_t txbroadcastframes_g;
    volatile rt_uint32_t txmulticastframes_g;
    volatile rt_uint32_t tx64octets_gb;
    volatile rt_uint32_t tx65to127octets_gb;
    volatile rt_uint32_t tx128to255octets_gb;
    volatile rt_uint32_t tx256to511octets_gb;
    volatile rt_uint32_t tx512to1023octets_gb;
    volatile rt_uint32_t tx1024tomaxoctets_gb;
    volatile rt_uint32_t txunicastframes_gb;
    volatile rt_uint32_t txmulticastframes_gb;
    volatile rt_uint32_t txbroadcastframes_gb;
    volatile rt_uint32_t txunderflowerror;
    volatile rt_uint32_t txsinglecol_g;
    volatile rt_uint32_t txmulticol_g;
    volatile rt_uint32_t txdeferred;
    volatile rt_uint32_t txlatecol;
    volatile rt_uint32_t txexesscol;
    volatile rt_uint32_t txcarriererror;
    volatile rt_uint32_t txoctetcount_g;
    volatile rt_uint32_t txframecount_g;
    volatile rt_uint32_t txexecessdef_g;
    volatile rt_uint32_t txpauseframes;
    volatile rt_uint32_t txvlanframes_g;
               rt_uint8_t RESERVED3[8];
    volatile rt_uint32_t rxframecount_gb;
    volatile rt_uint32_t rxoctetcount_gb;
    volatile rt_uint32_t rxoctetcount_g;
    volatile rt_uint32_t rxbroadcastframes_g;
    volatile rt_uint32_t rxmulticastframes_g;
    volatile rt_uint32_t rxcrcerror;
    volatile rt_uint32_t rxallignmenterror;
    volatile rt_uint32_t rxrunterror;
    volatile rt_uint32_t rxjabbererror;
    volatile rt_uint32_t rxundersize_g;
    volatile rt_uint32_t rxoversize_g;
    volatile rt_uint32_t rx64octets_gb;
    volatile rt_uint32_t rx65to127octets_gb;
    volatile rt_uint32_t rx128to255octets_gb;
    volatile rt_uint32_t rx256to511octets_gb;
    volatile rt_uint32_t rx512to1023octets_gb;
    volatile rt_uint32_t rx1024tomaxoctets_gb;
    volatile rt_uint32_t rxunicastframes_g;
    volatile rt_uint32_t rxlengtherror;
    volatile rt_uint32_t rxoutofrangetype;
    volatile rt_uint32_t rxpauseframes;
    volatile rt_uint32_t rxfifooverflow;
    volatile rt_uint32_t rxvlanframes_gb;
    volatile rt_uint32_t rxwatchdogerror;
               rt_uint8_t RESERVED4[32];
    volatile rt_uint32_t mmc_ipc_intr_mask_rx;
               rt_uint8_t RESERVED5[4];
    volatile rt_uint32_t mmc_ipc_intr_rx;
               rt_uint8_t RESERVED6[4];
    volatile rt_uint32_t rxipv4_gd_frms;
    volatile rt_uint32_t rxipv4_hdrerr_frms;
    volatile rt_uint32_t rxipv4_nopay_frms;
    volatile rt_uint32_t rxipv4_frag_frms;
    volatile rt_uint32_t rxipv4_udsbl_frms;
    volatile rt_uint32_t rxipv6_gd_frms;
    volatile rt_uint32_t rxipv6_hdrerr_frms;
    volatile rt_uint32_t rxipv6_nopay_frms;
    volatile rt_uint32_t rxudp_gd_frms;
    volatile rt_uint32_t rxudp_err_frms;
    volatile rt_uint32_t rxtcp_gd_frms;
    volatile rt_uint32_t rxtcp_err_frms;
    volatile rt_uint32_t rxicmp_gd_frms;
    volatile rt_uint32_t rxicmp_err_frms;
               rt_uint8_t RESERVED7[8];
    volatile rt_uint32_t rxipv4_gd_octets;
    volatile rt_uint32_t rxipv4_hdrerr_octets;
    volatile rt_uint32_t rxipv4_nopay_octets;
    volatile rt_uint32_t rxipv4_frag_octets;
    volatile rt_uint32_t rxipv4_udsbl_octets;
    volatile rt_uint32_t rxipv6_gd_octets;
    volatile rt_uint32_t rxipv6_hdrerr_octets;
    volatile rt_uint32_t rxipv6_nopay_octets;
    volatile rt_uint32_t rxudp_gd_octets;
    volatile rt_uint32_t rxudp_err_octets;
    volatile rt_uint32_t rxtcp_gd_octets;
    volatile rt_uint32_t rxtcp_err_octets;
    volatile rt_uint32_t rxicmp_gd_octets;
    volatile rt_uint32_t rxicmp_err_octets;
               rt_uint8_t RESERVED8[1144];
    volatile rt_uint32_t TSCR;
    volatile rt_uint32_t SSIR;
    volatile rt_uint32_t STSR;
    volatile rt_uint32_t STNR;
    volatile rt_uint32_t STSUR;
    volatile rt_uint32_t STNUR;
    volatile rt_uint32_t TSAR;
    volatile rt_uint32_t TTSR;
    volatile rt_uint32_t TTNR;
    volatile rt_uint32_t STHWSR;
    volatile rt_uint32_t TSR;
    volatile rt_uint32_t PPSCR;
    volatile rt_uint32_t ATNR;
    volatile rt_uint32_t ATSR;
               rt_uint8_t RESERVED9[200];
    volatile rt_uint32_t MAR16H;
    volatile rt_uint32_t MAR16L;
    volatile rt_uint32_t MAR17H;
    volatile rt_uint32_t MAR17L;
    volatile rt_uint32_t MAR18H;
    volatile rt_uint32_t MAR18L;
    volatile rt_uint32_t MAR19H;
    volatile rt_uint32_t MAR19L;
    volatile rt_uint32_t MAR20H;
    volatile rt_uint32_t MAR20L;
    volatile rt_uint32_t MAR21H;
    volatile rt_uint32_t MAR21L;
    volatile rt_uint32_t MAR22H;
    volatile rt_uint32_t MAR22L;
    volatile rt_uint32_t MAR23H;
    volatile rt_uint32_t MAR23L;
    volatile rt_uint32_t MAR24H;
    volatile rt_uint32_t MAR24L;
    volatile rt_uint32_t MAR25H;
    volatile rt_uint32_t MAR25L;
    volatile rt_uint32_t MAR26H;
    volatile rt_uint32_t MAR26L;
    volatile rt_uint32_t MAR27H;
    volatile rt_uint32_t MAR27L;
    volatile rt_uint32_t MAR28H;
    volatile rt_uint32_t MAR28L;
    volatile rt_uint32_t MAR29H;
    volatile rt_uint32_t MAR29L;
    volatile rt_uint32_t MAR30H;
    volatile rt_uint32_t MAR30L;
    volatile rt_uint32_t MAR31H;
    volatile rt_uint32_t MAR31L;
               rt_uint8_t RESERVED10[1920];
    volatile rt_uint32_t BMR;
    volatile rt_uint32_t TPDR;
    volatile rt_uint32_t RPDR;
    volatile rt_uint32_t RDLAR;
    volatile rt_uint32_t TDLAR;
    volatile rt_uint32_t SR;
    volatile rt_uint32_t OMR;
    volatile rt_uint32_t IER;
    volatile rt_uint32_t MFBOCR;
    volatile rt_uint32_t RIWTR;
               rt_uint8_t RESERVED11[4];
    volatile rt_uint32_t AHBSR;
               rt_uint8_t RESERVED12[24];
    volatile rt_uint32_t CHTDR;
    volatile rt_uint32_t CHRDR;
    volatile rt_uint32_t CHTBAR;
    volatile rt_uint32_t CHRBAR;
};
typedef struct rt_synopsys_eth rt_synopsys_eth;


rt_uint32_t EMAC_init(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t SystemCoreClock);

void EMAC_start(struct rt_synopsys_eth * ETHERNET_MAC);

rt_uint16_t EMAC_PHY_read(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint16_t PHYAddress, rt_uint16_t PHYReg);
rt_uint32_t EMAC_PHY_write(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint16_t PHYAddress, rt_uint16_t PHYReg, rt_uint16_t PHYValue);

void EMAC_MAC_Addr_config(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t MacAddr, rt_uint8_t *Addr);
void EMAC_clear_pending(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t EMAC_DMA_IT);

void EMAC_INT_config(struct rt_synopsys_eth * ETHERNET_MAC, rt_uint32_t EMAC_DMA_IT, rt_bool_t NewState);
void EMAC_resume_transmission(struct rt_synopsys_eth * ETHERNET_MAC);
void EMAC_resume_reception(struct rt_synopsys_eth * ETHERNET_MAC);

#endif
