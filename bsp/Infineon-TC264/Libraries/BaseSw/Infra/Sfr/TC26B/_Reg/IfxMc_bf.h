/**
 * \file IfxMc_bf.h
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
 * \defgroup IfxLld_Mc_BitfieldsMask Bitfields mask and offset
 * \ingroup IfxLld_Mc
 * 
 */
#ifndef IFXMC_BF_H
#define IFXMC_BF_H 1
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Mc_BitfieldsMask
 * \{  */

/** \brief  Length for Ifx_MC_CONFIG0_Bits.ACCSTYPE */
#define IFX_MC_CONFIG0_ACCSTYPE_LEN (8u)

/** \brief  Mask for Ifx_MC_CONFIG0_Bits.ACCSTYPE */
#define IFX_MC_CONFIG0_ACCSTYPE_MSK (0xffu)

/** \brief  Offset for Ifx_MC_CONFIG0_Bits.ACCSTYPE */
#define IFX_MC_CONFIG0_ACCSTYPE_OFF (0u)

/** \brief  Length for Ifx_MC_CONFIG0_Bits.NUMACCS */
#define IFX_MC_CONFIG0_NUMACCS_LEN (4u)

/** \brief  Mask for Ifx_MC_CONFIG0_Bits.NUMACCS */
#define IFX_MC_CONFIG0_NUMACCS_MSK (0xfu)

/** \brief  Offset for Ifx_MC_CONFIG0_Bits.NUMACCS */
#define IFX_MC_CONFIG0_NUMACCS_OFF (12u)

/** \brief  Length for Ifx_MC_CONFIG1_Bits.ACCSPAT */
#define IFX_MC_CONFIG1_ACCSPAT_LEN (8u)

/** \brief  Mask for Ifx_MC_CONFIG1_Bits.ACCSPAT */
#define IFX_MC_CONFIG1_ACCSPAT_MSK (0xffu)

/** \brief  Offset for Ifx_MC_CONFIG1_Bits.ACCSPAT */
#define IFX_MC_CONFIG1_ACCSPAT_OFF (0u)

/** \brief  Length for Ifx_MC_CONFIG1_Bits.AG_MOD */
#define IFX_MC_CONFIG1_AG_MOD_LEN (4u)

/** \brief  Mask for Ifx_MC_CONFIG1_Bits.AG_MOD */
#define IFX_MC_CONFIG1_AG_MOD_MSK (0xfu)

/** \brief  Offset for Ifx_MC_CONFIG1_Bits.AG_MOD */
#define IFX_MC_CONFIG1_AG_MOD_OFF (12u)

/** \brief  Length for Ifx_MC_CONFIG1_Bits.SELFASTB */
#define IFX_MC_CONFIG1_SELFASTB_LEN (4u)

/** \brief  Mask for Ifx_MC_CONFIG1_Bits.SELFASTB */
#define IFX_MC_CONFIG1_SELFASTB_MSK (0xfu)

/** \brief  Offset for Ifx_MC_CONFIG1_Bits.SELFASTB */
#define IFX_MC_CONFIG1_SELFASTB_OFF (8u)

/** \brief  Length for Ifx_MC_ECCD_Bits.AENE */
#define IFX_MC_ECCD_AENE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.AENE */
#define IFX_MC_ECCD_AENE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.AENE */
#define IFX_MC_ECCD_AENE_OFF (13u)

/** \brief  Length for Ifx_MC_ECCD_Bits.AERR */
#define IFX_MC_ECCD_AERR_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.AERR */
#define IFX_MC_ECCD_AERR_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.AERR */
#define IFX_MC_ECCD_AERR_OFF (3u)

/** \brief  Length for Ifx_MC_ECCD_Bits.CENE */
#define IFX_MC_ECCD_CENE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.CENE */
#define IFX_MC_ECCD_CENE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.CENE */
#define IFX_MC_ECCD_CENE_OFF (11u)

/** \brief  Length for Ifx_MC_ECCD_Bits.CERR */
#define IFX_MC_ECCD_CERR_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.CERR */
#define IFX_MC_ECCD_CERR_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.CERR */
#define IFX_MC_ECCD_CERR_OFF (1u)

/** \brief  Length for Ifx_MC_ECCD_Bits.ECE */
#define IFX_MC_ECCD_ECE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.ECE */
#define IFX_MC_ECCD_ECE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.ECE */
#define IFX_MC_ECCD_ECE_OFF (14u)

/** \brief  Length for Ifx_MC_ECCD_Bits.EOV */
#define IFX_MC_ECCD_EOV_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.EOV */
#define IFX_MC_ECCD_EOV_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.EOV */
#define IFX_MC_ECCD_EOV_OFF (15u)

/** \brief  Length for Ifx_MC_ECCD_Bits.RARVAL */
#define IFX_MC_ECCD_RARVAL_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.RARVAL */
#define IFX_MC_ECCD_RARVAL_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.RARVAL */
#define IFX_MC_ECCD_RARVAL_OFF (10u)

/** \brief  Length for Ifx_MC_ECCD_Bits.SERR */
#define IFX_MC_ECCD_SERR_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.SERR */
#define IFX_MC_ECCD_SERR_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.SERR */
#define IFX_MC_ECCD_SERR_OFF (0u)

/** \brief  Length for Ifx_MC_ECCD_Bits.TRC */
#define IFX_MC_ECCD_TRC_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.TRC */
#define IFX_MC_ECCD_TRC_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.TRC */
#define IFX_MC_ECCD_TRC_OFF (4u)

/** \brief  Length for Ifx_MC_ECCD_Bits.UENE */
#define IFX_MC_ECCD_UENE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.UENE */
#define IFX_MC_ECCD_UENE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.UENE */
#define IFX_MC_ECCD_UENE_OFF (12u)

/** \brief  Length for Ifx_MC_ECCD_Bits.UERR */
#define IFX_MC_ECCD_UERR_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.UERR */
#define IFX_MC_ECCD_UERR_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCD_Bits.UERR */
#define IFX_MC_ECCD_UERR_OFF (2u)

/** \brief  Length for Ifx_MC_ECCD_Bits.VAL */
#define IFX_MC_ECCD_VAL_LEN (5u)

/** \brief  Mask for Ifx_MC_ECCD_Bits.VAL */
#define IFX_MC_ECCD_VAL_MSK (0x1fu)

/** \brief  Offset for Ifx_MC_ECCD_Bits.VAL */
#define IFX_MC_ECCD_VAL_OFF (5u)

/** \brief  Length for Ifx_MC_ECCS_Bits.AENE */
#define IFX_MC_ECCS_AENE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.AENE */
#define IFX_MC_ECCS_AENE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.AENE */
#define IFX_MC_ECCS_AENE_OFF (2u)

/** \brief  Length for Ifx_MC_ECCS_Bits.BFLE */
#define IFX_MC_ECCS_BFLE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.BFLE */
#define IFX_MC_ECCS_BFLE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.BFLE */
#define IFX_MC_ECCS_BFLE_OFF (5u)

/** \brief  Length for Ifx_MC_ECCS_Bits.CENE */
#define IFX_MC_ECCS_CENE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.CENE */
#define IFX_MC_ECCS_CENE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.CENE */
#define IFX_MC_ECCS_CENE_OFF (0u)

/** \brief  Length for Ifx_MC_ECCS_Bits.ECCMAP */
#define IFX_MC_ECCS_ECCMAP_LEN (2u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.ECCMAP */
#define IFX_MC_ECCS_ECCMAP_MSK (0x3u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.ECCMAP */
#define IFX_MC_ECCS_ECCMAP_OFF (8u)

/** \brief  Length for Ifx_MC_ECCS_Bits.ECE */
#define IFX_MC_ECCS_ECE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.ECE */
#define IFX_MC_ECCS_ECE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.ECE */
#define IFX_MC_ECCS_ECE_OFF (3u)

/** \brief  Length for Ifx_MC_ECCS_Bits.SFLE */
#define IFX_MC_ECCS_SFLE_LEN (2u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.SFLE */
#define IFX_MC_ECCS_SFLE_MSK (0x3u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.SFLE */
#define IFX_MC_ECCS_SFLE_OFF (6u)

/** \brief  Length for Ifx_MC_ECCS_Bits.TC_WAY_SEL */
#define IFX_MC_ECCS_TC_WAY_SEL_LEN (2u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.TC_WAY_SEL */
#define IFX_MC_ECCS_TC_WAY_SEL_MSK (0x3u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.TC_WAY_SEL */
#define IFX_MC_ECCS_TC_WAY_SEL_OFF (10u)

/** \brief  Length for Ifx_MC_ECCS_Bits.TRE */
#define IFX_MC_ECCS_TRE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.TRE */
#define IFX_MC_ECCS_TRE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.TRE */
#define IFX_MC_ECCS_TRE_OFF (4u)

/** \brief  Length for Ifx_MC_ECCS_Bits.UENE */
#define IFX_MC_ECCS_UENE_LEN (1u)

/** \brief  Mask for Ifx_MC_ECCS_Bits.UENE */
#define IFX_MC_ECCS_UENE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_ECCS_Bits.UENE */
#define IFX_MC_ECCS_UENE_OFF (1u)

/** \brief  Length for Ifx_MC_ETRR_Bits.ADDR */
#define IFX_MC_ETRR_ADDR_LEN (13u)

/** \brief  Mask for Ifx_MC_ETRR_Bits.ADDR */
#define IFX_MC_ETRR_ADDR_MSK (0x1fffu)

/** \brief  Offset for Ifx_MC_ETRR_Bits.ADDR */
#define IFX_MC_ETRR_ADDR_OFF (0u)

/** \brief  Length for Ifx_MC_ETRR_Bits.MBI */
#define IFX_MC_ETRR_MBI_LEN (3u)

/** \brief  Mask for Ifx_MC_ETRR_Bits.MBI */
#define IFX_MC_ETRR_MBI_MSK (0x7u)

/** \brief  Offset for Ifx_MC_ETRR_Bits.MBI */
#define IFX_MC_ETRR_MBI_OFF (13u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.BITTOG */
#define IFX_MC_MCONTROL_BITTOG_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.BITTOG */
#define IFX_MC_MCONTROL_BITTOG_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.BITTOG */
#define IFX_MC_MCONTROL_BITTOG_OFF (7u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.DINIT */
#define IFX_MC_MCONTROL_DINIT_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.DINIT */
#define IFX_MC_MCONTROL_DINIT_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.DINIT */
#define IFX_MC_MCONTROL_DINIT_OFF (4u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.DIR */
#define IFX_MC_MCONTROL_DIR_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.DIR */
#define IFX_MC_MCONTROL_DIR_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.DIR */
#define IFX_MC_MCONTROL_DIR_OFF (3u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.ESTF */
#define IFX_MC_MCONTROL_ESTF_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.ESTF */
#define IFX_MC_MCONTROL_ESTF_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.ESTF */
#define IFX_MC_MCONTROL_ESTF_OFF (2u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.FAILDMP */
#define IFX_MC_MCONTROL_FAILDMP_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.FAILDMP */
#define IFX_MC_MCONTROL_FAILDMP_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.FAILDMP */
#define IFX_MC_MCONTROL_FAILDMP_OFF (9u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.GP_BASE */
#define IFX_MC_MCONTROL_GP_BASE_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.GP_BASE */
#define IFX_MC_MCONTROL_GP_BASE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.GP_BASE */
#define IFX_MC_MCONTROL_GP_BASE_OFF (8u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.RCADR */
#define IFX_MC_MCONTROL_RCADR_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.RCADR */
#define IFX_MC_MCONTROL_RCADR_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.RCADR */
#define IFX_MC_MCONTROL_RCADR_OFF (5u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.RESUME */
#define IFX_MC_MCONTROL_RESUME_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.RESUME */
#define IFX_MC_MCONTROL_RESUME_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.RESUME */
#define IFX_MC_MCONTROL_RESUME_OFF (1u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.ROWTOG */
#define IFX_MC_MCONTROL_ROWTOG_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.ROWTOG */
#define IFX_MC_MCONTROL_ROWTOG_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.ROWTOG */
#define IFX_MC_MCONTROL_ROWTOG_OFF (6u)

/** \brief  Length for Ifx_MC_MCONTROL_Bits.START */
#define IFX_MC_MCONTROL_START_LEN (1u)

/** \brief  Mask for Ifx_MC_MCONTROL_Bits.START */
#define IFX_MC_MCONTROL_START_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MCONTROL_Bits.START */
#define IFX_MC_MCONTROL_START_OFF (0u)

/** \brief  Length for Ifx_MC_MSTATUS_Bits.DONE */
#define IFX_MC_MSTATUS_DONE_LEN (1u)

/** \brief  Mask for Ifx_MC_MSTATUS_Bits.DONE */
#define IFX_MC_MSTATUS_DONE_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MSTATUS_Bits.DONE */
#define IFX_MC_MSTATUS_DONE_OFF (0u)

/** \brief  Length for Ifx_MC_MSTATUS_Bits.FAIL */
#define IFX_MC_MSTATUS_FAIL_LEN (1u)

/** \brief  Mask for Ifx_MC_MSTATUS_Bits.FAIL */
#define IFX_MC_MSTATUS_FAIL_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MSTATUS_Bits.FAIL */
#define IFX_MC_MSTATUS_FAIL_OFF (1u)

/** \brief  Length for Ifx_MC_MSTATUS_Bits.FDA */
#define IFX_MC_MSTATUS_FDA_LEN (1u)

/** \brief  Mask for Ifx_MC_MSTATUS_Bits.FDA */
#define IFX_MC_MSTATUS_FDA_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MSTATUS_Bits.FDA */
#define IFX_MC_MSTATUS_FDA_OFF (2u)

/** \brief  Length for Ifx_MC_MSTATUS_Bits.SFAIL */
#define IFX_MC_MSTATUS_SFAIL_LEN (1u)

/** \brief  Mask for Ifx_MC_MSTATUS_Bits.SFAIL */
#define IFX_MC_MSTATUS_SFAIL_MSK (0x1u)

/** \brief  Offset for Ifx_MC_MSTATUS_Bits.SFAIL */
#define IFX_MC_MSTATUS_SFAIL_OFF (3u)

/** \brief  Length for Ifx_MC_RANGE_Bits.ADDR */
#define IFX_MC_RANGE_ADDR_LEN (15u)

/** \brief  Mask for Ifx_MC_RANGE_Bits.ADDR */
#define IFX_MC_RANGE_ADDR_MSK (0x7fffu)

/** \brief  Offset for Ifx_MC_RANGE_Bits.ADDR */
#define IFX_MC_RANGE_ADDR_OFF (0u)

/** \brief  Length for Ifx_MC_RANGE_Bits.RAEN */
#define IFX_MC_RANGE_RAEN_LEN (1u)

/** \brief  Mask for Ifx_MC_RANGE_Bits.RAEN */
#define IFX_MC_RANGE_RAEN_MSK (0x1u)

/** \brief  Offset for Ifx_MC_RANGE_Bits.RAEN */
#define IFX_MC_RANGE_RAEN_OFF (15u)

/** \brief  Length for Ifx_MC_RDBFL_Bits.WDATA */
#define IFX_MC_RDBFL_WDATA_LEN (16u)

/** \brief  Mask for Ifx_MC_RDBFL_Bits.WDATA */
#define IFX_MC_RDBFL_WDATA_MSK (0xffffu)

/** \brief  Offset for Ifx_MC_RDBFL_Bits.WDATA */
#define IFX_MC_RDBFL_WDATA_OFF (0u)

/** \brief  Length for Ifx_MC_REVID_Bits.REV_ID */
#define IFX_MC_REVID_REV_ID_LEN (16u)

/** \brief  Mask for Ifx_MC_REVID_Bits.REV_ID */
#define IFX_MC_REVID_REV_ID_MSK (0xffffu)

/** \brief  Offset for Ifx_MC_REVID_Bits.REV_ID */
#define IFX_MC_REVID_REV_ID_OFF (0u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXMC_BF_H */
