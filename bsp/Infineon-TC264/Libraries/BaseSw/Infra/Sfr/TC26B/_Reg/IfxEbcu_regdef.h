/**
 * \file IfxEbcu_regdef.h
 * \brief
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC2XXED_TS_V1.0.R2
 * Specification: AurixED_TS_V1.0_CPU_VIEW_SFR.xml (Revision: V1.0)
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
 * \defgroup IfxLld_Ebcu Ebcu
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Ebcu_Bitfields Bitfields
 * \ingroup IfxLld_Ebcu
 * 
 * \defgroup IfxLld_Ebcu_union Union
 * \ingroup IfxLld_Ebcu
 * 
 * \defgroup IfxLld_Ebcu_struct Struct
 * \ingroup IfxLld_Ebcu
 * 
 */
#ifndef IFXEBCU_REGDEF_H
#define IFXEBCU_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Ebcu_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_EBCU_ACCEN0_Bits
{
    Ifx_Strict_32Bit EN0:1;                 /**< \brief [0:0] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN1:1;                 /**< \brief [1:1] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN2:1;                 /**< \brief [2:2] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN3:1;                 /**< \brief [3:3] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN4:1;                 /**< \brief [4:4] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN5:1;                 /**< \brief [5:5] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN6:1;                 /**< \brief [6:6] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN7:1;                 /**< \brief [7:7] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN8:1;                 /**< \brief [8:8] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN9:1;                 /**< \brief [9:9] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN10:1;                /**< \brief [10:10] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN11:1;                /**< \brief [11:11] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN12:1;                /**< \brief [12:12] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN13:1;                /**< \brief [13:13] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN14:1;                /**< \brief [14:14] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN15:1;                /**< \brief [15:15] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN16:1;                /**< \brief [16:16] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN17:1;                /**< \brief [17:17] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN18:1;                /**< \brief [18:18] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN19:1;                /**< \brief [19:19] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN20:1;                /**< \brief [20:20] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN21:1;                /**< \brief [21:21] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN22:1;                /**< \brief [22:22] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN23:1;                /**< \brief [23:23] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN24:1;                /**< \brief [24:24] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN25:1;                /**< \brief [25:25] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN26:1;                /**< \brief [26:26] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN27:1;                /**< \brief [27:27] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN28:1;                /**< \brief [28:28] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN29:1;                /**< \brief [29:29] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN30:1;                /**< \brief [30:30] Access Enable for Master TAG ID x (rw) */
    Ifx_Strict_32Bit EN31:1;                /**< \brief [31:31] Access Enable for Master TAG ID x (rw) */
} Ifx_EBCU_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_EBCU_ACCEN1_Bits
{
    Ifx_Strict_32Bit reserved_0:32;         /**< \brief \internal Reserved */
} Ifx_EBCU_ACCEN1_Bits;

/** \brief  EBCU Control Register */
typedef struct _Ifx_EBCU_CON_Bits
{
    Ifx_Strict_32Bit TOUT:16;               /**< \brief [15:0] Bus Time-Out Value (rw) */
    Ifx_Strict_32Bit DBG:1;                 /**< \brief [16:16] Debug Trace Enable (rw) */
    Ifx_Strict_32Bit reserved_17:7;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SPC:8;                 /**< \brief [31:24] Starvation Period Control (rw) */
} Ifx_EBCU_CON_Bits;

/** \brief  Error Address Capture Register */
typedef struct _Ifx_EBCU_EADD_Bits
{
    Ifx_Strict_32Bit FPIADR:32;             /**< \brief [31:0] Captured FPI Bus Address (rwh) */
} Ifx_EBCU_EADD_Bits;

/** \brief  Error Control Capture Register */
typedef struct _Ifx_EBCU_ECON_Bits
{
    Ifx_Strict_32Bit ERRCNT:14;             /**< \brief [13:0] FPI Bus Error Counter (rwh) */
    Ifx_Strict_32Bit TOUT:1;                /**< \brief [14:14] State of FPI Bus Time-Out Signal (rwh) */
    Ifx_Strict_32Bit RDY:1;                 /**< \brief [15:15] State of FPI Bus Ready Signal (rwh) */
    Ifx_Strict_32Bit ABT:1;                 /**< \brief [16:16] State of FPI Bus Abort Signal (rwh) */
    Ifx_Strict_32Bit ACK:2;                 /**< \brief [18:17] State of FPI Bus Acknowledge Signals (rwh) */
    Ifx_Strict_32Bit SVM:1;                 /**< \brief [19:19] State of FPI Bus Supervisor Mode Signal (rwh) */
    Ifx_Strict_32Bit WRN:1;                 /**< \brief [20:20] State of FPI Bus Write Signal (rwh) */
    Ifx_Strict_32Bit RDN:1;                 /**< \brief [21:21] State of FPI Bus Read Signal (rwh) */
    Ifx_Strict_32Bit TAG:6;                 /**< \brief [27:22] FPI Bus Master Tag Number Signals (rwh) */
    Ifx_Strict_32Bit OPC:4;                 /**< \brief [31:28] FPI Bus Operation Code Signals (rwh) */
} Ifx_EBCU_ECON_Bits;

