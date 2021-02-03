/**
 * \file IfxCif_reg.h
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
 * \defgroup IfxLld_Cif_Cfg Cif address
 * \ingroup IfxLld_Cif
 * 
 * \defgroup IfxLld_Cif_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Cif_Cfg
 * 
 * \defgroup IfxLld_Cif_Cfg_Cif 2-CIF
 * \ingroup IfxLld_Cif_Cfg
 * 
 */
#ifndef IFXCIF_REG_H
#define IFXCIF_REG_H 1
/******************************************************************************/
#include "IfxCif_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Cif_Cfg_BaseAddress
 * \{  */

/** \brief  CIF object */
#define MODULE_CIF /*lint --e(923)*/ (*(Ifx_CIF*)0xF90E1F00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cif_Cfg_Cif
 * \{  */

/** \brief  C, Access Enable Register 0 */
#define CIF_BBB_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_ACCEN0*)0xF90E1F0Cu)

/** Alias (User Manual Name) for CIF_BBB_ACCEN0.
* To use register names with standard convension, please use CIF_BBB_ACCEN0.
*/
#define	CIFBBB_ACCEN0	(CIF_BBB_ACCEN0)

/** \brief  10, Access Enable Register 1 */
#define CIF_BBB_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_ACCEN1*)0xF90E1F10u)

/** Alias (User Manual Name) for CIF_BBB_ACCEN1.
* To use register names with standard convension, please use CIF_BBB_ACCEN1.
*/
#define	CIFBBB_ACCEN1	(CIF_BBB_ACCEN1)

/** \brief  0, Clock Control Register */
#define CIF_BBB_CLC /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_CLC*)0xF90E1F00u)

/** Alias (User Manual Name) for CIF_BBB_CLC.
* To use register names with standard convension, please use CIF_BBB_CLC.
*/
#define	CIFBBB_CLC	(CIF_BBB_CLC)

/** \brief  8, General Purpose Control Register */
#define CIF_BBB_GPCTL /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_GPCTL*)0xF90E1F08u)

/** Alias (User Manual Name) for CIF_BBB_GPCTL.
* To use register names with standard convension, please use CIF_BBB_GPCTL.
*/
#define	CIFBBB_GPCTL	(CIF_BBB_GPCTL)

/** \brief  14, Kernel Reset Register 0 */
#define CIF_BBB_KRST0 /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_KRST0*)0xF90E1F14u)

/** Alias (User Manual Name) for CIF_BBB_KRST0.
* To use register names with standard convension, please use CIF_BBB_KRST0.
*/
#define	CIFBBB_KRST0	(CIF_BBB_KRST0)

/** \brief  18, Kernel Reset Register 1 */
#define CIF_BBB_KRST1 /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_KRST1*)0xF90E1F18u)

/** Alias (User Manual Name) for CIF_BBB_KRST1.
* To use register names with standard convension, please use CIF_BBB_KRST1.
*/
#define	CIFBBB_KRST1	(CIF_BBB_KRST1)

/** \brief  1C, Kernel Reset Status Clear Register */
#define CIF_BBB_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_KRSTCLR*)0xF90E1F1Cu)

/** Alias (User Manual Name) for CIF_BBB_KRSTCLR.
* To use register names with standard convension, please use CIF_BBB_KRSTCLR.
*/
#define	CIFBBB_KRSTCLR	(CIF_BBB_KRSTCLR)

/** \brief  4, Module Identification Register */
#define CIF_BBB_MODID /*lint --e(923)*/ (*(volatile Ifx_CIF_BBB_MODID*)0xF90E1F04u)

/** Alias (User Manual Name) for CIF_BBB_MODID.
* To use register names with standard convension, please use CIF_BBB_MODID.
*/
#define	CIFBBB_MODID	(CIF_BBB_MODID)

/** \brief  100, Clock Control Register */
#define CIF_CCL /*lint --e(923)*/ (*(volatile Ifx_CIF_CCL*)0xF90E2000u)

/** \brief  2800, Debug Path Control Register */
#define CIF_DP_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_CTRL*)0xF90E4700u)

/** Alias (User Manual Name) for CIF_DP_CTRL.
* To use register names with standard convension, please use CIF_DP_CTRL.
*/
#define	CIFDP_CTRL	(CIF_DP_CTRL)

/** \brief  2808, Debug Path Frame/Line Counter Status Register */
#define CIF_DP_FLC_STAT /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_FLC_STAT*)0xF90E4708u)

/** Alias (User Manual Name) for CIF_DP_FLC_STAT.
* To use register names with standard convension, please use CIF_DP_FLC_STAT.
*/
#define	CIFDP_FLC_STAT	(CIF_DP_FLC_STAT)

/** \brief  2804, Debug Path Predivider Control Register */
#define CIF_DP_PDIV_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_PDIV_CTRL*)0xF90E4704u)

/** Alias (User Manual Name) for CIF_DP_PDIV_CTRL.
* To use register names with standard convension, please use CIF_DP_PDIV_CTRL.
*/
#define	CIFDP_PDIV_CTRL	(CIF_DP_PDIV_CTRL)

/** \brief  280C, Debug Path Predivider Counter Status Register */
#define CIF_DP_PDIV_STAT /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_PDIV_STAT*)0xF90E470Cu)

/** Alias (User Manual Name) for CIF_DP_PDIV_STAT.
* To use register names with standard convension, please use CIF_DP_PDIV_STAT.
*/
#define	CIFDP_PDIV_STAT	(CIF_DP_PDIV_STAT)

/** \brief  2810, Debug Path Timestamp Counter Status Register */
#define CIF_DP_TSC_STAT /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_TSC_STAT*)0xF90E4710u)

/** Alias (User Manual Name) for CIF_DP_TSC_STAT.
* To use register names with standard convension, please use CIF_DP_TSC_STAT.
*/
#define	CIFDP_TSC_STAT	(CIF_DP_TSC_STAT)

/** \brief  2814, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S0 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E4714u)

/** Alias (User Manual Name) for CIF_DP_UDS_1S0.
* To use register names with standard convension, please use CIF_DP_UDS_1S0.
*/
#define	CIFDP_UDS_1	(CIF_DP_UDS_1S0)

/** \brief  2818, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S1 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E4718u)

/** Alias (User Manual Name) for CIF_DP_UDS_1S1.
* To use register names with standard convension, please use CIF_DP_UDS_1S1.
*/
#define	CIFDP_UDS_2	(CIF_DP_UDS_1S1)

/** \brief  281C, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S2 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E471Cu)

/** Alias (User Manual Name) for CIF_DP_UDS_1S2.
* To use register names with standard convension, please use CIF_DP_UDS_1S2.
*/
#define	CIFDP_UDS_3	(CIF_DP_UDS_1S2)

/** \brief  2820, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S3 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E4720u)

/** Alias (User Manual Name) for CIF_DP_UDS_1S3.
* To use register names with standard convension, please use CIF_DP_UDS_1S3.
*/
#define	CIFDP_UDS_4	(CIF_DP_UDS_1S3)

/** \brief  2824, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S4 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E4724u)

/** Alias (User Manual Name) for CIF_DP_UDS_1S4.
* To use register names with standard convension, please use CIF_DP_UDS_1S4.
*/
#define	CIFDP_UDS_5	(CIF_DP_UDS_1S4)

/** \brief  2828, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S5 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E4728u)

/** Alias (User Manual Name) for CIF_DP_UDS_1S5.
* To use register names with standard convension, please use CIF_DP_UDS_1S5.
*/
#define	CIFDP_UDS_6	(CIF_DP_UDS_1S5)

/** \brief  282C, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S6 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E472Cu)

/** Alias (User Manual Name) for CIF_DP_UDS_1S6.
* To use register names with standard convension, please use CIF_DP_UDS_1S6.
*/
#define	CIFDP_UDS_7	(CIF_DP_UDS_1S6)

/** \brief  2830, Debug Path User Defined Symbol Register \note Array index
 * shifted by 1. Example: defined register UDS_1S[0]/UDS_1S0 corresponds to user
 * manual UDS_1S1, ... */
#define CIF_DP_UDS_1S7 /*lint --e(923)*/ (*(volatile Ifx_CIF_DP_UDS*)0xF90E4730u)

/** Alias (User Manual Name) for CIF_DP_UDS_1S7.
* To use register names with standard convension, please use CIF_DP_UDS_1S7.
*/
#define	CIFDP_UDS_8	(CIF_DP_UDS_1S7)

/** \brief  118, CIF Data Path Control Register */
#define CIF_DPCL /*lint --e(923)*/ (*(volatile Ifx_CIF_DPCL*)0xF90E2018u)

/** \brief  2A00, Extra Path Image Cropping Control Register */
#define CIF_EP_IC_1S0_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_CTRL*)0xF90E4900u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_CTRL.
* To use register names with standard convension, please use CIF_EP_IC_1S0_CTRL.
*/
#define	CIFEP_1_IC_CTRL	(CIF_EP_IC_1S0_CTRL)

/** \brief  2A20, Extra Path Image Cropping Camera Displacement Register */
#define CIF_EP_IC_1S0_DISPLACE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_DISPLACE*)0xF90E4920u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_DISPLACE.
* To use register names with standard convension, please use CIF_EP_IC_1S0_DISPLACE.
*/
#define	CIFEP_1_IC_DISPLACE	(CIF_EP_IC_1S0_DISPLACE)

/** \brief  2A08, Extra Path Image Cropping Horizontal Offset of Output Window
 * Register */
#define CIF_EP_IC_1S0_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS*)0xF90E4908u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_H_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S0_H_OFFS.
*/
#define	CIFEP_1_IC_H_OFFS	(CIF_EP_IC_1S0_H_OFFS)

/** \brief  2A24, Extra Path Image Current Horizontal Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S0_H_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS_SHD*)0xF90E4924u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_H_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S0_H_OFFS_SHD.
*/
#define	CIFEP_1_IC_H_OFFS_SHD	(CIF_EP_IC_1S0_H_OFFS_SHD)

/** \brief  2A10, Extra Path Image Cropping Output Horizontal Picture Size
 * Register */
#define CIF_EP_IC_1S0_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE*)0xF90E4910u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_H_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S0_H_SIZE.
*/
#define	CIFEP_1_IC_H_SIZE	(CIF_EP_IC_1S0_H_SIZE)

/** \brief  2A2C, Extra Path Image Current Output Horizontal Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S0_H_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE_SHD*)0xF90E492Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_H_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S0_H_SIZE_SHD.
*/
#define	CIFEP_1_IC_H_SIZE_SHD	(CIF_EP_IC_1S0_H_SIZE_SHD)

/** \brief  2A18, Extra Path Image Cropping Maximum Horizontal Displacement
 * Register */
#define CIF_EP_IC_1S0_MAX_DX /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DX*)0xF90E4918u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_MAX_DX.
* To use register names with standard convension, please use CIF_EP_IC_1S0_MAX_DX.
*/
#define	CIFEP_1_IC_MAX_DX	(CIF_EP_IC_1S0_MAX_DX)

/** \brief  2A1C, Extra Path Image Cropping Maximum Vertical Displacement
 * Register */
#define CIF_EP_IC_1S0_MAX_DY /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DY*)0xF90E491Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_MAX_DY.
* To use register names with standard convension, please use CIF_EP_IC_1S0_MAX_DY.
*/
#define	CIFEP_1_IC_MAX_DY	(CIF_EP_IC_1S0_MAX_DY)

/** \brief  2A04, Extra Path Image Cropping Recenter Register */
#define CIF_EP_IC_1S0_RECENTER /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_RECENTER*)0xF90E4904u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_RECENTER.
* To use register names with standard convension, please use CIF_EP_IC_1S0_RECENTER.
*/
#define	CIFEP_1_IC_RECENTER	(CIF_EP_IC_1S0_RECENTER)

/** \brief  2A0C, Extra Path Image Cropping Vertical Offset Of Output Window
 * Register */
#define CIF_EP_IC_1S0_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS*)0xF90E490Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_V_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S0_V_OFFS.
*/
#define	CIFEP_1_IC_V_OFFS	(CIF_EP_IC_1S0_V_OFFS)

/** \brief  2A28, Extra Path Image Current Vertical Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S0_V_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS_SHD*)0xF90E4928u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_V_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S0_V_OFFS_SHD.
*/
#define	CIFEP_1_IC_V_OFFS_SHD	(CIF_EP_IC_1S0_V_OFFS_SHD)

/** \brief  2A14, Extra Path Image Cropping Output Vertical Picture Size
 * Register */
#define CIF_EP_IC_1S0_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE*)0xF90E4914u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_V_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S0_V_SIZE.
*/
#define	CIFEP_1_IC_V_SIZE	(CIF_EP_IC_1S0_V_SIZE)

/** \brief  2A30, Extra Path Image Current Output Vertical Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S0_V_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE_SHD*)0xF90E4930u)

/** Alias (User Manual Name) for CIF_EP_IC_1S0_V_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S0_V_SIZE_SHD.
*/
#define	CIFEP_1_IC_V_SIZE_SHD	(CIF_EP_IC_1S0_V_SIZE_SHD)

/** \brief  2B00, Extra Path Image Cropping Control Register */
#define CIF_EP_IC_1S1_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_CTRL*)0xF90E4A00u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_CTRL.
* To use register names with standard convension, please use CIF_EP_IC_1S1_CTRL.
*/
#define	CIFEP_2_IC_CTRL	(CIF_EP_IC_1S1_CTRL)

/** \brief  2B20, Extra Path Image Cropping Camera Displacement Register */
#define CIF_EP_IC_1S1_DISPLACE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_DISPLACE*)0xF90E4A20u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_DISPLACE.
* To use register names with standard convension, please use CIF_EP_IC_1S1_DISPLACE.
*/
#define	CIFEP_2_IC_DISPLACE	(CIF_EP_IC_1S1_DISPLACE)

/** \brief  2B08, Extra Path Image Cropping Horizontal Offset of Output Window
 * Register */
#define CIF_EP_IC_1S1_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS*)0xF90E4A08u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_H_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S1_H_OFFS.
*/
#define	CIFEP_2_IC_H_OFFS	(CIF_EP_IC_1S1_H_OFFS)

/** \brief  2B24, Extra Path Image Current Horizontal Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S1_H_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS_SHD*)0xF90E4A24u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_H_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S1_H_OFFS_SHD.
*/
#define	CIFEP_2_IC_H_OFFS_SHD	(CIF_EP_IC_1S1_H_OFFS_SHD)

/** \brief  2B10, Extra Path Image Cropping Output Horizontal Picture Size
 * Register */
#define CIF_EP_IC_1S1_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE*)0xF90E4A10u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_H_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S1_H_SIZE.
*/
#define	CIFEP_2_IC_H_SIZE	(CIF_EP_IC_1S1_H_SIZE)

/** \brief  2B2C, Extra Path Image Current Output Horizontal Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S1_H_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE_SHD*)0xF90E4A2Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_H_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S1_H_SIZE_SHD.
*/
#define	CIFEP_2_IC_H_SIZE_SHD	(CIF_EP_IC_1S1_H_SIZE_SHD)

/** \brief  2B18, Extra Path Image Cropping Maximum Horizontal Displacement
 * Register */
#define CIF_EP_IC_1S1_MAX_DX /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DX*)0xF90E4A18u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_MAX_DX.
* To use register names with standard convension, please use CIF_EP_IC_1S1_MAX_DX.
*/
#define	CIFEP_2_IC_MAX_DX	(CIF_EP_IC_1S1_MAX_DX)

/** \brief  2B1C, Extra Path Image Cropping Maximum Vertical Displacement
 * Register */
#define CIF_EP_IC_1S1_MAX_DY /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DY*)0xF90E4A1Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_MAX_DY.
* To use register names with standard convension, please use CIF_EP_IC_1S1_MAX_DY.
*/
#define	CIFEP_2_IC_MAX_DY	(CIF_EP_IC_1S1_MAX_DY)

/** \brief  2B04, Extra Path Image Cropping Recenter Register */
#define CIF_EP_IC_1S1_RECENTER /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_RECENTER*)0xF90E4A04u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_RECENTER.
* To use register names with standard convension, please use CIF_EP_IC_1S1_RECENTER.
*/
#define	CIFEP_2_IC_RECENTER	(CIF_EP_IC_1S1_RECENTER)

/** \brief  2B0C, Extra Path Image Cropping Vertical Offset Of Output Window
 * Register */
#define CIF_EP_IC_1S1_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS*)0xF90E4A0Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_V_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S1_V_OFFS.
*/
#define	CIFEP_2_IC_V_OFFS	(CIF_EP_IC_1S1_V_OFFS)

/** \brief  2B28, Extra Path Image Current Vertical Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S1_V_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS_SHD*)0xF90E4A28u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_V_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S1_V_OFFS_SHD.
*/
#define	CIFEP_2_IC_V_OFFS_SHD	(CIF_EP_IC_1S1_V_OFFS_SHD)

/** \brief  2B14, Extra Path Image Cropping Output Vertical Picture Size
 * Register */
#define CIF_EP_IC_1S1_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE*)0xF90E4A14u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_V_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S1_V_SIZE.
*/
#define	CIFEP_2_IC_V_SIZE	(CIF_EP_IC_1S1_V_SIZE)

/** \brief  2B30, Extra Path Image Current Output Vertical Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S1_V_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE_SHD*)0xF90E4A30u)

/** Alias (User Manual Name) for CIF_EP_IC_1S1_V_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S1_V_SIZE_SHD.
*/
#define	CIFEP_2_IC_V_SIZE_SHD	(CIF_EP_IC_1S1_V_SIZE_SHD)

/** \brief  2C00, Extra Path Image Cropping Control Register */
#define CIF_EP_IC_1S2_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_CTRL*)0xF90E4B00u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_CTRL.
* To use register names with standard convension, please use CIF_EP_IC_1S2_CTRL.
*/
#define	CIFEP_3_IC_CTRL	(CIF_EP_IC_1S2_CTRL)

/** \brief  2C20, Extra Path Image Cropping Camera Displacement Register */
#define CIF_EP_IC_1S2_DISPLACE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_DISPLACE*)0xF90E4B20u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_DISPLACE.
* To use register names with standard convension, please use CIF_EP_IC_1S2_DISPLACE.
*/
#define	CIFEP_3_IC_DISPLACE	(CIF_EP_IC_1S2_DISPLACE)

/** \brief  2C08, Extra Path Image Cropping Horizontal Offset of Output Window
 * Register */
#define CIF_EP_IC_1S2_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS*)0xF90E4B08u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_H_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S2_H_OFFS.
*/
#define	CIFEP_3_IC_H_OFFS	(CIF_EP_IC_1S2_H_OFFS)

/** \brief  2C24, Extra Path Image Current Horizontal Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S2_H_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS_SHD*)0xF90E4B24u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_H_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S2_H_OFFS_SHD.
*/
#define	CIFEP_3_IC_H_OFFS_SHD	(CIF_EP_IC_1S2_H_OFFS_SHD)

/** \brief  2C10, Extra Path Image Cropping Output Horizontal Picture Size
 * Register */
#define CIF_EP_IC_1S2_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE*)0xF90E4B10u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_H_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S2_H_SIZE.
*/
#define	CIFEP_3_IC_H_SIZE	(CIF_EP_IC_1S2_H_SIZE)

/** \brief  2C2C, Extra Path Image Current Output Horizontal Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S2_H_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE_SHD*)0xF90E4B2Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_H_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S2_H_SIZE_SHD.
*/
#define	CIFEP_3_IC_H_SIZE_SHD	(CIF_EP_IC_1S2_H_SIZE_SHD)

/** \brief  2C18, Extra Path Image Cropping Maximum Horizontal Displacement
 * Register */
#define CIF_EP_IC_1S2_MAX_DX /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DX*)0xF90E4B18u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_MAX_DX.
* To use register names with standard convension, please use CIF_EP_IC_1S2_MAX_DX.
*/
#define	CIFEP_3_IC_MAX_DX	(CIF_EP_IC_1S2_MAX_DX)

/** \brief  2C1C, Extra Path Image Cropping Maximum Vertical Displacement
 * Register */
#define CIF_EP_IC_1S2_MAX_DY /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DY*)0xF90E4B1Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_MAX_DY.
* To use register names with standard convension, please use CIF_EP_IC_1S2_MAX_DY.
*/
#define	CIFEP_3_IC_MAX_DY	(CIF_EP_IC_1S2_MAX_DY)

/** \brief  2C04, Extra Path Image Cropping Recenter Register */
#define CIF_EP_IC_1S2_RECENTER /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_RECENTER*)0xF90E4B04u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_RECENTER.
* To use register names with standard convension, please use CIF_EP_IC_1S2_RECENTER.
*/
#define	CIFEP_3_IC_RECENTER	(CIF_EP_IC_1S2_RECENTER)

/** \brief  2C0C, Extra Path Image Cropping Vertical Offset Of Output Window
 * Register */
#define CIF_EP_IC_1S2_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS*)0xF90E4B0Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_V_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S2_V_OFFS.
*/
#define	CIFEP_3_IC_V_OFFS	(CIF_EP_IC_1S2_V_OFFS)

/** \brief  2C28, Extra Path Image Current Vertical Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S2_V_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS_SHD*)0xF90E4B28u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_V_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S2_V_OFFS_SHD.
*/
#define	CIFEP_3_IC_V_OFFS_SHD	(CIF_EP_IC_1S2_V_OFFS_SHD)

/** \brief  2C14, Extra Path Image Cropping Output Vertical Picture Size
 * Register */
#define CIF_EP_IC_1S2_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE*)0xF90E4B14u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_V_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S2_V_SIZE.
*/
#define	CIFEP_3_IC_V_SIZE	(CIF_EP_IC_1S2_V_SIZE)

/** \brief  2C30, Extra Path Image Current Output Vertical Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S2_V_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE_SHD*)0xF90E4B30u)

/** Alias (User Manual Name) for CIF_EP_IC_1S2_V_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S2_V_SIZE_SHD.
*/
#define	CIFEP_3_IC_V_SIZE_SHD	(CIF_EP_IC_1S2_V_SIZE_SHD)

/** \brief  2D00, Extra Path Image Cropping Control Register */
#define CIF_EP_IC_1S3_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_CTRL*)0xF90E4C00u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_CTRL.
* To use register names with standard convension, please use CIF_EP_IC_1S3_CTRL.
*/
#define	CIFEP_4_IC_CTRL	(CIF_EP_IC_1S3_CTRL)

/** \brief  2D20, Extra Path Image Cropping Camera Displacement Register */
#define CIF_EP_IC_1S3_DISPLACE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_DISPLACE*)0xF90E4C20u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_DISPLACE.
* To use register names with standard convension, please use CIF_EP_IC_1S3_DISPLACE.
*/
#define	CIFEP_4_IC_DISPLACE	(CIF_EP_IC_1S3_DISPLACE)

/** \brief  2D08, Extra Path Image Cropping Horizontal Offset of Output Window
 * Register */
#define CIF_EP_IC_1S3_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS*)0xF90E4C08u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_H_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S3_H_OFFS.
*/
#define	CIFEP_4_IC_H_OFFS	(CIF_EP_IC_1S3_H_OFFS)

/** \brief  2D24, Extra Path Image Current Horizontal Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S3_H_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS_SHD*)0xF90E4C24u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_H_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S3_H_OFFS_SHD.
*/
#define	CIFEP_4_IC_H_OFFS_SHD	(CIF_EP_IC_1S3_H_OFFS_SHD)

/** \brief  2D10, Extra Path Image Cropping Output Horizontal Picture Size
 * Register */
#define CIF_EP_IC_1S3_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE*)0xF90E4C10u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_H_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S3_H_SIZE.
*/
#define	CIFEP_4_IC_H_SIZE	(CIF_EP_IC_1S3_H_SIZE)

/** \brief  2D2C, Extra Path Image Current Output Horizontal Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S3_H_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE_SHD*)0xF90E4C2Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_H_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S3_H_SIZE_SHD.
*/
#define	CIFEP_4_IC_H_SIZE_SHD	(CIF_EP_IC_1S3_H_SIZE_SHD)

/** \brief  2D18, Extra Path Image Cropping Maximum Horizontal Displacement
 * Register */
#define CIF_EP_IC_1S3_MAX_DX /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DX*)0xF90E4C18u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_MAX_DX.
* To use register names with standard convension, please use CIF_EP_IC_1S3_MAX_DX.
*/
#define	CIFEP_4_IC_MAX_DX	(CIF_EP_IC_1S3_MAX_DX)

/** \brief  2D1C, Extra Path Image Cropping Maximum Vertical Displacement
 * Register */
#define CIF_EP_IC_1S3_MAX_DY /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DY*)0xF90E4C1Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_MAX_DY.
* To use register names with standard convension, please use CIF_EP_IC_1S3_MAX_DY.
*/
#define	CIFEP_4_IC_MAX_DY	(CIF_EP_IC_1S3_MAX_DY)

/** \brief  2D04, Extra Path Image Cropping Recenter Register */
#define CIF_EP_IC_1S3_RECENTER /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_RECENTER*)0xF90E4C04u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_RECENTER.
* To use register names with standard convension, please use CIF_EP_IC_1S3_RECENTER.
*/
#define	CIFEP_4_IC_RECENTER	(CIF_EP_IC_1S3_RECENTER)

/** \brief  2D0C, Extra Path Image Cropping Vertical Offset Of Output Window
 * Register */
#define CIF_EP_IC_1S3_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS*)0xF90E4C0Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_V_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S3_V_OFFS.
*/
#define	CIFEP_4_IC_V_OFFS	(CIF_EP_IC_1S3_V_OFFS)

/** \brief  2D28, Extra Path Image Current Vertical Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S3_V_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS_SHD*)0xF90E4C28u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_V_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S3_V_OFFS_SHD.
*/
#define	CIFEP_4_IC_V_OFFS_SHD	(CIF_EP_IC_1S3_V_OFFS_SHD)

/** \brief  2D14, Extra Path Image Cropping Output Vertical Picture Size
 * Register */
#define CIF_EP_IC_1S3_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE*)0xF90E4C14u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_V_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S3_V_SIZE.
*/
#define	CIFEP_4_IC_V_SIZE	(CIF_EP_IC_1S3_V_SIZE)

/** \brief  2D30, Extra Path Image Current Output Vertical Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S3_V_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE_SHD*)0xF90E4C30u)

/** Alias (User Manual Name) for CIF_EP_IC_1S3_V_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S3_V_SIZE_SHD.
*/
#define	CIFEP_4_IC_V_SIZE_SHD	(CIF_EP_IC_1S3_V_SIZE_SHD)

/** \brief  2E00, Extra Path Image Cropping Control Register */
#define CIF_EP_IC_1S4_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_CTRL*)0xF90E4D00u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_CTRL.
* To use register names with standard convension, please use CIF_EP_IC_1S4_CTRL.
*/
#define	CIFEP_5_IC_CTRL	(CIF_EP_IC_1S4_CTRL)

/** \brief  2E20, Extra Path Image Cropping Camera Displacement Register */
#define CIF_EP_IC_1S4_DISPLACE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_DISPLACE*)0xF90E4D20u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_DISPLACE.
* To use register names with standard convension, please use CIF_EP_IC_1S4_DISPLACE.
*/
#define	CIFEP_5_IC_DISPLACE	(CIF_EP_IC_1S4_DISPLACE)

/** \brief  2E08, Extra Path Image Cropping Horizontal Offset of Output Window
 * Register */
#define CIF_EP_IC_1S4_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS*)0xF90E4D08u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_H_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S4_H_OFFS.
*/
#define	CIFEP_5_IC_H_OFFS	(CIF_EP_IC_1S4_H_OFFS)

/** \brief  2E24, Extra Path Image Current Horizontal Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S4_H_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_OFFS_SHD*)0xF90E4D24u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_H_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S4_H_OFFS_SHD.
*/
#define	CIFEP_5_IC_H_OFFS_SHD	(CIF_EP_IC_1S4_H_OFFS_SHD)

/** \brief  2E10, Extra Path Image Cropping Output Horizontal Picture Size
 * Register */
#define CIF_EP_IC_1S4_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE*)0xF90E4D10u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_H_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S4_H_SIZE.
*/
#define	CIFEP_5_IC_H_SIZE	(CIF_EP_IC_1S4_H_SIZE)

/** \brief  2E2C, Extra Path Image Current Output Horizontal Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S4_H_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_H_SIZE_SHD*)0xF90E4D2Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_H_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S4_H_SIZE_SHD.
*/
#define	CIFEP_5_IC_H_SIZE_SHD	(CIF_EP_IC_1S4_H_SIZE_SHD)

/** \brief  2E18, Extra Path Image Cropping Maximum Horizontal Displacement
 * Register */
#define CIF_EP_IC_1S4_MAX_DX /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DX*)0xF90E4D18u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_MAX_DX.
* To use register names with standard convension, please use CIF_EP_IC_1S4_MAX_DX.
*/
#define	CIFEP_5_IC_MAX_DX	(CIF_EP_IC_1S4_MAX_DX)

/** \brief  2E1C, Extra Path Image Cropping Maximum Vertical Displacement
 * Register */
#define CIF_EP_IC_1S4_MAX_DY /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_MAX_DY*)0xF90E4D1Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_MAX_DY.
* To use register names with standard convension, please use CIF_EP_IC_1S4_MAX_DY.
*/
#define	CIFEP_5_IC_MAX_DY	(CIF_EP_IC_1S4_MAX_DY)

/** \brief  2E04, Extra Path Image Cropping Recenter Register */
#define CIF_EP_IC_1S4_RECENTER /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_RECENTER*)0xF90E4D04u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_RECENTER.
* To use register names with standard convension, please use CIF_EP_IC_1S4_RECENTER.
*/
#define	CIFEP_5_IC_RECENTER	(CIF_EP_IC_1S4_RECENTER)

/** \brief  2E0C, Extra Path Image Cropping Vertical Offset Of Output Window
 * Register */
#define CIF_EP_IC_1S4_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS*)0xF90E4D0Cu)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_V_OFFS.
* To use register names with standard convension, please use CIF_EP_IC_1S4_V_OFFS.
*/
#define	CIFEP_5_IC_V_OFFS	(CIF_EP_IC_1S4_V_OFFS)

/** \brief  2E28, Extra Path Image Current Vertical Offset Of Output Window
 * Shadow Register */
#define CIF_EP_IC_1S4_V_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_OFFS_SHD*)0xF90E4D28u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_V_OFFS_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S4_V_OFFS_SHD.
*/
#define	CIFEP_5_IC_V_OFFS_SHD	(CIF_EP_IC_1S4_V_OFFS_SHD)

/** \brief  2E14, Extra Path Image Cropping Output Vertical Picture Size
 * Register */
#define CIF_EP_IC_1S4_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE*)0xF90E4D14u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_V_SIZE.
* To use register names with standard convension, please use CIF_EP_IC_1S4_V_SIZE.
*/
#define	CIFEP_5_IC_V_SIZE	(CIF_EP_IC_1S4_V_SIZE)

/** \brief  2E30, Extra Path Image Current Output Vertical Picture Size Shadow
 * Register */
#define CIF_EP_IC_1S4_V_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_EP_IC_V_SIZE_SHD*)0xF90E4D30u)

/** Alias (User Manual Name) for CIF_EP_IC_1S4_V_SIZE_SHD.
* To use register names with standard convension, please use CIF_EP_IC_1S4_V_SIZE_SHD.
*/
#define	CIFEP_5_IC_V_SIZE_SHD	(CIF_EP_IC_1S4_V_SIZE_SHD)

/** \brief  110, CIF Internal Clock Control Register */
#define CIF_ICCL /*lint --e(923)*/ (*(volatile Ifx_CIF_ICCL*)0xF90E2010u)

/** \brief  108, CIF Revision Identification Register */
#define CIF_ID /*lint --e(923)*/ (*(volatile Ifx_CIF_ID*)0xF90E2008u)

/** \brief  114, CIF Internal Reset Control Register */
#define CIF_IRCL /*lint --e(923)*/ (*(volatile Ifx_CIF_IRCL*)0xF90E2014u)

/** \brief  508, ISP Acquisition Horizontal Offset Register */
#define CIF_ISP_ACQ_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ACQ_H_OFFS*)0xF90E2408u)

/** Alias (User Manual Name) for CIF_ISP_ACQ_H_OFFS.
* To use register names with standard convension, please use CIF_ISP_ACQ_H_OFFS.
*/
#define	CIFISP_ACQ_H_OFFS	(CIF_ISP_ACQ_H_OFFS)

/** \brief  510, ISP Acquisition Horizontal Size Register */
#define CIF_ISP_ACQ_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ACQ_H_SIZE*)0xF90E2410u)

/** Alias (User Manual Name) for CIF_ISP_ACQ_H_SIZE.
* To use register names with standard convension, please use CIF_ISP_ACQ_H_SIZE.
*/
#define	CIFISP_ACQ_H_SIZE	(CIF_ISP_ACQ_H_SIZE)

/** \brief  518, ISP Acquisition Number of Frames Register */
#define CIF_ISP_ACQ_NR_FRAMES /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ACQ_NR_FRAMES*)0xF90E2418u)

/** Alias (User Manual Name) for CIF_ISP_ACQ_NR_FRAMES.
* To use register names with standard convension, please use CIF_ISP_ACQ_NR_FRAMES.
*/
#define	CIFISP_ACQ_NR_FRAMES	(CIF_ISP_ACQ_NR_FRAMES)

/** \brief  504, ISP Acquisition Properties Register */
#define CIF_ISP_ACQ_PROP /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ACQ_PROP*)0xF90E2404u)

/** Alias (User Manual Name) for CIF_ISP_ACQ_PROP.
* To use register names with standard convension, please use CIF_ISP_ACQ_PROP.
*/
#define	CIFISP_ACQ_PROP	(CIF_ISP_ACQ_PROP)

/** \brief  50C, ISP Acquistion Vertical Offset Register */
#define CIF_ISP_ACQ_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ACQ_V_OFFS*)0xF90E240Cu)

/** Alias (User Manual Name) for CIF_ISP_ACQ_V_OFFS.
* To use register names with standard convension, please use CIF_ISP_ACQ_V_OFFS.
*/
#define	CIFISP_ACQ_V_OFFS	(CIF_ISP_ACQ_V_OFFS)

/** \brief  514, ISP Acquisition Vertical Size Register */
#define CIF_ISP_ACQ_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ACQ_V_SIZE*)0xF90E2414u)

/** Alias (User Manual Name) for CIF_ISP_ACQ_V_SIZE.
* To use register names with standard convension, please use CIF_ISP_ACQ_V_SIZE.
*/
#define	CIFISP_ACQ_V_SIZE	(CIF_ISP_ACQ_V_SIZE)

/** \brief  500, ISP Global Control Register */
#define CIF_ISP_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_CTRL*)0xF90E2400u)

/** Alias (User Manual Name) for CIF_ISP_CTRL.
* To use register names with standard convension, please use CIF_ISP_CTRL.
*/
#define	CIFISP_CTRL	(CIF_ISP_CTRL)

/** \brief  73C, ISP Error Register */
#define CIF_ISP_ERR /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ERR*)0xF90E263Cu)

/** Alias (User Manual Name) for CIF_ISP_ERR.
* To use register names with standard convension, please use CIF_ISP_ERR.
*/
#define	CIFISP_ERR	(CIF_ISP_ERR)

/** \brief  740, ISP Error Clear Register */
#define CIF_ISP_ERR_CLR /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ERR_CLR*)0xF90E2640u)

/** Alias (User Manual Name) for CIF_ISP_ERR_CLR.
* To use register names with standard convension, please use CIF_ISP_ERR_CLR.
*/
#define	CIFISP_ERR_CLR	(CIF_ISP_ERR_CLR)

/** \brief  6A8, ISP Shadow Flags Register */
#define CIF_ISP_FLAGS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_FLAGS_SHD*)0xF90E25A8u)

/** Alias (User Manual Name) for CIF_ISP_FLAGS_SHD.
* To use register names with standard convension, please use CIF_ISP_FLAGS_SHD.
*/
#define	CIFISP_FLAGS_SHD	(CIF_ISP_FLAGS_SHD)

/** \brief  744, ISP Frame Counter Register */
#define CIF_ISP_FRAME_COUNT /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_FRAME_COUNT*)0xF90E2644u)

/** Alias (User Manual Name) for CIF_ISP_FRAME_COUNT.
* To use register names with standard convension, please use CIF_ISP_FRAME_COUNT.
*/
#define	CIFISP_FRAME_COUNT	(CIF_ISP_FRAME_COUNT)

/** \brief  6C8, ISP Interrupt Clear Register */
#define CIF_ISP_ICR /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ICR*)0xF90E25C8u)

/** Alias (User Manual Name) for CIF_ISP_ICR.
* To use register names with standard convension, please use CIF_ISP_ICR.
*/
#define	CIFISP_ICR	(CIF_ISP_ICR)

/** \brief  6BC, ISP Interrupt Mask Register */
#define CIF_ISP_IMSC /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_IMSC*)0xF90E25BCu)

/** Alias (User Manual Name) for CIF_ISP_IMSC.
* To use register names with standard convension, please use CIF_ISP_IMSC.
*/
#define	CIFISP_IMSC	(CIF_ISP_IMSC)

/** \brief  6CC, ISP Interrupt Set Register */
#define CIF_ISP_ISR /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_ISR*)0xF90E25CCu)

/** Alias (User Manual Name) for CIF_ISP_ISR.
* To use register names with standard convension, please use CIF_ISP_ISR.
*/
#define	CIFISP_ISR	(CIF_ISP_ISR)

/** \brief  6C4, ISP Masked Interrupt Status Register */
#define CIF_ISP_MIS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_MIS*)0xF90E25C4u)

/** Alias (User Manual Name) for CIF_ISP_MIS.
* To use register names with standard convension, please use CIF_ISP_MIS.
*/
#define	CIFISP_MIS	(CIF_ISP_MIS)

/** \brief  694, ISP Output Window Horizontal Offset Register */
#define CIF_ISP_OUT_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_H_OFFS*)0xF90E2594u)

/** Alias (User Manual Name) for CIF_ISP_OUT_H_OFFS.
* To use register names with standard convension, please use CIF_ISP_OUT_H_OFFS.
*/
#define	CIFISP_OUT_H_OFFS	(CIF_ISP_OUT_H_OFFS)

/** \brief  6AC, ISP Output Window Horizontal Offset Shadow Register */
#define CIF_ISP_OUT_H_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_H_OFFS_SHD*)0xF90E25ACu)

/** Alias (User Manual Name) for CIF_ISP_OUT_H_OFFS_SHD.
* To use register names with standard convension, please use CIF_ISP_OUT_H_OFFS_SHD.
*/
#define	CIFISP_OUT_H_OFFS_SHD	(CIF_ISP_OUT_H_OFFS_SHD)

/** \brief  69C, ISP Output Horizontal Picture Size Register */
#define CIF_ISP_OUT_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_H_SIZE*)0xF90E259Cu)

/** Alias (User Manual Name) for CIF_ISP_OUT_H_SIZE.
* To use register names with standard convension, please use CIF_ISP_OUT_H_SIZE.
*/
#define	CIFISP_OUT_H_SIZE	(CIF_ISP_OUT_H_SIZE)

/** \brief  6B4, ISP Output Horizontal Picture Size Shadow Register */
#define CIF_ISP_OUT_H_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_H_SIZE_SHD*)0xF90E25B4u)

/** Alias (User Manual Name) for CIF_ISP_OUT_H_SIZE_SHD.
* To use register names with standard convension, please use CIF_ISP_OUT_H_SIZE_SHD.
*/
#define	CIFISP_OUT_H_SIZE_SHD	(CIF_ISP_OUT_H_SIZE_SHD)

/** \brief  698, ISP Output Window Vertical Offset Register */
#define CIF_ISP_OUT_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_V_OFFS*)0xF90E2598u)

/** Alias (User Manual Name) for CIF_ISP_OUT_V_OFFS.
* To use register names with standard convension, please use CIF_ISP_OUT_V_OFFS.
*/
#define	CIFISP_OUT_V_OFFS	(CIF_ISP_OUT_V_OFFS)

/** \brief  6B0, ISP Output Window Vertical Offset Shadow Register */
#define CIF_ISP_OUT_V_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_V_OFFS_SHD*)0xF90E25B0u)

/** Alias (User Manual Name) for CIF_ISP_OUT_V_OFFS_SHD.
* To use register names with standard convension, please use CIF_ISP_OUT_V_OFFS_SHD.
*/
#define	CIFISP_OUT_V_OFFS_SHD	(CIF_ISP_OUT_V_OFFS_SHD)

/** \brief  6A0, ISP Output Vertical Picture Size Register */
#define CIF_ISP_OUT_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_V_SIZE*)0xF90E25A0u)

/** Alias (User Manual Name) for CIF_ISP_OUT_V_SIZE.
* To use register names with standard convension, please use CIF_ISP_OUT_V_SIZE.
*/
#define	CIFISP_OUT_V_SIZE	(CIF_ISP_OUT_V_SIZE)

/** \brief  6B8, ISP Output Vertical Picture Size Shadow Register */
#define CIF_ISP_OUT_V_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_OUT_V_SIZE_SHD*)0xF90E25B8u)

/** Alias (User Manual Name) for CIF_ISP_OUT_V_SIZE_SHD.
* To use register names with standard convension, please use CIF_ISP_OUT_V_SIZE_SHD.
*/
#define	CIFISP_OUT_V_SIZE_SHD	(CIF_ISP_OUT_V_SIZE_SHD)

/** \brief  6C0, ISP Raw Interrupt Status Register */
#define CIF_ISP_RIS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISP_RIS*)0xF90E25C0u)

/** Alias (User Manual Name) for CIF_ISP_RIS.
* To use register names with standard convension, please use CIF_ISP_RIS.
*/
#define	CIFISP_RIS	(CIF_ISP_RIS)

/** \brief  2400, ISP Image Stabilization Control Register */
#define CIF_ISPIS_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_CTRL*)0xF90E4300u)

/** Alias (User Manual Name) for CIF_ISPIS_CTRL.
* To use register names with standard convension, please use CIF_ISPIS_CTRL.
*/
#define	CIFISPIS_CTRL	(CIF_ISPIS_CTRL)

/** \brief  2420, ISP Image Stabilization Camera Displacement Register */
#define CIF_ISPIS_DISPLACE /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_DISPLACE*)0xF90E4320u)

/** Alias (User Manual Name) for CIF_ISPIS_DISPLACE.
* To use register names with standard convension, please use CIF_ISPIS_DISPLACE.
*/
#define	CIFISPIS_DISPLACE	(CIF_ISPIS_DISPLACE)

/** \brief  2408, ISP Image Stabilization Horizontal Offset Of Output Window
 * Register */
#define CIF_ISPIS_H_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_H_OFFS*)0xF90E4308u)

/** Alias (User Manual Name) for CIF_ISPIS_H_OFFS.
* To use register names with standard convension, please use CIF_ISPIS_H_OFFS.
*/
#define	CIFISPIS_H_OFFS	(CIF_ISPIS_H_OFFS)

/** \brief  2424, SP Image Current Horizontal Offset Of Output Window Shadow
 * Register */
#define CIF_ISPIS_H_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_H_OFFS_SHD*)0xF90E4324u)

/** Alias (User Manual Name) for CIF_ISPIS_H_OFFS_SHD.
* To use register names with standard convension, please use CIF_ISPIS_H_OFFS_SHD.
*/
#define	CIFISPIS_H_OFFS_SHD	(CIF_ISPIS_H_OFFS_SHD)

/** \brief  2410, ISP Image Stabilization Output Horizontal Picture Size
 * Register */
#define CIF_ISPIS_H_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_H_SIZE*)0xF90E4310u)

/** Alias (User Manual Name) for CIF_ISPIS_H_SIZE.
* To use register names with standard convension, please use CIF_ISPIS_H_SIZE.
*/
#define	CIFISPIS_H_SIZE	(CIF_ISPIS_H_SIZE)

/** \brief  242C, ISP Image Current Output Horizontal Picture Size Shadow
 * Register */
#define CIF_ISPIS_H_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_H_SIZE_SHD*)0xF90E432Cu)

/** Alias (User Manual Name) for CIF_ISPIS_H_SIZE_SHD.
* To use register names with standard convension, please use CIF_ISPIS_H_SIZE_SHD.
*/
#define	CIFISPIS_H_SIZE_SHD	(CIF_ISPIS_H_SIZE_SHD)

/** \brief  2418, ISP Image Stabilization Maximum Horizontal Displacement
 * Register */
#define CIF_ISPIS_MAX_DX /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_MAX_DX*)0xF90E4318u)

/** Alias (User Manual Name) for CIF_ISPIS_MAX_DX.
* To use register names with standard convension, please use CIF_ISPIS_MAX_DX.
*/
#define	CIFISPIS_MAX_DX	(CIF_ISPIS_MAX_DX)

/** \brief  241C, ISP Image Stabilization Maximum Vertical Displacement Register */
#define CIF_ISPIS_MAX_DY /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_MAX_DY*)0xF90E431Cu)

/** Alias (User Manual Name) for CIF_ISPIS_MAX_DY.
* To use register names with standard convension, please use CIF_ISPIS_MAX_DY.
*/
#define	CIFISPIS_MAX_DY	(CIF_ISPIS_MAX_DY)

/** \brief  2404, ISP Image Stabilization Recenter Register */
#define CIF_ISPIS_RECENTER /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_RECENTER*)0xF90E4304u)

/** Alias (User Manual Name) for CIF_ISPIS_RECENTER.
* To use register names with standard convension, please use CIF_ISPIS_RECENTER.
*/
#define	CIFISPIS_RECENTER	(CIF_ISPIS_RECENTER)

/** \brief  240C, ISP Image Stabilization Vertical Offset Of Output Window
 * Register */
#define CIF_ISPIS_V_OFFS /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_V_OFFS*)0xF90E430Cu)

/** Alias (User Manual Name) for CIF_ISPIS_V_OFFS.
* To use register names with standard convension, please use CIF_ISPIS_V_OFFS.
*/
#define	CIFISPIS_V_OFFS	(CIF_ISPIS_V_OFFS)

/** \brief  2428, ISP Image Current Vertical Offset Of Output Window Shadow
 * Register */
#define CIF_ISPIS_V_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_V_OFFS_SHD*)0xF90E4328u)

/** Alias (User Manual Name) for CIF_ISPIS_V_OFFS_SHD.
* To use register names with standard convension, please use CIF_ISPIS_V_OFFS_SHD.
*/
#define	CIFISPIS_V_OFFS_SHD	(CIF_ISPIS_V_OFFS_SHD)

/** \brief  2414, ISP Image Stabilization Output Vertical Picture Size Register */
#define CIF_ISPIS_V_SIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_V_SIZE*)0xF90E4314u)

/** Alias (User Manual Name) for CIF_ISPIS_V_SIZE.
* To use register names with standard convension, please use CIF_ISPIS_V_SIZE.
*/
#define	CIFISPIS_V_SIZE	(CIF_ISPIS_V_SIZE)

/** \brief  2430, ISP Image Current Output Vertical Picture Size Shadow Register */
#define CIF_ISPIS_V_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_ISPIS_V_SIZE_SHD*)0xF90E4330u)

/** Alias (User Manual Name) for CIF_ISPIS_V_SIZE_SHD.
* To use register names with standard convension, please use CIF_ISPIS_V_SIZE_SHD.
*/
#define	CIFISPIS_V_SIZE_SHD	(CIF_ISPIS_V_SIZE_SHD)

/** \brief  1938, JPE Huffman Table Selector For AC Values Register */
#define CIF_JPE_AC_TABLE_SELECT /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_AC_TABLE_SELECT*)0xF90E3838u)

/** Alias (User Manual Name) for CIF_JPE_AC_TABLE_SELECT.
* To use register names with standard convension, please use CIF_JPE_AC_TABLE_SELECT.
*/
#define	CIFJPE_AC_TABLE_SELECT	(CIF_JPE_AC_TABLE_SELECT)

/** \brief  1910, JPE Cb/Cr Value Scaling Control Register */
#define CIF_JPE_CBCR_SCALE_EN /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_CBCR_SCALE_EN*)0xF90E3810u)

/** Alias (User Manual Name) for CIF_JPE_CBCR_SCALE_EN.
* To use register names with standard convension, please use CIF_JPE_CBCR_SCALE_EN.
*/
#define	CIFJPE_CBCR_SCALE_EN	(CIF_JPE_CBCR_SCALE_EN)

/** \brief  1934, JPE Huffman Table Selector For DC Values Register */
#define CIF_JPE_DC_TABLE_SELECT /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_DC_TABLE_SELECT*)0xF90E3834u)

/** Alias (User Manual Name) for CIF_JPE_DC_TABLE_SELECT.
* To use register names with standard convension, please use CIF_JPE_DC_TABLE_SELECT.
*/
#define	CIFJPE_DC_TABLE_SELECT	(CIF_JPE_DC_TABLE_SELECT)

/** \brief  1964, JPE Debug Information Register */
#define CIF_JPE_DEBUG /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_DEBUG*)0xF90E3864u)

/** Alias (User Manual Name) for CIF_JPE_DEBUG.
* To use register names with standard convension, please use CIF_JPE_DEBUG.
*/
#define	CIFJPE_DEBUG	(CIF_JPE_DEBUG)

/** \brief  1918, JPEG Codec Horizontal Image Size For Encoding Register */
#define CIF_JPE_ENC_HSIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ENC_HSIZE*)0xF90E3818u)

/** Alias (User Manual Name) for CIF_JPE_ENC_HSIZE.
* To use register names with standard convension, please use CIF_JPE_ENC_HSIZE.
*/
#define	CIFJPE_ENC_HSIZE	(CIF_JPE_ENC_HSIZE)

/** \brief  191C, JPEG Codec Vertical Image Size For Encoding Register */
#define CIF_JPE_ENC_VSIZE /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ENC_VSIZE*)0xF90E381Cu)

/** Alias (User Manual Name) for CIF_JPE_ENC_VSIZE.
* To use register names with standard convension, please use CIF_JPE_ENC_VSIZE.
*/
#define	CIFJPE_ENC_VSIZE	(CIF_JPE_ENC_VSIZE)

/** \brief  1904, JPE Start Command To Start JFIF Stream Encoding Register */
#define CIF_JPE_ENCODE /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ENCODE*)0xF90E3804u)

/** Alias (User Manual Name) for CIF_JPE_ENCODE.
* To use register names with standard convension, please use CIF_JPE_ENCODE.
*/
#define	CIFJPE_ENCODE	(CIF_JPE_ENCODE)

/** \brief  1960, JPE Encode Mode Register */
#define CIF_JPE_ENCODE_MODE /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ENCODE_MODE*)0xF90E3860u)

/** Alias (User Manual Name) for CIF_JPE_ENCODE_MODE.
* To use register names with standard convension, please use CIF_JPE_ENCODE_MODE.
*/
#define	CIFJPE_ENCODE_MODE	(CIF_JPE_ENCODE_MODE)

/** \brief  1958, JPE Encoder Status Flag Register */
#define CIF_JPE_ENCODER_BUSY /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ENCODER_BUSY*)0xF90E3858u)

/** Alias (User Manual Name) for CIF_JPE_ENCODER_BUSY.
* To use register names with standard convension, please use CIF_JPE_ENCODER_BUSY.
*/
#define	CIFJPE_ENCODER_BUSY	(CIF_JPE_ENCODER_BUSY)

/** \brief  1974, JPE Error Interrupt Clear Register */
#define CIF_JPE_ERROR_ICR /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ERROR_ICR*)0xF90E3874u)

/** Alias (User Manual Name) for CIF_JPE_ERROR_ICR.
* To use register names with standard convension, please use CIF_JPE_ERROR_ICR.
*/
#define	CIFJPE_ERROR_ICR	(CIF_JPE_ERROR_ICR)

/** \brief  1968, JPE Error Interrupt Mask Register */
#define CIF_JPE_ERROR_IMR /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ERROR_IMR*)0xF90E3868u)

/** Alias (User Manual Name) for CIF_JPE_ERROR_IMR.
* To use register names with standard convension, please use CIF_JPE_ERROR_IMR.
*/
#define	CIFJPE_ERROR_IMR	(CIF_JPE_ERROR_IMR)

/** \brief  1978, JPE Error Interrupt Set Register */
#define CIF_JPE_ERROR_ISR /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ERROR_ISR*)0xF90E3878u)

/** Alias (User Manual Name) for CIF_JPE_ERROR_ISR.
* To use register names with standard convension, please use CIF_JPE_ERROR_ISR.
*/
#define	CIFJPE_ERROR_ISR	(CIF_JPE_ERROR_ISR)

/** \brief  1970, JPE Error Masked Interrupt Status Register */
#define CIF_JPE_ERROR_MIS /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ERROR_MIS*)0xF90E3870u)

/** Alias (User Manual Name) for CIF_JPE_ERROR_MIS.
* To use register names with standard convension, please use CIF_JPE_ERROR_MIS.
*/
#define	CIFJPE_ERROR_MIS	(CIF_JPE_ERROR_MIS)

/** \brief  196C, JPE Error Raw Interrupt Status Register */
#define CIF_JPE_ERROR_RIS /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_ERROR_RIS*)0xF90E386Cu)

/** Alias (User Manual Name) for CIF_JPE_ERROR_RIS.
* To use register names with standard convension, please use CIF_JPE_ERROR_RIS.
*/
#define	CIFJPE_ERROR_RIS	(CIF_JPE_ERROR_RIS)

/** \brief  1900, JPE Command To Start Stream Header Generation Register */
#define CIF_JPE_GEN_HEADER /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_GEN_HEADER*)0xF90E3800u)

/** Alias (User Manual Name) for CIF_JPE_GEN_HEADER.
* To use register names with standard convension, please use CIF_JPE_GEN_HEADER.
*/
#define	CIFJPE_GEN_HEADER	(CIF_JPE_GEN_HEADER)

/** \brief  195C, JPE Header Mode Definition Register */
#define CIF_JPE_HEADER_MODE /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_HEADER_MODE*)0xF90E385Cu)

/** Alias (User Manual Name) for CIF_JPE_HEADER_MODE.
* To use register names with standard convension, please use CIF_JPE_HEADER_MODE.
*/
#define	CIFJPE_HEADER_MODE	(CIF_JPE_HEADER_MODE)

/** \brief  1908, JPE Automatic Configuration Update Register */
#define CIF_JPE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_INIT*)0xF90E3808u)

/** Alias (User Manual Name) for CIF_JPE_INIT.
* To use register names with standard convension, please use CIF_JPE_INIT.
*/
#define	CIFJPE_INIT	(CIF_JPE_INIT)

/** \brief  1920, JPEG Picture Encoding Format Register */
#define CIF_JPE_PIC_FORMAT /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_PIC_FORMAT*)0xF90E3820u)

/** Alias (User Manual Name) for CIF_JPE_PIC_FORMAT.
* To use register names with standard convension, please use CIF_JPE_PIC_FORMAT.
*/
#define	CIFJPE_PIC_FORMAT	(CIF_JPE_PIC_FORMAT)

/** \brief  1924, JPE Restart Marker Insertion Register */
#define CIF_JPE_RESTART_INTERVAL /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_RESTART_INTERVAL*)0xF90E3824u)

/** Alias (User Manual Name) for CIF_JPE_RESTART_INTERVAL.
* To use register names with standard convension, please use CIF_JPE_RESTART_INTERVAL.
*/
#define	CIFJPE_RESTART_INTERVAL	(CIF_JPE_RESTART_INTERVAL)

/** \brief  1988, JPEG Status Interrupt Clear Register */
#define CIF_JPE_STATUS_ICR /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_STATUS_ICR*)0xF90E3888u)

/** Alias (User Manual Name) for CIF_JPE_STATUS_ICR.
* To use register names with standard convension, please use CIF_JPE_STATUS_ICR.
*/
#define	CIFJPE_STATUS_ICR	(CIF_JPE_STATUS_ICR)

/** \brief  197C, JPEG Status Interrupt Mask Register */
#define CIF_JPE_STATUS_IMR /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_STATUS_IMR*)0xF90E387Cu)

/** Alias (User Manual Name) for CIF_JPE_STATUS_IMR.
* To use register names with standard convension, please use CIF_JPE_STATUS_IMR.
*/
#define	CIFJPE_STATUS_IMR	(CIF_JPE_STATUS_IMR)

/** \brief  198C, JPEG Status Interrupt Set Register */
#define CIF_JPE_STATUS_ISR /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_STATUS_ISR*)0xF90E388Cu)

/** Alias (User Manual Name) for CIF_JPE_STATUS_ISR.
* To use register names with standard convension, please use CIF_JPE_STATUS_ISR.
*/
#define	CIFJPE_STATUS_ISR	(CIF_JPE_STATUS_ISR)

/** \brief  1984, JPEG Status Masked Interrupt Status Register */
#define CIF_JPE_STATUS_MIS /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_STATUS_MIS*)0xF90E3884u)

/** Alias (User Manual Name) for CIF_JPE_STATUS_MIS.
* To use register names with standard convension, please use CIF_JPE_STATUS_MIS.
*/
#define	CIFJPE_STATUS_MIS	(CIF_JPE_STATUS_MIS)

/** \brief  1980, JPEG Status Raw Interrupt Status Register */
#define CIF_JPE_STATUS_RIS /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_STATUS_RIS*)0xF90E3880u)

/** Alias (User Manual Name) for CIF_JPE_STATUS_RIS.
* To use register names with standard convension, please use CIF_JPE_STATUS_RIS.
*/
#define	CIFJPE_STATUS_RIS	(CIF_JPE_STATUS_RIS)

/** \brief  193C, JPE Table Programming Register */
#define CIF_JPE_TABLE_DATA /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TABLE_DATA*)0xF90E383Cu)

/** Alias (User Manual Name) for CIF_JPE_TABLE_DATA.
* To use register names with standard convension, please use CIF_JPE_TABLE_DATA.
*/
#define	CIFJPE_TABLE_DATA	(CIF_JPE_TABLE_DATA)

/** \brief  1914, JPE Header Generation Debug Register */
#define CIF_JPE_TABLE_FLUSH /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TABLE_FLUSH*)0xF90E3814u)

/** Alias (User Manual Name) for CIF_JPE_TABLE_FLUSH.
* To use register names with standard convension, please use CIF_JPE_TABLE_FLUSH.
*/
#define	CIFJPE_TABLE_FLUSH	(CIF_JPE_TABLE_FLUSH)

/** \brief  1940, JPE Table Programming Select Register */
#define CIF_JPE_TABLE_ID /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TABLE_ID*)0xF90E3840u)

/** Alias (User Manual Name) for CIF_JPE_TABLE_ID.
* To use register names with standard convension, please use CIF_JPE_TABLE_ID.
*/
#define	CIFJPE_TABLE_ID	(CIF_JPE_TABLE_ID)

/** \brief  1944, JPE Huffman AC Table 0 Length Register */
#define CIF_JPE_TAC0_LEN /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TAC0_LEN*)0xF90E3844u)

/** Alias (User Manual Name) for CIF_JPE_TAC0_LEN.
* To use register names with standard convension, please use CIF_JPE_TAC0_LEN.
*/
#define	CIFJPE_TAC0_LEN	(CIF_JPE_TAC0_LEN)

/** \brief  194C, JPE Huffman AC Table 1 Length Register */
#define CIF_JPE_TAC1_LEN /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TAC1_LEN*)0xF90E384Cu)

/** Alias (User Manual Name) for CIF_JPE_TAC1_LEN.
* To use register names with standard convension, please use CIF_JPE_TAC1_LEN.
*/
#define	CIFJPE_TAC1_LEN	(CIF_JPE_TAC1_LEN)

/** \brief  1948, JPE Huffman DC Table 0 Length Register */
#define CIF_JPE_TDC0_LEN /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TDC0_LEN*)0xF90E3848u)

/** Alias (User Manual Name) for CIF_JPE_TDC0_LEN.
* To use register names with standard convension, please use CIF_JPE_TDC0_LEN.
*/
#define	CIFJPE_TDC0_LEN	(CIF_JPE_TDC0_LEN)

/** \brief  1950, JPE Huffman DC Table 1 Length Register */
#define CIF_JPE_TDC1_LEN /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TDC1_LEN*)0xF90E3850u)

/** Alias (User Manual Name) for CIF_JPE_TDC1_LEN.
* To use register names with standard convension, please use CIF_JPE_TDC1_LEN.
*/
#define	CIFJPE_TDC1_LEN	(CIF_JPE_TDC1_LEN)

/** \brief  192C, Q- table Selector 1, Quant. Table For U Component */
#define CIF_JPE_TQ_U_SELECT /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TQ_U_SELECT*)0xF90E382Cu)

/** Alias (User Manual Name) for CIF_JPE_TQ_U_SELECT.
* To use register names with standard convension, please use CIF_JPE_TQ_U_SELECT.
*/
#define	CIFJPE_TQ_U_SELECT	(CIF_JPE_TQ_U_SELECT)

/** \brief  1930, Q- table Selector 2 Quant Table For V Component */
#define CIF_JPE_TQ_V_SELECT /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TQ_V_SELECT*)0xF90E3830u)

/** Alias (User Manual Name) for CIF_JPE_TQ_V_SELECT.
* To use register names with standard convension, please use CIF_JPE_TQ_V_SELECT.
*/
#define	CIFJPE_TQ_V_SELECT	(CIF_JPE_TQ_V_SELECT)

/** \brief  1928, Q- table Selector 0 Quant Table For Y Component */
#define CIF_JPE_TQ_Y_SELECT /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_TQ_Y_SELECT*)0xF90E3828u)

/** Alias (User Manual Name) for CIF_JPE_TQ_Y_SELECT.
* To use register names with standard convension, please use CIF_JPE_TQ_Y_SELECT.
*/
#define	CIFJPE_TQ_Y_SELECT	(CIF_JPE_TQ_Y_SELECT)

/** \brief  190C, JPE Y Value Scaling Control Register */
#define CIF_JPE_Y_SCALE_EN /*lint --e(923)*/ (*(volatile Ifx_CIF_JPE_Y_SCALE_EN*)0xF90E380Cu)

/** Alias (User Manual Name) for CIF_JPE_Y_SCALE_EN.
* To use register names with standard convension, please use CIF_JPE_Y_SCALE_EN.
*/
#define	CIFJPE_Y_SCALE_EN	(CIF_JPE_Y_SCALE_EN)

/** \brief  2600, Linear Downscaler Control Register */
#define CIF_LDS_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_LDS_CTRL*)0xF90E4500u)

/** Alias (User Manual Name) for CIF_LDS_CTRL.
* To use register names with standard convension, please use CIF_LDS_CTRL.
*/
#define	CIFLDS_CTRL	(CIF_LDS_CTRL)

/** \brief  2604, Linear Downscaler Factor Register */
#define CIF_LDS_FAC /*lint --e(923)*/ (*(volatile Ifx_CIF_LDS_FAC*)0xF90E4504u)

/** Alias (User Manual Name) for CIF_LDS_FAC.
* To use register names with standard convension, please use CIF_LDS_FAC.
*/
#define	CIFLDS_FAC	(CIF_LDS_FAC)

/** \brief  1570, Memory Interface Counter Value of JPEG or RAW Data Bytes
 * Register */
#define CIF_MI_BYTE_CNT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_BYTE_CNT*)0xF90E3470u)

/** Alias (User Manual Name) for CIF_MI_BYTE_CNT.
* To use register names with standard convension, please use CIF_MI_BYTE_CNT.
*/
#define	CIFMI_BYTE_CNT	(CIF_MI_BYTE_CNT)

/** \brief  1500, Memory Interface Global Control Register */
#define CIF_MI_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_CTRL*)0xF90E3400u)

/** Alias (User Manual Name) for CIF_MI_CTRL.
* To use register names with standard convension, please use CIF_MI_CTRL.
*/
#define	CIFMI_CTRL	(CIF_MI_CTRL)

/** \brief  1574, Memory Interface Global Control Internal Shadow Register */
#define CIF_MI_CTRL_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_CTRL_SHD*)0xF90E3474u)

/** Alias (User Manual Name) for CIF_MI_CTRL_SHD.
* To use register names with standard convension, please use CIF_MI_CTRL_SHD.
*/
#define	CIFMI_CTRL_SHD	(CIF_MI_CTRL_SHD)

/** \brief  1604, MI Interrupt Clear Register */
#define CIF_MI_ICR /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_ICR*)0xF90E3504u)

/** Alias (User Manual Name) for CIF_MI_ICR.
* To use register names with standard convension, please use CIF_MI_ICR.
*/
#define	CIFMI_ICR	(CIF_MI_ICR)

/** \brief  15F8, MI Interrupt Mask ‘1’ interrupt active ‘0’ interrupt masked */
#define CIF_MI_IMSC /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_IMSC*)0xF90E34F8u)

/** Alias (User Manual Name) for CIF_MI_IMSC.
* To use register names with standard convension, please use CIF_MI_IMSC.
*/
#define	CIFMI_IMSC	(CIF_MI_IMSC)

/** \brief  1504, Memory Interface Control Register For Address Init And Skip
 * Function Register */
#define CIF_MI_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_INIT*)0xF90E3404u)

/** Alias (User Manual Name) for CIF_MI_INIT.
* To use register names with standard convension, please use CIF_MI_INIT.
*/
#define	CIFMI_INIT	(CIF_MI_INIT)

/** \brief  1608, MI Interrupt Set Register */
#define CIF_MI_ISR /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_ISR*)0xF90E3508u)

/** Alias (User Manual Name) for CIF_MI_ISR.
* To use register names with standard convension, please use CIF_MI_ISR.
*/
#define	CIFMI_ISR	(CIF_MI_ISR)

/** \brief  1600, MI Masked Interrupt Status Registe */
#define CIF_MI_MIS /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MIS*)0xF90E3500u)

/** Alias (User Manual Name) for CIF_MI_MIS.
* To use register names with standard convension, please use CIF_MI_MIS.
*/
#define	CIFMI_MIS	(CIF_MI_MIS)

/** \brief  151C, Memory Interface Base Address For Main Picture Cb Component
 * Ring Buffer Register */
#define CIF_MI_MP_CB_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CB_BASE_AD_INIT*)0xF90E341Cu)

/** Alias (User Manual Name) for CIF_MI_MP_CB_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MI_MP_CB_BASE_AD_INIT.
*/
#define	CIFMI_MP_CB_BASE_AD_INIT	(CIF_MI_MP_CB_BASE_AD_INIT)

/** \brief  1588, Memory Interface Base Address Shadow Register For Main Picture
 * Cb Component Ring Register */
#define CIF_MI_MP_CB_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CB_BASE_AD_SHD*)0xF90E3488u)

/** Alias (User Manual Name) for CIF_MI_MP_CB_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MI_MP_CB_BASE_AD_SHD.
*/
#define	CIFMI_MP_CB_BASE_AD_SHD	(CIF_MI_MP_CB_BASE_AD_SHD)

/** \brief  1524, Memory Interface Offset Counter Init Value For Main Picture Cb
 * Component Ring Buffer Register */
#define CIF_MI_MP_CB_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CB_OFFS_CNT_INIT*)0xF90E3424u)

/** Alias (User Manual Name) for CIF_MI_MP_CB_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MI_MP_CB_OFFS_CNT_INIT.
*/
#define	CIFMI_MP_CB_OFFS_CNT_INIT	(CIF_MI_MP_CB_OFFS_CNT_INIT)

/** \brief  1590, Memory Interface Current Offset Counter Of Main Picture Cb
 * Component Ring Buffer Register */
#define CIF_MI_MP_CB_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CB_OFFS_CNT_SHD*)0xF90E3490u)

/** Alias (User Manual Name) for CIF_MI_MP_CB_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MI_MP_CB_OFFS_CNT_SHD.
*/
#define	CIFMI_MP_CB_OFFS_CNT_SHD	(CIF_MI_MP_CB_OFFS_CNT_SHD)

/** \brief  1528, Memory Interface Offset Counter Start Value For Main Picture
 * Cb Component Ring Buffer Register */
#define CIF_MI_MP_CB_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CB_OFFS_CNT_START*)0xF90E3428u)

/** Alias (User Manual Name) for CIF_MI_MP_CB_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MI_MP_CB_OFFS_CNT_START.
*/
#define	CIFMI_MP_CB_OFFS_CNT_START	(CIF_MI_MP_CB_OFFS_CNT_START)

/** \brief  1520, Memory Interface Size Of Main Picture Cb Component Ring Buffer
 * Register */
#define CIF_MI_MP_CB_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CB_SIZE_INIT*)0xF90E3420u)

/** Alias (User Manual Name) for CIF_MI_MP_CB_SIZE_INIT.
* To use register names with standard convension, please use CIF_MI_MP_CB_SIZE_INIT.
*/
#define	CIFMI_MP_CB_SIZE_INIT	(CIF_MI_MP_CB_SIZE_INIT)

/** \brief  158C, Memory Interface Size Shadow Register Of Main Picture Cb
 * Component Ring Buffer Register */
#define CIF_MI_MP_CB_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CB_SIZE_SHD*)0xF90E348Cu)

/** Alias (User Manual Name) for CIF_MI_MP_CB_SIZE_SHD.
* To use register names with standard convension, please use CIF_MI_MP_CB_SIZE_SHD.
*/
#define	CIFMI_MP_CB_SIZE_SHD	(CIF_MI_MP_CB_SIZE_SHD)

/** \brief  152C, Memory Interface Base Address For Main Picture Cr Component
 * Ring Buffer Register */
#define CIF_MI_MP_CR_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CR_BASE_AD_INIT*)0xF90E342Cu)

/** Alias (User Manual Name) for CIF_MI_MP_CR_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MI_MP_CR_BASE_AD_INIT.
*/
#define	CIFMI_MP_CR_BASE_AD_INIT	(CIF_MI_MP_CR_BASE_AD_INIT)

/** \brief  1594, Memory Interface Base Address Shadow Register For Main Picture
 * Cr Component Ring Register */
#define CIF_MI_MP_CR_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CR_BASE_AD_SHD*)0xF90E3494u)

/** Alias (User Manual Name) for CIF_MI_MP_CR_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MI_MP_CR_BASE_AD_SHD.
*/
#define	CIFMI_MP_CR_BASE_AD_SHD	(CIF_MI_MP_CR_BASE_AD_SHD)

/** \brief  1534, Memory Interface Offset Counter Init value For Main Picture Cr
 * Component Ring Buffer Register */
#define CIF_MI_MP_CR_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CR_OFFS_CNT_INIT*)0xF90E3434u)

/** Alias (User Manual Name) for CIF_MI_MP_CR_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MI_MP_CR_OFFS_CNT_INIT.
*/
#define	CIFMI_MP_CR_OFFS_CNT_INIT	(CIF_MI_MP_CR_OFFS_CNT_INIT)

/** \brief  159C, Memory Interface Current Offset Counter Of Main Picture Cr
 * Component Ring Buffer Register */
#define CIF_MI_MP_CR_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CR_OFFS_CNT_SHD*)0xF90E349Cu)

/** Alias (User Manual Name) for CIF_MI_MP_CR_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MI_MP_CR_OFFS_CNT_SHD.
*/
#define	CIFMI_MP_CR_OFFS_CNT_SHD	(CIF_MI_MP_CR_OFFS_CNT_SHD)

/** \brief  1538, Memory Interface Offset Counter Start Value For Main Picture
 * Cr Component Ring Buffer Register */
#define CIF_MI_MP_CR_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CR_OFFS_CNT_START*)0xF90E3438u)

/** Alias (User Manual Name) for CIF_MI_MP_CR_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MI_MP_CR_OFFS_CNT_START.
*/
#define	CIFMI_MP_CR_OFFS_CNT_START	(CIF_MI_MP_CR_OFFS_CNT_START)

/** \brief  1530, Memory Interface Size Of Main Picture Cr Component Ring Buffer
 * Register */
#define CIF_MI_MP_CR_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CR_SIZE_INIT*)0xF90E3430u)

/** Alias (User Manual Name) for CIF_MI_MP_CR_SIZE_INIT.
* To use register names with standard convension, please use CIF_MI_MP_CR_SIZE_INIT.
*/
#define	CIFMI_MP_CR_SIZE_INIT	(CIF_MI_MP_CR_SIZE_INIT)

/** \brief  1598, Memory Interface Size Shadow Register Of Main Picture Cr
 * Component Ring Buffer Register */
#define CIF_MI_MP_CR_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_CR_SIZE_SHD*)0xF90E3498u)

/** Alias (User Manual Name) for CIF_MI_MP_CR_SIZE_SHD.
* To use register names with standard convension, please use CIF_MI_MP_CR_SIZE_SHD.
*/
#define	CIFMI_MP_CR_SIZE_SHD	(CIF_MI_MP_CR_SIZE_SHD)

/** \brief  1508, Memory Interface Base Address For Main Picture Y Component,
 * JPEG or RAW Data Register */
#define CIF_MI_MP_Y_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_BASE_AD_INIT*)0xF90E3408u)

/** Alias (User Manual Name) for CIF_MI_MP_Y_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MI_MP_Y_BASE_AD_INIT.
*/
#define	CIFMI_MP_Y_BASE_AD_INIT	(CIF_MI_MP_Y_BASE_AD_INIT)

/** \brief  1578, Memory Interface Base Address Shadow Register For Main Picture
 * Y Component, JPEG Register */
#define CIF_MI_MP_Y_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_BASE_AD_SHD*)0xF90E3478u)

/** Alias (User Manual Name) for CIF_MI_MP_Y_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MI_MP_Y_BASE_AD_SHD.
*/
#define	CIFMI_MP_Y_BASE_AD_SHD	(CIF_MI_MP_Y_BASE_AD_SHD)

/** \brief  1518, Memory Interface Fill Level Interrupt Offset Value For Main
 * Picture Y, JPEG or RAW Data Register */
#define CIF_MI_MP_Y_IRQ_OFFS_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_IRQ_OFFS_INIT*)0xF90E3418u)

/** Alias (User Manual Name) for CIF_MI_MP_Y_IRQ_OFFS_INIT.
* To use register names with standard convension, please use CIF_MI_MP_Y_IRQ_OFFS_INIT.
*/
#define	CIFMI_MP_Y_IRQ_OFFS_INIT	(CIF_MI_MP_Y_IRQ_OFFS_INIT)

/** \brief  1584, Memory Interface Shadow Register of Fill Level Interrupt
 * Offset Value For Main Picture Y Register */
#define CIF_MI_MP_Y_IRQ_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_IRQ_OFFS_SHD*)0xF90E3484u)

/** Alias (User Manual Name) for CIF_MI_MP_Y_IRQ_OFFS_SHD.
* To use register names with standard convension, please use CIF_MI_MP_Y_IRQ_OFFS_SHD.
*/
#define	CIFMI_MP_Y_IRQ_OFFS_SHD	(CIF_MI_MP_Y_IRQ_OFFS_SHD)

/** \brief  1510, Memory Interface Offset Counter Init Value For Main Picture Y,
 * JPEG or RAW Data Register */
#define CIF_MI_MP_Y_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_OFFS_CNT_INIT*)0xF90E3410u)

/** Alias (User Manual Name) for CIF_MI_MP_Y_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MI_MP_Y_OFFS_CNT_INIT.
*/
#define	CIFMI_MP_Y_OFFS_CNT_INIT	(CIF_MI_MP_Y_OFFS_CNT_INIT)

/** \brief  1580, Memory Interface Current Offset Counter of Main Picture Y
 * Component JPEG or RAW Register */
#define CIF_MI_MP_Y_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_OFFS_CNT_SHD*)0xF90E3480u)

/** Alias (User Manual Name) for CIF_MI_MP_Y_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MI_MP_Y_OFFS_CNT_SHD.
*/
#define	CIFMI_MP_Y_OFFS_CNT_SHD	(CIF_MI_MP_Y_OFFS_CNT_SHD)

/** \brief  1514, Memory Interface Offset Counter Start Value For Main Picture
 * Y, JPEG or RAW Data Register */
#define CIF_MI_MP_Y_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_OFFS_CNT_START*)0xF90E3414u)

/** Alias (User Manual Name) for CIF_MI_MP_Y_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MI_MP_Y_OFFS_CNT_START.
*/
#define	CIFMI_MP_Y_OFFS_CNT_START	(CIF_MI_MP_Y_OFFS_CNT_START)

/** \brief  150C, Memory Interface Size of main picture Y component, JPEG or RAW
 * data Register */
#define CIF_MI_MP_Y_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_SIZE_INIT*)0xF90E340Cu)

/** Alias (User Manual Name) for CIF_MI_MP_Y_SIZE_INIT.
* To use register names with standard convension, please use CIF_MI_MP_Y_SIZE_INIT.
*/
#define	CIFMI_MP_Y_SIZE_INIT	(CIF_MI_MP_Y_SIZE_INIT)

/** \brief  157C, Memory Interface Size Shadow Register of Main Picture Y
 * Component,JPEG or RAW Data Register */
#define CIF_MI_MP_Y_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_MP_Y_SIZE_SHD*)0xF90E347Cu)

/** Alias (User Manual Name) for CIF_MI_MP_Y_SIZE_SHD.
* To use register names with standard convension, please use CIF_MI_MP_Y_SIZE_SHD.
*/
#define	CIFMI_MP_Y_SIZE_SHD	(CIF_MI_MP_Y_SIZE_SHD)

/** \brief  15FC, MI Raw Interrupt Status Register */
#define CIF_MI_RIS /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_RIS*)0xF90E34FCu)

/** Alias (User Manual Name) for CIF_MI_RIS.
* To use register names with standard convension, please use CIF_MI_RIS.
*/
#define	CIFMI_RIS	(CIF_MI_RIS)

/** \brief  160C, MI Status Register */
#define CIF_MI_STATUS /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_STATUS*)0xF90E350Cu)

/** Alias (User Manual Name) for CIF_MI_STATUS.
* To use register names with standard convension, please use CIF_MI_STATUS.
*/
#define	CIFMI_STATUS	(CIF_MI_STATUS)

/** \brief  1610, MI Status Clear Register */
#define CIF_MI_STATUS_CLR /*lint --e(923)*/ (*(volatile Ifx_CIF_MI_STATUS_CLR*)0xF90E3510u)

/** Alias (User Manual Name) for CIF_MI_STATUS_CLR.
* To use register names with standard convension, please use CIF_MI_STATUS_CLR.
*/
#define	CIFMI_STATUS_CLR	(CIF_MI_STATUS_CLR)

/** \brief  3608, Memory Interface Base Address For Extra Path Data Buffer
 * Register */
#define CIF_MIEP_CH_1S0_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_INIT*)0xF90E5508u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_BASE_AD_INIT.
*/
#define	CIFMIEP_1_BASE_AD_INIT	(CIF_MIEP_CH_1S0_BASE_AD_INIT)

/** \brief  3620, Memory Interface Base Address Shadow Register for Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S0_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_SHD*)0xF90E5520u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_BASE_AD_SHD.
*/
#define	CIFMIEP_1_BASE_AD_SHD	(CIF_MIEP_CH_1S0_BASE_AD_SHD)

/** \brief  3600, Memory Interface Extra Path Control Register */
#define CIF_MIEP_CH_1S0_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL*)0xF90E5500u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_CTRL.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_CTRL.
*/
#define	CIFMIEP_1_CTRL	(CIF_MIEP_CH_1S0_CTRL)

/** \brief  361C, Memory Interface Extra Path Control Internal Shadow Register */
#define CIF_MIEP_CH_1S0_CTRL_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL_SHD*)0xF90E551Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_CTRL_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_CTRL_SHD.
*/
#define	CIFMIEP_1_CTRL_SHD	(CIF_MIEP_CH_1S0_CTRL_SHD)

/** \brief  3604, Memory Interface Extra Path Control Register For Address Init
 * And Skip Function Register */
#define CIF_MIEP_CH_1S0_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_INIT*)0xF90E5504u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_INIT.
*/
#define	CIFMIEP_1_INIT	(CIF_MIEP_CH_1S0_INIT)

/** \brief  3618, Memory Interface Fill Level Interrupt Offset Value For Extra
 * Path Register */
#define CIF_MIEP_CH_1S0_IRQ_OFFS_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_INIT*)0xF90E5518u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_IRQ_OFFS_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_IRQ_OFFS_INIT.
*/
#define	CIFMIEP_1_IRQ_OFFS_INIT	(CIF_MIEP_CH_1S0_IRQ_OFFS_INIT)

/** \brief  362C, Memory Interface Shadow Register of Fill Level Interrupt
 * Offset Value For Extra Path Register */
#define CIF_MIEP_CH_1S0_IRQ_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_SHD*)0xF90E552Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_IRQ_OFFS_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_IRQ_OFFS_SHD.
*/
#define	CIFMIEP_1_IRQ_OFFS_SHD	(CIF_MIEP_CH_1S0_IRQ_OFFS_SHD)

/** \brief  3610, Memory Interface Offset Counter Init Value For Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S0_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_INIT*)0xF90E5510u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_OFFS_CNT_INIT.
*/
#define	CIFMIEP_1_OFFS_CNT_INIT	(CIF_MIEP_CH_1S0_OFFS_CNT_INIT)

/** \brief  3628, Memory Interface Current Offset Counter of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S0_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_SHD*)0xF90E5528u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_OFFS_CNT_SHD.
*/
#define	CIFMIEP_1_OFFS_CNT_SHD	(CIF_MIEP_CH_1S0_OFFS_CNT_SHD)

/** \brief  3614, Memory Interface Offset Counter Start Value For Extra Path
 * Register */
#define CIF_MIEP_CH_1S0_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_START*)0xF90E5514u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_OFFS_CNT_START.
*/
#define	CIFMIEP_1_OFFS_CNT_START	(CIF_MIEP_CH_1S0_OFFS_CNT_START)

/** \brief  360C, Memory Interface Size of Extra Path Data Buffer Register */
#define CIF_MIEP_CH_1S0_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_INIT*)0xF90E550Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_SIZE_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_SIZE_INIT.
*/
#define	CIFMIEP_1_SIZE_INIT	(CIF_MIEP_CH_1S0_SIZE_INIT)

/** \brief  3624, Memory Interface Size Shadow Register of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S0_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_SHD*)0xF90E5524u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S0_SIZE_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S0_SIZE_SHD.
*/
#define	CIFMIEP_1_SIZE_SHD	(CIF_MIEP_CH_1S0_SIZE_SHD)

/** \brief  3708, Memory Interface Base Address For Extra Path Data Buffer
 * Register */
#define CIF_MIEP_CH_1S1_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_INIT*)0xF90E5608u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_BASE_AD_INIT.
*/
#define	CIFMIEP_2_BASE_AD_INIT	(CIF_MIEP_CH_1S1_BASE_AD_INIT)

/** \brief  3720, Memory Interface Base Address Shadow Register for Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S1_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_SHD*)0xF90E5620u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_BASE_AD_SHD.
*/
#define	CIFMIEP_2_BASE_AD_SHD	(CIF_MIEP_CH_1S1_BASE_AD_SHD)

/** \brief  3700, Memory Interface Extra Path Control Register */
#define CIF_MIEP_CH_1S1_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL*)0xF90E5600u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_CTRL.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_CTRL.
*/
#define	CIFMIEP_2_CTRL	(CIF_MIEP_CH_1S1_CTRL)

/** \brief  371C, Memory Interface Extra Path Control Internal Shadow Register */
#define CIF_MIEP_CH_1S1_CTRL_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL_SHD*)0xF90E561Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_CTRL_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_CTRL_SHD.
*/
#define	CIFMIEP_2_CTRL_SHD	(CIF_MIEP_CH_1S1_CTRL_SHD)

/** \brief  3704, Memory Interface Extra Path Control Register For Address Init
 * And Skip Function Register */
#define CIF_MIEP_CH_1S1_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_INIT*)0xF90E5604u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_INIT.
*/
#define	CIFMIEP_2_INIT	(CIF_MIEP_CH_1S1_INIT)

/** \brief  3718, Memory Interface Fill Level Interrupt Offset Value For Extra
 * Path Register */
#define CIF_MIEP_CH_1S1_IRQ_OFFS_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_INIT*)0xF90E5618u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_IRQ_OFFS_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_IRQ_OFFS_INIT.
*/
#define	CIFMIEP_2_IRQ_OFFS_INIT	(CIF_MIEP_CH_1S1_IRQ_OFFS_INIT)

/** \brief  372C, Memory Interface Shadow Register of Fill Level Interrupt
 * Offset Value For Extra Path Register */
#define CIF_MIEP_CH_1S1_IRQ_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_SHD*)0xF90E562Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_IRQ_OFFS_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_IRQ_OFFS_SHD.
*/
#define	CIFMIEP_2_IRQ_OFFS_SHD	(CIF_MIEP_CH_1S1_IRQ_OFFS_SHD)

/** \brief  3710, Memory Interface Offset Counter Init Value For Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S1_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_INIT*)0xF90E5610u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_OFFS_CNT_INIT.
*/
#define	CIFMIEP_2_OFFS_CNT_INIT	(CIF_MIEP_CH_1S1_OFFS_CNT_INIT)

/** \brief  3728, Memory Interface Current Offset Counter of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S1_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_SHD*)0xF90E5628u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_OFFS_CNT_SHD.
*/
#define	CIFMIEP_2_OFFS_CNT_SHD	(CIF_MIEP_CH_1S1_OFFS_CNT_SHD)

/** \brief  3714, Memory Interface Offset Counter Start Value For Extra Path
 * Register */
#define CIF_MIEP_CH_1S1_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_START*)0xF90E5614u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_OFFS_CNT_START.
*/
#define	CIFMIEP_2_OFFS_CNT_START	(CIF_MIEP_CH_1S1_OFFS_CNT_START)

/** \brief  370C, Memory Interface Size of Extra Path Data Buffer Register */
#define CIF_MIEP_CH_1S1_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_INIT*)0xF90E560Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_SIZE_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_SIZE_INIT.
*/
#define	CIFMIEP_2_SIZE_INIT	(CIF_MIEP_CH_1S1_SIZE_INIT)

/** \brief  3724, Memory Interface Size Shadow Register of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S1_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_SHD*)0xF90E5624u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S1_SIZE_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S1_SIZE_SHD.
*/
#define	CIFMIEP_2_SIZE_SHD	(CIF_MIEP_CH_1S1_SIZE_SHD)

/** \brief  3808, Memory Interface Base Address For Extra Path Data Buffer
 * Register */
#define CIF_MIEP_CH_1S2_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_INIT*)0xF90E5708u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_BASE_AD_INIT.
*/
#define	CIFMIEP_3_BASE_AD_INIT	(CIF_MIEP_CH_1S2_BASE_AD_INIT)

/** \brief  3820, Memory Interface Base Address Shadow Register for Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S2_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_SHD*)0xF90E5720u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_BASE_AD_SHD.
*/
#define	CIFMIEP_3_BASE_AD_SHD	(CIF_MIEP_CH_1S2_BASE_AD_SHD)

/** \brief  3800, Memory Interface Extra Path Control Register */
#define CIF_MIEP_CH_1S2_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL*)0xF90E5700u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_CTRL.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_CTRL.
*/
#define	CIFMIEP_3_CTRL	(CIF_MIEP_CH_1S2_CTRL)

/** \brief  381C, Memory Interface Extra Path Control Internal Shadow Register */
#define CIF_MIEP_CH_1S2_CTRL_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL_SHD*)0xF90E571Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_CTRL_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_CTRL_SHD.
*/
#define	CIFMIEP_3_CTRL_SHD	(CIF_MIEP_CH_1S2_CTRL_SHD)

/** \brief  3804, Memory Interface Extra Path Control Register For Address Init
 * And Skip Function Register */
#define CIF_MIEP_CH_1S2_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_INIT*)0xF90E5704u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_INIT.
*/
#define	CIFMIEP_3_INIT	(CIF_MIEP_CH_1S2_INIT)

/** \brief  3818, Memory Interface Fill Level Interrupt Offset Value For Extra
 * Path Register */
#define CIF_MIEP_CH_1S2_IRQ_OFFS_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_INIT*)0xF90E5718u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_IRQ_OFFS_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_IRQ_OFFS_INIT.
*/
#define	CIFMIEP_3_IRQ_OFFS_INIT	(CIF_MIEP_CH_1S2_IRQ_OFFS_INIT)

/** \brief  382C, Memory Interface Shadow Register of Fill Level Interrupt
 * Offset Value For Extra Path Register */
#define CIF_MIEP_CH_1S2_IRQ_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_SHD*)0xF90E572Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_IRQ_OFFS_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_IRQ_OFFS_SHD.
*/
#define	CIFMIEP_3_IRQ_OFFS_SHD	(CIF_MIEP_CH_1S2_IRQ_OFFS_SHD)

/** \brief  3810, Memory Interface Offset Counter Init Value For Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S2_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_INIT*)0xF90E5710u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_OFFS_CNT_INIT.
*/
#define	CIFMIEP_3_OFFS_CNT_INIT	(CIF_MIEP_CH_1S2_OFFS_CNT_INIT)

/** \brief  3828, Memory Interface Current Offset Counter of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S2_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_SHD*)0xF90E5728u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_OFFS_CNT_SHD.
*/
#define	CIFMIEP_3_OFFS_CNT_SHD	(CIF_MIEP_CH_1S2_OFFS_CNT_SHD)

/** \brief  3814, Memory Interface Offset Counter Start Value For Extra Path
 * Register */
#define CIF_MIEP_CH_1S2_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_START*)0xF90E5714u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_OFFS_CNT_START.
*/
#define	CIFMIEP_3_OFFS_CNT_START	(CIF_MIEP_CH_1S2_OFFS_CNT_START)

/** \brief  380C, Memory Interface Size of Extra Path Data Buffer Register */
#define CIF_MIEP_CH_1S2_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_INIT*)0xF90E570Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_SIZE_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_SIZE_INIT.
*/
#define	CIFMIEP_3_SIZE_INIT	(CIF_MIEP_CH_1S2_SIZE_INIT)

/** \brief  3824, Memory Interface Size Shadow Register of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S2_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_SHD*)0xF90E5724u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S2_SIZE_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S2_SIZE_SHD.
*/
#define	CIFMIEP_3_SIZE_SHD	(CIF_MIEP_CH_1S2_SIZE_SHD)

/** \brief  3908, Memory Interface Base Address For Extra Path Data Buffer
 * Register */
#define CIF_MIEP_CH_1S3_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_INIT*)0xF90E5808u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_BASE_AD_INIT.
*/
#define	CIFMIEP_4_BASE_AD_INIT	(CIF_MIEP_CH_1S3_BASE_AD_INIT)

/** \brief  3920, Memory Interface Base Address Shadow Register for Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S3_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_SHD*)0xF90E5820u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_BASE_AD_SHD.
*/
#define	CIFMIEP_4_BASE_AD_SHD	(CIF_MIEP_CH_1S3_BASE_AD_SHD)

/** \brief  3900, Memory Interface Extra Path Control Register */
#define CIF_MIEP_CH_1S3_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL*)0xF90E5800u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_CTRL.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_CTRL.
*/
#define	CIFMIEP_4_CTRL	(CIF_MIEP_CH_1S3_CTRL)

/** \brief  391C, Memory Interface Extra Path Control Internal Shadow Register */
#define CIF_MIEP_CH_1S3_CTRL_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL_SHD*)0xF90E581Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_CTRL_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_CTRL_SHD.
*/
#define	CIFMIEP_4_CTRL_SHD	(CIF_MIEP_CH_1S3_CTRL_SHD)

/** \brief  3904, Memory Interface Extra Path Control Register For Address Init
 * And Skip Function Register */
#define CIF_MIEP_CH_1S3_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_INIT*)0xF90E5804u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_INIT.
*/
#define	CIFMIEP_4_INIT	(CIF_MIEP_CH_1S3_INIT)

/** \brief  3918, Memory Interface Fill Level Interrupt Offset Value For Extra
 * Path Register */
#define CIF_MIEP_CH_1S3_IRQ_OFFS_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_INIT*)0xF90E5818u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_IRQ_OFFS_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_IRQ_OFFS_INIT.
*/
#define	CIFMIEP_4_IRQ_OFFS_INIT	(CIF_MIEP_CH_1S3_IRQ_OFFS_INIT)

/** \brief  392C, Memory Interface Shadow Register of Fill Level Interrupt
 * Offset Value For Extra Path Register */
#define CIF_MIEP_CH_1S3_IRQ_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_SHD*)0xF90E582Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_IRQ_OFFS_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_IRQ_OFFS_SHD.
*/
#define	CIFMIEP_4_IRQ_OFFS_SHD	(CIF_MIEP_CH_1S3_IRQ_OFFS_SHD)

/** \brief  3910, Memory Interface Offset Counter Init Value For Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S3_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_INIT*)0xF90E5810u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_OFFS_CNT_INIT.
*/
#define	CIFMIEP_4_OFFS_CNT_INIT	(CIF_MIEP_CH_1S3_OFFS_CNT_INIT)

/** \brief  3928, Memory Interface Current Offset Counter of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S3_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_SHD*)0xF90E5828u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_OFFS_CNT_SHD.
*/
#define	CIFMIEP_4_OFFS_CNT_SHD	(CIF_MIEP_CH_1S3_OFFS_CNT_SHD)

/** \brief  3914, Memory Interface Offset Counter Start Value For Extra Path
 * Register */
#define CIF_MIEP_CH_1S3_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_START*)0xF90E5814u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_OFFS_CNT_START.
*/
#define	CIFMIEP_4_OFFS_CNT_START	(CIF_MIEP_CH_1S3_OFFS_CNT_START)

/** \brief  390C, Memory Interface Size of Extra Path Data Buffer Register */
#define CIF_MIEP_CH_1S3_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_INIT*)0xF90E580Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_SIZE_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_SIZE_INIT.
*/
#define	CIFMIEP_4_SIZE_INIT	(CIF_MIEP_CH_1S3_SIZE_INIT)

/** \brief  3924, Memory Interface Size Shadow Register of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S3_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_SHD*)0xF90E5824u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S3_SIZE_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S3_SIZE_SHD.
*/
#define	CIFMIEP_4_SIZE_SHD	(CIF_MIEP_CH_1S3_SIZE_SHD)

/** \brief  3A08, Memory Interface Base Address For Extra Path Data Buffer
 * Register */
#define CIF_MIEP_CH_1S4_BASE_AD_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_INIT*)0xF90E5908u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_BASE_AD_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_BASE_AD_INIT.
*/
#define	CIFMIEP_5_BASE_AD_INIT	(CIF_MIEP_CH_1S4_BASE_AD_INIT)

/** \brief  3A20, Memory Interface Base Address Shadow Register for Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S4_BASE_AD_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_BASE_AD_SHD*)0xF90E5920u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_BASE_AD_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_BASE_AD_SHD.
*/
#define	CIFMIEP_5_BASE_AD_SHD	(CIF_MIEP_CH_1S4_BASE_AD_SHD)

/** \brief  3A00, Memory Interface Extra Path Control Register */
#define CIF_MIEP_CH_1S4_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL*)0xF90E5900u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_CTRL.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_CTRL.
*/
#define	CIFMIEP_5_CTRL	(CIF_MIEP_CH_1S4_CTRL)

/** \brief  3A1C, Memory Interface Extra Path Control Internal Shadow Register */
#define CIF_MIEP_CH_1S4_CTRL_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_CTRL_SHD*)0xF90E591Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_CTRL_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_CTRL_SHD.
*/
#define	CIFMIEP_5_CTRL_SHD	(CIF_MIEP_CH_1S4_CTRL_SHD)

/** \brief  3A04, Memory Interface Extra Path Control Register For Address Init
 * And Skip Function Register */
#define CIF_MIEP_CH_1S4_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_INIT*)0xF90E5904u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_INIT.
*/
#define	CIFMIEP_5_INIT	(CIF_MIEP_CH_1S4_INIT)

/** \brief  3A18, Memory Interface Fill Level Interrupt Offset Value For Extra
 * Path Register */
#define CIF_MIEP_CH_1S4_IRQ_OFFS_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_INIT*)0xF90E5918u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_IRQ_OFFS_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_IRQ_OFFS_INIT.
*/
#define	CIFMIEP_5_IRQ_OFFS_INIT	(CIF_MIEP_CH_1S4_IRQ_OFFS_INIT)

/** \brief  3A2C, Memory Interface Shadow Register of Fill Level Interrupt
 * Offset Value For Extra Path Register */
#define CIF_MIEP_CH_1S4_IRQ_OFFS_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_IRQ_OFFS_SHD*)0xF90E592Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_IRQ_OFFS_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_IRQ_OFFS_SHD.
*/
#define	CIFMIEP_5_IRQ_OFFS_SHD	(CIF_MIEP_CH_1S4_IRQ_OFFS_SHD)

/** \brief  3A10, Memory Interface Offset Counter Init Value For Extra Path
 * Buffer Register */
#define CIF_MIEP_CH_1S4_OFFS_CNT_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_INIT*)0xF90E5910u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_OFFS_CNT_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_OFFS_CNT_INIT.
*/
#define	CIFMIEP_5_OFFS_CNT_INIT	(CIF_MIEP_CH_1S4_OFFS_CNT_INIT)

/** \brief  3A28, Memory Interface Current Offset Counter of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S4_OFFS_CNT_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_SHD*)0xF90E5928u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_OFFS_CNT_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_OFFS_CNT_SHD.
*/
#define	CIFMIEP_5_OFFS_CNT_SHD	(CIF_MIEP_CH_1S4_OFFS_CNT_SHD)

/** \brief  3A14, Memory Interface Offset Counter Start Value For Extra Path
 * Register */
#define CIF_MIEP_CH_1S4_OFFS_CNT_START /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_OFFS_CNT_START*)0xF90E5914u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_OFFS_CNT_START.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_OFFS_CNT_START.
*/
#define	CIFMIEP_5_OFFS_CNT_START	(CIF_MIEP_CH_1S4_OFFS_CNT_START)

/** \brief  3A0C, Memory Interface Size of Extra Path Data Buffer Register */
#define CIF_MIEP_CH_1S4_SIZE_INIT /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_INIT*)0xF90E590Cu)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_SIZE_INIT.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_SIZE_INIT.
*/
#define	CIFMIEP_5_SIZE_INIT	(CIF_MIEP_CH_1S4_SIZE_INIT)

/** \brief  3A24, Memory Interface Size Shadow Register of Extra Path Buffer
 * Register */
#define CIF_MIEP_CH_1S4_SIZE_SHD /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_CH_SIZE_SHD*)0xF90E5924u)

/** Alias (User Manual Name) for CIF_MIEP_CH_1S4_SIZE_SHD.
* To use register names with standard convension, please use CIF_MIEP_CH_1S4_SIZE_SHD.
*/
#define	CIFMIEP_5_SIZE_SHD	(CIF_MIEP_CH_1S4_SIZE_SHD)

/** \brief  3514, MI Extra Path Interrupt Clear Register */
#define CIF_MIEP_ICR /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_ICR*)0xF90E5414u)

/** Alias (User Manual Name) for CIF_MIEP_ICR.
* To use register names with standard convension, please use CIF_MIEP_ICR.
*/
#define	CIFMIEP_ICR	(CIF_MIEP_ICR)

/** \brief  3508, MI Extra Path Interrupt Mask ‘1’: interrupt active, ‘0’:
 * interrupt masked */
#define CIF_MIEP_IMSC /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_IMSC*)0xF90E5408u)

/** Alias (User Manual Name) for CIF_MIEP_IMSC.
* To use register names with standard convension, please use CIF_MIEP_IMSC.
*/
#define	CIFMIEP_IMSC	(CIF_MIEP_IMSC)

/** \brief  3518, MI Extra Path Interrupt Set Register */
#define CIF_MIEP_ISR /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_ISR*)0xF90E5418u)

/** Alias (User Manual Name) for CIF_MIEP_ISR.
* To use register names with standard convension, please use CIF_MIEP_ISR.
*/
#define	CIFMIEP_ISR	(CIF_MIEP_ISR)

/** \brief  3510, MI Extra Path Masked Interrupt Status Register */
#define CIF_MIEP_MIS /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_MIS*)0xF90E5410u)

/** Alias (User Manual Name) for CIF_MIEP_MIS.
* To use register names with standard convension, please use CIF_MIEP_MIS.
*/
#define	CIFMIEP_MIS	(CIF_MIEP_MIS)

/** \brief  350C, MI Extra Path Raw Interrupt Status Register */
#define CIF_MIEP_RIS /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_RIS*)0xF90E540Cu)

/** Alias (User Manual Name) for CIF_MIEP_RIS.
* To use register names with standard convension, please use CIF_MIEP_RIS.
*/
#define	CIFMIEP_RIS	(CIF_MIEP_RIS)

/** \brief  3500, Extra Path Error Register */
#define CIF_MIEP_STA_ERR /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_STA_ERR*)0xF90E5400u)

/** Alias (User Manual Name) for CIF_MIEP_STA_ERR.
* To use register names with standard convension, please use CIF_MIEP_STA_ERR.
*/
#define	CIFMIEP_STA_ERR	(CIF_MIEP_STA_ERR)

/** \brief  3504, Extra Path Error Clear Register */
#define CIF_MIEP_STA_ERR_CLR /*lint --e(923)*/ (*(volatile Ifx_CIF_MIEP_STA_ERR_CLR*)0xF90E5404u)

/** Alias (User Manual Name) for CIF_MIEP_STA_ERR_CLR.
* To use register names with standard convension, please use CIF_MIEP_STA_ERR_CLR.
*/
#define	CIFMIEP_STA_ERR_CLR	(CIF_MIEP_STA_ERR_CLR)

/** \brief  2500, Watchdog Control Register */
#define CIF_WD_CTRL /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_CTRL*)0xF90E4400u)

/** Alias (User Manual Name) for CIF_WD_CTRL.
* To use register names with standard convension, please use CIF_WD_CTRL.
*/
#define	CIFWD_CTRL	(CIF_WD_CTRL)

/** \brief  2508, Watchdog Horizontal Timeout Register */
#define CIF_WD_H_TIMEOUT /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_H_TIMEOUT*)0xF90E4408u)

/** Alias (User Manual Name) for CIF_WD_H_TIMEOUT.
* To use register names with standard convension, please use CIF_WD_H_TIMEOUT.
*/
#define	CIFWD_H_TIMEOUT	(CIF_WD_H_TIMEOUT)

/** \brief  2518, Watchdog Interrupt Clear Register */
#define CIF_WD_ICR /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_ICR*)0xF90E4418u)

/** Alias (User Manual Name) for CIF_WD_ICR.
* To use register names with standard convension, please use CIF_WD_ICR.
*/
#define	CIFWD_ICR	(CIF_WD_ICR)

/** \brief  250C, Watchdog Interrupt Mask Register */
#define CIF_WD_IMSC /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_IMSC*)0xF90E440Cu)

/** Alias (User Manual Name) for CIF_WD_IMSC.
* To use register names with standard convension, please use CIF_WD_IMSC.
*/
#define	CIFWD_IMSC	(CIF_WD_IMSC)

/** \brief  251C, Watchdog Interrupt Set Register */
#define CIF_WD_ISR /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_ISR*)0xF90E441Cu)

/** Alias (User Manual Name) for CIF_WD_ISR.
* To use register names with standard convension, please use CIF_WD_ISR.
*/
#define	CIFWD_ISR	(CIF_WD_ISR)

/** \brief  2514, Watchdog Masked Interrupt Status Register */
#define CIF_WD_MIS /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_MIS*)0xF90E4414u)

/** Alias (User Manual Name) for CIF_WD_MIS.
* To use register names with standard convension, please use CIF_WD_MIS.
*/
#define	CIFWD_MIS	(CIF_WD_MIS)

/** \brief  2510, Watchdog Raw Interrupt Status Register */
#define CIF_WD_RIS /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_RIS*)0xF90E4410u)

/** Alias (User Manual Name) for CIF_WD_RIS.
* To use register names with standard convension, please use CIF_WD_RIS.
*/
#define	CIFWD_RIS	(CIF_WD_RIS)

/** \brief  2504, Watchdog Vertical Timeout Register */
#define CIF_WD_V_TIMEOUT /*lint --e(923)*/ (*(volatile Ifx_CIF_WD_V_TIMEOUT*)0xF90E4404u)

/** Alias (User Manual Name) for CIF_WD_V_TIMEOUT.
* To use register names with standard convension, please use CIF_WD_V_TIMEOUT.
*/
#define	CIFWD_V_TIMEOUT	(CIF_WD_V_TIMEOUT)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXCIF_REG_H */
