/**
 * \file IfxSmu_regdef.h
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
 * \defgroup IfxLld_Smu Smu
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Smu_Bitfields Bitfields
 * \ingroup IfxLld_Smu
 * 
 * \defgroup IfxLld_Smu_union Union
 * \ingroup IfxLld_Smu
 * 
 * \defgroup IfxLld_Smu_struct Struct
 * \ingroup IfxLld_Smu
 * 
 */
#ifndef IFXSMU_REGDEF_H
#define IFXSMU_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Smu_Bitfields
 * \{  */

/** \brief  SMU Access Enable Register 0 */
typedef struct _Ifx_SMU_ACCEN0_Bits
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
} Ifx_SMU_ACCEN0_Bits;

/** \brief  SMU Access Enable Register 1 */
typedef struct _Ifx_SMU_ACCEN1_Bits
{
    Ifx_Strict_32Bit reserved_0:32;         /**< \brief \internal Reserved */
} Ifx_SMU_ACCEN1_Bits;

/** \brief  Alarm Status Register */
typedef struct _Ifx_SMU_AD_Bits
{
    Ifx_Strict_32Bit DF0:1;                 /**< \brief [0:0] Debug flag for alarm 0 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF1:1;                 /**< \brief [1:1] Debug flag for alarm 1 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF2:1;                 /**< \brief [2:2] Debug flag for alarm 2 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF3:1;                 /**< \brief [3:3] Debug flag for alarm 3 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF4:1;                 /**< \brief [4:4] Debug flag for alarm 4 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF5:1;                 /**< \brief [5:5] Debug flag for alarm 5 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF6:1;                 /**< \brief [6:6] Debug flag for alarm 6 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF7:1;                 /**< \brief [7:7] Debug flag for alarm 7 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF8:1;                 /**< \brief [8:8] Debug flag for alarm 8 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF9:1;                 /**< \brief [9:9] Debug flag for alarm 9 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF10:1;                /**< \brief [10:10] Debug flag for alarm 10 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF11:1;                /**< \brief [11:11] Debug flag for alarm 11 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF12:1;                /**< \brief [12:12] Debug flag for alarm 12 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF13:1;                /**< \brief [13:13] Debug flag for alarm 13 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF14:1;                /**< \brief [14:14] Debug flag for alarm 14 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF15:1;                /**< \brief [15:15] Debug flag for alarm 15 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF16:1;                /**< \brief [16:16] Debug flag for alarm 16 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF17:1;                /**< \brief [17:17] Debug flag for alarm 17 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF18:1;                /**< \brief [18:18] Debug flag for alarm 18 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF19:1;                /**< \brief [19:19] Debug flag for alarm 19 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF20:1;                /**< \brief [20:20] Debug flag for alarm 20 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF21:1;                /**< \brief [21:21] Debug flag for alarm 21 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF22:1;                /**< \brief [22:22] Debug flag for alarm 22 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF23:1;                /**< \brief [23:23] Debug flag for alarm 23 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF24:1;                /**< \brief [24:24] Debug flag for alarm 24 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF25:1;                /**< \brief [25:25] Debug flag for alarm 25 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF26:1;                /**< \brief [26:26] Debug flag for alarm 26 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF27:1;                /**< \brief [27:27] Debug flag for alarm 27 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF28:1;                /**< \brief [28:28] Debug flag for alarm 28 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF29:1;                /**< \brief [29:29] Debug flag for alarm 29 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF30:1;                /**< \brief [30:30] Debug flag for alarm 30 belonging to alarm group x (x=0-6). (rh) */
    Ifx_Strict_32Bit DF31:1;                /**< \brief [31:31] Debug flag for alarm 31 belonging to alarm group x (x=0-6). (rh) */
} Ifx_SMU_AD_Bits;

/** \brief  Alarm and Fault Counter */
typedef struct _Ifx_SMU_AFCNT_Bits
{
    Ifx_Strict_32Bit FCNT:4;                /**< \brief [3:0] Fault Counter. (rh) */
    Ifx_Strict_32Bit reserved_4:4;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ACNT:8;                /**< \brief [15:8] Alarm Counter. (rh) */
    Ifx_Strict_32Bit reserved_16:14;        /**< \brief \internal Reserved */
    Ifx_Strict_32Bit FCO:1;                 /**< \brief [30:30] Fault Counter Overflow. (rh) */
    Ifx_Strict_32Bit ACO:1;                 /**< \brief [31:31] Alarm Counter Overflow. (rh) */
} Ifx_SMU_AFCNT_Bits;

