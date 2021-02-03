/**
 * \file IfxCpu_regdef.h
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
 * \defgroup IfxLld_Cpu Cpu
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Cpu_Bitfields Bitfields
 * \ingroup IfxLld_Cpu
 * 
 * \defgroup IfxLld_Cpu_union Union
 * \ingroup IfxLld_Cpu
 * 
 * \defgroup IfxLld_Cpu_struct Struct
 * \ingroup IfxLld_Cpu
 * 
 */
#ifndef IFXCPU_REGDEF_H
#define IFXCPU_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Bitfields
 * \{  */

/** \brief  Address General Purpose Register */
typedef struct _Ifx_CPU_A_Bits
{
    Ifx_Strict_32Bit ADDR:32;               /**< \brief [31:0] Address Register (rw) */
} Ifx_CPU_A_Bits;

/** \brief  Base Interrupt Vector Table Pointer */
typedef struct _Ifx_CPU_BIV_Bits
{
    Ifx_Strict_32Bit VSS:1;                 /**< \brief [0:0] Vector Spacing Select (rw) */
    Ifx_Strict_32Bit BIV:31;                /**< \brief [31:1] Base Address of Interrupt Vector Table (rw) */
} Ifx_CPU_BIV_Bits;

/** \brief  Base Trap Vector Table Pointer */
typedef struct _Ifx_CPU_BTV_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BTV:31;                /**< \brief [31:1] Base Address of Trap Vector Table (rw) */
} Ifx_CPU_BTV_Bits;

/** \brief  CPU Clock Cycle Count */
typedef struct _Ifx_CPU_CCNT_Bits
{
    Ifx_Strict_32Bit CountValue:31;         /**< \brief [30:0] Count Value (rw) */
    Ifx_Strict_32Bit SOvf:1;                /**< \brief [31:31] Sticky Overflow Bit (rw) */
} Ifx_CPU_CCNT_Bits;

/** \brief  Counter Control */
typedef struct _Ifx_CPU_CCTRL_Bits
{
    Ifx_Strict_32Bit CM:1;                  /**< \brief [0:0] Counter Mode (rw) */
    Ifx_Strict_32Bit CE:1;                  /**< \brief [1:1] Count Enable (rw) */
    Ifx_Strict_32Bit M1:3;                  /**< \brief [4:2] M1CNT Configuration (rw) */
    Ifx_Strict_32Bit M2:3;                  /**< \brief [7:5] M2CNT Configuration (rw) */
    Ifx_Strict_32Bit M3:3;                  /**< \brief [10:8] M3CNT Configuration (rw) */
    Ifx_Strict_32Bit reserved_11:21;        /**< \brief \internal Reserved */
} Ifx_CPU_CCTRL_Bits;

