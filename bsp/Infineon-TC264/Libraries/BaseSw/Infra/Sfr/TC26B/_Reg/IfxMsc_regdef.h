/**
 * \file IfxMsc_regdef.h
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
 * \defgroup IfxLld_Msc Msc
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Msc_Bitfields Bitfields
 * \ingroup IfxLld_Msc
 * 
 * \defgroup IfxLld_Msc_union Union
 * \ingroup IfxLld_Msc
 * 
 * \defgroup IfxLld_Msc_struct Struct
 * \ingroup IfxLld_Msc
 * 
 */
#ifndef IFXMSC_REGDEF_H
#define IFXMSC_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Msc_Bitfields
 * \{  */

/** \brief  Asynchronous Block Configuration Register */
typedef struct _Ifx_MSC_ABC_Bits
{
    unsigned int LOW:4;                     /**< \brief [3:0] Duration of the Low Phase of the Shift Clock (rw) */
    unsigned int HIGH:4;                    /**< \brief [7:4] Duration of the High Phase of the Shift Clock (rw) */
    unsigned int OIP:2;                     /**< \brief [9:8] Overflow Interrupt Node Pointer (rw) */
    unsigned int OASR:1;                    /**< \brief [10:10] Overflow Alternate Service Request (rw) */
    unsigned int reserved_11:1;             /**< \brief \internal Reserved */
    unsigned int OVF:1;                     /**< \brief [12:12] Overflow Flag (r) */
    unsigned int OFM:2;                     /**< \brief [14:13] Overflow Flag Modify (w) */
    unsigned int OIE:1;                     /**< \brief [15:15] Overflow Interrupt Enable (rw) */
    unsigned int NDA:3;                     /**< \brief [18:16] N Divider ABRA (rw) */
    unsigned int UIP:2;                     /**< \brief [20:19] Underflow Interrupt Node Pointer (rw) */
    unsigned int UASR:1;                    /**< \brief [21:21] Underflow Alternate Service Request (rw) */
    unsigned int reserved_22:1;             /**< \brief \internal Reserved */
    unsigned int UNF:1;                     /**< \brief [23:23] Underflow Flag (r) */
    unsigned int UFM:2;                     /**< \brief [25:24] Underflow Flag Modify (w) */
    unsigned int UIE:1;                     /**< \brief [26:26] Underflow Interrupt Enable (rw) */
    unsigned int CLKSEL:3;                  /**< \brief [29:27] Clock Select (rw) */
    unsigned int reserved_30:1;             /**< \brief \internal Reserved */
    unsigned int ABB:1;                     /**< \brief [31:31] Asynchronous Block Bypass (rw) */
} Ifx_MSC_ABC_Bits;

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_MSC_ACCEN0_Bits
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
} Ifx_MSC_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_MSC_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_MSC_ACCEN1_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_MSC_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_MSC_CLC_Bits;

/** \brief  Downstream Command Register */
typedef struct _Ifx_MSC_DC_Bits
{
    unsigned int DCL:16;                    /**< \brief [15:0] Downstream Command for SRL Shift Register (rw) */
    unsigned int DCH:16;                    /**< \brief [31:16] Downstream Command for SRH Shift Register (rw) */
} Ifx_MSC_DC_Bits;

/** \brief  Downstream Data Register */
typedef struct _Ifx_MSC_DD_Bits
{
    unsigned int DDL:16;                    /**< \brief [15:0] Downstream Data for SRL Shift Register (rw) */
    unsigned int DDH:16;                    /**< \brief [31:16] Downstream Data for SRH Shift Register (rw) */
} Ifx_MSC_DD_Bits;

/** \brief  Downstream Data Extension Register */
typedef struct _Ifx_MSC_DDE_Bits
{
    unsigned int DDLE:16;                   /**< \brief [15:0] Downstream Data Extension for SRL Shift Register (rw) */
    unsigned int DDHE:16;                   /**< \brief [31:16] Downstream Data Extension for SRH Shift Register (rw) */
} Ifx_MSC_DDE_Bits;

/** \brief  Downstream Data Mirror Register */
typedef struct _Ifx_MSC_DDM_Bits
{
    unsigned int DDLM:16;                   /**< \brief [15:0] Downstream Data Mirror for SRL Shift Register (w) */
    unsigned int DDHM:16;                   /**< \brief [31:16] Downstream Data Mirror for SRH Shift Register (w) */
} Ifx_MSC_DDM_Bits;

