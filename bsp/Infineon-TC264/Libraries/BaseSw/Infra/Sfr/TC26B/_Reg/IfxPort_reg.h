/**
 * \file IfxPort_reg.h
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
 * \defgroup IfxLld_Port_Cfg Port address
 * \ingroup IfxLld_Port
 * 
 * \defgroup IfxLld_Port_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P00 2-P00
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P02 2-P02
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P10 2-P10
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P11 2-P11
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P13 2-P13
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P14 2-P14
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P15 2-P15
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P20 2-P20
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P21 2-P21
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P22 2-P22
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P23 2-P23
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P32 2-P32
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P33 2-P33
 * \ingroup IfxLld_Port_Cfg
 * 
 * \defgroup IfxLld_Port_Cfg_P40 2-P40
 * \ingroup IfxLld_Port_Cfg
 * 
 */
#ifndef IFXPORT_REG_H
#define IFXPORT_REG_H 1
/******************************************************************************/
#include "IfxPort_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_BaseAddress
 * \{  */

/** \brief  Port object */
#define MODULE_P00 /*lint --e(923)*/ (*(Ifx_P*)0xF003A000u)

/** \brief  Port object */
#define MODULE_P02 /*lint --e(923)*/ (*(Ifx_P*)0xF003A200u)

/** \brief  Port object */
#define MODULE_P10 /*lint --e(923)*/ (*(Ifx_P*)0xF003B000u)

/** \brief  Port object */
#define MODULE_P11 /*lint --e(923)*/ (*(Ifx_P*)0xF003B100u)

/** \brief  Port object */
#define MODULE_P13 /*lint --e(923)*/ (*(Ifx_P*)0xF003B300u)

/** \brief  Port object */
#define MODULE_P14 /*lint --e(923)*/ (*(Ifx_P*)0xF003B400u)

/** \brief  Port object */
#define MODULE_P15 /*lint --e(923)*/ (*(Ifx_P*)0xF003B500u)

/** \brief  Port object */
#define MODULE_P20 /*lint --e(923)*/ (*(Ifx_P*)0xF003C000u)

/** \brief  Port object */
#define MODULE_P21 /*lint --e(923)*/ (*(Ifx_P*)0xF003C100u)

/** \brief  Port object */
#define MODULE_P22 /*lint --e(923)*/ (*(Ifx_P*)0xF003C200u)

/** \brief  Port object */
#define MODULE_P23 /*lint --e(923)*/ (*(Ifx_P*)0xF003C300u)

/** \brief  Port object */
#define MODULE_P32 /*lint --e(923)*/ (*(Ifx_P*)0xF003D200u)

/** \brief  Port object */
#define MODULE_P33 /*lint --e(923)*/ (*(Ifx_P*)0xF003D300u)

/** \brief  Port object */
#define MODULE_P40 /*lint --e(923)*/ (*(Ifx_P*)0xF003E000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P00
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P00_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003A0FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P00_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003A0F8u)

/** \brief  50, Port Emergency Stop Register */
#define P00_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003A050u)

/** \brief  8, Identification Register */
#define P00_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003A008u)

/** \brief  24, Port Input Register */
#define P00_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003A024u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P00_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003A010u)

/** \brief  1C, Port Input/Output Control Register 12 */
#define P00_IOCR12 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR12*)0xF003A01Cu)

/** \brief  14, Port Input/Output Control Register 4 */
#define P00_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003A014u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P00_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003A018u)

/** \brief  94, Port Output Modification Clear Register */
#define P00_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003A094u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P00_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003A080u)

/** \brief  8C, Port Output Modification Clear Register 12 */
#define P00_OMCR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR12*)0xF003A08Cu)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P00_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003A084u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P00_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003A088u)

/** \brief  4, Port Output Modification Register */
#define P00_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003A004u)

/** \brief  90, Port Output Modification Set Register */
#define P00_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003A090u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P00_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003A070u)

/** \brief  7C, Port Output Modification Set Register 12 */
#define P00_OMSR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR12*)0xF003A07Cu)

