/**
 * \file IfxPsi5s_regdef.h
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
 * \defgroup IfxLld_Psi5s Psi5s
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Psi5s_Bitfields Bitfields
 * \ingroup IfxLld_Psi5s
 * 
 * \defgroup IfxLld_Psi5s_union Union
 * \ingroup IfxLld_Psi5s
 * 
 * \defgroup IfxLld_Psi5s_struct Struct
 * \ingroup IfxLld_Psi5s
 * 
 */
#ifndef IFXPSI5S_REGDEF_H
#define IFXPSI5S_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Psi5s_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_PSI5S_ACCEN0_Bits
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
} Ifx_PSI5S_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_PSI5S_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_PSI5S_ACCEN1_Bits;

/** \brief  Base Address Register */
typedef struct _Ifx_PSI5S_BAR_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int BA:30;                     /**< \brief [31:2] Base Address (rw) */
} Ifx_PSI5S_BAR_Bits;

/** \brief  Baud Rate Timer/Reload Register */
typedef struct _Ifx_PSI5S_BG_Bits
{
    unsigned int BR_VALUE:13;               /**< \brief [12:0] Baud Rate Timer/Reload Register Value (rwh) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_PSI5S_BG_Bits;

/** \brief  CPU Direct Write Register */
typedef struct _Ifx_PSI5S_CDW_Bits
{
    unsigned int SD0:1;                     /**< \brief [0:0] SD0 (rw) */
    unsigned int SD1:1;                     /**< \brief [1:1] SD1 (rw) */
    unsigned int SD2:1;                     /**< \brief [2:2] SD2 (rw) */
    unsigned int SD3:1;                     /**< \brief [3:3] SD3 (rw) */
    unsigned int SD4:1;                     /**< \brief [4:4] SD4 (rw) */
    unsigned int SD5:1;                     /**< \brief [5:5] SD5 (rw) */
    unsigned int SD6:1;                     /**< \brief [6:6] SD6 (rw) */
    unsigned int SD7:1;                     /**< \brief [7:7] SD7 (rw) */
    unsigned int TSI:1;                     /**< \brief [8:8] Trigger Pulse Indicator (rw) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_PSI5S_CDW_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_PSI5S_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] External Sleep Mode Request Disable Bit (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_PSI5S_CLC_Bits;

/** \brief  Control Register */
typedef struct _Ifx_PSI5S_CON_Bits
{
    unsigned int M:3;                       /**< \brief [2:0] Mode Selection (rw) */
    unsigned int STP:1;                     /**< \brief [3:3] Number of Stop Bit Selection (rw) */
    unsigned int REN:1;                     /**< \brief [4:4] Receiver Enable Control (r) */
    unsigned int PEN:1;                     /**< \brief [5:5] Parity Check Enable (asynchronous mode only) (rw) */
    unsigned int FEN:1;                     /**< \brief [6:6] Framing Check Enable (asynchronous mode only) (rw) */
    unsigned int OEN:1;                     /**< \brief [7:7] Overrun Check Enable (rw) */
    unsigned int PE:1;                      /**< \brief [8:8] ASC Parity Error Flag (r) */
    unsigned int FE:1;                      /**< \brief [9:9] ASC Framing Error Flag (r) */
    unsigned int OE:1;                      /**< \brief [10:10] ASC Overrun Error Flag (r) */
    unsigned int FDE:1;                     /**< \brief [11:11] Fractional Divider Enable (rw) */
    unsigned int ODD:1;                     /**< \brief [12:12] Parity Selection (rw) */
    unsigned int BRS:1;                     /**< \brief [13:13] Baud Rate Selection (rw) */
    unsigned int LB:1;                      /**< \brief [14:14] Loop-back Mode Enable (rw) */
    unsigned int R:1;                       /**< \brief [15:15] Baud Rate Generator Run Control (rw) */
    unsigned int MTX:3;                     /**< \brief [18:16] Mode Selection TX direction (rw) */
    unsigned int reserved_19:9;             /**< \brief \internal Reserved */
    unsigned int ODDTX:1;                   /**< \brief [28:28] Parity Selection TX direction (rw) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_PSI5S_CON_Bits;

/** \brief  Channel Trigger Value Register */
typedef struct _Ifx_PSI5S_CTV_Bits
{
    unsigned int CTV:16;                    /**< \brief [15:0] Channel Trigger Value CTV (rw) */
    unsigned int CTC:16;                    /**< \brief [31:16] Channel Trigger Counter (rw) */
} Ifx_PSI5S_CTV_Bits;

/** \brief  Frame Counter Register */
typedef struct _Ifx_PSI5S_FCNT_Bits
{
    unsigned int FC0:3;                     /**< \brief [2:0] Frame Counter for Channel 0 (r) */
    unsigned int FC1:3;                     /**< \brief [5:3] Frame Counter for Channel 1 (r) */
    unsigned int FC2:3;                     /**< \brief [8:6] Frame Counter for Channel 2 (r) */
    unsigned int FC3:3;                     /**< \brief [11:9] Frame Counter for Channel 3 (r) */
    unsigned int FC4:3;                     /**< \brief [14:12] Frame Counter for Channel 4 (r) */
    unsigned int FC5:3;                     /**< \brief [17:15] Frame Counter for Channel 5 (r) */
    unsigned int FC6:3;                     /**< \brief [20:18] Frame Counter for Channel 6 (r) */
    unsigned int FC7:3;                     /**< \brief [23:21] Frame Counter for Channel 7 (r) */
    unsigned int NFCLR0:1;                  /**< \brief [24:24] Clear Number of Frame Counter for Channel 0 (w) */
    unsigned int NFCLR1:1;                  /**< \brief [25:25] Clear Number of Frame Counter for Channel 1 (w) */
    unsigned int NFCLR2:1;                  /**< \brief [26:26] Clear Number of Frame Counter for Channel 2 (w) */
    unsigned int NFCLR3:1;                  /**< \brief [27:27] Clear Number of Frame Counter for Channel 3 (w) */
    unsigned int NFCLR4:1;                  /**< \brief [28:28] Clear Number of Frame Counter for Channel 4 (w) */
    unsigned int NFCLR5:1;                  /**< \brief [29:29] Clear Number of Frame Counter for Channel 5 (w) */
    unsigned int NFCLR6:1;                  /**< \brief [30:30] Clear Number of Frame Counter for Channel 6 (w) */
    unsigned int NFCLR7:1;                  /**< \brief [31:31] Clear Number of Frame Counter for Channel 7 (w) */
} Ifx_PSI5S_FCNT_Bits;

/** \brief  Fractional Divider for Output CLK Register */
typedef struct _Ifx_PSI5S_FDO_Bits
{
    unsigned int STEP:11;                   /**< \brief [10:0] Step Value (rw) */
    unsigned int reserved_11:3;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_PSI5S_FDO_Bits;

/** \brief  PSI5-S Fractional Divider Register */
typedef struct _Ifx_PSI5S_FDR_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int reserved_26:6;             /**< \brief \internal Reserved */
} Ifx_PSI5S_FDR_Bits;

/** \brief  Fractional Divider Register for Time Stamp */
typedef struct _Ifx_PSI5S_FDRT_Bits
{
    unsigned int STEP:10;                   /**< \brief [9:0] Step Value (rw) */
    unsigned int reserved_10:4;             /**< \brief \internal Reserved */
    unsigned int DM:2;                      /**< \brief [15:14] Divider Mode (rw) */
    unsigned int RESULT:10;                 /**< \brief [25:16] Result Value (rh) */
    unsigned int ECS:3;                     /**< \brief [28:26] External Time Stamp Clear Source Select (rw) */
    unsigned int ECEA:1;                    /**< \brief [29:29] External Time Stamp Clear Enable A (rw) */
    unsigned int ECEB:1;                    /**< \brief [30:30] External Time Stamp Clear Enable B (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_PSI5S_FDRT_Bits;

/** \brief  Fractional Divider Register */
typedef struct _Ifx_PSI5S_FDV_Bits
{
    unsigned int FD_VALUE:11;               /**< \brief [10:0] Fractional Divider Register Value (rw) */
    unsigned int reserved_11:21;            /**< \brief \internal Reserved */
} Ifx_PSI5S_FDV_Bits;

/** \brief  Global Control Register */
typedef struct _Ifx_PSI5S_GCR_Bits
{
    unsigned int CRCI:1;                    /**< \brief [0:0] CRCI (rw) */
    unsigned int XCRCI:1;                   /**< \brief [1:1] XCRCI (rw) */
    unsigned int TEI:1;                     /**< \brief [2:2] TEI (rw) */
    unsigned int PE:1;                      /**< \brief [3:3] PE (rw) */
    unsigned int FE:1;                      /**< \brief [4:4] FE (rw) */
    unsigned int OE:1;                      /**< \brief [5:5] OE (rw) */
    unsigned int RBI:1;                     /**< \brief [6:6] RBI (rw) */
    unsigned int HDI:1;                     /**< \brief [7:7] HDI (rw) */
    unsigned int ETC0:1;                    /**< \brief [8:8] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC1:1;                    /**< \brief [9:9] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC2:1;                    /**< \brief [10:10] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC3:1;                    /**< \brief [11:11] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC4:1;                    /**< \brief [12:12] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC5:1;                    /**< \brief [13:13] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC6:1;                    /**< \brief [14:14] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int ETC7:1;                    /**< \brief [15:15] Enable Channel Trigger Counter CTVx.CTC (rw) */
    unsigned int CEN0:1;                    /**< \brief [16:16] Enable Channel 0 (rw) */
    unsigned int CEN1:1;                    /**< \brief [17:17] Enable Channel 1 (rw) */
    unsigned int CEN2:1;                    /**< \brief [18:18] Enable Channel 2 (rw) */
    unsigned int CEN3:1;                    /**< \brief [19:19] Enable Channel 3 (rw) */
    unsigned int CEN4:1;                    /**< \brief [20:20] Enable Channel 4 (rw) */
    unsigned int CEN5:1;                    /**< \brief [21:21] Enable Channel 5 (rw) */
    unsigned int CEN6:1;                    /**< \brief [22:22] Enable Channel 6 (rw) */
    unsigned int CEN7:1;                    /**< \brief [23:23] Enable Channel 7 (rw) */
    unsigned int IDT:4;                     /**< \brief [27:24] Idle Time (GLOBAL VALUE FOR ALL CHANNELS) (rw) */
    unsigned int reserved_28:3;             /**< \brief \internal Reserved */
    unsigned int ASC:1;                     /**< \brief [31:31] ASC only Mode (rw) */
} Ifx_PSI5S_GCR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_PSI5S_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_PSI5S_ID_Bits;

/** \brief  Interrupt Node Pointer Register */
typedef struct _Ifx_PSI5S_INP_Bits
{
    unsigned int RSI:3;                     /**< \brief [2:0] Interrupt Node Pointer for Interrupt RSI (rw) */
    unsigned int RDI:3;                     /**< \brief [5:3] Interrupt Node Pointer for Interrupt RDI (rw) */
    unsigned int RBI:3;                     /**< \brief [8:6] Interrupt Node Pointer for Interrupt RBI (rw) */
    unsigned int TEI:3;                     /**< \brief [11:9] Interrupt Node Pointer for Interrupt TEI (rw) */
    unsigned int CHCI:3;                    /**< \brief [14:12] Interrupt Node Pointer for Interrupt CHCI (rw) */
    unsigned int CRCI:3;                    /**< \brief [17:15] Interrupt Node Pointer for Interrupt CRCI (rw) */
    unsigned int TPI:3;                     /**< \brief [20:18] Interrupt Node Pointer for Interrupt TOI (rw) */
    unsigned int TPOI:3;                    /**< \brief [23:21] Interrupt Node Pointer for TPOI (rw) */
    unsigned int HDI:3;                     /**< \brief [26:24] Interrupt Node Pointer for HDI (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INP_Bits;

/** \brief  Interrupt Node Pointer G Register */
typedef struct _Ifx_PSI5S_INPG_Bits
{
    unsigned int TIR:3;                     /**< \brief [2:0] Interrupt Node Pointer for Interrupt TIR (rw) */
    unsigned int RIR:3;                     /**< \brief [5:3] Interrupt Node Pointer for Interrupt RIR (rw) */
    unsigned int EIR:3;                     /**< \brief [8:6] Interrupt Node Pointer for Interrupt EIR (rw) */
    unsigned int TBIR:3;                    /**< \brief [11:9] Interrupt Node Pointer for Interrupt TBIR (rw) */
    unsigned int XCRCI:3;                   /**< \brief [14:12] Interrupt Node Pointer for Interrupt XCRCI (rw) */
    unsigned int FOI:3;                     /**< \brief [17:15] Interrupt Node Pointer for Interrupt FOI (rw) */
    unsigned int reserved_18:14;            /**< \brief \internal Reserved */
} Ifx_PSI5S_INPG_Bits;

/** \brief  Interrupt Clear Register */
typedef struct _Ifx_PSI5S_INTCLR_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Clear Interrupt Request Flag RSI (w) */
    unsigned int RDI:1;                     /**< \brief [1:1] Clear Interrupt Request Flag RDI (w) */
    unsigned int RBI:1;                     /**< \brief [2:2] Clear Interrupt Request Flag RBI (w) */
    unsigned int TEI:1;                     /**< \brief [3:3] Clear Interrupt Request Flag TEI (w) */
    unsigned int CHCI:1;                    /**< \brief [4:4] Clear Interrupt Request Flag CHCI (w) */
    unsigned int CRCI:1;                    /**< \brief [5:5] Clear Interrupt Request Flag CRCI (w) */
    unsigned int TPI:1;                     /**< \brief [6:6] Clear Interrupt Request Flag TPI (w) */
    unsigned int TPOI:1;                    /**< \brief [7:7] Clear Interrupt Request Flag TPOI (w) */
    unsigned int HDI:1;                     /**< \brief [8:8] Clear Interrupt Request Flag HDI (w) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTCLR_Bits;

/** \brief  Interrupt Clear Register G */
typedef struct _Ifx_PSI5S_INTCLRG_Bits
{
    unsigned int TIR:1;                     /**< \brief [0:0] Clear Interrupt Request Flag TIR (w) */
    unsigned int RIR:1;                     /**< \brief [1:1] Clear Interrupt Request Flag RIR (w) */
    unsigned int EIR:1;                     /**< \brief [2:2] Clear Interrupt Request Flag EIR (w) */
    unsigned int TBIR:1;                    /**< \brief [3:3] Clear Interrupt Request Flag TBIR (w) */
    unsigned int XCRCI:1;                   /**< \brief [4:4] Clear Interrupt Request Flag XCRCI (w) */
    unsigned int FOI:1;                     /**< \brief [5:5] Clear Interrupt Request Flag FOI (w) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTCLRG_Bits;

/** \brief  Interrupt Enable Register */
typedef struct _Ifx_PSI5S_INTEN_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Enable Interrupt Request RSI (rw) */
    unsigned int RDI:1;                     /**< \brief [1:1] Enable Interrupt Request RDI (rw) */
    unsigned int RBI:1;                     /**< \brief [2:2] Enable Interrupt Request RBI (rw) */
    unsigned int TEI:1;                     /**< \brief [3:3] Enable Interrupt Request TEI (rw) */
    unsigned int CHCI:1;                    /**< \brief [4:4] Enable Interrupt Request CHCI (rw) */
    unsigned int CRCI:1;                    /**< \brief [5:5] Enable Interrupt Request CRCI (rw) */
    unsigned int TPI:1;                     /**< \brief [6:6] Enable Interrupt Request TPI (rw) */
    unsigned int TPOI:1;                    /**< \brief [7:7] Enable Interrupt Request TPOI (rw) */
    unsigned int HDI:1;                     /**< \brief [8:8] Enable Interrupt Request HDI (rw) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTEN_Bits;

/** \brief  Interrupt Enable Register G */
typedef struct _Ifx_PSI5S_INTENG_Bits
{
    unsigned int TIR:1;                     /**< \brief [0:0] Enable Interrupt Request TIR (rw) */
    unsigned int RIR:1;                     /**< \brief [1:1] Enable Interrupt Request RIR (rw) */
    unsigned int EIR:1;                     /**< \brief [2:2] Enable Interrupt Request EIR (rw) */
    unsigned int TBIR:1;                    /**< \brief [3:3] Enable Interrupt Request TBIR (rw) */
    unsigned int XCRCI:1;                   /**< \brief [4:4] Enable Interrupt Request XCRCI (rw) */
    unsigned int FOI:1;                     /**< \brief [5:5] Enable Interrupt Request FOI (rw) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTENG_Bits;

/** \brief  Interrupt Overview Register */
typedef struct _Ifx_PSI5S_INTOV_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Interrupt Pending on Node Pointer RSI (rh) */
    unsigned int RDI:1;                     /**< \brief [1:1] Interrupt Pending on Node Pointer RDI (rh) */
    unsigned int RBI:1;                     /**< \brief [2:2] Interrupt Pending on Node Pointer RBI (rh) */
    unsigned int TEI:1;                     /**< \brief [3:3] Interrupt Pending on Node Pointer TEI (rh) */
    unsigned int CHCI:1;                    /**< \brief [4:4] Interrupt Pending on Node Pointer CHCI (rh) */
    unsigned int CRCI:1;                    /**< \brief [5:5] Interrupt Pending on Node Pointer CRCI (rh) */
    unsigned int TPI:1;                     /**< \brief [6:6] Interrupt Pending on Node Pointer TPI (rh) */
    unsigned int TPOI:1;                    /**< \brief [7:7] Interrupt Pending on Node Pointer TPOI (rh) */
    unsigned int HDI:1;                     /**< \brief [8:8] Interrupt Pending on Node Pointer HDI (rh) */
    unsigned int TIR:1;                     /**< \brief [9:9] Interrupt Pending on Node Pointer TIR (rh) */
    unsigned int RIR:1;                     /**< \brief [10:10] Interrupt Pending on Node Pointer RIR (rh) */
    unsigned int EIR:1;                     /**< \brief [11:11] Interrupt Pending on Node Pointer EIR (rh) */
    unsigned int TBIR:1;                    /**< \brief [12:12] Interrupt Pending on Node Pointer TBIR (rh) */
    unsigned int XCRCI:1;                   /**< \brief [13:13] Interrupt Pending on Node Pointer XCRCI (rh) */
    unsigned int FOI:1;                     /**< \brief [14:14] Interrupt Pending on Node Pointer FOI (rh) */
    unsigned int reserved_15:17;            /**< \brief \internal Reserved */
} Ifx_PSI5S_INTOV_Bits;

/** \brief  Interrupt Set Register */
typedef struct _Ifx_PSI5S_INTSET_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Set Interrupt Request Flag RSI (w) */
    unsigned int RDI:1;                     /**< \brief [1:1] Set Interrupt Request Flag RDI (w) */
    unsigned int RBI:1;                     /**< \brief [2:2] Set Interrupt Request Flag RBI (w) */
    unsigned int TEI:1;                     /**< \brief [3:3] Set Interrupt Request Flag TEI (w) */
    unsigned int CHCI:1;                    /**< \brief [4:4] Set Interrupt Request Flag CHCI (w) */
    unsigned int CRCI:1;                    /**< \brief [5:5] Set Interrupt Request Flag CRCI (w) */
    unsigned int TPI:1;                     /**< \brief [6:6] Set Interrupt Request Flag TPI (w) */
    unsigned int TPOI:1;                    /**< \brief [7:7] Set Interrupt Request Flag TPOI (w) */
    unsigned int HDI:1;                     /**< \brief [8:8] Set Interrupt Request Flag HDI (w) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTSET_Bits;

/** \brief  Interrupt Set Register G */
typedef struct _Ifx_PSI5S_INTSETG_Bits
{
    unsigned int TIR:1;                     /**< \brief [0:0] Set Interrupt Request Flag TIR (w) */
    unsigned int RIR:1;                     /**< \brief [1:1] Set Interrupt Request Flag RIR (w) */
    unsigned int EIR:1;                     /**< \brief [2:2] Set Interrupt Request Flag EIR (w) */
    unsigned int TBIR:1;                    /**< \brief [3:3] Set Interrupt Request Flag TBIR (w) */
    unsigned int XCRCI:1;                   /**< \brief [4:4] Set Interrupt Request Flag XCRCI (w) */
    unsigned int FOI:1;                     /**< \brief [5:5] Set Interrupt Request Flag FOI (w) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTSETG_Bits;

/** \brief  Interrupt Status Register */
typedef struct _Ifx_PSI5S_INTSTAT_Bits
{
    unsigned int RSI:1;                     /**< \brief [0:0] Receive Success Interrupt Request Flag (rh) */
    unsigned int RDI:1;                     /**< \brief [1:1] Receive Data Interrupt Request Flag (rh) */
    unsigned int RBI:1;                     /**< \brief [2:2] Receive Buffer Overflow Interrupt Request Flag (rh) */
    unsigned int TEI:1;                     /**< \brief [3:3] Timing Error Interrupt Request Flag (rh) */
    unsigned int CHCI:1;                    /**< \brief [4:4] Channel Completed Interrupt Request Flag (rh) */
    unsigned int CRCI:1;                    /**< \brief [5:5] CRC Error Request Flag (rh) */
    unsigned int TPI:1;                     /**< \brief [6:6] Transfer Preparation Interrupt Request Flag (rh) */
    unsigned int TPOI:1;                    /**< \brief [7:7] Transmit Preparation Overflow Interrupt Request Flag (rh) */
    unsigned int HDI:1;                     /**< \brief [8:8] Header Error Signalled Flag (rh) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTSTAT_Bits;

/** \brief  Interrupt Status Register G */
typedef struct _Ifx_PSI5S_INTSTATG_Bits
{
    unsigned int TIR:1;                     /**< \brief [0:0] Transmit Interrupt Request Flag (rh) */
    unsigned int RIR:1;                     /**< \brief [1:1] Receive Interrupt Request Flag (rh) */
    unsigned int EIR:1;                     /**< \brief [2:2] Error Interrupt Request Flag (rh) */
    unsigned int TBIR:1;                    /**< \brief [3:3] Transmit Buffer Interrupt Request Flag (rh) */
    unsigned int XCRCI:1;                   /**< \brief [4:4] XCRC Error Request Flag (rh) */
    unsigned int FOI:1;                     /**< \brief [5:5] FIFO Error Request Flag (rh) */
    unsigned int reserved_6:26;             /**< \brief \internal Reserved */
} Ifx_PSI5S_INTSTATG_Bits;

/** \brief  Input and Output Control Register */
typedef struct _Ifx_PSI5S_IOCR_Bits
{
    unsigned int ALTI:2;                    /**< \brief [1:0] Alternate Input Select (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_PSI5S_IOCR_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_PSI5S_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_PSI5S_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_PSI5S_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_PSI5S_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_PSI5S_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_PSI5S_KRSTCLR_Bits;

/** \brief  Number of Frames Control Register */
typedef struct _Ifx_PSI5S_NFC_Bits
{
    unsigned int NF0:3;                     /**< \brief [2:0] Number of expected Frames on Channel 0 (rw) */
    unsigned int NF1:3;                     /**< \brief [5:3] Number of expected Frames on Channel 1 (rw) */
    unsigned int NF2:3;                     /**< \brief [8:6] Number of expected Frames on Channel 2 (rw) */
    unsigned int NF3:3;                     /**< \brief [11:9] Number of expected Frames on Channel 3 (rw) */
    unsigned int NF4:3;                     /**< \brief [14:12] Number of expected Frames on Channel 4 (rw) */
    unsigned int NF5:3;                     /**< \brief [17:15] Number of expected Frames on Channel 5 (rw) */
    unsigned int NF6:3;                     /**< \brief [20:18] Number of expected Frames on Channel 6 (rw) */
    unsigned int NF7:3;                     /**< \brief [23:21] Number of expected Frames on Channel 7 (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5S_NFC_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_PSI5S_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_PSI5S_OCS_Bits;

/** \brief  Pulse Generation Control Register */
typedef struct _Ifx_PSI5S_PGC_Bits
{
    unsigned int TXCMD:5;                   /**< \brief [4:0] TX Command (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int ATXCMD:5;                  /**< \brief [12:8] Alternate TX Command (rw) */
    unsigned int reserved_13:2;             /**< \brief \internal Reserved */
    unsigned int TBS:1;                     /**< \brief [15:15] Time Base Select (rw) */
    unsigned int ETB:3;                     /**< \brief [18:16] External Time Base Select (rw) */
    unsigned int PTE:1;                     /**< \brief [19:19] Periodic Trigger Enable (rw) */
    unsigned int ETS:3;                     /**< \brief [22:20] External Trigger Select (rw) */
    unsigned int ETE:1;                     /**< \brief [23:23] External Trigger Enable (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5S_PGC_Bits;

/** \brief  Receive Buffer Register */
typedef struct _Ifx_PSI5S_RBUF_Bits
{
    unsigned int RD_VALUE:9;                /**< \brief [8:0] Receive Data Register Value (rh) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_PSI5S_RBUF_Bits;

/** \brief  Receiver Control Register A */
typedef struct _Ifx_PSI5S_RCRA_Bits
{
    unsigned int CRC0:1;                    /**< \brief [0:0] CRC or Parity Selection (rw) */
    unsigned int CRC1:1;                    /**< \brief [1:1] CRC or Parity Selection (rw) */
    unsigned int CRC2:1;                    /**< \brief [2:2] CRC or Parity Selection (rw) */
    unsigned int CRC3:1;                    /**< \brief [3:3] CRC or Parity Selection (rw) */
    unsigned int CRC4:1;                    /**< \brief [4:4] CRC or Parity Selection (rw) */
    unsigned int CRC5:1;                    /**< \brief [5:5] CRC or Parity Selection (rw) */
    unsigned int TSEN:1;                    /**< \brief [6:6] Time Stamp Enable (rw) */
    unsigned int TSP:1;                     /**< \brief [7:7] Time Stamp Select (rw) */
    unsigned int TSTS:1;                    /**< \brief [8:8] Time Stamp Trigger Select (rw) */
    unsigned int FIDS:1;                    /**< \brief [9:9] Frame ID Select (rw) */
    unsigned int WDMS:1;                    /**< \brief [10:10] Watch Dog Timer Mode Select (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int UFC0:2;                    /**< \brief [17:16] UART Frame Count per Packet Frame in Slot 0 (rw) */
    unsigned int UFC1:2;                    /**< \brief [19:18] UART Frame Count per Packet Frame in Slot 1 (rw) */
    unsigned int UFC2:2;                    /**< \brief [21:20] UART Frame Count per Packet Frame in Slot 2 (rw) */
    unsigned int UFC3:2;                    /**< \brief [23:22] UART Frame Count per Packet Frame in Slot 3 (rw) */
    unsigned int UFC4:2;                    /**< \brief [25:24] UART Frame Count per Packet Frame in Slot 4 (rw) */
    unsigned int UFC5:2;                    /**< \brief [27:26] UART Frame Count per Packet Frame in Slot 5 (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_PSI5S_RCRA_Bits;

/** \brief  Receiver Control Register B */
typedef struct _Ifx_PSI5S_RCRB_Bits
{
    unsigned int PDL0:5;                    /**< \brief [4:0] Payload Data Length (rw) */
    unsigned int PDL1:5;                    /**< \brief [9:5] Payload Data Length (rw) */
    unsigned int PDL2:5;                    /**< \brief [14:10] Payload Data Length (rw) */
    unsigned int PDL3:5;                    /**< \brief [19:15] Payload Data Length (rw) */
    unsigned int PDL4:5;                    /**< \brief [24:20] Payload Data Length (rw) */
    unsigned int PDL5:5;                    /**< \brief [29:25] Payload Data Length (rw) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_PSI5S_RCRB_Bits;

/** \brief  Receive Data Register */
typedef struct _Ifx_PSI5S_RDR_Bits
{
    unsigned int RD0:1;                     /**< \brief [0:0] PSI5 Receive Data (r) */
    unsigned int RD1:1;                     /**< \brief [1:1] PSI5 Receive Data (r) */
    unsigned int RD2:1;                     /**< \brief [2:2] PSI5 Receive Data (r) */
    unsigned int RD3:1;                     /**< \brief [3:3] PSI5 Receive Data (r) */
    unsigned int RD4:1;                     /**< \brief [4:4] PSI5 Receive Data (r) */
    unsigned int RD5:1;                     /**< \brief [5:5] PSI5 Receive Data (r) */
    unsigned int RD6:1;                     /**< \brief [6:6] PSI5 Receive Data (r) */
    unsigned int RD7:1;                     /**< \brief [7:7] PSI5 Receive Data (r) */
    unsigned int RD8:1;                     /**< \brief [8:8] PSI5 Receive Data (r) */
    unsigned int RD9:1;                     /**< \brief [9:9] PSI5 Receive Data (r) */
    unsigned int RD10:1;                    /**< \brief [10:10] PSI5 Receive Data (r) */
    unsigned int RD11:1;                    /**< \brief [11:11] PSI5 Receive Data (r) */
    unsigned int RD12:1;                    /**< \brief [12:12] PSI5 Receive Data (r) */
    unsigned int RD13:1;                    /**< \brief [13:13] PSI5 Receive Data (r) */
    unsigned int RD14:1;                    /**< \brief [14:14] PSI5 Receive Data (r) */
    unsigned int RD15:1;                    /**< \brief [15:15] PSI5 Receive Data (r) */
    unsigned int RD16:1;                    /**< \brief [16:16] PSI5 Receive Data (r) */
    unsigned int RD17:1;                    /**< \brief [17:17] PSI5 Receive Data (r) */
    unsigned int RD18:1;                    /**< \brief [18:18] PSI5 Receive Data (r) */
    unsigned int RD19:1;                    /**< \brief [19:19] PSI5 Receive Data (r) */
    unsigned int RD20:1;                    /**< \brief [20:20] PSI5 Receive Data (r) */
    unsigned int RD21:1;                    /**< \brief [21:21] PSI5 Receive Data (r) */
    unsigned int RD22:1;                    /**< \brief [22:22] PSI5 Receive Data (r) */
    unsigned int RD23:1;                    /**< \brief [23:23] PSI5 Receive Data (r) */
    unsigned int RD24:1;                    /**< \brief [24:24] PSI5 Receive Data (r) */
    unsigned int RD25:1;                    /**< \brief [25:25] PSI5 Receive Data (r) */
    unsigned int RD26:1;                    /**< \brief [26:26] PSI5 Receive Data (r) */
    unsigned int RD27:1;                    /**< \brief [27:27] PSI5 Receive Data (r) */
    unsigned int PFC:4;                     /**< \brief [31:28] Packet Frame Count (r) */
} Ifx_PSI5S_RDR_Bits;

/** \brief  Receive Status Register */
typedef struct _Ifx_PSI5S_RDS_Bits
{
    unsigned int XCRC0:1;                   /**< \brief [0:0] XCRC (r) */
    unsigned int XCRC1:1;                   /**< \brief [1:1] XCRC (r) */
    unsigned int XCRC2:1;                   /**< \brief [2:2] XCRC (r) */
    unsigned int XCRC3:1;                   /**< \brief [3:3] XCRC (r) */
    unsigned int XCRC4:1;                   /**< \brief [4:4] XCRC (r) */
    unsigned int XCRC5:1;                   /**< \brief [5:5] XCRC (r) */
    unsigned int XCRCI:1;                   /**< \brief [6:6] XCRC Error Flag (r) */
    unsigned int CRC0:1;                    /**< \brief [7:7] CRC (r) */
    unsigned int CRC1:1;                    /**< \brief [8:8] CRC (r) */
    unsigned int CRC2:1;                    /**< \brief [9:9] CRC (r) */
    unsigned int CRCI:1;                    /**< \brief [10:10] CRC Error Flag (r) */
    unsigned int ERR0:1;                    /**< \brief [11:11] Error signalling Flag 0 (r) */
    unsigned int ERR1:1;                    /**< \brief [12:12] Error signalling Flag 1 (r) */
    unsigned int HDI:1;                     /**< \brief [13:13] Header Error Signalled Flag (r) */
    unsigned int PE:1;                      /**< \brief [14:14] ASC Parity Error Flag (r) */
    unsigned int FE:1;                      /**< \brief [15:15] ASC Framing Error Flag (r) */
    unsigned int OE:1;                      /**< \brief [16:16] ASC Overrun Error Flag (r) */
    unsigned int TEI:1;                     /**< \brief [17:17] Time Error Flag (r) */
    unsigned int RBI:1;                     /**< \brief [18:18] Receive Buffer Overflow Flag (r) */
    unsigned int FID:3;                     /**< \brief [21:19] Frame ID (Frame Number) (r) */
    unsigned int CID:3;                     /**< \brief [24:22] Channel ID (Channel Number) (r) */
    unsigned int AFC:3;                     /**< \brief [27:25] Actual UART Frame Count (r) */
    unsigned int PFC:4;                     /**< \brief [31:28] Packet Frame Count (r) */
} Ifx_PSI5S_RDS_Bits;

/** \brief  Send Control Register */
typedef struct _Ifx_PSI5S_SCR_Bits
{
    unsigned int PLL:5;                     /**< \brief [4:0] Pay Load Length of Registers SDRx (rw) */
    unsigned int reserved_5:1;              /**< \brief \internal Reserved */
    unsigned int EPS:2;                     /**< \brief [7:6] Enhanced Protocol Selection (rw) */
    unsigned int BSC:1;                     /**< \brief [8:8] Bit Stuffing Control (rw) */
    unsigned int reserved_9:5;              /**< \brief \internal Reserved */
    unsigned int FLUS:1;                    /**< \brief [14:14] Flush SDRx (w) */
    unsigned int reserved_15:7;             /**< \brief \internal Reserved */
    unsigned int CRC:1;                     /**< \brief [22:22] CRC Generation Control (rw) */
    unsigned int STA:1;                     /**< \brief [23:23] Start Sequence Generation Control (rw) */
    unsigned int reserved_24:2;             /**< \brief \internal Reserved */
    unsigned int TPF:1;                     /**< \brief [26:26] Transmit in Progress Flag (r) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_PSI5S_SCR_Bits;

/** \brief  Send Data Register */
typedef struct _Ifx_PSI5S_SDR_Bits
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
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5S_SDR_Bits;

/** \brief  Target Address Register */
typedef struct _Ifx_PSI5S_TAR_Bits
{
    unsigned int reserved_0:2;              /**< \brief \internal Reserved */
    unsigned int TA:30;                     /**< \brief [31:2] Target Address (r) */
} Ifx_PSI5S_TAR_Bits;

/** \brief  Transmit Buffer Register */
typedef struct _Ifx_PSI5S_TBUF_Bits
{
    unsigned int TD_VALUE:9;                /**< \brief [8:0] Transmit Data Register Value (rw) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_PSI5S_TBUF_Bits;

/** \brief  Time Stamp Count Register A */
typedef struct _Ifx_PSI5S_TSCNTA_Bits
{
    unsigned int CTS:24;                    /**< \brief [23:0] Current Time Stamp for the Module (r) */
    unsigned int ETB:3;                     /**< \brief [26:24] External Time Base Select (rw) */
    unsigned int TBS:1;                     /**< \brief [27:27] Time Base Select (rw) */
    unsigned int TBEA:1;                    /**< \brief [28:28] Time Base Enable TSCNTA (rw) */
    unsigned int TBEB:1;                    /**< \brief [29:29] Time Base Enable TSCNTB (rw) */
    unsigned int CLRA:1;                    /**< \brief [30:30] Clear Time Stamp Counter A (w) */
    unsigned int CLRB:1;                    /**< \brief [31:31] Clear Time Stamp Counter B (w) */
} Ifx_PSI5S_TSCNTA_Bits;

/** \brief  Time Stamp Count Register B */
typedef struct _Ifx_PSI5S_TSCNTB_Bits
{
    unsigned int CTS:24;                    /**< \brief [23:0] Current Time Stamp for the Module (r) */
    unsigned int ETB:3;                     /**< \brief [26:24] External Time Base Select (rw) */
    unsigned int TBS:1;                     /**< \brief [27:27] Time Base Select (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_PSI5S_TSCNTB_Bits;

/** \brief  Capture Register */
typedef struct _Ifx_PSI5S_TSCR_Bits
{
    unsigned int TS:24;                     /**< \brief [23:0] Time Stamp (r) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5S_TSCR_Bits;

/** \brief  Time Stamp Mirror Register TSM */
typedef struct _Ifx_PSI5S_TSM_Bits
{
    unsigned int TS:24;                     /**< \brief [23:0] Time Stamp (r) */
    unsigned int reserved_24:4;             /**< \brief \internal Reserved */
    unsigned int PFC:4;                     /**< \brief [31:28] Packet Frame Count (r) */
} Ifx_PSI5S_TSM_Bits;

/** \brief  Watch Dog Timer Register */
typedef struct _Ifx_PSI5S_WDT_Bits
{
    unsigned int WDL:24;                    /**< \brief [23:0] Watch Dog Timer Limit (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_PSI5S_WDT_Bits;

/** \brief  Write Hardware Bits Control Register */
typedef struct _Ifx_PSI5S_WHBCON_Bits
{
    unsigned int reserved_0:4;              /**< \brief \internal Reserved */
    unsigned int CLRREN:1;                  /**< \brief [4:4] Clear Receiver Enable Bit (w) */
    unsigned int SETREN:1;                  /**< \brief [5:5] Set Receiver Enable Bit (w) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int CLRPE:1;                   /**< \brief [8:8] Clear Parity Error Flag (w) */
    unsigned int CLRFE:1;                   /**< \brief [9:9] Clear Framing Error Flag (w) */
    unsigned int CLROE:1;                   /**< \brief [10:10] Clear Overrun Error Flag (w) */
    unsigned int SETPE:1;                   /**< \brief [11:11] Set Parity Error Flag (w) */
    unsigned int SETFE:1;                   /**< \brief [12:12] Set Framing Error Flag (w) */
    unsigned int SETOE:1;                   /**< \brief [13:13] Set Overrun Error Flag (w) */
    unsigned int reserved_14:18;            /**< \brief \internal Reserved */
} Ifx_PSI5S_WHBCON_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Psi5s_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_ACCEN0_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_ACCEN1_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_ACCEN1;

/** \brief  Base Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_BAR_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_BAR;

/** \brief  Baud Rate Timer/Reload Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_BG_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5S_BG;

/** \brief  CPU Direct Write Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_CDW_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_CDW;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_CLC_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_CLC;

/** \brief  Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_CON_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_CON;

/** \brief  Channel Trigger Value Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_CTV_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_CTV;

/** \brief  Frame Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_FCNT_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_FCNT;

/** \brief  Fractional Divider for Output CLK Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_FDO_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_FDO;

/** \brief  PSI5-S Fractional Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_FDR_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_FDR;

/** \brief  Fractional Divider Register for Time Stamp */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_FDRT_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_FDRT;

/** \brief  Fractional Divider Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_FDV_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_FDV;

/** \brief  Global Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_GCR_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_GCR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_ID_Bits B;                    /**< \brief Bitfield access */
} Ifx_PSI5S_ID;

/** \brief  Interrupt Node Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INP_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_INP;

/** \brief  Interrupt Node Pointer G Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INPG_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_INPG;

/** \brief  Interrupt Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTCLR_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_INTCLR;

/** \brief  Interrupt Clear Register G */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTCLRG_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5S_INTCLRG;

/** \brief  Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTEN_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5S_INTEN;

/** \brief  Interrupt Enable Register G */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTENG_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_INTENG;

/** \brief  Interrupt Overview Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTOV_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5S_INTOV;

/** \brief  Interrupt Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTSET_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_INTSET;

/** \brief  Interrupt Set Register G */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTSETG_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5S_INTSETG;

/** \brief  Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTSTAT_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5S_INTSTAT;

/** \brief  Interrupt Status Register G */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_INTSTATG_Bits B;              /**< \brief Bitfield access */
} Ifx_PSI5S_INTSTATG;

/** \brief  Input and Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_IOCR_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_IOCR;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_KRST0_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5S_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_KRST1_Bits B;                 /**< \brief Bitfield access */
} Ifx_PSI5S_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_KRSTCLR_Bits B;               /**< \brief Bitfield access */
} Ifx_PSI5S_KRSTCLR;

/** \brief  Number of Frames Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_NFC_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_NFC;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_OCS_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_OCS;

/** \brief  Pulse Generation Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_PGC_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_PGC;

/** \brief  Receive Buffer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_RBUF_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_RBUF;

/** \brief  Receiver Control Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_RCRA_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_RCRA;

/** \brief  Receiver Control Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_RCRB_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_RCRB;

/** \brief  Receive Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_RDR_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_RDR;

/** \brief  Receive Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_RDS_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_RDS;

/** \brief  Send Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_SCR_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_SCR;

/** \brief  Send Data Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_SDR_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_SDR;

/** \brief  Target Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_TAR_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_TAR;

/** \brief  Transmit Buffer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_TBUF_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_TBUF;

/** \brief  Time Stamp Count Register A */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_TSCNTA_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_TSCNTA;

/** \brief  Time Stamp Count Register B */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_TSCNTB_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_TSCNTB;

/** \brief  Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_TSCR_Bits B;                  /**< \brief Bitfield access */
} Ifx_PSI5S_TSCR;

/** \brief  Time Stamp Mirror Register TSM */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_TSM_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_TSM;

/** \brief  Watch Dog Timer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_WDT_Bits B;                   /**< \brief Bitfield access */
} Ifx_PSI5S_WDT;

/** \brief  Write Hardware Bits Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PSI5S_WHBCON_Bits B;                /**< \brief Bitfield access */
} Ifx_PSI5S_WHBCON;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Psi5s_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  PSI5S object */
typedef volatile struct _Ifx_PSI5S
{
    Ifx_PSI5S_CLC CLC;                      /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_PSI5S_ID ID;                        /**< \brief 8, Module Identification Register */
    Ifx_PSI5S_FDR FDR;                      /**< \brief C, PSI5-S Fractional Divider Register */
    Ifx_PSI5S_FDRT FDRT;                    /**< \brief 10, Fractional Divider Register for Time Stamp */
    Ifx_PSI5S_TSCNTA TSCNTA;                /**< \brief 14, Time Stamp Count Register A */
    Ifx_PSI5S_TSCNTB TSCNTB;                /**< \brief 18, Time Stamp Count Register B */
    Ifx_PSI5S_GCR GCR;                      /**< \brief 1C, Global Control Register */
    Ifx_PSI5S_NFC NFC;                      /**< \brief 20, Number of Frames Control Register */
    Ifx_PSI5S_FCNT FCNT;                    /**< \brief 24, Frame Counter Register */
    Ifx_PSI5S_IOCR IOCR;                    /**< \brief 28, Input and Output Control Register */
    unsigned char reserved_2C[4];           /**< \brief 2C, \internal Reserved */
    Ifx_PSI5S_RCRA RCRA[8];                 /**< \brief 30, Receiver Control Register A */
    Ifx_PSI5S_RCRB RCRB[8];                 /**< \brief 50, Receiver Control Register B */
    Ifx_PSI5S_WDT WDT[8];                   /**< \brief 70, Watch Dog Timer Register */
    Ifx_PSI5S_TSCR TSCR[8];                 /**< \brief 90, Capture Register */
    Ifx_PSI5S_RDS RDS;                      /**< \brief B0, Receive Status Register */
    Ifx_PSI5S_RDR RDR;                      /**< \brief B4, Receive Data Register */
    Ifx_PSI5S_TSM TSM;                      /**< \brief B8, Time Stamp Mirror Register TSM */
    unsigned char reserved_BC[20];          /**< \brief BC, \internal Reserved */
    Ifx_PSI5S_TAR TAR;                      /**< \brief D0, Target Address Register */
    Ifx_PSI5S_BAR BAR;                      /**< \brief D4, Base Address Register */
    unsigned char reserved_D8[24];          /**< \brief D8, \internal Reserved */
    Ifx_PSI5S_PGC PGC[8];                   /**< \brief F0, Pulse Generation Control Register */
    Ifx_PSI5S_CTV CTV[8];                   /**< \brief 110, Channel Trigger Value Register */
    Ifx_PSI5S_SCR SCR[8];                   /**< \brief 130, Send Control Register */
    Ifx_PSI5S_SDR SDR[8];                   /**< \brief 150, Send Data Register */
    Ifx_PSI5S_CDW CDW;                      /**< \brief 170, CPU Direct Write Register */
    unsigned char reserved_174[156];        /**< \brief 174, \internal Reserved */
    Ifx_PSI5S_CON CON;                      /**< \brief 210, Control Register */
    Ifx_PSI5S_BG BG;                        /**< \brief 214, Baud Rate Timer/Reload Register */
    Ifx_PSI5S_FDV FDV;                      /**< \brief 218, Fractional Divider Register */
    Ifx_PSI5S_FDO FDO;                      /**< \brief 21C, Fractional Divider for Output CLK Register */
    Ifx_PSI5S_TBUF TBUF;                    /**< \brief 220, Transmit Buffer Register */
    Ifx_PSI5S_RBUF RBUF;                    /**< \brief 224, Receive Buffer Register */
    unsigned char reserved_228[40];         /**< \brief 228, \internal Reserved */
    Ifx_PSI5S_WHBCON WHBCON;                /**< \brief 250, Write Hardware Bits Control Register */
    unsigned char reserved_254[12];         /**< \brief 254, \internal Reserved */
    Ifx_PSI5S_INTSTAT INTSTAT[8];           /**< \brief 260, Interrupt Status Register */
    Ifx_PSI5S_INTSET INTSET[8];             /**< \brief 280, Interrupt Set Register */
    Ifx_PSI5S_INTCLR INTCLR[8];             /**< \brief 2A0, Interrupt Clear Register */
    Ifx_PSI5S_INTEN INTEN[8];               /**< \brief 2C0, Interrupt Enable Register */
    Ifx_PSI5S_INP INP[8];                   /**< \brief 2E0, Interrupt Node Pointer Register */
    Ifx_PSI5S_INTOV INTOV;                  /**< \brief 300, Interrupt Overview Register */
    Ifx_PSI5S_INTSTATG INTSTATG;            /**< \brief 304, Interrupt Status Register G */
    Ifx_PSI5S_INTSETG INTSETG;              /**< \brief 308, Interrupt Set Register G */
    Ifx_PSI5S_INTCLRG INTCLRG;              /**< \brief 30C, Interrupt Clear Register G */
    Ifx_PSI5S_INTENG INTENG;                /**< \brief 310, Interrupt Enable Register G */
    Ifx_PSI5S_INPG INPG;                    /**< \brief 314, Interrupt Node Pointer G Register */
    unsigned char reserved_318[180];        /**< \brief 318, \internal Reserved */
    Ifx_PSI5S_OCS OCS;                      /**< \brief 3CC, OCDS Control and Status */
    Ifx_PSI5S_ACCEN0 ACCEN0;                /**< \brief 3D0, Access Enable Register 0 */
    Ifx_PSI5S_ACCEN1 ACCEN1;                /**< \brief 3D4, Access Enable Register 1 */
    Ifx_PSI5S_KRST0 KRST0;                  /**< \brief 3D8, Kernel Reset Register 0 */
    Ifx_PSI5S_KRST1 KRST1;                  /**< \brief 3DC, Kernel Reset Register 1 */
    Ifx_PSI5S_KRSTCLR KRSTCLR;              /**< \brief 3E0, Kernel Reset Status Clear Register */
    unsigned char reserved_3E4[3100];       /**< \brief 3E4, \internal Reserved */
} Ifx_PSI5S;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXPSI5S_REGDEF_H */
