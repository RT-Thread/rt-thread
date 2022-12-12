/**
 * \file
 *
 * \brief SAM CAN
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifdef _SAMC21_CAN_COMPONENT_
#ifndef _HRI_CAN_C21_H_INCLUDED_
#define _HRI_CAN_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_CAN_CRITICAL_SECTIONS)
#define CAN_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define CAN_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define CAN_CRITICAL_SECTION_ENTER()
#define CAN_CRITICAL_SECTION_LEAVE()
#endif

typedef uint32_t hri_can_cccr_reg_t;
typedef uint32_t hri_can_crel_reg_t;
typedef uint32_t hri_can_dbtp_reg_t;
typedef uint32_t hri_can_ecr_reg_t;
typedef uint32_t hri_can_endn_reg_t;
typedef uint32_t hri_can_gfc_reg_t;
typedef uint32_t hri_can_hpms_reg_t;
typedef uint32_t hri_can_ie_reg_t;
typedef uint32_t hri_can_ile_reg_t;
typedef uint32_t hri_can_ils_reg_t;
typedef uint32_t hri_can_ir_reg_t;
typedef uint32_t hri_can_mrcfg_reg_t;
typedef uint32_t hri_can_nbtp_reg_t;
typedef uint32_t hri_can_ndat1_reg_t;
typedef uint32_t hri_can_ndat2_reg_t;
typedef uint32_t hri_can_psr_reg_t;
typedef uint32_t hri_can_rwd_reg_t;
typedef uint32_t hri_can_rxbc_reg_t;
typedef uint32_t hri_can_rxesc_reg_t;
typedef uint32_t hri_can_rxf0a_reg_t;
typedef uint32_t hri_can_rxf0c_reg_t;
typedef uint32_t hri_can_rxf0s_reg_t;
typedef uint32_t hri_can_rxf1a_reg_t;
typedef uint32_t hri_can_rxf1c_reg_t;
typedef uint32_t hri_can_rxf1s_reg_t;
typedef uint32_t hri_can_sidfc_reg_t;
typedef uint32_t hri_can_tdcr_reg_t;
typedef uint32_t hri_can_test_reg_t;
typedef uint32_t hri_can_tocc_reg_t;
typedef uint32_t hri_can_tocv_reg_t;
typedef uint32_t hri_can_tscc_reg_t;
typedef uint32_t hri_can_tscv_reg_t;
typedef uint32_t hri_can_txbar_reg_t;
typedef uint32_t hri_can_txbc_reg_t;
typedef uint32_t hri_can_txbcf_reg_t;
typedef uint32_t hri_can_txbcie_reg_t;
typedef uint32_t hri_can_txbcr_reg_t;
typedef uint32_t hri_can_txbrp_reg_t;
typedef uint32_t hri_can_txbtie_reg_t;
typedef uint32_t hri_can_txbto_reg_t;
typedef uint32_t hri_can_txefa_reg_t;
typedef uint32_t hri_can_txefc_reg_t;
typedef uint32_t hri_can_txefs_reg_t;
typedef uint32_t hri_can_txesc_reg_t;
typedef uint32_t hri_can_txfqs_reg_t;
typedef uint32_t hri_can_xidam_reg_t;
typedef uint32_t hri_can_xidfc_reg_t;

static inline hri_can_crel_reg_t hri_can_get_CREL_SUBSTEP_bf(const void *const hw, hri_can_crel_reg_t mask)
{
	return (((Can *)hw)->CREL.reg & CAN_CREL_SUBSTEP(mask)) >> CAN_CREL_SUBSTEP_Pos;
}

static inline hri_can_crel_reg_t hri_can_read_CREL_SUBSTEP_bf(const void *const hw)
{
	return (((Can *)hw)->CREL.reg & CAN_CREL_SUBSTEP_Msk) >> CAN_CREL_SUBSTEP_Pos;
}

static inline hri_can_crel_reg_t hri_can_get_CREL_STEP_bf(const void *const hw, hri_can_crel_reg_t mask)
{
	return (((Can *)hw)->CREL.reg & CAN_CREL_STEP(mask)) >> CAN_CREL_STEP_Pos;
}

static inline hri_can_crel_reg_t hri_can_read_CREL_STEP_bf(const void *const hw)
{
	return (((Can *)hw)->CREL.reg & CAN_CREL_STEP_Msk) >> CAN_CREL_STEP_Pos;
}

static inline hri_can_crel_reg_t hri_can_get_CREL_REL_bf(const void *const hw, hri_can_crel_reg_t mask)
{
	return (((Can *)hw)->CREL.reg & CAN_CREL_REL(mask)) >> CAN_CREL_REL_Pos;
}

static inline hri_can_crel_reg_t hri_can_read_CREL_REL_bf(const void *const hw)
{
	return (((Can *)hw)->CREL.reg & CAN_CREL_REL_Msk) >> CAN_CREL_REL_Pos;
}

static inline hri_can_crel_reg_t hri_can_get_CREL_reg(const void *const hw, hri_can_crel_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CREL.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_crel_reg_t hri_can_read_CREL_reg(const void *const hw)
{
	return ((Can *)hw)->CREL.reg;
}

static inline hri_can_endn_reg_t hri_can_get_ENDN_ETV_bf(const void *const hw, hri_can_endn_reg_t mask)
{
	return (((Can *)hw)->ENDN.reg & CAN_ENDN_ETV(mask)) >> CAN_ENDN_ETV_Pos;
}

static inline hri_can_endn_reg_t hri_can_read_ENDN_ETV_bf(const void *const hw)
{
	return (((Can *)hw)->ENDN.reg & CAN_ENDN_ETV_Msk) >> CAN_ENDN_ETV_Pos;
}

static inline hri_can_endn_reg_t hri_can_get_ENDN_reg(const void *const hw, hri_can_endn_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ENDN.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_endn_reg_t hri_can_read_ENDN_reg(const void *const hw)
{
	return ((Can *)hw)->ENDN.reg;
}

static inline hri_can_tscv_reg_t hri_can_get_TSCV_TSC_bf(const void *const hw, hri_can_tscv_reg_t mask)
{
	return (((Can *)hw)->TSCV.reg & CAN_TSCV_TSC(mask)) >> CAN_TSCV_TSC_Pos;
}

static inline hri_can_tscv_reg_t hri_can_read_TSCV_TSC_bf(const void *const hw)
{
	return (((Can *)hw)->TSCV.reg & CAN_TSCV_TSC_Msk) >> CAN_TSCV_TSC_Pos;
}

static inline hri_can_tscv_reg_t hri_can_get_TSCV_reg(const void *const hw, hri_can_tscv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TSCV.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_tscv_reg_t hri_can_read_TSCV_reg(const void *const hw)
{
	return ((Can *)hw)->TSCV.reg;
}

static inline bool hri_can_get_ECR_RP_bit(const void *const hw)
{
	return (((Can *)hw)->ECR.reg & CAN_ECR_RP) >> CAN_ECR_RP_Pos;
}

static inline hri_can_ecr_reg_t hri_can_get_ECR_TEC_bf(const void *const hw, hri_can_ecr_reg_t mask)
{
	return (((Can *)hw)->ECR.reg & CAN_ECR_TEC(mask)) >> CAN_ECR_TEC_Pos;
}

static inline hri_can_ecr_reg_t hri_can_read_ECR_TEC_bf(const void *const hw)
{
	return (((Can *)hw)->ECR.reg & CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos;
}

static inline hri_can_ecr_reg_t hri_can_get_ECR_REC_bf(const void *const hw, hri_can_ecr_reg_t mask)
{
	return (((Can *)hw)->ECR.reg & CAN_ECR_REC(mask)) >> CAN_ECR_REC_Pos;
}

static inline hri_can_ecr_reg_t hri_can_read_ECR_REC_bf(const void *const hw)
{
	return (((Can *)hw)->ECR.reg & CAN_ECR_REC_Msk) >> CAN_ECR_REC_Pos;
}

static inline hri_can_ecr_reg_t hri_can_get_ECR_CEL_bf(const void *const hw, hri_can_ecr_reg_t mask)
{
	return (((Can *)hw)->ECR.reg & CAN_ECR_CEL(mask)) >> CAN_ECR_CEL_Pos;
}

static inline hri_can_ecr_reg_t hri_can_read_ECR_CEL_bf(const void *const hw)
{
	return (((Can *)hw)->ECR.reg & CAN_ECR_CEL_Msk) >> CAN_ECR_CEL_Pos;
}

static inline hri_can_ecr_reg_t hri_can_get_ECR_reg(const void *const hw, hri_can_ecr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ECR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_ecr_reg_t hri_can_read_ECR_reg(const void *const hw)
{
	return ((Can *)hw)->ECR.reg;
}

static inline bool hri_can_get_PSR_EP_bit(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_EP) >> CAN_PSR_EP_Pos;
}

static inline bool hri_can_get_PSR_EW_bit(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_EW) >> CAN_PSR_EW_Pos;
}

static inline bool hri_can_get_PSR_BO_bit(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_BO) >> CAN_PSR_BO_Pos;
}

static inline bool hri_can_get_PSR_RESI_bit(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_RESI) >> CAN_PSR_RESI_Pos;
}

static inline bool hri_can_get_PSR_RBRS_bit(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_RBRS) >> CAN_PSR_RBRS_Pos;
}

static inline bool hri_can_get_PSR_RFDF_bit(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_RFDF) >> CAN_PSR_RFDF_Pos;
}

static inline bool hri_can_get_PSR_PXE_bit(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_PXE) >> CAN_PSR_PXE_Pos;
}

static inline hri_can_psr_reg_t hri_can_get_PSR_LEC_bf(const void *const hw, hri_can_psr_reg_t mask)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_LEC(mask)) >> CAN_PSR_LEC_Pos;
}

static inline hri_can_psr_reg_t hri_can_read_PSR_LEC_bf(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_LEC_Msk) >> CAN_PSR_LEC_Pos;
}

static inline hri_can_psr_reg_t hri_can_get_PSR_ACT_bf(const void *const hw, hri_can_psr_reg_t mask)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_ACT(mask)) >> CAN_PSR_ACT_Pos;
}

static inline hri_can_psr_reg_t hri_can_read_PSR_ACT_bf(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_ACT_Msk) >> CAN_PSR_ACT_Pos;
}

static inline hri_can_psr_reg_t hri_can_get_PSR_DLEC_bf(const void *const hw, hri_can_psr_reg_t mask)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_DLEC(mask)) >> CAN_PSR_DLEC_Pos;
}

static inline hri_can_psr_reg_t hri_can_read_PSR_DLEC_bf(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_DLEC_Msk) >> CAN_PSR_DLEC_Pos;
}

static inline hri_can_psr_reg_t hri_can_get_PSR_TDCV_bf(const void *const hw, hri_can_psr_reg_t mask)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_TDCV(mask)) >> CAN_PSR_TDCV_Pos;
}

static inline hri_can_psr_reg_t hri_can_read_PSR_TDCV_bf(const void *const hw)
{
	return (((Can *)hw)->PSR.reg & CAN_PSR_TDCV_Msk) >> CAN_PSR_TDCV_Pos;
}

static inline hri_can_psr_reg_t hri_can_get_PSR_reg(const void *const hw, hri_can_psr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->PSR.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_psr_reg_t hri_can_read_PSR_reg(const void *const hw)
{
	return ((Can *)hw)->PSR.reg;
}

static inline bool hri_can_get_HPMS_FLST_bit(const void *const hw)
{
	return (((Can *)hw)->HPMS.reg & CAN_HPMS_FLST) >> CAN_HPMS_FLST_Pos;
}

static inline hri_can_hpms_reg_t hri_can_get_HPMS_BIDX_bf(const void *const hw, hri_can_hpms_reg_t mask)
{
	return (((Can *)hw)->HPMS.reg & CAN_HPMS_BIDX(mask)) >> CAN_HPMS_BIDX_Pos;
}

static inline hri_can_hpms_reg_t hri_can_read_HPMS_BIDX_bf(const void *const hw)
{
	return (((Can *)hw)->HPMS.reg & CAN_HPMS_BIDX_Msk) >> CAN_HPMS_BIDX_Pos;
}

static inline hri_can_hpms_reg_t hri_can_get_HPMS_MSI_bf(const void *const hw, hri_can_hpms_reg_t mask)
{
	return (((Can *)hw)->HPMS.reg & CAN_HPMS_MSI(mask)) >> CAN_HPMS_MSI_Pos;
}

static inline hri_can_hpms_reg_t hri_can_read_HPMS_MSI_bf(const void *const hw)
{
	return (((Can *)hw)->HPMS.reg & CAN_HPMS_MSI_Msk) >> CAN_HPMS_MSI_Pos;
}

static inline hri_can_hpms_reg_t hri_can_get_HPMS_FIDX_bf(const void *const hw, hri_can_hpms_reg_t mask)
{
	return (((Can *)hw)->HPMS.reg & CAN_HPMS_FIDX(mask)) >> CAN_HPMS_FIDX_Pos;
}

static inline hri_can_hpms_reg_t hri_can_read_HPMS_FIDX_bf(const void *const hw)
{
	return (((Can *)hw)->HPMS.reg & CAN_HPMS_FIDX_Msk) >> CAN_HPMS_FIDX_Pos;
}

static inline hri_can_hpms_reg_t hri_can_get_HPMS_reg(const void *const hw, hri_can_hpms_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->HPMS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_hpms_reg_t hri_can_read_HPMS_reg(const void *const hw)
{
	return ((Can *)hw)->HPMS.reg;
}

static inline bool hri_can_get_RXF0S_F0F_bit(const void *const hw)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_F0F) >> CAN_RXF0S_F0F_Pos;
}

static inline bool hri_can_get_RXF0S_RF0L_bit(const void *const hw)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_RF0L) >> CAN_RXF0S_RF0L_Pos;
}

static inline hri_can_rxf0s_reg_t hri_can_get_RXF0S_F0FL_bf(const void *const hw, hri_can_rxf0s_reg_t mask)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_F0FL(mask)) >> CAN_RXF0S_F0FL_Pos;
}

static inline hri_can_rxf0s_reg_t hri_can_read_RXF0S_F0FL_bf(const void *const hw)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_F0FL_Msk) >> CAN_RXF0S_F0FL_Pos;
}

static inline hri_can_rxf0s_reg_t hri_can_get_RXF0S_F0GI_bf(const void *const hw, hri_can_rxf0s_reg_t mask)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_F0GI(mask)) >> CAN_RXF0S_F0GI_Pos;
}

static inline hri_can_rxf0s_reg_t hri_can_read_RXF0S_F0GI_bf(const void *const hw)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_F0GI_Msk) >> CAN_RXF0S_F0GI_Pos;
}

static inline hri_can_rxf0s_reg_t hri_can_get_RXF0S_F0PI_bf(const void *const hw, hri_can_rxf0s_reg_t mask)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_F0PI(mask)) >> CAN_RXF0S_F0PI_Pos;
}

static inline hri_can_rxf0s_reg_t hri_can_read_RXF0S_F0PI_bf(const void *const hw)
{
	return (((Can *)hw)->RXF0S.reg & CAN_RXF0S_F0PI_Msk) >> CAN_RXF0S_F0PI_Pos;
}

static inline hri_can_rxf0s_reg_t hri_can_get_RXF0S_reg(const void *const hw, hri_can_rxf0s_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0S.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_rxf0s_reg_t hri_can_read_RXF0S_reg(const void *const hw)
{
	return ((Can *)hw)->RXF0S.reg;
}

static inline bool hri_can_get_RXF1S_F1F_bit(const void *const hw)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_F1F) >> CAN_RXF1S_F1F_Pos;
}

static inline bool hri_can_get_RXF1S_RF1L_bit(const void *const hw)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_RF1L) >> CAN_RXF1S_RF1L_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_get_RXF1S_F1FL_bf(const void *const hw, hri_can_rxf1s_reg_t mask)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_F1FL(mask)) >> CAN_RXF1S_F1FL_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_read_RXF1S_F1FL_bf(const void *const hw)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_F1FL_Msk) >> CAN_RXF1S_F1FL_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_get_RXF1S_F1GI_bf(const void *const hw, hri_can_rxf1s_reg_t mask)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_F1GI(mask)) >> CAN_RXF1S_F1GI_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_read_RXF1S_F1GI_bf(const void *const hw)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_F1GI_Msk) >> CAN_RXF1S_F1GI_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_get_RXF1S_F1PI_bf(const void *const hw, hri_can_rxf1s_reg_t mask)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_F1PI(mask)) >> CAN_RXF1S_F1PI_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_read_RXF1S_F1PI_bf(const void *const hw)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_F1PI_Msk) >> CAN_RXF1S_F1PI_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_get_RXF1S_DMS_bf(const void *const hw, hri_can_rxf1s_reg_t mask)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_DMS(mask)) >> CAN_RXF1S_DMS_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_read_RXF1S_DMS_bf(const void *const hw)
{
	return (((Can *)hw)->RXF1S.reg & CAN_RXF1S_DMS_Msk) >> CAN_RXF1S_DMS_Pos;
}

static inline hri_can_rxf1s_reg_t hri_can_get_RXF1S_reg(const void *const hw, hri_can_rxf1s_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1S.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_rxf1s_reg_t hri_can_read_RXF1S_reg(const void *const hw)
{
	return ((Can *)hw)->RXF1S.reg;
}

static inline bool hri_can_get_TXFQS_TFQF_bit(const void *const hw)
{
	return (((Can *)hw)->TXFQS.reg & CAN_TXFQS_TFQF) >> CAN_TXFQS_TFQF_Pos;
}

static inline hri_can_txfqs_reg_t hri_can_get_TXFQS_TFFL_bf(const void *const hw, hri_can_txfqs_reg_t mask)
{
	return (((Can *)hw)->TXFQS.reg & CAN_TXFQS_TFFL(mask)) >> CAN_TXFQS_TFFL_Pos;
}

static inline hri_can_txfqs_reg_t hri_can_read_TXFQS_TFFL_bf(const void *const hw)
{
	return (((Can *)hw)->TXFQS.reg & CAN_TXFQS_TFFL_Msk) >> CAN_TXFQS_TFFL_Pos;
}

static inline hri_can_txfqs_reg_t hri_can_get_TXFQS_TFGI_bf(const void *const hw, hri_can_txfqs_reg_t mask)
{
	return (((Can *)hw)->TXFQS.reg & CAN_TXFQS_TFGI(mask)) >> CAN_TXFQS_TFGI_Pos;
}

static inline hri_can_txfqs_reg_t hri_can_read_TXFQS_TFGI_bf(const void *const hw)
{
	return (((Can *)hw)->TXFQS.reg & CAN_TXFQS_TFGI_Msk) >> CAN_TXFQS_TFGI_Pos;
}

static inline hri_can_txfqs_reg_t hri_can_get_TXFQS_TFQPI_bf(const void *const hw, hri_can_txfqs_reg_t mask)
{
	return (((Can *)hw)->TXFQS.reg & CAN_TXFQS_TFQPI(mask)) >> CAN_TXFQS_TFQPI_Pos;
}

static inline hri_can_txfqs_reg_t hri_can_read_TXFQS_TFQPI_bf(const void *const hw)
{
	return (((Can *)hw)->TXFQS.reg & CAN_TXFQS_TFQPI_Msk) >> CAN_TXFQS_TFQPI_Pos;
}

static inline hri_can_txfqs_reg_t hri_can_get_TXFQS_reg(const void *const hw, hri_can_txfqs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXFQS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_txfqs_reg_t hri_can_read_TXFQS_reg(const void *const hw)
{
	return ((Can *)hw)->TXFQS.reg;
}

static inline bool hri_can_get_TXBRP_TRP0_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP0) >> CAN_TXBRP_TRP0_Pos;
}

static inline bool hri_can_get_TXBRP_TRP1_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP1) >> CAN_TXBRP_TRP1_Pos;
}

static inline bool hri_can_get_TXBRP_TRP2_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP2) >> CAN_TXBRP_TRP2_Pos;
}

static inline bool hri_can_get_TXBRP_TRP3_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP3) >> CAN_TXBRP_TRP3_Pos;
}

static inline bool hri_can_get_TXBRP_TRP4_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP4) >> CAN_TXBRP_TRP4_Pos;
}

static inline bool hri_can_get_TXBRP_TRP5_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP5) >> CAN_TXBRP_TRP5_Pos;
}

static inline bool hri_can_get_TXBRP_TRP6_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP6) >> CAN_TXBRP_TRP6_Pos;
}

static inline bool hri_can_get_TXBRP_TRP7_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP7) >> CAN_TXBRP_TRP7_Pos;
}

static inline bool hri_can_get_TXBRP_TRP8_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP8) >> CAN_TXBRP_TRP8_Pos;
}

static inline bool hri_can_get_TXBRP_TRP9_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP9) >> CAN_TXBRP_TRP9_Pos;
}

static inline bool hri_can_get_TXBRP_TRP10_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP10) >> CAN_TXBRP_TRP10_Pos;
}

static inline bool hri_can_get_TXBRP_TRP11_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP11) >> CAN_TXBRP_TRP11_Pos;
}

static inline bool hri_can_get_TXBRP_TRP12_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP12) >> CAN_TXBRP_TRP12_Pos;
}

static inline bool hri_can_get_TXBRP_TRP13_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP13) >> CAN_TXBRP_TRP13_Pos;
}

static inline bool hri_can_get_TXBRP_TRP14_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP14) >> CAN_TXBRP_TRP14_Pos;
}

static inline bool hri_can_get_TXBRP_TRP15_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP15) >> CAN_TXBRP_TRP15_Pos;
}

static inline bool hri_can_get_TXBRP_TRP16_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP16) >> CAN_TXBRP_TRP16_Pos;
}

static inline bool hri_can_get_TXBRP_TRP17_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP17) >> CAN_TXBRP_TRP17_Pos;
}

static inline bool hri_can_get_TXBRP_TRP18_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP18) >> CAN_TXBRP_TRP18_Pos;
}

static inline bool hri_can_get_TXBRP_TRP19_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP19) >> CAN_TXBRP_TRP19_Pos;
}

static inline bool hri_can_get_TXBRP_TRP20_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP20) >> CAN_TXBRP_TRP20_Pos;
}

static inline bool hri_can_get_TXBRP_TRP21_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP21) >> CAN_TXBRP_TRP21_Pos;
}

static inline bool hri_can_get_TXBRP_TRP22_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP22) >> CAN_TXBRP_TRP22_Pos;
}

static inline bool hri_can_get_TXBRP_TRP23_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP23) >> CAN_TXBRP_TRP23_Pos;
}

static inline bool hri_can_get_TXBRP_TRP24_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP24) >> CAN_TXBRP_TRP24_Pos;
}

static inline bool hri_can_get_TXBRP_TRP25_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP25) >> CAN_TXBRP_TRP25_Pos;
}

static inline bool hri_can_get_TXBRP_TRP26_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP26) >> CAN_TXBRP_TRP26_Pos;
}

static inline bool hri_can_get_TXBRP_TRP27_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP27) >> CAN_TXBRP_TRP27_Pos;
}

static inline bool hri_can_get_TXBRP_TRP28_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP28) >> CAN_TXBRP_TRP28_Pos;
}

static inline bool hri_can_get_TXBRP_TRP29_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP29) >> CAN_TXBRP_TRP29_Pos;
}

static inline bool hri_can_get_TXBRP_TRP30_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP30) >> CAN_TXBRP_TRP30_Pos;
}

static inline bool hri_can_get_TXBRP_TRP31_bit(const void *const hw)
{
	return (((Can *)hw)->TXBRP.reg & CAN_TXBRP_TRP31) >> CAN_TXBRP_TRP31_Pos;
}

static inline hri_can_txbrp_reg_t hri_can_get_TXBRP_reg(const void *const hw, hri_can_txbrp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBRP.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_txbrp_reg_t hri_can_read_TXBRP_reg(const void *const hw)
{
	return ((Can *)hw)->TXBRP.reg;
}

static inline bool hri_can_get_TXBTO_TO0_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO0) >> CAN_TXBTO_TO0_Pos;
}

static inline bool hri_can_get_TXBTO_TO1_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO1) >> CAN_TXBTO_TO1_Pos;
}

static inline bool hri_can_get_TXBTO_TO2_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO2) >> CAN_TXBTO_TO2_Pos;
}

static inline bool hri_can_get_TXBTO_TO3_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO3) >> CAN_TXBTO_TO3_Pos;
}

static inline bool hri_can_get_TXBTO_TO4_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO4) >> CAN_TXBTO_TO4_Pos;
}

static inline bool hri_can_get_TXBTO_TO5_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO5) >> CAN_TXBTO_TO5_Pos;
}

static inline bool hri_can_get_TXBTO_TO6_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO6) >> CAN_TXBTO_TO6_Pos;
}

static inline bool hri_can_get_TXBTO_TO7_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO7) >> CAN_TXBTO_TO7_Pos;
}

static inline bool hri_can_get_TXBTO_TO8_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO8) >> CAN_TXBTO_TO8_Pos;
}

static inline bool hri_can_get_TXBTO_TO9_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO9) >> CAN_TXBTO_TO9_Pos;
}

static inline bool hri_can_get_TXBTO_TO10_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO10) >> CAN_TXBTO_TO10_Pos;
}

static inline bool hri_can_get_TXBTO_TO11_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO11) >> CAN_TXBTO_TO11_Pos;
}

static inline bool hri_can_get_TXBTO_TO12_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO12) >> CAN_TXBTO_TO12_Pos;
}

static inline bool hri_can_get_TXBTO_TO13_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO13) >> CAN_TXBTO_TO13_Pos;
}

static inline bool hri_can_get_TXBTO_TO14_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO14) >> CAN_TXBTO_TO14_Pos;
}

static inline bool hri_can_get_TXBTO_TO15_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO15) >> CAN_TXBTO_TO15_Pos;
}

static inline bool hri_can_get_TXBTO_TO16_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO16) >> CAN_TXBTO_TO16_Pos;
}

static inline bool hri_can_get_TXBTO_TO17_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO17) >> CAN_TXBTO_TO17_Pos;
}

static inline bool hri_can_get_TXBTO_TO18_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO18) >> CAN_TXBTO_TO18_Pos;
}

static inline bool hri_can_get_TXBTO_TO19_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO19) >> CAN_TXBTO_TO19_Pos;
}

static inline bool hri_can_get_TXBTO_TO20_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO20) >> CAN_TXBTO_TO20_Pos;
}

static inline bool hri_can_get_TXBTO_TO21_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO21) >> CAN_TXBTO_TO21_Pos;
}

static inline bool hri_can_get_TXBTO_TO22_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO22) >> CAN_TXBTO_TO22_Pos;
}

static inline bool hri_can_get_TXBTO_TO23_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO23) >> CAN_TXBTO_TO23_Pos;
}

static inline bool hri_can_get_TXBTO_TO24_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO24) >> CAN_TXBTO_TO24_Pos;
}

static inline bool hri_can_get_TXBTO_TO25_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO25) >> CAN_TXBTO_TO25_Pos;
}

static inline bool hri_can_get_TXBTO_TO26_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO26) >> CAN_TXBTO_TO26_Pos;
}

static inline bool hri_can_get_TXBTO_TO27_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO27) >> CAN_TXBTO_TO27_Pos;
}

static inline bool hri_can_get_TXBTO_TO28_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO28) >> CAN_TXBTO_TO28_Pos;
}

static inline bool hri_can_get_TXBTO_TO29_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO29) >> CAN_TXBTO_TO29_Pos;
}

static inline bool hri_can_get_TXBTO_TO30_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO30) >> CAN_TXBTO_TO30_Pos;
}

static inline bool hri_can_get_TXBTO_TO31_bit(const void *const hw)
{
	return (((Can *)hw)->TXBTO.reg & CAN_TXBTO_TO31) >> CAN_TXBTO_TO31_Pos;
}

static inline hri_can_txbto_reg_t hri_can_get_TXBTO_reg(const void *const hw, hri_can_txbto_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTO.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_txbto_reg_t hri_can_read_TXBTO_reg(const void *const hw)
{
	return ((Can *)hw)->TXBTO.reg;
}

static inline bool hri_can_get_TXBCF_CF0_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF0) >> CAN_TXBCF_CF0_Pos;
}

static inline bool hri_can_get_TXBCF_CF1_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF1) >> CAN_TXBCF_CF1_Pos;
}

static inline bool hri_can_get_TXBCF_CF2_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF2) >> CAN_TXBCF_CF2_Pos;
}

static inline bool hri_can_get_TXBCF_CF3_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF3) >> CAN_TXBCF_CF3_Pos;
}

static inline bool hri_can_get_TXBCF_CF4_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF4) >> CAN_TXBCF_CF4_Pos;
}

static inline bool hri_can_get_TXBCF_CF5_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF5) >> CAN_TXBCF_CF5_Pos;
}

static inline bool hri_can_get_TXBCF_CF6_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF6) >> CAN_TXBCF_CF6_Pos;
}

static inline bool hri_can_get_TXBCF_CF7_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF7) >> CAN_TXBCF_CF7_Pos;
}

static inline bool hri_can_get_TXBCF_CF8_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF8) >> CAN_TXBCF_CF8_Pos;
}

static inline bool hri_can_get_TXBCF_CF9_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF9) >> CAN_TXBCF_CF9_Pos;
}

static inline bool hri_can_get_TXBCF_CF10_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF10) >> CAN_TXBCF_CF10_Pos;
}

static inline bool hri_can_get_TXBCF_CF11_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF11) >> CAN_TXBCF_CF11_Pos;
}

static inline bool hri_can_get_TXBCF_CF12_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF12) >> CAN_TXBCF_CF12_Pos;
}

static inline bool hri_can_get_TXBCF_CF13_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF13) >> CAN_TXBCF_CF13_Pos;
}

static inline bool hri_can_get_TXBCF_CF14_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF14) >> CAN_TXBCF_CF14_Pos;
}

static inline bool hri_can_get_TXBCF_CF15_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF15) >> CAN_TXBCF_CF15_Pos;
}

static inline bool hri_can_get_TXBCF_CF16_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF16) >> CAN_TXBCF_CF16_Pos;
}

static inline bool hri_can_get_TXBCF_CF17_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF17) >> CAN_TXBCF_CF17_Pos;
}

static inline bool hri_can_get_TXBCF_CF18_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF18) >> CAN_TXBCF_CF18_Pos;
}

static inline bool hri_can_get_TXBCF_CF19_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF19) >> CAN_TXBCF_CF19_Pos;
}

static inline bool hri_can_get_TXBCF_CF20_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF20) >> CAN_TXBCF_CF20_Pos;
}

static inline bool hri_can_get_TXBCF_CF21_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF21) >> CAN_TXBCF_CF21_Pos;
}

static inline bool hri_can_get_TXBCF_CF22_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF22) >> CAN_TXBCF_CF22_Pos;
}

static inline bool hri_can_get_TXBCF_CF23_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF23) >> CAN_TXBCF_CF23_Pos;
}

static inline bool hri_can_get_TXBCF_CF24_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF24) >> CAN_TXBCF_CF24_Pos;
}

static inline bool hri_can_get_TXBCF_CF25_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF25) >> CAN_TXBCF_CF25_Pos;
}

static inline bool hri_can_get_TXBCF_CF26_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF26) >> CAN_TXBCF_CF26_Pos;
}

static inline bool hri_can_get_TXBCF_CF27_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF27) >> CAN_TXBCF_CF27_Pos;
}

static inline bool hri_can_get_TXBCF_CF28_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF28) >> CAN_TXBCF_CF28_Pos;
}

static inline bool hri_can_get_TXBCF_CF29_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF29) >> CAN_TXBCF_CF29_Pos;
}

static inline bool hri_can_get_TXBCF_CF30_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF30) >> CAN_TXBCF_CF30_Pos;
}

static inline bool hri_can_get_TXBCF_CF31_bit(const void *const hw)
{
	return (((Can *)hw)->TXBCF.reg & CAN_TXBCF_CF31) >> CAN_TXBCF_CF31_Pos;
}

static inline hri_can_txbcf_reg_t hri_can_get_TXBCF_reg(const void *const hw, hri_can_txbcf_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCF.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_txbcf_reg_t hri_can_read_TXBCF_reg(const void *const hw)
{
	return ((Can *)hw)->TXBCF.reg;
}

static inline bool hri_can_get_TXEFS_EFF_bit(const void *const hw)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_EFF) >> CAN_TXEFS_EFF_Pos;
}

static inline bool hri_can_get_TXEFS_TEFL_bit(const void *const hw)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_TEFL) >> CAN_TXEFS_TEFL_Pos;
}

static inline hri_can_txefs_reg_t hri_can_get_TXEFS_EFFL_bf(const void *const hw, hri_can_txefs_reg_t mask)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_EFFL(mask)) >> CAN_TXEFS_EFFL_Pos;
}

static inline hri_can_txefs_reg_t hri_can_read_TXEFS_EFFL_bf(const void *const hw)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_EFFL_Msk) >> CAN_TXEFS_EFFL_Pos;
}

static inline hri_can_txefs_reg_t hri_can_get_TXEFS_EFGI_bf(const void *const hw, hri_can_txefs_reg_t mask)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_EFGI(mask)) >> CAN_TXEFS_EFGI_Pos;
}

static inline hri_can_txefs_reg_t hri_can_read_TXEFS_EFGI_bf(const void *const hw)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_EFGI_Msk) >> CAN_TXEFS_EFGI_Pos;
}

static inline hri_can_txefs_reg_t hri_can_get_TXEFS_EFPI_bf(const void *const hw, hri_can_txefs_reg_t mask)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_EFPI(mask)) >> CAN_TXEFS_EFPI_Pos;
}

static inline hri_can_txefs_reg_t hri_can_read_TXEFS_EFPI_bf(const void *const hw)
{
	return (((Can *)hw)->TXEFS.reg & CAN_TXEFS_EFPI_Msk) >> CAN_TXEFS_EFPI_Pos;
}

static inline hri_can_txefs_reg_t hri_can_get_TXEFS_reg(const void *const hw, hri_can_txefs_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFS.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_can_txefs_reg_t hri_can_read_TXEFS_reg(const void *const hw)
{
	return ((Can *)hw)->TXEFS.reg;
}

static inline void hri_can_set_MRCFG_QOS_bf(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->MRCFG.reg |= CAN_MRCFG_QOS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_mrcfg_reg_t hri_can_get_MRCFG_QOS_bf(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->MRCFG.reg;
	tmp = (tmp & CAN_MRCFG_QOS(mask)) >> CAN_MRCFG_QOS_Pos;
	return tmp;
}

static inline void hri_can_write_MRCFG_QOS_bf(const void *const hw, hri_can_mrcfg_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->MRCFG.reg;
	tmp &= ~CAN_MRCFG_QOS_Msk;
	tmp |= CAN_MRCFG_QOS(data);
	((Can *)hw)->MRCFG.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_MRCFG_QOS_bf(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->MRCFG.reg &= ~CAN_MRCFG_QOS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_MRCFG_QOS_bf(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->MRCFG.reg ^= CAN_MRCFG_QOS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_mrcfg_reg_t hri_can_read_MRCFG_QOS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->MRCFG.reg;
	tmp = (tmp & CAN_MRCFG_QOS_Msk) >> CAN_MRCFG_QOS_Pos;
	return tmp;
}

static inline void hri_can_set_MRCFG_reg(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->MRCFG.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_mrcfg_reg_t hri_can_get_MRCFG_reg(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->MRCFG.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_MRCFG_reg(const void *const hw, hri_can_mrcfg_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->MRCFG.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_MRCFG_reg(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->MRCFG.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_MRCFG_reg(const void *const hw, hri_can_mrcfg_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->MRCFG.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_mrcfg_reg_t hri_can_read_MRCFG_reg(const void *const hw)
{
	return ((Can *)hw)->MRCFG.reg;
}

static inline void hri_can_set_DBTP_TDC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg |= CAN_DBTP_TDC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_DBTP_TDC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_TDC) >> CAN_DBTP_TDC_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_DBTP_TDC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->DBTP.reg;
	tmp &= ~CAN_DBTP_TDC;
	tmp |= value << CAN_DBTP_TDC_Pos;
	((Can *)hw)->DBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_DBTP_TDC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg &= ~CAN_DBTP_TDC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_DBTP_TDC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg ^= CAN_DBTP_TDC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_DBTP_DSJW_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg |= CAN_DBTP_DSJW(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_get_DBTP_DSJW_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DSJW(mask)) >> CAN_DBTP_DSJW_Pos;
	return tmp;
}

static inline void hri_can_write_DBTP_DSJW_bf(const void *const hw, hri_can_dbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->DBTP.reg;
	tmp &= ~CAN_DBTP_DSJW_Msk;
	tmp |= CAN_DBTP_DSJW(data);
	((Can *)hw)->DBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_DBTP_DSJW_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg &= ~CAN_DBTP_DSJW(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_DBTP_DSJW_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg ^= CAN_DBTP_DSJW(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_read_DBTP_DSJW_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DSJW_Msk) >> CAN_DBTP_DSJW_Pos;
	return tmp;
}

static inline void hri_can_set_DBTP_DTSEG2_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg |= CAN_DBTP_DTSEG2(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_get_DBTP_DTSEG2_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DTSEG2(mask)) >> CAN_DBTP_DTSEG2_Pos;
	return tmp;
}

static inline void hri_can_write_DBTP_DTSEG2_bf(const void *const hw, hri_can_dbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->DBTP.reg;
	tmp &= ~CAN_DBTP_DTSEG2_Msk;
	tmp |= CAN_DBTP_DTSEG2(data);
	((Can *)hw)->DBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_DBTP_DTSEG2_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg &= ~CAN_DBTP_DTSEG2(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_DBTP_DTSEG2_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg ^= CAN_DBTP_DTSEG2(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_read_DBTP_DTSEG2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DTSEG2_Msk) >> CAN_DBTP_DTSEG2_Pos;
	return tmp;
}

static inline void hri_can_set_DBTP_DTSEG1_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg |= CAN_DBTP_DTSEG1(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_get_DBTP_DTSEG1_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DTSEG1(mask)) >> CAN_DBTP_DTSEG1_Pos;
	return tmp;
}

static inline void hri_can_write_DBTP_DTSEG1_bf(const void *const hw, hri_can_dbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->DBTP.reg;
	tmp &= ~CAN_DBTP_DTSEG1_Msk;
	tmp |= CAN_DBTP_DTSEG1(data);
	((Can *)hw)->DBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_DBTP_DTSEG1_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg &= ~CAN_DBTP_DTSEG1(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_DBTP_DTSEG1_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg ^= CAN_DBTP_DTSEG1(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_read_DBTP_DTSEG1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DTSEG1_Msk) >> CAN_DBTP_DTSEG1_Pos;
	return tmp;
}

static inline void hri_can_set_DBTP_DBRP_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg |= CAN_DBTP_DBRP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_get_DBTP_DBRP_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DBRP(mask)) >> CAN_DBTP_DBRP_Pos;
	return tmp;
}

static inline void hri_can_write_DBTP_DBRP_bf(const void *const hw, hri_can_dbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->DBTP.reg;
	tmp &= ~CAN_DBTP_DBRP_Msk;
	tmp |= CAN_DBTP_DBRP(data);
	((Can *)hw)->DBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_DBTP_DBRP_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg &= ~CAN_DBTP_DBRP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_DBTP_DBRP_bf(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg ^= CAN_DBTP_DBRP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_read_DBTP_DBRP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp = (tmp & CAN_DBTP_DBRP_Msk) >> CAN_DBTP_DBRP_Pos;
	return tmp;
}

static inline void hri_can_set_DBTP_reg(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_get_DBTP_reg(const void *const hw, hri_can_dbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->DBTP.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_DBTP_reg(const void *const hw, hri_can_dbtp_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_DBTP_reg(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_DBTP_reg(const void *const hw, hri_can_dbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->DBTP.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_dbtp_reg_t hri_can_read_DBTP_reg(const void *const hw)
{
	return ((Can *)hw)->DBTP.reg;
}

static inline void hri_can_set_TEST_LBCK_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg |= CAN_TEST_LBCK;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TEST_LBCK_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TEST.reg;
	tmp = (tmp & CAN_TEST_LBCK) >> CAN_TEST_LBCK_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TEST_LBCK_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TEST.reg;
	tmp &= ~CAN_TEST_LBCK;
	tmp |= value << CAN_TEST_LBCK_Pos;
	((Can *)hw)->TEST.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TEST_LBCK_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg &= ~CAN_TEST_LBCK;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TEST_LBCK_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg ^= CAN_TEST_LBCK;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TEST_RX_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg |= CAN_TEST_RX;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TEST_RX_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TEST.reg;
	tmp = (tmp & CAN_TEST_RX) >> CAN_TEST_RX_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TEST_RX_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TEST.reg;
	tmp &= ~CAN_TEST_RX;
	tmp |= value << CAN_TEST_RX_Pos;
	((Can *)hw)->TEST.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TEST_RX_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg &= ~CAN_TEST_RX;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TEST_RX_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg ^= CAN_TEST_RX;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TEST_TX_bf(const void *const hw, hri_can_test_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg |= CAN_TEST_TX(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_test_reg_t hri_can_get_TEST_TX_bf(const void *const hw, hri_can_test_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TEST.reg;
	tmp = (tmp & CAN_TEST_TX(mask)) >> CAN_TEST_TX_Pos;
	return tmp;
}

static inline void hri_can_write_TEST_TX_bf(const void *const hw, hri_can_test_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TEST.reg;
	tmp &= ~CAN_TEST_TX_Msk;
	tmp |= CAN_TEST_TX(data);
	((Can *)hw)->TEST.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TEST_TX_bf(const void *const hw, hri_can_test_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg &= ~CAN_TEST_TX(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TEST_TX_bf(const void *const hw, hri_can_test_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg ^= CAN_TEST_TX(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_test_reg_t hri_can_read_TEST_TX_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TEST.reg;
	tmp = (tmp & CAN_TEST_TX_Msk) >> CAN_TEST_TX_Pos;
	return tmp;
}

static inline void hri_can_set_TEST_reg(const void *const hw, hri_can_test_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_test_reg_t hri_can_get_TEST_reg(const void *const hw, hri_can_test_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TEST.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TEST_reg(const void *const hw, hri_can_test_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TEST_reg(const void *const hw, hri_can_test_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TEST_reg(const void *const hw, hri_can_test_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TEST.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_test_reg_t hri_can_read_TEST_reg(const void *const hw)
{
	return ((Can *)hw)->TEST.reg;
}

static inline void hri_can_set_RWD_WDC_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg |= CAN_RWD_WDC(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rwd_reg_t hri_can_get_RWD_WDC_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RWD.reg;
	tmp = (tmp & CAN_RWD_WDC(mask)) >> CAN_RWD_WDC_Pos;
	return tmp;
}

static inline void hri_can_write_RWD_WDC_bf(const void *const hw, hri_can_rwd_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RWD.reg;
	tmp &= ~CAN_RWD_WDC_Msk;
	tmp |= CAN_RWD_WDC(data);
	((Can *)hw)->RWD.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RWD_WDC_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg &= ~CAN_RWD_WDC(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RWD_WDC_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg ^= CAN_RWD_WDC(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rwd_reg_t hri_can_read_RWD_WDC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RWD.reg;
	tmp = (tmp & CAN_RWD_WDC_Msk) >> CAN_RWD_WDC_Pos;
	return tmp;
}

static inline void hri_can_set_RWD_WDV_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg |= CAN_RWD_WDV(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rwd_reg_t hri_can_get_RWD_WDV_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RWD.reg;
	tmp = (tmp & CAN_RWD_WDV(mask)) >> CAN_RWD_WDV_Pos;
	return tmp;
}

static inline void hri_can_write_RWD_WDV_bf(const void *const hw, hri_can_rwd_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RWD.reg;
	tmp &= ~CAN_RWD_WDV_Msk;
	tmp |= CAN_RWD_WDV(data);
	((Can *)hw)->RWD.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RWD_WDV_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg &= ~CAN_RWD_WDV(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RWD_WDV_bf(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg ^= CAN_RWD_WDV(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rwd_reg_t hri_can_read_RWD_WDV_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RWD.reg;
	tmp = (tmp & CAN_RWD_WDV_Msk) >> CAN_RWD_WDV_Pos;
	return tmp;
}

static inline void hri_can_set_RWD_reg(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rwd_reg_t hri_can_get_RWD_reg(const void *const hw, hri_can_rwd_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RWD.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_RWD_reg(const void *const hw, hri_can_rwd_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RWD_reg(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RWD_reg(const void *const hw, hri_can_rwd_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RWD.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rwd_reg_t hri_can_read_RWD_reg(const void *const hw)
{
	return ((Can *)hw)->RWD.reg;
}

static inline void hri_can_set_CCCR_INIT_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_INIT;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_INIT_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_INIT) >> CAN_CCCR_INIT_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_INIT_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_INIT;
	tmp |= value << CAN_CCCR_INIT_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_INIT_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_INIT;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_INIT_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_INIT;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_CCE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_CCE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_CCE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_CCE) >> CAN_CCCR_CCE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_CCE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_CCE;
	tmp |= value << CAN_CCCR_CCE_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_CCE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_CCE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_CCE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_CCE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_ASM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_ASM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_ASM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_ASM) >> CAN_CCCR_ASM_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_ASM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_ASM;
	tmp |= value << CAN_CCCR_ASM_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_ASM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_ASM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_ASM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_ASM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_CSA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_CSA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_CSA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_CSA) >> CAN_CCCR_CSA_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_CSA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_CSA;
	tmp |= value << CAN_CCCR_CSA_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_CSA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_CSA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_CSA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_CSA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_CSR_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_CSR;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_CSR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_CSR) >> CAN_CCCR_CSR_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_CSR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_CSR;
	tmp |= value << CAN_CCCR_CSR_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_CSR_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_CSR;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_CSR_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_CSR;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_MON_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_MON;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_MON_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_MON) >> CAN_CCCR_MON_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_MON_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_MON;
	tmp |= value << CAN_CCCR_MON_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_MON_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_MON;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_MON_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_MON;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_DAR_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_DAR;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_DAR_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_DAR) >> CAN_CCCR_DAR_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_DAR_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_DAR;
	tmp |= value << CAN_CCCR_DAR_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_DAR_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_DAR;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_DAR_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_DAR;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_TEST_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_TEST;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_TEST_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_TEST) >> CAN_CCCR_TEST_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_TEST_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_TEST;
	tmp |= value << CAN_CCCR_TEST_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_TEST_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_TEST;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_TEST_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_TEST;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_FDOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_FDOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_FDOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_FDOE) >> CAN_CCCR_FDOE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_FDOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_FDOE;
	tmp |= value << CAN_CCCR_FDOE_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_FDOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_FDOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_FDOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_FDOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_BRSE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_BRSE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_BRSE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_BRSE) >> CAN_CCCR_BRSE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_BRSE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_BRSE;
	tmp |= value << CAN_CCCR_BRSE_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_BRSE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_BRSE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_BRSE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_BRSE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_PXHD_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_PXHD;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_PXHD_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_PXHD) >> CAN_CCCR_PXHD_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_PXHD_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_PXHD;
	tmp |= value << CAN_CCCR_PXHD_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_PXHD_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_PXHD;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_PXHD_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_PXHD;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_EFBI_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_EFBI;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_EFBI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_EFBI) >> CAN_CCCR_EFBI_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_EFBI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_EFBI;
	tmp |= value << CAN_CCCR_EFBI_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_EFBI_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_EFBI;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_EFBI_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_EFBI;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_TXP_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_TXP;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_TXP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_TXP) >> CAN_CCCR_TXP_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_TXP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_TXP;
	tmp |= value << CAN_CCCR_TXP_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_TXP_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_TXP;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_TXP_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_TXP;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_NISO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= CAN_CCCR_NISO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_CCCR_NISO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp = (tmp & CAN_CCCR_NISO) >> CAN_CCCR_NISO_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_CCCR_NISO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= ~CAN_CCCR_NISO;
	tmp |= value << CAN_CCCR_NISO_Pos;
	((Can *)hw)->CCCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_NISO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~CAN_CCCR_NISO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_NISO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= CAN_CCCR_NISO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_CCCR_reg(const void *const hw, hri_can_cccr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_cccr_reg_t hri_can_get_CCCR_reg(const void *const hw, hri_can_cccr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->CCCR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_CCCR_reg(const void *const hw, hri_can_cccr_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_CCCR_reg(const void *const hw, hri_can_cccr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_CCCR_reg(const void *const hw, hri_can_cccr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->CCCR.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_cccr_reg_t hri_can_read_CCCR_reg(const void *const hw)
{
	return ((Can *)hw)->CCCR.reg;
}

static inline void hri_can_set_NBTP_NTSEG2_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg |= CAN_NBTP_NTSEG2(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_get_NBTP_NTSEG2_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NTSEG2(mask)) >> CAN_NBTP_NTSEG2_Pos;
	return tmp;
}

static inline void hri_can_write_NBTP_NTSEG2_bf(const void *const hw, hri_can_nbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NBTP.reg;
	tmp &= ~CAN_NBTP_NTSEG2_Msk;
	tmp |= CAN_NBTP_NTSEG2(data);
	((Can *)hw)->NBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NBTP_NTSEG2_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg &= ~CAN_NBTP_NTSEG2(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NBTP_NTSEG2_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg ^= CAN_NBTP_NTSEG2(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_read_NBTP_NTSEG2_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NTSEG2_Msk) >> CAN_NBTP_NTSEG2_Pos;
	return tmp;
}

static inline void hri_can_set_NBTP_NTSEG1_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg |= CAN_NBTP_NTSEG1(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_get_NBTP_NTSEG1_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NTSEG1(mask)) >> CAN_NBTP_NTSEG1_Pos;
	return tmp;
}

static inline void hri_can_write_NBTP_NTSEG1_bf(const void *const hw, hri_can_nbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NBTP.reg;
	tmp &= ~CAN_NBTP_NTSEG1_Msk;
	tmp |= CAN_NBTP_NTSEG1(data);
	((Can *)hw)->NBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NBTP_NTSEG1_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg &= ~CAN_NBTP_NTSEG1(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NBTP_NTSEG1_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg ^= CAN_NBTP_NTSEG1(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_read_NBTP_NTSEG1_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NTSEG1_Msk) >> CAN_NBTP_NTSEG1_Pos;
	return tmp;
}

static inline void hri_can_set_NBTP_NBRP_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg |= CAN_NBTP_NBRP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_get_NBTP_NBRP_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NBRP(mask)) >> CAN_NBTP_NBRP_Pos;
	return tmp;
}

static inline void hri_can_write_NBTP_NBRP_bf(const void *const hw, hri_can_nbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NBTP.reg;
	tmp &= ~CAN_NBTP_NBRP_Msk;
	tmp |= CAN_NBTP_NBRP(data);
	((Can *)hw)->NBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NBTP_NBRP_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg &= ~CAN_NBTP_NBRP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NBTP_NBRP_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg ^= CAN_NBTP_NBRP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_read_NBTP_NBRP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NBRP_Msk) >> CAN_NBTP_NBRP_Pos;
	return tmp;
}

static inline void hri_can_set_NBTP_NSJW_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg |= CAN_NBTP_NSJW(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_get_NBTP_NSJW_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NSJW(mask)) >> CAN_NBTP_NSJW_Pos;
	return tmp;
}

static inline void hri_can_write_NBTP_NSJW_bf(const void *const hw, hri_can_nbtp_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NBTP.reg;
	tmp &= ~CAN_NBTP_NSJW_Msk;
	tmp |= CAN_NBTP_NSJW(data);
	((Can *)hw)->NBTP.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NBTP_NSJW_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg &= ~CAN_NBTP_NSJW(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NBTP_NSJW_bf(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg ^= CAN_NBTP_NSJW(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_read_NBTP_NSJW_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp = (tmp & CAN_NBTP_NSJW_Msk) >> CAN_NBTP_NSJW_Pos;
	return tmp;
}

static inline void hri_can_set_NBTP_reg(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_get_NBTP_reg(const void *const hw, hri_can_nbtp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NBTP.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_NBTP_reg(const void *const hw, hri_can_nbtp_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NBTP_reg(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NBTP_reg(const void *const hw, hri_can_nbtp_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NBTP.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_nbtp_reg_t hri_can_read_NBTP_reg(const void *const hw)
{
	return ((Can *)hw)->NBTP.reg;
}

static inline void hri_can_set_TSCC_TSS_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg |= CAN_TSCC_TSS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tscc_reg_t hri_can_get_TSCC_TSS_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TSCC.reg;
	tmp = (tmp & CAN_TSCC_TSS(mask)) >> CAN_TSCC_TSS_Pos;
	return tmp;
}

static inline void hri_can_write_TSCC_TSS_bf(const void *const hw, hri_can_tscc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TSCC.reg;
	tmp &= ~CAN_TSCC_TSS_Msk;
	tmp |= CAN_TSCC_TSS(data);
	((Can *)hw)->TSCC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TSCC_TSS_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg &= ~CAN_TSCC_TSS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TSCC_TSS_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg ^= CAN_TSCC_TSS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tscc_reg_t hri_can_read_TSCC_TSS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TSCC.reg;
	tmp = (tmp & CAN_TSCC_TSS_Msk) >> CAN_TSCC_TSS_Pos;
	return tmp;
}

static inline void hri_can_set_TSCC_TCP_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg |= CAN_TSCC_TCP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tscc_reg_t hri_can_get_TSCC_TCP_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TSCC.reg;
	tmp = (tmp & CAN_TSCC_TCP(mask)) >> CAN_TSCC_TCP_Pos;
	return tmp;
}

static inline void hri_can_write_TSCC_TCP_bf(const void *const hw, hri_can_tscc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TSCC.reg;
	tmp &= ~CAN_TSCC_TCP_Msk;
	tmp |= CAN_TSCC_TCP(data);
	((Can *)hw)->TSCC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TSCC_TCP_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg &= ~CAN_TSCC_TCP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TSCC_TCP_bf(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg ^= CAN_TSCC_TCP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tscc_reg_t hri_can_read_TSCC_TCP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TSCC.reg;
	tmp = (tmp & CAN_TSCC_TCP_Msk) >> CAN_TSCC_TCP_Pos;
	return tmp;
}

static inline void hri_can_set_TSCC_reg(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tscc_reg_t hri_can_get_TSCC_reg(const void *const hw, hri_can_tscc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TSCC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TSCC_reg(const void *const hw, hri_can_tscc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TSCC_reg(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TSCC_reg(const void *const hw, hri_can_tscc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TSCC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tscc_reg_t hri_can_read_TSCC_reg(const void *const hw)
{
	return ((Can *)hw)->TSCC.reg;
}

static inline void hri_can_set_TOCC_ETOC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg |= CAN_TOCC_ETOC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TOCC_ETOC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCC.reg;
	tmp = (tmp & CAN_TOCC_ETOC) >> CAN_TOCC_ETOC_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TOCC_ETOC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TOCC.reg;
	tmp &= ~CAN_TOCC_ETOC;
	tmp |= value << CAN_TOCC_ETOC_Pos;
	((Can *)hw)->TOCC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TOCC_ETOC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg &= ~CAN_TOCC_ETOC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TOCC_ETOC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg ^= CAN_TOCC_ETOC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TOCC_TOS_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg |= CAN_TOCC_TOS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocc_reg_t hri_can_get_TOCC_TOS_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCC.reg;
	tmp = (tmp & CAN_TOCC_TOS(mask)) >> CAN_TOCC_TOS_Pos;
	return tmp;
}

static inline void hri_can_write_TOCC_TOS_bf(const void *const hw, hri_can_tocc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TOCC.reg;
	tmp &= ~CAN_TOCC_TOS_Msk;
	tmp |= CAN_TOCC_TOS(data);
	((Can *)hw)->TOCC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TOCC_TOS_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg &= ~CAN_TOCC_TOS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TOCC_TOS_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg ^= CAN_TOCC_TOS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocc_reg_t hri_can_read_TOCC_TOS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCC.reg;
	tmp = (tmp & CAN_TOCC_TOS_Msk) >> CAN_TOCC_TOS_Pos;
	return tmp;
}

static inline void hri_can_set_TOCC_TOP_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg |= CAN_TOCC_TOP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocc_reg_t hri_can_get_TOCC_TOP_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCC.reg;
	tmp = (tmp & CAN_TOCC_TOP(mask)) >> CAN_TOCC_TOP_Pos;
	return tmp;
}

static inline void hri_can_write_TOCC_TOP_bf(const void *const hw, hri_can_tocc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TOCC.reg;
	tmp &= ~CAN_TOCC_TOP_Msk;
	tmp |= CAN_TOCC_TOP(data);
	((Can *)hw)->TOCC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TOCC_TOP_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg &= ~CAN_TOCC_TOP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TOCC_TOP_bf(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg ^= CAN_TOCC_TOP(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocc_reg_t hri_can_read_TOCC_TOP_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCC.reg;
	tmp = (tmp & CAN_TOCC_TOP_Msk) >> CAN_TOCC_TOP_Pos;
	return tmp;
}

static inline void hri_can_set_TOCC_reg(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocc_reg_t hri_can_get_TOCC_reg(const void *const hw, hri_can_tocc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TOCC_reg(const void *const hw, hri_can_tocc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TOCC_reg(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TOCC_reg(const void *const hw, hri_can_tocc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocc_reg_t hri_can_read_TOCC_reg(const void *const hw)
{
	return ((Can *)hw)->TOCC.reg;
}

static inline void hri_can_set_TOCV_TOC_bf(const void *const hw, hri_can_tocv_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCV.reg |= CAN_TOCV_TOC(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocv_reg_t hri_can_get_TOCV_TOC_bf(const void *const hw, hri_can_tocv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCV.reg;
	tmp = (tmp & CAN_TOCV_TOC(mask)) >> CAN_TOCV_TOC_Pos;
	return tmp;
}

static inline void hri_can_write_TOCV_TOC_bf(const void *const hw, hri_can_tocv_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TOCV.reg;
	tmp &= ~CAN_TOCV_TOC_Msk;
	tmp |= CAN_TOCV_TOC(data);
	((Can *)hw)->TOCV.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TOCV_TOC_bf(const void *const hw, hri_can_tocv_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCV.reg &= ~CAN_TOCV_TOC(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TOCV_TOC_bf(const void *const hw, hri_can_tocv_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCV.reg ^= CAN_TOCV_TOC(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocv_reg_t hri_can_read_TOCV_TOC_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCV.reg;
	tmp = (tmp & CAN_TOCV_TOC_Msk) >> CAN_TOCV_TOC_Pos;
	return tmp;
}

static inline void hri_can_set_TOCV_reg(const void *const hw, hri_can_tocv_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCV.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocv_reg_t hri_can_get_TOCV_reg(const void *const hw, hri_can_tocv_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TOCV.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TOCV_reg(const void *const hw, hri_can_tocv_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCV.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TOCV_reg(const void *const hw, hri_can_tocv_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCV.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TOCV_reg(const void *const hw, hri_can_tocv_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TOCV.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tocv_reg_t hri_can_read_TOCV_reg(const void *const hw)
{
	return ((Can *)hw)->TOCV.reg;
}

static inline void hri_can_set_TDCR_TDCF_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg |= CAN_TDCR_TDCF(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tdcr_reg_t hri_can_get_TDCR_TDCF_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TDCR.reg;
	tmp = (tmp & CAN_TDCR_TDCF(mask)) >> CAN_TDCR_TDCF_Pos;
	return tmp;
}

static inline void hri_can_write_TDCR_TDCF_bf(const void *const hw, hri_can_tdcr_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TDCR.reg;
	tmp &= ~CAN_TDCR_TDCF_Msk;
	tmp |= CAN_TDCR_TDCF(data);
	((Can *)hw)->TDCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TDCR_TDCF_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg &= ~CAN_TDCR_TDCF(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TDCR_TDCF_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg ^= CAN_TDCR_TDCF(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tdcr_reg_t hri_can_read_TDCR_TDCF_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TDCR.reg;
	tmp = (tmp & CAN_TDCR_TDCF_Msk) >> CAN_TDCR_TDCF_Pos;
	return tmp;
}

static inline void hri_can_set_TDCR_TDCO_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg |= CAN_TDCR_TDCO(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tdcr_reg_t hri_can_get_TDCR_TDCO_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TDCR.reg;
	tmp = (tmp & CAN_TDCR_TDCO(mask)) >> CAN_TDCR_TDCO_Pos;
	return tmp;
}

static inline void hri_can_write_TDCR_TDCO_bf(const void *const hw, hri_can_tdcr_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TDCR.reg;
	tmp &= ~CAN_TDCR_TDCO_Msk;
	tmp |= CAN_TDCR_TDCO(data);
	((Can *)hw)->TDCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TDCR_TDCO_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg &= ~CAN_TDCR_TDCO(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TDCR_TDCO_bf(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg ^= CAN_TDCR_TDCO(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tdcr_reg_t hri_can_read_TDCR_TDCO_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TDCR.reg;
	tmp = (tmp & CAN_TDCR_TDCO_Msk) >> CAN_TDCR_TDCO_Pos;
	return tmp;
}

static inline void hri_can_set_TDCR_reg(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tdcr_reg_t hri_can_get_TDCR_reg(const void *const hw, hri_can_tdcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TDCR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TDCR_reg(const void *const hw, hri_can_tdcr_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TDCR_reg(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TDCR_reg(const void *const hw, hri_can_tdcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TDCR.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_tdcr_reg_t hri_can_read_TDCR_reg(const void *const hw)
{
	return ((Can *)hw)->TDCR.reg;
}

static inline void hri_can_set_IR_RF0N_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF0N;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF0N_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF0N) >> CAN_IR_RF0N_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF0N_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF0N;
	tmp |= value << CAN_IR_RF0N_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF0N_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF0N;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF0N_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF0N;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_RF0W_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF0W;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF0W_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF0W) >> CAN_IR_RF0W_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF0W_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF0W;
	tmp |= value << CAN_IR_RF0W_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF0W_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF0W;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF0W_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF0W;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_RF0F_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF0F;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF0F_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF0F) >> CAN_IR_RF0F_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF0F_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF0F;
	tmp |= value << CAN_IR_RF0F_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF0F_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF0F;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF0F_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF0F;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_RF0L_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF0L;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF0L_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF0L) >> CAN_IR_RF0L_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF0L_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF0L;
	tmp |= value << CAN_IR_RF0L_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF0L_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF0L;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF0L_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF0L;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_RF1N_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF1N;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF1N_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF1N) >> CAN_IR_RF1N_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF1N_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF1N;
	tmp |= value << CAN_IR_RF1N_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF1N_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF1N;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF1N_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF1N;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_RF1W_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF1W;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF1W_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF1W) >> CAN_IR_RF1W_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF1W_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF1W;
	tmp |= value << CAN_IR_RF1W_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF1W_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF1W;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF1W_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF1W;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_RF1F_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF1F;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF1F_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF1F) >> CAN_IR_RF1F_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF1F_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF1F;
	tmp |= value << CAN_IR_RF1F_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF1F_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF1F;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF1F_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF1F;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_RF1L_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_RF1L;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_RF1L_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_RF1L) >> CAN_IR_RF1L_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_RF1L_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_RF1L;
	tmp |= value << CAN_IR_RF1L_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_RF1L_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_RF1L;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_RF1L_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_RF1L;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_HPM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_HPM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_HPM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_HPM) >> CAN_IR_HPM_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_HPM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_HPM;
	tmp |= value << CAN_IR_HPM_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_HPM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_HPM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_HPM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_HPM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TC) >> CAN_IR_TC_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TC;
	tmp |= value << CAN_IR_TC_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TCF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TCF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TCF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TCF) >> CAN_IR_TCF_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TCF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TCF;
	tmp |= value << CAN_IR_TCF_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TCF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TCF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TCF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TCF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TFE) >> CAN_IR_TFE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TFE;
	tmp |= value << CAN_IR_TFE_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TEFN_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TEFN;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TEFN_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TEFN) >> CAN_IR_TEFN_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TEFN_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TEFN;
	tmp |= value << CAN_IR_TEFN_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TEFN_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TEFN;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TEFN_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TEFN;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TEFW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TEFW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TEFW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TEFW) >> CAN_IR_TEFW_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TEFW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TEFW;
	tmp |= value << CAN_IR_TEFW_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TEFW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TEFW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TEFW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TEFW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TEFF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TEFF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TEFF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TEFF) >> CAN_IR_TEFF_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TEFF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TEFF;
	tmp |= value << CAN_IR_TEFF_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TEFF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TEFF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TEFF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TEFF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TEFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TEFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TEFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TEFL) >> CAN_IR_TEFL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TEFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TEFL;
	tmp |= value << CAN_IR_TEFL_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TEFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TEFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TEFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TEFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TSW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TSW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TSW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TSW) >> CAN_IR_TSW_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TSW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TSW;
	tmp |= value << CAN_IR_TSW_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TSW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TSW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TSW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TSW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_MRAF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_MRAF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_MRAF_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_MRAF) >> CAN_IR_MRAF_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_MRAF_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_MRAF;
	tmp |= value << CAN_IR_MRAF_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_MRAF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_MRAF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_MRAF_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_MRAF;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_TOO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_TOO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_TOO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_TOO) >> CAN_IR_TOO_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_TOO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_TOO;
	tmp |= value << CAN_IR_TOO_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_TOO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_TOO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_TOO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_TOO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_DRX_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_DRX;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_DRX_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_DRX) >> CAN_IR_DRX_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_DRX_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_DRX;
	tmp |= value << CAN_IR_DRX_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_DRX_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_DRX;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_DRX_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_DRX;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_BEC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_BEC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_BEC_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_BEC) >> CAN_IR_BEC_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_BEC_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_BEC;
	tmp |= value << CAN_IR_BEC_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_BEC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_BEC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_BEC_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_BEC;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_BEU_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_BEU;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_BEU_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_BEU) >> CAN_IR_BEU_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_BEU_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_BEU;
	tmp |= value << CAN_IR_BEU_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_BEU_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_BEU;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_BEU_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_BEU;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_ELO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_ELO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_ELO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_ELO) >> CAN_IR_ELO_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_ELO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_ELO;
	tmp |= value << CAN_IR_ELO_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_ELO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_ELO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_ELO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_ELO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_EP_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_EP;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_EP_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_EP) >> CAN_IR_EP_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_EP_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_EP;
	tmp |= value << CAN_IR_EP_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_EP_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_EP;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_EP_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_EP;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_EW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_EW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_EW_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_EW) >> CAN_IR_EW_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_EW_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_EW;
	tmp |= value << CAN_IR_EW_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_EW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_EW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_EW_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_EW;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_BO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_BO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_BO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_BO) >> CAN_IR_BO_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_BO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_BO;
	tmp |= value << CAN_IR_BO_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_BO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_BO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_BO_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_BO;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_WDI_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_WDI;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_WDI_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_WDI) >> CAN_IR_WDI_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_WDI_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_WDI;
	tmp |= value << CAN_IR_WDI_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_WDI_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_WDI;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_WDI_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_WDI;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_PEA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_PEA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_PEA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_PEA) >> CAN_IR_PEA_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_PEA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_PEA;
	tmp |= value << CAN_IR_PEA_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_PEA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_PEA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_PEA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_PEA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_PED_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_PED;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_PED_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_PED) >> CAN_IR_PED_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_PED_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_PED;
	tmp |= value << CAN_IR_PED_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_PED_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_PED;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_PED_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_PED;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_ARA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= CAN_IR_ARA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IR_ARA_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp = (tmp & CAN_IR_ARA) >> CAN_IR_ARA_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IR_ARA_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IR.reg;
	tmp &= ~CAN_IR_ARA;
	tmp |= value << CAN_IR_ARA_Pos;
	((Can *)hw)->IR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_ARA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~CAN_IR_ARA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_ARA_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= CAN_IR_ARA;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IR_reg(const void *const hw, hri_can_ir_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ir_reg_t hri_can_get_IR_reg(const void *const hw, hri_can_ir_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_IR_reg(const void *const hw, hri_can_ir_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IR_reg(const void *const hw, hri_can_ir_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IR_reg(const void *const hw, hri_can_ir_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IR.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ir_reg_t hri_can_read_IR_reg(const void *const hw)
{
	return ((Can *)hw)->IR.reg;
}

static inline void hri_can_set_IE_RF0NE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF0NE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF0NE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF0NE) >> CAN_IE_RF0NE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF0NE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF0NE;
	tmp |= value << CAN_IE_RF0NE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF0NE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF0NE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF0NE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF0NE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_RF0WE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF0WE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF0WE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF0WE) >> CAN_IE_RF0WE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF0WE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF0WE;
	tmp |= value << CAN_IE_RF0WE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF0WE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF0WE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF0WE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF0WE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_RF0FE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF0FE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF0FE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF0FE) >> CAN_IE_RF0FE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF0FE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF0FE;
	tmp |= value << CAN_IE_RF0FE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF0FE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF0FE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF0FE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF0FE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_RF0LE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF0LE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF0LE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF0LE) >> CAN_IE_RF0LE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF0LE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF0LE;
	tmp |= value << CAN_IE_RF0LE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF0LE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF0LE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF0LE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF0LE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_RF1NE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF1NE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF1NE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF1NE) >> CAN_IE_RF1NE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF1NE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF1NE;
	tmp |= value << CAN_IE_RF1NE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF1NE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF1NE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF1NE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF1NE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_RF1WE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF1WE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF1WE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF1WE) >> CAN_IE_RF1WE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF1WE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF1WE;
	tmp |= value << CAN_IE_RF1WE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF1WE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF1WE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF1WE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF1WE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_RF1FE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF1FE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF1FE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF1FE) >> CAN_IE_RF1FE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF1FE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF1FE;
	tmp |= value << CAN_IE_RF1FE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF1FE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF1FE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF1FE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF1FE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_RF1LE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_RF1LE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_RF1LE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_RF1LE) >> CAN_IE_RF1LE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_RF1LE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_RF1LE;
	tmp |= value << CAN_IE_RF1LE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_RF1LE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_RF1LE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_RF1LE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_RF1LE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_HPME_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_HPME;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_HPME_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_HPME) >> CAN_IE_HPME_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_HPME_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_HPME;
	tmp |= value << CAN_IE_HPME_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_HPME_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_HPME;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_HPME_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_HPME;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TCE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TCE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TCE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TCE) >> CAN_IE_TCE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TCE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TCE;
	tmp |= value << CAN_IE_TCE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TCE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TCE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TCE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TCE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TCFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TCFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TCFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TCFE) >> CAN_IE_TCFE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TCFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TCFE;
	tmp |= value << CAN_IE_TCFE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TCFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TCFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TCFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TCFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TFEE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TFEE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TFEE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TFEE) >> CAN_IE_TFEE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TFEE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TFEE;
	tmp |= value << CAN_IE_TFEE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TFEE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TFEE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TFEE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TFEE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TEFNE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TEFNE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TEFNE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TEFNE) >> CAN_IE_TEFNE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TEFNE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TEFNE;
	tmp |= value << CAN_IE_TEFNE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TEFNE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TEFNE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TEFNE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TEFNE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TEFWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TEFWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TEFWE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TEFWE) >> CAN_IE_TEFWE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TEFWE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TEFWE;
	tmp |= value << CAN_IE_TEFWE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TEFWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TEFWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TEFWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TEFWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TEFFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TEFFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TEFFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TEFFE) >> CAN_IE_TEFFE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TEFFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TEFFE;
	tmp |= value << CAN_IE_TEFFE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TEFFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TEFFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TEFFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TEFFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TEFLE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TEFLE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TEFLE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TEFLE) >> CAN_IE_TEFLE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TEFLE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TEFLE;
	tmp |= value << CAN_IE_TEFLE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TEFLE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TEFLE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TEFLE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TEFLE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TSWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TSWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TSWE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TSWE) >> CAN_IE_TSWE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TSWE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TSWE;
	tmp |= value << CAN_IE_TSWE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TSWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TSWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TSWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TSWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_MRAFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_MRAFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_MRAFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_MRAFE) >> CAN_IE_MRAFE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_MRAFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_MRAFE;
	tmp |= value << CAN_IE_MRAFE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_MRAFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_MRAFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_MRAFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_MRAFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_TOOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_TOOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_TOOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_TOOE) >> CAN_IE_TOOE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_TOOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_TOOE;
	tmp |= value << CAN_IE_TOOE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_TOOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_TOOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_TOOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_TOOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_DRXE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_DRXE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_DRXE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_DRXE) >> CAN_IE_DRXE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_DRXE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_DRXE;
	tmp |= value << CAN_IE_DRXE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_DRXE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_DRXE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_DRXE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_DRXE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_BECE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_BECE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_BECE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_BECE) >> CAN_IE_BECE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_BECE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_BECE;
	tmp |= value << CAN_IE_BECE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_BECE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_BECE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_BECE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_BECE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_BEUE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_BEUE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_BEUE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_BEUE) >> CAN_IE_BEUE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_BEUE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_BEUE;
	tmp |= value << CAN_IE_BEUE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_BEUE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_BEUE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_BEUE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_BEUE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_ELOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_ELOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_ELOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_ELOE) >> CAN_IE_ELOE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_ELOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_ELOE;
	tmp |= value << CAN_IE_ELOE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_ELOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_ELOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_ELOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_ELOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_EPE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_EPE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_EPE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_EPE) >> CAN_IE_EPE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_EPE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_EPE;
	tmp |= value << CAN_IE_EPE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_EPE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_EPE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_EPE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_EPE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_EWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_EWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_EWE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_EWE) >> CAN_IE_EWE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_EWE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_EWE;
	tmp |= value << CAN_IE_EWE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_EWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_EWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_EWE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_EWE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_BOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_BOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_BOE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_BOE) >> CAN_IE_BOE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_BOE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_BOE;
	tmp |= value << CAN_IE_BOE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_BOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_BOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_BOE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_BOE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_WDIE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_WDIE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_WDIE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_WDIE) >> CAN_IE_WDIE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_WDIE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_WDIE;
	tmp |= value << CAN_IE_WDIE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_WDIE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_WDIE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_WDIE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_WDIE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_PEAE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_PEAE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_PEAE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_PEAE) >> CAN_IE_PEAE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_PEAE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_PEAE;
	tmp |= value << CAN_IE_PEAE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_PEAE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_PEAE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_PEAE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_PEAE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_PEDE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_PEDE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_PEDE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_PEDE) >> CAN_IE_PEDE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_PEDE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_PEDE;
	tmp |= value << CAN_IE_PEDE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_PEDE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_PEDE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_PEDE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_PEDE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_ARAE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= CAN_IE_ARAE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_IE_ARAE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp = (tmp & CAN_IE_ARAE) >> CAN_IE_ARAE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_IE_ARAE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->IE.reg;
	tmp &= ~CAN_IE_ARAE;
	tmp |= value << CAN_IE_ARAE_Pos;
	((Can *)hw)->IE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_ARAE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~CAN_IE_ARAE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_ARAE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= CAN_IE_ARAE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_IE_reg(const void *const hw, hri_can_ie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ie_reg_t hri_can_get_IE_reg(const void *const hw, hri_can_ie_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->IE.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_IE_reg(const void *const hw, hri_can_ie_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_IE_reg(const void *const hw, hri_can_ie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_IE_reg(const void *const hw, hri_can_ie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->IE.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ie_reg_t hri_can_read_IE_reg(const void *const hw)
{
	return ((Can *)hw)->IE.reg;
}

static inline void hri_can_set_ILS_RF0NL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF0NL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF0NL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF0NL) >> CAN_ILS_RF0NL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF0NL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF0NL;
	tmp |= value << CAN_ILS_RF0NL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF0NL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF0NL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF0NL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF0NL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_RF0WL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF0WL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF0WL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF0WL) >> CAN_ILS_RF0WL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF0WL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF0WL;
	tmp |= value << CAN_ILS_RF0WL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF0WL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF0WL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF0WL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF0WL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_RF0FL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF0FL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF0FL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF0FL) >> CAN_ILS_RF0FL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF0FL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF0FL;
	tmp |= value << CAN_ILS_RF0FL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF0FL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF0FL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF0FL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF0FL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_RF0LL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF0LL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF0LL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF0LL) >> CAN_ILS_RF0LL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF0LL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF0LL;
	tmp |= value << CAN_ILS_RF0LL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF0LL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF0LL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF0LL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF0LL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_RF1NL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF1NL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF1NL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF1NL) >> CAN_ILS_RF1NL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF1NL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF1NL;
	tmp |= value << CAN_ILS_RF1NL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF1NL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF1NL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF1NL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF1NL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_RF1WL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF1WL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF1WL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF1WL) >> CAN_ILS_RF1WL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF1WL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF1WL;
	tmp |= value << CAN_ILS_RF1WL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF1WL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF1WL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF1WL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF1WL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_RF1FL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF1FL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF1FL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF1FL) >> CAN_ILS_RF1FL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF1FL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF1FL;
	tmp |= value << CAN_ILS_RF1FL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF1FL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF1FL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF1FL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF1FL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_RF1LL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_RF1LL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_RF1LL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_RF1LL) >> CAN_ILS_RF1LL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_RF1LL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_RF1LL;
	tmp |= value << CAN_ILS_RF1LL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_RF1LL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_RF1LL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_RF1LL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_RF1LL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_HPML_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_HPML;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_HPML_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_HPML) >> CAN_ILS_HPML_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_HPML_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_HPML;
	tmp |= value << CAN_ILS_HPML_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_HPML_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_HPML;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_HPML_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_HPML;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TCL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TCL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TCL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TCL) >> CAN_ILS_TCL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TCL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TCL;
	tmp |= value << CAN_ILS_TCL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TCL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TCL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TCL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TCL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TCFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TCFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TCFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TCFL) >> CAN_ILS_TCFL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TCFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TCFL;
	tmp |= value << CAN_ILS_TCFL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TCFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TCFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TCFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TCFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TFEL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TFEL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TFEL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TFEL) >> CAN_ILS_TFEL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TFEL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TFEL;
	tmp |= value << CAN_ILS_TFEL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TFEL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TFEL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TFEL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TFEL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TEFNL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TEFNL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TEFNL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TEFNL) >> CAN_ILS_TEFNL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TEFNL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TEFNL;
	tmp |= value << CAN_ILS_TEFNL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TEFNL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TEFNL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TEFNL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TEFNL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TEFWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TEFWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TEFWL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TEFWL) >> CAN_ILS_TEFWL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TEFWL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TEFWL;
	tmp |= value << CAN_ILS_TEFWL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TEFWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TEFWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TEFWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TEFWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TEFFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TEFFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TEFFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TEFFL) >> CAN_ILS_TEFFL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TEFFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TEFFL;
	tmp |= value << CAN_ILS_TEFFL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TEFFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TEFFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TEFFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TEFFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TEFLL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TEFLL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TEFLL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TEFLL) >> CAN_ILS_TEFLL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TEFLL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TEFLL;
	tmp |= value << CAN_ILS_TEFLL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TEFLL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TEFLL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TEFLL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TEFLL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TSWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TSWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TSWL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TSWL) >> CAN_ILS_TSWL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TSWL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TSWL;
	tmp |= value << CAN_ILS_TSWL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TSWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TSWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TSWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TSWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_MRAFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_MRAFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_MRAFL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_MRAFL) >> CAN_ILS_MRAFL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_MRAFL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_MRAFL;
	tmp |= value << CAN_ILS_MRAFL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_MRAFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_MRAFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_MRAFL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_MRAFL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_TOOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_TOOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_TOOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_TOOL) >> CAN_ILS_TOOL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_TOOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_TOOL;
	tmp |= value << CAN_ILS_TOOL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_TOOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_TOOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_TOOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_TOOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_DRXL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_DRXL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_DRXL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_DRXL) >> CAN_ILS_DRXL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_DRXL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_DRXL;
	tmp |= value << CAN_ILS_DRXL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_DRXL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_DRXL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_DRXL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_DRXL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_BECL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_BECL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_BECL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_BECL) >> CAN_ILS_BECL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_BECL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_BECL;
	tmp |= value << CAN_ILS_BECL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_BECL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_BECL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_BECL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_BECL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_BEUL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_BEUL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_BEUL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_BEUL) >> CAN_ILS_BEUL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_BEUL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_BEUL;
	tmp |= value << CAN_ILS_BEUL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_BEUL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_BEUL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_BEUL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_BEUL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_ELOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_ELOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_ELOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_ELOL) >> CAN_ILS_ELOL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_ELOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_ELOL;
	tmp |= value << CAN_ILS_ELOL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_ELOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_ELOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_ELOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_ELOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_EPL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_EPL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_EPL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_EPL) >> CAN_ILS_EPL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_EPL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_EPL;
	tmp |= value << CAN_ILS_EPL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_EPL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_EPL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_EPL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_EPL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_EWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_EWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_EWL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_EWL) >> CAN_ILS_EWL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_EWL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_EWL;
	tmp |= value << CAN_ILS_EWL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_EWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_EWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_EWL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_EWL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_BOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_BOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_BOL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_BOL) >> CAN_ILS_BOL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_BOL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_BOL;
	tmp |= value << CAN_ILS_BOL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_BOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_BOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_BOL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_BOL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_WDIL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_WDIL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_WDIL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_WDIL) >> CAN_ILS_WDIL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_WDIL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_WDIL;
	tmp |= value << CAN_ILS_WDIL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_WDIL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_WDIL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_WDIL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_WDIL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_PEAL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_PEAL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_PEAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_PEAL) >> CAN_ILS_PEAL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_PEAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_PEAL;
	tmp |= value << CAN_ILS_PEAL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_PEAL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_PEAL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_PEAL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_PEAL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_PEDL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_PEDL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_PEDL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_PEDL) >> CAN_ILS_PEDL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_PEDL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_PEDL;
	tmp |= value << CAN_ILS_PEDL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_PEDL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_PEDL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_PEDL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_PEDL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_ARAL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= CAN_ILS_ARAL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILS_ARAL_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp = (tmp & CAN_ILS_ARAL) >> CAN_ILS_ARAL_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILS_ARAL_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= ~CAN_ILS_ARAL;
	tmp |= value << CAN_ILS_ARAL_Pos;
	((Can *)hw)->ILS.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_ARAL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~CAN_ILS_ARAL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_ARAL_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= CAN_ILS_ARAL;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILS_reg(const void *const hw, hri_can_ils_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ils_reg_t hri_can_get_ILS_reg(const void *const hw, hri_can_ils_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILS.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_ILS_reg(const void *const hw, hri_can_ils_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILS_reg(const void *const hw, hri_can_ils_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILS_reg(const void *const hw, hri_can_ils_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILS.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ils_reg_t hri_can_read_ILS_reg(const void *const hw)
{
	return ((Can *)hw)->ILS.reg;
}

static inline void hri_can_set_ILE_EINT0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg |= CAN_ILE_EINT0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILE_EINT0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILE.reg;
	tmp = (tmp & CAN_ILE_EINT0) >> CAN_ILE_EINT0_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILE_EINT0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILE.reg;
	tmp &= ~CAN_ILE_EINT0;
	tmp |= value << CAN_ILE_EINT0_Pos;
	((Can *)hw)->ILE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILE_EINT0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg &= ~CAN_ILE_EINT0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILE_EINT0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg ^= CAN_ILE_EINT0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILE_EINT1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg |= CAN_ILE_EINT1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_ILE_EINT1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILE.reg;
	tmp = (tmp & CAN_ILE_EINT1) >> CAN_ILE_EINT1_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_ILE_EINT1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->ILE.reg;
	tmp &= ~CAN_ILE_EINT1;
	tmp |= value << CAN_ILE_EINT1_Pos;
	((Can *)hw)->ILE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILE_EINT1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg &= ~CAN_ILE_EINT1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILE_EINT1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg ^= CAN_ILE_EINT1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_ILE_reg(const void *const hw, hri_can_ile_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ile_reg_t hri_can_get_ILE_reg(const void *const hw, hri_can_ile_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->ILE.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_ILE_reg(const void *const hw, hri_can_ile_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_ILE_reg(const void *const hw, hri_can_ile_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_ILE_reg(const void *const hw, hri_can_ile_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->ILE.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ile_reg_t hri_can_read_ILE_reg(const void *const hw)
{
	return ((Can *)hw)->ILE.reg;
}

static inline void hri_can_set_GFC_RRFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg |= CAN_GFC_RRFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_GFC_RRFE_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->GFC.reg;
	tmp = (tmp & CAN_GFC_RRFE) >> CAN_GFC_RRFE_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_GFC_RRFE_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->GFC.reg;
	tmp &= ~CAN_GFC_RRFE;
	tmp |= value << CAN_GFC_RRFE_Pos;
	((Can *)hw)->GFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_GFC_RRFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg &= ~CAN_GFC_RRFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_GFC_RRFE_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg ^= CAN_GFC_RRFE;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_GFC_RRFS_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg |= CAN_GFC_RRFS;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_GFC_RRFS_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->GFC.reg;
	tmp = (tmp & CAN_GFC_RRFS) >> CAN_GFC_RRFS_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_GFC_RRFS_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->GFC.reg;
	tmp &= ~CAN_GFC_RRFS;
	tmp |= value << CAN_GFC_RRFS_Pos;
	((Can *)hw)->GFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_GFC_RRFS_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg &= ~CAN_GFC_RRFS;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_GFC_RRFS_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg ^= CAN_GFC_RRFS;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_GFC_ANFE_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg |= CAN_GFC_ANFE(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_gfc_reg_t hri_can_get_GFC_ANFE_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->GFC.reg;
	tmp = (tmp & CAN_GFC_ANFE(mask)) >> CAN_GFC_ANFE_Pos;
	return tmp;
}

static inline void hri_can_write_GFC_ANFE_bf(const void *const hw, hri_can_gfc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->GFC.reg;
	tmp &= ~CAN_GFC_ANFE_Msk;
	tmp |= CAN_GFC_ANFE(data);
	((Can *)hw)->GFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_GFC_ANFE_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg &= ~CAN_GFC_ANFE(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_GFC_ANFE_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg ^= CAN_GFC_ANFE(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_gfc_reg_t hri_can_read_GFC_ANFE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->GFC.reg;
	tmp = (tmp & CAN_GFC_ANFE_Msk) >> CAN_GFC_ANFE_Pos;
	return tmp;
}

static inline void hri_can_set_GFC_ANFS_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg |= CAN_GFC_ANFS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_gfc_reg_t hri_can_get_GFC_ANFS_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->GFC.reg;
	tmp = (tmp & CAN_GFC_ANFS(mask)) >> CAN_GFC_ANFS_Pos;
	return tmp;
}

static inline void hri_can_write_GFC_ANFS_bf(const void *const hw, hri_can_gfc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->GFC.reg;
	tmp &= ~CAN_GFC_ANFS_Msk;
	tmp |= CAN_GFC_ANFS(data);
	((Can *)hw)->GFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_GFC_ANFS_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg &= ~CAN_GFC_ANFS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_GFC_ANFS_bf(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg ^= CAN_GFC_ANFS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_gfc_reg_t hri_can_read_GFC_ANFS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->GFC.reg;
	tmp = (tmp & CAN_GFC_ANFS_Msk) >> CAN_GFC_ANFS_Pos;
	return tmp;
}

static inline void hri_can_set_GFC_reg(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_gfc_reg_t hri_can_get_GFC_reg(const void *const hw, hri_can_gfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->GFC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_GFC_reg(const void *const hw, hri_can_gfc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_GFC_reg(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_GFC_reg(const void *const hw, hri_can_gfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->GFC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_gfc_reg_t hri_can_read_GFC_reg(const void *const hw)
{
	return ((Can *)hw)->GFC.reg;
}

static inline void hri_can_set_SIDFC_FLSSA_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg |= CAN_SIDFC_FLSSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_sidfc_reg_t hri_can_get_SIDFC_FLSSA_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->SIDFC.reg;
	tmp = (tmp & CAN_SIDFC_FLSSA(mask)) >> CAN_SIDFC_FLSSA_Pos;
	return tmp;
}

static inline void hri_can_write_SIDFC_FLSSA_bf(const void *const hw, hri_can_sidfc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->SIDFC.reg;
	tmp &= ~CAN_SIDFC_FLSSA_Msk;
	tmp |= CAN_SIDFC_FLSSA(data);
	((Can *)hw)->SIDFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_SIDFC_FLSSA_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg &= ~CAN_SIDFC_FLSSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_SIDFC_FLSSA_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg ^= CAN_SIDFC_FLSSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_sidfc_reg_t hri_can_read_SIDFC_FLSSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->SIDFC.reg;
	tmp = (tmp & CAN_SIDFC_FLSSA_Msk) >> CAN_SIDFC_FLSSA_Pos;
	return tmp;
}

static inline void hri_can_set_SIDFC_LSS_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg |= CAN_SIDFC_LSS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_sidfc_reg_t hri_can_get_SIDFC_LSS_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->SIDFC.reg;
	tmp = (tmp & CAN_SIDFC_LSS(mask)) >> CAN_SIDFC_LSS_Pos;
	return tmp;
}

static inline void hri_can_write_SIDFC_LSS_bf(const void *const hw, hri_can_sidfc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->SIDFC.reg;
	tmp &= ~CAN_SIDFC_LSS_Msk;
	tmp |= CAN_SIDFC_LSS(data);
	((Can *)hw)->SIDFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_SIDFC_LSS_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg &= ~CAN_SIDFC_LSS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_SIDFC_LSS_bf(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg ^= CAN_SIDFC_LSS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_sidfc_reg_t hri_can_read_SIDFC_LSS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->SIDFC.reg;
	tmp = (tmp & CAN_SIDFC_LSS_Msk) >> CAN_SIDFC_LSS_Pos;
	return tmp;
}

static inline void hri_can_set_SIDFC_reg(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_sidfc_reg_t hri_can_get_SIDFC_reg(const void *const hw, hri_can_sidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->SIDFC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_SIDFC_reg(const void *const hw, hri_can_sidfc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_SIDFC_reg(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_SIDFC_reg(const void *const hw, hri_can_sidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->SIDFC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_sidfc_reg_t hri_can_read_SIDFC_reg(const void *const hw)
{
	return ((Can *)hw)->SIDFC.reg;
}

static inline void hri_can_set_XIDFC_FLESA_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg |= CAN_XIDFC_FLESA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidfc_reg_t hri_can_get_XIDFC_FLESA_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDFC.reg;
	tmp = (tmp & CAN_XIDFC_FLESA(mask)) >> CAN_XIDFC_FLESA_Pos;
	return tmp;
}

static inline void hri_can_write_XIDFC_FLESA_bf(const void *const hw, hri_can_xidfc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->XIDFC.reg;
	tmp &= ~CAN_XIDFC_FLESA_Msk;
	tmp |= CAN_XIDFC_FLESA(data);
	((Can *)hw)->XIDFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_XIDFC_FLESA_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg &= ~CAN_XIDFC_FLESA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_XIDFC_FLESA_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg ^= CAN_XIDFC_FLESA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidfc_reg_t hri_can_read_XIDFC_FLESA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDFC.reg;
	tmp = (tmp & CAN_XIDFC_FLESA_Msk) >> CAN_XIDFC_FLESA_Pos;
	return tmp;
}

static inline void hri_can_set_XIDFC_LSE_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg |= CAN_XIDFC_LSE(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidfc_reg_t hri_can_get_XIDFC_LSE_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDFC.reg;
	tmp = (tmp & CAN_XIDFC_LSE(mask)) >> CAN_XIDFC_LSE_Pos;
	return tmp;
}

static inline void hri_can_write_XIDFC_LSE_bf(const void *const hw, hri_can_xidfc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->XIDFC.reg;
	tmp &= ~CAN_XIDFC_LSE_Msk;
	tmp |= CAN_XIDFC_LSE(data);
	((Can *)hw)->XIDFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_XIDFC_LSE_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg &= ~CAN_XIDFC_LSE(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_XIDFC_LSE_bf(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg ^= CAN_XIDFC_LSE(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidfc_reg_t hri_can_read_XIDFC_LSE_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDFC.reg;
	tmp = (tmp & CAN_XIDFC_LSE_Msk) >> CAN_XIDFC_LSE_Pos;
	return tmp;
}

static inline void hri_can_set_XIDFC_reg(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidfc_reg_t hri_can_get_XIDFC_reg(const void *const hw, hri_can_xidfc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDFC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_XIDFC_reg(const void *const hw, hri_can_xidfc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_XIDFC_reg(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_XIDFC_reg(const void *const hw, hri_can_xidfc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDFC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidfc_reg_t hri_can_read_XIDFC_reg(const void *const hw)
{
	return ((Can *)hw)->XIDFC.reg;
}

static inline void hri_can_set_XIDAM_EIDM_bf(const void *const hw, hri_can_xidam_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDAM.reg |= CAN_XIDAM_EIDM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidam_reg_t hri_can_get_XIDAM_EIDM_bf(const void *const hw, hri_can_xidam_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDAM.reg;
	tmp = (tmp & CAN_XIDAM_EIDM(mask)) >> CAN_XIDAM_EIDM_Pos;
	return tmp;
}

static inline void hri_can_write_XIDAM_EIDM_bf(const void *const hw, hri_can_xidam_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->XIDAM.reg;
	tmp &= ~CAN_XIDAM_EIDM_Msk;
	tmp |= CAN_XIDAM_EIDM(data);
	((Can *)hw)->XIDAM.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_XIDAM_EIDM_bf(const void *const hw, hri_can_xidam_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDAM.reg &= ~CAN_XIDAM_EIDM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_XIDAM_EIDM_bf(const void *const hw, hri_can_xidam_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDAM.reg ^= CAN_XIDAM_EIDM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidam_reg_t hri_can_read_XIDAM_EIDM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDAM.reg;
	tmp = (tmp & CAN_XIDAM_EIDM_Msk) >> CAN_XIDAM_EIDM_Pos;
	return tmp;
}

static inline void hri_can_set_XIDAM_reg(const void *const hw, hri_can_xidam_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDAM.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidam_reg_t hri_can_get_XIDAM_reg(const void *const hw, hri_can_xidam_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->XIDAM.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_XIDAM_reg(const void *const hw, hri_can_xidam_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDAM.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_XIDAM_reg(const void *const hw, hri_can_xidam_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDAM.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_XIDAM_reg(const void *const hw, hri_can_xidam_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->XIDAM.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_xidam_reg_t hri_can_read_XIDAM_reg(const void *const hw)
{
	return ((Can *)hw)->XIDAM.reg;
}

static inline void hri_can_set_NDAT1_ND0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND0) >> CAN_NDAT1_ND0_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND0;
	tmp |= value << CAN_NDAT1_ND0_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND1) >> CAN_NDAT1_ND1_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND1;
	tmp |= value << CAN_NDAT1_ND1_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND2) >> CAN_NDAT1_ND2_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND2;
	tmp |= value << CAN_NDAT1_ND2_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND3) >> CAN_NDAT1_ND3_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND3;
	tmp |= value << CAN_NDAT1_ND3_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND4) >> CAN_NDAT1_ND4_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND4;
	tmp |= value << CAN_NDAT1_ND4_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND5) >> CAN_NDAT1_ND5_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND5;
	tmp |= value << CAN_NDAT1_ND5_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND6) >> CAN_NDAT1_ND6_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND6;
	tmp |= value << CAN_NDAT1_ND6_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND7) >> CAN_NDAT1_ND7_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND7;
	tmp |= value << CAN_NDAT1_ND7_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND8) >> CAN_NDAT1_ND8_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND8;
	tmp |= value << CAN_NDAT1_ND8_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND9) >> CAN_NDAT1_ND9_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND9;
	tmp |= value << CAN_NDAT1_ND9_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND10) >> CAN_NDAT1_ND10_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND10;
	tmp |= value << CAN_NDAT1_ND10_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND11) >> CAN_NDAT1_ND11_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND11;
	tmp |= value << CAN_NDAT1_ND11_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND12) >> CAN_NDAT1_ND12_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND12;
	tmp |= value << CAN_NDAT1_ND12_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND13) >> CAN_NDAT1_ND13_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND13;
	tmp |= value << CAN_NDAT1_ND13_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND14) >> CAN_NDAT1_ND14_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND14;
	tmp |= value << CAN_NDAT1_ND14_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND15) >> CAN_NDAT1_ND15_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND15;
	tmp |= value << CAN_NDAT1_ND15_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND16) >> CAN_NDAT1_ND16_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND16;
	tmp |= value << CAN_NDAT1_ND16_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND17) >> CAN_NDAT1_ND17_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND17;
	tmp |= value << CAN_NDAT1_ND17_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND18) >> CAN_NDAT1_ND18_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND18;
	tmp |= value << CAN_NDAT1_ND18_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND19) >> CAN_NDAT1_ND19_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND19;
	tmp |= value << CAN_NDAT1_ND19_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND20) >> CAN_NDAT1_ND20_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND20;
	tmp |= value << CAN_NDAT1_ND20_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND21) >> CAN_NDAT1_ND21_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND21;
	tmp |= value << CAN_NDAT1_ND21_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND22) >> CAN_NDAT1_ND22_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND22;
	tmp |= value << CAN_NDAT1_ND22_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND23) >> CAN_NDAT1_ND23_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND23;
	tmp |= value << CAN_NDAT1_ND23_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND24) >> CAN_NDAT1_ND24_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND24;
	tmp |= value << CAN_NDAT1_ND24_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND25) >> CAN_NDAT1_ND25_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND25;
	tmp |= value << CAN_NDAT1_ND25_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND26) >> CAN_NDAT1_ND26_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND26;
	tmp |= value << CAN_NDAT1_ND26_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND27) >> CAN_NDAT1_ND27_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND27;
	tmp |= value << CAN_NDAT1_ND27_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND28) >> CAN_NDAT1_ND28_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND28;
	tmp |= value << CAN_NDAT1_ND28_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND29) >> CAN_NDAT1_ND29_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND29;
	tmp |= value << CAN_NDAT1_ND29_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND30) >> CAN_NDAT1_ND30_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND30;
	tmp |= value << CAN_NDAT1_ND30_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_ND31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= CAN_NDAT1_ND31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT1_ND31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp = (tmp & CAN_NDAT1_ND31) >> CAN_NDAT1_ND31_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT1_ND31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= ~CAN_NDAT1_ND31;
	tmp |= value << CAN_NDAT1_ND31_Pos;
	((Can *)hw)->NDAT1.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_ND31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~CAN_NDAT1_ND31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_ND31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= CAN_NDAT1_ND31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT1_reg(const void *const hw, hri_can_ndat1_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ndat1_reg_t hri_can_get_NDAT1_reg(const void *const hw, hri_can_ndat1_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT1.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_NDAT1_reg(const void *const hw, hri_can_ndat1_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT1_reg(const void *const hw, hri_can_ndat1_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT1_reg(const void *const hw, hri_can_ndat1_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT1.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ndat1_reg_t hri_can_read_NDAT1_reg(const void *const hw)
{
	return ((Can *)hw)->NDAT1.reg;
}

static inline void hri_can_set_NDAT2_ND32_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND32;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND32_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND32) >> CAN_NDAT2_ND32_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND32_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND32;
	tmp |= value << CAN_NDAT2_ND32_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND32_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND32;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND32_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND32;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND33_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND33;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND33_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND33) >> CAN_NDAT2_ND33_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND33_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND33;
	tmp |= value << CAN_NDAT2_ND33_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND33_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND33;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND33_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND33;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND34_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND34;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND34_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND34) >> CAN_NDAT2_ND34_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND34_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND34;
	tmp |= value << CAN_NDAT2_ND34_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND34_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND34;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND34_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND34;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND35_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND35;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND35_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND35) >> CAN_NDAT2_ND35_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND35_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND35;
	tmp |= value << CAN_NDAT2_ND35_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND35_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND35;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND35_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND35;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND36_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND36;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND36_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND36) >> CAN_NDAT2_ND36_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND36_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND36;
	tmp |= value << CAN_NDAT2_ND36_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND36_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND36;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND36_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND36;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND37_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND37;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND37_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND37) >> CAN_NDAT2_ND37_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND37_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND37;
	tmp |= value << CAN_NDAT2_ND37_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND37_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND37;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND37_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND37;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND38_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND38;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND38_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND38) >> CAN_NDAT2_ND38_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND38_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND38;
	tmp |= value << CAN_NDAT2_ND38_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND38_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND38;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND38_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND38;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND39_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND39;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND39_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND39) >> CAN_NDAT2_ND39_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND39_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND39;
	tmp |= value << CAN_NDAT2_ND39_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND39_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND39;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND39_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND39;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND40_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND40;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND40_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND40) >> CAN_NDAT2_ND40_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND40_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND40;
	tmp |= value << CAN_NDAT2_ND40_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND40_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND40;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND40_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND40;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND41_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND41;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND41_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND41) >> CAN_NDAT2_ND41_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND41_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND41;
	tmp |= value << CAN_NDAT2_ND41_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND41_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND41;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND41_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND41;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND42_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND42;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND42_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND42) >> CAN_NDAT2_ND42_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND42_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND42;
	tmp |= value << CAN_NDAT2_ND42_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND42_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND42;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND42_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND42;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND43_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND43;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND43_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND43) >> CAN_NDAT2_ND43_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND43_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND43;
	tmp |= value << CAN_NDAT2_ND43_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND43_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND43;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND43_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND43;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND44_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND44;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND44_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND44) >> CAN_NDAT2_ND44_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND44_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND44;
	tmp |= value << CAN_NDAT2_ND44_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND44_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND44;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND44_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND44;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND45_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND45;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND45_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND45) >> CAN_NDAT2_ND45_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND45_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND45;
	tmp |= value << CAN_NDAT2_ND45_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND45_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND45;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND45_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND45;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND46_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND46;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND46_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND46) >> CAN_NDAT2_ND46_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND46_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND46;
	tmp |= value << CAN_NDAT2_ND46_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND46_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND46;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND46_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND46;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND47_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND47;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND47_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND47) >> CAN_NDAT2_ND47_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND47_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND47;
	tmp |= value << CAN_NDAT2_ND47_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND47_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND47;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND47_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND47;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND48_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND48;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND48_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND48) >> CAN_NDAT2_ND48_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND48_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND48;
	tmp |= value << CAN_NDAT2_ND48_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND48_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND48;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND48_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND48;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND49_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND49;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND49_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND49) >> CAN_NDAT2_ND49_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND49_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND49;
	tmp |= value << CAN_NDAT2_ND49_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND49_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND49;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND49_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND49;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND50_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND50;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND50_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND50) >> CAN_NDAT2_ND50_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND50_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND50;
	tmp |= value << CAN_NDAT2_ND50_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND50_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND50;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND50_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND50;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND51_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND51;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND51_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND51) >> CAN_NDAT2_ND51_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND51_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND51;
	tmp |= value << CAN_NDAT2_ND51_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND51_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND51;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND51_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND51;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND52_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND52;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND52_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND52) >> CAN_NDAT2_ND52_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND52_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND52;
	tmp |= value << CAN_NDAT2_ND52_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND52_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND52;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND52_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND52;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND53_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND53;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND53_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND53) >> CAN_NDAT2_ND53_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND53_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND53;
	tmp |= value << CAN_NDAT2_ND53_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND53_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND53;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND53_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND53;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND54_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND54;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND54_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND54) >> CAN_NDAT2_ND54_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND54_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND54;
	tmp |= value << CAN_NDAT2_ND54_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND54_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND54;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND54_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND54;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND55_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND55;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND55_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND55) >> CAN_NDAT2_ND55_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND55_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND55;
	tmp |= value << CAN_NDAT2_ND55_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND55_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND55;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND55_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND55;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND56_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND56;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND56_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND56) >> CAN_NDAT2_ND56_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND56_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND56;
	tmp |= value << CAN_NDAT2_ND56_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND56_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND56;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND56_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND56;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND57_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND57;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND57_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND57) >> CAN_NDAT2_ND57_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND57_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND57;
	tmp |= value << CAN_NDAT2_ND57_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND57_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND57;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND57_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND57;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND58_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND58;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND58_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND58) >> CAN_NDAT2_ND58_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND58_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND58;
	tmp |= value << CAN_NDAT2_ND58_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND58_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND58;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND58_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND58;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND59_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND59;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND59_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND59) >> CAN_NDAT2_ND59_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND59_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND59;
	tmp |= value << CAN_NDAT2_ND59_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND59_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND59;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND59_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND59;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND60_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND60;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND60_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND60) >> CAN_NDAT2_ND60_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND60_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND60;
	tmp |= value << CAN_NDAT2_ND60_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND60_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND60;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND60_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND60;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND61_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND61;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND61_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND61) >> CAN_NDAT2_ND61_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND61_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND61;
	tmp |= value << CAN_NDAT2_ND61_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND61_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND61;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND61_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND61;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND62_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND62;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND62_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND62) >> CAN_NDAT2_ND62_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND62_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND62;
	tmp |= value << CAN_NDAT2_ND62_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND62_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND62;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND62_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND62;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_ND63_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= CAN_NDAT2_ND63;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_NDAT2_ND63_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp = (tmp & CAN_NDAT2_ND63) >> CAN_NDAT2_ND63_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_NDAT2_ND63_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= ~CAN_NDAT2_ND63;
	tmp |= value << CAN_NDAT2_ND63_Pos;
	((Can *)hw)->NDAT2.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_ND63_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~CAN_NDAT2_ND63;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_ND63_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= CAN_NDAT2_ND63;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_NDAT2_reg(const void *const hw, hri_can_ndat2_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ndat2_reg_t hri_can_get_NDAT2_reg(const void *const hw, hri_can_ndat2_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->NDAT2.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_NDAT2_reg(const void *const hw, hri_can_ndat2_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_NDAT2_reg(const void *const hw, hri_can_ndat2_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_NDAT2_reg(const void *const hw, hri_can_ndat2_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->NDAT2.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_ndat2_reg_t hri_can_read_NDAT2_reg(const void *const hw)
{
	return ((Can *)hw)->NDAT2.reg;
}

static inline void hri_can_set_RXF0C_F0OM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg |= CAN_RXF0C_F0OM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_RXF0C_F0OM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp = (tmp & CAN_RXF0C_F0OM) >> CAN_RXF0C_F0OM_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_RXF0C_F0OM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp &= ~CAN_RXF0C_F0OM;
	tmp |= value << CAN_RXF0C_F0OM_Pos;
	((Can *)hw)->RXF0C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF0C_F0OM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg &= ~CAN_RXF0C_F0OM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF0C_F0OM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg ^= CAN_RXF0C_F0OM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_RXF0C_F0SA_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg |= CAN_RXF0C_F0SA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_get_RXF0C_F0SA_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp = (tmp & CAN_RXF0C_F0SA(mask)) >> CAN_RXF0C_F0SA_Pos;
	return tmp;
}

static inline void hri_can_write_RXF0C_F0SA_bf(const void *const hw, hri_can_rxf0c_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp &= ~CAN_RXF0C_F0SA_Msk;
	tmp |= CAN_RXF0C_F0SA(data);
	((Can *)hw)->RXF0C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF0C_F0SA_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg &= ~CAN_RXF0C_F0SA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF0C_F0SA_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg ^= CAN_RXF0C_F0SA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_read_RXF0C_F0SA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp = (tmp & CAN_RXF0C_F0SA_Msk) >> CAN_RXF0C_F0SA_Pos;
	return tmp;
}

static inline void hri_can_set_RXF0C_F0S_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg |= CAN_RXF0C_F0S(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_get_RXF0C_F0S_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp = (tmp & CAN_RXF0C_F0S(mask)) >> CAN_RXF0C_F0S_Pos;
	return tmp;
}

static inline void hri_can_write_RXF0C_F0S_bf(const void *const hw, hri_can_rxf0c_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp &= ~CAN_RXF0C_F0S_Msk;
	tmp |= CAN_RXF0C_F0S(data);
	((Can *)hw)->RXF0C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF0C_F0S_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg &= ~CAN_RXF0C_F0S(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF0C_F0S_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg ^= CAN_RXF0C_F0S(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_read_RXF0C_F0S_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp = (tmp & CAN_RXF0C_F0S_Msk) >> CAN_RXF0C_F0S_Pos;
	return tmp;
}

static inline void hri_can_set_RXF0C_F0WM_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg |= CAN_RXF0C_F0WM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_get_RXF0C_F0WM_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp = (tmp & CAN_RXF0C_F0WM(mask)) >> CAN_RXF0C_F0WM_Pos;
	return tmp;
}

static inline void hri_can_write_RXF0C_F0WM_bf(const void *const hw, hri_can_rxf0c_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp &= ~CAN_RXF0C_F0WM_Msk;
	tmp |= CAN_RXF0C_F0WM(data);
	((Can *)hw)->RXF0C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF0C_F0WM_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg &= ~CAN_RXF0C_F0WM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF0C_F0WM_bf(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg ^= CAN_RXF0C_F0WM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_read_RXF0C_F0WM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp = (tmp & CAN_RXF0C_F0WM_Msk) >> CAN_RXF0C_F0WM_Pos;
	return tmp;
}

static inline void hri_can_set_RXF0C_reg(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_get_RXF0C_reg(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0C.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_RXF0C_reg(const void *const hw, hri_can_rxf0c_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF0C_reg(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF0C_reg(const void *const hw, hri_can_rxf0c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0C.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0c_reg_t hri_can_read_RXF0C_reg(const void *const hw)
{
	return ((Can *)hw)->RXF0C.reg;
}

static inline void hri_can_set_RXF0A_F0AI_bf(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0A.reg |= CAN_RXF0A_F0AI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0a_reg_t hri_can_get_RXF0A_F0AI_bf(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0A.reg;
	tmp = (tmp & CAN_RXF0A_F0AI(mask)) >> CAN_RXF0A_F0AI_Pos;
	return tmp;
}

static inline void hri_can_write_RXF0A_F0AI_bf(const void *const hw, hri_can_rxf0a_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF0A.reg;
	tmp &= ~CAN_RXF0A_F0AI_Msk;
	tmp |= CAN_RXF0A_F0AI(data);
	((Can *)hw)->RXF0A.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF0A_F0AI_bf(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0A.reg &= ~CAN_RXF0A_F0AI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF0A_F0AI_bf(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0A.reg ^= CAN_RXF0A_F0AI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0a_reg_t hri_can_read_RXF0A_F0AI_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0A.reg;
	tmp = (tmp & CAN_RXF0A_F0AI_Msk) >> CAN_RXF0A_F0AI_Pos;
	return tmp;
}

static inline void hri_can_set_RXF0A_reg(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0A.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0a_reg_t hri_can_get_RXF0A_reg(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF0A.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_RXF0A_reg(const void *const hw, hri_can_rxf0a_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0A.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF0A_reg(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0A.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF0A_reg(const void *const hw, hri_can_rxf0a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF0A.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf0a_reg_t hri_can_read_RXF0A_reg(const void *const hw)
{
	return ((Can *)hw)->RXF0A.reg;
}

static inline void hri_can_set_RXBC_RBSA_bf(const void *const hw, hri_can_rxbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXBC.reg |= CAN_RXBC_RBSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxbc_reg_t hri_can_get_RXBC_RBSA_bf(const void *const hw, hri_can_rxbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXBC.reg;
	tmp = (tmp & CAN_RXBC_RBSA(mask)) >> CAN_RXBC_RBSA_Pos;
	return tmp;
}

static inline void hri_can_write_RXBC_RBSA_bf(const void *const hw, hri_can_rxbc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXBC.reg;
	tmp &= ~CAN_RXBC_RBSA_Msk;
	tmp |= CAN_RXBC_RBSA(data);
	((Can *)hw)->RXBC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXBC_RBSA_bf(const void *const hw, hri_can_rxbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXBC.reg &= ~CAN_RXBC_RBSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXBC_RBSA_bf(const void *const hw, hri_can_rxbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXBC.reg ^= CAN_RXBC_RBSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxbc_reg_t hri_can_read_RXBC_RBSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXBC.reg;
	tmp = (tmp & CAN_RXBC_RBSA_Msk) >> CAN_RXBC_RBSA_Pos;
	return tmp;
}

static inline void hri_can_set_RXBC_reg(const void *const hw, hri_can_rxbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXBC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxbc_reg_t hri_can_get_RXBC_reg(const void *const hw, hri_can_rxbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXBC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_RXBC_reg(const void *const hw, hri_can_rxbc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXBC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXBC_reg(const void *const hw, hri_can_rxbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXBC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXBC_reg(const void *const hw, hri_can_rxbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXBC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxbc_reg_t hri_can_read_RXBC_reg(const void *const hw)
{
	return ((Can *)hw)->RXBC.reg;
}

static inline void hri_can_set_RXF1C_F1OM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg |= CAN_RXF1C_F1OM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_RXF1C_F1OM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp = (tmp & CAN_RXF1C_F1OM) >> CAN_RXF1C_F1OM_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_RXF1C_F1OM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp &= ~CAN_RXF1C_F1OM;
	tmp |= value << CAN_RXF1C_F1OM_Pos;
	((Can *)hw)->RXF1C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF1C_F1OM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg &= ~CAN_RXF1C_F1OM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF1C_F1OM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg ^= CAN_RXF1C_F1OM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_RXF1C_F1SA_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg |= CAN_RXF1C_F1SA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_get_RXF1C_F1SA_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp = (tmp & CAN_RXF1C_F1SA(mask)) >> CAN_RXF1C_F1SA_Pos;
	return tmp;
}

static inline void hri_can_write_RXF1C_F1SA_bf(const void *const hw, hri_can_rxf1c_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp &= ~CAN_RXF1C_F1SA_Msk;
	tmp |= CAN_RXF1C_F1SA(data);
	((Can *)hw)->RXF1C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF1C_F1SA_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg &= ~CAN_RXF1C_F1SA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF1C_F1SA_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg ^= CAN_RXF1C_F1SA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_read_RXF1C_F1SA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp = (tmp & CAN_RXF1C_F1SA_Msk) >> CAN_RXF1C_F1SA_Pos;
	return tmp;
}

static inline void hri_can_set_RXF1C_F1S_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg |= CAN_RXF1C_F1S(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_get_RXF1C_F1S_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp = (tmp & CAN_RXF1C_F1S(mask)) >> CAN_RXF1C_F1S_Pos;
	return tmp;
}

static inline void hri_can_write_RXF1C_F1S_bf(const void *const hw, hri_can_rxf1c_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp &= ~CAN_RXF1C_F1S_Msk;
	tmp |= CAN_RXF1C_F1S(data);
	((Can *)hw)->RXF1C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF1C_F1S_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg &= ~CAN_RXF1C_F1S(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF1C_F1S_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg ^= CAN_RXF1C_F1S(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_read_RXF1C_F1S_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp = (tmp & CAN_RXF1C_F1S_Msk) >> CAN_RXF1C_F1S_Pos;
	return tmp;
}

static inline void hri_can_set_RXF1C_F1WM_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg |= CAN_RXF1C_F1WM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_get_RXF1C_F1WM_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp = (tmp & CAN_RXF1C_F1WM(mask)) >> CAN_RXF1C_F1WM_Pos;
	return tmp;
}

static inline void hri_can_write_RXF1C_F1WM_bf(const void *const hw, hri_can_rxf1c_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp &= ~CAN_RXF1C_F1WM_Msk;
	tmp |= CAN_RXF1C_F1WM(data);
	((Can *)hw)->RXF1C.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF1C_F1WM_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg &= ~CAN_RXF1C_F1WM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF1C_F1WM_bf(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg ^= CAN_RXF1C_F1WM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_read_RXF1C_F1WM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp = (tmp & CAN_RXF1C_F1WM_Msk) >> CAN_RXF1C_F1WM_Pos;
	return tmp;
}

static inline void hri_can_set_RXF1C_reg(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_get_RXF1C_reg(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1C.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_RXF1C_reg(const void *const hw, hri_can_rxf1c_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF1C_reg(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF1C_reg(const void *const hw, hri_can_rxf1c_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1C.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1c_reg_t hri_can_read_RXF1C_reg(const void *const hw)
{
	return ((Can *)hw)->RXF1C.reg;
}

static inline void hri_can_set_RXF1A_F1AI_bf(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1A.reg |= CAN_RXF1A_F1AI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1a_reg_t hri_can_get_RXF1A_F1AI_bf(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1A.reg;
	tmp = (tmp & CAN_RXF1A_F1AI(mask)) >> CAN_RXF1A_F1AI_Pos;
	return tmp;
}

static inline void hri_can_write_RXF1A_F1AI_bf(const void *const hw, hri_can_rxf1a_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXF1A.reg;
	tmp &= ~CAN_RXF1A_F1AI_Msk;
	tmp |= CAN_RXF1A_F1AI(data);
	((Can *)hw)->RXF1A.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF1A_F1AI_bf(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1A.reg &= ~CAN_RXF1A_F1AI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF1A_F1AI_bf(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1A.reg ^= CAN_RXF1A_F1AI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1a_reg_t hri_can_read_RXF1A_F1AI_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1A.reg;
	tmp = (tmp & CAN_RXF1A_F1AI_Msk) >> CAN_RXF1A_F1AI_Pos;
	return tmp;
}

static inline void hri_can_set_RXF1A_reg(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1A.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1a_reg_t hri_can_get_RXF1A_reg(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXF1A.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_RXF1A_reg(const void *const hw, hri_can_rxf1a_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1A.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXF1A_reg(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1A.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXF1A_reg(const void *const hw, hri_can_rxf1a_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXF1A.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxf1a_reg_t hri_can_read_RXF1A_reg(const void *const hw)
{
	return ((Can *)hw)->RXF1A.reg;
}

static inline void hri_can_set_RXESC_F0DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg |= CAN_RXESC_F0DS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_get_RXESC_F0DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXESC.reg;
	tmp = (tmp & CAN_RXESC_F0DS(mask)) >> CAN_RXESC_F0DS_Pos;
	return tmp;
}

static inline void hri_can_write_RXESC_F0DS_bf(const void *const hw, hri_can_rxesc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXESC.reg;
	tmp &= ~CAN_RXESC_F0DS_Msk;
	tmp |= CAN_RXESC_F0DS(data);
	((Can *)hw)->RXESC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXESC_F0DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg &= ~CAN_RXESC_F0DS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXESC_F0DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg ^= CAN_RXESC_F0DS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_read_RXESC_F0DS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXESC.reg;
	tmp = (tmp & CAN_RXESC_F0DS_Msk) >> CAN_RXESC_F0DS_Pos;
	return tmp;
}

static inline void hri_can_set_RXESC_F1DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg |= CAN_RXESC_F1DS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_get_RXESC_F1DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXESC.reg;
	tmp = (tmp & CAN_RXESC_F1DS(mask)) >> CAN_RXESC_F1DS_Pos;
	return tmp;
}

static inline void hri_can_write_RXESC_F1DS_bf(const void *const hw, hri_can_rxesc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXESC.reg;
	tmp &= ~CAN_RXESC_F1DS_Msk;
	tmp |= CAN_RXESC_F1DS(data);
	((Can *)hw)->RXESC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXESC_F1DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg &= ~CAN_RXESC_F1DS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXESC_F1DS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg ^= CAN_RXESC_F1DS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_read_RXESC_F1DS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXESC.reg;
	tmp = (tmp & CAN_RXESC_F1DS_Msk) >> CAN_RXESC_F1DS_Pos;
	return tmp;
}

static inline void hri_can_set_RXESC_RBDS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg |= CAN_RXESC_RBDS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_get_RXESC_RBDS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXESC.reg;
	tmp = (tmp & CAN_RXESC_RBDS(mask)) >> CAN_RXESC_RBDS_Pos;
	return tmp;
}

static inline void hri_can_write_RXESC_RBDS_bf(const void *const hw, hri_can_rxesc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->RXESC.reg;
	tmp &= ~CAN_RXESC_RBDS_Msk;
	tmp |= CAN_RXESC_RBDS(data);
	((Can *)hw)->RXESC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXESC_RBDS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg &= ~CAN_RXESC_RBDS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXESC_RBDS_bf(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg ^= CAN_RXESC_RBDS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_read_RXESC_RBDS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXESC.reg;
	tmp = (tmp & CAN_RXESC_RBDS_Msk) >> CAN_RXESC_RBDS_Pos;
	return tmp;
}

static inline void hri_can_set_RXESC_reg(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_get_RXESC_reg(const void *const hw, hri_can_rxesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->RXESC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_RXESC_reg(const void *const hw, hri_can_rxesc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_RXESC_reg(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_RXESC_reg(const void *const hw, hri_can_rxesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->RXESC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_rxesc_reg_t hri_can_read_RXESC_reg(const void *const hw)
{
	return ((Can *)hw)->RXESC.reg;
}

static inline void hri_can_set_TXBC_TFQM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg |= CAN_TXBC_TFQM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBC_TFQM_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp = (tmp & CAN_TXBC_TFQM) >> CAN_TXBC_TFQM_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBC_TFQM_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBC.reg;
	tmp &= ~CAN_TXBC_TFQM;
	tmp |= value << CAN_TXBC_TFQM_Pos;
	((Can *)hw)->TXBC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBC_TFQM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg &= ~CAN_TXBC_TFQM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBC_TFQM_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg ^= CAN_TXBC_TFQM;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBC_TBSA_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg |= CAN_TXBC_TBSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_get_TXBC_TBSA_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp = (tmp & CAN_TXBC_TBSA(mask)) >> CAN_TXBC_TBSA_Pos;
	return tmp;
}

static inline void hri_can_write_TXBC_TBSA_bf(const void *const hw, hri_can_txbc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBC.reg;
	tmp &= ~CAN_TXBC_TBSA_Msk;
	tmp |= CAN_TXBC_TBSA(data);
	((Can *)hw)->TXBC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBC_TBSA_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg &= ~CAN_TXBC_TBSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBC_TBSA_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg ^= CAN_TXBC_TBSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_read_TXBC_TBSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp = (tmp & CAN_TXBC_TBSA_Msk) >> CAN_TXBC_TBSA_Pos;
	return tmp;
}

static inline void hri_can_set_TXBC_NDTB_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg |= CAN_TXBC_NDTB(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_get_TXBC_NDTB_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp = (tmp & CAN_TXBC_NDTB(mask)) >> CAN_TXBC_NDTB_Pos;
	return tmp;
}

static inline void hri_can_write_TXBC_NDTB_bf(const void *const hw, hri_can_txbc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBC.reg;
	tmp &= ~CAN_TXBC_NDTB_Msk;
	tmp |= CAN_TXBC_NDTB(data);
	((Can *)hw)->TXBC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBC_NDTB_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg &= ~CAN_TXBC_NDTB(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBC_NDTB_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg ^= CAN_TXBC_NDTB(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_read_TXBC_NDTB_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp = (tmp & CAN_TXBC_NDTB_Msk) >> CAN_TXBC_NDTB_Pos;
	return tmp;
}

static inline void hri_can_set_TXBC_TFQS_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg |= CAN_TXBC_TFQS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_get_TXBC_TFQS_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp = (tmp & CAN_TXBC_TFQS(mask)) >> CAN_TXBC_TFQS_Pos;
	return tmp;
}

static inline void hri_can_write_TXBC_TFQS_bf(const void *const hw, hri_can_txbc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBC.reg;
	tmp &= ~CAN_TXBC_TFQS_Msk;
	tmp |= CAN_TXBC_TFQS(data);
	((Can *)hw)->TXBC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBC_TFQS_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg &= ~CAN_TXBC_TFQS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBC_TFQS_bf(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg ^= CAN_TXBC_TFQS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_read_TXBC_TFQS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp = (tmp & CAN_TXBC_TFQS_Msk) >> CAN_TXBC_TFQS_Pos;
	return tmp;
}

static inline void hri_can_set_TXBC_reg(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_get_TXBC_reg(const void *const hw, hri_can_txbc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXBC_reg(const void *const hw, hri_can_txbc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBC_reg(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBC_reg(const void *const hw, hri_can_txbc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbc_reg_t hri_can_read_TXBC_reg(const void *const hw)
{
	return ((Can *)hw)->TXBC.reg;
}

static inline void hri_can_set_TXESC_TBDS_bf(const void *const hw, hri_can_txesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXESC.reg |= CAN_TXESC_TBDS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txesc_reg_t hri_can_get_TXESC_TBDS_bf(const void *const hw, hri_can_txesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXESC.reg;
	tmp = (tmp & CAN_TXESC_TBDS(mask)) >> CAN_TXESC_TBDS_Pos;
	return tmp;
}

static inline void hri_can_write_TXESC_TBDS_bf(const void *const hw, hri_can_txesc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXESC.reg;
	tmp &= ~CAN_TXESC_TBDS_Msk;
	tmp |= CAN_TXESC_TBDS(data);
	((Can *)hw)->TXESC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXESC_TBDS_bf(const void *const hw, hri_can_txesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXESC.reg &= ~CAN_TXESC_TBDS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXESC_TBDS_bf(const void *const hw, hri_can_txesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXESC.reg ^= CAN_TXESC_TBDS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txesc_reg_t hri_can_read_TXESC_TBDS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXESC.reg;
	tmp = (tmp & CAN_TXESC_TBDS_Msk) >> CAN_TXESC_TBDS_Pos;
	return tmp;
}

static inline void hri_can_set_TXESC_reg(const void *const hw, hri_can_txesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXESC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txesc_reg_t hri_can_get_TXESC_reg(const void *const hw, hri_can_txesc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXESC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXESC_reg(const void *const hw, hri_can_txesc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXESC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXESC_reg(const void *const hw, hri_can_txesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXESC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXESC_reg(const void *const hw, hri_can_txesc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXESC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txesc_reg_t hri_can_read_TXESC_reg(const void *const hw)
{
	return ((Can *)hw)->TXESC.reg;
}

static inline void hri_can_set_TXBAR_AR0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR0) >> CAN_TXBAR_AR0_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR0;
	tmp |= value << CAN_TXBAR_AR0_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR1) >> CAN_TXBAR_AR1_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR1;
	tmp |= value << CAN_TXBAR_AR1_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR2) >> CAN_TXBAR_AR2_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR2;
	tmp |= value << CAN_TXBAR_AR2_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR3) >> CAN_TXBAR_AR3_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR3;
	tmp |= value << CAN_TXBAR_AR3_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR4) >> CAN_TXBAR_AR4_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR4;
	tmp |= value << CAN_TXBAR_AR4_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR5) >> CAN_TXBAR_AR5_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR5;
	tmp |= value << CAN_TXBAR_AR5_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR6) >> CAN_TXBAR_AR6_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR6;
	tmp |= value << CAN_TXBAR_AR6_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR7) >> CAN_TXBAR_AR7_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR7;
	tmp |= value << CAN_TXBAR_AR7_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR8) >> CAN_TXBAR_AR8_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR8;
	tmp |= value << CAN_TXBAR_AR8_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR9) >> CAN_TXBAR_AR9_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR9;
	tmp |= value << CAN_TXBAR_AR9_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR10) >> CAN_TXBAR_AR10_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR10;
	tmp |= value << CAN_TXBAR_AR10_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR11) >> CAN_TXBAR_AR11_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR11;
	tmp |= value << CAN_TXBAR_AR11_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR12) >> CAN_TXBAR_AR12_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR12;
	tmp |= value << CAN_TXBAR_AR12_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR13) >> CAN_TXBAR_AR13_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR13;
	tmp |= value << CAN_TXBAR_AR13_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR14) >> CAN_TXBAR_AR14_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR14;
	tmp |= value << CAN_TXBAR_AR14_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR15) >> CAN_TXBAR_AR15_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR15;
	tmp |= value << CAN_TXBAR_AR15_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR16) >> CAN_TXBAR_AR16_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR16;
	tmp |= value << CAN_TXBAR_AR16_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR17) >> CAN_TXBAR_AR17_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR17;
	tmp |= value << CAN_TXBAR_AR17_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR18) >> CAN_TXBAR_AR18_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR18;
	tmp |= value << CAN_TXBAR_AR18_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR19) >> CAN_TXBAR_AR19_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR19;
	tmp |= value << CAN_TXBAR_AR19_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR20) >> CAN_TXBAR_AR20_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR20;
	tmp |= value << CAN_TXBAR_AR20_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR21) >> CAN_TXBAR_AR21_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR21;
	tmp |= value << CAN_TXBAR_AR21_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR22) >> CAN_TXBAR_AR22_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR22;
	tmp |= value << CAN_TXBAR_AR22_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR23) >> CAN_TXBAR_AR23_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR23;
	tmp |= value << CAN_TXBAR_AR23_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR24) >> CAN_TXBAR_AR24_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR24;
	tmp |= value << CAN_TXBAR_AR24_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR25) >> CAN_TXBAR_AR25_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR25;
	tmp |= value << CAN_TXBAR_AR25_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR26) >> CAN_TXBAR_AR26_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR26;
	tmp |= value << CAN_TXBAR_AR26_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR27) >> CAN_TXBAR_AR27_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR27;
	tmp |= value << CAN_TXBAR_AR27_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR28) >> CAN_TXBAR_AR28_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR28;
	tmp |= value << CAN_TXBAR_AR28_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR29) >> CAN_TXBAR_AR29_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR29;
	tmp |= value << CAN_TXBAR_AR29_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR30) >> CAN_TXBAR_AR30_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR30;
	tmp |= value << CAN_TXBAR_AR30_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_AR31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= CAN_TXBAR_AR31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBAR_AR31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp = (tmp & CAN_TXBAR_AR31) >> CAN_TXBAR_AR31_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBAR_AR31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= ~CAN_TXBAR_AR31;
	tmp |= value << CAN_TXBAR_AR31_Pos;
	((Can *)hw)->TXBAR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_AR31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~CAN_TXBAR_AR31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_AR31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= CAN_TXBAR_AR31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBAR_reg(const void *const hw, hri_can_txbar_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbar_reg_t hri_can_get_TXBAR_reg(const void *const hw, hri_can_txbar_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBAR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXBAR_reg(const void *const hw, hri_can_txbar_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBAR_reg(const void *const hw, hri_can_txbar_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBAR_reg(const void *const hw, hri_can_txbar_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBAR.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbar_reg_t hri_can_read_TXBAR_reg(const void *const hw)
{
	return ((Can *)hw)->TXBAR.reg;
}

static inline void hri_can_set_TXBCR_CR0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR0) >> CAN_TXBCR_CR0_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR0;
	tmp |= value << CAN_TXBCR_CR0_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR1) >> CAN_TXBCR_CR1_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR1;
	tmp |= value << CAN_TXBCR_CR1_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR2) >> CAN_TXBCR_CR2_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR2;
	tmp |= value << CAN_TXBCR_CR2_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR3) >> CAN_TXBCR_CR3_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR3;
	tmp |= value << CAN_TXBCR_CR3_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR4) >> CAN_TXBCR_CR4_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR4;
	tmp |= value << CAN_TXBCR_CR4_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR5) >> CAN_TXBCR_CR5_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR5;
	tmp |= value << CAN_TXBCR_CR5_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR6) >> CAN_TXBCR_CR6_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR6;
	tmp |= value << CAN_TXBCR_CR6_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR7) >> CAN_TXBCR_CR7_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR7;
	tmp |= value << CAN_TXBCR_CR7_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR8) >> CAN_TXBCR_CR8_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR8;
	tmp |= value << CAN_TXBCR_CR8_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR9) >> CAN_TXBCR_CR9_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR9;
	tmp |= value << CAN_TXBCR_CR9_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR10) >> CAN_TXBCR_CR10_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR10;
	tmp |= value << CAN_TXBCR_CR10_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR11) >> CAN_TXBCR_CR11_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR11;
	tmp |= value << CAN_TXBCR_CR11_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR12) >> CAN_TXBCR_CR12_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR12;
	tmp |= value << CAN_TXBCR_CR12_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR13) >> CAN_TXBCR_CR13_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR13;
	tmp |= value << CAN_TXBCR_CR13_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR14) >> CAN_TXBCR_CR14_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR14;
	tmp |= value << CAN_TXBCR_CR14_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR15) >> CAN_TXBCR_CR15_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR15;
	tmp |= value << CAN_TXBCR_CR15_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR16) >> CAN_TXBCR_CR16_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR16;
	tmp |= value << CAN_TXBCR_CR16_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR17) >> CAN_TXBCR_CR17_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR17;
	tmp |= value << CAN_TXBCR_CR17_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR18) >> CAN_TXBCR_CR18_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR18;
	tmp |= value << CAN_TXBCR_CR18_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR19) >> CAN_TXBCR_CR19_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR19;
	tmp |= value << CAN_TXBCR_CR19_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR20) >> CAN_TXBCR_CR20_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR20;
	tmp |= value << CAN_TXBCR_CR20_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR21) >> CAN_TXBCR_CR21_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR21;
	tmp |= value << CAN_TXBCR_CR21_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR22) >> CAN_TXBCR_CR22_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR22;
	tmp |= value << CAN_TXBCR_CR22_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR23) >> CAN_TXBCR_CR23_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR23;
	tmp |= value << CAN_TXBCR_CR23_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR24) >> CAN_TXBCR_CR24_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR24;
	tmp |= value << CAN_TXBCR_CR24_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR25) >> CAN_TXBCR_CR25_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR25;
	tmp |= value << CAN_TXBCR_CR25_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR26) >> CAN_TXBCR_CR26_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR26;
	tmp |= value << CAN_TXBCR_CR26_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR27) >> CAN_TXBCR_CR27_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR27;
	tmp |= value << CAN_TXBCR_CR27_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR28) >> CAN_TXBCR_CR28_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR28;
	tmp |= value << CAN_TXBCR_CR28_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR29) >> CAN_TXBCR_CR29_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR29;
	tmp |= value << CAN_TXBCR_CR29_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR30) >> CAN_TXBCR_CR30_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR30;
	tmp |= value << CAN_TXBCR_CR30_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_CR31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= CAN_TXBCR_CR31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCR_CR31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp = (tmp & CAN_TXBCR_CR31) >> CAN_TXBCR_CR31_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCR_CR31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= ~CAN_TXBCR_CR31;
	tmp |= value << CAN_TXBCR_CR31_Pos;
	((Can *)hw)->TXBCR.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_CR31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~CAN_TXBCR_CR31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_CR31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= CAN_TXBCR_CR31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCR_reg(const void *const hw, hri_can_txbcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbcr_reg_t hri_can_get_TXBCR_reg(const void *const hw, hri_can_txbcr_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXBCR_reg(const void *const hw, hri_can_txbcr_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCR_reg(const void *const hw, hri_can_txbcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCR_reg(const void *const hw, hri_can_txbcr_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCR.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbcr_reg_t hri_can_read_TXBCR_reg(const void *const hw)
{
	return ((Can *)hw)->TXBCR.reg;
}

static inline void hri_can_set_TXBTIE_TIE0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE0) >> CAN_TXBTIE_TIE0_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE0;
	tmp |= value << CAN_TXBTIE_TIE0_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE1) >> CAN_TXBTIE_TIE1_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE1;
	tmp |= value << CAN_TXBTIE_TIE1_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE2) >> CAN_TXBTIE_TIE2_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE2;
	tmp |= value << CAN_TXBTIE_TIE2_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE3) >> CAN_TXBTIE_TIE3_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE3;
	tmp |= value << CAN_TXBTIE_TIE3_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE4) >> CAN_TXBTIE_TIE4_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE4;
	tmp |= value << CAN_TXBTIE_TIE4_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE5) >> CAN_TXBTIE_TIE5_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE5;
	tmp |= value << CAN_TXBTIE_TIE5_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE6) >> CAN_TXBTIE_TIE6_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE6;
	tmp |= value << CAN_TXBTIE_TIE6_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE7) >> CAN_TXBTIE_TIE7_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE7;
	tmp |= value << CAN_TXBTIE_TIE7_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE8) >> CAN_TXBTIE_TIE8_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE8;
	tmp |= value << CAN_TXBTIE_TIE8_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE9) >> CAN_TXBTIE_TIE9_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE9;
	tmp |= value << CAN_TXBTIE_TIE9_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE10) >> CAN_TXBTIE_TIE10_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE10;
	tmp |= value << CAN_TXBTIE_TIE10_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE11) >> CAN_TXBTIE_TIE11_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE11;
	tmp |= value << CAN_TXBTIE_TIE11_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE12) >> CAN_TXBTIE_TIE12_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE12;
	tmp |= value << CAN_TXBTIE_TIE12_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE13) >> CAN_TXBTIE_TIE13_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE13;
	tmp |= value << CAN_TXBTIE_TIE13_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE14) >> CAN_TXBTIE_TIE14_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE14;
	tmp |= value << CAN_TXBTIE_TIE14_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE15) >> CAN_TXBTIE_TIE15_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE15;
	tmp |= value << CAN_TXBTIE_TIE15_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE16) >> CAN_TXBTIE_TIE16_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE16;
	tmp |= value << CAN_TXBTIE_TIE16_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE17) >> CAN_TXBTIE_TIE17_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE17;
	tmp |= value << CAN_TXBTIE_TIE17_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE18) >> CAN_TXBTIE_TIE18_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE18;
	tmp |= value << CAN_TXBTIE_TIE18_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE19) >> CAN_TXBTIE_TIE19_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE19;
	tmp |= value << CAN_TXBTIE_TIE19_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE20) >> CAN_TXBTIE_TIE20_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE20;
	tmp |= value << CAN_TXBTIE_TIE20_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE21) >> CAN_TXBTIE_TIE21_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE21;
	tmp |= value << CAN_TXBTIE_TIE21_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE22) >> CAN_TXBTIE_TIE22_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE22;
	tmp |= value << CAN_TXBTIE_TIE22_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE23) >> CAN_TXBTIE_TIE23_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE23;
	tmp |= value << CAN_TXBTIE_TIE23_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE24) >> CAN_TXBTIE_TIE24_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE24;
	tmp |= value << CAN_TXBTIE_TIE24_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE25) >> CAN_TXBTIE_TIE25_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE25;
	tmp |= value << CAN_TXBTIE_TIE25_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE26) >> CAN_TXBTIE_TIE26_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE26;
	tmp |= value << CAN_TXBTIE_TIE26_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE27) >> CAN_TXBTIE_TIE27_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE27;
	tmp |= value << CAN_TXBTIE_TIE27_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE28) >> CAN_TXBTIE_TIE28_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE28;
	tmp |= value << CAN_TXBTIE_TIE28_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE29) >> CAN_TXBTIE_TIE29_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE29;
	tmp |= value << CAN_TXBTIE_TIE29_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE30) >> CAN_TXBTIE_TIE30_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE30;
	tmp |= value << CAN_TXBTIE_TIE30_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_TIE31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= CAN_TXBTIE_TIE31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBTIE_TIE31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp = (tmp & CAN_TXBTIE_TIE31) >> CAN_TXBTIE_TIE31_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBTIE_TIE31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= ~CAN_TXBTIE_TIE31;
	tmp |= value << CAN_TXBTIE_TIE31_Pos;
	((Can *)hw)->TXBTIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_TIE31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~CAN_TXBTIE_TIE31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_TIE31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= CAN_TXBTIE_TIE31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBTIE_reg(const void *const hw, hri_can_txbtie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbtie_reg_t hri_can_get_TXBTIE_reg(const void *const hw, hri_can_txbtie_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBTIE.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXBTIE_reg(const void *const hw, hri_can_txbtie_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBTIE_reg(const void *const hw, hri_can_txbtie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBTIE_reg(const void *const hw, hri_can_txbtie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBTIE.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbtie_reg_t hri_can_read_TXBTIE_reg(const void *const hw)
{
	return ((Can *)hw)->TXBTIE.reg;
}

static inline void hri_can_set_TXBCIE_CFIE0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE0) >> CAN_TXBCIE_CFIE0_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE0;
	tmp |= value << CAN_TXBCIE_CFIE0_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE0_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE0;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE1) >> CAN_TXBCIE_CFIE1_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE1;
	tmp |= value << CAN_TXBCIE_CFIE1_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE1_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE1;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE2) >> CAN_TXBCIE_CFIE2_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE2;
	tmp |= value << CAN_TXBCIE_CFIE2_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE2_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE2;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE3) >> CAN_TXBCIE_CFIE3_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE3;
	tmp |= value << CAN_TXBCIE_CFIE3_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE3_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE3;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE4) >> CAN_TXBCIE_CFIE4_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE4;
	tmp |= value << CAN_TXBCIE_CFIE4_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE4_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE4;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE5) >> CAN_TXBCIE_CFIE5_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE5;
	tmp |= value << CAN_TXBCIE_CFIE5_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE5_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE5;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE6) >> CAN_TXBCIE_CFIE6_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE6;
	tmp |= value << CAN_TXBCIE_CFIE6_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE6_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE6;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE7) >> CAN_TXBCIE_CFIE7_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE7;
	tmp |= value << CAN_TXBCIE_CFIE7_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE7_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE7;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE8_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE8) >> CAN_TXBCIE_CFIE8_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE8_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE8;
	tmp |= value << CAN_TXBCIE_CFIE8_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE8_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE8;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE9_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE9) >> CAN_TXBCIE_CFIE9_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE9_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE9;
	tmp |= value << CAN_TXBCIE_CFIE9_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE9_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE9;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE10_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE10) >> CAN_TXBCIE_CFIE10_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE10_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE10;
	tmp |= value << CAN_TXBCIE_CFIE10_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE10_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE10;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE11_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE11) >> CAN_TXBCIE_CFIE11_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE11_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE11;
	tmp |= value << CAN_TXBCIE_CFIE11_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE11_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE11;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE12_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE12) >> CAN_TXBCIE_CFIE12_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE12_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE12;
	tmp |= value << CAN_TXBCIE_CFIE12_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE12_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE12;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE13_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE13) >> CAN_TXBCIE_CFIE13_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE13_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE13;
	tmp |= value << CAN_TXBCIE_CFIE13_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE13_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE13;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE14_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE14) >> CAN_TXBCIE_CFIE14_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE14_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE14;
	tmp |= value << CAN_TXBCIE_CFIE14_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE14_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE14;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE15_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE15) >> CAN_TXBCIE_CFIE15_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE15_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE15;
	tmp |= value << CAN_TXBCIE_CFIE15_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE15_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE15;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE16_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE16) >> CAN_TXBCIE_CFIE16_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE16_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE16;
	tmp |= value << CAN_TXBCIE_CFIE16_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE16_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE16;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE17_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE17) >> CAN_TXBCIE_CFIE17_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE17_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE17;
	tmp |= value << CAN_TXBCIE_CFIE17_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE17_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE17;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE18_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE18) >> CAN_TXBCIE_CFIE18_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE18_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE18;
	tmp |= value << CAN_TXBCIE_CFIE18_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE18_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE18;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE19_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE19) >> CAN_TXBCIE_CFIE19_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE19_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE19;
	tmp |= value << CAN_TXBCIE_CFIE19_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE19_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE19;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE20_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE20) >> CAN_TXBCIE_CFIE20_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE20_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE20;
	tmp |= value << CAN_TXBCIE_CFIE20_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE20_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE20;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE21_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE21) >> CAN_TXBCIE_CFIE21_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE21_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE21;
	tmp |= value << CAN_TXBCIE_CFIE21_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE21_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE21;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE22_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE22) >> CAN_TXBCIE_CFIE22_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE22_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE22;
	tmp |= value << CAN_TXBCIE_CFIE22_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE22_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE22;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE23_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE23) >> CAN_TXBCIE_CFIE23_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE23_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE23;
	tmp |= value << CAN_TXBCIE_CFIE23_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE23_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE23;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE24_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE24) >> CAN_TXBCIE_CFIE24_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE24_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE24;
	tmp |= value << CAN_TXBCIE_CFIE24_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE24_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE24;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE25_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE25) >> CAN_TXBCIE_CFIE25_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE25_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE25;
	tmp |= value << CAN_TXBCIE_CFIE25_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE25_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE25;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE26_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE26) >> CAN_TXBCIE_CFIE26_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE26_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE26;
	tmp |= value << CAN_TXBCIE_CFIE26_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE26_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE26;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE27_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE27) >> CAN_TXBCIE_CFIE27_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE27_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE27;
	tmp |= value << CAN_TXBCIE_CFIE27_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE27_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE27;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE28_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE28) >> CAN_TXBCIE_CFIE28_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE28_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE28;
	tmp |= value << CAN_TXBCIE_CFIE28_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE28_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE28;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE29_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE29) >> CAN_TXBCIE_CFIE29_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE29_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE29;
	tmp |= value << CAN_TXBCIE_CFIE29_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE29_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE29;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE30_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE30) >> CAN_TXBCIE_CFIE30_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE30_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE30;
	tmp |= value << CAN_TXBCIE_CFIE30_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE30_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE30;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_CFIE31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= CAN_TXBCIE_CFIE31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_can_get_TXBCIE_CFIE31_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp = (tmp & CAN_TXBCIE_CFIE31) >> CAN_TXBCIE_CFIE31_Pos;
	return (bool)tmp;
}

static inline void hri_can_write_TXBCIE_CFIE31_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= ~CAN_TXBCIE_CFIE31;
	tmp |= value << CAN_TXBCIE_CFIE31_Pos;
	((Can *)hw)->TXBCIE.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_CFIE31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~CAN_TXBCIE_CFIE31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_CFIE31_bit(const void *const hw)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= CAN_TXBCIE_CFIE31;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_set_TXBCIE_reg(const void *const hw, hri_can_txbcie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbcie_reg_t hri_can_get_TXBCIE_reg(const void *const hw, hri_can_txbcie_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXBCIE.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXBCIE_reg(const void *const hw, hri_can_txbcie_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXBCIE_reg(const void *const hw, hri_can_txbcie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXBCIE_reg(const void *const hw, hri_can_txbcie_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXBCIE.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txbcie_reg_t hri_can_read_TXBCIE_reg(const void *const hw)
{
	return ((Can *)hw)->TXBCIE.reg;
}

static inline void hri_can_set_TXEFC_EFSA_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg |= CAN_TXEFC_EFSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_get_TXEFC_EFSA_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp = (tmp & CAN_TXEFC_EFSA(mask)) >> CAN_TXEFC_EFSA_Pos;
	return tmp;
}

static inline void hri_can_write_TXEFC_EFSA_bf(const void *const hw, hri_can_txefc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp &= ~CAN_TXEFC_EFSA_Msk;
	tmp |= CAN_TXEFC_EFSA(data);
	((Can *)hw)->TXEFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXEFC_EFSA_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg &= ~CAN_TXEFC_EFSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXEFC_EFSA_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg ^= CAN_TXEFC_EFSA(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_read_TXEFC_EFSA_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp = (tmp & CAN_TXEFC_EFSA_Msk) >> CAN_TXEFC_EFSA_Pos;
	return tmp;
}

static inline void hri_can_set_TXEFC_EFS_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg |= CAN_TXEFC_EFS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_get_TXEFC_EFS_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp = (tmp & CAN_TXEFC_EFS(mask)) >> CAN_TXEFC_EFS_Pos;
	return tmp;
}

static inline void hri_can_write_TXEFC_EFS_bf(const void *const hw, hri_can_txefc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp &= ~CAN_TXEFC_EFS_Msk;
	tmp |= CAN_TXEFC_EFS(data);
	((Can *)hw)->TXEFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXEFC_EFS_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg &= ~CAN_TXEFC_EFS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXEFC_EFS_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg ^= CAN_TXEFC_EFS(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_read_TXEFC_EFS_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp = (tmp & CAN_TXEFC_EFS_Msk) >> CAN_TXEFC_EFS_Pos;
	return tmp;
}

static inline void hri_can_set_TXEFC_EFWM_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg |= CAN_TXEFC_EFWM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_get_TXEFC_EFWM_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp = (tmp & CAN_TXEFC_EFWM(mask)) >> CAN_TXEFC_EFWM_Pos;
	return tmp;
}

static inline void hri_can_write_TXEFC_EFWM_bf(const void *const hw, hri_can_txefc_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp &= ~CAN_TXEFC_EFWM_Msk;
	tmp |= CAN_TXEFC_EFWM(data);
	((Can *)hw)->TXEFC.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXEFC_EFWM_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg &= ~CAN_TXEFC_EFWM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXEFC_EFWM_bf(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg ^= CAN_TXEFC_EFWM(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_read_TXEFC_EFWM_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp = (tmp & CAN_TXEFC_EFWM_Msk) >> CAN_TXEFC_EFWM_Pos;
	return tmp;
}

static inline void hri_can_set_TXEFC_reg(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_get_TXEFC_reg(const void *const hw, hri_can_txefc_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFC.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXEFC_reg(const void *const hw, hri_can_txefc_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXEFC_reg(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXEFC_reg(const void *const hw, hri_can_txefc_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFC.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefc_reg_t hri_can_read_TXEFC_reg(const void *const hw)
{
	return ((Can *)hw)->TXEFC.reg;
}

static inline void hri_can_set_TXEFA_EFAI_bf(const void *const hw, hri_can_txefa_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFA.reg |= CAN_TXEFA_EFAI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefa_reg_t hri_can_get_TXEFA_EFAI_bf(const void *const hw, hri_can_txefa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFA.reg;
	tmp = (tmp & CAN_TXEFA_EFAI(mask)) >> CAN_TXEFA_EFAI_Pos;
	return tmp;
}

static inline void hri_can_write_TXEFA_EFAI_bf(const void *const hw, hri_can_txefa_reg_t data)
{
	uint32_t tmp;
	CAN_CRITICAL_SECTION_ENTER();
	tmp = ((Can *)hw)->TXEFA.reg;
	tmp &= ~CAN_TXEFA_EFAI_Msk;
	tmp |= CAN_TXEFA_EFAI(data);
	((Can *)hw)->TXEFA.reg = tmp;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXEFA_EFAI_bf(const void *const hw, hri_can_txefa_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFA.reg &= ~CAN_TXEFA_EFAI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXEFA_EFAI_bf(const void *const hw, hri_can_txefa_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFA.reg ^= CAN_TXEFA_EFAI(mask);
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefa_reg_t hri_can_read_TXEFA_EFAI_bf(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFA.reg;
	tmp = (tmp & CAN_TXEFA_EFAI_Msk) >> CAN_TXEFA_EFAI_Pos;
	return tmp;
}

static inline void hri_can_set_TXEFA_reg(const void *const hw, hri_can_txefa_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFA.reg |= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefa_reg_t hri_can_get_TXEFA_reg(const void *const hw, hri_can_txefa_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Can *)hw)->TXEFA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_can_write_TXEFA_reg(const void *const hw, hri_can_txefa_reg_t data)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFA.reg = data;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_clear_TXEFA_reg(const void *const hw, hri_can_txefa_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFA.reg &= ~mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline void hri_can_toggle_TXEFA_reg(const void *const hw, hri_can_txefa_reg_t mask)
{
	CAN_CRITICAL_SECTION_ENTER();
	((Can *)hw)->TXEFA.reg ^= mask;
	CAN_CRITICAL_SECTION_LEAVE();
}

static inline hri_can_txefa_reg_t hri_can_read_TXEFA_reg(const void *const hw)
{
	return ((Can *)hw)->TXEFA.reg;
}

#ifdef __cplusplus
}
#endif

#endif /* _HRI_CAN_C21_H_INCLUDED */
#endif /* _SAMC21_CAN_COMPONENT_ */
