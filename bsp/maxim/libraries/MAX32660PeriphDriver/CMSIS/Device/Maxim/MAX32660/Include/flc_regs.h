/**
 * @file    flc_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the FLC Peripheral Module.
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

#ifndef _FLC_REGS_H_
#define _FLC_REGS_H_

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
 * @ingroup     flc
 * @defgroup    flc_registers FLC_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the FLC Peripheral Module.
 * @details Flash Memory Control.
 */

/**
 * @ingroup flc_registers
 * Structure type to access the FLC Registers.
 */
typedef struct {
    __IO uint32_t addr;                 /**< <tt>\b 0x00:</tt> FLC ADDR Register */
    __IO uint32_t clkdiv;               /**< <tt>\b 0x04:</tt> FLC CLKDIV Register */
    __IO uint32_t cn;                   /**< <tt>\b 0x08:</tt> FLC CN Register */
    __R  uint32_t rsv_0xc_0x23[6];
    __IO uint32_t intr;                 /**< <tt>\b 0x024:</tt> FLC INTR Register */
    __R  uint32_t rsv_0x28_0x2f[2];
    __IO uint32_t data[4];              /**< <tt>\b 0x30:</tt> FLC DATA Register */
    __O  uint32_t acntl;                /**< <tt>\b 0x40:</tt> FLC ACNTL Register */
} mxc_flc_regs_t;

/* Register offsets for module FLC */
/**
 * @ingroup    flc_registers
 * @defgroup   FLC_Register_Offsets Register Offsets
 * @brief      FLC Peripheral Register Offsets from the FLC Base Peripheral Address. 
 * @{
 */
 #define MXC_R_FLC_ADDR                     ((uint32_t)0x00000000UL) /**< Offset from FLC Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_FLC_CLKDIV                   ((uint32_t)0x00000004UL) /**< Offset from FLC Base Address: <tt> 0x0004</tt> */ 
 #define MXC_R_FLC_CN                       ((uint32_t)0x00000008UL) /**< Offset from FLC Base Address: <tt> 0x0008</tt> */ 
 #define MXC_R_FLC_INTR                     ((uint32_t)0x00000024UL) /**< Offset from FLC Base Address: <tt> 0x0024</tt> */ 
 #define MXC_R_FLC_DATA                     ((uint32_t)0x00000030UL) /**< Offset from FLC Base Address: <tt> 0x0030</tt> */ 
 #define MXC_R_FLC_ACNTL                    ((uint32_t)0x00000040UL) /**< Offset from FLC Base Address: <tt> 0x0040</tt> */ 
/**@} end of group flc_registers */

/**
 * @ingroup  flc_registers
 * @defgroup FLC_ADDR FLC_ADDR
 * @brief    Flash Write Address.
 * @{
 */
 #define MXC_F_FLC_ADDR_ADDR_POS                        0 /**< ADDR_ADDR Position */
 #define MXC_F_FLC_ADDR_ADDR                            ((uint32_t)(0xFFFFFFFFUL << MXC_F_FLC_ADDR_ADDR_POS)) /**< ADDR_ADDR Mask */

/**@} end of group FLC_ADDR_Register */

/**
 * @ingroup  flc_registers
 * @defgroup FLC_CLKDIV FLC_CLKDIV
 * @brief    Flash Clock Divide. The clock (PLL0) is divided by this value to generate a 1
 *           MHz clock for Flash controller.
 * @{
 */
 #define MXC_F_FLC_CLKDIV_CLKDIV_POS                    0 /**< CLKDIV_CLKDIV Position */
 #define MXC_F_FLC_CLKDIV_CLKDIV                        ((uint32_t)(0xFFUL << MXC_F_FLC_CLKDIV_CLKDIV_POS)) /**< CLKDIV_CLKDIV Mask */

/**@} end of group FLC_CLKDIV_Register */

