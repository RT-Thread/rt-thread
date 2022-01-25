/**
 * @file    rtc_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the RTC Peripheral Module.
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

#ifndef _RTC_REGS_H_
#define _RTC_REGS_H_

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
 * @ingroup     rtc
 * @defgroup    rtc_registers RTC_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the RTC Peripheral Module.
 * @details Real Time Clock and Alarm.
 */

/**
 * @ingroup rtc_registers
 * Structure type to access the RTC Registers.
 */
typedef struct {
    __IO uint32_t sec;                  /**< <tt>\b 0x00:</tt> RTC SEC Register */
    __IO uint32_t ssec;                 /**< <tt>\b 0x04:</tt> RTC SSEC Register */
    __IO uint32_t ras;                  /**< <tt>\b 0x08:</tt> RTC RAS Register */
    __IO uint32_t rssa;                 /**< <tt>\b 0x0C:</tt> RTC RSSA Register */
    __IO uint32_t ctrl;                 /**< <tt>\b 0x10:</tt> RTC CTRL Register */
    __IO uint32_t trim;                 /**< <tt>\b 0x14:</tt> RTC TRIM Register */
    __IO uint32_t oscctrl;              /**< <tt>\b 0x18:</tt> RTC OSCCTRL Register */
} mxc_rtc_regs_t;

/* Register offsets for module RTC */
/**
 * @ingroup    rtc_registers
 * @defgroup   RTC_Register_Offsets Register Offsets
 * @brief      RTC Peripheral Register Offsets from the RTC Base Peripheral Address. 
 * @{
 */
 #define MXC_R_RTC_SEC                      ((uint32_t)0x00000000UL) /**< Offset from RTC Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_RTC_SSEC                     ((uint32_t)0x00000004UL) /**< Offset from RTC Base Address: <tt> 0x0004</tt> */ 
 #define MXC_R_RTC_RAS                      ((uint32_t)0x00000008UL) /**< Offset from RTC Base Address: <tt> 0x0008</tt> */ 
 #define MXC_R_RTC_RSSA                     ((uint32_t)0x0000000CUL) /**< Offset from RTC Base Address: <tt> 0x000C</tt> */ 
 #define MXC_R_RTC_CTRL                     ((uint32_t)0x00000010UL) /**< Offset from RTC Base Address: <tt> 0x0010</tt> */ 
 #define MXC_R_RTC_TRIM                     ((uint32_t)0x00000014UL) /**< Offset from RTC Base Address: <tt> 0x0014</tt> */ 
 #define MXC_R_RTC_OSCCTRL                  ((uint32_t)0x00000018UL) /**< Offset from RTC Base Address: <tt> 0x0018</tt> */ 
/**@} end of group rtc_registers */

/**
 * @ingroup  rtc_registers
 * @defgroup RTC_SSEC RTC_SSEC
 * @brief    RTC Sub-second Counter. This counter increments at 256Hz. RTC_SEC is incremented
 *           when this register rolls over from 0xFF to 0x00.
 * @{
 */
 #define MXC_F_RTC_SSEC_RTSS_POS                        0 /**< SSEC_RTSS Position */
 #define MXC_F_RTC_SSEC_RTSS                            ((uint32_t)(0xFFUL << MXC_F_RTC_SSEC_RTSS_POS)) /**< SSEC_RTSS Mask */

/**@} end of group RTC_SSEC_Register */

/**
 * @ingroup  rtc_registers
 * @defgroup RTC_RAS RTC_RAS
 * @brief    Time-of-day Alarm.
 * @{
 */
 #define MXC_F_RTC_RAS_RAS_POS                          0 /**< RAS_RAS Position */
 #define MXC_F_RTC_RAS_RAS                              ((uint32_t)(0xFFFFFUL << MXC_F_RTC_RAS_RAS_POS)) /**< RAS_RAS Mask */

/**@} end of group RTC_RAS_Register */