/** \brief  Error Data Capture Register */
typedef struct _Ifx_EBCU_EDAT_Bits
{
    Ifx_Strict_32Bit FPIDAT:32;             /**< \brief [31:0] Captured FPI Bus Address (rwh) */
} Ifx_EBCU_EDAT_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_EBCU_ID_Bits
{
    Ifx_Strict_32Bit MOD_REV:8;             /**< \brief [7:0] Module Revision Number (r) */
    Ifx_Strict_32Bit MODNUMBER:8;           /**< \brief [15:8] Module Number Value (r) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_EBCU_ID_Bits;

/** \brief  Arbiter Priority Register */
typedef struct _Ifx_EBCU_PRIOH_Bits
{
    Ifx_Strict_32Bit MASTER8:4;             /**< \brief [3:0] Master 8 Priority (rw) */
    Ifx_Strict_32Bit MASTER9:4;             /**< \brief [7:4] Master 9 Priority (rw) */
    Ifx_Strict_32Bit MASTER10:4;            /**< \brief [11:8] Master 10 Priority (rw) */
    Ifx_Strict_32Bit MASTER11:4;            /**< \brief [15:12] Master 11 Priority (rw) */
    Ifx_Strict_32Bit MASTER12:4;            /**< \brief [19:16] Master 12 Priority (rw) */
    Ifx_Strict_32Bit MASTER13:4;            /**< \brief [23:20] Master 13 Priority (rw) */
    Ifx_Strict_32Bit MASTER14:4;            /**< \brief [27:24] Master 14 Priority (rw) */
    Ifx_Strict_32Bit MASTER15:4;            /**< \brief [31:28] Master 15 Priority (rw) */
} Ifx_EBCU_PRIOH_Bits;

/** \brief  Arbiter Priority Register */
typedef struct _Ifx_EBCU_PRIOL_Bits
{
    Ifx_Strict_32Bit MASTER0:4;             /**< \brief [3:0] Master 0 Priority (rw) */
    Ifx_Strict_32Bit MASTER1:4;             /**< \brief [7:4] Master 1 Priority (rw) */
    Ifx_Strict_32Bit MASTER2:4;             /**< \brief [11:8] Master 2 Priority (rw) */
    Ifx_Strict_32Bit MASTER3:4;             /**< \brief [15:12] Master 3 Priority (rw) */
    Ifx_Strict_32Bit MASTER4:4;             /**< \brief [19:16] Master 4 Priority (rw) */
    Ifx_Strict_32Bit MASTER5:4;             /**< \brief [23:20] Master 5 Priority (rw) */
    Ifx_Strict_32Bit MASTER6:4;             /**< \brief [27:24] Master 6 Priority (rw) */
    Ifx_Strict_32Bit MASTER7:4;             /**< \brief [31:28] Master 7 Priority (rw) */
} Ifx_EBCU_PRIOL_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Ebcu_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_ACCEN0_Bits B;                 /**< \brief Bitfield access */
} Ifx_EBCU_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_ACCEN1_Bits B;                 /**< \brief Bitfield access */
} Ifx_EBCU_ACCEN1;

/** \brief  EBCU Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_CON_Bits B;                    /**< \brief Bitfield access */
} Ifx_EBCU_CON;

/** \brief  Error Address Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_EADD_Bits B;                   /**< \brief Bitfield access */
} Ifx_EBCU_EADD;

/** \brief  Error Control Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_ECON_Bits B;                   /**< \brief Bitfield access */
} Ifx_EBCU_ECON;

/** \brief  Error Data Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_EDAT_Bits B;                   /**< \brief Bitfield access */
} Ifx_EBCU_EDAT;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_ID_Bits B;                     /**< \brief Bitfield access */
} Ifx_EBCU_ID;

/** \brief  Arbiter Priority Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_PRIOH_Bits B;                  /**< \brief Bitfield access */
} Ifx_EBCU_PRIOH;

/** \brief  Arbiter Priority Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_EBCU_PRIOL_Bits B;                  /**< \brief Bitfield access */
} Ifx_EBCU_PRIOL;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Ebcu_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  EBCU object */
typedef volatile struct _Ifx_EBCU
{
    unsigned char reserved_0[8];            /**< \brief 0, \internal Reserved */
    Ifx_EBCU_ID ID;                         /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_EBCU_CON CON;                       /**< \brief 10, EBCU Control Register */
    Ifx_EBCU_PRIOH PRIOH;                   /**< \brief 14, Arbiter Priority Register */
    Ifx_EBCU_PRIOL PRIOL;                   /**< \brief 18, Arbiter Priority Register */
    unsigned char reserved_1C[4];           /**< \brief 1C, \internal Reserved */
    Ifx_EBCU_ECON ECON;                     /**< \brief 20, Error Control Capture Register */
    Ifx_EBCU_EADD EADD;                     /**< \brief 24, Error Address Capture Register */
    Ifx_EBCU_EDAT EDAT;                     /**< \brief 28, Error Data Capture Register */
    unsigned char reserved_2C[204];         /**< \brief 2C, \internal Reserved */
    Ifx_EBCU_ACCEN1 ACCEN1;                 /**< \brief F8, Access Enable Register 1 */
    Ifx_EBCU_ACCEN0 ACCEN0;                 /**< \brief FC, Access Enable Register 0 */
} Ifx_EBCU;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXEBCU_REGDEF_H */