/**
 * @ingroup  flc_registers
 * @defgroup FLC_CN FLC_CN
 * @brief    Flash Control Register.
 * @{
 */
 #define MXC_F_FLC_CN_WR_POS                            0 /**< CN_WR Position */
 #define MXC_F_FLC_CN_WR                                ((uint32_t)(0x1UL << MXC_F_FLC_CN_WR_POS)) /**< CN_WR Mask */
 #define MXC_V_FLC_CN_WR_COMPLETE                       ((uint32_t)0x0UL) /**< CN_WR_COMPLETE Value */
 #define MXC_S_FLC_CN_WR_COMPLETE                       (MXC_V_FLC_CN_WR_COMPLETE << MXC_F_FLC_CN_WR_POS) /**< CN_WR_COMPLETE Setting */
 #define MXC_V_FLC_CN_WR_START                          ((uint32_t)0x1UL) /**< CN_WR_START Value */
 #define MXC_S_FLC_CN_WR_START                          (MXC_V_FLC_CN_WR_START << MXC_F_FLC_CN_WR_POS) /**< CN_WR_START Setting */

 #define MXC_F_FLC_CN_ME_POS                            1 /**< CN_ME Position */
 #define MXC_F_FLC_CN_ME                                ((uint32_t)(0x1UL << MXC_F_FLC_CN_ME_POS)) /**< CN_ME Mask */

 #define MXC_F_FLC_CN_PGE_POS                           2 /**< CN_PGE Position */
 #define MXC_F_FLC_CN_PGE                               ((uint32_t)(0x1UL << MXC_F_FLC_CN_PGE_POS)) /**< CN_PGE Mask */

 #define MXC_F_FLC_CN_WDTH_POS                          4 /**< CN_WDTH Position */
 #define MXC_F_FLC_CN_WDTH                              ((uint32_t)(0x1UL << MXC_F_FLC_CN_WDTH_POS)) /**< CN_WDTH Mask */
 #define MXC_V_FLC_CN_WDTH_SIZE128                      ((uint32_t)0x0UL) /**< CN_WDTH_SIZE128 Value */
 #define MXC_S_FLC_CN_WDTH_SIZE128                      (MXC_V_FLC_CN_WDTH_SIZE128 << MXC_F_FLC_CN_WDTH_POS) /**< CN_WDTH_SIZE128 Setting */
 #define MXC_V_FLC_CN_WDTH_SIZE32                       ((uint32_t)0x1UL) /**< CN_WDTH_SIZE32 Value */
 #define MXC_S_FLC_CN_WDTH_SIZE32                       (MXC_V_FLC_CN_WDTH_SIZE32 << MXC_F_FLC_CN_WDTH_POS) /**< CN_WDTH_SIZE32 Setting */

 #define MXC_F_FLC_CN_ERASE_CODE_POS                    8 /**< CN_ERASE_CODE Position */
 #define MXC_F_FLC_CN_ERASE_CODE                        ((uint32_t)(0xFFUL << MXC_F_FLC_CN_ERASE_CODE_POS)) /**< CN_ERASE_CODE Mask */
 #define MXC_V_FLC_CN_ERASE_CODE_NOP                    ((uint32_t)0x0UL) /**< CN_ERASE_CODE_NOP Value */
 #define MXC_S_FLC_CN_ERASE_CODE_NOP                    (MXC_V_FLC_CN_ERASE_CODE_NOP << MXC_F_FLC_CN_ERASE_CODE_POS) /**< CN_ERASE_CODE_NOP Setting */
 #define MXC_V_FLC_CN_ERASE_CODE_ERASEPAGE              ((uint32_t)0x55UL) /**< CN_ERASE_CODE_ERASEPAGE Value */
 #define MXC_S_FLC_CN_ERASE_CODE_ERASEPAGE              (MXC_V_FLC_CN_ERASE_CODE_ERASEPAGE << MXC_F_FLC_CN_ERASE_CODE_POS) /**< CN_ERASE_CODE_ERASEPAGE Setting */
 #define MXC_V_FLC_CN_ERASE_CODE_ERASEALL               ((uint32_t)0xAAUL) /**< CN_ERASE_CODE_ERASEALL Value */
 #define MXC_S_FLC_CN_ERASE_CODE_ERASEALL               (MXC_V_FLC_CN_ERASE_CODE_ERASEALL << MXC_F_FLC_CN_ERASE_CODE_POS) /**< CN_ERASE_CODE_ERASEALL Setting */

 #define MXC_F_FLC_CN_PEND_POS                          24 /**< CN_PEND Position */
 #define MXC_F_FLC_CN_PEND                              ((uint32_t)(0x1UL << MXC_F_FLC_CN_PEND_POS)) /**< CN_PEND Mask */
 #define MXC_V_FLC_CN_PEND_IDLE                         ((uint32_t)0x0UL) /**< CN_PEND_IDLE Value */
 #define MXC_S_FLC_CN_PEND_IDLE                         (MXC_V_FLC_CN_PEND_IDLE << MXC_F_FLC_CN_PEND_POS) /**< CN_PEND_IDLE Setting */
 #define MXC_V_FLC_CN_PEND_BUSY                         ((uint32_t)0x1UL) /**< CN_PEND_BUSY Value */
 #define MXC_S_FLC_CN_PEND_BUSY                         (MXC_V_FLC_CN_PEND_BUSY << MXC_F_FLC_CN_PEND_POS) /**< CN_PEND_BUSY Setting */

 #define MXC_F_FLC_CN_LVE_POS                           25 /**< CN_LVE Position */
 #define MXC_F_FLC_CN_LVE                               ((uint32_t)(0x1UL << MXC_F_FLC_CN_LVE_POS)) /**< CN_LVE Mask */
 #define MXC_V_FLC_CN_LVE_DIS                           ((uint32_t)0x0UL) /**< CN_LVE_DIS Value */
 #define MXC_S_FLC_CN_LVE_DIS                           (MXC_V_FLC_CN_LVE_DIS << MXC_F_FLC_CN_LVE_POS) /**< CN_LVE_DIS Setting */
 #define MXC_V_FLC_CN_LVE_EN                            ((uint32_t)0x1UL) /**< CN_LVE_EN Value */
 #define MXC_S_FLC_CN_LVE_EN                            (MXC_V_FLC_CN_LVE_EN << MXC_F_FLC_CN_LVE_POS) /**< CN_LVE_EN Setting */

 #define MXC_F_FLC_CN_BRST_POS                          27 /**< CN_BRST Position */
 #define MXC_F_FLC_CN_BRST                              ((uint32_t)(0x1UL << MXC_F_FLC_CN_BRST_POS)) /**< CN_BRST Mask */
 #define MXC_V_FLC_CN_BRST_DISABLE                      ((uint32_t)0x0UL) /**< CN_BRST_DISABLE Value */
 #define MXC_S_FLC_CN_BRST_DISABLE                      (MXC_V_FLC_CN_BRST_DISABLE << MXC_F_FLC_CN_BRST_POS) /**< CN_BRST_DISABLE Setting */
 #define MXC_V_FLC_CN_BRST_ENABLE                       ((uint32_t)0x1UL) /**< CN_BRST_ENABLE Value */
 #define MXC_S_FLC_CN_BRST_ENABLE                       (MXC_V_FLC_CN_BRST_ENABLE << MXC_F_FLC_CN_BRST_POS) /**< CN_BRST_ENABLE Setting */

 #define MXC_F_FLC_CN_UNLOCK_POS                        28 /**< CN_UNLOCK Position */
 #define MXC_F_FLC_CN_UNLOCK                            ((uint32_t)(0xFUL << MXC_F_FLC_CN_UNLOCK_POS)) /**< CN_UNLOCK Mask */
 #define MXC_V_FLC_CN_UNLOCK_UNLOCKED                   ((uint32_t)0x2UL) /**< CN_UNLOCK_UNLOCKED Value */
 #define MXC_S_FLC_CN_UNLOCK_UNLOCKED                   (MXC_V_FLC_CN_UNLOCK_UNLOCKED << MXC_F_FLC_CN_UNLOCK_POS) /**< CN_UNLOCK_UNLOCKED Setting */
 #define MXC_V_FLC_CN_UNLOCK_LOCKED                     ((uint32_t)0x3UL) /**< CN_UNLOCK_LOCKED Value */
 #define MXC_S_FLC_CN_UNLOCK_LOCKED                     (MXC_V_FLC_CN_UNLOCK_LOCKED << MXC_F_FLC_CN_UNLOCK_POS) /**< CN_UNLOCK_LOCKED Setting */

