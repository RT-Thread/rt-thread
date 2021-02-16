/**
 * @file    sir_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the SIR Peripheral Module.
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

#ifndef _SIR_REGS_H_
#define _SIR_REGS_H_

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
 * @ingroup     sir
 * @defgroup    sir_registers SIR_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the SIR Peripheral Module.
 * @details System Initialization Registers.
 */

/**
 * @ingroup sir_registers
 * Structure type to access the SIR Registers.
 */
typedef struct {
    __I  uint32_t sistat;               /**< <tt>\b 0x00:</tt> SIR SISTAT Register */
    __I  uint32_t erraddr;              /**< <tt>\b 0x04:</tt> SIR ERRADDR Register */
    __R  uint32_t rsv_0x8_0xff[62];
    __I  uint32_t fstat;                /**< <tt>\b 0x100:</tt> SIR FSTAT Register */
    __I  uint32_t sfstat;               /**< <tt>\b 0x104:</tt> SIR SFSTAT Register */
} mxc_sir_regs_t;

/* Register offsets for module SIR */
/**
 * @ingroup    sir_registers
 * @defgroup   SIR_Register_Offsets Register Offsets
 * @brief      SIR Peripheral Register Offsets from the SIR Base Peripheral Address. 
 * @{
 */
 #define MXC_R_SIR_SISTAT                   ((uint32_t)0x00000000UL) /**< Offset from SIR Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_SIR_ERRADDR                  ((uint32_t)0x00000004UL) /**< Offset from SIR Base Address: <tt> 0x0004</tt> */ 
 #define MXC_R_SIR_FSTAT                    ((uint32_t)0x00000100UL) /**< Offset from SIR Base Address: <tt> 0x0100</tt> */ 
 #define MXC_R_SIR_SFSTAT                   ((uint32_t)0x00000104UL) /**< Offset from SIR Base Address: <tt> 0x0104</tt> */ 
