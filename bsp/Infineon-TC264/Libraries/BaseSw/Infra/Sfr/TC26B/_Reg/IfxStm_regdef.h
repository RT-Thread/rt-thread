/**
 * \file IfxStm_regdef.h
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
 * \defgroup IfxLld_Stm Stm
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Stm_Bitfields Bitfields
 * \ingroup IfxLld_Stm
 * 
 * \defgroup IfxLld_Stm_union Union
 * \ingroup IfxLld_Stm
 * 
 * \defgroup IfxLld_Stm_struct Struct
 * \ingroup IfxLld_Stm
 * 
 */
#ifndef IFXSTM_REGDEF_H
#define IFXSTM_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Stm_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_STM_ACCEN0_Bits
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
} Ifx_STM_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_STM_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_STM_ACCEN1_Bits;

/** \brief  Timer Capture Register */
typedef struct _Ifx_STM_CAP_Bits
{
    unsigned int STMCAP63_32:32;            /**< \brief [31:0] Captured System Timer Bits [63:32] (rh) */
} Ifx_STM_CAP_Bits;

/** \brief  Timer Capture Register Second View */
typedef struct _Ifx_STM_CAPSV_Bits
{
    unsigned int STMCAP63_32:32;            /**< \brief [31:0] Captured System Timer Bits [63:32] (rh) */
} Ifx_STM_CAPSV_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_STM_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (r) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_STM_CLC_Bits;

/** \brief  Compare Match Control Register */
typedef struct _Ifx_STM_CMCON_Bits
{
    unsigned int MSIZE0:5;                  /**< \brief [4:0] Compare Register Size for CMP0 (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int MSTART0:5;                 /**< \brief [12:8] Start Bit Location for CMP0 (rw) */
    unsigned int reserved_13:3;             /**< \brief \internal Reserved */
    unsigned int MSIZE1:5;                  /**< \brief [20:16] Compare Register Size for CMP1 (rw) */
    unsigned int reserved_21:3;             /**< \brief \internal Reserved */
    unsigned int MSTART1:5;                 /**< \brief [28:24] Start Bit Location for CMP1 (rw) */
    unsigned int reserved_29:3;             /**< \brief \internal Reserved */
} Ifx_STM_CMCON_Bits;

/** \brief  Compare Register */
typedef struct _Ifx_STM_CMP_Bits
{
    unsigned int CMPVAL:32;                 /**< \brief [31:0] Compare Value of Compare Register x (rw) */
} Ifx_STM_CMP_Bits;

/** \brief  Interrupt Control Register */
typedef struct _Ifx_STM_ICR_Bits
{
    unsigned int CMP0EN:1;                  /**< \brief [0:0] Compare Register CMP0 Interrupt Enable Control (rw) */
    unsigned int CMP0IR:1;                  /**< \brief [1:1] Compare Register CMP0 Interrupt Request Flag (rh) */
    unsigned int CMP0OS:1;                  /**< \brief [2:2] Compare Register CMP0 Interrupt Output Selection (rw) */
    unsigned int reserved_3:1;              /**< \brief \internal Reserved */
    unsigned int CMP1EN:1;                  /**< \brief [4:4] Compare Register CMP1 Interrupt Enable Control (rw) */
    unsigned int CMP1IR:1;                  /**< \brief [5:5] Compare Register CMP1 Interrupt Request Flag (rh) */
    unsigned int CMP1OS:1;                  /**< \brief [6:6] Compare Register CMP1 Interrupt Output Selection (rw) */
    unsigned int reserved_7:25;             /**< \brief \internal Reserved */
} Ifx_STM_ICR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_STM_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_STM_ID_Bits;

/** \brief  Interrupt Set/Clear Register */
typedef struct _Ifx_STM_ISCR_Bits
{
    unsigned int CMP0IRR:1;                 /**< \brief [0:0] Reset Compare Register CMP0 Interrupt Flag (w) */
    unsigned int CMP0IRS:1;                 /**< \brief [1:1] Set Compare Register CMP0 Interrupt Flag (w) */
    unsigned int CMP1IRR:1;                 /**< \brief [2:2] Reset Compare Register CMP1 Interrupt Flag (w) */
    unsigned int CMP1IRS:1;                 /**< \brief [3:3] Set Compare Register CMP1 Interrupt Flag (w) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_STM_ISCR_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_STM_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_STM_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_STM_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_STM_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_STM_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_STM_KRSTCLR_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_STM_OCS_Bits
{
    unsigned int reserved_0:24;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_STM_OCS_Bits;

/** \brief  Timer Register 0 */
typedef struct _Ifx_STM_TIM0_Bits
{
    unsigned int STM31_0:32;                /**< \brief [31:0] System Timer Bits [31:0] (r) */
} Ifx_STM_TIM0_Bits;

/** \brief  Timer Register 0 Second View */
typedef struct _Ifx_STM_TIM0SV_Bits
{
    unsigned int STM31_0:32;                /**< \brief [31:0] System Timer Bits [31:0] (r) */
} Ifx_STM_TIM0SV_Bits;

/** \brief  Timer Register 1 */
typedef struct _Ifx_STM_TIM1_Bits
{
    unsigned int STM35_4:32;                /**< \brief [31:0] System Timer Bits [35:4] (r) */
} Ifx_STM_TIM1_Bits;

/** \brief  Timer Register 2 */
typedef struct _Ifx_STM_TIM2_Bits
{
    unsigned int STM39_8:32;                /**< \brief [31:0] System Timer Bits [39:8] (r) */
} Ifx_STM_TIM2_Bits;

/** \brief  Timer Register 3 */
typedef struct _Ifx_STM_TIM3_Bits
{
    unsigned int STM43_12:32;               /**< \brief [31:0] System Timer Bits [43:12] (r) */
} Ifx_STM_TIM3_Bits;

/** \brief  Timer Register 4 */
typedef struct _Ifx_STM_TIM4_Bits
{
    unsigned int STM47_16:32;               /**< \brief [31:0] System Timer Bits [47:16] (r) */
} Ifx_STM_TIM4_Bits;

/** \brief  Timer Register 5 */
typedef struct _Ifx_STM_TIM5_Bits
{
    unsigned int STM51_20:32;               /**< \brief [31:0] System Timer Bits [51:20] (r) */
} Ifx_STM_TIM5_Bits;

/** \brief  Timer Register 6 */
typedef struct _Ifx_STM_TIM6_Bits
{
    unsigned int STM63_32:32;               /**< \brief [31:0] System Timer Bits [63:32] (r) */
} Ifx_STM_TIM6_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Stm_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_STM_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_STM_ACCEN1;

/** \brief  Timer Capture Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_CAP_Bits B;                     /**< \brief Bitfield access */
} Ifx_STM_CAP;