/** \brief  Alarm Status Register */
typedef struct _Ifx_SMU_AG_Bits
{
    Ifx_Strict_32Bit SF0:1;                 /**< \brief [0:0] Status flag for alarm 0 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF1:1;                 /**< \brief [1:1] Status flag for alarm 1 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF2:1;                 /**< \brief [2:2] Status flag for alarm 2 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF3:1;                 /**< \brief [3:3] Status flag for alarm 3 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF4:1;                 /**< \brief [4:4] Status flag for alarm 4 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF5:1;                 /**< \brief [5:5] Status flag for alarm 5 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF6:1;                 /**< \brief [6:6] Status flag for alarm 6 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF7:1;                 /**< \brief [7:7] Status flag for alarm 7 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF8:1;                 /**< \brief [8:8] Status flag for alarm 8 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF9:1;                 /**< \brief [9:9] Status flag for alarm 9 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF10:1;                /**< \brief [10:10] Status flag for alarm 10 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF11:1;                /**< \brief [11:11] Status flag for alarm 11 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF12:1;                /**< \brief [12:12] Status flag for alarm 12 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF13:1;                /**< \brief [13:13] Status flag for alarm 13 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF14:1;                /**< \brief [14:14] Status flag for alarm 14 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF15:1;                /**< \brief [15:15] Status flag for alarm 15 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF16:1;                /**< \brief [16:16] Status flag for alarm 16 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF17:1;                /**< \brief [17:17] Status flag for alarm 17 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF18:1;                /**< \brief [18:18] Status flag for alarm 18 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF19:1;                /**< \brief [19:19] Status flag for alarm 19 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF20:1;                /**< \brief [20:20] Status flag for alarm 20 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF21:1;                /**< \brief [21:21] Status flag for alarm 21 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF22:1;                /**< \brief [22:22] Status flag for alarm 22 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF23:1;                /**< \brief [23:23] Status flag for alarm 23 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF24:1;                /**< \brief [24:24] Status flag for alarm 24 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF25:1;                /**< \brief [25:25] Status flag for alarm 25 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF26:1;                /**< \brief [26:26] Status flag for alarm 26 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF27:1;                /**< \brief [27:27] Status flag for alarm 27 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF28:1;                /**< \brief [28:28] Status flag for alarm 28 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF29:1;                /**< \brief [29:29] Status flag for alarm 29 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF30:1;                /**< \brief [30:30] Status flag for alarm 30 belonging to alarm group x (x=0-6). (rwh) */
    Ifx_Strict_32Bit SF31:1;                /**< \brief [31:31] Status flag for alarm 31 belonging to alarm group x (x=0-6). (rwh) */
} Ifx_SMU_AG_Bits;

/** \brief  Alarm Global Configuration */
typedef struct _Ifx_SMU_AGC_Bits
{
    Ifx_Strict_32Bit IGCS0:3;               /**< \brief [2:0] Interrupt Generation Configuration Set 0 (rw) */
    Ifx_Strict_32Bit reserved_3:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit IGCS1:3;               /**< \brief [6:4] Interrupt Generation Configuration Set 1 (rw) */
    Ifx_Strict_32Bit reserved_7:1;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit IGCS2:3;               /**< \brief [10:8] Interrupt Generation Configuration Set 2 (rw) */
    Ifx_Strict_32Bit reserved_11:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit ICS:3;                 /**< \brief [18:16] Idle Configuration Set (rw) */
    Ifx_Strict_32Bit reserved_19:5;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PES:5;                 /**< \brief [28:24] Port Emergency Stop (rw) */
    Ifx_Strict_32Bit EFRST:1;               /**< \brief [29:29] Enable FAULT to RUN State Transition (rw) */
    Ifx_Strict_32Bit reserved_30:2;         /**< \brief \internal Reserved */
} Ifx_SMU_AGC_Bits;