/** \brief  Downstream Control Register */
typedef struct _Ifx_MSC_DSC_Bits
{
    unsigned int TM:1;                      /**< \brief [0:0] Transmission Mode (rw) */
    unsigned int CP:1;                      /**< \brief [1:1] Command Pending (rh) */
    unsigned int DP:1;                      /**< \brief [2:2] Data Pending (rh) */
    unsigned int NDBL:5;                    /**< \brief [7:3] Number of SRL Bits Shifted at Data Frames (rw) */
    unsigned int NDBH:5;                    /**< \brief [12:8] Number of SRH Bits Shifted at Data Frames (rw) */
    unsigned int ENSELL:1;                  /**< \brief [13:13] Enable SRL Active Phase Selection Bit (rw) */
    unsigned int ENSELH:1;                  /**< \brief [14:14] Enable SRH Active Phase Selection Bit (rw) */
    unsigned int DSDIS:1;                   /**< \brief [15:15] Downstream Disable (rh) */
    unsigned int NBC:6;                     /**< \brief [21:16] Number of Bits Shifted at Command Frames (rw) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int PPD:5;                     /**< \brief [28:24] Passive Phase Length at Data Frames (rw) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_MSC_DSC_Bits;

/** \brief  Downstream Control Enhanced Register 1 */
typedef struct _Ifx_MSC_DSCE_Bits
{
    unsigned int NDBHE:1;                   /**< \brief [0:0] Number of SRH Bits Shifted at Data Frames Extension (rw) */
    unsigned int NDBLE:1;                   /**< \brief [1:1] Number of SRH Bits Shifted at Data Frames Extension (rw) */
    unsigned int reserved_2:12;             /**< \brief \internal Reserved */
    unsigned int EXEN:1;                    /**< \brief [14:14] Extension Enable (rw) */
    unsigned int CCF:1;                     /**< \brief [15:15] Command-Comand Flag (rh) */
    unsigned int INJENP0:1;                 /**< \brief [16:16] Injection Enable of the Pin 0 Signal (rw) */
    unsigned int INJPOSP0:6;                /**< \brief [22:17] Injection Position of the Pin 0 Signal (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int INJENP1:1;                 /**< \brief [24:24] Injection Enable of the Pin 1 Signal (rw) */
    unsigned int INJPOSP1:6;                /**< \brief [30:25] Injection Position of the Pin 1 Signal (rw) */
    unsigned int CDCM:1;                    /**< \brief [31:31] Command-Data-Comand in Data Repetition Mode (rw) */
} Ifx_MSC_DSCE_Bits;

/** \brief  Downstream Select Data Source High Register */
typedef struct _Ifx_MSC_DSDSH_Bits
{
    unsigned int SH0:2;                     /**< \brief [1:0] Select Source for SRH (rw) */
    unsigned int SH1:2;                     /**< \brief [3:2] Select Source for SRH (rw) */
    unsigned int SH2:2;                     /**< \brief [5:4] Select Source for SRH (rw) */
    unsigned int SH3:2;                     /**< \brief [7:6] Select Source for SRH (rw) */
    unsigned int SH4:2;                     /**< \brief [9:8] Select Source for SRH (rw) */
    unsigned int SH5:2;                     /**< \brief [11:10] Select Source for SRH (rw) */
    unsigned int SH6:2;                     /**< \brief [13:12] Select Source for SRH (rw) */
    unsigned int SH7:2;                     /**< \brief [15:14] Select Source for SRH (rw) */
    unsigned int SH8:2;                     /**< \brief [17:16] Select Source for SRH (rw) */
    unsigned int SH9:2;                     /**< \brief [19:18] Select Source for SRH (rw) */
    unsigned int SH10:2;                    /**< \brief [21:20] Select Source for SRH (rw) */
    unsigned int SH11:2;                    /**< \brief [23:22] Select Source for SRH (rw) */
    unsigned int SH12:2;                    /**< \brief [25:24] Select Source for SRH (rw) */
    unsigned int SH13:2;                    /**< \brief [27:26] Select Source for SRH (rw) */
    unsigned int SH14:2;                    /**< \brief [29:28] Select Source for SRH (rw) */
    unsigned int SH15:2;                    /**< \brief [31:30] Select Source for SRH (rw) */
} Ifx_MSC_DSDSH_Bits;

/** \brief  Downstream Select Data Source High Register */
typedef struct _Ifx_MSC_DSDSHE_Bits
{
    unsigned int SH16:2;                    /**< \brief [1:0] Select Source for SRH (rw) */
    unsigned int SH17:2;                    /**< \brief [3:2] Select Source for SRH (rw) */
    unsigned int SH18:2;                    /**< \brief [5:4] Select Source for SRH (rw) */
    unsigned int SH19:2;                    /**< \brief [7:6] Select Source for SRH (rw) */
    unsigned int SH20:2;                    /**< \brief [9:8] Select Source for SRH (rw) */
    unsigned int SH21:2;                    /**< \brief [11:10] Select Source for SRH (rw) */
    unsigned int SH22:2;                    /**< \brief [13:12] Select Source for SRH (rw) */
    unsigned int SH23:2;                    /**< \brief [15:14] Select Source for SRH (rw) */
    unsigned int SH24:2;                    /**< \brief [17:16] Select Source for SRH (rw) */
    unsigned int SH25:2;                    /**< \brief [19:18] Select Source for SRH (rw) */
    unsigned int SH26:2;                    /**< \brief [21:20] Select Source for SRH (rw) */
    unsigned int SH27:2;                    /**< \brief [23:22] Select Source for SRH (rw) */
    unsigned int SH28:2;                    /**< \brief [25:24] Select Source for SRH (rw) */
    unsigned int SH29:2;                    /**< \brief [27:26] Select Source for SRH (rw) */
    unsigned int SH30:2;                    /**< \brief [29:28] Select Source for SRH (rw) */
    unsigned int SH31:2;                    /**< \brief [31:30] Select Source for SRH (rw) */
} Ifx_MSC_DSDSHE_Bits;

/** \brief  Downstream Select Data Source Low Register */
typedef struct _Ifx_MSC_DSDSL_Bits
{
    unsigned int SL0:2;                     /**< \brief [1:0] Select Source for SRL (rw) */
    unsigned int SL1:2;                     /**< \brief [3:2] Select Source for SRL (rw) */
    unsigned int SL2:2;                     /**< \brief [5:4] Select Source for SRL (rw) */
    unsigned int SL3:2;                     /**< \brief [7:6] Select Source for SRL (rw) */
    unsigned int SL4:2;                     /**< \brief [9:8] Select Source for SRL (rw) */
    unsigned int SL5:2;                     /**< \brief [11:10] Select Source for SRL (rw) */
    unsigned int SL6:2;                     /**< \brief [13:12] Select Source for SRL (rw) */
    unsigned int SL7:2;                     /**< \brief [15:14] Select Source for SRL (rw) */
    unsigned int SL8:2;                     /**< \brief [17:16] Select Source for SRL (rw) */
    unsigned int SL9:2;                     /**< \brief [19:18] Select Source for SRL (rw) */
    unsigned int SL10:2;                    /**< \brief [21:20] Select Source for SRL (rw) */
    unsigned int SL11:2;                    /**< \brief [23:22] Select Source for SRL (rw) */
    unsigned int SL12:2;                    /**< \brief [25:24] Select Source for SRL (rw) */
    unsigned int SL13:2;                    /**< \brief [27:26] Select Source for SRL (rw) */
    unsigned int SL14:2;                    /**< \brief [29:28] Select Source for SRL (rw) */
    unsigned int SL15:2;                    /**< \brief [31:30] Select Source for SRL (rw) */
} Ifx_MSC_DSDSL_Bits;

/** \brief  Downstream Select Data Source Low Extension Register */
typedef struct _Ifx_MSC_DSDSLE_Bits
{
    unsigned int SL16:2;                    /**< \brief [1:0] Select Source for SRL (rw) */
    unsigned int SL17:2;                    /**< \brief [3:2] Select Source for SRL (rw) */
    unsigned int SL18:2;                    /**< \brief [5:4] Select Source for SRL (rw) */
    unsigned int SL19:2;                    /**< \brief [7:6] Select Source for SRL (rw) */
    unsigned int SL20:2;                    /**< \brief [9:8] Select Source for SRL (rw) */
    unsigned int SL21:2;                    /**< \brief [11:10] Select Source for SRL (rw) */
    unsigned int SL22:2;                    /**< \brief [13:12] Select Source for SRL (rw) */
    unsigned int SL23:2;                    /**< \brief [15:14] Select Source for SRL (rw) */
    unsigned int SL24:2;                    /**< \brief [17:16] Select Source for SRL (rw) */
    unsigned int SL25:2;                    /**< \brief [19:18] Select Source for SRL (rw) */
    unsigned int SL26:2;                    /**< \brief [21:20] Select Source for SRL (rw) */
    unsigned int SL27:2;                    /**< \brief [23:22] Select Source for SRL (rw) */
    unsigned int SL28:2;                    /**< \brief [25:24] Select Source for SRL (rw) */
    unsigned int SL29:2;                    /**< \brief [27:26] Select Source for SRL (rw) */
    unsigned int SL30:2;                    /**< \brief [29:28] Select Source for SRL (rw) */
    unsigned int SL31:2;                    /**< \brief [31:30] Select Source for SRL (rw) */
} Ifx_MSC_DSDSLE_Bits;

/** \brief  Downstream Status Register */
typedef struct _Ifx_MSC_DSS_Bits
{
    unsigned int PFC:4;                     /**< \brief [3:0] Passive Time Frame Counter (rh) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int NPTF:4;                    /**< \brief [11:8] Number Of Passive Time Frames (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int DC:8;                      /**< \brief [23:16] Downstream Counter (rh) */
    unsigned int DFA:1;                     /**< \brief [24:24] Data Frame Active (rh) */
    unsigned int CFA:1;                     /**< \brief [25:25] Command Frame Active (rh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_MSC_DSS_Bits;

/** \brief  Downstream Timing Extension Register */
typedef struct _Ifx_MSC_DSTE_Bits
{
    unsigned int PPDE:2;                    /**< \brief [1:0] Passive Phase Length at Data Frames Extension (rw) */
    unsigned int PPCE:6;                    /**< \brief [7:2] Passive Phase Length at Control Frames Extension (rw) */
    unsigned int NDD:4;                     /**< \brief [11:8] N Divider Downstream (rw) */
    unsigned int reserved_12:20;            /**< \brief \internal Reserved */
} Ifx_MSC_DSTE_Bits;

/** \brief  Emergency Stop Register */
typedef struct _Ifx_MSC_ESR_Bits
{
    unsigned int ENL0:1;                    /**< \brief [0:0] Emergency Stop Enable for Bit 0 in SRL (rw) */
    unsigned int ENL1:1;                    /**< \brief [1:1] Emergency Stop Enable for Bit 1 in SRL (rw) */
    unsigned int ENL2:1;                    /**< \brief [2:2] Emergency Stop Enable for Bit 2 in SRL (rw) */
    unsigned int ENL3:1;                    /**< \brief [3:3] Emergency Stop Enable for Bit 3 in SRL (rw) */
    unsigned int ENL4:1;                    /**< \brief [4:4] Emergency Stop Enable for Bit 4 in SRL (rw) */
    unsigned int ENL5:1;                    /**< \brief [5:5] Emergency Stop Enable for Bit 5 in SRL (rw) */
    unsigned int ENL6:1;                    /**< \brief [6:6] Emergency Stop Enable for Bit 6 in SRL (rw) */
    unsigned int ENL7:1;                    /**< \brief [7:7] Emergency Stop Enable for Bit 7 in SRL (rw) */
    unsigned int ENL8:1;                    /**< \brief [8:8] Emergency Stop Enable for Bit 8 in SRL (rw) */
    unsigned int ENL9:1;                    /**< \brief [9:9] Emergency Stop Enable for Bit 9 in SRL (rw) */
    unsigned int ENL10:1;                   /**< \brief [10:10] Emergency Stop Enable for Bit 10 in SRL (rw) */
    unsigned int ENL11:1;                   /**< \brief [11:11] Emergency Stop Enable for Bit 11 in SRL (rw) */
    unsigned int ENL12:1;                   /**< \brief [12:12] Emergency Stop Enable for Bit 12 in SRL (rw) */
    unsigned int ENL13:1;                   /**< \brief [13:13] Emergency Stop Enable for Bit 13 in SRL (rw) */
    unsigned int ENL14:1;                   /**< \brief [14:14] Emergency Stop Enable for Bit 14 in SRL (rw) */
    unsigned int ENL15:1;                   /**< \brief [15:15] Emergency Stop Enable for Bit 15 in SRL (rw) */
    unsigned int ENH0:1;                    /**< \brief [16:16] Emergency Stop Enable for Bit 0 in SRH (rw) */
    unsigned int ENH1:1;                    /**< \brief [17:17] Emergency Stop Enable for Bit 1 in SRH (rw) */
    unsigned int ENH2:1;                    /**< \brief [18:18] Emergency Stop Enable for Bit 2 in SRH (rw) */
    unsigned int ENH3:1;                    /**< \brief [19:19] Emergency Stop Enable for Bit 3 in SRH (rw) */
    unsigned int ENH4:1;                    /**< \brief [20:20] Emergency Stop Enable for Bit 4 in SRH (rw) */
    unsigned int ENH5:1;                    /**< \brief [21:21] Emergency Stop Enable for Bit 5 in SRH (rw) */
    unsigned int ENH6:1;                    /**< \brief [22:22] Emergency Stop Enable for Bit 6 in SRH (rw) */
    unsigned int ENH7:1;                    /**< \brief [23:23] Emergency Stop Enable for Bit 7 in SRH (rw) */
    unsigned int ENH8:1;                    /**< \brief [24:24] Emergency Stop Enable for Bit 8 in SRH (rw) */
    unsigned int ENH9:1;                    /**< \brief [25:25] Emergency Stop Enable for Bit 9 in SRH (rw) */
    unsigned int ENH10:1;                   /**< \brief [26:26] Emergency Stop Enable for Bit 10 in SRH (rw) */
    unsigned int ENH11:1;                   /**< \brief [27:27] Emergency Stop Enable for Bit 11 in SRH (rw) */
    unsigned int ENH12:1;                   /**< \brief [28:28] Emergency Stop Enable for Bit 12 in SRH (rw) */
    unsigned int ENH13:1;                   /**< \brief [29:29] Emergency Stop Enable for Bit 13 in SRH (rw) */
    unsigned int ENH14:1;                   /**< \brief [30:30] Emergency Stop Enable for Bit 14 in SRH (rw) */
    unsigned int ENH15:1;                   /**< \brief [31:31] Emergency Stop Enable for Bit 15 in SRH (rw) */
} Ifx_MSC_ESR_Bits;

/** \brief  Emergency Stop Extension Register */
typedef struct _Ifx_MSC_ESRE_Bits
{
    unsigned int ENL16:1;                   /**< \brief [0:0] Emergency Stop Enable for Bit 16 in SRL (rw) */
    unsigned int ENL17:1;                   /**< \brief [1:1] Emergency Stop Enable for Bit 17 in SRL (rw) */
    unsigned int ENL18:1;                   /**< \brief [2:2] Emergency Stop Enable for Bit 18 in SRL (rw) */
    unsigned int ENL19:1;                   /**< \brief [3:3] Emergency Stop Enable for Bit 19 in SRL (rw) */
    unsigned int ENL20:1;                   /**< \brief [4:4] Emergency Stop Enable for Bit 20 in SRL (rw) */
    unsigned int ENL21:1;                   /**< \brief [5:5] Emergency Stop Enable for Bit 21 in SRL (rw) */
    unsigned int ENL22:1;                   /**< \brief [6:6] Emergency Stop Enable for Bit 22 in SRL (rw) */
    unsigned int ENL23:1;                   /**< \brief [7:7] Emergency Stop Enable for Bit 23 in SRL (rw) */
    unsigned int ENL24:1;                   /**< \brief [8:8] Emergency Stop Enable for Bit 24 in SRL (rw) */
    unsigned int ENL25:1;                   /**< \brief [9:9] Emergency Stop Enable for Bit 25 in SRL (rw) */
    unsigned int ENL26:1;                   /**< \brief [10:10] Emergency Stop Enable for Bit 26 in SRL (rw) */
    unsigned int ENL27:1;                   /**< \brief [11:11] Emergency Stop Enable for Bit 27 in SRL (rw) */
    unsigned int ENL28:1;                   /**< \brief [12:12] Emergency Stop Enable for Bit 28 in SRL (rw) */
    unsigned int ENL29:1;                   /**< \brief [13:13] Emergency Stop Enable for Bit 29 in SRL (rw) */
    unsigned int ENL30:1;                   /**< \brief [14:14] Emergency Stop Enable for Bit 30 in SRL (rw) */
    unsigned int ENL31:1;                   /**< \brief [15:15] Emergency Stop Enable for Bit 31 in SRL (rw) */
    unsigned int ENH16:1;                   /**< \brief [16:16] Emergency Stop Enable for Bit 16 in SRH (rw) */
    unsigned int ENH17:1;                   /**< \brief [17:17] Emergency Stop Enable for Bit 17 in SRH (rw) */
    unsigned int ENH18:1;                   /**< \brief [18:18] Emergency Stop Enable for Bit 18 in SRH (rw) */
    unsigned int ENH19:1;                   /**< \brief [19:19] Emergency Stop Enable for Bit 19 in SRH (rw) */
    unsigned int ENH20:1;                   /**< \brief [20:20] Emergency Stop Enable for Bit 20 in SRH (rw) */
    unsigned int ENH21:1;                   /**< \brief [21:21] Emergency Stop Enable for Bit 21 in SRH (rw) */
    unsigned int ENH22:1;                   /**< \brief [22:22] Emergency Stop Enable for Bit 22 in SRH (rw) */
    unsigned int ENH23:1;                   /**< \brief [23:23] Emergency Stop Enable for Bit 23 in SRH (rw) */
    unsigned int ENH24:1;                   /**< \brief [24:24] Emergency Stop Enable for Bit 24 in SRH (rw) */
    unsigned int ENH25:1;                   /**< \brief [25:25] Emergency Stop Enable for Bit 25 in SRH (rw) */
    unsigned int ENH26:1;                   /**< \brief [26:26] Emergency Stop Enable for Bit 26 in SRH (rw) */
    unsigned int ENH27:1;                   /**< \brief [27:27] Emergency Stop Enable for Bit 27 in SRH (rw) */
    unsigned int ENH28:1;                   /**< \brief [28:28] Emergency Stop Enable for Bit 28 in SRH (rw) */
    unsigned int ENH29:1;                   /**< \brief [29:29] Emergency Stop Enable for Bit 29 in SRH (rw) */
    unsigned int ENH30:1;                   /**< \brief [30:30] Emergency Stop Enable for Bit 30 in SRH (rw) */
    unsigned int ENH31:1;                   /**< \brief [31:31] Emergency Stop Enable for Bit 31 in SRH (rw) */
} Ifx_MSC_ESRE_Bits;

/** \brief  Fractional Divider Register */
typedef struct _Ifx_MSC_FDR_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int reserved_26:4;             /**< \brief \internal Reserved */
    unsigned int ENHW:1;                    /**< \brief [30:30] Enable Hardware Clock Control (rw) */
    unsigned int DISCLK:1;                  /**< \brief [31:31] Disable Clock (rwh) */
} Ifx_MSC_FDR_Bits;

/** \brief  Interrupt Control Register */
typedef struct _Ifx_MSC_ICR_Bits
{
    unsigned int EDIP:2;                    /**< \brief [1:0] Data Frame Interrupt Node Pointer (rw) */
    unsigned int EDIE:2;                    /**< \brief [3:2] Data Frame Interrupt Enable (rw) */
    unsigned int ECIP:2;                    /**< \brief [5:4] Command Frame Interrupt Node Pointer (rw) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int ECIE:1;                    /**< \brief [7:7] Command Frame Interrupt Enable (rw) */
    unsigned int TFIP:2;                    /**< \brief [9:8] Time Frame Interrupt Pointer (rw) */
    unsigned int reserved_10:1;             /**< \brief \internal Reserved */
    unsigned int TFIE:1;                    /**< \brief [11:11] Time Frame Interrupt Enable (rw) */
    unsigned int RDIP:2;                    /**< \brief [13:12] Receive Data Interrupt Pointer (rw) */
    unsigned int RDIE:2;                    /**< \brief [15:14] Receive Data Interrupt Enable (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_MSC_ICR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_MSC_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_MSC_ID_Bits;

/** \brief  Interrupt Set Clear Register */
typedef struct _Ifx_MSC_ISC_Bits
{
    unsigned int CDEDI:1;                   /**< \brief [0:0] Clear DEDI Flag (w) */
    unsigned int CDECI:1;                   /**< \brief [1:1] Clear DECI Flag (w) */
    unsigned int CDTFI:1;                   /**< \brief [2:2] Clear DTFI Flag (w) */
    unsigned int CURDI:1;                   /**< \brief [3:3] Clear URDI Flag (w) */
    unsigned int CDP:1;                     /**< \brief [4:4] Clear DP Flag (w) */
    unsigned int CCP:1;                     /**< \brief [5:5] Clear CP Flag (w) */
    unsigned int CDDIS:1;                   /**< \brief [6:6] Clear DSDIS Flag (w) */
    unsigned int reserved_7:9;              /**< \brief \internal Reserved */
    unsigned int SDEDI:1;                   /**< \brief [16:16] Set DEDI Flag (w) */
    unsigned int SDECI:1;                   /**< \brief [17:17] Set DECI Flag (w) */
    unsigned int SDTFI:1;                   /**< \brief [18:18] Set DTFI Flag (w) */
    unsigned int SURDI:1;                   /**< \brief [19:19] Set URDI Flag (w) */
    unsigned int SDP:1;                     /**< \brief [20:20] Set DP Bit (w) */
    unsigned int SCP:1;                     /**< \brief [21:21] Set CP Flag (w) */
    unsigned int SDDIS:1;                   /**< \brief [22:22] Set DSDIS Flag (w) */
    unsigned int reserved_23:9;             /**< \brief \internal Reserved */
} Ifx_MSC_ISC_Bits;

/** \brief  Interrupt Status Register */
typedef struct _Ifx_MSC_ISR_Bits
{
    unsigned int DEDI:1;                    /**< \brief [0:0] Data Frame Interrupt Flag (rh) */
    unsigned int DECI:1;                    /**< \brief [1:1] Command Frame Interrupt Flag (rh) */
    unsigned int DTFI:1;                    /**< \brief [2:2] Time Frame Interrupt Flag (rh) */
    unsigned int URDI:1;                    /**< \brief [3:3] Receive Data Interrupt Flag (rh) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_MSC_ISR_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_MSC_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_MSC_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_MSC_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_MSC_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_MSC_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_MSC_KRSTCLR_Bits;

/** \brief  Output Control Register */
typedef struct _Ifx_MSC_OCR_Bits
{
    unsigned int CLP:1;                     /**< \brief [0:0] FCLP Line Polarity (rw) */
    unsigned int SLP:1;                     /**< \brief [1:1] SOP Line Polarity (rw) */
    unsigned int CSLP:1;                    /**< \brief [2:2] Chip Selection Lines Polarity (rw) */
    unsigned int ILP:1;                     /**< \brief [3:3] SDI Line Polarity (rw) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int CLKCTRL:1;                 /**< \brief [8:8] Clock Control (rw) */
    unsigned int CSL:2;                     /**< \brief [10:9] Chip Enable Selection for ENL (rw) */
    unsigned int CSH:2;                     /**< \brief [12:11] Chip Enable Selection for ENH (rw) */
    unsigned int CSC:2;                     /**< \brief [14:13] Chip Enable Selection for ENC (rw) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int SDISEL:3;                  /**< \brief [18:16] Serial Data Input Selection (rw) */
    unsigned int reserved_19:13;            /**< \brief \internal Reserved */
} Ifx_MSC_OCR_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_MSC_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_MSC_OCS_Bits;

/** \brief  Upstream Data Register */
typedef struct _Ifx_MSC_UD_Bits
{
    unsigned int DATA:8;                    /**< \brief [7:0] Received Data (rh) */
    unsigned int reserved_8:8;              /**< \brief \internal Reserved */
    unsigned int V:1;                       /**< \brief [16:16] Valid Bit (rh) */
    unsigned int P:1;                       /**< \brief [17:17] Parity Bit (rh) */
    unsigned int C:1;                       /**< \brief [18:18] Clear Bit (w) */
    unsigned int LABF:2;                    /**< \brief [20:19] Lower Address Bit Field (rh) */
    unsigned int IPF:1;                     /**< \brief [21:21] Internal Parity Flag (rh) */
    unsigned int PERR:1;                    /**< \brief [22:22] Parity Error (rh) */
    unsigned int reserved_23:9;             /**< \brief \internal Reserved */
} Ifx_MSC_UD_Bits;

/** \brief  Upstream Control Enhanced Register 1 */
typedef struct _Ifx_MSC_USCE_Bits
{
    unsigned int USTOPRE:4;                 /**< \brief [3:0] Upstream Timeout Prescaler (rw) */
    unsigned int USTOVAL:4;                 /**< \brief [7:4] Upstream Timeout Value (rw) */
    unsigned int USTOEN:1;                  /**< \brief [8:8] Upstream Timeout Interrupt Enable (rw) */
    unsigned int USTF:1;                    /**< \brief [9:9] Upstream Timeout Flag (rh) */
    unsigned int USTC:1;                    /**< \brief [10:10] Upstream Timout Clear (w) */
    unsigned int USTS:1;                    /**< \brief [11:11] Upstream Timout Set (w) */
    unsigned int reserved_12:1;             /**< \brief \internal Reserved */
    unsigned int UTASR:1;                   /**< \brief [13:13] Upstream Timout Alternate Service Request (rw) */
    unsigned int USTOIP:2;                  /**< \brief [15:14] Upstream Timout Interrupt Node Pointer (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_MSC_USCE_Bits;

/** \brief  Upstream Status Register */
typedef struct _Ifx_MSC_USR_Bits
{
    unsigned int UFT:1;                     /**< \brief [0:0] Upstream Channel Frame Type (rw) */
    unsigned int URR:3;                     /**< \brief [3:1] Upstream Channel Receiving Rate (rw) */
    unsigned int PCTR:1;                    /**< \brief [4:4] Parity Control (rw) */
    unsigned int SRDC:1;                    /**< \brief [5:5] Service Request Delay Control (rw) */
    unsigned int reserved_6:10;             /**< \brief \internal Reserved */
    unsigned int UC:5;                      /**< \brief [20:16] Upstream Counter (rh) */
    unsigned int reserved_21:11;            /**< \brief \internal Reserved */
} Ifx_MSC_USR_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Msc_union
 * \{  */

/** \brief  Asynchronous Block Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ABC_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_ABC;

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_MSC_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_MSC_ACCEN1;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_CLC;

/** \brief  Downstream Command Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DC_Bits B;                      /**< \brief Bitfield access */
} Ifx_MSC_DC;

/** \brief  Downstream Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DD_Bits B;                      /**< \brief Bitfield access */
} Ifx_MSC_DD;

/** \brief  Downstream Data Extension Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DDE_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_DDE;

/** \brief  Downstream Data Mirror Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DDM_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_DDM;

/** \brief  Downstream Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSC_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_DSC;

/** \brief  Downstream Control Enhanced Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSCE_Bits B;                    /**< \brief Bitfield access */
} Ifx_MSC_DSCE;

/** \brief  Downstream Select Data Source High Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSDSH_Bits B;                   /**< \brief Bitfield access */
} Ifx_MSC_DSDSH;

/** \brief  Downstream Select Data Source High Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSDSHE_Bits B;                  /**< \brief Bitfield access */
} Ifx_MSC_DSDSHE;

