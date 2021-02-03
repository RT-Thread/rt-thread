/**
 * \file IfxIom_regdef.h
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
 * \defgroup IfxLld_Iom Iom
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Iom_Bitfields Bitfields
 * \ingroup IfxLld_Iom
 * 
 * \defgroup IfxLld_Iom_union Union
 * \ingroup IfxLld_Iom
 * 
 * \defgroup IfxLld_Iom_struct Struct
 * \ingroup IfxLld_Iom
 * 
 */
#ifndef IFXIOM_REGDEF_H
#define IFXIOM_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Iom_Bitfields
 * \{  */

/** \brief  IOM Access Enable Register 0 */
typedef struct _Ifx_IOM_ACCEN0_Bits
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
} Ifx_IOM_ACCEN0_Bits;

/** \brief  IOM Access Enable Register 1 */
typedef struct _Ifx_IOM_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_IOM_ACCEN1_Bits;

/** \brief  IOM Clock Control Register */
typedef struct _Ifx_IOM_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (rh) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int RMC:8;                     /**< \brief [15:8] 8-bit Clock Divider Value in RUN Mode (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_IOM_CLC_Bits;

/** \brief  IOM Event Combiner Module Counter Configuration Register */
typedef struct _Ifx_IOM_ECMCCFG_Bits
{
    unsigned int SELC0:4;                   /**< \brief [3:0] Event Channel Select (rw) */
    unsigned int THRC0:4;                   /**< \brief [7:4] Channel Event Counter Threshold (rw) */
    unsigned int SELC1:4;                   /**< \brief [11:8] Event Channel Select (rw) */
    unsigned int THCR1:4;                   /**< \brief [15:12] Channel Event Counter Threshold (rw) */
    unsigned int SELC2:4;                   /**< \brief [19:16] Event Channel Select (rw) */
    unsigned int THCR2:4;                   /**< \brief [23:20] Channel Event Counter Threshold (rw) */
    unsigned int SELC3:4;                   /**< \brief [27:24] Event Channel Select (rw) */
    unsigned int THCR3:4;                   /**< \brief [31:28] Channel Event Counter Threshold (rw) */
} Ifx_IOM_ECMCCFG_Bits;

/** \brief  IOM Event Combiner Module Event Trigger History Register 0 */
typedef struct _Ifx_IOM_ECMETH0_Bits
{
    unsigned int ETA0:1;                    /**< \brief [0:0] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA1:1;                    /**< \brief [1:1] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA2:1;                    /**< \brief [2:2] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA3:1;                    /**< \brief [3:3] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA4:1;                    /**< \brief [4:4] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA5:1;                    /**< \brief [5:5] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA6:1;                    /**< \brief [6:6] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA7:1;                    /**< \brief [7:7] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA8:1;                    /**< \brief [8:8] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA9:1;                    /**< \brief [9:9] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA10:1;                   /**< \brief [10:10] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA11:1;                   /**< \brief [11:11] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA12:1;                   /**< \brief [12:12] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA13:1;                   /**< \brief [13:13] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA14:1;                   /**< \brief [14:14] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETA15:1;                   /**< \brief [15:15] LAM 0-15 Event Trigger Activity (last) (rwh) */
    unsigned int ETB0:1;                    /**< \brief [16:16] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB1:1;                    /**< \brief [17:17] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB2:1;                    /**< \brief [18:18] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB3:1;                    /**< \brief [19:19] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB4:1;                    /**< \brief [20:20] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB5:1;                    /**< \brief [21:21] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB6:1;                    /**< \brief [22:22] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB7:1;                    /**< \brief [23:23] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB8:1;                    /**< \brief [24:24] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB9:1;                    /**< \brief [25:25] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB10:1;                   /**< \brief [26:26] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB11:1;                   /**< \brief [27:27] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB12:1;                   /**< \brief [28:28] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB13:1;                   /**< \brief [29:29] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB14:1;                   /**< \brief [30:30] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
    unsigned int ETB15:1;                   /**< \brief [31:31] LAM 0-15 Event Trigger Activity (previous ETA0-15) (rwh) */
} Ifx_IOM_ECMETH0_Bits;

