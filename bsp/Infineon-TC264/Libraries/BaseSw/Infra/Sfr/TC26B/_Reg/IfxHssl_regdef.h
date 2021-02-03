/**
 * \file IfxHssl_regdef.h
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
 * \defgroup IfxLld_Hssl Hssl
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Hssl_Bitfields Bitfields
 * \ingroup IfxLld_Hssl
 * 
 * \defgroup IfxLld_Hssl_union Union
 * \ingroup IfxLld_Hssl
 * 
 * \defgroup IfxLld_Hssl_struct Struct
 * \ingroup IfxLld_Hssl
 * 
 */
#ifndef IFXHSSL_REGDEF_H
#define IFXHSSL_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Hssl_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_HSSL_ACCEN0_Bits
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
} Ifx_HSSL_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_HSSL_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_HSSL_ACCEN1_Bits;

/** \brief  Access Rules Register */
typedef struct _Ifx_HSSL_AR_Bits
{
    unsigned int ARW0:2;                    /**< \brief [1:0] Access Rule for Window 0 (rw) */
    unsigned int ARW1:2;                    /**< \brief [3:2] Access Rule for Window 1 (rw) */
    unsigned int ARW2:2;                    /**< \brief [5:4] Access Rule for Window 2 (rw) */
    unsigned int ARW3:2;                    /**< \brief [7:6] Access Rule for Window 3 (rw) */
    unsigned int reserved_8:8;              /**< \brief \internal Reserved */
    unsigned int MAVCH:2;                   /**< \brief [17:16] Memory Access Violation Channel (rh) */
    unsigned int reserved_18:14;            /**< \brief \internal Reserved */
} Ifx_HSSL_AR_Bits;

/** \brief  Access Window End Register */
typedef struct _Ifx_HSSL_AW_AWEND_Bits
{
    unsigned int reserved_0:8;              /**< \brief \internal Reserved */
    unsigned int AWE:24;                    /**< \brief [31:8] Access Window End Address (rw) */
} Ifx_HSSL_AW_AWEND_Bits;

/** \brief  Access Window Start Register */
typedef struct _Ifx_HSSL_AW_AWSTART_Bits
{
    unsigned int reserved_0:8;              /**< \brief \internal Reserved */
    unsigned int AWS:24;                    /**< \brief [31:8] Access Window Start Address (rw) */
} Ifx_HSSL_AW_AWSTART_Bits;

