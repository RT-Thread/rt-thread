/**
 * @file    gcr_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the GCR Peripheral Module.
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

#ifndef _GCR_REGS_H_
#define _GCR_REGS_H_

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
 * @ingroup     gcr
 * @defgroup    gcr_registers GCR_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the GCR Peripheral Module.
 * @details Global Control Registers.
 */

/**
 * @ingroup gcr_registers
 * Structure type to access the GCR Registers.
 */
typedef struct {
    __IO uint32_t scon;                 /**< <tt>\b 0x00:</tt> GCR SCON Register */
    __IO uint32_t rstr0;                /**< <tt>\b 0x04:</tt> GCR RSTR0 Register */
    __IO uint32_t clkcn;                /**< <tt>\b 0x08:</tt> GCR CLKCN Register */
    __IO uint32_t pm;                   /**< <tt>\b 0x0C:</tt> GCR PM Register */
    __R  uint32_t rsv_0x10_0x17[2];
    __IO uint32_t pckdiv;               /**< <tt>\b 0x18:</tt> GCR PCKDIV Register */
    __R  uint32_t rsv_0x1c_0x23[2];
    __IO uint32_t perckcn0;             /**< <tt>\b 0x24:</tt> GCR PERCKCN0 Register */
    __IO uint32_t memckcn;              /**< <tt>\b 0x28:</tt> GCR MEMCKCN Register */
    __IO uint32_t memzcn;               /**< <tt>\b 0x2C:</tt> GCR MEMZCN Register */
    __R  uint32_t rsv_0x30;
    __IO uint32_t scck;                 /**< <tt>\b 0x34:</tt> GCR SCCK Register */
    __IO uint32_t mpri0;                /**< <tt>\b 0x38:</tt> GCR MPRI0 Register */
    __IO uint32_t mpri1;                /**< <tt>\b 0x3C:</tt> GCR MPRI1 Register */
    __IO uint32_t sysst;                /**< <tt>\b 0x40:</tt> GCR SYSST Register */
    __IO uint32_t rstr1;                /**< <tt>\b 0x44:</tt> GCR RSTR1 Register */
    __IO uint32_t perckcn1;             /**< <tt>\b 0x48:</tt> GCR PERCKCN1 Register */
    __IO uint32_t evten;                /**< <tt>\b 0x4C:</tt> GCR EVTEN Register */
    __I  uint32_t revision;             /**< <tt>\b 0x50:</tt> GCR REVISION Register */
    __IO uint32_t syssie;               /**< <tt>\b 0x54:</tt> GCR SYSSIE Register */
} mxc_gcr_regs_t;

/* Register offsets for module GCR */
/**
 * @ingroup    gcr_registers
 * @defgroup   GCR_Register_Offsets Register Offsets
 * @brief      GCR Peripheral Register Offsets from the GCR Base Peripheral Address. 
 * @{
 */
 #define MXC_R_GCR_SCON                     ((uint32_t)0x00000000UL) /**< Offset from GCR Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_GCR_RSTR0                    ((uint32_t)0x00000004UL) /**< Offset from GCR Base Address: <tt> 0x0004</tt> */ 
 #define MXC_R_GCR_CLKCN                    ((uint32_t)0x00000008UL) /**< Offset from GCR Base Address: <tt> 0x0008</tt> */ 
 #define MXC_R_GCR_PM                       ((uint32_t)0x0000000CUL) /**< Offset from GCR Base Address: <tt> 0x000C</tt> */ 
 #define MXC_R_GCR_PCKDIV                   ((uint32_t)0x00000018UL) /**< Offset from GCR Base Address: <tt> 0x0018</tt> */ 
 #define MXC_R_GCR_PERCKCN0                 ((uint32_t)0x00000024UL) /**< Offset from GCR Base Address: <tt> 0x0024</tt> */ 
 #define MXC_R_GCR_MEMCKCN                  ((uint32_t)0x00000028UL) /**< Offset from GCR Base Address: <tt> 0x0028</tt> */ 
 #define MXC_R_GCR_MEMZCN                   ((uint32_t)0x0000002CUL) /**< Offset from GCR Base Address: <tt> 0x002C</tt> */ 
 #define MXC_R_GCR_SCCK                     ((uint32_t)0x00000034UL) /**< Offset from GCR Base Address: <tt> 0x0034</tt> */ 
 #define MXC_R_GCR_MPRI0                    ((uint32_t)0x00000038UL) /**< Offset from GCR Base Address: <tt> 0x0038</tt> */ 
 #define MXC_R_GCR_MPRI1                    ((uint32_t)0x0000003CUL) /**< Offset from GCR Base Address: <tt> 0x003C</tt> */ 
 #define MXC_R_GCR_SYSST                    ((uint32_t)0x00000040UL) /**< Offset from GCR Base Address: <tt> 0x0040</tt> */ 
 #define MXC_R_GCR_RSTR1                    ((uint32_t)0x00000044UL) /**< Offset from GCR Base Address: <tt> 0x0044</tt> */ 
 #define MXC_R_GCR_PERCKCN1                 ((uint32_t)0x00000048UL) /**< Offset from GCR Base Address: <tt> 0x0048</tt> */ 
 #define MXC_R_GCR_EVTEN                    ((uint32_t)0x0000004CUL) /**< Offset from GCR Base Address: <tt> 0x004C</tt> */ 
 #define MXC_R_GCR_REVISION                 ((uint32_t)0x00000050UL) /**< Offset from GCR Base Address: <tt> 0x0050</tt> */ 
 #define MXC_R_GCR_SYSSIE                   ((uint32_t)0x00000054UL) /**< Offset from GCR Base Address: <tt> 0x0054</tt> */ 
