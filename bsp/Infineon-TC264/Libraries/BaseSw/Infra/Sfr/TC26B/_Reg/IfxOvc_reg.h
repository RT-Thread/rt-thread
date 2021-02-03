/**
 * \file IfxOvc_reg.h
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
 * \defgroup IfxLld_Ovc_Cfg Ovc address
 * \ingroup IfxLld_Ovc
 * 
 * \defgroup IfxLld_Ovc_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Ovc_Cfg
 * 
 * \defgroup IfxLld_Ovc_Cfg_Ovc0 2-OVC0
 * \ingroup IfxLld_Ovc_Cfg
 * 
 * \defgroup IfxLld_Ovc_Cfg_Ovc1 2-OVC1
 * \ingroup IfxLld_Ovc_Cfg
 * 
 */
#ifndef IFXOVC_REG_H
#define IFXOVC_REG_H 1
/******************************************************************************/
#include "IfxOvc_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Ovc_Cfg_BaseAddress
 * \{  */

/** \brief  OVC object */
#define MODULE_OVC0 /*lint --e(923)*/ (*(Ifx_OVC*)0xF880FB00u)

/** \brief  OVC object */
#define MODULE_OVC1 /*lint --e(923)*/ (*(Ifx_OVC*)0xF882FB00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Ovc_Cfg_Ovc0
 * \{  */

/** \brief  18, Overlay Mask Register */
#define OVC0_BLK0_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB18u)

/** Alias (User Manual Name) for OVC0_BLK0_OMASK.
* To use register names with standard convension, please use OVC0_BLK0_OMASK.
*/
#define	OVC0_OMASK0	(OVC0_BLK0_OMASK)

/** \brief  14, Overlay Target Address Register */
#define OVC0_BLK0_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB14u)

/** Alias (User Manual Name) for OVC0_BLK0_OTAR.
* To use register names with standard convension, please use OVC0_BLK0_OTAR.
*/
#define	OVC0_OTAR0	(OVC0_BLK0_OTAR)

/** \brief  10, Redirected Address Base Register */
#define OVC0_BLK0_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB10u)

/** Alias (User Manual Name) for OVC0_BLK0_RABR.
* To use register names with standard convension, please use OVC0_BLK0_RABR.
*/
#define	OVC0_RABR0	(OVC0_BLK0_RABR)

/** \brief  90, Overlay Mask Register */
#define OVC0_BLK10_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB90u)

/** Alias (User Manual Name) for OVC0_BLK10_OMASK.
* To use register names with standard convension, please use OVC0_BLK10_OMASK.
*/
#define	OVC0_OMASK10	(OVC0_BLK10_OMASK)

/** \brief  8C, Overlay Target Address Register */
#define OVC0_BLK10_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB8Cu)

/** Alias (User Manual Name) for OVC0_BLK10_OTAR.
* To use register names with standard convension, please use OVC0_BLK10_OTAR.
*/
#define	OVC0_OTAR10	(OVC0_BLK10_OTAR)

/** \brief  88, Redirected Address Base Register */
#define OVC0_BLK10_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB88u)

/** Alias (User Manual Name) for OVC0_BLK10_RABR.
* To use register names with standard convension, please use OVC0_BLK10_RABR.
*/
#define	OVC0_RABR10	(OVC0_BLK10_RABR)

/** \brief  9C, Overlay Mask Register */
#define OVC0_BLK11_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB9Cu)

/** Alias (User Manual Name) for OVC0_BLK11_OMASK.
* To use register names with standard convension, please use OVC0_BLK11_OMASK.
*/
#define	OVC0_OMASK11	(OVC0_BLK11_OMASK)

/** \brief  98, Overlay Target Address Register */
#define OVC0_BLK11_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB98u)

/** Alias (User Manual Name) for OVC0_BLK11_OTAR.
* To use register names with standard convension, please use OVC0_BLK11_OTAR.
*/
#define	OVC0_OTAR11	(OVC0_BLK11_OTAR)

/** \brief  94, Redirected Address Base Register */
#define OVC0_BLK11_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB94u)

/** Alias (User Manual Name) for OVC0_BLK11_RABR.
* To use register names with standard convension, please use OVC0_BLK11_RABR.
*/
#define	OVC0_RABR11	(OVC0_BLK11_RABR)

/** \brief  A8, Overlay Mask Register */
#define OVC0_BLK12_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBA8u)

/** Alias (User Manual Name) for OVC0_BLK12_OMASK.
* To use register names with standard convension, please use OVC0_BLK12_OMASK.
*/
#define	OVC0_OMASK12	(OVC0_BLK12_OMASK)

/** \brief  A4, Overlay Target Address Register */
#define OVC0_BLK12_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBA4u)

/** Alias (User Manual Name) for OVC0_BLK12_OTAR.
* To use register names with standard convension, please use OVC0_BLK12_OTAR.
*/
#define	OVC0_OTAR12	(OVC0_BLK12_OTAR)

/** \brief  A0, Redirected Address Base Register */
#define OVC0_BLK12_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBA0u)

/** Alias (User Manual Name) for OVC0_BLK12_RABR.
* To use register names with standard convension, please use OVC0_BLK12_RABR.
*/
#define	OVC0_RABR12	(OVC0_BLK12_RABR)

/** \brief  B4, Overlay Mask Register */
#define OVC0_BLK13_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBB4u)

/** Alias (User Manual Name) for OVC0_BLK13_OMASK.
* To use register names with standard convension, please use OVC0_BLK13_OMASK.
*/
#define	OVC0_OMASK13	(OVC0_BLK13_OMASK)

/** \brief  B0, Overlay Target Address Register */
#define OVC0_BLK13_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBB0u)

/** Alias (User Manual Name) for OVC0_BLK13_OTAR.
* To use register names with standard convension, please use OVC0_BLK13_OTAR.
*/
#define	OVC0_OTAR13	(OVC0_BLK13_OTAR)

/** \brief  AC, Redirected Address Base Register */
#define OVC0_BLK13_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBACu)

/** Alias (User Manual Name) for OVC0_BLK13_RABR.
* To use register names with standard convension, please use OVC0_BLK13_RABR.
*/
#define	OVC0_RABR13	(OVC0_BLK13_RABR)

/** \brief  C0, Overlay Mask Register */
#define OVC0_BLK14_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBC0u)

/** Alias (User Manual Name) for OVC0_BLK14_OMASK.
* To use register names with standard convension, please use OVC0_BLK14_OMASK.
*/
#define	OVC0_OMASK14	(OVC0_BLK14_OMASK)

/** \brief  BC, Overlay Target Address Register */
#define OVC0_BLK14_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBBCu)

/** Alias (User Manual Name) for OVC0_BLK14_OTAR.
* To use register names with standard convension, please use OVC0_BLK14_OTAR.
*/
#define	OVC0_OTAR14	(OVC0_BLK14_OTAR)

/** \brief  B8, Redirected Address Base Register */
#define OVC0_BLK14_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBB8u)

/** Alias (User Manual Name) for OVC0_BLK14_RABR.
* To use register names with standard convension, please use OVC0_BLK14_RABR.
*/
#define	OVC0_RABR14	(OVC0_BLK14_RABR)

/** \brief  CC, Overlay Mask Register */
#define OVC0_BLK15_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBCCu)

/** Alias (User Manual Name) for OVC0_BLK15_OMASK.
* To use register names with standard convension, please use OVC0_BLK15_OMASK.
*/
#define	OVC0_OMASK15	(OVC0_BLK15_OMASK)

/** \brief  C8, Overlay Target Address Register */
#define OVC0_BLK15_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBC8u)

/** Alias (User Manual Name) for OVC0_BLK15_OTAR.
* To use register names with standard convension, please use OVC0_BLK15_OTAR.
*/
#define	OVC0_OTAR15	(OVC0_BLK15_OTAR)

/** \brief  C4, Redirected Address Base Register */
#define OVC0_BLK15_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBC4u)

/** Alias (User Manual Name) for OVC0_BLK15_RABR.
* To use register names with standard convension, please use OVC0_BLK15_RABR.
*/
#define	OVC0_RABR15	(OVC0_BLK15_RABR)

/** \brief  D8, Overlay Mask Register */
#define OVC0_BLK16_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBD8u)

/** Alias (User Manual Name) for OVC0_BLK16_OMASK.
* To use register names with standard convension, please use OVC0_BLK16_OMASK.
*/
#define	OVC0_OMASK16	(OVC0_BLK16_OMASK)

/** \brief  D4, Overlay Target Address Register */
#define OVC0_BLK16_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBD4u)

/** Alias (User Manual Name) for OVC0_BLK16_OTAR.
* To use register names with standard convension, please use OVC0_BLK16_OTAR.
*/
#define	OVC0_OTAR16	(OVC0_BLK16_OTAR)

/** \brief  D0, Redirected Address Base Register */
#define OVC0_BLK16_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBD0u)

/** Alias (User Manual Name) for OVC0_BLK16_RABR.
* To use register names with standard convension, please use OVC0_BLK16_RABR.
*/
#define	OVC0_RABR16	(OVC0_BLK16_RABR)

/** \brief  E4, Overlay Mask Register */
#define OVC0_BLK17_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBE4u)

/** Alias (User Manual Name) for OVC0_BLK17_OMASK.
* To use register names with standard convension, please use OVC0_BLK17_OMASK.
*/
#define	OVC0_OMASK17	(OVC0_BLK17_OMASK)

/** \brief  E0, Overlay Target Address Register */
#define OVC0_BLK17_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBE0u)

/** Alias (User Manual Name) for OVC0_BLK17_OTAR.
* To use register names with standard convension, please use OVC0_BLK17_OTAR.
*/
#define	OVC0_OTAR17	(OVC0_BLK17_OTAR)

/** \brief  DC, Redirected Address Base Register */
#define OVC0_BLK17_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBDCu)

/** Alias (User Manual Name) for OVC0_BLK17_RABR.
* To use register names with standard convension, please use OVC0_BLK17_RABR.
*/
#define	OVC0_RABR17	(OVC0_BLK17_RABR)

/** \brief  F0, Overlay Mask Register */
#define OVC0_BLK18_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBF0u)

/** Alias (User Manual Name) for OVC0_BLK18_OMASK.
* To use register names with standard convension, please use OVC0_BLK18_OMASK.
*/
#define	OVC0_OMASK18	(OVC0_BLK18_OMASK)

/** \brief  EC, Overlay Target Address Register */
#define OVC0_BLK18_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBECu)

/** Alias (User Manual Name) for OVC0_BLK18_OTAR.
* To use register names with standard convension, please use OVC0_BLK18_OTAR.
*/
#define	OVC0_OTAR18	(OVC0_BLK18_OTAR)

/** \brief  E8, Redirected Address Base Register */
#define OVC0_BLK18_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBE8u)

/** Alias (User Manual Name) for OVC0_BLK18_RABR.
* To use register names with standard convension, please use OVC0_BLK18_RABR.
*/
#define	OVC0_RABR18	(OVC0_BLK18_RABR)

/** \brief  FC, Overlay Mask Register */
#define OVC0_BLK19_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FBFCu)

/** Alias (User Manual Name) for OVC0_BLK19_OMASK.
* To use register names with standard convension, please use OVC0_BLK19_OMASK.
*/
#define	OVC0_OMASK19	(OVC0_BLK19_OMASK)

/** \brief  F8, Overlay Target Address Register */
#define OVC0_BLK19_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FBF8u)

/** Alias (User Manual Name) for OVC0_BLK19_OTAR.
* To use register names with standard convension, please use OVC0_BLK19_OTAR.
*/
#define	OVC0_OTAR19	(OVC0_BLK19_OTAR)

/** \brief  F4, Redirected Address Base Register */
#define OVC0_BLK19_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FBF4u)

/** Alias (User Manual Name) for OVC0_BLK19_RABR.
* To use register names with standard convension, please use OVC0_BLK19_RABR.
*/
#define	OVC0_RABR19	(OVC0_BLK19_RABR)

/** \brief  24, Overlay Mask Register */
#define OVC0_BLK1_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB24u)

/** Alias (User Manual Name) for OVC0_BLK1_OMASK.
* To use register names with standard convension, please use OVC0_BLK1_OMASK.
*/
#define	OVC0_OMASK1	(OVC0_BLK1_OMASK)

/** \brief  20, Overlay Target Address Register */
#define OVC0_BLK1_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB20u)

/** Alias (User Manual Name) for OVC0_BLK1_OTAR.
* To use register names with standard convension, please use OVC0_BLK1_OTAR.
*/
#define	OVC0_OTAR1	(OVC0_BLK1_OTAR)

/** \brief  1C, Redirected Address Base Register */
#define OVC0_BLK1_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB1Cu)

/** Alias (User Manual Name) for OVC0_BLK1_RABR.
* To use register names with standard convension, please use OVC0_BLK1_RABR.
*/
#define	OVC0_RABR1	(OVC0_BLK1_RABR)

/** \brief  108, Overlay Mask Register */
#define OVC0_BLK20_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC08u)

/** Alias (User Manual Name) for OVC0_BLK20_OMASK.
* To use register names with standard convension, please use OVC0_BLK20_OMASK.
*/
#define	OVC0_OMASK20	(OVC0_BLK20_OMASK)

/** \brief  104, Overlay Target Address Register */
#define OVC0_BLK20_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC04u)

/** Alias (User Manual Name) for OVC0_BLK20_OTAR.
* To use register names with standard convension, please use OVC0_BLK20_OTAR.
*/
#define	OVC0_OTAR20	(OVC0_BLK20_OTAR)

/** \brief  100, Redirected Address Base Register */
#define OVC0_BLK20_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC00u)

/** Alias (User Manual Name) for OVC0_BLK20_RABR.
* To use register names with standard convension, please use OVC0_BLK20_RABR.
*/
#define	OVC0_RABR20	(OVC0_BLK20_RABR)

/** \brief  114, Overlay Mask Register */
#define OVC0_BLK21_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC14u)

/** Alias (User Manual Name) for OVC0_BLK21_OMASK.
* To use register names with standard convension, please use OVC0_BLK21_OMASK.
*/
#define	OVC0_OMASK21	(OVC0_BLK21_OMASK)

/** \brief  110, Overlay Target Address Register */
#define OVC0_BLK21_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC10u)

/** Alias (User Manual Name) for OVC0_BLK21_OTAR.
* To use register names with standard convension, please use OVC0_BLK21_OTAR.
*/
#define	OVC0_OTAR21	(OVC0_BLK21_OTAR)

/** \brief  10C, Redirected Address Base Register */
#define OVC0_BLK21_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC0Cu)

/** Alias (User Manual Name) for OVC0_BLK21_RABR.
* To use register names with standard convension, please use OVC0_BLK21_RABR.
*/
#define	OVC0_RABR21	(OVC0_BLK21_RABR)

/** \brief  120, Overlay Mask Register */
#define OVC0_BLK22_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC20u)

/** Alias (User Manual Name) for OVC0_BLK22_OMASK.
* To use register names with standard convension, please use OVC0_BLK22_OMASK.
*/
#define	OVC0_OMASK22	(OVC0_BLK22_OMASK)

/** \brief  11C, Overlay Target Address Register */
#define OVC0_BLK22_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC1Cu)

/** Alias (User Manual Name) for OVC0_BLK22_OTAR.
* To use register names with standard convension, please use OVC0_BLK22_OTAR.
*/
#define	OVC0_OTAR22	(OVC0_BLK22_OTAR)

/** \brief  118, Redirected Address Base Register */
#define OVC0_BLK22_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC18u)

/** Alias (User Manual Name) for OVC0_BLK22_RABR.
* To use register names with standard convension, please use OVC0_BLK22_RABR.
*/
#define	OVC0_RABR22	(OVC0_BLK22_RABR)

/** \brief  12C, Overlay Mask Register */
#define OVC0_BLK23_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC2Cu)

/** Alias (User Manual Name) for OVC0_BLK23_OMASK.
* To use register names with standard convension, please use OVC0_BLK23_OMASK.
*/
#define	OVC0_OMASK23	(OVC0_BLK23_OMASK)

/** \brief  128, Overlay Target Address Register */
#define OVC0_BLK23_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC28u)

/** Alias (User Manual Name) for OVC0_BLK23_OTAR.
* To use register names with standard convension, please use OVC0_BLK23_OTAR.
*/
#define	OVC0_OTAR23	(OVC0_BLK23_OTAR)

/** \brief  124, Redirected Address Base Register */
#define OVC0_BLK23_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC24u)

/** Alias (User Manual Name) for OVC0_BLK23_RABR.
* To use register names with standard convension, please use OVC0_BLK23_RABR.
*/
#define	OVC0_RABR23	(OVC0_BLK23_RABR)

/** \brief  138, Overlay Mask Register */
#define OVC0_BLK24_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC38u)

/** Alias (User Manual Name) for OVC0_BLK24_OMASK.
* To use register names with standard convension, please use OVC0_BLK24_OMASK.
*/
#define	OVC0_OMASK24	(OVC0_BLK24_OMASK)

/** \brief  134, Overlay Target Address Register */
#define OVC0_BLK24_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC34u)

/** Alias (User Manual Name) for OVC0_BLK24_OTAR.
* To use register names with standard convension, please use OVC0_BLK24_OTAR.
*/
#define	OVC0_OTAR24	(OVC0_BLK24_OTAR)

/** \brief  130, Redirected Address Base Register */
#define OVC0_BLK24_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC30u)

/** Alias (User Manual Name) for OVC0_BLK24_RABR.
* To use register names with standard convension, please use OVC0_BLK24_RABR.
*/
#define	OVC0_RABR24	(OVC0_BLK24_RABR)

/** \brief  144, Overlay Mask Register */
#define OVC0_BLK25_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC44u)

/** Alias (User Manual Name) for OVC0_BLK25_OMASK.
* To use register names with standard convension, please use OVC0_BLK25_OMASK.
*/
#define	OVC0_OMASK25	(OVC0_BLK25_OMASK)

/** \brief  140, Overlay Target Address Register */
#define OVC0_BLK25_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC40u)

/** Alias (User Manual Name) for OVC0_BLK25_OTAR.
* To use register names with standard convension, please use OVC0_BLK25_OTAR.
*/
#define	OVC0_OTAR25	(OVC0_BLK25_OTAR)

/** \brief  13C, Redirected Address Base Register */
#define OVC0_BLK25_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC3Cu)

/** Alias (User Manual Name) for OVC0_BLK25_RABR.
* To use register names with standard convension, please use OVC0_BLK25_RABR.
*/
#define	OVC0_RABR25	(OVC0_BLK25_RABR)

/** \brief  150, Overlay Mask Register */
#define OVC0_BLK26_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC50u)

/** Alias (User Manual Name) for OVC0_BLK26_OMASK.
* To use register names with standard convension, please use OVC0_BLK26_OMASK.
*/
#define	OVC0_OMASK26	(OVC0_BLK26_OMASK)

/** \brief  14C, Overlay Target Address Register */
#define OVC0_BLK26_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC4Cu)

/** Alias (User Manual Name) for OVC0_BLK26_OTAR.
* To use register names with standard convension, please use OVC0_BLK26_OTAR.
*/
#define	OVC0_OTAR26	(OVC0_BLK26_OTAR)

/** \brief  148, Redirected Address Base Register */
#define OVC0_BLK26_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC48u)

/** Alias (User Manual Name) for OVC0_BLK26_RABR.
* To use register names with standard convension, please use OVC0_BLK26_RABR.
*/
#define	OVC0_RABR26	(OVC0_BLK26_RABR)

/** \brief  15C, Overlay Mask Register */
#define OVC0_BLK27_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC5Cu)

/** Alias (User Manual Name) for OVC0_BLK27_OMASK.
* To use register names with standard convension, please use OVC0_BLK27_OMASK.
*/
#define	OVC0_OMASK27	(OVC0_BLK27_OMASK)

/** \brief  158, Overlay Target Address Register */
#define OVC0_BLK27_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC58u)

/** Alias (User Manual Name) for OVC0_BLK27_OTAR.
* To use register names with standard convension, please use OVC0_BLK27_OTAR.
*/
#define	OVC0_OTAR27	(OVC0_BLK27_OTAR)

/** \brief  154, Redirected Address Base Register */
#define OVC0_BLK27_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC54u)

/** Alias (User Manual Name) for OVC0_BLK27_RABR.
* To use register names with standard convension, please use OVC0_BLK27_RABR.
*/
#define	OVC0_RABR27	(OVC0_BLK27_RABR)

/** \brief  168, Overlay Mask Register */
#define OVC0_BLK28_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC68u)

/** Alias (User Manual Name) for OVC0_BLK28_OMASK.
* To use register names with standard convension, please use OVC0_BLK28_OMASK.
*/
#define	OVC0_OMASK28	(OVC0_BLK28_OMASK)

/** \brief  164, Overlay Target Address Register */
#define OVC0_BLK28_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC64u)

/** Alias (User Manual Name) for OVC0_BLK28_OTAR.
* To use register names with standard convension, please use OVC0_BLK28_OTAR.
*/
#define	OVC0_OTAR28	(OVC0_BLK28_OTAR)

/** \brief  160, Redirected Address Base Register */
#define OVC0_BLK28_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC60u)

/** Alias (User Manual Name) for OVC0_BLK28_RABR.
* To use register names with standard convension, please use OVC0_BLK28_RABR.
*/
#define	OVC0_RABR28	(OVC0_BLK28_RABR)

/** \brief  174, Overlay Mask Register */
#define OVC0_BLK29_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC74u)

/** Alias (User Manual Name) for OVC0_BLK29_OMASK.
* To use register names with standard convension, please use OVC0_BLK29_OMASK.
*/
#define	OVC0_OMASK29	(OVC0_BLK29_OMASK)

/** \brief  170, Overlay Target Address Register */
#define OVC0_BLK29_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC70u)

/** Alias (User Manual Name) for OVC0_BLK29_OTAR.
* To use register names with standard convension, please use OVC0_BLK29_OTAR.
*/
#define	OVC0_OTAR29	(OVC0_BLK29_OTAR)

/** \brief  16C, Redirected Address Base Register */
#define OVC0_BLK29_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC6Cu)

/** Alias (User Manual Name) for OVC0_BLK29_RABR.
* To use register names with standard convension, please use OVC0_BLK29_RABR.
*/
#define	OVC0_RABR29	(OVC0_BLK29_RABR)

/** \brief  30, Overlay Mask Register */
#define OVC0_BLK2_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB30u)

/** Alias (User Manual Name) for OVC0_BLK2_OMASK.
* To use register names with standard convension, please use OVC0_BLK2_OMASK.
*/
#define	OVC0_OMASK2	(OVC0_BLK2_OMASK)

/** \brief  2C, Overlay Target Address Register */
#define OVC0_BLK2_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB2Cu)

/** Alias (User Manual Name) for OVC0_BLK2_OTAR.
* To use register names with standard convension, please use OVC0_BLK2_OTAR.
*/
#define	OVC0_OTAR2	(OVC0_BLK2_OTAR)

/** \brief  28, Redirected Address Base Register */
#define OVC0_BLK2_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB28u)

/** Alias (User Manual Name) for OVC0_BLK2_RABR.
* To use register names with standard convension, please use OVC0_BLK2_RABR.
*/
#define	OVC0_RABR2	(OVC0_BLK2_RABR)

/** \brief  180, Overlay Mask Register */
#define OVC0_BLK30_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC80u)

/** Alias (User Manual Name) for OVC0_BLK30_OMASK.
* To use register names with standard convension, please use OVC0_BLK30_OMASK.
*/
#define	OVC0_OMASK30	(OVC0_BLK30_OMASK)

/** \brief  17C, Overlay Target Address Register */
#define OVC0_BLK30_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC7Cu)

/** Alias (User Manual Name) for OVC0_BLK30_OTAR.
* To use register names with standard convension, please use OVC0_BLK30_OTAR.
*/
#define	OVC0_OTAR30	(OVC0_BLK30_OTAR)

/** \brief  178, Redirected Address Base Register */
#define OVC0_BLK30_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC78u)

/** Alias (User Manual Name) for OVC0_BLK30_RABR.
* To use register names with standard convension, please use OVC0_BLK30_RABR.
*/
#define	OVC0_RABR30	(OVC0_BLK30_RABR)

/** \brief  18C, Overlay Mask Register */
#define OVC0_BLK31_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FC8Cu)

/** Alias (User Manual Name) for OVC0_BLK31_OMASK.
* To use register names with standard convension, please use OVC0_BLK31_OMASK.
*/
#define	OVC0_OMASK31	(OVC0_BLK31_OMASK)

/** \brief  188, Overlay Target Address Register */
#define OVC0_BLK31_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FC88u)

/** Alias (User Manual Name) for OVC0_BLK31_OTAR.
* To use register names with standard convension, please use OVC0_BLK31_OTAR.
*/
#define	OVC0_OTAR31	(OVC0_BLK31_OTAR)

/** \brief  184, Redirected Address Base Register */
#define OVC0_BLK31_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FC84u)

/** Alias (User Manual Name) for OVC0_BLK31_RABR.
* To use register names with standard convension, please use OVC0_BLK31_RABR.
*/
#define	OVC0_RABR31	(OVC0_BLK31_RABR)

/** \brief  3C, Overlay Mask Register */
#define OVC0_BLK3_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB3Cu)

/** Alias (User Manual Name) for OVC0_BLK3_OMASK.
* To use register names with standard convension, please use OVC0_BLK3_OMASK.
*/
#define	OVC0_OMASK3	(OVC0_BLK3_OMASK)

/** \brief  38, Overlay Target Address Register */
#define OVC0_BLK3_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB38u)

/** Alias (User Manual Name) for OVC0_BLK3_OTAR.
* To use register names with standard convension, please use OVC0_BLK3_OTAR.
*/
#define	OVC0_OTAR3	(OVC0_BLK3_OTAR)

/** \brief  34, Redirected Address Base Register */
#define OVC0_BLK3_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB34u)

/** Alias (User Manual Name) for OVC0_BLK3_RABR.
* To use register names with standard convension, please use OVC0_BLK3_RABR.
*/
#define	OVC0_RABR3	(OVC0_BLK3_RABR)

/** \brief  48, Overlay Mask Register */
#define OVC0_BLK4_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB48u)

/** Alias (User Manual Name) for OVC0_BLK4_OMASK.
* To use register names with standard convension, please use OVC0_BLK4_OMASK.
*/
#define	OVC0_OMASK4	(OVC0_BLK4_OMASK)

/** \brief  44, Overlay Target Address Register */
#define OVC0_BLK4_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB44u)

/** Alias (User Manual Name) for OVC0_BLK4_OTAR.
* To use register names with standard convension, please use OVC0_BLK4_OTAR.
*/
#define	OVC0_OTAR4	(OVC0_BLK4_OTAR)

/** \brief  40, Redirected Address Base Register */
#define OVC0_BLK4_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB40u)

/** Alias (User Manual Name) for OVC0_BLK4_RABR.
* To use register names with standard convension, please use OVC0_BLK4_RABR.
*/
#define	OVC0_RABR4	(OVC0_BLK4_RABR)

/** \brief  54, Overlay Mask Register */
#define OVC0_BLK5_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB54u)

/** Alias (User Manual Name) for OVC0_BLK5_OMASK.
* To use register names with standard convension, please use OVC0_BLK5_OMASK.
*/
#define	OVC0_OMASK5	(OVC0_BLK5_OMASK)

/** \brief  50, Overlay Target Address Register */
#define OVC0_BLK5_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB50u)

/** Alias (User Manual Name) for OVC0_BLK5_OTAR.
* To use register names with standard convension, please use OVC0_BLK5_OTAR.
*/
#define	OVC0_OTAR5	(OVC0_BLK5_OTAR)

/** \brief  4C, Redirected Address Base Register */
#define OVC0_BLK5_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB4Cu)

/** Alias (User Manual Name) for OVC0_BLK5_RABR.
* To use register names with standard convension, please use OVC0_BLK5_RABR.
*/
#define	OVC0_RABR5	(OVC0_BLK5_RABR)

/** \brief  60, Overlay Mask Register */
#define OVC0_BLK6_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB60u)

/** Alias (User Manual Name) for OVC0_BLK6_OMASK.
* To use register names with standard convension, please use OVC0_BLK6_OMASK.
*/
#define	OVC0_OMASK6	(OVC0_BLK6_OMASK)

/** \brief  5C, Overlay Target Address Register */
#define OVC0_BLK6_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB5Cu)

/** Alias (User Manual Name) for OVC0_BLK6_OTAR.
* To use register names with standard convension, please use OVC0_BLK6_OTAR.
*/
#define	OVC0_OTAR6	(OVC0_BLK6_OTAR)

/** \brief  58, Redirected Address Base Register */
#define OVC0_BLK6_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB58u)

/** Alias (User Manual Name) for OVC0_BLK6_RABR.
* To use register names with standard convension, please use OVC0_BLK6_RABR.
*/
#define	OVC0_RABR6	(OVC0_BLK6_RABR)

/** \brief  6C, Overlay Mask Register */
#define OVC0_BLK7_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB6Cu)

/** Alias (User Manual Name) for OVC0_BLK7_OMASK.
* To use register names with standard convension, please use OVC0_BLK7_OMASK.
*/
#define	OVC0_OMASK7	(OVC0_BLK7_OMASK)

/** \brief  68, Overlay Target Address Register */
#define OVC0_BLK7_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB68u)

/** Alias (User Manual Name) for OVC0_BLK7_OTAR.
* To use register names with standard convension, please use OVC0_BLK7_OTAR.
*/
#define	OVC0_OTAR7	(OVC0_BLK7_OTAR)

/** \brief  64, Redirected Address Base Register */
#define OVC0_BLK7_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB64u)

/** Alias (User Manual Name) for OVC0_BLK7_RABR.
* To use register names with standard convension, please use OVC0_BLK7_RABR.
*/
#define	OVC0_RABR7	(OVC0_BLK7_RABR)

/** \brief  78, Overlay Mask Register */
#define OVC0_BLK8_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB78u)

/** Alias (User Manual Name) for OVC0_BLK8_OMASK.
* To use register names with standard convension, please use OVC0_BLK8_OMASK.
*/
#define	OVC0_OMASK8	(OVC0_BLK8_OMASK)

/** \brief  74, Overlay Target Address Register */
#define OVC0_BLK8_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB74u)

/** Alias (User Manual Name) for OVC0_BLK8_OTAR.
* To use register names with standard convension, please use OVC0_BLK8_OTAR.
*/
#define	OVC0_OTAR8	(OVC0_BLK8_OTAR)

/** \brief  70, Redirected Address Base Register */
#define OVC0_BLK8_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB70u)

/** Alias (User Manual Name) for OVC0_BLK8_RABR.
* To use register names with standard convension, please use OVC0_BLK8_RABR.
*/
#define	OVC0_RABR8	(OVC0_BLK8_RABR)

/** \brief  84, Overlay Mask Register */
#define OVC0_BLK9_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF880FB84u)

/** Alias (User Manual Name) for OVC0_BLK9_OMASK.
* To use register names with standard convension, please use OVC0_BLK9_OMASK.
*/
#define	OVC0_OMASK9	(OVC0_BLK9_OMASK)

/** \brief  80, Overlay Target Address Register */
#define OVC0_BLK9_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF880FB80u)

/** Alias (User Manual Name) for OVC0_BLK9_OTAR.
* To use register names with standard convension, please use OVC0_BLK9_OTAR.
*/
#define	OVC0_OTAR9	(OVC0_BLK9_OTAR)

/** \brief  7C, Redirected Address Base Register */
#define OVC0_BLK9_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF880FB7Cu)

/** Alias (User Manual Name) for OVC0_BLK9_RABR.
* To use register names with standard convension, please use OVC0_BLK9_RABR.
*/
#define	OVC0_RABR9	(OVC0_BLK9_RABR)

/** \brief  0, Overlay Range Select Register */
#define OVC0_OSEL /*lint --e(923)*/ (*(volatile Ifx_OVC_OSEL*)0xF880FB00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Ovc_Cfg_Ovc1
 * \{  */

/** \brief  18, Overlay Mask Register */
#define OVC1_BLK0_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB18u)

/** Alias (User Manual Name) for OVC1_BLK0_OMASK.
* To use register names with standard convension, please use OVC1_BLK0_OMASK.
*/
#define	OVC1_OMASK0	(OVC1_BLK0_OMASK)

/** \brief  14, Overlay Target Address Register */
#define OVC1_BLK0_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB14u)

/** Alias (User Manual Name) for OVC1_BLK0_OTAR.
* To use register names with standard convension, please use OVC1_BLK0_OTAR.
*/
#define	OVC1_OTAR0	(OVC1_BLK0_OTAR)

/** \brief  10, Redirected Address Base Register */
#define OVC1_BLK0_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB10u)

/** Alias (User Manual Name) for OVC1_BLK0_RABR.
* To use register names with standard convension, please use OVC1_BLK0_RABR.
*/
#define	OVC1_RABR0	(OVC1_BLK0_RABR)

/** \brief  90, Overlay Mask Register */
#define OVC1_BLK10_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB90u)

/** Alias (User Manual Name) for OVC1_BLK10_OMASK.
* To use register names with standard convension, please use OVC1_BLK10_OMASK.
*/
#define	OVC1_OMASK10	(OVC1_BLK10_OMASK)

/** \brief  8C, Overlay Target Address Register */
#define OVC1_BLK10_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB8Cu)

/** Alias (User Manual Name) for OVC1_BLK10_OTAR.
* To use register names with standard convension, please use OVC1_BLK10_OTAR.
*/
#define	OVC1_OTAR10	(OVC1_BLK10_OTAR)

/** \brief  88, Redirected Address Base Register */
#define OVC1_BLK10_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB88u)

/** Alias (User Manual Name) for OVC1_BLK10_RABR.
* To use register names with standard convension, please use OVC1_BLK10_RABR.
*/
#define	OVC1_RABR10	(OVC1_BLK10_RABR)

/** \brief  9C, Overlay Mask Register */
#define OVC1_BLK11_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB9Cu)

/** Alias (User Manual Name) for OVC1_BLK11_OMASK.
* To use register names with standard convension, please use OVC1_BLK11_OMASK.
*/
#define	OVC1_OMASK11	(OVC1_BLK11_OMASK)

/** \brief  98, Overlay Target Address Register */
#define OVC1_BLK11_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB98u)

/** Alias (User Manual Name) for OVC1_BLK11_OTAR.
* To use register names with standard convension, please use OVC1_BLK11_OTAR.
*/
#define	OVC1_OTAR11	(OVC1_BLK11_OTAR)

/** \brief  94, Redirected Address Base Register */
#define OVC1_BLK11_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB94u)

/** Alias (User Manual Name) for OVC1_BLK11_RABR.
* To use register names with standard convension, please use OVC1_BLK11_RABR.
*/
#define	OVC1_RABR11	(OVC1_BLK11_RABR)

/** \brief  A8, Overlay Mask Register */
#define OVC1_BLK12_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBA8u)

/** Alias (User Manual Name) for OVC1_BLK12_OMASK.
* To use register names with standard convension, please use OVC1_BLK12_OMASK.
*/
#define	OVC1_OMASK12	(OVC1_BLK12_OMASK)

/** \brief  A4, Overlay Target Address Register */
#define OVC1_BLK12_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBA4u)

/** Alias (User Manual Name) for OVC1_BLK12_OTAR.
* To use register names with standard convension, please use OVC1_BLK12_OTAR.
*/
#define	OVC1_OTAR12	(OVC1_BLK12_OTAR)

/** \brief  A0, Redirected Address Base Register */
#define OVC1_BLK12_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBA0u)

/** Alias (User Manual Name) for OVC1_BLK12_RABR.
* To use register names with standard convension, please use OVC1_BLK12_RABR.
*/
#define	OVC1_RABR12	(OVC1_BLK12_RABR)

/** \brief  B4, Overlay Mask Register */
#define OVC1_BLK13_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBB4u)

/** Alias (User Manual Name) for OVC1_BLK13_OMASK.
* To use register names with standard convension, please use OVC1_BLK13_OMASK.
*/
#define	OVC1_OMASK13	(OVC1_BLK13_OMASK)

/** \brief  B0, Overlay Target Address Register */
#define OVC1_BLK13_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBB0u)

/** Alias (User Manual Name) for OVC1_BLK13_OTAR.
* To use register names with standard convension, please use OVC1_BLK13_OTAR.
*/
#define	OVC1_OTAR13	(OVC1_BLK13_OTAR)

/** \brief  AC, Redirected Address Base Register */
#define OVC1_BLK13_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBACu)

/** Alias (User Manual Name) for OVC1_BLK13_RABR.
* To use register names with standard convension, please use OVC1_BLK13_RABR.
*/
#define	OVC1_RABR13	(OVC1_BLK13_RABR)

/** \brief  C0, Overlay Mask Register */
#define OVC1_BLK14_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBC0u)

/** Alias (User Manual Name) for OVC1_BLK14_OMASK.
* To use register names with standard convension, please use OVC1_BLK14_OMASK.
*/
#define	OVC1_OMASK14	(OVC1_BLK14_OMASK)

/** \brief  BC, Overlay Target Address Register */
#define OVC1_BLK14_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBBCu)

/** Alias (User Manual Name) for OVC1_BLK14_OTAR.
* To use register names with standard convension, please use OVC1_BLK14_OTAR.
*/
#define	OVC1_OTAR14	(OVC1_BLK14_OTAR)

/** \brief  B8, Redirected Address Base Register */
#define OVC1_BLK14_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBB8u)

/** Alias (User Manual Name) for OVC1_BLK14_RABR.
* To use register names with standard convension, please use OVC1_BLK14_RABR.
*/
#define	OVC1_RABR14	(OVC1_BLK14_RABR)

/** \brief  CC, Overlay Mask Register */
#define OVC1_BLK15_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBCCu)

/** Alias (User Manual Name) for OVC1_BLK15_OMASK.
* To use register names with standard convension, please use OVC1_BLK15_OMASK.
*/
#define	OVC1_OMASK15	(OVC1_BLK15_OMASK)

/** \brief  C8, Overlay Target Address Register */
#define OVC1_BLK15_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBC8u)

/** Alias (User Manual Name) for OVC1_BLK15_OTAR.
* To use register names with standard convension, please use OVC1_BLK15_OTAR.
*/
#define	OVC1_OTAR15	(OVC1_BLK15_OTAR)

/** \brief  C4, Redirected Address Base Register */
#define OVC1_BLK15_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBC4u)

/** Alias (User Manual Name) for OVC1_BLK15_RABR.
* To use register names with standard convension, please use OVC1_BLK15_RABR.
*/
#define	OVC1_RABR15	(OVC1_BLK15_RABR)

/** \brief  D8, Overlay Mask Register */
#define OVC1_BLK16_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBD8u)

/** Alias (User Manual Name) for OVC1_BLK16_OMASK.
* To use register names with standard convension, please use OVC1_BLK16_OMASK.
*/
#define	OVC1_OMASK16	(OVC1_BLK16_OMASK)

/** \brief  D4, Overlay Target Address Register */
#define OVC1_BLK16_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBD4u)

/** Alias (User Manual Name) for OVC1_BLK16_OTAR.
* To use register names with standard convension, please use OVC1_BLK16_OTAR.
*/
#define	OVC1_OTAR16	(OVC1_BLK16_OTAR)

/** \brief  D0, Redirected Address Base Register */
#define OVC1_BLK16_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBD0u)

/** Alias (User Manual Name) for OVC1_BLK16_RABR.
* To use register names with standard convension, please use OVC1_BLK16_RABR.
*/
#define	OVC1_RABR16	(OVC1_BLK16_RABR)

/** \brief  E4, Overlay Mask Register */
#define OVC1_BLK17_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBE4u)

/** Alias (User Manual Name) for OVC1_BLK17_OMASK.
* To use register names with standard convension, please use OVC1_BLK17_OMASK.
*/
#define	OVC1_OMASK17	(OVC1_BLK17_OMASK)

/** \brief  E0, Overlay Target Address Register */
#define OVC1_BLK17_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBE0u)

/** Alias (User Manual Name) for OVC1_BLK17_OTAR.
* To use register names with standard convension, please use OVC1_BLK17_OTAR.
*/
#define	OVC1_OTAR17	(OVC1_BLK17_OTAR)

/** \brief  DC, Redirected Address Base Register */
#define OVC1_BLK17_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBDCu)

/** Alias (User Manual Name) for OVC1_BLK17_RABR.
* To use register names with standard convension, please use OVC1_BLK17_RABR.
*/
#define	OVC1_RABR17	(OVC1_BLK17_RABR)

/** \brief  F0, Overlay Mask Register */
#define OVC1_BLK18_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBF0u)

/** Alias (User Manual Name) for OVC1_BLK18_OMASK.
* To use register names with standard convension, please use OVC1_BLK18_OMASK.
*/
#define	OVC1_OMASK18	(OVC1_BLK18_OMASK)

/** \brief  EC, Overlay Target Address Register */
#define OVC1_BLK18_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBECu)

/** Alias (User Manual Name) for OVC1_BLK18_OTAR.
* To use register names with standard convension, please use OVC1_BLK18_OTAR.
*/
#define	OVC1_OTAR18	(OVC1_BLK18_OTAR)

/** \brief  E8, Redirected Address Base Register */
#define OVC1_BLK18_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBE8u)

/** Alias (User Manual Name) for OVC1_BLK18_RABR.
* To use register names with standard convension, please use OVC1_BLK18_RABR.
*/
#define	OVC1_RABR18	(OVC1_BLK18_RABR)

/** \brief  FC, Overlay Mask Register */
#define OVC1_BLK19_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FBFCu)

/** Alias (User Manual Name) for OVC1_BLK19_OMASK.
* To use register names with standard convension, please use OVC1_BLK19_OMASK.
*/
#define	OVC1_OMASK19	(OVC1_BLK19_OMASK)

/** \brief  F8, Overlay Target Address Register */
#define OVC1_BLK19_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FBF8u)

/** Alias (User Manual Name) for OVC1_BLK19_OTAR.
* To use register names with standard convension, please use OVC1_BLK19_OTAR.
*/
#define	OVC1_OTAR19	(OVC1_BLK19_OTAR)

/** \brief  F4, Redirected Address Base Register */
#define OVC1_BLK19_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FBF4u)

/** Alias (User Manual Name) for OVC1_BLK19_RABR.
* To use register names with standard convension, please use OVC1_BLK19_RABR.
*/
#define	OVC1_RABR19	(OVC1_BLK19_RABR)

/** \brief  24, Overlay Mask Register */
#define OVC1_BLK1_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB24u)

/** Alias (User Manual Name) for OVC1_BLK1_OMASK.
* To use register names with standard convension, please use OVC1_BLK1_OMASK.
*/
#define	OVC1_OMASK1	(OVC1_BLK1_OMASK)

/** \brief  20, Overlay Target Address Register */
#define OVC1_BLK1_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB20u)

/** Alias (User Manual Name) for OVC1_BLK1_OTAR.
* To use register names with standard convension, please use OVC1_BLK1_OTAR.
*/
#define	OVC1_OTAR1	(OVC1_BLK1_OTAR)

/** \brief  1C, Redirected Address Base Register */
#define OVC1_BLK1_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB1Cu)

/** Alias (User Manual Name) for OVC1_BLK1_RABR.
* To use register names with standard convension, please use OVC1_BLK1_RABR.
*/
#define	OVC1_RABR1	(OVC1_BLK1_RABR)

/** \brief  108, Overlay Mask Register */
#define OVC1_BLK20_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC08u)

/** Alias (User Manual Name) for OVC1_BLK20_OMASK.
* To use register names with standard convension, please use OVC1_BLK20_OMASK.
*/
#define	OVC1_OMASK20	(OVC1_BLK20_OMASK)

/** \brief  104, Overlay Target Address Register */
#define OVC1_BLK20_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC04u)

/** Alias (User Manual Name) for OVC1_BLK20_OTAR.
* To use register names with standard convension, please use OVC1_BLK20_OTAR.
*/
#define	OVC1_OTAR20	(OVC1_BLK20_OTAR)

/** \brief  100, Redirected Address Base Register */
#define OVC1_BLK20_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC00u)

/** Alias (User Manual Name) for OVC1_BLK20_RABR.
* To use register names with standard convension, please use OVC1_BLK20_RABR.
*/
#define	OVC1_RABR20	(OVC1_BLK20_RABR)

/** \brief  114, Overlay Mask Register */
#define OVC1_BLK21_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC14u)

/** Alias (User Manual Name) for OVC1_BLK21_OMASK.
* To use register names with standard convension, please use OVC1_BLK21_OMASK.
*/
#define	OVC1_OMASK21	(OVC1_BLK21_OMASK)

/** \brief  110, Overlay Target Address Register */
#define OVC1_BLK21_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC10u)

/** Alias (User Manual Name) for OVC1_BLK21_OTAR.
* To use register names with standard convension, please use OVC1_BLK21_OTAR.
*/
#define	OVC1_OTAR21	(OVC1_BLK21_OTAR)

/** \brief  10C, Redirected Address Base Register */
#define OVC1_BLK21_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC0Cu)

/** Alias (User Manual Name) for OVC1_BLK21_RABR.
* To use register names with standard convension, please use OVC1_BLK21_RABR.
*/
#define	OVC1_RABR21	(OVC1_BLK21_RABR)

/** \brief  120, Overlay Mask Register */
#define OVC1_BLK22_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC20u)

/** Alias (User Manual Name) for OVC1_BLK22_OMASK.
* To use register names with standard convension, please use OVC1_BLK22_OMASK.
*/
#define	OVC1_OMASK22	(OVC1_BLK22_OMASK)

/** \brief  11C, Overlay Target Address Register */
#define OVC1_BLK22_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC1Cu)

/** Alias (User Manual Name) for OVC1_BLK22_OTAR.
* To use register names with standard convension, please use OVC1_BLK22_OTAR.
*/
#define	OVC1_OTAR22	(OVC1_BLK22_OTAR)

/** \brief  118, Redirected Address Base Register */
#define OVC1_BLK22_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC18u)

/** Alias (User Manual Name) for OVC1_BLK22_RABR.
* To use register names with standard convension, please use OVC1_BLK22_RABR.
*/
#define	OVC1_RABR22	(OVC1_BLK22_RABR)

/** \brief  12C, Overlay Mask Register */
#define OVC1_BLK23_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC2Cu)

/** Alias (User Manual Name) for OVC1_BLK23_OMASK.
* To use register names with standard convension, please use OVC1_BLK23_OMASK.
*/
#define	OVC1_OMASK23	(OVC1_BLK23_OMASK)

/** \brief  128, Overlay Target Address Register */
#define OVC1_BLK23_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC28u)

/** Alias (User Manual Name) for OVC1_BLK23_OTAR.
* To use register names with standard convension, please use OVC1_BLK23_OTAR.
*/
#define	OVC1_OTAR23	(OVC1_BLK23_OTAR)

/** \brief  124, Redirected Address Base Register */
#define OVC1_BLK23_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC24u)

/** Alias (User Manual Name) for OVC1_BLK23_RABR.
* To use register names with standard convension, please use OVC1_BLK23_RABR.
*/
#define	OVC1_RABR23	(OVC1_BLK23_RABR)

/** \brief  138, Overlay Mask Register */
#define OVC1_BLK24_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC38u)

/** Alias (User Manual Name) for OVC1_BLK24_OMASK.
* To use register names with standard convension, please use OVC1_BLK24_OMASK.
*/
#define	OVC1_OMASK24	(OVC1_BLK24_OMASK)

/** \brief  134, Overlay Target Address Register */
#define OVC1_BLK24_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC34u)

/** Alias (User Manual Name) for OVC1_BLK24_OTAR.
* To use register names with standard convension, please use OVC1_BLK24_OTAR.
*/
#define	OVC1_OTAR24	(OVC1_BLK24_OTAR)

/** \brief  130, Redirected Address Base Register */
#define OVC1_BLK24_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC30u)

/** Alias (User Manual Name) for OVC1_BLK24_RABR.
* To use register names with standard convension, please use OVC1_BLK24_RABR.
*/
#define	OVC1_RABR24	(OVC1_BLK24_RABR)

/** \brief  144, Overlay Mask Register */
#define OVC1_BLK25_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC44u)

/** Alias (User Manual Name) for OVC1_BLK25_OMASK.
* To use register names with standard convension, please use OVC1_BLK25_OMASK.
*/
#define	OVC1_OMASK25	(OVC1_BLK25_OMASK)

/** \brief  140, Overlay Target Address Register */
#define OVC1_BLK25_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC40u)

/** Alias (User Manual Name) for OVC1_BLK25_OTAR.
* To use register names with standard convension, please use OVC1_BLK25_OTAR.
*/
#define	OVC1_OTAR25	(OVC1_BLK25_OTAR)

/** \brief  13C, Redirected Address Base Register */
#define OVC1_BLK25_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC3Cu)

/** Alias (User Manual Name) for OVC1_BLK25_RABR.
* To use register names with standard convension, please use OVC1_BLK25_RABR.
*/
#define	OVC1_RABR25	(OVC1_BLK25_RABR)

/** \brief  150, Overlay Mask Register */
#define OVC1_BLK26_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC50u)

/** Alias (User Manual Name) for OVC1_BLK26_OMASK.
* To use register names with standard convension, please use OVC1_BLK26_OMASK.
*/
#define	OVC1_OMASK26	(OVC1_BLK26_OMASK)

/** \brief  14C, Overlay Target Address Register */
#define OVC1_BLK26_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC4Cu)

/** Alias (User Manual Name) for OVC1_BLK26_OTAR.
* To use register names with standard convension, please use OVC1_BLK26_OTAR.
*/
#define	OVC1_OTAR26	(OVC1_BLK26_OTAR)

/** \brief  148, Redirected Address Base Register */
#define OVC1_BLK26_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC48u)

/** Alias (User Manual Name) for OVC1_BLK26_RABR.
* To use register names with standard convension, please use OVC1_BLK26_RABR.
*/
#define	OVC1_RABR26	(OVC1_BLK26_RABR)

/** \brief  15C, Overlay Mask Register */
#define OVC1_BLK27_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC5Cu)

/** Alias (User Manual Name) for OVC1_BLK27_OMASK.
* To use register names with standard convension, please use OVC1_BLK27_OMASK.
*/
#define	OVC1_OMASK27	(OVC1_BLK27_OMASK)

/** \brief  158, Overlay Target Address Register */
#define OVC1_BLK27_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC58u)

/** Alias (User Manual Name) for OVC1_BLK27_OTAR.
* To use register names with standard convension, please use OVC1_BLK27_OTAR.
*/
#define	OVC1_OTAR27	(OVC1_BLK27_OTAR)

/** \brief  154, Redirected Address Base Register */
#define OVC1_BLK27_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC54u)

/** Alias (User Manual Name) for OVC1_BLK27_RABR.
* To use register names with standard convension, please use OVC1_BLK27_RABR.
*/
#define	OVC1_RABR27	(OVC1_BLK27_RABR)

/** \brief  168, Overlay Mask Register */
#define OVC1_BLK28_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC68u)

/** Alias (User Manual Name) for OVC1_BLK28_OMASK.
* To use register names with standard convension, please use OVC1_BLK28_OMASK.
*/
#define	OVC1_OMASK28	(OVC1_BLK28_OMASK)

/** \brief  164, Overlay Target Address Register */
#define OVC1_BLK28_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC64u)

/** Alias (User Manual Name) for OVC1_BLK28_OTAR.
* To use register names with standard convension, please use OVC1_BLK28_OTAR.
*/
#define	OVC1_OTAR28	(OVC1_BLK28_OTAR)

/** \brief  160, Redirected Address Base Register */
#define OVC1_BLK28_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC60u)

/** Alias (User Manual Name) for OVC1_BLK28_RABR.
* To use register names with standard convension, please use OVC1_BLK28_RABR.
*/
#define	OVC1_RABR28	(OVC1_BLK28_RABR)

/** \brief  174, Overlay Mask Register */
#define OVC1_BLK29_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC74u)

/** Alias (User Manual Name) for OVC1_BLK29_OMASK.
* To use register names with standard convension, please use OVC1_BLK29_OMASK.
*/
#define	OVC1_OMASK29	(OVC1_BLK29_OMASK)

/** \brief  170, Overlay Target Address Register */
#define OVC1_BLK29_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC70u)

/** Alias (User Manual Name) for OVC1_BLK29_OTAR.
* To use register names with standard convension, please use OVC1_BLK29_OTAR.
*/
#define	OVC1_OTAR29	(OVC1_BLK29_OTAR)

/** \brief  16C, Redirected Address Base Register */
#define OVC1_BLK29_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC6Cu)

/** Alias (User Manual Name) for OVC1_BLK29_RABR.
* To use register names with standard convension, please use OVC1_BLK29_RABR.
*/
#define	OVC1_RABR29	(OVC1_BLK29_RABR)

/** \brief  30, Overlay Mask Register */
#define OVC1_BLK2_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB30u)

/** Alias (User Manual Name) for OVC1_BLK2_OMASK.
* To use register names with standard convension, please use OVC1_BLK2_OMASK.
*/
#define	OVC1_OMASK2	(OVC1_BLK2_OMASK)

/** \brief  2C, Overlay Target Address Register */
#define OVC1_BLK2_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB2Cu)

/** Alias (User Manual Name) for OVC1_BLK2_OTAR.
* To use register names with standard convension, please use OVC1_BLK2_OTAR.
*/
#define	OVC1_OTAR2	(OVC1_BLK2_OTAR)

/** \brief  28, Redirected Address Base Register */
#define OVC1_BLK2_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB28u)

/** Alias (User Manual Name) for OVC1_BLK2_RABR.
* To use register names with standard convension, please use OVC1_BLK2_RABR.
*/
#define	OVC1_RABR2	(OVC1_BLK2_RABR)

/** \brief  180, Overlay Mask Register */
#define OVC1_BLK30_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC80u)

/** Alias (User Manual Name) for OVC1_BLK30_OMASK.
* To use register names with standard convension, please use OVC1_BLK30_OMASK.
*/
#define	OVC1_OMASK30	(OVC1_BLK30_OMASK)

/** \brief  17C, Overlay Target Address Register */
#define OVC1_BLK30_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC7Cu)

/** Alias (User Manual Name) for OVC1_BLK30_OTAR.
* To use register names with standard convension, please use OVC1_BLK30_OTAR.
*/
#define	OVC1_OTAR30	(OVC1_BLK30_OTAR)

/** \brief  178, Redirected Address Base Register */
#define OVC1_BLK30_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC78u)

/** Alias (User Manual Name) for OVC1_BLK30_RABR.
* To use register names with standard convension, please use OVC1_BLK30_RABR.
*/
#define	OVC1_RABR30	(OVC1_BLK30_RABR)

/** \brief  18C, Overlay Mask Register */
#define OVC1_BLK31_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FC8Cu)

/** Alias (User Manual Name) for OVC1_BLK31_OMASK.
* To use register names with standard convension, please use OVC1_BLK31_OMASK.
*/
#define	OVC1_OMASK31	(OVC1_BLK31_OMASK)

/** \brief  188, Overlay Target Address Register */
#define OVC1_BLK31_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FC88u)

/** Alias (User Manual Name) for OVC1_BLK31_OTAR.
* To use register names with standard convension, please use OVC1_BLK31_OTAR.
*/
#define	OVC1_OTAR31	(OVC1_BLK31_OTAR)

/** \brief  184, Redirected Address Base Register */
#define OVC1_BLK31_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FC84u)

/** Alias (User Manual Name) for OVC1_BLK31_RABR.
* To use register names with standard convension, please use OVC1_BLK31_RABR.
*/
#define	OVC1_RABR31	(OVC1_BLK31_RABR)

/** \brief  3C, Overlay Mask Register */
#define OVC1_BLK3_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB3Cu)

/** Alias (User Manual Name) for OVC1_BLK3_OMASK.
* To use register names with standard convension, please use OVC1_BLK3_OMASK.
*/
#define	OVC1_OMASK3	(OVC1_BLK3_OMASK)

/** \brief  38, Overlay Target Address Register */
#define OVC1_BLK3_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB38u)

/** Alias (User Manual Name) for OVC1_BLK3_OTAR.
* To use register names with standard convension, please use OVC1_BLK3_OTAR.
*/
#define	OVC1_OTAR3	(OVC1_BLK3_OTAR)

/** \brief  34, Redirected Address Base Register */
#define OVC1_BLK3_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB34u)

/** Alias (User Manual Name) for OVC1_BLK3_RABR.
* To use register names with standard convension, please use OVC1_BLK3_RABR.
*/
#define	OVC1_RABR3	(OVC1_BLK3_RABR)

/** \brief  48, Overlay Mask Register */
#define OVC1_BLK4_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB48u)

/** Alias (User Manual Name) for OVC1_BLK4_OMASK.
* To use register names with standard convension, please use OVC1_BLK4_OMASK.
*/
#define	OVC1_OMASK4	(OVC1_BLK4_OMASK)

/** \brief  44, Overlay Target Address Register */
#define OVC1_BLK4_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB44u)

/** Alias (User Manual Name) for OVC1_BLK4_OTAR.
* To use register names with standard convension, please use OVC1_BLK4_OTAR.
*/
#define	OVC1_OTAR4	(OVC1_BLK4_OTAR)

/** \brief  40, Redirected Address Base Register */
#define OVC1_BLK4_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB40u)

/** Alias (User Manual Name) for OVC1_BLK4_RABR.
* To use register names with standard convension, please use OVC1_BLK4_RABR.
*/
#define	OVC1_RABR4	(OVC1_BLK4_RABR)

/** \brief  54, Overlay Mask Register */
#define OVC1_BLK5_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB54u)

/** Alias (User Manual Name) for OVC1_BLK5_OMASK.
* To use register names with standard convension, please use OVC1_BLK5_OMASK.
*/
#define	OVC1_OMASK5	(OVC1_BLK5_OMASK)

/** \brief  50, Overlay Target Address Register */
#define OVC1_BLK5_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB50u)

/** Alias (User Manual Name) for OVC1_BLK5_OTAR.
* To use register names with standard convension, please use OVC1_BLK5_OTAR.
*/
#define	OVC1_OTAR5	(OVC1_BLK5_OTAR)

/** \brief  4C, Redirected Address Base Register */
#define OVC1_BLK5_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB4Cu)

/** Alias (User Manual Name) for OVC1_BLK5_RABR.
* To use register names with standard convension, please use OVC1_BLK5_RABR.
*/
#define	OVC1_RABR5	(OVC1_BLK5_RABR)

/** \brief  60, Overlay Mask Register */
#define OVC1_BLK6_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB60u)

/** Alias (User Manual Name) for OVC1_BLK6_OMASK.
* To use register names with standard convension, please use OVC1_BLK6_OMASK.
*/
#define	OVC1_OMASK6	(OVC1_BLK6_OMASK)

/** \brief  5C, Overlay Target Address Register */
#define OVC1_BLK6_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB5Cu)

/** Alias (User Manual Name) for OVC1_BLK6_OTAR.
* To use register names with standard convension, please use OVC1_BLK6_OTAR.
*/
#define	OVC1_OTAR6	(OVC1_BLK6_OTAR)

/** \brief  58, Redirected Address Base Register */
#define OVC1_BLK6_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB58u)

/** Alias (User Manual Name) for OVC1_BLK6_RABR.
* To use register names with standard convension, please use OVC1_BLK6_RABR.
*/
#define	OVC1_RABR6	(OVC1_BLK6_RABR)

/** \brief  6C, Overlay Mask Register */
#define OVC1_BLK7_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB6Cu)

/** Alias (User Manual Name) for OVC1_BLK7_OMASK.
* To use register names with standard convension, please use OVC1_BLK7_OMASK.
*/
#define	OVC1_OMASK7	(OVC1_BLK7_OMASK)

/** \brief  68, Overlay Target Address Register */
#define OVC1_BLK7_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB68u)

/** Alias (User Manual Name) for OVC1_BLK7_OTAR.
* To use register names with standard convension, please use OVC1_BLK7_OTAR.
*/
#define	OVC1_OTAR7	(OVC1_BLK7_OTAR)

/** \brief  64, Redirected Address Base Register */
#define OVC1_BLK7_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB64u)

/** Alias (User Manual Name) for OVC1_BLK7_RABR.
* To use register names with standard convension, please use OVC1_BLK7_RABR.
*/
#define	OVC1_RABR7	(OVC1_BLK7_RABR)

/** \brief  78, Overlay Mask Register */
#define OVC1_BLK8_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB78u)

/** Alias (User Manual Name) for OVC1_BLK8_OMASK.
* To use register names with standard convension, please use OVC1_BLK8_OMASK.
*/
#define	OVC1_OMASK8	(OVC1_BLK8_OMASK)

/** \brief  74, Overlay Target Address Register */
#define OVC1_BLK8_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB74u)

/** Alias (User Manual Name) for OVC1_BLK8_OTAR.
* To use register names with standard convension, please use OVC1_BLK8_OTAR.
*/
#define	OVC1_OTAR8	(OVC1_BLK8_OTAR)

/** \brief  70, Redirected Address Base Register */
#define OVC1_BLK8_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB70u)

/** Alias (User Manual Name) for OVC1_BLK8_RABR.
* To use register names with standard convension, please use OVC1_BLK8_RABR.
*/
#define	OVC1_RABR8	(OVC1_BLK8_RABR)

/** \brief  84, Overlay Mask Register */
#define OVC1_BLK9_OMASK /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OMASK*)0xF882FB84u)

/** Alias (User Manual Name) for OVC1_BLK9_OMASK.
* To use register names with standard convension, please use OVC1_BLK9_OMASK.
*/
#define	OVC1_OMASK9	(OVC1_BLK9_OMASK)

/** \brief  80, Overlay Target Address Register */
#define OVC1_BLK9_OTAR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_OTAR*)0xF882FB80u)

/** Alias (User Manual Name) for OVC1_BLK9_OTAR.
* To use register names with standard convension, please use OVC1_BLK9_OTAR.
*/
#define	OVC1_OTAR9	(OVC1_BLK9_OTAR)

/** \brief  7C, Redirected Address Base Register */
#define OVC1_BLK9_RABR /*lint --e(923)*/ (*(volatile Ifx_OVC_BLK_RABR*)0xF882FB7Cu)

/** Alias (User Manual Name) for OVC1_BLK9_RABR.
* To use register names with standard convension, please use OVC1_BLK9_RABR.
*/
#define	OVC1_RABR9	(OVC1_BLK9_RABR)

/** \brief  0, Overlay Range Select Register */
#define OVC1_OSEL /*lint --e(923)*/ (*(volatile Ifx_OVC_OSEL*)0xF882FB00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXOVC_REG_H */