/** \brief  Configuration Register */
typedef struct _Ifx_HSSL_CFG_Bits
{
    unsigned int PREDIV:14;                 /**< \brief [13:0] Global Predivider (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int SMT:1;                     /**< \brief [16:16] Streaming Mode Transmitter (rw) */
    unsigned int SMR:1;                     /**< \brief [17:17] Streaming Mode Receiver (rw) */
    unsigned int SCM:1;                     /**< \brief [18:18] Streaming Channel Mode (rw) */
    unsigned int CCC:1;                     /**< \brief [19:19] Channel Code Control (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_HSSL_CFG_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_HSSL_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_HSSL_CLC_Bits;

/** \brief  CRC Control Register */
typedef struct _Ifx_HSSL_CRC_Bits
{
    unsigned int XORMASK:16;                /**< \brief [15:0] Value to be XORed with the Calculated CRC (rw) */
    unsigned int XEN:1;                     /**< \brief [16:16] Enable the Error Injection via XORMASK (rw) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_HSSL_CRC_Bits;

/** \brief  Initiator Control Data Register */
typedef struct _Ifx_HSSL_I_ICON_Bits
{
    unsigned int IDQ:1;                     /**< \brief [0:0] Read ID Request (w) */
    unsigned int TQ:1;                      /**< \brief [1:1] Trigger Request (w) */
    unsigned int LETT:3;                    /**< \brief [4:2] Last Error Transaction Tag (rh) */
    unsigned int CETT:3;                    /**< \brief [7:5] Currently Expected Transaction Tag (rh) */
    unsigned int TOCV:8;                    /**< \brief [15:8] Time Out Current Value (rh) */
    unsigned int DATLEN:2;                  /**< \brief [17:16] Data Length (rw) */
    unsigned int RWT:2;                     /**< \brief [19:18] Read Write Trigger Command Type (rw) */
    unsigned int BSY:1;                     /**< \brief [20:20] Channel Busy (rh) */
    unsigned int ITTAG:3;                   /**< \brief [23:21] Initiator Transaction Tag (rh) */
    unsigned int TOREL:8;                   /**< \brief [31:24] Time Out Reload Value (rw) */
} Ifx_HSSL_I_ICON_Bits;

/** \brief  Initiator Read Data Register */
typedef struct _Ifx_HSSL_I_IRD_Bits
{
    unsigned int DATA:32;                   /**< \brief [31:0] Data Delivered by a Read Response Frame (rh) */
} Ifx_HSSL_I_IRD_Bits;

/** \brief  Initiator Read Write Address Register */
typedef struct _Ifx_HSSL_I_IRWA_Bits
{
    unsigned int ADDRESS:32;                /**< \brief [31:0] Address Part of the Payload of a Write Frame (rw) */
} Ifx_HSSL_I_IRWA_Bits;

/** \brief  Initiator Write Data Register */
typedef struct _Ifx_HSSL_I_IWD_Bits
{
    unsigned int DATA:32;                   /**< \brief [31:0] Data Part of the Payload of a Write Frame (rw) */
} Ifx_HSSL_I_IWD_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_HSSL_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_HSSL_ID_Bits;

/** \brief  Initiator Stream Current Address Register */
typedef struct _Ifx_HSSL_IS_CA_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int CURR:27;                   /**< \brief [31:5] Address of the Memory Location for the Current Transfer (rh) */
} Ifx_HSSL_IS_CA_Bits;

/** \brief  Initiator Stream Frame Count Register */
typedef struct _Ifx_HSSL_IS_FC_Bits
{
    unsigned int RELCOUNT:16;               /**< \brief [15:0] Reload Count Number (rw) */
    unsigned int CURCOUNT:16;               /**< \brief [31:16] Current Count Number (rh) */
} Ifx_HSSL_IS_FC_Bits;

/** \brief  Initiator Stream Start Address Register */
typedef struct _Ifx_HSSL_ISSA_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int START:27;                  /**< \brief [31:5] Start Address for the Memory Range (rw) */
} Ifx_HSSL_ISSA_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_HSSL_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_HSSL_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_HSSL_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_HSSL_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_HSSL_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_HSSL_KRSTCLR_Bits;

/** \brief  Miscellaneous Flags Register */
typedef struct _Ifx_HSSL_MFLAGS_Bits
{
    unsigned int NACK:4;                    /**< \brief [3:0] Not Acknowledge Error - Target Error (rh) */
    unsigned int TTE:4;                     /**< \brief [7:4] Transaction Tag Error (rh) */
    unsigned int TIMEOUT:4;                 /**< \brief [11:8] Timeout Error (rh) */
    unsigned int UNEXPECTED:4;              /**< \brief [15:12] Unexpected Type of Frame Error (rh) */
    unsigned int reserved_16:2;             /**< \brief \internal Reserved */
    unsigned int TMB:1;                     /**< \brief [18:18] Target Memory Block (rh) */
    unsigned int IMB:1;                     /**< \brief [19:19] Initiator Memory Block (rh) */
    unsigned int ISB:1;                     /**< \brief [20:20] Initiator Stream Block Request (rh) */
    unsigned int MAV:1;                     /**< \brief [21:21] Memory Access Violation (rh) */
    unsigned int SRIE:1;                    /**< \brief [22:22] SRI/SPB Bus Access Error (rh) */
    unsigned int PIE1:1;                    /**< \brief [23:23] PHY Inconsistency Error 1 (rh) */
    unsigned int PIE2:1;                    /**< \brief [24:24] PHY Inconsistency Error 2 (rh) */
    unsigned int CRCE:1;                    /**< \brief [25:25] CRC Error (rh) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int TSE:1;                     /**< \brief [28:28] Target Stream Enable (rh) */
    unsigned int TEI:1;                     /**< \brief [29:29] Transmit Enable Input (rh) */
    unsigned int TEO:1;                     /**< \brief [30:30] Transmit Enable Output (rh) */
    unsigned int INI:1;                     /**< \brief [31:31] Initialize Mode (rh) */
} Ifx_HSSL_MFLAGS_Bits;