/**
 * @ingroup  rtc_registers
 * @defgroup RTC_RSSA RTC_RSSA
 * @brief    RTC sub-second alarm.  This register contains the reload value for the sub-
 *           second alarm.
 * @{
 */
 #define MXC_F_RTC_RSSA_RSSA_POS                        0 /**< RSSA_RSSA Position */
 #define MXC_F_RTC_RSSA_RSSA                            ((uint32_t)(0xFFFFFFFFUL << MXC_F_RTC_RSSA_RSSA_POS)) /**< RSSA_RSSA Mask */

/**@} end of group RTC_RSSA_Register */

/**
 * @ingroup  rtc_registers
 * @defgroup RTC_CTRL RTC_CTRL
 * @brief    RTC Control Register.
 * @{
 */
 #define MXC_F_RTC_CTRL_RTCE_POS                        0 /**< CTRL_RTCE Position */
 #define MXC_F_RTC_CTRL_RTCE                            ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_RTCE_POS)) /**< CTRL_RTCE Mask */
 #define MXC_V_RTC_CTRL_RTCE_DIS                        ((uint32_t)0x0UL) /**< CTRL_RTCE_DIS Value */
 #define MXC_S_RTC_CTRL_RTCE_DIS                        (MXC_V_RTC_CTRL_RTCE_DIS << MXC_F_RTC_CTRL_RTCE_POS) /**< CTRL_RTCE_DIS Setting */
 #define MXC_V_RTC_CTRL_RTCE_EN                         ((uint32_t)0x1UL) /**< CTRL_RTCE_EN Value */
 #define MXC_S_RTC_CTRL_RTCE_EN                         (MXC_V_RTC_CTRL_RTCE_EN << MXC_F_RTC_CTRL_RTCE_POS) /**< CTRL_RTCE_EN Setting */

 #define MXC_F_RTC_CTRL_ADE_POS                         1 /**< CTRL_ADE Position */
 #define MXC_F_RTC_CTRL_ADE                             ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_ADE_POS)) /**< CTRL_ADE Mask */
 #define MXC_V_RTC_CTRL_ADE_DIS                         ((uint32_t)0x0UL) /**< CTRL_ADE_DIS Value */
 #define MXC_S_RTC_CTRL_ADE_DIS                         (MXC_V_RTC_CTRL_ADE_DIS << MXC_F_RTC_CTRL_ADE_POS) /**< CTRL_ADE_DIS Setting */
 #define MXC_V_RTC_CTRL_ADE_EN                          ((uint32_t)0x1UL) /**< CTRL_ADE_EN Value */
 #define MXC_S_RTC_CTRL_ADE_EN                          (MXC_V_RTC_CTRL_ADE_EN << MXC_F_RTC_CTRL_ADE_POS) /**< CTRL_ADE_EN Setting */

 #define MXC_F_RTC_CTRL_ASE_POS                         2 /**< CTRL_ASE Position */
 #define MXC_F_RTC_CTRL_ASE                             ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_ASE_POS)) /**< CTRL_ASE Mask */
 #define MXC_V_RTC_CTRL_ASE_DIS                         ((uint32_t)0x0UL) /**< CTRL_ASE_DIS Value */
 #define MXC_S_RTC_CTRL_ASE_DIS                         (MXC_V_RTC_CTRL_ASE_DIS << MXC_F_RTC_CTRL_ASE_POS) /**< CTRL_ASE_DIS Setting */
 #define MXC_V_RTC_CTRL_ASE_EN                          ((uint32_t)0x1UL) /**< CTRL_ASE_EN Value */
 #define MXC_S_RTC_CTRL_ASE_EN                          (MXC_V_RTC_CTRL_ASE_EN << MXC_F_RTC_CTRL_ASE_POS) /**< CTRL_ASE_EN Setting */

 #define MXC_F_RTC_CTRL_BUSY_POS                        3 /**< CTRL_BUSY Position */
 #define MXC_F_RTC_CTRL_BUSY                            ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_BUSY_POS)) /**< CTRL_BUSY Mask */
 #define MXC_V_RTC_CTRL_BUSY_IDLE                       ((uint32_t)0x0UL) /**< CTRL_BUSY_IDLE Value */
 #define MXC_S_RTC_CTRL_BUSY_IDLE                       (MXC_V_RTC_CTRL_BUSY_IDLE << MXC_F_RTC_CTRL_BUSY_POS) /**< CTRL_BUSY_IDLE Setting */
 #define MXC_V_RTC_CTRL_BUSY_BUSY                       ((uint32_t)0x1UL) /**< CTRL_BUSY_BUSY Value */
 #define MXC_S_RTC_CTRL_BUSY_BUSY                       (MXC_V_RTC_CTRL_BUSY_BUSY << MXC_F_RTC_CTRL_BUSY_POS) /**< CTRL_BUSY_BUSY Setting */

 #define MXC_F_RTC_CTRL_RDY_POS                         4 /**< CTRL_RDY Position */
 #define MXC_F_RTC_CTRL_RDY                             ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_RDY_POS)) /**< CTRL_RDY Mask */
 #define MXC_V_RTC_CTRL_RDY_BUSY                        ((uint32_t)0x0UL) /**< CTRL_RDY_BUSY Value */
 #define MXC_S_RTC_CTRL_RDY_BUSY                        (MXC_V_RTC_CTRL_RDY_BUSY << MXC_F_RTC_CTRL_RDY_POS) /**< CTRL_RDY_BUSY Setting */
 #define MXC_V_RTC_CTRL_RDY_READY                       ((uint32_t)0x1UL) /**< CTRL_RDY_READY Value */
 #define MXC_S_RTC_CTRL_RDY_READY                       (MXC_V_RTC_CTRL_RDY_READY << MXC_F_RTC_CTRL_RDY_POS) /**< CTRL_RDY_READY Setting */

 #define MXC_F_RTC_CTRL_RDYE_POS                        5 /**< CTRL_RDYE Position */
 #define MXC_F_RTC_CTRL_RDYE                            ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_RDYE_POS)) /**< CTRL_RDYE Mask */
 #define MXC_V_RTC_CTRL_RDYE_DIS                        ((uint32_t)0x0UL) /**< CTRL_RDYE_DIS Value */
 #define MXC_S_RTC_CTRL_RDYE_DIS                        (MXC_V_RTC_CTRL_RDYE_DIS << MXC_F_RTC_CTRL_RDYE_POS) /**< CTRL_RDYE_DIS Setting */
 #define MXC_V_RTC_CTRL_RDYE_EN                         ((uint32_t)0x1UL) /**< CTRL_RDYE_EN Value */
 #define MXC_S_RTC_CTRL_RDYE_EN                         (MXC_V_RTC_CTRL_RDYE_EN << MXC_F_RTC_CTRL_RDYE_POS) /**< CTRL_RDYE_EN Setting */

 #define MXC_F_RTC_CTRL_ALDF_POS                        6 /**< CTRL_ALDF Position */
 #define MXC_F_RTC_CTRL_ALDF                            ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_ALDF_POS)) /**< CTRL_ALDF Mask */
 #define MXC_V_RTC_CTRL_ALDF_INACTIVE                   ((uint32_t)0x0UL) /**< CTRL_ALDF_INACTIVE Value */
 #define MXC_S_RTC_CTRL_ALDF_INACTIVE                   (MXC_V_RTC_CTRL_ALDF_INACTIVE << MXC_F_RTC_CTRL_ALDF_POS) /**< CTRL_ALDF_INACTIVE Setting */
 #define MXC_V_RTC_CTRL_ALDF_PENDING                    ((uint32_t)0x1UL) /**< CTRL_ALDF_PENDING Value */
 #define MXC_S_RTC_CTRL_ALDF_PENDING                    (MXC_V_RTC_CTRL_ALDF_PENDING << MXC_F_RTC_CTRL_ALDF_POS) /**< CTRL_ALDF_PENDING Setting */

 #define MXC_F_RTC_CTRL_ALSF_POS                        7 /**< CTRL_ALSF Position */
 #define MXC_F_RTC_CTRL_ALSF                            ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_ALSF_POS)) /**< CTRL_ALSF Mask */
 #define MXC_V_RTC_CTRL_ALSF_INACTIVE                   ((uint32_t)0x0UL) /**< CTRL_ALSF_INACTIVE Value */
 #define MXC_S_RTC_CTRL_ALSF_INACTIVE                   (MXC_V_RTC_CTRL_ALSF_INACTIVE << MXC_F_RTC_CTRL_ALSF_POS) /**< CTRL_ALSF_INACTIVE Setting */
 #define MXC_V_RTC_CTRL_ALSF_PENDING                    ((uint32_t)0x1UL) /**< CTRL_ALSF_PENDING Value */
 #define MXC_S_RTC_CTRL_ALSF_PENDING                    (MXC_V_RTC_CTRL_ALSF_PENDING << MXC_F_RTC_CTRL_ALSF_POS) /**< CTRL_ALSF_PENDING Setting */

 #define MXC_F_RTC_CTRL_SQE_POS                         8 /**< CTRL_SQE Position */
 #define MXC_F_RTC_CTRL_SQE                             ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_SQE_POS)) /**< CTRL_SQE Mask */
 #define MXC_V_RTC_CTRL_SQE_INACTIVE                    ((uint32_t)0x0UL) /**< CTRL_SQE_INACTIVE Value */
 #define MXC_S_RTC_CTRL_SQE_INACTIVE                    (MXC_V_RTC_CTRL_SQE_INACTIVE << MXC_F_RTC_CTRL_SQE_POS) /**< CTRL_SQE_INACTIVE Setting */
 #define MXC_V_RTC_CTRL_SQE_PENDING                     ((uint32_t)0x1UL) /**< CTRL_SQE_PENDING Value */
 #define MXC_S_RTC_CTRL_SQE_PENDING                     (MXC_V_RTC_CTRL_SQE_PENDING << MXC_F_RTC_CTRL_SQE_POS) /**< CTRL_SQE_PENDING Setting */

 #define MXC_F_RTC_CTRL_FT_POS                          9 /**< CTRL_FT Position */
 #define MXC_F_RTC_CTRL_FT                              ((uint32_t)(0x3UL << MXC_F_RTC_CTRL_FT_POS)) /**< CTRL_FT Mask */
 #define MXC_V_RTC_CTRL_FT_FREQ1HZ                      ((uint32_t)0x0UL) /**< CTRL_FT_FREQ1HZ Value */
 #define MXC_S_RTC_CTRL_FT_FREQ1HZ                      (MXC_V_RTC_CTRL_FT_FREQ1HZ << MXC_F_RTC_CTRL_FT_POS) /**< CTRL_FT_FREQ1HZ Setting */
 #define MXC_V_RTC_CTRL_FT_FREQ512HZ                    ((uint32_t)0x1UL) /**< CTRL_FT_FREQ512HZ Value */
 #define MXC_S_RTC_CTRL_FT_FREQ512HZ                    (MXC_V_RTC_CTRL_FT_FREQ512HZ << MXC_F_RTC_CTRL_FT_POS) /**< CTRL_FT_FREQ512HZ Setting */
 #define MXC_V_RTC_CTRL_FT_FREQ4KHZ                     ((uint32_t)0x2UL) /**< CTRL_FT_FREQ4KHZ Value */
 #define MXC_S_RTC_CTRL_FT_FREQ4KHZ                     (MXC_V_RTC_CTRL_FT_FREQ4KHZ << MXC_F_RTC_CTRL_FT_POS) /**< CTRL_FT_FREQ4KHZ Setting */
 #define MXC_V_RTC_CTRL_FT_CLKDIV8                      ((uint32_t)0x3UL) /**< CTRL_FT_CLKDIV8 Value */
 #define MXC_S_RTC_CTRL_FT_CLKDIV8                      (MXC_V_RTC_CTRL_FT_CLKDIV8 << MXC_F_RTC_CTRL_FT_POS) /**< CTRL_FT_CLKDIV8 Setting */

 #define MXC_F_RTC_CTRL_X32KMD_POS                      11 /**< CTRL_X32KMD Position */
 #define MXC_F_RTC_CTRL_X32KMD                          ((uint32_t)(0x3UL << MXC_F_RTC_CTRL_X32KMD_POS)) /**< CTRL_X32KMD Mask */
 #define MXC_V_RTC_CTRL_X32KMD_NOISEIMMUNEMODE          ((uint32_t)0x0UL) /**< CTRL_X32KMD_NOISEIMMUNEMODE Value */
 #define MXC_S_RTC_CTRL_X32KMD_NOISEIMMUNEMODE          (MXC_V_RTC_CTRL_X32KMD_NOISEIMMUNEMODE << MXC_F_RTC_CTRL_X32KMD_POS) /**< CTRL_X32KMD_NOISEIMMUNEMODE Setting */
 #define MXC_V_RTC_CTRL_X32KMD_QUIETMODE                ((uint32_t)0x1UL) /**< CTRL_X32KMD_QUIETMODE Value */
 #define MXC_S_RTC_CTRL_X32KMD_QUIETMODE                (MXC_V_RTC_CTRL_X32KMD_QUIETMODE << MXC_F_RTC_CTRL_X32KMD_POS) /**< CTRL_X32KMD_QUIETMODE Setting */
 #define MXC_V_RTC_CTRL_X32KMD_QUIETINSTOPWITHWARMUP    ((uint32_t)0x2UL) /**< CTRL_X32KMD_QUIETINSTOPWITHWARMUP Value */
 #define MXC_S_RTC_CTRL_X32KMD_QUIETINSTOPWITHWARMUP    (MXC_V_RTC_CTRL_X32KMD_QUIETINSTOPWITHWARMUP << MXC_F_RTC_CTRL_X32KMD_POS) /**< CTRL_X32KMD_QUIETINSTOPWITHWARMUP Setting */
 #define MXC_V_RTC_CTRL_X32KMD_QUIETINSTOPNOWARMUP      ((uint32_t)0x3UL) /**< CTRL_X32KMD_QUIETINSTOPNOWARMUP Value */
 #define MXC_S_RTC_CTRL_X32KMD_QUIETINSTOPNOWARMUP      (MXC_V_RTC_CTRL_X32KMD_QUIETINSTOPNOWARMUP << MXC_F_RTC_CTRL_X32KMD_POS) /**< CTRL_X32KMD_QUIETINSTOPNOWARMUP Setting */

 #define MXC_F_RTC_CTRL_WE_POS                          15 /**< CTRL_WE Position */
 #define MXC_F_RTC_CTRL_WE                              ((uint32_t)(0x1UL << MXC_F_RTC_CTRL_WE_POS)) /**< CTRL_WE Mask */
 #define MXC_V_RTC_CTRL_WE_INACTIVE                     ((uint32_t)0x0UL) /**< CTRL_WE_INACTIVE Value */
 #define MXC_S_RTC_CTRL_WE_INACTIVE                     (MXC_V_RTC_CTRL_WE_INACTIVE << MXC_F_RTC_CTRL_WE_POS) /**< CTRL_WE_INACTIVE Setting */
 #define MXC_V_RTC_CTRL_WE_PENDING                      ((uint32_t)0x1UL) /**< CTRL_WE_PENDING Value */
 #define MXC_S_RTC_CTRL_WE_PENDING                      (MXC_V_RTC_CTRL_WE_PENDING << MXC_F_RTC_CTRL_WE_POS) /**< CTRL_WE_PENDING Setting */