/** \brief  IOM Event Combiner Module Event Trigger History Register 1 */
typedef struct _Ifx_IOM_ECMETH1_Bits
{
    unsigned int ETC0:1;                    /**< \brief [0:0] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC1:1;                    /**< \brief [1:1] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC2:1;                    /**< \brief [2:2] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC3:1;                    /**< \brief [3:3] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC4:1;                    /**< \brief [4:4] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC5:1;                    /**< \brief [5:5] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC6:1;                    /**< \brief [6:6] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC7:1;                    /**< \brief [7:7] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC8:1;                    /**< \brief [8:8] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC9:1;                    /**< \brief [9:9] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC10:1;                   /**< \brief [10:10] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC11:1;                   /**< \brief [11:11] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC12:1;                   /**< \brief [12:12] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC13:1;                   /**< \brief [13:13] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC14:1;                   /**< \brief [14:14] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETC15:1;                   /**< \brief [15:15] LAM 0-15 Event Trigger Activity (previous ETB0-15) (rwh) */
    unsigned int ETD0:1;                    /**< \brief [16:16] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD1:1;                    /**< \brief [17:17] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD2:1;                    /**< \brief [18:18] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD3:1;                    /**< \brief [19:19] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD4:1;                    /**< \brief [20:20] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD5:1;                    /**< \brief [21:21] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD6:1;                    /**< \brief [22:22] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD7:1;                    /**< \brief [23:23] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD8:1;                    /**< \brief [24:24] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD9:1;                    /**< \brief [25:25] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD10:1;                   /**< \brief [26:26] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD11:1;                   /**< \brief [27:27] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD12:1;                   /**< \brief [28:28] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD13:1;                   /**< \brief [29:29] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD14:1;                   /**< \brief [30:30] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
    unsigned int ETD15:1;                   /**< \brief [31:31] LAM 0-15 Event Trigger Activity (previous ETC0-15) (rwh) */
} Ifx_IOM_ECMETH1_Bits;

