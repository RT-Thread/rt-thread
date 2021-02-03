/**
 * \file IfxDma_regdef.h
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
 * \defgroup IfxLld_Dma Dma
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Dma_Bitfields Bitfields
 * \ingroup IfxLld_Dma
 * 
 * \defgroup IfxLld_Dma_union Union
 * \ingroup IfxLld_Dma
 * 
 * \defgroup IfxLld_Dma_struct Struct
 * \ingroup IfxLld_Dma
 * 
 */
#ifndef IFXDMA_REGDEF_H
#define IFXDMA_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Dma_Bitfields
 * \{  */

/** \brief  DMA Hardware Resource 0 Access Enable Register 0 */
typedef struct _Ifx_DMA_ACCEN00_Bits
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
} Ifx_DMA_ACCEN00_Bits;

/** \brief  DMA Hardware Resource 0 Access Enable Register 1 */
typedef struct _Ifx_DMA_ACCEN01_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_DMA_ACCEN01_Bits;

/** \brief  DMA Hardware Resource 1 Access Enable Register 0 */
typedef struct _Ifx_DMA_ACCEN10_Bits
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
} Ifx_DMA_ACCEN10_Bits;

/** \brief  DMA Hardware Resource 1 Access Enable Register 1 */
typedef struct _Ifx_DMA_ACCEN11_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_DMA_ACCEN11_Bits;

/** \brief  DMA Hardware Resource 2 Access Enable Register 0 */
typedef struct _Ifx_DMA_ACCEN20_Bits
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
} Ifx_DMA_ACCEN20_Bits;

/** \brief  DMA Hardware Resource 2 Access Enable Register 1 */
typedef struct _Ifx_DMA_ACCEN21_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_DMA_ACCEN21_Bits;

/** \brief  DMA Hardware Resource 3 Access Enable Register 0 */
typedef struct _Ifx_DMA_ACCEN30_Bits
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
} Ifx_DMA_ACCEN30_Bits;

/** \brief  DMA Hardware Resource 3 Access Enable Register 1 */
typedef struct _Ifx_DMA_ACCEN31_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_DMA_ACCEN31_Bits;