/**@} end of group gcr_registers */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_SCON GCR_SCON
 * @brief    System Control.
 * @{
 */
 #define MXC_F_GCR_SCON_SBUSARB_POS                     1 /**< SCON_SBUSARB Position */
 #define MXC_F_GCR_SCON_SBUSARB                         ((uint32_t)(0x3UL << MXC_F_GCR_SCON_SBUSARB_POS)) /**< SCON_SBUSARB Mask */
 #define MXC_V_GCR_SCON_SBUSARB_FIX                     ((uint32_t)0x0UL) /**< SCON_SBUSARB_FIX Value */
 #define MXC_S_GCR_SCON_SBUSARB_FIX                     (MXC_V_GCR_SCON_SBUSARB_FIX << MXC_F_GCR_SCON_SBUSARB_POS) /**< SCON_SBUSARB_FIX Setting */
 #define MXC_V_GCR_SCON_SBUSARB_ROUND                   ((uint32_t)0x1UL) /**< SCON_SBUSARB_ROUND Value */
 #define MXC_S_GCR_SCON_SBUSARB_ROUND                   (MXC_V_GCR_SCON_SBUSARB_ROUND << MXC_F_GCR_SCON_SBUSARB_POS) /**< SCON_SBUSARB_ROUND Setting */

 #define MXC_F_GCR_SCON_FLASH_PAGE_FLIP_POS             4 /**< SCON_FLASH_PAGE_FLIP Position */
 #define MXC_F_GCR_SCON_FLASH_PAGE_FLIP                 ((uint32_t)(0x1UL << MXC_F_GCR_SCON_FLASH_PAGE_FLIP_POS)) /**< SCON_FLASH_PAGE_FLIP Mask */
 #define MXC_V_GCR_SCON_FLASH_PAGE_FLIP_NORMAL          ((uint32_t)0x0UL) /**< SCON_FLASH_PAGE_FLIP_NORMAL Value */
 #define MXC_S_GCR_SCON_FLASH_PAGE_FLIP_NORMAL          (MXC_V_GCR_SCON_FLASH_PAGE_FLIP_NORMAL << MXC_F_GCR_SCON_FLASH_PAGE_FLIP_POS) /**< SCON_FLASH_PAGE_FLIP_NORMAL Setting */
 #define MXC_V_GCR_SCON_FLASH_PAGE_FLIP_SWAPPED         ((uint32_t)0x1UL) /**< SCON_FLASH_PAGE_FLIP_SWAPPED Value */
 #define MXC_S_GCR_SCON_FLASH_PAGE_FLIP_SWAPPED         (MXC_V_GCR_SCON_FLASH_PAGE_FLIP_SWAPPED << MXC_F_GCR_SCON_FLASH_PAGE_FLIP_POS) /**< SCON_FLASH_PAGE_FLIP_SWAPPED Setting */

 #define MXC_F_GCR_SCON_FPU_DIS_POS                     5 /**< SCON_FPU_DIS Position */
 #define MXC_F_GCR_SCON_FPU_DIS                         ((uint32_t)(0x1UL << MXC_F_GCR_SCON_FPU_DIS_POS)) /**< SCON_FPU_DIS Mask */
 #define MXC_V_GCR_SCON_FPU_DIS_ENABLE                  ((uint32_t)0x0UL) /**< SCON_FPU_DIS_ENABLE Value */
 #define MXC_S_GCR_SCON_FPU_DIS_ENABLE                  (MXC_V_GCR_SCON_FPU_DIS_ENABLE << MXC_F_GCR_SCON_FPU_DIS_POS) /**< SCON_FPU_DIS_ENABLE Setting */
 #define MXC_V_GCR_SCON_FPU_DIS_DISABLE                 ((uint32_t)0x1UL) /**< SCON_FPU_DIS_DISABLE Value */
 #define MXC_S_GCR_SCON_FPU_DIS_DISABLE                 (MXC_V_GCR_SCON_FPU_DIS_DISABLE << MXC_F_GCR_SCON_FPU_DIS_POS) /**< SCON_FPU_DIS_DISABLE Setting */

 #define MXC_F_GCR_SCON_CCACHE_FLUSH_POS                6 /**< SCON_CCACHE_FLUSH Position */
 #define MXC_F_GCR_SCON_CCACHE_FLUSH                    ((uint32_t)(0x1UL << MXC_F_GCR_SCON_CCACHE_FLUSH_POS)) /**< SCON_CCACHE_FLUSH Mask */
 #define MXC_V_GCR_SCON_CCACHE_FLUSH_NORMAL             ((uint32_t)0x0UL) /**< SCON_CCACHE_FLUSH_NORMAL Value */
 #define MXC_S_GCR_SCON_CCACHE_FLUSH_NORMAL             (MXC_V_GCR_SCON_CCACHE_FLUSH_NORMAL << MXC_F_GCR_SCON_CCACHE_FLUSH_POS) /**< SCON_CCACHE_FLUSH_NORMAL Setting */
 #define MXC_V_GCR_SCON_CCACHE_FLUSH_FLUSH              ((uint32_t)0x1UL) /**< SCON_CCACHE_FLUSH_FLUSH Value */
 #define MXC_S_GCR_SCON_CCACHE_FLUSH_FLUSH              (MXC_V_GCR_SCON_CCACHE_FLUSH_FLUSH << MXC_F_GCR_SCON_CCACHE_FLUSH_POS) /**< SCON_CCACHE_FLUSH_FLUSH Setting */

 #define MXC_F_GCR_SCON_SWD_DIS_POS                     14 /**< SCON_SWD_DIS Position */
 #define MXC_F_GCR_SCON_SWD_DIS                         ((uint32_t)(0x1UL << MXC_F_GCR_SCON_SWD_DIS_POS)) /**< SCON_SWD_DIS Mask */
 #define MXC_V_GCR_SCON_SWD_DIS_ENABLE                  ((uint32_t)0x0UL) /**< SCON_SWD_DIS_ENABLE Value */
 #define MXC_S_GCR_SCON_SWD_DIS_ENABLE                  (MXC_V_GCR_SCON_SWD_DIS_ENABLE << MXC_F_GCR_SCON_SWD_DIS_POS) /**< SCON_SWD_DIS_ENABLE Setting */
 #define MXC_V_GCR_SCON_SWD_DIS_DISABLE                 ((uint32_t)0x1UL) /**< SCON_SWD_DIS_DISABLE Value */
 #define MXC_S_GCR_SCON_SWD_DIS_DISABLE                 (MXC_V_GCR_SCON_SWD_DIS_DISABLE << MXC_F_GCR_SCON_SWD_DIS_POS) /**< SCON_SWD_DIS_DISABLE Setting */

/**@} end of group GCR_SCON_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_RSTR0 GCR_RSTR0
 * @brief    Reset.
 * @{
 */
 #define MXC_F_GCR_RSTR0_DMA_POS                        0 /**< RSTR0_DMA Position */
 #define MXC_F_GCR_RSTR0_DMA                            ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_DMA_POS)) /**< RSTR0_DMA Mask */
 #define MXC_V_GCR_RSTR0_DMA_RFU                        ((uint32_t)0x0UL) /**< RSTR0_DMA_RFU Value */
 #define MXC_S_GCR_RSTR0_DMA_RFU                        (MXC_V_GCR_RSTR0_DMA_RFU << MXC_F_GCR_RSTR0_DMA_POS) /**< RSTR0_DMA_RFU Setting */
 #define MXC_V_GCR_RSTR0_DMA_RESET                      ((uint32_t)0x1UL) /**< RSTR0_DMA_RESET Value */
 #define MXC_S_GCR_RSTR0_DMA_RESET                      (MXC_V_GCR_RSTR0_DMA_RESET << MXC_F_GCR_RSTR0_DMA_POS) /**< RSTR0_DMA_RESET Setting */
 #define MXC_V_GCR_RSTR0_DMA_RESET_DONE                 ((uint32_t)0x0UL) /**< RSTR0_DMA_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_DMA_RESET_DONE                 (MXC_V_GCR_RSTR0_DMA_RESET_DONE << MXC_F_GCR_RSTR0_DMA_POS) /**< RSTR0_DMA_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_DMA_BUSY                       ((uint32_t)0x1UL) /**< RSTR0_DMA_BUSY Value */
 #define MXC_S_GCR_RSTR0_DMA_BUSY                       (MXC_V_GCR_RSTR0_DMA_BUSY << MXC_F_GCR_RSTR0_DMA_POS) /**< RSTR0_DMA_BUSY Setting */

 #define MXC_F_GCR_RSTR0_WDT_POS                        1 /**< RSTR0_WDT Position */
 #define MXC_F_GCR_RSTR0_WDT                            ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_WDT_POS)) /**< RSTR0_WDT Mask */
 #define MXC_V_GCR_RSTR0_WDT_RFU                        ((uint32_t)0x0UL) /**< RSTR0_WDT_RFU Value */
 #define MXC_S_GCR_RSTR0_WDT_RFU                        (MXC_V_GCR_RSTR0_WDT_RFU << MXC_F_GCR_RSTR0_WDT_POS) /**< RSTR0_WDT_RFU Setting */
 #define MXC_V_GCR_RSTR0_WDT_RESET                      ((uint32_t)0x1UL) /**< RSTR0_WDT_RESET Value */
 #define MXC_S_GCR_RSTR0_WDT_RESET                      (MXC_V_GCR_RSTR0_WDT_RESET << MXC_F_GCR_RSTR0_WDT_POS) /**< RSTR0_WDT_RESET Setting */
 #define MXC_V_GCR_RSTR0_WDT_RESET_DONE                 ((uint32_t)0x0UL) /**< RSTR0_WDT_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_WDT_RESET_DONE                 (MXC_V_GCR_RSTR0_WDT_RESET_DONE << MXC_F_GCR_RSTR0_WDT_POS) /**< RSTR0_WDT_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_WDT_BUSY                       ((uint32_t)0x1UL) /**< RSTR0_WDT_BUSY Value */
 #define MXC_S_GCR_RSTR0_WDT_BUSY                       (MXC_V_GCR_RSTR0_WDT_BUSY << MXC_F_GCR_RSTR0_WDT_POS) /**< RSTR0_WDT_BUSY Setting */

 #define MXC_F_GCR_RSTR0_GPIO0_POS                      2 /**< RSTR0_GPIO0 Position */
 #define MXC_F_GCR_RSTR0_GPIO0                          ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_GPIO0_POS)) /**< RSTR0_GPIO0 Mask */
 #define MXC_V_GCR_RSTR0_GPIO0_RFU                      ((uint32_t)0x0UL) /**< RSTR0_GPIO0_RFU Value */
 #define MXC_S_GCR_RSTR0_GPIO0_RFU                      (MXC_V_GCR_RSTR0_GPIO0_RFU << MXC_F_GCR_RSTR0_GPIO0_POS) /**< RSTR0_GPIO0_RFU Setting */
 #define MXC_V_GCR_RSTR0_GPIO0_RESET                    ((uint32_t)0x1UL) /**< RSTR0_GPIO0_RESET Value */
 #define MXC_S_GCR_RSTR0_GPIO0_RESET                    (MXC_V_GCR_RSTR0_GPIO0_RESET << MXC_F_GCR_RSTR0_GPIO0_POS) /**< RSTR0_GPIO0_RESET Setting */
 #define MXC_V_GCR_RSTR0_GPIO0_RESET_DONE               ((uint32_t)0x0UL) /**< RSTR0_GPIO0_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_GPIO0_RESET_DONE               (MXC_V_GCR_RSTR0_GPIO0_RESET_DONE << MXC_F_GCR_RSTR0_GPIO0_POS) /**< RSTR0_GPIO0_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_GPIO0_BUSY                     ((uint32_t)0x1UL) /**< RSTR0_GPIO0_BUSY Value */
 #define MXC_S_GCR_RSTR0_GPIO0_BUSY                     (MXC_V_GCR_RSTR0_GPIO0_BUSY << MXC_F_GCR_RSTR0_GPIO0_POS) /**< RSTR0_GPIO0_BUSY Setting */

 #define MXC_F_GCR_RSTR0_TIMER0_POS                     5 /**< RSTR0_TIMER0 Position */
 #define MXC_F_GCR_RSTR0_TIMER0                         ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_TIMER0_POS)) /**< RSTR0_TIMER0 Mask */
 #define MXC_V_GCR_RSTR0_TIMER0_RFU                     ((uint32_t)0x0UL) /**< RSTR0_TIMER0_RFU Value */
 #define MXC_S_GCR_RSTR0_TIMER0_RFU                     (MXC_V_GCR_RSTR0_TIMER0_RFU << MXC_F_GCR_RSTR0_TIMER0_POS) /**< RSTR0_TIMER0_RFU Setting */
 #define MXC_V_GCR_RSTR0_TIMER0_RESET                   ((uint32_t)0x1UL) /**< RSTR0_TIMER0_RESET Value */
 #define MXC_S_GCR_RSTR0_TIMER0_RESET                   (MXC_V_GCR_RSTR0_TIMER0_RESET << MXC_F_GCR_RSTR0_TIMER0_POS) /**< RSTR0_TIMER0_RESET Setting */
 #define MXC_V_GCR_RSTR0_TIMER0_RESET_DONE              ((uint32_t)0x0UL) /**< RSTR0_TIMER0_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_TIMER0_RESET_DONE              (MXC_V_GCR_RSTR0_TIMER0_RESET_DONE << MXC_F_GCR_RSTR0_TIMER0_POS) /**< RSTR0_TIMER0_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_TIMER0_BUSY                    ((uint32_t)0x1UL) /**< RSTR0_TIMER0_BUSY Value */
 #define MXC_S_GCR_RSTR0_TIMER0_BUSY                    (MXC_V_GCR_RSTR0_TIMER0_BUSY << MXC_F_GCR_RSTR0_TIMER0_POS) /**< RSTR0_TIMER0_BUSY Setting */

 #define MXC_F_GCR_RSTR0_TIMER1_POS                     6 /**< RSTR0_TIMER1 Position */
 #define MXC_F_GCR_RSTR0_TIMER1                         ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_TIMER1_POS)) /**< RSTR0_TIMER1 Mask */
 #define MXC_V_GCR_RSTR0_TIMER1_RFU                     ((uint32_t)0x0UL) /**< RSTR0_TIMER1_RFU Value */
 #define MXC_S_GCR_RSTR0_TIMER1_RFU                     (MXC_V_GCR_RSTR0_TIMER1_RFU << MXC_F_GCR_RSTR0_TIMER1_POS) /**< RSTR0_TIMER1_RFU Setting */
 #define MXC_V_GCR_RSTR0_TIMER1_RESET                   ((uint32_t)0x1UL) /**< RSTR0_TIMER1_RESET Value */
 #define MXC_S_GCR_RSTR0_TIMER1_RESET                   (MXC_V_GCR_RSTR0_TIMER1_RESET << MXC_F_GCR_RSTR0_TIMER1_POS) /**< RSTR0_TIMER1_RESET Setting */
 #define MXC_V_GCR_RSTR0_TIMER1_RESET_DONE              ((uint32_t)0x0UL) /**< RSTR0_TIMER1_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_TIMER1_RESET_DONE              (MXC_V_GCR_RSTR0_TIMER1_RESET_DONE << MXC_F_GCR_RSTR0_TIMER1_POS) /**< RSTR0_TIMER1_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_TIMER1_BUSY                    ((uint32_t)0x1UL) /**< RSTR0_TIMER1_BUSY Value */
 #define MXC_S_GCR_RSTR0_TIMER1_BUSY                    (MXC_V_GCR_RSTR0_TIMER1_BUSY << MXC_F_GCR_RSTR0_TIMER1_POS) /**< RSTR0_TIMER1_BUSY Setting */

 #define MXC_F_GCR_RSTR0_TIMER2_POS                     7 /**< RSTR0_TIMER2 Position */
 #define MXC_F_GCR_RSTR0_TIMER2                         ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_TIMER2_POS)) /**< RSTR0_TIMER2 Mask */
 #define MXC_V_GCR_RSTR0_TIMER2_RFU                     ((uint32_t)0x0UL) /**< RSTR0_TIMER2_RFU Value */
 #define MXC_S_GCR_RSTR0_TIMER2_RFU                     (MXC_V_GCR_RSTR0_TIMER2_RFU << MXC_F_GCR_RSTR0_TIMER2_POS) /**< RSTR0_TIMER2_RFU Setting */
 #define MXC_V_GCR_RSTR0_TIMER2_RESET                   ((uint32_t)0x1UL) /**< RSTR0_TIMER2_RESET Value */
 #define MXC_S_GCR_RSTR0_TIMER2_RESET                   (MXC_V_GCR_RSTR0_TIMER2_RESET << MXC_F_GCR_RSTR0_TIMER2_POS) /**< RSTR0_TIMER2_RESET Setting */
 #define MXC_V_GCR_RSTR0_TIMER2_RESET_DONE              ((uint32_t)0x0UL) /**< RSTR0_TIMER2_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_TIMER2_RESET_DONE              (MXC_V_GCR_RSTR0_TIMER2_RESET_DONE << MXC_F_GCR_RSTR0_TIMER2_POS) /**< RSTR0_TIMER2_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_TIMER2_BUSY                    ((uint32_t)0x1UL) /**< RSTR0_TIMER2_BUSY Value */
 #define MXC_S_GCR_RSTR0_TIMER2_BUSY                    (MXC_V_GCR_RSTR0_TIMER2_BUSY << MXC_F_GCR_RSTR0_TIMER2_POS) /**< RSTR0_TIMER2_BUSY Setting */

 #define MXC_F_GCR_RSTR0_UART0_POS                      11 /**< RSTR0_UART0 Position */
 #define MXC_F_GCR_RSTR0_UART0                          ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_UART0_POS)) /**< RSTR0_UART0 Mask */
 #define MXC_V_GCR_RSTR0_UART0_RFU                      ((uint32_t)0x0UL) /**< RSTR0_UART0_RFU Value */
 #define MXC_S_GCR_RSTR0_UART0_RFU                      (MXC_V_GCR_RSTR0_UART0_RFU << MXC_F_GCR_RSTR0_UART0_POS) /**< RSTR0_UART0_RFU Setting */
 #define MXC_V_GCR_RSTR0_UART0_RESET                    ((uint32_t)0x1UL) /**< RSTR0_UART0_RESET Value */
 #define MXC_S_GCR_RSTR0_UART0_RESET                    (MXC_V_GCR_RSTR0_UART0_RESET << MXC_F_GCR_RSTR0_UART0_POS) /**< RSTR0_UART0_RESET Setting */
 #define MXC_V_GCR_RSTR0_UART0_RESET_DONE               ((uint32_t)0x0UL) /**< RSTR0_UART0_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_UART0_RESET_DONE               (MXC_V_GCR_RSTR0_UART0_RESET_DONE << MXC_F_GCR_RSTR0_UART0_POS) /**< RSTR0_UART0_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_UART0_BUSY                     ((uint32_t)0x1UL) /**< RSTR0_UART0_BUSY Value */
 #define MXC_S_GCR_RSTR0_UART0_BUSY                     (MXC_V_GCR_RSTR0_UART0_BUSY << MXC_F_GCR_RSTR0_UART0_POS) /**< RSTR0_UART0_BUSY Setting */

 #define MXC_F_GCR_RSTR0_UART1_POS                      12 /**< RSTR0_UART1 Position */
 #define MXC_F_GCR_RSTR0_UART1                          ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_UART1_POS)) /**< RSTR0_UART1 Mask */
 #define MXC_V_GCR_RSTR0_UART1_RFU                      ((uint32_t)0x0UL) /**< RSTR0_UART1_RFU Value */
 #define MXC_S_GCR_RSTR0_UART1_RFU                      (MXC_V_GCR_RSTR0_UART1_RFU << MXC_F_GCR_RSTR0_UART1_POS) /**< RSTR0_UART1_RFU Setting */
 #define MXC_V_GCR_RSTR0_UART1_RESET                    ((uint32_t)0x1UL) /**< RSTR0_UART1_RESET Value */
 #define MXC_S_GCR_RSTR0_UART1_RESET                    (MXC_V_GCR_RSTR0_UART1_RESET << MXC_F_GCR_RSTR0_UART1_POS) /**< RSTR0_UART1_RESET Setting */
 #define MXC_V_GCR_RSTR0_UART1_RESET_DONE               ((uint32_t)0x0UL) /**< RSTR0_UART1_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_UART1_RESET_DONE               (MXC_V_GCR_RSTR0_UART1_RESET_DONE << MXC_F_GCR_RSTR0_UART1_POS) /**< RSTR0_UART1_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_UART1_BUSY                     ((uint32_t)0x1UL) /**< RSTR0_UART1_BUSY Value */
 #define MXC_S_GCR_RSTR0_UART1_BUSY                     (MXC_V_GCR_RSTR0_UART1_BUSY << MXC_F_GCR_RSTR0_UART1_POS) /**< RSTR0_UART1_BUSY Setting */

 #define MXC_F_GCR_RSTR0_SPI0_POS                       13 /**< RSTR0_SPI0 Position */
 #define MXC_F_GCR_RSTR0_SPI0                           ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_SPI0_POS)) /**< RSTR0_SPI0 Mask */
 #define MXC_V_GCR_RSTR0_SPI0_RFU                       ((uint32_t)0x0UL) /**< RSTR0_SPI0_RFU Value */
 #define MXC_S_GCR_RSTR0_SPI0_RFU                       (MXC_V_GCR_RSTR0_SPI0_RFU << MXC_F_GCR_RSTR0_SPI0_POS) /**< RSTR0_SPI0_RFU Setting */
 #define MXC_V_GCR_RSTR0_SPI0_RESET                     ((uint32_t)0x1UL) /**< RSTR0_SPI0_RESET Value */
 #define MXC_S_GCR_RSTR0_SPI0_RESET                     (MXC_V_GCR_RSTR0_SPI0_RESET << MXC_F_GCR_RSTR0_SPI0_POS) /**< RSTR0_SPI0_RESET Setting */
 #define MXC_V_GCR_RSTR0_SPI0_RESET_DONE                ((uint32_t)0x0UL) /**< RSTR0_SPI0_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_SPI0_RESET_DONE                (MXC_V_GCR_RSTR0_SPI0_RESET_DONE << MXC_F_GCR_RSTR0_SPI0_POS) /**< RSTR0_SPI0_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_SPI0_BUSY                      ((uint32_t)0x1UL) /**< RSTR0_SPI0_BUSY Value */
 #define MXC_S_GCR_RSTR0_SPI0_BUSY                      (MXC_V_GCR_RSTR0_SPI0_BUSY << MXC_F_GCR_RSTR0_SPI0_POS) /**< RSTR0_SPI0_BUSY Setting */

 #define MXC_F_GCR_RSTR0_SPI1_POS                       14 /**< RSTR0_SPI1 Position */
 #define MXC_F_GCR_RSTR0_SPI1                           ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_SPI1_POS)) /**< RSTR0_SPI1 Mask */
 #define MXC_V_GCR_RSTR0_SPI1_RFU                       ((uint32_t)0x0UL) /**< RSTR0_SPI1_RFU Value */
 #define MXC_S_GCR_RSTR0_SPI1_RFU                       (MXC_V_GCR_RSTR0_SPI1_RFU << MXC_F_GCR_RSTR0_SPI1_POS) /**< RSTR0_SPI1_RFU Setting */
 #define MXC_V_GCR_RSTR0_SPI1_RESET                     ((uint32_t)0x1UL) /**< RSTR0_SPI1_RESET Value */
 #define MXC_S_GCR_RSTR0_SPI1_RESET                     (MXC_V_GCR_RSTR0_SPI1_RESET << MXC_F_GCR_RSTR0_SPI1_POS) /**< RSTR0_SPI1_RESET Setting */
 #define MXC_V_GCR_RSTR0_SPI1_RESET_DONE                ((uint32_t)0x0UL) /**< RSTR0_SPI1_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_SPI1_RESET_DONE                (MXC_V_GCR_RSTR0_SPI1_RESET_DONE << MXC_F_GCR_RSTR0_SPI1_POS) /**< RSTR0_SPI1_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_SPI1_BUSY                      ((uint32_t)0x1UL) /**< RSTR0_SPI1_BUSY Value */
 #define MXC_S_GCR_RSTR0_SPI1_BUSY                      (MXC_V_GCR_RSTR0_SPI1_BUSY << MXC_F_GCR_RSTR0_SPI1_POS) /**< RSTR0_SPI1_BUSY Setting */

 #define MXC_F_GCR_RSTR0_I2C0_POS                       16 /**< RSTR0_I2C0 Position */
 #define MXC_F_GCR_RSTR0_I2C0                           ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_I2C0_POS)) /**< RSTR0_I2C0 Mask */
 #define MXC_V_GCR_RSTR0_I2C0_RFU                       ((uint32_t)0x0UL) /**< RSTR0_I2C0_RFU Value */
 #define MXC_S_GCR_RSTR0_I2C0_RFU                       (MXC_V_GCR_RSTR0_I2C0_RFU << MXC_F_GCR_RSTR0_I2C0_POS) /**< RSTR0_I2C0_RFU Setting */
 #define MXC_V_GCR_RSTR0_I2C0_RESET                     ((uint32_t)0x1UL) /**< RSTR0_I2C0_RESET Value */
 #define MXC_S_GCR_RSTR0_I2C0_RESET                     (MXC_V_GCR_RSTR0_I2C0_RESET << MXC_F_GCR_RSTR0_I2C0_POS) /**< RSTR0_I2C0_RESET Setting */
 #define MXC_V_GCR_RSTR0_I2C0_RESET_DONE                ((uint32_t)0x0UL) /**< RSTR0_I2C0_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_I2C0_RESET_DONE                (MXC_V_GCR_RSTR0_I2C0_RESET_DONE << MXC_F_GCR_RSTR0_I2C0_POS) /**< RSTR0_I2C0_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_I2C0_BUSY                      ((uint32_t)0x1UL) /**< RSTR0_I2C0_BUSY Value */
 #define MXC_S_GCR_RSTR0_I2C0_BUSY                      (MXC_V_GCR_RSTR0_I2C0_BUSY << MXC_F_GCR_RSTR0_I2C0_POS) /**< RSTR0_I2C0_BUSY Setting */

 #define MXC_F_GCR_RSTR0_RTC_POS                        17 /**< RSTR0_RTC Position */
 #define MXC_F_GCR_RSTR0_RTC                            ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_RTC_POS)) /**< RSTR0_RTC Mask */
 #define MXC_V_GCR_RSTR0_RTC_RFU                        ((uint32_t)0x0UL) /**< RSTR0_RTC_RFU Value */
 #define MXC_S_GCR_RSTR0_RTC_RFU                        (MXC_V_GCR_RSTR0_RTC_RFU << MXC_F_GCR_RSTR0_RTC_POS) /**< RSTR0_RTC_RFU Setting */
 #define MXC_V_GCR_RSTR0_RTC_RESET                      ((uint32_t)0x1UL) /**< RSTR0_RTC_RESET Value */
 #define MXC_S_GCR_RSTR0_RTC_RESET                      (MXC_V_GCR_RSTR0_RTC_RESET << MXC_F_GCR_RSTR0_RTC_POS) /**< RSTR0_RTC_RESET Setting */
 #define MXC_V_GCR_RSTR0_RTC_RESET_DONE                 ((uint32_t)0x0UL) /**< RSTR0_RTC_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_RTC_RESET_DONE                 (MXC_V_GCR_RSTR0_RTC_RESET_DONE << MXC_F_GCR_RSTR0_RTC_POS) /**< RSTR0_RTC_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_RTC_BUSY                       ((uint32_t)0x1UL) /**< RSTR0_RTC_BUSY Value */
 #define MXC_S_GCR_RSTR0_RTC_BUSY                       (MXC_V_GCR_RSTR0_RTC_BUSY << MXC_F_GCR_RSTR0_RTC_POS) /**< RSTR0_RTC_BUSY Setting */

 #define MXC_F_GCR_RSTR0_SRST_POS                       29 /**< RSTR0_SRST Position */
 #define MXC_F_GCR_RSTR0_SRST                           ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_SRST_POS)) /**< RSTR0_SRST Mask */
 #define MXC_V_GCR_RSTR0_SRST_RFU                       ((uint32_t)0x0UL) /**< RSTR0_SRST_RFU Value */
 #define MXC_S_GCR_RSTR0_SRST_RFU                       (MXC_V_GCR_RSTR0_SRST_RFU << MXC_F_GCR_RSTR0_SRST_POS) /**< RSTR0_SRST_RFU Setting */
 #define MXC_V_GCR_RSTR0_SRST_RESET                     ((uint32_t)0x1UL) /**< RSTR0_SRST_RESET Value */
 #define MXC_S_GCR_RSTR0_SRST_RESET                     (MXC_V_GCR_RSTR0_SRST_RESET << MXC_F_GCR_RSTR0_SRST_POS) /**< RSTR0_SRST_RESET Setting */
 #define MXC_V_GCR_RSTR0_SRST_RESET_DONE                ((uint32_t)0x0UL) /**< RSTR0_SRST_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_SRST_RESET_DONE                (MXC_V_GCR_RSTR0_SRST_RESET_DONE << MXC_F_GCR_RSTR0_SRST_POS) /**< RSTR0_SRST_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_SRST_BUSY                      ((uint32_t)0x1UL) /**< RSTR0_SRST_BUSY Value */
 #define MXC_S_GCR_RSTR0_SRST_BUSY                      (MXC_V_GCR_RSTR0_SRST_BUSY << MXC_F_GCR_RSTR0_SRST_POS) /**< RSTR0_SRST_BUSY Setting */

 #define MXC_F_GCR_RSTR0_PRST_POS                       30 /**< RSTR0_PRST Position */
 #define MXC_F_GCR_RSTR0_PRST                           ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_PRST_POS)) /**< RSTR0_PRST Mask */
 #define MXC_V_GCR_RSTR0_PRST_RFU                       ((uint32_t)0x0UL) /**< RSTR0_PRST_RFU Value */
 #define MXC_S_GCR_RSTR0_PRST_RFU                       (MXC_V_GCR_RSTR0_PRST_RFU << MXC_F_GCR_RSTR0_PRST_POS) /**< RSTR0_PRST_RFU Setting */
 #define MXC_V_GCR_RSTR0_PRST_RESET                     ((uint32_t)0x1UL) /**< RSTR0_PRST_RESET Value */
 #define MXC_S_GCR_RSTR0_PRST_RESET                     (MXC_V_GCR_RSTR0_PRST_RESET << MXC_F_GCR_RSTR0_PRST_POS) /**< RSTR0_PRST_RESET Setting */
 #define MXC_V_GCR_RSTR0_PRST_RESET_DONE                ((uint32_t)0x0UL) /**< RSTR0_PRST_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_PRST_RESET_DONE                (MXC_V_GCR_RSTR0_PRST_RESET_DONE << MXC_F_GCR_RSTR0_PRST_POS) /**< RSTR0_PRST_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_PRST_BUSY                      ((uint32_t)0x1UL) /**< RSTR0_PRST_BUSY Value */
 #define MXC_S_GCR_RSTR0_PRST_BUSY                      (MXC_V_GCR_RSTR0_PRST_BUSY << MXC_F_GCR_RSTR0_PRST_POS) /**< RSTR0_PRST_BUSY Setting */

 #define MXC_F_GCR_RSTR0_SYSTEM_POS                     31 /**< RSTR0_SYSTEM Position */
 #define MXC_F_GCR_RSTR0_SYSTEM                         ((uint32_t)(0x1UL << MXC_F_GCR_RSTR0_SYSTEM_POS)) /**< RSTR0_SYSTEM Mask */
 #define MXC_V_GCR_RSTR0_SYSTEM_RFU                     ((uint32_t)0x0UL) /**< RSTR0_SYSTEM_RFU Value */
 #define MXC_S_GCR_RSTR0_SYSTEM_RFU                     (MXC_V_GCR_RSTR0_SYSTEM_RFU << MXC_F_GCR_RSTR0_SYSTEM_POS) /**< RSTR0_SYSTEM_RFU Setting */
 #define MXC_V_GCR_RSTR0_SYSTEM_RESET                   ((uint32_t)0x1UL) /**< RSTR0_SYSTEM_RESET Value */
 #define MXC_S_GCR_RSTR0_SYSTEM_RESET                   (MXC_V_GCR_RSTR0_SYSTEM_RESET << MXC_F_GCR_RSTR0_SYSTEM_POS) /**< RSTR0_SYSTEM_RESET Setting */
 #define MXC_V_GCR_RSTR0_SYSTEM_RESET_DONE              ((uint32_t)0x0UL) /**< RSTR0_SYSTEM_RESET_DONE Value */
 #define MXC_S_GCR_RSTR0_SYSTEM_RESET_DONE              (MXC_V_GCR_RSTR0_SYSTEM_RESET_DONE << MXC_F_GCR_RSTR0_SYSTEM_POS) /**< RSTR0_SYSTEM_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR0_SYSTEM_BUSY                    ((uint32_t)0x1UL) /**< RSTR0_SYSTEM_BUSY Value */
 #define MXC_S_GCR_RSTR0_SYSTEM_BUSY                    (MXC_V_GCR_RSTR0_SYSTEM_BUSY << MXC_F_GCR_RSTR0_SYSTEM_POS) /**< RSTR0_SYSTEM_BUSY Setting */

/**@} end of group GCR_RSTR0_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_CLKCN GCR_CLKCN
 * @brief    Clock Control.
 * @{
 */
 #define MXC_F_GCR_CLKCN_PSC_POS                        6 /**< CLKCN_PSC Position */
 #define MXC_F_GCR_CLKCN_PSC                            ((uint32_t)(0x7UL << MXC_F_GCR_CLKCN_PSC_POS)) /**< CLKCN_PSC Mask */
 #define MXC_V_GCR_CLKCN_PSC_DIV1                       ((uint32_t)0x0UL) /**< CLKCN_PSC_DIV1 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV1                       (MXC_V_GCR_CLKCN_PSC_DIV1 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV1 Setting */
 #define MXC_V_GCR_CLKCN_PSC_DIV2                       ((uint32_t)0x1UL) /**< CLKCN_PSC_DIV2 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV2                       (MXC_V_GCR_CLKCN_PSC_DIV2 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV2 Setting */
 #define MXC_V_GCR_CLKCN_PSC_DIV4                       ((uint32_t)0x2UL) /**< CLKCN_PSC_DIV4 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV4                       (MXC_V_GCR_CLKCN_PSC_DIV4 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV4 Setting */
 #define MXC_V_GCR_CLKCN_PSC_DIV8                       ((uint32_t)0x3UL) /**< CLKCN_PSC_DIV8 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV8                       (MXC_V_GCR_CLKCN_PSC_DIV8 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV8 Setting */
 #define MXC_V_GCR_CLKCN_PSC_DIV16                      ((uint32_t)0x4UL) /**< CLKCN_PSC_DIV16 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV16                      (MXC_V_GCR_CLKCN_PSC_DIV16 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV16 Setting */
 #define MXC_V_GCR_CLKCN_PSC_DIV32                      ((uint32_t)0x5UL) /**< CLKCN_PSC_DIV32 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV32                      (MXC_V_GCR_CLKCN_PSC_DIV32 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV32 Setting */
 #define MXC_V_GCR_CLKCN_PSC_DIV64                      ((uint32_t)0x6UL) /**< CLKCN_PSC_DIV64 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV64                      (MXC_V_GCR_CLKCN_PSC_DIV64 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV64 Setting */
 #define MXC_V_GCR_CLKCN_PSC_DIV128                     ((uint32_t)0x7UL) /**< CLKCN_PSC_DIV128 Value */
 #define MXC_S_GCR_CLKCN_PSC_DIV128                     (MXC_V_GCR_CLKCN_PSC_DIV128 << MXC_F_GCR_CLKCN_PSC_POS) /**< CLKCN_PSC_DIV128 Setting */

 #define MXC_F_GCR_CLKCN_CLKSEL_POS                     9 /**< CLKCN_CLKSEL Position */
 #define MXC_F_GCR_CLKCN_CLKSEL                         ((uint32_t)(0x7UL << MXC_F_GCR_CLKCN_CLKSEL_POS)) /**< CLKCN_CLKSEL Mask */
 #define MXC_V_GCR_CLKCN_CLKSEL_HIRC                    ((uint32_t)0x0UL) /**< CLKCN_CLKSEL_HIRC Value */
 #define MXC_S_GCR_CLKCN_CLKSEL_HIRC                    (MXC_V_GCR_CLKCN_CLKSEL_HIRC << MXC_F_GCR_CLKCN_CLKSEL_POS) /**< CLKCN_CLKSEL_HIRC Setting */
 #define MXC_V_GCR_CLKCN_CLKSEL_NANORING                ((uint32_t)0x3UL) /**< CLKCN_CLKSEL_NANORING Value */
 #define MXC_S_GCR_CLKCN_CLKSEL_NANORING                (MXC_V_GCR_CLKCN_CLKSEL_NANORING << MXC_F_GCR_CLKCN_CLKSEL_POS) /**< CLKCN_CLKSEL_NANORING Setting */
 #define MXC_V_GCR_CLKCN_CLKSEL_HFXIN                   ((uint32_t)0x6UL) /**< CLKCN_CLKSEL_HFXIN Value */
 #define MXC_S_GCR_CLKCN_CLKSEL_HFXIN                   (MXC_V_GCR_CLKCN_CLKSEL_HFXIN << MXC_F_GCR_CLKCN_CLKSEL_POS) /**< CLKCN_CLKSEL_HFXIN Setting */

 #define MXC_F_GCR_CLKCN_CKRDY_POS                      13 /**< CLKCN_CKRDY Position */
 #define MXC_F_GCR_CLKCN_CKRDY                          ((uint32_t)(0x1UL << MXC_F_GCR_CLKCN_CKRDY_POS)) /**< CLKCN_CKRDY Mask */
 #define MXC_V_GCR_CLKCN_CKRDY_BUSY                     ((uint32_t)0x0UL) /**< CLKCN_CKRDY_BUSY Value */
 #define MXC_S_GCR_CLKCN_CKRDY_BUSY                     (MXC_V_GCR_CLKCN_CKRDY_BUSY << MXC_F_GCR_CLKCN_CKRDY_POS) /**< CLKCN_CKRDY_BUSY Setting */
 #define MXC_V_GCR_CLKCN_CKRDY_READY                    ((uint32_t)0x1UL) /**< CLKCN_CKRDY_READY Value */
 #define MXC_S_GCR_CLKCN_CKRDY_READY                    (MXC_V_GCR_CLKCN_CKRDY_READY << MXC_F_GCR_CLKCN_CKRDY_POS) /**< CLKCN_CKRDY_READY Setting */

 #define MXC_F_GCR_CLKCN_X32K_EN_POS                    17 /**< CLKCN_X32K_EN Position */
 #define MXC_F_GCR_CLKCN_X32K_EN                        ((uint32_t)(0x1UL << MXC_F_GCR_CLKCN_X32K_EN_POS)) /**< CLKCN_X32K_EN Mask */
 #define MXC_V_GCR_CLKCN_X32K_EN_DIS                    ((uint32_t)0x0UL) /**< CLKCN_X32K_EN_DIS Value */
 #define MXC_S_GCR_CLKCN_X32K_EN_DIS                    (MXC_V_GCR_CLKCN_X32K_EN_DIS << MXC_F_GCR_CLKCN_X32K_EN_POS) /**< CLKCN_X32K_EN_DIS Setting */
 #define MXC_V_GCR_CLKCN_X32K_EN_EN                     ((uint32_t)0x1UL) /**< CLKCN_X32K_EN_EN Value */
 #define MXC_S_GCR_CLKCN_X32K_EN_EN                     (MXC_V_GCR_CLKCN_X32K_EN_EN << MXC_F_GCR_CLKCN_X32K_EN_POS) /**< CLKCN_X32K_EN_EN Setting */

 #define MXC_F_GCR_CLKCN_HIRC_EN_POS                    18 /**< CLKCN_HIRC_EN Position */
 #define MXC_F_GCR_CLKCN_HIRC_EN                        ((uint32_t)(0x1UL << MXC_F_GCR_CLKCN_HIRC_EN_POS)) /**< CLKCN_HIRC_EN Mask */
 #define MXC_V_GCR_CLKCN_HIRC_EN_DIS                    ((uint32_t)0x0UL) /**< CLKCN_HIRC_EN_DIS Value */
 #define MXC_S_GCR_CLKCN_HIRC_EN_DIS                    (MXC_V_GCR_CLKCN_HIRC_EN_DIS << MXC_F_GCR_CLKCN_HIRC_EN_POS) /**< CLKCN_HIRC_EN_DIS Setting */
 #define MXC_V_GCR_CLKCN_HIRC_EN_EN                     ((uint32_t)0x1UL) /**< CLKCN_HIRC_EN_EN Value */
 #define MXC_S_GCR_CLKCN_HIRC_EN_EN                     (MXC_V_GCR_CLKCN_HIRC_EN_EN << MXC_F_GCR_CLKCN_HIRC_EN_POS) /**< CLKCN_HIRC_EN_EN Setting */

 #define MXC_F_GCR_CLKCN_X32K_RDY_POS                   25 /**< CLKCN_X32K_RDY Position */
 #define MXC_F_GCR_CLKCN_X32K_RDY                       ((uint32_t)(0x1UL << MXC_F_GCR_CLKCN_X32K_RDY_POS)) /**< CLKCN_X32K_RDY Mask */
 #define MXC_V_GCR_CLKCN_X32K_RDY_NOT                   ((uint32_t)0x0UL) /**< CLKCN_X32K_RDY_NOT Value */
 #define MXC_S_GCR_CLKCN_X32K_RDY_NOT                   (MXC_V_GCR_CLKCN_X32K_RDY_NOT << MXC_F_GCR_CLKCN_X32K_RDY_POS) /**< CLKCN_X32K_RDY_NOT Setting */
 #define MXC_V_GCR_CLKCN_X32K_RDY_READY                 ((uint32_t)0x1UL) /**< CLKCN_X32K_RDY_READY Value */
 #define MXC_S_GCR_CLKCN_X32K_RDY_READY                 (MXC_V_GCR_CLKCN_X32K_RDY_READY << MXC_F_GCR_CLKCN_X32K_RDY_POS) /**< CLKCN_X32K_RDY_READY Setting */

 #define MXC_F_GCR_CLKCN_HIRC_RDY_POS                   26 /**< CLKCN_HIRC_RDY Position */
 #define MXC_F_GCR_CLKCN_HIRC_RDY                       ((uint32_t)(0x1UL << MXC_F_GCR_CLKCN_HIRC_RDY_POS)) /**< CLKCN_HIRC_RDY Mask */
 #define MXC_V_GCR_CLKCN_HIRC_RDY_NOT                   ((uint32_t)0x0UL) /**< CLKCN_HIRC_RDY_NOT Value */
 #define MXC_S_GCR_CLKCN_HIRC_RDY_NOT                   (MXC_V_GCR_CLKCN_HIRC_RDY_NOT << MXC_F_GCR_CLKCN_HIRC_RDY_POS) /**< CLKCN_HIRC_RDY_NOT Setting */
 #define MXC_V_GCR_CLKCN_HIRC_RDY_READY                 ((uint32_t)0x1UL) /**< CLKCN_HIRC_RDY_READY Value */
 #define MXC_S_GCR_CLKCN_HIRC_RDY_READY                 (MXC_V_GCR_CLKCN_HIRC_RDY_READY << MXC_F_GCR_CLKCN_HIRC_RDY_POS) /**< CLKCN_HIRC_RDY_READY Setting */

 #define MXC_F_GCR_CLKCN_LIRC8K_RDY_POS                 29 /**< CLKCN_LIRC8K_RDY Position */
 #define MXC_F_GCR_CLKCN_LIRC8K_RDY                     ((uint32_t)(0x1UL << MXC_F_GCR_CLKCN_LIRC8K_RDY_POS)) /**< CLKCN_LIRC8K_RDY Mask */
 #define MXC_V_GCR_CLKCN_LIRC8K_RDY_NOT                 ((uint32_t)0x0UL) /**< CLKCN_LIRC8K_RDY_NOT Value */
 #define MXC_S_GCR_CLKCN_LIRC8K_RDY_NOT                 (MXC_V_GCR_CLKCN_LIRC8K_RDY_NOT << MXC_F_GCR_CLKCN_LIRC8K_RDY_POS) /**< CLKCN_LIRC8K_RDY_NOT Setting */
 #define MXC_V_GCR_CLKCN_LIRC8K_RDY_READY               ((uint32_t)0x1UL) /**< CLKCN_LIRC8K_RDY_READY Value */
 #define MXC_S_GCR_CLKCN_LIRC8K_RDY_READY               (MXC_V_GCR_CLKCN_LIRC8K_RDY_READY << MXC_F_GCR_CLKCN_LIRC8K_RDY_POS) /**< CLKCN_LIRC8K_RDY_READY Setting */

/**@} end of group GCR_CLKCN_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_PM GCR_PM
 * @brief    Power Management.
 * @{
 */
 #define MXC_F_GCR_PM_MODE_POS                          0 /**< PM_MODE Position */
 #define MXC_F_GCR_PM_MODE                              ((uint32_t)(0x7UL << MXC_F_GCR_PM_MODE_POS)) /**< PM_MODE Mask */
 #define MXC_V_GCR_PM_MODE_ACTIVE                       ((uint32_t)0x0UL) /**< PM_MODE_ACTIVE Value */
 #define MXC_S_GCR_PM_MODE_ACTIVE                       (MXC_V_GCR_PM_MODE_ACTIVE << MXC_F_GCR_PM_MODE_POS) /**< PM_MODE_ACTIVE Setting */
 #define MXC_V_GCR_PM_MODE_SHUTDOWN                     ((uint32_t)0x3UL) /**< PM_MODE_SHUTDOWN Value */
 #define MXC_S_GCR_PM_MODE_SHUTDOWN                     (MXC_V_GCR_PM_MODE_SHUTDOWN << MXC_F_GCR_PM_MODE_POS) /**< PM_MODE_SHUTDOWN Setting */
 #define MXC_V_GCR_PM_MODE_BACKUP                       ((uint32_t)0x4UL) /**< PM_MODE_BACKUP Value */
 #define MXC_S_GCR_PM_MODE_BACKUP                       (MXC_V_GCR_PM_MODE_BACKUP << MXC_F_GCR_PM_MODE_POS) /**< PM_MODE_BACKUP Setting */

 #define MXC_F_GCR_PM_GPIOWKEN_POS                      4 /**< PM_GPIOWKEN Position */
 #define MXC_F_GCR_PM_GPIOWKEN                          ((uint32_t)(0x1UL << MXC_F_GCR_PM_GPIOWKEN_POS)) /**< PM_GPIOWKEN Mask */
 #define MXC_V_GCR_PM_GPIOWKEN_DIS                      ((uint32_t)0x0UL) /**< PM_GPIOWKEN_DIS Value */
 #define MXC_S_GCR_PM_GPIOWKEN_DIS                      (MXC_V_GCR_PM_GPIOWKEN_DIS << MXC_F_GCR_PM_GPIOWKEN_POS) /**< PM_GPIOWKEN_DIS Setting */
 #define MXC_V_GCR_PM_GPIOWKEN_EN                       ((uint32_t)0x1UL) /**< PM_GPIOWKEN_EN Value */
 #define MXC_S_GCR_PM_GPIOWKEN_EN                       (MXC_V_GCR_PM_GPIOWKEN_EN << MXC_F_GCR_PM_GPIOWKEN_POS) /**< PM_GPIOWKEN_EN Setting */

 #define MXC_F_GCR_PM_RTCWKEN_POS                       5 /**< PM_RTCWKEN Position */
 #define MXC_F_GCR_PM_RTCWKEN                           ((uint32_t)(0x1UL << MXC_F_GCR_PM_RTCWKEN_POS)) /**< PM_RTCWKEN Mask */
 #define MXC_V_GCR_PM_RTCWKEN_DIS                       ((uint32_t)0x0UL) /**< PM_RTCWKEN_DIS Value */
 #define MXC_S_GCR_PM_RTCWKEN_DIS                       (MXC_V_GCR_PM_RTCWKEN_DIS << MXC_F_GCR_PM_RTCWKEN_POS) /**< PM_RTCWKEN_DIS Setting */
 #define MXC_V_GCR_PM_RTCWKEN_EN                        ((uint32_t)0x1UL) /**< PM_RTCWKEN_EN Value */
 #define MXC_S_GCR_PM_RTCWKEN_EN                        (MXC_V_GCR_PM_RTCWKEN_EN << MXC_F_GCR_PM_RTCWKEN_POS) /**< PM_RTCWKEN_EN Setting */

 #define MXC_F_GCR_PM_HIRCPD_POS                        15 /**< PM_HIRCPD Position */
 #define MXC_F_GCR_PM_HIRCPD                            ((uint32_t)(0x1UL << MXC_F_GCR_PM_HIRCPD_POS)) /**< PM_HIRCPD Mask */
 #define MXC_V_GCR_PM_HIRCPD_ACTIVE                     ((uint32_t)0x0UL) /**< PM_HIRCPD_ACTIVE Value */
 #define MXC_S_GCR_PM_HIRCPD_ACTIVE                     (MXC_V_GCR_PM_HIRCPD_ACTIVE << MXC_F_GCR_PM_HIRCPD_POS) /**< PM_HIRCPD_ACTIVE Setting */
 #define MXC_V_GCR_PM_HIRCPD_DEEPSLEEP                  ((uint32_t)0x1UL) /**< PM_HIRCPD_DEEPSLEEP Value */
 #define MXC_S_GCR_PM_HIRCPD_DEEPSLEEP                  (MXC_V_GCR_PM_HIRCPD_DEEPSLEEP << MXC_F_GCR_PM_HIRCPD_POS) /**< PM_HIRCPD_DEEPSLEEP Setting */

/**@} end of group GCR_PM_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_PCKDIV GCR_PCKDIV
 * @brief    Peripheral Clock Divider.
 * @{
 */
 #define MXC_F_GCR_PCKDIV_AONCD_POS                     0 /**< PCKDIV_AONCD Position */
 #define MXC_F_GCR_PCKDIV_AONCD                         ((uint32_t)(0x3UL << MXC_F_GCR_PCKDIV_AONCD_POS)) /**< PCKDIV_AONCD Mask */
 #define MXC_V_GCR_PCKDIV_AONCD_DIV_4                   ((uint32_t)0x0UL) /**< PCKDIV_AONCD_DIV_4 Value */
 #define MXC_S_GCR_PCKDIV_AONCD_DIV_4                   (MXC_V_GCR_PCKDIV_AONCD_DIV_4 << MXC_F_GCR_PCKDIV_AONCD_POS) /**< PCKDIV_AONCD_DIV_4 Setting */
 #define MXC_V_GCR_PCKDIV_AONCD_DIV_8                   ((uint32_t)0x1UL) /**< PCKDIV_AONCD_DIV_8 Value */
 #define MXC_S_GCR_PCKDIV_AONCD_DIV_8                   (MXC_V_GCR_PCKDIV_AONCD_DIV_8 << MXC_F_GCR_PCKDIV_AONCD_POS) /**< PCKDIV_AONCD_DIV_8 Setting */
 #define MXC_V_GCR_PCKDIV_AONCD_DIV_16                  ((uint32_t)0x2UL) /**< PCKDIV_AONCD_DIV_16 Value */
 #define MXC_S_GCR_PCKDIV_AONCD_DIV_16                  (MXC_V_GCR_PCKDIV_AONCD_DIV_16 << MXC_F_GCR_PCKDIV_AONCD_POS) /**< PCKDIV_AONCD_DIV_16 Setting */
 #define MXC_V_GCR_PCKDIV_AONCD_DIV_32                  ((uint32_t)0x3UL) /**< PCKDIV_AONCD_DIV_32 Value */
 #define MXC_S_GCR_PCKDIV_AONCD_DIV_32                  (MXC_V_GCR_PCKDIV_AONCD_DIV_32 << MXC_F_GCR_PCKDIV_AONCD_POS) /**< PCKDIV_AONCD_DIV_32 Setting */

/**@} end of group GCR_PCKDIV_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_PERCKCN0 GCR_PERCKCN0
 * @brief    Peripheral Clock Disable.
 * @{
 */
 #define MXC_F_GCR_PERCKCN0_GPIO0D_POS                  0 /**< PERCKCN0_GPIO0D Position */
 #define MXC_F_GCR_PERCKCN0_GPIO0D                      ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_GPIO0D_POS)) /**< PERCKCN0_GPIO0D Mask */
 #define MXC_V_GCR_PERCKCN0_GPIO0D_EN                   ((uint32_t)0x0UL) /**< PERCKCN0_GPIO0D_EN Value */
 #define MXC_S_GCR_PERCKCN0_GPIO0D_EN                   (MXC_V_GCR_PERCKCN0_GPIO0D_EN << MXC_F_GCR_PERCKCN0_GPIO0D_POS) /**< PERCKCN0_GPIO0D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_GPIO0D_DIS                  ((uint32_t)0x1UL) /**< PERCKCN0_GPIO0D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_GPIO0D_DIS                  (MXC_V_GCR_PERCKCN0_GPIO0D_DIS << MXC_F_GCR_PERCKCN0_GPIO0D_POS) /**< PERCKCN0_GPIO0D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_DMAD_POS                    5 /**< PERCKCN0_DMAD Position */
 #define MXC_F_GCR_PERCKCN0_DMAD                        ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_DMAD_POS)) /**< PERCKCN0_DMAD Mask */
 #define MXC_V_GCR_PERCKCN0_DMAD_EN                     ((uint32_t)0x0UL) /**< PERCKCN0_DMAD_EN Value */
 #define MXC_S_GCR_PERCKCN0_DMAD_EN                     (MXC_V_GCR_PERCKCN0_DMAD_EN << MXC_F_GCR_PERCKCN0_DMAD_POS) /**< PERCKCN0_DMAD_EN Setting */
 #define MXC_V_GCR_PERCKCN0_DMAD_DIS                    ((uint32_t)0x1UL) /**< PERCKCN0_DMAD_DIS Value */
 #define MXC_S_GCR_PERCKCN0_DMAD_DIS                    (MXC_V_GCR_PERCKCN0_DMAD_DIS << MXC_F_GCR_PERCKCN0_DMAD_POS) /**< PERCKCN0_DMAD_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_SPI0D_POS                   6 /**< PERCKCN0_SPI0D Position */
 #define MXC_F_GCR_PERCKCN0_SPI0D                       ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_SPI0D_POS)) /**< PERCKCN0_SPI0D Mask */
 #define MXC_V_GCR_PERCKCN0_SPI0D_EN                    ((uint32_t)0x0UL) /**< PERCKCN0_SPI0D_EN Value */
 #define MXC_S_GCR_PERCKCN0_SPI0D_EN                    (MXC_V_GCR_PERCKCN0_SPI0D_EN << MXC_F_GCR_PERCKCN0_SPI0D_POS) /**< PERCKCN0_SPI0D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_SPI0D_DIS                   ((uint32_t)0x1UL) /**< PERCKCN0_SPI0D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_SPI0D_DIS                   (MXC_V_GCR_PERCKCN0_SPI0D_DIS << MXC_F_GCR_PERCKCN0_SPI0D_POS) /**< PERCKCN0_SPI0D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_SPI1D_POS                   7 /**< PERCKCN0_SPI1D Position */
 #define MXC_F_GCR_PERCKCN0_SPI1D                       ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_SPI1D_POS)) /**< PERCKCN0_SPI1D Mask */
 #define MXC_V_GCR_PERCKCN0_SPI1D_EN                    ((uint32_t)0x0UL) /**< PERCKCN0_SPI1D_EN Value */
 #define MXC_S_GCR_PERCKCN0_SPI1D_EN                    (MXC_V_GCR_PERCKCN0_SPI1D_EN << MXC_F_GCR_PERCKCN0_SPI1D_POS) /**< PERCKCN0_SPI1D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_SPI1D_DIS                   ((uint32_t)0x1UL) /**< PERCKCN0_SPI1D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_SPI1D_DIS                   (MXC_V_GCR_PERCKCN0_SPI1D_DIS << MXC_F_GCR_PERCKCN0_SPI1D_POS) /**< PERCKCN0_SPI1D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_UART0D_POS                  9 /**< PERCKCN0_UART0D Position */
 #define MXC_F_GCR_PERCKCN0_UART0D                      ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_UART0D_POS)) /**< PERCKCN0_UART0D Mask */
 #define MXC_V_GCR_PERCKCN0_UART0D_EN                   ((uint32_t)0x0UL) /**< PERCKCN0_UART0D_EN Value */
 #define MXC_S_GCR_PERCKCN0_UART0D_EN                   (MXC_V_GCR_PERCKCN0_UART0D_EN << MXC_F_GCR_PERCKCN0_UART0D_POS) /**< PERCKCN0_UART0D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_UART0D_DIS                  ((uint32_t)0x1UL) /**< PERCKCN0_UART0D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_UART0D_DIS                  (MXC_V_GCR_PERCKCN0_UART0D_DIS << MXC_F_GCR_PERCKCN0_UART0D_POS) /**< PERCKCN0_UART0D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_UART1D_POS                  10 /**< PERCKCN0_UART1D Position */
 #define MXC_F_GCR_PERCKCN0_UART1D                      ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_UART1D_POS)) /**< PERCKCN0_UART1D Mask */
 #define MXC_V_GCR_PERCKCN0_UART1D_EN                   ((uint32_t)0x0UL) /**< PERCKCN0_UART1D_EN Value */
 #define MXC_S_GCR_PERCKCN0_UART1D_EN                   (MXC_V_GCR_PERCKCN0_UART1D_EN << MXC_F_GCR_PERCKCN0_UART1D_POS) /**< PERCKCN0_UART1D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_UART1D_DIS                  ((uint32_t)0x1UL) /**< PERCKCN0_UART1D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_UART1D_DIS                  (MXC_V_GCR_PERCKCN0_UART1D_DIS << MXC_F_GCR_PERCKCN0_UART1D_POS) /**< PERCKCN0_UART1D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_I2C0D_POS                   13 /**< PERCKCN0_I2C0D Position */
 #define MXC_F_GCR_PERCKCN0_I2C0D                       ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_I2C0D_POS)) /**< PERCKCN0_I2C0D Mask */
 #define MXC_V_GCR_PERCKCN0_I2C0D_EN                    ((uint32_t)0x0UL) /**< PERCKCN0_I2C0D_EN Value */
 #define MXC_S_GCR_PERCKCN0_I2C0D_EN                    (MXC_V_GCR_PERCKCN0_I2C0D_EN << MXC_F_GCR_PERCKCN0_I2C0D_POS) /**< PERCKCN0_I2C0D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_I2C0D_DIS                   ((uint32_t)0x1UL) /**< PERCKCN0_I2C0D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_I2C0D_DIS                   (MXC_V_GCR_PERCKCN0_I2C0D_DIS << MXC_F_GCR_PERCKCN0_I2C0D_POS) /**< PERCKCN0_I2C0D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_T0D_POS                     15 /**< PERCKCN0_T0D Position */
 #define MXC_F_GCR_PERCKCN0_T0D                         ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_T0D_POS)) /**< PERCKCN0_T0D Mask */
 #define MXC_V_GCR_PERCKCN0_T0D_EN                      ((uint32_t)0x0UL) /**< PERCKCN0_T0D_EN Value */
 #define MXC_S_GCR_PERCKCN0_T0D_EN                      (MXC_V_GCR_PERCKCN0_T0D_EN << MXC_F_GCR_PERCKCN0_T0D_POS) /**< PERCKCN0_T0D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_T0D_DIS                     ((uint32_t)0x1UL) /**< PERCKCN0_T0D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_T0D_DIS                     (MXC_V_GCR_PERCKCN0_T0D_DIS << MXC_F_GCR_PERCKCN0_T0D_POS) /**< PERCKCN0_T0D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_T1D_POS                     16 /**< PERCKCN0_T1D Position */
 #define MXC_F_GCR_PERCKCN0_T1D                         ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_T1D_POS)) /**< PERCKCN0_T1D Mask */
 #define MXC_V_GCR_PERCKCN0_T1D_EN                      ((uint32_t)0x0UL) /**< PERCKCN0_T1D_EN Value */
 #define MXC_S_GCR_PERCKCN0_T1D_EN                      (MXC_V_GCR_PERCKCN0_T1D_EN << MXC_F_GCR_PERCKCN0_T1D_POS) /**< PERCKCN0_T1D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_T1D_DIS                     ((uint32_t)0x1UL) /**< PERCKCN0_T1D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_T1D_DIS                     (MXC_V_GCR_PERCKCN0_T1D_DIS << MXC_F_GCR_PERCKCN0_T1D_POS) /**< PERCKCN0_T1D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_T2D_POS                     17 /**< PERCKCN0_T2D Position */
 #define MXC_F_GCR_PERCKCN0_T2D                         ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_T2D_POS)) /**< PERCKCN0_T2D Mask */
 #define MXC_V_GCR_PERCKCN0_T2D_EN                      ((uint32_t)0x0UL) /**< PERCKCN0_T2D_EN Value */
 #define MXC_S_GCR_PERCKCN0_T2D_EN                      (MXC_V_GCR_PERCKCN0_T2D_EN << MXC_F_GCR_PERCKCN0_T2D_POS) /**< PERCKCN0_T2D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_T2D_DIS                     ((uint32_t)0x1UL) /**< PERCKCN0_T2D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_T2D_DIS                     (MXC_V_GCR_PERCKCN0_T2D_DIS << MXC_F_GCR_PERCKCN0_T2D_POS) /**< PERCKCN0_T2D_DIS Setting */

 #define MXC_F_GCR_PERCKCN0_I2C1D_POS                   28 /**< PERCKCN0_I2C1D Position */
 #define MXC_F_GCR_PERCKCN0_I2C1D                       ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN0_I2C1D_POS)) /**< PERCKCN0_I2C1D Mask */
 #define MXC_V_GCR_PERCKCN0_I2C1D_EN                    ((uint32_t)0x0UL) /**< PERCKCN0_I2C1D_EN Value */
 #define MXC_S_GCR_PERCKCN0_I2C1D_EN                    (MXC_V_GCR_PERCKCN0_I2C1D_EN << MXC_F_GCR_PERCKCN0_I2C1D_POS) /**< PERCKCN0_I2C1D_EN Setting */
 #define MXC_V_GCR_PERCKCN0_I2C1D_DIS                   ((uint32_t)0x1UL) /**< PERCKCN0_I2C1D_DIS Value */
 #define MXC_S_GCR_PERCKCN0_I2C1D_DIS                   (MXC_V_GCR_PERCKCN0_I2C1D_DIS << MXC_F_GCR_PERCKCN0_I2C1D_POS) /**< PERCKCN0_I2C1D_DIS Setting */

/**@} end of group GCR_PERCKCN0_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_MEMCKCN GCR_MEMCKCN
 * @brief    Memory Clock Control Register.
 * @{
 */
 #define MXC_F_GCR_MEMCKCN_FWS_POS                      0 /**< MEMCKCN_FWS Position */
 #define MXC_F_GCR_MEMCKCN_FWS                          ((uint32_t)(0x7UL << MXC_F_GCR_MEMCKCN_FWS_POS)) /**< MEMCKCN_FWS Mask */

 #define MXC_F_GCR_MEMCKCN_SYSRAM0LS_POS                8 /**< MEMCKCN_SYSRAM0LS Position */
 #define MXC_F_GCR_MEMCKCN_SYSRAM0LS                    ((uint32_t)(0x1UL << MXC_F_GCR_MEMCKCN_SYSRAM0LS_POS)) /**< MEMCKCN_SYSRAM0LS Mask */
 #define MXC_V_GCR_MEMCKCN_SYSRAM0LS_ACTIVE             ((uint32_t)0x0UL) /**< MEMCKCN_SYSRAM0LS_ACTIVE Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM0LS_ACTIVE             (MXC_V_GCR_MEMCKCN_SYSRAM0LS_ACTIVE << MXC_F_GCR_MEMCKCN_SYSRAM0LS_POS) /**< MEMCKCN_SYSRAM0LS_ACTIVE Setting */
 #define MXC_V_GCR_MEMCKCN_SYSRAM0LS_LIGHT_SLEEP        ((uint32_t)0x1UL) /**< MEMCKCN_SYSRAM0LS_LIGHT_SLEEP Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM0LS_LIGHT_SLEEP        (MXC_V_GCR_MEMCKCN_SYSRAM0LS_LIGHT_SLEEP << MXC_F_GCR_MEMCKCN_SYSRAM0LS_POS) /**< MEMCKCN_SYSRAM0LS_LIGHT_SLEEP Setting */

 #define MXC_F_GCR_MEMCKCN_SYSRAM1LS_POS                9 /**< MEMCKCN_SYSRAM1LS Position */
 #define MXC_F_GCR_MEMCKCN_SYSRAM1LS                    ((uint32_t)(0x1UL << MXC_F_GCR_MEMCKCN_SYSRAM1LS_POS)) /**< MEMCKCN_SYSRAM1LS Mask */
 #define MXC_V_GCR_MEMCKCN_SYSRAM1LS_ACTIVE             ((uint32_t)0x0UL) /**< MEMCKCN_SYSRAM1LS_ACTIVE Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM1LS_ACTIVE             (MXC_V_GCR_MEMCKCN_SYSRAM1LS_ACTIVE << MXC_F_GCR_MEMCKCN_SYSRAM1LS_POS) /**< MEMCKCN_SYSRAM1LS_ACTIVE Setting */
 #define MXC_V_GCR_MEMCKCN_SYSRAM1LS_LIGHT_SLEEP        ((uint32_t)0x1UL) /**< MEMCKCN_SYSRAM1LS_LIGHT_SLEEP Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM1LS_LIGHT_SLEEP        (MXC_V_GCR_MEMCKCN_SYSRAM1LS_LIGHT_SLEEP << MXC_F_GCR_MEMCKCN_SYSRAM1LS_POS) /**< MEMCKCN_SYSRAM1LS_LIGHT_SLEEP Setting */

 #define MXC_F_GCR_MEMCKCN_SYSRAM2LS_POS                10 /**< MEMCKCN_SYSRAM2LS Position */
 #define MXC_F_GCR_MEMCKCN_SYSRAM2LS                    ((uint32_t)(0x1UL << MXC_F_GCR_MEMCKCN_SYSRAM2LS_POS)) /**< MEMCKCN_SYSRAM2LS Mask */
 #define MXC_V_GCR_MEMCKCN_SYSRAM2LS_ACTIVE             ((uint32_t)0x0UL) /**< MEMCKCN_SYSRAM2LS_ACTIVE Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM2LS_ACTIVE             (MXC_V_GCR_MEMCKCN_SYSRAM2LS_ACTIVE << MXC_F_GCR_MEMCKCN_SYSRAM2LS_POS) /**< MEMCKCN_SYSRAM2LS_ACTIVE Setting */
 #define MXC_V_GCR_MEMCKCN_SYSRAM2LS_LIGHT_SLEEP        ((uint32_t)0x1UL) /**< MEMCKCN_SYSRAM2LS_LIGHT_SLEEP Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM2LS_LIGHT_SLEEP        (MXC_V_GCR_MEMCKCN_SYSRAM2LS_LIGHT_SLEEP << MXC_F_GCR_MEMCKCN_SYSRAM2LS_POS) /**< MEMCKCN_SYSRAM2LS_LIGHT_SLEEP Setting */

 #define MXC_F_GCR_MEMCKCN_SYSRAM3LS_POS                11 /**< MEMCKCN_SYSRAM3LS Position */
 #define MXC_F_GCR_MEMCKCN_SYSRAM3LS                    ((uint32_t)(0x1UL << MXC_F_GCR_MEMCKCN_SYSRAM3LS_POS)) /**< MEMCKCN_SYSRAM3LS Mask */
 #define MXC_V_GCR_MEMCKCN_SYSRAM3LS_ACTIVE             ((uint32_t)0x0UL) /**< MEMCKCN_SYSRAM3LS_ACTIVE Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM3LS_ACTIVE             (MXC_V_GCR_MEMCKCN_SYSRAM3LS_ACTIVE << MXC_F_GCR_MEMCKCN_SYSRAM3LS_POS) /**< MEMCKCN_SYSRAM3LS_ACTIVE Setting */
 #define MXC_V_GCR_MEMCKCN_SYSRAM3LS_LIGHT_SLEEP        ((uint32_t)0x1UL) /**< MEMCKCN_SYSRAM3LS_LIGHT_SLEEP Value */
 #define MXC_S_GCR_MEMCKCN_SYSRAM3LS_LIGHT_SLEEP        (MXC_V_GCR_MEMCKCN_SYSRAM3LS_LIGHT_SLEEP << MXC_F_GCR_MEMCKCN_SYSRAM3LS_POS) /**< MEMCKCN_SYSRAM3LS_LIGHT_SLEEP Setting */

 #define MXC_F_GCR_MEMCKCN_ICACHELS_POS                 12 /**< MEMCKCN_ICACHELS Position */
 #define MXC_F_GCR_MEMCKCN_ICACHELS                     ((uint32_t)(0x1UL << MXC_F_GCR_MEMCKCN_ICACHELS_POS)) /**< MEMCKCN_ICACHELS Mask */
 #define MXC_V_GCR_MEMCKCN_ICACHELS_ACTIVE              ((uint32_t)0x0UL) /**< MEMCKCN_ICACHELS_ACTIVE Value */
 #define MXC_S_GCR_MEMCKCN_ICACHELS_ACTIVE              (MXC_V_GCR_MEMCKCN_ICACHELS_ACTIVE << MXC_F_GCR_MEMCKCN_ICACHELS_POS) /**< MEMCKCN_ICACHELS_ACTIVE Setting */
 #define MXC_V_GCR_MEMCKCN_ICACHELS_LIGHT_SLEEP         ((uint32_t)0x1UL) /**< MEMCKCN_ICACHELS_LIGHT_SLEEP Value */
 #define MXC_S_GCR_MEMCKCN_ICACHELS_LIGHT_SLEEP         (MXC_V_GCR_MEMCKCN_ICACHELS_LIGHT_SLEEP << MXC_F_GCR_MEMCKCN_ICACHELS_POS) /**< MEMCKCN_ICACHELS_LIGHT_SLEEP Setting */

/**@} end of group GCR_MEMCKCN_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_MEMZCN GCR_MEMZCN
 * @brief    Memory Zeroize Control.
 * @{
 */
 #define MXC_F_GCR_MEMZCN_SRAM0Z_POS                    0 /**< MEMZCN_SRAM0Z Position */
 #define MXC_F_GCR_MEMZCN_SRAM0Z                        ((uint32_t)(0x1UL << MXC_F_GCR_MEMZCN_SRAM0Z_POS)) /**< MEMZCN_SRAM0Z Mask */
 #define MXC_V_GCR_MEMZCN_SRAM0Z_NOP                    ((uint32_t)0x0UL) /**< MEMZCN_SRAM0Z_NOP Value */
 #define MXC_S_GCR_MEMZCN_SRAM0Z_NOP                    (MXC_V_GCR_MEMZCN_SRAM0Z_NOP << MXC_F_GCR_MEMZCN_SRAM0Z_POS) /**< MEMZCN_SRAM0Z_NOP Setting */
 #define MXC_V_GCR_MEMZCN_SRAM0Z_START                  ((uint32_t)0x1UL) /**< MEMZCN_SRAM0Z_START Value */
 #define MXC_S_GCR_MEMZCN_SRAM0Z_START                  (MXC_V_GCR_MEMZCN_SRAM0Z_START << MXC_F_GCR_MEMZCN_SRAM0Z_POS) /**< MEMZCN_SRAM0Z_START Setting */

 #define MXC_F_GCR_MEMZCN_ICACHEZ_POS                   1 /**< MEMZCN_ICACHEZ Position */
 #define MXC_F_GCR_MEMZCN_ICACHEZ                       ((uint32_t)(0x1UL << MXC_F_GCR_MEMZCN_ICACHEZ_POS)) /**< MEMZCN_ICACHEZ Mask */
 #define MXC_V_GCR_MEMZCN_ICACHEZ_NOP                   ((uint32_t)0x0UL) /**< MEMZCN_ICACHEZ_NOP Value */
 #define MXC_S_GCR_MEMZCN_ICACHEZ_NOP                   (MXC_V_GCR_MEMZCN_ICACHEZ_NOP << MXC_F_GCR_MEMZCN_ICACHEZ_POS) /**< MEMZCN_ICACHEZ_NOP Setting */
 #define MXC_V_GCR_MEMZCN_ICACHEZ_START                 ((uint32_t)0x1UL) /**< MEMZCN_ICACHEZ_START Value */
 #define MXC_S_GCR_MEMZCN_ICACHEZ_START                 (MXC_V_GCR_MEMZCN_ICACHEZ_START << MXC_F_GCR_MEMZCN_ICACHEZ_POS) /**< MEMZCN_ICACHEZ_START Setting */

/**@} end of group GCR_MEMZCN_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_SYSST GCR_SYSST
 * @brief    System Status Register.
 * @{
 */
 #define MXC_F_GCR_SYSST_ICECLOCK_POS                   0 /**< SYSST_ICECLOCK Position */
 #define MXC_F_GCR_SYSST_ICECLOCK                       ((uint32_t)(0x1UL << MXC_F_GCR_SYSST_ICECLOCK_POS)) /**< SYSST_ICECLOCK Mask */
 #define MXC_V_GCR_SYSST_ICECLOCK_UNLOCKED              ((uint32_t)0x0UL) /**< SYSST_ICECLOCK_UNLOCKED Value */
 #define MXC_S_GCR_SYSST_ICECLOCK_UNLOCKED              (MXC_V_GCR_SYSST_ICECLOCK_UNLOCKED << MXC_F_GCR_SYSST_ICECLOCK_POS) /**< SYSST_ICECLOCK_UNLOCKED Setting */
 #define MXC_V_GCR_SYSST_ICECLOCK_LOCKED                ((uint32_t)0x1UL) /**< SYSST_ICECLOCK_LOCKED Value */
 #define MXC_S_GCR_SYSST_ICECLOCK_LOCKED                (MXC_V_GCR_SYSST_ICECLOCK_LOCKED << MXC_F_GCR_SYSST_ICECLOCK_POS) /**< SYSST_ICECLOCK_LOCKED Setting */

 #define MXC_F_GCR_SYSST_CODEINTERR_POS                 1 /**< SYSST_CODEINTERR Position */
 #define MXC_F_GCR_SYSST_CODEINTERR                     ((uint32_t)(0x1UL << MXC_F_GCR_SYSST_CODEINTERR_POS)) /**< SYSST_CODEINTERR Mask */
 #define MXC_V_GCR_SYSST_CODEINTERR_NORM                ((uint32_t)0x0UL) /**< SYSST_CODEINTERR_NORM Value */
 #define MXC_S_GCR_SYSST_CODEINTERR_NORM                (MXC_V_GCR_SYSST_CODEINTERR_NORM << MXC_F_GCR_SYSST_CODEINTERR_POS) /**< SYSST_CODEINTERR_NORM Setting */
 #define MXC_V_GCR_SYSST_CODEINTERR_CODE                ((uint32_t)0x1UL) /**< SYSST_CODEINTERR_CODE Value */
 #define MXC_S_GCR_SYSST_CODEINTERR_CODE                (MXC_V_GCR_SYSST_CODEINTERR_CODE << MXC_F_GCR_SYSST_CODEINTERR_POS) /**< SYSST_CODEINTERR_CODE Setting */

 #define MXC_F_GCR_SYSST_SCMEMF_POS                     5 /**< SYSST_SCMEMF Position */
 #define MXC_F_GCR_SYSST_SCMEMF                         ((uint32_t)(0x1UL << MXC_F_GCR_SYSST_SCMEMF_POS)) /**< SYSST_SCMEMF Mask */
 #define MXC_V_GCR_SYSST_SCMEMF_NORM                    ((uint32_t)0x0UL) /**< SYSST_SCMEMF_NORM Value */
 #define MXC_S_GCR_SYSST_SCMEMF_NORM                    (MXC_V_GCR_SYSST_SCMEMF_NORM << MXC_F_GCR_SYSST_SCMEMF_POS) /**< SYSST_SCMEMF_NORM Setting */
 #define MXC_V_GCR_SYSST_SCMEMF_MEMORY                  ((uint32_t)0x1UL) /**< SYSST_SCMEMF_MEMORY Value */
 #define MXC_S_GCR_SYSST_SCMEMF_MEMORY                  (MXC_V_GCR_SYSST_SCMEMF_MEMORY << MXC_F_GCR_SYSST_SCMEMF_POS) /**< SYSST_SCMEMF_MEMORY Setting */

/**@} end of group GCR_SYSST_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_RSTR1 GCR_RSTR1
 * @brief    Reset 1.
 * @{
 */
 #define MXC_F_GCR_RSTR1_I2C1_POS                       0 /**< RSTR1_I2C1 Position */
 #define MXC_F_GCR_RSTR1_I2C1                           ((uint32_t)(0x1UL << MXC_F_GCR_RSTR1_I2C1_POS)) /**< RSTR1_I2C1 Mask */
 #define MXC_V_GCR_RSTR1_I2C1_RFU                       ((uint32_t)0x0UL) /**< RSTR1_I2C1_RFU Value */
 #define MXC_S_GCR_RSTR1_I2C1_RFU                       (MXC_V_GCR_RSTR1_I2C1_RFU << MXC_F_GCR_RSTR1_I2C1_POS) /**< RSTR1_I2C1_RFU Setting */
 #define MXC_V_GCR_RSTR1_I2C1_RESET                     ((uint32_t)0x1UL) /**< RSTR1_I2C1_RESET Value */
 #define MXC_S_GCR_RSTR1_I2C1_RESET                     (MXC_V_GCR_RSTR1_I2C1_RESET << MXC_F_GCR_RSTR1_I2C1_POS) /**< RSTR1_I2C1_RESET Setting */
 #define MXC_V_GCR_RSTR1_I2C1_RESET_DONE                ((uint32_t)0x0UL) /**< RSTR1_I2C1_RESET_DONE Value */
 #define MXC_S_GCR_RSTR1_I2C1_RESET_DONE                (MXC_V_GCR_RSTR1_I2C1_RESET_DONE << MXC_F_GCR_RSTR1_I2C1_POS) /**< RSTR1_I2C1_RESET_DONE Setting */
 #define MXC_V_GCR_RSTR1_I2C1_BUSY                      ((uint32_t)0x1UL) /**< RSTR1_I2C1_BUSY Value */
 #define MXC_S_GCR_RSTR1_I2C1_BUSY                      (MXC_V_GCR_RSTR1_I2C1_BUSY << MXC_F_GCR_RSTR1_I2C1_POS) /**< RSTR1_I2C1_BUSY Setting */

/**@} end of group GCR_RSTR1_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_PERCKCN1 GCR_PERCKCN1
 * @brief    Peripheral Clock Disable.
 * @{
 */
 #define MXC_F_GCR_PERCKCN1_FLCD_POS                    3 /**< PERCKCN1_FLCD Position */
 #define MXC_F_GCR_PERCKCN1_FLCD                        ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN1_FLCD_POS)) /**< PERCKCN1_FLCD Mask */
 #define MXC_V_GCR_PERCKCN1_FLCD_EN                     ((uint32_t)0x0UL) /**< PERCKCN1_FLCD_EN Value */
 #define MXC_S_GCR_PERCKCN1_FLCD_EN                     (MXC_V_GCR_PERCKCN1_FLCD_EN << MXC_F_GCR_PERCKCN1_FLCD_POS) /**< PERCKCN1_FLCD_EN Setting */
 #define MXC_V_GCR_PERCKCN1_FLCD_DIS                    ((uint32_t)0x1UL) /**< PERCKCN1_FLCD_DIS Value */
 #define MXC_S_GCR_PERCKCN1_FLCD_DIS                    (MXC_V_GCR_PERCKCN1_FLCD_DIS << MXC_F_GCR_PERCKCN1_FLCD_POS) /**< PERCKCN1_FLCD_DIS Setting */

 #define MXC_F_GCR_PERCKCN1_ICACHED_POS                 11 /**< PERCKCN1_ICACHED Position */
 #define MXC_F_GCR_PERCKCN1_ICACHED                     ((uint32_t)(0x1UL << MXC_F_GCR_PERCKCN1_ICACHED_POS)) /**< PERCKCN1_ICACHED Mask */
 #define MXC_V_GCR_PERCKCN1_ICACHED_EN                  ((uint32_t)0x0UL) /**< PERCKCN1_ICACHED_EN Value */
 #define MXC_S_GCR_PERCKCN1_ICACHED_EN                  (MXC_V_GCR_PERCKCN1_ICACHED_EN << MXC_F_GCR_PERCKCN1_ICACHED_POS) /**< PERCKCN1_ICACHED_EN Setting */
 #define MXC_V_GCR_PERCKCN1_ICACHED_DIS                 ((uint32_t)0x1UL) /**< PERCKCN1_ICACHED_DIS Value */
 #define MXC_S_GCR_PERCKCN1_ICACHED_DIS                 (MXC_V_GCR_PERCKCN1_ICACHED_DIS << MXC_F_GCR_PERCKCN1_ICACHED_POS) /**< PERCKCN1_ICACHED_DIS Setting */

/**@} end of group GCR_PERCKCN1_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_EVTEN GCR_EVTEN
 * @brief    Event Enable Register.
 * @{
 */
 #define MXC_F_GCR_EVTEN_DMAEVENT_POS                   0 /**< EVTEN_DMAEVENT Position */
 #define MXC_F_GCR_EVTEN_DMAEVENT                       ((uint32_t)(0x1UL << MXC_F_GCR_EVTEN_DMAEVENT_POS)) /**< EVTEN_DMAEVENT Mask */

 #define MXC_F_GCR_EVTEN_RXEVENT_POS                    1 /**< EVTEN_RXEVENT Position */
 #define MXC_F_GCR_EVTEN_RXEVENT                        ((uint32_t)(0x1UL << MXC_F_GCR_EVTEN_RXEVENT_POS)) /**< EVTEN_RXEVENT Mask */

/**@} end of group GCR_EVTEN_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_REVISION GCR_REVISION
 * @brief    Revision Register.
 * @{
 */
 #define MXC_F_GCR_REVISION_REVISION_POS                0 /**< REVISION_REVISION Position */
 #define MXC_F_GCR_REVISION_REVISION                    ((uint32_t)(0xFFFFUL << MXC_F_GCR_REVISION_REVISION_POS)) /**< REVISION_REVISION Mask */

/**@} end of group GCR_REVISION_Register */

/**
 * @ingroup  gcr_registers
 * @defgroup GCR_SYSSIE GCR_SYSSIE
 * @brief    System Status Interrupt Enable Register.
 * @{
 */
 #define MXC_F_GCR_SYSSIE_ICEULIE_POS                   0 /**< SYSSIE_ICEULIE Position */
 #define MXC_F_GCR_SYSSIE_ICEULIE                       ((uint32_t)(0x1UL << MXC_F_GCR_SYSSIE_ICEULIE_POS)) /**< SYSSIE_ICEULIE Mask */
 #define MXC_V_GCR_SYSSIE_ICEULIE_DIS                   ((uint32_t)0x0UL) /**< SYSSIE_ICEULIE_DIS Value */
 #define MXC_S_GCR_SYSSIE_ICEULIE_DIS                   (MXC_V_GCR_SYSSIE_ICEULIE_DIS << MXC_F_GCR_SYSSIE_ICEULIE_POS) /**< SYSSIE_ICEULIE_DIS Setting */
 #define MXC_V_GCR_SYSSIE_ICEULIE_EN                    ((uint32_t)0x1UL) /**< SYSSIE_ICEULIE_EN Value */
 #define MXC_S_GCR_SYSSIE_ICEULIE_EN                    (MXC_V_GCR_SYSSIE_ICEULIE_EN << MXC_F_GCR_SYSSIE_ICEULIE_POS) /**< SYSSIE_ICEULIE_EN Setting */

 #define MXC_F_GCR_SYSSIE_CIEIE_POS                     1 /**< SYSSIE_CIEIE Position */
 #define MXC_F_GCR_SYSSIE_CIEIE                         ((uint32_t)(0x1UL << MXC_F_GCR_SYSSIE_CIEIE_POS)) /**< SYSSIE_CIEIE Mask */
 #define MXC_V_GCR_SYSSIE_CIEIE_DIS                     ((uint32_t)0x0UL) /**< SYSSIE_CIEIE_DIS Value */
 #define MXC_S_GCR_SYSSIE_CIEIE_DIS                     (MXC_V_GCR_SYSSIE_CIEIE_DIS << MXC_F_GCR_SYSSIE_CIEIE_POS) /**< SYSSIE_CIEIE_DIS Setting */
 #define MXC_V_GCR_SYSSIE_CIEIE_EN                      ((uint32_t)0x1UL) /**< SYSSIE_CIEIE_EN Value */
 #define MXC_S_GCR_SYSSIE_CIEIE_EN                      (MXC_V_GCR_SYSSIE_CIEIE_EN << MXC_F_GCR_SYSSIE_CIEIE_POS) /**< SYSSIE_CIEIE_EN Setting */

 #define MXC_F_GCR_SYSSIE_SCMFIE_POS                    5 /**< SYSSIE_SCMFIE Position */
 #define MXC_F_GCR_SYSSIE_SCMFIE                        ((uint32_t)(0x1UL << MXC_F_GCR_SYSSIE_SCMFIE_POS)) /**< SYSSIE_SCMFIE Mask */
 #define MXC_V_GCR_SYSSIE_SCMFIE_DIS                    ((uint32_t)0x0UL) /**< SYSSIE_SCMFIE_DIS Value */
 #define MXC_S_GCR_SYSSIE_SCMFIE_DIS                    (MXC_V_GCR_SYSSIE_SCMFIE_DIS << MXC_F_GCR_SYSSIE_SCMFIE_POS) /**< SYSSIE_SCMFIE_DIS Setting */
 #define MXC_V_GCR_SYSSIE_SCMFIE_EN                     ((uint32_t)0x1UL) /**< SYSSIE_SCMFIE_EN Value */
 #define MXC_S_GCR_SYSSIE_SCMFIE_EN                     (MXC_V_GCR_SYSSIE_SCMFIE_EN << MXC_F_GCR_SYSSIE_SCMFIE_POS) /**< SYSSIE_SCMFIE_EN Setting */

/**@} end of group GCR_SYSSIE_Register */

#ifdef __cplusplus
}
#endif

#endif /* _GCR_REGS_H_ */