/** \brief  IOM Event Combiner Module Global Event Selection Register */
typedef struct _Ifx_IOM_ECMSELR_Bits
{
    unsigned int CES0:1;                    /**< \brief [0:0] Event Combiner Selection (rw) */
    unsigned int CES1:1;                    /**< \brief [1:1] Event Combiner Selection (rw) */
    unsigned int CES2:1;                    /**< \brief [2:2] Event Combiner Selection (rw) */
    unsigned int CES3:1;                    /**< \brief [3:3] Event Combiner Selection (rw) */
    unsigned int CES4:1;                    /**< \brief [4:4] Event Combiner Selection (rw) */
    unsigned int CES5:1;                    /**< \brief [5:5] Event Combiner Selection (rw) */
    unsigned int CES6:1;                    /**< \brief [6:6] Event Combiner Selection (rw) */
    unsigned int CES7:1;                    /**< \brief [7:7] Event Combiner Selection (rw) */
    unsigned int CES8:1;                    /**< \brief [8:8] Event Combiner Selection (rw) */
    unsigned int CES9:1;                    /**< \brief [9:9] Event Combiner Selection (rw) */
    unsigned int CES10:1;                   /**< \brief [10:10] Event Combiner Selection (rw) */
    unsigned int CES11:1;                   /**< \brief [11:11] Event Combiner Selection (rw) */
    unsigned int CES12:1;                   /**< \brief [12:12] Event Combiner Selection (rw) */
    unsigned int CES13:1;                   /**< \brief [13:13] Event Combiner Selection (rw) */
    unsigned int CES14:1;                   /**< \brief [14:14] Event Combiner Selection (rw) */
    unsigned int CES15:1;                   /**< \brief [15:15] Event Combiner Selection (rw) */
    unsigned int CTS0:1;                    /**< \brief [16:16] Accumulated (Counted) Event Combiner Selection (rw) */
    unsigned int CTS1:1;                    /**< \brief [17:17] Accumulated (Counted) Event Combiner Selection (rw) */
    unsigned int CTS2:1;                    /**< \brief [18:18] Accumulated (Counted) Event Combiner Selection (rw) */
    unsigned int CTS3:1;                    /**< \brief [19:19] Accumulated (Counted) Event Combiner Selection (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_IOM_ECMSELR_Bits;

/** \brief  IOM Filter and Prescaler Cell Control Register */
typedef struct _Ifx_IOM_FPCCTR_Bits
{
    unsigned int CMP:16;                    /**< \brief [15:0] Threshold Value of Filter & Prescaler Cell k (rw) */
    unsigned int MOD:3;                     /**< \brief [18:16] Operation Mode Selection for Filter & Prescaler Cell k (rw) */
    unsigned int ISM:2;                     /**< \brief [20:19] Monitor Input Signal Selection for Filter & Prescaler Cell k (rw) */
    unsigned int reserved_21:1;             /**< \brief \internal Reserved */
    unsigned int RTG:1;                     /**< \brief [22:22] Reset Timer behaviour for Filter & Prescaler Cell k on Glitch (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int ISR:3;                     /**< \brief [26:24] Reference Input Signal Selection for Filter & Prescaler Cell k (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_IOM_FPCCTR_Bits;

/** \brief  IOM Filter and Prescaler Cells Rising & Falling Edge Status Register */
typedef struct _Ifx_IOM_FPCESR_Bits
{
    unsigned int FEG0:1;                    /**< \brief [0:0] Falling Edge Glitch Flag for FPC0 (rwh) */
    unsigned int FEG1:1;                    /**< \brief [1:1] Falling Edge Glitch Flag for FPC1 (rwh) */
    unsigned int FEG2:1;                    /**< \brief [2:2] Falling Edge Glitch Flag for FPC2 (rwh) */
    unsigned int FEG3:1;                    /**< \brief [3:3] Falling Edge Glitch Flag for FPC3 (rwh) */
    unsigned int FEG4:1;                    /**< \brief [4:4] Falling Edge Glitch Flag for FPC4 (rwh) */
    unsigned int FEG5:1;                    /**< \brief [5:5] Falling Edge Glitch Flag for FPC5 (rwh) */
    unsigned int FEG6:1;                    /**< \brief [6:6] Falling Edge Glitch Flag for FPC6 (rwh) */
    unsigned int FEG7:1;                    /**< \brief [7:7] Falling Edge Glitch Flag for FPC7 (rwh) */
    unsigned int FEG8:1;                    /**< \brief [8:8] Falling Edge Glitch Flag for FPC8 (rwh) */
    unsigned int FEG9:1;                    /**< \brief [9:9] Falling Edge Glitch Flag for FPC9 (rwh) */
    unsigned int FEG10:1;                   /**< \brief [10:10] Falling Edge Glitch Flag for FPC10 (rwh) */
    unsigned int FEG11:1;                   /**< \brief [11:11] Falling Edge Glitch Flag for FPC11 (rwh) */
    unsigned int FEG12:1;                   /**< \brief [12:12] Falling Edge Glitch Flag for FPC12 (rwh) */
    unsigned int FEG13:1;                   /**< \brief [13:13] Falling Edge Glitch Flag for FPC13 (rwh) */
    unsigned int FEG14:1;                   /**< \brief [14:14] Falling Edge Glitch Flag for FPC14 (rwh) */
    unsigned int FEG15:1;                   /**< \brief [15:15] Falling Edge Glitch Flag for FPC15 (rwh) */
    unsigned int REG0:1;                    /**< \brief [16:16] Rising Edge Glitch Flag for FPC0 (rwh) */
    unsigned int REG1:1;                    /**< \brief [17:17] Rising Edge Glitch Flag for FPC1 (rwh) */
    unsigned int REG2:1;                    /**< \brief [18:18] Rising Edge Glitch Flag for FPC2 (rwh) */
    unsigned int REG3:1;                    /**< \brief [19:19] Rising Edge Glitch Flag for FPC3 (rwh) */
    unsigned int REG4:1;                    /**< \brief [20:20] Rising Edge Glitch Flag for FPC4 (rwh) */
    unsigned int REG5:1;                    /**< \brief [21:21] Rising Edge Glitch Flag for FPC5 (rwh) */
    unsigned int REG6:1;                    /**< \brief [22:22] Rising Edge Glitch Flag for FPC6 (rwh) */
    unsigned int REG7:1;                    /**< \brief [23:23] Rising Edge Glitch Flag for FPC7 (rwh) */
    unsigned int REG8:1;                    /**< \brief [24:24] Rising Edge Glitch Flag for FPC8 (rwh) */
    unsigned int REG9:1;                    /**< \brief [25:25] Rising Edge Glitch Flag for FPC9 (rwh) */
    unsigned int REG10:1;                   /**< \brief [26:26] Rising Edge Glitch Flag for FPC10 (rwh) */
    unsigned int REG11:1;                   /**< \brief [27:27] Rising Edge Glitch Flag for FPC11 (rwh) */
    unsigned int REG12:1;                   /**< \brief [28:28] Rising Edge Glitch Flag for FPC12 (rwh) */
    unsigned int REG13:1;                   /**< \brief [29:29] Rising Edge Glitch Flag for FPC13 (rwh) */
    unsigned int REG14:1;                   /**< \brief [30:30] Rising Edge Glitch Flag for FPC14 (rwh) */
    unsigned int REG15:1;                   /**< \brief [31:31] Rising Edge Glitch Flag for FPC15 (rwh) */
} Ifx_IOM_FPCESR_Bits;

/** \brief  IOM Filter and Prescaler Cell Timer Register k */
typedef struct _Ifx_IOM_FPCTIM_Bits
{
    unsigned int TIM:16;                    /**< \brief [15:0] Timer Value of Filter and Prescaler Cell k (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_IOM_FPCTIM_Bits;

/** \brief  IOM GTM Input EXOR Combiner Selection Register */
typedef struct _Ifx_IOM_GTMEXR_Bits
{
    unsigned int EN0:1;                     /**< \brief [0:0] GTM input 0 selection for EXOR combiner (rw) */
    unsigned int EN1:1;                     /**< \brief [1:1] GTM input 1 selection for EXOR combiner (rw) */
    unsigned int EN2:1;                     /**< \brief [2:2] GTM input 2 selection for EXOR combiner (rw) */
    unsigned int EN3:1;                     /**< \brief [3:3] GTM input 3 selection for EXOR combiner (rw) */
    unsigned int EN4:1;                     /**< \brief [4:4] GTM input 4 selection for EXOR combiner (rw) */
    unsigned int EN5:1;                     /**< \brief [5:5] GTM input 5 selection for EXOR combiner (rw) */
    unsigned int EN6:1;                     /**< \brief [6:6] GTM input 6 selection for EXOR combiner (rw) */
    unsigned int EN7:1;                     /**< \brief [7:7] GTM input 7 selection for EXOR combiner (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_IOM_GTMEXR_Bits;

/** \brief  IOM Identification Register */
typedef struct _Ifx_IOM_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Number Value (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_IOM_ID_Bits;

/** \brief  IOM Kernel Reset Register 0 */
typedef struct _Ifx_IOM_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_IOM_KRST0_Bits;

/** \brief  IOM Kernel Reset Register 1 */
typedef struct _Ifx_IOM_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_IOM_KRST1_Bits;

/** \brief  IOM Kernel Reset Status Clear Register */
typedef struct _Ifx_IOM_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_IOM_KRSTCLR_Bits;

/** \brief  IOM Logic Analyzer Module Configuration Register */
typedef struct _Ifx_IOM_LAMCFG_Bits
{
    unsigned int IVR:1;                     /**< \brief [0:0] Invert Reference LAM block m (rw) */
    unsigned int IVM:1;                     /**< \brief [1:1] Invert Monitor LAM block m (rw) */
    unsigned int MOS:1;                     /**< \brief [2:2] Monitor Source Select LAM block m (rw) */
    unsigned int RMS:1;                     /**< \brief [3:3] Runmode Select LAM block m (rw) */
    unsigned int EWS:1;                     /**< \brief [4:4] Event Window Select LAM block m (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int EDS:4;                     /**< \brief [11:8] Event Window Active Edge Selection LAM block m (rw) */
    unsigned int IVW:1;                     /**< \brief [12:12] Invert Event Window LAM block m (rw) */
    unsigned int reserved_13:3;             /**< \brief \internal Reserved */
    unsigned int MCS:4;                     /**< \brief [19:16] Monitor Input Signal Selection LAM block m (rw) */
    unsigned int RCS:4;                     /**< \brief [23:20] Reference Input Signal Selection LAM block m (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_IOM_LAMCFG_Bits;

/** \brief  IOM Logic Analyzer Module Event Window Count Status Register */
typedef struct _Ifx_IOM_LAMEWC_Bits
{
    unsigned int CNT:24;                    /**< \brief [23:0] Event Window Count Value LAM block m (r) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_IOM_LAMEWC_Bits;

/** \brief  IOM Logic Analyzer Module Event Window Configuration Register */
typedef struct _Ifx_IOM_LAMEWS_Bits
{
    unsigned int THR:24;                    /**< \brief [23:0] Event Window Count Threshold (rw) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_IOM_LAMEWS_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Iom_union
 * \{  */

/** \brief  IOM Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_ACCEN0;

/** \brief  IOM Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_ACCEN1;

/** \brief  IOM Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_IOM_CLC;

/** \brief  IOM Event Combiner Module Counter Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_ECMCCFG_Bits B;                 /**< \brief Bitfield access */
} Ifx_IOM_ECMCCFG;

/** \brief  IOM Event Combiner Module Event Trigger History Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_ECMETH0_Bits B;                 /**< \brief Bitfield access */
} Ifx_IOM_ECMETH0;

/** \brief  IOM Event Combiner Module Event Trigger History Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_ECMETH1_Bits B;                 /**< \brief Bitfield access */
} Ifx_IOM_ECMETH1;

/** \brief  IOM Event Combiner Module Global Event Selection Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_ECMSELR_Bits B;                 /**< \brief Bitfield access */
} Ifx_IOM_ECMSELR;

/** \brief  IOM Filter and Prescaler Cell Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_FPCCTR_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_FPCCTR;

/** \brief  IOM Filter and Prescaler Cells Rising & Falling Edge Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_FPCESR_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_FPCESR;

/** \brief  IOM Filter and Prescaler Cell Timer Register k */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_FPCTIM_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_FPCTIM;

/** \brief  IOM GTM Input EXOR Combiner Selection Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_GTMEXR_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_GTMEXR;

/** \brief  IOM Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_IOM_ID;

/** \brief  IOM Kernel Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_IOM_KRST0;

/** \brief  IOM Kernel Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_IOM_KRST1;

/** \brief  IOM Kernel Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_IOM_KRSTCLR;

/** \brief  IOM Logic Analyzer Module Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_LAMCFG_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_LAMCFG;

/** \brief  IOM Logic Analyzer Module Event Window Count Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_LAMEWC_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_LAMEWC;

/** \brief  IOM Logic Analyzer Module Event Window Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_IOM_LAMEWS_Bits B;                  /**< \brief Bitfield access */
} Ifx_IOM_LAMEWS;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Iom_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  IOM object */
typedef volatile struct _Ifx_IOM
{
    Ifx_IOM_CLC CLC;                        /**< \brief 0, IOM Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_IOM_ID ID;                          /**< \brief 8, IOM Identification Register */
    unsigned char reserved_C[16];           /**< \brief C, \internal Reserved */
    Ifx_IOM_KRSTCLR KRSTCLR;                /**< \brief 1C, IOM Kernel Reset Status Clear Register */
    Ifx_IOM_KRST1 KRST1;                    /**< \brief 20, IOM Kernel Reset Register 1 */
    Ifx_IOM_KRST0 KRST0;                    /**< \brief 24, IOM Kernel Reset Register 0 */
    Ifx_IOM_ACCEN1 ACCEN1;                  /**< \brief 28, IOM Access Enable Register 1 */
    Ifx_IOM_ACCEN0 ACCEN0;                  /**< \brief 2C, IOM Access Enable Register 0 */
    Ifx_IOM_ECMCCFG ECMCCFG;                /**< \brief 30, IOM Event Combiner Module Counter Configuration Register */
    Ifx_IOM_ECMSELR ECMSELR;                /**< \brief 34, IOM Event Combiner Module Global Event Selection Register */
    Ifx_IOM_ECMETH0 ECMETH0;                /**< \brief 38, IOM Event Combiner Module Event Trigger History Register 0 */
    Ifx_IOM_ECMETH1 ECMETH1;                /**< \brief 3C, IOM Event Combiner Module Event Trigger History Register 1 */
    Ifx_IOM_GTMEXR GTMEXR;                  /**< \brief 40, IOM GTM Input EXOR Combiner Selection Register */
    unsigned char reserved_44[52];          /**< \brief 44, \internal Reserved */
    Ifx_IOM_FPCESR FPCESR;                  /**< \brief 78, IOM Filter and Prescaler Cells Rising & Falling Edge Status Register */
    unsigned char reserved_7C[4];           /**< \brief 7C, \internal Reserved */
    Ifx_IOM_FPCCTR FPCCTR[16];              /**< \brief 80, IOM Filter and Prescaler Cell Control Register */
    Ifx_IOM_FPCTIM FPCTIM[16];              /**< \brief C0, IOM Filter and Prescaler Cell Timer Register k */
    Ifx_IOM_LAMEWC LAMEWC[16];              /**< \brief 100, IOM Logic Analyzer Module Event Window Count Status Register */
    unsigned char reserved_140[64];         /**< \brief 140, \internal Reserved */
    Ifx_IOM_LAMCFG LAMCFG[16];              /**< \brief 180, IOM Logic Analyzer Module Configuration Register */
    Ifx_IOM_LAMEWS LAMEWS[16];              /**< \brief 1C0, IOM Logic Analyzer Module Event Window Configuration Register */
} Ifx_IOM;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXIOM_REGDEF_H */
