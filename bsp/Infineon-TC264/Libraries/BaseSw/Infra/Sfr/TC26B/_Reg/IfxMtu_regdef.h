/**
 * \file IfxMtu_regdef.h
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
 * \defgroup IfxLld_Mtu Mtu
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Mtu_Bitfields Bitfields
 * \ingroup IfxLld_Mtu
 * 
 * \defgroup IfxLld_Mtu_union Union
 * \ingroup IfxLld_Mtu
 * 
 * \defgroup IfxLld_Mtu_struct Struct
 * \ingroup IfxLld_Mtu
 * 
 */
#ifndef IFXMTU_REGDEF_H
#define IFXMTU_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Mtu_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_MTU_ACCEN0_Bits
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
} Ifx_MTU_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_MTU_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_MTU_ACCEN1_Bits;

/** \brief  Identification Register */
typedef struct _Ifx_MTU_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int Resvd:1;                   /**< \brief [2:2] Resvd (rw) */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_MTU_CLC_Bits;

/** \brief  Identification Register */
typedef struct _Ifx_MTU_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_MTU_ID_Bits;

/** \brief  Memory Mapping Enable Register */
typedef struct _Ifx_MTU_MEMMAP_Bits
{
    unsigned int reserved_0:1;              /**< \brief \internal Reserved */
    unsigned int CPU2DxMAP:2;               /**< \brief [2:1] Reserved in this product (r) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int CPU2PxMAP:2;               /**< \brief [5:4] Reserved in this product (r) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int CPU1DCMAP:1;               /**< \brief [7:7] CPU1 DCACHE Mapping (rwh) */
    unsigned int CPU1DTMAP:1;               /**< \brief [8:8] CPU1 DTAG Mapping (rh) */
    unsigned int reserved_9:1;              /**< \brief \internal Reserved */
    unsigned int CPU1PCMAP:1;               /**< \brief [10:10] CPU1 PCACHE Mapping (rwh) */
    unsigned int CPU1PTMAP:1;               /**< \brief [11:11] CPU1 PTAG Mapping (rh) */
    unsigned int reserved_12:3;             /**< \brief \internal Reserved */
    unsigned int CPU0PCMAP:1;               /**< \brief [15:15] CPU0 PCACHE Mapping (rwh) */
    unsigned int reserved_16:1;             /**< \brief \internal Reserved */
    unsigned int CPU0PTMAP:1;               /**< \brief [17:17] CPU0 PTAG Mapping (rh) */
    unsigned int CPU0DxMAP:2;               /**< \brief [19:18] Reserved in this product (r) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_MTU_MEMMAP_Bits;

/** \brief  Memory Status Register 0 */
typedef struct _Ifx_MTU_MEMSTAT0_Bits
{
    unsigned int CPU2DSAIU:1;               /**< \brief [0:0] Reserved in this product (r) */
    unsigned int reserved_1:1;              /**< \brief \internal Reserved */
    unsigned int CPU2DTAIU:1;               /**< \brief [2:2] Reserved in this product (r) */
    unsigned int CPU2PSAIU:1;               /**< \brief [3:3] Reserved in this product (r) */
    unsigned int reserved_4:1;              /**< \brief \internal Reserved */
    unsigned int CPU2PTAIU:1;               /**< \brief [5:5] Reserved in this product (r) */
    unsigned int CPU1DSAIU:1;               /**< \brief [6:6] CPU1 DCACHE Partial AutoInitialize Underway (rh) */
    unsigned int reserved_7:1;              /**< \brief \internal Reserved */
    unsigned int CPU1DTAIU:1;               /**< \brief [8:8] CPU1 DTAG MBIST AutoInitialize Underway (rh) */
    unsigned int CPU1PSAIU:1;               /**< \brief [9:9] CPU1 PCACHE Partial AutoInitialize Underway (rh) */
    unsigned int reserved_10:1;             /**< \brief \internal Reserved */
    unsigned int CPU1PTAIU:1;               /**< \brief [11:11] CPU1 PTAG MBIST AutoInitialize Underway (rh) */
    unsigned int reserved_12:2;             /**< \brief \internal Reserved */
    unsigned int CPU0DSAIU:1;               /**< \brief [14:14] Reserved in this product (r) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int CPU0PSAIU:1;               /**< \brief [16:16] CPU0 PCACHE Partial AutoInitialize Underway (rh) */
    unsigned int CPU0PTAIU:1;               /**< \brief [17:17] CPU0 PTAG MBIST AutoInitialize Underway (rh) */
    unsigned int reserved_18:1;             /**< \brief \internal Reserved */
    unsigned int CPU0DxAIU:1;               /**< \brief [19:19] Reserved in this product (r) */
    unsigned int CPU1DS2AIU:1;              /**< \brief [20:20] Reserved in this product (r) */
    unsigned int CPU2DS2AIU:1;              /**< \brief [21:21] Reserved in this product (r) */
    unsigned int reserved_22:1;             /**< \brief \internal Reserved */
    unsigned int HSMCAIU:1;                 /**< \brief [23:23] Reserved in this product (r) */
    unsigned int HSMTAIU:1;                 /**< \brief [24:24] Reserved in this product (r) */
    unsigned int HSMRAIU:1;                 /**< \brief [25:25] Reserved in this product (r) */
    unsigned int FSI0AIU:1;                 /**< \brief [26:26] FSI0 MBIST AutoInitialize Underway (rh) */
    unsigned int CPU0DS2AIU:1;              /**< \brief [27:27] Reserved in this product (r) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_MTU_MEMSTAT0_Bits;

/** \brief  Memory Status Register 1 */
typedef struct _Ifx_MTU_MEMSTAT1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_MTU_MEMSTAT1_Bits;

/** \brief  Memory Status Register 2 */
typedef struct _Ifx_MTU_MEMSTAT2_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_MTU_MEMSTAT2_Bits;

/** \brief  Memory MBISTEnable Register 0 */
typedef struct _Ifx_MTU_MEMTEST0_Bits
{
    unsigned int CPU2XEN:6;                 /**< \brief [5:0] Reserved in this product (r) */
    unsigned int CPU1DSEN:1;                /**< \brief [6:6] CPU1 TC1.6P DSPR MBIST Controller Memory Enable (rwh) */
    unsigned int Res:1;                     /**< \brief [7:7] Reserved in this product (r) */
    unsigned int CPU1DTEN:1;                /**< \brief [8:8] CPU1 TC1.6P DTAG MBIST Controller Memory Enable (rwh) */
    unsigned int CPU1PSEN:1;                /**< \brief [9:9] CPU1 TC1.6P PSPR MBIST Controller Memory Enable (rwh) */
    unsigned int reserved_10:1;             /**< \brief \internal Reserved */
    unsigned int CPU1PTEN:1;                /**< \brief [11:11] CPU1 TC1.6P PTAG MBIST Controller Memory Enable (rwh) */
    unsigned int LMUEN:1;                   /**< \brief [12:12] Reserved in this product (r) */
    unsigned int MMCDSEN:1;                 /**< \brief [13:13] Reserved in this product (r) */
    unsigned int CPU0DSEN:1;                /**< \brief [14:14] CPU0 DSPR MBIST Controller Memory Enable (rwh) */
    unsigned int reserved_15:1;             /**< \brief \internal Reserved */
    unsigned int CPU0PSEN:1;                /**< \brief [16:16] CPU0 PSPR MBIST Controller Memory Enable (rwh) */
    unsigned int CPU0PTEN:1;                /**< \brief [17:17] CPU0 PTAG MBIST Controller Memory Enable (rwh) */
    unsigned int reserved_18:1;             /**< \brief \internal Reserved */
    unsigned int CPU0DTEN:1;                /**< \brief [19:19] Reserved in this product (r) */
    unsigned int CPUXDS2EN:2;               /**< \brief [21:20] Reserved in this product (r) */
    unsigned int ETHEN:1;                   /**< \brief [22:22] ETHERMAC MBIST Controller Memory Enable (rwh) */
    unsigned int reserved_23:3;             /**< \brief \internal Reserved */
    unsigned int FSI0EN:1;                  /**< \brief [26:26] FSI0 MBIST Controller Memory Enable (rwh) */
    unsigned int CPU0DS2EN:1;               /**< \brief [27:27] Reserved in this product (r) */
    unsigned int GTMFEN:1;                  /**< \brief [28:28] GTM FIFO0 MBIST Controller Memory Enable (rwh) */
    unsigned int GTMM0EN:1;                 /**< \brief [29:29] GTM MCS0 MBIST Controller Memory Enable (rwh) */
    unsigned int GTMM1EN:1;                 /**< \brief [30:30] GTM RAM1 MBIST Controller Memory Enable (rwh) */
    unsigned int GTM1AEN:1;                 /**< \brief [31:31] GTM RAM1A MBIST Controller Memory Enable (rwh) */
} Ifx_MTU_MEMTEST0_Bits;

/** \brief  Memory MBISTEnable Register 1 */
typedef struct _Ifx_MTU_MEMTEST1_Bits
{
    unsigned int GTM1BEN:1;                 /**< \brief [0:0] GTM RAM1B Controller Memory Enable (rwh) */
    unsigned int GTM2EN:1;                  /**< \brief [1:1] GTM RAM2 Controller Memory Enable (rwh) */
    unsigned int PSI5EN:1;                  /**< \brief [2:2] PSI5 Controller Memory Enable (rwh) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int MCAN0EN:1;                 /**< \brief [4:4] MultiCAN0 Controller Memory Enable (rwh) */
    unsigned int MCAN1EN:1;                 /**< \brief [5:5] Reserved in this product (r) */
    unsigned int ERAY0OEN:1;                /**< \brief [6:6] ERAY0 OBF Controller Memory Enable (rwh) */
    unsigned int ERAY0TEN:1;                /**< \brief [7:7] ERAY0 TBF Controller Memory Enable (rwh) */
    unsigned int ERAY0MEN:1;                /**< \brief [8:8] ERAY0 MBF Controller Memory Enable (rwh) */
    unsigned int ERAY1XEN:3;                /**< \brief [11:9] Reserved in this product (r) */
    unsigned int STBY1EN:1;                 /**< \brief [12:12] 8 Bit Standby RAM Controller Memory 1 Enable (rwh) */
    unsigned int MCDSEN:1;                  /**< \brief [13:13] MCDS Controller Memory Enable (ED only) (rwh) */
    unsigned int EMEML0EN:1;                /**< \brief [14:14] EMEM Lower 0 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEML1EN:1;                /**< \brief [15:15] EMEM Lower 1 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEML2EN:1;                /**< \brief [16:16] EMEM Lower 2 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEML3EN:1;                /**< \brief [17:17] EMEM Lower 3 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEML4EN:1;                /**< \brief [18:18] EMEM Lower 4 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEML5EN:1;                /**< \brief [19:19] EMEM Lower 5 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEML6EN:1;                /**< \brief [20:20] EMEM Lower 6 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEML7EN:1;                /**< \brief [21:21] EMEM Lower 7 (TCM) MBIST Controller Memory Test Enable (ED only) (rwh) */
    unsigned int EMEMLXEN:8;                /**< \brief [29:22] Reserved in this product (r) */
    unsigned int EMEMUXEN:2;                /**< \brief [31:30] Reserved in this product (r) */
} Ifx_MTU_MEMTEST1_Bits;

/** \brief  Memory MBISTEnable Register 2 */
typedef struct _Ifx_MTU_MEMTEST2_Bits
{
    unsigned int EMEMUxEN:14;               /**< \brief [13:0] Reserved in this product (r) */
    unsigned int CIF0EN:1;                  /**< \brief [14:14] CIF JPEG1_4 Memory Enable (ED only) (rwh) */
    unsigned int DAMEN:1;                   /**< \brief [15:15] Reserved in this product (r) */
    unsigned int CIF1EN:1;                  /**< \brief [16:16] CIF JPEG3 Memory Enable (ADAS Product only) (rwh) */
    unsigned int CIF2EN:1;                  /**< \brief [17:17] CIF Memory2 Enable (ADAS Product only) (rwh) */
    unsigned int STBY2EN:1;                 /**< \brief [18:18] 8-bit Standby Controller Memory2 Enable (rwh) */
    unsigned int DMAEN:1;                   /**< \brief [19:19] DMA MBIST Controller Memory Enable (rwh) */
    unsigned int XTM0EN:1;                  /**< \brief [20:20] EMEM XTM0 Controller Memory Enable (ED only) (rwh) */
    unsigned int XTM1EN:1;                  /**< \brief [21:21] EMEM XTM1 Controller Memory Enable (ED only) (rwh) */
    unsigned int FFT0EN:1;                  /**< \brief [22:22] FFT0 Memory Controller Memory Enable (ADAS Product only) (rwh) */
    unsigned int FFT1EN:1;                  /**< \brief [23:23] FFT1 Memory Controller Memory Enable (ADAS Product only) (rwh) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_MTU_MEMTEST2_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Mtu_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_MTU_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_MTU_ACCEN1;

/** \brief  Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_MTU_CLC;

/** \brief  Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_MTU_ID;

/** \brief  Memory Mapping Enable Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_MEMMAP_Bits B;                  /**< \brief Bitfield access */
} Ifx_MTU_MEMMAP;

/** \brief  Memory Status Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_MEMSTAT0_Bits B;                /**< \brief Bitfield access */
} Ifx_MTU_MEMSTAT0;

/** \brief  Memory Status Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_MEMSTAT1_Bits B;                /**< \brief Bitfield access */
} Ifx_MTU_MEMSTAT1;