/** \brief  Miscellaneous Flags Clear Register */
typedef struct _Ifx_HSSL_MFLAGSCL_Bits
{
    unsigned int NACKC:4;                   /**< \brief [3:0] NACK Flags Clear (w) */
    unsigned int TTEC:4;                    /**< \brief [7:4] Transaction Tag Error Flags Clear (w) */
    unsigned int TIMEOUTC:4;                /**< \brief [11:8] Timeout Error Flags Clear (w) */
    unsigned int UNEXPECTEDC:4;             /**< \brief [15:12] Unexpected Error Flags Clear (w) */
    unsigned int reserved_16:2;             /**< \brief \internal Reserved */
    unsigned int TMBC:1;                    /**< \brief [18:18] Target Memory Block Flag Clear (w) */
    unsigned int IMBC:1;                    /**< \brief [19:19] Initiator Memory Block Flag Clear (w) */
    unsigned int ISBC:1;                    /**< \brief [20:20] Initiator Stream Block Request Clear (w) */
    unsigned int MAVC:1;                    /**< \brief [21:21] MAV Flag Clear (w) */
    unsigned int SRIEC:1;                   /**< \brief [22:22] SRI/SPB Bus Access Error Flag Clear (w) */
    unsigned int PIE1C:1;                   /**< \brief [23:23] PIE1 Error Flag Clear (w) */
    unsigned int PIE2C:1;                   /**< \brief [24:24] PIE2 Error Flag Clear (w) */
    unsigned int CRCEC:1;                   /**< \brief [25:25] CRC Error Flag Clear (w) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int TSEC:1;                    /**< \brief [28:28] Target Stream Enable Flag Clear (w) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int TEOC:1;                    /**< \brief [30:30] Transmit Enable Flag Clear (w) */
    unsigned int INIC:1;                    /**< \brief [31:31] Initialize Mode Flag Clear (w) */
} Ifx_HSSL_MFLAGSCL_Bits;