/**@} end of group RTC_CTRL_Register */

/**
 * @ingroup  rtc_registers
 * @defgroup RTC_TRIM RTC_TRIM
 * @brief    RTC Trim Register.
 * @{
 */
 #define MXC_F_RTC_TRIM_TRIM_POS                        0 /**< TRIM_TRIM Position */
 #define MXC_F_RTC_TRIM_TRIM                            ((uint32_t)(0xFFUL << MXC_F_RTC_TRIM_TRIM_POS)) /**< TRIM_TRIM Mask */

 #define MXC_F_RTC_TRIM_VBATTMR_POS                     8 /**< TRIM_VBATTMR Position */
 #define MXC_F_RTC_TRIM_VBATTMR                         ((uint32_t)(0xFFFFFFUL << MXC_F_RTC_TRIM_VBATTMR_POS)) /**< TRIM_VBATTMR Mask */

/**@} end of group RTC_TRIM_Register */

/**
 * @ingroup  rtc_registers
 * @defgroup RTC_OSCCTRL RTC_OSCCTRL
 * @brief    RTC Oscillator Control Register.
 * @{
 */
 #define MXC_F_RTC_OSCCTRL_FLITER_EN_POS                0 /**< OSCCTRL_FLITER_EN Position */
 #define MXC_F_RTC_OSCCTRL_FLITER_EN                    ((uint32_t)(0x1UL << MXC_F_RTC_OSCCTRL_FLITER_EN_POS)) /**< OSCCTRL_FLITER_EN Mask */

 #define MXC_F_RTC_OSCCTRL_IBIAS_SEL_POS                1 /**< OSCCTRL_IBIAS_SEL Position */
 #define MXC_F_RTC_OSCCTRL_IBIAS_SEL                    ((uint32_t)(0x1UL << MXC_F_RTC_OSCCTRL_IBIAS_SEL_POS)) /**< OSCCTRL_IBIAS_SEL Mask */
 #define MXC_V_RTC_OSCCTRL_IBIAS_SEL_2X                 ((uint32_t)0x0UL) /**< OSCCTRL_IBIAS_SEL_2X Value */
 #define MXC_S_RTC_OSCCTRL_IBIAS_SEL_2X                 (MXC_V_RTC_OSCCTRL_IBIAS_SEL_2X << MXC_F_RTC_OSCCTRL_IBIAS_SEL_POS) /**< OSCCTRL_IBIAS_SEL_2X Setting */
 #define MXC_V_RTC_OSCCTRL_IBIAS_SEL_4X                 ((uint32_t)0x1UL) /**< OSCCTRL_IBIAS_SEL_4X Value */
 #define MXC_S_RTC_OSCCTRL_IBIAS_SEL_4X                 (MXC_V_RTC_OSCCTRL_IBIAS_SEL_4X << MXC_F_RTC_OSCCTRL_IBIAS_SEL_POS) /**< OSCCTRL_IBIAS_SEL_4X Setting */

 #define MXC_F_RTC_OSCCTRL_HYST_EN_POS                  2 /**< OSCCTRL_HYST_EN Position */
 #define MXC_F_RTC_OSCCTRL_HYST_EN                      ((uint32_t)(0x1UL << MXC_F_RTC_OSCCTRL_HYST_EN_POS)) /**< OSCCTRL_HYST_EN Mask */

 #define MXC_F_RTC_OSCCTRL_IBIAS_EN_POS                 3 /**< OSCCTRL_IBIAS_EN Position */
 #define MXC_F_RTC_OSCCTRL_IBIAS_EN                     ((uint32_t)(0x1UL << MXC_F_RTC_OSCCTRL_IBIAS_EN_POS)) /**< OSCCTRL_IBIAS_EN Mask */

 #define MXC_F_RTC_OSCCTRL_BYPASS_POS                   4 /**< OSCCTRL_BYPASS Position */
 #define MXC_F_RTC_OSCCTRL_BYPASS                       ((uint32_t)(0x1UL << MXC_F_RTC_OSCCTRL_BYPASS_POS)) /**< OSCCTRL_BYPASS Mask */

 #define MXC_F_RTC_OSCCTRL_OUT32K_POS                   5 /**< OSCCTRL_OUT32K Position */
 #define MXC_F_RTC_OSCCTRL_OUT32K                       ((uint32_t)(0x1UL << MXC_F_RTC_OSCCTRL_OUT32K_POS)) /**< OSCCTRL_OUT32K Mask */

/**@} end of group RTC_OSCCTRL_Register */

#ifdef __cplusplus
}
#endif

#endif /* _RTC_REGS_H_ */