/** \brief  Downstream Select Data Source Low Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSDSL_Bits B;                   /**< \brief Bitfield access */
} Ifx_MSC_DSDSL;

/** \brief  Downstream Select Data Source Low Extension Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSDSLE_Bits B;                  /**< \brief Bitfield access */
} Ifx_MSC_DSDSLE;

/** \brief  Downstream Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSS_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_DSS;

/** \brief  Downstream Timing Extension Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_DSTE_Bits B;                    /**< \brief Bitfield access */
} Ifx_MSC_DSTE;

/** \brief  Emergency Stop Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ESR_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_ESR;

/** \brief  Emergency Stop Extension Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ESRE_Bits B;                    /**< \brief Bitfield access */
} Ifx_MSC_ESRE;

/** \brief  Fractional Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_FDR_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_FDR;

/** \brief  Interrupt Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ICR_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_ICR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_MSC_ID;

/** \brief  Interrupt Set Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ISC_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_ISC;

/** \brief  Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_ISR_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_ISR;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_MSC_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_MSC_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_MSC_KRSTCLR;

/** \brief  Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_OCR_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_OCR;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_OCS_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_OCS;

/** \brief  Upstream Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_UD_Bits B;                      /**< \brief Bitfield access */
} Ifx_MSC_UD;

/** \brief  Upstream Control Enhanced Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_USCE_Bits B;                    /**< \brief Bitfield access */
} Ifx_MSC_USCE;

