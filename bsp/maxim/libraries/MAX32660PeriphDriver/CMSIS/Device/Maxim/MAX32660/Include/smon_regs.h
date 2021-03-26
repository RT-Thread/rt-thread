/**
 * @file    smon_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the SMON Peripheral Module.
 */

/* ****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 *
 *************************************************************************** */

#ifndef _SMON_REGS_H_
#define _SMON_REGS_H_

/* **** Includes **** */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
 
#if defined (__ICCARM__)
  #pragma system_include
#endif
 
#if defined (__CC_ARM)
  #pragma anon_unions
#endif
/// @cond
/*
    If types are not defined elsewhere (CMSIS) define them here
*/
#ifndef __IO
#define __IO volatile
#endif
#ifndef __I
#define __I  volatile const
#endif
#ifndef __O
#define __O  volatile
#endif
#ifndef __R
#define __R  volatile const
#endif
/// @endcond

/* **** Definitions **** */

/**
 * @ingroup     smon
 * @defgroup    smon_registers SMON_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the SMON Peripheral Module.
 * @details The Security Monitor block used to monitor system threat conditions.
 */

/**
 * @ingroup smon_registers
 * Structure type to access the SMON Registers.
 */
typedef struct {
    __IO uint32_t extscn;               /**< <tt>\b 0x00:</tt> SMON EXTSCN Register */
    __IO uint32_t intscn;               /**< <tt>\b 0x04:</tt> SMON INTSCN Register */
    __IO uint32_t secalm;               /**< <tt>\b 0x08:</tt> SMON SECALM Register */
    __I  uint32_t secdiag;              /**< <tt>\b 0x0C:</tt> SMON SECDIAG Register */
    __I  uint32_t dlrtc;                /**< <tt>\b 0x10:</tt> SMON DLRTC Register */
    __R  uint32_t rsv_0x14_0x33[8];
    __I  uint32_t secst;                /**< <tt>\b 0x34:</tt> SMON SECST Register */
} mxc_smon_regs_t;

/* Register offsets for module SMON */
/**
 * @ingroup    smon_registers
 * @defgroup   SMON_Register_Offsets Register Offsets
 * @brief      SMON Peripheral Register Offsets from the SMON Base Peripheral Address. 
 * @{
 */
 #define MXC_R_SMON_EXTSCN                  ((uint32_t)0x00000000UL) /**< Offset from SMON Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_SMON_INTSCN                  ((uint32_t)0x00000004UL) /**< Offset from SMON Base Address: <tt> 0x0004</tt> */ 
 #define MXC_R_SMON_SECALM                  ((uint32_t)0x00000008UL) /**< Offset from SMON Base Address: <tt> 0x0008</tt> */ 
 #define MXC_R_SMON_SECDIAG                 ((uint32_t)0x0000000CUL) /**< Offset from SMON Base Address: <tt> 0x000C</tt> */ 
 #define MXC_R_SMON_DLRTC                   ((uint32_t)0x00000010UL) /**< Offset from SMON Base Address: <tt> 0x0010</tt> */ 
 #define MXC_R_SMON_SECST                   ((uint32_t)0x00000034UL) /**< Offset from SMON Base Address: <tt> 0x0034</tt> */ 
/**@} end of group smon_registers */