/** \brief  Alarm Configuration Register */
typedef struct _Ifx_SMU_AGCF_Bits
{
    Ifx_Strict_32Bit CF0:1;                 /**< \brief [0:0]  (rw) */
    Ifx_Strict_32Bit CF1:1;                 /**< \brief [1:1]  (rw) */
    Ifx_Strict_32Bit CF2:1;                 /**< \brief [2:2]  (rw) */
    Ifx_Strict_32Bit CF3:1;                 /**< \brief [3:3]  (rw) */
    Ifx_Strict_32Bit CF4:1;                 /**< \brief [4:4]  (rw) */
    Ifx_Strict_32Bit CF5:1;                 /**< \brief [5:5]  (rw) */
    Ifx_Strict_32Bit CF6:1;                 /**< \brief [6:6]  (rw) */
    Ifx_Strict_32Bit CF7:1;                 /**< \brief [7:7]  (rw) */
    Ifx_Strict_32Bit CF8:1;                 /**< \brief [8:8]  (rw) */
    Ifx_Strict_32Bit CF9:1;                 /**< \brief [9:9]  (rw) */
    Ifx_Strict_32Bit CF10:1;                /**< \brief [10:10]  (rw) */
    Ifx_Strict_32Bit CF11:1;                /**< \brief [11:11]  (rw) */
    Ifx_Strict_32Bit CF12:1;                /**< \brief [12:12]  (rw) */
    Ifx_Strict_32Bit CF13:1;                /**< \brief [13:13]  (rw) */
    Ifx_Strict_32Bit CF14:1;                /**< \brief [14:14]  (rw) */
    Ifx_Strict_32Bit CF15:1;                /**< \brief [15:15]  (rw) */
    Ifx_Strict_32Bit CF16:1;                /**< \brief [16:16]  (rw) */
    Ifx_Strict_32Bit CF17:1;                /**< \brief [17:17]  (rw) */
    Ifx_Strict_32Bit CF18:1;                /**< \brief [18:18]  (rw) */
    Ifx_Strict_32Bit CF19:1;                /**< \brief [19:19]  (rw) */
    Ifx_Strict_32Bit CF20:1;                /**< \brief [20:20]  (rw) */
    Ifx_Strict_32Bit CF21:1;                /**< \brief [21:21]  (rw) */
    Ifx_Strict_32Bit CF22:1;                /**< \brief [22:22]  (rw) */
    Ifx_Strict_32Bit CF23:1;                /**< \brief [23:23]  (rw) */
    Ifx_Strict_32Bit CF24:1;                /**< \brief [24:24]  (rw) */
    Ifx_Strict_32Bit CF25:1;                /**< \brief [25:25]  (rw) */
    Ifx_Strict_32Bit CF26:1;                /**< \brief [26:26]  (rw) */
    Ifx_Strict_32Bit CF27:1;                /**< \brief [27:27]  (rw) */
    Ifx_Strict_32Bit CF28:1;                /**< \brief [28:28]  (rw) */
    Ifx_Strict_32Bit CF29:1;                /**< \brief [29:29]  (rw) */
    Ifx_Strict_32Bit CF30:1;                /**< \brief [30:30]  (rw) */
    Ifx_Strict_32Bit CF31:1;                /**< \brief [31:31]  (rw) */
} Ifx_SMU_AGCF_Bits;