/** \brief  74, Port Output Modification Set Register 4 */
#define P00_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003A074u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P00_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003A078u)

/** \brief  0, Port Output Register */
#define P00_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003A000u)

/** \brief  64, Port Pin Controller Select Register */
#define P00_PCSR /*lint --e(923)*/ (*(volatile Ifx_P_PCSR*)0xF003A064u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P00_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003A040u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P00_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003A044u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P02
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P02_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003A2FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P02_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003A2F8u)

/** \brief  50, Port Emergency Stop Register */
#define P02_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003A250u)

/** \brief  8, Identification Register */
#define P02_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003A208u)

/** \brief  24, Port Input Register */
#define P02_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003A224u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P02_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003A210u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P02_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003A214u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P02_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003A218u)

/** \brief  94, Port Output Modification Clear Register */
#define P02_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003A294u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P02_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003A280u)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P02_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003A284u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P02_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003A288u)

/** \brief  4, Port Output Modification Register */
#define P02_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003A204u)

/** \brief  90, Port Output Modification Set Register */
#define P02_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003A290u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P02_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003A270u)

/** \brief  74, Port Output Modification Set Register 4 */
#define P02_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003A274u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P02_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003A278u)

/** \brief  0, Port Output Register */
#define P02_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003A200u)

/** \brief  64, Port Pin Controller Select Register */
#define P02_PCSR /*lint --e(923)*/ (*(volatile Ifx_P_PCSR*)0xF003A264u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P02_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003A240u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P02_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003A244u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P10
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P10_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003B0FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P10_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003B0F8u)

/** \brief  50, Port Emergency Stop Register */
#define P10_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003B050u)

/** \brief  8, Identification Register */
#define P10_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003B008u)

/** \brief  24, Port Input Register */
#define P10_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003B024u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P10_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003B010u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P10_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003B014u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P10_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003B018u)

/** \brief  94, Port Output Modification Clear Register */
#define P10_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003B094u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P10_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003B080u)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P10_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003B084u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P10_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003B088u)

/** \brief  4, Port Output Modification Register */
#define P10_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003B004u)

/** \brief  90, Port Output Modification Set Register */
#define P10_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003B090u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P10_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003B070u)

/** \brief  74, Port Output Modification Set Register 4 */
#define P10_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003B074u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P10_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003B078u)

/** \brief  0, Port Output Register */
#define P10_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003B000u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P10_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003B040u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P10_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003B044u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P11
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P11_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003B1FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P11_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003B1F8u)

/** \brief  50, Port Emergency Stop Register */
#define P11_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003B150u)

/** \brief  8, Identification Register */
#define P11_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003B108u)

/** \brief  24, Port Input Register */
#define P11_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003B124u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P11_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003B110u)

/** \brief  1C, Port Input/Output Control Register 12 */
#define P11_IOCR12 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR12*)0xF003B11Cu)

/** \brief  14, Port Input/Output Control Register 4 */
#define P11_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003B114u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P11_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003B118u)

/** \brief  94, Port Output Modification Clear Register */
#define P11_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003B194u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P11_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003B180u)

/** \brief  8C, Port Output Modification Clear Register 12 */
#define P11_OMCR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR12*)0xF003B18Cu)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P11_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003B184u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P11_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003B188u)

/** \brief  4, Port Output Modification Register */
#define P11_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003B104u)

/** \brief  90, Port Output Modification Set Register */
#define P11_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003B190u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P11_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003B170u)

/** \brief  7C, Port Output Modification Set Register 12 */
#define P11_OMSR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR12*)0xF003B17Cu)

/** \brief  74, Port Output Modification Set Register 4 */
#define P11_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003B174u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P11_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003B178u)

/** \brief  0, Port Output Register */
#define P11_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003B100u)

/** \brief  64, Port Pin Controller Select Register */
#define P11_PCSR /*lint --e(923)*/ (*(volatile Ifx_P_PCSR*)0xF003B164u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P11_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003B140u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P11_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003B144u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P13
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P13_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003B3FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P13_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003B3F8u)

/** \brief  50, Port Emergency Stop Register */
#define P13_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003B350u)