/** \brief  Flags Enable Register */
typedef struct _Ifx_HSSL_MFLAGSEN_Bits
{
    unsigned int NACKEN:4;                  /**< \brief [3:0] Not Acknowledge Error Enable Bits (rw) */
    unsigned int TTEEN:4;                   /**< \brief [7:4] Transaction Tag Error Enable Bits (rw) */
    unsigned int TIMEOUTEN:4;               /**< \brief [11:8] Timeout Error Enable Bits (rw) */
    unsigned int UNEXPECTEDEN:4;            /**< \brief [15:12] Unexpected Error Enable Bits (rw) */
    unsigned int reserved_16:5;             /**< \brief \internal Reserved */
    unsigned int MAVEN:1;                   /**< \brief [21:21] MAV Enable Bit (rw) */
    unsigned int SRIEEN:1;                  /**< \brief [22:22] SRI/SPB Bus Access Error Enable Bit (rw) */
    unsigned int PIE1EN:1;                  /**< \brief [23:23] PIE1 Error Enable Bit (rw) */
    unsigned int PIE2EN:1;                  /**< \brief [24:24] PIE2 Error Enable Bit (rw) */
    unsigned int CRCEEN:1;                  /**< \brief [25:25] CRC Error Enable Bit (rw) */
    unsigned int reserved_26:3;             /**< \brief \internal Reserved */
    unsigned int TEIEN:1;                   /**< \brief [29:29] TEI Enable Bit (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_HSSL_MFLAGSEN_Bits;

/** \brief  Miscellaneous Flags Set Register */
typedef struct _Ifx_HSSL_MFLAGSSET_Bits
{
    unsigned int NACKS:4;                   /**< \brief [3:0] NACK Flags Set (w) */
    unsigned int TTES:4;                    /**< \brief [7:4] Transaction Tag Error Flags Set (w) */
    unsigned int TIMEOUTS:4;                /**< \brief [11:8] Timeout Error Flags Set (w) */
    unsigned int UNEXPECTEDS:4;             /**< \brief [15:12] Unexpected Error Flags Set (w) */
    unsigned int reserved_16:2;             /**< \brief \internal Reserved */
    unsigned int TMBS:1;                    /**< \brief [18:18] Target Memory Block Flag Set (w) */
    unsigned int IMBS:1;                    /**< \brief [19:19] Initiator Memory Block Flag Set (w) */
    unsigned int ISBS:1;                    /**< \brief [20:20] Initiator Stream Block Request Set (w) */
    unsigned int MAVS:1;                    /**< \brief [21:21] MAV Flag Set (w) */
    unsigned int SRIES:1;                   /**< \brief [22:22] SRI/SPB Bus Access Error Flag Set (w) */
    unsigned int PIE1S:1;                   /**< \brief [23:23] PIE1 Error Flag Set (w) */
    unsigned int PIE2S:1;                   /**< \brief [24:24] PIE2 Error Flag Set (w) */
    unsigned int CRCES:1;                   /**< \brief [25:25] CRC Error Flag Set (w) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int TSES:1;                    /**< \brief [28:28] Target Stream Enable Flag Set (w) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int TEOS:1;                    /**< \brief [30:30] Transmit Enable Flag Set (w) */
    unsigned int INIS:1;                    /**< \brief [31:31] Initialize Mode Flag Set (w) */
} Ifx_HSSL_MFLAGSSET_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_HSSL_OCS_Bits
{
    unsigned int TGS:2;                     /**< \brief [1:0] Trigger Set for OTGB0/1 (rw) */
    unsigned int TGB:1;                     /**< \brief [2:2] OTGB0/1 Bus Select (rw) */
    unsigned int TG_P:1;                    /**< \brief [3:3] TGS, TGB Write Protection (w) */
    unsigned int reserved_4:20;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_HSSL_OCS_Bits;

/** \brief  Request Flags Register */
typedef struct _Ifx_HSSL_QFLAGS_Bits
{
    unsigned int I:4;                       /**< \brief [3:0] Request Flags for Initiated Commands (rh) */
    unsigned int T:4;                       /**< \brief [7:4] Request Flags for Commands Arrived at Target (rh) */
    unsigned int R:4;                       /**< \brief [11:8] Request Flags for Response Frames at the Target (rh) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int E0:2;                      /**< \brief [17:16] Expect Flags for Activated Timeout Timer 0 (rh) */
    unsigned int E1:2;                      /**< \brief [19:18] Expect Flags for Activated Timeout Timer 1 (rh) */
    unsigned int E2:2;                      /**< \brief [21:20] Expect Flags for Activated Timeout Timer 2 (rh) */
    unsigned int E3:2;                      /**< \brief [23:22] Expect Flags for Activated Timeout Timer 3 (rh) */
    unsigned int reserved_24:4;             /**< \brief \internal Reserved */
    unsigned int IS:1;                      /**< \brief [28:28] I Flag for Stream Frames (rh) */
    unsigned int RS:1;                      /**< \brief [29:29] R Flag for Stream Frames (rh) */
    unsigned int TS:1;                      /**< \brief [30:30] T Flag for Stream Frames (rh) */
    unsigned int ES:1;                      /**< \brief [31:31] E Flag for Stream Frames (rh) */
} Ifx_HSSL_QFLAGS_Bits;

/** \brief  Stream FIFOs Status Flags Register */
typedef struct _Ifx_HSSL_SFSFLAGS_Bits
{
    unsigned int RXFL:2;                    /**< \brief [1:0] Stream RxFIFO Filling Level (rh) */
    unsigned int TXFL:2;                    /**< \brief [3:2] Stream TxFIFO Filling Level (rh) */
    unsigned int EXFL:2;                    /**< \brief [5:4] Stream Expect FIFO Filling Level (rh) */
    unsigned int reserved_6:9;              /**< \brief \internal Reserved */
    unsigned int ISF:1;                     /**< \brief [15:15] Initiator Stream Frame Request (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_HSSL_SFSFLAGS_Bits;

/** \brief  Target Current Address Register */
typedef struct _Ifx_HSSL_T_TCA_Bits
{
    unsigned int A:32;                      /**< \brief [31:0] Address Part of the Payload of a Write Command Frame or a Read Command Frame or ID Frame (rh) */
} Ifx_HSSL_T_TCA_Bits;

/** \brief  Target Current Data Register */
typedef struct _Ifx_HSSL_T_TCD_Bits
{
    unsigned int D:32;                      /**< \brief [31:0] Data Part of the Payload of a Write Command Frame or Read Data of a Read Command Frame (rh) */
} Ifx_HSSL_T_TCD_Bits;

/** \brief  Target ID Address Register */
typedef struct _Ifx_HSSL_TIDADD_Bits
{
    unsigned int A:32;                      /**< \brief [31:0] Address Pointer (rw) */
} Ifx_HSSL_TIDADD_Bits;

/** \brief  Target Stream Current Address Register */
typedef struct _Ifx_HSSL_TS_CA_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int CURR:27;                   /**< \brief [31:5] Address of the Memory Location for the Current Transfer (rh) */
} Ifx_HSSL_TS_CA_Bits;

/** \brief  Target Stream Frame Count Register */
typedef struct _Ifx_HSSL_TS_FC_Bits
{
    unsigned int RELCOUNT:16;               /**< \brief [15:0] Reload Count Number (rw) */
    unsigned int CURCOUNT:16;               /**< \brief [31:16] Current Count Number (rh) */
} Ifx_HSSL_TS_FC_Bits;

/** \brief  Target Stream Start Address Register */
typedef struct _Ifx_HSSL_TSSA_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int ADDR:27;                   /**< \brief [31:5] Start Address for the Memory Range (rw) */
} Ifx_HSSL_TSSA_Bits;

/** \brief  Target Status Register */
typedef struct _Ifx_HSSL_TSTAT_Bits
{
    unsigned int LASTCC0:5;                 /**< \brief [4:0] Last Command Code (rh) */
    unsigned int LASTTT0:3;                 /**< \brief [7:5] Last Transaction Tag (rh) */
    unsigned int LASTCC1:5;                 /**< \brief [12:8] Last Command Code (rh) */
    unsigned int LASTTT1:3;                 /**< \brief [15:13] Last Transaction Tag (rh) */
    unsigned int LASTCC2:5;                 /**< \brief [20:16] Last Command Code (rh) */
    unsigned int LASTTT2:3;                 /**< \brief [23:21] Last Transaction Tag (rh) */
    unsigned int LASTCC3:5;                 /**< \brief [28:24] Last Command Code (rh) */
    unsigned int LASTTT3:3;                 /**< \brief [31:29] Last Transaction Tag (rh) */
} Ifx_HSSL_TSTAT_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Hssl_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSSL_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSSL_ACCEN1;

/** \brief  Access Rules Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_AR_Bits B;                     /**< \brief Bitfield access */
} Ifx_HSSL_AR;

