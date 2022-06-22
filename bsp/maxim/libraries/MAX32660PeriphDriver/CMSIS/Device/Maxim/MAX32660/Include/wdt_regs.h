/**
 * @file    wdt_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the WDT Peripheral Module.
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

#ifndef _WDT_REGS_H_
#define _WDT_REGS_H_

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
 * @ingroup     wdt
 * @defgroup    wdt_registers WDT_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the WDT Peripheral Module.
 * @details Watchdog Timer 0
 */

/**
 * @ingroup wdt_registers
 * Structure type to access the WDT Registers.
 */
typedef struct {
    __IO uint32_t ctrl;                 /**< <tt>\b 0x00:</tt> WDT CTRL Register */
    __O  uint32_t rst;                  /**< <tt>\b 0x04:</tt> WDT RST Register */
} mxc_wdt_regs_t;

/* Register offsets for module WDT */
/**
 * @ingroup    wdt_registers
 * @defgroup   WDT_Register_Offsets Register Offsets
 * @brief      WDT Peripheral Register Offsets from the WDT Base Peripheral Address. 
 * @{
 */
 #define MXC_R_WDT_CTRL                     ((uint32_t)0x00000000UL) /**< Offset from WDT Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_WDT_RST                      ((uint32_t)0x00000004UL) /**< Offset from WDT Base Address: <tt> 0x0004</tt> */ 
/**@} end of group wdt_registers */