/** \brief  8, Identification Register */
#define P13_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003B308u)

/** \brief  24, Port Input Register */
#define P13_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003B324u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P13_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003B310u)

/** \brief  A0, Port LVDS Pad Control Register 0 */
#define P13_LPCR0 /*lint --e(923)*/ (*(volatile Ifx_P_LPCR0*)0xF003B3A0u)

/** \brief  A4, Port LVDS Pad Control Register 1 */
#define P13_LPCR1 /*lint --e(923)*/ (*(volatile Ifx_P_LPCR1*)0xF003B3A4u)

/** \brief  94, Port Output Modification Clear Register */
#define P13_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003B394u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P13_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003B380u)

/** \brief  4, Port Output Modification Register */
#define P13_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003B304u)

/** \brief  90, Port Output Modification Set Register */
#define P13_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003B390u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P13_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003B370u)

/** \brief  0, Port Output Register */
#define P13_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003B300u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P13_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003B340u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P14
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P14_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003B4FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P14_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003B4F8u)

/** \brief  50, Port Emergency Stop Register */
#define P14_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003B450u)

/** \brief  8, Identification Register */
#define P14_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003B408u)

/** \brief  24, Port Input Register */
#define P14_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003B424u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P14_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003B410u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P14_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003B414u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P14_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003B418u)

/** \brief  94, Port Output Modification Clear Register */
#define P14_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003B494u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P14_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003B480u)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P14_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003B484u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P14_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003B488u)

/** \brief  4, Port Output Modification Register */
#define P14_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003B404u)

/** \brief  90, Port Output Modification Set Register */
#define P14_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003B490u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P14_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003B470u)

/** \brief  74, Port Output Modification Set Register 4 */
#define P14_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003B474u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P14_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003B478u)

/** \brief  0, Port Output Register */
#define P14_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003B400u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P14_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003B440u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P14_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003B444u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P15
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P15_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003B5FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P15_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003B5F8u)

/** \brief  50, Port Emergency Stop Register */
#define P15_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003B550u)

/** \brief  8, Identification Register */
#define P15_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003B508u)

/** \brief  24, Port Input Register */
#define P15_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003B524u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P15_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003B510u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P15_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003B514u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P15_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003B518u)

/** \brief  94, Port Output Modification Clear Register */
#define P15_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003B594u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P15_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003B580u)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P15_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003B584u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P15_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003B588u)

/** \brief  4, Port Output Modification Register */
#define P15_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003B504u)

/** \brief  90, Port Output Modification Set Register */
#define P15_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003B590u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P15_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003B570u)

/** \brief  74, Port Output Modification Set Register 4 */
#define P15_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003B574u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P15_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003B578u)

/** \brief  0, Port Output Register */
#define P15_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003B500u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P15_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003B540u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P15_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003B544u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P20
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P20_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003C0FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P20_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003C0F8u)

/** \brief  50, Port Emergency Stop Register */
#define P20_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003C050u)

/** \brief  8, Identification Register */
#define P20_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003C008u)

/** \brief  24, Port Input Register */
#define P20_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003C024u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P20_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003C010u)

/** \brief  1C, Port Input/Output Control Register 12 */
#define P20_IOCR12 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR12*)0xF003C01Cu)

/** \brief  14, Port Input/Output Control Register 4 */
#define P20_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003C014u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P20_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003C018u)

/** \brief  94, Port Output Modification Clear Register */
#define P20_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003C094u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P20_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003C080u)

/** \brief  8C, Port Output Modification Clear Register 12 */
#define P20_OMCR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR12*)0xF003C08Cu)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P20_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003C084u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P20_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003C088u)

/** \brief  4, Port Output Modification Register */
#define P20_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003C004u)

/** \brief  90, Port Output Modification Set Register */
#define P20_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003C090u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P20_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003C070u)

/** \brief  7C, Port Output Modification Set Register 12 */
#define P20_OMSR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR12*)0xF003C07Cu)

/** \brief  74, Port Output Modification Set Register 4 */
#define P20_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003C074u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P20_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003C078u)