/** \brief  Access Window End Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_AW_AWEND_Bits B;               /**< \brief Bitfield access */
} Ifx_HSSL_AW_AWEND;

/** \brief  Access Window Start Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_AW_AWSTART_Bits B;             /**< \brief Bitfield access */
} Ifx_HSSL_AW_AWSTART;

/** \brief  Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_CFG_Bits B;                    /**< \brief Bitfield access */
} Ifx_HSSL_CFG;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_CLC_Bits B;                    /**< \brief Bitfield access */
} Ifx_HSSL_CLC;

/** \brief  CRC Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_CRC_Bits B;                    /**< \brief Bitfield access */
} Ifx_HSSL_CRC;

/** \brief  Initiator Control Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_I_ICON_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSSL_I_ICON;

/** \brief  Initiator Read Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_I_IRD_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_I_IRD;

/** \brief  Initiator Read Write Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_I_IRWA_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSSL_I_IRWA;

/** \brief  Initiator Write Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_I_IWD_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_I_IWD;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_HSSL_ID;

/** \brief  Initiator Stream Current Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_IS_CA_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_IS_CA;

/** \brief  Initiator Stream Frame Count Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_IS_FC_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_IS_FC;

/** \brief  Initiator Stream Start Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_ISSA_Bits B;                   /**< \brief Bitfield access */
} Ifx_HSSL_ISSA;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_KRST0_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_KRST1_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_KRSTCLR_Bits B;                /**< \brief Bitfield access */
} Ifx_HSSL_KRSTCLR;

