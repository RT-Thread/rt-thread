/**
 * \file IfxEray_regdef.h
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
 * \defgroup IfxLld_Eray Eray
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Eray_Bitfields Bitfields
 * \ingroup IfxLld_Eray
 * 
 * \defgroup IfxLld_Eray_union Union
 * \ingroup IfxLld_Eray
 * 
 * \defgroup IfxLld_Eray_struct Struct
 * \ingroup IfxLld_Eray
 * 
 */
#ifndef IFXERAY_REGDEF_H
#define IFXERAY_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Eray_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_ERAY_ACCEN0_Bits
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
} Ifx_ERAY_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_ERAY_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_ERAY_ACCEN1_Bits;

/** \brief  Aggregated Channel Status */
typedef struct _Ifx_ERAY_ACS_Bits
{
    unsigned int VFRA:1;                    /**< \brief [0:0] Valid Frame Received on Channel A (vSS!ValidFrameA) (rwh) */
    unsigned int SEDA:1;                    /**< \brief [1:1] Syntax Error Detected on Channel A (vSS!SyntaxErrorA) (rwh) */
    unsigned int CEDA:1;                    /**< \brief [2:2] Content Error Detected on Channel A (vSS!ContentErrorA) (rwh) */
    unsigned int CIA:1;                     /**< \brief [3:3] Communication Indicator Channel A (rwh) */
    unsigned int SBVA:1;                    /**< \brief [4:4] Slot Boundary Violation on Channel A (vSS!BViolationA) (rwh) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int VFRB:1;                    /**< \brief [8:8] Valid Frame Received on Channel B (vSS!ValidFrameB) (rwh) */
    unsigned int SEDB:1;                    /**< \brief [9:9] Syntax Error Detected on Channel B (vSS!SyntaxErrorB) (rwh) */
    unsigned int CEDB:1;                    /**< \brief [10:10] Content Error Detected on Channel B (vSS!ContentErrorB) (rwh) */
    unsigned int CIB:1;                     /**< \brief [11:11] Communication Indicator Channel B (rwh) */
    unsigned int SBVB:1;                    /**< \brief [12:12] Slot Boundary Violation on Channel B (vSS!BViolationB) (rwh) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_ERAY_ACS_Bits;

/** \brief  Communication Controller Error Vector */
typedef struct _Ifx_ERAY_CCEV_Bits
{
    unsigned int CCFC:4;                    /**< \brief [3:0] Clock Correction Failed Counter (vClockCorrectionFailed) (rh) */
    unsigned int reserved_4:2;              /**< \brief \internal Reserved */
    unsigned int ERRM:2;                    /**< \brief [7:6] Error Mode (vPOC!ErrorMode) (rh) */
    unsigned int PTAC:5;                    /**< \brief [12:8] Passive to Active Count (vAllowPassiveToActive) (rh) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_ERAY_CCEV_Bits;

/** \brief  Communication Controller Status Vector */
typedef struct _Ifx_ERAY_CCSV_Bits
{
    unsigned int POCS:6;                    /**< \brief [5:0] Protocol Operation Control Status (rh) */
    unsigned int FSI:1;                     /**< \brief [6:6] Freeze Status Indicator (vPOC!Freeze) (rh) */
    unsigned int HRQ:1;                     /**< \brief [7:7] Halt Request (vPOC!CHIHaltRequest) (rh) */
    unsigned int SLM:2;                     /**< \brief [9:8] Slot Mode (vPOC!SlotMode) (rh) */
    unsigned int reserved_10:2;             /**< \brief \internal Reserved */
    unsigned int CSNI:1;                    /**< \brief [12:12] Coldstart Noise Indicator (vPOC!ColdstartNoise) (rh) */
    unsigned int CSAI:1;                    /**< \brief [13:13] Coldstart Abort Indicator (rh) */
    unsigned int CSI:1;                     /**< \brief [14:14] Cold Start Inhibit (vColdStartInhibit) (rh) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int WSV:3;                     /**< \brief [18:16] Wakeup Status (vPOC!WakeupStatus) (rh) */
    unsigned int RCA:5;                     /**< \brief [23:19] Remaining Coldstart Attempts (vRemainingColdstartAttempts) (rh) */
    unsigned int PSL:6;                     /**< \brief [29:24] POC Status Log (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_CCSV_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_ERAY_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] External Sleep Mode Request Disable Bit (rw) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int RMC:3;                     /**< \brief [10:8] Clock Divider in Run Mode (rw) */
    unsigned int reserved_11:21;            /**< \brief \internal Reserved */
} Ifx_ERAY_CLC_Bits;

/** \brief  Core Release Register */
typedef struct _Ifx_ERAY_CREL_Bits
{
    unsigned int DAY:8;                     /**< \brief [7:0] Design Time Stamp, Day (r) */
    unsigned int MON:8;                     /**< \brief [15:8] Design Time Stamp, Month (r) */
    unsigned int YEAR:4;                    /**< \brief [19:16] Design Time Stamp, Year (r) */
    unsigned int SUBSTEP:4;                 /**< \brief [23:20] Sub-Step of Core Release (r) */
    unsigned int STEP:4;                    /**< \brief [27:24] Step of Core Release (r) */
    unsigned int REL:4;                     /**< \brief [31:28] Core Release (r) */
} Ifx_ERAY_CREL_Bits;

/** \brief  Busy and Input Buffer Control Register */
typedef struct _Ifx_ERAY_CUST1_Bits
{
    unsigned int INT0:1;                    /**< \brief [0:0] CIF Timeout Service Request Status (rwh) */
    unsigned int OEN:1;                     /**< \brief [1:1] Enable auto delay scheme for Output Buffer Control Register (OBCR) (rw) */
    unsigned int IEN:1;                     /**< \brief [2:2] Enable auto delay scheme for Input Buffer Control Register (IBCR) (rw) */
    unsigned int IBFS:1;                    /**< \brief [3:3] Input Buffer Status Register (rh) */
    unsigned int IBF1PAG:1;                 /**< \brief [4:4] Input Buffer 1 Page Select Register (rw) */
    unsigned int reserved_5:2;              /**< \brief \internal Reserved */
    unsigned int IBF2PAG:1;                 /**< \brief [7:7] Input Buffer 2 Page Select Register (rw) */
    unsigned int reserved_8:2;              /**< \brief \internal Reserved */
    unsigned int RISA:2;                    /**< \brief [11:10] Receive Input Select Channel A (rw) */
    unsigned int RISB:2;                    /**< \brief [13:12] Receive Input Select Channel B (rw) */
    unsigned int STPWTS:2;                  /**< \brief [15:14] Stop Watch Trigger Input Select (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ERAY_CUST1_Bits;

/** \brief  Customer Interface Timeout Counter */
typedef struct _Ifx_ERAY_CUST3_Bits
{
    unsigned int TO:32;                     /**< \brief [31:0] CIF Timeout Reload Value (rw) */
} Ifx_ERAY_CUST3_Bits;

/** \brief  Error Service Request Enable Reset */
typedef struct _Ifx_ERAY_EIER_Bits
{
    unsigned int PEMCE:1;                   /**< \brief [0:0] POC Error Mode Changed Service Request Enable (rwh) */
    unsigned int CNAE:1;                    /**< \brief [1:1] Command Not Accepted Service Request Enable (rwh) */
    unsigned int SFBME:1;                   /**< \brief [2:2] SYNC Frames Below Minimum Service Request Enable (rwh) */
    unsigned int SFOE:1;                    /**< \brief [3:3] SYNC Frame Overflow Service Request Enable (rwh) */
    unsigned int CCFE:1;                    /**< \brief [4:4] Clock Correction Failure Service Request Enable (rwh) */
    unsigned int CCLE:1;                    /**< \brief [5:5] CHI Command Locked Service Request Enable (rwh) */
    unsigned int EERRE:1;                   /**< \brief [6:6] ECC Error Service Request Enable (rwh) */
    unsigned int RFOE:1;                    /**< \brief [7:7] Receive FIFO Overrun Service Request Enable (rwh) */
    unsigned int EFAE:1;                    /**< \brief [8:8] Empty FIFO Access Service Request Enable (rwh) */
    unsigned int IIBAE:1;                   /**< \brief [9:9] Illegal Input Buffer Access Service Request Enable (rwh) */
    unsigned int IOBAE:1;                   /**< \brief [10:10] Illegal Output Buffer Access Service Request Enable (rwh) */
    unsigned int MHFE:1;                    /**< \brief [11:11] Message Handler Constraints Flag Service Request Enable (rwh) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int EDAE:1;                    /**< \brief [16:16] Error Detected on Channel A Service Request Enable (rwh) */
    unsigned int LTVAE:1;                   /**< \brief [17:17] Latest Transmit Violation Channel A Service Request Enable (rwh) */
    unsigned int TABAE:1;                   /**< \brief [18:18] Transmission Across Boundary Channel A Service Request Enable (rwh) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int EDBE:1;                    /**< \brief [24:24] Error Detected on Channel B Service Request Enable (rwh) */
    unsigned int LTVBE:1;                   /**< \brief [25:25] Latest Transmit Violation Channel B Service Request Enable (rwh) */
    unsigned int TABBE:1;                   /**< \brief [26:26] Transmission Across Boundary Channel B Service Request Enable (rwh) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_EIER_Bits;

/** \brief  Error Service Request Enable Set */
typedef struct _Ifx_ERAY_EIES_Bits
{
    unsigned int PEMCE:1;                   /**< \brief [0:0] POC Error Mode Changed Service Request Enable (rwh) */
    unsigned int CNAE:1;                    /**< \brief [1:1] Command Not Accepted Service Request Enable (rwh) */
    unsigned int SFBME:1;                   /**< \brief [2:2] SYNC Frames Below Minimum Service Request Enable (rwh) */
    unsigned int SFOE:1;                    /**< \brief [3:3] SYNC Frame Overflow Service Request Enable (rwh) */
    unsigned int CCFE:1;                    /**< \brief [4:4] Clock Correction Failure Service Request Enable (rwh) */
    unsigned int CCLE:1;                    /**< \brief [5:5] CHI Command Locked Service Request Enable (rwh) */
    unsigned int EERRE:1;                   /**< \brief [6:6] ECC Error Service Request Enable (rwh) */
    unsigned int RFOE:1;                    /**< \brief [7:7] Receive FIFO Overrun Service Request Enable (rwh) */
    unsigned int EFAE:1;                    /**< \brief [8:8] Empty FIFO Access Service Request Enable (rwh) */
    unsigned int IIBAE:1;                   /**< \brief [9:9] Illegal Input Buffer Access Service Request Enable (rwh) */
    unsigned int IOBAE:1;                   /**< \brief [10:10] Illegal Output Buffer Access Service Request Enable (rwh) */
    unsigned int MHFE:1;                    /**< \brief [11:11] Message Handler Constraints Flag Service Request Enable (rwh) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int EDAE:1;                    /**< \brief [16:16] Error Detected on Channel A Service Request Enable (rwh) */
    unsigned int LTVAE:1;                   /**< \brief [17:17] Latest Transmit Violation Channel A Service Request Enable (rwh) */
    unsigned int TABAE:1;                   /**< \brief [18:18] Transmission Across Boundary Channel A Service Request Enable (rwh) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int EDBE:1;                    /**< \brief [24:24] Error Detected on Channel B Service Request Enable (rwh) */
    unsigned int LTVBE:1;                   /**< \brief [25:25] Latest Transmit Violation Channel B Service Request Enable (rwh) */
    unsigned int TABBE:1;                   /**< \brief [26:26] Transmission Across Boundary Channel B Service Request Enable (rwh) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_EIES_Bits;

/** \brief  Error Service Request Line Select */
typedef struct _Ifx_ERAY_EILS_Bits
{
    unsigned int PEMCL:1;                   /**< \brief [0:0] POC Error Mode Changed Service Request Line (rw) */
    unsigned int CNAL:1;                    /**< \brief [1:1] Command Not Accepted Service Request Line (rw) */
    unsigned int SFBML:1;                   /**< \brief [2:2] SYNC Frames Below Minimum Service Request Line (rw) */
    unsigned int SFOL:1;                    /**< \brief [3:3] SYNC Frame Overflow Service Request Line (rw) */
    unsigned int CCFL:1;                    /**< \brief [4:4] Clock Correction Failure Service Request Line (rw) */
    unsigned int CCLL:1;                    /**< \brief [5:5] CHI Command Locked Service Request Line (rw) */
    unsigned int EERRL:1;                   /**< \brief [6:6] ECC Error Service Request Line (rw) */
    unsigned int RFOL:1;                    /**< \brief [7:7] Receive FIFO Overrun Service Request Line (rw) */
    unsigned int EFAL:1;                    /**< \brief [8:8] Empty FIFO Access Service Request Line (rw) */
    unsigned int IIBAL:1;                   /**< \brief [9:9] Illegal Input Buffer Access Service Request Line (rw) */
    unsigned int IOBAL:1;                   /**< \brief [10:10] Illegal Output Buffer Access Service Request Line (rw) */
    unsigned int MHFL:1;                    /**< \brief [11:11] Message Handler Constrains Flag Service Request Line (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int EDAL:1;                    /**< \brief [16:16] Error Detected on Channel A Service Request Line (rw) */
    unsigned int LTVAL:1;                   /**< \brief [17:17] Latest Transmit Violation Channel A Service Request Line (rw) */
    unsigned int TABAL:1;                   /**< \brief [18:18] Transmission Across Boundary Channel A Service Request Line (rw) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int EDBL:1;                    /**< \brief [24:24] Error Detected on Channel B Service Request Line (rw) */
    unsigned int LTVBL:1;                   /**< \brief [25:25] Latest Transmit Violation Channel B Service Request Line (rw) */
    unsigned int TABBL:1;                   /**< \brief [26:26] Transmission Across Boundary Channel A Service Request Line (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_EILS_Bits;

/** \brief  Error Service Request Register */
typedef struct _Ifx_ERAY_EIR_Bits
{
    unsigned int PEMC:1;                    /**< \brief [0:0] POC Error Mode Changed (rwh) */
    unsigned int CNA:1;                     /**< \brief [1:1] Command Not Accepted (rwh) */
    unsigned int SFBM:1;                    /**< \brief [2:2] SYNC Frames Below Minimum (rwh) */
    unsigned int SFO:1;                     /**< \brief [3:3] SYNC Frame Overflow (rwh) */
    unsigned int CCF:1;                     /**< \brief [4:4] Clock Correction Failure (rwh) */
    unsigned int CCL:1;                     /**< \brief [5:5] CHI Command Locked (rwh) */
    unsigned int EERR:1;                    /**< \brief [6:6] ECC Error (rh) */
    unsigned int RFO:1;                     /**< \brief [7:7] Receive FIFO Overrun (rh) */
    unsigned int EFA:1;                     /**< \brief [8:8] Empty FIFO Access (rwh) */
    unsigned int IIBA:1;                    /**< \brief [9:9] Illegal Input Buffer Access (rwh) */
    unsigned int IOBA:1;                    /**< \brief [10:10] Illegal Output Buffer Access (rwh) */
    unsigned int MHF:1;                     /**< \brief [11:11] Message Handler Constraints Flag (rwh) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int EDA:1;                     /**< \brief [16:16] Error Detected on Channel A (rwh) */
    unsigned int LTVA:1;                    /**< \brief [17:17] Latest Transmit Violation Channel A (rwh) */
    unsigned int TABA:1;                    /**< \brief [18:18] Transmission Across Boundary Channel A (rwh) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int EDB:1;                     /**< \brief [24:24] Error Detected on Channel B (rwh) */
    unsigned int LTVB:1;                    /**< \brief [25:25] Latest Transmit Violation Channel B (rwh) */
    unsigned int TABB:1;                    /**< \brief [26:26] Transmission Across Boundary Channel B (rwh) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_EIR_Bits;

/** \brief  Endian Register */
typedef struct _Ifx_ERAY_ENDN_Bits
{
    unsigned int ETV:32;                    /**< \brief [31:0] Endianness Test Value (r) */
} Ifx_ERAY_ENDN_Bits;

/** \brief  Even Sync ID Symbol Window */
typedef struct _Ifx_ERAY_ESID_Bits
{
    unsigned int EID:10;                    /**< \brief [9:0] Even Sync ID (vsSyncIDListA,B even) (rh) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int RXEA:1;                    /**< \brief [14:14] Received/Configured Even Sync ID on Channel A (rh) */
    unsigned int RXEB:1;                    /**< \brief [15:15] Received/Configured Even Sync ID on Channel B (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ERAY_ESID_Bits;

/** \brief  FIFO Critical Level */
typedef struct _Ifx_ERAY_FCL_Bits
{
    unsigned int CL:8;                      /**< \brief [7:0] Critical Level (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_ERAY_FCL_Bits;

/** \brief  FIFO Rejection Filter */
typedef struct _Ifx_ERAY_FRF_Bits
{
    unsigned int CH:2;                      /**< \brief [1:0] Channel Filter (rw) */
    unsigned int FID:11;                    /**< \brief [12:2] Frame ID Filter (rw) */
    unsigned int reserved_13:3;             /**< \brief \internal Reserved */
    unsigned int CYF:7;                     /**< \brief [22:16] Cycle Counter Filter (rw) */
    unsigned int RSS:1;                     /**< \brief [23:23] Reject in Static Segment (rw) */
    unsigned int RNF:1;                     /**< \brief [24:24] Reject NULL Frames (rw) */
    unsigned int reserved_25:7;             /**< \brief \internal Reserved */
} Ifx_ERAY_FRF_Bits;

/** \brief  FIFO Rejection Filter Mask */
typedef struct _Ifx_ERAY_FRFM_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int MFID:11;                   /**< \brief [12:2] Mask Frame ID Filter (rw) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_ERAY_FRFM_Bits;

/** \brief  FIFO Status Register */
typedef struct _Ifx_ERAY_FSR_Bits
{
    unsigned int RFNE:1;                    /**< \brief [0:0] Receive FIFO Not Empty (rh) */
    unsigned int RFCL:1;                    /**< \brief [1:1] Receive FIFO Critical Level (rh) */
    unsigned int RFO:1;                     /**< \brief [2:2] Receive FIFO Overrun (rh) */
    unsigned int reserved_3:5;              /**< \brief \internal Reserved */
    unsigned int RFFL:8;                    /**< \brief [15:8] Receive FIFO Fill Level (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ERAY_FSR_Bits;

/** \brief  GTU Configuration Register 1 */
typedef struct _Ifx_ERAY_GTUC01_Bits
{
    unsigned int UT:20;                     /**< \brief [19:0] Microtick per Cycle (pMicroPerCycle) (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC01_Bits;

/** \brief  GTU Configuration Register 2 */
typedef struct _Ifx_ERAY_GTUC02_Bits
{
    unsigned int MPC:14;                    /**< \brief [13:0] Macrotick Per Cycle (gMacroPerCycle) (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int SNM:4;                     /**< \brief [19:16] Sync Node Max (gSyncNodeMax) (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC02_Bits;

/** \brief  GTU Configuration Register 3 */
typedef struct _Ifx_ERAY_GTUC03_Bits
{
    unsigned int UIOA:8;                    /**< \brief [7:0] Microtick Initial Offset Channel A (pMicroInitialOffset[A]) (rw) */
    unsigned int UIOB:8;                    /**< \brief [15:8] Microtick Initial Offset Channel B (pMicroInitialOffset[B]) (rw) */
    unsigned int MIOA:7;                    /**< \brief [22:16] Macrotick Initial Offset Channel A (gMacroInitialOffset[A]) (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int MIOB:7;                    /**< \brief [30:24] Macrotick Initial Offset Channel B (gMacroInitialOffset[B]) (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC03_Bits;

/** \brief  GTU Configuration Register 4 */
typedef struct _Ifx_ERAY_GTUC04_Bits
{
    unsigned int NIT:14;                    /**< \brief [13:0] Network Idle Time Start (gMacroPerCycle - gdNIT - 1) (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int OCS:14;                    /**< \brief [29:16] Offset Correction Start (gOffsetCorrectionStart - 1) (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC04_Bits;

/** \brief  GTU Configuration Register 5 */
typedef struct _Ifx_ERAY_GTUC05_Bits
{
    unsigned int DCA:8;                     /**< \brief [7:0] Delay Compensation Channel A (pDelayCompensation[A]) (rw) */
    unsigned int DCB:8;                     /**< \brief [15:8] Delay Compensation Channel B (pDelayCompensation[B]) (rw) */
    unsigned int CDD:5;                     /**< \brief [20:16] Cluster Drift Damping (pClusterDriftDamping) (rw) */
    unsigned int reserved_21:3;             /**< \brief \internal Reserved */
    unsigned int DEC:8;                     /**< \brief [31:24] Decoding Correction (pDecodingCorrection) (rw) */
} Ifx_ERAY_GTUC05_Bits;

/** \brief  GTU Configuration Register 6 */
typedef struct _Ifx_ERAY_GTUC06_Bits
{
    unsigned int ASR:11;                    /**< \brief [10:0] Accepted Startup Range (pdAcceptedStartupRange) (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int MOD:11;                    /**< \brief [26:16] Maximum Oscillator Drift (pdMaxDrift) (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC06_Bits;

/** \brief  GTU Configuration Register 7 */
typedef struct _Ifx_ERAY_GTUC07_Bits
{
    unsigned int SSL:10;                    /**< \brief [9:0] Static Slot Length (gdStaticSlot) (rw) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int NSS:10;                    /**< \brief [25:16] Number of Static Slots (gNumberOfStaticSlots) (rw) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC07_Bits;

/** \brief  GTU Configuration Register 8 */
typedef struct _Ifx_ERAY_GTUC08_Bits
{
    unsigned int MSL:6;                     /**< \brief [5:0] Minislot Length (gdMinislot) (rw) */
    unsigned int reserved_6:10;             /**< \brief \internal Reserved */
    unsigned int NMS:13;                    /**< \brief [28:16] Number of Minislots (gNumberOfMinislots) (rw) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC08_Bits;

/** \brief  GTU Configuration Register 9 */
typedef struct _Ifx_ERAY_GTUC09_Bits
{
    unsigned int APO:6;                     /**< \brief [5:0] Action Point Offset (gdActionPointOffset) (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int MAPO:5;                    /**< \brief [12:8] Minislot Action Point Offset (gd Minislot Action Point Offset) (rw) */
    unsigned int reserved_13:3;             /**< \brief \internal Reserved */
    unsigned int DSI:2;                     /**< \brief [17:16] Dynamic Slot Idle Phase (gdDynamicSlotIdlePhase) (rw) */
    unsigned int reserved_18:14;            /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC09_Bits;

/** \brief  GTU Configuration Register 10 */
typedef struct _Ifx_ERAY_GTUC10_Bits
{
    unsigned int MOC:14;                    /**< \brief [13:0] Maximum Offset Correction (pOffsetCorrectionOut) (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int MRC:11;                    /**< \brief [26:16] Maximum Rate Correction (pRateCorrectionOut) (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC10_Bits;

/** \brief  GTU Configuration Register 11 */
typedef struct _Ifx_ERAY_GTUC11_Bits
{
    unsigned int EOCC:2;                    /**< \brief [1:0] External Offset Correction Control (pExternOffsetControl) (rw) */
    unsigned int reserved_2:6;              /**< \brief \internal Reserved */
    unsigned int ERCC:2;                    /**< \brief [9:8] External Rate Correction Control (pExternRateControl) (rw) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int EOC:3;                     /**< \brief [18:16] External Offset Correction (pExternOffsetCorrection) (rw) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int ERC:3;                     /**< \brief [26:24] External Rate Correction (pExternRateCorrection) (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_GTUC11_Bits;

/** \brief  Input Buffer Command Mask */
typedef struct _Ifx_ERAY_IBCM_Bits
{
    unsigned int LHSH:1;                    /**< \brief [0:0] Load Header Section Host (rwh) */
    unsigned int LDSH:1;                    /**< \brief [1:1] Load Data Section Host (rwh) */
    unsigned int STXRH:1;                   /**< \brief [2:2] Set Transmission Request Host (rwh) */
    unsigned int reserved_3:13;             /**< \brief \internal Reserved */
    unsigned int LHSS:1;                    /**< \brief [16:16] Load Header Section Shadow (rh) */
    unsigned int LDSS:1;                    /**< \brief [17:17] Load Data Section Shadow (rh) */
    unsigned int STXRS:1;                   /**< \brief [18:18] Transmission Request Shadow (rh) */
    unsigned int reserved_19:13;            /**< \brief \internal Reserved */
} Ifx_ERAY_IBCM_Bits;

/** \brief  Input Buffer Command Request */
typedef struct _Ifx_ERAY_IBCR_Bits
{
    unsigned int IBRH:7;                    /**< \brief [6:0] Input Buffer Request Host (rwh) */
    unsigned int reserved_7:8;              /**< \brief \internal Reserved */
    unsigned int IBSYH:1;                   /**< \brief [15:15] Input Buffer Busy Host (rh) */
    unsigned int IBRS:7;                    /**< \brief [22:16] Input Buffer Request Shadow (rh) */
    unsigned int reserved_23:8;             /**< \brief \internal Reserved */
    unsigned int IBSYS:1;                   /**< \brief [31:31] Input Buffer Busy Shadow (rh) */
} Ifx_ERAY_IBCR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_ERAY_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_ERAY_ID_Bits;

/** \brief  Service Request Line Enable */
typedef struct _Ifx_ERAY_ILE_Bits
{
    unsigned int EINT0:1;                   /**< \brief [0:0] Enable Service Request Line 0 (INT0SRC) (rw) */
    unsigned int EINT1:1;                   /**< \brief [1:1] Enable Service Request Line 1 (INT1SRC) (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_ERAY_ILE_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_ERAY_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_ERAY_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_ERAY_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_ERAY_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_ERAY_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_ERAY_KRSTCLR_Bits;

/** \brief  Lock Register */
typedef struct _Ifx_ERAY_LCK_Bits
{
    unsigned int CLK:8;                     /**< \brief [7:0] Configuration Lock Key (w) */
    unsigned int TMK:8;                     /**< \brief [15:8] Test Mode Key (w) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ERAY_LCK_Bits;

/** \brief  Last Dynamic Transmit Slot */
typedef struct _Ifx_ERAY_LDTS_Bits
{
    unsigned int LDTA:11;                   /**< \brief [10:0] Last Dynamic Transmission Channel A (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int LDTB:11;                   /**< \brief [26:16] Last Dynamic Transmission Channel B (rh) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_LDTS_Bits;

/** \brief  Message Buffer Status */
typedef struct _Ifx_ERAY_MBS_Bits
{
    unsigned int VFRA:1;                    /**< \brief [0:0] Valid Frame Received on Channel A (vSS!ValidFrameA) (rh) */
    unsigned int VFRB:1;                    /**< \brief [1:1] Valid Frame Received on Channel B (vSS!ValidFrameB) (rh) */
    unsigned int SEOA:1;                    /**< \brief [2:2] Syntax Error Observed on Channel A (vSS!SyntaxErrorA) (rh) */
    unsigned int SEOB:1;                    /**< \brief [3:3] Syntax Error Observed on Channel B (vSS!SyntaxErrorB) (rh) */
    unsigned int CEOA:1;                    /**< \brief [4:4] Content Error Observed on Channel A (vSS!ContentErrorA) (rh) */
    unsigned int CEOB:1;                    /**< \brief [5:5] Content Error Observed on Channel B (vSS!ContentErrorB) (rh) */
    unsigned int SVOA:1;                    /**< \brief [6:6] Slot Boundary Violation Observed on Channel A (vSS!BViolationA) (rh) */
    unsigned int SVOB:1;                    /**< \brief [7:7] Slot Boundary Violation Observed on Channel B (vSS!BViolationB) (rh) */
    unsigned int TCIA:1;                    /**< \brief [8:8] Transmission Conflict Indication Channel A (vSS!TxConflictA) (rh) */
    unsigned int TCIB:1;                    /**< \brief [9:9] Transmission Conflict Indication Channel B (vSS!TxConflictB) (rh) */
    unsigned int ESA:1;                     /**< \brief [10:10] Empty Slot Channel A (rh) */
    unsigned int ESB:1;                     /**< \brief [11:11] Empty Slot Channel B (rh) */
    unsigned int MLST:1;                    /**< \brief [12:12] Message Lost (rh) */
    unsigned int reserved_13:1;             /**< \brief \internal Reserved */
    unsigned int FTA:1;                     /**< \brief [14:14] Frame Transmitted on Channel A (rh) */
    unsigned int FTB:1;                     /**< \brief [15:15] Frame Transmitted on Channel B (rh) */
    unsigned int CCS:6;                     /**< \brief [21:16] Cycle Count Status (rh) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int RCIS:1;                    /**< \brief [24:24] Received on Channel Indicator Status (vSS!Channel) (rh) */
    unsigned int SFIS:1;                    /**< \brief [25:25] Startup Frame Indicator Status (vRF!Header!SuFIndicator) (rh) */
    unsigned int SYNS:1;                    /**< \brief [26:26] SYNC Frame Indicator Status (vRF!Header!SyFIndicator) (rh) */
    unsigned int NFIS:1;                    /**< \brief [27:27] NULL Frame Indicator Status (vRF!Header!NFIndicator) (rh) */
    unsigned int PPIS:1;                    /**< \brief [28:28] Payload Preamble Indictor Status (vRF!Header!PPIndicator) (rh) */
    unsigned int RESS:1;                    /**< \brief [29:29] Reserved Bit Status (vRF!Header!Reserved) (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_MBS_Bits;

/** \brief  Message Buffer Status Changed 1 */
typedef struct _Ifx_ERAY_MBSC1_Bits
{
    unsigned int MBC0:1;                    /**< \brief [0:0] Message Buffer Status Changed 0 (0 = 0-31) (rh) */
    unsigned int MBC1:1;                    /**< \brief [1:1] Message Buffer Status Changed 1 (1 = 0-31) (rh) */
    unsigned int MBC2:1;                    /**< \brief [2:2] Message Buffer Status Changed 2 (2 = 0-31) (rh) */
    unsigned int MBC3:1;                    /**< \brief [3:3] Message Buffer Status Changed 3 (3 = 0-31) (rh) */
    unsigned int MBC4:1;                    /**< \brief [4:4] Message Buffer Status Changed 4 (4 = 0-31) (rh) */
    unsigned int MBC5:1;                    /**< \brief [5:5] Message Buffer Status Changed 5 (5 = 0-31) (rh) */
    unsigned int MBC6:1;                    /**< \brief [6:6] Message Buffer Status Changed 6 (6 = 0-31) (rh) */
    unsigned int MBC7:1;                    /**< \brief [7:7] Message Buffer Status Changed 7 (7 = 0-31) (rh) */
    unsigned int MBC8:1;                    /**< \brief [8:8] Message Buffer Status Changed 8 (8 = 0-31) (rh) */
    unsigned int MBC9:1;                    /**< \brief [9:9] Message Buffer Status Changed 9 (9 = 0-31) (rh) */
    unsigned int MBC10:1;                   /**< \brief [10:10] Message Buffer Status Changed 10 (10 = 0-31) (rh) */
    unsigned int MBC11:1;                   /**< \brief [11:11] Message Buffer Status Changed 11 (11 = 0-31) (rh) */
    unsigned int MBC12:1;                   /**< \brief [12:12] Message Buffer Status Changed 12 (12 = 0-31) (rh) */
    unsigned int MBC13:1;                   /**< \brief [13:13] Message Buffer Status Changed 13 (13 = 0-31) (rh) */
    unsigned int MBC14:1;                   /**< \brief [14:14] Message Buffer Status Changed 14 (14 = 0-31) (rh) */
    unsigned int MBC15:1;                   /**< \brief [15:15] Message Buffer Status Changed 15 (15 = 0-31) (rh) */
    unsigned int MBC16:1;                   /**< \brief [16:16] Message Buffer Status Changed 16 (16 = 0-31) (rh) */
    unsigned int MBC17:1;                   /**< \brief [17:17] Message Buffer Status Changed 17 (17 = 0-31) (rh) */
    unsigned int MBC18:1;                   /**< \brief [18:18] Message Buffer Status Changed 18 (18 = 0-31) (rh) */
    unsigned int MBC19:1;                   /**< \brief [19:19] Message Buffer Status Changed 19 (19 = 0-31) (rh) */
    unsigned int MBC20:1;                   /**< \brief [20:20] Message Buffer Status Changed 20 (20 = 0-31) (rh) */
    unsigned int MBC21:1;                   /**< \brief [21:21] Message Buffer Status Changed 21 (21 = 0-31) (rh) */
    unsigned int MBC22:1;                   /**< \brief [22:22] Message Buffer Status Changed 22 (22 = 0-31) (rh) */
    unsigned int MBC23:1;                   /**< \brief [23:23] Message Buffer Status Changed 23 (23 = 0-31) (rh) */
    unsigned int MBC24:1;                   /**< \brief [24:24] Message Buffer Status Changed 24 (24 = 0-31) (rh) */
    unsigned int MBC25:1;                   /**< \brief [25:25] Message Buffer Status Changed 25 (25 = 0-31) (rh) */
    unsigned int MBC26:1;                   /**< \brief [26:26] Message Buffer Status Changed 26 (26 = 0-31) (rh) */
    unsigned int MBC27:1;                   /**< \brief [27:27] Message Buffer Status Changed 27 (27 = 0-31) (rh) */
    unsigned int MBC28:1;                   /**< \brief [28:28] Message Buffer Status Changed 28 (28 = 0-31) (rh) */
    unsigned int MBC29:1;                   /**< \brief [29:29] Message Buffer Status Changed 29 (29 = 0-31) (rh) */
    unsigned int MBC30:1;                   /**< \brief [30:30] Message Buffer Status Changed 30 (30 = 0-31) (rh) */
    unsigned int MBC31:1;                   /**< \brief [31:31] Message Buffer Status Changed 31 (31 = 0-31) (rh) */
} Ifx_ERAY_MBSC1_Bits;

/** \brief  Message Buffer Status Changed 2 */
typedef struct _Ifx_ERAY_MBSC2_Bits
{
    unsigned int MBC32:1;                   /**< \brief [0:0] Message Buffer Status Changed 32 (32 = 32-63) (rh) */
    unsigned int MBC33:1;                   /**< \brief [1:1] Message Buffer Status Changed 33 (33 = 32-63) (rh) */
    unsigned int MBC34:1;                   /**< \brief [2:2] Message Buffer Status Changed 34 (34 = 32-63) (rh) */
    unsigned int MBC35:1;                   /**< \brief [3:3] Message Buffer Status Changed 35 (35 = 32-63) (rh) */
    unsigned int MBC36:1;                   /**< \brief [4:4] Message Buffer Status Changed 36 (36 = 32-63) (rh) */
    unsigned int MBC37:1;                   /**< \brief [5:5] Message Buffer Status Changed 37 (37 = 32-63) (rh) */
    unsigned int MBC38:1;                   /**< \brief [6:6] Message Buffer Status Changed 38 (38 = 32-63) (rh) */
    unsigned int MBC39:1;                   /**< \brief [7:7] Message Buffer Status Changed 39 (39 = 32-63) (rh) */
    unsigned int MBC40:1;                   /**< \brief [8:8] Message Buffer Status Changed 40 (40 = 32-63) (rh) */
    unsigned int MBC41:1;                   /**< \brief [9:9] Message Buffer Status Changed 41 (41 = 32-63) (rh) */
    unsigned int MBC42:1;                   /**< \brief [10:10] Message Buffer Status Changed 42 (42 = 32-63) (rh) */
    unsigned int MBC43:1;                   /**< \brief [11:11] Message Buffer Status Changed 43 (43 = 32-63) (rh) */
    unsigned int MBC44:1;                   /**< \brief [12:12] Message Buffer Status Changed 44 (44 = 32-63) (rh) */
    unsigned int MBC45:1;                   /**< \brief [13:13] Message Buffer Status Changed 45 (45 = 32-63) (rh) */
    unsigned int MBC46:1;                   /**< \brief [14:14] Message Buffer Status Changed 46 (46 = 32-63) (rh) */
    unsigned int MBC47:1;                   /**< \brief [15:15] Message Buffer Status Changed 47 (47 = 32-63) (rh) */
    unsigned int MBC48:1;                   /**< \brief [16:16] Message Buffer Status Changed 48 (48 = 32-63) (rh) */
    unsigned int MBC49:1;                   /**< \brief [17:17] Message Buffer Status Changed 49 (49 = 32-63) (rh) */
    unsigned int MBC50:1;                   /**< \brief [18:18] Message Buffer Status Changed 50 (50 = 32-63) (rh) */
    unsigned int MBC51:1;                   /**< \brief [19:19] Message Buffer Status Changed 51 (51 = 32-63) (rh) */
    unsigned int MBC52:1;                   /**< \brief [20:20] Message Buffer Status Changed 52 (52 = 32-63) (rh) */
    unsigned int MBC53:1;                   /**< \brief [21:21] Message Buffer Status Changed 53 (53 = 32-63) (rh) */
    unsigned int MBC54:1;                   /**< \brief [22:22] Message Buffer Status Changed 54 (54 = 32-63) (rh) */
    unsigned int MBC55:1;                   /**< \brief [23:23] Message Buffer Status Changed 55 (55 = 32-63) (rh) */
    unsigned int MBC56:1;                   /**< \brief [24:24] Message Buffer Status Changed 56 (56 = 32-63) (rh) */
    unsigned int MBC57:1;                   /**< \brief [25:25] Message Buffer Status Changed 57 (57 = 32-63) (rh) */
    unsigned int MBC58:1;                   /**< \brief [26:26] Message Buffer Status Changed 58 (58 = 32-63) (rh) */
    unsigned int MBC59:1;                   /**< \brief [27:27] Message Buffer Status Changed 59 (59 = 32-63) (rh) */
    unsigned int MBC60:1;                   /**< \brief [28:28] Message Buffer Status Changed 60 (60 = 32-63) (rh) */
    unsigned int MBC61:1;                   /**< \brief [29:29] Message Buffer Status Changed 61 (61 = 32-63) (rh) */
    unsigned int MBC62:1;                   /**< \brief [30:30] Message Buffer Status Changed 62 (62 = 32-63) (rh) */
    unsigned int MBC63:1;                   /**< \brief [31:31] Message Buffer Status Changed 63 (63 = 32-63) (rh) */
} Ifx_ERAY_MBSC2_Bits;

/** \brief  Message Buffer Status Changed 3 */
typedef struct _Ifx_ERAY_MBSC3_Bits
{
    unsigned int MBC64:1;                   /**< \brief [0:0] Message Buffer Status Changed 64 (64 = 64-95) (rh) */
    unsigned int MBC65:1;                   /**< \brief [1:1] Message Buffer Status Changed 65 (65 = 64-95) (rh) */
    unsigned int MBC66:1;                   /**< \brief [2:2] Message Buffer Status Changed 66 (66 = 64-95) (rh) */
    unsigned int MBC67:1;                   /**< \brief [3:3] Message Buffer Status Changed 67 (67 = 64-95) (rh) */
    unsigned int MBC68:1;                   /**< \brief [4:4] Message Buffer Status Changed 68 (68 = 64-95) (rh) */
    unsigned int MBC69:1;                   /**< \brief [5:5] Message Buffer Status Changed 69 (69 = 64-95) (rh) */
    unsigned int MBC70:1;                   /**< \brief [6:6] Message Buffer Status Changed 70 (70 = 64-95) (rh) */
    unsigned int MBC71:1;                   /**< \brief [7:7] Message Buffer Status Changed 71 (71 = 64-95) (rh) */
    unsigned int MBC72:1;                   /**< \brief [8:8] Message Buffer Status Changed 72 (72 = 64-95) (rh) */
    unsigned int MBC73:1;                   /**< \brief [9:9] Message Buffer Status Changed 73 (73 = 64-95) (rh) */
    unsigned int MBC74:1;                   /**< \brief [10:10] Message Buffer Status Changed 74 (74 = 64-95) (rh) */
    unsigned int MBC75:1;                   /**< \brief [11:11] Message Buffer Status Changed 75 (75 = 64-95) (rh) */
    unsigned int MBC76:1;                   /**< \brief [12:12] Message Buffer Status Changed 76 (76 = 64-95) (rh) */
    unsigned int MBC77:1;                   /**< \brief [13:13] Message Buffer Status Changed 77 (77 = 64-95) (rh) */
    unsigned int MBC78:1;                   /**< \brief [14:14] Message Buffer Status Changed 78 (78 = 64-95) (rh) */
    unsigned int MBC79:1;                   /**< \brief [15:15] Message Buffer Status Changed 79 (79 = 64-95) (rh) */
    unsigned int MBC80:1;                   /**< \brief [16:16] Message Buffer Status Changed 80 (80 = 64-95) (rh) */
    unsigned int MBC81:1;                   /**< \brief [17:17] Message Buffer Status Changed 81 (81 = 64-95) (rh) */
    unsigned int MBC82:1;                   /**< \brief [18:18] Message Buffer Status Changed 82 (82 = 64-95) (rh) */
    unsigned int MBC83:1;                   /**< \brief [19:19] Message Buffer Status Changed 83 (83 = 64-95) (rh) */
    unsigned int MBC84:1;                   /**< \brief [20:20] Message Buffer Status Changed 84 (84 = 64-95) (rh) */
    unsigned int MBC85:1;                   /**< \brief [21:21] Message Buffer Status Changed 85 (85 = 64-95) (rh) */
    unsigned int MBC86:1;                   /**< \brief [22:22] Message Buffer Status Changed 86 (86 = 64-95) (rh) */
    unsigned int MBC87:1;                   /**< \brief [23:23] Message Buffer Status Changed 87 (87 = 64-95) (rh) */
    unsigned int MBC88:1;                   /**< \brief [24:24] Message Buffer Status Changed 88 (88 = 64-95) (rh) */
    unsigned int MBC89:1;                   /**< \brief [25:25] Message Buffer Status Changed 89 (89 = 64-95) (rh) */
    unsigned int MBC90:1;                   /**< \brief [26:26] Message Buffer Status Changed 90 (90 = 64-95) (rh) */
    unsigned int MBC91:1;                   /**< \brief [27:27] Message Buffer Status Changed 91 (91 = 64-95) (rh) */
    unsigned int MBC92:1;                   /**< \brief [28:28] Message Buffer Status Changed 92 (92 = 64-95) (rh) */
    unsigned int MBC93:1;                   /**< \brief [29:29] Message Buffer Status Changed 93 (93 = 64-95) (rh) */
    unsigned int MBC94:1;                   /**< \brief [30:30] Message Buffer Status Changed 94 (94 = 64-95) (rh) */
    unsigned int MBC95:1;                   /**< \brief [31:31] Message Buffer Status Changed 95 (95 = 64-95) (rh) */
} Ifx_ERAY_MBSC3_Bits;

/** \brief  Message Buffer Status Changed 4 */
typedef struct _Ifx_ERAY_MBSC4_Bits
{
    unsigned int MBC96:1;                   /**< \brief [0:0] Message Buffer Status Changed 96 (96 = 96-127) (rh) */
    unsigned int MBC97:1;                   /**< \brief [1:1] Message Buffer Status Changed 97 (97 = 96-127) (rh) */
    unsigned int MBC98:1;                   /**< \brief [2:2] Message Buffer Status Changed 98 (98 = 96-127) (rh) */
    unsigned int MBC99:1;                   /**< \brief [3:3] Message Buffer Status Changed 99 (99 = 96-127) (rh) */
    unsigned int MBC100:1;                  /**< \brief [4:4] Message Buffer Status Changed 100 (100 = 96-127) (rh) */
    unsigned int MBC101:1;                  /**< \brief [5:5] Message Buffer Status Changed 101 (101 = 96-127) (rh) */
    unsigned int MBC102:1;                  /**< \brief [6:6] Message Buffer Status Changed 102 (102 = 96-127) (rh) */
    unsigned int MBC103:1;                  /**< \brief [7:7] Message Buffer Status Changed 103 (103 = 96-127) (rh) */
    unsigned int MBC104:1;                  /**< \brief [8:8] Message Buffer Status Changed 104 (104 = 96-127) (rh) */
    unsigned int MBC105:1;                  /**< \brief [9:9] Message Buffer Status Changed 105 (105 = 96-127) (rh) */
    unsigned int MBC106:1;                  /**< \brief [10:10] Message Buffer Status Changed 106 (106 = 96-127) (rh) */
    unsigned int MBC107:1;                  /**< \brief [11:11] Message Buffer Status Changed 107 (107 = 96-127) (rh) */
    unsigned int MBC108:1;                  /**< \brief [12:12] Message Buffer Status Changed 108 (108 = 96-127) (rh) */
    unsigned int MBC109:1;                  /**< \brief [13:13] Message Buffer Status Changed 109 (109 = 96-127) (rh) */
    unsigned int MBC110:1;                  /**< \brief [14:14] Message Buffer Status Changed 110 (110 = 96-127) (rh) */
    unsigned int MBC111:1;                  /**< \brief [15:15] Message Buffer Status Changed 111 (111 = 96-127) (rh) */
    unsigned int MBC112:1;                  /**< \brief [16:16] Message Buffer Status Changed 112 (112 = 96-127) (rh) */
    unsigned int MBC113:1;                  /**< \brief [17:17] Message Buffer Status Changed 113 (113 = 96-127) (rh) */
    unsigned int MBC114:1;                  /**< \brief [18:18] Message Buffer Status Changed 114 (114 = 96-127) (rh) */
    unsigned int MBC115:1;                  /**< \brief [19:19] Message Buffer Status Changed 115 (115 = 96-127) (rh) */
    unsigned int MBC116:1;                  /**< \brief [20:20] Message Buffer Status Changed 116 (116 = 96-127) (rh) */
    unsigned int MBC117:1;                  /**< \brief [21:21] Message Buffer Status Changed 117 (117 = 96-127) (rh) */
    unsigned int MBC118:1;                  /**< \brief [22:22] Message Buffer Status Changed 118 (118 = 96-127) (rh) */
    unsigned int MBC119:1;                  /**< \brief [23:23] Message Buffer Status Changed 119 (119 = 96-127) (rh) */
    unsigned int MBC120:1;                  /**< \brief [24:24] Message Buffer Status Changed 120 (120 = 96-127) (rh) */
    unsigned int MBC121:1;                  /**< \brief [25:25] Message Buffer Status Changed 121 (121 = 96-127) (rh) */
    unsigned int MBC122:1;                  /**< \brief [26:26] Message Buffer Status Changed 122 (122 = 96-127) (rh) */
    unsigned int MBC123:1;                  /**< \brief [27:27] Message Buffer Status Changed 123 (123 = 96-127) (rh) */
    unsigned int MBC124:1;                  /**< \brief [28:28] Message Buffer Status Changed 124 (124 = 96-127) (rh) */
    unsigned int MBC125:1;                  /**< \brief [29:29] Message Buffer Status Changed 125 (125 = 96-127) (rh) */
    unsigned int MBC126:1;                  /**< \brief [30:30] Message Buffer Status Changed 126 (126 = 96-127) (rh) */
    unsigned int MBC127:1;                  /**< \brief [31:31] Message Buffer Status Changed 127 (127 = 96-127) (rh) */
} Ifx_ERAY_MBSC4_Bits;

/** \brief  MHD Configuration Register */
typedef struct _Ifx_ERAY_MHDC_Bits
{
    unsigned int SFDL:7;                    /**< \brief [6:0] Static Frame Data Length (gPayloadLengthStatic) (rw) */
    unsigned int reserved_7:9;              /**< \brief \internal Reserved */
    unsigned int SLT:13;                    /**< \brief [28:16] Start of Latest Transmit (pLatestTx) (rw) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_ERAY_MHDC_Bits;

/** \brief  Message Handler Constraints Flags */
typedef struct _Ifx_ERAY_MHDF_Bits
{
    unsigned int SNUA:1;                    /**< \brief [0:0] Status Not Updated Channel A (rwh) */
    unsigned int SNUB:1;                    /**< \brief [1:1] Status Not Updated Channel B (rwh) */
    unsigned int FNFA:1;                    /**< \brief [2:2] Find Sequence Not Finished Channel A (rwh) */
    unsigned int FNFB:1;                    /**< \brief [3:3] Find Sequence Not Finished Channel B (rwh) */
    unsigned int TBFA:1;                    /**< \brief [4:4] Transient Buffer Access Failure A (rwh) */
    unsigned int TBFB:1;                    /**< \brief [5:5] Transient Buffer Access Failure B (rwh) */
    unsigned int TNSA:1;                    /**< \brief [6:6] Transmission Not Started Channel A (rwh) */
    unsigned int TNSB:1;                    /**< \brief [7:7] Transmission Not Started Channel B (rwh) */
    unsigned int WAHP:1;                    /**< \brief [8:8] Write Attempt to Header Partition (rwh) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_ERAY_MHDF_Bits;

/** \brief  Message Handler Status */
typedef struct _Ifx_ERAY_MHDS_Bits
{
    unsigned int EIBF:1;                    /**< \brief [0:0] ECC Error Input Buffer RAM 1,2 (rwh) */
    unsigned int EOBF:1;                    /**< \brief [1:1] ECC Error Output Buffer RAM 1,2 (rwh) */
    unsigned int EMR:1;                     /**< \brief [2:2] ECC Error Message RAM (rwh) */
    unsigned int ETBF1:1;                   /**< \brief [3:3] ECC Error Transient Buffer RAM A (rwh) */
    unsigned int ETBF2:1;                   /**< \brief [4:4] ECC Error Transient Buffer RAM B (rwh) */
    unsigned int FMBD:1;                    /**< \brief [5:5] Faulty Message Buffer Detected (rwh) */
    unsigned int MFMB:1;                    /**< \brief [6:6] Multiple Faulty Message Buffers detected (rwh) */
    unsigned int CRAM:1;                    /**< \brief [7:7] Clear all internal RAM’s (rh) */
    unsigned int FMB:7;                     /**< \brief [14:8] Faulty Message Buffer (rh) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int MBT:7;                     /**< \brief [22:16] Message Buffer Transmitted (rh) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int MBU:7;                     /**< \brief [30:24] Message Buffer Updated (rh) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ERAY_MHDS_Bits;

/** \brief  Message RAM Configuration */
typedef struct _Ifx_ERAY_MRC_Bits
{
    unsigned int FDB:8;                     /**< \brief [7:0] First Dynamic Buffer (rw) */
    unsigned int FFB:8;                     /**< \brief [15:8] First Buffer of FIFO (rw) */
    unsigned int LCB:8;                     /**< \brief [23:16] Last Configured Buffer (rw) */
    unsigned int SEC:2;                     /**< \brief [25:24] Secure Buffers (rw) */
    unsigned int SPLM:1;                    /**< \brief [26:26] SYNC Frame Payload Multiplex (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_MRC_Bits;

/** \brief  Message Buffer Status Changed Interrupt Control 1 */
typedef struct _Ifx_ERAY_MSIC1_Bits
{
    unsigned int MSIP0:1;                   /**< \brief [0:0] Message Buffer Status Changed Interrupt Pointer 0 (0 = 0-31) (rw) */
    unsigned int MSIP1:1;                   /**< \brief [1:1] Message Buffer Status Changed Interrupt Pointer 1 (1 = 0-31) (rw) */
    unsigned int MSIP2:1;                   /**< \brief [2:2] Message Buffer Status Changed Interrupt Pointer 2 (2 = 0-31) (rw) */
    unsigned int MSIP3:1;                   /**< \brief [3:3] Message Buffer Status Changed Interrupt Pointer 3 (3 = 0-31) (rw) */
    unsigned int MSIP4:1;                   /**< \brief [4:4] Message Buffer Status Changed Interrupt Pointer 4 (4 = 0-31) (rw) */
    unsigned int MSIP5:1;                   /**< \brief [5:5] Message Buffer Status Changed Interrupt Pointer 5 (5 = 0-31) (rw) */
    unsigned int MSIP6:1;                   /**< \brief [6:6] Message Buffer Status Changed Interrupt Pointer 6 (6 = 0-31) (rw) */
    unsigned int MSIP7:1;                   /**< \brief [7:7] Message Buffer Status Changed Interrupt Pointer 7 (7 = 0-31) (rw) */
    unsigned int MSIP8:1;                   /**< \brief [8:8] Message Buffer Status Changed Interrupt Pointer 8 (8 = 0-31) (rw) */
    unsigned int MSIP9:1;                   /**< \brief [9:9] Message Buffer Status Changed Interrupt Pointer 9 (9 = 0-31) (rw) */
    unsigned int MSIP10:1;                  /**< \brief [10:10] Message Buffer Status Changed Interrupt Pointer 10 (10 = 0-31) (rw) */
    unsigned int MSIP11:1;                  /**< \brief [11:11] Message Buffer Status Changed Interrupt Pointer 11 (11 = 0-31) (rw) */
    unsigned int MSIP12:1;                  /**< \brief [12:12] Message Buffer Status Changed Interrupt Pointer 12 (12 = 0-31) (rw) */
    unsigned int MSIP13:1;                  /**< \brief [13:13] Message Buffer Status Changed Interrupt Pointer 13 (13 = 0-31) (rw) */
    unsigned int MSIP14:1;                  /**< \brief [14:14] Message Buffer Status Changed Interrupt Pointer 14 (14 = 0-31) (rw) */
    unsigned int MSIP15:1;                  /**< \brief [15:15] Message Buffer Status Changed Interrupt Pointer 15 (15 = 0-31) (rw) */
    unsigned int MSIP16:1;                  /**< \brief [16:16] Message Buffer Status Changed Interrupt Pointer 16 (16 = 0-31) (rw) */
    unsigned int MSIP17:1;                  /**< \brief [17:17] Message Buffer Status Changed Interrupt Pointer 17 (17 = 0-31) (rw) */
    unsigned int MSIP18:1;                  /**< \brief [18:18] Message Buffer Status Changed Interrupt Pointer 18 (18 = 0-31) (rw) */
    unsigned int MSIP19:1;                  /**< \brief [19:19] Message Buffer Status Changed Interrupt Pointer 19 (19 = 0-31) (rw) */
    unsigned int MSIP20:1;                  /**< \brief [20:20] Message Buffer Status Changed Interrupt Pointer 20 (20 = 0-31) (rw) */
    unsigned int MSIP21:1;                  /**< \brief [21:21] Message Buffer Status Changed Interrupt Pointer 21 (21 = 0-31) (rw) */
    unsigned int MSIP22:1;                  /**< \brief [22:22] Message Buffer Status Changed Interrupt Pointer 22 (22 = 0-31) (rw) */
    unsigned int MSIP23:1;                  /**< \brief [23:23] Message Buffer Status Changed Interrupt Pointer 23 (23 = 0-31) (rw) */
    unsigned int MSIP24:1;                  /**< \brief [24:24] Message Buffer Status Changed Interrupt Pointer 24 (24 = 0-31) (rw) */
    unsigned int MSIP25:1;                  /**< \brief [25:25] Message Buffer Status Changed Interrupt Pointer 25 (25 = 0-31) (rw) */
    unsigned int MSIP26:1;                  /**< \brief [26:26] Message Buffer Status Changed Interrupt Pointer 26 (26 = 0-31) (rw) */
    unsigned int MSIP27:1;                  /**< \brief [27:27] Message Buffer Status Changed Interrupt Pointer 27 (27 = 0-31) (rw) */
    unsigned int MSIP28:1;                  /**< \brief [28:28] Message Buffer Status Changed Interrupt Pointer 28 (28 = 0-31) (rw) */
    unsigned int MSIP29:1;                  /**< \brief [29:29] Message Buffer Status Changed Interrupt Pointer 29 (29 = 0-31) (rw) */
    unsigned int MSIP30:1;                  /**< \brief [30:30] Message Buffer Status Changed Interrupt Pointer 30 (30 = 0-31) (rw) */
    unsigned int MSIP31:1;                  /**< \brief [31:31] Message Buffer Status Changed Interrupt Pointer 31 (31 = 0-31) (rw) */
} Ifx_ERAY_MSIC1_Bits;

/** \brief  Message Buffer Status Changed Interrupt Control 2 */
typedef struct _Ifx_ERAY_MSIC2_Bits
{
    unsigned int MSIP32:1;                  /**< \brief [0:0] Message Buffer Status Changed Interrupt Pointer 32 (32 = 32-63) (rh) */
    unsigned int MSIP33:1;                  /**< \brief [1:1] Message Buffer Status Changed Interrupt Pointer 33 (33 = 32-63) (rh) */
    unsigned int MSIP34:1;                  /**< \brief [2:2] Message Buffer Status Changed Interrupt Pointer 34 (34 = 32-63) (rh) */
    unsigned int MSIP35:1;                  /**< \brief [3:3] Message Buffer Status Changed Interrupt Pointer 35 (35 = 32-63) (rh) */
    unsigned int MSIP36:1;                  /**< \brief [4:4] Message Buffer Status Changed Interrupt Pointer 36 (36 = 32-63) (rh) */
    unsigned int MSIP37:1;                  /**< \brief [5:5] Message Buffer Status Changed Interrupt Pointer 37 (37 = 32-63) (rh) */
    unsigned int MSIP38:1;                  /**< \brief [6:6] Message Buffer Status Changed Interrupt Pointer 38 (38 = 32-63) (rh) */
    unsigned int MSIP39:1;                  /**< \brief [7:7] Message Buffer Status Changed Interrupt Pointer 39 (39 = 32-63) (rh) */
    unsigned int MSIP40:1;                  /**< \brief [8:8] Message Buffer Status Changed Interrupt Pointer 40 (40 = 32-63) (rh) */
    unsigned int MSIP41:1;                  /**< \brief [9:9] Message Buffer Status Changed Interrupt Pointer 41 (41 = 32-63) (rh) */
    unsigned int MSIP42:1;                  /**< \brief [10:10] Message Buffer Status Changed Interrupt Pointer 42 (42 = 32-63) (rh) */
    unsigned int MSIP43:1;                  /**< \brief [11:11] Message Buffer Status Changed Interrupt Pointer 43 (43 = 32-63) (rh) */
    unsigned int MSIP44:1;                  /**< \brief [12:12] Message Buffer Status Changed Interrupt Pointer 44 (44 = 32-63) (rh) */
    unsigned int MSIP45:1;                  /**< \brief [13:13] Message Buffer Status Changed Interrupt Pointer 45 (45 = 32-63) (rh) */
    unsigned int MSIP46:1;                  /**< \brief [14:14] Message Buffer Status Changed Interrupt Pointer 46 (46 = 32-63) (rh) */
    unsigned int MSIP47:1;                  /**< \brief [15:15] Message Buffer Status Changed Interrupt Pointer 47 (47 = 32-63) (rh) */
    unsigned int MSIP48:1;                  /**< \brief [16:16] Message Buffer Status Changed Interrupt Pointer 48 (48 = 32-63) (rh) */
    unsigned int MSIP49:1;                  /**< \brief [17:17] Message Buffer Status Changed Interrupt Pointer 49 (49 = 32-63) (rh) */
    unsigned int MSIP50:1;                  /**< \brief [18:18] Message Buffer Status Changed Interrupt Pointer 50 (50 = 32-63) (rh) */
    unsigned int MSIP51:1;                  /**< \brief [19:19] Message Buffer Status Changed Interrupt Pointer 51 (51 = 32-63) (rh) */
    unsigned int MSIP52:1;                  /**< \brief [20:20] Message Buffer Status Changed Interrupt Pointer 52 (52 = 32-63) (rh) */
    unsigned int MSIP53:1;                  /**< \brief [21:21] Message Buffer Status Changed Interrupt Pointer 53 (53 = 32-63) (rh) */
    unsigned int MSIP54:1;                  /**< \brief [22:22] Message Buffer Status Changed Interrupt Pointer 54 (54 = 32-63) (rh) */
    unsigned int MSIP55:1;                  /**< \brief [23:23] Message Buffer Status Changed Interrupt Pointer 55 (55 = 32-63) (rh) */
    unsigned int MSIP56:1;                  /**< \brief [24:24] Message Buffer Status Changed Interrupt Pointer 56 (56 = 32-63) (rh) */
    unsigned int MSIP57:1;                  /**< \brief [25:25] Message Buffer Status Changed Interrupt Pointer 57 (57 = 32-63) (rh) */
    unsigned int MSIP58:1;                  /**< \brief [26:26] Message Buffer Status Changed Interrupt Pointer 58 (58 = 32-63) (rh) */
    unsigned int MSIP59:1;                  /**< \brief [27:27] Message Buffer Status Changed Interrupt Pointer 59 (59 = 32-63) (rh) */
    unsigned int MSIP60:1;                  /**< \brief [28:28] Message Buffer Status Changed Interrupt Pointer 60 (60 = 32-63) (rh) */
    unsigned int MSIP61:1;                  /**< \brief [29:29] Message Buffer Status Changed Interrupt Pointer 61 (61 = 32-63) (rh) */
    unsigned int MSIP62:1;                  /**< \brief [30:30] Message Buffer Status Changed Interrupt Pointer 62 (62 = 32-63) (rh) */
    unsigned int MSIP63:1;                  /**< \brief [31:31] Message Buffer Status Changed Interrupt Pointer 63 (63 = 32-63) (rh) */
} Ifx_ERAY_MSIC2_Bits;

/** \brief  Message Buffer Status Changed Interrupt Control 3 */
typedef struct _Ifx_ERAY_MSIC3_Bits
{
    unsigned int MSIP64:1;                  /**< \brief [0:0] Message Buffer Status Changed Interrupt Pointer 64 (64 = 64-95) (rw) */
    unsigned int MSIP65:1;                  /**< \brief [1:1] Message Buffer Status Changed Interrupt Pointer 65 (65 = 64-95) (rw) */
    unsigned int MSIP66:1;                  /**< \brief [2:2] Message Buffer Status Changed Interrupt Pointer 66 (66 = 64-95) (rw) */
    unsigned int MSIP67:1;                  /**< \brief [3:3] Message Buffer Status Changed Interrupt Pointer 67 (67 = 64-95) (rw) */
    unsigned int MSIP68:1;                  /**< \brief [4:4] Message Buffer Status Changed Interrupt Pointer 68 (68 = 64-95) (rw) */
    unsigned int MSIP69:1;                  /**< \brief [5:5] Message Buffer Status Changed Interrupt Pointer 69 (69 = 64-95) (rw) */
    unsigned int MSIP70:1;                  /**< \brief [6:6] Message Buffer Status Changed Interrupt Pointer 70 (70 = 64-95) (rw) */
    unsigned int MSIP71:1;                  /**< \brief [7:7] Message Buffer Status Changed Interrupt Pointer 71 (71 = 64-95) (rw) */
    unsigned int MSIP72:1;                  /**< \brief [8:8] Message Buffer Status Changed Interrupt Pointer 72 (72 = 64-95) (rw) */
    unsigned int MSIP73:1;                  /**< \brief [9:9] Message Buffer Status Changed Interrupt Pointer 73 (73 = 64-95) (rw) */
    unsigned int MSIP74:1;                  /**< \brief [10:10] Message Buffer Status Changed Interrupt Pointer 74 (74 = 64-95) (rw) */
    unsigned int MSIP75:1;                  /**< \brief [11:11] Message Buffer Status Changed Interrupt Pointer 75 (75 = 64-95) (rw) */
    unsigned int MSIP76:1;                  /**< \brief [12:12] Message Buffer Status Changed Interrupt Pointer 76 (76 = 64-95) (rw) */
    unsigned int MSIP77:1;                  /**< \brief [13:13] Message Buffer Status Changed Interrupt Pointer 77 (77 = 64-95) (rw) */
    unsigned int MSIP78:1;                  /**< \brief [14:14] Message Buffer Status Changed Interrupt Pointer 78 (78 = 64-95) (rw) */
    unsigned int MSIP79:1;                  /**< \brief [15:15] Message Buffer Status Changed Interrupt Pointer 79 (79 = 64-95) (rw) */
    unsigned int MSIP80:1;                  /**< \brief [16:16] Message Buffer Status Changed Interrupt Pointer 80 (80 = 64-95) (rw) */
    unsigned int MSIP81:1;                  /**< \brief [17:17] Message Buffer Status Changed Interrupt Pointer 81 (81 = 64-95) (rw) */
    unsigned int MSIP82:1;                  /**< \brief [18:18] Message Buffer Status Changed Interrupt Pointer 82 (82 = 64-95) (rw) */
    unsigned int MSIP83:1;                  /**< \brief [19:19] Message Buffer Status Changed Interrupt Pointer 83 (83 = 64-95) (rw) */
    unsigned int MSIP84:1;                  /**< \brief [20:20] Message Buffer Status Changed Interrupt Pointer 84 (84 = 64-95) (rw) */
    unsigned int MSIP85:1;                  /**< \brief [21:21] Message Buffer Status Changed Interrupt Pointer 85 (85 = 64-95) (rw) */
    unsigned int MSIP86:1;                  /**< \brief [22:22] Message Buffer Status Changed Interrupt Pointer 86 (86 = 64-95) (rw) */
    unsigned int MSIP87:1;                  /**< \brief [23:23] Message Buffer Status Changed Interrupt Pointer 87 (87 = 64-95) (rw) */
    unsigned int MSIP88:1;                  /**< \brief [24:24] Message Buffer Status Changed Interrupt Pointer 88 (88 = 64-95) (rw) */
    unsigned int MSIP89:1;                  /**< \brief [25:25] Message Buffer Status Changed Interrupt Pointer 89 (89 = 64-95) (rw) */
    unsigned int MSIP90:1;                  /**< \brief [26:26] Message Buffer Status Changed Interrupt Pointer 90 (90 = 64-95) (rw) */
    unsigned int MSIP91:1;                  /**< \brief [27:27] Message Buffer Status Changed Interrupt Pointer 91 (91 = 64-95) (rw) */
    unsigned int MSIP92:1;                  /**< \brief [28:28] Message Buffer Status Changed Interrupt Pointer 92 (92 = 64-95) (rw) */
    unsigned int MSIP93:1;                  /**< \brief [29:29] Message Buffer Status Changed Interrupt Pointer 93 (93 = 64-95) (rw) */
    unsigned int MSIP94:1;                  /**< \brief [30:30] Message Buffer Status Changed Interrupt Pointer 94 (94 = 64-95) (rw) */
    unsigned int MSIP95:1;                  /**< \brief [31:31] Message Buffer Status Changed Interrupt Pointer 95 (95 = 64-95) (rw) */
} Ifx_ERAY_MSIC3_Bits;

/** \brief  Message Buffer Status Changed Interrupt Control 4 */
typedef struct _Ifx_ERAY_MSIC4_Bits
{
    unsigned int MSIP96:1;                  /**< \brief [0:0] Message Buffer Status Changed Interrupt Pointer 96 (96 = 96-127) (rw) */
    unsigned int MSIP97:1;                  /**< \brief [1:1] Message Buffer Status Changed Interrupt Pointer 97 (97 = 96-127) (rw) */
    unsigned int MSIP98:1;                  /**< \brief [2:2] Message Buffer Status Changed Interrupt Pointer 98 (98 = 96-127) (rw) */
    unsigned int MSIP99:1;                  /**< \brief [3:3] Message Buffer Status Changed Interrupt Pointer 99 (99 = 96-127) (rw) */
    unsigned int MSIP100:1;                 /**< \brief [4:4] Message Buffer Status Changed Interrupt Pointer 100 (100 = 96-127) (rw) */
    unsigned int MSIP101:1;                 /**< \brief [5:5] Message Buffer Status Changed Interrupt Pointer 101 (101 = 96-127) (rw) */
    unsigned int MSIP102:1;                 /**< \brief [6:6] Message Buffer Status Changed Interrupt Pointer 102 (102 = 96-127) (rw) */
    unsigned int MSIP103:1;                 /**< \brief [7:7] Message Buffer Status Changed Interrupt Pointer 103 (103 = 96-127) (rw) */
    unsigned int MSIP104:1;                 /**< \brief [8:8] Message Buffer Status Changed Interrupt Pointer 104 (104 = 96-127) (rw) */
    unsigned int MSIP105:1;                 /**< \brief [9:9] Message Buffer Status Changed Interrupt Pointer 105 (105 = 96-127) (rw) */
    unsigned int MSIP106:1;                 /**< \brief [10:10] Message Buffer Status Changed Interrupt Pointer 106 (106 = 96-127) (rw) */
    unsigned int MSIP107:1;                 /**< \brief [11:11] Message Buffer Status Changed Interrupt Pointer 107 (107 = 96-127) (rw) */
    unsigned int MSIP108:1;                 /**< \brief [12:12] Message Buffer Status Changed Interrupt Pointer 108 (108 = 96-127) (rw) */
    unsigned int MSIP109:1;                 /**< \brief [13:13] Message Buffer Status Changed Interrupt Pointer 109 (109 = 96-127) (rw) */
    unsigned int MSIP110:1;                 /**< \brief [14:14] Message Buffer Status Changed Interrupt Pointer 110 (110 = 96-127) (rw) */
    unsigned int MSIP111:1;                 /**< \brief [15:15] Message Buffer Status Changed Interrupt Pointer 111 (111 = 96-127) (rw) */
    unsigned int MSIP112:1;                 /**< \brief [16:16] Message Buffer Status Changed Interrupt Pointer 112 (112 = 96-127) (rw) */
    unsigned int MSIP113:1;                 /**< \brief [17:17] Message Buffer Status Changed Interrupt Pointer 113 (113 = 96-127) (rw) */
    unsigned int MSIP114:1;                 /**< \brief [18:18] Message Buffer Status Changed Interrupt Pointer 114 (114 = 96-127) (rw) */
    unsigned int MSIP115:1;                 /**< \brief [19:19] Message Buffer Status Changed Interrupt Pointer 115 (115 = 96-127) (rw) */
    unsigned int MSIP116:1;                 /**< \brief [20:20] Message Buffer Status Changed Interrupt Pointer 116 (116 = 96-127) (rw) */
    unsigned int MSIP117:1;                 /**< \brief [21:21] Message Buffer Status Changed Interrupt Pointer 117 (117 = 96-127) (rw) */
    unsigned int MSIP118:1;                 /**< \brief [22:22] Message Buffer Status Changed Interrupt Pointer 118 (118 = 96-127) (rw) */
    unsigned int MSIP119:1;                 /**< \brief [23:23] Message Buffer Status Changed Interrupt Pointer 119 (119 = 96-127) (rw) */
    unsigned int MSIP120:1;                 /**< \brief [24:24] Message Buffer Status Changed Interrupt Pointer 120 (120 = 96-127) (rw) */
    unsigned int MSIP121:1;                 /**< \brief [25:25] Message Buffer Status Changed Interrupt Pointer 121 (121 = 96-127) (rw) */
    unsigned int MSIP122:1;                 /**< \brief [26:26] Message Buffer Status Changed Interrupt Pointer 122 (122 = 96-127) (rw) */
    unsigned int MSIP123:1;                 /**< \brief [27:27] Message Buffer Status Changed Interrupt Pointer 123 (123 = 96-127) (rw) */
    unsigned int MSIP124:1;                 /**< \brief [28:28] Message Buffer Status Changed Interrupt Pointer 124 (124 = 96-127) (rw) */
    unsigned int MSIP125:1;                 /**< \brief [29:29] Message Buffer Status Changed Interrupt Pointer 125 (125 = 96-127) (rw) */
    unsigned int MSIP126:1;                 /**< \brief [30:30] Message Buffer Status Changed Interrupt Pointer 126 (126 = 96-127) (rw) */
    unsigned int MSIP127:1;                 /**< \brief [31:31] Message Buffer Status Changed Interrupt Pointer 127 (127 = 96-127) (rw) */
} Ifx_ERAY_MSIC4_Bits;

/** \brief  Macrotick and Cycle Counter Value */
typedef struct _Ifx_ERAY_MTCCV_Bits
{
    unsigned int MTV:14;                    /**< \brief [13:0] Macrotick Value (vMacrotick) (rh) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int CCV:6;                     /**< \brief [21:16] Cycle Counter Value (vCycleCounter) (rh) */
    unsigned int reserved_22:10;            /**< \brief \internal Reserved */
} Ifx_ERAY_MTCCV_Bits;

/** \brief  New Data Register 1 */
typedef struct _Ifx_ERAY_NDAT1_Bits
{
    unsigned int ND0:1;                     /**< \brief [0:0] New Data 0 (0 = 0-31) (rh) */
    unsigned int ND1:1;                     /**< \brief [1:1] New Data 1 (1 = 0-31) (rh) */
    unsigned int ND2:1;                     /**< \brief [2:2] New Data 2 (2 = 0-31) (rh) */
    unsigned int ND3:1;                     /**< \brief [3:3] New Data 3 (3 = 0-31) (rh) */
    unsigned int ND4:1;                     /**< \brief [4:4] New Data 4 (4 = 0-31) (rh) */
    unsigned int ND5:1;                     /**< \brief [5:5] New Data 5 (5 = 0-31) (rh) */
    unsigned int ND6:1;                     /**< \brief [6:6] New Data 6 (6 = 0-31) (rh) */
    unsigned int ND7:1;                     /**< \brief [7:7] New Data 7 (7 = 0-31) (rh) */
    unsigned int ND8:1;                     /**< \brief [8:8] New Data 8 (8 = 0-31) (rh) */
    unsigned int ND9:1;                     /**< \brief [9:9] New Data 9 (9 = 0-31) (rh) */
    unsigned int ND10:1;                    /**< \brief [10:10] New Data 10 (10 = 0-31) (rh) */
    unsigned int ND11:1;                    /**< \brief [11:11] New Data 11 (11 = 0-31) (rh) */
    unsigned int ND12:1;                    /**< \brief [12:12] New Data 12 (12 = 0-31) (rh) */
    unsigned int ND13:1;                    /**< \brief [13:13] New Data 13 (13 = 0-31) (rh) */
    unsigned int ND14:1;                    /**< \brief [14:14] New Data 14 (14 = 0-31) (rh) */
    unsigned int ND15:1;                    /**< \brief [15:15] New Data 15 (15 = 0-31) (rh) */
    unsigned int ND16:1;                    /**< \brief [16:16] New Data 16 (16 = 0-31) (rh) */
    unsigned int ND17:1;                    /**< \brief [17:17] New Data 17 (17 = 0-31) (rh) */
    unsigned int ND18:1;                    /**< \brief [18:18] New Data 18 (18 = 0-31) (rh) */
    unsigned int ND19:1;                    /**< \brief [19:19] New Data 19 (19 = 0-31) (rh) */
    unsigned int ND20:1;                    /**< \brief [20:20] New Data 20 (20 = 0-31) (rh) */
    unsigned int ND21:1;                    /**< \brief [21:21] New Data 21 (21 = 0-31) (rh) */
    unsigned int ND22:1;                    /**< \brief [22:22] New Data 22 (22 = 0-31) (rh) */
    unsigned int ND23:1;                    /**< \brief [23:23] New Data 23 (23 = 0-31) (rh) */
    unsigned int ND24:1;                    /**< \brief [24:24] New Data 24 (24 = 0-31) (rh) */
    unsigned int ND25:1;                    /**< \brief [25:25] New Data 25 (25 = 0-31) (rh) */
    unsigned int ND26:1;                    /**< \brief [26:26] New Data 26 (26 = 0-31) (rh) */
    unsigned int ND27:1;                    /**< \brief [27:27] New Data 27 (27 = 0-31) (rh) */
    unsigned int ND28:1;                    /**< \brief [28:28] New Data 28 (28 = 0-31) (rh) */
    unsigned int ND29:1;                    /**< \brief [29:29] New Data 29 (29 = 0-31) (rh) */
    unsigned int ND30:1;                    /**< \brief [30:30] New Data 30 (30 = 0-31) (rh) */
    unsigned int ND31:1;                    /**< \brief [31:31] New Data 31 (31 = 0-31) (rh) */
} Ifx_ERAY_NDAT1_Bits;

/** \brief  New Data Register 2 */
typedef struct _Ifx_ERAY_NDAT2_Bits
{
    unsigned int ND32:1;                    /**< \brief [0:0] New Data 32 (32 = 32-63) (rh) */
    unsigned int ND33:1;                    /**< \brief [1:1] New Data 33 (33 = 32-63) (rh) */
    unsigned int ND34:1;                    /**< \brief [2:2] New Data 34 (34 = 32-63) (rh) */
    unsigned int ND35:1;                    /**< \brief [3:3] New Data 35 (35 = 32-63) (rh) */
    unsigned int ND36:1;                    /**< \brief [4:4] New Data 36 (36 = 32-63) (rh) */
    unsigned int ND37:1;                    /**< \brief [5:5] New Data 37 (37 = 32-63) (rh) */
    unsigned int ND38:1;                    /**< \brief [6:6] New Data 38 (38 = 32-63) (rh) */
    unsigned int ND39:1;                    /**< \brief [7:7] New Data 39 (39 = 32-63) (rh) */
    unsigned int ND40:1;                    /**< \brief [8:8] New Data 40 (40 = 32-63) (rh) */
    unsigned int ND41:1;                    /**< \brief [9:9] New Data 41 (41 = 32-63) (rh) */
    unsigned int ND42:1;                    /**< \brief [10:10] New Data 42 (42 = 32-63) (rh) */
    unsigned int ND43:1;                    /**< \brief [11:11] New Data 43 (43 = 32-63) (rh) */
    unsigned int ND44:1;                    /**< \brief [12:12] New Data 44 (44 = 32-63) (rh) */
    unsigned int ND45:1;                    /**< \brief [13:13] New Data 45 (45 = 32-63) (rh) */
    unsigned int ND46:1;                    /**< \brief [14:14] New Data 46 (46 = 32-63) (rh) */
    unsigned int ND47:1;                    /**< \brief [15:15] New Data 47 (47 = 32-63) (rh) */
    unsigned int ND48:1;                    /**< \brief [16:16] New Data 48 (48 = 32-63) (rh) */
    unsigned int ND49:1;                    /**< \brief [17:17] New Data 49 (49 = 32-63) (rh) */
    unsigned int ND50:1;                    /**< \brief [18:18] New Data 50 (50 = 32-63) (rh) */
    unsigned int ND51:1;                    /**< \brief [19:19] New Data 51 (51 = 32-63) (rh) */
    unsigned int ND52:1;                    /**< \brief [20:20] New Data 52 (52 = 32-63) (rh) */
    unsigned int ND53:1;                    /**< \brief [21:21] New Data 53 (53 = 32-63) (rh) */
    unsigned int ND54:1;                    /**< \brief [22:22] New Data 54 (54 = 32-63) (rh) */
    unsigned int ND55:1;                    /**< \brief [23:23] New Data 55 (55 = 32-63) (rh) */
    unsigned int ND56:1;                    /**< \brief [24:24] New Data 56 (56 = 32-63) (rh) */
    unsigned int ND57:1;                    /**< \brief [25:25] New Data 57 (57 = 32-63) (rh) */
    unsigned int ND58:1;                    /**< \brief [26:26] New Data 58 (58 = 32-63) (rh) */
    unsigned int ND59:1;                    /**< \brief [27:27] New Data 59 (59 = 32-63) (rh) */
    unsigned int ND60:1;                    /**< \brief [28:28] New Data 60 (60 = 32-63) (rh) */
    unsigned int ND61:1;                    /**< \brief [29:29] New Data 61 (61 = 32-63) (rh) */
    unsigned int ND62:1;                    /**< \brief [30:30] New Data 62 (62 = 32-63) (rh) */
    unsigned int ND63:1;                    /**< \brief [31:31] New Data 63 (63 = 32-63) (rh) */
} Ifx_ERAY_NDAT2_Bits;

/** \brief  New Data Register 3 */
typedef struct _Ifx_ERAY_NDAT3_Bits
{
    unsigned int ND64:1;                    /**< \brief [0:0] New Data 64 (64 = 64-95) (rh) */
    unsigned int ND65:1;                    /**< \brief [1:1] New Data 65 (65 = 64-95) (rh) */
    unsigned int ND66:1;                    /**< \brief [2:2] New Data 66 (66 = 64-95) (rh) */
    unsigned int ND67:1;                    /**< \brief [3:3] New Data 67 (67 = 64-95) (rh) */
    unsigned int ND68:1;                    /**< \brief [4:4] New Data 68 (68 = 64-95) (rh) */
    unsigned int ND69:1;                    /**< \brief [5:5] New Data 69 (69 = 64-95) (rh) */
    unsigned int ND70:1;                    /**< \brief [6:6] New Data 70 (70 = 64-95) (rh) */
    unsigned int ND71:1;                    /**< \brief [7:7] New Data 71 (71 = 64-95) (rh) */
    unsigned int ND72:1;                    /**< \brief [8:8] New Data 72 (72 = 64-95) (rh) */
    unsigned int ND73:1;                    /**< \brief [9:9] New Data 73 (73 = 64-95) (rh) */
    unsigned int ND74:1;                    /**< \brief [10:10] New Data 74 (74 = 64-95) (rh) */
    unsigned int ND75:1;                    /**< \brief [11:11] New Data 75 (75 = 64-95) (rh) */
    unsigned int ND76:1;                    /**< \brief [12:12] New Data 76 (76 = 64-95) (rh) */
    unsigned int ND77:1;                    /**< \brief [13:13] New Data 77 (77 = 64-95) (rh) */
    unsigned int ND78:1;                    /**< \brief [14:14] New Data 78 (78 = 64-95) (rh) */
    unsigned int ND79:1;                    /**< \brief [15:15] New Data 79 (79 = 64-95) (rh) */
    unsigned int ND80:1;                    /**< \brief [16:16] New Data 80 (80 = 64-95) (rh) */
    unsigned int ND81:1;                    /**< \brief [17:17] New Data 81 (81 = 64-95) (rh) */
    unsigned int ND82:1;                    /**< \brief [18:18] New Data 82 (82 = 64-95) (rh) */
    unsigned int ND83:1;                    /**< \brief [19:19] New Data 83 (83 = 64-95) (rh) */
    unsigned int ND84:1;                    /**< \brief [20:20] New Data 84 (84 = 64-95) (rh) */
    unsigned int ND85:1;                    /**< \brief [21:21] New Data 85 (85 = 64-95) (rh) */
    unsigned int ND86:1;                    /**< \brief [22:22] New Data 86 (86 = 64-95) (rh) */
    unsigned int ND87:1;                    /**< \brief [23:23] New Data 87 (87 = 64-95) (rh) */
    unsigned int ND88:1;                    /**< \brief [24:24] New Data 88 (88 = 64-95) (rh) */
    unsigned int ND89:1;                    /**< \brief [25:25] New Data 89 (89 = 64-95) (rh) */
    unsigned int ND90:1;                    /**< \brief [26:26] New Data 90 (90 = 64-95) (rh) */
    unsigned int ND91:1;                    /**< \brief [27:27] New Data 91 (91 = 64-95) (rh) */
    unsigned int ND92:1;                    /**< \brief [28:28] New Data 92 (92 = 64-95) (rh) */
    unsigned int ND93:1;                    /**< \brief [29:29] New Data 93 (93 = 64-95) (rh) */
    unsigned int ND94:1;                    /**< \brief [30:30] New Data 94 (94 = 64-95) (rh) */
    unsigned int ND95:1;                    /**< \brief [31:31] New Data 95 (95 = 64-95) (rh) */
} Ifx_ERAY_NDAT3_Bits;

/** \brief  New Data Register 4 */
typedef struct _Ifx_ERAY_NDAT4_Bits
{
    unsigned int ND96:1;                    /**< \brief [0:0] New Data 96 (96 = 96-127) (rh) */
    unsigned int ND97:1;                    /**< \brief [1:1] New Data 97 (97 = 96-127) (rh) */
    unsigned int ND98:1;                    /**< \brief [2:2] New Data 98 (98 = 96-127) (rh) */
    unsigned int ND99:1;                    /**< \brief [3:3] New Data 99 (99 = 96-127) (rh) */
    unsigned int ND100:1;                   /**< \brief [4:4] New Data 100 (100 = 96-127) (rh) */
    unsigned int ND101:1;                   /**< \brief [5:5] New Data 101 (101 = 96-127) (rh) */
    unsigned int ND102:1;                   /**< \brief [6:6] New Data 102 (102 = 96-127) (rh) */
    unsigned int ND103:1;                   /**< \brief [7:7] New Data 103 (103 = 96-127) (rh) */
    unsigned int ND104:1;                   /**< \brief [8:8] New Data 104 (104 = 96-127) (rh) */
    unsigned int ND105:1;                   /**< \brief [9:9] New Data 105 (105 = 96-127) (rh) */
    unsigned int ND106:1;                   /**< \brief [10:10] New Data 106 (106 = 96-127) (rh) */
    unsigned int ND107:1;                   /**< \brief [11:11] New Data 107 (107 = 96-127) (rh) */
    unsigned int ND108:1;                   /**< \brief [12:12] New Data 108 (108 = 96-127) (rh) */
    unsigned int ND109:1;                   /**< \brief [13:13] New Data 109 (109 = 96-127) (rh) */
    unsigned int ND110:1;                   /**< \brief [14:14] New Data 110 (110 = 96-127) (rh) */
    unsigned int ND111:1;                   /**< \brief [15:15] New Data 111 (111 = 96-127) (rh) */
    unsigned int ND112:1;                   /**< \brief [16:16] New Data 112 (112 = 96-127) (rh) */
    unsigned int ND113:1;                   /**< \brief [17:17] New Data 113 (113 = 96-127) (rh) */
    unsigned int ND114:1;                   /**< \brief [18:18] New Data 114 (114 = 96-127) (rh) */
    unsigned int ND115:1;                   /**< \brief [19:19] New Data 115 (115 = 96-127) (rh) */
    unsigned int ND116:1;                   /**< \brief [20:20] New Data 116 (116 = 96-127) (rh) */
    unsigned int ND117:1;                   /**< \brief [21:21] New Data 117 (117 = 96-127) (rh) */
    unsigned int ND118:1;                   /**< \brief [22:22] New Data 118 (118 = 96-127) (rh) */
    unsigned int ND119:1;                   /**< \brief [23:23] New Data 119 (119 = 96-127) (rh) */
    unsigned int ND120:1;                   /**< \brief [24:24] New Data 120 (120 = 96-127) (rh) */
    unsigned int ND121:1;                   /**< \brief [25:25] New Data 121 (121 = 96-127) (rh) */
    unsigned int ND122:1;                   /**< \brief [26:26] New Data 122 (122 = 96-127) (rh) */
    unsigned int ND123:1;                   /**< \brief [27:27] New Data 123 (123 = 96-127) (rh) */
    unsigned int ND124:1;                   /**< \brief [28:28] New Data 124 (124 = 96-127) (rh) */
    unsigned int ND125:1;                   /**< \brief [29:29] New Data 125 (125 = 96-127) (rh) */
    unsigned int ND126:1;                   /**< \brief [30:30] New Data 126 (126 = 96-127) (rh) */
    unsigned int ND127:1;                   /**< \brief [31:31] New Data 127 (127 = 96-127) (rh) */
} Ifx_ERAY_NDAT4_Bits;

/** \brief  New Data Interrupt Control 1 */
typedef struct _Ifx_ERAY_NDIC1_Bits
{
    unsigned int NDIP0:1;                   /**< \brief [0:0] New Data Interrupt Pointer 0 (0 = 0-31) (rw) */
    unsigned int NDIP1:1;                   /**< \brief [1:1] New Data Interrupt Pointer 1 (1 = 0-31) (rw) */
    unsigned int NDIP2:1;                   /**< \brief [2:2] New Data Interrupt Pointer 2 (2 = 0-31) (rw) */
    unsigned int NDIP3:1;                   /**< \brief [3:3] New Data Interrupt Pointer 3 (3 = 0-31) (rw) */
    unsigned int NDIP4:1;                   /**< \brief [4:4] New Data Interrupt Pointer 4 (4 = 0-31) (rw) */
    unsigned int NDIP5:1;                   /**< \brief [5:5] New Data Interrupt Pointer 5 (5 = 0-31) (rw) */
    unsigned int NDIP6:1;                   /**< \brief [6:6] New Data Interrupt Pointer 6 (6 = 0-31) (rw) */
    unsigned int NDIP7:1;                   /**< \brief [7:7] New Data Interrupt Pointer 7 (7 = 0-31) (rw) */
    unsigned int NDIP8:1;                   /**< \brief [8:8] New Data Interrupt Pointer 8 (8 = 0-31) (rw) */
    unsigned int NDIP9:1;                   /**< \brief [9:9] New Data Interrupt Pointer 9 (9 = 0-31) (rw) */
    unsigned int NDIP10:1;                  /**< \brief [10:10] New Data Interrupt Pointer 10 (10 = 0-31) (rw) */
    unsigned int NDIP11:1;                  /**< \brief [11:11] New Data Interrupt Pointer 11 (11 = 0-31) (rw) */
    unsigned int NDIP12:1;                  /**< \brief [12:12] New Data Interrupt Pointer 12 (12 = 0-31) (rw) */
    unsigned int NDIP13:1;                  /**< \brief [13:13] New Data Interrupt Pointer 13 (13 = 0-31) (rw) */
    unsigned int NDIP14:1;                  /**< \brief [14:14] New Data Interrupt Pointer 14 (14 = 0-31) (rw) */
    unsigned int NDIP15:1;                  /**< \brief [15:15] New Data Interrupt Pointer 15 (15 = 0-31) (rw) */
    unsigned int NDIP16:1;                  /**< \brief [16:16] New Data Interrupt Pointer 16 (16 = 0-31) (rw) */
    unsigned int NDIP17:1;                  /**< \brief [17:17] New Data Interrupt Pointer 17 (17 = 0-31) (rw) */
    unsigned int NDIP18:1;                  /**< \brief [18:18] New Data Interrupt Pointer 18 (18 = 0-31) (rw) */
    unsigned int NDIP19:1;                  /**< \brief [19:19] New Data Interrupt Pointer 19 (19 = 0-31) (rw) */
    unsigned int NDIP20:1;                  /**< \brief [20:20] New Data Interrupt Pointer 20 (20 = 0-31) (rw) */
    unsigned int NDIP21:1;                  /**< \brief [21:21] New Data Interrupt Pointer 21 (21 = 0-31) (rw) */
    unsigned int NDIP22:1;                  /**< \brief [22:22] New Data Interrupt Pointer 22 (22 = 0-31) (rw) */
    unsigned int NDIP23:1;                  /**< \brief [23:23] New Data Interrupt Pointer 23 (23 = 0-31) (rw) */
    unsigned int NDIP24:1;                  /**< \brief [24:24] New Data Interrupt Pointer 24 (24 = 0-31) (rw) */
    unsigned int NDIP25:1;                  /**< \brief [25:25] New Data Interrupt Pointer 25 (25 = 0-31) (rw) */
    unsigned int NDIP26:1;                  /**< \brief [26:26] New Data Interrupt Pointer 26 (26 = 0-31) (rw) */
    unsigned int NDIP27:1;                  /**< \brief [27:27] New Data Interrupt Pointer 27 (27 = 0-31) (rw) */
    unsigned int NDIP28:1;                  /**< \brief [28:28] New Data Interrupt Pointer 28 (28 = 0-31) (rw) */
    unsigned int NDIP29:1;                  /**< \brief [29:29] New Data Interrupt Pointer 29 (29 = 0-31) (rw) */
    unsigned int NDIP30:1;                  /**< \brief [30:30] New Data Interrupt Pointer 30 (30 = 0-31) (rw) */
    unsigned int NDIP31:1;                  /**< \brief [31:31] New Data Interrupt Pointer 31 (31 = 0-31) (rw) */
} Ifx_ERAY_NDIC1_Bits;

/** \brief  New Data Interrupt Control 2 */
typedef struct _Ifx_ERAY_NDIC2_Bits
{
    unsigned int NDIP32:1;                  /**< \brief [0:0] New Data Interrupt Pointer 32 (32 = 32-63) (rw) */
    unsigned int NDIP33:1;                  /**< \brief [1:1] New Data Interrupt Pointer 33 (33 = 32-63) (rw) */
    unsigned int NDIP34:1;                  /**< \brief [2:2] New Data Interrupt Pointer 34 (34 = 32-63) (rw) */
    unsigned int NDIP35:1;                  /**< \brief [3:3] New Data Interrupt Pointer 35 (35 = 32-63) (rw) */
    unsigned int NDIP36:1;                  /**< \brief [4:4] New Data Interrupt Pointer 36 (36 = 32-63) (rw) */
    unsigned int NDIP37:1;                  /**< \brief [5:5] New Data Interrupt Pointer 37 (37 = 32-63) (rw) */
    unsigned int NDIP38:1;                  /**< \brief [6:6] New Data Interrupt Pointer 38 (38 = 32-63) (rw) */
    unsigned int NDIP39:1;                  /**< \brief [7:7] New Data Interrupt Pointer 39 (39 = 32-63) (rw) */
    unsigned int NDIP40:1;                  /**< \brief [8:8] New Data Interrupt Pointer 40 (40 = 32-63) (rw) */
    unsigned int NDIP41:1;                  /**< \brief [9:9] New Data Interrupt Pointer 41 (41 = 32-63) (rw) */
    unsigned int NDIP42:1;                  /**< \brief [10:10] New Data Interrupt Pointer 42 (42 = 32-63) (rw) */
    unsigned int NDIP43:1;                  /**< \brief [11:11] New Data Interrupt Pointer 43 (43 = 32-63) (rw) */
    unsigned int NDIP44:1;                  /**< \brief [12:12] New Data Interrupt Pointer 44 (44 = 32-63) (rw) */
    unsigned int NDIP45:1;                  /**< \brief [13:13] New Data Interrupt Pointer 45 (45 = 32-63) (rw) */
    unsigned int NDIP46:1;                  /**< \brief [14:14] New Data Interrupt Pointer 46 (46 = 32-63) (rw) */
    unsigned int NDIP47:1;                  /**< \brief [15:15] New Data Interrupt Pointer 47 (47 = 32-63) (rw) */
    unsigned int NDIP48:1;                  /**< \brief [16:16] New Data Interrupt Pointer 48 (48 = 32-63) (rw) */
    unsigned int NDIP49:1;                  /**< \brief [17:17] New Data Interrupt Pointer 49 (49 = 32-63) (rw) */
    unsigned int NDIP50:1;                  /**< \brief [18:18] New Data Interrupt Pointer 50 (50 = 32-63) (rw) */
    unsigned int NDIP51:1;                  /**< \brief [19:19] New Data Interrupt Pointer 51 (51 = 32-63) (rw) */
    unsigned int NDIP52:1;                  /**< \brief [20:20] New Data Interrupt Pointer 52 (52 = 32-63) (rw) */
    unsigned int NDIP53:1;                  /**< \brief [21:21] New Data Interrupt Pointer 53 (53 = 32-63) (rw) */
    unsigned int NDIP54:1;                  /**< \brief [22:22] New Data Interrupt Pointer 54 (54 = 32-63) (rw) */
    unsigned int NDIP55:1;                  /**< \brief [23:23] New Data Interrupt Pointer 55 (55 = 32-63) (rw) */
    unsigned int NDIP56:1;                  /**< \brief [24:24] New Data Interrupt Pointer 56 (56 = 32-63) (rw) */
    unsigned int NDIP57:1;                  /**< \brief [25:25] New Data Interrupt Pointer 57 (57 = 32-63) (rw) */
    unsigned int NDIP58:1;                  /**< \brief [26:26] New Data Interrupt Pointer 58 (58 = 32-63) (rw) */
    unsigned int NDIP59:1;                  /**< \brief [27:27] New Data Interrupt Pointer 59 (59 = 32-63) (rw) */
    unsigned int NDIP60:1;                  /**< \brief [28:28] New Data Interrupt Pointer 60 (60 = 32-63) (rw) */
    unsigned int NDIP61:1;                  /**< \brief [29:29] New Data Interrupt Pointer 61 (61 = 32-63) (rw) */
    unsigned int NDIP62:1;                  /**< \brief [30:30] New Data Interrupt Pointer 62 (62 = 32-63) (rw) */
    unsigned int NDIP63:1;                  /**< \brief [31:31] New Data Interrupt Pointer 63 (63 = 32-63) (rw) */
} Ifx_ERAY_NDIC2_Bits;

/** \brief  New Data Interrupt Control 3 */
typedef struct _Ifx_ERAY_NDIC3_Bits
{
    unsigned int NDIP64:1;                  /**< \brief [0:0] New Data Interrupt Pointer 64 (64 = 64-95) (rw) */
    unsigned int NDIP65:1;                  /**< \brief [1:1] New Data Interrupt Pointer 65 (65 = 64-95) (rw) */
    unsigned int NDIP66:1;                  /**< \brief [2:2] New Data Interrupt Pointer 66 (66 = 64-95) (rw) */
    unsigned int NDIP67:1;                  /**< \brief [3:3] New Data Interrupt Pointer 67 (67 = 64-95) (rw) */
    unsigned int NDIP68:1;                  /**< \brief [4:4] New Data Interrupt Pointer 68 (68 = 64-95) (rw) */
    unsigned int NDIP69:1;                  /**< \brief [5:5] New Data Interrupt Pointer 69 (69 = 64-95) (rw) */
    unsigned int NDIP70:1;                  /**< \brief [6:6] New Data Interrupt Pointer 70 (70 = 64-95) (rw) */
    unsigned int NDIP71:1;                  /**< \brief [7:7] New Data Interrupt Pointer 71 (71 = 64-95) (rw) */
    unsigned int NDIP72:1;                  /**< \brief [8:8] New Data Interrupt Pointer 72 (72 = 64-95) (rw) */
    unsigned int NDIP73:1;                  /**< \brief [9:9] New Data Interrupt Pointer 73 (73 = 64-95) (rw) */
    unsigned int NDIP74:1;                  /**< \brief [10:10] New Data Interrupt Pointer 74 (74 = 64-95) (rw) */
    unsigned int NDIP75:1;                  /**< \brief [11:11] New Data Interrupt Pointer 75 (75 = 64-95) (rw) */
    unsigned int NDIP76:1;                  /**< \brief [12:12] New Data Interrupt Pointer 76 (76 = 64-95) (rw) */
    unsigned int NDIP77:1;                  /**< \brief [13:13] New Data Interrupt Pointer 77 (77 = 64-95) (rw) */
    unsigned int NDIP78:1;                  /**< \brief [14:14] New Data Interrupt Pointer 78 (78 = 64-95) (rw) */
    unsigned int NDIP79:1;                  /**< \brief [15:15] New Data Interrupt Pointer 79 (79 = 64-95) (rw) */
    unsigned int NDIP80:1;                  /**< \brief [16:16] New Data Interrupt Pointer 80 (80 = 64-95) (rw) */
    unsigned int NDIP81:1;                  /**< \brief [17:17] New Data Interrupt Pointer 81 (81 = 64-95) (rw) */
    unsigned int NDIP82:1;                  /**< \brief [18:18] New Data Interrupt Pointer 82 (82 = 64-95) (rw) */
    unsigned int NDIP83:1;                  /**< \brief [19:19] New Data Interrupt Pointer 83 (83 = 64-95) (rw) */
    unsigned int NDIP84:1;                  /**< \brief [20:20] New Data Interrupt Pointer 84 (84 = 64-95) (rw) */
    unsigned int NDIP85:1;                  /**< \brief [21:21] New Data Interrupt Pointer 85 (85 = 64-95) (rw) */
    unsigned int NDIP86:1;                  /**< \brief [22:22] New Data Interrupt Pointer 86 (86 = 64-95) (rw) */
    unsigned int NDIP87:1;                  /**< \brief [23:23] New Data Interrupt Pointer 87 (87 = 64-95) (rw) */
    unsigned int NDIP88:1;                  /**< \brief [24:24] New Data Interrupt Pointer 88 (88 = 64-95) (rw) */
    unsigned int NDIP89:1;                  /**< \brief [25:25] New Data Interrupt Pointer 89 (89 = 64-95) (rw) */
    unsigned int NDIP90:1;                  /**< \brief [26:26] New Data Interrupt Pointer 90 (90 = 64-95) (rw) */
    unsigned int NDIP91:1;                  /**< \brief [27:27] New Data Interrupt Pointer 91 (91 = 64-95) (rw) */
    unsigned int NDIP92:1;                  /**< \brief [28:28] New Data Interrupt Pointer 92 (92 = 64-95) (rw) */
    unsigned int NDIP93:1;                  /**< \brief [29:29] New Data Interrupt Pointer 93 (93 = 64-95) (rw) */
    unsigned int NDIP94:1;                  /**< \brief [30:30] New Data Interrupt Pointer 94 (94 = 64-95) (rw) */
    unsigned int NDIP95:1;                  /**< \brief [31:31] New Data Interrupt Pointer 95 (95 = 64-95) (rw) */
} Ifx_ERAY_NDIC3_Bits;

/** \brief  New Data Interrupt Control 4 */
typedef struct _Ifx_ERAY_NDIC4_Bits
{
    unsigned int NDIP96:1;                  /**< \brief [0:0] New Data Interrupt Pointer 96 (96 = 96-127) (rw) */
    unsigned int NDIP97:1;                  /**< \brief [1:1] New Data Interrupt Pointer 97 (97 = 96-127) (rw) */
    unsigned int NDIP98:1;                  /**< \brief [2:2] New Data Interrupt Pointer 98 (98 = 96-127) (rw) */
    unsigned int NDIP99:1;                  /**< \brief [3:3] New Data Interrupt Pointer 99 (99 = 96-127) (rw) */
    unsigned int NDIP100:1;                 /**< \brief [4:4] New Data Interrupt Pointer 100 (100 = 96-127) (rw) */
    unsigned int NDIP101:1;                 /**< \brief [5:5] New Data Interrupt Pointer 101 (101 = 96-127) (rw) */
    unsigned int NDIP102:1;                 /**< \brief [6:6] New Data Interrupt Pointer 102 (102 = 96-127) (rw) */
    unsigned int NDIP103:1;                 /**< \brief [7:7] New Data Interrupt Pointer 103 (103 = 96-127) (rw) */
    unsigned int NDIP104:1;                 /**< \brief [8:8] New Data Interrupt Pointer 104 (104 = 96-127) (rw) */
    unsigned int NDIP105:1;                 /**< \brief [9:9] New Data Interrupt Pointer 105 (105 = 96-127) (rw) */
    unsigned int NDIP106:1;                 /**< \brief [10:10] New Data Interrupt Pointer 106 (106 = 96-127) (rw) */
    unsigned int NDIP107:1;                 /**< \brief [11:11] New Data Interrupt Pointer 107 (107 = 96-127) (rw) */
    unsigned int NDIP108:1;                 /**< \brief [12:12] New Data Interrupt Pointer 108 (108 = 96-127) (rw) */
    unsigned int NDIP109:1;                 /**< \brief [13:13] New Data Interrupt Pointer 109 (109 = 96-127) (rw) */
    unsigned int NDIP110:1;                 /**< \brief [14:14] New Data Interrupt Pointer 110 (110 = 96-127) (rw) */
    unsigned int NDIP111:1;                 /**< \brief [15:15] New Data Interrupt Pointer 111 (111 = 96-127) (rw) */
    unsigned int NDIP112:1;                 /**< \brief [16:16] New Data Interrupt Pointer 112 (112 = 96-127) (rw) */
    unsigned int NDIP113:1;                 /**< \brief [17:17] New Data Interrupt Pointer 113 (113 = 96-127) (rw) */
    unsigned int NDIP114:1;                 /**< \brief [18:18] New Data Interrupt Pointer 114 (114 = 96-127) (rw) */
    unsigned int NDIP115:1;                 /**< \brief [19:19] New Data Interrupt Pointer 115 (115 = 96-127) (rw) */
    unsigned int NDIP116:1;                 /**< \brief [20:20] New Data Interrupt Pointer 116 (116 = 96-127) (rw) */
    unsigned int NDIP117:1;                 /**< \brief [21:21] New Data Interrupt Pointer 117 (117 = 96-127) (rw) */
    unsigned int NDIP118:1;                 /**< \brief [22:22] New Data Interrupt Pointer 118 (118 = 96-127) (rw) */
    unsigned int NDIP119:1;                 /**< \brief [23:23] New Data Interrupt Pointer 119 (119 = 96-127) (rw) */
    unsigned int NDIP120:1;                 /**< \brief [24:24] New Data Interrupt Pointer 120 (120 = 96-127) (rw) */
    unsigned int NDIP121:1;                 /**< \brief [25:25] New Data Interrupt Pointer 121 (121 = 96-127) (rw) */
    unsigned int NDIP122:1;                 /**< \brief [26:26] New Data Interrupt Pointer 122 (122 = 96-127) (rw) */
    unsigned int NDIP123:1;                 /**< \brief [27:27] New Data Interrupt Pointer 123 (123 = 96-127) (rw) */
    unsigned int NDIP124:1;                 /**< \brief [28:28] New Data Interrupt Pointer 124 (124 = 96-127) (rw) */
    unsigned int NDIP125:1;                 /**< \brief [29:29] New Data Interrupt Pointer 125 (125 = 96-127) (rw) */
    unsigned int NDIP126:1;                 /**< \brief [30:30] New Data Interrupt Pointer 126 (126 = 96-127) (rw) */
    unsigned int NDIP127:1;                 /**< \brief [31:31] New Data Interrupt Pointer 127 (127 = 96-127) (rw) */
} Ifx_ERAY_NDIC4_Bits;

/** \brief  NEM Configuration Register */
typedef struct _Ifx_ERAY_NEMC_Bits
{
    unsigned int NML:4;                     /**< \brief [3:0] Network Management Vector Length (gNetworkManagementVectorLength) (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_ERAY_NEMC_Bits;

/** \brief  Network Management Vector */
typedef struct _Ifx_ERAY_NMV_Bits
{
    unsigned int NM:32;                     /**< \brief [31:0] Network Management Vector (rh) */
} Ifx_ERAY_NMV_Bits;

/** \brief  Output Buffer Command Mask */
typedef struct _Ifx_ERAY_OBCM_Bits
{
    unsigned int RHSS:1;                    /**< \brief [0:0] Read Header Section Shadow (rwh) */
    unsigned int RDSS:1;                    /**< \brief [1:1] Read Data Section Shadow (rwh) */
    unsigned int reserved_2:14;             /**< \brief \internal Reserved */
    unsigned int RHSH:1;                    /**< \brief [16:16] Read Header Section Host (rh) */
    unsigned int RDSH:1;                    /**< \brief [17:17] Read Data Section Host (rh) */
    unsigned int reserved_18:14;            /**< \brief \internal Reserved */
} Ifx_ERAY_OBCM_Bits;

/** \brief  Output Buffer Command Request */
typedef struct _Ifx_ERAY_OBCR_Bits
{
    unsigned int OBRS:7;                    /**< \brief [6:0] Output Buffer Request Shadow (rw) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int VIEW:1;                    /**< \brief [8:8] View Shadow Buffer (rw) */
    unsigned int REQ:1;                     /**< \brief [9:9] Request Message RAM Transfer (rw) */
    unsigned int reserved_10:5;             /**< \brief \internal Reserved */
    unsigned int OBSYS:1;                   /**< \brief [15:15] Output Buffer Busy Shadow (rh) */
    unsigned int OBRH:7;                    /**< \brief [22:16] Output Buffer Request Host (rh) */
    unsigned int reserved_23:9;             /**< \brief \internal Reserved */
} Ifx_ERAY_OBCR_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_ERAY_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_OCS_Bits;

/** \brief  Offset Correction Value */
typedef struct _Ifx_ERAY_OCV_Bits
{
    unsigned int OCV:19;                    /**< \brief [18:0] Offset Correction Value (vOffsetCorrection) (rh) */
    unsigned int reserved_19:13;            /**< \brief \internal Reserved */
} Ifx_ERAY_OCV_Bits;

/** \brief  Odd Sync ID Symbol Window */
typedef struct _Ifx_ERAY_OSID_Bits
{
    unsigned int OID:10;                    /**< \brief [9:0] Odd Sync ID (vsSyncIDListA,B odd) (rh) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int RXOA:1;                    /**< \brief [14:14] Received Odd Sync ID on Channel A (rh) */
    unsigned int RXOB:1;                    /**< \brief [15:15] Received Odd Sync ID on Channel B (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_ERAY_OSID_Bits;

/** \brief  OCDS Trigger Set Select */
typedef struct _Ifx_ERAY_OTSS_Bits
{
    unsigned int OTGB0:2;                   /**< \brief [1:0] Trigger Set for OTGB0 (rw) */
    unsigned int reserved_2:6;              /**< \brief \internal Reserved */
    unsigned int OTGB1:2;                   /**< \brief [9:8] Trigger Set for OTGB1 (rw) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int OTGB2:1;                   /**< \brief [16:16] Trigger Set for OTGB2 (rw) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_ERAY_OTSS_Bits;

/** \brief  PRT Configuration Register 1 */
typedef struct _Ifx_ERAY_PRTC1_Bits
{
    unsigned int TSST:4;                    /**< \brief [3:0] Transmission Start Sequence Transmitter (gdTSSTransmitter) (rw) */
    unsigned int CASM:7;                    /**< \brief [10:4] Collision Avoidance Symbol Maximum(gdCASRxLowMax) (rw) */
    unsigned int reserved_11:1;             /**< \brief \internal Reserved */
    unsigned int SPP:2;                     /**< \brief [13:12] Strobe Point Position (rw) */
    unsigned int BRP:2;                     /**< \brief [15:14] Baud Rate Prescaler(gdSampleClockPeriod, pSamplePerMicrotick) (rw) */
    unsigned int RXW:9;                     /**< \brief [24:16] Wakeup Symbol Receive Window Length (gdWakeupSymbolRxWindow) (rw) */
    unsigned int reserved_25:1;             /**< \brief \internal Reserved */
    unsigned int RWP:6;                     /**< \brief [31:26] Repetitions of Tx Wakeup Pattern (pWakeupPattern) (rw) */
} Ifx_ERAY_PRTC1_Bits;

/** \brief  PRT Configuration Register 2 */
typedef struct _Ifx_ERAY_PRTC2_Bits
{
    unsigned int RXI:6;                     /**< \brief [5:0] Wakeup Symbol Receive Idle (gdWakeupSymbolRxIdle) (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int RXL:6;                     /**< \brief [13:8] Wakeup Symbol Receive Low(gdWakeupSymbolRxLow) (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int TXI:8;                     /**< \brief [23:16] Wakeup Symbol Transmit Idle (gdWakeupSymbolTxIdle) (rw) */
    unsigned int TXL:6;                     /**< \brief [29:24] Wakeup Symbol Transmit Low (gdWakeupSymbolTxLow) (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_PRTC2_Bits;

/** \brief  Rate Correction Value */
typedef struct _Ifx_ERAY_RCV_Bits
{
    unsigned int RCV:12;                    /**< \brief [11:0] Rate Correction Value (vRateCorrection) (rh) */
    unsigned int reserved_12:20;            /**< \brief \internal Reserved */
} Ifx_ERAY_RCV_Bits;

/** \brief  Read Data Section */
typedef struct _Ifx_ERAY_RDDS_Bits
{
    unsigned int MDRB0:8;                   /**< \brief [7:0] 32-Bit Word nn, Byte 0 (rh) */
    unsigned int MDRB1:8;                   /**< \brief [15:8] 32-Bit Word nn, Byte 1 (rh) */
    unsigned int MDRB2:8;                   /**< \brief [23:16] 32-Bit Word nn, Byte 2 (rh) */
    unsigned int MDRB3:8;                   /**< \brief [31:24] 32-Bit Word nn, Byte 3 (rh) */
} Ifx_ERAY_RDDS_Bits;

/** \brief  Read Header Section 1 */
typedef struct _Ifx_ERAY_RDHS1_Bits
{
    unsigned int FID:11;                    /**< \brief [10:0] Frame ID (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int CYC:7;                     /**< \brief [22:16] Cycle Code (rh) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int CHA:1;                     /**< \brief [24:24] Channel Filter Control A (rh) */
    unsigned int CHB:1;                     /**< \brief [25:25] Channel Filter Control B (rh) */
    unsigned int CFG:1;                     /**< \brief [26:26] Message Buffer Direction Configuration Bit (rh) */
    unsigned int PPIT:1;                    /**< \brief [27:27] Payload Preamble Indicator Transmit (rh) */
    unsigned int TXM:1;                     /**< \brief [28:28] Transmission Mode (rh) */
    unsigned int MBI:1;                     /**< \brief [29:29] Message Buffer Service Request (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_RDHS1_Bits;

/** \brief  Read Header Section 2 */
typedef struct _Ifx_ERAY_RDHS2_Bits
{
    unsigned int CRC:11;                    /**< \brief [10:0] Header CRC (vRF!Header!HeaderCRC) (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int PLC:7;                     /**< \brief [22:16] Payload Length Configured (rh) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int PLR:7;                     /**< \brief [30:24] Payload Length Received (vRF!Header!Length) (rh) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_ERAY_RDHS2_Bits;

/** \brief  Read Header Section 3 */
typedef struct _Ifx_ERAY_RDHS3_Bits
{
    unsigned int DP:11;                     /**< \brief [10:0] Data Pointer (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int RCC:6;                     /**< \brief [21:16] Receive Cycle Count (vRF!Header!CycleCount) (rh) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int RCI:1;                     /**< \brief [24:24] Received on Channel Indicator (vSS!Channel) (rh) */
    unsigned int SFI:1;                     /**< \brief [25:25] Startup Frame Indicator (vRF!Header!SuFIndicator) (rh) */
    unsigned int SYN:1;                     /**< \brief [26:26] SYNC Frame Indicator (vRF!Header!SyFIndicator) (rh) */
    unsigned int NFI:1;                     /**< \brief [27:27] NULL Frame Indicator (vRF!Header!NFIndicator) (rh) */
    unsigned int PPI:1;                     /**< \brief [28:28] Payload Preamble Indicator (vRF!Header!PPIndicator) (rh) */
    unsigned int RES:1;                     /**< \brief [29:29] Reserved Bit (vRF!Header!Reserved) (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_RDHS3_Bits;

/** \brief  Slot Counter Value */
typedef struct _Ifx_ERAY_SCV_Bits
{
    unsigned int SCCA:11;                   /**< \brief [10:0] Slot Counter Channel A (vSlotCounter[A]) (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int SCCB:11;                   /**< \brief [26:16] Slot Counter Channel B (vSlotCounter[B]) (rh) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_SCV_Bits;

/** \brief  SYNC Frame Status */
typedef struct _Ifx_ERAY_SFS_Bits
{
    unsigned int VSAE:4;                    /**< \brief [3:0] Valid SYNC Frames Channel A, even communication cycle (rh) */
    unsigned int VSAO:4;                    /**< \brief [7:4] Valid SYNC Frames Channel A, odd communication cycle (rh) */
    unsigned int VSBE:4;                    /**< \brief [11:8] Valid SYNC Frames Channel B, even communication cycle (rh) */
    unsigned int VSBO:4;                    /**< \brief [15:12] Valid SYNC Frames Channel B, odd communication cycle (rh) */
    unsigned int MOCS:1;                    /**< \brief [16:16] Missing Offset Correction Signal (rh) */
    unsigned int OCLR:1;                    /**< \brief [17:17] Offset Correction Limit Reached (rh) */
    unsigned int MRCS:1;                    /**< \brief [18:18] Missing Rate Correction Signal (rh) */
    unsigned int RCLR:1;                    /**< \brief [19:19] Rate Correction Limit Reached (rh) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_ERAY_SFS_Bits;

/** \brief  Status Service Request Enable Reset */
typedef struct _Ifx_ERAY_SIER_Bits
{
    unsigned int WSTE:1;                    /**< \brief [0:0] Wakeup Status Service Request Enable (rwh) */
    unsigned int CASE:1;                    /**< \brief [1:1] Collision Avoidance Symbol Service Request Enable (rwh) */
    unsigned int CYCSE:1;                   /**< \brief [2:2] Cycle Start Service Request Enable (rwh) */
    unsigned int TXIE:1;                    /**< \brief [3:3] Transmit Service Request Enable (rwh) */
    unsigned int RXIE:1;                    /**< \brief [4:4] Receive Service Request Enable (rwh) */
    unsigned int RFNEE:1;                   /**< \brief [5:5] Receive FIFO Not Empty Service Request Enable (rwh) */
    unsigned int RFCLE:1;                   /**< \brief [6:6] Receive FIFO Critical Level Service Request Enable (rwh) */
    unsigned int NMVCE:1;                   /**< \brief [7:7] Network Management Vector Changed Service Request Enable (rwh) */
    unsigned int TI0E:1;                    /**< \brief [8:8] Timer Service Request 0 Enable (rwh) */
    unsigned int TI1E:1;                    /**< \brief [9:9] Timer Service Request 1 Enable (rwh) */
    unsigned int TIBCE:1;                   /**< \brief [10:10] Transfer Input Buffer Completed Service Request Enable (rwh) */
    unsigned int TOBCE:1;                   /**< \brief [11:11] Transfer Output Buffer Completed Service Request Enable (rwh) */
    unsigned int SWEE:1;                    /**< \brief [12:12] Stop Watch Event Service Request Enable (rwh) */
    unsigned int SUCSE:1;                   /**< \brief [13:13] Startup Completed Successfully Service Request Enable (rwh) */
    unsigned int MBSIE:1;                   /**< \brief [14:14] Message Buffer Status Service Request Enable (rwh) */
    unsigned int SDSE:1;                    /**< \brief [15:15] Start of Dynamic Segment Service Request Enable (rwh) */
    unsigned int WUPAE:1;                   /**< \brief [16:16] Wakeup Pattern Channel A Service Request Enable (rwh) */
    unsigned int MTSAE:1;                   /**< \brief [17:17] Media Access Test Symbol Channel A Service Request Enable (rwh) */
    unsigned int reserved_18:6;             /**< \brief \internal Reserved */
    unsigned int WUPBE:1;                   /**< \brief [24:24] Wakeup Pattern Channel B Service Request Enable (rwh) */
    unsigned int MTSBE:1;                   /**< \brief [25:25] Media Access Test Symbol Channel B Service Request Enable (rwh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ERAY_SIER_Bits;

/** \brief  Status Service Request Enable Set */
typedef struct _Ifx_ERAY_SIES_Bits
{
    unsigned int WSTE:1;                    /**< \brief [0:0] Wakeup Status Service Request Enable (rwh) */
    unsigned int CASE:1;                    /**< \brief [1:1] Collision Avoidance Symbol Service Request Enable (rwh) */
    unsigned int CYCSE:1;                   /**< \brief [2:2] Cycle Start Service Request Enable (rwh) */
    unsigned int TXIE:1;                    /**< \brief [3:3] Transmit Service Request Enable (rwh) */
    unsigned int RXIE:1;                    /**< \brief [4:4] Receive Service Request Enable (rwh) */
    unsigned int RFNEE:1;                   /**< \brief [5:5] Receive FIFO Not Empty Service Request Enable (rwh) */
    unsigned int RFCLE:1;                   /**< \brief [6:6] Receive FIFO Critical Level Service Request Enable (rwh) */
    unsigned int NMVCE:1;                   /**< \brief [7:7] Network Management Vector Changed Service Request Enable (rwh) */
    unsigned int TI0E:1;                    /**< \brief [8:8] Timer Service Request 0 Enable (rwh) */
    unsigned int TI1E:1;                    /**< \brief [9:9] Timer Service Request 1 Enable (rwh) */
    unsigned int TIBCE:1;                   /**< \brief [10:10] Transfer Input Buffer Completed Service Request Enable (rwh) */
    unsigned int TOBCE:1;                   /**< \brief [11:11] Transfer Output Buffer Completed Service Request Enable (rwh) */
    unsigned int SWEE:1;                    /**< \brief [12:12] Stop Watch Event Service Request Enable (rwh) */
    unsigned int SUCSE:1;                   /**< \brief [13:13] Startup Completed Successfully Service Request Enable (rwh) */
    unsigned int MBSIE:1;                   /**< \brief [14:14] Message Buffer Status Service Request Enable (rwh) */
    unsigned int SDSE:1;                    /**< \brief [15:15] Start of Dynamic Segment Service Request Enable (rwh) */
    unsigned int WUPAE:1;                   /**< \brief [16:16] Wakeup Pattern Channel A Service Request Enable (rwh) */
    unsigned int MTSAE:1;                   /**< \brief [17:17] Media Access Test Symbol Channel A Service Request Enable (rwh) */
    unsigned int reserved_18:6;             /**< \brief \internal Reserved */
    unsigned int WUPBE:1;                   /**< \brief [24:24] Wakeup Pattern Channel B Service Request Enable (rwh) */
    unsigned int MTSBE:1;                   /**< \brief [25:25] Media Access Test Symbol Channel B Service Request Enable (rwh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ERAY_SIES_Bits;

/** \brief  Status Service Request Line Select */
typedef struct _Ifx_ERAY_SILS_Bits
{
    unsigned int WSTL:1;                    /**< \brief [0:0] Wakeup Status Service Request Line (rw) */
    unsigned int CASL:1;                    /**< \brief [1:1] Collision Avoidance Symbol Service Request Line (rw) */
    unsigned int CYCSL:1;                   /**< \brief [2:2] Cycle Start Service Request Line (rw) */
    unsigned int TXIL:1;                    /**< \brief [3:3] Transmit Service Request Line (rw) */
    unsigned int RXIL:1;                    /**< \brief [4:4] Receive Service Request Line (rw) */
    unsigned int RFNEL:1;                   /**< \brief [5:5] Receive FIFO Not Empty Service Request Line (rw) */
    unsigned int RFCLL:1;                   /**< \brief [6:6] Receive FIFO Critical Level Service Request Line (rw) */
    unsigned int NMVCL:1;                   /**< \brief [7:7] Network Management Vector Changed Service Request Line (rw) */
    unsigned int TI0L:1;                    /**< \brief [8:8] Timer Service Request 0 Line (rw) */
    unsigned int TI1L:1;                    /**< \brief [9:9] Timer Service Request 1 Line (rw) */
    unsigned int TIBCL:1;                   /**< \brief [10:10] Transfer Input Buffer Completed Service Request Line (rw) */
    unsigned int TOBCL:1;                   /**< \brief [11:11] Transfer Output Buffer Completed Service Request Line (rw) */
    unsigned int SWEL:1;                    /**< \brief [12:12] Stop Watch Event Service Request Line (rw) */
    unsigned int SUCSL:1;                   /**< \brief [13:13] Startup Completed Successfully Service Request Line (rw) */
    unsigned int MBSIL:1;                   /**< \brief [14:14] Message Buffer Status Service Request Line (rw) */
    unsigned int SDSL:1;                    /**< \brief [15:15] Start of Dynamic Segment Service Request Line (rw) */
    unsigned int WUPAL:1;                   /**< \brief [16:16] Wakeup Pattern Channel A Service Request Line (rw) */
    unsigned int MTSAL:1;                   /**< \brief [17:17] Media Access Test Symbol Channel A Service Request Line (rw) */
    unsigned int reserved_18:6;             /**< \brief \internal Reserved */
    unsigned int WUPBL:1;                   /**< \brief [24:24] Wakeup Pattern Channel B Service Request Line (rw) */
    unsigned int MTSBL:1;                   /**< \brief [25:25] Media Access Test Symbol Channel B Service Request Line (rw) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ERAY_SILS_Bits;

/** \brief  Status Service Request Register */
typedef struct _Ifx_ERAY_SIR_Bits
{
    unsigned int WST:1;                     /**< \brief [0:0] Wakeup Status (rwh) */
    unsigned int CAS:1;                     /**< \brief [1:1] Collision Avoidance Symbol (rwh) */
    unsigned int CYCS:1;                    /**< \brief [2:2] Cycle Start Service Request (rwh) */
    unsigned int TXI:1;                     /**< \brief [3:3] Transmit Service Request (rwh) */
    unsigned int RXI:1;                     /**< \brief [4:4] Receive Service Request (rwh) */
    unsigned int RFNE:1;                    /**< \brief [5:5] Receive FIFO Not Empty (rh) */
    unsigned int RFCL:1;                    /**< \brief [6:6] Receive FIFO Critical Level (rh) */
    unsigned int NMVC:1;                    /**< \brief [7:7] Network Management Vector Changed (rwh) */
    unsigned int TI0:1;                     /**< \brief [8:8] Timer Service Request 0 (rwh) */
    unsigned int TI1:1;                     /**< \brief [9:9] Timer Service Request 1 (rwh) */
    unsigned int TIBC:1;                    /**< \brief [10:10] Transfer Input Buffer Completed (rwh) */
    unsigned int TOBC:1;                    /**< \brief [11:11] Transfer Output Buffer Completed (rwh) */
    unsigned int SWE:1;                     /**< \brief [12:12] Stop Watch Event (rwh) */
    unsigned int SUCS:1;                    /**< \brief [13:13] Startup Completed Successfully (rwh) */
    unsigned int MBSI:1;                    /**< \brief [14:14] Message Buffer Status Service Request (rwh) */
    unsigned int SDS:1;                     /**< \brief [15:15] Start of Dynamic Segment (rwh) */
    unsigned int WUPA:1;                    /**< \brief [16:16] Wakeup Pattern Channel A (rwh) */
    unsigned int MTSA:1;                    /**< \brief [17:17] MTS Received on Channel A (vSS!ValidMTSA) (rwh) */
    unsigned int reserved_18:6;             /**< \brief \internal Reserved */
    unsigned int WUPB:1;                    /**< \brief [24:24] Wakeup Pattern Channel B (rwh) */
    unsigned int MTSB:1;                    /**< \brief [25:25] MTS Received on Channel B (vSS!ValidMTSB) (rwh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_ERAY_SIR_Bits;

/** \brief  Stop Watch Register 1 */
typedef struct _Ifx_ERAY_STPW1_Bits
{
    unsigned int ESWT:1;                    /**< \brief [0:0] Enable Stop Watch Trigger (rwh) */
    unsigned int SWMS:1;                    /**< \brief [1:1] Stop Watch Mode Select (rw) */
    unsigned int EDGE:1;                    /**< \brief [2:2] Stop Watch Trigger Edge Select (rw) */
    unsigned int SSWT:1;                    /**< \brief [3:3] Software Stop Watch Trigger (rwh) */
    unsigned int EETP:1;                    /**< \brief [4:4] Enable External Trigger Pin (rw) */
    unsigned int EINT0:1;                   /**< \brief [5:5] Enable Service Request 0 Trigger (rw) */
    unsigned int EINT1:1;                   /**< \brief [6:6] Enable Service Request 1 Trigger (rw) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int SCCV:6;                    /**< \brief [13:8] Stopped Cycle Counter Value (rh) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int SMTV:14;                   /**< \brief [29:16] Stopped Macrotick Value (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_STPW1_Bits;

/** \brief  Stop Watch Register 2 */
typedef struct _Ifx_ERAY_STPW2_Bits
{
    unsigned int SSCVA:11;                  /**< \brief [10:0] Stop Watch Captured Slot Counter Value Channel A (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int SSCVB:11;                  /**< \brief [26:16] Stop Watch Captured Slot Counter Value Channel B (rh) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_ERAY_STPW2_Bits;

/** \brief  SUC Configuration Register 1 */
typedef struct _Ifx_ERAY_SUCC1_Bits
{
    unsigned int CMD:4;                     /**< \brief [3:0] CHI Command Vector (rwh) */
    unsigned int reserved_4:3;              /**< \brief \internal Reserved */
    unsigned int PBSY:1;                    /**< \brief [7:7] POC Busy (rh) */
    unsigned int TXST:1;                    /**< \brief [8:8] Transmit Startup Frame in Key Slot (pKeySlotUsedForStartup) (rw) */
    unsigned int TXSY:1;                    /**< \brief [9:9] Transmit SYNC Frame in Key Slot(pKeySlotUsedForSync) (rw) */
    unsigned int reserved_10:1;             /**< \brief \internal Reserved */
    unsigned int CSA:5;                     /**< \brief [15:11] Cold Start Attempts(gColdStartAttempts) (rw) */
    unsigned int PTA:5;                     /**< \brief [20:16] Passive to Active (pAllowPassiveToActive) (rw) */
    unsigned int WUCS:1;                    /**< \brief [21:21] Wakeup Channel Select (pWakeupChannel) (rw) */
    unsigned int TSM:1;                     /**< \brief [22:22] Transmission Slot Mode (pSingleSlotEnabled) (rw) */
    unsigned int HCSE:1;                    /**< \brief [23:23] Halt due to Clock Sync Error (pAllowHaltDueToClock) (rw) */
    unsigned int MTSA:1;                    /**< \brief [24:24] Select Channel A for MTS Transmission (rw) */
    unsigned int MTSB:1;                    /**< \brief [25:25] Select Channel B for MTS Transmission (rw) */
    unsigned int CCHA:1;                    /**< \brief [26:26] Connected to Channel A (pChannels) (rw) */
    unsigned int CCHB:1;                    /**< \brief [27:27] Connected to Channel B (pChannels) (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_ERAY_SUCC1_Bits;

/** \brief  SUC Configuration Register 2 */
typedef struct _Ifx_ERAY_SUCC2_Bits
{
    unsigned int LT:21;                     /**< \brief [20:0] Listen Timeout (pdListenTimeout) (rw) */
    unsigned int reserved_21:3;             /**< \brief \internal Reserved */
    unsigned int LTN:4;                     /**< \brief [27:24] Listen Time-out Noise (gListenNoise - 1) (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_ERAY_SUCC2_Bits;

/** \brief  SUC Configuration Register 3 */
typedef struct _Ifx_ERAY_SUCC3_Bits
{
    unsigned int WCP:4;                     /**< \brief [3:0] Maximum Without Clock Correction Passive (gMaxWithoutClockCorrectionPassive) (rw) */
    unsigned int WCF:4;                     /**< \brief [7:4] Maximum Without Clock Correction Fatal (gMaxWithoutClockCorrecti on Fatal) (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_ERAY_SUCC3_Bits;

/** \brief  Symbol Window and Network Idle Time Status */
typedef struct _Ifx_ERAY_SWNIT_Bits
{
    unsigned int SESA:1;                    /**< \brief [0:0] Syntax Error in Symbol Window Channel A (vSS!SyntaxErrorA) (rh) */
    unsigned int SBSA:1;                    /**< \brief [1:1] Slot Boundary Violation in Symbol Window Channel A (vSS!BViolationA) (rh) */
    unsigned int TCSA:1;                    /**< \brief [2:2] Transmission Conflict in Symbol Window Channel A (vSS!TxConflictA) (rh) */
    unsigned int SESB:1;                    /**< \brief [3:3] Syntax Error in Symbol Window Channel B (vSS!SyntaxErrorB) (rh) */
    unsigned int SBSB:1;                    /**< \brief [4:4] Slot Boundary Violation in Symbol Window Channel B (vSS!BViolationB) (rh) */
    unsigned int TCSB:1;                    /**< \brief [5:5] Transmission Conflict in Symbol Window Channel B (vSS!TxConflictB) (rh) */
    unsigned int MTSA:1;                    /**< \brief [6:6] MTS Received on Channel A (vSS!ValidMTSA) (rh) */
    unsigned int MTSB:1;                    /**< \brief [7:7] MTS Received on Channel B (vSS!ValidMTSB) (rh) */
    unsigned int SENA:1;                    /**< \brief [8:8] Syntax Error during network idle time (NIT) Channel A (vSS!SyntaxErrorA) (rh) */
    unsigned int SBNA:1;                    /**< \brief [9:9] Slot Boundary Violation during network idle time (NIT) Channel A (vSS!BViolationA) (rh) */
    unsigned int SENB:1;                    /**< \brief [10:10] Syntax Error during network idle time (NIT) Channel B (vSS!SyntaxErrorB) (rh) */
    unsigned int SBNB:1;                    /**< \brief [11:11] Slot Boundary Violation during network idle time (NIT) Channel B (vSS!BViolationB) (rh) */
    unsigned int reserved_12:20;            /**< \brief \internal Reserved */
} Ifx_ERAY_SWNIT_Bits;

/** \brief  Timer 0 Configuration */
typedef struct _Ifx_ERAY_T0C_Bits
{
    unsigned int T0RC:1;                    /**< \brief [0:0] Timer 0 Run Control (rwh) */
    unsigned int T0MS:1;                    /**< \brief [1:1] Timer 0 Mode Select (rw) */
    unsigned int reserved_2:6;              /**< \brief \internal Reserved */
    unsigned int T0CC:7;                    /**< \brief [14:8] Timer 0 Cycle Code (rw) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int T0MO:14;                   /**< \brief [29:16] Timer 0 Macrotick Offset (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_T0C_Bits;

/** \brief  Timer 1 Configuration */
typedef struct _Ifx_ERAY_T1C_Bits
{
    unsigned int T1RC:1;                    /**< \brief [0:0] Timer 1 Run Control (rwh) */
    unsigned int T1MS:1;                    /**< \brief [1:1] Timer 1 Mode Select (rw) */
    unsigned int reserved_2:14;             /**< \brief \internal Reserved */
    unsigned int T1MC:14;                   /**< \brief [29:16] Timer 1 Macrotick Count (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_T1C_Bits;

/** \brief  Test Register 1 */
typedef struct _Ifx_ERAY_TEST1_Bits
{
    unsigned int WRTEN:1;                   /**< \brief [0:0] Write Test Register Enable (rw) */
    unsigned int ELBE:1;                    /**< \brief [1:1] External Loop Back Enable (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int TMC:2;                     /**< \brief [5:4] Test Multiplexer Control (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int AOA:1;                     /**< \brief [8:8] Activity on A (rh) */
    unsigned int AOB:1;                     /**< \brief [9:9] Activity on B (rh) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int RXA:1;                     /**< \brief [16:16] Read Channel A Receive Pin (rh) */
    unsigned int RXB:1;                     /**< \brief [17:17] Read Channel B Receive Pin (rh) */
    unsigned int TXA:1;                     /**< \brief [18:18] Read or Write to Channel A Transmit Pin (rwh) */
    unsigned int TXB:1;                     /**< \brief [19:19] Read or Write to Channel B Transmit Pin (rwh) */
    unsigned int TXENA:1;                   /**< \brief [20:20] Read or Write to Channel A Transmit Enable Pin (rwh) */
    unsigned int TXENB:1;                   /**< \brief [21:21] Read or Write to Channel B Transmit Enable Pin (rwh) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int CERA:4;                    /**< \brief [27:24] Coding Error Report Channel A (rh) */
    unsigned int CERB:4;                    /**< \brief [31:28] Coding Error Report Channel B (rh) */
} Ifx_ERAY_TEST1_Bits;

/** \brief  Test Register 2 */
typedef struct _Ifx_ERAY_TEST2_Bits
{
    unsigned int RS:3;                      /**< \brief [2:0] RAM Select (rw) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int SSEL:3;                    /**< \brief [6:4] Segment Select (rw) */
    unsigned int reserved_7:7;              /**< \brief \internal Reserved */
    unsigned int WRECC:1;                   /**< \brief [14:14] Write ECC Data Enable (rw) */
    unsigned int reserved_15:17;            /**< \brief \internal Reserved */
} Ifx_ERAY_TEST2_Bits;

/** \brief  Transmission Request Register 1 */
typedef struct _Ifx_ERAY_TXRQ1_Bits
{
    unsigned int TXR0:1;                    /**< \brief [0:0] Transmission Request 0 (0 = 0-31) (rh) */
    unsigned int TXR1:1;                    /**< \brief [1:1] Transmission Request 1 (1 = 0-31) (rh) */
    unsigned int TXR2:1;                    /**< \brief [2:2] Transmission Request 2 (2 = 0-31) (rh) */
    unsigned int TXR3:1;                    /**< \brief [3:3] Transmission Request 3 (3 = 0-31) (rh) */
    unsigned int TXR4:1;                    /**< \brief [4:4] Transmission Request 4 (4 = 0-31) (rh) */
    unsigned int TXR5:1;                    /**< \brief [5:5] Transmission Request 5 (5 = 0-31) (rh) */
    unsigned int TXR6:1;                    /**< \brief [6:6] Transmission Request 6 (6 = 0-31) (rh) */
    unsigned int TXR7:1;                    /**< \brief [7:7] Transmission Request 7 (7 = 0-31) (rh) */
    unsigned int TXR8:1;                    /**< \brief [8:8] Transmission Request 8 (8 = 0-31) (rh) */
    unsigned int TXR9:1;                    /**< \brief [9:9] Transmission Request 9 (9 = 0-31) (rh) */
    unsigned int TXR10:1;                   /**< \brief [10:10] Transmission Request 10 (10 = 0-31) (rh) */
    unsigned int TXR11:1;                   /**< \brief [11:11] Transmission Request 11 (11 = 0-31) (rh) */
    unsigned int TXR12:1;                   /**< \brief [12:12] Transmission Request 12 (12 = 0-31) (rh) */
    unsigned int TXR13:1;                   /**< \brief [13:13] Transmission Request 13 (13 = 0-31) (rh) */
    unsigned int TXR14:1;                   /**< \brief [14:14] Transmission Request 14 (14 = 0-31) (rh) */
    unsigned int TXR15:1;                   /**< \brief [15:15] Transmission Request 15 (15 = 0-31) (rh) */
    unsigned int TXR16:1;                   /**< \brief [16:16] Transmission Request 16 (16 = 0-31) (rh) */
    unsigned int TXR17:1;                   /**< \brief [17:17] Transmission Request 17 (17 = 0-31) (rh) */
    unsigned int TXR18:1;                   /**< \brief [18:18] Transmission Request 18 (18 = 0-31) (rh) */
    unsigned int TXR19:1;                   /**< \brief [19:19] Transmission Request 19 (19 = 0-31) (rh) */
    unsigned int TXR20:1;                   /**< \brief [20:20] Transmission Request 20 (20 = 0-31) (rh) */
    unsigned int TXR21:1;                   /**< \brief [21:21] Transmission Request 21 (21 = 0-31) (rh) */
    unsigned int TXR22:1;                   /**< \brief [22:22] Transmission Request 22 (22 = 0-31) (rh) */
    unsigned int TXR23:1;                   /**< \brief [23:23] Transmission Request 23 (23 = 0-31) (rh) */
    unsigned int TXR24:1;                   /**< \brief [24:24] Transmission Request 24 (24 = 0-31) (rh) */
    unsigned int TXR25:1;                   /**< \brief [25:25] Transmission Request 25 (25 = 0-31) (rh) */
    unsigned int TXR26:1;                   /**< \brief [26:26] Transmission Request 26 (26 = 0-31) (rh) */
    unsigned int TXR27:1;                   /**< \brief [27:27] Transmission Request 27 (27 = 0-31) (rh) */
    unsigned int TXR28:1;                   /**< \brief [28:28] Transmission Request 28 (28 = 0-31) (rh) */
    unsigned int TXR29:1;                   /**< \brief [29:29] Transmission Request 29 (29 = 0-31) (rh) */
    unsigned int TXR30:1;                   /**< \brief [30:30] Transmission Request 30 (30 = 0-31) (rh) */
    unsigned int TXR31:1;                   /**< \brief [31:31] Transmission Request 31 (31 = 0-31) (rh) */
} Ifx_ERAY_TXRQ1_Bits;

/** \brief  Transmission Request Register 2 */
typedef struct _Ifx_ERAY_TXRQ2_Bits
{
    unsigned int TXR32:1;                   /**< \brief [0:0] Transmission Request 32 (32 = 32-63) (rh) */
    unsigned int TXR33:1;                   /**< \brief [1:1] Transmission Request 33 (33 = 32-63) (rh) */
    unsigned int TXR34:1;                   /**< \brief [2:2] Transmission Request 34 (34 = 32-63) (rh) */
    unsigned int TXR35:1;                   /**< \brief [3:3] Transmission Request 35 (35 = 32-63) (rh) */
    unsigned int TXR36:1;                   /**< \brief [4:4] Transmission Request 36 (36 = 32-63) (rh) */
    unsigned int TXR37:1;                   /**< \brief [5:5] Transmission Request 37 (37 = 32-63) (rh) */
    unsigned int TXR38:1;                   /**< \brief [6:6] Transmission Request 38 (38 = 32-63) (rh) */
    unsigned int TXR39:1;                   /**< \brief [7:7] Transmission Request 39 (39 = 32-63) (rh) */
    unsigned int TXR40:1;                   /**< \brief [8:8] Transmission Request 40 (40 = 32-63) (rh) */
    unsigned int TXR41:1;                   /**< \brief [9:9] Transmission Request 41 (41 = 32-63) (rh) */
    unsigned int TXR42:1;                   /**< \brief [10:10] Transmission Request 42 (42 = 32-63) (rh) */
    unsigned int TXR43:1;                   /**< \brief [11:11] Transmission Request 43 (43 = 32-63) (rh) */
    unsigned int TXR44:1;                   /**< \brief [12:12] Transmission Request 44 (44 = 32-63) (rh) */
    unsigned int TXR45:1;                   /**< \brief [13:13] Transmission Request 45 (45 = 32-63) (rh) */
    unsigned int TXR46:1;                   /**< \brief [14:14] Transmission Request 46 (46 = 32-63) (rh) */
    unsigned int TXR47:1;                   /**< \brief [15:15] Transmission Request 47 (47 = 32-63) (rh) */
    unsigned int TXR48:1;                   /**< \brief [16:16] Transmission Request 48 (48 = 32-63) (rh) */
    unsigned int TXR49:1;                   /**< \brief [17:17] Transmission Request 49 (49 = 32-63) (rh) */
    unsigned int TXR50:1;                   /**< \brief [18:18] Transmission Request 50 (50 = 32-63) (rh) */
    unsigned int TXR51:1;                   /**< \brief [19:19] Transmission Request 51 (51 = 32-63) (rh) */
    unsigned int TXR52:1;                   /**< \brief [20:20] Transmission Request 52 (52 = 32-63) (rh) */
    unsigned int TXR53:1;                   /**< \brief [21:21] Transmission Request 53 (53 = 32-63) (rh) */
    unsigned int TXR54:1;                   /**< \brief [22:22] Transmission Request 54 (54 = 32-63) (rh) */
    unsigned int TXR55:1;                   /**< \brief [23:23] Transmission Request 55 (55 = 32-63) (rh) */
    unsigned int TXR56:1;                   /**< \brief [24:24] Transmission Request 56 (56 = 32-63) (rh) */
    unsigned int TXR57:1;                   /**< \brief [25:25] Transmission Request 57 (57 = 32-63) (rh) */
    unsigned int TXR58:1;                   /**< \brief [26:26] Transmission Request 58 (58 = 32-63) (rh) */
    unsigned int TXR59:1;                   /**< \brief [27:27] Transmission Request 59 (59 = 32-63) (rh) */
    unsigned int TXR60:1;                   /**< \brief [28:28] Transmission Request 60 (60 = 32-63) (rh) */
    unsigned int TXR61:1;                   /**< \brief [29:29] Transmission Request 61 (61 = 32-63) (rh) */
    unsigned int TXR62:1;                   /**< \brief [30:30] Transmission Request 62 (62 = 32-63) (rh) */
    unsigned int TXR63:1;                   /**< \brief [31:31] Transmission Request 63 (63 = 32-63) (rh) */
} Ifx_ERAY_TXRQ2_Bits;

/** \brief  Transmission Request Register 3 */
typedef struct _Ifx_ERAY_TXRQ3_Bits
{
    unsigned int TXR64:1;                   /**< \brief [0:0] Transmission Request 64 (64 = 64-95) (rh) */
    unsigned int TXR65:1;                   /**< \brief [1:1] Transmission Request 65 (65 = 64-95) (rh) */
    unsigned int TXR66:1;                   /**< \brief [2:2] Transmission Request 66 (66 = 64-95) (rh) */
    unsigned int TXR67:1;                   /**< \brief [3:3] Transmission Request 67 (67 = 64-95) (rh) */
    unsigned int TXR68:1;                   /**< \brief [4:4] Transmission Request 68 (68 = 64-95) (rh) */
    unsigned int TXR69:1;                   /**< \brief [5:5] Transmission Request 69 (69 = 64-95) (rh) */
    unsigned int TXR70:1;                   /**< \brief [6:6] Transmission Request 70 (70 = 64-95) (rh) */
    unsigned int TXR71:1;                   /**< \brief [7:7] Transmission Request 71 (71 = 64-95) (rh) */
    unsigned int TXR72:1;                   /**< \brief [8:8] Transmission Request 72 (72 = 64-95) (rh) */
    unsigned int TXR73:1;                   /**< \brief [9:9] Transmission Request 73 (73 = 64-95) (rh) */
    unsigned int TXR74:1;                   /**< \brief [10:10] Transmission Request 74 (74 = 64-95) (rh) */
    unsigned int TXR75:1;                   /**< \brief [11:11] Transmission Request 75 (75 = 64-95) (rh) */
    unsigned int TXR76:1;                   /**< \brief [12:12] Transmission Request 76 (76 = 64-95) (rh) */
    unsigned int TXR77:1;                   /**< \brief [13:13] Transmission Request 77 (77 = 64-95) (rh) */
    unsigned int TXR78:1;                   /**< \brief [14:14] Transmission Request 78 (78 = 64-95) (rh) */
    unsigned int TXR79:1;                   /**< \brief [15:15] Transmission Request 79 (79 = 64-95) (rh) */
    unsigned int TXR80:1;                   /**< \brief [16:16] Transmission Request 80 (80 = 64-95) (rh) */
    unsigned int TXR81:1;                   /**< \brief [17:17] Transmission Request 81 (81 = 64-95) (rh) */
    unsigned int TXR82:1;                   /**< \brief [18:18] Transmission Request 82 (82 = 64-95) (rh) */
    unsigned int TXR83:1;                   /**< \brief [19:19] Transmission Request 83 (83 = 64-95) (rh) */
    unsigned int TXR84:1;                   /**< \brief [20:20] Transmission Request 84 (84 = 64-95) (rh) */
    unsigned int TXR85:1;                   /**< \brief [21:21] Transmission Request 85 (85 = 64-95) (rh) */
    unsigned int TXR86:1;                   /**< \brief [22:22] Transmission Request 86 (86 = 64-95) (rh) */
    unsigned int TXR87:1;                   /**< \brief [23:23] Transmission Request 87 (87 = 64-95) (rh) */
    unsigned int TXR88:1;                   /**< \brief [24:24] Transmission Request 88 (88 = 64-95) (rh) */
    unsigned int TXR89:1;                   /**< \brief [25:25] Transmission Request 89 (89 = 64-95) (rh) */
    unsigned int TXR90:1;                   /**< \brief [26:26] Transmission Request 90 (90 = 64-95) (rh) */
    unsigned int TXR91:1;                   /**< \brief [27:27] Transmission Request 91 (91 = 64-95) (rh) */
    unsigned int TXR92:1;                   /**< \brief [28:28] Transmission Request 92 (92 = 64-95) (rh) */
    unsigned int TXR93:1;                   /**< \brief [29:29] Transmission Request 93 (93 = 64-95) (rh) */
    unsigned int TXR94:1;                   /**< \brief [30:30] Transmission Request 94 (94 = 64-95) (rh) */
    unsigned int TXR95:1;                   /**< \brief [31:31] Transmission Request 95 (95 = 64-95) (rh) */
} Ifx_ERAY_TXRQ3_Bits;

/** \brief  Transmission Request Register 4 */
typedef struct _Ifx_ERAY_TXRQ4_Bits
{
    unsigned int TXR96:1;                   /**< \brief [0:0] Transmission Request 96 (96 = 96-127) (rh) */
    unsigned int TXR97:1;                   /**< \brief [1:1] Transmission Request 97 (97 = 96-127) (rh) */
    unsigned int TXR98:1;                   /**< \brief [2:2] Transmission Request 98 (98 = 96-127) (rh) */
    unsigned int TXR99:1;                   /**< \brief [3:3] Transmission Request 99 (99 = 96-127) (rh) */
    unsigned int TXR100:1;                  /**< \brief [4:4] Transmission Request 100 (100 = 96-127) (rh) */
    unsigned int TXR101:1;                  /**< \brief [5:5] Transmission Request 101 (101 = 96-127) (rh) */
    unsigned int TXR102:1;                  /**< \brief [6:6] Transmission Request 102 (102 = 96-127) (rh) */
    unsigned int TXR103:1;                  /**< \brief [7:7] Transmission Request 103 (103 = 96-127) (rh) */
    unsigned int TXR104:1;                  /**< \brief [8:8] Transmission Request 104 (104 = 96-127) (rh) */
    unsigned int TXR105:1;                  /**< \brief [9:9] Transmission Request 105 (105 = 96-127) (rh) */
    unsigned int TXR106:1;                  /**< \brief [10:10] Transmission Request 106 (106 = 96-127) (rh) */
    unsigned int TXR107:1;                  /**< \brief [11:11] Transmission Request 107 (107 = 96-127) (rh) */
    unsigned int TXR108:1;                  /**< \brief [12:12] Transmission Request 108 (108 = 96-127) (rh) */
    unsigned int TXR109:1;                  /**< \brief [13:13] Transmission Request 109 (109 = 96-127) (rh) */
    unsigned int TXR110:1;                  /**< \brief [14:14] Transmission Request 110 (110 = 96-127) (rh) */
    unsigned int TXR111:1;                  /**< \brief [15:15] Transmission Request 111 (111 = 96-127) (rh) */
    unsigned int TXR112:1;                  /**< \brief [16:16] Transmission Request 112 (112 = 96-127) (rh) */
    unsigned int TXR113:1;                  /**< \brief [17:17] Transmission Request 113 (113 = 96-127) (rh) */
    unsigned int TXR114:1;                  /**< \brief [18:18] Transmission Request 114 (114 = 96-127) (rh) */
    unsigned int TXR115:1;                  /**< \brief [19:19] Transmission Request 115 (115 = 96-127) (rh) */
    unsigned int TXR116:1;                  /**< \brief [20:20] Transmission Request 116 (116 = 96-127) (rh) */
    unsigned int TXR117:1;                  /**< \brief [21:21] Transmission Request 117 (117 = 96-127) (rh) */
    unsigned int TXR118:1;                  /**< \brief [22:22] Transmission Request 118 (118 = 96-127) (rh) */
    unsigned int TXR119:1;                  /**< \brief [23:23] Transmission Request 119 (119 = 96-127) (rh) */
    unsigned int TXR120:1;                  /**< \brief [24:24] Transmission Request 120 (120 = 96-127) (rh) */
    unsigned int TXR121:1;                  /**< \brief [25:25] Transmission Request 121 (121 = 96-127) (rh) */
    unsigned int TXR122:1;                  /**< \brief [26:26] Transmission Request 122 (122 = 96-127) (rh) */
    unsigned int TXR123:1;                  /**< \brief [27:27] Transmission Request 123 (123 = 96-127) (rh) */
    unsigned int TXR124:1;                  /**< \brief [28:28] Transmission Request 124 (124 = 96-127) (rh) */
    unsigned int TXR125:1;                  /**< \brief [29:29] Transmission Request 125 (125 = 96-127) (rh) */
    unsigned int TXR126:1;                  /**< \brief [30:30] Transmission Request 126 (126 = 96-127) (rh) */
    unsigned int TXR127:1;                  /**< \brief [31:31] Transmission Request 127 (127 = 96-127) (rh) */
} Ifx_ERAY_TXRQ4_Bits;

/** \brief  Write Data Section */
typedef struct _Ifx_ERAY_WRDS_Bits
{
    unsigned int MDWB0:8;                   /**< \brief [7:0] 32-Bit Word nn, Byte 0 (rw) */
    unsigned int MDWB1:8;                   /**< \brief [15:8] 32-Bit Word nn, Byte 1 (rw) */
    unsigned int MDWB2:8;                   /**< \brief [23:16] 32-Bit Word nn, Byte 2 (rw) */
    unsigned int MDWB3:8;                   /**< \brief [31:24] 32-Bit Word nn, Byte 3 (rw) */
} Ifx_ERAY_WRDS_Bits;

/** \brief  Write Header Section 1 */
typedef struct _Ifx_ERAY_WRHS1_Bits
{
    unsigned int FID:11;                    /**< \brief [10:0] Frame ID (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int CYC:7;                     /**< \brief [22:16] Cycle Code (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int CHA:1;                     /**< \brief [24:24] Channel Filter Control A (rw) */
    unsigned int CHB:1;                     /**< \brief [25:25] Channel Filter Control B (rw) */
    unsigned int CFG:1;                     /**< \brief [26:26] Message Buffer Direction Configuration Bit (rw) */
    unsigned int PPIT:1;                    /**< \brief [27:27] Payload Preamble Indicator Transmit (rw) */
    unsigned int TXM:1;                     /**< \brief [28:28] Transmission Mode (rw) */
    unsigned int MBI:1;                     /**< \brief [29:29] Message Buffer Service Request (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_ERAY_WRHS1_Bits;

/** \brief  Write Header Section 2 */
typedef struct _Ifx_ERAY_WRHS2_Bits
{
    unsigned int CRC:11;                    /**< \brief [10:0] Header CRC (vRF!Header!HeaderCRC) (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int PLC:7;                     /**< \brief [22:16] Payload Length Configured (rw) */
    unsigned int reserved_23:9;             /**< \brief \internal Reserved */
} Ifx_ERAY_WRHS2_Bits;

/** \brief  Write Header Section 3 */
typedef struct _Ifx_ERAY_WRHS3_Bits
{
    unsigned int DP:11;                     /**< \brief [10:0] Data Pointer (rw) */
    unsigned int reserved_11:21;            /**< \brief \internal Reserved */
} Ifx_ERAY_WRHS3_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Eray_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_ACCEN1;

/** \brief  Aggregated Channel Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_ACS_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_ACS;

/** \brief  Communication Controller Error Vector */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_CCEV_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_CCEV;

/** \brief  Communication Controller Status Vector */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_CCSV_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_CCSV;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_CLC_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_CLC;

/** \brief  Core Release Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_CREL_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_CREL;

/** \brief  Busy and Input Buffer Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_CUST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_CUST1;

/** \brief  Customer Interface Timeout Counter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_CUST3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_CUST3;

/** \brief  Error Service Request Enable Reset */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_EIER_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_EIER;

/** \brief  Error Service Request Enable Set */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_EIES_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_EIES;

/** \brief  Error Service Request Line Select */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_EILS_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_EILS;

/** \brief  Error Service Request Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_EIR_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_EIR;

/** \brief  Endian Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_ENDN_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_ENDN;

/** \brief  Even Sync ID Symbol Window */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_ESID_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_ESID;

/** \brief  FIFO Critical Level */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_FCL_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_FCL;

/** \brief  FIFO Rejection Filter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_FRF_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_FRF;

/** \brief  FIFO Rejection Filter Mask */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_FRFM_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_FRFM;

/** \brief  FIFO Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_FSR_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_FSR;

/** \brief  GTU Configuration Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC01_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC01;

/** \brief  GTU Configuration Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC02_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC02;

/** \brief  GTU Configuration Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC03_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC03;

/** \brief  GTU Configuration Register 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC04_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC04;

/** \brief  GTU Configuration Register 5 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC05_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC05;

/** \brief  GTU Configuration Register 6 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC06_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC06;

/** \brief  GTU Configuration Register 7 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC07_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC07;

/** \brief  GTU Configuration Register 8 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC08_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC08;

/** \brief  GTU Configuration Register 9 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC09_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC09;

/** \brief  GTU Configuration Register 10 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC10_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC10;

/** \brief  GTU Configuration Register 11 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_GTUC11_Bits B;                 /**< \brief Bitfield access */
} Ifx_ERAY_GTUC11;

/** \brief  Input Buffer Command Mask */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_IBCM_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_IBCM;

/** \brief  Input Buffer Command Request */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_IBCR_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_IBCR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_ERAY_ID;

/** \brief  Service Request Line Enable */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_ILE_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_ILE;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_KRST0_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_KRST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_KRSTCLR_Bits B;                /**< \brief Bitfield access */
} Ifx_ERAY_KRSTCLR;

/** \brief  Lock Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_LCK_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_LCK;

/** \brief  Last Dynamic Transmit Slot */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_LDTS_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_LDTS;

/** \brief  Message Buffer Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MBS_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_MBS;

/** \brief  Message Buffer Status Changed 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MBSC1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MBSC1;

/** \brief  Message Buffer Status Changed 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MBSC2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MBSC2;

/** \brief  Message Buffer Status Changed 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MBSC3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MBSC3;

/** \brief  Message Buffer Status Changed 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MBSC4_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MBSC4;

/** \brief  MHD Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MHDC_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_MHDC;

/** \brief  Message Handler Constraints Flags */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MHDF_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_MHDF;

/** \brief  Message Handler Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MHDS_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_MHDS;

/** \brief  Message RAM Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MRC_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_MRC;

/** \brief  Message Buffer Status Changed Interrupt Control 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MSIC1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MSIC1;

/** \brief  Message Buffer Status Changed Interrupt Control 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MSIC2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MSIC2;

/** \brief  Message Buffer Status Changed Interrupt Control 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MSIC3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MSIC3;

/** \brief  Message Buffer Status Changed Interrupt Control 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MSIC4_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MSIC4;

/** \brief  Macrotick and Cycle Counter Value */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_MTCCV_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_MTCCV;

/** \brief  New Data Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDAT1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDAT1;

/** \brief  New Data Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDAT2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDAT2;

/** \brief  New Data Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDAT3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDAT3;

/** \brief  New Data Register 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDAT4_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDAT4;

/** \brief  New Data Interrupt Control 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDIC1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDIC1;

/** \brief  New Data Interrupt Control 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDIC2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDIC2;

/** \brief  New Data Interrupt Control 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDIC3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDIC3;

/** \brief  New Data Interrupt Control 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NDIC4_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_NDIC4;

/** \brief  NEM Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NEMC_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_NEMC;

/** \brief  Network Management Vector */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_NMV_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_NMV;

/** \brief  Output Buffer Command Mask */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_OBCM_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_OBCM;

/** \brief  Output Buffer Command Request */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_OBCR_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_OBCR;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_OCS_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_OCS;

/** \brief  Offset Correction Value */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_OCV_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_OCV;

/** \brief  Odd Sync ID Symbol Window */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_OSID_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_OSID;

/** \brief  OCDS Trigger Set Select */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_OTSS_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_OTSS;

/** \brief  PRT Configuration Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_PRTC1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_PRTC1;

/** \brief  PRT Configuration Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_PRTC2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_PRTC2;

/** \brief  Rate Correction Value */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_RCV_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_RCV;

/** \brief  Read Data Section */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_RDDS_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_RDDS;

/** \brief  Read Header Section 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_RDHS1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_RDHS1;

/** \brief  Read Header Section 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_RDHS2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_RDHS2;

/** \brief  Read Header Section 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_RDHS3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_RDHS3;

/** \brief  Slot Counter Value */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SCV_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_SCV;

/** \brief  SYNC Frame Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SFS_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_SFS;

/** \brief  Status Service Request Enable Reset */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SIER_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_SIER;

/** \brief  Status Service Request Enable Set */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SIES_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_SIES;

/** \brief  Status Service Request Line Select */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SILS_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_SILS;

/** \brief  Status Service Request Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SIR_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_SIR;

/** \brief  Stop Watch Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_STPW1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_STPW1;

/** \brief  Stop Watch Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_STPW2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_STPW2;

/** \brief  SUC Configuration Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SUCC1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_SUCC1;

/** \brief  SUC Configuration Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SUCC2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_SUCC2;

/** \brief  SUC Configuration Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SUCC3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_SUCC3;

/** \brief  Symbol Window and Network Idle Time Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_SWNIT_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_SWNIT;

/** \brief  Timer 0 Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_T0C_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_T0C;

/** \brief  Timer 1 Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_T1C_Bits B;                    /**< \brief Bitfield access */
} Ifx_ERAY_T1C;

/** \brief  Test Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_TEST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_TEST1;

/** \brief  Test Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_TEST2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_TEST2;

/** \brief  Transmission Request Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_TXRQ1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_TXRQ1;

/** \brief  Transmission Request Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_TXRQ2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_TXRQ2;

/** \brief  Transmission Request Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_TXRQ3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_TXRQ3;

/** \brief  Transmission Request Register 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_TXRQ4_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_TXRQ4;

/** \brief  Write Data Section */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_WRDS_Bits B;                   /**< \brief Bitfield access */
} Ifx_ERAY_WRDS;

/** \brief  Write Header Section 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_WRHS1_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_WRHS1;

/** \brief  Write Header Section 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_WRHS2_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_WRHS2;

/** \brief  Write Header Section 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_ERAY_WRHS3_Bits B;                  /**< \brief Bitfield access */
} Ifx_ERAY_WRHS3;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Eray_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  ERAY object */
typedef volatile struct _Ifx_ERAY
{
    Ifx_ERAY_CLC CLC;                       /**< \brief 0, Clock Control Register */
    Ifx_ERAY_CUST1 CUST1;                   /**< \brief 4, Busy and Input Buffer Control Register */
    Ifx_ERAY_ID ID;                         /**< \brief 8, Module Identification Register */
    Ifx_ERAY_CUST3 CUST3;                   /**< \brief C, Customer Interface Timeout Counter */
    Ifx_ERAY_TEST1 TEST1;                   /**< \brief 10, Test Register 1 */
    Ifx_ERAY_TEST2 TEST2;                   /**< \brief 14, Test Register 2 */
    unsigned char reserved_18[4];           /**< \brief 18, \internal Reserved */
    Ifx_ERAY_LCK LCK;                       /**< \brief 1C, Lock Register */
    Ifx_ERAY_EIR EIR;                       /**< \brief 20, Error Service Request Register */
    Ifx_ERAY_SIR SIR;                       /**< \brief 24, Status Service Request Register */
    Ifx_ERAY_EILS EILS;                     /**< \brief 28, Error Service Request Line Select */
    Ifx_ERAY_SILS SILS;                     /**< \brief 2C, Status Service Request Line Select */
    Ifx_ERAY_EIES EIES;                     /**< \brief 30, Error Service Request Enable Set */
    Ifx_ERAY_EIER EIER;                     /**< \brief 34, Error Service Request Enable Reset */
    Ifx_ERAY_SIES SIES;                     /**< \brief 38, Status Service Request Enable Set */
    Ifx_ERAY_SIER SIER;                     /**< \brief 3C, Status Service Request Enable Reset */
    Ifx_ERAY_ILE ILE;                       /**< \brief 40, Service Request Line Enable */
    Ifx_ERAY_T0C T0C;                       /**< \brief 44, Timer 0 Configuration */
    Ifx_ERAY_T1C T1C;                       /**< \brief 48, Timer 1 Configuration */
    Ifx_ERAY_STPW1 STPW1;                   /**< \brief 4C, Stop Watch Register 1 */
    Ifx_ERAY_STPW2 STPW2;                   /**< \brief 50, Stop Watch Register 2 */
    unsigned char reserved_54[44];          /**< \brief 54, \internal Reserved */
    Ifx_ERAY_SUCC1 SUCC1;                   /**< \brief 80, SUC Configuration Register 1 */
    Ifx_ERAY_SUCC2 SUCC2;                   /**< \brief 84, SUC Configuration Register 2 */
    Ifx_ERAY_SUCC3 SUCC3;                   /**< \brief 88, SUC Configuration Register 3 */
    Ifx_ERAY_NEMC NEMC;                     /**< \brief 8C, NEM Configuration Register */
    Ifx_ERAY_PRTC1 PRTC1;                   /**< \brief 90, PRT Configuration Register 1 */
    Ifx_ERAY_PRTC2 PRTC2;                   /**< \brief 94, PRT Configuration Register 2 */
    Ifx_ERAY_MHDC MHDC;                     /**< \brief 98, MHD Configuration Register */
    unsigned char reserved_9C[4];           /**< \brief 9C, \internal Reserved */
    Ifx_ERAY_GTUC01 GTUC01;                 /**< \brief A0, GTU Configuration Register 1 */
    Ifx_ERAY_GTUC02 GTUC02;                 /**< \brief A4, GTU Configuration Register 2 */
    Ifx_ERAY_GTUC03 GTUC03;                 /**< \brief A8, GTU Configuration Register 3 */
    Ifx_ERAY_GTUC04 GTUC04;                 /**< \brief AC, GTU Configuration Register 4 */
    Ifx_ERAY_GTUC05 GTUC05;                 /**< \brief B0, GTU Configuration Register 5 */
    Ifx_ERAY_GTUC06 GTUC06;                 /**< \brief B4, GTU Configuration Register 6 */
    Ifx_ERAY_GTUC07 GTUC07;                 /**< \brief B8, GTU Configuration Register 7 */
    Ifx_ERAY_GTUC08 GTUC08;                 /**< \brief BC, GTU Configuration Register 8 */
    Ifx_ERAY_GTUC09 GTUC09;                 /**< \brief C0, GTU Configuration Register 9 */
    Ifx_ERAY_GTUC10 GTUC10;                 /**< \brief C4, GTU Configuration Register 10 */
    Ifx_ERAY_GTUC11 GTUC11;                 /**< \brief C8, GTU Configuration Register 11 */
    unsigned char reserved_CC[52];          /**< \brief CC, \internal Reserved */
    Ifx_ERAY_CCSV CCSV;                     /**< \brief 100, Communication Controller Status Vector */
    Ifx_ERAY_CCEV CCEV;                     /**< \brief 104, Communication Controller Error Vector */
    unsigned char reserved_108[8];          /**< \brief 108, \internal Reserved */
    Ifx_ERAY_SCV SCV;                       /**< \brief 110, Slot Counter Value */
    Ifx_ERAY_MTCCV MTCCV;                   /**< \brief 114, Macrotick and Cycle Counter Value */
    Ifx_ERAY_RCV RCV;                       /**< \brief 118, Rate Correction Value */
    Ifx_ERAY_OCV OCV;                       /**< \brief 11C, Offset Correction Value */
    Ifx_ERAY_SFS SFS;                       /**< \brief 120, SYNC Frame Status */
    Ifx_ERAY_SWNIT SWNIT;                   /**< \brief 124, Symbol Window and Network Idle Time Status */
    Ifx_ERAY_ACS ACS;                       /**< \brief 128, Aggregated Channel Status */
    unsigned char reserved_12C[4];          /**< \brief 12C, \internal Reserved */
    Ifx_ERAY_ESID ESID_1S[15];              /**< \brief 130, Even Sync ID Symbol Window \note Array index shifted by 1. Example: defined register ESID_1S[0]/ESID_1S0 corresponds to user manual ESID_1S1, ... */
    unsigned char reserved_16C[4];          /**< \brief 16C, \internal Reserved */
    Ifx_ERAY_OSID OSID_1S[15];              /**< \brief 170, Odd Sync ID Symbol Window \note Array index shifted by 1. Example: defined register OSID_1S[0]/OSID_1S0 corresponds to user manual OSID_1S1, ... */
    unsigned char reserved_1AC[4];          /**< \brief 1AC, \internal Reserved */
    Ifx_ERAY_NMV NMV_1S[3];                 /**< \brief 1B0, Network Management Vector \note Array index shifted by 1. Example: defined register NMV_1S[0]/NMV_1S0 corresponds to user manual NMV_1S1, ... */
    unsigned char reserved_1BC[324];        /**< \brief 1BC, \internal Reserved */
    Ifx_ERAY_MRC MRC;                       /**< \brief 300, Message RAM Configuration */
    Ifx_ERAY_FRF FRF;                       /**< \brief 304, FIFO Rejection Filter */
    Ifx_ERAY_FRFM FRFM;                     /**< \brief 308, FIFO Rejection Filter Mask */
    Ifx_ERAY_FCL FCL;                       /**< \brief 30C, FIFO Critical Level */
    Ifx_ERAY_MHDS MHDS;                     /**< \brief 310, Message Handler Status */
    Ifx_ERAY_LDTS LDTS;                     /**< \brief 314, Last Dynamic Transmit Slot */
    Ifx_ERAY_FSR FSR;                       /**< \brief 318, FIFO Status Register */
    Ifx_ERAY_MHDF MHDF;                     /**< \brief 31C, Message Handler Constraints Flags */
    Ifx_ERAY_TXRQ1 TXRQ1;                   /**< \brief 320, Transmission Request Register 1 */
    Ifx_ERAY_TXRQ2 TXRQ2;                   /**< \brief 324, Transmission Request Register 2 */
    Ifx_ERAY_TXRQ3 TXRQ3;                   /**< \brief 328, Transmission Request Register 3 */
    Ifx_ERAY_TXRQ4 TXRQ4;                   /**< \brief 32C, Transmission Request Register 4 */
    Ifx_ERAY_NDAT1 NDAT1;                   /**< \brief 330, New Data Register 1 */
    Ifx_ERAY_NDAT2 NDAT2;                   /**< \brief 334, New Data Register 2 */
    Ifx_ERAY_NDAT3 NDAT3;                   /**< \brief 338, New Data Register 3 */
    Ifx_ERAY_NDAT4 NDAT4;                   /**< \brief 33C, New Data Register 4 */
    Ifx_ERAY_MBSC1 MBSC1;                   /**< \brief 340, Message Buffer Status Changed 1 */
    Ifx_ERAY_MBSC2 MBSC2;                   /**< \brief 344, Message Buffer Status Changed 2 */
    Ifx_ERAY_MBSC3 MBSC3;                   /**< \brief 348, Message Buffer Status Changed 3 */
    Ifx_ERAY_MBSC4 MBSC4;                   /**< \brief 34C, Message Buffer Status Changed 4 */
    unsigned char reserved_350[88];         /**< \brief 350, \internal Reserved */
    Ifx_ERAY_NDIC1 NDIC1;                   /**< \brief 3A8, New Data Interrupt Control 1 */
    Ifx_ERAY_NDIC2 NDIC2;                   /**< \brief 3AC, New Data Interrupt Control 2 */
    Ifx_ERAY_NDIC3 NDIC3;                   /**< \brief 3B0, New Data Interrupt Control 3 */
    Ifx_ERAY_NDIC4 NDIC4;                   /**< \brief 3B4, New Data Interrupt Control 4 */
    Ifx_ERAY_MSIC1 MSIC1;                   /**< \brief 3B8, Message Buffer Status Changed Interrupt Control 1 */
    Ifx_ERAY_MSIC2 MSIC2;                   /**< \brief 3BC, Message Buffer Status Changed Interrupt Control 2 */
    Ifx_ERAY_MSIC3 MSIC3;                   /**< \brief 3C0, Message Buffer Status Changed Interrupt Control 3 */
    Ifx_ERAY_MSIC4 MSIC4;                   /**< \brief 3C4, Message Buffer Status Changed Interrupt Control 4 */
    unsigned char reserved_3C8[40];         /**< \brief 3C8, \internal Reserved */
    Ifx_ERAY_CREL CREL;                     /**< \brief 3F0, Core Release Register */
    Ifx_ERAY_ENDN ENDN;                     /**< \brief 3F4, Endian Register */
    unsigned char reserved_3F8[8];          /**< \brief 3F8, \internal Reserved */
    Ifx_ERAY_WRDS WRDS_1S[64];              /**< \brief 400, Write Data Section \note Array index shifted by 1. Example: defined register WRDS_1S[0]/WRDS_1S0 corresponds to user manual WRDS_1S1, ... */
    Ifx_ERAY_WRHS1 WRHS1;                   /**< \brief 500, Write Header Section 1 */
    Ifx_ERAY_WRHS2 WRHS2;                   /**< \brief 504, Write Header Section 2 */
    Ifx_ERAY_WRHS3 WRHS3;                   /**< \brief 508, Write Header Section 3 */
    unsigned char reserved_50C[4];          /**< \brief 50C, \internal Reserved */
    Ifx_ERAY_IBCM IBCM;                     /**< \brief 510, Input Buffer Command Mask */
    Ifx_ERAY_IBCR IBCR;                     /**< \brief 514, Input Buffer Command Request */
    unsigned char reserved_518[232];        /**< \brief 518, \internal Reserved */
    Ifx_ERAY_RDDS RDDS_1S[64];              /**< \brief 600, Read Data Section \note Array index shifted by 1. Example: defined register RDDS_1S[0]/RDDS_1S0 corresponds to user manual RDDS_1S1, ... */
    Ifx_ERAY_RDHS1 RDHS1;                   /**< \brief 700, Read Header Section 1 */
    Ifx_ERAY_RDHS2 RDHS2;                   /**< \brief 704, Read Header Section 2 */
    Ifx_ERAY_RDHS3 RDHS3;                   /**< \brief 708, Read Header Section 3 */
    Ifx_ERAY_MBS MBS;                       /**< \brief 70C, Message Buffer Status */
    Ifx_ERAY_OBCM OBCM;                     /**< \brief 710, Output Buffer Command Mask */
    Ifx_ERAY_OBCR OBCR;                     /**< \brief 714, Output Buffer Command Request */
    unsigned char reserved_718[344];        /**< \brief 718, \internal Reserved */
    Ifx_ERAY_OTSS OTSS;                     /**< \brief 870, OCDS Trigger Set Select */
    unsigned char reserved_874[116];        /**< \brief 874, \internal Reserved */
    Ifx_ERAY_OCS OCS;                       /**< \brief 8E8, OCDS Control and Status */
    Ifx_ERAY_KRSTCLR KRSTCLR;               /**< \brief 8EC, Kernel Reset Status Clear Register */
    Ifx_ERAY_KRST1 KRST1;                   /**< \brief 8F0, Kernel Reset Register 1 */
    Ifx_ERAY_KRST0 KRST0;                   /**< \brief 8F4, Kernel Reset Register 0 */
    Ifx_ERAY_ACCEN1 ACCEN1;                 /**< \brief 8F8, Access Enable Register 1 */
    Ifx_ERAY_ACCEN0 ACCEN0;                 /**< \brief 8FC, Access Enable Register 0 */
    unsigned char reserved_900[1792];       /**< \brief 900, \internal Reserved */
} Ifx_ERAY;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXERAY_REGDEF_H */