/**
 * @ingroup  smon_registers
 * @defgroup SMON_EXTSCN SMON_EXTSCN
 * @brief    External Sensor Control Register.
 * @{
 */
 #define MXC_F_SMON_EXTSCN_EXTS_EN0_POS                 0 /**< EXTSCN_EXTS_EN0 Position */
 #define MXC_F_SMON_EXTSCN_EXTS_EN0                     ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_EXTS_EN0_POS)) /**< EXTSCN_EXTS_EN0 Mask */
 #define MXC_V_SMON_EXTSCN_EXTS_EN0_DIS                 ((uint32_t)0x0UL) /**< EXTSCN_EXTS_EN0_DIS Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN0_DIS                 (MXC_V_SMON_EXTSCN_EXTS_EN0_DIS << MXC_F_SMON_EXTSCN_EXTS_EN0_POS) /**< EXTSCN_EXTS_EN0_DIS Setting */
 #define MXC_V_SMON_EXTSCN_EXTS_EN0_EN                  ((uint32_t)0x1UL) /**< EXTSCN_EXTS_EN0_EN Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN0_EN                  (MXC_V_SMON_EXTSCN_EXTS_EN0_EN << MXC_F_SMON_EXTSCN_EXTS_EN0_POS) /**< EXTSCN_EXTS_EN0_EN Setting */

 #define MXC_F_SMON_EXTSCN_EXTS_EN1_POS                 1 /**< EXTSCN_EXTS_EN1 Position */
 #define MXC_F_SMON_EXTSCN_EXTS_EN1                     ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_EXTS_EN1_POS)) /**< EXTSCN_EXTS_EN1 Mask */
 #define MXC_V_SMON_EXTSCN_EXTS_EN1_DIS                 ((uint32_t)0x0UL) /**< EXTSCN_EXTS_EN1_DIS Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN1_DIS                 (MXC_V_SMON_EXTSCN_EXTS_EN1_DIS << MXC_F_SMON_EXTSCN_EXTS_EN1_POS) /**< EXTSCN_EXTS_EN1_DIS Setting */
 #define MXC_V_SMON_EXTSCN_EXTS_EN1_EN                  ((uint32_t)0x1UL) /**< EXTSCN_EXTS_EN1_EN Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN1_EN                  (MXC_V_SMON_EXTSCN_EXTS_EN1_EN << MXC_F_SMON_EXTSCN_EXTS_EN1_POS) /**< EXTSCN_EXTS_EN1_EN Setting */

 #define MXC_F_SMON_EXTSCN_EXTS_EN2_POS                 2 /**< EXTSCN_EXTS_EN2 Position */
 #define MXC_F_SMON_EXTSCN_EXTS_EN2                     ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_EXTS_EN2_POS)) /**< EXTSCN_EXTS_EN2 Mask */
 #define MXC_V_SMON_EXTSCN_EXTS_EN2_DIS                 ((uint32_t)0x0UL) /**< EXTSCN_EXTS_EN2_DIS Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN2_DIS                 (MXC_V_SMON_EXTSCN_EXTS_EN2_DIS << MXC_F_SMON_EXTSCN_EXTS_EN2_POS) /**< EXTSCN_EXTS_EN2_DIS Setting */
 #define MXC_V_SMON_EXTSCN_EXTS_EN2_EN                  ((uint32_t)0x1UL) /**< EXTSCN_EXTS_EN2_EN Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN2_EN                  (MXC_V_SMON_EXTSCN_EXTS_EN2_EN << MXC_F_SMON_EXTSCN_EXTS_EN2_POS) /**< EXTSCN_EXTS_EN2_EN Setting */

 #define MXC_F_SMON_EXTSCN_EXTS_EN3_POS                 3 /**< EXTSCN_EXTS_EN3 Position */
 #define MXC_F_SMON_EXTSCN_EXTS_EN3                     ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_EXTS_EN3_POS)) /**< EXTSCN_EXTS_EN3 Mask */
 #define MXC_V_SMON_EXTSCN_EXTS_EN3_DIS                 ((uint32_t)0x0UL) /**< EXTSCN_EXTS_EN3_DIS Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN3_DIS                 (MXC_V_SMON_EXTSCN_EXTS_EN3_DIS << MXC_F_SMON_EXTSCN_EXTS_EN3_POS) /**< EXTSCN_EXTS_EN3_DIS Setting */
 #define MXC_V_SMON_EXTSCN_EXTS_EN3_EN                  ((uint32_t)0x1UL) /**< EXTSCN_EXTS_EN3_EN Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN3_EN                  (MXC_V_SMON_EXTSCN_EXTS_EN3_EN << MXC_F_SMON_EXTSCN_EXTS_EN3_POS) /**< EXTSCN_EXTS_EN3_EN Setting */

 #define MXC_F_SMON_EXTSCN_EXTS_EN4_POS                 4 /**< EXTSCN_EXTS_EN4 Position */
 #define MXC_F_SMON_EXTSCN_EXTS_EN4                     ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_EXTS_EN4_POS)) /**< EXTSCN_EXTS_EN4 Mask */
 #define MXC_V_SMON_EXTSCN_EXTS_EN4_DIS                 ((uint32_t)0x0UL) /**< EXTSCN_EXTS_EN4_DIS Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN4_DIS                 (MXC_V_SMON_EXTSCN_EXTS_EN4_DIS << MXC_F_SMON_EXTSCN_EXTS_EN4_POS) /**< EXTSCN_EXTS_EN4_DIS Setting */
 #define MXC_V_SMON_EXTSCN_EXTS_EN4_EN                  ((uint32_t)0x1UL) /**< EXTSCN_EXTS_EN4_EN Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN4_EN                  (MXC_V_SMON_EXTSCN_EXTS_EN4_EN << MXC_F_SMON_EXTSCN_EXTS_EN4_POS) /**< EXTSCN_EXTS_EN4_EN Setting */

 #define MXC_F_SMON_EXTSCN_EXTS_EN5_POS                 5 /**< EXTSCN_EXTS_EN5 Position */
 #define MXC_F_SMON_EXTSCN_EXTS_EN5                     ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_EXTS_EN5_POS)) /**< EXTSCN_EXTS_EN5 Mask */
 #define MXC_V_SMON_EXTSCN_EXTS_EN5_DIS                 ((uint32_t)0x0UL) /**< EXTSCN_EXTS_EN5_DIS Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN5_DIS                 (MXC_V_SMON_EXTSCN_EXTS_EN5_DIS << MXC_F_SMON_EXTSCN_EXTS_EN5_POS) /**< EXTSCN_EXTS_EN5_DIS Setting */
 #define MXC_V_SMON_EXTSCN_EXTS_EN5_EN                  ((uint32_t)0x1UL) /**< EXTSCN_EXTS_EN5_EN Value */
 #define MXC_S_SMON_EXTSCN_EXTS_EN5_EN                  (MXC_V_SMON_EXTSCN_EXTS_EN5_EN << MXC_F_SMON_EXTSCN_EXTS_EN5_POS) /**< EXTSCN_EXTS_EN5_EN Setting */

 #define MXC_F_SMON_EXTSCN_EXTCNT_POS                   16 /**< EXTSCN_EXTCNT Position */
 #define MXC_F_SMON_EXTSCN_EXTCNT                       ((uint32_t)(0x1FUL << MXC_F_SMON_EXTSCN_EXTCNT_POS)) /**< EXTSCN_EXTCNT Mask */

 #define MXC_F_SMON_EXTSCN_EXTFRQ_POS                   21 /**< EXTSCN_EXTFRQ Position */
 #define MXC_F_SMON_EXTSCN_EXTFRQ                       ((uint32_t)(0x7UL << MXC_F_SMON_EXTSCN_EXTFRQ_POS)) /**< EXTSCN_EXTFRQ Mask */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_FREQ2000HZ            ((uint32_t)0x0UL) /**< EXTSCN_EXTFRQ_FREQ2000HZ Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_FREQ2000HZ            (MXC_V_SMON_EXTSCN_EXTFRQ_FREQ2000HZ << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_FREQ2000HZ Setting */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_FREQ1000HZ            ((uint32_t)0x1UL) /**< EXTSCN_EXTFRQ_FREQ1000HZ Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_FREQ1000HZ            (MXC_V_SMON_EXTSCN_EXTFRQ_FREQ1000HZ << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_FREQ1000HZ Setting */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_FREQ500HZ             ((uint32_t)0x2UL) /**< EXTSCN_EXTFRQ_FREQ500HZ Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_FREQ500HZ             (MXC_V_SMON_EXTSCN_EXTFRQ_FREQ500HZ << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_FREQ500HZ Setting */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_FREQ250HZ             ((uint32_t)0x3UL) /**< EXTSCN_EXTFRQ_FREQ250HZ Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_FREQ250HZ             (MXC_V_SMON_EXTSCN_EXTFRQ_FREQ250HZ << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_FREQ250HZ Setting */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_FREQ125HZ             ((uint32_t)0x4UL) /**< EXTSCN_EXTFRQ_FREQ125HZ Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_FREQ125HZ             (MXC_V_SMON_EXTSCN_EXTFRQ_FREQ125HZ << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_FREQ125HZ Setting */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_FREQ63HZ              ((uint32_t)0x5UL) /**< EXTSCN_EXTFRQ_FREQ63HZ Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_FREQ63HZ              (MXC_V_SMON_EXTSCN_EXTFRQ_FREQ63HZ << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_FREQ63HZ Setting */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_FREQ31HZ              ((uint32_t)0x6UL) /**< EXTSCN_EXTFRQ_FREQ31HZ Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_FREQ31HZ              (MXC_V_SMON_EXTSCN_EXTFRQ_FREQ31HZ << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_FREQ31HZ Setting */
 #define MXC_V_SMON_EXTSCN_EXTFRQ_RFU                   ((uint32_t)0x7UL) /**< EXTSCN_EXTFRQ_RFU Value */
 #define MXC_S_SMON_EXTSCN_EXTFRQ_RFU                   (MXC_V_SMON_EXTSCN_EXTFRQ_RFU << MXC_F_SMON_EXTSCN_EXTFRQ_POS) /**< EXTSCN_EXTFRQ_RFU Setting */

 #define MXC_F_SMON_EXTSCN_DIVCLK_POS                   24 /**< EXTSCN_DIVCLK Position */
 #define MXC_F_SMON_EXTSCN_DIVCLK                       ((uint32_t)(0x7UL << MXC_F_SMON_EXTSCN_DIVCLK_POS)) /**< EXTSCN_DIVCLK Mask */
 #define MXC_V_SMON_EXTSCN_DIVCLK_DIV1                  ((uint32_t)0x0UL) /**< EXTSCN_DIVCLK_DIV1 Value */
 #define MXC_S_SMON_EXTSCN_DIVCLK_DIV1                  (MXC_V_SMON_EXTSCN_DIVCLK_DIV1 << MXC_F_SMON_EXTSCN_DIVCLK_POS) /**< EXTSCN_DIVCLK_DIV1 Setting */
 #define MXC_V_SMON_EXTSCN_DIVCLK_DIV2                  ((uint32_t)0x1UL) /**< EXTSCN_DIVCLK_DIV2 Value */
 #define MXC_S_SMON_EXTSCN_DIVCLK_DIV2                  (MXC_V_SMON_EXTSCN_DIVCLK_DIV2 << MXC_F_SMON_EXTSCN_DIVCLK_POS) /**< EXTSCN_DIVCLK_DIV2 Setting */
 #define MXC_V_SMON_EXTSCN_DIVCLK_DIV4                  ((uint32_t)0x2UL) /**< EXTSCN_DIVCLK_DIV4 Value */
 #define MXC_S_SMON_EXTSCN_DIVCLK_DIV4                  (MXC_V_SMON_EXTSCN_DIVCLK_DIV4 << MXC_F_SMON_EXTSCN_DIVCLK_POS) /**< EXTSCN_DIVCLK_DIV4 Setting */
 #define MXC_V_SMON_EXTSCN_DIVCLK_DIV8                  ((uint32_t)0x3UL) /**< EXTSCN_DIVCLK_DIV8 Value */
 #define MXC_S_SMON_EXTSCN_DIVCLK_DIV8                  (MXC_V_SMON_EXTSCN_DIVCLK_DIV8 << MXC_F_SMON_EXTSCN_DIVCLK_POS) /**< EXTSCN_DIVCLK_DIV8 Setting */
 #define MXC_V_SMON_EXTSCN_DIVCLK_DIV16                 ((uint32_t)0x4UL) /**< EXTSCN_DIVCLK_DIV16 Value */
 #define MXC_S_SMON_EXTSCN_DIVCLK_DIV16                 (MXC_V_SMON_EXTSCN_DIVCLK_DIV16 << MXC_F_SMON_EXTSCN_DIVCLK_POS) /**< EXTSCN_DIVCLK_DIV16 Setting */
 #define MXC_V_SMON_EXTSCN_DIVCLK_DIV32                 ((uint32_t)0x5UL) /**< EXTSCN_DIVCLK_DIV32 Value */
 #define MXC_S_SMON_EXTSCN_DIVCLK_DIV32                 (MXC_V_SMON_EXTSCN_DIVCLK_DIV32 << MXC_F_SMON_EXTSCN_DIVCLK_POS) /**< EXTSCN_DIVCLK_DIV32 Setting */
 #define MXC_V_SMON_EXTSCN_DIVCLK_DIV64                 ((uint32_t)0x6UL) /**< EXTSCN_DIVCLK_DIV64 Value */
 #define MXC_S_SMON_EXTSCN_DIVCLK_DIV64                 (MXC_V_SMON_EXTSCN_DIVCLK_DIV64 << MXC_F_SMON_EXTSCN_DIVCLK_POS) /**< EXTSCN_DIVCLK_DIV64 Setting */

 #define MXC_F_SMON_EXTSCN_BUSY_POS                     30 /**< EXTSCN_BUSY Position */
 #define MXC_F_SMON_EXTSCN_BUSY                         ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_BUSY_POS)) /**< EXTSCN_BUSY Mask */
 #define MXC_V_SMON_EXTSCN_BUSY_IDLE                    ((uint32_t)0x0UL) /**< EXTSCN_BUSY_IDLE Value */
 #define MXC_S_SMON_EXTSCN_BUSY_IDLE                    (MXC_V_SMON_EXTSCN_BUSY_IDLE << MXC_F_SMON_EXTSCN_BUSY_POS) /**< EXTSCN_BUSY_IDLE Setting */
 #define MXC_V_SMON_EXTSCN_BUSY_BUSY                    ((uint32_t)0x1UL) /**< EXTSCN_BUSY_BUSY Value */
 #define MXC_S_SMON_EXTSCN_BUSY_BUSY                    (MXC_V_SMON_EXTSCN_BUSY_BUSY << MXC_F_SMON_EXTSCN_BUSY_POS) /**< EXTSCN_BUSY_BUSY Setting */

 #define MXC_F_SMON_EXTSCN_LOCK_POS                     31 /**< EXTSCN_LOCK Position */
 #define MXC_F_SMON_EXTSCN_LOCK                         ((uint32_t)(0x1UL << MXC_F_SMON_EXTSCN_LOCK_POS)) /**< EXTSCN_LOCK Mask */
 #define MXC_V_SMON_EXTSCN_LOCK_UNLOCKED                ((uint32_t)0x0UL) /**< EXTSCN_LOCK_UNLOCKED Value */
 #define MXC_S_SMON_EXTSCN_LOCK_UNLOCKED                (MXC_V_SMON_EXTSCN_LOCK_UNLOCKED << MXC_F_SMON_EXTSCN_LOCK_POS) /**< EXTSCN_LOCK_UNLOCKED Setting */
 #define MXC_V_SMON_EXTSCN_LOCK_LOCKED                  ((uint32_t)0x1UL) /**< EXTSCN_LOCK_LOCKED Value */
 #define MXC_S_SMON_EXTSCN_LOCK_LOCKED                  (MXC_V_SMON_EXTSCN_LOCK_LOCKED << MXC_F_SMON_EXTSCN_LOCK_POS) /**< EXTSCN_LOCK_LOCKED Setting */