/** \brief  FSP Configuration Register */
typedef struct _Ifx_SMU_AGFSP_Bits
{
    Ifx_Strict_32Bit FE0:1;                 /**< \brief [0:0]  (rw) */
    Ifx_Strict_32Bit FE1:1;                 /**< \brief [1:1]  (rw) */
    Ifx_Strict_32Bit FE2:1;                 /**< \brief [2:2]  (rw) */
    Ifx_Strict_32Bit FE3:1;                 /**< \brief [3:3]  (rw) */
    Ifx_Strict_32Bit FE4:1;                 /**< \brief [4:4]  (rw) */
    Ifx_Strict_32Bit FE5:1;                 /**< \brief [5:5]  (rw) */
    Ifx_Strict_32Bit FE6:1;                 /**< \brief [6:6]  (rw) */
    Ifx_Strict_32Bit FE7:1;                 /**< \brief [7:7]  (rw) */
    Ifx_Strict_32Bit FE8:1;                 /**< \brief [8:8]  (rw) */
    Ifx_Strict_32Bit FE9:1;                 /**< \brief [9:9]  (rw) */
    Ifx_Strict_32Bit FE10:1;                /**< \brief [10:10]  (rw) */
    Ifx_Strict_32Bit FE11:1;                /**< \brief [11:11]  (rw) */
    Ifx_Strict_32Bit FE12:1;                /**< \brief [12:12]  (rw) */
    Ifx_Strict_32Bit FE13:1;                /**< \brief [13:13]  (rw) */
    Ifx_Strict_32Bit FE14:1;                /**< \brief [14:14]  (rw) */
    Ifx_Strict_32Bit FE15:1;                /**< \brief [15:15]  (rw) */
    Ifx_Strict_32Bit FE16:1;                /**< \brief [16:16]  (rw) */
    Ifx_Strict_32Bit FE17:1;                /**< \brief [17:17]  (rw) */
    Ifx_Strict_32Bit FE18:1;                /**< \brief [18:18]  (rw) */
    Ifx_Strict_32Bit FE19:1;                /**< \brief [19:19]  (rw) */
    Ifx_Strict_32Bit FE20:1;                /**< \brief [20:20]  (rw) */
    Ifx_Strict_32Bit FE21:1;                /**< \brief [21:21]  (rw) */
    Ifx_Strict_32Bit FE22:1;                /**< \brief [22:22]  (rw) */
    Ifx_Strict_32Bit FE23:1;                /**< \brief [23:23]  (rw) */
    Ifx_Strict_32Bit FE24:1;                /**< \brief [24:24]  (rw) */
    Ifx_Strict_32Bit FE25:1;                /**< \brief [25:25]  (rw) */
    Ifx_Strict_32Bit FE26:1;                /**< \brief [26:26]  (rw) */
    Ifx_Strict_32Bit FE27:1;                /**< \brief [27:27]  (rw) */
    Ifx_Strict_32Bit FE28:1;                /**< \brief [28:28]  (rw) */
    Ifx_Strict_32Bit FE29:1;                /**< \brief [29:29]  (rw) */
    Ifx_Strict_32Bit FE30:1;                /**< \brief [30:30]  (rw) */
    Ifx_Strict_32Bit FE31:1;                /**< \brief [31:31]  (rw) */
} Ifx_SMU_AGFSP_Bits;

/** \brief  Clock Control Register */
typedef struct _Ifx_SMU_CLC_Bits
{
    Ifx_Strict_32Bit DISR:1;                /**< \brief [0:0] Module Disable Request Bit (rw) */
    Ifx_Strict_32Bit DISS:1;                /**< \brief [1:1] Module Disable Status Bit (rh) */
    Ifx_Strict_32Bit FDIS:1;                /**< \brief [2:2] Force Disable (rw) */
    Ifx_Strict_32Bit EDIS:1;                /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    Ifx_Strict_32Bit reserved_4:28;         /**< \brief \internal Reserved */
} Ifx_SMU_CLC_Bits;

/** \brief  Command Register */
typedef struct _Ifx_SMU_CMD_Bits
{
    Ifx_Strict_32Bit CMD:4;                 /**< \brief [3:0] Implements the SMU Command Interface. (w) */
    Ifx_Strict_32Bit ARG:4;                 /**< \brief [7:4] Implements the SMU Command Interface. (w) */
    Ifx_Strict_32Bit reserved_8:24;         /**< \brief \internal Reserved */
} Ifx_SMU_CMD_Bits;