/** \brief  Memory Status Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_MEMSTAT2_Bits B;                /**< \brief Bitfield access */
} Ifx_MTU_MEMSTAT2;

/** \brief  Memory MBISTEnable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_MEMTEST0_Bits B;                /**< \brief Bitfield access */
} Ifx_MTU_MEMTEST0;

/** \brief  Memory MBISTEnable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_MEMTEST1_Bits B;                /**< \brief Bitfield access */
} Ifx_MTU_MEMTEST1;

/** \brief  Memory MBISTEnable Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_MTU_MEMTEST2_Bits B;                /**< \brief Bitfield access */
} Ifx_MTU_MEMTEST2;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Mtu_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  MTU object */
typedef volatile struct _Ifx_MTU
{
    Ifx_MTU_CLC CLC;                        /**< \brief 0, Identification Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_MTU_ID ID;                          /**< \brief 8, Identification Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_MTU_MEMTEST0 MEMTEST0;              /**< \brief 10, Memory MBISTEnable Register 0 */
    Ifx_MTU_MEMTEST1 MEMTEST1;              /**< \brief 14, Memory MBISTEnable Register 1 */
    Ifx_MTU_MEMTEST2 MEMTEST2;              /**< \brief 18, Memory MBISTEnable Register 2 */
    Ifx_MTU_MEMMAP MEMMAP;                  /**< \brief 1C, Memory Mapping Enable Register */
    unsigned char reserved_20[24];          /**< \brief 20, \internal Reserved */
    Ifx_MTU_MEMSTAT0 MEMSTAT0;              /**< \brief 38, Memory Status Register 0 */
    Ifx_MTU_MEMSTAT1 MEMSTAT1;              /**< \brief 3C, Memory Status Register 1 */
    Ifx_MTU_MEMSTAT2 MEMSTAT2;              /**< \brief 40, Memory Status Register 2 */
    unsigned char reserved_44[180];         /**< \brief 44, \internal Reserved */
    Ifx_MTU_ACCEN1 ACCEN1;                  /**< \brief F8, Access Enable Register 1 */
    Ifx_MTU_ACCEN0 ACCEN0;                  /**< \brief FC, Access Enable Register 0 */
    unsigned char reserved_100[1];          /**< \brief 100, \internal Reserved */
} Ifx_MTU;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXMTU_REGDEF_H */
