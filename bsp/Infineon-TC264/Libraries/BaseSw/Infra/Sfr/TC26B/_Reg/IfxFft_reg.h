/**
 * \file IfxFft_reg.h
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
 * \defgroup IfxLld_Fft_Cfg Fft address
 * \ingroup IfxLld_Fft
 * 
 * \defgroup IfxLld_Fft_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Fft_Cfg
 * 
 * \defgroup IfxLld_Fft_Cfg_Fft 2-FFT
 * \ingroup IfxLld_Fft_Cfg
 * 
 */
#ifndef IFXFFT_REG_H
#define IFXFFT_REG_H 1
/******************************************************************************/
#include "IfxFft_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Fft_Cfg_BaseAddress
 * \{  */

/** \brief  FFT object */
#define MODULE_FFT /*lint --e(923)*/ (*(Ifx_FFT*)0xF8700C00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Fft_Cfg_Fft
 * \{  */

/** \brief  0, FFT Clock Control Register */
#define FFT_CLC /*lint --e(923)*/ (*(volatile Ifx_FFT_CLC*)0xF8700C00u)

/** \brief  40, FFT Control and Status Register */
#define FFT_CSR /*lint --e(923)*/ (*(volatile Ifx_FFT_CSR*)0xF8700C40u)

/** \brief  60, FFT History0 Register */
#define FFT_HISTORY0 /*lint --e(923)*/ (*(volatile Ifx_FFT_HISTORY0*)0xF8700C60u)

/** \brief  70, FFT History1 Register */
#define FFT_HISTORY1 /*lint --e(923)*/ (*(volatile Ifx_FFT_HISTORY1*)0xF8700C70u)

/** \brief  8, FFT Identification Register */
#define FFT_ID /*lint --e(923)*/ (*(volatile Ifx_FFT_ID*)0xF8700C08u)

/** \brief  F4, FFT Kernel Reset Register 0 */
#define FFT_KRST0 /*lint --e(923)*/ (*(volatile Ifx_FFT_KRST0*)0xF8700CF4u)

/** \brief  F0, FFT Kernel Reset Register 1 */
#define FFT_KRST1 /*lint --e(923)*/ (*(volatile Ifx_FFT_KRST1*)0xF8700CF0u)

/** \brief  EC, FFT Kernel Reset Status Clear Register */
#define FFT_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_FFT_KRSTCLR*)0xF8700CECu)

/** \brief  E8, FFT OCDS Control and Status */
#define FFT_OCS /*lint --e(923)*/ (*(volatile Ifx_FFT_OCS*)0xF8700CE8u)

/** \brief  E4, FFT OCDS Debug Access Register */
#define FFT_ODA /*lint --e(923)*/ (*(volatile Ifx_FFT_ODA*)0xF8700CE4u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXFFT_REG_H */
