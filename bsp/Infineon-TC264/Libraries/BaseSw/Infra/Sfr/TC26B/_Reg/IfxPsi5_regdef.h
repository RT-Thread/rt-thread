/**
 * \file IfxPsi5_regdef.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Psi5 Psi5
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Psi5_Bitfields Bitfields
 * \ingroup IfxLld_Psi5
 * 
 * \defgroup IfxLld_Psi5_union Union
 * \ingroup IfxLld_Psi5
 * 
 * \defgroup IfxLld_Psi5_struct Struct
 * \ingroup IfxLld_Psi5
 * 
 */
#ifndef IFXPSI5_REGDEF_H
#define IFXPSI5_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Psi5_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_PSI5_ACCEN0_Bits
{
    unsigned int EN0:1;                     /**< \brief [0:0] Access Enable for Master TAG ID 0 (rw) */
    unsigned int EN1:1;                     /**< \brief [1:1] Access Enable for Master TAG ID 1 (rw) */
    unsigned int EN2:1;                     /**< \brief [2:2] Access Enable for Master TAG ID 2 (rw) */
    unsigned int EN3:1;                     /**< \brief [3:3] Access Enable for Master TAG ID 3 (rw) */
    unsigned int EN4:1;                     /**< \brief [4:4] Access Enable for Master TAG ID 4 (rw) */
    unsigned int EN5:1;                     /**< \brief [5:5] Access Enable for Master TAG ID 5 (rw) */
    unsigned int EN6:1;                     /**< \brief [6:6] Access Enable for Master TAG ID 6 (rw) */
    unsigned int EN7:1;                     /**< \brief [7:7] Access Enable for Master TAG ID 7 (rw) */
    unsigned int EN8:1;                     /**< \brief [8:8] Access Enable for Master TAG ID 8 (rw) */
    unsigned int EN9:1;                     /**< \brief [9:9] Access Enable for Master TAG ID 9 (rw) */
    unsigned int EN10:1;                    /**< \brief [10:10] Access Enable for Master TAG ID 10 (rw) */
    unsigned int EN11:1;                    /**< \brief [11:11] Access Enable for Master TAG ID 11 (rw) */
    unsigned int EN12:1;                    /**< \brief [12:12] Access Enable for Master TAG ID 12 (rw) */
    unsigned int EN13:1;                    /**< \brief [13:13] Access Enable for Master TAG ID 13 (rw) */
    unsigned int EN14:1;                    /**< \brief [14:14] Access Enable for Master TAG ID 14 (rw) */
    unsigned int EN15:1;                    /**< \brief [15:15] Access Enable for Master TAG ID 15 (rw) */
    unsigned int EN16:1;                    /**< \brief [16:16] Access Enable for Master TAG ID 16 (rw) */
    unsigned int EN17:1;                    /**< \brief [17:17] Access Enable for Master TAG ID 17 (rw) */
    unsigned int EN18:1;                    /**< \brief [18:18] Access Enable for Master TAG ID 18 (rw) */
    unsigned int EN19:1;                    /**< \brief [19:19] Access Enable for Master TAG ID 19 (rw) */
    unsigned int EN20:1;                    /**< \brief [20:20] Access Enable for Master TAG ID 20 (rw) */
    unsigned int EN21:1;                    /**< \brief [21:21] Access Enable for Master TAG ID 21 (rw) */
    unsigned int EN22:1;                    /**< \brief [22:22] Access Enable for Master TAG ID 22 (rw) */
    unsigned int EN23:1;                    /**< \brief [23:23] Access Enable for Master TAG ID 23 (rw) */
    unsigned int EN24:1;                    /**< \brief [24:24] Access Enable for Master TAG ID 24 (rw) */
    unsigned int EN25:1;                    /**< \brief [25:25] Access Enable for Master TAG ID 25 (rw) */
    unsigned int EN26:1;                    /**< \brief [26:26] Access Enable for Master TAG ID 26 (rw) */
    unsigned int EN27:1;                    /**< \brief [27:27] Access Enable for Master TAG ID 27 (rw) */
    unsigned int EN28:1;                    /**< \brief [28:28] Access Enable for Master TAG ID 28 (rw) */
    unsigned int EN29:1;                    /**< \brief [29:29] Access Enable for Master TAG ID 29 (rw) */
    unsigned int EN30:1;                    /**< \brief [30:30] Access Enable for Master TAG ID 30 (rw) */
    unsigned int EN31:1;                    /**< \brief [31:31] Access Enable for Master TAG ID 31 (rw) */
} Ifx_PSI5_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_PSI5_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_PSI5_ACCEN1_Bits;

/** \brief  Channel Trigger Value Register */
typedef struct _Ifx_PSI5_CH_CTV_Bits
{
    unsigned int CTV:16;                    /**< \brief [15:0] Channel Trigger Value CTV (rw) */
    unsigned int CTC:16;                    /**< \brief [31:16] Channel Trigger Counter (rw) */
} Ifx_PSI5_CH_CTV_Bits;

/** \brief  Input and Output Control Register */
typedef struct _Ifx_PSI5_CH_IOCR_Bits
{
    unsigned int ALTI:2;                    /**< \brief [1:0] Alternate Input Select (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int DEPTH:4;                   /**< \brief [7:4] Digital Glitch Filter Depth (rw) */
    unsigned int OIE:1;                     /**< \brief [8:8] Output Inverter Enable Channel x (rw) */
    unsigned int IIE:1;                     /**< \brief [9:9] Input Inverter Enable Channel x (rw) */
    unsigned int reserved_10:2;             /**< \brief \internal Reserved */
    unsigned int REG:1;                     /**< \brief [12:12] Rising Edge Glitch Flag for Channel x (rh) */
    unsigned int FEG:1;                     /**< \brief [13:13] Falling Edge Glitch Flag for Channel x (rh) */
    unsigned int CREG:1;                    /**< \brief [14:14] Clear Rising Edge Glitch Flag for Channel x (w) */
    unsigned int CFEG:1;                    /**< \brief [15:15] Clear Falling Edge Glitch Flag for Channel x (w) */
    unsigned int reserved_16:14;            /**< \brief \internal Reserved */
    unsigned int RXM:1;                     /**< \brief [30:30] Receive Monitor for Channel x (rh) */
    unsigned int TXM:1;                     /**< \brief [31:31] Transmit Monitor for Channel x (rh) */
} Ifx_PSI5_CH_IOCR_Bits;

/** \brief  Pulse Generation Control Register */
typedef struct _Ifx_PSI5_CH_PGC_Bits
{
    unsigned int PLEN:6;                    /**< \brief [5:0] Pulse Length (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int DEL:6;                     /**< \brief [13:8] Delay Length (rw) */
    unsigned int reserved_14:1;             /**< \brief \internal Reserved */
    unsigned int TBS:1;                     /**< \brief [15:15] Time Base Select (rw) */
    unsigned int ETB:3;                     /**< \brief [18:16] External Time Base Select (rw) */
    unsigned int PTE:1;                     /**< \brief [19:19] Periodic Trigger Enable (rw) */
    unsigned int ETS:3;                     /**< \brief [22:20] External Trigger Select (rw) */
    unsigned int ETE:1;                     /**< \brief [23:23] External Trigger Enable (rw) */
    unsigned int BYP:1;                     /**< \brief [24:24] Bypass Enable (rw) */
    unsigned int BOT:7;                     /**< \brief [31:25] Blank Out Time (rw) */
} Ifx_PSI5_CH_PGC_Bits;

/** \brief  Receiver Control Register A */
typedef struct _Ifx_PSI5_CH_RCRA_Bits
{
    unsigned int PDL0:5;                    /**< \brief [4:0] Payload Data Length (rw) */
    unsigned int PDL1:5;                    /**< \brief [9:5] Payload Data Length (rw) */
    unsigned int PDL2:5;                    /**< \brief [14:10] Payload Data Length (rw) */
    unsigned int PDL3:5;                    /**< \brief [19:15] Payload Data Length (rw) */
    unsigned int PDL4:5;                    /**< \brief [24:20] Payload Data Length (rw) */
    unsigned int PDL5:5;                    /**< \brief [29:25] Payload Data Length (rw) */
    unsigned int ASYN:1;                    /**< \brief [30:30] Asynchronous Mode (rw) */
    unsigned int AVBS:1;                    /**< \brief [31:31] Verbose Mode for Asynchronous Mode (rw) */
} Ifx_PSI5_CH_RCRA_Bits;