/**@} end of group SMON_EXTSCN_Register */

/**
 * @ingroup  smon_registers
 * @defgroup SMON_INTSCN SMON_INTSCN
 * @brief    Internal Sensor Control Register.
 * @{
 */
 #define MXC_F_SMON_INTSCN_SHIELD_EN_POS                0 /**< INTSCN_SHIELD_EN Position */
 #define MXC_F_SMON_INTSCN_SHIELD_EN                    ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_SHIELD_EN_POS)) /**< INTSCN_SHIELD_EN Mask */
 #define MXC_V_SMON_INTSCN_SHIELD_EN_DIS                ((uint32_t)0x0UL) /**< INTSCN_SHIELD_EN_DIS Value */
 #define MXC_S_SMON_INTSCN_SHIELD_EN_DIS                (MXC_V_SMON_INTSCN_SHIELD_EN_DIS << MXC_F_SMON_INTSCN_SHIELD_EN_POS) /**< INTSCN_SHIELD_EN_DIS Setting */
 #define MXC_V_SMON_INTSCN_SHIELD_EN_EN                 ((uint32_t)0x1UL) /**< INTSCN_SHIELD_EN_EN Value */
 #define MXC_S_SMON_INTSCN_SHIELD_EN_EN                 (MXC_V_SMON_INTSCN_SHIELD_EN_EN << MXC_F_SMON_INTSCN_SHIELD_EN_POS) /**< INTSCN_SHIELD_EN_EN Setting */

 #define MXC_F_SMON_INTSCN_TEMP_EN_POS                  1 /**< INTSCN_TEMP_EN Position */
 #define MXC_F_SMON_INTSCN_TEMP_EN                      ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_TEMP_EN_POS)) /**< INTSCN_TEMP_EN Mask */
 #define MXC_V_SMON_INTSCN_TEMP_EN_DIS                  ((uint32_t)0x0UL) /**< INTSCN_TEMP_EN_DIS Value */
 #define MXC_S_SMON_INTSCN_TEMP_EN_DIS                  (MXC_V_SMON_INTSCN_TEMP_EN_DIS << MXC_F_SMON_INTSCN_TEMP_EN_POS) /**< INTSCN_TEMP_EN_DIS Setting */
 #define MXC_V_SMON_INTSCN_TEMP_EN_EN                   ((uint32_t)0x1UL) /**< INTSCN_TEMP_EN_EN Value */
 #define MXC_S_SMON_INTSCN_TEMP_EN_EN                   (MXC_V_SMON_INTSCN_TEMP_EN_EN << MXC_F_SMON_INTSCN_TEMP_EN_POS) /**< INTSCN_TEMP_EN_EN Setting */

 #define MXC_F_SMON_INTSCN_VBAT_EN_POS                  2 /**< INTSCN_VBAT_EN Position */
 #define MXC_F_SMON_INTSCN_VBAT_EN                      ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_VBAT_EN_POS)) /**< INTSCN_VBAT_EN Mask */
 #define MXC_V_SMON_INTSCN_VBAT_EN_DIS                  ((uint32_t)0x0UL) /**< INTSCN_VBAT_EN_DIS Value */
 #define MXC_S_SMON_INTSCN_VBAT_EN_DIS                  (MXC_V_SMON_INTSCN_VBAT_EN_DIS << MXC_F_SMON_INTSCN_VBAT_EN_POS) /**< INTSCN_VBAT_EN_DIS Setting */
 #define MXC_V_SMON_INTSCN_VBAT_EN_EN                   ((uint32_t)0x1UL) /**< INTSCN_VBAT_EN_EN Value */
 #define MXC_S_SMON_INTSCN_VBAT_EN_EN                   (MXC_V_SMON_INTSCN_VBAT_EN_EN << MXC_F_SMON_INTSCN_VBAT_EN_POS) /**< INTSCN_VBAT_EN_EN Setting */

 #define MXC_F_SMON_INTSCN_LOTEMP_SEL_POS               16 /**< INTSCN_LOTEMP_SEL Position */
 #define MXC_F_SMON_INTSCN_LOTEMP_SEL                   ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_LOTEMP_SEL_POS)) /**< INTSCN_LOTEMP_SEL Mask */
 #define MXC_V_SMON_INTSCN_LOTEMP_SEL_NEG50C            ((uint32_t)0x0UL) /**< INTSCN_LOTEMP_SEL_NEG50C Value */
 #define MXC_S_SMON_INTSCN_LOTEMP_SEL_NEG50C            (MXC_V_SMON_INTSCN_LOTEMP_SEL_NEG50C << MXC_F_SMON_INTSCN_LOTEMP_SEL_POS) /**< INTSCN_LOTEMP_SEL_NEG50C Setting */
 #define MXC_V_SMON_INTSCN_LOTEMP_SEL_NEG30C            ((uint32_t)0x1UL) /**< INTSCN_LOTEMP_SEL_NEG30C Value */
 #define MXC_S_SMON_INTSCN_LOTEMP_SEL_NEG30C            (MXC_V_SMON_INTSCN_LOTEMP_SEL_NEG30C << MXC_F_SMON_INTSCN_LOTEMP_SEL_POS) /**< INTSCN_LOTEMP_SEL_NEG30C Setting */

 #define MXC_F_SMON_INTSCN_VCORELOEN_POS                18 /**< INTSCN_VCORELOEN Position */
 #define MXC_F_SMON_INTSCN_VCORELOEN                    ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_VCORELOEN_POS)) /**< INTSCN_VCORELOEN Mask */
 #define MXC_V_SMON_INTSCN_VCORELOEN_DIS                ((uint32_t)0x0UL) /**< INTSCN_VCORELOEN_DIS Value */
 #define MXC_S_SMON_INTSCN_VCORELOEN_DIS                (MXC_V_SMON_INTSCN_VCORELOEN_DIS << MXC_F_SMON_INTSCN_VCORELOEN_POS) /**< INTSCN_VCORELOEN_DIS Setting */
 #define MXC_V_SMON_INTSCN_VCORELOEN_EN                 ((uint32_t)0x1UL) /**< INTSCN_VCORELOEN_EN Value */
 #define MXC_S_SMON_INTSCN_VCORELOEN_EN                 (MXC_V_SMON_INTSCN_VCORELOEN_EN << MXC_F_SMON_INTSCN_VCORELOEN_POS) /**< INTSCN_VCORELOEN_EN Setting */

 #define MXC_F_SMON_INTSCN_VCOREHIEN_POS                19 /**< INTSCN_VCOREHIEN Position */
 #define MXC_F_SMON_INTSCN_VCOREHIEN                    ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_VCOREHIEN_POS)) /**< INTSCN_VCOREHIEN Mask */
 #define MXC_V_SMON_INTSCN_VCOREHIEN_DIS                ((uint32_t)0x0UL) /**< INTSCN_VCOREHIEN_DIS Value */
 #define MXC_S_SMON_INTSCN_VCOREHIEN_DIS                (MXC_V_SMON_INTSCN_VCOREHIEN_DIS << MXC_F_SMON_INTSCN_VCOREHIEN_POS) /**< INTSCN_VCOREHIEN_DIS Setting */
 #define MXC_V_SMON_INTSCN_VCOREHIEN_EN                 ((uint32_t)0x1UL) /**< INTSCN_VCOREHIEN_EN Value */
 #define MXC_S_SMON_INTSCN_VCOREHIEN_EN                 (MXC_V_SMON_INTSCN_VCOREHIEN_EN << MXC_F_SMON_INTSCN_VCOREHIEN_POS) /**< INTSCN_VCOREHIEN_EN Setting */

 #define MXC_F_SMON_INTSCN_VDDLOEN_POS                  20 /**< INTSCN_VDDLOEN Position */
 #define MXC_F_SMON_INTSCN_VDDLOEN                      ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_VDDLOEN_POS)) /**< INTSCN_VDDLOEN Mask */
 #define MXC_V_SMON_INTSCN_VDDLOEN_DIS                  ((uint32_t)0x0UL) /**< INTSCN_VDDLOEN_DIS Value */
 #define MXC_S_SMON_INTSCN_VDDLOEN_DIS                  (MXC_V_SMON_INTSCN_VDDLOEN_DIS << MXC_F_SMON_INTSCN_VDDLOEN_POS) /**< INTSCN_VDDLOEN_DIS Setting */
 #define MXC_V_SMON_INTSCN_VDDLOEN_EN                   ((uint32_t)0x1UL) /**< INTSCN_VDDLOEN_EN Value */
 #define MXC_S_SMON_INTSCN_VDDLOEN_EN                   (MXC_V_SMON_INTSCN_VDDLOEN_EN << MXC_F_SMON_INTSCN_VDDLOEN_POS) /**< INTSCN_VDDLOEN_EN Setting */

 #define MXC_F_SMON_INTSCN_VDDHIEN_POS                  21 /**< INTSCN_VDDHIEN Position */
 #define MXC_F_SMON_INTSCN_VDDHIEN                      ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_VDDHIEN_POS)) /**< INTSCN_VDDHIEN Mask */
 #define MXC_V_SMON_INTSCN_VDDHIEN_DIS                  ((uint32_t)0x0UL) /**< INTSCN_VDDHIEN_DIS Value */
 #define MXC_S_SMON_INTSCN_VDDHIEN_DIS                  (MXC_V_SMON_INTSCN_VDDHIEN_DIS << MXC_F_SMON_INTSCN_VDDHIEN_POS) /**< INTSCN_VDDHIEN_DIS Setting */
 #define MXC_V_SMON_INTSCN_VDDHIEN_EN                   ((uint32_t)0x1UL) /**< INTSCN_VDDHIEN_EN Value */
 #define MXC_S_SMON_INTSCN_VDDHIEN_EN                   (MXC_V_SMON_INTSCN_VDDHIEN_EN << MXC_F_SMON_INTSCN_VDDHIEN_POS) /**< INTSCN_VDDHIEN_EN Setting */

 #define MXC_F_SMON_INTSCN_VGLEN_POS                    22 /**< INTSCN_VGLEN Position */
 #define MXC_F_SMON_INTSCN_VGLEN                        ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_VGLEN_POS)) /**< INTSCN_VGLEN Mask */
 #define MXC_V_SMON_INTSCN_VGLEN_DIS                    ((uint32_t)0x0UL) /**< INTSCN_VGLEN_DIS Value */
 #define MXC_S_SMON_INTSCN_VGLEN_DIS                    (MXC_V_SMON_INTSCN_VGLEN_DIS << MXC_F_SMON_INTSCN_VGLEN_POS) /**< INTSCN_VGLEN_DIS Setting */
 #define MXC_V_SMON_INTSCN_VGLEN_EN                     ((uint32_t)0x1UL) /**< INTSCN_VGLEN_EN Value */
 #define MXC_S_SMON_INTSCN_VGLEN_EN                     (MXC_V_SMON_INTSCN_VGLEN_EN << MXC_F_SMON_INTSCN_VGLEN_POS) /**< INTSCN_VGLEN_EN Setting */

 #define MXC_F_SMON_INTSCN_LOCK_POS                     31 /**< INTSCN_LOCK Position */
 #define MXC_F_SMON_INTSCN_LOCK                         ((uint32_t)(0x1UL << MXC_F_SMON_INTSCN_LOCK_POS)) /**< INTSCN_LOCK Mask */
 #define MXC_V_SMON_INTSCN_LOCK_UNLOCKED                ((uint32_t)0x0UL) /**< INTSCN_LOCK_UNLOCKED Value */
 #define MXC_S_SMON_INTSCN_LOCK_UNLOCKED                (MXC_V_SMON_INTSCN_LOCK_UNLOCKED << MXC_F_SMON_INTSCN_LOCK_POS) /**< INTSCN_LOCK_UNLOCKED Setting */
 #define MXC_V_SMON_INTSCN_LOCK_LOCKED                  ((uint32_t)0x1UL) /**< INTSCN_LOCK_LOCKED Value */
 #define MXC_S_SMON_INTSCN_LOCK_LOCKED                  (MXC_V_SMON_INTSCN_LOCK_LOCKED << MXC_F_SMON_INTSCN_LOCK_POS) /**< INTSCN_LOCK_LOCKED Setting */