/** \brief  Debug Register */
typedef struct _Ifx_SMU_DBG_Bits
{
    Ifx_Strict_32Bit SSM:2;                 /**< \brief [1:0] Running state of the SMU State Machine (rh) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_SMU_DBG_Bits;

/** \brief  Fault Signaling Protocol */
typedef struct _Ifx_SMU_FSP_Bits
{
    Ifx_Strict_32Bit PRE1:3;                /**< \brief [2:0] Prescaler1 (rw) */
    Ifx_Strict_32Bit PRE2:2;                /**< \brief [4:3] Prescaler2 (rw) */
    Ifx_Strict_32Bit MODE:2;                /**< \brief [6:5] Fault Signaling Protocol configuration (rw) */
    Ifx_Strict_32Bit PES:1;                 /**< \brief [7:7] Port Emergency Stop (PES) (rw) */
    Ifx_Strict_32Bit TFSP_LOW:14;           /**< \brief [21:8] Specifies the FSP fault state duration (r) */
    Ifx_Strict_32Bit TFSP_HIGH:10;          /**< \brief [31:22] Specifies the FSP fault state duration (rw) */
} Ifx_SMU_FSP_Bits;

/** \brief  Module Identification Register */
typedef struct _Ifx_SMU_ID_Bits
{
    Ifx_Strict_32Bit MODREV:8;              /**< \brief [7:0] Module Revision Number (r) */
    Ifx_Strict_32Bit MODTYPE:8;             /**< \brief [15:8] Module Type (r) */
    Ifx_Strict_32Bit MODNUMBER:16;          /**< \brief [31:16] Module Number Value (r) */
} Ifx_SMU_ID_Bits;

/** \brief  Key Register */
typedef struct _Ifx_SMU_KEYS_Bits
{
    Ifx_Strict_32Bit CFGLCK:8;              /**< \brief [7:0] Configuration Lock (rw) */
    Ifx_Strict_32Bit PERLCK:8;              /**< \brief [15:8] Permanent Lock (rw) */
    Ifx_Strict_32Bit reserved_16:16;        /**< \brief \internal Reserved */
} Ifx_SMU_KEYS_Bits;

/** \brief  SMU Reset Register 0 */
typedef struct _Ifx_SMU_KRST0_Bits
{
    Ifx_Strict_32Bit RST:1;                 /**< \brief [0:0] Kernel Reset (rwh) */
    Ifx_Strict_32Bit RSTSTAT:1;             /**< \brief [1:1] Kernel Reset Status (rh) */
    Ifx_Strict_32Bit reserved_2:30;         /**< \brief \internal Reserved */
} Ifx_SMU_KRST0_Bits;

/** \brief  SMU Reset Register 1 */
typedef struct _Ifx_SMU_KRST1_Bits
{
    Ifx_Strict_32Bit RST:1;                 /**< \brief [0:0] Kernel Reset (rwh) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_SMU_KRST1_Bits;

/** \brief  SMU Reset Status Clear Register */
typedef struct _Ifx_SMU_KRSTCLR_Bits
{
    Ifx_Strict_32Bit CLR:1;                 /**< \brief [0:0] Kernel Reset Status Clear (w) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_SMU_KRSTCLR_Bits;

/** \brief  OCDS Control and Status */
typedef struct _Ifx_SMU_OCS_Bits
{
    Ifx_Strict_32Bit TGS:2;                 /**< \brief [1:0] Trigger Set for OTGB0/1 (rw) */
    Ifx_Strict_32Bit TGB:1;                 /**< \brief [2:2] OTGB0/1 Bus Select (rw) */
    Ifx_Strict_32Bit TG_P:1;                /**< \brief [3:3] TGS, TGB Write Protection (w) */
    Ifx_Strict_32Bit reserved_4:20;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit SUS:4;                 /**< \brief [27:24] OCDS Suspend Control (rw) */
    Ifx_Strict_32Bit SUS_P:1;               /**< \brief [28:28] SUS Write Protection (w) */
    Ifx_Strict_32Bit SUSSTA:1;              /**< \brief [29:29] Suspend State (rh) */
    Ifx_Strict_32Bit reserved_30:2;         /**< \brief \internal Reserved */
} Ifx_SMU_OCS_Bits;

/** \brief  Port Control */
typedef struct _Ifx_SMU_PCTL_Bits
{
    Ifx_Strict_32Bit HWDIR:1;               /**< \brief [0:0] Port Direction. (rw) */
    Ifx_Strict_32Bit HWEN:1;                /**< \brief [1:1] Port Enable. (rw) */
    Ifx_Strict_32Bit reserved_2:5;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PCS:1;                 /**< \brief [7:7] PAD Configuration Select (rw) */
    Ifx_Strict_32Bit reserved_8:8;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit PCFG:16;               /**< \brief [31:16] PAD Configuration (rh) */
} Ifx_SMU_PCTL_Bits;

/** \brief  Register Monitor Control */
typedef struct _Ifx_SMU_RMCTL_Bits
{
    Ifx_Strict_32Bit TE:1;                  /**< \brief [0:0] Test Enable. (rw) */
    Ifx_Strict_32Bit reserved_1:31;         /**< \brief \internal Reserved */
} Ifx_SMU_RMCTL_Bits;

/** \brief  Register Monitor Error Flags */
typedef struct _Ifx_SMU_RMEF_Bits
{
    Ifx_Strict_32Bit EF0:1;                 /**< \brief [0:0] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF1:1;                 /**< \brief [1:1] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF2:1;                 /**< \brief [2:2] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF3:1;                 /**< \brief [3:3] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF4:1;                 /**< \brief [4:4] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF5:1;                 /**< \brief [5:5] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF6:1;                 /**< \brief [6:6] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF7:1;                 /**< \brief [7:7] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF8:1;                 /**< \brief [8:8] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF9:1;                 /**< \brief [9:9] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF10:1;                /**< \brief [10:10] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF11:1;                /**< \brief [11:11] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF12:1;                /**< \brief [12:12] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF13:1;                /**< \brief [13:13] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF14:1;                /**< \brief [14:14] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF15:1;                /**< \brief [15:15] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF16:1;                /**< \brief [16:16] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF17:1;                /**< \brief [17:17] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF18:1;                /**< \brief [18:18] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF19:1;                /**< \brief [19:19] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF20:1;                /**< \brief [20:20] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF21:1;                /**< \brief [21:21] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF22:1;                /**< \brief [22:22] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF23:1;                /**< \brief [23:23] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF24:1;                /**< \brief [24:24] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF25:1;                /**< \brief [25:25] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF26:1;                /**< \brief [26:26] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF27:1;                /**< \brief [27:27] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF28:1;                /**< \brief [28:28] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF29:1;                /**< \brief [29:29] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF30:1;                /**< \brief [30:30] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit EF31:1;                /**< \brief [31:31] Status flag related to the different instances of the register monitor safety mechanism. (rwh) */
} Ifx_SMU_RMEF_Bits;

/** \brief  Register Monitor Self Test Status */
typedef struct _Ifx_SMU_RMSTS_Bits
{
    Ifx_Strict_32Bit STS0:1;                /**< \brief [0:0] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS1:1;                /**< \brief [1:1] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS2:1;                /**< \brief [2:2] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS3:1;                /**< \brief [3:3] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS4:1;                /**< \brief [4:4] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS5:1;                /**< \brief [5:5] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS6:1;                /**< \brief [6:6] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS7:1;                /**< \brief [7:7] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS8:1;                /**< \brief [8:8] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS9:1;                /**< \brief [9:9] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS10:1;               /**< \brief [10:10] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS11:1;               /**< \brief [11:11] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS12:1;               /**< \brief [12:12] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS13:1;               /**< \brief [13:13] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS14:1;               /**< \brief [14:14] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS15:1;               /**< \brief [15:15] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS16:1;               /**< \brief [16:16] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS17:1;               /**< \brief [17:17] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS18:1;               /**< \brief [18:18] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS19:1;               /**< \brief [19:19] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS20:1;               /**< \brief [20:20] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS21:1;               /**< \brief [21:21] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS22:1;               /**< \brief [22:22] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS23:1;               /**< \brief [23:23] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS24:1;               /**< \brief [24:24] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS25:1;               /**< \brief [25:25] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS26:1;               /**< \brief [26:26] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS27:1;               /**< \brief [27:27] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS28:1;               /**< \brief [28:28] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS29:1;               /**< \brief [29:29] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS30:1;               /**< \brief [30:30] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
    Ifx_Strict_32Bit STS31:1;               /**< \brief [31:31] Ready flag related to the different instances of the register monitor safety mechanism. (rwh) */
} Ifx_SMU_RMSTS_Bits;

/** \brief  Recovery Timer Alarm Configuration */
typedef struct _Ifx_SMU_RTAC0_Bits
{
    Ifx_Strict_32Bit GID0:3;                /**< \brief [2:0] Group Index 0. (rw) */
    Ifx_Strict_32Bit ALID0:5;               /**< \brief [7:3] Alarm Identifier 0. (rw) */
    Ifx_Strict_32Bit GID1:3;                /**< \brief [10:8] Group Index 1. (rw) */
    Ifx_Strict_32Bit ALID1:5;               /**< \brief [15:11] Alarm Identifier 1. (rw) */
    Ifx_Strict_32Bit GID2:3;                /**< \brief [18:16] Group Index 2. (rw) */
    Ifx_Strict_32Bit ALID2:5;               /**< \brief [23:19] Alarm Identifier 2. (rw) */
    Ifx_Strict_32Bit GID3:3;                /**< \brief [26:24] Group Index 3. (rw) */
    Ifx_Strict_32Bit ALID3:5;               /**< \brief [31:27] Alarm Identifier 3. (rw) */
} Ifx_SMU_RTAC0_Bits;

/** \brief  Recovery Timer Alarm Configuration */
typedef struct _Ifx_SMU_RTAC1_Bits
{
    Ifx_Strict_32Bit GID0:3;                /**< \brief [2:0] Group Index 0. (rw) */
    Ifx_Strict_32Bit ALID0:5;               /**< \brief [7:3] Alarm Identifier 0. (rw) */
    Ifx_Strict_32Bit GID1:3;                /**< \brief [10:8] Group Index 1. (rw) */
    Ifx_Strict_32Bit ALID1:5;               /**< \brief [15:11] Alarm Identifier 1. (rw) */
    Ifx_Strict_32Bit GID2:3;                /**< \brief [18:16] Group Index 2. (rw) */
    Ifx_Strict_32Bit ALID2:5;               /**< \brief [23:19] Alarm Identifier 2. (rw) */
    Ifx_Strict_32Bit GID3:3;                /**< \brief [26:24] Group Index 3. (rw) */
    Ifx_Strict_32Bit ALID3:5;               /**< \brief [31:27] Alarm Identifier 3. (rw) */
} Ifx_SMU_RTAC1_Bits;

/** \brief  Fault Signaling Protocol */
typedef struct _Ifx_SMU_RTC_Bits
{
    Ifx_Strict_32Bit RT0E:1;                /**< \brief [0:0] RT0 Enable Bit (rw) */
    Ifx_Strict_32Bit RT1E:1;                /**< \brief [1:1] RT1 Enable Bit (rw) */
    Ifx_Strict_32Bit reserved_2:6;          /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RTD:24;                /**< \brief [31:8] Recovery Timer Duration (rw) */
} Ifx_SMU_RTC_Bits;

/** \brief  Status Register */
typedef struct _Ifx_SMU_STS_Bits
{
    Ifx_Strict_32Bit CMD:4;                 /**< \brief [3:0] Last command received (rwh) */
    Ifx_Strict_32Bit ARG:4;                 /**< \brief [7:4] Last command argument received (rwh) */
    Ifx_Strict_32Bit RES:1;                 /**< \brief [8:8] Result of last received command (rwh) */
    Ifx_Strict_32Bit ASCE:1;                /**< \brief [9:9] Alarm Status Clear Enable (rwh) */
    Ifx_Strict_32Bit FSP:2;                 /**< \brief [11:10] Fault Signaling Protocol status (rh) */
    Ifx_Strict_32Bit FSTS:1;                /**< \brief [12:12] Fault State Timing Status (rwh) */
    Ifx_Strict_32Bit reserved_13:3;         /**< \brief \internal Reserved */
    Ifx_Strict_32Bit RTS0:1;                /**< \brief [16:16] Recovery Timer 0 Status (rwh) */
    Ifx_Strict_32Bit RTME0:1;               /**< \brief [17:17] Recovery Timer 0 Missed Event (rwh) */
    Ifx_Strict_32Bit RTS1:1;                /**< \brief [18:18] Recovery Timer 1 Status (rwh) */
    Ifx_Strict_32Bit RTME1:1;               /**< \brief [19:19] Recovery Timer 1 Missed Event (rwh) */
    Ifx_Strict_32Bit reserved_20:12;        /**< \brief \internal Reserved */
} Ifx_SMU_STS_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Smu_union
 * \{  */

/** \brief  SMU Access Enable Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_ACCEN0_Bits B;                  /**< \brief Bitfield access */
} Ifx_SMU_ACCEN0;

/** \brief  SMU Access Enable Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_ACCEN1_Bits B;                  /**< \brief Bitfield access */
} Ifx_SMU_ACCEN1;

/** \brief  Alarm Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_AD_Bits B;                      /**< \brief Bitfield access */
} Ifx_SMU_AD;

/** \brief  Alarm and Fault Counter */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_AFCNT_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_AFCNT;

/** \brief  Alarm Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_AG_Bits B;                      /**< \brief Bitfield access */
} Ifx_SMU_AG;

