/**
 * \file IfxSmu_reg.h
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
 * \defgroup IfxLld_Smu_Cfg Smu address
 * \ingroup IfxLld_Smu
 * 
 * \defgroup IfxLld_Smu_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Smu_Cfg
 * 
 * \defgroup IfxLld_Smu_Cfg_Smu 2-SMU
 * \ingroup IfxLld_Smu_Cfg
 * 
 */
#ifndef IFXSMU_REG_H
#define IFXSMU_REG_H 1
/******************************************************************************/
#include "IfxSmu_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Smu_Cfg_BaseAddress
 * \{  */

/** \brief  SMU object */
#define MODULE_SMU /*lint --e(923)*/ (*(Ifx_SMU*)0xF0036800u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Smu_Cfg_Smu
 * \{  */

/** \brief  7FC, SMU Access Enable Register 0 */
#define SMU_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_SMU_ACCEN0*)0xF0036FFCu)

/** \brief  7F8, SMU Access Enable Register 1 */
#define SMU_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_SMU_ACCEN1*)0xF0036FF8u)

/** \brief  200, Alarm Status Register */
#define SMU_AD0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AD*)0xF0036A00u)

/** \brief  204, Alarm Status Register */
#define SMU_AD1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AD*)0xF0036A04u)

/** \brief  208, Alarm Status Register */
#define SMU_AD2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AD*)0xF0036A08u)

/** \brief  20C, Alarm Status Register */
#define SMU_AD3 /*lint --e(923)*/ (*(volatile Ifx_SMU_AD*)0xF0036A0Cu)

/** \brief  210, Alarm Status Register */
#define SMU_AD4 /*lint --e(923)*/ (*(volatile Ifx_SMU_AD*)0xF0036A10u)

/** \brief  214, Alarm Status Register */
#define SMU_AD5 /*lint --e(923)*/ (*(volatile Ifx_SMU_AD*)0xF0036A14u)

/** \brief  218, Alarm Status Register */
#define SMU_AD6 /*lint --e(923)*/ (*(volatile Ifx_SMU_AD*)0xF0036A18u)

/** \brief  40, Alarm and Fault Counter */
#define SMU_AFCNT /*lint --e(923)*/ (*(volatile Ifx_SMU_AFCNT*)0xF0036840u)

/** \brief  1C0, Alarm Status Register */
#define SMU_AG0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AG*)0xF00369C0u)

/** \brief  1C4, Alarm Status Register */
#define SMU_AG1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AG*)0xF00369C4u)

/** \brief  1C8, Alarm Status Register */
#define SMU_AG2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AG*)0xF00369C8u)

/** \brief  1CC, Alarm Status Register */
#define SMU_AG3 /*lint --e(923)*/ (*(volatile Ifx_SMU_AG*)0xF00369CCu)

/** \brief  1D0, Alarm Status Register */
#define SMU_AG4 /*lint --e(923)*/ (*(volatile Ifx_SMU_AG*)0xF00369D0u)

/** \brief  1D4, Alarm Status Register */
#define SMU_AG5 /*lint --e(923)*/ (*(volatile Ifx_SMU_AG*)0xF00369D4u)

/** \brief  1D8, Alarm Status Register */
#define SMU_AG6 /*lint --e(923)*/ (*(volatile Ifx_SMU_AG*)0xF00369D8u)

/** \brief  2C, Alarm Global Configuration */
#define SMU_AGC /*lint --e(923)*/ (*(volatile Ifx_SMU_AGC*)0xF003682Cu)

/** \brief  100, Alarm Configuration Register */
#define SMU_AGCF0_0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036900u)

/** Alias (User Manual Name) for SMU_AGCF0_0.
* To use register names with standard convension, please use SMU_AGCF0_0.
*/
#define	SMU_AG0CF0	(SMU_AGCF0_0)

/** \brief  104, Alarm Configuration Register */
#define SMU_AGCF0_1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036904u)

/** Alias (User Manual Name) for SMU_AGCF0_1.
* To use register names with standard convension, please use SMU_AGCF0_1.
*/
#define	SMU_AG0CF1	(SMU_AGCF0_1)

/** \brief  108, Alarm Configuration Register */
#define SMU_AGCF0_2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036908u)

/** Alias (User Manual Name) for SMU_AGCF0_2.
* To use register names with standard convension, please use SMU_AGCF0_2.
*/
#define	SMU_AG0CF2	(SMU_AGCF0_2)

/** \brief  10C, Alarm Configuration Register */
#define SMU_AGCF1_0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF003690Cu)

/** Alias (User Manual Name) for SMU_AGCF1_0.
* To use register names with standard convension, please use SMU_AGCF1_0.
*/
#define	SMU_AG1CF0	(SMU_AGCF1_0)

/** \brief  110, Alarm Configuration Register */
#define SMU_AGCF1_1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036910u)

/** Alias (User Manual Name) for SMU_AGCF1_1.
* To use register names with standard convension, please use SMU_AGCF1_1.
*/
#define	SMU_AG1CF1	(SMU_AGCF1_1)

/** \brief  114, Alarm Configuration Register */
#define SMU_AGCF1_2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036914u)

/** Alias (User Manual Name) for SMU_AGCF1_2.
* To use register names with standard convension, please use SMU_AGCF1_2.
*/
#define	SMU_AG1CF2	(SMU_AGCF1_2)

/** \brief  118, Alarm Configuration Register */
#define SMU_AGCF2_0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036918u)

/** Alias (User Manual Name) for SMU_AGCF2_0.
* To use register names with standard convension, please use SMU_AGCF2_0.
*/
#define	SMU_AG2CF0	(SMU_AGCF2_0)

/** \brief  11C, Alarm Configuration Register */
#define SMU_AGCF2_1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF003691Cu)

/** Alias (User Manual Name) for SMU_AGCF2_1.
* To use register names with standard convension, please use SMU_AGCF2_1.
*/
#define	SMU_AG2CF1	(SMU_AGCF2_1)

/** \brief  120, Alarm Configuration Register */
#define SMU_AGCF2_2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036920u)

/** Alias (User Manual Name) for SMU_AGCF2_2.
* To use register names with standard convension, please use SMU_AGCF2_2.
*/
#define	SMU_AG2CF2	(SMU_AGCF2_2)

/** \brief  124, Alarm Configuration Register */
#define SMU_AGCF3_0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036924u)

/** Alias (User Manual Name) for SMU_AGCF3_0.
* To use register names with standard convension, please use SMU_AGCF3_0.
*/
#define	SMU_AG3CF0	(SMU_AGCF3_0)

/** \brief  128, Alarm Configuration Register */
#define SMU_AGCF3_1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036928u)

/** Alias (User Manual Name) for SMU_AGCF3_1.
* To use register names with standard convension, please use SMU_AGCF3_1.
*/
#define	SMU_AG3CF1	(SMU_AGCF3_1)

/** \brief  12C, Alarm Configuration Register */
#define SMU_AGCF3_2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF003692Cu)

/** Alias (User Manual Name) for SMU_AGCF3_2.
* To use register names with standard convension, please use SMU_AGCF3_2.
*/
#define	SMU_AG3CF2	(SMU_AGCF3_2)

/** \brief  130, Alarm Configuration Register */
#define SMU_AGCF4_0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036930u)

/** Alias (User Manual Name) for SMU_AGCF4_0.
* To use register names with standard convension, please use SMU_AGCF4_0.
*/
#define	SMU_AG4CF0	(SMU_AGCF4_0)

/** \brief  134, Alarm Configuration Register */
#define SMU_AGCF4_1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036934u)

/** Alias (User Manual Name) for SMU_AGCF4_1.
* To use register names with standard convension, please use SMU_AGCF4_1.
*/
#define	SMU_AG4CF1	(SMU_AGCF4_1)

/** \brief  138, Alarm Configuration Register */
#define SMU_AGCF4_2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036938u)

/** Alias (User Manual Name) for SMU_AGCF4_2.
* To use register names with standard convension, please use SMU_AGCF4_2.
*/
#define	SMU_AG4CF2	(SMU_AGCF4_2)

/** \brief  13C, Alarm Configuration Register */
#define SMU_AGCF5_0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF003693Cu)

/** Alias (User Manual Name) for SMU_AGCF5_0.
* To use register names with standard convension, please use SMU_AGCF5_0.
*/
#define	SMU_AG5CF0	(SMU_AGCF5_0)

/** \brief  140, Alarm Configuration Register */
#define SMU_AGCF5_1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036940u)

/** Alias (User Manual Name) for SMU_AGCF5_1.
* To use register names with standard convension, please use SMU_AGCF5_1.
*/
#define	SMU_AG5CF1	(SMU_AGCF5_1)

/** \brief  144, Alarm Configuration Register */
#define SMU_AGCF5_2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036944u)

/** Alias (User Manual Name) for SMU_AGCF5_2.
* To use register names with standard convension, please use SMU_AGCF5_2.
*/
#define	SMU_AG5CF2	(SMU_AGCF5_2)

/** \brief  148, Alarm Configuration Register */
#define SMU_AGCF6_0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036948u)

/** Alias (User Manual Name) for SMU_AGCF6_0.
* To use register names with standard convension, please use SMU_AGCF6_0.
*/
#define	SMU_AG6CF0	(SMU_AGCF6_0)

/** \brief  14C, Alarm Configuration Register */
#define SMU_AGCF6_1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF003694Cu)

/** Alias (User Manual Name) for SMU_AGCF6_1.
* To use register names with standard convension, please use SMU_AGCF6_1.
*/
#define	SMU_AG6CF1	(SMU_AGCF6_1)

/** \brief  150, Alarm Configuration Register */
#define SMU_AGCF6_2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGCF*)0xF0036950u)

/** Alias (User Manual Name) for SMU_AGCF6_2.
* To use register names with standard convension, please use SMU_AGCF6_2.
*/
#define	SMU_AG6CF2	(SMU_AGCF6_2)

/** \brief  180, FSP Configuration Register */
#define SMU_AGFSP0 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGFSP*)0xF0036980u)

/** Alias (User Manual Name) for SMU_AGFSP0.
* To use register names with standard convension, please use SMU_AGFSP0.
*/
#define	SMU_AG0FSP	(SMU_AGFSP0)

/** \brief  184, FSP Configuration Register */
#define SMU_AGFSP1 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGFSP*)0xF0036984u)

/** Alias (User Manual Name) for SMU_AGFSP1.
* To use register names with standard convension, please use SMU_AGFSP1.
*/
#define	SMU_AG1FSP	(SMU_AGFSP1)

/** \brief  188, FSP Configuration Register */
#define SMU_AGFSP2 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGFSP*)0xF0036988u)

/** Alias (User Manual Name) for SMU_AGFSP2.
* To use register names with standard convension, please use SMU_AGFSP2.
*/
#define	SMU_AG2FSP	(SMU_AGFSP2)

/** \brief  18C, FSP Configuration Register */
#define SMU_AGFSP3 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGFSP*)0xF003698Cu)

/** Alias (User Manual Name) for SMU_AGFSP3.
* To use register names with standard convension, please use SMU_AGFSP3.
*/
#define	SMU_AG3FSP	(SMU_AGFSP3)

/** \brief  190, FSP Configuration Register */
#define SMU_AGFSP4 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGFSP*)0xF0036990u)

/** Alias (User Manual Name) for SMU_AGFSP4.
* To use register names with standard convension, please use SMU_AGFSP4.
*/
#define	SMU_AG4FSP	(SMU_AGFSP4)

/** \brief  194, FSP Configuration Register */
#define SMU_AGFSP5 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGFSP*)0xF0036994u)

/** Alias (User Manual Name) for SMU_AGFSP5.
* To use register names with standard convension, please use SMU_AGFSP5.
*/
#define	SMU_AG5FSP	(SMU_AGFSP5)

/** \brief  198, FSP Configuration Register */
#define SMU_AGFSP6 /*lint --e(923)*/ (*(volatile Ifx_SMU_AGFSP*)0xF0036998u)

/** Alias (User Manual Name) for SMU_AGFSP6.
* To use register names with standard convension, please use SMU_AGFSP6.
*/
#define	SMU_AG6FSP	(SMU_AGFSP6)

/** \brief  0, Clock Control Register */
#define SMU_CLC /*lint --e(923)*/ (*(volatile Ifx_SMU_CLC*)0xF0036800u)

/** \brief  20, Command Register */
#define SMU_CMD /*lint --e(923)*/ (*(volatile Ifx_SMU_CMD*)0xF0036820u)

/** \brief  38, Debug Register */
#define SMU_DBG /*lint --e(923)*/ (*(volatile Ifx_SMU_DBG*)0xF0036838u)

/** \brief  28, Fault Signaling Protocol */
#define SMU_FSP /*lint --e(923)*/ (*(volatile Ifx_SMU_FSP*)0xF0036828u)

/** \brief  8, Module Identification Register */
#define SMU_ID /*lint --e(923)*/ (*(volatile Ifx_SMU_ID*)0xF0036808u)

/** \brief  34, Key Register */
#define SMU_KEYS /*lint --e(923)*/ (*(volatile Ifx_SMU_KEYS*)0xF0036834u)

/** \brief  7F4, SMU Reset Register 0 */
#define SMU_KRST0 /*lint --e(923)*/ (*(volatile Ifx_SMU_KRST0*)0xF0036FF4u)

/** \brief  7F0, SMU Reset Register 1 */
#define SMU_KRST1 /*lint --e(923)*/ (*(volatile Ifx_SMU_KRST1*)0xF0036FF0u)

/** \brief  7EC, SMU Reset Status Clear Register */
#define SMU_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_SMU_KRSTCLR*)0xF0036FECu)

/** \brief  7E8, OCDS Control and Status */
#define SMU_OCS /*lint --e(923)*/ (*(volatile Ifx_SMU_OCS*)0xF0036FE8u)

/** \brief  3C, Port Control */
#define SMU_PCTL /*lint --e(923)*/ (*(volatile Ifx_SMU_PCTL*)0xF003683Cu)

/** \brief  300, Register Monitor Control */
#define SMU_RMCTL /*lint --e(923)*/ (*(volatile Ifx_SMU_RMCTL*)0xF0036B00u)

/** \brief  304, Register Monitor Error Flags */
#define SMU_RMEF /*lint --e(923)*/ (*(volatile Ifx_SMU_RMEF*)0xF0036B04u)

/** \brief  308, Register Monitor Self Test Status */
#define SMU_RMSTS /*lint --e(923)*/ (*(volatile Ifx_SMU_RMSTS*)0xF0036B08u)

/** \brief  60, Recovery Timer Alarm Configuration */
#define SMU_RTAC0 /*lint --e(923)*/ (*(volatile Ifx_SMU_RTAC0*)0xF0036860u)

/** \brief  64, Recovery Timer Alarm Configuration */
#define SMU_RTAC1 /*lint --e(923)*/ (*(volatile Ifx_SMU_RTAC1*)0xF0036864u)

/** \brief  30, Fault Signaling Protocol */
#define SMU_RTC /*lint --e(923)*/ (*(volatile Ifx_SMU_RTC*)0xF0036830u)

/** \brief  24, Status Register */
#define SMU_STS /*lint --e(923)*/ (*(volatile Ifx_SMU_STS*)0xF0036824u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSMU_REG_H */