/** \brief  Receiver Control Register B */
typedef struct _Ifx_PSI5_CH_RCRB_Bits
{
    unsigned int MSG0:1;                    /**< \brief [0:0] Messaging Bits (rw) */
    unsigned int CRC0:1;                    /**< \brief [1:1] CRC or Parity Selection (rw) */
    unsigned int FEC0:1;                    /**< \brief [2:2] Frame Expectation Control (rw) */
    unsigned int VBS0:1;                    /**< \brief [3:3] Verbose Mode (rw) */
    unsigned int MSG1:1;                    /**< \brief [4:4] Messaging Bits (rw) */
    unsigned int CRC1:1;                    /**< \brief [5:5] CRC or Parity Selection (rw) */
    unsigned int FEC1:1;                    /**< \brief [6:6] Frame Expectation Control (rw) */
    unsigned int VBS1:1;                    /**< \brief [7:7] Verbose Mode (rw) */
    unsigned int MSG2:1;                    /**< \brief [8:8] Messaging Bits (rw) */
    unsigned int CRC2:1;                    /**< \brief [9:9] CRC or Parity Selection (rw) */
    unsigned int FEC2:1;                    /**< \brief [10:10] Frame Expectation Control (rw) */
    unsigned int VBS2:1;                    /**< \brief [11:11] Verbose Mode (rw) */
    unsigned int MSG3:1;                    /**< \brief [12:12] Messaging Bits (rw) */
    unsigned int CRC3:1;                    /**< \brief [13:13] CRC or Parity Selection (rw) */
    unsigned int FEC3:1;                    /**< \brief [14:14] Frame Expectation Control (rw) */
    unsigned int VBS3:1;                    /**< \brief [15:15] Verbose Mode (rw) */
    unsigned int MSG4:1;                    /**< \brief [16:16] Messaging Bits (rw) */
    unsigned int CRC4:1;                    /**< \brief [17:17] CRC or Parity Selection (rw) */
    unsigned int FEC4:1;                    /**< \brief [18:18] Frame Expectation Control (rw) */
    unsigned int VBS4:1;                    /**< \brief [19:19] Verbose Mode (rw) */
    unsigned int MSG5:1;                    /**< \brief [20:20] Messaging Bits (rw) */
    unsigned int CRC5:1;                    /**< \brief [21:21] CRC or Parity Selection (rw) */
    unsigned int FEC5:1;                    /**< \brief [22:22] Frame Expectation Control (rw) */
    unsigned int VBS5:1;                    /**< \brief [23:23] Verbose Mode (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5_CH_RCRB_Bits;

/** \brief  Receiver Control Register C */
typedef struct _Ifx_PSI5_CH_RCRC_Bits
{
    unsigned int BRS:1;                     /**< \brief [0:0] Baud Rate Select (rw) */
    unsigned int TSP:2;                     /**< \brief [2:1] Time Stamp Select for Pulses (rw) */
    unsigned int TSF:2;                     /**< \brief [4:3] Time Stamp Select for Start of Frame (SOF) (rw) */
    unsigned int TSR:1;                     /**< \brief [5:5] Time Stamp Select for Receive Data Registers (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_PSI5_CH_RCRC_Bits;

/** \brief  Receive Data Register High */
typedef struct _Ifx_PSI5_CH_RDRH_Bits
{
    unsigned int TS:24;                     /**< \brief [23:0] Time Stamp (rh) */
    unsigned int SC:3;                      /**< \brief [26:24] Slot Counter (rh) */
    unsigned int TEI:1;                     /**< \brief [27:27] Time Slot Error Flag (rh) */
    unsigned int NBI:1;                     /**< \brief [28:28] Number of bits Error Flag (rh) */
    unsigned int MEI:1;                     /**< \brief [29:29] Error in Message Bits Flag (rh) */
    unsigned int NFI:1;                     /**< \brief [30:30] No Frame Received Flag (rh) */
    unsigned int RBI:1;                     /**< \brief [31:31] Receive Buffer Overflow Flag (rh) */
} Ifx_PSI5_CH_RDRH_Bits;

/** \brief  Receive Data Register Low */
typedef struct _Ifx_PSI5_CH_RDRL_Bits
{
    unsigned int CRCI:1;                    /**< \brief [0:0] CRC Error Flag (rh) */
    unsigned int CRC:3;                     /**< \brief [3:1] CRC (rh) */
    unsigned int RD:28;                     /**< \brief [31:4] RD (rh) */
} Ifx_PSI5_CH_RDRL_Bits;

/** \brief  Receive Status Register */
typedef struct _Ifx_PSI5_CH_RSR_Bits
{
    unsigned int CRC:3;                     /**< \brief [2:0] CRC (r) */
    unsigned int reserved_3:5;              /**< \brief \internal Reserved */
    unsigned int MSG:2;                     /**< \brief [9:8] Messaging Bits (r) */
    unsigned int reserved_10:22;            /**< \brief \internal Reserved */
} Ifx_PSI5_CH_RSR_Bits;

/** \brief  Send Control Register */
typedef struct _Ifx_PSI5_CH_SCR_Bits
{
    unsigned int PLL:6;                     /**< \brief [5:0] Pay Load Length of Registers SDRL/H (rw) */
    unsigned int EPS:1;                     /**< \brief [6:6] Enhanced Protocol Selection (rw) */
    unsigned int BSC:1;                     /**< \brief [7:7] Bit Stuffing Control (rw) */
    unsigned int SSL:6;                     /**< \brief [13:8] Pay Load Length of Registers SSRL/H (rw) */
    unsigned int FLUS:1;                    /**< \brief [14:14] Flush SSRH/Lx (w) */
    unsigned int FLUO:1;                    /**< \brief [15:15] Flush SORH/Lx (w) */
    unsigned int SOL:6;                     /**< \brief [21:16] Pay Load Length of Registers SORL/H (rw) */
    unsigned int CRC:1;                     /**< \brief [22:22] CRC Generation Control (rw) */
    unsigned int STA:1;                     /**< \brief [23:23] Start Sequence Generation Control (rw) */
    unsigned int INH:1;                     /**< \brief [24:24] Inhibit Transfer (rw) */
    unsigned int GO:1;                      /**< \brief [25:25] Release prepared Send data (w) */
    unsigned int TPF:1;                     /**< \brief [26:26] Transmit Preparation Flag (r) */
    unsigned int TSF:1;                     /**< \brief [27:27] Transmit Shift Flag (r) */
    unsigned int TOF:1;                     /**< \brief [28:28] Transmit Output Flag (r) */
    unsigned int reserved_29:2;             /**< \brief \internal Reserved */
    unsigned int TRQ:1;                     /**< \brief [31:31] Transfer Request in Progress (r) */
} Ifx_PSI5_CH_SCR_Bits;

/** \brief  Send Data Register High */
typedef struct _Ifx_PSI5_CH_SDRH_Bits
{
    unsigned int SD32:1;                    /**< \brief [0:0] SD32 (rw) */
    unsigned int SD33:1;                    /**< \brief [1:1] SD33 (rw) */
    unsigned int SD34:1;                    /**< \brief [2:2] SD34 (rw) */
    unsigned int SD35:1;                    /**< \brief [3:3] SD35 (rw) */
    unsigned int SD36:1;                    /**< \brief [4:4] SD36 (rw) */
    unsigned int SD37:1;                    /**< \brief [5:5] SD37 (rw) */
    unsigned int SD38:1;                    /**< \brief [6:6] SD38 (rw) */
    unsigned int SD39:1;                    /**< \brief [7:7] SD39 (rw) */
    unsigned int SD40:1;                    /**< \brief [8:8] SD40 (rw) */
    unsigned int SD41:1;                    /**< \brief [9:9] SD41 (rw) */
    unsigned int SD42:1;                    /**< \brief [10:10] SD42 (rw) */
    unsigned int SD43:1;                    /**< \brief [11:11] SD43 (rw) */
    unsigned int SD44:1;                    /**< \brief [12:12] SD44 (rw) */
    unsigned int SD45:1;                    /**< \brief [13:13] SD45 (rw) */
    unsigned int SD46:1;                    /**< \brief [14:14] SD46 (rw) */
    unsigned int SD47:1;                    /**< \brief [15:15] SD47 (rw) */
    unsigned int SD48:1;                    /**< \brief [16:16] SD48 (rw) */
    unsigned int SD49:1;                    /**< \brief [17:17] SD49 (rw) */
    unsigned int SD50:1;                    /**< \brief [18:18] SD50 (rw) */
    unsigned int SD51:1;                    /**< \brief [19:19] SD51 (rw) */
    unsigned int SD52:1;                    /**< \brief [20:20] SD52 (rw) */
    unsigned int SD53:1;                    /**< \brief [21:21] SD53 (rw) */
    unsigned int SD54:1;                    /**< \brief [22:22] SD54 (rw) */
    unsigned int SD55:1;                    /**< \brief [23:23] SD55 (rw) */
    unsigned int SD56:1;                    /**< \brief [24:24] SD56 (rw) */
    unsigned int SD57:1;                    /**< \brief [25:25] SD57 (rw) */
    unsigned int SD58:1;                    /**< \brief [26:26] SD58 (rw) */
    unsigned int SD59:1;                    /**< \brief [27:27] SD59 (rw) */
    unsigned int SD60:1;                    /**< \brief [28:28] SD60 (rw) */
    unsigned int SD61:1;                    /**< \brief [29:29] SD61 (rw) */
    unsigned int SD62:1;                    /**< \brief [30:30] SD62 (rw) */
    unsigned int SD63:1;                    /**< \brief [31:31] SD63 (rw) */
} Ifx_PSI5_CH_SDRH_Bits;

/** \brief  Send Data Register Low */
typedef struct _Ifx_PSI5_CH_SDRL_Bits
{
    unsigned int SD0:1;                     /**< \brief [0:0] SD0 (rw) */
    unsigned int SD1:1;                     /**< \brief [1:1] SD1 (rw) */
    unsigned int SD2:1;                     /**< \brief [2:2] SD2 (rw) */
    unsigned int SD3:1;                     /**< \brief [3:3] SD3 (rw) */
    unsigned int SD4:1;                     /**< \brief [4:4] SD4 (rw) */
    unsigned int SD5:1;                     /**< \brief [5:5] SD5 (rw) */
    unsigned int SD6:1;                     /**< \brief [6:6] SD6 (rw) */
    unsigned int SD7:1;                     /**< \brief [7:7] SD7 (rw) */
    unsigned int SD8:1;                     /**< \brief [8:8] SD8 (rw) */
    unsigned int SD9:1;                     /**< \brief [9:9] SD9 (rw) */
    unsigned int SD10:1;                    /**< \brief [10:10] SD10 (rw) */
    unsigned int SD11:1;                    /**< \brief [11:11] SD11 (rw) */
    unsigned int SD12:1;                    /**< \brief [12:12] SD12 (rw) */
    unsigned int SD13:1;                    /**< \brief [13:13] SD13 (rw) */
    unsigned int SD14:1;                    /**< \brief [14:14] SD14 (rw) */
    unsigned int SD15:1;                    /**< \brief [15:15] SD15 (rw) */
    unsigned int SD16:1;                    /**< \brief [16:16] SD16 (rw) */
    unsigned int SD17:1;                    /**< \brief [17:17] SD17 (rw) */
    unsigned int SD18:1;                    /**< \brief [18:18] SD18 (rw) */
    unsigned int SD19:1;                    /**< \brief [19:19] SD19 (rw) */
    unsigned int SD20:1;                    /**< \brief [20:20] SD20 (rw) */
    unsigned int SD21:1;                    /**< \brief [21:21] SD21 (rw) */
    unsigned int SD22:1;                    /**< \brief [22:22] SD22 (rw) */
    unsigned int SD23:1;                    /**< \brief [23:23] SD23 (rw) */
    unsigned int SD24:1;                    /**< \brief [24:24] SD24 (rw) */
    unsigned int SD25:1;                    /**< \brief [25:25] SD25 (rw) */
    unsigned int SD26:1;                    /**< \brief [26:26] SD26 (rw) */
    unsigned int SD27:1;                    /**< \brief [27:27] SD27 (rw) */
    unsigned int SD28:1;                    /**< \brief [28:28] SD28 (rw) */
    unsigned int SD29:1;                    /**< \brief [29:29] SD29 (rw) */
    unsigned int SD30:1;                    /**< \brief [30:30] SD30 (rw) */
    unsigned int SD31:1;                    /**< \brief [31:31] SD31 (rw) */
} Ifx_PSI5_CH_SDRL_Bits;

/** \brief  Serial Data and Status Register */
typedef struct _Ifx_PSI5_CH_SDS_Bits
{
    unsigned int SD:16;                     /**< \brief [15:0] Serial Data (r) */
    unsigned int MID:8;                     /**< \brief [23:16] Message ID (r) */
    unsigned int SCRC:6;                    /**< \brief [29:24] SCRC (r) */
    unsigned int SCRI:1;                    /**< \brief [30:30] CRC of Serial Message failed Interrupt Flag. (r) */
    unsigned int CON:1;                     /**< \brief [31:31] Configuration bit (r) */
} Ifx_PSI5_CH_SDS_Bits;

/** \brief  SOF TS Capture Register SFTSC */
typedef struct _Ifx_PSI5_CH_SFTSC_Bits
{
    unsigned int TS:24;                     /**< \brief [23:0] Time Stamp (rh) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5_CH_SFTSC_Bits;

/** \brief  Send Output Register High */
typedef struct _Ifx_PSI5_CH_SORH_Bits
{
    unsigned int SD32:1;                    /**< \brief [0:0] SD32 (rw) */
    unsigned int SD33:1;                    /**< \brief [1:1] SD33 (rw) */
    unsigned int SD34:1;                    /**< \brief [2:2] SD34 (rw) */
    unsigned int SD35:1;                    /**< \brief [3:3] SD35 (rw) */
    unsigned int SD36:1;                    /**< \brief [4:4] SD36 (rw) */
    unsigned int SD37:1;                    /**< \brief [5:5] SD37 (rw) */
    unsigned int SD38:1;                    /**< \brief [6:6] SD38 (rw) */
    unsigned int SD39:1;                    /**< \brief [7:7] SD39 (rw) */
    unsigned int SD40:1;                    /**< \brief [8:8] SD40 (rw) */
    unsigned int SD41:1;                    /**< \brief [9:9] SD41 (rw) */
    unsigned int SD42:1;                    /**< \brief [10:10] SD42 (rw) */
    unsigned int SD43:1;                    /**< \brief [11:11] SD43 (rw) */
    unsigned int SD44:1;                    /**< \brief [12:12] SD44 (rw) */
    unsigned int SD45:1;                    /**< \brief [13:13] SD45 (rw) */
    unsigned int SD46:1;                    /**< \brief [14:14] SD46 (rw) */
    unsigned int SD47:1;                    /**< \brief [15:15] SD47 (rw) */
    unsigned int SD48:1;                    /**< \brief [16:16] SD48 (rw) */
    unsigned int SD49:1;                    /**< \brief [17:17] SD49 (rw) */
    unsigned int SD50:1;                    /**< \brief [18:18] SD50 (rw) */
    unsigned int SD51:1;                    /**< \brief [19:19] SD51 (rw) */
    unsigned int SD52:1;                    /**< \brief [20:20] SD52 (rw) */
    unsigned int SD53:1;                    /**< \brief [21:21] SD53 (rw) */
    unsigned int SD54:1;                    /**< \brief [22:22] SD54 (rw) */
    unsigned int SD55:1;                    /**< \brief [23:23] SD55 (rw) */
    unsigned int SD56:1;                    /**< \brief [24:24] SD56 (rw) */
    unsigned int SD57:1;                    /**< \brief [25:25] SD57 (rw) */
    unsigned int SD58:1;                    /**< \brief [26:26] SD58 (rw) */
    unsigned int SD59:1;                    /**< \brief [27:27] SD59 (rw) */
    unsigned int SD60:1;                    /**< \brief [28:28] SD60 (rw) */
    unsigned int SD61:1;                    /**< \brief [29:29] SD61 (rw) */
    unsigned int SD62:1;                    /**< \brief [30:30] SD62 (rw) */
    unsigned int SD63:1;                    /**< \brief [31:31] SD63 (rw) */
} Ifx_PSI5_CH_SORH_Bits;

/** \brief  Send Output Register Low */
typedef struct _Ifx_PSI5_CH_SORL_Bits
{
    unsigned int SD0:1;                     /**< \brief [0:0] SD0 (rw) */
    unsigned int SD1:1;                     /**< \brief [1:1] SD1 (rw) */
    unsigned int SD2:1;                     /**< \brief [2:2] SD2 (rw) */
    unsigned int SD3:1;                     /**< \brief [3:3] SD3 (rw) */
    unsigned int SD4:1;                     /**< \brief [4:4] SD4 (rw) */
    unsigned int SD5:1;                     /**< \brief [5:5] SD5 (rw) */
    unsigned int SD6:1;                     /**< \brief [6:6] SD6 (rw) */
    unsigned int SD7:1;                     /**< \brief [7:7] SD7 (rw) */
    unsigned int SD8:1;                     /**< \brief [8:8] SD8 (rw) */
    unsigned int SD9:1;                     /**< \brief [9:9] SD9 (rw) */
    unsigned int SD10:1;                    /**< \brief [10:10] SD10 (rw) */
    unsigned int SD11:1;                    /**< \brief [11:11] SD11 (rw) */
    unsigned int SD12:1;                    /**< \brief [12:12] SD12 (rw) */
    unsigned int SD13:1;                    /**< \brief [13:13] SD13 (rw) */
    unsigned int SD14:1;                    /**< \brief [14:14] SD14 (rw) */
    unsigned int SD15:1;                    /**< \brief [15:15] SD15 (rw) */
    unsigned int SD16:1;                    /**< \brief [16:16] SD16 (rw) */
    unsigned int SD17:1;                    /**< \brief [17:17] SD17 (rw) */
    unsigned int SD18:1;                    /**< \brief [18:18] SD18 (rw) */
    unsigned int SD19:1;                    /**< \brief [19:19] SD19 (rw) */
    unsigned int SD20:1;                    /**< \brief [20:20] SD20 (rw) */
    unsigned int SD21:1;                    /**< \brief [21:21] SD21 (rw) */
    unsigned int SD22:1;                    /**< \brief [22:22] SD22 (rw) */
    unsigned int SD23:1;                    /**< \brief [23:23] SD23 (rw) */
    unsigned int SD24:1;                    /**< \brief [24:24] SD24 (rw) */
    unsigned int SD25:1;                    /**< \brief [25:25] SD25 (rw) */
    unsigned int SD26:1;                    /**< \brief [26:26] SD26 (rw) */
    unsigned int SD27:1;                    /**< \brief [27:27] SD27 (rw) */
    unsigned int SD28:1;                    /**< \brief [28:28] SD28 (rw) */
    unsigned int SD29:1;                    /**< \brief [29:29] SD29 (rw) */
    unsigned int SD30:1;                    /**< \brief [30:30] SD30 (rw) */
    unsigned int SD31:1;                    /**< \brief [31:31] SD31 (rw) */
} Ifx_PSI5_CH_SORL_Bits;

/** \brief  SOP TS Capture Register SPTSC */
typedef struct _Ifx_PSI5_CH_SPTSC_Bits
{
    unsigned int TS:24;                     /**< \brief [23:0] Time Stamp (rh) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5_CH_SPTSC_Bits;

/** \brief  Send Shift Register High */
typedef struct _Ifx_PSI5_CH_SSRH_Bits
{
    unsigned int SD32:1;                    /**< \brief [0:0] SD32 (rw) */
    unsigned int SD33:1;                    /**< \brief [1:1] SD33 (rw) */
    unsigned int SD34:1;                    /**< \brief [2:2] SD34 (rw) */
    unsigned int SD35:1;                    /**< \brief [3:3] SD35 (rw) */
    unsigned int SD36:1;                    /**< \brief [4:4] SD36 (rw) */
    unsigned int SD37:1;                    /**< \brief [5:5] SD37 (rw) */
    unsigned int SD38:1;                    /**< \brief [6:6] SD38 (rw) */
    unsigned int SD39:1;                    /**< \brief [7:7] SD39 (rw) */
    unsigned int SD40:1;                    /**< \brief [8:8] SD40 (rw) */
    unsigned int SD41:1;                    /**< \brief [9:9] SD41 (rw) */
    unsigned int SD42:1;                    /**< \brief [10:10] SD42 (rw) */
    unsigned int SD43:1;                    /**< \brief [11:11] SD43 (rw) */
    unsigned int SD44:1;                    /**< \brief [12:12] SD44 (rw) */
    unsigned int SD45:1;                    /**< \brief [13:13] SD45 (rw) */
    unsigned int SD46:1;                    /**< \brief [14:14] SD46 (rw) */
    unsigned int SD47:1;                    /**< \brief [15:15] SD47 (rw) */
    unsigned int SD48:1;                    /**< \brief [16:16] SD48 (rw) */
    unsigned int SD49:1;                    /**< \brief [17:17] SD49 (rw) */
    unsigned int SD50:1;                    /**< \brief [18:18] SD50 (rw) */
    unsigned int SD51:1;                    /**< \brief [19:19] SD51 (rw) */
    unsigned int SD52:1;                    /**< \brief [20:20] SD52 (rw) */
    unsigned int SD53:1;                    /**< \brief [21:21] SD53 (rw) */
    unsigned int SD54:1;                    /**< \brief [22:22] SD54 (rw) */
    unsigned int SD55:1;                    /**< \brief [23:23] SD55 (rw) */
    unsigned int SD56:1;                    /**< \brief [24:24] SD56 (rw) */
    unsigned int SD57:1;                    /**< \brief [25:25] SD57 (rw) */
    unsigned int SD58:1;                    /**< \brief [26:26] SD58 (rw) */
    unsigned int SD59:1;                    /**< \brief [27:27] SD59 (rw) */
    unsigned int SD60:1;                    /**< \brief [28:28] SD60 (rw) */
    unsigned int SD61:1;                    /**< \brief [29:29] SD61 (rw) */
    unsigned int SD62:1;                    /**< \brief [30:30] SD62 (rw) */
    unsigned int SD63:1;                    /**< \brief [31:31] SD63 (rw) */
} Ifx_PSI5_CH_SSRH_Bits;

/** \brief  Send Shift Register Low */
typedef struct _Ifx_PSI5_CH_SSRL_Bits
{
    unsigned int SD0:1;                     /**< \brief [0:0] SD0 (rw) */
    unsigned int SD1:1;                     /**< \brief [1:1] SD1 (rw) */
    unsigned int SD2:1;                     /**< \brief [2:2] SD2 (rw) */
    unsigned int SD3:1;                     /**< \brief [3:3] SD3 (rw) */
    unsigned int SD4:1;                     /**< \brief [4:4] SD4 (rw) */
    unsigned int SD5:1;                     /**< \brief [5:5] SD5 (rw) */
    unsigned int SD6:1;                     /**< \brief [6:6] SD6 (rw) */
    unsigned int SD7:1;                     /**< \brief [7:7] SD7 (rw) */
    unsigned int SD8:1;                     /**< \brief [8:8] SD8 (rw) */
    unsigned int SD9:1;                     /**< \brief [9:9] SD9 (rw) */
    unsigned int SD10:1;                    /**< \brief [10:10] SD10 (rw) */
    unsigned int SD11:1;                    /**< \brief [11:11] SD11 (rw) */
    unsigned int SD12:1;                    /**< \brief [12:12] SD12 (rw) */
    unsigned int SD13:1;                    /**< \brief [13:13] SD13 (rw) */
    unsigned int SD14:1;                    /**< \brief [14:14] SD14 (rw) */
    unsigned int SD15:1;                    /**< \brief [15:15] SD15 (rw) */
    unsigned int SD16:1;                    /**< \brief [16:16] SD16 (rw) */
    unsigned int SD17:1;                    /**< \brief [17:17] SD17 (rw) */
    unsigned int SD18:1;                    /**< \brief [18:18] SD18 (rw) */
    unsigned int SD19:1;                    /**< \brief [19:19] SD19 (rw) */
    unsigned int SD20:1;                    /**< \brief [20:20] SD20 (rw) */
    unsigned int SD21:1;                    /**< \brief [21:21] SD21 (rw) */
    unsigned int SD22:1;                    /**< \brief [22:22] SD22 (rw) */
    unsigned int SD23:1;                    /**< \brief [23:23] SD23 (rw) */
    unsigned int SD24:1;                    /**< \brief [24:24] SD24 (rw) */
    unsigned int SD25:1;                    /**< \brief [25:25] SD25 (rw) */
    unsigned int SD26:1;                    /**< \brief [26:26] SD26 (rw) */
    unsigned int SD27:1;                    /**< \brief [27:27] SD27 (rw) */
    unsigned int SD28:1;                    /**< \brief [28:28] SD28 (rw) */
    unsigned int SD29:1;                    /**< \brief [29:29] SD29 (rw) */
    unsigned int SD30:1;                    /**< \brief [30:30] SD30 (rw) */
    unsigned int SD31:1;                    /**< \brief [31:31] SD31 (rw) */
} Ifx_PSI5_CH_SSRL_Bits;

/** \brief  Watch Dog Timer Register */
typedef struct _Ifx_PSI5_CH_WDT_Bits
{
    unsigned int WDLxw:16;                  /**< \brief [15:0] Watch Dog Timer Limit (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_PSI5_CH_WDT_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_PSI5_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_PSI5_CLC_Bits;

/** \brief  CRCIOV Clear Register */
typedef struct _Ifx_PSI5_CRCICLR_Bits
{
    unsigned int CRCI0:1;                   /**< \brief [0:0] Clear CRCI Flag of Buffer 0 (w) */
    unsigned int CRCI1:1;                   /**< \brief [1:1] Clear CRCI Flag of Buffer 1 (w) */
    unsigned int CRCI2:1;                   /**< \brief [2:2] Clear CRCI Flag of Buffer 2 (w) */
    unsigned int CRCI3:1;                   /**< \brief [3:3] Clear CRCI Flag of Buffer 3 (w) */
    unsigned int CRCI4:1;                   /**< \brief [4:4] Clear CRCI Flag of Buffer 4 (w) */
    unsigned int CRCI5:1;                   /**< \brief [5:5] Clear CRCI Flag of Buffer 5 (w) */
    unsigned int CRCI6:1;                   /**< \brief [6:6] Clear CRCI Flag of Buffer 6 (w) */
    unsigned int CRCI7:1;                   /**< \brief [7:7] Clear CRCI Flag of Buffer 7 (w) */
    unsigned int CRCI8:1;                   /**< \brief [8:8] Clear CRCI Flag of Buffer 8 (w) */
    unsigned int CRCI9:1;                   /**< \brief [9:9] Clear CRCI Flag of Buffer 9 (w) */
    unsigned int CRCI10:1;                  /**< \brief [10:10] Clear CRCI Flag of Buffer 10 (w) */
    unsigned int CRCI11:1;                  /**< \brief [11:11] Clear CRCI Flag of Buffer 11 (w) */
    unsigned int CRCI12:1;                  /**< \brief [12:12] Clear CRCI Flag of Buffer 12 (w) */
    unsigned int CRCI13:1;                  /**< \brief [13:13] Clear CRCI Flag of Buffer 13 (w) */
    unsigned int CRCI14:1;                  /**< \brief [14:14] Clear CRCI Flag of Buffer 14 (w) */
    unsigned int CRCI15:1;                  /**< \brief [15:15] Clear CRCI Flag of Buffer 15 (w) */
    unsigned int CRCI16:1;                  /**< \brief [16:16] Clear CRCI Flag of Buffer 16 (w) */
    unsigned int CRCI17:1;                  /**< \brief [17:17] Clear CRCI Flag of Buffer 17 (w) */
    unsigned int CRCI18:1;                  /**< \brief [18:18] Clear CRCI Flag of Buffer 18 (w) */
    unsigned int CRCI19:1;                  /**< \brief [19:19] Clear CRCI Flag of Buffer 19 (w) */
    unsigned int CRCI20:1;                  /**< \brief [20:20] Clear CRCI Flag of Buffer 20 (w) */
    unsigned int CRCI21:1;                  /**< \brief [21:21] Clear CRCI Flag of Buffer 21 (w) */
    unsigned int CRCI22:1;                  /**< \brief [22:22] Clear CRCI Flag of Buffer 22 (w) */
    unsigned int CRCI23:1;                  /**< \brief [23:23] Clear CRCI Flag of Buffer 23 (w) */
    unsigned int CRCI24:1;                  /**< \brief [24:24] Clear CRCI Flag of Buffer 24 (w) */
    unsigned int CRCI25:1;                  /**< \brief [25:25] Clear CRCI Flag of Buffer 25 (w) */
    unsigned int CRCI26:1;                  /**< \brief [26:26] Clear CRCI Flag of Buffer 26 (w) */
    unsigned int CRCI27:1;                  /**< \brief [27:27] Clear CRCI Flag of Buffer 27 (w) */
    unsigned int CRCI28:1;                  /**< \brief [28:28] Clear CRCI Flag of Buffer 28 (w) */
    unsigned int CRCI29:1;                  /**< \brief [29:29] Clear CRCI Flag of Buffer 29 (w) */
    unsigned int CRCI30:1;                  /**< \brief [30:30] Clear CRCI Flag of Buffer 30 (w) */
    unsigned int CRCI31:1;                  /**< \brief [31:31] Clear CRCI Flag of Buffer 31 (w) */
} Ifx_PSI5_CRCICLR_Bits;

/** \brief  CRCI Overview Register */
typedef struct _Ifx_PSI5_CRCIOV_Bits
{
    unsigned int CRCI0:1;                   /**< \brief [0:0] CRCI Flag of Buffer 0 (rh) */
    unsigned int CRCI1:1;                   /**< \brief [1:1] CRCI Flag of Buffer 1 (rh) */
    unsigned int CRCI2:1;                   /**< \brief [2:2] CRCI Flag of Buffer 2 (rh) */
    unsigned int CRCI3:1;                   /**< \brief [3:3] CRCI Flag of Buffer 3 (rh) */
    unsigned int CRCI4:1;                   /**< \brief [4:4] CRCI Flag of Buffer 4 (rh) */
    unsigned int CRCI5:1;                   /**< \brief [5:5] CRCI Flag of Buffer 5 (rh) */
    unsigned int CRCI6:1;                   /**< \brief [6:6] CRCI Flag of Buffer 6 (rh) */
    unsigned int CRCI7:1;                   /**< \brief [7:7] CRCI Flag of Buffer 7 (rh) */
    unsigned int CRCI8:1;                   /**< \brief [8:8] CRCI Flag of Buffer 8 (rh) */
    unsigned int CRCI9:1;                   /**< \brief [9:9] CRCI Flag of Buffer 9 (rh) */
    unsigned int CRCI10:1;                  /**< \brief [10:10] CRCI Flag of Buffer 10 (rh) */
    unsigned int CRCI11:1;                  /**< \brief [11:11] CRCI Flag of Buffer 11 (rh) */
    unsigned int CRCI12:1;                  /**< \brief [12:12] CRCI Flag of Buffer 12 (rh) */
    unsigned int CRCI13:1;                  /**< \brief [13:13] CRCI Flag of Buffer 13 (rh) */
    unsigned int CRCI14:1;                  /**< \brief [14:14] CRCI Flag of Buffer 14 (rh) */
    unsigned int CRCI15:1;                  /**< \brief [15:15] CRCI Flag of Buffer 15 (rh) */
    unsigned int CRCI16:1;                  /**< \brief [16:16] CRCI Flag of Buffer 16 (rh) */
    unsigned int CRCI17:1;                  /**< \brief [17:17] CRCI Flag of Buffer 17 (rh) */
    unsigned int CRCI18:1;                  /**< \brief [18:18] CRCI Flag of Buffer 18 (rh) */
    unsigned int CRCI19:1;                  /**< \brief [19:19] CRCI Flag of Buffer 19 (rh) */
    unsigned int CRCI20:1;                  /**< \brief [20:20] CRCI Flag of Buffer 20 (rh) */
    unsigned int CRCI21:1;                  /**< \brief [21:21] CRCI Flag of Buffer 21 (rh) */
    unsigned int CRCI22:1;                  /**< \brief [22:22] CRCI Flag of Buffer 22 (rh) */
    unsigned int CRCI23:1;                  /**< \brief [23:23] CRCI Flag of Buffer 23 (rh) */
    unsigned int CRCI24:1;                  /**< \brief [24:24] CRCI Flag of Buffer 24 (rh) */
    unsigned int CRCI25:1;                  /**< \brief [25:25] CRCI Flag of Buffer 25 (rh) */
    unsigned int CRCI26:1;                  /**< \brief [26:26] CRCI Flag of Buffer 26 (rh) */
    unsigned int CRCI27:1;                  /**< \brief [27:27] CRCI Flag of Buffer 27 (rh) */
    unsigned int CRCI28:1;                  /**< \brief [28:28] CRCI Flag of Buffer 28 (rh) */
    unsigned int CRCI29:1;                  /**< \brief [29:29] CRCI Flag of Buffer 29 (rh) */
    unsigned int CRCI30:1;                  /**< \brief [30:30] CRCI Flag of Buffer 30 (rh) */
    unsigned int CRCI31:1;                  /**< \brief [31:31] CRCI Flag of Buffer 31 (rh) */
} Ifx_PSI5_CRCIOV_Bits;

/** \brief  CRCIOV Set Register */
typedef struct _Ifx_PSI5_CRCISET_Bits
{
    unsigned int CRCI0:1;                   /**< \brief [0:0] Set CRCI Flag of Buffer 0 (w) */
    unsigned int CRCI1:1;                   /**< \brief [1:1] Set CRCI Flag of Buffer 1 (w) */
    unsigned int CRCI2:1;                   /**< \brief [2:2] Set CRCI Flag of Buffer 2 (w) */
    unsigned int CRCI3:1;                   /**< \brief [3:3] Set CRCI Flag of Buffer 3 (w) */
    unsigned int CRCI4:1;                   /**< \brief [4:4] Set CRCI Flag of Buffer 4 (w) */
    unsigned int CRCI5:1;                   /**< \brief [5:5] Set CRCI Flag of Buffer 5 (w) */
    unsigned int CRCI6:1;                   /**< \brief [6:6] Set CRCI Flag of Buffer 6 (w) */
    unsigned int CRCI7:1;                   /**< \brief [7:7] Set CRCI Flag of Buffer 7 (w) */
    unsigned int CRCI8:1;                   /**< \brief [8:8] Set CRCI Flag of Buffer 8 (w) */
    unsigned int CRCI9:1;                   /**< \brief [9:9] Set CRCI Flag of Buffer 9 (w) */
    unsigned int CRCI10:1;                  /**< \brief [10:10] Set CRCI Flag of Buffer 10 (w) */
    unsigned int CRCI11:1;                  /**< \brief [11:11] Set CRCI Flag of Buffer 11 (w) */
    unsigned int CRCI12:1;                  /**< \brief [12:12] Set CRCI Flag of Buffer 12 (w) */
    unsigned int CRCI13:1;                  /**< \brief [13:13] Set CRCI Flag of Buffer 13 (w) */
    unsigned int CRCI14:1;                  /**< \brief [14:14] Set CRCI Flag of Buffer 14 (w) */
    unsigned int CRCI15:1;                  /**< \brief [15:15] Set CRCI Flag of Buffer 15 (w) */
    unsigned int CRCI16:1;                  /**< \brief [16:16] Set CRCI Flag of Buffer 16 (w) */
    unsigned int CRCI17:1;                  /**< \brief [17:17] Set CRCI Flag of Buffer 17 (w) */
    unsigned int CRCI18:1;                  /**< \brief [18:18] Set CRCI Flag of Buffer 18 (w) */
    unsigned int CRCI19:1;                  /**< \brief [19:19] Set CRCI Flag of Buffer 19 (w) */
    unsigned int CRCI20:1;                  /**< \brief [20:20] Set CRCI Flag of Buffer 20 (w) */
    unsigned int CRCI21:1;                  /**< \brief [21:21] Set CRCI Flag of Buffer 21 (w) */
    unsigned int CRCI22:1;                  /**< \brief [22:22] Set CRCI Flag of Buffer 22 (w) */
    unsigned int CRCI23:1;                  /**< \brief [23:23] Set CRCI Flag of Buffer 23 (w) */
    unsigned int CRCI24:1;                  /**< \brief [24:24] Set CRCI Flag of Buffer 24 (w) */
    unsigned int CRCI25:1;                  /**< \brief [25:25] Set CRCI Flag of Buffer 25 (w) */
    unsigned int CRCI26:1;                  /**< \brief [26:26] Set CRCI Flag of Buffer 26 (w) */
    unsigned int CRCI27:1;                  /**< \brief [27:27] Set CRCI Flag of Buffer 27 (w) */
    unsigned int CRCI28:1;                  /**< \brief [28:28] Set CRCI Flag of Buffer 28 (w) */
    unsigned int CRCI29:1;                  /**< \brief [29:29] Set CRCI Flag of Buffer 29 (w) */
    unsigned int CRCI30:1;                  /**< \brief [30:30] Set CRCI Flag of Buffer 30 (w) */
    unsigned int CRCI31:1;                  /**< \brief [31:31] Set CRCI Flag of Buffer 31 (w) */
} Ifx_PSI5_CRCISET_Bits;

/** \brief  PSI5 Fractional Divider Register */
typedef struct _Ifx_PSI5_FDR_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_PSI5_FDR_Bits;

/** \brief  Fractional Divider Register for Higher Bit Rate */
typedef struct _Ifx_PSI5_FDRH_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_PSI5_FDRH_Bits;

/** \brief  Fractional Divider Register for Lower Bit Rate */
typedef struct _Ifx_PSI5_FDRL_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_PSI5_FDRL_Bits;

/** \brief  Fractional Divider Register for Time Stamp */
typedef struct _Ifx_PSI5_FDRT_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int ECS:3;                     /**< \brief [28:26] External Time Stamp Clear Source Select (rw) */
    unsigned int ECEA:1;                    /**< \brief [29:29] External Time Stamp Clear Enable A (rw) */
    unsigned int ECEB:1;                    /**< \brief [30:30] External Time Stamp Clear Enable B (rw) */
    unsigned int ECEC:1;                    /**< \brief [31:31] External Time Stamp Clear Enable C (rw) */
} Ifx_PSI5_FDRT_Bits;

/** \brief  Global Control Register */
typedef struct _Ifx_PSI5_GCR_Bits
{
    unsigned int CRCI:1;                    /**< \brief [0:0] CRCI (rw) */
    unsigned int NBI:1;                     /**< \brief [1:1] NBI (rw) */
    unsigned int MEI:1;                     /**< \brief [2:2] MEI (rw) */
    unsigned int NFI:1;                     /**< \brief [3:3] NFI (rw) */
    unsigned int TEI:1;                     /**< \brief [4:4] TEI (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int ETC0:1;                    /**< \brief [8:8] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC1:1;                    /**< \brief [9:9] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC2:1;                    /**< \brief [10:10] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC3:1;                    /**< \brief [11:11] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC4:1;                    /**< \brief [12:12] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int reserved_13:3;             /**< \brief \internal Reserved */
    unsigned int CEN0:1;                    /**< \brief [16:16] Enable Channel (rw) */
    unsigned int CEN1:1;                    /**< \brief [17:17] Enable Channel (rw) */
    unsigned int CEN2:1;                    /**< \brief [18:18] Enable Channel (rw) */
    unsigned int CEN3:1;                    /**< \brief [19:19] Enable Channel (rw) */
    unsigned int CEN4:1;                    /**< \brief [20:20] Enable Channel (rw) */
    unsigned int reserved_21:11;            /**< \brief \internal Reserved */
} Ifx_PSI5_GCR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_PSI5_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_PSI5_ID_Bits;

/** \brief  Interrupt Node Pointer Register */
typedef struct _Ifx_PSI5_INP_Bits
{
    unsigned int RSI:4;                     /**< \brief [3:0] Interrupt Node Pointer for Interrupt RSI (rw) */
    unsigned int RDI:4;                     /**< \brief [7:4] Interrupt Node Pointer for Interrupt RDI (rw) */
    unsigned int RBI:4;                     /**< \brief [11:8] Interrupt Node Pointer for Interrupt RBI (rw) */
    unsigned int TDI:4;                     /**< \brief [15:12] Interrupt Node Pointer for Interrupt TDI (rw) */
    unsigned int TBI:4;                     /**< \brief [19:16] Interrupt Node Pointer for Interrupt TBI (rw) */
    unsigned int ERRI:4;                    /**< \brief [23:20] Interrupt Node Pointer for Interrupt ERRI (rw) */
    unsigned int SDI:4;                     /**< \brief [27:24] Interrupt Node Pointer for Interrupt SDI (rw) */
    unsigned int FWI:4;                     /**< \brief [31:28] Interrupt Node Pointer for FWI (rw) */
} Ifx_PSI5_INP_Bits;

/** \brief  Interrupt Clear Register A */
typedef struct _Ifx_PSI5_INTCLRA_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Clear Interrupt Request Flag RSI (w) */
    unsigned int RDI:1;                     /**< \brief [1:1] Clear Interrupt Request Flag RDI (w) */
    unsigned int RBI:1;                     /**< \brief [2:2] Clear Interrupt Request Flag RBI (w) */
    unsigned int TEI:1;                     /**< \brief [3:3] Clear Interrupt Request Flag TEI (w) */
    unsigned int NBI:1;                     /**< \brief [4:4] Clear Interrupt Request Flag NBI (w) */
    unsigned int MEI:1;                     /**< \brief [5:5] Clear Interrupt Request Flag MEI (w) */
    unsigned int CRCI:1;                    /**< \brief [6:6] Clear Interrupt Request Flag CRCI (w) */
    unsigned int FWI:1;                     /**< \brief [7:7] Clear Interrupt Request Flag FWI (w) */
    unsigned int RUI:1;                     /**< \brief [8:8] Clear Interrupt Request Flag RUI (w) */
    unsigned int RMI:1;                     /**< \brief [9:9] Clear Interrupt Request Flag RMI (w) */
    unsigned int TPI:1;                     /**< \brief [10:10] Clear Interrupt Request Flag TPI (w) */
    unsigned int TPOI:1;                    /**< \brief [11:11] Clear Interrupt Request Flag TPOI (w) */
    unsigned int TSI:1;                     /**< \brief [12:12] Clear Interrupt Request Flag TSI (w) */
    unsigned int TSOI:1;                    /**< \brief [13:13] Clear Interrupt Request Flag TSOI (w) */
    unsigned int TOI:1;                     /**< \brief [14:14] Clear Interrupt Request Flag TOI (w) */
    unsigned int TOOI:1;                    /**< \brief [15:15] Clear Interrupt Request Flag TOOI (w) */
    unsigned int NFI:1;                     /**< \brief [16:16] Clear Interrupt Request Flag NFI (w) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_PSI5_INTCLRA_Bits;

/** \brief  Interrupt Clear Register A */
typedef struct _Ifx_PSI5_INTCLRB_Bits
{
    unsigned int WSI0:1;                    /**< \brief [0:0] Clear Interrupt Request Flag WSI0 (w) */
    unsigned int WSI1:1;                    /**< \brief [1:1] Clear Interrupt Request Flag WSI1 (w) */
    unsigned int WSI2:1;                    /**< \brief [2:2] Clear Interrupt Request Flag WSI2 (w) */
    unsigned int WSI3:1;                    /**< \brief [3:3] Clear Interrupt Request Flag WSI3 (w) */
    unsigned int WSI4:1;                    /**< \brief [4:4] Clear Interrupt Request Flag WSI4 (w) */
    unsigned int WSI5:1;                    /**< \brief [5:5] Clear Interrupt Request Flag WSI5 (w) */
    unsigned int SDI0:1;                    /**< \brief [6:6] Clear Interrupt Request Flag SDI0 (w) */
    unsigned int SDI1:1;                    /**< \brief [7:7] Clear Interrupt Request Flag SDI1 (w) */
    unsigned int SDI2:1;                    /**< \brief [8:8] Clear Interrupt Request Flag SDI2 (w) */
    unsigned int SDI3:1;                    /**< \brief [9:9] Clear Interrupt Request Flag SDI3 (w) */
    unsigned int SDI4:1;                    /**< \brief [10:10] Clear Interrupt Request Flag SDI4 (w) */
    unsigned int SDI5:1;                    /**< \brief [11:11] Clear Interrupt Request Flag SDI5 (w) */
    unsigned int SOI0:1;                    /**< \brief [12:12] Clear Interrupt Request Flag SOI0 (w) */
    unsigned int SOI1:1;                    /**< \brief [13:13] Clear Interrupt Request Flag SOI1 (w) */
    unsigned int SOI2:1;                    /**< \brief [14:14] Clear Interrupt Request Flag SOI2 (w) */
    unsigned int SOI3:1;                    /**< \brief [15:15] Clear Interrupt Request Flag SOI3 (w) */
    unsigned int SOI4:1;                    /**< \brief [16:16] Clear Interrupt Request Flag SOI4 (w) */
    unsigned int SOI5:1;                    /**< \brief [17:17] Clear Interrupt Request Flag SOI5 (w) */
    unsigned int SCRI0:1;                   /**< \brief [18:18] Clear Interrupt Request Flag SCRI0 (w) */
    unsigned int SCRI1:1;                   /**< \brief [19:19] Clear Interrupt Request Flag SCRI1 (w) */
    unsigned int SCRI2:1;                   /**< \brief [20:20] Clear Interrupt Request Flag SCRI2 (w) */
    unsigned int SCRI3:1;                   /**< \brief [21:21] Clear Interrupt Request Flag SCRI3 (w) */
    unsigned int SCRI4:1;                   /**< \brief [22:22] Clear Interrupt Request Flag SCRI4 (w) */
    unsigned int SCRI5:1;                   /**< \brief [23:23] Clear Interrupt Request Flag SCRI5 (w) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5_INTCLRB_Bits;

/** \brief  Interrupt Enable Register A */
typedef struct _Ifx_PSI5_INTENA_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Enable Interrupt Request RSI (rw) */
    unsigned int RDI:1;                     /**< \brief [1:1] Enable Interrupt Request RDI (rw) */
    unsigned int RBI:1;                     /**< \brief [2:2] Enable Interrupt Request RBI (rw) */
    unsigned int TEI:1;                     /**< \brief [3:3] Enable Interrupt Request TEI (rw) */
    unsigned int NBI:1;                     /**< \brief [4:4] Enable Interrupt Request NBI (rw) */
    unsigned int MEI:1;                     /**< \brief [5:5] Enable Interrupt Request MEII (rw) */
    unsigned int CRCI:1;                    /**< \brief [6:6] Enable Interrupt Request CRCI (rw) */
    unsigned int FWI:1;                     /**< \brief [7:7] Enable Interrupt Request FWI (rw) */
    unsigned int RUI:1;                     /**< \brief [8:8] Enable Interrupt Request RUI (rw) */
    unsigned int RMI:1;                     /**< \brief [9:9] Enable Interrupt Request RMII (rw) */
    unsigned int TPI:1;                     /**< \brief [10:10] Enable Interrupt Request TPI (rw) */
    unsigned int TPOI:1;                    /**< \brief [11:11] Enable Interrupt Request TPOI (rw) */
    unsigned int TSI:1;                     /**< \brief [12:12] Enable Interrupt Request TSI (rw) */
    unsigned int TSOI:1;                    /**< \brief [13:13] Enable Interrupt Request TSOI (rw) */
    unsigned int TOI:1;                     /**< \brief [14:14] Enable Interrupt Request TOI (rw) */
    unsigned int TOOI:1;                    /**< \brief [15:15] Enable Interrupt Request TOOI (rw) */
    unsigned int NFI:1;                     /**< \brief [16:16] Enable Interrupt Request NFI (rw) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_PSI5_INTENA_Bits;

/** \brief  Interrupt Enable Register B */
typedef struct _Ifx_PSI5_INTENB_Bits
{
    unsigned int WSI0:1;                    /**< \brief [0:0] Enable Interrupt Request WSI0 (rw) */
    unsigned int WSI1:1;                    /**< \brief [1:1] Enable Interrupt Request WSI1 (rw) */
    unsigned int WSI2:1;                    /**< \brief [2:2] Enable Interrupt Request WSI2 (rw) */
    unsigned int WSI3:1;                    /**< \brief [3:3] Enable Interrupt Request WSI3 (rw) */
    unsigned int WSI4:1;                    /**< \brief [4:4] Enable Interrupt Request WSI4 (rw) */
    unsigned int WSI5:1;                    /**< \brief [5:5] Enable Interrupt Request WSI5 (rw) */
    unsigned int SDI0:1;                    /**< \brief [6:6] Enable Interrupt Request SDI0 (rw) */
    unsigned int SDI1:1;                    /**< \brief [7:7] Enable Interrupt Request SDI1 (rw) */
    unsigned int SDI2:1;                    /**< \brief [8:8] Enable Interrupt Request SDI2 (rw) */
    unsigned int SDI3:1;                    /**< \brief [9:9] Enable Interrupt Request SDI3 (rw) */
    unsigned int SDI4:1;                    /**< \brief [10:10] Enable Interrupt Request SDI4 (rw) */
    unsigned int SDI5:1;                    /**< \brief [11:11] Enable Interrupt Request SDI5 (rw) */
    unsigned int SOI0:1;                    /**< \brief [12:12] Enable Interrupt Request SOI0 (rw) */
    unsigned int SOI1:1;                    /**< \brief [13:13] Enable Interrupt Request SOI1 (rw) */
    unsigned int SOI2:1;                    /**< \brief [14:14] Enable Interrupt Request SOI2 (rw) */
    unsigned int SOI3:1;                    /**< \brief [15:15] Enable Interrupt Request SOI3 (rw) */
    unsigned int SOI4:1;                    /**< \brief [16:16] Enable Interrupt Request SOI4 (rw) */
    unsigned int SOI5:1;                    /**< \brief [17:17] Enable Interrupt Request SOI5 (rw) */
    unsigned int SCRI0:1;                   /**< \brief [18:18] Enable Interrupt Request SCRI0 (rw) */
    unsigned int SCRI1:1;                   /**< \brief [19:19] Enable Interrupt Request SCRI1 (rw) */
    unsigned int SCRI2:1;                   /**< \brief [20:20] Enable Interrupt Request SCRI2 (rw) */
    unsigned int SCRI3:1;                   /**< \brief [21:21] Enable Interrupt Request SCRI3 (rw) */
    unsigned int SCRI4:1;                   /**< \brief [22:22] Enable Interrupt Request SCRI4 (rw) */
    unsigned int SCRI5:1;                   /**< \brief [23:23] Enable Interrupt Request SCRI5 (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5_INTENB_Bits;

/** \brief  Interrupt Overview Register */
typedef struct _Ifx_PSI5_INTOV_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Interrupt Pending on any Node Pointer RSI (rh) */
    unsigned int RDI:1;                     /**< \brief [1:1] Interrupt Pending on any Node Pointer RDI (rh) */
    unsigned int RBI:1;                     /**< \brief [2:2] Interrupt Pending on any Node Pointer RBI (rh) */
    unsigned int TDI:1;                     /**< \brief [3:3] Interrupt Pending on any Node Pointer TDI (rh) */
    unsigned int TBI:1;                     /**< \brief [4:4] Interrupt Pending on any Node Pointer TBI (rh) */
    unsigned int ERRI:1;                    /**< \brief [5:5] Interrupt Pending on any Node Pointer ERRI (rh) */
    unsigned int SDI:1;                     /**< \brief [6:6] Interrupt Pending on any Node Pointer SDI (rh) */
    unsigned int FWI:1;                     /**< \brief [7:7] Interrupt Pending on any Node Pointer FWI (rh) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_PSI5_INTOV_Bits;

/** \brief  Interrupt Set Register A */
typedef struct _Ifx_PSI5_INTSETA_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Set Interrupt Request Flag RSI (w) */
    unsigned int RDI:1;                     /**< \brief [1:1] Set Interrupt Request Flag RDI (w) */
    unsigned int RBI:1;                     /**< \brief [2:2] Set Interrupt Request Flag RBI (w) */
    unsigned int TEI:1;                     /**< \brief [3:3] Set Interrupt Request Flag TEI (w) */
    unsigned int NBI:1;                     /**< \brief [4:4] Set Interrupt Request Flag NBI (w) */
    unsigned int MEI:1;                     /**< \brief [5:5] Set Interrupt Request Flag MEI (w) */
    unsigned int CRCI:1;                    /**< \brief [6:6] Set Interrupt Request Flag CRCI (w) */
    unsigned int FWI:1;                     /**< \brief [7:7] Set Interrupt Request Flag FWI (w) */
    unsigned int RUI:1;                     /**< \brief [8:8] Set Interrupt Request Flag RUI (w) */
    unsigned int RMI:1;                     /**< \brief [9:9] Set Interrupt Request Flag RMI (w) */
    unsigned int TPI:1;                     /**< \brief [10:10] Set Interrupt Request Flag TPI (w) */
    unsigned int TPOI:1;                    /**< \brief [11:11] Set Interrupt Request Flag TPOI (w) */
    unsigned int TSI:1;                     /**< \brief [12:12] Set Interrupt Request Flag TSI (w) */
    unsigned int TSOI:1;                    /**< \brief [13:13] Set Interrupt Request Flag TSOI (w) */
    unsigned int TOI:1;                     /**< \brief [14:14] Set Interrupt Request Flag TOI (w) */
    unsigned int TOOI:1;                    /**< \brief [15:15] Set Interrupt Request Flag TOOI (w) */
    unsigned int NFI:1;                     /**< \brief [16:16] Set Interrupt Request Flag NFI (w) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_PSI5_INTSETA_Bits;

/** \brief  Interrupt Set Register B */
typedef struct _Ifx_PSI5_INTSETB_Bits
{
    unsigned int WSI0:1;                    /**< \brief [0:0] Set Interrupt Request Flag WSI0 (w) */
    unsigned int WSI1:1;                    /**< \brief [1:1] Set Interrupt Request Flag WSI1 (w) */
    unsigned int WSI2:1;                    /**< \brief [2:2] Set Interrupt Request Flag WSI2 (w) */
    unsigned int WSI3:1;                    /**< \brief [3:3] Set Interrupt Request Flag WSI3 (w) */
    unsigned int WSI4:1;                    /**< \brief [4:4] Set Interrupt Request Flag WSI4 (w) */
    unsigned int WSI5:1;                    /**< \brief [5:5] Set Interrupt Request Flag WSI5 (w) */
    unsigned int SDI0:1;                    /**< \brief [6:6] Set Interrupt Request Flag SDI0 (w) */
    unsigned int SDI1:1;                    /**< \brief [7:7] Set Interrupt Request Flag SDI1 (w) */
    unsigned int SDI2:1;                    /**< \brief [8:8] Set Interrupt Request Flag SDI2 (w) */
    unsigned int SDI3:1;                    /**< \brief [9:9] Set Interrupt Request Flag SDI3 (w) */
    unsigned int SDI4:1;                    /**< \brief [10:10] Set Interrupt Request Flag SDI4 (w) */
    unsigned int SDI5:1;                    /**< \brief [11:11] Set Interrupt Request Flag SDI5 (w) */
    unsigned int SOI0:1;                    /**< \brief [12:12] Set Interrupt Request Flag SOI0 (w) */
    unsigned int SOI1:1;                    /**< \brief [13:13] Set Interrupt Request Flag SOI1 (w) */
    unsigned int SOI2:1;                    /**< \brief [14:14] Set Interrupt Request Flag SOI2 (w) */
    unsigned int SOI3:1;                    /**< \brief [15:15] Set Interrupt Request Flag SOI3 (w) */
    unsigned int SOI4:1;                    /**< \brief [16:16] Set Interrupt Request Flag SOI4 (w) */
    unsigned int SOI5:1;                    /**< \brief [17:17] Set Interrupt Request Flag SOI5 (w) */
    unsigned int SCRI0:1;                   /**< \brief [18:18] Set Interrupt Request Flag SCRI0 (w) */
    unsigned int SCRI1:1;                   /**< \brief [19:19] Set Interrupt Request Flag SCRI1 (w) */
    unsigned int SCRI2:1;                   /**< \brief [20:20] Set Interrupt Request Flag SCRI2 (w) */
    unsigned int SCRI3:1;                   /**< \brief [21:21] Set Interrupt Request Flag SCRI3 (w) */
    unsigned int SCRI4:1;                   /**< \brief [22:22] Set Interrupt Request Flag SCRI4 (w) */
    unsigned int SCRI5:1;                   /**< \brief [23:23] Set Interrupt Request Flag SCRI5 (w) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5_INTSETB_Bits;

/** \brief  Interrupt Status Register A */
typedef struct _Ifx_PSI5_INTSTATA_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Receive Success Interrupt Request Flag (rh) */
    unsigned int RDI:1;                     /**< \brief [1:1] Receive Data Interrupt Request Flag (rh) */
    unsigned int RBI:1;                     /**< \brief [2:2] Receive Buffer Overflow Interrupt Request Flag (rh) */
    unsigned int TEI:1;                     /**< \brief [3:3] Time Slot Error Interrupt Request Flag (rh) */
    unsigned int NBI:1;                     /**< \brief [4:4] Number of Bits Wrong Request Flag (rh) */
    unsigned int MEI:1;                     /**< \brief [5:5] Error in Message Bits Flag (rh) */
    unsigned int CRCI:1;                    /**< \brief [6:6] CRC Error Request Flag (rh) */
    unsigned int FWI:1;                     /**< \brief [7:7] FIFO Warning Level Request Flag (rh) */
    unsigned int RUI:1;                     /**< \brief [8:8] Receive Memory Underrun Interrupt Request Flag (rh) */
    unsigned int RMI:1;                     /**< \brief [9:9] Receive Memory Overflow Flag (rh) */
    unsigned int TPI:1;                     /**< \brief [10:10] Transfer Preparation Interrupt Request Flag (rh) */
    unsigned int TPOI:1;                    /**< \brief [11:11] Transmit Preparation Overflow Interrupt Request Flag (rh) */
    unsigned int TSI:1;                     /**< \brief [12:12] Transfer Shift Interrupt Request Flag (rh) */
    unsigned int TSOI:1;                    /**< \brief [13:13] Transmit Shift Overflow Interrupt Request Flag (rh) */
    unsigned int TOI:1;                     /**< \brief [14:14] Transfer Output Interrupt Request Flag (rh) */
    unsigned int TOOI:1;                    /**< \brief [15:15] Transmit Shift Overflow Interrupt Request Flag (rh) */
    unsigned int NFI:1;                     /**< \brief [16:16] No Frame Received Interrupt Flag (rh) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_PSI5_INTSTATA_Bits;

/** \brief  Interrupt Status Register B */
typedef struct _Ifx_PSI5_INTSTATB_Bits
{
    unsigned int WSI0:1;                    /**< \brief [0:0] Wrong Serial Protocol Error Request Flag (rh) */
    unsigned int WSI1:1;                    /**< \brief [1:1] Wrong Serial Protocol Error Request Flag (rh) */
    unsigned int WSI2:1;                    /**< \brief [2:2] Wrong Serial Protocol Error Request Flag (rh) */
    unsigned int WSI3:1;                    /**< \brief [3:3] Wrong Serial Protocol Error Request Flag (rh) */
    unsigned int WSI4:1;                    /**< \brief [4:4] Wrong Serial Protocol Error Request Flag (rh) */
    unsigned int WSI5:1;                    /**< \brief [5:5] Wrong Serial Protocol Error Request Flag (rh) */
    unsigned int SDI0:1;                    /**< \brief [6:6] Serial Data Receive Interrupt Request Flag (rh) */
    unsigned int SDI1:1;                    /**< \brief [7:7] Serial Data Receive Interrupt Request Flag (rh) */
    unsigned int SDI2:1;                    /**< \brief [8:8] Serial Data Receive Interrupt Request Flag (rh) */
    unsigned int SDI3:1;                    /**< \brief [9:9] Serial Data Receive Interrupt Request Flag (rh) */
    unsigned int SDI4:1;                    /**< \brief [10:10] Serial Data Receive Interrupt Request Flag (rh) */
    unsigned int SDI5:1;                    /**< \brief [11:11] Serial Data Receive Interrupt Request Flag (rh) */
    unsigned int SOI0:1;                    /**< \brief [12:12] Serial Data Buffer Overrun Interrupt Request Flag (rh) */
    unsigned int SOI1:1;                    /**< \brief [13:13] Serial Data Buffer Overrun Interrupt Request Flag (rh) */
    unsigned int SOI2:1;                    /**< \brief [14:14] Serial Data Buffer Overrun Interrupt Request Flag (rh) */
    unsigned int SOI3:1;                    /**< \brief [15:15] Serial Data Buffer Overrun Interrupt Request Flag (rh) */
    unsigned int SOI4:1;                    /**< \brief [16:16] Serial Data Buffer Overrun Interrupt Request Flag (rh) */
    unsigned int SOI5:1;                    /**< \brief [17:17] Serial Data Buffer Overrun Interrupt Request Flag (rh) */
    unsigned int SCRI0:1;                   /**< \brief [18:18] Serial Data CRC Error Request Flag (rh) */
    unsigned int SCRI1:1;                   /**< \brief [19:19] Serial Data CRC Error Request Flag (rh) */
    unsigned int SCRI2:1;                   /**< \brief [20:20] Serial Data CRC Error Request Flag (rh) */
    unsigned int SCRI3:1;                   /**< \brief [21:21] Serial Data CRC Error Request Flag (rh) */
    unsigned int SCRI4:1;                   /**< \brief [22:22] Serial Data CRC Error Request Flag (rh) */
    unsigned int SCRI5:1;                   /**< \brief [23:23] Serial Data CRC Error Request Flag (rh) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5_INTSTATB_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_PSI5_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_PSI5_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_PSI5_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_PSI5_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_PSI5_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_PSI5_KRSTCLR_Bits;

/** \brief  MEIOV Clear Register */
typedef struct _Ifx_PSI5_MEICLR_Bits
{
    unsigned int MEI0:1;                    /**< \brief [0:0] Clear MEI Flag of Buffer 0 (w) */
    unsigned int MEI1:1;                    /**< \brief [1:1] Clear MEI Flag of Buffer 1 (w) */
    unsigned int MEI2:1;                    /**< \brief [2:2] Clear MEI Flag of Buffer 2 (w) */
    unsigned int MEI3:1;                    /**< \brief [3:3] Clear MEI Flag of Buffer 3 (w) */
    unsigned int MEI4:1;                    /**< \brief [4:4] Clear MEI Flag of Buffer 4 (w) */
    unsigned int MEI5:1;                    /**< \brief [5:5] Clear MEI Flag of Buffer 5 (w) */
    unsigned int MEI6:1;                    /**< \brief [6:6] Clear MEI Flag of Buffer 6 (w) */
    unsigned int MEI7:1;                    /**< \brief [7:7] Clear MEI Flag of Buffer 7 (w) */
    unsigned int MEI8:1;                    /**< \brief [8:8] Clear MEI Flag of Buffer 8 (w) */
    unsigned int MEI9:1;                    /**< \brief [9:9] Clear MEI Flag of Buffer 9 (w) */
    unsigned int MEI10:1;                   /**< \brief [10:10] Clear MEI Flag of Buffer 10 (w) */
    unsigned int MEI11:1;                   /**< \brief [11:11] Clear MEI Flag of Buffer 11 (w) */
    unsigned int MEI12:1;                   /**< \brief [12:12] Clear MEI Flag of Buffer 12 (w) */
    unsigned int MEI13:1;                   /**< \brief [13:13] Clear MEI Flag of Buffer 13 (w) */
    unsigned int MEI14:1;                   /**< \brief [14:14] Clear MEI Flag of Buffer 14 (w) */
    unsigned int MEI15:1;                   /**< \brief [15:15] Clear MEI Flag of Buffer 15 (w) */
    unsigned int MEI16:1;                   /**< \brief [16:16] Clear MEI Flag of Buffer 16 (w) */
    unsigned int MEI17:1;                   /**< \brief [17:17] Clear MEI Flag of Buffer 17 (w) */
    unsigned int MEI18:1;                   /**< \brief [18:18] Clear MEI Flag of Buffer 18 (w) */
    unsigned int MEI19:1;                   /**< \brief [19:19] Clear MEI Flag of Buffer 19 (w) */
    unsigned int MEI20:1;                   /**< \brief [20:20] Clear MEI Flag of Buffer 20 (w) */
    unsigned int MEI21:1;                   /**< \brief [21:21] Clear MEI Flag of Buffer 21 (w) */
    unsigned int MEI22:1;                   /**< \brief [22:22] Clear MEI Flag of Buffer 22 (w) */
    unsigned int MEI23:1;                   /**< \brief [23:23] Clear MEI Flag of Buffer 23 (w) */
    unsigned int MEI24:1;                   /**< \brief [24:24] Clear MEI Flag of Buffer 24 (w) */
    unsigned int MEI25:1;                   /**< \brief [25:25] Clear MEI Flag of Buffer 25 (w) */
    unsigned int MEI26:1;                   /**< \brief [26:26] Clear MEI Flag of Buffer 26 (w) */
    unsigned int MEI27:1;                   /**< \brief [27:27] Clear MEI Flag of Buffer 27 (w) */
    unsigned int MEI28:1;                   /**< \brief [28:28] Clear MEI Flag of Buffer 28 (w) */
    unsigned int MEI29:1;                   /**< \brief [29:29] Clear MEI Flag of Buffer 29 (w) */
    unsigned int MEI30:1;                   /**< \brief [30:30] Clear MEI Flag of Buffer 30 (w) */
    unsigned int MEI31:1;                   /**< \brief [31:31] Clear MEI Flag of Buffer 31 (w) */
} Ifx_PSI5_MEICLR_Bits;

/** \brief  MEI Overview Register */
typedef struct _Ifx_PSI5_MEIOV_Bits
{
    unsigned int MEI0:1;                    /**< \brief [0:0] MEI Flag of Buffer 0 (rh) */
    unsigned int MEI1:1;                    /**< \brief [1:1] MEI Flag of Buffer 1 (rh) */
    unsigned int MEI2:1;                    /**< \brief [2:2] MEI Flag of Buffer 2 (rh) */
    unsigned int MEI3:1;                    /**< \brief [3:3] MEI Flag of Buffer 3 (rh) */
    unsigned int MEI4:1;                    /**< \brief [4:4] MEI Flag of Buffer 4 (rh) */
    unsigned int MEI5:1;                    /**< \brief [5:5] MEI Flag of Buffer 5 (rh) */
    unsigned int MEI6:1;                    /**< \brief [6:6] MEI Flag of Buffer 6 (rh) */
    unsigned int MEI7:1;                    /**< \brief [7:7] MEI Flag of Buffer 7 (rh) */
    unsigned int MEI8:1;                    /**< \brief [8:8] MEI Flag of Buffer 8 (rh) */
    unsigned int MEI9:1;                    /**< \brief [9:9] MEI Flag of Buffer 9 (rh) */
    unsigned int MEI10:1;                   /**< \brief [10:10] MEI Flag of Buffer 10 (rh) */
    unsigned int MEI11:1;                   /**< \brief [11:11] MEI Flag of Buffer 11 (rh) */
    unsigned int MEI12:1;                   /**< \brief [12:12] MEI Flag of Buffer 12 (rh) */
    unsigned int MEI13:1;                   /**< \brief [13:13] MEI Flag of Buffer 13 (rh) */
    unsigned int MEI14:1;                   /**< \brief [14:14] MEI Flag of Buffer 14 (rh) */
    unsigned int MEI15:1;                   /**< \brief [15:15] MEI Flag of Buffer 15 (rh) */
    unsigned int MEI16:1;                   /**< \brief [16:16] MEI Flag of Buffer 16 (rh) */
    unsigned int MEI17:1;                   /**< \brief [17:17] MEI Flag of Buffer 17 (rh) */
    unsigned int MEI18:1;                   /**< \brief [18:18] MEI Flag of Buffer 18 (rh) */
    unsigned int MEI19:1;                   /**< \brief [19:19] MEI Flag of Buffer 19 (rh) */
    unsigned int MEI20:1;                   /**< \brief [20:20] MEI Flag of Buffer 20 (rh) */
    unsigned int MEI21:1;                   /**< \brief [21:21] MEI Flag of Buffer 21 (rh) */
    unsigned int MEI22:1;                   /**< \brief [22:22] MEI Flag of Buffer 22 (rh) */
    unsigned int MEI23:1;                   /**< \brief [23:23] MEI Flag of Buffer 23 (rh) */
    unsigned int MEI24:1;                   /**< \brief [24:24] MEI Flag of Buffer 24 (rh) */
    unsigned int MEI25:1;                   /**< \brief [25:25] MEI Flag of Buffer 25 (rh) */
    unsigned int MEI26:1;                   /**< \brief [26:26] MEI Flag of Buffer 26 (rh) */
    unsigned int MEI27:1;                   /**< \brief [27:27] MEI Flag of Buffer 27 (rh) */
    unsigned int MEI28:1;                   /**< \brief [28:28] MEI Flag of Buffer 28 (rh) */
    unsigned int MEI29:1;                   /**< \brief [29:29] MEI Flag of Buffer 29 (rh) */
    unsigned int MEI30:1;                   /**< \brief [30:30] MEI Flag of Buffer 30 (rh) */
    unsigned int MEI31:1;                   /**< \brief [31:31] MEI Flag of Buffer 31 (rh) */
} Ifx_PSI5_MEIOV_Bits;

/** \brief  MEIOV Set Register */
typedef struct _Ifx_PSI5_MEISET_Bits
{
    unsigned int MEI0:1;                    /**< \brief [0:0] Set MEI Flag of Buffer 0 (w) */
    unsigned int MEI1:1;                    /**< \brief [1:1] Set MEI Flag of Buffer 1 (w) */
    unsigned int MEI2:1;                    /**< \brief [2:2] Set MEI Flag of Buffer 2 (w) */
    unsigned int MEI3:1;                    /**< \brief [3:3] Set MEI Flag of Buffer 3 (w) */
    unsigned int MEI4:1;                    /**< \brief [4:4] Set MEI Flag of Buffer 4 (w) */
    unsigned int MEI5:1;                    /**< \brief [5:5] Set MEI Flag of Buffer 5 (w) */
    unsigned int MEI6:1;                    /**< \brief [6:6] Set MEI Flag of Buffer 6 (w) */
    unsigned int MEI7:1;                    /**< \brief [7:7] Set MEI Flag of Buffer 7 (w) */
    unsigned int MEI8:1;                    /**< \brief [8:8] Set MEI Flag of Buffer 8 (w) */
    unsigned int MEI9:1;                    /**< \brief [9:9] Set MEI Flag of Buffer 9 (w) */
    unsigned int MEI10:1;                   /**< \brief [10:10] Set MEI Flag of Buffer 10 (w) */
    unsigned int MEI11:1;                   /**< \brief [11:11] Set MEI Flag of Buffer 11 (w) */
    unsigned int MEI12:1;                   /**< \brief [12:12] Set MEI Flag of Buffer 12 (w) */
    unsigned int MEI13:1;                   /**< \brief [13:13] Set MEI Flag of Buffer 13 (w) */
    unsigned int MEI14:1;                   /**< \brief [14:14] Set MEI Flag of Buffer 14 (w) */
    unsigned int MEI15:1;                   /**< \brief [15:15] Set MEI Flag of Buffer 15 (w) */
    unsigned int MEI16:1;                   /**< \brief [16:16] Set MEI Flag of Buffer 16 (w) */
    unsigned int MEI17:1;                   /**< \brief [17:17] Set MEI Flag of Buffer 17 (w) */
    unsigned int MEI18:1;                   /**< \brief [18:18] Set MEI Flag of Buffer 18 (w) */
    unsigned int MEI19:1;                   /**< \brief [19:19] Set MEI Flag of Buffer 19 (w) */
    unsigned int MEI20:1;                   /**< \brief [20:20] Set MEI Flag of Buffer 20 (w) */
    unsigned int MEI21:1;                   /**< \brief [21:21] Set MEI Flag of Buffer 21 (w) */
    unsigned int MEI22:1;                   /**< \brief [22:22] Set MEI Flag of Buffer 22 (w) */
    unsigned int MEI23:1;                   /**< \brief [23:23] Set MEI Flag of Buffer 23 (w) */
    unsigned int MEI24:1;                   /**< \brief [24:24] Set MEI Flag of Buffer 24 (w) */
    unsigned int MEI25:1;                   /**< \brief [25:25] Set MEI Flag of Buffer 25 (w) */
    unsigned int MEI26:1;                   /**< \brief [26:26] Set MEI Flag of Buffer 26 (w) */
    unsigned int MEI27:1;                   /**< \brief [27:27] Set MEI Flag of Buffer 27 (w) */
    unsigned int MEI28:1;                   /**< \brief [28:28] Set MEI Flag of Buffer 28 (w) */
    unsigned int MEI29:1;                   /**< \brief [29:29] Set MEI Flag of Buffer 29 (w) */
    unsigned int MEI30:1;                   /**< \brief [30:30] Set MEI Flag of Buffer 30 (w) */
    unsigned int MEI31:1;                   /**< \brief [31:31] Set MEI Flag of Buffer 31 (w) */
} Ifx_PSI5_MEISET_Bits;

/** \brief  NBIOV Clear Register */
typedef struct _Ifx_PSI5_NBICLR_Bits
{
    unsigned int NBI0:1;                    /**< \brief [0:0] Clear NBI Flag of Buffer 0 (w) */
    unsigned int NBI1:1;                    /**< \brief [1:1] Clear NBI Flag of Buffer 1 (w) */
    unsigned int NBI2:1;                    /**< \brief [2:2] Clear NBI Flag of Buffer 2 (w) */
    unsigned int NBI3:1;                    /**< \brief [3:3] Clear NBI Flag of Buffer 3 (w) */
    unsigned int NBI4:1;                    /**< \brief [4:4] Clear NBI Flag of Buffer 4 (w) */
    unsigned int NBI5:1;                    /**< \brief [5:5] Clear NBI Flag of Buffer 5 (w) */
    unsigned int NBI6:1;                    /**< \brief [6:6] Clear NBI Flag of Buffer 6 (w) */
    unsigned int NBI7:1;                    /**< \brief [7:7] Clear NBI Flag of Buffer 7 (w) */
    unsigned int NBI8:1;                    /**< \brief [8:8] Clear NBI Flag of Buffer 8 (w) */
    unsigned int NBI9:1;                    /**< \brief [9:9] Clear NBI Flag of Buffer 9 (w) */
    unsigned int NBI10:1;                   /**< \brief [10:10] Clear NBI Flag of Buffer 10 (w) */
    unsigned int NBI11:1;                   /**< \brief [11:11] Clear NBI Flag of Buffer 11 (w) */
    unsigned int NBI12:1;                   /**< \brief [12:12] Clear NBI Flag of Buffer 12 (w) */
    unsigned int NBI13:1;                   /**< \brief [13:13] Clear NBI Flag of Buffer 13 (w) */
    unsigned int NBI14:1;                   /**< \brief [14:14] Clear NBI Flag of Buffer 14 (w) */
    unsigned int NBI15:1;                   /**< \brief [15:15] Clear NBI Flag of Buffer 15 (w) */
    unsigned int NBI16:1;                   /**< \brief [16:16] Clear NBI Flag of Buffer 16 (w) */
    unsigned int NBI17:1;                   /**< \brief [17:17] Clear NBI Flag of Buffer 17 (w) */
    unsigned int NBI18:1;                   /**< \brief [18:18] Clear NBI Flag of Buffer 18 (w) */
    unsigned int NBI19:1;                   /**< \brief [19:19] Clear NBI Flag of Buffer 19 (w) */
    unsigned int NBI20:1;                   /**< \brief [20:20] Clear NBI Flag of Buffer 20 (w) */
    unsigned int NBI21:1;                   /**< \brief [21:21] Clear NBI Flag of Buffer 21 (w) */
    unsigned int NBI22:1;                   /**< \brief [22:22] Clear NBI Flag of Buffer 22 (w) */
    unsigned int NBI23:1;                   /**< \brief [23:23] Clear NBI Flag of Buffer 23 (w) */
    unsigned int NBI24:1;                   /**< \brief [24:24] Clear NBI Flag of Buffer 24 (w) */
    unsigned int NBI25:1;                   /**< \brief [25:25] Clear NBI Flag of Buffer 25 (w) */
    unsigned int NBI26:1;                   /**< \brief [26:26] Clear NBI Flag of Buffer 26 (w) */
    unsigned int NBI27:1;                   /**< \brief [27:27] Clear NBI Flag of Buffer 27 (w) */
    unsigned int NBI28:1;                   /**< \brief [28:28] Clear NBI Flag of Buffer 28 (w) */
    unsigned int NBI29:1;                   /**< \brief [29:29] Clear NBI Flag of Buffer 29 (w) */
    unsigned int NBI30:1;                   /**< \brief [30:30] Clear NBI Flag of Buffer 30 (w) */
    unsigned int NBI31:1;                   /**< \brief [31:31] Clear NBI Flag of Buffer 31 (w) */
} Ifx_PSI5_NBICLR_Bits;

/** \brief  NBI Overview Register */
typedef struct _Ifx_PSI5_NBIOV_Bits
{
    unsigned int NBI0:1;                    /**< \brief [0:0] NBI Flag of Buffer 0 (rh) */
    unsigned int NBI1:1;                    /**< \brief [1:1] NBI Flag of Buffer 1 (rh) */
    unsigned int NBI2:1;                    /**< \brief [2:2] NBI Flag of Buffer 2 (rh) */
    unsigned int NBI3:1;                    /**< \brief [3:3] NBI Flag of Buffer 3 (rh) */
    unsigned int NBI4:1;                    /**< \brief [4:4] NBI Flag of Buffer 4 (rh) */
    unsigned int NBI5:1;                    /**< \brief [5:5] NBI Flag of Buffer 5 (rh) */
    unsigned int NBI6:1;                    /**< \brief [6:6] NBI Flag of Buffer 6 (rh) */
    unsigned int NBI7:1;                    /**< \brief [7:7] NBI Flag of Buffer 7 (rh) */
    unsigned int NBI8:1;                    /**< \brief [8:8] NBI Flag of Buffer 8 (rh) */
    unsigned int NBI9:1;                    /**< \brief [9:9] NBI Flag of Buffer 9 (rh) */
    unsigned int NBI10:1;                   /**< \brief [10:10] NBI Flag of Buffer 10 (rh) */
    unsigned int NBI11:1;                   /**< \brief [11:11] NBI Flag of Buffer 11 (rh) */
    unsigned int NBI12:1;                   /**< \brief [12:12] NBI Flag of Buffer 12 (rh) */
    unsigned int NBI13:1;                   /**< \brief [13:13] NBI Flag of Buffer 13 (rh) */
    unsigned int NBI14:1;                   /**< \brief [14:14] NBI Flag of Buffer 14 (rh) */
    unsigned int NBI15:1;                   /**< \brief [15:15] NBI Flag of Buffer 15 (rh) */
    unsigned int NBI16:1;                   /**< \brief [16:16] NBI Flag of Buffer 16 (rh) */
    unsigned int NBI17:1;                   /**< \brief [17:17] NBI Flag of Buffer 17 (rh) */
    unsigned int NBI18:1;                   /**< \brief [18:18] NBI Flag of Buffer 18 (rh) */
    unsigned int NBI19:1;                   /**< \brief [19:19] NBI Flag of Buffer 19 (rh) */
    unsigned int NBI20:1;                   /**< \brief [20:20] NBI Flag of Buffer 20 (rh) */
    unsigned int NBI21:1;                   /**< \brief [21:21] NBI Flag of Buffer 21 (rh) */
    unsigned int NBI22:1;                   /**< \brief [22:22] NBI Flag of Buffer 22 (rh) */
    unsigned int NBI23:1;                   /**< \brief [23:23] NBI Flag of Buffer 23 (rh) */
    unsigned int NBI24:1;                   /**< \brief [24:24] NBI Flag of Buffer 24 (rh) */
    unsigned int NBI25:1;                   /**< \brief [25:25] NBI Flag of Buffer 25 (rh) */
    unsigned int NBI26:1;                   /**< \brief [26:26] NBI Flag of Buffer 26 (rh) */
    unsigned int NBI27:1;                   /**< \brief [27:27] NBI Flag of Buffer 27 (rh) */
    unsigned int NBI28:1;                   /**< \brief [28:28] NBI Flag of Buffer 28 (rh) */
    unsigned int NBI29:1;                   /**< \brief [29:29] NBI Flag of Buffer 29 (rh) */
    unsigned int NBI30:1;                   /**< \brief [30:30] NBI Flag of Buffer 30 (rh) */
    unsigned int NBI31:1;                   /**< \brief [31:31] NBI Flag of Buffer 31 (rh) */
} Ifx_PSI5_NBIOV_Bits;

/** \brief  NBIOV Set Register */
typedef struct _Ifx_PSI5_NBISET_Bits
{
    unsigned int NBI0:1;                    /**< \brief [0:0] Set NBI Flag of Buffer 0 (w) */
    unsigned int NBI1:1;                    /**< \brief [1:1] Set NBI Flag of Buffer 1 (w) */
    unsigned int NBI2:1;                    /**< \brief [2:2] Set NBI Flag of Buffer 2 (w) */
    unsigned int NBI3:1;                    /**< \brief [3:3] Set NBI Flag of Buffer 3 (w) */
    unsigned int NBI4:1;                    /**< \brief [4:4] Set NBI Flag of Buffer 4 (w) */
    unsigned int NBI5:1;                    /**< \brief [5:5] Set NBI Flag of Buffer 5 (w) */
    unsigned int NBI6:1;                    /**< \brief [6:6] Set NBI Flag of Buffer 6 (w) */
    unsigned int NBI7:1;                    /**< \brief [7:7] Set NBI Flag of Buffer 7 (w) */
    unsigned int NBI8:1;                    /**< \brief [8:8] Set NBI Flag of Buffer 8 (w) */
    unsigned int NBI9:1;                    /**< \brief [9:9] Set NBI Flag of Buffer 9 (w) */
    unsigned int NBI10:1;                   /**< \brief [10:10] Set NBI Flag of Buffer 10 (w) */
    unsigned int NBI11:1;                   /**< \brief [11:11] Set NBI Flag of Buffer 11 (w) */
    unsigned int NBI12:1;                   /**< \brief [12:12] Set NBI Flag of Buffer 12 (w) */
    unsigned int NBI13:1;                   /**< \brief [13:13] Set NBI Flag of Buffer 13 (w) */
    unsigned int NBI14:1;                   /**< \brief [14:14] Set NBI Flag of Buffer 14 (w) */
    unsigned int NBI15:1;                   /**< \brief [15:15] Set NBI Flag of Buffer 15 (w) */
    unsigned int NBI16:1;                   /**< \brief [16:16] Set NBI Flag of Buffer 16 (w) */
    unsigned int NBI17:1;                   /**< \brief [17:17] Set NBI Flag of Buffer 17 (w) */
    unsigned int NBI18:1;                   /**< \brief [18:18] Set NBI Flag of Buffer 18 (w) */
    unsigned int NBI19:1;                   /**< \brief [19:19] Set NBI Flag of Buffer 19 (w) */
    unsigned int NBI20:1;                   /**< \brief [20:20] Set NBI Flag of Buffer 20 (w) */
    unsigned int NBI21:1;                   /**< \brief [21:21] Set NBI Flag of Buffer 21 (w) */
    unsigned int NBI22:1;                   /**< \brief [22:22] Set NBI Flag of Buffer 22 (w) */
    unsigned int NBI23:1;                   /**< \brief [23:23] Set NBI Flag of Buffer 23 (w) */
    unsigned int NBI24:1;                   /**< \brief [24:24] Set NBI Flag of Buffer 24 (w) */
    unsigned int NBI25:1;                   /**< \brief [25:25] Set NBI Flag of Buffer 25 (w) */
    unsigned int NBI26:1;                   /**< \brief [26:26] Set NBI Flag of Buffer 26 (w) */
    unsigned int NBI27:1;                   /**< \brief [27:27] Set NBI Flag of Buffer 27 (w) */
    unsigned int NBI28:1;                   /**< \brief [28:28] Set NBI Flag of Buffer 28 (w) */
    unsigned int NBI29:1;                   /**< \brief [29:29] Set NBI Flag of Buffer 29 (w) */
    unsigned int NBI30:1;                   /**< \brief [30:30] Set NBI Flag of Buffer 30 (w) */
    unsigned int NBI31:1;                   /**< \brief [31:31] Set NBI Flag of Buffer 31 (w) */
} Ifx_PSI5_NBISET_Bits;

/** \brief  NFIOV Clear Register */
typedef struct _Ifx_PSI5_NFICLR_Bits
{
    unsigned int NFI0:1;                    /**< \brief [0:0] Clear NFI Flag of Buffer 0 (w) */
    unsigned int NFI1:1;                    /**< \brief [1:1] Clear NFI Flag of Buffer 1 (w) */
    unsigned int NFI2:1;                    /**< \brief [2:2] Clear NFI Flag of Buffer 2 (w) */
    unsigned int NFI3:1;                    /**< \brief [3:3] Clear NFI Flag of Buffer 3 (w) */
    unsigned int NFI4:1;                    /**< \brief [4:4] Clear NFI Flag of Buffer 4 (w) */
    unsigned int NFI5:1;                    /**< \brief [5:5] Clear NFI Flag of Buffer 5 (w) */
    unsigned int NFI6:1;                    /**< \brief [6:6] Clear NFI Flag of Buffer 6 (w) */
    unsigned int NFI7:1;                    /**< \brief [7:7] Clear NFI Flag of Buffer 7 (w) */
    unsigned int NFI8:1;                    /**< \brief [8:8] Clear NFI Flag of Buffer 8 (w) */
    unsigned int NFI9:1;                    /**< \brief [9:9] Clear NFI Flag of Buffer 9 (w) */
    unsigned int NFI10:1;                   /**< \brief [10:10] Clear NFI Flag of Buffer 10 (w) */
    unsigned int NFI11:1;                   /**< \brief [11:11] Clear NFI Flag of Buffer 11 (w) */
    unsigned int NFI12:1;                   /**< \brief [12:12] Clear NFI Flag of Buffer 12 (w) */
    unsigned int NFI13:1;                   /**< \brief [13:13] Clear NFI Flag of Buffer 13 (w) */
    unsigned int NFI14:1;                   /**< \brief [14:14] Clear NFI Flag of Buffer 14 (w) */
    unsigned int NFI15:1;                   /**< \brief [15:15] Clear NFI Flag of Buffer 15 (w) */
    unsigned int NFI16:1;                   /**< \brief [16:16] Clear NFI Flag of Buffer 16 (w) */
    unsigned int NFI17:1;                   /**< \brief [17:17] Clear NFI Flag of Buffer 17 (w) */
    unsigned int NFI18:1;                   /**< \brief [18:18] Clear NFI Flag of Buffer 18 (w) */
    unsigned int NFI19:1;                   /**< \brief [19:19] Clear NFI Flag of Buffer 19 (w) */
    unsigned int NFI20:1;                   /**< \brief [20:20] Clear NFI Flag of Buffer 20 (w) */
    unsigned int NFI21:1;                   /**< \brief [21:21] Clear NFI Flag of Buffer 21 (w) */
    unsigned int NFI22:1;                   /**< \brief [22:22] Clear NFI Flag of Buffer 22 (w) */
    unsigned int NFI23:1;                   /**< \brief [23:23] Clear NFI Flag of Buffer 23 (w) */
    unsigned int NFI24:1;                   /**< \brief [24:24] Clear NFI Flag of Buffer 24 (w) */
    unsigned int NFI25:1;                   /**< \brief [25:25] Clear NFI Flag of Buffer 25 (w) */
    unsigned int NFI26:1;                   /**< \brief [26:26] Clear NFI Flag of Buffer 26 (w) */
    unsigned int NFI27:1;                   /**< \brief [27:27] Clear NFI Flag of Buffer 27 (w) */
    unsigned int NFI28:1;                   /**< \brief [28:28] Clear NFI Flag of Buffer 28 (w) */
    unsigned int NFI29:1;                   /**< \brief [29:29] Clear NFI Flag of Buffer 29 (w) */
    unsigned int NFI30:1;                   /**< \brief [30:30] Clear NFI Flag of Buffer 30 (w) */
    unsigned int NFI31:1;                   /**< \brief [31:31] Clear NFI Flag of Buffer 31 (w) */
} Ifx_PSI5_NFICLR_Bits;

/** \brief  NFI Overview Register */
typedef struct _Ifx_PSI5_NFIOV_Bits
{
    unsigned int NFI0:1;                    /**< \brief [0:0] NFI Flag of Buffer 0 (rh) */
    unsigned int NFI1:1;                    /**< \brief [1:1] NFI Flag of Buffer 1 (rh) */
    unsigned int NFI2:1;                    /**< \brief [2:2] NFI Flag of Buffer 2 (rh) */
    unsigned int NFI3:1;                    /**< \brief [3:3] NFI Flag of Buffer 3 (rh) */
    unsigned int NFI4:1;                    /**< \brief [4:4] NFI Flag of Buffer 4 (rh) */
    unsigned int NFI5:1;                    /**< \brief [5:5] NFI Flag of Buffer 5 (rh) */
    unsigned int NFI6:1;                    /**< \brief [6:6] NFI Flag of Buffer 6 (rh) */
    unsigned int NFI7:1;                    /**< \brief [7:7] NFI Flag of Buffer 7 (rh) */
    unsigned int NFI8:1;                    /**< \brief [8:8] NFI Flag of Buffer 8 (rh) */
    unsigned int NFI9:1;                    /**< \brief [9:9] NFI Flag of Buffer 9 (rh) */
    unsigned int NFI10:1;                   /**< \brief [10:10] NFI Flag of Buffer 10 (rh) */
    unsigned int NFI11:1;                   /**< \brief [11:11] NFI Flag of Buffer 11 (rh) */
    unsigned int NFI12:1;                   /**< \brief [12:12] NFI Flag of Buffer 12 (rh) */
    unsigned int NFI13:1;                   /**< \brief [13:13] NFI Flag of Buffer 13 (rh) */
    unsigned int NFI14:1;                   /**< \brief [14:14] NFI Flag of Buffer 14 (rh) */
    unsigned int NFI15:1;                   /**< \brief [15:15] NFI Flag of Buffer 15 (rh) */
    unsigned int NFI16:1;                   /**< \brief [16:16] NFI Flag of Buffer 16 (rh) */
    unsigned int NFI17:1;                   /**< \brief [17:17] NFI Flag of Buffer 17 (rh) */
    unsigned int NFI18:1;                   /**< \brief [18:18] NFI Flag of Buffer 18 (rh) */
    unsigned int NFI19:1;                   /**< \brief [19:19] NFI Flag of Buffer 19 (rh) */
    unsigned int NFI20:1;                   /**< \brief [20:20] NFI Flag of Buffer 20 (rh) */
    unsigned int NFI21:1;                   /**< \brief [21:21] NFI Flag of Buffer 21 (rh) */
    unsigned int NFI22:1;                   /**< \brief [22:22] NFI Flag of Buffer 22 (rh) */
    unsigned int NFI23:1;                   /**< \brief [23:23] NFI Flag of Buffer 23 (rh) */
    unsigned int NFI24:1;                   /**< \brief [24:24] NFI Flag of Buffer 24 (rh) */
    unsigned int NFI25:1;                   /**< \brief [25:25] NFI Flag of Buffer 25 (rh) */
    unsigned int NFI26:1;                   /**< \brief [26:26] NFI Flag of Buffer 26 (rh) */
    unsigned int NFI27:1;                   /**< \brief [27:27] NFI Flag of Buffer 27 (rh) */
    unsigned int NFI28:1;                   /**< \brief [28:28] NFI Flag of Buffer 28 (rh) */
    unsigned int NFI29:1;                   /**< \brief [29:29] NFI Flag of Buffer 29 (rh) */
    unsigned int NFI30:1;                   /**< \brief [30:30] NFI Flag of Buffer 30 (rh) */
    unsigned int NFI31:1;                   /**< \brief [31:31] NFI Flag of Buffer 31 (rh) */
} Ifx_PSI5_NFIOV_Bits;

/** \brief  NFIOV Set Register */
typedef struct _Ifx_PSI5_NFISET_Bits
{
    unsigned int NFI0:1;                    /**< \brief [0:0] Set NFI Flag of Buffer 0 (w) */
    unsigned int NFI1:1;                    /**< \brief [1:1] Set NFI Flag of Buffer 1 (w) */
    unsigned int NFI2:1;                    /**< \brief [2:2] Set NFI Flag of Buffer 2 (w) */
    unsigned int NFI3:1;                    /**< \brief [3:3] Set NFI Flag of Buffer 3 (w) */
    unsigned int NFI4:1;                    /**< \brief [4:4] Set NFI Flag of Buffer 4 (w) */
    unsigned int NFI5:1;                    /**< \brief [5:5] Set NFI Flag of Buffer 5 (w) */
    unsigned int NFI6:1;                    /**< \brief [6:6] Set NFI Flag of Buffer 6 (w) */
    unsigned int NFI7:1;                    /**< \brief [7:7] Set NFI Flag of Buffer 7 (w) */
    unsigned int NFI8:1;                    /**< \brief [8:8] Set NFI Flag of Buffer 8 (w) */
    unsigned int NFI9:1;                    /**< \brief [9:9] Set NFI Flag of Buffer 9 (w) */
    unsigned int NFI10:1;                   /**< \brief [10:10] Set NFI Flag of Buffer 10 (w) */
    unsigned int NFI11:1;                   /**< \brief [11:11] Set NFI Flag of Buffer 11 (w) */
    unsigned int NFI12:1;                   /**< \brief [12:12] Set NFI Flag of Buffer 12 (w) */
    unsigned int NFI13:1;                   /**< \brief [13:13] Set NFI Flag of Buffer 13 (w) */
    unsigned int NFI14:1;                   /**< \brief [14:14] Set NFI Flag of Buffer 14 (w) */
    unsigned int NFI15:1;                   /**< \brief [15:15] Set NFI Flag of Buffer 15 (w) */
    unsigned int NFI16:1;                   /**< \brief [16:16] Set NFI Flag of Buffer 16 (w) */
    unsigned int NFI17:1;                   /**< \brief [17:17] Set NFI Flag of Buffer 17 (w) */
    unsigned int NFI18:1;                   /**< \brief [18:18] Set NFI Flag of Buffer 18 (w) */
    unsigned int NFI19:1;                   /**< \brief [19:19] Set NFI Flag of Buffer 19 (w) */
    unsigned int NFI20:1;                   /**< \brief [20:20] Set NFI Flag of Buffer 20 (w) */
    unsigned int NFI21:1;                   /**< \brief [21:21] Set NFI Flag of Buffer 21 (w) */
    unsigned int NFI22:1;                   /**< \brief [22:22] Set NFI Flag of Buffer 22 (w) */
    unsigned int NFI23:1;                   /**< \brief [23:23] Set NFI Flag of Buffer 23 (w) */
    unsigned int NFI24:1;                   /**< \brief [24:24] Set NFI Flag of Buffer 24 (w) */
    unsigned int NFI25:1;                   /**< \brief [25:25] Set NFI Flag of Buffer 25 (w) */
    unsigned int NFI26:1;                   /**< \brief [26:26] Set NFI Flag of Buffer 26 (w) */
    unsigned int NFI27:1;                   /**< \brief [27:27] Set NFI Flag of Buffer 27 (w) */
    unsigned int NFI28:1;                   /**< \brief [28:28] Set NFI Flag of Buffer 28 (w) */
    unsigned int NFI29:1;                   /**< \brief [29:29] Set NFI Flag of Buffer 29 (w) */
    unsigned int NFI30:1;                   /**< \brief [30:30] Set NFI Flag of Buffer 30 (w) */
    unsigned int NFI31:1;                   /**< \brief [31:31] Set NFI Flag of Buffer 31 (w) */
} Ifx_PSI5_NFISET_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_PSI5_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_PSI5_OCS_Bits;

/** \brief  Receive Data FIFO */
typedef struct _Ifx_PSI5_RDF_Bits
{
    unsigned int RD:32;                     /**< \brief [31:0] RD (rh) */
} Ifx_PSI5_RDF_Bits;

/** \brief  RDIOV Clear Register */
typedef struct _Ifx_PSI5_RDICLR_Bits
{
    unsigned int RDI0:1;                    /**< \brief [0:0] Clear RDI Flag of Buffer 0 (w) */
    unsigned int RDI1:1;                    /**< \brief [1:1] Clear RDI Flag of Buffer 1 (w) */
    unsigned int RDI2:1;                    /**< \brief [2:2] Clear RDI Flag of Buffer 2 (w) */
    unsigned int RDI3:1;                    /**< \brief [3:3] Clear RDI Flag of Buffer 3 (w) */
    unsigned int RDI4:1;                    /**< \brief [4:4] Clear RDI Flag of Buffer 4 (w) */
    unsigned int RDI5:1;                    /**< \brief [5:5] Clear RDI Flag of Buffer 5 (w) */
    unsigned int RDI6:1;                    /**< \brief [6:6] Clear RDI Flag of Buffer 6 (w) */
    unsigned int RDI7:1;                    /**< \brief [7:7] Clear RDI Flag of Buffer 7 (w) */
    unsigned int RDI8:1;                    /**< \brief [8:8] Clear RDI Flag of Buffer 8 (w) */
    unsigned int RDI9:1;                    /**< \brief [9:9] Clear RDI Flag of Buffer 9 (w) */
    unsigned int RDI10:1;                   /**< \brief [10:10] Clear RDI Flag of Buffer 10 (w) */
    unsigned int RDI11:1;                   /**< \brief [11:11] Clear RDI Flag of Buffer 11 (w) */
    unsigned int RDI12:1;                   /**< \brief [12:12] Clear RDI Flag of Buffer 12 (w) */
    unsigned int RDI13:1;                   /**< \brief [13:13] Clear RDI Flag of Buffer 13 (w) */
    unsigned int RDI14:1;                   /**< \brief [14:14] Clear RDI Flag of Buffer 14 (w) */
    unsigned int RDI15:1;                   /**< \brief [15:15] Clear RDI Flag of Buffer 15 (w) */
    unsigned int RDI16:1;                   /**< \brief [16:16] Clear RDI Flag of Buffer 16 (w) */
    unsigned int RDI17:1;                   /**< \brief [17:17] Clear RDI Flag of Buffer 17 (w) */
    unsigned int RDI18:1;                   /**< \brief [18:18] Clear RDI Flag of Buffer 18 (w) */
    unsigned int RDI19:1;                   /**< \brief [19:19] Clear RDI Flag of Buffer 19 (w) */
    unsigned int RDI20:1;                   /**< \brief [20:20] Clear RDI Flag of Buffer 20 (w) */
    unsigned int RDI21:1;                   /**< \brief [21:21] Clear RDI Flag of Buffer 21 (w) */
    unsigned int RDI22:1;                   /**< \brief [22:22] Clear RDI Flag of Buffer 22 (w) */
    unsigned int RDI23:1;                   /**< \brief [23:23] Clear RDI Flag of Buffer 23 (w) */
    unsigned int RDI24:1;                   /**< \brief [24:24] Clear RDI Flag of Buffer 24 (w) */
    unsigned int RDI25:1;                   /**< \brief [25:25] Clear RDI Flag of Buffer 25 (w) */
    unsigned int RDI26:1;                   /**< \brief [26:26] Clear RDI Flag of Buffer 26 (w) */
    unsigned int RDI27:1;                   /**< \brief [27:27] Clear RDI Flag of Buffer 27 (w) */
    unsigned int RDI28:1;                   /**< \brief [28:28] Clear RDI Flag of Buffer 28 (w) */
    unsigned int RDI29:1;                   /**< \brief [29:29] Clear RDI Flag of Buffer 29 (w) */
    unsigned int RDI30:1;                   /**< \brief [30:30] Clear RDI Flag of Buffer 30 (w) */
    unsigned int RDI31:1;                   /**< \brief [31:31] Clear RDI Flag of Buffer 31 (w) */
} Ifx_PSI5_RDICLR_Bits;

/** \brief  RDI Overview Register */
typedef struct _Ifx_PSI5_RDIOV_Bits
{
    unsigned int RDI0:1;                    /**< \brief [0:0] RDI Flag of Buffer 0 (rh) */
    unsigned int RDI1:1;                    /**< \brief [1:1] RDI Flag of Buffer 1 (rh) */
    unsigned int RDI2:1;                    /**< \brief [2:2] RDI Flag of Buffer 2 (rh) */
    unsigned int RDI3:1;                    /**< \brief [3:3] RDI Flag of Buffer 3 (rh) */
    unsigned int RDI4:1;                    /**< \brief [4:4] RDI Flag of Buffer 4 (rh) */
    unsigned int RDI5:1;                    /**< \brief [5:5] RDI Flag of Buffer 5 (rh) */
    unsigned int RDI6:1;                    /**< \brief [6:6] RDI Flag of Buffer 6 (rh) */
    unsigned int RDI7:1;                    /**< \brief [7:7] RDI Flag of Buffer 7 (rh) */
    unsigned int RDI8:1;                    /**< \brief [8:8] RDI Flag of Buffer 8 (rh) */
    unsigned int RDI9:1;                    /**< \brief [9:9] RDI Flag of Buffer 9 (rh) */
    unsigned int RDI10:1;                   /**< \brief [10:10] RDI Flag of Buffer 10 (rh) */
    unsigned int RDI11:1;                   /**< \brief [11:11] RDI Flag of Buffer 11 (rh) */
    unsigned int RDI12:1;                   /**< \brief [12:12] RDI Flag of Buffer 12 (rh) */
    unsigned int RDI13:1;                   /**< \brief [13:13] RDI Flag of Buffer 13 (rh) */
    unsigned int RDI14:1;                   /**< \brief [14:14] RDI Flag of Buffer 14 (rh) */
    unsigned int RDI15:1;                   /**< \brief [15:15] RDI Flag of Buffer 15 (rh) */
    unsigned int RDI16:1;                   /**< \brief [16:16] RDI Flag of Buffer 16 (rh) */
    unsigned int RDI17:1;                   /**< \brief [17:17] RDI Flag of Buffer 17 (rh) */
    unsigned int RDI18:1;                   /**< \brief [18:18] RDI Flag of Buffer 18 (rh) */
    unsigned int RDI19:1;                   /**< \brief [19:19] RDI Flag of Buffer 19 (rh) */
    unsigned int RDI20:1;                   /**< \brief [20:20] RDI Flag of Buffer 20 (rh) */
    unsigned int RDI21:1;                   /**< \brief [21:21] RDI Flag of Buffer 21 (rh) */
    unsigned int RDI22:1;                   /**< \brief [22:22] RDI Flag of Buffer 22 (rh) */
    unsigned int RDI23:1;                   /**< \brief [23:23] RDI Flag of Buffer 23 (rh) */
    unsigned int RDI24:1;                   /**< \brief [24:24] RDI Flag of Buffer 24 (rh) */
    unsigned int RDI25:1;                   /**< \brief [25:25] RDI Flag of Buffer 25 (rh) */
    unsigned int RDI26:1;                   /**< \brief [26:26] RDI Flag of Buffer 26 (rh) */
    unsigned int RDI27:1;                   /**< \brief [27:27] RDI Flag of Buffer 27 (rh) */
    unsigned int RDI28:1;                   /**< \brief [28:28] RDI Flag of Buffer 28 (rh) */
    unsigned int RDI29:1;                   /**< \brief [29:29] RDI Flag of Buffer 29 (rh) */
    unsigned int RDI30:1;                   /**< \brief [30:30] RDI Flag of Buffer 30 (rh) */
    unsigned int RDI31:1;                   /**< \brief [31:31] RDI Flag of Buffer 31 (rh) */
} Ifx_PSI5_RDIOV_Bits;

/** \brief  RDIOV Set Register */
typedef struct _Ifx_PSI5_RDISET_Bits
{
    unsigned int RDI0:1;                    /**< \brief [0:0] Set RDI Flag of Buffer 0 (w) */
    unsigned int RDI1:1;                    /**< \brief [1:1] Set RDI Flag of Buffer 1 (w) */
    unsigned int RDI2:1;                    /**< \brief [2:2] Set RDI Flag of Buffer 2 (w) */
    unsigned int RDI3:1;                    /**< \brief [3:3] Set RDI Flag of Buffer 3 (w) */
    unsigned int RDI4:1;                    /**< \brief [4:4] Set RDI Flag of Buffer 4 (w) */
    unsigned int RDI5:1;                    /**< \brief [5:5] Set RDI Flag of Buffer 5 (w) */
    unsigned int RDI6:1;                    /**< \brief [6:6] Set RDI Flag of Buffer 6 (w) */
    unsigned int RDI7:1;                    /**< \brief [7:7] Set RDI Flag of Buffer 7 (w) */
    unsigned int RDI8:1;                    /**< \brief [8:8] Set RDI Flag of Buffer 8 (w) */
    unsigned int RDI9:1;                    /**< \brief [9:9] Set RDI Flag of Buffer 9 (w) */
    unsigned int RDI10:1;                   /**< \brief [10:10] Set RDI Flag of Buffer 10 (w) */
    unsigned int RDI11:1;                   /**< \brief [11:11] Set RDI Flag of Buffer 11 (w) */
    unsigned int RDI12:1;                   /**< \brief [12:12] Set RDI Flag of Buffer 12 (w) */
    unsigned int RDI13:1;                   /**< \brief [13:13] Set RDI Flag of Buffer 13 (w) */
    unsigned int RDI14:1;                   /**< \brief [14:14] Set RDI Flag of Buffer 14 (w) */
    unsigned int RDI15:1;                   /**< \brief [15:15] Set RDI Flag of Buffer 15 (w) */
    unsigned int RDI16:1;                   /**< \brief [16:16] Set RDI Flag of Buffer 16 (w) */
    unsigned int RDI17:1;                   /**< \brief [17:17] Set RDI Flag of Buffer 17 (w) */
    unsigned int RDI18:1;                   /**< \brief [18:18] Set RDI Flag of Buffer 18 (w) */
    unsigned int RDI19:1;                   /**< \brief [19:19] Set RDI Flag of Buffer 19 (w) */
    unsigned int RDI20:1;                   /**< \brief [20:20] Set RDI Flag of Buffer 20 (w) */
    unsigned int RDI21:1;                   /**< \brief [21:21] Set RDI Flag of Buffer 21 (w) */
    unsigned int RDI22:1;                   /**< \brief [22:22] Set RDI Flag of Buffer 22 (w) */
    unsigned int RDI23:1;                   /**< \brief [23:23] Set RDI Flag of Buffer 23 (w) */
    unsigned int RDI24:1;                   /**< \brief [24:24] Set RDI Flag of Buffer 24 (w) */
    unsigned int RDI25:1;                   /**< \brief [25:25] Set RDI Flag of Buffer 25 (w) */
    unsigned int RDI26:1;                   /**< \brief [26:26] Set RDI Flag of Buffer 26 (w) */
    unsigned int RDI27:1;                   /**< \brief [27:27] Set RDI Flag of Buffer 27 (w) */
    unsigned int RDI28:1;                   /**< \brief [28:28] Set RDI Flag of Buffer 28 (w) */
    unsigned int RDI29:1;                   /**< \brief [29:29] Set RDI Flag of Buffer 29 (w) */
    unsigned int RDI30:1;                   /**< \brief [30:30] Set RDI Flag of Buffer 30 (w) */
    unsigned int RDI31:1;                   /**< \brief [31:31] Set RDI Flag of Buffer 31 (w) */
} Ifx_PSI5_RDISET_Bits;

/** \brief  Receive Data Memory High */
typedef struct _Ifx_PSI5_RDM_H_Bits
{
    unsigned int TS:24;                     /**< \brief [23:0] Time Stamp (rh) */
    unsigned int SC:3;                      /**< \brief [26:24] Slot Counter (rh) */
    unsigned int TEI:1;                     /**< \brief [27:27] Time Slot Error Flag (rh) */
    unsigned int NBI:1;                     /**< \brief [28:28] Number of bits Error Flag (rh) */
    unsigned int MEI:1;                     /**< \brief [29:29] Error in Messaging Bits Flag (rh) */
    unsigned int NFI:1;                     /**< \brief [30:30] No Frame Received Flag (rh) */
    unsigned int RMI:1;                     /**< \brief [31:31] Receive Memory Overflow Flag (rh) */
} Ifx_PSI5_RDM_H_Bits;

/** \brief  Receive Data Memory Low */
typedef struct _Ifx_PSI5_RDM_L_Bits
{
    unsigned int CRCI:1;                    /**< \brief [0:0] CRC Error Flag (rh) */
    unsigned int CRC:3;                     /**< \brief [3:1] CRC (rh) */
    unsigned int RD:28;                     /**< \brief [31:4] RD (rh) */
} Ifx_PSI5_RDM_L_Bits;

/** \brief  Receive FIFO Control Register */
typedef struct _Ifx_PSI5_RFC_Bits
{
    unsigned int REP:6;                     /**< \brief [5:0] FIFO Read Pointer (r) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int WRP:6;                     /**< \brief [13:8] FIFO/Ring Buffer Write Pointer (r) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int FWL:5;                     /**< \brief [20:16] FIFO Warning Level (rw) */
    unsigned int reserved_21:8;             /**< \brief \internal Reserved */
    unsigned int WRAP:1;                    /**< \brief [29:29] Write Pointer WRAP Indicator (r) */
    unsigned int FRQ:1;                     /**< \brief [30:30] Flush Request (r) */
    unsigned int FLU:1;                     /**< \brief [31:31] Flush (w) */
} Ifx_PSI5_RFC_Bits;

/** \brief  RMIOV Clear Register */
typedef struct _Ifx_PSI5_RMICLR_Bits
{
    unsigned int RMI0:1;                    /**< \brief [0:0] Clear RMI Flag of Buffer 0 (w) */
    unsigned int RMI1:1;                    /**< \brief [1:1] Clear RMI Flag of Buffer 1 (w) */
    unsigned int RMI2:1;                    /**< \brief [2:2] Clear RMI Flag of Buffer 2 (w) */
    unsigned int RMI3:1;                    /**< \brief [3:3] Clear RMI Flag of Buffer 3 (w) */
    unsigned int RMI4:1;                    /**< \brief [4:4] Clear RMI Flag of Buffer 4 (w) */
    unsigned int RMI5:1;                    /**< \brief [5:5] Clear RMI Flag of Buffer 5 (w) */
    unsigned int RMI6:1;                    /**< \brief [6:6] Clear RMI Flag of Buffer 6 (w) */
    unsigned int RMI7:1;                    /**< \brief [7:7] Clear RMI Flag of Buffer 7 (w) */
    unsigned int RMI8:1;                    /**< \brief [8:8] Clear RMI Flag of Buffer 8 (w) */
    unsigned int RMI9:1;                    /**< \brief [9:9] Clear RMI Flag of Buffer 9 (w) */
    unsigned int RMI10:1;                   /**< \brief [10:10] Clear RMI Flag of Buffer 10 (w) */
    unsigned int RMI11:1;                   /**< \brief [11:11] Clear RMI Flag of Buffer 11 (w) */
    unsigned int RMI12:1;                   /**< \brief [12:12] Clear RMI Flag of Buffer 12 (w) */
    unsigned int RMI13:1;                   /**< \brief [13:13] Clear RMI Flag of Buffer 13 (w) */
    unsigned int RMI14:1;                   /**< \brief [14:14] Clear RMI Flag of Buffer 14 (w) */
    unsigned int RMI15:1;                   /**< \brief [15:15] Clear RMI Flag of Buffer 15 (w) */
    unsigned int RMI16:1;                   /**< \brief [16:16] Clear RMI Flag of Buffer 16 (w) */
    unsigned int RMI17:1;                   /**< \brief [17:17] Clear RMI Flag of Buffer 17 (w) */
    unsigned int RMI18:1;                   /**< \brief [18:18] Clear RMI Flag of Buffer 18 (w) */
    unsigned int RMI19:1;                   /**< \brief [19:19] Clear RMI Flag of Buffer 19 (w) */
    unsigned int RMI20:1;                   /**< \brief [20:20] Clear RMI Flag of Buffer 20 (w) */
    unsigned int RMI21:1;                   /**< \brief [21:21] Clear RMI Flag of Buffer 21 (w) */
    unsigned int RMI22:1;                   /**< \brief [22:22] Clear RMI Flag of Buffer 22 (w) */
    unsigned int RMI23:1;                   /**< \brief [23:23] Clear RMI Flag of Buffer 23 (w) */
    unsigned int RMI24:1;                   /**< \brief [24:24] Clear RMI Flag of Buffer 24 (w) */
    unsigned int RMI25:1;                   /**< \brief [25:25] Clear RMI Flag of Buffer 25 (w) */
    unsigned int RMI26:1;                   /**< \brief [26:26] Clear RMI Flag of Buffer 26 (w) */
    unsigned int RMI27:1;                   /**< \brief [27:27] Clear RMI Flag of Buffer 27 (w) */
    unsigned int RMI28:1;                   /**< \brief [28:28] Clear RMI Flag of Buffer 28 (w) */
    unsigned int RMI29:1;                   /**< \brief [29:29] Clear RMI Flag of Buffer 29 (w) */
    unsigned int RMI30:1;                   /**< \brief [30:30] Clear RMI Flag of Buffer 30 (w) */
    unsigned int RMI31:1;                   /**< \brief [31:31] Clear RMI Flag of Buffer 31 (w) */
} Ifx_PSI5_RMICLR_Bits;

/** \brief  RMI Overview Register */
typedef struct _Ifx_PSI5_RMIOV_Bits
{
    unsigned int RMI0:1;                    /**< \brief [0:0] RMI Flag of Buffer 0 (rh) */
    unsigned int RMI1:1;                    /**< \brief [1:1] RMI Flag of Buffer 1 (rh) */
    unsigned int RMI2:1;                    /**< \brief [2:2] RMI Flag of Buffer 2 (rh) */
    unsigned int RMI3:1;                    /**< \brief [3:3] RMI Flag of Buffer 3 (rh) */
    unsigned int RMI4:1;                    /**< \brief [4:4] RMI Flag of Buffer 4 (rh) */
    unsigned int RMI5:1;                    /**< \brief [5:5] RMI Flag of Buffer 5 (rh) */
    unsigned int RMI6:1;                    /**< \brief [6:6] RMI Flag of Buffer 6 (rh) */
    unsigned int RMI7:1;                    /**< \brief [7:7] RMI Flag of Buffer 7 (rh) */
    unsigned int RMI8:1;                    /**< \brief [8:8] RMI Flag of Buffer 8 (rh) */
    unsigned int RMI9:1;                    /**< \brief [9:9] RMI Flag of Buffer 9 (rh) */
    unsigned int RMI10:1;                   /**< \brief [10:10] RMI Flag of Buffer 10 (rh) */
    unsigned int RMI11:1;                   /**< \brief [11:11] RMI Flag of Buffer 11 (rh) */
    unsigned int RMI12:1;                   /**< \brief [12:12] RMI Flag of Buffer 12 (rh) */
    unsigned int RMI13:1;                   /**< \brief [13:13] RMI Flag of Buffer 13 (rh) */
    unsigned int RMI14:1;                   /**< \brief [14:14] RMI Flag of Buffer 14 (rh) */
    unsigned int RMI15:1;                   /**< \brief [15:15] RMI Flag of Buffer 15 (rh) */
    unsigned int RMI16:1;                   /**< \brief [16:16] RMI Flag of Buffer 16 (rh) */
    unsigned int RMI17:1;                   /**< \brief [17:17] RMI Flag of Buffer 17 (rh) */
    unsigned int RMI18:1;                   /**< \brief [18:18] RMI Flag of Buffer 18 (rh) */
    unsigned int RMI19:1;                   /**< \brief [19:19] RMI Flag of Buffer 19 (rh) */
    unsigned int RMI20:1;                   /**< \brief [20:20] RMI Flag of Buffer 20 (rh) */
    unsigned int RMI21:1;                   /**< \brief [21:21] RMI Flag of Buffer 21 (rh) */
    unsigned int RMI22:1;                   /**< \brief [22:22] RMI Flag of Buffer 22 (rh) */
    unsigned int RMI23:1;                   /**< \brief [23:23] RMI Flag of Buffer 23 (rh) */
    unsigned int RMI24:1;                   /**< \brief [24:24] RMI Flag of Buffer 24 (rh) */
    unsigned int RMI25:1;                   /**< \brief [25:25] RMI Flag of Buffer 25 (rh) */
    unsigned int RMI26:1;                   /**< \brief [26:26] RMI Flag of Buffer 26 (rh) */
    unsigned int RMI27:1;                   /**< \brief [27:27] RMI Flag of Buffer 27 (rh) */
    unsigned int RMI28:1;                   /**< \brief [28:28] RMI Flag of Buffer 28 (rh) */
    unsigned int RMI29:1;                   /**< \brief [29:29] RMI Flag of Buffer 29 (rh) */
    unsigned int RMI30:1;                   /**< \brief [30:30] RMI Flag of Buffer 30 (rh) */
    unsigned int RMI31:1;                   /**< \brief [31:31] RMI Flag of Buffer 31 (rh) */
} Ifx_PSI5_RMIOV_Bits;

/** \brief  RMIOV Set Register */
typedef struct _Ifx_PSI5_RMISET_Bits
{
    unsigned int RMI0:1;                    /**< \brief [0:0] Set RMI Flag of Buffer 0 (w) */
    unsigned int RMI1:1;                    /**< \brief [1:1] Set RMI Flag of Buffer 1 (w) */
    unsigned int RMI2:1;                    /**< \brief [2:2] Set RMI Flag of Buffer 2 (w) */
    unsigned int RMI3:1;                    /**< \brief [3:3] Set RMI Flag of Buffer 3 (w) */
    unsigned int RMI4:1;                    /**< \brief [4:4] Set RMI Flag of Buffer 4 (w) */
    unsigned int RMI5:1;                    /**< \brief [5:5] Set RMI Flag of Buffer 5 (w) */
    unsigned int RMI6:1;                    /**< \brief [6:6] Set RMI Flag of Buffer 6 (w) */
    unsigned int RMI7:1;                    /**< \brief [7:7] Set RMI Flag of Buffer 7 (w) */
    unsigned int RMI8:1;                    /**< \brief [8:8] Set RMI Flag of Buffer 8 (w) */
    unsigned int RMI9:1;                    /**< \brief [9:9] Set RMI Flag of Buffer 9 (w) */
    unsigned int RMI10:1;                   /**< \brief [10:10] Set RMI Flag of Buffer 10 (w) */
    unsigned int RMI11:1;                   /**< \brief [11:11] Set RMI Flag of Buffer 11 (w) */
    unsigned int RMI12:1;                   /**< \brief [12:12] Set RMI Flag of Buffer 12 (w) */
    unsigned int RMI13:1;                   /**< \brief [13:13] Set RMI Flag of Buffer 13 (w) */
    unsigned int RMI14:1;                   /**< \brief [14:14] Set RMI Flag of Buffer 14 (w) */
    unsigned int RMI15:1;                   /**< \brief [15:15] Set RMI Flag of Buffer 15 (w) */
    unsigned int RMI16:1;                   /**< \brief [16:16] Set RMI Flag of Buffer 16 (w) */
    unsigned int RMI17:1;                   /**< \brief [17:17] Set RMI Flag of Buffer 17 (w) */
    unsigned int RMI18:1;                   /**< \brief [18:18] Set RMI Flag of Buffer 18 (w) */
    unsigned int RMI19:1;                   /**< \brief [19:19] Set RMI Flag of Buffer 19 (w) */
    unsigned int RMI20:1;                   /**< \brief [20:20] Set RMI Flag of Buffer 20 (w) */
    unsigned int RMI21:1;                   /**< \brief [21:21] Set RMI Flag of Buffer 21 (w) */
    unsigned int RMI22:1;                   /**< \brief [22:22] Set RMI Flag of Buffer 22 (w) */
    unsigned int RMI23:1;                   /**< \brief [23:23] Set RMI Flag of Buffer 23 (w) */
    unsigned int RMI24:1;                   /**< \brief [24:24] Set RMI Flag of Buffer 24 (w) */
    unsigned int RMI25:1;                   /**< \brief [25:25] Set RMI Flag of Buffer 25 (w) */
    unsigned int RMI26:1;                   /**< \brief [26:26] Set RMI Flag of Buffer 26 (w) */
    unsigned int RMI27:1;                   /**< \brief [27:27] Set RMI Flag of Buffer 27 (w) */
    unsigned int RMI28:1;                   /**< \brief [28:28] Set RMI Flag of Buffer 28 (w) */
    unsigned int RMI29:1;                   /**< \brief [29:29] Set RMI Flag of Buffer 29 (w) */
    unsigned int RMI30:1;                   /**< \brief [30:30] Set RMI Flag of Buffer 30 (w) */
    unsigned int RMI31:1;                   /**< \brief [31:31] Set RMI Flag of Buffer 31 (w) */
} Ifx_PSI5_RMISET_Bits;

/** \brief  RSIOV Clear Register */
typedef struct _Ifx_PSI5_RSICLR_Bits
{
    unsigned int RSI0:1;                    /**< \brief [0:0] Clear RSI Flag of Buffer 0 (w) */
    unsigned int RSI1:1;                    /**< \brief [1:1] Clear RSI Flag of Buffer 1 (w) */
    unsigned int RSI2:1;                    /**< \brief [2:2] Clear RSI Flag of Buffer 2 (w) */
    unsigned int RSI3:1;                    /**< \brief [3:3] Clear RSI Flag of Buffer 3 (w) */
    unsigned int RSI4:1;                    /**< \brief [4:4] Clear RSI Flag of Buffer 4 (w) */
    unsigned int RSI5:1;                    /**< \brief [5:5] Clear RSI Flag of Buffer 5 (w) */
    unsigned int RSI6:1;                    /**< \brief [6:6] Clear RSI Flag of Buffer 6 (w) */
    unsigned int RSI7:1;                    /**< \brief [7:7] Clear RSI Flag of Buffer 7 (w) */
    unsigned int RSI8:1;                    /**< \brief [8:8] Clear RSI Flag of Buffer 8 (w) */
    unsigned int RSI9:1;                    /**< \brief [9:9] Clear RSI Flag of Buffer 9 (w) */
    unsigned int RSI10:1;                   /**< \brief [10:10] Clear RSI Flag of Buffer 10 (w) */
    unsigned int RSI11:1;                   /**< \brief [11:11] Clear RSI Flag of Buffer 11 (w) */
    unsigned int RSI12:1;                   /**< \brief [12:12] Clear RSI Flag of Buffer 12 (w) */
    unsigned int RSI13:1;                   /**< \brief [13:13] Clear RSI Flag of Buffer 13 (w) */
    unsigned int RSI14:1;                   /**< \brief [14:14] Clear RSI Flag of Buffer 14 (w) */
    unsigned int RSI15:1;                   /**< \brief [15:15] Clear RSI Flag of Buffer 15 (w) */
    unsigned int RSI16:1;                   /**< \brief [16:16] Clear RSI Flag of Buffer 16 (w) */
    unsigned int RSI17:1;                   /**< \brief [17:17] Clear RSI Flag of Buffer 17 (w) */
    unsigned int RSI18:1;                   /**< \brief [18:18] Clear RSI Flag of Buffer 18 (w) */
    unsigned int RSI19:1;                   /**< \brief [19:19] Clear RSI Flag of Buffer 19 (w) */
    unsigned int RSI20:1;                   /**< \brief [20:20] Clear RSI Flag of Buffer 20 (w) */
    unsigned int RSI21:1;                   /**< \brief [21:21] Clear RSI Flag of Buffer 21 (w) */
    unsigned int RSI22:1;                   /**< \brief [22:22] Clear RSI Flag of Buffer 22 (w) */
    unsigned int RSI23:1;                   /**< \brief [23:23] Clear RSI Flag of Buffer 23 (w) */
    unsigned int RSI24:1;                   /**< \brief [24:24] Clear RSI Flag of Buffer 24 (w) */
    unsigned int RSI25:1;                   /**< \brief [25:25] Clear RSI Flag of Buffer 25 (w) */
    unsigned int RSI26:1;                   /**< \brief [26:26] Clear RSI Flag of Buffer 26 (w) */
    unsigned int RSI27:1;                   /**< \brief [27:27] Clear RSI Flag of Buffer 27 (w) */
    unsigned int RSI28:1;                   /**< \brief [28:28] Clear RSI Flag of Buffer 28 (w) */
    unsigned int RSI29:1;                   /**< \brief [29:29] Clear RSI Flag of Buffer 29 (w) */
    unsigned int RSI30:1;                   /**< \brief [30:30] Clear RSI Flag of Buffer 30 (w) */
    unsigned int RSI31:1;                   /**< \brief [31:31] Clear RSI Flag of Buffer 31 (w) */
} Ifx_PSI5_RSICLR_Bits;

/** \brief  RSI Overview Register */
typedef struct _Ifx_PSI5_RSIOV_Bits
{
    unsigned int RSI0:1;                    /**< \brief [0:0] RSI Flag of Buffer 0 (rh) */
    unsigned int RSI1:1;                    /**< \brief [1:1] RSI Flag of Buffer 1 (rh) */
    unsigned int RSI2:1;                    /**< \brief [2:2] RSI Flag of Buffer 2 (rh) */
    unsigned int RSI3:1;                    /**< \brief [3:3] RSI Flag of Buffer 3 (rh) */
    unsigned int RSI4:1;                    /**< \brief [4:4] RSI Flag of Buffer 4 (rh) */
    unsigned int RSI5:1;                    /**< \brief [5:5] RSI Flag of Buffer 5 (rh) */
    unsigned int RSI6:1;                    /**< \brief [6:6] RSI Flag of Buffer 6 (rh) */
    unsigned int RSI7:1;                    /**< \brief [7:7] RSI Flag of Buffer 7 (rh) */
    unsigned int RSI8:1;                    /**< \brief [8:8] RSI Flag of Buffer 8 (rh) */
    unsigned int RSI9:1;                    /**< \brief [9:9] RSI Flag of Buffer 9 (rh) */
    unsigned int RSI10:1;                   /**< \brief [10:10] RSI Flag of Buffer 10 (rh) */
    unsigned int RSI11:1;                   /**< \brief [11:11] RSI Flag of Buffer 11 (rh) */
    unsigned int RSI12:1;                   /**< \brief [12:12] RSI Flag of Buffer 12 (rh) */
    unsigned int RSI13:1;                   /**< \brief [13:13] RSI Flag of Buffer 13 (rh) */
    unsigned int RSI14:1;                   /**< \brief [14:14] RSI Flag of Buffer 14 (rh) */
    unsigned int RSI15:1;                   /**< \brief [15:15] RSI Flag of Buffer 15 (rh) */
    unsigned int RSI16:1;                   /**< \brief [16:16] RSI Flag of Buffer 16 (rh) */
    unsigned int RSI17:1;                   /**< \brief [17:17] RSI Flag of Buffer 17 (rh) */
    unsigned int RSI18:1;                   /**< \brief [18:18] RSI Flag of Buffer 18 (rh) */
    unsigned int RSI19:1;                   /**< \brief [19:19] RSI Flag of Buffer 19 (rh) */
    unsigned int RSI20:1;                   /**< \brief [20:20] RSI Flag of Buffer 20 (rh) */
    unsigned int RSI21:1;                   /**< \brief [21:21] RSI Flag of Buffer 21 (rh) */
    unsigned int RSI22:1;                   /**< \brief [22:22] RSI Flag of Buffer 22 (rh) */
    unsigned int RSI23:1;                   /**< \brief [23:23] RSI Flag of Buffer 23 (rh) */
    unsigned int RSI24:1;                   /**< \brief [24:24] RSI Flag of Buffer 24 (rh) */
    unsigned int RSI25:1;                   /**< \brief [25:25] RSI Flag of Buffer 25 (rh) */
    unsigned int RSI26:1;                   /**< \brief [26:26] RSI Flag of Buffer 26 (rh) */
    unsigned int RSI27:1;                   /**< \brief [27:27] RSI Flag of Buffer 27 (rh) */
    unsigned int RSI28:1;                   /**< \brief [28:28] RSI Flag of Buffer 28 (rh) */
    unsigned int RSI29:1;                   /**< \brief [29:29] RSI Flag of Buffer 29 (rh) */
    unsigned int RSI30:1;                   /**< \brief [30:30] RSI Flag of Buffer 30 (rh) */
    unsigned int RSI31:1;                   /**< \brief [31:31] RSI Flag of Buffer 31 (rh) */
} Ifx_PSI5_RSIOV_Bits;

/** \brief  RSIOV Set Register */
typedef struct _Ifx_PSI5_RSISET_Bits
{
    unsigned int RSI0:1;                    /**< \brief [0:0] Set RSI Flag of Buffer 0 (w) */
    unsigned int RSI1:1;                    /**< \brief [1:1] Set RSI Flag of Buffer 1 (w) */
    unsigned int RSI2:1;                    /**< \brief [2:2] Set RSI Flag of Buffer 2 (w) */
    unsigned int RSI3:1;                    /**< \brief [3:3] Set RSI Flag of Buffer 3 (w) */
    unsigned int RSI4:1;                    /**< \brief [4:4] Set RSI Flag of Buffer 4 (w) */
    unsigned int RSI5:1;                    /**< \brief [5:5] Set RSI Flag of Buffer 5 (w) */
    unsigned int RSI6:1;                    /**< \brief [6:6] Set RSI Flag of Buffer 6 (w) */
    unsigned int RSI7:1;                    /**< \brief [7:7] Set RSI Flag of Buffer 7 (w) */
    unsigned int RSI8:1;                    /**< \brief [8:8] Set RSI Flag of Buffer 8 (w) */
    unsigned int RSI9:1;                    /**< \brief [9:9] Set RSI Flag of Buffer 9 (w) */
    unsigned int RSI10:1;                   /**< \brief [10:10] Set RSI Flag of Buffer 10 (w) */
    unsigned int RSI11:1;                   /**< \brief [11:11] Set RSI Flag of Buffer 11 (w) */
    unsigned int RSI12:1;                   /**< \brief [12:12] Set RSI Flag of Buffer 12 (w) */
    unsigned int RSI13:1;                   /**< \brief [13:13] Set RSI Flag of Buffer 13 (w) */
    unsigned int RSI14:1;                   /**< \brief [14:14] Set RSI Flag of Buffer 14 (w) */
    unsigned int RSI15:1;                   /**< \brief [15:15] Set RSI Flag of Buffer 15 (w) */
    unsigned int RSI16:1;                   /**< \brief [16:16] Set RSI Flag of Buffer 16 (w) */
    unsigned int RSI17:1;                   /**< \brief [17:17] Set RSI Flag of Buffer 17 (w) */
    unsigned int RSI18:1;                   /**< \brief [18:18] Set RSI Flag of Buffer 18 (w) */
    unsigned int RSI19:1;                   /**< \brief [19:19] Set RSI Flag of Buffer 19 (w) */
    unsigned int RSI20:1;                   /**< \brief [20:20] Set RSI Flag of Buffer 20 (w) */
    unsigned int RSI21:1;                   /**< \brief [21:21] Set RSI Flag of Buffer 21 (w) */
    unsigned int RSI22:1;                   /**< \brief [22:22] Set RSI Flag of Buffer 22 (w) */
    unsigned int RSI23:1;                   /**< \brief [23:23] Set RSI Flag of Buffer 23 (w) */
    unsigned int RSI24:1;                   /**< \brief [24:24] Set RSI Flag of Buffer 24 (w) */
    unsigned int RSI25:1;                   /**< \brief [25:25] Set RSI Flag of Buffer 25 (w) */
    unsigned int RSI26:1;                   /**< \brief [26:26] Set RSI Flag of Buffer 26 (w) */
    unsigned int RSI27:1;                   /**< \brief [27:27] Set RSI Flag of Buffer 27 (w) */
    unsigned int RSI28:1;                   /**< \brief [28:28] Set RSI Flag of Buffer 28 (w) */
    unsigned int RSI29:1;                   /**< \brief [29:29] Set RSI Flag of Buffer 29 (w) */
    unsigned int RSI30:1;                   /**< \brief [30:30] Set RSI Flag of Buffer 30 (w) */
    unsigned int RSI31:1;                   /**< \brief [31:31] Set RSI Flag of Buffer 31 (w) */
} Ifx_PSI5_RSISET_Bits;

/** \brief  TEIOV Clear Register */
typedef struct _Ifx_PSI5_TEICLR_Bits
{
    unsigned int TEI0:1;                    /**< \brief [0:0] Clear TEI Flag of Buffer 0 (w) */
    unsigned int TEI1:1;                    /**< \brief [1:1] Clear TEI Flag of Buffer 1 (w) */
    unsigned int TEI2:1;                    /**< \brief [2:2] Clear TEI Flag of Buffer 2 (w) */
    unsigned int TEI3:1;                    /**< \brief [3:3] Clear TEI Flag of Buffer 3 (w) */
    unsigned int TEI4:1;                    /**< \brief [4:4] Clear TEI Flag of Buffer 4 (w) */
    unsigned int TEI5:1;                    /**< \brief [5:5] Clear TEI Flag of Buffer 5 (w) */
    unsigned int TEI6:1;                    /**< \brief [6:6] Clear TEI Flag of Buffer 6 (w) */
    unsigned int TEI7:1;                    /**< \brief [7:7] Clear TEI Flag of Buffer 7 (w) */
    unsigned int TEI8:1;                    /**< \brief [8:8] Clear TEI Flag of Buffer 8 (w) */
    unsigned int TEI9:1;                    /**< \brief [9:9] Clear TEI Flag of Buffer 9 (w) */
    unsigned int TEI10:1;                   /**< \brief [10:10] Clear TEI Flag of Buffer 10 (w) */
    unsigned int TEI11:1;                   /**< \brief [11:11] Clear TEI Flag of Buffer 11 (w) */
    unsigned int TEI12:1;                   /**< \brief [12:12] Clear TEI Flag of Buffer 12 (w) */
    unsigned int TEI13:1;                   /**< \brief [13:13] Clear TEI Flag of Buffer 13 (w) */
    unsigned int TEI14:1;                   /**< \brief [14:14] Clear TEI Flag of Buffer 14 (w) */
    unsigned int TEI15:1;                   /**< \brief [15:15] Clear TEI Flag of Buffer 15 (w) */
    unsigned int TEI16:1;                   /**< \brief [16:16] Clear TEI Flag of Buffer 16 (w) */
    unsigned int TEI17:1;                   /**< \brief [17:17] Clear TEI Flag of Buffer 17 (w) */
    unsigned int TEI18:1;                   /**< \brief [18:18] Clear TEI Flag of Buffer 18 (w) */
    unsigned int TEI19:1;                   /**< \brief [19:19] Clear TEI Flag of Buffer 19 (w) */
    unsigned int TEI20:1;                   /**< \brief [20:20] Clear TEI Flag of Buffer 20 (w) */
    unsigned int TEI21:1;                   /**< \brief [21:21] Clear TEI Flag of Buffer 21 (w) */
    unsigned int TEI22:1;                   /**< \brief [22:22] Clear TEI Flag of Buffer 22 (w) */
    unsigned int TEI23:1;                   /**< \brief [23:23] Clear TEI Flag of Buffer 23 (w) */
    unsigned int TEI24:1;                   /**< \brief [24:24] Clear TEI Flag of Buffer 24 (w) */
    unsigned int TEI25:1;                   /**< \brief [25:25] Clear TEI Flag of Buffer 25 (w) */
    unsigned int TEI26:1;                   /**< \brief [26:26] Clear TEI Flag of Buffer 26 (w) */
    unsigned int TEI27:1;                   /**< \brief [27:27] Clear TEI Flag of Buffer 27 (w) */
    unsigned int TEI28:1;                   /**< \brief [28:28] Clear TEI Flag of Buffer 28 (w) */
    unsigned int TEI29:1;                   /**< \brief [29:29] Clear TEI Flag of Buffer 29 (w) */
    unsigned int TEI30:1;                   /**< \brief [30:30] Clear TEI Flag of Buffer 30 (w) */
    unsigned int TEI31:1;                   /**< \brief [31:31] Clear TEI Flag of Buffer 31 (w) */
} Ifx_PSI5_TEICLR_Bits;

/** \brief  TEI Overview Register */
typedef struct _Ifx_PSI5_TEIOV_Bits
{
    unsigned int TEI0:1;                    /**< \brief [0:0] TEI Flag of Buffer 0 (rh) */
    unsigned int TEI1:1;                    /**< \brief [1:1] TEI Flag of Buffer 1 (rh) */
    unsigned int TEI2:1;                    /**< \brief [2:2] TEI Flag of Buffer 2 (rh) */
    unsigned int TEI3:1;                    /**< \brief [3:3] TEI Flag of Buffer 3 (rh) */
    unsigned int TEI4:1;                    /**< \brief [4:4] TEI Flag of Buffer 4 (rh) */
    unsigned int TEI5:1;                    /**< \brief [5:5] TEI Flag of Buffer 5 (rh) */
    unsigned int TEI6:1;                    /**< \brief [6:6] TEI Flag of Buffer 6 (rh) */
    unsigned int TEI7:1;                    /**< \brief [7:7] TEI Flag of Buffer 7 (rh) */
    unsigned int TEI8:1;                    /**< \brief [8:8] TEI Flag of Buffer 8 (rh) */
    unsigned int TEI9:1;                    /**< \brief [9:9] TEI Flag of Buffer 9 (rh) */
    unsigned int TEI10:1;                   /**< \brief [10:10] TEI Flag of Buffer 10 (rh) */
    unsigned int TEI11:1;                   /**< \brief [11:11] TEI Flag of Buffer 11 (rh) */
    unsigned int TEI12:1;                   /**< \brief [12:12] TEI Flag of Buffer 12 (rh) */
    unsigned int TEI13:1;                   /**< \brief [13:13] TEI Flag of Buffer 13 (rh) */
    unsigned int TEI14:1;                   /**< \brief [14:14] TEI Flag of Buffer 14 (rh) */
    unsigned int TEI15:1;                   /**< \brief [15:15] TEI Flag of Buffer 15 (rh) */
    unsigned int TEI16:1;                   /**< \brief [16:16] TEI Flag of Buffer 16 (rh) */
    unsigned int TEI17:1;                   /**< \brief [17:17] TEI Flag of Buffer 17 (rh) */
    unsigned int TEI18:1;                   /**< \brief [18:18] TEI Flag of Buffer 18 (rh) */
    unsigned int TEI19:1;                   /**< \brief [19:19] TEI Flag of Buffer 19 (rh) */
    unsigned int TEI20:1;                   /**< \brief [20:20] TEI Flag of Buffer 20 (rh) */
    unsigned int TEI21:1;                   /**< \brief [21:21] TEI Flag of Buffer 21 (rh) */
    unsigned int TEI22:1;                   /**< \brief [22:22] TEI Flag of Buffer 22 (rh) */
    unsigned int TEI23:1;                   /**< \brief [23:23] TEI Flag of Buffer 23 (rh) */
    unsigned int TEI24:1;                   /**< \brief [24:24] TEI Flag of Buffer 24 (rh) */
    unsigned int TEI25:1;                   /**< \brief [25:25] TEI Flag of Buffer 25 (rh) */
    unsigned int TEI26:1;                   /**< \brief [26:26] TEI Flag of Buffer 26 (rh) */
    unsigned int TEI27:1;                   /**< \brief [27:27] TEI Flag of Buffer 27 (rh) */
    unsigned int TEI28:1;                   /**< \brief [28:28] TEI Flag of Buffer 28 (rh) */
    unsigned int TEI29:1;                   /**< \brief [29:29] TEI Flag of Buffer 29 (rh) */
    unsigned int TEI30:1;                   /**< \brief [30:30] TEI Flag of Buffer 30 (rh) */
    unsigned int TEI31:1;                   /**< \brief [31:31] TEI Flag of Buffer 31 (rh) */
} Ifx_PSI5_TEIOV_Bits;

/** \brief  TEIOV Set Register */
typedef struct _Ifx_PSI5_TEISET_Bits
{
    unsigned int TEI0:1;                    /**< \brief [0:0] Set TEI Flag of Buffer 0 (w) */
    unsigned int TEI1:1;                    /**< \brief [1:1] Set TEI Flag of Buffer 1 (w) */
    unsigned int TEI2:1;                    /**< \brief [2:2] Set TEI Flag of Buffer 2 (w) */
    unsigned int TEI3:1;                    /**< \brief [3:3] Set TEI Flag of Buffer 3 (w) */
    unsigned int TEI4:1;                    /**< \brief [4:4] Set TEI Flag of Buffer 4 (w) */
    unsigned int TEI5:1;                    /**< \brief [5:5] Set TEI Flag of Buffer 5 (w) */
    unsigned int TEI6:1;                    /**< \brief [6:6] Set TEI Flag of Buffer 6 (w) */
    unsigned int TEI7:1;                    /**< \brief [7:7] Set TEI Flag of Buffer 7 (w) */
    unsigned int TEI8:1;                    /**< \brief [8:8] Set TEI Flag of Buffer 8 (w) */
    unsigned int TEI9:1;                    /**< \brief [9:9] Set TEI Flag of Buffer 9 (w) */
    unsigned int TEI10:1;                   /**< \brief [10:10] Set TEI Flag of Buffer 10 (w) */
    unsigned int TEI11:1;                   /**< \brief [11:11] Set TEI Flag of Buffer 11 (w) */
    unsigned int TEI12:1;                   /**< \brief [12:12] Set TEI Flag of Buffer 12 (w) */
    unsigned int TEI13:1;                   /**< \brief [13:13] Set TEI Flag of Buffer 13 (w) */
    unsigned int TEI14:1;                   /**< \brief [14:14] Set TEI Flag of Buffer 14 (w) */
    unsigned int TEI15:1;                   /**< \brief [15:15] Set TEI Flag of Buffer 15 (w) */
    unsigned int TEI16:1;                   /**< \brief [16:16] Set TEI Flag of Buffer 16 (w) */
    unsigned int TEI17:1;                   /**< \brief [17:17] Set TEI Flag of Buffer 17 (w) */
    unsigned int TEI18:1;                   /**< \brief [18:18] Set TEI Flag of Buffer 18 (w) */
    unsigned int TEI19:1;                   /**< \brief [19:19] Set TEI Flag of Buffer 19 (w) */
    unsigned int TEI20:1;                   /**< \brief [20:20] Set TEI Flag of Buffer 20 (w) */
    unsigned int TEI21:1;                   /**< \brief [21:21] Set TEI Flag of Buffer 21 (w) */
    unsigned int TEI22:1;                   /**< \brief [22:22] Set TEI Flag of Buffer 22 (w) */
    unsigned int TEI23:1;                   /**< \brief [23:23] Set TEI Flag of Buffer 23 (w) */
    unsigned int TEI24:1;                   /**< \brief [24:24] Set TEI Flag of Buffer 24 (w) */
    unsigned int TEI25:1;                   /**< \brief [25:25] Set TEI Flag of Buffer 25 (w) */
    unsigned int TEI26:1;                   /**< \brief [26:26] Set TEI Flag of Buffer 26 (w) */
    unsigned int TEI27:1;                   /**< \brief [27:27] Set TEI Flag of Buffer 27 (w) */
    unsigned int TEI28:1;                   /**< \brief [28:28] Set TEI Flag of Buffer 28 (w) */
    unsigned int TEI29:1;                   /**< \brief [29:29] Set TEI Flag of Buffer 29 (w) */
    unsigned int TEI30:1;                   /**< \brief [30:30] Set TEI Flag of Buffer 30 (w) */
    unsigned int TEI31:1;                   /**< \brief [31:31] Set TEI Flag of Buffer 31 (w) */
} Ifx_PSI5_TEISET_Bits;

/** \brief  Time Stamp Register */
typedef struct _Ifx_PSI5_TSR_Bits
{
    unsigned int CTS:24;                    /**< \brief [23:0] Current Time Stamp for the Module (r) */
    unsigned int ETB:3;                     /**< \brief [26:24] External Time Base Select (rw) */
    unsigned int TBS:1;                     /**< \brief [27:27] Time Base Select (rw) */
    unsigned int reserved_28:2;             /**< \brief \internal Reserved */
    unsigned int ACLR:1;                    /**< \brief [30:30] Clear All Current Time Stamp Counters (w) */
    unsigned int CLR:1;                     /**< \brief [31:31] Clear Current Time Stamp for the Module (w) */
} Ifx_PSI5_TSR_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Psi5_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_ACCEN1;

/** \brief  Channel Trigger Value Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_CTV_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_CH_CTV;

/** \brief  Input and Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_IOCR_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_IOCR;

/** \brief  Pulse Generation Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_PGC_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_CH_PGC;

/** \brief  Receiver Control Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_RCRA_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_RCRA;

/** \brief  Receiver Control Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_RCRB_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_RCRB;

/** \brief  Receiver Control Register C */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_RCRC_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_RCRC;

/** \brief  Receive Data Register High */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_RDRH_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_RDRH;

/** \brief  Receive Data Register Low */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_RDRL_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_RDRL;

/** \brief  Receive Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_RSR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_CH_RSR;

/** \brief  Send Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SCR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_CH_SCR;

/** \brief  Send Data Register High */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SDRH_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_SDRH;

/** \brief  Send Data Register Low */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SDRL_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_SDRL;

/** \brief  Serial Data and Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SDS_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_CH_SDS;

/** \brief  SOF TS Capture Register SFTSC */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SFTSC_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5_CH_SFTSC;

/** \brief  Send Output Register High */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SORH_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_SORH;

/** \brief  Send Output Register Low */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SORL_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_SORL;

/** \brief  SOP TS Capture Register SPTSC */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SPTSC_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5_CH_SPTSC;

/** \brief  Send Shift Register High */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SSRH_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_SSRH;

/** \brief  Send Shift Register Low */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_SSRL_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CH_SSRL;

/** \brief  Watch Dog Timer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CH_WDT_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_CH_WDT;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CLC_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_CLC;

/** \brief  CRCIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CRCICLR_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CRCICLR;

/** \brief  CRCI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CRCIOV_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_CRCIOV;

/** \brief  CRCIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_CRCISET_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_CRCISET;

/** \brief  PSI5 Fractional Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_FDR_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_FDR;

/** \brief  Fractional Divider Register for Higher Bit Rate */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_FDRH_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5_FDRH;

/** \brief  Fractional Divider Register for Lower Bit Rate */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_FDRL_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5_FDRL;

/** \brief  Fractional Divider Register for Time Stamp */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_FDRT_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5_FDRT;

/** \brief  Global Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_GCR_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_GCR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_PSI5_ID;

/** \brief  Interrupt Node Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INP_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_INP;

/** \brief  Interrupt Clear Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTCLRA_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_INTCLRA;

/** \brief  Interrupt Clear Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTCLRB_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_INTCLRB;

/** \brief  Interrupt Enable Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTENA_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_INTENA;

/** \brief  Interrupt Enable Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTENB_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_INTENB;

/** \brief  Interrupt Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_INTOV;

/** \brief  Interrupt Set Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTSETA_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_INTSETA;

/** \brief  Interrupt Set Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTSETB_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_INTSETB;

/** \brief  Interrupt Status Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTSTATA_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5_INTSTATA;

/** \brief  Interrupt Status Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_INTSTATB_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5_INTSTATB;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_KRST0_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_KRST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_KRSTCLR_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5_KRSTCLR;

/** \brief  MEIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_MEICLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_MEICLR;

/** \brief  MEI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_MEIOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_MEIOV;

/** \brief  MEIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_MEISET_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_MEISET;

/** \brief  NBIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_NBICLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_NBICLR;

/** \brief  NBI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_NBIOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_NBIOV;

/** \brief  NBIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_NBISET_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_NBISET;

/** \brief  NFIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_NFICLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_NFICLR;

/** \brief  NFI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_NFIOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_NFIOV;

/** \brief  NFIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_NFISET_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_NFISET;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_OCS_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_OCS;

/** \brief  Receive Data FIFO */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RDF_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_RDF;

/** \brief  RDIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RDICLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_RDICLR;

/** \brief  RDI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RDIOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_RDIOV;

/** \brief  RDIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RDISET_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_RDISET;

/** \brief  Receive Data Memory High */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RDM_H_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_RDM_H;

/** \brief  Receive Data Memory Low */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RDM_L_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_RDM_L;

/** \brief  Receive FIFO Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RFC_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_RFC;

/** \brief  RMIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RMICLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_RMICLR;

/** \brief  RMI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RMIOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_RMIOV;

/** \brief  RMIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RMISET_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_RMISET;

/** \brief  RSIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RSICLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_RSICLR;

/** \brief  RSI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RSIOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_RSIOV;

/** \brief  RSIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_RSISET_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_RSISET;

/** \brief  TEIOV Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_TEICLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_TEICLR;

/** \brief  TEI Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_TEIOV_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5_TEIOV;

/** \brief  TEIOV Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_TEISET_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5_TEISET;

/** \brief  Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5_TSR_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5_TSR;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Psi5_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Protection range */
typedef volatile struct _Ifx_PSI5_CH
{
    Ifx_PSI5_CH_IOCR IOCR;                  /**< \brief 0, Input and Output Control Register  */
    Ifx_PSI5_CH_RCRA RCRA;                  /**< \brief 4, Receiver Control Register A  */
    Ifx_PSI5_CH_RCRB RCRB;                  /**< \brief 8, Receiver Control Register B  */
    Ifx_PSI5_CH_RCRC RCRC;                  /**< \brief C, Receiver Control Register C  */
    Ifx_PSI5_CH_WDT WDT[7];                 /**< \brief 10, Watch Dog Timer Register */
    Ifx_PSI5_CH_RSR RSR;                    /**< \brief 2C, Receive Status Register  */
    Ifx_PSI5_CH_SDS SDS[6];                 /**< \brief 30, Serial Data and Status Register */
    Ifx_PSI5_CH_SPTSC SPTSC;                /**< \brief 48, SOP TS Capture Register SPTSC */
    Ifx_PSI5_CH_SFTSC SFTSC;                /**< \brief 4C, SOF TS Capture Register SFTSC */
    Ifx_PSI5_CH_RDRL RDRL;                  /**< \brief 50, Receive Data Register Low  */
    Ifx_PSI5_CH_RDRH RDRH;                  /**< \brief 54, Receive Data Register High  */
    Ifx_PSI5_CH_PGC PGC;                    /**< \brief 58, Pulse Generation Control Register  */
    Ifx_PSI5_CH_CTV CTV;                    /**< \brief 5C, Channel Trigger Value Register  */
    Ifx_PSI5_CH_SCR SCR;                    /**< \brief 60, Send Control Register  */
    Ifx_PSI5_CH_SDRL SDRL;                  /**< \brief 64, Send Data Register Low  */
    Ifx_PSI5_CH_SDRH SDRH;                  /**< \brief 68, Send Data Register High  */
    Ifx_PSI5_CH_SSRL SSRL;                  /**< \brief 6C, Send Shift Register Low  */
    Ifx_PSI5_CH_SSRH SSRH;                  /**< \brief 70, Send Shift Register High  */
    Ifx_PSI5_CH_SORL SORL;                  /**< \brief 74, Send Output Register Low  */
    Ifx_PSI5_CH_SORH SORH;                  /**< \brief 78, Send Output Register High  */
    unsigned char reserved_7C[20];          /**< \brief 7C, \internal Reserved */
} Ifx_PSI5_CH;

/** \brief  Receive data memory */
typedef volatile struct _Ifx_PSI5_RDM
{
    Ifx_PSI5_RDM_L L;                       /**< \brief 0, Receive Data Memory Low */
    Ifx_PSI5_RDM_H H;                       /**< \brief 4, Receive Data Memory High */
} Ifx_PSI5_RDM;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Psi5_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  PSI5 object */
typedef volatile struct _Ifx_PSI5
{
    Ifx_PSI5_CLC CLC;                       /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_PSI5_ID ID;                         /**< \brief 8, Module Identification Register */
    Ifx_PSI5_FDR FDR;                       /**< \brief C, PSI5 Fractional Divider Register */
    Ifx_PSI5_FDRL FDRL;                     /**< \brief 10, Fractional Divider Register for Lower Bit Rate */
    Ifx_PSI5_FDRH FDRH;                     /**< \brief 14, Fractional Divider Register for Higher Bit Rate */
    Ifx_PSI5_FDRT FDRT;                     /**< \brief 18, Fractional Divider Register for Time Stamp */
    Ifx_PSI5_TSR TSRA;                      /**< \brief 1C, Time Stamp Register A */
    Ifx_PSI5_TSR TSRB;                      /**< \brief 20, Time Stamp Register B */
    Ifx_PSI5_TSR TSRC;                      /**< \brief 24, Time Stamp Register C */
    unsigned char reserved_28[4];           /**< \brief 28, \internal Reserved */
    Ifx_PSI5_GCR GCR;                       /**< \brief 2C, Global Control Register */
    Ifx_PSI5_CH CH[2];                      /**< \brief 30, Protection range */
    unsigned char reserved_150[424];        /**< \brief 150, \internal Reserved */
    Ifx_PSI5_INTOV INTOV;                   /**< \brief 2F8, Interrupt Overview Register */
    Ifx_PSI5_INP INP[2];                    /**< \brief 2FC, Interrupt Node Pointer Register */
    unsigned char reserved_304[12];         /**< \brief 304, \internal Reserved */
    Ifx_PSI5_INTSTATA INTSTATA[2];          /**< \brief 310, Interrupt Status Register A */
    unsigned char reserved_318[12];         /**< \brief 318, \internal Reserved */
    Ifx_PSI5_INTSTATB INTSTATB[2];          /**< \brief 324, Interrupt Status Register B */
    unsigned char reserved_32C[12];         /**< \brief 32C, \internal Reserved */
    Ifx_PSI5_INTSETA INTSETA[2];            /**< \brief 338, Interrupt Set Register A */
    unsigned char reserved_340[12];         /**< \brief 340, \internal Reserved */
    Ifx_PSI5_INTSETB INTSETB[2];            /**< \brief 34C, Interrupt Set Register B */
    unsigned char reserved_354[12];         /**< \brief 354, \internal Reserved */
    Ifx_PSI5_INTCLRA INTCLRA[2];            /**< \brief 360, Interrupt Clear Register A */
    unsigned char reserved_368[12];         /**< \brief 368, \internal Reserved */
    Ifx_PSI5_INTCLRB INTCLRB[2];            /**< \brief 374, Interrupt Clear Register A */
    unsigned char reserved_37C[12];         /**< \brief 37C, \internal Reserved */
    Ifx_PSI5_INTENA INTENA[2];              /**< \brief 388, Interrupt Enable Register A */
    unsigned char reserved_390[12];         /**< \brief 390, \internal Reserved */
    Ifx_PSI5_INTENB INTENB[2];              /**< \brief 39C, Interrupt Enable Register B */
    unsigned char reserved_3A4[40];         /**< \brief 3A4, \internal Reserved */
    Ifx_PSI5_OCS OCS;                       /**< \brief 3CC, OCDS Control and Status */
    Ifx_PSI5_ACCEN0 ACCEN0;                 /**< \brief 3D0, Access Enable Register 0 */
    Ifx_PSI5_ACCEN1 ACCEN1;                 /**< \brief 3D4, Access Enable Register 1 */
    Ifx_PSI5_KRST0 KRST0;                   /**< \brief 3D8, Kernel Reset Register 0 */
    Ifx_PSI5_KRST1 KRST1;                   /**< \brief 3DC, Kernel Reset Register 1 */
    Ifx_PSI5_KRSTCLR KRSTCLR;               /**< \brief 3E0, Kernel Reset Status Clear Register */
    Ifx_PSI5_RFC RFC[2];                    /**< \brief 3E4, Receive FIFO Control Register */
    unsigned char reserved_3EC[12];         /**< \brief 3EC, \internal Reserved */
    Ifx_PSI5_RDF RDF[2];                    /**< \brief 3F8, Receive Data FIFO */
    unsigned char reserved_400[12];         /**< \brief 400, \internal Reserved */
    Ifx_PSI5_RSIOV RSIOV[2];                /**< \brief 40C, RSI Overview Register */
    unsigned char reserved_414[12];         /**< \brief 414, \internal Reserved */
    Ifx_PSI5_RMIOV RMIOV[2];                /**< \brief 420, RMI Overview Register */
    unsigned char reserved_428[12];         /**< \brief 428, \internal Reserved */
    Ifx_PSI5_NBIOV NBIOV[2];                /**< \brief 434, NBI Overview Register */
    unsigned char reserved_43C[12];         /**< \brief 43C, \internal Reserved */
    Ifx_PSI5_TEIOV TEIOV[2];                /**< \brief 448, TEI Overview Register */
    unsigned char reserved_450[12];         /**< \brief 450, \internal Reserved */
    Ifx_PSI5_CRCIOV CRCIOV[2];              /**< \brief 45C, CRCI Overview Register */
    unsigned char reserved_464[12];         /**< \brief 464, \internal Reserved */
    Ifx_PSI5_RDIOV RDIOV[2];                /**< \brief 470, RDI Overview Register */
    unsigned char reserved_478[12];         /**< \brief 478, \internal Reserved */
    Ifx_PSI5_NFIOV NFIOV[2];                /**< \brief 484, NFI Overview Register */
    unsigned char reserved_48C[12];         /**< \brief 48C, \internal Reserved */
    Ifx_PSI5_MEIOV MEIOV[2];                /**< \brief 498, MEI Overview Register */
    unsigned char reserved_4A0[12];         /**< \brief 4A0, \internal Reserved */
    Ifx_PSI5_RSISET RSISET[2];              /**< \brief 4AC, RSIOV Set Register */
    unsigned char reserved_4B4[12];         /**< \brief 4B4, \internal Reserved */
    Ifx_PSI5_RMISET RMISET[2];              /**< \brief 4C0, RMIOV Set Register */
    unsigned char reserved_4C8[12];         /**< \brief 4C8, \internal Reserved */
    Ifx_PSI5_NBISET NBISET[2];              /**< \brief 4D4, NBIOV Set Register */
    unsigned char reserved_4DC[12];         /**< \brief 4DC, \internal Reserved */
    Ifx_PSI5_TEISET TEISET[2];              /**< \brief 4E8, TEIOV Set Register */
    unsigned char reserved_4F0[12];         /**< \brief 4F0, \internal Reserved */
    Ifx_PSI5_CRCISET CRCISET[2];            /**< \brief 4FC, CRCIOV Set Register */
    unsigned char reserved_504[12];         /**< \brief 504, \internal Reserved */
    Ifx_PSI5_RDISET RDISET[2];              /**< \brief 510, RDIOV Set Register */
    unsigned char reserved_518[12];         /**< \brief 518, \internal Reserved */
    Ifx_PSI5_NFISET NFISET[2];              /**< \brief 524, NFIOV Set Register */
    unsigned char reserved_52C[12];         /**< \brief 52C, \internal Reserved */
    Ifx_PSI5_MEISET MEISET[2];              /**< \brief 538, MEIOV Set Register */
    unsigned char reserved_540[12];         /**< \brief 540, \internal Reserved */
    Ifx_PSI5_RSICLR RSICLR[2];              /**< \brief 54C, RSIOV Clear Register */
    unsigned char reserved_554[12];         /**< \brief 554, \internal Reserved */
    Ifx_PSI5_RMICLR RMICLR[2];              /**< \brief 560, RMIOV Clear Register */
    unsigned char reserved_568[12];         /**< \brief 568, \internal Reserved */
    Ifx_PSI5_NBICLR NBICLR[2];              /**< \brief 574, NBIOV Clear Register */
    unsigned char reserved_57C[12];         /**< \brief 57C, \internal Reserved */
    Ifx_PSI5_TEICLR TEICLR[2];              /**< \brief 588, TEIOV Clear Register */
    unsigned char reserved_590[12];         /**< \brief 590, \internal Reserved */
    Ifx_PSI5_CRCICLR CRCICLR[2];            /**< \brief 59C, CRCIOV Clear Register */
    unsigned char reserved_5A4[12];         /**< \brief 5A4, \internal Reserved */
    Ifx_PSI5_RDICLR RDICLR[2];              /**< \brief 5B0, RDIOV Clear Register */
    unsigned char reserved_5B8[12];         /**< \brief 5B8, \internal Reserved */
    Ifx_PSI5_NFICLR NFICLR[2];              /**< \brief 5C4, NFIOV Clear Register */
    unsigned char reserved_5CC[12];         /**< \brief 5CC, \internal Reserved */
    Ifx_PSI5_MEICLR MEICLR[2];              /**< \brief 5D8, MEIOV Clear Register */
    unsigned char reserved_5E0[32];         /**< \brief 5E0, \internal Reserved */
    Ifx_PSI5_RDM RDM[2][32];                /**< \brief 600, Receive data memory */
    unsigned char reserved_800[768];        /**< \brief 800, \internal Reserved */
} Ifx_PSI5;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXPSI5_REGDEF_H */