/**@} end of group sir_registers */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_SISTAT SIR_SISTAT
 * @brief    System Initialization Status Register.
 * @{
 */
 #define MXC_F_SIR_SISTAT_MAGIC_POS                     0 /**< SISTAT_MAGIC Position */
 #define MXC_F_SIR_SISTAT_MAGIC                         ((uint32_t)(0x1UL << MXC_F_SIR_SISTAT_MAGIC_POS)) /**< SISTAT_MAGIC Mask */
 #define MXC_V_SIR_SISTAT_MAGIC_MAGICNOTSET             ((uint32_t)0x0UL) /**< SISTAT_MAGIC_MAGICNOTSET Value */
 #define MXC_S_SIR_SISTAT_MAGIC_MAGICNOTSET             (MXC_V_SIR_SISTAT_MAGIC_MAGICNOTSET << MXC_F_SIR_SISTAT_MAGIC_POS) /**< SISTAT_MAGIC_MAGICNOTSET Setting */
 #define MXC_V_SIR_SISTAT_MAGIC_MAGICSET                ((uint32_t)0x1UL) /**< SISTAT_MAGIC_MAGICSET Value */
 #define MXC_S_SIR_SISTAT_MAGIC_MAGICSET                (MXC_V_SIR_SISTAT_MAGIC_MAGICSET << MXC_F_SIR_SISTAT_MAGIC_POS) /**< SISTAT_MAGIC_MAGICSET Setting */

 #define MXC_F_SIR_SISTAT_CRCERR_POS                    1 /**< SISTAT_CRCERR Position */
 #define MXC_F_SIR_SISTAT_CRCERR                        ((uint32_t)(0x1UL << MXC_F_SIR_SISTAT_CRCERR_POS)) /**< SISTAT_CRCERR Mask */
 #define MXC_V_SIR_SISTAT_CRCERR_NOERROR                ((uint32_t)0x0UL) /**< SISTAT_CRCERR_NOERROR Value */
 #define MXC_S_SIR_SISTAT_CRCERR_NOERROR                (MXC_V_SIR_SISTAT_CRCERR_NOERROR << MXC_F_SIR_SISTAT_CRCERR_POS) /**< SISTAT_CRCERR_NOERROR Setting */
 #define MXC_V_SIR_SISTAT_CRCERR_ERROR                  ((uint32_t)0x1UL) /**< SISTAT_CRCERR_ERROR Value */
 #define MXC_S_SIR_SISTAT_CRCERR_ERROR                  (MXC_V_SIR_SISTAT_CRCERR_ERROR << MXC_F_SIR_SISTAT_CRCERR_POS) /**< SISTAT_CRCERR_ERROR Setting */

/**@} end of group SIR_SISTAT_Register */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_ERRADDR SIR_ERRADDR
 * @brief    Read-only field set by the SIB block if a CRC error occurs during the read of
 *           the OTP memory. Contains the failing address in OTP memory (when CRCERR equals
 *           1).
 * @{
 */
 #define MXC_F_SIR_ERRADDR_ERRADDR_POS                  0 /**< ERRADDR_ERRADDR Position */
 #define MXC_F_SIR_ERRADDR_ERRADDR                      ((uint32_t)(0xFFFFFFFFUL << MXC_F_SIR_ERRADDR_ERRADDR_POS)) /**< ERRADDR_ERRADDR Mask */

/**@} end of group SIR_ERRADDR_Register */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_FSTAT SIR_FSTAT
 * @brief    funcstat register.
 * @{
 */
 #define MXC_F_SIR_FSTAT_FPU_POS                        0 /**< FSTAT_FPU Position */
 #define MXC_F_SIR_FSTAT_FPU                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_FPU_POS)) /**< FSTAT_FPU Mask */
 #define MXC_V_SIR_FSTAT_FPU_NO                         ((uint32_t)0x0UL) /**< FSTAT_FPU_NO Value */
 #define MXC_S_SIR_FSTAT_FPU_NO                         (MXC_V_SIR_FSTAT_FPU_NO << MXC_F_SIR_FSTAT_FPU_POS) /**< FSTAT_FPU_NO Setting */
 #define MXC_V_SIR_FSTAT_FPU_YES                        ((uint32_t)0x1UL) /**< FSTAT_FPU_YES Value */
 #define MXC_S_SIR_FSTAT_FPU_YES                        (MXC_V_SIR_FSTAT_FPU_YES << MXC_F_SIR_FSTAT_FPU_POS) /**< FSTAT_FPU_YES Setting */

 #define MXC_F_SIR_FSTAT_USB_POS                        1 /**< FSTAT_USB Position */
 #define MXC_F_SIR_FSTAT_USB                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_USB_POS)) /**< FSTAT_USB Mask */
 #define MXC_V_SIR_FSTAT_USB_NO                         ((uint32_t)0x0UL) /**< FSTAT_USB_NO Value */
 #define MXC_S_SIR_FSTAT_USB_NO                         (MXC_V_SIR_FSTAT_USB_NO << MXC_F_SIR_FSTAT_USB_POS) /**< FSTAT_USB_NO Setting */
 #define MXC_V_SIR_FSTAT_USB_YES                        ((uint32_t)0x1UL) /**< FSTAT_USB_YES Value */
 #define MXC_S_SIR_FSTAT_USB_YES                        (MXC_V_SIR_FSTAT_USB_YES << MXC_F_SIR_FSTAT_USB_POS) /**< FSTAT_USB_YES Setting */

 #define MXC_F_SIR_FSTAT_ADC_POS                        2 /**< FSTAT_ADC Position */
 #define MXC_F_SIR_FSTAT_ADC                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_ADC_POS)) /**< FSTAT_ADC Mask */
 #define MXC_V_SIR_FSTAT_ADC_NO                         ((uint32_t)0x0UL) /**< FSTAT_ADC_NO Value */
 #define MXC_S_SIR_FSTAT_ADC_NO                         (MXC_V_SIR_FSTAT_ADC_NO << MXC_F_SIR_FSTAT_ADC_POS) /**< FSTAT_ADC_NO Setting */
 #define MXC_V_SIR_FSTAT_ADC_YES                        ((uint32_t)0x1UL) /**< FSTAT_ADC_YES Value */
 #define MXC_S_SIR_FSTAT_ADC_YES                        (MXC_V_SIR_FSTAT_ADC_YES << MXC_F_SIR_FSTAT_ADC_POS) /**< FSTAT_ADC_YES Setting */

 #define MXC_F_SIR_FSTAT_XIP_POS                        3 /**< FSTAT_XIP Position */
 #define MXC_F_SIR_FSTAT_XIP                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_XIP_POS)) /**< FSTAT_XIP Mask */
 #define MXC_V_SIR_FSTAT_XIP_NO                         ((uint32_t)0x0UL) /**< FSTAT_XIP_NO Value */
 #define MXC_S_SIR_FSTAT_XIP_NO                         (MXC_V_SIR_FSTAT_XIP_NO << MXC_F_SIR_FSTAT_XIP_POS) /**< FSTAT_XIP_NO Setting */
 #define MXC_V_SIR_FSTAT_XIP_YES                        ((uint32_t)0x1UL) /**< FSTAT_XIP_YES Value */
 #define MXC_S_SIR_FSTAT_XIP_YES                        (MXC_V_SIR_FSTAT_XIP_YES << MXC_F_SIR_FSTAT_XIP_POS) /**< FSTAT_XIP_YES Setting */

 #define MXC_F_SIR_FSTAT_PBM_POS                        4 /**< FSTAT_PBM Position */
 #define MXC_F_SIR_FSTAT_PBM                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_PBM_POS)) /**< FSTAT_PBM Mask */
 #define MXC_V_SIR_FSTAT_PBM_NO                         ((uint32_t)0x0UL) /**< FSTAT_PBM_NO Value */
 #define MXC_S_SIR_FSTAT_PBM_NO                         (MXC_V_SIR_FSTAT_PBM_NO << MXC_F_SIR_FSTAT_PBM_POS) /**< FSTAT_PBM_NO Setting */
 #define MXC_V_SIR_FSTAT_PBM_YES                        ((uint32_t)0x1UL) /**< FSTAT_PBM_YES Value */
 #define MXC_S_SIR_FSTAT_PBM_YES                        (MXC_V_SIR_FSTAT_PBM_YES << MXC_F_SIR_FSTAT_PBM_POS) /**< FSTAT_PBM_YES Setting */

 #define MXC_F_SIR_FSTAT_HBC_POS                        5 /**< FSTAT_HBC Position */
 #define MXC_F_SIR_FSTAT_HBC                            ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_HBC_POS)) /**< FSTAT_HBC Mask */
 #define MXC_V_SIR_FSTAT_HBC_NO                         ((uint32_t)0x0UL) /**< FSTAT_HBC_NO Value */
 #define MXC_S_SIR_FSTAT_HBC_NO                         (MXC_V_SIR_FSTAT_HBC_NO << MXC_F_SIR_FSTAT_HBC_POS) /**< FSTAT_HBC_NO Setting */
 #define MXC_V_SIR_FSTAT_HBC_YES                        ((uint32_t)0x1UL) /**< FSTAT_HBC_YES Value */
 #define MXC_S_SIR_FSTAT_HBC_YES                        (MXC_V_SIR_FSTAT_HBC_YES << MXC_F_SIR_FSTAT_HBC_POS) /**< FSTAT_HBC_YES Setting */

 #define MXC_F_SIR_FSTAT_SDHC_POS                       6 /**< FSTAT_SDHC Position */
 #define MXC_F_SIR_FSTAT_SDHC                           ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SDHC_POS)) /**< FSTAT_SDHC Mask */
 #define MXC_V_SIR_FSTAT_SDHC_NO                        ((uint32_t)0x0UL) /**< FSTAT_SDHC_NO Value */
 #define MXC_S_SIR_FSTAT_SDHC_NO                        (MXC_V_SIR_FSTAT_SDHC_NO << MXC_F_SIR_FSTAT_SDHC_POS) /**< FSTAT_SDHC_NO Setting */
 #define MXC_V_SIR_FSTAT_SDHC_YES                       ((uint32_t)0x1UL) /**< FSTAT_SDHC_YES Value */
 #define MXC_S_SIR_FSTAT_SDHC_YES                       (MXC_V_SIR_FSTAT_SDHC_YES << MXC_F_SIR_FSTAT_SDHC_POS) /**< FSTAT_SDHC_YES Setting */

 #define MXC_F_SIR_FSTAT_SMPHR_POS                      7 /**< FSTAT_SMPHR Position */
 #define MXC_F_SIR_FSTAT_SMPHR                          ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SMPHR_POS)) /**< FSTAT_SMPHR Mask */
 #define MXC_V_SIR_FSTAT_SMPHR_NO                       ((uint32_t)0x0UL) /**< FSTAT_SMPHR_NO Value */
 #define MXC_S_SIR_FSTAT_SMPHR_NO                       (MXC_V_SIR_FSTAT_SMPHR_NO << MXC_F_SIR_FSTAT_SMPHR_POS) /**< FSTAT_SMPHR_NO Setting */
 #define MXC_V_SIR_FSTAT_SMPHR_YES                      ((uint32_t)0x1UL) /**< FSTAT_SMPHR_YES Value */
 #define MXC_S_SIR_FSTAT_SMPHR_YES                      (MXC_V_SIR_FSTAT_SMPHR_YES << MXC_F_SIR_FSTAT_SMPHR_POS) /**< FSTAT_SMPHR_YES Setting */

 #define MXC_F_SIR_FSTAT_SCACHE_POS                     8 /**< FSTAT_SCACHE Position */
 #define MXC_F_SIR_FSTAT_SCACHE                         ((uint32_t)(0x1UL << MXC_F_SIR_FSTAT_SCACHE_POS)) /**< FSTAT_SCACHE Mask */
 #define MXC_V_SIR_FSTAT_SCACHE_NO                      ((uint32_t)0x0UL) /**< FSTAT_SCACHE_NO Value */
 #define MXC_S_SIR_FSTAT_SCACHE_NO                      (MXC_V_SIR_FSTAT_SCACHE_NO << MXC_F_SIR_FSTAT_SCACHE_POS) /**< FSTAT_SCACHE_NO Setting */
 #define MXC_V_SIR_FSTAT_SCACHE_YES                     ((uint32_t)0x1UL) /**< FSTAT_SCACHE_YES Value */
 #define MXC_S_SIR_FSTAT_SCACHE_YES                     (MXC_V_SIR_FSTAT_SCACHE_YES << MXC_F_SIR_FSTAT_SCACHE_POS) /**< FSTAT_SCACHE_YES Setting */

/**@} end of group SIR_FSTAT_Register */

/**
 * @ingroup  sir_registers
 * @defgroup SIR_SFSTAT SIR_SFSTAT
 * @brief    secfuncstat register.
 * @{
 */
 #define MXC_F_SIR_SFSTAT_TRNG_POS                      2 /**< SFSTAT_TRNG Position */
 #define MXC_F_SIR_SFSTAT_TRNG                          ((uint32_t)(0x1UL << MXC_F_SIR_SFSTAT_TRNG_POS)) /**< SFSTAT_TRNG Mask */
 #define MXC_V_SIR_SFSTAT_TRNG_NO                       ((uint32_t)0x0UL) /**< SFSTAT_TRNG_NO Value */
 #define MXC_S_SIR_SFSTAT_TRNG_NO                       (MXC_V_SIR_SFSTAT_TRNG_NO << MXC_F_SIR_SFSTAT_TRNG_POS) /**< SFSTAT_TRNG_NO Setting */
 #define MXC_V_SIR_SFSTAT_TRNG_YES                      ((uint32_t)0x1UL) /**< SFSTAT_TRNG_YES Value */
 #define MXC_S_SIR_SFSTAT_TRNG_YES                      (MXC_V_SIR_SFSTAT_TRNG_YES << MXC_F_SIR_SFSTAT_TRNG_POS) /**< SFSTAT_TRNG_YES Setting */

 #define MXC_F_SIR_SFSTAT_AES_POS                       3 /**< SFSTAT_AES Position */
 #define MXC_F_SIR_SFSTAT_AES                           ((uint32_t)(0x1UL << MXC_F_SIR_SFSTAT_AES_POS)) /**< SFSTAT_AES Mask */
 #define MXC_V_SIR_SFSTAT_AES_NO                        ((uint32_t)0x0UL) /**< SFSTAT_AES_NO Value */
 #define MXC_S_SIR_SFSTAT_AES_NO                        (MXC_V_SIR_SFSTAT_AES_NO << MXC_F_SIR_SFSTAT_AES_POS) /**< SFSTAT_AES_NO Setting */
 #define MXC_V_SIR_SFSTAT_AES_YES                       ((uint32_t)0x1UL) /**< SFSTAT_AES_YES Value */
 #define MXC_S_SIR_SFSTAT_AES_YES                       (MXC_V_SIR_SFSTAT_AES_YES << MXC_F_SIR_SFSTAT_AES_POS) /**< SFSTAT_AES_YES Setting */

 #define MXC_F_SIR_SFSTAT_SHA_POS                       4 /**< SFSTAT_SHA Position */
 #define MXC_F_SIR_SFSTAT_SHA                           ((uint32_t)(0x1UL << MXC_F_SIR_SFSTAT_SHA_POS)) /**< SFSTAT_SHA Mask */
 #define MXC_V_SIR_SFSTAT_SHA_NO                        ((uint32_t)0x0UL) /**< SFSTAT_SHA_NO Value */
 #define MXC_S_SIR_SFSTAT_SHA_NO                        (MXC_V_SIR_SFSTAT_SHA_NO << MXC_F_SIR_SFSTAT_SHA_POS) /**< SFSTAT_SHA_NO Setting */
 #define MXC_V_SIR_SFSTAT_SHA_YES                       ((uint32_t)0x1UL) /**< SFSTAT_SHA_YES Value */
 #define MXC_S_SIR_SFSTAT_SHA_YES                       (MXC_V_SIR_SFSTAT_SHA_YES << MXC_F_SIR_SFSTAT_SHA_POS) /**< SFSTAT_SHA_YES Setting */

 #define MXC_F_SIR_SFSTAT_MAA_POS                       5 /**< SFSTAT_MAA Position */
 #define MXC_F_SIR_SFSTAT_MAA                           ((uint32_t)(0x1UL << MXC_F_SIR_SFSTAT_MAA_POS)) /**< SFSTAT_MAA Mask */
 #define MXC_V_SIR_SFSTAT_MAA_NO                        ((uint32_t)0x0UL) /**< SFSTAT_MAA_NO Value */
 #define MXC_S_SIR_SFSTAT_MAA_NO                        (MXC_V_SIR_SFSTAT_MAA_NO << MXC_F_SIR_SFSTAT_MAA_POS) /**< SFSTAT_MAA_NO Setting */
 #define MXC_V_SIR_SFSTAT_MAA_YES                       ((uint32_t)0x1UL) /**< SFSTAT_MAA_YES Value */
 #define MXC_S_SIR_SFSTAT_MAA_YES                       (MXC_V_SIR_SFSTAT_MAA_YES << MXC_F_SIR_SFSTAT_MAA_POS) /**< SFSTAT_MAA_YES Setting */

/**@} end of group SIR_SFSTAT_Register */

#ifdef __cplusplus
}
#endif

#endif /* _SIR_REGS_H_ */
