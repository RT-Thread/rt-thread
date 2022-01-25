/**
 * @file    bbsir_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the BBSIR Peripheral Module.
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

#ifndef _BBSIR_REGS_H_
#define _BBSIR_REGS_H_

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
 * @ingroup     bbsir
 * @defgroup    bbsir_registers BBSIR_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the BBSIR Peripheral Module.
 * @details Battery-Backed Registers.
 */

/**
 * @ingroup bbsir_registers
 * Structure type to access the BBSIR Registers.
 */
typedef struct {
    __IO uint32_t rsv0;                 /**< <tt>\b 0x00:</tt> BBSIR RSV0 Register */
    __R  uint32_t rsv_0x4;
    __I  uint32_t bb_sir2;              /**< <tt>\b 0x08:</tt> BBSIR BB_SIR2 Register */
    __I  uint32_t bb_sir3;              /**< <tt>\b 0x0C:</tt> BBSIR BB_SIR3 Register */
} mxc_bbsir_regs_t;

/* Register offsets for module BBSIR */
/**
 * @ingroup    bbsir_registers
 * @defgroup   BBSIR_Register_Offsets Register Offsets
 * @brief      BBSIR Peripheral Register Offsets from the BBSIR Base Peripheral Address. 
 * @{
 */
 #define MXC_R_BBSIR_RSV0                   ((uint32_t)0x00000000UL) /**< Offset from BBSIR Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_BBSIR_BB_SIR2                ((uint32_t)0x00000008UL) /**< Offset from BBSIR Base Address: <tt> 0x0008</tt> */ 
 #define MXC_R_BBSIR_BB_SIR3                ((uint32_t)0x0000000CUL) /**< Offset from BBSIR Base Address: <tt> 0x000C</tt> */ 
/**@} end of group bbsir_registers */

#ifdef __cplusplus
}
#endif

#endif /* _BBSIR_REGS_H_ */