/**
 * @ingroup  wdt_registers
 * @defgroup WDT_CTRL WDT_CTRL
 * @brief    Watchdog Timer Control Register.
 * @{
 */
 #define MXC_F_WDT_CTRL_INT_PERIOD_POS                  0 /**< CTRL_INT_PERIOD Position */
 #define MXC_F_WDT_CTRL_INT_PERIOD                      ((uint32_t)(0xFUL << MXC_F_WDT_CTRL_INT_PERIOD_POS)) /**< CTRL_INT_PERIOD Mask */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW31            ((uint32_t)0x0UL) /**< CTRL_INT_PERIOD_WDT2POW31 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW31            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW31 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW31 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW30            ((uint32_t)0x1UL) /**< CTRL_INT_PERIOD_WDT2POW30 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW30            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW30 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW30 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW29            ((uint32_t)0x2UL) /**< CTRL_INT_PERIOD_WDT2POW29 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW29            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW29 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW29 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW28            ((uint32_t)0x3UL) /**< CTRL_INT_PERIOD_WDT2POW28 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW28            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW28 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW28 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW27            ((uint32_t)0x4UL) /**< CTRL_INT_PERIOD_WDT2POW27 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW27            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW27 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW27 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW26            ((uint32_t)0x5UL) /**< CTRL_INT_PERIOD_WDT2POW26 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW26            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW26 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW26 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW25            ((uint32_t)0x6UL) /**< CTRL_INT_PERIOD_WDT2POW25 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW25            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW25 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW25 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW24            ((uint32_t)0x7UL) /**< CTRL_INT_PERIOD_WDT2POW24 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW24            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW24 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW24 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW23            ((uint32_t)0x8UL) /**< CTRL_INT_PERIOD_WDT2POW23 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW23            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW23 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW23 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW22            ((uint32_t)0x9UL) /**< CTRL_INT_PERIOD_WDT2POW22 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW22            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW22 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW22 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW21            ((uint32_t)0xAUL) /**< CTRL_INT_PERIOD_WDT2POW21 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW21            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW21 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW21 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW20            ((uint32_t)0xBUL) /**< CTRL_INT_PERIOD_WDT2POW20 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW20            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW20 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW20 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW19            ((uint32_t)0xCUL) /**< CTRL_INT_PERIOD_WDT2POW19 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW19            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW19 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW19 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW18            ((uint32_t)0xDUL) /**< CTRL_INT_PERIOD_WDT2POW18 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW18            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW18 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW18 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW17            ((uint32_t)0xEUL) /**< CTRL_INT_PERIOD_WDT2POW17 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW17            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW17 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW17 Setting */
 #define MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW16            ((uint32_t)0xFUL) /**< CTRL_INT_PERIOD_WDT2POW16 Value */
 #define MXC_S_WDT_CTRL_INT_PERIOD_WDT2POW16            (MXC_V_WDT_CTRL_INT_PERIOD_WDT2POW16 << MXC_F_WDT_CTRL_INT_PERIOD_POS) /**< CTRL_INT_PERIOD_WDT2POW16 Setting */

 #define MXC_F_WDT_CTRL_RST_PERIOD_POS                  4 /**< CTRL_RST_PERIOD Position */
 #define MXC_F_WDT_CTRL_RST_PERIOD                      ((uint32_t)(0xFUL << MXC_F_WDT_CTRL_RST_PERIOD_POS)) /**< CTRL_RST_PERIOD Mask */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW31            ((uint32_t)0x0UL) /**< CTRL_RST_PERIOD_WDT2POW31 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW31            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW31 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW31 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW30            ((uint32_t)0x1UL) /**< CTRL_RST_PERIOD_WDT2POW30 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW30            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW30 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW30 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW29            ((uint32_t)0x2UL) /**< CTRL_RST_PERIOD_WDT2POW29 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW29            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW29 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW29 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW28            ((uint32_t)0x3UL) /**< CTRL_RST_PERIOD_WDT2POW28 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW28            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW28 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW28 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW27            ((uint32_t)0x4UL) /**< CTRL_RST_PERIOD_WDT2POW27 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW27            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW27 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW27 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW26            ((uint32_t)0x5UL) /**< CTRL_RST_PERIOD_WDT2POW26 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW26            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW26 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW26 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW25            ((uint32_t)0x6UL) /**< CTRL_RST_PERIOD_WDT2POW25 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW25            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW25 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW25 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW24            ((uint32_t)0x7UL) /**< CTRL_RST_PERIOD_WDT2POW24 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW24            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW24 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW24 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW23            ((uint32_t)0x8UL) /**< CTRL_RST_PERIOD_WDT2POW23 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW23            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW23 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW23 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW22            ((uint32_t)0x9UL) /**< CTRL_RST_PERIOD_WDT2POW22 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW22            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW22 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW22 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW21            ((uint32_t)0xAUL) /**< CTRL_RST_PERIOD_WDT2POW21 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW21            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW21 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW21 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW20            ((uint32_t)0xBUL) /**< CTRL_RST_PERIOD_WDT2POW20 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW20            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW20 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW20 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW19            ((uint32_t)0xCUL) /**< CTRL_RST_PERIOD_WDT2POW19 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW19            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW19 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW19 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW18            ((uint32_t)0xDUL) /**< CTRL_RST_PERIOD_WDT2POW18 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW18            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW18 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW18 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW17            ((uint32_t)0xEUL) /**< CTRL_RST_PERIOD_WDT2POW17 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW17            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW17 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW17 Setting */
 #define MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW16            ((uint32_t)0xFUL) /**< CTRL_RST_PERIOD_WDT2POW16 Value */
 #define MXC_S_WDT_CTRL_RST_PERIOD_WDT2POW16            (MXC_V_WDT_CTRL_RST_PERIOD_WDT2POW16 << MXC_F_WDT_CTRL_RST_PERIOD_POS) /**< CTRL_RST_PERIOD_WDT2POW16 Setting */

 #define MXC_F_WDT_CTRL_WDT_EN_POS                      8 /**< CTRL_WDT_EN Position */
 #define MXC_F_WDT_CTRL_WDT_EN                          ((uint32_t)(0x1UL << MXC_F_WDT_CTRL_WDT_EN_POS)) /**< CTRL_WDT_EN Mask */
 #define MXC_V_WDT_CTRL_WDT_EN_DIS                      ((uint32_t)0x0UL) /**< CTRL_WDT_EN_DIS Value */
 #define MXC_S_WDT_CTRL_WDT_EN_DIS                      (MXC_V_WDT_CTRL_WDT_EN_DIS << MXC_F_WDT_CTRL_WDT_EN_POS) /**< CTRL_WDT_EN_DIS Setting */
 #define MXC_V_WDT_CTRL_WDT_EN_EN                       ((uint32_t)0x1UL) /**< CTRL_WDT_EN_EN Value */
 #define MXC_S_WDT_CTRL_WDT_EN_EN                       (MXC_V_WDT_CTRL_WDT_EN_EN << MXC_F_WDT_CTRL_WDT_EN_POS) /**< CTRL_WDT_EN_EN Setting */

 #define MXC_F_WDT_CTRL_INT_FLAG_POS                    9 /**< CTRL_INT_FLAG Position */
 #define MXC_F_WDT_CTRL_INT_FLAG                        ((uint32_t)(0x1UL << MXC_F_WDT_CTRL_INT_FLAG_POS)) /**< CTRL_INT_FLAG Mask */
 #define MXC_V_WDT_CTRL_INT_FLAG_INACTIVE               ((uint32_t)0x0UL) /**< CTRL_INT_FLAG_INACTIVE Value */
 #define MXC_S_WDT_CTRL_INT_FLAG_INACTIVE               (MXC_V_WDT_CTRL_INT_FLAG_INACTIVE << MXC_F_WDT_CTRL_INT_FLAG_POS) /**< CTRL_INT_FLAG_INACTIVE Setting */
 #define MXC_V_WDT_CTRL_INT_FLAG_PENDING                ((uint32_t)0x1UL) /**< CTRL_INT_FLAG_PENDING Value */
 #define MXC_S_WDT_CTRL_INT_FLAG_PENDING                (MXC_V_WDT_CTRL_INT_FLAG_PENDING << MXC_F_WDT_CTRL_INT_FLAG_POS) /**< CTRL_INT_FLAG_PENDING Setting */

 #define MXC_F_WDT_CTRL_INT_EN_POS                      10 /**< CTRL_INT_EN Position */
 #define MXC_F_WDT_CTRL_INT_EN                          ((uint32_t)(0x1UL << MXC_F_WDT_CTRL_INT_EN_POS)) /**< CTRL_INT_EN Mask */
 #define MXC_V_WDT_CTRL_INT_EN_DIS                      ((uint32_t)0x0UL) /**< CTRL_INT_EN_DIS Value */
 #define MXC_S_WDT_CTRL_INT_EN_DIS                      (MXC_V_WDT_CTRL_INT_EN_DIS << MXC_F_WDT_CTRL_INT_EN_POS) /**< CTRL_INT_EN_DIS Setting */
 #define MXC_V_WDT_CTRL_INT_EN_EN                       ((uint32_t)0x1UL) /**< CTRL_INT_EN_EN Value */
 #define MXC_S_WDT_CTRL_INT_EN_EN                       (MXC_V_WDT_CTRL_INT_EN_EN << MXC_F_WDT_CTRL_INT_EN_POS) /**< CTRL_INT_EN_EN Setting */

 #define MXC_F_WDT_CTRL_RST_EN_POS                      11 /**< CTRL_RST_EN Position */
 #define MXC_F_WDT_CTRL_RST_EN                          ((uint32_t)(0x1UL << MXC_F_WDT_CTRL_RST_EN_POS)) /**< CTRL_RST_EN Mask */
 #define MXC_V_WDT_CTRL_RST_EN_DIS                      ((uint32_t)0x0UL) /**< CTRL_RST_EN_DIS Value */
 #define MXC_S_WDT_CTRL_RST_EN_DIS                      (MXC_V_WDT_CTRL_RST_EN_DIS << MXC_F_WDT_CTRL_RST_EN_POS) /**< CTRL_RST_EN_DIS Setting */
 #define MXC_V_WDT_CTRL_RST_EN_EN                       ((uint32_t)0x1UL) /**< CTRL_RST_EN_EN Value */
 #define MXC_S_WDT_CTRL_RST_EN_EN                       (MXC_V_WDT_CTRL_RST_EN_EN << MXC_F_WDT_CTRL_RST_EN_POS) /**< CTRL_RST_EN_EN Setting */

 #define MXC_F_WDT_CTRL_RST_FLAG_POS                    31 /**< CTRL_RST_FLAG Position */
 #define MXC_F_WDT_CTRL_RST_FLAG                        ((uint32_t)(0x1UL << MXC_F_WDT_CTRL_RST_FLAG_POS)) /**< CTRL_RST_FLAG Mask */
 #define MXC_V_WDT_CTRL_RST_FLAG_NOEVENT                ((uint32_t)0x0UL) /**< CTRL_RST_FLAG_NOEVENT Value */
 #define MXC_S_WDT_CTRL_RST_FLAG_NOEVENT                (MXC_V_WDT_CTRL_RST_FLAG_NOEVENT << MXC_F_WDT_CTRL_RST_FLAG_POS) /**< CTRL_RST_FLAG_NOEVENT Setting */
 #define MXC_V_WDT_CTRL_RST_FLAG_OCCURRED               ((uint32_t)0x1UL) /**< CTRL_RST_FLAG_OCCURRED Value */
 #define MXC_S_WDT_CTRL_RST_FLAG_OCCURRED               (MXC_V_WDT_CTRL_RST_FLAG_OCCURRED << MXC_F_WDT_CTRL_RST_FLAG_POS) /**< CTRL_RST_FLAG_OCCURRED Setting */

