/**
 * @file    bbfc_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the BBFC Peripheral Module.
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

#ifndef _BBFC_REGS_H_
#define _BBFC_REGS_H_

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
 * @ingroup     bbfc
 * @defgroup    bbfc_registers BBFC_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the BBFC Peripheral Module.
 * @details Battery-Backed Function Control.
 */

/**
 * @ingroup bbfc_registers
 * Structure type to access the BBFC Registers.
 */
typedef struct {
    __IO uint32_t bbfcr0;               /**< <tt>\b 0x00:</tt> BBFC BBFCR0 Register */
} mxc_bbfc_regs_t;

/* Register offsets for module BBFC */
/**
 * @ingroup    bbfc_registers
 * @defgroup   BBFC_Register_Offsets Register Offsets
 * @brief      BBFC Peripheral Register Offsets from the BBFC Base Peripheral Address. 
 * @{
 */
 #define MXC_R_BBFC_BBFCR0                  ((uint32_t)0x00000000UL) /**< Offset from BBFC Base Address: <tt> 0x0000</tt> */ 
/**@} end of group bbfc_registers */

/**
 * @ingroup  bbfc_registers
 * @defgroup BBFC_BBFCR0 BBFC_BBFCR0
 * @brief    Function Control Register 0.
 * @{
 */
 #define MXC_F_BBFC_BBFCR0_CKPDRV_POS                   0 /**< BBFCR0_CKPDRV Position */
 #define MXC_F_BBFC_BBFCR0_CKPDRV                       ((uint32_t)(0xFUL << MXC_F_BBFC_BBFCR0_CKPDRV_POS)) /**< BBFCR0_CKPDRV Mask */

 #define MXC_F_BBFC_BBFCR0_CKNPDRV_POS                  4 /**< BBFCR0_CKNPDRV Position */
 #define MXC_F_BBFC_BBFCR0_CKNPDRV                      ((uint32_t)(0xFUL << MXC_F_BBFC_BBFCR0_CKNPDRV_POS)) /**< BBFCR0_CKNPDRV Mask */

 #define MXC_F_BBFC_BBFCR0_RDSDLLEN_POS                 8 /**< BBFCR0_RDSDLLEN Position */
 #define MXC_F_BBFC_BBFCR0_RDSDLLEN                     ((uint32_t)(0x1UL << MXC_F_BBFC_BBFCR0_RDSDLLEN_POS)) /**< BBFCR0_RDSDLLEN Mask */
 #define MXC_V_BBFC_BBFCR0_RDSDLLEN_DIS                 ((uint32_t)0x0UL) /**< BBFCR0_RDSDLLEN_DIS Value */
 #define MXC_S_BBFC_BBFCR0_RDSDLLEN_DIS                 (MXC_V_BBFC_BBFCR0_RDSDLLEN_DIS << MXC_F_BBFC_BBFCR0_RDSDLLEN_POS) /**< BBFCR0_RDSDLLEN_DIS Setting */
 #define MXC_V_BBFC_BBFCR0_RDSDLLEN_EN                  ((uint32_t)0x1UL) /**< BBFCR0_RDSDLLEN_EN Value */
 #define MXC_S_BBFC_BBFCR0_RDSDLLEN_EN                  (MXC_V_BBFC_BBFCR0_RDSDLLEN_EN << MXC_F_BBFC_BBFCR0_RDSDLLEN_POS) /**< BBFCR0_RDSDLLEN_EN Setting */

/**@} end of group BBFC_BBFCR0_Register */

#ifdef __cplusplus
}
#endif

#endif /* _BBFC_REGS_H_ */
