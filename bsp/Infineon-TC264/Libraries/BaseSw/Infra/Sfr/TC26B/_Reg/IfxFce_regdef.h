/**
 * \file IfxFce_regdef.h
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
 * \defgroup IfxLld_Fce Fce
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Fce_Bitfields Bitfields
 * \ingroup IfxLld_Fce
 * 
 * \defgroup IfxLld_Fce_union Union
 * \ingroup IfxLld_Fce
 * 
 * \defgroup IfxLld_Fce_struct Struct
 * \ingroup IfxLld_Fce
 * 
 */
#ifndef IFXFCE_REGDEF_H
#define IFXFCE_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Fce_Bitfields
 * \{  */

/** \brief  Access Enable Register 0 */
typedef struct _Ifx_FCE_ACCEN0_Bits
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
} Ifx_FCE_ACCEN0_Bits;

/** \brief  Access Enable Register 1 */
typedef struct _Ifx_FCE_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_FCE_ACCEN1_Bits;

/** \brief  CRC Configuration Register */
typedef struct _Ifx_FCE_CFG_Bits
{
    unsigned int CMI:1;                     /**< \brief [0:0] CRC Mismatch Interrupt (rw) */
    unsigned int CEI:1;                     /**< \brief [1:1] Configuration Error Interrupt (rw) */
    unsigned int LEI:1;                     /**< \brief [2:2] Length Error Interrupt (rw) */
    unsigned int BEI:1;                     /**< \brief [3:3] Bus Error Interrupt (rw) */
    unsigned int CCE:1;                     /**< \brief [4:4] CRC Check Comparison (rw) */
    unsigned int ALR:1;                     /**< \brief [5:5] Automatic Length Reload (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int REFIN:1;                   /**< \brief [8:8] IR Byte Wise Reflection (rw) */
    unsigned int REFOUT:1;                  /**< \brief [9:9] CRC 32-Bit Wise Reflection (rw) */
    unsigned int XSEL:1;                    /**< \brief [10:10] Selects the value to be xored with the final CRC (rw) */
    unsigned int reserved_11:21;            /**< \brief \internal Reserved */
} Ifx_FCE_CFG_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_FCE_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_FCE_CLC_Bits;

/** \brief  CRC Test Register */
typedef struct _Ifx_FCE_CTR_Bits
{
    unsigned int FCM:1;                     /**< \brief [0:0] Force CRC Mismatch (rw) */
    unsigned int FRM_CFG:1;                 /**< \brief [1:1] Force CFG Register Mismatch (rw) */
    unsigned int FRM_CHECK:1;               /**< \brief [2:2] Force Check Register Mismatch (rw) */
    unsigned int reserved_3:29;             /**< \brief \internal Reserved */
} Ifx_FCE_CTR_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_FCE_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_FCE_ID_Bits;

/** \brief  CRC Check Register */
typedef struct _Ifx_FCE_IN0_CHECK_Bits
{
    unsigned int CHECK:32;                  /**< \brief [31:0] CHECK Register (rw) */
} Ifx_FCE_IN0_CHECK_Bits;

/** \brief  CRC Register */
typedef struct _Ifx_FCE_IN0_CRC_Bits
{
    unsigned int CRC:32;                    /**< \brief [31:0] CRC Register (rwh) */
} Ifx_FCE_IN0_CRC_Bits;

/** \brief  Input Register */
typedef struct _Ifx_FCE_IN0_IR_Bits
{
    unsigned int IR:32;                     /**< \brief [31:0] Input Register (rw) */
} Ifx_FCE_IN0_IR_Bits;

/** \brief  CRC Result Register */
typedef struct _Ifx_FCE_IN0_RES_Bits
{
    unsigned int RES:32;                    /**< \brief [31:0] Result Register (rh) */
} Ifx_FCE_IN0_RES_Bits;

/** \brief  CRC Check Register */
typedef struct _Ifx_FCE_IN1_CHECK_Bits
{
    unsigned int CHECK:32;                  /**< \brief [31:0] CHECK Register (rw) */
} Ifx_FCE_IN1_CHECK_Bits;

/** \brief  CRC Register */
typedef struct _Ifx_FCE_IN1_CRC_Bits
{
    unsigned int CRC:32;                    /**< \brief [31:0] CRC Register (rwh) */
} Ifx_FCE_IN1_CRC_Bits;

/** \brief  Input Register */
typedef struct _Ifx_FCE_IN1_IR_Bits
{
    unsigned int IR:32;                     /**< \brief [31:0] Input Register (rw) */
} Ifx_FCE_IN1_IR_Bits;

/** \brief  CRC Result Register */
typedef struct _Ifx_FCE_IN1_RES_Bits
{
    unsigned int RES:32;                    /**< \brief [31:0] Result Register (rh) */
} Ifx_FCE_IN1_RES_Bits;