/** \brief  Alarm Global Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_AGC_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_AGC;

/** \brief  Alarm Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_AGCF_Bits B;                    /**< \brief Bitfield access */
} Ifx_SMU_AGCF;

/** \brief  FSP Configuration Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_AGFSP_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_AGFSP;

/** \brief  Clock Control Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_CLC_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_CLC;

/** \brief  Command Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_CMD_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_CMD;

/** \brief  Debug Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_DBG_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_DBG;

/** \brief  Fault Signaling Protocol */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_FSP_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_FSP;

/** \brief  Module Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_SMU_ID;

/** \brief  Key Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_KEYS_Bits B;                    /**< \brief Bitfield access */
} Ifx_SMU_KEYS;

/** \brief  SMU Reset Register 0 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_KRST0_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_KRST0;

/** \brief  SMU Reset Register 1 */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_KRST1_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_KRST1;

/** \brief  SMU Reset Status Clear Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_KRSTCLR_Bits B;                 /**< \brief Bitfield access */
} Ifx_SMU_KRSTCLR;

/** \brief  OCDS Control and Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_OCS_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_OCS;

/** \brief  Port Control */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_PCTL_Bits B;                    /**< \brief Bitfield access */
} Ifx_SMU_PCTL;

/** \brief  Register Monitor Control */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_RMCTL_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_RMCTL;