/** \brief  Compatibility Control Register */
typedef struct _Ifx_CPU_COMPAT_Bits
{
    Ifx_Strict_32Bit reserved_0:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RM:1;                  /**< \brief [3:3] Rounding Mode Compatibility (rw) */
    Ifx_Strict_32Bit SP:1;                  /**< \brief [4:4] SYSCON Safety Protection Mode Compatibility (rw) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_CPU_COMPAT_Bits;

/** \brief  CPU Core Identification Register */
typedef struct _Ifx_CPU_CORE_ID_Bits
{
    Ifx_Strict_32Bit CORE_ID:3;             /**< \brief [2:0] Core Identification Number (rw) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_CPU_CORE_ID_Bits;

/** \brief  CPU Code Protection Range Lower Bound Register */
typedef struct _Ifx_CPU_CPR_L_Bits
{
    Ifx_Strict_32Bit reserved_0:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit LOWBND:29;             /**< \brief [31:3] CPRy Lower Boundary Address (rw) */
} Ifx_CPU_CPR_L_Bits;

/** \brief  CPU Code Protection Range Upper Bound Register */
typedef struct _Ifx_CPU_CPR_U_Bits
{
    Ifx_Strict_32Bit reserved_0:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit UPPBND:29;             /**< \brief [31:3] CPR0_m Upper Boundary Address (rw) */
} Ifx_CPU_CPR_U_Bits;

/** \brief  CPU Identification Register TC1.6P */
typedef struct _Ifx_CPU_CPU_ID_Bits
{
    Ifx_Strict_32Bit MODREV:8;              /**< \brief [7:0] Revision Number (r) */
    Ifx_Strict_32Bit MOD_32B:8;             /**< \brief [15:8] 32-Bit Module Enable (r) */
    Ifx_Strict_32Bit MOD:16;                /**< \brief [31:16] Module Identification Number (r) */
} Ifx_CPU_CPU_ID_Bits;

/** \brief  CPU Code Protection Execute Enable Register Set */
typedef struct _Ifx_CPU_CPXE_Bits
{
    Ifx_Strict_32Bit XE:8;                  /**< \brief [7:0] Execute Enable Range select (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_CPU_CPXE_Bits;

/** \brief  Core Register Access Event */
typedef struct _Ifx_CPU_CREVT_Bits
{
    Ifx_Strict_32Bit EVTA:3;                /**< \brief [2:0] Event Associated (rw) */
    Ifx_Strict_32Bit BBM:1;                 /**< \brief [3:3] Break Before Make (BBM) or Break After Make (BAM) Selection (rw) */
    Ifx_Strict_32Bit BOD:1;                 /**< \brief [4:4] Breakout Disable (rw) */
    Ifx_Strict_32Bit SUSP:1;                /**< \brief [5:5] CDC Suspend-Out Signal State (rw) */
    Ifx_Strict_32Bit CNT:2;                 /**< \brief [7:6] Counter (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_CPU_CREVT_Bits;

/** \brief  CPU Customer ID register */
typedef struct _Ifx_CPU_CUS_ID_Bits
{
    Ifx_Strict_32Bit CID:3;                 /**< \brief [2:0] Customer ID (r) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_CPU_CUS_ID_Bits;

/** \brief  Data General Purpose Register */
typedef struct _Ifx_CPU_D_Bits
{
    Ifx_Strict_32Bit DATA:32;               /**< \brief [31:0] Data Register (rw) */
} Ifx_CPU_D_Bits;

/** \brief  Data Asynchronous Trap Register */
typedef struct _Ifx_CPU_DATR_Bits
{
    Ifx_Strict_32Bit reserved_0:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SBE:1;                 /**< \brief [3:3] Store Bus Error (rwh) */
    Ifx_Strict_32Bit reserved_4:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CWE:1;                 /**< \brief [9:9] Cache Writeback Error (rwh) */
    Ifx_Strict_32Bit CFE:1;                 /**< \brief [10:10] Cache Flush Error (rwh) */
    Ifx_Strict_32Bit reserved_11:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SOE:1;                 /**< \brief [14:14] Store Overlay Error (rwh) */
    Ifx_Strict_32Bit SME:1;                 /**< \brief [15:15] Store MIST Error (rwh) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_CPU_DATR_Bits;

/** \brief  Debug Status Register */
typedef struct _Ifx_CPU_DBGSR_Bits
{
    Ifx_Strict_32Bit DE:1;                  /**< \brief [0:0] Debug Enable (rh) */
    Ifx_Strict_32Bit HALT:2;                /**< \brief [2:1] CPU Halt Request / Status Field (rwh) */
    Ifx_Strict_32Bit SIH:1;                 /**< \brief [3:3] Suspend-in Halt (rh) */
    Ifx_Strict_32Bit SUSP:1;                /**< \brief [4:4] Current State of the Core Suspend-Out Signal (rwh) */
    Ifx_Strict_32Bit reserved_5:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PREVSUSP:1;            /**< \brief [6:6] Previous State of Core Suspend-Out Signal (rh) */
    Ifx_Strict_32Bit PEVT:1;                /**< \brief [7:7] Posted Event (rwh) */
    Ifx_Strict_32Bit EVTSRC:5;              /**< \brief [12:8] Event Source (rh) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_CPU_DBGSR_Bits;

/** \brief  Debug Trap Control Register */
typedef struct _Ifx_CPU_DBGTCR_Bits
{
    Ifx_Strict_32Bit DTA:1;                 /**< \brief [0:0] Debug Trap Active Bit (rwh) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_CPU_DBGTCR_Bits;

/** \brief  Data Memory Control Register */
typedef struct _Ifx_CPU_DCON0_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DCBYP:1;               /**< \brief [1:1] Data Cache Bypass (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_CPU_DCON0_Bits;

/** \brief  Data Control Register 2 */
typedef struct _Ifx_CPU_DCON2_Bits
{
    Ifx_Strict_32Bit DCACHE_SZE:16;         /**< \brief [15:0] Data Cache Size (r) */
    Ifx_Strict_32Bit DSCRATCH_SZE:16;       /**< \brief [31:16] Data Scratch Size (r) */
} Ifx_CPU_DCON2_Bits;

/** \brief  CPU Debug Context Save Area Pointer */
typedef struct _Ifx_CPU_DCX_Bits
{
    Ifx_Strict_32Bit reserved_0:6;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DCXValue:26;           /**< \brief [31:6] Debug Context Save Area Pointer (rw) */
} Ifx_CPU_DCX_Bits;

/** \brief  Data Error Address Register */
typedef struct _Ifx_CPU_DEADD_Bits
{
    Ifx_Strict_32Bit ERROR_ADDRESS:32;      /**< \brief [31:0] Error Address (rh) */
} Ifx_CPU_DEADD_Bits;

/** \brief  Data Integrity Error Address Register */
typedef struct _Ifx_CPU_DIEAR_Bits
{
    Ifx_Strict_32Bit TA:32;                 /**< \brief [31:0] Transaction Address (rh) */
} Ifx_CPU_DIEAR_Bits;

/** \brief  Data Integrity Error Trap Register */
typedef struct _Ifx_CPU_DIETR_Bits
{
    Ifx_Strict_32Bit IED:1;                 /**< \brief [0:0] Integrity Error Detected (rwh) */
    Ifx_Strict_32Bit IE_T:1;                /**< \brief [1:1] Integrity Error - Tag Memory (rh) */
    Ifx_Strict_32Bit IE_C:1;                /**< \brief [2:2] Integrity Error - Cache Memory (rh) */
    Ifx_Strict_32Bit IE_S:1;                /**< \brief [3:3] Integrity Error - Scratchpad Memory (rh) */
    Ifx_Strict_32Bit IE_BI:1;               /**< \brief [4:4] Integrity Error - Bus Integrity (rh) */
    Ifx_Strict_32Bit E_INFO:6;              /**< \brief [10:5] Error Information (rh) */
    Ifx_Strict_32Bit IE_DUAL:1;             /**< \brief [11:11] Dual Bit Error Detected (rh) */
    Ifx_Strict_32Bit IE_SP:1;               /**< \brief [12:12] Safety Protection Error Detected (rh) */
    Ifx_Strict_32Bit IE_BS:1;               /**< \brief [13:13] Bus Slave Access Indicator (rh) */
    Ifx_Strict_32Bit reserved_14:18;        /**< \brief \internal Reserved */
} Ifx_CPU_DIETR_Bits;

/** \brief  CPU Debug Monitor Start Address */
typedef struct _Ifx_CPU_DMS_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DMSValue:31;           /**< \brief [31:1] Debug Monitor Start Address (rw) */
} Ifx_CPU_DMS_Bits;

/** \brief  CPU Data Protection Range, Lower Bound Register */
typedef struct _Ifx_CPU_DPR_L_Bits
{
    Ifx_Strict_32Bit reserved_0:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit LOWBND:29;             /**< \brief [31:3] DPRy Lower Boundary Address (rw) */
} Ifx_CPU_DPR_L_Bits;

/** \brief  CPU Data Protection Range, Upper Bound Register */
typedef struct _Ifx_CPU_DPR_U_Bits
{
    Ifx_Strict_32Bit reserved_0:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit UPPBND:29;             /**< \brief [31:3] DPRy Upper Boundary Address (rw) */
} Ifx_CPU_DPR_U_Bits;

/** \brief  CPU Data Protection Read Enable Register Set */
typedef struct _Ifx_CPU_DPRE_Bits
{
    Ifx_Strict_32Bit RE:16;                 /**< \brief [15:0] Read Enable Range Select (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_CPU_DPRE_Bits;

/** \brief  CPU Data Protection Write Enable Register Set */
typedef struct _Ifx_CPU_DPWE_Bits
{
    Ifx_Strict_32Bit WE:16;                 /**< \brief [15:0] Write Enable Range Select (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_CPU_DPWE_Bits;

/** \brief  Data Synchronous Trap Register */
typedef struct _Ifx_CPU_DSTR_Bits
{
    Ifx_Strict_32Bit SRE:1;                 /**< \brief [0:0] Scratch Range Error (rwh) */
    Ifx_Strict_32Bit GAE:1;                 /**< \brief [1:1] Global Address Error (rwh) */
    Ifx_Strict_32Bit LBE:1;                 /**< \brief [2:2] Load Bus Error (rwh) */
    Ifx_Strict_32Bit reserved_3:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CRE:1;                 /**< \brief [6:6] Cache Refill Error (rwh) */
    Ifx_Strict_32Bit reserved_7:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DTME:1;                /**< \brief [14:14] DTAG MSIST Error (rwh) */
    Ifx_Strict_32Bit LOE:1;                 /**< \brief [15:15] Load Overlay Error (rwh) */
    Ifx_Strict_32Bit SDE:1;                 /**< \brief [16:16] Segment Difference Error (rwh) */
    Ifx_Strict_32Bit SCE:1;                 /**< \brief [17:17] Segment Crossing Error (rwh) */
    Ifx_Strict_32Bit CAC:1;                 /**< \brief [18:18] CSFR Access Error (rwh) */
    Ifx_Strict_32Bit MPE:1;                 /**< \brief [19:19] Memory Protection Error (rwh) */
    Ifx_Strict_32Bit CLE:1;                 /**< \brief [20:20] Context Location Error (rwh) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ALN:1;                 /**< \brief [24:24] Alignment Error (rwh) */
    Ifx_Strict_32Bit reserved_25:7;         /**< \brief \internal Reserved */
} Ifx_CPU_DSTR_Bits;

/** \brief  External Event Register */
typedef struct _Ifx_CPU_EXEVT_Bits
{
    Ifx_Strict_32Bit EVTA:3;                /**< \brief [2:0] Event Associated (rw) */
    Ifx_Strict_32Bit BBM:1;                 /**< \brief [3:3] Break Before Make (BBM) or Break After Make (BAM) Selection (rw) */
    Ifx_Strict_32Bit BOD:1;                 /**< \brief [4:4] Breakout Disable (rw) */
    Ifx_Strict_32Bit SUSP:1;                /**< \brief [5:5] CDC Suspend-Out Signal State (rw) */
    Ifx_Strict_32Bit CNT:2;                 /**< \brief [7:6] Counter (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_CPU_EXEVT_Bits;

/** \brief  Free CSA List Head Pointer */
typedef struct _Ifx_CPU_FCX_Bits
{
    Ifx_Strict_32Bit FCXO:16;               /**< \brief [15:0] FCX Offset Address Field (rw) */
    Ifx_Strict_32Bit FCXS:4;                /**< \brief [19:16] FCX Segment Address Field (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_CPU_FCX_Bits;

/** \brief  CPU Trap Control Register */
typedef struct _Ifx_CPU_FPU_TRAP_CON_Bits
{
    Ifx_Strict_32Bit TST:1;                 /**< \brief [0:0] Trap Status (rh) */
    Ifx_Strict_32Bit TCL:1;                 /**< \brief [1:1] Trap Clear (w) */
    Ifx_Strict_32Bit reserved_2:6;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RM:2;                  /**< \brief [9:8] Captured Rounding Mode (rh) */
    Ifx_Strict_32Bit reserved_10:8;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit FXE:1;                 /**< \brief [18:18] FX Trap Enable (rw) */
    Ifx_Strict_32Bit FUE:1;                 /**< \brief [19:19] FU Trap Enable (rw) */
    Ifx_Strict_32Bit FZE:1;                 /**< \brief [20:20] FZ Trap Enable (rw) */
    Ifx_Strict_32Bit FVE:1;                 /**< \brief [21:21] FV Trap Enable (rw) */
    Ifx_Strict_32Bit FIE:1;                 /**< \brief [22:22] FI Trap Enable (rw) */
    Ifx_Strict_32Bit reserved_23:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit FX:1;                  /**< \brief [26:26] Captured FX (rh) */
    Ifx_Strict_32Bit FU:1;                  /**< \brief [27:27] Captured FU (rh) */
    Ifx_Strict_32Bit FZ:1;                  /**< \brief [28:28] Captured FZ (rh) */
    Ifx_Strict_32Bit FV:1;                  /**< \brief [29:29] Captured FV (rh) */
    Ifx_Strict_32Bit FI:1;                  /**< \brief [30:30] Captured FI (rh) */
    Ifx_Strict_32Bit reserved_31:1;         /**< \brief \internal Reserved */
} Ifx_CPU_FPU_TRAP_CON_Bits;

/** \brief  CPU Trapping Instruction Opcode Register */
typedef struct _Ifx_CPU_FPU_TRAP_OPC_Bits
{
    Ifx_Strict_32Bit OPC:8;                 /**< \brief [7:0] Captured Opcode (rh) */
    Ifx_Strict_32Bit FMT:1;                 /**< \brief [8:8] Captured Instruction Format (rh) */
    Ifx_Strict_32Bit reserved_9:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DREG:4;                /**< \brief [19:16] Captured Destination Register (rh) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_CPU_FPU_TRAP_OPC_Bits;

/** \brief  CPU Trapping Instruction Program Counter Register */
typedef struct _Ifx_CPU_FPU_TRAP_PC_Bits
{
    Ifx_Strict_32Bit PC:32;                 /**< \brief [31:0] Captured Program Counter (rh) */
} Ifx_CPU_FPU_TRAP_PC_Bits;

/** \brief  CPU Trapping Instruction Operand Register */
typedef struct _Ifx_CPU_FPU_TRAP_SRC1_Bits
{
    Ifx_Strict_32Bit SRC1:32;               /**< \brief [31:0] Captured SRC1 Operand (rh) */
} Ifx_CPU_FPU_TRAP_SRC1_Bits;

/** \brief  CPU Trapping Instruction Operand Register */
typedef struct _Ifx_CPU_FPU_TRAP_SRC2_Bits
{
    Ifx_Strict_32Bit SRC2:32;               /**< \brief [31:0] Captured SRC2 Operand (rh) */
} Ifx_CPU_FPU_TRAP_SRC2_Bits;

/** \brief  Trapping Instruction Operand Register */
typedef struct _Ifx_CPU_FPU_TRAP_SRC3_Bits
{
    Ifx_Strict_32Bit SRC3:32;               /**< \brief [31:0] Captured SRC3 Operand (rh) */
} Ifx_CPU_FPU_TRAP_SRC3_Bits;

/** \brief  Instruction Count */
typedef struct _Ifx_CPU_ICNT_Bits
{
    Ifx_Strict_32Bit CountValue:31;         /**< \brief [30:0] Count Value (rw) */
    Ifx_Strict_32Bit SOvf:1;                /**< \brief [31:31] Sticky Overflow Bit (rw) */
} Ifx_CPU_ICNT_Bits;

/** \brief  Interrupt Control Register */
typedef struct _Ifx_CPU_ICR_Bits
{
    Ifx_Strict_32Bit CCPN:10;               /**< \brief [9:0] Current CPU Priority Number (rwh) */
    Ifx_Strict_32Bit reserved_10:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit IE:1;                  /**< \brief [15:15] Global Interrupt Enable Bit (rwh) */
    Ifx_Strict_32Bit PIPN:10;               /**< \brief [25:16] Pending Interrupt Priority Number (rh) */
    Ifx_Strict_32Bit reserved_26:6;         /**< \brief \internal Reserved */
} Ifx_CPU_ICR_Bits;

/** \brief  Interrupt Stack Pointer */
typedef struct _Ifx_CPU_ISP_Bits
{
    Ifx_Strict_32Bit ISP:32;                /**< \brief [31:0] Interrupt Stack Pointer (rw) */
} Ifx_CPU_ISP_Bits;

/** \brief  Free CSA List Limit Pointer */
typedef struct _Ifx_CPU_LCX_Bits
{
    Ifx_Strict_32Bit LCXO:16;               /**< \brief [15:0] LCX Offset Field (rw) */
    Ifx_Strict_32Bit LCXS:4;                /**< \brief [19:16] LCX Segment Address (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_CPU_LCX_Bits;

/** \brief  Multi-Count Register 1 */
typedef struct _Ifx_CPU_M1CNT_Bits
{
    Ifx_Strict_32Bit CountValue:31;         /**< \brief [30:0] Count Value (rw) */
    Ifx_Strict_32Bit SOvf:1;                /**< \brief [31:31] Sticky Overflow Bit (rw) */
} Ifx_CPU_M1CNT_Bits;

/** \brief  Multi-Count Register 2 */
typedef struct _Ifx_CPU_M2CNT_Bits
{
    Ifx_Strict_32Bit CountValue:31;         /**< \brief [30:0] Count Value (rw) */
    Ifx_Strict_32Bit SOvf:1;                /**< \brief [31:31] Sticky Overflow Bit (rw) */
} Ifx_CPU_M2CNT_Bits;

/** \brief  Multi-Count Register 3 */
typedef struct _Ifx_CPU_M3CNT_Bits
{
    Ifx_Strict_32Bit CountValue:31;         /**< \brief [30:0] Count Value (rw) */
    Ifx_Strict_32Bit SOvf:1;                /**< \brief [31:31] Sticky Overflow Bit (rw) */
} Ifx_CPU_M3CNT_Bits;

/** \brief  Program Counter */
typedef struct _Ifx_CPU_PC_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PC:31;                 /**< \brief [31:1] Program Counter (r) */
} Ifx_CPU_PC_Bits;

/** \brief  Program Control 0 */
typedef struct _Ifx_CPU_PCON0_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PCBYP:1;               /**< \brief [1:1] Program Cache Bypass (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_CPU_PCON0_Bits;

/** \brief  Program Control 1 */
typedef struct _Ifx_CPU_PCON1_Bits
{
    Ifx_Strict_32Bit PCINV:1;               /**< \brief [0:0] Program Cache Invalidate (rw) */
    Ifx_Strict_32Bit PBINV:1;               /**< \brief [1:1] Program Buffer Invalidate (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_CPU_PCON1_Bits;

/** \brief  Program Control 2 */
typedef struct _Ifx_CPU_PCON2_Bits
{
    Ifx_Strict_32Bit PCACHE_SZE:16;         /**< \brief [15:0] Program Cache Size (ICACHE) in KBytes (r) */
    Ifx_Strict_32Bit PSCRATCH_SZE:16;       /**< \brief [31:16] Program Scratch Size in KBytes (r) */
} Ifx_CPU_PCON2_Bits;

/** \brief  Previous Context Information Register */
typedef struct _Ifx_CPU_PCXI_Bits
{
    Ifx_Strict_32Bit PCXO:16;               /**< \brief [15:0] Previous Context Pointer Offset Field (rw) */
    Ifx_Strict_32Bit PCXS:4;                /**< \brief [19:16] Previous Context Pointer Segment Address (rw) */
    Ifx_Strict_32Bit UL:1;                  /**< \brief [20:20] Upper or Lower Context Tag (rw) */
    Ifx_Strict_32Bit PIE:1;                 /**< \brief [21:21] Previous Interrupt Enable (rw) */
    Ifx_Strict_32Bit PCPN:10;               /**< \brief [31:22] Previous CPU Priority Number (rw) */
} Ifx_CPU_PCXI_Bits;

/** \brief  Program Integrity Error Address Register */
typedef struct _Ifx_CPU_PIEAR_Bits
{
    Ifx_Strict_32Bit TA:32;                 /**< \brief [31:0] Transaction Address (rh) */
} Ifx_CPU_PIEAR_Bits;

/** \brief  Program Integrity Error Trap Register */
typedef struct _Ifx_CPU_PIETR_Bits
{
    Ifx_Strict_32Bit IED:1;                 /**< \brief [0:0] Integrity Error Detected (rwh) */
    Ifx_Strict_32Bit IE_T:1;                /**< \brief [1:1] Integrity Error - Tag Memory (rh) */
    Ifx_Strict_32Bit IE_C:1;                /**< \brief [2:2] Integrity Error - Cache Memory (rh) */
    Ifx_Strict_32Bit IE_S:1;                /**< \brief [3:3] Integrity Error - Scratchpad Memory (rh) */
    Ifx_Strict_32Bit IE_BI:1;               /**< \brief [4:4] Integrity Error - Bus Interface (rh) */
    Ifx_Strict_32Bit E_INFO:6;              /**< \brief [10:5] Error Information (rh) */
    Ifx_Strict_32Bit IE_DUAL:1;             /**< \brief [11:11] Integrity Error - Dual Error Detected (r) */
    Ifx_Strict_32Bit IE_SP:1;               /**< \brief [12:12] Safety Protection Error Detected (rh) */
    Ifx_Strict_32Bit IE_BS:1;               /**< \brief [13:13] Bus Slave Access Indicator (rh) */
    Ifx_Strict_32Bit reserved_14:18;        /**< \brief \internal Reserved */
} Ifx_CPU_PIETR_Bits;

/** \brief  Data Access CacheabilityRegister */
typedef struct _Ifx_CPU_PMA0_Bits
{
    Ifx_Strict_32Bit reserved_0:13;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DAC:3;                 /**< \brief [15:13] Data Access Cacheability Segments FH,EH,DH (r) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_CPU_PMA0_Bits;

/** \brief  Code Access CacheabilityRegister */
typedef struct _Ifx_CPU_PMA1_Bits
{
    Ifx_Strict_32Bit reserved_0:14;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CAC:2;                 /**< \brief [15:14] Code Access Cacheability Segments FH,EH (r) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_CPU_PMA1_Bits;

/** \brief  Peripheral Space Identifier register */
typedef struct _Ifx_CPU_PMA2_Bits
{
    Ifx_Strict_32Bit PSI:16;                /**< \brief [15:0] Peripheral Space Identifier Segments FH-0H (r) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_CPU_PMA2_Bits;

/** \brief  Program Synchronous Trap Register */
typedef struct _Ifx_CPU_PSTR_Bits
{
    Ifx_Strict_32Bit FRE:1;                 /**< \brief [0:0] Fetch Range Error (rwh) */
    Ifx_Strict_32Bit reserved_1:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit FBE:1;                 /**< \brief [2:2] Fetch Bus Error (rwh) */
    Ifx_Strict_32Bit reserved_3:9;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit FPE:1;                 /**< \brief [12:12] Fetch Peripheral Error (rwh) */
    Ifx_Strict_32Bit reserved_13:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit FME:1;                 /**< \brief [14:14] Fetch MSIST Error (rwh) */
    Ifx_Strict_32Bit reserved_15:17;        /**< \brief \internal Reserved */
} Ifx_CPU_PSTR_Bits;

/** \brief  Program Status Word */
typedef struct _Ifx_CPU_PSW_Bits
{
    Ifx_Strict_32Bit CDC:7;                 /**< \brief [6:0] Call Depth Counter (rwh) */
    Ifx_Strict_32Bit CDE:1;                 /**< \brief [7:7] Call Depth Count Enable (rwh) */
    Ifx_Strict_32Bit GW:1;                  /**< \brief [8:8] Global Address Register Write Permission (rwh) */
    Ifx_Strict_32Bit IS:1;                  /**< \brief [9:9] Interrupt Stack Control (rwh) */
    Ifx_Strict_32Bit IO:2;                  /**< \brief [11:10] Access Privilege Level Control (I/O Privilege) (rwh) */
    Ifx_Strict_32Bit PRS:2;                 /**< \brief [13:12] Protection Register Set (rwh) */
    Ifx_Strict_32Bit S:1;                   /**< \brief [14:14] Safe Task Identifier (rwh) */
    Ifx_Strict_32Bit reserved_15:12;        /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SAV:1;                 /**< \brief [27:27] Sticky Advance Overflow Flag (rwh) */
    Ifx_Strict_32Bit AV:1;                  /**< \brief [28:28] Advance Overflow Flag (rwh) */
    Ifx_Strict_32Bit SV:1;                  /**< \brief [29:29] Sticky Overflow Flag (rwh) */
    Ifx_Strict_32Bit V:1;                   /**< \brief [30:30] Overflow Flag (rwh) */
    Ifx_Strict_32Bit C:1;                   /**< \brief [31:31] Carry Flag (rwh) */
} Ifx_CPU_PSW_Bits;

/** \brief  SRI Error Generation Register */
typedef struct _Ifx_CPU_SEGEN_Bits
{
    Ifx_Strict_32Bit ADFLIP:8;              /**< \brief [7:0] Address ECC Bit Flip (rw) */
    Ifx_Strict_32Bit ADTYPE:2;              /**< \brief [9:8] Type of error (rw) */
    Ifx_Strict_32Bit reserved_10:21;        /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AE:1;                  /**< \brief [31:31] Activate Error Enable (rwh) */
} Ifx_CPU_SEGEN_Bits;

/** \brief  SIST Mode Access Control Register */
typedef struct _Ifx_CPU_SMACON_Bits
{
    Ifx_Strict_32Bit PC:1;                  /**< \brief [0:0] Instruction Cache Memory SIST Mode Access Control (rw) */
    Ifx_Strict_32Bit reserved_1:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PT:1;                  /**< \brief [2:2] Program Tag Memory SIST Mode Access Control (rw) */
    Ifx_Strict_32Bit reserved_3:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DC:1;                  /**< \brief [8:8] Data Cache Memory SIST Mode Access Control (rw) */
    Ifx_Strict_32Bit reserved_9:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DT:1;                  /**< \brief [10:10] Data Tag Memory SIST Mode Access Control (rw) */
    Ifx_Strict_32Bit reserved_11:13;        /**< \brief \internal Reserved */
    Ifx_Strict_32Bit IODT:1;                /**< \brief [24:24] In-Order Data Transactions (rw) */
    Ifx_Strict_32Bit reserved_25:7;         /**< \brief \internal Reserved */
} Ifx_CPU_SMACON_Bits;

/** \brief  CPU Safety Protection Register Access Enable Register A */
typedef struct _Ifx_CPU_SPROT_ACCENA_Bits
{
    unsigned int EN:32;                     /**< \brief [31:0] Access Enable for Master TAG ID n (n= 0-31) (rw) */
} Ifx_CPU_SPROT_ACCENA_Bits;

/** \brief  CPU Safety Protection Region Access Enable Register B */
typedef struct _Ifx_CPU_SPROT_ACCENB_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_CPU_SPROT_ACCENB_Bits;

/** \brief  CPU Safety Protection Region Access Enable Register A */
typedef struct _Ifx_CPU_SPROT_RGN_ACCENA_Bits
{
    unsigned int EN:32;                     /**< \brief [31:0] Access Enable for Master TAG ID n (n = 0-31) (rw) */
} Ifx_CPU_SPROT_RGN_ACCENA_Bits;

/** \brief  CPU Safety Protection Region Access Enable Register B */
typedef struct _Ifx_CPU_SPROT_RGN_ACCENB_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_CPU_SPROT_RGN_ACCENB_Bits;

/** \brief  CPU Safety Protection Region Lower Address Register */
typedef struct _Ifx_CPU_SPROT_RGN_LA_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int ADDR:27;                   /**< \brief [31:5] Region Lower Address (rw) */
} Ifx_CPU_SPROT_RGN_LA_Bits;

/** \brief  CPU Safety protection Region Upper Address Register */
typedef struct _Ifx_CPU_SPROT_RGN_UA_Bits
{
    unsigned int reserved_0:5;              /**< \brief \internal Reserved */
    unsigned int ADDR:27;                   /**< \brief [31:5] Region Upper Address (rw) */
} Ifx_CPU_SPROT_RGN_UA_Bits;

/** \brief  Software Debug Event */
typedef struct _Ifx_CPU_SWEVT_Bits
{
    Ifx_Strict_32Bit EVTA:3;                /**< \brief [2:0] Event Associated (rw) */
    Ifx_Strict_32Bit BBM:1;                 /**< \brief [3:3] Break Before Make (BBM) or Break After Make (BAM) Selection (rw) */
    Ifx_Strict_32Bit BOD:1;                 /**< \brief [4:4] Breakout Disable (rw) */
    Ifx_Strict_32Bit SUSP:1;                /**< \brief [5:5] CDC Suspend-Out Signal State (rw) */
    Ifx_Strict_32Bit CNT:2;                 /**< \brief [7:6] Counter (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_CPU_SWEVT_Bits;

/** \brief  System Configuration Register */
typedef struct _Ifx_CPU_SYSCON_Bits
{
    Ifx_Strict_32Bit FCDSF:1;               /**< \brief [0:0] Free Context List Depleted Sticky Flag (rwh) */
    Ifx_Strict_32Bit PROTEN:1;              /**< \brief [1:1] Memory Protection Enable (rw) */
    Ifx_Strict_32Bit TPROTEN:1;             /**< \brief [2:2] Temporal Protection Enable (rw) */
    Ifx_Strict_32Bit IS:1;                  /**< \brief [3:3] Initial State (rw) */
    Ifx_Strict_32Bit IT:1;                  /**< \brief [4:4] Initial State (rw) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_CPU_SYSCON_Bits;

/** \brief  CPU Task Address Space Identifier Register */
typedef struct _Ifx_CPU_TASK_ASI_Bits
{
    Ifx_Strict_32Bit ASI:5;                 /**< \brief [4:0] Address Space Identifier (rw) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_CPU_TASK_ASI_Bits;

/** \brief  CPU Temporal Protection System Control Register */
typedef struct _Ifx_CPU_TPS_CON_Bits
{
    Ifx_Strict_32Bit TEXP0:1;               /**< \brief [0:0] Timer0 Expired Flag (rh) */
    Ifx_Strict_32Bit TEXP1:1;               /**< \brief [1:1] Timer1 Expired Flag (rh) */
    Ifx_Strict_32Bit TEXP2:1;               /**< \brief [2:2] Timer1 Expired Flag (rh) */
    Ifx_Strict_32Bit reserved_3:13;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TTRAP:1;               /**< \brief [16:16] Temporal Protection Trap (rh) */
    Ifx_Strict_32Bit reserved_17:15;        /**< \brief \internal Reserved */
} Ifx_CPU_TPS_CON_Bits;

/** \brief  CPU Temporal Protection System Timer Register */
typedef struct _Ifx_CPU_TPS_TIMER_Bits
{
    Ifx_Strict_32Bit Timer:32;              /**< \brief [31:0] Temporal Protection Timer (rwh) */
} Ifx_CPU_TPS_TIMER_Bits;

/** \brief  Trigger Address */
typedef struct _Ifx_CPU_TR_ADR_Bits
{
    Ifx_Strict_32Bit ADDR:32;               /**< \brief [31:0] Comparison Address (rw) */
} Ifx_CPU_TR_ADR_Bits;

/** \brief  Trigger Event */
typedef struct _Ifx_CPU_TR_EVT_Bits
{
    Ifx_Strict_32Bit EVTA:3;                /**< \brief [2:0] Event Associated (rw) */
    Ifx_Strict_32Bit BBM:1;                 /**< \brief [3:3] Break Before Make (BBM) or Break After Make (BAM) Selection (rw) */
    Ifx_Strict_32Bit BOD:1;                 /**< \brief [4:4] Breakout Disable (rw) */
    Ifx_Strict_32Bit SUSP:1;                /**< \brief [5:5] CDC Suspend-Out Signal State (rw) */
    Ifx_Strict_32Bit CNT:2;                 /**< \brief [7:6] Counter (rw) */
    Ifx_Strict_32Bit reserved_8:4;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TYP:1;                 /**< \brief [12:12] Input Selection (rw) */
    Ifx_Strict_32Bit RNG:1;                 /**< \brief [13:13] Compare Type (rw) */
    Ifx_Strict_32Bit reserved_14:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ASI_EN:1;              /**< \brief [15:15] Enable ASI Comparison (rw) */
    Ifx_Strict_32Bit ASI:5;                 /**< \brief [20:16] Address Space Identifier (rw) */
    Ifx_Strict_32Bit reserved_21:6;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AST:1;                 /**< \brief [27:27] Address Store (rw) */
    Ifx_Strict_32Bit ALD:1;                 /**< \brief [28:28] Address Load (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_CPU_TR_EVT_Bits;

/** \brief  CPU Trigger Address x */
typedef struct _Ifx_CPU_TRIG_ACC_Bits
{
    Ifx_Strict_32Bit T0:1;                  /**< \brief [0:0] Trigger-0 (rh) */
    Ifx_Strict_32Bit T1:1;                  /**< \brief [1:1] Trigger-1 (rh) */
    Ifx_Strict_32Bit T2:1;                  /**< \brief [2:2] Trigger-2 (rh) */
    Ifx_Strict_32Bit T3:1;                  /**< \brief [3:3] Trigger-3 (rh) */
    Ifx_Strict_32Bit T4:1;                  /**< \brief [4:4] Trigger-4 (rh) */
    Ifx_Strict_32Bit T5:1;                  /**< \brief [5:5] Trigger-5 (rh) */
    Ifx_Strict_32Bit T6:1;                  /**< \brief [6:6] Trigger-6 (rh) */
    Ifx_Strict_32Bit T7:1;                  /**< \brief [7:7] Trigger-7 (rh) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_CPU_TRIG_ACC_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_union
 * \{  */

/** \brief  Address General Purpose Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_A_Bits B;                       /**< \brief Bitfield access */
} Ifx_CPU_A;

/** \brief  Base Interrupt Vector Table Pointer */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_BIV_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_BIV;

/** \brief  Base Trap Vector Table Pointer */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_BTV_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_BTV;

/** \brief  CPU Clock Cycle Count */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CCNT_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_CCNT;

/** \brief  Counter Control */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CCTRL_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_CCTRL;

/** \brief  Compatibility Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_COMPAT_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_COMPAT;

/** \brief  CPU Core Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CORE_ID_Bits B;                 /**< \brief Bitfield access */
} Ifx_CPU_CORE_ID;

/** \brief  CPU Code Protection Range Lower Bound Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CPR_L_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_CPR_L;

/** \brief  CPU Code Protection Range Upper Bound Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CPR_U_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_CPR_U;

/** \brief  CPU Identification Register TC1.6P */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CPU_ID_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_CPU_ID;

/** \brief  CPU Code Protection Execute Enable Register Set */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CPXE_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_CPXE;

/** \brief  Core Register Access Event */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CREVT_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_CREVT;

/** \brief  CPU Customer ID register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_CUS_ID_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_CUS_ID;

/** \brief  Data General Purpose Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_D_Bits B;                       /**< \brief Bitfield access */
} Ifx_CPU_D;

/** \brief  Data Asynchronous Trap Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DATR_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_DATR;

/** \brief  Debug Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DBGSR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DBGSR;

/** \brief  Debug Trap Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DBGTCR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_DBGTCR;

/** \brief  Data Memory Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DCON0_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DCON0;

/** \brief  Data Control Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DCON2_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DCON2;

/** \brief  CPU Debug Context Save Area Pointer */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DCX_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_DCX;

/** \brief  Data Error Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DEADD_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DEADD;

/** \brief  Data Integrity Error Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DIEAR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DIEAR;

/** \brief  Data Integrity Error Trap Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DIETR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DIETR;

/** \brief  CPU Debug Monitor Start Address */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DMS_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_DMS;

/** \brief  CPU Data Protection Range, Lower Bound Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DPR_L_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DPR_L;

/** \brief  CPU Data Protection Range, Upper Bound Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DPR_U_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_DPR_U;

/** \brief  CPU Data Protection Read Enable Register Set */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DPRE_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_DPRE;

/** \brief  CPU Data Protection Write Enable Register Set */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DPWE_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_DPWE;

/** \brief  Data Synchronous Trap Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_DSTR_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_DSTR;

/** \brief  External Event Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_EXEVT_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_EXEVT;

/** \brief  Free CSA List Head Pointer */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_FCX_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_FCX;

/** \brief  CPU Trap Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_FPU_TRAP_CON_Bits B;            /**< \brief Bitfield access */
} Ifx_CPU_FPU_TRAP_CON;

/** \brief  CPU Trapping Instruction Opcode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_FPU_TRAP_OPC_Bits B;            /**< \brief Bitfield access */
} Ifx_CPU_FPU_TRAP_OPC;

/** \brief  CPU Trapping Instruction Program Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_FPU_TRAP_PC_Bits B;             /**< \brief Bitfield access */
} Ifx_CPU_FPU_TRAP_PC;

/** \brief  CPU Trapping Instruction Operand Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_FPU_TRAP_SRC1_Bits B;           /**< \brief Bitfield access */
} Ifx_CPU_FPU_TRAP_SRC1;

/** \brief  CPU Trapping Instruction Operand Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_FPU_TRAP_SRC2_Bits B;           /**< \brief Bitfield access */
} Ifx_CPU_FPU_TRAP_SRC2;

/** \brief  Trapping Instruction Operand Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_FPU_TRAP_SRC3_Bits B;           /**< \brief Bitfield access */
} Ifx_CPU_FPU_TRAP_SRC3;

/** \brief  Instruction Count */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_ICNT_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_ICNT;

/** \brief  Interrupt Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_ICR_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_ICR;

/** \brief  Interrupt Stack Pointer */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_ISP_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_ISP;

/** \brief  Free CSA List Limit Pointer */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_LCX_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_LCX;

/** \brief  Multi-Count Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_M1CNT_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_M1CNT;

/** \brief  Multi-Count Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_M2CNT_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_M2CNT;

/** \brief  Multi-Count Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_M3CNT_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_M3CNT;

/** \brief  Program Counter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PC_Bits B;                      /**< \brief Bitfield access */
} Ifx_CPU_PC;

/** \brief  Program Control 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PCON0_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_PCON0;

/** \brief  Program Control 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PCON1_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_PCON1;

/** \brief  Program Control 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PCON2_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_PCON2;

/** \brief  Previous Context Information Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PCXI_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_PCXI;

/** \brief  Program Integrity Error Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PIEAR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_PIEAR;

/** \brief  Program Integrity Error Trap Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PIETR_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_PIETR;

/** \brief  Data Access CacheabilityRegister */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PMA0_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_PMA0;

/** \brief  Code Access CacheabilityRegister */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PMA1_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_PMA1;

/** \brief  Peripheral Space Identifier register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PMA2_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_PMA2;

/** \brief  Program Synchronous Trap Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PSTR_Bits B;                    /**< \brief Bitfield access */
} Ifx_CPU_PSTR;

/** \brief  Program Status Word */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_PSW_Bits B;                     /**< \brief Bitfield access */
} Ifx_CPU_PSW;

/** \brief  SRI Error Generation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SEGEN_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_SEGEN;

/** \brief  SIST Mode Access Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SMACON_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_SMACON;

/** \brief  CPU Safety Protection Register Access Enable Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SPROT_ACCENA_Bits B;            /**< \brief Bitfield access */
} Ifx_CPU_SPROT_ACCENA;

/** \brief  CPU Safety Protection Region Access Enable Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SPROT_ACCENB_Bits B;            /**< \brief Bitfield access */
} Ifx_CPU_SPROT_ACCENB;

/** \brief  CPU Safety Protection Region Access Enable Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SPROT_RGN_ACCENA_Bits B;        /**< \brief Bitfield access */
} Ifx_CPU_SPROT_RGN_ACCENA;

/** \brief  CPU Safety Protection Region Access Enable Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SPROT_RGN_ACCENB_Bits B;        /**< \brief Bitfield access */
} Ifx_CPU_SPROT_RGN_ACCENB;

/** \brief  CPU Safety Protection Region Lower Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SPROT_RGN_LA_Bits B;            /**< \brief Bitfield access */
} Ifx_CPU_SPROT_RGN_LA;

/** \brief  CPU Safety protection Region Upper Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SPROT_RGN_UA_Bits B;            /**< \brief Bitfield access */
} Ifx_CPU_SPROT_RGN_UA;

/** \brief  Software Debug Event */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SWEVT_Bits B;                   /**< \brief Bitfield access */
} Ifx_CPU_SWEVT;

/** \brief  System Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_SYSCON_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_SYSCON;

/** \brief  CPU Task Address Space Identifier Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_TASK_ASI_Bits B;                /**< \brief Bitfield access */
} Ifx_CPU_TASK_ASI;