/**@} end of group SMON_INTSCN_Register */

/**
 * @ingroup  smon_registers
 * @defgroup SMON_SECALM SMON_SECALM
 * @brief    Security Alarm Register.
 * @{
 */
 #define MXC_F_SMON_SECALM_DRS_POS                      0 /**< SECALM_DRS Position */
 #define MXC_F_SMON_SECALM_DRS                          ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_DRS_POS)) /**< SECALM_DRS Mask */
 #define MXC_V_SMON_SECALM_DRS_COMPLETE                 ((uint32_t)0x0UL) /**< SECALM_DRS_COMPLETE Value */
 #define MXC_S_SMON_SECALM_DRS_COMPLETE                 (MXC_V_SMON_SECALM_DRS_COMPLETE << MXC_F_SMON_SECALM_DRS_POS) /**< SECALM_DRS_COMPLETE Setting */
 #define MXC_V_SMON_SECALM_DRS_START                    ((uint32_t)0x1UL) /**< SECALM_DRS_START Value */
 #define MXC_S_SMON_SECALM_DRS_START                    (MXC_V_SMON_SECALM_DRS_START << MXC_F_SMON_SECALM_DRS_POS) /**< SECALM_DRS_START Setting */

 #define MXC_F_SMON_SECALM_KEYWIPE_POS                  1 /**< SECALM_KEYWIPE Position */
 #define MXC_F_SMON_SECALM_KEYWIPE                      ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_KEYWIPE_POS)) /**< SECALM_KEYWIPE Mask */
 #define MXC_V_SMON_SECALM_KEYWIPE_COMPLETE             ((uint32_t)0x0UL) /**< SECALM_KEYWIPE_COMPLETE Value */
 #define MXC_S_SMON_SECALM_KEYWIPE_COMPLETE             (MXC_V_SMON_SECALM_KEYWIPE_COMPLETE << MXC_F_SMON_SECALM_KEYWIPE_POS) /**< SECALM_KEYWIPE_COMPLETE Setting */
 #define MXC_V_SMON_SECALM_KEYWIPE_START                ((uint32_t)0x1UL) /**< SECALM_KEYWIPE_START Value */
 #define MXC_S_SMON_SECALM_KEYWIPE_START                (MXC_V_SMON_SECALM_KEYWIPE_START << MXC_F_SMON_SECALM_KEYWIPE_POS) /**< SECALM_KEYWIPE_START Setting */

 #define MXC_F_SMON_SECALM_SHIELDF_POS                  2 /**< SECALM_SHIELDF Position */
 #define MXC_F_SMON_SECALM_SHIELDF                      ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_SHIELDF_POS)) /**< SECALM_SHIELDF Mask */
 #define MXC_V_SMON_SECALM_SHIELDF_NOEVENT              ((uint32_t)0x0UL) /**< SECALM_SHIELDF_NOEVENT Value */
 #define MXC_S_SMON_SECALM_SHIELDF_NOEVENT              (MXC_V_SMON_SECALM_SHIELDF_NOEVENT << MXC_F_SMON_SECALM_SHIELDF_POS) /**< SECALM_SHIELDF_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_SHIELDF_OCCURRED             ((uint32_t)0x1UL) /**< SECALM_SHIELDF_OCCURRED Value */
 #define MXC_S_SMON_SECALM_SHIELDF_OCCURRED             (MXC_V_SMON_SECALM_SHIELDF_OCCURRED << MXC_F_SMON_SECALM_SHIELDF_POS) /**< SECALM_SHIELDF_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_LOTEMP_POS                   3 /**< SECALM_LOTEMP Position */
 #define MXC_F_SMON_SECALM_LOTEMP                       ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_LOTEMP_POS)) /**< SECALM_LOTEMP Mask */
 #define MXC_V_SMON_SECALM_LOTEMP_NOEVENT               ((uint32_t)0x0UL) /**< SECALM_LOTEMP_NOEVENT Value */
 #define MXC_S_SMON_SECALM_LOTEMP_NOEVENT               (MXC_V_SMON_SECALM_LOTEMP_NOEVENT << MXC_F_SMON_SECALM_LOTEMP_POS) /**< SECALM_LOTEMP_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_LOTEMP_OCCURRED              ((uint32_t)0x1UL) /**< SECALM_LOTEMP_OCCURRED Value */
 #define MXC_S_SMON_SECALM_LOTEMP_OCCURRED              (MXC_V_SMON_SECALM_LOTEMP_OCCURRED << MXC_F_SMON_SECALM_LOTEMP_POS) /**< SECALM_LOTEMP_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_HITEMP_POS                   4 /**< SECALM_HITEMP Position */
 #define MXC_F_SMON_SECALM_HITEMP                       ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_HITEMP_POS)) /**< SECALM_HITEMP Mask */
 #define MXC_V_SMON_SECALM_HITEMP_NOEVENT               ((uint32_t)0x0UL) /**< SECALM_HITEMP_NOEVENT Value */
 #define MXC_S_SMON_SECALM_HITEMP_NOEVENT               (MXC_V_SMON_SECALM_HITEMP_NOEVENT << MXC_F_SMON_SECALM_HITEMP_POS) /**< SECALM_HITEMP_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_HITEMP_OCCURRED              ((uint32_t)0x1UL) /**< SECALM_HITEMP_OCCURRED Value */
 #define MXC_S_SMON_SECALM_HITEMP_OCCURRED              (MXC_V_SMON_SECALM_HITEMP_OCCURRED << MXC_F_SMON_SECALM_HITEMP_POS) /**< SECALM_HITEMP_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_BATLO_POS                    5 /**< SECALM_BATLO Position */
 #define MXC_F_SMON_SECALM_BATLO                        ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_BATLO_POS)) /**< SECALM_BATLO Mask */
 #define MXC_V_SMON_SECALM_BATLO_NOEVENT                ((uint32_t)0x0UL) /**< SECALM_BATLO_NOEVENT Value */
 #define MXC_S_SMON_SECALM_BATLO_NOEVENT                (MXC_V_SMON_SECALM_BATLO_NOEVENT << MXC_F_SMON_SECALM_BATLO_POS) /**< SECALM_BATLO_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_BATLO_OCCURRED               ((uint32_t)0x1UL) /**< SECALM_BATLO_OCCURRED Value */
 #define MXC_S_SMON_SECALM_BATLO_OCCURRED               (MXC_V_SMON_SECALM_BATLO_OCCURRED << MXC_F_SMON_SECALM_BATLO_POS) /**< SECALM_BATLO_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_BATHI_POS                    6 /**< SECALM_BATHI Position */
 #define MXC_F_SMON_SECALM_BATHI                        ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_BATHI_POS)) /**< SECALM_BATHI Mask */
 #define MXC_V_SMON_SECALM_BATHI_NOEVENT                ((uint32_t)0x0UL) /**< SECALM_BATHI_NOEVENT Value */
 #define MXC_S_SMON_SECALM_BATHI_NOEVENT                (MXC_V_SMON_SECALM_BATHI_NOEVENT << MXC_F_SMON_SECALM_BATHI_POS) /**< SECALM_BATHI_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_BATHI_OCCURRED               ((uint32_t)0x1UL) /**< SECALM_BATHI_OCCURRED Value */
 #define MXC_S_SMON_SECALM_BATHI_OCCURRED               (MXC_V_SMON_SECALM_BATHI_OCCURRED << MXC_F_SMON_SECALM_BATHI_POS) /**< SECALM_BATHI_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTF_POS                     7 /**< SECALM_EXTF Position */
 #define MXC_F_SMON_SECALM_EXTF                         ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTF_POS)) /**< SECALM_EXTF Mask */
 #define MXC_V_SMON_SECALM_EXTF_NOEVENT                 ((uint32_t)0x0UL) /**< SECALM_EXTF_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTF_NOEVENT                 (MXC_V_SMON_SECALM_EXTF_NOEVENT << MXC_F_SMON_SECALM_EXTF_POS) /**< SECALM_EXTF_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTF_OCCURRED                ((uint32_t)0x1UL) /**< SECALM_EXTF_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTF_OCCURRED                (MXC_V_SMON_SECALM_EXTF_OCCURRED << MXC_F_SMON_SECALM_EXTF_POS) /**< SECALM_EXTF_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_VDDLO_POS                    8 /**< SECALM_VDDLO Position */
 #define MXC_F_SMON_SECALM_VDDLO                        ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_VDDLO_POS)) /**< SECALM_VDDLO Mask */
 #define MXC_V_SMON_SECALM_VDDLO_NOEVENT                ((uint32_t)0x0UL) /**< SECALM_VDDLO_NOEVENT Value */
 #define MXC_S_SMON_SECALM_VDDLO_NOEVENT                (MXC_V_SMON_SECALM_VDDLO_NOEVENT << MXC_F_SMON_SECALM_VDDLO_POS) /**< SECALM_VDDLO_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_VDDLO_OCCURRED               ((uint32_t)0x1UL) /**< SECALM_VDDLO_OCCURRED Value */
 #define MXC_S_SMON_SECALM_VDDLO_OCCURRED               (MXC_V_SMON_SECALM_VDDLO_OCCURRED << MXC_F_SMON_SECALM_VDDLO_POS) /**< SECALM_VDDLO_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_VCORELO_POS                  9 /**< SECALM_VCORELO Position */
 #define MXC_F_SMON_SECALM_VCORELO                      ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_VCORELO_POS)) /**< SECALM_VCORELO Mask */
 #define MXC_V_SMON_SECALM_VCORELO_NOEVENT              ((uint32_t)0x0UL) /**< SECALM_VCORELO_NOEVENT Value */
 #define MXC_S_SMON_SECALM_VCORELO_NOEVENT              (MXC_V_SMON_SECALM_VCORELO_NOEVENT << MXC_F_SMON_SECALM_VCORELO_POS) /**< SECALM_VCORELO_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_VCORELO_OCCURRED             ((uint32_t)0x1UL) /**< SECALM_VCORELO_OCCURRED Value */
 #define MXC_S_SMON_SECALM_VCORELO_OCCURRED             (MXC_V_SMON_SECALM_VCORELO_OCCURRED << MXC_F_SMON_SECALM_VCORELO_POS) /**< SECALM_VCORELO_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_VCOREHI_POS                  10 /**< SECALM_VCOREHI Position */
 #define MXC_F_SMON_SECALM_VCOREHI                      ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_VCOREHI_POS)) /**< SECALM_VCOREHI Mask */
 #define MXC_V_SMON_SECALM_VCOREHI_NOEVENT              ((uint32_t)0x0UL) /**< SECALM_VCOREHI_NOEVENT Value */
 #define MXC_S_SMON_SECALM_VCOREHI_NOEVENT              (MXC_V_SMON_SECALM_VCOREHI_NOEVENT << MXC_F_SMON_SECALM_VCOREHI_POS) /**< SECALM_VCOREHI_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_VCOREHI_OCCURRED             ((uint32_t)0x1UL) /**< SECALM_VCOREHI_OCCURRED Value */
 #define MXC_S_SMON_SECALM_VCOREHI_OCCURRED             (MXC_V_SMON_SECALM_VCOREHI_OCCURRED << MXC_F_SMON_SECALM_VCOREHI_POS) /**< SECALM_VCOREHI_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_VDDHI_POS                    11 /**< SECALM_VDDHI Position */
 #define MXC_F_SMON_SECALM_VDDHI                        ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_VDDHI_POS)) /**< SECALM_VDDHI Mask */
 #define MXC_V_SMON_SECALM_VDDHI_NOEVENT                ((uint32_t)0x0UL) /**< SECALM_VDDHI_NOEVENT Value */
 #define MXC_S_SMON_SECALM_VDDHI_NOEVENT                (MXC_V_SMON_SECALM_VDDHI_NOEVENT << MXC_F_SMON_SECALM_VDDHI_POS) /**< SECALM_VDDHI_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_VDDHI_OCCURRED               ((uint32_t)0x1UL) /**< SECALM_VDDHI_OCCURRED Value */
 #define MXC_S_SMON_SECALM_VDDHI_OCCURRED               (MXC_V_SMON_SECALM_VDDHI_OCCURRED << MXC_F_SMON_SECALM_VDDHI_POS) /**< SECALM_VDDHI_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_VGL_POS                      12 /**< SECALM_VGL Position */
 #define MXC_F_SMON_SECALM_VGL                          ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_VGL_POS)) /**< SECALM_VGL Mask */
 #define MXC_V_SMON_SECALM_VGL_NOEVENT                  ((uint32_t)0x0UL) /**< SECALM_VGL_NOEVENT Value */
 #define MXC_S_SMON_SECALM_VGL_NOEVENT                  (MXC_V_SMON_SECALM_VGL_NOEVENT << MXC_F_SMON_SECALM_VGL_POS) /**< SECALM_VGL_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_VGL_OCCURRED                 ((uint32_t)0x1UL) /**< SECALM_VGL_OCCURRED Value */
 #define MXC_S_SMON_SECALM_VGL_OCCURRED                 (MXC_V_SMON_SECALM_VGL_OCCURRED << MXC_F_SMON_SECALM_VGL_POS) /**< SECALM_VGL_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSTAT0_POS                 16 /**< SECALM_EXTSTAT0 Position */
 #define MXC_F_SMON_SECALM_EXTSTAT0                     ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSTAT0_POS)) /**< SECALM_EXTSTAT0 Mask */
 #define MXC_V_SMON_SECALM_EXTSTAT0_NOEVENT             ((uint32_t)0x0UL) /**< SECALM_EXTSTAT0_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSTAT0_NOEVENT             (MXC_V_SMON_SECALM_EXTSTAT0_NOEVENT << MXC_F_SMON_SECALM_EXTSTAT0_POS) /**< SECALM_EXTSTAT0_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSTAT0_OCCURRED            ((uint32_t)0x1UL) /**< SECALM_EXTSTAT0_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSTAT0_OCCURRED            (MXC_V_SMON_SECALM_EXTSTAT0_OCCURRED << MXC_F_SMON_SECALM_EXTSTAT0_POS) /**< SECALM_EXTSTAT0_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSTAT1_POS                 17 /**< SECALM_EXTSTAT1 Position */
 #define MXC_F_SMON_SECALM_EXTSTAT1                     ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSTAT1_POS)) /**< SECALM_EXTSTAT1 Mask */
 #define MXC_V_SMON_SECALM_EXTSTAT1_NOEVENT             ((uint32_t)0x0UL) /**< SECALM_EXTSTAT1_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSTAT1_NOEVENT             (MXC_V_SMON_SECALM_EXTSTAT1_NOEVENT << MXC_F_SMON_SECALM_EXTSTAT1_POS) /**< SECALM_EXTSTAT1_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSTAT1_OCCURRED            ((uint32_t)0x1UL) /**< SECALM_EXTSTAT1_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSTAT1_OCCURRED            (MXC_V_SMON_SECALM_EXTSTAT1_OCCURRED << MXC_F_SMON_SECALM_EXTSTAT1_POS) /**< SECALM_EXTSTAT1_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSTAT2_POS                 18 /**< SECALM_EXTSTAT2 Position */
 #define MXC_F_SMON_SECALM_EXTSTAT2                     ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSTAT2_POS)) /**< SECALM_EXTSTAT2 Mask */
 #define MXC_V_SMON_SECALM_EXTSTAT2_NOEVENT             ((uint32_t)0x0UL) /**< SECALM_EXTSTAT2_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSTAT2_NOEVENT             (MXC_V_SMON_SECALM_EXTSTAT2_NOEVENT << MXC_F_SMON_SECALM_EXTSTAT2_POS) /**< SECALM_EXTSTAT2_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSTAT2_OCCURRED            ((uint32_t)0x1UL) /**< SECALM_EXTSTAT2_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSTAT2_OCCURRED            (MXC_V_SMON_SECALM_EXTSTAT2_OCCURRED << MXC_F_SMON_SECALM_EXTSTAT2_POS) /**< SECALM_EXTSTAT2_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSTAT3_POS                 19 /**< SECALM_EXTSTAT3 Position */
 #define MXC_F_SMON_SECALM_EXTSTAT3                     ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSTAT3_POS)) /**< SECALM_EXTSTAT3 Mask */
 #define MXC_V_SMON_SECALM_EXTSTAT3_NOEVENT             ((uint32_t)0x0UL) /**< SECALM_EXTSTAT3_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSTAT3_NOEVENT             (MXC_V_SMON_SECALM_EXTSTAT3_NOEVENT << MXC_F_SMON_SECALM_EXTSTAT3_POS) /**< SECALM_EXTSTAT3_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSTAT3_OCCURRED            ((uint32_t)0x1UL) /**< SECALM_EXTSTAT3_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSTAT3_OCCURRED            (MXC_V_SMON_SECALM_EXTSTAT3_OCCURRED << MXC_F_SMON_SECALM_EXTSTAT3_POS) /**< SECALM_EXTSTAT3_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSTAT4_POS                 20 /**< SECALM_EXTSTAT4 Position */
 #define MXC_F_SMON_SECALM_EXTSTAT4                     ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSTAT4_POS)) /**< SECALM_EXTSTAT4 Mask */
 #define MXC_V_SMON_SECALM_EXTSTAT4_NOEVENT             ((uint32_t)0x0UL) /**< SECALM_EXTSTAT4_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSTAT4_NOEVENT             (MXC_V_SMON_SECALM_EXTSTAT4_NOEVENT << MXC_F_SMON_SECALM_EXTSTAT4_POS) /**< SECALM_EXTSTAT4_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSTAT4_OCCURRED            ((uint32_t)0x1UL) /**< SECALM_EXTSTAT4_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSTAT4_OCCURRED            (MXC_V_SMON_SECALM_EXTSTAT4_OCCURRED << MXC_F_SMON_SECALM_EXTSTAT4_POS) /**< SECALM_EXTSTAT4_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSTAT5_POS                 21 /**< SECALM_EXTSTAT5 Position */
 #define MXC_F_SMON_SECALM_EXTSTAT5                     ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSTAT5_POS)) /**< SECALM_EXTSTAT5 Mask */
 #define MXC_V_SMON_SECALM_EXTSTAT5_NOEVENT             ((uint32_t)0x0UL) /**< SECALM_EXTSTAT5_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSTAT5_NOEVENT             (MXC_V_SMON_SECALM_EXTSTAT5_NOEVENT << MXC_F_SMON_SECALM_EXTSTAT5_POS) /**< SECALM_EXTSTAT5_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSTAT5_OCCURRED            ((uint32_t)0x1UL) /**< SECALM_EXTSTAT5_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSTAT5_OCCURRED            (MXC_V_SMON_SECALM_EXTSTAT5_OCCURRED << MXC_F_SMON_SECALM_EXTSTAT5_POS) /**< SECALM_EXTSTAT5_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSWARN0_POS                24 /**< SECALM_EXTSWARN0 Position */
 #define MXC_F_SMON_SECALM_EXTSWARN0                    ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSWARN0_POS)) /**< SECALM_EXTSWARN0 Mask */
 #define MXC_V_SMON_SECALM_EXTSWARN0_NOEVENT            ((uint32_t)0x0UL) /**< SECALM_EXTSWARN0_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSWARN0_NOEVENT            (MXC_V_SMON_SECALM_EXTSWARN0_NOEVENT << MXC_F_SMON_SECALM_EXTSWARN0_POS) /**< SECALM_EXTSWARN0_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSWARN0_OCCURRED           ((uint32_t)0x1UL) /**< SECALM_EXTSWARN0_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSWARN0_OCCURRED           (MXC_V_SMON_SECALM_EXTSWARN0_OCCURRED << MXC_F_SMON_SECALM_EXTSWARN0_POS) /**< SECALM_EXTSWARN0_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSWARN1_POS                25 /**< SECALM_EXTSWARN1 Position */
 #define MXC_F_SMON_SECALM_EXTSWARN1                    ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSWARN1_POS)) /**< SECALM_EXTSWARN1 Mask */
 #define MXC_V_SMON_SECALM_EXTSWARN1_NOEVENT            ((uint32_t)0x0UL) /**< SECALM_EXTSWARN1_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSWARN1_NOEVENT            (MXC_V_SMON_SECALM_EXTSWARN1_NOEVENT << MXC_F_SMON_SECALM_EXTSWARN1_POS) /**< SECALM_EXTSWARN1_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSWARN1_OCCURRED           ((uint32_t)0x1UL) /**< SECALM_EXTSWARN1_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSWARN1_OCCURRED           (MXC_V_SMON_SECALM_EXTSWARN1_OCCURRED << MXC_F_SMON_SECALM_EXTSWARN1_POS) /**< SECALM_EXTSWARN1_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSWARN2_POS                26 /**< SECALM_EXTSWARN2 Position */
 #define MXC_F_SMON_SECALM_EXTSWARN2                    ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSWARN2_POS)) /**< SECALM_EXTSWARN2 Mask */
 #define MXC_V_SMON_SECALM_EXTSWARN2_NOEVENT            ((uint32_t)0x0UL) /**< SECALM_EXTSWARN2_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSWARN2_NOEVENT            (MXC_V_SMON_SECALM_EXTSWARN2_NOEVENT << MXC_F_SMON_SECALM_EXTSWARN2_POS) /**< SECALM_EXTSWARN2_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSWARN2_OCCURRED           ((uint32_t)0x1UL) /**< SECALM_EXTSWARN2_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSWARN2_OCCURRED           (MXC_V_SMON_SECALM_EXTSWARN2_OCCURRED << MXC_F_SMON_SECALM_EXTSWARN2_POS) /**< SECALM_EXTSWARN2_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSWARN3_POS                27 /**< SECALM_EXTSWARN3 Position */
 #define MXC_F_SMON_SECALM_EXTSWARN3                    ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSWARN3_POS)) /**< SECALM_EXTSWARN3 Mask */
 #define MXC_V_SMON_SECALM_EXTSWARN3_NOEVENT            ((uint32_t)0x0UL) /**< SECALM_EXTSWARN3_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSWARN3_NOEVENT            (MXC_V_SMON_SECALM_EXTSWARN3_NOEVENT << MXC_F_SMON_SECALM_EXTSWARN3_POS) /**< SECALM_EXTSWARN3_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSWARN3_OCCURRED           ((uint32_t)0x1UL) /**< SECALM_EXTSWARN3_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSWARN3_OCCURRED           (MXC_V_SMON_SECALM_EXTSWARN3_OCCURRED << MXC_F_SMON_SECALM_EXTSWARN3_POS) /**< SECALM_EXTSWARN3_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSWARN4_POS                28 /**< SECALM_EXTSWARN4 Position */
 #define MXC_F_SMON_SECALM_EXTSWARN4                    ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSWARN4_POS)) /**< SECALM_EXTSWARN4 Mask */
 #define MXC_V_SMON_SECALM_EXTSWARN4_NOEVENT            ((uint32_t)0x0UL) /**< SECALM_EXTSWARN4_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSWARN4_NOEVENT            (MXC_V_SMON_SECALM_EXTSWARN4_NOEVENT << MXC_F_SMON_SECALM_EXTSWARN4_POS) /**< SECALM_EXTSWARN4_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSWARN4_OCCURRED           ((uint32_t)0x1UL) /**< SECALM_EXTSWARN4_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSWARN4_OCCURRED           (MXC_V_SMON_SECALM_EXTSWARN4_OCCURRED << MXC_F_SMON_SECALM_EXTSWARN4_POS) /**< SECALM_EXTSWARN4_OCCURRED Setting */

 #define MXC_F_SMON_SECALM_EXTSWARN5_POS                29 /**< SECALM_EXTSWARN5 Position */
 #define MXC_F_SMON_SECALM_EXTSWARN5                    ((uint32_t)(0x1UL << MXC_F_SMON_SECALM_EXTSWARN5_POS)) /**< SECALM_EXTSWARN5 Mask */
 #define MXC_V_SMON_SECALM_EXTSWARN5_NOEVENT            ((uint32_t)0x0UL) /**< SECALM_EXTSWARN5_NOEVENT Value */
 #define MXC_S_SMON_SECALM_EXTSWARN5_NOEVENT            (MXC_V_SMON_SECALM_EXTSWARN5_NOEVENT << MXC_F_SMON_SECALM_EXTSWARN5_POS) /**< SECALM_EXTSWARN5_NOEVENT Setting */
 #define MXC_V_SMON_SECALM_EXTSWARN5_OCCURRED           ((uint32_t)0x1UL) /**< SECALM_EXTSWARN5_OCCURRED Value */
 #define MXC_S_SMON_SECALM_EXTSWARN5_OCCURRED           (MXC_V_SMON_SECALM_EXTSWARN5_OCCURRED << MXC_F_SMON_SECALM_EXTSWARN5_POS) /**< SECALM_EXTSWARN5_OCCURRED Setting */

