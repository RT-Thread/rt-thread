/**
 * \file IfxDsadc_reg.h
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
 * \defgroup IfxLld_Dsadc_Cfg Dsadc address
 * \ingroup IfxLld_Dsadc
 * 
 * \defgroup IfxLld_Dsadc_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Dsadc_Cfg
 * 
 * \defgroup IfxLld_Dsadc_Cfg_Dsadc 2-DSADC
 * \ingroup IfxLld_Dsadc_Cfg
 * 
 */
#ifndef IFXDSADC_REG_H
#define IFXDSADC_REG_H 1
/******************************************************************************/
#include "IfxDsadc_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Dsadc_Cfg_BaseAddress
 * \{  */

/** \brief  DSADC object */
#define MODULE_DSADC /*lint --e(923)*/ (*(Ifx_DSADC*)0xF0024000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dsadc_Cfg_Dsadc
 * \{  */

/** \brief  3C, Access Enable Register 0 */
#define DSADC_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_DSADC_ACCEN0*)0xF002403Cu)

/** \brief  90, Access Protection Register */
#define DSADC_ACCPROT /*lint --e(923)*/ (*(volatile Ifx_DSADC_ACCPROT*)0xF0024090u)

/** \brief  A0, Carrier Generator Configuration Register */
#define DSADC_CGCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CGCFG*)0xF00240A0u)

/** \brief  128, Boundary Select Register */
#define DSADC_CH0_BOUNDSEL /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_BOUNDSEL*)0xF0024128u)

/** Alias (User Manual Name) for DSADC_CH0_BOUNDSEL.
* To use register names with standard convension, please use DSADC_CH0_BOUNDSEL.
*/
#define	DSADC_BOUNDSEL0	(DSADC_CH0_BOUNDSEL)

/** \brief  1A0, Carrier Generator Synchronization Register */
#define DSADC_CH0_CGSYNC /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_CGSYNC*)0xF00241A0u)

/** Alias (User Manual Name) for DSADC_CH0_CGSYNC.
* To use register names with standard convension, please use DSADC_CH0_CGSYNC.
*/
#define	DSADC_CGSYNC0	(DSADC_CH0_CGSYNC)

/** \brief  108, Demodulator Input Configuration Register */
#define DSADC_CH0_DICFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_DICFG*)0xF0024108u)

/** Alias (User Manual Name) for DSADC_CH0_DICFG.
* To use register names with standard convension, please use DSADC_CH0_DICFG.
*/
#define	DSADC_DICFG0	(DSADC_CH0_DICFG)

/** \brief  118, Filter Configuration Register, Auxiliary Filter */
#define DSADC_CH0_FCFGA /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGA*)0xF0024118u)

/** Alias (User Manual Name) for DSADC_CH0_FCFGA.
* To use register names with standard convension, please use DSADC_CH0_FCFGA.
*/
#define	DSADC_FCFGA0	(DSADC_CH0_FCFGA)

/** \brief  114, Filter Configuration Register, Main CIC Filter */
#define DSADC_CH0_FCFGC /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGC*)0xF0024114u)

/** Alias (User Manual Name) for DSADC_CH0_FCFGC.
* To use register names with standard convension, please use DSADC_CH0_FCFGC.
*/
#define	DSADC_FCFGC0	(DSADC_CH0_FCFGC)

/** \brief  110, Filter Configuration Register, Main Filter Chain */
#define DSADC_CH0_FCFGM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGM*)0xF0024110u)

/** Alias (User Manual Name) for DSADC_CH0_FCFGM.
* To use register names with standard convension, please use DSADC_CH0_FCFGM.
*/
#define	DSADC_FCFGM0	(DSADC_CH0_FCFGM)

/** \brief  1D0, Initial Channel Config. Reg. 0 */
#define DSADC_CH0_ICCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_ICCFG*)0xF00241D0u)

/** Alias (User Manual Name) for DSADC_CH0_ICCFG.
* To use register names with standard convension, please use DSADC_CH0_ICCFG.
*/
#define	DSADC_ICCFG0	(DSADC_CH0_ICCFG)

/** \brief  120, Integration Window Control Register */
#define DSADC_CH0_IWCTR /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_IWCTR*)0xF0024120u)

/** Alias (User Manual Name) for DSADC_CH0_IWCTR.
* To use register names with standard convension, please use DSADC_CH0_IWCTR.
*/
#define	DSADC_IWCTR0	(DSADC_CH0_IWCTR)

/** \brief  100, Modulator Configuration Register */
#define DSADC_CH0_MODCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_MODCFG*)0xF0024100u)

/** Alias (User Manual Name) for DSADC_CH0_MODCFG.
* To use register names with standard convension, please use DSADC_CH0_MODCFG.
*/
#define	DSADC_MODCFG0	(DSADC_CH0_MODCFG)

/** \brief  138, Offset Register Main Filter */
#define DSADC_CH0_OFFM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_OFFM*)0xF0024138u)

/** Alias (User Manual Name) for DSADC_CH0_OFFM.
* To use register names with standard convension, please use DSADC_CH0_OFFM.
*/
#define	DSADC_OFFM0	(DSADC_CH0_OFFM)

/** \brief  1A8, Rectification Configuration Register */
#define DSADC_CH0_RECTCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RECTCFG*)0xF00241A8u)

/** Alias (User Manual Name) for DSADC_CH0_RECTCFG.
* To use register names with standard convension, please use DSADC_CH0_RECTCFG.
*/
#define	DSADC_RECTCFG0	(DSADC_CH0_RECTCFG)

/** \brief  140, Result Register Auxiliary Filter */
#define DSADC_CH0_RESA /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RESA*)0xF0024140u)

/** Alias (User Manual Name) for DSADC_CH0_RESA.
* To use register names with standard convension, please use DSADC_CH0_RESA.
*/
#define	DSADC_RESA0	(DSADC_CH0_RESA)

/** \brief  130, Result Register Main Filter */
#define DSADC_CH0_RESM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RESM*)0xF0024130u)

/** Alias (User Manual Name) for DSADC_CH0_RESM.
* To use register names with standard convension, please use DSADC_CH0_RESM.
*/
#define	DSADC_RESM0	(DSADC_CH0_RESM)

/** \brief  150, Time-Stamp Register */
#define DSADC_CH0_TSTMP /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_TSTMP*)0xF0024150u)

/** Alias (User Manual Name) for DSADC_CH0_TSTMP.
* To use register names with standard convension, please use DSADC_CH0_TSTMP.
*/
#define	DSADC_TSTMP0	(DSADC_CH0_TSTMP)

/** \brief  328, Boundary Select Register */
#define DSADC_CH2_BOUNDSEL /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_BOUNDSEL*)0xF0024328u)

/** Alias (User Manual Name) for DSADC_CH2_BOUNDSEL.
* To use register names with standard convension, please use DSADC_CH2_BOUNDSEL.
*/
#define	DSADC_BOUNDSEL2	(DSADC_CH2_BOUNDSEL)

/** \brief  3A0, Carrier Generator Synchronization Register */
#define DSADC_CH2_CGSYNC /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_CGSYNC*)0xF00243A0u)

/** Alias (User Manual Name) for DSADC_CH2_CGSYNC.
* To use register names with standard convension, please use DSADC_CH2_CGSYNC.
*/
#define	DSADC_CGSYNC2	(DSADC_CH2_CGSYNC)

/** \brief  308, Demodulator Input Configuration Register */
#define DSADC_CH2_DICFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_DICFG*)0xF0024308u)

/** Alias (User Manual Name) for DSADC_CH2_DICFG.
* To use register names with standard convension, please use DSADC_CH2_DICFG.
*/
#define	DSADC_DICFG2	(DSADC_CH2_DICFG)

/** \brief  318, Filter Configuration Register, Auxiliary Filter */
#define DSADC_CH2_FCFGA /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGA*)0xF0024318u)

/** Alias (User Manual Name) for DSADC_CH2_FCFGA.
* To use register names with standard convension, please use DSADC_CH2_FCFGA.
*/
#define	DSADC_FCFGA2	(DSADC_CH2_FCFGA)

/** \brief  314, Filter Configuration Register, Main CIC Filter */
#define DSADC_CH2_FCFGC /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGC*)0xF0024314u)

/** Alias (User Manual Name) for DSADC_CH2_FCFGC.
* To use register names with standard convension, please use DSADC_CH2_FCFGC.
*/
#define	DSADC_FCFGC2	(DSADC_CH2_FCFGC)

/** \brief  310, Filter Configuration Register, Main Filter Chain */
#define DSADC_CH2_FCFGM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGM*)0xF0024310u)

/** Alias (User Manual Name) for DSADC_CH2_FCFGM.
* To use register names with standard convension, please use DSADC_CH2_FCFGM.
*/
#define	DSADC_FCFGM2	(DSADC_CH2_FCFGM)

/** \brief  3D0, Initial Channel Config. Reg. 0 */
#define DSADC_CH2_ICCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_ICCFG*)0xF00243D0u)

/** Alias (User Manual Name) for DSADC_CH2_ICCFG.
* To use register names with standard convension, please use DSADC_CH2_ICCFG.
*/
#define	DSADC_ICCFG2	(DSADC_CH2_ICCFG)

/** \brief  320, Integration Window Control Register */
#define DSADC_CH2_IWCTR /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_IWCTR*)0xF0024320u)

/** Alias (User Manual Name) for DSADC_CH2_IWCTR.
* To use register names with standard convension, please use DSADC_CH2_IWCTR.
*/
#define	DSADC_IWCTR2	(DSADC_CH2_IWCTR)

/** \brief  300, Modulator Configuration Register */
#define DSADC_CH2_MODCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_MODCFG*)0xF0024300u)

/** Alias (User Manual Name) for DSADC_CH2_MODCFG.
* To use register names with standard convension, please use DSADC_CH2_MODCFG.
*/
#define	DSADC_MODCFG2	(DSADC_CH2_MODCFG)

/** \brief  338, Offset Register Main Filter */
#define DSADC_CH2_OFFM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_OFFM*)0xF0024338u)

/** Alias (User Manual Name) for DSADC_CH2_OFFM.
* To use register names with standard convension, please use DSADC_CH2_OFFM.
*/
#define	DSADC_OFFM2	(DSADC_CH2_OFFM)

/** \brief  3A8, Rectification Configuration Register */
#define DSADC_CH2_RECTCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RECTCFG*)0xF00243A8u)

/** Alias (User Manual Name) for DSADC_CH2_RECTCFG.
* To use register names with standard convension, please use DSADC_CH2_RECTCFG.
*/
#define	DSADC_RECTCFG2	(DSADC_CH2_RECTCFG)

/** \brief  340, Result Register Auxiliary Filter */
#define DSADC_CH2_RESA /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RESA*)0xF0024340u)

/** Alias (User Manual Name) for DSADC_CH2_RESA.
* To use register names with standard convension, please use DSADC_CH2_RESA.
*/
#define	DSADC_RESA2	(DSADC_CH2_RESA)

/** \brief  330, Result Register Main Filter */
#define DSADC_CH2_RESM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RESM*)0xF0024330u)

/** Alias (User Manual Name) for DSADC_CH2_RESM.
* To use register names with standard convension, please use DSADC_CH2_RESM.
*/
#define	DSADC_RESM2	(DSADC_CH2_RESM)

/** \brief  350, Time-Stamp Register */
#define DSADC_CH2_TSTMP /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_TSTMP*)0xF0024350u)

/** Alias (User Manual Name) for DSADC_CH2_TSTMP.
* To use register names with standard convension, please use DSADC_CH2_TSTMP.
*/
#define	DSADC_TSTMP2	(DSADC_CH2_TSTMP)

/** \brief  428, Boundary Select Register */
#define DSADC_CH3_BOUNDSEL /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_BOUNDSEL*)0xF0024428u)

/** Alias (User Manual Name) for DSADC_CH3_BOUNDSEL.
* To use register names with standard convension, please use DSADC_CH3_BOUNDSEL.
*/
#define	DSADC_BOUNDSEL3	(DSADC_CH3_BOUNDSEL)

/** \brief  4A0, Carrier Generator Synchronization Register */
#define DSADC_CH3_CGSYNC /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_CGSYNC*)0xF00244A0u)

/** Alias (User Manual Name) for DSADC_CH3_CGSYNC.
* To use register names with standard convension, please use DSADC_CH3_CGSYNC.
*/
#define	DSADC_CGSYNC3	(DSADC_CH3_CGSYNC)

/** \brief  408, Demodulator Input Configuration Register */
#define DSADC_CH3_DICFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_DICFG*)0xF0024408u)

/** Alias (User Manual Name) for DSADC_CH3_DICFG.
* To use register names with standard convension, please use DSADC_CH3_DICFG.
*/
#define	DSADC_DICFG3	(DSADC_CH3_DICFG)

/** \brief  418, Filter Configuration Register, Auxiliary Filter */
#define DSADC_CH3_FCFGA /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGA*)0xF0024418u)

/** Alias (User Manual Name) for DSADC_CH3_FCFGA.
* To use register names with standard convension, please use DSADC_CH3_FCFGA.
*/
#define	DSADC_FCFGA3	(DSADC_CH3_FCFGA)

/** \brief  414, Filter Configuration Register, Main CIC Filter */
#define DSADC_CH3_FCFGC /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGC*)0xF0024414u)

/** Alias (User Manual Name) for DSADC_CH3_FCFGC.
* To use register names with standard convension, please use DSADC_CH3_FCFGC.
*/
#define	DSADC_FCFGC3	(DSADC_CH3_FCFGC)

/** \brief  410, Filter Configuration Register, Main Filter Chain */
#define DSADC_CH3_FCFGM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_FCFGM*)0xF0024410u)

/** Alias (User Manual Name) for DSADC_CH3_FCFGM.
* To use register names with standard convension, please use DSADC_CH3_FCFGM.
*/
#define	DSADC_FCFGM3	(DSADC_CH3_FCFGM)

/** \brief  4D0, Initial Channel Config. Reg. 0 */
#define DSADC_CH3_ICCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_ICCFG*)0xF00244D0u)

/** Alias (User Manual Name) for DSADC_CH3_ICCFG.
* To use register names with standard convension, please use DSADC_CH3_ICCFG.
*/
#define	DSADC_ICCFG3	(DSADC_CH3_ICCFG)

/** \brief  420, Integration Window Control Register */
#define DSADC_CH3_IWCTR /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_IWCTR*)0xF0024420u)

/** Alias (User Manual Name) for DSADC_CH3_IWCTR.
* To use register names with standard convension, please use DSADC_CH3_IWCTR.
*/
#define	DSADC_IWCTR3	(DSADC_CH3_IWCTR)

/** \brief  400, Modulator Configuration Register */
#define DSADC_CH3_MODCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_MODCFG*)0xF0024400u)

/** Alias (User Manual Name) for DSADC_CH3_MODCFG.
* To use register names with standard convension, please use DSADC_CH3_MODCFG.
*/
#define	DSADC_MODCFG3	(DSADC_CH3_MODCFG)

/** \brief  438, Offset Register Main Filter */
#define DSADC_CH3_OFFM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_OFFM*)0xF0024438u)

/** Alias (User Manual Name) for DSADC_CH3_OFFM.
* To use register names with standard convension, please use DSADC_CH3_OFFM.
*/
#define	DSADC_OFFM3	(DSADC_CH3_OFFM)

/** \brief  4A8, Rectification Configuration Register */
#define DSADC_CH3_RECTCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RECTCFG*)0xF00244A8u)

/** Alias (User Manual Name) for DSADC_CH3_RECTCFG.
* To use register names with standard convension, please use DSADC_CH3_RECTCFG.
*/
#define	DSADC_RECTCFG3	(DSADC_CH3_RECTCFG)

/** \brief  440, Result Register Auxiliary Filter */
#define DSADC_CH3_RESA /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RESA*)0xF0024440u)

/** Alias (User Manual Name) for DSADC_CH3_RESA.
* To use register names with standard convension, please use DSADC_CH3_RESA.
*/
#define	DSADC_RESA3	(DSADC_CH3_RESA)

/** \brief  430, Result Register Main Filter */
#define DSADC_CH3_RESM /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_RESM*)0xF0024430u)

/** Alias (User Manual Name) for DSADC_CH3_RESM.
* To use register names with standard convension, please use DSADC_CH3_RESM.
*/
#define	DSADC_RESM3	(DSADC_CH3_RESM)

/** \brief  450, Time-Stamp Register */
#define DSADC_CH3_TSTMP /*lint --e(923)*/ (*(volatile Ifx_DSADC_CH_TSTMP*)0xF0024450u)

/** Alias (User Manual Name) for DSADC_CH3_TSTMP.
* To use register names with standard convension, please use DSADC_CH3_TSTMP.
*/
#define	DSADC_TSTMP3	(DSADC_CH3_TSTMP)

/** \brief  0, Clock Control Register */
#define DSADC_CLC /*lint --e(923)*/ (*(volatile Ifx_DSADC_CLC*)0xF0024000u)

/** \brief  E0, Event Flag Register */
#define DSADC_EVFLAG /*lint --e(923)*/ (*(volatile Ifx_DSADC_EVFLAG*)0xF00240E0u)

/** \brief  E4, Event Flag Clear Register */
#define DSADC_EVFLAGCLR /*lint --e(923)*/ (*(volatile Ifx_DSADC_EVFLAGCLR*)0xF00240E4u)

/** \brief  80, Global Configuration Register */
#define DSADC_GLOBCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_GLOBCFG*)0xF0024080u)

/** \brief  88, Global Run Control Register */
#define DSADC_GLOBRC /*lint --e(923)*/ (*(volatile Ifx_DSADC_GLOBRC*)0xF0024088u)

/** \brief  B0, Common Mode Hold Voltage Register 0 */
#define DSADC_GLOBVCMH0 /*lint --e(923)*/ (*(volatile Ifx_DSADC_GLOBVCMH0*)0xF00240B0u)

/** \brief  B8, Common Mode Hold Voltage Register 2 */
#define DSADC_GLOBVCMH2 /*lint --e(923)*/ (*(volatile Ifx_DSADC_GLOBVCMH2*)0xF00240B8u)

/** \brief  8, Module Identification Register */
#define DSADC_ID /*lint --e(923)*/ (*(volatile Ifx_DSADC_ID*)0xF0024008u)

/** \brief  D0, Initial Global Config. Register */
#define DSADC_IGCFG /*lint --e(923)*/ (*(volatile Ifx_DSADC_IGCFG*)0xF00240D0u)

/** \brief  34, Kernel Reset Register 0 */
#define DSADC_KRST0 /*lint --e(923)*/ (*(volatile Ifx_DSADC_KRST0*)0xF0024034u)

/** \brief  30, Kernel Reset Register 1 */
#define DSADC_KRST1 /*lint --e(923)*/ (*(volatile Ifx_DSADC_KRST1*)0xF0024030u)

/** \brief  2C, Kernel Reset Status Clear Register */
#define DSADC_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_DSADC_KRSTCLR*)0xF002402Cu)

/** \brief  28, OCDS Control and Status Register */
#define DSADC_OCS /*lint --e(923)*/ (*(volatile Ifx_DSADC_OCS*)0xF0024028u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXDSADC_REG_H */
