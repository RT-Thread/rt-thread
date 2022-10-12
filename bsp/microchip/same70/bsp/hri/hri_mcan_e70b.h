/**
 * \file
 *
 * \brief SAM MCAN
 *
 * Copyright (c) 2017-2019 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifdef _SAME70_MCAN_COMPONENT_
#ifndef _HRI_MCAN_E70B_H_INCLUDED_
#define _HRI_MCAN_E70B_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_MCAN_CRITICAL_SECTIONS)
#define MCAN_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define MCAN_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define MCAN_CRITICAL_SECTION_ENTER()
#define MCAN_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_mcan_cccr_reg_t;
typedef uint32_t hri_mcan_crel_reg_t;
typedef uint32_t hri_mcan_cust_reg_t;
typedef uint32_t hri_mcan_dbtp_reg_t;
typedef uint32_t hri_mcan_ecr_reg_t;
typedef uint32_t hri_mcan_endn_reg_t;
typedef uint32_t hri_mcan_gfc_reg_t;
typedef uint32_t hri_mcan_hpms_reg_t;
typedef uint32_t hri_mcan_ie_reg_t;
typedef uint32_t hri_mcan_ile_reg_t;
typedef uint32_t hri_mcan_ils_reg_t;
typedef uint32_t hri_mcan_ir_reg_t;
typedef uint32_t hri_mcan_nbtp_reg_t;
typedef uint32_t hri_mcan_ndat1_reg_t;
typedef uint32_t hri_mcan_ndat2_reg_t;
typedef uint32_t hri_mcan_psr_reg_t;
typedef uint32_t hri_mcan_rwd_reg_t;
typedef uint32_t hri_mcan_rxbc_reg_t;
typedef uint32_t hri_mcan_rxesc_reg_t;
typedef uint32_t hri_mcan_rxf0a_reg_t;
typedef uint32_t hri_mcan_rxf0c_reg_t;
typedef uint32_t hri_mcan_rxf0s_reg_t;
typedef uint32_t hri_mcan_rxf1a_reg_t;
typedef uint32_t hri_mcan_rxf1c_reg_t;
typedef uint32_t hri_mcan_rxf1s_reg_t;
typedef uint32_t hri_mcan_sidfc_reg_t;
typedef uint32_t hri_mcan_tdcr_reg_t;
typedef uint32_t hri_mcan_test_reg_t;
typedef uint32_t hri_mcan_tocc_reg_t;
typedef uint32_t hri_mcan_tocv_reg_t;
typedef uint32_t hri_mcan_tscc_reg_t;
typedef uint32_t hri_mcan_tscv_reg_t;
typedef uint32_t hri_mcan_txbar_reg_t;
typedef uint32_t hri_mcan_txbc_reg_t;
typedef uint32_t hri_mcan_txbcf_reg_t;
typedef uint32_t hri_mcan_txbcie_reg_t;
typedef uint32_t hri_mcan_txbcr_reg_t;
typedef uint32_t hri_mcan_txbrp_reg_t;
typedef uint32_t hri_mcan_txbtie_reg_t;
typedef uint32_t hri_mcan_txbto_reg_t;
typedef uint32_t hri_mcan_txefa_reg_t;
typedef uint32_t hri_mcan_txefc_reg_t;
typedef uint32_t hri_mcan_txefs_reg_t;
typedef uint32_t hri_mcan_txesc_reg_t;
typedef uint32_t hri_mcan_txfqs_reg_t;
typedef uint32_t hri_mcan_xidam_reg_t;
typedef uint32_t hri_mcan_xidfc_reg_t;

static inline hri_mcan_crel_reg_t hri_mcan_get_CREL_DAY_bf(const void *const hw, hri_mcan_crel_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_DAY(mask)) >> MCAN_CREL_DAY_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_read_CREL_DAY_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_DAY_Msk) >> MCAN_CREL_DAY_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_get_CREL_MON_bf(const void *const hw, hri_mcan_crel_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_MON(mask)) >> MCAN_CREL_MON_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_read_CREL_MON_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_MON_Msk) >> MCAN_CREL_MON_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_get_CREL_YEAR_bf(const void *const hw, hri_mcan_crel_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_YEAR(mask)) >> MCAN_CREL_YEAR_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_read_CREL_YEAR_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_YEAR_Msk) >> MCAN_CREL_YEAR_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_get_CREL_SUBSTEP_bf(const void *const hw, hri_mcan_crel_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_SUBSTEP(mask)) >> MCAN_CREL_SUBSTEP_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_read_CREL_SUBSTEP_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_SUBSTEP_Msk) >> MCAN_CREL_SUBSTEP_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_get_CREL_STEP_bf(const void *const hw, hri_mcan_crel_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_STEP(mask)) >> MCAN_CREL_STEP_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_read_CREL_STEP_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_STEP_Msk) >> MCAN_CREL_STEP_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_get_CREL_REL_bf(const void *const hw, hri_mcan_crel_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_REL(mask)) >> MCAN_CREL_REL_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_read_CREL_REL_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_CREL & MCAN_CREL_REL_Msk) >> MCAN_CREL_REL_Pos;
}

static inline hri_mcan_crel_reg_t hri_mcan_get_CREL_reg(const void *const hw, hri_mcan_crel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CREL;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_crel_reg_t hri_mcan_read_CREL_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_CREL;
}

static inline hri_mcan_endn_reg_t hri_mcan_get_ENDN_ETV_bf(const void *const hw, hri_mcan_endn_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_ENDN & MCAN_ENDN_ETV(mask)) >> MCAN_ENDN_ETV_Pos;
}

static inline hri_mcan_endn_reg_t hri_mcan_read_ENDN_ETV_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_ENDN & MCAN_ENDN_ETV_Msk) >> MCAN_ENDN_ETV_Pos;
}

static inline hri_mcan_endn_reg_t hri_mcan_get_ENDN_reg(const void *const hw, hri_mcan_endn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ENDN;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_endn_reg_t hri_mcan_read_ENDN_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_ENDN;
}

static inline bool hri_mcan_get_ECR_RP_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_ECR & MCAN_ECR_RP) > 0;
}

static inline hri_mcan_ecr_reg_t hri_mcan_get_ECR_TEC_bf(const void *const hw, hri_mcan_ecr_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_ECR & MCAN_ECR_TEC(mask)) >> MCAN_ECR_TEC_Pos;
}

static inline hri_mcan_ecr_reg_t hri_mcan_read_ECR_TEC_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_ECR & MCAN_ECR_TEC_Msk) >> MCAN_ECR_TEC_Pos;
}

static inline hri_mcan_ecr_reg_t hri_mcan_get_ECR_REC_bf(const void *const hw, hri_mcan_ecr_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_ECR & MCAN_ECR_REC(mask)) >> MCAN_ECR_REC_Pos;
}

static inline hri_mcan_ecr_reg_t hri_mcan_read_ECR_REC_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_ECR & MCAN_ECR_REC_Msk) >> MCAN_ECR_REC_Pos;
}

static inline hri_mcan_ecr_reg_t hri_mcan_get_ECR_CEL_bf(const void *const hw, hri_mcan_ecr_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_ECR & MCAN_ECR_CEL(mask)) >> MCAN_ECR_CEL_Pos;
}

static inline hri_mcan_ecr_reg_t hri_mcan_read_ECR_CEL_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_ECR & MCAN_ECR_CEL_Msk) >> MCAN_ECR_CEL_Pos;
}

static inline hri_mcan_ecr_reg_t hri_mcan_get_ECR_reg(const void *const hw, hri_mcan_ecr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ECR;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_ecr_reg_t hri_mcan_read_ECR_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_ECR;
}

static inline bool hri_mcan_get_PSR_EP_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_EP) > 0;
}

static inline bool hri_mcan_get_PSR_EW_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_EW) > 0;
}

static inline bool hri_mcan_get_PSR_BO_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_BO) > 0;
}

static inline bool hri_mcan_get_PSR_RESI_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_RESI) > 0;
}

static inline bool hri_mcan_get_PSR_RBRS_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_RBRS) > 0;
}

static inline bool hri_mcan_get_PSR_RFDF_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_RFDF) > 0;
}

static inline bool hri_mcan_get_PSR_PXE_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_PXE) > 0;
}

static inline hri_mcan_psr_reg_t hri_mcan_get_PSR_LEC_bf(const void *const hw, hri_mcan_psr_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_LEC(mask)) >> MCAN_PSR_LEC_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_read_PSR_LEC_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_LEC_Msk) >> MCAN_PSR_LEC_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_get_PSR_ACT_bf(const void *const hw, hri_mcan_psr_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_ACT(mask)) >> MCAN_PSR_ACT_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_read_PSR_ACT_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_ACT_Msk) >> MCAN_PSR_ACT_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_get_PSR_DLEC_bf(const void *const hw, hri_mcan_psr_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_DLEC(mask)) >> MCAN_PSR_DLEC_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_read_PSR_DLEC_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_DLEC_Msk) >> MCAN_PSR_DLEC_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_get_PSR_TDCV_bf(const void *const hw, hri_mcan_psr_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_TDCV(mask)) >> MCAN_PSR_TDCV_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_read_PSR_TDCV_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_PSR & MCAN_PSR_TDCV_Msk) >> MCAN_PSR_TDCV_Pos;
}

static inline hri_mcan_psr_reg_t hri_mcan_get_PSR_reg(const void *const hw, hri_mcan_psr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_PSR;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_psr_reg_t hri_mcan_read_PSR_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_PSR;
}

static inline bool hri_mcan_get_HPMS_FLST_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_HPMS & MCAN_HPMS_FLST) > 0;
}

static inline hri_mcan_hpms_reg_t hri_mcan_get_HPMS_BIDX_bf(const void *const hw, hri_mcan_hpms_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_HPMS & MCAN_HPMS_BIDX(mask)) >> MCAN_HPMS_BIDX_Pos;
}

static inline hri_mcan_hpms_reg_t hri_mcan_read_HPMS_BIDX_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_HPMS & MCAN_HPMS_BIDX_Msk) >> MCAN_HPMS_BIDX_Pos;
}

static inline hri_mcan_hpms_reg_t hri_mcan_get_HPMS_MSI_bf(const void *const hw, hri_mcan_hpms_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_HPMS & MCAN_HPMS_MSI(mask)) >> MCAN_HPMS_MSI_Pos;
}

static inline hri_mcan_hpms_reg_t hri_mcan_read_HPMS_MSI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_HPMS & MCAN_HPMS_MSI_Msk) >> MCAN_HPMS_MSI_Pos;
}

static inline hri_mcan_hpms_reg_t hri_mcan_get_HPMS_FIDX_bf(const void *const hw, hri_mcan_hpms_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_HPMS & MCAN_HPMS_FIDX(mask)) >> MCAN_HPMS_FIDX_Pos;
}

static inline hri_mcan_hpms_reg_t hri_mcan_read_HPMS_FIDX_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_HPMS & MCAN_HPMS_FIDX_Msk) >> MCAN_HPMS_FIDX_Pos;
}

static inline hri_mcan_hpms_reg_t hri_mcan_get_HPMS_reg(const void *const hw, hri_mcan_hpms_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_HPMS;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_hpms_reg_t hri_mcan_read_HPMS_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_HPMS;
}

static inline bool hri_mcan_get_RXF0S_F0F_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_F0F) > 0;
}

static inline bool hri_mcan_get_RXF0S_RF0L_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_RF0L) > 0;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_get_RXF0S_F0FL_bf(const void *const hw, hri_mcan_rxf0s_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_F0FL(mask)) >> MCAN_RXF0S_F0FL_Pos;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_read_RXF0S_F0FL_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_F0FL_Msk) >> MCAN_RXF0S_F0FL_Pos;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_get_RXF0S_F0GI_bf(const void *const hw, hri_mcan_rxf0s_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_F0GI(mask)) >> MCAN_RXF0S_F0GI_Pos;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_read_RXF0S_F0GI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_F0GI_Msk) >> MCAN_RXF0S_F0GI_Pos;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_get_RXF0S_F0PI_bf(const void *const hw, hri_mcan_rxf0s_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_F0PI(mask)) >> MCAN_RXF0S_F0PI_Pos;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_read_RXF0S_F0PI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF0S & MCAN_RXF0S_F0PI_Msk) >> MCAN_RXF0S_F0PI_Pos;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_get_RXF0S_reg(const void *const hw, hri_mcan_rxf0s_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0S;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_rxf0s_reg_t hri_mcan_read_RXF0S_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXF0S;
}

static inline bool hri_mcan_get_RXF1S_F1F_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_F1F) > 0;
}

static inline bool hri_mcan_get_RXF1S_RF1L_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_RF1L) > 0;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_get_RXF1S_F1FL_bf(const void *const hw, hri_mcan_rxf1s_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_F1FL(mask)) >> MCAN_RXF1S_F1FL_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_read_RXF1S_F1FL_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_F1FL_Msk) >> MCAN_RXF1S_F1FL_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_get_RXF1S_F1GI_bf(const void *const hw, hri_mcan_rxf1s_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_F1GI(mask)) >> MCAN_RXF1S_F1GI_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_read_RXF1S_F1GI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_F1GI_Msk) >> MCAN_RXF1S_F1GI_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_get_RXF1S_F1PI_bf(const void *const hw, hri_mcan_rxf1s_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_F1PI(mask)) >> MCAN_RXF1S_F1PI_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_read_RXF1S_F1PI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_F1PI_Msk) >> MCAN_RXF1S_F1PI_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_get_RXF1S_DMS_bf(const void *const hw, hri_mcan_rxf1s_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_DMS(mask)) >> MCAN_RXF1S_DMS_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_read_RXF1S_DMS_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_RXF1S & MCAN_RXF1S_DMS_Msk) >> MCAN_RXF1S_DMS_Pos;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_get_RXF1S_reg(const void *const hw, hri_mcan_rxf1s_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1S;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_rxf1s_reg_t hri_mcan_read_RXF1S_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXF1S;
}

static inline bool hri_mcan_get_TXFQS_TFQF_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXFQS & MCAN_TXFQS_TFQF) > 0;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_get_TXFQS_TFFL_bf(const void *const hw, hri_mcan_txfqs_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_TXFQS & MCAN_TXFQS_TFFL(mask)) >> MCAN_TXFQS_TFFL_Pos;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_read_TXFQS_TFFL_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXFQS & MCAN_TXFQS_TFFL_Msk) >> MCAN_TXFQS_TFFL_Pos;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_get_TXFQS_TFGI_bf(const void *const hw, hri_mcan_txfqs_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_TXFQS & MCAN_TXFQS_TFGI(mask)) >> MCAN_TXFQS_TFGI_Pos;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_read_TXFQS_TFGI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXFQS & MCAN_TXFQS_TFGI_Msk) >> MCAN_TXFQS_TFGI_Pos;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_get_TXFQS_TFQPI_bf(const void *const hw, hri_mcan_txfqs_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_TXFQS & MCAN_TXFQS_TFQPI(mask)) >> MCAN_TXFQS_TFQPI_Pos;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_read_TXFQS_TFQPI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXFQS & MCAN_TXFQS_TFQPI_Msk) >> MCAN_TXFQS_TFQPI_Pos;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_get_TXFQS_reg(const void *const hw, hri_mcan_txfqs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXFQS;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_txfqs_reg_t hri_mcan_read_TXFQS_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXFQS;
}

static inline bool hri_mcan_get_TXBRP_TRP0_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP0) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP1_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP1) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP2_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP2) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP3_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP3) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP4_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP4) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP5_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP5) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP6_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP6) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP7_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP7) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP8_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP8) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP9_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP9) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP10_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP10) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP11_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP11) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP12_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP12) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP13_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP13) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP14_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP14) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP15_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP15) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP16_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP16) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP17_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP17) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP18_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP18) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP19_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP19) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP20_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP20) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP21_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP21) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP22_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP22) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP23_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP23) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP24_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP24) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP25_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP25) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP26_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP26) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP27_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP27) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP28_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP28) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP29_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP29) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP30_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP30) > 0;
}

static inline bool hri_mcan_get_TXBRP_TRP31_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBRP & MCAN_TXBRP_TRP31) > 0;
}

static inline hri_mcan_txbrp_reg_t hri_mcan_get_TXBRP_reg(const void *const hw, hri_mcan_txbrp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBRP;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_txbrp_reg_t hri_mcan_read_TXBRP_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBRP;
}

static inline bool hri_mcan_get_TXBTO_TO0_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO0) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO1_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO1) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO2_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO2) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO3_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO3) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO4_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO4) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO5_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO5) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO6_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO6) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO7_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO7) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO8_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO8) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO9_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO9) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO10_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO10) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO11_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO11) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO12_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO12) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO13_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO13) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO14_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO14) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO15_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO15) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO16_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO16) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO17_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO17) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO18_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO18) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO19_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO19) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO20_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO20) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO21_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO21) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO22_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO22) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO23_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO23) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO24_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO24) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO25_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO25) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO26_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO26) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO27_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO27) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO28_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO28) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO29_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO29) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO30_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO30) > 0;
}

static inline bool hri_mcan_get_TXBTO_TO31_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBTO & MCAN_TXBTO_TO31) > 0;
}

static inline hri_mcan_txbto_reg_t hri_mcan_get_TXBTO_reg(const void *const hw, hri_mcan_txbto_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTO;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_txbto_reg_t hri_mcan_read_TXBTO_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBTO;
}

static inline bool hri_mcan_get_TXBCF_CF0_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF0) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF1_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF1) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF2_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF2) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF3_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF3) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF4_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF4) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF5_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF5) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF6_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF6) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF7_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF7) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF8_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF8) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF9_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF9) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF10_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF10) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF11_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF11) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF12_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF12) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF13_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF13) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF14_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF14) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF15_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF15) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF16_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF16) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF17_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF17) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF18_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF18) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF19_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF19) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF20_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF20) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF21_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF21) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF22_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF22) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF23_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF23) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF24_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF24) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF25_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF25) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF26_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF26) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF27_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF27) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF28_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF28) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF29_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF29) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF30_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF30) > 0;
}

static inline bool hri_mcan_get_TXBCF_CF31_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXBCF & MCAN_TXBCF_CF31) > 0;
}

static inline hri_mcan_txbcf_reg_t hri_mcan_get_TXBCF_reg(const void *const hw, hri_mcan_txbcf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCF;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_txbcf_reg_t hri_mcan_read_TXBCF_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBCF;
}

static inline bool hri_mcan_get_TXEFS_EFF_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_EFF) > 0;
}

static inline bool hri_mcan_get_TXEFS_TEFL_bit(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_TEFL) > 0;
}

static inline hri_mcan_txefs_reg_t hri_mcan_get_TXEFS_EFFL_bf(const void *const hw, hri_mcan_txefs_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_EFFL(mask)) >> MCAN_TXEFS_EFFL_Pos;
}

static inline hri_mcan_txefs_reg_t hri_mcan_read_TXEFS_EFFL_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_EFFL_Msk) >> MCAN_TXEFS_EFFL_Pos;
}

static inline hri_mcan_txefs_reg_t hri_mcan_get_TXEFS_EFGI_bf(const void *const hw, hri_mcan_txefs_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_EFGI(mask)) >> MCAN_TXEFS_EFGI_Pos;
}

static inline hri_mcan_txefs_reg_t hri_mcan_read_TXEFS_EFGI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_EFGI_Msk) >> MCAN_TXEFS_EFGI_Pos;
}

static inline hri_mcan_txefs_reg_t hri_mcan_get_TXEFS_EFPI_bf(const void *const hw, hri_mcan_txefs_reg_t mask)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_EFPI(mask)) >> MCAN_TXEFS_EFPI_Pos;
}

static inline hri_mcan_txefs_reg_t hri_mcan_read_TXEFS_EFPI_bf(const void *const hw)
{
	return (((Mcan *)hw)->MCAN_TXEFS & MCAN_TXEFS_EFPI_Msk) >> MCAN_TXEFS_EFPI_Pos;
}

static inline hri_mcan_txefs_reg_t hri_mcan_get_TXEFS_reg(const void *const hw, hri_mcan_txefs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFS;
	tmp &= mask;
	return tmp;
}

static inline hri_mcan_txefs_reg_t hri_mcan_read_TXEFS_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXEFS;
}

static inline void hri_mcan_set_CUST_CSV_bf(const void *const hw, hri_mcan_cust_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CUST |= MCAN_CUST_CSV(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_cust_reg_t hri_mcan_get_CUST_CSV_bf(const void *const hw, hri_mcan_cust_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CUST;
	tmp = (tmp & MCAN_CUST_CSV(mask)) >> MCAN_CUST_CSV_Pos;
	return tmp;
}

static inline void hri_mcan_write_CUST_CSV_bf(const void *const hw, hri_mcan_cust_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CUST;
	tmp &= ~MCAN_CUST_CSV_Msk;
	tmp |= MCAN_CUST_CSV(data);
	((Mcan *)hw)->MCAN_CUST = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CUST_CSV_bf(const void *const hw, hri_mcan_cust_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CUST &= ~MCAN_CUST_CSV(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CUST_CSV_bf(const void *const hw, hri_mcan_cust_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CUST ^= MCAN_CUST_CSV(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_cust_reg_t hri_mcan_read_CUST_CSV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CUST;
	tmp = (tmp & MCAN_CUST_CSV_Msk) >> MCAN_CUST_CSV_Pos;
	return tmp;
}

static inline void hri_mcan_set_CUST_reg(const void *const hw, hri_mcan_cust_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CUST |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_cust_reg_t hri_mcan_get_CUST_reg(const void *const hw, hri_mcan_cust_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CUST;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_CUST_reg(const void *const hw, hri_mcan_cust_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CUST = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CUST_reg(const void *const hw, hri_mcan_cust_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CUST &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CUST_reg(const void *const hw, hri_mcan_cust_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CUST ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_cust_reg_t hri_mcan_read_CUST_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_CUST;
}

static inline void hri_mcan_set_DBTP_TDC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP |= MCAN_DBTP_TDC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_DBTP_TDC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_TDC) >> MCAN_DBTP_TDC_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_DBTP_TDC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp &= ~MCAN_DBTP_TDC;
	tmp |= value << MCAN_DBTP_TDC_Pos;
	((Mcan *)hw)->MCAN_DBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_DBTP_TDC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP &= ~MCAN_DBTP_TDC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_DBTP_TDC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP ^= MCAN_DBTP_TDC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_DBTP_DSJW_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP |= MCAN_DBTP_DSJW(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_get_DBTP_DSJW_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DSJW(mask)) >> MCAN_DBTP_DSJW_Pos;
	return tmp;
}

static inline void hri_mcan_write_DBTP_DSJW_bf(const void *const hw, hri_mcan_dbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp &= ~MCAN_DBTP_DSJW_Msk;
	tmp |= MCAN_DBTP_DSJW(data);
	((Mcan *)hw)->MCAN_DBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_DBTP_DSJW_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP &= ~MCAN_DBTP_DSJW(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_DBTP_DSJW_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP ^= MCAN_DBTP_DSJW(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_read_DBTP_DSJW_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DSJW_Msk) >> MCAN_DBTP_DSJW_Pos;
	return tmp;
}

static inline void hri_mcan_set_DBTP_DTSEG2_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP |= MCAN_DBTP_DTSEG2(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_get_DBTP_DTSEG2_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DTSEG2(mask)) >> MCAN_DBTP_DTSEG2_Pos;
	return tmp;
}

static inline void hri_mcan_write_DBTP_DTSEG2_bf(const void *const hw, hri_mcan_dbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp &= ~MCAN_DBTP_DTSEG2_Msk;
	tmp |= MCAN_DBTP_DTSEG2(data);
	((Mcan *)hw)->MCAN_DBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_DBTP_DTSEG2_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP &= ~MCAN_DBTP_DTSEG2(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_DBTP_DTSEG2_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP ^= MCAN_DBTP_DTSEG2(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_read_DBTP_DTSEG2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DTSEG2_Msk) >> MCAN_DBTP_DTSEG2_Pos;
	return tmp;
}

static inline void hri_mcan_set_DBTP_DTSEG1_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP |= MCAN_DBTP_DTSEG1(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_get_DBTP_DTSEG1_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DTSEG1(mask)) >> MCAN_DBTP_DTSEG1_Pos;
	return tmp;
}

static inline void hri_mcan_write_DBTP_DTSEG1_bf(const void *const hw, hri_mcan_dbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp &= ~MCAN_DBTP_DTSEG1_Msk;
	tmp |= MCAN_DBTP_DTSEG1(data);
	((Mcan *)hw)->MCAN_DBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_DBTP_DTSEG1_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP &= ~MCAN_DBTP_DTSEG1(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_DBTP_DTSEG1_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP ^= MCAN_DBTP_DTSEG1(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_read_DBTP_DTSEG1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DTSEG1_Msk) >> MCAN_DBTP_DTSEG1_Pos;
	return tmp;
}

static inline void hri_mcan_set_DBTP_DBRP_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP |= MCAN_DBTP_DBRP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_get_DBTP_DBRP_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DBRP(mask)) >> MCAN_DBTP_DBRP_Pos;
	return tmp;
}

static inline void hri_mcan_write_DBTP_DBRP_bf(const void *const hw, hri_mcan_dbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp &= ~MCAN_DBTP_DBRP_Msk;
	tmp |= MCAN_DBTP_DBRP(data);
	((Mcan *)hw)->MCAN_DBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_DBTP_DBRP_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP &= ~MCAN_DBTP_DBRP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_DBTP_DBRP_bf(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP ^= MCAN_DBTP_DBRP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_read_DBTP_DBRP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp = (tmp & MCAN_DBTP_DBRP_Msk) >> MCAN_DBTP_DBRP_Pos;
	return tmp;
}

static inline void hri_mcan_set_DBTP_reg(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_get_DBTP_reg(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_DBTP;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_DBTP_reg(const void *const hw, hri_mcan_dbtp_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_DBTP_reg(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_DBTP_reg(const void *const hw, hri_mcan_dbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_DBTP ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_dbtp_reg_t hri_mcan_read_DBTP_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_DBTP;
}

static inline void hri_mcan_set_TEST_LBCK_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST |= MCAN_TEST_LBCK;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TEST_LBCK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp = (tmp & MCAN_TEST_LBCK) >> MCAN_TEST_LBCK_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TEST_LBCK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp &= ~MCAN_TEST_LBCK;
	tmp |= value << MCAN_TEST_LBCK_Pos;
	((Mcan *)hw)->MCAN_TEST = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TEST_LBCK_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST &= ~MCAN_TEST_LBCK;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TEST_LBCK_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST ^= MCAN_TEST_LBCK;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TEST_RX_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST |= MCAN_TEST_RX;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TEST_RX_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp = (tmp & MCAN_TEST_RX) >> MCAN_TEST_RX_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TEST_RX_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp &= ~MCAN_TEST_RX;
	tmp |= value << MCAN_TEST_RX_Pos;
	((Mcan *)hw)->MCAN_TEST = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TEST_RX_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST &= ~MCAN_TEST_RX;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TEST_RX_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST ^= MCAN_TEST_RX;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TEST_TX_bf(const void *const hw, hri_mcan_test_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST |= MCAN_TEST_TX(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_test_reg_t hri_mcan_get_TEST_TX_bf(const void *const hw, hri_mcan_test_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp = (tmp & MCAN_TEST_TX(mask)) >> MCAN_TEST_TX_Pos;
	return tmp;
}

static inline void hri_mcan_write_TEST_TX_bf(const void *const hw, hri_mcan_test_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp &= ~MCAN_TEST_TX_Msk;
	tmp |= MCAN_TEST_TX(data);
	((Mcan *)hw)->MCAN_TEST = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TEST_TX_bf(const void *const hw, hri_mcan_test_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST &= ~MCAN_TEST_TX(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TEST_TX_bf(const void *const hw, hri_mcan_test_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST ^= MCAN_TEST_TX(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_test_reg_t hri_mcan_read_TEST_TX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp = (tmp & MCAN_TEST_TX_Msk) >> MCAN_TEST_TX_Pos;
	return tmp;
}

static inline void hri_mcan_set_TEST_reg(const void *const hw, hri_mcan_test_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_test_reg_t hri_mcan_get_TEST_reg(const void *const hw, hri_mcan_test_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TEST;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TEST_reg(const void *const hw, hri_mcan_test_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TEST_reg(const void *const hw, hri_mcan_test_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TEST_reg(const void *const hw, hri_mcan_test_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TEST ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_test_reg_t hri_mcan_read_TEST_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TEST;
}

static inline void hri_mcan_set_RWD_WDC_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD |= MCAN_RWD_WDC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rwd_reg_t hri_mcan_get_RWD_WDC_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RWD;
	tmp = (tmp & MCAN_RWD_WDC(mask)) >> MCAN_RWD_WDC_Pos;
	return tmp;
}

static inline void hri_mcan_write_RWD_WDC_bf(const void *const hw, hri_mcan_rwd_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RWD;
	tmp &= ~MCAN_RWD_WDC_Msk;
	tmp |= MCAN_RWD_WDC(data);
	((Mcan *)hw)->MCAN_RWD = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RWD_WDC_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD &= ~MCAN_RWD_WDC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RWD_WDC_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD ^= MCAN_RWD_WDC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rwd_reg_t hri_mcan_read_RWD_WDC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RWD;
	tmp = (tmp & MCAN_RWD_WDC_Msk) >> MCAN_RWD_WDC_Pos;
	return tmp;
}

static inline void hri_mcan_set_RWD_WDV_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD |= MCAN_RWD_WDV(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rwd_reg_t hri_mcan_get_RWD_WDV_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RWD;
	tmp = (tmp & MCAN_RWD_WDV(mask)) >> MCAN_RWD_WDV_Pos;
	return tmp;
}

static inline void hri_mcan_write_RWD_WDV_bf(const void *const hw, hri_mcan_rwd_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RWD;
	tmp &= ~MCAN_RWD_WDV_Msk;
	tmp |= MCAN_RWD_WDV(data);
	((Mcan *)hw)->MCAN_RWD = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RWD_WDV_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD &= ~MCAN_RWD_WDV(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RWD_WDV_bf(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD ^= MCAN_RWD_WDV(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rwd_reg_t hri_mcan_read_RWD_WDV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RWD;
	tmp = (tmp & MCAN_RWD_WDV_Msk) >> MCAN_RWD_WDV_Pos;
	return tmp;
}

static inline void hri_mcan_set_RWD_reg(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rwd_reg_t hri_mcan_get_RWD_reg(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RWD;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_RWD_reg(const void *const hw, hri_mcan_rwd_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RWD_reg(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RWD_reg(const void *const hw, hri_mcan_rwd_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RWD ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rwd_reg_t hri_mcan_read_RWD_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RWD;
}

static inline void hri_mcan_set_CCCR_INIT_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_INIT;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_INIT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_INIT) >> MCAN_CCCR_INIT_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_INIT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_INIT;
	tmp |= value << MCAN_CCCR_INIT_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_INIT_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_INIT;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_INIT_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_INIT;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_CCE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_CCE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_CCE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_CCE) >> MCAN_CCCR_CCE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_CCE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_CCE;
	tmp |= value << MCAN_CCCR_CCE_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_CCE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_CCE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_CCE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_CCE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_ASM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_ASM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_ASM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_ASM) >> MCAN_CCCR_ASM_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_ASM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_ASM;
	tmp |= value << MCAN_CCCR_ASM_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_ASM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_ASM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_ASM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_ASM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_CSA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_CSA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_CSA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_CSA) >> MCAN_CCCR_CSA_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_CSA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_CSA;
	tmp |= value << MCAN_CCCR_CSA_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_CSA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_CSA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_CSA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_CSA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_CSR_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_CSR;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_CSR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_CSR) >> MCAN_CCCR_CSR_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_CSR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_CSR;
	tmp |= value << MCAN_CCCR_CSR_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_CSR_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_CSR;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_CSR_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_CSR;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_MON_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_MON;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_MON_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_MON) >> MCAN_CCCR_MON_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_MON_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_MON;
	tmp |= value << MCAN_CCCR_MON_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_MON_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_MON;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_MON_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_MON;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_DAR_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_DAR;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_DAR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_DAR) >> MCAN_CCCR_DAR_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_DAR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_DAR;
	tmp |= value << MCAN_CCCR_DAR_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_DAR_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_DAR;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_DAR_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_DAR;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_TEST_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_TEST;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_TEST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_TEST) >> MCAN_CCCR_TEST_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_TEST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_TEST;
	tmp |= value << MCAN_CCCR_TEST_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_TEST_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_TEST;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_TEST_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_TEST;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_FDOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_FDOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_FDOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_FDOE) >> MCAN_CCCR_FDOE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_FDOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_FDOE;
	tmp |= value << MCAN_CCCR_FDOE_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_FDOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_FDOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_FDOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_FDOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_BRSE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_BRSE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_BRSE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_BRSE) >> MCAN_CCCR_BRSE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_BRSE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_BRSE;
	tmp |= value << MCAN_CCCR_BRSE_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_BRSE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_BRSE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_BRSE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_BRSE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_PXHD_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_PXHD;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_PXHD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_PXHD) >> MCAN_CCCR_PXHD_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_PXHD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_PXHD;
	tmp |= value << MCAN_CCCR_PXHD_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_PXHD_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_PXHD;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_PXHD_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_PXHD;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_EFBI_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_EFBI;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_EFBI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_EFBI) >> MCAN_CCCR_EFBI_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_EFBI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_EFBI;
	tmp |= value << MCAN_CCCR_EFBI_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_EFBI_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_EFBI;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_EFBI_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_EFBI;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_TXP_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_TXP;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_TXP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_TXP) >> MCAN_CCCR_TXP_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_TXP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_TXP;
	tmp |= value << MCAN_CCCR_TXP_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_TXP_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_TXP;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_TXP_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_TXP;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_NISO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= MCAN_CCCR_NISO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_CCCR_NISO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp = (tmp & MCAN_CCCR_NISO) >> MCAN_CCCR_NISO_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_CCCR_NISO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= ~MCAN_CCCR_NISO;
	tmp |= value << MCAN_CCCR_NISO_Pos;
	((Mcan *)hw)->MCAN_CCCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_NISO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~MCAN_CCCR_NISO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_NISO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= MCAN_CCCR_NISO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_CCCR_reg(const void *const hw, hri_mcan_cccr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_cccr_reg_t hri_mcan_get_CCCR_reg(const void *const hw, hri_mcan_cccr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_CCCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_CCCR_reg(const void *const hw, hri_mcan_cccr_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_CCCR_reg(const void *const hw, hri_mcan_cccr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_CCCR_reg(const void *const hw, hri_mcan_cccr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_CCCR ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_cccr_reg_t hri_mcan_read_CCCR_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_CCCR;
}

static inline void hri_mcan_set_NBTP_NTSEG2_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP |= MCAN_NBTP_NTSEG2(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_get_NBTP_NTSEG2_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NTSEG2(mask)) >> MCAN_NBTP_NTSEG2_Pos;
	return tmp;
}

static inline void hri_mcan_write_NBTP_NTSEG2_bf(const void *const hw, hri_mcan_nbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp &= ~MCAN_NBTP_NTSEG2_Msk;
	tmp |= MCAN_NBTP_NTSEG2(data);
	((Mcan *)hw)->MCAN_NBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NBTP_NTSEG2_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP &= ~MCAN_NBTP_NTSEG2(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NBTP_NTSEG2_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP ^= MCAN_NBTP_NTSEG2(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_read_NBTP_NTSEG2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NTSEG2_Msk) >> MCAN_NBTP_NTSEG2_Pos;
	return tmp;
}

static inline void hri_mcan_set_NBTP_NTSEG1_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP |= MCAN_NBTP_NTSEG1(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_get_NBTP_NTSEG1_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NTSEG1(mask)) >> MCAN_NBTP_NTSEG1_Pos;
	return tmp;
}

static inline void hri_mcan_write_NBTP_NTSEG1_bf(const void *const hw, hri_mcan_nbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp &= ~MCAN_NBTP_NTSEG1_Msk;
	tmp |= MCAN_NBTP_NTSEG1(data);
	((Mcan *)hw)->MCAN_NBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NBTP_NTSEG1_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP &= ~MCAN_NBTP_NTSEG1(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NBTP_NTSEG1_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP ^= MCAN_NBTP_NTSEG1(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_read_NBTP_NTSEG1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NTSEG1_Msk) >> MCAN_NBTP_NTSEG1_Pos;
	return tmp;
}

static inline void hri_mcan_set_NBTP_NBRP_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP |= MCAN_NBTP_NBRP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_get_NBTP_NBRP_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NBRP(mask)) >> MCAN_NBTP_NBRP_Pos;
	return tmp;
}

static inline void hri_mcan_write_NBTP_NBRP_bf(const void *const hw, hri_mcan_nbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp &= ~MCAN_NBTP_NBRP_Msk;
	tmp |= MCAN_NBTP_NBRP(data);
	((Mcan *)hw)->MCAN_NBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NBTP_NBRP_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP &= ~MCAN_NBTP_NBRP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NBTP_NBRP_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP ^= MCAN_NBTP_NBRP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_read_NBTP_NBRP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NBRP_Msk) >> MCAN_NBTP_NBRP_Pos;
	return tmp;
}

static inline void hri_mcan_set_NBTP_NSJW_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP |= MCAN_NBTP_NSJW(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_get_NBTP_NSJW_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NSJW(mask)) >> MCAN_NBTP_NSJW_Pos;
	return tmp;
}

static inline void hri_mcan_write_NBTP_NSJW_bf(const void *const hw, hri_mcan_nbtp_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp &= ~MCAN_NBTP_NSJW_Msk;
	tmp |= MCAN_NBTP_NSJW(data);
	((Mcan *)hw)->MCAN_NBTP = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NBTP_NSJW_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP &= ~MCAN_NBTP_NSJW(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NBTP_NSJW_bf(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP ^= MCAN_NBTP_NSJW(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_read_NBTP_NSJW_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp = (tmp & MCAN_NBTP_NSJW_Msk) >> MCAN_NBTP_NSJW_Pos;
	return tmp;
}

static inline void hri_mcan_set_NBTP_reg(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_get_NBTP_reg(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NBTP;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_NBTP_reg(const void *const hw, hri_mcan_nbtp_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NBTP_reg(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NBTP_reg(const void *const hw, hri_mcan_nbtp_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NBTP ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_nbtp_reg_t hri_mcan_read_NBTP_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_NBTP;
}

static inline void hri_mcan_set_TSCC_TSS_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC |= MCAN_TSCC_TSS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscc_reg_t hri_mcan_get_TSCC_TSS_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCC;
	tmp = (tmp & MCAN_TSCC_TSS(mask)) >> MCAN_TSCC_TSS_Pos;
	return tmp;
}

static inline void hri_mcan_write_TSCC_TSS_bf(const void *const hw, hri_mcan_tscc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TSCC;
	tmp &= ~MCAN_TSCC_TSS_Msk;
	tmp |= MCAN_TSCC_TSS(data);
	((Mcan *)hw)->MCAN_TSCC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TSCC_TSS_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC &= ~MCAN_TSCC_TSS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TSCC_TSS_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC ^= MCAN_TSCC_TSS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscc_reg_t hri_mcan_read_TSCC_TSS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCC;
	tmp = (tmp & MCAN_TSCC_TSS_Msk) >> MCAN_TSCC_TSS_Pos;
	return tmp;
}

static inline void hri_mcan_set_TSCC_TCP_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC |= MCAN_TSCC_TCP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscc_reg_t hri_mcan_get_TSCC_TCP_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCC;
	tmp = (tmp & MCAN_TSCC_TCP(mask)) >> MCAN_TSCC_TCP_Pos;
	return tmp;
}

static inline void hri_mcan_write_TSCC_TCP_bf(const void *const hw, hri_mcan_tscc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TSCC;
	tmp &= ~MCAN_TSCC_TCP_Msk;
	tmp |= MCAN_TSCC_TCP(data);
	((Mcan *)hw)->MCAN_TSCC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TSCC_TCP_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC &= ~MCAN_TSCC_TCP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TSCC_TCP_bf(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC ^= MCAN_TSCC_TCP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscc_reg_t hri_mcan_read_TSCC_TCP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCC;
	tmp = (tmp & MCAN_TSCC_TCP_Msk) >> MCAN_TSCC_TCP_Pos;
	return tmp;
}

static inline void hri_mcan_set_TSCC_reg(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscc_reg_t hri_mcan_get_TSCC_reg(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TSCC_reg(const void *const hw, hri_mcan_tscc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TSCC_reg(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TSCC_reg(const void *const hw, hri_mcan_tscc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscc_reg_t hri_mcan_read_TSCC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TSCC;
}

static inline void hri_mcan_set_TSCV_TSC_bf(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCV |= MCAN_TSCV_TSC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscv_reg_t hri_mcan_get_TSCV_TSC_bf(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCV;
	tmp = (tmp & MCAN_TSCV_TSC(mask)) >> MCAN_TSCV_TSC_Pos;
	return tmp;
}

static inline void hri_mcan_write_TSCV_TSC_bf(const void *const hw, hri_mcan_tscv_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TSCV;
	tmp &= ~MCAN_TSCV_TSC_Msk;
	tmp |= MCAN_TSCV_TSC(data);
	((Mcan *)hw)->MCAN_TSCV = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TSCV_TSC_bf(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCV &= ~MCAN_TSCV_TSC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TSCV_TSC_bf(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCV ^= MCAN_TSCV_TSC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscv_reg_t hri_mcan_read_TSCV_TSC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCV;
	tmp = (tmp & MCAN_TSCV_TSC_Msk) >> MCAN_TSCV_TSC_Pos;
	return tmp;
}

static inline void hri_mcan_set_TSCV_reg(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCV |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscv_reg_t hri_mcan_get_TSCV_reg(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TSCV;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TSCV_reg(const void *const hw, hri_mcan_tscv_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCV = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TSCV_reg(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCV &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TSCV_reg(const void *const hw, hri_mcan_tscv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TSCV ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tscv_reg_t hri_mcan_read_TSCV_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TSCV;
}

static inline void hri_mcan_set_TOCC_ETOC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC |= MCAN_TOCC_ETOC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TOCC_ETOC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp = (tmp & MCAN_TOCC_ETOC) >> MCAN_TOCC_ETOC_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TOCC_ETOC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp &= ~MCAN_TOCC_ETOC;
	tmp |= value << MCAN_TOCC_ETOC_Pos;
	((Mcan *)hw)->MCAN_TOCC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TOCC_ETOC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC &= ~MCAN_TOCC_ETOC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TOCC_ETOC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC ^= MCAN_TOCC_ETOC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TOCC_TOS_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC |= MCAN_TOCC_TOS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocc_reg_t hri_mcan_get_TOCC_TOS_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp = (tmp & MCAN_TOCC_TOS(mask)) >> MCAN_TOCC_TOS_Pos;
	return tmp;
}

static inline void hri_mcan_write_TOCC_TOS_bf(const void *const hw, hri_mcan_tocc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp &= ~MCAN_TOCC_TOS_Msk;
	tmp |= MCAN_TOCC_TOS(data);
	((Mcan *)hw)->MCAN_TOCC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TOCC_TOS_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC &= ~MCAN_TOCC_TOS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TOCC_TOS_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC ^= MCAN_TOCC_TOS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocc_reg_t hri_mcan_read_TOCC_TOS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp = (tmp & MCAN_TOCC_TOS_Msk) >> MCAN_TOCC_TOS_Pos;
	return tmp;
}

static inline void hri_mcan_set_TOCC_TOP_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC |= MCAN_TOCC_TOP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocc_reg_t hri_mcan_get_TOCC_TOP_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp = (tmp & MCAN_TOCC_TOP(mask)) >> MCAN_TOCC_TOP_Pos;
	return tmp;
}

static inline void hri_mcan_write_TOCC_TOP_bf(const void *const hw, hri_mcan_tocc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp &= ~MCAN_TOCC_TOP_Msk;
	tmp |= MCAN_TOCC_TOP(data);
	((Mcan *)hw)->MCAN_TOCC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TOCC_TOP_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC &= ~MCAN_TOCC_TOP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TOCC_TOP_bf(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC ^= MCAN_TOCC_TOP(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocc_reg_t hri_mcan_read_TOCC_TOP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp = (tmp & MCAN_TOCC_TOP_Msk) >> MCAN_TOCC_TOP_Pos;
	return tmp;
}

static inline void hri_mcan_set_TOCC_reg(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocc_reg_t hri_mcan_get_TOCC_reg(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TOCC_reg(const void *const hw, hri_mcan_tocc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TOCC_reg(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TOCC_reg(const void *const hw, hri_mcan_tocc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocc_reg_t hri_mcan_read_TOCC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TOCC;
}

static inline void hri_mcan_set_TOCV_TOC_bf(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCV |= MCAN_TOCV_TOC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocv_reg_t hri_mcan_get_TOCV_TOC_bf(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCV;
	tmp = (tmp & MCAN_TOCV_TOC(mask)) >> MCAN_TOCV_TOC_Pos;
	return tmp;
}

static inline void hri_mcan_write_TOCV_TOC_bf(const void *const hw, hri_mcan_tocv_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TOCV;
	tmp &= ~MCAN_TOCV_TOC_Msk;
	tmp |= MCAN_TOCV_TOC(data);
	((Mcan *)hw)->MCAN_TOCV = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TOCV_TOC_bf(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCV &= ~MCAN_TOCV_TOC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TOCV_TOC_bf(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCV ^= MCAN_TOCV_TOC(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocv_reg_t hri_mcan_read_TOCV_TOC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCV;
	tmp = (tmp & MCAN_TOCV_TOC_Msk) >> MCAN_TOCV_TOC_Pos;
	return tmp;
}

static inline void hri_mcan_set_TOCV_reg(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCV |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocv_reg_t hri_mcan_get_TOCV_reg(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TOCV;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TOCV_reg(const void *const hw, hri_mcan_tocv_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCV = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TOCV_reg(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCV &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TOCV_reg(const void *const hw, hri_mcan_tocv_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TOCV ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tocv_reg_t hri_mcan_read_TOCV_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TOCV;
}

static inline void hri_mcan_set_TDCR_TDCF_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR |= MCAN_TDCR_TDCF(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tdcr_reg_t hri_mcan_get_TDCR_TDCF_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TDCR;
	tmp = (tmp & MCAN_TDCR_TDCF(mask)) >> MCAN_TDCR_TDCF_Pos;
	return tmp;
}

static inline void hri_mcan_write_TDCR_TDCF_bf(const void *const hw, hri_mcan_tdcr_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TDCR;
	tmp &= ~MCAN_TDCR_TDCF_Msk;
	tmp |= MCAN_TDCR_TDCF(data);
	((Mcan *)hw)->MCAN_TDCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TDCR_TDCF_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR &= ~MCAN_TDCR_TDCF(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TDCR_TDCF_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR ^= MCAN_TDCR_TDCF(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tdcr_reg_t hri_mcan_read_TDCR_TDCF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TDCR;
	tmp = (tmp & MCAN_TDCR_TDCF_Msk) >> MCAN_TDCR_TDCF_Pos;
	return tmp;
}

static inline void hri_mcan_set_TDCR_TDCO_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR |= MCAN_TDCR_TDCO(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tdcr_reg_t hri_mcan_get_TDCR_TDCO_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TDCR;
	tmp = (tmp & MCAN_TDCR_TDCO(mask)) >> MCAN_TDCR_TDCO_Pos;
	return tmp;
}

static inline void hri_mcan_write_TDCR_TDCO_bf(const void *const hw, hri_mcan_tdcr_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TDCR;
	tmp &= ~MCAN_TDCR_TDCO_Msk;
	tmp |= MCAN_TDCR_TDCO(data);
	((Mcan *)hw)->MCAN_TDCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TDCR_TDCO_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR &= ~MCAN_TDCR_TDCO(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TDCR_TDCO_bf(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR ^= MCAN_TDCR_TDCO(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tdcr_reg_t hri_mcan_read_TDCR_TDCO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TDCR;
	tmp = (tmp & MCAN_TDCR_TDCO_Msk) >> MCAN_TDCR_TDCO_Pos;
	return tmp;
}

static inline void hri_mcan_set_TDCR_reg(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tdcr_reg_t hri_mcan_get_TDCR_reg(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TDCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TDCR_reg(const void *const hw, hri_mcan_tdcr_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TDCR_reg(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TDCR_reg(const void *const hw, hri_mcan_tdcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TDCR ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_tdcr_reg_t hri_mcan_read_TDCR_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TDCR;
}

static inline void hri_mcan_set_IR_RF0N_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF0N;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF0N_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF0N) >> MCAN_IR_RF0N_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF0N_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF0N;
	tmp |= value << MCAN_IR_RF0N_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF0N_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF0N;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF0N_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF0N;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_RF0W_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF0W;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF0W_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF0W) >> MCAN_IR_RF0W_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF0W_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF0W;
	tmp |= value << MCAN_IR_RF0W_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF0W_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF0W;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF0W_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF0W;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_RF0F_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF0F;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF0F_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF0F) >> MCAN_IR_RF0F_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF0F_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF0F;
	tmp |= value << MCAN_IR_RF0F_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF0F_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF0F;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF0F_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF0F;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_RF0L_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF0L;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF0L_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF0L) >> MCAN_IR_RF0L_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF0L_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF0L;
	tmp |= value << MCAN_IR_RF0L_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF0L_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF0L;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF0L_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF0L;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_RF1N_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF1N;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF1N_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF1N) >> MCAN_IR_RF1N_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF1N_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF1N;
	tmp |= value << MCAN_IR_RF1N_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF1N_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF1N;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF1N_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF1N;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_RF1W_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF1W;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF1W_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF1W) >> MCAN_IR_RF1W_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF1W_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF1W;
	tmp |= value << MCAN_IR_RF1W_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF1W_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF1W;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF1W_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF1W;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_RF1F_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF1F;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF1F_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF1F) >> MCAN_IR_RF1F_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF1F_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF1F;
	tmp |= value << MCAN_IR_RF1F_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF1F_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF1F;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF1F_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF1F;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_RF1L_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_RF1L;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_RF1L_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_RF1L) >> MCAN_IR_RF1L_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_RF1L_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_RF1L;
	tmp |= value << MCAN_IR_RF1L_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_RF1L_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_RF1L;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_RF1L_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_RF1L;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_HPM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_HPM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_HPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_HPM) >> MCAN_IR_HPM_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_HPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_HPM;
	tmp |= value << MCAN_IR_HPM_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_HPM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_HPM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_HPM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_HPM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TC) >> MCAN_IR_TC_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TC;
	tmp |= value << MCAN_IR_TC_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TC_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TC;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TCF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TCF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TCF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TCF) >> MCAN_IR_TCF_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TCF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TCF;
	tmp |= value << MCAN_IR_TCF_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TCF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TCF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TCF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TCF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TFE) >> MCAN_IR_TFE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TFE;
	tmp |= value << MCAN_IR_TFE_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TEFN_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TEFN;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TEFN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TEFN) >> MCAN_IR_TEFN_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TEFN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TEFN;
	tmp |= value << MCAN_IR_TEFN_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TEFN_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TEFN;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TEFN_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TEFN;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TEFW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TEFW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TEFW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TEFW) >> MCAN_IR_TEFW_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TEFW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TEFW;
	tmp |= value << MCAN_IR_TEFW_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TEFW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TEFW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TEFW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TEFW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TEFF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TEFF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TEFF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TEFF) >> MCAN_IR_TEFF_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TEFF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TEFF;
	tmp |= value << MCAN_IR_TEFF_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TEFF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TEFF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TEFF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TEFF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TEFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TEFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TEFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TEFL) >> MCAN_IR_TEFL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TEFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TEFL;
	tmp |= value << MCAN_IR_TEFL_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TEFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TEFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TEFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TEFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TSW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TSW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TSW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TSW) >> MCAN_IR_TSW_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TSW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TSW;
	tmp |= value << MCAN_IR_TSW_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TSW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TSW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TSW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TSW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_MRAF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_MRAF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_MRAF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_MRAF) >> MCAN_IR_MRAF_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_MRAF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_MRAF;
	tmp |= value << MCAN_IR_MRAF_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_MRAF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_MRAF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_MRAF_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_MRAF;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_TOO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_TOO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_TOO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_TOO) >> MCAN_IR_TOO_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_TOO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_TOO;
	tmp |= value << MCAN_IR_TOO_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_TOO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_TOO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_TOO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_TOO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_DRX_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_DRX;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_DRX_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_DRX) >> MCAN_IR_DRX_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_DRX_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_DRX;
	tmp |= value << MCAN_IR_DRX_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_DRX_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_DRX;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_DRX_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_DRX;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_ELO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_ELO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_ELO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_ELO) >> MCAN_IR_ELO_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_ELO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_ELO;
	tmp |= value << MCAN_IR_ELO_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_ELO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_ELO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_ELO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_ELO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_EP_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_EP;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_EP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_EP) >> MCAN_IR_EP_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_EP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_EP;
	tmp |= value << MCAN_IR_EP_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_EP_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_EP;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_EP_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_EP;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_EW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_EW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_EW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_EW) >> MCAN_IR_EW_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_EW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_EW;
	tmp |= value << MCAN_IR_EW_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_EW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_EW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_EW_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_EW;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_BO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_BO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_BO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_BO) >> MCAN_IR_BO_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_BO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_BO;
	tmp |= value << MCAN_IR_BO_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_BO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_BO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_BO_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_BO;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_WDI_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_WDI;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_WDI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_WDI) >> MCAN_IR_WDI_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_WDI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_WDI;
	tmp |= value << MCAN_IR_WDI_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_WDI_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_WDI;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_WDI_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_WDI;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_PEA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_PEA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_PEA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_PEA) >> MCAN_IR_PEA_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_PEA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_PEA;
	tmp |= value << MCAN_IR_PEA_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_PEA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_PEA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_PEA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_PEA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_PED_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_PED;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_PED_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_PED) >> MCAN_IR_PED_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_PED_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_PED;
	tmp |= value << MCAN_IR_PED_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_PED_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_PED;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_PED_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_PED;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_ARA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= MCAN_IR_ARA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IR_ARA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp = (tmp & MCAN_IR_ARA) >> MCAN_IR_ARA_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IR_ARA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= ~MCAN_IR_ARA;
	tmp |= value << MCAN_IR_ARA_Pos;
	((Mcan *)hw)->MCAN_IR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_ARA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~MCAN_IR_ARA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_ARA_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= MCAN_IR_ARA;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IR_reg(const void *const hw, hri_mcan_ir_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ir_reg_t hri_mcan_get_IR_reg(const void *const hw, hri_mcan_ir_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IR;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_IR_reg(const void *const hw, hri_mcan_ir_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IR_reg(const void *const hw, hri_mcan_ir_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IR_reg(const void *const hw, hri_mcan_ir_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IR ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ir_reg_t hri_mcan_read_IR_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_IR;
}

static inline void hri_mcan_set_IE_RF0NE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF0NE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF0NE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF0NE) >> MCAN_IE_RF0NE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF0NE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF0NE;
	tmp |= value << MCAN_IE_RF0NE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF0NE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF0NE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF0NE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF0NE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_RF0WE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF0WE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF0WE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF0WE) >> MCAN_IE_RF0WE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF0WE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF0WE;
	tmp |= value << MCAN_IE_RF0WE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF0WE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF0WE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF0WE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF0WE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_RF0FE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF0FE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF0FE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF0FE) >> MCAN_IE_RF0FE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF0FE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF0FE;
	tmp |= value << MCAN_IE_RF0FE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF0FE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF0FE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF0FE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF0FE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_RF0LE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF0LE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF0LE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF0LE) >> MCAN_IE_RF0LE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF0LE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF0LE;
	tmp |= value << MCAN_IE_RF0LE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF0LE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF0LE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF0LE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF0LE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_RF1NE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF1NE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF1NE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF1NE) >> MCAN_IE_RF1NE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF1NE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF1NE;
	tmp |= value << MCAN_IE_RF1NE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF1NE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF1NE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF1NE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF1NE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_RF1WE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF1WE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF1WE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF1WE) >> MCAN_IE_RF1WE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF1WE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF1WE;
	tmp |= value << MCAN_IE_RF1WE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF1WE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF1WE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF1WE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF1WE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_RF1FE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF1FE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF1FE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF1FE) >> MCAN_IE_RF1FE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF1FE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF1FE;
	tmp |= value << MCAN_IE_RF1FE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF1FE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF1FE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF1FE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF1FE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_RF1LE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_RF1LE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_RF1LE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_RF1LE) >> MCAN_IE_RF1LE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_RF1LE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_RF1LE;
	tmp |= value << MCAN_IE_RF1LE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_RF1LE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_RF1LE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_RF1LE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_RF1LE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_HPME_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_HPME;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_HPME_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_HPME) >> MCAN_IE_HPME_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_HPME_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_HPME;
	tmp |= value << MCAN_IE_HPME_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_HPME_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_HPME;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_HPME_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_HPME;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TCE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TCE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TCE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TCE) >> MCAN_IE_TCE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TCE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TCE;
	tmp |= value << MCAN_IE_TCE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TCE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TCE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TCE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TCE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TCFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TCFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TCFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TCFE) >> MCAN_IE_TCFE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TCFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TCFE;
	tmp |= value << MCAN_IE_TCFE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TCFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TCFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TCFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TCFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TFEE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TFEE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TFEE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TFEE) >> MCAN_IE_TFEE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TFEE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TFEE;
	tmp |= value << MCAN_IE_TFEE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TFEE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TFEE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TFEE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TFEE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TEFNE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TEFNE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TEFNE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TEFNE) >> MCAN_IE_TEFNE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TEFNE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TEFNE;
	tmp |= value << MCAN_IE_TEFNE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TEFNE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TEFNE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TEFNE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TEFNE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TEFWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TEFWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TEFWE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TEFWE) >> MCAN_IE_TEFWE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TEFWE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TEFWE;
	tmp |= value << MCAN_IE_TEFWE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TEFWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TEFWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TEFWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TEFWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TEFFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TEFFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TEFFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TEFFE) >> MCAN_IE_TEFFE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TEFFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TEFFE;
	tmp |= value << MCAN_IE_TEFFE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TEFFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TEFFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TEFFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TEFFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TEFLE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TEFLE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TEFLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TEFLE) >> MCAN_IE_TEFLE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TEFLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TEFLE;
	tmp |= value << MCAN_IE_TEFLE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TEFLE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TEFLE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TEFLE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TEFLE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TSWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TSWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TSWE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TSWE) >> MCAN_IE_TSWE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TSWE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TSWE;
	tmp |= value << MCAN_IE_TSWE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TSWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TSWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TSWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TSWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_MRAFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_MRAFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_MRAFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_MRAFE) >> MCAN_IE_MRAFE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_MRAFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_MRAFE;
	tmp |= value << MCAN_IE_MRAFE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_MRAFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_MRAFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_MRAFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_MRAFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_TOOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_TOOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_TOOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_TOOE) >> MCAN_IE_TOOE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_TOOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_TOOE;
	tmp |= value << MCAN_IE_TOOE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_TOOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_TOOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_TOOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_TOOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_DRXE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_DRXE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_DRXE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_DRXE) >> MCAN_IE_DRXE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_DRXE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_DRXE;
	tmp |= value << MCAN_IE_DRXE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_DRXE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_DRXE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_DRXE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_DRXE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_ELOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_ELOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_ELOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_ELOE) >> MCAN_IE_ELOE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_ELOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_ELOE;
	tmp |= value << MCAN_IE_ELOE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_ELOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_ELOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_ELOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_ELOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_EPE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_EPE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_EPE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_EPE) >> MCAN_IE_EPE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_EPE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_EPE;
	tmp |= value << MCAN_IE_EPE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_EPE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_EPE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_EPE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_EPE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_EWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_EWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_EWE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_EWE) >> MCAN_IE_EWE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_EWE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_EWE;
	tmp |= value << MCAN_IE_EWE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_EWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_EWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_EWE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_EWE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_BOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_BOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_BOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_BOE) >> MCAN_IE_BOE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_BOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_BOE;
	tmp |= value << MCAN_IE_BOE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_BOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_BOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_BOE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_BOE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_WDIE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_WDIE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_WDIE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_WDIE) >> MCAN_IE_WDIE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_WDIE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_WDIE;
	tmp |= value << MCAN_IE_WDIE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_WDIE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_WDIE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_WDIE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_WDIE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_PEAE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_PEAE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_PEAE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_PEAE) >> MCAN_IE_PEAE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_PEAE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_PEAE;
	tmp |= value << MCAN_IE_PEAE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_PEAE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_PEAE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_PEAE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_PEAE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_PEDE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_PEDE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_PEDE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_PEDE) >> MCAN_IE_PEDE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_PEDE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_PEDE;
	tmp |= value << MCAN_IE_PEDE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_PEDE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_PEDE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_PEDE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_PEDE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_ARAE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= MCAN_IE_ARAE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_IE_ARAE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp = (tmp & MCAN_IE_ARAE) >> MCAN_IE_ARAE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_IE_ARAE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= ~MCAN_IE_ARAE;
	tmp |= value << MCAN_IE_ARAE_Pos;
	((Mcan *)hw)->MCAN_IE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_ARAE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~MCAN_IE_ARAE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_ARAE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= MCAN_IE_ARAE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_IE_reg(const void *const hw, hri_mcan_ie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ie_reg_t hri_mcan_get_IE_reg(const void *const hw, hri_mcan_ie_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_IE;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_IE_reg(const void *const hw, hri_mcan_ie_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_IE_reg(const void *const hw, hri_mcan_ie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_IE_reg(const void *const hw, hri_mcan_ie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_IE ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ie_reg_t hri_mcan_read_IE_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_IE;
}

static inline void hri_mcan_set_ILS_RF0NL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF0NL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF0NL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF0NL) >> MCAN_ILS_RF0NL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF0NL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF0NL;
	tmp |= value << MCAN_ILS_RF0NL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF0NL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF0NL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF0NL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF0NL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_RF0WL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF0WL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF0WL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF0WL) >> MCAN_ILS_RF0WL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF0WL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF0WL;
	tmp |= value << MCAN_ILS_RF0WL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF0WL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF0WL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF0WL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF0WL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_RF0FL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF0FL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF0FL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF0FL) >> MCAN_ILS_RF0FL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF0FL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF0FL;
	tmp |= value << MCAN_ILS_RF0FL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF0FL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF0FL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF0FL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF0FL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_RF0LL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF0LL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF0LL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF0LL) >> MCAN_ILS_RF0LL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF0LL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF0LL;
	tmp |= value << MCAN_ILS_RF0LL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF0LL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF0LL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF0LL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF0LL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_RF1NL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF1NL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF1NL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF1NL) >> MCAN_ILS_RF1NL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF1NL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF1NL;
	tmp |= value << MCAN_ILS_RF1NL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF1NL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF1NL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF1NL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF1NL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_RF1WL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF1WL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF1WL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF1WL) >> MCAN_ILS_RF1WL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF1WL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF1WL;
	tmp |= value << MCAN_ILS_RF1WL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF1WL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF1WL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF1WL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF1WL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_RF1FL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF1FL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF1FL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF1FL) >> MCAN_ILS_RF1FL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF1FL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF1FL;
	tmp |= value << MCAN_ILS_RF1FL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF1FL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF1FL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF1FL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF1FL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_RF1LL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_RF1LL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_RF1LL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_RF1LL) >> MCAN_ILS_RF1LL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_RF1LL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_RF1LL;
	tmp |= value << MCAN_ILS_RF1LL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_RF1LL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_RF1LL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_RF1LL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_RF1LL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_HPML_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_HPML;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_HPML_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_HPML) >> MCAN_ILS_HPML_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_HPML_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_HPML;
	tmp |= value << MCAN_ILS_HPML_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_HPML_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_HPML;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_HPML_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_HPML;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TCL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TCL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TCL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TCL) >> MCAN_ILS_TCL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TCL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TCL;
	tmp |= value << MCAN_ILS_TCL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TCL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TCL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TCL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TCL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TCFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TCFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TCFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TCFL) >> MCAN_ILS_TCFL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TCFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TCFL;
	tmp |= value << MCAN_ILS_TCFL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TCFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TCFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TCFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TCFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TFEL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TFEL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TFEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TFEL) >> MCAN_ILS_TFEL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TFEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TFEL;
	tmp |= value << MCAN_ILS_TFEL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TFEL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TFEL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TFEL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TFEL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TEFNL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TEFNL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TEFNL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TEFNL) >> MCAN_ILS_TEFNL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TEFNL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TEFNL;
	tmp |= value << MCAN_ILS_TEFNL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TEFNL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TEFNL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TEFNL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TEFNL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TEFWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TEFWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TEFWL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TEFWL) >> MCAN_ILS_TEFWL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TEFWL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TEFWL;
	tmp |= value << MCAN_ILS_TEFWL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TEFWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TEFWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TEFWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TEFWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TEFFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TEFFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TEFFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TEFFL) >> MCAN_ILS_TEFFL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TEFFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TEFFL;
	tmp |= value << MCAN_ILS_TEFFL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TEFFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TEFFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TEFFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TEFFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TEFLL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TEFLL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TEFLL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TEFLL) >> MCAN_ILS_TEFLL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TEFLL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TEFLL;
	tmp |= value << MCAN_ILS_TEFLL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TEFLL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TEFLL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TEFLL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TEFLL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TSWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TSWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TSWL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TSWL) >> MCAN_ILS_TSWL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TSWL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TSWL;
	tmp |= value << MCAN_ILS_TSWL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TSWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TSWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TSWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TSWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_MRAFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_MRAFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_MRAFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_MRAFL) >> MCAN_ILS_MRAFL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_MRAFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_MRAFL;
	tmp |= value << MCAN_ILS_MRAFL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_MRAFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_MRAFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_MRAFL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_MRAFL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_TOOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_TOOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_TOOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_TOOL) >> MCAN_ILS_TOOL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_TOOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_TOOL;
	tmp |= value << MCAN_ILS_TOOL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_TOOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_TOOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_TOOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_TOOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_DRXL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_DRXL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_DRXL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_DRXL) >> MCAN_ILS_DRXL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_DRXL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_DRXL;
	tmp |= value << MCAN_ILS_DRXL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_DRXL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_DRXL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_DRXL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_DRXL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_ELOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_ELOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_ELOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_ELOL) >> MCAN_ILS_ELOL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_ELOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_ELOL;
	tmp |= value << MCAN_ILS_ELOL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_ELOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_ELOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_ELOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_ELOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_EPL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_EPL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_EPL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_EPL) >> MCAN_ILS_EPL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_EPL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_EPL;
	tmp |= value << MCAN_ILS_EPL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_EPL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_EPL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_EPL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_EPL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_EWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_EWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_EWL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_EWL) >> MCAN_ILS_EWL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_EWL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_EWL;
	tmp |= value << MCAN_ILS_EWL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_EWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_EWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_EWL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_EWL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_BOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_BOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_BOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_BOL) >> MCAN_ILS_BOL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_BOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_BOL;
	tmp |= value << MCAN_ILS_BOL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_BOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_BOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_BOL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_BOL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_WDIL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_WDIL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_WDIL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_WDIL) >> MCAN_ILS_WDIL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_WDIL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_WDIL;
	tmp |= value << MCAN_ILS_WDIL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_WDIL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_WDIL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_WDIL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_WDIL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_PEAL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_PEAL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_PEAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_PEAL) >> MCAN_ILS_PEAL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_PEAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_PEAL;
	tmp |= value << MCAN_ILS_PEAL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_PEAL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_PEAL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_PEAL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_PEAL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_PEDL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_PEDL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_PEDL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_PEDL) >> MCAN_ILS_PEDL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_PEDL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_PEDL;
	tmp |= value << MCAN_ILS_PEDL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_PEDL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_PEDL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_PEDL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_PEDL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_ARAL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= MCAN_ILS_ARAL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILS_ARAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp = (tmp & MCAN_ILS_ARAL) >> MCAN_ILS_ARAL_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILS_ARAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= ~MCAN_ILS_ARAL;
	tmp |= value << MCAN_ILS_ARAL_Pos;
	((Mcan *)hw)->MCAN_ILS = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_ARAL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~MCAN_ILS_ARAL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_ARAL_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= MCAN_ILS_ARAL;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILS_reg(const void *const hw, hri_mcan_ils_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ils_reg_t hri_mcan_get_ILS_reg(const void *const hw, hri_mcan_ils_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILS;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_ILS_reg(const void *const hw, hri_mcan_ils_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILS_reg(const void *const hw, hri_mcan_ils_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILS_reg(const void *const hw, hri_mcan_ils_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILS ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ils_reg_t hri_mcan_read_ILS_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_ILS;
}

static inline void hri_mcan_set_ILE_EINT0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE |= MCAN_ILE_EINT0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILE_EINT0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILE;
	tmp = (tmp & MCAN_ILE_EINT0) >> MCAN_ILE_EINT0_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILE_EINT0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILE;
	tmp &= ~MCAN_ILE_EINT0;
	tmp |= value << MCAN_ILE_EINT0_Pos;
	((Mcan *)hw)->MCAN_ILE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILE_EINT0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE &= ~MCAN_ILE_EINT0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILE_EINT0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE ^= MCAN_ILE_EINT0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILE_EINT1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE |= MCAN_ILE_EINT1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_ILE_EINT1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILE;
	tmp = (tmp & MCAN_ILE_EINT1) >> MCAN_ILE_EINT1_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_ILE_EINT1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_ILE;
	tmp &= ~MCAN_ILE_EINT1;
	tmp |= value << MCAN_ILE_EINT1_Pos;
	((Mcan *)hw)->MCAN_ILE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILE_EINT1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE &= ~MCAN_ILE_EINT1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILE_EINT1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE ^= MCAN_ILE_EINT1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_ILE_reg(const void *const hw, hri_mcan_ile_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ile_reg_t hri_mcan_get_ILE_reg(const void *const hw, hri_mcan_ile_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_ILE;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_ILE_reg(const void *const hw, hri_mcan_ile_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_ILE_reg(const void *const hw, hri_mcan_ile_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_ILE_reg(const void *const hw, hri_mcan_ile_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_ILE ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ile_reg_t hri_mcan_read_ILE_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_ILE;
}

static inline void hri_mcan_set_GFC_RRFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC |= MCAN_GFC_RRFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_GFC_RRFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp = (tmp & MCAN_GFC_RRFE) >> MCAN_GFC_RRFE_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_GFC_RRFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp &= ~MCAN_GFC_RRFE;
	tmp |= value << MCAN_GFC_RRFE_Pos;
	((Mcan *)hw)->MCAN_GFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_GFC_RRFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC &= ~MCAN_GFC_RRFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_GFC_RRFE_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC ^= MCAN_GFC_RRFE;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_GFC_RRFS_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC |= MCAN_GFC_RRFS;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_GFC_RRFS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp = (tmp & MCAN_GFC_RRFS) >> MCAN_GFC_RRFS_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_GFC_RRFS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp &= ~MCAN_GFC_RRFS;
	tmp |= value << MCAN_GFC_RRFS_Pos;
	((Mcan *)hw)->MCAN_GFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_GFC_RRFS_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC &= ~MCAN_GFC_RRFS;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_GFC_RRFS_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC ^= MCAN_GFC_RRFS;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_GFC_ANFE_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC |= MCAN_GFC_ANFE(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_gfc_reg_t hri_mcan_get_GFC_ANFE_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp = (tmp & MCAN_GFC_ANFE(mask)) >> MCAN_GFC_ANFE_Pos;
	return tmp;
}

static inline void hri_mcan_write_GFC_ANFE_bf(const void *const hw, hri_mcan_gfc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp &= ~MCAN_GFC_ANFE_Msk;
	tmp |= MCAN_GFC_ANFE(data);
	((Mcan *)hw)->MCAN_GFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_GFC_ANFE_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC &= ~MCAN_GFC_ANFE(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_GFC_ANFE_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC ^= MCAN_GFC_ANFE(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_gfc_reg_t hri_mcan_read_GFC_ANFE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp = (tmp & MCAN_GFC_ANFE_Msk) >> MCAN_GFC_ANFE_Pos;
	return tmp;
}

static inline void hri_mcan_set_GFC_ANFS_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC |= MCAN_GFC_ANFS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_gfc_reg_t hri_mcan_get_GFC_ANFS_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp = (tmp & MCAN_GFC_ANFS(mask)) >> MCAN_GFC_ANFS_Pos;
	return tmp;
}

static inline void hri_mcan_write_GFC_ANFS_bf(const void *const hw, hri_mcan_gfc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp &= ~MCAN_GFC_ANFS_Msk;
	tmp |= MCAN_GFC_ANFS(data);
	((Mcan *)hw)->MCAN_GFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_GFC_ANFS_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC &= ~MCAN_GFC_ANFS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_GFC_ANFS_bf(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC ^= MCAN_GFC_ANFS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_gfc_reg_t hri_mcan_read_GFC_ANFS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp = (tmp & MCAN_GFC_ANFS_Msk) >> MCAN_GFC_ANFS_Pos;
	return tmp;
}

static inline void hri_mcan_set_GFC_reg(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_gfc_reg_t hri_mcan_get_GFC_reg(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_GFC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_GFC_reg(const void *const hw, hri_mcan_gfc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_GFC_reg(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_GFC_reg(const void *const hw, hri_mcan_gfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_GFC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_gfc_reg_t hri_mcan_read_GFC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_GFC;
}

static inline void hri_mcan_set_SIDFC_FLSSA_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC |= MCAN_SIDFC_FLSSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_sidfc_reg_t hri_mcan_get_SIDFC_FLSSA_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_SIDFC;
	tmp = (tmp & MCAN_SIDFC_FLSSA(mask)) >> MCAN_SIDFC_FLSSA_Pos;
	return tmp;
}

static inline void hri_mcan_write_SIDFC_FLSSA_bf(const void *const hw, hri_mcan_sidfc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_SIDFC;
	tmp &= ~MCAN_SIDFC_FLSSA_Msk;
	tmp |= MCAN_SIDFC_FLSSA(data);
	((Mcan *)hw)->MCAN_SIDFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_SIDFC_FLSSA_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC &= ~MCAN_SIDFC_FLSSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_SIDFC_FLSSA_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC ^= MCAN_SIDFC_FLSSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_sidfc_reg_t hri_mcan_read_SIDFC_FLSSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_SIDFC;
	tmp = (tmp & MCAN_SIDFC_FLSSA_Msk) >> MCAN_SIDFC_FLSSA_Pos;
	return tmp;
}

static inline void hri_mcan_set_SIDFC_LSS_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC |= MCAN_SIDFC_LSS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_sidfc_reg_t hri_mcan_get_SIDFC_LSS_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_SIDFC;
	tmp = (tmp & MCAN_SIDFC_LSS(mask)) >> MCAN_SIDFC_LSS_Pos;
	return tmp;
}

static inline void hri_mcan_write_SIDFC_LSS_bf(const void *const hw, hri_mcan_sidfc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_SIDFC;
	tmp &= ~MCAN_SIDFC_LSS_Msk;
	tmp |= MCAN_SIDFC_LSS(data);
	((Mcan *)hw)->MCAN_SIDFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_SIDFC_LSS_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC &= ~MCAN_SIDFC_LSS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_SIDFC_LSS_bf(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC ^= MCAN_SIDFC_LSS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_sidfc_reg_t hri_mcan_read_SIDFC_LSS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_SIDFC;
	tmp = (tmp & MCAN_SIDFC_LSS_Msk) >> MCAN_SIDFC_LSS_Pos;
	return tmp;
}

static inline void hri_mcan_set_SIDFC_reg(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_sidfc_reg_t hri_mcan_get_SIDFC_reg(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_SIDFC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_SIDFC_reg(const void *const hw, hri_mcan_sidfc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_SIDFC_reg(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_SIDFC_reg(const void *const hw, hri_mcan_sidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_SIDFC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_sidfc_reg_t hri_mcan_read_SIDFC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_SIDFC;
}

static inline void hri_mcan_set_XIDFC_FLESA_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC |= MCAN_XIDFC_FLESA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidfc_reg_t hri_mcan_get_XIDFC_FLESA_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDFC;
	tmp = (tmp & MCAN_XIDFC_FLESA(mask)) >> MCAN_XIDFC_FLESA_Pos;
	return tmp;
}

static inline void hri_mcan_write_XIDFC_FLESA_bf(const void *const hw, hri_mcan_xidfc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_XIDFC;
	tmp &= ~MCAN_XIDFC_FLESA_Msk;
	tmp |= MCAN_XIDFC_FLESA(data);
	((Mcan *)hw)->MCAN_XIDFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_XIDFC_FLESA_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC &= ~MCAN_XIDFC_FLESA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_XIDFC_FLESA_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC ^= MCAN_XIDFC_FLESA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidfc_reg_t hri_mcan_read_XIDFC_FLESA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDFC;
	tmp = (tmp & MCAN_XIDFC_FLESA_Msk) >> MCAN_XIDFC_FLESA_Pos;
	return tmp;
}

static inline void hri_mcan_set_XIDFC_LSE_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC |= MCAN_XIDFC_LSE(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidfc_reg_t hri_mcan_get_XIDFC_LSE_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDFC;
	tmp = (tmp & MCAN_XIDFC_LSE(mask)) >> MCAN_XIDFC_LSE_Pos;
	return tmp;
}

static inline void hri_mcan_write_XIDFC_LSE_bf(const void *const hw, hri_mcan_xidfc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_XIDFC;
	tmp &= ~MCAN_XIDFC_LSE_Msk;
	tmp |= MCAN_XIDFC_LSE(data);
	((Mcan *)hw)->MCAN_XIDFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_XIDFC_LSE_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC &= ~MCAN_XIDFC_LSE(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_XIDFC_LSE_bf(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC ^= MCAN_XIDFC_LSE(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidfc_reg_t hri_mcan_read_XIDFC_LSE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDFC;
	tmp = (tmp & MCAN_XIDFC_LSE_Msk) >> MCAN_XIDFC_LSE_Pos;
	return tmp;
}

static inline void hri_mcan_set_XIDFC_reg(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidfc_reg_t hri_mcan_get_XIDFC_reg(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDFC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_XIDFC_reg(const void *const hw, hri_mcan_xidfc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_XIDFC_reg(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_XIDFC_reg(const void *const hw, hri_mcan_xidfc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDFC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidfc_reg_t hri_mcan_read_XIDFC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_XIDFC;
}

static inline void hri_mcan_set_XIDAM_EIDM_bf(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDAM |= MCAN_XIDAM_EIDM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidam_reg_t hri_mcan_get_XIDAM_EIDM_bf(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDAM;
	tmp = (tmp & MCAN_XIDAM_EIDM(mask)) >> MCAN_XIDAM_EIDM_Pos;
	return tmp;
}

static inline void hri_mcan_write_XIDAM_EIDM_bf(const void *const hw, hri_mcan_xidam_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_XIDAM;
	tmp &= ~MCAN_XIDAM_EIDM_Msk;
	tmp |= MCAN_XIDAM_EIDM(data);
	((Mcan *)hw)->MCAN_XIDAM = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_XIDAM_EIDM_bf(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDAM &= ~MCAN_XIDAM_EIDM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_XIDAM_EIDM_bf(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDAM ^= MCAN_XIDAM_EIDM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidam_reg_t hri_mcan_read_XIDAM_EIDM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDAM;
	tmp = (tmp & MCAN_XIDAM_EIDM_Msk) >> MCAN_XIDAM_EIDM_Pos;
	return tmp;
}

static inline void hri_mcan_set_XIDAM_reg(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDAM |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidam_reg_t hri_mcan_get_XIDAM_reg(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_XIDAM;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_XIDAM_reg(const void *const hw, hri_mcan_xidam_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDAM = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_XIDAM_reg(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDAM &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_XIDAM_reg(const void *const hw, hri_mcan_xidam_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_XIDAM ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_xidam_reg_t hri_mcan_read_XIDAM_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_XIDAM;
}

static inline void hri_mcan_set_NDAT1_ND0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND0) >> MCAN_NDAT1_ND0_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND0;
	tmp |= value << MCAN_NDAT1_ND0_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND1) >> MCAN_NDAT1_ND1_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND1;
	tmp |= value << MCAN_NDAT1_ND1_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND2) >> MCAN_NDAT1_ND2_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND2;
	tmp |= value << MCAN_NDAT1_ND2_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND3) >> MCAN_NDAT1_ND3_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND3;
	tmp |= value << MCAN_NDAT1_ND3_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND4) >> MCAN_NDAT1_ND4_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND4;
	tmp |= value << MCAN_NDAT1_ND4_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND5) >> MCAN_NDAT1_ND5_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND5;
	tmp |= value << MCAN_NDAT1_ND5_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND6) >> MCAN_NDAT1_ND6_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND6;
	tmp |= value << MCAN_NDAT1_ND6_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND7) >> MCAN_NDAT1_ND7_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND7;
	tmp |= value << MCAN_NDAT1_ND7_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND8) >> MCAN_NDAT1_ND8_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND8;
	tmp |= value << MCAN_NDAT1_ND8_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND9) >> MCAN_NDAT1_ND9_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND9;
	tmp |= value << MCAN_NDAT1_ND9_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND10) >> MCAN_NDAT1_ND10_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND10;
	tmp |= value << MCAN_NDAT1_ND10_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND11) >> MCAN_NDAT1_ND11_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND11;
	tmp |= value << MCAN_NDAT1_ND11_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND12) >> MCAN_NDAT1_ND12_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND12;
	tmp |= value << MCAN_NDAT1_ND12_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND13) >> MCAN_NDAT1_ND13_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND13;
	tmp |= value << MCAN_NDAT1_ND13_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND14) >> MCAN_NDAT1_ND14_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND14;
	tmp |= value << MCAN_NDAT1_ND14_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND15) >> MCAN_NDAT1_ND15_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND15;
	tmp |= value << MCAN_NDAT1_ND15_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND16) >> MCAN_NDAT1_ND16_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND16;
	tmp |= value << MCAN_NDAT1_ND16_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND17) >> MCAN_NDAT1_ND17_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND17;
	tmp |= value << MCAN_NDAT1_ND17_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND18) >> MCAN_NDAT1_ND18_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND18;
	tmp |= value << MCAN_NDAT1_ND18_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND19) >> MCAN_NDAT1_ND19_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND19;
	tmp |= value << MCAN_NDAT1_ND19_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND20) >> MCAN_NDAT1_ND20_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND20;
	tmp |= value << MCAN_NDAT1_ND20_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND21) >> MCAN_NDAT1_ND21_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND21;
	tmp |= value << MCAN_NDAT1_ND21_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND22) >> MCAN_NDAT1_ND22_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND22;
	tmp |= value << MCAN_NDAT1_ND22_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND23) >> MCAN_NDAT1_ND23_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND23;
	tmp |= value << MCAN_NDAT1_ND23_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND24) >> MCAN_NDAT1_ND24_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND24;
	tmp |= value << MCAN_NDAT1_ND24_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND25) >> MCAN_NDAT1_ND25_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND25;
	tmp |= value << MCAN_NDAT1_ND25_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND26) >> MCAN_NDAT1_ND26_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND26;
	tmp |= value << MCAN_NDAT1_ND26_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND27) >> MCAN_NDAT1_ND27_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND27;
	tmp |= value << MCAN_NDAT1_ND27_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND28) >> MCAN_NDAT1_ND28_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND28;
	tmp |= value << MCAN_NDAT1_ND28_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND29) >> MCAN_NDAT1_ND29_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND29;
	tmp |= value << MCAN_NDAT1_ND29_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND30) >> MCAN_NDAT1_ND30_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND30;
	tmp |= value << MCAN_NDAT1_ND30_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_ND31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= MCAN_NDAT1_ND31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT1_ND31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp = (tmp & MCAN_NDAT1_ND31) >> MCAN_NDAT1_ND31_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT1_ND31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= ~MCAN_NDAT1_ND31;
	tmp |= value << MCAN_NDAT1_ND31_Pos;
	((Mcan *)hw)->MCAN_NDAT1 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_ND31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~MCAN_NDAT1_ND31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_ND31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= MCAN_NDAT1_ND31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT1_reg(const void *const hw, hri_mcan_ndat1_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ndat1_reg_t hri_mcan_get_NDAT1_reg(const void *const hw, hri_mcan_ndat1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT1;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_NDAT1_reg(const void *const hw, hri_mcan_ndat1_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT1_reg(const void *const hw, hri_mcan_ndat1_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT1_reg(const void *const hw, hri_mcan_ndat1_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT1 ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ndat1_reg_t hri_mcan_read_NDAT1_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_NDAT1;
}

static inline void hri_mcan_set_NDAT2_ND32_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND32;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND32_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND32) >> MCAN_NDAT2_ND32_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND32_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND32;
	tmp |= value << MCAN_NDAT2_ND32_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND32_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND32;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND32_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND32;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND33_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND33;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND33_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND33) >> MCAN_NDAT2_ND33_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND33_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND33;
	tmp |= value << MCAN_NDAT2_ND33_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND33_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND33;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND33_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND33;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND34_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND34;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND34_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND34) >> MCAN_NDAT2_ND34_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND34_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND34;
	tmp |= value << MCAN_NDAT2_ND34_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND34_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND34;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND34_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND34;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND35_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND35;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND35_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND35) >> MCAN_NDAT2_ND35_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND35_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND35;
	tmp |= value << MCAN_NDAT2_ND35_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND35_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND35;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND35_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND35;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND36_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND36;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND36_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND36) >> MCAN_NDAT2_ND36_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND36_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND36;
	tmp |= value << MCAN_NDAT2_ND36_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND36_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND36;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND36_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND36;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND37_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND37;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND37_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND37) >> MCAN_NDAT2_ND37_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND37_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND37;
	tmp |= value << MCAN_NDAT2_ND37_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND37_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND37;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND37_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND37;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND38_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND38;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND38_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND38) >> MCAN_NDAT2_ND38_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND38_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND38;
	tmp |= value << MCAN_NDAT2_ND38_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND38_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND38;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND38_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND38;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND39_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND39;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND39_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND39) >> MCAN_NDAT2_ND39_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND39_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND39;
	tmp |= value << MCAN_NDAT2_ND39_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND39_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND39;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND39_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND39;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND40_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND40;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND40_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND40) >> MCAN_NDAT2_ND40_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND40_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND40;
	tmp |= value << MCAN_NDAT2_ND40_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND40_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND40;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND40_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND40;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND41_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND41;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND41_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND41) >> MCAN_NDAT2_ND41_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND41_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND41;
	tmp |= value << MCAN_NDAT2_ND41_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND41_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND41;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND41_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND41;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND42_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND42;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND42_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND42) >> MCAN_NDAT2_ND42_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND42_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND42;
	tmp |= value << MCAN_NDAT2_ND42_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND42_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND42;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND42_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND42;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND43_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND43;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND43_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND43) >> MCAN_NDAT2_ND43_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND43_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND43;
	tmp |= value << MCAN_NDAT2_ND43_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND43_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND43;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND43_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND43;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND44_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND44;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND44_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND44) >> MCAN_NDAT2_ND44_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND44_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND44;
	tmp |= value << MCAN_NDAT2_ND44_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND44_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND44;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND44_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND44;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND45_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND45;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND45_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND45) >> MCAN_NDAT2_ND45_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND45_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND45;
	tmp |= value << MCAN_NDAT2_ND45_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND45_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND45;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND45_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND45;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND46_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND46;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND46_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND46) >> MCAN_NDAT2_ND46_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND46_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND46;
	tmp |= value << MCAN_NDAT2_ND46_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND46_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND46;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND46_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND46;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND47_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND47;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND47_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND47) >> MCAN_NDAT2_ND47_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND47_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND47;
	tmp |= value << MCAN_NDAT2_ND47_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND47_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND47;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND47_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND47;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND48_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND48;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND48_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND48) >> MCAN_NDAT2_ND48_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND48_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND48;
	tmp |= value << MCAN_NDAT2_ND48_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND48_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND48;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND48_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND48;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND49_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND49;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND49_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND49) >> MCAN_NDAT2_ND49_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND49_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND49;
	tmp |= value << MCAN_NDAT2_ND49_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND49_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND49;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND49_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND49;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND50_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND50;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND50_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND50) >> MCAN_NDAT2_ND50_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND50_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND50;
	tmp |= value << MCAN_NDAT2_ND50_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND50_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND50;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND50_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND50;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND51_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND51;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND51_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND51) >> MCAN_NDAT2_ND51_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND51_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND51;
	tmp |= value << MCAN_NDAT2_ND51_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND51_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND51;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND51_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND51;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND52_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND52;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND52_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND52) >> MCAN_NDAT2_ND52_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND52_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND52;
	tmp |= value << MCAN_NDAT2_ND52_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND52_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND52;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND52_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND52;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND53_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND53;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND53_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND53) >> MCAN_NDAT2_ND53_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND53_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND53;
	tmp |= value << MCAN_NDAT2_ND53_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND53_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND53;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND53_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND53;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND54_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND54;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND54_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND54) >> MCAN_NDAT2_ND54_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND54_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND54;
	tmp |= value << MCAN_NDAT2_ND54_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND54_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND54;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND54_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND54;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND55_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND55;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND55_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND55) >> MCAN_NDAT2_ND55_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND55_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND55;
	tmp |= value << MCAN_NDAT2_ND55_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND55_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND55;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND55_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND55;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND56_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND56;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND56_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND56) >> MCAN_NDAT2_ND56_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND56_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND56;
	tmp |= value << MCAN_NDAT2_ND56_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND56_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND56;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND56_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND56;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND57_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND57;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND57_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND57) >> MCAN_NDAT2_ND57_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND57_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND57;
	tmp |= value << MCAN_NDAT2_ND57_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND57_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND57;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND57_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND57;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND58_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND58;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND58_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND58) >> MCAN_NDAT2_ND58_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND58_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND58;
	tmp |= value << MCAN_NDAT2_ND58_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND58_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND58;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND58_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND58;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND59_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND59;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND59_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND59) >> MCAN_NDAT2_ND59_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND59_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND59;
	tmp |= value << MCAN_NDAT2_ND59_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND59_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND59;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND59_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND59;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND60_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND60;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND60_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND60) >> MCAN_NDAT2_ND60_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND60_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND60;
	tmp |= value << MCAN_NDAT2_ND60_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND60_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND60;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND60_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND60;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND61_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND61;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND61_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND61) >> MCAN_NDAT2_ND61_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND61_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND61;
	tmp |= value << MCAN_NDAT2_ND61_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND61_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND61;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND61_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND61;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND62_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND62;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND62_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND62) >> MCAN_NDAT2_ND62_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND62_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND62;
	tmp |= value << MCAN_NDAT2_ND62_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND62_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND62;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND62_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND62;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_ND63_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= MCAN_NDAT2_ND63;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_NDAT2_ND63_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp = (tmp & MCAN_NDAT2_ND63) >> MCAN_NDAT2_ND63_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_NDAT2_ND63_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= ~MCAN_NDAT2_ND63;
	tmp |= value << MCAN_NDAT2_ND63_Pos;
	((Mcan *)hw)->MCAN_NDAT2 = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_ND63_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~MCAN_NDAT2_ND63;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_ND63_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= MCAN_NDAT2_ND63;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_NDAT2_reg(const void *const hw, hri_mcan_ndat2_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ndat2_reg_t hri_mcan_get_NDAT2_reg(const void *const hw, hri_mcan_ndat2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_NDAT2;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_NDAT2_reg(const void *const hw, hri_mcan_ndat2_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_NDAT2_reg(const void *const hw, hri_mcan_ndat2_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_NDAT2_reg(const void *const hw, hri_mcan_ndat2_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_NDAT2 ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_ndat2_reg_t hri_mcan_read_NDAT2_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_NDAT2;
}

static inline void hri_mcan_set_RXF0C_F0OM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C |= MCAN_RXF0C_F0OM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_RXF0C_F0OM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp = (tmp & MCAN_RXF0C_F0OM) >> MCAN_RXF0C_F0OM_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_RXF0C_F0OM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp &= ~MCAN_RXF0C_F0OM;
	tmp |= value << MCAN_RXF0C_F0OM_Pos;
	((Mcan *)hw)->MCAN_RXF0C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF0C_F0OM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C &= ~MCAN_RXF0C_F0OM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF0C_F0OM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C ^= MCAN_RXF0C_F0OM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_RXF0C_F0SA_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C |= MCAN_RXF0C_F0SA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_get_RXF0C_F0SA_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp = (tmp & MCAN_RXF0C_F0SA(mask)) >> MCAN_RXF0C_F0SA_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF0C_F0SA_bf(const void *const hw, hri_mcan_rxf0c_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp &= ~MCAN_RXF0C_F0SA_Msk;
	tmp |= MCAN_RXF0C_F0SA(data);
	((Mcan *)hw)->MCAN_RXF0C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF0C_F0SA_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C &= ~MCAN_RXF0C_F0SA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF0C_F0SA_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C ^= MCAN_RXF0C_F0SA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_read_RXF0C_F0SA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp = (tmp & MCAN_RXF0C_F0SA_Msk) >> MCAN_RXF0C_F0SA_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF0C_F0S_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C |= MCAN_RXF0C_F0S(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_get_RXF0C_F0S_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp = (tmp & MCAN_RXF0C_F0S(mask)) >> MCAN_RXF0C_F0S_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF0C_F0S_bf(const void *const hw, hri_mcan_rxf0c_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp &= ~MCAN_RXF0C_F0S_Msk;
	tmp |= MCAN_RXF0C_F0S(data);
	((Mcan *)hw)->MCAN_RXF0C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF0C_F0S_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C &= ~MCAN_RXF0C_F0S(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF0C_F0S_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C ^= MCAN_RXF0C_F0S(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_read_RXF0C_F0S_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp = (tmp & MCAN_RXF0C_F0S_Msk) >> MCAN_RXF0C_F0S_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF0C_F0WM_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C |= MCAN_RXF0C_F0WM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_get_RXF0C_F0WM_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp = (tmp & MCAN_RXF0C_F0WM(mask)) >> MCAN_RXF0C_F0WM_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF0C_F0WM_bf(const void *const hw, hri_mcan_rxf0c_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp &= ~MCAN_RXF0C_F0WM_Msk;
	tmp |= MCAN_RXF0C_F0WM(data);
	((Mcan *)hw)->MCAN_RXF0C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF0C_F0WM_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C &= ~MCAN_RXF0C_F0WM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF0C_F0WM_bf(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C ^= MCAN_RXF0C_F0WM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_read_RXF0C_F0WM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp = (tmp & MCAN_RXF0C_F0WM_Msk) >> MCAN_RXF0C_F0WM_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF0C_reg(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_get_RXF0C_reg(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0C;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_RXF0C_reg(const void *const hw, hri_mcan_rxf0c_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF0C_reg(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF0C_reg(const void *const hw, hri_mcan_rxf0c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0C ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0c_reg_t hri_mcan_read_RXF0C_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXF0C;
}

static inline void hri_mcan_set_RXF0A_F0AI_bf(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0A |= MCAN_RXF0A_F0AI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0a_reg_t hri_mcan_get_RXF0A_F0AI_bf(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0A;
	tmp = (tmp & MCAN_RXF0A_F0AI(mask)) >> MCAN_RXF0A_F0AI_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF0A_F0AI_bf(const void *const hw, hri_mcan_rxf0a_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF0A;
	tmp &= ~MCAN_RXF0A_F0AI_Msk;
	tmp |= MCAN_RXF0A_F0AI(data);
	((Mcan *)hw)->MCAN_RXF0A = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF0A_F0AI_bf(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0A &= ~MCAN_RXF0A_F0AI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF0A_F0AI_bf(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0A ^= MCAN_RXF0A_F0AI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0a_reg_t hri_mcan_read_RXF0A_F0AI_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0A;
	tmp = (tmp & MCAN_RXF0A_F0AI_Msk) >> MCAN_RXF0A_F0AI_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF0A_reg(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0A |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0a_reg_t hri_mcan_get_RXF0A_reg(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF0A;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_RXF0A_reg(const void *const hw, hri_mcan_rxf0a_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0A = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF0A_reg(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0A &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF0A_reg(const void *const hw, hri_mcan_rxf0a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF0A ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf0a_reg_t hri_mcan_read_RXF0A_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXF0A;
}

static inline void hri_mcan_set_RXBC_RBSA_bf(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXBC |= MCAN_RXBC_RBSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxbc_reg_t hri_mcan_get_RXBC_RBSA_bf(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXBC;
	tmp = (tmp & MCAN_RXBC_RBSA(mask)) >> MCAN_RXBC_RBSA_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXBC_RBSA_bf(const void *const hw, hri_mcan_rxbc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXBC;
	tmp &= ~MCAN_RXBC_RBSA_Msk;
	tmp |= MCAN_RXBC_RBSA(data);
	((Mcan *)hw)->MCAN_RXBC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXBC_RBSA_bf(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXBC &= ~MCAN_RXBC_RBSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXBC_RBSA_bf(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXBC ^= MCAN_RXBC_RBSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxbc_reg_t hri_mcan_read_RXBC_RBSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXBC;
	tmp = (tmp & MCAN_RXBC_RBSA_Msk) >> MCAN_RXBC_RBSA_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXBC_reg(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXBC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxbc_reg_t hri_mcan_get_RXBC_reg(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXBC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_RXBC_reg(const void *const hw, hri_mcan_rxbc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXBC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXBC_reg(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXBC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXBC_reg(const void *const hw, hri_mcan_rxbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXBC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxbc_reg_t hri_mcan_read_RXBC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXBC;
}

static inline void hri_mcan_set_RXF1C_F1OM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C |= MCAN_RXF1C_F1OM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_RXF1C_F1OM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp = (tmp & MCAN_RXF1C_F1OM) >> MCAN_RXF1C_F1OM_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_RXF1C_F1OM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp &= ~MCAN_RXF1C_F1OM;
	tmp |= value << MCAN_RXF1C_F1OM_Pos;
	((Mcan *)hw)->MCAN_RXF1C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF1C_F1OM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C &= ~MCAN_RXF1C_F1OM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF1C_F1OM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C ^= MCAN_RXF1C_F1OM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_RXF1C_F1SA_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C |= MCAN_RXF1C_F1SA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_get_RXF1C_F1SA_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp = (tmp & MCAN_RXF1C_F1SA(mask)) >> MCAN_RXF1C_F1SA_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF1C_F1SA_bf(const void *const hw, hri_mcan_rxf1c_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp &= ~MCAN_RXF1C_F1SA_Msk;
	tmp |= MCAN_RXF1C_F1SA(data);
	((Mcan *)hw)->MCAN_RXF1C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF1C_F1SA_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C &= ~MCAN_RXF1C_F1SA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF1C_F1SA_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C ^= MCAN_RXF1C_F1SA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_read_RXF1C_F1SA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp = (tmp & MCAN_RXF1C_F1SA_Msk) >> MCAN_RXF1C_F1SA_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF1C_F1S_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C |= MCAN_RXF1C_F1S(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_get_RXF1C_F1S_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp = (tmp & MCAN_RXF1C_F1S(mask)) >> MCAN_RXF1C_F1S_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF1C_F1S_bf(const void *const hw, hri_mcan_rxf1c_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp &= ~MCAN_RXF1C_F1S_Msk;
	tmp |= MCAN_RXF1C_F1S(data);
	((Mcan *)hw)->MCAN_RXF1C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF1C_F1S_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C &= ~MCAN_RXF1C_F1S(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF1C_F1S_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C ^= MCAN_RXF1C_F1S(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_read_RXF1C_F1S_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp = (tmp & MCAN_RXF1C_F1S_Msk) >> MCAN_RXF1C_F1S_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF1C_F1WM_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C |= MCAN_RXF1C_F1WM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_get_RXF1C_F1WM_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp = (tmp & MCAN_RXF1C_F1WM(mask)) >> MCAN_RXF1C_F1WM_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF1C_F1WM_bf(const void *const hw, hri_mcan_rxf1c_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp &= ~MCAN_RXF1C_F1WM_Msk;
	tmp |= MCAN_RXF1C_F1WM(data);
	((Mcan *)hw)->MCAN_RXF1C = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF1C_F1WM_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C &= ~MCAN_RXF1C_F1WM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF1C_F1WM_bf(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C ^= MCAN_RXF1C_F1WM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_read_RXF1C_F1WM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp = (tmp & MCAN_RXF1C_F1WM_Msk) >> MCAN_RXF1C_F1WM_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF1C_reg(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_get_RXF1C_reg(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1C;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_RXF1C_reg(const void *const hw, hri_mcan_rxf1c_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF1C_reg(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF1C_reg(const void *const hw, hri_mcan_rxf1c_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1C ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1c_reg_t hri_mcan_read_RXF1C_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXF1C;
}

static inline void hri_mcan_set_RXF1A_F1AI_bf(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1A |= MCAN_RXF1A_F1AI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1a_reg_t hri_mcan_get_RXF1A_F1AI_bf(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1A;
	tmp = (tmp & MCAN_RXF1A_F1AI(mask)) >> MCAN_RXF1A_F1AI_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXF1A_F1AI_bf(const void *const hw, hri_mcan_rxf1a_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXF1A;
	tmp &= ~MCAN_RXF1A_F1AI_Msk;
	tmp |= MCAN_RXF1A_F1AI(data);
	((Mcan *)hw)->MCAN_RXF1A = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF1A_F1AI_bf(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1A &= ~MCAN_RXF1A_F1AI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF1A_F1AI_bf(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1A ^= MCAN_RXF1A_F1AI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1a_reg_t hri_mcan_read_RXF1A_F1AI_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1A;
	tmp = (tmp & MCAN_RXF1A_F1AI_Msk) >> MCAN_RXF1A_F1AI_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXF1A_reg(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1A |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1a_reg_t hri_mcan_get_RXF1A_reg(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXF1A;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_RXF1A_reg(const void *const hw, hri_mcan_rxf1a_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1A = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXF1A_reg(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1A &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXF1A_reg(const void *const hw, hri_mcan_rxf1a_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXF1A ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxf1a_reg_t hri_mcan_read_RXF1A_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXF1A;
}

static inline void hri_mcan_set_RXESC_F0DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC |= MCAN_RXESC_F0DS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_get_RXESC_F0DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp = (tmp & MCAN_RXESC_F0DS(mask)) >> MCAN_RXESC_F0DS_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXESC_F0DS_bf(const void *const hw, hri_mcan_rxesc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp &= ~MCAN_RXESC_F0DS_Msk;
	tmp |= MCAN_RXESC_F0DS(data);
	((Mcan *)hw)->MCAN_RXESC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXESC_F0DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC &= ~MCAN_RXESC_F0DS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXESC_F0DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC ^= MCAN_RXESC_F0DS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_read_RXESC_F0DS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp = (tmp & MCAN_RXESC_F0DS_Msk) >> MCAN_RXESC_F0DS_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXESC_F1DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC |= MCAN_RXESC_F1DS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_get_RXESC_F1DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp = (tmp & MCAN_RXESC_F1DS(mask)) >> MCAN_RXESC_F1DS_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXESC_F1DS_bf(const void *const hw, hri_mcan_rxesc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp &= ~MCAN_RXESC_F1DS_Msk;
	tmp |= MCAN_RXESC_F1DS(data);
	((Mcan *)hw)->MCAN_RXESC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXESC_F1DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC &= ~MCAN_RXESC_F1DS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXESC_F1DS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC ^= MCAN_RXESC_F1DS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_read_RXESC_F1DS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp = (tmp & MCAN_RXESC_F1DS_Msk) >> MCAN_RXESC_F1DS_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXESC_RBDS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC |= MCAN_RXESC_RBDS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_get_RXESC_RBDS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp = (tmp & MCAN_RXESC_RBDS(mask)) >> MCAN_RXESC_RBDS_Pos;
	return tmp;
}

static inline void hri_mcan_write_RXESC_RBDS_bf(const void *const hw, hri_mcan_rxesc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp &= ~MCAN_RXESC_RBDS_Msk;
	tmp |= MCAN_RXESC_RBDS(data);
	((Mcan *)hw)->MCAN_RXESC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXESC_RBDS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC &= ~MCAN_RXESC_RBDS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXESC_RBDS_bf(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC ^= MCAN_RXESC_RBDS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_read_RXESC_RBDS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp = (tmp & MCAN_RXESC_RBDS_Msk) >> MCAN_RXESC_RBDS_Pos;
	return tmp;
}

static inline void hri_mcan_set_RXESC_reg(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_get_RXESC_reg(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_RXESC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_RXESC_reg(const void *const hw, hri_mcan_rxesc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_RXESC_reg(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_RXESC_reg(const void *const hw, hri_mcan_rxesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_RXESC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_rxesc_reg_t hri_mcan_read_RXESC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_RXESC;
}

static inline void hri_mcan_set_TXBC_TFQM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC |= MCAN_TXBC_TFQM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBC_TFQM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp = (tmp & MCAN_TXBC_TFQM) >> MCAN_TXBC_TFQM_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBC_TFQM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp &= ~MCAN_TXBC_TFQM;
	tmp |= value << MCAN_TXBC_TFQM_Pos;
	((Mcan *)hw)->MCAN_TXBC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBC_TFQM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC &= ~MCAN_TXBC_TFQM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBC_TFQM_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC ^= MCAN_TXBC_TFQM;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBC_TBSA_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC |= MCAN_TXBC_TBSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_get_TXBC_TBSA_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp = (tmp & MCAN_TXBC_TBSA(mask)) >> MCAN_TXBC_TBSA_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXBC_TBSA_bf(const void *const hw, hri_mcan_txbc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp &= ~MCAN_TXBC_TBSA_Msk;
	tmp |= MCAN_TXBC_TBSA(data);
	((Mcan *)hw)->MCAN_TXBC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBC_TBSA_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC &= ~MCAN_TXBC_TBSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBC_TBSA_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC ^= MCAN_TXBC_TBSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_read_TXBC_TBSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp = (tmp & MCAN_TXBC_TBSA_Msk) >> MCAN_TXBC_TBSA_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXBC_NDTB_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC |= MCAN_TXBC_NDTB(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_get_TXBC_NDTB_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp = (tmp & MCAN_TXBC_NDTB(mask)) >> MCAN_TXBC_NDTB_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXBC_NDTB_bf(const void *const hw, hri_mcan_txbc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp &= ~MCAN_TXBC_NDTB_Msk;
	tmp |= MCAN_TXBC_NDTB(data);
	((Mcan *)hw)->MCAN_TXBC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBC_NDTB_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC &= ~MCAN_TXBC_NDTB(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBC_NDTB_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC ^= MCAN_TXBC_NDTB(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_read_TXBC_NDTB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp = (tmp & MCAN_TXBC_NDTB_Msk) >> MCAN_TXBC_NDTB_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXBC_TFQS_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC |= MCAN_TXBC_TFQS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_get_TXBC_TFQS_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp = (tmp & MCAN_TXBC_TFQS(mask)) >> MCAN_TXBC_TFQS_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXBC_TFQS_bf(const void *const hw, hri_mcan_txbc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp &= ~MCAN_TXBC_TFQS_Msk;
	tmp |= MCAN_TXBC_TFQS(data);
	((Mcan *)hw)->MCAN_TXBC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBC_TFQS_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC &= ~MCAN_TXBC_TFQS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBC_TFQS_bf(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC ^= MCAN_TXBC_TFQS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_read_TXBC_TFQS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp = (tmp & MCAN_TXBC_TFQS_Msk) >> MCAN_TXBC_TFQS_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXBC_reg(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_get_TXBC_reg(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXBC_reg(const void *const hw, hri_mcan_txbc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBC_reg(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBC_reg(const void *const hw, hri_mcan_txbc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbc_reg_t hri_mcan_read_TXBC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBC;
}

static inline void hri_mcan_set_TXESC_TBDS_bf(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXESC |= MCAN_TXESC_TBDS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txesc_reg_t hri_mcan_get_TXESC_TBDS_bf(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXESC;
	tmp = (tmp & MCAN_TXESC_TBDS(mask)) >> MCAN_TXESC_TBDS_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXESC_TBDS_bf(const void *const hw, hri_mcan_txesc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXESC;
	tmp &= ~MCAN_TXESC_TBDS_Msk;
	tmp |= MCAN_TXESC_TBDS(data);
	((Mcan *)hw)->MCAN_TXESC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXESC_TBDS_bf(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXESC &= ~MCAN_TXESC_TBDS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXESC_TBDS_bf(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXESC ^= MCAN_TXESC_TBDS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txesc_reg_t hri_mcan_read_TXESC_TBDS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXESC;
	tmp = (tmp & MCAN_TXESC_TBDS_Msk) >> MCAN_TXESC_TBDS_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXESC_reg(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXESC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txesc_reg_t hri_mcan_get_TXESC_reg(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXESC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXESC_reg(const void *const hw, hri_mcan_txesc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXESC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXESC_reg(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXESC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXESC_reg(const void *const hw, hri_mcan_txesc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXESC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txesc_reg_t hri_mcan_read_TXESC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXESC;
}

static inline void hri_mcan_set_TXBAR_AR0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR0) >> MCAN_TXBAR_AR0_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR0;
	tmp |= value << MCAN_TXBAR_AR0_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR1) >> MCAN_TXBAR_AR1_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR1;
	tmp |= value << MCAN_TXBAR_AR1_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR2) >> MCAN_TXBAR_AR2_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR2;
	tmp |= value << MCAN_TXBAR_AR2_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR3) >> MCAN_TXBAR_AR3_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR3;
	tmp |= value << MCAN_TXBAR_AR3_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR4) >> MCAN_TXBAR_AR4_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR4;
	tmp |= value << MCAN_TXBAR_AR4_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR5) >> MCAN_TXBAR_AR5_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR5;
	tmp |= value << MCAN_TXBAR_AR5_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR6) >> MCAN_TXBAR_AR6_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR6;
	tmp |= value << MCAN_TXBAR_AR6_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR7) >> MCAN_TXBAR_AR7_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR7;
	tmp |= value << MCAN_TXBAR_AR7_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR8) >> MCAN_TXBAR_AR8_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR8;
	tmp |= value << MCAN_TXBAR_AR8_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR9) >> MCAN_TXBAR_AR9_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR9;
	tmp |= value << MCAN_TXBAR_AR9_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR10) >> MCAN_TXBAR_AR10_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR10;
	tmp |= value << MCAN_TXBAR_AR10_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR11) >> MCAN_TXBAR_AR11_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR11;
	tmp |= value << MCAN_TXBAR_AR11_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR12) >> MCAN_TXBAR_AR12_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR12;
	tmp |= value << MCAN_TXBAR_AR12_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR13) >> MCAN_TXBAR_AR13_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR13;
	tmp |= value << MCAN_TXBAR_AR13_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR14) >> MCAN_TXBAR_AR14_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR14;
	tmp |= value << MCAN_TXBAR_AR14_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR15) >> MCAN_TXBAR_AR15_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR15;
	tmp |= value << MCAN_TXBAR_AR15_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR16) >> MCAN_TXBAR_AR16_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR16;
	tmp |= value << MCAN_TXBAR_AR16_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR17) >> MCAN_TXBAR_AR17_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR17;
	tmp |= value << MCAN_TXBAR_AR17_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR18) >> MCAN_TXBAR_AR18_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR18;
	tmp |= value << MCAN_TXBAR_AR18_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR19) >> MCAN_TXBAR_AR19_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR19;
	tmp |= value << MCAN_TXBAR_AR19_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR20) >> MCAN_TXBAR_AR20_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR20;
	tmp |= value << MCAN_TXBAR_AR20_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR21) >> MCAN_TXBAR_AR21_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR21;
	tmp |= value << MCAN_TXBAR_AR21_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR22) >> MCAN_TXBAR_AR22_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR22;
	tmp |= value << MCAN_TXBAR_AR22_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR23) >> MCAN_TXBAR_AR23_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR23;
	tmp |= value << MCAN_TXBAR_AR23_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR24) >> MCAN_TXBAR_AR24_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR24;
	tmp |= value << MCAN_TXBAR_AR24_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR25) >> MCAN_TXBAR_AR25_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR25;
	tmp |= value << MCAN_TXBAR_AR25_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR26) >> MCAN_TXBAR_AR26_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR26;
	tmp |= value << MCAN_TXBAR_AR26_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR27) >> MCAN_TXBAR_AR27_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR27;
	tmp |= value << MCAN_TXBAR_AR27_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR28) >> MCAN_TXBAR_AR28_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR28;
	tmp |= value << MCAN_TXBAR_AR28_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR29) >> MCAN_TXBAR_AR29_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR29;
	tmp |= value << MCAN_TXBAR_AR29_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR30) >> MCAN_TXBAR_AR30_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR30;
	tmp |= value << MCAN_TXBAR_AR30_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_AR31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= MCAN_TXBAR_AR31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBAR_AR31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp = (tmp & MCAN_TXBAR_AR31) >> MCAN_TXBAR_AR31_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBAR_AR31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= ~MCAN_TXBAR_AR31;
	tmp |= value << MCAN_TXBAR_AR31_Pos;
	((Mcan *)hw)->MCAN_TXBAR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_AR31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~MCAN_TXBAR_AR31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_AR31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= MCAN_TXBAR_AR31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBAR_reg(const void *const hw, hri_mcan_txbar_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbar_reg_t hri_mcan_get_TXBAR_reg(const void *const hw, hri_mcan_txbar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBAR;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXBAR_reg(const void *const hw, hri_mcan_txbar_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBAR_reg(const void *const hw, hri_mcan_txbar_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBAR_reg(const void *const hw, hri_mcan_txbar_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBAR ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbar_reg_t hri_mcan_read_TXBAR_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBAR;
}

static inline void hri_mcan_set_TXBCR_CR0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR0) >> MCAN_TXBCR_CR0_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR0;
	tmp |= value << MCAN_TXBCR_CR0_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR1) >> MCAN_TXBCR_CR1_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR1;
	tmp |= value << MCAN_TXBCR_CR1_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR2) >> MCAN_TXBCR_CR2_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR2;
	tmp |= value << MCAN_TXBCR_CR2_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR3) >> MCAN_TXBCR_CR3_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR3;
	tmp |= value << MCAN_TXBCR_CR3_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR4) >> MCAN_TXBCR_CR4_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR4;
	tmp |= value << MCAN_TXBCR_CR4_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR5) >> MCAN_TXBCR_CR5_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR5;
	tmp |= value << MCAN_TXBCR_CR5_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR6) >> MCAN_TXBCR_CR6_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR6;
	tmp |= value << MCAN_TXBCR_CR6_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR7) >> MCAN_TXBCR_CR7_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR7;
	tmp |= value << MCAN_TXBCR_CR7_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR8) >> MCAN_TXBCR_CR8_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR8;
	tmp |= value << MCAN_TXBCR_CR8_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR9) >> MCAN_TXBCR_CR9_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR9;
	tmp |= value << MCAN_TXBCR_CR9_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR10) >> MCAN_TXBCR_CR10_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR10;
	tmp |= value << MCAN_TXBCR_CR10_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR11) >> MCAN_TXBCR_CR11_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR11;
	tmp |= value << MCAN_TXBCR_CR11_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR12) >> MCAN_TXBCR_CR12_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR12;
	tmp |= value << MCAN_TXBCR_CR12_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR13) >> MCAN_TXBCR_CR13_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR13;
	tmp |= value << MCAN_TXBCR_CR13_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR14) >> MCAN_TXBCR_CR14_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR14;
	tmp |= value << MCAN_TXBCR_CR14_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR15) >> MCAN_TXBCR_CR15_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR15;
	tmp |= value << MCAN_TXBCR_CR15_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR16) >> MCAN_TXBCR_CR16_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR16;
	tmp |= value << MCAN_TXBCR_CR16_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR17) >> MCAN_TXBCR_CR17_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR17;
	tmp |= value << MCAN_TXBCR_CR17_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR18) >> MCAN_TXBCR_CR18_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR18;
	tmp |= value << MCAN_TXBCR_CR18_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR19) >> MCAN_TXBCR_CR19_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR19;
	tmp |= value << MCAN_TXBCR_CR19_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR20) >> MCAN_TXBCR_CR20_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR20;
	tmp |= value << MCAN_TXBCR_CR20_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR21) >> MCAN_TXBCR_CR21_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR21;
	tmp |= value << MCAN_TXBCR_CR21_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR22) >> MCAN_TXBCR_CR22_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR22;
	tmp |= value << MCAN_TXBCR_CR22_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR23) >> MCAN_TXBCR_CR23_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR23;
	tmp |= value << MCAN_TXBCR_CR23_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR24) >> MCAN_TXBCR_CR24_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR24;
	tmp |= value << MCAN_TXBCR_CR24_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR25) >> MCAN_TXBCR_CR25_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR25;
	tmp |= value << MCAN_TXBCR_CR25_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR26) >> MCAN_TXBCR_CR26_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR26;
	tmp |= value << MCAN_TXBCR_CR26_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR27) >> MCAN_TXBCR_CR27_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR27;
	tmp |= value << MCAN_TXBCR_CR27_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR28) >> MCAN_TXBCR_CR28_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR28;
	tmp |= value << MCAN_TXBCR_CR28_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR29) >> MCAN_TXBCR_CR29_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR29;
	tmp |= value << MCAN_TXBCR_CR29_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR30) >> MCAN_TXBCR_CR30_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR30;
	tmp |= value << MCAN_TXBCR_CR30_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_CR31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= MCAN_TXBCR_CR31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCR_CR31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp = (tmp & MCAN_TXBCR_CR31) >> MCAN_TXBCR_CR31_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCR_CR31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= ~MCAN_TXBCR_CR31;
	tmp |= value << MCAN_TXBCR_CR31_Pos;
	((Mcan *)hw)->MCAN_TXBCR = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_CR31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~MCAN_TXBCR_CR31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_CR31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= MCAN_TXBCR_CR31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCR_reg(const void *const hw, hri_mcan_txbcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbcr_reg_t hri_mcan_get_TXBCR_reg(const void *const hw, hri_mcan_txbcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCR;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXBCR_reg(const void *const hw, hri_mcan_txbcr_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCR_reg(const void *const hw, hri_mcan_txbcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCR_reg(const void *const hw, hri_mcan_txbcr_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCR ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbcr_reg_t hri_mcan_read_TXBCR_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBCR;
}

static inline void hri_mcan_set_TXBTIE_TIE0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE0) >> MCAN_TXBTIE_TIE0_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE0;
	tmp |= value << MCAN_TXBTIE_TIE0_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE1) >> MCAN_TXBTIE_TIE1_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE1;
	tmp |= value << MCAN_TXBTIE_TIE1_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE2) >> MCAN_TXBTIE_TIE2_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE2;
	tmp |= value << MCAN_TXBTIE_TIE2_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE3) >> MCAN_TXBTIE_TIE3_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE3;
	tmp |= value << MCAN_TXBTIE_TIE3_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE4) >> MCAN_TXBTIE_TIE4_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE4;
	tmp |= value << MCAN_TXBTIE_TIE4_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE5) >> MCAN_TXBTIE_TIE5_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE5;
	tmp |= value << MCAN_TXBTIE_TIE5_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE6) >> MCAN_TXBTIE_TIE6_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE6;
	tmp |= value << MCAN_TXBTIE_TIE6_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE7) >> MCAN_TXBTIE_TIE7_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE7;
	tmp |= value << MCAN_TXBTIE_TIE7_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE8) >> MCAN_TXBTIE_TIE8_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE8;
	tmp |= value << MCAN_TXBTIE_TIE8_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE9) >> MCAN_TXBTIE_TIE9_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE9;
	tmp |= value << MCAN_TXBTIE_TIE9_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE10) >> MCAN_TXBTIE_TIE10_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE10;
	tmp |= value << MCAN_TXBTIE_TIE10_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE11) >> MCAN_TXBTIE_TIE11_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE11;
	tmp |= value << MCAN_TXBTIE_TIE11_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE12) >> MCAN_TXBTIE_TIE12_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE12;
	tmp |= value << MCAN_TXBTIE_TIE12_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE13) >> MCAN_TXBTIE_TIE13_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE13;
	tmp |= value << MCAN_TXBTIE_TIE13_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE14) >> MCAN_TXBTIE_TIE14_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE14;
	tmp |= value << MCAN_TXBTIE_TIE14_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE15) >> MCAN_TXBTIE_TIE15_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE15;
	tmp |= value << MCAN_TXBTIE_TIE15_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE16) >> MCAN_TXBTIE_TIE16_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE16;
	tmp |= value << MCAN_TXBTIE_TIE16_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE17) >> MCAN_TXBTIE_TIE17_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE17;
	tmp |= value << MCAN_TXBTIE_TIE17_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE18) >> MCAN_TXBTIE_TIE18_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE18;
	tmp |= value << MCAN_TXBTIE_TIE18_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE19) >> MCAN_TXBTIE_TIE19_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE19;
	tmp |= value << MCAN_TXBTIE_TIE19_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE20) >> MCAN_TXBTIE_TIE20_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE20;
	tmp |= value << MCAN_TXBTIE_TIE20_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE21) >> MCAN_TXBTIE_TIE21_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE21;
	tmp |= value << MCAN_TXBTIE_TIE21_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE22) >> MCAN_TXBTIE_TIE22_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE22;
	tmp |= value << MCAN_TXBTIE_TIE22_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE23) >> MCAN_TXBTIE_TIE23_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE23;
	tmp |= value << MCAN_TXBTIE_TIE23_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE24) >> MCAN_TXBTIE_TIE24_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE24;
	tmp |= value << MCAN_TXBTIE_TIE24_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE25) >> MCAN_TXBTIE_TIE25_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE25;
	tmp |= value << MCAN_TXBTIE_TIE25_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE26) >> MCAN_TXBTIE_TIE26_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE26;
	tmp |= value << MCAN_TXBTIE_TIE26_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE27) >> MCAN_TXBTIE_TIE27_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE27;
	tmp |= value << MCAN_TXBTIE_TIE27_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE28) >> MCAN_TXBTIE_TIE28_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE28;
	tmp |= value << MCAN_TXBTIE_TIE28_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE29) >> MCAN_TXBTIE_TIE29_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE29;
	tmp |= value << MCAN_TXBTIE_TIE29_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE30) >> MCAN_TXBTIE_TIE30_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE30;
	tmp |= value << MCAN_TXBTIE_TIE30_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_TIE31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= MCAN_TXBTIE_TIE31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBTIE_TIE31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp = (tmp & MCAN_TXBTIE_TIE31) >> MCAN_TXBTIE_TIE31_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBTIE_TIE31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= ~MCAN_TXBTIE_TIE31;
	tmp |= value << MCAN_TXBTIE_TIE31_Pos;
	((Mcan *)hw)->MCAN_TXBTIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_TIE31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~MCAN_TXBTIE_TIE31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_TIE31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= MCAN_TXBTIE_TIE31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBTIE_reg(const void *const hw, hri_mcan_txbtie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbtie_reg_t hri_mcan_get_TXBTIE_reg(const void *const hw, hri_mcan_txbtie_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBTIE;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXBTIE_reg(const void *const hw, hri_mcan_txbtie_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBTIE_reg(const void *const hw, hri_mcan_txbtie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBTIE_reg(const void *const hw, hri_mcan_txbtie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBTIE ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbtie_reg_t hri_mcan_read_TXBTIE_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBTIE;
}

static inline void hri_mcan_set_TXBCIE_CFIE0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE0) >> MCAN_TXBCIE_CFIE0_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE0;
	tmp |= value << MCAN_TXBCIE_CFIE0_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE0_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE0;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE1) >> MCAN_TXBCIE_CFIE1_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE1;
	tmp |= value << MCAN_TXBCIE_CFIE1_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE1_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE1;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE2) >> MCAN_TXBCIE_CFIE2_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE2;
	tmp |= value << MCAN_TXBCIE_CFIE2_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE2_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE2;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE3) >> MCAN_TXBCIE_CFIE3_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE3;
	tmp |= value << MCAN_TXBCIE_CFIE3_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE3_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE3;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE4) >> MCAN_TXBCIE_CFIE4_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE4;
	tmp |= value << MCAN_TXBCIE_CFIE4_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE4_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE4;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE5) >> MCAN_TXBCIE_CFIE5_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE5;
	tmp |= value << MCAN_TXBCIE_CFIE5_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE5_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE5;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE6) >> MCAN_TXBCIE_CFIE6_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE6;
	tmp |= value << MCAN_TXBCIE_CFIE6_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE6_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE6;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE7) >> MCAN_TXBCIE_CFIE7_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE7;
	tmp |= value << MCAN_TXBCIE_CFIE7_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE7_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE7;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE8) >> MCAN_TXBCIE_CFIE8_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE8;
	tmp |= value << MCAN_TXBCIE_CFIE8_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE8_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE8;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE9) >> MCAN_TXBCIE_CFIE9_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE9;
	tmp |= value << MCAN_TXBCIE_CFIE9_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE9_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE9;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE10) >> MCAN_TXBCIE_CFIE10_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE10;
	tmp |= value << MCAN_TXBCIE_CFIE10_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE10_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE10;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE11) >> MCAN_TXBCIE_CFIE11_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE11;
	tmp |= value << MCAN_TXBCIE_CFIE11_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE11_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE11;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE12) >> MCAN_TXBCIE_CFIE12_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE12;
	tmp |= value << MCAN_TXBCIE_CFIE12_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE12_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE12;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE13) >> MCAN_TXBCIE_CFIE13_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE13;
	tmp |= value << MCAN_TXBCIE_CFIE13_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE13_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE13;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE14) >> MCAN_TXBCIE_CFIE14_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE14;
	tmp |= value << MCAN_TXBCIE_CFIE14_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE14_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE14;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE15) >> MCAN_TXBCIE_CFIE15_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE15;
	tmp |= value << MCAN_TXBCIE_CFIE15_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE15_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE15;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE16) >> MCAN_TXBCIE_CFIE16_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE16;
	tmp |= value << MCAN_TXBCIE_CFIE16_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE16_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE16;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE17) >> MCAN_TXBCIE_CFIE17_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE17;
	tmp |= value << MCAN_TXBCIE_CFIE17_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE17_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE17;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE18) >> MCAN_TXBCIE_CFIE18_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE18;
	tmp |= value << MCAN_TXBCIE_CFIE18_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE18_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE18;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE19) >> MCAN_TXBCIE_CFIE19_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE19;
	tmp |= value << MCAN_TXBCIE_CFIE19_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE19_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE19;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE20) >> MCAN_TXBCIE_CFIE20_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE20;
	tmp |= value << MCAN_TXBCIE_CFIE20_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE20_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE20;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE21) >> MCAN_TXBCIE_CFIE21_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE21;
	tmp |= value << MCAN_TXBCIE_CFIE21_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE21_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE21;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE22) >> MCAN_TXBCIE_CFIE22_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE22;
	tmp |= value << MCAN_TXBCIE_CFIE22_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE22_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE22;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE23) >> MCAN_TXBCIE_CFIE23_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE23;
	tmp |= value << MCAN_TXBCIE_CFIE23_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE23_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE23;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE24) >> MCAN_TXBCIE_CFIE24_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE24;
	tmp |= value << MCAN_TXBCIE_CFIE24_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE24_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE24;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE25) >> MCAN_TXBCIE_CFIE25_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE25;
	tmp |= value << MCAN_TXBCIE_CFIE25_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE25_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE25;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE26) >> MCAN_TXBCIE_CFIE26_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE26;
	tmp |= value << MCAN_TXBCIE_CFIE26_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE26_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE26;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE27) >> MCAN_TXBCIE_CFIE27_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE27;
	tmp |= value << MCAN_TXBCIE_CFIE27_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE27_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE27;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE28) >> MCAN_TXBCIE_CFIE28_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE28;
	tmp |= value << MCAN_TXBCIE_CFIE28_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE28_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE28;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE29) >> MCAN_TXBCIE_CFIE29_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE29;
	tmp |= value << MCAN_TXBCIE_CFIE29_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE29_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE29;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE30) >> MCAN_TXBCIE_CFIE30_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE30;
	tmp |= value << MCAN_TXBCIE_CFIE30_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE30_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE30;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_CFIE31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= MCAN_TXBCIE_CFIE31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_mcan_get_TXBCIE_CFIE31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp = (tmp & MCAN_TXBCIE_CFIE31) >> MCAN_TXBCIE_CFIE31_Pos;
	return (bool)tmp;
}

static inline void hri_mcan_write_TXBCIE_CFIE31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= ~MCAN_TXBCIE_CFIE31;
	tmp |= value << MCAN_TXBCIE_CFIE31_Pos;
	((Mcan *)hw)->MCAN_TXBCIE = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_CFIE31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~MCAN_TXBCIE_CFIE31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_CFIE31_bit(const void *const hw)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= MCAN_TXBCIE_CFIE31;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_set_TXBCIE_reg(const void *const hw, hri_mcan_txbcie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbcie_reg_t hri_mcan_get_TXBCIE_reg(const void *const hw, hri_mcan_txbcie_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXBCIE;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXBCIE_reg(const void *const hw, hri_mcan_txbcie_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXBCIE_reg(const void *const hw, hri_mcan_txbcie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXBCIE_reg(const void *const hw, hri_mcan_txbcie_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXBCIE ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txbcie_reg_t hri_mcan_read_TXBCIE_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXBCIE;
}

static inline void hri_mcan_set_TXEFC_EFSA_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC |= MCAN_TXEFC_EFSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_get_TXEFC_EFSA_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp = (tmp & MCAN_TXEFC_EFSA(mask)) >> MCAN_TXEFC_EFSA_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXEFC_EFSA_bf(const void *const hw, hri_mcan_txefc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp &= ~MCAN_TXEFC_EFSA_Msk;
	tmp |= MCAN_TXEFC_EFSA(data);
	((Mcan *)hw)->MCAN_TXEFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXEFC_EFSA_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC &= ~MCAN_TXEFC_EFSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXEFC_EFSA_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC ^= MCAN_TXEFC_EFSA(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_read_TXEFC_EFSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp = (tmp & MCAN_TXEFC_EFSA_Msk) >> MCAN_TXEFC_EFSA_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXEFC_EFS_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC |= MCAN_TXEFC_EFS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_get_TXEFC_EFS_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp = (tmp & MCAN_TXEFC_EFS(mask)) >> MCAN_TXEFC_EFS_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXEFC_EFS_bf(const void *const hw, hri_mcan_txefc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp &= ~MCAN_TXEFC_EFS_Msk;
	tmp |= MCAN_TXEFC_EFS(data);
	((Mcan *)hw)->MCAN_TXEFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXEFC_EFS_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC &= ~MCAN_TXEFC_EFS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXEFC_EFS_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC ^= MCAN_TXEFC_EFS(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_read_TXEFC_EFS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp = (tmp & MCAN_TXEFC_EFS_Msk) >> MCAN_TXEFC_EFS_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXEFC_EFWM_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC |= MCAN_TXEFC_EFWM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_get_TXEFC_EFWM_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp = (tmp & MCAN_TXEFC_EFWM(mask)) >> MCAN_TXEFC_EFWM_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXEFC_EFWM_bf(const void *const hw, hri_mcan_txefc_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp &= ~MCAN_TXEFC_EFWM_Msk;
	tmp |= MCAN_TXEFC_EFWM(data);
	((Mcan *)hw)->MCAN_TXEFC = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXEFC_EFWM_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC &= ~MCAN_TXEFC_EFWM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXEFC_EFWM_bf(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC ^= MCAN_TXEFC_EFWM(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_read_TXEFC_EFWM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp = (tmp & MCAN_TXEFC_EFWM_Msk) >> MCAN_TXEFC_EFWM_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXEFC_reg(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_get_TXEFC_reg(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFC;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXEFC_reg(const void *const hw, hri_mcan_txefc_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXEFC_reg(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXEFC_reg(const void *const hw, hri_mcan_txefc_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFC ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefc_reg_t hri_mcan_read_TXEFC_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXEFC;
}

static inline void hri_mcan_set_TXEFA_EFAI_bf(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFA |= MCAN_TXEFA_EFAI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefa_reg_t hri_mcan_get_TXEFA_EFAI_bf(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFA;
	tmp = (tmp & MCAN_TXEFA_EFAI(mask)) >> MCAN_TXEFA_EFAI_Pos;
	return tmp;
}

static inline void hri_mcan_write_TXEFA_EFAI_bf(const void *const hw, hri_mcan_txefa_reg_t data)
{
	uint32_t tmp;
	MCAN_CRITICAL_SECTION_ENTER();
	tmp = ((Mcan *)hw)->MCAN_TXEFA;
	tmp &= ~MCAN_TXEFA_EFAI_Msk;
	tmp |= MCAN_TXEFA_EFAI(data);
	((Mcan *)hw)->MCAN_TXEFA = tmp;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXEFA_EFAI_bf(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFA &= ~MCAN_TXEFA_EFAI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXEFA_EFAI_bf(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFA ^= MCAN_TXEFA_EFAI(mask);
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefa_reg_t hri_mcan_read_TXEFA_EFAI_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFA;
	tmp = (tmp & MCAN_TXEFA_EFAI_Msk) >> MCAN_TXEFA_EFAI_Pos;
	return tmp;
}

static inline void hri_mcan_set_TXEFA_reg(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFA |= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefa_reg_t hri_mcan_get_TXEFA_reg(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Mcan *)hw)->MCAN_TXEFA;
	tmp &= mask;
	return tmp;
}

static inline void hri_mcan_write_TXEFA_reg(const void *const hw, hri_mcan_txefa_reg_t data)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFA = data;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_clear_TXEFA_reg(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFA &= ~mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_mcan_toggle_TXEFA_reg(const void *const hw, hri_mcan_txefa_reg_t mask)
{
	MCAN_CRITICAL_SECTION_ENTER();
	((Mcan *)hw)->MCAN_TXEFA ^= mask;
	MCAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_mcan_txefa_reg_t hri_mcan_read_TXEFA_reg(const void *const hw)
{
	return ((Mcan *)hw)->MCAN_TXEFA;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_MCAN_E70B_H_INCLUDED */
#endif /* _SAME70_MCAN_COMPONENT_ */