/** \brief  CRC Check Register */
typedef struct _Ifx_FCE_IN2_CHECK_Bits
{
    unsigned int CHECK:16;                  /**< \brief [15:0] CHECK Register (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FCE_IN2_CHECK_Bits;

/** \brief  CRC Register */
typedef struct _Ifx_FCE_IN2_CRC_Bits
{
    unsigned int CRC:16;                    /**< \brief [15:0] CRC Register (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FCE_IN2_CRC_Bits;

/** \brief  Input Register */
typedef struct _Ifx_FCE_IN2_IR_Bits
{
    unsigned int IR:16;                     /**< \brief [15:0] Input Register (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FCE_IN2_IR_Bits;

/** \brief  CRC Result Register */
typedef struct _Ifx_FCE_IN2_RES_Bits
{
    unsigned int RES:16;                    /**< \brief [15:0] Result Register (rh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FCE_IN2_RES_Bits;

/** \brief  CRC Check Register */
typedef struct _Ifx_FCE_IN3_CHECK_Bits
{
    unsigned int CHECK:8;                   /**< \brief [7:0] CHECK Register (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_FCE_IN3_CHECK_Bits;

/** \brief  CRC Register */
typedef struct _Ifx_FCE_IN3_CRC_Bits
{
    unsigned int CRC:8;                     /**< \brief [7:0] CRC Register (rwh) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_FCE_IN3_CRC_Bits;

/** \brief  Input Register */
typedef struct _Ifx_FCE_IN3_IR_Bits
{
    unsigned int IR:8;                      /**< \brief [7:0] Input Register (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_FCE_IN3_IR_Bits;

/** \brief  CRC Result Register */
typedef struct _Ifx_FCE_IN3_RES_Bits
{
    unsigned int RES:8;                     /**< \brief [7:0] Result Register (rh) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_FCE_IN3_RES_Bits;

/** \brief  Kernel Reset Register 0 */
typedef struct _Ifx_FCE_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rw) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_FCE_KRST0_Bits;

/** \brief  Kernel Reset Register 1 */
typedef struct _Ifx_FCE_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_FCE_KRST1_Bits;

/** \brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_FCE_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_FCE_KRSTCLR_Bits;

/** \brief  CRC Length Register */
typedef struct _Ifx_FCE_LENGTH_Bits
{
    unsigned int LENGTH:16;                 /**< \brief [15:0] Message Length Register (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_FCE_LENGTH_Bits;

/** \brief  CRC Status Register */
typedef struct _Ifx_FCE_STS_Bits
{
    unsigned int CMF:1;                     /**< \brief [0:0] CRC Mismatch Flag (rwh) */
    unsigned int CEF:1;                     /**< \brief [1:1] Configuration Error Flag (rwh) */
    unsigned int LEF:1;                     /**< \brief [2:2] Length Error Flag (rwh) */
    unsigned int BEF:1;                     /**< \brief [3:3] Bus Error Flag (rwh) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_FCE_STS_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Fce_union
 * \{  */

/** \brief  Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_FCE_ACCEN0;

/** \brief  Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_FCE_ACCEN1;

/** \brief  CRC Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_CFG_Bits B;                     /**< \brief Bitfield access */
} Ifx_FCE_CFG;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_FCE_CLC;

/** \brief  CRC Test Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_CTR_Bits B;                     /**< \brief Bitfield access */
} Ifx_FCE_CTR;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_FCE_ID;

/** \brief  CRC Check Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN0_CHECK_Bits B;               /**< \brief Bitfield access */
} Ifx_FCE_IN0_CHECK;

/** \brief  CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN0_CRC_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN0_CRC;

/** \brief  Input Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN0_IR_Bits B;                  /**< \brief Bitfield access */
} Ifx_FCE_IN0_IR;

/** \brief  CRC Result Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN0_RES_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN0_RES;

/** \brief  CRC Check Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN1_CHECK_Bits B;               /**< \brief Bitfield access */
} Ifx_FCE_IN1_CHECK;

/** \brief  CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN1_CRC_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN1_CRC;

/** \brief  Input Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN1_IR_Bits B;                  /**< \brief Bitfield access */
} Ifx_FCE_IN1_IR;

/** \brief  CRC Result Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN1_RES_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN1_RES;

/** \brief  CRC Check Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN2_CHECK_Bits B;               /**< \brief Bitfield access */
} Ifx_FCE_IN2_CHECK;

/** \brief  CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN2_CRC_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN2_CRC;

/** \brief  Input Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN2_IR_Bits B;                  /**< \brief Bitfield access */
} Ifx_FCE_IN2_IR;

/** \brief  CRC Result Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN2_RES_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN2_RES;

/** \brief  CRC Check Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN3_CHECK_Bits B;               /**< \brief Bitfield access */
} Ifx_FCE_IN3_CHECK;

/** \brief  CRC Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN3_CRC_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN3_CRC;

/** \brief  Input Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN3_IR_Bits B;                  /**< \brief Bitfield access */
} Ifx_FCE_IN3_IR;

/** \brief  CRC Result Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_IN3_RES_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_IN3_RES;

/** \brief  Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_FCE_KRST0;

/** \brief  Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_FCE_KRST1;

/** \brief  Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_FCE_KRSTCLR;

/** \brief  CRC Length Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_LENGTH_Bits B;                  /**< \brief Bitfield access */
} Ifx_FCE_LENGTH;

