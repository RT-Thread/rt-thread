/**
 * \file IfxDma_reg.h
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
 * \defgroup IfxLld_Dma_Cfg Dma address
 * \ingroup IfxLld_Dma
 * 
 * \defgroup IfxLld_Dma_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Dma_Cfg
 * 
 * \defgroup IfxLld_Dma_Cfg_Dma 2-DMA
 * \ingroup IfxLld_Dma_Cfg
 * 
 */
#ifndef IFXDMA_REG_H
#define IFXDMA_REG_H 1
/******************************************************************************/
#include "IfxDma_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Dma_Cfg_BaseAddress
 * \{  */

/** \brief  DMA object */
#define MODULE_DMA /*lint --e(923)*/ (*(Ifx_DMA*)0xF0010000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Dma_Cfg_Dma
 * \{  */

/** \brief  40, DMA Hardware Resource 0 Access Enable Register 0 */
#define DMA_ACCEN00 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN00*)0xF0010040u)

/** \brief  44, DMA Hardware Resource 0 Access Enable Register 1 */
#define DMA_ACCEN01 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN01*)0xF0010044u)

/** \brief  48, DMA Hardware Resource 1 Access Enable Register 0 */
#define DMA_ACCEN10 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN10*)0xF0010048u)

/** \brief  4C, DMA Hardware Resource 1 Access Enable Register 1 */
#define DMA_ACCEN11 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN11*)0xF001004Cu)

/** \brief  50, DMA Hardware Resource 2 Access Enable Register 0 */
#define DMA_ACCEN20 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN20*)0xF0010050u)

/** \brief  54, DMA Hardware Resource 2 Access Enable Register 1 */
#define DMA_ACCEN21 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN21*)0xF0010054u)

/** \brief  58, DMA Hardware Resource 3 Access Enable Register 0 */
#define DMA_ACCEN30 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN30*)0xF0010058u)

/** \brief  5C, DMA Hardware Resource 3 Access Enable Register 1 */
#define DMA_ACCEN31 /*lint --e(923)*/ (*(volatile Ifx_DMA_ACCEN31*)0xF001005Cu)

/** \brief  128, DMA Clear Error Register */
#define DMA_BLK0_CLRE /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_CLRE*)0xF0010128u)

/** Alias (User Manual Name) for DMA_BLK0_CLRE.
* To use register names with standard convension, please use DMA_BLK0_CLRE.
*/
#define	DMA_CLRE0	(DMA_BLK0_CLRE)

/** \brief  120, DMA Enable Error Register */
#define DMA_BLK0_EER /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_EER*)0xF0010120u)

/** Alias (User Manual Name) for DMA_BLK0_EER.
* To use register names with standard convension, please use DMA_BLK0_EER.
*/
#define	DMA_EER0	(DMA_BLK0_EER)

/** \brief  124, DMA Error Status Register */
#define DMA_BLK0_ERRSR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ERRSR*)0xF0010124u)

/** Alias (User Manual Name) for DMA_BLK0_ERRSR.
* To use register names with standard convension, please use DMA_BLK0_ERRSR.
*/
#define	DMA_ERRSR0	(DMA_BLK0_ERRSR)

/** \brief  190, DMA Move Engine Channel Address and Interrupt Control Register */
#define DMA_BLK0_ME_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_ADICR*)0xF0010190u)

/** Alias (User Manual Name) for DMA_BLK0_ME_ADICR.
* To use register names with standard convension, please use DMA_BLK0_ME_ADICR.
*/
#define	DMA_ME0ADICR	(DMA_BLK0_ME_ADICR)

/** \brief  194, DMA Move Engine Channel Control Register */
#define DMA_BLK0_ME_CHCR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_CHCR*)0xF0010194u)

/** Alias (User Manual Name) for DMA_BLK0_ME_CHCR.
* To use register names with standard convension, please use DMA_BLK0_ME_CHCR.
*/
#define	DMA_ME0CHCR	(DMA_BLK0_ME_CHCR)

/** \brief  19C, DMA Move Engine Channel Status Register */
#define DMA_BLK0_ME_CHSR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_CHSR*)0xF001019Cu)

/** Alias (User Manual Name) for DMA_BLK0_ME_CHSR.
* To use register names with standard convension, please use DMA_BLK0_ME_CHSR.
*/
#define	DMA_ME0CHSR	(DMA_BLK0_ME_CHSR)

/** \brief  18C, DMA Move Engine Channel Destination Address Register x */
#define DMA_BLK0_ME_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_DADR*)0xF001018Cu)

/** Alias (User Manual Name) for DMA_BLK0_ME_DADR.
* To use register names with standard convension, please use DMA_BLK0_ME_DADR.
*/
#define	DMA_ME0DADR	(DMA_BLK0_ME_DADR)

/** \brief  140, DMA Move Engine Read Register 0 */
#define DMA_BLK0_ME_R0 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R0*)0xF0010140u)

/** Alias (User Manual Name) for DMA_BLK0_ME_R0.
* To use register names with standard convension, please use DMA_BLK0_ME_R0.
*/
#define	DMA_ME00R	(DMA_BLK0_ME_R0)

/** \brief  144, DMA Move Engine Read Register 1 */
#define DMA_BLK0_ME_R1 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R1*)0xF0010144u)

/** Alias (User Manual Name) for DMA_BLK0_ME_R1.
* To use register names with standard convension, please use DMA_BLK0_ME_R1.
*/
#define	DMA_ME01R	(DMA_BLK0_ME_R1)

/** \brief  148, DMA Move Engine Read Register 2 */
#define DMA_BLK0_ME_R2 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R2*)0xF0010148u)

/** Alias (User Manual Name) for DMA_BLK0_ME_R2.
* To use register names with standard convension, please use DMA_BLK0_ME_R2.
*/
#define	DMA_ME02R	(DMA_BLK0_ME_R2)

/** \brief  14C, DMA Move Engine Read Register 3 */
#define DMA_BLK0_ME_R3 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R3*)0xF001014Cu)

/** Alias (User Manual Name) for DMA_BLK0_ME_R3.
* To use register names with standard convension, please use DMA_BLK0_ME_R3.
*/
#define	DMA_ME03R	(DMA_BLK0_ME_R3)

/** \brief  150, DMA Move Engine Read Register 4 */
#define DMA_BLK0_ME_R4 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R4*)0xF0010150u)

/** Alias (User Manual Name) for DMA_BLK0_ME_R4.
* To use register names with standard convension, please use DMA_BLK0_ME_R4.
*/
#define	DMA_ME04R	(DMA_BLK0_ME_R4)

/** \brief  154, DMA Move Engine Read Register 5 */
#define DMA_BLK0_ME_R5 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R5*)0xF0010154u)

/** Alias (User Manual Name) for DMA_BLK0_ME_R5.
* To use register names with standard convension, please use DMA_BLK0_ME_R5.
*/
#define	DMA_ME05R	(DMA_BLK0_ME_R5)

/** \brief  158, DMA Move Engine Read Register 6 */
#define DMA_BLK0_ME_R6 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R6*)0xF0010158u)

/** Alias (User Manual Name) for DMA_BLK0_ME_R6.
* To use register names with standard convension, please use DMA_BLK0_ME_R6.
*/
#define	DMA_ME06R	(DMA_BLK0_ME_R6)

/** \brief  15C, DMA Move Engine Read Register 7 */
#define DMA_BLK0_ME_R7 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R7*)0xF001015Cu)

/** Alias (User Manual Name) for DMA_BLK0_ME_R7.
* To use register names with standard convension, please use DMA_BLK0_ME_R7.
*/
#define	DMA_ME07R	(DMA_BLK0_ME_R7)

/** \brief  180, DMA Move Engine Channel Read Data CRC Register */
#define DMA_BLK0_ME_RDCRC /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_RDCRC*)0xF0010180u)

/** Alias (User Manual Name) for DMA_BLK0_ME_RDCRC.
* To use register names with standard convension, please use DMA_BLK0_ME_RDCRC.
*/
#define	DMA_ME0RDCRC	(DMA_BLK0_ME_RDCRC)

/** \brief  188, DMA Move Engine Channel Source Address Register */
#define DMA_BLK0_ME_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SADR*)0xF0010188u)

/** Alias (User Manual Name) for DMA_BLK0_ME_SADR.
* To use register names with standard convension, please use DMA_BLK0_ME_SADR.
*/
#define	DMA_ME0SADR	(DMA_BLK0_ME_SADR)

/** \brief  184, DMA Move Engine Channel Source and Destination Address CRC
 * Register */
#define DMA_BLK0_ME_SDCRC /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SDCRC*)0xF0010184u)

/** Alias (User Manual Name) for DMA_BLK0_ME_SDCRC.
* To use register names with standard convension, please use DMA_BLK0_ME_SDCRC.
*/
#define	DMA_ME0SDCRC	(DMA_BLK0_ME_SDCRC)

/** \brief  198, DMA Move Engine Channel Shadow Address Register */
#define DMA_BLK0_ME_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SHADR*)0xF0010198u)

/** Alias (User Manual Name) for DMA_BLK0_ME_SHADR.
* To use register names with standard convension, please use DMA_BLK0_ME_SHADR.
*/
#define	DMA_ME0SHADR	(DMA_BLK0_ME_SHADR)

/** \brief  130, DMA Move Engine Status Register */
#define DMA_BLK0_ME_SR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SR*)0xF0010130u)

/** Alias (User Manual Name) for DMA_BLK0_ME_SR.
* To use register names with standard convension, please use DMA_BLK0_ME_SR.
*/
#define	DMA_ME0SR	(DMA_BLK0_ME_SR)

/** \brief  1128, DMA Clear Error Register */
#define DMA_BLK1_CLRE /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_CLRE*)0xF0011128u)

/** Alias (User Manual Name) for DMA_BLK1_CLRE.
* To use register names with standard convension, please use DMA_BLK1_CLRE.
*/
#define	DMA_CLRE1	(DMA_BLK1_CLRE)

/** \brief  1120, DMA Enable Error Register */
#define DMA_BLK1_EER /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_EER*)0xF0011120u)

/** Alias (User Manual Name) for DMA_BLK1_EER.
* To use register names with standard convension, please use DMA_BLK1_EER.
*/
#define	DMA_EER1	(DMA_BLK1_EER)

/** \brief  1124, DMA Error Status Register */
#define DMA_BLK1_ERRSR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ERRSR*)0xF0011124u)

/** Alias (User Manual Name) for DMA_BLK1_ERRSR.
* To use register names with standard convension, please use DMA_BLK1_ERRSR.
*/
#define	DMA_ERRSR1	(DMA_BLK1_ERRSR)

/** \brief  1190, DMA Move Engine Channel Address and Interrupt Control Register */
#define DMA_BLK1_ME_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_ADICR*)0xF0011190u)

/** Alias (User Manual Name) for DMA_BLK1_ME_ADICR.
* To use register names with standard convension, please use DMA_BLK1_ME_ADICR.
*/
#define	DMA_ME1ADICR	(DMA_BLK1_ME_ADICR)

/** \brief  1194, DMA Move Engine Channel Control Register */
#define DMA_BLK1_ME_CHCR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_CHCR*)0xF0011194u)

/** Alias (User Manual Name) for DMA_BLK1_ME_CHCR.
* To use register names with standard convension, please use DMA_BLK1_ME_CHCR.
*/
#define	DMA_ME1CHCR	(DMA_BLK1_ME_CHCR)

/** \brief  119C, DMA Move Engine Channel Status Register */
#define DMA_BLK1_ME_CHSR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_CHSR*)0xF001119Cu)

/** Alias (User Manual Name) for DMA_BLK1_ME_CHSR.
* To use register names with standard convension, please use DMA_BLK1_ME_CHSR.
*/
#define	DMA_ME1CHSR	(DMA_BLK1_ME_CHSR)

/** \brief  118C, DMA Move Engine Channel Destination Address Register x */
#define DMA_BLK1_ME_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_DADR*)0xF001118Cu)

/** Alias (User Manual Name) for DMA_BLK1_ME_DADR.
* To use register names with standard convension, please use DMA_BLK1_ME_DADR.
*/
#define	DMA_ME1DADR	(DMA_BLK1_ME_DADR)

/** \brief  1140, DMA Move Engine Read Register 0 */
#define DMA_BLK1_ME_R0 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R0*)0xF0011140u)

/** Alias (User Manual Name) for DMA_BLK1_ME_R0.
* To use register names with standard convension, please use DMA_BLK1_ME_R0.
*/
#define	DMA_ME10R	(DMA_BLK1_ME_R0)

/** \brief  1144, DMA Move Engine Read Register 1 */
#define DMA_BLK1_ME_R1 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R1*)0xF0011144u)

/** Alias (User Manual Name) for DMA_BLK1_ME_R1.
* To use register names with standard convension, please use DMA_BLK1_ME_R1.
*/
#define	DMA_ME11R	(DMA_BLK1_ME_R1)

/** \brief  1148, DMA Move Engine Read Register 2 */
#define DMA_BLK1_ME_R2 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R2*)0xF0011148u)

/** Alias (User Manual Name) for DMA_BLK1_ME_R2.
* To use register names with standard convension, please use DMA_BLK1_ME_R2.
*/
#define	DMA_ME12R	(DMA_BLK1_ME_R2)

/** \brief  114C, DMA Move Engine Read Register 3 */
#define DMA_BLK1_ME_R3 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R3*)0xF001114Cu)

/** Alias (User Manual Name) for DMA_BLK1_ME_R3.
* To use register names with standard convension, please use DMA_BLK1_ME_R3.
*/
#define	DMA_ME13R	(DMA_BLK1_ME_R3)

/** \brief  1150, DMA Move Engine Read Register 4 */
#define DMA_BLK1_ME_R4 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R4*)0xF0011150u)

/** Alias (User Manual Name) for DMA_BLK1_ME_R4.
* To use register names with standard convension, please use DMA_BLK1_ME_R4.
*/
#define	DMA_ME14R	(DMA_BLK1_ME_R4)

/** \brief  1154, DMA Move Engine Read Register 5 */
#define DMA_BLK1_ME_R5 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R5*)0xF0011154u)

/** Alias (User Manual Name) for DMA_BLK1_ME_R5.
* To use register names with standard convension, please use DMA_BLK1_ME_R5.
*/
#define	DMA_ME15R	(DMA_BLK1_ME_R5)

/** \brief  1158, DMA Move Engine Read Register 6 */
#define DMA_BLK1_ME_R6 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R6*)0xF0011158u)

/** Alias (User Manual Name) for DMA_BLK1_ME_R6.
* To use register names with standard convension, please use DMA_BLK1_ME_R6.
*/
#define	DMA_ME16R	(DMA_BLK1_ME_R6)

/** \brief  115C, DMA Move Engine Read Register 7 */
#define DMA_BLK1_ME_R7 /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_R7*)0xF001115Cu)

/** Alias (User Manual Name) for DMA_BLK1_ME_R7.
* To use register names with standard convension, please use DMA_BLK1_ME_R7.
*/
#define	DMA_ME17R	(DMA_BLK1_ME_R7)

/** \brief  1180, DMA Move Engine Channel Read Data CRC Register */
#define DMA_BLK1_ME_RDCRC /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_RDCRC*)0xF0011180u)

/** Alias (User Manual Name) for DMA_BLK1_ME_RDCRC.
* To use register names with standard convension, please use DMA_BLK1_ME_RDCRC.
*/
#define	DMA_ME1RDCRC	(DMA_BLK1_ME_RDCRC)

/** \brief  1188, DMA Move Engine Channel Source Address Register */
#define DMA_BLK1_ME_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SADR*)0xF0011188u)

/** Alias (User Manual Name) for DMA_BLK1_ME_SADR.
* To use register names with standard convension, please use DMA_BLK1_ME_SADR.
*/
#define	DMA_ME1SADR	(DMA_BLK1_ME_SADR)

/** \brief  1184, DMA Move Engine Channel Source and Destination Address CRC
 * Register */
#define DMA_BLK1_ME_SDCRC /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SDCRC*)0xF0011184u)

/** Alias (User Manual Name) for DMA_BLK1_ME_SDCRC.
* To use register names with standard convension, please use DMA_BLK1_ME_SDCRC.
*/
#define	DMA_ME1SDCRC	(DMA_BLK1_ME_SDCRC)

/** \brief  1198, DMA Move Engine Channel Shadow Address Register */
#define DMA_BLK1_ME_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SHADR*)0xF0011198u)

/** Alias (User Manual Name) for DMA_BLK1_ME_SHADR.
* To use register names with standard convension, please use DMA_BLK1_ME_SHADR.
*/
#define	DMA_ME1SHADR	(DMA_BLK1_ME_SHADR)

/** \brief  1130, DMA Move Engine Status Register */
#define DMA_BLK1_ME_SR /*lint --e(923)*/ (*(volatile Ifx_DMA_BLK_ME_SR*)0xF0011130u)

/** Alias (User Manual Name) for DMA_BLK1_ME_SR.
* To use register names with standard convension, please use DMA_BLK1_ME_SR.
*/
#define	DMA_ME1SR	(DMA_BLK1_ME_SR)

/** \brief  2010, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH0_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012010u)

/** Alias (User Manual Name) for DMA_CH0_ADICR.
* To use register names with standard convension, please use DMA_CH0_ADICR.
*/
#define	DMA_ADICR000	(DMA_CH0_ADICR)

/** \brief  2014, DMA Channel Configuration Register */
#define DMA_CH0_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012014u)

/** Alias (User Manual Name) for DMA_CH0_CHCFGR.
* To use register names with standard convension, please use DMA_CH0_CHCFGR.
*/
#define	DMA_CHCFGR000	(DMA_CH0_CHCFGR)

/** \brief  201C, DMARAM Channel Control and Status Register */
#define DMA_CH0_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001201Cu)

/** Alias (User Manual Name) for DMA_CH0_CHCSR.
* To use register names with standard convension, please use DMA_CH0_CHCSR.
*/
#define	DMA_CHCSR000	(DMA_CH0_CHCSR)

/** \brief  200C, DMA Channel Destination Address Register x */
#define DMA_CH0_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001200Cu)

/** Alias (User Manual Name) for DMA_CH0_DADR.
* To use register names with standard convension, please use DMA_CH0_DADR.
*/
#define	DMA_DADR000	(DMA_CH0_DADR)

/** \brief  2000, DMA Channel Read Data CRC Register */
#define DMA_CH0_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012000u)

/** Alias (User Manual Name) for DMA_CH0_RDCRCR.
* To use register names with standard convension, please use DMA_CH0_RDCRCR.
*/
#define	DMA_RDCRCR000	(DMA_CH0_RDCRCR)

/** \brief  2008, DMA Channel Source Address Register */
#define DMA_CH0_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012008u)

/** Alias (User Manual Name) for DMA_CH0_SADR.
* To use register names with standard convension, please use DMA_CH0_SADR.
*/
#define	DMA_SADR000	(DMA_CH0_SADR)

/** \brief  2004, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH0_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012004u)

/** Alias (User Manual Name) for DMA_CH0_SDCRCR.
* To use register names with standard convension, please use DMA_CH0_SDCRCR.
*/
#define	DMA_SDCRCR000	(DMA_CH0_SDCRCR)

/** \brief  2018, DMA Channel Shadow Address Register */
#define DMA_CH0_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012018u)

/** Alias (User Manual Name) for DMA_CH0_SHADR.
* To use register names with standard convension, please use DMA_CH0_SHADR.
*/
#define	DMA_SHADR000	(DMA_CH0_SHADR)

/** \brief  2150, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH10_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012150u)

/** Alias (User Manual Name) for DMA_CH10_ADICR.
* To use register names with standard convension, please use DMA_CH10_ADICR.
*/
#define	DMA_ADICR010	(DMA_CH10_ADICR)

/** \brief  2154, DMA Channel Configuration Register */
#define DMA_CH10_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012154u)

/** Alias (User Manual Name) for DMA_CH10_CHCFGR.
* To use register names with standard convension, please use DMA_CH10_CHCFGR.
*/
#define	DMA_CHCFGR010	(DMA_CH10_CHCFGR)

/** \brief  215C, DMARAM Channel Control and Status Register */
#define DMA_CH10_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001215Cu)

/** Alias (User Manual Name) for DMA_CH10_CHCSR.
* To use register names with standard convension, please use DMA_CH10_CHCSR.
*/
#define	DMA_CHCSR010	(DMA_CH10_CHCSR)

/** \brief  214C, DMA Channel Destination Address Register x */
#define DMA_CH10_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001214Cu)

/** Alias (User Manual Name) for DMA_CH10_DADR.
* To use register names with standard convension, please use DMA_CH10_DADR.
*/
#define	DMA_DADR010	(DMA_CH10_DADR)

/** \brief  2140, DMA Channel Read Data CRC Register */
#define DMA_CH10_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012140u)

/** Alias (User Manual Name) for DMA_CH10_RDCRCR.
* To use register names with standard convension, please use DMA_CH10_RDCRCR.
*/
#define	DMA_RDCRCR010	(DMA_CH10_RDCRCR)

/** \brief  2148, DMA Channel Source Address Register */
#define DMA_CH10_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012148u)

/** Alias (User Manual Name) for DMA_CH10_SADR.
* To use register names with standard convension, please use DMA_CH10_SADR.
*/
#define	DMA_SADR010	(DMA_CH10_SADR)

/** \brief  2144, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH10_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012144u)

/** Alias (User Manual Name) for DMA_CH10_SDCRCR.
* To use register names with standard convension, please use DMA_CH10_SDCRCR.
*/
#define	DMA_SDCRCR010	(DMA_CH10_SDCRCR)

/** \brief  2158, DMA Channel Shadow Address Register */
#define DMA_CH10_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012158u)

/** Alias (User Manual Name) for DMA_CH10_SHADR.
* To use register names with standard convension, please use DMA_CH10_SHADR.
*/
#define	DMA_SHADR010	(DMA_CH10_SHADR)

/** \brief  2170, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH11_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012170u)

/** Alias (User Manual Name) for DMA_CH11_ADICR.
* To use register names with standard convension, please use DMA_CH11_ADICR.
*/
#define	DMA_ADICR011	(DMA_CH11_ADICR)

/** \brief  2174, DMA Channel Configuration Register */
#define DMA_CH11_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012174u)

/** Alias (User Manual Name) for DMA_CH11_CHCFGR.
* To use register names with standard convension, please use DMA_CH11_CHCFGR.
*/
#define	DMA_CHCFGR011	(DMA_CH11_CHCFGR)

/** \brief  217C, DMARAM Channel Control and Status Register */
#define DMA_CH11_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001217Cu)

/** Alias (User Manual Name) for DMA_CH11_CHCSR.
* To use register names with standard convension, please use DMA_CH11_CHCSR.
*/
#define	DMA_CHCSR011	(DMA_CH11_CHCSR)

/** \brief  216C, DMA Channel Destination Address Register x */
#define DMA_CH11_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001216Cu)

/** Alias (User Manual Name) for DMA_CH11_DADR.
* To use register names with standard convension, please use DMA_CH11_DADR.
*/
#define	DMA_DADR011	(DMA_CH11_DADR)

/** \brief  2160, DMA Channel Read Data CRC Register */
#define DMA_CH11_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012160u)

/** Alias (User Manual Name) for DMA_CH11_RDCRCR.
* To use register names with standard convension, please use DMA_CH11_RDCRCR.
*/
#define	DMA_RDCRCR011	(DMA_CH11_RDCRCR)

/** \brief  2168, DMA Channel Source Address Register */
#define DMA_CH11_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012168u)

/** Alias (User Manual Name) for DMA_CH11_SADR.
* To use register names with standard convension, please use DMA_CH11_SADR.
*/
#define	DMA_SADR011	(DMA_CH11_SADR)

/** \brief  2164, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH11_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012164u)

/** Alias (User Manual Name) for DMA_CH11_SDCRCR.
* To use register names with standard convension, please use DMA_CH11_SDCRCR.
*/
#define	DMA_SDCRCR011	(DMA_CH11_SDCRCR)

/** \brief  2178, DMA Channel Shadow Address Register */
#define DMA_CH11_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012178u)

/** Alias (User Manual Name) for DMA_CH11_SHADR.
* To use register names with standard convension, please use DMA_CH11_SHADR.
*/
#define	DMA_SHADR011	(DMA_CH11_SHADR)

/** \brief  2190, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH12_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012190u)

/** Alias (User Manual Name) for DMA_CH12_ADICR.
* To use register names with standard convension, please use DMA_CH12_ADICR.
*/
#define	DMA_ADICR012	(DMA_CH12_ADICR)

/** \brief  2194, DMA Channel Configuration Register */
#define DMA_CH12_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012194u)

/** Alias (User Manual Name) for DMA_CH12_CHCFGR.
* To use register names with standard convension, please use DMA_CH12_CHCFGR.
*/
#define	DMA_CHCFGR012	(DMA_CH12_CHCFGR)

/** \brief  219C, DMARAM Channel Control and Status Register */
#define DMA_CH12_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001219Cu)

/** Alias (User Manual Name) for DMA_CH12_CHCSR.
* To use register names with standard convension, please use DMA_CH12_CHCSR.
*/
#define	DMA_CHCSR012	(DMA_CH12_CHCSR)

/** \brief  218C, DMA Channel Destination Address Register x */
#define DMA_CH12_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001218Cu)

/** Alias (User Manual Name) for DMA_CH12_DADR.
* To use register names with standard convension, please use DMA_CH12_DADR.
*/
#define	DMA_DADR012	(DMA_CH12_DADR)

/** \brief  2180, DMA Channel Read Data CRC Register */
#define DMA_CH12_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012180u)

/** Alias (User Manual Name) for DMA_CH12_RDCRCR.
* To use register names with standard convension, please use DMA_CH12_RDCRCR.
*/
#define	DMA_RDCRCR012	(DMA_CH12_RDCRCR)

/** \brief  2188, DMA Channel Source Address Register */
#define DMA_CH12_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012188u)

/** Alias (User Manual Name) for DMA_CH12_SADR.
* To use register names with standard convension, please use DMA_CH12_SADR.
*/
#define	DMA_SADR012	(DMA_CH12_SADR)

/** \brief  2184, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH12_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012184u)

/** Alias (User Manual Name) for DMA_CH12_SDCRCR.
* To use register names with standard convension, please use DMA_CH12_SDCRCR.
*/
#define	DMA_SDCRCR012	(DMA_CH12_SDCRCR)

/** \brief  2198, DMA Channel Shadow Address Register */
#define DMA_CH12_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012198u)

/** Alias (User Manual Name) for DMA_CH12_SHADR.
* To use register names with standard convension, please use DMA_CH12_SHADR.
*/
#define	DMA_SHADR012	(DMA_CH12_SHADR)

/** \brief  21B0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH13_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00121B0u)

/** Alias (User Manual Name) for DMA_CH13_ADICR.
* To use register names with standard convension, please use DMA_CH13_ADICR.
*/
#define	DMA_ADICR013	(DMA_CH13_ADICR)

/** \brief  21B4, DMA Channel Configuration Register */
#define DMA_CH13_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00121B4u)

/** Alias (User Manual Name) for DMA_CH13_CHCFGR.
* To use register names with standard convension, please use DMA_CH13_CHCFGR.
*/
#define	DMA_CHCFGR013	(DMA_CH13_CHCFGR)

/** \brief  21BC, DMARAM Channel Control and Status Register */
#define DMA_CH13_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00121BCu)

/** Alias (User Manual Name) for DMA_CH13_CHCSR.
* To use register names with standard convension, please use DMA_CH13_CHCSR.
*/
#define	DMA_CHCSR013	(DMA_CH13_CHCSR)

/** \brief  21AC, DMA Channel Destination Address Register x */
#define DMA_CH13_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00121ACu)

/** Alias (User Manual Name) for DMA_CH13_DADR.
* To use register names with standard convension, please use DMA_CH13_DADR.
*/
#define	DMA_DADR013	(DMA_CH13_DADR)

/** \brief  21A0, DMA Channel Read Data CRC Register */
#define DMA_CH13_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00121A0u)

/** Alias (User Manual Name) for DMA_CH13_RDCRCR.
* To use register names with standard convension, please use DMA_CH13_RDCRCR.
*/
#define	DMA_RDCRCR013	(DMA_CH13_RDCRCR)

/** \brief  21A8, DMA Channel Source Address Register */
#define DMA_CH13_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00121A8u)

/** Alias (User Manual Name) for DMA_CH13_SADR.
* To use register names with standard convension, please use DMA_CH13_SADR.
*/
#define	DMA_SADR013	(DMA_CH13_SADR)

/** \brief  21A4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH13_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00121A4u)

/** Alias (User Manual Name) for DMA_CH13_SDCRCR.
* To use register names with standard convension, please use DMA_CH13_SDCRCR.
*/
#define	DMA_SDCRCR013	(DMA_CH13_SDCRCR)

/** \brief  21B8, DMA Channel Shadow Address Register */
#define DMA_CH13_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00121B8u)

/** Alias (User Manual Name) for DMA_CH13_SHADR.
* To use register names with standard convension, please use DMA_CH13_SHADR.
*/
#define	DMA_SHADR013	(DMA_CH13_SHADR)

/** \brief  21D0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH14_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00121D0u)

/** Alias (User Manual Name) for DMA_CH14_ADICR.
* To use register names with standard convension, please use DMA_CH14_ADICR.
*/
#define	DMA_ADICR014	(DMA_CH14_ADICR)

/** \brief  21D4, DMA Channel Configuration Register */
#define DMA_CH14_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00121D4u)

/** Alias (User Manual Name) for DMA_CH14_CHCFGR.
* To use register names with standard convension, please use DMA_CH14_CHCFGR.
*/
#define	DMA_CHCFGR014	(DMA_CH14_CHCFGR)

/** \brief  21DC, DMARAM Channel Control and Status Register */
#define DMA_CH14_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00121DCu)

/** Alias (User Manual Name) for DMA_CH14_CHCSR.
* To use register names with standard convension, please use DMA_CH14_CHCSR.
*/
#define	DMA_CHCSR014	(DMA_CH14_CHCSR)

/** \brief  21CC, DMA Channel Destination Address Register x */
#define DMA_CH14_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00121CCu)

/** Alias (User Manual Name) for DMA_CH14_DADR.
* To use register names with standard convension, please use DMA_CH14_DADR.
*/
#define	DMA_DADR014	(DMA_CH14_DADR)

/** \brief  21C0, DMA Channel Read Data CRC Register */
#define DMA_CH14_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00121C0u)

/** Alias (User Manual Name) for DMA_CH14_RDCRCR.
* To use register names with standard convension, please use DMA_CH14_RDCRCR.
*/
#define	DMA_RDCRCR014	(DMA_CH14_RDCRCR)

/** \brief  21C8, DMA Channel Source Address Register */
#define DMA_CH14_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00121C8u)

/** Alias (User Manual Name) for DMA_CH14_SADR.
* To use register names with standard convension, please use DMA_CH14_SADR.
*/
#define	DMA_SADR014	(DMA_CH14_SADR)

/** \brief  21C4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH14_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00121C4u)

/** Alias (User Manual Name) for DMA_CH14_SDCRCR.
* To use register names with standard convension, please use DMA_CH14_SDCRCR.
*/
#define	DMA_SDCRCR014	(DMA_CH14_SDCRCR)

/** \brief  21D8, DMA Channel Shadow Address Register */
#define DMA_CH14_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00121D8u)

/** Alias (User Manual Name) for DMA_CH14_SHADR.
* To use register names with standard convension, please use DMA_CH14_SHADR.
*/
#define	DMA_SHADR014	(DMA_CH14_SHADR)

/** \brief  21F0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH15_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00121F0u)

/** Alias (User Manual Name) for DMA_CH15_ADICR.
* To use register names with standard convension, please use DMA_CH15_ADICR.
*/
#define	DMA_ADICR015	(DMA_CH15_ADICR)

/** \brief  21F4, DMA Channel Configuration Register */
#define DMA_CH15_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00121F4u)

/** Alias (User Manual Name) for DMA_CH15_CHCFGR.
* To use register names with standard convension, please use DMA_CH15_CHCFGR.
*/
#define	DMA_CHCFGR015	(DMA_CH15_CHCFGR)

/** \brief  21FC, DMARAM Channel Control and Status Register */
#define DMA_CH15_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00121FCu)

/** Alias (User Manual Name) for DMA_CH15_CHCSR.
* To use register names with standard convension, please use DMA_CH15_CHCSR.
*/
#define	DMA_CHCSR015	(DMA_CH15_CHCSR)

/** \brief  21EC, DMA Channel Destination Address Register x */
#define DMA_CH15_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00121ECu)

/** Alias (User Manual Name) for DMA_CH15_DADR.
* To use register names with standard convension, please use DMA_CH15_DADR.
*/
#define	DMA_DADR015	(DMA_CH15_DADR)

/** \brief  21E0, DMA Channel Read Data CRC Register */
#define DMA_CH15_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00121E0u)

/** Alias (User Manual Name) for DMA_CH15_RDCRCR.
* To use register names with standard convension, please use DMA_CH15_RDCRCR.
*/
#define	DMA_RDCRCR015	(DMA_CH15_RDCRCR)

/** \brief  21E8, DMA Channel Source Address Register */
#define DMA_CH15_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00121E8u)

/** Alias (User Manual Name) for DMA_CH15_SADR.
* To use register names with standard convension, please use DMA_CH15_SADR.
*/
#define	DMA_SADR015	(DMA_CH15_SADR)

/** \brief  21E4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH15_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00121E4u)

/** Alias (User Manual Name) for DMA_CH15_SDCRCR.
* To use register names with standard convension, please use DMA_CH15_SDCRCR.
*/
#define	DMA_SDCRCR015	(DMA_CH15_SDCRCR)

/** \brief  21F8, DMA Channel Shadow Address Register */
#define DMA_CH15_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00121F8u)

/** Alias (User Manual Name) for DMA_CH15_SHADR.
* To use register names with standard convension, please use DMA_CH15_SHADR.
*/
#define	DMA_SHADR015	(DMA_CH15_SHADR)

/** \brief  2210, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH16_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012210u)

/** Alias (User Manual Name) for DMA_CH16_ADICR.
* To use register names with standard convension, please use DMA_CH16_ADICR.
*/
#define	DMA_ADICR016	(DMA_CH16_ADICR)

/** \brief  2214, DMA Channel Configuration Register */
#define DMA_CH16_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012214u)

/** Alias (User Manual Name) for DMA_CH16_CHCFGR.
* To use register names with standard convension, please use DMA_CH16_CHCFGR.
*/
#define	DMA_CHCFGR016	(DMA_CH16_CHCFGR)

/** \brief  221C, DMARAM Channel Control and Status Register */
#define DMA_CH16_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001221Cu)

/** Alias (User Manual Name) for DMA_CH16_CHCSR.
* To use register names with standard convension, please use DMA_CH16_CHCSR.
*/
#define	DMA_CHCSR016	(DMA_CH16_CHCSR)

/** \brief  220C, DMA Channel Destination Address Register x */
#define DMA_CH16_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001220Cu)

/** Alias (User Manual Name) for DMA_CH16_DADR.
* To use register names with standard convension, please use DMA_CH16_DADR.
*/
#define	DMA_DADR016	(DMA_CH16_DADR)

/** \brief  2200, DMA Channel Read Data CRC Register */
#define DMA_CH16_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012200u)

/** Alias (User Manual Name) for DMA_CH16_RDCRCR.
* To use register names with standard convension, please use DMA_CH16_RDCRCR.
*/
#define	DMA_RDCRCR016	(DMA_CH16_RDCRCR)

/** \brief  2208, DMA Channel Source Address Register */
#define DMA_CH16_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012208u)

/** Alias (User Manual Name) for DMA_CH16_SADR.
* To use register names with standard convension, please use DMA_CH16_SADR.
*/
#define	DMA_SADR016	(DMA_CH16_SADR)

/** \brief  2204, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH16_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012204u)

/** Alias (User Manual Name) for DMA_CH16_SDCRCR.
* To use register names with standard convension, please use DMA_CH16_SDCRCR.
*/
#define	DMA_SDCRCR016	(DMA_CH16_SDCRCR)

/** \brief  2218, DMA Channel Shadow Address Register */
#define DMA_CH16_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012218u)

/** Alias (User Manual Name) for DMA_CH16_SHADR.
* To use register names with standard convension, please use DMA_CH16_SHADR.
*/
#define	DMA_SHADR016	(DMA_CH16_SHADR)

/** \brief  2230, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH17_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012230u)

/** Alias (User Manual Name) for DMA_CH17_ADICR.
* To use register names with standard convension, please use DMA_CH17_ADICR.
*/
#define	DMA_ADICR017	(DMA_CH17_ADICR)

/** \brief  2234, DMA Channel Configuration Register */
#define DMA_CH17_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012234u)

/** Alias (User Manual Name) for DMA_CH17_CHCFGR.
* To use register names with standard convension, please use DMA_CH17_CHCFGR.
*/
#define	DMA_CHCFGR017	(DMA_CH17_CHCFGR)

/** \brief  223C, DMARAM Channel Control and Status Register */
#define DMA_CH17_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001223Cu)

/** Alias (User Manual Name) for DMA_CH17_CHCSR.
* To use register names with standard convension, please use DMA_CH17_CHCSR.
*/
#define	DMA_CHCSR017	(DMA_CH17_CHCSR)

/** \brief  222C, DMA Channel Destination Address Register x */
#define DMA_CH17_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001222Cu)

/** Alias (User Manual Name) for DMA_CH17_DADR.
* To use register names with standard convension, please use DMA_CH17_DADR.
*/
#define	DMA_DADR017	(DMA_CH17_DADR)

/** \brief  2220, DMA Channel Read Data CRC Register */
#define DMA_CH17_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012220u)

/** Alias (User Manual Name) for DMA_CH17_RDCRCR.
* To use register names with standard convension, please use DMA_CH17_RDCRCR.
*/
#define	DMA_RDCRCR017	(DMA_CH17_RDCRCR)

/** \brief  2228, DMA Channel Source Address Register */
#define DMA_CH17_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012228u)

/** Alias (User Manual Name) for DMA_CH17_SADR.
* To use register names with standard convension, please use DMA_CH17_SADR.
*/
#define	DMA_SADR017	(DMA_CH17_SADR)

/** \brief  2224, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH17_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012224u)

/** Alias (User Manual Name) for DMA_CH17_SDCRCR.
* To use register names with standard convension, please use DMA_CH17_SDCRCR.
*/
#define	DMA_SDCRCR017	(DMA_CH17_SDCRCR)

/** \brief  2238, DMA Channel Shadow Address Register */
#define DMA_CH17_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012238u)

/** Alias (User Manual Name) for DMA_CH17_SHADR.
* To use register names with standard convension, please use DMA_CH17_SHADR.
*/
#define	DMA_SHADR017	(DMA_CH17_SHADR)

/** \brief  2250, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH18_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012250u)

/** Alias (User Manual Name) for DMA_CH18_ADICR.
* To use register names with standard convension, please use DMA_CH18_ADICR.
*/
#define	DMA_ADICR018	(DMA_CH18_ADICR)

/** \brief  2254, DMA Channel Configuration Register */
#define DMA_CH18_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012254u)

/** Alias (User Manual Name) for DMA_CH18_CHCFGR.
* To use register names with standard convension, please use DMA_CH18_CHCFGR.
*/
#define	DMA_CHCFGR018	(DMA_CH18_CHCFGR)

/** \brief  225C, DMARAM Channel Control and Status Register */
#define DMA_CH18_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001225Cu)

/** Alias (User Manual Name) for DMA_CH18_CHCSR.
* To use register names with standard convension, please use DMA_CH18_CHCSR.
*/
#define	DMA_CHCSR018	(DMA_CH18_CHCSR)

/** \brief  224C, DMA Channel Destination Address Register x */
#define DMA_CH18_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001224Cu)

/** Alias (User Manual Name) for DMA_CH18_DADR.
* To use register names with standard convension, please use DMA_CH18_DADR.
*/
#define	DMA_DADR018	(DMA_CH18_DADR)

/** \brief  2240, DMA Channel Read Data CRC Register */
#define DMA_CH18_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012240u)

/** Alias (User Manual Name) for DMA_CH18_RDCRCR.
* To use register names with standard convension, please use DMA_CH18_RDCRCR.
*/
#define	DMA_RDCRCR018	(DMA_CH18_RDCRCR)

/** \brief  2248, DMA Channel Source Address Register */
#define DMA_CH18_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012248u)

/** Alias (User Manual Name) for DMA_CH18_SADR.
* To use register names with standard convension, please use DMA_CH18_SADR.
*/
#define	DMA_SADR018	(DMA_CH18_SADR)

/** \brief  2244, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH18_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012244u)

/** Alias (User Manual Name) for DMA_CH18_SDCRCR.
* To use register names with standard convension, please use DMA_CH18_SDCRCR.
*/
#define	DMA_SDCRCR018	(DMA_CH18_SDCRCR)

/** \brief  2258, DMA Channel Shadow Address Register */
#define DMA_CH18_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012258u)

/** Alias (User Manual Name) for DMA_CH18_SHADR.
* To use register names with standard convension, please use DMA_CH18_SHADR.
*/
#define	DMA_SHADR018	(DMA_CH18_SHADR)

/** \brief  2270, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH19_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012270u)

/** Alias (User Manual Name) for DMA_CH19_ADICR.
* To use register names with standard convension, please use DMA_CH19_ADICR.
*/
#define	DMA_ADICR019	(DMA_CH19_ADICR)

/** \brief  2274, DMA Channel Configuration Register */
#define DMA_CH19_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012274u)

/** Alias (User Manual Name) for DMA_CH19_CHCFGR.
* To use register names with standard convension, please use DMA_CH19_CHCFGR.
*/
#define	DMA_CHCFGR019	(DMA_CH19_CHCFGR)

/** \brief  227C, DMARAM Channel Control and Status Register */
#define DMA_CH19_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001227Cu)

/** Alias (User Manual Name) for DMA_CH19_CHCSR.
* To use register names with standard convension, please use DMA_CH19_CHCSR.
*/
#define	DMA_CHCSR019	(DMA_CH19_CHCSR)

/** \brief  226C, DMA Channel Destination Address Register x */
#define DMA_CH19_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001226Cu)

/** Alias (User Manual Name) for DMA_CH19_DADR.
* To use register names with standard convension, please use DMA_CH19_DADR.
*/
#define	DMA_DADR019	(DMA_CH19_DADR)

/** \brief  2260, DMA Channel Read Data CRC Register */
#define DMA_CH19_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012260u)

/** Alias (User Manual Name) for DMA_CH19_RDCRCR.
* To use register names with standard convension, please use DMA_CH19_RDCRCR.
*/
#define	DMA_RDCRCR019	(DMA_CH19_RDCRCR)

/** \brief  2268, DMA Channel Source Address Register */
#define DMA_CH19_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012268u)

/** Alias (User Manual Name) for DMA_CH19_SADR.
* To use register names with standard convension, please use DMA_CH19_SADR.
*/
#define	DMA_SADR019	(DMA_CH19_SADR)

/** \brief  2264, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH19_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012264u)

/** Alias (User Manual Name) for DMA_CH19_SDCRCR.
* To use register names with standard convension, please use DMA_CH19_SDCRCR.
*/
#define	DMA_SDCRCR019	(DMA_CH19_SDCRCR)

/** \brief  2278, DMA Channel Shadow Address Register */
#define DMA_CH19_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012278u)

/** Alias (User Manual Name) for DMA_CH19_SHADR.
* To use register names with standard convension, please use DMA_CH19_SHADR.
*/
#define	DMA_SHADR019	(DMA_CH19_SHADR)

/** \brief  2030, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH1_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012030u)

/** Alias (User Manual Name) for DMA_CH1_ADICR.
* To use register names with standard convension, please use DMA_CH1_ADICR.
*/
#define	DMA_ADICR001	(DMA_CH1_ADICR)

/** \brief  2034, DMA Channel Configuration Register */
#define DMA_CH1_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012034u)

/** Alias (User Manual Name) for DMA_CH1_CHCFGR.
* To use register names with standard convension, please use DMA_CH1_CHCFGR.
*/
#define	DMA_CHCFGR001	(DMA_CH1_CHCFGR)

/** \brief  203C, DMARAM Channel Control and Status Register */
#define DMA_CH1_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001203Cu)

/** Alias (User Manual Name) for DMA_CH1_CHCSR.
* To use register names with standard convension, please use DMA_CH1_CHCSR.
*/
#define	DMA_CHCSR001	(DMA_CH1_CHCSR)

/** \brief  202C, DMA Channel Destination Address Register x */
#define DMA_CH1_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001202Cu)

/** Alias (User Manual Name) for DMA_CH1_DADR.
* To use register names with standard convension, please use DMA_CH1_DADR.
*/
#define	DMA_DADR001	(DMA_CH1_DADR)

/** \brief  2020, DMA Channel Read Data CRC Register */
#define DMA_CH1_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012020u)

/** Alias (User Manual Name) for DMA_CH1_RDCRCR.
* To use register names with standard convension, please use DMA_CH1_RDCRCR.
*/
#define	DMA_RDCRCR001	(DMA_CH1_RDCRCR)

/** \brief  2028, DMA Channel Source Address Register */
#define DMA_CH1_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012028u)

/** Alias (User Manual Name) for DMA_CH1_SADR.
* To use register names with standard convension, please use DMA_CH1_SADR.
*/
#define	DMA_SADR001	(DMA_CH1_SADR)

/** \brief  2024, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH1_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012024u)

/** Alias (User Manual Name) for DMA_CH1_SDCRCR.
* To use register names with standard convension, please use DMA_CH1_SDCRCR.
*/
#define	DMA_SDCRCR001	(DMA_CH1_SDCRCR)

/** \brief  2038, DMA Channel Shadow Address Register */
#define DMA_CH1_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012038u)

/** Alias (User Manual Name) for DMA_CH1_SHADR.
* To use register names with standard convension, please use DMA_CH1_SHADR.
*/
#define	DMA_SHADR001	(DMA_CH1_SHADR)

/** \brief  2290, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH20_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012290u)

/** Alias (User Manual Name) for DMA_CH20_ADICR.
* To use register names with standard convension, please use DMA_CH20_ADICR.
*/
#define	DMA_ADICR020	(DMA_CH20_ADICR)

/** \brief  2294, DMA Channel Configuration Register */
#define DMA_CH20_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012294u)

/** Alias (User Manual Name) for DMA_CH20_CHCFGR.
* To use register names with standard convension, please use DMA_CH20_CHCFGR.
*/
#define	DMA_CHCFGR020	(DMA_CH20_CHCFGR)

/** \brief  229C, DMARAM Channel Control and Status Register */
#define DMA_CH20_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001229Cu)

/** Alias (User Manual Name) for DMA_CH20_CHCSR.
* To use register names with standard convension, please use DMA_CH20_CHCSR.
*/
#define	DMA_CHCSR020	(DMA_CH20_CHCSR)

/** \brief  228C, DMA Channel Destination Address Register x */
#define DMA_CH20_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001228Cu)

/** Alias (User Manual Name) for DMA_CH20_DADR.
* To use register names with standard convension, please use DMA_CH20_DADR.
*/
#define	DMA_DADR020	(DMA_CH20_DADR)

/** \brief  2280, DMA Channel Read Data CRC Register */
#define DMA_CH20_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012280u)

/** Alias (User Manual Name) for DMA_CH20_RDCRCR.
* To use register names with standard convension, please use DMA_CH20_RDCRCR.
*/
#define	DMA_RDCRCR020	(DMA_CH20_RDCRCR)

/** \brief  2288, DMA Channel Source Address Register */
#define DMA_CH20_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012288u)

/** Alias (User Manual Name) for DMA_CH20_SADR.
* To use register names with standard convension, please use DMA_CH20_SADR.
*/
#define	DMA_SADR020	(DMA_CH20_SADR)

/** \brief  2284, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH20_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012284u)

/** Alias (User Manual Name) for DMA_CH20_SDCRCR.
* To use register names with standard convension, please use DMA_CH20_SDCRCR.
*/
#define	DMA_SDCRCR020	(DMA_CH20_SDCRCR)

/** \brief  2298, DMA Channel Shadow Address Register */
#define DMA_CH20_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012298u)

/** Alias (User Manual Name) for DMA_CH20_SHADR.
* To use register names with standard convension, please use DMA_CH20_SHADR.
*/
#define	DMA_SHADR020	(DMA_CH20_SHADR)

/** \brief  22B0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH21_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00122B0u)

/** Alias (User Manual Name) for DMA_CH21_ADICR.
* To use register names with standard convension, please use DMA_CH21_ADICR.
*/
#define	DMA_ADICR021	(DMA_CH21_ADICR)

/** \brief  22B4, DMA Channel Configuration Register */
#define DMA_CH21_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00122B4u)

/** Alias (User Manual Name) for DMA_CH21_CHCFGR.
* To use register names with standard convension, please use DMA_CH21_CHCFGR.
*/
#define	DMA_CHCFGR021	(DMA_CH21_CHCFGR)

/** \brief  22BC, DMARAM Channel Control and Status Register */
#define DMA_CH21_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00122BCu)

/** Alias (User Manual Name) for DMA_CH21_CHCSR.
* To use register names with standard convension, please use DMA_CH21_CHCSR.
*/
#define	DMA_CHCSR021	(DMA_CH21_CHCSR)

/** \brief  22AC, DMA Channel Destination Address Register x */
#define DMA_CH21_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00122ACu)

/** Alias (User Manual Name) for DMA_CH21_DADR.
* To use register names with standard convension, please use DMA_CH21_DADR.
*/
#define	DMA_DADR021	(DMA_CH21_DADR)

/** \brief  22A0, DMA Channel Read Data CRC Register */
#define DMA_CH21_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00122A0u)

/** Alias (User Manual Name) for DMA_CH21_RDCRCR.
* To use register names with standard convension, please use DMA_CH21_RDCRCR.
*/
#define	DMA_RDCRCR021	(DMA_CH21_RDCRCR)

/** \brief  22A8, DMA Channel Source Address Register */
#define DMA_CH21_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00122A8u)

/** Alias (User Manual Name) for DMA_CH21_SADR.
* To use register names with standard convension, please use DMA_CH21_SADR.
*/
#define	DMA_SADR021	(DMA_CH21_SADR)

/** \brief  22A4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH21_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00122A4u)

/** Alias (User Manual Name) for DMA_CH21_SDCRCR.
* To use register names with standard convension, please use DMA_CH21_SDCRCR.
*/
#define	DMA_SDCRCR021	(DMA_CH21_SDCRCR)

/** \brief  22B8, DMA Channel Shadow Address Register */
#define DMA_CH21_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00122B8u)

/** Alias (User Manual Name) for DMA_CH21_SHADR.
* To use register names with standard convension, please use DMA_CH21_SHADR.
*/
#define	DMA_SHADR021	(DMA_CH21_SHADR)

/** \brief  22D0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH22_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00122D0u)

/** Alias (User Manual Name) for DMA_CH22_ADICR.
* To use register names with standard convension, please use DMA_CH22_ADICR.
*/
#define	DMA_ADICR022	(DMA_CH22_ADICR)

/** \brief  22D4, DMA Channel Configuration Register */
#define DMA_CH22_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00122D4u)

/** Alias (User Manual Name) for DMA_CH22_CHCFGR.
* To use register names with standard convension, please use DMA_CH22_CHCFGR.
*/
#define	DMA_CHCFGR022	(DMA_CH22_CHCFGR)

/** \brief  22DC, DMARAM Channel Control and Status Register */
#define DMA_CH22_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00122DCu)

/** Alias (User Manual Name) for DMA_CH22_CHCSR.
* To use register names with standard convension, please use DMA_CH22_CHCSR.
*/
#define	DMA_CHCSR022	(DMA_CH22_CHCSR)

/** \brief  22CC, DMA Channel Destination Address Register x */
#define DMA_CH22_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00122CCu)

/** Alias (User Manual Name) for DMA_CH22_DADR.
* To use register names with standard convension, please use DMA_CH22_DADR.
*/
#define	DMA_DADR022	(DMA_CH22_DADR)

/** \brief  22C0, DMA Channel Read Data CRC Register */
#define DMA_CH22_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00122C0u)

/** Alias (User Manual Name) for DMA_CH22_RDCRCR.
* To use register names with standard convension, please use DMA_CH22_RDCRCR.
*/
#define	DMA_RDCRCR022	(DMA_CH22_RDCRCR)

/** \brief  22C8, DMA Channel Source Address Register */
#define DMA_CH22_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00122C8u)

/** Alias (User Manual Name) for DMA_CH22_SADR.
* To use register names with standard convension, please use DMA_CH22_SADR.
*/
#define	DMA_SADR022	(DMA_CH22_SADR)

/** \brief  22C4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH22_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00122C4u)

/** Alias (User Manual Name) for DMA_CH22_SDCRCR.
* To use register names with standard convension, please use DMA_CH22_SDCRCR.
*/
#define	DMA_SDCRCR022	(DMA_CH22_SDCRCR)

/** \brief  22D8, DMA Channel Shadow Address Register */
#define DMA_CH22_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00122D8u)

/** Alias (User Manual Name) for DMA_CH22_SHADR.
* To use register names with standard convension, please use DMA_CH22_SHADR.
*/
#define	DMA_SHADR022	(DMA_CH22_SHADR)

/** \brief  22F0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH23_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00122F0u)

/** Alias (User Manual Name) for DMA_CH23_ADICR.
* To use register names with standard convension, please use DMA_CH23_ADICR.
*/
#define	DMA_ADICR023	(DMA_CH23_ADICR)

/** \brief  22F4, DMA Channel Configuration Register */
#define DMA_CH23_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00122F4u)

/** Alias (User Manual Name) for DMA_CH23_CHCFGR.
* To use register names with standard convension, please use DMA_CH23_CHCFGR.
*/
#define	DMA_CHCFGR023	(DMA_CH23_CHCFGR)

/** \brief  22FC, DMARAM Channel Control and Status Register */
#define DMA_CH23_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00122FCu)

/** Alias (User Manual Name) for DMA_CH23_CHCSR.
* To use register names with standard convension, please use DMA_CH23_CHCSR.
*/
#define	DMA_CHCSR023	(DMA_CH23_CHCSR)

/** \brief  22EC, DMA Channel Destination Address Register x */
#define DMA_CH23_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00122ECu)

/** Alias (User Manual Name) for DMA_CH23_DADR.
* To use register names with standard convension, please use DMA_CH23_DADR.
*/
#define	DMA_DADR023	(DMA_CH23_DADR)

/** \brief  22E0, DMA Channel Read Data CRC Register */
#define DMA_CH23_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00122E0u)

/** Alias (User Manual Name) for DMA_CH23_RDCRCR.
* To use register names with standard convension, please use DMA_CH23_RDCRCR.
*/
#define	DMA_RDCRCR023	(DMA_CH23_RDCRCR)

/** \brief  22E8, DMA Channel Source Address Register */
#define DMA_CH23_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00122E8u)

/** Alias (User Manual Name) for DMA_CH23_SADR.
* To use register names with standard convension, please use DMA_CH23_SADR.
*/
#define	DMA_SADR023	(DMA_CH23_SADR)

/** \brief  22E4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH23_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00122E4u)

/** Alias (User Manual Name) for DMA_CH23_SDCRCR.
* To use register names with standard convension, please use DMA_CH23_SDCRCR.
*/
#define	DMA_SDCRCR023	(DMA_CH23_SDCRCR)

/** \brief  22F8, DMA Channel Shadow Address Register */
#define DMA_CH23_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00122F8u)

/** Alias (User Manual Name) for DMA_CH23_SHADR.
* To use register names with standard convension, please use DMA_CH23_SHADR.
*/
#define	DMA_SHADR023	(DMA_CH23_SHADR)

/** \brief  2310, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH24_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012310u)

/** Alias (User Manual Name) for DMA_CH24_ADICR.
* To use register names with standard convension, please use DMA_CH24_ADICR.
*/
#define	DMA_ADICR024	(DMA_CH24_ADICR)

/** \brief  2314, DMA Channel Configuration Register */
#define DMA_CH24_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012314u)

/** Alias (User Manual Name) for DMA_CH24_CHCFGR.
* To use register names with standard convension, please use DMA_CH24_CHCFGR.
*/
#define	DMA_CHCFGR024	(DMA_CH24_CHCFGR)

/** \brief  231C, DMARAM Channel Control and Status Register */
#define DMA_CH24_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001231Cu)

/** Alias (User Manual Name) for DMA_CH24_CHCSR.
* To use register names with standard convension, please use DMA_CH24_CHCSR.
*/
#define	DMA_CHCSR024	(DMA_CH24_CHCSR)

/** \brief  230C, DMA Channel Destination Address Register x */
#define DMA_CH24_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001230Cu)

/** Alias (User Manual Name) for DMA_CH24_DADR.
* To use register names with standard convension, please use DMA_CH24_DADR.
*/
#define	DMA_DADR024	(DMA_CH24_DADR)

/** \brief  2300, DMA Channel Read Data CRC Register */
#define DMA_CH24_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012300u)

/** Alias (User Manual Name) for DMA_CH24_RDCRCR.
* To use register names with standard convension, please use DMA_CH24_RDCRCR.
*/
#define	DMA_RDCRCR024	(DMA_CH24_RDCRCR)

/** \brief  2308, DMA Channel Source Address Register */
#define DMA_CH24_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012308u)

/** Alias (User Manual Name) for DMA_CH24_SADR.
* To use register names with standard convension, please use DMA_CH24_SADR.
*/
#define	DMA_SADR024	(DMA_CH24_SADR)

/** \brief  2304, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH24_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012304u)

/** Alias (User Manual Name) for DMA_CH24_SDCRCR.
* To use register names with standard convension, please use DMA_CH24_SDCRCR.
*/
#define	DMA_SDCRCR024	(DMA_CH24_SDCRCR)

/** \brief  2318, DMA Channel Shadow Address Register */
#define DMA_CH24_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012318u)

/** Alias (User Manual Name) for DMA_CH24_SHADR.
* To use register names with standard convension, please use DMA_CH24_SHADR.
*/
#define	DMA_SHADR024	(DMA_CH24_SHADR)

/** \brief  2330, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH25_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012330u)

/** Alias (User Manual Name) for DMA_CH25_ADICR.
* To use register names with standard convension, please use DMA_CH25_ADICR.
*/
#define	DMA_ADICR025	(DMA_CH25_ADICR)

/** \brief  2334, DMA Channel Configuration Register */
#define DMA_CH25_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012334u)

/** Alias (User Manual Name) for DMA_CH25_CHCFGR.
* To use register names with standard convension, please use DMA_CH25_CHCFGR.
*/
#define	DMA_CHCFGR025	(DMA_CH25_CHCFGR)

/** \brief  233C, DMARAM Channel Control and Status Register */
#define DMA_CH25_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001233Cu)

/** Alias (User Manual Name) for DMA_CH25_CHCSR.
* To use register names with standard convension, please use DMA_CH25_CHCSR.
*/
#define	DMA_CHCSR025	(DMA_CH25_CHCSR)

/** \brief  232C, DMA Channel Destination Address Register x */
#define DMA_CH25_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001232Cu)

/** Alias (User Manual Name) for DMA_CH25_DADR.
* To use register names with standard convension, please use DMA_CH25_DADR.
*/
#define	DMA_DADR025	(DMA_CH25_DADR)

/** \brief  2320, DMA Channel Read Data CRC Register */
#define DMA_CH25_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012320u)

/** Alias (User Manual Name) for DMA_CH25_RDCRCR.
* To use register names with standard convension, please use DMA_CH25_RDCRCR.
*/
#define	DMA_RDCRCR025	(DMA_CH25_RDCRCR)

/** \brief  2328, DMA Channel Source Address Register */
#define DMA_CH25_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012328u)

/** Alias (User Manual Name) for DMA_CH25_SADR.
* To use register names with standard convension, please use DMA_CH25_SADR.
*/
#define	DMA_SADR025	(DMA_CH25_SADR)

/** \brief  2324, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH25_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012324u)

/** Alias (User Manual Name) for DMA_CH25_SDCRCR.
* To use register names with standard convension, please use DMA_CH25_SDCRCR.
*/
#define	DMA_SDCRCR025	(DMA_CH25_SDCRCR)

/** \brief  2338, DMA Channel Shadow Address Register */
#define DMA_CH25_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012338u)

/** Alias (User Manual Name) for DMA_CH25_SHADR.
* To use register names with standard convension, please use DMA_CH25_SHADR.
*/
#define	DMA_SHADR025	(DMA_CH25_SHADR)

/** \brief  2350, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH26_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012350u)

/** Alias (User Manual Name) for DMA_CH26_ADICR.
* To use register names with standard convension, please use DMA_CH26_ADICR.
*/
#define	DMA_ADICR026	(DMA_CH26_ADICR)

/** \brief  2354, DMA Channel Configuration Register */
#define DMA_CH26_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012354u)

/** Alias (User Manual Name) for DMA_CH26_CHCFGR.
* To use register names with standard convension, please use DMA_CH26_CHCFGR.
*/
#define	DMA_CHCFGR026	(DMA_CH26_CHCFGR)

/** \brief  235C, DMARAM Channel Control and Status Register */
#define DMA_CH26_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001235Cu)

/** Alias (User Manual Name) for DMA_CH26_CHCSR.
* To use register names with standard convension, please use DMA_CH26_CHCSR.
*/
#define	DMA_CHCSR026	(DMA_CH26_CHCSR)

/** \brief  234C, DMA Channel Destination Address Register x */
#define DMA_CH26_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001234Cu)

/** Alias (User Manual Name) for DMA_CH26_DADR.
* To use register names with standard convension, please use DMA_CH26_DADR.
*/
#define	DMA_DADR026	(DMA_CH26_DADR)

/** \brief  2340, DMA Channel Read Data CRC Register */
#define DMA_CH26_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012340u)

/** Alias (User Manual Name) for DMA_CH26_RDCRCR.
* To use register names with standard convension, please use DMA_CH26_RDCRCR.
*/
#define	DMA_RDCRCR026	(DMA_CH26_RDCRCR)

/** \brief  2348, DMA Channel Source Address Register */
#define DMA_CH26_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012348u)

/** Alias (User Manual Name) for DMA_CH26_SADR.
* To use register names with standard convension, please use DMA_CH26_SADR.
*/
#define	DMA_SADR026	(DMA_CH26_SADR)

/** \brief  2344, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH26_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012344u)

/** Alias (User Manual Name) for DMA_CH26_SDCRCR.
* To use register names with standard convension, please use DMA_CH26_SDCRCR.
*/
#define	DMA_SDCRCR026	(DMA_CH26_SDCRCR)

/** \brief  2358, DMA Channel Shadow Address Register */
#define DMA_CH26_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012358u)

/** Alias (User Manual Name) for DMA_CH26_SHADR.
* To use register names with standard convension, please use DMA_CH26_SHADR.
*/
#define	DMA_SHADR026	(DMA_CH26_SHADR)

/** \brief  2370, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH27_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012370u)

/** Alias (User Manual Name) for DMA_CH27_ADICR.
* To use register names with standard convension, please use DMA_CH27_ADICR.
*/
#define	DMA_ADICR027	(DMA_CH27_ADICR)

/** \brief  2374, DMA Channel Configuration Register */
#define DMA_CH27_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012374u)

/** Alias (User Manual Name) for DMA_CH27_CHCFGR.
* To use register names with standard convension, please use DMA_CH27_CHCFGR.
*/
#define	DMA_CHCFGR027	(DMA_CH27_CHCFGR)

/** \brief  237C, DMARAM Channel Control and Status Register */
#define DMA_CH27_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001237Cu)

/** Alias (User Manual Name) for DMA_CH27_CHCSR.
* To use register names with standard convension, please use DMA_CH27_CHCSR.
*/
#define	DMA_CHCSR027	(DMA_CH27_CHCSR)

/** \brief  236C, DMA Channel Destination Address Register x */
#define DMA_CH27_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001236Cu)

/** Alias (User Manual Name) for DMA_CH27_DADR.
* To use register names with standard convension, please use DMA_CH27_DADR.
*/
#define	DMA_DADR027	(DMA_CH27_DADR)

/** \brief  2360, DMA Channel Read Data CRC Register */
#define DMA_CH27_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012360u)

/** Alias (User Manual Name) for DMA_CH27_RDCRCR.
* To use register names with standard convension, please use DMA_CH27_RDCRCR.
*/
#define	DMA_RDCRCR027	(DMA_CH27_RDCRCR)

/** \brief  2368, DMA Channel Source Address Register */
#define DMA_CH27_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012368u)

/** Alias (User Manual Name) for DMA_CH27_SADR.
* To use register names with standard convension, please use DMA_CH27_SADR.
*/
#define	DMA_SADR027	(DMA_CH27_SADR)

/** \brief  2364, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH27_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012364u)

/** Alias (User Manual Name) for DMA_CH27_SDCRCR.
* To use register names with standard convension, please use DMA_CH27_SDCRCR.
*/
#define	DMA_SDCRCR027	(DMA_CH27_SDCRCR)

/** \brief  2378, DMA Channel Shadow Address Register */
#define DMA_CH27_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012378u)

/** Alias (User Manual Name) for DMA_CH27_SHADR.
* To use register names with standard convension, please use DMA_CH27_SHADR.
*/
#define	DMA_SHADR027	(DMA_CH27_SHADR)

/** \brief  2390, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH28_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012390u)

/** Alias (User Manual Name) for DMA_CH28_ADICR.
* To use register names with standard convension, please use DMA_CH28_ADICR.
*/
#define	DMA_ADICR028	(DMA_CH28_ADICR)

/** \brief  2394, DMA Channel Configuration Register */
#define DMA_CH28_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012394u)

/** Alias (User Manual Name) for DMA_CH28_CHCFGR.
* To use register names with standard convension, please use DMA_CH28_CHCFGR.
*/
#define	DMA_CHCFGR028	(DMA_CH28_CHCFGR)

/** \brief  239C, DMARAM Channel Control and Status Register */
#define DMA_CH28_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001239Cu)

/** Alias (User Manual Name) for DMA_CH28_CHCSR.
* To use register names with standard convension, please use DMA_CH28_CHCSR.
*/
#define	DMA_CHCSR028	(DMA_CH28_CHCSR)

/** \brief  238C, DMA Channel Destination Address Register x */
#define DMA_CH28_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001238Cu)

/** Alias (User Manual Name) for DMA_CH28_DADR.
* To use register names with standard convension, please use DMA_CH28_DADR.
*/
#define	DMA_DADR028	(DMA_CH28_DADR)

/** \brief  2380, DMA Channel Read Data CRC Register */
#define DMA_CH28_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012380u)

/** Alias (User Manual Name) for DMA_CH28_RDCRCR.
* To use register names with standard convension, please use DMA_CH28_RDCRCR.
*/
#define	DMA_RDCRCR028	(DMA_CH28_RDCRCR)

/** \brief  2388, DMA Channel Source Address Register */
#define DMA_CH28_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012388u)

/** Alias (User Manual Name) for DMA_CH28_SADR.
* To use register names with standard convension, please use DMA_CH28_SADR.
*/
#define	DMA_SADR028	(DMA_CH28_SADR)

/** \brief  2384, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH28_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012384u)

/** Alias (User Manual Name) for DMA_CH28_SDCRCR.
* To use register names with standard convension, please use DMA_CH28_SDCRCR.
*/
#define	DMA_SDCRCR028	(DMA_CH28_SDCRCR)

/** \brief  2398, DMA Channel Shadow Address Register */
#define DMA_CH28_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012398u)

/** Alias (User Manual Name) for DMA_CH28_SHADR.
* To use register names with standard convension, please use DMA_CH28_SHADR.
*/
#define	DMA_SHADR028	(DMA_CH28_SHADR)

/** \brief  23B0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH29_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00123B0u)

/** Alias (User Manual Name) for DMA_CH29_ADICR.
* To use register names with standard convension, please use DMA_CH29_ADICR.
*/
#define	DMA_ADICR029	(DMA_CH29_ADICR)

/** \brief  23B4, DMA Channel Configuration Register */
#define DMA_CH29_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00123B4u)

/** Alias (User Manual Name) for DMA_CH29_CHCFGR.
* To use register names with standard convension, please use DMA_CH29_CHCFGR.
*/
#define	DMA_CHCFGR029	(DMA_CH29_CHCFGR)

/** \brief  23BC, DMARAM Channel Control and Status Register */
#define DMA_CH29_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00123BCu)

/** Alias (User Manual Name) for DMA_CH29_CHCSR.
* To use register names with standard convension, please use DMA_CH29_CHCSR.
*/
#define	DMA_CHCSR029	(DMA_CH29_CHCSR)

/** \brief  23AC, DMA Channel Destination Address Register x */
#define DMA_CH29_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00123ACu)

/** Alias (User Manual Name) for DMA_CH29_DADR.
* To use register names with standard convension, please use DMA_CH29_DADR.
*/
#define	DMA_DADR029	(DMA_CH29_DADR)

/** \brief  23A0, DMA Channel Read Data CRC Register */
#define DMA_CH29_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00123A0u)

/** Alias (User Manual Name) for DMA_CH29_RDCRCR.
* To use register names with standard convension, please use DMA_CH29_RDCRCR.
*/
#define	DMA_RDCRCR029	(DMA_CH29_RDCRCR)

/** \brief  23A8, DMA Channel Source Address Register */
#define DMA_CH29_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00123A8u)

/** Alias (User Manual Name) for DMA_CH29_SADR.
* To use register names with standard convension, please use DMA_CH29_SADR.
*/
#define	DMA_SADR029	(DMA_CH29_SADR)

/** \brief  23A4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH29_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00123A4u)

/** Alias (User Manual Name) for DMA_CH29_SDCRCR.
* To use register names with standard convension, please use DMA_CH29_SDCRCR.
*/
#define	DMA_SDCRCR029	(DMA_CH29_SDCRCR)

/** \brief  23B8, DMA Channel Shadow Address Register */
#define DMA_CH29_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00123B8u)

/** Alias (User Manual Name) for DMA_CH29_SHADR.
* To use register names with standard convension, please use DMA_CH29_SHADR.
*/
#define	DMA_SHADR029	(DMA_CH29_SHADR)

/** \brief  2050, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH2_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012050u)

/** Alias (User Manual Name) for DMA_CH2_ADICR.
* To use register names with standard convension, please use DMA_CH2_ADICR.
*/
#define	DMA_ADICR002	(DMA_CH2_ADICR)

/** \brief  2054, DMA Channel Configuration Register */
#define DMA_CH2_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012054u)

/** Alias (User Manual Name) for DMA_CH2_CHCFGR.
* To use register names with standard convension, please use DMA_CH2_CHCFGR.
*/
#define	DMA_CHCFGR002	(DMA_CH2_CHCFGR)

/** \brief  205C, DMARAM Channel Control and Status Register */
#define DMA_CH2_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001205Cu)

/** Alias (User Manual Name) for DMA_CH2_CHCSR.
* To use register names with standard convension, please use DMA_CH2_CHCSR.
*/
#define	DMA_CHCSR002	(DMA_CH2_CHCSR)

/** \brief  204C, DMA Channel Destination Address Register x */
#define DMA_CH2_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001204Cu)

/** Alias (User Manual Name) for DMA_CH2_DADR.
* To use register names with standard convension, please use DMA_CH2_DADR.
*/
#define	DMA_DADR002	(DMA_CH2_DADR)

/** \brief  2040, DMA Channel Read Data CRC Register */
#define DMA_CH2_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012040u)

/** Alias (User Manual Name) for DMA_CH2_RDCRCR.
* To use register names with standard convension, please use DMA_CH2_RDCRCR.
*/
#define	DMA_RDCRCR002	(DMA_CH2_RDCRCR)

/** \brief  2048, DMA Channel Source Address Register */
#define DMA_CH2_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012048u)

/** Alias (User Manual Name) for DMA_CH2_SADR.
* To use register names with standard convension, please use DMA_CH2_SADR.
*/
#define	DMA_SADR002	(DMA_CH2_SADR)

/** \brief  2044, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH2_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012044u)

/** Alias (User Manual Name) for DMA_CH2_SDCRCR.
* To use register names with standard convension, please use DMA_CH2_SDCRCR.
*/
#define	DMA_SDCRCR002	(DMA_CH2_SDCRCR)

/** \brief  2058, DMA Channel Shadow Address Register */
#define DMA_CH2_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012058u)

/** Alias (User Manual Name) for DMA_CH2_SHADR.
* To use register names with standard convension, please use DMA_CH2_SHADR.
*/
#define	DMA_SHADR002	(DMA_CH2_SHADR)

/** \brief  23D0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH30_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00123D0u)

/** Alias (User Manual Name) for DMA_CH30_ADICR.
* To use register names with standard convension, please use DMA_CH30_ADICR.
*/
#define	DMA_ADICR030	(DMA_CH30_ADICR)

/** \brief  23D4, DMA Channel Configuration Register */
#define DMA_CH30_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00123D4u)

/** Alias (User Manual Name) for DMA_CH30_CHCFGR.
* To use register names with standard convension, please use DMA_CH30_CHCFGR.
*/
#define	DMA_CHCFGR030	(DMA_CH30_CHCFGR)

/** \brief  23DC, DMARAM Channel Control and Status Register */
#define DMA_CH30_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00123DCu)

/** Alias (User Manual Name) for DMA_CH30_CHCSR.
* To use register names with standard convension, please use DMA_CH30_CHCSR.
*/
#define	DMA_CHCSR030	(DMA_CH30_CHCSR)

/** \brief  23CC, DMA Channel Destination Address Register x */
#define DMA_CH30_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00123CCu)

/** Alias (User Manual Name) for DMA_CH30_DADR.
* To use register names with standard convension, please use DMA_CH30_DADR.
*/
#define	DMA_DADR030	(DMA_CH30_DADR)

/** \brief  23C0, DMA Channel Read Data CRC Register */
#define DMA_CH30_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00123C0u)

/** Alias (User Manual Name) for DMA_CH30_RDCRCR.
* To use register names with standard convension, please use DMA_CH30_RDCRCR.
*/
#define	DMA_RDCRCR030	(DMA_CH30_RDCRCR)

/** \brief  23C8, DMA Channel Source Address Register */
#define DMA_CH30_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00123C8u)

/** Alias (User Manual Name) for DMA_CH30_SADR.
* To use register names with standard convension, please use DMA_CH30_SADR.
*/
#define	DMA_SADR030	(DMA_CH30_SADR)

/** \brief  23C4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH30_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00123C4u)

/** Alias (User Manual Name) for DMA_CH30_SDCRCR.
* To use register names with standard convension, please use DMA_CH30_SDCRCR.
*/
#define	DMA_SDCRCR030	(DMA_CH30_SDCRCR)

/** \brief  23D8, DMA Channel Shadow Address Register */
#define DMA_CH30_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00123D8u)

/** Alias (User Manual Name) for DMA_CH30_SHADR.
* To use register names with standard convension, please use DMA_CH30_SHADR.
*/
#define	DMA_SHADR030	(DMA_CH30_SHADR)

/** \brief  23F0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH31_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00123F0u)

/** Alias (User Manual Name) for DMA_CH31_ADICR.
* To use register names with standard convension, please use DMA_CH31_ADICR.
*/
#define	DMA_ADICR031	(DMA_CH31_ADICR)

/** \brief  23F4, DMA Channel Configuration Register */
#define DMA_CH31_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00123F4u)

/** Alias (User Manual Name) for DMA_CH31_CHCFGR.
* To use register names with standard convension, please use DMA_CH31_CHCFGR.
*/
#define	DMA_CHCFGR031	(DMA_CH31_CHCFGR)

/** \brief  23FC, DMARAM Channel Control and Status Register */
#define DMA_CH31_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00123FCu)

/** Alias (User Manual Name) for DMA_CH31_CHCSR.
* To use register names with standard convension, please use DMA_CH31_CHCSR.
*/
#define	DMA_CHCSR031	(DMA_CH31_CHCSR)

/** \brief  23EC, DMA Channel Destination Address Register x */
#define DMA_CH31_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00123ECu)

/** Alias (User Manual Name) for DMA_CH31_DADR.
* To use register names with standard convension, please use DMA_CH31_DADR.
*/
#define	DMA_DADR031	(DMA_CH31_DADR)

/** \brief  23E0, DMA Channel Read Data CRC Register */
#define DMA_CH31_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00123E0u)

/** Alias (User Manual Name) for DMA_CH31_RDCRCR.
* To use register names with standard convension, please use DMA_CH31_RDCRCR.
*/
#define	DMA_RDCRCR031	(DMA_CH31_RDCRCR)

/** \brief  23E8, DMA Channel Source Address Register */
#define DMA_CH31_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00123E8u)

/** Alias (User Manual Name) for DMA_CH31_SADR.
* To use register names with standard convension, please use DMA_CH31_SADR.
*/
#define	DMA_SADR031	(DMA_CH31_SADR)

/** \brief  23E4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH31_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00123E4u)

/** Alias (User Manual Name) for DMA_CH31_SDCRCR.
* To use register names with standard convension, please use DMA_CH31_SDCRCR.
*/
#define	DMA_SDCRCR031	(DMA_CH31_SDCRCR)

/** \brief  23F8, DMA Channel Shadow Address Register */
#define DMA_CH31_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00123F8u)

/** Alias (User Manual Name) for DMA_CH31_SHADR.
* To use register names with standard convension, please use DMA_CH31_SHADR.
*/
#define	DMA_SHADR031	(DMA_CH31_SHADR)

/** \brief  2410, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH32_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012410u)

/** Alias (User Manual Name) for DMA_CH32_ADICR.
* To use register names with standard convension, please use DMA_CH32_ADICR.
*/
#define	DMA_ADICR032	(DMA_CH32_ADICR)

/** \brief  2414, DMA Channel Configuration Register */
#define DMA_CH32_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012414u)

/** Alias (User Manual Name) for DMA_CH32_CHCFGR.
* To use register names with standard convension, please use DMA_CH32_CHCFGR.
*/
#define	DMA_CHCFGR032	(DMA_CH32_CHCFGR)

/** \brief  241C, DMARAM Channel Control and Status Register */
#define DMA_CH32_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001241Cu)

/** Alias (User Manual Name) for DMA_CH32_CHCSR.
* To use register names with standard convension, please use DMA_CH32_CHCSR.
*/
#define	DMA_CHCSR032	(DMA_CH32_CHCSR)

/** \brief  240C, DMA Channel Destination Address Register x */
#define DMA_CH32_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001240Cu)

/** Alias (User Manual Name) for DMA_CH32_DADR.
* To use register names with standard convension, please use DMA_CH32_DADR.
*/
#define	DMA_DADR032	(DMA_CH32_DADR)

/** \brief  2400, DMA Channel Read Data CRC Register */
#define DMA_CH32_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012400u)

/** Alias (User Manual Name) for DMA_CH32_RDCRCR.
* To use register names with standard convension, please use DMA_CH32_RDCRCR.
*/
#define	DMA_RDCRCR032	(DMA_CH32_RDCRCR)

/** \brief  2408, DMA Channel Source Address Register */
#define DMA_CH32_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012408u)

/** Alias (User Manual Name) for DMA_CH32_SADR.
* To use register names with standard convension, please use DMA_CH32_SADR.
*/
#define	DMA_SADR032	(DMA_CH32_SADR)

/** \brief  2404, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH32_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012404u)

/** Alias (User Manual Name) for DMA_CH32_SDCRCR.
* To use register names with standard convension, please use DMA_CH32_SDCRCR.
*/
#define	DMA_SDCRCR032	(DMA_CH32_SDCRCR)

/** \brief  2418, DMA Channel Shadow Address Register */
#define DMA_CH32_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012418u)

/** Alias (User Manual Name) for DMA_CH32_SHADR.
* To use register names with standard convension, please use DMA_CH32_SHADR.
*/
#define	DMA_SHADR032	(DMA_CH32_SHADR)

/** \brief  2430, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH33_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012430u)

/** Alias (User Manual Name) for DMA_CH33_ADICR.
* To use register names with standard convension, please use DMA_CH33_ADICR.
*/
#define	DMA_ADICR033	(DMA_CH33_ADICR)

/** \brief  2434, DMA Channel Configuration Register */
#define DMA_CH33_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012434u)

/** Alias (User Manual Name) for DMA_CH33_CHCFGR.
* To use register names with standard convension, please use DMA_CH33_CHCFGR.
*/
#define	DMA_CHCFGR033	(DMA_CH33_CHCFGR)

/** \brief  243C, DMARAM Channel Control and Status Register */
#define DMA_CH33_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001243Cu)

/** Alias (User Manual Name) for DMA_CH33_CHCSR.
* To use register names with standard convension, please use DMA_CH33_CHCSR.
*/
#define	DMA_CHCSR033	(DMA_CH33_CHCSR)

/** \brief  242C, DMA Channel Destination Address Register x */
#define DMA_CH33_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001242Cu)

/** Alias (User Manual Name) for DMA_CH33_DADR.
* To use register names with standard convension, please use DMA_CH33_DADR.
*/
#define	DMA_DADR033	(DMA_CH33_DADR)

/** \brief  2420, DMA Channel Read Data CRC Register */
#define DMA_CH33_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012420u)

/** Alias (User Manual Name) for DMA_CH33_RDCRCR.
* To use register names with standard convension, please use DMA_CH33_RDCRCR.
*/
#define	DMA_RDCRCR033	(DMA_CH33_RDCRCR)

/** \brief  2428, DMA Channel Source Address Register */
#define DMA_CH33_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012428u)

/** Alias (User Manual Name) for DMA_CH33_SADR.
* To use register names with standard convension, please use DMA_CH33_SADR.
*/
#define	DMA_SADR033	(DMA_CH33_SADR)

/** \brief  2424, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH33_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012424u)

/** Alias (User Manual Name) for DMA_CH33_SDCRCR.
* To use register names with standard convension, please use DMA_CH33_SDCRCR.
*/
#define	DMA_SDCRCR033	(DMA_CH33_SDCRCR)

/** \brief  2438, DMA Channel Shadow Address Register */
#define DMA_CH33_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012438u)

/** Alias (User Manual Name) for DMA_CH33_SHADR.
* To use register names with standard convension, please use DMA_CH33_SHADR.
*/
#define	DMA_SHADR033	(DMA_CH33_SHADR)

/** \brief  2450, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH34_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012450u)

/** Alias (User Manual Name) for DMA_CH34_ADICR.
* To use register names with standard convension, please use DMA_CH34_ADICR.
*/
#define	DMA_ADICR034	(DMA_CH34_ADICR)

/** \brief  2454, DMA Channel Configuration Register */
#define DMA_CH34_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012454u)

/** Alias (User Manual Name) for DMA_CH34_CHCFGR.
* To use register names with standard convension, please use DMA_CH34_CHCFGR.
*/
#define	DMA_CHCFGR034	(DMA_CH34_CHCFGR)

/** \brief  245C, DMARAM Channel Control and Status Register */
#define DMA_CH34_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001245Cu)

/** Alias (User Manual Name) for DMA_CH34_CHCSR.
* To use register names with standard convension, please use DMA_CH34_CHCSR.
*/
#define	DMA_CHCSR034	(DMA_CH34_CHCSR)

/** \brief  244C, DMA Channel Destination Address Register x */
#define DMA_CH34_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001244Cu)

/** Alias (User Manual Name) for DMA_CH34_DADR.
* To use register names with standard convension, please use DMA_CH34_DADR.
*/
#define	DMA_DADR034	(DMA_CH34_DADR)

/** \brief  2440, DMA Channel Read Data CRC Register */
#define DMA_CH34_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012440u)

/** Alias (User Manual Name) for DMA_CH34_RDCRCR.
* To use register names with standard convension, please use DMA_CH34_RDCRCR.
*/
#define	DMA_RDCRCR034	(DMA_CH34_RDCRCR)

/** \brief  2448, DMA Channel Source Address Register */
#define DMA_CH34_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012448u)

/** Alias (User Manual Name) for DMA_CH34_SADR.
* To use register names with standard convension, please use DMA_CH34_SADR.
*/
#define	DMA_SADR034	(DMA_CH34_SADR)

/** \brief  2444, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH34_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012444u)

/** Alias (User Manual Name) for DMA_CH34_SDCRCR.
* To use register names with standard convension, please use DMA_CH34_SDCRCR.
*/
#define	DMA_SDCRCR034	(DMA_CH34_SDCRCR)

/** \brief  2458, DMA Channel Shadow Address Register */
#define DMA_CH34_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012458u)

/** Alias (User Manual Name) for DMA_CH34_SHADR.
* To use register names with standard convension, please use DMA_CH34_SHADR.
*/
#define	DMA_SHADR034	(DMA_CH34_SHADR)

/** \brief  2470, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH35_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012470u)

/** Alias (User Manual Name) for DMA_CH35_ADICR.
* To use register names with standard convension, please use DMA_CH35_ADICR.
*/
#define	DMA_ADICR035	(DMA_CH35_ADICR)

/** \brief  2474, DMA Channel Configuration Register */
#define DMA_CH35_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012474u)

/** Alias (User Manual Name) for DMA_CH35_CHCFGR.
* To use register names with standard convension, please use DMA_CH35_CHCFGR.
*/
#define	DMA_CHCFGR035	(DMA_CH35_CHCFGR)

/** \brief  247C, DMARAM Channel Control and Status Register */
#define DMA_CH35_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001247Cu)

/** Alias (User Manual Name) for DMA_CH35_CHCSR.
* To use register names with standard convension, please use DMA_CH35_CHCSR.
*/
#define	DMA_CHCSR035	(DMA_CH35_CHCSR)

/** \brief  246C, DMA Channel Destination Address Register x */
#define DMA_CH35_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001246Cu)

/** Alias (User Manual Name) for DMA_CH35_DADR.
* To use register names with standard convension, please use DMA_CH35_DADR.
*/
#define	DMA_DADR035	(DMA_CH35_DADR)

/** \brief  2460, DMA Channel Read Data CRC Register */
#define DMA_CH35_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012460u)

/** Alias (User Manual Name) for DMA_CH35_RDCRCR.
* To use register names with standard convension, please use DMA_CH35_RDCRCR.
*/
#define	DMA_RDCRCR035	(DMA_CH35_RDCRCR)

/** \brief  2468, DMA Channel Source Address Register */
#define DMA_CH35_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012468u)

/** Alias (User Manual Name) for DMA_CH35_SADR.
* To use register names with standard convension, please use DMA_CH35_SADR.
*/
#define	DMA_SADR035	(DMA_CH35_SADR)

/** \brief  2464, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH35_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012464u)

/** Alias (User Manual Name) for DMA_CH35_SDCRCR.
* To use register names with standard convension, please use DMA_CH35_SDCRCR.
*/
#define	DMA_SDCRCR035	(DMA_CH35_SDCRCR)

/** \brief  2478, DMA Channel Shadow Address Register */
#define DMA_CH35_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012478u)

/** Alias (User Manual Name) for DMA_CH35_SHADR.
* To use register names with standard convension, please use DMA_CH35_SHADR.
*/
#define	DMA_SHADR035	(DMA_CH35_SHADR)

/** \brief  2490, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH36_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012490u)

/** Alias (User Manual Name) for DMA_CH36_ADICR.
* To use register names with standard convension, please use DMA_CH36_ADICR.
*/
#define	DMA_ADICR036	(DMA_CH36_ADICR)

/** \brief  2494, DMA Channel Configuration Register */
#define DMA_CH36_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012494u)

/** Alias (User Manual Name) for DMA_CH36_CHCFGR.
* To use register names with standard convension, please use DMA_CH36_CHCFGR.
*/
#define	DMA_CHCFGR036	(DMA_CH36_CHCFGR)

/** \brief  249C, DMARAM Channel Control and Status Register */
#define DMA_CH36_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001249Cu)

/** Alias (User Manual Name) for DMA_CH36_CHCSR.
* To use register names with standard convension, please use DMA_CH36_CHCSR.
*/
#define	DMA_CHCSR036	(DMA_CH36_CHCSR)

/** \brief  248C, DMA Channel Destination Address Register x */
#define DMA_CH36_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001248Cu)

/** Alias (User Manual Name) for DMA_CH36_DADR.
* To use register names with standard convension, please use DMA_CH36_DADR.
*/
#define	DMA_DADR036	(DMA_CH36_DADR)

/** \brief  2480, DMA Channel Read Data CRC Register */
#define DMA_CH36_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012480u)

/** Alias (User Manual Name) for DMA_CH36_RDCRCR.
* To use register names with standard convension, please use DMA_CH36_RDCRCR.
*/
#define	DMA_RDCRCR036	(DMA_CH36_RDCRCR)

/** \brief  2488, DMA Channel Source Address Register */
#define DMA_CH36_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012488u)

/** Alias (User Manual Name) for DMA_CH36_SADR.
* To use register names with standard convension, please use DMA_CH36_SADR.
*/
#define	DMA_SADR036	(DMA_CH36_SADR)

/** \brief  2484, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH36_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012484u)

/** Alias (User Manual Name) for DMA_CH36_SDCRCR.
* To use register names with standard convension, please use DMA_CH36_SDCRCR.
*/
#define	DMA_SDCRCR036	(DMA_CH36_SDCRCR)

/** \brief  2498, DMA Channel Shadow Address Register */
#define DMA_CH36_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012498u)

/** Alias (User Manual Name) for DMA_CH36_SHADR.
* To use register names with standard convension, please use DMA_CH36_SHADR.
*/
#define	DMA_SHADR036	(DMA_CH36_SHADR)

/** \brief  24B0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH37_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00124B0u)

/** Alias (User Manual Name) for DMA_CH37_ADICR.
* To use register names with standard convension, please use DMA_CH37_ADICR.
*/
#define	DMA_ADICR037	(DMA_CH37_ADICR)

/** \brief  24B4, DMA Channel Configuration Register */
#define DMA_CH37_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00124B4u)

/** Alias (User Manual Name) for DMA_CH37_CHCFGR.
* To use register names with standard convension, please use DMA_CH37_CHCFGR.
*/
#define	DMA_CHCFGR037	(DMA_CH37_CHCFGR)

/** \brief  24BC, DMARAM Channel Control and Status Register */
#define DMA_CH37_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00124BCu)

/** Alias (User Manual Name) for DMA_CH37_CHCSR.
* To use register names with standard convension, please use DMA_CH37_CHCSR.
*/
#define	DMA_CHCSR037	(DMA_CH37_CHCSR)

/** \brief  24AC, DMA Channel Destination Address Register x */
#define DMA_CH37_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00124ACu)

/** Alias (User Manual Name) for DMA_CH37_DADR.
* To use register names with standard convension, please use DMA_CH37_DADR.
*/
#define	DMA_DADR037	(DMA_CH37_DADR)

/** \brief  24A0, DMA Channel Read Data CRC Register */
#define DMA_CH37_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00124A0u)

/** Alias (User Manual Name) for DMA_CH37_RDCRCR.
* To use register names with standard convension, please use DMA_CH37_RDCRCR.
*/
#define	DMA_RDCRCR037	(DMA_CH37_RDCRCR)

/** \brief  24A8, DMA Channel Source Address Register */
#define DMA_CH37_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00124A8u)

/** Alias (User Manual Name) for DMA_CH37_SADR.
* To use register names with standard convension, please use DMA_CH37_SADR.
*/
#define	DMA_SADR037	(DMA_CH37_SADR)

/** \brief  24A4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH37_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00124A4u)

/** Alias (User Manual Name) for DMA_CH37_SDCRCR.
* To use register names with standard convension, please use DMA_CH37_SDCRCR.
*/
#define	DMA_SDCRCR037	(DMA_CH37_SDCRCR)

/** \brief  24B8, DMA Channel Shadow Address Register */
#define DMA_CH37_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00124B8u)

/** Alias (User Manual Name) for DMA_CH37_SHADR.
* To use register names with standard convension, please use DMA_CH37_SHADR.
*/
#define	DMA_SHADR037	(DMA_CH37_SHADR)

/** \brief  24D0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH38_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00124D0u)

/** Alias (User Manual Name) for DMA_CH38_ADICR.
* To use register names with standard convension, please use DMA_CH38_ADICR.
*/
#define	DMA_ADICR038	(DMA_CH38_ADICR)

/** \brief  24D4, DMA Channel Configuration Register */
#define DMA_CH38_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00124D4u)

/** Alias (User Manual Name) for DMA_CH38_CHCFGR.
* To use register names with standard convension, please use DMA_CH38_CHCFGR.
*/
#define	DMA_CHCFGR038	(DMA_CH38_CHCFGR)

/** \brief  24DC, DMARAM Channel Control and Status Register */
#define DMA_CH38_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00124DCu)

/** Alias (User Manual Name) for DMA_CH38_CHCSR.
* To use register names with standard convension, please use DMA_CH38_CHCSR.
*/
#define	DMA_CHCSR038	(DMA_CH38_CHCSR)

/** \brief  24CC, DMA Channel Destination Address Register x */
#define DMA_CH38_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00124CCu)

/** Alias (User Manual Name) for DMA_CH38_DADR.
* To use register names with standard convension, please use DMA_CH38_DADR.
*/
#define	DMA_DADR038	(DMA_CH38_DADR)

/** \brief  24C0, DMA Channel Read Data CRC Register */
#define DMA_CH38_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00124C0u)

/** Alias (User Manual Name) for DMA_CH38_RDCRCR.
* To use register names with standard convension, please use DMA_CH38_RDCRCR.
*/
#define	DMA_RDCRCR038	(DMA_CH38_RDCRCR)

/** \brief  24C8, DMA Channel Source Address Register */
#define DMA_CH38_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00124C8u)

/** Alias (User Manual Name) for DMA_CH38_SADR.
* To use register names with standard convension, please use DMA_CH38_SADR.
*/
#define	DMA_SADR038	(DMA_CH38_SADR)

/** \brief  24C4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH38_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00124C4u)

/** Alias (User Manual Name) for DMA_CH38_SDCRCR.
* To use register names with standard convension, please use DMA_CH38_SDCRCR.
*/
#define	DMA_SDCRCR038	(DMA_CH38_SDCRCR)

/** \brief  24D8, DMA Channel Shadow Address Register */
#define DMA_CH38_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00124D8u)

/** Alias (User Manual Name) for DMA_CH38_SHADR.
* To use register names with standard convension, please use DMA_CH38_SHADR.
*/
#define	DMA_SHADR038	(DMA_CH38_SHADR)

/** \brief  24F0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH39_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00124F0u)

/** Alias (User Manual Name) for DMA_CH39_ADICR.
* To use register names with standard convension, please use DMA_CH39_ADICR.
*/
#define	DMA_ADICR039	(DMA_CH39_ADICR)

/** \brief  24F4, DMA Channel Configuration Register */
#define DMA_CH39_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00124F4u)

/** Alias (User Manual Name) for DMA_CH39_CHCFGR.
* To use register names with standard convension, please use DMA_CH39_CHCFGR.
*/
#define	DMA_CHCFGR039	(DMA_CH39_CHCFGR)

/** \brief  24FC, DMARAM Channel Control and Status Register */
#define DMA_CH39_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00124FCu)

/** Alias (User Manual Name) for DMA_CH39_CHCSR.
* To use register names with standard convension, please use DMA_CH39_CHCSR.
*/
#define	DMA_CHCSR039	(DMA_CH39_CHCSR)

/** \brief  24EC, DMA Channel Destination Address Register x */
#define DMA_CH39_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00124ECu)

/** Alias (User Manual Name) for DMA_CH39_DADR.
* To use register names with standard convension, please use DMA_CH39_DADR.
*/
#define	DMA_DADR039	(DMA_CH39_DADR)

/** \brief  24E0, DMA Channel Read Data CRC Register */
#define DMA_CH39_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00124E0u)

/** Alias (User Manual Name) for DMA_CH39_RDCRCR.
* To use register names with standard convension, please use DMA_CH39_RDCRCR.
*/
#define	DMA_RDCRCR039	(DMA_CH39_RDCRCR)

/** \brief  24E8, DMA Channel Source Address Register */
#define DMA_CH39_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00124E8u)

/** Alias (User Manual Name) for DMA_CH39_SADR.
* To use register names with standard convension, please use DMA_CH39_SADR.
*/
#define	DMA_SADR039	(DMA_CH39_SADR)

/** \brief  24E4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH39_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00124E4u)

/** Alias (User Manual Name) for DMA_CH39_SDCRCR.
* To use register names with standard convension, please use DMA_CH39_SDCRCR.
*/
#define	DMA_SDCRCR039	(DMA_CH39_SDCRCR)

/** \brief  24F8, DMA Channel Shadow Address Register */
#define DMA_CH39_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00124F8u)

/** Alias (User Manual Name) for DMA_CH39_SHADR.
* To use register names with standard convension, please use DMA_CH39_SHADR.
*/
#define	DMA_SHADR039	(DMA_CH39_SHADR)

/** \brief  2070, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH3_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012070u)

/** Alias (User Manual Name) for DMA_CH3_ADICR.
* To use register names with standard convension, please use DMA_CH3_ADICR.
*/
#define	DMA_ADICR003	(DMA_CH3_ADICR)

/** \brief  2074, DMA Channel Configuration Register */
#define DMA_CH3_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012074u)

/** Alias (User Manual Name) for DMA_CH3_CHCFGR.
* To use register names with standard convension, please use DMA_CH3_CHCFGR.
*/
#define	DMA_CHCFGR003	(DMA_CH3_CHCFGR)

/** \brief  207C, DMARAM Channel Control and Status Register */
#define DMA_CH3_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001207Cu)

/** Alias (User Manual Name) for DMA_CH3_CHCSR.
* To use register names with standard convension, please use DMA_CH3_CHCSR.
*/
#define	DMA_CHCSR003	(DMA_CH3_CHCSR)

/** \brief  206C, DMA Channel Destination Address Register x */
#define DMA_CH3_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001206Cu)

/** Alias (User Manual Name) for DMA_CH3_DADR.
* To use register names with standard convension, please use DMA_CH3_DADR.
*/
#define	DMA_DADR003	(DMA_CH3_DADR)

/** \brief  2060, DMA Channel Read Data CRC Register */
#define DMA_CH3_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012060u)

/** Alias (User Manual Name) for DMA_CH3_RDCRCR.
* To use register names with standard convension, please use DMA_CH3_RDCRCR.
*/
#define	DMA_RDCRCR003	(DMA_CH3_RDCRCR)

/** \brief  2068, DMA Channel Source Address Register */
#define DMA_CH3_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012068u)

/** Alias (User Manual Name) for DMA_CH3_SADR.
* To use register names with standard convension, please use DMA_CH3_SADR.
*/
#define	DMA_SADR003	(DMA_CH3_SADR)

/** \brief  2064, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH3_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012064u)

/** Alias (User Manual Name) for DMA_CH3_SDCRCR.
* To use register names with standard convension, please use DMA_CH3_SDCRCR.
*/
#define	DMA_SDCRCR003	(DMA_CH3_SDCRCR)

/** \brief  2078, DMA Channel Shadow Address Register */
#define DMA_CH3_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012078u)

/** Alias (User Manual Name) for DMA_CH3_SHADR.
* To use register names with standard convension, please use DMA_CH3_SHADR.
*/
#define	DMA_SHADR003	(DMA_CH3_SHADR)

/** \brief  2510, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH40_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012510u)

/** Alias (User Manual Name) for DMA_CH40_ADICR.
* To use register names with standard convension, please use DMA_CH40_ADICR.
*/
#define	DMA_ADICR040	(DMA_CH40_ADICR)

/** \brief  2514, DMA Channel Configuration Register */
#define DMA_CH40_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012514u)

/** Alias (User Manual Name) for DMA_CH40_CHCFGR.
* To use register names with standard convension, please use DMA_CH40_CHCFGR.
*/
#define	DMA_CHCFGR040	(DMA_CH40_CHCFGR)

/** \brief  251C, DMARAM Channel Control and Status Register */
#define DMA_CH40_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001251Cu)

/** Alias (User Manual Name) for DMA_CH40_CHCSR.
* To use register names with standard convension, please use DMA_CH40_CHCSR.
*/
#define	DMA_CHCSR040	(DMA_CH40_CHCSR)

/** \brief  250C, DMA Channel Destination Address Register x */
#define DMA_CH40_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001250Cu)

/** Alias (User Manual Name) for DMA_CH40_DADR.
* To use register names with standard convension, please use DMA_CH40_DADR.
*/
#define	DMA_DADR040	(DMA_CH40_DADR)

/** \brief  2500, DMA Channel Read Data CRC Register */
#define DMA_CH40_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012500u)

/** Alias (User Manual Name) for DMA_CH40_RDCRCR.
* To use register names with standard convension, please use DMA_CH40_RDCRCR.
*/
#define	DMA_RDCRCR040	(DMA_CH40_RDCRCR)

/** \brief  2508, DMA Channel Source Address Register */
#define DMA_CH40_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012508u)

/** Alias (User Manual Name) for DMA_CH40_SADR.
* To use register names with standard convension, please use DMA_CH40_SADR.
*/
#define	DMA_SADR040	(DMA_CH40_SADR)

/** \brief  2504, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH40_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012504u)

/** Alias (User Manual Name) for DMA_CH40_SDCRCR.
* To use register names with standard convension, please use DMA_CH40_SDCRCR.
*/
#define	DMA_SDCRCR040	(DMA_CH40_SDCRCR)

/** \brief  2518, DMA Channel Shadow Address Register */
#define DMA_CH40_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012518u)

/** Alias (User Manual Name) for DMA_CH40_SHADR.
* To use register names with standard convension, please use DMA_CH40_SHADR.
*/
#define	DMA_SHADR040	(DMA_CH40_SHADR)

/** \brief  2530, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH41_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012530u)

/** Alias (User Manual Name) for DMA_CH41_ADICR.
* To use register names with standard convension, please use DMA_CH41_ADICR.
*/
#define	DMA_ADICR041	(DMA_CH41_ADICR)

/** \brief  2534, DMA Channel Configuration Register */
#define DMA_CH41_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012534u)

/** Alias (User Manual Name) for DMA_CH41_CHCFGR.
* To use register names with standard convension, please use DMA_CH41_CHCFGR.
*/
#define	DMA_CHCFGR041	(DMA_CH41_CHCFGR)

/** \brief  253C, DMARAM Channel Control and Status Register */
#define DMA_CH41_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001253Cu)

/** Alias (User Manual Name) for DMA_CH41_CHCSR.
* To use register names with standard convension, please use DMA_CH41_CHCSR.
*/
#define	DMA_CHCSR041	(DMA_CH41_CHCSR)

/** \brief  252C, DMA Channel Destination Address Register x */
#define DMA_CH41_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001252Cu)

/** Alias (User Manual Name) for DMA_CH41_DADR.
* To use register names with standard convension, please use DMA_CH41_DADR.
*/
#define	DMA_DADR041	(DMA_CH41_DADR)

/** \brief  2520, DMA Channel Read Data CRC Register */
#define DMA_CH41_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012520u)

/** Alias (User Manual Name) for DMA_CH41_RDCRCR.
* To use register names with standard convension, please use DMA_CH41_RDCRCR.
*/
#define	DMA_RDCRCR041	(DMA_CH41_RDCRCR)

/** \brief  2528, DMA Channel Source Address Register */
#define DMA_CH41_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012528u)

/** Alias (User Manual Name) for DMA_CH41_SADR.
* To use register names with standard convension, please use DMA_CH41_SADR.
*/
#define	DMA_SADR041	(DMA_CH41_SADR)

/** \brief  2524, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH41_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012524u)

/** Alias (User Manual Name) for DMA_CH41_SDCRCR.
* To use register names with standard convension, please use DMA_CH41_SDCRCR.
*/
#define	DMA_SDCRCR041	(DMA_CH41_SDCRCR)

/** \brief  2538, DMA Channel Shadow Address Register */
#define DMA_CH41_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012538u)

/** Alias (User Manual Name) for DMA_CH41_SHADR.
* To use register names with standard convension, please use DMA_CH41_SHADR.
*/
#define	DMA_SHADR041	(DMA_CH41_SHADR)

/** \brief  2550, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH42_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012550u)

/** Alias (User Manual Name) for DMA_CH42_ADICR.
* To use register names with standard convension, please use DMA_CH42_ADICR.
*/
#define	DMA_ADICR042	(DMA_CH42_ADICR)

/** \brief  2554, DMA Channel Configuration Register */
#define DMA_CH42_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012554u)

/** Alias (User Manual Name) for DMA_CH42_CHCFGR.
* To use register names with standard convension, please use DMA_CH42_CHCFGR.
*/
#define	DMA_CHCFGR042	(DMA_CH42_CHCFGR)

/** \brief  255C, DMARAM Channel Control and Status Register */
#define DMA_CH42_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001255Cu)

/** Alias (User Manual Name) for DMA_CH42_CHCSR.
* To use register names with standard convension, please use DMA_CH42_CHCSR.
*/
#define	DMA_CHCSR042	(DMA_CH42_CHCSR)

/** \brief  254C, DMA Channel Destination Address Register x */
#define DMA_CH42_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001254Cu)

/** Alias (User Manual Name) for DMA_CH42_DADR.
* To use register names with standard convension, please use DMA_CH42_DADR.
*/
#define	DMA_DADR042	(DMA_CH42_DADR)

/** \brief  2540, DMA Channel Read Data CRC Register */
#define DMA_CH42_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012540u)

/** Alias (User Manual Name) for DMA_CH42_RDCRCR.
* To use register names with standard convension, please use DMA_CH42_RDCRCR.
*/
#define	DMA_RDCRCR042	(DMA_CH42_RDCRCR)

/** \brief  2548, DMA Channel Source Address Register */
#define DMA_CH42_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012548u)

/** Alias (User Manual Name) for DMA_CH42_SADR.
* To use register names with standard convension, please use DMA_CH42_SADR.
*/
#define	DMA_SADR042	(DMA_CH42_SADR)

/** \brief  2544, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH42_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012544u)

/** Alias (User Manual Name) for DMA_CH42_SDCRCR.
* To use register names with standard convension, please use DMA_CH42_SDCRCR.
*/
#define	DMA_SDCRCR042	(DMA_CH42_SDCRCR)

/** \brief  2558, DMA Channel Shadow Address Register */
#define DMA_CH42_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012558u)

/** Alias (User Manual Name) for DMA_CH42_SHADR.
* To use register names with standard convension, please use DMA_CH42_SHADR.
*/
#define	DMA_SHADR042	(DMA_CH42_SHADR)

/** \brief  2570, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH43_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012570u)

/** Alias (User Manual Name) for DMA_CH43_ADICR.
* To use register names with standard convension, please use DMA_CH43_ADICR.
*/
#define	DMA_ADICR043	(DMA_CH43_ADICR)

/** \brief  2574, DMA Channel Configuration Register */
#define DMA_CH43_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012574u)

/** Alias (User Manual Name) for DMA_CH43_CHCFGR.
* To use register names with standard convension, please use DMA_CH43_CHCFGR.
*/
#define	DMA_CHCFGR043	(DMA_CH43_CHCFGR)

/** \brief  257C, DMARAM Channel Control and Status Register */
#define DMA_CH43_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001257Cu)

/** Alias (User Manual Name) for DMA_CH43_CHCSR.
* To use register names with standard convension, please use DMA_CH43_CHCSR.
*/
#define	DMA_CHCSR043	(DMA_CH43_CHCSR)

/** \brief  256C, DMA Channel Destination Address Register x */
#define DMA_CH43_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001256Cu)

/** Alias (User Manual Name) for DMA_CH43_DADR.
* To use register names with standard convension, please use DMA_CH43_DADR.
*/
#define	DMA_DADR043	(DMA_CH43_DADR)

/** \brief  2560, DMA Channel Read Data CRC Register */
#define DMA_CH43_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012560u)

/** Alias (User Manual Name) for DMA_CH43_RDCRCR.
* To use register names with standard convension, please use DMA_CH43_RDCRCR.
*/
#define	DMA_RDCRCR043	(DMA_CH43_RDCRCR)

/** \brief  2568, DMA Channel Source Address Register */
#define DMA_CH43_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012568u)

/** Alias (User Manual Name) for DMA_CH43_SADR.
* To use register names with standard convension, please use DMA_CH43_SADR.
*/
#define	DMA_SADR043	(DMA_CH43_SADR)

/** \brief  2564, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH43_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012564u)

/** Alias (User Manual Name) for DMA_CH43_SDCRCR.
* To use register names with standard convension, please use DMA_CH43_SDCRCR.
*/
#define	DMA_SDCRCR043	(DMA_CH43_SDCRCR)

/** \brief  2578, DMA Channel Shadow Address Register */
#define DMA_CH43_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012578u)

/** Alias (User Manual Name) for DMA_CH43_SHADR.
* To use register names with standard convension, please use DMA_CH43_SHADR.
*/
#define	DMA_SHADR043	(DMA_CH43_SHADR)

/** \brief  2590, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH44_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012590u)

/** Alias (User Manual Name) for DMA_CH44_ADICR.
* To use register names with standard convension, please use DMA_CH44_ADICR.
*/
#define	DMA_ADICR044	(DMA_CH44_ADICR)

/** \brief  2594, DMA Channel Configuration Register */
#define DMA_CH44_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012594u)

/** Alias (User Manual Name) for DMA_CH44_CHCFGR.
* To use register names with standard convension, please use DMA_CH44_CHCFGR.
*/
#define	DMA_CHCFGR044	(DMA_CH44_CHCFGR)

/** \brief  259C, DMARAM Channel Control and Status Register */
#define DMA_CH44_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001259Cu)

/** Alias (User Manual Name) for DMA_CH44_CHCSR.
* To use register names with standard convension, please use DMA_CH44_CHCSR.
*/
#define	DMA_CHCSR044	(DMA_CH44_CHCSR)

/** \brief  258C, DMA Channel Destination Address Register x */
#define DMA_CH44_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001258Cu)

/** Alias (User Manual Name) for DMA_CH44_DADR.
* To use register names with standard convension, please use DMA_CH44_DADR.
*/
#define	DMA_DADR044	(DMA_CH44_DADR)

/** \brief  2580, DMA Channel Read Data CRC Register */
#define DMA_CH44_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012580u)

/** Alias (User Manual Name) for DMA_CH44_RDCRCR.
* To use register names with standard convension, please use DMA_CH44_RDCRCR.
*/
#define	DMA_RDCRCR044	(DMA_CH44_RDCRCR)

/** \brief  2588, DMA Channel Source Address Register */
#define DMA_CH44_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012588u)

/** Alias (User Manual Name) for DMA_CH44_SADR.
* To use register names with standard convension, please use DMA_CH44_SADR.
*/
#define	DMA_SADR044	(DMA_CH44_SADR)

/** \brief  2584, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH44_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012584u)

/** Alias (User Manual Name) for DMA_CH44_SDCRCR.
* To use register names with standard convension, please use DMA_CH44_SDCRCR.
*/
#define	DMA_SDCRCR044	(DMA_CH44_SDCRCR)

/** \brief  2598, DMA Channel Shadow Address Register */
#define DMA_CH44_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012598u)

/** Alias (User Manual Name) for DMA_CH44_SHADR.
* To use register names with standard convension, please use DMA_CH44_SHADR.
*/
#define	DMA_SHADR044	(DMA_CH44_SHADR)

/** \brief  25B0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH45_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00125B0u)

/** Alias (User Manual Name) for DMA_CH45_ADICR.
* To use register names with standard convension, please use DMA_CH45_ADICR.
*/
#define	DMA_ADICR045	(DMA_CH45_ADICR)

/** \brief  25B4, DMA Channel Configuration Register */
#define DMA_CH45_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00125B4u)

/** Alias (User Manual Name) for DMA_CH45_CHCFGR.
* To use register names with standard convension, please use DMA_CH45_CHCFGR.
*/
#define	DMA_CHCFGR045	(DMA_CH45_CHCFGR)

/** \brief  25BC, DMARAM Channel Control and Status Register */
#define DMA_CH45_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00125BCu)

/** Alias (User Manual Name) for DMA_CH45_CHCSR.
* To use register names with standard convension, please use DMA_CH45_CHCSR.
*/
#define	DMA_CHCSR045	(DMA_CH45_CHCSR)

/** \brief  25AC, DMA Channel Destination Address Register x */
#define DMA_CH45_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00125ACu)

/** Alias (User Manual Name) for DMA_CH45_DADR.
* To use register names with standard convension, please use DMA_CH45_DADR.
*/
#define	DMA_DADR045	(DMA_CH45_DADR)

/** \brief  25A0, DMA Channel Read Data CRC Register */
#define DMA_CH45_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00125A0u)

/** Alias (User Manual Name) for DMA_CH45_RDCRCR.
* To use register names with standard convension, please use DMA_CH45_RDCRCR.
*/
#define	DMA_RDCRCR045	(DMA_CH45_RDCRCR)

/** \brief  25A8, DMA Channel Source Address Register */
#define DMA_CH45_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00125A8u)

/** Alias (User Manual Name) for DMA_CH45_SADR.
* To use register names with standard convension, please use DMA_CH45_SADR.
*/
#define	DMA_SADR045	(DMA_CH45_SADR)

/** \brief  25A4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH45_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00125A4u)

/** Alias (User Manual Name) for DMA_CH45_SDCRCR.
* To use register names with standard convension, please use DMA_CH45_SDCRCR.
*/
#define	DMA_SDCRCR045	(DMA_CH45_SDCRCR)

/** \brief  25B8, DMA Channel Shadow Address Register */
#define DMA_CH45_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00125B8u)

/** Alias (User Manual Name) for DMA_CH45_SHADR.
* To use register names with standard convension, please use DMA_CH45_SHADR.
*/
#define	DMA_SHADR045	(DMA_CH45_SHADR)

/** \brief  25D0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH46_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00125D0u)

/** Alias (User Manual Name) for DMA_CH46_ADICR.
* To use register names with standard convension, please use DMA_CH46_ADICR.
*/
#define	DMA_ADICR046	(DMA_CH46_ADICR)

/** \brief  25D4, DMA Channel Configuration Register */
#define DMA_CH46_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00125D4u)

/** Alias (User Manual Name) for DMA_CH46_CHCFGR.
* To use register names with standard convension, please use DMA_CH46_CHCFGR.
*/
#define	DMA_CHCFGR046	(DMA_CH46_CHCFGR)

/** \brief  25DC, DMARAM Channel Control and Status Register */
#define DMA_CH46_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00125DCu)

/** Alias (User Manual Name) for DMA_CH46_CHCSR.
* To use register names with standard convension, please use DMA_CH46_CHCSR.
*/
#define	DMA_CHCSR046	(DMA_CH46_CHCSR)

/** \brief  25CC, DMA Channel Destination Address Register x */
#define DMA_CH46_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00125CCu)

/** Alias (User Manual Name) for DMA_CH46_DADR.
* To use register names with standard convension, please use DMA_CH46_DADR.
*/
#define	DMA_DADR046	(DMA_CH46_DADR)

/** \brief  25C0, DMA Channel Read Data CRC Register */
#define DMA_CH46_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00125C0u)

/** Alias (User Manual Name) for DMA_CH46_RDCRCR.
* To use register names with standard convension, please use DMA_CH46_RDCRCR.
*/
#define	DMA_RDCRCR046	(DMA_CH46_RDCRCR)

/** \brief  25C8, DMA Channel Source Address Register */
#define DMA_CH46_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00125C8u)

/** Alias (User Manual Name) for DMA_CH46_SADR.
* To use register names with standard convension, please use DMA_CH46_SADR.
*/
#define	DMA_SADR046	(DMA_CH46_SADR)

/** \brief  25C4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH46_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00125C4u)

/** Alias (User Manual Name) for DMA_CH46_SDCRCR.
* To use register names with standard convension, please use DMA_CH46_SDCRCR.
*/
#define	DMA_SDCRCR046	(DMA_CH46_SDCRCR)

/** \brief  25D8, DMA Channel Shadow Address Register */
#define DMA_CH46_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00125D8u)

/** Alias (User Manual Name) for DMA_CH46_SHADR.
* To use register names with standard convension, please use DMA_CH46_SHADR.
*/
#define	DMA_SHADR046	(DMA_CH46_SHADR)

/** \brief  25F0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH47_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00125F0u)

/** Alias (User Manual Name) for DMA_CH47_ADICR.
* To use register names with standard convension, please use DMA_CH47_ADICR.
*/
#define	DMA_ADICR047	(DMA_CH47_ADICR)

/** \brief  25F4, DMA Channel Configuration Register */
#define DMA_CH47_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00125F4u)

/** Alias (User Manual Name) for DMA_CH47_CHCFGR.
* To use register names with standard convension, please use DMA_CH47_CHCFGR.
*/
#define	DMA_CHCFGR047	(DMA_CH47_CHCFGR)

/** \brief  25FC, DMARAM Channel Control and Status Register */
#define DMA_CH47_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00125FCu)

/** Alias (User Manual Name) for DMA_CH47_CHCSR.
* To use register names with standard convension, please use DMA_CH47_CHCSR.
*/
#define	DMA_CHCSR047	(DMA_CH47_CHCSR)

/** \brief  25EC, DMA Channel Destination Address Register x */
#define DMA_CH47_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00125ECu)

/** Alias (User Manual Name) for DMA_CH47_DADR.
* To use register names with standard convension, please use DMA_CH47_DADR.
*/
#define	DMA_DADR047	(DMA_CH47_DADR)

/** \brief  25E0, DMA Channel Read Data CRC Register */
#define DMA_CH47_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00125E0u)

/** Alias (User Manual Name) for DMA_CH47_RDCRCR.
* To use register names with standard convension, please use DMA_CH47_RDCRCR.
*/
#define	DMA_RDCRCR047	(DMA_CH47_RDCRCR)

/** \brief  25E8, DMA Channel Source Address Register */
#define DMA_CH47_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00125E8u)

/** Alias (User Manual Name) for DMA_CH47_SADR.
* To use register names with standard convension, please use DMA_CH47_SADR.
*/
#define	DMA_SADR047	(DMA_CH47_SADR)

/** \brief  25E4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH47_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00125E4u)

/** Alias (User Manual Name) for DMA_CH47_SDCRCR.
* To use register names with standard convension, please use DMA_CH47_SDCRCR.
*/
#define	DMA_SDCRCR047	(DMA_CH47_SDCRCR)

/** \brief  25F8, DMA Channel Shadow Address Register */
#define DMA_CH47_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00125F8u)

/** Alias (User Manual Name) for DMA_CH47_SHADR.
* To use register names with standard convension, please use DMA_CH47_SHADR.
*/
#define	DMA_SHADR047	(DMA_CH47_SHADR)

/** \brief  2090, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH4_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012090u)

/** Alias (User Manual Name) for DMA_CH4_ADICR.
* To use register names with standard convension, please use DMA_CH4_ADICR.
*/
#define	DMA_ADICR004	(DMA_CH4_ADICR)

/** \brief  2094, DMA Channel Configuration Register */
#define DMA_CH4_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012094u)

/** Alias (User Manual Name) for DMA_CH4_CHCFGR.
* To use register names with standard convension, please use DMA_CH4_CHCFGR.
*/
#define	DMA_CHCFGR004	(DMA_CH4_CHCFGR)

/** \brief  209C, DMARAM Channel Control and Status Register */
#define DMA_CH4_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001209Cu)

/** Alias (User Manual Name) for DMA_CH4_CHCSR.
* To use register names with standard convension, please use DMA_CH4_CHCSR.
*/
#define	DMA_CHCSR004	(DMA_CH4_CHCSR)

/** \brief  208C, DMA Channel Destination Address Register x */
#define DMA_CH4_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001208Cu)

/** Alias (User Manual Name) for DMA_CH4_DADR.
* To use register names with standard convension, please use DMA_CH4_DADR.
*/
#define	DMA_DADR004	(DMA_CH4_DADR)

/** \brief  2080, DMA Channel Read Data CRC Register */
#define DMA_CH4_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012080u)

/** Alias (User Manual Name) for DMA_CH4_RDCRCR.
* To use register names with standard convension, please use DMA_CH4_RDCRCR.
*/
#define	DMA_RDCRCR004	(DMA_CH4_RDCRCR)

/** \brief  2088, DMA Channel Source Address Register */
#define DMA_CH4_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012088u)

/** Alias (User Manual Name) for DMA_CH4_SADR.
* To use register names with standard convension, please use DMA_CH4_SADR.
*/
#define	DMA_SADR004	(DMA_CH4_SADR)

/** \brief  2084, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH4_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012084u)

/** Alias (User Manual Name) for DMA_CH4_SDCRCR.
* To use register names with standard convension, please use DMA_CH4_SDCRCR.
*/
#define	DMA_SDCRCR004	(DMA_CH4_SDCRCR)

/** \brief  2098, DMA Channel Shadow Address Register */
#define DMA_CH4_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012098u)

/** Alias (User Manual Name) for DMA_CH4_SHADR.
* To use register names with standard convension, please use DMA_CH4_SHADR.
*/
#define	DMA_SHADR004	(DMA_CH4_SHADR)

/** \brief  20B0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH5_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00120B0u)

/** Alias (User Manual Name) for DMA_CH5_ADICR.
* To use register names with standard convension, please use DMA_CH5_ADICR.
*/
#define	DMA_ADICR005	(DMA_CH5_ADICR)

/** \brief  20B4, DMA Channel Configuration Register */
#define DMA_CH5_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00120B4u)

/** Alias (User Manual Name) for DMA_CH5_CHCFGR.
* To use register names with standard convension, please use DMA_CH5_CHCFGR.
*/
#define	DMA_CHCFGR005	(DMA_CH5_CHCFGR)

/** \brief  20BC, DMARAM Channel Control and Status Register */
#define DMA_CH5_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00120BCu)

/** Alias (User Manual Name) for DMA_CH5_CHCSR.
* To use register names with standard convension, please use DMA_CH5_CHCSR.
*/
#define	DMA_CHCSR005	(DMA_CH5_CHCSR)

/** \brief  20AC, DMA Channel Destination Address Register x */
#define DMA_CH5_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00120ACu)

/** Alias (User Manual Name) for DMA_CH5_DADR.
* To use register names with standard convension, please use DMA_CH5_DADR.
*/
#define	DMA_DADR005	(DMA_CH5_DADR)

/** \brief  20A0, DMA Channel Read Data CRC Register */
#define DMA_CH5_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00120A0u)

/** Alias (User Manual Name) for DMA_CH5_RDCRCR.
* To use register names with standard convension, please use DMA_CH5_RDCRCR.
*/
#define	DMA_RDCRCR005	(DMA_CH5_RDCRCR)

/** \brief  20A8, DMA Channel Source Address Register */
#define DMA_CH5_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00120A8u)

/** Alias (User Manual Name) for DMA_CH5_SADR.
* To use register names with standard convension, please use DMA_CH5_SADR.
*/
#define	DMA_SADR005	(DMA_CH5_SADR)

/** \brief  20A4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH5_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00120A4u)

/** Alias (User Manual Name) for DMA_CH5_SDCRCR.
* To use register names with standard convension, please use DMA_CH5_SDCRCR.
*/
#define	DMA_SDCRCR005	(DMA_CH5_SDCRCR)

/** \brief  20B8, DMA Channel Shadow Address Register */
#define DMA_CH5_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00120B8u)

/** Alias (User Manual Name) for DMA_CH5_SHADR.
* To use register names with standard convension, please use DMA_CH5_SHADR.
*/
#define	DMA_SHADR005	(DMA_CH5_SHADR)

/** \brief  20D0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH6_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00120D0u)

/** Alias (User Manual Name) for DMA_CH6_ADICR.
* To use register names with standard convension, please use DMA_CH6_ADICR.
*/
#define	DMA_ADICR006	(DMA_CH6_ADICR)

/** \brief  20D4, DMA Channel Configuration Register */
#define DMA_CH6_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00120D4u)

/** Alias (User Manual Name) for DMA_CH6_CHCFGR.
* To use register names with standard convension, please use DMA_CH6_CHCFGR.
*/
#define	DMA_CHCFGR006	(DMA_CH6_CHCFGR)

/** \brief  20DC, DMARAM Channel Control and Status Register */
#define DMA_CH6_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00120DCu)

/** Alias (User Manual Name) for DMA_CH6_CHCSR.
* To use register names with standard convension, please use DMA_CH6_CHCSR.
*/
#define	DMA_CHCSR006	(DMA_CH6_CHCSR)

/** \brief  20CC, DMA Channel Destination Address Register x */
#define DMA_CH6_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00120CCu)

/** Alias (User Manual Name) for DMA_CH6_DADR.
* To use register names with standard convension, please use DMA_CH6_DADR.
*/
#define	DMA_DADR006	(DMA_CH6_DADR)

/** \brief  20C0, DMA Channel Read Data CRC Register */
#define DMA_CH6_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00120C0u)

/** Alias (User Manual Name) for DMA_CH6_RDCRCR.
* To use register names with standard convension, please use DMA_CH6_RDCRCR.
*/
#define	DMA_RDCRCR006	(DMA_CH6_RDCRCR)

/** \brief  20C8, DMA Channel Source Address Register */
#define DMA_CH6_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00120C8u)

/** Alias (User Manual Name) for DMA_CH6_SADR.
* To use register names with standard convension, please use DMA_CH6_SADR.
*/
#define	DMA_SADR006	(DMA_CH6_SADR)

/** \brief  20C4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH6_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00120C4u)

/** Alias (User Manual Name) for DMA_CH6_SDCRCR.
* To use register names with standard convension, please use DMA_CH6_SDCRCR.
*/
#define	DMA_SDCRCR006	(DMA_CH6_SDCRCR)

/** \brief  20D8, DMA Channel Shadow Address Register */
#define DMA_CH6_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00120D8u)

/** Alias (User Manual Name) for DMA_CH6_SHADR.
* To use register names with standard convension, please use DMA_CH6_SHADR.
*/
#define	DMA_SHADR006	(DMA_CH6_SHADR)

/** \brief  20F0, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH7_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF00120F0u)

/** Alias (User Manual Name) for DMA_CH7_ADICR.
* To use register names with standard convension, please use DMA_CH7_ADICR.
*/
#define	DMA_ADICR007	(DMA_CH7_ADICR)

/** \brief  20F4, DMA Channel Configuration Register */
#define DMA_CH7_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF00120F4u)

/** Alias (User Manual Name) for DMA_CH7_CHCFGR.
* To use register names with standard convension, please use DMA_CH7_CHCFGR.
*/
#define	DMA_CHCFGR007	(DMA_CH7_CHCFGR)

/** \brief  20FC, DMARAM Channel Control and Status Register */
#define DMA_CH7_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF00120FCu)

/** Alias (User Manual Name) for DMA_CH7_CHCSR.
* To use register names with standard convension, please use DMA_CH7_CHCSR.
*/
#define	DMA_CHCSR007	(DMA_CH7_CHCSR)

/** \brief  20EC, DMA Channel Destination Address Register x */
#define DMA_CH7_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF00120ECu)

/** Alias (User Manual Name) for DMA_CH7_DADR.
* To use register names with standard convension, please use DMA_CH7_DADR.
*/
#define	DMA_DADR007	(DMA_CH7_DADR)

/** \brief  20E0, DMA Channel Read Data CRC Register */
#define DMA_CH7_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF00120E0u)

/** Alias (User Manual Name) for DMA_CH7_RDCRCR.
* To use register names with standard convension, please use DMA_CH7_RDCRCR.
*/
#define	DMA_RDCRCR007	(DMA_CH7_RDCRCR)

/** \brief  20E8, DMA Channel Source Address Register */
#define DMA_CH7_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF00120E8u)

/** Alias (User Manual Name) for DMA_CH7_SADR.
* To use register names with standard convension, please use DMA_CH7_SADR.
*/
#define	DMA_SADR007	(DMA_CH7_SADR)

/** \brief  20E4, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH7_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF00120E4u)

/** Alias (User Manual Name) for DMA_CH7_SDCRCR.
* To use register names with standard convension, please use DMA_CH7_SDCRCR.
*/
#define	DMA_SDCRCR007	(DMA_CH7_SDCRCR)

/** \brief  20F8, DMA Channel Shadow Address Register */
#define DMA_CH7_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF00120F8u)

/** Alias (User Manual Name) for DMA_CH7_SHADR.
* To use register names with standard convension, please use DMA_CH7_SHADR.
*/
#define	DMA_SHADR007	(DMA_CH7_SHADR)

/** \brief  2110, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH8_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012110u)

/** Alias (User Manual Name) for DMA_CH8_ADICR.
* To use register names with standard convension, please use DMA_CH8_ADICR.
*/
#define	DMA_ADICR008	(DMA_CH8_ADICR)

/** \brief  2114, DMA Channel Configuration Register */
#define DMA_CH8_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012114u)

/** Alias (User Manual Name) for DMA_CH8_CHCFGR.
* To use register names with standard convension, please use DMA_CH8_CHCFGR.
*/
#define	DMA_CHCFGR008	(DMA_CH8_CHCFGR)

/** \brief  211C, DMARAM Channel Control and Status Register */
#define DMA_CH8_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001211Cu)

/** Alias (User Manual Name) for DMA_CH8_CHCSR.
* To use register names with standard convension, please use DMA_CH8_CHCSR.
*/
#define	DMA_CHCSR008	(DMA_CH8_CHCSR)

/** \brief  210C, DMA Channel Destination Address Register x */
#define DMA_CH8_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001210Cu)

/** Alias (User Manual Name) for DMA_CH8_DADR.
* To use register names with standard convension, please use DMA_CH8_DADR.
*/
#define	DMA_DADR008	(DMA_CH8_DADR)

/** \brief  2100, DMA Channel Read Data CRC Register */
#define DMA_CH8_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012100u)

/** Alias (User Manual Name) for DMA_CH8_RDCRCR.
* To use register names with standard convension, please use DMA_CH8_RDCRCR.
*/
#define	DMA_RDCRCR008	(DMA_CH8_RDCRCR)

/** \brief  2108, DMA Channel Source Address Register */
#define DMA_CH8_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012108u)

/** Alias (User Manual Name) for DMA_CH8_SADR.
* To use register names with standard convension, please use DMA_CH8_SADR.
*/
#define	DMA_SADR008	(DMA_CH8_SADR)

/** \brief  2104, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH8_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012104u)

/** Alias (User Manual Name) for DMA_CH8_SDCRCR.
* To use register names with standard convension, please use DMA_CH8_SDCRCR.
*/
#define	DMA_SDCRCR008	(DMA_CH8_SDCRCR)

/** \brief  2118, DMA Channel Shadow Address Register */
#define DMA_CH8_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012118u)

/** Alias (User Manual Name) for DMA_CH8_SHADR.
* To use register names with standard convension, please use DMA_CH8_SHADR.
*/
#define	DMA_SHADR008	(DMA_CH8_SHADR)

/** \brief  2130, DMA Channel Address and Interrupt Control Register x */
#define DMA_CH9_ADICR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_ADICR*)0xF0012130u)

/** Alias (User Manual Name) for DMA_CH9_ADICR.
* To use register names with standard convension, please use DMA_CH9_ADICR.
*/
#define	DMA_ADICR009	(DMA_CH9_ADICR)

/** \brief  2134, DMA Channel Configuration Register */
#define DMA_CH9_CHCFGR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCFGR*)0xF0012134u)

/** Alias (User Manual Name) for DMA_CH9_CHCFGR.
* To use register names with standard convension, please use DMA_CH9_CHCFGR.
*/
#define	DMA_CHCFGR009	(DMA_CH9_CHCFGR)

/** \brief  213C, DMARAM Channel Control and Status Register */
#define DMA_CH9_CHCSR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_CHCSR*)0xF001213Cu)

/** Alias (User Manual Name) for DMA_CH9_CHCSR.
* To use register names with standard convension, please use DMA_CH9_CHCSR.
*/
#define	DMA_CHCSR009	(DMA_CH9_CHCSR)

/** \brief  212C, DMA Channel Destination Address Register x */
#define DMA_CH9_DADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_DADR*)0xF001212Cu)

/** Alias (User Manual Name) for DMA_CH9_DADR.
* To use register names with standard convension, please use DMA_CH9_DADR.
*/
#define	DMA_DADR009	(DMA_CH9_DADR)

/** \brief  2120, DMA Channel Read Data CRC Register */
#define DMA_CH9_RDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_RDCRCR*)0xF0012120u)

/** Alias (User Manual Name) for DMA_CH9_RDCRCR.
* To use register names with standard convension, please use DMA_CH9_RDCRCR.
*/
#define	DMA_RDCRCR009	(DMA_CH9_RDCRCR)

/** \brief  2128, DMA Channel Source Address Register */
#define DMA_CH9_SADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SADR*)0xF0012128u)

/** Alias (User Manual Name) for DMA_CH9_SADR.
* To use register names with standard convension, please use DMA_CH9_SADR.
*/
#define	DMA_SADR009	(DMA_CH9_SADR)

/** \brief  2124, DMA Channel Source and Destination Address CRC Register */
#define DMA_CH9_SDCRCR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SDCRCR*)0xF0012124u)

/** Alias (User Manual Name) for DMA_CH9_SDCRCR.
* To use register names with standard convension, please use DMA_CH9_SDCRCR.
*/
#define	DMA_SDCRCR009	(DMA_CH9_SDCRCR)

/** \brief  2138, DMA Channel Shadow Address Register */
#define DMA_CH9_SHADR /*lint --e(923)*/ (*(volatile Ifx_DMA_CH_SHADR*)0xF0012138u)

/** Alias (User Manual Name) for DMA_CH9_SHADR.
* To use register names with standard convension, please use DMA_CH9_SHADR.
*/
#define	DMA_SHADR009	(DMA_CH9_SHADR)

/** \brief  0, DMA Clock Control Register */
#define DMA_CLC /*lint --e(923)*/ (*(volatile Ifx_DMA_CLC*)0xF0010000u)

/** \brief  1204, DMA Error Interrupt Set Register */
#define DMA_ERRINTR /*lint --e(923)*/ (*(volatile Ifx_DMA_ERRINTR*)0xF0011204u)

/** \brief  1800, DMA Channel Hardware Resource Register */
#define DMA_HRR0 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011800u)

/** Alias (User Manual Name) for DMA_HRR0.
* To use register names with standard convension, please use DMA_HRR0.
*/
#define	DMA_HRR000	(DMA_HRR0)

/** \brief  1804, DMA Channel Hardware Resource Register */
#define DMA_HRR1 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011804u)

/** Alias (User Manual Name) for DMA_HRR1.
* To use register names with standard convension, please use DMA_HRR1.
*/
#define	DMA_HRR001	(DMA_HRR1)

/** \brief  1828, DMA Channel Hardware Resource Register */
#define DMA_HRR10 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011828u)

/** Alias (User Manual Name) for DMA_HRR10.
* To use register names with standard convension, please use DMA_HRR10.
*/
#define	DMA_HRR010	(DMA_HRR10)

/** \brief  182C, DMA Channel Hardware Resource Register */
#define DMA_HRR11 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001182Cu)

/** Alias (User Manual Name) for DMA_HRR11.
* To use register names with standard convension, please use DMA_HRR11.
*/
#define	DMA_HRR011	(DMA_HRR11)

/** \brief  1830, DMA Channel Hardware Resource Register */
#define DMA_HRR12 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011830u)

/** Alias (User Manual Name) for DMA_HRR12.
* To use register names with standard convension, please use DMA_HRR12.
*/
#define	DMA_HRR012	(DMA_HRR12)

/** \brief  1834, DMA Channel Hardware Resource Register */
#define DMA_HRR13 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011834u)

/** Alias (User Manual Name) for DMA_HRR13.
* To use register names with standard convension, please use DMA_HRR13.
*/
#define	DMA_HRR013	(DMA_HRR13)

/** \brief  1838, DMA Channel Hardware Resource Register */
#define DMA_HRR14 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011838u)

/** Alias (User Manual Name) for DMA_HRR14.
* To use register names with standard convension, please use DMA_HRR14.
*/
#define	DMA_HRR014	(DMA_HRR14)

/** \brief  183C, DMA Channel Hardware Resource Register */
#define DMA_HRR15 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001183Cu)

/** Alias (User Manual Name) for DMA_HRR15.
* To use register names with standard convension, please use DMA_HRR15.
*/
#define	DMA_HRR015	(DMA_HRR15)

/** \brief  1840, DMA Channel Hardware Resource Register */
#define DMA_HRR16 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011840u)

/** Alias (User Manual Name) for DMA_HRR16.
* To use register names with standard convension, please use DMA_HRR16.
*/
#define	DMA_HRR016	(DMA_HRR16)

/** \brief  1844, DMA Channel Hardware Resource Register */
#define DMA_HRR17 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011844u)

/** Alias (User Manual Name) for DMA_HRR17.
* To use register names with standard convension, please use DMA_HRR17.
*/
#define	DMA_HRR017	(DMA_HRR17)

/** \brief  1848, DMA Channel Hardware Resource Register */
#define DMA_HRR18 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011848u)

/** Alias (User Manual Name) for DMA_HRR18.
* To use register names with standard convension, please use DMA_HRR18.
*/
#define	DMA_HRR018	(DMA_HRR18)

/** \brief  184C, DMA Channel Hardware Resource Register */
#define DMA_HRR19 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001184Cu)

/** Alias (User Manual Name) for DMA_HRR19.
* To use register names with standard convension, please use DMA_HRR19.
*/
#define	DMA_HRR019	(DMA_HRR19)

/** \brief  1808, DMA Channel Hardware Resource Register */
#define DMA_HRR2 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011808u)

/** Alias (User Manual Name) for DMA_HRR2.
* To use register names with standard convension, please use DMA_HRR2.
*/
#define	DMA_HRR002	(DMA_HRR2)

/** \brief  1850, DMA Channel Hardware Resource Register */
#define DMA_HRR20 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011850u)

/** Alias (User Manual Name) for DMA_HRR20.
* To use register names with standard convension, please use DMA_HRR20.
*/
#define	DMA_HRR020	(DMA_HRR20)

/** \brief  1854, DMA Channel Hardware Resource Register */
#define DMA_HRR21 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011854u)

/** Alias (User Manual Name) for DMA_HRR21.
* To use register names with standard convension, please use DMA_HRR21.
*/
#define	DMA_HRR021	(DMA_HRR21)

/** \brief  1858, DMA Channel Hardware Resource Register */
#define DMA_HRR22 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011858u)

/** Alias (User Manual Name) for DMA_HRR22.
* To use register names with standard convension, please use DMA_HRR22.
*/
#define	DMA_HRR022	(DMA_HRR22)

/** \brief  185C, DMA Channel Hardware Resource Register */
#define DMA_HRR23 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001185Cu)

/** Alias (User Manual Name) for DMA_HRR23.
* To use register names with standard convension, please use DMA_HRR23.
*/
#define	DMA_HRR023	(DMA_HRR23)

/** \brief  1860, DMA Channel Hardware Resource Register */
#define DMA_HRR24 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011860u)

/** Alias (User Manual Name) for DMA_HRR24.
* To use register names with standard convension, please use DMA_HRR24.
*/
#define	DMA_HRR024	(DMA_HRR24)

/** \brief  1864, DMA Channel Hardware Resource Register */
#define DMA_HRR25 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011864u)

/** Alias (User Manual Name) for DMA_HRR25.
* To use register names with standard convension, please use DMA_HRR25.
*/
#define	DMA_HRR025	(DMA_HRR25)

/** \brief  1868, DMA Channel Hardware Resource Register */
#define DMA_HRR26 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011868u)

/** Alias (User Manual Name) for DMA_HRR26.
* To use register names with standard convension, please use DMA_HRR26.
*/
#define	DMA_HRR026	(DMA_HRR26)

/** \brief  186C, DMA Channel Hardware Resource Register */
#define DMA_HRR27 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001186Cu)

/** Alias (User Manual Name) for DMA_HRR27.
* To use register names with standard convension, please use DMA_HRR27.
*/
#define	DMA_HRR027	(DMA_HRR27)

/** \brief  1870, DMA Channel Hardware Resource Register */
#define DMA_HRR28 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011870u)

/** Alias (User Manual Name) for DMA_HRR28.
* To use register names with standard convension, please use DMA_HRR28.
*/
#define	DMA_HRR028	(DMA_HRR28)

/** \brief  1874, DMA Channel Hardware Resource Register */
#define DMA_HRR29 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011874u)

/** Alias (User Manual Name) for DMA_HRR29.
* To use register names with standard convension, please use DMA_HRR29.
*/
#define	DMA_HRR029	(DMA_HRR29)

/** \brief  180C, DMA Channel Hardware Resource Register */
#define DMA_HRR3 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001180Cu)

/** Alias (User Manual Name) for DMA_HRR3.
* To use register names with standard convension, please use DMA_HRR3.
*/
#define	DMA_HRR003	(DMA_HRR3)

/** \brief  1878, DMA Channel Hardware Resource Register */
#define DMA_HRR30 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011878u)

/** Alias (User Manual Name) for DMA_HRR30.
* To use register names with standard convension, please use DMA_HRR30.
*/
#define	DMA_HRR030	(DMA_HRR30)

/** \brief  187C, DMA Channel Hardware Resource Register */
#define DMA_HRR31 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001187Cu)

/** Alias (User Manual Name) for DMA_HRR31.
* To use register names with standard convension, please use DMA_HRR31.
*/
#define	DMA_HRR031	(DMA_HRR31)

/** \brief  1880, DMA Channel Hardware Resource Register */
#define DMA_HRR32 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011880u)

/** Alias (User Manual Name) for DMA_HRR32.
* To use register names with standard convension, please use DMA_HRR32.
*/
#define	DMA_HRR032	(DMA_HRR32)

/** \brief  1884, DMA Channel Hardware Resource Register */
#define DMA_HRR33 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011884u)

/** Alias (User Manual Name) for DMA_HRR33.
* To use register names with standard convension, please use DMA_HRR33.
*/
#define	DMA_HRR033	(DMA_HRR33)

/** \brief  1888, DMA Channel Hardware Resource Register */
#define DMA_HRR34 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011888u)

/** Alias (User Manual Name) for DMA_HRR34.
* To use register names with standard convension, please use DMA_HRR34.
*/
#define	DMA_HRR034	(DMA_HRR34)

/** \brief  188C, DMA Channel Hardware Resource Register */
#define DMA_HRR35 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001188Cu)

/** Alias (User Manual Name) for DMA_HRR35.
* To use register names with standard convension, please use DMA_HRR35.
*/
#define	DMA_HRR035	(DMA_HRR35)

/** \brief  1890, DMA Channel Hardware Resource Register */
#define DMA_HRR36 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011890u)

/** Alias (User Manual Name) for DMA_HRR36.
* To use register names with standard convension, please use DMA_HRR36.
*/
#define	DMA_HRR036	(DMA_HRR36)

/** \brief  1894, DMA Channel Hardware Resource Register */
#define DMA_HRR37 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011894u)

/** Alias (User Manual Name) for DMA_HRR37.
* To use register names with standard convension, please use DMA_HRR37.
*/
#define	DMA_HRR037	(DMA_HRR37)

/** \brief  1898, DMA Channel Hardware Resource Register */
#define DMA_HRR38 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011898u)

/** Alias (User Manual Name) for DMA_HRR38.
* To use register names with standard convension, please use DMA_HRR38.
*/
#define	DMA_HRR038	(DMA_HRR38)

/** \brief  189C, DMA Channel Hardware Resource Register */
#define DMA_HRR39 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001189Cu)

/** Alias (User Manual Name) for DMA_HRR39.
* To use register names with standard convension, please use DMA_HRR39.
*/
#define	DMA_HRR039	(DMA_HRR39)

/** \brief  1810, DMA Channel Hardware Resource Register */
#define DMA_HRR4 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011810u)

/** Alias (User Manual Name) for DMA_HRR4.
* To use register names with standard convension, please use DMA_HRR4.
*/
#define	DMA_HRR004	(DMA_HRR4)

/** \brief  18A0, DMA Channel Hardware Resource Register */
#define DMA_HRR40 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118A0u)

/** Alias (User Manual Name) for DMA_HRR40.
* To use register names with standard convension, please use DMA_HRR40.
*/
#define	DMA_HRR040	(DMA_HRR40)

/** \brief  18A4, DMA Channel Hardware Resource Register */
#define DMA_HRR41 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118A4u)

/** Alias (User Manual Name) for DMA_HRR41.
* To use register names with standard convension, please use DMA_HRR41.
*/
#define	DMA_HRR041	(DMA_HRR41)

/** \brief  18A8, DMA Channel Hardware Resource Register */
#define DMA_HRR42 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118A8u)

/** Alias (User Manual Name) for DMA_HRR42.
* To use register names with standard convension, please use DMA_HRR42.
*/
#define	DMA_HRR042	(DMA_HRR42)

/** \brief  18AC, DMA Channel Hardware Resource Register */
#define DMA_HRR43 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118ACu)

/** Alias (User Manual Name) for DMA_HRR43.
* To use register names with standard convension, please use DMA_HRR43.
*/
#define	DMA_HRR043	(DMA_HRR43)

/** \brief  18B0, DMA Channel Hardware Resource Register */
#define DMA_HRR44 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118B0u)

/** Alias (User Manual Name) for DMA_HRR44.
* To use register names with standard convension, please use DMA_HRR44.
*/
#define	DMA_HRR044	(DMA_HRR44)

/** \brief  18B4, DMA Channel Hardware Resource Register */
#define DMA_HRR45 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118B4u)

/** Alias (User Manual Name) for DMA_HRR45.
* To use register names with standard convension, please use DMA_HRR45.
*/
#define	DMA_HRR045	(DMA_HRR45)

/** \brief  18B8, DMA Channel Hardware Resource Register */
#define DMA_HRR46 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118B8u)

/** Alias (User Manual Name) for DMA_HRR46.
* To use register names with standard convension, please use DMA_HRR46.
*/
#define	DMA_HRR046	(DMA_HRR46)

/** \brief  18BC, DMA Channel Hardware Resource Register */
#define DMA_HRR47 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF00118BCu)

/** Alias (User Manual Name) for DMA_HRR47.
* To use register names with standard convension, please use DMA_HRR47.
*/
#define	DMA_HRR047	(DMA_HRR47)

/** \brief  1814, DMA Channel Hardware Resource Register */
#define DMA_HRR5 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011814u)

/** Alias (User Manual Name) for DMA_HRR5.
* To use register names with standard convension, please use DMA_HRR5.
*/
#define	DMA_HRR005	(DMA_HRR5)

/** \brief  1818, DMA Channel Hardware Resource Register */
#define DMA_HRR6 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011818u)

/** Alias (User Manual Name) for DMA_HRR6.
* To use register names with standard convension, please use DMA_HRR6.
*/
#define	DMA_HRR006	(DMA_HRR6)

/** \brief  181C, DMA Channel Hardware Resource Register */
#define DMA_HRR7 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF001181Cu)

/** Alias (User Manual Name) for DMA_HRR7.
* To use register names with standard convension, please use DMA_HRR7.
*/
#define	DMA_HRR007	(DMA_HRR7)

/** \brief  1820, DMA Channel Hardware Resource Register */
#define DMA_HRR8 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011820u)

/** Alias (User Manual Name) for DMA_HRR8.
* To use register names with standard convension, please use DMA_HRR8.
*/
#define	DMA_HRR008	(DMA_HRR8)

/** \brief  1824, DMA Channel Hardware Resource Register */
#define DMA_HRR9 /*lint --e(923)*/ (*(volatile Ifx_DMA_HRR*)0xF0011824u)

/** Alias (User Manual Name) for DMA_HRR9.
* To use register names with standard convension, please use DMA_HRR9.
*/
#define	DMA_HRR009	(DMA_HRR9)

/** \brief  8, Module Identification Register */
#define DMA_ID /*lint --e(923)*/ (*(volatile Ifx_DMA_ID*)0xF0010008u)

/** \brief  20, DMA Memory Control Register */
#define DMA_MEMCON /*lint --e(923)*/ (*(volatile Ifx_DMA_MEMCON*)0xF0010020u)

/** \brief  1300, DMA Mode Register */
#define DMA_MODE0 /*lint --e(923)*/ (*(volatile Ifx_DMA_MODE*)0xF0011300u)

/** \brief  1304, DMA Mode Register */
#define DMA_MODE1 /*lint --e(923)*/ (*(volatile Ifx_DMA_MODE*)0xF0011304u)

/** \brief  1308, DMA Mode Register */
#define DMA_MODE2 /*lint --e(923)*/ (*(volatile Ifx_DMA_MODE*)0xF0011308u)

/** \brief  130C, DMA Mode Register */
#define DMA_MODE3 /*lint --e(923)*/ (*(volatile Ifx_DMA_MODE*)0xF001130Cu)

/** \brief  1200, DMA OCDS Trigger Set Select */
#define DMA_OTSS /*lint --e(923)*/ (*(volatile Ifx_DMA_OTSS*)0xF0011200u)

/** \brief  1208, Pattern Read Register 0 */
#define DMA_PRR0 /*lint --e(923)*/ (*(volatile Ifx_DMA_PRR0*)0xF0011208u)

/** \brief  120C, Pattern Read Register 1 */
#define DMA_PRR1 /*lint --e(923)*/ (*(volatile Ifx_DMA_PRR1*)0xF001120Cu)

/** \brief  1C00, DMA Suspend Acknowledge Register */
#define DMA_SUSACR0 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C00u)

/** Alias (User Manual Name) for DMA_SUSACR0.
* To use register names with standard convension, please use DMA_SUSACR0.
*/
#define	DMA_SUSACR000	(DMA_SUSACR0)

/** \brief  1C04, DMA Suspend Acknowledge Register */
#define DMA_SUSACR1 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C04u)

/** Alias (User Manual Name) for DMA_SUSACR1.
* To use register names with standard convension, please use DMA_SUSACR1.
*/
#define	DMA_SUSACR001	(DMA_SUSACR1)

/** \brief  1C28, DMA Suspend Acknowledge Register */
#define DMA_SUSACR10 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C28u)

/** Alias (User Manual Name) for DMA_SUSACR10.
* To use register names with standard convension, please use DMA_SUSACR10.
*/
#define	DMA_SUSACR010	(DMA_SUSACR10)

/** \brief  1C2C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR11 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C2Cu)

/** Alias (User Manual Name) for DMA_SUSACR11.
* To use register names with standard convension, please use DMA_SUSACR11.
*/
#define	DMA_SUSACR011	(DMA_SUSACR11)

/** \brief  1C30, DMA Suspend Acknowledge Register */
#define DMA_SUSACR12 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C30u)

/** Alias (User Manual Name) for DMA_SUSACR12.
* To use register names with standard convension, please use DMA_SUSACR12.
*/
#define	DMA_SUSACR012	(DMA_SUSACR12)

/** \brief  1C34, DMA Suspend Acknowledge Register */
#define DMA_SUSACR13 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C34u)

/** Alias (User Manual Name) for DMA_SUSACR13.
* To use register names with standard convension, please use DMA_SUSACR13.
*/
#define	DMA_SUSACR013	(DMA_SUSACR13)

/** \brief  1C38, DMA Suspend Acknowledge Register */
#define DMA_SUSACR14 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C38u)

/** Alias (User Manual Name) for DMA_SUSACR14.
* To use register names with standard convension, please use DMA_SUSACR14.
*/
#define	DMA_SUSACR014	(DMA_SUSACR14)

/** \brief  1C3C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR15 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C3Cu)

/** Alias (User Manual Name) for DMA_SUSACR15.
* To use register names with standard convension, please use DMA_SUSACR15.
*/
#define	DMA_SUSACR015	(DMA_SUSACR15)

/** \brief  1C40, DMA Suspend Acknowledge Register */
#define DMA_SUSACR16 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C40u)

/** Alias (User Manual Name) for DMA_SUSACR16.
* To use register names with standard convension, please use DMA_SUSACR16.
*/
#define	DMA_SUSACR016	(DMA_SUSACR16)

/** \brief  1C44, DMA Suspend Acknowledge Register */
#define DMA_SUSACR17 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C44u)

/** Alias (User Manual Name) for DMA_SUSACR17.
* To use register names with standard convension, please use DMA_SUSACR17.
*/
#define	DMA_SUSACR017	(DMA_SUSACR17)

/** \brief  1C48, DMA Suspend Acknowledge Register */
#define DMA_SUSACR18 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C48u)

/** Alias (User Manual Name) for DMA_SUSACR18.
* To use register names with standard convension, please use DMA_SUSACR18.
*/
#define	DMA_SUSACR018	(DMA_SUSACR18)

/** \brief  1C4C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR19 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C4Cu)

/** Alias (User Manual Name) for DMA_SUSACR19.
* To use register names with standard convension, please use DMA_SUSACR19.
*/
#define	DMA_SUSACR019	(DMA_SUSACR19)

/** \brief  1C08, DMA Suspend Acknowledge Register */
#define DMA_SUSACR2 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C08u)

/** Alias (User Manual Name) for DMA_SUSACR2.
* To use register names with standard convension, please use DMA_SUSACR2.
*/
#define	DMA_SUSACR002	(DMA_SUSACR2)

/** \brief  1C50, DMA Suspend Acknowledge Register */
#define DMA_SUSACR20 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C50u)

/** Alias (User Manual Name) for DMA_SUSACR20.
* To use register names with standard convension, please use DMA_SUSACR20.
*/
#define	DMA_SUSACR020	(DMA_SUSACR20)

/** \brief  1C54, DMA Suspend Acknowledge Register */
#define DMA_SUSACR21 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C54u)

/** Alias (User Manual Name) for DMA_SUSACR21.
* To use register names with standard convension, please use DMA_SUSACR21.
*/
#define	DMA_SUSACR021	(DMA_SUSACR21)

/** \brief  1C58, DMA Suspend Acknowledge Register */
#define DMA_SUSACR22 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C58u)

/** Alias (User Manual Name) for DMA_SUSACR22.
* To use register names with standard convension, please use DMA_SUSACR22.
*/
#define	DMA_SUSACR022	(DMA_SUSACR22)

/** \brief  1C5C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR23 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C5Cu)

/** Alias (User Manual Name) for DMA_SUSACR23.
* To use register names with standard convension, please use DMA_SUSACR23.
*/
#define	DMA_SUSACR023	(DMA_SUSACR23)

/** \brief  1C60, DMA Suspend Acknowledge Register */
#define DMA_SUSACR24 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C60u)

/** Alias (User Manual Name) for DMA_SUSACR24.
* To use register names with standard convension, please use DMA_SUSACR24.
*/
#define	DMA_SUSACR024	(DMA_SUSACR24)

/** \brief  1C64, DMA Suspend Acknowledge Register */
#define DMA_SUSACR25 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C64u)

/** Alias (User Manual Name) for DMA_SUSACR25.
* To use register names with standard convension, please use DMA_SUSACR25.
*/
#define	DMA_SUSACR025	(DMA_SUSACR25)

/** \brief  1C68, DMA Suspend Acknowledge Register */
#define DMA_SUSACR26 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C68u)

/** Alias (User Manual Name) for DMA_SUSACR26.
* To use register names with standard convension, please use DMA_SUSACR26.
*/
#define	DMA_SUSACR026	(DMA_SUSACR26)

/** \brief  1C6C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR27 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C6Cu)

/** Alias (User Manual Name) for DMA_SUSACR27.
* To use register names with standard convension, please use DMA_SUSACR27.
*/
#define	DMA_SUSACR027	(DMA_SUSACR27)

/** \brief  1C70, DMA Suspend Acknowledge Register */
#define DMA_SUSACR28 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C70u)

/** Alias (User Manual Name) for DMA_SUSACR28.
* To use register names with standard convension, please use DMA_SUSACR28.
*/
#define	DMA_SUSACR028	(DMA_SUSACR28)

/** \brief  1C74, DMA Suspend Acknowledge Register */
#define DMA_SUSACR29 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C74u)

/** Alias (User Manual Name) for DMA_SUSACR29.
* To use register names with standard convension, please use DMA_SUSACR29.
*/
#define	DMA_SUSACR029	(DMA_SUSACR29)

/** \brief  1C0C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR3 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C0Cu)

/** Alias (User Manual Name) for DMA_SUSACR3.
* To use register names with standard convension, please use DMA_SUSACR3.
*/
#define	DMA_SUSACR003	(DMA_SUSACR3)

/** \brief  1C78, DMA Suspend Acknowledge Register */
#define DMA_SUSACR30 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C78u)

/** Alias (User Manual Name) for DMA_SUSACR30.
* To use register names with standard convension, please use DMA_SUSACR30.
*/
#define	DMA_SUSACR030	(DMA_SUSACR30)

/** \brief  1C7C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR31 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C7Cu)

/** Alias (User Manual Name) for DMA_SUSACR31.
* To use register names with standard convension, please use DMA_SUSACR31.
*/
#define	DMA_SUSACR031	(DMA_SUSACR31)

/** \brief  1C80, DMA Suspend Acknowledge Register */
#define DMA_SUSACR32 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C80u)

/** Alias (User Manual Name) for DMA_SUSACR32.
* To use register names with standard convension, please use DMA_SUSACR32.
*/
#define	DMA_SUSACR032	(DMA_SUSACR32)

/** \brief  1C84, DMA Suspend Acknowledge Register */
#define DMA_SUSACR33 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C84u)

/** Alias (User Manual Name) for DMA_SUSACR33.
* To use register names with standard convension, please use DMA_SUSACR33.
*/
#define	DMA_SUSACR033	(DMA_SUSACR33)

/** \brief  1C88, DMA Suspend Acknowledge Register */
#define DMA_SUSACR34 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C88u)

/** Alias (User Manual Name) for DMA_SUSACR34.
* To use register names with standard convension, please use DMA_SUSACR34.
*/
#define	DMA_SUSACR034	(DMA_SUSACR34)

/** \brief  1C8C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR35 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C8Cu)

/** Alias (User Manual Name) for DMA_SUSACR35.
* To use register names with standard convension, please use DMA_SUSACR35.
*/
#define	DMA_SUSACR035	(DMA_SUSACR35)

/** \brief  1C90, DMA Suspend Acknowledge Register */
#define DMA_SUSACR36 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C90u)

/** Alias (User Manual Name) for DMA_SUSACR36.
* To use register names with standard convension, please use DMA_SUSACR36.
*/
#define	DMA_SUSACR036	(DMA_SUSACR36)

/** \brief  1C94, DMA Suspend Acknowledge Register */
#define DMA_SUSACR37 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C94u)

/** Alias (User Manual Name) for DMA_SUSACR37.
* To use register names with standard convension, please use DMA_SUSACR37.
*/
#define	DMA_SUSACR037	(DMA_SUSACR37)

/** \brief  1C98, DMA Suspend Acknowledge Register */
#define DMA_SUSACR38 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C98u)

/** Alias (User Manual Name) for DMA_SUSACR38.
* To use register names with standard convension, please use DMA_SUSACR38.
*/
#define	DMA_SUSACR038	(DMA_SUSACR38)

/** \brief  1C9C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR39 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C9Cu)

/** Alias (User Manual Name) for DMA_SUSACR39.
* To use register names with standard convension, please use DMA_SUSACR39.
*/
#define	DMA_SUSACR039	(DMA_SUSACR39)

/** \brief  1C10, DMA Suspend Acknowledge Register */
#define DMA_SUSACR4 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C10u)

/** Alias (User Manual Name) for DMA_SUSACR4.
* To use register names with standard convension, please use DMA_SUSACR4.
*/
#define	DMA_SUSACR004	(DMA_SUSACR4)

/** \brief  1CA0, DMA Suspend Acknowledge Register */
#define DMA_SUSACR40 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CA0u)

/** Alias (User Manual Name) for DMA_SUSACR40.
* To use register names with standard convension, please use DMA_SUSACR40.
*/
#define	DMA_SUSACR040	(DMA_SUSACR40)

/** \brief  1CA4, DMA Suspend Acknowledge Register */
#define DMA_SUSACR41 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CA4u)

/** Alias (User Manual Name) for DMA_SUSACR41.
* To use register names with standard convension, please use DMA_SUSACR41.
*/
#define	DMA_SUSACR041	(DMA_SUSACR41)

/** \brief  1CA8, DMA Suspend Acknowledge Register */
#define DMA_SUSACR42 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CA8u)

/** Alias (User Manual Name) for DMA_SUSACR42.
* To use register names with standard convension, please use DMA_SUSACR42.
*/
#define	DMA_SUSACR042	(DMA_SUSACR42)

/** \brief  1CAC, DMA Suspend Acknowledge Register */
#define DMA_SUSACR43 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CACu)

/** Alias (User Manual Name) for DMA_SUSACR43.
* To use register names with standard convension, please use DMA_SUSACR43.
*/
#define	DMA_SUSACR043	(DMA_SUSACR43)

/** \brief  1CB0, DMA Suspend Acknowledge Register */
#define DMA_SUSACR44 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CB0u)

/** Alias (User Manual Name) for DMA_SUSACR44.
* To use register names with standard convension, please use DMA_SUSACR44.
*/
#define	DMA_SUSACR044	(DMA_SUSACR44)

/** \brief  1CB4, DMA Suspend Acknowledge Register */
#define DMA_SUSACR45 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CB4u)

/** Alias (User Manual Name) for DMA_SUSACR45.
* To use register names with standard convension, please use DMA_SUSACR45.
*/
#define	DMA_SUSACR045	(DMA_SUSACR45)

/** \brief  1CB8, DMA Suspend Acknowledge Register */
#define DMA_SUSACR46 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CB8u)

/** Alias (User Manual Name) for DMA_SUSACR46.
* To use register names with standard convension, please use DMA_SUSACR46.
*/
#define	DMA_SUSACR046	(DMA_SUSACR46)

/** \brief  1CBC, DMA Suspend Acknowledge Register */
#define DMA_SUSACR47 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011CBCu)

/** Alias (User Manual Name) for DMA_SUSACR47.
* To use register names with standard convension, please use DMA_SUSACR47.
*/
#define	DMA_SUSACR047	(DMA_SUSACR47)

/** \brief  1C14, DMA Suspend Acknowledge Register */
#define DMA_SUSACR5 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C14u)

/** Alias (User Manual Name) for DMA_SUSACR5.
* To use register names with standard convension, please use DMA_SUSACR5.
*/
#define	DMA_SUSACR005	(DMA_SUSACR5)

/** \brief  1C18, DMA Suspend Acknowledge Register */
#define DMA_SUSACR6 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C18u)

/** Alias (User Manual Name) for DMA_SUSACR6.
* To use register names with standard convension, please use DMA_SUSACR6.
*/
#define	DMA_SUSACR006	(DMA_SUSACR6)

/** \brief  1C1C, DMA Suspend Acknowledge Register */
#define DMA_SUSACR7 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C1Cu)

/** Alias (User Manual Name) for DMA_SUSACR7.
* To use register names with standard convension, please use DMA_SUSACR7.
*/
#define	DMA_SUSACR007	(DMA_SUSACR7)

/** \brief  1C20, DMA Suspend Acknowledge Register */
#define DMA_SUSACR8 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C20u)

/** Alias (User Manual Name) for DMA_SUSACR8.
* To use register names with standard convension, please use DMA_SUSACR8.
*/
#define	DMA_SUSACR008	(DMA_SUSACR8)

/** \brief  1C24, DMA Suspend Acknowledge Register */
#define DMA_SUSACR9 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSACR*)0xF0011C24u)

/** Alias (User Manual Name) for DMA_SUSACR9.
* To use register names with standard convension, please use DMA_SUSACR9.
*/
#define	DMA_SUSACR009	(DMA_SUSACR9)

/** \brief  1A00, DMA Suspend Enable Register */
#define DMA_SUSENR0 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A00u)

/** Alias (User Manual Name) for DMA_SUSENR0.
* To use register names with standard convension, please use DMA_SUSENR0.
*/
#define	DMA_SUSENR000	(DMA_SUSENR0)

/** \brief  1A04, DMA Suspend Enable Register */
#define DMA_SUSENR1 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A04u)

/** Alias (User Manual Name) for DMA_SUSENR1.
* To use register names with standard convension, please use DMA_SUSENR1.
*/
#define	DMA_SUSENR001	(DMA_SUSENR1)

/** \brief  1A28, DMA Suspend Enable Register */
#define DMA_SUSENR10 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A28u)

/** Alias (User Manual Name) for DMA_SUSENR10.
* To use register names with standard convension, please use DMA_SUSENR10.
*/
#define	DMA_SUSENR010	(DMA_SUSENR10)

/** \brief  1A2C, DMA Suspend Enable Register */
#define DMA_SUSENR11 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A2Cu)

/** Alias (User Manual Name) for DMA_SUSENR11.
* To use register names with standard convension, please use DMA_SUSENR11.
*/
#define	DMA_SUSENR011	(DMA_SUSENR11)

/** \brief  1A30, DMA Suspend Enable Register */
#define DMA_SUSENR12 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A30u)

/** Alias (User Manual Name) for DMA_SUSENR12.
* To use register names with standard convension, please use DMA_SUSENR12.
*/
#define	DMA_SUSENR012	(DMA_SUSENR12)

/** \brief  1A34, DMA Suspend Enable Register */
#define DMA_SUSENR13 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A34u)

/** Alias (User Manual Name) for DMA_SUSENR13.
* To use register names with standard convension, please use DMA_SUSENR13.
*/
#define	DMA_SUSENR013	(DMA_SUSENR13)

/** \brief  1A38, DMA Suspend Enable Register */
#define DMA_SUSENR14 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A38u)

/** Alias (User Manual Name) for DMA_SUSENR14.
* To use register names with standard convension, please use DMA_SUSENR14.
*/
#define	DMA_SUSENR014	(DMA_SUSENR14)

/** \brief  1A3C, DMA Suspend Enable Register */
#define DMA_SUSENR15 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A3Cu)

/** Alias (User Manual Name) for DMA_SUSENR15.
* To use register names with standard convension, please use DMA_SUSENR15.
*/
#define	DMA_SUSENR015	(DMA_SUSENR15)

/** \brief  1A40, DMA Suspend Enable Register */
#define DMA_SUSENR16 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A40u)

/** Alias (User Manual Name) for DMA_SUSENR16.
* To use register names with standard convension, please use DMA_SUSENR16.
*/
#define	DMA_SUSENR016	(DMA_SUSENR16)

/** \brief  1A44, DMA Suspend Enable Register */
#define DMA_SUSENR17 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A44u)

/** Alias (User Manual Name) for DMA_SUSENR17.
* To use register names with standard convension, please use DMA_SUSENR17.
*/
#define	DMA_SUSENR017	(DMA_SUSENR17)

/** \brief  1A48, DMA Suspend Enable Register */
#define DMA_SUSENR18 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A48u)

/** Alias (User Manual Name) for DMA_SUSENR18.
* To use register names with standard convension, please use DMA_SUSENR18.
*/
#define	DMA_SUSENR018	(DMA_SUSENR18)

/** \brief  1A4C, DMA Suspend Enable Register */
#define DMA_SUSENR19 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A4Cu)

/** Alias (User Manual Name) for DMA_SUSENR19.
* To use register names with standard convension, please use DMA_SUSENR19.
*/
#define	DMA_SUSENR019	(DMA_SUSENR19)

/** \brief  1A08, DMA Suspend Enable Register */
#define DMA_SUSENR2 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A08u)

/** Alias (User Manual Name) for DMA_SUSENR2.
* To use register names with standard convension, please use DMA_SUSENR2.
*/
#define	DMA_SUSENR002	(DMA_SUSENR2)

/** \brief  1A50, DMA Suspend Enable Register */
#define DMA_SUSENR20 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A50u)

/** Alias (User Manual Name) for DMA_SUSENR20.
* To use register names with standard convension, please use DMA_SUSENR20.
*/
#define	DMA_SUSENR020	(DMA_SUSENR20)

/** \brief  1A54, DMA Suspend Enable Register */
#define DMA_SUSENR21 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A54u)

/** Alias (User Manual Name) for DMA_SUSENR21.
* To use register names with standard convension, please use DMA_SUSENR21.
*/
#define	DMA_SUSENR021	(DMA_SUSENR21)

/** \brief  1A58, DMA Suspend Enable Register */
#define DMA_SUSENR22 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A58u)

/** Alias (User Manual Name) for DMA_SUSENR22.
* To use register names with standard convension, please use DMA_SUSENR22.
*/
#define	DMA_SUSENR022	(DMA_SUSENR22)

/** \brief  1A5C, DMA Suspend Enable Register */
#define DMA_SUSENR23 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A5Cu)

/** Alias (User Manual Name) for DMA_SUSENR23.
* To use register names with standard convension, please use DMA_SUSENR23.
*/
#define	DMA_SUSENR023	(DMA_SUSENR23)

/** \brief  1A60, DMA Suspend Enable Register */
#define DMA_SUSENR24 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A60u)

/** Alias (User Manual Name) for DMA_SUSENR24.
* To use register names with standard convension, please use DMA_SUSENR24.
*/
#define	DMA_SUSENR024	(DMA_SUSENR24)

/** \brief  1A64, DMA Suspend Enable Register */
#define DMA_SUSENR25 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A64u)

/** Alias (User Manual Name) for DMA_SUSENR25.
* To use register names with standard convension, please use DMA_SUSENR25.
*/
#define	DMA_SUSENR025	(DMA_SUSENR25)

/** \brief  1A68, DMA Suspend Enable Register */
#define DMA_SUSENR26 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A68u)

/** Alias (User Manual Name) for DMA_SUSENR26.
* To use register names with standard convension, please use DMA_SUSENR26.
*/
#define	DMA_SUSENR026	(DMA_SUSENR26)

/** \brief  1A6C, DMA Suspend Enable Register */
#define DMA_SUSENR27 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A6Cu)

/** Alias (User Manual Name) for DMA_SUSENR27.
* To use register names with standard convension, please use DMA_SUSENR27.
*/
#define	DMA_SUSENR027	(DMA_SUSENR27)

/** \brief  1A70, DMA Suspend Enable Register */
#define DMA_SUSENR28 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A70u)

/** Alias (User Manual Name) for DMA_SUSENR28.
* To use register names with standard convension, please use DMA_SUSENR28.
*/
#define	DMA_SUSENR028	(DMA_SUSENR28)

/** \brief  1A74, DMA Suspend Enable Register */
#define DMA_SUSENR29 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A74u)

/** Alias (User Manual Name) for DMA_SUSENR29.
* To use register names with standard convension, please use DMA_SUSENR29.
*/
#define	DMA_SUSENR029	(DMA_SUSENR29)

/** \brief  1A0C, DMA Suspend Enable Register */
#define DMA_SUSENR3 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A0Cu)

/** Alias (User Manual Name) for DMA_SUSENR3.
* To use register names with standard convension, please use DMA_SUSENR3.
*/
#define	DMA_SUSENR003	(DMA_SUSENR3)

/** \brief  1A78, DMA Suspend Enable Register */
#define DMA_SUSENR30 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A78u)

/** Alias (User Manual Name) for DMA_SUSENR30.
* To use register names with standard convension, please use DMA_SUSENR30.
*/
#define	DMA_SUSENR030	(DMA_SUSENR30)

/** \brief  1A7C, DMA Suspend Enable Register */
#define DMA_SUSENR31 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A7Cu)

/** Alias (User Manual Name) for DMA_SUSENR31.
* To use register names with standard convension, please use DMA_SUSENR31.
*/
#define	DMA_SUSENR031	(DMA_SUSENR31)

/** \brief  1A80, DMA Suspend Enable Register */
#define DMA_SUSENR32 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A80u)

/** Alias (User Manual Name) for DMA_SUSENR32.
* To use register names with standard convension, please use DMA_SUSENR32.
*/
#define	DMA_SUSENR032	(DMA_SUSENR32)

/** \brief  1A84, DMA Suspend Enable Register */
#define DMA_SUSENR33 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A84u)

/** Alias (User Manual Name) for DMA_SUSENR33.
* To use register names with standard convension, please use DMA_SUSENR33.
*/
#define	DMA_SUSENR033	(DMA_SUSENR33)

/** \brief  1A88, DMA Suspend Enable Register */
#define DMA_SUSENR34 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A88u)

/** Alias (User Manual Name) for DMA_SUSENR34.
* To use register names with standard convension, please use DMA_SUSENR34.
*/
#define	DMA_SUSENR034	(DMA_SUSENR34)

/** \brief  1A8C, DMA Suspend Enable Register */
#define DMA_SUSENR35 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A8Cu)

/** Alias (User Manual Name) for DMA_SUSENR35.
* To use register names with standard convension, please use DMA_SUSENR35.
*/
#define	DMA_SUSENR035	(DMA_SUSENR35)

/** \brief  1A90, DMA Suspend Enable Register */
#define DMA_SUSENR36 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A90u)

/** Alias (User Manual Name) for DMA_SUSENR36.
* To use register names with standard convension, please use DMA_SUSENR36.
*/
#define	DMA_SUSENR036	(DMA_SUSENR36)

/** \brief  1A94, DMA Suspend Enable Register */
#define DMA_SUSENR37 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A94u)

/** Alias (User Manual Name) for DMA_SUSENR37.
* To use register names with standard convension, please use DMA_SUSENR37.
*/
#define	DMA_SUSENR037	(DMA_SUSENR37)

/** \brief  1A98, DMA Suspend Enable Register */
#define DMA_SUSENR38 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A98u)

/** Alias (User Manual Name) for DMA_SUSENR38.
* To use register names with standard convension, please use DMA_SUSENR38.
*/
#define	DMA_SUSENR038	(DMA_SUSENR38)

/** \brief  1A9C, DMA Suspend Enable Register */
#define DMA_SUSENR39 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A9Cu)

/** Alias (User Manual Name) for DMA_SUSENR39.
* To use register names with standard convension, please use DMA_SUSENR39.
*/
#define	DMA_SUSENR039	(DMA_SUSENR39)

/** \brief  1A10, DMA Suspend Enable Register */
#define DMA_SUSENR4 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A10u)

/** Alias (User Manual Name) for DMA_SUSENR4.
* To use register names with standard convension, please use DMA_SUSENR4.
*/
#define	DMA_SUSENR004	(DMA_SUSENR4)

/** \brief  1AA0, DMA Suspend Enable Register */
#define DMA_SUSENR40 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011AA0u)

/** Alias (User Manual Name) for DMA_SUSENR40.
* To use register names with standard convension, please use DMA_SUSENR40.
*/
#define	DMA_SUSENR040	(DMA_SUSENR40)

/** \brief  1AA4, DMA Suspend Enable Register */
#define DMA_SUSENR41 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011AA4u)

/** Alias (User Manual Name) for DMA_SUSENR41.
* To use register names with standard convension, please use DMA_SUSENR41.
*/
#define	DMA_SUSENR041	(DMA_SUSENR41)

/** \brief  1AA8, DMA Suspend Enable Register */
#define DMA_SUSENR42 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011AA8u)

/** Alias (User Manual Name) for DMA_SUSENR42.
* To use register names with standard convension, please use DMA_SUSENR42.
*/
#define	DMA_SUSENR042	(DMA_SUSENR42)

/** \brief  1AAC, DMA Suspend Enable Register */
#define DMA_SUSENR43 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011AACu)

/** Alias (User Manual Name) for DMA_SUSENR43.
* To use register names with standard convension, please use DMA_SUSENR43.
*/
#define	DMA_SUSENR043	(DMA_SUSENR43)

/** \brief  1AB0, DMA Suspend Enable Register */
#define DMA_SUSENR44 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011AB0u)

/** Alias (User Manual Name) for DMA_SUSENR44.
* To use register names with standard convension, please use DMA_SUSENR44.
*/
#define	DMA_SUSENR044	(DMA_SUSENR44)

/** \brief  1AB4, DMA Suspend Enable Register */
#define DMA_SUSENR45 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011AB4u)

/** Alias (User Manual Name) for DMA_SUSENR45.
* To use register names with standard convension, please use DMA_SUSENR45.
*/
#define	DMA_SUSENR045	(DMA_SUSENR45)

/** \brief  1AB8, DMA Suspend Enable Register */
#define DMA_SUSENR46 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011AB8u)

/** Alias (User Manual Name) for DMA_SUSENR46.
* To use register names with standard convension, please use DMA_SUSENR46.
*/
#define	DMA_SUSENR046	(DMA_SUSENR46)

/** \brief  1ABC, DMA Suspend Enable Register */
#define DMA_SUSENR47 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011ABCu)

/** Alias (User Manual Name) for DMA_SUSENR47.
* To use register names with standard convension, please use DMA_SUSENR47.
*/
#define	DMA_SUSENR047	(DMA_SUSENR47)

/** \brief  1A14, DMA Suspend Enable Register */
#define DMA_SUSENR5 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A14u)

/** Alias (User Manual Name) for DMA_SUSENR5.
* To use register names with standard convension, please use DMA_SUSENR5.
*/
#define	DMA_SUSENR005	(DMA_SUSENR5)

/** \brief  1A18, DMA Suspend Enable Register */
#define DMA_SUSENR6 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A18u)

/** Alias (User Manual Name) for DMA_SUSENR6.
* To use register names with standard convension, please use DMA_SUSENR6.
*/
#define	DMA_SUSENR006	(DMA_SUSENR6)

/** \brief  1A1C, DMA Suspend Enable Register */
#define DMA_SUSENR7 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A1Cu)

/** Alias (User Manual Name) for DMA_SUSENR7.
* To use register names with standard convension, please use DMA_SUSENR7.
*/
#define	DMA_SUSENR007	(DMA_SUSENR7)

/** \brief  1A20, DMA Suspend Enable Register */
#define DMA_SUSENR8 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A20u)

/** Alias (User Manual Name) for DMA_SUSENR8.
* To use register names with standard convension, please use DMA_SUSENR8.
*/
#define	DMA_SUSENR008	(DMA_SUSENR8)

/** \brief  1A24, DMA Suspend Enable Register */
#define DMA_SUSENR9 /*lint --e(923)*/ (*(volatile Ifx_DMA_SUSENR*)0xF0011A24u)

/** Alias (User Manual Name) for DMA_SUSENR9.
* To use register names with standard convension, please use DMA_SUSENR9.
*/
#define	DMA_SUSENR009	(DMA_SUSENR9)

/** \brief  1210, Time Register */
#define DMA_TIME /*lint --e(923)*/ (*(volatile Ifx_DMA_TIME*)0xF0011210u)

/** \brief  1E00, DMA Transaction State Register */
#define DMA_TSR0 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E00u)

/** Alias (User Manual Name) for DMA_TSR0.
* To use register names with standard convension, please use DMA_TSR0.
*/
#define	DMA_TSR000	(DMA_TSR0)

/** \brief  1E04, DMA Transaction State Register */
#define DMA_TSR1 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E04u)

/** Alias (User Manual Name) for DMA_TSR1.
* To use register names with standard convension, please use DMA_TSR1.
*/
#define	DMA_TSR001	(DMA_TSR1)

/** \brief  1E28, DMA Transaction State Register */
#define DMA_TSR10 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E28u)

/** Alias (User Manual Name) for DMA_TSR10.
* To use register names with standard convension, please use DMA_TSR10.
*/
#define	DMA_TSR010	(DMA_TSR10)

/** \brief  1E2C, DMA Transaction State Register */
#define DMA_TSR11 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E2Cu)

/** Alias (User Manual Name) for DMA_TSR11.
* To use register names with standard convension, please use DMA_TSR11.
*/
#define	DMA_TSR011	(DMA_TSR11)

/** \brief  1E30, DMA Transaction State Register */
#define DMA_TSR12 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E30u)

/** Alias (User Manual Name) for DMA_TSR12.
* To use register names with standard convension, please use DMA_TSR12.
*/
#define	DMA_TSR012	(DMA_TSR12)

/** \brief  1E34, DMA Transaction State Register */
#define DMA_TSR13 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E34u)

/** Alias (User Manual Name) for DMA_TSR13.
* To use register names with standard convension, please use DMA_TSR13.
*/
#define	DMA_TSR013	(DMA_TSR13)

/** \brief  1E38, DMA Transaction State Register */
#define DMA_TSR14 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E38u)

/** Alias (User Manual Name) for DMA_TSR14.
* To use register names with standard convension, please use DMA_TSR14.
*/
#define	DMA_TSR014	(DMA_TSR14)

/** \brief  1E3C, DMA Transaction State Register */
#define DMA_TSR15 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E3Cu)

/** Alias (User Manual Name) for DMA_TSR15.
* To use register names with standard convension, please use DMA_TSR15.
*/
#define	DMA_TSR015	(DMA_TSR15)

/** \brief  1E40, DMA Transaction State Register */
#define DMA_TSR16 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E40u)

/** Alias (User Manual Name) for DMA_TSR16.
* To use register names with standard convension, please use DMA_TSR16.
*/
#define	DMA_TSR016	(DMA_TSR16)

/** \brief  1E44, DMA Transaction State Register */
#define DMA_TSR17 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E44u)

/** Alias (User Manual Name) for DMA_TSR17.
* To use register names with standard convension, please use DMA_TSR17.
*/
#define	DMA_TSR017	(DMA_TSR17)

/** \brief  1E48, DMA Transaction State Register */
#define DMA_TSR18 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E48u)

/** Alias (User Manual Name) for DMA_TSR18.
* To use register names with standard convension, please use DMA_TSR18.
*/
#define	DMA_TSR018	(DMA_TSR18)

/** \brief  1E4C, DMA Transaction State Register */
#define DMA_TSR19 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E4Cu)

/** Alias (User Manual Name) for DMA_TSR19.
* To use register names with standard convension, please use DMA_TSR19.
*/
#define	DMA_TSR019	(DMA_TSR19)

/** \brief  1E08, DMA Transaction State Register */
#define DMA_TSR2 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E08u)

/** Alias (User Manual Name) for DMA_TSR2.
* To use register names with standard convension, please use DMA_TSR2.
*/
#define	DMA_TSR002	(DMA_TSR2)

/** \brief  1E50, DMA Transaction State Register */
#define DMA_TSR20 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E50u)

/** Alias (User Manual Name) for DMA_TSR20.
* To use register names with standard convension, please use DMA_TSR20.
*/
#define	DMA_TSR020	(DMA_TSR20)

/** \brief  1E54, DMA Transaction State Register */
#define DMA_TSR21 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E54u)

/** Alias (User Manual Name) for DMA_TSR21.
* To use register names with standard convension, please use DMA_TSR21.
*/
#define	DMA_TSR021	(DMA_TSR21)

/** \brief  1E58, DMA Transaction State Register */
#define DMA_TSR22 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E58u)

/** Alias (User Manual Name) for DMA_TSR22.
* To use register names with standard convension, please use DMA_TSR22.
*/
#define	DMA_TSR022	(DMA_TSR22)

/** \brief  1E5C, DMA Transaction State Register */
#define DMA_TSR23 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E5Cu)

/** Alias (User Manual Name) for DMA_TSR23.
* To use register names with standard convension, please use DMA_TSR23.
*/
#define	DMA_TSR023	(DMA_TSR23)

/** \brief  1E60, DMA Transaction State Register */
#define DMA_TSR24 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E60u)

/** Alias (User Manual Name) for DMA_TSR24.
* To use register names with standard convension, please use DMA_TSR24.
*/
#define	DMA_TSR024	(DMA_TSR24)

/** \brief  1E64, DMA Transaction State Register */
#define DMA_TSR25 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E64u)

/** Alias (User Manual Name) for DMA_TSR25.
* To use register names with standard convension, please use DMA_TSR25.
*/
#define	DMA_TSR025	(DMA_TSR25)

/** \brief  1E68, DMA Transaction State Register */
#define DMA_TSR26 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E68u)

/** Alias (User Manual Name) for DMA_TSR26.
* To use register names with standard convension, please use DMA_TSR26.
*/
#define	DMA_TSR026	(DMA_TSR26)

/** \brief  1E6C, DMA Transaction State Register */
#define DMA_TSR27 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E6Cu)

/** Alias (User Manual Name) for DMA_TSR27.
* To use register names with standard convension, please use DMA_TSR27.
*/
#define	DMA_TSR027	(DMA_TSR27)

/** \brief  1E70, DMA Transaction State Register */
#define DMA_TSR28 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E70u)

/** Alias (User Manual Name) for DMA_TSR28.
* To use register names with standard convension, please use DMA_TSR28.
*/
#define	DMA_TSR028	(DMA_TSR28)

/** \brief  1E74, DMA Transaction State Register */
#define DMA_TSR29 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E74u)

/** Alias (User Manual Name) for DMA_TSR29.
* To use register names with standard convension, please use DMA_TSR29.
*/
#define	DMA_TSR029	(DMA_TSR29)

/** \brief  1E0C, DMA Transaction State Register */
#define DMA_TSR3 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E0Cu)

/** Alias (User Manual Name) for DMA_TSR3.
* To use register names with standard convension, please use DMA_TSR3.
*/
#define	DMA_TSR003	(DMA_TSR3)

/** \brief  1E78, DMA Transaction State Register */
#define DMA_TSR30 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E78u)

/** Alias (User Manual Name) for DMA_TSR30.
* To use register names with standard convension, please use DMA_TSR30.
*/
#define	DMA_TSR030	(DMA_TSR30)

/** \brief  1E7C, DMA Transaction State Register */
#define DMA_TSR31 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E7Cu)

/** Alias (User Manual Name) for DMA_TSR31.
* To use register names with standard convension, please use DMA_TSR31.
*/
#define	DMA_TSR031	(DMA_TSR31)

/** \brief  1E80, DMA Transaction State Register */
#define DMA_TSR32 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E80u)

/** Alias (User Manual Name) for DMA_TSR32.
* To use register names with standard convension, please use DMA_TSR32.
*/
#define	DMA_TSR032	(DMA_TSR32)

/** \brief  1E84, DMA Transaction State Register */
#define DMA_TSR33 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E84u)

/** Alias (User Manual Name) for DMA_TSR33.
* To use register names with standard convension, please use DMA_TSR33.
*/
#define	DMA_TSR033	(DMA_TSR33)

/** \brief  1E88, DMA Transaction State Register */
#define DMA_TSR34 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E88u)

/** Alias (User Manual Name) for DMA_TSR34.
* To use register names with standard convension, please use DMA_TSR34.
*/
#define	DMA_TSR034	(DMA_TSR34)

/** \brief  1E8C, DMA Transaction State Register */
#define DMA_TSR35 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E8Cu)

/** Alias (User Manual Name) for DMA_TSR35.
* To use register names with standard convension, please use DMA_TSR35.
*/
#define	DMA_TSR035	(DMA_TSR35)

/** \brief  1E90, DMA Transaction State Register */
#define DMA_TSR36 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E90u)

/** Alias (User Manual Name) for DMA_TSR36.
* To use register names with standard convension, please use DMA_TSR36.
*/
#define	DMA_TSR036	(DMA_TSR36)

/** \brief  1E94, DMA Transaction State Register */
#define DMA_TSR37 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E94u)

/** Alias (User Manual Name) for DMA_TSR37.
* To use register names with standard convension, please use DMA_TSR37.
*/
#define	DMA_TSR037	(DMA_TSR37)

/** \brief  1E98, DMA Transaction State Register */
#define DMA_TSR38 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E98u)

/** Alias (User Manual Name) for DMA_TSR38.
* To use register names with standard convension, please use DMA_TSR38.
*/
#define	DMA_TSR038	(DMA_TSR38)

/** \brief  1E9C, DMA Transaction State Register */
#define DMA_TSR39 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E9Cu)

/** Alias (User Manual Name) for DMA_TSR39.
* To use register names with standard convension, please use DMA_TSR39.
*/
#define	DMA_TSR039	(DMA_TSR39)

/** \brief  1E10, DMA Transaction State Register */
#define DMA_TSR4 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E10u)

/** Alias (User Manual Name) for DMA_TSR4.
* To use register names with standard convension, please use DMA_TSR4.
*/
#define	DMA_TSR004	(DMA_TSR4)

/** \brief  1EA0, DMA Transaction State Register */
#define DMA_TSR40 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EA0u)

/** Alias (User Manual Name) for DMA_TSR40.
* To use register names with standard convension, please use DMA_TSR40.
*/
#define	DMA_TSR040	(DMA_TSR40)

/** \brief  1EA4, DMA Transaction State Register */
#define DMA_TSR41 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EA4u)

/** Alias (User Manual Name) for DMA_TSR41.
* To use register names with standard convension, please use DMA_TSR41.
*/
#define	DMA_TSR041	(DMA_TSR41)

/** \brief  1EA8, DMA Transaction State Register */
#define DMA_TSR42 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EA8u)

/** Alias (User Manual Name) for DMA_TSR42.
* To use register names with standard convension, please use DMA_TSR42.
*/
#define	DMA_TSR042	(DMA_TSR42)

/** \brief  1EAC, DMA Transaction State Register */
#define DMA_TSR43 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EACu)

/** Alias (User Manual Name) for DMA_TSR43.
* To use register names with standard convension, please use DMA_TSR43.
*/
#define	DMA_TSR043	(DMA_TSR43)

/** \brief  1EB0, DMA Transaction State Register */
#define DMA_TSR44 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EB0u)

/** Alias (User Manual Name) for DMA_TSR44.
* To use register names with standard convension, please use DMA_TSR44.
*/
#define	DMA_TSR044	(DMA_TSR44)

/** \brief  1EB4, DMA Transaction State Register */
#define DMA_TSR45 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EB4u)

/** Alias (User Manual Name) for DMA_TSR45.
* To use register names with standard convension, please use DMA_TSR45.
*/
#define	DMA_TSR045	(DMA_TSR45)

/** \brief  1EB8, DMA Transaction State Register */
#define DMA_TSR46 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EB8u)

/** Alias (User Manual Name) for DMA_TSR46.
* To use register names with standard convension, please use DMA_TSR46.
*/
#define	DMA_TSR046	(DMA_TSR46)

/** \brief  1EBC, DMA Transaction State Register */
#define DMA_TSR47 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011EBCu)

/** Alias (User Manual Name) for DMA_TSR47.
* To use register names with standard convension, please use DMA_TSR47.
*/
#define	DMA_TSR047	(DMA_TSR47)

/** \brief  1E14, DMA Transaction State Register */
#define DMA_TSR5 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E14u)

/** Alias (User Manual Name) for DMA_TSR5.
* To use register names with standard convension, please use DMA_TSR5.
*/
#define	DMA_TSR005	(DMA_TSR5)

/** \brief  1E18, DMA Transaction State Register */
#define DMA_TSR6 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E18u)

/** Alias (User Manual Name) for DMA_TSR6.
* To use register names with standard convension, please use DMA_TSR6.
*/
#define	DMA_TSR006	(DMA_TSR6)

/** \brief  1E1C, DMA Transaction State Register */
#define DMA_TSR7 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E1Cu)

/** Alias (User Manual Name) for DMA_TSR7.
* To use register names with standard convension, please use DMA_TSR7.
*/
#define	DMA_TSR007	(DMA_TSR7)

/** \brief  1E20, DMA Transaction State Register */
#define DMA_TSR8 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E20u)

/** Alias (User Manual Name) for DMA_TSR8.
* To use register names with standard convension, please use DMA_TSR8.
*/
#define	DMA_TSR008	(DMA_TSR8)

/** \brief  1E24, DMA Transaction State Register */
#define DMA_TSR9 /*lint --e(923)*/ (*(volatile Ifx_DMA_TSR*)0xF0011E24u)

/** Alias (User Manual Name) for DMA_TSR9.
* To use register names with standard convension, please use DMA_TSR9.
*/
#define	DMA_TSR009	(DMA_TSR9)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXDMA_REG_H */
