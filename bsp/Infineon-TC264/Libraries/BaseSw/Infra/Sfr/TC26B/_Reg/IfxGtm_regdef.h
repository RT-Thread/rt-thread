/**
 * \file IfxGtm_regdef.h
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
 * \defgroup IfxLld_Gtm Gtm
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Gtm_Bitfields Bitfields
 * \ingroup IfxLld_Gtm
 * 
 * \defgroup IfxLld_Gtm_union Union
 * \ingroup IfxLld_Gtm
 * 
 * \defgroup IfxLld_Gtm_struct Struct
 * \ingroup IfxLld_Gtm
 * 
 */
#ifndef IFXGTM_REGDEF_H
#define IFXGTM_REGDEF_H 1
/******************************************************************************/
#if defined (__TASKING__)
#pragma warning 586
#endif
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Gtm_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_GTM_ACCEN0_Bits
{
    Ifx_Strict_32Bit EN0:1;                 /**< \brief [0:0] Access Enable for Master TAG ID 0 (rw) */
    Ifx_Strict_32Bit EN1:1;                 /**< \brief [1:1] Access Enable for Master TAG ID 1 (rw) */
    Ifx_Strict_32Bit EN2:1;                 /**< \brief [2:2] Access Enable for Master TAG ID 2 (rw) */
    Ifx_Strict_32Bit EN3:1;                 /**< \brief [3:3] Access Enable for Master TAG ID 3 (rw) */
    Ifx_Strict_32Bit EN4:1;                 /**< \brief [4:4] Access Enable for Master TAG ID 4 (rw) */
    Ifx_Strict_32Bit EN5:1;                 /**< \brief [5:5] Access Enable for Master TAG ID 5 (rw) */
    Ifx_Strict_32Bit EN6:1;                 /**< \brief [6:6] Access Enable for Master TAG ID 6 (rw) */
    Ifx_Strict_32Bit EN7:1;                 /**< \brief [7:7] Access Enable for Master TAG ID 7 (rw) */
    Ifx_Strict_32Bit EN8:1;                 /**< \brief [8:8] Access Enable for Master TAG ID 8 (rw) */
    Ifx_Strict_32Bit EN9:1;                 /**< \brief [9:9] Access Enable for Master TAG ID 9 (rw) */
    Ifx_Strict_32Bit EN10:1;                /**< \brief [10:10] Access Enable for Master TAG ID 10 (rw) */
    Ifx_Strict_32Bit EN11:1;                /**< \brief [11:11] Access Enable for Master TAG ID 11 (rw) */
    Ifx_Strict_32Bit EN12:1;                /**< \brief [12:12] Access Enable for Master TAG ID 12 (rw) */
    Ifx_Strict_32Bit EN13:1;                /**< \brief [13:13] Access Enable for Master TAG ID 13 (rw) */
    Ifx_Strict_32Bit EN14:1;                /**< \brief [14:14] Access Enable for Master TAG ID 14 (rw) */
    Ifx_Strict_32Bit EN15:1;                /**< \brief [15:15] Access Enable for Master TAG ID 15 (rw) */
    Ifx_Strict_32Bit EN16:1;                /**< \brief [16:16] Access Enable for Master TAG ID 16 (rw) */
    Ifx_Strict_32Bit EN17:1;                /**< \brief [17:17] Access Enable for Master TAG ID 17 (rw) */
    Ifx_Strict_32Bit EN18:1;                /**< \brief [18:18] Access Enable for Master TAG ID 18 (rw) */
    Ifx_Strict_32Bit EN19:1;                /**< \brief [19:19] Access Enable for Master TAG ID 19 (rw) */
    Ifx_Strict_32Bit EN20:1;                /**< \brief [20:20] Access Enable for Master TAG ID 20 (rw) */
    Ifx_Strict_32Bit EN21:1;                /**< \brief [21:21] Access Enable for Master TAG ID 21 (rw) */
    Ifx_Strict_32Bit EN22:1;                /**< \brief [22:22] Access Enable for Master TAG ID 22 (rw) */
    Ifx_Strict_32Bit EN23:1;                /**< \brief [23:23] Access Enable for Master TAG ID 23 (rw) */
    Ifx_Strict_32Bit EN24:1;                /**< \brief [24:24] Access Enable for Master TAG ID 24 (rw) */
    Ifx_Strict_32Bit EN25:1;                /**< \brief [25:25] Access Enable for Master TAG ID 25 (rw) */
    Ifx_Strict_32Bit EN26:1;                /**< \brief [26:26] Access Enable for Master TAG ID 26 (rw) */
    Ifx_Strict_32Bit EN27:1;                /**< \brief [27:27] Access Enable for Master TAG ID 27 (rw) */
    Ifx_Strict_32Bit EN28:1;                /**< \brief [28:28] Access Enable for Master TAG ID 28 (rw) */
    Ifx_Strict_32Bit EN29:1;                /**< \brief [29:29] Access Enable for Master TAG ID 29 (rw) */
    Ifx_Strict_32Bit EN30:1;                /**< \brief [30:30] Access Enable for Master TAG ID 30 (rw) */
    Ifx_Strict_32Bit EN31:1;                /**< \brief [31:31] Access Enable for Master TAG ID 31 (rw) */
} Ifx_GTM_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_GTM_ACCEN1_Bits
{
    Ifx_Strict_32Bit reserved_0:32;         /**< \brief \internal Reserved */
} Ifx_GTM_ACCEN1_Bits;

/** \brief  ADC Trigger 0 Output Select 0 Register */
typedef struct _Ifx_GTM_ADCTRIG0OUT0_Bits
{
    Ifx_Strict_32Bit SEL0:4;                /**< \brief [3:0] Output Selection for ADC0 GTM connection (rw) */
    Ifx_Strict_32Bit SEL1:4;                /**< \brief [7:4] Output Selection for ADC1 GTM connection (rw) */
    Ifx_Strict_32Bit SEL2:4;                /**< \brief [11:8] Output Selection for ADC2 GTM connection (rw) */
    Ifx_Strict_32Bit SEL3:4;                /**< \brief [15:12] Output Selection for ADC3 GTM connection (rw) */
    Ifx_Strict_32Bit SEL4:4;                /**< \brief [19:16] Output Selection for ADC4 GTM connection (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_ADCTRIG0OUT0_Bits;

/** \brief  ADC Trigger 1 Output Select 0 Register */
typedef struct _Ifx_GTM_ADCTRIG1OUT0_Bits
{
    Ifx_Strict_32Bit SEL0:4;                /**< \brief [3:0] Output Selection for ADC0 GTM connection (rw) */
    Ifx_Strict_32Bit SEL1:4;                /**< \brief [7:4] Output Selection for ADC1 GTM connection (rw) */
    Ifx_Strict_32Bit SEL2:4;                /**< \brief [11:8] Output Selection for ADC2 GTM connection (rw) */
    Ifx_Strict_32Bit SEL3:4;                /**< \brief [15:12] Output Selection for ADC3 GTM connection (rw) */
    Ifx_Strict_32Bit SEL4:4;                /**< \brief [19:16] Output Selection for ADC4 GTM connection (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_ADCTRIG1OUT0_Bits;

/** \brief  GTM AEI Timeout Exception Address Register */
typedef struct _Ifx_GTM_AEI_ADDR_XPT_Bits
{
    Ifx_Strict_32Bit TO_ADDR:20;            /**< \brief [19:0] AEI Timeout address (r) */
    Ifx_Strict_32Bit TO_W1R0:1;             /**< \brief [20:20] AEI Timeout Read/Write flag (r) */
    Ifx_Strict_32Bit reserved_21:11;        /**< \brief \internal Reserved */
} Ifx_GTM_AEI_ADDR_XPT_Bits;

/** \brief  AFD0 FIFO0 Channel Buffer Access Register */
typedef struct _Ifx_GTM_AFD_CH_BUF_ACC_Bits
{
    Ifx_Strict_32Bit DATA:29;               /**< \brief [28:0] Read/write data from/to FIFO (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_AFD_CH_BUF_ACC_Bits;

/** \brief  ARU Access Register */
typedef struct _Ifx_GTM_ARU_ARU_ACCESS_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RREQ:1;                /**< \brief [12:12] Initiate read request (rwh) */
    Ifx_Strict_32Bit WREQ:1;                /**< \brief [13:13] Initiate write request (rwh) */
    Ifx_Strict_32Bit reserved_14:18;        /**< \brief \internal Reserved */
} Ifx_GTM_ARU_ARU_ACCESS_Bits;

/** \brief  ARU Access Register Upper Data Word */
typedef struct _Ifx_GTM_ARU_DATA_H_Bits
{
    Ifx_Strict_32Bit DATA:29;               /**< \brief [28:0] Upper ARU data word (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DATA_H_Bits;

/** \brief  ARU Access Register Lower Data Word */
typedef struct _Ifx_GTM_ARU_DATA_L_Bits
{
    Ifx_Strict_32Bit DATA:29;               /**< \brief [28:0] Lower ARU data word (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DATA_L_Bits;

/** \brief  Debug Access Channel 0 */
typedef struct _Ifx_GTM_ARU_DBG_ACCESS0_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] ARU debugging address (rw) */
    Ifx_Strict_32Bit reserved_9:23;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DBG_ACCESS0_Bits;

/** \brief  Debug Access Channel 0 */
typedef struct _Ifx_GTM_ARU_DBG_ACCESS1_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] ARU debugging address (rw) */
    Ifx_Strict_32Bit reserved_9:23;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DBG_ACCESS1_Bits;

/** \brief  Debug Access 0 Transfer Register Upper Data Word */
typedef struct _Ifx_GTM_ARU_DBG_DATA0_H_Bits
{
    Ifx_Strict_32Bit DATA:29;               /**< \brief [28:0] Upper debug data word (r) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DBG_DATA0_H_Bits;

/** \brief  Debug Access 0 Transfer Register Lower Data Word */
typedef struct _Ifx_GTM_ARU_DBG_DATA0_L_Bits
{
    Ifx_Strict_32Bit DATA:29;               /**< \brief [28:0] Lower debug data word (r) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DBG_DATA0_L_Bits;

/** \brief  Debug Access 1 Transfer Register Upper Data Word */
typedef struct _Ifx_GTM_ARU_DBG_DATA1_H_Bits
{
    Ifx_Strict_32Bit DATA:29;               /**< \brief [28:0] Upper debug data word (r) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DBG_DATA1_H_Bits;

/** \brief  Debug Access 1 Transfer Register Lower Data Word */
typedef struct _Ifx_GTM_ARU_DBG_DATA1_L_Bits
{
    Ifx_Strict_32Bit DATA:29;               /**< \brief [28:0] Lower debug data word (r) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_DBG_DATA1_L_Bits;

/** \brief  ARU Interrupt Enable Register */
typedef struct _Ifx_GTM_ARU_IRQ_EN_Bits
{
    Ifx_Strict_32Bit NEW_DATA0_IRQ_EN:1;    /**< \brief [0:0] ARU_NEW_DATA0_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit NEW_DATA1_IRQ_EN:1;    /**< \brief [1:1] ARU_NEW_DATA1_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit ACC_ACK_IRQ_EN:1;      /**< \brief [2:2] ACC_ACK_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_IRQ_EN_Bits;

/** \brief  ARU_NEW_DATA_IRQ Forcing Interrupt Register */
typedef struct _Ifx_GTM_ARU_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_NEW_DATA0:1;       /**< \brief [0:0] Trigger new data 0 interrupt (w) */
    Ifx_Strict_32Bit TRG_NEW_DATA:1;        /**< \brief [1:1] 1 Trigger new data 1 interrupt (w) */
    Ifx_Strict_32Bit TRG_ACC_ACK:1;         /**< \brief [2:2] Trigger ACC_ACK interrupt (w) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_IRQ_FORCINT_Bits;

/** \brief  IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_ARU_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_IRQ_MODE_Bits;

/** \brief  ARU Interrupt Notification Register */
typedef struct _Ifx_GTM_ARU_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit NEW_DATA0:1;           /**< \brief [0:0] Data was transferred for addr ARU_DBG_ACCESS0 (rwh) */
    Ifx_Strict_32Bit NEW_DATA1:1;           /**< \brief [1:1] Data was transferred for addr ARU_DBG_ACCESS1 (rwh) */
    Ifx_Strict_32Bit ACC_ACK:1;             /**< \brief [2:2] AEI to ARU access finished, on read access data are valid (rwh) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_ARU_IRQ_NOTIFY_Bits;

/** \brief  TOM TGC0 Action Time Base Register */
typedef struct _Ifx_GTM_ATOM_AGC_ACT_TB_Bits
{
    Ifx_Strict_32Bit ACT_TB:24;             /**< \brief [23:0] Time base value (rw) */
    Ifx_Strict_32Bit TB_TRIG:1;             /**< \brief [24:24] Set trigger request (rwh) */
    Ifx_Strict_32Bit TBU_SEL:2;             /**< \brief [26:25] Selection of time base used for comparison (rw) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_AGC_ACT_TB_Bits;

/** \brief  ATOM AGC Enable/Disable Control Register */
typedef struct _Ifx_GTM_ATOM_AGC_ENDIS_CTRL_Bits
{
    Ifx_Strict_32Bit ENDIS_CTRL0:2;         /**< \brief [1:0] (A)TOM channel 0 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL1:2;         /**< \brief [3:2] (A)TOM channel 1 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL2:2;         /**< \brief [5:4] (A)TOM channel 2 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL3:2;         /**< \brief [7:6] (A)TOM channel 3 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL4:2;         /**< \brief [9:8] (A)TOM channel 4 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL5:2;         /**< \brief [11:10] (A)TOM channel 5 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL6:2;         /**< \brief [13:12] (A)TOM channel 6 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL7:2;         /**< \brief [15:14] (A)TOM channel 7 enable/disable update value (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_AGC_ENDIS_CTRL_Bits;

/** \brief  ATOM AGC Enable/Disable Status Register */
typedef struct _Ifx_GTM_ATOM_AGC_ENDIS_STAT_Bits
{
    Ifx_Strict_32Bit ENDIS_STAT0:2;         /**< \brief [1:0] (A)TOM channel 0 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT1:2;         /**< \brief [3:2] (A)TOM channel 1 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT2:2;         /**< \brief [5:4] (A)TOM channel 2 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT3:2;         /**< \brief [7:6] (A)TOM channel 3 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT4:2;         /**< \brief [9:8] (A)TOM channel 4 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT5:2;         /**< \brief [11:10] (A)TOM channel 5 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT6:2;         /**< \brief [13:12] (A)TOM channel 6 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT7:2;         /**< \brief [15:14] (A)TOM channel 7 enable/disable (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_AGC_ENDIS_STAT_Bits;

/** \brief  ATOM AGC Force Update Control Register */
typedef struct _Ifx_GTM_ATOM_AGC_FUPD_CTRL_Bits
{
    Ifx_Strict_32Bit FUPD_CTRL0:2;          /**< \brief [1:0] Force update of (A)TOM channel 0 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL1:2;          /**< \brief [3:2] Force update of (A)TOM channel 1 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL2:2;          /**< \brief [5:4] Force update of (A)TOM channel 2 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL3:2;          /**< \brief [7:6] Force update of (A)TOM channel 3 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL4:2;          /**< \brief [9:8] Force update of (A)TOM channel 4 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL5:2;          /**< \brief [11:10] Force update of (A)TOM channel 5 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL6:2;          /**< \brief [13:12] Force update of (A)TOM channel 6 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL7:2;          /**< \brief [15:14] Force update of (A)TOM channel 7 operation registers (rw) */
    Ifx_Strict_32Bit RSTCN0_CH0:2;          /**< \brief [17:16] Reset CN0 of channel 0 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH1:2;          /**< \brief [19:18] Reset CN0 of channel 1 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH2:2;          /**< \brief [21:20] Reset CN0 of channel 2 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH3:2;          /**< \brief [23:22] Reset CN0 of channel 3 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH4:2;          /**< \brief [25:24] Reset CN0 of channel 4 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH5:2;          /**< \brief [27:26] Reset CN0 of channel 5 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH6:2;          /**< \brief [29:28] Reset CN0 of channel 6 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH7:2;          /**< \brief [31:30] Reset CN0 of channel 7 on force update event (rw) */
} Ifx_GTM_ATOM_AGC_FUPD_CTRL_Bits;

/** \brief  ATOM AGC Global control register */
typedef struct _Ifx_GTM_ATOM_AGC_GLB_CTRL_Bits
{
    Ifx_Strict_32Bit HOST_TRIG:1;           /**< \brief [0:0] Trigger request signal (see AGC) to update the register ENDIS_STAT and OUTEN_STAT (w) */
    Ifx_Strict_32Bit reserved_1:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RST_CH0:1;             /**< \brief [8:8] Software reset of channel 0 (w) */
    Ifx_Strict_32Bit RST_CH1:1;             /**< \brief [9:9] Software reset of channel 1 (w) */
    Ifx_Strict_32Bit RST_CH2:1;             /**< \brief [10:10] Software reset of channel 2 (w) */
    Ifx_Strict_32Bit RST_CH3:1;             /**< \brief [11:11] Software reset of channel 3 (w) */
    Ifx_Strict_32Bit RST_CH4:1;             /**< \brief [12:12] Software reset of channel 4 (w) */
    Ifx_Strict_32Bit RST_CH5:1;             /**< \brief [13:13] Software reset of channel 5 (w) */
    Ifx_Strict_32Bit RST_CH6:1;             /**< \brief [14:14] Software reset of channel 6 (w) */
    Ifx_Strict_32Bit RST_CH7:1;             /**< \brief [15:15] Software reset of channel 7 (w) */
    Ifx_Strict_32Bit UPEN_CTRL0:2;          /**< \brief [17:16] ATOM channel 0 enable update of register CM0, CM1 and CLK_SRC from SR0, SR1 and CLK_SRC_SR (rw) */
    Ifx_Strict_32Bit UPEN_CTRL1:2;          /**< \brief [19:18] ATOM channel 1 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL2:2;          /**< \brief [21:20] ATOM channel 2 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL3:2;          /**< \brief [23:22] ATOM channel 3 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL4:2;          /**< \brief [25:24] ATOM channel 4 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL5:2;          /**< \brief [27:26] ATOM channel 5 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL6:2;          /**< \brief [29:28] ATOM channel 6 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL7:2;          /**< \brief [31:30] ATOM channel 7 enable update of register CM0, CM1 and CLK_SRC (rw) */
} Ifx_GTM_ATOM_AGC_GLB_CTRL_Bits;

/** \brief  ATOM AGC Internal Trigger Control Register */
typedef struct _Ifx_GTM_ATOM_AGC_INT_TRIG_Bits
{
    Ifx_Strict_32Bit INT_TRIG0:2;           /**< \brief [1:0] Select input signal TRIG_0 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG1:2;           /**< \brief [3:2] Select input signal TRIG_1 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG2:2;           /**< \brief [5:4] Select input signal TRIG_2 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG3:2;           /**< \brief [7:6] Select input signal TRIG_3 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG4:2;           /**< \brief [9:8] Select input signal TRIG_4 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG5:2;           /**< \brief [11:10] Select input signal TRIG_5 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG6:2;           /**< \brief [13:12] Select input signal TRIG_6 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG7:2;           /**< \brief [15:14] Select input signal TRIG_7 as a trigger source (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_AGC_INT_TRIG_Bits;

/** \brief  ATOM AGC Output Enable Control Register */
typedef struct _Ifx_GTM_ATOM_AGC_OUTEN_CTRL_Bits
{
    Ifx_Strict_32Bit OUTEN_CTRL0:2;         /**< \brief [1:0] Output (A)TOM_OUT(0) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL1:2;         /**< \brief [3:2] Output (A)TOM_OUT(1)enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL2:2;         /**< \brief [5:4] Output (A)TOM_OUT(2) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL3:2;         /**< \brief [7:6] Output (A)TOM_OUT(3) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL4:2;         /**< \brief [9:8] Output (A)TOM_OUT(4) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL5:2;         /**< \brief [11:10] Output (A)TOM_OUT(5) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL6:2;         /**< \brief [13:12] Output (A)TOM_OUT(6) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL7:2;         /**< \brief [15:14] Output (A)TOM_OUT(7) enable/disable update value (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_AGC_OUTEN_CTRL_Bits;

/** \brief  ATOM AGC Output Enable Status Register */
typedef struct _Ifx_GTM_ATOM_AGC_OUTEN_STAT_Bits
{
    Ifx_Strict_32Bit OUTEN_STAT0:2;         /**< \brief [1:0] Control/status of output (A)TOM_OUT(0) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT1:2;         /**< \brief [3:2] Control/status of output (A)TOM_OUT(1) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT2:2;         /**< \brief [5:4] Control/status of output (A)TOM_OUT(2) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT3:2;         /**< \brief [7:6] Control/status of output (A)TOM_OUT(3) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT4:2;         /**< \brief [9:8] Control/status of output (A)TOM_OUT(4) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT5:2;         /**< \brief [11:10] Control/status of output (A)TOM_OUT(5) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT6:2;         /**< \brief [13:12] Control/status of output (A)TOM_OUT(6) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT7:2;         /**< \brief [15:14] Control/status of output (A)TOM_OUT(7) (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_AGC_OUTEN_STAT_Bits;

/** \brief  ATOM Channel CCU0 Compare Register */
typedef struct _Ifx_GTM_ATOM_CH_CM0_Bits
{
    Ifx_Strict_32Bit CM0:24;                /**< \brief [23:0] ATOM CCU0 compare register (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_CM0_Bits;

/** \brief  ATOM Channel CCU1 Compare Register */
typedef struct _Ifx_GTM_ATOM_CH_CM1_Bits
{
    Ifx_Strict_32Bit CM1:24;                /**< \brief [23:0] ATOM CCU1 compare register (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_CM1_Bits;

/** \brief  ATOM Channel CCU0 Counter Register */
typedef struct _Ifx_GTM_ATOM_CH_CN0_Bits
{
    Ifx_Strict_32Bit CN0:24;                /**< \brief [23:0] ATOM CCU0 counter register (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_CN0_Bits;

/** \brief  ATOM Channel Control Register */
typedef struct _Ifx_GTM_ATOM_CH_CTRL_Bits
{
    Ifx_Strict_32Bit MODE:2;                /**< \brief [1:0] ATOM channel mode select (rw) */
    Ifx_Strict_32Bit TB12_SEL:1;            /**< \brief [2:2] Select time base value TBU_TS1 or TBU_TS2. (rw) */
    Ifx_Strict_32Bit ARU_EN:1;              /**< \brief [3:3] ARU Input stream enable (rw) */
    Ifx_Strict_32Bit ACB:5;                 /**< \brief [8:4] ATOM Mode control bits (rw) */
    Ifx_Strict_32Bit CMP_CTRL:1;            /**< \brief [9:9] CCUx compare strategy select (rw) */
    Ifx_Strict_32Bit reserved_10:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SL:1;                  /**< \brief [11:11] Initial signal level (rw) */
    Ifx_Strict_32Bit CLK_SRC:3;             /**< \brief [14:12] actual CMU clock source (SOMS)/ shadow register for CMU clock source (SOMP) (rw) */
    Ifx_Strict_32Bit reserved_15:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WR_REQ:1;              /**< \brief [16:16] CPU Write request bit for late compare register update (rw) */
    Ifx_Strict_32Bit reserved_17:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RST_CCU0:1;            /**< \brief [20:20] Reset source of CCU0 (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TRIGOUT:1;             /**< \brief [24:24] Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx. (rw) */
    Ifx_Strict_32Bit SLA:1;                 /**< \brief [25:25] Serve last ARU communication strategy (rw) */
    Ifx_Strict_32Bit OSM:1;                 /**< \brief [26:26] One-shot mode (rw) */
    Ifx_Strict_32Bit ABM:1;                 /**< \brief [27:27] ARU blocking mode (rw) */
    Ifx_Strict_32Bit reserved_28:4;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_CTRL_Bits;

/** \brief  ATOM Channel Interrupt Enable Register */
typedef struct _Ifx_GTM_ATOM_CH_IRQ_EN_Bits
{
    Ifx_Strict_32Bit CCU0TC_IRQ_EN:1;       /**< \brief [0:0] ATOM_CCU0TC_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit CCU1TC_IRQ_EN:1;       /**< \brief [1:1] ATOM_CCU1TC_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_IRQ_EN_Bits;

/** \brief  ATOM Channel Software Interrupt Generation Register */
typedef struct _Ifx_GTM_ATOM_CH_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_CCU0TC:1;          /**< \brief [0:0] Trigger ATOM_CCU0TC_IRQ interrupt by software (w) */
    Ifx_Strict_32Bit TRG_CCU1TC:1;          /**< \brief [1:1] Trigger ATOM_CCU1TC_IRQ interrupt by software (w) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_IRQ_FORCINT_Bits;

/** \brief  ATOM IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_ATOM_CH_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_IRQ_MODE_Bits;

/** \brief  ATOM Channel Interrupt Notification Register */
typedef struct _Ifx_GTM_ATOM_CH_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit CCU0TC:1;              /**< \brief [0:0] CCU0 Trigger condition interrupt for channel x (rwh) */
    Ifx_Strict_32Bit CCU1TC:1;              /**< \brief [1:1] CCU1 Trigger condition interrupt for channel x (rwh) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_IRQ_NOTIFY_Bits;

/** \brief  ATOM Channel ARU Read Address Register */
typedef struct _Ifx_GTM_ATOM_CH_RDADDR_Bits
{
    Ifx_Strict_32Bit RDADDR0:9;             /**< \brief [8:0] ARU Read address 0 (rw) */
    Ifx_Strict_32Bit reserved_9:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RDADDR1:9;             /**< \brief [24:16] ARU Read address 1 (rw) */
    Ifx_Strict_32Bit reserved_25:7;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_RDADDR_Bits;

/** \brief  ATOM Channel Control in SOMC mode Register */
typedef struct _Ifx_GTM_ATOM_CH_SOMC_Bits
{
    Ifx_Strict_32Bit MODE:2;                /**< \brief [1:0] ATOM channel mode select (rw) */
    Ifx_Strict_32Bit TB12_SEL:1;            /**< \brief [2:2] Select time base value TBU_TS1 or TBU_TS2. (rw) */
    Ifx_Strict_32Bit ARU_EN:1;              /**< \brief [3:3] ARU Input stream enable (rw) */
    Ifx_Strict_32Bit ACB10:2;               /**< \brief [5:4] Signal level control bits (rw) */
    Ifx_Strict_32Bit ACB42:3;               /**< \brief [8:6] ATOM control bits ACB(4), ACB(3), ACB(2) (rw) */
    Ifx_Strict_32Bit CMP_CTRL:1;            /**< \brief [9:9] CCUx compare strategy select (rw) */
    Ifx_Strict_32Bit reserved_10:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SL:1;                  /**< \brief [11:11] Initial signal level after channel enable (rw) */
    Ifx_Strict_32Bit reserved_12:4;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WR_REQ:1;              /**< \brief [16:16] CPU write request bit (rw) */
    Ifx_Strict_32Bit reserved_17:7;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TRIGOUT:1;             /**< \brief [24:24] Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx (rw) */
    Ifx_Strict_32Bit SLA:1;                 /**< \brief [25:25] Serve last ARU communication strategy (rw) */
    Ifx_Strict_32Bit reserved_26:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ABM:1;                 /**< \brief [27:27] ARU blocking mode (rw) */
    Ifx_Strict_32Bit reserved_28:4;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_SOMC_Bits;

/** \brief  ATOM Channel Control in SOMI mode Register */
typedef struct _Ifx_GTM_ATOM_CH_SOMI_Bits
{
    Ifx_Strict_32Bit MODE:2;                /**< \brief [1:0] ATOM channel mode select (rw) */
    Ifx_Strict_32Bit reserved_2:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ARU_EN:1;              /**< \brief [3:3] ARU Input stream enable (rw) */
    Ifx_Strict_32Bit ACB0:1;                /**< \brief [4:4] ACB bit 0 (rw) */
    Ifx_Strict_32Bit reserved_5:6;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SL:1;                  /**< \brief [11:11] Initial signal level after channel is enabled (rw) */
    Ifx_Strict_32Bit reserved_12:20;        /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_SOMI_Bits;

/** \brief  ATOM Channel Control in SOMP mode Register */
typedef struct _Ifx_GTM_ATOM_CH_SOMP_Bits
{
    Ifx_Strict_32Bit MODE:2;                /**< \brief [1:0] ATOM channel mode select (rw) */
    Ifx_Strict_32Bit reserved_2:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ARU_EN:1;              /**< \brief [3:3] ARU Input stream enable (rw) */
    Ifx_Strict_32Bit ADL:2;                 /**< \brief [5:4] ARU data select for SOMP (r) */
    Ifx_Strict_32Bit reserved_6:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SL:1;                  /**< \brief [11:11] Signal level for pulse of PWM (rw) */
    Ifx_Strict_32Bit CLK_SRC_SR:3;          /**< \brief [14:12] Shadow register for CMU clock source register CLK_SRC (rw) */
    Ifx_Strict_32Bit reserved_15:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RST_CCU0:1;            /**< \brief [20:20] Reset source of CCU0 (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TRIGOUT:1;             /**< \brief [24:24] Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx. (rw) */
    Ifx_Strict_32Bit reserved_25:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit OSM:1;                 /**< \brief [26:26] One-shot mode (rw) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_SOMP_Bits;

/** \brief  ATOM Channel Control in SOMS mode Register */
typedef struct _Ifx_GTM_ATOM_CH_SOMS_Bits
{
    Ifx_Strict_32Bit MODE:2;                /**< \brief [1:0] ATOM channel mode select (rw) */
    Ifx_Strict_32Bit reserved_2:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ARU_EN:1;              /**< \brief [3:3] ARU Input stream enable (rw) */
    Ifx_Strict_32Bit ACB0:1;                /**< \brief [4:4] Shift direction for CM1 register (rw) */
    Ifx_Strict_32Bit reserved_5:6;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SL:1;                  /**< \brief [11:11] Defines signal level when channel and output is disable (rw) */
    Ifx_Strict_32Bit CLK_SRC:3;             /**< \brief [14:12] Shift frequency select for channel (rw) */
    Ifx_Strict_32Bit reserved_15:11;        /**< \brief \internal Reserved */
    Ifx_Strict_32Bit OSM:1;                 /**< \brief [26:26] One-shot mode (rw) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_SOMS_Bits;

/** \brief  ATOM Channel CCU0 Compare Shadow Register */
typedef struct _Ifx_GTM_ATOM_CH_SR0_Bits
{
    Ifx_Strict_32Bit SR0:24;                /**< \brief [23:0] ATOM channel x shadow register SR0 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_SR0_Bits;

/** \brief  ATOM Channel CCU1 Compare Shadow Register */
typedef struct _Ifx_GTM_ATOM_CH_SR1_Bits
{
    Ifx_Strict_32Bit SR1:24;                /**< \brief [23:0] ATOM channel x shadow register SR0 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_SR1_Bits;

/** \brief  ATOM Channel Status Register */
typedef struct _Ifx_GTM_ATOM_CH_STAT_Bits
{
    Ifx_Strict_32Bit OL:1;                  /**< \brief [0:0] Actual output signal level of ATOM_CHx_OUT (r) */
    Ifx_Strict_32Bit reserved_1:15;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ACBI:5;                /**< \brief [20:16] ATOM Mode control bits received through ARU (r) */
    Ifx_Strict_32Bit DV:1;                  /**< \brief [21:21] Valid ARU Data stored in compare registers (r) */
    Ifx_Strict_32Bit WRF:1;                 /**< \brief [22:22] Write request of CPU failed for late update (rwh) */
    Ifx_Strict_32Bit reserved_23:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ACBO:5;                /**< \brief [28:24] ATOM Internal status bits (r) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_ATOM_CH_STAT_Bits;

/** \brief  BRC Error Interrupt Enable Register */
typedef struct _Ifx_GTM_BRC_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit DEST_ERR_EN:1;         /**< \brief [0:0] BRC_DEST_ERR_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN0:1;             /**< \brief [1:1] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN1:1;             /**< \brief [2:2] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN2:1;             /**< \brief [3:3] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN3:1;             /**< \brief [4:4] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN4:1;             /**< \brief [5:5] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN5:1;             /**< \brief [6:6] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN6:1;             /**< \brief [7:7] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN7:1;             /**< \brief [8:8] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN8:1;             /**< \brief [9:9] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN9:1;             /**< \brief [10:10] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN10:1;            /**< \brief [11:11] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN11:1;            /**< \brief [12:12] BRC_DIDx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_EIRQ_EN_Bits;

/** \brief  BRC Interrupt Enable Register */
typedef struct _Ifx_GTM_BRC_IRQ_EN_Bits
{
    Ifx_Strict_32Bit DEST_ERR_EN:1;         /**< \brief [0:0] BRC_DEST_ERR_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN0:1;             /**< \brief [1:1] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN1:1;             /**< \brief [2:2] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN2:1;             /**< \brief [3:3] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN3:1;             /**< \brief [4:4] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN4:1;             /**< \brief [5:5] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN5:1;             /**< \brief [6:6] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN6:1;             /**< \brief [7:7] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN7:1;             /**< \brief [8:8] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN8:1;             /**< \brief [9:9] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN9:1;             /**< \brief [10:10] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN10:1;            /**< \brief [11:11] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit DID_EN11:1;            /**< \brief [12:12] BRC_DIDx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_IRQ_EN_Bits;

/** \brief  BRC_DEST_ERR Forcing Interrupt Register */
typedef struct _Ifx_GTM_BRC_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_DEST_ERR:1;        /**< \brief [0:0] Trigger destination error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID0:1;            /**< \brief [1:1] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID1:1;            /**< \brief [2:2] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID2:1;            /**< \brief [3:3] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID3:1;            /**< \brief [4:4] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID4:1;            /**< \brief [5:5] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID5:1;            /**< \brief [6:6] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID6:1;            /**< \brief [7:7] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID7:1;            /**< \brief [8:8] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID8:1;            /**< \brief [9:9] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID9:1;            /**< \brief [10:10] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID10:1;           /**< \brief [11:11] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit TRG_DID11:1;           /**< \brief [12:12] Trigger data inconsistency error interrupt (w) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_IRQ_FORCINT_Bits;

/** \brief  BRC IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_BRC_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_IRQ_MODE_Bits;

/** \brief  BRC Interrupt Notification Register */
typedef struct _Ifx_GTM_BRC_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit DEST_ERR:1;            /**< \brief [0:0] Configuration error interrupt for BRC submodule (rwh) */
    Ifx_Strict_32Bit DID0:1;                /**< \brief [1:1] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID1:1;                /**< \brief [2:2] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID2:1;                /**< \brief [3:3] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID3:1;                /**< \brief [4:4] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID4:1;                /**< \brief [5:5] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID5:1;                /**< \brief [6:6] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID6:1;                /**< \brief [7:7] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID7:1;                /**< \brief [8:8] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID8:1;                /**< \brief [9:9] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID9:1;                /**< \brief [10:10] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID10:1;               /**< \brief [11:11] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit DID11:1;               /**< \brief [12:12] Data inconsistency occurred in MTM mode (rwh) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_IRQ_NOTIFY_Bits;

/** \brief  BRC Software Reset Register */
typedef struct _Ifx_GTM_BRC_RST_Bits
{
    Ifx_Strict_32Bit RST:1;                 /**< \brief [0:0] Software reset (w) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_RST_Bits;

/** \brief  Read Address For Input Channel 0 */
typedef struct _Ifx_GTM_BRC_SRC0_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC0_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 0 */
typedef struct _Ifx_GTM_BRC_SRC0_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC0_DEST_Bits;

/** \brief  Read Address For Input Channel 10 */
typedef struct _Ifx_GTM_BRC_SRC10_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC10_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 10 */
typedef struct _Ifx_GTM_BRC_SRC10_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC10_DEST_Bits;

/** \brief  Read Address For Input Channel 11 */
typedef struct _Ifx_GTM_BRC_SRC11_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC11_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 11 */
typedef struct _Ifx_GTM_BRC_SRC11_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC11_DEST_Bits;

/** \brief  Read Address For Input Channel 1 */
typedef struct _Ifx_GTM_BRC_SRC1_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC1_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 1 */
typedef struct _Ifx_GTM_BRC_SRC1_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC1_DEST_Bits;

/** \brief  Read Address For Input Channel 2 */
typedef struct _Ifx_GTM_BRC_SRC2_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC2_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 2 */
typedef struct _Ifx_GTM_BRC_SRC2_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC2_DEST_Bits;

/** \brief  Read Address For Input Channel 3 */
typedef struct _Ifx_GTM_BRC_SRC3_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC3_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 3 */
typedef struct _Ifx_GTM_BRC_SRC3_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC3_DEST_Bits;

/** \brief  Read Address For Input Channel 4 */
typedef struct _Ifx_GTM_BRC_SRC4_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC4_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 4 */
typedef struct _Ifx_GTM_BRC_SRC4_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC4_DEST_Bits;

/** \brief  Read Address For Input Channel 5 */
typedef struct _Ifx_GTM_BRC_SRC5_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC5_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 5 */
typedef struct _Ifx_GTM_BRC_SRC5_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC5_DEST_Bits;

/** \brief  Read Address For Input Channel 6 */
typedef struct _Ifx_GTM_BRC_SRC6_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC6_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 6 */
typedef struct _Ifx_GTM_BRC_SRC6_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC6_DEST_Bits;

/** \brief  Read Address For Input Channel 7 */
typedef struct _Ifx_GTM_BRC_SRC7_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC7_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 7 */
typedef struct _Ifx_GTM_BRC_SRC7_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC7_DEST_Bits;

/** \brief  Read Address For Input Channel 8 */
typedef struct _Ifx_GTM_BRC_SRC8_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC8_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 8 */
typedef struct _Ifx_GTM_BRC_SRC8_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC8_DEST_Bits;

/** \brief  Read Address For Input Channel 9 */
typedef struct _Ifx_GTM_BRC_SRC9_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] Source ARU address (rw) */
    Ifx_Strict_32Bit reserved_9:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRC_MODE:1;            /**< \brief [12:12] BRC Operation mode select (rw) */
    Ifx_Strict_32Bit reserved_13:19;        /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC9_ADDR_Bits;

/** \brief  Destination Channels For Input Channel 9 */
typedef struct _Ifx_GTM_BRC_SRC9_DEST_Bits
{
    Ifx_Strict_32Bit EN_DEST0:1;            /**< \brief [0:0] Enable BRC destination address 0 (rw) */
    Ifx_Strict_32Bit EN_DEST1:1;            /**< \brief [1:1] Enable BRC destination address 1 (rw) */
    Ifx_Strict_32Bit EN_DEST2:1;            /**< \brief [2:2] Enable BRC destination address 2 (rw) */
    Ifx_Strict_32Bit EN_DEST3:1;            /**< \brief [3:3] Enable BRC destination address 3 (rw) */
    Ifx_Strict_32Bit EN_DEST4:1;            /**< \brief [4:4] Enable BRC destination address 4 (rw) */
    Ifx_Strict_32Bit EN_DEST5:1;            /**< \brief [5:5] Enable BRC destination address 5 (rw) */
    Ifx_Strict_32Bit EN_DEST6:1;            /**< \brief [6:6] Enable BRC destination address 6 (rw) */
    Ifx_Strict_32Bit EN_DEST7:1;            /**< \brief [7:7] Enable BRC destination address 7 (rw) */
    Ifx_Strict_32Bit EN_DEST8:1;            /**< \brief [8:8] Enable BRC destination address 8 (rw) */
    Ifx_Strict_32Bit EN_DEST9:1;            /**< \brief [9:9] Enable BRC destination address 9 (rw) */
    Ifx_Strict_32Bit EN_DEST10:1;           /**< \brief [10:10] Enable BRC destination address 10 (rw) */
    Ifx_Strict_32Bit EN_DEST11:1;           /**< \brief [11:11] Enable BRC destination address 11 (rw) */
    Ifx_Strict_32Bit EN_DEST12:1;           /**< \brief [12:12] Enable BRC destination address 12 (rw) */
    Ifx_Strict_32Bit EN_DEST13:1;           /**< \brief [13:13] Enable BRC destination address 13 (rw) */
    Ifx_Strict_32Bit EN_DEST14:1;           /**< \brief [14:14] Enable BRC destination address 14 (rw) */
    Ifx_Strict_32Bit EN_DEST15:1;           /**< \brief [15:15] Enable BRC destination address 15 (rw) */
    Ifx_Strict_32Bit EN_DEST16:1;           /**< \brief [16:16] Enable BRC destination address 16 (rw) */
    Ifx_Strict_32Bit EN_DEST17:1;           /**< \brief [17:17] Enable BRC destination address 17 (rw) */
    Ifx_Strict_32Bit EN_DEST18:1;           /**< \brief [18:18] Enable BRC destination address 18 (rw) */
    Ifx_Strict_32Bit EN_DEST19:1;           /**< \brief [19:19] Enable BRC destination address 19 (rw) */
    Ifx_Strict_32Bit EN_DEST20:1;           /**< \brief [20:20] Enable BRC destination address 20 (rw) */
    Ifx_Strict_32Bit EN_DEST21:1;           /**< \brief [21:21] Enable BRC destination address 21 (rw) */
    Ifx_Strict_32Bit EN_TRASHBIN:1;         /**< \brief [22:22] Control trash bin functionality (rw) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_BRC_SRC9_DEST_Bits;

/** \brief  GTM to SPB BRIDGE MODE */
typedef struct _Ifx_GTM_BRIDGE_MODE_Bits
{
    Ifx_Strict_32Bit BRG_MODE:1;            /**< \brief [0:0] Defines the operation mode for the AEI bridge (rw) */
    Ifx_Strict_32Bit MSK_WR_RSP:1;          /**< \brief [1:1] Mask write response (rw) */
    Ifx_Strict_32Bit reserved_2:6;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit MODE_UP_PGR:1;         /**< \brief [8:8] Mode update in progress (r) */
    Ifx_Strict_32Bit BUFF_OVL:1;            /**< \brief [9:9] Buffer overflow register (rwh) */
    Ifx_Strict_32Bit reserved_10:2;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SYNC_INPUT_REG:1;      /**< \brief [12:12] Additional Pipeline Stage in Synchronous Bridge Mode (rw) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BRG_RST:1;             /**< \brief [16:16] Bridge software reset (w) */
    Ifx_Strict_32Bit reserved_17:7;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit BUFF_DPT:8;            /**< \brief [31:24] Buffer depth of AEI bridge (r) */
} Ifx_GTM_BRIDGE_MODE_Bits;

/** \brief  GTM to SPB BRIDGE PTR1 */
typedef struct _Ifx_GTM_BRIDGE_PTR1_Bits
{
    Ifx_Strict_32Bit NEW_TRAN_PTR:5;        /**< \brief [4:0] New transaction pointer (r) */
    Ifx_Strict_32Bit FIRST_RSP_PTR:5;       /**< \brief [9:5] First response pointer (r) */
    Ifx_Strict_32Bit TRAN_IN_PGR:5;         /**< \brief [14:10] Transaction in progress pointer (acquire) (r) */
    Ifx_Strict_32Bit ABT_TRAN_PGR:5;        /**< \brief [19:15] Aborted transaction in progress pointer (r) */
    Ifx_Strict_32Bit FBC:6;                 /**< \brief [25:20] Free buffer count (r) */
    Ifx_Strict_32Bit RSP_TRAN_RDY:6;        /**< \brief [31:26] Response transactions ready (r) */
} Ifx_GTM_BRIDGE_PTR1_Bits;

/** \brief  GTM to SPB BRIDGE PTR2 */
typedef struct _Ifx_GTM_BRIDGE_PTR2_Bits
{
    Ifx_Strict_32Bit TRAN_IN_PGR2:5;        /**< \brief [4:0] Transaction in progress pointer (aquire2) (r) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_GTM_BRIDGE_PTR2_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_GTM_CLC_Bits
{
    Ifx_Strict_32Bit DISR:1;                /**< \brief [0:0] Module Disable Request Bit (rw) */
    Ifx_Strict_32Bit DISS:1;                /**< \brief [1:1] Module Disable Status Bit (r) */
    Ifx_Strict_32Bit reserved_2:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit EDIS:1;                /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_CLC_Bits;

/** \brief  CMP Error Interrupt Enable Register */
typedef struct _Ifx_GTM_CMP_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit ABWC0_EN_EIRQ:1;       /**< \brief [0:0] enable ABWC0 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC1_EN_EIRQ:1;       /**< \brief [1:1] enable ABWC1 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC2_EN_EIRQ:1;       /**< \brief [2:2] enable ABWC2 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC3_EN_EIRQ:1;       /**< \brief [3:3] enable ABWC3 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC4_EN_EIRQ:1;       /**< \brief [4:4] enable ABWC4 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC5_EN_EIRQ:1;       /**< \brief [5:5] enable ABWC5 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC6_EN_EIRQ:1;       /**< \brief [6:6] enable ABWC6 interrupt source for CMP_EIRQ line. (rw) */
    Ifx_Strict_32Bit ABWC7_EN_EIRQ:1;       /**< \brief [7:7] enable ABWC7 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC8_EN_EIRQ:1;       /**< \brief [8:8] enable ABWC8 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC9_EN_EIRQ:1;       /**< \brief [9:9] enable ABWC9 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC10_EN_EIRQ:1;      /**< \brief [10:10] enable ABWC10 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit ABWC11_EN_EIRQ:1;      /**< \brief [11:11] enable ABWC11 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC0_EN_EIRQ:1;       /**< \brief [12:12] enable TBWC0 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC1_EN_EIRQ:1;       /**< \brief [13:13] enable TBWC1 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC2_EN_EIRQ:1;       /**< \brief [14:14] enable TBWC2 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC3_EN_EIRQ:1;       /**< \brief [15:15] enable TBWC3 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC4_EN_EIRQ:1;       /**< \brief [16:16] enable TBWC4 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC5_EN_EIRQ:1;       /**< \brief [17:17] enable TBWC5 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC6_EN_EIRQ:1;       /**< \brief [18:18] enable TBWC6 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC7_EN_EIRQ:1;       /**< \brief [19:19] enable TBWC7 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC8_EN_EIRQ:1;       /**< \brief [20:20] enable TBWC8 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC9_EN_EIRQ:1;       /**< \brief [21:21] enable TBWC9 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC10_EN_EIRQ:1;      /**< \brief [22:22] enable TBWC10 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit TBWC11_EN_EIRQ:1;      /**< \brief [23:23] enable TBWC11 interrupt source for CMP_EIRQ line (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMP_EIRQ_EN_Bits;

/** \brief  CMP Comparator Enable Register */
typedef struct _Ifx_GTM_CMP_EN_Bits
{
    Ifx_Strict_32Bit ABWC0_EN:1;            /**< \brief [0:0] Enable comparator 0 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC1_EN:1;            /**< \brief [1:1] Enable comparator 1 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC2_EN:1;            /**< \brief [2:2] Enable comparator 2 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC3_EN:1;            /**< \brief [3:3] Enable comparator 3 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC4_EN:1;            /**< \brief [4:4] Enable comparator 4 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC5_EN:1;            /**< \brief [5:5] Enable comparator 5 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC6_EN:1;            /**< \brief [6:6] Enable comparator 6 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC7_EN:1;            /**< \brief [7:7] Enable comparator 7 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC8_EN:1;            /**< \brief [8:8] Enable comparator 8 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC9_EN:1;            /**< \brief [9:9] Enable comparator 9 in ABW (rw) */
    Ifx_Strict_32Bit ABWC10_EN:1;           /**< \brief [10:10] Enable comparator 10 in ABWC (rw) */
    Ifx_Strict_32Bit ABWC11_EN:1;           /**< \brief [11:11] Enable comparator 11 in ABWC (rw) */
    Ifx_Strict_32Bit TBWC0_EN:1;            /**< \brief [12:12] Enable comparator 0 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC1_EN:1;            /**< \brief [13:13] Enable comparator 1 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC2_EN:1;            /**< \brief [14:14] Enable comparator 2 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC3_EN:1;            /**< \brief [15:15] Enable comparator 3 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC4_EN:1;            /**< \brief [16:16] Enable comparator 4 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC5_EN:1;            /**< \brief [17:17] Enable comparator 5 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC6_EN:1;            /**< \brief [18:18] Enable comparator 6 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC7_EN:1;            /**< \brief [19:19] Enable comparator 7 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC8_EN:1;            /**< \brief [20:20] Enable comparator 8 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC9_EN:1;            /**< \brief [21:21] Enable comparator 9 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC10_EN:1;           /**< \brief [22:22] Enable comparator 10 in TBWC (rw) */
    Ifx_Strict_32Bit TBWC11_EN:1;           /**< \brief [23:23] Enable comparator 11 in TBWC (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMP_EN_Bits;

/** \brief  CMP Interrupt Enable Register */
typedef struct _Ifx_GTM_CMP_IRQ_EN_Bits
{
    Ifx_Strict_32Bit ABWC0_EN_IRQ:1;        /**< \brief [0:0] Enable ABWC0 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC1_EN_IRQ:1;        /**< \brief [1:1] Enable ABWC1 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC2_EN_IRQ:1;        /**< \brief [2:2] Enable ABWC2 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC3_EN_IRQ:1;        /**< \brief [3:3] Enable ABWC3 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC4_EN_IRQ:1;        /**< \brief [4:4] Enable ABWC4 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC5_EN_IRQ:1;        /**< \brief [5:5] Enable ABWC5 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC6_EN_IRQ:1;        /**< \brief [6:6] Enable ABWC6 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC7_EN_IRQ:1;        /**< \brief [7:7] Enable ABWC7 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC8_EN_IRQ:1;        /**< \brief [8:8] Enable ABWC8 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC9_EN_IRQ:1;        /**< \brief [9:9] Enable ABWC9 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC10_EN_IRQ:1;       /**< \brief [10:10] Enable ABWC10 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit ABWC11_EN_IRQ:1;       /**< \brief [11:11] Enable ABWC11 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC0_EN_IRQ:1;        /**< \brief [12:12] Enable TBWC0 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC1_EN_IRQ:1;        /**< \brief [13:13] Enable TBWC1 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC2_EN_IRQ:1;        /**< \brief [14:14] Enable TBWC2 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC3_EN_IRQ:1;        /**< \brief [15:15] Enable TBWC3 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC4_EN_IRQ:1;        /**< \brief [16:16] Enable TBWC4 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC5_EN_IRQ:1;        /**< \brief [17:17] Enable TBWC5 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC6_EN_IRQ:1;        /**< \brief [18:18] Enable TBWC6 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC7_EN_IRQ:1;        /**< \brief [19:19] Enable TBWC7 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC8_EN_IRQ:1;        /**< \brief [20:20] Enable TBWC8 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC9_EN_IRQ:1;        /**< \brief [21:21] Enable TBWC9 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC10_EN_IRQ:1;       /**< \brief [22:22] Enable TBWC10 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit TBWC11_EN_IRQ:1;       /**< \brief [23:23] Enable TBWC11 interrupt source for CMP_IRQ line (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMP_IRQ_EN_Bits;

/** \brief  CMP Interrupt Force Register */
typedef struct _Ifx_GTM_CMP_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_ABWC0:1;           /**< \brief [0:0] Trigger ABWC0 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC1:1;           /**< \brief [1:1] Trigger ABWC1 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC2:1;           /**< \brief [2:2] Trigger ABWC2 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC3:1;           /**< \brief [3:3] Trigger ABWC3 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC4:1;           /**< \brief [4:4] Trigger ABWC4 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC5:1;           /**< \brief [5:5] Trigger ABWC5 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC6:1;           /**< \brief [6:6] Trigger ABWC6 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC7:1;           /**< \brief [7:7] Trigger ABWC7 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC8:1;           /**< \brief [8:8] Trigger ABWC8 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC9:1;           /**< \brief [9:9] Trigger ABWC9 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC10:1;          /**< \brief [10:10] Trigger ABWC10 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ABWC11:1;          /**< \brief [11:11] Trigger ABWC11 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC0:1;           /**< \brief [12:12] Trigger TBWC0 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC1:1;           /**< \brief [13:13] Trigger TBWC1 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC2:1;           /**< \brief [14:14] Trigger TBWC2 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC3:1;           /**< \brief [15:15] Trigger TBWC3 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC4:1;           /**< \brief [16:16] Trigger TBWC4 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC5:1;           /**< \brief [17:17] Trigger TBWC5 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC6:1;           /**< \brief [18:18] Trigger TBWC6 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC7:1;           /**< \brief [19:19] Trigger TBWC7 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC8:1;           /**< \brief [20:20] Trigger TBWC8 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC9:1;           /**< \brief [21:21] Trigger TBWC9 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC10:1;          /**< \brief [22:22] Trigger TBWC10 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TBWC11:1;          /**< \brief [23:23] Trigger TBWC11 bit in CMP_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMP_IRQ_FORCINT_Bits;

/** \brief  CMP IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_CMP_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_CMP_IRQ_MODE_Bits;

/** \brief  CMP Event Notification Register */
typedef struct _Ifx_GTM_CMP_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit ABWC0:1;               /**< \brief [0:0] Error indication for ABWC0 (rwh) */
    Ifx_Strict_32Bit ABWC1:1;               /**< \brief [1:1] Error indication for ABWC1 (rwh) */
    Ifx_Strict_32Bit ABWC2:1;               /**< \brief [2:2] Error indication for ABWC2 (rwh) */
    Ifx_Strict_32Bit ABWC3:1;               /**< \brief [3:3] Error indication for ABWC3 (rwh) */
    Ifx_Strict_32Bit ABWC4:1;               /**< \brief [4:4] Error indication for ABWC4 (rwh) */
    Ifx_Strict_32Bit ABWC5:1;               /**< \brief [5:5] Error indication for ABWC5 (rwh) */
    Ifx_Strict_32Bit ABWC6:1;               /**< \brief [6:6] Error indication for ABWC6 (rwh) */
    Ifx_Strict_32Bit ABWC7:1;               /**< \brief [7:7] Error indication for ABWC7 (rwh) */
    Ifx_Strict_32Bit ABWC8:1;               /**< \brief [8:8] Error indication for ABWC8 (rwh) */
    Ifx_Strict_32Bit ABWC9:1;               /**< \brief [9:9] Error indication for ABWC9 (rwh) */
    Ifx_Strict_32Bit ABWC10:1;              /**< \brief [10:10] Error indication for ABWC10 (rwh) */
    Ifx_Strict_32Bit ABWC11:1;              /**< \brief [11:11] Error indication for ABWC11 (rwh) */
    Ifx_Strict_32Bit TBWC0:1;               /**< \brief [12:12] TOM sub modules outputs bitwise comparator 0 error indication (rwh) */
    Ifx_Strict_32Bit TBWC1:1;               /**< \brief [13:13] TOM sub modules outputs bitwise comparator 1 error indication (rwh) */
    Ifx_Strict_32Bit TBWC2:1;               /**< \brief [14:14] TOM sub modules outputs bitwise comparator 2 error indication (rwh) */
    Ifx_Strict_32Bit TBWC3:1;               /**< \brief [15:15] TOM sub modules outputs bitwise comparator 3 error indication (rwh) */
    Ifx_Strict_32Bit TBWC4:1;               /**< \brief [16:16] TOM sub modules outputs bitwise comparator 4 error indication (rwh) */
    Ifx_Strict_32Bit TBWC5:1;               /**< \brief [17:17] TOM sub modules outputs bitwise comparator 5 error indication (rwh) */
    Ifx_Strict_32Bit TBWC6:1;               /**< \brief [18:18] TOM sub modules outputs bitwise comparator 6 error indication (rwh) */
    Ifx_Strict_32Bit TBWC7:1;               /**< \brief [19:19] TOM sub modules outputs bitwise comparator 7 error indication (rwh) */
    Ifx_Strict_32Bit TBWC8:1;               /**< \brief [20:20] TOM sub modules outputs bitwise comparator 8 error indication (rwh) */
    Ifx_Strict_32Bit TBWC9:1;               /**< \brief [21:21] TOM sub modules outputs bitwise comparator 9 error indication (rwh) */
    Ifx_Strict_32Bit TBWC10:1;              /**< \brief [22:22] TOM sub modules outputs bitwise comparator 10 error indication (rwh) */
    Ifx_Strict_32Bit TBWC11:1;              /**< \brief [23:23] TOM sub modules outputs bitwise comparator 11 error indication (rwh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMP_IRQ_NOTIFY_Bits;

/** \brief  CMU Control For Clock Source Register */
typedef struct _Ifx_GTM_CMU_CLK0_5_CTRL_Bits
{
    Ifx_Strict_32Bit CLK_CNT:24;            /**< \brief [23:0] Clock count Defines count value for the clock divider of clock source CMU_CLK[x] (x:0...5) (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_CLK0_5_CTRL_Bits;

/** \brief  CMU Control For Clock Source 6 Register */
typedef struct _Ifx_GTM_CMU_CLK_6_CTRL_Bits
{
    Ifx_Strict_32Bit CLK_CNT:24;            /**< \brief [23:0] Clock count. Define count value for the clock divider of clock source CMU_CLK6 (rw) */
    Ifx_Strict_32Bit CLK6_SEL:1;            /**< \brief [24:24] Clock source selection for CMU_CLK6 (rw) */
    Ifx_Strict_32Bit reserved_25:7;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_CLK_6_CTRL_Bits;

/** \brief  CMU Control For Clock Source 7 Register */
typedef struct _Ifx_GTM_CMU_CLK_7_CTRL_Bits
{
    Ifx_Strict_32Bit CLK_CNT:24;            /**< \brief [23:0] Clock count. Define count value for the clock divider of clock source CMU_CLK7 (rw) */
    Ifx_Strict_32Bit CLK7_SEL:1;            /**< \brief [24:24] Clock source selection for CMU_CLK7 (rw) */
    Ifx_Strict_32Bit reserved_25:7;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_CLK_7_CTRL_Bits;

/** \brief  CMU Clock Enable Register */
typedef struct _Ifx_GTM_CMU_CLK_EN_Bits
{
    Ifx_Strict_32Bit EN_CLK0:2;             /**< \brief [1:0] Enable clock source 0 (rw) */
    Ifx_Strict_32Bit EN_CLK1:2;             /**< \brief [3:2] Enable clock source 1 (rw) */
    Ifx_Strict_32Bit EN_CLK2:2;             /**< \brief [5:4] Enable clock source 2 (rw) */
    Ifx_Strict_32Bit EN_CLK3:2;             /**< \brief [7:6] Enable clock source 3 (rw) */
    Ifx_Strict_32Bit EN_CLK4:2;             /**< \brief [9:8] Enable clock source 4 (rw) */
    Ifx_Strict_32Bit EN_CLK5:2;             /**< \brief [11:10] Enable clock source 5 (rw) */
    Ifx_Strict_32Bit EN_CLK6:2;             /**< \brief [13:12] Enable clock source 6 (rw) */
    Ifx_Strict_32Bit EN_CLK7:2;             /**< \brief [15:14] Enable clock source 7 (rw) */
    Ifx_Strict_32Bit EN_ECLK0:2;            /**< \brief [17:16] Enable ECLK 0 generation subunit (rw) */
    Ifx_Strict_32Bit EN_ECLK1:2;            /**< \brief [19:18] Enable ECLK 1 generation subunit (rw) */
    Ifx_Strict_32Bit EN_ECLK2:2;            /**< \brief [21:20] Enable ECLK 2 generation subunit (rw) */
    Ifx_Strict_32Bit EN_FXCLK:2;            /**< \brief [23:22] Enable all CMU_FXCLK (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_CLK_EN_Bits;

/** \brief  CMU External Clock Control Denominator Register */
typedef struct _Ifx_GTM_CMU_ECLK_DEN_Bits
{
    Ifx_Strict_32Bit ECLK_DEN:24;           /**< \brief [23:0] Denominator for external clock divider (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_ECLK_DEN_Bits;

/** \brief  CMU External Clock Control Numerator Register */
typedef struct _Ifx_GTM_CMU_ECLK_NUM_Bits
{
    Ifx_Strict_32Bit ECLK_NUM:24;           /**< \brief [23:0] Numerator for external clock divider (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_ECLK_NUM_Bits;

/** \brief  CMU FXCLK Control Register */
typedef struct _Ifx_GTM_CMU_FXCLK_CTRL_Bits
{
    Ifx_Strict_32Bit FXCLK_SEL:4;           /**< \brief [3:0] Input clock selection for EN_FXCLK line (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_FXCLK_CTRL_Bits;

/** \brief  CMU Global Clock Control Denominator Register */
typedef struct _Ifx_GTM_CMU_GCLK_DEN_Bits
{
    Ifx_Strict_32Bit GCLK_DEN:24;           /**< \brief [23:0] Denominator for global clock divider (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_GCLK_DEN_Bits;

/** \brief  CMU Global Clock Control Numerator Register */
typedef struct _Ifx_GTM_CMU_GCLK_NUM_Bits
{
    Ifx_Strict_32Bit GCLK_NUM:24;           /**< \brief [23:0] Numerator for global clock divider (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_CMU_GCLK_NUM_Bits;

/** \brief  GTM Global Control Register */
typedef struct _Ifx_GTM_CTRL_Bits
{
    Ifx_Strict_32Bit RF_PROT:1;             /**< \brief [0:0] RST and FORCINT protection (rw) */
    Ifx_Strict_32Bit TO_MODE:1;             /**< \brief [1:1] AEI Timeout mode (rw) */
    Ifx_Strict_32Bit reserved_2:2;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TO_VAL:5;              /**< \brief [8:4] AEI Timeout value (rw) */
    Ifx_Strict_32Bit reserved_9:23;         /**< \brief \internal Reserved */
} Ifx_GTM_CTRL_Bits;

/** \brief  Data Input 0 0 Register */
typedef struct _Ifx_GTM_DATAIN_Bits
{
    Ifx_Strict_32Bit DATA:32;               /**< \brief [31:0] Data (rw) */
} Ifx_GTM_DATAIN_Bits;

/** \brief  DPLL Action Control i Register */
typedef struct _Ifx_GTM_DPLL_ACB_Bits
{
    Ifx_Strict_32Bit ACB_0:5;               /**< \brief [4:0] Action Control Bits of ACTION_j (rw) */
    Ifx_Strict_32Bit reserved_5:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ACB_1:5;               /**< \brief [12:8] Action Control Bits of ACTION_(j + 1) (rw) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ACB_2:5;               /**< \brief [20:16] Action Control Bits of ACTION_(j + 2) (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ACB_3:5;               /**< \brief [28:24] Action Control Bits of ACTION_(j + 3) (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ACB_Bits;

/** \brief  DPLL ACTION Status Register With Shadow Register */
typedef struct _Ifx_GTM_DPLL_ACT_STA_Bits
{
    Ifx_Strict_32Bit ACT_Ni:24;             /**< \brief [23:0] New output data values concerning to action i provided (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ACT_STA_Bits;

/** \brief  DPLL Calculated ADD_IN Value for SUB_INC1 Generation */
typedef struct _Ifx_GTM_DPLL_ADD_IN_CAL1_Bits
{
    Ifx_Strict_32Bit ADD_IN_CAL_1:24;       /**< \brief [23:0] Calculated input value for SUB_INC1 generation, calculated by the DPLL (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ADD_IN_CAL1_Bits;

/** \brief  DPLL Calculated ADD_IN Value for SUB_INC2 Generation */
typedef struct _Ifx_GTM_DPLL_ADD_IN_CAL2_Bits
{
    Ifx_Strict_32Bit ADD_IN_CAL_2:24;       /**< \brief [23:0] Input value for SUB_INC2 generation, calculated by the DPLL for SMC=RMO=1 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ADD_IN_CAL2_Bits;

/** \brief  DPLL Direct Load Input Value for SUB_INC1 */
typedef struct _Ifx_GTM_DPLL_ADD_IN_LD1_Bits
{
    Ifx_Strict_32Bit ADD_IN_LD_1:24;        /**< \brief [23:0] Input value for SUB_INC1 generation (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ADD_IN_LD1_Bits;

/** \brief  DPLL Direct Load Input Value for SUB_INC1 */
typedef struct _Ifx_GTM_DPLL_ADD_IN_LD2_Bits
{
    Ifx_Strict_32Bit ADD_IN_LD_2:24;        /**< \brief [23:0] Input value for SUB_INC2 generation (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ADD_IN_LD2_Bits;

/** \brief  DPLL Adapt Values for All STATE Increments */
typedef struct _Ifx_GTM_DPLL_ADT_S_Bits
{
    Ifx_Strict_32Bit PD_S:16;               /**< \brief [15:0] Physical deviation of STATE (rw) */
    Ifx_Strict_32Bit NS:6;                  /**< \brief [21:16] Number of STATEs (rw) */
    Ifx_Strict_32Bit reserved_22:10;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ADT_S_Bits;

/** \brief  DPLL Address Offset Register For APT In RAM Region 2 */
typedef struct _Ifx_GTM_DPLL_AOSV_2_Bits
{
    Ifx_Strict_32Bit AOSV_2A:8;             /**< \brief [7:0] Address offset value of the RAM 2A region (r) */
    Ifx_Strict_32Bit AOSV_2B:8;             /**< \brief [15:8] Address offset value of the RAM 2B region (r) */
    Ifx_Strict_32Bit AOSV_2C:8;             /**< \brief [23:16] Address offset value of the RAM 2C region (r) */
    Ifx_Strict_32Bit AOSV_2D:8;             /**< \brief [31:24] Address offset value of the RAM 2D region (r) */
} Ifx_GTM_DPLL_AOSV_2_Bits;

/** \brief  DPLL Actual RAM Pointer to RAM Region 1C3 */
typedef struct _Ifx_GTM_DPLL_APS_1C3_Bits
{
    Ifx_Strict_32Bit reserved_0:2;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit APS_1C3:6;             /**< \brief [7:2] Address pointer STATE for RAM region 1C3 (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_APS_1C3_Bits;

/** \brief  DPLL Actual RAM Pointer to RAM Regions 1C1, 1C2 and 1C4 */
typedef struct _Ifx_GTM_DPLL_APS_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WAPS:1;                /**< \brief [1:1] Write bit for address pointer APS (w) */
    Ifx_Strict_32Bit APS:6;                 /**< \brief [7:2] Address pointer STATE (rw) */
    Ifx_Strict_32Bit reserved_8:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WAPS_1C2:1;            /**< \brief [13:13] Write bit for address pointer APS_1C2 (w) */
    Ifx_Strict_32Bit APS_1C2:6;             /**< \brief [19:14] Address pointer STATE for RAM region 1C2 (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_APS_Bits;

/** \brief  DPLL Old RAM Pointer and Offset Value for STATE */
typedef struct _Ifx_GTM_DPLL_APS_SYNC_Bits
{
    Ifx_Strict_32Bit APS_1C2_EXT:6;         /**< \brief [5:0] Address pointer 1C2 extension (rw) */
    Ifx_Strict_32Bit APS_1C2_STATUS:1;      /**< \brief [6:6] Address pointer 1C2 status (rwh) */
    Ifx_Strict_32Bit reserved_7:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit APS_1C2_OLD:6;         /**< \brief [19:14] Address pointer STATE for RAM region 1C2 at synchronization time (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_APS_SYNC_Bits;

/** \brief  DPLL Actual RAM Pointer to RAM Region 2C */
typedef struct _Ifx_GTM_DPLL_APT_2C_Bits
{
    Ifx_Strict_32Bit reserved_0:2;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit APT_2C:10;             /**< \brief [11:2] Address pointer TRIGGER for RAM region 2C (rw) */
    Ifx_Strict_32Bit reserved_12:20;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_APT_2C_Bits;

/** \brief  DPLL Actual RAM Pointer to RAM Regions 2A, B and D */
typedef struct _Ifx_GTM_DPLL_APT_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WAPT:1;                /**< \brief [1:1] Write bit for address pointer APT (w) */
    Ifx_Strict_32Bit APT:10;                /**< \brief [11:2] Address pointer TRIGGER (rw) */
    Ifx_Strict_32Bit reserved_12:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WAPT_2B:1;             /**< \brief [13:13] Write bit for address pointer APT_2B (w) */
    Ifx_Strict_32Bit APT_2B:10;             /**< \brief [23:14] Address pointer TRIGGER for RAM region 2B (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_APT_Bits;

/** \brief  DPLL Old RAM Pointer and Offset Value for TRIGGER */
typedef struct _Ifx_GTM_DPLL_APT_SYNC_Bits
{
    Ifx_Strict_32Bit APT_2B_EXT:6;          /**< \brief [5:0] Address pointer 2B extension (rw) */
    Ifx_Strict_32Bit APT_2B_STATUS:1;       /**< \brief [6:6] Address pointer 2B status (rwh) */
    Ifx_Strict_32Bit reserved_7:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit APT_2B_OLD:10;         /**< \brief [23:14] Address pointer TRIGGER for RAM region 2B at synchronization time (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_APT_SYNC_Bits;

/** \brief  DPLL Prediction of the actual STATE Increment */
typedef struct _Ifx_GTM_DPLL_CDT_SX_Bits
{
    Ifx_Strict_32Bit CDT_SX:24;             /**< \brief [23:0] Calculated duration of the current STATE increment (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CDT_SX_Bits;

/** \brief  DPLL Prediction of the nominal STATE increment duration */
typedef struct _Ifx_GTM_DPLL_CDT_SX_NOM_Bits
{
    Ifx_Strict_32Bit CDT_SX_NOM:24;         /**< \brief [23:0] Calculated duration of the current t nominal STATE event (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CDT_SX_NOM_Bits;

/** \brief  DPLL Prediction of the actual TRIGGER Increment */
typedef struct _Ifx_GTM_DPLL_CDT_TX_Bits
{
    Ifx_Strict_32Bit CDT_TX:24;             /**< \brief [23:0] Calculated duration of the current TRIGGER increment (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CDT_TX_Bits;

/** \brief  DPLL Prediction of the nominal TRIGGER Increment duration */
typedef struct _Ifx_GTM_DPLL_CDT_TX_NOM_Bits
{
    Ifx_Strict_32Bit CDT_TX_NOM:24;         /**< \brief [23:0] Calculated duration of the current nominal TRIGGER event (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CDT_TX_NOM_Bits;

/** \brief  DPLL Number of Sub-Pulses of SUB_INC1 in Continuous Mode */
typedef struct _Ifx_GTM_DPLL_CNT_NUM1_Bits
{
    Ifx_Strict_32Bit CNT_NUM_1:24;          /**< \brief [23:0] Counter for number of SUB_INC1 pulses (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CNT_NUM1_Bits;

/** \brief  DPLL Number of Sub-Pulses of SUB_INC2 in Continuous Mode */
typedef struct _Ifx_GTM_DPLL_CNT_NUM2_Bits
{
    Ifx_Strict_32Bit CNT_NUM_2:24;          /**< \brief [23:0] Counter for number of SUB_INC2 pulses (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CNT_NUM2_Bits;

/** \brief  DPLL Control 1 Shadow STATE Register */
typedef struct _Ifx_GTM_DPLL_CRTL_1_SHADOW_STATE_Bits
{
    Ifx_Strict_32Bit DMO:1;                 /**< \brief [0:0] DPLL mode select (r) */
    Ifx_Strict_32Bit reserved_1:2;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit COA:1;                 /**< \brief [3:3] Correction strategy in automatic end mode (DMO=0) (r) */
    Ifx_Strict_32Bit PIT:1;                 /**< \brief [4:4] Plausibility (r) */
    Ifx_Strict_32Bit SGE1:1;                /**< \brief [5:5] SUB_INC1 generator enable (r) */
    Ifx_Strict_32Bit DLM1:1;                /**< \brief [6:6] Direct Load Mode (r) */
    Ifx_Strict_32Bit PCM1:1;                /**< \brief [7:7] Pulse Correction Mode (r) */
    Ifx_Strict_32Bit SGE2:1;                /**< \brief [8:8] SUB_INC2 generator enable (r) */
    Ifx_Strict_32Bit DLM2:1;                /**< \brief [9:9] Direct Load Mode (r) */
    Ifx_Strict_32Bit PCM2:1;                /**< \brief [10:10] Pulse Correction Mode (r) */
    Ifx_Strict_32Bit SYN_NS:21;             /**< \brief [31:11] Synchronization number of STATE (r) */
} Ifx_GTM_DPLL_CRTL_1_SHADOW_STATE_Bits;

/** \brief  DPLL Control Register 0 */
typedef struct _Ifx_GTM_DPLL_CTRL_0_Bits
{
    Ifx_Strict_32Bit MLT:10;                /**< \brief [9:0] Multiplier for TRIGGER (rw) */
    Ifx_Strict_32Bit IFP:1;                 /**< \brief [10:10] Input filter position (rw) */
    Ifx_Strict_32Bit SNU:5;                 /**< \brief [15:11] STATE number (rw) */
    Ifx_Strict_32Bit TNU:9;                 /**< \brief [24:16] TRIGGER number (rw) */
    Ifx_Strict_32Bit AMS:1;                 /**< \brief [25:25] Adapt mode STATE (rw) */
    Ifx_Strict_32Bit AMT:1;                 /**< \brief [26:26] Adapt mode TRIGGER (rw) */
    Ifx_Strict_32Bit IDS:1;                 /**< \brief [27:27] Input delay STATE (rw) */
    Ifx_Strict_32Bit IDT:1;                 /**< \brief [28:28] Input delay TRIGGER (rw) */
    Ifx_Strict_32Bit SEN:1;                 /**< \brief [29:29] STATE enable (rw) */
    Ifx_Strict_32Bit TEN:1;                 /**< \brief [30:30] TRIGGER enable (rw) */
    Ifx_Strict_32Bit RMO:1;                 /**< \brief [31:31] Reference mode (rw) */
} Ifx_GTM_DPLL_CTRL_0_Bits;

/** \brief  DPLL Control 0 Shadow STATE Register */
typedef struct _Ifx_GTM_DPLL_CTRL_0_SHADOW_STATE_Bits
{
    Ifx_Strict_32Bit reserved_0:10;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit IFP:1;                 /**< \brief [10:10] Input filter position (r) */
    Ifx_Strict_32Bit reserved_11:14;        /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AMS:1;                 /**< \brief [25:25] Adapt mode STATE (r) */
    Ifx_Strict_32Bit reserved_26:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit IDS:1;                 /**< \brief [27:27] Input delay STATE (r) */
    Ifx_Strict_32Bit reserved_28:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RMO:1;                 /**< \brief [31:31] Reference mode; selection of the relevant the input signal for generation of SUB_INC1 (r) */
} Ifx_GTM_DPLL_CTRL_0_SHADOW_STATE_Bits;

/** \brief  DPLL Control0 Shadow Trigger Register */
typedef struct _Ifx_GTM_DPLL_CTRL_0_SHADOW_TRIGGER_Bits
{
    Ifx_Strict_32Bit MLT:10;                /**< \brief [9:0] multiplier for TRIGGER (r) */
    Ifx_Strict_32Bit IFP:1;                 /**< \brief [10:10] Input filter position (r) */
    Ifx_Strict_32Bit reserved_11:15;        /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AMT:1;                 /**< \brief [26:26] Adapt mode TRIGGER (r) */
    Ifx_Strict_32Bit IDS:1;                 /**< \brief [27:27] Input delay STATE (r) */
    Ifx_Strict_32Bit IDT:1;                 /**< \brief [28:28] Input delay TRIGGER (r) */
    Ifx_Strict_32Bit reserved_29:2;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RMO:1;                 /**< \brief [31:31] Reference mode; selection of the relevant the input signal for generation of SUB_INC1 (r) */
} Ifx_GTM_DPLL_CTRL_0_SHADOW_TRIGGER_Bits;

/** \brief  DPLL Control Register 1 */
typedef struct _Ifx_GTM_DPLL_CTRL_1_Bits
{
    Ifx_Strict_32Bit DMO:1;                 /**< \brief [0:0] DPLL mode select (rw) */
    Ifx_Strict_32Bit DEN:1;                 /**< \brief [1:1] DPLL enable (rw) */
    Ifx_Strict_32Bit IDDS:1;                /**< \brief [2:2] Input direction detection strategy in case of SMC = 0 (rw) */
    Ifx_Strict_32Bit COA:1;                 /**< \brief [3:3] Correction strategy in automatic end mode (DMO=0) (rw) */
    Ifx_Strict_32Bit PIT:1;                 /**< \brief [4:4] Plausibility value PVT to next valid TRIGGER is time related (rw) */
    Ifx_Strict_32Bit SGE1:1;                /**< \brief [5:5] SUB_INC1 generator enable (rw) */
    Ifx_Strict_32Bit DLM1:1;                /**< \brief [6:6] Direct Load Mode for SUB_INC1 generation (rw) */
    Ifx_Strict_32Bit PCM1:1;                /**< \brief [7:7] Pulse Correction Mode for SUB_INC1 generation (rw) */
    Ifx_Strict_32Bit SGE2:1;                /**< \brief [8:8] SUB_INC2 generator enable (rw) */
    Ifx_Strict_32Bit DLM2:1;                /**< \brief [9:9] Direct Load Mode for SUB_INC2 generation (rw) */
    Ifx_Strict_32Bit PCM2:1;                /**< \brief [10:10] Pulse Correction Mode for SUB_INC2 generation (rw) */
    Ifx_Strict_32Bit SYN_NS:5;              /**< \brief [15:11] Synchronization number of STATE (rw) */
    Ifx_Strict_32Bit SYN_NT:5;              /**< \brief [20:16] Synchronization number of TRIGGER (rw) */
    Ifx_Strict_32Bit reserved_21:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit LCD:1;                 /**< \brief [22:22] Locking condition definition (rw) */
    Ifx_Strict_32Bit SWR:1;                 /**< \brief [23:23] Software Reset (w) */
    Ifx_Strict_32Bit SYSF:1;                /**< \brief [24:24] SYN_NS for FULL_SCALE (rw) */
    Ifx_Strict_32Bit TS0_HRS:1;             /**< \brief [25:25] TS0_HRS (rw) */
    Ifx_Strict_32Bit TS0_HRT:1;             /**< \brief [26:26] TS0_HRT (rw) */
    Ifx_Strict_32Bit SMC:1;                 /**< \brief [27:27] Synchronous Motor Control (rw) */
    Ifx_Strict_32Bit SSL:2;                 /**< \brief [29:28] STATE slope select (rw) */
    Ifx_Strict_32Bit TSL:2;                 /**< \brief [31:30] Definition of active slope for signal TRIGGER each active slope is an event defined by TNU (rw) */
} Ifx_GTM_DPLL_CTRL_1_Bits;

/** \brief  DPLL Control 1 Shadow TRIGGER Register */
typedef struct _Ifx_GTM_DPLL_CTRL_1_SHADOW_TRIGGER_Bits
{
    Ifx_Strict_32Bit DMO:1;                 /**< \brief [0:0] DPLL mode select (r) */
    Ifx_Strict_32Bit reserved_1:2;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit COA:1;                 /**< \brief [3:3] Correction strategy in automatic end mode (DMO=0) (r) */
    Ifx_Strict_32Bit PIT:1;                 /**< \brief [4:4] Plausibility (r) */
    Ifx_Strict_32Bit SGE1:1;                /**< \brief [5:5] SUB_INC1 generator enable (r) */
    Ifx_Strict_32Bit DLM1:1;                /**< \brief [6:6] Direct Load Mode (r) */
    Ifx_Strict_32Bit PCM1:1;                /**< \brief [7:7] Pulse Correction Mode (r) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CTRL_1_SHADOW_TRIGGER_Bits;

/** \brief  DPLL Control Register 2 */
typedef struct _Ifx_GTM_DPLL_CTRL_2_Bits
{
    Ifx_Strict_32Bit reserved_0:8;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AEN0:1;                /**< \brief [8:8] ACTION_0 enable (rw) */
    Ifx_Strict_32Bit AEN1:1;                /**< \brief [9:9] ACTION_1 enable (rw) */
    Ifx_Strict_32Bit AEN2:1;                /**< \brief [10:10] ACTION_2 enable (rw) */
    Ifx_Strict_32Bit AEN3:1;                /**< \brief [11:11] ACTION_3 enable (rw) */
    Ifx_Strict_32Bit AEN4:1;                /**< \brief [12:12] ACTION_4 enable (rw) */
    Ifx_Strict_32Bit AEN5:1;                /**< \brief [13:13] ACTION_5 enable (rw) */
    Ifx_Strict_32Bit AEN6:1;                /**< \brief [14:14] ACTION_6 enable (rw) */
    Ifx_Strict_32Bit AEN7:1;                /**< \brief [15:15] ACTION_7 enable (rw) */
    Ifx_Strict_32Bit WAD0:1;                /**< \brief [16:16] Write control bit of Action_0 (w) */
    Ifx_Strict_32Bit WAD1:1;                /**< \brief [17:17] Write control bit of Action_1 (w) */
    Ifx_Strict_32Bit WAD2:1;                /**< \brief [18:18] Write control bit of Action_2 (w) */
    Ifx_Strict_32Bit WAD3:1;                /**< \brief [19:19] Write control bit of Action_3 (w) */
    Ifx_Strict_32Bit WAD4:1;                /**< \brief [20:20] Write control bit of Action_4 (w) */
    Ifx_Strict_32Bit WAD5:1;                /**< \brief [21:21] Write control bit of Action_5 (w) */
    Ifx_Strict_32Bit WAD6:1;                /**< \brief [22:22] Write control bit of Action_6 (w) */
    Ifx_Strict_32Bit WAD7:1;                /**< \brief [23:23] Write control bit of Action_7 (w) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CTRL_2_Bits;

/** \brief  DPLL Control Register 3 */
typedef struct _Ifx_GTM_DPLL_CTRL_3_Bits
{
    Ifx_Strict_32Bit reserved_0:8;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AEN8:1;                /**< \brief [8:8] ACTION_8 enable (rw) */
    Ifx_Strict_32Bit AEN9:1;                /**< \brief [9:9] ACTION_9 enable (rw) */
    Ifx_Strict_32Bit AEN10:1;               /**< \brief [10:10] ACTION_10enable (rw) */
    Ifx_Strict_32Bit AEN11:1;               /**< \brief [11:11] ACTION_11 enable (rw) */
    Ifx_Strict_32Bit AEN12:1;               /**< \brief [12:12] ACTION_12 enable (rw) */
    Ifx_Strict_32Bit AEN13:1;               /**< \brief [13:13] ACTION_13 enable (rw) */
    Ifx_Strict_32Bit AEN14:1;               /**< \brief [14:14] ACTION_14 enable (rw) */
    Ifx_Strict_32Bit AEN15:1;               /**< \brief [15:15] ACTION_15 enable (rw) */
    Ifx_Strict_32Bit WAD8:1;                /**< \brief [16:16] Write control bit of Action_8 (w) */
    Ifx_Strict_32Bit WAD9:1;                /**< \brief [17:17] Write control bit of Action_9 (w) */
    Ifx_Strict_32Bit WAD10:1;               /**< \brief [18:18] Write control bit of Action_10 (w) */
    Ifx_Strict_32Bit WAD11:1;               /**< \brief [19:19] Write control bit of Action_11 (w) */
    Ifx_Strict_32Bit WAD12:1;               /**< \brief [20:20] Write control bit of Action_12 (w) */
    Ifx_Strict_32Bit WAD13:1;               /**< \brief [21:21] Write control bit of Action_13 (w) */
    Ifx_Strict_32Bit WAD14:1;               /**< \brief [22:22] Write control bit of Action_14 (w) */
    Ifx_Strict_32Bit WAD15:1;               /**< \brief [23:23] Write control bit of Action_15 (w) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CTRL_3_Bits;

/** \brief  DPLL Control Register 4 */
typedef struct _Ifx_GTM_DPLL_CTRL_4_Bits
{
    Ifx_Strict_32Bit reserved_0:8;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AEN16:1;               /**< \brief [8:8] ACTION_16 enable (rw) */
    Ifx_Strict_32Bit AEN17:1;               /**< \brief [9:9] ACTION_17 enable (rw) */
    Ifx_Strict_32Bit AEN18:1;               /**< \brief [10:10] ACTION_18 enable (rw) */
    Ifx_Strict_32Bit AEN19:1;               /**< \brief [11:11] ACTION_19 enable (rw) */
    Ifx_Strict_32Bit AEN20:1;               /**< \brief [12:12] ACTION_20 enable (rw) */
    Ifx_Strict_32Bit AEN21:1;               /**< \brief [13:13] ACTION_21 enable (rw) */
    Ifx_Strict_32Bit AEN22:1;               /**< \brief [14:14] ACTION_22 enable (rw) */
    Ifx_Strict_32Bit AEN23:1;               /**< \brief [15:15] ACTION_23 enable (rw) */
    Ifx_Strict_32Bit WAD16:1;               /**< \brief [16:16] Write control bit of Action_16 (w) */
    Ifx_Strict_32Bit WAD17:1;               /**< \brief [17:17] Write control bit of Action_17 (w) */
    Ifx_Strict_32Bit WAD18:1;               /**< \brief [18:18] Write control bit of Action_18 (w) */
    Ifx_Strict_32Bit WAD19:1;               /**< \brief [19:19] Write control bit of Action_19 (w) */
    Ifx_Strict_32Bit WAD20:1;               /**< \brief [20:20] Write control bit of Action_20 (w) */
    Ifx_Strict_32Bit WAD21:1;               /**< \brief [21:21] Write control bit of Action_21 (w) */
    Ifx_Strict_32Bit WAD22:1;               /**< \brief [22:22] Write control bit of Action_22 (w) */
    Ifx_Strict_32Bit WAD23:1;               /**< \brief [23:23] Write control bit of Action_23 (w) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_CTRL_4_Bits;

/** \brief  DPLL ACTION Time To React Before PSAi Register */
typedef struct _Ifx_GTM_DPLL_DLA_Bits
{
    Ifx_Strict_32Bit DLA:24;                /**< \brief [23:0] Time to react before the corresponding position value of a desired action is reached (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_DLA_Bits;

/** \brief  DPLL Duration of Last STATE Increment [DT_S_ACT] */
typedef struct _Ifx_GTM_DPLL_DT_S_ACT_Bits
{
    Ifx_Strict_32Bit DT_S_ACT:24;           /**< \brief [23:0] Calculated duration of the last STATE increment (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_DT_S_ACT_Bits;

/** \brief  DPLL Nominal STATE Increment Values for FULL_SCALE */
typedef struct _Ifx_GTM_DPLL_DT_S_Bits
{
    Ifx_Strict_32Bit DT_S:24;               /**< \brief [23:0] Difference time of STATE (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_DT_S_Bits;

/** \brief  DPLL Duration of Last TRIGGER Increment */
typedef struct _Ifx_GTM_DPLL_DT_T_ACT_Bits
{
    Ifx_Strict_32Bit DT_T_ACT:24;           /**< \brief [23:0] Calculated duration of the last TRIGGER increment (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_DT_T_ACT_Bits;

/** \brief  DPLL Calculated Relative Time To ACTION_i Register */
typedef struct _Ifx_GTM_DPLL_DTA_Bits
{
    Ifx_Strict_32Bit DTA:24;                /**< \brief [23:0] Calculated relative time to ACTION_i (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_DTA_Bits;

/** \brief  DPLL Difference of Prediction to actual value for Last STATE
 * Increment */
typedef struct _Ifx_GTM_DPLL_EDT_S_Bits
{
    Ifx_Strict_32Bit EDT_S:24;              /**< \brief [23:0] Signed difference between actual value and prediction of the last STATE increment: sint24 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_EDT_S_Bits;

/** \brief  DPLL Difference of prediction to actual value of the last TRIGGER
 * increment */
typedef struct _Ifx_GTM_DPLL_EDT_T_Bits
{
    Ifx_Strict_32Bit EDT_T:24;              /**< \brief [23:0] Signed difference between actual value and a simple prediction of the last TRIGGER increment: sint24 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_EDT_T_Bits;

/** \brief  DPLL Error Interrupt Enable Register */
typedef struct _Ifx_GTM_DPLL_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit PDI_EIRQ_EN:1;         /**< \brief [0:0] DPLL disable interrupt enable, when switch off of the DEN bit (rw) */
    Ifx_Strict_32Bit PEI_EIRQ_EN:1;         /**< \brief [1:1] DPLL enable interrupt enable, when switch on of the DEN bit (rw) */
    Ifx_Strict_32Bit TINI_EIRQ_EN:1;        /**< \brief [2:2] TRIGGER minimum hold time violation interrupt enable bit. (rw) */
    Ifx_Strict_32Bit TAXI_EIRQ_EN:1;        /**< \brief [3:3] TRIGGER maximum hold time violation interrupt enable bit (rw) */
    Ifx_Strict_32Bit SISI_EIRQ_EN:1;        /**< \brief [4:4] STATE inactive slope interrupt enable bit (rw) */
    Ifx_Strict_32Bit TISI_EIRQ_EN:1;        /**< \brief [5:5] TRIGGER inactive slope interrupt enable bit (rw) */
    Ifx_Strict_32Bit MSI_EIRQ_EN:1;         /**< \brief [6:6] Missing STATE interrupt enable (rw) */
    Ifx_Strict_32Bit MTI_EIRQ_EN:1;         /**< \brief [7:7] Missing TRIGGER interrupt enable (rw) */
    Ifx_Strict_32Bit SASI_EIRQ_EN:1;        /**< \brief [8:8] STATE active slope interrupt enable (rw) */
    Ifx_Strict_32Bit TASI_EIRQ_EN:1;        /**< \brief [9:9] TRIGGER active slope interrupt enable (rw) */
    Ifx_Strict_32Bit PWI_EIRQ_EN:1;         /**< \brief [10:10] Plausibility window (PVT) violation interrupt of TRIGGER enable (rw) */
    Ifx_Strict_32Bit W2I_EIRQ_EN:1;         /**< \brief [11:11] RAM write access to RAM region 2 interrupt enable (rw) */
    Ifx_Strict_32Bit W1I_EIRQ_EN:1;         /**< \brief [12:12] Write access to RAM region 1B or 1C interrupt (rw) */
    Ifx_Strict_32Bit GL1I_EIRQ_EN:1;        /**< \brief [13:13] Get of lock interrupt enable, when lock arises (rw) */
    Ifx_Strict_32Bit LL1I_EIRQ_EN:1;        /**< \brief [14:14] Loss of lock interrupt enable (rw) */
    Ifx_Strict_32Bit EI_EIRQ_EN:1;          /**< \brief [15:15] Error interrupt enable (see status register) (rw) */
    Ifx_Strict_32Bit GL2I_EIRQ_EN:1;        /**< \brief [16:16] Get of lock interrupt enable for SUB_INC2 (rw) */
    Ifx_Strict_32Bit LL2I_EIRQ_EN:1;        /**< \brief [17:17] Loss of lock interrupt enable for SUB_INC2 (rw) */
    Ifx_Strict_32Bit TE0I_EIRQ_EN:1;        /**< \brief [18:18] TRIGGER event interrupt 0 enable (rw) */
    Ifx_Strict_32Bit TE1I_EIRQ_EN:1;        /**< \brief [19:19] TRIGGER event interrupt 1 enable (rw) */
    Ifx_Strict_32Bit TE2I_EIRQ_EN:1;        /**< \brief [20:20] TRIGGER event interrupt 2 enable (rw) */
    Ifx_Strict_32Bit TE3I_EIRQ_EN:1;        /**< \brief [21:21] TRIGGER event interrupt 3 enable (rw) */
    Ifx_Strict_32Bit TE4I_EIRQ_EN:1;        /**< \brief [22:22] TRIGGER event interrupt 4 enable (rw) */
    Ifx_Strict_32Bit CDTI_EIRQ_EN:1;        /**< \brief [23:23] Enable interrupt when calculation of TRIGGER duration done (rw) */
    Ifx_Strict_32Bit CDSI_EIRQ_EN:1;        /**< \brief [24:24] Enable interrupt when calculation of TRIGGER duration done (rw) */
    Ifx_Strict_32Bit TORI:1;                /**< \brief [25:25] TRIGGER out of range interrupt (rw) */
    Ifx_Strict_32Bit SORI:1;                /**< \brief [26:26] STATE out of range (rw) */
    Ifx_Strict_32Bit DCGI:1;                /**< \brief [27:27] Direction change interrupt (rw) */
    Ifx_Strict_32Bit reserved_28:4;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_EIRQ_EN_Bits;

/** \brief  DPLL Actual Signal STATE Filter Value Register */
typedef struct _Ifx_GTM_DPLL_FTV_S_Bits
{
    Ifx_Strict_32Bit STATE_FT:24;           /**< \brief [23:0] Filter value of the last valid STATE input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_FTV_S_Bits;

/** \brief  DPLL Actual Signal TRIGGER Filter Value Register */
typedef struct _Ifx_GTM_DPLL_FTV_T_Bits
{
    Ifx_Strict_32Bit TRIGGER_FT:24;         /**< \brief [23:0] Filter value of the last valid TRIGGER input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_FTV_T_Bits;

/** \brief  DPLL ID Information For Input Signal PMTR Register */
typedef struct _Ifx_GTM_DPLL_ID_PMTR_Bits
{
    Ifx_Strict_32Bit ID_PMTR_x:9;           /**< \brief [8:0] ID information to the input signal PMTR_x from the ARU (rw) */
    Ifx_Strict_32Bit reserved_9:23;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_ID_PMTR_Bits;

/** \brief  DPLL Counter for Pulses for TBU_TS1 to be sent in Automatic End Mode */
typedef struct _Ifx_GTM_DPLL_INC_CNT1_Bits
{
    Ifx_Strict_32Bit INC_CNT1:24;           /**< \brief [23:0] Actual number of pulses to be still sent out at the current increment until the next valid input signal in automatic end mode (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_INC_CNT1_Bits;

/** \brief  DPLL Counter for Pulses for TBU_TS2 to be sent in Automatic End Mode
 * when SMC=RMO=1 */
typedef struct _Ifx_GTM_DPLL_INC_CNT2_Bits
{
    Ifx_Strict_32Bit INC_CNT2:24;           /**< \brief [23:0] Actual number of pulses to be still sent out at the current increment until the next valid input signal in automatic end mode (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_INC_CNT2_Bits;

/** \brief  DPLL Interrupt Enable Register */
typedef struct _Ifx_GTM_DPLL_IRQ_EN_Bits
{
    Ifx_Strict_32Bit PDI_IRQ_EN:1;          /**< \brief [0:0] DPLL disable interrupt enable, when switch off of the DEN bit (rw) */
    Ifx_Strict_32Bit PEI_IRQ_EN:1;          /**< \brief [1:1] DPLL enable interrupt enable, when switch on of the DEN bit (rw) */
    Ifx_Strict_32Bit TINI_IRQ_EN:1;         /**< \brief [2:2] TRIGGER minimum hold time violation interrupt enable bit (rw) */
    Ifx_Strict_32Bit TAXI_IRQ_EN:1;         /**< \brief [3:3] TRIGGER maximum hold time violation interrupt enable bit (rw) */
    Ifx_Strict_32Bit SISI_IRQ_EN:1;         /**< \brief [4:4] STATE inactive slope interrupt enable bit (rw) */
    Ifx_Strict_32Bit TISI_IRQ_EN:1;         /**< \brief [5:5] TRIGGER inactive slope interrupt enable bit (rw) */
    Ifx_Strict_32Bit MSI_IRQ_EN:1;          /**< \brief [6:6] Missing STATE interrupt enable (rw) */
    Ifx_Strict_32Bit MTI_IRQ_EN:1;          /**< \brief [7:7] Missing TRIGGER interrupt enable (rw) */
    Ifx_Strict_32Bit SASI_IRQ_EN:1;         /**< \brief [8:8] STATE active slope interrupt enable (rw) */
    Ifx_Strict_32Bit TASI_IRQ_EN:1;         /**< \brief [9:9] TRIGGER active slope interrupt enable (rw) */
    Ifx_Strict_32Bit PWI_IRQ_EN:1;          /**< \brief [10:10] Plausibility window (PVT) violation interrupt of TRIGGER enable (rw) */
    Ifx_Strict_32Bit W2I_IRQ_EN:1;          /**< \brief [11:11] RAM write access to RAM region 2 interrupt enable (rw) */
    Ifx_Strict_32Bit W1I_IRQ_EN:1;          /**< \brief [12:12] Write access to RAM region 1B or 1C interrupt (rw) */
    Ifx_Strict_32Bit GL1I_IRQ_EN:1;         /**< \brief [13:13] Get of lock interrupt enable, when lock arises (rw) */
    Ifx_Strict_32Bit LL1I_IRQ_EN:1;         /**< \brief [14:14] Loss of lock interrupt enable (rw) */
    Ifx_Strict_32Bit EI_IRQ_EN:1;           /**< \brief [15:15] Error interrupt enable (see status register) (rw) */
    Ifx_Strict_32Bit GL2I_IRQ_EN:1;         /**< \brief [16:16] Get of lock interrupt enable for SUB_INC2 (rw) */
    Ifx_Strict_32Bit LL2I_IRQ_EN:1;         /**< \brief [17:17] Loss of lock interrupt enable for SUB_INC2 (rw) */
    Ifx_Strict_32Bit TE0I_IRQ_EN:1;         /**< \brief [18:18] TRIGGER event interrupt 0 enable (rw) */
    Ifx_Strict_32Bit TE1I_IRQ_EN:1;         /**< \brief [19:19] TRIGGER event interrupt 1 enable (rw) */
    Ifx_Strict_32Bit TE2I_IRQ_EN:1;         /**< \brief [20:20] TRIGGER event interrupt 2 enable (rw) */
    Ifx_Strict_32Bit TE3I_IRQ_EN:1;         /**< \brief [21:21] TRIGGER event interrupt 3 enable (rw) */
    Ifx_Strict_32Bit TE4I_IRQ_EN:1;         /**< \brief [22:22] TRIGGER event interrupt 4 enable (rw) */
    Ifx_Strict_32Bit CDTI_IRQ_EN:1;         /**< \brief [23:23] Enable interrupt when calculation of TRIGGER duration done (rw) */
    Ifx_Strict_32Bit CDSI_IRQ_EN:1;         /**< \brief [24:24] Enable interrupt when calculation of TRIGGER duration done (rw) */
    Ifx_Strict_32Bit TORI:1;                /**< \brief [25:25] TRIGGER out of range interrupt (rw) */
    Ifx_Strict_32Bit SORI:1;                /**< \brief [26:26] STATE out of range (rw) */
    Ifx_Strict_32Bit DCGI:1;                /**< \brief [27:27] Direction change interrupt (rw) */
    Ifx_Strict_32Bit reserved_28:4;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_IRQ_EN_Bits;

/** \brief  DPLL Interrupt Force Register */
typedef struct _Ifx_GTM_DPLL_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_PDI:1;             /**< \brief [0:0] Force Interrupt PDI (w) */
    Ifx_Strict_32Bit TRG_PEI:1;             /**< \brief [1:1] Force Interrupt PEI (w) */
    Ifx_Strict_32Bit TRG_TINI:1;            /**< \brief [2:2] Force Interrupt TINI (w) */
    Ifx_Strict_32Bit TRG_TAXI:1;            /**< \brief [3:3] Force Interrupt TAXI (w) */
    Ifx_Strict_32Bit TRG_SISI:1;            /**< \brief [4:4] Force Interrupt SISI (w) */
    Ifx_Strict_32Bit TRG_TISI:1;            /**< \brief [5:5] Force Interrupt TISI (w) */
    Ifx_Strict_32Bit TRG_MSI:1;             /**< \brief [6:6] Force Interrupt MSI (w) */
    Ifx_Strict_32Bit TRG_MTI:1;             /**< \brief [7:7] Force Interrupt MTI (w) */
    Ifx_Strict_32Bit TRG_SASI:1;            /**< \brief [8:8] Force Interrupt SASI (w) */
    Ifx_Strict_32Bit TRG_TASI:1;            /**< \brief [9:9] Force Interrupt TASI (w) */
    Ifx_Strict_32Bit TRG_PWI:1;             /**< \brief [10:10] Force Interrupt PWI (w) */
    Ifx_Strict_32Bit TRG_W2I:1;             /**< \brief [11:11] Force Interrupt W2IF (w) */
    Ifx_Strict_32Bit TRG_W1I:1;             /**< \brief [12:12] Force Interrupt W1I (w) */
    Ifx_Strict_32Bit TRG_GL1I:1;            /**< \brief [13:13] Force Interrupt GL1I (w) */
    Ifx_Strict_32Bit TRG_LL1I:1;            /**< \brief [14:14] Force Interrupt LL1I (w) */
    Ifx_Strict_32Bit TRG_EI:1;              /**< \brief [15:15] Force Interrupt EI (w) */
    Ifx_Strict_32Bit TRG_GL2I:1;            /**< \brief [16:16] Force Interrupt GL2I (w) */
    Ifx_Strict_32Bit TRG_LL2I:1;            /**< \brief [17:17] Force Interrupt LL2I (w) */
    Ifx_Strict_32Bit TRG_TE0I:1;            /**< \brief [18:18] Force Interrupt TE0I (w) */
    Ifx_Strict_32Bit TRG_TE1I:1;            /**< \brief [19:19] Force Interrupt TE1I (w) */
    Ifx_Strict_32Bit TRG_TE2I:1;            /**< \brief [20:20] Force Interrupt TE2I (w) */
    Ifx_Strict_32Bit TRG_TE3I:1;            /**< \brief [21:21] Force Interrupt TE3I (w) */
    Ifx_Strict_32Bit TRG_TE4I:1;            /**< \brief [22:22] Force Interrupt TE4I (w) */
    Ifx_Strict_32Bit TRG_CDTI:1;            /**< \brief [23:23] Force Interrupt CDTI (w) */
    Ifx_Strict_32Bit TRG_CDSI:1;            /**< \brief [24:24] Force Interrupt CDSI (w) */
    Ifx_Strict_32Bit TRG_TORI:1;            /**< \brief [25:25] Force Interrupt TORI (w) */
    Ifx_Strict_32Bit TRG_SORI:1;            /**< \brief [26:26] Force Interrupt SORI (w) */
    Ifx_Strict_32Bit TRG_DCGI:1;            /**< \brief [27:27] Force Interrupt DCGI (w) */
    Ifx_Strict_32Bit reserved_28:4;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_IRQ_FORCINT_Bits;

/** \brief  DPLL Interrupt Mode Register */
typedef struct _Ifx_GTM_DPLL_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_IRQ_MODE_Bits;

/** \brief  DPLL Interrupt Notification Register */
typedef struct _Ifx_GTM_DPLL_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit PDI:1;                 /**< \brief [0:0] DPLL disable interrupt (rwh) */
    Ifx_Strict_32Bit PEI:1;                 /**< \brief [1:1] DPLL enable interrupt (rwh) */
    Ifx_Strict_32Bit TINI:1;                /**< \brief [2:2] TRIGGER minimum hold time violation interrupt (∆T) (rwh) */
    Ifx_Strict_32Bit TAXI:1;                /**< \brief [3:3] TRIGGER maximum hold time violation interrupt (∆T>THMA>0) (rwh) */
    Ifx_Strict_32Bit SISI:1;                /**< \brief [4:4] STATE inactive slope interrupt (rwh) */
    Ifx_Strict_32Bit TISI:1;                /**< \brief [5:5] TRIGGER inactive slope interrupt (rwh) */
    Ifx_Strict_32Bit MSI:1;                 /**< \brief [6:6] Missing STATE interrupt (rwh) */
    Ifx_Strict_32Bit MTI:1;                 /**< \brief [7:7] Missing TRIGGER interrupt (rwh) */
    Ifx_Strict_32Bit SASI:1;                /**< \brief [8:8] STATE active slope interrupt (rwh) */
    Ifx_Strict_32Bit TASI:1;                /**< \brief [9:9] TRIGGER active slope interrupt (rwh) */
    Ifx_Strict_32Bit PWI:1;                 /**< \brief [10:10] Plausibility window (PVT) violation interrupt of TRIGGER (rwh) */
    Ifx_Strict_32Bit W2I:1;                 /**< \brief [11:11] RAM write access to RAM region 2 interrupt (rwh) */
    Ifx_Strict_32Bit W1I:1;                 /**< \brief [12:12] Write access to RAM region 1B or 1C interrupt (rwh) */
    Ifx_Strict_32Bit GL1I:1;                /**< \brief [13:13] Get of lock interrupt, for SUB_INC1 (rwh) */
    Ifx_Strict_32Bit LL1I:1;                /**< \brief [14:14] Loss of lock interrupt for SUB_INC1 (rwh) */
    Ifx_Strict_32Bit EI:1;                  /**< \brief [15:15] Error interrupt (see status register bit 31) (rwh) */
    Ifx_Strict_32Bit GL2I:1;                /**< \brief [16:16] Get of lock interrupt, for SUB_INC2 (rwh) */
    Ifx_Strict_32Bit LL2I:1;                /**< \brief [17:17] Loss of lock interrupt for SUB_INC2 (rwh) */
    Ifx_Strict_32Bit TE0I:1;                /**< \brief [18:18] TRIGGER event interrupt 0 (rwh) */
    Ifx_Strict_32Bit TE1I:1;                /**< \brief [19:19] TRIGGER event interrupt 1 (rwh) */
    Ifx_Strict_32Bit TE2I:1;                /**< \brief [20:20] TRIGGER event interrupt 2 (rwh) */
    Ifx_Strict_32Bit TE3I:1;                /**< \brief [21:21] TRIGGER event interrupt 3 (rwh) */
    Ifx_Strict_32Bit TE4I:1;                /**< \brief [22:22] TRIGGER event interrupt 4 (rwh) */
    Ifx_Strict_32Bit CDTI:1;                /**< \brief [23:23] Calculation of TRIGGER duration done, only while NTI_CNT is zero (rwh) */
    Ifx_Strict_32Bit CDSI:1;                /**< \brief [24:24] Calculation of STATE duration done (rwh) */
    Ifx_Strict_32Bit TORI:1;                /**< \brief [25:25] TRIGGER out of range interrupt (rwh) */
    Ifx_Strict_32Bit SORI:1;                /**< \brief [26:26] STATE out of range (rwh) */
    Ifx_Strict_32Bit DCGI:1;                /**< \brief [27:27] Direction change interrupt (rwh) */
    Ifx_Strict_32Bit reserved_28:4;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_IRQ_NOTIFY_Bits;

/** \brief  DPLL Weighted difference of Prediction up to the Last STATE
 * Increment */
typedef struct _Ifx_GTM_DPLL_MEDT_S_Bits
{
    Ifx_Strict_32Bit MEDT_S:24;             /**< \brief [23:0] Signed middle weighted difference between actual value and prediction of the last STATE increments: sint24 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_MEDT_S_Bits;

/** \brief  DPLL Weighted difference of Prediction up to the Last TRIGGER
 * Increment */
typedef struct _Ifx_GTM_DPLL_MEDT_T_Bits
{
    Ifx_Strict_32Bit MEDT_T:24;             /**< \brief [23:0] Signed middle weighted difference between actual value and prediction of the last TRIGGER increments: sint24 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_MEDT_T_Bits;

/** \brief  DPLL Calculated Number of Sub-Pulses between Two STATE Events */
typedef struct _Ifx_GTM_DPLL_MLS1_Bits
{
    Ifx_Strict_32Bit MLS1:18;               /**< \brief [17:0] Number of pulses between two STATE events (to be set and updated by the CPU) (rw) */
    Ifx_Strict_32Bit reserved_18:14;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_MLS1_Bits;

/** \brief  DPLL Calculated Number of Sub-Pulses between Two STATE Events */
typedef struct _Ifx_GTM_DPLL_MLS2_Bits
{
    Ifx_Strict_32Bit MLS2:18;               /**< \brief [17:0] Counter for number of SUB_INC2 pulses (rw) */
    Ifx_Strict_32Bit reserved_18:14;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_MLS2_Bits;

/** \brief  DPLL Missing Pulses to be Added/Subtracted Directly to SUB_INC1 and
 * INC_CNT1 Once */
typedef struct _Ifx_GTM_DPLL_MPVAL1_Bits
{
    Ifx_Strict_32Bit MPVAL1:16;             /**< \brief [15:0] Missing pulses for direct correction of SUB_INC1 pulses by the CPU (sint16) (rw) */
    Ifx_Strict_32Bit SIX1:8;                /**< \brief [23:16] sign extension for MPVAL1 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_MPVAL1_Bits;

/** \brief  DPLL Missing Pulses to be Added/Subtracted Directly to SUB_INC2 and
 * INC_CNT2 Once */
typedef struct _Ifx_GTM_DPLL_MPVAL2_Bits
{
    Ifx_Strict_32Bit MPVAL2:16;             /**< \brief [15:0] missing pulses for direct correction of SUB_INC2 pulses by the CPU (sint16) (rw) */
    Ifx_Strict_32Bit SIX2:8;                /**< \brief [23:16] sign extension for MPVAL2 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_MPVAL2_Bits;

/** \brief  DPLL Calculated Number Of TRIGGER/STATE Increments To ACTION */
typedef struct _Ifx_GTM_DPLL_NA_Bits
{
    Ifx_Strict_32Bit DB:10;                 /**< \brief [9:0] Number of events to Action_i (fractional part) (rw) */
    Ifx_Strict_32Bit DW:10;                 /**< \brief [19:10] Number of events to Action_i (integer part) (w) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NA_Bits;

/** \brief  DPLL Number of Pulses of Current Increment in Emergency Mode */
typedef struct _Ifx_GTM_DPLL_NMB_S_Bits
{
    Ifx_Strict_32Bit NMB_S:20;              /**< \brief [19:0] Number of pulses for STATE (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NMB_S_Bits;

/** \brief  DPLL Target Number of Pulses to be sent in emergency mode Register */
typedef struct _Ifx_GTM_DPLL_NMB_S_TAR_Bits
{
    Ifx_Strict_32Bit NMB_S_TAR:20;          /**< \brief [19:0] Target Number of pulses for STATE (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NMB_S_TAR_Bits;

/** \brief  DPLL Target Number of Pulses to be sent in emergency mode Register */
typedef struct _Ifx_GTM_DPLL_NMB_S_TAR_OLD_Bits
{
    Ifx_Strict_32Bit NMB_S_TAR_OLD:20;      /**< \brief [19:0] Target Number of pulses for STATE (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NMB_S_TAR_OLD_Bits;

/** \brief  DPLL Number of Pulses of Current Increment in Normal Mode */
typedef struct _Ifx_GTM_DPLL_NMB_T_Bits
{
    Ifx_Strict_32Bit NMB_T:16;              /**< \brief [15:0] Number of pulses for TRIGGER (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NMB_T_Bits;

/** \brief  DPLL Target Number of Pulses to be sent in normal mode Register */
typedef struct _Ifx_GTM_DPLL_NMB_T_TAR_Bits
{
    Ifx_Strict_32Bit NMB_T_TAR:16;          /**< \brief [15:0] Target Number of pulses for TRIGGER (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NMB_T_TAR_Bits;

/** \brief  DPLL Target Number of Pulses to be sent in normal mode Register */
typedef struct _Ifx_GTM_DPLL_NMB_T_TAR_OLD_Bits
{
    Ifx_Strict_32Bit NMB_T_TAR_OLD:16;      /**< \brief [15:0] Target Number of pulses for TRIGGER (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NMB_T_TAR_OLD_Bits;

/** \brief  DPLL Number of Active TRIGGER Events to Interrupt */
typedef struct _Ifx_GTM_DPLL_NTI_CNT_Bits
{
    Ifx_Strict_32Bit NTI_CNT:10;            /**< \brief [9:0] Number of TRIGGERs to interrupt (rw) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_NTI_CNT_Bits;

/** \brief  DPLL Number of Recent STATE Events Used for Calculations */
typedef struct _Ifx_GTM_DPLL_NUSC_Bits
{
    Ifx_Strict_32Bit NUSE:6;                /**< \brief [5:0] Number of recent STATE events used for SUB_INCx calculations modulo 2*(SNUmax+1) (rw) */
    Ifx_Strict_32Bit FSS:1;                 /**< \brief [6:6] this value is to be set, when NUSE is set to FULL_SCALE (rw) */
    Ifx_Strict_32Bit SYN_S:6;               /**< \brief [12:7] Number of real and virtual events to be considered for the current increment (rw) */
    Ifx_Strict_32Bit SYN_S_OLD:6;           /**< \brief [18:13] Number of real and virtual events to be considered for the last increment (rw) */
    Ifx_Strict_32Bit VSN:6;                 /**< \brief [24:19] Virtual STATE number (rw) */
    Ifx_Strict_32Bit reserved_25:4;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WNUS:1;                /**< \brief [29:29] Write control bit for NUSE; read as zero (w) */
    Ifx_Strict_32Bit WSYN:1;                /**< \brief [30:30] Write control bit for SYN_S and SYN_S_OLD; read as zero (w) */
    Ifx_Strict_32Bit WVSN:1;                /**< \brief [31:31] Write control bit for VSN; read as zero (w) */
} Ifx_GTM_DPLL_NUSC_Bits;

/** \brief  DPLL Number of Recent TRIGGER Events Used for Calculations */
typedef struct _Ifx_GTM_DPLL_NUTC_Bits
{
    Ifx_Strict_32Bit NUTE:10;               /**< \brief [9:0] Number of recent TRIGGER events used for SUB_INC1 and action calculations modulo 2*(TNUmax+1) (rw) */
    Ifx_Strict_32Bit FST:1;                 /**< \brief [10:10] this value is to be set, when NUTE is set to FULL_SCALE (rw) */
    Ifx_Strict_32Bit reserved_11:2;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SYN_T:3;               /**< \brief [15:13] Number of real and virtual events to be considered for the current increment (rw) */
    Ifx_Strict_32Bit SYN_T_OLD:3;           /**< \brief [18:16] Number of real and virtual events to be considered for the last increment (rw) */
    Ifx_Strict_32Bit VTN:6;                 /**< \brief [24:19] Virtual TRIGGER number (rw) */
    Ifx_Strict_32Bit reserved_25:4;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit WNUT:1;                /**< \brief [29:29] Write control bit for NUTE and FST (w) */
    Ifx_Strict_32Bit WSYN:1;                /**< \brief [30:30] Write control bit for SYN_T and SYN_T_OLD (w) */
    Ifx_Strict_32Bit WVTN:1;                /**< \brief [31:31] Write control bit for VTN (w) */
} Ifx_GTM_DPLL_NUTC_Bits;

/** \brief  DPLL Offset And Switch Old/New Address Register */
typedef struct _Ifx_GTM_DPLL_OSW_Bits
{
    Ifx_Strict_32Bit SWON_S:1;              /**< \brief [0:0] Switch of new STATE (r) */
    Ifx_Strict_32Bit SWON_T:1;              /**< \brief [1:1] Switch of new TRIGGER (r) */
    Ifx_Strict_32Bit reserved_2:6;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit OSS:2;                 /**< \brief [9:8] Offset size of RAM region 2 (rw) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_OSW_Bits;

/** \brief  DPLL Projected TRIGGER Increment Sum Relations for Action_i */
typedef struct _Ifx_GTM_DPLL_PDT_T_Bits
{
    Ifx_Strict_32Bit DB:14;                 /**< \brief [13:0] Fractional part of relation between TRIGGER or STATE increments (rw) */
    Ifx_Strict_32Bit DW:10;                 /**< \brief [23:14] Integer part of relation between TRIGGER or STATE increments (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PDT_T_Bits;

/** \brief  DPLL ACTION Position/Value Action Request Register */
typedef struct _Ifx_GTM_DPLL_PSA_Bits
{
    Ifx_Strict_32Bit PSA:24;                /**< \brief [23:0] Position information of a desired action (i=0...23) (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSA_Bits;

/** \brief  DPLL Calculated Position Value Register */
typedef struct _Ifx_GTM_DPLL_PSAC_Bits
{
    Ifx_Strict_32Bit PSAC:24;               /**< \brief [23:0] calculated position value for the start of ACTION_i in normal or emergency mode according to equations DPLL-17 or DPLL-20 respectively (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSAC_Bits;

/** \brief  DPLL Accurate Calculated Position Stamp of Last STATE Input */
typedef struct _Ifx_GTM_DPLL_PSSC_Bits
{
    Ifx_Strict_32Bit PSSC:24;               /**< \brief [23:0] Calculated position stamp for the last STATE input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSSC_Bits;

/** \brief  DPLL Measured Position Stamp of Last STATE Input */
typedef struct _Ifx_GTM_DPLL_PSSM_0_Bits
{
    Ifx_Strict_32Bit PSSM:24;               /**< \brief [23:0] Position stamp of STATE, measured (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSSM_0_Bits;

/** \brief  DPLL Measured Position Stamp of Last STATE Input */
typedef struct _Ifx_GTM_DPLL_PSSM_1_Bits
{
    Ifx_Strict_32Bit PSSM:24;               /**< \brief [23:0] Position stamp of STATE, measured (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSSM_1_Bits;

/** \brief  DPLL Actual Calculated Position Stamp of Last TRIGGER Input */
typedef struct _Ifx_GTM_DPLL_PSTC_Bits
{
    Ifx_Strict_32Bit PSTC:24;               /**< \brief [23:0] Calculated position stamp of last TRIGGER input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSTC_Bits;

/** \brief  DPLL Measured Position Stamp of Last TRIGGER Input */
typedef struct _Ifx_GTM_DPLL_PSTM_0_Bits
{
    Ifx_Strict_32Bit PSTM:24;               /**< \brief [23:0] Position stamp of TRIGGER, measured (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSTM_0_Bits;

/** \brief  DPLL Measured Position Stamp of Last TRIGGER Input */
typedef struct _Ifx_GTM_DPLL_PSTM_1_Bits
{
    Ifx_Strict_32Bit PSTM:24;               /**< \brief [23:0] Position stamp of TRIGGER, measured (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PSTM_1_Bits;

/** \brief  DPLL Plausibility Value of Next Active TRIGGER Slope */
typedef struct _Ifx_GTM_DPLL_PVT_Bits
{
    Ifx_Strict_32Bit PVT:24;                /**< \brief [23:0] Plausibility value of next valid TRIGGER slope (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_PVT_Bits;

/** \brief  DPLL RAM Initatlisation Register */
typedef struct _Ifx_GTM_DPLL_RAM_INI_Bits
{
    Ifx_Strict_32Bit INIT_1A:1;             /**< \brief [0:0] RAM region 1A initialization in progress (r) */
    Ifx_Strict_32Bit INIT_1B:1;             /**< \brief [1:1] RAM region 1B initialization in progress (r) */
    Ifx_Strict_32Bit INIT_2:1;              /**< \brief [2:2] RAM region 2 initialization in progress (r) */
    Ifx_Strict_32Bit reserved_3:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit INIT_RAM:1;            /**< \brief [4:4] RAM regions 1A, 1B and 2 are to be initialized (w) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RAM_INI_Bits;

/** \brief  DPLL Reciprocal Value of Expected Increment Duration STATE */
typedef struct _Ifx_GTM_DPLL_RCDT_SX_Bits
{
    Ifx_Strict_32Bit RCDT_SX:24;            /**< \brief [23:0] Reciprocal value of expected increment duration *2 while only the lower 24 bits are used (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RCDT_SX_Bits;

/** \brief  DPLL Reciprocal Value of the Expected Nominal Increment Duration
 * STATE */
typedef struct _Ifx_GTM_DPLL_RCDT_SX_NOM_Bits
{
    Ifx_Strict_32Bit RCDT_SX_NOM:24;        /**< \brief [23:0] Reciprocal value of nominal increment duration *2 while only the lower 24 bits are used (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RCDT_SX_NOM_Bits;

/** \brief  DPLL Reciprocal Value of Expected Increment Duration TRIGGER */
typedef struct _Ifx_GTM_DPLL_RCDT_TX_Bits
{
    Ifx_Strict_32Bit RCDT_TX:24;            /**< \brief [23:0] Reciprocal value of expected increment duration *2 while only the lower 24 bits are used (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RCDT_TX_Bits;

/** \brief  DPLL Reciprocal Value of the Expected Nominal Increment Duration
 * TRIGGER */
typedef struct _Ifx_GTM_DPLL_RCDT_TX_NOM_Bits
{
    Ifx_Strict_32Bit RCDT_TX_NOM:24;        /**< \brief [23:0] Reciprocal value of nominal increment duration *2 while only the lower 24 bits are used (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RCDT_TX_NOM_Bits;

/** \brief  DPLL Actual Reciprocal Value of STATE */
typedef struct _Ifx_GTM_DPLL_RDT_S_ACT_Bits
{
    Ifx_Strict_32Bit RDT_S_ACT:24;          /**< \brief [23:0] Reciprocal value of last STATE increment *2 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RDT_S_ACT_Bits;

/** \brief  DPLL Nominal STATE Reciprocal Values in FULL_SCALE */
typedef struct _Ifx_GTM_DPLL_RDT_S_Bits
{
    Ifx_Strict_32Bit RDT_S:24;              /**< \brief [23:0] Reciprocal difference time of TRIGGER (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RDT_S_Bits;

/** \brief  DPLL Actual Reciprocal Value of TRIGGER */
typedef struct _Ifx_GTM_DPLL_RDT_T_ACT_Bits
{
    Ifx_Strict_32Bit RDT_T_ACT:24;          /**< \brief [23:0] Reciprocal value of last TRIGGER increment *2 (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_RDT_T_ACT_Bits;

/** \brief  DPLL STATE Locking Range */
typedef struct _Ifx_GTM_DPLL_SLR_Bits
{
    Ifx_Strict_32Bit SLR:8;                 /**< \brief [7:0] Value is to be multiplied with the last nominal STATE duration in order to get the range for the next STATE event without setting SOR in the DPLL_STATUS register (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_SLR_Bits;

/** \brief  DPLL Status Register */
typedef struct _Ifx_GTM_DPLL_STATUS_Bits
{
    Ifx_Strict_32Bit reserved_0:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CSO:1;                 /**< \brief [1:1] Calculated STATE duration overflow (rwh) */
    Ifx_Strict_32Bit reserved_2:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CTO:1;                 /**< \brief [3:3] Calculated TRIGGER duration overflow (rwh) */
    Ifx_Strict_32Bit CRO:1;                 /**< \brief [4:4] Calculated Reciprocal value overflow (rwh) */
    Ifx_Strict_32Bit RCS:1;                 /**< \brief [5:5] RCS (rh) */
    Ifx_Strict_32Bit RCT:1;                 /**< \brief [6:6] RCT (rwh) */
    Ifx_Strict_32Bit PSE:1;                 /**< \brief [7:7] Prediction space configuration error (rwh) */
    Ifx_Strict_32Bit SOR:1;                 /**< \brief [8:8] STATE out of range (rh) */
    Ifx_Strict_32Bit MS:1;                  /**< \brief [9:9] Missing STATE detected according to TOV_S (rh) */
    Ifx_Strict_32Bit TOR:1;                 /**< \brief [10:10] TRIGGER out of range (rh) */
    Ifx_Strict_32Bit MT:1;                  /**< \brief [11:11] Missing TRIGGER detected according to TOV (rwh) */
    Ifx_Strict_32Bit RAM2_ERR:1;            /**< \brief [12:12] DPLL internal access to not configured RAM2 (rwh) */
    Ifx_Strict_32Bit reserved_13:2;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit LOW_RES:1;             /**< \brief [15:15] Low resolution of TBU_TS0 is used for DPLL input (rwh) */
    Ifx_Strict_32Bit CSVS:1;                /**< \brief [16:16] Current signal value STATE (rh) */
    Ifx_Strict_32Bit CSVT:1;                /**< \brief [17:17] Current signal value TRIGGER (rh) */
    Ifx_Strict_32Bit CAIP2:1;               /**< \brief [18:18] Calculation of actions 12 to 23 in progress (2nd part) (rh) */
    Ifx_Strict_32Bit CAIP1:1;               /**< \brief [19:19] Calculation of actions 0 to 11 in progress (1st part) (rh) */
    Ifx_Strict_32Bit ISN:1;                 /**< \brief [20:20] Number of STATE is not plausible (rh) */
    Ifx_Strict_32Bit ITN:1;                 /**< \brief [21:21] Increment number of TRIGGER is not plausible (rh) */
    Ifx_Strict_32Bit BWD2:1;                /**< \brief [22:22] Backwards drive of SUB_INC2 (rh) */
    Ifx_Strict_32Bit BWD1:1;                /**< \brief [23:23] Backwards drive of SUB_INC1 (rh) */
    Ifx_Strict_32Bit reserved_24:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit LOCK2:1;               /**< \brief [25:25] DPLL Lock status concerning SUB_INC2 (rh) */
    Ifx_Strict_32Bit SYS:1;                 /**< \brief [26:26] Synchronization condition of STATE fixed (rh) */
    Ifx_Strict_32Bit SYT:1;                 /**< \brief [27:27] Synchronization condition of TRIGGER fixed (rh) */
    Ifx_Strict_32Bit FSD:1;                 /**< \brief [28:28] STATE detected (rh) */
    Ifx_Strict_32Bit FTD:1;                 /**< \brief [29:29] First TRIGGER detected (rh) */
    Ifx_Strict_32Bit LOCK1:1;               /**< \brief [30:30] DPLL Lock status concerning SUB_INC1 (rh) */
    Ifx_Strict_32Bit ERR:1;                 /**< \brief [31:31] Error during configuration or operation resulting in unexpected values (rh) */
} Ifx_GTM_DPLL_STATUS_Bits;

/** \brief  DPLL TBU_TS0 Value at last STATE Event */
typedef struct _Ifx_GTM_DPLL_TBU_TS0_S_Bits
{
    Ifx_Strict_32Bit TBU_TS0_S:24;          /**< \brief [23:0] value of TBU_TS0 at the last STATE event (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TBU_TS0_S_Bits;

/** \brief  DPLL TBU_TS0 Value at last TRIGGER Event */
typedef struct _Ifx_GTM_DPLL_TBU_TS0_T_Bits
{
    Ifx_Strict_32Bit TBU_TS0_T:24;          /**< \brief [23:0] value of TBU_TS0 at the last TRIGGER event (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TBU_TS0_T_Bits;

/** \brief  DPLL TRIGGER Hold Time Max Value */
typedef struct _Ifx_GTM_DPLL_THMA_Bits
{
    Ifx_Strict_32Bit THMA:16;               /**< \brief [15:0] Maximal time between active and inactive TRIGGER slope (uint16) (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_THMA_Bits;

/** \brief  DPLL TRIGGER hold time min value */
typedef struct _Ifx_GTM_DPLL_THMI_Bits
{
    Ifx_Strict_32Bit THMI:16;               /**< \brief [15:0] Minimal time between active and inactive TRIGGER slope (uint16) (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_THMI_Bits;

/** \brief  DPLL Measured Last Pulse Time from Valid to Invalid TRIGGER Slope */
typedef struct _Ifx_GTM_DPLL_THVAL_Bits
{
    Ifx_Strict_32Bit THVAL:16;              /**< \brief [15:0] Measured time from the last valid slope to the next inactive TRIGGER slope in time stamp clock counts: this does mean the clock selected for the TBU_CH0_BASE (uint16) (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_THVAL_Bits;

/** \brief  DPLL TRIGGER locking range */
typedef struct _Ifx_GTM_DPLL_TLR_Bits
{
    Ifx_Strict_32Bit TLR:8;                 /**< \brief [7:0] Value is to be multiplied with the last nominal TRIGGER duration in order to get the range for the next TRIGGER event without setting TOR in the DPLL_STATUS register (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TLR_Bits;

/** \brief  DPLL Time Out Value of active TRIGGER Slope */
typedef struct _Ifx_GTM_DPLL_TOV_Bits
{
    Ifx_Strict_32Bit DB:10;                 /**< \brief [9:0] Decision value (fractional part) for missing TRIGGER interrupt (rw) */
    Ifx_Strict_32Bit DW:6;                  /**< \brief [15:10] Decision value (integer part) for missing TRIGGER interrupt (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TOV_Bits;

/** \brief  DPLL Time Out Value of active STATE Slope */
typedef struct _Ifx_GTM_DPLL_TOV_S_Bits
{
    Ifx_Strict_32Bit DB:10;                 /**< \brief [9:0] Decision value (fractional part) for missing STATE interrupt (rw) */
    Ifx_Strict_32Bit DW:6;                  /**< \brief [15:10] Decision value (integer part) for missing STATE interrupt (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TOV_S_Bits;

/** \brief  DPLL Actual Signal STATE Time Stamp Register */
typedef struct _Ifx_GTM_DPLL_TS_S_0_Bits
{
    Ifx_Strict_32Bit STATE_TS:24;           /**< \brief [23:0] Time stamp value of the last valid STATE input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TS_S_0_Bits;

/** \brief  DPLL Actual Signal STATE Time Stamp Register */
typedef struct _Ifx_GTM_DPLL_TS_S_1_Bits
{
    Ifx_Strict_32Bit STATE_TS:24;           /**< \brief [23:0] Time stamp value of the last valid STATE input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TS_S_1_Bits;

/** \brief  DPLL Actual Signal TRIGGER Time Stamp Register */
typedef struct _Ifx_GTM_DPLL_TS_T_0_Bits
{
    Ifx_Strict_32Bit TRIGGER_TS:24;         /**< \brief [23:0] Time stamp value of the last valid TRIGGER input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TS_T_0_Bits;

/** \brief  DPLL Actual Signal TRIGGER Time Stamp Register */
typedef struct _Ifx_GTM_DPLL_TS_T_1_Bits
{
    Ifx_Strict_32Bit TRIGGER_TS:24;         /**< \brief [23:0] Time stamp value of the last valid TRIGGER input (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TS_T_1_Bits;

/** \brief  DPLL Calculate Time Stamp Register */
typedef struct _Ifx_GTM_DPLL_TSAC_Bits
{
    Ifx_Strict_32Bit TSAC:24;               /**< \brief [23:0] calculated time stamp for ACTION_i (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TSAC_Bits;

/** \brief  DPLL Time Stamp Field of STATE Events */
typedef struct _Ifx_GTM_DPLL_TSF_S_Bits
{
    Ifx_Strict_32Bit TSF_S:24;              /**< \brief [23:0] Time stamp field of STATE (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_DPLL_TSF_S_Bits;

/** \brief  Data Exchange Input Control Register */
typedef struct _Ifx_GTM_DXINCON_Bits
{
    Ifx_Strict_32Bit IN00:1;                /**< \brief [0:0] Input 0x Control (rw) */
    Ifx_Strict_32Bit IN01:1;                /**< \brief [1:1] Input 0x Control (rw) */
    Ifx_Strict_32Bit IN02:1;                /**< \brief [2:2] Input 0x Control (rw) */
    Ifx_Strict_32Bit reserved_3:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit IN10:1;                /**< \brief [8:8] Input 1x Control (rw) */
    Ifx_Strict_32Bit IN11:1;                /**< \brief [9:9] Input 1x Control (rw) */
    Ifx_Strict_32Bit IN12:1;                /**< \brief [10:10] Input 1x Control (rw) */
    Ifx_Strict_32Bit reserved_11:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DSS00:1;               /**< \brief [16:16] Data Source Select 0x Control (rw) */
    Ifx_Strict_32Bit DSS01:1;               /**< \brief [17:17] Data Source Select 0x Control (rw) */
    Ifx_Strict_32Bit DSS02:1;               /**< \brief [18:18] Data Source Select 0x Control (rw) */
    Ifx_Strict_32Bit reserved_19:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DSS10:1;               /**< \brief [24:24] Data Source Select 1x Control (rw) */
    Ifx_Strict_32Bit DSS11:1;               /**< \brief [25:25] Data Source Select 1x Control (rw) */
    Ifx_Strict_32Bit DSS12:1;               /**< \brief [26:26] Data Source Select 1x Control (rw) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_DXINCON_Bits;

/** \brief  Data Exchange Output Control Register */
typedef struct _Ifx_GTM_DXOUTCON_Bits
{
    Ifx_Strict_32Bit OUT00:1;               /**< \brief [0:0] Output 0x Control (rw) */
    Ifx_Strict_32Bit OUT01:1;               /**< \brief [1:1] Output 0x Control (rw) */
    Ifx_Strict_32Bit OUT02:1;               /**< \brief [2:2] Output 0x Control (rw) */
    Ifx_Strict_32Bit reserved_3:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit OUT10:1;               /**< \brief [8:8] Output 1x Control (rw) */
    Ifx_Strict_32Bit OUT11:1;               /**< \brief [9:9] Output 1x Control (rw) */
    Ifx_Strict_32Bit OUT12:1;               /**< \brief [10:10] Output 1x Control (rw) */
    Ifx_Strict_32Bit reserved_11:21;        /**< \brief \internal Reserved */
} Ifx_GTM_DXOUTCON_Bits;

/** \brief  GTM Error Interrupt Enable Register */
typedef struct _Ifx_GTM_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit AEI_TO_XPT_EIRQ_EN:1;  /**< \brief [0:0] AEI_TO_XPT_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit AEI_USP_ADDR_EIRQ_EN:1;    /**< \brief [1:1] AEI_USP_ADDR_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit AEI_IM_ADDR_EIRQ_EN:1; /**< \brief [2:2] AEI_IM_ADDR_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit AEI_USP_BE_EIRQ_EN:1;  /**< \brief [3:3] AEI_USP_BE_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_EIRQ_EN_Bits;

/** \brief  F2A0 Stream Activation Register */
typedef struct _Ifx_GTM_F2A_ENABLE_Bits
{
    Ifx_Strict_32Bit STR0_EN:2;             /**< \brief [1:0] Enable/disable stream 0 (rw) */
    Ifx_Strict_32Bit STR1_EN:2;             /**< \brief [3:2] Enable/disable stream 1 (rw) */
    Ifx_Strict_32Bit STR2_EN:2;             /**< \brief [5:4] Enable/disable stream 2 (rw) */
    Ifx_Strict_32Bit STR3_EN:2;             /**< \brief [7:6] Enable/disable stream 3 (rw) */
    Ifx_Strict_32Bit STR4_EN:2;             /**< \brief [9:8] Enable/disable stream 4 (rw) */
    Ifx_Strict_32Bit STR5_EN:2;             /**< \brief [11:10] Enable/disable stream 5 (rw) */
    Ifx_Strict_32Bit STR6_EN:2;             /**< \brief [13:12] Enable/disable stream 6 (rw) */
    Ifx_Strict_32Bit STR7_EN:2;             /**< \brief [15:14] Enable/disable stream 7 (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_F2A_ENABLE_Bits;

/** \brief  F2A Read Channel Address Register */
typedef struct _Ifx_GTM_F2A_RD_CH_ARU_RD_FIFO_Bits
{
    Ifx_Strict_32Bit ADDR:9;                /**< \brief [8:0] ARU Read address (rw) */
    Ifx_Strict_32Bit reserved_9:23;         /**< \brief \internal Reserved */
} Ifx_GTM_F2A_RD_CH_ARU_RD_FIFO_Bits;

/** \brief  F2A Stream Configuration Register */
typedef struct _Ifx_GTM_F2A_STR_CH_STR_CFG_Bits
{
    Ifx_Strict_32Bit reserved_0:16;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TMODE:2;               /**< \brief [17:16] Transfer mode for 53 bit ARU data from/to FIFO (rw) */
    Ifx_Strict_32Bit DIR:1;                 /**< \brief [18:18] Data transfer direction (rw) */
    Ifx_Strict_32Bit reserved_19:13;        /**< \brief \internal Reserved */
} Ifx_GTM_F2A_STR_CH_STR_CFG_Bits;

/** \brief  FIFO0 Channel Control Register */
typedef struct _Ifx_GTM_FIFO_CH_CTRL_Bits
{
    Ifx_Strict_32Bit RBM:1;                 /**< \brief [0:0] Ring buffer mode enable (rw) */
    Ifx_Strict_32Bit RAP:1;                 /**< \brief [1:1] RAM access priority (rw) */
    Ifx_Strict_32Bit FLUSH:1;               /**< \brief [2:2] FIFO Flush control (w) */
    Ifx_Strict_32Bit WULOCK:1;              /**< \brief [3:3] RAM write unlock Enable/disable direct RAM write access to the memory mapped FIFO region (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_CTRL_Bits;

/** \brief  FIFO0 Channel Error Interrupt Enable Register */
typedef struct _Ifx_GTM_FIFO_CH_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit FIFO_EMPTY_EIRQ_EN:1;  /**< \brief [0:0] Error interrupt enable (rw) */
    Ifx_Strict_32Bit FIFO_FULL_EIRQ_EN:1;   /**< \brief [1:1] Interrupt enable (rw) */
    Ifx_Strict_32Bit FIFO_LWM_EIRQ_EN:1;    /**< \brief [2:2] Interrupt enable (rw) */
    Ifx_Strict_32Bit FIFO_UWM_EIRQ_EN:1;    /**< \brief [3:3] Interrupt enable (rw) */
    Ifx_Strict_32Bit Reserved:28;           /**< \brief [31:4] reserved (r) */
} Ifx_GTM_FIFO_CH_EIRQ_EN_Bits;

/** \brief  FIFO0 Channel End Address Register */
typedef struct _Ifx_GTM_FIFO_CH_END_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:10;               /**< \brief [9:0] End address for FIFOi channel x, (x:0...7) (rw) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_END_ADDR_Bits;

/** \brief  FIFO0 Channel Fill Level Register */
typedef struct _Ifx_GTM_FIFO_CH_FILL_LEVEL_Bits
{
    Ifx_Strict_32Bit LEVEL:11;              /**< \brief [10:0] Fill level of the current FIFO (r) */
    Ifx_Strict_32Bit reserved_11:21;        /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_FILL_LEVEL_Bits;

/** \brief  FIFO0 Channel Interrupt Enable Register */
typedef struct _Ifx_GTM_FIFO_CH_IRQ_EN_Bits
{
    Ifx_Strict_32Bit FIFO_EMPTY_IRQ_EN:1;   /**< \brief [0:0] interrupt enable (rw) */
    Ifx_Strict_32Bit FIFO_FULL_IRQ_EN:1;    /**< \brief [1:1] interrupt enable (rw) */
    Ifx_Strict_32Bit FIFO_LWM_IRQ_EN:1;     /**< \brief [2:2] interrupt enable (rw) */
    Ifx_Strict_32Bit FIFO_UWM_IRQ_EN:1;     /**< \brief [3:3] interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_IRQ_EN_Bits;

/** \brief  FIFO0 Channel Force Interrupt By Software Register */
typedef struct _Ifx_GTM_FIFO_CH_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_FIFO_EMPTY:1;      /**< \brief [0:0] Force interrupt of FIFO empty status (w) */
    Ifx_Strict_32Bit TRG_FIFO_FULL:1;       /**< \brief [1:1] Force interrupt of FIFO full status (w) */
    Ifx_Strict_32Bit TRG_FIFO_LWM:1;        /**< \brief [2:2] Force interrupt of lower watermark (w) */
    Ifx_Strict_32Bit TRG_FIFO_UWM:1;        /**< \brief [3:3] Force interrupt of upper watermark (w) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_IRQ_FORCINT_Bits;

/** \brief  FIFO0 Channel IRQ Mode Control Register */
typedef struct _Ifx_GTM_FIFO_CH_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit DMA_HYSTERESIS:1;      /**< \brief [2:2] Enable DMA hysteresis mode (rw) */
    Ifx_Strict_32Bit DMA_HYST_DIR:1;        /**< \brief [3:3] DMA direction in hysteresis mode (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_IRQ_MODE_Bits;

/** \brief  FIFO0 Channel Interrupt Notification Register */
typedef struct _Ifx_GTM_FIFO_CH_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit FIFO_EMPTY:1;          /**< \brief [0:0] FIFO is empty (rwh) */
    Ifx_Strict_32Bit FIFO_FULL:1;           /**< \brief [1:1] FIFO is full (rwh) */
    Ifx_Strict_32Bit FIFO_LWM:1;            /**< \brief [2:2] FIFO Lower watermark was under-run (rwh) */
    Ifx_Strict_32Bit FIFO_UWM:1;            /**< \brief [3:3] FIFO Upper watermark was over-run (rwh) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_IRQ_NOTIFY_Bits;

/** \brief  FIFO0 Channel Lower Watermark Register */
typedef struct _Ifx_GTM_FIFO_CH_LOWER_WM_Bits
{
    Ifx_Strict_32Bit ADDR:10;               /**< \brief [9:0] Lower watermark address (rw) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_LOWER_WM_Bits;

/** \brief  FIFO0 Channel Read Pointer Register */
typedef struct _Ifx_GTM_FIFO_CH_RD_PTR_Bits
{
    Ifx_Strict_32Bit ADDR:10;               /**< \brief [9:0] Position of the read pointer (r) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_RD_PTR_Bits;

/** \brief  FIFO0 Channel Start Address Register */
typedef struct _Ifx_GTM_FIFO_CH_START_ADDR_Bits
{
    Ifx_Strict_32Bit ADDR:10;               /**< \brief [9:0] Start address for FIFOi channel x, (x07) (rw) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_START_ADDR_Bits;

/** \brief  FIFO0 Channel Status Register */
typedef struct _Ifx_GTM_FIFO_CH_STATUS_Bits
{
    Ifx_Strict_32Bit EMPTY:1;               /**< \brief [0:0] FIFO is empty (r) */
    Ifx_Strict_32Bit FULL:1;                /**< \brief [1:1] FIFO is full (r) */
    Ifx_Strict_32Bit LOW_WM:1;              /**< \brief [2:2] Lower watermark reached (r) */
    Ifx_Strict_32Bit UP_WM:1;               /**< \brief [3:3] Upper watermark reached (r) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_STATUS_Bits;

/** \brief  FIFO0 Channel Upper Watermark Register */
typedef struct _Ifx_GTM_FIFO_CH_UPPER_WM_Bits
{
    Ifx_Strict_32Bit ADDR:10;               /**< \brief [9:0] Upper watermark address (rw) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_UPPER_WM_Bits;

/** \brief  FIFO0 Channel Write Pointer Register */
typedef struct _Ifx_GTM_FIFO_CH_WR_PTR_Bits
{
    Ifx_Strict_32Bit ADDR:10;               /**< \brief [9:0] Position of the write pointer (r) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_FIFO_CH_WR_PTR_Bits;

/** \brief  GTM Infrastructure Interrupt Group */
typedef struct _Ifx_GTM_ICM_IRQG_0_Bits
{
    Ifx_Strict_32Bit ARU_NEW_DATA0_IRQ:1;   /**< \brief [0:0] ARU_NEW_DATA0 interrupt (rh) */
    Ifx_Strict_32Bit ARU_NEW_DATA1_IRQ:1;   /**< \brief [1:1] ARU_NEW_DATA1 interrupt (rh) */
    Ifx_Strict_32Bit ARU_ACC_ACK_IRQ:1;     /**< \brief [2:2] ARU_ACC_ACK interrupt (rh) */
    Ifx_Strict_32Bit BRC_IRQ:1;             /**< \brief [3:3] BRC shared submodule interrupt (rh) */
    Ifx_Strict_32Bit AEI_IRQ:1;             /**< \brief [4:4] AEI_IRQ interrupt (rh) */
    Ifx_Strict_32Bit CMP_IRQ:1;             /**< \brief [5:5] CMP shared submodule interrupt (rh) */
    Ifx_Strict_32Bit SPE0_IRQ:1;            /**< \brief [6:6] SPE0 shared submodule interrupt (rh) */
    Ifx_Strict_32Bit SPE1_IRQ:1;            /**< \brief [7:7] SPE1 shared submodule interrupt (rh) */
    Ifx_Strict_32Bit reserved_8:8;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PSM0_CH0_IRQ:1;        /**< \brief [16:16] PSM0 shared submodule channel 0 interrupt (rh) */
    Ifx_Strict_32Bit PSM0_CH1_IRQ:1;        /**< \brief [17:17] PSM0 shared submodule channel 1 interrupt (rh) */
    Ifx_Strict_32Bit PSM0_CH2_IRQ:1;        /**< \brief [18:18] PSM0 shared submodule channel 2 interrupt (rh) */
    Ifx_Strict_32Bit PSM0_CH3_IRQ:1;        /**< \brief [19:19] PSM0 shared submodule channel 3 interrupt (rh) */
    Ifx_Strict_32Bit PSM0_CH4_IRQ:1;        /**< \brief [20:20] PSM0 shared submodule channel 4 interrupt (rh) */
    Ifx_Strict_32Bit PSM0_CH5_IRQ:1;        /**< \brief [21:21] PSM0 shared submodule channel 5 interrupt (rh) */
    Ifx_Strict_32Bit PSM0_CH6_IRQ:1;        /**< \brief [22:22] PSM0 shared submodule channel 6 interrupt (rh) */
    Ifx_Strict_32Bit PSM0_CH7_IRQ:1;        /**< \brief [23:23] PSM0 shared submodule channel 7 interrupt (rh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_0_Bits;

/** \brief  GTM DPLL Interrupt Group */
typedef struct _Ifx_GTM_ICM_IRQG_1_Bits
{
    Ifx_Strict_32Bit DPLL_DCG_IRQ:1;        /**< \brief [0:0] TRIGGER direction change detected. (rh) */
    Ifx_Strict_32Bit DPLL_EDI_IRQ:1;        /**< \brief [1:1] DPLL enable/disable interrupt (rh) */
    Ifx_Strict_32Bit DPLL_TIN_IRQ:1;        /**< \brief [2:2] TRIGGER minimum hold time (THMI) violation detected interrupt (rh) */
    Ifx_Strict_32Bit DPLL_TAX_IRQ:1;        /**< \brief [3:3] TRIGGER maximum hold time (THMA) violation detected interrupt (rh) */
    Ifx_Strict_32Bit DPLL_SIS_IRQ:1;        /**< \brief [4:4] STATE inactive slope detected interrupt. See bit 0. (rh) */
    Ifx_Strict_32Bit DPLL_TIS_IRQ:1;        /**< \brief [5:5] TRIGGER inactive slope detected interrupt. See bit 0. (rh) */
    Ifx_Strict_32Bit DPLL_MSI_IRQ:1;        /**< \brief [6:6] Missing STATE interrupt (rh) */
    Ifx_Strict_32Bit DPLL_MTI_IRQ:1;        /**< \brief [7:7] Missing TRIGGER interrupt (rh) */
    Ifx_Strict_32Bit DPLL_SAS_IRQ:1;        /**< \brief [8:8] STATE active slope detected (rh) */
    Ifx_Strict_32Bit DPLL_TAS_IRQ:1;        /**< \brief [9:9] TRIGGER active slope detected while NTI_CNT is zero (rh) */
    Ifx_Strict_32Bit DPLL_PWI_IRQ:1;        /**< \brief [10:10] Plausibility window (PVT) violation interrupt of TRIGGER (rh) */
    Ifx_Strict_32Bit DPLL_W2I_IRQ:1;        /**< \brief [11:11] Write access to RAM region 2 interrupt (rh) */
    Ifx_Strict_32Bit DPLL_W1I_IRQ:1;        /**< \brief [12:12] Write access to RAM region 1B or 1C interrupt (rh) */
    Ifx_Strict_32Bit DPLL_GLI_IRQ:1;        /**< \brief [13:13] Get of lock interrupt for SUB_INC1 (rh) */
    Ifx_Strict_32Bit DPLL_LLI_IRQ:1;        /**< \brief [14:14] Lost of lock interrupt for SUB_INC1 (rh) */
    Ifx_Strict_32Bit DPLL_EI_IRQ:1;         /**< \brief [15:15] Error interrupt See bit 0 (rh) */
    Ifx_Strict_32Bit DPLL_GL2I_IRQ:1;       /**< \brief [16:16] Get of lock interrupt for SUB_INC2 (rh) */
    Ifx_Strict_32Bit DPLL_LL2I_IRQ:1;       /**< \brief [17:17] Lost of lock interrupt for SUB_INC2 (rh) */
    Ifx_Strict_32Bit DPLL_TE0_IRQ:1;        /**< \brief [18:18] TRIGGER event interrupt 0 (rh) */
    Ifx_Strict_32Bit DPLL_TE1_IRQ:1;        /**< \brief [19:19] TRIGGER event interrupt 1 (rh) */
    Ifx_Strict_32Bit DPLL_TE2_IRQ:1;        /**< \brief [20:20] TRIGGER event interrupt 2 (rh) */
    Ifx_Strict_32Bit DPLL_TE3_IRQ:1;        /**< \brief [21:21] TRIGGER event interrupt 3 (rh) */
    Ifx_Strict_32Bit DPLL_TE4_IRQ:1;        /**< \brief [22:22] TRIGGER event interrupt 4 (rh) */
    Ifx_Strict_32Bit DPLL_CDIT_IRQ:1;       /**< \brief [23:23] DPLL calculated duration interrupt for trigger (rh) */
    Ifx_Strict_32Bit DPLL_CDIS_IRQ:1;       /**< \brief [24:24] DPLL calculated duration interrupt for state (rh) */
    Ifx_Strict_32Bit DPLL_TORI_IRQ:1;       /**< \brief [25:25] DPLL calculated duration interrupt for state (rh) */
    Ifx_Strict_32Bit DPLL_SORI_IRQ:1;       /**< \brief [26:26] DPLL calculated duration interrupt for state (rh) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_1_Bits;

/** \brief  TIM Interrupt Group 0 */
typedef struct _Ifx_GTM_ICM_IRQG_2_Bits
{
    Ifx_Strict_32Bit TIM0_CH0_IRQ:1;        /**< \brief [0:0] TIM0 shared interrupt channel 0 (rh) */
    Ifx_Strict_32Bit TIM0_CH1_IRQ:1;        /**< \brief [1:1] TIM0 shared interrupt channel 1 (rh) */
    Ifx_Strict_32Bit TIM0_CH2_IRQ:1;        /**< \brief [2:2] TIM0 shared interrupt channel 2 (rh) */
    Ifx_Strict_32Bit TIM0_CH3_IRQ:1;        /**< \brief [3:3] TIM0 shared interrupt channel 3 (rh) */
    Ifx_Strict_32Bit TIM0_CH4_IRQ:1;        /**< \brief [4:4] TIM0 shared interrupt channel 4 (rh) */
    Ifx_Strict_32Bit TIM0_CH5_IRQ:1;        /**< \brief [5:5] TIM0 shared interrupt channel 5 (rh) */
    Ifx_Strict_32Bit TIM0_CH6_IRQ:1;        /**< \brief [6:6] TIM0 shared interrupt channel 6 (rh) */
    Ifx_Strict_32Bit TIM0_CH7_IRQ:1;        /**< \brief [7:7] TIM0 shared interrupt channel 7 (rh) */
    Ifx_Strict_32Bit TIM1_CH0_IRQ:1;        /**< \brief [8:8] TIM1 shared interrupt channel 0 (rh) */
    Ifx_Strict_32Bit TIM1_CH1_IRQ:1;        /**< \brief [9:9] TIM1 shared interrupt channel 1 (rh) */
    Ifx_Strict_32Bit TIM1_CH2_IRQ:1;        /**< \brief [10:10] TIM1 shared interrupt channel 2 (rh) */
    Ifx_Strict_32Bit TIM1_CH3_IRQ:1;        /**< \brief [11:11] TIM1 shared interrupt channel 3 (rh) */
    Ifx_Strict_32Bit TIM1_CH4_IRQ:1;        /**< \brief [12:12] TIM1 shared interrupt channel 4 (rh) */
    Ifx_Strict_32Bit TIM1_CH5_IRQ:1;        /**< \brief [13:13] TIM1 shared interrupt channel 5 (rh) */
    Ifx_Strict_32Bit TIM1_CH6_IRQ:1;        /**< \brief [14:14] TIM1 shared interrupt channel 6 (rh) */
    Ifx_Strict_32Bit TIM1_CH7_IRQ:1;        /**< \brief [15:15] TIM1 shared interrupt channel 7 (rh) */
    Ifx_Strict_32Bit TIM2_CH0_IRQ:1;        /**< \brief [16:16] TIM2 shared interrupt channel 0 (rh) */
    Ifx_Strict_32Bit TIM2_CH1_IRQ:1;        /**< \brief [17:17] TIM2 shared interrupt channel 1 (rh) */
    Ifx_Strict_32Bit TIM2_CH2_IRQ:1;        /**< \brief [18:18] TIM2 shared interrupt channel 2 (rh) */
    Ifx_Strict_32Bit TIM2_CH3_IRQ:1;        /**< \brief [19:19] TIM2 shared interrupt channel 3 (rh) */
    Ifx_Strict_32Bit TIM2_CH4_IRQ:1;        /**< \brief [20:20] TIM2 shared interrupt channel 4 (rh) */
    Ifx_Strict_32Bit TIM2_CH5_IRQ:1;        /**< \brief [21:21] TIM2 shared interrupt channel 5 (rh) */
    Ifx_Strict_32Bit TIM2_CH6_IRQ:1;        /**< \brief [22:22] TIM2 shared interrupt channel 6 (rh) */
    Ifx_Strict_32Bit TIM2_CH7_IRQ:1;        /**< \brief [23:23] TIM2 shared interrupt channel 7 (rh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_2_Bits;

/** \brief  MCS Interrupt Group 0 */
typedef struct _Ifx_GTM_ICM_IRQG_4_Bits
{
    Ifx_Strict_32Bit MCS0_CH0_IRQ:1;        /**< \brief [0:0] MCS0 channel 0 interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH1_IRQ:1;        /**< \brief [1:1] MCS0 channel 1 interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH2_IRQ:1;        /**< \brief [2:2] MCS0 channel 2 interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH3_IRQ:1;        /**< \brief [3:3] MCS0 channel 3 interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH4_IRQ:1;        /**< \brief [4:4] MCS0 channel 4 interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH5_IRQ:1;        /**< \brief [5:5] MCS0 channel 5 interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH6_IRQ:1;        /**< \brief [6:6] MCS0 channel 6 interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH7_IRQ:1;        /**< \brief [7:7] MCS0 channel 7 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH0_IRQ:1;        /**< \brief [8:8] MCS1 channel 0 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH1_IRQ:1;        /**< \brief [9:9] MCS1 channel 1 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH2_IRQ:1;        /**< \brief [10:10] MCS1 channel 2 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH3_IRQ:1;        /**< \brief [11:11] MCS1 channel 3 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH4_IRQ:1;        /**< \brief [12:12] MCS1 channel 4 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH5_IRQ:1;        /**< \brief [13:13] MCS1 channel 5 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH6_IRQ:1;        /**< \brief [14:14] MCS1 channel 6 interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH7_IRQ:1;        /**< \brief [15:15] MCS1 channel 7 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH0_IRQ:1;        /**< \brief [16:16] MCS2 channel 0 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH1_IRQ:1;        /**< \brief [17:17] MCS2 channel 1 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH2_IRQ:1;        /**< \brief [18:18] MCS2 channel 2 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH3_IRQ:1;        /**< \brief [19:19] MCS2 channel 3 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH4_IRQ:1;        /**< \brief [20:20] MCS2 channel 4 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH5_IRQ:1;        /**< \brief [21:21] MCS2 channel 5 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH6_IRQ:1;        /**< \brief [22:22] MCS2 channel 6 interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH7_IRQ:1;        /**< \brief [23:23] MCS2 channel 7 interrupt (rh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_4_Bits;

/** \brief  TOM Interrupt Group 0 */
typedef struct _Ifx_GTM_ICM_IRQG_6_Bits
{
    Ifx_Strict_32Bit TOM0_CH0_IRQ:1;        /**< \brief [0:0] TOM0 channel 0 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH1_IRQ:1;        /**< \brief [1:1] TOM0 channel 1 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH2_IRQ:1;        /**< \brief [2:2] TOM0 channel 2 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH3_IRQ:1;        /**< \brief [3:3] TOM0 channel 3 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH4_IRQ:1;        /**< \brief [4:4] TOM0 channel 4 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH5_IRQ:1;        /**< \brief [5:5] TOM0 channel 5 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH6_IRQ:1;        /**< \brief [6:6] TOM0 channel 6 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH7_IRQ:1;        /**< \brief [7:7] TOM0 channel 7 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH8_IRQ:1;        /**< \brief [8:8] TOM0 channel 8 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH9_IRQ:1;        /**< \brief [9:9] TOM0 channel 9 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH10_IRQ:1;       /**< \brief [10:10] TOM0 channel 10 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH11_IRQ:1;       /**< \brief [11:11] TOM0 channel 11 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH12_IRQ:1;       /**< \brief [12:12] TOM0 channel 12 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH13_IRQ:1;       /**< \brief [13:13] TOM0 channel 13 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH14_IRQ:1;       /**< \brief [14:14] TOM0 channel 14 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM0_CH15_IRQ:1;       /**< \brief [15:15] TOM0 channel 15 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH0_IRQ:1;        /**< \brief [16:16] TOM1 channel 0 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH1_IRQ:1;        /**< \brief [17:17] TOM1 channel 1 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH2_IRQ:1;        /**< \brief [18:18] TOM1 channel 2 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH3_IRQ:1;        /**< \brief [19:19] TOM1 channel 3 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH4_IRQ:1;        /**< \brief [20:20] TOM1 channel 4 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH5_IRQ:1;        /**< \brief [21:21] TOM1 channel 5 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH6_IRQ:1;        /**< \brief [22:22] TOM1 channel 6 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH7_IRQ:1;        /**< \brief [23:23] TOM1 channel 7 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH8_IRQ:1;        /**< \brief [24:24] TOM1 channel 8 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH9_IRQ:1;        /**< \brief [25:25] TOM1 channel 9 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH10_IRQ:1;       /**< \brief [26:26] TOM1 channel 10 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH11_IRQ:1;       /**< \brief [27:27] TOM1 channel 11 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH12_IRQ:1;       /**< \brief [28:28] TOM1 channel 12 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH13_IRQ:1;       /**< \brief [29:29] TOM1 channel 13 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH14_IRQ:1;       /**< \brief [30:30] TOM1 channel 14 shared interrupt (rh) */
    Ifx_Strict_32Bit TOM1_CH15_IRQ:1;       /**< \brief [31:31] TOM1 channel 15 shared interrupt (rh) */
} Ifx_GTM_ICM_IRQG_6_Bits;

/** \brief  ATOM Interrupt Group 0 */
typedef struct _Ifx_GTM_ICM_IRQG_9_Bits
{
    Ifx_Strict_32Bit ATOM0_CH0_IRQ:1;       /**< \brief [0:0] ATOM0 channel 0 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM0_CH1_IRQ:1;       /**< \brief [1:1] ATOM0 channel 1 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM0_CH2_IRQ:1;       /**< \brief [2:2] ATOM0 channel 2 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM0_CH3_IRQ:1;       /**< \brief [3:3] ATOM0 channel 3 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM0_CH4_IRQ:1;       /**< \brief [4:4] ATOM0 channel 4 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM0_CH5_IRQ:1;       /**< \brief [5:5] ATOM0 channel 5 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM0_CH6_IRQ:1;       /**< \brief [6:6] ATOM0 channel 6 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM0_CH7_IRQ:1;       /**< \brief [7:7] ATOM0 channel 7 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH0_IRQ:1;       /**< \brief [8:8] ATOM1 channel 0 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH1_IRQ:1;       /**< \brief [9:9] ATOM1 channel 1 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH2_IRQ:1;       /**< \brief [10:10] ATOM1 channel 2 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH3_IRQ:1;       /**< \brief [11:11] ATOM1 channel 3 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH4_IRQ:1;       /**< \brief [12:12] ATOM1 channel 4 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH5_IRQ:1;       /**< \brief [13:13] ATOM1 channel 5 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH6_IRQ:1;       /**< \brief [14:14] ATOM1 channel 6 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM1_CH7_IRQ:1;       /**< \brief [15:15] ATOM1 channel 7 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH0_IRQ:1;       /**< \brief [16:16] ATOM2 channel 0 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH1_IRQ:1;       /**< \brief [17:17] ATOM2 channel 1 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH2_IRQ:1;       /**< \brief [18:18] ATOM2 channel 2 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH3_IRQ:1;       /**< \brief [19:19] ATOM2 channel 3 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH4_IRQ:1;       /**< \brief [20:20] ATOM2 channel 4 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH5_IRQ:1;       /**< \brief [21:21] ATOM2 channel 5 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH6_IRQ:1;       /**< \brief [22:22] ATOM2 channel 6 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM2_CH7_IRQ:1;       /**< \brief [23:23] ATOM2 channel 7 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH0_IRQ:1;       /**< \brief [24:24] ATOM3 channel 0 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH1_IRQ:1;       /**< \brief [25:25] ATOM3 channel 1 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH2_IRQ:1;       /**< \brief [26:26] ATOM3 channel 2 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH3_IRQ:1;       /**< \brief [27:27] ATOM3 channel 3 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH4_IRQ:1;       /**< \brief [28:28] ATOM3 channel 4 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH5_IRQ:1;       /**< \brief [29:29] ATOM3 channel 5 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH6_IRQ:1;       /**< \brief [30:30] ATOM3 channel 6 shared interrupt (rh) */
    Ifx_Strict_32Bit ATOM3_CH7_IRQ:1;       /**< \brief [31:31] ATOM3 channel 7 shared interrupt (rh) */
} Ifx_GTM_ICM_IRQG_9_Bits;

/** \brief  ICM Channel Error Interrupt 0 Register */
typedef struct _Ifx_GTM_ICM_IRQG_CEI0_Bits
{
    Ifx_Strict_32Bit FIFO0_CH0_EIRQ:1;      /**< \brief [0:0] FIFO0 channel 0 error interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_CH1_EIRQ:1;      /**< \brief [1:1] FIFO0 channel 1 shared interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_CH2_EIRQ:1;      /**< \brief [2:2] FIFO0 channel 2 shared interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_CH3_EIRQ:1;      /**< \brief [3:3] FIFO0 channel 3 shared interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_CH4_EIRQ:1;      /**< \brief [4:4] FIFO0 channel 4 shared interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_CH5_EIRQ:1;      /**< \brief [5:5] FIFO0 channel 5 shared interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_CH6_EIRQ:1;      /**< \brief [6:6] FIFO0 channel 6 shared interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_CH7_EIRQ:1;      /**< \brief [7:7] FIFO0 channel 7 shared interrupt (rh) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_CEI0_Bits;

/** \brief  ICM Channel Error Interrupt 1 Register */
typedef struct _Ifx_GTM_ICM_IRQG_CEI1_Bits
{
    Ifx_Strict_32Bit TIM0_CH0_EIRQ:1;       /**< \brief [0:0] TIM0 channel 0 error interrupt (rh) */
    Ifx_Strict_32Bit TIM0_CH1_EIRQ:1;       /**< \brief [1:1] TIM0 channel 1 error interrupt (rh) */
    Ifx_Strict_32Bit TIM0_CH2_EIRQ:1;       /**< \brief [2:2] TIM0 channel 2 error interrupt (rh) */
    Ifx_Strict_32Bit TIM0_CH3_EIRQ:1;       /**< \brief [3:3] TIM0 channel 3 error interrupt (rh) */
    Ifx_Strict_32Bit TIM0_CH4_EIRQ:1;       /**< \brief [4:4] TIM0 channel 4 error interrupt (rh) */
    Ifx_Strict_32Bit TIM0_CH5_EIRQ:1;       /**< \brief [5:5] TIM0 channel 5 error interrupt (rh) */
    Ifx_Strict_32Bit TIM0_CH6_EIRQ:1;       /**< \brief [6:6] TIM0 channel 6 error interrupt (rh) */
    Ifx_Strict_32Bit TIM0_CH7_EIRQ:1;       /**< \brief [7:7] TIM0 channel 7 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH0_EIRQ:1;       /**< \brief [8:8] TIM1 channel 0 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH1_EIRQ:1;       /**< \brief [9:9] TIM1 channel 1 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH2_EIRQ:1;       /**< \brief [10:10] TIM1 channel 2 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH3_EIRQ:1;       /**< \brief [11:11] TIM1 channel 3 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH4_EIRQ:1;       /**< \brief [12:12] TIM1 channel 4 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH5_EIRQ:1;       /**< \brief [13:13] TIM1 channel 5 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH6_EIRQ:1;       /**< \brief [14:14] TIM1 channel 6 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_CH7_EIRQ:1;       /**< \brief [15:15] TIM1 channel 7 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH0_EIRQ:1;       /**< \brief [16:16] TIM2 channel 0 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH1_EIRQ:1;       /**< \brief [17:17] TIM2 channel 1 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH2_EIRQ:1;       /**< \brief [18:18] TIM2 channel 2 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH3_EIRQ:1;       /**< \brief [19:19] TIM2 channel 3 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH4_EIRQ:1;       /**< \brief [20:20] TIM2 channel 4 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH5_EIRQ:1;       /**< \brief [21:21] TIM2 channel 5 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH6_EIRQ:1;       /**< \brief [22:22] TIM2 channel 6 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_CH7_EIRQ:1;       /**< \brief [23:23] TIM2 channel 7 error interrupt (rh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_CEI1_Bits;

/** \brief  ICM Channel Error Interrupt 3 Register */
typedef struct _Ifx_GTM_ICM_IRQG_CEI3_Bits
{
    Ifx_Strict_32Bit MCS0_CH0_EIRQ:1;       /**< \brief [0:0] MCS0 channel 0 error interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH1_EIRQ:1;       /**< \brief [1:1] MCS0 channel 1 error interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH2_EIRQ:1;       /**< \brief [2:2] MCS0 channel 2 error interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH3_EIRQ:1;       /**< \brief [3:3] MCS0 channel 3 error interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH4_EIRQ:1;       /**< \brief [4:4] MCS0 channel 4 error interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH5_EIRQ:1;       /**< \brief [5:5] MCS0 channel 5 error interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH6_EIRQ:1;       /**< \brief [6:6] MCS0 channel 6 error interrupt (rh) */
    Ifx_Strict_32Bit MCS0_CH7_EIRQ:1;       /**< \brief [7:7] MCS0 channel 7 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH0_EIRQ:1;       /**< \brief [8:8] MCS1 channel 0 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH1_EIRQ:1;       /**< \brief [9:9] MCS1 channel 1 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH2_EIRQ:1;       /**< \brief [10:10] MCS1 channel 2 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH3_EIRQ:1;       /**< \brief [11:11] MCS1 channel 3 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH4_EIRQ:1;       /**< \brief [12:12] MCS1 channel 4 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH5_EIRQ:1;       /**< \brief [13:13] MCS1 channel 5 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH6_EIRQ:1;       /**< \brief [14:14] MCS1 channel 6 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_CH7_EIRQ:1;       /**< \brief [15:15] MCS1 channel 7 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH0_EIRQ:1;       /**< \brief [16:16] MCS2 channel 0 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH1_EIRQ:1;       /**< \brief [17:17] MCS2 channel 1 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH2_EIRQ:1;       /**< \brief [18:18] MCS2 channel 2 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH3_EIRQ:1;       /**< \brief [19:19] MCS2 channel 3 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH4_EIRQ:1;       /**< \brief [20:20] MCS2 channel 4 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH5_EIRQ:1;       /**< \brief [21:21] MCS2 channel 5 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH6_EIRQ:1;       /**< \brief [22:22] MCS2 channel 6 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_CH7_EIRQ:1;       /**< \brief [23:23] MCS2 channel 7 error interrupt (rh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_CEI3_Bits;

/** \brief  ICM Module Error Interrupt Register */
typedef struct _Ifx_GTM_ICM_IRQG_MEI_Bits
{
    Ifx_Strict_32Bit GTM_EIRQ:1;            /**< \brief [0:0] GTM Error interrupt request (rh) */
    Ifx_Strict_32Bit BRC_EIRQ:1;            /**< \brief [1:1] BRC error interrupt (rh) */
    Ifx_Strict_32Bit FIFO0_EIRQ:1;          /**< \brief [2:2] FIFO0 error interrupt (rh) */
    Ifx_Strict_32Bit reserved_3:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TIM0_EIRQ:1;           /**< \brief [4:4] TIM0 error interrupt (rh) */
    Ifx_Strict_32Bit TIM1_EIRQ:1;           /**< \brief [5:5] TIM1 error interrupt (rh) */
    Ifx_Strict_32Bit TIM2_EIRQ:1;           /**< \brief [6:6] TIM2 error interrupt (rh) */
    Ifx_Strict_32Bit reserved_7:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit MCS0_EIRQ:1;           /**< \brief [12:12] MCS0 error interrupt (rh) */
    Ifx_Strict_32Bit MCS1_EIRQ:1;           /**< \brief [13:13] MCS1 error interrupt (rh) */
    Ifx_Strict_32Bit MCS2_EIRQ:1;           /**< \brief [14:14] MCS2 error interrupt (rh) */
    Ifx_Strict_32Bit reserved_15:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SPE0_EIRQ:1;           /**< \brief [20:20] SPE0 error interrupt (rh) */
    Ifx_Strict_32Bit SPE1_EIRQ:1;           /**< \brief [21:21] SPE1 error interrupt (rh) */
    Ifx_Strict_32Bit reserved_22:2;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CMP_EIRQ:1;            /**< \brief [24:24] CMP error interrupt (rh) */
    Ifx_Strict_32Bit DPLL_EIRQ:1;           /**< \brief [25:25] DPLL error interrupt (rh) */
    Ifx_Strict_32Bit reserved_26:6;         /**< \brief \internal Reserved */
} Ifx_GTM_ICM_IRQG_MEI_Bits;

/** \brief  CAN Output Select Register */
typedef struct _Ifx_GTM_INOUTSEL_CAN_OUTSEL_Bits
{
    Ifx_Strict_32Bit SEL0:4;                /**< \brief [3:0] Output Selection for CAN GTM connection (rw) */
    Ifx_Strict_32Bit SEL1:4;                /**< \brief [7:4] Output Selection for CAN GTM connection (rw) */
    Ifx_Strict_32Bit SEL2:4;                /**< \brief [11:8] Output Selection for CAN GTM connection (rw) */
    Ifx_Strict_32Bit SEL3:4;                /**< \brief [15:12] Output Selection for CAN GTM connection (rw) */
    Ifx_Strict_32Bit SEL4:4;                /**< \brief [19:16] Output Selection for CAN GTM connection (rw) */
    Ifx_Strict_32Bit SEL5:4;                /**< \brief [23:20] Output Selection for CAN GTM connection (rw) */
    Ifx_Strict_32Bit SEL6:4;                /**< \brief [27:24] Output Selection for CAN GTM connection (rw) */
    Ifx_Strict_32Bit SEL7:4;                /**< \brief [31:28] Output Selection for CAN GTM connection (rw) */
} Ifx_GTM_INOUTSEL_CAN_OUTSEL_Bits;

/** \brief  DSADC Input Select Register */
typedef struct _Ifx_GTM_INOUTSEL_DSADC_INSEL_Bits
{
    Ifx_Strict_32Bit INSEL0:4;              /**< \brief [3:0] In Selection for DSADCn GTM connection (rw) */
    Ifx_Strict_32Bit INSEL1:4;              /**< \brief [7:4] In Selection for DSADCn GTM connection (rw) */
    Ifx_Strict_32Bit INSEL2:4;              /**< \brief [11:8] In Selection for DSADCn GTM connection (rw) */
    Ifx_Strict_32Bit INSEL3:4;              /**< \brief [15:12] In Selection for DSADCn GTM connection (rw) */
    Ifx_Strict_32Bit INSEL4:4;              /**< \brief [19:16] In Selection for DSADCn GTM connection (rw) */
    Ifx_Strict_32Bit INSEL5:4;              /**< \brief [23:20] In Selection for DSADCn GTM connection (rw) */
    Ifx_Strict_32Bit INSEL6:4;              /**< \brief [27:24] In Selection for DSADCn GTM connection (rw) */
    Ifx_Strict_32Bit INSEL7:4;              /**< \brief [31:28] In Selection for DSADCn GTM connection (rw) */
} Ifx_GTM_INOUTSEL_DSADC_INSEL_Bits;

/** \brief  DSADC Output Select Register */
typedef struct _Ifx_GTM_INOUTSEL_DSADC_OUTSEL_Bits
{
    Ifx_Strict_32Bit SEL0:3;                /**< \brief [2:0] Output Selection for DSADC0 GTM connection (rw) */
    Ifx_Strict_32Bit reserved_3:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL2:3;                /**< \brief [10:8] Output Selection for DSADC2 GTM connection (rw) */
    Ifx_Strict_32Bit reserved_11:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL3:3;                /**< \brief [14:12] Output Selection for DSADC3 GTM connection (rw) */
    Ifx_Strict_32Bit reserved_15:17;        /**< \brief \internal Reserved */
} Ifx_GTM_INOUTSEL_DSADC_OUTSEL_Bits;

/** \brief  PSI5 Output Select 0 Register */
typedef struct _Ifx_GTM_INOUTSEL_PSI5_OUTSEL0_Bits
{
    Ifx_Strict_32Bit SEL0:4;                /**< \brief [3:0] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL1:4;                /**< \brief [7:4] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL2:4;                /**< \brief [11:8] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL3:4;                /**< \brief [15:12] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL4:4;                /**< \brief [19:16] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL5:4;                /**< \brief [23:20] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_INOUTSEL_PSI5_OUTSEL0_Bits;

/** \brief  PSI5-S Output Select Register */
typedef struct _Ifx_GTM_INOUTSEL_PSI5S_OUTSEL_Bits
{
    Ifx_Strict_32Bit SEL0:4;                /**< \brief [3:0] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL1:4;                /**< \brief [7:4] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL2:4;                /**< \brief [11:8] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit reserved_12:4;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL4:4;                /**< \brief [19:16] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL5:4;                /**< \brief [23:20] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit SEL6:4;                /**< \brief [27:24] Output Selection for PSI5x GTM connection (rw) */
    Ifx_Strict_32Bit reserved_28:4;         /**< \brief \internal Reserved */
} Ifx_GTM_INOUTSEL_PSI5S_OUTSEL_Bits;

/** \brief  Timer Output Select Register */
typedef struct _Ifx_GTM_INOUTSEL_T_OUTSEL_Bits
{
    Ifx_Strict_32Bit SEL0:2;                /**< \brief [1:0] TOUT(n*16+0) Output Selection (rw) */
    Ifx_Strict_32Bit SEL1:2;                /**< \brief [3:2] TOUT(n*16+1) Output Selection (rw) */
    Ifx_Strict_32Bit SEL2:2;                /**< \brief [5:4] TOUT(n*16+2) Output Selection (rw) */
    Ifx_Strict_32Bit SEL3:2;                /**< \brief [7:6] TOUT(n*16+3) Output Selection (rw) */
    Ifx_Strict_32Bit SEL4:2;                /**< \brief [9:8] TOUT(n*16+4) Output Selection (rw) */
    Ifx_Strict_32Bit SEL5:2;                /**< \brief [11:10] TOUT(n*16+5) Output Selection (rw) */
    Ifx_Strict_32Bit SEL6:2;                /**< \brief [13:12] TOUT(n*16+6) Output Selection (rw) */
    Ifx_Strict_32Bit SEL7:2;                /**< \brief [15:14] TOUT(n*16+7) Output Selection (rw) */
    Ifx_Strict_32Bit SEL8:2;                /**< \brief [17:16] TOUT(n*16+8) Output Selection (rw) */
    Ifx_Strict_32Bit SEL9:2;                /**< \brief [19:18] TOUT(n*16+9) Output Selection (rw) */
    Ifx_Strict_32Bit SEL10:2;               /**< \brief [21:20] TOUT(n*16+10) Output Selection (rw) */
    Ifx_Strict_32Bit SEL11:2;               /**< \brief [23:22] TOUT(n*16+11) Output Selection (rw) */
    Ifx_Strict_32Bit SEL12:2;               /**< \brief [25:24] TOUT(n*16+12) Output Selection (rw) */
    Ifx_Strict_32Bit SEL13:2;               /**< \brief [27:26] TOUT(n*16+13) Output Selection (rw) */
    Ifx_Strict_32Bit SEL14:2;               /**< \brief [29:28] TOUT(n*16+14) Output Selection (rw) */
    Ifx_Strict_32Bit SEL15:2;               /**< \brief [31:30] TOUT(n*16+15) Output Selection (rw) */
} Ifx_GTM_INOUTSEL_T_OUTSEL_Bits;

/** \brief  TIM Input Select Register */
typedef struct _Ifx_GTM_INOUTSEL_TIM_INSEL_Bits
{
    Ifx_Strict_32Bit CH0SEL:4;              /**< \brief [3:0] TIM Channel 0 Input Selection (rw) */
    Ifx_Strict_32Bit CH1SEL:4;              /**< \brief [7:4] TIM Channel 1 Input Selection (rw) */
    Ifx_Strict_32Bit CH2SEL:4;              /**< \brief [11:8] TIM Channel 2 Input Selection (rw) */
    Ifx_Strict_32Bit CH3SEL:4;              /**< \brief [15:12] TIM Channel 3 Input Selection (rw) */
    Ifx_Strict_32Bit CH4SEL:4;              /**< \brief [19:16] TIM Channel 4 Input Selection (rw) */
    Ifx_Strict_32Bit CH5SEL:4;              /**< \brief [23:20] TIM Channel 5 Input Selection (rw) */
    Ifx_Strict_32Bit CH6SEL:4;              /**< \brief [27:24] TIM Channel 6 Input Selection (rw) */
    Ifx_Strict_32Bit CH7SEL:4;              /**< \brief [31:28] TIM Channel 7 Input Selection (rw) */
} Ifx_GTM_INOUTSEL_TIM_INSEL_Bits;

/** \brief  GTM Interrupt Enable Register */
typedef struct _Ifx_GTM_IRQ_EN_Bits
{
    Ifx_Strict_32Bit AEI_TO_XPT_IRQ_EN:1;   /**< \brief [0:0] AEI_TO_XPT_IRQ interrupt enable. (rw) */
    Ifx_Strict_32Bit AEI_USP_ADDR_IRQ_EN:1; /**< \brief [1:1] AEI_USP_ADDR_IRQ interrupt enable. (rw) */
    Ifx_Strict_32Bit AEI_IM_ADDR_IRQ_EN:1;  /**< \brief [2:2] AEI_IM_ADDR_IRQ interrupt enable. (rw) */
    Ifx_Strict_32Bit AEI_USP_BE_IRQ_EN:1;   /**< \brief [3:3] AEI_USP_BE_IRQ interrupt enable. (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_IRQ_EN_Bits;

/** \brief  GTM Software Interrupt Generation Register */
typedef struct _Ifx_GTM_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_AEI_TO_XPT:1;      /**< \brief [0:0] Trigger AEI_TO_XPT_IRQ interrupt by software. (w) */
    Ifx_Strict_32Bit TRG_AEI_USP_ADDR:1;    /**< \brief [1:1] Trigger AEI_USP_ADDR_IRQ interrupt by software. (w) */
    Ifx_Strict_32Bit TRG_AEI_IM_ADDR:1;     /**< \brief [2:2] Trigger AEI_IM_ADDR_IRQ interrupt by software. (w) */
    Ifx_Strict_32Bit TRG_AEI_USP_BE:1;      /**< \brief [3:3] Trigger AEI_USP_BE_IRQ interrupt by software. (w) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_IRQ_FORCINT_Bits;

/** \brief  GTM Top Level Interrupts Mode Selection */
typedef struct _Ifx_GTM_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] Interrupt strategy mode selection for the AEI timeout and address monitoring interrupts (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_IRQ_MODE_Bits;

/** \brief  GTM Interrupt Notification Register */
typedef struct _Ifx_GTM_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit AEI_TO_XPT:1;          /**< \brief [0:0] AEI Timeout exception occurred (rwh) */
    Ifx_Strict_32Bit AEI_USP_ADDR:1;        /**< \brief [1:1] AEI Unsupported address interrupt (rwh) */
    Ifx_Strict_32Bit AEI_IM_ADDR:1;         /**< \brief [2:2] AEI Illegal Module address interrupt (rwh) */
    Ifx_Strict_32Bit AEI_USP_BE:1;          /**< \brief [3:3] AEI Unsupported byte enable interrupt (rwh) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_IRQ_NOTIFY_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_GTM_KRST0_Bits
{
    Ifx_Strict_32Bit RST:1;                 /**< \brief [0:0] Kernel Reset (rwh) */
    Ifx_Strict_32Bit RSTSTAT:1;             /**< \brief [1:1] Kernel Reset Status (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_GTM_KRST1_Bits
{
    Ifx_Strict_32Bit RST:1;                 /**< \brief [0:0] Kernel Reset (rwh) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_GTM_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_GTM_KRSTCLR_Bits
{
    Ifx_Strict_32Bit CLR:1;                 /**< \brief [0:0] Kernel Reset Status Clear (w) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_GTM_KRSTCLR_Bits;

/** \brief  MAP Control Register */
typedef struct _Ifx_GTM_MAP_CTRL_Bits
{
    Ifx_Strict_32Bit TSEL:1;                /**< \brief [0:0] TRIGGER signal output select. (rw) */
    Ifx_Strict_32Bit SSL:3;                 /**< \brief [3:1] STATE signal output select. (rw) */
    Ifx_Strict_32Bit LSEL:1;                /**< \brief [4:4] TIM0_IN6 input level selection (rw) */
    Ifx_Strict_32Bit reserved_5:11;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TSPP0_EN:1;            /**< \brief [16:16] Enable of TSPP0 subunit (rw) */
    Ifx_Strict_32Bit TSPP0_DLD:1;           /**< \brief [17:17] DIR level definition bit (rw) */
    Ifx_Strict_32Bit reserved_18:2;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TSPP0_I0V:1;           /**< \brief [20:20] Disable of TSPP0 TIM0_CHx(48) input line. (rw) */
    Ifx_Strict_32Bit TSPP0_I1V:1;           /**< \brief [21:21] Disable of TSPP0 TIM0_CHy(48) input line. (rw) */
    Ifx_Strict_32Bit TSPP0_I2V:1;           /**< \brief [22:22] Disable of TSPP0 TIM0_CHz(48) input line. (rw) */
    Ifx_Strict_32Bit reserved_23:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TSPP1_EN:1;            /**< \brief [24:24] Enable of TSPP1 subunit (rw) */
    Ifx_Strict_32Bit TSPP1_DLD:1;           /**< \brief [25:25] DIR level definition bit (rw) */
    Ifx_Strict_32Bit reserved_26:2;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TSPP1_I0V:1;           /**< \brief [28:28] Disable of TSPP1 TIM0_CHx(48) input line (rw) */
    Ifx_Strict_32Bit TSPP1_I1V:1;           /**< \brief [29:29] Disable of TSPP1 TIM0_CHy(48) input line (rw) */
    Ifx_Strict_32Bit TSPP1_I2V:1;           /**< \brief [30:30] Disable of TSPP1 TIM0_CHz(48) input line. (rw) */
    Ifx_Strict_32Bit reserved_31:1;         /**< \brief \internal Reserved */
} Ifx_GTM_MAP_CTRL_Bits;

/** \brief  Memory Layout Configuration Register */
typedef struct _Ifx_GTM_MCFG_CTRL_Bits
{
    Ifx_Strict_32Bit MEM0:2;                /**< \brief [1:0] Configure Memory pages for MCS-instance MCS0 (rw) */
    Ifx_Strict_32Bit MEM1:2;                /**< \brief [3:2] Configure Memory pages for MCS-instance MCS1 (rw) */
    Ifx_Strict_32Bit MEM2:2;                /**< \brief [5:4] Configure Memory pages for MCS-instance MCS2 (rw) */
    Ifx_Strict_32Bit reserved_6:26;         /**< \brief \internal Reserved */
} Ifx_GTM_MCFG_CTRL_Bits;

/** \brief  MCS Clear Trigger Control Register */
typedef struct _Ifx_GTM_MCS_CH0_CTRG_Bits
{
    Ifx_Strict_32Bit TRG0:1;                /**< \brief [0:0] Trigger bit 0 (rw) */
    Ifx_Strict_32Bit TRG1:1;                /**< \brief [1:1] Trigger bit 1 (rw) */
    Ifx_Strict_32Bit TRG2:1;                /**< \brief [2:2] Trigger bit 2 (rw) */
    Ifx_Strict_32Bit TRG3:1;                /**< \brief [3:3] Trigger bit 3 (rw) */
    Ifx_Strict_32Bit TRG4:1;                /**< \brief [4:4] Trigger bit 4 (rw) */
    Ifx_Strict_32Bit TRG5:1;                /**< \brief [5:5] Trigger bit 5 (rw) */
    Ifx_Strict_32Bit TRG6:1;                /**< \brief [6:6] Trigger bit 6 (rw) */
    Ifx_Strict_32Bit TRG7:1;                /**< \brief [7:7] Trigger bit 7 (rw) */
    Ifx_Strict_32Bit TRG8:1;                /**< \brief [8:8] Trigger bit 8 (rw) */
    Ifx_Strict_32Bit TRG9:1;                /**< \brief [9:9] Trigger bit 9 (rw) */
    Ifx_Strict_32Bit TRG10:1;               /**< \brief [10:10] Trigger bit 10 (rw) */
    Ifx_Strict_32Bit TRG11:1;               /**< \brief [11:11] Trigger bit 11 (rw) */
    Ifx_Strict_32Bit TRG12:1;               /**< \brief [12:12] Trigger bit 12 (rw) */
    Ifx_Strict_32Bit TRG13:1;               /**< \brief [13:13] Trigger bit 13 (rw) */
    Ifx_Strict_32Bit TRG14:1;               /**< \brief [14:14] Trigger bit 14 (rw) */
    Ifx_Strict_32Bit TRG15:1;               /**< \brief [15:15] Trigger bit 15 (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH0_CTRG_Bits;

/** \brief  MCS Set Trigger Control Register */
typedef struct _Ifx_GTM_MCS_CH0_STRG_Bits
{
    Ifx_Strict_32Bit TRG0:1;                /**< \brief [0:0] Trigger bit 0 (rw) */
    Ifx_Strict_32Bit TRG1:1;                /**< \brief [1:1] Trigger bit 1 (rw) */
    Ifx_Strict_32Bit TRG2:1;                /**< \brief [2:2] Trigger bit 2 (rw) */
    Ifx_Strict_32Bit TRG3:1;                /**< \brief [3:3] Trigger bit 3 (rw) */
    Ifx_Strict_32Bit TRG4:1;                /**< \brief [4:4] Trigger bit 4 (rw) */
    Ifx_Strict_32Bit TRG5:1;                /**< \brief [5:5] Trigger bit 5 (rw) */
    Ifx_Strict_32Bit TRG6:1;                /**< \brief [6:6] Trigger bit 6 (rw) */
    Ifx_Strict_32Bit TRG7:1;                /**< \brief [7:7] Trigger bit 7 (rw) */
    Ifx_Strict_32Bit TRG8:1;                /**< \brief [8:8] trigger bit 8 (rw) */
    Ifx_Strict_32Bit TRG9:1;                /**< \brief [9:9] Trigger bit 9 (rw) */
    Ifx_Strict_32Bit TRG10:1;               /**< \brief [10:10] Trigger bit 10 (rw) */
    Ifx_Strict_32Bit TRG11:1;               /**< \brief [11:11] Trigger bit 11 (rw) */
    Ifx_Strict_32Bit TRG12:1;               /**< \brief [12:12] Trigger bit 12 (rw) */
    Ifx_Strict_32Bit TRG13:1;               /**< \brief [13:13] Trigger bit 13 (rw) */
    Ifx_Strict_32Bit TRG14:1;               /**< \brief [14:14] Trigger bit 14 (rw) */
    Ifx_Strict_32Bit TRG15:1;               /**< \brief [15:15] Trigger bit 15 (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH0_STRG_Bits;

/** \brief  MCS Channel ACB Register */
typedef struct _Ifx_GTM_MCS_CH_ACB_Bits
{
    Ifx_Strict_32Bit ACB0:1;                /**< \brief [0:0] ARU Control bit 0 (r) */
    Ifx_Strict_32Bit ACB1:1;                /**< \brief [1:1] ARU Control bit 1 (r) */
    Ifx_Strict_32Bit ACB2:1;                /**< \brief [2:2] ARU Control bit 2 (r) */
    Ifx_Strict_32Bit ACB3:1;                /**< \brief [3:3] ARU Control bit 3 (r) */
    Ifx_Strict_32Bit ACB4:1;                /**< \brief [4:4] ARU Control bit 4 (r) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_ACB_Bits;

/** \brief  MCS Channel Control Register */
typedef struct _Ifx_GTM_MCS_CH_CTRL_Bits
{
    Ifx_Strict_32Bit EN:1;                  /**< \brief [0:0] Enable MCS-channel (rw) */
    Ifx_Strict_32Bit IRQ:1;                 /**< \brief [1:1] Interrupt state (r) */
    Ifx_Strict_32Bit ERR:1;                 /**< \brief [2:2] Error state (r) */
    Ifx_Strict_32Bit reserved_3:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CY:1;                  /**< \brief [4:4] Carry bit state (r) */
    Ifx_Strict_32Bit Z:1;                   /**< \brief [5:5] Zero bit state (r) */
    Ifx_Strict_32Bit V:1;                   /**< \brief [6:6] Overflow bit state (r) */
    Ifx_Strict_32Bit N:1;                   /**< \brief [7:7] Negative bit state (r) */
    Ifx_Strict_32Bit CAT:1;                 /**< \brief [8:8] Cancel ARU transfer state (r) */
    Ifx_Strict_32Bit CWT:1;                 /**< \brief [9:9] Cancel WURM instruction state (r) */
    Ifx_Strict_32Bit reserved_10:6;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SP_CNT:3;              /**< \brief [18:16] Stack pointer counter value (r) */
    Ifx_Strict_32Bit reserved_19:13;        /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_CTRL_Bits;

/** \brief  MCS_Channel Error Interrupt Enable Register */
typedef struct _Ifx_GTM_MCS_CH_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit MCS_EIRQ_EN:1;         /**< \brief [0:0] MCS channel x MCS_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit STK_ERR_EIRQ_EN:1;     /**< \brief [1:1] MCS channel x STK_ERR_IRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit MEM_ERR_EIRQ_EN:1;     /**< \brief [2:2] MCS channel x MEM_ERR_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_EIRQ_EN_Bits;

/** \brief  MCS Channel Interrupt Enable Register */
typedef struct _Ifx_GTM_MCS_CH_IRQ_EN_Bits
{
    Ifx_Strict_32Bit MCS_IRQ_EN:1;          /**< \brief [0:0] MCS channel x MCS_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit STK_ERR_IRQ_EN:1;      /**< \brief [1:1] MCS channel x STK_ERR_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit MEM_ERR_IRQ_EN:1;      /**< \brief [2:2] MCS channel x MEM_ERR_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_IRQ_EN_Bits;

/** \brief  MCS Channel Software Interrupt Generation Register */
typedef struct _Ifx_GTM_MCS_CH_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_MCS_IRQ:1;         /**< \brief [0:0] Trigger IRQ bit in MCS_CH_x_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_STK_ERR_IRQ:1;     /**< \brief [1:1] Trigger IRQ bit in MCS_CH_x_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_MEM_ERR_IRQ:1;     /**< \brief [2:2] Trigger IRQ bit in MCS_CH_x_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_IRQ_FORCINT_Bits;

/** \brief  MCS IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_MCS_CH_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_IRQ_MODE_Bits;

/** \brief  MCS Channel interrupt notification register */
typedef struct _Ifx_GTM_MCS_CH_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit MCS_IRQ:1;             /**< \brief [0:0] Interrupt request by MCS-channel x (rwh) */
    Ifx_Strict_32Bit STK_ERR_IRQ:1;         /**< \brief [1:1] Stack counter overflow/underflow of channel x (rwh) */
    Ifx_Strict_32Bit MEM_ERR_IRQ:1;         /**< \brief [2:2] Memory access out of range in channel x (rwh) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_IRQ_NOTIFY_Bits;

/** \brief  MCS Channel Program Counter Register */
typedef struct _Ifx_GTM_MCS_CH_PC_Bits
{
    Ifx_Strict_32Bit PC:14;                 /**< \brief [13:0] Current Program Counter (rw) */
    Ifx_Strict_32Bit reserved_14:18;        /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_PC_Bits;

/** \brief  MCS Channel Program Counter Register 0 */
typedef struct _Ifx_GTM_MCS_CH_R0_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R0_Bits;

/** \brief  MCS Channel Program Counter Register 1 */
typedef struct _Ifx_GTM_MCS_CH_R1_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R1_Bits;

/** \brief  MCS Channel Program Counter Register 2 */
typedef struct _Ifx_GTM_MCS_CH_R2_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R2_Bits;

/** \brief  MCS Channel Program Counter Register 3 */
typedef struct _Ifx_GTM_MCS_CH_R3_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R3_Bits;

/** \brief  MCS Channel Program Counter Register 4 */
typedef struct _Ifx_GTM_MCS_CH_R4_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R4_Bits;

/** \brief  MCS Channel Program Counter Register 5 */
typedef struct _Ifx_GTM_MCS_CH_R5_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R5_Bits;

/** \brief  MCS Channel Program Counter Register 6 */
typedef struct _Ifx_GTM_MCS_CH_R6_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R6_Bits;

/** \brief  MCS Channel Program Counter Register 7 */
typedef struct _Ifx_GTM_MCS_CH_R7_Bits
{
    Ifx_Strict_32Bit DATA:24;               /**< \brief [23:0] Data of MCS general purpose register ry (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CH_R7_Bits;

/** \brief  MCS Control Register */
typedef struct _Ifx_GTM_MCS_CTRL_Bits
{
    Ifx_Strict_32Bit SCHED:1;               /**< \brief [0:0] MCS submodule scheduling scheme (rw) */
    Ifx_Strict_32Bit HLT_SP_OFL:1;          /**< \brief [1:1] Halt on stack pointer overflow (rw) */
    Ifx_Strict_32Bit reserved_2:14;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RAM_RST:1;             /**< \brief [16:16] RAM reset bit (r) */
    Ifx_Strict_32Bit reserved_17:15;        /**< \brief \internal Reserved */
} Ifx_GTM_MCS_CTRL_Bits;

/** \brief  MCS Error Register */
typedef struct _Ifx_GTM_MCS_ERR_Bits
{
    Ifx_Strict_32Bit ERR0:1;                /**< \brief [0:0] Error State of MCS-channel 0 (rwh) */
    Ifx_Strict_32Bit ERR1:1;                /**< \brief [1:1] Error State of MCS-channel 1 (rwh) */
    Ifx_Strict_32Bit ERR2:1;                /**< \brief [2:2] Error State of MCS-channel 2 (rwh) */
    Ifx_Strict_32Bit ERR3:1;                /**< \brief [3:3] Error State of MCS-channel3 (rwh) */
    Ifx_Strict_32Bit ERR4:1;                /**< \brief [4:4] Error State of MCS-channel 4 (rwh) */
    Ifx_Strict_32Bit ERR5:1;                /**< \brief [5:5] Error State of MCS-channel 5 (rwh) */
    Ifx_Strict_32Bit ERR6:1;                /**< \brief [6:6] Error State of MCS-channel 6 (rwh) */
    Ifx_Strict_32Bit ERR7:1;                /**< \brief [7:7] Error State of MCS-channel 7 (rwh) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_ERR_Bits;

/** \brief  MCS Channel Reset Register */
typedef struct _Ifx_GTM_MCS_RST_Bits
{
    Ifx_Strict_32Bit RST0:1;                /**< \brief [0:0] Software reset of channel 0 (w) */
    Ifx_Strict_32Bit RST1:1;                /**< \brief [1:1] Software reset of channel 1 (w) */
    Ifx_Strict_32Bit RST2:1;                /**< \brief [2:2] Software reset of channel 2 (w) */
    Ifx_Strict_32Bit RST3:1;                /**< \brief [3:3] Software reset of channel 3 (w) */
    Ifx_Strict_32Bit RST4:1;                /**< \brief [4:4] Software reset of channel 4 (w) */
    Ifx_Strict_32Bit RST5:1;                /**< \brief [5:5] Software reset of channel 5 (w) */
    Ifx_Strict_32Bit RST6:1;                /**< \brief [6:6] Software reset of channel 6 (w) */
    Ifx_Strict_32Bit RST7:1;                /**< \brief [7:7] Software reset of channel 7 (w) */
    Ifx_Strict_32Bit CAT0:1;                /**< \brief [8:8] Cancel ARU transfer for channel 0 (rwh) */
    Ifx_Strict_32Bit CAT1:1;                /**< \brief [9:9] Cancel ARU transfer for channel 1 (rwh) */
    Ifx_Strict_32Bit CAT2:1;                /**< \brief [10:10] Cancel ARU transfer for channel 2 (rwh) */
    Ifx_Strict_32Bit CAT3:1;                /**< \brief [11:11] Cancel ARU transfer for channel 3 (rwh) */
    Ifx_Strict_32Bit CAT4:1;                /**< \brief [12:12] Cancel ARU transfer for channel 4 (rwh) */
    Ifx_Strict_32Bit CAT5:1;                /**< \brief [13:13] Cancel ARU transfer for channel 5 (rwh) */
    Ifx_Strict_32Bit CAT6:1;                /**< \brief [14:14] Cancel ARU transfer for channel 6 (rwh) */
    Ifx_Strict_32Bit CAT7:1;                /**< \brief [15:15] Cancel ARU transfer for channel 7 (rwh) */
    Ifx_Strict_32Bit CWT0:1;                /**< \brief [16:16] Cancel WURM instruction for channel 0 (rwh) */
    Ifx_Strict_32Bit CWT1:1;                /**< \brief [17:17] Cancel WURM instruction for channel 1 (rwh) */
    Ifx_Strict_32Bit CWT2:1;                /**< \brief [18:18] Cancel WURM instruction for channel 2 (rwh) */
    Ifx_Strict_32Bit CWT3:1;                /**< \brief [19:19] Cancel WURM instruction for channel 3 (rwh) */
    Ifx_Strict_32Bit CWT4:1;                /**< \brief [20:20] Cancel WURM instruction for channel 4 (rwh) */
    Ifx_Strict_32Bit CWT5:1;                /**< \brief [21:21] Cancel WURM instruction for channel 5 (rwh) */
    Ifx_Strict_32Bit CWT6:1;                /**< \brief [22:22] Cancel WURM instruction for channel 6 (rwh) */
    Ifx_Strict_32Bit CWT7:1;                /**< \brief [23:23] Cancel WURM instruction for channel 7 (rwh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MCS_RST_Bits;

/** \brief  MCS Interrupt Clear Register */
typedef struct _Ifx_GTM_MCSINTCLR_Bits
{
    Ifx_Strict_32Bit MCS000:1;              /**< \brief [0:0] MCS0 RAM0 Interrupt 0 Status Clear (w) */
    Ifx_Strict_32Bit MCS001:1;              /**< \brief [1:1] MCS0 RAM0 Interrupt 1 Status Clear (w) */
    Ifx_Strict_32Bit MCS010:1;              /**< \brief [2:2] MCS0 RAM1 Interrupt 0 Status Clear (w) */
    Ifx_Strict_32Bit MCS011:1;              /**< \brief [3:3] MCS0 RAM1 Interrupt 1 Status Clear (w) */
    Ifx_Strict_32Bit MCS100:1;              /**< \brief [4:4] MCS1 RAM0 Interrupt 0 Status Clear (w) */
    Ifx_Strict_32Bit MCS101:1;              /**< \brief [5:5] MCS1 RAM0 Interrupt 1 Status Clear (w) */
    Ifx_Strict_32Bit MCS110:1;              /**< \brief [6:6] MCS1 RAM1 Interrupt 0 Status Clear (w) */
    Ifx_Strict_32Bit MCS111:1;              /**< \brief [7:7] MCS1 RAM1 Interrupt 1 Status Clear (w) */
    Ifx_Strict_32Bit MCS200:1;              /**< \brief [8:8] MCS2 RAM0 Interrupt 0 Status Clear (w) */
    Ifx_Strict_32Bit MCS201:1;              /**< \brief [9:9] MCS2 RAM0 Interrupt 1 Status Clear (w) */
    Ifx_Strict_32Bit MCS210:1;              /**< \brief [10:10] MCS2 RAM1 Interrupt 0 Status Clear (w) */
    Ifx_Strict_32Bit MCS211:1;              /**< \brief [11:11] MCS2 RAM1 Interrupt 1 Status Clear (w) */
    Ifx_Strict_32Bit reserved_12:20;        /**< \brief \internal Reserved */
} Ifx_GTM_MCSINTCLR_Bits;

/** \brief  MCS Interrupt Status Register */
typedef struct _Ifx_GTM_MCSINTSTAT_Bits
{
    Ifx_Strict_32Bit MCS000:1;              /**< \brief [0:0] MCS0 RAM0 Interrupt 0 Status (rh) */
    Ifx_Strict_32Bit MCS001:1;              /**< \brief [1:1] MCS0 RAM0 Interrupt 1 Status (rh) */
    Ifx_Strict_32Bit MCS010:1;              /**< \brief [2:2] MCS0 RAM1 Interrupt 0 Status (rh) */
    Ifx_Strict_32Bit MCS011:1;              /**< \brief [3:3] MCS0 RAM1 Interrupt 1 Status (rh) */
    Ifx_Strict_32Bit MCS100:1;              /**< \brief [4:4] MCS1 RAM0 Interrupt 0 Status (rh) */
    Ifx_Strict_32Bit MCS101:1;              /**< \brief [5:5] MCS1 RAM0 Interrupt 1 Status (rh) */
    Ifx_Strict_32Bit MCS110:1;              /**< \brief [6:6] MCS1 RAM1 Interrupt 0 Status (rh) */
    Ifx_Strict_32Bit MCS111:1;              /**< \brief [7:7] MCS1 RAM1 Interrupt 1 Status (rh) */
    Ifx_Strict_32Bit MCS200:1;              /**< \brief [8:8] MCS2 RAM0 Interrupt 0 Status (rh) */
    Ifx_Strict_32Bit MCS201:1;              /**< \brief [9:9] MCS2 RAM0 Interrupt 1 Status (rh) */
    Ifx_Strict_32Bit MCS210:1;              /**< \brief [10:10] MCS2 RAM1 Interrupt 0 Status (rh) */
    Ifx_Strict_32Bit MCS211:1;              /**< \brief [11:11] MCS2 RAM1 Interrupt 1 Status (rh) */
    Ifx_Strict_32Bit reserved_12:20;        /**< \brief \internal Reserved */
} Ifx_GTM_MCSINTSTAT_Bits;

/** \brief  Monitor Activity Register 0 */
typedef struct _Ifx_GTM_MON_ACTIVITY_0_Bits
{
    Ifx_Strict_32Bit MCA_0_0:1;             /**< \brief [0:0] Activity of check performed in module MCS0 at channel 0 (rwh) */
    Ifx_Strict_32Bit MCA_0_1:1;             /**< \brief [1:1] Activity of check performed in module MCS0 at channel 1 (rwh) */
    Ifx_Strict_32Bit MCA_0_2:1;             /**< \brief [2:2] Activity of check performed in module MCS0 at channel 2 (rwh) */
    Ifx_Strict_32Bit MCA_0_3:1;             /**< \brief [3:3] Activity of check performed in module MCS0 at channel 3 (rwh) */
    Ifx_Strict_32Bit MCA_0_4:1;             /**< \brief [4:4] Activity of check performed in module MCS0 at channel 4 (rwh) */
    Ifx_Strict_32Bit MCA_0_5:1;             /**< \brief [5:5] Activity of check performed in module MCS0 at channel 5 (rwh) */
    Ifx_Strict_32Bit MCA_0_6:1;             /**< \brief [6:6] Activity of check performed in module MCS0 at channel 6 (rwh) */
    Ifx_Strict_32Bit MCA_0_7:1;             /**< \brief [7:7] Activity of check performed in module MCS0 at channel 7 (rwh) */
    Ifx_Strict_32Bit MCA_1_0:1;             /**< \brief [8:8] Activity of check performed in module MCS1 at channel 0 (rwh) */
    Ifx_Strict_32Bit MCA_1_1:1;             /**< \brief [9:9] Activity of check performed in module MCS1 at channel 1 (rwh) */
    Ifx_Strict_32Bit MCA_1_2:1;             /**< \brief [10:10] Activity of check performed in module MCS1 at channel 2 (rwh) */
    Ifx_Strict_32Bit MCA_1_3:1;             /**< \brief [11:11] Activity of check performed in module MCS1 at channel 3 (rwh) */
    Ifx_Strict_32Bit MCA_1_4:1;             /**< \brief [12:12] Activity of check performed in module MCS1 at channel 4 (rwh) */
    Ifx_Strict_32Bit MCA_1_5:1;             /**< \brief [13:13] Activity of check performed in module MCS1 at channel 5 (rwh) */
    Ifx_Strict_32Bit MCA_1_6:1;             /**< \brief [14:14] Activity of check performed in module MCS1 at channel 6 (rwh) */
    Ifx_Strict_32Bit MCA_1_7:1;             /**< \brief [15:15] Activity of check performed in module MCS1 at channel 7 (rwh) */
    Ifx_Strict_32Bit MCA_2_0:1;             /**< \brief [16:16] Activity of check performed in module MCS2 at channel 0 (rwh) */
    Ifx_Strict_32Bit MCA_2_1:1;             /**< \brief [17:17] Activity of check performed in module MCS2 at channel 1 (rwh) */
    Ifx_Strict_32Bit MCA_2_2:1;             /**< \brief [18:18] Activity of check performed in module MCS2 at channel 2 (rwh) */
    Ifx_Strict_32Bit MCA_2_3:1;             /**< \brief [19:19] Activity of check performed in module MCS2 at channel 3 (rwh) */
    Ifx_Strict_32Bit MCA_2_4:1;             /**< \brief [20:20] Activity of check performed in module MCS2 at channel 4 (rwh) */
    Ifx_Strict_32Bit MCA_2_5:1;             /**< \brief [21:21] Activity of check performed in module MCS2 at channel 5 (rwh) */
    Ifx_Strict_32Bit MCA_2_6:1;             /**< \brief [22:22] Activity of check performed in module MCS2 at channel 6 (rwh) */
    Ifx_Strict_32Bit MCA_2_7:1;             /**< \brief [23:23] Activity of check performed in module MCS2 at channel 7 (rwh) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_MON_ACTIVITY_0_Bits;

/** \brief  Monitor Status Register */
typedef struct _Ifx_GTM_MON_STATUS_Bits
{
    Ifx_Strict_32Bit ACT_CMU0:1;            /**< \brief [0:0] CMU_CLK0 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMU1:1;            /**< \brief [1:1] CMU_CLK1 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMU2:1;            /**< \brief [2:2] CMU_CLK2 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMU3:1;            /**< \brief [3:3] CMU_CLK3 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMU4:1;            /**< \brief [4:4] CMU_CLK4 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMU5:1;            /**< \brief [5:5] CMU_CLK5 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMU6:1;            /**< \brief [6:6] CMU_CLK6 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMU7:1;            /**< \brief [7:7] CMU_CLK7 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMUFX0:1;          /**< \brief [8:8] CMU_CLKFX0 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMUFX1:1;          /**< \brief [9:9] CMU_CLKFX1 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMUFX2:1;          /**< \brief [10:10] CMU_CLKFX2 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMUFX3:1;          /**< \brief [11:11] CMU_CLKFX3 activity (rwh) */
    Ifx_Strict_32Bit ACT_CMUFX4:1;          /**< \brief [12:12] CMU_CLKFX4 activity (rwh) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CMP_ERR:1;             /**< \brief [16:16] Error detected at CMP (r) */
    Ifx_Strict_32Bit reserved_17:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit MCS0_ERR:1;            /**< \brief [20:20] Error detected at MCS[0] (r) */
    Ifx_Strict_32Bit MCS1_ERR:1;            /**< \brief [21:21] Error detected at MCS[1] (r) */
    Ifx_Strict_32Bit MCS2_ERR:1;            /**< \brief [22:22] Error detected at MCS[2] (r) */
    Ifx_Strict_32Bit reserved_23:9;         /**< \brief \internal Reserved */
} Ifx_GTM_MON_STATUS_Bits;

/** \brief  MSC0 Input Low Extended Control Register */
typedef struct _Ifx_GTM_MSC0INLEXTCON_Bits
{
    Ifx_Strict_32Bit SEL0:2;                /**< \brief [1:0] GTM MSC0 Low Extended 0 Output Selection (rw) */
    Ifx_Strict_32Bit SEL1:2;                /**< \brief [3:2] GTM MSC0 Low Extended 1 Output Selection (rw) */
    Ifx_Strict_32Bit SEL2:2;                /**< \brief [5:4] GTM MSC0 Low Extended 2 Output Selection (rw) */
    Ifx_Strict_32Bit SEL3:2;                /**< \brief [7:6] GTM MSC0 Low Extended 3 Output Selection (rw) */
    Ifx_Strict_32Bit SEL4:2;                /**< \brief [9:8] GTM MSC0 Low Extended 4 Output Selection (rw) */
    Ifx_Strict_32Bit SEL5:2;                /**< \brief [11:10] GTM MSC0 Low Extended 5 Output Selection (rw) */
    Ifx_Strict_32Bit SEL6:2;                /**< \brief [13:12] GTM MSC0 Low Extended 6 Output Selection (rw) */
    Ifx_Strict_32Bit SEL7:2;                /**< \brief [15:14] GTM MSC0 Low Extended 7 Output Selection (rw) */
    Ifx_Strict_32Bit SEL8:2;                /**< \brief [17:16] GTM MSC0 Low Extended 8 Output Selection (rw) */
    Ifx_Strict_32Bit SEL9:2;                /**< \brief [19:18] GTM MSC0 Low Extended 9 Output Selection (rw) */
    Ifx_Strict_32Bit SEL10:2;               /**< \brief [21:20] GTM MSC0 Low Extended 10 Output Selection (rw) */
    Ifx_Strict_32Bit SEL11:2;               /**< \brief [23:22] GTM MSC0 Low Extended 11 Output Selection (rw) */
    Ifx_Strict_32Bit SEL12:2;               /**< \brief [25:24] GTM MSC0 Low Extended 12 Output Selection (rw) */
    Ifx_Strict_32Bit SEL13:2;               /**< \brief [27:26] GTM MSC0 Low Extended 13 Output Selection (rw) */
    Ifx_Strict_32Bit SEL14:2;               /**< \brief [29:28] GTM MSC0 Low Extended 14 Output Selection (rw) */
    Ifx_Strict_32Bit SEL15:2;               /**< \brief [31:30] GTM MSC0 Low Extended 15 Output Selection (rw) */
} Ifx_GTM_MSC0INLEXTCON_Bits;

/** \brief  MSC Input High Control Register */
typedef struct _Ifx_GTM_MSCIN_INHCON_Bits
{
    Ifx_Strict_32Bit SEL0:2;                /**< \brief [1:0]  (rw) */
    Ifx_Strict_32Bit SEL1:2;                /**< \brief [3:2]  (rw) */
    Ifx_Strict_32Bit SEL2:2;                /**< \brief [5:4]  (rw) */
    Ifx_Strict_32Bit SEL3:2;                /**< \brief [7:6]  (rw) */
    Ifx_Strict_32Bit SEL4:2;                /**< \brief [9:8]  (rw) */
    Ifx_Strict_32Bit SEL5:2;                /**< \brief [11:10]  (rw) */
    Ifx_Strict_32Bit SEL6:2;                /**< \brief [13:12]  (rw) */
    Ifx_Strict_32Bit SEL7:2;                /**< \brief [15:14]  (rw) */
    Ifx_Strict_32Bit SEL8:2;                /**< \brief [17:16]  (rw) */
    Ifx_Strict_32Bit SEL9:2;                /**< \brief [19:18]  (rw) */
    Ifx_Strict_32Bit SEL10:2;               /**< \brief [21:20]  (rw) */
    Ifx_Strict_32Bit SEL11:2;               /**< \brief [23:22]  (rw) */
    Ifx_Strict_32Bit SEL12:2;               /**< \brief [25:24]  (rw) */
    Ifx_Strict_32Bit SEL13:2;               /**< \brief [27:26]  (rw) */
    Ifx_Strict_32Bit SEL14:2;               /**< \brief [29:28]  (rw) */
    Ifx_Strict_32Bit SEL15:2;               /**< \brief [31:30]  (rw) */
} Ifx_GTM_MSCIN_INHCON_Bits;

/** \brief  MSC Input Low Control Register */
typedef struct _Ifx_GTM_MSCIN_INLCON_Bits
{
    Ifx_Strict_32Bit SEL0:2;                /**< \brief [1:0]  (rw) */
    Ifx_Strict_32Bit SEL1:2;                /**< \brief [3:2]  (rw) */
    Ifx_Strict_32Bit SEL2:2;                /**< \brief [5:4]  (rw) */
    Ifx_Strict_32Bit SEL3:2;                /**< \brief [7:6]  (rw) */
    Ifx_Strict_32Bit SEL4:2;                /**< \brief [9:8]  (rw) */
    Ifx_Strict_32Bit SEL5:2;                /**< \brief [11:10]  (rw) */
    Ifx_Strict_32Bit SEL6:2;                /**< \brief [13:12]  (rw) */
    Ifx_Strict_32Bit SEL7:2;                /**< \brief [15:14]  (rw) */
    Ifx_Strict_32Bit SEL8:2;                /**< \brief [17:16]  (rw) */
    Ifx_Strict_32Bit SEL9:2;                /**< \brief [19:18]  (rw) */
    Ifx_Strict_32Bit SEL10:2;               /**< \brief [21:20]  (rw) */
    Ifx_Strict_32Bit SEL11:2;               /**< \brief [23:22]  (rw) */
    Ifx_Strict_32Bit SEL12:2;               /**< \brief [25:24]  (rw) */
    Ifx_Strict_32Bit SEL13:2;               /**< \brief [27:26]  (rw) */
    Ifx_Strict_32Bit SEL14:2;               /**< \brief [29:28]  (rw) */
    Ifx_Strict_32Bit SEL15:2;               /**< \brief [31:30]  (rw) */
} Ifx_GTM_MSCIN_INLCON_Bits;

/** \brief  MSC Set Control 0 Register */
typedef struct _Ifx_GTM_MSCSET_CON0_Bits
{
    Ifx_Strict_32Bit SEL0:5;                /**< \brief [4:0]  (rw) */
    Ifx_Strict_32Bit reserved_5:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL1:5;                /**< \brief [12:8]  (rw) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL2:5;                /**< \brief [20:16]  (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL3:5;                /**< \brief [28:24]  (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_MSCSET_CON0_Bits;

/** \brief  MSC Set Control 1 Register */
typedef struct _Ifx_GTM_MSCSET_CON1_Bits
{
    Ifx_Strict_32Bit SEL4:5;                /**< \brief [4:0]  (rw) */
    Ifx_Strict_32Bit reserved_5:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL5:5;                /**< \brief [12:8]  (rw) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL6:5;                /**< \brief [20:16]  (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL7:5;                /**< \brief [28:24]  (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_MSCSET_CON1_Bits;

/** \brief  MSC Set Control 2 Register */
typedef struct _Ifx_GTM_MSCSET_CON2_Bits
{
    Ifx_Strict_32Bit SEL8:5;                /**< \brief [4:0]  (rw) */
    Ifx_Strict_32Bit reserved_5:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL9:5;                /**< \brief [12:8]  (rw) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL10:5;               /**< \brief [20:16]  (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL11:5;               /**< \brief [28:24]  (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_MSCSET_CON2_Bits;

/** \brief  MSC Set Control 3 Register */
typedef struct _Ifx_GTM_MSCSET_CON3_Bits
{
    Ifx_Strict_32Bit SEL12:5;               /**< \brief [4:0]  (rw) */
    Ifx_Strict_32Bit reserved_5:3;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL13:5;               /**< \brief [12:8]  (rw) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL14:5;               /**< \brief [20:16]  (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SEL15:5;               /**< \brief [28:24]  (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_MSCSET_CON3_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_GTM_OCS_Bits
{
    Ifx_Strict_32Bit reserved_0:24;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SUS:4;                 /**< \brief [27:24] OCDS Suspend Control (rw) */
    Ifx_Strict_32Bit SUS_P:1;               /**< \brief [28:28] SUS Write Protection (w) */
    Ifx_Strict_32Bit SUSSTA:1;              /**< \brief [29:29] Suspend State (rh) */
    Ifx_Strict_32Bit reserved_30:2;         /**< \brief \internal Reserved */
} Ifx_GTM_OCS_Bits;

/** \brief  OCDS Debug Access Register */
typedef struct _Ifx_GTM_ODA_Bits
{
    Ifx_Strict_32Bit DDREN:1;               /**< \brief [0:0] Detructive Debug Read Enable (rw) */
    Ifx_Strict_32Bit DREN:1;                /**< \brief [1:1] Detructive Read Enable (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_ODA_Bits;

/** \brief  OCDS TBU0 Trigger Register */
typedef struct _Ifx_GTM_OTBU0T_Bits
{
    Ifx_Strict_32Bit CV:27;                 /**< \brief [26:0] Compare Value (rw) */
    Ifx_Strict_32Bit reserved_27:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit CM:2;                  /**< \brief [29:28] Compare Mode (rw) */
    Ifx_Strict_32Bit reserved_30:2;         /**< \brief \internal Reserved */
} Ifx_GTM_OTBU0T_Bits;

/** \brief  OCDS TBU1 Trigger Register */
typedef struct _Ifx_GTM_OTBU1T_Bits
{
    Ifx_Strict_32Bit CV:24;                 /**< \brief [23:0] Compare Value (rw) */
    Ifx_Strict_32Bit reserved_24:4;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit EN:1;                  /**< \brief [28:28] Enable (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_OTBU1T_Bits;

/** \brief  OCDS TBU2 Trigger Register */
typedef struct _Ifx_GTM_OTBU2T_Bits
{
    Ifx_Strict_32Bit CV:24;                 /**< \brief [23:0] Compare Value (rw) */
    Ifx_Strict_32Bit reserved_24:4;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit EN:1;                  /**< \brief [28:28] Enable (rw) */
    Ifx_Strict_32Bit reserved_29:3;         /**< \brief \internal Reserved */
} Ifx_GTM_OTBU2T_Bits;

/** \brief  OCDS Trigger Set Control 0 Register */
typedef struct _Ifx_GTM_OTSC0_Bits
{
    Ifx_Strict_32Bit B0LMT:3;               /**< \brief [2:0] OTGB0 TS16_IOS Low Byte Module Type (rw) */
    Ifx_Strict_32Bit reserved_3:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit B0LMI:4;               /**< \brief [7:4] OTGB0 TS16_IOS Low Byte Module Instance (rw) */
    Ifx_Strict_32Bit B0HMT:3;               /**< \brief [10:8] OTGB0 TS16_IOS High Byte Module Type (rw) */
    Ifx_Strict_32Bit reserved_11:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit B0HMI:4;               /**< \brief [15:12] OTGB0 TS16_IOS High Byte Module Instance (rw) */
    Ifx_Strict_32Bit B1LMT:3;               /**< \brief [18:16] OTGB1 TS16_IOS Low Byte Module Type (rw) */
    Ifx_Strict_32Bit reserved_19:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit B1LMI:4;               /**< \brief [23:20] OTGB1 TS16_IOS Low Byte Module Instance (rw) */
    Ifx_Strict_32Bit B1HMT:3;               /**< \brief [26:24] OTGB1 TS16_IOS High Byte Module Type (rw) */
    Ifx_Strict_32Bit reserved_27:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit B1HMI:4;               /**< \brief [31:28] OTGB1 TS16_IOS High Byte Module Instance (rw) */
} Ifx_GTM_OTSC0_Bits;

/** \brief  OCDS Trigger Set Control 1 Register */
typedef struct _Ifx_GTM_OTSC1_Bits
{
    Ifx_Strict_32Bit MCS:4;                 /**< \brief [3:0] MCS Channel Select (rw) */
    Ifx_Strict_32Bit MI:4;                  /**< \brief [7:4] MCS Instance (rw) */
    Ifx_Strict_32Bit reserved_8:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit MOE:1;                 /**< \brief [9:9] MCS Opcode Trace Enable (rw) */
    Ifx_Strict_32Bit reserved_10:22;        /**< \brief \internal Reserved */
} Ifx_GTM_OTSC1_Bits;

/** \brief  OCDS Trigger Set Select Register */
typedef struct _Ifx_GTM_OTSS_Bits
{
    Ifx_Strict_32Bit OTGB0:4;               /**< \brief [3:0] Trigger Set for OTGB0 (rw) */
    Ifx_Strict_32Bit reserved_4:4;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit OTGB1:4;               /**< \brief [11:8] Trigger Set for OTGB1 (rw) */
    Ifx_Strict_32Bit reserved_12:4;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit OTGB2:4;               /**< \brief [19:16] Trigger Set for OTGB2 (rw) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_GTM_OTSS_Bits;

/** \brief  GTM Version Control Register */
typedef struct _Ifx_GTM_REV_Bits
{
    Ifx_Strict_32Bit STEP:8;                /**< \brief [7:0] Release Step (r) */
    Ifx_Strict_32Bit NO:4;                  /**< \brief [11:8] Define delivery number of GTM specification (r) */
    Ifx_Strict_32Bit MINOR:4;               /**< \brief [15:12] Define minor version number of GTM specification (r) */
    Ifx_Strict_32Bit MAJOR:4;               /**< \brief [19:16] Define major version number of GTM specification (r) */
    Ifx_Strict_32Bit DEV_CODE0:4;           /**< \brief [23:20] Device encoding digit 0 (r) */
    Ifx_Strict_32Bit DEV_CODE1:4;           /**< \brief [27:24] Device encoding digit 1 (r) */
    Ifx_Strict_32Bit DEV_CODE2:4;           /**< \brief [31:28] Device encoding digit 2 (r) */
} Ifx_GTM_REV_Bits;

/** \brief  GTM Global Reset Register */
typedef struct _Ifx_GTM_RST_Bits
{
    Ifx_Strict_32Bit RST:1;                 /**< \brief [0:0] GTM Reset (w) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_GTM_RST_Bits;

/** \brief  SPE Revolution Compare Register */
typedef struct _Ifx_GTM_SPE_CMP_Bits
{
    Ifx_Strict_32Bit CMP:24;                /**< \brief [23:0] Input signal revolution counter compare value (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_SPE_CMP_Bits;

/** \brief  SPE Revolution Counter Register */
typedef struct _Ifx_GTM_SPE_CNT_Bits
{
    Ifx_Strict_32Bit CNT:24;                /**< \brief [23:0] Input signal revolution counter (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_SPE_CNT_Bits;

/** \brief  SPE Control Status Register */
typedef struct _Ifx_GTM_SPE_CTRL_STAT_Bits
{
    Ifx_Strict_32Bit SPE_EN:1;              /**< \brief [0:0] SPE Submodule enable (rw) */
    Ifx_Strict_32Bit SIE0:1;                /**< \brief [1:1] SPE Input enable for TIM_CHx(48) (rw) */
    Ifx_Strict_32Bit SIE1:1;                /**< \brief [2:2] SPE Input enable for TIM_CHy(48) (rw) */
    Ifx_Strict_32Bit SIE2:1;                /**< \brief [3:3] SPE Input enable for TIM_CHz(48) (rw) */
    Ifx_Strict_32Bit TRIG_SEL:2;            /**< \brief [5:4] Select trigger input signal (rw) */
    Ifx_Strict_32Bit TIM_SEL:1;             /**< \brief [6:6] select TIM input signal (rw) */
    Ifx_Strict_32Bit FSOM:1;                /**< \brief [7:7] Fast Shut-Off Mode (rw) */
    Ifx_Strict_32Bit SPE_PAT_PTR:3;         /**< \brief [10:8] Pattern selector for TOM output signals (rw) */
    Ifx_Strict_32Bit reserved_11:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit AIP:3;                 /**< \brief [14:12] Actual input pattern that was detected by a regular input pattern change (rw) */
    Ifx_Strict_32Bit ADIR:1;                /**< \brief [15:15] Actual rotation direction (rw) */
    Ifx_Strict_32Bit PIP:3;                 /**< \brief [18:16] Previous input pattern that was detected by a regular input pattern change (rw) */
    Ifx_Strict_32Bit PDIR:1;                /**< \brief [19:19] Previous rotation direction (rw) */
    Ifx_Strict_32Bit NIP:3;                 /**< \brief [22:20] New input pattern that was detected (r) */
    Ifx_Strict_32Bit reserved_23:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit FSOL:8;                /**< \brief [31:24] Fast Shut-Off Level for TOM[i] channel 0 to 7 (rw) */
} Ifx_GTM_SPE_CTRL_STAT_Bits;

/** \brief  SPE Error Interrupt Enable Register */
typedef struct _Ifx_GTM_SPE_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit SPE_NIPD_EIRQ_EN:1;    /**< \brief [0:0] SPE_NIPD_EIRQ interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_DCHG_EIRQ_EN:1;    /**< \brief [1:1] SPE_DCHG_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_PERR_EIRQ_EN:1;    /**< \brief [2:2] SPE_PERR_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_BIS_EIRQ_EN:1;     /**< \brief [3:3] SPE_BIS_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_RCMP_EIRQ_EN:1;    /**< \brief [4:4] SPE_RCMP_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_GTM_SPE_EIRQ_EN_Bits;

/** \brief  SPE Interrupt Enable Register */
typedef struct _Ifx_GTM_SPE_IRQ_EN_Bits
{
    Ifx_Strict_32Bit SPE_NIPD_IRQ_EN:1;     /**< \brief [0:0] SPE_NIPD_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_DCHG_IRQ_EN:1;     /**< \brief [1:1] SPE_DCHG_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_PERR_IRQ_EN:1;     /**< \brief [2:2] SPE_PERR_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_BIS_IRQ_EN:1;      /**< \brief [3:3] SPE_BIS_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit SPE_RCMP_IRQ_EN:1;     /**< \brief [4:4] SPE_RCMP_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_GTM_SPE_IRQ_EN_Bits;

/** \brief  SPE Interrupt Generation by Software */
typedef struct _Ifx_GTM_SPE_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_SPE_NIPD:1;        /**< \brief [0:0] Force interrupt of SPE_NIPD (w) */
    Ifx_Strict_32Bit TRG_SPE_DCHG:1;        /**< \brief [1:1] Force interrupt of SPE_DCHG (w) */
    Ifx_Strict_32Bit TRG_SPE_PERR:1;        /**< \brief [2:2] Force interrupt of SPE_PERR (w) */
    Ifx_Strict_32Bit TRG_SPE_BIS:1;         /**< \brief [3:3] Force interrupt of SPE_BIS (w) */
    Ifx_Strict_32Bit TRG_SPE_RCMP:1;        /**< \brief [4:4] Force interrupt of SPE_RCMP (w) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_GTM_SPE_IRQ_FORCINT_Bits;

/** \brief  SPE IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_SPE_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_SPE_IRQ_MODE_Bits;

/** \brief  SPE Interrupt Notification Register */
typedef struct _Ifx_GTM_SPE_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit SPE_NIPD:1;            /**< \brief [0:0] New input pattern interrupt occurred (rwh) */
    Ifx_Strict_32Bit SPE_DCHG:1;            /**< \brief [1:1] SPE_DIR bit changed on behalf of new input pattern (rwh) */
    Ifx_Strict_32Bit SPE_PERR:1;            /**< \brief [2:2] Wrong or invalid pattern detected at input (rwh) */
    Ifx_Strict_32Bit SPE_BIS:1;             /**< \brief [3:3] Bouncing input signal detected (rwh) */
    Ifx_Strict_32Bit SPE_RCMP:1;            /**< \brief [4:4] SPE revolution counter match event (rwh) */
    Ifx_Strict_32Bit reserved_5:27;         /**< \brief \internal Reserved */
} Ifx_GTM_SPE_IRQ_NOTIFY_Bits;

/** \brief  SPE Output Control Register */
typedef struct _Ifx_GTM_SPE_OUT_CTRL_Bits
{
    Ifx_Strict_32Bit SPE_OUT_CTRL:16;       /**< \brief [15:0] SPE output control value for TOM_CH0 to TOM_CH7 (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_SPE_OUT_CTRL_Bits;

/** \brief  SPE Output Definition Register */
typedef struct _Ifx_GTM_SPE_OUT_PAT_Bits
{
    Ifx_Strict_32Bit SPE_OUT_PAT:16;        /**< \brief [15:0] SPE output control value for TOM_CH0 to TOM_CH7 (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_SPE_OUT_PAT_Bits;

/** \brief  SPE Input Pattern Definition Register */
typedef struct _Ifx_GTM_SPE_PAT_Bits
{
    Ifx_Strict_32Bit IP0_VAL:1;             /**< \brief [0:0] Input pattern 0 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP0_PAT:3;             /**< \brief [3:1] Input pattern 0 (rw) */
    Ifx_Strict_32Bit IP1_VAL:1;             /**< \brief [4:4] Input pattern 1 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP1_PAT:3;             /**< \brief [7:5] Input pattern 1 (rw) */
    Ifx_Strict_32Bit IP2_VAL:1;             /**< \brief [8:8] Input pattern 2 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP2_PAT:3;             /**< \brief [11:9] Input pattern 2 (rw) */
    Ifx_Strict_32Bit IP3_VAL:1;             /**< \brief [12:12] Input pattern 3 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP3_PAT:3;             /**< \brief [15:13] Input pattern 3 (rw) */
    Ifx_Strict_32Bit IP4_VAL:1;             /**< \brief [16:16] Input pattern 4 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP4_PAT:3;             /**< \brief [19:17] Input pattern 4 (rw) */
    Ifx_Strict_32Bit IP5_VAL:1;             /**< \brief [20:20] Input pattern 5 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP5_PAT:3;             /**< \brief [23:21] Input pattern 5 (rw) */
    Ifx_Strict_32Bit IP6_VAL:1;             /**< \brief [24:24] Input pattern 6 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP6_PAT:3;             /**< \brief [27:25] Input pattern 6 (rw) */
    Ifx_Strict_32Bit IP7_VAL:1;             /**< \brief [28:28] Input pattern 7 is a valid pattern (rw) */
    Ifx_Strict_32Bit IP7_PAT:3;             /**< \brief [31:29] Input pattern 7 (rw) */
} Ifx_GTM_SPE_PAT_Bits;

/** \brief  TBU Channel 0 Base Register */
typedef struct _Ifx_GTM_TBU_CH0_BASE_Bits
{
    Ifx_Strict_32Bit BASE:27;               /**< \brief [26:0] Time base value for channel 0 (rw) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_TBU_CH0_BASE_Bits;

/** \brief  TBU Channel 0 Control Register */
typedef struct _Ifx_GTM_TBU_CH0_CTRL_Bits
{
    Ifx_Strict_32Bit LOW_RES:1;             /**< \brief [0:0] TBU_CH0_BASE register resolution (rw) */
    Ifx_Strict_32Bit CH_CLK_SRC:3;          /**< \brief [3:1] Clock source for channel x (x:0...2) time base counter (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_TBU_CH0_CTRL_Bits;

/** \brief  TBU Channel 1 Base Register */
typedef struct _Ifx_GTM_TBU_CH1_BASE_Bits
{
    Ifx_Strict_32Bit BASE:24;               /**< \brief [23:0] Time base value for channel x (x 1, 2) (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_TBU_CH1_BASE_Bits;

/** \brief  TBU Channel 1 Control Register */
typedef struct _Ifx_GTM_TBU_CH1_CTRL_Bits
{
    Ifx_Strict_32Bit CH_MODE:1;             /**< \brief [0:0] Channel mode (rw) */
    Ifx_Strict_32Bit CH_CLK_SRC:3;          /**< \brief [3:1] Clock source for channel x (x1...2) time base counter (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_TBU_CH1_CTRL_Bits;

/** \brief  TBU Channel 2 Base Register */
typedef struct _Ifx_GTM_TBU_CH2_BASE_Bits
{
    Ifx_Strict_32Bit BASE:24;               /**< \brief [23:0] Time base value for channel x (x 1, 2) (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_TBU_CH2_BASE_Bits;

/** \brief  TBU Channel 2 Control Register */
typedef struct _Ifx_GTM_TBU_CH2_CTRL_Bits
{
    Ifx_Strict_32Bit CH_MODE:1;             /**< \brief [0:0] Channel mode (rw) */
    Ifx_Strict_32Bit CH_CLK_SRC:3;          /**< \brief [3:1] Clock source for channel x (x1...2) time base counter (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_GTM_TBU_CH2_CTRL_Bits;

/** \brief  TBU Global Channel Enable Register */
typedef struct _Ifx_GTM_TBU_CHEN_Bits
{
    Ifx_Strict_32Bit ENDIS_CH0:2;           /**< \brief [1:0] TBU channel 0 enable/disable control (rw) */
    Ifx_Strict_32Bit ENDIS_CH1:2;           /**< \brief [3:2] TBU channel 1 enable/disable control (rw) */
    Ifx_Strict_32Bit ENDIS_CH2:2;           /**< \brief [5:4] TBU channel 2 enable/disable control (rw) */
    Ifx_Strict_32Bit reserved_6:26;         /**< \brief \internal Reserved */
} Ifx_GTM_TBU_CHEN_Bits;

/** \brief  GTM TIM  AUX_IN_SRC */
typedef struct _Ifx_GTM_TIM_AUX_IN_SRC_Bits
{
    Ifx_Strict_32Bit SRC_CH0:1;             /**< \brief [0:0] Defines AUX_IN source of TIMi channel 0 x=0 (rw) */
    Ifx_Strict_32Bit SRC_CH1:1;             /**< \brief [1:1] Defines AUX_IN source of TIMi channel 1 x=1, see bit 0 (rw) */
    Ifx_Strict_32Bit SRC_CH2:1;             /**< \brief [2:2] Defines AUX_IN source of TIMi channel 2 x=2, see bit 0 (rw) */
    Ifx_Strict_32Bit SRC_CH3:1;             /**< \brief [3:3] Defines AUX_IN source of TIMi channel 3 x=3, see bit 0 (rw) */
    Ifx_Strict_32Bit SRC_CH4:1;             /**< \brief [4:4] Defines AUX_IN source of TIMi channel 4 x=4, see bit 0 (rw) */
    Ifx_Strict_32Bit SRC_CH5:1;             /**< \brief [5:5] Defines AUX_IN source of TIMi channel 5 x=5, see bit 0 (rw) */
    Ifx_Strict_32Bit SRC_CH6:1;             /**< \brief [6:6] Defines AUX_IN source of TIMi channel 6 x=6, see bit 0 (rw) */
    Ifx_Strict_32Bit SRC_CH7:1;             /**< \brief [7:7] Defines AUX_IN source of TIMi channel 7 x=7, see bit 0 (rw) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_AUX_IN_SRC_Bits;

/** \brief  TIM Channel SMU Counter Register */
typedef struct _Ifx_GTM_TIM_CH_CNT_Bits
{
    Ifx_Strict_32Bit CNT:24;                /**< \brief [23:0] Actual SMU counter value (r) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_CNT_Bits;

/** \brief  TIM Channel SMU Shadow Counter Register */
typedef struct _Ifx_GTM_TIM_CH_CNTS_Bits
{
    Ifx_Strict_32Bit CNTS:24;               /**< \brief [23:0] Counter shadow register (rw) */
    Ifx_Strict_32Bit ECNT:8;                /**< \brief [31:24] Edge counter (r) */
} Ifx_GTM_TIM_CH_CNTS_Bits;

/** \brief  TIM Channel Control Register */
typedef struct _Ifx_GTM_TIM_CH_CTRL_Bits
{
    Ifx_Strict_32Bit TIM_EN:1;              /**< \brief [0:0] TIM channel x (x:0...7) enable (rwh) */
    Ifx_Strict_32Bit TIM_MODE:3;            /**< \brief [3:1] TIM channel x (x:0...7) mode (rw) */
    Ifx_Strict_32Bit OSM:1;                 /**< \brief [4:4] One-shot mode (rw) */
    Ifx_Strict_32Bit ARU_EN:1;              /**< \brief [5:5] GPR0 and GPR1 register values routed to ARU (rw) */
    Ifx_Strict_32Bit CICTRL:1;              /**< \brief [6:6] Channel Input Control (rw) */
    Ifx_Strict_32Bit TBU0_SEL:1;            /**< \brief [7:7] TBU_TS0 bits input select for TIM_CH[x]_GPRz (z: 0, 1) (rw) */
    Ifx_Strict_32Bit GPR0_SEL:2;            /**< \brief [9:8] Selection for GPR0 register (rw) */
    Ifx_Strict_32Bit GPR1_SEL:2;            /**< \brief [11:10] Selection for GPR1 register (rw) */
    Ifx_Strict_32Bit CNTS_SEL:1;            /**< \brief [12:12] Selection for CNTS register (rw) */
    Ifx_Strict_32Bit DSL:1;                 /**< \brief [13:13] Signal level control (rw) */
    Ifx_Strict_32Bit ISL:1;                 /**< \brief [14:14] Ignore signal level (rw) */
    Ifx_Strict_32Bit ECNT_RESET:1;          /**< \brief [15:15] Enables resetting the ECNT counter in periodic sampling mode (rw) */
    Ifx_Strict_32Bit FLT_EN:1;              /**< \brief [16:16] Filter enable for channel x (x:0...7) (rw) */
    Ifx_Strict_32Bit FLT_CNT_FRQ:2;         /**< \brief [18:17] Filter counter frequency select (rw) */
    Ifx_Strict_32Bit EXT_CAP_EN:1;          /**< \brief [19:19] Enables external capture mode (rw) */
    Ifx_Strict_32Bit FLT_MODE_RE:1;         /**< \brief [20:20] Filter mode for rising edge (rw) */
    Ifx_Strict_32Bit FLT_CTR_RE:1;          /**< \brief [21:21] Filter counter mode for rising edge (rw) */
    Ifx_Strict_32Bit FLT_MODE_FE:1;         /**< \brief [22:22] Filter mode for falling edge (rw) */
    Ifx_Strict_32Bit FLT_CTR_FE:1;          /**< \brief [23:23] Filter counter mode for falling edge (rw) */
    Ifx_Strict_32Bit CLK_SEL:3;             /**< \brief [26:24] CMU clock source select for channel (rw) */
    Ifx_Strict_32Bit FR_ECNT_OFL:1;         /**< \brief [27:27] Extended Edge counter overflow behaviour (rw) */
    Ifx_Strict_32Bit EGPR0_SEL:1;           /**< \brief [28:28] Extension of GPR0_SEL bit field (rw) */
    Ifx_Strict_32Bit EGPR1_SEL:1;           /**< \brief [29:29] Extension of GPR1_SEL bit field (rw) */
    Ifx_Strict_32Bit TOCTRL:2;              /**< \brief [31:30] Timeout control (rw) */
} Ifx_GTM_TIM_CH_CTRL_Bits;

/** \brief  TIM Channel Edge Counter Register */
typedef struct _Ifx_GTM_TIM_CH_ECNT_Bits
{
    Ifx_Strict_32Bit ECNT:16;               /**< \brief [15:0] Edge counter (rh) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_ECNT_Bits;

/** \brief  TIM Channel External Capture Control Register */
typedef struct _Ifx_GTM_TIM_CH_ECTRL_Bits
{
    Ifx_Strict_32Bit EXT_CAP_SRC:3;         /**< \brief [2:0] Defines selected source for triggering the EXT_CAPTURE functionality (rw) */
    Ifx_Strict_32Bit reserved_3:29;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_ECTRL_Bits;

/** \brief  TIM Channel Error Interrupt Enable Register */
typedef struct _Ifx_GTM_TIM_CH_EIRQ_EN_Bits
{
    Ifx_Strict_32Bit NEWVAL_EIRQ_EN:1;      /**< \brief [0:0] TIM_NEWVALx_EIRQ error interrupt enable (rw) */
    Ifx_Strict_32Bit ECNTOFL_EIRQ_EN:1;     /**< \brief [1:1] TIM_ECNTOFLx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit CNTOFL_EIRQ_EN:1;      /**< \brief [2:2] TIM_CNTOFLx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit GPROFL_EIRQ_EN:1;      /**< \brief [3:3] TIM_GPROFL_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit TODET_EIRQ_EN:1;       /**< \brief [4:4] TIM_TODETx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit GLITCHDET_EIRQ_EN:1;   /**< \brief [5:5] TIM_GLITCHDETx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_6:26;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_EIRQ_EN_Bits;

/** \brief  TIM Channel Filter Parameter 1 Register */
typedef struct _Ifx_GTM_TIM_CH_FLT_FE_Bits
{
    Ifx_Strict_32Bit FLT_FE:24;             /**< \brief [23:0] Filter parameter for falling edge (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_FLT_FE_Bits;

/** \brief  GTM_TIM Channel Filter Parameter 0 Register */
typedef struct _Ifx_GTM_TIM_CH_FLT_RE_Bits
{
    Ifx_Strict_32Bit FLT_RE:24;             /**< \brief [23:0] Filter parameter for rising edge (rw) */
    Ifx_Strict_32Bit reserved_24:8;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_FLT_RE_Bits;

/** \brief  TIM Channel General Purpose 0 Register */
typedef struct _Ifx_GTM_TIM_CH_GPR0_Bits
{
    Ifx_Strict_32Bit GPR0:24;               /**< \brief [23:0] Input signal characteristic parameter 0 (r) */
    Ifx_Strict_32Bit ECNT:8;                /**< \brief [31:24] Edge counter (r) */
} Ifx_GTM_TIM_CH_GPR0_Bits;

/** \brief  TIM Channel General Purpose 1 Register */
typedef struct _Ifx_GTM_TIM_CH_GPR1_Bits
{
    Ifx_Strict_32Bit GPR1:24;               /**< \brief [23:0] Input signal characteristic parameter 1 (r) */
    Ifx_Strict_32Bit ECNT:8;                /**< \brief [31:24] Edge counter (r) */
} Ifx_GTM_TIM_CH_GPR1_Bits;

/** \brief  TIM Channel Interrupt Enable Register */
typedef struct _Ifx_GTM_TIM_CH_IRQ_EN_Bits
{
    Ifx_Strict_32Bit NEWVAL_IRQ_EN:1;       /**< \brief [0:0] TIM_NEWVALx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit ECNTOFL_IRQ_EN:1;      /**< \brief [1:1] TIM_ECNTOFLx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit CNTOFL_IRQ_EN:1;       /**< \brief [2:2] TIM_CNTOFLx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit GPROFL_IRQ_EN:1;       /**< \brief [3:3] TIM_GPROFLx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit TODET_IRQ_EN:1;        /**< \brief [4:4] TIM_TODETx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit GLITCHDET_IRQ_EN:1;    /**< \brief [5:5] TIM_GLITCHDETx_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_6:26;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_IRQ_EN_Bits;

/** \brief  TIM Channel Software Interrupt Force Register */
typedef struct _Ifx_GTM_TIM_CH_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_NEWVAL:1;          /**< \brief [0:0] Trigger NEWVAL bit in TIM_CHx_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_ECNTOFL:1;         /**< \brief [1:1] Trigger ECNTOFL bit in TIM_CHx_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_CNTOFL:1;          /**< \brief [2:2] Trigger CNTOFL bit in TIM_CHx_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_GPROFL:1;          /**< \brief [3:3] Trigger GPROFL bit in TIM_CHx_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_TODET:1;           /**< \brief [4:4] Trigger TODET bit in TIM_CHx_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit TRG_GLITCHDET:1;       /**< \brief [5:5] Trigger GLITCHDET bit in TIM_CHx_IRQ_NOTIFY register by software (w) */
    Ifx_Strict_32Bit reserved_6:26;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_IRQ_FORCINT_Bits;

/** \brief  TIM IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_TIM_CH_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_IRQ_MODE_Bits;

/** \brief  TIM Channel Interrupt Notification Register */
typedef struct _Ifx_GTM_TIM_CH_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit NEWVAL:1;              /**< \brief [0:0] New measurement value detected by in channel x (x:0...7) (rwh) */
    Ifx_Strict_32Bit ECNTOFL:1;             /**< \brief [1:1] counter overflow of channel x, (x:0...7) (rwh) */
    Ifx_Strict_32Bit CNTOFL:1;              /**< \brief [2:2] SMU CNT counter overflow of channel x, (x:0...7) (rwh) */
    Ifx_Strict_32Bit GPROFL:1;              /**< \brief [3:3] GPR0 and GPR1 data overflow, old data not read out before new data has arrived at input pin, (x:0...7) (rwh) */
    Ifx_Strict_32Bit TODET:1;               /**< \brief [4:4] Timeout reached for input signal of channel x, (x:0...7) (rwh) */
    Ifx_Strict_32Bit GLITCHDET:1;           /**< \brief [5:5] Glitch detected on channel x, (x:0...7) (rwh) */
    Ifx_Strict_32Bit reserved_6:26;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_IRQ_NOTIFY_Bits;

/** \brief  TIM Channel TDUC Register */
typedef struct _Ifx_GTM_TIM_CH_TDUC_Bits
{
    Ifx_Strict_32Bit TO_CNT:8;              /**< \brief [7:0] Current Timeout value for channel x (rh) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_TDUC_Bits;

/** \brief  TIM Channel TDUV Register */
typedef struct _Ifx_GTM_TIM_CH_TDUV_Bits
{
    Ifx_Strict_32Bit TOV:8;                 /**< \brief [7:0] Time out duration for channel x (rw) */
    Ifx_Strict_32Bit reserved_8:20;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TCS:3;                 /**< \brief [30:28] Timeout Clock selection (rw) */
    Ifx_Strict_32Bit reserved_31:1;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_CH_TDUV_Bits;

/** \brief  TIM_IN_SRC Long Name */
typedef struct _Ifx_GTM_TIM_IN_SRC_Bits
{
    Ifx_Strict_32Bit VAL_0:2;               /**< \brief [1:0] Value to be fed to Channel 0 (rw) */
    Ifx_Strict_32Bit MODE_0:2;              /**< \brief [3:2] Input source to Channel 0 (rw) */
    Ifx_Strict_32Bit VAL_1:2;               /**< \brief [5:4] Value to be fed to Channel 1 (rw) */
    Ifx_Strict_32Bit MODE_1:2;              /**< \brief [7:6] Input source to Channel 1 (rw) */
    Ifx_Strict_32Bit VAL_2:2;               /**< \brief [9:8] Value to be fed to Channel 2 (rw) */
    Ifx_Strict_32Bit MODE_2:2;              /**< \brief [11:10] Input source to Channel 2 (rw) */
    Ifx_Strict_32Bit VAL_3:2;               /**< \brief [13:12] Value to be fed to Channel 3 (rw) */
    Ifx_Strict_32Bit MODE_3:2;              /**< \brief [15:14] Input source to Channel 3 (rw) */
    Ifx_Strict_32Bit VAL_4:2;               /**< \brief [17:16] Value to be fed to Channel 4 (rw) */
    Ifx_Strict_32Bit MODE_4:2;              /**< \brief [19:18] Input source to Channel 4 (rw) */
    Ifx_Strict_32Bit VAL_5:2;               /**< \brief [21:20] Value to be fed to Channel 5 (rw) */
    Ifx_Strict_32Bit MODE_5:2;              /**< \brief [23:22] Input source to Channel 5 (rw) */
    Ifx_Strict_32Bit VAL_6:2;               /**< \brief [25:24] Value to be fed to Channel 6 (rw) */
    Ifx_Strict_32Bit MODE_6:2;              /**< \brief [27:26] Input source to Channel 6 (rw) */
    Ifx_Strict_32Bit VAL_7:2;               /**< \brief [29:28] Value to be fed to Channel 7 (rw) */
    Ifx_Strict_32Bit MODE_7:2;              /**< \brief [31:30] Input source to Channel 7 (rw) */
} Ifx_GTM_TIM_IN_SRC_Bits;

/** \brief  TIM Global Software Reset Register */
typedef struct _Ifx_GTM_TIM_RST_Bits
{
    Ifx_Strict_32Bit RST_CH0:1;             /**< \brief [0:0] Software reset of channel 0 (w) */
    Ifx_Strict_32Bit RST_CH1:1;             /**< \brief [1:1] Software reset of channel 1 (w) */
    Ifx_Strict_32Bit RST_CH2:1;             /**< \brief [2:2] Software reset of channel 2 (w) */
    Ifx_Strict_32Bit RST_CH3:1;             /**< \brief [3:3] Software reset of channel 3 (w) */
    Ifx_Strict_32Bit RST_CH4:1;             /**< \brief [4:4] Software reset of channel 4 (w) */
    Ifx_Strict_32Bit RST_CH5:1;             /**< \brief [5:5] Software reset of channel 5 (w) */
    Ifx_Strict_32Bit RST_CH6:1;             /**< \brief [6:6] Software reset of channel 6 (w) */
    Ifx_Strict_32Bit RST_CH7:1;             /**< \brief [7:7] Software reset of channel 7 (w) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_GTM_TIM_RST_Bits;

/** \brief  TOM Channel CCU0 Compare Register */
typedef struct _Ifx_GTM_TOM_CH_CM0_Bits
{
    Ifx_Strict_32Bit CM0:16;                /**< \brief [15:0] TOM CCU0 compare register (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_CM0_Bits;

/** \brief  TOM Channel CCU1 Compare Register */
typedef struct _Ifx_GTM_TOM_CH_CM1_Bits
{
    Ifx_Strict_32Bit CM1:16;                /**< \brief [15:0] TOM CCU1 compare register (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_CM1_Bits;

/** \brief  TOM Channel CCU0 Counter Register */
typedef struct _Ifx_GTM_TOM_CH_CN0_Bits
{
    Ifx_Strict_32Bit CN0:16;                /**< \brief [15:0] TOM CCU0 counter register (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_CN0_Bits;

/** \brief  TOM Channel Control Register’ */
typedef struct _Ifx_GTM_TOM_CH_CTRL_Bits
{
    Ifx_Strict_32Bit reserved_0:11;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SL:1;                  /**< \brief [11:11] Signal level for duty cycle (rw) */
    Ifx_Strict_32Bit CLK_SRC_SR:3;          /**< \brief [14:12] Clock source select for channel (rw) */
    Ifx_Strict_32Bit reserved_15:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RST_CCU0:1;            /**< \brief [20:20] Reset source of CCU0 (rw) */
    Ifx_Strict_32Bit reserved_21:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit TRIGOUT:1;             /**< \brief [24:24] Trigger output selection (output signal TRIG_[x]) of module TOM_CH[x] (rw) */
    Ifx_Strict_32Bit reserved_25:1;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit OSM:1;                 /**< \brief [26:26] One-shot mode (rw) */
    Ifx_Strict_32Bit BITREV:1;              /**< \brief [27:27] Bit-reversing of output of counter register CN0 (rw) */
    Ifx_Strict_32Bit SPEM:1;                /**< \brief [28:28] SPE mode enable for channel (rw) */
    Ifx_Strict_32Bit GCM:1;                 /**< \brief [29:29] Gated Counter Mode enable (rw) */
    Ifx_Strict_32Bit reserved_30:2;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_CTRL_Bits;

/** \brief  TOM Channel Interrupt Enable Register */
typedef struct _Ifx_GTM_TOM_CH_IRQ_EN_Bits
{
    Ifx_Strict_32Bit CCU0TC_IRQ_EN:1;       /**< \brief [0:0] TOM_CCU0TC_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit CCU1TC_IRQ_EN:1;       /**< \brief [1:1] TOM_CCU1TC_IRQ interrupt enable (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_IRQ_EN_Bits;

/** \brief  TOM Channel Software Interrupt Generation Register */
typedef struct _Ifx_GTM_TOM_CH_IRQ_FORCINT_Bits
{
    Ifx_Strict_32Bit TRG_CCU0TC0:1;         /**< \brief [0:0] Trigger TOM_CCU0TC0_IRQ interrupt by software (w) */
    Ifx_Strict_32Bit TRG_CCU1TC0:1;         /**< \brief [1:1] Trigger TOM_CCU1TC0_IRQ interrupt by software (w) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_IRQ_FORCINT_Bits;

/** \brief  TOM IRQ Mode Configuration Register */
typedef struct _Ifx_GTM_TOM_CH_IRQ_MODE_Bits
{
    Ifx_Strict_32Bit IRQ_MODE:2;            /**< \brief [1:0] IRQ mode selection (rw) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_IRQ_MODE_Bits;

/** \brief  TOM Channel Interrupt Notification Register */
typedef struct _Ifx_GTM_TOM_CH_IRQ_NOTIFY_Bits
{
    Ifx_Strict_32Bit CCU0TC:1;              /**< \brief [0:0] CCU0 Trigger condition interrupt for channel x (rwh) */
    Ifx_Strict_32Bit CCU1TC:1;              /**< \brief [1:1] CCU1 Trigger condition interrupt for channel x (rwh) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_IRQ_NOTIFY_Bits;

/** \brief  TOM Channel CCU0 Compare Shadow Register */
typedef struct _Ifx_GTM_TOM_CH_SR0_Bits
{
    Ifx_Strict_32Bit SR0:16;                /**< \brief [15:0] TOM channel x shadow register SR0 for update of compare register CM0 (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_SR0_Bits;

/** \brief  TOM Channel CCU1 Compare Shadow Register */
typedef struct _Ifx_GTM_TOM_CH_SR1_Bits
{
    Ifx_Strict_32Bit SR1:16;                /**< \brief [15:0] TOM channel x shadow register SR1 for update of compare register CM1 (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_SR1_Bits;

/** \brief  TOM Channel Status Register */
typedef struct _Ifx_GTM_TOM_CH_STAT_Bits
{
    Ifx_Strict_32Bit OL:1;                  /**< \brief [0:0] Output level of output TOM_OUT(x) (r) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_CH_STAT_Bits;

/** \brief  TOM TGC0 Action Time Base Register */
typedef struct _Ifx_GTM_TOM_TGC0_ACT_TB_Bits
{
    Ifx_Strict_32Bit ACT_TB:24;             /**< \brief [23:0] Time base value (rw) */
    Ifx_Strict_32Bit TB_TRIG:1;             /**< \brief [24:24] Set trigger request (rwh) */
    Ifx_Strict_32Bit TBU_SEL:2;             /**< \brief [26:25] Selection of time base used for comparison (rw) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC0_ACT_TB_Bits;

/** \brief  TOM TGC0 Enable/Disable Control Register */
typedef struct _Ifx_GTM_TOM_TGC0_ENDIS_CTRL_Bits
{
    Ifx_Strict_32Bit ENDIS_CTRL0:2;         /**< \brief [1:0] (A)TOM channel 0 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL1:2;         /**< \brief [3:2] (A)TOM channel 1 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL2:2;         /**< \brief [5:4] (A)TOM channel 2 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL3:2;         /**< \brief [7:6] (A)TOM channel 3 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL4:2;         /**< \brief [9:8] (A)TOM channel 4 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL5:2;         /**< \brief [11:10] (A)TOM channel 5 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL6:2;         /**< \brief [13:12] (A)TOM channel 6 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL7:2;         /**< \brief [15:14] (A)TOM channel 7 enable/disable update value (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC0_ENDIS_CTRL_Bits;

/** \brief  TOM TGC0 Enable/Disable Status Register */
typedef struct _Ifx_GTM_TOM_TGC0_ENDIS_STAT_Bits
{
    Ifx_Strict_32Bit ENDIS_STAT0:2;         /**< \brief [1:0] (A)TOM channel 0 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT1:2;         /**< \brief [3:2] (A)TOM channel 1 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT2:2;         /**< \brief [5:4] (A)TOM channel 2 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT3:2;         /**< \brief [7:6] (A)TOM channel 3 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT4:2;         /**< \brief [9:8] (A)TOM channel 4 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT5:2;         /**< \brief [11:10] (A)TOM channel 5 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT6:2;         /**< \brief [13:12] (A)TOM channel 6 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT7:2;         /**< \brief [15:14] (A)TOM channel 7 enable/disable (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC0_ENDIS_STAT_Bits;

/** \brief  TOM TGC0 Force Update Control Register */
typedef struct _Ifx_GTM_TOM_TGC0_FUPD_CTRL_Bits
{
    Ifx_Strict_32Bit FUPD_CTRL0:2;          /**< \brief [1:0] Force update of (A)TOM channel 0 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL1:2;          /**< \brief [3:2] Force update of (A)TOM channel 1 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL2:2;          /**< \brief [5:4] Force update of (A)TOM channel 2 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL3:2;          /**< \brief [7:6] Force update of (A)TOM channel 3 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL4:2;          /**< \brief [9:8] Force update of (A)TOM channel 4 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL5:2;          /**< \brief [11:10] Force update of (A)TOM channel 5 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL6:2;          /**< \brief [13:12] Force update of (A)TOM channel 6 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL7:2;          /**< \brief [15:14] Force update of (A)TOM channel 7 operation registers (rw) */
    Ifx_Strict_32Bit RSTCN0_CH0:2;          /**< \brief [17:16] Reset CN0 of channel 0 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH1:2;          /**< \brief [19:18] Reset CN0 of channel 1 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH2:2;          /**< \brief [21:20] Reset CN0 of channel 2 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH3:2;          /**< \brief [23:22] Reset CN0 of channel 3 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH4:2;          /**< \brief [25:24] Reset CN0 of channel 4 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH5:2;          /**< \brief [27:26] Reset CN0 of channel 5 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH6:2;          /**< \brief [29:28] Reset CN0 of channel 6 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH7:2;          /**< \brief [31:30] Reset CN0 of channel 7 on force update event (rw) */
} Ifx_GTM_TOM_TGC0_FUPD_CTRL_Bits;

/** \brief  TOM TGC0 Global Control Register */
typedef struct _Ifx_GTM_TOM_TGC0_GLB_CTRL_Bits
{
    Ifx_Strict_32Bit HOST_TRIG:1;           /**< \brief [0:0] Trigger request signal (see TGC0, TGC1) to update the register ENDIS_STAT and OUTEN_STAT (w) */
    Ifx_Strict_32Bit reserved_1:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RST_CH0:1;             /**< \brief [8:8] Software reset of channel 0 (w) */
    Ifx_Strict_32Bit RST_CH1:1;             /**< \brief [9:9] Software reset of channel 1 (w) */
    Ifx_Strict_32Bit RST_CH2:1;             /**< \brief [10:10] Software reset of channel 2 (w) */
    Ifx_Strict_32Bit RST_CH3:1;             /**< \brief [11:11] Software reset of channel 3 (w) */
    Ifx_Strict_32Bit RST_CH4:1;             /**< \brief [12:12] Software reset of channel 4 (w) */
    Ifx_Strict_32Bit RST_CH5:1;             /**< \brief [13:13] Software reset of channel 5 (w) */
    Ifx_Strict_32Bit RST_CH6:1;             /**< \brief [14:14] Software reset of channel 6 (w) */
    Ifx_Strict_32Bit RST_CH7:1;             /**< \brief [15:15] Software reset of channel 7 (w) */
    Ifx_Strict_32Bit UPEN_CTRL0:2;          /**< \brief [17:16] TOM channel 0 enable update of register CM0, CM1 and CLK_SRC from SR0, SR1 and CLK_SRC_SR (rw) */
    Ifx_Strict_32Bit UPEN_CTRL1:2;          /**< \brief [19:18] TOM channel 1 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL2:2;          /**< \brief [21:20] TOM channel 2 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL3:2;          /**< \brief [23:22] TOM channel 3 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL4:2;          /**< \brief [25:24] TOM channel 4 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL5:2;          /**< \brief [27:26] TOM channel 5 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL6:2;          /**< \brief [29:28] TOM channel 6 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL7:2;          /**< \brief [31:30] TOM channel 7 enable update of register CM0, CM1 and CLK_SRC (rw) */
} Ifx_GTM_TOM_TGC0_GLB_CTRL_Bits;

/** \brief  TOM TGC0 Internal Trigger Control Register */
typedef struct _Ifx_GTM_TOM_TGC0_INT_TRIG_Bits
{
    Ifx_Strict_32Bit INT_TRIG0:2;           /**< \brief [1:0] Select input signal TRIG_0 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG1:2;           /**< \brief [3:2] Select input signal TRIG_1 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG2:2;           /**< \brief [5:4] Select input signal TRIG_2 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG3:2;           /**< \brief [7:6] Select input signal TRIG_3 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG4:2;           /**< \brief [9:8] Select input signal TRIG_4 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG5:2;           /**< \brief [11:10] Select input signal TRIG_5 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG6:2;           /**< \brief [13:12] Select input signal TRIG_6 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG7:2;           /**< \brief [15:14] Select input signal TRIG_7 as a trigger source (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC0_INT_TRIG_Bits;

/** \brief  TOM TGC0 Output Enable Control Register */
typedef struct _Ifx_GTM_TOM_TGC0_OUTEN_CTRL_Bits
{
    Ifx_Strict_32Bit OUTEN_CTRL0:2;         /**< \brief [1:0] Output (A)TOM_OUT(0) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL1:2;         /**< \brief [3:2] Output (A)TOM_OUT(1)enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL2:2;         /**< \brief [5:4] Output (A)TOM_OUT(2) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL3:2;         /**< \brief [7:6] Output (A)TOM_OUT(3) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL4:2;         /**< \brief [9:8] Output (A)TOM_OUT(4) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL5:2;         /**< \brief [11:10] Output (A)TOM_OUT(5) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL6:2;         /**< \brief [13:12] Output (A)TOM_OUT(6) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL7:2;         /**< \brief [15:14] Output (A)TOM_OUT(7) enable/disable update value (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC0_OUTEN_CTRL_Bits;

/** \brief  TOM TGC0 Output Enable Status Register */
typedef struct _Ifx_GTM_TOM_TGC0_OUTEN_STAT_Bits
{
    Ifx_Strict_32Bit OUTEN_STAT0:2;         /**< \brief [1:0] Control/status of output (A)TOM_OUT(0) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT1:2;         /**< \brief [3:2] Control/status of output (A)TOM_OUT(1) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT2:2;         /**< \brief [5:4] Control/status of output (A)TOM_OUT(2) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT3:2;         /**< \brief [7:6] Control/status of output (A)TOM_OUT(3) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT4:2;         /**< \brief [9:8] Control/status of output (A)TOM_OUT(4) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT5:2;         /**< \brief [11:10] Control/status of output (A)TOM_OUT(5) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT6:2;         /**< \brief [13:12] Control/status of output (A)TOM_OUT(6) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT7:2;         /**< \brief [15:14] Control/status of output (A)TOM_OUT(7) (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC0_OUTEN_STAT_Bits;

/** \brief  TOM TGC1 Action Time Base Register */
typedef struct _Ifx_GTM_TOM_TGC1_ACT_TB_Bits
{
    Ifx_Strict_32Bit ACT_TB:24;             /**< \brief [23:0] Time base value (rw) */
    Ifx_Strict_32Bit TB_TRIG:1;             /**< \brief [24:24] Set trigger request (rwh) */
    Ifx_Strict_32Bit TBU_SEL:2;             /**< \brief [26:25] Selection of time base used for comparison (rw) */
    Ifx_Strict_32Bit reserved_27:5;         /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC1_ACT_TB_Bits;

/** \brief  TOM TGC1 Enable/Disable Control Register */
typedef struct _Ifx_GTM_TOM_TGC1_ENDIS_CTRL_Bits
{
    Ifx_Strict_32Bit ENDIS_CTRL0:2;         /**< \brief [1:0] (A)TOM channel 0 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL1:2;         /**< \brief [3:2] (A)TOM channel 1 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL2:2;         /**< \brief [5:4] (A)TOM channel 2 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL3:2;         /**< \brief [7:6] (A)TOM channel 3 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL4:2;         /**< \brief [9:8] (A)TOM channel 4 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL5:2;         /**< \brief [11:10] (A)TOM channel 5 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL6:2;         /**< \brief [13:12] (A)TOM channel 6 enable/disable update value (rw) */
    Ifx_Strict_32Bit ENDIS_CTRL7:2;         /**< \brief [15:14] (A)TOM channel 7 enable/disable update value (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC1_ENDIS_CTRL_Bits;

/** \brief  TOM TGC1 Enable/Disable Status Register */
typedef struct _Ifx_GTM_TOM_TGC1_ENDIS_STAT_Bits
{
    Ifx_Strict_32Bit ENDIS_STAT0:2;         /**< \brief [1:0] (A)TOM channel 0 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT1:2;         /**< \brief [3:2] (A)TOM channel 1 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT2:2;         /**< \brief [5:4] (A)TOM channel 2 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT3:2;         /**< \brief [7:6] (A)TOM channel 3 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT4:2;         /**< \brief [9:8] (A)TOM channel 4 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT5:2;         /**< \brief [11:10] (A)TOM channel 5 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT6:2;         /**< \brief [13:12] (A)TOM channel 6 enable/disable (rw) */
    Ifx_Strict_32Bit ENDIS_STAT7:2;         /**< \brief [15:14] (A)TOM channel 7 enable/disable (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC1_ENDIS_STAT_Bits;

/** \brief  TOM TGC1 Force Update Control Register */
typedef struct _Ifx_GTM_TOM_TGC1_FUPD_CTRL_Bits
{
    Ifx_Strict_32Bit FUPD_CTRL0:2;          /**< \brief [1:0] Force update of (A)TOM channel 0 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL1:2;          /**< \brief [3:2] Force update of (A)TOM channel 1 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL2:2;          /**< \brief [5:4] Force update of (A)TOM channel 2 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL3:2;          /**< \brief [7:6] Force update of (A)TOM channel 3 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL4:2;          /**< \brief [9:8] Force update of (A)TOM channel 4 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL5:2;          /**< \brief [11:10] Force update of (A)TOM channel 5 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL6:2;          /**< \brief [13:12] Force update of (A)TOM channel 6 operation registers (rw) */
    Ifx_Strict_32Bit FUPD_CTRL7:2;          /**< \brief [15:14] Force update of (A)TOM channel 7 operation registers (rw) */
    Ifx_Strict_32Bit RSTCN0_CH0:2;          /**< \brief [17:16] Reset CN0 of channel 0 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH1:2;          /**< \brief [19:18] Reset CN0 of channel 1 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH2:2;          /**< \brief [21:20] Reset CN0 of channel 2 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH3:2;          /**< \brief [23:22] Reset CN0 of channel 3 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH4:2;          /**< \brief [25:24] Reset CN0 of channel 4 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH5:2;          /**< \brief [27:26] Reset CN0 of channel 5 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH6:2;          /**< \brief [29:28] Reset CN0 of channel 6 on force update event (rw) */
    Ifx_Strict_32Bit RSTCN0_CH7:2;          /**< \brief [31:30] Reset CN0 of channel 7 on force update event (rw) */
} Ifx_GTM_TOM_TGC1_FUPD_CTRL_Bits;

/** \brief  TOM TGC1 Global Control Register */
typedef struct _Ifx_GTM_TOM_TGC1_GLB_CTRL_Bits
{
    Ifx_Strict_32Bit HOST_TRIG:1;           /**< \brief [0:0] Trigger request signal (see TGC0, TGC1) to update the register ENDIS_STAT and OUTEN_STAT (w) */
    Ifx_Strict_32Bit reserved_1:7;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RST_CH0:1;             /**< \brief [8:8] Software reset of channel 0 (w) */
    Ifx_Strict_32Bit RST_CH1:1;             /**< \brief [9:9] Software reset of channel 1 (w) */
    Ifx_Strict_32Bit RST_CH2:1;             /**< \brief [10:10] Software reset of channel 2 (w) */
    Ifx_Strict_32Bit RST_CH3:1;             /**< \brief [11:11] Software reset of channel 3 (w) */
    Ifx_Strict_32Bit RST_CH4:1;             /**< \brief [12:12] Software reset of channel 4 (w) */
    Ifx_Strict_32Bit RST_CH5:1;             /**< \brief [13:13] Software reset of channel 5 (w) */
    Ifx_Strict_32Bit RST_CH6:1;             /**< \brief [14:14] Software reset of channel 6 (w) */
    Ifx_Strict_32Bit RST_CH7:1;             /**< \brief [15:15] Software reset of channel 7 (w) */
    Ifx_Strict_32Bit UPEN_CTRL0:2;          /**< \brief [17:16] TOM channel 0 enable update of register CM0, CM1 and CLK_SRC from SR0, SR1 and CLK_SRC_SR (rw) */
    Ifx_Strict_32Bit UPEN_CTRL1:2;          /**< \brief [19:18] TOM channel 1 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL2:2;          /**< \brief [21:20] TOM channel 2 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL3:2;          /**< \brief [23:22] TOM channel 3 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL4:2;          /**< \brief [25:24] TOM channel 4 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL5:2;          /**< \brief [27:26] TOM channel 5 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL6:2;          /**< \brief [29:28] TOM channel 6 enable update of register CM0, CM1 and CLK_SRC (rw) */
    Ifx_Strict_32Bit UPEN_CTRL7:2;          /**< \brief [31:30] TOM channel 7 enable update of register CM0, CM1 and CLK_SRC (rw) */
} Ifx_GTM_TOM_TGC1_GLB_CTRL_Bits;

/** \brief  TOM TGC1 Internal Trigger Control Register */
typedef struct _Ifx_GTM_TOM_TGC1_INT_TRIG_Bits
{
    Ifx_Strict_32Bit INT_TRIG0:2;           /**< \brief [1:0] Select input signal TRIG_0 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG1:2;           /**< \brief [3:2] Select input signal TRIG_1 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG2:2;           /**< \brief [5:4] Select input signal TRIG_2 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG3:2;           /**< \brief [7:6] Select input signal TRIG_3 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG4:2;           /**< \brief [9:8] Select input signal TRIG_4 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG5:2;           /**< \brief [11:10] Select input signal TRIG_5 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG6:2;           /**< \brief [13:12] Select input signal TRIG_6 as a trigger source (rw) */
    Ifx_Strict_32Bit INT_TRIG7:2;           /**< \brief [15:14] Select input signal TRIG_7 as a trigger source (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC1_INT_TRIG_Bits;

/** \brief  TOM TGC1 Output Enable Control Register */
typedef struct _Ifx_GTM_TOM_TGC1_OUTEN_CTRL_Bits
{
    Ifx_Strict_32Bit OUTEN_CTRL0:2;         /**< \brief [1:0] Output (A)TOM_OUT(0) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL1:2;         /**< \brief [3:2] Output (A)TOM_OUT(1)enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL2:2;         /**< \brief [5:4] Output (A)TOM_OUT(2) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL3:2;         /**< \brief [7:6] Output (A)TOM_OUT(3) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL4:2;         /**< \brief [9:8] Output (A)TOM_OUT(4) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL5:2;         /**< \brief [11:10] Output (A)TOM_OUT(5) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL6:2;         /**< \brief [13:12] Output (A)TOM_OUT(6) enable/disable update value (rw) */
    Ifx_Strict_32Bit OUTEN_CTRL7:2;         /**< \brief [15:14] Output (A)TOM_OUT(7) enable/disable update value (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC1_OUTEN_CTRL_Bits;

/** \brief  TOM TGC1 Output Enable Status Register */
typedef struct _Ifx_GTM_TOM_TGC1_OUTEN_STAT_Bits
{
    Ifx_Strict_32Bit OUTEN_STAT0:2;         /**< \brief [1:0] Control/status of output (A)TOM_OUT(0) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT1:2;         /**< \brief [3:2] Control/status of output (A)TOM_OUT(1) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT2:2;         /**< \brief [5:4] Control/status of output (A)TOM_OUT(2) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT3:2;         /**< \brief [7:6] Control/status of output (A)TOM_OUT(3) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT4:2;         /**< \brief [9:8] Control/status of output (A)TOM_OUT(4) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT5:2;         /**< \brief [11:10] Control/status of output (A)TOM_OUT(5) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT6:2;         /**< \brief [13:12] Control/status of output (A)TOM_OUT(6) (rw) */
    Ifx_Strict_32Bit OUTEN_STAT7:2;         /**< \brief [15:14] Control/status of output (A)TOM_OUT(7) (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TOM_TGC1_OUTEN_STAT_Bits;

/** \brief  Trigger Output Register */
typedef struct _Ifx_GTM_TRIGOUT_Bits
{
    Ifx_Strict_32Bit INT0:2;                /**< \brief [1:0] Interrupt Trigger Request 0 (w) */
    Ifx_Strict_32Bit INT1:2;                /**< \brief [3:2] Interrupt Trigger Request 1 (w) */
    Ifx_Strict_32Bit TRIG0:2;               /**< \brief [5:4] Trigger 0 (w) */
    Ifx_Strict_32Bit TRIG1:2;               /**< \brief [7:6] Trigger 1 (w) */
    Ifx_Strict_32Bit TRIG2:2;               /**< \brief [9:8] Trigger 2 (w) */
    Ifx_Strict_32Bit TRIG3:2;               /**< \brief [11:10] Trigger 3 (w) */
    Ifx_Strict_32Bit TRIG4:2;               /**< \brief [13:12] Trigger 4 (w) */
    Ifx_Strict_32Bit TRIG5:2;               /**< \brief [15:14] Trigger 5 (w) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_GTM_TRIGOUT_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Gtm_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_ACCEN1;

/** \brief  ADC Trigger 0 Output Select 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ADCTRIG0OUT0_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ADCTRIG0OUT0;

/** \brief  ADC Trigger 1 Output Select 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ADCTRIG1OUT0_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ADCTRIG1OUT0;

/** \brief  GTM AEI Timeout Exception Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_AEI_ADDR_XPT_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_AEI_ADDR_XPT;

/** \brief  AFD0 FIFO0 Channel Buffer Access Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_AFD_CH_BUF_ACC_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_AFD_CH_BUF_ACC;

/** \brief  ARU Access Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_ARU_ACCESS_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_ARU_ARU_ACCESS;

/** \brief  ARU Access Register Upper Data Word */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DATA_H_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ARU_DATA_H;

/** \brief  ARU Access Register Lower Data Word */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DATA_L_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ARU_DATA_L;

/** \brief  Debug Access Channel 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DBG_ACCESS0_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ARU_DBG_ACCESS0;

/** \brief  Debug Access Channel 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DBG_ACCESS1_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ARU_DBG_ACCESS1;

/** \brief  Debug Access 0 Transfer Register Upper Data Word */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DBG_DATA0_H_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ARU_DBG_DATA0_H;

/** \brief  Debug Access 0 Transfer Register Lower Data Word */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DBG_DATA0_L_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ARU_DBG_DATA0_L;

/** \brief  Debug Access 1 Transfer Register Upper Data Word */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DBG_DATA1_H_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ARU_DBG_DATA1_H;

/** \brief  Debug Access 1 Transfer Register Lower Data Word */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_DBG_DATA1_L_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ARU_DBG_DATA1_L;

/** \brief  ARU Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_IRQ_EN_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ARU_IRQ_EN;

/** \brief  ARU_NEW_DATA_IRQ Forcing Interrupt Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_IRQ_FORCINT_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ARU_IRQ_FORCINT;

/** \brief  IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_IRQ_MODE_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ARU_IRQ_MODE;

/** \brief  ARU Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ARU_IRQ_NOTIFY_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_ARU_IRQ_NOTIFY;

/** \brief  TOM TGC0 Action Time Base Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_ACT_TB_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_ACT_TB;

/** \brief  ATOM AGC Enable/Disable Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_ENDIS_CTRL_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_ENDIS_CTRL;

/** \brief  ATOM AGC Enable/Disable Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_ENDIS_STAT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_ENDIS_STAT;

/** \brief  ATOM AGC Force Update Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_FUPD_CTRL_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_FUPD_CTRL;

/** \brief  ATOM AGC Global control register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_GLB_CTRL_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_GLB_CTRL;

/** \brief  ATOM AGC Internal Trigger Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_INT_TRIG_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_INT_TRIG;

/** \brief  ATOM AGC Output Enable Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_OUTEN_CTRL_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_OUTEN_CTRL;

/** \brief  ATOM AGC Output Enable Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_AGC_OUTEN_STAT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_ATOM_AGC_OUTEN_STAT;

/** \brief  ATOM Channel CCU0 Compare Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_CM0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_CM0;

/** \brief  ATOM Channel CCU1 Compare Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_CM1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_CM1;

/** \brief  ATOM Channel CCU0 Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_CN0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_CN0;

/** \brief  ATOM Channel Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_CTRL_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_CTRL;

/** \brief  ATOM Channel Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_IRQ_EN_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_IRQ_EN;

/** \brief  ATOM Channel Software Interrupt Generation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_IRQ_FORCINT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_IRQ_FORCINT;

/** \brief  ATOM IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_IRQ_MODE_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_IRQ_MODE;

/** \brief  ATOM Channel Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_IRQ_NOTIFY_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_IRQ_NOTIFY;

/** \brief  ATOM Channel ARU Read Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_RDADDR_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_RDADDR;

/** \brief  ATOM Channel Control in SOMC mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_SOMC_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_SOMC;

/** \brief  ATOM Channel Control in SOMI mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_SOMI_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_SOMI;

/** \brief  ATOM Channel Control in SOMP mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_SOMP_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_SOMP;

/** \brief  ATOM Channel Control in SOMS mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_SOMS_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_SOMS;

/** \brief  ATOM Channel CCU0 Compare Shadow Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_SR0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_SR0;

/** \brief  ATOM Channel CCU1 Compare Shadow Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_SR1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_SR1;

/** \brief  ATOM Channel Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ATOM_CH_STAT_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ATOM_CH_STAT;

/** \brief  BRC Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_EIRQ_EN_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_BRC_EIRQ_EN;

/** \brief  BRC Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_IRQ_EN_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_BRC_IRQ_EN;

/** \brief  BRC_DEST_ERR Forcing Interrupt Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_IRQ_FORCINT_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_BRC_IRQ_FORCINT;

/** \brief  BRC IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_IRQ_MODE_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_BRC_IRQ_MODE;

/** \brief  BRC Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_IRQ_NOTIFY_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_BRC_IRQ_NOTIFY;

/** \brief  BRC Software Reset Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_RST_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_BRC_RST;

/** \brief  Read Address For Input Channel 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC0_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC0_ADDR;

/** \brief  Destination Channels For Input Channel 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC0_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC0_DEST;

/** \brief  Read Address For Input Channel 10 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC10_ADDR_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC10_ADDR;

/** \brief  Destination Channels For Input Channel 10 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC10_DEST_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC10_DEST;

/** \brief  Read Address For Input Channel 11 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC11_ADDR_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC11_ADDR;

/** \brief  Destination Channels For Input Channel 11 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC11_DEST_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC11_DEST;

/** \brief  Read Address For Input Channel 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC1_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC1_ADDR;

/** \brief  Destination Channels For Input Channel 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC1_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC1_DEST;

/** \brief  Read Address For Input Channel 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC2_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC2_ADDR;

/** \brief  Destination Channels For Input Channel 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC2_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC2_DEST;

/** \brief  Read Address For Input Channel 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC3_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC3_ADDR;

/** \brief  Destination Channels For Input Channel 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC3_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC3_DEST;

/** \brief  Read Address For Input Channel 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC4_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC4_ADDR;

/** \brief  Destination Channels For Input Channel 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC4_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC4_DEST;

/** \brief  Read Address For Input Channel 5 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC5_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC5_ADDR;

/** \brief  Destination Channels For Input Channel 5 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC5_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC5_DEST;

/** \brief  Read Address For Input Channel 6 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC6_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC6_ADDR;

/** \brief  Destination Channels For Input Channel 6 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC6_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC6_DEST;

/** \brief  Read Address For Input Channel 7 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC7_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC7_ADDR;

/** \brief  Destination Channels For Input Channel 7 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC7_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC7_DEST;

/** \brief  Read Address For Input Channel 8 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC8_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC8_ADDR;

/** \brief  Destination Channels For Input Channel 8 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC8_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC8_DEST;

/** \brief  Read Address For Input Channel 9 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC9_ADDR_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC9_ADDR;

/** \brief  Destination Channels For Input Channel 9 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRC_SRC9_DEST_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_BRC_SRC9_DEST;

/** \brief  GTM to SPB BRIDGE MODE */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRIDGE_MODE_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_BRIDGE_MODE;

/** \brief  GTM to SPB BRIDGE PTR1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRIDGE_PTR1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_BRIDGE_PTR1;

/** \brief  GTM to SPB BRIDGE PTR2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_BRIDGE_PTR2_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_BRIDGE_PTR2;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_GTM_CLC;

/** \brief  CMP Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMP_EIRQ_EN_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_CMP_EIRQ_EN;

/** \brief  CMP Comparator Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMP_EN_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_CMP_EN;

/** \brief  CMP Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMP_IRQ_EN_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_CMP_IRQ_EN;

/** \brief  CMP Interrupt Force Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMP_IRQ_FORCINT_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_CMP_IRQ_FORCINT;

/** \brief  CMP IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMP_IRQ_MODE_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_CMP_IRQ_MODE;

/** \brief  CMP Event Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMP_IRQ_NOTIFY_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_CMP_IRQ_NOTIFY;

/** \brief  CMU Control For Clock Source Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_CLK0_5_CTRL_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_CMU_CLK0_5_CTRL;

/** \brief  CMU Control For Clock Source 6 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_CLK_6_CTRL_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_CMU_CLK_6_CTRL;

/** \brief  CMU Control For Clock Source 7 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_CLK_7_CTRL_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_CMU_CLK_7_CTRL;

/** \brief  CMU Clock Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_CLK_EN_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_CMU_CLK_EN;

/** \brief  CMU External Clock Control Denominator Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_ECLK_DEN_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_CMU_ECLK_DEN;

/** \brief  CMU External Clock Control Numerator Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_ECLK_NUM_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_CMU_ECLK_NUM;

/** \brief  CMU FXCLK Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_FXCLK_CTRL_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_CMU_FXCLK_CTRL;

/** \brief  CMU Global Clock Control Denominator Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_GCLK_DEN_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_CMU_GCLK_DEN;

/** \brief  CMU Global Clock Control Numerator Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CMU_GCLK_NUM_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_CMU_GCLK_NUM;

/** \brief  GTM Global Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_CTRL_Bits B;                    /**< \brief Bitfield access */
} Ifx_GTM_CTRL;

/** \brief  Data Input 0 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DATAIN_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_DATAIN;

/** \brief  DPLL Action Control i Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ACB_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ACB;

/** \brief  DPLL ACTION Status Register With Shadow Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ACT_STA_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ACT_STA;

/** \brief  DPLL Calculated ADD_IN Value for SUB_INC1 Generation */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ADD_IN_CAL1_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ADD_IN_CAL1;

/** \brief  DPLL Calculated ADD_IN Value for SUB_INC2 Generation */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ADD_IN_CAL2_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ADD_IN_CAL2;

/** \brief  DPLL Direct Load Input Value for SUB_INC1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ADD_IN_LD1_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ADD_IN_LD1;

/** \brief  DPLL Direct Load Input Value for SUB_INC1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ADD_IN_LD2_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ADD_IN_LD2;

/** \brief  DPLL Adapt Values for All STATE Increments */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ADT_S_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ADT_S;

/** \brief  DPLL Address Offset Register For APT In RAM Region 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_AOSV_2_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_AOSV_2;

/** \brief  DPLL Actual RAM Pointer to RAM Regions 1C1, 1C2 and 1C4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_APS_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_APS;

/** \brief  DPLL Actual RAM Pointer to RAM Region 1C3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_APS_1C3_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_APS_1C3;

/** \brief  DPLL Old RAM Pointer and Offset Value for STATE */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_APS_SYNC_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_APS_SYNC;

/** \brief  DPLL Actual RAM Pointer to RAM Regions 2A, B and D */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_APT_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_APT;

/** \brief  DPLL Actual RAM Pointer to RAM Region 2C */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_APT_2C_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_APT_2C;

/** \brief  DPLL Old RAM Pointer and Offset Value for TRIGGER */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_APT_SYNC_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_APT_SYNC;

/** \brief  DPLL Prediction of the actual STATE Increment */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CDT_SX_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CDT_SX;

/** \brief  DPLL Prediction of the nominal STATE increment duration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CDT_SX_NOM_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CDT_SX_NOM;

/** \brief  DPLL Prediction of the actual TRIGGER Increment */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CDT_TX_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CDT_TX;

/** \brief  DPLL Prediction of the nominal TRIGGER Increment duration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CDT_TX_NOM_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CDT_TX_NOM;

/** \brief  DPLL Number of Sub-Pulses of SUB_INC1 in Continuous Mode */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CNT_NUM1_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CNT_NUM1;

/** \brief  DPLL Number of Sub-Pulses of SUB_INC2 in Continuous Mode */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CNT_NUM2_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CNT_NUM2;

/** \brief  DPLL Control 1 Shadow STATE Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CRTL_1_SHADOW_STATE_Bits B;    /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CRTL_1_SHADOW_STATE;

/** \brief  DPLL Control Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_0;

/** \brief  DPLL Control 0 Shadow STATE Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_0_SHADOW_STATE_Bits B;    /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_0_SHADOW_STATE;

/** \brief  DPLL Control0 Shadow Trigger Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_0_SHADOW_TRIGGER_Bits B;  /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_0_SHADOW_TRIGGER;

/** \brief  DPLL Control Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_1;

/** \brief  DPLL Control 1 Shadow TRIGGER Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_1_SHADOW_TRIGGER_Bits B;  /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_1_SHADOW_TRIGGER;

/** \brief  DPLL Control Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_2_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_2;

/** \brief  DPLL Control Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_3_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_3;

/** \brief  DPLL Control Register 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_CTRL_4_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_CTRL_4;

/** \brief  DPLL ACTION Time To React Before PSAi Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_DLA_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_DLA;

/** \brief  DPLL Nominal STATE Increment Values for FULL_SCALE */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_DT_S_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_DT_S;

/** \brief  DPLL Duration of Last STATE Increment [DT_S_ACT] */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_DT_S_ACT_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_DT_S_ACT;

/** \brief  DPLL Duration of Last TRIGGER Increment */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_DT_T_ACT_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_DT_T_ACT;

/** \brief  DPLL Calculated Relative Time To ACTION_i Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_DTA_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_DTA;

/** \brief  DPLL Difference of Prediction to actual value for Last STATE
 * Increment */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_EDT_S_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_EDT_S;

/** \brief  DPLL Difference of prediction to actual value of the last TRIGGER
 * increment */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_EDT_T_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_EDT_T;

/** \brief  DPLL Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_EIRQ_EN_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_EIRQ_EN;

/** \brief  DPLL Actual Signal STATE Filter Value Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_FTV_S_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_FTV_S;

/** \brief  DPLL Actual Signal TRIGGER Filter Value Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_FTV_T_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_FTV_T;

/** \brief  DPLL ID Information For Input Signal PMTR Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_ID_PMTR_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_ID_PMTR;

/** \brief  DPLL Counter for Pulses for TBU_TS1 to be sent in Automatic End Mode */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_INC_CNT1_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_INC_CNT1;

/** \brief  DPLL Counter for Pulses for TBU_TS2 to be sent in Automatic End Mode
 * when SMC=RMO=1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_INC_CNT2_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_INC_CNT2;

/** \brief  DPLL Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_IRQ_EN_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_IRQ_EN;

/** \brief  DPLL Interrupt Force Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_IRQ_FORCINT_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_DPLL_IRQ_FORCINT;

/** \brief  DPLL Interrupt Mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_IRQ_MODE_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_DPLL_IRQ_MODE;

/** \brief  DPLL Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_IRQ_NOTIFY_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_DPLL_IRQ_NOTIFY;

/** \brief  DPLL Weighted difference of Prediction up to the Last STATE
 * Increment */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_MEDT_S_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_MEDT_S;

/** \brief  DPLL Weighted difference of Prediction up to the Last TRIGGER
 * Increment */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_MEDT_T_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_MEDT_T;

/** \brief  DPLL Calculated Number of Sub-Pulses between Two STATE Events */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_MLS1_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_MLS1;

/** \brief  DPLL Calculated Number of Sub-Pulses between Two STATE Events */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_MLS2_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_MLS2;

/** \brief  DPLL Missing Pulses to be Added/Subtracted Directly to SUB_INC1 and
 * INC_CNT1 Once */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_MPVAL1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_MPVAL1;

/** \brief  DPLL Missing Pulses to be Added/Subtracted Directly to SUB_INC2 and
 * INC_CNT2 Once */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_MPVAL2_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_MPVAL2;

/** \brief  DPLL Calculated Number Of TRIGGER/STATE Increments To ACTION */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NA_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NA;

/** \brief  DPLL Number of Pulses of Current Increment in Emergency Mode */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NMB_S_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NMB_S;

/** \brief  DPLL Target Number of Pulses to be sent in emergency mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NMB_S_TAR_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NMB_S_TAR;

/** \brief  DPLL Target Number of Pulses to be sent in emergency mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NMB_S_TAR_OLD_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NMB_S_TAR_OLD;

/** \brief  DPLL Number of Pulses of Current Increment in Normal Mode */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NMB_T_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NMB_T;

/** \brief  DPLL Target Number of Pulses to be sent in normal mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NMB_T_TAR_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NMB_T_TAR;

/** \brief  DPLL Target Number of Pulses to be sent in normal mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NMB_T_TAR_OLD_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NMB_T_TAR_OLD;

/** \brief  DPLL Number of Active TRIGGER Events to Interrupt */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NTI_CNT_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NTI_CNT;

/** \brief  DPLL Number of Recent STATE Events Used for Calculations */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NUSC_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NUSC;

/** \brief  DPLL Number of Recent TRIGGER Events Used for Calculations */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_NUTC_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_NUTC;

/** \brief  DPLL Offset And Switch Old/New Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_OSW_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_OSW;

/** \brief  DPLL Projected TRIGGER Increment Sum Relations for Action_i */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PDT_T_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PDT_T;

/** \brief  DPLL ACTION Position/Value Action Request Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSA_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSA;

/** \brief  DPLL Calculated Position Value Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSAC_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSAC;

/** \brief  DPLL Accurate Calculated Position Stamp of Last STATE Input */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSSC_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSSC;

/** \brief  DPLL Measured Position Stamp of Last STATE Input */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSSM_0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSSM_0;

/** \brief  DPLL Measured Position Stamp of Last STATE Input */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSSM_1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSSM_1;

/** \brief  DPLL Actual Calculated Position Stamp of Last TRIGGER Input */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSTC_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSTC;

/** \brief  DPLL Measured Position Stamp of Last TRIGGER Input */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSTM_0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSTM_0;

/** \brief  DPLL Measured Position Stamp of Last TRIGGER Input */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PSTM_1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PSTM_1;

/** \brief  DPLL Plausibility Value of Next Active TRIGGER Slope */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_PVT_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_PVT;

/** \brief  DPLL RAM Initatlisation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RAM_INI_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RAM_INI;

/** \brief  DPLL Reciprocal Value of Expected Increment Duration STATE */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RCDT_SX_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RCDT_SX;

/** \brief  DPLL Reciprocal Value of the Expected Nominal Increment Duration
 * STATE */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RCDT_SX_NOM_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RCDT_SX_NOM;

/** \brief  DPLL Reciprocal Value of Expected Increment Duration TRIGGER */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RCDT_TX_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RCDT_TX;

/** \brief  DPLL Reciprocal Value of the Expected Nominal Increment Duration
 * TRIGGER */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RCDT_TX_NOM_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RCDT_TX_NOM;

/** \brief  DPLL Nominal STATE Reciprocal Values in FULL_SCALE */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RDT_S_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RDT_S;

/** \brief  DPLL Actual Reciprocal Value of STATE */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RDT_S_ACT_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RDT_S_ACT;

/** \brief  DPLL Actual Reciprocal Value of TRIGGER */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_RDT_T_ACT_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_DPLL_RDT_T_ACT;

/** \brief  DPLL STATE Locking Range */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_SLR_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_SLR;

/** \brief  DPLL Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_STATUS_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_STATUS;

/** \brief  DPLL TBU_TS0 Value at last STATE Event */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TBU_TS0_S_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TBU_TS0_S;

/** \brief  DPLL TBU_TS0 Value at last TRIGGER Event */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TBU_TS0_T_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TBU_TS0_T;

/** \brief  DPLL TRIGGER Hold Time Max Value */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_THMA_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_THMA;

/** \brief  DPLL TRIGGER hold time min value */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_THMI_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_THMI;

/** \brief  DPLL Measured Last Pulse Time from Valid to Invalid TRIGGER Slope */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_THVAL_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_THVAL;

/** \brief  DPLL TRIGGER locking range */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TLR_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TLR;

/** \brief  DPLL Time Out Value of active TRIGGER Slope */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TOV_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TOV;

/** \brief  DPLL Time Out Value of active STATE Slope */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TOV_S_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TOV_S;

/** \brief  DPLL Actual Signal STATE Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TS_S_0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TS_S_0;

/** \brief  DPLL Actual Signal STATE Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TS_S_1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TS_S_1;

/** \brief  DPLL Actual Signal TRIGGER Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TS_T_0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TS_T_0;

/** \brief  DPLL Actual Signal TRIGGER Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TS_T_1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TS_T_1;

/** \brief  DPLL Calculate Time Stamp Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TSAC_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TSAC;

/** \brief  DPLL Time Stamp Field of STATE Events */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DPLL_TSF_S_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_DPLL_TSF_S;

/** \brief  Data Exchange Input Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DXINCON_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_DXINCON;

/** \brief  Data Exchange Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_DXOUTCON_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_DXOUTCON;

/** \brief  GTM Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_EIRQ_EN_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_EIRQ_EN;

/** \brief  F2A0 Stream Activation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_F2A_ENABLE_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_F2A_ENABLE;

/** \brief  F2A Read Channel Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_F2A_RD_CH_ARU_RD_FIFO_Bits B;   /**< \brief Bitfield access */
} Ifx_GTM_F2A_RD_CH_ARU_RD_FIFO;

/** \brief  F2A Stream Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_F2A_STR_CH_STR_CFG_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_F2A_STR_CH_STR_CFG;

/** \brief  FIFO0 Channel Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_CTRL_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_CTRL;

/** \brief  FIFO0 Channel Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_EIRQ_EN_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_EIRQ_EN;

/** \brief  FIFO0 Channel End Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_END_ADDR_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_END_ADDR;

/** \brief  FIFO0 Channel Fill Level Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_FILL_LEVEL_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_FILL_LEVEL;

/** \brief  FIFO0 Channel Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_IRQ_EN_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_IRQ_EN;

/** \brief  FIFO0 Channel Force Interrupt By Software Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_IRQ_FORCINT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_IRQ_FORCINT;

/** \brief  FIFO0 Channel IRQ Mode Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_IRQ_MODE_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_IRQ_MODE;

/** \brief  FIFO0 Channel Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_IRQ_NOTIFY_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_IRQ_NOTIFY;

/** \brief  FIFO0 Channel Lower Watermark Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_LOWER_WM_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_LOWER_WM;

/** \brief  FIFO0 Channel Read Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_RD_PTR_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_RD_PTR;

/** \brief  FIFO0 Channel Start Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_START_ADDR_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_START_ADDR;

/** \brief  FIFO0 Channel Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_STATUS_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_STATUS;

/** \brief  FIFO0 Channel Upper Watermark Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_UPPER_WM_Bits B;        /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_UPPER_WM;

/** \brief  FIFO0 Channel Write Pointer Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_FIFO_CH_WR_PTR_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_FIFO_CH_WR_PTR;

/** \brief  GTM Infrastructure Interrupt Group */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_0_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_0;

/** \brief  GTM DPLL Interrupt Group */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_1_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_1;

/** \brief  TIM Interrupt Group 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_2_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_2;

/** \brief  MCS Interrupt Group 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_4_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_4;

/** \brief  TOM Interrupt Group 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_6_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_6;

/** \brief  ATOM Interrupt Group 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_9_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_9;

/** \brief  ICM Channel Error Interrupt 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_CEI0_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_CEI0;

/** \brief  ICM Channel Error Interrupt 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_CEI1_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_CEI1;

/** \brief  ICM Channel Error Interrupt 3 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_CEI3_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_CEI3;

/** \brief  ICM Module Error Interrupt Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ICM_IRQG_MEI_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_ICM_IRQG_MEI;

/** \brief  CAN Output Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_INOUTSEL_CAN_OUTSEL_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_INOUTSEL_CAN_OUTSEL;

/** \brief  DSADC Input Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_INOUTSEL_DSADC_INSEL_Bits B;    /**< \brief Bitfield access */
} Ifx_GTM_INOUTSEL_DSADC_INSEL;

/** \brief  DSADC Output Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_INOUTSEL_DSADC_OUTSEL_Bits B;   /**< \brief Bitfield access */
} Ifx_GTM_INOUTSEL_DSADC_OUTSEL;

/** \brief  PSI5 Output Select 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_INOUTSEL_PSI5_OUTSEL0_Bits B;   /**< \brief Bitfield access */
} Ifx_GTM_INOUTSEL_PSI5_OUTSEL0;

/** \brief  PSI5-S Output Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_INOUTSEL_PSI5S_OUTSEL_Bits B;   /**< \brief Bitfield access */
} Ifx_GTM_INOUTSEL_PSI5S_OUTSEL;

/** \brief  Timer Output Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_INOUTSEL_T_OUTSEL_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_INOUTSEL_T_OUTSEL;

/** \brief  TIM Input Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_INOUTSEL_TIM_INSEL_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_INOUTSEL_TIM_INSEL;

/** \brief  GTM Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_IRQ_EN_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_IRQ_EN;

/** \brief  GTM Software Interrupt Generation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_IRQ_FORCINT_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_IRQ_FORCINT;

/** \brief  GTM Top Level Interrupts Mode Selection */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_IRQ_MODE_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_IRQ_MODE;

/** \brief  GTM Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_IRQ_NOTIFY_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_IRQ_NOTIFY;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_GTM_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_GTM_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_KRSTCLR;

/** \brief  MAP Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MAP_CTRL_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_MAP_CTRL;

/** \brief  Memory Layout Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCFG_CTRL_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCFG_CTRL;

/** \brief  MCS Clear Trigger Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH0_CTRG_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH0_CTRG;

/** \brief  MCS Set Trigger Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH0_STRG_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH0_STRG;

/** \brief  MCS Channel ACB Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_ACB_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_ACB;

/** \brief  MCS Channel Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_CTRL_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_CTRL;

/** \brief  MCS_Channel Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_EIRQ_EN_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_EIRQ_EN;

/** \brief  MCS Channel Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_IRQ_EN_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_IRQ_EN;

/** \brief  MCS Channel Software Interrupt Generation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_IRQ_FORCINT_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_IRQ_FORCINT;

/** \brief  MCS IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_IRQ_MODE_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_IRQ_MODE;

/** \brief  MCS Channel interrupt notification register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_IRQ_NOTIFY_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_IRQ_NOTIFY;

/** \brief  MCS Channel Program Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_PC_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_PC;

/** \brief  MCS Channel Program Counter Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R0_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R0;

/** \brief  MCS Channel Program Counter Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R1_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R1;

/** \brief  MCS Channel Program Counter Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R2_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R2;

/** \brief  MCS Channel Program Counter Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R3_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R3;

/** \brief  MCS Channel Program Counter Register 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R4_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R4;

/** \brief  MCS Channel Program Counter Register 5 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R5_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R5;

/** \brief  MCS Channel Program Counter Register 6 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R6_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R6;

/** \brief  MCS Channel Program Counter Register 7 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CH_R7_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCS_CH_R7;

/** \brief  MCS Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_CTRL_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_MCS_CTRL;

/** \brief  MCS Error Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_ERR_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_MCS_ERR;

/** \brief  MCS Channel Reset Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCS_RST_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_MCS_RST;

/** \brief  MCS Interrupt Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCSINTCLR_Bits B;               /**< \brief Bitfield access */
} Ifx_GTM_MCSINTCLR;

/** \brief  MCS Interrupt Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MCSINTSTAT_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_MCSINTSTAT;

/** \brief  Monitor Activity Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MON_ACTIVITY_0_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_MON_ACTIVITY_0;

/** \brief  Monitor Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MON_STATUS_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_MON_STATUS;

/** \brief  MSC0 Input Low Extended Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MSC0INLEXTCON_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_MSC0INLEXTCON;

/** \brief  MSC Input High Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MSCIN_INHCON_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_MSCIN_INHCON;

/** \brief  MSC Input Low Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MSCIN_INLCON_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_MSCIN_INLCON;

/** \brief  MSC Set Control 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MSCSET_CON0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_MSCSET_CON0;

/** \brief  MSC Set Control 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MSCSET_CON1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_MSCSET_CON1;

/** \brief  MSC Set Control 2 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MSCSET_CON2_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_MSCSET_CON2;

/** \brief  MSC Set Control 3 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_MSCSET_CON3_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_MSCSET_CON3;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_OCS_Bits B;                     /**< \brief Bitfield access */
} Ifx_GTM_OCS;

/** \brief  OCDS Debug Access Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_ODA_Bits B;                     /**< \brief Bitfield access */
} Ifx_GTM_ODA;

/** \brief  OCDS TBU0 Trigger Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_OTBU0T_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_OTBU0T;

/** \brief  OCDS TBU1 Trigger Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_OTBU1T_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_OTBU1T;

/** \brief  OCDS TBU2 Trigger Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_OTBU2T_Bits B;                  /**< \brief Bitfield access */
} Ifx_GTM_OTBU2T;

/** \brief  OCDS Trigger Set Control 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_OTSC0_Bits B;                   /**< \brief Bitfield access */
} Ifx_GTM_OTSC0;

/** \brief  OCDS Trigger Set Control 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_OTSC1_Bits B;                   /**< \brief Bitfield access */
} Ifx_GTM_OTSC1;

/** \brief  OCDS Trigger Set Select Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_OTSS_Bits B;                    /**< \brief Bitfield access */
} Ifx_GTM_OTSS;

/** \brief  GTM Version Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_REV_Bits B;                     /**< \brief Bitfield access */
} Ifx_GTM_REV;

/** \brief  GTM Global Reset Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_RST_Bits B;                     /**< \brief Bitfield access */
} Ifx_GTM_RST;

/** \brief  SPE Revolution Compare Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_CMP_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_SPE_CMP;

/** \brief  SPE Revolution Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_CNT_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_SPE_CNT;

/** \brief  SPE Control Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_CTRL_STAT_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_SPE_CTRL_STAT;

/** \brief  SPE Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_EIRQ_EN_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_SPE_EIRQ_EN;

/** \brief  SPE Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_IRQ_EN_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_SPE_IRQ_EN;

/** \brief  SPE Interrupt Generation by Software */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_IRQ_FORCINT_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_SPE_IRQ_FORCINT;

/** \brief  SPE IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_IRQ_MODE_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_SPE_IRQ_MODE;

/** \brief  SPE Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_IRQ_NOTIFY_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_SPE_IRQ_NOTIFY;

/** \brief  SPE Output Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_OUT_CTRL_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_SPE_OUT_CTRL;

/** \brief  SPE Output Definition Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_OUT_PAT_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_SPE_OUT_PAT;

/** \brief  SPE Input Pattern Definition Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_SPE_PAT_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_SPE_PAT;

/** \brief  TBU Channel 0 Base Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TBU_CH0_BASE_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_TBU_CH0_BASE;

/** \brief  TBU Channel 0 Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TBU_CH0_CTRL_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_TBU_CH0_CTRL;

/** \brief  TBU Channel 1 Base Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TBU_CH1_BASE_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_TBU_CH1_BASE;

/** \brief  TBU Channel 1 Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TBU_CH1_CTRL_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_TBU_CH1_CTRL;

/** \brief  TBU Channel 2 Base Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TBU_CH2_BASE_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_TBU_CH2_BASE;

/** \brief  TBU Channel 2 Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TBU_CH2_CTRL_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_TBU_CH2_CTRL;

/** \brief  TBU Global Channel Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TBU_CHEN_Bits B;                /**< \brief Bitfield access */
} Ifx_GTM_TBU_CHEN;

/** \brief  GTM TIM  AUX_IN_SRC */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_AUX_IN_SRC_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_TIM_AUX_IN_SRC;

/** \brief  TIM Channel SMU Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_CNT_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_CNT;

/** \brief  TIM Channel SMU Shadow Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_CNTS_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_CNTS;

/** \brief  TIM Channel Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_CTRL_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_CTRL;

/** \brief  TIM Channel Edge Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_ECNT_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_ECNT;

/** \brief  TIM Channel External Capture Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_ECTRL_Bits B;            /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_ECTRL;

/** \brief  TIM Channel Error Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_EIRQ_EN_Bits B;          /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_EIRQ_EN;

/** \brief  TIM Channel Filter Parameter 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_FLT_FE_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_FLT_FE;

/** \brief  GTM_TIM Channel Filter Parameter 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_FLT_RE_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_FLT_RE;

/** \brief  TIM Channel General Purpose 0 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_GPR0_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_GPR0;

/** \brief  TIM Channel General Purpose 1 Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_GPR1_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_GPR1;

/** \brief  TIM Channel Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_IRQ_EN_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_IRQ_EN;

/** \brief  TIM Channel Software Interrupt Force Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_IRQ_FORCINT_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_IRQ_FORCINT;

/** \brief  TIM IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_IRQ_MODE_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_IRQ_MODE;

/** \brief  TIM Channel Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_IRQ_NOTIFY_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_IRQ_NOTIFY;

/** \brief  TIM Channel TDUC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_TDUC_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_TDUC;

/** \brief  TIM Channel TDUV Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_CH_TDUV_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TIM_CH_TDUV;

/** \brief  TIM_IN_SRC Long Name */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_IN_SRC_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_TIM_IN_SRC;

/** \brief  TIM Global Software Reset Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TIM_RST_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_TIM_RST;

/** \brief  TOM Channel CCU0 Compare Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_CM0_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_CM0;

/** \brief  TOM Channel CCU1 Compare Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_CM1_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_CM1;

/** \brief  TOM Channel CCU0 Counter Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_CN0_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_CN0;

/** \brief  TOM Channel Control Register’ */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_CTRL_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_CTRL;

/** \brief  TOM Channel Interrupt Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_IRQ_EN_Bits B;           /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_IRQ_EN;

/** \brief  TOM Channel Software Interrupt Generation Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_IRQ_FORCINT_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_IRQ_FORCINT;

/** \brief  TOM IRQ Mode Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_IRQ_MODE_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_IRQ_MODE;

/** \brief  TOM Channel Interrupt Notification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_IRQ_NOTIFY_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_IRQ_NOTIFY;

/** \brief  TOM Channel CCU0 Compare Shadow Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_SR0_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_SR0;

/** \brief  TOM Channel CCU1 Compare Shadow Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_SR1_Bits B;              /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_SR1;

/** \brief  TOM Channel Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_CH_STAT_Bits B;             /**< \brief Bitfield access */
} Ifx_GTM_TOM_CH_STAT;

/** \brief  TOM TGC0 Action Time Base Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_ACT_TB_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_ACT_TB;

/** \brief  TOM TGC0 Enable/Disable Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_ENDIS_CTRL_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_ENDIS_CTRL;

/** \brief  TOM TGC0 Enable/Disable Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_ENDIS_STAT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_ENDIS_STAT;

/** \brief  TOM TGC0 Force Update Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_FUPD_CTRL_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_FUPD_CTRL;

/** \brief  TOM TGC0 Global Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_GLB_CTRL_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_GLB_CTRL;

/** \brief  TOM TGC0 Internal Trigger Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_INT_TRIG_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_INT_TRIG;

/** \brief  TOM TGC0 Output Enable Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_OUTEN_CTRL_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_OUTEN_CTRL;

/** \brief  TOM TGC0 Output Enable Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC0_OUTEN_STAT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC0_OUTEN_STAT;

/** \brief  TOM TGC1 Action Time Base Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_ACT_TB_Bits B;         /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_ACT_TB;

/** \brief  TOM TGC1 Enable/Disable Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_ENDIS_CTRL_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_ENDIS_CTRL;

/** \brief  TOM TGC1 Enable/Disable Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_ENDIS_STAT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_ENDIS_STAT;

/** \brief  TOM TGC1 Force Update Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_FUPD_CTRL_Bits B;      /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_FUPD_CTRL;

/** \brief  TOM TGC1 Global Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_GLB_CTRL_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_GLB_CTRL;

/** \brief  TOM TGC1 Internal Trigger Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_INT_TRIG_Bits B;       /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_INT_TRIG;

/** \brief  TOM TGC1 Output Enable Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_OUTEN_CTRL_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_OUTEN_CTRL;

/** \brief  TOM TGC1 Output Enable Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TOM_TGC1_OUTEN_STAT_Bits B;     /**< \brief Bitfield access */
} Ifx_GTM_TOM_TGC1_OUTEN_STAT;

/** \brief  Trigger Output Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_GTM_TRIGOUT_Bits B;                 /**< \brief Bitfield access */
} Ifx_GTM_TRIGOUT;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Gtm_struct
 * \{  */
/******************************************************************************/
/** \name Object L2
 * \{  */

/** \brief  AFD FIFO channel objects */
typedef volatile struct _Ifx_GTM_AFD_CH
{
    Ifx_GTM_AFD_CH_BUF_ACC BUF_ACC;         /**< \brief 0, AFD0 FIFO0 Channel Buffer Access Register */
    unsigned char reserved_4[12];           /**< \brief 4, \internal Reserved */
} Ifx_GTM_AFD_CH;

/** \brief  ACG object */
typedef volatile struct _Ifx_GTM_ATOM_AGC
{
    Ifx_GTM_ATOM_AGC_GLB_CTRL GLB_CTRL;     /**< \brief 0, ATOM AGC Global control register */
    Ifx_GTM_ATOM_AGC_ENDIS_CTRL ENDIS_CTRL; /**< \brief 4, ATOM AGC Enable/Disable Control Register */
    Ifx_GTM_ATOM_AGC_ENDIS_STAT ENDIS_STAT; /**< \brief 8, ATOM AGC Enable/Disable Status Register */
    Ifx_GTM_ATOM_AGC_ACT_TB ACT_TB;         /**< \brief C, TOM TGC0 Action Time Base Register */
    Ifx_GTM_ATOM_AGC_OUTEN_CTRL OUTEN_CTRL; /**< \brief 10, ATOM AGC Output Enable Control Register */
    Ifx_GTM_ATOM_AGC_OUTEN_STAT OUTEN_STAT; /**< \brief 14, ATOM AGC Output Enable Status Register */
    Ifx_GTM_ATOM_AGC_FUPD_CTRL FUPD_CTRL;   /**< \brief 18, ATOM AGC Force Update Control Register */
    Ifx_GTM_ATOM_AGC_INT_TRIG INT_TRIG;     /**< \brief 1C, ATOM AGC Internal Trigger Control Register */
    unsigned char reserved_20[32];          /**< \brief 20, \internal Reserved */
} Ifx_GTM_ATOM_AGC;

/** \brief  ATOM channel objects */
typedef volatile struct _Ifx_GTM_ATOM_CH
{
    Ifx_GTM_ATOM_CH_RDADDR RDADDR;          /**< \brief 0, ATOM Channel ARU Read Address Register */
    union
    {
        Ifx_GTM_ATOM_CH_CTRL CTRL;          /**< \brief 4, ATOM Channel Control in SOMI mode Register */
        Ifx_GTM_ATOM_CH_SOMC SOMC;          /**< \brief 4, ATOM Channel Control in SOMI mode Register */
        Ifx_GTM_ATOM_CH_SOMI SOMI;          /**< \brief 4, ATOM Channel Control in SOMI mode Register */
        Ifx_GTM_ATOM_CH_SOMP SOMP;          /**< \brief 4, ATOM Channel Control in SOMI mode Register */
        Ifx_GTM_ATOM_CH_SOMS SOMS;          /**< \brief 4, ATOM Channel Control in SOMI mode Register */
    };

    Ifx_GTM_ATOM_CH_SR0 SR0;                /**< \brief 8, ATOM Channel CCU0 Compare Shadow Register */
    Ifx_GTM_ATOM_CH_SR1 SR1;                /**< \brief C, ATOM Channel CCU1 Compare Shadow Register */
    Ifx_GTM_ATOM_CH_CM0 CM0;                /**< \brief 10, ATOM Channel CCU0 Compare Register */
    Ifx_GTM_ATOM_CH_CM1 CM1;                /**< \brief 14, ATOM Channel CCU1 Compare Register */
    Ifx_GTM_ATOM_CH_CN0 CN0;                /**< \brief 18, ATOM Channel CCU0 Counter Register */
    Ifx_GTM_ATOM_CH_STAT STAT;              /**< \brief 1C, ATOM Channel Status Register */
    Ifx_GTM_ATOM_CH_IRQ_NOTIFY IRQ_NOTIFY;  /**< \brief 20, ATOM Channel Interrupt Notification Register */
    Ifx_GTM_ATOM_CH_IRQ_EN IRQ_EN;          /**< \brief 24, ATOM Channel Interrupt Enable Register */
    Ifx_GTM_ATOM_CH_IRQ_FORCINT IRQ_FORCINT;    /**< \brief 28, ATOM Channel Software Interrupt Generation Register */
    Ifx_GTM_ATOM_CH_IRQ_MODE IRQ_MODE;      /**< \brief 2C, ATOM IRQ Mode Configuration Register */
    unsigned char reserved_30[16];          /**< \brief 30, \internal Reserved */
} Ifx_GTM_ATOM_CH;

/** \brief  CLK objects */
typedef volatile struct _Ifx_GTM_CMU_CLK0_5
{
    Ifx_GTM_CMU_CLK0_5_CTRL CTRL;           /**< \brief 0, CMU Control For Clock Source Register */
} Ifx_GTM_CMU_CLK0_5;

/** \brief  CLK objects */
typedef volatile struct _Ifx_GTM_CMU_CLK_6
{
    Ifx_GTM_CMU_CLK_6_CTRL CTRL;            /**< \brief 0, CMU Control For Clock Source 6 Register */
} Ifx_GTM_CMU_CLK_6;

/** \brief  CLK objects */
typedef volatile struct _Ifx_GTM_CMU_CLK_7
{
    Ifx_GTM_CMU_CLK_7_CTRL CTRL;            /**< \brief 0, CMU Control For Clock Source 7 Register */
} Ifx_GTM_CMU_CLK_7;

/** \brief  ECLK objects */
typedef volatile struct _Ifx_GTM_CMU_ECLK
{
    Ifx_GTM_CMU_ECLK_NUM NUM;               /**< \brief 0, CMU External Clock Control Numerator Register */
    Ifx_GTM_CMU_ECLK_DEN DEN;               /**< \brief 4, CMU External Clock Control Denominator Register */
} Ifx_GTM_CMU_ECLK;

/** \brief  FXCLK objects */
typedef volatile struct _Ifx_GTM_CMU_FXCLK
{
    Ifx_GTM_CMU_FXCLK_CTRL CTRL;            /**< \brief 0, CMU FXCLK Control Register */
} Ifx_GTM_CMU_FXCLK;

/** \brief  F2A ARU RD FIFO address */
typedef volatile struct _Ifx_GTM_F2A_RD_CH
{
    Ifx_GTM_F2A_RD_CH_ARU_RD_FIFO ARU_RD_FIFO;  /**< \brief 0, F2A Read Channel Address Register */
} Ifx_GTM_F2A_RD_CH;

/** \brief  F2A Stream configuration */
typedef volatile struct _Ifx_GTM_F2A_STR_CH
{
    Ifx_GTM_F2A_STR_CH_STR_CFG STR_CFG;     /**< \brief 0, F2A Stream Configuration Register */
} Ifx_GTM_F2A_STR_CH;

/** \brief  FIFO channel */
typedef volatile struct _Ifx_GTM_FIFO_CH
{
    Ifx_GTM_FIFO_CH_CTRL CTRL;              /**< \brief 0, FIFO0 Channel Control Register */
    Ifx_GTM_FIFO_CH_END_ADDR END_ADDR;      /**< \brief 4, FIFO0 Channel End Address Register */
    Ifx_GTM_FIFO_CH_START_ADDR START_ADDR;  /**< \brief 8, FIFO0 Channel Start Address Register */
    Ifx_GTM_FIFO_CH_UPPER_WM UPPER_WM;      /**< \brief C, FIFO0 Channel Upper Watermark Register */
    Ifx_GTM_FIFO_CH_LOWER_WM LOWER_WM;      /**< \brief 10, FIFO0 Channel Lower Watermark Register */
    Ifx_GTM_FIFO_CH_STATUS STATUS;          /**< \brief 14, FIFO0 Channel Status Register */
    Ifx_GTM_FIFO_CH_FILL_LEVEL FILL_LEVEL;  /**< \brief 18, FIFO0 Channel Fill Level Register */
    Ifx_GTM_FIFO_CH_WR_PTR WR_PTR;          /**< \brief 1C, FIFO0 Channel Write Pointer Register */
    Ifx_GTM_FIFO_CH_RD_PTR RD_PTR;          /**< \brief 20, FIFO0 Channel Read Pointer Register */
    Ifx_GTM_FIFO_CH_IRQ_NOTIFY IRQ_NOTIFY;  /**< \brief 24, FIFO0 Channel Interrupt Notification Register */
    Ifx_GTM_FIFO_CH_IRQ_EN IRQ_EN;          /**< \brief 28, FIFO0 Channel Interrupt Enable Register */
    Ifx_GTM_FIFO_CH_IRQ_FORCINT IRQ_FORCINT;    /**< \brief 2C, FIFO0 Channel Force Interrupt By Software Register */
    Ifx_GTM_FIFO_CH_IRQ_MODE IRQ_MODE;      /**< \brief 30, FIFO0 Channel IRQ Mode Control Register */
    Ifx_GTM_FIFO_CH_EIRQ_EN EIRQ_EN;        /**< \brief 34, FIFO0 Channel Error Interrupt Enable Register */
    unsigned char reserved_38[8];           /**< \brief 38, \internal Reserved */
} Ifx_GTM_FIFO_CH;

/** \brief  CAN */
typedef volatile struct _Ifx_GTM_INOUTSEL_CAN
{
    Ifx_GTM_INOUTSEL_CAN_OUTSEL OUTSEL;     /**< \brief 0, CAN Output Select Register */
} Ifx_GTM_INOUTSEL_CAN;

/** \brief  DSADC */
typedef volatile struct _Ifx_GTM_INOUTSEL_DSADC
{
    Ifx_GTM_INOUTSEL_DSADC_INSEL INSEL[3];  /**< \brief 0, DSADC Input Select Register */
    Ifx_GTM_INOUTSEL_DSADC_OUTSEL OUTSEL00; /**< \brief C, DSADC Output Select 00 Register */
    unsigned char reserved_10[4];           /**< \brief 10, \internal Reserved */
    Ifx_GTM_INOUTSEL_DSADC_OUTSEL OUTSEL10; /**< \brief 14, DSADC Output Select 10 Register */
} Ifx_GTM_INOUTSEL_DSADC;

/** \brief  PSI5 */
typedef volatile struct _Ifx_GTM_INOUTSEL_PSI5
{
    Ifx_GTM_INOUTSEL_PSI5_OUTSEL0 OUTSEL0;  /**< \brief 0, PSI5 Output Select 0 Register */
} Ifx_GTM_INOUTSEL_PSI5;

/** \brief  PSI5S */
typedef volatile struct _Ifx_GTM_INOUTSEL_PSI5S
{
    Ifx_GTM_INOUTSEL_PSI5S_OUTSEL OUTSEL;   /**< \brief 0, PSI5-S Output Select Register */
} Ifx_GTM_INOUTSEL_PSI5S;

/** \brief  Timer */
typedef volatile struct _Ifx_GTM_INOUTSEL_T
{
    Ifx_GTM_INOUTSEL_T_OUTSEL OUTSEL[10];   /**< \brief 0, Timer Output Select Register */
} Ifx_GTM_INOUTSEL_T;

/** \brief  TIM */
typedef volatile struct _Ifx_GTM_INOUTSEL_TIM
{
    Ifx_GTM_INOUTSEL_TIM_INSEL INSEL;       /**< \brief 0, TIM Input Select Register */
} Ifx_GTM_INOUTSEL_TIM;

/** \brief  MCS channel objects */
typedef volatile struct _Ifx_GTM_MCS_CH
{
    Ifx_GTM_MCS_CH_R0 R0;                   /**< \brief 0, MCS Channel Program Counter Register 0 */
    Ifx_GTM_MCS_CH_R1 R1;                   /**< \brief 4, MCS Channel Program Counter Register 1 */
    Ifx_GTM_MCS_CH_R2 R2;                   /**< \brief 8, MCS Channel Program Counter Register 2 */
    Ifx_GTM_MCS_CH_R3 R3;                   /**< \brief C, MCS Channel Program Counter Register 3 */
    Ifx_GTM_MCS_CH_R4 R4;                   /**< \brief 10, MCS Channel Program Counter Register 4 */
    Ifx_GTM_MCS_CH_R5 R5;                   /**< \brief 14, MCS Channel Program Counter Register 5 */
    Ifx_GTM_MCS_CH_R6 R6;                   /**< \brief 18, MCS Channel Program Counter Register 6 */
    Ifx_GTM_MCS_CH_R7 R7;                   /**< \brief 1C, MCS Channel Program Counter Register 7 */
    Ifx_GTM_MCS_CH_CTRL CTRL;               /**< \brief 20, MCS Channel Control Register */
    Ifx_GTM_MCS_CH_ACB ACB;                 /**< \brief 24, MCS Channel ACB Register */
    unsigned char reserved_28[24];          /**< \brief 28, \internal Reserved */
    Ifx_GTM_MCS_CH_PC PC;                   /**< \brief 40, MCS Channel Program Counter Register */
    Ifx_GTM_MCS_CH_IRQ_NOTIFY IRQ_NOTIFY;   /**< \brief 44, MCS Channel interrupt notification register */
    Ifx_GTM_MCS_CH_IRQ_EN IRQ_EN;           /**< \brief 48, MCS Channel Interrupt Enable Register */
    Ifx_GTM_MCS_CH_IRQ_FORCINT IRQ_FORCINT; /**< \brief 4C, MCS Channel Software Interrupt Generation Register */
    Ifx_GTM_MCS_CH_IRQ_MODE IRQ_MODE;       /**< \brief 50, MCS IRQ Mode Configuration Register */
    Ifx_GTM_MCS_CH_EIRQ_EN EIRQ_EN;         /**< \brief 54, MCS_Channel Error Interrupt Enable Register */
    unsigned char reserved_58[40];          /**< \brief 58, \internal Reserved */
} Ifx_GTM_MCS_CH;

/** \brief  MCS channel0 object */
typedef volatile struct _Ifx_GTM_MCS_CH0
{
    Ifx_GTM_MCS_CH_R0 R0;                   /**< \brief 0, MCS Channel Program Counter Register 0 */
    Ifx_GTM_MCS_CH_R1 R1;                   /**< \brief 4, MCS Channel Program Counter Register 1 */
    Ifx_GTM_MCS_CH_R2 R2;                   /**< \brief 8, MCS Channel Program Counter Register 2 */
    Ifx_GTM_MCS_CH_R3 R3;                   /**< \brief C, MCS Channel Program Counter Register 3 */
    Ifx_GTM_MCS_CH_R4 R4;                   /**< \brief 10, MCS Channel Program Counter Register 4 */
    Ifx_GTM_MCS_CH_R5 R5;                   /**< \brief 14, MCS Channel Program Counter Register 5 */
    Ifx_GTM_MCS_CH_R6 R6;                   /**< \brief 18, MCS Channel Program Counter Register 6 */
    Ifx_GTM_MCS_CH_R7 R7;                   /**< \brief 1C, MCS Channel Program Counter Register 7 */
    Ifx_GTM_MCS_CH_CTRL CTRL;               /**< \brief 20, MCS Channel Control Register */
    Ifx_GTM_MCS_CH_ACB ACB;                 /**< \brief 24, MCS Channel ACB Register */
    Ifx_GTM_MCS_CH0_CTRG CTRG;              /**< \brief 28, MCS Clear Trigger Control Register */
    Ifx_GTM_MCS_CH0_STRG STRG;              /**< \brief 2C, MCS Set Trigger Control Register */
    unsigned char reserved_30[16];          /**< \brief 30, \internal Reserved */
    Ifx_GTM_MCS_CH_PC PC;                   /**< \brief 40, MCS Channel Program Counter Register */
    Ifx_GTM_MCS_CH_IRQ_NOTIFY IRQ_NOTIFY;   /**< \brief 44, MCS Channel interrupt notification register */
    Ifx_GTM_MCS_CH_IRQ_EN IRQ_EN;           /**< \brief 48, MCS Channel Interrupt Enable Register */
    Ifx_GTM_MCS_CH_IRQ_FORCINT IRQ_FORCINT; /**< \brief 4C, MCS Channel Software Interrupt Generation Register */
    Ifx_GTM_MCS_CH_IRQ_MODE IRQ_MODE;       /**< \brief 50, MCS IRQ Mode Configuration Register */
    Ifx_GTM_MCS_CH_EIRQ_EN EIRQ_EN;         /**< \brief 54, MCS_Channel Error Interrupt Enable Register */
} Ifx_GTM_MCS_CH0;

/** \brief  TIM channel objects */
typedef volatile struct _Ifx_GTM_TIM_CH
{
    Ifx_GTM_TIM_CH_GPR0 GPR0;               /**< \brief 0, TIM Channel General Purpose 0 Register */
    Ifx_GTM_TIM_CH_GPR1 GPR1;               /**< \brief 4, TIM Channel General Purpose 1 Register */
    Ifx_GTM_TIM_CH_CNT CNT;                 /**< \brief 8, TIM Channel SMU Counter Register */
    Ifx_GTM_TIM_CH_ECNT ECNT;               /**< \brief C, TIM Channel Edge Counter Register */
    Ifx_GTM_TIM_CH_CNTS CNTS;               /**< \brief 10, TIM Channel SMU Shadow Counter Register */
    Ifx_GTM_TIM_CH_TDUC TDUC;               /**< \brief 14, TIM Channel TDUC Register */
    Ifx_GTM_TIM_CH_TDUV TDUV;               /**< \brief 18, TIM Channel TDUV Register */
    Ifx_GTM_TIM_CH_FLT_RE FLT_RE;           /**< \brief 1C, GTM_TIM Channel Filter Parameter 0 Register */
    Ifx_GTM_TIM_CH_FLT_FE FLT_FE;           /**< \brief 20, TIM Channel Filter Parameter 1 Register */
    Ifx_GTM_TIM_CH_CTRL CTRL;               /**< \brief 24, TIM Channel Control Register */
    Ifx_GTM_TIM_CH_ECTRL ECTRL;             /**< \brief 28, TIM Channel External Capture Control Register */
    Ifx_GTM_TIM_CH_IRQ_NOTIFY IRQ_NOTIFY;   /**< \brief 2C, TIM Channel Interrupt Notification Register */
    Ifx_GTM_TIM_CH_IRQ_EN IRQ_EN;           /**< \brief 30, TIM Channel Interrupt Enable Register */
    Ifx_GTM_TIM_CH_IRQ_FORCINT IRQ_FORCINT; /**< \brief 34, TIM Channel Software Interrupt Force Register */
    Ifx_GTM_TIM_CH_IRQ_MODE IRQ_MODE;       /**< \brief 38, TIM IRQ Mode Configuration Register */
    Ifx_GTM_TIM_CH_EIRQ_EN EIRQ_EN;         /**< \brief 3C, TIM Channel Error Interrupt Enable Register */
    unsigned char reserved_40[56];          /**< \brief 40, \internal Reserved */
} Ifx_GTM_TIM_CH;

/** \brief  TOM channel objects */
typedef volatile struct _Ifx_GTM_TOM_CH
{
    Ifx_GTM_TOM_CH_CTRL CTRL;               /**< \brief 0, TOM Channel Control Register’ */
    Ifx_GTM_TOM_CH_SR0 SR0;                 /**< \brief 4, TOM Channel CCU0 Compare Shadow Register */
    Ifx_GTM_TOM_CH_SR1 SR1;                 /**< \brief 8, TOM Channel CCU1 Compare Shadow Register */
    Ifx_GTM_TOM_CH_CM0 CM0;                 /**< \brief C, TOM Channel CCU0 Compare Register */
    Ifx_GTM_TOM_CH_CM1 CM1;                 /**< \brief 10, TOM Channel CCU1 Compare Register */
    Ifx_GTM_TOM_CH_CN0 CN0;                 /**< \brief 14, TOM Channel CCU0 Counter Register */
    Ifx_GTM_TOM_CH_STAT STAT;               /**< \brief 18, TOM Channel Status Register */
    Ifx_GTM_TOM_CH_IRQ_NOTIFY IRQ_NOTIFY;   /**< \brief 1C, TOM Channel Interrupt Notification Register */
    Ifx_GTM_TOM_CH_IRQ_EN IRQ_EN;           /**< \brief 20, TOM Channel Interrupt Enable Register */
    Ifx_GTM_TOM_CH_IRQ_FORCINT IRQ_FORCINT; /**< \brief 24, TOM Channel Software Interrupt Generation Register */
    Ifx_GTM_TOM_CH_IRQ_MODE IRQ_MODE;       /**< \brief 28, TOM IRQ Mode Configuration Register */
    unsigned char reserved_2C[4];           /**< \brief 2C, \internal Reserved */
} Ifx_GTM_TOM_CH;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Gtm_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  AFD object */
typedef volatile struct _Ifx_GTM_AFD
{
    Ifx_GTM_AFD_CH CH[8];                   /**< \brief 0, AFD FIFO channel objects */
} Ifx_GTM_AFD;

/** \brief  ARU object */
typedef volatile struct _Ifx_GTM_ARU
{
    Ifx_GTM_ARU_ARU_ACCESS ARU_ACCESS;      /**< \brief 0, ARU Access Register */
    Ifx_GTM_ARU_DATA_H DATA_H;              /**< \brief 4, ARU Access Register Upper Data Word */
    Ifx_GTM_ARU_DATA_L DATA_L;              /**< \brief 8, ARU Access Register Lower Data Word */
    Ifx_GTM_ARU_DBG_ACCESS0 DBG_ACCESS0;    /**< \brief C, Debug Access Channel 0 */
    Ifx_GTM_ARU_DBG_DATA0_H DBG_DATA0_H;    /**< \brief 10, Debug Access 0 Transfer Register Upper Data Word */
    Ifx_GTM_ARU_DBG_DATA0_L DBG_DATA0_L;    /**< \brief 14, Debug Access 0 Transfer Register Lower Data Word */
    Ifx_GTM_ARU_DBG_ACCESS1 DBG_ACCESS1;    /**< \brief 18, Debug Access Channel 0 */
    Ifx_GTM_ARU_DBG_DATA1_H DBG_DATA1_H;    /**< \brief 1C, Debug Access 1 Transfer Register Upper Data Word */
    Ifx_GTM_ARU_DBG_DATA1_L DBG_DATA1_L;    /**< \brief 20, Debug Access 1 Transfer Register Lower Data Word */
    Ifx_GTM_ARU_IRQ_NOTIFY IRQ_NOTIFY;      /**< \brief 24, ARU Interrupt Notification Register */
    Ifx_GTM_ARU_IRQ_EN IRQ_EN;              /**< \brief 28, ARU Interrupt Enable Register */
    Ifx_GTM_ARU_IRQ_FORCINT IRQ_FORCINT;    /**< \brief 2C, ARU_NEW_DATA_IRQ Forcing Interrupt Register */
    Ifx_GTM_ARU_IRQ_MODE IRQ_MODE;          /**< \brief 30, IRQ Mode Configuration Register */
} Ifx_GTM_ARU;

/** \brief  ATOM objects */
typedef volatile struct _Ifx_GTM_ATOM
{
    Ifx_GTM_ATOM_CH CH0;                    /**< \brief 0, ATOM channel objects */
    Ifx_GTM_ATOM_AGC AGC;                   /**< \brief 40, ACG object */
    Ifx_GTM_ATOM_CH CH1;                    /**< \brief 80, ATOM channel objects */
    unsigned char reserved_C0[64];          /**< \brief C0, \internal Reserved */
    Ifx_GTM_ATOM_CH CH2;                    /**< \brief 100, ATOM channel objects */
    unsigned char reserved_140[64];         /**< \brief 140, \internal Reserved */
    Ifx_GTM_ATOM_CH CH3;                    /**< \brief 180, ATOM channel objects */
    unsigned char reserved_1C0[64];         /**< \brief 1C0, \internal Reserved */
    Ifx_GTM_ATOM_CH CH4;                    /**< \brief 200, ATOM channel objects */
    unsigned char reserved_240[64];         /**< \brief 240, \internal Reserved */
    Ifx_GTM_ATOM_CH CH5;                    /**< \brief 280, ATOM channel objects */
    unsigned char reserved_2C0[64];         /**< \brief 2C0, \internal Reserved */
    Ifx_GTM_ATOM_CH CH6;                    /**< \brief 300, ATOM channel objects */
    unsigned char reserved_340[64];         /**< \brief 340, \internal Reserved */
    Ifx_GTM_ATOM_CH CH7;                    /**< \brief 380, ATOM channel objects */
    unsigned char reserved_3C0[1088];       /**< \brief 3C0, \internal Reserved */
} Ifx_GTM_ATOM;

/** \brief  BRC object */
typedef volatile struct _Ifx_GTM_BRC
{
    Ifx_GTM_BRC_SRC0_ADDR SRC0_ADDR;        /**< \brief 0, Read Address For Input Channel 0 */
    Ifx_GTM_BRC_SRC0_DEST SRC0_DEST;        /**< \brief 4, Destination Channels For Input Channel 0 */
    Ifx_GTM_BRC_SRC1_ADDR SRC1_ADDR;        /**< \brief 8, Read Address For Input Channel 1 */
    Ifx_GTM_BRC_SRC1_DEST SRC1_DEST;        /**< \brief C, Destination Channels For Input Channel 1 */
    Ifx_GTM_BRC_SRC2_ADDR SRC2_ADDR;        /**< \brief 10, Read Address For Input Channel 2 */
    Ifx_GTM_BRC_SRC2_DEST SRC2_DEST;        /**< \brief 14, Destination Channels For Input Channel 2 */
    Ifx_GTM_BRC_SRC3_ADDR SRC3_ADDR;        /**< \brief 18, Read Address For Input Channel 3 */
    Ifx_GTM_BRC_SRC3_DEST SRC3_DEST;        /**< \brief 1C, Destination Channels For Input Channel 3 */
    Ifx_GTM_BRC_SRC4_ADDR SRC4_ADDR;        /**< \brief 20, Read Address For Input Channel 4 */
    Ifx_GTM_BRC_SRC4_DEST SRC4_DEST;        /**< \brief 24, Destination Channels For Input Channel 4 */
    Ifx_GTM_BRC_SRC5_ADDR SRC5_ADDR;        /**< \brief 28, Read Address For Input Channel 5 */
    Ifx_GTM_BRC_SRC5_DEST SRC5_DEST;        /**< \brief 2C, Destination Channels For Input Channel 5 */
    Ifx_GTM_BRC_SRC6_ADDR SRC6_ADDR;        /**< \brief 30, Read Address For Input Channel 6 */
    Ifx_GTM_BRC_SRC6_DEST SRC6_DEST;        /**< \brief 34, Destination Channels For Input Channel 6 */
    Ifx_GTM_BRC_SRC7_ADDR SRC7_ADDR;        /**< \brief 38, Read Address For Input Channel 7 */
    Ifx_GTM_BRC_SRC7_DEST SRC7_DEST;        /**< \brief 3C, Destination Channels For Input Channel 7 */
    Ifx_GTM_BRC_SRC8_ADDR SRC8_ADDR;        /**< \brief 40, Read Address For Input Channel 8 */
    Ifx_GTM_BRC_SRC8_DEST SRC8_DEST;        /**< \brief 44, Destination Channels For Input Channel 8 */
    Ifx_GTM_BRC_SRC9_ADDR SRC9_ADDR;        /**< \brief 48, Read Address For Input Channel 9 */
    Ifx_GTM_BRC_SRC9_DEST SRC9_DEST;        /**< \brief 4C, Destination Channels For Input Channel 9 */
    Ifx_GTM_BRC_SRC10_ADDR SRC10_ADDR;      /**< \brief 50, Read Address For Input Channel 10 */
    Ifx_GTM_BRC_SRC10_DEST SRC10_DEST;      /**< \brief 54, Destination Channels For Input Channel 10 */
    Ifx_GTM_BRC_SRC11_ADDR SRC11_ADDR;      /**< \brief 58, Read Address For Input Channel 11 */
    Ifx_GTM_BRC_SRC11_DEST SRC11_DEST;      /**< \brief 5C, Destination Channels For Input Channel 11 */
    Ifx_GTM_BRC_IRQ_NOTIFY IRQ_NOTIFY;      /**< \brief 60, BRC Interrupt Notification Register */
    Ifx_GTM_BRC_IRQ_EN IRQ_EN;              /**< \brief 64, BRC Interrupt Enable Register */
    Ifx_GTM_BRC_IRQ_FORCINT IRQ_FORCINT;    /**< \brief 68, BRC_DEST_ERR Forcing Interrupt Register */
    Ifx_GTM_BRC_IRQ_MODE IRQ_MODE;          /**< \brief 6C, BRC IRQ Mode Configuration Register */
    Ifx_GTM_BRC_RST RST;                    /**< \brief 70, BRC Software Reset Register */
    Ifx_GTM_BRC_EIRQ_EN EIRQ_EN;            /**< \brief 74, BRC Error Interrupt Enable Register */
} Ifx_GTM_BRC;

/** \brief  BRIDGE object */
typedef volatile struct _Ifx_GTM_BRIDGE
{
    Ifx_GTM_BRIDGE_MODE MODE;               /**< \brief 0, GTM to SPB BRIDGE MODE */
    Ifx_GTM_BRIDGE_PTR1 PTR1;               /**< \brief 4, GTM to SPB BRIDGE PTR1 */
    Ifx_GTM_BRIDGE_PTR2 PTR2;               /**< \brief 8, GTM to SPB BRIDGE PTR2 */
} Ifx_GTM_BRIDGE;

/** \brief  CMP object */
typedef volatile struct _Ifx_GTM_CMP
{
    Ifx_GTM_CMP_EN EN;                      /**< \brief 0, CMP Comparator Enable Register */
    Ifx_GTM_CMP_IRQ_NOTIFY IRQ_NOTIFY;      /**< \brief 4, CMP Event Notification Register */
    Ifx_GTM_CMP_IRQ_EN IRQ_EN;              /**< \brief 8, CMP Interrupt Enable Register */
    Ifx_GTM_CMP_IRQ_FORCINT IRQ_FORCINT;    /**< \brief C, CMP Interrupt Force Register */
    Ifx_GTM_CMP_IRQ_MODE IRQ_MODE;          /**< \brief 10, CMP IRQ Mode Configuration Register */
    Ifx_GTM_CMP_EIRQ_EN EIRQ_EN;            /**< \brief 14, CMP Error Interrupt Enable Register */
} Ifx_GTM_CMP;

/** \brief  CMU object */
typedef volatile struct _Ifx_GTM_CMU
{
    Ifx_GTM_CMU_CLK_EN CLK_EN;              /**< \brief 0, CMU Clock Enable Register */
    Ifx_GTM_CMU_GCLK_NUM GCLK_NUM;          /**< \brief 4, CMU Global Clock Control Numerator Register */
    Ifx_GTM_CMU_GCLK_DEN GCLK_DEN;          /**< \brief 8, CMU Global Clock Control Denominator Register */
    Ifx_GTM_CMU_CLK0_5 CLK0_5[6];           /**< \brief C, CLK objects */
    Ifx_GTM_CMU_CLK_6 CLK_6;                /**< \brief 24, CLK objects */
    Ifx_GTM_CMU_CLK_7 CLK_7;                /**< \brief 28, CLK objects */
    Ifx_GTM_CMU_ECLK ECLK[3];               /**< \brief 2C, ECLK objects */
    Ifx_GTM_CMU_FXCLK FXCLK;                /**< \brief 44, FXCLK objects */
} Ifx_GTM_CMU;

/** \brief  DPLL object */
typedef volatile struct _Ifx_GTM_DPLL
{
    Ifx_GTM_DPLL_CTRL_0 CTRL_0;             /**< \brief 0, DPLL Control Register 0 */
    Ifx_GTM_DPLL_CTRL_1 CTRL_1;             /**< \brief 4, DPLL Control Register 1 */
    Ifx_GTM_DPLL_CTRL_2 CTRL_2;             /**< \brief 8, DPLL Control Register 2 */
    Ifx_GTM_DPLL_CTRL_3 CTRL_3;             /**< \brief C, DPLL Control Register 3 */
    Ifx_GTM_DPLL_CTRL_4 CTRL_4;             /**< \brief 10, DPLL Control Register 4 */
    unsigned char reserved_14[4];           /**< \brief 14, \internal Reserved */
    Ifx_GTM_DPLL_ACT_STA ACT_STA;           /**< \brief 18, DPLL ACTION Status Register With Shadow Register */
    Ifx_GTM_DPLL_OSW OSW;                   /**< \brief 1C, DPLL Offset And Switch Old/New Address Register */
    Ifx_GTM_DPLL_AOSV_2 AOSV_2;             /**< \brief 20, DPLL Address Offset Register For APT In RAM Region 2 */
    Ifx_GTM_DPLL_APT APT;                   /**< \brief 24, DPLL Actual RAM Pointer to RAM Regions 2A, B and D */
    Ifx_GTM_DPLL_APS APS;                   /**< \brief 28, DPLL Actual RAM Pointer to RAM Regions 1C1, 1C2 and 1C4 */
    Ifx_GTM_DPLL_APT_2C APT_2C;             /**< \brief 2C, DPLL Actual RAM Pointer to RAM Region 2C */
    Ifx_GTM_DPLL_APS_1C3 APS_1C3;           /**< \brief 30, DPLL Actual RAM Pointer to RAM Region 1C3 */
    Ifx_GTM_DPLL_NUTC NUTC;                 /**< \brief 34, DPLL Number of Recent TRIGGER Events Used for Calculations */
    Ifx_GTM_DPLL_NUSC NUSC;                 /**< \brief 38, DPLL Number of Recent STATE Events Used for Calculations */
    Ifx_GTM_DPLL_NTI_CNT NTI_CNT;           /**< \brief 3C, DPLL Number of Active TRIGGER Events to Interrupt */
    Ifx_GTM_DPLL_IRQ_NOTIFY IRQ_NOTIFY;     /**< \brief 40, DPLL Interrupt Notification Register */
    Ifx_GTM_DPLL_IRQ_EN IRQ_EN;             /**< \brief 44, DPLL Interrupt Enable Register */
    Ifx_GTM_DPLL_IRQ_FORCINT IRQ_FORCINT;   /**< \brief 48, DPLL Interrupt Force Register */
    Ifx_GTM_DPLL_IRQ_MODE IRQ_MODE;         /**< \brief 4C, DPLL Interrupt Mode Register */
    Ifx_GTM_DPLL_EIRQ_EN EIRQ_EN;           /**< \brief 50, DPLL Error Interrupt Enable Register */
    unsigned char reserved_54[92];          /**< \brief 54, \internal Reserved */
    Ifx_GTM_DPLL_INC_CNT1 INC_CNT1;         /**< \brief B0, DPLL Counter for Pulses for TBU_TS1 to be sent in Automatic End Mode */
    Ifx_GTM_DPLL_INC_CNT2 INC_CNT2;         /**< \brief B4, DPLL Counter for Pulses for TBU_TS2 to be sent in Automatic End Mode when SMC=RMO=1 */
    Ifx_GTM_DPLL_APT_SYNC APT_SYNC;         /**< \brief B8, DPLL Old RAM Pointer and Offset Value for TRIGGER */
    Ifx_GTM_DPLL_APS_SYNC APS_SYNC;         /**< \brief BC, DPLL Old RAM Pointer and Offset Value for STATE */
    Ifx_GTM_DPLL_TBU_TS0_T TBU_TS0_T;       /**< \brief C0, DPLL TBU_TS0 Value at last TRIGGER Event */
    Ifx_GTM_DPLL_TBU_TS0_S TBU_TS0_S;       /**< \brief C4, DPLL TBU_TS0 Value at last STATE Event */
    Ifx_GTM_DPLL_ADD_IN_LD1 ADD_IN_LD1;     /**< \brief C8, DPLL Direct Load Input Value for SUB_INC1 */
    Ifx_GTM_DPLL_ADD_IN_LD2 ADD_IN_LD2;     /**< \brief CC, DPLL Direct Load Input Value for SUB_INC1 */
    unsigned char reserved_D0[44];          /**< \brief D0, \internal Reserved */
    Ifx_GTM_DPLL_STATUS STATUS;             /**< \brief FC, DPLL Status Register */
    Ifx_GTM_DPLL_ID_PMTR ID_PMTR[24];       /**< \brief 100, DPLL ID Information For Input Signal PMTR n Register */
    unsigned char reserved_160[128];        /**< \brief 160, \internal Reserved */
    Ifx_GTM_DPLL_CTRL_0_SHADOW_TRIGGER CTRL_0_SHADOW_TRIGGER;   /**< \brief 1E0, DPLL Control0 Shadow Trigger Register */
    Ifx_GTM_DPLL_CTRL_0_SHADOW_STATE CTRL_0_SHADOW_STATE;   /**< \brief 1E4, DPLL Control 0 Shadow STATE Register */
    Ifx_GTM_DPLL_CTRL_1_SHADOW_TRIGGER CTRL_1_SHADOW_TRIGGER;   /**< \brief 1E8, DPLL Control 1 Shadow TRIGGER Register */
    Ifx_GTM_DPLL_CRTL_1_SHADOW_STATE CRTL_1_SHADOW_STATE;   /**< \brief 1EC, DPLL Control 1 Shadow STATE Register */
    unsigned char reserved_1F0[12];         /**< \brief 1F0, \internal Reserved */
    Ifx_GTM_DPLL_RAM_INI RAM_INI;           /**< \brief 1FC, DPLL RAM Initatlisation Register */
    Ifx_GTM_DPLL_PSA PSA[24];               /**< \brief 200, DPLL ACTION Position/Value Action Request Register */
    unsigned char reserved_260[32];         /**< \brief 260, \internal Reserved */
    Ifx_GTM_DPLL_DLA DLA[24];               /**< \brief 280, DPLL ACTION Time To React Before PSAi Register */
    unsigned char reserved_2E0[32];         /**< \brief 2E0, \internal Reserved */
    Ifx_GTM_DPLL_NA NA[24];                 /**< \brief 300, DPLL Calculated Number Of TRIGGER/STATE Increments To ACTION */
    unsigned char reserved_360[32];         /**< \brief 360, \internal Reserved */
    Ifx_GTM_DPLL_DTA DTA[24];               /**< \brief 380, DPLL Calculated Relative Time To ACTION_i Register */
    unsigned char reserved_3E0[32];         /**< \brief 3E0, \internal Reserved */
    Ifx_GTM_DPLL_TS_T_0 TS_T_0;             /**< \brief 400, DPLL Actual Signal TRIGGER Time Stamp Register */
    Ifx_GTM_DPLL_TS_T_1 TS_T_1;             /**< \brief 404, DPLL Actual Signal TRIGGER Time Stamp Register */
    Ifx_GTM_DPLL_FTV_T FTV_T;               /**< \brief 408, DPLL Actual Signal TRIGGER Filter Value Register */
    unsigned char reserved_40C[4];          /**< \brief 40C, \internal Reserved */
    Ifx_GTM_DPLL_TS_S_0 TS_S_0;             /**< \brief 410, DPLL Actual Signal STATE Time Stamp Register */
    Ifx_GTM_DPLL_TS_S_1 TS_S_1;             /**< \brief 414, DPLL Actual Signal STATE Time Stamp Register */
    Ifx_GTM_DPLL_FTV_S FTV_S;               /**< \brief 418, DPLL Actual Signal STATE Filter Value Register */
    unsigned char reserved_41C[4];          /**< \brief 41C, \internal Reserved */
    Ifx_GTM_DPLL_THMI THMI;                 /**< \brief 420, DPLL TRIGGER hold time min value */
    Ifx_GTM_DPLL_THMA THMA;                 /**< \brief 424, DPLL TRIGGER Hold Time Max Value */
    Ifx_GTM_DPLL_THVAL THVAL;               /**< \brief 428, DPLL Measured Last Pulse Time from Valid to Invalid TRIGGER Slope */
    unsigned char reserved_42C[4];          /**< \brief 42C, \internal Reserved */
    Ifx_GTM_DPLL_TOV TOV;                   /**< \brief 430, DPLL Time Out Value of active TRIGGER Slope */
    Ifx_GTM_DPLL_TOV_S TOV_S;               /**< \brief 434, DPLL Time Out Value of active STATE Slope */
    Ifx_GTM_DPLL_ADD_IN_CAL1 ADD_IN_CAL1;   /**< \brief 438, DPLL Calculated ADD_IN Value for SUB_INC1 Generation */
    Ifx_GTM_DPLL_ADD_IN_CAL2 ADD_IN_CAL2;   /**< \brief 43C, DPLL Calculated ADD_IN Value for SUB_INC2 Generation */
    Ifx_GTM_DPLL_MPVAL1 MPVAL1;             /**< \brief 440, DPLL Missing Pulses to be Added/Subtracted Directly to SUB_INC1 and INC_CNT1 Once */
    Ifx_GTM_DPLL_MPVAL2 MPVAL2;             /**< \brief 444, DPLL Missing Pulses to be Added/Subtracted Directly to SUB_INC2 and INC_CNT2 Once */
    Ifx_GTM_DPLL_NMB_T_TAR NMB_T_TAR;       /**< \brief 448, DPLL Target Number of Pulses to be sent in normal mode Register */
    Ifx_GTM_DPLL_NMB_T_TAR_OLD NMB_T_TAR_OLD;   /**< \brief 44C, DPLL Target Number of Pulses to be sent in normal mode Register */
    Ifx_GTM_DPLL_NMB_S_TAR NMB_S_TAR;       /**< \brief 450, DPLL Target Number of Pulses to be sent in emergency mode Register */
    Ifx_GTM_DPLL_NMB_S_TAR_OLD NMB_S_TAR_OLD;   /**< \brief 454, DPLL Target Number of Pulses to be sent in emergency mode Register */
    unsigned char reserved_458[8];          /**< \brief 458, \internal Reserved */
    Ifx_GTM_DPLL_RCDT_TX RCDT_TX;           /**< \brief 460, DPLL Reciprocal Value of Expected Increment Duration TRIGGER */
    Ifx_GTM_DPLL_RCDT_SX RCDT_SX;           /**< \brief 464, DPLL Reciprocal Value of Expected Increment Duration STATE */
    Ifx_GTM_DPLL_RCDT_TX_NOM RCDT_TX_NOM;   /**< \brief 468, DPLL Reciprocal Value of the Expected Nominal Increment Duration TRIGGER */
    Ifx_GTM_DPLL_RCDT_SX_NOM RCDT_SX_NOM;   /**< \brief 46C, DPLL Reciprocal Value of the Expected Nominal Increment Duration STATE */
    Ifx_GTM_DPLL_RDT_T_ACT RDT_T_ACT;       /**< \brief 470, DPLL Actual Reciprocal Value of TRIGGER */
    Ifx_GTM_DPLL_RDT_S_ACT RDT_S_ACT;       /**< \brief 474, DPLL Actual Reciprocal Value of STATE */
    Ifx_GTM_DPLL_DT_T_ACT DT_T_ACT;         /**< \brief 478, DPLL Duration of Last TRIGGER Increment */
    Ifx_GTM_DPLL_DT_S_ACT DT_S_ACT;         /**< \brief 47C, DPLL Duration of Last STATE Increment [DT_S_ACT] */
    Ifx_GTM_DPLL_EDT_T EDT_T;               /**< \brief 480, DPLL Difference of prediction to actual value of the last TRIGGER increment */
    Ifx_GTM_DPLL_MEDT_T MEDT_T;             /**< \brief 484, DPLL Weighted difference of Prediction up to the Last TRIGGER Increment */
    Ifx_GTM_DPLL_EDT_S EDT_S;               /**< \brief 488, DPLL Difference of Prediction to actual value for Last STATE Increment */
    Ifx_GTM_DPLL_MEDT_S MEDT_S;             /**< \brief 48C, DPLL Weighted difference of Prediction up to the Last STATE Increment */
    Ifx_GTM_DPLL_CDT_TX CDT_TX;             /**< \brief 490, DPLL Prediction of the actual TRIGGER Increment */
    Ifx_GTM_DPLL_CDT_SX CDT_SX;             /**< \brief 494, DPLL Prediction of the actual STATE Increment */
    Ifx_GTM_DPLL_CDT_TX_NOM CDT_TX_NOM;     /**< \brief 498, DPLL Prediction of the nominal TRIGGER Increment duration */
    Ifx_GTM_DPLL_CDT_SX_NOM CDT_SX_NOM;     /**< \brief 49C, DPLL Prediction of the nominal STATE increment duration */
    Ifx_GTM_DPLL_TLR TLR;                   /**< \brief 4A0, DPLL TRIGGER locking range */
    Ifx_GTM_DPLL_SLR SLR;                   /**< \brief 4A4, DPLL STATE Locking Range */
    unsigned char reserved_4A8[88];         /**< \brief 4A8, \internal Reserved */
    Ifx_GTM_DPLL_PDT_T PDT_T[24];           /**< \brief 500, DPLL Projected TRIGGER Increment Sum Relations for Action_i */
    unsigned char reserved_560[96];         /**< \brief 560, \internal Reserved */
    Ifx_GTM_DPLL_MLS1 MLS1;                 /**< \brief 5C0, DPLL Calculated Number of Sub-Pulses between Two STATE Events */
    Ifx_GTM_DPLL_MLS2 MLS2;                 /**< \brief 5C4, DPLL Calculated Number of Sub-Pulses between Two STATE Events */
    Ifx_GTM_DPLL_CNT_NUM1 CNT_NUM1;         /**< \brief 5C8, DPLL Number of Sub-Pulses of SUB_INC1 in Continuous Mode */
    Ifx_GTM_DPLL_CNT_NUM2 CNT_NUM2;         /**< \brief 5CC, DPLL Number of Sub-Pulses of SUB_INC2 in Continuous Mode */
    Ifx_GTM_DPLL_PVT PVT;                   /**< \brief 5D0, DPLL Plausibility Value of Next Active TRIGGER Slope */
    unsigned char reserved_5D4[12];         /**< \brief 5D4, \internal Reserved */
    Ifx_GTM_DPLL_PSTC PSTC;                 /**< \brief 5E0, DPLL Actual Calculated Position Stamp of Last TRIGGER Input */
    Ifx_GTM_DPLL_PSSC PSSC;                 /**< \brief 5E4, DPLL Accurate Calculated Position Stamp of Last STATE Input */
    Ifx_GTM_DPLL_PSTM_0 PSTM_0;             /**< \brief 5E8, DPLL Measured Position Stamp of Last TRIGGER Input */
    Ifx_GTM_DPLL_PSTM_1 PSTM_1;             /**< \brief 5EC, DPLL Measured Position Stamp of Last TRIGGER Input */
    Ifx_GTM_DPLL_PSSM_0 PSSM_0;             /**< \brief 5F0, DPLL Measured Position Stamp of Last STATE Input */
    Ifx_GTM_DPLL_PSSM_1 PSSM_1;             /**< \brief 5F4, DPLL Measured Position Stamp of Last STATE Input */
    Ifx_GTM_DPLL_NMB_T NMB_T;               /**< \brief 5F8, DPLL Number of Pulses of Current Increment in Normal Mode */
    Ifx_GTM_DPLL_NMB_S NMB_S;               /**< \brief 5FC, DPLL Number of Pulses of Current Increment in Emergency Mode */
    Ifx_GTM_DPLL_RDT_S RDT_S[64];           /**< \brief 600, DPLL Nominal STATE Reciprocal Values in FULL_SCALE */
    Ifx_GTM_DPLL_TSF_S TSF_S[64];           /**< \brief 700, DPLL Time Stamp Field of STATE Events */
    Ifx_GTM_DPLL_ADT_S ADT_S[64];           /**< \brief 800, DPLL Adapt Values for All STATE Increments */
    Ifx_GTM_DPLL_DT_S DT_S[64];             /**< \brief 900, DPLL Nominal STATE Increment Values for FULL_SCALE */
    unsigned char reserved_A00[1024];       /**< \brief A00, \internal Reserved */
    Ifx_GTM_DPLL_TSAC TSAC[24];             /**< \brief E00, DPLL Calculate Time Stamp Register */
    unsigned char reserved_E60[32];         /**< \brief E60, \internal Reserved */
    Ifx_GTM_DPLL_PSAC PSAC[24];             /**< \brief E80, DPLL Calculated Position Value Register */
    unsigned char reserved_EE0[32];         /**< \brief EE0, \internal Reserved */
    Ifx_GTM_DPLL_ACB ACB[6];                /**< \brief F00, DPLL Action Control i Register */
} Ifx_GTM_DPLL;

/** \brief  F2A object */
typedef volatile struct _Ifx_GTM_F2A
{
    Ifx_GTM_F2A_RD_CH RD_CH[8];             /**< \brief 0, F2A ARU RD FIFO address */
    Ifx_GTM_F2A_STR_CH STR_CH[8];           /**< \brief 20, F2A Stream configuration */
    Ifx_GTM_F2A_ENABLE ENABLE;              /**< \brief 40, F2A0 Stream Activation Register */
} Ifx_GTM_F2A;

/** \brief  FIFO object */
typedef volatile struct _Ifx_GTM_FIFO
{
    Ifx_GTM_FIFO_CH CH[8];                  /**< \brief 0, FIFO channel */
} Ifx_GTM_FIFO;

/** \brief  ICM object */
typedef volatile struct _Ifx_GTM_ICM
{
    Ifx_GTM_ICM_IRQG_0 IRQG_0;              /**< \brief 0, GTM Infrastructure Interrupt Group */
    Ifx_GTM_ICM_IRQG_1 IRQG_1;              /**< \brief 4, GTM DPLL Interrupt Group */
    Ifx_GTM_ICM_IRQG_2 IRQG_2;              /**< \brief 8, TIM Interrupt Group 0 */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_GTM_ICM_IRQG_4 IRQG_4;              /**< \brief 10, MCS Interrupt Group 0 */
    unsigned char reserved_14[4];           /**< \brief 14, \internal Reserved */
    Ifx_GTM_ICM_IRQG_6 IRQG_6;              /**< \brief 18, TOM Interrupt Group 0 */
    unsigned char reserved_1C[8];           /**< \brief 1C, \internal Reserved */
    Ifx_GTM_ICM_IRQG_9 IRQG_9;              /**< \brief 24, ATOM Interrupt Group 0 */
    unsigned char reserved_28[8];           /**< \brief 28, \internal Reserved */
    Ifx_GTM_ICM_IRQG_MEI IRQG_MEI;          /**< \brief 30, ICM Module Error Interrupt Register */
    Ifx_GTM_ICM_IRQG_CEI0 IRQG_CEI0;        /**< \brief 34, ICM Channel Error Interrupt 0 Register */
    Ifx_GTM_ICM_IRQG_CEI1 IRQG_CEI1;        /**< \brief 38, ICM Channel Error Interrupt 1 Register */
    unsigned char reserved_3C[4];           /**< \brief 3C, \internal Reserved */
    Ifx_GTM_ICM_IRQG_CEI3 IRQG_CEI3;        /**< \brief 40, ICM Channel Error Interrupt 3 Register */
} Ifx_GTM_ICM;

/** \brief  INSEL / OUTSEL object */
typedef volatile struct _Ifx_GTM_INOUTSEL
{
    Ifx_GTM_INOUTSEL_TIM TIM[3];            /**< \brief 0, TIM */
    unsigned char reserved_C[20];           /**< \brief C, \internal Reserved */
    Ifx_GTM_INOUTSEL_T T;                   /**< \brief 20, Timer */
    unsigned char reserved_48[36];          /**< \brief 48, \internal Reserved */
    Ifx_GTM_INOUTSEL_DSADC DSADC;           /**< \brief 6C, DSADC */
    unsigned char reserved_84[12];          /**< \brief 84, \internal Reserved */
    Ifx_GTM_INOUTSEL_CAN CAN;               /**< \brief 90, CAN */
    Ifx_GTM_INOUTSEL_PSI5 PSI5;             /**< \brief 94, PSI5 */
    Ifx_GTM_INOUTSEL_PSI5S PSI5S;           /**< \brief 98, PSI5S */
} Ifx_GTM_INOUTSEL;

/** \brief  MCS objects */
typedef volatile struct _Ifx_GTM_MCS
{
    Ifx_GTM_MCS_CH0 CH0;                    /**< \brief 0, MCS channel0 object */
    unsigned char reserved_58[28];          /**< \brief 58, \internal Reserved */
    Ifx_GTM_MCS_CTRL CTRL;                  /**< \brief 74, MCS Control Register */
    Ifx_GTM_MCS_RST RST;                    /**< \brief 78, MCS Channel Reset Register */
    Ifx_GTM_MCS_ERR ERR;                    /**< \brief 7C, MCS Error Register */
    Ifx_GTM_MCS_CH CH1;                     /**< \brief 80, MCS channel objects */
    Ifx_GTM_MCS_CH CH2;                     /**< \brief 100, MCS channel objects */
    Ifx_GTM_MCS_CH CH3;                     /**< \brief 180, MCS channel objects */
    Ifx_GTM_MCS_CH CH4;                     /**< \brief 200, MCS channel objects */
    Ifx_GTM_MCS_CH CH5;                     /**< \brief 280, MCS channel objects */
    Ifx_GTM_MCS_CH CH6;                     /**< \brief 300, MCS channel objects */
    Ifx_GTM_MCS_CH CH7;                     /**< \brief 380, MCS channel objects */
    unsigned char reserved_400[3072];       /**< \brief 400, \internal Reserved */
} Ifx_GTM_MCS;

/** \brief  MON object */
typedef volatile struct _Ifx_GTM_MON
{
    Ifx_GTM_MON_STATUS STATUS;              /**< \brief 0, Monitor Status Register */
    Ifx_GTM_MON_ACTIVITY_0 ACTIVITY_0;      /**< \brief 4, Monitor Activity Register 0 */
} Ifx_GTM_MON;

/** \brief  MSC input */
typedef volatile struct _Ifx_GTM_MSCIN
{
    Ifx_GTM_MSCIN_INLCON INLCON;            /**< \brief 0, MSC Input Low Control Register */
    Ifx_GTM_MSCIN_INHCON INHCON;            /**< \brief 4, MSC Input High Control Register */
} Ifx_GTM_MSCIN;

/** \brief  MSC objects */
typedef volatile struct _Ifx_GTM_MSCSET
{
    Ifx_GTM_MSCSET_CON0 CON0;               /**< \brief 0, MSC Set Control 0 Register */
    Ifx_GTM_MSCSET_CON1 CON1;               /**< \brief 4, MSC Set Control 1 Register */
    Ifx_GTM_MSCSET_CON2 CON2;               /**< \brief 8, MSC Set Control 2 Register */
    Ifx_GTM_MSCSET_CON3 CON3;               /**< \brief C, MSC Set Control 3 Register */
} Ifx_GTM_MSCSET;

/** \brief  SPE objects */
typedef volatile struct _Ifx_GTM_SPE
{
    Ifx_GTM_SPE_CTRL_STAT CTRL_STAT;        /**< \brief 0, SPE Control Status Register */
    Ifx_GTM_SPE_PAT PAT;                    /**< \brief 4, SPE Input Pattern Definition Register */
    Ifx_GTM_SPE_OUT_PAT OUT_PAT[8];         /**< \brief 8, SPE Output Definition Register */
    Ifx_GTM_SPE_OUT_CTRL OUT_CTRL;          /**< \brief 28, SPE Output Control Register */
    Ifx_GTM_SPE_IRQ_NOTIFY IRQ_NOTIFY;      /**< \brief 2C, SPE Interrupt Notification Register */
    Ifx_GTM_SPE_IRQ_EN IRQ_EN;              /**< \brief 30, SPE Interrupt Enable Register */
    Ifx_GTM_SPE_IRQ_FORCINT IRQ_FORCINT;    /**< \brief 34, SPE Interrupt Generation by Software */
    Ifx_GTM_SPE_IRQ_MODE IRQ_MODE;          /**< \brief 38, SPE IRQ Mode Configuration Register */
    Ifx_GTM_SPE_EIRQ_EN EIRQ_EN;            /**< \brief 3C, SPE Error Interrupt Enable Register */
    Ifx_GTM_SPE_CNT CNT;                    /**< \brief 40, SPE Revolution Counter Register */
    Ifx_GTM_SPE_CMP CMP;                    /**< \brief 44, SPE Revolution Compare Register */
    unsigned char reserved_48[56];          /**< \brief 48, \internal Reserved */
} Ifx_GTM_SPE;

/** \brief  TBU object */
typedef volatile struct _Ifx_GTM_TBU
{
    Ifx_GTM_TBU_CHEN CHEN;                  /**< \brief 0, TBU Global Channel Enable Register */
    Ifx_GTM_TBU_CH0_CTRL CH0_CTRL;          /**< \brief 4, TBU Channel 0 Control Register */
    Ifx_GTM_TBU_CH0_BASE CH0_BASE;          /**< \brief 8, TBU Channel 0 Base Register */
    Ifx_GTM_TBU_CH1_CTRL CH1_CTRL;          /**< \brief C, TBU Channel 1 Control Register */
    Ifx_GTM_TBU_CH1_BASE CH1_BASE;          /**< \brief 10, TBU Channel 1 Base Register */
    Ifx_GTM_TBU_CH2_CTRL CH2_CTRL;          /**< \brief 14, TBU Channel 2 Control Register */
    Ifx_GTM_TBU_CH2_BASE CH2_BASE;          /**< \brief 18, TBU Channel 2 Base Register */
} Ifx_GTM_TBU;

/** \brief  TIM objects */
typedef volatile struct _Ifx_GTM_TIM
{
    Ifx_GTM_TIM_CH CH0;                     /**< \brief 0, TIM channel objects */
    Ifx_GTM_TIM_IN_SRC IN_SRC;              /**< \brief 78, TIM_IN_SRC Long Name */
    Ifx_GTM_TIM_RST RST;                    /**< \brief 7C, TIM Global Software Reset Register */
    Ifx_GTM_TIM_CH CH1;                     /**< \brief 80, TIM channel objects */
    unsigned char reserved_F8[8];           /**< \brief F8, \internal Reserved */
    Ifx_GTM_TIM_CH CH2;                     /**< \brief 100, TIM channel objects */
    unsigned char reserved_178[8];          /**< \brief 178, \internal Reserved */
    Ifx_GTM_TIM_CH CH3;                     /**< \brief 180, TIM channel objects */
    unsigned char reserved_1F8[8];          /**< \brief 1F8, \internal Reserved */
    Ifx_GTM_TIM_CH CH4;                     /**< \brief 200, TIM channel objects */
    unsigned char reserved_278[8];          /**< \brief 278, \internal Reserved */
    Ifx_GTM_TIM_CH CH5;                     /**< \brief 280, TIM channel objects */
    unsigned char reserved_2F8[8];          /**< \brief 2F8, \internal Reserved */
    Ifx_GTM_TIM_CH CH6;                     /**< \brief 300, TIM channel objects */
    unsigned char reserved_378[8];          /**< \brief 378, \internal Reserved */
    Ifx_GTM_TIM_CH CH7;                     /**< \brief 380, TIM channel objects */
    unsigned char reserved_3F8[1032];       /**< \brief 3F8, \internal Reserved */
} Ifx_GTM_TIM;

/** \brief  TOM objects */
typedef volatile struct _Ifx_GTM_TOM
{
    Ifx_GTM_TOM_CH CH0;                     /**< \brief 0, TOM channel objects */
    Ifx_GTM_TOM_TGC0_GLB_CTRL TGC0_GLB_CTRL;    /**< \brief 30, TOM TGC0 Global Control Register */
    Ifx_GTM_TOM_TGC0_ACT_TB TGC0_ACT_TB;    /**< \brief 34, TOM TGC0 Action Time Base Register */
    Ifx_GTM_TOM_TGC0_FUPD_CTRL TGC0_FUPD_CTRL;  /**< \brief 38, TOM TGC0 Force Update Control Register */
    Ifx_GTM_TOM_TGC0_INT_TRIG TGC0_INT_TRIG;    /**< \brief 3C, TOM TGC0 Internal Trigger Control Register */
    Ifx_GTM_TOM_CH CH1;                     /**< \brief 40, TOM channel objects */
    Ifx_GTM_TOM_TGC0_ENDIS_CTRL TGC0_ENDIS_CTRL;    /**< \brief 70, TOM TGC0 Enable/Disable Control Register */
    Ifx_GTM_TOM_TGC0_ENDIS_STAT TGC0_ENDIS_STAT;    /**< \brief 74, TOM TGC0 Enable/Disable Status Register */
    Ifx_GTM_TOM_TGC0_OUTEN_CTRL TGC0_OUTEN_CTRL;    /**< \brief 78, TOM TGC0 Output Enable Control Register */
    Ifx_GTM_TOM_TGC0_OUTEN_STAT TGC0_OUTEN_STAT;    /**< \brief 7C, TOM TGC0 Output Enable Status Register */
    Ifx_GTM_TOM_CH CH2;                     /**< \brief 80, TOM channel objects */
    unsigned char reserved_B0[16];          /**< \brief B0, \internal Reserved */
    Ifx_GTM_TOM_CH CH3;                     /**< \brief C0, TOM channel objects */
    unsigned char reserved_F0[16];          /**< \brief F0, \internal Reserved */
    Ifx_GTM_TOM_CH CH4;                     /**< \brief 100, TOM channel objects */
    unsigned char reserved_130[16];         /**< \brief 130, \internal Reserved */
    Ifx_GTM_TOM_CH CH5;                     /**< \brief 140, TOM channel objects */
    unsigned char reserved_170[16];         /**< \brief 170, \internal Reserved */
    Ifx_GTM_TOM_CH CH6;                     /**< \brief 180, TOM channel objects */
    unsigned char reserved_1B0[16];         /**< \brief 1B0, \internal Reserved */
    Ifx_GTM_TOM_CH CH7;                     /**< \brief 1C0, TOM channel objects */
    unsigned char reserved_1F0[16];         /**< \brief 1F0, \internal Reserved */
    Ifx_GTM_TOM_CH CH8;                     /**< \brief 200, TOM channel objects */
    Ifx_GTM_TOM_TGC1_GLB_CTRL TGC1_GLB_CTRL;    /**< \brief 230, TOM TGC1 Global Control Register */
    Ifx_GTM_TOM_TGC1_ACT_TB TGC1_ACT_TB;    /**< \brief 234, TOM TGC1 Action Time Base Register */
    Ifx_GTM_TOM_TGC1_FUPD_CTRL TGC1_FUPD_CTRL;  /**< \brief 238, TOM TGC1 Force Update Control Register */
    Ifx_GTM_TOM_TGC1_INT_TRIG TGC1_INT_TRIG;    /**< \brief 23C, TOM TGC1 Internal Trigger Control Register */
    Ifx_GTM_TOM_CH CH9;                     /**< \brief 240, TOM channel objects */
    Ifx_GTM_TOM_TGC1_ENDIS_CTRL TGC1_ENDIS_CTRL;    /**< \brief 270, TOM TGC1 Enable/Disable Control Register */
    Ifx_GTM_TOM_TGC1_ENDIS_STAT TGC1_ENDIS_STAT;    /**< \brief 274, TOM TGC1 Enable/Disable Status Register */
    Ifx_GTM_TOM_TGC1_OUTEN_CTRL TGC1_OUTEN_CTRL;    /**< \brief 278, TOM TGC1 Output Enable Control Register */
    Ifx_GTM_TOM_TGC1_OUTEN_STAT TGC1_OUTEN_STAT;    /**< \brief 27C, TOM TGC1 Output Enable Status Register */
    Ifx_GTM_TOM_CH CH10;                    /**< \brief 280, TOM channel objects */
    unsigned char reserved_2B0[16];         /**< \brief 2B0, \internal Reserved */
    Ifx_GTM_TOM_CH CH11;                    /**< \brief 2C0, TOM channel objects */
    unsigned char reserved_2F0[16];         /**< \brief 2F0, \internal Reserved */
    Ifx_GTM_TOM_CH CH12;                    /**< \brief 300, TOM channel objects */
    unsigned char reserved_330[16];         /**< \brief 330, \internal Reserved */
    Ifx_GTM_TOM_CH CH13;                    /**< \brief 340, TOM channel objects */
    unsigned char reserved_370[16];         /**< \brief 370, \internal Reserved */
    Ifx_GTM_TOM_CH CH14;                    /**< \brief 380, TOM channel objects */
    unsigned char reserved_3B0[16];         /**< \brief 3B0, \internal Reserved */
    Ifx_GTM_TOM_CH CH15;                    /**< \brief 3C0, TOM channel objects */
    unsigned char reserved_3F0[1040];       /**< \brief 3F0, \internal Reserved */
} Ifx_GTM_TOM;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Gtm_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  GTM object */
typedef volatile struct _Ifx_GTM
{
    Ifx_GTM_REV REV;                        /**< \brief 0, GTM Version Control Register */
    Ifx_GTM_RST RST;                        /**< \brief 4, GTM Global Reset Register */
    Ifx_GTM_CTRL CTRL;                      /**< \brief 8, GTM Global Control Register */
    Ifx_GTM_AEI_ADDR_XPT AEI_ADDR_XPT;      /**< \brief C, GTM AEI Timeout Exception Address Register */
    Ifx_GTM_IRQ_NOTIFY IRQ_NOTIFY;          /**< \brief 10, GTM Interrupt Notification Register */
    Ifx_GTM_IRQ_EN IRQ_EN;                  /**< \brief 14, GTM Interrupt Enable Register */
    Ifx_GTM_IRQ_FORCINT IRQ_FORCINT;        /**< \brief 18, GTM Software Interrupt Generation Register */
    Ifx_GTM_IRQ_MODE IRQ_MODE;              /**< \brief 1C, GTM Top Level Interrupts Mode Selection */
    Ifx_GTM_EIRQ_EN EIRQ_EN;                /**< \brief 20, GTM Error Interrupt Enable Register */
    unsigned char reserved_24[12];          /**< \brief 24, \internal Reserved */
    Ifx_GTM_BRIDGE BRIDGE;                  /**< \brief 30, BRIDGE object */
    unsigned char reserved_3C[4];           /**< \brief 3C, \internal Reserved */
    Ifx_GTM_TIM_AUX_IN_SRC TIM_AUX_IN_SRC[3];   /**< \brief 40, GTM TIM  AUX_IN_SRC */
    unsigned char reserved_4C[180];         /**< \brief 4C, \internal Reserved */
    Ifx_GTM_TBU TBU;                        /**< \brief 100, TBU object */
    unsigned char reserved_11C[100];        /**< \brief 11C, \internal Reserved */
    Ifx_GTM_MON MON;                        /**< \brief 180, MON object */
    unsigned char reserved_188[120];        /**< \brief 188, \internal Reserved */
    Ifx_GTM_CMP CMP;                        /**< \brief 200, CMP object */
    unsigned char reserved_218[104];        /**< \brief 218, \internal Reserved */
    Ifx_GTM_ARU ARU;                        /**< \brief 280, ARU object */
    unsigned char reserved_2B4[76];         /**< \brief 2B4, \internal Reserved */
    Ifx_GTM_CMU CMU;                        /**< \brief 300, CMU object */
    unsigned char reserved_348[184];        /**< \brief 348, \internal Reserved */
    Ifx_GTM_BRC BRC;                        /**< \brief 400, BRC object */
    unsigned char reserved_478[392];        /**< \brief 478, \internal Reserved */
    Ifx_GTM_ICM ICM;                        /**< \brief 600, ICM object */
    unsigned char reserved_644[444];        /**< \brief 644, \internal Reserved */
    Ifx_GTM_SPE SPE[2];                     /**< \brief 800, SPE objects */
    unsigned char reserved_900[1536];       /**< \brief 900, \internal Reserved */
    Ifx_GTM_MAP_CTRL MAP_CTRL;              /**< \brief F00, MAP Control Register */
    unsigned char reserved_F04[60];         /**< \brief F04, \internal Reserved */
    Ifx_GTM_MCFG_CTRL MCFG_CTRL;            /**< \brief F40, Memory Layout Configuration Register */
    unsigned char reserved_F44[188];        /**< \brief F44, \internal Reserved */
    Ifx_GTM_TIM TIM[3];                     /**< \brief 1000, TIM objects */
    unsigned char reserved_2800[22528];     /**< \brief 2800, \internal Reserved */
    Ifx_GTM_TOM TOM[2];                     /**< \brief 8000, TOM objects */
    unsigned char reserved_9000[16384];     /**< \brief 9000, \internal Reserved */
    Ifx_GTM_ATOM ATOM[4];                   /**< \brief D000, ATOM objects */
    unsigned char reserved_F000[36864];     /**< \brief F000, \internal Reserved */
    Ifx_GTM_F2A F2A0;                       /**< \brief 18000, F2A object */
    unsigned char reserved_18044[60];       /**< \brief 18044, \internal Reserved */
    Ifx_GTM_AFD AFD0;                       /**< \brief 18080, AFD object */
    unsigned char reserved_18100[768];      /**< \brief 18100, \internal Reserved */
    Ifx_GTM_FIFO FIFO0;                     /**< \brief 18400, FIFO object */
    unsigned char reserved_18600[64000];    /**< \brief 18600, \internal Reserved */
    Ifx_GTM_DPLL DPLL;                      /**< \brief 28000, DPLL object */
    unsigned char reserved_28F18[28904];    /**< \brief 28F18, \internal Reserved */
    Ifx_GTM_MCS MCS[3];                     /**< \brief 30000, MCS objects */
    unsigned char reserved_33000[445696];   /**< \brief 33000, \internal Reserved */
    Ifx_GTM_CLC CLC;                        /**< \brief 9FD00, Clock Control Register */
    unsigned char reserved_9FD04[12];       /**< \brief 9FD04, \internal Reserved */
    Ifx_GTM_INOUTSEL INOUTSEL;              /**< \brief 9FD10, INSEL / OUTSEL object */
    unsigned char reserved_9FDAC[4];        /**< \brief 9FDAC, \internal Reserved */
    Ifx_GTM_ADCTRIG0OUT0 ADCTRIG0OUT0;      /**< \brief 9FDB0, ADC Trigger 0 Output Select 0 Register */
    unsigned char reserved_9FDB4[4];        /**< \brief 9FDB4, \internal Reserved */
    Ifx_GTM_ADCTRIG1OUT0 ADCTRIG1OUT0;      /**< \brief 9FDB8, ADC Trigger 1 Output Select 0 Register */
    unsigned char reserved_9FDBC[8];        /**< \brief 9FDBC, \internal Reserved */
    Ifx_GTM_OTBU0T OTBU0T;                  /**< \brief 9FDC4, OCDS TBU0 Trigger Register */
    Ifx_GTM_OTBU1T OTBU1T;                  /**< \brief 9FDC8, OCDS TBU1 Trigger Register */
    Ifx_GTM_OTBU2T OTBU2T;                  /**< \brief 9FDCC, OCDS TBU2 Trigger Register */
    Ifx_GTM_OTSS OTSS;                      /**< \brief 9FDD0, OCDS Trigger Set Select Register */
    Ifx_GTM_OTSC0 OTSC0;                    /**< \brief 9FDD4, OCDS Trigger Set Control 0 Register */
    Ifx_GTM_OTSC1 OTSC1;                    /**< \brief 9FDD8, OCDS Trigger Set Control 1 Register */
    Ifx_GTM_ODA ODA;                        /**< \brief 9FDDC, OCDS Debug Access Register */
    unsigned char reserved_9FDE0[8];        /**< \brief 9FDE0, \internal Reserved */
    Ifx_GTM_OCS OCS;                        /**< \brief 9FDE8, OCDS Control and Status */
    Ifx_GTM_KRSTCLR KRSTCLR;                /**< \brief 9FDEC, Kernel Reset Status Clear Register */
    Ifx_GTM_KRST1 KRST1;                    /**< \brief 9FDF0, Kernel Reset Register 1 */
    Ifx_GTM_KRST0 KRST0;                    /**< \brief 9FDF4, Kernel Reset Register 0 */
    Ifx_GTM_ACCEN1 ACCEN1;                  /**< \brief 9FDF8, Access Enable Register 1 */
    Ifx_GTM_ACCEN0 ACCEN0;                  /**< \brief 9FDFC, Access Enable Register 0 */
    Ifx_GTM_DXOUTCON DXOUTCON;              /**< \brief 9FE00, Data Exchange Output Control Register */
    Ifx_GTM_TRIGOUT TRIGOUT0[3];            /**< \brief 9FE04, Trigger Output Register */
    unsigned char reserved_9FE10[52];       /**< \brief 9FE10, \internal Reserved */
    Ifx_GTM_TRIGOUT TRIGOUT1[3];            /**< \brief 9FE44, Trigger Output Register */
    unsigned char reserved_9FE50[32];       /**< \brief 9FE50, \internal Reserved */
    Ifx_GTM_MCSINTSTAT MCSINTSTAT;          /**< \brief 9FE70, MCS Interrupt Status Register */
    Ifx_GTM_MCSINTCLR MCSINTCLR;            /**< \brief 9FE74, MCS Interrupt Clear Register */
    unsigned char reserved_9FE78[24];       /**< \brief 9FE78, \internal Reserved */
    Ifx_GTM_DXINCON DXINCON;                /**< \brief 9FE90, Data Exchange Input Control Register */
    Ifx_GTM_DATAIN DATAIN0[3];              /**< \brief 9FE94, Data Input 0 0 Register */
    unsigned char reserved_9FEA0[52];       /**< \brief 9FEA0, \internal Reserved */
    Ifx_GTM_DATAIN DATAIN1[3];              /**< \brief 9FED4, Data Input 0 Register */
    unsigned char reserved_9FEE0[32];       /**< \brief 9FEE0, \internal Reserved */
    Ifx_GTM_MSCSET MSCSET_1S[4];            /**< \brief 9FF00, MSC objects \note Array index shifted by 1. Example: defined register MSCSET_1S[0]/MSCSET_1S0 corresponds to user manual MSCSET_1S1, ... */
    unsigned char reserved_9FF40[32];       /**< \brief 9FF40, \internal Reserved */
    Ifx_GTM_MSCIN MSCIN[2];                 /**< \brief 9FF60, MSC input */
    Ifx_GTM_MSC0INLEXTCON MSC0INLEXTCON;    /**< \brief 9FF70, MSC0 Input Low Extended Control Register */
    unsigned char reserved_9FF74[140];      /**< \brief 9FF74, \internal Reserved */
} Ifx_GTM;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#if defined (__TASKING__)
#pragma warning restore
#endif
/******************************************************************************/
#endif /* IFXGTM_REGDEF_H */