/** \brief  Upstream Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MSC_USR_Bits B;                     /**< \brief Bitfield access */
} Ifx_MSC_USR;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Msc_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  MSC object */
typedef volatile struct _Ifx_MSC
{
    Ifx_MSC_CLC CLC;                        /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_MSC_ID ID;                          /**< \brief 8, Module Identification Register */
    Ifx_MSC_FDR FDR;                        /**< \brief C, Fractional Divider Register */
    Ifx_MSC_USR USR;                        /**< \brief 10, Upstream Status Register */
    Ifx_MSC_DSC DSC;                        /**< \brief 14, Downstream Control Register */
    Ifx_MSC_DSS DSS;                        /**< \brief 18, Downstream Status Register */
    Ifx_MSC_DD DD;                          /**< \brief 1C, Downstream Data Register */
    Ifx_MSC_DC DC;                          /**< \brief 20, Downstream Command Register */
    Ifx_MSC_DSDSL DSDSL;                    /**< \brief 24, Downstream Select Data Source Low Register */
    Ifx_MSC_DSDSH DSDSH;                    /**< \brief 28, Downstream Select Data Source High Register */
    Ifx_MSC_ESR ESR;                        /**< \brief 2C, Emergency Stop Register */
    Ifx_MSC_UD UD[4];                       /**< \brief 30, Upstream Data Register */
    Ifx_MSC_ICR ICR;                        /**< \brief 40, Interrupt Control Register */
    Ifx_MSC_ISR ISR;                        /**< \brief 44, Interrupt Status Register */
    Ifx_MSC_ISC ISC;                        /**< \brief 48, Interrupt Set Clear Register */
    Ifx_MSC_OCR OCR;                        /**< \brief 4C, Output Control Register */
    unsigned char reserved_50[8];           /**< \brief 50, \internal Reserved */
    Ifx_MSC_DSCE DSCE;                      /**< \brief 58, Downstream Control Enhanced Register 1 */
    Ifx_MSC_USCE USCE;                      /**< \brief 5C, Upstream Control Enhanced Register 1 */
    Ifx_MSC_DSDSLE DSDSLE;                  /**< \brief 60, Downstream Select Data Source Low Extension Register */
    Ifx_MSC_DSDSHE DSDSHE;                  /**< \brief 64, Downstream Select Data Source High Register */
    Ifx_MSC_ESRE ESRE;                      /**< \brief 68, Emergency Stop Extension Register */
    Ifx_MSC_DDE DDE;                        /**< \brief 6C, Downstream Data Extension Register */
    Ifx_MSC_DDM DDM;                        /**< \brief 70, Downstream Data Mirror Register */
    Ifx_MSC_DSTE DSTE;                      /**< \brief 74, Downstream Timing Extension Register */
    unsigned char reserved_78[8];           /**< \brief 78, \internal Reserved */
    Ifx_MSC_ABC ABC;                        /**< \brief 80, Asynchronous Block Configuration Register */
    unsigned char reserved_84[100];         /**< \brief 84, \internal Reserved */
    Ifx_MSC_OCS OCS;                        /**< \brief E8, OCDS Control and Status */
    Ifx_MSC_KRSTCLR KRSTCLR;                /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_MSC_KRST1 KRST1;                    /**< \brief F0, Kernel Reset Register 1 */
    Ifx_MSC_KRST0 KRST0;                    /**< \brief F4, Kernel Reset Register 0 */
    Ifx_MSC_ACCEN1 ACCEN1;                  /**< \brief F8, Access Enable Register 1 */
    Ifx_MSC_ACCEN0 ACCEN0;                  /**< \brief FC, Access Enable Register 0 */
} Ifx_MSC;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXMSC_REGDEF_H */