/**@} end of group FLC_CN_Register */

/**
 * @ingroup  flc_registers
 * @defgroup FLC_INTR FLC_INTR
 * @brief    Flash Interrupt Register.
 * @{
 */
 #define MXC_F_FLC_INTR_DONE_POS                        0 /**< INTR_DONE Position */
 #define MXC_F_FLC_INTR_DONE                            ((uint32_t)(0x1UL << MXC_F_FLC_INTR_DONE_POS)) /**< INTR_DONE Mask */
 #define MXC_V_FLC_INTR_DONE_INACTIVE                   ((uint32_t)0x0UL) /**< INTR_DONE_INACTIVE Value */
 #define MXC_S_FLC_INTR_DONE_INACTIVE                   (MXC_V_FLC_INTR_DONE_INACTIVE << MXC_F_FLC_INTR_DONE_POS) /**< INTR_DONE_INACTIVE Setting */
 #define MXC_V_FLC_INTR_DONE_PENDING                    ((uint32_t)0x1UL) /**< INTR_DONE_PENDING Value */
 #define MXC_S_FLC_INTR_DONE_PENDING                    (MXC_V_FLC_INTR_DONE_PENDING << MXC_F_FLC_INTR_DONE_POS) /**< INTR_DONE_PENDING Setting */

 #define MXC_F_FLC_INTR_AF_POS                          1 /**< INTR_AF Position */
 #define MXC_F_FLC_INTR_AF                              ((uint32_t)(0x1UL << MXC_F_FLC_INTR_AF_POS)) /**< INTR_AF Mask */
 #define MXC_V_FLC_INTR_AF_NOERROR                      ((uint32_t)0x0UL) /**< INTR_AF_NOERROR Value */
 #define MXC_S_FLC_INTR_AF_NOERROR                      (MXC_V_FLC_INTR_AF_NOERROR << MXC_F_FLC_INTR_AF_POS) /**< INTR_AF_NOERROR Setting */
 #define MXC_V_FLC_INTR_AF_ERROR                        ((uint32_t)0x1UL) /**< INTR_AF_ERROR Value */
 #define MXC_S_FLC_INTR_AF_ERROR                        (MXC_V_FLC_INTR_AF_ERROR << MXC_F_FLC_INTR_AF_POS) /**< INTR_AF_ERROR Setting */

 #define MXC_F_FLC_INTR_DONEIE_POS                      8 /**< INTR_DONEIE Position */
 #define MXC_F_FLC_INTR_DONEIE                          ((uint32_t)(0x1UL << MXC_F_FLC_INTR_DONEIE_POS)) /**< INTR_DONEIE Mask */
 #define MXC_V_FLC_INTR_DONEIE_DISABLE                  ((uint32_t)0x0UL) /**< INTR_DONEIE_DISABLE Value */
 #define MXC_S_FLC_INTR_DONEIE_DISABLE                  (MXC_V_FLC_INTR_DONEIE_DISABLE << MXC_F_FLC_INTR_DONEIE_POS) /**< INTR_DONEIE_DISABLE Setting */
 #define MXC_V_FLC_INTR_DONEIE_ENABLE                   ((uint32_t)0x1UL) /**< INTR_DONEIE_ENABLE Value */
 #define MXC_S_FLC_INTR_DONEIE_ENABLE                   (MXC_V_FLC_INTR_DONEIE_ENABLE << MXC_F_FLC_INTR_DONEIE_POS) /**< INTR_DONEIE_ENABLE Setting */

 #define MXC_F_FLC_INTR_AFIE_POS                        9 /**< INTR_AFIE Position */
 #define MXC_F_FLC_INTR_AFIE                            ((uint32_t)(0x1UL << MXC_F_FLC_INTR_AFIE_POS)) /**< INTR_AFIE Mask */

