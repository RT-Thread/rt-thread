/**
 * \file IfxCpu_bf.h
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
 * \defgroup IfxLld_Cpu_BitfieldsMask Bitfields mask and offset
 * \ingroup IfxLld_Cpu
 * 
 */
#ifndef IFXCPU_BF_H
#define IFXCPU_BF_H 1
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_BitfieldsMask
 * \{  */

/** \brief  Length for Ifx_CPU_A_Bits.ADDR */
#define IFX_CPU_A_ADDR_LEN (32u)

/** \brief  Mask for Ifx_CPU_A_Bits.ADDR */
#define IFX_CPU_A_ADDR_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_A_Bits.ADDR */
#define IFX_CPU_A_ADDR_OFF (0u)

/** \brief  Length for Ifx_CPU_BIV_Bits.BIV */
#define IFX_CPU_BIV_BIV_LEN (31u)

/** \brief  Mask for Ifx_CPU_BIV_Bits.BIV */
#define IFX_CPU_BIV_BIV_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_BIV_Bits.BIV */
#define IFX_CPU_BIV_BIV_OFF (1u)

/** \brief  Length for Ifx_CPU_BIV_Bits.VSS */
#define IFX_CPU_BIV_VSS_LEN (1u)

/** \brief  Mask for Ifx_CPU_BIV_Bits.VSS */
#define IFX_CPU_BIV_VSS_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_BIV_Bits.VSS */
#define IFX_CPU_BIV_VSS_OFF (0u)

/** \brief  Length for Ifx_CPU_BTV_Bits.BTV */
#define IFX_CPU_BTV_BTV_LEN (31u)

/** \brief  Mask for Ifx_CPU_BTV_Bits.BTV */
#define IFX_CPU_BTV_BTV_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_BTV_Bits.BTV */
#define IFX_CPU_BTV_BTV_OFF (1u)

/** \brief  Length for Ifx_CPU_CCNT_Bits.CountValue */
#define IFX_CPU_CCNT_COUNTVALUE_LEN (31u)

/** \brief  Mask for Ifx_CPU_CCNT_Bits.CountValue */
#define IFX_CPU_CCNT_COUNTVALUE_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_CCNT_Bits.CountValue */
#define IFX_CPU_CCNT_COUNTVALUE_OFF (0u)

/** \brief  Length for Ifx_CPU_CCNT_Bits.SOvf */
#define IFX_CPU_CCNT_SOVF_LEN (1u)

/** \brief  Mask for Ifx_CPU_CCNT_Bits.SOvf */
#define IFX_CPU_CCNT_SOVF_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_CCNT_Bits.SOvf */
#define IFX_CPU_CCNT_SOVF_OFF (31u)

/** \brief  Length for Ifx_CPU_CCTRL_Bits.CE */
#define IFX_CPU_CCTRL_CE_LEN (1u)

/** \brief  Mask for Ifx_CPU_CCTRL_Bits.CE */
#define IFX_CPU_CCTRL_CE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_CCTRL_Bits.CE */
#define IFX_CPU_CCTRL_CE_OFF (1u)

/** \brief  Length for Ifx_CPU_CCTRL_Bits.CM */
#define IFX_CPU_CCTRL_CM_LEN (1u)

/** \brief  Mask for Ifx_CPU_CCTRL_Bits.CM */
#define IFX_CPU_CCTRL_CM_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_CCTRL_Bits.CM */
#define IFX_CPU_CCTRL_CM_OFF (0u)

/** \brief  Length for Ifx_CPU_CCTRL_Bits.M1 */
#define IFX_CPU_CCTRL_M1_LEN (3u)

/** \brief  Mask for Ifx_CPU_CCTRL_Bits.M1 */
#define IFX_CPU_CCTRL_M1_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_CCTRL_Bits.M1 */
#define IFX_CPU_CCTRL_M1_OFF (2u)

/** \brief  Length for Ifx_CPU_CCTRL_Bits.M2 */
#define IFX_CPU_CCTRL_M2_LEN (3u)

/** \brief  Mask for Ifx_CPU_CCTRL_Bits.M2 */
#define IFX_CPU_CCTRL_M2_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_CCTRL_Bits.M2 */
#define IFX_CPU_CCTRL_M2_OFF (5u)

/** \brief  Length for Ifx_CPU_CCTRL_Bits.M3 */
#define IFX_CPU_CCTRL_M3_LEN (3u)

/** \brief  Mask for Ifx_CPU_CCTRL_Bits.M3 */
#define IFX_CPU_CCTRL_M3_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_CCTRL_Bits.M3 */
#define IFX_CPU_CCTRL_M3_OFF (8u)

/** \brief  Length for Ifx_CPU_COMPAT_Bits.RM */
#define IFX_CPU_COMPAT_RM_LEN (1u)

/** \brief  Mask for Ifx_CPU_COMPAT_Bits.RM */
#define IFX_CPU_COMPAT_RM_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_COMPAT_Bits.RM */
#define IFX_CPU_COMPAT_RM_OFF (3u)

/** \brief  Length for Ifx_CPU_COMPAT_Bits.SP */
#define IFX_CPU_COMPAT_SP_LEN (1u)

/** \brief  Mask for Ifx_CPU_COMPAT_Bits.SP */
#define IFX_CPU_COMPAT_SP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_COMPAT_Bits.SP */
#define IFX_CPU_COMPAT_SP_OFF (4u)

/** \brief  Length for Ifx_CPU_CORE_ID_Bits.CORE_ID */
#define IFX_CPU_CORE_ID_CORE_ID_LEN (3u)

/** \brief  Mask for Ifx_CPU_CORE_ID_Bits.CORE_ID */
#define IFX_CPU_CORE_ID_CORE_ID_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_CORE_ID_Bits.CORE_ID */
#define IFX_CPU_CORE_ID_CORE_ID_OFF (0u)

/** \brief  Length for Ifx_CPU_CPR_L_Bits.LOWBND */
#define IFX_CPU_CPR_L_LOWBND_LEN (29u)

/** \brief  Mask for Ifx_CPU_CPR_L_Bits.LOWBND */
#define IFX_CPU_CPR_L_LOWBND_MSK (0x1fffffffu)

/** \brief  Offset for Ifx_CPU_CPR_L_Bits.LOWBND */
#define IFX_CPU_CPR_L_LOWBND_OFF (3u)

/** \brief  Length for Ifx_CPU_CPR_U_Bits.UPPBND */
#define IFX_CPU_CPR_U_UPPBND_LEN (29u)

/** \brief  Mask for Ifx_CPU_CPR_U_Bits.UPPBND */
#define IFX_CPU_CPR_U_UPPBND_MSK (0x1fffffffu)

/** \brief  Offset for Ifx_CPU_CPR_U_Bits.UPPBND */
#define IFX_CPU_CPR_U_UPPBND_OFF (3u)

/** \brief  Length for Ifx_CPU_CPU_ID_Bits.MOD_32B */
#define IFX_CPU_CPU_ID_MOD_32B_LEN (8u)

/** \brief  Mask for Ifx_CPU_CPU_ID_Bits.MOD_32B */
#define IFX_CPU_CPU_ID_MOD_32B_MSK (0xffu)

/** \brief  Offset for Ifx_CPU_CPU_ID_Bits.MOD_32B */
#define IFX_CPU_CPU_ID_MOD_32B_OFF (8u)

/** \brief  Length for Ifx_CPU_CPU_ID_Bits.MOD */
#define IFX_CPU_CPU_ID_MOD_LEN (16u)

/** \brief  Mask for Ifx_CPU_CPU_ID_Bits.MOD */
#define IFX_CPU_CPU_ID_MOD_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_CPU_ID_Bits.MOD */
#define IFX_CPU_CPU_ID_MOD_OFF (16u)

/** \brief  Length for Ifx_CPU_CPU_ID_Bits.MODREV */
#define IFX_CPU_CPU_ID_MODREV_LEN (8u)

/** \brief  Mask for Ifx_CPU_CPU_ID_Bits.MODREV */
#define IFX_CPU_CPU_ID_MODREV_MSK (0xffu)

/** \brief  Offset for Ifx_CPU_CPU_ID_Bits.MODREV */
#define IFX_CPU_CPU_ID_MODREV_OFF (0u)

/** \brief  Length for Ifx_CPU_CPXE_Bits.XE */
#define IFX_CPU_CPXE_XE_LEN (8u)

/** \brief  Mask for Ifx_CPU_CPXE_Bits.XE */
#define IFX_CPU_CPXE_XE_MSK (0xffu)

/** \brief  Offset for Ifx_CPU_CPXE_Bits.XE */
#define IFX_CPU_CPXE_XE_OFF (0u)

/** \brief  Length for Ifx_CPU_CREVT_Bits.BBM */
#define IFX_CPU_CREVT_BBM_LEN (1u)

/** \brief  Mask for Ifx_CPU_CREVT_Bits.BBM */
#define IFX_CPU_CREVT_BBM_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_CREVT_Bits.BBM */
#define IFX_CPU_CREVT_BBM_OFF (3u)

/** \brief  Length for Ifx_CPU_CREVT_Bits.BOD */
#define IFX_CPU_CREVT_BOD_LEN (1u)

/** \brief  Mask for Ifx_CPU_CREVT_Bits.BOD */
#define IFX_CPU_CREVT_BOD_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_CREVT_Bits.BOD */
#define IFX_CPU_CREVT_BOD_OFF (4u)

/** \brief  Length for Ifx_CPU_CREVT_Bits.CNT */
#define IFX_CPU_CREVT_CNT_LEN (2u)

/** \brief  Mask for Ifx_CPU_CREVT_Bits.CNT */
#define IFX_CPU_CREVT_CNT_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_CREVT_Bits.CNT */
#define IFX_CPU_CREVT_CNT_OFF (6u)

/** \brief  Length for Ifx_CPU_CREVT_Bits.EVTA */
#define IFX_CPU_CREVT_EVTA_LEN (3u)

/** \brief  Mask for Ifx_CPU_CREVT_Bits.EVTA */
#define IFX_CPU_CREVT_EVTA_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_CREVT_Bits.EVTA */
#define IFX_CPU_CREVT_EVTA_OFF (0u)

/** \brief  Length for Ifx_CPU_CREVT_Bits.SUSP */
#define IFX_CPU_CREVT_SUSP_LEN (1u)

/** \brief  Mask for Ifx_CPU_CREVT_Bits.SUSP */
#define IFX_CPU_CREVT_SUSP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_CREVT_Bits.SUSP */
#define IFX_CPU_CREVT_SUSP_OFF (5u)

/** \brief  Length for Ifx_CPU_CUS_ID_Bits.CID */
#define IFX_CPU_CUS_ID_CID_LEN (3u)

/** \brief  Mask for Ifx_CPU_CUS_ID_Bits.CID */
#define IFX_CPU_CUS_ID_CID_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_CUS_ID_Bits.CID */
#define IFX_CPU_CUS_ID_CID_OFF (0u)

/** \brief  Length for Ifx_CPU_D_Bits.DATA */
#define IFX_CPU_D_DATA_LEN (32u)

/** \brief  Mask for Ifx_CPU_D_Bits.DATA */
#define IFX_CPU_D_DATA_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_D_Bits.DATA */
#define IFX_CPU_D_DATA_OFF (0u)

/** \brief  Length for Ifx_CPU_DATR_Bits.CFE */
#define IFX_CPU_DATR_CFE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DATR_Bits.CFE */
#define IFX_CPU_DATR_CFE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DATR_Bits.CFE */
#define IFX_CPU_DATR_CFE_OFF (10u)

/** \brief  Length for Ifx_CPU_DATR_Bits.CWE */
#define IFX_CPU_DATR_CWE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DATR_Bits.CWE */
#define IFX_CPU_DATR_CWE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DATR_Bits.CWE */
#define IFX_CPU_DATR_CWE_OFF (9u)

/** \brief  Length for Ifx_CPU_DATR_Bits.SBE */
#define IFX_CPU_DATR_SBE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DATR_Bits.SBE */
#define IFX_CPU_DATR_SBE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DATR_Bits.SBE */
#define IFX_CPU_DATR_SBE_OFF (3u)

/** \brief  Length for Ifx_CPU_DATR_Bits.SME */
#define IFX_CPU_DATR_SME_LEN (1u)

/** \brief  Mask for Ifx_CPU_DATR_Bits.SME */
#define IFX_CPU_DATR_SME_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DATR_Bits.SME */
#define IFX_CPU_DATR_SME_OFF (15u)

/** \brief  Length for Ifx_CPU_DATR_Bits.SOE */
#define IFX_CPU_DATR_SOE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DATR_Bits.SOE */
#define IFX_CPU_DATR_SOE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DATR_Bits.SOE */
#define IFX_CPU_DATR_SOE_OFF (14u)

/** \brief  Length for Ifx_CPU_DBGSR_Bits.DE */
#define IFX_CPU_DBGSR_DE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DBGSR_Bits.DE */
#define IFX_CPU_DBGSR_DE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DBGSR_Bits.DE */
#define IFX_CPU_DBGSR_DE_OFF (0u)

/** \brief  Length for Ifx_CPU_DBGSR_Bits.EVTSRC */
#define IFX_CPU_DBGSR_EVTSRC_LEN (5u)

/** \brief  Mask for Ifx_CPU_DBGSR_Bits.EVTSRC */
#define IFX_CPU_DBGSR_EVTSRC_MSK (0x1fu)

/** \brief  Offset for Ifx_CPU_DBGSR_Bits.EVTSRC */
#define IFX_CPU_DBGSR_EVTSRC_OFF (8u)

/** \brief  Length for Ifx_CPU_DBGSR_Bits.HALT */
#define IFX_CPU_DBGSR_HALT_LEN (2u)

/** \brief  Mask for Ifx_CPU_DBGSR_Bits.HALT */
#define IFX_CPU_DBGSR_HALT_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_DBGSR_Bits.HALT */
#define IFX_CPU_DBGSR_HALT_OFF (1u)

/** \brief  Length for Ifx_CPU_DBGSR_Bits.PEVT */
#define IFX_CPU_DBGSR_PEVT_LEN (1u)

/** \brief  Mask for Ifx_CPU_DBGSR_Bits.PEVT */
#define IFX_CPU_DBGSR_PEVT_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DBGSR_Bits.PEVT */
#define IFX_CPU_DBGSR_PEVT_OFF (7u)

/** \brief  Length for Ifx_CPU_DBGSR_Bits.PREVSUSP */
#define IFX_CPU_DBGSR_PREVSUSP_LEN (1u)

/** \brief  Mask for Ifx_CPU_DBGSR_Bits.PREVSUSP */
#define IFX_CPU_DBGSR_PREVSUSP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DBGSR_Bits.PREVSUSP */
#define IFX_CPU_DBGSR_PREVSUSP_OFF (6u)

/** \brief  Length for Ifx_CPU_DBGSR_Bits.SIH */
#define IFX_CPU_DBGSR_SIH_LEN (1u)

/** \brief  Mask for Ifx_CPU_DBGSR_Bits.SIH */
#define IFX_CPU_DBGSR_SIH_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DBGSR_Bits.SIH */
#define IFX_CPU_DBGSR_SIH_OFF (3u)

/** \brief  Length for Ifx_CPU_DBGSR_Bits.SUSP */
#define IFX_CPU_DBGSR_SUSP_LEN (1u)

/** \brief  Mask for Ifx_CPU_DBGSR_Bits.SUSP */
#define IFX_CPU_DBGSR_SUSP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DBGSR_Bits.SUSP */
#define IFX_CPU_DBGSR_SUSP_OFF (4u)

/** \brief  Length for Ifx_CPU_DBGTCR_Bits.DTA */
#define IFX_CPU_DBGTCR_DTA_LEN (1u)

/** \brief  Mask for Ifx_CPU_DBGTCR_Bits.DTA */
#define IFX_CPU_DBGTCR_DTA_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DBGTCR_Bits.DTA */
#define IFX_CPU_DBGTCR_DTA_OFF (0u)

/** \brief  Length for Ifx_CPU_DCON0_Bits.DCBYP */
#define IFX_CPU_DCON0_DCBYP_LEN (1u)

/** \brief  Mask for Ifx_CPU_DCON0_Bits.DCBYP */
#define IFX_CPU_DCON0_DCBYP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DCON0_Bits.DCBYP */
#define IFX_CPU_DCON0_DCBYP_OFF (1u)

/** \brief  Length for Ifx_CPU_DCON2_Bits.DCACHE_SZE */
#define IFX_CPU_DCON2_DCACHE_SZE_LEN (16u)

/** \brief  Mask for Ifx_CPU_DCON2_Bits.DCACHE_SZE */
#define IFX_CPU_DCON2_DCACHE_SZE_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_DCON2_Bits.DCACHE_SZE */
#define IFX_CPU_DCON2_DCACHE_SZE_OFF (0u)

/** \brief  Length for Ifx_CPU_DCON2_Bits.DSCRATCH_SZE */
#define IFX_CPU_DCON2_DSCRATCH_SZE_LEN (16u)

/** \brief  Mask for Ifx_CPU_DCON2_Bits.DSCRATCH_SZE */
#define IFX_CPU_DCON2_DSCRATCH_SZE_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_DCON2_Bits.DSCRATCH_SZE */
#define IFX_CPU_DCON2_DSCRATCH_SZE_OFF (16u)

/** \brief  Length for Ifx_CPU_DCX_Bits.DCXValue */
#define IFX_CPU_DCX_DCXVALUE_LEN (26u)

/** \brief  Mask for Ifx_CPU_DCX_Bits.DCXValue */
#define IFX_CPU_DCX_DCXVALUE_MSK (0x3ffffffu)

/** \brief  Offset for Ifx_CPU_DCX_Bits.DCXValue */
#define IFX_CPU_DCX_DCXVALUE_OFF (6u)

/** \brief  Length for Ifx_CPU_DEADD_Bits.ERROR_ADDRESS */
#define IFX_CPU_DEADD_ERROR_ADDRESS_LEN (32u)

/** \brief  Mask for Ifx_CPU_DEADD_Bits.ERROR_ADDRESS */
#define IFX_CPU_DEADD_ERROR_ADDRESS_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_DEADD_Bits.ERROR_ADDRESS */
#define IFX_CPU_DEADD_ERROR_ADDRESS_OFF (0u)

/** \brief  Length for Ifx_CPU_DIEAR_Bits.TA */
#define IFX_CPU_DIEAR_TA_LEN (32u)

/** \brief  Mask for Ifx_CPU_DIEAR_Bits.TA */
#define IFX_CPU_DIEAR_TA_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_DIEAR_Bits.TA */
#define IFX_CPU_DIEAR_TA_OFF (0u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.E_INFO */
#define IFX_CPU_DIETR_E_INFO_LEN (6u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.E_INFO */
#define IFX_CPU_DIETR_E_INFO_MSK (0x3fu)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.E_INFO */
#define IFX_CPU_DIETR_E_INFO_OFF (5u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IE_BI */
#define IFX_CPU_DIETR_IE_BI_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IE_BI */
#define IFX_CPU_DIETR_IE_BI_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IE_BI */
#define IFX_CPU_DIETR_IE_BI_OFF (4u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IE_BS */
#define IFX_CPU_DIETR_IE_BS_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IE_BS */
#define IFX_CPU_DIETR_IE_BS_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IE_BS */
#define IFX_CPU_DIETR_IE_BS_OFF (13u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IE_C */
#define IFX_CPU_DIETR_IE_C_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IE_C */
#define IFX_CPU_DIETR_IE_C_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IE_C */
#define IFX_CPU_DIETR_IE_C_OFF (2u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IE_DUAL */
#define IFX_CPU_DIETR_IE_DUAL_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IE_DUAL */
#define IFX_CPU_DIETR_IE_DUAL_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IE_DUAL */
#define IFX_CPU_DIETR_IE_DUAL_OFF (11u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IE_S */
#define IFX_CPU_DIETR_IE_S_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IE_S */
#define IFX_CPU_DIETR_IE_S_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IE_S */
#define IFX_CPU_DIETR_IE_S_OFF (3u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IE_SP */
#define IFX_CPU_DIETR_IE_SP_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IE_SP */
#define IFX_CPU_DIETR_IE_SP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IE_SP */
#define IFX_CPU_DIETR_IE_SP_OFF (12u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IE_T */
#define IFX_CPU_DIETR_IE_T_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IE_T */
#define IFX_CPU_DIETR_IE_T_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IE_T */
#define IFX_CPU_DIETR_IE_T_OFF (1u)

/** \brief  Length for Ifx_CPU_DIETR_Bits.IED */
#define IFX_CPU_DIETR_IED_LEN (1u)

/** \brief  Mask for Ifx_CPU_DIETR_Bits.IED */
#define IFX_CPU_DIETR_IED_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DIETR_Bits.IED */
#define IFX_CPU_DIETR_IED_OFF (0u)

/** \brief  Length for Ifx_CPU_DMS_Bits.DMSValue */
#define IFX_CPU_DMS_DMSVALUE_LEN (31u)

/** \brief  Mask for Ifx_CPU_DMS_Bits.DMSValue */
#define IFX_CPU_DMS_DMSVALUE_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_DMS_Bits.DMSValue */
#define IFX_CPU_DMS_DMSVALUE_OFF (1u)

/** \brief  Length for Ifx_CPU_DPR_L_Bits.LOWBND */
#define IFX_CPU_DPR_L_LOWBND_LEN (29u)

/** \brief  Mask for Ifx_CPU_DPR_L_Bits.LOWBND */
#define IFX_CPU_DPR_L_LOWBND_MSK (0x1fffffffu)

/** \brief  Offset for Ifx_CPU_DPR_L_Bits.LOWBND */
#define IFX_CPU_DPR_L_LOWBND_OFF (3u)

/** \brief  Length for Ifx_CPU_DPR_U_Bits.UPPBND */
#define IFX_CPU_DPR_U_UPPBND_LEN (29u)

/** \brief  Mask for Ifx_CPU_DPR_U_Bits.UPPBND */
#define IFX_CPU_DPR_U_UPPBND_MSK (0x1fffffffu)

/** \brief  Offset for Ifx_CPU_DPR_U_Bits.UPPBND */
#define IFX_CPU_DPR_U_UPPBND_OFF (3u)

/** \brief  Length for Ifx_CPU_DPRE_Bits.RE */
#define IFX_CPU_DPRE_RE_LEN (16u)

/** \brief  Mask for Ifx_CPU_DPRE_Bits.RE */
#define IFX_CPU_DPRE_RE_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_DPRE_Bits.RE */
#define IFX_CPU_DPRE_RE_OFF (0u)

/** \brief  Length for Ifx_CPU_DPWE_Bits.WE */
#define IFX_CPU_DPWE_WE_LEN (16u)

/** \brief  Mask for Ifx_CPU_DPWE_Bits.WE */
#define IFX_CPU_DPWE_WE_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_DPWE_Bits.WE */
#define IFX_CPU_DPWE_WE_OFF (0u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.ALN */
#define IFX_CPU_DSTR_ALN_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.ALN */
#define IFX_CPU_DSTR_ALN_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.ALN */
#define IFX_CPU_DSTR_ALN_OFF (24u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.CAC */
#define IFX_CPU_DSTR_CAC_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.CAC */
#define IFX_CPU_DSTR_CAC_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.CAC */
#define IFX_CPU_DSTR_CAC_OFF (18u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.CLE */
#define IFX_CPU_DSTR_CLE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.CLE */
#define IFX_CPU_DSTR_CLE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.CLE */
#define IFX_CPU_DSTR_CLE_OFF (20u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.CRE */
#define IFX_CPU_DSTR_CRE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.CRE */
#define IFX_CPU_DSTR_CRE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.CRE */
#define IFX_CPU_DSTR_CRE_OFF (6u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.DTME */
#define IFX_CPU_DSTR_DTME_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.DTME */
#define IFX_CPU_DSTR_DTME_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.DTME */
#define IFX_CPU_DSTR_DTME_OFF (14u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.GAE */
#define IFX_CPU_DSTR_GAE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.GAE */
#define IFX_CPU_DSTR_GAE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.GAE */
#define IFX_CPU_DSTR_GAE_OFF (1u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.LBE */
#define IFX_CPU_DSTR_LBE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.LBE */
#define IFX_CPU_DSTR_LBE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.LBE */
#define IFX_CPU_DSTR_LBE_OFF (2u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.LOE */
#define IFX_CPU_DSTR_LOE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.LOE */
#define IFX_CPU_DSTR_LOE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.LOE */
#define IFX_CPU_DSTR_LOE_OFF (15u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.MPE */
#define IFX_CPU_DSTR_MPE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.MPE */
#define IFX_CPU_DSTR_MPE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.MPE */
#define IFX_CPU_DSTR_MPE_OFF (19u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.SCE */
#define IFX_CPU_DSTR_SCE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.SCE */
#define IFX_CPU_DSTR_SCE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.SCE */
#define IFX_CPU_DSTR_SCE_OFF (17u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.SDE */
#define IFX_CPU_DSTR_SDE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.SDE */
#define IFX_CPU_DSTR_SDE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.SDE */
#define IFX_CPU_DSTR_SDE_OFF (16u)

/** \brief  Length for Ifx_CPU_DSTR_Bits.SRE */
#define IFX_CPU_DSTR_SRE_LEN (1u)

/** \brief  Mask for Ifx_CPU_DSTR_Bits.SRE */
#define IFX_CPU_DSTR_SRE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_DSTR_Bits.SRE */
#define IFX_CPU_DSTR_SRE_OFF (0u)

/** \brief  Length for Ifx_CPU_EXEVT_Bits.BBM */
#define IFX_CPU_EXEVT_BBM_LEN (1u)

/** \brief  Mask for Ifx_CPU_EXEVT_Bits.BBM */
#define IFX_CPU_EXEVT_BBM_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_EXEVT_Bits.BBM */
#define IFX_CPU_EXEVT_BBM_OFF (3u)

/** \brief  Length for Ifx_CPU_EXEVT_Bits.BOD */
#define IFX_CPU_EXEVT_BOD_LEN (1u)

/** \brief  Mask for Ifx_CPU_EXEVT_Bits.BOD */
#define IFX_CPU_EXEVT_BOD_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_EXEVT_Bits.BOD */
#define IFX_CPU_EXEVT_BOD_OFF (4u)

/** \brief  Length for Ifx_CPU_EXEVT_Bits.CNT */
#define IFX_CPU_EXEVT_CNT_LEN (2u)

/** \brief  Mask for Ifx_CPU_EXEVT_Bits.CNT */
#define IFX_CPU_EXEVT_CNT_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_EXEVT_Bits.CNT */
#define IFX_CPU_EXEVT_CNT_OFF (6u)

/** \brief  Length for Ifx_CPU_EXEVT_Bits.EVTA */
#define IFX_CPU_EXEVT_EVTA_LEN (3u)

/** \brief  Mask for Ifx_CPU_EXEVT_Bits.EVTA */
#define IFX_CPU_EXEVT_EVTA_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_EXEVT_Bits.EVTA */
#define IFX_CPU_EXEVT_EVTA_OFF (0u)

/** \brief  Length for Ifx_CPU_EXEVT_Bits.SUSP */
#define IFX_CPU_EXEVT_SUSP_LEN (1u)

/** \brief  Mask for Ifx_CPU_EXEVT_Bits.SUSP */
#define IFX_CPU_EXEVT_SUSP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_EXEVT_Bits.SUSP */
#define IFX_CPU_EXEVT_SUSP_OFF (5u)

/** \brief  Length for Ifx_CPU_FCX_Bits.FCXO */
#define IFX_CPU_FCX_FCXO_LEN (16u)

/** \brief  Mask for Ifx_CPU_FCX_Bits.FCXO */
#define IFX_CPU_FCX_FCXO_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_FCX_Bits.FCXO */
#define IFX_CPU_FCX_FCXO_OFF (0u)

/** \brief  Length for Ifx_CPU_FCX_Bits.FCXS */
#define IFX_CPU_FCX_FCXS_LEN (4u)

/** \brief  Mask for Ifx_CPU_FCX_Bits.FCXS */
#define IFX_CPU_FCX_FCXS_MSK (0xfu)

/** \brief  Offset for Ifx_CPU_FCX_Bits.FCXS */
#define IFX_CPU_FCX_FCXS_OFF (16u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FI */
#define IFX_CPU_FPU_TRAP_CON_FI_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FI */
#define IFX_CPU_FPU_TRAP_CON_FI_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FI */
#define IFX_CPU_FPU_TRAP_CON_FI_OFF (30u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FIE */
#define IFX_CPU_FPU_TRAP_CON_FIE_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FIE */
#define IFX_CPU_FPU_TRAP_CON_FIE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FIE */
#define IFX_CPU_FPU_TRAP_CON_FIE_OFF (22u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FU */
#define IFX_CPU_FPU_TRAP_CON_FU_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FU */
#define IFX_CPU_FPU_TRAP_CON_FU_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FU */
#define IFX_CPU_FPU_TRAP_CON_FU_OFF (27u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FUE */
#define IFX_CPU_FPU_TRAP_CON_FUE_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FUE */
#define IFX_CPU_FPU_TRAP_CON_FUE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FUE */
#define IFX_CPU_FPU_TRAP_CON_FUE_OFF (19u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FV */
#define IFX_CPU_FPU_TRAP_CON_FV_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FV */
#define IFX_CPU_FPU_TRAP_CON_FV_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FV */
#define IFX_CPU_FPU_TRAP_CON_FV_OFF (29u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FVE */
#define IFX_CPU_FPU_TRAP_CON_FVE_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FVE */
#define IFX_CPU_FPU_TRAP_CON_FVE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FVE */
#define IFX_CPU_FPU_TRAP_CON_FVE_OFF (21u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FX */
#define IFX_CPU_FPU_TRAP_CON_FX_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FX */
#define IFX_CPU_FPU_TRAP_CON_FX_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FX */
#define IFX_CPU_FPU_TRAP_CON_FX_OFF (26u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FXE */
#define IFX_CPU_FPU_TRAP_CON_FXE_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FXE */
#define IFX_CPU_FPU_TRAP_CON_FXE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FXE */
#define IFX_CPU_FPU_TRAP_CON_FXE_OFF (18u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FZ */
#define IFX_CPU_FPU_TRAP_CON_FZ_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FZ */
#define IFX_CPU_FPU_TRAP_CON_FZ_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FZ */
#define IFX_CPU_FPU_TRAP_CON_FZ_OFF (28u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.FZE */
#define IFX_CPU_FPU_TRAP_CON_FZE_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.FZE */
#define IFX_CPU_FPU_TRAP_CON_FZE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.FZE */
#define IFX_CPU_FPU_TRAP_CON_FZE_OFF (20u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.RM */
#define IFX_CPU_FPU_TRAP_CON_RM_LEN (2u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.RM */
#define IFX_CPU_FPU_TRAP_CON_RM_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.RM */
#define IFX_CPU_FPU_TRAP_CON_RM_OFF (8u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.TCL */
#define IFX_CPU_FPU_TRAP_CON_TCL_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.TCL */
#define IFX_CPU_FPU_TRAP_CON_TCL_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.TCL */
#define IFX_CPU_FPU_TRAP_CON_TCL_OFF (1u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_CON_Bits.TST */
#define IFX_CPU_FPU_TRAP_CON_TST_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_CON_Bits.TST */
#define IFX_CPU_FPU_TRAP_CON_TST_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_CON_Bits.TST */
#define IFX_CPU_FPU_TRAP_CON_TST_OFF (0u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_OPC_Bits.DREG */
#define IFX_CPU_FPU_TRAP_OPC_DREG_LEN (4u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_OPC_Bits.DREG */
#define IFX_CPU_FPU_TRAP_OPC_DREG_MSK (0xfu)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_OPC_Bits.DREG */
#define IFX_CPU_FPU_TRAP_OPC_DREG_OFF (16u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_OPC_Bits.FMT */
#define IFX_CPU_FPU_TRAP_OPC_FMT_LEN (1u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_OPC_Bits.FMT */
#define IFX_CPU_FPU_TRAP_OPC_FMT_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_OPC_Bits.FMT */
#define IFX_CPU_FPU_TRAP_OPC_FMT_OFF (8u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_OPC_Bits.OPC */
#define IFX_CPU_FPU_TRAP_OPC_OPC_LEN (8u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_OPC_Bits.OPC */
#define IFX_CPU_FPU_TRAP_OPC_OPC_MSK (0xffu)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_OPC_Bits.OPC */
#define IFX_CPU_FPU_TRAP_OPC_OPC_OFF (0u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_PC_Bits.PC */
#define IFX_CPU_FPU_TRAP_PC_PC_LEN (32u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_PC_Bits.PC */
#define IFX_CPU_FPU_TRAP_PC_PC_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_PC_Bits.PC */
#define IFX_CPU_FPU_TRAP_PC_PC_OFF (0u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_SRC1_Bits.SRC1 */
#define IFX_CPU_FPU_TRAP_SRC1_SRC1_LEN (32u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_SRC1_Bits.SRC1 */
#define IFX_CPU_FPU_TRAP_SRC1_SRC1_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_SRC1_Bits.SRC1 */
#define IFX_CPU_FPU_TRAP_SRC1_SRC1_OFF (0u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_SRC2_Bits.SRC2 */
#define IFX_CPU_FPU_TRAP_SRC2_SRC2_LEN (32u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_SRC2_Bits.SRC2 */
#define IFX_CPU_FPU_TRAP_SRC2_SRC2_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_SRC2_Bits.SRC2 */
#define IFX_CPU_FPU_TRAP_SRC2_SRC2_OFF (0u)

/** \brief  Length for Ifx_CPU_FPU_TRAP_SRC3_Bits.SRC3 */
#define IFX_CPU_FPU_TRAP_SRC3_SRC3_LEN (32u)

/** \brief  Mask for Ifx_CPU_FPU_TRAP_SRC3_Bits.SRC3 */
#define IFX_CPU_FPU_TRAP_SRC3_SRC3_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_FPU_TRAP_SRC3_Bits.SRC3 */
#define IFX_CPU_FPU_TRAP_SRC3_SRC3_OFF (0u)

/** \brief  Length for Ifx_CPU_ICNT_Bits.CountValue */
#define IFX_CPU_ICNT_COUNTVALUE_LEN (31u)

/** \brief  Mask for Ifx_CPU_ICNT_Bits.CountValue */
#define IFX_CPU_ICNT_COUNTVALUE_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_ICNT_Bits.CountValue */
#define IFX_CPU_ICNT_COUNTVALUE_OFF (0u)

/** \brief  Length for Ifx_CPU_ICNT_Bits.SOvf */
#define IFX_CPU_ICNT_SOVF_LEN (1u)

/** \brief  Mask for Ifx_CPU_ICNT_Bits.SOvf */
#define IFX_CPU_ICNT_SOVF_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_ICNT_Bits.SOvf */
#define IFX_CPU_ICNT_SOVF_OFF (31u)

/** \brief  Length for Ifx_CPU_ICR_Bits.CCPN */
#define IFX_CPU_ICR_CCPN_LEN (10u)

/** \brief  Mask for Ifx_CPU_ICR_Bits.CCPN */
#define IFX_CPU_ICR_CCPN_MSK (0x3ffu)

/** \brief  Offset for Ifx_CPU_ICR_Bits.CCPN */
#define IFX_CPU_ICR_CCPN_OFF (0u)

/** \brief  Length for Ifx_CPU_ICR_Bits.IE */
#define IFX_CPU_ICR_IE_LEN (1u)

/** \brief  Mask for Ifx_CPU_ICR_Bits.IE */
#define IFX_CPU_ICR_IE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_ICR_Bits.IE */
#define IFX_CPU_ICR_IE_OFF (15u)

/** \brief  Length for Ifx_CPU_ICR_Bits.PIPN */
#define IFX_CPU_ICR_PIPN_LEN (10u)

/** \brief  Mask for Ifx_CPU_ICR_Bits.PIPN */
#define IFX_CPU_ICR_PIPN_MSK (0x3ffu)

/** \brief  Offset for Ifx_CPU_ICR_Bits.PIPN */
#define IFX_CPU_ICR_PIPN_OFF (16u)

/** \brief  Length for Ifx_CPU_ISP_Bits.ISP */
#define IFX_CPU_ISP_ISP_LEN (32u)

/** \brief  Mask for Ifx_CPU_ISP_Bits.ISP */
#define IFX_CPU_ISP_ISP_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_ISP_Bits.ISP */
#define IFX_CPU_ISP_ISP_OFF (0u)

/** \brief  Length for Ifx_CPU_LCX_Bits.LCXO */
#define IFX_CPU_LCX_LCXO_LEN (16u)

/** \brief  Mask for Ifx_CPU_LCX_Bits.LCXO */
#define IFX_CPU_LCX_LCXO_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_LCX_Bits.LCXO */
#define IFX_CPU_LCX_LCXO_OFF (0u)

/** \brief  Length for Ifx_CPU_LCX_Bits.LCXS */
#define IFX_CPU_LCX_LCXS_LEN (4u)

/** \brief  Mask for Ifx_CPU_LCX_Bits.LCXS */
#define IFX_CPU_LCX_LCXS_MSK (0xfu)

/** \brief  Offset for Ifx_CPU_LCX_Bits.LCXS */
#define IFX_CPU_LCX_LCXS_OFF (16u)

/** \brief  Length for Ifx_CPU_M1CNT_Bits.CountValue */
#define IFX_CPU_M1CNT_COUNTVALUE_LEN (31u)

/** \brief  Mask for Ifx_CPU_M1CNT_Bits.CountValue */
#define IFX_CPU_M1CNT_COUNTVALUE_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_M1CNT_Bits.CountValue */
#define IFX_CPU_M1CNT_COUNTVALUE_OFF (0u)

/** \brief  Length for Ifx_CPU_M1CNT_Bits.SOvf */
#define IFX_CPU_M1CNT_SOVF_LEN (1u)

/** \brief  Mask for Ifx_CPU_M1CNT_Bits.SOvf */
#define IFX_CPU_M1CNT_SOVF_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_M1CNT_Bits.SOvf */
#define IFX_CPU_M1CNT_SOVF_OFF (31u)

/** \brief  Length for Ifx_CPU_M2CNT_Bits.CountValue */
#define IFX_CPU_M2CNT_COUNTVALUE_LEN (31u)

/** \brief  Mask for Ifx_CPU_M2CNT_Bits.CountValue */
#define IFX_CPU_M2CNT_COUNTVALUE_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_M2CNT_Bits.CountValue */
#define IFX_CPU_M2CNT_COUNTVALUE_OFF (0u)

/** \brief  Length for Ifx_CPU_M2CNT_Bits.SOvf */
#define IFX_CPU_M2CNT_SOVF_LEN (1u)

/** \brief  Mask for Ifx_CPU_M2CNT_Bits.SOvf */
#define IFX_CPU_M2CNT_SOVF_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_M2CNT_Bits.SOvf */
#define IFX_CPU_M2CNT_SOVF_OFF (31u)

/** \brief  Length for Ifx_CPU_M3CNT_Bits.CountValue */
#define IFX_CPU_M3CNT_COUNTVALUE_LEN (31u)

/** \brief  Mask for Ifx_CPU_M3CNT_Bits.CountValue */
#define IFX_CPU_M3CNT_COUNTVALUE_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_M3CNT_Bits.CountValue */
#define IFX_CPU_M3CNT_COUNTVALUE_OFF (0u)

/** \brief  Length for Ifx_CPU_M3CNT_Bits.SOvf */
#define IFX_CPU_M3CNT_SOVF_LEN (1u)

/** \brief  Mask for Ifx_CPU_M3CNT_Bits.SOvf */
#define IFX_CPU_M3CNT_SOVF_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_M3CNT_Bits.SOvf */
#define IFX_CPU_M3CNT_SOVF_OFF (31u)

/** \brief  Length for Ifx_CPU_PC_Bits.PC */
#define IFX_CPU_PC_PC_LEN (31u)

/** \brief  Mask for Ifx_CPU_PC_Bits.PC */
#define IFX_CPU_PC_PC_MSK (0x7fffffffu)

/** \brief  Offset for Ifx_CPU_PC_Bits.PC */
#define IFX_CPU_PC_PC_OFF (1u)

/** \brief  Length for Ifx_CPU_PCON0_Bits.PCBYP */
#define IFX_CPU_PCON0_PCBYP_LEN (1u)

/** \brief  Mask for Ifx_CPU_PCON0_Bits.PCBYP */
#define IFX_CPU_PCON0_PCBYP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PCON0_Bits.PCBYP */
#define IFX_CPU_PCON0_PCBYP_OFF (1u)

/** \brief  Length for Ifx_CPU_PCON1_Bits.PBINV */
#define IFX_CPU_PCON1_PBINV_LEN (1u)

/** \brief  Mask for Ifx_CPU_PCON1_Bits.PBINV */
#define IFX_CPU_PCON1_PBINV_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PCON1_Bits.PBINV */
#define IFX_CPU_PCON1_PBINV_OFF (1u)

/** \brief  Length for Ifx_CPU_PCON1_Bits.PCINV */
#define IFX_CPU_PCON1_PCINV_LEN (1u)

/** \brief  Mask for Ifx_CPU_PCON1_Bits.PCINV */
#define IFX_CPU_PCON1_PCINV_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PCON1_Bits.PCINV */
#define IFX_CPU_PCON1_PCINV_OFF (0u)

/** \brief  Length for Ifx_CPU_PCON2_Bits.PCACHE_SZE */
#define IFX_CPU_PCON2_PCACHE_SZE_LEN (16u)

/** \brief  Mask for Ifx_CPU_PCON2_Bits.PCACHE_SZE */
#define IFX_CPU_PCON2_PCACHE_SZE_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_PCON2_Bits.PCACHE_SZE */
#define IFX_CPU_PCON2_PCACHE_SZE_OFF (0u)

/** \brief  Length for Ifx_CPU_PCON2_Bits.PSCRATCH_SZE */
#define IFX_CPU_PCON2_PSCRATCH_SZE_LEN (16u)

/** \brief  Mask for Ifx_CPU_PCON2_Bits.PSCRATCH_SZE */
#define IFX_CPU_PCON2_PSCRATCH_SZE_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_PCON2_Bits.PSCRATCH_SZE */
#define IFX_CPU_PCON2_PSCRATCH_SZE_OFF (16u)

/** \brief  Length for Ifx_CPU_PCXI_Bits.PCPN */
#define IFX_CPU_PCXI_PCPN_LEN (10u)

/** \brief  Mask for Ifx_CPU_PCXI_Bits.PCPN */
#define IFX_CPU_PCXI_PCPN_MSK (0x3ffu)

/** \brief  Offset for Ifx_CPU_PCXI_Bits.PCPN */
#define IFX_CPU_PCXI_PCPN_OFF (22u)

/** \brief  Length for Ifx_CPU_PCXI_Bits.PCXO */
#define IFX_CPU_PCXI_PCXO_LEN (16u)

/** \brief  Mask for Ifx_CPU_PCXI_Bits.PCXO */
#define IFX_CPU_PCXI_PCXO_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_PCXI_Bits.PCXO */
#define IFX_CPU_PCXI_PCXO_OFF (0u)

/** \brief  Length for Ifx_CPU_PCXI_Bits.PCXS */
#define IFX_CPU_PCXI_PCXS_LEN (4u)

/** \brief  Mask for Ifx_CPU_PCXI_Bits.PCXS */
#define IFX_CPU_PCXI_PCXS_MSK (0xfu)

/** \brief  Offset for Ifx_CPU_PCXI_Bits.PCXS */
#define IFX_CPU_PCXI_PCXS_OFF (16u)

/** \brief  Length for Ifx_CPU_PCXI_Bits.PIE */
#define IFX_CPU_PCXI_PIE_LEN (1u)

/** \brief  Mask for Ifx_CPU_PCXI_Bits.PIE */
#define IFX_CPU_PCXI_PIE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PCXI_Bits.PIE */
#define IFX_CPU_PCXI_PIE_OFF (21u)

/** \brief  Length for Ifx_CPU_PCXI_Bits.UL */
#define IFX_CPU_PCXI_UL_LEN (1u)

/** \brief  Mask for Ifx_CPU_PCXI_Bits.UL */
#define IFX_CPU_PCXI_UL_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PCXI_Bits.UL */
#define IFX_CPU_PCXI_UL_OFF (20u)

/** \brief  Length for Ifx_CPU_PIEAR_Bits.TA */
#define IFX_CPU_PIEAR_TA_LEN (32u)

/** \brief  Mask for Ifx_CPU_PIEAR_Bits.TA */
#define IFX_CPU_PIEAR_TA_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_PIEAR_Bits.TA */
#define IFX_CPU_PIEAR_TA_OFF (0u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.E_INFO */
#define IFX_CPU_PIETR_E_INFO_LEN (6u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.E_INFO */
#define IFX_CPU_PIETR_E_INFO_MSK (0x3fu)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.E_INFO */
#define IFX_CPU_PIETR_E_INFO_OFF (5u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IE_BI */
#define IFX_CPU_PIETR_IE_BI_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IE_BI */
#define IFX_CPU_PIETR_IE_BI_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IE_BI */
#define IFX_CPU_PIETR_IE_BI_OFF (4u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IE_BS */
#define IFX_CPU_PIETR_IE_BS_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IE_BS */
#define IFX_CPU_PIETR_IE_BS_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IE_BS */
#define IFX_CPU_PIETR_IE_BS_OFF (13u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IE_C */
#define IFX_CPU_PIETR_IE_C_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IE_C */
#define IFX_CPU_PIETR_IE_C_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IE_C */
#define IFX_CPU_PIETR_IE_C_OFF (2u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IE_DUAL */
#define IFX_CPU_PIETR_IE_DUAL_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IE_DUAL */
#define IFX_CPU_PIETR_IE_DUAL_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IE_DUAL */
#define IFX_CPU_PIETR_IE_DUAL_OFF (11u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IE_S */
#define IFX_CPU_PIETR_IE_S_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IE_S */
#define IFX_CPU_PIETR_IE_S_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IE_S */
#define IFX_CPU_PIETR_IE_S_OFF (3u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IE_SP */
#define IFX_CPU_PIETR_IE_SP_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IE_SP */
#define IFX_CPU_PIETR_IE_SP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IE_SP */
#define IFX_CPU_PIETR_IE_SP_OFF (12u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IE_T */
#define IFX_CPU_PIETR_IE_T_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IE_T */
#define IFX_CPU_PIETR_IE_T_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IE_T */
#define IFX_CPU_PIETR_IE_T_OFF (1u)

/** \brief  Length for Ifx_CPU_PIETR_Bits.IED */
#define IFX_CPU_PIETR_IED_LEN (1u)

/** \brief  Mask for Ifx_CPU_PIETR_Bits.IED */
#define IFX_CPU_PIETR_IED_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PIETR_Bits.IED */
#define IFX_CPU_PIETR_IED_OFF (0u)

/** \brief  Length for Ifx_CPU_PMA0_Bits.DAC */
#define IFX_CPU_PMA0_DAC_LEN (3u)

/** \brief  Mask for Ifx_CPU_PMA0_Bits.DAC */
#define IFX_CPU_PMA0_DAC_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_PMA0_Bits.DAC */
#define IFX_CPU_PMA0_DAC_OFF (13u)

/** \brief  Length for Ifx_CPU_PMA1_Bits.CAC */
#define IFX_CPU_PMA1_CAC_LEN (2u)

/** \brief  Mask for Ifx_CPU_PMA1_Bits.CAC */
#define IFX_CPU_PMA1_CAC_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_PMA1_Bits.CAC */
#define IFX_CPU_PMA1_CAC_OFF (14u)

/** \brief  Length for Ifx_CPU_PMA2_Bits.PSI */
#define IFX_CPU_PMA2_PSI_LEN (16u)

/** \brief  Mask for Ifx_CPU_PMA2_Bits.PSI */
#define IFX_CPU_PMA2_PSI_MSK (0xffffu)

/** \brief  Offset for Ifx_CPU_PMA2_Bits.PSI */
#define IFX_CPU_PMA2_PSI_OFF (0u)

/** \brief  Length for Ifx_CPU_PSTR_Bits.FBE */
#define IFX_CPU_PSTR_FBE_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSTR_Bits.FBE */
#define IFX_CPU_PSTR_FBE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSTR_Bits.FBE */
#define IFX_CPU_PSTR_FBE_OFF (2u)

/** \brief  Length for Ifx_CPU_PSTR_Bits.FME */
#define IFX_CPU_PSTR_FME_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSTR_Bits.FME */
#define IFX_CPU_PSTR_FME_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSTR_Bits.FME */
#define IFX_CPU_PSTR_FME_OFF (14u)

/** \brief  Length for Ifx_CPU_PSTR_Bits.FPE */
#define IFX_CPU_PSTR_FPE_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSTR_Bits.FPE */
#define IFX_CPU_PSTR_FPE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSTR_Bits.FPE */
#define IFX_CPU_PSTR_FPE_OFF (12u)

/** \brief  Length for Ifx_CPU_PSTR_Bits.FRE */
#define IFX_CPU_PSTR_FRE_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSTR_Bits.FRE */
#define IFX_CPU_PSTR_FRE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSTR_Bits.FRE */
#define IFX_CPU_PSTR_FRE_OFF (0u)

/** \brief  Length for Ifx_CPU_PSW_Bits.AV */
#define IFX_CPU_PSW_AV_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.AV */
#define IFX_CPU_PSW_AV_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.AV */
#define IFX_CPU_PSW_AV_OFF (28u)

/** \brief  Length for Ifx_CPU_PSW_Bits.C */
#define IFX_CPU_PSW_C_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.C */
#define IFX_CPU_PSW_C_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.C */
#define IFX_CPU_PSW_C_OFF (31u)

/** \brief  Length for Ifx_CPU_PSW_Bits.CDC */
#define IFX_CPU_PSW_CDC_LEN (7u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.CDC */
#define IFX_CPU_PSW_CDC_MSK (0x7fu)

/** \brief  Offset for Ifx_CPU_PSW_Bits.CDC */
#define IFX_CPU_PSW_CDC_OFF (0u)

/** \brief  Length for Ifx_CPU_PSW_Bits.CDE */
#define IFX_CPU_PSW_CDE_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.CDE */
#define IFX_CPU_PSW_CDE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.CDE */
#define IFX_CPU_PSW_CDE_OFF (7u)

/** \brief  Length for Ifx_CPU_PSW_Bits.GW */
#define IFX_CPU_PSW_GW_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.GW */
#define IFX_CPU_PSW_GW_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.GW */
#define IFX_CPU_PSW_GW_OFF (8u)

/** \brief  Length for Ifx_CPU_PSW_Bits.IO */
#define IFX_CPU_PSW_IO_LEN (2u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.IO */
#define IFX_CPU_PSW_IO_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.IO */
#define IFX_CPU_PSW_IO_OFF (10u)

/** \brief  Length for Ifx_CPU_PSW_Bits.IS */
#define IFX_CPU_PSW_IS_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.IS */
#define IFX_CPU_PSW_IS_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.IS */
#define IFX_CPU_PSW_IS_OFF (9u)

/** \brief  Length for Ifx_CPU_PSW_Bits.PRS */
#define IFX_CPU_PSW_PRS_LEN (2u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.PRS */
#define IFX_CPU_PSW_PRS_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.PRS */
#define IFX_CPU_PSW_PRS_OFF (12u)

/** \brief  Length for Ifx_CPU_PSW_Bits.S */
#define IFX_CPU_PSW_S_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.S */
#define IFX_CPU_PSW_S_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.S */
#define IFX_CPU_PSW_S_OFF (14u)

/** \brief  Length for Ifx_CPU_PSW_Bits.SAV */
#define IFX_CPU_PSW_SAV_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.SAV */
#define IFX_CPU_PSW_SAV_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.SAV */
#define IFX_CPU_PSW_SAV_OFF (27u)

/** \brief  Length for Ifx_CPU_PSW_Bits.SV */
#define IFX_CPU_PSW_SV_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.SV */
#define IFX_CPU_PSW_SV_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.SV */
#define IFX_CPU_PSW_SV_OFF (29u)

/** \brief  Length for Ifx_CPU_PSW_Bits.V */
#define IFX_CPU_PSW_V_LEN (1u)

/** \brief  Mask for Ifx_CPU_PSW_Bits.V */
#define IFX_CPU_PSW_V_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_PSW_Bits.V */
#define IFX_CPU_PSW_V_OFF (30u)

/** \brief  Length for Ifx_CPU_SEGEN_Bits.ADFLIP */
#define IFX_CPU_SEGEN_ADFLIP_LEN (8u)

/** \brief  Mask for Ifx_CPU_SEGEN_Bits.ADFLIP */
#define IFX_CPU_SEGEN_ADFLIP_MSK (0xffu)

/** \brief  Offset for Ifx_CPU_SEGEN_Bits.ADFLIP */
#define IFX_CPU_SEGEN_ADFLIP_OFF (0u)

/** \brief  Length for Ifx_CPU_SEGEN_Bits.ADTYPE */
#define IFX_CPU_SEGEN_ADTYPE_LEN (2u)

/** \brief  Mask for Ifx_CPU_SEGEN_Bits.ADTYPE */
#define IFX_CPU_SEGEN_ADTYPE_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_SEGEN_Bits.ADTYPE */
#define IFX_CPU_SEGEN_ADTYPE_OFF (8u)

/** \brief  Length for Ifx_CPU_SEGEN_Bits.AE */
#define IFX_CPU_SEGEN_AE_LEN (1u)

/** \brief  Mask for Ifx_CPU_SEGEN_Bits.AE */
#define IFX_CPU_SEGEN_AE_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SEGEN_Bits.AE */
#define IFX_CPU_SEGEN_AE_OFF (31u)

/** \brief  Length for Ifx_CPU_SMACON_Bits.DC */
#define IFX_CPU_SMACON_DC_LEN (1u)

/** \brief  Mask for Ifx_CPU_SMACON_Bits.DC */
#define IFX_CPU_SMACON_DC_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SMACON_Bits.DC */
#define IFX_CPU_SMACON_DC_OFF (8u)

/** \brief  Length for Ifx_CPU_SMACON_Bits.DT */
#define IFX_CPU_SMACON_DT_LEN (1u)

/** \brief  Mask for Ifx_CPU_SMACON_Bits.DT */
#define IFX_CPU_SMACON_DT_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SMACON_Bits.DT */
#define IFX_CPU_SMACON_DT_OFF (10u)

/** \brief  Length for Ifx_CPU_SMACON_Bits.IODT */
#define IFX_CPU_SMACON_IODT_LEN (1u)

/** \brief  Mask for Ifx_CPU_SMACON_Bits.IODT */
#define IFX_CPU_SMACON_IODT_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SMACON_Bits.IODT */
#define IFX_CPU_SMACON_IODT_OFF (24u)

/** \brief  Length for Ifx_CPU_SMACON_Bits.PC */
#define IFX_CPU_SMACON_PC_LEN (1u)

/** \brief  Mask for Ifx_CPU_SMACON_Bits.PC */
#define IFX_CPU_SMACON_PC_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SMACON_Bits.PC */
#define IFX_CPU_SMACON_PC_OFF (0u)

/** \brief  Length for Ifx_CPU_SMACON_Bits.PT */
#define IFX_CPU_SMACON_PT_LEN (1u)

/** \brief  Mask for Ifx_CPU_SMACON_Bits.PT */
#define IFX_CPU_SMACON_PT_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SMACON_Bits.PT */
#define IFX_CPU_SMACON_PT_OFF (2u)

/** \brief  Length for Ifx_CPU_SPROT_ACCENA_Bits.EN */
#define IFX_CPU_SPROT_ACCENA_EN_LEN (32u)

/** \brief  Mask for Ifx_CPU_SPROT_ACCENA_Bits.EN */
#define IFX_CPU_SPROT_ACCENA_EN_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_SPROT_ACCENA_Bits.EN */
#define IFX_CPU_SPROT_ACCENA_EN_OFF (0u)

/** \brief  Length for Ifx_CPU_SPROT_RGN_ACCENA_Bits.EN */
#define IFX_CPU_SPROT_RGN_ACCENA_EN_LEN (32u)

/** \brief  Mask for Ifx_CPU_SPROT_RGN_ACCENA_Bits.EN */
#define IFX_CPU_SPROT_RGN_ACCENA_EN_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_SPROT_RGN_ACCENA_Bits.EN */
#define IFX_CPU_SPROT_RGN_ACCENA_EN_OFF (0u)

/** \brief  Length for Ifx_CPU_SPROT_RGN_LA_Bits.ADDR */
#define IFX_CPU_SPROT_RGN_LA_ADDR_LEN (27u)

/** \brief  Mask for Ifx_CPU_SPROT_RGN_LA_Bits.ADDR */
#define IFX_CPU_SPROT_RGN_LA_ADDR_MSK (0x7ffffffu)

/** \brief  Offset for Ifx_CPU_SPROT_RGN_LA_Bits.ADDR */
#define IFX_CPU_SPROT_RGN_LA_ADDR_OFF (5u)

/** \brief  Length for Ifx_CPU_SPROT_RGN_UA_Bits.ADDR */
#define IFX_CPU_SPROT_RGN_UA_ADDR_LEN (27u)

/** \brief  Mask for Ifx_CPU_SPROT_RGN_UA_Bits.ADDR */
#define IFX_CPU_SPROT_RGN_UA_ADDR_MSK (0x7ffffffu)

/** \brief  Offset for Ifx_CPU_SPROT_RGN_UA_Bits.ADDR */
#define IFX_CPU_SPROT_RGN_UA_ADDR_OFF (5u)

/** \brief  Length for Ifx_CPU_SWEVT_Bits.BBM */
#define IFX_CPU_SWEVT_BBM_LEN (1u)

/** \brief  Mask for Ifx_CPU_SWEVT_Bits.BBM */
#define IFX_CPU_SWEVT_BBM_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SWEVT_Bits.BBM */
#define IFX_CPU_SWEVT_BBM_OFF (3u)

/** \brief  Length for Ifx_CPU_SWEVT_Bits.BOD */
#define IFX_CPU_SWEVT_BOD_LEN (1u)

/** \brief  Mask for Ifx_CPU_SWEVT_Bits.BOD */
#define IFX_CPU_SWEVT_BOD_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SWEVT_Bits.BOD */
#define IFX_CPU_SWEVT_BOD_OFF (4u)

/** \brief  Length for Ifx_CPU_SWEVT_Bits.CNT */
#define IFX_CPU_SWEVT_CNT_LEN (2u)

/** \brief  Mask for Ifx_CPU_SWEVT_Bits.CNT */
#define IFX_CPU_SWEVT_CNT_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_SWEVT_Bits.CNT */
#define IFX_CPU_SWEVT_CNT_OFF (6u)

/** \brief  Length for Ifx_CPU_SWEVT_Bits.EVTA */
#define IFX_CPU_SWEVT_EVTA_LEN (3u)

/** \brief  Mask for Ifx_CPU_SWEVT_Bits.EVTA */
#define IFX_CPU_SWEVT_EVTA_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_SWEVT_Bits.EVTA */
#define IFX_CPU_SWEVT_EVTA_OFF (0u)

/** \brief  Length for Ifx_CPU_SWEVT_Bits.SUSP */
#define IFX_CPU_SWEVT_SUSP_LEN (1u)

/** \brief  Mask for Ifx_CPU_SWEVT_Bits.SUSP */
#define IFX_CPU_SWEVT_SUSP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SWEVT_Bits.SUSP */
#define IFX_CPU_SWEVT_SUSP_OFF (5u)

/** \brief  Length for Ifx_CPU_SYSCON_Bits.FCDSF */
#define IFX_CPU_SYSCON_FCDSF_LEN (1u)

/** \brief  Mask for Ifx_CPU_SYSCON_Bits.FCDSF */
#define IFX_CPU_SYSCON_FCDSF_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SYSCON_Bits.FCDSF */
#define IFX_CPU_SYSCON_FCDSF_OFF (0u)

/** \brief  Length for Ifx_CPU_SYSCON_Bits.IS */
#define IFX_CPU_SYSCON_IS_LEN (1u)

/** \brief  Mask for Ifx_CPU_SYSCON_Bits.IS */
#define IFX_CPU_SYSCON_IS_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SYSCON_Bits.IS */
#define IFX_CPU_SYSCON_IS_OFF (3u)

/** \brief  Length for Ifx_CPU_SYSCON_Bits.IT */
#define IFX_CPU_SYSCON_IT_LEN (1u)

/** \brief  Mask for Ifx_CPU_SYSCON_Bits.IT */
#define IFX_CPU_SYSCON_IT_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SYSCON_Bits.IT */
#define IFX_CPU_SYSCON_IT_OFF (4u)

/** \brief  Length for Ifx_CPU_SYSCON_Bits.PROTEN */
#define IFX_CPU_SYSCON_PROTEN_LEN (1u)

/** \brief  Mask for Ifx_CPU_SYSCON_Bits.PROTEN */
#define IFX_CPU_SYSCON_PROTEN_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SYSCON_Bits.PROTEN */
#define IFX_CPU_SYSCON_PROTEN_OFF (1u)

/** \brief  Length for Ifx_CPU_SYSCON_Bits.TPROTEN */
#define IFX_CPU_SYSCON_TPROTEN_LEN (1u)

/** \brief  Mask for Ifx_CPU_SYSCON_Bits.TPROTEN */
#define IFX_CPU_SYSCON_TPROTEN_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_SYSCON_Bits.TPROTEN */
#define IFX_CPU_SYSCON_TPROTEN_OFF (2u)

/** \brief  Length for Ifx_CPU_TASK_ASI_Bits.ASI */
#define IFX_CPU_TASK_ASI_ASI_LEN (5u)

/** \brief  Mask for Ifx_CPU_TASK_ASI_Bits.ASI */
#define IFX_CPU_TASK_ASI_ASI_MSK (0x1fu)

/** \brief  Offset for Ifx_CPU_TASK_ASI_Bits.ASI */
#define IFX_CPU_TASK_ASI_ASI_OFF (0u)

/** \brief  Length for Ifx_CPU_TPS_CON_Bits.TEXP0 */
#define IFX_CPU_TPS_CON_TEXP0_LEN (1u)

/** \brief  Mask for Ifx_CPU_TPS_CON_Bits.TEXP0 */
#define IFX_CPU_TPS_CON_TEXP0_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TPS_CON_Bits.TEXP0 */
#define IFX_CPU_TPS_CON_TEXP0_OFF (0u)

/** \brief  Length for Ifx_CPU_TPS_CON_Bits.TEXP1 */
#define IFX_CPU_TPS_CON_TEXP1_LEN (1u)

/** \brief  Mask for Ifx_CPU_TPS_CON_Bits.TEXP1 */
#define IFX_CPU_TPS_CON_TEXP1_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TPS_CON_Bits.TEXP1 */
#define IFX_CPU_TPS_CON_TEXP1_OFF (1u)

/** \brief  Length for Ifx_CPU_TPS_CON_Bits.TEXP2 */
#define IFX_CPU_TPS_CON_TEXP2_LEN (1u)

/** \brief  Mask for Ifx_CPU_TPS_CON_Bits.TEXP2 */
#define IFX_CPU_TPS_CON_TEXP2_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TPS_CON_Bits.TEXP2 */
#define IFX_CPU_TPS_CON_TEXP2_OFF (2u)

/** \brief  Length for Ifx_CPU_TPS_CON_Bits.TTRAP */
#define IFX_CPU_TPS_CON_TTRAP_LEN (1u)

/** \brief  Mask for Ifx_CPU_TPS_CON_Bits.TTRAP */
#define IFX_CPU_TPS_CON_TTRAP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TPS_CON_Bits.TTRAP */
#define IFX_CPU_TPS_CON_TTRAP_OFF (16u)

/** \brief  Length for Ifx_CPU_TPS_TIMER_Bits.Timer */
#define IFX_CPU_TPS_TIMER_TIMER_LEN (32u)

/** \brief  Mask for Ifx_CPU_TPS_TIMER_Bits.Timer */
#define IFX_CPU_TPS_TIMER_TIMER_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_TPS_TIMER_Bits.Timer */
#define IFX_CPU_TPS_TIMER_TIMER_OFF (0u)

/** \brief  Length for Ifx_CPU_TR_ADR_Bits.ADDR */
#define IFX_CPU_TR_ADR_ADDR_LEN (32u)

/** \brief  Mask for Ifx_CPU_TR_ADR_Bits.ADDR */
#define IFX_CPU_TR_ADR_ADDR_MSK (0xffffffffu)

/** \brief  Offset for Ifx_CPU_TR_ADR_Bits.ADDR */
#define IFX_CPU_TR_ADR_ADDR_OFF (0u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.ALD */
#define IFX_CPU_TR_EVT_ALD_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.ALD */
#define IFX_CPU_TR_EVT_ALD_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.ALD */
#define IFX_CPU_TR_EVT_ALD_OFF (28u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.ASI_EN */
#define IFX_CPU_TR_EVT_ASI_EN_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.ASI_EN */
#define IFX_CPU_TR_EVT_ASI_EN_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.ASI_EN */
#define IFX_CPU_TR_EVT_ASI_EN_OFF (15u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.ASI */
#define IFX_CPU_TR_EVT_ASI_LEN (5u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.ASI */
#define IFX_CPU_TR_EVT_ASI_MSK (0x1fu)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.ASI */
#define IFX_CPU_TR_EVT_ASI_OFF (16u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.AST */
#define IFX_CPU_TR_EVT_AST_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.AST */
#define IFX_CPU_TR_EVT_AST_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.AST */
#define IFX_CPU_TR_EVT_AST_OFF (27u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.BBM */
#define IFX_CPU_TR_EVT_BBM_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.BBM */
#define IFX_CPU_TR_EVT_BBM_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.BBM */
#define IFX_CPU_TR_EVT_BBM_OFF (3u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.BOD */
#define IFX_CPU_TR_EVT_BOD_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.BOD */
#define IFX_CPU_TR_EVT_BOD_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.BOD */
#define IFX_CPU_TR_EVT_BOD_OFF (4u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.CNT */
#define IFX_CPU_TR_EVT_CNT_LEN (2u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.CNT */
#define IFX_CPU_TR_EVT_CNT_MSK (0x3u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.CNT */
#define IFX_CPU_TR_EVT_CNT_OFF (6u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.EVTA */
#define IFX_CPU_TR_EVT_EVTA_LEN (3u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.EVTA */
#define IFX_CPU_TR_EVT_EVTA_MSK (0x7u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.EVTA */
#define IFX_CPU_TR_EVT_EVTA_OFF (0u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.RNG */
#define IFX_CPU_TR_EVT_RNG_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.RNG */
#define IFX_CPU_TR_EVT_RNG_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.RNG */
#define IFX_CPU_TR_EVT_RNG_OFF (13u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.SUSP */
#define IFX_CPU_TR_EVT_SUSP_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.SUSP */
#define IFX_CPU_TR_EVT_SUSP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.SUSP */
#define IFX_CPU_TR_EVT_SUSP_OFF (5u)

/** \brief  Length for Ifx_CPU_TR_EVT_Bits.TYP */
#define IFX_CPU_TR_EVT_TYP_LEN (1u)

/** \brief  Mask for Ifx_CPU_TR_EVT_Bits.TYP */
#define IFX_CPU_TR_EVT_TYP_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TR_EVT_Bits.TYP */
#define IFX_CPU_TR_EVT_TYP_OFF (12u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T0 */
#define IFX_CPU_TRIG_ACC_T0_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T0 */
#define IFX_CPU_TRIG_ACC_T0_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T0 */
#define IFX_CPU_TRIG_ACC_T0_OFF (0u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T1 */
#define IFX_CPU_TRIG_ACC_T1_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T1 */
#define IFX_CPU_TRIG_ACC_T1_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T1 */
#define IFX_CPU_TRIG_ACC_T1_OFF (1u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T2 */
#define IFX_CPU_TRIG_ACC_T2_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T2 */
#define IFX_CPU_TRIG_ACC_T2_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T2 */
#define IFX_CPU_TRIG_ACC_T2_OFF (2u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T3 */
#define IFX_CPU_TRIG_ACC_T3_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T3 */
#define IFX_CPU_TRIG_ACC_T3_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T3 */
#define IFX_CPU_TRIG_ACC_T3_OFF (3u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T4 */
#define IFX_CPU_TRIG_ACC_T4_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T4 */
#define IFX_CPU_TRIG_ACC_T4_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T4 */
#define IFX_CPU_TRIG_ACC_T4_OFF (4u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T5 */
#define IFX_CPU_TRIG_ACC_T5_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T5 */
#define IFX_CPU_TRIG_ACC_T5_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T5 */
#define IFX_CPU_TRIG_ACC_T5_OFF (5u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T6 */
#define IFX_CPU_TRIG_ACC_T6_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T6 */
#define IFX_CPU_TRIG_ACC_T6_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T6 */
#define IFX_CPU_TRIG_ACC_T6_OFF (6u)

/** \brief  Length for Ifx_CPU_TRIG_ACC_Bits.T7 */
#define IFX_CPU_TRIG_ACC_T7_LEN (1u)

/** \brief  Mask for Ifx_CPU_TRIG_ACC_Bits.T7 */
#define IFX_CPU_TRIG_ACC_T7_MSK (0x1u)

/** \brief  Offset for Ifx_CPU_TRIG_ACC_Bits.T7 */
#define IFX_CPU_TRIG_ACC_T7_OFF (7u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXCPU_BF_H */