/** \brief  0, Port Output Register */
#define P20_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003C000u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P20_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003C040u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P20_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003C044u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P21
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P21_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003C1FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P21_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003C1F8u)

/** \brief  50, Port Emergency Stop Register */
#define P21_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003C150u)

/** \brief  8, Identification Register */
#define P21_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003C108u)

/** \brief  24, Port Input Register */
#define P21_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003C124u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P21_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003C110u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P21_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003C114u)

/** \brief  A4, Port LVDS Pad Control Register 1 */
#define P21_LPCR1 /*lint --e(923)*/ (*(volatile Ifx_P_LPCR1*)0xF003C1A4u)

/** \brief  A8, Port LVDS Pad Control Register 2 */
#define P21_LPCR2 /*lint --e(923)*/ (*(volatile Ifx_P_LPCR2*)0xF003C1A8u)

/** \brief  94, Port Output Modification Clear Register */
#define P21_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003C194u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P21_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003C180u)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P21_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003C184u)

/** \brief  4, Port Output Modification Register */
#define P21_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003C104u)

/** \brief  90, Port Output Modification Set Register */
#define P21_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003C190u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P21_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003C170u)

/** \brief  74, Port Output Modification Set Register 4 */
#define P21_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003C174u)

/** \brief  0, Port Output Register */
#define P21_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003C100u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P21_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003C140u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P22
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P22_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003C2FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P22_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003C2F8u)

/** \brief  50, Port Emergency Stop Register */
#define P22_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003C250u)

/** \brief  8, Identification Register */
#define P22_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003C208u)

/** \brief  24, Port Input Register */
#define P22_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003C224u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P22_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003C210u)

/** \brief  A0, Port LVDS Pad Control Register 0 */
#define P22_LPCR0 /*lint --e(923)*/ (*(volatile Ifx_P_LPCR0*)0xF003C2A0u)

/** \brief  A4, Port LVDS Pad Control Register 1 */
#define P22_LPCR1 /*lint --e(923)*/ (*(volatile Ifx_P_LPCR1*)0xF003C2A4u)

/** \brief  94, Port Output Modification Clear Register */
#define P22_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003C294u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P22_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003C280u)

/** \brief  4, Port Output Modification Register */
#define P22_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003C204u)

/** \brief  90, Port Output Modification Set Register */
#define P22_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003C290u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P22_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003C270u)

/** \brief  0, Port Output Register */
#define P22_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003C200u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P22_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003C240u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P23
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P23_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003C3FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P23_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003C3F8u)

/** \brief  50, Port Emergency Stop Register */
#define P23_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003C350u)

/** \brief  8, Identification Register */
#define P23_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003C308u)

/** \brief  24, Port Input Register */
#define P23_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003C324u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P23_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003C310u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P23_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003C314u)

/** \brief  94, Port Output Modification Clear Register */
#define P23_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003C394u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P23_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003C380u)

/** \brief  4, Port Output Modification Register */
#define P23_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003C304u)

/** \brief  90, Port Output Modification Set Register */
#define P23_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003C390u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P23_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003C370u)

/** \brief  0, Port Output Register */
#define P23_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003C300u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P23_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003C340u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P32
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P32_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003D2FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P32_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003D2F8u)

/** \brief  50, Port Emergency Stop Register */
#define P32_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003D250u)

/** \brief  8, Identification Register */
#define P32_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003D208u)

/** \brief  24, Port Input Register */
#define P32_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003D224u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P32_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003D210u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P32_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003D214u)

/** \brief  94, Port Output Modification Clear Register */
#define P32_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003D294u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P32_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003D280u)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P32_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003D284u)

/** \brief  4, Port Output Modification Register */
#define P32_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003D204u)

/** \brief  90, Port Output Modification Set Register */
#define P32_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003D290u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P32_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003D270u)

/** \brief  74, Port Output Modification Set Register 4 */
#define P32_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003D274u)

/** \brief  0, Port Output Register */
#define P32_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003D200u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P32_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003D240u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P33
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P33_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003D3FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P33_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003D3F8u)