/**@} end of group FLC_INTR_Register */

/**
 * @ingroup  flc_registers
 * @defgroup FLC_DATA FLC_DATA
 * @brief    Flash Write Data.
 * @{
 */
 #define MXC_F_FLC_DATA_DATA_POS                        0 /**< DATA_DATA Position */
 #define MXC_F_FLC_DATA_DATA                            ((uint32_t)(0xFFFFFFFFUL << MXC_F_FLC_DATA_DATA_POS)) /**< DATA_DATA Mask */

/**@} end of group FLC_DATA_Register */

/**
 * @ingroup  flc_registers
 * @defgroup FLC_ACNTL FLC_ACNTL
 * @brief    Access Control Register. Writing the ACNTL register with the following values in
 *           the order shown, allows read and write access to the system and user Information
 *           block: pflc-acntl = 0x3a7f5ca3; pflc-acntl = 0xa1e34f20; pflc-acntl =
 *           0x9608b2c1. When unlocked, a write of any word will disable access to system and
 *           user information block. Readback of this register is always zero.
 * @{
 */
 #define MXC_F_FLC_ACNTL_ACNTL_POS                      0 /**< ACNTL_ACNTL Position */
 #define MXC_F_FLC_ACNTL_ACNTL                          ((uint32_t)(0xFFFFFFFFUL << MXC_F_FLC_ACNTL_ACNTL_POS)) /**< ACNTL_ACNTL Mask */

/**@} end of group FLC_ACNTL_Register */

#ifdef __cplusplus
}
#endif

#endif /* _FLC_REGS_H_ */