/** \brief  Miscellaneous Flags Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_MFLAGS_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSSL_MFLAGS;

/** \brief  Miscellaneous Flags Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_MFLAGSCL_Bits B;               /**< \brief Bitfield access */
} Ifx_HSSL_MFLAGSCL;

/** \brief  Flags Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_MFLAGSEN_Bits B;               /**< \brief Bitfield access */
} Ifx_HSSL_MFLAGSEN;

/** \brief  Miscellaneous Flags Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_MFLAGSSET_Bits B;              /**< \brief Bitfield access */
} Ifx_HSSL_MFLAGSSET;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_OCS_Bits B;                    /**< \brief Bitfield access */
} Ifx_HSSL_OCS;

/** \brief  Request Flags Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_QFLAGS_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSSL_QFLAGS;

/** \brief  Stream FIFOs Status Flags Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_SFSFLAGS_Bits B;               /**< \brief Bitfield access */
} Ifx_HSSL_SFSFLAGS;

/** \brief  Target Current Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_T_TCA_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_T_TCA;

/** \brief  Target Current Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_T_TCD_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_T_TCD;

/** \brief  Target ID Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_TIDADD_Bits B;                 /**< \brief Bitfield access */
} Ifx_HSSL_TIDADD;

/** \brief  Target Stream Current Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_TS_CA_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_TS_CA;

/** \brief  Target Stream Frame Count Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_TS_FC_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_TS_FC;

/** \brief  Target Stream Start Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_TSSA_Bits B;                   /**< \brief Bitfield access */
} Ifx_HSSL_TSSA;

/** \brief  Target Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_HSSL_TSTAT_Bits B;                  /**< \brief Bitfield access */
} Ifx_HSSL_TSTAT;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Hssl_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Access window */
typedef volatile struct _Ifx_HSSL_AW
{
    Ifx_HSSL_AW_AWSTART AWSTART;            /**< \brief 0, Access Window Start Register */
    Ifx_HSSL_AW_AWEND AWEND;                /**< \brief 4, Access Window End Register */
} Ifx_HSSL_AW;

/** \brief  Initiator */
typedef volatile struct _Ifx_HSSL_I
{
    Ifx_HSSL_I_IWD IWD;                     /**< \brief 0, Initiator Write Data Register */
    Ifx_HSSL_I_ICON ICON;                   /**< \brief 4, Initiator Control Data Register */
    Ifx_HSSL_I_IRWA IRWA;                   /**< \brief 8, Initiator Read Write Address Register */
    Ifx_HSSL_I_IRD IRD;                     /**< \brief C, Initiator Read Data Register */
} Ifx_HSSL_I;