/** \brief  CPU Temporal Protection System Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_TPS_CON_Bits B;                 /**< \brief Bitfield access */
} Ifx_CPU_TPS_CON;

/** \brief  CPU Temporal Protection System Timer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_TPS_TIMER_Bits B;               /**< \brief Bitfield access */
} Ifx_CPU_TPS_TIMER;

/** \brief  Trigger Address */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_TR_ADR_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_TR_ADR;

/** \brief  Trigger Event */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_TR_EVT_Bits B;                  /**< \brief Bitfield access */
} Ifx_CPU_TR_EVT;

/** \brief  CPU Trigger Address x */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_CPU_TRIG_ACC_Bits B;                /**< \brief Bitfield access */
} Ifx_CPU_TRIG_ACC;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Protection range */
typedef volatile struct _Ifx_CPU_CPR
{
    Ifx_CPU_CPR_L L;                        /**< \brief 0, CPU Code Protection Range Lower Bound Register */
    Ifx_CPU_CPR_U U;                        /**< \brief 4, CPU Code Protection Range Upper Bound Register */
} Ifx_CPU_CPR;

/** \brief  Protection range */
typedef volatile struct _Ifx_CPU_DPR
{
    Ifx_CPU_DPR_L L;                        /**< \brief 0, CPU Data Protection Range, Lower Bound Register */
    Ifx_CPU_DPR_U U;                        /**< \brief 4, CPU Data Protection Range, Upper Bound Register */
} Ifx_CPU_DPR;