/** \brief  Timer Capture Register Second View */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_CAPSV_Bits B;                   /**< \brief Bitfield access */
} Ifx_STM_CAPSV;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_STM_CLC;

/** \brief  Compare Match Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_CMCON_Bits B;                   /**< \brief Bitfield access */
} Ifx_STM_CMCON;

/** \brief  Compare Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_CMP_Bits B;                     /**< \brief Bitfield access */
} Ifx_STM_CMP;

/** \brief  Interrupt Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_ICR_Bits B;                     /**< \brief Bitfield access */
} Ifx_STM_ICR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_STM_ID;

/** \brief  Interrupt Set/Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_ISCR_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_ISCR;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_STM_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_STM_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_STM_KRSTCLR;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_OCS_Bits B;                     /**< \brief Bitfield access */
} Ifx_STM_OCS;

/** \brief  Timer Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM0_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_TIM0;

/** \brief  Timer Register 0 Second View */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM0SV_Bits B;                  /**< \brief Bitfield access */
} Ifx_STM_TIM0SV;

/** \brief  Timer Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM1_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_TIM1;

/** \brief  Timer Register 2 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM2_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_TIM2;

/** \brief  Timer Register 3 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM3_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_TIM3;

/** \brief  Timer Register 4 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM4_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_TIM4;

/** \brief  Timer Register 5 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM5_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_TIM5;

/** \brief  Timer Register 6 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_STM_TIM6_Bits B;                    /**< \brief Bitfield access */
} Ifx_STM_TIM6;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Stm_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  STM object */
typedef volatile struct _Ifx_STM
{
    Ifx_STM_CLC CLC;                        /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_STM_ID ID;                          /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_STM_TIM0 TIM0;                      /**< \brief 10, Timer Register 0 */
    Ifx_STM_TIM1 TIM1;                      /**< \brief 14, Timer Register 1 */
    Ifx_STM_TIM2 TIM2;                      /**< \brief 18, Timer Register 2 */
    Ifx_STM_TIM3 TIM3;                      /**< \brief 1C, Timer Register 3 */
    Ifx_STM_TIM4 TIM4;                      /**< \brief 20, Timer Register 4 */
    Ifx_STM_TIM5 TIM5;                      /**< \brief 24, Timer Register 5 */
    Ifx_STM_TIM6 TIM6;                      /**< \brief 28, Timer Register 6 */
    Ifx_STM_CAP CAP;                        /**< \brief 2C, Timer Capture Register */
    Ifx_STM_CMP CMP[2];                     /**< \brief 30, Compare Register */
    Ifx_STM_CMCON CMCON;                    /**< \brief 38, Compare Match Control Register */
    Ifx_STM_ICR ICR;                        /**< \brief 3C, Interrupt Control Register */
    Ifx_STM_ISCR ISCR;                      /**< \brief 40, Interrupt Set/Clear Register */
    unsigned char reserved_44[12];          /**< \brief 44, \internal Reserved */
    Ifx_STM_TIM0SV TIM0SV;                  /**< \brief 50, Timer Register 0 Second View */
    Ifx_STM_CAPSV CAPSV;                    /**< \brief 54, Timer Capture Register Second View */
    unsigned char reserved_58[144];         /**< \brief 58, \internal Reserved */
    Ifx_STM_OCS OCS;                        /**< \brief E8, OCDS Control and Status */
    Ifx_STM_KRSTCLR KRSTCLR;                /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_STM_KRST1 KRST1;                    /**< \brief F0, Kernel Reset Register 1 */
    Ifx_STM_KRST0 KRST0;                    /**< \brief F4, Kernel Reset Register 0 */
    Ifx_STM_ACCEN1 ACCEN1;                  /**< \brief F8, Access Enable Register 1 */
    Ifx_STM_ACCEN0 ACCEN0;                  /**< \brief FC, Access Enable Register 0 */
} Ifx_STM;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSTM_REGDEF_H */