/** \brief  Register Monitor Error Flags */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_RMEF_Bits B;                    /**< \brief Bitfield access */
} Ifx_SMU_RMEF;

/** \brief  Register Monitor Self Test Status */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_RMSTS_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_RMSTS;

/** \brief  Recovery Timer Alarm Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_RTAC0_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_RTAC0;

/** \brief  Recovery Timer Alarm Configuration */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_RTAC1_Bits B;                   /**< \brief Bitfield access */
} Ifx_SMU_RTAC1;

/** \brief  Fault Signaling Protocol */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_RTC_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_RTC;

/** \brief  Status Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_SMU_STS_Bits B;                     /**< \brief Bitfield access */
} Ifx_SMU_STS;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Smu_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  SMU object */
typedef volatile struct _Ifx_SMU
{
    Ifx_SMU_CLC CLC;                        /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_SMU_ID ID;                          /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[20];           /**< \brief C, \internal Reserved */
    Ifx_SMU_CMD CMD;                        /**< \brief 20, Command Register */
    Ifx_SMU_STS STS;                        /**< \brief 24, Status Register */
    Ifx_SMU_FSP FSP;                        /**< \brief 28, Fault Signaling Protocol */
    Ifx_SMU_AGC AGC;                        /**< \brief 2C, Alarm Global Configuration */
    Ifx_SMU_RTC RTC;                        /**< \brief 30, Fault Signaling Protocol */
    Ifx_SMU_KEYS KEYS;                      /**< \brief 34, Key Register */
    Ifx_SMU_DBG DBG;                        /**< \brief 38, Debug Register */
    Ifx_SMU_PCTL PCTL;                      /**< \brief 3C, Port Control */
    Ifx_SMU_AFCNT AFCNT;                    /**< \brief 40, Alarm and Fault Counter */
    unsigned char reserved_44[28];          /**< \brief 44, \internal Reserved */
    Ifx_SMU_RTAC0 RTAC0;                    /**< \brief 60, Recovery Timer Alarm Configuration */
    Ifx_SMU_RTAC1 RTAC1;                    /**< \brief 64, Recovery Timer Alarm Configuration */
    unsigned char reserved_68[152];         /**< \brief 68, \internal Reserved */
    Ifx_SMU_AGCF AGCF[7][3];                /**< \brief 100, Alarm Configuration Register */
    unsigned char reserved_154[44];         /**< \brief 154, \internal Reserved */
    Ifx_SMU_AGFSP AGFSP[7];                 /**< \brief 180, FSP Configuration Register */
    unsigned char reserved_19C[36];         /**< \brief 19C, \internal Reserved */
    Ifx_SMU_AG AG[7];                       /**< \brief 1C0, Alarm Status Register */
    unsigned char reserved_1DC[36];         /**< \brief 1DC, \internal Reserved */
    Ifx_SMU_AD AD[7];                       /**< \brief 200, Alarm Status Register */
    unsigned char reserved_21C[228];        /**< \brief 21C, \internal Reserved */
    Ifx_SMU_RMCTL RMCTL;                    /**< \brief 300, Register Monitor Control */
    Ifx_SMU_RMEF RMEF;                      /**< \brief 304, Register Monitor Error Flags */
    Ifx_SMU_RMSTS RMSTS;                    /**< \brief 308, Register Monitor Self Test Status */
    unsigned char reserved_30C[1244];       /**< \brief 30C, \internal Reserved */
    Ifx_SMU_OCS OCS;                        /**< \brief 7E8, OCDS Control and Status */
    Ifx_SMU_KRSTCLR KRSTCLR;                /**< \brief 7EC, SMU Reset Status Clear Register */
    Ifx_SMU_KRST1 KRST1;                    /**< \brief 7F0, SMU Reset Register 1 */
    Ifx_SMU_KRST0 KRST0;                    /**< \brief 7F4, SMU Reset Register 0 */
    Ifx_SMU_ACCEN1 ACCEN1;                  /**< \brief 7F8, SMU Access Enable Register 1 */
    Ifx_SMU_ACCEN0 ACCEN0;                  /**< \brief 7FC, SMU Access Enable Register 0 */
} Ifx_SMU;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSMU_REGDEF_H */