/** \brief  DMA Clear Error Register */
typedef struct _Ifx_DMA_BLK_CLRE_Bits
{
    unsigned int reserved_0:16;             /**< \brief \internal Reserved */
    unsigned int CSER:1;                    /**< \brief [16:16] Clear Move Engine x Source Error (w) */
    unsigned int CDER:1;                    /**< \brief [17:17] Clear Move Engine x Destination Error (w) */
    unsigned int reserved_18:2;             /**< \brief \internal Reserved */
    unsigned int CSPBER:1;                  /**< \brief [20:20] Clear SPB Error (w) */
    unsigned int CSRIER:1;                  /**< \brief [21:21] Clear SRI Error (w) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int CRAMER:1;                  /**< \brief [24:24] Clear RAM Error (w) */
    unsigned int CSLLER:1;                  /**< \brief [25:25] Clear SLL Error (w) */
    unsigned int CDLLER:1;                  /**< \brief [26:26] Clear DLL Error (w) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_DMA_BLK_CLRE_Bits;

/** \brief  DMA Enable Error Register */
typedef struct _Ifx_DMA_BLK_EER_Bits
{
    unsigned int reserved_0:16;             /**< \brief \internal Reserved */
    unsigned int ESER:1;                    /**< \brief [16:16] Enable Move Engine x Source Error (rw) */
    unsigned int EDER:1;                    /**< \brief [17:17] Enable Move Engine x Destination Error (rw) */
    unsigned int reserved_18:6;             /**< \brief \internal Reserved */
    unsigned int ERER:1;                    /**< \brief [24:24] Enable Move Engine x RAM Error (rw) */
    unsigned int reserved_25:1;             /**< \brief \internal Reserved */
    unsigned int ELER:1;                    /**< \brief [26:26] Enable Move Engine x DMA Linked List Error (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_DMA_BLK_EER_Bits;

/** \brief  DMA Error Status Register */
typedef struct _Ifx_DMA_BLK_ERRSR_Bits
{
    unsigned int LEC:7;                     /**< \brief [6:0] Move Engine x Last Error Channel (rh) */
    unsigned int reserved_7:9;              /**< \brief \internal Reserved */
    unsigned int SER:1;                     /**< \brief [16:16] Move Engine x Source Error (rh) */
    unsigned int DER:1;                     /**< \brief [17:17] Move Engine x Destination Error (rh) */
    unsigned int reserved_18:2;             /**< \brief \internal Reserved */
    unsigned int SPBER:1;                   /**< \brief [20:20] Move Engine x SPB Bus Error (rh) */
    unsigned int SRIER:1;                   /**< \brief [21:21] Move Engine x SRI Bus Error (rh) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int RAMER:1;                   /**< \brief [24:24] Move Engine x RAM Error (rh) */
    unsigned int SLLER:1;                   /**< \brief [25:25] Move Engine x Safe Linked List Error (rh) */
    unsigned int DLLER:1;                   /**< \brief [26:26] Move Engine x DMA Linked List Error (rh) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_DMA_BLK_ERRSR_Bits;

/** \brief  DMA Move Engine Channel Address and Interrupt Control Register */
typedef struct _Ifx_DMA_BLK_ME_ADICR_Bits
{
    unsigned int SMF:3;                     /**< \brief [2:0] Source Address Modification Factor (rh) */
    unsigned int INCS:1;                    /**< \brief [3:3] Increment of Source Address (rh) */
    unsigned int DMF:3;                     /**< \brief [6:4] Destination Address Modification Factor (rh) */
    unsigned int INCD:1;                    /**< \brief [7:7] Increment of Destination Address (rh) */
    unsigned int CBLS:4;                    /**< \brief [11:8] Circular Buffer Length Source (rh) */
    unsigned int CBLD:4;                    /**< \brief [15:12] Circular Buffer Length Destination (rh) */
    unsigned int SHCT:4;                    /**< \brief [19:16] Shadow Control (rh) */
    unsigned int SCBE:1;                    /**< \brief [20:20] Source Circular Buffer Enable (rh) */
    unsigned int DCBE:1;                    /**< \brief [21:21] Destination Circular Buffer Enable (rh) */
    unsigned int STAMP:1;                   /**< \brief [22:22] Time Stamp (rh) */
    unsigned int ETRL:1;                    /**< \brief [23:23] Enable Transaction Request Lost Interrupt (rh) */
    unsigned int WRPSE:1;                   /**< \brief [24:24] Wrap Source Enable (rh) */
    unsigned int WRPDE:1;                   /**< \brief [25:25] Wrap Destination Enable (rh) */
    unsigned int INTCT:2;                   /**< \brief [27:26] Interrupt Control (rh) */
    unsigned int IRDV:4;                    /**< \brief [31:28] Interrupt Raise Detect Value (rh) */
} Ifx_DMA_BLK_ME_ADICR_Bits;

/** \brief  DMA Move Engine Channel Control Register */
typedef struct _Ifx_DMA_BLK_ME_CHCR_Bits
{
    unsigned int TREL:14;                   /**< \brief [13:0] Transfer Reload Value (rh) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int BLKM:3;                    /**< \brief [18:16] Block Mode (rh) */
    unsigned int RROAT:1;                   /**< \brief [19:19] Reset Request Only After Transaction (rh) */
    unsigned int CHMODE:1;                  /**< \brief [20:20] Channel Operation Mode (rh) */
    unsigned int CHDW:3;                    /**< \brief [23:21] Channel Data Width (rh) */
    unsigned int PATSEL:3;                  /**< \brief [26:24] Pattern Select (rh) */
    unsigned int reserved_27:1;             /**< \brief \internal Reserved */
    unsigned int PRSEL:1;                   /**< \brief [28:28] Peripheral Request Select (rh) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int DMAPRIO:2;                 /**< \brief [31:30] DMA Priority (rh) */
} Ifx_DMA_BLK_ME_CHCR_Bits;

/** \brief  DMA Move Engine Channel Status Register */
typedef struct _Ifx_DMA_BLK_ME_CHSR_Bits
{
    unsigned int TCOUNT:14;                 /**< \brief [13:0] Transfer Count Status (rh) */
    unsigned int reserved_14:1;             /**< \brief \internal Reserved */
    unsigned int LXO:1;                     /**< \brief [15:15] Old Value of Pattern Detection (rh) */
    unsigned int WRPS:1;                    /**< \brief [16:16] Wrap Source Buffer (rh) */
    unsigned int WRPD:1;                    /**< \brief [17:17] Wrap Destination Buffer (rh) */
    unsigned int ICH:1;                     /**< \brief [18:18] Interrupt from Channel (rh) */
    unsigned int IPM:1;                     /**< \brief [19:19] Pattern Detection from Channel (rh) */
    unsigned int reserved_20:2;             /**< \brief \internal Reserved */
    unsigned int BUFFER:1;                  /**< \brief [22:22] DMA Double Buffering Active Buffer (rh) */
    unsigned int FROZEN:1;                  /**< \brief [23:23] DMA Double Buffering Frozen Buffer (rh) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_DMA_BLK_ME_CHSR_Bits;

/** \brief  DMA Move Engine Channel Destination Address Register x */
typedef struct _Ifx_DMA_BLK_ME_DADR_Bits
{
    unsigned int DADR:32;                   /**< \brief [31:0] Destination Address (rh) */
} Ifx_DMA_BLK_ME_DADR_Bits;

/** \brief  DMA Move Engine Read Register 0 */
typedef struct _Ifx_DMA_BLK_ME_R0_Bits
{
    unsigned int RD00:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD01:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD02:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD03:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R0_Bits;

/** \brief  DMA Move Engine Read Register 1 */
typedef struct _Ifx_DMA_BLK_ME_R1_Bits
{
    unsigned int RD10:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD11:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD12:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD13:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R1_Bits;

/** \brief  DMA Move Engine Read Register 2 */
typedef struct _Ifx_DMA_BLK_ME_R2_Bits
{
    unsigned int RD20:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD21:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD22:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD23:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R2_Bits;

/** \brief  DMA Move Engine Read Register 3 */
typedef struct _Ifx_DMA_BLK_ME_R3_Bits
{
    unsigned int RD30:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD31:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD32:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD33:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R3_Bits;

/** \brief  DMA Move Engine Read Register 4 */
typedef struct _Ifx_DMA_BLK_ME_R4_Bits
{
    unsigned int RD40:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD41:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD42:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD43:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R4_Bits;

/** \brief  DMA Move Engine Read Register 5 */
typedef struct _Ifx_DMA_BLK_ME_R5_Bits
{
    unsigned int RD50:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD51:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD52:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD53:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R5_Bits;

/** \brief  DMA Move Engine Read Register 6 */
typedef struct _Ifx_DMA_BLK_ME_R6_Bits
{
    unsigned int RD60:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD61:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD62:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD63:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R6_Bits;

/** \brief  DMA Move Engine Read Register 7 */
typedef struct _Ifx_DMA_BLK_ME_R7_Bits
{
    unsigned int RD70:8;                    /**< \brief [7:0] Read Value for Move Engine x (rh) */
    unsigned int RD71:8;                    /**< \brief [15:8] Read Value for Move Engine x (rh) */
    unsigned int RD72:8;                    /**< \brief [23:16] Read Value for Move Engine x (rh) */
    unsigned int RD73:8;                    /**< \brief [31:24] Read Value for Move Engine x (rh) */
} Ifx_DMA_BLK_ME_R7_Bits;

/** \brief  DMA Move Engine Channel Read Data CRC Register */
typedef struct _Ifx_DMA_BLK_ME_RDCRC_Bits
{
    unsigned int RDCRC:32;                  /**< \brief [31:0] Read Data CRC (rh) */
} Ifx_DMA_BLK_ME_RDCRC_Bits;

/** \brief  DMA Move Engine Channel Source Address Register */
typedef struct _Ifx_DMA_BLK_ME_SADR_Bits
{
    unsigned int SADR:32;                   /**< \brief [31:0] Source Start Address (rh) */
} Ifx_DMA_BLK_ME_SADR_Bits;

/** \brief  DMA Move Engine Channel Source and Destination Address CRC Register */
typedef struct _Ifx_DMA_BLK_ME_SDCRC_Bits
{
    unsigned int SDCRC:32;                  /**< \brief [31:0] Source and Destination Address CRC (rh) */
} Ifx_DMA_BLK_ME_SDCRC_Bits;

/** \brief  DMA Move Engine Channel Shadow Address Register */
typedef struct _Ifx_DMA_BLK_ME_SHADR_Bits
{
    unsigned int SHADR:32;                  /**< \brief [31:0] Shadowed Address (rh) */
} Ifx_DMA_BLK_ME_SHADR_Bits;

/** \brief  DMA Move Engine Status Register */
typedef struct _Ifx_DMA_BLK_ME_SR_Bits
{
    unsigned int RS:1;                      /**< \brief [0:0] Move Engine x Read Status (rh) */
    unsigned int reserved_1:3;              /**< \brief \internal Reserved */
    unsigned int WS:1;                      /**< \brief [4:4] Move Engine x Write Status (rh) */
    unsigned int reserved_5:11;             /**< \brief \internal Reserved */
    unsigned int CH:7;                      /**< \brief [22:16] Active Channel z in Move Engine x (rh) */
    unsigned int reserved_23:9;             /**< \brief \internal Reserved */
} Ifx_DMA_BLK_ME_SR_Bits;

/** \brief  DMA Channel Address and Interrupt Control Register x */
typedef struct _Ifx_DMA_CH_ADICR_Bits
{
    unsigned int SMF:3;                     /**< \brief [2:0] Source Address Modification Factor (rwh) */
    unsigned int INCS:1;                    /**< \brief [3:3] Increment of Source Address (rwh) */
    unsigned int DMF:3;                     /**< \brief [6:4] Destination Address Modification Factor (rwh) */
    unsigned int INCD:1;                    /**< \brief [7:7] Increment of Destination Address (rwh) */
    unsigned int CBLS:4;                    /**< \brief [11:8] Circular Buffer Length Source (rwh) */
    unsigned int CBLD:4;                    /**< \brief [15:12] Circular Buffer Length Destination (rwh) */
    unsigned int SHCT:4;                    /**< \brief [19:16] Shadow Control (rwh) */
    unsigned int SCBE:1;                    /**< \brief [20:20] Source Circular Buffer Enable (rwh) */
    unsigned int DCBE:1;                    /**< \brief [21:21] Destination Circular Buffer Enable (rwh) */
    unsigned int STAMP:1;                   /**< \brief [22:22] Time Stamp (rwh) */
    unsigned int ETRL:1;                    /**< \brief [23:23] Enable Transaction Request Lost Interrupt (rwh) */
    unsigned int WRPSE:1;                   /**< \brief [24:24] Wrap Source Enable (rwh) */
    unsigned int WRPDE:1;                   /**< \brief [25:25] Wrap Destination Enable (rwh) */
    unsigned int INTCT:2;                   /**< \brief [27:26] Interrupt Control (rwh) */
    unsigned int IRDV:4;                    /**< \brief [31:28] Interrupt Raise Detect Value (rwh) */
} Ifx_DMA_CH_ADICR_Bits;

/** \brief  DMA Channel Configuration Register */
typedef struct _Ifx_DMA_CH_CHCFGR_Bits
{
    unsigned int TREL:14;                   /**< \brief [13:0] Transfer Reload Value (rwh) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int BLKM:3;                    /**< \brief [18:16] Block Mode (rwh) */
    unsigned int RROAT:1;                   /**< \brief [19:19] Reset Request Only After Transaction (rwh) */
    unsigned int CHMODE:1;                  /**< \brief [20:20] Channel Operation Mode (rwh) */
    unsigned int CHDW:3;                    /**< \brief [23:21] Channel Data Width (rwh) */
    unsigned int PATSEL:3;                  /**< \brief [26:24] Pattern Select (rwh) */
    unsigned int reserved_27:1;             /**< \brief \internal Reserved */
    unsigned int PRSEL:1;                   /**< \brief [28:28] Peripheral Request Select (rwh) */
    unsigned int reserved_29:1;             /**< \brief \internal Reserved */
    unsigned int DMAPRIO:2;                 /**< \brief [31:30] DMA Priority (rwh) */
} Ifx_DMA_CH_CHCFGR_Bits;

/** \brief  DMARAM Channel Control and Status Register */
typedef struct _Ifx_DMA_CH_CHCSR_Bits
{
    unsigned int TCOUNT:14;                 /**< \brief [13:0] Transfer Count Status (rh) */
    unsigned int reserved_14:1;             /**< \brief \internal Reserved */
    unsigned int LXO:1;                     /**< \brief [15:15] Old Value of Pattern Detection (rh) */
    unsigned int WRPS:1;                    /**< \brief [16:16] Wrap Source Buffer (rh) */
    unsigned int WRPD:1;                    /**< \brief [17:17] Wrap Destination Buffer (rh) */
    unsigned int ICH:1;                     /**< \brief [18:18] Interrupt from Channel (rh) */
    unsigned int IPM:1;                     /**< \brief [19:19] Pattern Detection from Channel (rh) */
    unsigned int reserved_20:2;             /**< \brief \internal Reserved */
    unsigned int BUFFER:1;                  /**< \brief [22:22] DMA Double Buffering Active Buffer (rh) */
    unsigned int FROZEN:1;                  /**< \brief [23:23] DMA Double Buffering Frozen Buffer (rwh) */
    unsigned int SWB:1;                     /**< \brief [24:24] DMA Double Buffering Switch Buffer (w) */
    unsigned int CWRP:1;                    /**< \brief [25:25] Clear Wrap Buffer Interrupt z (w) */
    unsigned int CICH:1;                    /**< \brief [26:26] Clear Interrupt for DMA Channel z (w) */
    unsigned int SIT:1;                     /**< \brief [27:27] Set Interrupt Trigger for DMA Channel z (w) */
    unsigned int reserved_28:3;             /**< \brief \internal Reserved */
    unsigned int SCH:1;                     /**< \brief [31:31] Set Transaction Request for DMA Channel (w) */
} Ifx_DMA_CH_CHCSR_Bits;

/** \brief  DMA Channel Destination Address Register x */
typedef struct _Ifx_DMA_CH_DADR_Bits
{
    unsigned int DADR:32;                   /**< \brief [31:0] Destination Address (rwh) */
} Ifx_DMA_CH_DADR_Bits;

/** \brief  DMA Channel Read Data CRC Register */
typedef struct _Ifx_DMA_CH_RDCRCR_Bits
{
    unsigned int RDCRC:32;                  /**< \brief [31:0] Read Data CRC (rwh) */
} Ifx_DMA_CH_RDCRCR_Bits;

/** \brief  DMA Channel Source Address Register */
typedef struct _Ifx_DMA_CH_SADR_Bits
{
    unsigned int SADR:32;                   /**< \brief [31:0] Source Address (rwh) */
} Ifx_DMA_CH_SADR_Bits;

/** \brief  DMA Channel Source and Destination Address CRC Register */
typedef struct _Ifx_DMA_CH_SDCRCR_Bits
{
    unsigned int SDCRC:32;                  /**< \brief [31:0] Source and Destination Address CRC (rwh) */
} Ifx_DMA_CH_SDCRCR_Bits;

/** \brief  DMA Channel Shadow Address Register */
typedef struct _Ifx_DMA_CH_SHADR_Bits
{
    unsigned int SHADR:32;                  /**< \brief [31:0] Shadowed Address (rwh) */
} Ifx_DMA_CH_SHADR_Bits;

/** \brief  DMA Clock Control Register */
typedef struct _Ifx_DMA_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_DMA_CLC_Bits;

/** \brief  DMA Error Interrupt Set Register */
typedef struct _Ifx_DMA_ERRINTR_Bits
{
    unsigned int SIT:1;                     /**< \brief [0:0] Set Error Interrupt Service Request (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_DMA_ERRINTR_Bits;

/** \brief  DMA Channel Hardware Resource Register */
typedef struct _Ifx_DMA_HRR_Bits
{
    unsigned int HRP:2;                     /**< \brief [1:0] Hardware Resource Partition y (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_DMA_HRR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_DMA_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_DMA_ID_Bits;

/** \brief  DMA Memory Control Register */
typedef struct _Ifx_DMA_MEMCON_Bits
{
    Ifx_Strict_32Bit reserved_0:2;              /**< \brief \internal Reserved */
    Ifx_Strict_32Bit INTERR:1;                  /**< \brief [2:2] Internal ECC Error (rwh) */
    Ifx_Strict_32Bit reserved_3:1;              /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RMWERR:1;                  /**< \brief [4:4] Internal Read Modify Write Error (rwh) */
    Ifx_Strict_32Bit reserved_5:1;              /**< \brief \internal Reserved */
    Ifx_Strict_32Bit DATAERR:1;                 /**< \brief [6:6] SPB Data Phase ECC Error (rwh) */
    Ifx_Strict_32Bit reserved_7:1;              /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PMIC:1;                    /**< \brief [8:8] Protection Bit for Memory Integrity Control Bit (w) */
    Ifx_Strict_32Bit ERRDIS:1;                  /**< \brief [9:9] ECC Error Disable (rw) */
    Ifx_Strict_32Bit reserved_10:22;            /**< \brief \internal Reserved */
} Ifx_DMA_MEMCON_Bits;

/** \brief  DMA Mode Register */
typedef struct _Ifx_DMA_MODE_Bits
{
    unsigned int MODE:1;                    /**< \brief [0:0] Hardware Resource Supervisor Mode (rw) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_DMA_MODE_Bits;

/** \brief  DMA OCDS Trigger Set Select */
typedef struct _Ifx_DMA_OTSS_Bits
{
    unsigned int TGS:4;                     /**< \brief [3:0] Trigger Set () for OTGB0/1 (rw) */
    unsigned int reserved_4:3;              /**< \brief \internal Reserved */
    unsigned int BS:1;                      /**< \brief [7:7] OTGB0/1 Bus Select (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_DMA_OTSS_Bits;

/** \brief  Pattern Read Register 0 */
typedef struct _Ifx_DMA_PRR0_Bits
{
    unsigned int PAT00:8;                   /**< \brief [7:0] Pattern for Move Engine (rw) */
    unsigned int PAT01:8;                   /**< \brief [15:8] Pattern for Move Engine (rw) */
    unsigned int PAT02:8;                   /**< \brief [23:16] Pattern for Move Engine (rw) */
    unsigned int PAT03:8;                   /**< \brief [31:24] Pattern for Move Engine (rw) */
} Ifx_DMA_PRR0_Bits;

/** \brief  Pattern Read Register 1 */
typedef struct _Ifx_DMA_PRR1_Bits
{
    unsigned int PAT10:8;                   /**< \brief [7:0] Pattern for Move Engine (rw) */
    unsigned int PAT11:8;                   /**< \brief [15:8] Pattern for Move Engine (rw) */
    unsigned int PAT12:8;                   /**< \brief [23:16] Pattern for Move Engine (rw) */
    unsigned int PAT13:8;                   /**< \brief [31:24] Pattern for Move Engine (rw) */
} Ifx_DMA_PRR1_Bits;

/** \brief  DMA Suspend Acknowledge Register */
typedef struct _Ifx_DMA_SUSACR_Bits
{
    unsigned int SUSAC:1;                   /**< \brief [0:0] Channel Suspend Mode or Frozen State Active for DMA Channel z (rh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_DMA_SUSACR_Bits;

/** \brief  DMA Suspend Enable Register */
typedef struct _Ifx_DMA_SUSENR_Bits
{
    unsigned int SUSEN:1;                   /**< \brief [0:0] Channel Suspend Enable for DMA Channel z (rw) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_DMA_SUSENR_Bits;

/** \brief  Time Register */
typedef struct _Ifx_DMA_TIME_Bits
{
    unsigned int COUNT:32;                  /**< \brief [31:0] Timestamp Count (r) */
} Ifx_DMA_TIME_Bits;

/** \brief  DMA Transaction State Register */
typedef struct _Ifx_DMA_TSR_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] DMA Channel Reset (rwh) */
    unsigned int HTRE:1;                    /**< \brief [1:1] Hardware Transaction Request Enable State (rh) */
    unsigned int TRL:1;                     /**< \brief [2:2] Transaction/Transfer Request Lost of DMA Channel (rh) */
    unsigned int CH:1;                      /**< \brief [3:3] Transaction Request State (rh) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int HLTREQ:1;                  /**< \brief [8:8] Halt Request (rwh) */
    unsigned int HLTACK:1;                  /**< \brief [9:9] Halt Acknowledge (rh) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int ECH:1;                     /**< \brief [16:16] Enable Hardware Transfer Request (w) */
    unsigned int DCH:1;                     /**< \brief [17:17] Disable Hardware Transfer Request (w) */
    unsigned int CTL:1;                     /**< \brief [18:18] Clear Transaction Request Lost for DMA Channel z (w) */
    unsigned int reserved_19:5;             /**< \brief \internal Reserved */
    unsigned int HLTCLR:1;                  /**< \brief [24:24] Clear Halt Request and Acknowledge (w) */
    unsigned int reserved_25:7;             /**< \brief \internal Reserved */
} Ifx_DMA_TSR_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dma_union
 * \{  */

/** \brief  DMA Hardware Resource 0 Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN00_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN00;

/** \brief  DMA Hardware Resource 0 Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN01_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN01;

/** \brief  DMA Hardware Resource 1 Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN10_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN10;

/** \brief  DMA Hardware Resource 1 Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN11_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN11;

/** \brief  DMA Hardware Resource 2 Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN20_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN20;

/** \brief  DMA Hardware Resource 2 Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN21_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN21;

/** \brief  DMA Hardware Resource 3 Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN30_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN30;

/** \brief  DMA Hardware Resource 3 Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ACCEN31_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ACCEN31;

/** \brief  DMA Clear Error Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_CLRE_Bits B;                /**< \brief Bitfield access */
} Ifx_DMA_BLK_CLRE;

/** \brief  DMA Enable Error Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_EER_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_BLK_EER;

/** \brief  DMA Error Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ERRSR_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ERRSR;

/** \brief  DMA Move Engine Channel Address and Interrupt Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_ADICR_Bits B;            /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_ADICR;

/** \brief  DMA Move Engine Channel Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_CHCR_Bits B;             /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_CHCR;

/** \brief  DMA Move Engine Channel Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_CHSR_Bits B;             /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_CHSR;

/** \brief  DMA Move Engine Channel Destination Address Register x */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_DADR_Bits B;             /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_DADR;

/** \brief  DMA Move Engine Read Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R0_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R0;

/** \brief  DMA Move Engine Read Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R1_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R1;

/** \brief  DMA Move Engine Read Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R2_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R2;

/** \brief  DMA Move Engine Read Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R3_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R3;

/** \brief  DMA Move Engine Read Register 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R4_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R4;

/** \brief  DMA Move Engine Read Register 5 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R5_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R5;

/** \brief  DMA Move Engine Read Register 6 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R6_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R6;

/** \brief  DMA Move Engine Read Register 7 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_R7_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_R7;

/** \brief  DMA Move Engine Channel Read Data CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_RDCRC_Bits B;            /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_RDCRC;

/** \brief  DMA Move Engine Channel Source Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_SADR_Bits B;             /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_SADR;

/** \brief  DMA Move Engine Channel Source and Destination Address CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_SDCRC_Bits B;            /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_SDCRC;

/** \brief  DMA Move Engine Channel Shadow Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_SHADR_Bits B;            /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_SHADR;

/** \brief  DMA Move Engine Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_BLK_ME_SR_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_BLK_ME_SR;

/** \brief  DMA Channel Address and Interrupt Control Register x */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_ADICR_Bits B;                /**< \brief Bitfield access */
} Ifx_DMA_CH_ADICR;

/** \brief  DMA Channel Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_CHCFGR_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_CH_CHCFGR;

/** \brief  DMARAM Channel Control and Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_CHCSR_Bits B;                /**< \brief Bitfield access */
} Ifx_DMA_CH_CHCSR;

/** \brief  DMA Channel Destination Address Register x */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_DADR_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_CH_DADR;

/** \brief  DMA Channel Read Data CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_RDCRCR_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_CH_RDCRCR;

/** \brief  DMA Channel Source Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_SADR_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_CH_SADR;

/** \brief  DMA Channel Source and Destination Address CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_SDCRCR_Bits B;               /**< \brief Bitfield access */
} Ifx_DMA_CH_SDCRCR;

/** \brief  DMA Channel Shadow Address Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CH_SHADR_Bits B;                /**< \brief Bitfield access */
} Ifx_DMA_CH_SHADR;

/** \brief  DMA Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_DMA_CLC;

/** \brief  DMA Error Interrupt Set Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ERRINTR_Bits B;                 /**< \brief Bitfield access */
} Ifx_DMA_ERRINTR;

/** \brief  DMA Channel Hardware Resource Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_HRR_Bits B;                     /**< \brief Bitfield access */
} Ifx_DMA_HRR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_DMA_ID;

/** \brief  DMA Memory Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_MEMCON_Bits B;                  /**< \brief Bitfield access */
} Ifx_DMA_MEMCON;

/** \brief  DMA Mode Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_MODE_Bits B;                    /**< \brief Bitfield access */
} Ifx_DMA_MODE;

/** \brief  DMA OCDS Trigger Set Select */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_OTSS_Bits B;                    /**< \brief Bitfield access */
} Ifx_DMA_OTSS;

/** \brief  Pattern Read Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_PRR0_Bits B;                    /**< \brief Bitfield access */
} Ifx_DMA_PRR0;

/** \brief  Pattern Read Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_PRR1_Bits B;                    /**< \brief Bitfield access */
} Ifx_DMA_PRR1;

/** \brief  DMA Suspend Acknowledge Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_SUSACR_Bits B;                  /**< \brief Bitfield access */
} Ifx_DMA_SUSACR;

/** \brief  DMA Suspend Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_SUSENR_Bits B;                  /**< \brief Bitfield access */
} Ifx_DMA_SUSENR;

/** \brief  Time Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_TIME_Bits B;                    /**< \brief Bitfield access */
} Ifx_DMA_TIME;

/** \brief  DMA Transaction State Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_DMA_TSR_Bits B;                     /**< \brief Bitfield access */
} Ifx_DMA_TSR;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dma_struct
 * \{  */
/******************************************************************************/
/** \name Object L2
 * \{  */

/** \brief  DMA move engine */
typedef volatile struct _Ifx_DMA_BLK_ME
{
    Ifx_DMA_BLK_ME_SR SR;                   /**< \brief 0, DMA Move Engine Status Register */
    unsigned char reserved_4[12];           /**< \brief 4, \internal Reserved */
    Ifx_DMA_BLK_ME_R0 R0;                   /**< \brief 10, DMA Move Engine Read Register 0 */
    Ifx_DMA_BLK_ME_R1 R1;                   /**< \brief 14, DMA Move Engine Read Register 1 */
    Ifx_DMA_BLK_ME_R2 R2;                   /**< \brief 18, DMA Move Engine Read Register 2 */
    Ifx_DMA_BLK_ME_R3 R3;                   /**< \brief 1C, DMA Move Engine Read Register 3 */
    Ifx_DMA_BLK_ME_R4 R4;                   /**< \brief 20, DMA Move Engine Read Register 4 */
    Ifx_DMA_BLK_ME_R5 R5;                   /**< \brief 24, DMA Move Engine Read Register 5 */
    Ifx_DMA_BLK_ME_R6 R6;                   /**< \brief 28, DMA Move Engine Read Register 6 */
    Ifx_DMA_BLK_ME_R7 R7;                   /**< \brief 2C, DMA Move Engine Read Register 7 */
    unsigned char reserved_30[32];          /**< \brief 30, \internal Reserved */
    Ifx_DMA_BLK_ME_RDCRC RDCRC;             /**< \brief 50, DMA Move Engine Channel Read Data CRC Register */
    Ifx_DMA_BLK_ME_SDCRC SDCRC;             /**< \brief 54, DMA Move Engine Channel Source and Destination Address CRC Register */
    Ifx_DMA_BLK_ME_SADR SADR;               /**< \brief 58, DMA Move Engine Channel Source Address Register */
    Ifx_DMA_BLK_ME_DADR DADR;               /**< \brief 5C, DMA Move Engine Channel Destination Address Register x */
    Ifx_DMA_BLK_ME_ADICR ADICR;             /**< \brief 60, DMA Move Engine Channel Address and Interrupt Control Register */
    Ifx_DMA_BLK_ME_CHCR CHCR;               /**< \brief 64, DMA Move Engine Channel Control Register */
    Ifx_DMA_BLK_ME_SHADR SHADR;             /**< \brief 68, DMA Move Engine Channel Shadow Address Register */
    Ifx_DMA_BLK_ME_CHSR CHSR;               /**< \brief 6C, DMA Move Engine Channel Status Register */
} Ifx_DMA_BLK_ME;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dma_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  DMA sub block */
typedef volatile struct _Ifx_DMA_BLK
{
    Ifx_DMA_BLK_EER EER;                    /**< \brief 0, DMA Enable Error Register */
    Ifx_DMA_BLK_ERRSR ERRSR;                /**< \brief 4, DMA Error Status Register */
    Ifx_DMA_BLK_CLRE CLRE;                  /**< \brief 8, DMA Clear Error Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_DMA_BLK_ME ME;                      /**< \brief 10, DMA move engine */
} Ifx_DMA_BLK;

/** \brief  DMA channels */
typedef volatile struct _Ifx_DMA_CH
{
    Ifx_DMA_CH_RDCRCR RDCRCR;               /**< \brief 0, DMA Channel Read Data CRC Register */
    Ifx_DMA_CH_SDCRCR SDCRCR;               /**< \brief 4, DMA Channel Source and Destination Address CRC Register */
    Ifx_DMA_CH_SADR SADR;                   /**< \brief 8, DMA Channel Source Address Register */
    Ifx_DMA_CH_DADR DADR;                   /**< \brief C, DMA Channel Destination Address Register x */
    Ifx_DMA_CH_ADICR ADICR;                 /**< \brief 10, DMA Channel Address and Interrupt Control Register x */
    Ifx_DMA_CH_CHCFGR CHCFGR;               /**< \brief 14, DMA Channel Configuration Register */
    Ifx_DMA_CH_SHADR SHADR;                 /**< \brief 18, DMA Channel Shadow Address Register */
    Ifx_DMA_CH_CHCSR CHCSR;                 /**< \brief 1C, DMARAM Channel Control and Status Register */
} Ifx_DMA_CH;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dma_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  DMA object */
typedef volatile struct _Ifx_DMA
{
    Ifx_DMA_CLC CLC;                        /**< \brief 0, DMA Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_DMA_ID ID;                          /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[20];           /**< \brief C, \internal Reserved */
    Ifx_DMA_MEMCON MEMCON;                  /**< \brief 20, DMA Memory Control Register */
    unsigned char reserved_24[28];          /**< \brief 24, \internal Reserved */
    Ifx_DMA_ACCEN00 ACCEN00;                /**< \brief 40, DMA Hardware Resource 0 Access Enable Register 0 */
    Ifx_DMA_ACCEN01 ACCEN01;                /**< \brief 44, DMA Hardware Resource 0 Access Enable Register 1 */
    Ifx_DMA_ACCEN10 ACCEN10;                /**< \brief 48, DMA Hardware Resource 1 Access Enable Register 0 */
    Ifx_DMA_ACCEN11 ACCEN11;                /**< \brief 4C, DMA Hardware Resource 1 Access Enable Register 1 */
    Ifx_DMA_ACCEN20 ACCEN20;                /**< \brief 50, DMA Hardware Resource 2 Access Enable Register 0 */
    Ifx_DMA_ACCEN21 ACCEN21;                /**< \brief 54, DMA Hardware Resource 2 Access Enable Register 1 */
    Ifx_DMA_ACCEN30 ACCEN30;                /**< \brief 58, DMA Hardware Resource 3 Access Enable Register 0 */
    Ifx_DMA_ACCEN31 ACCEN31;                /**< \brief 5C, DMA Hardware Resource 3 Access Enable Register 1 */
    unsigned char reserved_60[192];         /**< \brief 60, \internal Reserved */
    Ifx_DMA_BLK BLK0;                       /**< \brief 120, DMA sub block 0 */
    unsigned char reserved_1A0[3968];       /**< \brief 1A0, \internal Reserved */
    Ifx_DMA_BLK BLK1;                       /**< \brief 1120, DMA sub block 1 */
    unsigned char reserved_11A0[96];        /**< \brief 11A0, \internal Reserved */
    Ifx_DMA_OTSS OTSS;                      /**< \brief 1200, DMA OCDS Trigger Set Select */
    Ifx_DMA_ERRINTR ERRINTR;                /**< \brief 1204, DMA Error Interrupt Set Register */
    Ifx_DMA_PRR0 PRR0;                      /**< \brief 1208, Pattern Read Register 0 */
    Ifx_DMA_PRR1 PRR1;                      /**< \brief 120C, Pattern Read Register 1 */
    Ifx_DMA_TIME TIME;                      /**< \brief 1210, Time Register */
    unsigned char reserved_1214[236];       /**< \brief 1214, \internal Reserved */
    Ifx_DMA_MODE MODE[4];                   /**< \brief 1300, DMA Mode Register */
    unsigned char reserved_1310[1264];      /**< \brief 1310, \internal Reserved */
    Ifx_DMA_HRR HRR[48];                    /**< \brief 1800, DMA Channel Hardware Resource Register */
    unsigned char reserved_18C0[320];       /**< \brief 18C0, \internal Reserved */
    Ifx_DMA_SUSENR SUSENR[48];              /**< \brief 1A00, DMA Suspend Enable Register */
    unsigned char reserved_1AC0[320];       /**< \brief 1AC0, \internal Reserved */
    Ifx_DMA_SUSACR SUSACR[48];              /**< \brief 1C00, DMA Suspend Acknowledge Register */
    unsigned char reserved_1CC0[320];       /**< \brief 1CC0, \internal Reserved */
    Ifx_DMA_TSR TSR[48];                    /**< \brief 1E00, DMA Transaction State Register */
    unsigned char reserved_1EC0[320];       /**< \brief 1EC0, \internal Reserved */
    Ifx_DMA_CH CH[48];                      /**< \brief 2000, DMA channels */
    unsigned char reserved_2600[6656];      /**< \brief 2600, \internal Reserved */
} Ifx_DMA;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXDMA_REGDEF_H */