/** \brief  CRC Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_FCE_STS_Bits B;                     /**< \brief Bitfield access */
} Ifx_FCE_STS;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Fce_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \brief  Input */
typedef volatile struct _Ifx_FCE_IN0
{
    Ifx_FCE_IN0_IR IR;                      /**< \brief 0, Input Register */
    Ifx_FCE_IN0_RES RES;                    /**< \brief 4, CRC Result Register */
    Ifx_FCE_CFG CFG;                        /**< \brief 8, CRC Configuration Register */
    Ifx_FCE_STS STS;                        /**< \brief C, CRC Status Register */
    Ifx_FCE_LENGTH LENGTH;                  /**< \brief 10, CRC Length Register */
    Ifx_FCE_IN0_CHECK CHECK;                /**< \brief 14, CRC Check Register */
    Ifx_FCE_IN0_CRC CRC;                    /**< \brief 18, CRC Register */
    Ifx_FCE_CTR CTR;                        /**< \brief 1C, CRC Test Register */
} Ifx_FCE_IN0;

/** \brief  Input */
typedef volatile struct _Ifx_FCE_IN1
{
    Ifx_FCE_IN1_IR IR;                      /**< \brief 0, Input Register */
    Ifx_FCE_IN1_RES RES;                    /**< \brief 4, CRC Result Register */
    Ifx_FCE_CFG CFG;                        /**< \brief 8, CRC Configuration Register */
    Ifx_FCE_STS STS;                        /**< \brief C, CRC Status Register */
    Ifx_FCE_LENGTH LENGTH;                  /**< \brief 10, CRC Length Register */
    Ifx_FCE_IN1_CHECK CHECK;                /**< \brief 14, CRC Check Register */
    Ifx_FCE_IN1_CRC CRC;                    /**< \brief 18, CRC Register */
    Ifx_FCE_CTR CTR;                        /**< \brief 1C, CRC Test Register */
} Ifx_FCE_IN1;

/** \brief  Input */
typedef volatile struct _Ifx_FCE_IN2
{
    Ifx_FCE_IN2_IR IR;                      /**< \brief 0, Input Register */
    Ifx_FCE_IN2_RES RES;                    /**< \brief 4, CRC Result Register */
    Ifx_FCE_CFG CFG;                        /**< \brief 8, CRC Configuration Register */
    Ifx_FCE_STS STS;                        /**< \brief C, CRC Status Register */
    Ifx_FCE_LENGTH LENGTH;                  /**< \brief 10, CRC Length Register */
    Ifx_FCE_IN2_CHECK CHECK;                /**< \brief 14, CRC Check Register */
    Ifx_FCE_IN2_CRC CRC;                    /**< \brief 18, CRC Register */
    Ifx_FCE_CTR CTR;                        /**< \brief 1C, CRC Test Register */
} Ifx_FCE_IN2;

/** \brief  Input */
typedef volatile struct _Ifx_FCE_IN3
{
    Ifx_FCE_IN3_IR IR;                      /**< \brief 0, Input Register */
    Ifx_FCE_IN3_RES RES;                    /**< \brief 4, CRC Result Register */
    Ifx_FCE_CFG CFG;                        /**< \brief 8, CRC Configuration Register */
    Ifx_FCE_STS STS;                        /**< \brief C, CRC Status Register */
    Ifx_FCE_LENGTH LENGTH;                  /**< \brief 10, CRC Length Register */
    Ifx_FCE_IN3_CHECK CHECK;                /**< \brief 14, CRC Check Register */
    Ifx_FCE_IN3_CRC CRC;                    /**< \brief 18, CRC Register */
    Ifx_FCE_CTR CTR;                        /**< \brief 1C, CRC Test Register */
} Ifx_FCE_IN3;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Fce_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  FCE object */
typedef volatile struct _Ifx_FCE
{
    Ifx_FCE_CLC CLC;                        /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_FCE_ID ID;                          /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[20];           /**< \brief C, \internal Reserved */
    Ifx_FCE_IN0 IN0;                        /**< \brief 20, Input */
    Ifx_FCE_IN1 IN1;                        /**< \brief 40, Input */
    Ifx_FCE_IN2 IN2;                        /**< \brief 60, Input */
    Ifx_FCE_IN3 IN3;                        /**< \brief 80, Input */
    unsigned char reserved_A0[76];          /**< \brief A0, \internal Reserved */
    Ifx_FCE_KRSTCLR KRSTCLR;                /**< \brief EC, Kernel Reset Status Clear Register */
    Ifx_FCE_KRST1 KRST1;                    /**< \brief F0, Kernel Reset Register 1 */
    Ifx_FCE_KRST0 KRST0;                    /**< \brief F4, Kernel Reset Register 0 */
    Ifx_FCE_ACCEN1 ACCEN1;                  /**< \brief F8, Access Enable Register 1 */
    Ifx_FCE_ACCEN0 ACCEN0;                  /**< \brief FC, Access Enable Register 0 */
} Ifx_FCE;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXFCE_REGDEF_H */