/** \brief  50, Port Emergency Stop Register */
#define P33_ESR /*lint --e(923)*/ (*(volatile Ifx_P_ESR*)0xF003D350u)

/** \brief  8, Identification Register */
#define P33_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003D308u)

/** \brief  24, Port Input Register */
#define P33_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003D324u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P33_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003D310u)

/** \brief  1C, Port Input/Output Control Register 12 */
#define P33_IOCR12 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR12*)0xF003D31Cu)

/** \brief  14, Port Input/Output Control Register 4 */
#define P33_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003D314u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P33_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003D318u)

/** \brief  94, Port Output Modification Clear Register */
#define P33_OMCR /*lint --e(923)*/ (*(volatile Ifx_P_OMCR*)0xF003D394u)

/** \brief  80, Port Output Modification Clear Register 0 */
#define P33_OMCR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR0*)0xF003D380u)

/** \brief  8C, Port Output Modification Clear Register 12 */
#define P33_OMCR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR12*)0xF003D38Cu)

/** \brief  84, Port Output Modification Clear Register 4 */
#define P33_OMCR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR4*)0xF003D384u)

/** \brief  88, Port Output Modification Clear Register 8 */
#define P33_OMCR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMCR8*)0xF003D388u)

/** \brief  4, Port Output Modification Register */
#define P33_OMR /*lint --e(923)*/ (*(volatile Ifx_P_OMR*)0xF003D304u)

/** \brief  90, Port Output Modification Set Register */
#define P33_OMSR /*lint --e(923)*/ (*(volatile Ifx_P_OMSR*)0xF003D390u)

/** \brief  70, Port Output Modification Set Register 0 */
#define P33_OMSR0 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR0*)0xF003D370u)

/** \brief  7C, Port Output Modification Set Register 12 */
#define P33_OMSR12 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR12*)0xF003D37Cu)

/** \brief  74, Port Output Modification Set Register 4 */
#define P33_OMSR4 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR4*)0xF003D374u)

/** \brief  78, Port Output Modification Set Register 8 */
#define P33_OMSR8 /*lint --e(923)*/ (*(volatile Ifx_P_OMSR8*)0xF003D378u)

/** \brief  0, Port Output Register */
#define P33_OUT /*lint --e(923)*/ (*(volatile Ifx_P_OUT*)0xF003D300u)

/** \brief  40, Port Pad Driver Mode 0 Register */
#define P33_PDR0 /*lint --e(923)*/ (*(volatile Ifx_P_PDR0*)0xF003D340u)

/** \brief  44, Port Pad Driver Mode 1 Register */
#define P33_PDR1 /*lint --e(923)*/ (*(volatile Ifx_P_PDR1*)0xF003D344u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Port_Cfg_P40
 * \{  */

/** \brief  FC, Port Access Enable Register 0 */
#define P40_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN0*)0xF003E0FCu)

/** \brief  F8, Port Access Enable Register 1 */
#define P40_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_P_ACCEN1*)0xF003E0F8u)

/** \brief  8, Identification Register */
#define P40_ID /*lint --e(923)*/ (*(volatile Ifx_P_ID*)0xF003E008u)

/** \brief  24, Port Input Register */
#define P40_IN /*lint --e(923)*/ (*(volatile Ifx_P_IN*)0xF003E024u)

/** \brief  10, Port Input/Output Control Register 0 */
#define P40_IOCR0 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR0*)0xF003E010u)

/** \brief  14, Port Input/Output Control Register 4 */
#define P40_IOCR4 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR4*)0xF003E014u)

/** \brief  18, Port Input/Output Control Register 8 */
#define P40_IOCR8 /*lint --e(923)*/ (*(volatile Ifx_P_IOCR8*)0xF003E018u)

/** \brief  64, Port Pin Controller Select Register */
#define P40_PCSR /*lint --e(923)*/ (*(volatile Ifx_P_PCSR*)0xF003E064u)

/** \brief  60, Port Pin Function Decision Control Register */
#define P40_PDISC /*lint --e(923)*/ (*(volatile Ifx_P_PDISC*)0xF003E060u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXPORT_REG_H */
