/**
 * \file IfxCbs_reg.h
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
 * \defgroup IfxLld_Cbs_Cfg Cbs address
 * \ingroup IfxLld_Cbs
 * 
 * \defgroup IfxLld_Cbs_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Cbs_Cfg
 * 
 * \defgroup IfxLld_Cbs_Cfg_Cbs 2-CBS
 * \ingroup IfxLld_Cbs_Cfg
 * 
 */
#ifndef IFXCBS_REG_H
#define IFXCBS_REG_H 1
/******************************************************************************/
#include "IfxCbs_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Cbs_Cfg_BaseAddress
 * \{  */

/** \brief  CBS object */
#define MODULE_CBS /*lint --e(923)*/ (*(Ifx_CBS*)0xF0000400u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cbs_Cfg_Cbs
 * \{  */

/** \brief  68, Communication Mode Data Register */
#define CBS_COMDATA /*lint --e(923)*/ (*(volatile Ifx_CBS_COMDATA*)0xF0000468u)

/** \brief  88, Internally Controlled Trace Source Register */
#define CBS_ICTSA /*lint --e(923)*/ (*(volatile Ifx_CBS_ICTSA*)0xF0000488u)

/** \brief  8C, Internally Controlled Trace Destination Register */
#define CBS_ICTTA /*lint --e(923)*/ (*(volatile Ifx_CBS_ICTTA*)0xF000048Cu)

/** \brief  84, Internal Mode Status and Control Register */
#define CBS_INTMOD /*lint --e(923)*/ (*(volatile Ifx_CBS_INTMOD*)0xF0000484u)

/** \brief  6C, IOClient Status and Control Register */
#define CBS_IOSR /*lint --e(923)*/ (*(volatile Ifx_CBS_IOSR*)0xF000046Cu)

/** \brief  8, Module Identification Register */
#define CBS_JDPID /*lint --e(923)*/ (*(volatile Ifx_CBS_JDPID*)0xF0000408u)

/** \brief  64, JTAG Device Identification Register */
#define CBS_JTAGID /*lint --e(923)*/ (*(volatile Ifx_CBS_JTAGID*)0xF0000464u)

/** \brief  7C, OSCU Control Register */
#define CBS_OCNTRL /*lint --e(923)*/ (*(volatile Ifx_CBS_OCNTRL*)0xF000047Cu)

/** \brief  78, OCDS Enable Control Register */
#define CBS_OEC /*lint --e(923)*/ (*(volatile Ifx_CBS_OEC*)0xF0000478u)

/** \brief  C, OCDS Interface Mode Register */
#define CBS_OIFM /*lint --e(923)*/ (*(volatile Ifx_CBS_OIFM*)0xF000040Cu)

/** \brief  80, OSCU Status Register */
#define CBS_OSTATE /*lint --e(923)*/ (*(volatile Ifx_CBS_OSTATE*)0xF0000480u)

/** \brief  B0, TG Capture for Cores - BRKOUT */
#define CBS_TCCB /*lint --e(923)*/ (*(volatile Ifx_CBS_TCCB*)0xF00004B0u)

/** \brief  B4, TG Capture for Cores - HALT */
#define CBS_TCCH /*lint --e(923)*/ (*(volatile Ifx_CBS_TCCH*)0xF00004B4u)

/** \brief  1C, TG Capture for TG Input Pins */
#define CBS_TCIP /*lint --e(923)*/ (*(volatile Ifx_CBS_TCIP*)0xF000041Cu)

/** \brief  BC, TG Capture for MCDS */
#define CBS_TCM /*lint --e(923)*/ (*(volatile Ifx_CBS_TCM*)0xF00004BCu)

/** \brief  B8, TG Capture for OTGB0/1 */
#define CBS_TCTGB /*lint --e(923)*/ (*(volatile Ifx_CBS_TCTGB*)0xF00004B8u)

/** \brief  74, TG Capture for TG Lines */
#define CBS_TCTL /*lint --e(923)*/ (*(volatile Ifx_CBS_TCTL*)0xF0000474u)

/** \brief  10, TG Input Pins Routing */
#define CBS_TIPR /*lint --e(923)*/ (*(volatile Ifx_CBS_TIPR*)0xF0000410u)

/** \brief  94, TG Line 1 Suspend Targets */
#define CBS_TL1ST /*lint --e(923)*/ (*(volatile Ifx_CBS_TL1ST*)0xF0000494u)

/** \brief  90, TG Line Control */
#define CBS_TLC /*lint --e(923)*/ (*(volatile Ifx_CBS_TLC*)0xF0000490u)

/** \brief  40, TG Line Counter Control */
#define CBS_TLCC0 /*lint --e(923)*/ (*(volatile Ifx_CBS_TLCC*)0xF0000440u)

/** \brief  44, TG Line Counter Control */
#define CBS_TLCC1 /*lint --e(923)*/ (*(volatile Ifx_CBS_TLCC*)0xF0000444u)

/** \brief  98, TG Line Capture and Hold Enable */
#define CBS_TLCHE /*lint --e(923)*/ (*(volatile Ifx_CBS_TLCHE*)0xF0000498u)

/** \brief  9C, TG Line Capture and Hold Clear */
#define CBS_TLCHS /*lint --e(923)*/ (*(volatile Ifx_CBS_TLCHS*)0xF000049Cu)

/** \brief  50, TG Line Counter Value */
#define CBS_TLCV0 /*lint --e(923)*/ (*(volatile Ifx_CBS_TLCV*)0xF0000450u)

/** \brief  54, TG Line Counter Value */
#define CBS_TLCV1 /*lint --e(923)*/ (*(volatile Ifx_CBS_TLCV*)0xF0000454u)

/** \brief  70, TG Line State */
#define CBS_TLS /*lint --e(923)*/ (*(volatile Ifx_CBS_TLS*)0xF0000470u)

/** \brief  A8, TG Line Timer */
#define CBS_TLT /*lint --e(923)*/ (*(volatile Ifx_CBS_TLT*)0xF00004A8u)

/** \brief  AC, TG Lines for Trigger to Host */
#define CBS_TLTTH /*lint --e(923)*/ (*(volatile Ifx_CBS_TLTTH*)0xF00004ACu)

/** \brief  18, TG Output Pins Pulse Stretcher */
#define CBS_TOPPS /*lint --e(923)*/ (*(volatile Ifx_CBS_TOPPS*)0xF0000418u)

/** \brief  14, TG Output Pins Routing */
#define CBS_TOPR /*lint --e(923)*/ (*(volatile Ifx_CBS_TOPR*)0xF0000414u)

/** \brief  20, TG Routing for CPU */
#define CBS_TRC0 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRC*)0xF0000420u)

/** \brief  24, TG Routing for CPU */
#define CBS_TRC1 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRC*)0xF0000424u)

/** \brief  C0, TG Routing Events of CPU */
#define CBS_TREC0 /*lint --e(923)*/ (*(volatile Ifx_CBS_TREC*)0xF00004C0u)

/** \brief  C4, TG Routing Events of CPU */
#define CBS_TREC1 /*lint --e(923)*/ (*(volatile Ifx_CBS_TREC*)0xF00004C4u)

/** \brief  100, Trigger to Host Register */
#define CBS_TRIG0 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000500u)

/** \brief  104, Trigger to Host Register */
#define CBS_TRIG1 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000504u)

/** \brief  128, Trigger to Host Register */
#define CBS_TRIG10 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000528u)

/** \brief  12C, Trigger to Host Register */
#define CBS_TRIG11 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF000052Cu)

/** \brief  130, Trigger to Host Register */
#define CBS_TRIG12 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000530u)

/** \brief  134, Trigger to Host Register */
#define CBS_TRIG13 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000534u)

/** \brief  138, Trigger to Host Register */
#define CBS_TRIG14 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000538u)

/** \brief  13C, Trigger to Host Register */
#define CBS_TRIG15 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF000053Cu)

/** \brief  140, Trigger to Host Register */
#define CBS_TRIG16 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000540u)

/** \brief  144, Trigger to Host Register */
#define CBS_TRIG17 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000544u)

/** \brief  148, Trigger to Host Register */
#define CBS_TRIG18 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000548u)

/** \brief  14C, Trigger to Host Register */
#define CBS_TRIG19 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF000054Cu)

/** \brief  108, Trigger to Host Register */
#define CBS_TRIG2 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000508u)

/** \brief  150, Trigger to Host Register */
#define CBS_TRIG20 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000550u)

/** \brief  154, Trigger to Host Register */
#define CBS_TRIG21 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000554u)

/** \brief  10C, Trigger to Host Register */
#define CBS_TRIG3 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF000050Cu)

/** \brief  110, Trigger to Host Register */
#define CBS_TRIG4 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000510u)

/** \brief  114, Trigger to Host Register */
#define CBS_TRIG5 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000514u)

/** \brief  118, Trigger to Host Register */
#define CBS_TRIG6 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000518u)

/** \brief  11C, Trigger to Host Register */
#define CBS_TRIG7 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF000051Cu)

/** \brief  120, Trigger to Host Register */
#define CBS_TRIG8 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000520u)

/** \brief  124, Trigger to Host Register */
#define CBS_TRIG9 /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIG*)0xF0000524u)

/** \brief  A4, Clear Trigger to Host Register */
#define CBS_TRIGC /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIGC*)0xF00004A4u)

/** \brief  A0, Set Trigger to Host Register */
#define CBS_TRIGS /*lint --e(923)*/ (*(volatile Ifx_CBS_TRIGS*)0xF00004A0u)

/** \brief  3C, TG Routing for MCDS Control */
#define CBS_TRMC /*lint --e(923)*/ (*(volatile Ifx_CBS_TRMC*)0xF000043Cu)

/** \brief  DC, TG Routing for MCDS Triggers */
#define CBS_TRMT /*lint --e(923)*/ (*(volatile Ifx_CBS_TRMT*)0xF00004DCu)

/** \brief  60, TG Routing for Special Signals */
#define CBS_TRSS /*lint --e(923)*/ (*(volatile Ifx_CBS_TRSS*)0xF0000460u)

/** \brief  E4, TG Routing for OTGB Bits [15:8] */
#define CBS_TRTGB0_H /*lint --e(923)*/ (*(volatile Ifx_CBS_TRTGB_H*)0xF00004E4u)

/** Alias (User Manual Name) for CBS_TRTGB0_H.
* To use register names with standard convension, please use CBS_TRTGB0_H.
*/
#define	CBS_TRTGB0H	(CBS_TRTGB0_H)

/** \brief  E0, TG Routing for OTGB Bits [7:0] */
#define CBS_TRTGB0_L /*lint --e(923)*/ (*(volatile Ifx_CBS_TRTGB_L*)0xF00004E0u)

/** Alias (User Manual Name) for CBS_TRTGB0_L.
* To use register names with standard convension, please use CBS_TRTGB0_L.
*/
#define	CBS_TRTGB0L	(CBS_TRTGB0_L)

/** \brief  EC, TG Routing for OTGB Bits [15:8] */
#define CBS_TRTGB1_H /*lint --e(923)*/ (*(volatile Ifx_CBS_TRTGB_H*)0xF00004ECu)

/** Alias (User Manual Name) for CBS_TRTGB1_H.
* To use register names with standard convension, please use CBS_TRTGB1_H.
*/
#define	CBS_TRTGB1H	(CBS_TRTGB1_H)

/** \brief  E8, TG Routing for OTGB Bits [7:0] */
#define CBS_TRTGB1_L /*lint --e(923)*/ (*(volatile Ifx_CBS_TRTGB_L*)0xF00004E8u)

/** Alias (User Manual Name) for CBS_TRTGB1_L.
* To use register names with standard convension, please use CBS_TRTGB1_L.
*/
#define	CBS_TRTGB1L	(CBS_TRTGB1_L)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXCBS_REG_H */