/**@} end of group SMON_SECALM_Register */

/**
 * @ingroup  smon_registers
 * @defgroup SMON_SECDIAG SMON_SECDIAG
 * @brief    Security Diagnostic Register.
 * @{
 */
 #define MXC_F_SMON_SECDIAG_BORF_POS                    0 /**< SECDIAG_BORF Position */
 #define MXC_F_SMON_SECDIAG_BORF                        ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_BORF_POS)) /**< SECDIAG_BORF Mask */
 #define MXC_V_SMON_SECDIAG_BORF_NOEVENT                ((uint32_t)0x0UL) /**< SECDIAG_BORF_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_BORF_NOEVENT                (MXC_V_SMON_SECDIAG_BORF_NOEVENT << MXC_F_SMON_SECDIAG_BORF_POS) /**< SECDIAG_BORF_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_BORF_OCCURRED               ((uint32_t)0x1UL) /**< SECDIAG_BORF_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_BORF_OCCURRED               (MXC_V_SMON_SECDIAG_BORF_OCCURRED << MXC_F_SMON_SECDIAG_BORF_POS) /**< SECDIAG_BORF_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_SHIELDF_POS                 2 /**< SECDIAG_SHIELDF Position */
 #define MXC_F_SMON_SECDIAG_SHIELDF                     ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_SHIELDF_POS)) /**< SECDIAG_SHIELDF Mask */
 #define MXC_V_SMON_SECDIAG_SHIELDF_NOEVENT             ((uint32_t)0x0UL) /**< SECDIAG_SHIELDF_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_SHIELDF_NOEVENT             (MXC_V_SMON_SECDIAG_SHIELDF_NOEVENT << MXC_F_SMON_SECDIAG_SHIELDF_POS) /**< SECDIAG_SHIELDF_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_SHIELDF_OCCURRED            ((uint32_t)0x1UL) /**< SECDIAG_SHIELDF_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_SHIELDF_OCCURRED            (MXC_V_SMON_SECDIAG_SHIELDF_OCCURRED << MXC_F_SMON_SECDIAG_SHIELDF_POS) /**< SECDIAG_SHIELDF_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_LOTEMP_POS                  3 /**< SECDIAG_LOTEMP Position */
 #define MXC_F_SMON_SECDIAG_LOTEMP                      ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_LOTEMP_POS)) /**< SECDIAG_LOTEMP Mask */
 #define MXC_V_SMON_SECDIAG_LOTEMP_NOEVENT              ((uint32_t)0x0UL) /**< SECDIAG_LOTEMP_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_LOTEMP_NOEVENT              (MXC_V_SMON_SECDIAG_LOTEMP_NOEVENT << MXC_F_SMON_SECDIAG_LOTEMP_POS) /**< SECDIAG_LOTEMP_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_LOTEMP_OCCURRED             ((uint32_t)0x1UL) /**< SECDIAG_LOTEMP_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_LOTEMP_OCCURRED             (MXC_V_SMON_SECDIAG_LOTEMP_OCCURRED << MXC_F_SMON_SECDIAG_LOTEMP_POS) /**< SECDIAG_LOTEMP_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_HITEMP_POS                  4 /**< SECDIAG_HITEMP Position */
 #define MXC_F_SMON_SECDIAG_HITEMP                      ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_HITEMP_POS)) /**< SECDIAG_HITEMP Mask */
 #define MXC_V_SMON_SECDIAG_HITEMP_NOEVENT              ((uint32_t)0x0UL) /**< SECDIAG_HITEMP_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_HITEMP_NOEVENT              (MXC_V_SMON_SECDIAG_HITEMP_NOEVENT << MXC_F_SMON_SECDIAG_HITEMP_POS) /**< SECDIAG_HITEMP_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_HITEMP_OCCURRED             ((uint32_t)0x1UL) /**< SECDIAG_HITEMP_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_HITEMP_OCCURRED             (MXC_V_SMON_SECDIAG_HITEMP_OCCURRED << MXC_F_SMON_SECDIAG_HITEMP_POS) /**< SECDIAG_HITEMP_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_BATLO_POS                   5 /**< SECDIAG_BATLO Position */
 #define MXC_F_SMON_SECDIAG_BATLO                       ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_BATLO_POS)) /**< SECDIAG_BATLO Mask */
 #define MXC_V_SMON_SECDIAG_BATLO_NOEVENT               ((uint32_t)0x0UL) /**< SECDIAG_BATLO_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_BATLO_NOEVENT               (MXC_V_SMON_SECDIAG_BATLO_NOEVENT << MXC_F_SMON_SECDIAG_BATLO_POS) /**< SECDIAG_BATLO_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_BATLO_OCCURRED              ((uint32_t)0x1UL) /**< SECDIAG_BATLO_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_BATLO_OCCURRED              (MXC_V_SMON_SECDIAG_BATLO_OCCURRED << MXC_F_SMON_SECDIAG_BATLO_POS) /**< SECDIAG_BATLO_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_BATHI_POS                   6 /**< SECDIAG_BATHI Position */
 #define MXC_F_SMON_SECDIAG_BATHI                       ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_BATHI_POS)) /**< SECDIAG_BATHI Mask */
 #define MXC_V_SMON_SECDIAG_BATHI_NOEVENT               ((uint32_t)0x0UL) /**< SECDIAG_BATHI_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_BATHI_NOEVENT               (MXC_V_SMON_SECDIAG_BATHI_NOEVENT << MXC_F_SMON_SECDIAG_BATHI_POS) /**< SECDIAG_BATHI_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_BATHI_OCCURRED              ((uint32_t)0x1UL) /**< SECDIAG_BATHI_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_BATHI_OCCURRED              (MXC_V_SMON_SECDIAG_BATHI_OCCURRED << MXC_F_SMON_SECDIAG_BATHI_POS) /**< SECDIAG_BATHI_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_DYNF_POS                    7 /**< SECDIAG_DYNF Position */
 #define MXC_F_SMON_SECDIAG_DYNF                        ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_DYNF_POS)) /**< SECDIAG_DYNF Mask */
 #define MXC_V_SMON_SECDIAG_DYNF_NOEVENT                ((uint32_t)0x0UL) /**< SECDIAG_DYNF_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_DYNF_NOEVENT                (MXC_V_SMON_SECDIAG_DYNF_NOEVENT << MXC_F_SMON_SECDIAG_DYNF_POS) /**< SECDIAG_DYNF_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_DYNF_OCCURRED               ((uint32_t)0x1UL) /**< SECDIAG_DYNF_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_DYNF_OCCURRED               (MXC_V_SMON_SECDIAG_DYNF_OCCURRED << MXC_F_SMON_SECDIAG_DYNF_POS) /**< SECDIAG_DYNF_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_AESKT_POS                   8 /**< SECDIAG_AESKT Position */
 #define MXC_F_SMON_SECDIAG_AESKT                       ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_AESKT_POS)) /**< SECDIAG_AESKT Mask */
 #define MXC_V_SMON_SECDIAG_AESKT_INCOMPLETE            ((uint32_t)0x0UL) /**< SECDIAG_AESKT_INCOMPLETE Value */
 #define MXC_S_SMON_SECDIAG_AESKT_INCOMPLETE            (MXC_V_SMON_SECDIAG_AESKT_INCOMPLETE << MXC_F_SMON_SECDIAG_AESKT_POS) /**< SECDIAG_AESKT_INCOMPLETE Setting */
 #define MXC_V_SMON_SECDIAG_AESKT_COMPLETE              ((uint32_t)0x1UL) /**< SECDIAG_AESKT_COMPLETE Value */
 #define MXC_S_SMON_SECDIAG_AESKT_COMPLETE              (MXC_V_SMON_SECDIAG_AESKT_COMPLETE << MXC_F_SMON_SECDIAG_AESKT_POS) /**< SECDIAG_AESKT_COMPLETE Setting */

 #define MXC_F_SMON_SECDIAG_EXTSTAT0_POS                16 /**< SECDIAG_EXTSTAT0 Position */
 #define MXC_F_SMON_SECDIAG_EXTSTAT0                    ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_EXTSTAT0_POS)) /**< SECDIAG_EXTSTAT0 Mask */
 #define MXC_V_SMON_SECDIAG_EXTSTAT0_NOEVENT            ((uint32_t)0x0UL) /**< SECDIAG_EXTSTAT0_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT0_NOEVENT            (MXC_V_SMON_SECDIAG_EXTSTAT0_NOEVENT << MXC_F_SMON_SECDIAG_EXTSTAT0_POS) /**< SECDIAG_EXTSTAT0_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_EXTSTAT0_OCCURRED           ((uint32_t)0x1UL) /**< SECDIAG_EXTSTAT0_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT0_OCCURRED           (MXC_V_SMON_SECDIAG_EXTSTAT0_OCCURRED << MXC_F_SMON_SECDIAG_EXTSTAT0_POS) /**< SECDIAG_EXTSTAT0_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_EXTSTAT1_POS                17 /**< SECDIAG_EXTSTAT1 Position */
 #define MXC_F_SMON_SECDIAG_EXTSTAT1                    ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_EXTSTAT1_POS)) /**< SECDIAG_EXTSTAT1 Mask */
 #define MXC_V_SMON_SECDIAG_EXTSTAT1_NOEVENT            ((uint32_t)0x0UL) /**< SECDIAG_EXTSTAT1_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT1_NOEVENT            (MXC_V_SMON_SECDIAG_EXTSTAT1_NOEVENT << MXC_F_SMON_SECDIAG_EXTSTAT1_POS) /**< SECDIAG_EXTSTAT1_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_EXTSTAT1_OCCURRED           ((uint32_t)0x1UL) /**< SECDIAG_EXTSTAT1_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT1_OCCURRED           (MXC_V_SMON_SECDIAG_EXTSTAT1_OCCURRED << MXC_F_SMON_SECDIAG_EXTSTAT1_POS) /**< SECDIAG_EXTSTAT1_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_EXTSTAT2_POS                18 /**< SECDIAG_EXTSTAT2 Position */
 #define MXC_F_SMON_SECDIAG_EXTSTAT2                    ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_EXTSTAT2_POS)) /**< SECDIAG_EXTSTAT2 Mask */
 #define MXC_V_SMON_SECDIAG_EXTSTAT2_NOEVENT            ((uint32_t)0x0UL) /**< SECDIAG_EXTSTAT2_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT2_NOEVENT            (MXC_V_SMON_SECDIAG_EXTSTAT2_NOEVENT << MXC_F_SMON_SECDIAG_EXTSTAT2_POS) /**< SECDIAG_EXTSTAT2_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_EXTSTAT2_OCCURRED           ((uint32_t)0x1UL) /**< SECDIAG_EXTSTAT2_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT2_OCCURRED           (MXC_V_SMON_SECDIAG_EXTSTAT2_OCCURRED << MXC_F_SMON_SECDIAG_EXTSTAT2_POS) /**< SECDIAG_EXTSTAT2_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_EXTSTAT3_POS                19 /**< SECDIAG_EXTSTAT3 Position */
 #define MXC_F_SMON_SECDIAG_EXTSTAT3                    ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_EXTSTAT3_POS)) /**< SECDIAG_EXTSTAT3 Mask */
 #define MXC_V_SMON_SECDIAG_EXTSTAT3_NOEVENT            ((uint32_t)0x0UL) /**< SECDIAG_EXTSTAT3_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT3_NOEVENT            (MXC_V_SMON_SECDIAG_EXTSTAT3_NOEVENT << MXC_F_SMON_SECDIAG_EXTSTAT3_POS) /**< SECDIAG_EXTSTAT3_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_EXTSTAT3_OCCURRED           ((uint32_t)0x1UL) /**< SECDIAG_EXTSTAT3_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT3_OCCURRED           (MXC_V_SMON_SECDIAG_EXTSTAT3_OCCURRED << MXC_F_SMON_SECDIAG_EXTSTAT3_POS) /**< SECDIAG_EXTSTAT3_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_EXTSTAT4_POS                20 /**< SECDIAG_EXTSTAT4 Position */
 #define MXC_F_SMON_SECDIAG_EXTSTAT4                    ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_EXTSTAT4_POS)) /**< SECDIAG_EXTSTAT4 Mask */
 #define MXC_V_SMON_SECDIAG_EXTSTAT4_NOEVENT            ((uint32_t)0x0UL) /**< SECDIAG_EXTSTAT4_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT4_NOEVENT            (MXC_V_SMON_SECDIAG_EXTSTAT4_NOEVENT << MXC_F_SMON_SECDIAG_EXTSTAT4_POS) /**< SECDIAG_EXTSTAT4_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_EXTSTAT4_OCCURRED           ((uint32_t)0x1UL) /**< SECDIAG_EXTSTAT4_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT4_OCCURRED           (MXC_V_SMON_SECDIAG_EXTSTAT4_OCCURRED << MXC_F_SMON_SECDIAG_EXTSTAT4_POS) /**< SECDIAG_EXTSTAT4_OCCURRED Setting */

 #define MXC_F_SMON_SECDIAG_EXTSTAT5_POS                21 /**< SECDIAG_EXTSTAT5 Position */
 #define MXC_F_SMON_SECDIAG_EXTSTAT5                    ((uint32_t)(0x1UL << MXC_F_SMON_SECDIAG_EXTSTAT5_POS)) /**< SECDIAG_EXTSTAT5 Mask */
 #define MXC_V_SMON_SECDIAG_EXTSTAT5_NOEVENT            ((uint32_t)0x0UL) /**< SECDIAG_EXTSTAT5_NOEVENT Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT5_NOEVENT            (MXC_V_SMON_SECDIAG_EXTSTAT5_NOEVENT << MXC_F_SMON_SECDIAG_EXTSTAT5_POS) /**< SECDIAG_EXTSTAT5_NOEVENT Setting */
 #define MXC_V_SMON_SECDIAG_EXTSTAT5_OCCURRED           ((uint32_t)0x1UL) /**< SECDIAG_EXTSTAT5_OCCURRED Value */
 #define MXC_S_SMON_SECDIAG_EXTSTAT5_OCCURRED           (MXC_V_SMON_SECDIAG_EXTSTAT5_OCCURRED << MXC_F_SMON_SECDIAG_EXTSTAT5_POS) /**< SECDIAG_EXTSTAT5_OCCURRED Setting */