/** \brief  Initiator stream */
typedef volatile struct _Ifx_HSSL_IS
{
    Ifx_HSSL_ISSA SA[2];                    /**< \brief 0, Initiator Stream Start Address Register */
    Ifx_HSSL_IS_CA CA;                      /**< \brief 8, Initiator Stream Current Address Register */
    Ifx_HSSL_IS_FC FC;                      /**< \brief C, Initiator Stream Frame Count Register */
} Ifx_HSSL_IS;

/** \brief  target */
typedef volatile struct _Ifx_HSSL_T
{
    Ifx_HSSL_T_TCD TCD;                     /**< \brief 0, Target Current Data Register */
    Ifx_HSSL_T_TCA TCA;                     /**< \brief 4, Target Current Address Register */
} Ifx_HSSL_T;

/** \brief  Target stream */
typedef volatile struct _Ifx_HSSL_TS
{
    Ifx_HSSL_TSSA SA[2];                    /**< \brief 0, Target Stream Start Address Register */
    Ifx_HSSL_TS_CA CA;                      /**< \brief 8, Target Stream Current Address Register */
    Ifx_HSSL_TS_FC FC;                      /**< \brief C, Target Stream Frame Count Register */
} Ifx_HSSL_TS;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Hssl_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  HSSL object */
typedef volatile struct _Ifx_HSSL
{
    Ifx_HSSL_CLC CLC;                       /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_HSSL_ID ID;                         /**< \brief 8, Module Identification Register */
    Ifx_HSSL_CRC CRC;                       /**< \brief C, CRC Control Register */
    Ifx_HSSL_CFG CFG;                       /**< \brief 10, Configuration Register */
    Ifx_HSSL_QFLAGS QFLAGS;                 /**< \brief 14, Request Flags Register */
    Ifx_HSSL_MFLAGS MFLAGS;                 /**< \brief 18, Miscellaneous Flags Register */
    Ifx_HSSL_MFLAGSSET MFLAGSSET;           /**< \brief 1C, Miscellaneous Flags Set Register */
    Ifx_HSSL_MFLAGSCL MFLAGSCL;             /**< \brief 20, Miscellaneous Flags Clear Register */
    Ifx_HSSL_MFLAGSEN MFLAGSEN;             /**< \brief 24, Flags Enable Register */
    Ifx_HSSL_SFSFLAGS SFSFLAGS;             /**< \brief 28, Stream FIFOs Status Flags Register */
    unsigned char reserved_2C[4];           /**< \brief 2C, \internal Reserved */
    Ifx_HSSL_I I[4];                        /**< \brief 30, Initiator */
    Ifx_HSSL_T T[4];                        /**< \brief 70, target */
    Ifx_HSSL_TSTAT TSTAT;                   /**< \brief 90, Target Status Register */
    Ifx_HSSL_TIDADD TIDADD;                 /**< \brief 94, Target ID Address Register */
    unsigned char reserved_98[8];           /**< \brief 98, \internal Reserved */
    Ifx_HSSL_IS IS;                         /**< \brief A0, Initiator stream */
    Ifx_HSSL_TS TS;                         /**< \brief B0, Target stream */
    Ifx_HSSL_AW AW[4];                      /**< \brief C0, Access window */
    Ifx_HSSL_AR AR;                         /**< \brief E0, Access Rules Register */
    unsigned char reserved_E4[4];           /**< \brief E4, \internal Reserved */
    Ifx_HSSL_OCS OCS;                       /**< \brief E8, OCDS Control and Status */
    Ifx_HSSL_KRSTCLR KRSTCLR;               /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_HSSL_KRST1 KRST1;                   /**< \brief F0, Kernel Reset Register 1 */
    Ifx_HSSL_KRST0 KRST0;                   /**< \brief F4, Kernel Reset Register 0 */
    Ifx_HSSL_ACCEN1 ACCEN1;                 /**< \brief F8, Access Enable Register 1 */
    Ifx_HSSL_ACCEN0 ACCEN0;                 /**< \brief FC, Access Enable Register 0 */
    unsigned char reserved_100[768];        /**< \brief 100, \internal Reserved */
} Ifx_HSSL;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXHSSL_REGDEF_H */
