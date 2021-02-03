/**
 * \file IfxSrc_reg.h
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
 * \defgroup IfxLld_Src_Cfg Src address
 * \ingroup IfxLld_Src
 * 
 * \defgroup IfxLld_Src_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Src_Cfg
 * 
 * \defgroup IfxLld_Src_Cfg_Src 2-SRC
 * \ingroup IfxLld_Src_Cfg
 * 
 */
#ifndef IFXSRC_REG_H
#define IFXSRC_REG_H 1
/******************************************************************************/
#include "IfxSrc_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Src_Cfg_BaseAddress
 * \{  */

/** \brief  SRC object */
#define MODULE_SRC /*lint --e(923)*/ (*(Ifx_SRC*)0xF0038000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Src_Cfg_Src
 * \{  */

/** \brief  24, AGBT Service Request */
#define SRC_AGBT_AGBT0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038024u)

/** Alias (User Manual Name) for SRC_AGBT_AGBT0_SR.
* To use register names with standard convension, please use SRC_AGBT_AGBT0_SR.
*/
#define	SRC_AGBT	(SRC_AGBT_AGBT0_SR)

/** \brief  88, ASCLIN Error Service Request */
#define SRC_ASCLIN_ASCLIN0_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038088u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN0_ERR.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN0_ERR.
*/
#define	SRC_ASCLIN0ERR	(SRC_ASCLIN_ASCLIN0_ERR)

/** \brief  84, ASCLIN Receive Service Request */
#define SRC_ASCLIN_ASCLIN0_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038084u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN0_RX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN0_RX.
*/
#define	SRC_ASCLIN0RX	(SRC_ASCLIN_ASCLIN0_RX)

/** \brief  80, ASCLIN Transmit Service Request */
#define SRC_ASCLIN_ASCLIN0_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038080u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN0_TX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN0_TX.
*/
#define	SRC_ASCLIN0TX	(SRC_ASCLIN_ASCLIN0_TX)

/** \brief  94, ASCLIN Error Service Request */
#define SRC_ASCLIN_ASCLIN1_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038094u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN1_ERR.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN1_ERR.
*/
#define	SRC_ASCLIN1ERR	(SRC_ASCLIN_ASCLIN1_ERR)

/** \brief  90, ASCLIN Receive Service Request */
#define SRC_ASCLIN_ASCLIN1_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038090u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN1_RX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN1_RX.
*/
#define	SRC_ASCLIN1RX	(SRC_ASCLIN_ASCLIN1_RX)

/** \brief  8C, ASCLIN Transmit Service Request */
#define SRC_ASCLIN_ASCLIN1_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003808Cu)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN1_TX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN1_TX.
*/
#define	SRC_ASCLIN1TX	(SRC_ASCLIN_ASCLIN1_TX)

/** \brief  A0, ASCLIN Error Service Request */
#define SRC_ASCLIN_ASCLIN2_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00380A0u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN2_ERR.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN2_ERR.
*/
#define	SRC_ASCLIN2ERR	(SRC_ASCLIN_ASCLIN2_ERR)

/** \brief  9C, ASCLIN Receive Service Request */
#define SRC_ASCLIN_ASCLIN2_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003809Cu)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN2_RX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN2_RX.
*/
#define	SRC_ASCLIN2RX	(SRC_ASCLIN_ASCLIN2_RX)

/** \brief  98, ASCLIN Transmit Service Request */
#define SRC_ASCLIN_ASCLIN2_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038098u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN2_TX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN2_TX.
*/
#define	SRC_ASCLIN2TX	(SRC_ASCLIN_ASCLIN2_TX)

/** \brief  AC, ASCLIN Error Service Request */
#define SRC_ASCLIN_ASCLIN3_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00380ACu)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN3_ERR.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN3_ERR.
*/
#define	SRC_ASCLIN3ERR	(SRC_ASCLIN_ASCLIN3_ERR)

/** \brief  A8, ASCLIN Receive Service Request */
#define SRC_ASCLIN_ASCLIN3_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00380A8u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN3_RX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN3_RX.
*/
#define	SRC_ASCLIN3RX	(SRC_ASCLIN_ASCLIN3_RX)

/** \brief  A4, ASCLIN Transmit Service Request */
#define SRC_ASCLIN_ASCLIN3_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00380A4u)

/** Alias (User Manual Name) for SRC_ASCLIN_ASCLIN3_TX.
* To use register names with standard convension, please use SRC_ASCLIN_ASCLIN3_TX.
*/
#define	SRC_ASCLIN3TX	(SRC_ASCLIN_ASCLIN3_TX)

/** \brief  40, Bus Control Unit SPB Service Request */
#define SRC_BCU_SPB_SBSRC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038040u)

/** Alias (User Manual Name) for SRC_BCU_SPB_SBSRC.
* To use register names with standard convension, please use SRC_BCU_SPB_SBSRC.
*/
#define	SRC_BCUSPBSBSRC	(SRC_BCU_SPB_SBSRC)

/** \brief  900, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038900u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT0.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT0.
*/
#define	SRC_CANINT0	(SRC_CAN_CAN0_INT0)

/** \brief  904, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038904u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT1.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT1.
*/
#define	SRC_CANINT1	(SRC_CAN_CAN0_INT1)

/** \brief  928, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT10 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038928u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT10.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT10.
*/
#define	SRC_CANINT10	(SRC_CAN_CAN0_INT10)

/** \brief  92C, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT11 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003892Cu)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT11.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT11.
*/
#define	SRC_CANINT11	(SRC_CAN_CAN0_INT11)

/** \brief  930, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT12 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038930u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT12.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT12.
*/
#define	SRC_CANINT12	(SRC_CAN_CAN0_INT12)

/** \brief  934, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT13 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038934u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT13.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT13.
*/
#define	SRC_CANINT13	(SRC_CAN_CAN0_INT13)

/** \brief  938, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT14 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038938u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT14.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT14.
*/
#define	SRC_CANINT14	(SRC_CAN_CAN0_INT14)

/** \brief  93C, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT15 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003893Cu)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT15.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT15.
*/
#define	SRC_CANINT15	(SRC_CAN_CAN0_INT15)

/** \brief  908, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038908u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT2.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT2.
*/
#define	SRC_CANINT2	(SRC_CAN_CAN0_INT2)

/** \brief  90C, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003890Cu)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT3.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT3.
*/
#define	SRC_CANINT3	(SRC_CAN_CAN0_INT3)

/** \brief  910, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038910u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT4.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT4.
*/
#define	SRC_CANINT4	(SRC_CAN_CAN0_INT4)

/** \brief  914, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038914u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT5.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT5.
*/
#define	SRC_CANINT5	(SRC_CAN_CAN0_INT5)

/** \brief  918, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038918u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT6.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT6.
*/
#define	SRC_CANINT6	(SRC_CAN_CAN0_INT6)

/** \brief  91C, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003891Cu)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT7.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT7.
*/
#define	SRC_CANINT7	(SRC_CAN_CAN0_INT7)

/** \brief  920, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT8 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038920u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT8.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT8.
*/
#define	SRC_CANINT8	(SRC_CAN_CAN0_INT8)

/** \brief  924, MULTICAN+ Service Request */
#define SRC_CAN_CAN0_INT9 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038924u)

/** Alias (User Manual Name) for SRC_CAN_CAN0_INT9.
* To use register names with standard convension, please use SRC_CAN_CAN0_INT9.
*/
#define	SRC_CANINT9	(SRC_CAN_CAN0_INT9)

/** \brief  420, CCU6 Service Request 0 */
#define SRC_CCU6_CCU60_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038420u)

/** Alias (User Manual Name) for SRC_CCU6_CCU60_SR0.
* To use register names with standard convension, please use SRC_CCU6_CCU60_SR0.
*/
#define	SRC_CCU60SR0	(SRC_CCU6_CCU60_SR0)

/** \brief  424, CCU6 Service Request 1 */
#define SRC_CCU6_CCU60_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038424u)

/** Alias (User Manual Name) for SRC_CCU6_CCU60_SR1.
* To use register names with standard convension, please use SRC_CCU6_CCU60_SR1.
*/
#define	SRC_CCU60SR1	(SRC_CCU6_CCU60_SR1)

/** \brief  428, CCU6 Service Request 2 */
#define SRC_CCU6_CCU60_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038428u)

/** Alias (User Manual Name) for SRC_CCU6_CCU60_SR2.
* To use register names with standard convension, please use SRC_CCU6_CCU60_SR2.
*/
#define	SRC_CCU60SR2	(SRC_CCU6_CCU60_SR2)

/** \brief  42C, CCU6 Service Request 3 */
#define SRC_CCU6_CCU60_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003842Cu)

/** Alias (User Manual Name) for SRC_CCU6_CCU60_SR3.
* To use register names with standard convension, please use SRC_CCU6_CCU60_SR3.
*/
#define	SRC_CCU60SR3	(SRC_CCU6_CCU60_SR3)

/** \brief  430, CCU6 Service Request 0 */
#define SRC_CCU6_CCU61_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038430u)

/** Alias (User Manual Name) for SRC_CCU6_CCU61_SR0.
* To use register names with standard convension, please use SRC_CCU6_CCU61_SR0.
*/
#define	SRC_CCU61SR0	(SRC_CCU6_CCU61_SR0)

/** \brief  434, CCU6 Service Request 1 */
#define SRC_CCU6_CCU61_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038434u)

/** Alias (User Manual Name) for SRC_CCU6_CCU61_SR1.
* To use register names with standard convension, please use SRC_CCU6_CCU61_SR1.
*/
#define	SRC_CCU61SR1	(SRC_CCU6_CCU61_SR1)

/** \brief  438, CCU6 Service Request 2 */
#define SRC_CCU6_CCU61_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038438u)

/** Alias (User Manual Name) for SRC_CCU6_CCU61_SR2.
* To use register names with standard convension, please use SRC_CCU6_CCU61_SR2.
*/
#define	SRC_CCU61SR2	(SRC_CCU6_CCU61_SR2)

/** \brief  43C, CCU6 Service Request 3 */
#define SRC_CCU6_CCU61_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003843Cu)

/** Alias (User Manual Name) for SRC_CCU6_CCU61_SR3.
* To use register names with standard convension, please use SRC_CCU6_CCU61_SR3.
*/
#define	SRC_CCU61SR3	(SRC_CCU6_CCU61_SR3)

/** \brief  50, Cerberus Service Request */
#define SRC_CERBERUS_CERBERUS_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038050u)

/** Alias (User Manual Name) for SRC_CERBERUS_CERBERUS_SR0.
* To use register names with standard convension, please use SRC_CERBERUS_CERBERUS_SR0.
*/
#define	SRC_CERBERUS0	(SRC_CERBERUS_CERBERUS_SR0)

/** \brief  54, Cerberus Service Request */
#define SRC_CERBERUS_CERBERUS_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038054u)

/** Alias (User Manual Name) for SRC_CERBERUS_CERBERUS_SR1.
* To use register names with standard convension, please use SRC_CERBERUS_CERBERUS_SR1.
*/
#define	SRC_CERBERUS1	(SRC_CERBERUS_CERBERUS_SR1)

/** \brief  DA8, CIF ISP Service Request */
#define SRC_CIF_CIF0_ISP /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DA8u)

/** Alias (User Manual Name) for SRC_CIF_CIF0_ISP.
* To use register names with standard convension, please use SRC_CIF_CIF0_ISP.
*/
#define	SRC_CIFISP	(SRC_CIF_CIF0_ISP)

/** \brief  DA0, CIF MI Service Request */
#define SRC_CIF_CIF0_MI /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DA0u)

/** Alias (User Manual Name) for SRC_CIF_CIF0_MI.
* To use register names with standard convension, please use SRC_CIF_CIF0_MI.
*/
#define	SRC_CIFMI	(SRC_CIF_CIF0_MI)

/** \brief  DA4, CIF MI EP Service Request */
#define SRC_CIF_CIF0_MIEP /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DA4u)

/** Alias (User Manual Name) for SRC_CIF_CIF0_MIEP.
* To use register names with standard convension, please use SRC_CIF_CIF0_MIEP.
*/
#define	SRC_CIFMIEP	(SRC_CIF_CIF0_MIEP)

/** \brief  DAC, CIF MJPEG Service Request */
#define SRC_CIF_CIF0_MJPEG /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DACu)

/** Alias (User Manual Name) for SRC_CIF_CIF0_MJPEG.
* To use register names with standard convension, please use SRC_CIF_CIF0_MJPEG.
*/
#define	SRC_CIFMJPEG	(SRC_CIF_CIF0_MJPEG)

/** \brief  0, CPU Software Breakpoint Service Request */
#define SRC_CPU_CPU0_SBSRC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038000u)

/** Alias (User Manual Name) for SRC_CPU_CPU0_SBSRC.
* To use register names with standard convension, please use SRC_CPU_CPU0_SBSRC.
*/
#define	SRC_CPU0SBSRC	(SRC_CPU_CPU0_SBSRC)

/** \brief  4, CPU Software Breakpoint Service Request */
#define SRC_CPU_CPU1_SBSRC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038004u)

/** Alias (User Manual Name) for SRC_CPU_CPU1_SBSRC.
* To use register names with standard convension, please use SRC_CPU_CPU1_SBSRC.
*/
#define	SRC_CPU1SBSRC	(SRC_CPU_CPU1_SBSRC)

/** \brief  500, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038500u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH0.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH0.
*/
#define	SRC_DMACH0	(SRC_DMA_DMA0_CH0)

/** \brief  504, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038504u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH1.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH1.
*/
#define	SRC_DMACH1	(SRC_DMA_DMA0_CH1)

/** \brief  528, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH10 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038528u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH10.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH10.
*/
#define	SRC_DMACH10	(SRC_DMA_DMA0_CH10)

/** \brief  52C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH11 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003852Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH11.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH11.
*/
#define	SRC_DMACH11	(SRC_DMA_DMA0_CH11)

/** \brief  530, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH12 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038530u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH12.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH12.
*/
#define	SRC_DMACH12	(SRC_DMA_DMA0_CH12)

/** \brief  534, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH13 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038534u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH13.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH13.
*/
#define	SRC_DMACH13	(SRC_DMA_DMA0_CH13)

/** \brief  538, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH14 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038538u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH14.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH14.
*/
#define	SRC_DMACH14	(SRC_DMA_DMA0_CH14)

/** \brief  53C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH15 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003853Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH15.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH15.
*/
#define	SRC_DMACH15	(SRC_DMA_DMA0_CH15)

/** \brief  540, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH16 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038540u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH16.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH16.
*/
#define	SRC_DMACH16	(SRC_DMA_DMA0_CH16)

/** \brief  544, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH17 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038544u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH17.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH17.
*/
#define	SRC_DMACH17	(SRC_DMA_DMA0_CH17)

/** \brief  548, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH18 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038548u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH18.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH18.
*/
#define	SRC_DMACH18	(SRC_DMA_DMA0_CH18)

/** \brief  54C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH19 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003854Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH19.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH19.
*/
#define	SRC_DMACH19	(SRC_DMA_DMA0_CH19)

/** \brief  508, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038508u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH2.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH2.
*/
#define	SRC_DMACH2	(SRC_DMA_DMA0_CH2)

/** \brief  550, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH20 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038550u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH20.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH20.
*/
#define	SRC_DMACH20	(SRC_DMA_DMA0_CH20)

/** \brief  554, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH21 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038554u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH21.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH21.
*/
#define	SRC_DMACH21	(SRC_DMA_DMA0_CH21)

/** \brief  558, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH22 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038558u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH22.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH22.
*/
#define	SRC_DMACH22	(SRC_DMA_DMA0_CH22)

/** \brief  55C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH23 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003855Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH23.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH23.
*/
#define	SRC_DMACH23	(SRC_DMA_DMA0_CH23)

/** \brief  560, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH24 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038560u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH24.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH24.
*/
#define	SRC_DMACH24	(SRC_DMA_DMA0_CH24)

/** \brief  564, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH25 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038564u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH25.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH25.
*/
#define	SRC_DMACH25	(SRC_DMA_DMA0_CH25)

/** \brief  568, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH26 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038568u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH26.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH26.
*/
#define	SRC_DMACH26	(SRC_DMA_DMA0_CH26)

/** \brief  56C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH27 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003856Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH27.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH27.
*/
#define	SRC_DMACH27	(SRC_DMA_DMA0_CH27)

/** \brief  570, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH28 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038570u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH28.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH28.
*/
#define	SRC_DMACH28	(SRC_DMA_DMA0_CH28)

/** \brief  574, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH29 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038574u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH29.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH29.
*/
#define	SRC_DMACH29	(SRC_DMA_DMA0_CH29)

/** \brief  50C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003850Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH3.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH3.
*/
#define	SRC_DMACH3	(SRC_DMA_DMA0_CH3)

/** \brief  578, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH30 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038578u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH30.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH30.
*/
#define	SRC_DMACH30	(SRC_DMA_DMA0_CH30)

/** \brief  57C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH31 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003857Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH31.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH31.
*/
#define	SRC_DMACH31	(SRC_DMA_DMA0_CH31)

/** \brief  580, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH32 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038580u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH32.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH32.
*/
#define	SRC_DMACH32	(SRC_DMA_DMA0_CH32)

/** \brief  584, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH33 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038584u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH33.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH33.
*/
#define	SRC_DMACH33	(SRC_DMA_DMA0_CH33)

/** \brief  588, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH34 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038588u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH34.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH34.
*/
#define	SRC_DMACH34	(SRC_DMA_DMA0_CH34)

/** \brief  58C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH35 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003858Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH35.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH35.
*/
#define	SRC_DMACH35	(SRC_DMA_DMA0_CH35)

/** \brief  590, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH36 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038590u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH36.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH36.
*/
#define	SRC_DMACH36	(SRC_DMA_DMA0_CH36)

/** \brief  594, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH37 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038594u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH37.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH37.
*/
#define	SRC_DMACH37	(SRC_DMA_DMA0_CH37)

/** \brief  598, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH38 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038598u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH38.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH38.
*/
#define	SRC_DMACH38	(SRC_DMA_DMA0_CH38)

/** \brief  59C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH39 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003859Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH39.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH39.
*/
#define	SRC_DMACH39	(SRC_DMA_DMA0_CH39)

/** \brief  510, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038510u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH4.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH4.
*/
#define	SRC_DMACH4	(SRC_DMA_DMA0_CH4)

/** \brief  5A0, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH40 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385A0u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH40.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH40.
*/
#define	SRC_DMACH40	(SRC_DMA_DMA0_CH40)

/** \brief  5A4, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH41 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385A4u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH41.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH41.
*/
#define	SRC_DMACH41	(SRC_DMA_DMA0_CH41)

/** \brief  5A8, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH42 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385A8u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH42.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH42.
*/
#define	SRC_DMACH42	(SRC_DMA_DMA0_CH42)

/** \brief  5AC, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH43 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385ACu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH43.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH43.
*/
#define	SRC_DMACH43	(SRC_DMA_DMA0_CH43)

/** \brief  5B0, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH44 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385B0u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH44.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH44.
*/
#define	SRC_DMACH44	(SRC_DMA_DMA0_CH44)

/** \brief  5B4, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH45 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385B4u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH45.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH45.
*/
#define	SRC_DMACH45	(SRC_DMA_DMA0_CH45)

/** \brief  5B8, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH46 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385B8u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH46.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH46.
*/
#define	SRC_DMACH46	(SRC_DMA_DMA0_CH46)

/** \brief  5BC, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH47 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00385BCu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH47.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH47.
*/
#define	SRC_DMACH47	(SRC_DMA_DMA0_CH47)

/** \brief  514, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038514u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH5.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH5.
*/
#define	SRC_DMACH5	(SRC_DMA_DMA0_CH5)

/** \brief  518, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038518u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH6.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH6.
*/
#define	SRC_DMACH6	(SRC_DMA_DMA0_CH6)

/** \brief  51C, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003851Cu)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH7.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH7.
*/
#define	SRC_DMACH7	(SRC_DMA_DMA0_CH7)

/** \brief  520, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH8 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038520u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH8.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH8.
*/
#define	SRC_DMACH8	(SRC_DMA_DMA0_CH8)

/** \brief  524, DMA Channel Service Request */
#define SRC_DMA_DMA0_CH9 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038524u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_CH9.
* To use register names with standard convension, please use SRC_DMA_DMA0_CH9.
*/
#define	SRC_DMACH9	(SRC_DMA_DMA0_CH9)

/** \brief  4F0, DMA Error Service Request */
#define SRC_DMA_DMA0_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00384F0u)

/** Alias (User Manual Name) for SRC_DMA_DMA0_ERR.
* To use register names with standard convension, please use SRC_DMA_DMA0_ERR.
*/
#define	SRC_DMAERR	(SRC_DMA_DMA0_ERR)

/** \brief  B54, DSADC SRA Service Request */
#define SRC_DSADC_DSADC0_SRA /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038B54u)

/** Alias (User Manual Name) for SRC_DSADC_DSADC0_SRA.
* To use register names with standard convension, please use SRC_DSADC_DSADC0_SRA.
*/
#define	SRC_DSADCSRA0	(SRC_DSADC_DSADC0_SRA)

/** \brief  B50, DSADC SRM Service Request */
#define SRC_DSADC_DSADC0_SRM /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038B50u)

/** Alias (User Manual Name) for SRC_DSADC_DSADC0_SRM.
* To use register names with standard convension, please use SRC_DSADC_DSADC0_SRM.
*/
#define	SRC_DSADCSRM0	(SRC_DSADC_DSADC0_SRM)

/** \brief  B64, DSADC SRA Service Request */
#define SRC_DSADC_DSADC2_SRA /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038B64u)

/** Alias (User Manual Name) for SRC_DSADC_DSADC2_SRA.
* To use register names with standard convension, please use SRC_DSADC_DSADC2_SRA.
*/
#define	SRC_DSADCSRA2	(SRC_DSADC_DSADC2_SRA)

/** \brief  B60, DSADC SRM Service Request */
#define SRC_DSADC_DSADC2_SRM /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038B60u)

/** Alias (User Manual Name) for SRC_DSADC_DSADC2_SRM.
* To use register names with standard convension, please use SRC_DSADC_DSADC2_SRM.
*/
#define	SRC_DSADCSRM2	(SRC_DSADC_DSADC2_SRM)

/** \brief  B6C, DSADC SRA Service Request */
#define SRC_DSADC_DSADC3_SRA /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038B6Cu)

/** Alias (User Manual Name) for SRC_DSADC_DSADC3_SRA.
* To use register names with standard convension, please use SRC_DSADC_DSADC3_SRA.
*/
#define	SRC_DSADCSRA3	(SRC_DSADC_DSADC3_SRA)

/** \brief  B68, DSADC SRM Service Request */
#define SRC_DSADC_DSADC3_SRM /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038B68u)

/** Alias (User Manual Name) for SRC_DSADC_DSADC3_SRM.
* To use register names with standard convension, please use SRC_DSADC_DSADC3_SRM.
*/
#define	SRC_DSADCSRM3	(SRC_DSADC_DSADC3_SRM)

/** \brief  20, Emulation Memory Service Request */
#define SRC_EMEM_EMEM0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038020u)

/** Alias (User Manual Name) for SRC_EMEM_EMEM0_SR.
* To use register names with standard convension, please use SRC_EMEM_EMEM0_SR.
*/
#define	SRC_EMEM	(SRC_EMEM_EMEM0_SR)

/** \brief  C04, E-RAY Input Buffer Busy Service Request */
#define SRC_ERAY_ERAY0_IBUSY /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038C04u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_IBUSY.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_IBUSY.
*/
#define	SRC_ERAYIBUSY	(SRC_ERAY_ERAY0_IBUSY)

/** \brief  BE0, E-RAY Service Request */
#define SRC_ERAY_ERAY0_INT0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BE0u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_INT0.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_INT0.
*/
#define	SRC_ERAYINT0	(SRC_ERAY_ERAY0_INT0)

/** \brief  BE4, E-RAY Service Request */
#define SRC_ERAY_ERAY0_INT1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BE4u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_INT1.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_INT1.
*/
#define	SRC_ERAYINT1	(SRC_ERAY_ERAY0_INT1)

/** \brief  BF8, E-RAY Message Buffer Status Changed Service Request */
#define SRC_ERAY_ERAY0_MBSC0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BF8u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_MBSC0.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_MBSC0.
*/
#define	SRC_ERAYMBSC0	(SRC_ERAY_ERAY0_MBSC0)

/** \brief  BFC, E-RAY Message Buffer Status Changed Service Request */
#define SRC_ERAY_ERAY0_MBSC1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BFCu)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_MBSC1.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_MBSC1.
*/
#define	SRC_ERAYMBSC1	(SRC_ERAY_ERAY0_MBSC1)

/** \brief  BF0, E-RAY New Data Service Request */
#define SRC_ERAY_ERAY0_NDAT0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BF0u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_NDAT0.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_NDAT0.
*/
#define	SRC_ERAYNDAT0	(SRC_ERAY_ERAY0_NDAT0)

/** \brief  BF4, E-RAY New Data Service Request */
#define SRC_ERAY_ERAY0_NDAT1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BF4u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_NDAT1.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_NDAT1.
*/
#define	SRC_ERAYNDAT1	(SRC_ERAY_ERAY0_NDAT1)

/** \brief  C00, E-RAY Output Buffer Busy Service Request */
#define SRC_ERAY_ERAY0_OBUSY /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038C00u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_OBUSY.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_OBUSY.
*/
#define	SRC_ERAYOBUSY	(SRC_ERAY_ERAY0_OBUSY)

/** \brief  BE8, E-RAY Timer Interrupt Service Request */
#define SRC_ERAY_ERAY0_TINT0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BE8u)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_TINT0.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_TINT0.
*/
#define	SRC_ERAYTINT0	(SRC_ERAY_ERAY0_TINT0)

/** \brief  BEC, E-RAY Timer Interrupt Service Request */
#define SRC_ERAY_ERAY0_TINT1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038BECu)

/** Alias (User Manual Name) for SRC_ERAY_ERAY0_TINT1.
* To use register names with standard convension, please use SRC_ERAY_ERAY0_TINT1.
*/
#define	SRC_ERAYTINT1	(SRC_ERAY_ERAY0_TINT1)

/** \brief  8F0, Ethernet Service Request */
#define SRC_ETH_ETH0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00388F0u)

/** Alias (User Manual Name) for SRC_ETH_ETH0_SR.
* To use register names with standard convension, please use SRC_ETH_ETH0_SR.
*/
#define	SRC_ETH	(SRC_ETH_ETH0_SR)

/** \brief  4B0, FCE Error Service Request */
#define SRC_FCE_FCE0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00384B0u)

/** Alias (User Manual Name) for SRC_FCE_FCE0_SR.
* To use register names with standard convension, please use SRC_FCE_FCE0_SR.
*/
#define	SRC_FCE	(SRC_FCE_FCE0_SR)

/** \brief  FC0, FFT Done Service Request */
#define SRC_FFT_FFT0_DONE /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038FC0u)

/** Alias (User Manual Name) for SRC_FFT_FFT0_DONE.
* To use register names with standard convension, please use SRC_FFT_FFT0_DONE.
*/
#define	SRC_FFTDONE	(SRC_FFT_FFT0_DONE)

/** \brief  FC4, FFT Error Service Request */
#define SRC_FFT_FFT0_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038FC4u)

/** Alias (User Manual Name) for SRC_FFT_FFT0_ERR.
* To use register names with standard convension, please use SRC_FFT_FFT0_ERR.
*/
#define	SRC_FFTERR	(SRC_FFT_FFT0_ERR)

/** \brief  FC8, FFT Ready For Start Service Request */
#define SRC_FFT_FFT0_RFS /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038FC8u)

/** Alias (User Manual Name) for SRC_FFT_FFT0_RFS.
* To use register names with standard convension, please use SRC_FFT_FFT0_RFS.
*/
#define	SRC_FFTRFS	(SRC_FFT_FFT0_RFS)

/** \brief  1000, General Purpose Service Request 0 */
#define SRC_GPSR_GPSR0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039000u)

/** Alias (User Manual Name) for SRC_GPSR_GPSR0_SR0.
* To use register names with standard convension, please use SRC_GPSR_GPSR0_SR0.
*/
#define	SRC_GPSR00	(SRC_GPSR_GPSR0_SR0)

/** \brief  1004, General Purpose Service Request 1 */
#define SRC_GPSR_GPSR0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039004u)

/** Alias (User Manual Name) for SRC_GPSR_GPSR0_SR1.
* To use register names with standard convension, please use SRC_GPSR_GPSR0_SR1.
*/
#define	SRC_GPSR01	(SRC_GPSR_GPSR0_SR1)

/** \brief  1008, General Purpose Service Request 2 */
#define SRC_GPSR_GPSR0_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039008u)

/** Alias (User Manual Name) for SRC_GPSR_GPSR0_SR2.
* To use register names with standard convension, please use SRC_GPSR_GPSR0_SR2.
*/
#define	SRC_GPSR02	(SRC_GPSR_GPSR0_SR2)

/** \brief  100C, General Purpose Service Request 3 */
#define SRC_GPSR_GPSR0_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003900Cu)

/** Alias (User Manual Name) for SRC_GPSR_GPSR0_SR3.
* To use register names with standard convension, please use SRC_GPSR_GPSR0_SR3.
*/
#define	SRC_GPSR03	(SRC_GPSR_GPSR0_SR3)

/** \brief  1020, General Purpose Service Request 0 */
#define SRC_GPSR_GPSR1_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039020u)

/** Alias (User Manual Name) for SRC_GPSR_GPSR1_SR0.
* To use register names with standard convension, please use SRC_GPSR_GPSR1_SR0.
*/
#define	SRC_GPSR10	(SRC_GPSR_GPSR1_SR0)

/** \brief  1024, General Purpose Service Request 1 */
#define SRC_GPSR_GPSR1_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039024u)

/** Alias (User Manual Name) for SRC_GPSR_GPSR1_SR1.
* To use register names with standard convension, please use SRC_GPSR_GPSR1_SR1.
*/
#define	SRC_GPSR11	(SRC_GPSR_GPSR1_SR1)

/** \brief  1028, General Purpose Service Request 2 */
#define SRC_GPSR_GPSR1_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039028u)

/** Alias (User Manual Name) for SRC_GPSR_GPSR1_SR2.
* To use register names with standard convension, please use SRC_GPSR_GPSR1_SR2.
*/
#define	SRC_GPSR12	(SRC_GPSR_GPSR1_SR2)

/** \brief  102C, General Purpose Service Request 3 */
#define SRC_GPSR_GPSR1_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003902Cu)

/** Alias (User Manual Name) for SRC_GPSR_GPSR1_SR3.
* To use register names with standard convension, please use SRC_GPSR_GPSR1_SR3.
*/
#define	SRC_GPSR13	(SRC_GPSR_GPSR1_SR3)

/** \brief  460, GPT12 CAPREL Service Request */
#define SRC_GPT12_GPT120_CIRQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038460u)

/** Alias (User Manual Name) for SRC_GPT12_GPT120_CIRQ.
* To use register names with standard convension, please use SRC_GPT12_GPT120_CIRQ.
*/
#define	SRC_GPT120CIRQ	(SRC_GPT12_GPT120_CIRQ)

/** \brief  464, GPT12 T2 Overflow/Underflow Service Request */
#define SRC_GPT12_GPT120_T2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038464u)

/** Alias (User Manual Name) for SRC_GPT12_GPT120_T2.
* To use register names with standard convension, please use SRC_GPT12_GPT120_T2.
*/
#define	SRC_GPT120T2	(SRC_GPT12_GPT120_T2)

/** \brief  468, GPT12 T3 Overflow/Underflow Service Request */
#define SRC_GPT12_GPT120_T3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038468u)

/** Alias (User Manual Name) for SRC_GPT12_GPT120_T3.
* To use register names with standard convension, please use SRC_GPT12_GPT120_T3.
*/
#define	SRC_GPT120T3	(SRC_GPT12_GPT120_T3)

/** \brief  46C, GPT12 T4 Overflow/Underflow Service Request */
#define SRC_GPT12_GPT120_T4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003846Cu)

/** Alias (User Manual Name) for SRC_GPT12_GPT120_T4.
* To use register names with standard convension, please use SRC_GPT12_GPT120_T4.
*/
#define	SRC_GPT120T4	(SRC_GPT12_GPT120_T4)

/** \brief  470, GPT12 T5 Overflow/Underflow Service Request */
#define SRC_GPT12_GPT120_T5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038470u)

/** Alias (User Manual Name) for SRC_GPT12_GPT120_T5.
* To use register names with standard convension, please use SRC_GPT12_GPT120_T5.
*/
#define	SRC_GPT120T5	(SRC_GPT12_GPT120_T5)

/** \brief  474, GPT12 T6 Overflow/Underflow Service Request */
#define SRC_GPT12_GPT120_T6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038474u)

/** Alias (User Manual Name) for SRC_GPT12_GPT120_T6.
* To use register names with standard convension, please use SRC_GPT12_GPT120_T6.
*/
#define	SRC_GPT120T6	(SRC_GPT12_GPT120_T6)

/** \brief  1600, GTM AEI Shared Service Request */
#define SRC_GTM_GTM0_AEIIRQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039600u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_AEIIRQ.
* To use register names with standard convension, please use SRC_GTM_GTM0_AEIIRQ.
*/
#define	SRC_GTMAEIIRQ	(SRC_GTM_GTM0_AEIIRQ)

/** \brief  1604, GTM ARU Shared Service Request */
#define SRC_GTM_GTM0_ARUIRQ0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039604u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ARUIRQ0.
* To use register names with standard convension, please use SRC_GTM_GTM0_ARUIRQ0.
*/
#define	SRC_GTMARUIRQ0	(SRC_GTM_GTM0_ARUIRQ0)

/** \brief  1608, GTM ARU Shared Service Request */
#define SRC_GTM_GTM0_ARUIRQ1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039608u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ARUIRQ1.
* To use register names with standard convension, please use SRC_GTM_GTM0_ARUIRQ1.
*/
#define	SRC_GTMARUIRQ1	(SRC_GTM_GTM0_ARUIRQ1)

/** \brief  160C, GTM ARU Shared Service Request */
#define SRC_GTM_GTM0_ARUIRQ2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003960Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ARUIRQ2.
* To use register names with standard convension, please use SRC_GTM_GTM0_ARUIRQ2.
*/
#define	SRC_GTMARUIRQ2	(SRC_GTM_GTM0_ARUIRQ2)

/** \brief  1D80, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM0_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D80u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM0_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM0_0.
*/
#define	SRC_GTMATOM00	(SRC_GTM_GTM0_ATOM0_0)

/** \brief  1D84, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM0_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D84u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM0_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM0_1.
*/
#define	SRC_GTMATOM01	(SRC_GTM_GTM0_ATOM0_1)

/** \brief  1D88, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM0_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D88u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM0_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM0_2.
*/
#define	SRC_GTMATOM02	(SRC_GTM_GTM0_ATOM0_2)

/** \brief  1D8C, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM0_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D8Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM0_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM0_3.
*/
#define	SRC_GTMATOM03	(SRC_GTM_GTM0_ATOM0_3)

/** \brief  1D90, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM1_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D90u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM1_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM1_0.
*/
#define	SRC_GTMATOM10	(SRC_GTM_GTM0_ATOM1_0)

/** \brief  1D94, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM1_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D94u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM1_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM1_1.
*/
#define	SRC_GTMATOM11	(SRC_GTM_GTM0_ATOM1_1)

/** \brief  1D98, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM1_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D98u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM1_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM1_2.
*/
#define	SRC_GTMATOM12	(SRC_GTM_GTM0_ATOM1_2)

/** \brief  1D9C, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM1_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039D9Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM1_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM1_3.
*/
#define	SRC_GTMATOM13	(SRC_GTM_GTM0_ATOM1_3)

/** \brief  1DA0, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM2_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DA0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM2_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM2_0.
*/
#define	SRC_GTMATOM20	(SRC_GTM_GTM0_ATOM2_0)

/** \brief  1DA4, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM2_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DA4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM2_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM2_1.
*/
#define	SRC_GTMATOM21	(SRC_GTM_GTM0_ATOM2_1)

/** \brief  1DA8, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM2_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DA8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM2_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM2_2.
*/
#define	SRC_GTMATOM22	(SRC_GTM_GTM0_ATOM2_2)

/** \brief  1DAC, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM2_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DACu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM2_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM2_3.
*/
#define	SRC_GTMATOM23	(SRC_GTM_GTM0_ATOM2_3)

/** \brief  1DB0, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM3_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DB0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM3_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM3_0.
*/
#define	SRC_GTMATOM30	(SRC_GTM_GTM0_ATOM3_0)

/** \brief  1DB4, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM3_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DB4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM3_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM3_1.
*/
#define	SRC_GTMATOM31	(SRC_GTM_GTM0_ATOM3_1)

/** \brief  1DB8, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM3_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DB8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM3_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM3_2.
*/
#define	SRC_GTMATOM32	(SRC_GTM_GTM0_ATOM3_2)

/** \brief  1DBC, GTM ATOM Shared Service Request */
#define SRC_GTM_GTM0_ATOM3_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039DBCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ATOM3_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_ATOM3_3.
*/
#define	SRC_GTMATOM33	(SRC_GTM_GTM0_ATOM3_3)

/** \brief  1614, GTM BRC Shared Service Request */
#define SRC_GTM_GTM0_BRCIRQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039614u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_BRCIRQ.
* To use register names with standard convension, please use SRC_GTM_GTM0_BRCIRQ.
*/
#define	SRC_GTMBRCIRQ	(SRC_GTM_GTM0_BRCIRQ)

/** \brief  1618, GTM CMP Shared Service Request */
#define SRC_GTM_GTM0_CMPIRQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039618u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_CMPIRQ.
* To use register names with standard convension, please use SRC_GTM_GTM0_CMPIRQ.
*/
#define	SRC_GTMCMPIRQ	(SRC_GTM_GTM0_CMPIRQ)

/** \brief  16A4, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396A4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL0.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL0.
*/
#define	SRC_GTMDPLL0	(SRC_GTM_GTM0_DPLL0)

/** \brief  16A8, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396A8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL1.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL1.
*/
#define	SRC_GTMDPLL1	(SRC_GTM_GTM0_DPLL1)

/** \brief  16CC, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL10 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396CCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL10.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL10.
*/
#define	SRC_GTMDPLL10	(SRC_GTM_GTM0_DPLL10)

/** \brief  16D0, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL11 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396D0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL11.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL11.
*/
#define	SRC_GTMDPLL11	(SRC_GTM_GTM0_DPLL11)

/** \brief  16D4, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL12 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396D4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL12.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL12.
*/
#define	SRC_GTMDPLL12	(SRC_GTM_GTM0_DPLL12)

/** \brief  16D8, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL13 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396D8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL13.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL13.
*/
#define	SRC_GTMDPLL13	(SRC_GTM_GTM0_DPLL13)

/** \brief  16DC, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL14 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396DCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL14.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL14.
*/
#define	SRC_GTMDPLL14	(SRC_GTM_GTM0_DPLL14)

/** \brief  16E0, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL15 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396E0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL15.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL15.
*/
#define	SRC_GTMDPLL15	(SRC_GTM_GTM0_DPLL15)

/** \brief  16E4, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL16 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396E4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL16.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL16.
*/
#define	SRC_GTMDPLL16	(SRC_GTM_GTM0_DPLL16)

/** \brief  16E8, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL17 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396E8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL17.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL17.
*/
#define	SRC_GTMDPLL17	(SRC_GTM_GTM0_DPLL17)

/** \brief  16EC, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL18 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396ECu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL18.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL18.
*/
#define	SRC_GTMDPLL18	(SRC_GTM_GTM0_DPLL18)

/** \brief  16F0, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL19 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396F0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL19.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL19.
*/
#define	SRC_GTMDPLL19	(SRC_GTM_GTM0_DPLL19)

/** \brief  16AC, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396ACu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL2.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL2.
*/
#define	SRC_GTMDPLL2	(SRC_GTM_GTM0_DPLL2)

/** \brief  16F4, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL20 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396F4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL20.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL20.
*/
#define	SRC_GTMDPLL20	(SRC_GTM_GTM0_DPLL20)

/** \brief  16F8, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL21 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396F8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL21.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL21.
*/
#define	SRC_GTMDPLL21	(SRC_GTM_GTM0_DPLL21)

/** \brief  16FC, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL22 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396FCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL22.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL22.
*/
#define	SRC_GTMDPLL22	(SRC_GTM_GTM0_DPLL22)

/** \brief  1700, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL23 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039700u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL23.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL23.
*/
#define	SRC_GTMDPLL23	(SRC_GTM_GTM0_DPLL23)

/** \brief  1704, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL24 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039704u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL24.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL24.
*/
#define	SRC_GTMDPLL24	(SRC_GTM_GTM0_DPLL24)

/** \brief  1708, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL25 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039708u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL25.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL25.
*/
#define	SRC_GTMDPLL25	(SRC_GTM_GTM0_DPLL25)

/** \brief  170C, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL26 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003970Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL26.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL26.
*/
#define	SRC_GTMDPLL26	(SRC_GTM_GTM0_DPLL26)

/** \brief  16B0, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396B0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL3.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL3.
*/
#define	SRC_GTMDPLL3	(SRC_GTM_GTM0_DPLL3)

/** \brief  16B4, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396B4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL4.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL4.
*/
#define	SRC_GTMDPLL4	(SRC_GTM_GTM0_DPLL4)

/** \brief  16B8, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396B8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL5.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL5.
*/
#define	SRC_GTMDPLL5	(SRC_GTM_GTM0_DPLL5)

/** \brief  16BC, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396BCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL6.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL6.
*/
#define	SRC_GTMDPLL6	(SRC_GTM_GTM0_DPLL6)

/** \brief  16C0, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396C0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL7.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL7.
*/
#define	SRC_GTMDPLL7	(SRC_GTM_GTM0_DPLL7)

/** \brief  16C4, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL8 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396C4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL8.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL8.
*/
#define	SRC_GTMDPLL8	(SRC_GTM_GTM0_DPLL8)

/** \brief  16C8, GTM DPLL Service Request */
#define SRC_GTM_GTM0_DPLL9 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00396C8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_DPLL9.
* To use register names with standard convension, please use SRC_GTM_GTM0_DPLL9.
*/
#define	SRC_GTMDPLL9	(SRC_GTM_GTM0_DPLL9)

/** \brief  1770, GTM Error Service Request */
#define SRC_GTM_GTM0_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039770u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_ERR.
* To use register names with standard convension, please use SRC_GTM_GTM0_ERR.
*/
#define	SRC_GTMERR	(SRC_GTM_GTM0_ERR)

/** \brief  1980, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039980u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_0.
*/
#define	SRC_GTMMCS00	(SRC_GTM_GTM0_MCS0_0)

/** \brief  1984, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039984u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_1.
*/
#define	SRC_GTMMCS01	(SRC_GTM_GTM0_MCS0_1)

/** \brief  1988, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039988u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_2.
*/
#define	SRC_GTMMCS02	(SRC_GTM_GTM0_MCS0_2)

/** \brief  198C, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003998Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_3.
*/
#define	SRC_GTMMCS03	(SRC_GTM_GTM0_MCS0_3)

/** \brief  1990, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039990u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_4.
*/
#define	SRC_GTMMCS04	(SRC_GTM_GTM0_MCS0_4)

/** \brief  1994, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039994u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_5.
*/
#define	SRC_GTMMCS05	(SRC_GTM_GTM0_MCS0_5)

/** \brief  1998, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039998u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_6.
*/
#define	SRC_GTMMCS06	(SRC_GTM_GTM0_MCS0_6)

/** \brief  199C, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS0_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003999Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS0_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS0_7.
*/
#define	SRC_GTMMCS07	(SRC_GTM_GTM0_MCS0_7)

/** \brief  19A0, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399A0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_0.
*/
#define	SRC_GTMMCS10	(SRC_GTM_GTM0_MCS1_0)

/** \brief  19A4, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399A4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_1.
*/
#define	SRC_GTMMCS11	(SRC_GTM_GTM0_MCS1_1)

/** \brief  19A8, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399A8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_2.
*/
#define	SRC_GTMMCS12	(SRC_GTM_GTM0_MCS1_2)

/** \brief  19AC, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399ACu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_3.
*/
#define	SRC_GTMMCS13	(SRC_GTM_GTM0_MCS1_3)

/** \brief  19B0, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399B0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_4.
*/
#define	SRC_GTMMCS14	(SRC_GTM_GTM0_MCS1_4)

/** \brief  19B4, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399B4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_5.
*/
#define	SRC_GTMMCS15	(SRC_GTM_GTM0_MCS1_5)

/** \brief  19B8, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399B8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_6.
*/
#define	SRC_GTMMCS16	(SRC_GTM_GTM0_MCS1_6)

/** \brief  19BC, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS1_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399BCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS1_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS1_7.
*/
#define	SRC_GTMMCS17	(SRC_GTM_GTM0_MCS1_7)

/** \brief  19C0, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399C0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_0.
*/
#define	SRC_GTMMCS20	(SRC_GTM_GTM0_MCS2_0)

/** \brief  19C4, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399C4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_1.
*/
#define	SRC_GTMMCS21	(SRC_GTM_GTM0_MCS2_1)

/** \brief  19C8, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399C8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_2.
*/
#define	SRC_GTMMCS22	(SRC_GTM_GTM0_MCS2_2)

/** \brief  19CC, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399CCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_3.
*/
#define	SRC_GTMMCS23	(SRC_GTM_GTM0_MCS2_3)

/** \brief  19D0, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399D0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_4.
*/
#define	SRC_GTMMCS24	(SRC_GTM_GTM0_MCS2_4)

/** \brief  19D4, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399D4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_5.
*/
#define	SRC_GTMMCS25	(SRC_GTM_GTM0_MCS2_5)

/** \brief  19D8, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399D8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_6.
*/
#define	SRC_GTMMCS26	(SRC_GTM_GTM0_MCS2_6)

/** \brief  19DC, GTM MCS Shared Service Request */
#define SRC_GTM_GTM0_MCS2_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00399DCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCS2_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCS2_7.
*/
#define	SRC_GTMMCS27	(SRC_GTM_GTM0_MCS2_7)

/** \brief  1F00, GTM Multi Channel Sequencer 0 Service Request */
#define SRC_GTM_GTM0_MCSW00 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039F00u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCSW00.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCSW00.
*/
#define	SRC_GTMMCSW00	(SRC_GTM_GTM0_MCSW00)

/** \brief  1F04, GTM Multi Channel Sequencer 0 Service Request */
#define SRC_GTM_GTM0_MCSW01 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039F04u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCSW01.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCSW01.
*/
#define	SRC_GTMMCSW01	(SRC_GTM_GTM0_MCSW01)

/** \brief  1F08, GTM Multi Channel Sequencer 0 Service Request */
#define SRC_GTM_GTM0_MCSW02 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039F08u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCSW02.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCSW02.
*/
#define	SRC_GTMMCSW02	(SRC_GTM_GTM0_MCSW02)

/** \brief  1F40, GTM Multi Channel Sequencer 1 Service Request */
#define SRC_GTM_GTM0_MCSW10 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039F40u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCSW10.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCSW10.
*/
#define	SRC_GTMMCSW10	(SRC_GTM_GTM0_MCSW10)

/** \brief  1F44, GTM Multi Channel Sequencer 1 Service Request */
#define SRC_GTM_GTM0_MCSW11 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039F44u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCSW11.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCSW11.
*/
#define	SRC_GTMMCSW11	(SRC_GTM_GTM0_MCSW11)

/** \brief  1F48, GTM Multi Channel Sequencer 1 Service Request */
#define SRC_GTM_GTM0_MCSW12 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039F48u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_MCSW12.
* To use register names with standard convension, please use SRC_GTM_GTM0_MCSW12.
*/
#define	SRC_GTMMCSW12	(SRC_GTM_GTM0_MCSW12)

/** \brief  162C, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003962Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_0.
*/
#define	SRC_GTMPSM00	(SRC_GTM_GTM0_PSM0_0)

/** \brief  1630, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039630u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_1.
*/
#define	SRC_GTMPSM01	(SRC_GTM_GTM0_PSM0_1)

/** \brief  1634, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039634u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_2.
*/
#define	SRC_GTMPSM02	(SRC_GTM_GTM0_PSM0_2)

/** \brief  1638, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039638u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_3.
*/
#define	SRC_GTMPSM03	(SRC_GTM_GTM0_PSM0_3)

/** \brief  163C, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003963Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_4.
*/
#define	SRC_GTMPSM04	(SRC_GTM_GTM0_PSM0_4)

/** \brief  1640, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039640u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_5.
*/
#define	SRC_GTMPSM05	(SRC_GTM_GTM0_PSM0_5)

/** \brief  1644, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039644u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_6.
*/
#define	SRC_GTMPSM06	(SRC_GTM_GTM0_PSM0_6)

/** \brief  1648, GTM PSM Shared Service Request */
#define SRC_GTM_GTM0_PSM0_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039648u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_PSM0_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_PSM0_7.
*/
#define	SRC_GTMPSM07	(SRC_GTM_GTM0_PSM0_7)

/** \brief  161C, GTM SPE Shared Service Request */
#define SRC_GTM_GTM0_SPEIRQ0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003961Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_SPEIRQ0.
* To use register names with standard convension, please use SRC_GTM_GTM0_SPEIRQ0.
*/
#define	SRC_GTMSPE0IRQ	(SRC_GTM_GTM0_SPEIRQ0)

/** \brief  1620, GTM SPE Shared Service Request */
#define SRC_GTM_GTM0_SPEIRQ1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039620u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_SPEIRQ1.
* To use register names with standard convension, please use SRC_GTM_GTM0_SPEIRQ1.
*/
#define	SRC_GTMSPE1IRQ	(SRC_GTM_GTM0_SPEIRQ1)

/** \brief  1780, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039780u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_0.
*/
#define	SRC_GTMTIM00	(SRC_GTM_GTM0_TIM0_0)

/** \brief  1784, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039784u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_1.
*/
#define	SRC_GTMTIM01	(SRC_GTM_GTM0_TIM0_1)

/** \brief  1788, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039788u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_2.
*/
#define	SRC_GTMTIM02	(SRC_GTM_GTM0_TIM0_2)

/** \brief  178C, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003978Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_3.
*/
#define	SRC_GTMTIM03	(SRC_GTM_GTM0_TIM0_3)

/** \brief  1790, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039790u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_4.
*/
#define	SRC_GTMTIM04	(SRC_GTM_GTM0_TIM0_4)

/** \brief  1794, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039794u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_5.
*/
#define	SRC_GTMTIM05	(SRC_GTM_GTM0_TIM0_5)

/** \brief  1798, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039798u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_6.
*/
#define	SRC_GTMTIM06	(SRC_GTM_GTM0_TIM0_6)

/** \brief  179C, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM0_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003979Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM0_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM0_7.
*/
#define	SRC_GTMTIM07	(SRC_GTM_GTM0_TIM0_7)

/** \brief  17A0, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397A0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_0.
*/
#define	SRC_GTMTIM10	(SRC_GTM_GTM0_TIM1_0)

/** \brief  17A4, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397A4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_1.
*/
#define	SRC_GTMTIM11	(SRC_GTM_GTM0_TIM1_1)

/** \brief  17A8, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397A8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_2.
*/
#define	SRC_GTMTIM12	(SRC_GTM_GTM0_TIM1_2)

/** \brief  17AC, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397ACu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_3.
*/
#define	SRC_GTMTIM13	(SRC_GTM_GTM0_TIM1_3)

/** \brief  17B0, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397B0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_4.
*/
#define	SRC_GTMTIM14	(SRC_GTM_GTM0_TIM1_4)

/** \brief  17B4, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397B4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_5.
*/
#define	SRC_GTMTIM15	(SRC_GTM_GTM0_TIM1_5)

/** \brief  17B8, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397B8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_6.
*/
#define	SRC_GTMTIM16	(SRC_GTM_GTM0_TIM1_6)

/** \brief  17BC, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM1_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397BCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM1_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM1_7.
*/
#define	SRC_GTMTIM17	(SRC_GTM_GTM0_TIM1_7)

/** \brief  17C0, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397C0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_0.
*/
#define	SRC_GTMTIM20	(SRC_GTM_GTM0_TIM2_0)

/** \brief  17C4, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397C4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_1.
*/
#define	SRC_GTMTIM21	(SRC_GTM_GTM0_TIM2_1)

/** \brief  17C8, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397C8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_2.
*/
#define	SRC_GTMTIM22	(SRC_GTM_GTM0_TIM2_2)

/** \brief  17CC, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397CCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_3.
*/
#define	SRC_GTMTIM23	(SRC_GTM_GTM0_TIM2_3)

/** \brief  17D0, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397D0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_4.
*/
#define	SRC_GTMTIM24	(SRC_GTM_GTM0_TIM2_4)

/** \brief  17D4, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397D4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_5.
*/
#define	SRC_GTMTIM25	(SRC_GTM_GTM0_TIM2_5)

/** \brief  17D8, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397D8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_6.
*/
#define	SRC_GTMTIM26	(SRC_GTM_GTM0_TIM2_6)

/** \brief  17DC, GTM TIM Shared Service Request */
#define SRC_GTM_GTM0_TIM2_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00397DCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TIM2_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_TIM2_7.
*/
#define	SRC_GTMTIM27	(SRC_GTM_GTM0_TIM2_7)

/** \brief  1B80, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B80u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_0.
*/
#define	SRC_GTMTOM00	(SRC_GTM_GTM0_TOM0_0)

/** \brief  1B84, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B84u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_1.
*/
#define	SRC_GTMTOM01	(SRC_GTM_GTM0_TOM0_1)

/** \brief  1B88, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B88u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_2.
*/
#define	SRC_GTMTOM02	(SRC_GTM_GTM0_TOM0_2)

/** \brief  1B8C, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B8Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_3.
*/
#define	SRC_GTMTOM03	(SRC_GTM_GTM0_TOM0_3)

/** \brief  1B90, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B90u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_4.
*/
#define	SRC_GTMTOM04	(SRC_GTM_GTM0_TOM0_4)

/** \brief  1B94, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B94u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_5.
*/
#define	SRC_GTMTOM05	(SRC_GTM_GTM0_TOM0_5)

/** \brief  1B98, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B98u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_6.
*/
#define	SRC_GTMTOM06	(SRC_GTM_GTM0_TOM0_6)

/** \brief  1B9C, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM0_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039B9Cu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM0_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM0_7.
*/
#define	SRC_GTMTOM07	(SRC_GTM_GTM0_TOM0_7)

/** \brief  1BA0, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BA0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_0.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_0.
*/
#define	SRC_GTMTOM10	(SRC_GTM_GTM0_TOM1_0)

/** \brief  1BA4, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BA4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_1.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_1.
*/
#define	SRC_GTMTOM11	(SRC_GTM_GTM0_TOM1_1)

/** \brief  1BA8, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BA8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_2.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_2.
*/
#define	SRC_GTMTOM12	(SRC_GTM_GTM0_TOM1_2)

/** \brief  1BAC, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BACu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_3.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_3.
*/
#define	SRC_GTMTOM13	(SRC_GTM_GTM0_TOM1_3)

/** \brief  1BB0, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BB0u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_4.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_4.
*/
#define	SRC_GTMTOM14	(SRC_GTM_GTM0_TOM1_4)

/** \brief  1BB4, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BB4u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_5.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_5.
*/
#define	SRC_GTMTOM15	(SRC_GTM_GTM0_TOM1_5)

/** \brief  1BB8, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BB8u)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_6.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_6.
*/
#define	SRC_GTMTOM16	(SRC_GTM_GTM0_TOM1_6)

/** \brief  1BBC, GTM TOM Shared Service Request */
#define SRC_GTM_GTM0_TOM1_7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0039BBCu)

/** Alias (User Manual Name) for SRC_GTM_GTM0_TOM1_7.
* To use register names with standard convension, please use SRC_GTM_GTM0_TOM1_7.
*/
#define	SRC_GTMTOM17	(SRC_GTM_GTM0_TOM1_7)

/** \brief  290, HSCT Service Request */
#define SRC_HSCT_HSCT0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038290u)

/** Alias (User Manual Name) for SRC_HSCT_HSCT0_SR.
* To use register names with standard convension, please use SRC_HSCT_HSCT0_SR.
*/
#define	SRC_HSCT	(SRC_HSCT_HSCT0_SR)

/** \brief  2E0, Exception Service Request */
#define SRC_HSSL_EXI /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382E0u)

/** Alias (User Manual Name) for SRC_HSSL_EXI.
* To use register names with standard convension, please use SRC_HSSL_EXI.
*/
#define	SRC_HSSLEXI	(SRC_HSSL_EXI)

/** \brief  2A0, Channel OK Service Request m */
#define SRC_HSSL_HSSL0_COK /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382A0u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL0_COK.
* To use register names with standard convension, please use SRC_HSSL_HSSL0_COK.
*/
#define	SRC_HSSLCOK0	(SRC_HSSL_HSSL0_COK)

/** \brief  2A8, Channel Error ServiceRequest m */
#define SRC_HSSL_HSSL0_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382A8u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL0_ERR.
* To use register names with standard convension, please use SRC_HSSL_HSSL0_ERR.
*/
#define	SRC_HSSLERR0	(SRC_HSSL_HSSL0_ERR)

/** \brief  2A4, Channel Read Data Service Request m */
#define SRC_HSSL_HSSL0_RDI /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382A4u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL0_RDI.
* To use register names with standard convension, please use SRC_HSSL_HSSL0_RDI.
*/
#define	SRC_HSSLRDI0	(SRC_HSSL_HSSL0_RDI)

/** \brief  2AC, Channel Trigger Service Request m */
#define SRC_HSSL_HSSL0_TRG /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382ACu)

/** Alias (User Manual Name) for SRC_HSSL_HSSL0_TRG.
* To use register names with standard convension, please use SRC_HSSL_HSSL0_TRG.
*/
#define	SRC_HSSLTRG0	(SRC_HSSL_HSSL0_TRG)

/** \brief  2B0, Channel OK Service Request m */
#define SRC_HSSL_HSSL1_COK /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382B0u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL1_COK.
* To use register names with standard convension, please use SRC_HSSL_HSSL1_COK.
*/
#define	SRC_HSSLCOK1	(SRC_HSSL_HSSL1_COK)

/** \brief  2B8, Channel Error ServiceRequest m */
#define SRC_HSSL_HSSL1_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382B8u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL1_ERR.
* To use register names with standard convension, please use SRC_HSSL_HSSL1_ERR.
*/
#define	SRC_HSSLERR1	(SRC_HSSL_HSSL1_ERR)

/** \brief  2B4, Channel Read Data Service Request m */
#define SRC_HSSL_HSSL1_RDI /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382B4u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL1_RDI.
* To use register names with standard convension, please use SRC_HSSL_HSSL1_RDI.
*/
#define	SRC_HSSLRDI1	(SRC_HSSL_HSSL1_RDI)

/** \brief  2BC, Channel Trigger Service Request m */
#define SRC_HSSL_HSSL1_TRG /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382BCu)

/** Alias (User Manual Name) for SRC_HSSL_HSSL1_TRG.
* To use register names with standard convension, please use SRC_HSSL_HSSL1_TRG.
*/
#define	SRC_HSSLTRG1	(SRC_HSSL_HSSL1_TRG)

/** \brief  2C0, Channel OK Service Request m */
#define SRC_HSSL_HSSL2_COK /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382C0u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL2_COK.
* To use register names with standard convension, please use SRC_HSSL_HSSL2_COK.
*/
#define	SRC_HSSLCOK2	(SRC_HSSL_HSSL2_COK)

/** \brief  2C8, Channel Error ServiceRequest m */
#define SRC_HSSL_HSSL2_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382C8u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL2_ERR.
* To use register names with standard convension, please use SRC_HSSL_HSSL2_ERR.
*/
#define	SRC_HSSLERR2	(SRC_HSSL_HSSL2_ERR)

/** \brief  2C4, Channel Read Data Service Request m */
#define SRC_HSSL_HSSL2_RDI /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382C4u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL2_RDI.
* To use register names with standard convension, please use SRC_HSSL_HSSL2_RDI.
*/
#define	SRC_HSSLRDI2	(SRC_HSSL_HSSL2_RDI)

/** \brief  2CC, Channel Trigger Service Request m */
#define SRC_HSSL_HSSL2_TRG /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382CCu)

/** Alias (User Manual Name) for SRC_HSSL_HSSL2_TRG.
* To use register names with standard convension, please use SRC_HSSL_HSSL2_TRG.
*/
#define	SRC_HSSLTRG2	(SRC_HSSL_HSSL2_TRG)

/** \brief  2D0, Channel OK Service Request m */
#define SRC_HSSL_HSSL3_COK /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382D0u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL3_COK.
* To use register names with standard convension, please use SRC_HSSL_HSSL3_COK.
*/
#define	SRC_HSSLCOK3	(SRC_HSSL_HSSL3_COK)

/** \brief  2D8, Channel Error ServiceRequest m */
#define SRC_HSSL_HSSL3_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382D8u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL3_ERR.
* To use register names with standard convension, please use SRC_HSSL_HSSL3_ERR.
*/
#define	SRC_HSSLERR3	(SRC_HSSL_HSSL3_ERR)

/** \brief  2D4, Channel Read Data Service Request m */
#define SRC_HSSL_HSSL3_RDI /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382D4u)

/** Alias (User Manual Name) for SRC_HSSL_HSSL3_RDI.
* To use register names with standard convension, please use SRC_HSSL_HSSL3_RDI.
*/
#define	SRC_HSSLRDI3	(SRC_HSSL_HSSL3_RDI)

/** \brief  2DC, Channel Trigger Service Request m */
#define SRC_HSSL_HSSL3_TRG /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00382DCu)

/** Alias (User Manual Name) for SRC_HSSL_HSSL3_TRG.
* To use register names with standard convension, please use SRC_HSSL_HSSL3_TRG.
*/
#define	SRC_HSSLTRG3	(SRC_HSSL_HSSL3_TRG)

/** \brief  300, I2C Burst Data Transfer Request */
#define SRC_I2C_I2C0_BREQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038300u)

/** Alias (User Manual Name) for SRC_I2C_I2C0_BREQ.
* To use register names with standard convension, please use SRC_I2C_I2C0_BREQ.
*/
#define	SRC_I2C0BREQ	(SRC_I2C_I2C0_BREQ)

/** \brief  310, I2C Error Service Request */
#define SRC_I2C_I2C0_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038310u)

/** Alias (User Manual Name) for SRC_I2C_I2C0_ERR.
* To use register names with standard convension, please use SRC_I2C_I2C0_ERR.
*/
#define	SRC_I2C0ERR	(SRC_I2C_I2C0_ERR)

/** \brief  304, I2C Last Burst Data Transfer Service Request */
#define SRC_I2C_I2C0_LBREQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038304u)

/** Alias (User Manual Name) for SRC_I2C_I2C0_LBREQ.
* To use register names with standard convension, please use SRC_I2C_I2C0_LBREQ.
*/
#define	SRC_I2C0LBREQ	(SRC_I2C_I2C0_LBREQ)

/** \brief  30C, I2C Last Single Data Transfer Service Request */
#define SRC_I2C_I2C0_LSREQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003830Cu)

/** Alias (User Manual Name) for SRC_I2C_I2C0_LSREQ.
* To use register names with standard convension, please use SRC_I2C_I2C0_LSREQ.
*/
#define	SRC_I2C0LSREQ	(SRC_I2C_I2C0_LSREQ)

/** \brief  314, I2C Kernel Service Request */
#define SRC_I2C_I2C0_P /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038314u)

/** Alias (User Manual Name) for SRC_I2C_I2C0_P.
* To use register names with standard convension, please use SRC_I2C_I2C0_P.
*/
#define	SRC_I2C0P	(SRC_I2C_I2C0_P)

/** \brief  308, I2C Single Data Transfer Service Request */
#define SRC_I2C_I2C0_SREQ /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038308u)

/** Alias (User Manual Name) for SRC_I2C_I2C0_SREQ.
* To use register names with standard convension, please use SRC_I2C_I2C0_SREQ.
*/
#define	SRC_I2C0SREQ	(SRC_I2C_I2C0_SREQ)

/** \brief  DE0, LMU Service Request */
#define SRC_LMU_LMU0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DE0u)

/** Alias (User Manual Name) for SRC_LMU_LMU0_SR.
* To use register names with standard convension, please use SRC_LMU_LMU0_SR.
*/
#define	SRC_LMU	(SRC_LMU_LMU0_SR)

/** \brief  3E0, MSC Service Request 0 */
#define SRC_MSC_MSC0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383E0u)

/** Alias (User Manual Name) for SRC_MSC_MSC0_SR0.
* To use register names with standard convension, please use SRC_MSC_MSC0_SR0.
*/
#define	SRC_MSC0SR0	(SRC_MSC_MSC0_SR0)

/** \brief  3E4, MSC Service Request 1 */
#define SRC_MSC_MSC0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383E4u)

/** Alias (User Manual Name) for SRC_MSC_MSC0_SR1.
* To use register names with standard convension, please use SRC_MSC_MSC0_SR1.
*/
#define	SRC_MSC0SR1	(SRC_MSC_MSC0_SR1)

/** \brief  3E8, MSC Service Request 2 */
#define SRC_MSC_MSC0_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383E8u)

/** Alias (User Manual Name) for SRC_MSC_MSC0_SR2.
* To use register names with standard convension, please use SRC_MSC_MSC0_SR2.
*/
#define	SRC_MSC0SR2	(SRC_MSC_MSC0_SR2)

/** \brief  3EC, MSC Service Request 3 */
#define SRC_MSC_MSC0_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383ECu)

/** Alias (User Manual Name) for SRC_MSC_MSC0_SR3.
* To use register names with standard convension, please use SRC_MSC_MSC0_SR3.
*/
#define	SRC_MSC0SR3	(SRC_MSC_MSC0_SR3)

/** \brief  3F0, MSC Service Request 4 */
#define SRC_MSC_MSC0_SR4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383F0u)

/** Alias (User Manual Name) for SRC_MSC_MSC0_SR4.
* To use register names with standard convension, please use SRC_MSC_MSC0_SR4.
*/
#define	SRC_MSC0SR4	(SRC_MSC_MSC0_SR4)

/** \brief  3F4, MSC Service Request 0 */
#define SRC_MSC_MSC1_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383F4u)

/** Alias (User Manual Name) for SRC_MSC_MSC1_SR0.
* To use register names with standard convension, please use SRC_MSC_MSC1_SR0.
*/
#define	SRC_MSC1SR0	(SRC_MSC_MSC1_SR0)

/** \brief  3F8, MSC Service Request 1 */
#define SRC_MSC_MSC1_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383F8u)

/** Alias (User Manual Name) for SRC_MSC_MSC1_SR1.
* To use register names with standard convension, please use SRC_MSC_MSC1_SR1.
*/
#define	SRC_MSC1SR1	(SRC_MSC_MSC1_SR1)

/** \brief  3FC, MSC Service Request 2 */
#define SRC_MSC_MSC1_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00383FCu)

/** Alias (User Manual Name) for SRC_MSC_MSC1_SR2.
* To use register names with standard convension, please use SRC_MSC_MSC1_SR2.
*/
#define	SRC_MSC1SR2	(SRC_MSC_MSC1_SR2)

/** \brief  400, MSC Service Request 3 */
#define SRC_MSC_MSC1_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038400u)

/** Alias (User Manual Name) for SRC_MSC_MSC1_SR3.
* To use register names with standard convension, please use SRC_MSC_MSC1_SR3.
*/
#define	SRC_MSC1SR3	(SRC_MSC_MSC1_SR3)

/** \brief  404, MSC Service Request 4 */
#define SRC_MSC_MSC1_SR4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038404u)

/** Alias (User Manual Name) for SRC_MSC_MSC1_SR4.
* To use register names with standard convension, please use SRC_MSC_MSC1_SR4.
*/
#define	SRC_MSC1SR4	(SRC_MSC_MSC1_SR4)

/** \brief  C30, PMU  Service Request */
#define SRC_PMU_PMU0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038C30u)

/** Alias (User Manual Name) for SRC_PMU_PMU0_SR.
* To use register names with standard convension, please use SRC_PMU_PMU0_SR.
*/
#define	SRC_PMU00	(SRC_PMU_PMU0_SR)

/** \brief  C34, PMU  Service Request */
#define SRC_PMU_PMU1_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038C34u)

/** Alias (User Manual Name) for SRC_PMU_PMU1_SR.
* To use register names with standard convension, please use SRC_PMU_PMU1_SR.
*/
#define	SRC_PMU01	(SRC_PMU_PMU1_SR)

/** \brief  D30, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D30u)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR0.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR0.
*/
#define	SRC_PSI50	(SRC_PSI5_PSI50_SR0)

/** \brief  D34, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D34u)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR1.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR1.
*/
#define	SRC_PSI51	(SRC_PSI5_PSI50_SR1)

/** \brief  D38, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D38u)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR2.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR2.
*/
#define	SRC_PSI52	(SRC_PSI5_PSI50_SR2)

/** \brief  D3C, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D3Cu)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR3.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR3.
*/
#define	SRC_PSI53	(SRC_PSI5_PSI50_SR3)

/** \brief  D40, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D40u)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR4.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR4.
*/
#define	SRC_PSI54	(SRC_PSI5_PSI50_SR4)

/** \brief  D44, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D44u)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR5.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR5.
*/
#define	SRC_PSI55	(SRC_PSI5_PSI50_SR5)

/** \brief  D48, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D48u)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR6.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR6.
*/
#define	SRC_PSI56	(SRC_PSI5_PSI50_SR6)

/** \brief  D4C, PSI5 Service Request */
#define SRC_PSI5_PSI50_SR7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D4Cu)

/** Alias (User Manual Name) for SRC_PSI5_PSI50_SR7.
* To use register names with standard convension, please use SRC_PSI5_PSI50_SR7.
*/
#define	SRC_PSI57	(SRC_PSI5_PSI50_SR7)

/** \brief  DF0, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DF0u)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR0.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR0.
*/
#define	SRC_PSI5S0	(SRC_PSI5S_PSI5S0_SR0)

/** \brief  DF4, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DF4u)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR1.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR1.
*/
#define	SRC_PSI5S1	(SRC_PSI5S_PSI5S0_SR1)

/** \brief  DF8, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DF8u)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR2.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR2.
*/
#define	SRC_PSI5S2	(SRC_PSI5S_PSI5S0_SR2)

/** \brief  DFC, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038DFCu)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR3.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR3.
*/
#define	SRC_PSI5S3	(SRC_PSI5S_PSI5S0_SR3)

/** \brief  E00, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038E00u)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR4.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR4.
*/
#define	SRC_PSI5S4	(SRC_PSI5S_PSI5S0_SR4)

/** \brief  E04, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038E04u)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR5.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR5.
*/
#define	SRC_PSI5S5	(SRC_PSI5S_PSI5S0_SR5)

/** \brief  E08, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR6 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038E08u)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR6.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR6.
*/
#define	SRC_PSI5S6	(SRC_PSI5S_PSI5S0_SR6)

/** \brief  E0C, PSI5-S Service Request */
#define SRC_PSI5S_PSI5S0_SR7 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038E0Cu)

/** Alias (User Manual Name) for SRC_PSI5S_PSI5S0_SR7.
* To use register names with standard convension, please use SRC_PSI5S_PSI5S0_SR7.
*/
#define	SRC_PSI5S7	(SRC_PSI5S_PSI5S0_SR7)

/** \brief  198, QSPI Error Service Request */
#define SRC_QSPI_QSPI0_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038198u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI0_ERR.
* To use register names with standard convension, please use SRC_QSPI_QSPI0_ERR.
*/
#define	SRC_QSPI0ERR	(SRC_QSPI_QSPI0_ERR)

/** \brief  1A0, QSPI High Speed Capture Service Request */
#define SRC_QSPI_QSPI0_HC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381A0u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI0_HC.
* To use register names with standard convension, please use SRC_QSPI_QSPI0_HC.
*/
#define	SRC_RESERVED10	(SRC_QSPI_QSPI0_HC)

/** \brief  19C, QSPI Phase Transition Service Request */
#define SRC_QSPI_QSPI0_PT /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003819Cu)

/** Alias (User Manual Name) for SRC_QSPI_QSPI0_PT.
* To use register names with standard convension, please use SRC_QSPI_QSPI0_PT.
*/
#define	SRC_QSPI0PT	(SRC_QSPI_QSPI0_PT)

/** \brief  194, QSPI Receive Service Request */
#define SRC_QSPI_QSPI0_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038194u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI0_RX.
* To use register names with standard convension, please use SRC_QSPI_QSPI0_RX.
*/
#define	SRC_QSPI0RX	(SRC_QSPI_QSPI0_RX)

/** \brief  190, QSPI Transmit Service Request */
#define SRC_QSPI_QSPI0_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038190u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI0_TX.
* To use register names with standard convension, please use SRC_QSPI_QSPI0_TX.
*/
#define	SRC_QSPI0TX	(SRC_QSPI_QSPI0_TX)

/** \brief  1A4, QSPI User Defined Service Request */
#define SRC_QSPI_QSPI0_U /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381A4u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI0_U.
* To use register names with standard convension, please use SRC_QSPI_QSPI0_U.
*/
#define	SRC_QSPI0U	(SRC_QSPI_QSPI0_U)

/** \brief  1B0, QSPI Error Service Request */
#define SRC_QSPI_QSPI1_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381B0u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI1_ERR.
* To use register names with standard convension, please use SRC_QSPI_QSPI1_ERR.
*/
#define	SRC_QSPI1ERR	(SRC_QSPI_QSPI1_ERR)

/** \brief  1B8, QSPI High Speed Capture Service Request */
#define SRC_QSPI_QSPI1_HC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381B8u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI1_HC.
* To use register names with standard convension, please use SRC_QSPI_QSPI1_HC.
*/
#define	SRC_RESERVED11	(SRC_QSPI_QSPI1_HC)

/** \brief  1B4, QSPI Phase Transition Service Request */
#define SRC_QSPI_QSPI1_PT /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381B4u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI1_PT.
* To use register names with standard convension, please use SRC_QSPI_QSPI1_PT.
*/
#define	SRC_QSPI1PT	(SRC_QSPI_QSPI1_PT)

/** \brief  1AC, QSPI Receive Service Request */
#define SRC_QSPI_QSPI1_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381ACu)

/** Alias (User Manual Name) for SRC_QSPI_QSPI1_RX.
* To use register names with standard convension, please use SRC_QSPI_QSPI1_RX.
*/
#define	SRC_QSPI1RX	(SRC_QSPI_QSPI1_RX)

/** \brief  1A8, QSPI Transmit Service Request */
#define SRC_QSPI_QSPI1_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381A8u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI1_TX.
* To use register names with standard convension, please use SRC_QSPI_QSPI1_TX.
*/
#define	SRC_QSPI1TX	(SRC_QSPI_QSPI1_TX)

/** \brief  1BC, QSPI User Defined Service Request */
#define SRC_QSPI_QSPI1_U /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381BCu)

/** Alias (User Manual Name) for SRC_QSPI_QSPI1_U.
* To use register names with standard convension, please use SRC_QSPI_QSPI1_U.
*/
#define	SRC_QSPI1U	(SRC_QSPI_QSPI1_U)

/** \brief  1C8, QSPI Error Service Request */
#define SRC_QSPI_QSPI2_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381C8u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI2_ERR.
* To use register names with standard convension, please use SRC_QSPI_QSPI2_ERR.
*/
#define	SRC_QSPI2ERR	(SRC_QSPI_QSPI2_ERR)

/** \brief  1D0, QSPI High Speed Capture Service Request */
#define SRC_QSPI_QSPI2_HC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381D0u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI2_HC.
* To use register names with standard convension, please use SRC_QSPI_QSPI2_HC.
*/
#define	SRC_QSPI2HC	(SRC_QSPI_QSPI2_HC)

/** \brief  1CC, QSPI Phase Transition Service Request */
#define SRC_QSPI_QSPI2_PT /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381CCu)

/** Alias (User Manual Name) for SRC_QSPI_QSPI2_PT.
* To use register names with standard convension, please use SRC_QSPI_QSPI2_PT.
*/
#define	SRC_QSPI2PT	(SRC_QSPI_QSPI2_PT)

/** \brief  1C4, QSPI Receive Service Request */
#define SRC_QSPI_QSPI2_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381C4u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI2_RX.
* To use register names with standard convension, please use SRC_QSPI_QSPI2_RX.
*/
#define	SRC_QSPI2RX	(SRC_QSPI_QSPI2_RX)

/** \brief  1C0, QSPI Transmit Service Request */
#define SRC_QSPI_QSPI2_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381C0u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI2_TX.
* To use register names with standard convension, please use SRC_QSPI_QSPI2_TX.
*/
#define	SRC_QSPI2TX	(SRC_QSPI_QSPI2_TX)

/** \brief  1D4, QSPI User Defined Service Request */
#define SRC_QSPI_QSPI2_U /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381D4u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI2_U.
* To use register names with standard convension, please use SRC_QSPI_QSPI2_U.
*/
#define	SRC_QSPI2U	(SRC_QSPI_QSPI2_U)

/** \brief  1E0, QSPI Error Service Request */
#define SRC_QSPI_QSPI3_ERR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381E0u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI3_ERR.
* To use register names with standard convension, please use SRC_QSPI_QSPI3_ERR.
*/
#define	SRC_QSPI3ERR	(SRC_QSPI_QSPI3_ERR)

/** \brief  1E8, QSPI High Speed Capture Service Request */
#define SRC_QSPI_QSPI3_HC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381E8u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI3_HC.
* To use register names with standard convension, please use SRC_QSPI_QSPI3_HC.
*/
#define	SRC_QSPI3HC	(SRC_QSPI_QSPI3_HC)

/** \brief  1E4, QSPI Phase Transition Service Request */
#define SRC_QSPI_QSPI3_PT /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381E4u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI3_PT.
* To use register names with standard convension, please use SRC_QSPI_QSPI3_PT.
*/
#define	SRC_QSPI3PT	(SRC_QSPI_QSPI3_PT)

/** \brief  1DC, QSPI Receive Service Request */
#define SRC_QSPI_QSPI3_RX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381DCu)

/** Alias (User Manual Name) for SRC_QSPI_QSPI3_RX.
* To use register names with standard convension, please use SRC_QSPI_QSPI3_RX.
*/
#define	SRC_QSPI3RX	(SRC_QSPI_QSPI3_RX)

/** \brief  1D8, QSPI Transmit Service Request */
#define SRC_QSPI_QSPI3_TX /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381D8u)

/** Alias (User Manual Name) for SRC_QSPI_QSPI3_TX.
* To use register names with standard convension, please use SRC_QSPI_QSPI3_TX.
*/
#define	SRC_QSPI3TX	(SRC_QSPI_QSPI3_TX)

/** \brief  1EC, QSPI User Defined Service Request */
#define SRC_QSPI_QSPI3_U /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00381ECu)

/** Alias (User Manual Name) for SRC_QSPI_QSPI3_U.
* To use register names with standard convension, please use SRC_QSPI_QSPI3_U.
*/
#define	SRC_QSPI3U	(SRC_QSPI_QSPI3_U)

/** \brief  D00, Stand By Controller Service Request */
#define SRC_SCR_SCR0_SR /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D00u)

/** Alias (User Manual Name) for SRC_SCR_SCR0_SR.
* To use register names with standard convension, please use SRC_SCR_SCR0_SR.
*/
#define	SRC_SCR	(SRC_SCR_SCR0_SR)

/** \brief  CD0, SCU DTS Busy Service Request */
#define SRC_SCU_SCU_DTS /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038CD0u)

/** Alias (User Manual Name) for SRC_SCU_SCU_DTS.
* To use register names with standard convension, please use SRC_SCU_SCU_DTS.
*/
#define	SRC_SCUDTS	(SRC_SCU_SCU_DTS)

/** \brief  CD4, SCU ERU Service Request */
#define SRC_SCU_SCU_ERU0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038CD4u)

/** Alias (User Manual Name) for SRC_SCU_SCU_ERU0.
* To use register names with standard convension, please use SRC_SCU_SCU_ERU0.
*/
#define	SRC_SCUERU0	(SRC_SCU_SCU_ERU0)

/** \brief  CD8, SCU ERU Service Request */
#define SRC_SCU_SCU_ERU1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038CD8u)

/** Alias (User Manual Name) for SRC_SCU_SCU_ERU1.
* To use register names with standard convension, please use SRC_SCU_SCU_ERU1.
*/
#define	SRC_SCUERU1	(SRC_SCU_SCU_ERU1)

/** \brief  CDC, SCU ERU Service Request */
#define SRC_SCU_SCU_ERU2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038CDCu)

/** Alias (User Manual Name) for SRC_SCU_SCU_ERU2.
* To use register names with standard convension, please use SRC_SCU_SCU_ERU2.
*/
#define	SRC_SCUERU2	(SRC_SCU_SCU_ERU2)

/** \brief  CE0, SCU ERU Service Request */
#define SRC_SCU_SCU_ERU3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038CE0u)

/** Alias (User Manual Name) for SRC_SCU_SCU_ERU3.
* To use register names with standard convension, please use SRC_SCU_SCU_ERU3.
*/
#define	SRC_SCUERU3	(SRC_SCU_SCU_ERU3)

/** \brief  350, SENT TRIG Service Request */
#define SRC_SENT_SENT0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038350u)

/** Alias (User Manual Name) for SRC_SENT_SENT0_SR0.
* To use register names with standard convension, please use SRC_SENT_SENT0_SR0.
*/
#define	SRC_SENT0	(SRC_SENT_SENT0_SR0)

/** \brief  354, SENT TRIG Service Request */
#define SRC_SENT_SENT0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038354u)

/** Alias (User Manual Name) for SRC_SENT_SENT0_SR1.
* To use register names with standard convension, please use SRC_SENT_SENT0_SR1.
*/
#define	SRC_SENT1	(SRC_SENT_SENT0_SR1)

/** \brief  358, SENT TRIG Service Request */
#define SRC_SENT_SENT0_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038358u)

/** Alias (User Manual Name) for SRC_SENT_SENT0_SR2.
* To use register names with standard convension, please use SRC_SENT_SENT0_SR2.
*/
#define	SRC_SENT2	(SRC_SENT_SENT0_SR2)

/** \brief  35C, SENT TRIG Service Request */
#define SRC_SENT_SENT0_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003835Cu)

/** Alias (User Manual Name) for SRC_SENT_SENT0_SR3.
* To use register names with standard convension, please use SRC_SENT_SENT0_SR3.
*/
#define	SRC_SENT3	(SRC_SENT_SENT0_SR3)

/** \brief  360, SENT TRIG Service Request */
#define SRC_SENT_SENT0_SR4 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038360u)

/** Alias (User Manual Name) for SRC_SENT_SENT0_SR4.
* To use register names with standard convension, please use SRC_SENT_SENT0_SR4.
*/
#define	SRC_SENT4	(SRC_SENT_SENT0_SR4)

/** \brief  364, SENT TRIG Service Request */
#define SRC_SENT_SENT0_SR5 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038364u)

/** Alias (User Manual Name) for SRC_SENT_SENT0_SR5.
* To use register names with standard convension, please use SRC_SENT_SENT0_SR5.
*/
#define	SRC_SENT5	(SRC_SENT_SENT0_SR5)

/** \brief  D10, SMU Service Request */
#define SRC_SMU_SMU0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D10u)

/** Alias (User Manual Name) for SRC_SMU_SMU0_SR0.
* To use register names with standard convension, please use SRC_SMU_SMU0_SR0.
*/
#define	SRC_SMU0	(SRC_SMU_SMU0_SR0)

/** \brief  D14, SMU Service Request */
#define SRC_SMU_SMU0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D14u)

/** Alias (User Manual Name) for SRC_SMU_SMU0_SR1.
* To use register names with standard convension, please use SRC_SMU_SMU0_SR1.
*/
#define	SRC_SMU1	(SRC_SMU_SMU0_SR1)

/** \brief  D18, SMU Service Request */
#define SRC_SMU_SMU0_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038D18u)

/** Alias (User Manual Name) for SRC_SMU_SMU0_SR2.
* To use register names with standard convension, please use SRC_SMU_SMU0_SR2.
*/
#define	SRC_SMU2	(SRC_SMU_SMU0_SR2)

/** \brief  490, System Timer  Service Request 0 */
#define SRC_STM_STM0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038490u)

/** Alias (User Manual Name) for SRC_STM_STM0_SR0.
* To use register names with standard convension, please use SRC_STM_STM0_SR0.
*/
#define	SRC_STM0SR0	(SRC_STM_STM0_SR0)

/** \brief  494, System Timer  Service Request 1 */
#define SRC_STM_STM0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038494u)

/** Alias (User Manual Name) for SRC_STM_STM0_SR1.
* To use register names with standard convension, please use SRC_STM_STM0_SR1.
*/
#define	SRC_STM0SR1	(SRC_STM_STM0_SR1)

/** \brief  498, System Timer  Service Request 0 */
#define SRC_STM_STM1_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038498u)

/** Alias (User Manual Name) for SRC_STM_STM1_SR0.
* To use register names with standard convension, please use SRC_STM_STM1_SR0.
*/
#define	SRC_STM1SR0	(SRC_STM_STM1_SR0)

/** \brief  49C, System Timer  Service Request 1 */
#define SRC_STM_STM1_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003849Cu)

/** Alias (User Manual Name) for SRC_STM_STM1_SR1.
* To use register names with standard convension, please use SRC_STM_STM1_SR1.
*/
#define	SRC_STM1SR1	(SRC_STM_STM1_SR1)

/** \brief  AA0, VADC Common Group  Service Request 0 */
#define SRC_VADC_CG0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038AA0u)

/** Alias (User Manual Name) for SRC_VADC_CG0_SR0.
* To use register names with standard convension, please use SRC_VADC_CG0_SR0.
*/
#define	SRC_VADCCG0SR0	(SRC_VADC_CG0_SR0)

/** \brief  AA4, VADC Common Group  Service Request 1 */
#define SRC_VADC_CG0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038AA4u)

/** Alias (User Manual Name) for SRC_VADC_CG0_SR1.
* To use register names with standard convension, please use SRC_VADC_CG0_SR1.
*/
#define	SRC_VADCCG0SR1	(SRC_VADC_CG0_SR1)

/** \brief  AA8, VADC Common Group  Service Request 2 */
#define SRC_VADC_CG0_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038AA8u)

/** Alias (User Manual Name) for SRC_VADC_CG0_SR2.
* To use register names with standard convension, please use SRC_VADC_CG0_SR2.
*/
#define	SRC_VADCCG0SR2	(SRC_VADC_CG0_SR2)

/** \brief  AAC, VADC Common Group  Service Request 3 */
#define SRC_VADC_CG0_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038AACu)

/** Alias (User Manual Name) for SRC_VADC_CG0_SR3.
* To use register names with standard convension, please use SRC_VADC_CG0_SR3.
*/
#define	SRC_VADCCG0SR3	(SRC_VADC_CG0_SR3)

/** \brief  AB0, VADC Common Group  Service Request 0 */
#define SRC_VADC_CG1_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038AB0u)

/** Alias (User Manual Name) for SRC_VADC_CG1_SR0.
* To use register names with standard convension, please use SRC_VADC_CG1_SR0.
*/
#define	SRC_VADCCG1SR0	(SRC_VADC_CG1_SR0)

/** \brief  AB4, VADC Common Group  Service Request 1 */
#define SRC_VADC_CG1_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038AB4u)

/** Alias (User Manual Name) for SRC_VADC_CG1_SR1.
* To use register names with standard convension, please use SRC_VADC_CG1_SR1.
*/
#define	SRC_VADCCG1SR1	(SRC_VADC_CG1_SR1)

/** \brief  AB8, VADC Common Group  Service Request 2 */
#define SRC_VADC_CG1_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038AB8u)

/** Alias (User Manual Name) for SRC_VADC_CG1_SR2.
* To use register names with standard convension, please use SRC_VADC_CG1_SR2.
*/
#define	SRC_VADCCG1SR2	(SRC_VADC_CG1_SR2)

/** \brief  ABC, VADC Common Group  Service Request 3 */
#define SRC_VADC_CG1_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038ABCu)

/** Alias (User Manual Name) for SRC_VADC_CG1_SR3.
* To use register names with standard convension, please use SRC_VADC_CG1_SR3.
*/
#define	SRC_VADCCG1SR3	(SRC_VADC_CG1_SR3)

/** \brief  980, VADC Group  Service Request 0 */
#define SRC_VADC_G0_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038980u)

/** Alias (User Manual Name) for SRC_VADC_G0_SR0.
* To use register names with standard convension, please use SRC_VADC_G0_SR0.
*/
#define	SRC_VADCG0SR0	(SRC_VADC_G0_SR0)

/** \brief  984, VADC Group  Service Request 1 */
#define SRC_VADC_G0_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038984u)

/** Alias (User Manual Name) for SRC_VADC_G0_SR1.
* To use register names with standard convension, please use SRC_VADC_G0_SR1.
*/
#define	SRC_VADCG0SR1	(SRC_VADC_G0_SR1)

/** \brief  988, VADC Group  Service Request 2 */
#define SRC_VADC_G0_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038988u)

/** Alias (User Manual Name) for SRC_VADC_G0_SR2.
* To use register names with standard convension, please use SRC_VADC_G0_SR2.
*/
#define	SRC_VADCG0SR2	(SRC_VADC_G0_SR2)

/** \brief  98C, VADC Group  Service Request 3 */
#define SRC_VADC_G0_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003898Cu)

/** Alias (User Manual Name) for SRC_VADC_G0_SR3.
* To use register names with standard convension, please use SRC_VADC_G0_SR3.
*/
#define	SRC_VADCG0SR3	(SRC_VADC_G0_SR3)

/** \brief  990, VADC Group  Service Request 0 */
#define SRC_VADC_G1_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038990u)

/** Alias (User Manual Name) for SRC_VADC_G1_SR0.
* To use register names with standard convension, please use SRC_VADC_G1_SR0.
*/
#define	SRC_VADCG1SR0	(SRC_VADC_G1_SR0)

/** \brief  994, VADC Group  Service Request 1 */
#define SRC_VADC_G1_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038994u)

/** Alias (User Manual Name) for SRC_VADC_G1_SR1.
* To use register names with standard convension, please use SRC_VADC_G1_SR1.
*/
#define	SRC_VADCG1SR1	(SRC_VADC_G1_SR1)

/** \brief  998, VADC Group  Service Request 2 */
#define SRC_VADC_G1_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038998u)

/** Alias (User Manual Name) for SRC_VADC_G1_SR2.
* To use register names with standard convension, please use SRC_VADC_G1_SR2.
*/
#define	SRC_VADCG1SR2	(SRC_VADC_G1_SR2)

/** \brief  99C, VADC Group  Service Request 3 */
#define SRC_VADC_G1_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF003899Cu)

/** Alias (User Manual Name) for SRC_VADC_G1_SR3.
* To use register names with standard convension, please use SRC_VADC_G1_SR3.
*/
#define	SRC_VADCG1SR3	(SRC_VADC_G1_SR3)

/** \brief  9A0, VADC Group  Service Request 0 */
#define SRC_VADC_G2_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389A0u)

/** Alias (User Manual Name) for SRC_VADC_G2_SR0.
* To use register names with standard convension, please use SRC_VADC_G2_SR0.
*/
#define	SRC_VADCG2SR0	(SRC_VADC_G2_SR0)

/** \brief  9A4, VADC Group  Service Request 1 */
#define SRC_VADC_G2_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389A4u)

/** Alias (User Manual Name) for SRC_VADC_G2_SR1.
* To use register names with standard convension, please use SRC_VADC_G2_SR1.
*/
#define	SRC_VADCG2SR1	(SRC_VADC_G2_SR1)

/** \brief  9A8, VADC Group  Service Request 2 */
#define SRC_VADC_G2_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389A8u)

/** Alias (User Manual Name) for SRC_VADC_G2_SR2.
* To use register names with standard convension, please use SRC_VADC_G2_SR2.
*/
#define	SRC_VADCG2SR2	(SRC_VADC_G2_SR2)

/** \brief  9AC, VADC Group  Service Request 3 */
#define SRC_VADC_G2_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389ACu)

/** Alias (User Manual Name) for SRC_VADC_G2_SR3.
* To use register names with standard convension, please use SRC_VADC_G2_SR3.
*/
#define	SRC_VADCG2SR3	(SRC_VADC_G2_SR3)

/** \brief  9B0, VADC Group  Service Request 0 */
#define SRC_VADC_G3_SR0 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389B0u)

/** Alias (User Manual Name) for SRC_VADC_G3_SR0.
* To use register names with standard convension, please use SRC_VADC_G3_SR0.
*/
#define	SRC_VADCG3SR0	(SRC_VADC_G3_SR0)

/** \brief  9B4, VADC Group  Service Request 1 */
#define SRC_VADC_G3_SR1 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389B4u)

/** Alias (User Manual Name) for SRC_VADC_G3_SR1.
* To use register names with standard convension, please use SRC_VADC_G3_SR1.
*/
#define	SRC_VADCG3SR1	(SRC_VADC_G3_SR1)

/** \brief  9B8, VADC Group  Service Request 2 */
#define SRC_VADC_G3_SR2 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389B8u)

/** Alias (User Manual Name) for SRC_VADC_G3_SR2.
* To use register names with standard convension, please use SRC_VADC_G3_SR2.
*/
#define	SRC_VADCG3SR2	(SRC_VADC_G3_SR2)

/** \brief  9BC, VADC Group  Service Request 3 */
#define SRC_VADC_G3_SR3 /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF00389BCu)

/** Alias (User Manual Name) for SRC_VADC_G3_SR3.
* To use register names with standard convension, please use SRC_VADC_G3_SR3.
*/
#define	SRC_VADCG3SR3	(SRC_VADC_G3_SR3)

/** \brief  48, XBAR_SRI Service Request */
#define SRC_XBAR_XBAR_SRC /*lint --e(923)*/ (*(volatile Ifx_SRC_SRCR*)0xF0038048u)

/** Alias (User Manual Name) for SRC_XBAR_XBAR_SRC.
* To use register names with standard convension, please use SRC_XBAR_XBAR_SRC.
*/
#define	SRC_XBARSRC	(SRC_XBAR_XBAR_SRC)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSRC_REG_H */
