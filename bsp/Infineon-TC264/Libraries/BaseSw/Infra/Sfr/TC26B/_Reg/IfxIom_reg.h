/**
 * \file IfxIom_reg.h
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
 * \defgroup IfxLld_Iom_Cfg Iom address
 * \ingroup IfxLld_Iom
 * 
 * \defgroup IfxLld_Iom_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Iom_Cfg
 * 
 * \defgroup IfxLld_Iom_Cfg_Iom 2-IOM
 * \ingroup IfxLld_Iom_Cfg
 * 
 */
#ifndef IFXIOM_REG_H
#define IFXIOM_REG_H 1
/******************************************************************************/
#include "IfxIom_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Iom_Cfg_BaseAddress
 * \{  */

/** \brief  IOM object */
#define MODULE_IOM /*lint --e(923)*/ (*(Ifx_IOM*)0xF0035000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Iom_Cfg_Iom
 * \{  */

/** \brief  2C, IOM Access Enable Register 0 */
#define IOM_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_IOM_ACCEN0*)0xF003502Cu)

/** \brief  28, IOM Access Enable Register 1 */
#define IOM_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_IOM_ACCEN1*)0xF0035028u)

/** \brief  0, IOM Clock Control Register */
#define IOM_CLC /*lint --e(923)*/ (*(volatile Ifx_IOM_CLC*)0xF0035000u)

/** \brief  30, IOM Event Combiner Module Counter Configuration Register */
#define IOM_ECMCCFG /*lint --e(923)*/ (*(volatile Ifx_IOM_ECMCCFG*)0xF0035030u)

/** \brief  38, IOM Event Combiner Module Event Trigger History Register 0 */
#define IOM_ECMETH0 /*lint --e(923)*/ (*(volatile Ifx_IOM_ECMETH0*)0xF0035038u)

/** \brief  3C, IOM Event Combiner Module Event Trigger History Register 1 */
#define IOM_ECMETH1 /*lint --e(923)*/ (*(volatile Ifx_IOM_ECMETH1*)0xF003503Cu)

/** \brief  34, IOM Event Combiner Module Global Event Selection Register */
#define IOM_ECMSELR /*lint --e(923)*/ (*(volatile Ifx_IOM_ECMSELR*)0xF0035034u)

/** \brief  80, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR0 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF0035080u)

/** \brief  84, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR1 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF0035084u)

/** \brief  A8, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR10 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350A8u)

/** \brief  AC, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR11 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350ACu)

/** \brief  B0, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR12 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350B0u)

/** \brief  B4, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR13 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350B4u)

/** \brief  B8, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR14 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350B8u)

/** \brief  BC, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR15 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350BCu)

/** \brief  88, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR2 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF0035088u)

/** \brief  8C, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR3 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF003508Cu)

/** \brief  90, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR4 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF0035090u)

/** \brief  94, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR5 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF0035094u)

/** \brief  98, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR6 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF0035098u)

/** \brief  9C, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR7 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF003509Cu)

/** \brief  A0, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR8 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350A0u)

/** \brief  A4, IOM Filter and Prescaler Cell Control Register */
#define IOM_FPCCTR9 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCCTR*)0xF00350A4u)

/** \brief  78, IOM Filter and Prescaler Cells Rising & Falling Edge Status
 * Register */
#define IOM_FPCESR /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCESR*)0xF0035078u)

/** \brief  C0, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM0 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350C0u)

/** \brief  C4, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM1 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350C4u)

/** \brief  E8, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM10 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350E8u)

/** \brief  EC, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM11 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350ECu)

/** \brief  F0, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM12 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350F0u)

/** \brief  F4, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM13 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350F4u)

/** \brief  F8, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM14 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350F8u)

/** \brief  FC, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM15 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350FCu)

/** \brief  C8, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM2 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350C8u)

/** \brief  CC, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM3 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350CCu)

/** \brief  D0, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM4 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350D0u)

/** \brief  D4, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM5 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350D4u)

/** \brief  D8, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM6 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350D8u)

/** \brief  DC, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM7 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350DCu)

/** \brief  E0, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM8 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350E0u)

/** \brief  E4, IOM Filter and Prescaler Cell Timer Register k */
#define IOM_FPCTIM9 /*lint --e(923)*/ (*(volatile Ifx_IOM_FPCTIM*)0xF00350E4u)

/** \brief  40, IOM GTM Input EXOR Combiner Selection Register */
#define IOM_GTMEXR /*lint --e(923)*/ (*(volatile Ifx_IOM_GTMEXR*)0xF0035040u)

/** \brief  8, IOM Identification Register */
#define IOM_ID /*lint --e(923)*/ (*(volatile Ifx_IOM_ID*)0xF0035008u)

/** \brief  24, IOM Kernel Reset Register 0 */
#define IOM_KRST0 /*lint --e(923)*/ (*(volatile Ifx_IOM_KRST0*)0xF0035024u)

/** \brief  20, IOM Kernel Reset Register 1 */
#define IOM_KRST1 /*lint --e(923)*/ (*(volatile Ifx_IOM_KRST1*)0xF0035020u)

/** \brief  1C, IOM Kernel Reset Status Clear Register */
#define IOM_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_IOM_KRSTCLR*)0xF003501Cu)

/** \brief  180, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG0 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF0035180u)

/** \brief  184, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG1 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF0035184u)

/** \brief  1A8, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG10 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351A8u)

/** \brief  1AC, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG11 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351ACu)

/** \brief  1B0, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG12 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351B0u)

/** \brief  1B4, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG13 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351B4u)

/** \brief  1B8, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG14 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351B8u)

/** \brief  1BC, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG15 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351BCu)

/** \brief  188, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG2 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF0035188u)

/** \brief  18C, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG3 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF003518Cu)

/** \brief  190, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG4 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF0035190u)

/** \brief  194, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG5 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF0035194u)

/** \brief  198, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG6 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF0035198u)

/** \brief  19C, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG7 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF003519Cu)

/** \brief  1A0, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG8 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351A0u)

/** \brief  1A4, IOM Logic Analyzer Module Configuration Register */
#define IOM_LAMCFG9 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMCFG*)0xF00351A4u)

/** \brief  100, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC0 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035100u)

/** \brief  104, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC1 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035104u)

/** \brief  128, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC10 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035128u)

/** \brief  12C, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC11 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF003512Cu)

/** \brief  130, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC12 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035130u)

/** \brief  134, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC13 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035134u)

/** \brief  138, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC14 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035138u)

/** \brief  13C, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC15 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF003513Cu)

/** \brief  108, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC2 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035108u)

/** \brief  10C, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC3 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF003510Cu)

/** \brief  110, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC4 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035110u)

/** \brief  114, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC5 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035114u)

/** \brief  118, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC6 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035118u)

/** \brief  11C, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC7 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF003511Cu)

/** \brief  120, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC8 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035120u)

/** \brief  124, IOM Logic Analyzer Module Event Window Count Status Register */
#define IOM_LAMEWC9 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWC*)0xF0035124u)

/** \brief  1C0, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS0 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351C0u)

/** \brief  1C4, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS1 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351C4u)

/** \brief  1E8, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS10 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351E8u)

/** \brief  1EC, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS11 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351ECu)

/** \brief  1F0, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS12 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351F0u)

/** \brief  1F4, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS13 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351F4u)

/** \brief  1F8, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS14 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351F8u)

/** \brief  1FC, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS15 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351FCu)

/** \brief  1C8, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS2 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351C8u)

/** \brief  1CC, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS3 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351CCu)

/** \brief  1D0, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS4 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351D0u)

/** \brief  1D4, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS5 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351D4u)

/** \brief  1D8, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS6 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351D8u)

/** \brief  1DC, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS7 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351DCu)

/** \brief  1E0, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS8 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351E0u)

/** \brief  1E4, IOM Logic Analyzer Module Event Window Configuration Register */
#define IOM_LAMEWS9 /*lint --e(923)*/ (*(volatile Ifx_IOM_LAMEWS*)0xF00351E4u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXIOM_REG_H */
