/**
 * @file    icc_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the ICC Peripheral Module.
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

#ifndef _ICC_REGS_H_
#define _ICC_REGS_H_

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
 * @ingroup     icc
 * @defgroup    icc_registers ICC_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the ICC Peripheral Module.
 * @details Instruction Cache Controller Registers
 */

/**
 * @ingroup icc_registers
 * Structure type to access the ICC Registers.
 */
typedef struct {
    __I  uint32_t cache_id;             /**< <tt>\b 0x0000:</tt> ICC CACHE_ID Register */
    __I  uint32_t memcfg;               /**< <tt>\b 0x0004:</tt> ICC MEMCFG Register */
    __R  uint32_t rsv_0x8_0xff[62];
    __IO uint32_t cache_ctrl;           /**< <tt>\b 0x0100:</tt> ICC CACHE_CTRL Register */
    __R  uint32_t rsv_0x104_0x6ff[383];
    __IO uint32_t invalidate;           /**< <tt>\b 0x0700:</tt> ICC INVALIDATE Register */
} mxc_icc_regs_t;

/* Register offsets for module ICC */
/**
 * @ingroup    icc_registers
 * @defgroup   ICC_Register_Offsets Register Offsets
 * @brief      ICC Peripheral Register Offsets from the ICC Base Peripheral Address. 
 * @{
 */
 #define MXC_R_ICC_CACHE_ID                 ((uint32_t)0x00000000UL) /**< Offset from ICC Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_ICC_MEMCFG                   ((uint32_t)0x00000004UL) /**< Offset from ICC Base Address: <tt> 0x0004</tt> */ 
 #define MXC_R_ICC_CACHE_CTRL               ((uint32_t)0x00000100UL) /**< Offset from ICC Base Address: <tt> 0x0100</tt> */ 
 #define MXC_R_ICC_INVALIDATE               ((uint32_t)0x00000700UL) /**< Offset from ICC Base Address: <tt> 0x0700</tt> */ 
/**@} end of group icc_registers */

/**
 * @ingroup  icc_registers
 * @defgroup ICC_CACHE_ID ICC_CACHE_ID
 * @brief    Cache ID Register.
 * @{
 */
 #define MXC_F_ICC_CACHE_ID_RELNUM_POS                  0 /**< CACHE_ID_RELNUM Position */
 #define MXC_F_ICC_CACHE_ID_RELNUM                      ((uint32_t)(0x3FUL << MXC_F_ICC_CACHE_ID_RELNUM_POS)) /**< CACHE_ID_RELNUM Mask */

 #define MXC_F_ICC_CACHE_ID_PARTNUM_POS                 6 /**< CACHE_ID_PARTNUM Position */
 #define MXC_F_ICC_CACHE_ID_PARTNUM                     ((uint32_t)(0xFUL << MXC_F_ICC_CACHE_ID_PARTNUM_POS)) /**< CACHE_ID_PARTNUM Mask */

 #define MXC_F_ICC_CACHE_ID_CCHID_POS                   10 /**< CACHE_ID_CCHID Position */
 #define MXC_F_ICC_CACHE_ID_CCHID                       ((uint32_t)(0x3FUL << MXC_F_ICC_CACHE_ID_CCHID_POS)) /**< CACHE_ID_CCHID Mask */

/**@} end of group ICC_CACHE_ID_Register */

/**
 * @ingroup  icc_registers
 * @defgroup ICC_MEMCFG ICC_MEMCFG
 * @brief    Memory Configuration Register.
 * @{
 */
 #define MXC_F_ICC_MEMCFG_CCHSZ_POS                     0 /**< MEMCFG_CCHSZ Position */
 #define MXC_F_ICC_MEMCFG_CCHSZ                         ((uint32_t)(0xFFFFUL << MXC_F_ICC_MEMCFG_CCHSZ_POS)) /**< MEMCFG_CCHSZ Mask */

 #define MXC_F_ICC_MEMCFG_MEMSZ_POS                     16 /**< MEMCFG_MEMSZ Position */
 #define MXC_F_ICC_MEMCFG_MEMSZ                         ((uint32_t)(0xFFFFUL << MXC_F_ICC_MEMCFG_MEMSZ_POS)) /**< MEMCFG_MEMSZ Mask */

/**@} end of group ICC_MEMCFG_Register */

/**
 * @ingroup  icc_registers
 * @defgroup ICC_CACHE_CTRL ICC_CACHE_CTRL
 * @brief    Cache Control and Status Register.
 * @{
 */
 #define MXC_F_ICC_CACHE_CTRL_CACHE_EN_POS              0 /**< CACHE_CTRL_CACHE_EN Position */
 #define MXC_F_ICC_CACHE_CTRL_CACHE_EN                  ((uint32_t)(0x1UL << MXC_F_ICC_CACHE_CTRL_CACHE_EN_POS)) /**< CACHE_CTRL_CACHE_EN Mask */
 #define MXC_V_ICC_CACHE_CTRL_CACHE_EN_DIS              ((uint32_t)0x0UL) /**< CACHE_CTRL_CACHE_EN_DIS Value */
 #define MXC_S_ICC_CACHE_CTRL_CACHE_EN_DIS              (MXC_V_ICC_CACHE_CTRL_CACHE_EN_DIS << MXC_F_ICC_CACHE_CTRL_CACHE_EN_POS) /**< CACHE_CTRL_CACHE_EN_DIS Setting */
 #define MXC_V_ICC_CACHE_CTRL_CACHE_EN_EN               ((uint32_t)0x1UL) /**< CACHE_CTRL_CACHE_EN_EN Value */
 #define MXC_S_ICC_CACHE_CTRL_CACHE_EN_EN               (MXC_V_ICC_CACHE_CTRL_CACHE_EN_EN << MXC_F_ICC_CACHE_CTRL_CACHE_EN_POS) /**< CACHE_CTRL_CACHE_EN_EN Setting */

 #define MXC_F_ICC_CACHE_CTRL_CACHE_RDY_POS             16 /**< CACHE_CTRL_CACHE_RDY Position */
 #define MXC_F_ICC_CACHE_CTRL_CACHE_RDY                 ((uint32_t)(0x1UL << MXC_F_ICC_CACHE_CTRL_CACHE_RDY_POS)) /**< CACHE_CTRL_CACHE_RDY Mask */
 #define MXC_V_ICC_CACHE_CTRL_CACHE_RDY_NOTREADY        ((uint32_t)0x0UL) /**< CACHE_CTRL_CACHE_RDY_NOTREADY Value */
 #define MXC_S_ICC_CACHE_CTRL_CACHE_RDY_NOTREADY        (MXC_V_ICC_CACHE_CTRL_CACHE_RDY_NOTREADY << MXC_F_ICC_CACHE_CTRL_CACHE_RDY_POS) /**< CACHE_CTRL_CACHE_RDY_NOTREADY Setting */
 #define MXC_V_ICC_CACHE_CTRL_CACHE_RDY_READY           ((uint32_t)0x1UL) /**< CACHE_CTRL_CACHE_RDY_READY Value */
 #define MXC_S_ICC_CACHE_CTRL_CACHE_RDY_READY           (MXC_V_ICC_CACHE_CTRL_CACHE_RDY_READY << MXC_F_ICC_CACHE_CTRL_CACHE_RDY_POS) /**< CACHE_CTRL_CACHE_RDY_READY Setting */

/**@} end of group ICC_CACHE_CTRL_Register */

#ifdef __cplusplus
}
#endif

#endif /* _ICC_REGS_H_ */