/**@} end of group SMON_SECDIAG_Register */

/**
 * @ingroup  smon_registers
 * @defgroup SMON_DLRTC SMON_DLRTC
 * @brief    DRS Log RTC Value. This register contains the 32 bit value in the RTC second
 *           register when the last DRS event occurred.
 * @{
 */
 #define MXC_F_SMON_DLRTC_DLRTC_POS                     0 /**< DLRTC_DLRTC Position */
 #define MXC_F_SMON_DLRTC_DLRTC                         ((uint32_t)(0xFFFFFFFFUL << MXC_F_SMON_DLRTC_DLRTC_POS)) /**< DLRTC_DLRTC Mask */

/**@} end of group SMON_DLRTC_Register */

/**
 * @ingroup  smon_registers
 * @defgroup SMON_SECST SMON_SECST
 * @brief    Security Monitor Status Register.
 * @{
 */
 #define MXC_F_SMON_SECST_EXTSRS_POS                    0 /**< SECST_EXTSRS Position */
 #define MXC_F_SMON_SECST_EXTSRS                        ((uint32_t)(0x1UL << MXC_F_SMON_SECST_EXTSRS_POS)) /**< SECST_EXTSRS Mask */
 #define MXC_V_SMON_SECST_EXTSRS_ALLOWED                ((uint32_t)0x0UL) /**< SECST_EXTSRS_ALLOWED Value */
 #define MXC_S_SMON_SECST_EXTSRS_ALLOWED                (MXC_V_SMON_SECST_EXTSRS_ALLOWED << MXC_F_SMON_SECST_EXTSRS_POS) /**< SECST_EXTSRS_ALLOWED Setting */
 #define MXC_V_SMON_SECST_EXTSRS_NOTALLOWED             ((uint32_t)0x1UL) /**< SECST_EXTSRS_NOTALLOWED Value */
 #define MXC_S_SMON_SECST_EXTSRS_NOTALLOWED             (MXC_V_SMON_SECST_EXTSRS_NOTALLOWED << MXC_F_SMON_SECST_EXTSRS_POS) /**< SECST_EXTSRS_NOTALLOWED Setting */

 #define MXC_F_SMON_SECST_INTSRS_POS                    1 /**< SECST_INTSRS Position */
 #define MXC_F_SMON_SECST_INTSRS                        ((uint32_t)(0x1UL << MXC_F_SMON_SECST_INTSRS_POS)) /**< SECST_INTSRS Mask */
 #define MXC_V_SMON_SECST_INTSRS_ALLOWED                ((uint32_t)0x0UL) /**< SECST_INTSRS_ALLOWED Value */
 #define MXC_S_SMON_SECST_INTSRS_ALLOWED                (MXC_V_SMON_SECST_INTSRS_ALLOWED << MXC_F_SMON_SECST_INTSRS_POS) /**< SECST_INTSRS_ALLOWED Setting */
 #define MXC_V_SMON_SECST_INTSRS_NOTALLOWED             ((uint32_t)0x1UL) /**< SECST_INTSRS_NOTALLOWED Value */
 #define MXC_S_SMON_SECST_INTSRS_NOTALLOWED             (MXC_V_SMON_SECST_INTSRS_NOTALLOWED << MXC_F_SMON_SECST_INTSRS_POS) /**< SECST_INTSRS_NOTALLOWED Setting */

 #define MXC_F_SMON_SECST_SECALRS_POS                   2 /**< SECST_SECALRS Position */
 #define MXC_F_SMON_SECST_SECALRS                       ((uint32_t)(0x1UL << MXC_F_SMON_SECST_SECALRS_POS)) /**< SECST_SECALRS Mask */
 #define MXC_V_SMON_SECST_SECALRS_ALLOWED               ((uint32_t)0x0UL) /**< SECST_SECALRS_ALLOWED Value */
 #define MXC_S_SMON_SECST_SECALRS_ALLOWED               (MXC_V_SMON_SECST_SECALRS_ALLOWED << MXC_F_SMON_SECST_SECALRS_POS) /**< SECST_SECALRS_ALLOWED Setting */
 #define MXC_V_SMON_SECST_SECALRS_NOTALLOWED            ((uint32_t)0x1UL) /**< SECST_SECALRS_NOTALLOWED Value */
 #define MXC_S_SMON_SECST_SECALRS_NOTALLOWED            (MXC_V_SMON_SECST_SECALRS_NOTALLOWED << MXC_F_SMON_SECST_SECALRS_POS) /**< SECST_SECALRS_NOTALLOWED Setting */

/**@} end of group SMON_SECST_Register */

#ifdef __cplusplus
}
#endif

#endif /* _SMON_REGS_H_ */