/** \brief  Safety protection region */
typedef volatile struct _Ifx_CPU_SPROT_RGN
{
    Ifx_CPU_SPROT_RGN_LA LA;                /**< \brief 0, CPU Safety Protection Region Lower Address Register */
    Ifx_CPU_SPROT_RGN_UA UA;                /**< \brief 4, CPU Safety protection Region Upper Address Register */
    Ifx_CPU_SPROT_RGN_ACCENA ACCENA;        /**< \brief 8, CPU Safety Protection Region Access Enable Register A */
    Ifx_CPU_SPROT_RGN_ACCENB ACCENB;        /**< \brief C, CPU Safety Protection Region Access Enable Register B */
} Ifx_CPU_SPROT_RGN;

/** \brief  Temporal Protection System */
typedef volatile struct _Ifx_CPU_TPS
{
    Ifx_CPU_TPS_CON CON;                    /**< \brief 0, CPU Temporal Protection System Control Register */
    Ifx_CPU_TPS_TIMER TIMER[3];             /**< \brief 4, CPU Temporal Protection System Timer Register */
} Ifx_CPU_TPS;

/** \brief  Trigger */
typedef volatile struct _Ifx_CPU_TR
{
    Ifx_CPU_TR_EVT EVT;                     /**< \brief 0, Trigger Event  */
    Ifx_CPU_TR_ADR ADR;                     /**< \brief 4, Trigger Address  */
} Ifx_CPU_TR;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  CPU object */
typedef volatile struct _Ifx_CPU
{
    unsigned char reserved_0[4144];         /**< \brief 0, \internal Reserved */
    Ifx_CPU_SEGEN SEGEN;                    /**< \brief 1030, SRI Error Generation Register */
    unsigned char reserved_1034[28624];     /**< \brief 1034, \internal Reserved */
    Ifx_CPU_TASK_ASI TASK_ASI;              /**< \brief 8004, CPU Task Address Space Identifier Register */
    unsigned char reserved_8008[248];       /**< \brief 8008, \internal Reserved */
    Ifx_CPU_PMA0 PMA0;                      /**< \brief 8100, Data Access CacheabilityRegister */
    Ifx_CPU_PMA1 PMA1;                      /**< \brief 8104, Code Access CacheabilityRegister */
    Ifx_CPU_PMA2 PMA2;                      /**< \brief 8108, Peripheral Space Identifier register */
    unsigned char reserved_810C[3828];      /**< \brief 810C, \internal Reserved */
    Ifx_CPU_DCON2 DCON2;                    /**< \brief 9000, Data Control Register 2 */
    unsigned char reserved_9004[8];         /**< \brief 9004, \internal Reserved */
    Ifx_CPU_SMACON SMACON;                  /**< \brief 900C, SIST Mode Access Control Register */
    Ifx_CPU_DSTR DSTR;                      /**< \brief 9010, Data Synchronous Trap Register */
    unsigned char reserved_9014[4];         /**< \brief 9014, \internal Reserved */
    Ifx_CPU_DATR DATR;                      /**< \brief 9018, Data Asynchronous Trap Register */
    Ifx_CPU_DEADD DEADD;                    /**< \brief 901C, Data Error Address Register */
    Ifx_CPU_DIEAR DIEAR;                    /**< \brief 9020, Data Integrity Error Address Register */
    Ifx_CPU_DIETR DIETR;                    /**< \brief 9024, Data Integrity Error Trap Register */
    unsigned char reserved_9028[24];        /**< \brief 9028, \internal Reserved */
    Ifx_CPU_DCON0 DCON0;                    /**< \brief 9040, Data Memory Control Register */
    unsigned char reserved_9044[444];       /**< \brief 9044, \internal Reserved */
    Ifx_CPU_PSTR PSTR;                      /**< \brief 9200, Program Synchronous Trap Register */
    Ifx_CPU_PCON1 PCON1;                    /**< \brief 9204, Program Control 1 */
    Ifx_CPU_PCON2 PCON2;                    /**< \brief 9208, Program Control 2 */
    Ifx_CPU_PCON0 PCON0;                    /**< \brief 920C, Program Control 0 */
    Ifx_CPU_PIEAR PIEAR;                    /**< \brief 9210, Program Integrity Error Address Register */
    Ifx_CPU_PIETR PIETR;                    /**< \brief 9214, Program Integrity Error Trap Register */
    unsigned char reserved_9218[488];       /**< \brief 9218, \internal Reserved */
    Ifx_CPU_COMPAT COMPAT;                  /**< \brief 9400, Compatibility Control Register */
    unsigned char reserved_9404[3068];      /**< \brief 9404, \internal Reserved */
    Ifx_CPU_FPU_TRAP_CON FPU_TRAP_CON;      /**< \brief A000, CPU Trap Control Register */
    Ifx_CPU_FPU_TRAP_PC FPU_TRAP_PC;        /**< \brief A004, CPU Trapping Instruction Program Counter Register */
    Ifx_CPU_FPU_TRAP_OPC FPU_TRAP_OPC;      /**< \brief A008, CPU Trapping Instruction Opcode Register */
    unsigned char reserved_A00C[4];         /**< \brief A00C, \internal Reserved */
    Ifx_CPU_FPU_TRAP_SRC1 FPU_TRAP_SRC1;    /**< \brief A010, CPU Trapping Instruction Operand Register */
    Ifx_CPU_FPU_TRAP_SRC2 FPU_TRAP_SRC2;    /**< \brief A014, CPU Trapping Instruction Operand Register */
    Ifx_CPU_FPU_TRAP_SRC3 FPU_TRAP_SRC3;    /**< \brief A018, Trapping Instruction Operand Register */
    unsigned char reserved_A01C[8164];      /**< \brief A01C, \internal Reserved */
    Ifx_CPU_DPR DPR[16];                    /**< \brief C000, Protection range */
    unsigned char reserved_C080[3968];      /**< \brief C080, \internal Reserved */
    Ifx_CPU_CPR CPR[8];                     /**< \brief D000, Protection range */
    unsigned char reserved_D040[4032];      /**< \brief D040, \internal Reserved */
    Ifx_CPU_CPXE CPXE[4];                   /**< \brief E000, CPU Code Protection Execute Enable Register Set */
    Ifx_CPU_DPRE DPRE[4];                   /**< \brief E010, CPU Data Protection Read Enable Register Set */
    Ifx_CPU_DPWE DPWE[4];                   /**< \brief E020, CPU Data Protection Write Enable Register Set */
    unsigned char reserved_E030[976];       /**< \brief E030, \internal Reserved */
    Ifx_CPU_TPS TPS;                        /**< \brief E400, Temporal Protection System */
    unsigned char reserved_E410[3056];      /**< \brief E410, \internal Reserved */
    Ifx_CPU_TR TR[8];                       /**< \brief F000, Trigger */
    unsigned char reserved_F040[3008];      /**< \brief F040, \internal Reserved */
    Ifx_CPU_CCTRL CCTRL;                    /**< \brief FC00, Counter Control */
    Ifx_CPU_CCNT CCNT;                      /**< \brief FC04, CPU Clock Cycle Count */
    Ifx_CPU_ICNT ICNT;                      /**< \brief FC08, Instruction Count */
    Ifx_CPU_M1CNT M1CNT;                    /**< \brief FC0C, Multi-Count Register 1 */
    Ifx_CPU_M2CNT M2CNT;                    /**< \brief FC10, Multi-Count Register 2 */
    Ifx_CPU_M3CNT M3CNT;                    /**< \brief FC14, Multi-Count Register 3 */
    unsigned char reserved_FC18[232];       /**< \brief FC18, \internal Reserved */
    Ifx_CPU_DBGSR DBGSR;                    /**< \brief FD00, Debug Status Register */
    unsigned char reserved_FD04[4];         /**< \brief FD04, \internal Reserved */
    Ifx_CPU_EXEVT EXEVT;                    /**< \brief FD08, External Event Register */
    Ifx_CPU_CREVT CREVT;                    /**< \brief FD0C, Core Register Access Event */
    Ifx_CPU_SWEVT SWEVT;                    /**< \brief FD10, Software Debug Event */
    unsigned char reserved_FD14[28];        /**< \brief FD14, \internal Reserved */
    Ifx_CPU_TRIG_ACC TRIG_ACC;              /**< \brief FD30, CPU Trigger Address x */
    unsigned char reserved_FD34[12];        /**< \brief FD34, \internal Reserved */
    Ifx_CPU_DMS DMS;                        /**< \brief FD40, CPU Debug Monitor Start Address */
    Ifx_CPU_DCX DCX;                        /**< \brief FD44, CPU Debug Context Save Area Pointer */
    Ifx_CPU_DBGTCR DBGTCR;                  /**< \brief FD48, Debug Trap Control Register */
    unsigned char reserved_FD4C[180];       /**< \brief FD4C, \internal Reserved */
    Ifx_CPU_PCXI PCXI;                      /**< \brief FE00, Previous Context Information Register */
    Ifx_CPU_PSW PSW;                        /**< \brief FE04, Program Status Word */
    Ifx_CPU_PC PC;                          /**< \brief FE08, Program Counter */
    unsigned char reserved_FE0C[8];         /**< \brief FE0C, \internal Reserved */
    Ifx_CPU_SYSCON SYSCON;                  /**< \brief FE14, System Configuration Register */
    Ifx_CPU_CPU_ID CPU_ID;                  /**< \brief FE18, CPU Identification Register TC1.6P */
    Ifx_CPU_CORE_ID CORE_ID;                /**< \brief FE1C, CPU Core Identification Register */
    Ifx_CPU_BIV BIV;                        /**< \brief FE20, Base Interrupt Vector Table Pointer */
    Ifx_CPU_BTV BTV;                        /**< \brief FE24, Base Trap Vector Table Pointer */
    Ifx_CPU_ISP ISP;                        /**< \brief FE28, Interrupt Stack Pointer */
    Ifx_CPU_ICR ICR;                        /**< \brief FE2C, Interrupt Control Register */
    unsigned char reserved_FE30[8];         /**< \brief FE30, \internal Reserved */
    Ifx_CPU_FCX FCX;                        /**< \brief FE38, Free CSA List Head Pointer */
    Ifx_CPU_LCX LCX;                        /**< \brief FE3C, Free CSA List Limit Pointer */
    unsigned char reserved_FE40[16];        /**< \brief FE40, \internal Reserved */
    Ifx_CPU_CUS_ID CUS_ID;                  /**< \brief FE50, CPU Customer ID register */
    unsigned char reserved_FE54[172];       /**< \brief FE54, \internal Reserved */
    Ifx_CPU_D D[16];                        /**< \brief FF00, Data General Purpose Register */
    unsigned char reserved_FF40[64];        /**< \brief FF40, \internal Reserved */
    Ifx_CPU_A A[16];                        /**< \brief FF80, Address General Purpose Register */
    unsigned char reserved_FFC0[64];        /**< \brief FFC0, \internal Reserved */
} Ifx_CPU;

/** \brief  CPU SPROT object */
typedef volatile struct _Ifx_CPU_SPROT
{
    unsigned char reserved_0[57344];        /**< \brief 0, \internal Reserved */
    Ifx_CPU_SPROT_RGN RGN[8];               /**< \brief E000, Safety protection region */
    unsigned char reserved_E080[128];       /**< \brief E080, \internal Reserved */
    Ifx_CPU_SPROT_ACCENA ACCENA;            /**< \brief E100, CPU Safety Protection Register Access Enable Register A */
    Ifx_CPU_SPROT_ACCENB ACCENB;            /**< \brief E104, CPU Safety Protection Region Access Enable Register B */
    unsigned char reserved_E108[7928];      /**< \brief E108, \internal Reserved */
} Ifx_CPU_SPROT;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXCPU_REGDEF_H */