/**@} end of group WDT_CTRL_Register */

/**
 * @ingroup  wdt_registers
 * @defgroup WDT_RST WDT_RST
 * @brief    Watchdog Timer Reset Register.
 * @{
 */
 #define MXC_F_WDT_RST_WDT_RST_POS                      0 /**< RST_WDT_RST Position */
 #define MXC_F_WDT_RST_WDT_RST                          ((uint32_t)(0xFFUL << MXC_F_WDT_RST_WDT_RST_POS)) /**< RST_WDT_RST Mask */
 #define MXC_V_WDT_RST_WDT_RST_SEQ0                     ((uint32_t)0xA5UL) /**< RST_WDT_RST_SEQ0 Value */
 #define MXC_S_WDT_RST_WDT_RST_SEQ0                     (MXC_V_WDT_RST_WDT_RST_SEQ0 << MXC_F_WDT_RST_WDT_RST_POS) /**< RST_WDT_RST_SEQ0 Setting */
 #define MXC_V_WDT_RST_WDT_RST_SEQ1                     ((uint32_t)0x5AUL) /**< RST_WDT_RST_SEQ1 Value */
 #define MXC_S_WDT_RST_WDT_RST_SEQ1                     (MXC_V_WDT_RST_WDT_RST_SEQ1 << MXC_F_WDT_RST_WDT_RST_POS) /**< RST_WDT_RST_SEQ1 Setting */

/**@} end of group WDT_RST_Register */

#ifdef __cplusplus
}
#endif

#endif /* _WDT_REGS_H_ */
